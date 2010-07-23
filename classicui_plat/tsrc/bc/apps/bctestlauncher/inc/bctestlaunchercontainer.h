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
* Description:         Declares container control for application.
*
*/









#ifndef C_CBCTESTLAUNCHERCONTAINER_H
#define C_CBCTESTLAUNCHERCONTAINER_H

#include <coecntrl.h>
#include <eikon.hrh>
#include <eikapp.h>

#include "BCTestLauncher.hrh"

class CAknTitlePane;

/**
 *  CBCTestLauncherContainer  container control class.
 */
class CBCTestLauncherContainer : public CCoeControl, 
                                 public MCoeControlObserver
    {
public: // Constructors and destructor
    /**
     * C++ default constructor
     */
    CBCTestLauncherContainer();         

    /**
     * Symbian 2nd phase constructor.
     * @param aRect Frame rectangle for container.
     */
    void ConstructL( const TRect& aRect );

    /**
     * Destructor.
     */
    virtual ~CBCTestLauncherContainer();

public: // New functions

	/**
	 * Clears the entire screen
	 */
	void ClearScreen();
	
	/**
	 * Makes the status pane and cba labels visible
	 */
	void RestoreScreen();
    	void SetSdkVersion();

private: // Functions from base classes

    /**
     * From CoeControl,CountComponentControls.
     * @return amount of component controls,
     *         in this application, this is the
     *         number of progress bars.
     */
    TInt CountComponentControls() const;

    /**
     * From CCoeControl,ComponentControl.
     * @param aIndex each component controls in order
     * @return Ptr to each component controls
     */
    CCoeControl* ComponentControl( TInt aIndex ) const;

    /**
     * From CCoeControl,Draw.
     * @param aRect Frame rectangle for container
     */
    void Draw( const TRect& aRect ) const;


private : // Functions from base classes
    /**
     * From MCoeControlObserver
     * @param aControl each component controls
     * @param aEventType event type
     */
    void HandleControlEventL( 
            CCoeControl* /*aControl*/, TCoeEvent /*aEventType*/ );

private: //data
    CAknTitlePane* 				iTitlePane;
    CEikButtonGroupContainer*   iCba;

    };

#endif // C_CBCTESTLAUNCHERCONTAINER_H

