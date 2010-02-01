/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include "bctestmisc32.hrh"
#include <bctestmisc32.rsg>
#include "bctestmisc32view.h"
#include "bctestmisc32container.h"
#include "bctestutil.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestmisc32View* CBCTestmisc32View::NewL(CBCTestUtil* aUtil)
    {
    CBCTestmisc32View* self = new( ELeave ) CBCTestmisc32View();
    CleanupStack::PushL( self );
    self->ConstructL(aUtil);
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestmisc32View::CBCTestmisc32View()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestmisc32View::ConstructL(CBCTestUtil* aUtil)
    {
    BaseConstructL( R_BCTESTMISC32_VIEW );

    iContainer = new( ELeave ) CBCTestmisc32Container();
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
CBCTestmisc32View::~CBCTestmisc32View()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    }

// ---------------------------------------------------------------------------
// CBCTestmisc32View::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestmisc32View::Id() const
    {
    return KBCTestmisc32ViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestmisc32View::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestmisc32View::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestmisc32View::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestmisc32View::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestmisc32View::Container
// ---------------------------------------------------------------------------
//
CBCTestmisc32Container* CBCTestmisc32View::Container()
    {
	return iContainer;
    }

// ---------------------------------------------------------------------------
// CBCTestmisc32View::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestmisc32View::HandleCommandL( TInt aCommand )
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
