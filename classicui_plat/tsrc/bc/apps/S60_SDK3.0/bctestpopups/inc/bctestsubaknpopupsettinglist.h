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
* Description:         Invoke popup setting list's protected APIs.
*
*/









#ifndef C_CBCTESTSUBAKNPOPUPSETTINGLIST_H
#define C_CBCTESTSUBAKNPOPUPSETTINGLIST_H

#include <aknpopup.h>

/**
 * Invoke popup setting list's protected APIs
 */    
	
class CBCTestSubAknPopupSettingList: public CAknPopupSettingList
    {
    friend class CBCTestPopupSettingPageCase;
    void Init()
    	{
    	CreateViewL();
    	}
 
    };

#endif // C_CBCTESTSUBAKNPOPUPSETTINGLIST_H