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









#include "bctestvolumesettingpage.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



EXPORT_C CBCTestVolumeSettingPage::CBCTestVolumeSettingPage( TInt aResourceId, TInt& aVolume ):
     CAknVolumeSettingPage( aResourceId, aVolume)
    {
    }

EXPORT_C CBCTestVolumeSettingPage::CBCTestVolumeSettingPage(
                                const TDesC* aSettingText,
                                TInt aSettingNumber,
                                TInt aControlType,
                                TInt aEditorResourceId,
                                TInt aSettingPageResourceId,
                                TInt& aVolume)
                                :   CAknVolumeSettingPage(
                                    aSettingText,
                                    aSettingNumber,
                                    aControlType,
                                    aEditorResourceId,
                                    aSettingPageResourceId,
                                    aVolume )
    {
    }

/**
 * Destructor
 *
 */
EXPORT_C CBCTestVolumeSettingPage::~CBCTestVolumeSettingPage()
    {
    }

EXPORT_C void CBCTestVolumeSettingPage::ConstructL()
    {
    CAknVolumeSettingPage::ConstructL();
    }

EXPORT_C void CBCTestVolumeSettingPage::UpdateSettingL()
    {
    CAknVolumeSettingPage::UpdateSettingL();
    }

EXPORT_C void CBCTestVolumeSettingPage::AcceptSettingL()
    {
    CAknVolumeSettingPage::AcceptSettingL();
    }

EXPORT_C void CBCTestVolumeSettingPage::RestoreOriginalSettingL()
    {
    CAknVolumeSettingPage::RestoreOriginalSettingL();
    }


EXPORT_C CAknVolumeControl* CBCTestVolumeSettingPage::VolumeControl()
    {
    return CAknVolumeSettingPage::VolumeControl();
    }

EXPORT_C void CBCTestVolumeSettingPage::SizeChanged()
    {
    CAknVolumeSettingPage::SizeChanged();
    }

EXPORT_C void CBCTestVolumeSettingPage::Draw(const TRect &aRect) const
    {
    CAknVolumeSettingPage::Draw( aRect );
    }

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 */
#ifndef _DEBUG
EXPORT_C void CBCTestVolumeSettingPage::WriteInternalStateL(RWriteStream& /*aWriteStream*/) const
    {}
#else
EXPORT_C void CBCTestVolumeSettingPage::WriteInternalStateL(RWriteStream& aWriteStream) const
    {
    CAknVolumeSettingPage::WriteInternalStateL(aWriteStream);
    }
#endif


// End of File
