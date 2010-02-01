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
* Description:     A generic parameter class.
*
*/





#ifndef AIW_GENERIC_PARAM_H
#define AIW_GENERIC_PARAM_H

// INCLUDES
#include <e32base.h>
#include "AiwGenericParam.hrh"
#include "AiwVariant.h"

/**
 * AIW generic parameter id. This data type should always be used when dealing 
 * with AIW generic parameters. UIDs can be used as AIW generic parameter IDs. 
 * However, values from 0 to 131071 are reserved.
 * @see TAiwGenericParam 
 * @see TGenericParamIdValue
 */ 
typedef TInt TGenericParamId;

// CLASS DECLARATION

/**
* Generic parameter class for passing data between applications.
* A generic parameter is a pair of semantic ID and
* variant value. The semantic ID tells the purpose of the parameter,
* for example a file name, URL or phone number. The variant value contains
* the data format and actual value. This class does not implement any
* consistency checks between the semantic ID and value's data format.
* So one semantic ID can be expressed as alternative data formats.
*
* @lib ServiceHandler.lib
* @since Series 60 2.6
* @see TAiwVariant
* @see CAiwGenericParamList
*/
class TAiwGenericParam
    {
    public:  // Constructors and destructor
        /**
        * Constructs a generic parameter.
        */
        inline TAiwGenericParam();
        
        /**
        * Constructs a generic parameter.
        *
        * @param aSemanticId The semantic ID of the parameter, one of TGenericParamId values.
        */        
        inline TAiwGenericParam(TGenericParamId aSemanticId);
        
        /**
        * Constructs a generic parameter.
        *
        * @param aSemanticId The semantic ID of the parameter, one of TGenericParamId values.
        * @param aValue The parameter value.
        */        
        inline TAiwGenericParam(TGenericParamId aSemanticId, const TAiwVariant& aValue);

    public:  // Interface
        /**
        * Sets the semantic ID. Possibly set previous ID is overwritten.
        *
        * @param aSemanticId The semantic ID of the parameter.
        */
        inline void SetSemanticId(TGenericParamId aSemanticId);

        /**
        * Returns the semantic ID of this parameter.
        *
        * @return The semantic ID.
        */
        inline TGenericParamId SemanticId() const;

        /**
        * Returns the value of this parameter.
        *
        * @return The value of the parameter.        
        */
        inline TAiwVariant& Value();

        /**
        * Returns the const value of this parameter.
        *
        * @return The const value of the parameter.        
        */
        inline const TAiwVariant& Value() const;

        /**
        * Resets the semantic ID and the value of this parameter.
        */
        inline void Reset();

    private:  // Interface for friend classes
        void Destroy();
        void CopyLC(const TAiwGenericParam& aParam);
        static void CleanupDestroy(TAny* aObj);
        operator TCleanupItem();
        void InternalizeL(RReadStream& aStream);
        void ExternalizeL(RWriteStream& aStream) const;
        TInt Size() const; 

    private:  // Data
        /// Own: semantic ID of this parameter
        TGenericParamId iSemanticId;
        /// Own: value of this parameter
        TAiwVariant iValue;
        /// Reserved member
        TAny* iReserved;

    private:  // friend declarations
        friend class CAiwGenericParamList;
    };


// FUNCTIONS

/**
* Returns ETrue if two generic params are equal.
*
* @param aLhs Left hand side.
* @param aRhs Right hand side.
* @return ETrue if equal, EFalse otherwise.
*/ 
IMPORT_C TBool operator==(const TAiwGenericParam& aLhs, const TAiwGenericParam& aRhs);

/**
* Returns ETrue if two generic params are not equal.
*
* @param aLhs Left hand side.
* @param aRhs Right hand side.
* @return ETrue if not equal, EFalse otherwise.
*/
inline TBool operator!=(const TAiwGenericParam& aLhs, const TAiwGenericParam& aRhs);
        

/**
 * Generic parameter list.
 * A list containing TAiwGenericParam objects. Used for passing parameters 
 * between consumers and providers.
 *
 * @lib ServiceHandler.lib
 * @since Series 60 2.6
 */
NONSHARABLE_CLASS(CAiwGenericParamList): public CBase
    {
    public:   // Constructors and destructor
        /**
        * Creates an instance of this class.
        *
        * @return A pointer to the new instance.
        */
        IMPORT_C static CAiwGenericParamList* NewL();
        
        /**
        * Creates an instance of this class.
        *
        * @param aReadStream A stream to initialize this parameter list from.
        * @return A pointer to the new instance.
        */        
        IMPORT_C static CAiwGenericParamList* NewL(RReadStream& aReadStream);

        /**
        * Creates an instance of this class. Leaves the created instance on the
        * cleanup stack.
        *
        * @return A pointer to the new instance.
        */
        IMPORT_C static CAiwGenericParamList* NewLC();
        
        /**
        * Creates an instance of this class. Leaves the created instance on the
        * cleanup stack.
        *
        * @param aReadStream A stream to initialize this parameter list from.
        * @return A pointer to the new instance.
        */        
        IMPORT_C static CAiwGenericParamList* NewLC(RReadStream& aReadStream);

        /**
        * Destructor.
        */
        virtual ~CAiwGenericParamList();
        
    public:  // Interface
        /**
        * Returns the number of parameters in the list. 
        *
        * @return The number of parameters in the list. 
        */
        IMPORT_C TInt Count() const;
        
        /**
        * Returns the number of the parameters in the list by semantic id and datatype.
        *
        * @param aSemanticId The semantic ID of the parameter.
        * @param aDataType The type id of data. Default is any type.
        * @return The number of parameters in the list by semantic id and datatype.
        */
        IMPORT_C TInt Count(TGenericParamId aSemanticId, 
                TVariantTypeId aDataType = EVariantTypeAny) const;  
            
        /**
        * Returns a parameter from this list.
        *
        * @param aIndex Index of the parameter.
        * @return The parameter at the aIndex position.
        * @pre aIndex>=0 && aIndex<Count()
        */
        IMPORT_C const TAiwGenericParam& operator[](TInt aIndex) const;

        /**
        * Appends a parameter to this list.
        *
        * @param aParam The parameter to append to this list. This object takes
        *               an own copy of the data in aParam.
        */
        IMPORT_C void AppendL(const TAiwGenericParam& aParam);

        /**
        * Copies the given list and appends it to end of this list.
        *
        * @since Series 60 2.8        
        * @param aList A list to be copied and appended.
        */
        IMPORT_C void AppendL(const CAiwGenericParamList& aList);
        
        /**
        * Removes the first found item with given semantic id from the list.
        * 
        * @param aSemanticId Semantic id for the item to be removed.
        * @return  ETrue  if an item for the given semantic id was found and removed.
        *          EFalse otherwise.
        */
        IMPORT_C TBool Remove(TInt aSemanticId);

        /**
        * Deletes all parameters in the list and resets the list.
        */
        IMPORT_C void Reset();

        /**
        * Returns the first item matching the given semantic ID.
        *
        * @param aIndex Position in which to start searching. On return it contains 
        *               the position of the found parameter. It is set to KErrNotFound, 
        *               if no matching items were found.
        * @param aSemanticId The semantic ID of the parameter.
        * @param aDataType The type id of data. Default is any type.
        * @return The first matching item.
        */
        IMPORT_C const TAiwGenericParam* FindFirst(
            TInt& aIndex, 
            TGenericParamId aSemanticId,
            TVariantTypeId aDataType = EVariantTypeAny) const;
        /**
        * Returns the next item matching the given semantic ID.
        * 
        * @param aIndex Position after which to start searching. On return it contains 
        *               the position of the found parameter. It is set to KErrNotFound, 
        *               if no matching items were found.
        * @param aSemanticId The semantic ID of the parameter.
        * @param aDataType The type id of data. Default is any type. 
        * @return The next matching item.       
        */
        IMPORT_C const TAiwGenericParam* FindNext(
            TInt& aIndex, 
            TGenericParamId aSemanticId,
            TVariantTypeId aDataType = EVariantTypeAny) const;
        
        /**
        * Externalizes this parameter list to a stream.
        *
        * @param aStream The stream. 
        * @see NewL(RReadStream& aStream)
        * @see NewLC(RReadStream& aStream)
        */
        IMPORT_C void ExternalizeL(RWriteStream& aStream) const;

        /**
        * Returns the externalized size of the parameter list in bytes.
        *
        * @return The size.
        */
        IMPORT_C TInt Size() const;

        /**
        * Internalizes the parameter list from a stream.
        *
        * @since Series60 2.8
        * @param aStream The stream.
        */
        IMPORT_C void InternalizeL(RReadStream& aStream);

        /**
        * Packs the parameter list to TIpcArgs structure for
        * passing the generic param list to server over process boundary.
        * Only one RFile handle parameter can be passed over process boundary.
        *
        * @since Series60 3.0
        * @param aArgs Inter process call arguments.
        * @return Packed parameter list.
        */
        IMPORT_C HBufC8* PackForServerL(TIpcArgs& aArgs);

        /**
        * Unpacks the list from client message structure.
        *
        * @since Series60 3.0
        * @param aArgs The list to be unpacked. 
        */
        IMPORT_C void UnpackFromClientL(const RMessage2& aArgs);
        
    private:  // Implementation
        CAiwGenericParamList();
        void ConstructL();
        void AppendL(RReadStream& aReadStream);
        
    private:  // Data
        /// Own: the parameter list
        RArray<TAiwGenericParam> iParameters;
    };


// INLINE FUNCTIONS
#include "AiwGenericParam.inl"

#endif // AIW_GENERIC_PARAM_H

// End of File
