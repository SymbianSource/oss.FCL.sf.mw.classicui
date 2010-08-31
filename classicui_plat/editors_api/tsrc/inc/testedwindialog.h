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
* Description:  a subclass of CAknDialog which has a CEikEdwin. This dialog is 
* to test smiley feature of CEikEdwin.
*
*/

#ifndef TESTEDWINDIALOG_H_
#define TESTEDWINDIALOG_H_

#include <AknDialog.h>

class TestEdwinDialog : public CAknDialog
    {
public:     // construction
    static TInt RunDlgLD( TInt aResouceId );
private:    // construction
    TestEdwinDialog();
    virtual ~TestEdwinDialog();
    
private:    // from CAknDialog
    void PreLayoutDynInitL(); // initialize controls
    void ProcessCommandL( TInt aCommandId );
    TKeyResponse OfferKeyEventL
        ( const TKeyEvent& aKeyEvent, TEventCode aType );
    };

#endif /* TESTEDWINDIALOG_H_ */
