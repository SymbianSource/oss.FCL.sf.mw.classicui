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
* Intermediate class for setting pages with listboxes in them
*
*/


#include "AknListBoxSettingPage.h"
#include "AknUtils.h"

#include <gulicon.h>

#include <AknTasHook.h>
// Skins support
#include <AknsDrawUtils.h>

#include <AknLayout2ScalableDef.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <layoutmetadata.cdl.h>

#include <aknlists.h>

//
// Constructor for CAknListBoxSettingPage
//

/**
*
* Empty implementation of constructors for the ancestor of listbox-hosting setting pages
*
*/
CAknListBoxSettingPage::CAknListBoxSettingPage( TInt aSettingPageResourceId ) : CAknSettingPage( aSettingPageResourceId )
	{
	AKNTASHOOK_ADD( this, "CAknListBoxSettingPage" );
	}

CAknListBoxSettingPage::CAknListBoxSettingPage(	
					const TDesC* aSettingText, 
					TInt aSettingNumber, 
					TInt aControlType,
					TInt aEditorResourceId, 
					TInt aSettingPageResourceId )
					:	CAknSettingPage( 
						aSettingText, 
						aSettingNumber, 
						aControlType, 
						aEditorResourceId, 
						aSettingPageResourceId ) 
						
	{
	AKNTASHOOK_ADD( this, "CAknListBoxSettingPage" );
	}

EXPORT_C void CAknListBoxSettingPage::HandleListBoxEventL(CEikListBox* /*aListBox*/, MEikListBoxObserver::TListBoxEvent /*aEventType*/)
	{
	}

EXPORT_C void CAknListBoxSettingPage::CheckAndSetDataValidity()
	{
	if ( ListBoxControl() )
		{
		SetDataValidity( ListBoxControl()->Model()->NumberOfItems()  > 0 ); // Even 1 item is OK. Might not be selected!
		}
	}

EXPORT_C void CAknListBoxSettingPage::UpdateCbaL()
	{
	CAknSettingPage::UpdateCbaL();
	}



EXPORT_C void CAknListBoxSettingPage::SizeChanged ()
	{
	StandardSettingPageLayout();  // Must be part of any re-implementation

	CEikListBox* listbox = ListBoxControl();

    TRect rect( SettingItemContentRect( ETrue ) );
	TRect totalRect( rect );

	if ( listbox )
	    {
	    // The maximum lines for the listbox.
        TAknLayoutScalableParameterLimits listBoxLimits(
            AknLayoutScalable_Avkon::list_set_graphic_pane_copy1_ParamLimits() );

        TInt maxNumberOfRows = listBoxLimits.LastRow() + 1;
        TInt numItemsShown = Min( listbox->Model()->NumberOfItems(),
                                  maxNumberOfRows );

        // The layout for max items is used for empty note display.
        if ( numItemsShown == 0 )
            {
            numItemsShown = maxNumberOfRows;
            }
        
        // Transparent setting page has different layout data
        // for both portrait and landscape
        if ( !IsBackgroundDrawingEnabled() )
            {
            // Transparent does not have as many items as normal list.
            if ( numItemsShown > 6 )
                {
                numItemsShown = 6;
                }
            
            numItemsShown += 6; // skip the normal varieties
            }
        else
            {
            if ( numItemsShown > 6 )
                {
                numItemsShown += 12; // skip the transparent varieties
                }
            }
        
        AknLayoutUtils::LayoutControl(
            listbox,
            rect, 
            AknLayoutScalable_Avkon::list_set_pane_copy1(
                numItemsShown - 1 ) );
        
        totalRect = listbox->Rect();
        
        // Note the scrollbar is not showing in transparent setting page.
        AknLayoutUtils::LayoutVerticalScrollBar(
            listbox->ScrollBarFrame(),
            Rect(),
            TAknWindowComponentLayout::Compose(
                AknLayoutScalable_Avkon::settings_container_pane(),
                TAknWindowComponentLayout::Compose(
                    AknLayoutScalable_Avkon::listscroll_set_pane_copy1(),
                    AknLayoutScalable_Avkon::scroll_pane_cp121_copy1() ) ) );
	    }
	
	TAknLayoutRect layoutRect;
	layoutRect.LayoutRect(
	    totalRect,
        AknLayoutScalable_Avkon::set_opt_bg_pane_g1_copy1() );
    SetEditedItemFrameRects( totalRect, layoutRect.Rect() );
	}

EXPORT_C void CAknListBoxSettingPage::Draw(const TRect& aRect) const
	{
	CAknSettingPage::BaseDraw(aRect);
	}

TBool CAknListBoxSettingPage::FocusToSelectedItem()
	{
	return !FocusToFirstItem(); // This determines whether to use FocusToFirstItem or FocusToSelectedItem.
	}

TBool CAknListBoxSettingPage::FocusToFirstItem()
	{
	return EFalse; 
	}

void CAknListBoxSettingPage::CreateIconAndAddToArrayL(
    CArrayPtr<CGulIcon>*& aIconArray,
    const TAknsItemID& aId,
    const TInt aColorIndex,
    const TDesC& aBmpFile,
    const TInt32 aBmp,
    const TInt32 aBmpM )
    {
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    CFbsBitmap* bitmap = 0;
    CFbsBitmap* mask = 0;

    AknsUtils::CreateColorIconLC( skin,
                                  aId,
                                  KAknsIIDQsnIconColors,
                                  aColorIndex,
                                  bitmap,
                                  mask,
                                  aBmpFile,
                                  aBmp,
                                  aBmpM,
                                  KRgbBlack );

    CGulIcon* gulicon = CGulIcon::NewL( bitmap, mask ); // ownership passed
    CleanupStack::PushL( gulicon );
    
    aIconArray->AppendL( gulicon );
    CleanupStack::Pop( 3 ); // mask, bitmap, gulicon
    }


/**
* CAknListBoxSettingPage reserved methods
*/
EXPORT_C void CAknListBoxSettingPage::CAknListBoxSettingPage_Reserved_1()
	{
	}

// End of File
