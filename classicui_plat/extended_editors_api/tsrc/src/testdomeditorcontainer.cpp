/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  ?Description
*
*/



#include "testdomeditorcontainer.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMEditorContainer::CTestDOMEditorContainer
// -----------------------------------------------------------------------------
//
CTestDOMEditorContainer::CTestDOMEditorContainer()
    {
    }

// -----------------------------------------------------------------------------
// CTestDOMEditorContainer::~CTestDOMEditorContainer
// -----------------------------------------------------------------------------
//
CTestDOMEditorContainer::~CTestDOMEditorContainer()
    {
    }

// -----------------------------------------------------------------------------
// CTestDOMEditorContainer::NewL
// -----------------------------------------------------------------------------
//
CTestDOMEditorContainer* CTestDOMEditorContainer::NewL()
    {
    CTestDOMEditorContainer* self = new ( ELeave ) CTestDOMEditorContainer;
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CTestDOMEditorContainer::ConstructL
// -----------------------------------------------------------------------------
//
void CTestDOMEditorContainer::ConstructL()
    {
    CreateWindowL();
    SetRect( Rect() );
    ActivateL();
    }

// -----------------------------------------------------------------------------
// CTestDOMEditorContainer::Draw
// -----------------------------------------------------------------------------
//
void CTestDOMEditorContainer::Draw(const TRect& /*aRect*/) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );  
    gc.DrawRect( Rect() );
    }

// -----------------------------------------------------------------------------
// CTestDOMEditorContainer::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditorContainer::CountComponentControls() const
    {
    return 0;
    }

// -----------------------------------------------------------------------------
// CTestDOMEditorContainer::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CTestDOMEditorContainer::ComponentControl(TInt /*aIndex*/) const
    {
    return NULL;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditorContainer::SizeChanged
// -----------------------------------------------------------------------------
//
void CTestDOMEditorContainer::SizeChanged()
    {
    }

