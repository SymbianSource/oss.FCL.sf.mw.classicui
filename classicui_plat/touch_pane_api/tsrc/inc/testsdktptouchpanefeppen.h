/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef C_TESTSDKTPTOUCHPANEFEPPEN_H
#define C_TESTSDKTPTOUCHPANEFEPPEN_H

#include <akntouchpane.h>
#include <aknfeppensupportinterface.h>

/**
 *  CTestTouchPaneFepPen class
 */
class CTestSDKTPTouchPaneFepPen: public CBase, public MAknFepPenSupportInterface
    {
    /**
     * Start pen input method
     *
     * @since S60 v3.2
     * @return None
     */
    void ActivatePenInputL();

    /**
     * Close pen input method
     *
     * @since S60 v3.2
     * @return None
     */
    void DeactivatePenInputL();
    };

#endif /*C_TESTSDKTPTOUCHPANEFEPPEN_H*/
