/*
* Copyright (c) 2002-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Alert dialog implementation for EIKON Server.
*
*/


#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eiknotifyalert.h>
#endif
#include <coemain.h>
#include <eikbtgpc.h>
#include <aknmessagequerycontrol.h>
#include <eiksrvui.rsg>

#include "EIKNFYUI.H"
#include "EIKSRV.HRH"

//
// CEikServNotifyAlert
//

const TInt KSomethingDefinetelyDifferentFromEEikBidCancel( ~( EEikBidCancel ) );

// ======== LOCAL FUNCTIONS ========

// ---------------------------------------------------------------------------
// CallDisplayNextNote
// ---------------------------------------------------------------------------
//
TInt CallDisplayNextNote( TAny* aThis )
    {
    TRAPD( err, ( static_cast<CEikServNotifyAlert*>( aThis )->DisplayNextNoteL() ) ); 
    return err;
    }

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CEikServNotifyAlert::CEikServNotifyAlert
// ---------------------------------------------------------------------------
//
CEikServNotifyAlert::CEikServNotifyAlert() : CAknMessageQueryDialog( ENoTone )
    {
    }


// ---------------------------------------------------------------------------
// CEikServNotifyAlert::~CEikServNotifyAlert
// ---------------------------------------------------------------------------
//
CEikServNotifyAlert::~CEikServNotifyAlert()
    {
    Reset();
    }


// ---------------------------------------------------------------------------
// CEikServNotifyAlert::ConstructL
// ---------------------------------------------------------------------------
//
void CEikServNotifyAlert::ConstructL()
    {
    SetGloballyCapturing( ETrue );

    // Constructs with two labels & two buttons.
    // Normal priority for CBA's is just ok.
    ConstructSleepingDialogL( R_EIKSERV_NOTIFIER_DIALOG2 );

    TCallBack callback( CallDisplayNextNote, this );
    iDisplayCallback = new (ELeave) CAsyncCallBack( callback,
                                                    CActive::EPriorityHigh );
    }


// ---------------------------------------------------------------------------
// CEikServNotifyAlert::Release
// ---------------------------------------------------------------------------
//
void CEikServNotifyAlert::Release()
    {
    if ( iObserver )
        {
        iObserver->HandleAlertCompletion(
            KSomethingDefinetelyDifferentFromEEikBidCancel );
        }

    delete this;
    }


// ---------------------------------------------------------------------------
// CEikServNotifyAlert::Reset
// ---------------------------------------------------------------------------
//
void CEikServNotifyAlert::Reset()
    {
    delete iTitle;
    delete iLabel;
    delete iBut1;
    delete iBut2;

    iTitle = NULL;
    iLabel = NULL;
    iBut1  = NULL;
    iBut2  = NULL;
    }


// ---------------------------------------------------------------------------
// CEikServNotifyAlert::DoLeavingSettingsL
// ---------------------------------------------------------------------------
//
void CEikServNotifyAlert::DoLeavingSettingsL( const TDesC& aTitle,
                                              const TDesC& aLabel, 
                                              const TDesC& aBut1,
                                              const TDesC& aBut2 )
    {
    TInt bufferSize = aTitle.Length() + aLabel.Length() + 1;
    HBufC* textBuffer = HBufC::NewLC( bufferSize );
    TPtr ptr( textBuffer->Des() );

    if ( aTitle.Length() )
        {
        ptr.Append( aTitle );
        _LIT( KFormFeed, "\f" );
        ptr.Append( KFormFeed );
        }
        
    if ( aLabel.Length() )
        {
        ptr.Append( aLabel );
        }
    
    if ( ptr.Length() )
        {
        static_cast<CAknMessageQueryControl*>(
            Control( EAknMessageQueryContentId ) )->SetMessageTextL( &ptr );
        CleanupStack::Pop( textBuffer );
        }
    else
        {
        // Ownership not transferred.
        CleanupStack::PopAndDestroy( textBuffer );
        }

    CEikButtonGroupContainer& bgc = ButtonGroupContainer();
    bgc.SetCommandL( EAknAlertWinButton1, aBut1 );    
    bgc.SetCommandL( EAknAlertWinButton2, aBut2 );    
    }


// ---------------------------------------------------------------------------
// CEikServNotifyAlert::DisplayNotifier
// ---------------------------------------------------------------------------
//
void CEikServNotifyAlert::DisplayNotifier(
    const TDesC& aTitle,
    const TDesC& aLabel, 
    const TDesC& aBut1,
    const TDesC& aBut2,
    MEikNotifyAlertCompletionObserver* aObserver )
    {
    // Previous notify still not handled.
    if ( iObserver && aObserver )
        {
        aObserver->HandleAlertCompletion(
            KSomethingDefinetelyDifferentFromEEikBidCancel );
        return;
        }

    TRAPD( err,
        {
        iTitle = aTitle.AllocL();
        iLabel = aLabel.AllocL();
        iBut1  = aBut1.AllocL();
        iBut2  = aBut2.AllocL();
        }
        )

    if ( err )
        {
        Reset();
        }
    else
        {
        iObserver = aObserver;
        iDisplayCallback->CallBack();
        }
    }


// ---------------------------------------------------------------------------
// CEikServNotifyAlert::DisplayNextNoteL
// ---------------------------------------------------------------------------
//
void CEikServNotifyAlert::DisplayNextNoteL()
    {
    TRAPD( err, DoLeavingSettingsL( iTitle->Des(),
                                    iLabel->Des(),
                                    iBut1->Des(),
                                    iBut2->Des() ) );

    // Ownership was transferred.
    Reset();

    if ( err )
        {
        // Just make sure that observer will be completed correctly.
        OkToExitL( KSomethingDefinetelyDifferentFromEEikBidCancel ); 
        return;
        }

#ifdef RD_SCALABLE_UI_V2
    if ( AknLayoutUtils::PenEnabled() )
        {
        SetGloballyCapturing( ETrue ); 
        SetPointerCapture( ETrue ); 
        }
#endif
 
    RouseSleepingDialog();
    }


// ---------------------------------------------------------------------------
// CEikServNotifyAlert::OkToExitL
// ---------------------------------------------------------------------------
//
TBool CEikServNotifyAlert::OkToExitL( TInt aButtonId )
    {
#ifdef RD_SCALABLE_UI_V2
    if ( AknLayoutUtils::PenEnabled() )
        {
        SetGloballyCapturing( EFalse ); 
        SetPointerCapture( EFalse ); 
        }
#endif

    if ( iObserver )
        {
        iObserver->HandleAlertCompletion( aButtonId );
        }

    // To make sure that HandleAlertCompletion() will be
    // called only once per DisplayNotifier.
    iObserver = NULL;

    // always exit
    return ETrue;
    }

// End of file
