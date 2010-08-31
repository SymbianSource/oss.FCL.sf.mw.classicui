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
* Description:  test functions in akniconarray.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <testsdkuifwutil.rsg>

#include "testsdkuifwutil.h"

// CONSTANTS
const TInt KArraySize = 10;
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestCAknIconArrayConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestCAknIconArrayConstructorL( CStifItemParser& /*aItem*/ )
    {
    CAknIconArray* array = new ( ELeave ) CAknIconArray( KArraySize );
    CleanupStack::PushL( array );
    STIF_ASSERT_NOT_NULL( array );
    CleanupStack::PopAndDestroy( array );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestCAknIconArrayConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestCAknIconArrayConstructFromResourceL( CStifItemParser& aItem )
    {
    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }
    CAknIconArray* array = new ( ELeave ) CAknIconArray( KArraySize );
    CleanupStack::PushL( array );
    switch ( num )
        {
        case ECaseZero:
            {
            array->ConstructFromResourceL( R_CAKNICONARRAY_ICON_ARRAY );
            break;
            }
        case ECaseOne:
            {
            TResourceReader reader;
            CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CAKNICONARRAY_ICON_ARRAY );
            array->ConstructFromResourceL( reader );
            CleanupStack::PopAndDestroy();
            break;
            }
        default:
            {
            CleanupStack::PopAndDestroy( array );
            return KErrNotSupported;
            }
        }
    
    CleanupStack::PopAndDestroy( array );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKUiFwUtil::TestCAknIconArrayAppendFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKUiFwUtil::TestCAknIconArrayAppendFromResourceL( CStifItemParser& aItem )
    {
    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }
    CAknIconArray* array = new ( ELeave ) CAknIconArray( KArraySize );
    CleanupStack::PushL( array );
    switch ( num )
        {
        case ECaseZero:
            {
            array->AppendFromResourceL( R_CAKNICONARRAY_ICON_ARRAY );
            break;
            }
        case ECaseOne:
            {
            TResourceReader reader;
            CCoeEnv::Static()->CreateResourceReaderLC( reader, R_CAKNICONARRAY_ICON_ARRAY );
            array->AppendFromResourceL( reader );
            CleanupStack::PopAndDestroy();
            break;
            }
        default:
            {
            CleanupStack::PopAndDestroy( array );
            return KErrNotSupported;
            }
        }
    
    CleanupStack::PopAndDestroy( array );
    
    return KErrNone;
    }

// End of file

