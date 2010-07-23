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
* Description:     Variant data type for AIW generic parameters.
*
*/





#ifndef AIW_VARIANT_H
#define AIW_VARIANT_H

// INCLUDES
#include <e32std.h>
#include <s32strm.h>
#include <f32file.h>
#include "AiwVariantType.hrh"

// FORWARD DECLARATIONS

// CLASS DECLARATION

/**
* Variant data class to hold a value of a TAiwGenericParam instance.
* The variant contains a data type and a value. This class is attached to
* TAiwGenericParam instance which holds the semantic type of the value.
*
* @lib ServiceHandler.lib
* @since Series 60 2.6
* @see TAiwGenericParam
*/
class TAiwVariant
    {
    public:  // Constructors
        /**
        * Default constructor. Initializes this variant to be empty.
        *
        * @post IsEmpty()
        */
        inline TAiwVariant();
        
        /**
        * Constructor from a value.
        *
        * @param aValue The value to set for this variant object.
        */
        inline TAiwVariant(TInt32 aValue);
        
        /**
        * Constructor from a value.
        *
        * @param aValue The value to set for this variant object.
        */        
        inline TAiwVariant(const TUid& aValue);
        
        /**
        * Constructor from a value.
        *
        * @param aValue The value to set for this variant object.
        */        
        inline TAiwVariant(const TTime& aValue);
        
        /**
        * Constructor from a value.
        *
        * @param aValue The value to set for this variant object.
        */        
        inline TAiwVariant(const TDesC& aValue);
        
        /**
        * Constructor from a value.
        *
        * @param aValue The value to set for this variant object.
        */        
        inline TAiwVariant(const HBufC* aValue);
        
        /**
        * Constructor from a value.
        *
        * @param aValue The value to set for this variant object.
        */        
        inline TAiwVariant(const TDesC8& aValue);
        
        /**
        * Constructor from a value.
        *
        * @param aValue The value to set for this variant object.
        */        
        inline TAiwVariant(const RFile& aValue);

        /**
        * Copy constructor. Does not take ownership of data.
        *
        * @param aSrc The source object.
        */
        IMPORT_C TAiwVariant(const TAiwVariant& aSrc);
                
        /**
        * Assignment operator. Does not take ownership of data.
        *
        * @param aValue The source object.
        */
        IMPORT_C TAiwVariant& TAiwVariant::operator=(const TAiwVariant& aValue);

        // This class does not need a destructor because memory allocation
        // policy for variant class has been implemented by TAiwGenericParam
        // class.

    public:  // Interface
        /**
        * Returns the type id of data this variant object is holding.
        */
        inline TVariantTypeId TypeId() const;

        /**
        * Returns ETrue if this variant is empty (it does not hold any value).
        */
        inline TBool IsEmpty() const;

        /**
        * Retrieves the value held by this variant.
        *
        * @param aValue If this variant's type does not match the
        *               parameter type, the parameter will not be modified.
        * @return ETrue if aValue was set, EFalse if types did not match.
        */
        IMPORT_C TBool Get(TInt32& aValue) const;
        
        /**
        * Retrieves the value held by this variant.
        *
        * @param aValue If this variant's type does not match the
        *               parameter type, the parameter will not be modified.
        * @return ETrue if aValue was set, EFalse if types did not match.
        */        
        IMPORT_C TBool Get(TUid& aValue)   const;
        
        /**
        * Retrieves the value held by this variant.
        *
        * @param aValue If this variant's type does not match the
        *               parameter type, the parameter will not be modified.
        * @return ETrue if aValue was set, EFalse if types did not match.
        */        
        IMPORT_C TBool Get(TPtrC& aValue)  const;
        
        /**
        * Retrieves the value held by this variant.
        *
        * @param aValue If this variant's type does not match the
        *               parameter type, the parameter will not be modified.
        * @return ETrue if aValue was set, EFalse if types did not match.
        */        
        IMPORT_C TBool Get(TTime& aValue)  const;
        
        /**
        * Retrieves the value held by this variant.
        *
        * @param aValue If this variant's type does not match the
        *               parameter type, the parameter will not be modified.
        * @return ETrue if aValue was set, EFalse if types did not match.
        */        
        IMPORT_C TBool Get(TPtrC8& aValue) const;
        
        /**
        * Retrieves the value held by this variant.
        *
        * @param aValue If this variant's type does not match the
        *               parameter type, the parameter will not be modified.
        * @return ETrue if aValue was set, EFalse if types did not match.
        */        
        IMPORT_C TBool Get(RFile& aValue) const;

        /**
        * Returns the value held by this variant.
        *
        * @return The value held by this variant. If the data type does not
        *         match the function, the default initialized data is returned.
        */
        IMPORT_C TInt32 AsTInt32() const;
        
        /**
        * Returns the value held by this variant.
        *
        * @return The value held by this variant. If the data type does not
        *         match the function, the default initialized data is returned.
        */        
        IMPORT_C TUid AsTUid() const;
        
        /**
        * Returns the value held by this variant.
        *
        * @return The value held by this variant. If the data type does not
        *         match the function, the default initialized data is returned.
        */        
        IMPORT_C TPtrC AsDes() const;
        
        /**
        * Returns the value held by this variant.
        *
        * @return The value held by this variant. If the data type does not
        *         match the function, the default initialized data is returned.
        */        
        IMPORT_C TTime AsTTime() const;
        
        /**
        * Returns the value held by this variant.
        *
        * @return The value held by this variant. If the data type does not
        *         match the function, the default initialized data is returned.
        */        
        IMPORT_C TPtrC8 AsData() const; 
        
        /**
        * Returns the value held by this variant.
        *
        * @return The value held by this variant. If the data type does not
        *         match the function, the default initialized data is returned.
        */        
        IMPORT_C RFile AsFileHandle() const;

        /**
        * Deletes possibly set value and resets this variant to empty.
        *
        * @post IsEmpty()
        */
        IMPORT_C void Reset();

        /**
        * Sets integer value to this variant. The previous value is overwritten.
        *
        * @param aValue Value for this variant object to hold.
        * @post *this == aValue
        */
        IMPORT_C void Set(TInt32 aValue);

        /**
        * Sets unique ID value to this variant. The previous value is overwritten.
        *
        * @param aValue Value for this variant object to hold.
        * @post *this == aValue
        */
        IMPORT_C void Set(const TUid& aValue);
        
        /**
        * Sets date and time value to this variant. The previous value is overwritten.
        *
        * @param aValue Value for this variant object to hold.
        * @post *this == aValue
        */
        IMPORT_C void Set(const TTime& aValue);

        /**
        * Sets constant text reference to this variant. 
        *
        * @param aValue Text value for this variant object to hold.
        * @post *this == aValue
        */
        IMPORT_C void Set(const TDesC& aValue);

        /**
        * Sets constant text reference to this variant. 
        *
        * @param aValue Text value for this variant object to hold. 
        *               Ownership is not taken.
        */
        inline void Set(const HBufC* aValue);

        /**
        * Sets constant 8-bit text reference to this variant.
        * 
        * @param aValue Text value for this variant object to hold.
        * @post *this == aValue
        */
        IMPORT_C void Set(const TDesC8& aValue);

        /**
        * Sets RFile file handle to this variant.
        *
        * @param aValue File handle for this variant object to hold.
        * @post *this == aValue
        */
        IMPORT_C void Set(const RFile& aValue);

        /**
        * Assignment operator for the variant.
        *
        * @param aValue The source object.
        */
        inline TAiwVariant& operator=(const TTime& aValue);

        /**
        * Assignment operator for the variant.
        *
        * @param aValue The source object.
        */        
        inline TAiwVariant& operator=(const TUid& aValue);
        
        /**
        * Assignment operator for the variant.
        *
        * @param aValue The source object.
        */        
        inline TAiwVariant& operator=(TInt32 aValue);
        
        /**
        * Assignment operator for the variant.
        *
        * @param aValue The source object.
        */        
        inline TAiwVariant& operator=(const TDesC& aValue);
        
        /**
        * Assignment operator for the variant.
        *
        * @param aValue The source object.
        */        
        inline TAiwVariant& operator=(const HBufC* aValue);
        
        /**
        * Assignment operator for the variant.
        *
        * @param aValue The source object.
        */        
        inline TAiwVariant& operator=(const TDesC8& aValue);
        
        /**
        * Assignment operator for the variant.
        *
        * @param aValue The source object.
        */        
        inline TAiwVariant& operator=(const RFile& aValue);
        
    private:
        /**
        * Streaming support for TAiwGenericParam.
        * Internalizes this variant from a stream.
        */
        void InternalizeL(RReadStream& aStream);

        /**
        * Streaming support for TAiwGenericParam.
        * Externalizes this variant to a stream.
        */
        void ExternalizeL(RWriteStream& aStream) const;

        /**
        * Streaming support for TAiwGenericParam.
        * Returns the maximum externalized size of this variant in bytes.
        */
        TInt Size() const; 

        /**
        * Data copying support for TAiwGenericParam.
        * Sets the copy of given variant value to this variant
        * @param aValue variant value for this variant object to hold.
        * @post *this == aValue
        */
        void SetL(const TAiwVariant& aValue);

        /**
        * Destroys any dynamic resource owned by this variant.
        */
        void Destroy();

        /// Debug invariant
        void __DbgTestInvariant() const;
        
    private:  // Data
        /// Type of the data this variant is holding
        TUint8 iTypeId;

        /// POD storage for a 64-bit integer
        struct SInt64
            {
            TInt32 iLow;
            TInt32 iHigh;
            void InternalizeL(RReadStream& aStream);
            void ExternalizeL(RWriteStream& aStream) const;
            void Set(const TInt64& aTInt64);
            operator TInt64() const;
            TBool operator==(const SInt64& aRhs) const;
            };

        // Data value stored in this variant.
        // One of these are effective at a time depending on the iTypeId
        //
        union UData
            {
            TInt32 iInt32;      // 32-bit integer
            SInt64 iInt64;      // 64-bit integer
            HBufC* iBufC;       // owned string pointer 
            HBufC8* iBufC8;     // owned 8-bit data pointer 
            };

        UData  iData;  // Data union
        TPtrC  iPtrC;  // Pointer to string
        TPtrC8 iPtrC8; // Pointer to 8-bit data 

    private:  // friend declarations
        friend IMPORT_C TBool operator==(const TAiwVariant& aLhs, const TAiwVariant& aRhs);
        /// TAiwGenericParam needs access to private streaming and copying methods.
        friend class TAiwGenericParam;
        
    };


// FUNCTIONS

/**
* Returns ETrue if two variants are equal.
*
* @param aLhs Left hand side.
* @param aRhs Right hand side.
* @return ETrue if equal, EFalse otherwise.
*/
IMPORT_C TBool operator==(const TAiwVariant& aLhs, const TAiwVariant& aRhs);

/**
* Returns ETrue if two variants are not equal.
*
* @param aLhs Left hand side.
* @param aRhs Right hand side.
* @return ETrue if not equal, EFalse otherwise.
*/
inline TBool operator!=(const TAiwVariant& aLhs, const TAiwVariant& aRhs);

/**
* Dumps the contents of aVariant to debug output. Available only in debug builds.
*
* @param aVariant The object to be dumped.
*/
void Dump(const TAiwVariant& aVariant);


// INLINE FUNCTIONS
#include "AiwVariant.inl"

#endif // AIW_VARIANT_H

// End of File
