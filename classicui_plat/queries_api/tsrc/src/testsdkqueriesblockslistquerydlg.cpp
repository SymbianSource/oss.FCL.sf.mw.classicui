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
* Description:  Test aknlistquerydialog.h
*
*/

//INCLUDE
#include <aknlistquerydialog.h>
#include <testsdkqueries.rsg>
#include <akniconutils.h>
#include <akniconarray.h>
#include <avkon.mbg>
#include <gulicon.h>
#include <eikdialg.h>


#include "testsdkqueries.h"
#include "testsdkqueriescontainer.h"
#include "testsdkaknlistquerydialogprotected.h"
#include "testsdkdialogmediatorobserver.h"

const TInt KZero = 0;
const TInt KOne = 1;
const TInt KTwo = 2;
const TInt KThree = 3;
const TInt KFive = 5;
const TInt KTen = 10;

_LIT( KTestMbmFile,"\\resource\\apps\\avkon2.mbm" );

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqdlgConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqdlgConstructorL( CStifItemParser& /*aItem*/ )
    {
    TInt mIndex = KZero;
    CAknListQueryDialog* dlg = new( ELeave ) CAknListQueryDialog( &mIndex );
    CleanupStack::PushL( dlg );
    STIF_ASSERT_NOT_NULL( dlg );
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqdlgConstructorLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqdlgConstructorLL( CStifItemParser& /*aItem*/ )
    {
    CArrayFixFlat< TInt >* selArray = new( ELeave )CArrayFixFlat< TInt >( KFive );
    CleanupStack::PushL( selArray );
    selArray->AppendL( KOne );
    selArray->AppendL( KThree );
    CAknListQueryDialog* dlg = new( ELeave ) CAknListQueryDialog( selArray );
    CleanupStack::PushL( dlg );
    STIF_ASSERT_NOT_NULL( dlg );
    CleanupStack::PopAndDestroy( dlg );
    CleanupStack::Pop( selArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqcConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqdlgDestructorL( CStifItemParser& /*aItem*/ )
    {
    TInt mIndex = KZero;
    CAknListQueryDialog* dlg = new( ELeave ) CAknListQueryDialog( &mIndex );
    CleanupStack::PushL( dlg );
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }
//There is a problm here
// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqcConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqdlgSetSizeAndPositionL( CStifItemParser& /*aItem*/ )
    {
    TInt selectedOption( KZero );
    
    CDesCArrayFlat* mArray = new (ELeave) CDesCArrayFlat( KTen );
    CleanupStack::PushL(mArray);
     
    TBuf< KTen > palabra;
    for (TInt num = KZero; num< KTen; num++)
        {
       palabra.Format(_L("option %d"), num);
       mArray->AppendL(palabra);
        }
     
    CTestCAknListQueryDialog* dlg = new( ELeave ) CTestCAknListQueryDialog( &selectedOption );
    dlg->PrepareLC( R_UPDATE_QUERY_DIALOG );
    dlg->SetItemTextArray( mArray );
    dlg->SetOwnershipType( ELbmDoesNotOwnItemArray );
    
    dlg->PreLayoutDynInitL();
    TSize size = iContainer->Rect().Size();
    dlg->SetSizeAndPosition( size );
    
    CleanupStack::PopAndDestroy( dlg );
    CleanupStack::PopAndDestroy( mArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqcConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqdlgOfferKeyEventL( CStifItemParser& /*aItem*/ )
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
    dlg->PrepareLC( R_UPDATE_QUERY_DIALOG );
    dlg->SetItemTextArray( mArray );
    dlg->SetOwnershipType( ELbmDoesNotOwnItemArray );
    
    TKeyEvent event;
    event.iCode = EKeyEscape;
    dlg->OfferKeyEventL( event, EEventKey );
    
    CleanupStack::Pop( dlg );
    CleanupStack::PopAndDestroy( mArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqdlgHandleListBoxEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqdlgHandleListBoxEventL( CStifItemParser& /*aItem*/ )
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
    dlg->PrepareLC( R_UPDATE_QUERY_DIALOG );
    dlg->SetItemTextArray( mArray );
    dlg->SetOwnershipType( ELbmDoesNotOwnItemArray );
    
    CEikTextListBox* listBox = new( ELeave ) CEikTextListBox; 
    CleanupStack::PushL( listBox ); 
    CAknPopupList* popupList = CAknPopupList::NewL( listBox, R_AVKON_SOFTKEYS_OK_BACK );
    CleanupStack::PushL( popupList ); 
    listBox->ConstructL( popupList, CEikListBox::ELeftDownInViewRect ); 
    
    dlg->HandleListBoxEventL( listBox, MEikListBoxObserver::EEventEnterKeyPressed );
    dlg->HandleListBoxEventL( listBox, MEikListBoxObserver::EEventPenDownOnItem );
    dlg->HandleListBoxEventL( listBox, MEikListBoxObserver::EEventItemDraggingActioned );
    dlg->HandleListBoxEventL( listBox, MEikListBoxObserver::EEventItemClicked );
    dlg->HandleListBoxEventL( listBox, MEikListBoxObserver::EEventEditingStarted );
    
    CleanupStack::Pop( popupList );
    CleanupStack::PopAndDestroy( listBox );
    CleanupStack::PopAndDestroy( dlg );
    CleanupStack::PopAndDestroy( mArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqdlgSetItemTextArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqdlgSetItemTextArrayL( CStifItemParser& aItem )
    {
    TInt err = TestLqdlgHandleListBoxEventL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqdlgSetOwnershipTypeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqdlgSetOwnershipTypeL( CStifItemParser& aItem )
    {
    TInt err = TestLqdlgHandleListBoxEventL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqdlgSetIconArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqdlgSetIconArrayL( CStifItemParser& /*aItem*/ )
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
    dlg->PrepareLC( R_UPDATE_QUERY_DIALOG );
    dlg->SetItemTextArray( mArray );
    dlg->SetOwnershipType( ELbmDoesNotOwnItemArray );
    
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 
    
    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KFive ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    
    dlg->SetIconArrayL( mIcons );
    
    CleanupStack::Pop( mIcon );
    CleanupStack::Pop( KThree );
    CleanupStack::PopAndDestroy( dlg );
    CleanupStack::Pop( KOne );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqdlgListBoxL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqdlgListBoxL( CStifItemParser& /*aItem*/ )
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
    dlg->PrepareLC( R_UPDATE_QUERY_DIALOG );
    dlg->SetItemTextArray( mArray );
    dlg->SetOwnershipType( ELbmDoesNotOwnItemArray );
    
    CEikListBox* listBox = dlg->ListBox();
    STIF_ASSERT_NOT_NULL( listBox );
    
    CleanupStack::PopAndDestroy( dlg );
    CleanupStack::PopAndDestroy( mArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqdlgListControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqdlgListControlL( CStifItemParser& /*aItem*/ )
    {
    TInt selectedOption( KZero );
    CAknListQueryDialog* dlg = new( ELeave ) CAknListQueryDialog( &selectedOption );
    
    CAknListQueryControl* listControl = dlg->ListControl();
    STIF_ASSERT_NULL( listControl );
    
    CDesCArrayFlat* mArray = new (ELeave) CDesCArrayFlat( KTen );
    CleanupStack::PushL( mArray );
     
    TBuf< KTen > palabra;
    for (TInt num = KZero; num< KTen; num++)
        {
       palabra.Format(_L("option %d"), num);
       mArray->AppendL(palabra);
        }
     
    dlg->PrepareLC( R_UPDATE_QUERY_DIALOG );
    dlg->SetItemTextArray( mArray );
    dlg->SetOwnershipType( ELbmDoesNotOwnItemArray );
    
    listControl = dlg->ListControl();
    STIF_ASSERT_NOT_NULL( listControl );
    
    CleanupStack::PopAndDestroy( dlg );
    CleanupStack::PopAndDestroy( mArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqcConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqdlgMessageBoxL( CStifItemParser& /*aItem*/ )
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
    dlg->PrepareLC( R_UPDATE_QUERY_DIALOG );
    dlg->SetItemTextArray( mArray );
    dlg->SetOwnershipType( ELbmDoesNotOwnItemArray );
    
    CAknMessageQueryControl* msgBox = dlg->MessageBox();
    STIF_ASSERT_NULL( msgBox );
    
    CleanupStack::Pop( dlg );
    
    dlg = new( ELeave ) CAknListQueryDialog( &selectedOption );
    dlg->PrepareLC( R_UPDATE_QUERY_MSG_DIALOG );
    dlg->SetItemTextArray( mArray );
    dlg->SetOwnershipType( ELbmDoesNotOwnItemArray );
    
    msgBox = dlg->MessageBox();
    STIF_ASSERT_NOT_NULL( msgBox );
    
    CleanupStack::PopAndDestroy( dlg );
    CleanupStack::PopAndDestroy( mArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqcConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqdlgQueryHeadingL( CStifItemParser& /*aItem*/ )
    {
    TInt selectedOption( KZero );
    CAknListQueryDialog* dlg = new( ELeave ) CAknListQueryDialog( &selectedOption );
    
    CAknPopupHeadingPane* heading = dlg->QueryHeading();
    STIF_ASSERT_NULL( heading );
    
    CDesCArrayFlat* mArray = new (ELeave) CDesCArrayFlat( KTen );
    CleanupStack::PushL( mArray );
     
    TBuf< KTen > palabra;
    for (TInt num = KZero; num< KTen; num++)
        {
       palabra.Format(_L("option %d"), num);
       mArray->AppendL(palabra);
        }
     
    dlg->PrepareLC( R_UPDATE_QUERY_DIALOG );
    dlg->SetItemTextArray( mArray );
    dlg->SetOwnershipType( ELbmDoesNotOwnItemArray );
    
    heading = dlg->QueryHeading();
    STIF_ASSERT_NOT_NULL( heading );
    
    CleanupStack::PopAndDestroy( dlg );
    CleanupStack::PopAndDestroy( mArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqcConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqdlgActivateL( CStifItemParser& /*aItem*/ )
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
    dlg->PrepareLC( R_UPDATE_QUERY_DIALOG );
    dlg->SetOwnershipType( ELbmDoesNotOwnItemArray );
    
    dlg->ActivateL();
    
    dlg->SetItemTextArray( mArray );
    
    CleanupStack::PopAndDestroy( dlg );
    CleanupStack::PopAndDestroy( mArray );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqdlgHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqdlgHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    TInt selectedOption( KZero );
    CAknListQueryDialog* dlg = new( ELeave ) CAknListQueryDialog( &selectedOption );
    
    CDesCArrayFlat* mArray = new (ELeave) CDesCArrayFlat( KTen );
    CleanupStack::PushL( mArray );
     
    TBuf< KTen > palabra;
    for (TInt num = KZero; num< KTen; num++)
        {
       palabra.Format(_L("option %d"), num);
       mArray->AppendL(palabra);
        }
     
    dlg->PrepareLC( R_UPDATE_QUERY_DIALOG );
    dlg->SetItemTextArray( mArray );
    dlg->SetOwnershipType( ELbmDoesNotOwnItemArray );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = KZero;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    TInt err = KErrNone;
    TRAP( err, dlg->HandlePointerEventL( event ) );
    
    CleanupStack::PopAndDestroy( dlg );
    CleanupStack::PopAndDestroy( mArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqdlgPreLayoutDynInitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqdlgPreLayoutDynInitL( CStifItemParser& /*aItem*/ )
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
     
    CTestCAknListQueryDialog* dlg = new( ELeave ) CTestCAknListQueryDialog( &selectedOption );
    dlg->PrepareLC( R_UPDATE_QUERY_DIALOG );
    dlg->SetItemTextArray( mArray );
    dlg->SetOwnershipType( ELbmDoesNotOwnItemArray );
    
    TInt err = KErrNone;
    TRAP( err, dlg->PreLayoutDynInitL() );
    
    CleanupStack::PopAndDestroy( dlg );
    CleanupStack::PopAndDestroy( mArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqdlgPostLayoutDynInitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqdlgPostLayoutDynInitL( CStifItemParser& /*aItem*/ )
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
     
    CTestCAknListQueryDialog* dlg = new( ELeave ) CTestCAknListQueryDialog( &selectedOption );
    dlg->PrepareLC( R_UPDATE_QUERY_DIALOG );
    dlg->SetItemTextArray( mArray );
    dlg->SetOwnershipType( ELbmDoesNotOwnItemArray );
    
    TInt err = KErrNone;
    TRAP( err, dlg->PostLayoutDynInitL());
    
    CleanupStack::PopAndDestroy( dlg );
    CleanupStack::PopAndDestroy( mArray );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqdlgOkToExitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqdlgOkToExitL( CStifItemParser& /*aItem*/ )
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
     
    CTestCAknListQueryDialog* dlg = new( ELeave ) CTestCAknListQueryDialog( &selectedOption );
    dlg->PrepareLC( R_UPDATE_QUERY_DIALOG );
    dlg->SetItemTextArray( mArray );
    dlg->SetOwnershipType( ELbmDoesNotOwnItemArray );
    
    TInt err = KErrNone;
    TInt buttonId = EAknSoftkeyMark;
    TRAP( err, dlg->OkToExitL( buttonId ));
    
    CleanupStack::PopAndDestroy( dlg );
    CleanupStack::PopAndDestroy( mArray );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqdlgBorderStyleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqdlgBorderStyleL( CStifItemParser& /*aItem*/ )
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
     
    CTestCAknListQueryDialog* dlg = new( ELeave ) CTestCAknListQueryDialog( &selectedOption );
    dlg->PrepareLC( R_UPDATE_QUERY_DIALOG );
    dlg->SetItemTextArray( mArray );
    dlg->SetOwnershipType( ELbmDoesNotOwnItemArray );
    
    TInt borderStyle = KZero;
    TInt compareStyle = TGulBorder::ENone;
    borderStyle = dlg->BorderStyle();
    STIF_ASSERT_EQUALS( compareStyle, borderStyle );
    
    CleanupStack::PopAndDestroy( dlg );
    CleanupStack::PopAndDestroy( mArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqdlgCloseStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqdlgCloseStateL( CStifItemParser& /*aItem*/ )
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
     
    CTestCAknListQueryDialog* dlg = new( ELeave ) CTestCAknListQueryDialog( &selectedOption );
    dlg->PrepareLC( R_UPDATE_QUERY_DIALOG );
    dlg->SetItemTextArray( mArray );
    dlg->SetOwnershipType( ELbmDoesNotOwnItemArray );
    
    dlg->CloseState();
    
    CleanupStack::Pop( dlg );
    CleanupStack::PopAndDestroy( mArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqdlgFindBoxL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqdlgFindBoxL( CStifItemParser& /*aItem*/ )
    {
    TInt selectedOption( KZero );
    CTestCAknListQueryDialog* dlg = new( ELeave ) CTestCAknListQueryDialog( &selectedOption );
    
    CAknSearchField* findBox = dlg->FindBox();
    STIF_ASSERT_NULL( findBox );
    
    CDesCArrayFlat* mArray = new (ELeave) CDesCArrayFlat( KTen );
    CleanupStack::PushL( mArray );
     
    TBuf< KTen > palabra;
    for (TInt num = KZero; num< KTen; num++)
        {
       palabra.Format(_L("option %d"), num);
       mArray->AppendL(palabra);
        }
     
    dlg->PrepareLC( R_UPDATE_QUERY_DIALOG );
    dlg->SetItemTextArray( mArray );
    dlg->SetOwnershipType( ELbmDoesNotOwnItemArray );
    
    findBox = dlg->FindBox();
    STIF_ASSERT_NULL( findBox );
    
    CleanupStack::PopAndDestroy( dlg );
    CleanupStack::PopAndDestroy( mArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqdlgSetToneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqdlgSetToneL( CStifItemParser& /*aItem*/ )
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
    dlg->PrepareLC( R_UPDATE_QUERY_DIALOG );
    dlg->SetItemTextArray( mArray );
    dlg->SetOwnershipType( ELbmDoesNotOwnItemArray );
    
    TInt tone = CAknQueryDialog::EConfirmationTone;
    dlg->SetTone( tone );
    
    CleanupStack::PopAndDestroy( dlg );
    CleanupStack::PopAndDestroy( mArray );
    return KErrNone;
    }
//There is a problm here
// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqdlgHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqdlgHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    TInt selectedOption( KZero );
    
    CDesCArrayFlat* mArray = new (ELeave) CDesCArrayFlat(KTen);
    CleanupStack::PushL( mArray );
     
    TBuf< KTen > palabra;
    for (TInt num = KZero; num< KTen; num++)
        {
       palabra.Format(_L("option %d"), num);
       mArray->AppendL(palabra);
        }
     
    CTestCAknListQueryDialog* dlg = new( ELeave ) CTestCAknListQueryDialog( &selectedOption );
    dlg->PrepareLC( R_UPDATE_QUERY_MSG_DIALOG );
    dlg->SetItemTextArray( mArray );
    dlg->SetOwnershipType( ELbmDoesNotOwnItemArray );
    
    dlg->PreLayoutDynInitL();
    dlg->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    
    CleanupStack::PopAndDestroy( dlg );
    CleanupStack::PopAndDestroy( mArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqdlgPublishDialogL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqdlgPublishDialogL( CStifItemParser& /*aItem*/ )
    {
    TInt selectedOption( KZero );
    
    CDesCArrayFlat* mArray = new (ELeave) CDesCArrayFlat(KTen);
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
    
    CArrayFixFlat< TInt >* selArray = new( ELeave )CArrayFixFlat< TInt >( KFive );
    CleanupStack::PushL( selArray );
    selArray->AppendL( KOne );
    selArray->AppendL( KThree );
    
    TInt err = KErrNone;
    TRAP( err, dlg->PublishDialogL( KOne, KNullUid, selArray ));
    
    CleanupStack::Pop( KOne );
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestLqdlgSetMediatorObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestLqdlgSetMediatorObserverL( CStifItemParser& /*aItem*/ )
    {
    TInt selectedOption( KZero );
    
    CDesCArrayFlat* mArray = new (ELeave) CDesCArrayFlat(KTen);
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
    
    CTestDialogMediatorObserver* observer = new( ELeave ) CTestDialogMediatorObserver;
    dlg->SetMediatorObserver( observer );
    
    CleanupStack::PopAndDestroy( dlg );
    CleanupStack::PopAndDestroy( mArray );
    return KErrNone;
    }

//End file


