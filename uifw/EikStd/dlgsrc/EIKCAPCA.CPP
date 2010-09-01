/*
* Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
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


#include <eikcapca.h>
#include <eikcapc.h>
#include <AknLayout2ScalableDef.h>
#include <AknUtils.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <AknsUtils.h>
#include <eikedwin.h>
#include "AknPanic.h"
#include "akntrace.h"

const TInt KVerticalSpacing=-2;  // Avkon form controls overlap by two pixels!
const TInt KVerticalSpacingSquash=0;

const TInt KAknTopMargin = 0 ;
const TInt KAknNoTopMargin = 0 ;


class CEikCapCArrayExtension : public CBase
{
public:
	TInt iCaptionWidth;
	TRect iRect;
};


TBool IsPopupField(CEikCaptionedControl* aCC)
{
	TInt ctrlType = aCC->iControlType;
	if (ctrlType == EAknCtPopupField || ctrlType == EAknCtPopupFieldText)
	{
		CAknPopupField *field = (CAknPopupField*)aCC->iControl;
		if (field->SelectionMode() != CAknPopupField::EAknPopupFieldLabelMode)
			return ETrue;
		return EFalse;
	}
	return EFalse;
}

// NOTE densePacking != iIsFormControl  (i.e. Dialogs are dense packed)

EXPORT_C CEikCapCArray::CEikCapCArray(TInt aGranularity)
	: CArrayPtrFlat<CEikCaptionedControl>(aGranularity)
	{
	__DECLARE_NAME(_S("CEikCapCArray"));
	}

EXPORT_C CEikCapCArray::~CEikCapCArray()
	{
	delete iExtension;
	ResetAndDestroy();
	}

EXPORT_C void CEikCapCArray::DeleteLine(TInt aIndex)
	{		
	// Changed the deleting order to fix TSW Error EKMA-7ES98G
	// so that now the item is removed from the array first,
	// and only after that actually deleted.
	CBase* tmp = ((*this)[aIndex]);
	Delete(aIndex);
	delete tmp;
	}

EXPORT_C void CEikCapCArray::SetDensePacking(TBool aDensePacking)
	{
	iDensePacking=aDensePacking;
	}


void CEikCapCArray::CreateExtensionL()
{
	iExtension = new(ELeave) CEikCapCArrayExtension;
}
CEikCapCArrayExtension *CEikCapCArray::ExtensionOrNull() const
{
	if (!iExtension)
		{
		TRAP_IGNORE(const_cast<CEikCapCArray*>(this)->CreateExtensionL());
		}
	return iExtension;
}


/**
 *  Calculate the size of all the component controls stacked vertically.
 *  For Avkon Forms the controls overlap by 2 pixels (hard coded)
 */
EXPORT_C TSize CEikCapCArray::MinimumSize()
	{
	_AKNTRACE_FUNC_ENTER;
	TSize size(0,0);

	CEikCaptionedControl *firstCapCC = Count() > 0 ? (*this)[0] : NULL;
	if (firstCapCC && firstCapCC->iIsFormControl)
		{ // we're inside form
	    // Minimumsize needs to be called even though we wouldnt use the result (at least it calculates the number of lines)
		// TP HACK START (made because MinimumSize() is not good name for situations where content dimensions are desired)
		TInt height = 0;
		TInt width = 0;
		TSize lineSize; // absolute size, minimumSize = maximumSize = LAF size
		for(TInt i=0;i<Count();i++)
			{
			CEikCaptionedControl *line = (*this)[i];
            lineSize = line->MinimumSize(); // ensures NumberOfLines() is valid.
			height += lineSize.iHeight;
			width = lineSize.iWidth;
			}
		size.SetSize(width,height);
		}
	else
		{
        TInt wholeWidth=0;
        const TInt count=Count();
        const TInt topMargin=iDensePacking ? KAknNoTopMargin : KAknTopMargin;
        const TInt bottomMargin = iDensePacking ? KAknNoTopMargin : KAknTopMargin ;
        const TInt verticalSpacing=iDensePacking ? KVerticalSpacingSquash : KVerticalSpacing;
        TInt deltaHeight=0;
        CEikCapCArrayExtension *extension = ExtensionOrNull();
        if (!extension) return TSize(30,30); // OOM
        for (TInt ii=0;ii<count;++ii)
            {
            CEikCaptionedControl* line=(*this)[ii];
            TSize thisSize=line->MinimumSize();
            TInt thisDeltaHeight=thisSize.iHeight+verticalSpacing;
            if (deltaHeight<thisDeltaHeight)
                deltaHeight=thisDeltaHeight;
            const TInt thisCaptionWidth=line->iCaptionWidth;
            if (!(line->LatentGroupLineFollows()))
                {
                size.iHeight+=deltaHeight;
                deltaHeight=0;
                }
            if (!thisCaptionWidth)
                {
                if (wholeWidth<thisSize.iWidth)
                    wholeWidth=thisSize.iWidth;
                }
            else
                {
                thisSize.iWidth-=thisCaptionWidth;
                if (extension->iCaptionWidth<thisCaptionWidth)
                    extension->iCaptionWidth=thisCaptionWidth;
                if (size.iWidth<thisSize.iWidth)
                    size.iWidth=thisSize.iWidth;
                }
            }
        size.iWidth+=extension->iCaptionWidth;
        if (size.iWidth<wholeWidth)
            size.iWidth=wholeWidth;
        // If the total height is zero don't bother adding a top margin
        if ( size.iHeight > 0 )
            {
            size.iHeight+=( topMargin + bottomMargin ) ;
            size.iHeight+=2 ;  // (we have included one too many '-2's)
            }
        }
    _AKNTRACE( "The Size : ( %d, %d ) ", size.iHeight, size.iWidth );
	_AKNTRACE_FUNC_EXIT;
	return size;
	}


/**
 * Position all of the component controls in a vertical pile.
 * For Avkon Forms the controls overlap by two pixels.  (hard coded)
 */
TRect CEikCapCArray::Rect() const
{
	CEikCapCArrayExtension *ext = ExtensionOrNull();
	if (ext)
		return ext->iRect;
	else
		return TRect(0,0, 100,100); // oom
}

TBool CEikCapCArray::CalcItemIndexes(TInt &aTopItemIndex, TInt &aMiddleItemIndex, TInt &aBottomItemIndex, TSize aAreaSize)
{ // calculates last item that still fits to the area's size
	TBool switchDir = EFalse;
	TInt i;
	TInt reservedHeight = 0;
	TInt newTop = aTopItemIndex, newMiddle = 1, newBottom = aBottomItemIndex;
	const TInt count = Count();
	CEikCaptionedControl *firstCapCC = Count() > 0 ? (*this)[0] : NULL;
	TInt num = 0;

	if (newTop == -1) { newTop = Count() - newMiddle - newBottom; }
	if (newBottom == -1) { newBottom = Count() - newTop - newMiddle; }


	if (aTopItemIndex != -1)
		{
		num = count - aTopItemIndex;
		}
	if (aBottomItemIndex != -1)
		{
		num = count - aBottomItemIndex;
		}
	for (i = 0; i < num; i++)
		{
		TInt index = 0;
		if (aTopItemIndex != -1)
			{
			index = i + aTopItemIndex;
			}
		else if (aBottomItemIndex != -1)
			{
			index = count - 1 - aBottomItemIndex - i;
			}
		CEikCaptionedControl* line=(*this)[index];

		const CEikDialogPage *dialogPage = firstCapCC->DialogPage();
	    CEikDialogPage::TFormLayoutSelection ret = CEikDialogPage::ESingle;
		if ( dialogPage )
			ret = dialogPage->FormLayout();
		TAknWindowLineLayout layout;
		if (ret == CEikDialogPage::ESingle)
			{
			TInt height = line->NumberOfLines();
			if (height < 1) height = 1;
			if (IsPopupField(line))
				{
				layout = AknLayoutScalable_Avkon::form_field_popup_pane(height-1).LayoutLine();
				}
				else
				{	
				layout = AknLayoutScalable_Avkon::form_field_data_pane(height-1).LayoutLine();
				}
			}
		else if (ret == CEikDialogPage::EDouble)
			{
			TInt height = line->NumberOfLines();
			if (height < 1) height = 1;
			if (IsPopupField(line))
				{
				layout = AknLayoutScalable_Avkon::form_field_popup_wide_pane(height-1).LayoutLine();
				}
				else
				{
				layout = AknLayoutScalable_Avkon::form_field_data_wide_pane(height-1).LayoutLine();
				}
			}	
		else
			{
			// should Panic() here 
			}
		TRect rect(aAreaSize);
		TAknLayoutRect layoutRect;
		layoutRect.LayoutRect(rect, layout);
		TInt height2 = layoutRect.Rect().Height();
		reservedHeight += height2;

		if (reservedHeight > aAreaSize.iHeight)
			{
			break;
			}

		newMiddle = i + 1;
		if (aTopItemIndex == -1)
			{
			newTop = count - i - 1 - aBottomItemIndex;
			}
		if (aBottomItemIndex == -1)
			{
			newBottom = count - i - 1 - aTopItemIndex;
			}

		}	
	if (reservedHeight <= aAreaSize.iHeight)
		{
		// 2nd loop for case where item sizes have changed; makes sure screen is full.
		for(int i = 0; newBottom > 0 && aTopItemIndex == -1 || newTop > 0 && aBottomItemIndex == -1; i++)
			{
			switchDir = ETrue;
			TInt index = 0;
			if (aBottomItemIndex == -1)
				{
				newMiddle ++;
				newTop --;
				index = newTop;
				}
			if (aTopItemIndex == -1)
				{
				newMiddle ++;
				newBottom --;
				index = count - 1 - newBottom;
				}
			CEikCaptionedControl* line=(*this)[index];

			const CEikDialogPage *dialogPage = firstCapCC->DialogPage();
		    CEikDialogPage::TFormLayoutSelection ret = CEikDialogPage::ESingle;
			if ( dialogPage )
				ret = dialogPage->FormLayout();
			TAknWindowLineLayout layout;
			if (ret == CEikDialogPage::ESingle)
				{
				TInt height = line->NumberOfLines();
				if (height < 1) height = 1;
			if (IsPopupField(line))
				{
				layout = AknLayoutScalable_Avkon::form_field_popup_pane(height-1).LayoutLine();
				}
				else
				{	
				layout = AknLayoutScalable_Avkon::form_field_data_pane(height-1).LayoutLine();
				}
				}
			else if (ret == CEikDialogPage::EDouble)
				{
				TInt height = line->NumberOfLines();
				if (height < 1) height = 1;
			if (IsPopupField(line))
				{
				layout = AknLayoutScalable_Avkon::form_field_popup_wide_pane(height-1).LayoutLine();
				}
				else
				{
				layout = AknLayoutScalable_Avkon::form_field_data_wide_pane(height-1).LayoutLine();
				}
				}	
			else
				{
				// should Panic() here 
				}
			TRect rect = TRect(TPoint(0,0), aAreaSize);
			TAknLayoutRect layoutRect;
			layoutRect.LayoutRect(rect, layout);
			TInt height2 = layoutRect.Rect().Height();

			reservedHeight += height2;


			if (reservedHeight > aAreaSize.iHeight)
				break;

			}
		}
	aTopItemIndex = newTop;
	aMiddleItemIndex = newMiddle;
	aBottomItemIndex = newBottom;
	return switchDir;
}

EXPORT_C void CEikCapCArray::SetRect(const TRect &aRect)
{
	SetRect(aRect, 0, -1, -1);
}


/**
* Places the dialog items according to the current visible window position.
* When hiding items, uses SetExtent() instead of just SetPosition() in order to call
* SizeChanged() of the moved item. For example, this is needed for the editor to
* change its cursor accordingly.
*
* @param aRect Rectangle of the form window
* @param aTop Number of items above the window
* @param aMiddle Number of items inside the window
* @param aBottom Number of items below the window
*
* Parameter value equal to -1 means that the parameter is not defined and will be
* calculated automatically. Normally, either the top number or the bottom one
* is only defined. If @a aTop is defined, the items will be placed from top downwards, leaving
* @a aTop items above the window. If @a aBottom is defined, the items will be placed from bottom
* upwards, leaving @a aBottom items below the window.
*
* This function panics, if neither @a aTop nor @a aBottom are defined.
*
* The function first checks if the provided @a aTop and @a aBottom are consistent with
* the item sizes and the given window rectangle. If they are not, they will be
* corrected. Usually, @a aTop and @a aBottom come out of sync with the item sizes
* after the dynamic layout change.
*/
void CEikCapCArray::SetRect(const TRect& aRect, TInt aTop, TInt /*aMiddle*/, TInt aBottom)
	{
	_AKNTRACE_FUNC_ENTER;
    TAknLayoutRect formtLayoutRect;
    formtLayoutRect.LayoutRect(aRect, AknLayoutScalable_Avkon::listscroll_form_pane().LayoutLine());
    formtLayoutRect.LayoutRect(formtLayoutRect.Rect(), AknLayoutScalable_Avkon::list_form_gen_pane().LayoutLine());
    TRect formRect( formtLayoutRect.Rect() );
	
	CEikCapCArrayExtension *extension_or_null = ExtensionOrNull();
	
	TBool rectChanged = ETrue;
	
	if (extension_or_null)
		{
        rectChanged = ( extension_or_null->iRect != formRect );
		extension_or_null->iRect = formRect;
		}

    // controls need to be placed in real locations if physics is enabled
    if ( Count() > 0 )
        {
        CEikCaptionedControl* control = (*this)[0];
        
        if ( control->DialogPage()->IsForm() )
            {
            if ( rectChanged )
                {
                SetRealRect( aRect, aTop, aBottom );
                }

            _AKNTRACE_FUNC_EXIT;
            return;
            }
        }
        
	// rest of the function is executed for dialogs and empty forms only
    TRect rect(aRect);
    const TInt fullWidth=rect.iBr.iX-rect.iTl.iX;
    const TInt count=Count();
    const TInt topMargin=iDensePacking ? KAknNoTopMargin : KAknTopMargin;
    const TInt verticalSpacing=iDensePacking ? KVerticalSpacingSquash : KVerticalSpacing;
    rect.iTl.iY+=topMargin;
    TInt deltaHeight=0;
    for (TInt ii=0;ii<count;++ii)
        {
        CEikCaptionedControl* line=(*this)[ii];
        TSize thisSize=line->MinimumSize();
        TInt thisDeltaHeight=thisSize.iHeight+verticalSpacing;
        if (deltaHeight<thisDeltaHeight)
            deltaHeight=thisDeltaHeight;
        if (!(line->iCaptionWidth))
            thisSize.iWidth=fullWidth;
        else
            {
            CEikCapCArrayExtension *ext = ExtensionOrNull();
            TInt deltaWidth = 0;

            if (ext) 
                deltaWidth = ext->iCaptionWidth-line->iCaptionWidth;
            thisSize.iWidth+=deltaWidth;
            if (ext)
                line->iCaptionWidth=ext->iCaptionWidth;
            else
                line->iCaptionWidth = 0;
            }
        line->iFullWidth=fullWidth;
        line->SetExtent(rect.iTl,thisSize);
        if (!(line->LatentGroupLineFollows()))
            {
            rect.iTl.iY+=deltaHeight;
            deltaHeight=0;
            }
        }

    _AKNTRACE_FUNC_EXIT;
	}
	
EXPORT_C void CEikCapCArray::ResetMinimumSizes()
	{
	const TInt count=Count();
	for (TInt ii=0;ii<count;++ii)
		(*this)[ii]->ResetMinimumSizes();
	}

EXPORT_C TInt CEikCapCArray::LineIndexFromId(TInt aControlId) const
	{
    const TInt count=Count();
    TInt ii=0;
    FOREVER
        {
        if (ii==count)
            return(KErrNotFound);
        if ((*this)[ii]->iId==aControlId)
            break;
		ii++;
        }
    return(ii);
	}

EXPORT_C void CEikCapCArray::AdjustAllIds(TInt aControlIdDelta)
	{
    const TInt count=Count();
	for (TInt ii=0; ii<count; ii++)
		(*this)[ii]->iId+=aControlIdDelta;
	}

EXPORT_C TInt CEikCapCArray::FindLineIndex(const CCoeControl* aControl) const
	{
    const TInt count=Count();
    TInt ii=0;
	while (ii<count)
		{
		CEikCaptionedControl* line=(*this)[ii];
		if (line==aControl || line->iControl==aControl)
			return(ii);
		ii++;
		}
	return(KErrNotFound);
	}


// ---------------------------------------------------------------------------
// CEikCapCArray::SetRealRect
// ---------------------------------------------------------------------------
//
void CEikCapCArray::SetRealRect( 
		const TRect& /*aRect*/, TInt /*aTop*/, TInt /*aBottom*/ )
    {
	_AKNTRACE_FUNC_ENTER;
    TInt count = Count();
    const TPoint virtualTl( 1000, 0 );
    TPoint skinLocation( 0, 0 );
    CEikCaptionedControl* currentLine = (*this)[0]->DialogPage()->CurrentLine();
    
    for ( TInt i = 0; i < count; ++i )
        {
        CEikCaptionedControl* line = (*this)[i];
        
        if ( line != currentLine )
            {
            line->SetExtent( virtualTl, line->Size() );
            }
        else
            {
        	line->SetExtent( line->Position(), line->Size() ); 
            }
        
        skinLocation.iY += line->Size().iHeight;
        
        AknsUtils::RegisterControlPosition( line, skinLocation );
        AknsUtils::RegisterControlPosition( line->iCaption, skinLocation );
        AknsUtils::RegisterControlPosition( line->iControl, skinLocation );
        AknsUtils::RegisterControlPosition( line->iTrailer, skinLocation );
        AknsUtils::RegisterControlPosition( line->iBitmap, skinLocation );
        }
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CEikCapCArray::YPositionToLineIndex
// ---------------------------------------------------------------------------
//
TInt CEikCapCArray::YPositionToLineIndex( TInt aYPos ) const
    {
    TInt count = Count();
    TInt topY = 0;
    TInt bottomY = 0;
    
    for ( TInt i = 0; i < count; ++i )
        {
        topY = bottomY;           
        bottomY = topY + (*this)[i]->Size().iHeight;
        
        if ( aYPos >= topY && aYPos < bottomY )
            {
            return i;
            }
        }

    return KErrNotFound;
    }


// ---------------------------------------------------------------------------
// CEikCapCArray::LineIndexToYPosition
// ---------------------------------------------------------------------------
//
TInt CEikCapCArray::LineIndexToYPosition( TInt aLine, TInt aTopY ) const
    {
    TInt topY = 0;
    TInt bottomY = 0;
    
    for ( TInt i = 0; i <= aLine; ++i )
        {
        topY = bottomY;
        bottomY = topY + (*this)[i]->Size().iHeight;
        }

    return topY - aTopY;
    }


// ---------------------------------------------------------------------------
// CEikCapCArray::MoveLineToScreen
// ---------------------------------------------------------------------------
//
void CEikCapCArray::MoveLineToScreen( TInt aLine, TInt aTopY, TBool aVisible )
    {
	_AKNTRACE_FUNC_ENTER;
	_AKNTRACE( "aLine: [%d], aTopY: [%d], aVisible: [%d]", aLine, aTopY, aVisible );
    if ( aLine != -1 && aLine < Count() )
        {
        CEikCaptionedControl* line = (*this)[aLine];
        TPoint topLeft( 1000, 0 );
        
        if ( aVisible )
            {
            topLeft.SetXY( Rect().iTl.iX, LineIndexToYPosition( aLine, aTopY ) );
            }
        
        TRect newRect( topLeft, line->Size() );
        
        if ( newRect != line->Rect() )
            {
            line->SetRect( TRect( topLeft, line->Size() ) );
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// CEikCapCArray::FocusableLine
// ---------------------------------------------------------------------------
//
TInt CEikCapCArray::FocusableLine( TInt aCurrentLine, TInt aTopY )
    {
	_AKNTRACE_FUNC_ENTER;
	_AKNTRACE( "aCurrentLine: [%d]", aCurrentLine );
    TInt focusableLine = KErrNotFound;
    
    if ( aCurrentLine >= 0 && aCurrentLine < Count() )
        {
        TInt y = LineIndexToYPosition( aCurrentLine, aTopY );

        // if current line is visible on the screen then focus that
        if ( y >= 0 && y <= Rect().Height() )
            {
            focusableLine = aCurrentLine;
            }
        else // otherwise return the topmost totally visible line
            {
            TInt topLine = YPositionToLineIndex( aTopY );
            
            if ( topLine != KErrNotFound && 
                    (*this)[topLine]->Position().iY < aTopY )
                {
                if ( ( topLine + 1 ) < Count() )
                    {
                    ++topLine;
                    }
                
                focusableLine = topLine;
                }
            }
        }
    _AKNTRACE_FUNC_EXIT;
    return focusableLine;
    }

