/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test AknStaticNoteDialog.h 
*
*/


//  INCLUDES
#include "testsdknotesstaticnotedialog.h"

// -----------------------------------------------------------------------------
// CTestSDKNotesControl::CTestSDKNotesStaticNoteDialog
// -----------------------------------------------------------------------------
CTestSDKNotesStaticNoteDialog::CTestSDKNotesStaticNoteDialog():CAknStaticNoteDialog()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesControl::~CTestSDKNotesStaticNoteDialog
// -----------------------------------------------------------------------------
CTestSDKNotesStaticNoteDialog::~CTestSDKNotesStaticNoteDialog()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesControl::PostLayoutDynInitL
// -----------------------------------------------------------------------------
void CTestSDKNotesStaticNoteDialog::PostLayoutDynInitL()
    {
    CAknStaticNoteDialog::PostLayoutDynInitL();
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesControl::Indicator
// -----------------------------------------------------------------------------
CAknStaticNoteStackIndicator* CTestSDKNotesStaticNoteDialog::Indicator()
    {
    return iStackIndicator;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesControl::OfferKeyEventL
// -----------------------------------------------------------------------------
TKeyResponse CTestSDKNotesStaticNoteDialog::OfferKeyEventL( const TKeyEvent& aKeyEvent,TEventCode aType )
    {
    return CAknStaticNoteDialog::OfferKeyEventL( aKeyEvent, aType );
    }
