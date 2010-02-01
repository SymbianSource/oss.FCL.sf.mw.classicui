/*
* Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         view class
*
*/









#include <aknviewappui.h>

#include "bctestuniteditor.hrh"
#include <bctestuniteditor.rsg>
#include "bctestuniteditorview.h"
#include "bctestuniteditorcontainer.h"
#include "bctestutil.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestUnitEditorView* CBCTestUnitEditorView::NewL(CBCTestUtil* aUtil)
    {
    CBCTestUnitEditorView* self = new( ELeave ) CBCTestUnitEditorView();
    CleanupStack::PushL( self );
    self->ConstructL(aUtil);
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestUnitEditorView::CBCTestUnitEditorView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestUnitEditorView::ConstructL(CBCTestUtil* aUtil)
    {
    BaseConstructL( R_BCTESTUNITEDITOR_VIEW );

    iContainer = new( ELeave ) CBCTestUnitEditorContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = aUtil;
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestUnitEditorView::~CBCTestUnitEditorView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    }

// ---------------------------------------------------------------------------
// CBCTestUnitEditorView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestUnitEditorView::Id() const
    {
    return KBCTestUnitEditorViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestUnitEditorView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestUnitEditorView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestUnitEditorView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestUnitEditorView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestUnitEditorView::Container
// ---------------------------------------------------------------------------
//
CBCTestUnitEditorContainer* CBCTestUnitEditorView::Container()
    {
	return iContainer;
    }

// ---------------------------------------------------------------------------
// CBCTestUnitEditorView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestUnitEditorView::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EProgCmdAutoTest:
            iTestUtil->RunL();
            break;
        default:
            if ( aCommand > EBCTestCmdEmptyOutline &&
                 aCommand < EBCTestCmdMaxOutline )
                {
                iTestUtil->RunL( aCommand );
                }
            break;
        }
    }
