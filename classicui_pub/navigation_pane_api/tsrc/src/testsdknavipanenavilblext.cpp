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
* Description:  Test aknnavide.h
 *
*/

#include "testsdknavipanenavilblext.h"


// ---------------------------------------------------------------------------
// Implementation of CAknNaviLabelExt
// ---------------------------------------------------------------------------
//
//
// ---------------------------------------------------------------------------
// CAknNaviLabelExt::SizeChanged
// ---------------------------------------------------------------------------
//
void CTestSDKNavipaneNaviLblExt::SizeChanged()
    {
    CAknNaviLabel::SizeChanged();
    }

//
// ---------------------------------------------------------------------------
// CAknNaviLabelExt::Draw
// ---------------------------------------------------------------------------
//
void CTestSDKNavipaneNaviLblExt::Draw(const TRect& aRect) const
    {
    CAknNaviLabel::Draw( aRect );
    }


//
// ---------------------------------------------------------------------------
// CAknNaviLabelExt::CAknNaviLabelExt
// ---------------------------------------------------------------------------
//
CTestSDKNavipaneNaviLblExt::CTestSDKNavipaneNaviLblExt()
    {

    }

