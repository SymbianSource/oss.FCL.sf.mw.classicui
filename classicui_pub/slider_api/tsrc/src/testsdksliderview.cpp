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
* Description:  slider_api
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

#include "testsdksliderview.h"
#include "testsdkslidercontainer.h"


// -----------------------------------------------------------------------------
// CSliderView::CSliderView
// -----------------------------------------------------------------------------
//
CSliderView::CSliderView()
    {
    iSliderContainer = NULL;
    }


// -----------------------------------------------------------------------------
// CSliderView::~CSliderView
// -----------------------------------------------------------------------------
//
CSliderView::~CSliderView()
    {
    delete iSliderContainer;
    iSliderContainer = NULL;
    }
// -----------------------------------------------------------------------------
// CSliderView::NewL
// -----------------------------------------------------------------------------
//
CSliderView* CSliderView::NewL()
    {
    CSliderView* self = CSliderView::NewLC();
    CleanupStack::Pop(self);
    return self;
    }

// -----------------------------------------------------------------------------
// CSliderView::NewLC
// -----------------------------------------------------------------------------
//
CSliderView* CSliderView::NewLC()
    {
    CSliderView* self = new ( ELeave ) CSliderView();
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

// -----------------------------------------------------------------------------
// CSliderView::ConstructL
// -----------------------------------------------------------------------------
//
void CSliderView::ConstructL()
    {

    }
// -----------------------------------------------------------------------------
// CSliderView::Id
// -----------------------------------------------------------------------------
//
TUid CSliderView::Id() const
    {
    return TUid::Uid(1);
    }

// -----------------------------------------------------------------------------
// CSliderView::HandleCommandL
// -----------------------------------------------------------------------------
//
void CSliderView::HandleCommandL(TInt aCommand)
    {
    switch ( aCommand )
            {
            default:
                break;
            }

    }
// -----------------------------------------------------------------------------
// CSliderView::DoActivateL
// -----------------------------------------------------------------------------
//
void CSliderView::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
        TUid /*aCustomMessageId*/, const TDesC8& /*aCustomMessage*/)
    {

    }
// -----------------------------------------------------------------------------
// CSliderView::DoDeactivate
// -----------------------------------------------------------------------------
//
void CSliderView::DoDeactivate()
    {

    }
// -----------------------------------------------------------------------------
// CSliderView::HandleStatusPaneSizeChange
// -----------------------------------------------------------------------------
//
void CSliderView::HandleStatusPaneSizeChange()
    {


    }
// -----------------------------------------------------------------------------
// CSliderView::SetupStatusPaneL
// -----------------------------------------------------------------------------
//
void CSliderView::SetupStatusPaneL()
    {

      

    }
// -----------------------------------------------------------------------------
// CSliderView::CleanupStatusPane
// -----------------------------------------------------------------------------
//

void CSliderView::CleanupStatusPane()
    {
    }

// -----------------------------------------------------------------------------
// CSliderView::CreateContainerL
// -----------------------------------------------------------------------------
//
CSliderContainer* CSliderView::CreateContainerL()
    {
    return NULL;
    }

