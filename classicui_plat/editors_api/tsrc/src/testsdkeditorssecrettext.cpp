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
* Description:  Test EIKSECED.h
*
*/


#include "testsdkeditorssecrettext.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKEditorsSecretText::EditObserver
// -----------------------------------------------------------------------------
void CTestSDKEditorsSecretText::AppendCharacterL( TInt aKeyCode )
    {
    CEikSecretEditor::AppendCharacterL( aKeyCode );
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsSecretText::Update
// -----------------------------------------------------------------------------
void CTestSDKEditorsSecretText::Update()
    {
    CEikSecretEditor::Update();
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsSecretText::Update
// -----------------------------------------------------------------------------
void CTestSDKEditorsSecretText::SizeChanged()
    {
    CEikSecretEditor::SizeChanged();
    }
