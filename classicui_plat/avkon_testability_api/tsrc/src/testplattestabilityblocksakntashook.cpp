/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test AknTasHook.h
*
*/
// [INCLUDE FILES]
#include <coemain.h>
#include <tasdatamodelinterface.h>
#include "testplattestability.h"

// CONSTANTS
_LIT( KTest, "test" );
const TInt KHBufSize = 1024;
const TUid KUidTasHook = { 0xE000DEC4 };
// ============================ MEMBER FUNCTIONS =========================

// --------------------------------------------------------------------------
// CTestPlatTestAbility::TestCAknTasHookAddL
// --------------------------------------------------------------------------
//
TInt CTestPlatTestAbility::TestCAknTasHookAddL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplattestability, "CTestPlatTestAbility");
    _LIT(Ktestcakntashookaddl, "In TestCAknTasHookAddL");
    TestModuleIf().Printf(0, Kctestplattestability, Ktestcakntashookaddl);
    iLog->Log(Ktestcakntashookaddl);

    TPtrC ptr( KTest );
    HBufC* hBuf = HBufC::NewL( KHBufSize );
    CleanupStack::PushL( hBuf);
    *hBuf = ptr;
    CAknTasHook::AddL( hBuf, ptr );
    CleanupStack::PopAndDestroy( hBuf );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatTestAbility::TestCAknTasHookRemoveL
// --------------------------------------------------------------------------
//
TInt CTestPlatTestAbility::TestCAknTasHookRemoveL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplattestability, "CTestPlatTestAbility");
    _LIT(Ktestcakntashookremovel, "In TestCAknTasHookRemoveL");
    TestModuleIf().Printf(0, Kctestplattestability, Ktestcakntashookremovel);
    iLog->Log(Ktestcakntashookremovel);

    TPtrC ptr( KTest );
    HBufC* hBuf = HBufC::NewL( KHBufSize );
    CleanupStack::PushL( hBuf);
    *hBuf = ptr;
    CAknTasHook::Remove( hBuf );
    CleanupStack::PopAndDestroy( hBuf );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatTestAbility::TestCAknTasHookGetL
// --------------------------------------------------------------------------
//
TInt CTestPlatTestAbility::TestCAknTasHookGetL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplattestability, "CTestPlatTestAbility");
    _LIT(Ktestcakntashookgetl, "In TestCAknTasHookGetL");
    TestModuleIf().Printf(0, Kctestplattestability, Ktestcakntashookgetl);
    iLog->Log(Ktestcakntashookgetl);

    CAknTasHook* temp = 
        static_cast<CAknTasHook*> ( CCoeEnv::Static( KUidTasHook ) );
    TPtrC ptr( KTest );
    HBufC* hBuf = HBufC::NewL( KHBufSize );
    CleanupStack::PushL( hBuf);
    *hBuf = ptr;
    CAknTasObjectInfo* object  = CAknTasHook::Get( hBuf );
    CleanupStack::PopAndDestroy( hBuf );
    temp = NULL;


    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatTestAbility::TestCAknTasHookGetAllL
// --------------------------------------------------------------------------
//
TInt CTestPlatTestAbility::TestCAknTasHookGetAllL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplattestability, "CTestPlatTestAbility");
    _LIT(Ktestcakntashookgetalll, "In TestCAknTasHookGetAllL");
    TestModuleIf().Printf(0, Kctestplattestability, Ktestcakntashookgetalll);
    iLog->Log(Ktestcakntashookgetalll);
    
    CAknTasHook* temp = 
        static_cast<CAknTasHook*> ( CCoeEnv::Static( KUidTasHook ) );
    
    temp->GetAll();
    temp = NULL;

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatTestAbility::TestCAknTasHookGetAknUiLCL
// --------------------------------------------------------------------------
//
TInt CTestPlatTestAbility::TestCAknTasHookGetAknUiLCL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplattestability, "CTestPlatTestAbility");
    _LIT(Ktestcakntashookgetaknuilcl, "In TestCAknTasHookGetAknUiLCL");
    TestModuleIf().Printf(0, Kctestplattestability, Ktestcakntashookgetaknuilcl);
    iLog->Log(Ktestcakntashookgetaknuilcl);

    CAknTasHook* temp = 
        static_cast<CAknTasHook*> ( CCoeEnv::Static( KUidTasHook ) );

    class CTasObject : public CBase, public MTasObject
        {
    public:
        /*Constructor*/
        CTasObject(){}
        /*Deconstructor*/
        ~CTasObject(){}
        /**
         * Add new attribute to the MTasObject.
         * A reference to a new empty MTasAttribute instance is returned.
         * 
         * @return Reference to a new MTasAttribute.
         */
        MTasAttribute& AddAttributeL(){ return *this; }
        
        /**
         * Add new attribute to the MTasObject.
         * A reference to a new empty MTasAttribute instance is returned.
         * 
         * @param aName Name of the attribute. 
         * @param aValue Value of the attribute. 
         * 
         * @return Reference to a new MTasAttribute.
         */
        MTasAttribute& AddAttributeL( const TDesC& /*aName*/, 
            const TDesC& /*aValue*/)
            {
            return *this;
            }
        
        /**
         * Add new attribute to the MTasObject.
         * A reference to a new empty MTasAttribute instance is returned.
         * 
         * @param aName Name of the attribute. 
         * @param aValue Value of the attribute.
         * 
         * @return Reference to a new MTasAttribute.
         */
        MTasAttribute& AddAttributeL( const TDesC& /*aName*/,
                const TInt& /*aValue*/){ return *this; }
                
        /**
         * Set the parent of this object. Parent is not the object that this object derives
         * from but an object that this object belongs to e.g ui component in a window.
         * 
         * The parent will be added to model as a deep copy of the given object. This is done to make
         * sure that the parent object which may also reside in a different location in the model
         * is not deleted too early by some party. This means that the parent given will not be deleted 
         * by this model.
         * @param aParent Parent of this object.
         */
        void SetParentL( MTasObject& /*aParent*/ ){}

        
        /**
          * Add a complicated value to the object.
          * Returns a reference new empty MTasObject which has been 
          * added to the attribute.         
          * 
          * @return A reference to a new empty MTasObject instance.
          */
         MTasObject& AddObjectL(){ return *this; }
        
        /**
         * Add the object that this object derives from.
         * A reference to a new MTasObject instance is retuned.
         * 
         * @return A reference to a new MTasObject instance.
         */        
        MTasObject& AddSuperClassL(){ return *this; }

        /**
         * Deep copy the data from the given object to this object.
         * 
         * @param aObject Data from the given object will be deep 
         *                   copied into this object.
         */
        void CloneL( MTasObject& /*aObject*/){}
        
        /**
          * Set an id for the attribute. Used to identify objects.
          *   
          * @param aName Name of the attribute. 
          */
         void SetIdL( const TDesC& /*aId*/ ){}
        
         /**
          * Set an id for the attribute. Used to identify objects.
          *   
          * @param aName Name of the attribute. 
          */
         void SetIdL( const TInt& /*aId*/ ){}
                  
        /**
         * Set the name of the attribute. A new copy of the given descriptor is made.
         * The value is copied simply to avoid a scenario where the data model 
         * would remove a buffer which would still be needed by the calling 
         * component.  
         * @param aName Name of the attribute. 
         */
        void SetNameL( const TDesC& /*aName*/ ){}
        
        /**
         * Set the type of the attribute.  A new copy of the given descriptor is made.
         * The value is copied simply to avoid a scenario where the data model 
         * would remove a buffer which would still be needed by the calling 
         * component.         
         * 
         * @param aType Type of the attribute. 
         */
        void SetTypeL( const TDesC& /*aName*/  ){}
        
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
        void AddValueL( const TDesC& /*aValue*/  ){}
        
          
                
        /**
         * Deep copy the data from the given attribute to this attribute.
         * 
         * @param aAttribute Data from the given attribute will be deep 
         *                   copied into this attribute.
         */
        void CloneL( MTasAttribute &/*aAttribute*/ ){}
        
        };
    CTasObject object;
    temp->GetAknUiLC( object );
    temp = NULL;

    return KErrNone;
    }

// End of File

