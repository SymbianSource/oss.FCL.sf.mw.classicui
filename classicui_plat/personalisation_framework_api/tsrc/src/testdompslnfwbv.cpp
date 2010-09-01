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
* Description:  
*
*/

#include "testdompslnfwbv.h"
#include "testdompslnfwbc.h"

//==============================CTestPslnFWBaseView===========================
//
// ---------------------------------------------------------------------------
// CTestPslnFWBaseView::ConstructL()
// ---------------------------------------------------------------------------
//    
void CTestPslnFWBaseView::ConstructL()
    {
    iContainer = new( ELeave ) CTestPslnFWBaseContainer();
    }

// ---------------------------------------------------------------------------
// CTestPslnFWBaseView::NewContainerL()
// ---------------------------------------------------------------------------
//    
void CTestPslnFWBaseView::NewContainerL()
    {
    if( iContainer )
    delete iContainer;
    iContainer = NULL;
    iContainer = new ( ELeave )CTestPslnFWBaseContainer;
    }

// ---------------------------------------------------------------------------
// CTestPslnFWBaseView::HandleListBoxSelectionL()
// ---------------------------------------------------------------------------
//   
void CTestPslnFWBaseView::HandleListBoxSelectionL()
    { 
    }

// ---------------------------------------------------------------------------
// CTestPslnFWBaseView::GetCaptionL()
// ---------------------------------------------------------------------------
//   
void CTestPslnFWBaseView::GetCaptionL( TDes& /*aCaption*/ ) const
    {  
    }
    
// ---------------------------------------------------------------------------
// CTestPslnFWBaseView::GetTabTextL()
// ---------------------------------------------------------------------------
//   
void CTestPslnFWBaseView::GetTabTextL( TDes& /*aCaption*/ ) const
    {   
    }

// ---------------------------------------------------------------------------
// CGulIcon* CTestPslnFWBaseView::CreateIconL()
// ---------------------------------------------------------------------------
//   
CGulIcon* CTestPslnFWBaseView::CreateIconL()
    {
    return NULL;
    }

// ---------------------------------------------------------------------------
// CTestPslnFWBaseView::SetNaviPaneL()
// ---------------------------------------------------------------------------
//   
void CTestPslnFWBaseView::SetNaviPaneL()
    {
    CPslnFWBaseView::SetNaviPaneL();
    }

// ---------------------------------------------------------------------------
// CTestPslnFWBaseView::CreateNaviPaneContextL()
// ---------------------------------------------------------------------------
//   
void CTestPslnFWBaseView::CreateNaviPaneContextL( TInt aResourceId )
    {
    CPslnFWBaseView::CreateNaviPaneContextL( aResourceId );
    }

// ---------------------------------------------------------------------------
// CTestPslnFWBaseView::CreateContainerL()
// ---------------------------------------------------------------------------
//   
void CTestPslnFWBaseView::CreateContainerL()
    {
    CPslnFWBaseView::CreateContainerL();
    }

// ---------------------------------------------------------------------------
// CTestPslnFWBaseView::SetNaviPaneL()
// ---------------------------------------------------------------------------
//   
void CTestPslnFWBaseView::SetNaviPaneL( const TInt aTabLocation )
    {
    CPslnFWBaseView::SetNaviPaneL( aTabLocation );
    }

// ---------------------------------------------------------------------------
// CTestPslnFWBaseView::SetMiddleSoftKeyLabelL()
// ---------------------------------------------------------------------------
//   
void CTestPslnFWBaseView::SetMiddleSoftKeyLabelL( const TInt aResourceId, const TInt aCommandId )
    {
    CPslnFWBaseView::SetMiddleSoftKeyLabelL( aResourceId, aCommandId );
    }

// ---------------------------------------------------------------------------
// CTestPslnFWBaseView::HandleCommandL()
// ---------------------------------------------------------------------------
//   
void CTestPslnFWBaseView::HandleCommandL( TInt aCommand )
    {
    CPslnFWBaseView::HandleCommandL( aCommand );
    }

// ---------------------------------------------------------------------------
// CTestPslnFWBaseView::SetTitlePaneL()
// ---------------------------------------------------------------------------
//   
void CTestPslnFWBaseView::SetTitlePaneL( TInt& aResourceId )
    {
    CPslnFWBaseView::SetTitlePaneL( aResourceId );
    }
// ---------------------------------------------------------------------------
// CTestPslnFWBaseView::Id()
// ---------------------------------------------------------------------------
//   
TUid CTestPslnFWBaseView::Id() const
    {
    return KNullUid;
    }

