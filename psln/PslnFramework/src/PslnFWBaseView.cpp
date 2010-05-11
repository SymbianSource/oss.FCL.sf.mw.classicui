/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Base view for all plugin views.
*
*/


// INCLUDE FILES
#include "pslnfwbaseview.h"
#include "pslnfwbasecontainer.h"
#include "PslnConst.h"
#include "PslnDebug.h"

// For Download and Help command handling
#include <psln.hrh>
#include <hlplch.h>

// AVKON utilities
#include <aknnavide.h>
#include <akntitle.h>
#include <aknViewAppUi.h>
#include <akntabgrp.h>

// General Utilities
#include <barsread.h>
#include <bautils.h>
#include <data_caging_path_literals.hrh>
#include <StringLoader.h>

// Static view locations.
const TInt KPslnFWGeneralThemeViewLocation = 0;

// ========================= MEMBER FUNCTIONS ================================
// ---------------------------------------------------------------------------
// C++ constructor
// ---------------------------------------------------------------------------
EXPORT_C CPslnFWBaseView::CPslnFWBaseView() : iResourceLoader( *iCoeEnv ),
    iMyTabIndex ( KErrNotFound )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
EXPORT_C CPslnFWBaseView::~CPslnFWBaseView()
    {
    iResourceLoader.Close();
    if ( iContainer )
        {
        CAknViewAppUi* appUi = AppUi();
        if ( appUi )
            {
            appUi->RemoveFromStack( iContainer );
            }
        delete iContainer;
        }
    }

// ---------------------------------------------------------------------------
// CPslnFWBaseView::Container
// ---------------------------------------------------------------------------
EXPORT_C CPslnFWBaseContainer* CPslnFWBaseView::Container()
    {
    return iContainer;
    }

// ---------------------------------------------------------------------------
// CPslnFWBaseView::SetCurrentItem
// ---------------------------------------------------------------------------
EXPORT_C void CPslnFWBaseView::SetCurrentItem( TInt aIndex )
    {
    PSLN_TRACE_DEBUG("CPslnFWBaseView::SetCurrentItem");
    if ( aIndex > 0 )
        {
        iCurrentItem = aIndex;
        }
    else
        {
        // If invalid index, set to first.
        iCurrentItem = 0;
        }
    }

// ---------------------------------------------------------------------------
// CPslnFWBaseView::HandleListBoxEventL
// ---------------------------------------------------------------------------
EXPORT_C void CPslnFWBaseView::HandleListBoxEventL( CEikListBox* /*aListBox*/,
                                                TListBoxEvent aEventType )
    {
    switch ( aEventType )
        {
        case EEventItemClicked:
            if ( iContainer && iContainer->iMSKObserver )
                {
                iContainer->iMSKObserver->CheckMiddleSoftkeyLabelL();
                }
            break;
        case EEventEnterKeyPressed:
        case EEventItemDoubleClicked:
        case EEventItemSingleClicked:
            HandleListBoxSelectionL();
            break;
        default:
           break;
        }
    }

// ---------------------------------------------------------------------------
// Sets navi_pane.
// ---------------------------------------------------------------------------
//
EXPORT_C void CPslnFWBaseView::SetNaviPaneL()
    {
    PSLN_TRACE_DEBUG("CPslnFWBaseView::SetNaviPaneL BEGIN");
    if ( !iNaviControlContainer )
        {
        CAknViewAppUi* appUi = AppUi();
        if ( appUi )
            {
            CEikStatusPane* sp = appUi->StatusPane();
            if ( sp )
                {
                iNaviControlContainer = static_cast<CAknNavigationControlContainer*>
                    ( sp->ControlL( TUid::Uid( EEikStatusPaneUidNavi ) ) );
                }
            }
        }

    _LIT( KPanicText, "CPslnFWBaseView" );
    __ASSERT_DEBUG( iNaviControlContainer, User::Panic( KPanicText, KErrGeneral ) );

    if ( iNaviControlContainer )
        {
        if ( iNaviPaneContext )
            {
            iNaviControlContainer->PushL( *iNaviPaneContext );
            }
        else
            {
            iNaviControlContainer->PushDefaultL();
            }
        }
    PSLN_TRACE_DEBUG("CPslnFWBaseView::SetNaviPaneL END");
    }

// ---------------------------------------------------------------------------
// CPslnFWBaseView::CreateNaviPaneContextL
// ---------------------------------------------------------------------------
//
EXPORT_C void CPslnFWBaseView::CreateNaviPaneContextL( TInt /*aResourceId*/ )
    {
    // Deprecated.
    }

// ---------------------------------------------------------------------------
// Sets navi_pane decorator.
// ---------------------------------------------------------------------------
//
EXPORT_C void CPslnFWBaseView::SetNaviPaneDecorator(
    CAknNavigationDecorator* aDecorator )
    {
    PSLN_TRACE_DEBUG("CPslnFWBaseView::SetNaviPaneDecorator");
    iNaviPaneContext = aDecorator;
    }

// ---------------------------------------------------------------------------
// Sets navi_pane and activates a tab.
// ---------------------------------------------------------------------------
//
EXPORT_C void CPslnFWBaseView::SetNaviPaneL( const TInt aTabLocation )
    {
    PSLN_TRACE_DEBUG("CPslnFWBaseView::SetNaviPaneL w/ param BEGIN");
    if ( !iNaviControlContainer )
        {
        CAknViewAppUi* appUi = AppUi();
        if ( appUi )
            {
            CEikStatusPane* sp = appUi->StatusPane();
            if ( sp )
                {
                iNaviControlContainer = static_cast<CAknNavigationControlContainer*>
                    ( sp->ControlL( TUid::Uid( EEikStatusPaneUidNavi ) ) );
                }
            }
        }

    if ( iNaviControlContainer )
        {
        if ( iNaviPaneContext && ( aTabLocation > 0 ) )
            {
            CAknTabGroup* tabGrp = static_cast <CAknTabGroup*>
                        ( iNaviPaneContext->DecoratedControl() );
            tabGrp->SetActiveTabByIndex( aTabLocation );
            iNaviControlContainer->PushL( *iNaviPaneContext );
            }
        else
            {
            iNaviControlContainer->PushDefaultL();
            }
        }
    PSLN_TRACE_DEBUG("CPslnFWBaseView::SetNaviPaneL w/ param END");
    }

// ---------------------------------------------------------------------------
// Activates the view.
// ---------------------------------------------------------------------------
//
EXPORT_C void CPslnFWBaseView::DoActivateL( const TVwsViewId& aPrevViewId,
                                        TUid /*aCustomMessageId*/,
                                        const TDesC8& /*aCustomMessage*/ )
    {
    PSLN_TRACE_DEBUG("CPslnFWBaseView::DoActivateL END");
    iPrevViewId = aPrevViewId;
    CAknViewAppUi* appUi = AppUi();
    if ( !iContainer )
        {
        CreateContainerL();
        if ( appUi )
            {
            AppUi()->AddToStackL( *this, iContainer );
            }
        iContainer->iListBox->SetListBoxObserver( this );
        }

#ifdef RD_CONTROL_PANEL
    TInt titlePaneResID = KErrNotFound;
    SetTitlePaneL( titlePaneResID );
    // Retrieve title pane and set it.
    CEikStatusPane* sp = iAvkonAppUi->StatusPane();
    if ( sp )
        {
        CAknTitlePane* titlePane = static_cast<CAknTitlePane*>(
            sp->ControlL( TUid::Uid( EEikStatusPaneUidTitle ) ) );
        if ( ( titlePaneResID > KErrNone ) && titlePane )
            {
            HBufC* titlePaneText = NULL;
            titlePaneText = StringLoader::LoadLC( titlePaneResID );
            titlePane->SetTextL( titlePaneText->Des() );
            CleanupStack::PopAndDestroy( titlePaneText );
            }
        }
#endif //RD_CONTROL_PANEL

    PSLN_TRACE_DEBUG("CPslnFWBaseView::DoActivateL END");
    }

// ---------------------------------------------------------------------------
// Deactivates view.
// ---------------------------------------------------------------------------
//
EXPORT_C void CPslnFWBaseView::DoDeactivate()
    {
    PSLN_TRACE_DEBUG("CPslnFWBaseView::DoDeactivate BEGIN");
    if ( iContainer )
        {
        CAknViewAppUi* appUi = AppUi();
        if ( appUi )
            {
            appUi->RemoveFromStack( iContainer );
            }
        delete iContainer;
        iContainer = NULL;
        }
    PSLN_TRACE_DEBUG("CPslnFWBaseView::DoDeactivate END");
    }

// ---------------------------------------------------------------------------
// Sets the real tab location of the view.
// ---------------------------------------------------------------------------
//
EXPORT_C void CPslnFWBaseView::SetTabIndex( TInt aMyTabIndex )
    {
    if ( iNaviPaneContext &&
         IsValidLocation( aMyTabIndex ) )
        {
        CAknTabGroup* tabGrp = static_cast <CAknTabGroup*>
                    ( iNaviPaneContext->DecoratedControl() );
        if ( tabGrp && ( tabGrp->TabCount() > aMyTabIndex  ) )
            {
            iMyTabIndex = aMyTabIndex;
            }
        }
    }

// ---------------------------------------------------------------------------
// Gets the real tab location of the view.
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CPslnFWBaseView::GetTabIndex() const
    {
    return iMyTabIndex;
    }

// ---------------------------------------------------------------------------
// Creates container.
// ---------------------------------------------------------------------------
//
EXPORT_C void CPslnFWBaseView::CreateContainerL()
    {
    PSLN_TRACE_DEBUG("CPslnFWBaseView::CreateContainerL BEGIN");
    NewContainerL();
    iContainer->SetMopParent( this );

    CPslnFWBaseContainer* container = iContainer;
    iContainer = NULL;
    CleanupStack::PushL( container );
    container->ConstructL( ClientRect() );
    CleanupStack::Pop( container );
    iContainer = container;
    PSLN_TRACE_DEBUG("CPslnFWBaseView::CreateContainerL END");
    }

// ---------------------------------------------------------------------------
// Opens localized resource file from static path.
// ---------------------------------------------------------------------------
//
EXPORT_C void CPslnFWBaseView::OpenLocalizedResourceFileL(
    const TDesC& aResourceFileName,
    RConeResourceLoader& aResourceLoader )
    {
    PSLN_TRACE_DEBUG("CPslnFWBaseView::OpenLocalizedResourceFileL BEGIN");
    // Find the resource file:
    OpenLocalizedResourceFileL(
        aResourceFileName,
        aResourceLoader,
        &KDC_RESOURCE_FILES_DIR );
    PSLN_TRACE_DEBUG("CPslnFWBaseView::OpenLocalizedResourceFileL END");
    }

// ---------------------------------------------------------------------------
// Same as above, except this takes resource path from user.
// ---------------------------------------------------------------------------
//
EXPORT_C void CPslnFWBaseView::OpenLocalizedResourceFileL(
            const TDesC& aResourceFileName,
            RConeResourceLoader& aResourceLoader,
            const TDesC* aPath )
    {
    PSLN_TRACE_DEBUG("CPslnFWBaseView::OpenLocalizedResourceFileL 2 BEGIN");
    // Find the resource file:
    TParse* parse = new (ELeave) TParse;
    CleanupStack::PushL( parse );
    parse->Set( aResourceFileName, aPath, NULL );
    TFileName* fileName = new (ELeave) TFileName( parse->FullName() );
    CleanupStack::PushL( fileName );

    // Open resource file:
    aResourceLoader.OpenL( *fileName );

    CleanupStack::PopAndDestroy( 2, parse ); // fileName, parse
    PSLN_TRACE_DEBUG("CPslnFWBaseView::OpenLocalizedResourceFileL 2 END");
    }

// ---------------------------------------------------------------------------
// Sets middle softkey label.
// ---------------------------------------------------------------------------
//
EXPORT_C void CPslnFWBaseView::SetMiddleSoftKeyLabelL(
    const TInt aResourceId, const TInt aCommandId )
    {
    PSLN_TRACE_DEBUG("CPslnFWBaseView::SetMiddleSoftKeyLabelL BEGIN");
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
    PSLN_TRACE_DEBUG("CPslnFWBaseView::SetMiddleSoftKeyLabelL END");
    }

// ---------------------------------------------------------------------------
// Handles Help command.
// ---------------------------------------------------------------------------
//
EXPORT_C void CPslnFWBaseView::HandleCommandL( TInt aCommand )
    {
    CAknViewAppUi* appUi = AppUi();
    if ( !appUi )
        {
        User::Leave( KErrNotFound );
        }
    switch( aCommand )
        {
        case EAknCmdHelp:
        case EPslnCmdAppHelp:
            // launch Help
            HlpLauncher::LaunchHelpApplicationL(
                iCoeEnv->WsSession(), appUi->AppHelpContextL());
            break;
        default:
            appUi->HandleCommandL( aCommand );
            break;
        }
    }

// ---------------------------------------------------------------------------
// Set title pane to a view.
// ---------------------------------------------------------------------------
//
EXPORT_C void CPslnFWBaseView::SetTitlePaneL( TInt& /*aResourceId*/ )
    {
    // Empty implementation to be overloaded.
    }

// ----------------------------------------------------------------------------
// Checks that the location is valid.
// ----------------------------------------------------------------------------
//
TBool CPslnFWBaseView::IsValidLocation( const TInt& aLoc ) const
    {
    TBool retVal = ETrue;
    // First location is always forbidden.
    if ( aLoc == KPslnFWGeneralThemeViewLocation )
        {
        retVal = EFalse;
        }
    return retVal;
    }

//End of File
