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
* Description:  Test eikfnlab.h
*
*/



// [INCLUDE FILES]

#include <eikfnlab.h>
#include <aknsconstants.h>
#include <akndef.h>
#include <coeaui.h>

#include "testsdklabels.h"
#include "testsdklabelsview.h"
#include "testsdklabelscontainer.h"

class CTestSDKEikFileNameLabel : public CEikFileNameLabel
    {
    friend class CTestSDKLabels;

public:
    CTestSDKEikFileNameLabel(){}

    };
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLCEikFileNameLabelL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLCEikFileNameLabelL( CStifItemParser& /*aItem*/ )
    {
    CEikFileNameLabel* fileNameLabel = new (ELeave) CEikFileNameLabel;
    CleanupStack::PushL( fileNameLabel );
    
    STIF_ASSERT_NOT_NULL( fileNameLabel );
    fileNameLabel->ConstructL();
    
    CleanupStack::PopAndDestroy( fileNameLabel );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CEikFileNameLabel* fileNameLabel = new (ELeave) CEikFileNameLabel;
    CleanupStack::PushL( fileNameLabel );
    
    STIF_ASSERT_NOT_NULL( fileNameLabel );
    fileNameLabel->ConstructL();
    
    CleanupStack::Pop( fileNameLabel );
    delete fileNameLabel;
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLConstructL( CStifItemParser& /*aItem*/ )
    {
    CEikFileNameLabel* fileNameLabel = new (ELeave) CEikFileNameLabel;
    CleanupStack::PushL( fileNameLabel );
    
    STIF_ASSERT_NOT_NULL( fileNameLabel );
    fileNameLabel->ConstructL();
    
    CleanupStack::PopAndDestroy( fileNameLabel );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLUpdateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLUpdateL( CStifItemParser& /*aItem*/ )
    {
    CEikFileNameLabel* fileNameLabel = new (ELeave) CEikFileNameLabel;
    CleanupStack::PushL( fileNameLabel );
    
    STIF_ASSERT_NOT_NULL( fileNameLabel );
    fileNameLabel->ConstructL();
    
    STIF_ASSERT_NOT_LEAVES( fileNameLabel->UpdateL() );
    
    CleanupStack::PopAndDestroy( fileNameLabel );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLGetColorUseListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLGetColorUseListL( CStifItemParser& /*aItem*/ )
    {
    CEikFileNameLabel* fileNameLabel = new (ELeave) CEikFileNameLabel;
    CleanupStack::PushL( fileNameLabel );
    
    STIF_ASSERT_NOT_NULL( fileNameLabel );
    fileNameLabel->ConstructL();
    
    CArrayFix<TCoeColorUse>* colorUseList = new (ELeave) CArrayFixFlat<TCoeColorUse>( 1 );
    CleanupStack::PushL( colorUseList );
    STIF_ASSERT_NOT_LEAVES( fileNameLabel->GetColorUseListL( *colorUseList ) );
    STIF_ASSERT_NOT_NULL( colorUseList );
    
    CleanupStack::PopAndDestroy( colorUseList );
    CleanupStack::PopAndDestroy( fileNameLabel );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    CEikFileNameLabel* fileNameLabel = new (ELeave) CEikFileNameLabel;
    CleanupStack::PushL( fileNameLabel );
    
    STIF_ASSERT_NOT_NULL( fileNameLabel );
    fileNameLabel->ConstructL();
    
    fileNameLabel->HandleResourceChange( KAknsMessageSkinChange );
    fileNameLabel->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    
    CleanupStack::PopAndDestroy( fileNameLabel );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    CEikFileNameLabel* fileNameLabel = new (ELeave) CEikFileNameLabel;
    CleanupStack::PushL( fileNameLabel );
    
    STIF_ASSERT_NOT_NULL( fileNameLabel );
    fileNameLabel->ConstructL();
    
    TSize minsize = fileNameLabel->MinimumSize();
    TPoint point( minsize.AsPoint() );
    
    STIF_ASSERT_NOT_EQUALS( 0, point.iX );
    STIF_ASSERT_NOT_EQUALS( 0, point.iY );
    
    CleanupStack::PopAndDestroy( fileNameLabel );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CEikFileNameLabel* fileNameLabel = new (ELeave) CEikFileNameLabel;
    CleanupStack::PushL( fileNameLabel );
    
    STIF_ASSERT_NOT_NULL( fileNameLabel );
    fileNameLabel->ConstructL();
    
    TPointerEvent event;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    event.iType = TPointerEvent::EButton1Down;
    fileNameLabel->HandlePointerEventL( event );
    
    event.iType = TPointerEvent::EButton2Down;
    fileNameLabel->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( fileNameLabel );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabels::TestLDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLabels::TestLDrawL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKLabelsView* view = CTestSDKLabelsView::NewL();
    CleanupStack::PushL( view );
    CTestSDKLabelsContainer* container = new ( ELeave ) CTestSDKLabelsContainer;
    CleanupStack::PushL( container );

    container->SetMopParent( view );
    container->ConstructL( view->ClientRect() );
    CCoeEnv::Static()->AppUi()->AddToStackL( container );
    container->MakeVisible( ETrue );

    CTestSDKEikFileNameLabel* fileNameLabel = new (ELeave) CTestSDKEikFileNameLabel;
    CleanupStack::PushL( fileNameLabel );
    STIF_ASSERT_NOT_NULL( fileNameLabel );
    fileNameLabel->ConstructL();

    container->SetControlL( fileNameLabel );

    container->ActivateGc();
    TRect rect( 1, 1, 1, 1 );
    fileNameLabel->Draw( rect );
    container->DeactivateGc();

    CleanupStack::Pop( fileNameLabel );
    CCoeEnv::Static()->AppUi()->RemoveFromStack( container );
    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    
    }


//  [End of File]
