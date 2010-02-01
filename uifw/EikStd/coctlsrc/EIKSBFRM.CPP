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


#include <eiksbfrm.h>
#include <eikpanic.h>
#include <eikbtgpc.h>
#include <eikcba.h>
#include <eikenv.h>
#include <eikappui.h>

#include <aknenv.h>
#include <aknappui.h>
#include <AknLayout.lag>
#include <AknUtils.h>

#include "EIKSBEXT.H"

// const TInt KCbaScrollBarWidth=9;

//
// TEikScrollBarFrameLayout
//

EXPORT_C TEikScrollBarFrameLayout::TEikScrollBarFrameLayout()
	//
	// default constructor
	//
	{
    iInclusiveMargin.iTop = 0;
    iInclusiveMargin.iBottom = 0;
    iInclusiveMargin.iLeft = 0;
    iInclusiveMargin.iRight = 0;
    
    iClientMargin.iTop = 0;
    iClientMargin.iBottom = 0;
    iClientMargin.iLeft = 0;
    iClientMargin.iRight = 0;
    
    iClientAreaGranularity = TSize(0,0);
    
    iTilingMode = EClientRectConstant;
	}

EXPORT_C void TEikScrollBarFrameLayout::SetInclusiveMargin(TInt aMargin)
	//
	// sets all inclusive margins to aMargin
	//
	{
    iInclusiveMargin.iTop = aMargin;
    iInclusiveMargin.iBottom = aMargin;
    iInclusiveMargin.iLeft = aMargin;
    iInclusiveMargin.iRight = aMargin;
	}

EXPORT_C void TEikScrollBarFrameLayout::SetClientMargin(TInt aMargin)
	//
	// sets all client margins to aMargin
	//
	{
    iClientMargin.iTop = aMargin;
    iClientMargin.iBottom = aMargin;
    iClientMargin.iLeft = aMargin;
    iClientMargin.iRight = aMargin;
	}


CEikScrollBarFrameExtension::CEikScrollBarFrameExtension()
    {

    }

CEikScrollBarFrameExtension::~CEikScrollBarFrameExtension()
    {

    }

//
// CEikScrollBarFrame
//

enum TEikScrollBarFramePanic
	{
	ENoScrollBarFrame	=0x01,
	EFailedToRemoveExternalScrollBar,
	EUnexpectedExternalScrollBarDisconnectRequest
	};

GLDEF_C void SbfPanic(TEikScrollBarFramePanic aPanic)
    {
	_LIT(KPanicCategory, "UIKON - Scrollbar Frame");
    User::Panic(KPanicCategory, aPanic);
    }

// const TInt KTypeOfScrollBarMask=0x0300;
// const TInt KSideOfScrollBarMask=0x0c00;


enum // private flags
	{
	EDisplayHScrollBar			=0x01,
	EDisplayVScrollBar			=0x02,
	EDoNotAdjustHorizontalModel	=0x04,
	EDoNotAdjustVerticalModel	=0x08,
	EPreAllocScrollBars			=0x10
	};

EXPORT_C CEikScrollBarFrame::~CEikScrollBarFrame()
	{
    DeleteScrollBars();
    delete iExtension;
	}

EXPORT_C CEikScrollBarFrame::CEikScrollBarFrame(CCoeControl* aParentWindow, MEikScrollBarObserver* aObserver, TBool /*aPreAlloc*/)
	{
    InitExtension(aParentWindow,aObserver);
	GetScrollBars(EFalse);	
	}

CEikScrollBarFrame::CEikScrollBarFrame(CCoeControl* aParentWindow, MEikScrollBarObserver* aObserver, TBool /*aPreAlloc*/, TBool aDoubleSpan)
	{
    InitExtension(aParentWindow,aObserver);
	GetScrollBars(aDoubleSpan);
	}

void CEikScrollBarFrame::InitExtension(CCoeControl* aParentWindow, MEikScrollBarObserver* aObserver)
    {
    iExtension = new CEikScrollBarFrameExtension();
    if (iExtension)
        {
        iExtension->iParentWindow = aParentWindow;
        iExtension->iH.iModel = TAknDoubleSpanScrollBarModel();
        iExtension->iH.iBar = NULL;
        iExtension->iH.iExternalScrollBarAttached = EFalse;
        iExtension->iH.iVisibility = EOff; 
        if(AknLayoutUtils::PenEnabled())
            {
            iExtension->iScrollBarObserver = aObserver;
            }
        }
    }

void CEikScrollBarFrame::DisconnectExternalScrollBar(CEikScrollBar* aScrollBar)
	{
	if (iV.iExternalScrollBarAttached && iV.iBar == aScrollBar)
        {
        iV.iExternalScrollBarAttached = EFalse;
	    iV.iBar = NULL;
        }

    if (iExtension && iExtension->iH.iExternalScrollBarAttached && iExtension->iH.iBar == aScrollBar) 
        {
    	iExtension->iH.iExternalScrollBarAttached = EFalse;
	    iExtension->iH.iBar = NULL;
        }
    }

void CEikScrollBarFrame::GetScrollBars(TBool aDoubleSpan)
	{
	if (!iV.iBar)
		{
		CEikCba* cba=GetCurrentCba();
		if (cba)
			{
			// If aDoubleSpan is true, we will optimize and do not create arrow heads at all.
			// There will come CreateDoubleSpanScrollBarsL call, and arrow heads are not needed.
			if ( !(aDoubleSpan && (AknLayoutUtils::DefaultScrollBarType(iAvkonAppUi) == CEikScrollBarFrame::EDoubleSpan)) )
			    {
			    TRAP_IGNORE(cba->CreateArrowHeadScrollBarL());  
			    }
			// returns the vertical scroll bar from the top scroll bar host
			iV.iBar=cba->VScrollBarAsControl();
			iV.iExternalScrollBarAttached=ETrue;
			TRAPD(err, iV.iBar->AddExternalFrameL(this));
			if (err)
				{
				iV.iExternalScrollBarAttached = EFalse;
				iV.iBar = NULL;
				}
			}
		}
	}

EXPORT_C void CEikScrollBarFrame::DrawScrollBarsNow() const
// Force a redraw of any scrollbars
	{	
	if (iV.iBar && iExtension && iExtension->iParentWindow->IsVisible())
		iV.iBar->DrawNow();

	if (iExtension && iExtension->iH.iBar && iExtension->iParentWindow->IsVisible())
		iExtension->iH.iBar->DrawNow();

	}

void CEikScrollBarFrame::DrawScrollBarsDeferred() const
    {
    if (iV.iBar && iExtension && iExtension->iParentWindow->IsVisible())
	    {	   
	    iV.iBar->DrawDeferred();	    
	    }		

	if (iExtension && iExtension->iH.iBar && iExtension->iParentWindow->IsVisible())
	    {
	    iExtension->iH.iBar->DrawDeferred();	    
	    }    
    }

const TInt KLongEnoughToCauseComponentsToBeCreated=200;


EXPORT_C void CEikScrollBarFrame::SetScrollBarVisibilityL(TScrollBarVisibility aHVisibility, TScrollBarVisibility aVVisibility)
// Set the visibility state for both scrollbars to be used when tiling
	{
	__ASSERT_DEBUG(this, SbfPanic(ENoScrollBarFrame));

    // Vertical scrollbar
	iV.iVisibility=aVVisibility;
    if (iV.iBar && TypeOfVScrollBar() == EDoubleSpan && aVVisibility==EOff)
        {
       	iScrollBarFrameFlags&=(~EDisplayVScrollBar);
        MakeSBarVisible(iV, EFalse);
        }

    // Horizontal scrollbar
    if (iExtension)
        {
    	iExtension->iH.iVisibility=aHVisibility;
        if (iExtension->iH.iBar && TypeOfHScrollBar() == EDoubleSpan && aHVisibility==EOff)
            {
       	    iScrollBarFrameFlags&=(~EDisplayHScrollBar);
            MakeSBarVisible(iExtension->iH, EFalse);
            }
        }
	}

EXPORT_C TBool CEikScrollBarFrame::Tile(TEikScrollBarModel* aVModel)
	//
	// The main function which provides the necessary scrollbars according to visibilities and size considerations
	// returns ETrue if the "output rect" was changed
	//
	{
	GetScrollBars(EFalse);
	CalcTheoreticalScrollBarVisibility(aVModel);
	if (iV.iVisibility!=EOff)
		iV.iModel = *aVModel;
	MakeSBarVisible(iV, iScrollBarFrameFlags&EDisplayVScrollBar);
	return EFalse;
	}

EXPORT_C TBool CEikScrollBarFrame::TileL(TEikScrollBarModel* aHModel, TEikScrollBarModel* aVModel,
			  TRect& aClientRect, TRect& aInclusiveRect, const TEikScrollBarFrameLayout& aLayout)
	{
	TRect tempRect(aClientRect);
	if(aClientRect.Height() < 0 )
	    {
	    aClientRect.iTl.iY = aClientRect.iBr.iY;
	    aClientRect.iBr.iY = tempRect.iTl.iY;
	    }
	if(aClientRect.Width() < 0 )
        {
        aClientRect.iTl.iX = aClientRect.iBr.iX;
        aClientRect.iBr.iX = tempRect.iTl.iX;
        }
	tempRect = aInclusiveRect;
	if(aInclusiveRect.Height() < 0 )
        {
        aInclusiveRect.iTl.iY = aInclusiveRect.iBr.iY;
        aInclusiveRect.iBr.iY = tempRect.iTl.iY;
        }
    if(aInclusiveRect.Width() < 0 )
        {
        aInclusiveRect.iTl.iX = aInclusiveRect.iBr.iX;
        aInclusiveRect.iBr.iX = tempRect.iTl.iX;
        }
    if (iExtension && iExtension->iH.iVisibility!=EOff)
        {
        if(aClientRect.Height() < ScrollBarBreadth( CEikScrollBar::EHorizontal) )
            {
            aClientRect.SetHeight( ScrollBarBreadth(CEikScrollBar::EHorizontal) );
            }
        if(aInclusiveRect.Height() < ScrollBarBreadth( CEikScrollBar::EHorizontal) )
            {
            aInclusiveRect.SetHeight( ScrollBarBreadth(CEikScrollBar::EHorizontal) );
            }
        }
    TBool sizeChanged = EFalse;
    
	GetScrollBars(EFalse);
	CalcTheoreticalScrollBarVisibility(aVModel,aHModel);

	if (iV.iVisibility!=EOff)
		iV.iModel = *aVModel;
	
	MakeSBarVisible(iV, iScrollBarFrameFlags&EDisplayVScrollBar);

    if (iExtension && iExtension->iH.iBar)
        {
        if (iExtension->iH.iVisibility!=EOff)
	        iExtension->iH.iModel = *aHModel;   
        
        MakeSBarVisible(iExtension->iH, iScrollBarFrameFlags&EDisplayHScrollBar);
        }

    // Vertical Double span scollbar
    if (iV.iBar && TypeOfVScrollBar() == EDoubleSpan && iV.iExternalScrollBarAttached==EFalse )
        {        
        TInt scrollBarWidth = ScrollBarBreadth(CEikScrollBar::EVertical); // is 0 if SB not visible !
        TInt horizontalScrollBarWidth = 0;
        if (iExtension && iExtension->iH.iVisibility!=EOff)
            {
            horizontalScrollBarWidth = ScrollBarBreadth(CEikScrollBar::EHorizontal);
            }
        CAknDoubleSpanScrollBar* scrollbar = static_cast <CAknDoubleSpanScrollBar*> (iV.iBar);
        if (scrollbar->FixedLayoutRect().Size() == TSize(0,0))
            {
            TMargins checkedClientMargin(aLayout.iClientMargin);
            TMargins checkedInclusiveMargin(aLayout.iInclusiveMargin);
            checkedClientMargin.iTop = Max(0,checkedClientMargin.iTop);
            checkedClientMargin.iBottom = Max(0,checkedClientMargin.iBottom);
            checkedClientMargin.iRight = Max(0,checkedClientMargin.iRight);
            checkedClientMargin.iLeft = Max(0,checkedClientMargin.iLeft);

            checkedInclusiveMargin.iTop = Max(0,checkedInclusiveMargin.iTop);
            checkedInclusiveMargin.iBottom = Max(0,checkedInclusiveMargin.iBottom);
            checkedInclusiveMargin.iRight = Max(0,checkedInclusiveMargin.iRight);
            checkedInclusiveMargin.iLeft = Max(0,checkedInclusiveMargin.iLeft);

            TInt width  = 0;                
            TInt xPos   = 0;
            TInt yPos   = 0;
            TInt height = 0;
            
            if (!AknLayoutUtils::LayoutMirrored())
                {
                if (aLayout.iTilingMode == TEikScrollBarFrameLayout::EInclusiveRectConstant)
                    {
                    width = scrollBarWidth + checkedInclusiveMargin.iRight;                
                    xPos = aInclusiveRect.iBr.iX - width;
                    yPos = aInclusiveRect.iTl.iY + checkedInclusiveMargin.iTop;
                    height = aInclusiveRect.Size().iHeight - (checkedInclusiveMargin.iTop + checkedInclusiveMargin.iBottom) - horizontalScrollBarWidth;
                
                    if ((aClientRect.iBr.iX + width > aInclusiveRect.iBr.iX) || (aInclusiveRect.iBr.iX - width > aClientRect.iBr.iX))
                        {
                        aClientRect.iBr.iX = aInclusiveRect.iBr.iX - width;
                        sizeChanged = ETrue;
                        }
                    }
                else
                    {
                    width = scrollBarWidth + checkedClientMargin.iRight;                
                    xPos = aClientRect.iBr.iX + checkedClientMargin.iRight;
                    yPos = aInclusiveRect.iTl.iY + checkedInclusiveMargin.iTop;
                    height = aInclusiveRect.Size().iHeight - (checkedInclusiveMargin.iTop + checkedInclusiveMargin.iBottom) - horizontalScrollBarWidth;

                    if ((aClientRect.iBr.iX + width + checkedInclusiveMargin.iRight > aInclusiveRect.iBr.iX) || 
                        (aInclusiveRect.iBr.iX - (width + checkedInclusiveMargin.iRight) > aClientRect.iBr.iX))
                        {
                        aInclusiveRect.iBr.iX = aClientRect.iBr.iX + width + checkedInclusiveMargin.iRight;
                        sizeChanged = ETrue;
                        }
                    }
                }
            else
                {
                // Mirrored Left & Right
                if (aLayout.iTilingMode == TEikScrollBarFrameLayout::EInclusiveRectConstant)
                    {
                    width = scrollBarWidth + checkedInclusiveMargin.iRight;                
                    xPos = aInclusiveRect.iTl.iX + checkedInclusiveMargin.iRight;
                    yPos = aInclusiveRect.iTl.iY + checkedInclusiveMargin.iTop;
                    height = aInclusiveRect.Size().iHeight - (checkedInclusiveMargin.iTop + checkedInclusiveMargin.iBottom) - horizontalScrollBarWidth;
                
                    if ((aClientRect.iTl.iX - width < aInclusiveRect.iTl.iX) || (aInclusiveRect.iTl.iX + width > aClientRect.iTl.iX))
                        {
                        aClientRect.iTl.iX = aInclusiveRect.iTl.iX + width;
                        xPos = aInclusiveRect.iTl.iX + checkedInclusiveMargin.iRight;
                        sizeChanged = ETrue;
                        }
                    }
                else
                    {
                    width = scrollBarWidth + checkedClientMargin.iRight;                
                    xPos = aClientRect.iTl.iX - checkedClientMargin.iRight;
                    yPos = aInclusiveRect.iTl.iY + checkedInclusiveMargin.iTop;
                    height = aInclusiveRect.Size().iHeight - (checkedInclusiveMargin.iTop + checkedInclusiveMargin.iBottom) - horizontalScrollBarWidth;

                    if ((aClientRect.iTl.iX - width - checkedInclusiveMargin.iRight > aInclusiveRect.iTl.iX) || 
                        (aInclusiveRect.iTl.iX - (width + checkedInclusiveMargin.iRight) < aClientRect.iTl.iX))
                        {
                        aInclusiveRect.iTl.iX = aClientRect.iTl.iX - width - checkedInclusiveMargin.iRight;
                        xPos = aInclusiveRect.iTl.iX + checkedInclusiveMargin.iRight;
                        sizeChanged = ETrue;
                        }
                    }

                }
    
            TRect newRect = TRect(TPoint(xPos, yPos), TSize(width, height ));
            if (iV.iBar->IsVisible() && (newRect != TRect(iV.iBar->Position(), iV.iBar->Size())))
                {
                iV.iBar->SetRect(newRect);                     
                }

            }
        }

    // Horizontal Double span scollbar
    if (iExtension && 
        iExtension->iH.iBar && 
        TypeOfHScrollBar() == EDoubleSpan && 
        iExtension->iH.iExternalScrollBarAttached==EFalse )
        {                
        TInt scrollBarWidth = ScrollBarBreadth(CEikScrollBar::EHorizontal); // is 0 if SB not visible !
        TInt verticalScrollBarWidth = 0;
        if (iV.iVisibility!=EOff)
            {
            verticalScrollBarWidth = ScrollBarBreadth(CEikScrollBar::EVertical);
            }
        CAknDoubleSpanScrollBar* scrollbar = static_cast <CAknDoubleSpanScrollBar*> (iExtension->iH.iBar);
        if (scrollbar->FixedLayoutRect().Size() == TSize(0,0))
            {
            TMargins checkedClientMargin(aLayout.iClientMargin);
            TMargins checkedInclusiveMargin(aLayout.iInclusiveMargin);
            checkedClientMargin.iTop = Max(0,checkedClientMargin.iTop);
            checkedClientMargin.iBottom = Max(0,checkedClientMargin.iBottom);
            checkedClientMargin.iRight = Max(0,checkedClientMargin.iRight);
            checkedClientMargin.iLeft = Max(0,checkedClientMargin.iLeft);

            checkedInclusiveMargin.iTop = Max(0,checkedInclusiveMargin.iTop);
            checkedInclusiveMargin.iBottom = Max(0,checkedInclusiveMargin.iBottom);
            checkedInclusiveMargin.iRight = Max(0,checkedInclusiveMargin.iRight);
            checkedInclusiveMargin.iLeft = Max(0,checkedInclusiveMargin.iLeft);

            TInt width  = 0;                
            TInt xPos   = 0;
            TInt yPos   = 0;
            TInt height = 0;
            
            if (aLayout.iTilingMode == TEikScrollBarFrameLayout::EInclusiveRectConstant)
                {
                width = scrollBarWidth + checkedInclusiveMargin.iBottom; // width as vertical direction (height).               
                xPos = aInclusiveRect.iTl.iX + checkedInclusiveMargin.iLeft;
                if (AknLayoutUtils::LayoutMirrored())
                    {
                    xPos += verticalScrollBarWidth;
                    }
                yPos = aInclusiveRect.iBr.iY - checkedInclusiveMargin.iBottom - width;
                height = aInclusiveRect.Size().iWidth - (checkedInclusiveMargin.iLeft + checkedInclusiveMargin.iRight) - verticalScrollBarWidth; // height as horizontal (width).
                
                if ((aClientRect.iBr.iY + width > aInclusiveRect.iBr.iY) || (aInclusiveRect.iBr.iY - width > aClientRect.iBr.iY))
                    {
                    aClientRect.iBr.iY = aInclusiveRect.iBr.iY - width;
                    sizeChanged = ETrue;
                    }
                }
            else
                {
                width = scrollBarWidth + checkedClientMargin.iBottom; // width as vertical direction (height).               
                xPos = aInclusiveRect.iTl.iX + checkedInclusiveMargin.iLeft;
                if (AknLayoutUtils::LayoutMirrored())
                    {
                    xPos += verticalScrollBarWidth;
                    }
                yPos = aClientRect.iBr.iY + checkedClientMargin.iBottom;
                height = aInclusiveRect.Size().iWidth - (checkedInclusiveMargin.iLeft + checkedInclusiveMargin.iRight) - verticalScrollBarWidth; // height as horizontal (width).
                
                if ((aClientRect.iBr.iY + width + checkedClientMargin.iBottom > aInclusiveRect.iBr.iY) || 
                    (aInclusiveRect.iBr.iY - (width + checkedInclusiveMargin.iBottom) > aClientRect.iBr.iY))
                    {
                    aInclusiveRect.iBr.iY = aClientRect.iBr.iY + width + checkedInclusiveMargin.iBottom;
                    sizeChanged = ETrue;
                    }
                }

            TRect newRect = TRect(TPoint(xPos, yPos), TSize(height, width ));  // height & width swapped 
            if (iExtension->iH.iBar->IsVisible() && (newRect != TRect(iV.iBar->Position(), iV.iBar->Size())))
                {
                iExtension->iH.iBar->SetRect(newRect);                   
                }
            }
        
        }

    return sizeChanged;
	}

EXPORT_C void CEikScrollBarFrame::MoveThumbsBy(TInt aDeltaX, TInt aDeltaY)
	//
 	// Used to update any scrollbar(s) after an external scroll
	// values in terms of the model, presumed not to have changed spans.
	//
	{
    // Vertical scrollbar
    if (aDeltaY && iV.iBar)
        {
        if (TypeOfVScrollBar() == TScrollBarType(EArrowHead))
            {
		    iV.iModel.iThumbPosition += aDeltaY;
            }
        else
            {
            // EDoubleSpan has different model.
            if (iV.iModel.ScrollBarModelType() == TEikScrollBarModel::EAknDoubleSpanScrollBarModel)
                {
                TAknDoubleSpanScrollBarModel* model = static_cast <TAknDoubleSpanScrollBarModel*> (&iV.iModel);
                // Note that for a large scroll span and small delta this may not actually change focusposition
                // because of the 15 bit accuracy of TAknDoubleSpanScrollBarModel values.
                model->SetFocusPosition(model->FocusPosition() + aDeltaY);    
                }
            else
                {
                // Error. User of the API is perhaps assigning values directly to TEikScrollBarModel
                // member variables which is not allowed with EAknDoubleSpanScrollBarModel.
                // #ifdef _DEBUG
                // RDebug::Print(_L("CEikScrollBarFrame: Please, use TAknDoubleSpanScrollBarModel instead of TEikScrollBarModel"));
                // #endif
                // In most cases we can work with the TEikScrollBarModel model.
    		    iV.iModel.iThumbPosition += aDeltaY;
                }
            }
	    ApplyModel(iV);
        }


    // Horizontal scrollbar
    if (aDeltaX && iExtension && iExtension->iH.iBar && TypeOfHScrollBar() == TScrollBarType(EDoubleSpan))
        {
        if (iExtension->iH.iModel.ScrollBarModelType() == TEikScrollBarModel::EAknDoubleSpanScrollBarModel)
            {
            TAknDoubleSpanScrollBarModel* model = static_cast <TAknDoubleSpanScrollBarModel*> (&(iExtension->iH.iModel));
            // Note that for a large scroll span and small delta this may not actually change focusposition
            // because of the 15 bit accuracy of TAknDoubleSpanScrollBarModel values.
            model->SetFocusPosition(model->FocusPosition() + aDeltaX);    
            }
        else
            {
            // Error. User of the API is perhaps assigning values directly to TEikScrollBarModel
            // member variables which is not allowed with EAknDoubleSpanScrollBarModel.
            // #ifdef _DEBUG
            // RDebug::Print(_L("CEikScrollBarFrame: Please, use TAknDoubleSpanScrollBarModel instead of TEikScrollBarModel"));
            // #endif
            // In most cases we can work with the TEikScrollBarModel model.
            iExtension->iH.iModel.iThumbPosition += aDeltaX;
            }
        ApplyModel(iExtension->iH);
        }

	}

EXPORT_C void CEikScrollBarFrame::MoveVertThumbTo(TInt aVertThumbPos)
	{
	if (iV.iBar)
		{
        if (TypeOfVScrollBar() == TScrollBarType(EArrowHead))
            {
    		iV.iModel.iThumbPosition = aVertThumbPos;
            }
        else
            {
            // EDoubleSpan has different model.
            if (iV.iModel.ScrollBarModelType() == TEikScrollBarModel::EAknDoubleSpanScrollBarModel)
                {
                TAknDoubleSpanScrollBarModel* model = static_cast <TAknDoubleSpanScrollBarModel*> (&iV.iModel);
                model->SetFocusPosition(aVertThumbPos);    
                }
            else
                {
                // Error. User of the API is perhaps assigning values directly to TEikScrollBarModel
                // member variables which is not allowed with EAknDoubleSpanScrollBarModel.
                // #ifdef _DEBUG
                // RDebug::Print(_L("CEikScrollBarFrame: Please, use TAknDoubleSpanScrollBarModel instead of TEikScrollBarModel"));
                // #endif
                // In most cases we can work with the TEikScrollBarModel model.
        		iV.iModel.iThumbPosition = aVertThumbPos;
                }
            }
		ApplyModel(iV);
		}
	}

EXPORT_C void CEikScrollBarFrame::SetVFocusPosToThumbPos(TInt aFocusPosition)
	{
	MoveVertThumbTo(aFocusPosition);
	}

EXPORT_C TInt CEikScrollBarFrame::ScrollBarBreadth(CEikScrollBar::TOrientation aOrientation) const
	//
	// return the appropriate scrollbar's breadth or zero if none exists
	//
	{
	CAknScrollBar* sBar=(CAknScrollBar*)GetScrollBarHandle(aOrientation);
	if (!sBar) 
		return 0;
	return sBar->ScrollBarBreadth(); 
	}

EXPORT_C TBool CEikScrollBarFrame::ScrollBarExists(CEikScrollBar::TOrientation aOrientation) const
	//
	// returns ETrue if the specified scrollbar exists
	//
	{
	if (GetScrollBarHandle(aOrientation))
		return ETrue;
	return EFalse;
	}

EXPORT_C TInt CEikScrollBarFrame::CountComponentControls() const
    {
    TInt numberOfComponents = 0;
	
    if (iV.iBar)
		numberOfComponents++;
	
    if (iExtension && iExtension->iH.iBar)
		numberOfComponents++;

    return numberOfComponents;
    }

EXPORT_C CCoeControl* CEikScrollBarFrame::ComponentControl(TInt aIndex) const
    {
    if (aIndex == 0)
        {
        if (iV.iBar)
            return iV.iBar;
        else
            {
            if (iExtension && iExtension->iH.iBar)
                return iExtension->iH.iBar;
            }
        }

    if (aIndex == 1)
        {
        if (iExtension && iExtension->iH.iBar)
            return iExtension->iH.iBar;
        else
            {
            if (iV.iBar)
                return iV.iBar;
            }
        }

	return NULL;
    }

EXPORT_C CEikScrollBar* CEikScrollBarFrame::GetScrollBarHandle(CEikScrollBar::TOrientation aOrientation) const
	//
	// returns the pointer to the appropriate scrollbar
	//
	{
	if (aOrientation==CEikScrollBar::EVertical)
		{
		if (iScrollBarFrameFlags&EDisplayVScrollBar)
			return(iV.iBar);
		}

	if (aOrientation==CEikScrollBar::EHorizontal)
		{
		if (iScrollBarFrameFlags&EDisplayHScrollBar && iExtension)
			return(iExtension->iH.iBar);
		}

	return(NULL);
	}

EXPORT_C CEikScrollBar* CEikScrollBarFrame::VerticalScrollBar() const
	//
	// returns the vertical scroll bar
	//
	{
	return iV.iBar;
	}

void CEikScrollBarFrame::CalcTheoreticalScrollBarVisibility(const TEikScrollBarModel* aVModel)
	//
	// Determines which scrollbars are necessary before size considerations are taken into account
	//
	{
	// assume no scrollbars to start with
	iScrollBarFrameFlags&=(~EDisplayVScrollBar);
    
    TBool scrollBarUseful = EFalse;

    switch(TypeOfVScrollBar())
        {
        case EDoubleSpan:
            {
            if (aVModel->ScrollBarModelType() == TEikScrollBarModel::EAknDoubleSpanScrollBarModel)
                {
                //const TAknDoubleSpanScrollBarModel* model = static_cast <const TAknDoubleSpanScrollBarModel*> (aVModel);
                //scrollBarUseful = (model->FocusPosition() < model->ScrollSpan()) && (model->WindowSize() < model->ScrollSpan());    
                scrollBarUseful = ETrue; // S60 style says double span scrollbar is always shown if visibility is EAuto
                }
            else
                {
                // Error. User of the API is perhaps assigning values directly to TEikScrollBarModel
                // member variables which is not allowed with EAknDoubleSpanScrollBarModel.
                //#ifdef _DEBUG
                //RDebug::Print(_L("CEikScrollBarFrame: Please, use TAknDoubleSpanScrollBarModel instead of TEikScrollBarModel"));
                //#endif
                // In most cases we can work with the TEikScrollBarModel model.
                //scrollBarUseful = (aVModel->iThumbPosition < aVModel->iScrollSpan) && (aVModel->iThumbSpan < aVModel->iScrollSpan);    
                scrollBarUseful = ETrue; // S60 style says double span scrollbar is always shown if visibility is EAuto
                }
            break;
            }

        case EArrowHead: // fallthrough
        default:
            {
            scrollBarUseful = aVModel->ScrollBarUseful();
            break;
            }
        }

    if ( (iV.iVisibility==EOn) || ( (iV.iVisibility==EAuto)&&(scrollBarUseful) ) )
        {
        iScrollBarFrameFlags|=EDisplayVScrollBar;
        }

	}

CEikCba* CEikScrollBarFrame::GetCurrentCba()
	{
	CEikCba* mopCba = NULL;
    if (iExtension && iExtension->iParentWindow)
        mopCba=iExtension->iParentWindow->MopGetObject(mopCba);
	return mopCba;
	}

void CEikScrollBarFrame::ApplyModel(SBarData& aSBar)
	{
	if (iExtension && iExtension->iParentWindow && iExtension->iParentWindow->IsVisible() 
	        && aSBar.iBar && aSBar.iBar->IsVisible())
		{
		aSBar.iBar->SetModel(&aSBar.iModel);
		}		
	}

void CEikScrollBarFrame::MakeSBarVisible(SBarData& aSBar, TBool aVisible)
	{
	if (iExtension && iExtension->iParentWindow->IsVisible() && aSBar.iBar)
		{
		if (aVisible && iExtension->iParentWindow->IsVisible())
		    {
		    aSBar.iBar->SetModel(&aSBar.iModel);
		    aSBar.iBar->MakeVisible(ETrue);
		    }
		else if(!aVisible)
		    {
		    aSBar.iBar->MakeVisible(EFalse);
		    }
		}
    else if (TypeOfVScrollBar() == TScrollBarType(EDoubleSpan) && aSBar.iBar)
        aSBar.iBar->SetModel(&aSBar.iModel);
	}

void CEikScrollBarFrame::SetParentWindow(CCoeControl* aParentWindow)
	{
	if (iExtension)
        {
        iExtension->iParentWindow=aParentWindow;
        }
    else
        {
        iExtension = new CEikScrollBarFrameExtension();
        if (iExtension)
            {
            iExtension->iParentWindow = aParentWindow;
            iExtension->iH.iModel = TAknDoubleSpanScrollBarModel();
            iExtension->iH.iBar = NULL;
            iExtension->iH.iExternalScrollBarAttached = EFalse;
            iExtension->iH.iVisibility = EOff; 
            }
        }
	}

CCoeControl* CEikScrollBarFrame::ParentWindow() const
	{
    if (iExtension)
        {
        return iExtension->iParentWindow;
        }
    else
        {
        return NULL;
        }
	}



EXPORT_C void CEikScrollBarFrame::SetScrollBarFrameObserver(MEikScrollBarObserver* aObserver)
	{
    if( !AknLayoutUtils::PenEnabled() )
        {
        return;
        }
    
    iExtension->iScrollBarObserver = aObserver;
    
    if(iV.iBar)
        {
        iV.iBar->SetScrollBarObserver(aObserver);
        }
    if(iExtension && iExtension->iH.iBar)
        {
        iExtension->iH.iBar->SetScrollBarObserver(aObserver);
        }
	}

MEikScrollBarObserver* CEikScrollBarFrame::ScrollBarFrameObserver()
	{
	if(AknLayoutUtils::PenEnabled())
        return iExtension->iScrollBarObserver;
	else
	    return NULL;
	}

// Functions which don't do anything useful in the avkon UI
EXPORT_C void CEikScrollBarFrame::SetAdjustsHorizontalModel(TBool /*aAdjusts*/)
	{
	}

EXPORT_C void CEikScrollBarFrame::SetAdjustsVerticalModel(TBool /*aAdjusts*/)
	{
	}

EXPORT_C void CEikScrollBarFrame::MoveHorizThumbTo(TInt aHorizThumbPos)
	{
	if (iExtension && iExtension->iH.iBar)
		{
        if (TypeOfVScrollBar() == TScrollBarType(EDoubleSpan))
            {
            // EDoubleSpan has different model.
            if (iV.iModel.ScrollBarModelType() == TEikScrollBarModel::EAknDoubleSpanScrollBarModel)
                {
                TAknDoubleSpanScrollBarModel* model = static_cast <TAknDoubleSpanScrollBarModel*> (&(iExtension->iH.iModel));
                model->SetFocusPosition(aHorizThumbPos);    
                }
            else
                {
                // Error. User of the API is perhaps assigning values directly to TEikScrollBarModel
                // member variables which is not allowed with EAknDoubleSpanScrollBarModel.
                // #ifdef _DEBUG
                // RDebug::Print(_L("CEikScrollBarFrame: Please, use TAknDoubleSpanScrollBarModel instead of TEikScrollBarModel"));
                // #endif
                // In most cases we can work with the TEikScrollBarModel model.
        		iExtension->iH.iModel.iThumbPosition = aHorizThumbPos;
                }
            }
		ApplyModel(iExtension->iH);
		}
	}

EXPORT_C void CEikScrollBarFrame::SetTypeOfHScrollBar(TScrollBarType aType)
	{
    if (iExtension && iExtension->iH.iBar)
        {
        if (TypeOfHScrollBar() == aType)
            return; // already set to requested type

        if (aType == CEikScrollBarFrame::TScrollBarType(EDoubleSpan))
            {
            TRAP_IGNORE(CreateDoubleSpanScrollBarsL(ETrue,EFalse)); // by default a window owning                
            return;    
            }

        if (aType == CEikScrollBarFrame::TScrollBarType(EArrowHead))
            {
            return; // not supported   
            }
        }
	}

EXPORT_C void CEikScrollBarFrame::SetTypeOfVScrollBar(TScrollBarType aType)
	{
    if (iV.iBar)
        {
        if (TypeOfVScrollBar() == aType)
            return; // already set to requested type


        if (aType == CEikScrollBarFrame::TScrollBarType(EDoubleSpan))
            {
            TRAP_IGNORE(CreateDoubleSpanScrollBarsL(ETrue,EFalse)); // by default a window owning                
            return;    
            }

        if (aType == CEikScrollBarFrame::TScrollBarType(EArrowHead))
            {
            TRAP_IGNORE(CreateArrowHeadScrollBarsL());
            return;    
            }
        }
	}

EXPORT_C CEikScrollBarFrame::TScrollBarType CEikScrollBarFrame::TypeOfHScrollBar() const
	{
    if (iExtension && iExtension->iH.iBar && 
       (iExtension->iH.iBar->ScrollBarType() == CEikScrollBar::TScrollBarType(EDoubleSpan)))
        {
        return EDoubleSpan;
        }
    else
        {
	    return EArrowHead;
        }
	}

EXPORT_C CEikScrollBarFrame::TScrollBarType CEikScrollBarFrame::TypeOfVScrollBar() const
	{
    if (iV.iBar && (iV.iBar->ScrollBarType() == CEikScrollBar::TScrollBarType(EDoubleSpan)))
        {
        return EDoubleSpan;
        }
    else
        {
	    return EArrowHead;
        }
	}

EXPORT_C TBool CEikScrollBarFrame::IsArrowHeadScrollBar(TInt /*aFlag*/) const
	{
    if (TypeOfVScrollBar() == TScrollBarType(EArrowHead))
        {
        return ETrue;
        }
    else
        {
        return EFalse;
        }
	}

EXPORT_C void CEikScrollBarFrame::CreateDoubleSpanScrollBarsL(TBool aWindowOwning, TBool aRemote)
    {
    CreateDoubleSpanScrollBarsL(aWindowOwning, aRemote, ETrue, ETrue);
    }

EXPORT_C void CEikScrollBarFrame::CreateDoubleSpanScrollBarsL(TBool aWindowOwning, TBool aRemote, TBool aVertical, TBool aHorizontal)
    {
    if (!TAknDoubleSpanScrollBarModel::ModelIsSupported())
        {
        return;
        }

    // This method should not delete the old scrollbars before it is sure that new 
    // one has been succesfully created. Create a temp variable here.
    SBarData newVerticalScrollBar;
    newVerticalScrollBar.iBar = NULL;
    newVerticalScrollBar.iExternalScrollBarAttached = EFalse;
    newVerticalScrollBar.iVisibility = iV.iVisibility;

    SBarData newHorizontalScrollBar;
    newHorizontalScrollBar.iBar = NULL;
    newHorizontalScrollBar.iExternalScrollBarAttached = EFalse;
    if (iExtension)
        newHorizontalScrollBar.iVisibility = iExtension->iH.iVisibility;

    if (aRemote && iExtension && iExtension->iParentWindow)
        {
        // try getting scrollbarframe from parent using mop supply mechanism
        CEikScrollBarFrame* sbf = iExtension->iParentWindow->MopGetObject(sbf);
        if (sbf)
            {
            newVerticalScrollBar.iBar = sbf->VerticalScrollBar();
            newVerticalScrollBar.iExternalScrollBarAttached = ETrue;
            
            newHorizontalScrollBar.iBar = sbf->HorizontalScrollBar();
            newHorizontalScrollBar.iExternalScrollBarAttached = ETrue;
            
            TInt err1 = KErrNone;
            TInt err2 = KErrNone;
            if (newVerticalScrollBar.iBar)
                {
                TRAP(err1, newVerticalScrollBar.iBar->AddExternalFrameL(this));
                }

            if (newHorizontalScrollBar.iBar)
                {
                TRAP(err2, newHorizontalScrollBar.iBar->AddExternalFrameL(this));
                }
            
            if (err1 || err2)
	            {
	            newVerticalScrollBar.iExternalScrollBarAttached = EFalse;
	            newVerticalScrollBar.iBar = NULL;
	            newHorizontalScrollBar.iExternalScrollBarAttached = EFalse;
	            newHorizontalScrollBar.iBar = NULL;
	            }

            User::LeaveIfError(err1);
            User::LeaveIfError(err2);

            if (TypeOfVScrollBar() == EDoubleSpan)
                {
                if( AknLayoutUtils::PenEnabled() )
                    {
	    			// Correction. Giving null reference as parameter screws up the model values
                    newVerticalScrollBar.iModel = TAknDoubleSpanScrollBarModel();
                    }
                else
                    {
                    newVerticalScrollBar.iModel = TAknDoubleSpanScrollBarModel(0);
                    }
                }

            if (TypeOfHScrollBar() == EDoubleSpan)
                {
                if( AknLayoutUtils::PenEnabled() )
                    {
                    // Correction. Giving null reference as parameter screws up the model values
                    newHorizontalScrollBar.iModel = TAknDoubleSpanScrollBarModel();
                    }
                else
                    {
                    newHorizontalScrollBar.iModel = TAknDoubleSpanScrollBarModel(0);
                    }
                }

            }
        else
            {
            User::Leave(KErrNotFound);
            }
        }
    else
        {
        // Create new vertical AknDoubleSpanScrollBar
        newVerticalScrollBar.iBar = 0;
        newVerticalScrollBar.iExternalScrollBarAttached=EFalse;
        
        CAknDoubleSpanScrollBar* verticalScrollBar = NULL;

        MEikScrollBarObserver* observer = NULL;

        if(AknLayoutUtils::PenEnabled())
            {
            if(iExtension)
                {
                observer = iExtension->iScrollBarObserver;
                }
            }

        TInt scrollBarFlags = 
            ( ( iScrollBarFrameFlags & EEnableNudgeButtons ) ? 
                CEikScrollBar::EEnableNudgeButtons : 0 ) |
            ( ( iScrollBarFrameFlags & EDisableExpandedTouchArea ) ? 
                CEikScrollBar::EDisableExpandedTouchArea : 0 );
                
        if (aVertical)
            {
            verticalScrollBar = new(ELeave) CAknDoubleSpanScrollBar(ParentWindow());            
            CleanupStack::PushL(verticalScrollBar);
            verticalScrollBar->ConstructL(
                aWindowOwning, observer ,ParentWindow(),
                CAknScrollBar::EVertical,
                KLongEnoughToCauseComponentsToBeCreated,
                scrollBarFlags );
            CleanupStack::Pop(); // verticalScrollBar
            }
        newVerticalScrollBar.iBar = verticalScrollBar;
        if( AknLayoutUtils::PenEnabled() )
            {
            // Correction. Giving null reference as parameter screws up the model values
            newVerticalScrollBar.iModel = TAknDoubleSpanScrollBarModel();
            }
        else
            {
            newVerticalScrollBar.iModel = TAknDoubleSpanScrollBarModel(0);
            }

        // Create new horizontal AknDoubleSpanScrollBar
        newHorizontalScrollBar.iBar = 0;
        newHorizontalScrollBar.iExternalScrollBarAttached=EFalse;
        CAknDoubleSpanScrollBar* horizontalScrollBar = NULL;
       
        if (aHorizontal)
            {
            horizontalScrollBar = new(ELeave) CAknDoubleSpanScrollBar(ParentWindow());
            CleanupStack::PushL(horizontalScrollBar);
            horizontalScrollBar->ConstructL(
                aWindowOwning, observer ,ParentWindow(),
                CAknScrollBar::EHorizontal,
                KLongEnoughToCauseComponentsToBeCreated,
                scrollBarFlags );
            CleanupStack::Pop(); // horizontalScrollBar
            }
        newHorizontalScrollBar.iBar = horizontalScrollBar;        
        if( AknLayoutUtils::PenEnabled() )
            {
            // Correction. Giving null reference as parameter screws up the model values
            newHorizontalScrollBar.iModel = TAknDoubleSpanScrollBarModel();
            }
        else
            {
            newHorizontalScrollBar.iModel = TAknDoubleSpanScrollBarModel(0);
            }
        }

    TBool oldVerticalScrollbarExists = EFalse;
    TBool oldHorizontalScrollbarExists = EFalse;

    if (iV.iBar)
        oldVerticalScrollbarExists = ETrue;

    if (iExtension && iExtension->iH.iBar)
        oldHorizontalScrollbarExists = ETrue;

    
    if (oldVerticalScrollbarExists || oldHorizontalScrollbarExists)
        {
        // Remove old scroll bar
        DeleteScrollBars();
        }
    
    iV = newVerticalScrollBar;
    
    if (iExtension)
        iExtension->iH = newHorizontalScrollBar;

    }


EXPORT_C void CEikScrollBarFrame::Tile(TEikScrollBarModel* aVModel, TRect& aVScrollBarRect)
    {
	Tile(aVModel);
	TRect tempRect(aVScrollBarRect);
    if(aVScrollBarRect.Height() < 0 )
        {
        aVScrollBarRect.iTl.iY = aVScrollBarRect.iBr.iY;
        aVScrollBarRect.iBr.iY = tempRect.iTl.iY;
        }
    if(aVScrollBarRect.Width() < 0 )
        {
        aVScrollBarRect.iTl.iX = aVScrollBarRect.iBr.iX;
        aVScrollBarRect.iBr.iX = tempRect.iTl.iX;
        }
    if (iV.iBar && TypeOfVScrollBar() == EDoubleSpan && iV.iExternalScrollBarAttached==EFalse )
        {
        CAknDoubleSpanScrollBar* scrollbar = static_cast <CAknDoubleSpanScrollBar*> (iV.iBar);
        // check if fixed layout has been set
        if (scrollbar->FixedLayoutRect().Size() == TSize(0,0))
            {
            if (aVScrollBarRect != TRect(iV.iBar->Position(), iV.iBar->Size()))
                {
                iV.iBar->SetRect(aVScrollBarRect);
                }
            }
        }
    }


void CEikScrollBarFrame::DeleteScrollBars()
    {
    //
    // Delete vertical scollbar
    //
    if(!iV.iExternalScrollBarAttached)
        delete(iV.iBar);
    else if (iV.iBar)
	    {
	    if (iExtension && iExtension->iParentWindow && iExtension->iParentWindow->IsVisible())
		    {
		    // This test will be false if the app is being destroyed, making it unsafe to resize the CBA.
		    if (CCoeEnv::Static()->NormalFont())
			    iV.iBar->MakeVisible(EFalse);
		    }
	    iV.iBar->RemoveExternalFrame(this);		// calls back to DisconnectExternalScrollBar to null iV.iBar
	    __ASSERT_DEBUG(iV.iBar == NULL, SbfPanic(EFailedToRemoveExternalScrollBar));
	    }

    //
    // Delete horizontal scrollbar
    //
    if(iExtension && iExtension->iH.iBar)
        {
        if(!(iExtension->iH.iExternalScrollBarAttached))
            {
            delete(iExtension->iH.iBar);
            iExtension->iH.iBar = NULL;
            }
        else if (iExtension->iH.iBar)
	        {
	        if (iExtension && iExtension->iParentWindow && iExtension->iParentWindow->IsVisible())
		        {
		        // This test will be false if the app is being destroyed, making it unsafe to resize the CBA.
		        if (CCoeEnv::Static()->NormalFont())
			        iExtension->iH.iBar->MakeVisible(EFalse);
		        }
	        iExtension->iH.iBar->RemoveExternalFrame(this);		// calls back to DisconnectExternalScrollBar to null iV.iBar
	        __ASSERT_DEBUG(iExtension->iH.iBar == NULL, SbfPanic(EFailedToRemoveExternalScrollBar));
	        }    
        }
    }


void CEikScrollBarFrame::CreateArrowHeadScrollBarsL()
    {
    CEikCba* cba=GetCurrentCba();
    if (cba)
        {
        // create arrow heads
        TRAPD(err, cba->CreateArrowHeadScrollBarL()); 
        if (err)
            {
		    iV.iExternalScrollBarAttached = EFalse;
		    iV.iBar = NULL;
	        return;
            }
        // delete old scroll bars
        DeleteScrollBars();
        // returns the vertical scroll bar from the top scroll bar host
		iV.iBar=cba->VScrollBarAsControl();
		iV.iExternalScrollBarAttached=ETrue;
		TRAPD(err2, iV.iBar->AddExternalFrameL(this));
		if (err2)
		    {
			iV.iExternalScrollBarAttached = EFalse;
			iV.iBar = NULL;
			}
		}
    }

void CEikScrollBarFrame::CalcTheoreticalScrollBarVisibility(const TEikScrollBarModel* aVModel, const TEikScrollBarModel* aHModel)
    {
	// assume no scrollbars to start with
    iScrollBarFrameFlags&=(~EDisplayVScrollBar);
	iScrollBarFrameFlags&=(~EDisplayHScrollBar);
    
    TBool verticalScrollBarUseful = EFalse;
    TBool horizontalScrollBarUseful = EFalse;

    if (aVModel)
        {
        switch(TypeOfVScrollBar())
            {
            case EDoubleSpan:
                {
                if (aVModel->ScrollBarModelType() == TEikScrollBarModel::EAknDoubleSpanScrollBarModel)
                    {
                    //const TAknDoubleSpanScrollBarModel* model = static_cast <const TAknDoubleSpanScrollBarModel*> (aVModel);
                    //verticalScrollBarUseful = (model->FocusPosition() < model->ScrollSpan()) && (model->WindowSize() <= model->ScrollSpan());    
                    verticalScrollBarUseful = ETrue; // S60 style says double span scrollbar is always shown if visibility is EAuto
                    }
                else
                    {
                    // Error. User of the API is perhaps assigning values directly to TEikScrollBarModel
                    // member variables which is not allowed with EAknDoubleSpanScrollBarModel.
                    //#ifdef _DEBUG
                    //RDebug::Print(_L("CEikScrollBarFrame: Please, use TAknDoubleSpanScrollBarModel instead of TEikScrollBarModel"));
                    //#endif
                    // In most cases we can work with the TEikScrollBarModel model.
                    //verticalScrollBarUseful = (aVModel->iThumbPosition < aVModel->iScrollSpan) && (aVModel->iThumbSpan <= aVModel->iScrollSpan);    
                    verticalScrollBarUseful = ETrue; // S60 style says double span scrollbar is always shown if visibility is EAuto
                    }
                break;
                }

            case EArrowHead: // fallthrough
            default:
                {
                verticalScrollBarUseful = aVModel->ScrollBarUseful();
                break;
                }
            }
        }

    if (aHModel)
        {
        switch(TypeOfHScrollBar())
            {
            case EDoubleSpan: // by default only double span is supported as horizontal scrollbar
            default:
                {
                if (aHModel->ScrollBarModelType() == TEikScrollBarModel::EAknDoubleSpanScrollBarModel)
                    {
                    //const TAknDoubleSpanScrollBarModel* model = static_cast <const TAknDoubleSpanScrollBarModel*> (aHModel);
                    //horizontalScrollBarUseful = (model->FocusPosition() < model->ScrollSpan()) && (model->WindowSize() <= model->ScrollSpan());    
                    horizontalScrollBarUseful = ETrue; // S60 style says double span scrollbar is always shown if visibility is EAuto
                    }
                else
                    {
                    // Error. User of the API is perhaps assigning values directly to TEikScrollBarModel
                    // member variables which is not allowed with EAknDoubleSpanScrollBarModel.
                    //#ifdef _DEBUG
                    //RDebug::Print(_L("CEikScrollBarFrame: Please, use TAknDoubleSpanScrollBarModel instead of TEikScrollBarModel"));
                    //#endif
                    // In most cases we can work with the TEikScrollBarModel model.
                    //horizontalScrollBarUseful = (aHModel->iThumbPosition < aHModel->iScrollSpan) && (aHModel->iThumbSpan <= aVModel->iScrollSpan);    
                    horizontalScrollBarUseful = ETrue; // S60 style says double span scrollbar is always shown if visibility is EAuto
                    }
                break;
                }
            }
        }


    // Decide visibility for vertical scrollbar
    if ( (iV.iVisibility==EOn) || ( (iV.iVisibility==EAuto)&&(verticalScrollBarUseful) ) )
        {
        iScrollBarFrameFlags|=EDisplayVScrollBar;
        }

    // Decide visibility for horizontal scrollbar
    if (iExtension && (iExtension->iH.iVisibility==EOn || (iExtension->iH.iVisibility==EAuto && horizontalScrollBarUseful)))
        {
        iScrollBarFrameFlags|=EDisplayHScrollBar;
        }
    }

EXPORT_C CEikScrollBarFrame::TScrollBarVisibility CEikScrollBarFrame::ScrollBarVisibility(CEikScrollBar::TOrientation aOrientation) const
    {
    if (aOrientation == CEikScrollBar::EVertical)
        {
        return iV.iVisibility;
        }
    else
        {
        if (iExtension)
            {
            return iExtension->iH.iVisibility;
            }
        else
            {
            return EOff;
            }

        }
    }

EXPORT_C void CEikScrollBarFrame::Tile(TEikScrollBarModel* aHModel, TEikScrollBarModel* aVModel)
    {
	GetScrollBars(EFalse);
	CalcTheoreticalScrollBarVisibility(aVModel,aHModel);
	
	if (iV.iVisibility!=EOff)
		iV.iModel = *aVModel;
    
    MakeSBarVisible(iV, iScrollBarFrameFlags&EDisplayVScrollBar);
	
    if (iExtension && iExtension->iH.iBar)
        {
   	    if (iExtension->iH.iVisibility!=EOff)
	        iExtension->iH.iModel = *aHModel;
   	    
   	    MakeSBarVisible(iExtension->iH, iScrollBarFrameFlags&EDisplayHScrollBar);
        }

    }

EXPORT_C TInt CEikScrollBarFrame::DrawBackground(TBool aDrawHorizontal, TBool aDrawVertical)
	{
	// The double span scrollbar only supports backgroun drawing flag
	if(TypeOfHScrollBar() != EDoubleSpan && TypeOfVScrollBar() != EDoubleSpan)
		{
		return KErrNotSupported;
		}
	
	if(iV.iBar && (TypeOfVScrollBar() == EDoubleSpan))
		{
		CAknDoubleSpanScrollBar* scrollbar = static_cast <CAknDoubleSpanScrollBar*> (iV.iBar);
		scrollbar->DrawBackground(aDrawVertical);
		}
	
	if(iExtension && iExtension->iH.iBar && (TypeOfHScrollBar() == EDoubleSpan))
		{
		CAknDoubleSpanScrollBar* scrollbar = static_cast <CAknDoubleSpanScrollBar*> (iExtension->iH.iBar);
		scrollbar->DrawBackground(aDrawHorizontal);
		}
	
	return KErrNone;				
	}
	
EXPORT_C TInt CEikScrollBarFrame::DrawBackgroundState(TBool& aDrawHorizontal, TBool& aDrawVertical)
	{
	// The double span scrollbar only supports backgroun drawing flag
		
	if(iV.iBar && (TypeOfVScrollBar() == EDoubleSpan))
		{
		CAknDoubleSpanScrollBar* scrollbar = static_cast <CAknDoubleSpanScrollBar*> (iV.iBar);		
		aDrawVertical = scrollbar->DrawBackgroundState();
		}
	
	if(iExtension && iExtension->iH.iBar && (TypeOfHScrollBar() == EDoubleSpan))
		{
		CAknDoubleSpanScrollBar* scrollbar = static_cast <CAknDoubleSpanScrollBar*> (iExtension->iH.iBar);
		aDrawHorizontal = scrollbar->DrawBackgroundState();
		}
	
	if(TypeOfHScrollBar() != EDoubleSpan && TypeOfVScrollBar() != EDoubleSpan)
		{
		return KErrNotSupported;
		}
	
	return KErrNone;
	}

CEikScrollBar* CEikScrollBarFrame::HorizontalScrollBar() const
    {
    if (iExtension)
        return iExtension->iH.iBar;
    else
        return NULL;
    }



// For Cba Scrollbar frame

CEikCbaScrollBarFrame::CEikCbaScrollBarFrame(CCoeControl* aParentWindow, MEikScrollBarObserver* /*aObserver*/, TBool /*aPreAlloc*/)
	{
	SetParentWindow(aParentWindow);
	}

void CEikCbaScrollBarFrame::ConstructL()
	{
    iV.iBar = 0;
    iV.iExternalScrollBarAttached=EFalse;
    
    // We construct CEikScrollBar instance here, because it doesn't create bitmaps -> faster 
    // and save RAM. If CBAs are really needed, then we replace CEikScrollBar with  
    // CAknArrowHeadScrollBar instance at SwitchArrowHeadScrollBarL method.
    iV.iBar = new(ELeave) CEikScrollBar();
    iV.iBar->ConstructL(NULL,ParentWindow(),CAknScrollBar::EVertical,KLongEnoughToCauseComponentsToBeCreated,0);
	}
	
// Delete CEikScrollBar instance and replace it with actual arrow head scroll bar
void CEikCbaScrollBarFrame::SwitchToArrowHeadScrollBarL()
	{
	delete(iV.iBar);
	iV.iBar = 0;
	iV.iExternalScrollBarAttached=EFalse;
	iV.iBar = new(ELeave) CAknArrowHeadScrollBar(ParentWindow());
	iV.iBar->ConstructL(NULL,ParentWindow(),CAknScrollBar::EVertical,KLongEnoughToCauseComponentsToBeCreated,0);
	}

