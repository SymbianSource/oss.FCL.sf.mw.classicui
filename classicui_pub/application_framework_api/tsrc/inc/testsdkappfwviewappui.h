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
* Description:  Test application_framework_api
*
*/



#ifndef C_TESTSDKAPPFWVIEWAPPUI_H
#define C_TESTSDKAPPFWVIEWAPPUI_H

//  INCLUDES
#include "testsdkappfw.h"

/**
*  CTestSDKAppFWAppUi test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestSDKAppFWViewAppUi ) : public CAknViewAppUi
    {
public:

    /**
    * Two-phased constructor.
    */
    static CTestSDKAppFWViewAppUi* NewL();

    /**
     * Constructor.
     */
    CTestSDKAppFWViewAppUi();

    /**
     * Destructor.
     */
    virtual ~CTestSDKAppFWViewAppUi();

    /**
     * symbian 2nd constructor
     */
    void ConstructL();

    /**
    * From @c MEikStatusPaneObserver. Handles a change in the position or
    * size of the screen area occupied by the status pane.
    */
    void ProtectedHandleStatusPaneSizeChange();

    /**
    * From @c CCoeAppUi. Handles changes in keyboard focus when
    * an application switches to foreground.
    * @param aForeground @c ETrue if the application is in the foreground,
    * otherwise @c EFalse.
    */
    void ProtectedHandleForegroundEventL( TBool aForeground );

    /**
    * From AknAppUi. Handles pointer-initiated view switch. Currently this
    * function does nothing but calls base class function.
    * @since Series 60 3.0
    * @param aEvent Window server event.
    * @param aDestination Pointer to the control which the event is targeted to.
    */
    void ProtectedHandleWsEventL( const TWsEvent& aEvent, CCoeControl* aDestination );

    };

#endif      // C_TESTSDKAPPFWVIEWAPPUI_H

// End of File
