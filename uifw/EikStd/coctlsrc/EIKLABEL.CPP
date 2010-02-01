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


#include <eiklabel.h>
#include <coeutils.h>
#include <eikenv.h>
#include <eikpanic.h>
#include <barsread.h>
#include <uikon.hrh>
#include "laflabel.h"

#include <gulcolor.h>
#include <AknUtils.h>

#include <bidivisual.h> 
#include <biditext.h>
#include <AknBidiTextUtils.h>

#include <AknPictographInterface.h>
#include <AknPictographDrawerInterface.h>
#include <AknLayoutFont.h>

const TInt KTextEmphasisMask		= 0x30;
const TInt KTextBufferReserveLength = 0x40;


/* This class needs to be in .cpp file so that we
   do not accidentally make it derivable; that would
   destroy all the binary compability advantages this
   class has..
   */
NONSHARABLE_CLASS(CEikLabelExtension) : public CBase
	{
public: // enums
    enum {
        ECropText,
        EUseDynamicBidiTextAlignment,
        EUseBrushStyle
        };
public:
	static CEikLabelExtension* NewL();
	~CEikLabelExtension();
	void SetTextLengthL(TInt aLength);

private:
	CEikLabelExtension();
	void ConstructL();
public: //data
	HBufC* iLabelLine;
    TBitFlags iFlags;
    CWindowGc::TBrushStyle iBrushStyle;
    CAknPictographInterface* iPictographInterface; // not owned
	};

CEikLabelExtension* CEikLabelExtension::NewL()
	{
	CEikLabelExtension* self = new(ELeave) CEikLabelExtension;
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

CEikLabelExtension::CEikLabelExtension()
	{
    iFlags.ClearAll();
	}

CEikLabelExtension::~CEikLabelExtension()
	{
	delete iLabelLine;
	}

void CEikLabelExtension::ConstructL()
	{
	iLabelLine = HBufC::NewL(0);
	}

void CEikLabelExtension::SetTextLengthL(TInt aLength)
	{
    aLength += TBidiLogicalToVisual::KMinCharAvailable;
	if (aLength <= iLabelLine->Des().MaxLength())
		return;

	HBufC* tempBuf = HBufC::NewL(aLength);
	delete iLabelLine;
	iLabelLine = tempBuf;
	}

/**
 * Gets the list of logical colors employed in the drawing of the control,
 * paired with an explanation of how they are used. Appends the list to aColorUseList.
 *
 * @since ER5U 
 */
EXPORT_C void CEikLabel::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const
	{
	CCoeControl::GetColorUseListL(aColorUseList);

	TInt commonAttributes = TCoeColorUse::ESurrounds|TCoeColorUse::ENormal|TCoeColorUse::ENeutral;
	TCoeColorUse colorUse;

	colorUse.SetLogicalColor(EColorLabelText);
	colorUse.SetUse(TCoeColorUse::EFore|TCoeColorUse::EActive|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorControlBackground);
	colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::EActive|commonAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorLabelDimmedText);
	colorUse.SetUse(TCoeColorUse::EFore|TCoeColorUse::EDimmed|commonAttributes);
	aColorUseList.AppendL(colorUse);

	TInt highlightAttributes = TCoeColorUse::EHighlights|TCoeColorUse::ENormal|TCoeColorUse::ENeutral;

	colorUse.SetLogicalColor(EColorLabelTextEmphasis);
	colorUse.SetUse(TCoeColorUse::EFore|TCoeColorUse::EActive|highlightAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorLabelHighlightFullEmphasis);
	colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::EActive|highlightAttributes);
	aColorUseList.AppendL(colorUse);

	colorUse.SetLogicalColor(EColorLabelHighlightPartialEmphasis);
	colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::EDimmed|highlightAttributes);
	aColorUseList.AppendL(colorUse);
	}

/**
 * Handles a change to the control's resources of type aType
 * which are shared across the environment, e.g. colors or fonts.
 *
 * @since ER5U 
 */
EXPORT_C void CEikLabel::HandleResourceChange(TInt aType)
	{
	CCoeControl::HandleResourceChange(aType);
	}

EXPORT_C CEikLabel::~CEikLabel()
	{
	delete iText;
	delete iExtension;
 	}

EXPORT_C CEikLabel::CEikLabel()	: 
    iLabFlags( EUseLogicalToVisualConversion ),
    iGapBetweenLines( LafLabel::DefaultGapBetweenLines() )
	{
	__DECLARE_NAME(_S("CEikLabel"));
	iFont=iCoeEnv->NormalFont();
	}

EXPORT_C void CEikLabel::SetLabelAlignment(TInt aAlignment)
	{
    if (CheckAndCreateExtension())
        iExtension->iFlags.Assign(CEikLabelExtension::EUseDynamicBidiTextAlignment, (aAlignment == ELayoutAlignBidi));

    switch(aAlignment)
        {
        case ELayoutAlignBidi: // alignment handled above in extension above
            break;
        default:
            SetAlignment(AknLayoutUtils::GulAlignFromId(aAlignment));
            break;
        }
	}

EXPORT_C void CEikLabel::SetBrushStyle(CWindowGc::TBrushStyle aBrushStyle)
    {
    if (CheckAndCreateExtension())
        {
        iExtension->iBrushStyle = aBrushStyle;
        iExtension->iFlags.Set(CEikLabelExtension::EUseBrushStyle);
        }
    }

EXPORT_C void CEikLabel::SetBrushStyleFromContext()
    {
    if (CheckAndCreateExtension()) // can't be sure creation above passed
        {
        iExtension->iFlags.Clear(CEikLabelExtension::EUseBrushStyle);
        }
    }

EXPORT_C void CEikLabel::ConstructFromResourceL(TResourceReader& aReader)
	{
	TInt flags=aReader.ReadInt16();
	SetUnderlining(flags&EikLabelUnderline);
	SetStrikethrough(flags&EikLabelStrikeThrough);
	iAlignment.SetHAlignment((TGulHAlignment)aReader.ReadInt16());
	iAlignment.SetVAlignment((TGulVAlignment)aReader.ReadInt16());
	TInt standardFont=aReader.ReadInt16();
	switch (standardFont)
		{
	case EEikLabelFontLegend:
		iFont=iEikonEnv->LegendFont();
		break;
	case EEikLabelFontAnnotation:
		iFont=iEikonEnv->AnnotationFont();
		break;
	default:
		break;
		}
	TInt length=aReader.ReadInt16();
	if (length)
		SetBufferReserveLengthL(length);
	SetTextL(aReader.ReadTPtrC());
	}
       
EXPORT_C void CEikLabel::SetTextL(const TDesC& aText)
	{
	__ASSERT_DEBUG(&aText,Panic(EEikPanicLabelNullText));
	
	if (iLabFlags&KTextBufferReserveLength || 
		(iText && iText->Des().MaxLength() >= aText.Length()))
		{
        *iText=aText; // will panic if not long enough
		}
    else
        {
        User::LeaveIfError( AknBidiTextUtils::PrepareRunInfoArray( aText ) );

        HBufC* newText=aText.AllocL();
	    delete(iText); // after the AllocL succeeds
	    iText=newText;

		if ( !iExtension )
			{
			iExtension = CEikLabelExtension::NewL();
			}
		iExtension->SetTextLengthL(iText->Length());
        }
    if (iExtension)
        iExtension->iFlags.Clear(CEikLabelExtension::ECropText); // reset ECropText
    iNumberOfLines=1;
    TPtrC ptr=(*iText);
    FOREVER
        {
        const TInt offset=ptr.Locate('\n');
        if (offset<0 || offset==ptr.Length()-1)
            break;
        iNumberOfLines++;
        ptr.Set(ptr.Mid(offset+1));
        }
	return ;
 	}

EXPORT_C void CEikLabel::CropText()
	{
	if ( iExtension ) // if no extension do nothing as SetTextL has not yet been called
		iExtension->iFlags.Set(CEikLabelExtension::ECropText);
	}
	
TInt CEikLabel::HeightInPixels() const
    {
    return(iMargin.iTop+iMargin.iBottom + iGapBetweenLines*(iNumberOfLines-1) + iNumberOfLines*iFont->HeightInPixels());
    }

TInt CEikLabel::WidthInPixels(TPtrC& aText) const
    {
    TInt maxLineWidth=0;

    FOREVER
        {
        const TInt offset=aText.Locate('\n');
        TPtrC left=aText;
        if (offset>=0)
            left.Set(aText.Left(offset));

        CFont::TMeasureTextInput input;
        if ( !(iLabFlags & EUseLogicalToVisualConversion) )
            {
            input.iFlags = CFont::TMeasureTextInput::EFVisualOrder;
            }
        TInt thisWidth = iFont->MeasureText( left, &input );

        if (thisWidth>maxLineWidth)
            maxLineWidth=thisWidth;
        if (offset<0 || offset==aText.Length()-1)
            break;
        aText.Set(aText.Mid(offset+1));
        }
    return(iMargin.iLeft + iMargin.iRight + maxLineWidth);
    }

TInt CEikLabel::HeightInPixels(const TDesC& aText) const
    {
    // Calculate amount of lines in aText
    TInt numberOfLines = 1;
    TPtrC ptr=aText;
    FOREVER
        {
        const TInt offset=ptr.Locate('\n');
        if (offset<0 || offset==ptr.Length()-1)
            break;
        numberOfLines++;
        ptr.Set(ptr.Mid(offset+1));
        }

    // Calculate height.
    return(iMargin.iTop+iMargin.iBottom + iGapBetweenLines*(numberOfLines-1) + numberOfLines*iFont->HeightInPixels());
    }

EXPORT_C void CEikLabel::Draw( const TRect& /*aRect*/ ) const
    {
    CWindowGc& gc = SystemGc();
    DrawToContext( gc, NULL );
    gc.SetOpaque( EFalse ); // transparency back on
    }


void CEikLabel::DrawToContext( CBitmapContext& aContext, 
        const TRgb* aOverrideColor ) const
    {
    __ASSERT_ALWAYS(iText,Panic(EEikPanicLabelNullText));
    TInt textTooLong = KErrNone;
    if (iExtension->iLabelLine->Des().MaxLength() < iText->Length() + TBidiLogicalToVisual::KMinCharAvailable)
        {
        TRAP(textTooLong, iExtension->SetTextLengthL(iText->Length()));
        } // textTooLong condition is handled later in this function, tries to recover as much as possible

    TBool outlineEffectOn = EFalse;
    const CAknLayoutFont* layoutFont = CAknLayoutFont::AsCAknLayoutFontOrNull( iFont ); 
    if (layoutFont) 
        {
        outlineEffectOn = layoutFont->FontSpecification().IsOutlineEffectOn(); 
        }

    CBitmapContext& gc = aContext;
    if (IsStrikethrough())
        {
        gc.SetStrikethroughStyle(EStrikethroughOn);
        }
    else
        {
        gc.SetStrikethroughStyle(EStrikethroughOff);
        }

    if (IsUnderlined())
        {
        gc.SetUnderlineStyle(EUnderlineOn);
        }
    else
        {
        gc.SetUnderlineStyle(EUnderlineOff);
        }
    
    if ( aOverrideColor )
        {
        gc.SetPenColor(*aOverrideColor);
        gc.SetBrushColor(*aOverrideColor);
        }
    else if ((iLabFlags&KTextEmphasisMask) != ENoEmphasis)
        {
        SetupGcForEmphasis(gc);
        }
    else
        {
        TRgb penColor;
        TRgb brushColor;
        if (IsDimmed()) 
            {
            penColor = iEikonEnv->ControlColor(EColorLabelDimmedText,*this); 
            brushColor = iEikonEnv->ControlColor(EColorControlDimmedBackground,*this); 
            }
        else
            {
            penColor = iEikonEnv->ControlColor(EColorLabelText,*this); 
            brushColor = iEikonEnv->ControlColor(EColorControlBackground,*this); 
            }
        if(outlineEffectOn)
            {
            ConvertColorsForOutlineEffect(penColor, brushColor); 
            }
        gc.SetPenColor(penColor); 
        gc.SetBrushColor(brushColor); 
        }

    
    gc.UseFont(iFont);

    if (iExtension->iFlags.IsSet(CEikLabelExtension::EUseBrushStyle))
        {
        gc.SetBrushStyle(iExtension->iBrushStyle);
        }
    
    const TRect rect = Rect();

    const TInt deltaHeight=rect.Height()-HeightInPixels();
    TInt preHeight=iMargin.iTop; // used on first line
    TInt postHeight=iMargin.iBottom; // used on last line
    if (deltaHeight>0)
        {
        switch(iAlignment.VAlignment())
            {
            case EVTop:
                postHeight+=deltaHeight;
                break;
            case EVBottom:
                preHeight+=deltaHeight;
                break;
            case EVCenter:
                TInt postInc=deltaHeight/2; // give odd pixel to pre-Height
                preHeight+=deltaHeight-postInc;
                postHeight+=postInc;
            }
        }
    TInt lineNo=0;
    
    TPtrC ptr=(*iText);
    TRect box=rect;
    TBool clippedAtBottom=EFalse;
    TInt textPaneTopToBaseline(0);
    TInt textPaneHeight(0);
    
    if ( layoutFont )
        {
        textPaneTopToBaseline = layoutFont->TextPaneTopToBaseline();
        textPaneHeight = layoutFont->TextPaneHeight();
        }
    else
        {
        textPaneTopToBaseline = iFont->AscentInPixels();
        textPaneHeight = iFont->HeightInPixels();
        }
    
    // iGapBetweenLines is defined as baseline separation - CFont::HeightInPixels
    // Since we are using the better metrics above, we have to actually use something which is 
    // derived from iGapBetweenLines, but is e.g. reduced if textpaneheight > heightInPixels
    TInt gapBetweenTextPanes( iGapBetweenLines - (textPaneHeight - iFont->HeightInPixels()) );

    FOREVER
        {
        TInt ascent=textPaneTopToBaseline+preHeight;
        TInt lineHeight=textPaneHeight+preHeight;
        if (++lineNo==iNumberOfLines)
            {
            lineHeight+=postHeight;
            }
        
        TInt off=ptr.Locate('\n');
        TPtrC left=ptr;
        if (off>=0)
            {
            left.Set(ptr.Left(off));
            }
        
        box.iBr.iY=box.iTl.iY+lineHeight;
        if (box.iBr.iY>rect.iBr.iY)
            {
            box.iBr.iY=rect.iBr.iY;
            clippedAtBottom=ETrue;
            }
        
        CGraphicsContext::TTextAlign align=iAlignment.TextAlign();
        TInt margin = iMargin.iLeft;
        
        TBidiText::TDirectionality labelDirectionality = TBidiText::TextDirectionality(*iText);
        if (iExtension->iFlags.IsSet(CEikLabelExtension::EUseDynamicBidiTextAlignment))
            {
            switch(labelDirectionality)
                {
                case TBidiText::ELeftToRight:
                    align = CGraphicsContext::ELeft;
                    break;
                case TBidiText::ERightToLeft:
                    align = CGraphicsContext::ERight;
                    break;
                default:
                    break; // do nothing
                }
            }
        
        if (align==CGraphicsContext::ERight)
            {
            margin = iMargin.iRight;
            }
        else if (align==CGraphicsContext::ECenter)
            {
            margin -= iMargin.iRight;
            }
        
        TRect adjustedBox( box ) ;  // create a new box to accommodate underline if present (without affecting layout)
        if ( IsUnderlined() )
            {
            TAknTextDecorationMetrics decoration(iFont);
            TInt underlineWidth = decoration.UnderlineHeight();
            TInt underlineSpace = decoration.BaselineToUnderlineOffset();
            
            if (  ( textPaneTopToBaseline + underlineSpace ) > textPaneHeight )
                {
                adjustedBox.iBr.iY += (  textPaneTopToBaseline + underlineSpace - textPaneHeight ) ;
                }
            }
        
        TPtr text = iExtension->iLabelLine->Des();
        TInt textMaxLength = text.MaxLength();
        TBool dontDoComplicatedDraw = EFalse;
        
        TInt usableLength = 0;
        if (textTooLong == KErrNone || textMaxLength >= left.Length() + TBidiLogicalToVisual::KMinCharAvailable)
            {
            usableLength = left.Length(); // no problem with memory
            }
        else
            { // problem with lack of memory so find a usable length.
            if (labelDirectionality == TBidiText::ELeftToRight || !(iLabFlags & EUseLogicalToVisualConversion))
                { // most likely western text so just display logically (no truncation)
                dontDoComplicatedDraw = ETrue;
                }
            else
                { // most likely NOT western text so display as much visually as possible
                if (textMaxLength > TBidiLogicalToVisual::KMinCharAvailable)
                    {
                    usableLength = textMaxLength - TBidiLogicalToVisual::KMinCharAvailable;
                    }
                else // there is no buffer so give up and draw logically
                    {
                    dontDoComplicatedDraw = ETrue;
                    }
                }
            }
        
        if (dontDoComplicatedDraw)
            {
            gc.DrawText( left, adjustedBox, ascent, align, margin );
            if ( iExtension->iPictographInterface )
                {
                iExtension->iPictographInterface->Interface()->DrawPictographsInText(
                    gc, *iFont, left, adjustedBox, ascent, align, margin );
                }
            }
        else
            { // we have some buffer space to try and draw text correctly
            TPtrC usableText=left.Left(usableLength);
            TInt adjustedBoxWidth = adjustedBox.Size().iWidth;
            
            if (iLabFlags & EUseLogicalToVisualConversion)
                {
                if (iExtension->iFlags.IsSet(CEikLabelExtension::ECropText))
                    {
                    AknBidiTextUtils::ConvertToVisualAndClip(usableText, text, *iFont, adjustedBoxWidth, adjustedBoxWidth);
                    }
                else
                    {
                    const TUint KEmptyChar = TUint(0xFFFF);
                    AknBidiTextUtils::ConvertToVisualAndClip(usableText, text, *iFont, adjustedBoxWidth, adjustedBoxWidth, AknBidiTextUtils::EImplicit, KEmptyChar );
                    }
                }
            else
                {
                text = usableText; // copy
                }
            gc.DrawText( text, adjustedBox, ascent, align, margin );
            if ( iExtension->iPictographInterface )
                {
                iExtension->iPictographInterface->Interface()->DrawPictographsInText(
                    gc, *iFont, text, adjustedBox, ascent, align, margin );
                }
            }
        
        
        if (off<0 || off==ptr.Length()-1 || clippedAtBottom)
            break;
        
        ptr.Set(ptr.Mid(off+1));
        box.iTl.iY=box.iBr.iY;
        
        preHeight=gapBetweenTextPanes;
        }
    
    gc.DiscardFont();
    }

EXPORT_C void CEikLabel::SetBufferReserveLengthL(TInt aLength)
	{
	if (iText)
		iText=iText->ReAllocL(aLength);
	else
		iText=HBufC::NewL(aLength);
	iLabFlags|=KTextBufferReserveLength;
	iReserveLength=aLength;
	if ( !iExtension )
		{
		iExtension = CEikLabelExtension::NewL();
		}
	iExtension->SetTextLengthL(iText->Length());
	}

EXPORT_C void CEikLabel::SetFont(const CFont* aFont) 
	{
	iFont=aFont;
	}

EXPORT_C TSize CEikLabel::CalcMinimumSize(TPtrC& aText) const
    {
    // HeightInPixels does not modify aText.
    const TInt height = HeightInPixels(aText);

    // Note that WidthInPixels modifies aText and so
    // it must be called after HeightInPixels.
    const TInt width = WidthInPixels(aText);
    return TSize( width, height );
    }

EXPORT_C void CEikLabel::SetEmphasis(TTextEmphasis aEmphasis)
	{
    iLabFlags&=(~KTextEmphasisMask);
    iLabFlags|=aEmphasis;
	}

EXPORT_C TSize CEikLabel::MinimumSize()
	{
	__ASSERT_ALWAYS(iText,Panic(EEikPanicLabelNullText));
	TPtrC ptr=(*iText);
	iSize=TSize(WidthInPixels(ptr),HeightInPixels());
	return(iSize);
	}

EXPORT_C void CEikLabel::SetPixelGapBetweenLines(TInt aGap)
	{
	iGapBetweenLines=aGap;
	}

EXPORT_C TInt CEikLabel::PixelGapBetweenLines() const
	{
	return iGapBetweenLines;
	}

EXPORT_C void CEikLabel::SetUnderlining(TBool aUnderLining)
	{
	if (aUnderLining) {iLabFlags|=EUnderlining;}
        else iLabFlags&=(~EUnderlining);
	}

EXPORT_C void CEikLabel::SetStrikethrough(TBool aStrikethrough)
	{
	if (aStrikethrough) {iLabFlags|=EStrikethrough;}
        else iLabFlags&=(~EStrikethrough);
	}

EXPORT_C TInt CEikLabel::BufferReserveLength() const
	{
	return (iLabFlags&KTextBufferReserveLength? iReserveLength : 0);
	}

EXPORT_C void CEikLabel::UseLogicalToVisualConversion( TBool aUseConversion )
    {
    if ( aUseConversion )
        {
        iLabFlags |= EUseLogicalToVisualConversion;
        }
    else
        {
        iLabFlags &= (~EUseLogicalToVisualConversion);
        }
    }

EXPORT_C TBool CEikLabel::LogicalToVisualConversionUsed() const
    {
    return iLabFlags & EUseLogicalToVisualConversion;
    }

EXPORT_C void CEikLabel::EnablePictographsL( CAknPictographInterface& aInterface )
    {
    if ( !iExtension )
        {
        iExtension = CEikLabelExtension::NewL();
        }

    iExtension->iPictographInterface = &aInterface;
    }

EXPORT_C void CEikLabel::DisablePictographs()
    {
    if ( iExtension )
        {
        iExtension->iPictographInterface = NULL;
        }
    }

void CEikLabel::SetupGcForEmphasis(CGraphicsContext& aGc) const
	{
    TRgb penColor;
    TRgb brushColor; 

    penColor = (iEikonEnv->ControlColor(EColorLabelTextEmphasis,*this)); 
    if ((iLabFlags&KTextEmphasisMask) == EFullEmphasis) 
        {
        brushColor = (iEikonEnv->ControlColor(EColorLabelHighlightFullEmphasis,*this)); 
        }
    else
        {
        brushColor = (iEikonEnv->ControlColor(EColorLabelHighlightPartialEmphasis,*this)); 
        }
    
    aGc.SetPenColor(penColor); 
    aGc.SetBrushColor(brushColor);
    aGc.SetBrushStyle(CGraphicsContext::ESolidBrush); 
    }

TBool CEikLabel::CheckAndCreateExtension()
    {
	if (!iExtension)
		{
		TRAP_IGNORE(iExtension = CEikLabelExtension::NewL());
		}
    return (iExtension != NULL);
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
EXPORT_C void CEikLabel::WriteInternalStateL(RWriteStream&) const
	{}
#else
EXPORT_C void CEikLabel::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	_LIT(KLitEikLblCtlStart, "<CEiklabel>");
	_LIT(KLitEikLblCtlEnd, "<\\CEikLabel>");

	_LIT(KLitEikLblTxt,"<iText>");
	_LIT(KLitEikLblTxtEnd,"<\\iText>");
	_LIT(KLitEikLblFnt,"<iFont>");
	_LIT(KLitEikLblFntEnd,"<\\iFont>");
	_LIT(KLitEikLblNoLns,"<iNumberOfLines>");
	_LIT(KLitEikLblNoLnsEnd,"<\\iNumberOfLines>");
	_LIT(KLitEikLblFlgs,"<iLabFlags>");
	_LIT(KLitEikLblFlgsEnd,"<\\iLabFlags>");
	_LIT(KLitEikLblGpBtwnLns,"<iGapBetweenLines>");
	_LIT(KLitEikLblGpBtwnLnsEnd,"<\\iGapBetweenLines>");
	_LIT(KLitEikLblResLen,"<iReserveLength>");
	_LIT(KLitEikLblResLenEnd,"<\\iReserveLength>");

	aWriteStream << KLitEikLblCtlStart;
	aWriteStream << KLitEikLblTxt;
	if(iText)
		aWriteStream.WriteL(*iText);
	aWriteStream << KLitEikLblTxtEnd;
	aWriteStream << KLitEikLblFnt;
	const TFontSpec& spec=iFont->FontSpecInTwips();
	aWriteStream << spec;
	aWriteStream << KLitEikLblFntEnd;
	aWriteStream << KLitEikLblNoLns;
	aWriteStream.WriteInt32L(iNumberOfLines);
	aWriteStream << KLitEikLblNoLnsEnd;
	aWriteStream << KLitEikLblFlgs;
	aWriteStream.WriteInt32L(iLabFlags);
	aWriteStream << KLitEikLblFlgsEnd;
	aWriteStream << KLitEikLblGpBtwnLns;
	aWriteStream.WriteInt32L(iGapBetweenLines);
	aWriteStream << KLitEikLblGpBtwnLnsEnd;
	aWriteStream << KLitEikLblResLen;
	aWriteStream.WriteInt32L(iReserveLength);
	aWriteStream << KLitEikLblResLenEnd;
	CEikAlignedControl::WriteInternalStateL(aWriteStream);
	aWriteStream << KLitEikLblCtlEnd;
	}
#endif

EXPORT_C void CEikLabel::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikAlignedControl::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CEikLabel::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CEikLabel::Reserved_2()
	{}

// @todo use some utility 
#define max(a, b) a > b ? a : b; 
#define min(a, b) a < b ? a : b; 
#define abs(a) a < 0 ? -a : a; 

TInt CalculateLuminance(const TRgb& aColor) 
    { 
    TInt R = aColor.Red(); 
    TInt G = aColor.Green(); 
    TInt B = aColor.Blue(); 
    // Should be scaled to 0-255? 
    TInt Y = (((66 * R) + (129 * G) + (25 * B) + 128) >> 8) + 16; 
    return Y; 
    } 
    
void CEikLabel::ConvertColorsForOutlineEffect(TRgb& aPenColor, TRgb& aBrushColor) const 
    { 
    // the caller intends the brush color to be the background or outline, 
    // and the pen color to be the foreground color 
    TRgb innerColor = aPenColor; 
    TRgb outerColor = aBrushColor; 

    // @todo maybe there is already some conversion utility in multimedia image library? 
    TInt innerLum = CalculateLuminance(innerColor); 
    TInt outerLum = CalculateLuminance(outerColor); 
    
    // if the defined colours are the same, then change the outline color so that 
    // it's either black or white, contrasting according to the font label text color's brightness 
    TInt difference = outerLum - innerLum; 
    difference = abs(difference); 
    TInt half = (0xff / 2); // @todo figure out hlsMax somehow 
    TInt threshold = (0xff / 3); // @todo figure out hlsMax somehow, and decide on the threshold! 
    if(difference < threshold) 
        { 
        // if inner luminance is low, the outer luminance should be high, i.e. white 
        outerColor = (innerLum < half) ? KRgbWhite : KRgbBlack; 
        } 
    
    // for outline effect, we must set the color we want as the outline to the pen color, and 
    // the color we want as the fill to the brush color, so swap them round 
    aPenColor = outerColor; 
    aBrushColor = innerColor; 
    } 


