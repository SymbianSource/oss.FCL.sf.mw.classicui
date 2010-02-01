/*
* Copyright (c) 2003-2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:     Declares common constants, types, classes etc. to be used both
*                consumer and provider side.
*
*/





#ifndef AIW_COMMON_H
#define AIW_COMMON_H

// INCLUDES
#include <AiwCommon.hrh>
#include <barsread.h> 
#include <AiwGenericParam.h>

// CONSTANTS

// MACROS

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS
class CEikMenuPane;
class CAiwGenericParamList;

// CLASS DECLARATION

/**
 * Criteria item data.
 * This class encapsulates an AIW criteria item. Criteria items are building 
 * blocks for AIW interests, i.e. an interest is a list of criteria items. 
 * A criteria item can be defined dynamically (by using this class) or 
 * in a resource file.
 *
 * @lib ServiceHandler.lib
 * @since Series 60 2.6
 */
class CAiwCriteriaItem : public CBase
    {
    public:   // Constructors and destructor
        /** 
        * Constructs a criteria item instance with null items.
        *
        * @return A pointer to the new object.
        */
        IMPORT_C static CAiwCriteriaItem* NewL();

        /** 
        * Constructs a criteria item instance with null items. Leaves the 
        * pointer to the cleanup stack.
        *
        * @return A pointer to the new object.
        */
        IMPORT_C static CAiwCriteriaItem* NewLC();

        /** 
        * Constructs a criteria item instance.
        *
        * @param aCriteriaId The criteria ID.
        * @param aServiceCmd The service command.
        * @param aContentType The content type.
        * @return A pointer to the new object.
        */
        IMPORT_C static CAiwCriteriaItem* NewL(
            TInt aCriteriaId,
            TInt aServiceCmd,
            const TDesC8& aContentType);

        /** 
        * Constructs a criteria item instance. Leaves the pointer to the 
        * cleanup stack.
        *
        * @param aCriteriaId The criteria ID.
        * @param aServiceCmd The service command.
        * @param aContentType The content type.
        * @return A pointer to the new object.
        */
        IMPORT_C static CAiwCriteriaItem* NewLC(
            TInt aCriteriaId,
            TInt aServiceCmd,
            const TDesC8& aContentType);

        /** 
        * Destructor.
        */        
        IMPORT_C virtual ~CAiwCriteriaItem();

    public: // New functions
        /** 
        * Sets the criteria ID.
        *
        * @param aId The criteria ID.
        */
        IMPORT_C void SetId(TInt aId);

        /** 
        * Sets the service class.
        *
        * @param aServiceUid The service class, see TAiwServiceClass.
        */
        IMPORT_C void SetServiceClass(const TUid& aServiceUid);
        
        /** 
        * Sets the service command UID.
        *
        * @param aServiceCmd The AIW service command, see TAiwServiceCommands.
        */
        IMPORT_C void SetServiceCmd(TInt aServiceCmd);

        /** 
        * Sets the content type. Makes a copy of the string data.
        *
        * @param aContentType Content MIME type, event type or any agreed one.
        */
        IMPORT_C void SetContentTypeL(const TDesC8& aContentType);

        /** 
        * Gets the criteria ID, 0 if not defined.
        *
        * @return The criteria ID.
        */
        IMPORT_C TInt Id() const;

        /** 
        * Gets the service class UID.
        *
        * @return The service class UID, see TAiwServiceClass.
        */
        IMPORT_C const TUid& ServiceClass() const;
        
        /** 
        * Gets the service command UID. KNullUid, if not defined.
        *
        * @return The service command UID, see TAiwServiceCommands.
        */
        IMPORT_C TInt ServiceCmd() const;

        /** 
        * Gets the content type.
        *
        * @return The content type.
        */
        IMPORT_C const TDesC8& ContentType() const;

        /** 
        * Sets the options.
        *
        * @param aOptions Options.
        */
        IMPORT_C void SetOptions(TUint aOptions);

        /** 
        * Gets the options.
        * 
        * @return Options.
        */
        IMPORT_C TUint Options() const;

        /** 
        * Maximum number of providers allowed for this criteria item. 
        * 
        * @return Maximum number of providers allowed for this criteria item.
        */
        IMPORT_C TInt MaxProviders() const;

        /** 
        * Reads a criteria item from a resource.  
        *
        * @param aReader A resource reader pointing to a criteria item.
        */
        IMPORT_C void ReadFromResoureL(TResourceReader& aReader);

        /** 
        * Returns the default provider.
        * 
        * @return The default provider UID.        
        */
        IMPORT_C TUid DefaultProvider() const;

        /** 
        * Sets the default provider.
        *
        * @param aDefault The UID of a default provider.
        */
        IMPORT_C void SetDefaultProvider(TInt aDefault);

        /** 
        * Equality operator. Two criteria items are considered equal only if all
        * parameters match. The parameters are: criteria id, service command, 
        * content type, service class, default provider, max providers and options). 
        *
        * @param aItem Criteria item to compare.
        * @return ETrue if criteria items are equal, EFalse otherwise.
        */
        IMPORT_C TBool operator==(const CAiwCriteriaItem& aItem);

        /** 
        * Sets the maximum number of providers.
        *
        * @param aMaxProviders The maximum number of providers.
        */
        IMPORT_C void SetMaxProviders(TInt aMaxProviders);

    public:
        /** 
        * If set, only ROM based providers can be attached to this criteria.
        *
        * @return ETrue if AIW_OPTIONS_ROM_ONLY bit is set, EFalse otherwise.
        */    
        inline TBool RomOnly() const;

    private:
        /**
        * C++ default constructor.
        */
        CAiwCriteriaItem();    
    
        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();
        
        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL(
            TInt aCriteriaId,
            TInt aServiceCmd,
            const TDesC8& aContentType);

    private:
        // Criteria ID.
        TInt iCriteriaId;
        // Service class UID
        TUid iServiceClass;
        // Service command UID
        TInt iServiceCmd;
        // Content type (MIME type). 
        HBufC8* iContentType;
        // Additional options
        TAiwVariant iOptions;
        //Default provider implementation uid
        TUid iDefaultProvider;
        // Reserved member
        TAiwVariant iReserved;
        // Max providers
        TInt iMaxProviders;
    };


inline TBool CAiwCriteriaItem::RomOnly() const
    {
    return (Options() & AIW_OPTIONS_ROM_ONLY) != 0;
    }


/**
* Interest is an array of criteria items.
*/
typedef RPointerArray<CAiwCriteriaItem> RCriteriaArray;

/**
* Abstract callback interface to handle callbacks or events
* from providers. This callback is needed when
* - Consumer wants to pre-check output parameters before returning
*   synchronous Handle*Cmd.
* - Asynchronous Handle*Cmd is used.
* - An asynchronous event occurs in the system.
* 
*  @lib ServiceHandler.lib
*  @since Series 60 2.6
*/ 
class MAiwNotifyCallback
    {
    public:
        /**
        * Handles notifications caused by an asynchronous Execute*CmdL call
        * or an event.
        *
        * @param aCmdId The service command associated to the event.
        * @param aEventId Occured event, see AiwCommon.hrh.
        * @param aEventParamList Event parameters, if any, as defined per
        *        each event.
        * @param aInParamList Input parameters, if any, given in the
        *        related HandleCommmandL.
        * @return Error code for the callback.
        */
        virtual TInt HandleNotifyL(
            TInt aCmdId,
            TInt aEventId,
            CAiwGenericParamList& aEventParamList,
            const CAiwGenericParamList& aInParamList) = 0;
    };

#endif // AIW_COMMON_H

// End of File


