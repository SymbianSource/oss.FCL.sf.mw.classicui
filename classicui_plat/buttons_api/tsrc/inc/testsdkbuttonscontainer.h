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
* Description:  ccoecontrl class to test some functions
*
*/

#ifndef C_TESTSDKBUTTONSCONTAINER_H
#define C_TESTSDKBUTTONSCONTAINER_H

// INCLUDES
#include <coecntrl.h>
#include <eikcmobs.h>

/*
* A container class has window for test
*/
class CButtonControl : public CCoeControl, public MEikCommandObserver
    {
public:
    /*
     * static NewL function to build this object
     * */
    static CButtonControl* NewL( TRect& aRect );
    
    /*
     * deconstructor
     * */
    ~CButtonControl();
    
    /*
     * set component control
     * */
    void SetComponentControlL( CCoeControl* aControl );
    
    /*
     * unset component control
     * */
    void ResetComponentControl();
    
    /*
     * ActivateGc for winserver9 error
     * */
    void ActivateGc();
    
    /*
     * DeactivateGc for winserver9 error
     * */
    void DeactivateGc();
    
private:
    /*
     * constructor
     * */
    CButtonControl();
    
    /*
     * 2rd phase constructor
     * */
    void ConstructL( TRect& aRect );
    
    /*
     * for components
     * */
    TInt CountComponentControls() const;
    
    /*
     * for components
     * */
    CCoeControl *ComponentControl( TInt aIndex ) const;
    
    /*
     * from MEikCommandObserver
     * */
    void ProcessCommandL( TInt aCommandId );
    
private:
    // Data
    /*
     * Not own, for component control
     * */
    CCoeControl* iControl;
    };

#endif /*C_TESTSDKBUTTONSCONTAINER_H*/
