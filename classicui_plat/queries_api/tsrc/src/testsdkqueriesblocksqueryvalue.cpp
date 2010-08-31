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
* Description:  Test aknqueryvalue.h
*
*/

//INCLUDE
#include <aknqueryvalue.h>
#include <aknqueryvaluedate.h>

#include "testsdkqueries.h"

const TInt KZero = 0;

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVSetQueryModeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVSetQueryModeL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValue* date = CAknQueryValueDate::NewL();
    CleanupStack::PushL( date );
    
    date->SetQueryMode( MAknQueryValue::ESettingPageMode );
    date->SetQueryMode( MAknQueryValue::EQueryMode );
    
    CleanupStack::PopAndDestroy( date );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVSetSettingPageResourceIdsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVSetSettingPageResourceIdsL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValue* date = CAknQueryValueDate::NewL();
    CleanupStack::PushL( date );
    
    date->SetSettingPageResourceIds( KZero, KZero );
    
    CleanupStack::PopAndDestroy( date );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVSetAutoAppendL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVSetAutoAppendL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValue* date = CAknQueryValueDate::NewL();
    CleanupStack::PushL( date );
    
    date->SetAutoAppend( ETrue );
    date->SetAutoAppend( EFalse );
    
    CleanupStack::PopAndDestroy( date );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQVAppendValueIfNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQVAppendValueIfNewL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryValue* date = CAknQueryValueDate::NewL();
    CleanupStack::PushL( date );
    
    date->CAknQueryValue::AppendValueIfNewL();
    
    CleanupStack::PopAndDestroy( date );
    return KErrNone;
    }


//End file


