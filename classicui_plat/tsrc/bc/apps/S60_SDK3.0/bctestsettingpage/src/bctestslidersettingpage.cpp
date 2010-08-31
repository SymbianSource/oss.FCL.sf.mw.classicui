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









#include "bctestslidersettingpage.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


EXPORT_C CBCTestSliderSettingPage::CBCTestSliderSettingPage( TInt aResourceId, TInt& aSliderValue ):
     CAknSliderSettingPage( aResourceId, aSliderValue )
    {
    }

EXPORT_C CBCTestSliderSettingPage::CBCTestSliderSettingPage(
                                const TDesC* aSettingText,
                                TInt aSettingNumber,
                                TInt aControlType,
                                TInt aEditorResourceId,
                                TInt aSettingPageResourceId,
                                TInt& aSliderValue)
                                :   CAknSliderSettingPage(
                                    aSettingText,
                                    aSettingNumber,
                                    aControlType,
                                    aEditorResourceId,
                                    aSettingPageResourceId,
                                    aSliderValue )
    {
    }

/**
 * Destructor
 *
 */
EXPORT_C CBCTestSliderSettingPage::~CBCTestSliderSettingPage()
    {
    }


EXPORT_C void CBCTestSliderSettingPage::UpdateSettingL()
    {
    CAknSliderSettingPage::UpdateSettingL();
    }

EXPORT_C void CBCTestSliderSettingPage::AcceptSettingL()
    {
    CAknSliderSettingPage::AcceptSettingL();
    }

EXPORT_C void CBCTestSliderSettingPage::RestoreOriginalSettingL()
    {
    CAknSliderSettingPage::RestoreOriginalSettingL();
    }


EXPORT_C void CBCTestSliderSettingPage::SizeChanged()
    {
    CAknSliderSettingPage::SizeChanged();
    }

EXPORT_C void CBCTestSliderSettingPage::Draw(const TRect &aRect) const
    {
    CAknSliderSettingPage::Draw( aRect );
    }

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 */
#ifndef _DEBUG
EXPORT_C void CBCTestSliderSettingPage::WriteInternalStateL(RWriteStream& /*aWriteStream*/) const
    {}
#else
EXPORT_C void CBCTestSliderSettingPage::WriteInternalStateL(RWriteStream& aWriteStream) const
    {
    CAknSliderSettingPage::WriteInternalStateL(aWriteStream);
    }
#endif



// End of File
