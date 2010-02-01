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
* Description:  Alert dialog for EIKON Server.
*
*/


#ifndef C_EIKNFYUI_H
#define C_EIKNFYUI_H

#include <e32base.h>
#include <aknmessagequerydialog.h>

#ifndef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eiksvfty.h>
#else
#include <uikon/eiksvfty.h>
#include <uikon/eiknotifyalert.h>
#endif

/**
*  EIKON Server alert dialog.
*  Used as the UI implementation of a @c RNotifier::Notify dialog.
*
*  This class implements a basic the two-line dialog.
*
*  @lib eiksrvui.lib
*/
NONSHARABLE_CLASS( CEikServNotifyAlert ) : public CAknMessageQueryDialog,
                                           public MEikServNotifyAlert
    {
public:
    
    /**
    * Default constructor.
    */
    CEikServNotifyAlert();

    /**
    * Second-phase constructor.
    */
    void ConstructL();

public: // From base class @c MEikServNotifyAlert.
    
    /**
    * Completes and releases the notifier.
    */
    void Release();
    
    /**
    * Displays the two-line notifier dialog.
    *
    * @param  aTitle     Text to be shown on the first row.
    * @param  aLabel     Text to be shown on the second row.
    * @param  aBut1      Text to be shown on the left softkey.
    * @param  aBut2      Text to be shown on the right softkey.
    * @param  aObserver  Pointer to the completion observer.
    */
    void DisplayNotifier(
        const TDesC& aTitle, 
        const TDesC& aLabel, 
        const TDesC& aBut1, 
        const TDesC& aBut2, 
        MEikNotifyAlertCompletionObserver* aObserver );

public: // From base class @c CEikDialog.

    /**
    * Handles a dialog button press for the specified button.
    *
    * @param   aButtonId  Button that was pressed.
    *
    * @return  @c ETrue it it's ok to exit,
    *          @c EFalse to keep the dialog active.
    */
    TBool OkToExitL( TInt aButtonId );

public:

    /**
    * Displays the note underneath when this is completed.
    */
    void DisplayNextNoteL();
    
private: 
    void DoLeavingSettingsL(
        const TDesC& aTitle, 
        const TDesC& aLabel, 
        const TDesC& aBut1, 
        const TDesC& aBut2);
    
    /**
    * Resets member variables when their ownership is transferred.
    */
    void Reset();
    
private:

    /**
    * Destructor.
    */
    ~CEikServNotifyAlert();
    
private: // Member data

    MEikNotifyAlertCompletionObserver*  iObserver;
    HBufC*                              iTitle;
    HBufC*                              iLabel;
    HBufC*                              iBut1;
    HBufC*                              iBut2;
    CAsyncCallBack*                     iDisplayCallback; 
    };

#endif
