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
*     Implements setting_volume_pane
*
*/


#include "aknvolumesettingpage.h"
#include "aknsettingpage.h"

#include <aknlayoutscalable_avkon.cdl.h>

#include <AknTasHook.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



EXPORT_C CAknVolumeSettingPage::CAknVolumeSettingPage(
     TInt aResourceId, TInt& aVolume ):
	 CAknSettingPage(aResourceId),iVolume(aVolume)
	{
	iBackupVolume = iVolume;
	AKNTASHOOK_ADD( this, "CAknVolumeSettingPage" );
	}

EXPORT_C CAknVolumeSettingPage::CAknVolumeSettingPage(	
								const TDesC* aSettingText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId, 
								TInt& aVolume)
								:	CAknSettingPage( 
									aSettingText, 
									aSettingNumber, 
									aControlType, 
									aEditorResourceId, 
									aSettingPageResourceId ), 
									iVolume( aVolume )
	{
	iBackupVolume = iVolume;
	AKNTASHOOK_ADD( this, "CAknVolumeSettingPage" );
	}

/**
 * Destructor
 *
 */
EXPORT_C CAknVolumeSettingPage::~CAknVolumeSettingPage()
	{
	AKNTASHOOK_REMOVE();
	}

EXPORT_C void CAknVolumeSettingPage::ConstructL()
	{
	BaseConstructL();
	VolumeControl()->SetValue( iVolume );

	// Construct an appropriate control context for the contained editor areas.
	// Context produced is owned by CAknSettingPage. 
    SetEditedItemFrameIID( KAknsIIDQsnFrSetOpt, KAknsIIDQsnFrSetOptCenter );
	}

EXPORT_C void CAknVolumeSettingPage::UpdateSettingL()
	{
	iVolume = VolumeControl()->Value();
	if( iSettingPageObserver )
	    {
		iSettingPageObserver->HandleSettingPageEventL(
		        this, MAknSettingPageObserver::EEventSettingChanged);	
		}
	}

EXPORT_C void CAknVolumeSettingPage::AcceptSettingL()
	{
	iVolume = VolumeControl()->Value();
	}

EXPORT_C void CAknVolumeSettingPage::RestoreOriginalSettingL()
	{
	iVolume = iBackupVolume;
	}


EXPORT_C CAknVolumeControl* CAknVolumeSettingPage::VolumeControl()
	{
	return STATIC_CAST( CAknVolumeControl*, EditorControl());
	}

EXPORT_C void CAknVolumeSettingPage::SizeChanged()
	{
	StandardSettingPageLayout();  // Must be part of any re-implementation

    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( CAknSettingPage::SettingItemContentRect( EFalse ),
                AknLayoutScalable_Avkon::setting_volume_pane_copy1() );
    AknLayoutUtils::LayoutControl( EditorControl(), layoutRect.Rect(),
            AknLayoutScalable_Avkon::volume_set_pane_copy1() );
    
    TRect outerFrameRect( layoutRect.Rect() );
	layoutRect.LayoutRect( outerFrameRect,
                           AknLayoutScalable_Avkon::set_opt_bg_pane_g1() );
	SetEditedItemFrameRects( outerFrameRect, layoutRect.Rect() );
	}

EXPORT_C void CAknVolumeSettingPage::Draw(const TRect &aRect) const
    {
    BaseDraw(aRect);
	// There is no pre-skins legacy drawing to suppress/allow here
	// so there is nothing more to do here.
    }


/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 */
#ifndef _DEBUG
EXPORT_C void CAknVolumeSettingPage::WriteInternalStateL(
            RWriteStream& /*aWriteStream*/) const
	{}
#else
EXPORT_C void CAknVolumeSettingPage::WriteInternalStateL(
            RWriteStream& aWriteStream) const
	{
	CAknSettingPage::WriteInternalStateL(aWriteStream);
	}
#endif

EXPORT_C void CAknVolumeSettingPage::HandlePointerEventL(
                const TPointerEvent& aPointerEvent) 
    { 
    CAknSettingPage::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CAknVolumeSettingPage::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

/**
 *	Reserved method derived from CCoeControl
 */
EXPORT_C void CAknVolumeSettingPage::Reserved_2()
	{
	}

/**
* Setting Page reserved methods 
*/ 
EXPORT_C void CAknVolumeSettingPage::CAknSettingPage_Reserved_1()
	{
	}
EXPORT_C void CAknVolumeSettingPage::CAknSettingPage_Reserved_2()
	{
	}

// End of File
