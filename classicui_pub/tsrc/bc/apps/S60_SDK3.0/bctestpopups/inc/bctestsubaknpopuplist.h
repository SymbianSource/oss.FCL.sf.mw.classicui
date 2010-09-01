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
* Description:         Invoke popup list's protected APIs.
*
*/









#ifndef C_CBCTESTSUBAKNPOPUPLIST_H
#define C_CBCTESTSUBAKNPOPUPLIST_H

#include <aknpopup.h>

/**
 * Invoke popup list's protected APIs
 */
    
class CBCTestSubAknPopupList: public CAknPopupList
	{
	
	friend class CBCTestPopupSettingPageCase;
	
	}; 

#endif // C_CBCTESTSUBAKNPOPUPLIST_H
