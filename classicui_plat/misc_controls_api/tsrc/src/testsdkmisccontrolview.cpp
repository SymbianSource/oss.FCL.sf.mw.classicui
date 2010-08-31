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
* Description:  misc_control_api
 *
*/

#include <aknviewappui.h>
#include <eikmenub.h>
#include <avkon.hrh>
#include <akncontext.h>
#include <akntitle.h>
#include <stringloader.h>
#include <barsread.h>
#include <eikbtgpc.h>



#include "testsdkmisccontrolview.h"
#include "testsdkmisccontrolcontainer.h"


// -----------------------------------------------------------------------------
// CMiscControlView::CMiscControlView
// -----------------------------------------------------------------------------
//
CMiscControlView::CMiscControlView()
    {

    iMiscControlContainer = NULL;


    }

// -----------------------------------------------------------------------------
// CMiscControlView::~CMiscControlView
// -----------------------------------------------------------------------------
//
CMiscControlView::~CMiscControlView()
    {

    delete iMiscControlContainer;
    iMiscControlContainer = NULL;

    }

// -----------------------------------------------------------------------------
// CMiscControlView::NewL
// -----------------------------------------------------------------------------
//
CMiscControlView* CMiscControlView::NewL()
    {
    CMiscControlView* self = CMiscControlView::NewLC();
    CleanupStack::Pop(self);
    return self;
    }
// -----------------------------------------------------------------------------
// CMiscControlView::NewLC
// -----------------------------------------------------------------------------
//
CMiscControlView* CMiscControlView::NewLC()
    {
    CMiscControlView* self = new ( ELeave ) CMiscControlView();
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }
// -----------------------------------------------------------------------------
// CMiscControlView::ConstructL
// -----------------------------------------------------------------------------
//
void CMiscControlView::ConstructL()
    {

    }
// -----------------------------------------------------------------------------
// CMiscControlView::Id
// -----------------------------------------------------------------------------
//
TUid CMiscControlView::Id() const
    {
    return TUid::Uid(1);
    }

// -----------------------------------------------------------------------------
// CMiscControlView::HandleCommandL
// -----------------------------------------------------------------------------
//
void CMiscControlView::HandleCommandL(TInt aCommand)
    {
    switch ( aCommand )
            {
            default:
                break;
            }

    }

// -----------------------------------------------------------------------------
// CMiscControlView::DoActivateL
// -----------------------------------------------------------------------------
//
void CMiscControlView::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
        TUid /*aCustomMessageId*/, const TDesC8& /*aCustomMessage*/)
    {

    }
// -----------------------------------------------------------------------------
// CMiscControlView::DoDeactivate
// -----------------------------------------------------------------------------
//
void CMiscControlView::DoDeactivate()
    {

    }

// -----------------------------------------------------------------------------
// CMiscControlView::HandleStatusPaneSizeChange
// -----------------------------------------------------------------------------
//
void CMiscControlView::HandleStatusPaneSizeChange()
    {


    }
// -----------------------------------------------------------------------------
// CMiscControlView::SetupStatusPaneL
// -----------------------------------------------------------------------------
//
void CMiscControlView::SetupStatusPaneL()
    {

      

    }

// -----------------------------------------------------------------------------
// CMiscControlView::CleanupStatusPane
// -----------------------------------------------------------------------------
//
void CMiscControlView::CleanupStatusPane()
    {
    }

// -----------------------------------------------------------------------------
// CMiscControlView::CreateContainerL
// -----------------------------------------------------------------------------
//
CMiscControlsContainer* CMiscControlView::CreateContainerL()
    {
    return iMiscControlContainer;
    }

