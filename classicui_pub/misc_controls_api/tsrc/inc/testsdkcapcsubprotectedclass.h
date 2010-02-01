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
* Description:  misc_controls_api
*
*/

#ifndef C_TESTSDKCAPCSUBPROTECTEDCLASS_H
#define C_TESTSDKCAPCSUBPROTECTEDCLASS_H
//  INCLUDES
#include <eikcapc.h>
#include <coemop.h>

#include "testsdkmisccontrols.h"
/**
*  CTestSDKMiscControls test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
class CTestSDKMiscControls;
class CTestSubCaptionedControl : public CEikCaptionedControl, public MPointerEventObserver
    {
public:
    /**
    *  Draw
    */
    void Draw(const TRect& aRect) const;
    /**
    *  WriteInternalStateL
    */
    void WriteInternalStateL(RWriteStream& aWriteStream) const;
    /**
    *  MopSupplyObject
    */
    TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
    /**
    *  PointerEvent
    */
    virtual bool PointerEvent(CEikCaptionedControl *aControl, const TPointerEvent& aPointerEvent);
    };
#endif /*C_TESTSDKCAPCSUBPROTECTEDCLASS_H*/
