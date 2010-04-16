/*
* Copyright (c) 2002-2008 Nokia Corporation and/or its subsidiary(-ies). 
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
* Description:        
*
*/









#include <e32std.h>
#include <featmgr.h>
#include "FindUtil.h"
#include "FindUtilBase.h"

#ifdef __WINS__     
#include <featmgr.h>    
#endif

typedef MFindUtil* (*TFindUtilFactoryFunctionL)();
_LIT( KFindUtilImpl, "FindUtilImpl.dll" );
#ifdef __WINS__
_LIT( KFindUtilImplJapan, "FindUtilImplJapan.dll" );
_LIT( KFindUtilImplChina, "FindUtilImplChina.dll" );
_LIT( KFindUtilImplThai, "FindUtilImplThai.dll" );
#endif // __WINS__

// -----------------------------------------------------------------------------
// CFindUtil::NewL()
// -----------------------------------------------------------------------------
//
EXPORT_C CFindUtil* CFindUtil::NewL()
    {
    TBool supported(ETrue);

    CFindUtil* self = NULL;

    if ( supported )
        {
        self = new( ELeave ) CFindUtil;
        CleanupStack::PushL( self );
        self->ConstructL();
        CleanupStack::Pop(self);
        }
        
    return self;
    }

// -----------------------------------------------------------------------------
// CFindUtil::~CFindUtil()
// -----------------------------------------------------------------------------
//
EXPORT_C CFindUtil::~CFindUtil()
    {
    if ( iInterface )
        {
        static_cast<CFindUtilBase*>( iInterface )->Close();
        }

    iLib.Close();
    }

// -----------------------------------------------------------------------------
// CFindUtil::CFindUtil()
// -----------------------------------------------------------------------------
//
CFindUtil::CFindUtil()
    {
    }

// -----------------------------------------------------------------------------
// CFindUtil::ConstructL()
// -----------------------------------------------------------------------------
//
void CFindUtil::ConstructL()
    {
#ifdef __WINS__     
    FeatureManager::InitializeLibL();
    if ( FeatureManager::FeatureSupported( KFeatureIdJapanese ) )
        {
        // load polymorphic implementation DLL
        User::LeaveIfError( iLib.Load( KFindUtilImplJapan ) );
        }
    else if ( FeatureManager::FeatureSupported( KFeatureIdChinese ) )
        {
        // load polymorphic implementation DLL
        User::LeaveIfError( iLib.Load( KFindUtilImplChina ) );
        }
    else if ( FeatureManager::FeatureSupported( KFeatureIdThai ) )
        {
        // load polymorphic implementation DLL
        User::LeaveIfError( iLib.Load( KFindUtilImplThai ) );
        }
    else
        {
        // load polymorphic implementation DLL
        User::LeaveIfError( iLib.Load( KFindUtilImpl ) );
        }
    FeatureManager::UnInitializeLib();
#else    

    // load polymorphic implementation DLL
    User::LeaveIfError( iLib.Load( KFindUtilImpl ) );

#endif  // __WINS__

    // Check if object has already been allocated
    iInterface = static_cast<MFindUtil*>( Dll::Tls() );
    
    if ( !iInterface )
        {
        iInterface = ( *(TFindUtilFactoryFunctionL)iLib.Lookup( 1 ) )();
        Dll::SetTls( iInterface );
        }

    if ( iInterface )
        {
        // This never leaves
        static_cast<CFindUtilBase*>( iInterface )->OpenL();
        }
    }

// End of File
