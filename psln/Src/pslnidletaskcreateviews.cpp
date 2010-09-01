/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Background task for creating views.
*
*/


#include "pslnidletaskcreateviews.h"
#include "PslnUi.h"
#include "PslnConst.h"
#include "PslnModel.h"

// First step is to create tabgroup.
const TInt KPslnCreateTabs = 0;
// Second step is to create parts of the model.
const TInt KPslnFullUpdateModel = 1;
// Third  step is to create general theme view.
const TInt KPslnCreateGeneralView = 2;
// Fourth step is to create wallpaper view.
const TInt KPslnCreateWallpaperView = 3;
// Fifth (and final) step is to create screensaver view.
const TInt KPslnCreateScreensaverView = 4;

// ---------------------------------------------------------------------------
// C++ constructor can NOT contain any code, that might leave.
// ---------------------------------------------------------------------------
//
CPslnIdleTaskCreateViews::CPslnIdleTaskCreateViews( CPslnUi* aPslnUi ) :
    iPslnUi( aPslnUi ), iDone( EFalse ), iIdleStep( KPslnCreateTabs )
    {
    }

// -----------------------------------------------------------------------------
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CPslnIdleTaskCreateViews* CPslnIdleTaskCreateViews::NewL( CPslnUi* aPslnUi )
    {
    CPslnIdleTaskCreateViews* self =
        new( ELeave ) CPslnIdleTaskCreateViews( aPslnUi );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CPslnIdleTaskCreateViews::ConstructL()
    {
    iIdleTask = CIdle::NewL( CActive::EPriorityIdle );
    iIdleTask->Start( TCallBack( DoHandleIdleTimeL, this ) );
    }

// Destructor
CPslnIdleTaskCreateViews::~CPslnIdleTaskCreateViews()
    {
    if ( iIdleTask )
        {
        iIdleTask->Cancel();
        }
    delete iIdleTask;
    }

// ---------------------------------------------------------------------------
// Informs when task is finished.
// ---------------------------------------------------------------------------
//
TBool CPslnIdleTaskCreateViews::IsFinished() const
    {
    return iDone;
    }

// -----------------------------------------------------------------------------
// Callback function when application is idle.
// -----------------------------------------------------------------------------
//
TInt CPslnIdleTaskCreateViews::DoHandleIdleTimeL( TAny* aAny )
    {
    static_cast< CPslnIdleTaskCreateViews* >( aAny )->HandleIdleTimeL();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Handles idle time. With each step a new view is created.
// -----------------------------------------------------------------------------
//
void CPslnIdleTaskCreateViews::HandleIdleTimeL()
    {
    if ( !IsFinished() )
        {
        TUid viewToCreate = KPslnGeneralView; //just initialise
        switch( iIdleStep )
            {
            case KPslnCreateTabs:
                iPslnUi->ConstructTabGroupL();
                break;
            case KPslnFullUpdateModel:
                if ( iPslnUi->Model() &&
                     iPslnUi->Model()->ActiveSkinIndex() == KErrNotFound )
                    {
                    iPslnUi->Model()->PerformCompleteUpdateL();
                    }
                break;
            case KPslnCreateGeneralView:
                viewToCreate = KPslnGeneralView;
                break;
            case KPslnCreateWallpaperView:
                viewToCreate = KPslnWallpaperView;
                break;
            case KPslnCreateScreensaverView:
                viewToCreate = KPslnScreenSaverView;
                iDone = ETrue;
                break;
            default:
                User::Leave( KErrArgument );
                break;
            }
        if ( iIdleStep != KPslnCreateTabs && iIdleStep != KPslnFullUpdateModel )
            {
            iPslnUi->CreateViewL( viewToCreate );
            }
        iIdleStep++;
        if ( !iDone )
            {
            if ( iIdleTask && !iIdleTask->IsActive() )
                {
                iIdleTask->Start( TCallBack( DoHandleIdleTimeL, this ) );
                }
            }
        }
    }

// End of file
