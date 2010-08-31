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

TInt CEikCapCArray::NumberOfTextLines() const
{
	CEikCaptionedControl *firstCapCC = Count() > 0 ? (*this)[0] : NULL;
	const CEikDialogPage *dialogPage = firstCapCC ? firstCapCC->DialogPage() : NULL;
    CEikDialogPage::TFormLayoutSelection ret = CEikDialogPage::ESingle;
	if ( dialogPage )
		ret = dialogPage->FormLayout();

	TInt lines = 0;
	for(TInt i = 0; i<Count(); i++)
		{
			TInt num_of_lines = 0;
			CEikCaptionedControl *line = (*this)[i];
			if (ret == CEikDialogPage::ESingle)
					{
					//line->MinimumSize(); // ensures NumberOfLines() is valid.
					TInt h = line->NumberOfLinesForScrollBar();
					num_of_lines = h;
					}
			else if (ret == CEikDialogPage::EDouble)
					{
					//line->MinimumSize(); // ensures NumberOfLines() is valid.
					TInt h = line->NumberOfLinesForScrollBar();
					num_of_lines = h; // one for title
					}	
		lines += num_of_lines;
	}
	return lines;
}

TInt CEikCapCArray::NumberOfTextLinesBeforeLine(TInt aLine) const
{
	CEikCaptionedControl *firstCapCC = Count() > 0 ? (*this)[0] : NULL;
	const CEikDialogPage *dialogPage = firstCapCC ? firstCapCC->DialogPage() : NULL;
    CEikDialogPage::TFormLayoutSelection ret = CEikDialogPage::ESingle;
	if ( dialogPage )
		ret = dialogPage->FormLayout();

	TInt lines = 0;
	for(TInt i = 0; i<aLine; i++)
		{
			TInt num_of_lines = 0;
			CEikCaptionedControl *line = (*this)[i];
			if (ret == CEikDialogPage::ESingle)
					{
					//line->MinimumSize(); // ensures NumberOfLines() is valid.
					TInt h = line->NumberOfLinesForScrollBar();
					num_of_lines = h;
					}
			else if (ret == CEikDialogPage::EDouble)
					{
					//line->MinimumSize(); // ensures NumberOfLines() is valid.
					TInt h = line->NumberOfLinesForScrollBar();
					num_of_lines = h; // one for title
					}	
		lines += num_of_lines;
	}
	return lines;

}

TInt CEikCapCArray::FindItemFromTextLine(TInt aTextLine) const
	{
	CEikCaptionedControl *firstCapCC = Count() > 0 ? (*this)[0] : NULL;
	const CEikDialogPage *dialogPage = firstCapCC ? firstCapCC->DialogPage() : NULL;
    CEikDialogPage::TFormLayoutSelection ret = CEikDialogPage::ESingle;
	if ( dialogPage )
		ret = dialogPage->FormLayout();

	TInt lines = 0;
	TInt i = 0;
	for(i = 0; i<Count(); i++)
		{
			TInt num_of_lines = 0;
			CEikCaptionedControl *line = (*this)[i];
			if (ret == CEikDialogPage::ESingle)
					{
					//line->MinimumSize(); // ensures NumberOfLines() is valid.
					TInt h = line->NumberOfLinesForScrollBar();
					num_of_lines = h;
					}
			else if (ret == CEikDialogPage::EDouble)
					{
					//line->MinimumSize(); // ensures NumberOfLines() is valid.
					TInt h = line->NumberOfLinesForScrollBar();
					num_of_lines = h; // one for title
					}	
		lines += num_of_lines;
		if (lines > aTextLine)
			break;
	}
	return i;
	}
/**
 *  Calculate the size of all the component controls stacked vertically.
 *  For Avkon Forms the controls overlap by 2 pixels (hard coded)
 */
EXPORT_C TSize CEikCapCArray::MinimumSize()
	{
	TSize size(0,0);

	CEikCaptionedControl *firstCapCC = Count() > 0 ? (*this)[0] : NULL;
	if (firstCapCC && firstCapCC->iIsFormControl)
		{ // we're inside form
	    // Minimumsize needs to be called even though we wouldnt use the result (at least it calculates the number of lines)
		// TP HACK START (made because MinimumSize() is not good name for situations where content dimensions are desired)
		TInt height = 0;
		TInt width = 0;
		TRect parentRect = Rect();
		TSize lineSize; // absolute size, minimumSize = maximumSize = LAF size
		for(TInt i=0;i<Count();i++)
			{
			TInt gap = 0; // not possible to get this from LAF. (should be 0.5u or something)
			CEikCaptionedControl *line = (*this)[i];
				TAknWindowLineLayout layout;
			const CEikDialogPage *dialogPage = firstCapCC->DialogPage();
		    CEikDialogPage::TFormLayoutSelection ret = CEikDialogPage::ESingle;
			if ( dialogPage )
				ret = dialogPage->FormLayout();
			if (ret == CEikDialogPage::ESingle)
					{
					lineSize = line->MinimumSize(); // ensures NumberOfLines() is valid.
					}
			else if (ret == CEikDialogPage::EDouble)
					{
					lineSize = line->MinimumSize(); // ensures NumberOfLines() is valid.
					}	
			height += lineSize.iHeight + gap;
			width = lineSize.iWidth;
			}
		size = TSize(width,height);
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
		TRect rect = TRect(TPoint(0,0), aAreaSize);
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
 * If aControl is an edwin, set its clipping rect to empty. This
 * will disable the text hiding.
 */
static void ResetHides(CEikCaptionedControl *aControl)
	{
	aControl->SetPartiallyVisible( EFalse );
	if (aControl->ControlIsAnEdwin(aControl->iControlType))
		{
		CEikEdwin *edwin = (CEikEdwin*)aControl->iControl;
		edwin->SetTextLinesRect(TRect());
		}
	}

/**
 * Sets a clipping rectangle for hiding the whole or a part of edwin's text.
 *
 * The reason for using this function is the multiline edwins. The text inside
 * an edwin can be broken to two or more lines, which must be hidden or shown 
 * independently from each other. That is why it is not enough just to move
 * the whole edwin out of the screen.
 *
 * @param aClipRect The clipping rect for edwin's text. An empty rect disables 
 *   hiding.
 *
 * @return How many subcontrols were hidden
 */
static TInt HideLines_Edwin(CEikEdwin *aEdwin, TRect aClipRect)
	{
	aEdwin->SetTextLinesRect(aClipRect);
    
    // Create rects of the first and last edwin lines
    TPoint edwinTl( aEdwin->Rect().iTl );
    TPoint edwinBr( aEdwin->Rect().iBr );
    TRect textFirstLine;
    aEdwin->TextLayout()->GetLineRect(edwinTl.iY, textFirstLine);
    textFirstLine.Move( edwinTl.iX, edwinTl.iY + aEdwin->Margins().iTop );
    TRect textLastLine;
    aEdwin->TextLayout()->GetLineRect(edwinBr.iY, textLastLine);
    textLastLine.Move( edwinBr.iX, edwinBr.iY - aEdwin->Margins().iTop - textLastLine.Height() );

    // Check if at least one line fits to the clipping rect
	if( aClipRect.Contains(textFirstLine.iTl) &&
	    aClipRect.iBr.iY >= textFirstLine.iBr.iY )   // The first line fits
	    return 0;
	if( aClipRect.Contains(textLastLine.iTl) &&
	    aClipRect.iBr.iY >= textLastLine.iBr.iY )   // The last line fits
	    return 0;
	return 1;
	}

/**
 * Tries to hide the specified control. The control will be hidden, if it doesn't
 * fit to the specified clipping rectangle. Checks if the control exists.
 *
 * @return How many subcontrols were hidden
 */
static TInt HideLines_Ctrl(CCoeControl *aControl, TRect aClipRect)
	{
	if ( !aControl )
	    return 1;   // It doesn't exist and hence not visible
	TRect rect( aControl->Rect() );
	if ( !aClipRect.Contains(rect.iTl) || aClipRect.iBr.iY <= rect.iBr.iY )
	    // Never use TRect::Contains() for checking the bottom right corner, see documentation
		{
		// hide it
		aControl->SetPosition( TPoint(-666,-666) );
		return 1;
		}
    else
        return 0;
	}

/**
 * Get vertically minimal rectangle of the two given.
 *
 * Vertically reduces aRect1 by aRect2's dangling part, if aRect2
 * doesn't fit to aRect1.
 *
 * Sets aRect1 to the resulting minimal rectangle.
 */	
static void GetVertMinRect( TRect& aRect1, const TRect aRect2 )
    {
    // If aRect2's top doesn't fit, lower aRect1's top
    if( aRect2.iTl.iY < aRect1.iTl.iY )
        aRect1.iTl.iY = Max( aRect1.iTl.iY, aRect2.iBr.iY );
    // If aRect2's bottom doesn't fit, raise aRect1's bottom
    if( aRect2.iBr.iY > aRect1.iBr.iY )
        aRect1.iBr.iY = Min( aRect1.iBr.iY, aRect2.iTl.iY );
    }

/**
 * Hides the specified form line, if it does not fit to the specified clipping rectangle.
 * The function never hides focused editable lines. If the form layout is single, the whole
 * captioned control is hidden.
 * 
 * @param aControl The form line to be hidden
 * @param aClipRect The clipping rectangle
 *
 * @return How many subcontrols remained visible
 */	
static TInt HideLines(CEikCaptionedControl *aControl, TRect aClipRect)
	{
	TInt visibleCtrls = 3; // Visible subcontrols after hiding
	CEikCaptionedControl *currentdLine = aControl->DialogPage()->CurrentLine();
	if( ( aControl == currentdLine ) && aControl->iIsEditable )
	    {
	    return visibleCtrls;
	    }
	
	TBool isEdwin = aControl->ControlIsAnEdwin(aControl->iControlType);    
	CEikEdwin* edwin( NULL );
	if( isEdwin )
	    edwin = (CEikEdwin*)aControl->iControl;
	TRect ctrlRect( aControl->iControl->Rect() );
		
	if( isEdwin )
	    {
	    // Adjust rectangle only to the first line (with edwin's top margin)
	    TRect textFirstLine;
	    edwin->TextLayout()->GetLineRect(ctrlRect.iTl.iY, textFirstLine);
	    ctrlRect.iBr.iY = ctrlRect.iTl.iY + edwin->Margins().iTop + textFirstLine.Height();
	    }	    
	
	// Find the minimal clipping rectangle
	if( aControl->iBitmap )
	    GetVertMinRect( aClipRect, aControl->iBitmap->Rect() );
	if( aControl->iCaption )
	    GetVertMinRect( aClipRect, aControl->iCaption->Rect() );
	GetVertMinRect( aClipRect, ctrlRect );
	
	
	
	// Try to hide all controls on the current line
	aControl->SetPartiallyVisible( ETrue );
	visibleCtrls -= HideLines_Ctrl( aControl->iBitmap, aClipRect );
	visibleCtrls -= HideLines_Ctrl( aControl->iCaption, aClipRect );
	if( isEdwin )
		visibleCtrls -= HideLines_Edwin( edwin, aClipRect );
	else
		visibleCtrls -= HideLines_Ctrl( aControl->iControl, aClipRect );
    return visibleCtrls;
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
    TAknLayoutRect formtLayoutRect;
    formtLayoutRect.LayoutRect(aRect, AknLayoutScalable_Avkon::listscroll_form_pane().LayoutLine());
    formtLayoutRect.LayoutRect(formtLayoutRect.Rect(), AknLayoutScalable_Avkon::list_form_gen_pane().LayoutLine());
    TRect formRect = formtLayoutRect.Rect();
	
	CEikCapCArrayExtension *extension_or_null = ExtensionOrNull();
	if (extension_or_null)
		{
		extension_or_null->iRect = formRect;
		}

    // controls need to be placed in real locations if physics is enabled
    if ( Count() > 0 )
        {
        CEikCaptionedControl* control = (*this)[0];
        
        if ( control->DialogPage()->IsForm() )
            {
            SetRealRect( aRect, aTop, aBottom );
            return;
            }
        }
        
	TBool topDefined = EFalse;   // top or bottom number defined?
	if( aTop > -1 )
	    {
	    topDefined = ETrue;
	    }
	else if( aBottom > -1 )
	    {
	    topDefined = EFalse;
	    }
	else    // aBottom == aTop == -1
	    {
	    User::Panic( _L("CEikCapCArray::SetRect(): Neither top nor bottom items number defined"), EAknPanicInvalidValue );
	    }
	const TInt count = Count();
	const TInt rectHeight = aRect.Height();
	/**
	* Special invisible points are used for placing the items that are
	* outside the window. CCoeControl's invisible flag cannot be used,
	* as it is controlled by third-party applications.
	*/
	const TPoint topInvisPoint( -10000, -10000 );
	const TPoint bottomInvisPoint( 10000, 10000 );
	
	CEikCaptionedControl *firstCapCC = count > 0 ? (*this)[0] : NULL;
	if( firstCapCC && firstCapCC->iIsFormControl )  // Forms
		{
		CEikCaptionedControl *selectedLine( NULL );
		if( firstCapCC->DialogPage())
	        selectedLine = firstCapCC->DialogPage()->CurrentLine();
		
		// Check height of items and the input parameters aTop and aBottom.
		TInt rest = 0;  // number of the rest items without aTop or aBottom
		TInt index = 0;
    	if( topDefined )
    	    {
    	    rest = count - aTop;
    	    index = aTop;
    	    }
    	else
    	    {
    	    rest = count - aBottom;
    	    index = rest - 1;
    	    }
		TInt height = 0;
		for( TInt ii = 0; ii < rest; ii++ )
			{
    		CEikCaptionedControl* line = (*this)[index];
		    height += line->MinimumSize().iHeight;  // Use MinimumSize() here as a protection from dynamic layout change
		    if( height >= rectHeight )
                break;  // Input params are OK
		    topDefined? index++ : index--;
		    }
		/** 
		* If the window contains too few items inside and there are still items outside,
		* correct the input parameters @a aTop and @a aBottom to fill up the window.
		*/
		if( height < rectHeight )
		    {
		    if( topDefined && aTop > 0 )    // For top-down placement and there are items above the window
    		    {
    		    // Calculate height of controls above the window also
		        for( TInt ii = 0; ii < aTop; ii++ )
		            {
    		        CEikCaptionedControl* line = (*this)[ii];
		            height += line->MinimumSize().iHeight;
        		    if( height >= rectHeight )  // All items don't fit to the window anyway
    		            {
        		        topDefined = EFalse;   // Reverse direction to bottom-up
        		        aBottom = 0;
                        break;
        		        }
		            }
		        if( height < rectHeight )  // All items fit to the window
    		        {
    		        aTop = 0; // Just place them from the first item
    		        }
    		    }
    	    else if( !topDefined )  // For bottom-up placement
    	        {
    		    topDefined = ETrue;   // Reverse direction to top-down
    		    aTop = 0;
    	        }
    	    }
		
		// Hiding items that are explicitly defined to be outside the window
		TInt start;
		TInt end;
	    TPoint invisPoint;    // current invisible point, depends on placement direction
    	if( topDefined )
    	    {
    	    start = 0;
    	    end = aTop;
    	    invisPoint = topInvisPoint;
    	    }
    	else
    	    {
    	    start = count - aBottom;
    	    end = count;
    	    invisPoint = bottomInvisPoint;
    	    }
		for( TInt ii = start; ii < end; ii++ )
			{
			CEikCaptionedControl* line = (*this)[ii];
			line->SetPosition( invisPoint );
			}
		
		// Setting rects for the rest of the items
    	if( topDefined )
    	    {
    	    rest = count - aTop;
    	    invisPoint = bottomInvisPoint;
    	    index = aTop;
    	    }
    	else
    	    {
    	    rest = count - aBottom;
    	    invisPoint = topInvisPoint;
    	    index = rest - 1;
    	    }
		TInt reservedHeight = 0; // in pixels
		TBool insideWindow = ETrue; // The current item is still inside the window
        TInt topY = 0;
        
		
		for( TInt ii = 0; ii < rest; ii++ )
			{
    		CEikCaptionedControl* line = (*this)[index];
    		TSize lineSize( line->Size() );
		    if( insideWindow )
		        {
			    ResetHides( line );
    		    if( topDefined )
    		        {   // Top-down placement
    		        topY = aRect.iTl.iY + reservedHeight;   
    		        }
    		    else
    		        {   // Bottom-up placement
    		        topY = aRect.iBr.iY - reservedHeight - lineSize.iHeight;
    		        }
    		    line->SetExtent( TPoint( formRect.iTl.iX, topY ), lineSize );
    			AknsUtils::RegisterControlPosition( line );
    			AknsUtils::RegisterControlPosition( line->iCaption );
    			AknsUtils::RegisterControlPosition( line->iControl );
    			AknsUtils::RegisterControlPosition( line->iTrailer );
    			AknsUtils::RegisterControlPosition( line->iBitmap );
    			reservedHeight += lineSize.iHeight;
    			/** 
    			* The control at a window edge is considered as partially-visible.
    			* Its subcontrols must be checked for visibility individually.
    			*/
    			if( reservedHeight > rectHeight )
    			    {
    			    TInt visibleSubctrls = HideLines( line, aRect );    // Check how many subcontrols stayed visible
    			    insideWindow = EFalse;
    			    /**
    			    * For the bottom-up placement:
    			    * if the window contains only an empty "partially-visible" control and a
    			    * a selected popup field, make the popup to hang at the top alone.
    			    */
    			    if( !topDefined && index < count - 1 ) // bottom-up and not last
    			        {
        			    CEikCaptionedControl* lineBelow = (*this)[index+1];
        			    if( visibleSubctrls == 0 && ii == 1 &&
        			        IsPopupField( lineBelow ) && lineBelow == selectedLine )
        			        {
            		        TRect popupRect( lineBelow->Rect() );
            		        TInt diff = aRect.iTl.iY - popupRect.iTl.iY; // negative
            		        popupRect.Move( 0, diff );
            		        lineBelow->SetRect( popupRect );
        			        }
    			        }
    			    }
		        }
		    else
		        {
	            line->SetPosition( invisPoint );
		        }
		    topDefined? index++ : index--;
			}
		}
	else    // Dialogs other than forms:
		{
    	TRect rect=aRect;
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
    			line->iMinSize.iWidth+=deltaWidth;
    			}
    		line->iFullWidth=fullWidth;
    	    line->SetExtent(rect.iTl,thisSize);
    		if (!(line->LatentGroupLineFollows()))
    			{
    			rect.iTl.iY+=deltaHeight;
    			deltaHeight=0;
    			}
    		}
		}
	}

TInt CEikCapCArray::YPosToLine(const TRect &aRect, 
							   TInt aTop, TInt aMiddle, TInt aBottom, 
							   TInt aYCoord)
	{
	TInt top = aTop;
	TInt middle = aMiddle;
	TInt bottom = aBottom;
	CalcItemIndexes(top, middle, bottom, aRect.Size());
	
	for(int i = top ; i < top+middle; i++)
		{
		CEikCaptionedControl *fst = (*this)[i];
		if (aYCoord < fst->Rect().iTl.iY)
			{
			if (i > 0)
				return i-1;
			else
				return KErrNotFound;
			}
		}
	if (Count() == 0) return -1;
	TInt ii = top+middle-1;
	CEikCaptionedControl *last = (*this)[ii];
	if ( aYCoord < last->Rect().iBr.iY )
		{
		return ii;
		}
	else
		{
		if ( ii+1 < Count() )
		    {
		    return ii+1;
		    }
		else if ( aYCoord > last->Rect().iBr.iY )
		    {
		    return KErrNotFound;
		    }
		else
		    {
		    return ii;
		    }
		}
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
// CEikCapCArray::ScrollByPixels
// ---------------------------------------------------------------------------
//
TInt CEikCapCArray::ScrollByPixels( TInt aDelta )
    {
    TInt count = Count();
    
    // Top and bottom of lines
    TInt topY = (*this)[0]->Rect().iTl.iY;
    TInt bottomY = (*this)[count - 1]->Rect().iBr.iY;

    TRect formRect( Rect() );

    if ( aDelta )
        {
        for( TInt i = 0; i < count; ++i )
            {
            CEikCaptionedControl* line = (*this)[i];
            TBool onDisplay = line->Rect().Intersects( formRect );
            TPoint position( line->Position() );
            position.iY += aDelta;
            
            line->SetPosition( position );
            
            onDisplay = onDisplay || line->Rect().Intersects( formRect );
            
            // Line is or was on display
            if ( ETrue /*onDisplay*/ )
                // Some controls, eg. slider and edwin don't handle
                // SetPosition properly. Workaround is to use SetRect,
                // which is slow as it does a whole layout for the control.
                // If form panning is ever speed optimized, captioned
                // control should me made to support SetPosition() correctly.
                {
                if ( line->ControlIsAPopfield( line->iControlType ) )
                    {
                    // Have to layout whole captioned control, otherwise
                    // text doesn't move. Fix later popup field to move
                    // properly.
                    line->SetRect( line->Rect() );
                    }
                else
                    {
                    line->iControl->SetRect( line->iControl->Rect() );
                    }
                line->DrawDeferred();
                //line->DrawNow();
                }
            }
        }

    return aDelta;
    }

// ---------------------------------------------------------------------------
// CEikCapCArray::SetRealRect
// ---------------------------------------------------------------------------
//
void CEikCapCArray::SetRealRect( 
		const TRect& /*aRect*/, TInt /*aTop*/, TInt /*aBottom*/ )
    {
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
    if ( aLine != -1 && aLine < Count() )
        {
        CEikCaptionedControl* line = (*this)[aLine];
        TPoint topLeft( 1000, 0 );
        
        if ( aVisible )
            {
            topLeft.SetXY( Rect().iTl.iX, LineIndexToYPosition( aLine, aTopY ) );
            }
        
        line->SetRect( TRect( topLeft, line->Size() ) );
        }
    }


// ---------------------------------------------------------------------------
// CEikCapCArray::FocusableLine
// ---------------------------------------------------------------------------
//
TInt CEikCapCArray::FocusableLine( TInt aCurrentLine, TInt aTopY )
    {
    TInt focusableLine = KErrNotFound;
    
    if ( aCurrentLine >= 0 && aCurrentLine < Count() )
        {
        TInt y = LineIndexToYPosition( aCurrentLine, aTopY );

        // if current line is visible on the screen the focus that
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
    
    return focusableLine;
    }

