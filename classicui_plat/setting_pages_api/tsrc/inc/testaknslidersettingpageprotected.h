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
* Description:  Test aknslidersetting.h
*
*/

#ifndef C_TESTAKNSLIDERSETTINGPAGEPROTECTED_H
#define C_TESTAKNSLIDERSETTINGPAGEPROTECTED_H
//INCLUDE
#include <aknslidersettingpage.h>

/*
 * This class inherit from the CAknSliderSettingPage class for 
 * testing the class CAknSliderSettingPage's protected function
 */ 
class CTestSliderSettingPage:public CAknSliderSettingPage
    {
public:
    /*
     * Constructor
     */
    CTestSliderSettingPage( TInt aResourceID, TInt& aSliderValue );
    /*
     * Constructor
     */
    
    CTestSliderSettingPage( const TDesC* aSettingTitleText, 
        TInt aSettingNumber, 
        TInt aControlType,
        TInt aEditorResourceId, 
        TInt aSettingPageResourceId,
        TInt& aSliderValue );
    /*
     * Destructor
     */
    ~CTestSliderSettingPage();
    
    /*
     * This fuction is wrote for testing DoSizeChanged() function
     */
    void DoSizeChanged();
    
    /*
     * This fuction is wrote for testing DoDraw() function
     */
    void DoDraw(const TRect &aRect) const;

    /*
     * This fuction is wrote for testing DoWriteInternalStateL() function
     */
    void DoWriteInternalStateL(RWriteStream& aWriteStream) const;

    /*
     * This fuction is wrote for testing DoUpdateSettingL() function
     */
    void DoUpdateSettingL();

    /*
     * This fuction is wrote for testing DoAcceptSettingL() function
     */
    void DoAcceptSettingL();

    /*
     * This fuction is wrote for testing DoRestoreOriginalSettingL() function
     */
    void DoRestoreOriginalSettingL();

    /*
     * This fuction is wrote for testing DoActivateGc() function
     */
    void DoActivateGc() const;

    /*
     * This fuction is wrote for testing DoDeactivateGc() function
     */
    void DoDeactivateGc() const;
    };

#endif /*C_TESTAKNSLIDERSETTINGPAGEPROTECTED_H*/

//End file


