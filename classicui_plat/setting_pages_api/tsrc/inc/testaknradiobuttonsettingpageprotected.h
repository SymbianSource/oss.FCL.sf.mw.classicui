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
* Description:  Test aknradiobuttonsettingpage.h
*
*/

#ifndef C_TESTAKNRADIOBUTTONSETTINGPAGEPROTECTED_H
#define C_TESTAKNRADIOBUTTONSETTINGPAGEPROTECTED_H

//INCLUDE
#include <aknradiobuttonsettingpage.h>

/*
 * This class inherit from the CAknRadioButtonSettingPage class for 
 * testing the CAknRadioButtonSettingPage's protected function
 */
class CTestRadioButtonSettingPage:public CAknRadioButtonSettingPage
    {
public:
    /*
     * Constructor
     */
    CTestRadioButtonSettingPage( TInt aResourceID, 
        TInt& aCurrentSelectionIndex, 
        const MDesCArray* aItemArray );
    /*
     * Constructor
     */
    CTestRadioButtonSettingPage( const TDesC* aSettingTitleText, 
        TInt aSettingNumber, 
        TInt aControlType,
        TInt aEditorResourceId, 
        TInt aSettingPageResourceId,
        TInt& aCurrentSelectionIndex, 
        const MDesCArray* aItemArray );
    /*
     * Destructor
     */
    ~CTestRadioButtonSettingPage();
    /*
     * This fuction is wrote for testing UpdateSettingL() function
     */
    void DoUpdateSettingL();
    /*
     * This fuction is wrote for testing DynamicInitL() function
     */
    void DoDynamicInitL();
    /*
     * This fuction is wrote for testing SelectCurrentItemL() function
     */
    void DoSelectCurrentItemL();
    /*
     * This fuction is wrote for testing WriteInternalStateL() function
     */
    void DoWriteInternalStateL(RWriteStream& aWriteStream) const;
    };

#endif /*C_TESTAKNRADIOBUTTONSETTINGPAGEPROTECTED_H*/

//End file


