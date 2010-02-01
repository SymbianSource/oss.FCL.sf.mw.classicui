/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef __EIKSVPRV_H__
#define __EIKSVPRV_H__

#ifndef __EIKDIALG_H__
#include <eikdialg.h>
#endif

/**
* CEikServPanicScreen
*/
class CEikServPanicScreen : public CEikDialog
    {
public:
    CEikServPanicScreen(RThread& aThread);
private: // from CEikDialog
    void PreLayoutDynInitL();
protected:
    RThread& iThread;
    };

/**
* CEikServResetReasonDialog
*
* Not currently used in Avkon, but could be wired up to Shift-Ctrl-Alt-r if
* from somewhere if it was thought to be useful
*
* This dialog examines any information available on HW that recorded the
* reason for the reset and displays it.
*/
class CEikServResetReasonDialog : public CEikDialog
    {
private: // virtual from CEikDialog
    virtual void PreLayoutDynInitL();
    };

#endif
