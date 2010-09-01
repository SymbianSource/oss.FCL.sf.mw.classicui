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
* Description:  Test akncheckboxsettingpage.h
*
*/

#ifndef C_TESTAKNCHECKBOXSETTINGPAGEPROTECTED_H
#define C_TESTAKNCHECKBOXSETTINGPAGEPROTECTED_H
//INCLUDE
#include <akncheckboxsettingpage.h>

/*
 * This class inherit from CAknCheckBoxSettingPage for testing the
 * CAknCheckBoxSettingPage
 * class's protected function.
 */
class CTestCheckBoxSettingPage:public CAknCheckBoxSettingPage
    {
public:
    /*
     * Constructor
     */
    CTestCheckBoxSettingPage( TInt aResourceID, CSelectionItemList* aItemArray );
    /*
     * Constructor
     */
    CTestCheckBoxSettingPage( const TDesC* aSettingTitleText, 
            TInt aSettingNumber, 
            TInt aControlType,
            TInt aEditorResourceId, 
            TInt aSettingPageResourceId,
            CSelectionItemList* aItemArray );
    /*
     * Destructor
     */
    ~CTestCheckBoxSettingPage();
    /*
     * This function is wrote for testing UpdateSettingL() function
     */
    void TestUpdateSettingL();
    /*
     * This function is wrote for testing DynamicInitL() function
     */
    void TestDynamicInitL();
    /*
     * This function is wrote for testing ProcessCommandL() function
     */
    void TestProcessCommandL(TInt aCommandId);
    /*
     * This function is wrote for testing SelectCurrentItemL() function
     */
    void TestSelectCurrentItemL();
    /*
     * This function is wrote for testing WriteInternalStateL() function
     */
    void TestWriteInternalStateL(RWriteStream& aWriteStream) const;
    };

#endif /*C_TESTAKNCHECKBOXSETTINGPAGEPROTECTED_H*/
//End file


