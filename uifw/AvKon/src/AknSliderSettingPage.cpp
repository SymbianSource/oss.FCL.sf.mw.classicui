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
*     Implementation of setting_slider_pane
*
*/


#include "aknslidersettingpage.h"
#include "aknsettingpage.h"
#include <aknlayoutscalable_avkon.cdl.h>
#include <aknappui.h>

#include <AknTasHook.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


EXPORT_C CAknSliderSettingPage::CAknSliderSettingPage( TInt aResourceId, TInt& aSliderValue ):
	 CAknSettingPage(aResourceId),iSliderValue(aSliderValue)
	{
	iBackupSliderValue = iSliderValue;
	AKNTASHOOK_ADD( this, "CAknSliderSettingPage" );
	}

EXPORT_C CAknSliderSettingPage::CAknSliderSettingPage(	
								const TDesC* aSettingText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId, 
								TInt& aSliderValue)
								:	CAknSettingPage( 
									aSettingText, 
									aSettingNumber, 
									aControlType, 
									aEditorResourceId, 
									aSettingPageResourceId ), 
									iSliderValue( aSliderValue )
	{
	iBackupSliderValue = iSliderValue;
	AKNTASHOOK_ADD( this, "CAknSliderSettingPage" );
	}

/**
 * Destructor
 *
 */
EXPORT_C CAknSliderSettingPage::~CAknSliderSettingPage()
	{
	AKNTASHOOK_REMOVE();
	}

EXPORT_C void CAknSliderSettingPage::ConstructL()
	{
	BaseConstructL();
	SliderControl()->SetValueL( iSliderValue );

	// Construct an appropriate control context for the contained editor areas.
	// Context produced is owned by CAknSettingPage. 
    SetEditedItemFrameIID( KAknsIIDQsnFrSetOpt, KAknsIIDQsnFrSetOptCenter );
	}

EXPORT_C void CAknSliderSettingPage::UpdateSettingL()
	{
	iSliderValue = SliderControl()->Value();
	if( iSettingPageObserver )
		iSettingPageObserver->HandleSettingPageEventL(this, MAknSettingPageObserver::EEventSettingChanged);	

	}

EXPORT_C void CAknSliderSettingPage::AcceptSettingL()
	{
	iSliderValue = SliderControl()->Value();
	if( iSettingPageObserver )
		iSettingPageObserver->HandleSettingPageEventL(this, MAknSettingPageObserver::EEventSettingChanged);	

	}

EXPORT_C void CAknSliderSettingPage::RestoreOriginalSettingL()
	{
	iSliderValue = iBackupSliderValue;
	}


EXPORT_C CAknSlider* CAknSliderSettingPage::SliderControl()
	{
	return STATIC_CAST( CAknSlider*, EditorControl());
	}


EXPORT_C void CAknSliderSettingPage::SizeChanged()
	{
	StandardSettingPageLayout();  // Must be part of any re-implementation
    AknLayoutUtils::LayoutControl(
            EditorControl(),
            CAknSettingPage::SettingItemContentRect( EFalse ),
            AknLayoutScalable_Avkon::setting_slider_graphic_pane_copy1() );
    
    TRect frameOuterRect( EditorControl()->Rect() );
    TAknLayoutRect innerLayoutRect;
    innerLayoutRect.LayoutRect(
        frameOuterRect,
        AknLayoutScalable_Avkon::set_opt_bg_pane_g1() );

    SetEditedItemFrameRects( frameOuterRect, innerLayoutRect.Rect() );
	}

EXPORT_C void CAknSliderSettingPage::Draw(const TRect &aRect) const
    {
    BaseDraw(aRect);
	// There is no pre-skins legacy drawing to suppress/allow here so there is nothing
	// more to do here.
    }

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 */
#ifndef _DEBUG
EXPORT_C void CAknSliderSettingPage::WriteInternalStateL(RWriteStream& /*aWriteStream*/) const
	{}
#else
EXPORT_C void CAknSliderSettingPage::WriteInternalStateL(RWriteStream& aWriteStream) const
	{
	CAknSettingPage::WriteInternalStateL(aWriteStream);
	}
#endif

EXPORT_C void CAknSliderSettingPage::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknSettingPage::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CAknSliderSettingPage::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

/**
 *	Reserved method derived from CCoeControl
 */
EXPORT_C void CAknSliderSettingPage::Reserved_2()
	{
	}

/**
* Setting Page reserved methods 
*/ 
EXPORT_C void CAknSliderSettingPage::CAknSettingPage_Reserved_1()
	{
	}
EXPORT_C void CAknSliderSettingPage::CAknSettingPage_Reserved_2()
	{
	}


// End of File
