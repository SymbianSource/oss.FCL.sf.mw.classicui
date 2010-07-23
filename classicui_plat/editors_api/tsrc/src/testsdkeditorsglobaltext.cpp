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
* Description:  Test EIKGTED.h
*
*/


#include "testsdkeditorsglobaltext.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKEditorsGloablText::WriteInternalStateL
// -----------------------------------------------------------------------------
void CTestSDKEditorsGloablText::WriteInternalStateL(RWriteStream& aWriteStream) const
    {
    CEikGlobalTextEditor::WriteInternalStateL( aWriteStream );
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsGloablText::WriteInternalStateL
// -----------------------------------------------------------------------------
void CTestSDKEditorsGloablText::BaseConstructL()
    {
    CEikGlobalTextEditor::BaseConstructL();
    }
