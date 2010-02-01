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
* Description:  Test aknnotecontrol.h
*
*/


//  INCLUDES
#include "testsdknotesnotecontrol.h"

// -----------------------------------------------------------------------------
// CTestSDKNotesNoteControl::CTestSDKNotesNoteControl
// -----------------------------------------------------------------------------
CTestSDKNotesNoteControl::CTestSDKNotesNoteControl() : CAknNoteControl()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesNoteControl::MopSupplyObject
// -----------------------------------------------------------------------------
TTypeUid::Ptr CTestSDKNotesNoteControl::MopSupplyObject( TTypeUid aId )
    {
    return CAknNoteControl::MopSupplyObject( aId );
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesNoteControl::ConstructFromResourceL
// -----------------------------------------------------------------------------
void CTestSDKNotesNoteControl::ConstructFromResourceL(TResourceReader& /*aRes*/)
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesNoteControl::Draw
// -----------------------------------------------------------------------------
void CTestSDKNotesNoteControl::Draw(const TRect& /*aRect*/) const
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesNoteControl::SizeChanged
// -----------------------------------------------------------------------------
void CTestSDKNotesNoteControl::SizeChanged()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesNoteControl::MinimumSize
// -----------------------------------------------------------------------------
TSize CTestSDKNotesNoteControl::MinimumSize()
    {
    return TSize( 0, 0 );
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesNoteControl::CountComponentControls
// -----------------------------------------------------------------------------
TInt CTestSDKNotesNoteControl::CountComponentControls() const
    {
    return 0;
    }

// -----------------------------------------------------------------------------
// CTestSDKNotesNoteControl::ComponentControl
// -----------------------------------------------------------------------------
CCoeControl* CTestSDKNotesNoteControl::ComponentControl(TInt /*anIndex*/) const
    {
    return NULL;
    }

