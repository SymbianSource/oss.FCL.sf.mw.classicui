/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Process popup window for application. 
*
*/









// INCLUDE FILES
#include <eiklabel.h>
#include <aknconsts.h>
#include <akncontext.h>
#include <coemain.h>

#include "BCTestVolumePopupWindow.h"

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// ctor do nothing.
// ---------------------------------------------------------
//
CBCTestVolumePopUpWindow::CBCTestVolumePopUpWindow() : iColor(KRgbBlue)
    {
    }

// ---------------------------------------------------------
// symbian 2nd ctor
// ---------------------------------------------------------
//
void CBCTestVolumePopUpWindow::ConstructL(const TRect& aRect)
    {
    iMyWindowGroup=RWindowGroup(iCoeEnv->WsSession());
    
    User::LeaveIfError(iMyWindowGroup.Construct((TUint32)&iMyWindowGroup));
    
    iMyWindowGroup.SetOrdinalPosition(0, ECoeWinPriorityAlwaysAtFront);
    iMyWindowGroup.EnableReceiptOfFocus(EFalse);
    
    CreateWindowL(&iMyWindowGroup);
    SetRect(aRect);
    EnableDragEvents();
    ActivateL();
    }

// ---------------------------------------------------------
// dtor do nothing.
// ---------------------------------------------------------
//
CBCTestVolumePopUpWindow::~CBCTestVolumePopUpWindow()
    {
    iMyWindowGroup.Close();
    }

// ---------------------------------------------------------
// CBCTestVolumePopUpWindow
// ---------------------------------------------------------
//
void CBCTestVolumePopUpWindow::SetColor(TRgb aColor)
    {
    iColor = aColor;
    }

// ---------------------------------------------------------
// CBCTestVolumePopUpWindow::Draw(const TRect& aRect) const
// Draw function.
// ---------------------------------------------------------
//
void CBCTestVolumePopUpWindow::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.SetBrushColor(KRgbBlue);
    gc.DrawRect(aRect);
    }

// End of File
