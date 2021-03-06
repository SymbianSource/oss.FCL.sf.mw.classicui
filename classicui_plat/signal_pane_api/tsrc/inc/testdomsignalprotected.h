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
* Description:  signal_pane_api
*
*/

#ifndef C_TESTDOMSIGNALPROTECTED_H
#define C_TESTDOMSIGNALPROTECTED_H

//  INCLUDES
#include <aknsignal.h>

#include "testdomsignalpane.h"

/**
*  CTestDOMSignalPane test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
class CTestDOMSignalPane;
class CTestDOMSignal : public CAknSignalPane
    {
    
friend class CTestDOMSignalPane;

    /**
     *  HandlePointerEventL
     *  @since S60 5.0
     */
    void HandlePointerEventL( const TPointerEvent& aPointerEvent );
    };
#endif /*C_TESTDOMSIGNALPROTECTED_H*/
