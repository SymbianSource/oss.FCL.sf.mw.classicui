/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Dynamic soft notification observer.
*
*/

#ifndef AKNDYNAMICSOFTNOTEOBSERVER_H
#define AKNDYNAMICSOFTNOTEOBSERVER_H

// INCLUDES
#include <e32base.h>
#include <AknCapServerClient.h> // RAknUiServer

// FORWARD DECLARATIONS
class MAknDynamicSoftNoteObserver;
class CAknDynamicSoftNotifier;


/**
 * Observer class for dynamic soft notifications. Listens and receives 
 * dynamic soft notification events from CapServer. 
 * 
 * @since S60 3.2
 * @lib AknNotify.DLL 
 */
class CAknDynamicSoftNoteObserver : public CActive
    {
public:
    /**
     * Constructor.
     * 
     * @param aDynamicSoftNotifier Dynamic soft notifier.
     * @param aClientApp Observer client.
     * @param aNoteId Observed soft notification id
     */
    IMPORT_C static CAknDynamicSoftNoteObserver* NewL(
        CAknDynamicSoftNotifier& aDynamicSoftNotifier,
        MAknDynamicSoftNoteObserver* aClientApp, 
        TInt aNoteId );

    /**
     * Constructor.
     * 
     * @param aDynamicSoftNotifier Dynamic soft notifier.
     * @param aClientApp Observer client.
     * @param aNoteId Observed soft notification id
     */
    IMPORT_C static CAknDynamicSoftNoteObserver* NewLC(
        CAknDynamicSoftNotifier& aDynamicSoftNotifier,
        MAknDynamicSoftNoteObserver* aClientApp, 
        TInt aNoteId );
    
    /**
     * Destructor.
     */    
    virtual ~CAknDynamicSoftNoteObserver();
    
    /**
     * Observed dynamic soft notification id.
     * 
     * @return Observed note id.
     */
    TInt NoteId() const;
        
public: // From CActive
    void RunL();
    void DoCancel();

private: // new methods
    
    /**
     * Constructor.
     * 
     * @param aDynamicSoftNotifier Dynamic soft notifier.
     * @param aClientApp Observer client.
     * @param aNoteId Observed soft notification id
     */
    CAknDynamicSoftNoteObserver(
        CAknDynamicSoftNotifier& aDynamicSoftNotifier,
        MAknDynamicSoftNoteObserver* aClientApp, 
        TInt aNoteId );
    
    /**
     * Constructor.
     */
    void ConstructL();

    /**
     * Send asynchronous event request to server. Request is completed when
     * user responds to dynamic soft notification. 
     */
    void IssueRequest();
        
private: // Data
    /// Own. CapServer client session.
    RAknUiServer iSession;
    
    /// Not Own. Actual observing client. 
    MAknDynamicSoftNoteObserver* iClientApp;
    /// Reference to soft notifier. 
    CAknDynamicSoftNotifier& iDynamicSoftNotifier;
    /// Observed soft notification identifier. 
    TInt iNoteId;
    /// Response data from the server. 
    TPckgBuf<TInt> iEventBuffer;
    };

#endif // AKNDYNAMICSOFTNOTEOBSERVER_H
