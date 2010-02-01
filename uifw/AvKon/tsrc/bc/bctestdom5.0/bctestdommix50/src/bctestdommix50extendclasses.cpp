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
* Description:  test case
*
*/


#include "bctestdommix50extendclasses.h"
#include <bctestdommix50.rsg>

// ---------------------------------------------------------------------------
// CBCTestCAknPopupForm::NewL()
//
// ---------------------------------------------------------------------------
//
CBCTestCAknPopupForm* CBCTestCAknPopupForm::NewL()
    {
    TInt  ttimeout = 3;
    TPopupFormType ttype = EAknQuery;
    CAknPopupForm* self = CAknPopupForm::NewL();
    self->SetPopupFormType( ttype );
    self->PrepareLC( R_BCTESTPOPUPS_ATTRIB_SET_DIALOG );
    self->SetTimeout( ttimeout );
    self->SetTone( ENoTone );
    CBCTestCAknPopupForm* rSelf =
                     static_cast< CBCTestCAknPopupForm* > ( self );
    CleanupStack::Pop( self );
    return rSelf;
    }


// ---------------------------------------------------------------------------
// CBCTestCAknTransparentCameraSettingPage constructor
//
// ---------------------------------------------------------------------------
//
CBCTestCAknTransparentCameraSettingPage::CBCTestCAknTransparentCameraSettingPage(
                                             TInt aResourceID,
                                             TInt& aCurrentSelectionIndex,
                                             const MDesCArray* aItemArray )
    : CAknTransparentCameraSettingPage( aResourceID,
                                        aCurrentSelectionIndex,
                                        aItemArray )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestCAknTransparentCameraSettingPage constructor
//
// ---------------------------------------------------------------------------
//
CBCTestCAknTransparentCameraSettingPage::CBCTestCAknTransparentCameraSettingPage(
                                     const TDesC* aSettingTitleText,
                                     TInt aSettingNumber,
                                     TInt aControlType,
                                     TInt aEditorResourceId,
                                     TInt aSettingPageResourceId,
                                     TInt& aCurrentSelectionIndex,
                                     const MDesCArray* aItemArray )
    : CAknTransparentCameraSettingPage( aSettingTitleText, 
                                        aSettingNumber, 
                                        aControlType,
                                        aEditorResourceId, 
                                        aSettingPageResourceId,
                                        aCurrentSelectionIndex, 
                                        aItemArray )
    {
    }


// ---------------------------------------------------------------------------
// TBCTestAknEventObserver::HandleInputCapabilitiesEventL
//
// ---------------------------------------------------------------------------
//
void TBCTestAknEventObserver::HandleInputCapabilitiesEventL( TInt /*aEvent*/,
    TAny* /*aParams*/ )
    {
    }
