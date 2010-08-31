/*
* Copyright (c) 2002-2005 Nokia Corporation and/or its subsidiary(-ies).
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


// INCLUDE FILES
#include <eikbtgpc.h>
#include <avkon.rsg>
#include <avkon.hrh>
#include <eikenv.h>
#include <eikmenub.h>
#include <eikcolib.h>
#include <eikapp.h>
#include <aknclearer.h>
#include <AknUtils.h>
#include <akntoolbar.h>
#include "aknview.h"
#include "aknshut.h"
#include "aknenv.h"
#include "AknPanic.h"
#ifdef RD_SPLIT_VIEW
#include "AknViewNavigator.h"
#include <aknsutils.h>
#include <aknsdrawutils.h>
#include <AknLayoutScalable_Avkon.cdl.h>
#include <LayoutMetaData.cdl.h>
#endif // RD_SPLIT_VIEW
#include "aknViewAppUi.h"

// CONSTANTS
const TInt KAknAppUiViewsGranularity = 1;
const TInt KAknViewAsyncPriority = EActivePriorityRedrawEvents + 10;
#ifdef RD_SPLIT_VIEW
const TInt KAknSplitViewSize = 2;

// MODULE DATA STRUCTURES
enum TAknViewAppUiFlags
    {
    EAknViewAppUiButton1DownInRight = 0x00000001,
    EAknViewAppUiButton1DownInLeft  = 0x00000002,
    EAknViewAppUiFromSplitToSingle  = 0x00000004,
    EAknViewAppUiFromSingleToSplit  = 0x00000008,
    };
#endif // RD_SPLIT_VIEW

/**
*  CAknViewAppUi extension class.
*
*  @lib avkon.lib
*/
NONSHARABLE_CLASS(CAknViewAppUiExtension) : public CBase
    {
    public:
		/**
		* Two-phased constructor.
		*/
        static CAknViewAppUiExtension* NewL();

        /**
        * Destructor.
        */
        ~CAknViewAppUiExtension();
        
    private:
		/**
		* C++ constructor.
		*/
        CAknViewAppUiExtension();

		/**
		* Symbian 2nd-stage constructor.
		*/
        void ConstructL();

    public:
        RPointerArray<CAknView> iActiveViews;
#ifdef RD_SPLIT_VIEW
        RArray<CAknViewAppUi::TAknSplitViewContainer> iSplitViews;
        CAknViewNavigator* iNavigator;
        TInt iFlags;
#endif // RD_SPLIT_VIEW
        TBool iUseDefaultScreenClearer;
    };

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknViewAppUiExtension::CAknViewAppUiExtension
// C++ constructor.
// -----------------------------------------------------------------------------
//
CAknViewAppUiExtension::CAknViewAppUiExtension()
    {
    iUseDefaultScreenClearer = ETrue; // by default clear the screen automatically
    }

// -----------------------------------------------------------------------------
// CAknViewAppUiExtension::~CAknViewAppUiExtension
// Destructor.
// -----------------------------------------------------------------------------
//
CAknViewAppUiExtension::~CAknViewAppUiExtension()
    {
    iActiveViews.Close();
#ifdef RD_SPLIT_VIEW
    delete iNavigator;
    iSplitViews.Close();
#endif // RD_SPLIT_VIEW
    }

// -----------------------------------------------------------------------------
// CAknViewAppUiExtension::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CAknViewAppUiExtension* CAknViewAppUiExtension::NewL()
    {
    CAknViewAppUiExtension* ext = new ( ELeave ) CAknViewAppUiExtension;
    CleanupStack::PushL( ext );
    ext->ConstructL();
    CleanupStack::Pop();
    return ext;
    }

// -----------------------------------------------------------------------------
// CAknViewAppUiExtension::NewL
// Symbian 2nd-stage constructor.
// -----------------------------------------------------------------------------
//
void CAknViewAppUiExtension::ConstructL()
    {
    }
    
// -----------------------------------------------------------------------------
// CAknViewAppUi::TAknSplitViewContainer::IsPartOf
// Tests if a given view is part of the split view.
// -----------------------------------------------------------------------------
//
#ifdef RD_SPLIT_VIEW
TBool CAknViewAppUi::TAknSplitViewContainer::IsPartOf( const TUid aViewId )
    {
    if ( aViewId == iViewIds[0] || aViewId == iViewIds[1] )
        {
        return ETrue;
        }
        
    return EFalse;
    }
#endif // RD_SPLIT_VIEW
    
// -----------------------------------------------------------------------------
// CAknViewAppUi::CViewActivationItem::NewLC
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CAknViewAppUi::CViewActivationItem* CAknViewAppUi::CViewActivationItem::NewLC( CAknView* aNewView, TUid aCustomMessageId, const TDesC8& aCustomMessage, const TVwsViewId& aPrevViewId )
	{
	CViewActivationItem* self = new ( ELeave ) CViewActivationItem( aNewView, aCustomMessageId, aPrevViewId );
	CleanupStack::PushL( self );
	self->ConstructL( aCustomMessage );
	return self;
	}

// -----------------------------------------------------------------------------
// CAknViewAppUi::CViewActivationItem::~CViewActivationItem
// Destructor.
// -----------------------------------------------------------------------------
//
CAknViewAppUi::CViewActivationItem::~CViewActivationItem()
	{
	delete iCustomMessage;
	}

// -----------------------------------------------------------------------------
// CAknViewAppUi::CViewActivationItem::CViewActivationItem
// C++ default constructor.
// -----------------------------------------------------------------------------
//
CAknViewAppUi::CViewActivationItem::CViewActivationItem( CAknView* aNewView, TUid aCustomMessageId, const TVwsViewId& aPrevViewId )
: iNewView( aNewView ), iCustomMessageId( aCustomMessageId ), iPrevViewId( aPrevViewId )
	{
	}

// -----------------------------------------------------------------------------
// CAknViewAppUi::CViewActivationItem::ConstructL
// Symbian 2nd phase constructor.
// -----------------------------------------------------------------------------
//
void CAknViewAppUi::CViewActivationItem::ConstructL( const TDesC8& aCustomMessage )
	{
	iCustomMessage = aCustomMessage.AllocL();
	}

// -----------------------------------------------------------------------------
// CAknViewAppUi::BaseConstructL
// Second-phase base class constructor.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknViewAppUi::BaseConstructL( TInt aAppUiFlags )
	{
	CAknAppUi::BaseConstructL( aAppUiFlags );

	iViews = new ( ELeave ) CAknViews( KAknAppUiViewsGranularity );
	iActivationQueue = new ( ELeave ) CAknViewActivationQueue( KAknAppUiViewsGranularity );
	iActivationTick = CIdle::NewL( KAknViewAsyncPriority );
	iShutter = CAknViewShutter::NewL( *iEikonEnv, this );
	
	// Might be already constructed
    if ( !iExtension )
        {
        iExtension = CAknViewAppUiExtension::NewL();
        }
	    
#ifdef RD_SPLIT_VIEW
	iExtension->iNavigator = new ( ELeave ) CAknViewNavigator( this );
	AddToStackL( iExtension->iNavigator, ECoeStackPriorityDefault - 1, ECoeStackFlagRefusesFocus );
#endif // RD_SPLIT_VIEW
	
	if ( iEikonEnv->RootWin().OrdinalPosition() == 0 && // only clear the window for foreground apps
	     iExtension->iUseDefaultScreenClearer )
		{
		iClearer = CAknLocalScreenClearer::NewL( ETrue );
		}
	}

// -----------------------------------------------------------------------------
// CAknViewAppUi::~CAknViewAppUi
// Destructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknViewAppUi::~CAknViewAppUi()
	{
#ifdef RD_SPLIT_VIEW
	if (iExtension && iExtension->iNavigator )
	    RemoveFromStack( iExtension->iNavigator );
#endif // RD_SPLIT_VIEW
	
    // Hide application toolbar to prevent it from showing 
    // after views are deleted
    if ( CAknAppUi::CurrentFixedToolbar() )
        {
        CAknAppUi::CurrentFixedToolbar()->SetToolbarVisibility( EFalse );   
        }

	delete iClearer;
	delete iShutter;
	delete iActivationTick;
	
	if ( iActivationQueue )
		{
		iActivationQueue->ResetAndDestroy();
		delete iActivationQueue;
		}

	if (iExtension)
	    for ( TInt i = 0; i < iExtension->iActiveViews.Count(); i++ )
	        {
    		iExtension->iActiveViews[i]->AknViewDeactivated();
	        }

	if ( iViews )
		{
		TInt count( iViews->Count() );
		
		for ( TInt i = 0; i < count; i++ )
			{
			CCoeAppUi::DeregisterView( *iViews->At( i ) );
			}
			
		iViews->ResetAndDestroy();
		}
		
	delete iViews;
	delete iExtension;
	}

// -----------------------------------------------------------------------------
// CAknViewAppUi::AddViewL
// Registers a new view to the view server.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknViewAppUi::AddViewL( CAknView* aView )
	{
	// this is here to assert that BaseConstructL has been called properly.
	Extension();

	CCoeAppUi::RegisterViewL( *aView );
	iViews->AppendL( aView );
	}

// -----------------------------------------------------------------------------
// CAknViewAppUi::RemoveView
// Deregisters a new view from the view server.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknViewAppUi::RemoveView( TUid aViewId )
	{
	const TInt count( iViews->Count() );
	
	for ( TInt i = 0; i < count; ++i )
		{
		CAknView* view( iViews->At( i ) );
		
		if ( view->Id() == aViewId )
			{
			iViews->Delete( i );
			CCoeAppUi::DeregisterView( *view );
			delete view;
			return;
			}
		}
	}

// -----------------------------------------------------------------------------
// CAknViewAppUi::View
// Returns a view that has the given UID.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknView* CAknViewAppUi::View( TUid aView ) const
	{
	if ( iViews )
	    {
    	const TInt count( iViews->Count() );
	
    	for ( TInt i = 0; i < count; ++i )
	    	{
    		CAknView* view( iViews->At( i ) );
		
	    	if ( view->Id() == aView )
		        {
			    return view;
    		    }
    		}
	    }
	return NULL;
	}

// -----------------------------------------------------------------------------
// CAknViewAppUi::ProcessCommandL
// Processes a command.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknViewAppUi::ProcessCommandL( TInt aCommand )
	{
	MEikAppUiFactory* appUiFactory( iEikonEnv->AppUiFactory() );
	ASSERT( appUiFactory );
	
	if ( appUiFactory->Popup() )
	    {
	    ClosePopup();
	    }
    else if ( iView && iView->MenuBar() )
        {
        iView->MenuBar()->StopDisplayingMenuBar();
        }
    else if ( appUiFactory->MenuBar() )
        {
        StopDisplayingMenuBar();
        }
	
	if ( aCommand == EAknSoftkeyOptions )
		{
		if ( iView && iView->MenuBar() )
		    {
			iView->MenuBar()->TryDisplayMenuBarL();
		    }
		else if ( appUiFactory->MenuBar() )
		    {
			appUiFactory->MenuBar()->TryDisplayMenuBarL();
		    }
		    
		return;
		}
	if ( aCommand == EAknSoftkeyContextOptions )
		{
		if ( iView && iView->MenuBar() )
		    {
			iView->MenuBar()->TryDisplayContextMenuBarL();
		    }
		else if ( appUiFactory->MenuBar() )
		    {
			appUiFactory->MenuBar()->TryDisplayContextMenuBarL();
		    }
		    
		return;
		}
		
	if ( aCommand == EAknCmdExit )
		{
		CAknEnv::RunAppShutter();
		return;
		}
		
 	if ( iView )
 	    {
		iView->ProcessCommandL( aCommand );
 	    }
 	    
	if ( aCommand != EEikCmdCanceled )
	    {
	    HandleCommandL( aCommand );
	    }
	}

// -----------------------------------------------------------------------------
// CAknViewAppUi::ActivateLocalViewL
// Activates a local view.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknViewAppUi::ActivateLocalViewL( TUid aViewId )
	{
#ifdef RD_SPLIT_VIEW
    ActivateLocalViewL( aViewId, KNullUid, KNullDesC8 );
#else
	ActivateViewL( TVwsViewId( Application()->AppDllUid(), aViewId ) );
#endif // RD_SPLIT_VIEW	    
	}

// -----------------------------------------------------------------------------
// CAknViewAppUi::ActivateLocalViewL
// Activates a local view.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknViewAppUi::ActivateLocalViewL( TUid aViewId, TUid aCustomMessageId, const TDesC8& aCustomMessage )
	{
	ActivateViewL( TVwsViewId( Application()->AppDllUid(), aViewId ), aCustomMessageId, aCustomMessage );

#ifdef RD_SPLIT_VIEW
    const TAknSplitViewContainer* splitView( SplitView( aViewId ) );
	if ( splitView )
	    {
        CAknEnv::Static()->SplitViewActive( ETrue );
        
        if ( !ViewShown( splitView->iViewIds[0] ) || !ViewShown( splitView->iViewIds[1] ) )
            {
            iExtension->iFlags |= EAknViewAppUiFromSingleToSplit;
            }
	    }
#endif // RD_SPLIT_VIEW	    
	}

// -----------------------------------------------------------------------------
// CAknViewAppUi::HandleStatusPaneSizeChange
// Called by the framework when status pane's position or size changes.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknViewAppUi::HandleStatusPaneSizeChange()
	{
	if (iClearer)
		{
		TRAP_IGNORE(iClearer->HandleStatusPaneSizeChangeL());
		}
	
	const TInt count( iViews->Count() );
	
	for ( TInt i = 0; i < count; ++i )
		{
		iViews->At( i )->HandleStatusPaneSizeChange();
		}
	}

// -----------------------------------------------------------------------------
// CAknViewAppUi::ViewActivatedL
// Adds a view to the activation queue. 
// -----------------------------------------------------------------------------
//
void CAknViewAppUi::ViewActivatedL( CAknView* aView, const TVwsViewId& aPrevViewId, TUid aCustomMessageId, const TDesC8& aCustomMessage )
	{
	CViewActivationItem* activation( CViewActivationItem::NewLC( aView, aCustomMessageId, aCustomMessage, aPrevViewId ) );
	iActivationQueue->AppendL( activation );
	CleanupStack::Pop(); // activation
	QueueActivationTick();
	}

// -----------------------------------------------------------------------------
// CAknViewAppUi::ViewDeactivated
// An empty implementation.
// -----------------------------------------------------------------------------
//
void CAknViewAppUi::ViewDeactivated( CAknView* /*aView*/ )
	{
	// SERIES60 apps always have at least one active view.
	}

// -----------------------------------------------------------------------------
// CAknViewAppUi::HandleForegroundEventL
// Called by the framework when view's foreground status changes.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknViewAppUi::HandleForegroundEventL( TBool aForeground )
	{
	CAknAppUi::HandleForegroundEventL( aForeground );
	
	if ( iView )
	    {
		iView->ProcessForegroundEventL( aForeground );
	    }
	}

// -----------------------------------------------------------------------------
// CAknViewAppUi::ActivationCallBack
// Callback function of idle timer iActivationTick.
// -----------------------------------------------------------------------------
//
TInt CAknViewAppUi::ActivationCallBack( TAny* aThis )
	{
    static_cast<CAknViewAppUi*>( aThis )->ActivationTick();
    
	return 0;
	}

// -----------------------------------------------------------------------------
// CAknViewAppUi::ActivationTick
// Handles asynchronous view activation / deactivation.
// -----------------------------------------------------------------------------
//
void CAknViewAppUi::ActivationTick()
	{
	CViewActivationItem* item( iActivationQueue->At( 0 ) );
#ifndef RD_SPLIT_VIEW	
	iActivationQueue->Delete( 0 );
#endif // !RD_SPLIT_VIEW
	
	TBool exit( EFalse );
	
#ifdef RD_SPLIT_VIEW
	if ( !( iExtension->iFlags & EAknViewAppUiFromSplitToSingle ) &&
	     !( iExtension->iFlags & EAknViewAppUiFromSingleToSplit ) &&
	     item->iNewView == iView &&
	     item->iCustomMessageId == KNullUid &&
	     item->iCustomMessage->Length() == 0 )
	    {
	    // Still in the same app view with no new message.
	    // No need for view switch.
	    }
	else
	    {
		TInt error( KErrNone );

        const TAknSplitViewContainer* splitView( SplitView( item->iNewView->Id() ) );
        
        if ( splitView )
            {
            TRAP( error, ActivateSplitViewL( item ) );
            }
        else if ( iExtension->iFlags & EAknViewAppUiFromSplitToSingle )
            {
            CAknEnv::Static()->SplitViewActive( EFalse );
            item->iNewView->HandleViewRectChange();
            item->iNewView->Redraw();
            }
        else
            {
            TRAP( error, item->iNewView->AknViewActivatedL( item->iPrevViewId, 
                                                            item->iCustomMessageId, 
                                                            *item->iCustomMessage ) );
            CAknEnv::Static()->SplitViewActive( EFalse );                                                            
            }
            
		iExtension->iFlags &= ~( EAknViewAppUiFromSplitToSingle | EAknViewAppUiFromSingleToSplit );

        if ( error == KErrNone )
            {
            if ( iView )
                {
                // new view successfully activated, shut down the old one(s)
                for ( TInt i = 0; i < iExtension->iActiveViews.Count(); i++ )
                    {
                    if ( splitView )
                        {
                        if ( iExtension->iSplitViews[i].IsPartOf( iExtension->iActiveViews[i]->Id() ) )                      
                            {
                            iExtension->iActiveViews.Remove( i );
                            --i;
                            }
                        }
                    else
                        {
                        if ( iExtension->iActiveViews[i] == item->iNewView )
                            {
                            iExtension->iActiveViews.Remove( i );
                            --i;
                            }
                        }
                    }
                    
                iShutter->Start( iExtension->iActiveViews );
                
                if ( iExtension->iActiveViews.Count() == 0 )
                    {
                    iView->StopDisplayingMenuBar();
                    }
                }

            iExtension->iActiveViews.Reset();
            
            // Number of views is always smaller than already reserved array 
            // (default granularity is 8) -> no memory allocation failures.
            if ( splitView )
                {
                iExtension->iActiveViews.Append( View( splitView->iViewIds[0] ) );
                iExtension->iActiveViews.Append( View( splitView->iViewIds[1] ) );
                }
            else
                {
                iExtension->iActiveViews.Append( item->iNewView );
                }

            iView = item->iNewView;
            }
        else
            {
            // deactivate failed view(s) immediately
            if ( splitView )
                {
                CAknEnv::Static()->SplitViewActive( EFalse );

                for ( TInt i = 0; i < KAknSplitViewSize; i++ )
                    {
                      if ( splitView->iFailed[i] )
                        {
                        CAknView* view( View( splitView->iViewIds[i] ) );

                        view->AknViewDeactivated();

                        TInt position( iExtension->iActiveViews.Find( view ) );

                        if ( position != KErrNotFound )
                            {
                            iExtension->iActiveViews.Remove( position );
                            }
                        }
                    }
                }
            else
                {
                item->iNewView->AknViewDeactivated();

                TInt position( iExtension->iActiveViews.Find( item->iNewView ) );
                        
                if ( position != KErrNotFound )
                    {
                    iExtension->iActiveViews.Remove( position );
                    }
                }
            
            // report error to the user
            iEikonEnv->HandleError( error );
            
            // recover the app as best possible
            if ( !iView )
                {
                // no view to fall back to -> exit
                exit = ETrue;
                }
            else if ( iView == item->iNewView )
                {
                // view reactivation failed -> forget current and try default
                iView = NULL;
                TVwsViewId viewId;
                
                if ( GetDefaultViewId( viewId ) == KErrNone )
                    {
                    TRAP_IGNORE( ActivateViewL( viewId ) );
                    }
                else
                    {
                    exit = ETrue;
                    }
                }
            else
                {
                // tell the view server that we're staying here
                TRAP_IGNORE( ActivateLocalViewL( iView->Id() ) );
                }
            
            // activation has failed, go back to the last view if in a different app
            if ( item->iPrevViewId.iAppUid != Application()->AppDllUid() )
                {
                TRAP_IGNORE( ActivateViewL( item->iPrevViewId ) );
                }
	        }
	    }
#else
	if ( item->iNewView == iView && 
	     item->iCustomMessageId == KNullUid && 
	     item->iCustomMessage->Length() == 0 )
		{
		// Still on the same app view, with no new message. 
		// No need for a app view switch.
		}
	else
		{
        if ( iView && CurrentPopupToolbar() )
            {
            iView->SaveToolbarStatus(CurrentPopupToolbar()->IsShown(), !CurrentPopupToolbar()->IsNonFocusing() ); 
            }

		TRAPD( error, item->iNewView->AknViewActivatedL( item->iPrevViewId, 
		                                                 item->iCustomMessageId, 
		                                                 *item->iCustomMessage ) );

		if ( error == KErrNone )
			{
			// New view sucessfully activated. Shut down the old one.
			if ( iView )
				{
				if ( iView != item->iNewView )	// Is this really a new view?
					{
					iExtension->iActiveViews.Reset();
					iExtension->iActiveViews.Append( iView );
					iShutter->Start( iExtension->iActiveViews ); // Deactivate iView
					}
				else
					{
					iExtension->iActiveViews.Reset();
					iShutter->Start( iExtension->iActiveViews ); // Tidy up iView if it's not new
					iView->StopDisplayingMenuBar();
					}
				}
				
            iExtension->iActiveViews.Reset();
            iExtension->iActiveViews.Append( item->iNewView );
			iView = item->iNewView;
			}
		else
			{
			// deactivate failed view immediately
			item->iNewView->AknViewDeactivated();
			
			// report the error to the user
			iEikonEnv->HandleError( error );

			// recover the app as best possible
			if ( !iView )
				{
				// no view to fall back to - exit
				exit = ETrue;
				}
			else if ( iView == item->iNewView )
				{
				// Reactivation of view failed - forget current and try default view
				iView = NULL;
				TVwsViewId viewId;
				
				if ( GetDefaultViewId( viewId ) == KErrNone )
					{
					TRAP_IGNORE( ActivateViewL( viewId ) );
					}
				else
					{
					// no default view - exit
					exit = ETrue;
					}
				}
			else
				{
				// Tell view server that we're staying here
				TRAP_IGNORE( ActivateLocalViewL( iView->Id() ) );
				}
			
			// This activation has failed, so go back to the last view if in a different app.
			if ( item->iPrevViewId.iAppUid != Application()->AppDllUid() )
				{
				TRAP_IGNORE( ActivateViewL( item->iPrevViewId ) );
				}
			}
		}
#endif // RD_SPLIT_VIEW
	    
	delete iClearer;
	iClearer = NULL;
	
#ifdef RD_SPLIT_VIEW	
	iActivationQueue->Delete( 0 );
#endif // RD_SPLIT_VIEW
	delete item;
	
	if ( exit )
	    {
	    TRAP_IGNORE( HandleForegroundEventL( EFalse ) );
	    RunAppShutter();
	    }
	else
	    {
	    QueueActivationTick();
	    }
	}

// -----------------------------------------------------------------------------
// CAknViewAppUi::QueueActivationTick
// Starts the activation idle timer.
// -----------------------------------------------------------------------------
//
void CAknViewAppUi::QueueActivationTick()
	{
	if ( iActivationQueue->Count() && !iActivationTick->IsActive() )
	    {
		iActivationTick->Start( TCallBack( ActivationCallBack, this ) );
	    }
	}

// -----------------------------------------------------------------------------
// CAknViewAppUi::StopDisplayingMenuBar
// Called by the framework when a possible menu bar should be dismissed.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknViewAppUi::StopDisplayingMenuBar()
	{
	CAknAppUi::StopDisplayingMenuBar();
	
	if ( iView )
	    {
		iView->StopDisplayingMenuBar();
	    }
	}

// -----------------------------------------------------------------------------
// CAknViewAppUi::Extension
// Asserts that extension object has been created.
// -----------------------------------------------------------------------------
//
CAknViewAppUiExtension* CAknViewAppUi::Extension() const
    {
    __ASSERT_ALWAYS( iExtension, Panic( EAknPanicObjectNotFullyConstructed ) );
    return iExtension;
    }

// -----------------------------------------------------------------------------
// CAknViewAppUi::SetSplitViewL
// Combines two views.
// -----------------------------------------------------------------------------
//
#ifdef RD_SPLIT_VIEW
EXPORT_C void CAknViewAppUi::SetSplitViewL( const TUid aView1Id, 
                                            const TUid aView2Id, 
                                            const TInt aLeftViewSize )
    {
    // a view can belong to one split view only
    RemoveSplitViewL( aView1Id );
    RemoveSplitViewL( aView2Id );
        
    TAknSplitViewContainer splitView;
    splitView.iViewIds[0] = aView1Id;
    splitView.iViewIds[1] = aView2Id;
    splitView.iLeftViewSize = aLeftViewSize;
    
    iExtension->iSplitViews.AppendL( splitView );
    }
#else
EXPORT_C void CAknViewAppUi::SetSplitViewL( const TUid /*aView1Id*/, 
                                            const TUid /*aView2Id*/, 
                                            const TInt /*aLeftViewSize*/ )
    {
    }
#endif // RD_SPLIT_VIEW
    
// -----------------------------------------------------------------------------
// CAknViewAppUi::RemoveSplitViewL
// Removes a view combination containing the given view UID.
// -----------------------------------------------------------------------------
//
#ifdef RD_SPLIT_VIEW
EXPORT_C void CAknViewAppUi::RemoveSplitViewL( const TUid aViewId )
    {
    for ( TInt i = 0; i < iExtension->iSplitViews.Count(); i++ )
        {
          if ( iExtension->iSplitViews[i].IsPartOf( aViewId ) )
            {
            iExtension->iSplitViews.Remove( i );
            
            if ( ViewShown( aViewId ) )
                {
                iExtension->iFlags |= EAknViewAppUiFromSplitToSingle;
                ActivateLocalViewL( aViewId );
                }
                
            return;
            }
        }
    }
#else
EXPORT_C void CAknViewAppUi::RemoveSplitViewL( const TUid /*aViewId*/ )
    {
    }
#endif // RD_SPLIT_VIEW

// -----------------------------------------------------------------------------
// CAknViewAppUi::SplitViewActive
// Checks if split view is in use.
// -----------------------------------------------------------------------------
//
#ifdef RD_SPLIT_VIEW
EXPORT_C TBool CAknViewAppUi::SplitViewActive() const
    {
    if ( iActivationQueue->Count() > 0 )
        {
    	if ( SplitView( iActivationQueue->At( 0 )->iNewView->Id() ) )
    	    {
            return ETrue;    	    
    	    }
        }
        
    if ( iExtension->iFlags & EAknViewAppUiFromSplitToSingle )
        {
        return EFalse;
        }
        
    return iExtension->iActiveViews.Count() > 1;
    }
#else
EXPORT_C TBool CAknViewAppUi::SplitViewActive() const
    {
    return EFalse;
    }
#endif // RD_SPLIT_VIEW

// -----------------------------------------------------------------------------
// CAknViewAppUi::FocusedView
// Returns the currently focused view.
// -----------------------------------------------------------------------------
//
#ifdef RD_SPLIT_VIEW
EXPORT_C TUid CAknViewAppUi::FocusedView() const
    {
    if ( iView )
        {
        return iView->Id();
        }
        
    return KNullUid;
    }
#else    
EXPORT_C TUid CAknViewAppUi::FocusedView() const
    {
    return KNullUid;
    }
#endif // RD_SPLIT_VIEW

// -----------------------------------------------------------------------------
// CAknViewAppUi::ViewShown
// Checks if the given view is visible on the screen.
// -----------------------------------------------------------------------------
//    
#ifdef RD_SPLIT_VIEW
EXPORT_C TBool CAknViewAppUi::ViewShown( const TUid aViewId ) const
    {
    for ( TInt i = 0; i < iExtension->iActiveViews.Count(); i++ )
        {
        if ( iExtension->iActiveViews[i]->Id() == aViewId )
            {
            return ETrue;
            }
        }
        
    return EFalse;
    }
#else
EXPORT_C TBool CAknViewAppUi::ViewShown( const TUid /*aViewId*/ ) const
    {
    return EFalse;
    }
#endif // RD_SPLIT_VIEW
    
   
// -----------------------------------------------------------------------------
// CAknViewAppUi::EnableLocalScreenClearer
// Enables/disables local screen clearer.
// -----------------------------------------------------------------------------
//  
EXPORT_C void CAknViewAppUi::EnableLocalScreenClearer( TBool aEnable )
    {
    // Make sure iExtension exists (can be called before BaseConstructL)
    if ( !iExtension )
        {
        TRAP_IGNORE( iExtension = CAknViewAppUiExtension::NewL() );
        }
    
    // Update flag
    if ( iExtension )
        {
        iExtension->iUseDefaultScreenClearer = aEnable;
        }

    // Create/delete iClearer if required
    if ( aEnable && !iClearer )
        {
        TRAP_IGNORE( iClearer = CAknLocalScreenClearer::NewL( EFalse ) );
        }
    else if ( !aEnable && iClearer )
        {
        delete iClearer;
        iClearer = NULL;
        }
    }
    
// -----------------------------------------------------------------------------
// CAknViewAppUi::ViewRect
// Returns view's rectangle.
// -----------------------------------------------------------------------------
//
#ifdef RD_SPLIT_VIEW
TRect CAknViewAppUi::ViewRect( const TUid aViewId ) const
    {
    // Following code is used until layout data is available. Eventually it
    // will be replaced by the commented code.
    TRect rect( ClientRect() );
    const TAknSplitViewContainer* splitView( SplitView( aViewId ) );
    
    if ( splitView )
        {
        TInt leftWidth( rect.Width() * splitView->iLeftViewSize / 100 );
        
        if ( splitView->iViewIds[0] == aViewId )
            {
            rect.SetWidth( leftWidth );
            }
        else
            {
            rect.SetWidth( rect.Width() - leftWidth );
            rect.Move( leftWidth, 0 );
            }
        }
        
    return rect;
    
/*    const TAknSplitViewContainer* splitView( SplitView( aViewId ) );
    
    if ( splitView)
        {
        TAknLayoutRect viewRect;
        
        if ( splitView->iViewIds[0] == aViewId ) // left view
            {
            viewRect.LayoutRect( ApplicationRect(), AknLayoutScalable_Avkon::main_pane( 8 ) );
            }
        else // right view
            {
            viewRect.LayoutRect( ApplicationRect(), AknLayoutScalable_Avkon::main_pane_cp() );
            }
            
        return viewRect.Rect();
        }
    
    return ClientRect();*/
    }
#endif // RD_SPLIT_VIEW
    
// -----------------------------------------------------------------------------
// CAknViewAppUi::SplitView
// If the given view is part of a split view then returns that split view.
// -----------------------------------------------------------------------------
//    
#ifdef RD_SPLIT_VIEW
CAknViewAppUi::TAknSplitViewContainer* CAknViewAppUi::SplitView( const TUid aViewId ) const
    {
    for ( TInt i = 0; i < iExtension->iSplitViews.Count(); i++ )
        {
          if ( iExtension->iSplitViews[i].IsPartOf( aViewId ) )
            {
            return &iExtension->iSplitViews[i];
            }
        }
        
    return NULL;
    }
#endif // RD_SPLIT_VIEW
    
// -----------------------------------------------------------------------------
// CAknViewAppUi::ActivateSplitViewL
// Activates views in split view.
// -----------------------------------------------------------------------------
//
#ifdef RD_SPLIT_VIEW
void CAknViewAppUi::ActivateSplitViewL( CViewActivationItem* aItem )
    {
    TAknSplitViewContainer* splitView( SplitView( aItem->iNewView->Id() ) );
    
    splitView->iFailed[0] = ETrue;
    splitView->iFailed[1] = ETrue;
    
    for ( TInt i = 0; i < KAknSplitViewSize; i++ )
        {
        TRect viewRect( ViewRect( splitView->iViewIds[i] ) );
        
        if ( ViewShown( splitView->iViewIds[i] ) )
            {
            if ( splitView->iViewRect[i] != viewRect )
                {
                splitView->iViewRect[i] = viewRect;
                View( splitView->iViewIds[i] )->HandleViewRectChange();
                }

            View( splitView->iViewIds[i] )->Redraw();
            }
        else
            {
            View( splitView->iViewIds[i] )->AknViewActivatedL( aItem->iPrevViewId, 
                                                               aItem->iCustomMessageId, 
                                                               *aItem->iCustomMessage );
            splitView->iViewRect[i] = viewRect;
            }
            
        splitView->iFailed[i] = EFalse;
        }
    }
#endif // RD_SPLIT_VIEW

// -----------------------------------------------------------------------------
// CAknViewAppUi::HandleViewNavigationL
// Handles navigation between visible split views.
// -----------------------------------------------------------------------------
//
#ifdef RD_SPLIT_VIEW
TKeyResponse CAknViewAppUi::HandleViewNavigationL( const TKeyEvent& aKeyEvent )
    {
    if ( SplitViewActive() )
        {
        switch ( aKeyEvent.iCode )
            {
            case EKeyLeftArrow:
            case EKeyRightArrow:
            case EKeyTab:
                if ( iView == iExtension->iActiveViews[0] )
                    {
                    ActivateLocalViewL( iExtension->iActiveViews[1]->Id() );
                    }
                else
                    {
                    ActivateLocalViewL( iExtension->iActiveViews[0]->Id() );
                    }

                return EKeyWasConsumed;
                
            default:
                break;
            }
        }

    return EKeyWasNotConsumed;
    }
#endif // RD_SPLIT_VIEW
    
// -----------------------------------------------------------------------------
// CAknViewAppUi::HandleWsEventL
// Handles pointer-initiated view switch.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknViewAppUi::HandleWsEventL( const TWsEvent& aEvent, CCoeControl* aDestination )
    {
#ifdef RD_SPLIT_VIEW
    if ( AknLayoutUtils::PenEnabled() )
        {
        if ( SplitViewActive() && aEvent.Type() == EEventPointer && !IsDisplayingMenuOrDialog() )
            {
            switch ( aEvent.Pointer()->iType )
                {
                case TPointerEvent::EButton1Down:
                    for ( TInt i = 0; i < iExtension->iActiveViews.Count(); i++ )
                        {
                        if ( iView == iExtension->iActiveViews[i] )
                            {
                            if ( iExtension->iActiveViews[i^1]->ClientRect().Contains( aEvent.Pointer()->iParentPosition ) )
                                {
                                iExtension->iFlags |= i + 1;
                                break;
                                }
                            }
                        }
                    break;
                    
                case TPointerEvent::EButton1Up:
                    for ( TInt i = 0; i < iExtension->iActiveViews.Count(); i++ )
                        {
                        if ( iView == iExtension->iActiveViews[i] )
                            {
                            if ( iExtension->iActiveViews[i^1]->ClientRect().Contains( aEvent.Pointer()->iParentPosition ) &&
                                 iExtension->iFlags & i + 1 )
                                {
                                ActivateLocalViewL( iExtension->iActiveViews[i^1]->Id() );
                                break;
                                }
                            }
                        }
                
                    iExtension->iFlags &= ~( EAknViewAppUiButton1DownInLeft | EAknViewAppUiButton1DownInRight );
                    break;
                    
                default:
                    break;
                }
            }
        }
#endif // RD_SPLIT_VIEW
    CAknAppUi::HandleWsEventL( aEvent, aDestination );
    }

// End of File
