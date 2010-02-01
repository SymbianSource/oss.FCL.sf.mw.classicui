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
* Description:  test protected for CAknCheckBoxSettingPage
*
*/

#ifndef C_TESTSDKLISTSLISTBOXSETTINGPAGEEXT_H
#define C_TESTSDKLISTSLISTBOXSETTINGPAGEEXT_H

#include <aknlistboxsettingpage.h>
#include <akncheckboxsettingpage.h>

#include "testsdklists.h"
/**
 * class for testing protected API of CAknListSettingPage
 */    
class CAknListBoxSettingPageExt: public CAknCheckBoxSettingPage
    {
    friend class CTestSDKLists;
    
public:
    /**
     * C++ default constructor.
     */
    CAknListBoxSettingPageExt(TInt aResourceID, 
        CSelectionItemList* aItemArray );
    
    };

#endif /*C_TESTSDKLISTSLISTBOXSETTINGPAGEEXT_H*/
