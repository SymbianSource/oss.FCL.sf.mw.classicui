/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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


#include "AknPanic.h"
#include "akntextcontrol.h"

#include "AknUtils.h"
#include "AknBidiTextUtils.h"

#include <AknPictographInterface.h>
#include <AknPictographDrawerInterface.h>

// CONSTANTS

const TInt KDefaultMinCharWidthInPixels = 4;

const TText KLineFeed               = 0x000A;
const TText KCarriageReturn         = 0x000D;
const TText KLineSeparator          = 0x2028;
const TText KParagraphSeparator     = 0x2029;

CAknTextControl* CAknTextControl::NewL(const CAknText::TType& aTextType)
	{
	CAknTextControl* self = new (ELeave) CAknTextControl();
	CleanupStack::PushL(self);
	self->ConstructL(aTextType);
	CleanupStack::Pop(); //self
	return self;
	}

void CAknTextControl::ConstructL(const CAknText::TType& aTextType)
	{
	iText = new (ELeave) CAknText( aTextType );
	iWrappedArray = new (ELeave) CArrayFixFlat<TPtrC>(5);
	iPictoInterface = CAknPictographInterface::NewL( *this, *this );
	}

CAknTextControl::CAknTextControl() 
	{
	}

CAknTextControl::~CAknTextControl()
	{
	delete iText;
	delete iWrappedArray;
	delete iPictoInterface;
	iLines.ResetAndDestroy();
	iLines.Close();
	}

/*
 * Copy text and labels across (pointer copy)
 */
CAknTextControl& CAknTextControl::operator=(CAknTextControl& aTextControl)
	{
	if (&aTextControl == this)
		return *this;

	if (aTextControl.iText && iText)
		*iText = *aTextControl.iText;

	if (aTextControl.NumberOfLines() > 0 && NumberOfLines() == 0)
		{
		iLines.ResetAndDestroy();
		
		for ( TInt i = aTextControl.NumberOfLines() - 1; i >= 0; i--)
			if (iLines.Insert( aTextControl.iLines[i], 0) == KErrNone)
				aTextControl.iLines.Remove(i);
		}

	if (aTextControl.iTextIsAlreadyInLabel)
		iTextIsAlreadyInLabel = aTextControl.iTextIsAlreadyInLabel;

	return *this;
	}

void CAknTextControl::ConstructFromResourceL(TResourceReader& aRes)
	{
	if (iText)
		iText->ConstructFromResourceL(aRes);
	}

TInt CAknTextControl::CountComponentControls() const
	{
	return NumberOfLines();
	}

CCoeControl* CAknTextControl::ComponentControl(TInt anIndex) const
	{
	return const_cast<CEikLabel*>(Line(anIndex));
	}

TInt CAknTextControl::NumberOfLines() const
	{
	__ASSERT_DEBUG(iLines.Count() >= iNumberOfLines, Panic(EAknPanicSelfCheckFailure));
	return iNumberOfLines;
	}

CEikLabel* CAknTextControl::Line(TInt aIndex) const
	{
	if (aIndex >= 0 && aIndex < NumberOfLines())
		return iLines[aIndex]->iLabel;
	return NULL;
	}

TBool CAknTextControl::LineModified(TInt aIndex) const
	{
	if (aIndex >= 0 && aIndex < NumberOfLines())
		return iLines[aIndex]->iModified;
	return EFalse;
	}

void  CAknTextControl::SetLineModified(TInt aIndex, TBool aValue)
	{
	if (aIndex >= 0 && aIndex < NumberOfLines())
		iLines[aIndex]->iModified = aValue;
	}

void CAknTextControl::SetTextPluralityL(TBool aIsPlural)
	{
	if (iText)
		iText->SetPluralityL(aIsPlural);
    }

void CAknTextControl::SetTextNumberL(TInt aNumber)
	{
	if (iText)
		iText->SetNumberL(aNumber);
    }

/**
 * Set the text, to be spread across labels.
 */
void CAknTextControl::SetTextL(const TDesC& aText)
	{
	if (iText)
		{
		iText->SetL(aText);
		iTextIsAlreadyInLabel = EFalse;
		}
	}

/**
 * Set text into a single label. ParseText will do nothing if this
 * method has been called.
 *
 * If the line already exists and it has already the same text and font
 * then return without doing anything.
 *
 * If the line does not exist, create it.
 *
 * SetBufferReserveLengthL causes a reallocation but this should never
 * be called unless somebody decides to change the font after the label
 * has been created and with this new font you can fit more characters 
 * in the same width
 */


void CAknTextControl::SetTextL(
    const TDesC& aText,
    TInt aLineNum,
    const CFont* aFont,
    CArrayFixFlat<TInt>* aLineWidths )
	{
	__ASSERT_DEBUG( aLineNum >= 0, Panic( EAknPanicInvalidValue ) );
	
	if ( aLineNum >= iNumberOfLines )
		{
		CreateLabelsL( aLineNum + 1, aFont, aLineWidths );
		iNumberOfLines = aLineNum + 1;
		}
	else
		{
		if ( aText == *( Line( aLineNum )->Text() ) )
			{
			iTextIsAlreadyInLabel = ETrue;
            return;
			}
		}

    TInt newReservedLength = aText.Length() + KAknBidiExtraSpacePerLine;

    HBufC* visualText = HBufC::NewL( newReservedLength );
    CleanupStack::PushL( visualText );

    *visualText = aText;

	Line( aLineNum )->SetFont( aFont );

	if ( Line( aLineNum )->BufferReserveLength() < newReservedLength )
        {
		Line( aLineNum )->SetBufferReserveLengthL( newReservedLength );
        }

    TInt clipWidth = aLineWidths->At( aLineNum );

    // Logical-to-visual conversion is disabled in the owned CEikLabel instances,
    // so we do the conversion here, while clipping.

    TPtr ptr = visualText->Des();

    AknBidiTextUtils::ConvertToVisualAndClipL(
        ptr,
        *aFont,
        clipWidth,
        clipWidth );

	Line( aLineNum )->SetTextL( *visualText );
	iLines[aLineNum]->iModified = ETrue;
	iTextIsAlreadyInLabel = ETrue;

    CleanupStack::PopAndDestroy(); // visualText;
	}


TPtr CAknTextControl::Text() const
	{
	if (iText) 
		return iText->Get();
	return TPtr(0,0);
	}

/**
 * Wraps the text and sets it into the labels.
 */
void CAknTextControl::ParseTextL(const CFont* aFont, CArrayFixFlat<TInt>* aLineWidths,const TWrapMethod& aWrapMethod)
    { 
	if ( aWrapMethod == ENoAllocation && iWrappedArray )
		{
		// We preallocate text required in construction of alert win, so we just replace the texts in labels.
        TPtrC remainder = Text();
		TChar endlchar('\n');
		TInt linebreak = remainder.LocateReverse(endlchar);
        
		TBuf<17 + KAknBidiExtraSpacePerLine> temp; //KEikAlertMaxMsgLength not declared in this scope

        if ( linebreak == KErrNotFound )
            {
            AknBidiTextUtils::ConvertToVisualAndClip(remainder, temp, *aFont, KMaxTInt, KMaxTInt );
            Line(0)->SetTextL(temp); // won't leave as there is enough space in buffer
            iLines[0]->iModified = ETrue;
            Line(1)->SetTextL(KNullDesC);
            iLines[1]->iModified = ETrue;
            }
        else
            {
            AknBidiTextUtils::ConvertToVisualAndClip(
                remainder.Left(linebreak), temp, *aFont, KMaxTInt, KMaxTInt );
            Line(0)->SetTextL(temp);
            iLines[0]->iModified = ETrue;
            if ( remainder.Length()-1 == linebreak) // Line break is the last character
                {
                Line(1)->SetTextL(KNullDesC);
                }
            else
                {
                AknBidiTextUtils::ConvertToVisualAndClip( 
                    remainder.Right(remainder.Length()-linebreak-1), temp, *aFont, KMaxTInt, KMaxTInt );
                Line(1)->SetTextL(temp); // we don't want new line to label, thus -1
                }
            iLines[1]->iModified = ETrue;		
			}
		return;
		}
	if (iTextIsAlreadyInLabel || !iWrappedArray)
		return;

    TInt maxLines = aLineWidths->Count();

    // user handles all text processing
    if ( aWrapMethod == ENoProcessing )
        {
        iWrappedArray->Reset();

        TPtrC remainder = Text();

        while ( remainder.Length() && iWrappedArray->Count() < maxLines )
            {
            const TText* textArray = remainder.Ptr();
            TInt textLength = remainder.Length();

            TInt i = 0;

            for ( ; i < textLength ; i++ )
                {
                TText t = textArray[i];

                if ( t == KLineFeed ||
                     t == KLineSeparator ||
                     t == KParagraphSeparator ||
                     t == KCarriageReturn )
                    {
                    break;
                    }
                }

            iWrappedArray->AppendL( remainder.Left( i ) );

            // After a CR, skip also possible matching LF
            if ( i < textLength - 1 &&
                 textArray[i] == KCarriageReturn &&
                 textArray[i + 1] == KLineFeed )
                {
                i++;
                }

            i++;

            if ( i >= textLength )
                {
                break;
                }
            remainder.Set( remainder.Right( textLength - i ) );
            }
        }

    else
        {
        TPtr text = Text();

        HBufC* visualBuffer = HBufC::NewLC( 
            text.Length() + maxLines * KAknBidiExtraSpacePerLine );
        *visualBuffer = text;
        TPtr ptr = visualBuffer->Des();

        AknTextUtils::DisplayTextLanguageSpecificNumberConversion( ptr);

	    if (aWrapMethod == EWord)
            {
            AknBidiTextUtils::ConvertToVisualAndWrapToArrayL(
                ptr, *aLineWidths, *aFont, *iWrappedArray, ETrue );
            }
	    else if (aWrapMethod == ELine)
            {
		    AknBidiTextUtils::ConvertToVisualAndChopToArrayL(
                ptr, *aLineWidths, *aFont, *iWrappedArray );
            }
	    else
            {
		    __ASSERT_DEBUG(0,Panic(EAknPanicNotSupported));
            }
        }

    TInt numLines = iWrappedArray->Count();

	UpdateLabelsL(numLines,aFont,aLineWidths);	
	SetWrappedTextIntoLabelsL(*iWrappedArray, numLines, aFont);

    if ( aWrapMethod != ENoProcessing )
        {
        CleanupStack::PopAndDestroy(); // visualBuffer
        }
    }

/**
 * Set text and font into labels.
 *
 * SetBufferReserveLengthL causes a reallocation but this should never
 * be called unless somebody decides to change the font after the label
 * has been created and with this new font you can fit more characters 
 * in the same width

 */
void CAknTextControl::SetWrappedTextIntoLabelsL(const CArrayFix<TPtrC>& aWrappedArray, TInt aNumLines, const CFont* aFont)
	{
	__ASSERT_DEBUG(aNumLines == iNumberOfLines, Panic(EAknPanicSelfCheckFailure));

	for (TInt i=0; i < iNumberOfLines; i++)
		{
		
		if (Line(i)->BufferReserveLength() < aWrappedArray.At(i).Length())
			Line(i)->SetBufferReserveLengthL(aWrappedArray.At(i).Length());

		if (*(Line(i)->Text()) != aWrappedArray.At(i) )
			{
			Line(i)->SetTextL(aWrappedArray.At(i));
			Line(i)->SetFont(aFont);
			iLines[i]->iModified = ETrue;
			}
		}
	}
/**
 * Reset text in existing labels and create new ones if needed.
 *
 * Update the number of lines.
 */
void CAknTextControl::UpdateLabelsL(const TInt aNum,const CFont* aFont, CArrayFixFlat<TInt>* aLineWidths)
	{
	__ASSERT_DEBUG(iNumberOfLines <= iLines.Count(), Panic(EAknPanicSelfCheckFailure));

	if (aNum <= iNumberOfLines)
		{
		for (TInt i = aNum; i < iNumberOfLines; i++)
			{
			Line(i)->SetTextL(KNullDesC);
			iLines[i]->iModified = ETrue;
			}
		}
	else
		{
		CreateLabelsL(aNum,aFont,aLineWidths);
		}

	iNumberOfLines = aNum;
	}

/**
 * Create labels up to the specified number. 
 *
 * When a new label is created, allocate a buffer inside the label so 
 * that it can contains a text as long as the maximum number of 'l' characters 
 * that fit into the given line width (in pixels). 
 */
void CAknTextControl::CreateLabelsL(const TInt aNum,const CFont* aFont, CArrayFixFlat<TInt>* aLineWidths)
	{
	__ASSERT_DEBUG(aFont,Panic(EAknPanicSelfCheckFailure));
	__ASSERT_DEBUG(aLineWidths->Count() >= aNum,Panic(EAknPanicSelfCheckFailure));

    TInt minCharWidthInPixels = aFont->CharWidthInPixels('l');
    if ( minCharWidthInPixels < 1)
        {
        minCharWidthInPixels = KDefaultMinCharWidthInPixels;
        }

	for (TInt i = iNumberOfLines; i < aNum; i++)
		{
		CEikLabel* label = CreateLabelLC(aLineWidths->At(i) / minCharWidthInPixels);
		CLine* line = new (ELeave) CLine(label);
		CleanupStack::Pop(); //label
		CleanupStack::PushL(line);
		User::LeaveIfError(iLines.Append(line));
		CleanupStack::Pop(); //line
		}
	}

/**
 * Create a label
 */
CEikLabel* CAknTextControl::CreateLabelLC(TInt aLen)
	{
	CEikLabel* label = new(ELeave) CEikLabel;
	CleanupStack::PushL(label);

	label->SetContainerWindowL(*this);
	label->SetBufferReserveLengthL(aLen);
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    label->SetParent( this );
#endif	
	
    // we do logical to visual conversion ourselves while wrapping text
    label->UseLogicalToVisualConversion( EFalse );

    if ( iPictoInterface )
        {
        label->EnablePictographsL( *iPictoInterface );
        }
	
	return label;
	}

void CAknTextControl::SetPictographCallBackL( TCallBack& aCallBack )
    {
    iPictoCallBack = aCallBack;
    }

CAknPictographInterface* CAknTextControl::PictographInterface() const
    {
    return iPictoInterface;
    }

void CAknTextControl::DrawPictographArea()
    {
    if ( iPictoCallBack.iFunction )
        {
        iPictoCallBack.CallBack();
        }
    }

		
// End of File
