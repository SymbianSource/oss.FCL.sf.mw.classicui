/*
* Copyright (c) 2002-2004 Nokia Corporation and/or its subsidiary(-ies).
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

#if !defined(__AKNMEDIATORFACADE_H_)
#define __AKNMEDIATORFACADE_H_

#include <eikdialg.h>
#include<MediatorCommandInitiator.h> 
#include<MediatorEventConsumer.h>
#include<MediatorEventProvider.h>
#include <s32mem.h> 

#include <AknMediatorObserver.h>

NONSHARABLE_CLASS(CAknMediatorFacade): 
    public CBase, 
    public MMediatorEventObserver, 
    public MMediatorCommandResponseObserver
    {
public:
    DECLARE_TYPE_ID(KAknMediatorFacade)
    // Static constructor
    IMPORT_C static CAknMediatorFacade* NewL(CEikDialog* aDialog);
        
    // command enFacade to publish current data, 
    // enFacade will also start listening events with same parameters. 
    // if there is already active command, returns immediately and does nothing 
    IMPORT_C void IssueCommand();

    // cancels active command and event subscribe
    IMPORT_C void CancelCommand();
    
    // resets additional databuf
    IMPORT_C void ResetBuffer();

    // Sets external observer for commands and events. Once set, any arriving information will be passed to 
    // the observer before enFacade tries to do anythin with the data.
    IMPORT_C void SetObserver(MAknDialogMediatorObserver* aObserver);

    /**
	* @since 3.1
    * Post an updated data to cover ui. This option is available while dialog is on screen, previously defined 
    * category will be used. First call of this method will allocate event provider, so it is not created by default
    *
    * Please note that CAknMediatorFacade instance still conttains the data previously set, i.e.  
    * before setting new data, obsolete data should be cleared using CAknMediatorFacade::ResetBuffer()
    *
	* @param aDialogIndex Unique index to identify a dialog within the category
	*                     0 has special meaning, it causes implementation to generate event id based on 
	*                     original dialog index, namely dialogIndex + KAknMediatorUpdateChannelOffset
	* @return void 
	*/
	IMPORT_C void PostUpdatedDataL(TInt EventId = 0);
    
    ~CAknMediatorFacade();

public: // from MMediatorEventObserver
    void MediatorEventL( TUid aDomain,
                         TUid aCategory, 
                         TInt aEventId, 
                         const TDesC8& aData );


public: // MMediatorCommandResponderObserver
    void CommandResponseL( TUid aDomain,
                           TUid aCategory, 
                           TInt aCommandId,
                           TInt aStatus, 
                           const TDesC8& aData );

public: //inlines
    RBufWriteStream& BufStream() { return iStream; }
    TUid& CatUid()          { return iAppUid; }
    TInt& DialogIndex()     { return iDialogIndex; }

private: // utilities
    CAknMediatorFacade(CEikDialog* aDialog);
    void ConstructL();
    void HandleCommandL(TAknDialogMediatorObserverCommand aCmd, const TDesC8& aData);
    void ProcessDataL( const TDesC8& aData );

private:
    // -- Do not change place or content of this block --
    TUid                        iAppUid;
    TInt                        iDialogIndex; 
    RBufWriteStream                  iStream;
    // -- that would break BC with inline defs --
    CMediatorCommandInitiator*  iCommander;
    CMediatorEventConsumer*     iUpdater;
    MAknDialogMediatorObserver* iExternalObserver;
    CBufFlat*                   iBuf;
    CEikDialog*                 iDialog; // not owned
    CMediatorEventProvider*     iUpdateToCover;
    };

// Static getter, will return dialogs instance of CAknMediatorFacade once instance has been set 
IMPORT_C CAknMediatorFacade* AknMediatorFacade(const MObjectProvider* aMop);


#endif
