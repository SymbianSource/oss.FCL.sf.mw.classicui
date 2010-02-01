/*
* Copyright (c) 2004-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Background task for creating views.
*
*/


#ifndef C_PSLNIDLETASKCREATEVIEWS_H
#define C_PSLNIDLETASKCREATEVIEWS_H

#include <e32base.h>

class CPslnUi;

/**
 *  Creates Themes application views in the background when application 
 *  is idle.
 *  @since S60 v3.1
 */
class CPslnIdleTaskCreateViews : public CBase
    {
public:

    /**
    * Two-phased constructor.
    * @param aPslnUi pointer to UI class.
    * @return new instance of CPslnIdleTaskCreateViews.
    */
    static CPslnIdleTaskCreateViews* NewL( CPslnUi* aPslnUi );
    
    /**
    * Destructor.
    */
    virtual ~CPslnIdleTaskCreateViews();

    /**
    * From MAknBackgroundProcess.
    * Return ETrue when the process is done.
    * @return ETrue if process is ready.
    */
    TBool IsFinished() const;

private:

    /**
    * Callback when idle time occurs.
    */
    static TInt DoHandleIdleTimeL( TAny* aAny );

    /**
    * When idle time occurs, creates a new view, until all views
    * have been created.
    */
    void HandleIdleTimeL();

    /**
    * C++ constructor.
    */
    CPslnIdleTaskCreateViews( CPslnUi* aPslnUi );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

private: // data

    /**
    * Reference to Psln UI class.
    * Not own.
    */
    CPslnUi* iPslnUi;

    /**
    * Has the task been done.
    */
    TBool iDone;

    /**
    * Internal state.
    */
    TInt iIdleStep;

    /**
    * Idle task that creates views in the background.
    * Own.
    */
    CIdle* iIdleTask;
    };

#endif // C_PSLNIDLETASKCREATEVIEWS_H
