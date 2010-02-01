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
* Description:  
*
*/

#include <testdompslnframework.rsg>
#include <eiktxlbx.h>
#include <barsread.h>

#include "testdompslnfwbc.h"

//==============================CTestPslnFWBaseContainer=======================
//
// ---------------------------------------------------------------------------
// CTestPslnFWBaseContainer::CPslnFWBaseContainerExt()
// ---------------------------------------------------------------------------
//
CTestPslnFWBaseContainer::CTestPslnFWBaseContainer()
    {
    iListBox = NULL; 
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd static constructor
// ---------------------------------------------------------------------------
//
void CTestPslnFWBaseContainer::ConstructL( const TRect& aRect )
    {
    iListBox = new( ELeave ) CEikTextListBox();
    BaseConstructL( aRect, 0, R_TESTDOMPSLNFRAMEWORK_LISTBOX );
    }
    

// ---------------------------------------------------------------------------
// C++ default Destructor
// ---------------------------------------------------------------------------
//    
CTestPslnFWBaseContainer::~CTestPslnFWBaseContainer()
    {
    }
    
// ---------------------------------------------------------------------------
// CTestPslnFWBaseContainer::ConstructListBoxL()
// ---------------------------------------------------------------------------
//    
void CTestPslnFWBaseContainer::ConstructListBoxL( TInt aResLbxId )
    {
    TResourceReader rReader;
    iCoeEnv->CreateResourceReaderLC( rReader, aResLbxId );
    iListBox->ConstructFromResourceL( rReader );
    CleanupStack::PopAndDestroy(); // rReader
    }
