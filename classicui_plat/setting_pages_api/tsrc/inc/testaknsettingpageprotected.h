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
* Description:  Test aknsettingpage.h
*
*/

#ifndef C_TESTAKNSETTINGPAGEPROTECTED_H
#define C_TESTAKNSETTINGPAGEPROTECTED_H
//INCLUDE
#include <aknsettingpage.h>
/*
 * This class inherit from the CAknSettingPage class for 
 * testing the class CAknSettingPage's protected function
 */ 
class CTestSettingPage:public CAknSettingPage
    {
public:
    /*
     * Constructor
     */
    CTestSettingPage( TInt aSettingPageResourceId );
    /*
     * Constructor
     */
    CTestSettingPage( const TDesC* aSettingTitleText, 
        TInt aSettingNumber, 
        TInt aControlType,
        TInt aEditorResourceId, 
        TInt aSettingPageResourceId = 0 );
    /*
     * Destructor
     */
    ~CTestSettingPage();
    /*
     * This fuction is wrote for testing SizeChanged() function
     */
    void TestSizeChanged();
    /*
     * This fuction is wrote for testing FocusChanged() function
     */
    void TestFocusChanged(TDrawNow aDrawNow);
    /*
     * This fuction is wrote for testing ProcessCommandL() function
     */
    void TestProcessCommandL(TInt aCommandId);
    /*
     * This fuction is wrote for testing HandleControlEventL() function
     */
    void TestHandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
    /*
     * This fuction is wrote for testing OkToExitL() function
     */
    TBool TestOkToExitL(TBool aAccept);
    /*
     * This fuction is wrote for testing DynamicInitL() function
     */
    void TestDynamicInitL();
    /*
     * This fuction is wrote for testing UpdateSettingL() function
     */
    void TestUpdateSettingL();
    /*
     * This fuction is wrote for testing AcceptSettingL() function
     */
    void TestAcceptSettingL();
    /*
     * This fuction is wrote for testing RestoreOriginalSettingL() function
     */
    void TestRestoreOriginalSettingL();
    /*
     * This fuction is wrote for testing DisplayMenuL() function
     */
    void TestDisplayMenuL();
    /*
     * This fuction is wrote for testing HideMenu() function
     */
    void TestHideMenu();
    /*
     * This fuction is wrote for testing SetFocusToEditor() function
     */
    void TestSetFocusToEditor();
    /*
     * This fuction is wrote for testing SelectCurrentItemL() function
     */
    void TestSelectCurrentItemL();
    /*
     * This fuction is wrote for testing BaseConstructL() function
     */
    void TestBaseConstructL();
    /*
     * This fuction is wrote for testing DismissL() function
     */
    void TestDismissL( TBool aAccept );
    /*
     * This fuction is wrote for testing MenuShowing() function
     */
    TBool TestMenuShowing() const;
    /*
     * This fuction is wrote for testing ConstructFromResourceL() function
     */
    void TestConstructFromResourceL( TInt aResourceId);
    /*
     * This fuction is wrote for testing ConstructFromResourceL() function
     */
    void TestConstructFromResourceL(TResourceReader& aRes);
    /*
     * This fuction is wrote for testing AttemptExitL() function
     */
    void TestAttemptExitL(TBool aAccept);
    /*
     * This fuction is wrote for testing Waiting() function
     */
    TBool TestWaiting();
    /*
     * This fuction is wrote for testing Cba() function
     */
    CEikButtonGroupContainer* TestCba() const ;
    /*
     * This fuction is wrote for testing DefaultCbaResourceId() function
     */
    TInt TestDefaultCbaResourceId() const;
    /*
     * This fuction is wrote for testing OfferKeyEventL() function
     */
    TKeyResponse TestOfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType);
    /*
     * This fuction is wrote for testing StandardSettingPageLayout() function
     */
    void TestStandardSettingPageLayout();
    /*
     * This fuction is wrote for testing IsBaseConstructed() function
     */
    TBool TestIsBaseConstructed();
    /*
     * This fuction is wrote for testing SettingPageResourceId() function
     */
    TInt TestSettingPageResourceId();
    /*
     * This fuction is wrote for testing BaseDraw() function
     */
    void TestBaseDraw(const TRect& aRect) const;
    /*
     * This fuction is wrote for testing ResetFlags() function
     */
    void TestResetFlags();
    /*
     * This fuction is wrote for testing PostDisplayCheckL() function
     */
    TBool TestPostDisplayCheckL();
    /*
     * This fuction is wrote for testing UpdateCbaL() function
     */
    void TestUpdateCbaL();
    /*
     * This fuction is wrote for testing DataValidity() function
     */
    TBool TestDataValidity() const;
    /*
     * This fuction is wrote for testing SetDataValidity() function
     */
    void TestSetDataValidity(TBool aValid);
    /*
     * This fuction is wrote for testing CheckAndSetDataValidity() function
     */
    void TestCheckAndSetDataValidity();
    /*
     * This fuction is wrote for testing SetEmphasis() function
     */
    void TestSetEmphasis(CCoeControl* aMenuControl,TBool aEmphasis);
    /*
     * This fuction is wrote for testing DynInitMenuPaneL() function
     */
    void TestDynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane ); 
    /*
     * This fuction is wrote for testing HandleResourceChange() function
     */
    void TestHandleResourceChange(TInt aType);
    /*
     * This fuction is wrote for testing CountComponentControls() function
     */
    TInt TestCountComponentControls() const;
    /*
     * This fuction is wrote for testing ComponentControl() function
     */
    CCoeControl* TestComponentControl(TInt anIndex) const;
    /*
     * This fuction is wrote for testing HandlePointerEventL() function
     */
    void TestHandlePointerEventL(const TPointerEvent& aPointerEvent);
    /*
     * This fuction is wrote for testing InputCapabilities() function
     */
    TCoeInputCapabilities TestInputCapabilities() const;
    /*
     * This fuction is wrote for testing InvalidDataCbaResourceId(() function
     */
    TInt TestInvalidDataCbaResourceId() const; 
    /*
     * This fuction is wrote for testing MopSupplyObject() function
     */
    TTypeUid::Ptr TestMopSupplyObject(TTypeUid aId);
    /*
     * This fuction is wrote for testing WriteInternalState() function
     */
    void TestWriteInternalStateL(RWriteStream& aWriteStream) const;
    /*
     * This fuction is wrote for testing TextLabel() function
     */
    CEikLabel* TestTextLabel() const;
    /*
     * This fuction is wrote for testing ShadowText() function
     */
    CEikLabel* TestShadowText() const;
    /*
     * This fuction is wrote for activationing gc
     */
    void DoActivateGc() const;
    /*
     * This fuction is wrote for deactivationing gc
     */
    void DoDeactivateGc() const;
    /*
     * This fuction is wrote for testing GetWindow() function
     */
    RWindow& GetWindow() const;
    /*
     * This function is used to set iUpdateMode's value 
     */
    void SetiUpdateMode( TInt aUpdateMode );
    };

#endif /*C_TESTAKNSETTINGPAGEPROTECTED_H*/

//End file


