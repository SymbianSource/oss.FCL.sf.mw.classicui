/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:
*
*/


#include <basched.h>
#include <barsread.h>
#include <eikenv.h>
#include <eikcmbut.h>
#include <eikmsg.h>
#include <gulcolor.h>
#include <gulutil.h>
#include <eikon.hrh>
#include <eikmfne.pan>
#include <eikmfne.h>
#include <eikctl.rsg>
#include <coecobs.h>
#include <AknUtils.h>
#include <avkon.hrh>
#include <aknenv.h>

// Skins drawing support
#include <AknsDrawUtils.h>
#include <aknappui.h>
#include <AknSettingCache.h>
#include <numberconversion.h>
#include <aknsoundsystem.h>
#include <AknTextDecorationMetrics.h>
#include <AknLayoutFont.h>
#include <AknBidiTextUtils.h>
#include <aknextendedinputcapabilities.h>
#include <fepbase.h>

#include <AknTasHook.h>
#include <eikdialg.h>

#include <touchfeedback.h>

// const TInt KMaxLatitudeDegrees=90;
// const TInt KMaxLongitudeDegrees=180;
const TInt KMaxMinSecValue=59;


namespace EikMfneUtils
    {
    /**
    IsAnyDigit, Is this a digit character any kind of numeral which can be mapped to 0-9?
    @internalComponent
    @return ETrue if this character is a numeral
    @param aCharacter character to be tested 
    */
    LOCAL_D TBool IsAnyDigit(TChar aCharacter)
        {
        return ( aCharacter.GetNumericValue() != KErrNotFound);
        }
    }

enum
    {
    EGapAboveText=0,
    EMfneFieldExtraHeight=2, // This constant is not used in Scalable UI
    EGapBelowText=0,
    EGapLeftOfFirstField=0,
    EGapRightOfLastField=0,
    EExtraHighlightHeight=0,
    };

// _LIT(KSpace," ");
_LIT(KPlus,"+");
_LIT(KMinus,"-");

// global functions

GLDEF_C TInt ExtraBaselineOffset()
    {
    TInt baselineOffset(0);
    return baselineOffset;
    }

// For positioning mfne vertically to the correct position.
GLDEF_C TInt VerticalOffsetForMfnePosition()
    {
    TAknLayoutId layout;
    CAknEnv::Static()->GetCurrentLayoutId( layout );
    return 0;
    }

GLDEF_C void Panic(TEikMfnePanic aPanic)
    {
    _LIT(KPanicCat,"EIKON-MFNE");
    User::Panic(KPanicCat, aPanic);
    }

NONSHARABLE_CLASS(CEikMfneExtension) : public CBase, public MCoeFepAwareTextEditor 
    {
public:
    static CEikMfneExtension* NewL();
    virtual ~CEikMfneExtension();
    
// From MCoeFepAwareTextEditor
public:
    void StartFepInlineEditL( const TDesC &aInitialInlineText,
        TInt aPositionOfInsertionPointInInlineText, TBool aCursorVisibility,
        const MFormCustomDraw *aCustomDraw,
        MFepInlineTextFormatRetriever &aInlineTextFormatRetriever,
        MFepPointerEventHandlerDuringInlineEdit
            &aPointerEventHandlerDuringInlineEdit );

    void UpdateFepInlineTextL( const TDesC &aNewInlineText,
        TInt aPositionOfInsertionPointInInlineText );
    
    void SetInlineEditingCursorVisibilityL( TBool aCursorVisibility );
    void CancelFepInlineEdit();
    TInt DocumentLengthForFep() const;
    TInt DocumentMaximumLengthForFep() const;
    void SetCursorSelectionForFepL( 
        const TCursorSelection &aCursorSelection );
        
    void GetCursorSelectionForFep( TCursorSelection &aCursorSelection ) const;
    void GetEditorContentForFep( TDes &aEditorContent, TInt aDocumentPosition,
        TInt aLengthToRetrieve ) const;
        
    void GetFormatForFep( TCharFormat &aFormat, TInt aDocumentPosition ) const;
    void GetScreenCoordinatesForFepL( TPoint &aLeftSideOfBaseLine,
        TInt &aHeight, TInt &aAscent, TInt aDocumentPosition ) const;

private:
    void DoCommitFepInlineEditL();
    void FieldToSelection( TInt aField, TCursorSelection &aCursorSelection ) const;

private: 
    CEikMfneExtension();
    void ConstructL();

public:
    MAknsControlContext* iExternalSkinControlContext;
    TInt iAknSkinColorIndex;
    TInt iSkinIdForTextBackgroundColor; 
    CAknExtendedInputCapabilities* iExtendedInputCapabilities;
    CEikMfne* iEditor; // not owned
    CAknExtendedInputCapabilities::CAknExtendedInputCapabilitiesProvider*
        iExtendedInputCapabilitiesProvider;
    TInt iClipGcToRect; // Mainly for 0/1 values
    TInt iDisablePenInput; // Mainly for 0/1 values
    TBool iTwiceTap;   
    TBool iCursorShown; 
    TBool iFingerSupport;
    TInt iFingerParam;
    TBool iHighlightAll; 
    TBool iTouchActivated;
    TCallBack iValidateValueCallBack;
    
    MTouchFeedback* iFeedback;
    TBool iLaunchPenInputAutomatic;
    TBool iPartialScreenInput;
    };

// Implementation of the extension
CEikMfneExtension* CEikMfneExtension::NewL()
    {
    CEikMfneExtension* self = new (ELeave) CEikMfneExtension();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

CEikMfneExtension::~CEikMfneExtension()
    {
    delete iExtendedInputCapabilities;
    delete iExtendedInputCapabilitiesProvider;
    }

CEikMfneExtension::CEikMfneExtension():iAknSkinColorIndex(KErrNotFound), iSkinIdForTextBackgroundColor(KErrNotFound)
    , iFeedback(MTouchFeedback::Instance())
    {
    }

void CEikMfneExtension::ConstructL()
    {
    iExtendedInputCapabilities = CAknExtendedInputCapabilities::NewL();
    iExtendedInputCapabilitiesProvider =
        new (ELeave) CAknExtendedInputCapabilities::CAknExtendedInputCapabilitiesProvider;
        
    iExtendedInputCapabilitiesProvider->SetExtendedInputCapabilities(
        iExtendedInputCapabilities );
    }


void CEikMfneExtension::StartFepInlineEditL( const TDesC &/*aInitialInlineText*/,
        TInt /*aPositionOfInsertionPointInInlineText*/, TBool /*aCursorVisibility*/,
        const MFormCustomDraw */*aCustomDraw*/,
        MFepInlineTextFormatRetriever &/*aInlineTextFormatRetriever*/,
        MFepPointerEventHandlerDuringInlineEdit
            &/*aPointerEventHandlerDuringInlineEdit*/ )
    {
    // No implementation
    }


void CEikMfneExtension::UpdateFepInlineTextL( const TDesC &/*aNewInlineText*/,
        TInt /*aPositionOfInsertionPointInInlineText*/ )
    {
    // No implementation
    }
    
    
void CEikMfneExtension::SetInlineEditingCursorVisibilityL( TBool /*aCursorVisibility*/ )
    {
    // No implementation
    }
    
    
void CEikMfneExtension::CancelFepInlineEdit()
    {
    // No implementation
    }
    
    
TInt CEikMfneExtension::DocumentLengthForFep() const
    {
    TInt documentLength( 0 );
    
    // The fields' concrete Text() function must be
    // properly implemented for this to work.
    for ( TInt i = 0; i < iEditor->NumFields(); ++i )
        {
        documentLength += iEditor->Field( i )->FieldText().Length();
        }

    return documentLength;
    }
    
    
TInt CEikMfneExtension::DocumentMaximumLengthForFep() const
    {
    // We can't reach the field descriptors' MaxLength
    // from here, as the implementations may vary
    return DocumentLengthForFep();
    }
    
    
void CEikMfneExtension::SetCursorSelectionForFepL(
    const TCursorSelection &aCursorSelection )
    {
    TInt documentLength( 0 );
    TInt cursorPos = aCursorSelection.iCursorPos;
    TInt i( 0 );
    // The fields' concrete Text() function must be
    // properly implemented for this to work.
    for ( ; i < iEditor->NumFields(); ++i )
        {
        documentLength += iEditor->Field( i )->FieldText().Length();
  
        if ( cursorPos <= documentLength )
            {
            if ( iEditor->Field( i )->IsEditable() )
                {
                iEditor->HighlightField( i );
                break;
                }
            else
                {
                cursorPos++;
                }
            }
        }
    
    if ( iFingerSupport && iFingerParam == CEikMfne::EnableWithAllHighlight )
        {
        TBool oldHighlightAll( iHighlightAll );                
        iHighlightAll = ( aCursorSelection.Length() > documentLength && 
            i == iEditor->NumFields() );
        iTouchActivated = !iHighlightAll;
        if ( oldHighlightAll != iHighlightAll )
            {
            CEikMfneField* currentField( iEditor->Field( 
                iEditor->CurrentField() ) );
            if ( currentField->HighlightType() == CEikMfneField::ECursor )
                {
                const CFont& font=*( iEditor->Font() );
                TBool dataAltered( EFalse );
                TBool error( EFalse );
                CEikonEnv* env( CEikonEnv::Static() );
                currentField->HandleDeHighlight( font, *env, dataAltered, 
                    error );
                env->HideCursor( iEditor );
                iCursorShown = EFalse;                
                }
            iEditor->DrawDeferred();
            iEditor->ReportUpdate();
            if ( iHighlightAll )
                {
                iEditor->SetFirstEditableField();
                }
            }
        if ( !iTouchActivated )
            {
            iValidateValueCallBack.CallBack();
            iEditor->ReportStateChangeEventL();
            }
        }
    }
        
void CEikMfneExtension::FieldToSelection( TInt aField, TCursorSelection &aCursorSelection ) const
    {
    TInt fieldStart( 0 );
    TInt fieldEnd( 0 );
    TInt fieldIndex( 0 );
    
    while ( fieldIndex < iEditor->NumFields() && fieldIndex <= aField )
        {
        fieldStart = fieldEnd;
        fieldEnd += iEditor->Field( fieldIndex )->FieldText().Length();
        
        if ( fieldIndex == aField )
            {
            aCursorSelection.SetSelection( fieldStart, fieldEnd );
            }
        
        fieldIndex++;
        }
    }
    
void CEikMfneExtension::GetCursorSelectionForFep( TCursorSelection &aCursorSelection ) const
    {
    TInt currentField = iEditor->CurrentField();
    
    // ENullIndex is private
    if ( iFingerSupport && ( iFingerParam == CEikMfne::EnableWithAllHighlight ) && 
        iHighlightAll )
        {
        aCursorSelection.SetSelection( 0, DocumentLengthForFep() );        
        }
    else if ( currentField >= 0 && currentField < iEditor->NumFields() )
        {
        CEikMfneField* field = iEditor->Field( currentField );
        
        FieldToSelection( currentField, aCursorSelection );
    
        // If the field is not highlighted, we'll assume that the
        // cursor is in the end of the field.
        if ( field->HighlightType() == CEikMfneField::ECursor )
            {
            aCursorSelection.iCursorPos = aCursorSelection.iAnchorPos;
            }
        }
    else
        {
        aCursorSelection.SetSelection( -1, -1 );
        }
    }
    
    
void CEikMfneExtension::GetEditorContentForFep( TDes &aEditorContent, TInt aDocumentPosition,
        TInt aLengthToRetrieve ) const
    {
    TInt length = DocumentLengthForFep();
    
    HBufC* content = HBufC::New( length );
    if ( content )
        {
        TPtr contentPtr = content->Des();
        
        for ( TInt i = 0; i < iEditor->NumFields(); ++i )
            {
            contentPtr += iEditor->Field( i )->FieldText();
            }
            
        aEditorContent =
            contentPtr.Mid( aDocumentPosition, aLengthToRetrieve );
            
        delete content;
        }
    }
      
        
void CEikMfneExtension::GetFormatForFep( TCharFormat &/*aFormat*/, TInt /*aDocumentPosition*/ ) const
    {
    // No implementation
    }
    
// FEP uses this function to get the coordinates of bottom of current cursor
void CEikMfneExtension::GetScreenCoordinatesForFepL(
    TPoint &aLeftSideOfBaseLine, TInt &aHeight, TInt &aAscent,
    TInt /*aDocumentPosition*/ ) const
    {
    TInt cursorWidth( 0 );
    iEditor->GetCursorInfo( aLeftSideOfBaseLine, aHeight, cursorWidth, 
        aAscent );
    TPoint screenPos( iEditor->PositionRelativeToScreen() );
    TPoint edwinPos = iEditor->Position();
    aLeftSideOfBaseLine.iY += ( screenPos.iY - edwinPos.iY );    
    }
    
void CEikMfneExtension::DoCommitFepInlineEditL()
    {
    // No implementation
    }

// CEikMfneField

EXPORT_C CEikMfneField::CEikMfneField()
    :iMinimumWidthInPixels(0)
    {
    __DECLARE_NAME(_S("CEikMfneField"));
    }

void CEikMfneField::Draw(CWindowGc& aGc, const CFont& aFont, const TPoint& aTopLeft) const
    {
    // Note that skin background drawing is currently performed in CEikMfne::DrawRange.
    // So this is just responsible for text and (depending on highlighting) the highlight block    
    TInt topMargin(0);
    TInt bottomMargin(0);
    TInt extraHeight(0);
    TAknTextDecorationMetrics metrics( &aFont );
    metrics.GetTopAndBottomMargins( topMargin, bottomMargin );
    extraHeight = topMargin + bottomMargin;
    const CAknLayoutFont* layoutFont = CAknLayoutFont::AsCAknLayoutFontOrNull( &aFont );
    TInt textPaneHeight(0);
    TInt textPaneAscent(0);

    // Get the pane metrics from the best source of information
    if ( layoutFont )
        {
        textPaneHeight = layoutFont->TextPaneHeight();
        textPaneAscent = layoutFont->TextPaneTopToBaseline();
        }
    else
        {
        textPaneHeight = aFont.HeightInPixels();
        textPaneAscent = aFont.AscentInPixels();
        }

    // This is similar to TAknLayoutText's draw, but includes margins.
    // Text and background are draw in one operation. Positioning of the text horizontally
    // w.r.t. aTopMargin is done with the "aLeftMargin" parameter. Horizontal extent is
    // controlled by the width of the "aBox" parameter
    TInt leftMargin(0);
    TInt rightMargin(0);
    metrics.GetLeftAndRightMargins( leftMargin, rightMargin );
    
    // Convert the text to visual
    TInt textWidth    = WidthInPixels( aFont );
    TPtrC drawText    = Text();
    HBufC* visualText = HBufC::New( drawText.Length() + KAknBidiExtraSpacePerLine );
    
    if ( visualText )
        {
        TPtr visualTextPtr = visualText->Des();
                        
        AknBidiTextUtils::ConvertToVisualAndClip(
            drawText,
            visualTextPtr,
            aFont,
            textWidth,
            textWidth,
            AknBidiTextUtils::EImplicit,
            0xFFFF ); // no clipping char
            
        drawText.Set( *visualText );
        }
    
    aGc.DrawText( drawText,
        TRect( aTopLeft, // top left. Should be control top left
        TSize( textWidth, //width
        textPaneHeight + extraHeight )), // total height
        textPaneAscent + topMargin, // distance from top to baseline
        CGraphicsContext::ECenter); // alignment to center
        
    delete visualText;
    }

TInt CEikMfneField::WidthInPixels(const CFont& aFont) const
    {
    return Max( iMinimumWidthInPixels, aFont.TextWidthInPixels(Text()) + AdditionalWidthForHighlights(aFont) );
    }

TInt CEikMfneField::DistanceFromStartOfFieldToEndOfTextInPixels(const CFont& aFont) const
    {
    // Approximation is that the spacing in glyphs is on the right. Therefore the additional spacing will
    // have been put on the left. See the draw routine call in CEikMMfneField::Draw
    TInt textwidth = aFont.TextWidthInPixels(Text()); 
    return  textwidth + AdditionalWidthForHighlights(aFont)+ (WidthInPixels(aFont)-textwidth)/2;
    }

EXPORT_C TBool CEikMfneField::IsEditable() const
    {
    return EFalse;
    }

EXPORT_C TBool CEikMfneField::IsValid() const
    {
    return ETrue;
    }

EXPORT_C CEikMfneField::THighlightType CEikMfneField::HighlightType() const
    {
#if defined(_DEBUG)
    Panic(EEikPanicMfneFieldIsNotEditable1);
#endif
    return EInverseVideo; // dummy return to prevent compiler error
    }

EXPORT_C void CEikMfneField::HandleKey(const CFont&, const TKeyEvent&, TBool, TBool&, TInt&)
    {
#if defined(_DEBUG)
    Panic(EEikPanicMfneFieldIsNotEditable2);
#endif
    }

EXPORT_C void CEikMfneField::HandleDeHighlight(const CFont&, CEikonEnv&, TBool&, TBool&)
    {
#if defined(_DEBUG)
    Panic(EEikPanicMfneFieldIsNotEditable3);
#endif
    }

EXPORT_C void CEikMfneField::HandleLeftOrRightArrow(TChar aKey, TBool& aDataAltered, TInt& aHighlightIncrement)
    {
    __ASSERT_DEBUG((aKey==EKeyLeftArrow) || (aKey==EKeyRightArrow), Panic(EEikPanicMfneArrowKeyExpected));
    aHighlightIncrement=(aKey==EKeyLeftArrow)? -1: 1;
    aDataAltered=ETrue;
    }

TInt CEikMfneField::AdditionalWidthForHighlights(const CFont& aFont) const
    {
    TInt addedWidth(0);
    if ( IsEditable() )
        {
        TInt rightHighlight(0);
        TAknTextDecorationMetrics metrics( &aFont );
        // Width is increased only by leftHighlight.  This is a compromise in that glyphs already have 
        // spacing within them to achieve character spacing. This spacing is generally (for numbers) on the right. 
        metrics.GetLeftAndRightMargins( addedWidth, rightHighlight ); // rightHighlight is not used
        }
    return addedWidth;
    }

const TDesC& CEikMfneField::FieldText() const
    {
    return Text();
    }

// CEikMfneSeparator

CEikMfneSeparator::CEikMfneSeparator(HBufC* aText)
    :iText(aText)
    {
    __DECLARE_NAME(_S("CEikMfneSeparator"));
    }

EXPORT_C CEikMfneSeparator::~CEikMfneSeparator()
    {
    delete iText;
    }

EXPORT_C CEikMfneSeparator* CEikMfneSeparator::NewL(TResourceReader& aResourceReader)
    {
    HBufC* text=aResourceReader.ReadHBufCL();
    CleanupStack::PushL(text);
    CEikMfneSeparator* separator=NewL(text);
    CleanupStack::Pop();
    return separator;
    }

EXPORT_C CEikMfneSeparator* CEikMfneSeparator::NewL(HBufC* aText)
    {
    return new(ELeave) CEikMfneSeparator(aText);
    }

EXPORT_C void CEikMfneSeparator::SetText(HBufC* aText)
    {
    __ASSERT_ALWAYS(iText==NULL, Panic(EEikPanicMfneSeparatorTextHasAlreadyBeenSet));
    iText=aText;
    }

TInt CEikMfneSeparator::MaximumWidthInPixels(const CFont& aFont, TBool)
    {
    return aFont.TextWidthInPixels(*iText)+AdditionalWidthForHighlights(aFont);
    }

TCoeInputCapabilities CEikMfneSeparator::InputCapabilities() const
    {
    return TCoeInputCapabilities(TCoeInputCapabilities::ENone);
    }

const TDesC& CEikMfneSeparator::Text() const
    {
    return *iText;
    }



// CEikMfneNumber

CEikMfneNumber::CEikMfneNumber(TInt aMinimumValue, TInt aMaximumValue, TUint32 aFlags)
    :iMinimumValue(aMinimumValue),
     iMaximumValue(aMaximumValue),
     iFlags(aFlags),
     iDigitType(EDigitTypeWestern)
    {
    TBuf<16> minText;
    minText.AppendNum(aMinimumValue);
    TBuf<16> maxText;
    maxText.AppendNum(aMaximumValue);
    iMaxDigits=Max(minText.Length(),maxText.Length());

    iMaxDigitsMinimumValue=minText.Length();
    iMaxDigitsMaximumValue=maxText.Length();

    __DECLARE_NAME(_S("CEikMfneNumber"));
    __ASSERT_ALWAYS(aMinimumValue<=aMaximumValue, Panic(EEikPanicMfneBadNumberMinimumAndMaximum1));
    __ASSERT_ALWAYS((aFlags&~EPublicallySettableFlags)==0, Panic(EEikPanicMfneBadNumberFlags));
    }

EXPORT_C CEikMfneNumber::~CEikMfneNumber()
    {
    delete iText;
    }

EXPORT_C CEikMfneNumber* CEikMfneNumber::NewL(const CFont& aFont, TResourceReader& aResourceReader)
    {
#pragma warning (disable : 4127)
    __ASSERT_DEBUG((EFillWithLeadingZeros==EEikMfneNumberFlagFillWithLeadingZeros) &&
                   (EPreserveOldWidthBeforeEditing==EEikMfneNumberFlagPreserveOldWidthBeforeEditing) &&
                   (EFillWithLeadingZeros==EEikMfneNumberFlagFillWithLeadingZeros), Panic(EEikPanicMfneInconsistentNumberFlags));
#pragma warning (default : 4127)
    TInt minimumValue=aResourceReader.ReadInt32();
    TInt maximumValue=aResourceReader.ReadInt32();
    TUint32 flags=aResourceReader.ReadUint8();
    return NewL(aFont, minimumValue, maximumValue, maximumValue, flags);
    }

EXPORT_C CEikMfneNumber* CEikMfneNumber::NewL(const CFont& aFont, TInt aMinimumValue, TInt aMaximumValue, TInt aInitialValue, TUint32 aFlags)
    {
    __ASSERT_ALWAYS((aInitialValue>=aMinimumValue) && (aInitialValue<=aMaximumValue), Panic(EEikPanicMfneBadNumberMinimumAndMaximum2));
    CEikMfneNumber* number=new(ELeave) CEikMfneNumber(aMinimumValue, aMaximumValue, aFlags);
    CleanupStack::PushL(number);
    number->iText=HBufC::NewL(number->MaximumNumberOfDigits()+((aMinimumValue<0)? 1: 0));
    number->SetValue(aInitialValue, aFont);
    number->ConstructL();
    CleanupStack::Pop();
    return number;
    }

void CEikMfneNumber::ConstructL()
    {
    CEikonEnv* eikEnv=CEikonEnv::Static();
    iNudgeCharMinus=eikEnv->NudgeCharMinus();
    iNudgeCharPlus=eikEnv->NudgeCharPlus();
    }

EXPORT_C void CEikMfneNumber::SetMinimumAndMaximum(TInt aMinimumValue, TInt aMaximumValue, const CFont& aFont)
    {
    TBuf<16> minText;
    minText.AppendNum(aMinimumValue);
    TBuf<16> maxText;
    maxText.AppendNum(aMaximumValue);
    TInt minTextLength=minText.Length();
    TInt maxTextLength=maxText.Length();
    __ASSERT_ALWAYS((aMinimumValue<=aMaximumValue) &&
                    (minTextLength<=iMaxDigits) &&
                    (maxTextLength<=iMaxDigits), Panic(EEikPanicMfneBadNumberMinimumAndMaximum3));
    //__ASSERT_ALWAYS((aMinimumValue<=aMaximumValue) &&
    //              (aMinimumValue>=iMinimumValueCateredForInFieldWidth) &&
    //              (aMaximumValue<=iMaximumValueCateredForInFieldWidth), Panic(EEikPanicMfneBadNumberMinimumAndMaximum3));
    iMinimumValue=aMinimumValue;
    iMaximumValue=aMaximumValue;
    TInt value=ValueFromText();
    if (value<aMinimumValue||!NumberOfDigits())
        SetTextToValue(aMinimumValue, aFont);
    else if (value>aMaximumValue)
        SetTextToValue(aMaximumValue, aFont);
    }

EXPORT_C void CEikMfneNumber::GetMinimumAndMaximum(TInt& aMinimumValue, TInt& aMaximumValue) const
    {
    aMinimumValue=iMinimumValue;
    aMaximumValue=iMaximumValue;
    }

EXPORT_C void CEikMfneNumber::SetValue(TInt aValue, const CFont& aFont)
    {
    // This is part of the trailing zeros and TInt fix. We have to do this to
    // allow setting values like "050" by passing 50 to this function in case
    // the trailing zeros are on.
    if ( iFlags & EFillWithTrailingZeros )
        {
        TInt val = aValue;
        TInt count = 0;
        for(;val;val/=10) count ++; 
        if (MaximumNumberOfDigits()-count < 0) count = MaximumNumberOfDigits();
        iText->Des().Fill( TText('1'), MaximumNumberOfDigits() );
        iText->Des().Fill( ZeroCharacter(), MaximumNumberOfDigits() - count);
        }
        
    SetTextToValue(aValue, aFont);
    }

EXPORT_C TInt CEikMfneNumber::Value() const
    {
    TInt value( -1 );
    if (NumberOfDigits() > 0)
        {
        value = ValueFromText();
        }    
    if (value < iMinimumValue)
        {
        value = iMinimumValue;
        }
    if (value > iMaximumValue)
        {       
        value = iMaximumValue;
        }
    return value;
    }

EXPORT_C TBool CEikMfneNumber::IsValid() const
    {
    return (NumberOfDigits() != 0);
    }

TChar CEikMfneNumber::NormalizeDigit(TChar aChar)
/**
NormalizeDigit
Normalises a character to the current digit type.
@internalComponent
@return TChar of  if this character is a numeral
@param aCharacter character to be tested 
*/
    {
    TBuf<1> buf;
    buf.Append(aChar);
    NumberConversion::ConvertDigits(buf, iDigitType);
    return buf[0];
    }

TText CEikMfneNumber::ZeroCharacter() const
        {
        return TText(iDigitType);
        }

TText CEikMfneNumber::NegativeCharacter() const
        {
        return TText('-');
        }

TBool CEikMfneNumber::IsTextNull() const
    {
    return ( Text().Length() < 1 );
    }

TInt CEikMfneNumber::MaximumWidthInPixels(const CFont& aFont, TBool aShrinkToMinimumSize)
    {
    if (aShrinkToMinimumSize)
        {
        //iMinimumValueCateredForInFieldWidth=iMinimumValue;
        //iMaximumValueCateredForInFieldWidth=iMaximumValue;
        TBuf<16> minText;
        minText.AppendNum(iMinimumValue);
        TBuf<16> maxText;
        maxText.AppendNum(iMaximumValue);

        iMaxDigits=Max(2,Max(minText.Length(),maxText.Length()));
        }
    return (MaximumNumberOfDigits()*TFindWidthOfWidestDigitType(DigitType()).MaximumWidthInPixels(aFont)) + AdditionalWidthForHighlights(aFont) /*+((iMinimumValueCateredForInFieldWidth<0)? aFont.TextWidthInPixels(_L("-")): 0)*/;
    }

TCoeInputCapabilities CEikMfneNumber::InputCapabilities() const
    {
    TUint inputCapabilities=TCoeInputCapabilities::ENone;
    if (iMinimumValue<0)
        {
        inputCapabilities|=TCoeInputCapabilities::EWesternNumericIntegerNegative;
        }
    if (iMaximumValue>0)
        {
        inputCapabilities|=TCoeInputCapabilities::EWesternNumericIntegerPositive;
        }
    return TCoeInputCapabilities(inputCapabilities);
    }

const TDesC& CEikMfneNumber::Text() const
    {
    if (IsUninitialised())
        return KNullDesC();
    else
        return *iText;
    }

TBool CEikMfneNumber::IsEditable() const
    {
    return ETrue;
    }

CEikMfneField::THighlightType CEikMfneNumber::HighlightType() const
    {
    return (iFlags&EIsBeingEditedWithCursor)? ECursor: EInverseVideo;
    }

void CEikMfneNumber::HandleKey(const CFont& aFont, const TKeyEvent& aKeyEvent, TBool aInterpretLeftAndRightAsEarEvents, TBool& aDataAltered, TInt& aHighlightIncrement)
    {
    TChar ch=aKeyEvent.iCode;

    TPtr text=iText->Des();
    TInt textLength=text.Length();
    TBool nudgeTen=EFalse;
    switch (ch)
        {
    case EKeyLeftArrow:
    case EKeyRightArrow:
        if (!aInterpretLeftAndRightAsEarEvents)
            HandleLeftOrRightArrow(ch, aDataAltered, aHighlightIncrement);
        else
            {
            const TInt nudge=(nudgeTen? 10 : 1);
            TInt newValue;


            if ((textLength==0) || ! EikMfneUtils::IsAnyDigit( TChar(text[textLength-1]) ) )
                newValue=0;
            else
                newValue=ValueFromText()+((ch==EKeyLeftArrow)? -nudge: nudge);
            if (newValue>=iMaximumValue)
                newValue=iMaximumValue;
            else if (newValue<=iMinimumValue)
                newValue=iMinimumValue;
            SetTextToValue(newValue, aFont);
            aHighlightIncrement=0;// Always highlight the field being nudged
            aDataAltered=ETrue;
            SetUninitialised(EFalse);
            iFlags&=~EIsBeingEditedWithCursor;
            }
        break;
    case EKeyDownArrow:
    case EKeyUpArrow:
        {
        if (IsUninitialised())
            {
            SetUninitialised(EFalse);
            }
        else
            {
                const TInt nudge=(nudgeTen? 10 : 1);
                TInt newValue;


                if ((textLength==0) || ! EikMfneUtils::IsAnyDigit( TChar(text[textLength-1])) )
                    newValue=0;
                else
                        newValue=ValueFromText()+((ch==EKeyDownArrow)? -nudge: nudge);
       
            if (newValue>iMaximumValue)
                        newValue=iMinimumValue;
                else if (newValue<iMinimumValue)
                    newValue=iMaximumValue;
                SetTextToValue(newValue, aFont);
                aHighlightIncrement=0;// Always highlight the field being nudged
                aDataAltered=ETrue;
                iFlags&=~EIsBeingEditedWithCursor;
            }
        aDataAltered=ETrue;
        }
        break;
    case EKeyBackspace:
        if (textLength)
            {
            if (iFlags&EIsBeingEditedWithCursor)
                {
                text.SetLength(textLength-1);
                }
            else
                {
                iFlags|=EIsBeingEditedWithCursor;
                text.SetLength(0);
                }
            if (text==KMinus)
                text.SetLength(0);
            aDataAltered=ETrue;
            SetUninitialised(EFalse);
            }
        break;
    case '+':
        break;
    case '-':
        if (iMinimumValue < 0)
            {
            if (~iFlags&EIsBeingEditedWithCursor)
                {
                iFlags|=EIsBeingEditedWithCursor;
                text.SetLength(0);
                }
            if (text.Length()==0)
                {
                text.Append('-');
                aDataAltered=ETrue;
                SetUninitialised(EFalse);
                }
            }
        break;
    default:
        if ( EikMfneUtils::IsAnyDigit(ch) )
            {
            if (~iFlags&EIsBeingEditedWithCursor)
                {
                iFlags|=EIsBeingEditedWithCursor;
                text.SetLength(0);
                }
            __ASSERT_DEBUG(NumberOfDigits()<MaximumNumberOfDigits(),Panic(EEikPanicMfneNumberTextInBadState));
            text.Append(NormalizeDigit(ch) );
            aDataAltered=ETrue;
            SetUninitialised(EFalse);
            
            // Space reserved for minus sign is not supposed to be shown, so if
            // the value is >= 0 we must subtract the space for minus in case
            // the minimum possible value is negative..
            if ( NumberOfDigits() >= 
                ( ValueFromText() >= 0 && iMinimumValue < 0 ? MaximumNumberOfDigits() - 1 : MaximumNumberOfDigits() ) )
                {
                aHighlightIncrement=1;
                }
            }
        break;
        }
    }

void CEikMfneNumber::HandleDeHighlight(const CFont& aFont, CEikonEnv& aEikonEnv, TBool& aDataAltered, TBool& aError)
    {
    iFlags&=~EIsBeingEditedWithCursor;
    if (NumberOfDigits()==0)
        {
        SetTextToValue(iMinimumValue, aFont);
        aDataAltered=ETrue;
        aError=ETrue;
        aEikonEnv.InfoMsg(R_EIK_TBUF_NO_NUMBER_ENTERED);
        return;
        }
    TInt value=ValueFromText();
    if ((value<iMinimumValue) || (value>iMaximumValue))
        {
        TBool succeeded = ConvertsIntoValidValue(value);
        if ( !succeeded )
            {
            aDataAltered=ETrue;
            aError=ETrue;
            if (value<iMinimumValue)
                {
                SetTextToValue(iMinimumValue, aFont);
                CEikMfne::InvalidFieldAlert();
                aEikonEnv.InfoMsg(R_EIK_TBUF_NUMBER_BELOW_MIN, iMinimumValue);
                return;
                }
            if (value>iMaximumValue) 
                {
                CEikMfne::InvalidFieldAlert();
                SetTextToValue(iMaximumValue, aFont);
                aEikonEnv.InfoMsg(R_EIK_TBUF_NUMBER_ABOVE_MAX, iMaximumValue);
                return;
                }
            }
        }
    TBuf<128> oldText=*iText;
    TBool unInit = IsUninitialised();
    SetTextToValue(value, aFont);
    if (oldText!=*iText)
        aDataAltered=ETrue;
    else
        SetUninitialised(unInit);
    }

TInt CEikMfneNumber::MaximumNumberOfDigits() const
    {
    return Max(2,iMaxDigits);
    }

TInt CEikMfneNumber::NumberOfDigits() const
    {
    return iText->Length();
    }

void CEikMfneNumber::SetTrailingZeros()
    {
    iFlags |= EFillWithTrailingZeros;
    }

void CEikMfneNumber::SetTextToValue(TInt aValue, const CFont& /*aFont*/)
    {
    __ASSERT_DEBUG((aValue>=iMinimumValue) && (aValue<=iMaximumValue), Panic(EEikPanicMfneNumberOutsidePermittedRange));
    
    SetUninitialised(EFalse);

    TPtr textPtr       = iText->Des();
    TInt maxNumbers    = MaximumNumberOfDigits();
    TInt leadingZeros  = 0;
    TText zeroChar     = ZeroCharacter();
    TText negChar      = NegativeCharacter();

    // The problem here is that we have no way of knowing through TInt aValue
    // if the number that is wanted is 005, 05, or 5. That would be fine
    // as long as trailing zeros are not used, but with the trailing
    // zeros one has to be able to enter "050" by typing just "05".
    // When this is typed and the field changes, this function gets called with
    // aValue of 5, and we don't know if that should really be "500", "050" or
    // "005", because all those values could be possible in a number with
    // trailing zeros. The following tries to overcome this limitation..
    TLex lex( textPtr );
    TChar chr;

    while ( chr = lex.Get() )
        {
        if ( chr == zeroChar )
            {
            leadingZeros++;
            }
        else if ( chr != negChar )
            {
            break; // We break at first char that's not '-' or zero
            }
        }
        
    textPtr.SetLength( 0 );

    if ( iMinimumValue < 0 )
        {
        maxNumbers--;

        // Has to be done here, because we have to pad between
        // the negative char and the number.
        if ( aValue < 0 )
            {
            textPtr.Append( negChar );
            aValue = -aValue;
            }        
        }
        
    // From this on we deal with western digits, and convert at the end
    zeroChar = TText( '0' );
                
    if ( iFlags & EFillWithTrailingZeros ) // trailing takes precedence
        {
        HBufC* formatStringBuf = HBufC::New( leadingZeros + 10 );
        
        if ( !formatStringBuf )
            {
            textPtr.Num( aValue );
            }
        else
            {
            TPtr formatString = formatStringBuf->Des();
            
            if ( aValue != 0 && leadingZeros )
                {
                formatString.Fill( zeroChar, leadingZeros );
                maxNumbers -= leadingZeros;
                }

            _LIT( KFormatString, "%-**d" );
            formatString.Append( KFormatString );
            textPtr.AppendFormat( formatString, zeroChar, maxNumbers, aValue );
            delete formatStringBuf;
            }
        }
    else if ( iFlags & EFillWithLeadingZeros )
        {
        _LIT( KFormatString, "%+**d" );
        textPtr.Format( KFormatString, zeroChar, maxNumbers, aValue );
        }
    else
        {
        textPtr.Num( aValue );
        }
    
    NumberConversion::ConvertDigits( textPtr, iDigitType );
    
    if ( iFlags & EPreserveOldWidthBeforeEditing )
        {
        iMinimumWidthInPixels = 0; //WidthInPixels(aFont);    
        }
    }

TInt CEikMfneNumber::ValueFromText() const
    {
//  __ASSERT_DEBUG(NumberOfDigits(), Panic(EEikPanicMfneNumberHasNoDigits));
    if (!NumberOfDigits())
        return iMinimumValue;
    TInt i=0;
    TInt valueFromText=0;
    TBool isNegative=EFalse;
    switch ((*iText)[i])
        {
    case '-':
        ++i;
        isNegative=ETrue;
        break;
        }
    TInt textLength=iText->Length();
    for (; i<textLength; ++i)
        {
        TText digit=(*iText)[i];
        __ASSERT_DEBUG(EikMfneUtils::IsAnyDigit( TChar(digit)), Panic(EEikPanicMfneDigitExpected));
        if (i>=textLength-2)
            {
            if (!isNegative && valueFromText>(KMaxTInt32/10))
                return KMaxTInt32;
            else if (isNegative && (-valueFromText)<(KMinTInt32/10))
                return KMinTInt32;
            }
        valueFromText=(valueFromText*10)+(TInt)(digit-ZeroCharacter());
        }
    if (isNegative==EFalse && valueFromText<0)
        return KMaxTInt32;// Deals with overflow
    if (isNegative)
        valueFromText=-valueFromText;
    return valueFromText;
    }

TBool CEikMfneNumber::ConvertsIntoValidValue(TInt& aValue) const
    {
    if ((iFlags&ERepresentsYear) && (aValue>=0) && (aValue<100))
        {
        TTime homeTime;
        homeTime.HomeTime();
        TInt currentYear=homeTime.DateTime().Year();
        if (currentYear>0)
            {
            TInt yearsSinceStartOfCurrentCentury=currentYear%100;
            TInt newValue=(currentYear-yearsSinceStartOfCurrentCentury)+aValue;
            // If two digit year is given, 2000 + aValue is expected.
            aValue=newValue;
            if ((newValue>=iMinimumValue) && (newValue<=iMaximumValue))
                {
                return ETrue;
                }
            }
        }
    return EFalse;
    }

EXPORT_C void CEikMfneNumber::SetUninitialised(TBool aUninitialised)
    {
    if (aUninitialised)
        iFlags |= EIsUninitialised;
    else
        iFlags &= ~EIsUninitialised;
    }

EXPORT_C TBool CEikMfneNumber::IsUninitialised() const
    {
    return iFlags & EIsUninitialised;
    }


EXPORT_C void CEikMfneNumber::RefreshDigitType( const CFont& aFont)
/**
Derive digit display type from locale information. This call sets the digit type based on current device settings.
It can be called after construction to make the field display correct numeral (if it is required.
Or can be called any number of times in response to Tlocale change. For dynamic update.
@publishedComponent
@since 2.0
@lib eikctl.lib
@param a locale structure which will be used to decide on the digit display.
@param aFont the font of the MFNE which owns this class
@post the next time the field is drawn it will display the number using digit type derived from the locale information.
*/
    {
    SetDigitType( AknTextUtils::NumericEditorDigitType(), aFont);
    }

EXPORT_C void CEikMfneNumber::SetDigitType(TDigitType aDigitType, const CFont& aFont)
/**
Set Numeral Type for displaying Numbers type for International digit support
@publishedComponent
@since 2.0
@lib eikctl.lib
@param aDigitType Set the numeral type for this field to display numbers in.
@param aFont the font of the MFNE which owns this class
@post the next time the field is drawn it will display the number using the supplied digit type.
*/
    {
    TInt value = Value();
    iDigitType = aDigitType;
    SetTextToValue(value, aFont);
    }

EXPORT_C TDigitType CEikMfneNumber::DigitType() const
/**
retrieve the current numeral type of the field
@publishedComponent
@since 2.0
@lib eikctl.lib
@return the current numeral display type.
*/
    {
    return iDigitType;
    }

// CEikMfneSymbol

CEikMfneSymbol::CEikMfneSymbol(TInt aNumSymbolicItems)
    :iNumSymbolicItems(aNumSymbolicItems),
     iCurrentSymbolicItem(0)
    {
    __DECLARE_NAME(_S("CEikMfneSymbol"));
    __ASSERT_ALWAYS(aNumSymbolicItems>1, Panic(EEikPanicMfneTooFewSymbolicItems));
    }

EXPORT_C CEikMfneSymbol::~CEikMfneSymbol()
    {
    if (iSymbolicItems)
        {
        for (TInt i=0; i<iNumSymbolicItems; ++i)
            delete iSymbolicItems[i];
        delete [] iSymbolicItems;
        }
    }

EXPORT_C CEikMfneSymbol* CEikMfneSymbol::NewL(TResourceReader& aResourceReader)
    {
    TInt numSymbols=aResourceReader.ReadUint8();
    CEikMfneSymbol* symbol=NewL(numSymbols);
    CleanupStack::PushL(symbol);
    for (TInt i=0; i<numSymbols; ++i)
        symbol->AddSymbolicItem(CItem::NewL(aResourceReader), i==0);
    CleanupStack::Pop();
    return symbol;
    }

EXPORT_C CEikMfneSymbol* CEikMfneSymbol::NewL(TInt aNumSymbolicItems)
    {
    CEikMfneSymbol* symbol=new(ELeave) CEikMfneSymbol(aNumSymbolicItems);
    CleanupStack::PushL(symbol);
    symbol->iSymbolicItems=new(ELeave) CItem*[aNumSymbolicItems];
    for (TInt i=0; i<aNumSymbolicItems; ++i)
        symbol->iSymbolicItems[i]=NULL;
    CleanupStack::Pop();
    return symbol;
    }

EXPORT_C void CEikMfneSymbol::AddSymbolicItem(CItem* aSymbolicItem, TBool aMakeCurrent)
    {
    __ASSERT_DEBUG(iSymbolicItems, Panic(EEikPanicMfneSymbolicItemArrayNotCreated));
    for (TInt i=0; i<iNumSymbolicItems; ++i)
        if (iSymbolicItems[i]==NULL)
            {
            iSymbolicItems[i]=aSymbolicItem;
            if (aMakeCurrent)
                SetCurrentSymbolicItem(i);
            return;
            }
#if defined(_DEBUG)
    Panic(EEikPanicMfneTooManySymbolicItemsAdded);
#endif
    }

EXPORT_C void CEikMfneSymbol::SetCurrentSymbolicItemToId(TInt aId)
    {
    for (TInt i=0; i<iNumSymbolicItems; ++i)
        if (iSymbolicItems[i]->iId==aId)
            {
            SetCurrentSymbolicItem(i);
            SetUninitialised(EFalse);
            return;
            }
#if defined(_DEBUG)
    Panic(EEikPanicMfneIdOfSymbolicItemNotFound);
#endif
    }

EXPORT_C TInt CEikMfneSymbol::IdOfCurrentSymbolicItem() const
    {
    return iSymbolicItems[CurrentSymbolicItem()]->iId;
    }

TInt CEikMfneSymbol::MaximumWidthInPixels(const CFont& aFont, TBool)
    {
    TInt maximumWidthInPixels=0;
    for (TInt i=0; i<iNumSymbolicItems; ++i)
        {
        TInt widthInPixels=aFont.TextWidthInPixels(*iSymbolicItems[i]->iText);
        if (maximumWidthInPixels<widthInPixels)
            maximumWidthInPixels=widthInPixels;
        }

    /* In the uninitialised state iMinimumWidthInPixels is set to the max with so that when focussed in the uninitialised state the
     * whole space is highlighted.  Note that when the state becomes not uninitialised iMinimumwidth... is set back to zero.
     */
    if (IsUninitialised())
        iMinimumWidthInPixels = maximumWidthInPixels + AdditionalWidthForHighlights(aFont);
    else
        iMinimumWidthInPixels = 0;
    return maximumWidthInPixels;
    }

TCoeInputCapabilities CEikMfneSymbol::InputCapabilities() const
    {
    TUint inputCapabilities=TCoeInputCapabilities::EWesternAlphabetic;
    for (TInt i=0; i<iNumSymbolicItems; ++i)
        {
        const TCharF keyToMatch=iSymbolicItems[i]->iKeyToMatch;
        if ((keyToMatch<TCharF('A')) || (keyToMatch>TCharF('Z'))) // a crude test, but it's probably sufficient
            {
            inputCapabilities=TCoeInputCapabilities::EAllText;
            }
        }
    return TCoeInputCapabilities(inputCapabilities);
    }

const TDesC& CEikMfneSymbol::Text() const
    {
    if (IsUninitialised())
        return KNullDesC();
    else
        return *iSymbolicItems[CurrentSymbolicItem()]->iText;
    }

TBool CEikMfneSymbol::IsEditable() const
    {
    return ETrue;
    }

CEikMfneField::THighlightType CEikMfneSymbol::HighlightType() const
    {
    return EInverseVideo;
    }

void CEikMfneSymbol::HandleKey(const CFont&, const TKeyEvent& aKeyEvent, TBool, TBool& aDataAltered, TInt& aHighlightIncrement)
    {
    TChar ch=aKeyEvent.iCode;
    switch (ch)
        {
        case EKeyLeftArrow:
        case EKeyRightArrow:
            HandleLeftOrRightArrow(ch, aDataAltered, aHighlightIncrement);
            break;
        case EKeyPowerOff:
        case EKeyPhoneEnd:
        case EKeyApplication:
            break;
        default:
            if (IsUninitialised())
                SetUninitialised(EFalse);
            else
                SetCurrentSymbolicItem((CurrentSymbolicItem()+1)%iNumSymbolicItems);
            aDataAltered=ETrue;
            break;
        }
    }

void CEikMfneSymbol::HandleDeHighlight(const CFont&, CEikonEnv&, TBool&, TBool&)
    {
    }



/*
 * The unilitialised flag uses the topmost bit of iCurrentSymbolicItem.  This is to preserve the size of the class for BC.
 * It's important that iCurrentSymbolic item is never negative though as it is an index that should not happen.  
 *
 */
const TInt KMfneSymbolUninitialisedBit = 0xf0000000;
EXPORT_C void CEikMfneSymbol::SetUninitialised(TBool aUninitialised)
    {
    if (aUninitialised)
        {
        iCurrentSymbolicItem |= KMfneSymbolUninitialisedBit;
        }
    else
        {
        iCurrentSymbolicItem &= ~KMfneSymbolUninitialisedBit;
        iMinimumWidthInPixels = 0;
        }
    }

EXPORT_C TBool CEikMfneSymbol::IsUninitialised() const
    {
    return iCurrentSymbolicItem & KMfneSymbolUninitialisedBit;
    }

TInt CEikMfneSymbol::CurrentSymbolicItem() const
    {
    return iCurrentSymbolicItem & ~KMfneSymbolUninitialisedBit;
    }

void CEikMfneSymbol::SetCurrentSymbolicItem(TInt aCurrentSymbolicItem)
    {
    __ASSERT_ALWAYS( aCurrentSymbolicItem >=0, Panic( EEikPanicMfneIdOfSymbolicItemNotFound ) ) ;
    TInt uninitialised = iCurrentSymbolicItem & KMfneSymbolUninitialisedBit;
    iCurrentSymbolicItem = aCurrentSymbolicItem | uninitialised;
    }

// CEikMfneSymbol::CItem

CEikMfneSymbol::CItem::CItem(TInt aId, TChar aKeyToMatch, HBufC* aText)
    :iId(aId),
     iKeyToMatch(aKeyToMatch),
     iText(aText)
    {
    __DECLARE_NAME(_S("CItem"));
    }

EXPORT_C CEikMfneSymbol::CItem::~CItem()
    {
    delete iText;
    }

EXPORT_C CEikMfneSymbol::CItem* CEikMfneSymbol::CItem::NewL(TResourceReader& aResourceReader)
    {
    TInt id=aResourceReader.ReadInt32();
    TChar keyToMatch=aResourceReader.ReadUint16();
    HBufC* text=aResourceReader.ReadHBufCL();
    CleanupStack::PushL(text);
    CItem* symbolicItem=NewL(id, keyToMatch, text);
    CleanupStack::Pop();
    return symbolicItem;
    }

EXPORT_C CEikMfneSymbol::CItem* CEikMfneSymbol::CItem::NewL(TInt aId, TChar aKeyToMatch, HBufC* aText)
    {
    return new(ELeave) CItem(aId, aKeyToMatch, aText);
    }

EXPORT_C void CEikMfneSymbol::CItem::SetText(HBufC* aText)
    {
    __ASSERT_DEBUG(iText==NULL, Panic(EEikPanicMfneSymbolicItemTextHasAlreadyBeenSet));
    iText=aText;
    }

//
// CEikMfne
//

// Enumerations use to implement the flag setter/getter methods used with CEikMfne::iFlags
enum TEikMfneFlagIndex
    {
    EConsumeUpAndDownKeysIndex = 0,
    ESkinningBackground,
    ESkinBackGroundControlContextSetByApi,
    ESuppressBackgroundDrawing,
    EUseOverrideColors
    };

EXPORT_C CEikMfne::CEikMfne()
    :CEikBorderedControl(TGulBorder(TGulBorder::ESingleGray)),
     iCurrentField(ENullIndex)
    {
    __DECLARE_NAME(_S("CEikMfne"));
    AKNTASHOOK_ADD( this, "CEikMfne" );
    }

EXPORT_C CEikMfne::~CEikMfne()
    {
    AKNTASHOOK_REMOVE();
    if (iFields)
        {
        if (IsFocused() && (iCurrentField!=ENullIndex) && (iFields[iCurrentField]->HighlightType()==CEikMfneField::ECursor))
            HideCursor();
        for (TInt i=0; i<iNumFields; ++i)
            delete iFields[i];
        delete [] iFields;
        }
    delete iExtension;
    }

EXPORT_C void CEikMfne::CreateFieldArrayL(TInt aNumFields)
    {
    __ASSERT_DEBUG(iFields==NULL, Panic(EEikPanicMfneFieldArrayAlreadyCreated));
    __ASSERT_DEBUG(aNumFields>0, Panic(EEikPanicMfneTooFewFields));
    iNumFields=aNumFields;
    iFields=new(ELeave) CEikMfneField*[aNumFields];
    for (TInt i=0; i<aNumFields; ++i)
        iFields[i]=NULL;
    // Set the flag that says background skin drawing will be done
    EvaluateSkinningBackground();
    CreateExtensionIfRequiredL();
    }
EXPORT_C void CEikMfne::ResetFieldArray()
    {
    if (iFields)
        {
        for (TInt i=0; i<iNumFields; ++i)
            delete iFields[i];
        delete [] iFields;
        iFields = NULL;
        iNumFields = 0;
        iCurrentField = ENullIndex;
        }   
    }

EXPORT_C void CEikMfne::AddField(CEikMfneField* aField)
    {
    __ASSERT_DEBUG(iFields, Panic(EEikPanicMfneFieldArrayNotCreated));
    for (TInt i=0; i<iNumFields; ++i)
        if (iFields[i]==NULL)
            {
            iFields[i]=aField;
            if ((iCurrentField==ENullIndex) && aField->IsEditable())
                iCurrentField=i;
            return;
            }
#if defined(_DEBUG)
    Panic(EEikPanicMfneTooManyFieldsAdded);
#endif
    }

EXPORT_C TMargins CEikMfne::BorderMargins() const
    {
    return iBorder.Margins();
    }

EXPORT_C TTime CEikMfne::ReadTime(TResourceReader& aResourceReader)
    {
    TInt second=aResourceReader.ReadUint8();
    TInt minute=aResourceReader.ReadUint8();
    TInt hour=aResourceReader.ReadUint8();
    return TTime(TDateTime(0, EJanuary, 0, hour, minute, second, 0));
    }

EXPORT_C TTime CEikMfne::ReadDate(TResourceReader& aResourceReader)
    {
    TInt day=aResourceReader.ReadUint8();
    TMonth month=(TMonth)aResourceReader.ReadUint8();
    TInt year=aResourceReader.ReadInt16();
    return TTime(TDateTime(year, month, day, 0, 0, 0, 0));
    }

EXPORT_C TTime CEikMfne::ReadTimeAndDate(TResourceReader& aResourceReader)
    {
    TInt second=aResourceReader.ReadUint8();
    TInt minute=aResourceReader.ReadUint8();
    TInt hour=aResourceReader.ReadUint8();
    TInt day=aResourceReader.ReadUint8();
    TMonth month=(TMonth)aResourceReader.ReadUint8();
    TInt year=aResourceReader.ReadInt16();
    return TTime(TDateTime(year, month, day, hour, minute, second, 0));
    }

EXPORT_C TTimeIntervalSeconds CEikMfne::ReadDuration(TResourceReader& aResourceReader)
    {
    TInt seconds=aResourceReader.ReadInt32();
    __ASSERT_ALWAYS(seconds>=0, Panic(EEikPanicMfneNegativeDuration));
    return TTimeIntervalSeconds(seconds);
    }

EXPORT_C TTimeIntervalSeconds CEikMfne::ReadTimeOffset(TResourceReader& aResourceReader)
    {
    TInt seconds=aResourceReader.ReadInt32();
    return TTimeIntervalSeconds(seconds);
    }

void CEikMfne::InvalidFieldAlert()
/**
Display alert to user, when input is not a valid number (too big or too small etc).
Current implementation is to play a sound alert.
@publishedComponent
@since 2.0
*/
    {
    CAknKeySoundSystem* soundPlayer = (static_cast<CAknAppUi*>(CEikonEnv::Static()->AppUi()))->KeySounds();
    if(soundPlayer)
        {
        soundPlayer->PlaySound(EAvkonSIDWarningTone); 
        }
    }

void CEikMfne::LeaveWithAlert(TInt /*aResourceId*/)
/**
This is to aid the old code in the derived classes which called LeaveWithInfoMsg().
Now they leave and play warning sound to indicate a problem/correction made by the editor.
@publishedComponent
@since 2.0
*/
    {
    InvalidFieldAlert();
    CBaActiveScheduler::LeaveNoAlert();
    }

EXPORT_C TTimeIntervalSeconds CEikMfne::Convert(const TTime& aTime)
    {
    TDateTime dateTime=aTime.DateTime();
    return TTimeIntervalSeconds(dateTime.Second()+(dateTime.Minute()*60)+(dateTime.Hour()*3600)+(dateTime.Day()*3600*24));
    }

EXPORT_C TTime CEikMfne::Convert(const TTimeIntervalSeconds& aTimeIntervalSeconds)
    {
    TInt timeIntervalSeconds=aTimeIntervalSeconds.Int();
    TInt second=timeIntervalSeconds%60;
    timeIntervalSeconds/=60;
    TInt minute=timeIntervalSeconds%60;
    timeIntervalSeconds/=60;
    TInt hour=timeIntervalSeconds%24;
    return TTime(TDateTime(0, EJanuary, 0, hour, minute, second, 0));
    }

EXPORT_C TKeyResponse CEikMfne::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
    {
    const TInt code=aKeyEvent.iCode;

    if ( !ConsumesUpAndDownKeys() && (code==EKeyDownArrow || code==EKeyUpArrow))
        return EKeyWasNotConsumed;

    if ((aType==EEventKey) && (iCurrentField!=ENullIndex) && 
        ( aKeyEvent.iRepeats == 0 || code == EKeyLeftArrow || 
            code == EKeyRightArrow || code == EKeyDownArrow || code == EKeyUpArrow ) )
        {
        iExtension->iHighlightAll = EFalse;
        const CFont& font=*Font();
        CEikMfneField::THighlightType oldHighlightTypeOfOldCurrentField=iFields[iCurrentField]->HighlightType();
        TInt oldWidthInPixelsOfOldCurrentField=iFields[iCurrentField]->WidthInPixels(font);
        TBool dataAltered=EFalse;
        TInt highlightIncrement=0;
        iFields[iCurrentField]->HandleKey(font, aKeyEvent, iNumFields==1, dataAltered, highlightIncrement);
        TInt newCurrentField;
        for (TInt i=iCurrentField+highlightIncrement; ; i+=highlightIncrement)
            {
            if (i<0)
                i=iNumFields-1;
            else if (i>=iNumFields)
                i=0;
            if (iFields[i]->IsEditable())
                {
                newCurrentField=i;
                break;
                }
            }
        TBool error=EFalse;
        HandleInteraction(highlightIncrement, newCurrentField, oldWidthInPixelsOfOldCurrentField, oldHighlightTypeOfOldCurrentField, dataAltered, error);
        ReportUpdate();
        }
    return EKeyWasConsumed;
    }

EXPORT_C void CEikMfne::PrepareForFocusLossL()
    {
    if (iCurrentField!=ENullIndex)
        {
        TBool dataAltered=EFalse;
        TBool error=EFalse;
        HandleInteraction(ETrue, iCurrentField, iFields[iCurrentField]->WidthInPixels(*Font()), iFields[iCurrentField]->HighlightType(), dataAltered, error);
        ReportUpdate();
        }
    }

EXPORT_C TSize CEikMfne::MinimumSize()
    {
    return MfneSize(ETrue);
    }

EXPORT_C TCoeInputCapabilities CEikMfne::InputCapabilities() const
    {
#ifdef RD_SCALABLE_UI_V2
    TCoeInputCapabilities inputCapabilities(
        TCoeInputCapabilities::ENavigation, iExtension, NULL );
#else       
    TCoeInputCapabilities inputCapabilities(
        TCoeInputCapabilities::ENavigation );
#endif // RD_SCALABLE_UI_V2     
    
    for (TInt i=0; i<iNumFields; ++i)
        {
        inputCapabilities.MergeWith(iFields[i]->InputCapabilities());
        }

    //inputCapabilities.SetObjectProvider(const_cast<CEikMfne*>(this));
    if ( iExtension )
        {
        inputCapabilities.SetObjectProvider(
            iExtension->iExtendedInputCapabilitiesProvider );
        }
        
    return inputCapabilities;
    }

EXPORT_C void CEikMfne::FocusChanged(TDrawNow aDrawNow)
    {
    if (iCurrentField==ENullIndex)
        return;
    if ( IsFocused() && iExtension && !iExtension->iDisablePenInput && 
        iExtension->iLaunchPenInputAutomatic )
        {
        TRAP_IGNORE( LaunchPenInputL() );
        }
    if (iFields[iCurrentField]->HighlightType()==CEikMfneField::ECursor)
        {
        if (IsFocused())
            DrawCursor();
        else
            HideCursor();
        return;
        }
        
    if ( aDrawNow  && !(iExtension && iExtension->iDisablePenInput) )
        {
        ActivateGc();
        if ( CAknEnv::Static()->TransparencyEnabled() )
            {
            TRect ctrlRect = Rect();
        
            if ( !IsBackedUp() )
                {
                Window().Invalidate( ctrlRect );
                Window().BeginRedraw( ctrlRect );
                }
            // Just draw all, sacrifice perf a bit for vast simplicity
            DrawRange( PreparedGc(), -1, iNumFields );
            SystemGc().DiscardFont();
            Window().EndRedraw();
            
            }
        else
            {
            if (iAlignment == ELayoutAlignRight || iAlignment == ELayoutAlignCenter)
                { // need to redraw whole editor because right align
                DrawRange( PreparedGc(), -1, iNumFields );
                }
            else
                { // updating current field is enough
                DrawRange(PreparedGc(), iCurrentField,iCurrentField);    
                }
            SystemGc().DiscardFont();
            }
  
        DeactivateGc();
        }
    }

EXPORT_C void CEikMfne::HandleInteraction(TBool aHandleDeHighlight, TInt aNewCurrentField, TInt aOldWidthInPixelsOfOldCurrentField,
                                CEikMfneField::THighlightType aOldHighlightTypeOfOldCurrentField, TBool& aDataAltered, TBool& aError)
    {
    const CFont& font=*Font();
    TBool drawAllFields = ETrue;
    if (aHandleDeHighlight)
        {
        iFields[iCurrentField]->HandleDeHighlight(font, *iEikonEnv, aDataAltered, aError);
        iExtension->iValidateValueCallBack.CallBack();
        if (aError)
            aNewCurrentField=iCurrentField;
        else
            FieldIsAboutToBeDeHighlighted(iFields[iCurrentField], drawAllFields);
        }
    TInt oldCurrentField=iCurrentField;
    iCurrentField=aNewCurrentField;

    if ( aDataAltered )
        {
        ReportEventL(MCoeControlObserver::EEventStateChanged);  
        }
    
    CEikMfneField::THighlightType newHighlightTypeOfOldCurrentField=iFields[oldCurrentField]->HighlightType();
    CEikMfneField::THighlightType highlightTypeOfCurrentField=iFields[iCurrentField]->HighlightType();

    ActivateGc();
    if ( CAknEnv::Static()->TransparencyEnabled() )
        {
        if ( !IsBackedUp() )
            {
            TRect ctrlRect = Rect();
            Window().Invalidate( ctrlRect );
            Window().BeginRedraw( ctrlRect );
            }
        
        // Just draw all, sacrifice perf a bit for vast simplicity
        drawAllFields = ETrue;
        }

    SystemGc().Reset();
    CWindowGc& gc=PreparedGc();

    if (drawAllFields ||iAlignment == ELayoutAlignRight || iAlignment == ELayoutAlignCenter) // draw all fields in case of right align
        DrawRange(gc, -1, iNumFields);
    else
        {
        TInt newWidthInPixelsOfOldCurrentField=iFields[oldCurrentField]->WidthInPixels(font);
        TInt firstFieldToDraw=(aDataAltered ||
                               ((iCurrentField!=oldCurrentField) && (aOldHighlightTypeOfOldCurrentField==CEikMfneField::EInverseVideo)) ||
                               ((iCurrentField==oldCurrentField) && (aOldHighlightTypeOfOldCurrentField!=newHighlightTypeOfOldCurrentField)))?
                                                                    oldCurrentField: oldCurrentField+1;
        TInt lastFieldToDraw=(newWidthInPixelsOfOldCurrentField!=aOldWidthInPixelsOfOldCurrentField)? iNumFields: oldCurrentField;
        DrawRange(gc, firstFieldToDraw, lastFieldToDraw);
        if ((iCurrentField!=oldCurrentField) && ((iCurrentField<firstFieldToDraw) || (iCurrentField>lastFieldToDraw)))
            {
            __ASSERT_DEBUG(highlightTypeOfCurrentField==CEikMfneField::EInverseVideo, Panic(EEikPanicMfneInverseVideoHighlightTypeExpected));
            DrawRange(gc, iCurrentField, iCurrentField);
            }
        }
    if ( (aOldHighlightTypeOfOldCurrentField==CEikMfneField::ECursor) && 
        ((iCurrentField!=oldCurrentField) || 
        (newHighlightTypeOfOldCurrentField!=CEikMfneField::ECursor)))
        {
        __ASSERT_DEBUG(highlightTypeOfCurrentField!=CEikMfneField::ECursor, Panic(EEikPanicMfneBadCursorState1));
        HideCursor();
        }
    if ( (highlightTypeOfCurrentField==CEikMfneField::ECursor) && 
        ((aOldHighlightTypeOfOldCurrentField!=CEikMfneField::ECursor) || aDataAltered))
        {
        __ASSERT_DEBUG(iCurrentField==oldCurrentField, Panic(EEikPanicMfneBadCursorState2));
        DrawCursor();
        }
    gc.DiscardFont();
    if ( CAknEnv::Static()->TransparencyEnabled() && !IsBackedUp() )
        {
        Window().EndRedraw();
        }
    DeactivateGc();
    }

EXPORT_C void CEikMfne::FieldIsAboutToBeDeHighlighted(CEikMfneField*, TBool&)
    {
    }

EXPORT_C void CEikMfne::DrawNowAndLeaveWithTimeDateFormatInfoMsgL(TInt /*aResourceId*/, const TTime& /*aTimeDate*/) const
    {
    CEikMfne::InvalidFieldAlert();
    DrawNow();
//  AVKON does not show info messages, removed because they take up lots of time and space
    CBaActiveScheduler::LeaveNoAlert();
    }

EXPORT_C CEikMfneField* CEikMfne::Field(TInt aField) const
    {
    return (aField<0 || aField>=iNumFields)?NULL:iFields[aField];
    }

EXPORT_C void CEikMfne::SetMfneAlignment(TInt aAlignment)
    {
    if( !iExtension )
        {
        TRAPD( err, CreateExtensionIfRequiredL() );
        if ( err != KErrNone )
            {
            return;
            }
        }
    if ( aAlignment >= ELayoutAlignNone && iExtension )
        {
        iAlignment = aAlignment;
        TUint capabilities = iExtension->
            iExtendedInputCapabilities->Capabilities();
        capabilities &= 
            ~( CAknExtendedInputCapabilities::KAknEditorAlignMask );
        switch( iAlignment )
            {
            case ELayoutAlignCenter:
                capabilities |= 
                    CAknExtendedInputCapabilities::EInputEditorAlignCenter;
                break;
            case ELayoutAlignLeft:
                capabilities |= 
                    CAknExtendedInputCapabilities::EInputEditorAlignLeft;
                break;
            case ELayoutAlignRight:
                capabilities |=
                    CAknExtendedInputCapabilities::EInputEditorAlignRight;
                break;
            case ELayoutAlignBidi:
                capabilities |=
                    CAknExtendedInputCapabilities::EInputEditorAlignBidi;
                break;
            default:
                break;
            }
        iExtension->iExtendedInputCapabilities->SetCapabilities( 
            capabilities );
        }
        
    MfneSize();
    }

EXPORT_C void CEikMfne::SetUpAndDownKeysConsumed(TBool aConsume)
    {
    iFlags.Assign( EConsumeUpAndDownKeysIndex, aConsume );
    }
    
EXPORT_C void CEikMfne::SetSuppressBackgroundDrawing( TBool aSuppress )
    {
    iFlags.Assign( ESuppressBackgroundDrawing, aSuppress );
    }
    
EXPORT_C TInt CEikMfne::SetFeature( TInt aFeatureId, TInt aFeatureParam )
    {
    TInt ret = KErrNone;
    
    if ( !SupportsFeature( aFeatureId ) )
        {
        ret = KErrNotSupported;
        }
    else
        {
        switch ( aFeatureId )
            {
            case EClipGcToRect:
                if ( iExtension )
                    {
                    iExtension->iClipGcToRect = aFeatureParam;
                    }
                else
                    {
                    ret = KErrGeneral;
                    }
                break;
                
            case EDisablePenInput:
                if ( iExtension )
                    {
                    iExtension->iDisablePenInput = aFeatureParam;
                    iExtension->iFingerSupport = !( iExtension->iDisablePenInput != 0 );
                    iExtension->iHighlightAll = EFalse;
                    }
                else
                    {
                    ret = KErrGeneral;
                    }
                break;
            case EFingerSupport:
                if ( iExtension )
                    {
                    iExtension->iFingerSupport = ( TBool )( aFeatureParam );
                    iExtension->iDisablePenInput = !( iExtension->iFingerSupport );                    
                    iExtension->iFingerParam = aFeatureParam; 
                    iExtension->iHighlightAll = ( iExtension->iFingerSupport &&
                        aFeatureParam == EnableWithAllHighlight );                  
                    }
                else
                    {
                    ret = KErrGeneral;
                    }
                break;
            case ELaunchPenInputAutomatic:
                if ( iExtension )
                    {
                    iExtension->iLaunchPenInputAutomatic = aFeatureParam;                    
                    }
                else
                    {
                    ret = KErrGeneral;
                    }
                break; 
            case EPartialScreenInput:
                if ( iExtension )
                    {
                    iExtension->iPartialScreenInput = aFeatureParam;
                    TUint caps( iExtension->iExtendedInputCapabilities->Capabilities() );
                    if ( aFeatureParam )
                        {
                        caps |= CAknExtendedInputCapabilities::EInputEditorPartialScreen;
                        }
                    else
                        {
                        caps &= ~CAknExtendedInputCapabilities::EInputEditorPartialScreen;
                        }
                    iExtension->iExtendedInputCapabilities->SetCapabilities( caps );
                    }
                else
                    {
                    ret = KErrGeneral;
                    }
                break;
            default:
                ret = KErrNotSupported;
                break;
            }
        }
    
    return ret;
    }

EXPORT_C TInt CEikMfne::GetFeature( TInt aFeatureId, TInt& aFeatureParam ) const
    {
    TInt ret = KErrNone;
    
    if ( !SupportsFeature( aFeatureId ) )
        {
        ret = KErrNotSupported;
        }
    else
        {
        switch ( aFeatureId )
            {
            case EClipGcToRect:
                if ( iExtension )
                    {
                    aFeatureParam = iExtension->iClipGcToRect;
                    }
                else
                    {
                    ret = KErrGeneral;
                    }
                break;
                
            case EDisablePenInput:
                if ( iExtension )
                    {
                    aFeatureParam = iExtension->iDisablePenInput;
                    }
                else
                    {
                    ret = KErrGeneral;
                    }
                break;
            case EFingerSupport:
                if ( iExtension )
                    {
                    aFeatureParam = iExtension->iFingerParam;
                    }
                else
                    {
                    ret = KErrGeneral;
                    }
                break;
            case ELaunchPenInputAutomatic:
                if ( iExtension )
                    {
                    aFeatureParam = iExtension->iLaunchPenInputAutomatic;
                    }
                else
                    {
                    ret = KErrGeneral;
                    }
                break;
            case EPartialScreenInput:
                if ( iExtension )
                    {
                    aFeatureParam = iExtension->iPartialScreenInput;
                    }
                else
                    {
                    ret = KErrGeneral;
                    }
                break;
            default:
                ret = KErrNotSupported;
                break;
            }
        }
    
    return ret;
    }

EXPORT_C TBool CEikMfne::SupportsFeature( TInt aFeatureId ) const
    {
    // This is done so that there is an option of leaving out
    // a feature instead of using the enum TFeatureId, although
    // for simplified BC that will probably never be done.
    const TInt supportedFeatures[] = 
        {
        EClipGcToRect,
        EDisablePenInput,
        EFingerSupport,
        ELaunchPenInputAutomatic,
        EPartialScreenInput
        };
        
    TBool ret = EFalse;
    
    for ( TInt i = 0; i < sizeof( supportedFeatures ) / sizeof( TInt ); ++i )
        {
        if ( supportedFeatures[i] == aFeatureId )
            {
            ret = ETrue;
            break;
            }
        }
         
    return ret;   
    }
    
void CEikMfne::HighlightField( TInt aFieldPosition )
    {
    TBool dataAltered = ETrue;
    TBool error = EFalse;
    const CFont& font=*Font();
    HandleInteraction(ETrue, aFieldPosition, iFields[iCurrentField]->WidthInPixels(font), iFields[iCurrentField]->HighlightType(), dataAltered, error);
    }

EXPORT_C const CFont* CEikMfne::Font() const
    {
    if (iFont)
        {
        return iFont;
        }
    else
        {
        return AknLayoutUtils::FontFromId( EAknLogicalFontPrimaryFont );
        }
    }

EXPORT_C void CEikMfne::SetFont(const CFont* aFont)
    {
    TBool fontChanged(iFont==aFont);
    iFont = aFont;
    if (fontChanged)
        MfneSize();
    }

EXPORT_C void CEikMfne::SetSkinBackgroundControlContextL( MAknsControlContext* aControlContext )
    {
    CreateExtensionIfRequiredL();
    if ( iExtension )
        {
        iExtension->iExternalSkinControlContext = aControlContext;
        iFlags.Set(ESkinBackGroundControlContextSetByApi);
        }
    }

EXPORT_C TSize CEikMfne::MfneSize() const
    {
    return ((CEikMfne*)this)->MfneSize(EFalse); // cast away the const-ness
    }

EXPORT_C TSize CEikMfne::MfneSize(TBool aShrinkToMinimumSize)
    {
    const CFont& font=*Font();
    TSize size=iBorder.SizeDelta(); // Shrink to border first

    size.iHeight=Rect().Height(); // Do not change height
    iBorder.SizeDelta(); // Shrink to border first

    TInt leftHighlightExtension;
    TInt rightHighlightExtension;
    TAknTextDecorationMetrics decoration( &font );
    decoration.GetLeftAndRightMargins( leftHighlightExtension, rightHighlightExtension);

    size.iWidth += leftHighlightExtension + rightHighlightExtension;

    if( iFields )
        {
        for (TInt i=0; i<iNumFields; ++i)
            size.iWidth+=iFields[i]->MaximumWidthInPixels(font, aShrinkToMinimumSize);
        }

    TRect rect = Rect();
    switch ( iAlignment )
        {
        case ELayoutAlignCenter:
            {
            TInt fieldXPosition = rect.iTl.iX + (rect.Width() - size.iWidth) / 2;
            SetExtent(TPoint(fieldXPosition, rect.iTl.iY), TSize(size));
            }
            break;
        case ELayoutAlignRight:
            {
            TInt fieldXPosition = rect.iTl.iX + (rect.Width() - size.iWidth);
            SetExtent(TPoint(fieldXPosition, rect.iTl.iY), TSize(size));
            }
            break;
        case ELayoutAlignLeft: // Left alignment is default
        case ELayoutAlignBidi: // Bidi should be ignored, so it's the same as default
        default:
            {
            iSize=size;
            }
            break;
        }

    return iSize;
    }

EXPORT_C void CEikMfne::Draw(const TRect& /*aRect*/) const
    {
    CWindowGc& gc=PreparedGc();
    TRect rect=Rect();

    // Inhibit border if skinning
    if ( !SkinningBackground() )
        iBorder.Draw(gc, rect);

    DrawRange( gc, -1, iNumFields, ETrue );
    gc.DiscardFont(); // this is not nice if there are eg. child controls to draw..

    }

EXPORT_C void* CEikMfne::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CEikMfne::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    CCoeControl::HandlePointerEventL(aPointerEvent);

    if ((aPointerEvent.iType==TPointerEvent::EButton1Down) || (aPointerEvent.iType==TPointerEvent::EDrag))
        {
        const CFont& font=*Font();
        TInt newField=ENullIndex;
        TMargins borderMargins=iBorder.Margins();
        
        TInt leftHighlightExtension;
        TInt rightHighlightExtension;
        TAknTextDecorationMetrics decoration( &font );
        decoration.GetLeftAndRightMargins( leftHighlightExtension, rightHighlightExtension );
        
        TInt leftPositionOfThisField = 
            iPosition.iX + borderMargins.iLeft + EGapLeftOfFirstField + leftHighlightExtension;
        
        // No need to do anything in the block below in case of left align
        if ( iAlignment == ELayoutAlignCenter ||
             iAlignment == ELayoutAlignRight )
            {
            TInt mfneWidth( 0 );
            for ( TInt i=0; i < iNumFields; ++i )
                {
                mfneWidth += iFields[i]->WidthInPixels( font );
                }
            
            if ( iAlignment == ELayoutAlignCenter )
                {
                leftPositionOfThisField += ( iSize.iWidth - mfneWidth ) / 2;
                }
            else if ( iAlignment == ELayoutAlignRight )
                {
                leftPositionOfThisField += ( iSize.iWidth - mfneWidth );
                }
            }
        
        // TInt leftPositionOfNewField=0; // dummy initialization to prevent compiler warning (NOT USED)
        TInt rightPositionOfNewField=0; // dummy initialization to prevent compiler warning
        for (TInt i=0; i<iNumFields; ++i)
            {
            TInt widthOfThisFieldInPixels=iFields[i]->WidthInPixels(font);
            if (iFields[i]->IsEditable())
                {
                TInt rightPositionOfThisField=(leftPositionOfThisField+widthOfThisFieldInPixels)-1;
                if (rightPositionOfThisField<aPointerEvent.iPosition.iX)
                    {
                    newField=i;
                    //leftPositionOfNewField=leftPositionOfThisField;
                    rightPositionOfNewField=rightPositionOfThisField;
                    }
                else
                    {
                    if ((newField==ENullIndex) || (leftPositionOfThisField-aPointerEvent.iPosition.iX<aPointerEvent.iPosition.iX-rightPositionOfNewField))
                        {
                        newField=i;
                        // leftPositionOfNewField and rightPositionOfNewField do not need to be set as they are not going to be used again
                        }
                    break;
                    }
                }
            leftPositionOfThisField+=widthOfThisFieldInPixels;
            }
        if (newField==ENullIndex)
            newField=iCurrentField;
        if ( aPointerEvent.iType == TPointerEvent::EButton1Down )
            {
            iExtension->iTwiceTap = ( iExtension->iFingerSupport ? ETrue : 
                newField == iCurrentField );            
            }

        if (iExtension && aPointerEvent.iType == TPointerEvent::EButton1Down)
            {
            // Edit feedback on down event in current field, 
            // Edit feedback when changing fields
            TTouchLogicalFeedback feedback = 
                ( iExtension->iTwiceTap ? ETouchFeedbackEditor : ETouchFeedbackEditor );
            iExtension->iFeedback->InstantFeedback( this, feedback );
            }
        TBool createPopoutIfRequired=((newField==iCurrentField) && aPointerEvent.iType==TPointerEvent::EButton1Down && IsFocused());
        TBool dataAltered=EFalse;
        TBool error=EFalse;
        HandleInteraction(ETrue, newField, iFields[iCurrentField]->WidthInPixels(font), iFields[iCurrentField]->HighlightType(), dataAltered, error);
        if (createPopoutIfRequired)
            CreatePopoutIfRequiredL();
        
        ReportEventL( MCoeControlObserver::EEventStateChanged );
        ReportUpdate();
        }
    else if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
        {
        if ( iExtension && !iExtension->iDisablePenInput && iExtension->iTwiceTap )
            {
            iExtension->iFeedback->InstantFeedback( this,
                ETouchFeedbackEditor,
                ETouchFeedbackVibra,
                aPointerEvent );
            LaunchPenInputL();
            }
        }
    }
    
EXPORT_C TTypeUid::Ptr CEikMfne::MopSupplyObject( TTypeUid aId )
    {
    if ( aId.iUid == CAknExtendedInputCapabilities::ETypeId && iExtension )
        {
        return aId.MakePtr( iExtension->iExtendedInputCapabilities );
        }
    
    return CCoeControl::MopSupplyObject( aId );
    }

EXPORT_C void CEikMfne::CreatePopoutIfRequiredL()
    {
    // does nothing
    }

// ----------------------------------------------------------------------------
// Draws the specified range of fields.
// ----------------------------------------------------------------------------
//
void CEikMfne::DrawRange( CWindowGc& aGc,
                          TInt aFirstField,
                          TInt aLastField,
                          TBool aSkipBackgroundDrawer ) const
    {
    const MCoeControlBackground* backgroundDrawer = FindBackground();

    TInt leftHighlightExtension;
    TInt rightHighlightExtension;

    TInt topHighlightExtension;
    TInt bottomHighlightExtension;
    TAknTextDecorationMetrics decoration( Font() );
    decoration.GetTopAndBottomMargins( topHighlightExtension, bottomHighlightExtension);
    decoration.GetLeftAndRightMargins( leftHighlightExtension, rightHighlightExtension);

    // Some values that will be needed for Skins.  These will behave when not skinned, etc..
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* edCc = SkinBackgroundControlContext();

    TInt skinDrawFlags = KAknsDrawParamDefault;
    if ( CAknEnv::Static()->TransparencyEnabled() )
        {
        skinDrawFlags = KAknsDrawParamNoClearUnderImage;
        }

    // N.B. a value of iNumFields for aFirstField or aLastField is permitted, this means draw the space after the last field, and similarly
    // a value of -1 is permitted which means draw the space before the first field
    __ASSERT_DEBUG((aFirstField>=-1) && (aFirstField<=iNumFields) && (aLastField>=-1) && (aLastField<=iNumFields), Panic(EEikPanicMfneBadRangeToDraw));
    // N.B. aLastField is permitted to be less than aFirstField, in which case nothing will be drawn
    if (aFirstField<=aLastField)
        {
        TBool drawtrailingSpace=EFalse;
        if (aLastField==iNumFields)
            {
            if (iAlignment != ELayoutAlignRight)
                drawtrailingSpace=ETrue;
            --aLastField;
            }
        TMargins borderMargins=iBorder.Margins();
        
        TInt alignLeftOffset = VerticalOffsetForMfnePosition();
        const CFont& font=*Font();
        
        TBool clipGcToRect( EFalse );
        
        if ( iExtension )
            {
            clipGcToRect = iExtension->iClipGcToRect;
            }
                
        if (iAlignment == ELayoutAlignRight)
            {
            alignLeftOffset = iSize.iWidth-VerticalOffsetForMfnePosition();
            for (TInt i = 0; i <= aLastField;i++ )
                alignLeftOffset -= iFields[i]->WidthInPixels(font);
            
            if (alignLeftOffset < 0 && !clipGcToRect )
                alignLeftOffset = 0; // fields are not goin to fit anyway.
            }
        if (iAlignment == ELayoutAlignCenter)
            {
            alignLeftOffset = iSize.iWidth-VerticalOffsetForMfnePosition();
            for (TInt i = 0; i <= aLastField;i++ )
                alignLeftOffset -= iFields[i]->WidthInPixels(font);
            
            if (alignLeftOffset < 0 && !clipGcToRect )
                alignLeftOffset = 0; // fields are not goin to fit anyway.
            alignLeftOffset /= 2;
            }
        
        const TPoint topLeftOfMfne(iPosition.iX+borderMargins.iLeft, iPosition.iY+borderMargins.iTop);
        TPoint topLeftOfField(topLeftOfMfne);
        topLeftOfField.iX += alignLeftOffset;
		
        TInt posX = topLeftOfField.iX; 
        TRect controlRect = Rect();
        posX += leftHighlightExtension;
        for (TInt i = 0; i <= aLastField;i++ )
            {
            posX += iFields[i]->WidthInPixels(font); 
            }
        if (posX < controlRect.iBr.iX )
            {
            topLeftOfField.iX+= leftHighlightExtension;
            }

        TInt textHeight=font.HeightInPixels();
    
        if (aFirstField==-1)
            {
            SetGcToNormalVideo(aGc);
            // Clear the area between the mfne left border and the first field of the mfne
            TRect clearRect( topLeftOfMfne, TSize( (topLeftOfField.iX - topLeftOfMfne.iX), Rect().Height() ) );

            TBool skinnedDraw = EFalse;

            if ( !iFlags[ESuppressBackgroundDrawing] )
                {
                if ( backgroundDrawer )
                    {
                    if ( !aSkipBackgroundDrawer )
                        {
                        backgroundDrawer->Draw( aGc, *this, clearRect );
                        }

                    skinnedDraw = ETrue;
                    }
                else if ( SkinningBackground() && !iFlags[EUseOverrideColors] )
                    {
                    skinnedDraw = AknsDrawUtils::Background( 
                        skin, edCc, this, aGc, clearRect, skinDrawFlags );
                    }
                if ( !skinnedDraw ) // legacy code ( rect construction move to above)
                    {
                    aGc.Clear( clearRect );
                    }
                }

            ++aFirstField;
            }
        //if there is one field with text, whole MFNE editor should 
        //be highlighted when highlight all feature is enabled.
        TBool isEmpty( ETrue );
        for ( TInt i( 0 ); i< aLastField; i++ )
            {
            if ( iFields[i]->FieldText().Length() > 0 )
                {
                isEmpty = EFalse;
                break;
                }
            }       
        TBool focused = IsFocused();
        for (TInt i=0; i<=aLastField; ++i)
            {
            if (i>=aFirstField)
                {
                if (focused && ( iExtension->iHighlightAll || ( i == iCurrentField 
                    && iFields[i]->HighlightType() == CEikMfneField::EInverseVideo
                    && iFields[i]->FieldText().Length() > 0 ) ) && !isEmpty )
                    {
                    // Currently no skin effect for the highlighted field drawing
                    SetGcToInverseVideo(aGc);
                    }
                else 
                    {
                    if (IsDimmed())
                        SetGcToDimmedVideo(aGc);
                    else
                        SetGcToNormalVideo(aGc);

                    // Note!! This is taking responsibility away from the CEikMfne Field for drawing
                    // Skin background is drawn for the fields here
                    if( SkinningBackground() && !iFlags[EUseOverrideColors] )
                        {
                        // Note that in case EUseOverrideColors is up, there is no need
                        // to clear here, as the ENullBrush below is skipped and therefore
                        // the field will draw its own background with the overridden color
                        if ( !iFlags[ESuppressBackgroundDrawing] )
                            {
                            TRect clearRect(
                                TPoint( topLeftOfField.iX, topLeftOfMfne.iY ),
                                TPoint( 
                                        topLeftOfField.iX +(iFields[i]->WidthInPixels(font)), 
                                        topLeftOfMfne.iY + Rect().Height() 
                                        )  );

                            if ( backgroundDrawer )
                                {
                                if ( !aSkipBackgroundDrawer )
                                    {
                                    backgroundDrawer->Draw( aGc, *this, clearRect );
                                    }
                                }
                            else
							    {
                                AknsDrawUtils::Background( 
                                    skin, edCc, this, aGc, clearRect, skinDrawFlags );
                                }
                            }

                        // Set up null brush GC here for the upcoming draw
                        aGc.SetBrushStyle(CGraphicsContext::ENullBrush);
                        }
                    }
                // This draw must only draw the text with a null brush or draw block highlight 
                iFields[i]->Draw(aGc, font, topLeftOfField);
                }
            topLeftOfField.iX+=iFields[i]->WidthInPixels(font); // Increment field Position
            }
        if (drawtrailingSpace)
            {
            SetGcToNormalVideo(aGc);
            if ( !iFlags[ESuppressBackgroundDrawing] )
                {
                TInt width=0;
                if (iAlignment == ELayoutAlignCenter)
                {
                width = iSize.iWidth-VerticalOffsetForMfnePosition();
                for(TInt i=0;i<iNumFields;i++)
                    width -= iFields[i]->WidthInPixels(font);
                if (width < 0) width = 0;
                width /= 2;
                }
                
                TRect clearRect;
                if ( CAknEnv::Static()->TransparencyEnabled() )
                    {
                    clearRect = TRect( topLeftOfField,
                                    TPoint( iPosition.iX + iSize.iWidth, topLeftOfMfne.iY+Rect().Height() ));
                    }
                else
                    {
                    clearRect = TRect( topLeftOfField,
                                    TPoint(iPosition.iX + width + iSize.iWidth, topLeftOfMfne.iY+Rect().Height() ));
                    }

                TBool skinnedDraw = EFalse;

                if ( backgroundDrawer )
                    {
                    if ( !aSkipBackgroundDrawer )
                        {
                        backgroundDrawer->Draw( aGc, *this, clearRect );
                        }

                    skinnedDraw = ETrue;
                    }
                else if ( SkinningBackground() && !iFlags[EUseOverrideColors] )
                    {
                    skinnedDraw = AknsDrawUtils::Background( 
                        skin, edCc, this, aGc, clearRect, skinDrawFlags );
                    }
                if ( !skinnedDraw )
                    {
                    aGc.Clear( clearRect );
                    }
                }
            }
        }
    }

CWindowGc& CEikMfne::PreparedGc() const
    {
    CWindowGc& gc=SystemGc();
    gc.SetBrushStyle(CWindowGc::ESolidBrush);
    gc.UseFont(Font()); // The font must be discarded also -> always when using PreparedGc(), 
    
    if ( iExtension && iExtension->iClipGcToRect )
        {
        gc.SetClippingRect( Rect() );
        }
    
    return gc;          // and finishing drawing, gc.DiscardFont must be called
    }

void CEikMfne::SetGcToNormalVideo(CWindowGc& aGc) const
    {
    TRgb textColor = AKN_LAF_COLOR(215);
    TRgb bgColor = iEikonEnv->ControlColor(EColorControlBackground,*this);

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    if ( iFlags[EUseOverrideColors] )
        {
        textColor = iEikonEnv->ControlColor( EColorControlText, *this );
        }
    else if ( skin && iExtension )
       {
       AknsUtils::GetCachedColor(skin, textColor, KAknsIIDQsnTextColors, iExtension->iAknSkinColorIndex); 
       AknsUtils::GetCachedColor(skin, bgColor, KAknsIIDQsnTextColors, iExtension->iSkinIdForTextBackgroundColor);         
       }
        
    aGc.SetPenColor(textColor);  // Text color
    aGc.SetBrushColor(bgColor); 
    }

void CEikMfne::SetGcToInverseVideo(CWindowGc& aGc) const
    {
    TRgb hightext = AKN_LAF_COLOR(0); // Hightlighted text color   // AVKON LAF
    TRgb highcolor = AKN_LAF_COLOR(210); // Highlight color  // AVKON LAF

    if ( iFlags[EUseOverrideColors] )
        {
        hightext = iEikonEnv->ControlColor( EColorControlHighlightText, *this );
        highcolor = iEikonEnv->ControlColor( EColorControlHighlightBackground, *this );
        }
    else
        {
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        AknsUtils::GetCachedColor(skin, hightext, KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG24);
        AknsUtils::GetCachedColor(skin, highcolor, KAknsIIDQsnHighlightColors, EAknsCIQsnHighlightColorsCG2);
        }

    aGc.SetPenColor(hightext); 
    aGc.SetBrushColor(highcolor); 

    // Ensure highlight in inverse video
    aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    }

void CEikMfne::SetGcToDimmedVideo(CWindowGc& aGc) const
    {
    if ( iFlags[EUseOverrideColors] )
        {
        aGc.SetPenColor(iEikonEnv->ControlColor(EColorControlDimmedText,*this)); //KEikMfneDimmedColor);
        aGc.SetBrushColor(iEikonEnv->ControlColor(EColorControlBackground,*this)); //KEikMfneBackgroundColor);
        }
    else
        {
        SetGcToNormalVideo(aGc);
        }
    }

void CEikMfne::GetCursorInfo( TPoint& aPos, TInt& aHeight, TInt& aWidth, 
    TInt& aAscent )
    {
    const CFont& font=*Font();
    const CAknLayoutFont* layoutFont = CAknLayoutFont::AsCAknLayoutFontOrNull( &font );
    if ( layoutFont )
        {
        TInt topMargin;
        TInt bottomMargin;
        TAknTextDecorationMetrics metrics = layoutFont->TextDecorationMetrics();
        metrics.GetTopAndBottomMargins( topMargin, bottomMargin );
        aHeight = layoutFont->TextPaneHeight() + topMargin + bottomMargin;
        aWidth  = metrics.CursorWidth();
        aAscent = layoutFont->TextPaneHeight();
        // The ascent is according to CursorAscentFromFont. It doesn't really make a
        // difference because it is added to the cursor TPoint and then used again
        // in CEikonEnv::DrawCursor
        }
    else
        { // The old way
        aHeight = AknLayoutUtils::CursorHeightFromFont( font.FontSpecInTwips() );
        aWidth  = AknLayoutUtils::CursorWidthFromFont ( font.FontSpecInTwips() );
        aAscent = AknLayoutUtils::CursorAscentFromFont( font.FontSpecInTwips() );
        }

    TMargins borderMargins = iBorder.Margins();
    aPos.iX = iPosition.iX + borderMargins.iLeft + EGapLeftOfFirstField;
    aPos.iY = iPosition.iY + borderMargins.iTop + EGapAboveText + 
        aAscent + ( EMfneFieldExtraHeight / 2 );
    
    if ( iAlignment == ELayoutAlignRight )
        {
        aPos.iX = iPosition.iX + iSize.iWidth - VerticalOffsetForMfnePosition();
        for ( TInt i = iNumFields-1 ; i >= iCurrentField ; i-- )
            {
            aPos.iX -= iFields[i]->WidthInPixels(font);
            }           
        }
    else if (iAlignment == ELayoutAlignCenter)
        {
        TInt width = iSize.iWidth-VerticalOffsetForMfnePosition();
        for ( TInt i = 0; i < iNumFields; i++ )
            {
            width -= iFields[i]->WidthInPixels( font );
            }           
        if ( width < 0 )
            {
            width = 0;
            }
        width /= 2;
        aPos.iX += width;
        for (TInt i = 0; i<iCurrentField; ++i)
            {
            aPos.iX += iFields[i]->WidthInPixels( font );       
            }           
        }
    else
        {
        for ( TInt i = 0; i < iCurrentField; ++i )
            {
            aPos.iX += iFields[i]->WidthInPixels( font );
            }           
        }
        
    aPos.iX += iFields[iCurrentField]->
        DistanceFromStartOfFieldToEndOfTextInPixels( font );
    }

void CEikMfne::DrawCursor()
    {
    __ASSERT_DEBUG(IsFocused() && (iFields[iCurrentField]->HighlightType()==CEikMfneField::ECursor), Panic(EEikPanicMfneBadCursorState3));  

    TInt cursorHeight( 0 );
    TInt cursorWidth( 0 );
    TInt cursorAscent( 0 );
    TPoint cursorPosition( 0, 0 );

    GetCursorInfo( cursorPosition, cursorHeight, cursorWidth, cursorAscent );

    iEikonEnv->DrawCursor(this, cursorPosition, cursorWidth, cursorAscent, cursorHeight);
    iExtension->iCursorShown = ETrue;
    }

void CEikMfne::HideCursor()
    {
    if ( iExtension->iCursorShown )
        {
        iEikonEnv->HideCursor(this);
        iExtension->iCursorShown = EFalse;
        }   
    }


void CEikMfne::ReportUpdate()
    {
    if ( iExtension )
        {
        TRAP_IGNORE (
            iExtension->iExtendedInputCapabilities->ReportEventL(
            CAknExtendedInputCapabilities::MAknEventObserver::EControlContentUpdatedInternally,
            NULL );
            )
        }
    }

/**
 * Gets the list of logical colors employed in the drawing of the control,
 * paired with an explanation of how they are used. Appends the list to aColorUseList.
 *
 * @since ER5U
 */
EXPORT_C void CEikMfne::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const
    {
    CEikBorderedControl::GetColorUseListL(aColorUseList);

    TInt commonAttributes = TCoeColorUse::EContents|TCoeColorUse::ENormal|TCoeColorUse::ENeutral;
    TCoeColorUse colorUse;

    colorUse.SetLogicalColor(EColorControlText);
    colorUse.SetUse(TCoeColorUse::EFore|TCoeColorUse::EActive|commonAttributes);
    aColorUseList.AppendL(colorUse);

    colorUse.SetLogicalColor(EColorControlHighlightText);
    colorUse.SetUse(TCoeColorUse::EFore|TCoeColorUse::EHighlights|commonAttributes);
    aColorUseList.AppendL(colorUse);

    colorUse.SetLogicalColor(EColorControlDimmedText);
    colorUse.SetUse(TCoeColorUse::EFore|TCoeColorUse::EDimmed|commonAttributes);
    aColorUseList.AppendL(colorUse);

    colorUse.SetLogicalColor(EColorControlBackground);
    colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::EActive|commonAttributes);
    aColorUseList.AppendL(colorUse);

    colorUse.SetLogicalColor(EColorControlHighlightBackground);
    colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::EHighlights|commonAttributes);
    aColorUseList.AppendL(colorUse);
    }

/**
 * Handles a change to the control's resources of type aType
 * which are shared across the environment, e.g. colors or fonts.
 *
 * @since ER5U
 */
EXPORT_C void CEikMfne::HandleResourceChange(TInt aType)
    {
    EvaluateSkinningBackground();
    CEikBorderedControl::HandleResourceChange(aType);
    if ( aType == KEikDynamicLayoutVariantSwitch && iFields )
        {
        if ( IsFocused() && iFields[iCurrentField]->HighlightType() ==
            CEikMfneField::ECursor )
            {
	        HideCursor();
            DrawCursor();
            }
        }
    }

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 *
 * @internal
 * @since App-Framework_6.1
 */
#ifndef _DEBUG
EXPORT_C void CEikMfne::WriteInternalStateL(RWriteStream&) const
    {}
#else
EXPORT_C void CEikMfne::WriteInternalStateL(RWriteStream& aWriteStream) const
    {
    CEikBorderedControl::WriteInternalStateL(aWriteStream);
    }
#endif

EXPORT_C void CEikMfne::Reserved_2()
    {
    }

EXPORT_C void CEikMfne::CEikMfne_Reserved()
    {
    }
    
    
// -----------------------------------------------------------------------------
// CEikMfne::HandleMfneCommandL
// Handles external MFNE commands
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikMfne::HandleMfneCommandL(TInt aCommand)
    {
    if( !AknLayoutUtils::PenEnabled() )
        {
        return;
        }

    // store the original setting
    TBool original = ConsumesUpAndDownKeys();
    
    if(!original)
        {
        // We need to enable the up/down key support to simulate key events
        SetUpAndDownKeysConsumed(ETrue);
        }
    
    TKeyEvent event;
    event.iCode = 0;
    event.iScanCode = 0;
    event.iModifiers = 0;
    event.iRepeats = 0;
    
    switch(aCommand)
        {
        case MAknMfneCommandObserver::EMfneIncrementCurrentFieldValue:
            // Increment current field value by simulating internally
            // an up arrow key event 
            event.iCode = EKeyUpArrow;
            OfferKeyEventL(event, EEventKey);
        break;
        
        case MAknMfneCommandObserver::EMfneDecrementCurrentFieldValue:
            // Decrement current field value by simulating internally
            // a down arrow key event 
            event.iCode = EKeyDownArrow;
            OfferKeyEventL(event, EEventKey);
        break;
        
        default:
        break;
        }
        
    if(!original)
        {
        // restore the original setting
        SetUpAndDownKeysConsumed(original);
        }
    }
    
EXPORT_C void CEikMfne::SetUseOverrideColors( TBool aUseOverrideColors )
    {
    iFlags.Assign( EUseOverrideColors, aUseOverrideColors );
    }


TBool CEikMfne::ConsumesUpAndDownKeys() const
    {
    return iFlags[ EConsumeUpAndDownKeysIndex ];
    }

TBool CEikMfne::SkinningBackground() const
    {
    if (iExtension)
        return iExtension->iSkinIdForTextBackgroundColor == KErrNotFound && iFlags[ ESkinningBackground ]; 
    else
        return iFlags[ ESkinningBackground ];
    }

void CEikMfne::EvaluateSkinningBackground()
    {
    // Status of application skinning is latched at construction and resource change
    iFlags.Assign( ESkinningBackground, AknsUtils::AvkonSkinEnabled() );
    }

MAknsControlContext* CEikMfne::SkinBackgroundControlContext() const
    {
    MAknsControlContext* context = 0;

    if ( iExtension )
        context = iExtension->iExternalSkinControlContext;

    if (!context && !iFlags[ESkinBackGroundControlContextSetByApi] )
        {
        // Obtain the context from Object Provider
        context = AknsDrawUtils::ControlContext( this );
        }

    return context;
    }

void CEikMfne::CreateExtensionIfRequiredL()
    {
    if (!iExtension )
        {
        iExtension = CEikMfneExtension::NewL();
        iExtension->iEditor = this;
        iExtension->iExtendedInputCapabilities->SetEditorType(
            CAknExtendedInputCapabilities::EMFNEBased );
        iExtension->iExtendedInputCapabilitiesProvider->SetMopParent(
            this );
        }
    }

void CEikMfne::SetCurrentField( TInt aCurrentField )
    {
    iCurrentField = aCurrentField;
    }

void CEikMfne::SetFirstEditableField( )
	{
    TBool foundEditable = EFalse;
    for ( TInt i=0; i < iNumFields; ++i )
        {
        if ( iFields[i]->IsEditable() )
            {
            SetCurrentField(i);
            foundEditable = ETrue;
            break;
            }
        }
    if ( !foundEditable )
	    {
	    SetCurrentField( 0 );
	    }
	}
//
// CEikNumberEditor
//

EXPORT_C CEikNumberEditor::CEikNumberEditor()
    {
    __DECLARE_NAME(_S("CEikNumberEditor"));
    AKNTASHOOK_ADD( this, "CEikNumberEditor" );
    }

EXPORT_C void CEikNumberEditor::ConstructL(TInt aMinimumValue, TInt aMaximumValue, TInt aInitialValue)
    {
    CreateFieldArrayL(1);
    iNumber=CEikMfneNumber::NewL(*Font(), aMinimumValue, aMaximumValue, aInitialValue, 0);
    AddField(iNumber);
    RefreshFromLocale();
    }

void CEikNumberEditor::RefreshFromLocale()
/**
Update the editor from locale - ensures that digits are displayed using correct numerals for current device settings.
@publishedComponent
@param aFont the font of the MFNE which owns this class
@post the next time the editor is drawn it will display the number using digit type derived from the locale information.
*/
    {
    iNumber->RefreshDigitType(*Font());
    }

EXPORT_C void CEikNumberEditor::SetMinimumAndMaximum(TInt aMinimumValue, TInt aMaximumValue)
    {
    iNumber->SetMinimumAndMaximum(aMinimumValue, aMaximumValue, *Font());
    }

EXPORT_C void CEikNumberEditor::GetMinimumAndMaximum(TInt& aMinimumValue, TInt& aMaximumValue) const
    {
    iNumber->GetMinimumAndMaximum(aMinimumValue, aMaximumValue);
    }

EXPORT_C void CEikNumberEditor::SetNumber(TInt aNumber)
    {
    iNumber->SetValue(aNumber, *Font());
    TRAP_IGNORE ( ReportEventL( MCoeControlObserver::EEventStateChanged ) );
    }

EXPORT_C TInt CEikNumberEditor::Number() const
    {
    return iNumber->Value();
    }

EXPORT_C void CEikNumberEditor::ConstructFromResourceL(TResourceReader& aResourceReader)
    {
    TInt minimumValue=aResourceReader.ReadInt32();
    TInt maximumValue=aResourceReader.ReadInt32();
    ConstructL(minimumValue, maximumValue, minimumValue);
    }
    
EXPORT_C void CEikNumberEditor::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikMfne::HandlePointerEventL(aPointerEvent); 
    }   

EXPORT_C void* CEikNumberEditor::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CEikNumberEditor::CEikMfne_Reserved()
    {
    }


// CEikRangeEditor

EXPORT_C CEikRangeEditor::CEikRangeEditor()
    {
    __DECLARE_NAME(_S("CEikRangeEditor"));
    AKNTASHOOK_ADD( this, "CEikRangeEditor" );
    }

EXPORT_C void CEikRangeEditor::ConstructL(TInt aMinimumValue, TInt aMaximumValue, const SEikRange& aInitialRange, HBufC* aSeparatorText)
    {
    const CFont& font=*Font();
    CreateFieldArrayL(3);
    iLowerLimit=CEikMfneNumber::NewL(font, aMinimumValue, aMaximumValue, aInitialRange.iLowerLimit, 0);
    AddField(iLowerLimit);
    CEikMfneSeparator* separator=CEikMfneSeparator::NewL(NULL);
    AddField(separator);
    iUpperLimit=CEikMfneNumber::NewL(font, aMinimumValue, aMaximumValue, aInitialRange.iUpperLimit, 0);
    AddField(iUpperLimit);
    // do stuff that can only be done when all leaving functions have successfully been done
    separator->SetText(aSeparatorText);

    RefreshFromLocale();
    }

void CEikRangeEditor::RefreshFromLocale()
    {
    iLowerLimit->RefreshDigitType(*Font() );
    iUpperLimit->RefreshDigitType(*Font() );
    }

EXPORT_C void CEikRangeEditor::SetMinimumAndMaximum(TInt aMinimumValue, TInt aMaximumValue)
    {
    const CFont& font=*Font();
    iLowerLimit->SetMinimumAndMaximum(aMinimumValue, aMaximumValue, font);
    iUpperLimit->SetMinimumAndMaximum(aMinimumValue, aMaximumValue, font);
    }

EXPORT_C void CEikRangeEditor::GetMinimumAndMaximum(TInt& aMinimumValue, TInt& aMaximumValue) const
    {
    iLowerLimit->GetMinimumAndMaximum(aMinimumValue, aMaximumValue);
#if defined(_DEBUG)
    TInt minimumValue;
    TInt maximumValue;
    iUpperLimit->GetMinimumAndMaximum(minimumValue, maximumValue);
    __ASSERT_DEBUG((minimumValue==aMinimumValue) && (maximumValue==aMaximumValue), Panic(EEikPanicRangeEditorInconsistentMinimumAndMaximum));
#endif
    }

EXPORT_C void CEikRangeEditor::SetRange(const SEikRange& aRange)
    {
    const CFont& font=*Font();
    iLowerLimit->SetValue(aRange.iLowerLimit, font);
    iUpperLimit->SetValue(aRange.iUpperLimit, font);
    }

EXPORT_C SEikRange CEikRangeEditor::Range() const
    {
    SEikRange range;
    range.iLowerLimit=iLowerLimit->Value();
    range.iUpperLimit=iUpperLimit->Value();
    return range;
    }

EXPORT_C void CEikRangeEditor::ConstructFromResourceL(TResourceReader& aResourceReader)
    {
    TInt minimumValue=aResourceReader.ReadInt32();
    TInt maximumValue=aResourceReader.ReadInt32();
    HBufC* separatorText=aResourceReader.ReadHBufCL();
    CleanupStack::PushL(separatorText);
    SEikRange initialRange;
    initialRange.iLowerLimit=maximumValue;
    initialRange.iUpperLimit=maximumValue;
    ConstructL(minimumValue, maximumValue, initialRange, separatorText);
    CleanupStack::Pop();
    }

void CEikRangeEditor::FieldIsAboutToBeDeHighlighted(CEikMfneField* aField, TBool& aDrawAllFields)
    {
    const CFont& font=*Font();
    if (aField==iLowerLimit)
        {
        TInt lowerLimitValue=iLowerLimit->Value();
        if (iUpperLimit->Value()<lowerLimitValue)
            {
            iUpperLimit->SetValue(lowerLimitValue, font);
            aDrawAllFields=ETrue;
            }
        }
    else if (aField==iUpperLimit)
        {
        TInt upperLimitValue=iUpperLimit->Value();
        if (iLowerLimit->Value()>upperLimitValue)
            {
            iLowerLimit->SetValue(upperLimitValue, font);
            aDrawAllFields=ETrue;
            }
        }
    }
    
EXPORT_C void CEikRangeEditor::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikMfne::HandlePointerEventL(aPointerEvent); 
    }   

EXPORT_C void* CEikRangeEditor::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CEikRangeEditor::CEikMfne_Reserved()
    {
    }


// CTimeEditor

class CTimeEditor : public CBase
    {
public:
    enum
        {
        EWithoutSecondsField        =1, // same as EEikTimeWithoutSecondsField,
        EWithoutPopoutCalendar      =2, // same as EEikDateWithoutPopoutCalendar,
        EWithoutHoursField          =4, // same as EEikTimeWithoutHoursField,
        EForce24HourFormat          =8, // same as EEikTimeForce24HourFormat,
        ETimeZoneOffsetFormat       =16,// same as EEikTimeZoneOffsetFormat,
        };
public:
    CTimeEditor();
    TInt NumFieldsRequired(TUint32 aFlags);
    void ConstructFieldsL(CEikMfne& aOwner, const TTime& aInitialTime, const CFont& aFont);
    void SetTime(const TTime& aTime, const CFont& aFont);
    void SetMinMax(TInt aHourMin,TInt aHourMax,TInt aMinuteMin,TInt aMinuteMax,
        TInt aSecondMin,TInt aSecondMax,const CFont& aFont);
    TTime Time() const;
    void SetUninitialised(TBool aUninitialised);
    TBool IsUninitialised() const;
    void RefreshFromLocale(const CFont& aFont);

private:
    void AddAmPmFieldsIfNecessaryL(CEikMfne& aOwner, TAmPm aAmPm, TLocalePos aPos);
private:
    enum // these are needed in case the OS locale changes between NumFieldsRequired and ConstructFieldsL being called
        {
        EIn12HourFormat             =0x20,
        ESpaceBeforeAmPm            =0x40,
        EAmPmIsPositionedBeforeTime =0x80,
        };
private:
    TUint32 iFlags;
    // none of these pointers owns anything
    CEikMfneNumber* iSecond; // may be NULL;
    CEikMfneNumber* iMinute;
    CEikMfneNumber* iHour; // may be NULL;
    CEikMfneSymbol* iAmPm; // may be NULL;
    };

CTimeEditor::CTimeEditor()
    {
    __DECLARE_NAME(_S("CTimeEditor"));
    }

TInt CTimeEditor::NumFieldsRequired(TUint32 aFlags)
    {
    iFlags=aFlags;
    TInt numFieldsRequired=1; // 1 for minute
    if (~iFlags&EWithoutSecondsField)
        numFieldsRequired+=2; // 2 for separator and second
    if (~iFlags&EWithoutHoursField)
        numFieldsRequired+=2; // 2 for hour and separator
    if (~iFlags&EForce24HourFormat&&~iFlags&ETimeZoneOffsetFormat)
        {
        TLocale locale;
        TTimeFormat timeFormat=locale.TimeFormat();
        __ASSERT_DEBUG((timeFormat==ETime12) || (timeFormat==ETime24), Panic(EEikPanicDateEditorBadTimeFormat));
        if (timeFormat==ETime12)
            {
            if (locale.AmPmSymbolPosition()==ELocaleBefore)
                iFlags|=EAmPmIsPositionedBeforeTime;
            if (locale.AmPmSpaceBetween())
                {
                ++numFieldsRequired;
                iFlags|=ESpaceBeforeAmPm;
                }
            ++numFieldsRequired;
            iFlags|=EIn12HourFormat;
            }
        }
    return numFieldsRequired;
    }

void CTimeEditor::RefreshFromLocale(const CFont& aFont)
/**
Update the tier editor from locale - ensures that digits are displayed using correct numerals for current device settings.
@publishedComponent
@param aFont the font of the MFNE which owns this class
@post the next time the editor is drawn it will display the number using digit type derived from the locale information.
*/
    {
    if(iSecond)
        iSecond->RefreshDigitType(aFont);

    if(iMinute)
        iMinute->RefreshDigitType(aFont);

    if(iHour)
        iHour->RefreshDigitType(aFont);
    }

void CTimeEditor::ConstructFieldsL(CEikMfne& aOwner, const TTime& aInitialTime, const CFont& aFont)
    {
    TDateTime initialTime=aInitialTime.DateTime();
    TLocale locale;
    TInt timeSeparatorIndex=1;
    const TUint32 flags=CEikMfneNumber::EFillWithLeadingZeros|CEikMfneNumber::EPreserveOldWidthBeforeEditing;
    TInt hour=initialTime.Hour();
    TAmPm amPm=(hour<12)? EAm: EPm;
    TInt minimumHour=0;
    TInt maximumHour=23;
    if (iFlags&EIn12HourFormat)
        {
        minimumHour=1;
        maximumHour=12;
        hour%=12;
        if (hour==0)
            hour=12;
        }
    if (iFlags&ETimeZoneOffsetFormat)
        {
        minimumHour=0;
        maximumHour=12;
        hour=0;
        }
    // create and push the time elements in the opposite order to the order in which they will be added so that they are popped off in the correct order
    AddAmPmFieldsIfNecessaryL(aOwner, amPm, ELocaleBefore);
    TBool amIsBefor(iFlags&EAmPmIsPositionedBeforeTime);
    if (~iFlags&EWithoutSecondsField)
        {
        iSecond=CEikMfneNumber::NewL(aFont, 0, KMaxMinSecValue, initialTime.Second(), flags);
        CleanupStack::PushL(iSecond); // this needs to be pushed as it would not be destroyed by the class' destructor
        }
    iMinute=CEikMfneNumber::NewL(aFont, 0, KMaxMinSecValue, initialTime.Minute(), flags);
    CleanupStack::PushL(iMinute); // this needs to be pushed as it would not be destroyed by the class' destructor
    if (~iFlags&EWithoutHoursField)
        {
        //iHour=CEikMfneNumber::NewL(aFont, minimumHour, maximumHour, hour, flags&~((iFlags&EIn12HourFormat)? CEikMfneNumber::EFillWithLeadingZeros: 0));
        iHour=CEikMfneNumber::NewL(aFont, minimumHour, maximumHour, hour,flags);
        CleanupStack::PushL(iHour); // this needs to be pushed as it would not be destroyed by the class' destructor
        // add hour
        aOwner.AddField(iHour);
        CleanupStack::Pop();
        // add the first separator
        HBufC* firstSeparatorText=HBufC::NewLC(1); // also pushes on to CleanupStack
        firstSeparatorText->Des().Append(locale.TimeSeparator(timeSeparatorIndex++));
        aOwner.AddField(CEikMfneSeparator::NewL(firstSeparatorText));
        CleanupStack::Pop();
        }
    // add minute
    aOwner.AddField(iMinute);
    CleanupStack::Pop();
    if (~iFlags&EWithoutSecondsField)
        {
        // add the second separator
        HBufC* secondSeparatorText=HBufC::NewLC(1); // also pushes on to CleanupStack
        secondSeparatorText->Des().Append(locale.TimeSeparator(timeSeparatorIndex++));
        aOwner.AddField(CEikMfneSeparator::NewL(secondSeparatorText));
        CleanupStack::Pop();
        // add second
        aOwner.AddField(iSecond);
        CleanupStack::Pop();
        }
    if ( !amIsBefor )
        {
        AddAmPmFieldsIfNecessaryL(aOwner, amPm, ELocaleAfter);    
        }    
    else
        {
        // if am is added before time fields, set first editable time field 
        // as highlighted        
        for ( TInt i = 1; aOwner.Field( i ) != NULL; i++ )
            {
            if ( aOwner.Field( i )->IsEditable() )
                {
                aOwner.SetCurrentField( i );
                break;
                }                
            }        
        }    
    }

void CTimeEditor::SetTime(const TTime& aTime, const CFont& aFont)
    {
    TDateTime time=aTime.DateTime();
    if (iSecond)
        iSecond->SetValue(time.Second(), aFont);
    iMinute->SetValue(time.Minute(), aFont);
    TInt hour=time.Hour();
    if (iAmPm)
        {
        TAmPm amPm=(hour<12)? EAm: EPm;
        hour%=12;
        if (hour==0)
            hour=12;
        iAmPm->SetCurrentSymbolicItemToId(amPm);
        }
    if(iHour)
        iHour->SetValue(hour, aFont);
    }

void CTimeEditor::SetMinMax(TInt /*aHourMin*/,TInt /*aHourMax*/,TInt /*aMinuteMin*/,TInt /*aMinuteMax*/,
        TInt /*aSecondMin*/,TInt /*aSecondMax*/,const CFont& /*aFont*/)
    {
    /*iHour->SetMinimumAndMaximum(aHourMin, aHourMax, aFont);
    iMinute->SetMinimumAndMaximum(aMinuteMin, aMinuteMax, aFont);
    if (iSecond!=NULL)
        iSecond->SetMinimumAndMaximum(aSecondMin, aSecondMax, aFont);*/
    }

TTime CTimeEditor::Time() const
    {
    TInt dayValue=0;
    TInt hourValue=iHour?iHour->Value():0;
    if (iAmPm)
        {
        hourValue%=12;
        if (iAmPm->IdOfCurrentSymbolicItem()==EPm)
            hourValue+=12;
        }
    return TTime(TDateTime(0, EJanuary, dayValue, hourValue, iMinute->Value(), iSecond? iSecond->Value(): 0, 0));
    }

void CTimeEditor::AddAmPmFieldsIfNecessaryL(CEikMfne& aOwner, TAmPm aAmPm, TLocalePos aPos)
    {
    if ( iFlags&EIn12HourFormat )
        {
        // Test the am/pm symbol 
        TAmPmName amName(EAm);
        TAmPmName pmName(EPm);

        TBool stackedBefore = iFlags&EAmPmIsPositionedBeforeTime;

        // Use the directionality of the first character of the localized Am symbol
        // to determine if "Before" means stacked first or last. 
        TChar firstChar('A') ;
        if (amName.Length()>0)
            {
            firstChar = amName[0];
            TInt cat = firstChar.GetBdCategory();
            // RTL indicates that we have to put it stack as if after.
            if ( cat == TChar::ERightToLeft || cat == TChar::ERightToLeftArabic )
                stackedBefore = !(iFlags&EAmPmIsPositionedBeforeTime);
            }

        if ( ( stackedBefore && ( aPos==ELocaleBefore ) )
            || ( !stackedBefore && (aPos!=ELocaleBefore ) ) )
            {
            CEikMfneSeparator* space=NULL;
            if (iFlags&ESpaceBeforeAmPm)
                {
                // add separator consisting of a space
                HBufC* spaceSeparatorText=HBufC::NewLC(1); // also pushes on to CleanupStack
                spaceSeparatorText->Des().Append(TChar(' '));
                space=CEikMfneSeparator::NewL(spaceSeparatorText);
                CleanupStack::Pop();
                CleanupStack::PushL(space);
                }
            iAmPm=CEikMfneSymbol::NewL(2);
            CleanupStack::PushL(iAmPm); // this needs to be pushed as it would not be destroyed by the class' destructor

            // add the am symbol
            HBufC* amText=HBufC::NewLC(amName.Length()); // also pushes on to CleanupStack
            *amText=amName;
            iAmPm->AddSymbolicItem(CEikMfneSymbol::CItem::NewL(EAm, amName[0], amText), aAmPm==EAm); // !! IS amName[0] SUFFICIENT FOR THE KEY TO MATCH?
            CleanupStack::Pop();
            // add the pm symbol
            HBufC* pmText=HBufC::NewLC(pmName.Length()); // also pushes on to CleanupStack
            *pmText=pmName;
            iAmPm->AddSymbolicItem(CEikMfneSymbol::CItem::NewL(EPm, pmName[0], pmText), aAmPm==EPm); // !! IS pmName[0] SUFFICIENT FOR THE KEY TO MATCH?
            CleanupStack::Pop((iFlags&ESpaceBeforeAmPm)? 3: 2);
            if ( (!stackedBefore) && space )
                aOwner.AddField(space);
            aOwner.AddField(iAmPm);
            if ( stackedBefore && space )
                aOwner.AddField(space);
            }
        }
    }

void CTimeEditor::SetUninitialised(TBool aUninitialised)
    {
    if (iSecond)
        iSecond->SetUninitialised(aUninitialised);
    if (iMinute)
        iMinute->SetUninitialised(aUninitialised);
    if (iHour)
        iHour->SetUninitialised(aUninitialised);
    if (iAmPm)
        iAmPm->SetUninitialised(aUninitialised);
    }

TBool CTimeEditor::IsUninitialised() const
    {
    return 
        (iSecond && iSecond->IsUninitialised()) ||
        (iMinute && iMinute->IsUninitialised()) ||
        (iHour && iHour->IsUninitialised()) ||
        (iAmPm && iAmPm->IsUninitialised());
    }


// CDateEditor

class CDateEditor : public CBase
    {
public:
    CDateEditor(CEikMfne& aOwner, MEikCalendarObserver* aCalendarObserver, TInt aFirstFieldPosition);
    TInt NumFieldsRequired() const;
    void ConstructFieldsL(TInt aMinimumYear, TInt aMaximumYear, const TTime& aInitialDate, TBool aWithoutPopoutCalendar, CEikonEnv& aEikonEnv, const CFont& aFont);
    void SetMinimumAndMaximum(TInt aMinimumYear, TInt aMaximumYear, const CFont& aFont);
    void SetDate(const TTime& aDate, const CFont& aFont);
    TTime Date(const TTime* aTime=NULL) const;
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
    void PrepareForFocusLossL();
    void CreatePopoutIfRequiredL();
    void ExecuteCalendarL();

    void SetUninitialised(TBool aUninitialised);
    TBool IsUninitialised() const;
    void RefreshFromLocale(const CFont& aFont);
    
    static TInt ValidateCallBack( TAny* aPtr );

public:
    TInt Year() const;
    TInt Month() const;
    TInt Day() const;
    TBool IsTextNull() const;
    void UpdateMaxDay( const CFont& aFont );
private:
    class RDateElements // objects of this class must be pushed on to the cleanup-stack
        {
    public:
        RDateElements();
        void Add(CEikMfneNumber* aDateElement, TInt aPosition);
        CEikMfneNumber* Next();
    private:
        static void Cleanup(TAny* aThis);
    public:
        inline operator TCleanupItem() {return TCleanupItem(Cleanup, this);}
    private:
        enum {EMaximumNumberOfDateElements=3};
    private:
        CEikMfneNumber* iDateElements[EMaximumNumberOfDateElements];
        };

private:
    /**
    * Called to see if the date fields need to be re-ordered because the 
    * number format causes logical to visual reordering in text.
    */
    static TBool DateFieldReOrderingNeeded();

private:
    CEikMfne& iOwner;
    MEikCalendarObserver* iCalendarObserver;
    TBool iWithoutPopoutCalendar;
    // none of these pointers owns anything
    CEikMfneNumber* iDay;
    CEikMfneNumber* iMonth;
    CEikMfneNumber* iYear;
    TInt iDayFieldPosition;
    TInt iFirstFieldPosition;
    };

CDateEditor::CDateEditor(CEikMfne& aOwner,MEikCalendarObserver* aCalendarObserver,TInt aFirstFieldPosition)
    :iOwner(aOwner),
     iCalendarObserver(aCalendarObserver),
     iFirstFieldPosition(aFirstFieldPosition)
    {
    __DECLARE_NAME(_S("CDateEditor"));
    }

TInt CDateEditor::NumFieldsRequired() const
    {
    return 5;
    }

TBool CDateEditor::DateFieldReOrderingNeeded()
    {
    TBool reorderingNeeded(EFalse);

    TLocale locale;

    // Reordering needed if it is RTL, we have arabic digits and if the separator is not 
    // numeric separator.
    TLanguage language = (TLanguage)(User::Language() & KAknLanguageMask);
    if ( TBidiText::ScriptDirectionality( language ) == TBidiText::ERightToLeft)
        {
        TInt digitType = AknTextUtils::NumericEditorDigitType();
        if ( digitType == EDigitTypeArabicIndic )
            //|| digitType == EDigitTypeEasternArabicIndic ) // Urdu has numbers bidi=EN (LTR)
                                                             // no re-ordering is needed
            {
            TChar sep = locale.DateSeparator(1); 
            if ( sep.GetBdCategory() != TChar::ECommonNumberSeparator )
                reorderingNeeded = ETrue;
            }
        }
    return reorderingNeeded;
    }

void CDateEditor::ConstructFieldsL(TInt aMinimumYear, TInt aMaximumYear, const TTime& aInitialDate, TBool aWithoutPopoutCalendar, CEikonEnv& /*aEikonEnv*/, const CFont& aFont)
    {
    iWithoutPopoutCalendar=aWithoutPopoutCalendar;
    const TUint32 flags=CEikMfneNumber::EFillWithLeadingZeros|CEikMfneNumber::EPreserveOldWidthBeforeEditing;
    TLocale locale;
    TDateFormat dateFormat=locale.DateFormat();
    TInt dateSeparatorIndex=1;
    TInt dayPosition=0, monthPosition=0, yearPosition=0; // dummy initializations to prevent compiler warnings

    // Implement switch in layout owning to locale:
    if ( DateFieldReOrderingNeeded() )
        {
        switch (dateFormat)
            {
        case EDateAmerican:
            monthPosition=2;
            dayPosition=1;
            yearPosition=0;
            break;
        case EDateEuropean:
            dayPosition=2;
            monthPosition=1;
            yearPosition=0;
            break;
        case EDateJapanese:
            yearPosition=2;
            monthPosition=1;
            dayPosition=0;
            break;
#if defined(_DEBUG)
        default:
            Panic(EEikPanicDateEditorBadDateFormat);
            break;
#endif
            }
        }
    else
        {
        switch (dateFormat)
            {
        case EDateAmerican:
            monthPosition=0;
            dayPosition=1;
            yearPosition=2;
            break;
        case EDateEuropean:
            dayPosition=0;
            monthPosition=1;
            yearPosition=2;
            break;
        case EDateJapanese:
            yearPosition=0;
            monthPosition=1;
            dayPosition=2;
            break;
#if defined(_DEBUG)
        default:
            Panic(EEikPanicDateEditorBadDateFormat);
            break;
#endif
            }
        }

    TDateTime initialDate=aInitialDate.DateTime();
    RDateElements dateElements;
    CleanupStack::PushL(dateElements);
    iDay=CEikMfneNumber::NewL(aFont, 1, 31, initialDate.Day()+1, flags);

    iDayFieldPosition = dayPosition * 2;
    dateElements.Add(iDay, dayPosition);
    iMonth=CEikMfneNumber::NewL(aFont, 1, 12, initialDate.Month()+1, flags);
    dateElements.Add(iMonth, monthPosition);
    iYear=CEikMfneNumber::NewL(aFont, aMinimumYear, aMaximumYear, initialDate.Year(), flags|CEikMfneNumber::ERepresentsYear);
    dateElements.Add(iYear, yearPosition);
    // add first date element
    iOwner.AddField(dateElements.Next());
    // add first separator
    HBufC* firstSeparatorText=HBufC::NewLC(1); // also pushes on to CleanupStack
    firstSeparatorText->Des().Append(locale.DateSeparator(dateSeparatorIndex++));
    iOwner.AddField(CEikMfneSeparator::NewL(firstSeparatorText));
    CleanupStack::Pop(firstSeparatorText);

    // add second date element
    iOwner.AddField(dateElements.Next());
    // add second separator
    HBufC* secondSeparatorText=HBufC::NewLC(1); // also pushes on to CleanupStack
    secondSeparatorText->Des().Append(locale.DateSeparator(dateSeparatorIndex++));
    iOwner.AddField(CEikMfneSeparator::NewL(secondSeparatorText));
    CleanupStack::Pop(secondSeparatorText); 

    // add third date element
    iOwner.AddField(dateElements.Next());
    CleanupStack::PopAndDestroy(); // 
    iOwner.SetValidateCallBack( TCallBack( ValidateCallBack, this ) );
    }

void CDateEditor::RefreshFromLocale(const CFont& aFont)
/**
Update the date editor from locale - ensursed that digits are displayed using correct numerals for current device settings.
@publishedComponent
@param aFont the font of the MFNE which owns this class
@post the next time the editor is drawn it will display the number using digit type derived from the locale information.
*/
    {
    iDay->RefreshDigitType(aFont);
    iMonth->RefreshDigitType(aFont);
    iYear->RefreshDigitType(aFont);
    }

void CDateEditor::SetMinimumAndMaximum(TInt aMinimumYear, TInt aMaximumYear, const CFont& aFont)
    {
    iYear->SetMinimumAndMaximum(aMinimumYear, aMaximumYear, aFont);
    }

void CDateEditor::SetDate(const TTime& aDate, const CFont& aFont)
    {
    TDateTime date=aDate.DateTime();
    iDay->SetValue(date.Day()+1, aFont);
    iMonth->SetValue(date.Month()+1, aFont);
    iYear->SetValue(date.Year(), aFont);
    }

TTime CDateEditor::Date(const TTime* aTime) const
    {
    TInt hour=0;
    TInt minute=0;
    TInt second=0;
    if (aTime)
        {
        TDateTime time=aTime->DateTime();
        hour=time.Hour();
        minute=time.Minute();
        second=time.Second();
        }
    TDateTime date;
    TInt day = iDay->Value();
    if (date.Set(iYear->Value(), (TMonth)(iMonth->Value()-1), day-1, 0, 0, 0, 0)!=KErrNone)
        {
        TInt maximumDay = Time::DaysInMonth( iYear->Value(), (TMonth)(iMonth->Value()-1));
        if (day > maximumDay)
            {
            day = maximumDay;
            iDay->SetValue(maximumDay, *(iOwner.Font()));
            iOwner.HighlightField(iDayFieldPosition + iFirstFieldPosition);
            }
//      AVKON - should not leave in Date() function. Day value is fixed instead.
        }
    return TTime(TDateTime(iYear->Value(), (TMonth)(iMonth->Value()-1), day-1, hour, minute, second, 0));
    }

TKeyResponse CDateEditor::OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/, TEventCode /*aType*/)
    {
//  AVKON - we do not want any behavior from up/down or tab key (which was here before)
    return EKeyWasNotConsumed;
    }

void CDateEditor::PrepareForFocusLossL()
    {
    TDateTime date;

    if (date.Set(iYear->Value(), (TMonth)(iMonth->Value()-1), iDay->Value()-1, 0, 0, 0, 0)!=KErrNone)
        {
        TInt maximumDay = Time::DaysInMonth( iYear->Value(), (TMonth)(iMonth->Value()-1));
        if ( iDay->Value() > maximumDay )
            {
            iDay->SetValue(maximumDay, *(iOwner.Font()));    
            iOwner.HighlightField(iDayFieldPosition + iFirstFieldPosition);
            iOwner.ReportUpdate();
            }
         iOwner.DrawNowAndLeaveWithTimeDateFormatInfoMsgL(R_EIK_TBUF_DATE_INVALID, date);
        //aEikonEnv.LeaveWithInfoMsg(R_EIK_TBUF_DATE_INVALID);
        }
    }

void CDateEditor::CreatePopoutIfRequiredL()
    {
    if (!iWithoutPopoutCalendar)
        ExecuteCalendarL();
    }

void CDateEditor::ExecuteCalendarL()
    {
    if( AknLayoutUtils::PenEnabled() )
        {
        // must not do anything when Touch UI is enabled
        }
    else
        {
        User::Leave(KErrNotSupported);
        }

/*  Build Thinning
    CEikCalendar* calendar=new(ELeave) CEikCalendar;
    calendar->SetCalendarObserver(iCalendarObserver);
    calendar->ExecuteLD(R_EIK_ONE_MONTH_CALENDAR);
*/
    }

TInt CDateEditor::Year() const
    {
    return(iYear->Value());
    }

TInt CDateEditor::Month() const
    {
    return(iMonth->Value());
    }

TInt CDateEditor::Day() const
    {
    return(iDay->Value());
    }

TBool CDateEditor::IsTextNull() const
    {
    return ( iYear->IsTextNull() | iMonth->IsTextNull() |  iDay->IsTextNull());
    }

void CDateEditor::UpdateMaxDay( const CFont& aFont )
	{
	TInt maximumDay = Time::DaysInMonth( iYear->Value(), (TMonth)(iMonth->Value()-1));
	iDay->SetMinimumAndMaximum( 1, maximumDay, aFont );
	}

// CDateEditor::RDateElements

CDateEditor::RDateElements::RDateElements()
    {
    for (TInt i=0; i<EMaximumNumberOfDateElements; ++i)
        iDateElements[i]=NULL;
    }

void CDateEditor::RDateElements::Add(CEikMfneNumber* aDateElement, TInt aPosition)
    {
    __ASSERT_DEBUG((aPosition>=0) && (aPosition<EMaximumNumberOfDateElements), Panic(EEikPanicDateEditorBadDateElementPosition));
    iDateElements[aPosition]=aDateElement;
    }

CEikMfneNumber* CDateEditor::RDateElements::Next()
    {
    for (TInt i=0; i<EMaximumNumberOfDateElements; ++i)
        if (iDateElements[i])
            {
            CEikMfneNumber* dateElement=iDateElements[i];
            iDateElements[i]=NULL;
            return dateElement;
            }
#if defined(_DEBUG)
    Panic(EEikPanicDateEditorNoMoreDateElements);
#endif
    return NULL; // dummy return to prevent compiler error
    }

void CDateEditor::RDateElements::Cleanup(TAny* aThis)
    {
    for (TInt i=0; i<EMaximumNumberOfDateElements; ++i)
        delete ((RDateElements*)aThis)->iDateElements[i];
    }

void CDateEditor::SetUninitialised(TBool aUninitialised)
    {
    if (iDay)
        iDay->SetUninitialised(aUninitialised);
    if (iMonth)
        iMonth->SetUninitialised(aUninitialised);
    if (iYear)
        iYear->SetUninitialised(aUninitialised);
    }

TBool CDateEditor::IsUninitialised() const
    {
    return 
        (iDay && iDay->IsUninitialised()) ||
        (iMonth && iMonth->IsUninitialised()) ||
        (iYear && iYear->IsUninitialised());
    }

TInt CDateEditor::ValidateCallBack( TAny* aPtr )
    {
    CDateEditor* edit( static_cast<CDateEditor*>( aPtr ) );
    TRAPD( err, edit->PrepareForFocusLossL() );
    edit->UpdateMaxDay( *(CEikonEnv::Static()->NormalFont()));
    return err;
    }

// CEikTimeEditor

EXPORT_C CEikTimeEditor::CEikTimeEditor()
    {
    __DECLARE_NAME(_S("CEikTimeEditor"));
    AKNTASHOOK_ADD( this, "CEikTimeEditor" );
    }

EXPORT_C CEikTimeEditor::~CEikTimeEditor()
    {
    AKNTASHOOK_REMOVE();
    delete iTimeEditor;
    }

EXPORT_C void CEikTimeEditor::ConstructL(const TTime& aMinimumTime, const TTime& aMaximumTime, const TTime& aInitialTime, TUint32 aFlags)
    {
    iTimeEditor=new(ELeave) CTimeEditor;
    //CreateFieldArrayL(iTimeEditor->NumFieldsRequired(aWithoutSecondsField? CTimeEditor::EWithoutSecondsField: 0));
    CreateFieldArrayL(iTimeEditor->NumFieldsRequired(aFlags));
    iTimeEditor->ConstructFieldsL(*this, aInitialTime, *Font());
    iTimeEditor->RefreshFromLocale(*Font());
    DoSetMinimumAndMaximum(aMinimumTime, aMaximumTime);
    }

EXPORT_C void CEikTimeEditor::SetMinimumAndMaximum(const TTime& aMinimumTime, const TTime& aMaximumTime)
    {
    // __ASSERT_ALWAYS((aMinimumTime>=iMinimumTime) && (aMaximumTime<=iMaximumTime), Panic(EEikPanicTimeEditorBadMinimumAndMaximum1));
    DoSetMinimumAndMaximum(aMinimumTime, aMaximumTime);
    }

EXPORT_C void CEikTimeEditor::GetMinimumAndMaximum(TTime& aMinimumTime, TTime& aMaximumTime) const
    {
    aMinimumTime=iMinimumTime;
    aMaximumTime=iMaximumTime;
    }

EXPORT_C void CEikTimeEditor::SetTime(const TTime& aTime)
    {
    iTimeEditor->SetTime(aTime, *Font());
	TRAP_IGNORE ( ReportEventL( MCoeControlObserver::EEventStateChanged ) );
    }

EXPORT_C TTime CEikTimeEditor::Time() const
    {
    return iTimeEditor->Time();
    }

void CEikTimeEditor::SetTTime(const TTime& aTime)
    {
    SetTime(aTime);
    }

TTime CEikTimeEditor::GetTTime() const
    {
    return(Time());
    }

EXPORT_C void CEikTimeEditor::ConstructFromResourceL(TResourceReader& aResourceReader)
    {
    TTime minimumTime=ReadTime(aResourceReader);
    TTime maximumTime=ReadTime(aResourceReader);
    TUint32 flags=aResourceReader.ReadUint8();
    ConstructL(minimumTime, maximumTime, maximumTime, flags);
    }

EXPORT_C void CEikTimeEditor::PrepareForFocusLossL()
    {
    CEikMfne::PrepareForFocusLossL();
    TTime time=Time();
    if (time<iMinimumTime)
        {
        SetTime(iMinimumTime);
        DrawNowAndLeaveWithTimeDateFormatInfoMsgL(R_EIK_TBUF_BEFORE_EARLIEST_ALLOWED_TIME, iMinimumTime);
        }
    else if (time>iMaximumTime)
        {
        SetTime(iMaximumTime);
        DrawNowAndLeaveWithTimeDateFormatInfoMsgL(R_EIK_TBUF_AFTER_LATEST_ALLOWED_TIME, iMaximumTime);
        }
    }

void CEikTimeEditor::DoSetMinimumAndMaximum(const TTime& aMinimumTime, const TTime& aMaximumTime)
    {
    __ASSERT_ALWAYS(aMinimumTime<=aMaximumTime, Panic(EEikPanicTimeEditorBadMinimumAndMaximum2));
    iMinimumTime=aMinimumTime;
    iMaximumTime=aMaximumTime;
    TTime time=Time();
    if (time<iMinimumTime)
        SetTime(iMinimumTime);
    else if (time>iMaximumTime)
        SetTime(iMaximumTime);
    }

EXPORT_C void CEikTimeEditor::CEikMfne_Reserved()
    {
    }
    
EXPORT_C void CEikTimeEditor::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikTTimeEditor::HandlePointerEventL(aPointerEvent); 
    }   

EXPORT_C void* CEikTimeEditor::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CEikTimeEditor::SetUninitialised(TBool aUninitialised)
    {
    iTimeEditor->SetUninitialised(aUninitialised);
    }

EXPORT_C TBool CEikTimeEditor::IsUninitialised() const
    {
    return iTimeEditor->IsUninitialised();
    }

// CEikDateEditor

EXPORT_C CEikDateEditor::CEikDateEditor()
    {
    __DECLARE_NAME(_S("CEikDateEditor"));
    AKNTASHOOK_ADD( this, "CEikDateEditor" );
    }

EXPORT_C CEikDateEditor::~CEikDateEditor()
    {
    AKNTASHOOK_REMOVE();
    delete iDateEditor;
    }

EXPORT_C void CEikDateEditor::ConstructL(const TTime& aMinimumDate, const TTime& aMaximumDate, const TTime& aInitialDate, TBool aWithoutPopoutCalendar)
    {
    __ASSERT_DEBUG(KAknMinimumDate<=aMinimumDate, Panic(EEikPanicDateEditorBadMinimum));
    __ASSERT_DEBUG(aMaximumDate<=KAknMaximumDate, Panic(EEikPanicDateEditorBadMaximum));
    TTime minDate = Max(KAknMinimumDate, aMinimumDate);
    TTime maxDate = Min(aMaximumDate, KAknMaximumDate);
    iDateEditor=new(ELeave) CDateEditor(*this,this,0);
    CreateFieldArrayL(iDateEditor->NumFieldsRequired());
    iDateEditor->ConstructFieldsL(minDate.DateTime().Year(), maxDate.DateTime().Year(), aInitialDate, aWithoutPopoutCalendar, *iEikonEnv, *Font());
    DoSetMinimumAndMaximum(minDate, maxDate);
    iDateEditor->RefreshFromLocale(*Font());
    }

EXPORT_C void CEikDateEditor::SetMinimumAndMaximum(const TTime& aMinimumDate, const TTime& aMaximumDate)
    {
    __ASSERT_DEBUG(KAknMinimumDate<=aMinimumDate, Panic(EEikPanicDateEditorBadMinimum));
    __ASSERT_DEBUG(aMaximumDate<=KAknMaximumDate, Panic(EEikPanicDateEditorBadMaximum));
    TTime minDate = Max(KAknMinimumDate, aMinimumDate);
    TTime maxDate = Min(aMaximumDate, KAknMaximumDate);
    iDateEditor->SetMinimumAndMaximum(minDate.DateTime().Year(), maxDate.DateTime().Year(), *Font());
    DoSetMinimumAndMaximum(minDate, maxDate);
    }

EXPORT_C void CEikDateEditor::GetMinimumAndMaximum(TTime& aMinimumDate, TTime& aMaximumDate) const
    {
    aMinimumDate=iMinimumDate;
    aMaximumDate=iMaximumDate;
    }

EXPORT_C void CEikDateEditor::SetDate(const TTime& aDate)
    {
    iDateEditor->SetDate(aDate, *Font());
    TRAP_IGNORE ( ReportEventL( MCoeControlObserver::EEventStateChanged ) );
    }

EXPORT_C TTime CEikDateEditor::Date() const
    {
    return iDateEditor->Date();
    }

void CEikDateEditor::SetTTime(const TTime& aTime)
    {
    SetDate(aTime);
    }

TTime CEikDateEditor::GetTTime() const
    {
    return(Date());
    }

EXPORT_C TKeyResponse CEikDateEditor::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
    {
    if (iDateEditor->OfferKeyEventL(aKeyEvent, aType)==EKeyWasConsumed)
        return EKeyWasConsumed;
    if ( ( aType==EEventKey)&& 
           ( aKeyEvent.iCode == EKeyLeftArrow || aKeyEvent.iCode == EKeyRightArrow || 
             aKeyEvent.iCode == EKeyDownArrow || aKeyEvent.iCode == EKeyUpArrow ) )
    	{
        iDateEditor->UpdateMaxDay( *Font() );
    	}

    return CEikMfne::OfferKeyEventL(aKeyEvent, aType);
    }

EXPORT_C void CEikDateEditor::ConstructFromResourceL(TResourceReader& aResourceReader)
    {
    TTime minimumDate=ReadDate(aResourceReader);
    TTime maximumDate=ReadDate(aResourceReader);
    TUint32 flags=aResourceReader.ReadUint8();
    ConstructL(minimumDate, maximumDate, maximumDate, flags&EEikDateWithoutPopoutCalendar);
    }

EXPORT_C void CEikDateEditor::PrepareForFocusLossL()
    {
    CEikMfne::PrepareForFocusLossL();
    iDateEditor->PrepareForFocusLossL();
    TTime date=Date();
    if (date<iMinimumDate)
        {
        SetDate(iMinimumDate);
        DrawNowAndLeaveWithTimeDateFormatInfoMsgL(R_EIK_TBUF_BEFORE_EARLIEST_ALLOWED_DATE, iMinimumDate);
        }
    else if (date>iMaximumDate)
        {
        SetDate(iMaximumDate);
        DrawNowAndLeaveWithTimeDateFormatInfoMsgL(R_EIK_TBUF_AFTER_LATEST_ALLOWED_DATE, iMaximumDate);
        }
    }

void CEikDateEditor::CreatePopoutIfRequiredL()
    {
    iDateEditor->CreatePopoutIfRequiredL();
    }

void CEikDateEditor::GetMinimumAndMaximumAndInitialDatesForCalendarL(TTime& aMinimumDate, TTime& aMaximumDate, TTime& aInitialDate) const
    {
    aMinimumDate=iMinimumDate;
    aMaximumDate=iMaximumDate;
    TDateTime date;
    if (iDateEditor->IsTextNull())
        CEikMfne::LeaveWithAlert(R_EIK_TBUF_DATE_INVALID);
    if (date.Set(iDateEditor->Year(), (TMonth)(iDateEditor->Month()-1), iDateEditor->Day()-1, 0, 0, 0, 0)!=KErrNone)
        CEikMfne::LeaveWithAlert(R_EIK_TBUF_DATE_INVALID);
    aInitialDate=iDateEditor->Date();
    }

void CEikDateEditor::SetDateFromCalendarAndDrawNow(const TTime& aDate)
    {
    iDateEditor->SetDate(aDate, *Font());
    DrawNow();
    }

void CEikDateEditor::DoSetMinimumAndMaximum(const TTime& aMinimumDate, const TTime& aMaximumDate)
    {
    __ASSERT_ALWAYS(aMinimumDate<=aMaximumDate, Panic(EEikPanicDateEditorBadMinimumAndMaximum2));
    TDateTime minimumDate=aMinimumDate.DateTime();
    TDateTime maximumDate=aMaximumDate.DateTime();
    iMinimumDate=TDateTime(minimumDate.Year(), minimumDate.Month(), minimumDate.Day(), 0, 0, 0, 0);
    iMaximumDate=TDateTime(maximumDate.Year(), maximumDate.Month(), maximumDate.Day(), 0, 0, 0, 0);
    TTime date=Date();
    if (date<iMinimumDate)
        SetDate(iMinimumDate);
    else if (date>iMaximumDate)
        SetDate(iMaximumDate);
    }

EXPORT_C void CEikDateEditor::CEikMfne_Reserved()
    {
    }
    
EXPORT_C void CEikDateEditor::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikTTimeEditor::HandlePointerEventL(aPointerEvent); 
    }   

EXPORT_C void* CEikDateEditor::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CEikDateEditor::SetUninitialised(TBool aUninitialised)
    {
    iDateEditor->SetUninitialised(aUninitialised);
    }

EXPORT_C TBool CEikDateEditor::IsUninitialised() const
    {
    return iDateEditor->IsUninitialised();
    }


// CEikTimeAndDateEditor

EXPORT_C CEikTimeAndDateEditor::CEikTimeAndDateEditor()
    {
    __DECLARE_NAME(_S("CEikTimeAndDateEditor"));
    AKNTASHOOK_ADD( this, "CEikTimeAndDateEditor" );
    }

EXPORT_C CEikTimeAndDateEditor::~CEikTimeAndDateEditor()
    {
    AKNTASHOOK_REMOVE();
    delete iTimeEditor;
    delete iDateEditor;
    }

EXPORT_C void CEikTimeAndDateEditor::ConstructL(const TTime& aMinimumTimeAndDate, const TTime& aMaximumTimeAndDate,
                                    const TTime& aInitialTimeAndDate,TUint32 aFlags, HBufC* aInterveningText)
    {
    iTimeEditor=new(ELeave) CTimeEditor;
    TInt numTimeFields(iTimeEditor->NumFieldsRequired(aFlags));
    iDateEditor=new(ELeave) CDateEditor(*this,this,numTimeFields);
    CreateFieldArrayL(numTimeFields+(aInterveningText? 1: 0)+iDateEditor->NumFieldsRequired());
    const CFont& font=*Font();
    CEikMfneSeparator* interveningText=NULL;

    // Implement reversed time and date date for A&H locales
    if ( TBidiText::ScriptDirectionality( (TLanguage)(User::Language() & KAknLanguageMask) ) == TBidiText::ELeftToRight)
        {
        iTimeEditor->ConstructFieldsL(*this, aInitialTimeAndDate, font);
        iTimeEditor->RefreshFromLocale(font);

        if (aInterveningText)
            {
            interveningText=CEikMfneSeparator::NewL(NULL);
            AddField(interveningText);
            }
        iDateEditor->ConstructFieldsL(aMinimumTimeAndDate.DateTime().Year(), aMaximumTimeAndDate.DateTime().Year(), aInitialTimeAndDate, (aFlags&CTimeEditor::EWithoutPopoutCalendar), *iEikonEnv, font);
        iDateEditor->RefreshFromLocale(font);
        }
    else  // These are reversed
        {
        iDateEditor->ConstructFieldsL(aMinimumTimeAndDate.DateTime().Year(), aMaximumTimeAndDate.DateTime().Year(), aInitialTimeAndDate, (aFlags&CTimeEditor::EWithoutPopoutCalendar), *iEikonEnv, font);
        iDateEditor->RefreshFromLocale(font);

        if (aInterveningText)
            {
            interveningText=CEikMfneSeparator::NewL(NULL);
            AddField(interveningText);
            }

        iTimeEditor->ConstructFieldsL(*this, aInitialTimeAndDate, font);
        iTimeEditor->RefreshFromLocale(font);
        }

    DoSetMinimumAndMaximum(aMinimumTimeAndDate, aMaximumTimeAndDate);
    // do stuff that can only be done when all leaving functions have successfully been done
    if (aInterveningText)
        interveningText->SetText(aInterveningText);
    }

EXPORT_C void CEikTimeAndDateEditor::SetMinimumAndMaximum(const TTime& aMinimumTimeAndDate, const TTime& aMaximumTimeAndDate)
    {
    // __ASSERT_ALWAYS((aMinimumTimeAndDate>=iMinimumTimeAndDate) && (aMaximumTimeAndDate<=iMaximumTimeAndDate), Panic(EEikPanicTimeAndDateEditorBadMinimumAndMaximum1));
    iDateEditor->SetMinimumAndMaximum(aMinimumTimeAndDate.DateTime().Year(), aMaximumTimeAndDate.DateTime().Year(), *Font());
    DoSetMinimumAndMaximum(aMinimumTimeAndDate, aMaximumTimeAndDate);
    }

EXPORT_C void CEikTimeAndDateEditor::GetMinimumAndMaximum(TTime& aMinimumTimeAndDate, TTime& aMaximumTimeAndDate) const
    {
    aMinimumTimeAndDate=iMinimumTimeAndDate;
    aMaximumTimeAndDate=iMaximumTimeAndDate;
    }

EXPORT_C void CEikTimeAndDateEditor::SetTimeAndDate(const TTime& aTimeAndDate)
    {
    const CFont& font=*Font();
    iDateEditor->SetDate(aTimeAndDate, font);
    TDateTime dateTime=aTimeAndDate.DateTime();
    dateTime.SetYear(0);
    dateTime.SetMonth(EJanuary);
    dateTime.SetDay(0);
    TTime timeWithoutDate(dateTime);
    iTimeEditor->SetTime(timeWithoutDate, font);
    }

EXPORT_C TTime CEikTimeAndDateEditor::TimeAndDate() const
    {
    TTime time=iTimeEditor->Time();
    return iDateEditor->Date(&time);
    }

EXPORT_C void CEikTimeAndDateEditor::SetUninitialised(TBool aUninitialised)
    {
    iTimeEditor->SetUninitialised(aUninitialised);
    iDateEditor->SetUninitialised(aUninitialised);
    }

EXPORT_C TBool CEikTimeAndDateEditor::IsUninitialised() const
    {
    return iTimeEditor->IsUninitialised() || iDateEditor->IsUninitialised();
    }


void CEikTimeAndDateEditor::SetTTime(const TTime& aTime)
    {
    SetTimeAndDate(aTime);
    }

TTime CEikTimeAndDateEditor::GetTTime() const
    {
    return(TimeAndDate());
    }

EXPORT_C TKeyResponse CEikTimeAndDateEditor::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
    {
    if (iDateEditor->OfferKeyEventL(aKeyEvent, aType)==EKeyWasConsumed)
        return EKeyWasConsumed;
    return CEikMfne::OfferKeyEventL(aKeyEvent, aType);
    }

EXPORT_C void CEikTimeAndDateEditor::ConstructFromResourceL(TResourceReader& aResourceReader)
    {
    TTime minimumTimeAndDate=ReadTimeAndDate(aResourceReader);
    TTime maximumTimeAndDate=ReadTimeAndDate(aResourceReader);
    TBool flags=aResourceReader.ReadUint8();
    HBufC* interveningText=aResourceReader.ReadHBufCL();
    CleanupStack::PushL(interveningText);
    ConstructL(minimumTimeAndDate, maximumTimeAndDate, maximumTimeAndDate, flags, interveningText);
    CleanupStack::Pop();
    }

EXPORT_C void CEikTimeAndDateEditor::PrepareForFocusLossL()
    {
    CEikMfne::PrepareForFocusLossL();
    iDateEditor->PrepareForFocusLossL();
    TTime timeAndDate=TimeAndDate();
    if (timeAndDate<iMinimumTimeAndDate)
        {
        SetTimeAndDate(iMinimumTimeAndDate);
        DrawNowAndLeaveWithTimeDateFormatInfoMsgL(R_EIK_TBUF_BEFORE_EARLIEST_ALLOWED_TIME_AND_DATE, iMinimumTimeAndDate);
        }
    else if (timeAndDate>iMaximumTimeAndDate)
        {
        SetTimeAndDate(iMaximumTimeAndDate);
        DrawNowAndLeaveWithTimeDateFormatInfoMsgL(R_EIK_TBUF_AFTER_LATEST_ALLOWED_TIME_AND_DATE, iMaximumTimeAndDate);
        }
    }

void CEikTimeAndDateEditor::CreatePopoutIfRequiredL()
    {
    iDateEditor->CreatePopoutIfRequiredL();
    }

void CEikTimeAndDateEditor::GetMinimumAndMaximumAndInitialDatesForCalendarL(TTime& aMinimumDate, TTime& aMaximumDate, TTime& aInitialDate) const
    {
    aMinimumDate=iMinimumTimeAndDate;
    aMaximumDate=iMaximumTimeAndDate;
    TDateTime date;
    if (iDateEditor->IsTextNull())
        CEikMfne::LeaveWithAlert(R_EIK_TBUF_DATE_INVALID);
    if (date.Set(iDateEditor->Year(), (TMonth)(iDateEditor->Month()-1), iDateEditor->Day()-1, 0, 0, 0, 0)!=KErrNone)
        CEikMfne::LeaveWithAlert(R_EIK_TBUF_DATE_INVALID);
    aInitialDate=iDateEditor->Date();
    }

void CEikTimeAndDateEditor::SetDateFromCalendarAndDrawNow(const TTime& aDate)
    {
    iDateEditor->SetDate(aDate, *Font());
    DrawNow();
    }

void CEikTimeAndDateEditor::DoSetMinimumAndMaximum(const TTime& aMinimumTimeAndDate, const TTime& aMaximumTimeAndDate)
    {
    __ASSERT_ALWAYS(aMinimumTimeAndDate<=aMaximumTimeAndDate, Panic(EEikPanicTimeAndDateEditorBadMinimumAndMaximum2));
    iMinimumTimeAndDate=aMinimumTimeAndDate;
    iMaximumTimeAndDate=aMaximumTimeAndDate;
    TTime timeAndDate=TimeAndDate();
    if (timeAndDate<iMinimumTimeAndDate)
        SetTimeAndDate(iMinimumTimeAndDate);
    else if (timeAndDate>iMaximumTimeAndDate)
        SetTimeAndDate(iMaximumTimeAndDate);
    }

EXPORT_C void CEikTimeAndDateEditor::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikTTimeEditor::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CEikTimeAndDateEditor::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CEikTimeAndDateEditor::CEikMfne_Reserved()
    {
    }


// CEikDurationEditor

EXPORT_C CEikDurationEditor::CEikDurationEditor()
    {
    __DECLARE_NAME(_S("CEikDurationEditor"));
    AKNTASHOOK_ADD( this, "CEikDurationEditor" );
    }

EXPORT_C CEikDurationEditor::~CEikDurationEditor()
    {
    AKNTASHOOK_REMOVE();
    delete iTimeEditor;
    }

EXPORT_C void CEikDurationEditor::ConstructL(const TTimeIntervalSeconds& aMinimumDuration, const TTimeIntervalSeconds& aMaximumDuration, const TTimeIntervalSeconds& aInitialDuration, TUint32 aFlags)
    {
    iTimeEditor=new(ELeave) CTimeEditor;
    aFlags|=CTimeEditor::EForce24HourFormat;
    CreateFieldArrayL(iTimeEditor->NumFieldsRequired(aFlags));
    iTimeEditor->ConstructFieldsL(*this, Convert(aInitialDuration), *Font());
    iTimeEditor->RefreshFromLocale(*Font());

    DoSetMinimumAndMaximum(aMinimumDuration, aMaximumDuration);
    }

EXPORT_C void CEikDurationEditor::SetMinimumAndMaximum(const TTimeIntervalSeconds& aMinimumDuration, const TTimeIntervalSeconds& aMaximumDuration)
    {
    // __ASSERT_ALWAYS((aMinimumDuration>=iMinimumDuration) && (aMaximumDuration<=iMaximumDuration), Panic(EEikPanicDurationEditorBadMinimumAndMaximum1));
    DoSetMinimumAndMaximum(aMinimumDuration, aMaximumDuration);
    }

EXPORT_C void CEikDurationEditor::GetMinimumAndMaximum(TTimeIntervalSeconds& aMinimumDuration, TTimeIntervalSeconds& aMaximumDuration) const
    {
    aMinimumDuration=iMinimumDuration;
    aMaximumDuration=iMaximumDuration;
    }

EXPORT_C void CEikDurationEditor::SetDuration(const TTimeIntervalSeconds& aDuration)
    {
    iTimeEditor->SetTime(Convert(aDuration), *Font());
    }

EXPORT_C TTimeIntervalSeconds CEikDurationEditor::Duration() const
    {
    return Convert(iTimeEditor->Time());
    }

EXPORT_C void CEikDurationEditor::ConstructFromResourceL(TResourceReader& aResourceReader)
    {
    TTimeIntervalSeconds minimumDuration=ReadDuration(aResourceReader);
    TTimeIntervalSeconds maximumDuration=ReadDuration(aResourceReader);
    TUint32 flags=aResourceReader.ReadUint8();
    ConstructL(minimumDuration, maximumDuration, maximumDuration, flags);
    }

EXPORT_C void CEikDurationEditor::PrepareForFocusLossL()
    {
    CEikMfne::PrepareForFocusLossL();
    TTimeIntervalSeconds duration=Duration();
    if (duration<iMinimumDuration)
        {
        SetDuration(iMinimumDuration);

        DrawNowAndLeaveWithTimeDateFormatInfoMsgL(R_EIK_TBUF_BELOW_SHORTEST_ALLOWED_DURATION, Convert(iMinimumDuration));
        }
    else if (duration>iMaximumDuration)
        {
        SetDuration(iMaximumDuration);
        DrawNowAndLeaveWithTimeDateFormatInfoMsgL(R_EIK_TBUF_ABOVE_LONGEST_ALLOWED_DURATION, Convert(iMaximumDuration));
        }
    }

void CEikDurationEditor::DoSetMinimumAndMaximum(const TTimeIntervalSeconds& aMinimumDuration, const TTimeIntervalSeconds& aMaximumDuration)
    {
    __ASSERT_ALWAYS(aMinimumDuration<=aMaximumDuration, Panic(EEikPanicDurationEditorBadMinimumAndMaximum2));
    iMinimumDuration=aMinimumDuration;
    iMaximumDuration=aMaximumDuration;
    TTimeIntervalSeconds duration=Duration();
    if (duration<iMinimumDuration)
        SetDuration(iMinimumDuration);
    else if (duration>iMaximumDuration)
        SetDuration(iMaximumDuration);
    }
    
EXPORT_C void CEikDurationEditor::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikMfne::HandlePointerEventL(aPointerEvent); 
    }    

EXPORT_C void* CEikDurationEditor::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CEikDurationEditor::CEikMfne_Reserved()
    {
    }


// CEikTimeOffsetEditor

EXPORT_C CEikTimeOffsetEditor::CEikTimeOffsetEditor()
    {
    __DECLARE_NAME(_S("CEikTimeOffsetEditor"));
    AKNTASHOOK_ADD( this, "CEikTimeOffsetEditor" );
    }

EXPORT_C CEikTimeOffsetEditor::~CEikTimeOffsetEditor()
    {
    AKNTASHOOK_REMOVE();
    delete iTimeEditor;
    }

EXPORT_C void CEikTimeOffsetEditor::ConstructL(const TTimeIntervalSeconds& aMinimumTimeOffset, const TTimeIntervalSeconds& aMaximumTimeOffset, const TTimeIntervalSeconds& aInitialTimeOffset, TUint32 aFlags)
    {
    TTimeIntervalSeconds magnitudeOfInitialTimeOffset=aInitialTimeOffset;
    TBool positive=ETrue;
    if (magnitudeOfInitialTimeOffset.Int()<0)
        {
        magnitudeOfInitialTimeOffset=-magnitudeOfInitialTimeOffset.Int();
        positive=EFalse;
        }
    iTimeEditor=new(ELeave) CTimeEditor;
    if (~aFlags&CTimeEditor::ETimeZoneOffsetFormat)
        {
        aFlags|=CTimeEditor::EForce24HourFormat;
        }
    CreateFieldArrayL(2+iTimeEditor->NumFieldsRequired(aFlags));
    iSign=CEikMfneSymbol::NewL(2);
    CleanupStack::PushL(iSign); // this needs to be pushed as it would not be destroyed by the class' destructor
    // add the "+" symbol
    HBufC* plusText=HBufC::NewLC(1); // also pushes on to CleanupStack
    *plusText=KPlus;
    iSign->AddSymbolicItem(CEikMfneSymbol::CItem::NewL('+', '+', plusText), positive);
    CleanupStack::Pop();
    // add the "-" symbol
    HBufC* minusText=HBufC::NewLC(1); // also pushes on to CleanupStack
    *minusText=KMinus;
    iSign->AddSymbolicItem(CEikMfneSymbol::CItem::NewL('-', '-', minusText), !positive);
    CleanupStack::Pop(2);
    AddField(iSign);
    HBufC* spaceSeparatorText=HBufC::NewLC(1); // also pushes on to CleanupStack
    spaceSeparatorText->Des().Append(TChar(' '));
    AddField(CEikMfneSeparator::NewL(spaceSeparatorText));
    CleanupStack::Pop();
    iTimeEditor->ConstructFieldsL(*this, Convert(magnitudeOfInitialTimeOffset), *Font());
    DoSetMinimumAndMaximum(aMinimumTimeOffset, aMaximumTimeOffset);
    }

EXPORT_C void CEikTimeOffsetEditor::SetMinimumAndMaximum(const TTimeIntervalSeconds& aMinimumTimeOffset, const TTimeIntervalSeconds& aMaximumTimeOffset)
    {
    // __ASSERT_ALWAYS((aMinimumTimeOffset>=iMinimumTimeOffset) && (aMaximumTimeOffset<=iMaximumTimeOffset), Panic(EEikPanicTimeOffsetEditorBadMinimumAndMaximum1));
    DoSetMinimumAndMaximum(aMinimumTimeOffset, aMaximumTimeOffset);
    }

EXPORT_C void CEikTimeOffsetEditor::GetMinimumAndMaximum(TTimeIntervalSeconds& aMinimumTimeOffset, TTimeIntervalSeconds& aMaximumTimeOffset) const
    {
    aMinimumTimeOffset=iMinimumTimeOffset;
    aMaximumTimeOffset=iMaximumTimeOffset;
    }

EXPORT_C void CEikTimeOffsetEditor::SetTimeOffset(const TTimeIntervalSeconds& aTimeOffset)
    {
    TTimeIntervalSeconds magnitudeOfTimeOffset=aTimeOffset;
    TInt signId='+';
    if (magnitudeOfTimeOffset.Int()<0)
        {
        magnitudeOfTimeOffset=-magnitudeOfTimeOffset.Int();
        signId='-';
        }
    iTimeEditor->SetTime(Convert(magnitudeOfTimeOffset), *Font());
    iSign->SetCurrentSymbolicItemToId(signId);
    }

EXPORT_C TTimeIntervalSeconds CEikTimeOffsetEditor::TimeOffset() const
    {
    TTimeIntervalSeconds timeOffset=Convert(iTimeEditor->Time());
    if (iSign->IdOfCurrentSymbolicItem()=='-')
        timeOffset=-timeOffset.Int();
    return timeOffset;
    }

EXPORT_C void CEikTimeOffsetEditor::ConstructFromResourceL(TResourceReader& aResourceReader)
    {
    TTimeIntervalSeconds minimumTimeOffset=ReadTimeOffset(aResourceReader);
    TTimeIntervalSeconds maximumTimeOffset=ReadTimeOffset(aResourceReader);
    TUint32 flags=aResourceReader.ReadUint8();
    ConstructL(minimumTimeOffset, maximumTimeOffset, maximumTimeOffset, flags);
    }

EXPORT_C void CEikTimeOffsetEditor::PrepareForFocusLossL()
    {
    CEikMfne::PrepareForFocusLossL();
    TTimeIntervalSeconds timeOffset=TimeOffset();
    if (timeOffset<iMinimumTimeOffset)
        {
        SetTimeOffset(iMinimumTimeOffset);
        TInt valueOfMinimumTimeOffset=iMinimumTimeOffset.Int();
        TInt resourceId=R_EIK_TBUF_BELOW_MINIMUM_TIME_OFFSET;
        if (valueOfMinimumTimeOffset<0)
            {
            valueOfMinimumTimeOffset=-valueOfMinimumTimeOffset;
            resourceId=R_EIK_TBUF_BELOW_NEGATIVE_MINIMUM_TIME_OFFSET;
            }
        DrawNowAndLeaveWithTimeDateFormatInfoMsgL(resourceId, Convert(TTimeIntervalSeconds(valueOfMinimumTimeOffset)));
        }
    else if (timeOffset>iMaximumTimeOffset)
        {
        SetTimeOffset(iMaximumTimeOffset);
        TInt valueOfMaximumTimeOffset=iMaximumTimeOffset.Int();
        TInt resourceId=R_EIK_TBUF_ABOVE_MAXIMUM_TIME_OFFSET;
        if (valueOfMaximumTimeOffset<0)
            {
            valueOfMaximumTimeOffset=-valueOfMaximumTimeOffset;
            resourceId=R_EIK_TBUF_ABOVE_NEGATIVE_MAXIMUM_TIME_OFFSET;
            }
        DrawNowAndLeaveWithTimeDateFormatInfoMsgL(resourceId, Convert(TTimeIntervalSeconds(valueOfMaximumTimeOffset)));
        }
    }

void CEikTimeOffsetEditor::DoSetMinimumAndMaximum(const TTimeIntervalSeconds& aMinimumTimeOffset, const TTimeIntervalSeconds& aMaximumTimeOffset)
    {
    __ASSERT_ALWAYS(aMinimumTimeOffset<=aMaximumTimeOffset, Panic(EEikPanicTimeOffsetEditorBadMinimumAndMaximum2));
    iMinimumTimeOffset=aMinimumTimeOffset;
    iMaximumTimeOffset=aMaximumTimeOffset;
    TTimeIntervalSeconds timeOffset=TimeOffset();
    if (timeOffset<iMinimumTimeOffset)
        SetTimeOffset(iMinimumTimeOffset);
    else if (timeOffset>iMaximumTimeOffset)
        SetTimeOffset(iMaximumTimeOffset);
    }

EXPORT_C void CEikTimeOffsetEditor::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikMfne::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CEikTimeOffsetEditor::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CEikTimeOffsetEditor::CEikMfne_Reserved()
    {
    }

EXPORT_C void CEikMfne::SetSkinTextColorL(TInt aAknSkinIDForTextColor, TInt aAknSkinIDForBgColor)
    {
    CreateExtensionIfRequiredL();
        
    iExtension->iAknSkinColorIndex = aAknSkinIDForTextColor;
    iExtension->iSkinIdForTextBackgroundColor = aAknSkinIDForBgColor;
    
    // if we are already visible, try to apply new color
    if (IsVisible())
        {
        DrawDeferred(); // No hurry anyway
        }
    }
    
EXPORT_C void CEikMfne::SizeChanged()
    {    
    CEikBorderedControl::SizeChanged();
    if ( !iFields || iCurrentField < 0 || iCurrentField >= iNumFields )
        {
        return;
        }
    TBool cursorDisplay( iFields[iCurrentField]->HighlightType() ==
        CEikMfneField::ECursor );
    if ( IsFocused() && cursorDisplay )
        {
        TRect mainPaneRect;        
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, 
            mainPaneRect );
        TRect rect( Rect() );
        if ( rect.iTl.iY < 0 || rect.iBr.iY > mainPaneRect.Height() ||
             rect.iTl.iX >= mainPaneRect.Width() || rect.iBr.iX <= 0 )
            {
            HideCursor();    
            }
        else
            {
            DrawCursor();
            }
        }    
    }

EXPORT_C void CEikMfne::MakeVisible( TBool aVisible )
    {
    CEikBorderedControl::MakeVisible( aVisible );
    if ( !aVisible && iExtension->iCursorShown )
        {
        HideCursor();
        }
    }

void CEikMfne::SetValidateCallBack( TCallBack aCallBack )
    {
    if ( iExtension )
        {
        iExtension->iValidateValueCallBack = aCallBack;
        }
    }

void CEikMfne::ReportStateChangeEventL()
    {
    ReportEventL( MCoeControlObserver::EEventStateChanged );
    }

void CEikMfne::LaunchPenInputL()
    {
    if ( iExtension && !iExtension->iDisablePenInput )
        {
        if ( iExtension->iFingerSupport && 
            iExtension->iFingerParam == EnableWithAllHighlight )
            {            
            iExtension->iHighlightAll = !iExtension->iTouchActivated &&
            !(iExtension->iExtendedInputCapabilities->Capabilities() & CAknExtendedInputCapabilities::EInputEditorQwertyInputActive);
            if ( iExtension->iHighlightAll )
                {                
                SetFirstEditableField();
                }            
            ReportUpdate();
            DrawDeferred();
            }
        iExtension->iExtendedInputCapabilities->ReportEventL( 
            CAknExtendedInputCapabilities::MAknEventObserver::EActivatePenInputRequest, 
            0 );
        iExtension->iTouchActivated = ETrue;
        }
    }
