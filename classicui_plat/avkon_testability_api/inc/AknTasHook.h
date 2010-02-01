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
* Description:  Avkon testability hooking interface.
*
*/

#ifndef AKNTASHOOK_H
#define AKNTASHOOK_H

// INCLUDES
#include <e32base.h>
#include <coecntrl.h>
#include <cenrepnotifyhandler.h>
#include <TasDataModelInterface.h>

// CONSTANTS

// MACROS

    /**
     * AKNTASHOOK_ADDL
     * 
     * Leaving operation for adding an object hook. Use this macro in 
     * object construction, which can leave (i.e. Symbian two-phase 
     * construction, NewL/ConstructL).  
     * 
     * Add the macro into object construction so that it is called once 
     * per object instance creation. With some classes like lists etc. 
     * it should be so that the most derived class and a common base 
     * class are both hooked. The add code works so that if you call Add 
     * many times for the same object the class name is added into the 
     * list of known implementations for this object. Therefore, it should 
     * not matter if you call it many times but it should be called only 
     * once per class instance for performance reasons.
     * 
     * aTAnyPtr      Pointer to the added object (TAny*).
     * aClassNameStr Added object class name (literal text in double quotes).
     * aObjType      Type of the hooked object (TAknTasHookObjectType).
     * 
     * Usage:
     * 
     * void CAknAbc::ConstructL()
     *     {
     *     // Do construction stuff...
     *     AKNTASHOOK_ADDL( this, "CAknAbc" );
     *     }
     * 
     * void CBknAbc::ConstructL()
     *     {
     *     // Do construction stuff...
     *     AKNTASHOOK_ADDL2( this, "CBknAbc", EHookTypeFuture1 );
     *     }
     * 
     */
    #define AKNTASHOOK_ADDL( aTAnyPtr, aClassNameStr ) \
            { \
            CAknTasHook::AddL( aTAnyPtr, _L( aClassNameStr ) ); \
            }
    #define AKNTASHOOK_ADDL2( aTAnyPtr, aClassNameStr, aObjType ) \
            { \
            CAknTasHook::AddL( aTAnyPtr, _L( aClassNameStr ), aObjType ); \
            }
    
    /**
     * AKNTASHOOK_ADD
     * 
     * Use only if called from a constructor!!! Non-leaving operation 
     * for adding an object hook. Use this macro in C++ constructor, 
     * which cannot leave. 
     * 
     * Add the macro into object construction so that it is called once 
     * per object instance creation. With some classes like lists etc. 
     * it should be so that the most derived class and a common base 
     * class are both hooked. The add code works so that if you call Add 
     * many times for the same object the class name is added into the 
     * list of known implementations for this object. Therefore, it should 
     * not matter if you call it many times but it should be called only 
     * once per class instance for performance reasons.
     * 
     * aTAnyPtr      Pointer to the added object (TAny*).
     * aClassNameStr Added object class name (literal text in double quotes).
     * aObjType      Type of the hooked object (TAknTasHookObjectType).
     * 
     * Usage:
     * 
     * void CAknXyz::CAknXyz()
     *     {
     *     // Do construction stuff...
     *     AKNTASHOOK_ADD( this, "CAknXyz" );
     *     }
     * 
     * void CBknXyz::CBknXyz()
     *     {
     *     // Do construction stuff...
     *     AKNTASHOOK_ADD2( this, "CAknXyz", EHookTypeFuture1 );
     *     }
     * 
     */
    #define AKNTASHOOK_ADD( aTAnyPtr, aClassNameStr ) \
            { \
            TInt err( KErrNone ); \
            TRAP( err, CAknTasHook::AddL( aTAnyPtr, _L( aClassNameStr ) ) ); \
            }
    #define AKNTASHOOK_ADD2( aTAnyPtr, aClassNameStr, aObjType ) \
            { \
            TInt err( KErrNone ); \
            TRAP( err, CAknTasHook::AddL( aTAnyPtr, _L( aClassNameStr ), aObjType ) ); \
            }

    /**
     * AKNTASHOOK_REMOVE
     * 
     * Non-leaving operation for removing an object hook. Use this macro 
     * in C++ destructor, which cannot leave. 
     * 
     * Add the macro into object destruction so that it is called once 
     * per object pointer. Add and Remove operations do not necessarily 
     * have to be in pairs. It is enough to call Remove once per object 
     * pointer. For performance reasons it might be enough to call Remove 
     * only from the base class destructor. If you call it multiple times 
     * it will remove the pointer and information on all known 
     * implementations during the first call and the second call will 
     * just return without doing anything.
     *
     * Usage:
     * 
     * void CAknNka::~CAknNka()
     *     {
     *     AKNTASHOOK_REMOVE();
     *     // Do destruction stuff..
     *     }
     * 
     */
    #define AKNTASHOOK_REMOVE() \
            { \
            CAknTasHook::Remove( ( TAny* ) this ); \
            }

// DATA TYPES
/**
 * Supported UI technologies/object types. Avkon is used as default,
 * others may be defined in future for other technologies.
 */
enum TAknTasHookObjectType
    {
    EAknHookTypeNone,
    EAknHookTypeAvkon   /// Avkon/CCoeControl
    };

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS
class CAknTasPluginInterface;
class CRepository;

// CLASS DECLARATIONS
/**
 * Storage class for information about class/interface that the object implements
 *
 * @since S60 5.1
 * 
 */
class CAknTasClassInfo : public CBase
    {
    public:
        CAknTasClassInfo();
        ~CAknTasClassInfo();
        void ConstructL( TDesC& aClassName );
        
    public:
        const TDesC& GetClassName() const;
        static TInt MatchName( 
                const CAknTasClassInfo& aInfo1, 
                const CAknTasClassInfo& aInfo2 );

    private:
        HBufC* iClassName;

    };

/**
 * Storage class for information about UI object
 *
 * @since S60 5.1
 * 
 */
class CAknTasObjectInfo : public CBase
    {
    public:
        CAknTasObjectInfo();
        ~CAknTasObjectInfo();
        void ConstructL( 
                TAny* aObjPtr, 
                TAknTasHookObjectType aObjType = EAknHookTypeAvkon );
        
    public:
        /**
         * @brief Match object class.
         *
         * Interface for examining whether this object is of the given class.
         * The given class name is matched against the class names stored
         * for this object.
         * 
         * @return ETrue if the given class name matches, EFalse if not
         * @param aClassName Class name to match
         */
        IMPORT_C TBool IsA( TPtrC aClassName );
        
        /**
         * @brief Get this object.
         *
         * Interface for getting the hooked object stored in this class. The
         * pointer type depends on the object type, which can be checked with
         * function Type(). Received pointer can then be cast into correct 
         * object type base class when doing the hook traversing. 
         * 
         * @see TAknTasHookObjectType
         * 
         * @return Pointer to the hooked object
         */
        IMPORT_C TAny* GetControl() const;      
        
        /**
         * @brief Type of this object.
         *
         * Interface for getting the type of this object.
         * 
         * @see TAknTasHookObjectType
         * 
         * @return Type of the hooked object; represents the UI 
         *         technology/object type, can be Avkon or some
         *         other future UI technology 
         */
        IMPORT_C TAknTasHookObjectType Type() const;
        
        /**
         * @brief Get all class names of this object.
         *
         * Interface for getting all the class names of this object. The 
         * names are separated by a colon. 
         * 
         * Returned heap descriptor ownership passed to caller! 
         * 
         * @see HBufC
         * 
         * @return Pointer to the created descriptor
         */
        IMPORT_C HBufC* GetClassNames();

        void AddL( CAknTasClassInfo* aObjPtr );
        static TInt MatchByControl( 
                const CAknTasObjectInfo& aInfo1, 
                const CAknTasObjectInfo& aInfo2 );
                        
    public:        
        TUint32 iControlKey;        

    private:
        TAny*                            iObjPtr;               
        TAknTasHookObjectType            iObjType;
        RPointerArray<CAknTasClassInfo>* iClassInfoArray;       

    };
        
/**
 * Storage class for storing information about all UI objects
 *
 * @since S60 5.1
 * 
 */
class CAknTasHook : public CCoeStatic, public MCenRepNotifyHandlerCallback
    {
    public:
        /**
         * @brief Class function for adding an object hook.
         *
         * Interface for adding an object (hook) to the object info data 
         * structure. This is a class function and can be conveniently used
         * from the helper macros.
         * 
         * @see TAknTasHookObjectType
         *
         * @param aObjPtr Pointer to the added object
         * @param aStrPtr Added object class name
         * @param aObjType Type of the hooked object, default EAknHookTypeAvkon
         */
        IMPORT_C static void AddL( 
                TAny* aObjPtr, 
                TPtrC aStrPtr, 
                TAknTasHookObjectType aObjType = EAknHookTypeAvkon );
        
        /**
         * @brief Class function for removing an object hook.
         *
         * Interface for removing an object (hook) from the object info
         * data structure. This is a class function and can be conveniently
         * used from the helper macros.
         * 
         * @param aObjPtr Pointer to the object to be removed
         */
        IMPORT_C static void Remove( TAny* aObjPtr );
        
        /**
         * @brief Class function for getting a hooked object info.
         *
         * Interface for getting a stored object (hook) information from
         * the object info data structure. This is a class function.
         * 
         * @see CAknTasObjectInfo
         *
         * @return Instance of CAknTasObjectInfo or null
         * @param aObjPtr Pointer to the object whose info to get
         */
        IMPORT_C static CAknTasObjectInfo* Get( TAny* aObjPtr );
        
        /**
         * @brief Interface for getting all hooked objects.
         *
         * Interface for getting all stored objects' (hooks') information
         * from the object info data structure.
         * 
         * @see RPointerArray
         * @see CAknTasObjectInfo
         *
         * @return Array of all stored CAknTasObjectInfo instances
         */
        IMPORT_C RPointerArray<CAknTasObjectInfo>* GetAll();

        /**
         * @brief Interface for getting Avkon internal hooked objects.
         * 
         * Add avkon internal details to the provided tas model object. 
         * In most cases the object given represents the application
         * being traversed.
         * 
         * @param aParentApplication The object where to add the internal data
         */
        IMPORT_C void GetAknUiLC( MTasObject& aParentApplication );
        
        static CAknTasHook* InstanceL();
        static CAknTasHook* Self();
        static TBool ExistsL( TAny* aObjPtr );
        
        CCenRepNotifyHandler* CreateNotifyHandlerL( CRepository& aRepository, TUint32 aKey );
        CAknTasObjectInfo* GetInfo( TAny* aObjPtr );
        void AddInfoL( TAny* aObjPtr, TPtrC aStrPtr, TAknTasHookObjectType aObjType );
        void RemoveInfoL( TAny* aObjPtr );
        TBool InfoExistsL( TAny* aObjPtr );
        TBool Initialized();
        
        ~CAknTasHook();
        void ConstructL();
        
    public: // From MCenRepNotifyHandlerCallback
        void HandleNotifyInt( TUint32 aId, TInt aNewValue );

    private:
        CAknTasHook();
        TBool CheckSanityL( CCoeControl* aCcontrol );       
        void AddCommonCoeInfoL( CCoeControl* aObjPtr, MTasObject& aObjectInfo );
        
    private:
        RPointerArray<CAknTasObjectInfo>*   iObjectInfoArray;     
        CAknTasPluginInterface*             iTasPlugin;
        CCenRepNotifyHandler*               iHookingNotifyHandler;
        CCenRepNotifyHandler*               iHookStoringNotifyHandler;
        CRepository*                        iTasHookingRepo;
        TBool                               iTasHookingEnabled;
        TBool                               iTasHookStoringEnabled;

    };    

#endif // AKNTASHOOK_H

// End of File
