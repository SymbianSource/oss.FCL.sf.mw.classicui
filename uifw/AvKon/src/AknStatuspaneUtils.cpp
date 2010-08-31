/*
* Copyright (c) 2004-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Statuspane related utilities.
*
*/


#include <avkon.rsg>
#include <AknLayout.lag>
#include <eikspane.h>
#include <AknSgcc.h>
#include <layoutmetadata.cdl.h>
#include <eikappui.h>
#include <eikapp.h>

#include "AknStatuspaneUtils.h"
#include "aknenv.h"

EXPORT_C TBool AknStatuspaneUtils::IdleLayoutActive()
    {
    TBool retVal = EFalse;
    
    TInt currentStatusPaneLayoutResId = CurrentStatusPaneLayoutResId();
        
    retVal = ( currentStatusPaneLayoutResId == R_AVKON_STATUS_PANE_LAYOUT_IDLE ||
               currentStatusPaneLayoutResId == R_AVKON_STATUS_PANE_LAYOUT_IDLE_EXT ||
               currentStatusPaneLayoutResId == R_AVKON_STATUS_PANE_LAYOUT_IDLE_FLAT ||
               currentStatusPaneLayoutResId == R_AVKON_STATUS_PANE_LAYOUT_IDLE_MIRRORED || 
               currentStatusPaneLayoutResId == R_AVKON_STATUS_PANE_LAYOUT_VT ||
               currentStatusPaneLayoutResId == R_AVKON_STATUS_PANE_LAYOUT_VT_MIRRORED ||
               currentStatusPaneLayoutResId == R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_RIGHT ||
               currentStatusPaneLayoutResId == R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_LEFT ||
               currentStatusPaneLayoutResId == R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE ||
               currentStatusPaneLayoutResId == R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT ||
               currentStatusPaneLayoutResId == R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT_NO_SOFTKEYS );
        
    return retVal;
    }

EXPORT_C TBool AknStatuspaneUtils::UsualLayoutActive()
    {
    TBool retVal = EFalse;

    TInt currentStatusPaneLayoutResId = CurrentStatusPaneLayoutResId();

    retVal = ( currentStatusPaneLayoutResId == R_AVKON_STATUS_PANE_LAYOUT_USUAL ||
               currentStatusPaneLayoutResId == R_AVKON_STATUS_PANE_LAYOUT_USUAL_EXT ||
               currentStatusPaneLayoutResId == R_AVKON_STATUS_PANE_LAYOUT_USUAL_FLAT ||
               currentStatusPaneLayoutResId == R_AVKON_STATUS_PANE_LAYOUT_USUAL_MIRRORED ||
               currentStatusPaneLayoutResId == R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_RIGHT ||
               currentStatusPaneLayoutResId == R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_LEFT ||
               currentStatusPaneLayoutResId == R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL ||
               currentStatusPaneLayoutResId == R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL_FLAT ||
               currentStatusPaneLayoutResId == R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL_FLAT_NO_SOFTKEYS );

    return retVal;
    }


EXPORT_C TBool AknStatuspaneUtils::SmallLayoutActive()
    {
    TBool retVal = EFalse;

    TInt currentStatusPaneLayoutResId = CurrentStatusPaneLayoutResId();
        
    retVal = ( currentStatusPaneLayoutResId == R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE ||
               currentStatusPaneLayoutResId == R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE_MIRRORED ||
               currentStatusPaneLayoutResId == R_AVKON_STATUS_PANE_LAYOUT_SMALL );
    
    return retVal;
    }

EXPORT_C TBool AknStatuspaneUtils::StaconPaneActive()
    {
    TBool retVal = EFalse;

    TInt currentStatusPaneLayoutResId = CurrentStatusPaneLayoutResId();

    retVal = ( currentStatusPaneLayoutResId == R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_RIGHT ||
               currentStatusPaneLayoutResId == R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_LEFT  ||
               currentStatusPaneLayoutResId == R_AVKON_STACON_PANE_LAYOUT_EMPTY_SOFTKEYS_RIGHT ||
               currentStatusPaneLayoutResId == R_AVKON_STACON_PANE_LAYOUT_EMPTY_SOFTKEYS_LEFT  ||        
               currentStatusPaneLayoutResId == R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_RIGHT  ||
               currentStatusPaneLayoutResId == R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_LEFT );
                 
    return retVal;
    }


EXPORT_C TBool AknStatuspaneUtils::StaconSoftKeysLeft()
    {
    TBool retVal = EFalse;

    TInt currentStatusPaneLayoutResId = CurrentStatusPaneLayoutResId();
        
    retVal = ( currentStatusPaneLayoutResId == R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_LEFT ||
               currentStatusPaneLayoutResId == R_AVKON_STACON_PANE_LAYOUT_EMPTY_SOFTKEYS_LEFT ||
               currentStatusPaneLayoutResId == R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_LEFT );
    
    return retVal;
    }

EXPORT_C TBool AknStatuspaneUtils::StaconSoftKeysRight()
    {
    TBool retVal = EFalse;

    TInt currentStatusPaneLayoutResId = CurrentStatusPaneLayoutResId();
        
    retVal = ( currentStatusPaneLayoutResId == R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_RIGHT ||
               currentStatusPaneLayoutResId == R_AVKON_STACON_PANE_LAYOUT_EMPTY_SOFTKEYS_RIGHT ||
               currentStatusPaneLayoutResId == R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_RIGHT ) ||
		( HDLayoutActive() && currentStatusPaneLayoutResId != R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT_NO_SOFTKEYS );
    
    return retVal;
    }

EXPORT_C TBool AknStatuspaneUtils::FlatLayoutActive()
    {
    TBool retVal = EFalse;

    TInt currentStatusPaneLayoutResId = CurrentStatusPaneLayoutResId();

    retVal = ( currentStatusPaneLayoutResId == R_AVKON_STATUS_PANE_LAYOUT_USUAL_FLAT || 
               currentStatusPaneLayoutResId == R_AVKON_STATUS_PANE_LAYOUT_IDLE_FLAT ||
               currentStatusPaneLayoutResId == R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL_FLAT ||
               currentStatusPaneLayoutResId == R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT ||
               currentStatusPaneLayoutResId == R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL_FLAT_NO_SOFTKEYS ||
               currentStatusPaneLayoutResId == R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT_NO_SOFTKEYS );

    return retVal;
    }

EXPORT_C TBool AknStatuspaneUtils::TouchPaneCompatibleLayoutActive()
    {
    TBool retVal = EFalse;
    
    TInt currentStatusPaneLayoutResId = CurrentStatusPaneLayoutResId();

    retVal = ( currentStatusPaneLayoutResId != R_AVKON_STATUS_PANE_LAYOUT_EMPTY && 
               currentStatusPaneLayoutResId != R_AVKON_STATUS_PANE_LAYOUT_POWER_OFF_RECHARGE && 
               currentStatusPaneLayoutResId != R_AVKON_STACON_PANE_LAYOUT_EMPTY_SOFTKEYS_LEFT && 
               currentStatusPaneLayoutResId != R_AVKON_STACON_PANE_LAYOUT_EMPTY_SOFTKEYS_RIGHT );

    return retVal;
    }

EXPORT_C TBool AknStatuspaneUtils::ExtendedLayoutActive()
    {
    TBool retVal = EFalse;

    TInt currentStatusPaneLayoutResId = CurrentStatusPaneLayoutResId();

    retVal = ( currentStatusPaneLayoutResId == R_AVKON_STATUS_PANE_LAYOUT_USUAL_EXT ||
    		   currentStatusPaneLayoutResId == R_AVKON_STATUS_PANE_LAYOUT_IDLE_EXT ||
               currentStatusPaneLayoutResId == R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL ||
               currentStatusPaneLayoutResId == R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE );

    return retVal;
    
    }


TBool AknStatuspaneUtils::HDLayoutActive()
    {
    TBool retVal = EFalse;
    
    if ( Layout_Meta_Data::IsLandscapeOrientation() )
        {
        // Can be widescreen only in landscape orientation.
        TInt currentStatusPaneLayoutResId = CurrentStatusPaneLayoutResId();
        
        retVal = ( currentStatusPaneLayoutResId == R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL ||
                   currentStatusPaneLayoutResId == R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE ||
                   currentStatusPaneLayoutResId == R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL_FLAT ||
                   currentStatusPaneLayoutResId == R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT ||
                   currentStatusPaneLayoutResId == R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL_FLAT_NO_SOFTKEYS ||
                   currentStatusPaneLayoutResId == R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT_NO_SOFTKEYS );
        }
    
    return retVal;
    }


EXPORT_C TBool AknStatuspaneUtils::ExtendedStaconPaneActive()
    {
	if ( AknStatuspaneUtils::StaconPaneActive() )
		{
        TBool smallDigitalClockShownInStacon = ETrue;
            
        // Check for small digital clock if app has no status pane. Status pane clock
        // is shown only in resolutions having aspect ratio equal or wider than qvga
        // because otherwise there is no space for it.
        TAknWindowLineLayout screenLayout =
            AknLayout::screen();
        TRect screenRect = screenLayout.Rect(); 

       	TReal aspectRatio = TReal(screenRect.Width()) / TReal(screenRect.Height());
       	if ( aspectRatio <= 1.33 )
       	    {
			smallDigitalClockShownInStacon = EFalse;
      	    }
    	
	    return smallDigitalClockShownInStacon;				
		}
	else
		{
		return EFalse;	
		}			
	}

EXPORT_C TBool AknStatuspaneUtils::ExtendedFlatLayoutActive()
	{
	if ( FlatLayoutActive() &&
	     Layout_Meta_Data::IsLandscapeOrientation() &&
	     !HDLayoutActive() )
		{
        TBool smallDigitalClockShown = EFalse;
        
	    CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
            
	   	if (statusPane && statusPane->PaneCapabilities(TUid::Uid(EEikStatusPaneUidDigitalClock)).IsInCurrentLayout())
	   		{
	        // Final check for small digital clock, shown only in resolutions having aspect 
	        // ratio equal or wider than qvga because otherwise there is no space for it.
	        TAknWindowLineLayout screenLayout =
	            AknLayout::screen();
	        TRect screenRect = screenLayout.Rect(); 

	       	TReal aspectRatio = TReal(screenRect.Width()) / TReal(screenRect.Height());
	       	if ( aspectRatio > 1.33 )
	       	    {
				smallDigitalClockShown = ETrue;
	       	    }
	    	}
	    return smallDigitalClockShown;				
		}
	else
		{
		return EFalse;	
		}			
	}
	
EXPORT_C TInt AknStatuspaneUtils::CurrentStatusPaneLayoutResId()
    {
    TInt resourceId = 0;
    CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
    
    if ( statusPane ) // Return the resource ID of app statuspane if it exists.
        {
        resourceId = statusPane->CurrentLayoutResId();
        }
    else // If this app does not have statuspane, then we ask the layout from AknCapServer.
        {
        resourceId = CAknSgcClient::CurrentStatuspaneResource();
        }
        
    return resourceId;
    }

TBool AknStatuspaneUtils::IsActiveIdle()
    {
    TBool isAcIdle = EFalse;
    
    const TUid KActiveIdle2Uid = {0x102750F0};
    CEikApplication* app = CEikonEnv::Static()->EikAppUi()->Application();
    
    if ( app && app->AppDllUid() == KActiveIdle2Uid )
        {
        isAcIdle = ETrue;
        }
    
    return isAcIdle;
    }

