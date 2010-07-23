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
* Description:  Test AknNoteDialog.h 
*
*/


//  INCLUDES
#include "testsdknotesnotedialog.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKNotesControl::CTestSDKNotesNoteDialog
// -----------------------------------------------------------------------------
CTestSDKNotesNoteDialog::CTestSDKNotesNoteDialog():CAknNoteDialog(),
    iTimeoutInMicroseconds( CAknNoteDialog::iTimeoutInMicroseconds ),
    iTone( CAknNoteDialog::iTone )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesControl::~CTestSDKNotesNoteDialog
// -----------------------------------------------------------------------------
CTestSDKNotesNoteDialog::~CTestSDKNotesNoteDialog()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesControl::SetSizeAndPosition
// -----------------------------------------------------------------------------
void CTestSDKNotesNoteDialog::SetSizeAndPosition( const TSize& aSize )
    {
    CAknNoteDialog::SetSizeAndPosition( aSize );
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesControl::PreLayoutDynInitL
// -----------------------------------------------------------------------------
void CTestSDKNotesNoteDialog::PreLayoutDynInitL()
    {
    CAknNoteDialog::PreLayoutDynInitL();
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesControl::PostLayoutDynInitL
// -----------------------------------------------------------------------------
void CTestSDKNotesNoteDialog::PostLayoutDynInitL()
    {
    CAknNoteDialog::PostLayoutDynInitL();
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesControl::PlayTone
// -----------------------------------------------------------------------------
void CTestSDKNotesNoteDialog::PlayTone()
    {
    CAknNoteDialog::PlayTone();
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesControl::ReportUserActivity
// -----------------------------------------------------------------------------
void CTestSDKNotesNoteDialog::ReportUserActivity() const
    {
    CAknNoteDialog::ReportUserActivity();
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesControl::StaticDeleteL
// -----------------------------------------------------------------------------
TInt CTestSDKNotesNoteDialog::StaticDeleteL( TAny* aThis )
    {
    return CAknNoteDialog::StaticDeleteL( aThis );
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesControl::ControlAttributes
// -----------------------------------------------------------------------------
CAknNoteAttributes* CTestSDKNotesNoteDialog::ControlAttributes()
    {
    return CAknNoteDialog::ControlAttributes();
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesControl::TransferControlAttributes
// -----------------------------------------------------------------------------
void CTestSDKNotesNoteDialog::TransferControlAttributes()
    {
    CAknNoteDialog::TransferControlAttributes();
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesControl::SoundSystem
// -----------------------------------------------------------------------------
CAknKeySoundSystem* CTestSDKNotesNoteDialog::SoundSystem() const
    {
    return CAknNoteDialog::SoundSystem();
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesControl::NoteControl
// -----------------------------------------------------------------------------
CAknNoteControl* CTestSDKNotesNoteDialog::NoteControl()
    {
    return CAknNoteDialog::NoteControl();
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesControl::SetNoMemoryAllocation
// -----------------------------------------------------------------------------
void CTestSDKNotesNoteDialog::SetNoMemoryAllocation()
    {
    CAknNoteDialog::SetNoMemoryAllocation();
    }
