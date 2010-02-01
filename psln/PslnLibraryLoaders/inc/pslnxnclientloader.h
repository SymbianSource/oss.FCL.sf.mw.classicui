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
* Description:  Loads dynamically XnClient.dll.
*
*/


#ifndef C_PSLNXNCLIENTLOADER
#define C_PSLNXNCLIENTLOADER

#include <e32base.h>

class CXnODT;
class MXnThemeManagementServiceObserver;
class CXnClient;

/**
*  Interface class for browser launch.
*  
*  @lib PslnXNClientLoader.lib
*  @since Series 60 3.1
*/
class MPslnXNClientLoader
    {
    public:
        
        /**
        * Pure virtual method for searching for relevant themes.
        * @param aSearchMask mask to use when searching themes (contains app UID).
        * @param aHeaderList list to append found themes to.
        * @return result of operation
        */
        virtual TXnServiceCompletedMessage GetListHeaders( 
            const CXnODT& aSearchMask,
            CArrayPtrFlat<CXnODT>& aHeaderList ) = 0;

        /**
        * Pure virtual method for applying active theme.
        * @param aSetMask mask to use when applying theme (contains skin UID).
        * @param aHeader on return this will contain the activated theme info.
        * @return result of operation
        */
        virtual TXnServiceCompletedMessage SetActiveTheme( 
            const CXnODT& aSetMask, 
            CXnODT& aHeader ) = 0;

        /**
        * Pure virtual method for getting the next found theme.
        */
        virtual void GetNextHeader() = 0;

        /**
        * Pure virtual method for cancelling theme list query.
        * @return result of operation
        */
        virtual TXnServiceCompletedMessage CancelGetListHeaders() = 0;

        /**
        * Pure virtual method for creating the XnClient object.
        * @param aObserver observer for XnClient.
        */
        virtual void CreateClientL( 
            MXnThemeManagementServiceObserver& aObserver ) = 0;
    };

/**
*  This class is for dynamically loading ProfilesSettingsView.dll that 
*  enables setting of ringing tone for all profiles.
*
*  @lib PslnXNClientLoader.lib
*  @since Series 60 3.1
*/
class CPslnXNClientLoader : public CBase, public MPslnXNClientLoader
    {
public:
    /**
    * Two-phased constructor.
    * @return new instance of CPslnXNClientLoader.
    */
    static CPslnXNClientLoader* NewL();
    
    /**
    * Destructor.
    */
    virtual ~CPslnXNClientLoader();

    /**
    * Searches for relevant application themes.
    * @param aSearchMask mask to use when searching themes (contains app UID).
    * @param aHeaderList list to append found themes to.
    * @return result of operation
    */
    TXnServiceCompletedMessage GetListHeaders( 
        const CXnODT& aSearchMask,
        CArrayPtrFlat<CXnODT>& aHeaderList );

    /**
    * Applies active theme.
    * @param aSetMask mask to use when applying theme (contains skin UID).
    * @param aHeader on return this will contain the activated theme info.
    * @return result of operation
    */
    TXnServiceCompletedMessage SetActiveTheme( 
        const CXnODT& aSetMask, 
        CXnODT& aHeader );

    /**
    * Gets the next found theme.
    */
    void GetNextHeader();

    /**
    * Cancels theme list query.
    * @return result of operation
    */
    TXnServiceCompletedMessage CancelGetListHeaders();

    /**
    * Creates the XnClient object.
    * @param aObserver observer for XnClient.
    */
    void CreateClientL( 
        MXnThemeManagementServiceObserver& aObserver );

private:

    /**
    * C++ default constructor.
    */
    CPslnXNClientLoader();

private:

    /**
    * Xuikon client interface for applying theme changes.
    * Own.
    */
    CXnClient* iXknClient;

    };

// Environment gate function
IMPORT_C TAny* GateFunction( TAny* aObserver );

#endif // C_PSLNXNCLIENTLOADER
            
// End of File
