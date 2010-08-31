/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  CAknPhysics
*
*/


#include <aknphysics.h>
#include <aknphysicsobserveriface.h>
#include <e32debug.h>

#include "aknphysicsconstants.h"
#include "aknphysicsengine.h"
#include "aknphysicsparameterprovider.h"
#include "aknphysicsrestrictor.h"
#include "aknphysicsconeobserver.h"
#include <touchfeedback.h>

const TInt KSamePositionStopCount( 3 );

_LIT( KNullThreadProcessName, "ekern.exe*" );
_LIT( KNullThreadName, "::Null" );

#undef AKNHIGHRESPERIODIC_PROFILE

/**
 * Opens a handle to the null thread.
 */
static TBool FindNullThread( RThread& aThread )
    {
    TFindProcess fp( KNullThreadProcessName );
    TFullName kernelName;
    if ( fp.Next( kernelName ) == KErrNone )
        {
        kernelName.Append( KNullThreadName );
        
        TFindThread ft( kernelName );
        TFullName threadName;
        if ( ft.Next( threadName ) == KErrNone )
            {
            if ( aThread.Open( threadName ) != KErrNone )
                {
                return EFalse;
                }
            }
        }        

    return ( aThread.Handle() != 0 );
    }


/**
 * Periodic timer using CTimer::HighRes.
 */
NONSHARABLE_CLASS( CAknHighResPeriodic ) : public CTimer
    {
public:

    /**
     * Creates new timer instance.
     * 
     * @param  aPriority    Priority of the timer.
     * @param  aNullThread  Open thread handle to the null thread,
     *                      ownership is not transferred.
     */
    static CAknHighResPeriodic* NewL( TInt aPriority,
                                      RThread* aNullThread );

    /**
     * Destructor.
     */
    ~CAknHighResPeriodic();

    /**
     * Starts periodic timer.
     * 
     * @param  aDelay      Initial delay.
     * @param  anInterval  Minimum interval between callback.
     * @param  aCallBack   Callback to invoke.
     */
    void Start( TTimeIntervalMicroSeconds32 aDelay,
                TTimeIntervalMicroSeconds32 anInterval,
                TCallBack aCallBack );

    /**
     * Sets minimum time between end of callback to beginning of next one.
     *
     * This is one approach to try to make sure that there is some time for
     * other processes. If this process can handle callback quickly,
     * this won't slow down frame rate.
     * 
     * @param  aDelay  Minimum time between callbacks.
     */
    void SetMinCallBackPeriod( TTimeIntervalMicroSeconds32 aDelay );

protected:

    /**
     * C++ constructor.
     * 
     * @param  aPriority    Priority of the timer.
     * @param  aNullThread  Open thread handle to the null thread,
     *                      ownership is not transferred.
     */
    CAknHighResPeriodic( TInt aPriority, RThread* aNullThread );
    
    /**
     * Called upon timer completion.
     */
    void RunL();

private:

    /**
     * Prints out the CPU time given to the null thread between this and
     * the previous call to this method.
     */
    void DumpNull();
    
private:

    /** Timer interval. */
    TTimeIntervalMicroSeconds32 iInterval;
    
    /** Callback of the timer. */
    TCallBack iCallBack;
    
    /** Is the end time valid, i.e. has the timer been completed at least once. */
    TBool iEndTimeValid;
    
    /** Time after the execution of the last timer callback. */
    TTime iEndTime;
    
    /** Minimum interval between callbacks. */
    TInt64 iMinCallBackPeriod;
    
    TBool iWaiting;
    
    /** Pointer to the null thread handle, not own. */
    RThread* iDebugNullThread;
    
    /** Null thread CPU time after the last callback. */ 
    TInt64 iDebugPreviousTime;
    };


// ---------------------------------------------------------------------------
// Creates new timer instance
// ---------------------------------------------------------------------------
//
CAknHighResPeriodic* CAknHighResPeriodic::NewL( TInt aPriority,
                                                RThread* aNullThread )
    {
    CAknHighResPeriodic* self =
        new (ELeave) CAknHighResPeriodic( aPriority, aNullThread );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CAknHighResPeriodic::~CAknHighResPeriodic()
    {
    }


// ---------------------------------------------------------------------------
// Starts the periodic timer.
// ---------------------------------------------------------------------------
//
void CAknHighResPeriodic::Start( TTimeIntervalMicroSeconds32 aDelay,
                                 TTimeIntervalMicroSeconds32 anInterval,
                                 TCallBack aCallBack)
    {
    iInterval = anInterval.Int();
    iCallBack = aCallBack;
    iEndTimeValid = EFalse;
    iWaiting = EFalse;
    HighRes( aDelay );
    }


// ---------------------------------------------------------------------------
// Sets minimum time between end of callback to beginning of next one.
// ---------------------------------------------------------------------------
//
void CAknHighResPeriodic::SetMinCallBackPeriod(
    TTimeIntervalMicroSeconds32 aDelay )
    {
    if ( aDelay.Int() >= 0 )
        {
        iMinCallBackPeriod = aDelay.Int();
        }
    else
        {
        iMinCallBackPeriod = 0;
        }
    }


// ---------------------------------------------------------------------------
// C++ constructor.
// ---------------------------------------------------------------------------
//
CAknHighResPeriodic::CAknHighResPeriodic( TInt aPriority,
                                          RThread* aNullThread )
    : CTimer( aPriority ), iDebugNullThread( aNullThread )
    {
    CActiveScheduler::Add( this );
    }


// ---------------------------------------------------------------------------
// Prints out the CPU time given to the null thread between this and previous
// call to this method.
// ---------------------------------------------------------------------------
//
void CAknHighResPeriodic::DumpNull()
    {
    TTimeIntervalMicroSeconds time;
    TInt err = iDebugNullThread->GetCpuTime( time );

    if ( !err )
        {
        if ( !iEndTimeValid )
            {
            iDebugPreviousTime = time.Int64();
            }
        else
            {
            TInt64 delta = time.Int64() - iDebugPreviousTime; 
            iDebugPreviousTime = time.Int64();
#ifdef AKNHIGHRESPERIODIC_PROFILE
            _LIT( KDMsg1, "[AKNPHYSICS] Null thread CPU time between frames: %d microseconds" );
            RDebug::Print( KDMsg1, TInt( delta ) );
#endif // AKNHIGHRESPERIODIC_PROFILE
            }
        }
    else
        {
#ifdef AKNHIGHRESPERIODIC_PROFILE
        _LIT( KDMsg2, "[AKNPHYSICS] Error %d in getting null thread CPU time" );
        RDebug::Print( KDMsg2, err );
#endif // AKNHIGHRESPERIODIC_PROFILE
        }
    }


// ---------------------------------------------------------------------------
// Handles timer completion.
// ---------------------------------------------------------------------------
//
void CAknHighResPeriodic::RunL()
    {
    if ( iEndTimeValid && !iWaiting ) 
        {
        TTime now;
        now.UniversalTime();
        
        TInt64 delta = now.MicroSecondsFrom( iEndTime ).Int64();
        if ( delta < 0 )
            {
            delta = 0;
            }

        TInt64 waitTime = iMinCallBackPeriod - delta; 
        
        if ( waitTime >= 0 )
            {
            // Restrict to some sensible min-max period.
            if ( waitTime < KAknHighResMinWait )
                {
                waitTime = KAknHighResMinWait;
                }

            if ( waitTime > KAknHighResMaxWait )
                {
                waitTime = KAknHighResMaxWait;
                }

            TInt timeToWait( waitTime );

#ifdef AKNHIGHRESPERIODIC_PROFILE
            _LIT( KDmsg, "[AKNPHYSICS] - CAknHighResPeriodic::RunL : waiting for %d microseconds" );
            RDebug::Print( KDmsg, timeToWait );
#endif            
            iWaiting = ETrue;
            HighRes( timeToWait );
            return;
            }
        }
    
    HighRes( iInterval );
    iCallBack.CallBack();
    
#ifdef AKNHIGHRESPERIODIC_PROFILE

    if ( iDebugNullThread && iDebugNullThread->Handle() )
        {
        DumpNull();
        }

#endif // AKNHIGHRESPERIODIC_PROFILE
    
    iWaiting = EFalse;
    iEndTime.UniversalTime();
    iEndTimeValid = ETrue;
    }



// ---------------------------------------------------------------------------
// CAknPhysics::NewL()
// ---------------------------------------------------------------------------
//
EXPORT_C CAknPhysics* CAknPhysics::NewL( MAknPhysicsObserver& aObserver,
                                         CCoeControl* aViewControl )
    {
    CAknPhysics* self = new ( ELeave ) CAknPhysics( aObserver );
    CleanupStack::PushL( self );
    self->ConstructL( aViewControl );
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// CAknPhysics::~CAknPhysics()
// ---------------------------------------------------------------------------
//
CAknPhysics::~CAknPhysics()
    {
    delete iPhysics;
    delete iEngine;
    delete iParamProvider;
    delete iRestrictor;
    delete iConeObserver;

    iNullThread.Close();
    }

// ---------------------------------------------------------------------------
// CAknPhysics::InitPhysicsL()
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknPhysics::InitPhysicsL( const TSize& aWorldSize, 
                                         const TSize& aViewSize, 
                                         TBool aLandscape )
    {
    if ( iRestrictor )
        {
        // Update always the restrictor parameters.
        iRestrictor->UpdatePhysicsEnvironment( aWorldSize,
                                               aViewSize,
                                               aLandscape );
        }
    
    // Do not initialize if all parameters match with old ones
    if ( aWorldSize == iWorldSize && aViewSize == iViewSize 
        && ( ( aLandscape && iLandscape ) || ( !aLandscape && !iLandscape ) ) )
        {
        return;    
        }

    StopPhysics();
    iEngine->DeletePhysics();

    iLandscape = aLandscape;

    iWorldSize = aWorldSize;
    iViewSize = aViewSize;
    if( (iLandscape && aWorldSize.iWidth < aViewSize.iWidth) 
            || (!iLandscape && aWorldSize.iHeight < aViewSize.iHeight) )
        {
        iWorldSize = aViewSize;
        }

    TInt64 ih, x, y, w, h, r;
    if(iLandscape)
        {
        ih = iWorldSize.iWidth;
        x = 1;
        y = 0;
        r = iViewSize.iHeight;
        }
    else
        {
        ih = iWorldSize.iHeight;
        x = 0;
        y = 1;
        r = iViewSize.iWidth;
        }

    w = iViewSize.iWidth;
    h = iViewSize.iHeight;
    
    if ( iEngine )
        {
        iEngine->CreateWorld( iParamProvider->Gravity() );
        iEngine->CreatePlanes( ih, x, y, r );
        iEngine->CreateViewBody( w, h, iParamProvider->ViewMass() );
        }
    }


// ---------------------------------------------------------------------------
// CAknPhysics::StartPhysics
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CAknPhysics::StartPhysics( TPoint& aDrag, 
                                          const TTime& aStartTime )
    {
    // Check that world really exists
    if ( !iEngine || !iEngine->WorldExists() )
        {
        return EFalse;
        }
    
    iSuspended = EFalse;

    TTime now;
    now.HomeTime();
    TInt moveTime( now.MicroSecondsFrom( aStartTime ).Int64() );

    TBool startPhysics( EFalse );
    iFlickTimeExceeded = EFalse;

    // Check if drag direction has changed during drag event
    // and receive the changed parameters
    if ( iConeObserver )
        {
        iConeObserver->DragChanged( iLandscape, aDrag, moveTime );
        }

    // Start physics if drag threshold is exceeded
    startPhysics = 
        ( iLandscape && Abs( aDrag.iX ) > DragThreshold() )
        || ( !iLandscape && Abs( aDrag.iY ) > DragThreshold() );
        
    // Check if movetime threshold is exceeded
    if ( startPhysics && moveTime > KFlickMaxDuration )
        {
        iFlickTimeExceeded = ETrue;
        }

    // Start physics always if position reveals empty space
    if ( !startPhysics && iRestrictor )
        {
        TPoint viewPosition( iObserver.ViewPosition() );
        startPhysics = 
            iRestrictor->PositionRevealsEmptySpace( viewPosition );
        }
        
    // Stop FPS logging here so that panning gets logged correctly. Each
    // panning always ends with a flick attempt.
    if ( iParamProvider->FpsLoggingEnabled() )
        {
        iEngine->StopFpsLogging();
        }

    if ( startPhysics && iEngine )
        {
        iEngine->SetViewBodyPosition( iObserver.ViewPosition() );
        StartPhysics();
        ApplyDrag( aDrag, moveTime ); 
        
        if ( iParamProvider->FpsLoggingEnabled() )
            {
            iEngine->StartFpsLogging();
            }
            
        return ETrue;
        }
    return EFalse;
    }


// ---------------------------------------------------------------------------
// CAknPhysics::StopPhysics()
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknPhysics::StopPhysics()
    {
    // Check that world really exists
    if ( !iEngine || !iEngine->WorldExists() )
        {
        return;
        }
    
    iSuspended = EFalse;

    iSamePositionCounter = 0;
    
    if ( iPhysics && iPhysics->IsActive() )
        {
        if ( iParamProvider->FpsLoggingEnabled() )
            {
            iEngine->StopFpsLogging();
            }

        CancelPhysicsTimer();
    
        if ( iEngine )
            {
            iEngine->ResetViewBodyForceAndVelocity();
            }
        iObserver.PhysicEmulationEnded();
        }
    else
        {
        UpdateActionState();
        }
    }


// ---------------------------------------------------------------------------
// CAknPhysics::OngoingPhysicsAction
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CAknPhysics::OngoingPhysicsAction() const
    {
    return iOngoingAction;
    }


// ---------------------------------------------------------------------------
// CAknPhysics::RegisterPanningPosition
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknPhysics::RegisterPanningPosition( const TPoint& aDelta )
    {
    TTimeIntervalMicroSeconds time;
    TInt err( KErrNone );
    if ( iNullThread.Handle() )
        {
        err = iNullThread.GetCpuTime( time );
        }
    else
        {
        err = KErrBadHandle;
        }
    
    TInt64 nullDelta = !err ? time.Int64() - iNullThreadTime : KMaxTInt64;
    
    TTime now;
    now.UniversalTime();
    
    TInt64 delta = Max( 0, now.MicroSecondsFrom( iTimeOfLastDraw ).Int64() );
    
#ifdef AKNHIGHRESPERIODIC_PROFILE

    _LIT( KDMsg1, "[AKNPHYSICS] - RegisterPanningPosition : Null thread CPU time between frames: %d microseconds" );
    _LIT( KDMsg2, "[AKNPHYSICS] - RegisterPanningPosition : Last draw %d microseconds ago");
    RDebug::Print( KDMsg1, TInt( nullDelta ) );
    RDebug::Print( KDMsg2, TInt( delta ) );
    
    if ( err )
        {
        _LIT( KDMsg3, "[AKNPHYSICS] Error %d in getting null thread CPU time" );
        RDebug::Print( KDMsg3, err );
        }
    
#endif // AKNHIGHRESPERIODIC_PROFILE
    
    TBool drawNow = EFalse;
    if ( nullDelta > FrameDelay() * 1000 ||       // There has been enough idle time.
         delta > MinFrameInterval() * 1000 ||     // Enough time since last draw.
         iTimeOfLastDraw.Int64() == Int64( 0 ) || // First draw.
         nullDelta < 0 )                          // Null thread CPU time not valid.
        {
        drawNow = ETrue;
        }

    iPanningDrawOmitted = !drawNow;
    
    TPoint position( iObserver.ViewPosition() );
    position += aDelta;

    if ( iRestrictor && iRestrictor->AllowedViewPosition( position ) )
        {
        if ( OngoingPhysicsAction() == EAknPhysicsActionNone )
            {
            iOngoingAction = EAknPhysicsActionDragging;
            
            if ( iParamProvider->FpsLoggingEnabled() )
                {
                iEngine->StartFpsLogging();
                }
            }
        
        NotifyViewPositionChanged( position, drawNow );
        
        if ( drawNow )
            {
            // Update the CPU time that the null thread has gotten.
            iNullThreadTime = time.Int64();
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknPhysics::SetFriction()
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknPhysics::SetFriction( TReal aFriction )
    {
    if ( iEngine )
        {
        iEngine->SetFriction( aFriction );
        }
    }


// ---------------------------------------------------------------------------
// CAknPhysics::ResetFriction()
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknPhysics::ResetFriction()
    {
    if ( iEngine )
        {
        iEngine->ResetFriction();
        }
    }


// ---------------------------------------------------------------------------
// CAknPhysics::HighlightTimeOut
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CAknPhysics::HighlightTimeout() const
    {
    if ( iParamProvider )
        {
        return iParamProvider->HighlightTimeout();
        }
    return 0;
    }


// ---------------------------------------------------------------------------
// CAknPhysics::DragThreshold
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CAknPhysics::DragThreshold() const
    {
    if ( iParamProvider )
        {
        return iParamProvider->DragThreshold();
        }
    return 0;
    }


// ---------------------------------------------------------------------------
// CAknPhysics::FeatureEnabled
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CAknPhysics::FeatureEnabled()
    {
    return CAknPhysicsParameterProvider::FeatureEnabled();
    }


// ---------------------------------------------------------------------------
// CAknPhysics::EventHandlingAllowed
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CAknPhysics::EventHandlingAllowed() const
    {
    if ( iConeObserver )
        {
        return iConeObserver->EventHandlingAllowed();
        }
    return ETrue;
    }


// ---------------------------------------------------------------------------
// CAknPhysics::UpdateViewWindowControl
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknPhysics::UpdateViewWindowControl( CCoeControl* aControl )
    {
    if ( iConeObserver )
        {
        iConeObserver->UpdateViewWindowControl( aControl );
        }
    }


// ---------------------------------------------------------------------------
// CAknPhysics::SuspendPhysics
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknPhysics::SuspendPhysics()
    {
    // Check that world really exists
    if ( !iEngine || !iEngine->WorldExists() )
        {
        return;
        }
    
    if ( iSuspended )
        {
        // Already suspended
        return;
        }
    iSuspended = ETrue;
    
    iSamePositionCounter = 0;
    if ( iPhysics && iPhysics->IsActive() )
        {
        if ( iParamProvider->FpsLoggingEnabled() )
            {
            iEngine->StopFpsLogging();
            }
        CancelPhysicsTimer();
        }
    else
        {
        UpdateActionState();
        }
    }


// ---------------------------------------------------------------------------
// CAknPhysics::ResumePhysics
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknPhysics::ResumePhysics()
    {
    if ( !iEngine || !iEngine->WorldExists() )
        {
        return;
        }
    
    if ( !iSuspended )
        {
        // Not suspended
        return;
        }
    iSuspended = EFalse;
    
    if ( iParamProvider->FpsLoggingEnabled() )
        {
        iEngine->StopFpsLogging();
        }

    iEngine->SetViewBodyPosition( iObserver.ViewPosition() );
    StartPhysics();         
            
    if ( iParamProvider->FpsLoggingEnabled() )
        {
        iEngine->StartFpsLogging();
        }
    }


// ---------------------------------------------------------------------------
// CAknPhysics::UpdateViewPosition
// ---------------------------------------------------------------------------
//
void CAknPhysics::UpdateViewPosition()
    {
    if ( iOngoingAction == CAknPhysics::EAknPhysicsActionNone
         || iOngoingAction == CAknPhysics::EAknPhysicsActionDragging )
        {
        TPoint viewPosition( iObserver.ViewPosition() );
        if ( iRestrictor 
            && iRestrictor->PositionRevealsEmptySpace( viewPosition ) )
            {
            NotifyViewPositionChanged( viewPosition );            
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknPhysics::Landscape
// ---------------------------------------------------------------------------
//
const TBool& CAknPhysics::Landscape()
    {
    return iLandscape;
    }


// ---------------------------------------------------------------------------
// CAknPhysics::ViewSize
// ---------------------------------------------------------------------------
//
const TSize& CAknPhysics::ViewSize()
    {
    return iViewSize;
    }


// ---------------------------------------------------------------------------
// CAknPhysics::WorldSize
// ---------------------------------------------------------------------------
//
const TSize& CAknPhysics::WorldSize()
    {
    return iWorldSize;
    }


// ---------------------------------------------------------------------------
// CAknPhysics::SurfaceErp
// ---------------------------------------------------------------------------
//
TInt CAknPhysics::SurfaceErp() const
    {
    if ( iParamProvider )
        {
        return iParamProvider->SurfaceErp();
        }
    return 0;
    }


// ---------------------------------------------------------------------------
// CAknPhysics::SurfaceCfm
// ---------------------------------------------------------------------------
//
TInt CAknPhysics::SurfaceCfm() const
    {
    if ( iParamProvider )
        {
        return iParamProvider->SurfaceCfm();
        }
    return 0;
    }

// ---------------------------------------------------------------------------
// CAknPhysics::IsPanningDrawIgnored
// ---------------------------------------------------------------------------
//
TBool CAknPhysics::IsPanningDrawOmitted() const
    {
    return iPanningDrawOmitted;
    }



// ---------------------------------------------------------------------------
// CAknPhysics::FrameDelay
// ---------------------------------------------------------------------------
//
TInt CAknPhysics::FrameDelay() const
    {
    if ( iParamProvider )
        {
        return iParamProvider->FrameDelay();
        }

    return KPhysicsMinTime / 1000;
    }


// ---------------------------------------------------------------------------
// CAknPhysics::MinFrameInterval
// ---------------------------------------------------------------------------
//
TInt CAknPhysics::MinFrameInterval() const
    {
    if ( iParamProvider )
        {
        return iParamProvider->MinFrameInterval();
        }

    return KPhysicsTime / 1000;
    }


// ---------------------------------------------------------------------------
// CAknPhysics::DrawViewInCurrentPosition
// ---------------------------------------------------------------------------
//
void CAknPhysics::DrawViewInCurrentPosition()
    {
    NotifyViewPositionChanged( iObserver.ViewPosition(), ETrue );
    }

// --------------------------------------------------------------------------
// CAknPhysics::SetBounceTactileFeedback
// --------------------------------------------------------------------------
//
void CAknPhysics::SetBounceTactileFeedback( TBool aBounceTactileFeedback )
    {
    iBounceTactileFeedback = aBounceTactileFeedback;
    }

// ---------------------------------------------------------------------------
// CAknPhysics::CAknPhysics
// ---------------------------------------------------------------------------
//
CAknPhysics::CAknPhysics( MAknPhysicsObserver& aObserver )
    : iObserver( aObserver ),
    iOngoingAction( EAknPhysicsActionNone ),
    iParamProvider( NULL ),
    iRestrictor( NULL ),
    iConeObserver( NULL ),
    iEngine( NULL ),
    iNullThreadTime( 0 ),
    iTimeOfLastDraw( 0 ), 
    iBounceTactileFeedback( ETrue ),
    iPanningDrawOmitted( EFalse )
    {
    }


// ---------------------------------------------------------------------------
// CAknPhysics::ConstructL()
// ---------------------------------------------------------------------------
//
void CAknPhysics::ConstructL( CCoeControl* aViewControl )
    {
    // Open the handle to the null thread.
    TBool nullThreadOpen = FindNullThread( iNullThread );
    
    // Create Physics timer to step physics emulation
    iPhysics = CAknHighResPeriodic::NewL(
        CActive::EPriorityStandard, nullThreadOpen ? &iNullThread : NULL );
    iPhysics->SetMinCallBackPeriod( FrameDelay() * 1000 );
    
    iEngine = CAknPhysicsEngine::NewL( this );
    iParamProvider = CAknPhysicsParameterProvider::NewL();
    iRestrictor = CAknPhysicsRestrictor::NewL( iParamProvider );
    iConeObserver = CAknPhysicsConeObserver::NewL( this, iRestrictor );
    iConeObserver->SetViewWindowControl( aViewControl );
    iFeedback = MTouchFeedback::Instance();
    }


// ---------------------------------------------------------------------------
// CAknPhysics::StartPhysics()
// ---------------------------------------------------------------------------
//
void CAknPhysics::StartPhysics()
    {
    // Check that world really exists
    if ( !iEngine || !iEngine->WorldExists() )
        {
        return;
        }

    iEngine->ResetCollisionState();
    iEngine->EnableViewBody();
    CancelPhysicsTimer();
    if ( iPhysics && !iPhysics->IsActive() )
        {
        iPhysics->Start(
                0, KPhysicsTime, TCallBack( CAknPhysics::Simulate, this ) );
		UpdateActionState();
        }
    }


// ---------------------------------------------------------------------------
// CAknPhysics::ApplyDrag()
// ---------------------------------------------------------------------------
//
void CAknPhysics::ApplyDrag( TPoint aDrag, TInt aMoveTime )
    {
    // Check that world really exists
    if ( !iEngine || !iEngine->WorldExists() )
        {
        return;
        }
    
    if ( iRestrictor )
        {
        iRestrictor->AdjustDragPoint( aDrag );
        }

    iEngine->ResetCollisionState();

    if(iLandscape)
        {
        if(aDrag.iY > iViewSize.iHeight/2 || aDrag.iY < -iViewSize.iHeight/2)
            aDrag.iX = 0;
        else
            aDrag.iY = 0;
        }
    else
        {
        if(aDrag.iX > iViewSize.iWidth/2 || aDrag.iX < -iViewSize.iWidth/2)
            aDrag.iY = 0;
        else
            aDrag.iX = 0;
        }

    if( aMoveTime < KSwipeDuration )
        {
        iEngine->ApplyDragForce( aDrag, aMoveTime );
        }
    }


// ---------------------------------------------------------------------------
// CAknPhysics::Simulate()
// ---------------------------------------------------------------------------
//
TInt CAknPhysics::Simulate(TAny* aSelf)
    {
    CAknPhysics* self = (CAknPhysics*) aSelf;
    self->DoSimulation();
    return KErrNone;
    }


// ---------------------------------------------------------------------------
// CAknPhysics::DoSimulation()
// ---------------------------------------------------------------------------
//
void CAknPhysics::DoSimulation()
    {
    if ( iFlickTimeExceeded && iOngoingAction != EAknPhysicsActionBouncing  )
        {
        iFlickTimeExceeded = EFalse;
        StopPhysics();
        return;
        }

    TPoint previousViewPosition;
    TPoint currentViewPosition;

    // get position before step
    iEngine->GetViewBodyPosition( previousViewPosition );
    
    CAknPhysicsEngine::TAknPhysicsCollision prevState = iEngine->CollisionState();

    iEngine->TakePhysicsStep();

    // get position after step
    iEngine->GetViewBodyPosition( currentViewPosition );
    
    // Signal physics stop only after a possible view position change has been 
    // communicated.
    TBool stopPhysics = EFalse;
    
    // if iViewBody gets auto disabled, it's safe to stop physics emulation 
    if( !iEngine->IsViewBodyEnabled() )
        {
        stopPhysics = ETrue;
        }
    else if ( prevState != CAknPhysicsEngine::EAknPhysicsNoCollision )
        {

        TBool collisionChanged( 
            iEngine->CollisionState() != CAknPhysicsEngine::EAknPhysicsNoCollision 
            && iEngine->CollisionState() != prevState );
        TBool topCollision( prevState == CAknPhysicsEngine::EAknPhysicsTopCollision );
        TBool previousOut( EFalse );
        TBool currentOut( EFalse );

        // Check if positions are out of boundaries
        if ( iRestrictor )
            {
            previousOut = iRestrictor->PositionIsOutOfBoundaries( 
                previousViewPosition, topCollision );
            currentOut = iRestrictor->PositionIsOutOfBoundaries( 
                currentViewPosition, topCollision );
            }

        // Stop bounce if
        // 1) Collision has changed from top to bottom or bottom to top
        // 2) Current view position is out of boundaries (and previous was not)
        // -> prevent view flicking when bounce ends
        // 3) Collision type has changed to no collision and both of the view
        // positions are inside view boundaries.
        if ( collisionChanged 
            || currentOut && !previousOut
            || !currentOut && !previousOut 
            && iEngine->CollisionState() == CAknPhysicsEngine::EAknPhysicsNoCollision )
            {
            if ( topCollision || collisionChanged )
                {
                iRestrictor->PositionToViewTop( currentViewPosition );
                }
            else
                {
                iRestrictor->PositionToViewBottom( currentViewPosition );
                }
            stopPhysics = ETrue;
            iEngine->ResetCollisionState();
            // boundary effect                       
            if ( iBounceTactileFeedback && iFeedback )
                {
                iFeedback->InstantFeedback( NULL,
                                            ETouchFeedbackBounceEffect,
                                            ETouchFeedbackVibra,
                                            TPointerEvent() );
                }
            }

        // Previous view position and current view position are out of view
        // boundaries -> bounce has changed to flick
        else if ( currentOut && previousOut )
            {
            iEngine->ResetCollisionState();
            }
        }

    UpdateActionState();

    if ( currentViewPosition == previousViewPosition )
        {
        iSamePositionCounter++;
        // Never stop physics while bouncing even though
        // same position count has been exceeded
        if ( iOngoingAction != EAknPhysicsActionBouncing 
            && iSamePositionCounter >= KSamePositionStopCount )
            {
            stopPhysics = ETrue;
            }
        }

    NotifyViewPositionChanged( currentViewPosition );
       
    if ( stopPhysics )
        {
        StopPhysics();
        }
    }


// ---------------------------------------------------------------------------
// CAknPhysics::CancelPhysicsTimer()
// ---------------------------------------------------------------------------
//
void CAknPhysics::CancelPhysicsTimer()
    {
    if ( iPhysics )
        {
        iPhysics->Cancel();
        UpdateActionState();
        }
    }


// ---------------------------------------------------------------------------
// CAknPhysics::UpdateActionState()
// ---------------------------------------------------------------------------
//
void CAknPhysics::UpdateActionState()
    {
    if ( iPhysics && iPhysics->IsActive() )
        {
        // If we are colliding or physics timer is active and view is about
        // to bounce -> action to bouncing
        if ( iEngine->CollisionState() != CAknPhysicsEngine::EAknPhysicsNoCollision
            || ( iOngoingAction == EAknPhysicsActionNone && ViewAboutToBounce() ) )
            {
            iOngoingAction = EAknPhysicsActionBouncing;
            }
        // Otherwise we are flicking
        else
            {
            iOngoingAction = EAknPhysicsActionFlicking;
            }
        }
    else
        {
        iOngoingAction = EAknPhysicsActionNone;
        }

    if ( iConeObserver )
        {
        iConeObserver->PhysicsStateChanged();
        }
    }


// ---------------------------------------------------------------------------
// CAknPhysics::ViewAboutToBounce()
// ---------------------------------------------------------------------------
//
TBool CAknPhysics::ViewAboutToBounce()
    {
    TPoint viewPosition( iObserver.ViewPosition() );
    if ( iRestrictor && iRestrictor->PositionRevealsEmptySpace( viewPosition ) )
        {
        return ETrue;
        }
    return EFalse;
    }


// ---------------------------------------------------------------------------
// CAknPhysics::NotifyViewPositionChanged
// ---------------------------------------------------------------------------
//
void CAknPhysics::NotifyViewPositionChanged( const TPoint& aPosition,
                                             TBool aDrawNow )
    {
    iObserver.ViewPositionChanged( aPosition, aDrawNow, 0 );
    
    if ( aDrawNow )
        {
        // Update the time of the last draw.
        iTimeOfLastDraw.UniversalTime();
        }
    }

// End of File
