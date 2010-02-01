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
* Description: Test aknphysics.h
*
*/

// [INCLUDE FILES]
#include "testplatphysics.h"

// observer for test
class CTestPhysicsObserver : public CBase, public MAknPhysicsObserver
    {
public:
    /*Constructor*/
    CTestPhysicsObserver(){}
    /*Deconstructor*/
    ~CTestPhysicsObserver(){}
    /**
     * Physics emulation has moved the view
     * 
     * @since S60 v5.0
     * @param aNewPosition   The new position of the view.
     * @param  aDrawNow      @c ETrue if client should redraw the screen,
     *                       otherwise @c EFalse.
     * @param  aFlags        Additional flags, not used currently.
     */	 
    void ViewPositionChanged( const TPoint& /*aNewPosition*/,
                              TBool /*aDrawNow*/,
                              TUint /*aFlags*/ ){}
    
    /**
     * Physics emulation has stopped moving the view
     *
     * @since S60 v5.0
     */
    void PhysicEmulationEnded(){}

    /**
     * Returns the observer view position.
     *
     * @since S60 v5.0
     * @return Physics observer view position.
     */
    TPoint ViewPosition() const
    {
    TPoint point( 0, 0 );
    return point;
    }

    };

// ============================ MEMBER FUNCTIONS =========================


// --------------------------------------------------------------------------
// CTestPlatPhysics::TestCAknPhysicsNewL
// --------------------------------------------------------------------------
//
TInt CTestPlatPhysics::TestCAknPhysicsNewL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatphysics, "CTestPlatPhysics");
    _LIT(Ktestcaknphysicsnewl, "In TestCAknPhysicsNewL");
    TestModuleIf().Printf(0, Kctestplatphysics, Ktestcaknphysicsnewl);
    iLog->Log(Ktestcaknphysicsnewl);

    CTestPhysicsObserver* ob = new ( ELeave ) CTestPhysicsObserver;
    CleanupStack::PushL( ob );
    CAknPhysics* temp = CAknPhysics::NewL( *ob, iControl );
    CleanupStack::PushL( temp );
    STIF_ASSERT_NOT_NULL( temp );
    CleanupStack::PopAndDestroy( temp );
    CleanupStack::PopAndDestroy( ob );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatPhysics::TestCAknPhysicsInitPhysicsL
// --------------------------------------------------------------------------
//
TInt CTestPlatPhysics::TestCAknPhysicsInitPhysicsL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatphysics, "CTestPlatPhysics");
    _LIT(Ktestcaknphysicsinitphysicsl, "In TestCAknPhysicsInitPhysicsL");
    TestModuleIf().Printf(0, Kctestplatphysics, Ktestcaknphysicsinitphysicsl);
    iLog->Log(Ktestcaknphysicsinitphysicsl);

    CTestPhysicsObserver* ob = new ( ELeave ) CTestPhysicsObserver;
    CleanupStack::PushL( ob );
    CAknPhysics* temp = CAknPhysics::NewL( *ob, iControl );
    CleanupStack::PushL( temp );
    TSize workSize;
    TSize viewSize;
    TBool landscape = EFalse;
    temp->InitPhysicsL( workSize, viewSize, landscape );
    CleanupStack::PopAndDestroy( temp );
    CleanupStack::PopAndDestroy( ob );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatPhysics::TestCAknPhysicsStartPhysicsL
// --------------------------------------------------------------------------
//
TInt CTestPlatPhysics::TestCAknPhysicsStartPhysicsL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatphysics, "CTestPlatPhysics");
    _LIT(Ktestcaknphysicsstartphysicsl, "In TestCAknPhysicsStartPhysicsL");
    TestModuleIf().Printf(0, Kctestplatphysics, Ktestcaknphysicsstartphysicsl);
    iLog->Log(Ktestcaknphysicsstartphysicsl);

    CTestPhysicsObserver* ob = new ( ELeave ) CTestPhysicsObserver;
    CleanupStack::PushL( ob );
    CAknPhysics* temp = CAknPhysics::NewL( *ob, iControl );
    CleanupStack::PushL( temp );
    TPoint drag;
    TTime startTime;
    temp->StartPhysics( drag, startTime );
    CleanupStack::PopAndDestroy( temp );
    CleanupStack::PopAndDestroy( ob );


    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatPhysics::TestCAknPhysicsStopPhysicsL
// --------------------------------------------------------------------------
//
TInt CTestPlatPhysics::TestCAknPhysicsStopPhysicsL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatphysics, "CTestPlatPhysics");
    _LIT(Ktestcaknphysicsstopphysicsl, "In TestCAknPhysicsStopPhysicsL");
    TestModuleIf().Printf(0, Kctestplatphysics, Ktestcaknphysicsstopphysicsl);
    iLog->Log(Ktestcaknphysicsstopphysicsl);

    CTestPhysicsObserver* ob = new ( ELeave ) CTestPhysicsObserver;
    CleanupStack::PushL( ob );
    CAknPhysics* temp = CAknPhysics::NewL( *ob, iControl );
    CleanupStack::PushL( temp );
    temp->StopPhysics();
    CleanupStack::PopAndDestroy( temp );
    CleanupStack::PopAndDestroy( ob );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatPhysics::TestCAknPhysicsOngoingPhysicsActionL
// --------------------------------------------------------------------------
//
TInt CTestPlatPhysics::TestCAknPhysicsOngoingPhysicsActionL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatphysics, "CTestPlatPhysics");
    _LIT(Ktestcaknphysicsongoingphysicsactionl, "In TestCAknPhysicsOngoingPhysicsActionL");
    TestModuleIf().Printf(0, Kctestplatphysics, Ktestcaknphysicsongoingphysicsactionl);
    iLog->Log(Ktestcaknphysicsongoingphysicsactionl);

    CTestPhysicsObserver* ob = new ( ELeave ) CTestPhysicsObserver;
    CleanupStack::PushL( ob );
    CAknPhysics* temp = CAknPhysics::NewL( *ob, iControl );
    CleanupStack::PushL( temp );
    temp->OngoingPhysicsAction();
    CleanupStack::PopAndDestroy( temp );
    CleanupStack::PopAndDestroy( ob );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatPhysics::TestCAknPhysicsRegisterPanningPositionL
// --------------------------------------------------------------------------
//
TInt CTestPlatPhysics::TestCAknPhysicsRegisterPanningPositionL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatphysics, "CTestPlatPhysics");
    _LIT(Ktestcaknphysicsregisterpanningpositionl, "In TestCAknPhysicsRegisterPanningPositionL");
    TestModuleIf().Printf(0, Kctestplatphysics, Ktestcaknphysicsregisterpanningpositionl);
    iLog->Log(Ktestcaknphysicsregisterpanningpositionl);

    CTestPhysicsObserver* ob = new ( ELeave ) CTestPhysicsObserver;
    CleanupStack::PushL( ob );
    CAknPhysics* temp = CAknPhysics::NewL( *ob, iControl );
    CleanupStack::PushL( temp );
    TPoint delta;
    temp->RegisterPanningPosition( delta );
    CleanupStack::PopAndDestroy( temp );
    CleanupStack::PopAndDestroy( ob );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatPhysics::TestCAknPhysicsSetFrictionL
// --------------------------------------------------------------------------
//
TInt CTestPlatPhysics::TestCAknPhysicsSetFrictionL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatphysics, "CTestPlatPhysics");
    _LIT(Ktestcaknphysicssetfrictionl, "In TestCAknPhysicsSetFrictionL");
    TestModuleIf().Printf(0, Kctestplatphysics, Ktestcaknphysicssetfrictionl);
    iLog->Log(Ktestcaknphysicssetfrictionl);

    CTestPhysicsObserver* ob = new ( ELeave ) CTestPhysicsObserver;
    CleanupStack::PushL( ob );
    CAknPhysics* temp = CAknPhysics::NewL( *ob, iControl );
    CleanupStack::PushL( temp );
    TReal friction( 0 );
    temp->SetFriction( friction );
    CleanupStack::PopAndDestroy( temp );
    CleanupStack::PopAndDestroy( ob );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatPhysics::TestCAknPhysicsResetFrictionL
// --------------------------------------------------------------------------
//
TInt CTestPlatPhysics::TestCAknPhysicsResetFrictionL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatphysics, "CTestPlatPhysics");
    _LIT(Ktestcaknphysicsresetfrictionl, "In TestCAknPhysicsResetFrictionL");
    TestModuleIf().Printf(0, Kctestplatphysics, Ktestcaknphysicsresetfrictionl);
    iLog->Log(Ktestcaknphysicsresetfrictionl);
    
    CTestPhysicsObserver* ob = new ( ELeave ) CTestPhysicsObserver;
    CleanupStack::PushL( ob );
    CAknPhysics* temp = CAknPhysics::NewL( *ob, iControl );
    CleanupStack::PushL( temp );
    temp->ResetFriction();
    CleanupStack::PopAndDestroy( temp );
    CleanupStack::PopAndDestroy( ob );


    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatPhysics::TestCAknPhysicsHighlightTimeoutL
// --------------------------------------------------------------------------
//
TInt CTestPlatPhysics::TestCAknPhysicsHighlightTimeoutL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatphysics, "CTestPlatPhysics");
    _LIT(Ktestcaknphysicshighlighttimeoutl, "In TestCAknPhysicsHighlightTimeoutL");
    TestModuleIf().Printf(0, Kctestplatphysics, Ktestcaknphysicshighlighttimeoutl);
    iLog->Log(Ktestcaknphysicshighlighttimeoutl);

    CTestPhysicsObserver* ob = new ( ELeave ) CTestPhysicsObserver;
    CleanupStack::PushL( ob );
    CAknPhysics* temp = CAknPhysics::NewL( *ob, iControl );
    CleanupStack::PushL( temp );
    temp->HighlightTimeout();
    CleanupStack::PopAndDestroy( temp );
    CleanupStack::PopAndDestroy( ob );
    
    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatPhysics::TestCAknPhysicsDragThresholdL
// --------------------------------------------------------------------------
//
TInt CTestPlatPhysics::TestCAknPhysicsDragThresholdL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatphysics, "CTestPlatPhysics");
    _LIT(Ktestcaknphysicsdragthresholdl, "In TestCAknPhysicsDragThresholdL");
    TestModuleIf().Printf(0, Kctestplatphysics, Ktestcaknphysicsdragthresholdl);
    iLog->Log(Ktestcaknphysicsdragthresholdl);

    CTestPhysicsObserver* ob = new ( ELeave ) CTestPhysicsObserver;
    CleanupStack::PushL( ob );
    CAknPhysics* temp = CAknPhysics::NewL( *ob, iControl );
    CleanupStack::PushL( temp );
    temp->DragThreshold();
    CleanupStack::PopAndDestroy( temp );
    CleanupStack::PopAndDestroy( ob );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatPhysics::TestCAknPhysicsFeatureEnabledL
// --------------------------------------------------------------------------
//
TInt CTestPlatPhysics::TestCAknPhysicsFeatureEnabledL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatphysics, "CTestPlatPhysics");
    _LIT(Ktestcaknphysicsfeatureenabledl, "In TestCAknPhysicsFeatureEnabledL");
    TestModuleIf().Printf(0, Kctestplatphysics, Ktestcaknphysicsfeatureenabledl);
    iLog->Log(Ktestcaknphysicsfeatureenabledl);

    CTestPhysicsObserver* ob = new ( ELeave ) CTestPhysicsObserver;
    CleanupStack::PushL( ob );
    CAknPhysics* temp = CAknPhysics::NewL( *ob, iControl );
    CleanupStack::PushL( temp );
    temp->FeatureEnabled();
    CleanupStack::PopAndDestroy( temp );
    CleanupStack::PopAndDestroy( ob );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatPhysics::TestCAknPhysicsEventHandlingAllowedL
// --------------------------------------------------------------------------
//
TInt CTestPlatPhysics::TestCAknPhysicsEventHandlingAllowedL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatphysics, "CTestPlatPhysics");
    _LIT(Ktestcaknphysicseventhandlingallowedl, "In TestCAknPhysicsEventHandlingAllowedL");
    TestModuleIf().Printf(0, Kctestplatphysics, Ktestcaknphysicseventhandlingallowedl);
    iLog->Log(Ktestcaknphysicseventhandlingallowedl);

    CTestPhysicsObserver* ob = new ( ELeave ) CTestPhysicsObserver;
    CleanupStack::PushL( ob );
    CAknPhysics* temp = CAknPhysics::NewL( *ob, iControl );
    CleanupStack::PushL( temp );
    temp->EventHandlingAllowed();
    CleanupStack::PopAndDestroy( temp );
    CleanupStack::PopAndDestroy( ob );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatPhysics::TestCAknPhysicsUpdateViewWindowControlL
// --------------------------------------------------------------------------
//
TInt CTestPlatPhysics::TestCAknPhysicsUpdateViewWindowControlL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatphysics, "CTestPlatPhysics");
    _LIT(Ktestcaknphysicsupdateviewwindowcontroll, "In TestCAknPhysicsUpdateViewWindowControlL");
    TestModuleIf().Printf(0, Kctestplatphysics, Ktestcaknphysicsupdateviewwindowcontroll);
    iLog->Log(Ktestcaknphysicsupdateviewwindowcontroll);

    CTestPhysicsObserver* ob = new ( ELeave ) CTestPhysicsObserver;
    CleanupStack::PushL( ob );
    CAknPhysics* temp = CAknPhysics::NewL( *ob, iControl );
    CleanupStack::PushL( temp );
    temp->UpdateViewWindowControl();
    CleanupStack::PopAndDestroy( temp );
    CleanupStack::PopAndDestroy( ob );

    return KErrNone;
    }

// --------------------------------------------------------------------------
// CTestPlatPhysics::TestCAknPhysicsSuspendPhysicsL
// --------------------------------------------------------------------------
//
TInt CTestPlatPhysics::TestCAknPhysicsSuspendPhysicsL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatphysics, "CTestPlatPhysics");
    _LIT(Ktestcaknphysicssuspendphysicsl, "In TestCAknPhysicsSuspendPhysicsL");
    TestModuleIf().Printf(0, Kctestplatphysics, Ktestcaknphysicssuspendphysicsl);
    iLog->Log(Ktestcaknphysicssuspendphysicsl);

    CTestPhysicsObserver* ob = new ( ELeave ) CTestPhysicsObserver;
    CleanupStack::PushL( ob );
    CAknPhysics* temp = CAknPhysics::NewL( *ob, iControl );
    CleanupStack::PushL( temp );
    temp->SuspendPhysics();
    CleanupStack::PopAndDestroy( temp );
    CleanupStack::PopAndDestroy( ob );

    return KErrNone;
    }
    
// --------------------------------------------------------------------------
// CTestPlatPhysics::TestCAknPhysicsResumePhysicsL
// --------------------------------------------------------------------------
//
TInt CTestPlatPhysics::TestCAknPhysicsResumePhysicsL( CStifItemParser& /*aItem*/ )
    {
    _LIT(Kctestplatphysics, "CTestPlatPhysics");
    _LIT(Ktestcaknphysicsresumephysicsl, "In TestCAknPhysicsResumePhysicsL");
    TestModuleIf().Printf(0, Kctestplatphysics, Ktestcaknphysicsresumephysicsl);
    iLog->Log(Ktestcaknphysicsresumephysicsl);

    CTestPhysicsObserver* ob = new ( ELeave ) CTestPhysicsObserver;
    CleanupStack::PushL( ob );
    CAknPhysics* temp = CAknPhysics::NewL( *ob, iControl );
    CleanupStack::PushL( temp );
    temp->ResumePhysics();
    CleanupStack::PopAndDestroy( temp );
    CleanupStack::PopAndDestroy( ob );

    return KErrNone;
    }

