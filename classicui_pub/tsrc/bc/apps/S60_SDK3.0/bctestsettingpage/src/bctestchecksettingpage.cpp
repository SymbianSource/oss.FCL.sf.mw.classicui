/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Declares main application class.
*
*/









#include "bctestchecksettingpage.h"
#include "bctestsettingpage.hrh"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


/**
 * Destructor
 *
 */
EXPORT_C CBCTestCheckSettingPage::~CBCTestCheckSettingPage()
    {

    }


EXPORT_C CBCTestCheckSettingPage::CBCTestCheckSettingPage( TInt aResourceId, CSelectionItemList* aItemArray):
     CAknCheckBoxSettingPage( aResourceId, aItemArray )
    {
    }


EXPORT_C CBCTestCheckSettingPage::CBCTestCheckSettingPage(
            const TDesC* aSettingText,
            TInt aSettingNumber,
            TInt aControlType,
            TInt aEditorResourceId,
            TInt aSettingPageResourceId,
            CSelectionItemList* aItemArray )
            :   CAknCheckBoxSettingPage(
                aSettingText,
                aSettingNumber,
                aControlType,
                aEditorResourceId,
                aSettingPageResourceId,
                aItemArray )
    {
    }

EXPORT_C void CBCTestCheckSettingPage::BCUpdateSettingL()
    {
    UpdateSettingL();
    }

EXPORT_C void CBCTestCheckSettingPage::BCDynamicInitL()
    {
    DynamicInitL();
    }

/**
 * Processes events from the softkeys. (Or tranlated from key events)
 *
 *
 * @param   aCommandId  Event Id from the soft-key
 */
EXPORT_C void CBCTestCheckSettingPage::ProcessCommandL(TInt aCommandId)
    {
    if ( aCommandId != EBCTestMenuItem )
        {
        CAknCheckBoxSettingPage::ProcessCommandL( aCommandId );    
        }
    }

EXPORT_C void CBCTestCheckSettingPage::BCSelectCurrentItemL()
    {
    SelectCurrentItemL();
    }
    
/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 */
#ifndef _DEBUG
EXPORT_C void CBCTestCheckSettingPage::BCWriteInternalStateL(RWriteStream& /*aWriteStream*/) const
    {}
#else
EXPORT_C void CBCTestCheckSettingPage::BCWriteInternalStateL(RWriteStream& aWriteStream) const
    {
    WriteInternalStateL(aWriteStream);
    }
#endif

// End of File
