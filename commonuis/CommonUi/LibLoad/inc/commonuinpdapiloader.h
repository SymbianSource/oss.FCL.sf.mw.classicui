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
* Description:  Loads Npdlib.dll dynamically.
*
*/


#ifndef C_COMMONUINPDAPILOADER
#define C_COMMONUINPDAPILOADER

#include <e32base.h>
#include <f32file.h>


/**
*  Interface class for saving a notepad memo.
*  
*  @lib commonuinpdapiloader.lib
*  @since Series 60 3.1
*/
class MCommonUiNpdApiLoader
    {
    public:
        
        /**
        * Pure virtual method for saving a notepad memo.
        * @param aFileName name of the file to be saved.
        * @since Series 60 3.1
        */
        virtual void SaveFileAsMemoL( const TDesC& aFileName ) = 0;
    
    	/**
        * Pure virtual method for saving a notepad memo.
        * @param aFileHandle handle of the file to be saved.
        * @since Series 60 3.1
        */        
        virtual void SaveFileAsMemoL( const RFile& aFileHandle ) = 0;
            
    };

/**
*  This class is for dynamically loading commonuinpdloader.dll that 
*  enables saving memos.
*
*  @lib CommonUiNpdApiLoader.lib
*  @since Series 60 3.1
*/
class CCommonUiNpdApiLoader : public CBase, public MCommonUiNpdApiLoader
    {
public:
    /**
    * Two-phased constructor.
    * @return new instance of CCommonUiNpdApiLoader.
    */
    static CCommonUiNpdApiLoader* NewL();
    
    /**
    * Destructor.
    */
    virtual ~CCommonUiNpdApiLoader();

	/**
    * Saves a files as a memo.
    * @param aFile name of the file to be saved.
    */
    void SaveFileAsMemoL( const TDesC& aFileName );
    
    /**
    * Saves a files as a memo.
    * @param aFile handle of the file to be saved.
    */
    void SaveFileAsMemoL( const RFile& aFileHandle );
    

private:

    /**
    * C++ default constructor.
    */
    CCommonUiNpdApiLoader();

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    };

// Environment gate function
IMPORT_C TAny* GateFunction();

#endif // C_COMMONUINPDAPILOADER
            
// End of File
