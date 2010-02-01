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
* Description:  Loads MPEngine.dll dynamically.
*
*/


#ifndef C_COMMONUIMPENGINEAPILOADER
#define C_COMMONUIMPENGINEAPILOADER

#include <e32base.h>
#include <f32file.h>

class MDesCArray;
class CStreamingLinkModel;

/**
*  Interface class for creating a new RAM file.
*  
*  @lib CommonUiMPEngineApiLoader.lib
*  @since Series 60 3.1
*/
class MCommonUiMPEngineApiLoader
    {
    public:

        /**
        * Pure virtual method for creating a new RAM file.
        * @param aNewRamFileName, New RAM file.
        * @param aLinkArray, Array which contains links which are 
            saved to RAM file.
        * @param aOverWrite, Overwrite existing file or not.
        * @return KErrNone or one of the system wide error codes. 
        * @since Series 60 3.1
        */
        virtual TInt CreateNewLinkFileL(
            const TDesC& aFileName, 
            MDesCArray* aLinkArray, 
            TBool aOverWrite ) = 0;
    };

/**
*  This class is for dynamically loading commonuimpengineapiloader.dll that 
*  enables creating a new RAM file.
*
*  @lib commonuimpengineapiloader.lib
*  @since Series 60 3.1
*/
class CCommonUiMPEngineApiLoader : public CBase, public MCommonUiMPEngineApiLoader
    {
public:
    /**
    * Two-phased constructor.
    * @return new instance of CCommonUiMPEngineApiLoader.
    */
    static CCommonUiMPEngineApiLoader* NewL();

    /**
    * Destructor.
    */
    virtual ~CCommonUiMPEngineApiLoader();

    /**
    * Create a new RAM file.
    * @param aNewRamFileName, New RAM file.
    * @param aLinkArray, Array which contains links which are 
        saved to RAM file.
    * @param aOverWrite, Overwrite existing file or not.
    * @return KErrNone or one of the system wide error codes. 
    */
    TInt CreateNewLinkFileL(
        const TDesC& aFileName, 
        MDesCArray* aLinkArray, 
        TBool aOverWrite );

private:

    /**
    * C++ default constructor.
    */
    CCommonUiMPEngineApiLoader();

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();
    
private: // data

    CStreamingLinkModel* iMPlayerModel;

    };

// Environment gate function
IMPORT_C TAny* GateFunction();

#endif // C_COMMONUIMPENGINEAPILOADER

// End of File
