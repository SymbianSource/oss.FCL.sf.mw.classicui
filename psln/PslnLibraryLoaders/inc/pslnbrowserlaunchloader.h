/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Loads BrowserLaunch dll dynamically.
*
*/


#ifndef C_PSLNBROWSERLAUNCHLOADER
#define C_PSLNBROWSERLAUNCHLOADER

#include <e32base.h>


/**
*  Interface class for browser launcher library.
*  
*  @lib PslnBrowserLaunchLoader.lib
*  @since Series 60 3.2
*/
class MPslnBrowserLaunchLoader
    {
    public:
         
        /**
        * Pure virtual method for launching browser as standalone application.
        * 
        */            
        virtual void LaunchBrowserStandaloneL( ) = 0;
        
        /**
        * Pure virtual method for cancelling download.
        * @since 3.2
        */
        virtual void CancelDownload() = 0;

    };

/**
*  This class is for dynamically loading browserlauncher.dll that 
*  allows launching of browser as embedded application.
*
*  @lib PslnBrowserLaunchLoader.lib
*  @since Series 60 3.2
*/
class CPslnBrowserLaunchLoader : public CBase, public MPslnBrowserLaunchLoader
    {
public:
    /**
    * Two-phased constructor.
    * @return new instance of CPslnBrowserLaunchLoader.
    */
    static CPslnBrowserLaunchLoader* NewL();
    
    /**
    * Destructor.
    */
    virtual ~CPslnBrowserLaunchLoader();

    /**
    * Launches browser as standalone application.
    * 
    */            
    void LaunchBrowserStandaloneL(  );    

    /**
    * Cancels download.
    * @since 3.2
    */
    void CancelDownload();

private:

    /**
    * C++ default constructor.
    */
    CPslnBrowserLaunchLoader();
       
    /**
    * Gets browser bookmark folder id.
    */
    TInt GetFolderIdByContextIdL( TUint32 aContextId );
    

    };

// Environment gate function
IMPORT_C TAny* GateFunction();

#endif // C_PSLNBROWSERLAUNCHLOADER
            
// End of File
