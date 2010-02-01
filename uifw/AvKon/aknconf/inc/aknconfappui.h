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
* Description:  Declares UI class for application.
 *
*/


#ifndef __AKNCONFAPPUI_H__
#define __AKNCONFAPPUI_H__

// INCLUDES
#include <aknViewAppUi.h>
#include <AknTabObserver.h>

// FORWARD DECLARATIONS
class CAknConfView;
class CAknNavigationDecorator;

// CLASS DECLARATION
/**
 * CAknConfAppUi application UI class.
 * Interacts with the user through the UI and request message processing
 * from the handler class
 */
class CAknConfAppUi : public CAknViewAppUi, public MAknTabObserver
    {
public:
    // Constructors and destructor

    /**
     * ConstructL.
     * 2nd phase constructor.
     */
    void ConstructL();

    /**
     * CAknConfAppUi.
     * C++ default constructor. This needs to be public due to
     * the way the framework constructs the AppUi
     */
    CAknConfAppUi();

    /**
     * ~CAknConfAppUi.
     * Virtual Destructor.
     */
    virtual ~CAknConfAppUi();

    /**
     * Sets tab index.
     */
    void SetTabIndex( TInt aViewId );

// from base class MAknTabObserver
    /**
     * Method for handling tab change events in observed classes. 
     * 
     * @param aIndex Index of the active tab.
     *
     */
    void TabChangedL( TInt aIndex );


private:

    /**
     * Activates view. 
     * 
     * @param aViewId View id.
     */
    void ActivateViewL( TUid aViewId );

    /**
     * Returns pointer to active view.
     * 
     * @return Pointer to active view.
     */
    CAknConfView* CurrentView();

    // Functions from base classes

    /**
     * From CEikAppUi, HandleCommandL.
     * Takes care of command handling.
     * @param aCommand Command to be handled.
     */
    void HandleCommandL(TInt aCommand);

    /**
     *  HandleStatusPaneSizeChange.
     *  Called by the framework when the application status pane
     *  size is changed.
     */
    void HandleStatusPaneSizeChange();

private:
    // Data
    /**
     * Current view id.
     */
    TInt iCurrentViewId;

    /**
     * Navi decorator.
     * Own.
     */
    CAknNavigationDecorator* iDecorator;

    };

#endif // __AKNCONFAPPUI_H__
// End of File
