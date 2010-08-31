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
* Description:  Test aknvolumesettingpage.h
*
*/

#ifndef C_TESTAKNVOLUMESETTINGPAGEPROTECTED_H
#define C_TESTAKNVOLUMESETTINGPAGEPROTECTED_H
//Include files
#include <aknvolumesettingpage.h>

/*
 * This class inherit from CAknVolumeSettingPage for testing 
 * CAknVolumeSettingPage class's protect function
 */
class CTestVolumeSettingPage:public CAknVolumeSettingPage
    {
public:
    /*
     * Constructor
     */
    CTestVolumeSettingPage( TInt aResourceID, TInt& aVolume );
    
    /*
     * Constructor
     */
    CTestVolumeSettingPage( const TDesC* aSettingTitleText, 
        TInt aSettingNumber, 
        TInt aControlType,
        TInt aEditorResourceId, 
        TInt aSettingPageResourceId,
        TInt& aVolume );
    
    /*
     * Destructor
     */
    ~CTestVolumeSettingPage();

    /*
     * This fuction is wrote for testing DoConstructL() function
     */
    void DoConstructL();

    /*
     * This fuction is wrote for testing DoVolumeControl() function
     */
    CAknVolumeControl* DoVolumeControl();

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
     * This fuction is wrote for activating gc
     */
    void DoActivateGc() const;
    
    /*
     * This fuction is wrote for non-activating gc
     */
    void DoDeactivateGc() const;
    };

#endif /*C_TESTAKNVOLUMESETTINGPAGEPROTECTED_H*/

//End file


