/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  declaration of testting needed extend classes.
*
*/


#ifndef C_BCTESTDOMMIX50EXTENDCLASSES_H
#define C_BCTESTDOMMIX50EXTENDCLASSES_H

#include <aknpopupform.h>
#include <aknextendedinputcapabilities.h>
#include <akntransparentcamerasettingpage.h>


/**
 * following class for HandlePointerEventL
 */
class CBCTestCAknPopupForm: public CAknPopupForm
    {
    friend class CBCTestDomMix50Case;

public:
    /**
     * Symbian static 2nd constructor
     */
    static CBCTestCAknPopupForm* NewL();
    };


/**
 * test for CAknTransparentCameraSettingPage::ProcessCommandL ( protected )
 */
class CBCTestCAknTransparentCameraSettingPage:
                                 public CAknTransparentCameraSettingPage
    {
    friend class CBCTestDomMix50Case;

public:
    CBCTestCAknTransparentCameraSettingPage( TInt aResourceID,
                                             TInt& aCurrentSelectionIndex,
                                             const MDesCArray* aItemArray );

    CBCTestCAknTransparentCameraSettingPage(
                                         const TDesC* aSettingTitleText,
                                         TInt aSettingNumber,
                                         TInt aControlType,
                                         TInt aEditorResourceId,
                                         TInt aSettingPageResourceId,
                                         TInt& aCurrentSelectionIndex,
                                         const MDesCArray* aItemArray );
    };

/**
 * following class for RegisterObserver
 */
class TBCTestAknEventObserver: public
    CAknExtendedInputCapabilities::MAknEventObserver
    {
    void HandleInputCapabilitiesEventL( TInt /*aEvent*/,
                                        TAny* /*aParams*/ );
    };

#endif //C_BCTESTDOMMIX50EXTENDCLASSES_H
