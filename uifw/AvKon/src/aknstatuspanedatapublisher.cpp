/*
* Copyright (c) 2006-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  AVKON internal publisher for system owned status pane data.
*
*/


// INCLUDE FILES
#include "aknstatuspanedatapublisher.h"
#include <aknglobalpopupprioritycontroller.h>
#include "aknstatuspanedata.h"
#include "avkoninternalpskeys.h"
#include <e32property.h>
#include <AknIndicator.h>
#include <avkon.rsg>
#include <AknStatuspaneUtils.h>
#include <AknUtils.h>
#include <AknIndicatorPlugin.h>
#include <AknIndicatorPluginImplUIDs.hrh>
#include <AknPreviewPopUpController.h>
#include <eikenv.h>
#include <gulicon.h>
#include "aknindicatorpopup.h"
#include <layoutmetadata.cdl.h>
#include <coreapplicationuisdomainpskeys.h> // KCoreAppUIsAutolockStatus
#include <aknlayoutscalable_avkon.cdl.h>

// CONSTANTS
const TUint KEmpty              = 0xFFFFFFFF;
const TInt KNoIndicatorPriority = 0xFFFF;
const TInt KIndicTextBufferSize = 128;
const TInt KAknSignalLength     = EAknSignalCommonPacketDataIndicatorOff - EAknSignalGprsIndicatorOff;

class CAknStatusPanePublisherData : public CBase
	{
public:
    CAknStatusPanePublisherData():iDisabledByInput( EFalse ), iDisabledByPopup( EFalse ),
        iCoeEnv( NULL ),iProcessList(5){};
    ~CAknStatusPanePublisherData(){ iProcessList.Close(); };
public:
	TAknStatusPaneStateData iData;
	TBool iDisabledByInput;
	TBool iDisabledByPopup;
	CCoeEnv* iCoeEnv;
	RArray<TUint64> iProcessList;
    };

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknStatusPaneDataPublisher::NewL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
EXPORT_C CAknStatusPaneDataPublisher* CAknStatusPaneDataPublisher::NewL()
	{
	CAknStatusPaneDataPublisher* self =
		new (ELeave) CAknStatusPaneDataPublisher();
  	CleanupStack::PushL( self );
  	self->ConstructL();
  	CleanupStack::Pop( self );
  	return self;
	}


// -----------------------------------------------------------------------------
// CAknStatusPaneDataPublisher::ConstructL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknStatusPaneDataPublisher::ConstructL()
	{
	User::LeaveIfError( RProperty::Define( KPSUidAvkonInternal,
		                                   KAknStatusPaneSystemData,
		                                   RProperty::EByteArray ) );

 	User::LeaveIfError( iProperty.Attach( KPSUidAvkonInternal,
 		                                  KAknStatusPaneSystemData ) );

	iStatusPaneStateData = new (ELeave) CAknStatusPanePublisherData();
	ClearIndicatorStates();

	iPopup = CAknIndicatorPopup::NewL();
	iPopup->SetObserverL( *this );

	// Get a handle to the P&S property containing Autolock state.
	iAutolockStateProperty.Attach( KPSUidCoreApplicationUIs,
                                   KCoreAppUIsAutolockStatus );
	}


// -----------------------------------------------------------------------------
// CAknStatusPaneDataPublisher::CAknStatusPaneDataPublisher
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CAknStatusPaneDataPublisher::CAknStatusPaneDataPublisher()
	{
  	}


// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------
//
CAknStatusPaneDataPublisher::~CAknStatusPaneDataPublisher()
	{
	iProperty.Close();
	TInt count = iIndicators.Count();
	TBool pluginDeleted = EFalse;
	for ( TInt i = 0; i < count; i++ )
	  	{
        if ( AknLayoutUtils::PenEnabled() && iIndicators[i].iPluginLoaded )
            {
            iIndicators[i].iPluginLoaded = EFalse;
            delete iIndicators[i].iPlugin;
			pluginDeleted = ETrue;
	  		}
		}

	if ( pluginDeleted )
		{
    	REComSession::FinalClose();
		}

	iIndicators.Close();
	delete iStatusPaneStateData;

	if ( iPopup )
        {
        iPopup->RemoveObserver( *this );
        }

	delete iPopup;

	iAutolockStateProperty.Close();
  	}


// -----------------------------------------------------------------------------
// CAknStatusPaneDataPublisher::PublishUpdateL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknStatusPaneDataPublisher::PublishDataL()
	{
	// check if the bubble is disabled by either popup or input
	if ( iStatusPaneStateData->iDisabledByPopup
	    || iStatusPaneStateData->iDisabledByInput )
	    {
	    iStatusPaneStateData->iData.iIndicatorState.iIncallBubbleDisabled = ETrue;
	    }
	else
	    {
	    iStatusPaneStateData->iData.iIndicatorState.iIncallBubbleDisabled = EFalse;
	    }
	TAknStatusPaneStateData::TAknStatusPaneStateDataPckg
		statusPaneStateDataPckg( iStatusPaneStateData->iData );
	iProperty.Set( statusPaneStateDataPckg );
	}


// -----------------------------------------------------------------------------
// CAknStatusPaneDataPublisher::SetForegroundSubscriberId
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknStatusPaneDataPublisher::SetForegroundSubscriberId( TInt aId )
	{
	if ( iStatusPaneStateData->iData.iForegroundSubscriberId != aId &&
	     iPopup )
	    {
	    // Hide the indicator popup if it's visible when an
	    // applications loses foreground,
	    iPopup->HidePopup();
	    }

	iStatusPaneStateData->iData.iForegroundSubscriberId = aId;
	}


// -----------------------------------------------------------------------------
// CAknStatusPaneDataPublisher::SetBatteryLevel
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknStatusPaneDataPublisher::SetBatteryLevel( TInt aLevel )
	{
	iStatusPaneStateData->iData.iBatteryState.iBatteryStrength = aLevel;
	}


// -----------------------------------------------------------------------------
// CAknStatusPaneDataPublisher::SetRecharge
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknStatusPaneDataPublisher::SetRecharge( TBool aRecharging )
	{
	iStatusPaneStateData->iData.iBatteryState.iRecharging = aRecharging;
	}


// -----------------------------------------------------------------------------
// CAknStatusPaneDataPublisher::SetSignalLevel
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknStatusPaneDataPublisher::SetSignalLevel( TInt aLevel )
	{
	iStatusPaneStateData->iData.iSignalState.iSignalStrength = aLevel;
	}


// -----------------------------------------------------------------------------
// CAknStatusPaneDataPublisher::SetSignalIcon
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknStatusPaneDataPublisher::SetSignalIcon( TInt aIcon )
	{
	TBool iconChanged( ETrue );

	if ( !( aIcon % KAknSignalLength ) ) // Signal off state
        {
        // If the off state signal type is not the same type signal as
        // the currently active one, no need to change signal.
        // This is done to filter out unnecessary signal state changes
        // sent by SysAp, since the icon for off state of all signal types
        // is the same.
        iconChanged = aIcon / KAknSignalLength ==
        	iStatusPaneStateData->iData.iSignalState.iIconState / KAknSignalLength;
        }

	if ( iconChanged )
		{
		iStatusPaneStateData->iData.iSignalState.iIconState = aIcon;
		}
	}


// -----------------------------------------------------------------------------
// CAknStatusPaneDataPublisher::SetIncallBubbleFlags
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknStatusPaneDataPublisher::SetIncallBubbleFlags( TInt aFlags )
	{
	// if the flag is ESBTouchInput, do not remove previous setting
	if ( aFlags & EAknStatusBubbleInputShow || aFlags & EAknStatusBubbleInputHide )
	    {
		TInt bBubbleDisabled =  ( ( aFlags & EAknStatusBubbleInputShow ) == EAknStatusBubbleInputShow )? ETrue : EFalse;
	    iStatusPaneStateData->iDisabledByInput = bBubbleDisabled;
	    }
	else
	    {
	    iStatusPaneStateData->iData.iIndicatorState.iIncallBubbleFlags = aFlags;
	    }
	}


// -----------------------------------------------------------------------------
// CAknStatusPaneDataPublisher::SetIncallBubbleAllowedInUsual
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknStatusPaneDataPublisher::SetIncallBubbleAllowedInUsual(
    TBool aAllowed )
	{
	iStatusPaneStateData->iData.iIndicatorState.iIncallBubbleAllowedInUsual =
	    aAllowed;
	}

// -----------------------------------------------------------------------------
// CAknStatusPaneDataPublisher::SetIncallBubbleAllowedInUsual
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknStatusPaneDataPublisher::SetIncallBubbleAllowedInUsual( TBool aAllowed, const TUint64& aClientId )
    {
    if ( aClientId == 0 )
        {
        iStatusPaneStateData->iData.iIndicatorState.iIncallBubbleAllowedInUsual = aAllowed ;
        return;
        }

    // To store the list when switch from a view disabling the bubble to the other view disabling
    // the buble,too. Currently, this list will not bu used not.
    if ( !aAllowed )
        {
        if( iStatusPaneStateData->iProcessList.Find( aClientId ) == KErrNotFound )
            {
            iStatusPaneStateData->iProcessList.Append( aClientId );
            }
        }
    else
        {
        TInt index = iStatusPaneStateData->iProcessList.Find( aClientId );
        if(  index != KErrNotFound )
            {
            iStatusPaneStateData->iProcessList.Remove( index );
            }

        // if the focused process has disabled the bubble ,ignore the bubble enable flag
        if ( !iStatusPaneStateData->iCoeEnv )
            {
            iStatusPaneStateData->iCoeEnv = CCoeEnv::Static( );
            }
        RWsSession &ws = iStatusPaneStateData->iCoeEnv->WsSession();
        TInt focusId =  ws.GetFocusWindowGroup();
        RThread focusThread;
        TThreadId threadId = 0;
        if ( KErrNone == ws.GetWindowGroupClientThreadId( focusId, threadId ) )
            {
            // if focused window has disable the bubble,ignore it
            if ( KErrNotFound != iStatusPaneStateData->iProcessList.Find( threadId.Id() ) )
                {
                aAllowed = EFalse;
                }
            }
        // reset the process list
        iStatusPaneStateData->iProcessList.Reset();
        }
    iStatusPaneStateData->iData.iIndicatorState.iIncallBubbleAllowedInUsual = aAllowed ;
    }

// -----------------------------------------------------------------------------
// CAknStatusPaneDataPublisher::SetIncallBubbleAllowedInIdle
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknStatusPaneDataPublisher::SetIncallBubbleAllowedInIdle(
    TBool aAllowed )
	{
	iStatusPaneStateData->iData.iIndicatorState.iIncallBubbleAllowedInIdle =
	    aAllowed;
	}


// -----------------------------------------------------------------------------
// CAknStatusPaneDataPublisher::SetIndicatorState
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknStatusPaneDataPublisher::SetIndicatorState( TUid aUid,
                                                              TInt aState )
	{
	TRAP_IGNORE( SetIndicatorStateL( aUid, aState ) );
	}


// -----------------------------------------------------------------------------
// CAknStatusPaneDataPublisher::SetIndicatorStateL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknStatusPaneDataPublisher::SetIndicatorStateL( TUid aUid, TInt aState )
	{
	TBool indicatorExists = EFalse;
	TBool found           = EFalse;
	TInt  count           = iIndicators.Count();
	// Whether or not an indicator is added to or removed from the popup.
	TBool resizePopup     = EFalse;

	for ( TInt i = 0; i < count; i++ )
	  	{
	  	if ( iIndicators[i].iUid == aUid.iUid )
	  		{
	  		indicatorExists = ETrue;
			iIndicators[i].iState = aState;
		    if ( aState == EAknIndicatorStateOff )
		        {
		        if ( AknLayoutUtils::PenEnabled() &&
		             iIndicators[i].iPluginLoaded )
		            {
		            if ( iPopup && iIndicators[i].iPopupItemExists )
		                {
		                iPopup->RemoveItem( aUid.iUid );
		                iIndicators[i].iPopupItemExists = EFalse;
		                resizePopup = ETrue;
		                }

                    // We don't delete the ECOM plugins here, as they don't
                    // have such a major impact on memory consumption.
                    // If the plugin would be destroyed here,
                    // REComSession::FinalClose() should also be called
                    // to avoid leaking memory, and it could cause
                    // KERN-EXEC panics with certain plugin implementations
                    // in which part of the plugin DLL is still on the
                    // call stack when the library is unloaded.
			  		}
		        }
	  		break;
	  		}
		}

	if ( !indicatorExists )
		{
		TInt widePriority   = KNoIndicatorPriority;
		TInt narrowPriority = KNoIndicatorPriority;

		TResourceReader res;

		// Check first the status indicators
		CCoeEnv::Static()->CreateResourceReaderLC(
				res,
				R_AVKON_STATUS_PANE_INDICATOR_DEFAULT );

	   	TInt indicatorCount = res.ReadInt16();
	    for ( TInt ii = 0; ii < indicatorCount; ii++ )
	        {
		    TInt foundUid = res.ReadInt16();
			if ( foundUid == aUid.iUid )
				{
				found 		   = ETrue;
		    	widePriority   = res.ReadInt16();
		    	narrowPriority = res.ReadInt16();
		        break;
				}
			else
			 	{
		    	res.ReadInt16();
		    	res.ReadInt16();
		    	HBufC* bitmapFile = res.ReadHBufCL(); // bmp filename
		    	delete bitmapFile;
		    	bitmapFile = NULL;
			    TInt numberOfStates = res.ReadInt16();  // Number of states
		    	for ( TInt i = 0; i < numberOfStates; i++ )
		        	{
		        	res.ReadInt16(); // State id
					TInt numberOfIcons = res.ReadInt16();
				    for ( TInt iii = 0; iii < numberOfIcons; iii++ )
				        {
				        for ( TInt jj = 0; jj <= 1; jj++ )
				            {
			                res.ReadInt16(); // bitmaps
			                res.ReadInt16(); // mask
				            }
		                }
		            }
		        }
	        }
		CleanupStack::PopAndDestroy();	// res

		// If not found then check the editor indicators
		if ( !indicatorExists && !found )
		    {
		    CCoeEnv::Static()->CreateResourceReaderLC( res, R_AVKON_NAVI_PANE_EDITOR_INDICATORS );

	   	    indicatorCount = res.ReadInt16();
	        for (TInt ii = 0; ii < indicatorCount; ii++)
    	        {
    		    TInt foundUid = res.ReadInt16();
    			if (foundUid == aUid.iUid)
    				{
    				found = ETrue;
    		    	widePriority = res.ReadInt16();
    		    	narrowPriority = res.ReadInt16();
    		        break;
    				}
    			else
    			 	{
    		    	res.ReadInt16();
    		    	res.ReadInt16();
    		    	HBufC* bitmapFile = res.ReadHBufCL(); // bmp filename
    		    	delete bitmapFile;
    		    	bitmapFile = NULL;
    			    TInt numberOfStates = res.ReadInt16();  // Number of states
    		    	for (TInt i = 0; i < numberOfStates; i++)
    		        	{
    		        	res.ReadInt16(); // State id
    					TInt numberOfIcons = res.ReadInt16();
    				    for (TInt ii = 0; ii < numberOfIcons; ii++)
    				        {
    				        for (TInt jj = 0; jj <= 1; jj++)
    				            {
    			                res.ReadInt16(); // bitmaps
    			                res.ReadInt16(); // mask
    				            }
    		                }
    		            }
    		        }
    	        }
    		CleanupStack::PopAndDestroy();	// res
    		}

		TAknStatusIndicator newIndicator;
		newIndicator.iUid = aUid.iUid;
		newIndicator.iNarrowPriority = narrowPriority;
		newIndicator.iWidePriority = widePriority;
		newIndicator.iState = aState;

		iIndicators.AppendL( newIndicator );
		}

	PrioritizeIndicatorsL();

	ClearIndicatorStates();

    TInt prioritizedIndicatorCount = iIndicators.Count();
    TInt publishedCount = 0;

	for ( TInt ii = 0; ii < prioritizedIndicatorCount; ii++ )
	  	{
	  	if ( publishedCount < TAknIndicatorState::EMaxVisibleIndicators )
	  		{
	  		if ( iIndicators[ii].iState != MAknIndicator::EIndicatorOff )
	  			{
			  	iStatusPaneStateData->iData.iIndicatorState.visibleIndicators[publishedCount] =
			  	    iIndicators[ii].iUid;
			  	iStatusPaneStateData->iData.iIndicatorState.visibleIndicatorStates[publishedCount] =
			  	    iIndicators[ii].iState;
	  			publishedCount++;

	  			if ( iPopup )
                    {
        		    if ( !iIndicators[ii].iPluginLoaded )
        	  		    {
        			    LoadIndicatorPlugin( iIndicators[ii] );
        	  		    }

        	  		if ( iIndicators[ii].iPlugin )
        			    {
        			    if ( !iIndicators[ii].iPopupItemExists )
        			        {
            			    TInt textType( 0 );
            			    HBufC* text = iIndicators[ii].iPlugin->TextL( iIndicators[ii].iUid, textType );
            			    if ( text )
            			        {
            			        // Ownership is transferred here.
            			        CleanupStack::PushL( text );
            			        }

            			    // If plugin does not provide the text, the we use the
            			    // default string for the indicator.
            			    if ( textType == 0 || !text )
            			        {
            			        if ( !text )
            			            {
            			            text = HBufC::NewLC( KIndicTextBufferSize );
            			            }
            			        else
            			            {
            			            text->ReAllocL( KIndicTextBufferSize );
            			            }

            			        TPtr ptr( text->Des() );
            			        GetDefaultIndicatorTextL( iIndicators[ii].iUid, ptr );

            			        if ( textType == 0 )
            			            {
            			            // Set the text type to information text
            			            // only if the type is not specified by
            			            // the plugin. This enables the plugins
            			            // to use the default string as link text.
            			            textType = CAknIndicatorPlugin::EAknIndicatorPluginInformationText;
            			            }
            			        }

                            if ( text->Length() ) // Only add item if it has description.
                                {
                                const CGulIcon* icon = NULL;
                                TRAPD( err, icon =
                                    iIndicators[ii].iPlugin->IconL(
                                        iIndicators[ii].iUid ) );

                                if ( err )
                                    {
                                    icon = NULL;
                                    }

                		    	iPopup->AddItemL( iIndicators[ii].iUid,
                		    	                  *text,
                		    	                  textType,
                		    	                  icon,
                		    	                  iIndicators[ii].iPlugin,
                		    	                  iIndicators[ii].iNarrowPriority != KNoIndicatorPriority ?
                		    	                      iIndicators[ii].iNarrowPriority :
                		    	                      iIndicators[ii].iWidePriority );

                                iIndicators[ii].iPopupItemExists = ETrue;

                                resizePopup = ETrue;
                                }

            		    	CleanupStack::PopAndDestroy( text );
            		        }
            		    else if ( aUid.iUid == iIndicators[ii].iUid )
            		        {
            		        // Indicator already exists in the popup, try to update it.
            		        iPopup->UpdatePopupIndicatorL( aUid.iUid );
            		        }
        		    	}
                    else if ( !iIndicators[ii].iPopupItemExists )
                        {
                        // Indicator doesn't have a plugin, so show the default content
                        // for it in the popup.
                        HBufC* text = HBufC::NewLC( KIndicTextBufferSize );
        			    TPtr ptr( text->Des() );
        			    GetDefaultIndicatorTextL( iIndicators[ii].iUid, ptr );

        			    if ( ptr.Length() ) // Only add item if it has description.
        			        {
            			    iPopup->AddItemL( iIndicators[ii].iUid,
            		    	                  *text,
            		    	                  CAknIndicatorPlugin::EAknIndicatorPluginInformationText,
            		    	                  NULL,
            		    	                  NULL,
            		    	                  iIndicators[ii].iNarrowPriority != KNoIndicatorPriority ?
            		    	                      iIndicators[ii].iNarrowPriority :
            		    	                      iIndicators[ii].iWidePriority );

                            iIndicators[ii].iPopupItemExists = ETrue;
                            resizePopup = ETrue;
        			        }

                        CleanupStack::PopAndDestroy( text );
                        }
        		    }
	  			}
	  		}
	  	else
	  		{
	  		break;
	  		}
		}

	if ( resizePopup )
	    {
        // Popup position needs to be reset if in current layout the popup
	    // grows upwards as indicators are added.
        if ( Layout_Meta_Data::IsLandscapeOrientation() &&
             AknLayoutUtils::CbaLocation() ==
                     AknLayoutUtils::EAknCbaLocationBottom )
            {
            SetIndicatorPopupPosition();
            }
	    }
	}


// -----------------------------------------------------------------------------
// CAknStatusPaneDataPublisher::ClearIndicatorStates
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknStatusPaneDataPublisher::ClearIndicatorStates()
	{
	Mem::Fill(&(iStatusPaneStateData->iData.iIndicatorState.visibleIndicators[0]),
		(sizeof(TInt)*TAknIndicatorState::EMaxVisibleIndicators),
		KEmpty);
	Mem::Fill(&(iStatusPaneStateData->iData.iIndicatorState.visibleIndicatorStates[0]),
		(sizeof(TInt)*TAknIndicatorState::EMaxVisibleIndicators),
		KEmpty);
	}


// ---------------------------------------------------------------------------
// CAknStatusPaneDataPublisher::SetBatteryIcon
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknStatusPaneDataPublisher::SetBatteryIcon( TInt aIcon )
    {
    iStatusPaneStateData->iData.iBatteryState.iIconState = aIcon;
    }

// ----------------------------------------------------------------------------
// CAknStatusPaneDataPublisher::SetIndicatorPopupPosition
// (other items were commented in the header
// ----------------------------------------------------------------------------
EXPORT_C void CAknStatusPaneDataPublisher::SetIndicatorPopupPosition()
    {
    // Position is read from the LAF data.
    // Application window should be the parent rectangle, but
    // in nHD landscape it's not correct.
    // In that case the parent has to be adjusted somewhat.
    // Also, the layout data doesn't currently mirror the
    // popup_uni_indicator_window, so it must be done here.
    TRect applicationWindow;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EApplicationWindow,
                                       applicationWindow );

    TRect mainPane;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane,
                                       mainPane );

    TBool layoutMirrored( AknLayoutUtils::LayoutMirrored() );
    TBool isLandscape( Layout_Meta_Data::IsLandscapeOrientation() );

    // This defines if the popup should be located on the bottom of the screen
    // and grown upwards when content is added.
    TBool positionIsBottomLeft( EFalse );

    if ( isLandscape && AknStatuspaneUtils::HDLayoutActive() )
        {
        // In nHD landscape A&H layout the right pane area
        // is not mirrored so this is sufficient.
        applicationWindow.iBr.iX = mainPane.iBr.iX;
        }
    
    TInt statusPaneLayoutId = AknStatuspaneUtils::CurrentStatusPaneLayoutResId();
    TAknLayoutRect layoutRect;
    if ( isLandscape &&
         ( statusPaneLayoutId == R_AVKON_STATUS_PANE_LAYOUT_USUAL_FLAT ||
           statusPaneLayoutId == R_AVKON_STATUS_PANE_LAYOUT_IDLE_FLAT ) )
        {
        layoutRect.LayoutRect(
            applicationWindow,
            AknLayoutScalable_Avkon::popup_uni_indicator_window( 6 ) );
        positionIsBottomLeft = ETrue;
        }
    else if ( statusPaneLayoutId == R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL ||
              statusPaneLayoutId == R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE )
        {
        layoutRect.LayoutRect(
                applicationWindow,
                AknLayoutScalable_Avkon::popup_uni_indicator_window( 6 ) );
        }
    else if ( statusPaneLayoutId == R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL_FLAT ||
              statusPaneLayoutId == R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT ||
              statusPaneLayoutId == R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL_FLAT_NO_SOFTKEYS ||
              statusPaneLayoutId == R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT_NO_SOFTKEYS )
        {
        layoutRect.LayoutRect(
                applicationWindow,
                AknLayoutScalable_Avkon::popup_uni_indicator_window( 5 ) );
        }
    else
        {
        layoutRect.LayoutRect(
                applicationWindow,
                AknLayoutScalable_Avkon::popup_uni_indicator_window( 0 ) );
        
        }
    TRect popupRect( layoutRect.Rect() );

    TInt popupWidth( popupRect.Width() );
    TInt xyOffset( popupRect.iTl.iY );
    TInt xPoint( 0 );

    // Preview popup's size contains also the frames, so the
    // difference between that size and the content's size
    // has to be taken into account in the positioning.
    // Frame width is read from the LAF because preview popup's
    // size may not be correct at this point.
    TAknWindowLineLayout previewPopupSideFrameLayout(
        AknLayoutScalable_Avkon::bg_popup_preview_window_pane_g9().LayoutLine() );
    TInt frameOffset = previewPopupSideFrameLayout.iW;

    if ( isLandscape )
        {
        if ( !layoutMirrored )
            {
            xPoint = popupRect.iBr.iX + frameOffset;
            }
        else
            {
            xPoint = applicationWindow.iBr.iX - popupRect.iTl.iX + frameOffset;
            }
        }
    else
        {
        if ( !layoutMirrored )
            {
            xPoint = applicationWindow.iBr.iX - xyOffset;
            }
        else
            {
            xPoint = xyOffset + popupWidth + frameOffset * 2;
            }
        }

    if ( positionIsBottomLeft )
        {
        iPopup->SetBottomPosition( TPoint( xPoint, popupRect.iBr.iY ) );
        }
    else
        {
        iPopup->SetPosition( TPoint( xPoint, xyOffset ) );
        }
    }
// -----------------------------------------------------------------------------
// From class MAknPreviewPopUpObserver.
// CAknStatusPaneDataPublisher::HandlePreviewPopUpEventL
// -----------------------------------------------------------------------------
//
void CAknStatusPaneDataPublisher::HandlePreviewPopUpEventL(
    CAknPreviewPopUpController* aController,
    TPreviewPopUpEvent aEvent )
    {
    if ( AknGlobalPopupPriorityController::GlobalPopupsAllowed() &&
            iPopup && aController == iPopup->Controller() )
        {
        TInt incallBubbleFlags =
            iStatusPaneStateData->iData.iIndicatorState.iIncallBubbleFlags;

        TBool incallBubbleDisabled =
            iStatusPaneStateData->iData.iIndicatorState.iIncallBubbleDisabled;

        switch ( aEvent )
            {
            case EPreviewPopUpShown:
                if ( ( incallBubbleFlags & EAknStatusBubbleVisible ) &&
                     !incallBubbleDisabled )
                    {
                    // Hide the incall status bubble if
                    // it's visible when indicator popup is shown.
                    iStatusPaneStateData->iDisabledByPopup = ETrue;
                    PublishDataL();
                    }
                iPopup->SetContentVisible( ETrue );
                break;

            case EPreviewPopUpHidden:
                if ( incallBubbleDisabled )
                    {
                    iStatusPaneStateData->iDisabledByPopup = EFalse;
                    PublishDataL();
                    }
                iPopup->SetContentVisible( EFalse );
                break;

            default:
                break;
            }
        }
    }


// -----------------------------------------------------------------------------
// CAknStatusPaneDataPublisher::PrioritizeIndicatorsL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknStatusPaneDataPublisher::PrioritizeIndicatorsL()
    {
    TInt count = iIndicators.Count();
    if ( count < 2 )
        {
        // Nothing to prioritize.
        return;
        }

    // Assume that narrow/wide priorities are the same.
    TBool sortByWidePriority = AknStatuspaneUtils::IdleLayoutActive();

    TAknStatusIndicator temp;
    for ( TInt ii = 1; ii < count; ii++ )
        {
        temp = iIndicators[ii];
        TInt tempPriority = temp.iNarrowPriority;

        if ( tempPriority == KNoIndicatorPriority )
            {
        	tempPriority = temp.iWidePriority;
            }

        if ( tempPriority >= 0 )
            {
            for ( TInt jj = 0; jj <= ii; jj++ )
                {
                TInt indicatorPriority = iIndicators[jj].iNarrowPriority;
		        if ( indicatorPriority == KNoIndicatorPriority )
		            {
        			indicatorPriority = iIndicators[jj].iWidePriority;
		            }

                if ( tempPriority < indicatorPriority )
                    {
                    iIndicators.Remove( ii );
                    iIndicators.InsertL( temp, jj );
                    break;
                    }
                else if ( jj == ( ii - 1 ) )
                    {
                    break;
                    }
                }
            }
        }
    }


// -----------------------------------------------------------------------------
// CAknStatusPaneDataPublisher::HandleIndicatorTapL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknStatusPaneDataPublisher::HandleIndicatorTapL(
    TUid /*aIndicatorUid*/ )
    {
    if ( AknLayoutUtils::PenEnabled() && iPopup )
        {
        // Do not display the universal indicator popup
        // if device lock is active.
        TInt autolockState;
        TInt err = iAutolockStateProperty.Get( autolockState );

        if ( err != KErrNone || autolockState <= EAutolockOff )
            {
            // This is called to ensure correct information on the popup
            // and to lessen the need for indicator plugins to have
            // change listeners for indicator data.
            iPopup->UpdateAllPopupIndicatorsL();

            iPopup->ShowPopup();
            }
        }
    }


// -----------------------------------------------------------------------------
// CAknStatusPaneDataPublisher::LoadIndicatorPlugin
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknStatusPaneDataPublisher::LoadIndicatorPlugin(
    TAknStatusIndicator& aIndicator )
    {
    if ( AknLayoutUtils::PenEnabled() )
        {
        CAknIndicatorPlugin* indicatorPlugin = NULL;
        TUid pluginUid = { KErrNotFound };

        switch ( aIndicator.iUid )
            {
            // Status pane's indicators
            case EAknIndicatorIrActive:
                {
                pluginUid.iUid = KImplUIDIRIndicatorsPlugin;
                break;
                }
            case EAknIndicatorEnvelope:
            case EAknIndicatorEmailMessage:
            case EAknIndicatorDataMessage:
            case EAknIndicatorFaxMessage:
            case EAknIndicatorOtherMessage:
            case EAknIndicatorOutbox:
            case EAknIndicatorVoiceMailWaiting:
            case EAknIndicatorVoiceMailWaitingOnLine1:
            case EAknIndicatorVoiceMailWaitingOnLine2:
            case EAknIndicatorVoiceMailWaitingOnBothLines:
            case EAknIndicatorRemoteMailboxEmailMessage:
                {
                pluginUid.iUid = KImplUIDMessagingIndicatorsPlugin;
                break;
                }
            case EAknIndicatorBluetooth:
            case EAknIndicatorBluetoothVisible:
            case EAknIndicatorBluetoothModuleOn:
            case EAknIndicatorBluetoothModuleOnVisible:
                {
                pluginUid.iUid = KImplUIDBTIndicatorsPlugin;
                break;
                }
            case EAknIndicatorMissedCalls:
                {
                pluginUid.iUid = KImplUIDCallRelatedIndicatorsPlugin;
                break;
                }
            case EAknIndicatorAlarmClock:
                {
                pluginUid.iUid = KImplUIDClockIndicatorsPlugin;
                break;
                }
            case EAknIndicatorStopWatch:
                {
                pluginUid.iUid = KImplUIDStopwatchIndicatorsPlugin;
                break;
                }
            case EAknIndicatorUSBConnection:
                {
                pluginUid.iUid = KImplUIDUSBIndicatorsPlugin;
                break;
                }
            case EAknIndicatorLocation:
            case EAknIndicatorLocationOn:
            case EAknIndicatorLocationOff:
            case EAknIndicatorGPS:
                {
                pluginUid.iUid = KImplUIDLocationIndicatorsPlugin;
                break;
                }
            case EAknIndicatorInstantMessage:
                {
                pluginUid.iUid = KImplUIDInstantMessageIndicatorsPlugin;
                break;
                }

            case EAknIndicatorPoC:
            case EAknIndicatorPoCMissed:
            case EAknIndicatorPoCDnD:
                {
                pluginUid.iUid = KImplUIDPoCIndicatorsPlugin;
                break;
                }

            case EAknIndicatorWlanAvailable:
            case EAknIndicatorWlanActive:
            case EAknIndicatorWlanActiveSecure:
                {
                pluginUid.iUid = KImplUIDWlanIndicatorPlugin;
                break;
                }
            case EAknIndicatorMissedCalendarAlarm:
                {
                pluginUid.iUid = KImplUIDMissedCalendarAlarmIndicatorPlugin;
                break;
                }
            case EAknIndicatorFMTxSending:
            case EAknIndicatorFMTxEnabled:	
        	      {
		            pluginUid.iUid = KImplUIDFMTxIndicatorPlugin;
	              break;
      		      }
      		  case EAknIndicatorMecoServiceTab:
                {
                pluginUid.iUid = KImplUIDMecoServiceTabIndicatorPlugin;
                break;
                }
            case EAknIndicatorUSBMemActive:    
            case EAknIndicatorUSBMemConnected:
                {
                pluginUid.iUid = KImplUIDUSBMEMIndicatorsPlugin;
                break;
                }
             // currently uncategorized:
            case EAknIndicatorKeyguard:
            case EAknIndicatorHomeZone:
            case EAknIndicatorSecuredConnection:
            case EAknIndicatorHeadset:
            case EAknIndicatorLoopset:
            case EAknIndicatorIHFActive:
            case EAknIndicatorTTY:
            case EAknIndicatorHeadsetUnavailable:
            case EAknIndicatorRoaming:
            case EAknIndicatorCarkit:
            case EAknIndicatorTvOut:
            case EAknIndicatorHDMI:
            case EAknIndicatorMobileTV:
            case EAknIndicatorTARM:
            case EAknIndicatorTARMModuleOn:
            case EAknIndicatorVideoSharing:
            case EAknIndicatorSynchronization:
            case EAknIndicatorVoIP:
            case EAknIndicatorAllCallsForwarded:
            case EAknIndicatorCallsForwardedOnLine1:
            case EAknIndicatorCallsForwardedOnLine2:
            case EAknIndicatorCallsForwardedOnBothLines:
            case EAknIndicatorCallsForwardedToVoiceMailbox:
            case EAknIndicatorSelectedLine:
            default:
                {
                break;
                }
            }

        TRAPD( err, indicatorPlugin = CAknIndicatorPlugin::NewL( pluginUid ) );
        aIndicator.iPluginLoaded = ETrue;
        if ( err == KErrNone )
            {
            aIndicator.iPlugin = indicatorPlugin;
            }
        }
    }


// -----------------------------------------------------------------------------
// CAknStatusPaneDataPublisher::GetDefaultIndicatorText
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknStatusPaneDataPublisher::GetDefaultIndicatorTextL( TInt aUid,
                                                            TDes& aText )
    {
    CCoeEnv* env = CCoeEnv::Static();

    TResourceReader reader;
    env->CreateResourceReaderLC( reader, R_AVKON_INDICATOR_POPUP_DEFAULTS );

    TInt itemCount( reader.ReadInt16() );
    TInt uid( KErrNotFound );

    for ( TInt i = 0; i < itemCount; i++ )
        {
        uid  = reader.ReadInt16();

        if ( uid == aUid )
            {
            aText = reader.ReadTPtrC16();
            break;
            }
        else
            {
            reader.ReadTPtrC16(); // text
            reader.ReadInt32();   // extension
            }
        }

    CleanupStack::PopAndDestroy(); // reader
    }
