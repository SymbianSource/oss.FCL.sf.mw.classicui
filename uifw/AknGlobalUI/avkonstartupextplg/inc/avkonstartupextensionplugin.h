/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Declaration of CAvkonStartupExtensionPlugIn class.
*
*/


#ifndef C_AVKON_STARTUP_EXTENSION_PLUG_IN_H
#define C_AVKON_STARTUP_EXTENSION_PLUG_IN_H

#include <systemstartupextension.h>
#include <AknCapServerClient.h>

class RAknUiServer;

/**
 * System Startup Extension plug-in for executing Avkon initialization during
 * system startup and shutting down applications during system shutdown.
 *
 *  @lib avkonstartupextensionplugin.lib
 *  @since S60 3.2
 */
NONSHARABLE_CLASS( CAvkonStartupExtensionPlugIn )
  : public CSystemStartupExtension
    {

public:

    /**
    * Constructs a CAvkonStartupExtensionPlugIn object.
    *
    * @param aConstructionParameters For the use of the base class.
    *
    * @since S60 3.2
    */
    static CAvkonStartupExtensionPlugIn* NewL( TAny* aConstructionParameters );

    /**
    * Destructor.
    *
    * @since S60 3.2
    */
    virtual ~CAvkonStartupExtensionPlugIn();

    /**
     * Execute Avkon operations depending on parameters.
     *
     * @since S60 3.2
     *
     * @param aStatus The request status to complete after the task has been
     * finished.
     * @param aParams Identifies the action to take. Either KPalette (to load
     *                palette), KEnableApps (to enable apps key) or KShutdown
     *                (to shut down applications).
     */
    virtual void ExecuteL( TRequestStatus& aStatus, const TDesC& aParams );

    /**
     * Cancel pending request.
     *
     * @since S60 3.2
     */
    virtual void Cancel();

private:

    CAvkonStartupExtensionPlugIn( TAny* aConstructionParameters );

    /**
     * Second phase constructor.
     *
     */
    void ConstructL();

    /**
    * Read color palette identifier from Central Repository and take it to use.
    *
    * @return KErrNone if successful, one of the global error codes otherwise.
    */
    TInt SetColorPalette();

    /**
    * Enable apps key.
    *
    * @return KErrNone if successful, one of the global error codes otherwise.
    */
    TInt EnableAppsKey();

    /**
    * Set global notes allowed.
    *
    * @return KErrNone if successful, one of the global error codes otherwise.
    */
    TInt EnableGlobalNotes();

private:

    RAknUiServer iAknUiServer; // AknUiServer session.
    
    TBool iActive; // Status of the ShutdownApps request.

    };

#endif // C_AVKON_STARTUP_EXTENSION_PLUG_IN_H
