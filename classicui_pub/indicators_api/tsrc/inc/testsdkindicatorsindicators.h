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
* Description:  for testing the indicators api module
*
*/


#ifndef C_TESTSDKINDICATORSINDICATORS_H
#define C_TESTSDKINDICATORSINDICATORS_H

// INCLUDES
#include <aknindicatorcontainer.h>

// CLASS DECLARATION

/**
 *  Ctestsdkindicatorsindicators
 * 
 */
class CTestSDKIndicatorsIndicators : public CAknIndicatorContainer
	{
public: // From base class @c CCoeControl.
	/**
	* Handles a change to the control's resources of type @c aType
	* which are shared across the environment, e.g. color scheme change.
    * Responds fade events and fades incall status bubble window group.
    *
	* @param  aType  Event type.
	*/
    virtual void HandleResourceChange( TInt aType );

    /**
    * Handles size change events.
    */
    virtual void SizeChanged();

    /**
    * Handles position change events.
    */
    virtual void PositionChanged();

    /**
    * Returns number of controls inside the context pane control.
    *
    * @return Amount of component controls.
    */
    virtual TInt CountComponentControls() const;

    /**
    * Returns a control determined by control index.
    *
    * @param  aIndex  Index of a control to be returned.
    * @return Pointer to control
    */
    virtual CCoeControl* ComponentControl( TInt aIndex ) const;

public:

    /**
    * Default constructor.
    * Creates an @c EUniversalIndicators object.
    */
	CTestSDKIndicatorsIndicators();	

    /**
    * Destructor.
    */
	~CTestSDKIndicatorsIndicators();
	
    /** 
    * Constructs the object from resource.
    *
    * @param  aReader  Resource reader.
    */
	void ConstructFromResourceL( TResourceReader& aReader );
	
	void Reserved_1();
	
	};

#endif // C_TESTSDKINDICATORSINDICATORS_H
