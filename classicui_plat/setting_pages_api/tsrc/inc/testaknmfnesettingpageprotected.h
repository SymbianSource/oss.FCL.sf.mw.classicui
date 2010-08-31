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
* Description:  Test aknmfnesettingpage.h
*
*/

#ifndef C_TESTAKNMFNESETTINGPAGEPROTECTED_H
#define C_TESTAKNMFNESETTINGPAGEPROTECTED_H
//INCLUDE 
#include <aknmfnesettingpage.h>

/*
 * This class inherit from CAknMfneSettingPage class for 
 * testing the CAknMfneSettingPage's
 * protected function
 */
class CTestMfneSettingPage : public CAknMfneSettingPage
    {
public:
    /*
     * Constructor
     */
    CTestMfneSettingPage( TInt aResourceId );
    /*
     * Constructor
     */
    CTestMfneSettingPage( const TDesC* aSettingTitleText, 
        TInt aSettingNumber, 
        TInt aControlType,
        TInt aEditorResourceId, 
        TInt aSettingPageResourceId );
    /*
     * Destructor
     */
    ~CTestMfneSettingPage();
    /*
     * This fuction is wrote for testing BaseConstructL() function
     */
    void DoBaseConstructL();
    /*
     * This fuction is wrote for testing SizeChanged() function
     */
    void DoSizeChanged();
    /*
         * This fuction is wrote for testing BaseConstructL() function
         */
    void DoDraw(const TRect& aRect) const;
    /*
         * This fuction is wrote for testing BaseConstructL() function
         */
    CEikMfne* DoMfne() const;
    /*
         * This fuction is wrote for testing BaseConstructL() function
         */
    void DoCheckAndSetDataValidity();
    /*
         * This fuction is wrote for testing BaseConstructL() function
         */
    void DoHandleControlEventL(CCoeControl* aControl,
        TCoeEvent aEventType);
    /*
         * This fuction is wrote for testing BaseConstructL() function
         */
    void DoConstructL();
    /*
         * This fuction is wrote for testing BaseConstructL() function
         */
    TInt DoCountComponentControls() const;
    /*
         * This fuction is wrote for testing BaseConstructL() function
         */
    CCoeControl* DoComponentControl(TInt anIndex) const;
    /*
         * This fuction is wrote for testing BaseConstructL() function
         */
    void DoActivateGc();
    /*
         * This fuction is wrote for testing BaseConstructL() function
         */
    void DoDeactivateGc();
    };

/*
 * This class inherit from CAknDateSettingPage class for 
 * testing the CAknDateSettingPage's protected function
 */
class CTestDateSettingPage:public CAknDateSettingPage
    {
public:
    /*
     * Constructor
     */
    CTestDateSettingPage( TInt aResourceID, 
        TTime& aDateValue );
    /*
     * Constructor
     */
    CTestDateSettingPage( const TDesC* aSettingTitleText, 
        TInt aSettingNumber, 
        TInt aControlType,
        TInt aEditorResourceId, 
        TInt aSettingPageResourceId,    
        TTime& aDateValue );
    /*
     * Destructor
     */
    ~CTestDateSettingPage();
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
     * This fuction is wrote for testing WriteInternalStateL() function
     */
    void DoWriteInternalStateL(RWriteStream& aWriteStream) const;
    };

/*
 * This class inherit from CAknTimeSettingPage class for
 * testing the CAknTimeSettingPage class's protected function
 */
class CTestTimeSettingPage:public CAknTimeSettingPage
    {
public:
    /*
     * Constructor
     */
    CTestTimeSettingPage( TInt aResourceID, TTime& aTimeValue );
    /*
     * Constructor
     */
    CTestTimeSettingPage( const TDesC* aSettingTitleText, 
        TInt aSettingNumber, 
        TInt aControlType,
        TInt aEditorResourceId, 
        TInt aSettingPageResourceId,    
        TTime& aTimeValue );
    /*
     * Destructor
     */
    ~CTestTimeSettingPage();
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
     * This fuction is wrote for testing WriteInternalStateL() function
     */
    void DoWriteInternalStateL(RWriteStream& aWriteStream) const;
    };

/*
 * This class inherit from CAknDurationSettingPage for
 * testing the CAknDurationSettingPage's protected function
 */
class CTestDurationSettingPage:public CAknDurationSettingPage
    {
public:
    /*
     * Constructor
     */
    CTestDurationSettingPage( TInt aResourceID, 
        TTimeIntervalSeconds&   aDurationValue );
    /*
     * Constructor
     */
    CTestDurationSettingPage( const TDesC* aSettingTitleText, 
        TInt aSettingNumber, 
        TInt aControlType,
        TInt aEditorResourceId, 
        TInt aSettingPageResourceId,    
        TTimeIntervalSeconds&   aDurationValue );
    /*
     * Destructor
     */
    ~CTestDurationSettingPage();
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
     * This fuction is wrote for testing WriteInternalStateL() function
     */
    void DoWriteInternalStateL(RWriteStream& aWriteStream) const;
    };

/*
 * This class inherit from CaknTimeOffsetSettingPage for testing 
 * the CAknTimeOffsetSettingPage's protected function
 */
class CTestTimeOffsetSettingPage:public CAknTimeOffsetSettingPage
    {
public:
    /*
     * Constructor
     */
    CTestTimeOffsetSettingPage( TInt aResourceID, 
        TTimeIntervalSeconds& aTimeOffsetValue );
    /*
     * Constructor
     */
    CTestTimeOffsetSettingPage( const TDesC* aSettingTitleText, 
        TInt aSettingNumber, 
        TInt aControlType,
        TInt aEditorResourceId, 
        TInt aSettingPageResourceId,    
        TTimeIntervalSeconds&   aTimeOffsetValue );
    /*
     * Destructor
     */
    ~CTestTimeOffsetSettingPage();
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
     * This fuction is wrote for testing WriteInternalStateL() function
     */
    void DoWriteInternalStateL(RWriteStream& aWriteStream) const;
    
    };

class CTestIpFieldSettingPage:public CAknIpFieldSettingPage
    {
public:
    /*
     * Constructor
     */
    CTestIpFieldSettingPage( TInt aResourceID, 
        TInetAddr& aIpAddress );
    /*
     * Constructor
     */
    CTestIpFieldSettingPage( const TDesC* aSettingTitleText, 
        TInt aSettingNumber, 
        TInt aControlType,
        TInt aEditorResourceId, 
        TInt aSettingPageResourceId,    
        TInetAddr&  aIpAddress );
    /*
     * Destructor
     */
    ~CTestIpFieldSettingPage();
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
     * This fuction is wrote for testing WriteinternalStateL() function
     */
    void DoWriteInternalStateL(RWriteStream& aWriteStream) const;
    
    };

#endif/*C_TESTAKNMFNESETTINGPAGEPROTECTED_H*/

//End file


