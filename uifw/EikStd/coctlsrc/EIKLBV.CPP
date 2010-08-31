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


#include <badesca.h>
#include <gdi.h>
#include <w32std.h>
#include <eiklbx.pan>
#include <eiklbx.h>
#include <eiklbv.h>
#include <eiklbm.h>
#include <eiklbi.h>
#include <gulutil.h>
#include <eikenv.h>
#include <avkon.rsg>
#include <barsread.h>
#include <AknUtils.h>
#include <AknsDrawUtils.h>
#include <AknsControlContext.h>

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
#include <aknlistboxtfxinternal.h>
#include <aknlistloadertfx.h>
#endif

#include "laflbv.h"
#include "laflbx.h"
#include "akntrace.h"

#define ITEM_EXISTS_BEGIN TInt no_of_items__ = iModel->NumberOfItems()
#define ITEM_EXISTS(x) (((x) > -1) && ((x) < no_of_items__))

#define ITEM_EXISTS_ONCE(x) (((x) > -1) && ((x) < iModel->NumberOfItems()))

//
// class CListBoxView
//
CListBoxViewExtension* CListBoxViewExtension::NewL()
    {
    CListBoxViewExtension* self = new ( ELeave ) CListBoxViewExtension;
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop(); // self
    
    return self;
    }
 
CListBoxViewExtension::~CListBoxViewExtension()
    {
    }
 
void CListBoxViewExtension::ConstructL()
    {
    // Panning and flicking disabled by default
    iScrollingDisabled = ETrue;
    }
 
 
void CListBoxView::SetVisibilityObserver(MListVisibilityObserver* aObserver)
	{
	iVisibilityObserver=aObserver;
	}

EXPORT_C TBool CListBoxView::IsVisible() const
	{
	if(iVisibilityObserver)
		return(iVisibilityObserver->IsVisible());
	return ETrue;
	}

EXPORT_C void CListBoxView::SetListEmptyTextL(const TDesC& aText)
	{
	delete iListEmptyText;
	iListEmptyText = NULL;

	iListEmptyText= aText.AllocL();
	}

EXPORT_C CListBoxView::CListBoxView()
	{
	_AKNTRACE_FUNC_ENTER;
	iItemHeight = 20;
//	iBackColor = KDefaultLbxBackColor;
	iBackColor = CEikonEnv::Static()->Color(EColorControlBackground); //KDefaultLbxBackColor;
	iMatcherCursorColor = TRgb(177, 177, 177);		// light gray?
	iCurrentItemIndex = 0;
	iTopItemIndex = 0;
	iListEmptyText = 0;
	iVerticalOffset = 0;
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C void CListBoxView::ConstructL(MListBoxModel* aList, CListItemDrawer* aItemDrawer, CWsScreenDevice* aScreen, RWindowGroup* aGroupWindow, RWindow* aWsWindow, const TRect& aDisplayArea, TInt aItemHeight)
	{
	_AKNTRACE_FUNC_ENTER;
	iExtension = CListBoxViewExtension::NewL();

	iModel = aList;
	iItemDrawer = aItemDrawer;
	iWin = aWsWindow;
	iGroupWin = aGroupWindow;
	// create a graphics context
    User::LeaveIfError(aScreen->CreateContext(iGc));
	iGc->Activate(*iWin);
	iItemDrawer->SetGc(iGc);
	iViewRect = aDisplayArea;
	iItemHeight = aItemHeight;
	iSelectionIndexes = new(ELeave) CArrayFixFlat<TInt>(5);

	//SetListEmptyTextL(_L("No Data"));
	TResourceReader rr;
	CEikonEnv::Static()->CreateResourceReaderLC(rr,R_AVKON_LISTBOX_DEFAULT_EMPTY_TEXT);
	TPtrC emptytext= rr.ReadTPtrC();
	SetListEmptyTextL(emptytext);
	CleanupStack::PopAndDestroy();
	_AKNTRACE_FUNC_EXIT;
	}
	
EXPORT_C CListBoxView::~CListBoxView()
	{
	_AKNTRACE_FUNC_ENTER;
	// Although my "item Drawer" is created by some other object, it is convenient
	// for me to destroy it here...
	delete iExtension;
	delete(iItemDrawer);
	delete iSelectionIndexes;
	delete(iGc);
	delete (iListEmptyText);
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C TInt CListBoxView::TopItemIndex() const
	{
	_AKNTRACE( "iTopItemIndex = %d", iTopItemIndex );
	return iTopItemIndex;
	}

EXPORT_C TInt CListBoxView::BottomItemIndex() const
	{
	_AKNTRACE( "iBottomItemIndex = %d", iBottomItemIndex );
	return iBottomItemIndex;
	}

EXPORT_C TBool CListBoxView::ItemIsSelected(TInt aItemIndex) const
	{
	_AKNTRACE( "Item selected is %d", aItemIndex );
	TKeyArrayFix key(0, ECmpTInt);	
	TInt pos;
	if (iSelectionIndexes->Find(aItemIndex, key, pos))
		return(EFalse);
	return(ETrue);
	}

EXPORT_C void CListBoxView::ToggleItemL(TInt aItemIndex) 
	{
	_AKNTRACE_FUNC_ENTER;
	__ASSERT_DEBUG(iSelectionIndexes, Panic(EEikPanicListBoxNoSelIndexArray));
	if (iItemDrawer->Properties(aItemIndex).IsSelectionHidden()) { DeselectItem(aItemIndex); return; }
	TKeyArrayFix key(0, ECmpTInt);	
	TInt pos;
	if (iSelectionIndexes->Find(aItemIndex, key, pos))
		iSelectionIndexes->AppendL(aItemIndex);   
	else
		iSelectionIndexes->Delete(pos);
	DrawItem(aItemIndex);
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C void CListBoxView::SelectItemL(TInt aItemIndex)
    {   
    // select the specified item; if already selected, do nothing
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "SelectItem is %d", aItemIndex );
    __ASSERT_DEBUG(iSelectionIndexes, Panic(EEikPanicListBoxNoSelIndexArray));
    if (iItemDrawer->Properties(aItemIndex).IsSelectionHidden()) 
        { 
        DeselectItem(aItemIndex); 
        _AKNTRACE_FUNC_EXIT;
        return; 
        }
    TKeyArrayFix key(0, ECmpTInt);  
    TInt pos;
    if (iSelectionIndexes->Find(aItemIndex, key, pos))
        {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal( iGc );
        if ( transApi )
            {
            transApi->Invalidate( MAknListBoxTfxInternal::EListItem, aItemIndex );
            }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
        iSelectionIndexes->AppendL(aItemIndex);
        DrawItem(aItemIndex);
        }
    _AKNTRACE_FUNC_EXIT;
    }  

EXPORT_C void CListBoxView::DeselectItem(TInt aItemIndex)
    {
    // deselect the specified item; if not currently selected, do nothing
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "DeselectItem is %d", aItemIndex );
    __ASSERT_DEBUG(iSelectionIndexes, Panic(EEikPanicListBoxNoSelIndexArray));
    TKeyArrayFix key(0, ECmpTInt);  
    TInt pos;
    if (!(iSelectionIndexes->Find(aItemIndex, key, pos)))
        {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal( iGc );
        if ( transApi )
            {
            transApi->Invalidate( MAknListBoxTfxInternal::EListItem, aItemIndex );
            }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
        iSelectionIndexes->Delete(pos);
        DrawItem(aItemIndex);
        }
    _AKNTRACE_FUNC_EXIT;
    }  

EXPORT_C void CListBoxView::GetSelectionIndexesL(CSelectionIndexArray *aSelectionArray) const
	{
	__ASSERT_DEBUG(aSelectionArray, Panic(EEikPanicListBoxInvalidSelIndexArraySpecified));
	__ASSERT_DEBUG(iSelectionIndexes, Panic(EEikPanicListBoxNoSelIndexArray));
	aSelectionArray->Reset();
	TInt selectionIndex;
	TInt numOfSelections = iSelectionIndexes->Count();
	for (TInt i = 0; i < numOfSelections; i++)
		{
		selectionIndex = (*(iSelectionIndexes))[i];
		aSelectionArray->AppendL(selectionIndex);
		}
	}

EXPORT_C void CListBoxView::SetSelectionIndexesL(const CSelectionIndexArray *aSelectionArray)
	{
	__ASSERT_DEBUG(aSelectionArray, Panic(EEikPanicListBoxInvalidSelIndexArraySpecified));
	ClearSelection();
	TInt numOfSelections = aSelectionArray->Count();
	TInt selectionIndex;
	for (TInt i = 0; i < numOfSelections; i++)
		{
		selectionIndex = (*aSelectionArray)[i];
        SelectItemL(selectionIndex);
		}
	}

EXPORT_C const CListBoxView::CSelectionIndexArray* CListBoxView::SelectionIndexes() const
	{
	return iSelectionIndexes;
	}

EXPORT_C void CListBoxView::ClearSelection()
	{
	_AKNTRACE_FUNC_ENTER;
	__ASSERT_DEBUG(iSelectionIndexes, Panic(EEikPanicListBoxNoSelIndexArray));
	TInt numSelectedItems = iSelectionIndexes->Count();
	TInt selectedItemIndex; 
	for	(TInt i = 0; i < numSelectedItems; i++)
		{
		selectedItemIndex = (*(iSelectionIndexes))[0];
        DeselectItem(selectedItemIndex);
		}
	ClearSelectionAnchorAndActiveIndex();
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C void CListBoxView::ClearSelectionAnchorAndActiveIndex()
	{
	_AKNTRACE_FUNC_ENTER;
	iAnchorIndex = 0;
	iActiveEndIndex = 0;
	ClearFlags(EAnchorExists);
	ClearFlags(EMarkSelection);
	ClearFlags(EUnmarkSelection);
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C void CListBoxView::SelectRangeL(TInt aItemIndex1, TInt aItemIndex2)
	{
	TInt startItem, endItem;
	startItem = Min(aItemIndex1, aItemIndex2);
	endItem = Max(aItemIndex1, aItemIndex2);
	for (TInt i = startItem; i <= endItem; i++)
        SelectItemL(i);
	}

EXPORT_C void CListBoxView::SetAnchor(TInt aItemIndex)
	{
    SetFlags(EAnchorExists);
	iAnchorIndex = aItemIndex;
	iActiveEndIndex = aItemIndex;
	}

EXPORT_C void CListBoxView::UpdateSelectionL(TSelectionMode aSelectionMode)
	{
	// assumes that iCurrentItemIndex has already been updated...
	_AKNTRACE_FUNC_ENTER;
	_AKNTRACE( "aSelectionMode is %d", aSelectionMode );
	if (iCurrentItemIndex == -1)   // i.e. no selection
		{
		ClearSelection();
		_AKNTRACE_FUNC_EXIT;
		return;
		}
	TInt newActiveEndIndex = iCurrentItemIndex;

	if ( Flags() & EPaintedSelection )
		{
		switch (aSelectionMode)
			{
		case ENoSelection:
			{
			ClearFlags(EAnchorExists);
			iActiveEndIndex = iCurrentItemIndex;
			DrawItem(iCurrentItemIndex);
			break;
			}
		case ESingleSelection:
			{
			TInt i = 0;
			iAnchorIndex = iCurrentItemIndex;
			iActiveEndIndex = iCurrentItemIndex;
			SetFlags(EAnchorExists);
			TInt selectedItemIndex; 
			while (i < iSelectionIndexes->Count())
				{
				selectedItemIndex = (*(iSelectionIndexes))[i];
                DeselectItem(selectedItemIndex);
				}
			//DrawItem(iActiveEndIndex);
            SelectItemL(newActiveEndIndex);
			}
			break;
		case EContiguousSelection:
			{
			if (newActiveEndIndex == iActiveEndIndex)
				break;

			if (!(iFlags & EAnchorExists))
				{
				iAnchorIndex = newActiveEndIndex;
				SetFlags(EAnchorExists);
				}

			TInt startIndex=0, endIndex=0;
			if ( iActiveEndIndex < newActiveEndIndex )
				{
				startIndex = iActiveEndIndex;
				endIndex = newActiveEndIndex; // - 1;  // select current item too
				}
			else
				{
				startIndex = newActiveEndIndex; // + 1;  // select current item too
				endIndex = iActiveEndIndex;
				}
			SelectRangeL( startIndex, endIndex );		// select always

			iActiveEndIndex = iCurrentItemIndex;
			DrawItem(iActiveEndIndex);
			}
			break;
		case EDisjointSelection:
			ClearFlags(EAnchorExists);
			ToggleItemL(newActiveEndIndex);
			iActiveEndIndex = iCurrentItemIndex;
			break;
		default:
			break;
			}
		}
	else	// Here begins the Eikon original code
		{
		switch (aSelectionMode)
			{
		case ENoSelection:
			DrawItem(iCurrentItemIndex);
			break;
		case ESingleSelection:
			{
			TInt i = 0;
			iAnchorIndex = newActiveEndIndex;
			iActiveEndIndex = newActiveEndIndex;
			SetFlags(EAnchorExists);
			TInt selectedItemIndex; 
			// deselect everything except newActiveEndIndex
			while (i < iSelectionIndexes->Count())
				{
				selectedItemIndex = (*(iSelectionIndexes))[i];
                DeselectItem(selectedItemIndex);
				}
            SelectItemL(newActiveEndIndex);
			}
			break;
		case EContiguousSelection:
			{
			TInt itemIndex=0;
			if (newActiveEndIndex == iActiveEndIndex)
				break;
			if (!(iFlags & EAnchorExists))
				{
				iAnchorIndex = newActiveEndIndex;
				iActiveEndIndex = newActiveEndIndex;
    			SetFlags(EAnchorExists);
				SelectRangeL(iAnchorIndex, newActiveEndIndex);
				break;
				}
			if ((newActiveEndIndex < iActiveEndIndex) && (iActiveEndIndex <= iAnchorIndex))
				SelectRangeL(iActiveEndIndex, newActiveEndIndex);
			else if ((newActiveEndIndex < iActiveEndIndex) && (iActiveEndIndex > iAnchorIndex))
				{
				itemIndex = iActiveEndIndex;
				while ((itemIndex > newActiveEndIndex) && (itemIndex > iAnchorIndex))
					{
                    DeselectItem(itemIndex);
					--itemIndex;
					}
				SelectRangeL(iAnchorIndex, newActiveEndIndex);
				}
			else if ((newActiveEndIndex > iActiveEndIndex) && (iActiveEndIndex < iAnchorIndex))
				{
				itemIndex = iActiveEndIndex;
				while ((itemIndex < newActiveEndIndex) && (itemIndex < iAnchorIndex))
					{
                    DeselectItem(itemIndex);
					++itemIndex;
					}
				SelectRangeL(iAnchorIndex, newActiveEndIndex);
				}
			else if ((newActiveEndIndex > iActiveEndIndex) && (iActiveEndIndex >= iAnchorIndex))
				SelectRangeL(iActiveEndIndex, newActiveEndIndex);
			iActiveEndIndex = newActiveEndIndex;
			DrawItem(iActiveEndIndex);
			}
			break;
		case EDisjointSelection: // toggled behavior
		    // Make a choice whether to mark or unmark
			// We havent made that choice yet.
			if (!ItemIsSelected(newActiveEndIndex)) 
			    {
			    SetFlags(EMarkSelection);
				ClearFlags(EUnmarkSelection);
			}
			else
			    {
			    SetFlags(EUnmarkSelection);
				ClearFlags(EMarkSelection);
			    }

			if (newActiveEndIndex == iActiveEndIndex)
				{
    			ClearFlags(EAnchorExists);
				ToggleItemL(newActiveEndIndex);
				break;
				}
			iAnchorIndex = newActiveEndIndex;
			iActiveEndIndex = newActiveEndIndex;
    		SetFlags(EAnchorExists);
			ToggleItemL(newActiveEndIndex);
			break;
		case EDisjointMarkSelection: // can only mark items, not unmark them
		    // Make a choice whether to mark or unmark
		    if (! (Flags()&EMarkSelection ||Flags()&EUnmarkSelection))
			{
			// We havent made that choice yet.
			if (ItemIsSelected(iAnchorIndex)) 
			    {
            	ClearFlags(EMarkSelection);
			    SetFlags(EUnmarkSelection);
			    }
			else
			    {
            	ClearFlags(EUnmarkSelection);
			    SetFlags(EMarkSelection);
			    }
			}

		    // order of these is important.
		    if (Flags()&EMarkSelection)
            SelectItemL(iActiveEndIndex);
		    else
            DeselectItem(iActiveEndIndex);
		    //iAnchorIndex = newActiveEndIndex;
		    iActiveEndIndex = newActiveEndIndex;
		    //SetFlags(EAnchorExists);
		    if (Flags()&EMarkSelection)
            SelectItemL(newActiveEndIndex);
		    else
            DeselectItem(newActiveEndIndex);
			DrawItem(iCurrentItemIndex);
		    break;
		    
		case EChangeMarkMode:
		    {
		    // Clear flags, correct flag will be set on later.   
        	ClearFlags(EMarkSelection);
        	ClearFlags(EUnmarkSelection);
        	
        	// If item is hidden, use next non-hidden item to decide markmode.
			while( iItemDrawer->Properties(newActiveEndIndex).IsSelectionHidden() 
			       && newActiveEndIndex != iActiveEndIndex )
			    {
			    if ( newActiveEndIndex > iActiveEndIndex )
			        {
			        newActiveEndIndex--;
			        }
			    else 
			        {
                    newActiveEndIndex++;
		            }
			    }

		    // Change Mark Mode to different than current mark is
			if (ItemIsSelected(newActiveEndIndex)) 
			    {
			    SetFlags(EUnmarkSelection);
			    }
			else
			    {
			    SetFlags(EMarkSelection);
			    }
		    }
		    break;
		
	    case EPenMultiselection:
	        {
	        TInt itemIndex=0;
	        TBool mark = (Flags() & EMarkSelection);
	        
			if ((newActiveEndIndex < iActiveEndIndex) && (iActiveEndIndex <= iAnchorIndex))
			    {	
			    if ( mark )
			        {			        
				    SelectRangeL(iActiveEndIndex, newActiveEndIndex);
			        }
			    else 
			        {
				    DeselectRangeL(iActiveEndIndex, newActiveEndIndex);
			        }
			    }
			else if ((newActiveEndIndex < iActiveEndIndex) && (iActiveEndIndex > iAnchorIndex))
				{
				itemIndex = iActiveEndIndex;
				while ((itemIndex > newActiveEndIndex) && (itemIndex > iAnchorIndex))
					{
					if ( mark )
			            {
                        DeselectItem(itemIndex);
			            }
			        else
			            {
                        SelectItemL(itemIndex); 
			            }
					--itemIndex;
					}
                
				if ( mark )
		            {					
			        SelectRangeL(iAnchorIndex, newActiveEndIndex);
		            }
			    else
			        {
				    DeselectRangeL(iAnchorIndex, newActiveEndIndex);			        
			        }
				}
			else if ((newActiveEndIndex > iActiveEndIndex) && (iActiveEndIndex < iAnchorIndex))
				{
				itemIndex = iActiveEndIndex;
				while ((itemIndex < newActiveEndIndex) && (itemIndex < iAnchorIndex))
					{
					if ( mark )
			            {
                        DeselectItem(itemIndex);
			            }
			        else
			            {
                        SelectItemL(itemIndex); 
			            };
			            
					++itemIndex;
					}
                if ( mark )
			        {					
				    SelectRangeL(iAnchorIndex, newActiveEndIndex);
			        }
			    else
			        {			        
				    DeselectRangeL(iAnchorIndex, newActiveEndIndex);
			        }
				}
				// "=" is necessary for Editkey + sigle tab on an item
			else if ((newActiveEndIndex >= iActiveEndIndex) && (iActiveEndIndex >= iAnchorIndex))
			    {
			    if ( mark )
			        {			    
			    	SelectRangeL(iActiveEndIndex, newActiveEndIndex);
				    }
			    else
			        {			        
				    DeselectRangeL(iAnchorIndex, newActiveEndIndex);
			        }
			    }
			    
			iActiveEndIndex = newActiveEndIndex;
			
			DrawItem(iActiveEndIndex);        
			
	        break;
	        }
		 
		default:
			break;
			}
		}
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C void CListBoxView::CalcBottomItemIndex()
/* called by listbox control when either the size of the listbox or the number of items in 
   its model changes
*/
	{
	_AKNTRACE_FUNC_ENTER;
	TInt i = iTopItemIndex;
	TInt totalHeight = 0;
	TInt numberOfVisibleItems = 0;
	// iVerticalOffset is negative (add this to view's height)
	TInt viewHeight = iViewRect.Height();
    viewHeight -= iVerticalOffset;

	ITEM_EXISTS_BEGIN;
	while ((totalHeight < viewHeight) && (ITEM_EXISTS(i)))
		{
		totalHeight += iItemHeight;
		++ i;
		++ numberOfVisibleItems;
		}
		
    iBottomItemIndex = Max(0, iTopItemIndex + numberOfVisibleItems - 1);
    _AKNTRACE( "iBottomItemIndex is %d", iBottomItemIndex );
    _AKNTRACE_FUNC_EXIT;
	}

EXPORT_C TInt CListBoxView::NumberOfItemsThatFitInRect(const TRect& aRect) const
	{
	if (iItemHeight == 0)
	    {
	    _AKNTRACE( "Number of items is 0" );
		return 0;
	    }
    TInt items = aRect.Height() / iItemHeight;
	if ( ( iVerticalOffset != 0 ) || ( (aRect.Height() - iVerticalOffset) % iItemHeight > 0 ) ) items++;
	_AKNTRACE( "Number of items is %d", items );
	return items;
	}

EXPORT_C void CListBoxView::DeselectRangeL(TInt aItemIndex1, TInt aItemIndex2)
	{
	TInt startItem, endItem;
	startItem = Min(aItemIndex1, aItemIndex2);
	endItem = Max(aItemIndex1, aItemIndex2);
	for (TInt i = startItem; i <= endItem; i++)
	    {	    
        DeselectItem(i);
	    }
	}

EXPORT_C TBool CListBoxView::ItemIsVisible(TInt aItemIndex) const
	{
	if ((aItemIndex == 0) && !(ITEM_EXISTS_ONCE(aItemIndex)))
		return EFalse;
	
	return ((aItemIndex >= iTopItemIndex) && (aItemIndex <= iBottomItemIndex));
	}

EXPORT_C TPoint CListBoxView::ItemPos(TInt aItemIndex) const
	{
	return TPoint(-iHScrollOffset + iViewRect.iTl.iX, iViewRect.iTl.iY + 
		(aItemIndex - iTopItemIndex) * iItemHeight + iVerticalOffset);
	}

EXPORT_C TSize CListBoxView::ItemSize(TInt /*aItemIndex*/) const
	{
	/*This return value controls the actual size of item which the text may
	or may not be clipped and truncated with an ellipse to fit into*/
	return TSize(LafListBoxView::ItemWidth(iViewRect.Width(), DataWidth()), iItemHeight);
	}

EXPORT_C TBool CListBoxView::XYPosToItemIndex(TPoint aPosition, TInt& aItemIndex) const
	{
	// returns ETrue and sets aItemIndex to the index of the item whose bounding box contains aPosition
	// returns EFalse if no such item exists 
	_AKNTRACE_FUNC_ENTER;
	TBool itemFound = EFalse;
	if (iItemHeight == 0) 
	    {
	    _AKNTRACE_FUNC_EXIT;
		return EFalse;
	    }
	if (iViewRect.Contains(aPosition))
		{
		// aPosition is inside the display area
		TInt yOffsetFromViewRectOrigin = aPosition.iY - iViewRect.iTl.iY - iVerticalOffset;
		TInt numberOfItemsFromTheTop = yOffsetFromViewRectOrigin / iItemHeight;
		TInt itemAtSpecifiedPos = iTopItemIndex + numberOfItemsFromTheTop;
		if (ITEM_EXISTS_ONCE(itemAtSpecifiedPos))
			{
			aItemIndex = itemAtSpecifiedPos;
			itemFound = ETrue;
			}
		}
	_AKNTRACE_FUNC_EXIT;
	return itemFound;
	}

EXPORT_C void CListBoxView::MoveCursorL(TCursorMovement aCursorMovement, TSelectionMode aSelectionMode)
	{
	_AKNTRACE_FUNC_ENTER;
	_AKNTRACE( "aSelectionMode is %d", aSelectionMode );
	TInt pageSize = NumberOfItemsThatFitInRect(iViewRect);
	TInt numOfItems = iModel->NumberOfItems(); 
	switch (aCursorMovement)
		{
	case ECursorNextItem:
		VerticalMoveToItemL(iCurrentItemIndex + 1, aSelectionMode);
		break;
	case ECursorPreviousItem:
		VerticalMoveToItemL(iCurrentItemIndex - 1, aSelectionMode);
		break;
	case ECursorNextPage:
		VerticalMoveToItemL(iCurrentItemIndex + Min((pageSize - 1), numOfItems - 1 - iCurrentItemIndex),
							   aSelectionMode);
		break;
	case ECursorPreviousPage:
		VerticalMoveToItemL(iCurrentItemIndex - Min((pageSize - 1), iCurrentItemIndex),
						   aSelectionMode);
		break;
	case ECursorFirstItem:
		VerticalMoveToItemL(0, aSelectionMode);
		break;
	case ECursorLastItem:
		if (numOfItems > 0)
			VerticalMoveToItemL(numOfItems-1, aSelectionMode);
		break;
		
		case ECursorNextScreen:
		    {
		    TInt targetItem = iTopItemIndex + pageSize;
		    if (targetItem > numOfItems - pageSize) targetItem = numOfItems - pageSize;
		    if (targetItem < 0) targetItem = 0;
		    VScrollTo(targetItem);
		    SetCurrentItemIndex(targetItem);
		    }
		    break;
		case ECursorPrevScreen:
		    {
		    TInt targetItem = iTopItemIndex - pageSize;
		    if (targetItem < 0) targetItem = 0;
		    VScrollTo(targetItem);
		    SetCurrentItemIndex(targetItem);
		    }
	    break;
	default:
		break;
		};
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C void CListBoxView::VerticalMoveToItemL(TInt aTargetItemIndex, TSelectionMode aSelectionMode)
	{
	// SERIES60 IMPLEMENTATION
	_AKNTRACE_FUNC_ENTER;
	if (ITEM_EXISTS_ONCE(aTargetItemIndex))
	    {
	    TInt oldCurrentItemIndex = iCurrentItemIndex;
	    iCurrentItemIndex = aTargetItemIndex;

	    
        TInt oldVerticalOffset = iVerticalOffset;
	    TInt newTopItemIndex = CalcNewTopItemIndexSoItemIsVisible(aTargetItemIndex);
	    if ( oldVerticalOffset != iVerticalOffset )
	        {
	        iFlags |= EOffsetChanged;
	        }
	    
	    TInt oldVOffset = oldCurrentItemIndex - iTopItemIndex;
	    TInt newVOffset = aTargetItemIndex    - newTopItemIndex;
        // We calculate if the change in highlight position moves highlight in screen
	    TBool sameHighlightPos = oldVOffset == newVOffset;

        // When a partially visible item gets focus, it should be fully visible.
        // 'iFlags & EOffsetChanged' can be use to judge in this case.
        if ((ItemIsVisible(iCurrentItemIndex)) && !(iFlags & EOffsetChanged))     
	        {	    
	        if (!sameHighlightPos && 
	                (!ItemIsSelected(oldCurrentItemIndex) ||
	                        aSelectionMode != ESingleSelection))
	            {
                DrawItem(oldCurrentItemIndex);
	            }	    
	        }
	    else // items will get redrawn anyway
	        {
	        ScrollToMakeItemVisible(iCurrentItemIndex);
	        }
        UpdateSelectionL(aSelectionMode);
        iFlags &= ~EOffsetChanged;
	    }
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C void CListBoxView::VScrollTo(TInt aNewTopItemIndex)
	{
	_AKNTRACE_FUNC_ENTER;
	if (iTopItemIndex == aNewTopItemIndex && !(iFlags & EOffsetChanged))
	    {
	    _AKNTRACE_FUNC_EXIT;
		return;
	    }
	if (RedrawDisabled())
	    {
	    SetTopItemIndex(aNewTopItemIndex);
	    _AKNTRACE_FUNC_EXIT;
		return;
	    }
	TRect minRedrawRect;
	HideMatcherCursor();
	VScrollTo(aNewTopItemIndex, minRedrawRect);


	if (ItemIsVisible(iCurrentItemIndex))
		DrawMatcherCursor();
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C void CListBoxView::VScrollTo(TInt aNewTopItemIndex, TRect& aMinRedrawRect)
	{
	_AKNTRACE_FUNC_ENTER;
    if (iTopItemIndex == aNewTopItemIndex && !(iFlags & EOffsetChanged))
        {
        _AKNTRACE_FUNC_EXIT;
	    return;
        }
	if (RedrawDisabled()) 
	    {
	    SetTopItemIndex(aNewTopItemIndex);   
	    _AKNTRACE_FUNC_EXIT;
	    return;
	    }
	aMinRedrawRect.SetRect(iViewRect.iTl,iViewRect.Size());
	SetTopItemIndex(aNewTopItemIndex);
	Draw(&aMinRedrawRect);
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C void CListBoxView::HScroll(TInt aHScrollAmount)
	{
	_AKNTRACE_FUNC_ENTER;
	if (RedrawDisabled())
	    {
	    _AKNTRACE_FUNC_EXIT;
		return;
	    }
	if (aHScrollAmount == 0)
	    {
	    _AKNTRACE_FUNC_EXIT;
		return;
	    }
	TInt maxNumOfPixelsScrolledRight = DataWidth() - VisibleWidth(iViewRect);
	if (maxNumOfPixelsScrolledRight <= 0)
	    {
	    _AKNTRACE_FUNC_EXIT;
		return;
	    }
	TInt oldHScrollOffset = iHScrollOffset;
	iHScrollOffset += aHScrollAmount;
	iHScrollOffset = Max(0, Min(iHScrollOffset, maxNumOfPixelsScrolledRight));
	DrawMatcherCursor();
	TInt actualScrollAmount = iHScrollOffset - oldHScrollOffset;
	iWin->Scroll(iViewRect, TPoint(-actualScrollAmount, 0));
	TRect redrawRect(iViewRect.iTl+TPoint(iViewRect.Width()-actualScrollAmount,0),TSize(actualScrollAmount,iViewRect.Height()));
	if (actualScrollAmount<0)
		redrawRect.SetRect(iViewRect.iTl,TSize(-actualScrollAmount,iViewRect.Height()));
	redrawRect.Intersection(iViewRect);
    iItemDrawer->Gc()->Clear( redrawRect );
	iWin->Invalidate(redrawRect);
	iWin->BeginRedraw(redrawRect);
	Draw(&redrawRect);
	iWin->EndRedraw();
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C TInt CListBoxView::HScrollOffset() const
	{
	return iHScrollOffset;
	}

EXPORT_C void CListBoxView::SetHScrollOffset(TInt aHScrollOffset)
	{
	iHScrollOffset = aHScrollOffset;
	}

EXPORT_C void CListBoxView::SetItemHeight(TInt aItemHeight)
	{
	_AKNTRACE_FUNC_ENTER;
	_AKNTRACE( "aItemHeight is %d", aItemHeight );
	SetItemOffsetInPixels( 0 );
	iItemHeight = aItemHeight;
	iItemDrawer->SetItemCellSize(ItemSize());
	_AKNTRACE_FUNC_EXIT;
	}
	
EXPORT_C void CListBoxView::SetViewRect(const TRect& aRect)
	{
    if ( aRect != iViewRect && iViewRect != TRect::EUninitialized )
        {
        iGc->Deactivate();
        iGc->Activate( *iWin );
        }

	iViewRect = aRect;
	iItemDrawer->SetViewRect(iViewRect);
	iItemDrawer->SetItemCellSize(ItemSize());
	}

EXPORT_C TRect CListBoxView::ViewRect() const
	{
	return iViewRect;
	}

EXPORT_C void CListBoxView::DrawItem(TInt aItemIndex) const
	{
	_AKNTRACE_FUNC_ENTER;
	if (RedrawDisabled() || !IsVisible())
	    {
	    _AKNTRACE_FUNC_EXIT;
		return;
	    }

    TBool transparencyEnabled( CAknEnv::Static()->TransparencyEnabled() );

    if ((ITEM_EXISTS_ONCE(aItemIndex)) && ItemIsVisible(aItemIndex))
		{
		TBool drawingInitiated = ETrue;

		if ( transparencyEnabled )
		    {
		    if ( iWin && iWin->GetDrawRect() == TRect::EUninitialized )
			    {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
                MAknListBoxTfxInternal* transApi =
                    CAknListLoader::TfxApiInternal( iGc );
                drawingInitiated = transApi && !transApi->EffectsDisabled();
#else
                drawingInitiated = EFalse;
#endif			
                }

            if ( !drawingInitiated )
			    {
                TRect rect( ItemPos(aItemIndex), ItemSize(aItemIndex) );
			    rect.Intersection( iViewRect );
			    iWin->Invalidate( rect );
			    iWin->BeginRedraw( rect );
			    }
		    }
		
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        MAknListBoxTfxInternal *transApi = CAknListLoader::TfxApiInternal( iGc );
        if ( transApi )
            {
            TRect rect( ItemPos( aItemIndex ),
                                ItemSize(aItemIndex) );
            transApi->BeginRedraw( MAknListBoxTfxInternal::EListItem, rect, aItemIndex );
            transApi->StartDrawing( MAknListBoxTfxInternal::EListItem );
            }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
        
        iGc->SetClippingRect( iViewRect );

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        if ( transApi )
            {
            transApi->StopDrawing();
            }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
        
		TBool currentItem = (aItemIndex == iCurrentItemIndex);

		iItemDrawer->DrawItem(aItemIndex, ItemPos(aItemIndex), ItemIsSelected(aItemIndex),
			currentItem, (iFlags&EEmphasized)>0, (iFlags&EDimmed)>0 );

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        if ( transApi )
            {
            transApi->StartDrawing( MAknListBoxTfxInternal::EListItem );
            }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
            
		iGc->CancelClippingRect();

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        if ( transApi )
            {
            transApi->StopDrawing();
            }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
		
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        if ( transApi )
            {
            transApi->EndRedraw( MAknListBoxTfxInternal::EListItem, aItemIndex );
            }
#endif // RD_UI_TRANSITION_EFFECTS_LIST

		if ( transparencyEnabled && !drawingInitiated )
			{
			iWin->EndRedraw();
			}
		}
    _AKNTRACE_FUNC_EXIT;
    }


EXPORT_C void CListBoxView::Draw( const TRect* /*aClipRect*/ ) const
	{
	_AKNTRACE_FUNC_ENTER;
    if ( RedrawDisabled() || !IsVisible() )
        {
        _AKNTRACE_FUNC_EXIT;
        return;
        }

	__ASSERT_DEBUG( iModel, Panic( EEikPanicListBoxNoModel ) );

	if ( iModel->NumberOfItems() == 0 )
	    {
	    //DrawEmptyList();
	    }
	else
		{
		TInt firstPotentialItemIndex = iTopItemIndex;
		TInt lastPotentialItemIndex =
            iTopItemIndex + NumberOfItemsThatFitInRect( iViewRect ) - 1;
		TInt i;
        ITEM_EXISTS_BEGIN;
        for ( i = firstPotentialItemIndex; i <= lastPotentialItemIndex; i++ )
            {
            if ( ITEM_EXISTS( i ) )
                {
                DrawItem( i );
                }
            else
                {
                break;
                }
            }

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal( iGc );
        if ( transApi )
        	{
        	transApi->StartDrawing( MAknListBoxTfxInternal::EListView );
        	}
#endif // RD_UI_TRANSITION_EFFECTS_LIST

        TBool backgroundDrawn( EFalse );
        TRect usedPortionOfViewRect(
            iViewRect.iTl,
            TSize( iViewRect.Width(),
                   ( i - firstPotentialItemIndex ) * iItemHeight ) );

        if ( iExtension && iExtension->iListBox )
            {
            MAknsSkinInstance* skin = AknsUtils::SkinInstance();
            MAknsControlContext* cc =
                AknsDrawUtils::ControlContext( iExtension->iListBox );

            if ( cc )
                {
                backgroundDrawn =
                    AknsDrawUtils::BackgroundBetweenRects( skin,
                                                           cc,
                                                           iExtension->iListBox,
                                                           *iItemDrawer->Gc(),
                                                           iViewRect,
                                                           usedPortionOfViewRect );
                }
            }

        if ( !backgroundDrawn )
            {
            iItemDrawer->Gc()->SetBrushColor( iBackColor );
            DrawUtils::ClearBetweenRects( *iItemDrawer->Gc(),
                                          iViewRect,
                                          usedPortionOfViewRect );
            }

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        if ( transApi )
            {
            transApi->StopDrawing();
            }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
		}
	_AKNTRACE_FUNC_EXIT;
	}


EXPORT_C void CListBoxView::SetTopItemIndex(TInt aNewTopItemIndex)
	{
	_AKNTRACE_FUNC_ENTER;
	TBool validIndex = (aNewTopItemIndex == 0) || (ITEM_EXISTS_ONCE(aNewTopItemIndex)); 
	__ASSERT_ALWAYS(validIndex, Panic(EEikPanicListBoxInvalidTopItemIndexSpecified));
	iTopItemIndex = aNewTopItemIndex;
	CalcBottomItemIndex();	
	_AKNTRACE_FUNC_EXIT;
	}
		
EXPORT_C void CListBoxView::SetCurrentItemIndex(TInt aItemIndex)
	{
	_AKNTRACE_FUNC_ENTER;
	TBool validIndex = (aItemIndex == 0) || (ITEM_EXISTS_ONCE(aItemIndex)); 
	__ASSERT_ALWAYS(validIndex, Panic(EEikPanicListBoxInvalidCurrentItemIndexSpecified));
	iCurrentItemIndex = aItemIndex;	
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C TInt CListBoxView::CurrentItemIndex() const
	{
	if (ITEM_EXISTS_ONCE(iCurrentItemIndex))
		return iCurrentItemIndex;
	else
		return -1;		// means there is no current item
	}

EXPORT_C TBool CListBoxView::ScrollToMakeItemVisible(TInt aItemIndex)
	{
	_AKNTRACE_FUNC_ENTER;
	TInt oldVerticalOffset = iVerticalOffset;
	TInt newTopItemIndex = CalcNewTopItemIndexSoItemIsVisible( aItemIndex );
	
	if ( ( ItemIsVisible( aItemIndex ) || aItemIndex < 0 ) 
	        && iVerticalOffset == oldVerticalOffset
	        && !(iFlags & EOffsetChanged) )
	    {
	    _AKNTRACE_FUNC_EXIT;
	    return EFalse;
	    }
	
	if ( iVerticalOffset != oldVerticalOffset )
	    {
	    iFlags |= EOffsetChanged;
	    }
	
    VScrollTo( newTopItemIndex );
    
    iFlags &= ~EOffsetChanged;
    
    _AKNTRACE_FUNC_EXIT;
    return ETrue;
	}

EXPORT_C TInt CListBoxView::CalcNewTopItemIndexSoItemIsVisible(TInt aItemIndex) const
	{
	_AKNTRACE_FUNC_ENTER;
#ifdef _DEBUG
    RDebug::Print( _L( "CListBoxView::CalcNewTopItemIndexSoItemIsVisible" ) );
#endif // _DEBUG
	TInt newTopItemIndex=iTopItemIndex;
	const TInt numItemsThatFitInRect=NumberOfItemsThatFitInRect(iViewRect);
	if (aItemIndex < iTopItemIndex || numItemsThatFitInRect == 0)
		newTopItemIndex = aItemIndex;
	else if (aItemIndex > iBottomItemIndex)
		newTopItemIndex = aItemIndex - numItemsThatFitInRect + 1;

	if (!ITEM_EXISTS_ONCE(newTopItemIndex) && newTopItemIndex != 0 )
		{ // if application fails to call HandleItemAdditionL(), we might go here.
		  // we dont want our OfferKeyEventL() to panic in that case.
		newTopItemIndex = iTopItemIndex;
		}
	
	CListBoxView* me = const_cast<CListBoxView*>( this );
	// change vertical offset value if needed
	if ( aItemIndex <= iTopItemIndex && iVerticalOffset < 0 )
	    {
	    me->SetItemOffsetInPixels( 0 );
	    }
	else if ( aItemIndex >= iBottomItemIndex && aItemIndex >= ( numItemsThatFitInRect - 1 ) ) 
	    {
        TInt delta = iViewRect.Height() % iItemHeight;
        
        if ( delta > 0 )
            {
            me->SetItemOffsetInPixels( -( iItemHeight - delta ) );
            }
        else
            {
            me->SetItemOffsetInPixels( 0 );
            }
	    }

	_AKNTRACE_FUNC_EXIT;
    return newTopItemIndex;
	}

EXPORT_C void CListBoxView::DrawMatcherCursor()
	{
    // DrawMatcherCursor code is broken in S60, it will crash some lists. There
    // is no need to draw matcher cursor in S60 -> deprecated method.
    }

EXPORT_C void CListBoxView::HideMatcherCursor()
	{
	if (!(iFlags & EHasMatcherCursor))
		return;	
    iGroupWin->CancelTextCursor(); 
	}

EXPORT_C void CListBoxView::SetMatcherCursorPos(TInt aPosWithinCurrentItem)
	{
	iMatcherCursorPos = aPosWithinCurrentItem;
	}

EXPORT_C TInt CListBoxView::MatcherCursorPos() const
	{
	return iMatcherCursorPos;
	}

EXPORT_C void CListBoxView::SetMatcherCursorColor(TRgb aColor)
	{
	iMatcherCursorColor = aColor;
	}

EXPORT_C void CListBoxView::SetMatcherCursor(TBool aMatcherCursor)
	{
	if (aMatcherCursor)
		SetFlags(EHasMatcherCursor);
	else
		ClearFlags(EHasMatcherCursor);
	}

EXPORT_C void CListBoxView::SetEmphasized(TBool aEmphasized)
	{
	if (aEmphasized)
		SetFlags(EEmphasized);
	else
		ClearFlags(EEmphasized);
	}

EXPORT_C void CListBoxView::SetDimmed(TBool aDimmed)
	{
	if (aDimmed)
		SetFlags(EDimmed);
	else
		ClearFlags(EDimmed);
	}

EXPORT_C void CListBoxView::SetDisableRedraw(TBool aDisableRedraw)
	{
	if (aDisableRedraw)
		SetFlags(EDisableRedraw);
	else
		ClearFlags(EDisableRedraw);
	}

EXPORT_C TBool CListBoxView::RedrawDisabled() const
	{
	return (iFlags & EDisableRedraw);
	}

EXPORT_C void CListBoxView::SetPaintedSelection( TBool aPaintedSelection )
    {
	if ( aPaintedSelection )
	    SetFlags( EPaintedSelection );
	else
        ClearFlags( EPaintedSelection );
    }

EXPORT_C TInt CListBoxView::DataWidth() const
	{
	return iDataWidth;
	}

EXPORT_C TInt CListBoxView::VisibleWidth(const TRect& aRect) const
	{
	return aRect.Width();
	}

EXPORT_C void CListBoxView::CalcDataWidth()
	{
    // The loop below causes HUGE performance problems for no reason
    // with long lists. 
#if NOT_NEEDED_IN_SERIES60
	// assumes that iModel and iItemDrawer are both valid 
	// calculate data width (in pixels)
	TInt largestItemWidth = 0;

    TInt i = 0;
    while (ITEM_EXISTS(i))
        {
        largestItemWidth = Max(largestItemWidth, iItemDrawer->ItemWidthInPixels(i)); 
        ++ i;
        }
    iDataWidth = largestItemWidth;
	iDataWidth += LafListBox::InnerGutter();
	iItemDrawer->SetItemCellSize(ItemSize());
#endif
	}

EXPORT_C TRgb CListBoxView::BackColor() const
	{
	return iBackColor;
	}

EXPORT_C void CListBoxView::SetBackColor(TRgb aColor)
	{
	iBackColor = aColor;
	}

EXPORT_C TRgb CListBoxView::TextColor() const
	{
	return iTextColor;
	}

EXPORT_C void CListBoxView::SetTextColor(TRgb aColor)
	{
	iTextColor = aColor;
	}


EXPORT_C void CListBoxView::DrawEmptyList(const TRect & /*aClientRect*/) const
    {
    }

void CListBoxView::DisableVerticalLineDrawing( TBool aDisable )
    {
    iDisableVerticalLineDrawing = aDisable;
    }

EXPORT_C void CListBoxView::SetItemOffsetInPixels(TInt aOffset)
	{
	if ( iExtension && !iExtension->iScrollingDisabled )
	    {
	    iVerticalOffset = aOffset;
	    }
	else
	    {
	    // Make sure that offset is 0 when
	    // panning is disabled
	    iVerticalOffset = 0;    
	    }    

#ifdef _DEBUG
    RDebug::Print( _L( "CListBoxView::SetItemOffsetInPixels, iVerticalOffset = %d" ), iVerticalOffset );
#endif // _DEBUG
	}

EXPORT_C TInt CListBoxView::ItemOffsetInPixels() const
    {
    return iVerticalOffset;
    }
    
void CListBoxView::SetScrolling( TBool aIsScrolling )
    {
    if ( iExtension )
        {
        iExtension->iScrolling = aIsScrolling;
        }
    }
    
void CListBoxView::SetItemIndex( TInt aItemIndex )
    {
    iCurrentItemIndex = aItemIndex;
    }


// ---------------------------------------------------------------------------
// Returns ETrue if item is partially visible.
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CListBoxView::ItemIsPartiallyVisible( TInt aItemIndex ) const
    {
    _AKNTRACE_FUNC_ENTER;
    TPoint itemPosition( ItemPos( aItemIndex ) );
    TBool itemPartiallyVisible =
        ( itemPosition.iY < iViewRect.iTl.iY &&
          itemPosition.iY + iItemHeight >= iViewRect.iTl.iY ) ||
        ( itemPosition.iY <= iViewRect.iBr.iY &&
          itemPosition.iY + iItemHeight > iViewRect.iBr.iY );
    _AKNTRACE( "itemPartiallyVisible is %d", itemPartiallyVisible );
    _AKNTRACE_FUNC_EXIT;
    return itemPartiallyVisible;
    }



// class CSnakingListBoxView

EXPORT_C CSnakingListBoxView::CSnakingListBoxView()
    {
	iColumnWidth = 100;
    }

EXPORT_C CSnakingListBoxView::~CSnakingListBoxView()
    {
    }

EXPORT_C void CSnakingListBoxView::CalcBottomItemIndex() 
	{
	_AKNTRACE_FUNC_ENTER;
	TInt i = iTopItemIndex;
	iBottomItemIndex = i;
	if ((iColumnWidth == 0) || (iItemHeight == 0))
	    {
	    _AKNTRACE_FUNC_EXIT;	    
		return;
	    }
	TInt xpos = iViewRect.iTl.iX;
	TInt ypos = iViewRect.iTl.iY;	 
	TInt maxXPos = xpos + (iViewRect.Width() / iColumnWidth) * iColumnWidth;
	TInt maxYPos = ypos + ((iViewRect.Height() / iItemHeight) * iItemHeight)- iItemHeight;
	ITEM_EXISTS_BEGIN;
	while ((xpos < maxXPos) && (ITEM_EXISTS(i+1)))
		{
		++ i;
		if (ypos == maxYPos)
			{
			ypos = iViewRect.iTl.iY;
			xpos += iColumnWidth;
			} 
		else
			ypos += iItemHeight;
		}
	if ((i > 0) && (xpos >= maxXPos))
		--i;
	iBottomItemIndex = i;
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C void CSnakingListBoxView::CalcRowAndColIndexesFromItemIndex(TInt aItemIndex, TInt& aRowIndex, TInt& aColIndex) const
	{
	// should panic if iItemHeight or iViewRect.Height() is 0
	// assumes specified item is currently visible
	_AKNTRACE_FUNC_ENTER;
	TInt numOfItemsFromFirstVisibleItem = (aItemIndex - iTopItemIndex);
	TInt numOfItemsPerColumn = NumberOfItemsPerColumn();
	aColIndex = numOfItemsFromFirstVisibleItem / numOfItemsPerColumn;
	aRowIndex = numOfItemsFromFirstVisibleItem % numOfItemsPerColumn;
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C TInt CSnakingListBoxView::NumberOfItemsPerColumn() const
	{
	TInt numOfItemsPerColumn = iViewRect.Height() / iItemHeight;
	return (numOfItemsPerColumn<1? 1: numOfItemsPerColumn);
	}

EXPORT_C void CSnakingListBoxView::CalcItemIndexFromRowAndColIndexes(TInt& aItemIndex, TInt aRowIndex, TInt aColIndex) const
	{
	_AKNTRACE_FUNC_ENTER;
	__ASSERT_DEBUG((aRowIndex >= 0), Panic(EEikPanicListBoxInvalidRowIndexSpecified));
	__ASSERT_DEBUG((aColIndex >= 0), Panic(EEikPanicListBoxInvalidColIndexSpecified));
	// should panic if iItemHeight is 0
	TInt numOfItemsPerColumn = NumberOfItemsPerColumn();
	aItemIndex = iTopItemIndex + ((aColIndex * numOfItemsPerColumn) + aRowIndex); 
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C TPoint CSnakingListBoxView::ItemPos(TInt aItemIndex) const
	{
	TInt rowIndex, colIndex;
	CalcRowAndColIndexesFromItemIndex(aItemIndex, rowIndex, colIndex);
	return TPoint(iViewRect.iTl.iX + colIndex * iColumnWidth, iViewRect.iTl.iY + rowIndex * iItemHeight);
	}

EXPORT_C TBool CSnakingListBoxView::XYPosToItemIndex(TPoint aPosition, TInt& aItemIndex) const
	{
	// returns ETrue and sets aItemIndex to the index of the item whose bounding box contains aPosition
	// returns EFalse if no such item exists 
	_AKNTRACE_FUNC_ENTER;
	TBool itemFound = EFalse;
	if ((iColumnWidth == 0) || (iItemHeight == 0))
	    {
	    _AKNTRACE_FUNC_EXIT;
		return EFalse;
	    }
	if (iViewRect.Contains(aPosition))
		{
		// aPosition is inside the display area
		TInt yOffsetFromViewRectOrigin = aPosition.iY - iViewRect.iTl.iY;
		TInt xOffsetFromViewRectOrigin = aPosition.iX - iViewRect.iTl.iX;
		TInt colIndex = xOffsetFromViewRectOrigin / iColumnWidth;
		TInt rowIndex = yOffsetFromViewRectOrigin / iItemHeight;
		// now work out the item index given that we know which row and column it is in 
		TInt itemIndex;
		CalcItemIndexFromRowAndColIndexes(itemIndex, rowIndex, colIndex);
		if ((ITEM_EXISTS_ONCE(itemIndex)) && (ItemIsVisible(itemIndex)))
			{
			aItemIndex = itemIndex;
			itemFound = ETrue;
			}
		}
	_AKNTRACE_FUNC_EXIT;
	return itemFound;
	}

EXPORT_C void CSnakingListBoxView::MoveCursorL(TCursorMovement aCursorMovement, TSelectionMode aSelectionMode)
	{
	if (aCursorMovement == ECursorNextColumn)
		MoveToNextColumnL(aSelectionMode);
	else if (aCursorMovement == ECursorPreviousColumn)
		MoveToPreviousColumnL(aSelectionMode);
	else 
		CListBoxView::MoveCursorL(aCursorMovement, aSelectionMode);
	}

EXPORT_C TSize CSnakingListBoxView::ItemSize(TInt /*aItemIndex*/) const
	{
	return TSize(iColumnWidth, iItemHeight);
	}

EXPORT_C void CSnakingListBoxView::SetColumnWidth(TInt aColumnWidth)
	{
	TBool validColumnWidth = (aColumnWidth > 0);
	__ASSERT_ALWAYS(validColumnWidth, Panic(EEikPanicListBoxInvalidColumnWidthSpecified));
	iColumnWidth = aColumnWidth;
	CalcBottomItemIndex();
	iItemDrawer->SetItemCellSize(ItemSize());
	}

EXPORT_C TInt CSnakingListBoxView::NumberOfItemsThatFitInRect(const TRect& aRect) const
	{
	_AKNTRACE_FUNC_ENTER;
	if ((iItemHeight == 0) || (iColumnWidth == 0))
	    {
	    _AKNTRACE_FUNC_EXIT;
		return 0;
	    }
	TInt numOfRows = aRect.Height() / iItemHeight;
	TInt numOfCols = aRect.Width() / iColumnWidth;
	_AKNTRACE_FUNC_EXIT;
	return (numOfRows * numOfCols);
	}

EXPORT_C void CSnakingListBoxView::ClearUnusedItemSpace(TInt aStartItemIndex, TInt aEndItemIndex) const
	{
	TRect blankRect;
	for (TInt i = aStartItemIndex; i <= aEndItemIndex; i++)
		{
		blankRect.SetRect(ItemPos(i), ItemSize());
		iItemDrawer->ClearRect(blankRect);
		}
	}

EXPORT_C void CSnakingListBoxView::MoveToPreviousColumnL(TSelectionMode aSelectionMode)
	{
	_AKNTRACE_FUNC_ENTER;
	TInt oldCurrentItemIndex = iCurrentItemIndex;
	TInt indexOfNewCurrentItem = iCurrentItemIndex;
	// TInt indexOfNewTopItem = iTopItemIndex;
	TInt numOfItemsPerColumn = NumberOfItemsPerColumn();
	indexOfNewCurrentItem = iCurrentItemIndex - numOfItemsPerColumn;
	if (indexOfNewCurrentItem < 0) 
	    {
	    _AKNTRACE_FUNC_EXIT;
		return;
	    }
	if (ITEM_EXISTS_ONCE(indexOfNewCurrentItem))
		{
		iCurrentItemIndex = indexOfNewCurrentItem;
		if (!(ItemIsSelected(oldCurrentItemIndex)) || (aSelectionMode != ESingleSelection)) 
			DrawItem(oldCurrentItemIndex);
		if (iCurrentItemIndex < iTopItemIndex)
			{
			UpdateSelectionL(aSelectionMode);
			ScrollToMakeItemVisible(iCurrentItemIndex);
			}
		else
			{
			ScrollToMakeItemVisible(iCurrentItemIndex);
			UpdateSelectionL(aSelectionMode);
			}
		}
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C void CSnakingListBoxView::MoveToNextColumnL(TSelectionMode aSelectionMode)
	{
	_AKNTRACE_FUNC_ENTER;
	TInt oldCurrentItemIndex = iCurrentItemIndex;
	TInt indexOfNewCurrentItem = iCurrentItemIndex;
	TInt numOfItemsPerColumn = NumberOfItemsPerColumn();
	indexOfNewCurrentItem = iCurrentItemIndex + numOfItemsPerColumn;
	ITEM_EXISTS_BEGIN;
	if (ITEM_EXISTS(indexOfNewCurrentItem) == EFalse)
		{
		TInt indexOfItemAtTopOfTargetCol = (indexOfNewCurrentItem / numOfItemsPerColumn) * numOfItemsPerColumn;
		if (! (ITEM_EXISTS(indexOfItemAtTopOfTargetCol)))
		    {
		    _AKNTRACE_FUNC_EXIT;
			return;		// no more columns of data to the right, so just return
		    }
		// there are more columns of data available to the right of the current column
		// since there is no item at the expected position, look for an item further up in the same column
		TInt i = indexOfNewCurrentItem;
		while (ITEM_EXISTS(i) == EFalse)
			--i;
		indexOfNewCurrentItem = i;
		}
	iCurrentItemIndex = indexOfNewCurrentItem;
	if (!(ItemIsSelected(oldCurrentItemIndex)) || (aSelectionMode != ESingleSelection)) 
		DrawItem(oldCurrentItemIndex);
	if (iCurrentItemIndex > iBottomItemIndex)
		{
		UpdateSelectionL(aSelectionMode);
		ScrollToMakeItemVisible(iCurrentItemIndex);
		}
	else 
		{
		ScrollToMakeItemVisible(iCurrentItemIndex);
		UpdateSelectionL(aSelectionMode);
		}
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C TInt CSnakingListBoxView::CalcNewTopItemIndexSoItemIsVisible(TInt aItemIndex) const
	{
	_AKNTRACE_FUNC_ENTER;
	if (aItemIndex == iTopItemIndex)
	    {
	    _AKNTRACE_FUNC_EXIT;
		return iTopItemIndex;
	    }
	TInt newTopItemIndex = iTopItemIndex;
	TInt numOfItemsPerColumn = NumberOfItemsPerColumn();
	TInt colIndexOfTargetItem = aItemIndex / numOfItemsPerColumn;
	TInt numOfColsThatFitInViewRect = VisibleWidth(iViewRect);
	if (aItemIndex < iTopItemIndex)
		newTopItemIndex = colIndexOfTargetItem * numOfItemsPerColumn;
	else if (aItemIndex > iBottomItemIndex)
		{
		TInt colIndexOfNewBottomItem = colIndexOfTargetItem;
		TInt colIndexOfNewTopItem = colIndexOfNewBottomItem - (numOfColsThatFitInViewRect - 1);
		newTopItemIndex = colIndexOfNewTopItem * numOfItemsPerColumn;
		}
	_AKNTRACE_FUNC_EXIT;
	return newTopItemIndex;
	}

EXPORT_C void CSnakingListBoxView::HScroll(TInt aHScrollAmount)
	{
	// note: aHScrollAmount is assumed to be specified in terms of number of columns; 
	//       a negative value ==> we need to scroll view contents to the right
	_AKNTRACE_FUNC_ENTER;
	if ((aHScrollAmount == 0) || (iItemHeight == 0))
	    {
	    _AKNTRACE_FUNC_EXIT;
		return;
	    }
	if (RedrawDisabled())
	    {
	    _AKNTRACE_FUNC_EXIT;
		return;
	    }
	iHScrollOffset += aHScrollAmount;
	TInt numOfColsThatFitInViewRect = VisibleWidth(iViewRect);
	TInt numOfItemsPerColumn = NumberOfItemsPerColumn();
	if (Abs(aHScrollAmount) >= numOfColsThatFitInViewRect)
		{
		iTopItemIndex = iTopItemIndex + (numOfItemsPerColumn * aHScrollAmount);
		CalcBottomItemIndex();
		Draw();
		}
	else
		{
		TInt oldTopItemIndex = iTopItemIndex;
		TInt usedViewRectPortionWidth = VisibleWidth(iViewRect) * iColumnWidth;
		TInt usedViewRectPortionHeight = (iViewRect.Height() / iItemHeight) * iItemHeight;
		TRect usedPortionOfViewRect(iViewRect.iTl, TSize(usedViewRectPortionWidth, usedViewRectPortionHeight));
		iWin->Scroll(usedPortionOfViewRect, TPoint(-aHScrollAmount * iColumnWidth, 0));
		// iWin->Scroll(iViewRect, TPoint(-aHScrollAmount * iColumnWidth, 0));
		iTopItemIndex = iTopItemIndex + (numOfItemsPerColumn * aHScrollAmount);
		CalcBottomItemIndex();
		TInt colIndexOfOldTopItem = oldTopItemIndex / numOfItemsPerColumn;
		TRect redrawRect;
		TInt startColIndex;
		TInt endColIndex;
		if (aHScrollAmount > 0)
			{
			redrawRect.SetRect(TPoint((numOfColsThatFitInViewRect - aHScrollAmount) * iColumnWidth + iViewRect.iTl.iX, iViewRect.iTl.iY), iViewRect.iBr);
			startColIndex = colIndexOfOldTopItem + numOfColsThatFitInViewRect;
			endColIndex = startColIndex + aHScrollAmount - 1;
			}
		else
			{
			redrawRect.SetRect(iViewRect.iTl, TPoint(Abs(aHScrollAmount) * iColumnWidth + iViewRect.iTl.iX, iViewRect.iBr.iY));
			startColIndex = colIndexOfOldTopItem + aHScrollAmount;
			endColIndex = colIndexOfOldTopItem - 1;
			}
		redrawRect.Intersection(iViewRect);
		iWin->Invalidate(iViewRect);
		iWin->BeginRedraw(iViewRect);
		DrawColumnRange(startColIndex, endColIndex);
		iWin->EndRedraw();
		}
	_AKNTRACE_FUNC_EXIT;
	}

EXPORT_C void CSnakingListBoxView::CalcDataWidth() 
	{
	// assumes that iModel and iItemDrawer are both valid
	// assumes that the model knows how many items there are...
	// calculate data width (in columns)
	iDataWidth = 0;
	if ((iViewRect.Height() == 0) || (iItemHeight == 0))
		return;
	TInt numOfItemsPerColumn = NumberOfItemsPerColumn();
	iDataWidth = iModel->NumberOfItems() / numOfItemsPerColumn;
	if (iModel->NumberOfItems() % numOfItemsPerColumn)
		iDataWidth++;	// add on one column if remainder != 0
	}

EXPORT_C TInt CSnakingListBoxView::VisibleWidth(const TRect& aRect) const
	{
	return aRect.Width() / iColumnWidth;
	}

EXPORT_C void CSnakingListBoxView::Draw(const TRect* aClipRect) const
	{
	// temporary: some code sharing with CListBoxView::Draw() is needed!
	_AKNTRACE_FUNC_ENTER;
	if (RedrawDisabled())
	    {
	    _AKNTRACE_FUNC_EXIT;
		return;
	    }
	__ASSERT_DEBUG(iModel, Panic(EEikPanicListBoxNoModel));
	if (iItemHeight == 0)
	    {
	    _AKNTRACE_FUNC_EXIT;
		return;
	    }
	if (! aClipRect)
		aClipRect = &iViewRect;
	iItemDrawer->ClearRect(iViewRect);
	if (iModel->NumberOfItems() == 0)
	    {
	    // call to this was moved to CEikListBox::Draw(), because we need the whole clientrect
	    // to do the drawing correctly.
	    //DrawEmptyList();
		}
	else
		{
		TInt firstPotentialItemIndex = iTopItemIndex;
		TInt lastPotentialItemIndex = iTopItemIndex + NumberOfItemsThatFitInRect(iViewRect) - 1;
		TInt i;
		ITEM_EXISTS_BEGIN;
		for (i = firstPotentialItemIndex; i <= lastPotentialItemIndex; i++)
			if (ITEM_EXISTS(i))
				DrawItem(i);
			else
				{
				ClearUnusedItemSpace(i, lastPotentialItemIndex);
				break;
				}
		// clear the unused portion of the viewing area
		TInt usedViewRectPortionWidth = VisibleWidth(iViewRect) * iColumnWidth;
		TInt usedViewRectPortionHeight = (iViewRect.Height() / iItemHeight) * iItemHeight;
		TRect usedPortionOfViewRect(iViewRect.iTl, TSize(usedViewRectPortionWidth, usedViewRectPortionHeight));
        iItemDrawer->Gc()->SetBrushColor( BackColor() );
        DrawUtils::ClearBetweenRects( *iItemDrawer->Gc(), iViewRect, usedPortionOfViewRect );
		// ((CSnakingListBoxView*)this)->iBottomItemIndex = i - 1;
		}
	_AKNTRACE_FUNC_EXIT;
	} 

EXPORT_C void CSnakingListBoxView::DrawItemRange(TInt aStartItemIndex, TInt aEndItemIndex) const
	{
	// temporary: some code sharing with CSnakingListBoxView::Draw() is needed!
	_AKNTRACE_FUNC_ENTER;
	if (RedrawDisabled())
	    {
	    _AKNTRACE_FUNC_EXIT;
		return;
	    }
	if (iItemHeight == 0)
	    {
	    _AKNTRACE_FUNC_EXIT;
		return;
	    }
	TInt i;
	ITEM_EXISTS_BEGIN;
	for (i = aStartItemIndex; i <= aEndItemIndex; i++)
		if (ITEM_EXISTS(i))
			DrawItem(i);
		else
			{
			ClearUnusedItemSpace(i, aEndItemIndex);
			break;
			}
	TInt usedViewRectPortionWidth = VisibleWidth(iViewRect) * iColumnWidth;
	TInt usedViewRectPortionHeight = (iViewRect.Height() / iItemHeight) * iItemHeight;
	TRect usedPortionOfViewRect(iViewRect.iTl, TSize(usedViewRectPortionWidth, usedViewRectPortionHeight));
    iItemDrawer->Gc()->SetBrushColor( BackColor() );
    DrawUtils::ClearBetweenRects( *iItemDrawer->Gc(), iViewRect, usedPortionOfViewRect);
    _AKNTRACE_FUNC_EXIT;
	}

EXPORT_C void CSnakingListBoxView::DrawColumnRange(TInt aStartColIndex, TInt aEndColIndex) const
	{
	_AKNTRACE_FUNC_ENTER;
	if (RedrawDisabled())
	    {
	    _AKNTRACE_FUNC_EXIT;
		return;
	    }
	if (iItemHeight == 0)
	    {
	    _AKNTRACE_FUNC_EXIT;
		return;
	    }
	TInt numOfItemsPerColumn = NumberOfItemsPerColumn();
	TInt startItemIndex = aStartColIndex * numOfItemsPerColumn;
	TInt endItemIndex = aEndColIndex * numOfItemsPerColumn + numOfItemsPerColumn - 1;
	DrawItemRange(startItemIndex, endItemIndex);
	}

EXPORT_C void CSnakingListBoxView::SetTopItemIndex(TInt aNewTopItemIndex)
	{
	if (iViewRect.Height() == 0)
		return;
	CListBoxView::SetTopItemIndex(aNewTopItemIndex);
	UpdateHScrollOffsetBasedOnTopItemIndex();
	}

EXPORT_C void CSnakingListBoxView::SetItemHeight(TInt aItemHeight)
	{
	CListBoxView::SetItemHeight(aItemHeight);
	CalcBottomItemIndex();
	UpdateHScrollOffsetBasedOnTopItemIndex();
	}

EXPORT_C void CSnakingListBoxView::UpdateHScrollOffsetBasedOnTopItemIndex()
	{
	TInt numOfItemsPerColumn = NumberOfItemsPerColumn();
	iHScrollOffset = iTopItemIndex / numOfItemsPerColumn;
	}

EXPORT_C TBool CSnakingListBoxView::ScrollToMakeItemVisible(TInt aItemIndex)
	{
	_AKNTRACE_FUNC_ENTER;
	if ((RedrawDisabled()) || (ItemIsVisible(aItemIndex)) || (iViewRect.Height() == 0))
	    {
	    _AKNTRACE_FUNC_EXIT;
		return EFalse;
	    }
	HideMatcherCursor();
	TInt amountToScroll = CalculateHScrollOffsetSoItemIsVisible(aItemIndex);
	HScroll(amountToScroll);
	DrawMatcherCursor();
	_AKNTRACE_FUNC_EXIT;
	return ETrue;
	}

EXPORT_C TInt CSnakingListBoxView::CalculateHScrollOffsetSoItemIsVisible(TInt aItemIndex) 
	{
	// returns the number of cols that we need to scroll, 0 if no scrolling is needed
	_AKNTRACE_FUNC_ENTER;
	TInt newTopItemIndex = CalcNewTopItemIndexSoItemIsVisible(aItemIndex);
	TInt numOfItemsPerColumn = NumberOfItemsPerColumn();
	TInt oldHScrollOffset = iHScrollOffset;
	TInt newHScrollOffset = newTopItemIndex / numOfItemsPerColumn;
	TInt numOfColsToScroll = newHScrollOffset - oldHScrollOffset;
	_AKNTRACE_FUNC_EXIT;
	return numOfColsToScroll;
	}

EXPORT_C TAny* CSnakingListBoxView::Reserved_1()
	{
	return NULL;
	}



