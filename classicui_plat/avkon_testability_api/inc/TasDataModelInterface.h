/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  ECom plugin interface for testability data model for passing ui 
*                data from avkon to pc
*
*/


#ifndef __TASDATAMODELINTERFACE_H__
#define __TASDATAMODELINTERFACE_H__

// INCLUDES
#include <e32base.h>
#include <ecom/ecom.h>

// CONSTANTS
const static TUid KTasDataModelInterfaceUid = { 0x2001950D };
const static TUid KTasDataModelImplementationUid = { 0x2001950E };

// MACROS

// DATA TYPES

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS

class MTasObject;

// CLASS DECLARATION

/**
 * Represents an attribute in tas data 
 * model. Attribute can have values or 
 * object as members.
 * 
 * Attribute in the tas data model represents an attribute of an object.
 * Attributes can be simple name value pairs or more complicated structures.
 * Complicated attribute values are represented as tasobjects.
 * 
 * The object does not have to contain all elements. Implementations of serialize
 * have to take this fact into consideration.
 * 
 */
class MTasAttribute
    {
    public:
        
        /**
          * Set an id for the attribute. Used to identify objects.
          *   
          * @param aName Name of the attribute. 
          */
         virtual void SetIdL( const TDesC& aId )=0;
        
         /**
          * Set an id for the attribute. Used to identify objects.
          *   
          * @param aName Name of the attribute. 
          */
         virtual void SetIdL( const TInt& aId )=0;
                  
        /**
         * Set the name of the attribute. A new copy of the given descriptor is made.
         * The value is copied simply to avoid a scenario where the data model 
         * would remove a buffer which would still be needed by the calling 
         * component.  
         * @param aName Name of the attribute. 
         */
        virtual void SetNameL( const TDesC& aName )=0;
        
        /**
         * Set the type of the attribute.  A new copy of the given descriptor is made.
         * The value is copied simply to avoid a scenario where the data model 
         * would remove a buffer which would still be needed by the calling 
         * component.         
         * 
         * @param aType Type of the attribute. 
         */
        virtual void SetTypeL( const TDesC& aName  )=0;
        
        /**
         * Add a simple value to the attribute. Simple values are 
         * can be repserented as string. If a more complicated 
         * value is required use AddObject.  
         * A new copy of the given descriptor is made. 
         * The value is copied simply to avoid a scenario where the data model 
         * would remove a buffer which would still be needed by the calling 
         * component.
         * 
         * @param aValue New value for the attribute.
         */
        virtual void AddValueL( const TDesC& aValue  )=0;
        
          
                
        /**
         * Deep copy the data from the given attribute to this attribute.
         * 
         * @param aAttribute Data from the given attribute will be deep 
         *                   copied into this attribute.
         */
        virtual void CloneL( MTasAttribute &aAttribute )=0;
        
        /**
         * Destructor for MTasAttribute.
         * Needs to be defined here in case some implementations use
         * arrays to avoid user 42 panic.         
         * 
         */
        virtual ~MTasAttribute(){};

    };

/**
 * Represents an object in tas data model. MTasObjects are derived from MTasAttribute.
 * MTasObject can contains a handle to its parent, children and derivation tree.
 *  
 * The object does not have to contain all elements. Implementations of serialize
 * have to take this fact into consideration. 
 * 
 */
class MTasObject : public MTasAttribute
    {
    public:
      
        /**
         * Add new attribute to the MTasObject.
         * A reference to a new empty MTasAttribute instance is returned.          
         * 
         * @return Reference to a new MTasAttribute.
         */
        virtual MTasAttribute& AddAttributeL()=0;
        
        /**
         * Add new attribute to the MTasObject.
         * A reference to a new empty MTasAttribute instance is returned.          
         * 
         * @param aName Name of the attribute. 
         * @param aValue Value of the attribute. 
         * 
         * @return Reference to a new MTasAttribute.
         */
        virtual MTasAttribute& AddAttributeL( const TDesC& aName, const TDesC& aValue)=0;
        
        /**
         * Add new attribute to the MTasObject.
         * A reference to a new empty MTasAttribute instance is returned.          
         * 
         * @param aName Name of the attribute. 
         * @param aValue Value of the attribute.
         * 
         * @return Reference to a new MTasAttribute.
         */
        virtual MTasAttribute& AddAttributeL( const TDesC& aName, const TInt& aValue)=0;
                
        /**
         * Set the parent of this object. Parent is not the object that this object derives
         * from but an object that this object belongs to e.g ui component in a window.
         * 
         * The parent will be added to model as a deep copy of the given object. This is done to make
         * sure that the parent object which may also reside in a different location in the model
         * is not deleted too early by some party. This means that the parent given will not be deleted 
         * by this model.
         * 
         * @param aParent Parent of this object.
         */
        virtual void SetParentL( MTasObject& aParent )=0;

        
        /**
          * Add a complicated value to the object.
          * Returns a reference new empty MTasObject which has been 
          * added to the attribute.         
          * 
          * @return A reference to a new empty MTasObject instance.
          */
         virtual MTasObject& AddObjectL( )=0;                      
        
        /**
         * Add the object that this object derives from.
         * A reference to a new MTasObject instance is retuned.
         * 
         * @return A reference to a new MTasObject instance.
         */        
        virtual MTasObject& AddSuperClassL()=0;

        /**
         * Deep copy the data from the given object to this object.
         * 
         * @param aObject Data from the given object will be deep 
         *                   copied into this object.
         */
        virtual void CloneL( MTasObject& aObject)=0;        
        
        /**
         * Destructor for MTasObject
         * Needs to be defined here in case some implementations use
         * arrays to avoid user 42 panic.         
         * 
         */
        virtual ~MTasObject(){};
    };

/**
 * The container can represent an application for instance that contains 
 * the objects.   
 * 
 */
class MTasObjectContainer 
    {
    public:
        /**
         * Set an id for the attribute. Used to identify objects.
         *   
         * @param aName Name of the attribute. 
         */
        virtual void SetIdL( const TDesC& aId )=0;
    
        /**
         * Set the name of the attribute. A new copy of the given descriptor is made.
         * The value is copied simply to avoid a scenario where the data model 
         * would remove a buffer which would still be needed by the calling 
         * component.  
         * @param aName Name of the attribute. 
         */
        virtual void SetNameL( const TDesC& aName )=0;
    
        /**
         * Set the type of the attribute.  A new copy of the given descriptor is made.
         * The value is copied simply to avoid a scenario where the data model 
         * would remove a buffer which would still be needed by the calling 
         * component.         
         * 
         * @param aType Type of the attribute. 
         */
        virtual void SetTypeL( const TDesC& aName  )=0;    
    
        /**
         * Add new object to the container.
         * 
         * @return New MTasObject added to the storage.
         */
        virtual MTasObject& AddNewObjectL()=0;
        
        /**
         * Add new object to the container.
         * The container can represent an application for instance that contains 
         * the objects.
         * 
         * @param aName Name of the object.
         * @param aValue Value of the object.
         * @return New MTasObject added to the storage.
         */
        virtual MTasObject& AddNewObjectL( const TDesC& aName, const TDesC& aType, const TDesC& aId )=0;                                

        /**
         * Deep copy the data from the given container to this container.
         * 
         * @param aContainer Data from the given container will be deep 
         *                   copied into this container.
         */
        virtual void CloneL( MTasObjectContainer& aContainer )=0;           
        
        /**
         * Destructor for MTasObjectContainer
         * Needs to be defined here in case some implementations use
         * arrays to avoid user 42 panic.         
         * 
         */
        virtual ~MTasObjectContainer(){};
    };

/**
* Interface to the TasDataModel. The tas data model contains the ui data collected 
* From avkon. The data format and internal data model implementation are the responsibility of
* intarface implementations.
* 
* Some implementation considerations:
* All attributes of MTasAttribute and MTasObject are optional. This means that serialize 
* implementations must take this fact into consideration. 
* The model must be responsible for freeing all memory it has reserved. 
* The buffer passed to the SerializeTasDataL is naturally the responsibility 
* of the caller.
*/
class CTasDataModelInterface : public CBase
    {
    public:
        /**
         * Symbian constructor
         */ 
        static CTasDataModelInterface* NewL();

        /**
        * Wraps ECom object instantitation
        * plug-in loaded by its UID
        *
        * @param aUID service plugin implementation UDI
        */
        static CTasDataModelInterface* NewL(const TUid aUID);

        /**
        * Wraps ECom object instantitation
        * default resovler is used
        *
        * @param aMatchString service plugin name
        */
        static CTasDataModelInterface* NewL(const TDesC8& aMatchString);        
        
        /**
         * Destructor
         */
        virtual ~CTasDataModelInterface();
        

    public: //Comm plugin interface methods        
        
        /**
         * Add new Object to the data model.
         * Objects added directly to the DataModel 
         * will be serialized to the top level.
         * 
         * @return A reference to a new TasObject, which will be added to the data model.
         */
        virtual MTasObjectContainer& AddNewObjectContainerL() = 0;
        
        /**
         * Clean and destroy the added objects from the data model.
         * 
         */
        virtual void CleanObjectData() = 0;

        /**
         * Make a deep copy of the given CTasDataModelInterface
         * object to this CTasDataModelInterface object.
         * Any existing data will be removed berofe the clone is performed.
         * For merging models use MergeL.
         * All data is copied so the original model can be destroyed 
         * freely after the clone.
         * 
         * @param aModel CTasDataModelInterface to be copied into this object.
         */
        virtual void CloneL( CTasDataModelInterface& aModel )=0;         

        /**
         * Merges two TasDataModel structures into one model.
         * Merging is done by appending the TasObjectContainers 
         * from the given model to this model. Merged data is copied
         * so that the given model can be deleted with no affect to this 
         * instance.
         * 
         * @param aModel CTasDataModelInterface to be merged to this object.
         */
        virtual void MergeL( CTasDataModelInterface& aModel )=0;
        
        /**
         * Serialize the datamodel structure into the given buffer.
         * 
         * Implementing classes must consider the following facts when implementing:
         * All variables in MTasObject and MTasAttribute are optional. Existence of
         * data can not be assumed.
         * All memory reserved by the model is to be removed once model deleted.
         * aDataBuffer is considered not part of the model so its is the responsibility
         * of the calling module.          
         *          
         * @param The target buffer to where to serialize the data model.         
         * @return Amount of bytes updated to the buffer.
         */
        virtual TInt SerializeTasDataL( 
                RBuf8& aDataBuffer, 
                TBool aCompressionOn = EFalse ) = 0;
        
        /**
         * Serialize the datamodel structure into a file.
         * 
         * Implementing classes must consider the following facts when implementing:
         * All variables in MTasObject and MTasAttribute are optional. Existence of
         * data can not be assumed.
         *           
         *          
         * @param The target buffer to where to serialize the data model.
         * @return Number of byte written          
         */
        virtual TInt SerializeTasDataL( 
                RFs& aRFs, 
                const TDesC& aFileName, 
                TBool aCompressionOn = EFalse ) = 0;
        
        
    private: // Data
        /// Current instance identifier
        TUid iImplementation;

    };

#include <TasDataModelInterface.inl>

#endif // __TasDataModelInterface_H__

// End of File
