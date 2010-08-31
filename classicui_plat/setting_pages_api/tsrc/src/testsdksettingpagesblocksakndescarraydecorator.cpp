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
* Description:  Test akndescarraydecorator.h
*
*/



// INCLUDE FILES
#include <akndescarraydecorator.h>
#include <badesca.h>

#include "testsdksettingpages.h"
#include "testsdksettingpagesstdinclude.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesArrayDecoratorConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesArrayDecoratorConstructorL( CStifItemParser& /*aItem*/ )
    {
    TAknDesCArrayDecorator* decorator = new( ELeave ) TAknDesCArrayDecorator();
    CleanupStack::PushL( decorator );
    STIF_ASSERT_NOT_NULL( decorator );
    CleanupStack::PopAndDestroy( decorator );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesArrayDecoratorSetArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesArrayDecoratorSetArrayL( CStifItemParser& /*aItem*/ )
    {
    TAknDesCArrayDecorator* decorator = new( ELeave ) TAknDesCArrayDecorator();
    CleanupStack::PushL( decorator );
    
    CDesCArrayFlat* arr = new( ELeave ) CDesCArrayFlat( KSize );
    CleanupStack::PushL( arr );

    TBuf<KBufSize> tom( KTom );
    TBuf<KBufSize> jack( KJack );
    TBuf<KBufSize> mary( KMary );
    
    arr->AppendL( tom );
    arr->AppendL( jack );
    arr->AppendL( mary );
    
    decorator->SetArray( arr );
    TBuf<KBufSize> buffer( KTestString );
    decorator->SetDecorationText( buffer );
    
    TInt count = decorator->MdcaCount();
    STIF_ASSERT_EQUALS( KThree, count );
    
    TInt numberofarray( KZero );
    TBool flag = decorator->DecoratedIndex( numberofarray );
    STIF_ASSERT_EQUALS( KThree, numberofarray );
    STIF_ASSERT_FALSE( flag );
    
    decorator->SetActive( ETrue );
    count = decorator->MdcaCount();
    STIF_ASSERT_EQUALS( KFour, count );
    
    TPtrC returnText = decorator->MdcaPoint( KZero );
    STIF_ASSERT_TRUE( returnText == tom );
    
    CleanupStack::PopAndDestroy( arr );
    CleanupStack::PopAndDestroy( decorator );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesArrayDecoratorSetDecorationTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesArrayDecoratorSetDecorationTextL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesArrayDecoratorSetArrayL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesArrayDecoratorSetActiveL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesArrayDecoratorSetActiveL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesArrayDecoratorSetArrayL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesArrayDecoratorDecoratedIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesArrayDecoratorDecoratedIndexL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesArrayDecoratorSetArrayL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesArrayDecoratorMdcaCountL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesArrayDecoratorMdcaCountL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesArrayDecoratorSetArrayL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesArrayDecoratorMdcaPointL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesArrayDecoratorMdcaPointL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesArrayDecoratorSetArrayL( aItem );
    return err;
    }

//End file

