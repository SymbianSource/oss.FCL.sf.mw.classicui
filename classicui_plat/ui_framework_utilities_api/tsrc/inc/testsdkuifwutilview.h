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
* Description:  view class for test
*
*/


#ifndef C_TESTSDKUIFWUTILVIEW_H
#define C_TESTSDKUIFWUTILVIEW_H

#include <aknview.h>

// CONSTANTS
const TUid KCTestUiFwUtilViewId = { 0x11111111 };

// FORWARD DECLARATIONS
class CTestUiFwUtilContainer;

/*
 * View class for listbox
 */
class CTestUiFwUtilView : public CAknView
    {
public:
    
    /**
    * New a CTestUiFwUtilView object
    */
    static CTestUiFwUtilView* NewL();
    
    /**
    * Deconstructor
    */
    ~CTestUiFwUtilView();
    /**
    * Return view id
    */
    TUid Id() const;
    
    /**
    * Return container
    */
    CTestUiFwUtilContainer* GetContainer();
    
private:
    /**
    * 2nd phrase constructor
    */
    void ConstructL();
    /**
    * Constructor
    */
    CTestUiFwUtilView();
    
    /**
    * Activates view
    */
    void DoActivateL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,
        const TDesC8& aCustomMessage);
    
    /**
    * Deactivates view
    */
    void DoDeactivate();
    
private: // Data
    /**
    * Container
    * Own
    */
    CTestUiFwUtilContainer* iContainer;
    };

#endif /*C_TESTSDKUIFWUTILVIEW_H*/

// End of file

