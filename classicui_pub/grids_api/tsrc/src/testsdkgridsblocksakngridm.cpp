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
* Description:  Test akngridm.h
*
*/


/*
 * Include files
 */
#include <akngridm.h>
#include <badesca.h>

#include "testsdkgrids.h"

const TInt KSize = 5;
const TInt KThree = 3;
const TInt KSix = 6;
const TInt KFour = 4;
const TInt KZero = 0;

_LIT(KTom, "Tom");
_LIT(KJack, "Jack");
_LIT(KMary, "Mary");

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridmConstructorAndDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridmConstructorAndDestructorL( CStifItemParser& /*aItem*/ )
    {
    CAknGridM* grid = new( ELeave ) CAknGridM;
    CleanupStack::PushL( grid );
    STIF_ASSERT_NOT_NULL( grid );

    CleanupStack::PopAndDestroy( grid );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridmNumberOfItemsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridmNumberOfItemsL( CStifItemParser& /*aItem*/ )
    {
    CAknGridM* grid = new( ELeave ) CAknGridM;
    CleanupStack::PushL( grid );

    CDesCArrayFlat* arr = new( ELeave ) CDesCArrayFlat( KSize );
    CleanupStack::PushL( arr );

    HBufC* buf1 = KTom().AllocLC();
    HBufC* buf2 = KJack().AllocLC();
    HBufC* buf3 = KMary().AllocLC();
    
    arr->AppendL(*buf1);
    arr->AppendL(*buf2);
    arr->AppendL(*buf3);

    grid->SetItemTextArray( arr );

    TInt numberofitem = grid->NumberOfItems();
    STIF_ASSERT_EQUALS( numberofitem, KThree );

    grid->SetStartCells( KThree );
    numberofitem = grid->NumberOfItems();
    STIF_ASSERT_EQUALS( KSix, numberofitem );

    CleanupStack::PopAndDestroy( buf3 );
    CleanupStack::PopAndDestroy( buf2 );
    CleanupStack::PopAndDestroy( buf1 );
    CleanupStack::Pop( arr );
    CleanupStack::PopAndDestroy( grid );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridmIndexContainsDataL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridmIndexContainsDataL( CStifItemParser& /*aItem*/ )
    {
    CAknGridM* grid = new( ELeave ) CAknGridM;
    CleanupStack::PushL( grid );

    CDesCArrayFlat* arr = new(ELeave)CDesCArrayFlat(KSize);
    CleanupStack::PushL( arr );

    HBufC* buf1 = KTom().AllocLC();
    HBufC* buf2 = KJack().AllocLC();
    HBufC* buf3 = KMary().AllocLC();

    arr->AppendL(*buf1);
    arr->AppendL(*buf2);
    arr->AppendL(*buf3);

    grid->SetItemTextArray( arr );

    TBool flag = grid->IndexContainsData( KThree );
    STIF_ASSERT_FALSE( flag );

    flag = grid->IndexContainsData( KSix );
    STIF_ASSERT_FALSE( flag );

    grid->SetStartCells( KThree );
    flag = grid->IndexContainsData( KSix );
    STIF_ASSERT_FALSE( flag );

    flag = grid->IndexContainsData( KThree );
    STIF_ASSERT_TRUE( flag );

    flag = grid->IndexContainsData( KFour );
    STIF_ASSERT_TRUE( flag );

    CleanupStack::PopAndDestroy( buf3 );
    CleanupStack::PopAndDestroy( buf2 );
    CleanupStack::PopAndDestroy( buf1 );
    CleanupStack::Pop( arr );
    CleanupStack::PopAndDestroy( grid );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridmNumberOfDataL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridmNumberOfDataL( CStifItemParser& /*aItem*/ )
    {
    CAknGridM* grid = new( ELeave ) CAknGridM;
    CleanupStack::PushL( grid );

    CDesCArrayFlat* arr = new(ELeave)CDesCArrayFlat(KSize);
    CleanupStack::PushL( arr );

    HBufC* buf1 = KTom().AllocLC();
    HBufC* buf2 = KJack().AllocLC();
    HBufC* buf3 = KMary().AllocLC();

    arr->AppendL(*buf1);
    arr->AppendL(*buf2);
    arr->AppendL(*buf3);

    grid->SetItemTextArray( arr );

    TInt numberofdata = grid->NumberOfData();
    STIF_ASSERT_EQUALS( KThree, numberofdata );

    CleanupStack::PopAndDestroy( buf3 );
    CleanupStack::PopAndDestroy( buf2 );
    CleanupStack::PopAndDestroy( buf1 );
    CleanupStack::Pop( arr );
    CleanupStack::PopAndDestroy( grid );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridmSetStartCellsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridmSetStartCellsL( CStifItemParser& /*aItem*/ )
    {
    CAknGridM* grid = new( ELeave ) CAknGridM;
    CleanupStack::PushL( grid );

    CDesCArrayFlat* arr = new(ELeave)CDesCArrayFlat(KSize);
    CleanupStack::PushL( arr );

	HBufC* buf1 = KTom().AllocLC();

    arr->AppendL(*buf1);

    grid->SetItemTextArray( arr );

    TInt cells = grid->IndexOfFirstDataItem();
    STIF_ASSERT_EQUALS( KZero, cells );

    grid->SetStartCells( KThree );
    cells = grid->IndexOfFirstDataItem();
    STIF_ASSERT_EQUALS( KThree, cells );

    CleanupStack::PopAndDestroy( buf1 );
    CleanupStack::Pop( arr );
    CleanupStack::PopAndDestroy( grid );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridmIndexOfFirstDataItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridmIndexOfFirstDataItemL( CStifItemParser& /*aItem*/ )
    {
    CAknGridM* grid = new( ELeave ) CAknGridM;
    CleanupStack::PushL( grid );

    grid->SetStartCells( KThree );

    CDesCArrayFlat* arr = new(ELeave)CDesCArrayFlat(KSize);
    CleanupStack::PushL( arr );

    HBufC* buf1 = KTom().AllocLC();

    arr->AppendL(*buf1);

    grid->SetItemTextArray( arr );

    TInt firstdataitemindex = grid->IndexOfFirstDataItem();
    STIF_ASSERT_EQUALS( KThree, firstdataitemindex );

    CleanupStack::PopAndDestroy( buf1 );
    CleanupStack::Pop( arr );
    CleanupStack::PopAndDestroy( grid );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridmIndexOfLastDataItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridmIndexOfLastDataItemL( CStifItemParser& /*aItem*/ )
    {
    CAknGridM* grid = new( ELeave ) CAknGridM;
    CleanupStack::PushL( grid );

    CDesCArrayFlat* arr = new(ELeave)CDesCArrayFlat(KSize);
    CleanupStack::PushL( arr );

    HBufC* buf1 = KTom().AllocLC();

    arr->AppendL(*buf1);

    grid->SetItemTextArray( arr );

    TInt lastdataitemindex = grid->IndexOfLastDataItem();
    STIF_ASSERT_EQUALS( KZero, lastdataitemindex );

    grid->SetStartCells( KThree );

    lastdataitemindex = grid->IndexOfLastDataItem();
    STIF_ASSERT_EQUALS( KThree, lastdataitemindex );

    CleanupStack::PopAndDestroy( buf1 );
    CleanupStack::Pop( arr );
    CleanupStack::PopAndDestroy( grid );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKGrids::TestGridsGridmItemTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::TestGridsGridmItemTextL( CStifItemParser& /*aItem*/ )
    {   
    CAknGridM* grid = new( ELeave ) CAknGridM;
    CleanupStack::PushL( grid );

    CDesCArrayFlat* arr = new(ELeave)CDesCArrayFlat(KSize);
    CleanupStack::PushL( arr );

    HBufC* buf1 = KTom().AllocLC();

    arr->AppendL(*buf1);

    grid->SetItemTextArray( arr );

    TBufC<10> buf ( KTom ); 
    TPtrC comparetext( buf );
    TPtrC returntext = grid->ItemText( KZero );
    STIF_ASSERT_EQUALS( comparetext, returntext );

    grid->SetStartCells( KThree );
    TPtrC returntexttwo = grid->ItemText( KThree );
    STIF_ASSERT_EQUALS( comparetext, returntexttwo );

    CleanupStack::PopAndDestroy( buf1 );
    CleanupStack::Pop( arr );
    CleanupStack::PopAndDestroy( grid );
    return KErrNone;
    }

/*
 * End files
 */
