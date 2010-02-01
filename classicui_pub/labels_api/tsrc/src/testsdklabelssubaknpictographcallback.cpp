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
* Description:  Test EIKLABEL.H
*
*/


#include "testsdklabelssubaknpictographcallback.h"

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKLabelsSubAknPictographCallBack::NewLC
// -----------------------------------------------------------------------------
CTestSDKLabelsSubAknPictographCallBack* CTestSDKLabelsSubAknPictographCallBack::NewLC()
    {
    CTestSDKLabelsSubAknPictographCallBack* self = new (ELeave) CTestSDKLabelsSubAknPictographCallBack;
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// -----------------------------------------------------------------------------
// CTestSDKLabelsSubAknPictographCallBack::~CTestSDKLabelsSubAknPictographCallBack
// -----------------------------------------------------------------------------
CTestSDKLabelsSubAknPictographCallBack::~CTestSDKLabelsSubAknPictographCallBack()
    {
    delete iInterface;
    }

// -----------------------------------------------------------------------------
// CTestSDKLabelsSubAknPictographCallBack::DrawPictographArea
// -----------------------------------------------------------------------------
void CTestSDKLabelsSubAknPictographCallBack::DrawPictographArea()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabelsSubAknPictographCallBack::ConstructL
// -----------------------------------------------------------------------------
void CTestSDKLabelsSubAknPictographCallBack::ConstructL()
    {
    iInterface = CAknPictographInterface::NewL( *this, *this);
    }

// -----------------------------------------------------------------------------
// CTestSDKLabelsSubAknPictographCallBack::CTestSDKLabelsSubAknPictographCallBack
// -----------------------------------------------------------------------------
CTestSDKLabelsSubAknPictographCallBack::CTestSDKLabelsSubAknPictographCallBack():CCoeControl()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKLabelsSubAknPictographCallBack::Interface
// -----------------------------------------------------------------------------
CAknPictographInterface* CTestSDKLabelsSubAknPictographCallBack::Interface()
    {
    return iInterface;
    }
