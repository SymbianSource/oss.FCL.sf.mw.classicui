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

#include <e32hal.h>
#include <s32file.h>
#include "eiksvprv.h"
#include <eiksrvui.rsg>
#include "eiksrv.hrh"
#include <hal.h>
#include <hal_data.h>
#include <aknnotecontrol.h>

// ===================
// CEikServPanicScreen
// ===================

CEikServPanicScreen::CEikServPanicScreen(RThread& aThread) : iThread(aThread)
    {
    SetGloballyCapturing(ETrue);
    }
    
void CEikServPanicScreen::PreLayoutDynInitL()
    {
    CAknNoteControl* note = STATIC_CAST(CAknNoteControl*, Control(EESrvDlgPanicName));
    TBuf<64> programName;
    TBuf<64> reasonCategory;
    TBuf<64> reasonCode;
    iEikonEnv->ReadResource(programName, R_EIKSERV_PANIC_DIALOG_NAME);
    iEikonEnv->ReadResource(reasonCategory, R_EIKSERV_PANIC_DIALOG_CATEGORY);
    iEikonEnv->ReadResource(reasonCode, R_EIKSERV_PANIC_DIALOG_CODE);
    programName.Append(iThread.Name());
    reasonCategory.Append(iThread.ExitCategory());
    reasonCode.AppendNum(iThread.ExitReason());
    note->UpdateLabelsL(programName, reasonCategory, reasonCode);
    }

// =========================
// CEikServResetReasonDialog
// =========================

// Populate the dialog with reset info.
// Debug & tech support use only - hence hard coded text.
void CEikServResetReasonDialog::PreLayoutDynInitL()
    {
    TInt reason;
    HAL::Get(HAL::ESystemStartupReason,reason);
    TBuf<80> reasonBuf;
    TExcInfo exceptInfo;
    UserHal::ExceptionInfo(exceptInfo);
    _LIT(KReasonColdStart,"Cold Start");
    _LIT(KReasonColdReset,"Cold Reset");
    _LIT(KReasonNewOs,"New OS");
    _LIT(KReasonPowerFail,"Power failed");
    _LIT(KReasonarmReset,"Warm Reset");
    switch (reason)
        {
        case EStartupCold:
            reasonBuf = KReasonColdStart; 
            break;
        case EStartupColdReset:
            reasonBuf = KReasonColdReset; 
            break;
        case EStartupNewOs:
            reasonBuf = KReasonNewOs; 
            break;
        case EStartupPowerFail:
            reasonBuf = KReasonPowerFail; 
            break;
        case EStartupWarmReset:
            reasonBuf = KReasonarmReset; 
            break;
        case EStartupKernelFault:
            {
            TUint32 decode[3];
            decode[0] = TUint32(exceptInfo.iCodeAddress);
            decode[1] = TUint32(exceptInfo.iDataAddress);
            decode[2] = 0;
            
            // Interpret decode as a null-terminated string.
            TPtrC category((TText*)&decode[0]);
            TInt faultno;
            UserHal::FaultReason(faultno);
            
            if (faultno == 0x10000000)
                {
                _LIT(KReason,"Kernel Exception");
                reasonBuf=(KReason);
                }
            else if (faultno >= 0x10000)
                {
                _LIT(KReason,"Kernel PANIC: %d %S ");
                reasonBuf.Format(KReason, faultno-0x10000,&category);
                }
            else
                {
                _LIT(KReason,"Kernel FAULT: %d %S ");
                reasonBuf.Format(KReason, faultno,&category);
                }
            }
            break;
        default:
            reasonBuf.Num((TInt)reason);
            break;
        }
    
    SetLabelL(EESrvResetInfoReason, reasonBuf);
    
    // Last exception.
    if (reason >= EStartupPowerFail)
        {
        TBuf<80> lastExceptBuf;
        TInt exceptno;
        UserHal::ExceptionId(exceptno);
        _LIT(KFormat,"(No. %d: Code 0x%08x Data 0x%08x) ");
        lastExceptBuf.Format(KFormat, exceptno, exceptInfo.iCodeAddress, exceptInfo.iDataAddress);
        SetLabelL(EESrvResetInfoLastException, lastExceptBuf);
        }
    else
        {
        SetLineDimmedNow(EESrvResetInfoLastException, ETrue);
        }
    }

// End of file
