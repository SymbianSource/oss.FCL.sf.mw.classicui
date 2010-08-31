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
* Description:  test eikhkeyt.h
*
*/



/*
 *  [INCLUDE FILES] - do not remove
 */
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <eikhkeyt.h>
#include <testsdkeikhkeyt.rsg>
#include <coemain.h>
#include <barsread.h>

#include "testsdkeikhkeyt.h"

const TInt KZero = 0;
const TInt KOne = 1;
const TInt KTwo = 2;
const TInt KThree = 3;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKEIKHKEYT::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKEIKHKEYT::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTestSDKEIKHKEYT::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKEIKHKEYT::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        ENTRY( "TestEHKEYCEikHotKeyTableL",
            CTestSDKEIKHKEYT::TestEHKEYCEikHotKeyTableL ),
        ENTRY( "TestEHKEYAddItemL", CTestSDKEIKHKEYT::TestEHKEYAddItemL ),
        ENTRY( "TestEHKEYCommandIdFromHotKeyL",
            CTestSDKEIKHKEYT::TestEHKEYCommandIdFromHotKeyL ),
        ENTRY( "TestEHKEYHotKeyFromCommandIdL",
            CTestSDKEIKHKEYT::TestEHKEYHotKeyFromCommandIdL ),
        ENTRY( "TestEHKEYRemoveItemL",
            CTestSDKEIKHKEYT::TestEHKEYRemoveItemL ),
        ENTRY( "TestEHKEYConstructFromResourceL",
            CTestSDKEIKHKEYT::TestEHKEYConstructFromResourceL ),
        ENTRY( "TestEHKEYResetL", CTestSDKEIKHKEYT::TestEHKEYResetL ),
        ENTRY( "TestEHKEYDestructorL", CTestSDKEIKHKEYT::TestEHKEYDestructorL ),

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestSDKEIKHKEYT::TestEHKEYCEikHotKeyTable
// -----------------------------------------------------------------------------
//
TInt CTestSDKEIKHKEYT::TestEHKEYCEikHotKeyTableL( CStifItemParser& /*aItem*/ )
    {
    CEikHotKeyTable* hotkeytable = new (ELeave) CEikHotKeyTable;
    CleanupStack::PushL( hotkeytable );
    STIF_ASSERT_NOT_NULL( hotkeytable );
    CleanupStack::PopAndDestroy( hotkeytable );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestEHKEYAddItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEIKHKEYT::TestEHKEYAddItemL( CStifItemParser& /*aItem*/ )
    {
    CEikHotKeyTable* hotkeytableptr = new( ELeave ) CEikHotKeyTable;
    CleanupStack::PushL( hotkeytableptr );
    
    TInt commandId( KOne );
    TInt keycode( KTwo );
    TInt modifiers( KZero );
    hotkeytableptr->AddItemL( commandId, keycode, modifiers );
    
    TBool flag;
    TInt returnkeycode;
    flag = hotkeytableptr->HotKeyFromCommandId( commandId, returnkeycode,
        modifiers );
    STIF_ASSERT_TRUE( flag );
    STIF_ASSERT_EQUALS( keycode, returnkeycode );
    
    TInt returncommandId;
    returncommandId = hotkeytableptr->CommandIdFromHotKey( keycode, modifiers );
    STIF_ASSERT_EQUALS( commandId, returncommandId );
    CleanupStack::PopAndDestroy( hotkeytableptr );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestEHKEYCommandIdFromHotKey
// -----------------------------------------------------------------------------
//
TInt CTestSDKEIKHKEYT::TestEHKEYCommandIdFromHotKeyL( CStifItemParser& /*aItem*/ )
    {
    CEikHotKeyTable* hotkeytableptr = new( ELeave ) CEikHotKeyTable;
    CleanupStack::PushL( hotkeytableptr );
    
    TInt commandId( KOne);
    TInt keycode( KTwo );
    TInt modifiers( KZero );
    hotkeytableptr->AddItemL( commandId, keycode, modifiers );
    
    TInt commandId2( KTwo );
    TInt keycode2( KThree );
    TInt modifiers2( KZero );
    hotkeytableptr->AddItemL( commandId2, keycode2, modifiers2 );
    
    TInt returncommandId;
    TInt returncommandId2;
    returncommandId = hotkeytableptr->CommandIdFromHotKey( keycode, modifiers );
    returncommandId2 = hotkeytableptr->CommandIdFromHotKey( keycode2,
        modifiers2 );
    STIF_ASSERT_NOT_EQUALS( returncommandId, returncommandId2 );
    CleanupStack::PopAndDestroy( hotkeytableptr );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestEHKEYHotKeyFromCommandId
// -----------------------------------------------------------------------------
//
TInt CTestSDKEIKHKEYT::TestEHKEYHotKeyFromCommandIdL( CStifItemParser& /*aItem*/ )
    {
    CEikHotKeyTable* hotkeytableptr;
    hotkeytableptr = new( ELeave ) CEikHotKeyTable;
    CleanupStack::PushL( hotkeytableptr );

    TInt commandId( KOne );
    TInt keycode( KTwo );
    TInt modifiers( KZero );
    hotkeytableptr->AddItemL( commandId, keycode, modifiers );
    
    TInt commandId2( KTwo );
    TInt keycode2( KThree );
    TInt modifiers2( KZero );
    hotkeytableptr->AddItemL( commandId2, keycode2, modifiers2 );
    
    TInt returnkeycode;
    TInt returnkeycode2;
    TBool flag;
    TBool flag2;
    flag = hotkeytableptr->HotKeyFromCommandId( commandId, returnkeycode,
        modifiers );
    STIF_ASSERT_TRUE( flag );
    flag2 = hotkeytableptr->HotKeyFromCommandId( commandId2, returnkeycode2,
        modifiers2 );
    STIF_ASSERT_TRUE( flag2 );
    STIF_ASSERT_NOT_EQUALS( returnkeycode, returnkeycode2 );
    
    CleanupStack::PopAndDestroy( hotkeytableptr );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestEHKEYRemoveItem
// -----------------------------------------------------------------------------
//
TInt CTestSDKEIKHKEYT::TestEHKEYRemoveItemL( CStifItemParser& /*aItem*/ )
    {
    CEikHotKeyTable* hotkeytableptr = new( ELeave ) CEikHotKeyTable;
    CleanupStack::PushL( hotkeytableptr );

    TInt commandId( KOne );
    TInt keycode( KTwo );
    TInt modifiers( KZero );
    hotkeytableptr->AddItemL( commandId, keycode, modifiers );
    
    TBool flag;
    TInt returnkeycode;
    TInt returncommandId;
    flag = hotkeytableptr->HotKeyFromCommandId( commandId, returnkeycode,
        modifiers );
    returncommandId = hotkeytableptr->CommandIdFromHotKey( keycode, modifiers );
    
    STIF_ASSERT_TRUE( flag );
    STIF_ASSERT_EQUALS( keycode, returnkeycode );
    STIF_ASSERT_EQUALS( commandId, returncommandId );
    
    hotkeytableptr->RemoveItem( commandId );
    returnkeycode = 0;
    
    flag = hotkeytableptr->HotKeyFromCommandId( commandId, returnkeycode,
        modifiers );
    returncommandId = hotkeytableptr->CommandIdFromHotKey( keycode, modifiers );
    STIF_ASSERT_FALSE( flag );
    STIF_ASSERT_NOT_EQUALS( keycode, returnkeycode );
    STIF_ASSERT_NOT_EQUALS( commandId, returncommandId );
    CleanupStack::PopAndDestroy( hotkeytableptr );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestEHKEYConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEIKHKEYT::TestEHKEYConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CEikHotKeyTable* hotkeytableptr = new( ELeave ) CEikHotKeyTable;
    CleanupStack::PushL( hotkeytableptr );
    
    hotkeytableptr->ConstructFromResourceL( R_TEST_HOTKEYS );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader,R_TEST_HOTKEYS);
    
    TInt numberPlain( KZero );
    numberPlain = reader.ReadInt16();
    if( numberPlain )
        {
        const SEikHotKey* ptr=(const SEikHotKey*)reader.Ptr();
        reader.Advance(numberPlain*sizeof(SEikHotKey));
        TBool flag(EFalse);
        TInt keycode( KZero );
        TInt commandId( KZero );
        TInt modifires( KZero );
        commandId = ptr->iCommandId;
        flag = hotkeytableptr->HotKeyFromCommandId( commandId, keycode, modifires );
        STIF_ASSERT_TRUE( flag );
        }
    
    TInt numberCtrl( KZero );
    numberCtrl = reader.ReadInt16();
    if( numberCtrl )
        {
        const SEikHotKey* ptr=(const SEikHotKey*)reader.Ptr();
        reader.Advance(numberCtrl*sizeof(SEikHotKey));
        TBool flag(EFalse);
        TInt keycode( KZero );
        TInt commandId( KZero );
        TInt modifires(EModifierCtrl);
        commandId = ptr->iCommandId;
        flag = hotkeytableptr->HotKeyFromCommandId( commandId, keycode, modifires );
        STIF_ASSERT_TRUE( flag );
        }
    
    TInt numberShiftCtrl( KZero );
    numberShiftCtrl = reader.ReadInt16();
    if( numberShiftCtrl )
        {
        const SEikHotKey* ptr=(const SEikHotKey*)reader.Ptr();
        reader.Advance(numberShiftCtrl*sizeof(SEikHotKey));
        TBool flag(EFalse);
        TInt keycode( KZero );
        TInt commandId( KZero );
        TInt modifires(EModifierShift|EModifierCtrl);
        commandId = ptr->iCommandId;
        flag = hotkeytableptr->HotKeyFromCommandId( commandId, keycode, modifires );
        STIF_ASSERT_TRUE( flag );
        }
    
    CleanupStack::PopAndDestroy( KTwo );//reader, hotkeytableptr
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestEHKEYReset
// -----------------------------------------------------------------------------
//
TInt CTestSDKEIKHKEYT::TestEHKEYResetL( CStifItemParser& /*aItem*/ )
    {
    CEikHotKeyTable* hotkeytableptr = new( ELeave ) CEikHotKeyTable;
    CleanupStack::PushL( hotkeytableptr );

    TInt commandId( KOne );
    TInt keycode( KTwo );
    TInt modifiers( KZero );
    hotkeytableptr->AddItemL( commandId, keycode, modifiers );
    
    TInt commandId2( KTwo );
    TInt keycode2( KThree );
    TInt modifiers2( KZero );
    hotkeytableptr->AddItemL( commandId2, keycode2, modifiers2 );
    
    hotkeytableptr->Reset();
    
    TBool flag;
    TInt returnkeycode( KZero );
    TInt returncommandId( KZero );
    flag = hotkeytableptr->HotKeyFromCommandId( commandId, returnkeycode,
        modifiers );
    returncommandId = hotkeytableptr->CommandIdFromHotKey( keycode, modifiers );
    STIF_ASSERT_FALSE( flag );
    STIF_ASSERT_NOT_EQUALS( keycode, returnkeycode );
    STIF_ASSERT_NOT_EQUALS( commandId, returncommandId );
    
    flag = ETrue;
    flag = hotkeytableptr->HotKeyFromCommandId( commandId2, returnkeycode,
        modifiers2 );
    returncommandId = hotkeytableptr->CommandIdFromHotKey( keycode2,
        modifiers2 );
    STIF_ASSERT_FALSE( flag );
    STIF_ASSERT_NOT_EQUALS( keycode2, returnkeycode );
    STIF_ASSERT_NOT_EQUALS( commandId2, returncommandId );
    CleanupStack::PopAndDestroy( hotkeytableptr );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestEHKEYDestructor
// -----------------------------------------------------------------------------
//
TInt CTestSDKEIKHKEYT::TestEHKEYDestructorL( CStifItemParser& /*aItem*/ )
    {
    CEikHotKeyTable* hotkeytableptr = new( ELeave ) CEikHotKeyTable;
    CleanupStack::PushL( hotkeytableptr );
    STIF_ASSERT_NOT_NULL( hotkeytableptr );
    CleanupStack::Pop( hotkeytableptr );
    delete hotkeytableptr;
    
    return KErrNone;
    }

/*
 * [End of File] - Do not remove
 */
