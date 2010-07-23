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
* Description:  Test akntextsettingpage.h
*
*/

#ifndef C_TESTAKNTEXTSETTINGPAGEPROTECTED_H
#define C_TESTAKNTEXTSETTINGPAGEPROTECTED_H
//Include files
#include <akntextsettingpage.h>
/*
 * This class inherit from the CAknIntegerSettingPage class for 
 * testing the class CAknIntegerSettingPage's protected function
 */ 
class CTestEdwinSettingPage:public CAknEdwinSettingPage
    {
public:
    /*
     * Constructor
     */
    CTestEdwinSettingPage( TInt aResourceId );
    /*
     * Constructor
     */
    CTestEdwinSettingPage( const TDesC* aSettingTitleText, 
        TInt aSettingNumber, 
        TInt aControlType,
        TInt aEditorResourceId, 
        TInt aSettingPageResourceId );
    /*
     * Destructor
     */
    ~CTestEdwinSettingPage();
    /*
     * This fuction is wrote for testing SizeChanged() function
     */
    void SizeChanged();
    /*
     * This fuction is wrote for testing Draw() function
     */
    void DoDraw(const TRect& aRect) const;
    /*
     * This fuction is wrote for activating gc
     */
    void DoActivateGc() const;
    /*
     * This fuction is wrote for non-activating gc
     */
    void DoDeactivateGc() const;
    /*
     * This function is used to initial some variable
     */
    void DoLayoutRect();
    };
/*
 * This class inherit from the CAknIntegerSettingPage class for 
 * testing the class CAknIntegerSettingPage's protected function
 */ 
class CTestTextSettingPage:public CAknTextSettingPage
    {
public:
    /*
     * Constructor
     */
    CTestTextSettingPage( TInt aResourceID, TDes& aText, 
        TInt aTextSettingPageFlags = 0 );
    /*
     * Constructor
     */
    CTestTextSettingPage( const TDesC* aSettingTitleText, 
            TInt aSettingNumber, 
            TInt aControlType,
            TInt aEditorResourceId, 
            TInt aSettingPageResourceId,
            TDes& aText, 
            TInt aTextSettingPageFlags = 0 );
    /*
     * Destructor
     */
    ~CTestTextSettingPage();
    /*
     * This fuction is wrote for testing DynamicInitL() function
     */
    void DoDynamicInitL();
    /*
     * This fuction is wrote for testing UpdateSettingL() function
     */
    void DoUpdateSettingL();
    /*
     * This fuction is wrote for testing AcceptSettingL() function
     */
    void DoAcceptSettingL();
    /*
     * This fuction is wrote for testing RestoreOriginalSettingL() function
     */
    void DoRestoreOriginalSettingL();
    /*
     * This fuction is wrote for testing HandleControlEventL() function
     */
    void DoHandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType );
    /*
     * This fuction is wrote for testing CheckAndSetDataValidity() function
     */
    void DoCheckAndSetDataValidity();
    /*
     * This fuction is wrote for testing UpdateTextL() function
     */
    void DoUpdateTextL();
    /*
     * This fuction is wrote for testing UpdateCbaL() function
     */
    void DoUpdateCbaL();
    /*
     * This fuction is wrote for testing OkToExitL() function
     */
    void DoOkToExitL(TBool aAccept);
    /*
     * This fuction is wrote for testing OfferKeyEventL() function
     */
    void DoOfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType);
    /*
     * This fuction is wrote for testing SizeChanged() function
     */
    void DoSizeChanged();
    /*
     * This fuction is wrote for testing WriteInternalStateL() function
     */
    void DoWriteInternalStateL(RWriteStream& aWriteStream) const;
    };
/*
 * This class inherit from the CAknIntegerSettingPage class for 
 * testing the class CAknIntegerSettingPage's protected function
 */ 
class CTestIntegerSettingPage:public CAknIntegerSettingPage
    {
public:
    /*
     * Constructor
     */
    CTestIntegerSettingPage( TInt aResourceID, TInt& aValue, 
        TInt aTextSettingPageFlags = 0 );
    /*
     * Constructor
     */
    CTestIntegerSettingPage( const TDesC* aSettingTitleText, 
        TInt aSettingNumber, 
        TInt aControlType,
        TInt aEditorResourceId, 
        TInt aSettingPageResourceId,
        TInt& aValue, 
        TInt aIntegerSettingPageFlags = 0 );
    /*
     * Destructor
     */
    ~CTestIntegerSettingPage();
    /*
     * This fuction is wrote for testing DynamicInitL() function
     */
    void DoDynamicInitL();
    /*
     * This fuction is wrote for testing UpdateSettingL() function
     */
    void DoUpdateSettingL();
    /*
     * This fuction is wrote for testing RestoreOriginalSettingL() function
     */
    void DoRestoreOriginalSettingL();
    /*
     * This fuction is wrote for testing CheckAndSetDataValidity() function
     */
    void DoCheckAndSetDataValidity();
    /*
     * This fuction is wrote for testing UpdateCbaL() function
     */
    void DoUpdateCbaL();
    /*
     * This fuction is wrote for testing HandleControlEventL() function
     */
    void DoHandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType );
    /*
     * This fuction is wrote for testing SizeChanged() function
     */
    void DoSizeChanged();
    /*
     * This fuction is wrote for testing WriteInternalStateL() function
     */
    void DoWriteInternalStateL(RWriteStream& aWriteStream) const;
    };

#endif
//Endfile


