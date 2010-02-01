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
* Description:  volume_control_api
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



#include "testsdkvolumeview.h"
#include "testsdkvolumecontainer.h"


// -----------------------------------------------------------------------------
// CVolumeControlView::CVolumeControlView
// -----------------------------------------------------------------------------
//
CVolumeControlView::CVolumeControlView()
    {

    iVolumeControlContainer = NULL;


    }

// -----------------------------------------------------------------------------
// CVolumeControlView::~CVolumeControlView
// -----------------------------------------------------------------------------
//
CVolumeControlView::~CVolumeControlView()
    {

    delete iVolumeControlContainer;
    iVolumeControlContainer = NULL;

    }

// -----------------------------------------------------------------------------
// CVolumeControlView::NewL
// -----------------------------------------------------------------------------
//
CVolumeControlView* CVolumeControlView::NewL()
    {
    CVolumeControlView* self = CVolumeControlView::NewLC();
    CleanupStack::Pop(self);
    return self;
    }
// -----------------------------------------------------------------------------
// CVolumeControlView::NewLC
// -----------------------------------------------------------------------------
//
CVolumeControlView* CVolumeControlView::NewLC()
    {
    CVolumeControlView* self = new ( ELeave ) CVolumeControlView();
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }
// -----------------------------------------------------------------------------
// CVolumeControlView::ConstructL
// -----------------------------------------------------------------------------
//
void CVolumeControlView::ConstructL()
    {

    }
// -----------------------------------------------------------------------------
// CVolumeControlView::Id
// -----------------------------------------------------------------------------
//
TUid CVolumeControlView::Id() const
    {
    return TUid::Uid(1);
    }

// -----------------------------------------------------------------------------
// CVolumeControlView::HandleCommandL
// -----------------------------------------------------------------------------
//
void CVolumeControlView::HandleCommandL(TInt aCommand)
    {
    switch ( aCommand )
            {
            default:
                break;
            }

    }

// -----------------------------------------------------------------------------
// CVolumeControlView::DoActivateL
// -----------------------------------------------------------------------------
//
void CVolumeControlView::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
        TUid /*aCustomMessageId*/, const TDesC8& /*aCustomMessage*/)
    {

    }
// -----------------------------------------------------------------------------
// CVolumeControlView::DoDeactivate
// -----------------------------------------------------------------------------
//
void CVolumeControlView::DoDeactivate()
    {

    }

// -----------------------------------------------------------------------------
// CVolumeControlView::HandleStatusPaneSizeChange
// -----------------------------------------------------------------------------
//
void CVolumeControlView::HandleStatusPaneSizeChange()
    {


    }
// -----------------------------------------------------------------------------
// CVolumeControlView::SetupStatusPaneL
// -----------------------------------------------------------------------------
//
void CVolumeControlView::SetupStatusPaneL()
    {

      

    }

// -----------------------------------------------------------------------------
// CVolumeControlView::CleanupStatusPane
// -----------------------------------------------------------------------------
//
void CVolumeControlView::CleanupStatusPane()
    {
    }

// -----------------------------------------------------------------------------
// CVolumeControlView::CreateContainerL
// -----------------------------------------------------------------------------
//
CVolumeControlContainer* CVolumeControlView::CreateContainerL()
    {
    return iVolumeControlContainer;
    }

