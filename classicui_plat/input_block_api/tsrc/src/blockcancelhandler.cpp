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
* Description:  Test AknInputBlock.h
*
*/


/*
 *  [INCLUDE FILES]
 */
#include "blockcancelhandler.h"

// -----------------------------------------------------------------------------
// CBlockCancelHandler::CBlockCancelHandler
// -----------------------------------------------------------------------------
//
CBlockCancelHandler::CBlockCancelHandler()
{
    iFlag = EFalse;
}

// -----------------------------------------------------------------------------
// CBlockCancelHandler::~CBlockCancelHandler
// -----------------------------------------------------------------------------
//
CBlockCancelHandler::~CBlockCancelHandler()
{
}

// -----------------------------------------------------------------------------
// CBlockCancelHandler::AknInputBlockCancel
// -----------------------------------------------------------------------------
//
void CBlockCancelHandler::AknInputBlockCancel()
    {
    iFlag = ETrue;
    }

// -----------------------------------------------------------------------------
// CBlockCancelHandler::Getflag
// -----------------------------------------------------------------------------
//
TBool CBlockCancelHandler::Getflag()
    {
    return iFlag;
    }

// -----------------------------------------------------------------------------
// CBlockCancelHandler::Getflag
// -----------------------------------------------------------------------------
//
void CBlockCancelHandler::Setfalg( TBool aFlag )
    {
    iFlag = aFlag;
    }
