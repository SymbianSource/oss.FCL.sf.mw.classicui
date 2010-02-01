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
* Description:  AknPhysics parameter provider
*
*/


#ifndef C_AKNPHYSICSPARAMETERPROVIDER_H
#define C_AKNPHYSICSPARAMETERPROVIDER_H


#include <e32base.h>
#include "aknphysicscenreplistener.h"

class CRepository;

/**
 *  ODE parameter provider
 *
 */
NONSHARABLE_CLASS( CAknPhysicsParameterProvider ) : public CBase, 
                                                    public MAknPhysicsCenRepObserver
    {

public:

    /**
     * Two-phased constructor.
     */
    static CAknPhysicsParameterProvider* NewL();

    /**
     * Two-phased constructor.
     */
    static CAknPhysicsParameterProvider* NewLC();

    /**
     * Destructor.
     */
    virtual ~CAknPhysicsParameterProvider();
    
    /**
     * Returns view mass value.
     *
     * @return View mass value.
     */
    TInt ViewMass() const;
    
    /**
     * Returns gravity value.
     *
     * @return Gravity value.
     */
    TInt Gravity() const;
    
    /**
     * Returns surface erp value.
     *
     * @return Surface erp value.
     */
    TInt SurfaceErp() const;
    
    /**
     * Returns surface cfm value.
     *
     * @return Surface cfm value.
     */
    TInt SurfaceCfm() const;

    /**
     * Returns highlight timeout value.
     *
     * @return Highlight timeout value.
     */
    TInt HighlightTimeout() const;
    
    /**
     * Returns drag threshold value.
     *
     * @return Drag threshold value.
     */
    TInt DragThreshold() const;

    /**
     * Returns frame delay value.
     *
     * @return Frame delay value.
     */
    TInt FrameDelay() const;

    /**
     * Returns min frame interval value.
     *
     * @return Min frame interval value.
     */
    TInt MinFrameInterval() const;

    /**
     * Returns ETrue if ode feature is enabled.
     *
     * @return ETrue if feature is enabled.
     */
    static TBool FeatureEnabled();
    
    /**
     * Returns short list empty space value.
     *
     * @return Short list empty space value.
     */
    TInt ShortListEmptySpace() const;

    /**
     * Returns long list empty space value.
     *
     * @return Long list empty space value.
     */
    TInt LongListEmptySpace() const;
    
    /**
     * Returns whether FPS logging is enabled.
     */
    TBool FpsLoggingEnabled() const;

// from base class MAknPhysicsCenRepObserver

    /**
     * Informs the observer that the cenrep
     * value have been changed.
     *
     * @param aKey CenRep value key.
     */
    void CenRepValueChanged( const TInt& aKey );

private:

    /**
     * C++ constructor.
     */
    CAknPhysicsParameterProvider();

    /**
     * Symbian second-phase constructor.
     */
    void ConstructL();
    
    /**
     * Reads ode parameters from cen rep.
     */
    void ReadValuesFromCenRepL();

    /**
     * Sets ode parameters as defaults.
     *
     * @param aWriteToCenRep ETrue if values should be written to cen rep.
     */
    void SetDefaultValues( TBool aWriteToCenRep );

    /**
     * Checks are the values set.
     */
    TBool ValuesAreSet();

private: // data

    /**
     * Central repository.
     * Own.
     */
    CRepository* iCenRep;
    
    /**
     * View mass value.
     */
    TInt iViewMass;

    /**
     * Gravity value.
     */
    TInt iGravity;

    /**
     * Surface erp value.
     */
    TInt iSurfaceErp;

    /**
     * Surface cfm value.
     */
    TInt iSurfaceCfm;

    /**
     * Highlight timeout value.
     */
    TInt iHighlightTimeout;

    /**
     * Drag threshold value.
     */
    TInt iDragThreshold;
    
    /**
     * Frame delay value.
     */
    TInt iFrameDelay;
    
	/**
     * Min frame interval value.
     */
    TInt iMinFrameInterval;
	
    /**
     * Empty space percent in short lists.
     */
    TInt iShortListEmptySpace;

    /**
     * Empty space percent in long lists.
     */
    TInt iLongListEmptySpace;
    
    /**
     * FPS logging enabled / disabled.
     */
    TBool iFpsLoggingEnabled;
    
    /**
     * CenRep listener.
     * Own.
     */
    CAknPhysicsCenRepListener* iListener;

    };


#endif // C_AKNPHYSICSPARAMETERPROVIDER_H
