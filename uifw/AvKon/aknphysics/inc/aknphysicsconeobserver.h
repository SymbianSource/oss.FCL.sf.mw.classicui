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
* Description:  AknPhysics control environment observer
*
*/


#ifndef C_AKNPHYSICSCONEOBSERVER_H
#define C_AKNPHYSICSCONEOBSERVER_H


#include <coemain.h>
#include <e32base.h>

class CAknPhysics;
class CAknPhysicsKeyConsumer;
class CAknPhysicsRestrictor;
class CCoeControl;
class CAknPhysicsDragObserver;
class CAknAppUi;

/**
 *  AknPhysics control environment observer
 *
 */
NONSHARABLE_CLASS( CAknPhysicsConeObserver ) 
    : 
    public CBase, 
    public MCoeForegroundObserver, 
    public MCoeMessageMonitorObserver
    {

public:

    /**
     * Two-phased constructor.
     */
    static CAknPhysicsConeObserver* NewL( CAknPhysics* aPhysics,
                                          CAknPhysicsRestrictor* aRestrictror );

    /**
     * Two-phased constructor.
     */
    static CAknPhysicsConeObserver* NewLC( CAknPhysics* aPhysics,
                                           CAknPhysicsRestrictor* aRestrictror );

    /**
     * Destructor.
     */
    virtual ~CAknPhysicsConeObserver();
    
    /**
     * Returns ETrue if event handling is allowed.
     *
     * @return ETrue if event handling is allowed.
     */
    TBool EventHandlingAllowed() const;

    /**
     * Sets view window control.
     *
     * @param aControl New view control.
     */
    void SetViewWindowControl( CCoeControl* aControl );

    /**
     * Informs that physics state is changed.
     */
    void PhysicsStateChanged();

    /**
     * Returns ETrue if drag parameters has changed during view control
     * dragging event.
     *
     * @param aLandscape ETrue if physics view is in landscape.
     * @param aDragDistance Changed drag distance.
     * @param aMoveTime Changed drag move time.
     * @return ETrue if drag direction has changed.
     */
    TBool DragChanged( const TBool& aLandscape,
                       TPoint& aDragDistance, 
                       TInt& aMoveTime ) const;

    /**
     * Updates view window control.
     *
     * @param aControl New view control.
     */
    void UpdateViewWindowControl( CCoeControl* aControl );

private:

    /**
     * C++ constructor.
     */
    CAknPhysicsConeObserver( CAknPhysics* aPhysics, CAknPhysicsRestrictor* aRestrictror );

    /**
     * Symbian second-phase constructor.
     */
    void ConstructL();

    /**
     * Returns the ongoing physics action.
     *
     * @return Ongoing physics action.
     */
    TInt OngoingAction() const;
    
    /**
     * Returns code that determines where the pointerevent was targeted.
     *
     * @param aPointerEvent Event to be tested.
     * @param aTargetControl Event target control.
     * @return TPointerEventTarget type target code.
     */
    TInt EventTargetedToView( const TPointerEvent* aEvent, 
                              const CCoeControl* aTargetControl );

    /**
     * Returns ETrue if physics should be stopped with pointer
     * event.
     *
     * @param aEvent Pointer event.
     * @param aTargetControl Event target control.
     * @return ETrue if physics should be stopped.
     */
    TBool MonitorPointerEvent( TPointerEvent* aEvent,
                               CCoeControl* aTargetControl );

    /**
     * Returns ETrue if physics should be stopped with key event.
     *
     * @param aEvent Key event.
     * @return ETrue if physics should be stopped.
     */
    TBool MonitorKeyEvent( TKeyEvent* aEvent );

    /**
     * Returns ETrue if pointer event modifier has modified the pointer event.
     * This is the case e.g. if scroll bar extension is in view control
     * area and pointer event is actually targeted to scroll bar instead of
     * view control.
     *
     * @param aEvent Pointer event.
     * @param aTargetControl Event target control.
     * @return ETrue pointer event modifier has modified the pointer event.
     */
    TBool PointerEventModified( TPointerEvent* aEvent,
                                CCoeControl* aTargetControl );

    /**
     * Provides application AknAppUi.
     */
    CAknAppUi* AppUi();

// from base class MCoeForegroundObserver

    /**
     * Handles the application coming to the foreground.
     */
    void HandleGainingForeground();

    /**
     * Handles the application going into the background.
     */
    void HandleLosingForeground();

// from base class MCoeMessageMonitorObserver
    
    /**
     * Received windows messages for monitoring.
     *
     * @param aEvent The windows server event data.
     */
    void MonitorWsMessage( const TWsEvent &aEvent );

private: // data


    /**
     * Pointer event target enum.
     */
    enum TPointerEventTarget
        {
        ETargetViewControl = 1,
        ETargetOtherControl,
        ETargetUnresolvedControl,
        ETargetChildControl
        };

    /**
     * Physics object.
     * Not own.
     */
    CAknPhysics* iPhysics;

    /**
     * Key consuming control.
     * Own.
     */
    CAknPhysicsKeyConsumer* iKeyConsumer;
    
    /**
     * Control environment.
     * Not own.
     */
    CCoeEnv* iCoeEnv;

    /**
     * ETrue if physics event handling is allowed.
     */
    TBool iEventsAllowed;

    /**
     * ETrue if observer is monitoring wsevents.
     */
    TBool iMonitoringWs;

    /**
     * Physics view window control.
     * Not own.
     */
    CCoeControl* iWindowControl;

    /**
     * Physics view control.
     * Not own.
     */
    CCoeControl* iViewControl;

    /**
     * Physics restrictor.
     * Not own.
     */
    CAknPhysicsRestrictor* iRestrictor;

    /**
     * Drag observer.
     * Own.
     */
    CAknPhysicsDragObserver* iDragObserver;

    };


#endif // C_AKNPHYSICSCONEOBSERVER_H
