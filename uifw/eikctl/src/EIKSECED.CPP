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


#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikdefmacros.h>
#endif
#include <eikseced.h>
#include <barsread.h>
#include <eikenv.h>
#include <eikpanic.h>
#include <e32keys.h>
#include <aknedsts.h>
#include <gulcolor.h>
#include <AknUtils.h>

#include <avkon.rsg>
#include <aknenv.h>
#include <aknappui.h>
#include <aknsoundsystem.h>

#include <AknsFrameBackgroundControlContext.h>
#include <AknsDrawUtils.h>

#include <PUAcodes.hrh>

#include <AknTasHook.h>
#include <AknTextDecorationMetrics.h>
#include <AknLayoutFont.h>

#include <aknextendedinputcapabilities.h>
#include <touchfeedback.h>

#define KSecretChar '*'
#define KSecretCharAsString "*"
#define KWait 1000000

_LIT(KSecretCharString, "*******************************");

#ifdef RD_UI_TRANSITION_EFFECTS_PHASE2
#include <gfxtranseffect/gfxtranseffect.h>
#include <akntransitionutils.h>
#include <avkondomainpskeys.h>
#include <e32property.h>

// Helper class that monitor redirection changes
class CRedirectionListener : public CBase, public MAknTransitionUtilsObserver
    {
private:
    TInt AknTransitionCallback( TInt aEvent, TInt aState,
            const TDesC8* /*aParams*/ )
        {
        if ( aEvent == CAknTransitionUtils::EEventWsBufferRedirection )
            {
            iRedirected = aState;
            if ( iCursorEnabled )
                {
                if ( iRedirected )
                    {
                    if ( iWg && iCursorStatus )
                        {
                        iWg->CancelTextCursor();
                        }
                    iCursorStatus = EFalse;
                    }
                else
                    {
                    iOwner.EnableCursor( ETrue );
                    }
                }
            }
        return 0;
        }

public:
    CRedirectionListener( CEikSecretEditor& aOwner ) : iOwner( aOwner )
        {
        RProperty::Get( KPSUidAvkonDomain, KAknTfxServerRedirectionStatus,
                        iRedirected );
        iRedirected &= ETfxScreenRedirected;
        }
    
    inline void EnableCursor()
        {
        iCursorEnabled = ETrue;
        }
    
    void DisableCursor()
        {
        if ( iWg && iCursorStatus )
            {
            iWg->CancelTextCursor();
            }
        iCursorEnabled = EFalse;
        iCursorStatus = EFalse;
        }
    
    void UpdateCursor( const TTextCursor& aCursor )
        {
        TInt redirected;
        RProperty::Get( KPSUidAvkonDomain, KAknTfxServerRedirectionStatus,
                        redirected );
        redirected &= ETfxScreenRedirected;
        if ( redirected != iRedirected && redirected )
            {
            AknTransitionCallback( CAknTransitionUtils::EEventWsBufferRedirection,
                                   1, NULL );
            return;
            }

        iRedirected = redirected;
        
        if ( iCursorEnabled && iWg && iWindow && !iRedirected )
            {
            iWg->SetTextCursor( *iWindow, iOwner.CursorPos(),
                                aCursor );
            iCursorStatus = ETrue;
            }
        }
        
    inline void SetWindows( RWindowGroup* aWg, RWindowBase* aWindow )
        {
        iWg = aWg;
        iWindow = aWindow;
        }
private:
    TBool iRedirected;
    TBool iCursorEnabled;
    TBool iCursorStatus;
    RWindowGroup* iWg;
    RWindowBase* iWindow;
    CEikSecretEditor& iOwner;
    };
#endif

/**
* Internal extension class for CEikSecretEditor.
*
* @since 2.0
*
* @internal
*/
class CEikSecretEditorExtension : public CBase
    {
public: // Construction and destruction

    CEikSecretEditorExtension()
    :iAknSkinColorIndex(KErrNotFound), 
    iSkinIdForBgColor(KErrNotFound), 
    iFeedback(MTouchFeedback::Instance())
                {
                }

    ~CEikSecretEditorExtension()
        {
        delete iExtendedInputCapabilitiesProvider;
        delete iExtendedInputCapabilities;
        }

    static CEikSecretEditorExtension* NewL()
        {
        CEikSecretEditorExtension* self =
        new ( ELeave ) CEikSecretEditorExtension;

        CleanupStack::PushL( self );
        self->ConstructL();
        CleanupStack::Pop();
        return self;
        }

    void ConstructL()
        {
        iExtendedInputCapabilities = 
        CAknExtendedInputCapabilities::NewL();
        TUint cap( iExtendedInputCapabilities->Capabilities() );
        cap |= CAknExtendedInputCapabilities::EInputEditorAlignBidi;
        iExtendedInputCapabilities->SetCapabilities( cap );

        iExtendedInputCapabilitiesProvider =
        new ( ELeave ) CAknExtendedInputCapabilities::
        CAknExtendedInputCapabilitiesProvider;

        iExtendedInputCapabilitiesProvider->SetExtendedInputCapabilities(
                iExtendedInputCapabilities );

        iExtendedInputCapabilities->SetEditorType( 
                CAknExtendedInputCapabilities::EEikSecretEditorBased );                
        }

public: // Data
    MAknsControlContext* iBgContext; // Not owned
    TBool iBgContextSet;
    TInt iAknSkinColorIndex;
    TInt iSkinIdForBgColor;
    MTouchFeedback* iFeedback;

    /**
     * Pointer to a CAknExtendedInputCapabilities.
     * Own.
     */
    CAknExtendedInputCapabilities* iExtendedInputCapabilities; 

    /**
     * Pointer to a extended input capabilities object provider.
     * Own.
     */
    CAknExtendedInputCapabilities::CAknExtendedInputCapabilitiesProvider*
    iExtendedInputCapabilitiesProvider;

    TInt iDisablePenInput; // Mainly for 0/1 values
    TTextCursor iCursor;
    RWindowGroup* iWg;
    RWindowBase* iWindow;
    TRect iTextRect;
    TBool iCursorEnabled;
    TBool iWindowSet;
    TBool iLaunchPenInputAutomatic;
    TBool iPartialScreenInput;
    };

EXPORT_C void CEikSecretEditor::AknSetFont(const CFont &aFont)
    { 
    iFont = &aFont;
    iCharWidth=iFont->TextWidthInPixels(TPtrC((TText*)KSecretCharAsString, 1));
    CalculateAscent();
    }

EXPORT_C void CEikSecretEditor::AknSetAlignment(const CGraphicsContext::TTextAlign &aAlign) { iAlign = aAlign; }

EXPORT_C void CEikSecretEditor::SetDefaultInputMode(TInt aInputMode)
    {
    if (iFepState)
        {
        if ( aInputMode != EAknEditorNumericInputMode )
            {
            aInputMode = EAknEditorSecretAlphaInputMode;
            }
        
        CAknEdwinState* edwinState = STATIC_CAST(CAknEdwinState*, iFepState);
        edwinState->SetDefaultInputMode(aInputMode);
        edwinState->SetCurrentInputMode(aInputMode);
        }
    }

EXPORT_C CEikSecretEditor::CEikSecretEditor()
    : CEikBorderedControl(TGulBorder(TGulBorder::ESingleGray))
    {
    __DECLARE_NAME(_S("CEikSecretEditor"));
    const CFont* font=iCoeEnv->NormalFont();
    iFont = font;
    iCharWidth=font->TextWidthInPixels(TPtrC((TText*)KSecretCharAsString, 1));
    CalculateAscent();
    iAlign = CGraphicsContext::ELeft;
    AKNTASHOOK_ADD( this, "CEikSecretEditor" );
    }

EXPORT_C CEikSecretEditor::~CEikSecretEditor()
    {
    AKNTASHOOK_REMOVE();
#ifdef RD_UI_TRANSITION_EFFECTS_PHASE2
    CRedirectionListener* listener = ( CRedirectionListener* )
        CAknTransitionUtils::GetData( (TInt) this );
    if ( listener )
        {
        CAknTransitionUtils::RemoveObserver( listener,
            CAknTransitionUtils::EEventWsBufferRedirection );
        CAknTransitionUtils::RemoveData( (TInt) this );
        delete listener;
        }
#endif
    delete iInlineEditText;
    delete iFepState;
    delete iTimer;
    delete iSecCharArr;
    delete iExtension;
    }

EXPORT_C void CEikSecretEditor::ConstructFromResourceL(TResourceReader& aReader)
    //
    // Construct from resource
    //
    {
    iMaxLen=aReader.ReadUint16();
    __ASSERT_ALWAYS(iMaxLen<=EMaxSecEdSecArrayLength, Panic(EEikPanicSecretEditorTooLong));
    iSecCharArr = HBufC::NewL( EMaxSecEdSecArrayLength );
    iFepState = CreateFepStateL();

    if ( !iExtension )
        {
        iExtension = CEikSecretEditorExtension::NewL();
        }
    InitCRedirectionListenerL();
    }

void CEikSecretEditor::StartTimer()
    {
    iTimer->Start(KWait, KWait, TCallBack(TimerCallback, this));
    }

TInt CEikSecretEditor::TimerCallback(TAny* aThis)
    {
    static_cast<CEikSecretEditor*>(aThis)->Update();
    return NULL;
    }

EXPORT_C void CEikSecretEditor::Update()
    {
    if ( iTimer )
        {
        iTimer->Cancel();
        }
    InsertSecretChar();
    DrawDeferred();
    }

void CEikSecretEditor::OverflowAlert()
/**
Display alert to user, when character is entered but there is no more room in the field.
Current implementation is to play a sound alert.
@publishedComponent
*/
    {
    CAknKeySoundSystem* soundPlayer = (static_cast<CAknAppUi*>(CEikonEnv::Static()->AppUi()))->KeySounds();
    if(soundPlayer)
        {
        soundPlayer->PlaySound(EAvkonSIDWarningTone);
        }
    };

EXPORT_C TKeyResponse CEikSecretEditor::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    //
    // Respond to key presses
    //
    {
    if ( aType != EEventKey )
        {
        return EKeyWasConsumed;
        }
    TInt code=aKeyEvent.iCode;
    if ((code==EKeyUpArrow) || (code==EKeyDownArrow) || (aKeyEvent.iScanCode==EStdKeyHash) ||
    	(code==EKeyLeftArrow) || (code==EKeyRightArrow))
        return(EKeyWasNotConsumed);
    
    EnableCursor( EFalse );

    if ( ( code<ENonCharacterKeyBase  && TChar(code).IsPrint() ) || code == KPuaCodeSpaceSymbol)
        {
        if (iSecCharArr->Length()<iMaxLen)
            {
            AppendCharacterL( code );
            ReportEventL(MCoeControlObserver::EEventStateChanged);
            }
        else
            {
            iBufferFull=ETrue;
            OverflowAlert();
            }
        }

    if (iSecCharArr->Length()>0 && (code==EKeyBackspace || (code==EKeyF20 && !iBufferFull)))
        {
        iBufferFull=EFalse;

        TPtr secCharArrAppend = iSecCharArr->Des();
        secCharArrAppend.Delete(iSecCharArr->Length() - 1,1);
        Update();
        // ---------------
        // If the text doesn't fit on line and a user presses backspace
        // it must be illustrated to the user that a char was deleted
        // (instead of just showing max amount of KSecretChars).
        if ( iSecCharArr->Length() >= CharsFitOnEditor() )
            {
            if (!iTimer)
                iTimer=CPeriodic::NewL(CActive::EPriorityLow);
            if (iTimer->IsActive())
                Update();

            iBuf.Delete(iBuf.Length() - 1,1);
            DrawDeferred();
            StartTimer();
            }
        //-----------
        if ( iSecCharArr->Length() == 0 )
            {
            EnableCursor( ETrue );
            }
        ReportEventL(MCoeControlObserver::EEventStateChanged);
        }
    if ( code != EKeyF20 )
        {
        ReportUpdate();
        }
    return EKeyWasConsumed;
    }

EXPORT_C TSize CEikSecretEditor::MinimumSize()
    //
    // Returns the minimum size needed to display
    //
    {
    TSize size=iBorder.SizeDelta();

    const CAknLayoutFont* layoutFont = CAknLayoutFont::AsCAknLayoutFontOrNull( iFont );
    if ( layoutFont )
        {
        size.iHeight += layoutFont->TextPaneHeight();
        }
    else
        {
        size.iHeight += iFont->HeightInPixels();
        }
    TAknTextDecorationMetrics decoration( iFont );
    TInt leftMargin(0);
    TInt rightMargin(0);
    decoration.GetLeftAndRightMargins( rightMargin, leftMargin );
    size.iWidth+=iCharWidth*(iMaxLen+1)+rightMargin + leftMargin; // 1 is for the cursor 

    return size;
    }

EXPORT_C TCoeInputCapabilities CEikSecretEditor::InputCapabilities() const
    {
    TCoeInputCapabilities inputCaps( 
        TCoeInputCapabilities::ESecretText|TCoeInputCapabilities::ENavigation,
        const_cast<CEikSecretEditor*>( this ),
        NULL );
        
    if ( iExtension )
        {
        inputCaps.SetObjectProvider( iExtension->iExtendedInputCapabilitiesProvider );
        }
    
    return inputCaps;
    }

EXPORT_C void CEikSecretEditor::GetText(TDes& aText) const
    //
    // Get the actual text typed
    //
    {
    // Check the buffer passed relative to the maximum number of characters enterable.
    // This will cause the panic to occur earlier and not depend upon how many characters 
    // have actually been entered
    __ASSERT_ALWAYS( aText.MaxLength() >= iMaxLen, Panic(EEikPanicSecretEditorTooLong));
    aText.Copy( *iSecCharArr );
    }

EXPORT_C void CEikSecretEditor::SetText( const TDesC& aText )
    {
    //
    // Initialize editor (the buffer and the display)
    //
    __ASSERT_ALWAYS( aText.Length() <= iMaxLen, Panic(EEikPanicSecretEditorTooLong));

    TPtr secCharArrAppend = iSecCharArr->Des();
    secCharArrAppend.Zero();
    iBuf.Zero();
    secCharArrAppend.Append( aText );
    InsertSecretChar();
    ReportUpdate();
    DrawDeferred();
    UpdateCursor();
    }

EXPORT_C void CEikSecretEditor::InitializeDisplay( TInt aNumberOfChars )
    {
    //
    // Initialize display with KSecretChars, doesn't affect the actual buffer.
    //
    __ASSERT_ALWAYS( aNumberOfChars <= iBuf.MaxLength(), Panic(EEikPanicSecretEditorTooLong));
    Reset();
    iBuf.Fill(KSecretChar, aNumberOfChars);
    ReportUpdate();
    DrawDeferred();
    }

EXPORT_C void CEikSecretEditor::Reset()
    //
    // Clear the text
    //
    {
    TPtr secCharArrAppend = iSecCharArr->Des();
    secCharArrAppend.Zero();
    iBuf.Zero();
    ReportUpdate();
    DrawDeferred();
	UpdateCursor();
    }

EXPORT_C void CEikSecretEditor::SetMaxLength(TInt aMaxLength)
    //
    // Set the maximum number of characters for the secret editor
    //
    {
    iMaxLen=aMaxLength;
    __ASSERT_ALWAYS(iMaxLen<=EMaxSecEdSecArrayLength, Panic(EEikPanicSecretEditorTooLong));
    
    // Docs claim that CEikSecretEditor's 2nd stage construction can be
    // done either by ConstructFromResourceL() or SetMaxLength().
    // We'll have to at least try to create extension here, sadly adding to the
    // iExtension creation mess already prevalent in this class.
    if ( !iExtension )
        {
        TRAP_IGNORE ( iExtension = CEikSecretEditorExtension::NewL() );
        }
    }

EXPORT_C void CEikSecretEditor::Draw(const TRect& /*aRect*/) const
    //
    // Draw the whole secret editor
    //
    {
    CWindowGc& gc=SystemGc();

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = NULL;

    TRgb textColor = iEikonEnv->ControlColor(EColorControlText, *this);
    TRgb bgColor = iEikonEnv->ControlColor(EColorControlBackground, *this);

    if( iExtension && iExtension->iBgContextSet )
        {
        cc = iExtension->iBgContext;
        }
    else
        {
        cc = AknsDrawUtils::ControlContext( this );
        }
 
    if (iExtension)
        {
        AknsUtils::GetCachedColor(skin, textColor, KAknsIIDQsnTextColors, iExtension->iAknSkinColorIndex); 
        AknsUtils::GetCachedColor(skin, bgColor, KAknsIIDQsnTextColors, iExtension->iSkinIdForBgColor);         
        }

    TBool drawn(EFalse);
    
    const MCoeControlBackground* backgroundDrawer = FindBackground();
	
    if ( !backgroundDrawer )
        {
        if ( CAknEnv::Static()->TransparencyEnabled() )
            {
            drawn = AknsDrawUtils::Background( skin, cc, this, gc, Rect(), KAknsDrawParamNoClearUnderImage );
            }
        else
            {
            drawn = AknsDrawUtils::Background( skin, cc, this, gc, Rect() );
            }
        }
    else
        {
        drawn = ETrue;
        }

    if( drawn )
        {
        gc.SetBrushStyle(CGraphicsContext::ENullBrush);        
        }
    else       
        {
        gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
        gc.SetBrushColor(bgColor); // KEikSecretEditorBackgroundColor
        iBorder.Draw(SystemGc(), Rect());
        }
    
    gc.SetPenColor(textColor);
    gc.UseFont(iFont);

    TSize size=iBorder.SizeDelta();

    if ( iRevealSecretText )
        {
        gc.DrawText( iSecCharArr->Des(), iExtension->iTextRect, 
            iAscent, iAlign, 0 );
        }
    else
        {
        gc.DrawText(iBuf, iExtension->iTextRect, iAscent, iAlign, 0);
        }
        
    gc.DiscardFont();    
    }

void CEikSecretEditor::InsertChar()
    {
    InsertSecretChar();
    TInt charsFit = CharsFitOnEditor();
    TInt pos = (iSecCharArr->Length() < charsFit ? iSecCharArr->Length()-1 : charsFit-1);
    if ( pos < 0 )
        return;
    iBuf.Replace(pos, 1, iSecCharArr->Right(1));
    }

void CEikSecretEditor::InsertSecretChar()
    {
    TInt charsFit = CharsFitOnEditor();
    TInt pos = (iSecCharArr->Length() < charsFit ? iSecCharArr->Length() : charsFit);
    iBuf.Fill(KSecretChar, pos);
    }

TInt CEikSecretEditor::CharsFitOnEditor() const
    {
    TRect rect=iBorder.InnerRect(Rect());
    const CFont* font=iFont;
    TInt ret = font->TextCount( KSecretCharString, rect.Width() );   
    return ((ret <= 1)? ret : ret-1); // there might be chars wider than asterisk visible.
    }

void CEikSecretEditor::ReportUpdate()
    {
    TRAP_IGNORE (
        iExtension->iExtendedInputCapabilities->ReportEventL(
        CAknExtendedInputCapabilities::MAknEventObserver::EControlContentUpdatedInternally,
        NULL );
        )
    }

EXPORT_C void CEikSecretEditor::AppendCharacterL( TInt aKeyCode )
    { // Replace this if a timer is not needed.
    if (!iTimer)
        iTimer=CPeriodic::NewL(CActive::EPriorityLow);
    if (iTimer->IsActive())
        Update();

    TPtr secCharArrAppend = iSecCharArr->Des();
    secCharArrAppend.Append( (TText)aKeyCode );
    iSecPos++;
    InsertChar();
    DrawDeferred();
    StartTimer();
    }

EXPORT_C void CEikSecretEditor::SizeChanged()
    {
    InsertSecretChar();
    //DrawNow();
    if ( iExtension )
        {
        iExtension->iTextRect = iBorder.InnerRect( Rect() );
        TAknTextDecorationMetrics metrics( iFont );
        TInt topMargin(0);
        TInt bottomMargin(0);
        TInt leftMargin(0);
        TInt rightMargin(0);

        metrics.GetTopAndBottomMargins( topMargin, bottomMargin );
        metrics.GetLeftAndRightMargins( leftMargin, rightMargin );

        iExtension->iTextRect.iTl.iY += topMargin;
        iExtension->iTextRect.iBr.iY -= bottomMargin;
        iExtension->iTextRect.iTl.iX += leftMargin;
        iExtension->iTextRect.iBr.iX -= rightMargin;
        }
    }

/**
 * Gets the list of logical colors employed in the drawing of the control,
 * paired with an explanation of how they are used. Appends the list to aColorUseList.
 *
 * @since ER5U 
 */
EXPORT_C void CEikSecretEditor::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const
    {
    CEikBorderedControl::GetColorUseListL(aColorUseList);

    TInt commonAttributes = TCoeColorUse::EContents|TCoeColorUse::EActive|TCoeColorUse::ENormal|TCoeColorUse::ENeutral;
    TCoeColorUse colorUse;

    colorUse.SetLogicalColor(EColorControlText);
    colorUse.SetUse(TCoeColorUse::EFore|commonAttributes);
    aColorUseList.AppendL(colorUse);

    colorUse.SetLogicalColor(EColorControlBackground);
    colorUse.SetUse(TCoeColorUse::EBack|commonAttributes);
    aColorUseList.AppendL(colorUse);
    }

/**
 * Handles a change to the control's resources of type aType
 * which are shared across the environment, e.g. colors or fonts.
 *
 * @since ER5U 
 */
EXPORT_C void CEikSecretEditor::HandleResourceChange(TInt aType)
    {
    // redraw if skin changes and skin control color has been set.
    if ( aType == KAknsMessageSkinChange && 
        iExtension && iExtension->iAknSkinColorIndex != KErrNotFound )
        {
        DrawDeferred(); // no hurry anyway.. 
        }
    if( aType == KEikDynamicLayoutVariantSwitch )
        {
        UpdateCursor();
        }
    
    CEikBorderedControl::HandleResourceChange(aType);
    }

EXPORT_C TInt CEikSecretEditor::MaxLength() const
    {
    return iMaxLen;
    }

EXPORT_C const TDesC& CEikSecretEditor::Buffer() const
    {
    return *iSecCharArr;
    }

EXPORT_C void CEikSecretEditor::RevealSecretText( TBool aReveal )
    {

    TBool oldShown = iRevealSecretText;
    iRevealSecretText = aReveal;

    if ( !COMPARE_BOOLS( oldShown, iRevealSecretText ) )
        {
        TInt caps = iExtension->iExtendedInputCapabilities->Capabilities();
        if ( iRevealSecretText )
            {            
            caps |= CAknExtendedInputCapabilities::EInputEditorRevealSecretText;
            }
        else
            {
            caps &= ~CAknExtendedInputCapabilities::EInputEditorRevealSecretText;
            }
        iExtension->iExtendedInputCapabilities->SetCapabilities( caps );
        // Work probably done in the Draw routine
        DrawDeferred();
        }
    }

EXPORT_C void CEikSecretEditor::EnableSCT( TBool aEnable )
    {
    if( iExtension )
        {
        TInt capabilities = iExtension->iExtendedInputCapabilities->Capabilities();
        if (aEnable)
            {
            capabilities &= ~CAknExtendedInputCapabilities::EDisableSCT;            
            }
        else
            {
            capabilities |= CAknExtendedInputCapabilities::EDisableSCT;
            }
        iExtension->iExtendedInputCapabilities->SetCapabilities( capabilities );
        }
    }


// -----------------------------------------------------------------------------
// CEikSecretEditor::SetSkinBackgroundControlContextL
// Sets the skin control context, and also constructs CEikSecretEditorExtension
// if not already available.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikSecretEditor::SetSkinBackgroundControlContextL(
    MAknsControlContext* aContext )
    {
    if( !iExtension )
        {
        iExtension = CEikSecretEditorExtension::NewL();
        }
    
    iExtension->iBgContext = aContext;
    iExtension->iBgContextSet = ETrue;
    }
    
EXPORT_C void CEikSecretEditor::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    if ( iFepState )
        {
        if ( aPointerEvent.iType == TPointerEvent::EButton1Down )
            {
            if ( iExtension 
              && iExtension->iFeedback )
                {
                // tactile feedback is always given on down event
                iExtension->iFeedback->InstantFeedback( this, ETouchFeedbackEditor );
                }
            
            CAknExtendedInputCapabilities::
                MAknEventObserver::TPointerEventReceivedParams params;
            params.iPointerEvent = aPointerEvent;
            
            if (IsFocused() && !iExtension->iDisablePenInput)
                {
                TRAP_IGNORE (
                    iExtension->iExtendedInputCapabilities->ReportEventL(
                        CAknExtendedInputCapabilities::MAknEventObserver::EPointerEventReceived,
                        &params );
                      )
                }
            }
        else if ( aPointerEvent.iType == TPointerEvent::EButton1Up && 
            iExtension && !iExtension->iDisablePenInput)
            {
            if (iExtension && iExtension->iFeedback)
                {
                // Edit feedback is given if PenInput will open on up event
                iExtension->iFeedback->InstantFeedback( this,
                                                        ETouchFeedbackEditor,
                                                        ETouchFeedbackVibra,
                                                        aPointerEvent );
                }
            TRAP_IGNORE( 
                static_cast<CAknEdwinState*>(iFepState)->ReportAknEdStateEventL( 
                    MAknEdStateObserver::EAknActivatePenInputRequest ) 
                );
            }
        }

    CEikBorderedControl::HandlePointerEventL(aPointerEvent); 
    }    

EXPORT_C void* CEikSecretEditor::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CEikSecretEditor::Reserved_1()
    {}

EXPORT_C void CEikSecretEditor::Reserved_2()
    {}

EXPORT_C void CEikSecretEditor::StartFepInlineEditL(const TDesC& aInitialInlineText, TInt /*aPositionOfInsertionPointInInlineText*/, TBool /*aCursorVisibility*/, const MFormCustomDraw* /*aCustomDraw*/, MFepInlineTextFormatRetriever& /*aInlineTextFormatRetriever*/, MFepPointerEventHandlerDuringInlineEdit& /*aPointerEventHandlerDuringInlineEdit*/)
    {
    delete iInlineEditText;
    iInlineEditText = NULL;
    iInlineEditText = aInitialInlineText.AllocL();
    }

EXPORT_C void CEikSecretEditor::UpdateFepInlineTextL(const TDesC& aNewInlineText, TInt /*aPositionOfInsertionPointInInlineText*/)
    {
    delete iInlineEditText;
    iInlineEditText = NULL;
    iInlineEditText = aNewInlineText.AllocL();
    }

EXPORT_C void CEikSecretEditor::SetInlineEditingCursorVisibilityL(TBool /*aCursorVisibility*/)
    {
    }

EXPORT_C void CEikSecretEditor::CancelFepInlineEdit()
    {
    }

EXPORT_C TInt CEikSecretEditor::DocumentLengthForFep() const
    {
    return iSecCharArr->Length();
    }

EXPORT_C TInt CEikSecretEditor::DocumentMaximumLengthForFep() const
    {
    return MaxLength();
    }

EXPORT_C void CEikSecretEditor::SetCursorSelectionForFepL(const TCursorSelection& /*aCursorSelection*/)
    {
    }

EXPORT_C void CEikSecretEditor::GetCursorSelectionForFep(TCursorSelection& aCursorSelection) const
    {
    aCursorSelection.iCursorPos = iSecCharArr->Length();
    aCursorSelection.iAnchorPos = iSecCharArr->Length();
    }

EXPORT_C void CEikSecretEditor::GetEditorContentForFep(TDes& aEditorContent, TInt aDocumentPosition, TInt aLengthToRetrieve) const
    {
    aEditorContent = iSecCharArr->Mid(aDocumentPosition).Left(aLengthToRetrieve);
    }

EXPORT_C void CEikSecretEditor::GetFormatForFep(TCharFormat& /*aFormat*/, TInt /*aDocumentPosition*/) const
    {
    }

EXPORT_C void CEikSecretEditor::GetScreenCoordinatesForFepL(TPoint& /*aLeftSideOfBaseLine*/, TInt& /*aHeight*/, TInt& /*aAscent*/, TInt /*aDocumentPosition*/) const
    {
    }

EXPORT_C void CEikSecretEditor::DoCommitFepInlineEditL()
    {
    if (iInlineEditText)
        {
        for (TInt i=0; i<iInlineEditText->Length(); i++)
            {
            if (iSecCharArr->Length()<iMaxLen)
                AppendCharacterL((*iInlineEditText)[i]);
            }
        ReportEventL(MCoeControlObserver::EEventStateChanged);
        }
    delete iInlineEditText;
    iInlineEditText = NULL;
    }

EXPORT_C MCoeFepAwareTextEditor_Extension1* CEikSecretEditor::Extension1(TBool& aSetToTrue)
    {
    aSetToTrue=ETrue;
    return this;
    }

EXPORT_C void CEikSecretEditor::SetStateTransferingOwnershipL(CState* aState, TUid /*aTypeSafetyUid*/)
    {
    if (iFepState)
        delete iFepState;
    iFepState=aState;
    }

EXPORT_C MCoeFepAwareTextEditor_Extension1::CState* CEikSecretEditor::State(TUid /*aTypeSafetzyUid*/)
    {
    return iFepState;
    }

EXPORT_C MCoeFepAwareTextEditor_Extension1::CState* CEikSecretEditor::CreateFepStateL()
    {
    CAknEdwinState* editorState = new(ELeave) CAknEdwinState();

    // The status of AknLayoutUtils::Variant() is no longer checked -> Both
    // European and APAC variants enable EAknEditorFlagLatinInputModesOnly.
    editorState->SetFlags( EAknEditorFlagNoLRNavigation |
                           EAknEditorFlagLatinInputModesOnly |
                           EAknEditorFlagNoT9 |
                           EAknEditorFlagUseSCTNumericCharmap );

    editorState->SetDefaultInputMode(EAknEditorSecretAlphaInputMode);
    editorState->SetCurrentInputMode(EAknEditorSecretAlphaInputMode);
    editorState->SetPermittedCases(EAknEditorLowerCase|EAknEditorUpperCase);
    editorState->SetCurrentCase(EAknEditorLowerCase);    
    editorState->SetPermittedInputModes(EAknEditorSecretAlphaInputMode | EAknEditorNumericInputMode);
    editorState->SetDefaultCase(EAknEditorLowerCase);
    editorState->SetSpecialCharacterTableResourceId(R_AVKON_SPECIAL_CHARACTER_TABLE_DIALOG_LATIN_ONLY);    
    editorState->SetNumericKeymap(EAknEditorPlainNumberModeKeymap);
    editorState->SetObjectProvider(this);
    
    return editorState;
    }

EXPORT_C void CEikSecretEditor::MCoeFepAwareTextEditor_Reserved_2()
    {
    }

EXPORT_C void CEikSecretEditor::MCoeFepAwareTextEditor_Extension1_Reserved_2()
    {
    }

EXPORT_C void CEikSecretEditor::MCoeFepAwareTextEditor_Extension1_Reserved_3()
    {
    }

EXPORT_C void CEikSecretEditor::MCoeFepAwareTextEditor_Extension1_Reserved_4()
    {
    }

void CEikSecretEditor::CalculateAscent()
    {
    const CAknLayoutFont* layoutFont = CAknLayoutFont::AsCAknLayoutFontOrNull( iFont );
    if ( layoutFont )
        iAscent = layoutFont->TextPaneTopToBaseline();
    else
        iAscent = iFont->AscentInPixels();
    }
    
EXPORT_C void CEikSecretEditor::SetSkinTextColorL(TInt aAknSkinIDForTextColor, TInt aAknSkinIdForBgColor )
    {
    if( !iExtension )
        {
        iExtension = CEikSecretEditorExtension::NewL();
        }
        
    iExtension->iAknSkinColorIndex = aAknSkinIDForTextColor;
    iExtension->iSkinIdForBgColor = aAknSkinIdForBgColor;
    
    
    // if we are already visible, try to apply new color
    if (IsVisible())
        {
        DrawDeferred();
        }
    }


EXPORT_C TInt CEikSecretEditor::SetFeature( TInt aFeatureId, TInt aFeatureParam )
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
            case EDisablePenInput:
                if ( iExtension )
                    {
                    iExtension->iDisablePenInput = aFeatureParam;
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
                if ( iFepState && iExtension )
                    {
                    iExtension->iPartialScreenInput = aFeatureParam;
                    CAknEdwinState* state( static_cast<CAknEdwinState*>( iFepState ) );
                    TInt flags( state->Flags() );
                    if ( aFeatureParam )
                        {
                        flags |= EAknEditorFlagEnablePartialScreen;
                        }
                    else
                        {
                        flags &= ~EAknEditorFlagEnablePartialScreen;
                        }
                    state->SetFlags( flags );
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

EXPORT_C TInt CEikSecretEditor::GetFeature( TInt aFeatureId, TInt& aFeatureParam ) const
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

EXPORT_C TBool CEikSecretEditor::SupportsFeature( TInt aFeatureId ) const
    {
    // This is done so that there is an option of leaving out
    // a feature instead of using the enum TFeatureId, although
    // for simplified BC that will probably never be done.
    const TInt supportedFeatures[] = 
        {
        EDisablePenInput,
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

void CEikSecretEditor::SetCursorFormat()
    {    
    iExtension->iCursor.iType = TTextCursor::ETypeRectangle;        
    iExtension->iCursor.iFlags = 0;    
    iExtension->iCursor.iHeight = AknLayoutUtils::CursorHeightFromFont( 
        iFont->FontSpecInTwips() );
    iExtension->iCursor.iAscent = AknLayoutUtils::CursorAscentFromFont( 
        iFont->FontSpecInTwips() );
    iExtension->iCursor.iWidth  = AknLayoutUtils::CursorWidthFromFont ( 
        iFont->FontSpecInTwips() );
    iExtension->iCursor.iColor = KRgbWhite;
    if ( !iExtension->iWindowSet )
        {
#ifdef RD_UI_TRANSITION_EFFECTS_PHASE2
        CRedirectionListener* listener = ( CRedirectionListener* )
        CAknTransitionUtils::GetData( (TInt) this );
        listener->SetWindows( &( iCoeEnv->RootWin() ), DrawableWindow() );
#else           
        iExtension->iWg = &( iCoeEnv->RootWin() );
        iExtension->iWindow = DrawableWindow();
#endif
        iExtension->iWindowSet = ETrue;
        }
    }

TPoint CEikSecretEditor::CursorPos()
    {
    TInt charsFit = CharsFitOnEditor();
    TInt pos = ( iSecCharArr->Length() < charsFit ? 
        iSecCharArr->Length() : charsFit );
    TInt textWidth( iRevealSecretText ? 
        iFont->TextWidthInPixels( *iSecCharArr ) : 
        iFont->CharWidthInPixels( KSecretChar ) * pos );
    TInt x;
    if ( iAlign == CGraphicsContext::ELeft )
    	{
        x = iExtension->iTextRect.iTl.iX + textWidth;
    	}
    else if (iAlign == CGraphicsContext::ECenter)
    	{
        x = iExtension->iTextRect.iTl.iX +
            (iExtension->iTextRect.Width() + textWidth) / 2;
    	}
    else
    	{
    	x = iExtension->iTextRect.iBr.iX;
    	}
    TInt y( Rect().iTl.iY + iAscent );    
    return TPoint( x, y );
    }

EXPORT_C void CEikSecretEditor::EnableCursor( TBool aEnable )
    {        
    if ( !iExtension )
        {
        TRAPD( errorCode, iExtension = CEikSecretEditorExtension::NewL() );
        if ( KErrNone != errorCode )
            {
            return;
            }
        }
#ifdef RD_UI_TRANSITION_EFFECTS_PHASE2
        TRAPD( errorCode, InitCRedirectionListenerL() );
        if ( KErrNone != errorCode )
            {
            return;
            }
        CRedirectionListener* listener = ( CRedirectionListener* )
            CAknTransitionUtils::GetData( (TInt) this );
#endif
    
    if ( aEnable )
        {
        SetCursorFormat();
#ifdef RD_UI_TRANSITION_EFFECTS_PHASE2
        listener->EnableCursor();
#else
        iExtension->iCursorEnabled = ETrue;        
#endif        
        UpdateCursor();
        }
    else
        {
#ifdef RD_UI_TRANSITION_EFFECTS_PHASE2
        listener->DisableCursor();
#else
        if ( iExtension->iCursorEnabled )
            {
            iExtension->iWg->CancelTextCursor();
            iExtension->iCursorEnabled = EFalse;
            }
#endif        
        }
  if ( iFepState )
        {
        CAknEdwinState* edwinState( static_cast<CAknEdwinState*>(
            iFepState ) );
        TInt flags( edwinState->Flags() );
        if ( aEnable )
            {
            flags &= ~EEikEdwinAvkonDisableCursor;
            }
        else
            {
            flags |= EEikEdwinAvkonDisableCursor;
            }
        edwinState->SetFlags( flags );
        }    
    }

void CEikSecretEditor::UpdateCursor()
    {
#ifdef RD_UI_TRANSITION_EFFECTS_PHASE2
    CRedirectionListener* listener = ( CRedirectionListener* )
        CAknTransitionUtils::GetData( (TInt) this );
    listener->UpdateCursor( iExtension->iCursor );
#else
    if ( iExtension->iCursorEnabled )
        {                
        if ( iExtension->iWindow )
            {            
            iExtension->iWg->SetTextCursor( *iExtension->iWindow, CursorPos(), 
                iExtension->iCursor );            
            }
        iExtension->iCursorEnabled = ETrue;
        }
#endif       
    }

EXPORT_C void CEikSecretEditor::FocusChanged( TDrawNow /*aDrawNow*/ )
    {
    EnableCursor( IsFocused() );        
    if ( IsFocused() && iExtension && !iExtension->iDisablePenInput && 
        iExtension->iLaunchPenInputAutomatic )
        {
        TRAP_IGNORE( 
            static_cast<CAknEdwinState*>(iFepState)->ReportAknEdStateEventL( 
                MAknEdStateObserver::EAknActivatePenInputRequest ) 
            );
        }
    }
    
void CEikSecretEditor::InitCRedirectionListenerL()
    {
#ifdef RD_UI_TRANSITION_EFFECTS_PHASE2
    CRedirectionListener* listener = ( CRedirectionListener* )
        CAknTransitionUtils::GetData( (TInt) this );    
    if(!listener)
    	{
        // Create listener that listen for redirection changes
    	CRedirectionListener* listener = new (ELeave) CRedirectionListener( *this );
        User::LeaveIfError( CAknTransitionUtils::SetData( (TInt) this,
            (TDesC8*) listener ) );
        User::LeaveIfError( CAknTransitionUtils::AddObserver( listener,
            CAknTransitionUtils::EEventWsBufferRedirection ) );
    	} 
#endif
    }
