/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Key sound window server plug-in class.
*
*/

#ifndef __AKNANIMKEYSOUND_H__
#define __AKNANIMKEYSOUND_H__

// INCLUDES
#include <w32adll.h>
#include <kefprovider.h>

// FORWARD DECLARATION
class CKefMap;
class CAknKeyRotator;
class CRepository;
class CAknPendingKeyEvent;
class CHWRMLight;
class MTactileFeedbackServer;

// CLASS DECLARATION

/**
 * Sound server session.
 */
class REikSrvSoundServerSession : public RSessionBase
    {
public: // New functions
    /**
    * Connects to sound server.
    * @return error code.
    */
    TInt Connect();

    /**
    * Informs sound server of key press.
    * @param aKey key pressed.
    * @param aRepeat ETrue if repeat, EFalse otherwise.
    * Asynch
    */
    void KeyPressed( TInt aKey, TRequestStatus& aStatus, TBool aRepeat = EFalse );
    };

/**
 * Asynchronous tone player.
 */
NONSHARABLE_CLASS(CAknAsynchTonePlayer) : public CActive
    {
public:
    CAknAsynchTonePlayer() : CActive(CActive::EPriorityHigh)
        {
        CActiveScheduler::Add(this);
        iSoundSession.Connect();
        }

    ~CAknAsynchTonePlayer()
        {
        iSoundSession.Close();
        }

    void RunL()
        {} // we could close & null sound session handle here in case error returned..

    void DoCancel()
        {}

    void KeyPressed( TInt aKey, TBool aRepeat = EFalse )
        {
        if ( (!IsActive() || iStatus != KRequestPending) && iSoundSession.Handle() )
            {
            Cancel();
            SetActive();
            iSoundSession.KeyPressed(aKey, iStatus, aRepeat);            
            }
        }
        
    REikSrvSoundServerSession iSoundSession;
    };

/**
 * Key sound plug-in.
 */
class CAknAnimKeySound : public CWindowAnim, public MKefProvider
    {
public: // Constructor and destructor
    /**
    * Constructor.
    */
    CAknAnimKeySound();

    /**
    * Destructor.
    */
    ~CAknAnimKeySound();

public: // Functions from base classes
    // From CAnim
    virtual TInt CommandReplyL( TInt aOpcode, TAny *aArgs );
    virtual void Command( TInt aOpcode, TAny *aArgs );
    virtual void Animate( TDateTime *aDateTime );

    // From CWindowAnim
    virtual void ConstructL( TAny *aArgs, TBool aHasFocus );
    virtual void Redraw();
    virtual void FocusChanged( TBool aState );

    // From MEventHandler
    virtual TBool OfferRawEvent( const TRawEvent &aRawEvent );

    // From MKefProvider
    void KefPostRawEvent(const TRawEvent& aRawEvent) const;
    void KefPostKeyEvent(const TKeyEvent& aKeyEvent) const;
    void KefGenerateKeySound( TInt aKey );    
    void KefGenerateFeedback( TUint16 aFeedback );

public: 
    /**
    * Checks if key code is in blocked.
    * @param key code to be checked.
    * @return ETrue if blocked.
    */
    static TBool IsBlockedKeyCode( TInt aScanCode );

    /**
    * Checks if key code is non-blocked.
    * @param key code to be checked.
    * @return ETrue if non-blocked.
    */
    static TBool NonBlockedKeyCode( TInt aScanCode );

private:
    
    /**
    * Checks key and pointer event interaction
    * @paran aRawEvent Event to be checked
    * @return ETrue if event should be blocked
    */
    TBool IsBlockedEvent( const TRawEvent &aRawEvent );

    /**
    * Checks key and pointer event interaction
    * @paran aScanCode Scan code of key pressed
    * @return ETrue if key event should be handled
    */    
    TBool IsAlwaysAcceptedKey( TInt aScanCode );
    
private:
    // ETrue if connected to sound server successfully.
    TBool iConnected;

    // Key pressed.
    TInt  iKeyPressed;

    // Key block enabled.
    TBool iEnableKeyBlock;

        // If pointer down is received while the lights are out
        // (this is checked with HWRMLight interface),
        // this is set to true. The next pointer down sets this
        // to false.
        //
        // When iBlockedPointerDown is true, all pointer events are blocked.
      //
      // See TSW Error TSUN-7E9BGR and CR 403-11166.
    TBool iBlockedPointerDown;

    // Library for key rotator.
    RLibrary iRotateLibrary;

    // Key rotator instance.
    CAknKeyRotator* iKeyRotator;
    
    // Library for KEF.
    RLibrary iKefLibrary;

    // Key event map instance.
    CKefMap* iKeyEventMap;
    
    // ETrue if no separate power key (end/power key sends power key events).
    TBool iFeatureNoPowerKey;

    // Event delivered down scan code when no power key enabled.
    TInt iNoPowerKeyScanCode;
    
    CAknAsynchTonePlayer* iSoundSession; // to make keytone playing asynch

    CAknPendingKeyEvent* iPendingEvent;
    
    // Extension for window group information.
    MAnimGeneralFunctionsWindowExtension* iExt;      
    
    // Pointer event handling ongoing, block key events
    TBool iBlockKeyEvents;
    
    // Key event handling ongoing, block pointer events
    TBool iBlockPointerEvents;
    

    CHWRMLight* iLight;
    MTactileFeedbackServer* iFeedback;
    };

#endif // __AKNANIMKEYSOUND_H__

// End of File
