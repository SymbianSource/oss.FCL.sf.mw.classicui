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
* Description:         test case
*
*/









#include "bctestbasesettingpage.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/**
 * Constructor
 *
 * @param	aResourceId Setting Page resource ID
 */
EXPORT_C CBCTestBaseSettingPage::CBCTestBaseSettingPage( TInt aResourceId )
								:	CAknSettingPage( aResourceId )
	{
	}


EXPORT_C CBCTestBaseSettingPage::CBCTestBaseSettingPage(	
								const TDesC* aSettingText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId )
								:	CAknSettingPage( aSettingText,
								    aSettingNumber,
									aControlType,
									aEditorResourceId,
									aSettingPageResourceId )
	{
	}

/**
 * Destructor
 *
 */
EXPORT_C CBCTestBaseSettingPage::~CBCTestBaseSettingPage()
	{
	}
EXPORT_C void CBCTestBaseSettingPage::SetFocusToEditor()
    {
	//You can do some work here, or the base class's function will get panic.
    }

EXPORT_C TBool CBCTestBaseSettingPage::PostDisplayCheckL()
	{
		DisplayMenuL();
		return CAknSettingPage::PostDisplayCheckL();
	}

// End of File
