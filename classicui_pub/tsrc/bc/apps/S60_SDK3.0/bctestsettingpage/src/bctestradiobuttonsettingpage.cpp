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
* Description:         container
*
*/









#include "bctestradiobuttonsettingpage.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


EXPORT_C CBCTestRadioButtonSettingPage::CBCTestRadioButtonSettingPage( TInt aResourceId,
    TInt& aCurrentSelectionItem, const MDesCArray* aItemArray):
    CAknRadioButtonSettingPage( aResourceId, aCurrentSelectionItem, aItemArray )
    {
    }


EXPORT_C CBCTestRadioButtonSettingPage::CBCTestRadioButtonSettingPage(
            const TDesC* aSettingText,
            TInt aSettingNumber,
            TInt aControlType,
            TInt aEditorResourceId,
            TInt aSettingPageResourceId,
            TInt& aCurrentSelectionIndex,
            const MDesCArray* aItemArray )
            :   CAknRadioButtonSettingPage(
                aSettingText,
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
EXPORT_C CBCTestRadioButtonSettingPage::~CBCTestRadioButtonSettingPage()
    {
    }


EXPORT_C void CBCTestRadioButtonSettingPage::UpdateSettingL()
    {
    CAknRadioButtonSettingPage::UpdateSettingL();
    }


EXPORT_C void CBCTestRadioButtonSettingPage::DynamicInitL()
    {
    CAknRadioButtonSettingPage::DynamicInitL();
    }


EXPORT_C void CBCTestRadioButtonSettingPage::SelectCurrentItemL()
    {
    CAknRadioButtonSettingPage::SelectCurrentItemL();
    }

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 */
#ifndef _DEBUG
EXPORT_C void CBCTestRadioButtonSettingPage::WriteInternalStateL(RWriteStream& /*aWriteStream*/) const
    {}
#else
EXPORT_C void CBCTestRadioButtonSettingPage::WriteInternalStateL(RWriteStream& aWriteStream) const
    {
    CAknRadioButtonSettingPage::WriteInternalStateL(aWriteStream);
    }
#endif

// End of File
