/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Handles interface towards XUIKON, sets and gets theme information.
*
*/


#ifndef C_PSLNFWAPPTHEMEHANDLER_H
#define C_PSLNFWAPPTHEMEHANDLER_H


#include <e32base.h>
#include <XnThemeManagement.h>

class CXnODT;
class MPslnFWAppThemeObserver;
class CPslnXNClientLoader;

/**
 *  Handles interface towards XUIKON, sets and gets theme information.
 *
 *  @lib PslnFramework.lib
 *  @since S60 v3.1
 */
NONSHARABLE_CLASS( CPslnFWAppThemeHandler ) : 
    public CBase, 
    public MXnThemeManagementServiceObserver
    {

public:

    /**
    * Two-phased constructor.
    * @param aObserver observer for theme changes.
    * @param aApplicationSkinList plugin owned array, to be filled with 
    *        application specific themes.
    * @return new instance of CPslnFWAppThemeHandler.
    */
    EXPORT_C static CPslnFWAppThemeHandler* NewL( 
        MPslnFWAppThemeObserver& aObserver,
        CArrayPtrFlat<CXnODT>& aApplicationSkinList );

    /**
    * Destructor.
    */
    EXPORT_C virtual ~CPslnFWAppThemeHandler();

    /**
    * Gets application specific themes. Framework starts automatically listen 
    * for changes in application themes. These are given to the client using 
    * MPslnFWAppThemeObserver interface.
    * 
    * @param aUid UID of application whose themes are needed.
    * @return Xuikon specific error code for setting active skin.
    */
    IMPORT_C TXnServiceCompletedMessage GetApplicationSkinsL( TUid aUid );

    /**
    * Activates application specific theme. 
    * @param aThemeODT ODT of theme to be active (includes theme UID).
    * @return Xuikon specific error code for setting active skin.
    */
    IMPORT_C TXnServiceCompletedMessage SetApplicationSkinL( CXnODT& aThemeODT );

    /**
    * Client informs that is not interested in anymore getting notifications
    * through MPslnFWAppThemeObserver.
    */
    IMPORT_C void CancelGetApplicationSkins();
    
    /**
    * Activates application specific theme and exits calling application. 
    *
    * @since S60 V3.2
    *
    * @param aThemeODT ODT of theme to be active (includes theme UID).
    * @return Xuikon specific error code for setting active skin.
    */
    IMPORT_C TXnServiceCompletedMessage SetApplicationSkinAndExitL( 
        CXnODT& aThemeODT );

private:

    /**
    * From MXnThemeManagementServiceObserver.
    * Handles theme management events.
    * @param aMessage contains a service completion message returned from 
    *        the XnInstallationHandler and XnMaintenanceHandler to their 
    *        observer.
    */
    void HandleXnClientMessage( TXnServiceCompletedMessage aMessage );

    /**
    * C++ default constructor.
    */
    CPslnFWAppThemeHandler(
        MPslnFWAppThemeObserver& aObserver,
        CArrayPtrFlat<CXnODT>& aApplicationSkinList );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    /**
    * Creates and pushes new ODT to stack.
    * Created ODT is based on Application Uid.
    */
    CXnODT* CreateODTFromAppUidLC( TUid aUid );
    
    /**
    * Creates XUIKON client when needed.
    */
    void CreateXnClientL();

private: // data

    /**
    * Observer for framework's application theme changes.
    */
    MPslnFWAppThemeObserver& iObserver;

    /**
    * List of themes. Each theme is described within an ODT.
    * Now own.
    */
    CArrayPtrFlat<CXnODT>* iAppThemeList;

    /**
    * ETrue if there is outstanding application skin retrieval ongoing.
    */
    TBool iFetchOngoing;

    /*
    * Has the XUIKON client DLL already been loaded.
    */
    TBool iXnClientDllLoaded;

    /*
    * A handle to a dynamically loadable DLL.
    */
    RLibrary iXnClientDll;

    /*
    * Loads XUIKON Client library and acts as wrapper around the DLL.
    * Own.
    */
    CPslnXNClientLoader* iXnClientLoader;

    };

#endif // C_PSLNFWAPPTHEMEHANDLER_H

// End of File
