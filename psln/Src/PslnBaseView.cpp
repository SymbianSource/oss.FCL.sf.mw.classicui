/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Provides Psln Application Base view methods.
*
*/


// INCLUDE FILES

#include "PslnBaseView.h"

#include <mpslnfwmsklabelobserver.h>

#include <aknnavi.h>
#include <aknnavide.h>
#include <aknViewAppUi.h>
#include <akntitle.h>
#include <barsread.h>
#include <StringLoader.h>
#include <eikbtgpc.h>
#include <eikmenup.h>
#include <avkon.rsg>

#include <psln.rsg>

#include "PslnFeatures.h"
#include "PslnUi.h"
#include "PslnBaseContainer.h"
#include "PslnConst.h"

// ========================= MEMBER FUNCTIONS ================================
// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
CPslnBaseView::CPslnBaseView()
    {
    iPslnUi = static_cast<CPslnUi*>( AppUi() );

    if ( !iModel )
        {
        iModel = iPslnUi->Model();
        }
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CPslnBaseView::~CPslnBaseView()
    {
    if ( iContainer )
        {
        iPslnUi->RemoveFromStack( iContainer );
        delete iContainer;
        }
    if ( iNaviPaneContext &&
         iNaviPaneContext != iPslnUi->PslnTabGroup() )
        {
        delete iNaviPaneContext;
        }
    }

// ---------------------------------------------------------------------------
// CPslnBaseView::HandleListBoxEventL
// ---------------------------------------------------------------------------
//
void CPslnBaseView::HandleListBoxEventL(
    CEikListBox* /*aListBox*/, TListBoxEvent aEventType)
    {
    switch ( aEventType )
        {
        case EEventItemClicked:
        case EEventFlickStopped:
            if ( iContainer && iContainer->GetMiddleSoftkeyObserver() )
                {
                iContainer->GetMiddleSoftkeyObserver()->CheckMiddleSoftkeyLabelL();
                }
            HandleListBoxItemHighlightL();    
            break;
        case EEventEnterKeyPressed:
        case EEventItemDoubleClicked:
        case EEventItemSingleClicked:
            HandleListBoxSelectionL();
            break;
        case EEventPenDownOnItem:
            HandleListBoxStylusDown();
            break;
        case EEventItemDraggingActioned:
            HandleListBoxStylusDrag();
            break;
        default:
           break;
        }
    }

// ---------------------------------------------------------------------------
// CPslnBaseView::DoActivateL
// Activates the view.
// ---------------------------------------------------------------------------
//
void CPslnBaseView::DoActivateL( const TVwsViewId& aPrevViewId,
    TUid aCustomMessageId, const TDesC8& /*aCustomMessage*/ )
    {
    if( aPrevViewId.iViewUid == Id() &&
        aPrevViewId.iAppUid == KUidPsln )//same view?
        {
        //if continuous activate same view twice,direct return,do nothing
        return;   
        }
        
    if( iContainer )
        {
        RemoveContainer();
        }

    CreateContainerL();
    iPslnUi->AddToStackL( *this, iContainer );
    iContainer->SetListBoxObserver( this );

    SetNaviPaneL();
    TInt titlePaneResourceID = KErrNone;
    SetTitlePaneL( titlePaneResourceID );
    // Retrieve title pane and set it.
    CEikStatusPane* sp = iAvkonAppUi->StatusPane();
    if ( sp )
        {
        CAknTitlePane* titlePane = static_cast<CAknTitlePane*>(
            sp->ControlL( TUid::Uid( EEikStatusPaneUidTitle ) ) );
        if ( ( titlePaneResourceID > KErrNone ) && titlePane )
            {
            HBufC* titlePaneText = NULL;
            titlePaneText = StringLoader::LoadLC( titlePaneResourceID );
            titlePane->SetTextL( titlePaneText->Des() );
            CleanupStack::PopAndDestroy( titlePaneText );
            }
        }
        
    CEikButtonGroupContainer* cba = Cba();
    if (cba)
        {
        TInt id = CbaResourceId( aPrevViewId, aCustomMessageId );
        cba->SetCommandSetL( id );
        cba->DrawDeferred();
        }
    }

// ---------------------------------------------------------------------------
// CPslnBaseView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CPslnBaseView::DoDeactivate()
    {
    if ( iContainer )
        {
        iCurrentItem = iContainer->CurrentItemIndex();
        RemoveContainer();
        }
    }

// ---------------------------------------------------------------------------
// CPslnBaseView::CreateContainerL()
// ---------------------------------------------------------------------------
//
void CPslnBaseView::CreateContainerL()
    {
    NewContainerL();
    iContainer->SetMopParent( this );

    CPslnBaseContainer* container = iContainer;
    iContainer = NULL;
    CleanupStack::PushL( container );
    container->ConstructL( ClientRect() );
    CleanupStack::Pop( container );
    iContainer = container;
    }

// ---------------------------------------------------------------------------
// CPslnBaseView::SetNaviPaneL
// ---------------------------------------------------------------------------
//
void CPslnBaseView::SetNaviPaneL()
    {
#ifndef RD_CONTROL_PANEL
    CAknNavigationControlContainer* naviPane = iPslnUi->NaviContainer();
    if ( !naviPane )
        {
        return;
        }
    if ( iNaviPaneContext )
        {
        iPslnUi->NaviContainer()->PushL( *iNaviPaneContext );

        if ( iNaviPaneContext == iPslnUi->PslnTabGroup() )
            {
            iPslnUi->UpdateTabIndex();
            }
        }
    else
        {
        iPslnUi->NaviContainer()->PushDefaultL();
        }
#else
    iPslnUi->NaviContainer()->PushDefaultL();
#endif //RD_CONTROL_PANEL
    }

// ---------------------------------------------------------------------------
// Sets middle softkey label.
// ---------------------------------------------------------------------------
//
void CPslnBaseView::SetMiddleSoftKeyLabelL(
    const TInt aResourceId, const TInt aCommandId )
    {
    CEikButtonGroupContainer* cbaGroup = Cba();
    if ( cbaGroup )
        {
        HBufC* middleSKText = StringLoader::LoadLC( aResourceId );
        TPtr mskPtr = middleSKText->Des();
        cbaGroup->AddCommandToStackL(
            KPslnMSKControlID,
            aCommandId,
            mskPtr );
        CleanupStack::PopAndDestroy( middleSKText );
        }
    }

// ---------------------------------------------------------------------------
// Removes Help if it is not supported.
// ---------------------------------------------------------------------------
//
void CPslnBaseView::DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane )
    {
    if ( aResourceId == R_PSLN_BASIC_MENUPANE )
        {
        if( !PslnFeatures::IsHelpSupported() )
            {
            // Disable help if not supported
            aMenuPane->SetItemDimmed( EPslnCmdAppHelp, ETrue );
            }
        }
    }

// ---------------------------------------------------------------------------
// Whether to set right softkey as exit
// ---------------------------------------------------------------------------
//        
TInt CPslnBaseView::CbaResourceId(const TVwsViewId& /*aPrevViewId*/,TUid /*aCustomMessageId*/  )
    {
    return R_AVKON_SOFTKEYS_OPTIONS_BACK;
    }
    
// -----------------------------------------------------------------------------
// Handle listbox stylus move event.
// -----------------------------------------------------------------------------
//
void CPslnBaseView::HandleListBoxStylusDown()
    {
    }
    
// -----------------------------------------------------------------------------
// Handle listbox stylus move event.
// -----------------------------------------------------------------------------
//
void CPslnBaseView::HandleListBoxStylusDrag()
    {
    }

// ---------------------------------------------------------------------------
// Removes container.
// ---------------------------------------------------------------------------
//
void CPslnBaseView::RemoveContainer()
    {
    if ( iPslnUi )
        {
        iPslnUi->RemoveFromStack( iContainer );
        }
    delete iContainer;
    iContainer = NULL;
    }

//End of File
