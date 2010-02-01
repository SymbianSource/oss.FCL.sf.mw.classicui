/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Implements test bc for popup field text testcase.
*
*/










#ifndef C_CBCTESTPOPUPSETTINGPAGE_H
#define C_CBCTESTPOPUPSETTINGPAGE_H

#include <aknpopupsettingpage.h>

class CBCTestPopupsContainer;

/**
* test case for various popup classes
*/
class CBCTestPopupSettingPage: public CAknPopupSettingPage
    {
public: // constructor and destructor

    friend class CBCTestPopupSettingPageCase;
    
    /**
    * C++ default constructor
    */
    CBCTestPopupSettingPage(
        const TInt aResourceId,
        CAknQueryValueText& aQueryValue );
    	
    /**
    * C++ default constructor
    */
    CBCTestPopupSettingPage(
		const TDesC* aSettingTitleText, 
		TInt aSettingNumber, 
		TInt aControlType,
		TInt aEditorResourceId, 
        TInt aSettingPageResourceId,
		MAknQueryValue& aQueryValue);
    	
    ~CBCTestPopupSettingPage();

    };

#endif    //C_CBCTESTPOPUPSETTINGPAGE_H

