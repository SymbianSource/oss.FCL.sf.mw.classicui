/*
* Copyright (c) 2004-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Notifier server app wrapper implementation.                                             
*
*/

#ifndef __AKNNOTIFIERSERVERAPPLICATION__
#define __AKNNOTIFIERSERVERAPPLICATION__

#include <AknDoc.h>
#include <aknapp.h>
#include <aknappui.h>
#include <aknappui.h>

class CAknNotifierManagerExtension;
class MEikSrvNotifierManager;
class CAknNotifierControllerUtility;

//----------------------------------
// Application
//----------------------------------
class CAknNotifierAppServerApplication : public CAknApplication
    {
public:
    IMPORT_C CAknNotifierAppServerApplication();
    IMPORT_C ~CAknNotifierAppServerApplication();
    
public: // CAknApplication 
    IMPORT_C void NewAppServerL(CApaAppServer*& aAppServer);
    IMPORT_C CApaDocument* CreateDocumentL(); 
    };

//----------------------------------
// Document
//----------------------------------
class CAknNotifierAppServerDocument : public CAknDocument
    {
public:
    CAknNotifierAppServerDocument(CEikApplication& aApp):CAknDocument(aApp){};
    
private: // from CAknDocument
    CEikAppUi* CreateAppUiL();
    };
 
//----------------------------------
// AppUi
//----------------------------------
class CAknNotifierAppServerAppUi : public CAknAppUi
    {
public:
    IMPORT_C CAknNotifierAppServerAppUi();
    IMPORT_C ~CAknNotifierAppServerAppUi();
    
public: //from CAknAppUi 
    IMPORT_C void ConstructL();
    IMPORT_C void HandleCommandL(TInt aCommand);
    IMPORT_C TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
    IMPORT_C void SetFadedL(TBool aFade);
    
    IMPORT_C TErrorHandlerResponse HandleError(
        TInt aError, 
        const SExtendedError& aExtErr, 
        TDes& aErrorText, 
        TDes& aContextText); 
        
    IMPORT_C void HandleSystemEventL(const TWsEvent& aEvent);
    
public: // new methods
    /**
     * Command AppUi to suppress appskey, ie. prevent app switch and FSW.
     * Method is synchronous.
     * @since 3.0
     * @param aSupress Set AppsKey blocked
     * @return Return KErrNone on success, otherwise system wide error code.
     */
    IMPORT_C TInt SuppressAppSwitching(TBool aSuppress);
    
    /**
     * Set non-standard notifier manager, see Manager().
     * Does not take ownership. 
     * @since 3.0
     * @param aManager Instance which implements MEikSrvNotifierManager.
     */
    IMPORT_C void SetManager(MEikSrvNotifierManager* aManager);

    /**
     * Returns pointer to instance implemeting MEikSrvNotifierManager.
     * If manager is not set by SetManager() defaults to CEikEnv::AppServer().  
     * @since 3.0
     * @return Pointer instance which acts as MEikSrvNotifierManager in this process.
     */
    IMPORT_C MEikSrvNotifierManager* Manager();
    
    IMPORT_C TBool& EikSrvBlocked();

public: //for internal use
    void BaseCallFadeL(TBool aFade);
    CAknNotifierControllerUtility* NotifierControllerUtility();
        
protected:
    /**
     * Sets ordinal position of this application window group (using priority 
     * ECoeAlwaysAtFront).
     * @since 3.0
     */
    IMPORT_C void SetOrdinalPositionL(TInt aPosition);

private:
    CAknNotifierManagerExtension* iExtension;
    }; 
 
#endif
 
// End of file
 
