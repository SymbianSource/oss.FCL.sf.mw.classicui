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
* Description:  Test aknmessagequerycontrol.h
*
*/

//INCLUDE
#include <aknmessagequerycontrol.h>
#include <aknlistquerydialog.h>
#include <testsdkqueries.rsg>
#include <barsread.h>

#include "testsdkqueries.h"
#include "testsdkqueriescontainer.h"
#include "testsdkaknmessagequerycontrolprotected.h"

const TInt KZero = 0;
const TInt KOne = 1;
const TInt KTen = 10;

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqcConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMqcConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    TInt selectedOption( KZero );
        
    CDesCArrayFlat* mArray = new (ELeave) CDesCArrayFlat( KTen );
    CleanupStack::PushL( mArray );
     
    TBuf< KTen > palabra;
    for (TInt num = KZero; num< KTen; num++)
        {
       palabra.Format(_L("option %d"), num);
       mArray->AppendL(palabra);
        }
     
    CAknListQueryDialog* dlg = new( ELeave ) CAknListQueryDialog( &selectedOption );
    dlg->PrepareLC( R_UPDATE_QUERY_MSG_DIALOG );
    dlg->SetItemTextArray( mArray );
    dlg->SetOwnershipType( ELbmDoesNotOwnItemArray );
    
    CAknMessageQueryControl* msgBox = dlg->MessageBox();
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_MESSAGE );
    
    msgBox->ConstructFromResourceL( reader );
    
    CleanupStack::PopAndDestroy( KOne );
    CleanupStack::PopAndDestroy( dlg );
    CleanupStack::Pop( mArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqcSetMessageTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMqcSetMessageTextL( CStifItemParser& aItem )
    {
    TInt err = TestMqcConstructFromResourceL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqcLinkHighLightedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMqcLinkHighLightedL( CStifItemParser& /*aItem*/ )
    {
    TInt selectedOption( KZero );
        
    CDesCArrayFlat* mArray = new (ELeave) CDesCArrayFlat( KTen );
    CleanupStack::PushL( mArray );
     
    TBuf< KTen > palabra;
    for (TInt num = KZero; num< KTen; num++)
        {
       palabra.Format(_L("option %d"), num);
       mArray->AppendL(palabra);
        }
     
    CAknListQueryDialog* dlg = new( ELeave ) CAknListQueryDialog( &selectedOption );
    dlg->PrepareLC( R_UPDATE_QUERY_MSG_DIALOG );
    dlg->SetItemTextArray( mArray );
    dlg->SetOwnershipType( ELbmDoesNotOwnItemArray );
    
    CAknMessageQueryControl* msgBox = dlg->MessageBox();
    
    TBool flag = msgBox->LinkHighLighted();
    STIF_ASSERT_FALSE( flag );
    
    CleanupStack::PopAndDestroy( dlg );
    CleanupStack::Pop( mArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqcDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMqcDrawL( CStifItemParser& /*aItem*/ )
    {
    TInt selectedOption( KZero );
        
    CDesCArrayFlat* mArray = new (ELeave) CDesCArrayFlat( KTen );
    CleanupStack::PushL( mArray );
     
    TBuf< KTen > palabra;
    for (TInt num = KZero; num< KTen; num++)
        {
       palabra.Format(_L("option %d"), num);
       mArray->AppendL(palabra);
        }
     
    CAknListQueryDialog* dlg = new( ELeave ) CAknListQueryDialog( &selectedOption );
    dlg->PrepareLC( R_UPDATE_QUERY_MSG_DIALOG );
    dlg->SetItemTextArray( mArray );
    dlg->SetOwnershipType( ELbmDoesNotOwnItemArray );
    
    CTestCAknMessageQueryControl* msgBox = static_cast<CTestCAknMessageQueryControl*>( dlg->MessageBox());

    msgBox->Draw( iContainer->Rect() );
    
    CleanupStack::PopAndDestroy( dlg );
    CleanupStack::PopAndDestroy( mArray );
    return KErrNone;
    }

//End file


