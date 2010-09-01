/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test case
*
*/


#include "bctesttransparentcamerasettingpage.h"

/**
 * Simple pass-through constructor for class
 *
 */
EXPORT_C CBCTestTransparentCameraSettingPage::CBCTestTransparentCameraSettingPage(
                        TInt aResourceID, 
                        TInt& aCurrentSelectionIndex, 
                        const MDesCArray* aItemArray )
                        : CAknTransparentCameraSettingPage(      
                            aResourceID, 
                            aCurrentSelectionIndex, 
                            aItemArray )
     {
     }

/**
 * Constructor that allows separate setting page and editor resources
 * 
 */
EXPORT_C CBCTestTransparentCameraSettingPage::CBCTestTransparentCameraSettingPage(  
                        const TDesC* aSettingTitleText, 
                        TInt aSettingNumber, 
                        TInt aControlType,
                        TInt aEditorResourceId, 
                        TInt aSettingPageResourceId,
                        TInt& aCurrentSelectionIndex, 
                        const MDesCArray* aItemArray )
                        : CAknTransparentCameraSettingPage( 
                            aSettingTitleText, 
                            aSettingNumber, 
                            aControlType,
                            aEditorResourceId, 
                            aSettingPageResourceId,
                            aCurrentSelectionIndex, 
                            aItemArray )
                              
    {
    }

/**
 * Destructor
 *
 */

EXPORT_C CBCTestTransparentCameraSettingPage::~CBCTestTransparentCameraSettingPage()
    {
    }

