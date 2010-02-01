/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Discreet popup
*
*/

#include <akndiscreetpopup.h>
#include <AknPanic.h>
#include <AknTasHook.h>
#include <eiksrvs.h>

#include "akndiscreetpopupcontrol.h"
#include "akndiscreetpopupserverhandler.h"

const TUid KDiscreetPopupSingleton = { 537001156 };
const TInt KInitialPopupId( 1 );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAknDiscreetPopup::~CAknDiscreetPopup
// ---------------------------------------------------------------------------
//
CAknDiscreetPopup::~CAknDiscreetPopup()
    {
    if ( iUseCoeEnv )
        {
        AKNTASHOOK_REMOVE();
        }
    CAknDiscreetPopupControl* popup( NULL );
    for ( TInt j = 0; j < iLocalPopups.Count(); j++ )
        {
        popup = iLocalPopups[ j ];
        delete popup;
        popup = NULL;
        }
    iLocalPopups.Close();
    delete iServerHandler;
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopup::ShowLocalPopupL
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CAknDiscreetPopup::ShowLocalPopupL( 
    const TDesC& aTitle,
    const TDesC& aText,
    CGulIcon* aIcon,
    const TAknsItemID& aSkinId,
    const TDesC& aBitmapFile,
    const TInt aBitmapId,
    const TInt aMaskId,
    const TInt aFlags,
    const TInt aCommand,
    MEikCommandObserver* aCommandObserver )
    {
    __ASSERT_ALWAYS( CCoeEnv::Static(), Panic( EAknPanicNotSupported ) );
    TInt popupId = 0;
    CAknDiscreetPopup* instance = InstanceL();
    if( instance )
        {
        popupId = instance->DoShowLocalL( aTitle, 
                                          aText, 
                                          aIcon,
                                          aSkinId,
                                          aBitmapFile,
                                          aBitmapId,
                                          aMaskId,
                                          aFlags, 
                                          aCommand, 
                                          aCommandObserver );
        }
    return popupId;
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopup::ShowLocalPopupL
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CAknDiscreetPopup::ShowLocalPopupL(
    const TInt aResourceId, 
    const TInt aCommand,
    MEikCommandObserver* aCommandObserver )
    {
    __ASSERT_ALWAYS( CCoeEnv::Static(), Panic( EAknPanicNotSupported ) );
    TInt popupId = 0;
    CAknDiscreetPopup* instance = InstanceL();
    if( instance )
        {
        popupId = instance->DoShowLocalL( aResourceId, KNullDesC, aCommand, aCommandObserver );
        }
    return popupId;    
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopup::ShowGlobalPopupL
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CAknDiscreetPopup::ShowGlobalPopupL(
    const TDesC& aTitle,
    const TDesC& aText,
    const TAknsItemID& aSkinId,
    const TDesC& aBitmapFile,
    const TInt aBitmapId,
    const TInt aMaskId,
    const TInt aFlags,
    const TInt aCommandId,
    MEikCommandObserver* aCommandObserver,
    const TUid& aAppUid,
    const TUid& aViewUid )
    {
    TInt popupId = 0;
    CAknDiscreetPopup* instance = InstanceL();
    if ( instance )
        {
        popupId = instance->DoShowGlobalL(aTitle, aText, aSkinId, aBitmapFile, 
            aBitmapId, aMaskId, aFlags, aCommandId, aCommandObserver, aAppUid,
            aViewUid);
        }
    return popupId;    
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopup::ShowGlobalPopupL
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CAknDiscreetPopup::ShowGlobalPopupL( 
    const TInt aResourceId,
    const TDesC& aResourceFile,
    const TInt aCommandId,
    MEikCommandObserver* aCommandObserver,
    const TUid& aAppUid,
    const TUid& aViewUid )
    {
    TInt popupId = 0;
    CAknDiscreetPopup* instance = InstanceL();
    if( instance )
        {
        popupId = instance->DoShowGlobalL( aResourceId,
                                           aResourceFile,
                                           aCommandId,
                                           aCommandObserver,
                                           aAppUid,
                                           aViewUid );
        }
    return popupId;    
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopup::InitL
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknDiscreetPopup::InitL()
    {
    __ASSERT_ALWAYS( !CCoeEnv::Static(), Panic( EAknPanicNotSupported ) );

    // Create popup instance and store it to TLS
    if ( !Dll::Tls() )
        {
        CAknDiscreetPopup* instance = new ( ELeave ) CAknDiscreetPopup;
        CleanupStack::PushL( instance );
        instance->ConstructL();
        User::LeaveIfError( Dll::SetTls( instance ) );
        CleanupStack::Pop( instance );
        }
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopup::Release
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknDiscreetPopup::Release()
    {
    __ASSERT_ALWAYS( !CCoeEnv::Static(), Panic( EAknPanicNotSupported ) );

    // Delete popup instance from TLS
    CAknDiscreetPopup* instance =
        static_cast<CAknDiscreetPopup*>( Dll::Tls() );
    if ( instance )
        {
        delete instance;
        instance = NULL;
        Dll::SetTls( NULL );
        }
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopup::CAknDiscreetPopup
// ---------------------------------------------------------------------------
//
CAknDiscreetPopup::CAknDiscreetPopup()
    {
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopup::CAknDiscreetPopup
// ---------------------------------------------------------------------------
//
CAknDiscreetPopup::CAknDiscreetPopup( TBool aUseCoeEnv )
    : CCoeStatic( KDiscreetPopupSingleton, CCoeStatic::EThread ),
    iUseCoeEnv( aUseCoeEnv )
    {
    AKNTASHOOK_ADD( this, "CAknDiscreetPopup" );
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopup::ConstructL
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopup::ConstructL()
    {
    iServerHandler = CAknDiscreetPopupServerHandler::NewL();
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopup::InstanceL
// ---------------------------------------------------------------------------
//
CAknDiscreetPopup* CAknDiscreetPopup::InstanceL()
    {
    CAknDiscreetPopup* instance( NULL );
    if ( CCoeEnv::Static() )
        {
        instance = static_cast< CAknDiscreetPopup* >
            ( CCoeEnv::Static( KDiscreetPopupSingleton ) );
        if ( !instance )
            {
            instance = new ( ELeave ) CAknDiscreetPopup( ETrue );
            CleanupStack::PushL( instance );
            instance->ConstructL();
            CleanupStack::Pop( instance );
            }
        }
    else
        {
        instance = static_cast<CAknDiscreetPopup*>( Dll::Tls() );
        }
    return instance;
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopup::DoShowLocalL
// ---------------------------------------------------------------------------
//
TInt CAknDiscreetPopup::DoShowLocalL(
        const TDesC& aTitle, 
        const TDesC& aText, 
        CGulIcon* aIcon, 
        const TAknsItemID& aSkinId,
        const TDesC& aBitmapFile,
        const TInt& aBitmapId,
        const TInt& aMaskId,
        const TInt& aFlags, 
        const TInt& aCommand, 
        MEikCommandObserver* aCommandObserver )
    {
    TInt popupId( NextPopupId() );
    CAknDiscreetPopupControl* popup = CAknDiscreetPopupControl::NewL(
            EFalse, aTitle, aText, aIcon, aSkinId, aBitmapFile,
            aBitmapId, aMaskId, aFlags, aCommand, popupId, aCommandObserver );
    CleanupStack::PushL( popup );
    ShowPopupL( popup );
    CleanupStack::Pop( popup );
    return popupId;
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopup::DoShowLocalL
// ---------------------------------------------------------------------------
//
TInt CAknDiscreetPopup::DoShowLocalL( 
    const TInt& aResourceId,
    const TDesC& aResourceFile,
    const TInt& aCommand,
    MEikCommandObserver* aCommandObserver )
    {
    TInt popupId( NextPopupId() );
    CAknDiscreetPopupControl* popup = CAknDiscreetPopupControl::NewL(
            EFalse, aResourceId, aResourceFile, 
            aCommand, popupId, aCommandObserver );
    CleanupStack::PushL( popup );
    ShowPopupL( popup );
    CleanupStack::Pop( popup );
    return popupId;
    }

// ---------------------------------------------------------------------------
// CAknDiscreetPopup::DoShowGlobalL
// ---------------------------------------------------------------------------
//
TInt CAknDiscreetPopup::DoShowGlobalL(
        const TDesC& aTitle, 
        const TDesC& aText, 
        const TAknsItemID& aSkinId,
        const TDesC& aBitmapFile,
        const TInt& aBitmapId,
        const TInt& aMaskId,
        const TInt& aFlags,
        const TInt& aCommandId,
        MEikCommandObserver* aCommandObserver,
        const TUid& aAppUid,
        const TUid& aViewUid )
    {
    TInt popupId;
    RThread thread;
    if ( thread.Name() != EIKAPPUI_SERVER_THREAD_NAME && iServerHandler )
        {
        popupId = NextPopupId();
        iServerHandler->LaunchGlobalPopupL(
                aTitle,
                aText,
                aSkinId,
                aBitmapFile,
                aBitmapId,
                aMaskId,
                aFlags,
                aCommandId,
                popupId,
                aCommandObserver,
                aAppUid,
                aViewUid );
        }
    else
    	{
    	CGulIcon* icon = NULL;
    	DoShowLocalL( aTitle, aText, icon, aSkinId, aBitmapFile, 
    			aBitmapId, aMaskId, aFlags, aCommandId, aCommandObserver );
        }
    return popupId;    
    }
    
// ---------------------------------------------------------------------------
// CAknDiscreetPopup::DoShowGlobalL
// ---------------------------------------------------------------------------
//
TInt CAknDiscreetPopup::DoShowGlobalL( 
        const TInt& aResourceId,
        const TDesC& aResourceFile,
        const TInt& aCommandId,
        MEikCommandObserver* aCommandObserver,
        const TUid& aAppUid,
        const TUid& aViewUid )
    {
    TInt popupId;
    RThread thread;
    if ( thread.Name() != EIKAPPUI_SERVER_THREAD_NAME && iServerHandler )
        {
        popupId = NextPopupId();
        iServerHandler->LaunchGlobalPopupL(
                aResourceId,
                aResourceFile,
                aCommandId,
                popupId,
                aCommandObserver,
                aAppUid,
                aViewUid );
        }
    else
    	{
    	DoShowLocalL( aResourceId, aResourceFile, 
    			aCommandId, aCommandObserver );
        }
    return popupId;
    }

// ---------------------------------------------------------------------------
// CAknDiscreetPopup::ShowPopupL
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopup::ShowPopupL( CAknDiscreetPopupControl* aControl )
    {
    if ( !aControl )
        {
        return;
        }
        
    // Inform other popups that new popup is launched
    for ( TInt i = 0; i < iLocalPopups.Count(); i++ )
        {
        iLocalPopups[ i ]->HandleDiscreetPopupActionL( 
                CAknDiscreetPopupControl::EAknDiscreetPopupAnotherLaunched );
        }
    // Show popup and add it to popup list
    aControl->SetObserver( this );
    aControl->HandleDiscreetPopupActionL( 
        CAknDiscreetPopupControl::EAknDiscreetPopupShow );
    iLocalPopups.AppendL( aControl );
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopup::DeletePopup
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopup::DeletePopup( CAknDiscreetPopupControl* aControl )
    {
    if ( !aControl )
        {
        return;
        }

    TInt index = iLocalPopups.Find( aControl );
    iLocalPopups.Remove( index );
    delete aControl;
    aControl = NULL;
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopup::NextPopupId
// ---------------------------------------------------------------------------
//
TInt CAknDiscreetPopup::NextPopupId()
    {
    TInt popupId( KInitialPopupId );
    while ( PopupIdInUse( popupId ) )
        {
        popupId++;
        }
    if ( iServerHandler )
        {
        popupId = iServerHandler->CheckPopupId( popupId );
        }
    return popupId;
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopup::PopupIdInUse
// ---------------------------------------------------------------------------
//
TBool CAknDiscreetPopup::PopupIdInUse( const TInt& aPopupId )
    {
    for ( TInt i = 0; i < iLocalPopups.Count(); i++ )
        {
        if ( iLocalPopups[ i ]->PopupId() == aPopupId )
            {
            return ETrue;
            }
        }
    return EFalse;
    }


// ---------------------------------------------------------------------------
// CAknDiscreetPopup::HandleControlEventL
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopup::HandleControlEventL( 
        CCoeControl* aControl, TCoeEvent aEventType )
    {
    if ( aEventType == EEventRequestExit || aEventType == EEventRequestCancel )
        {
        DeletePopup( static_cast<CAknDiscreetPopupControl*>( aControl ) );
        }
    }


