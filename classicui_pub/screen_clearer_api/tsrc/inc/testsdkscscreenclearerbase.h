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
* Description:  Test AknClearer.h & eikspace.h
*
*/

#ifndef C_TESTSDKSCSCREENCLEARERBASE_H
#define C_TESTSDKSCSCREENCLEARERBASE_H

#include <aknclearer.h>

// ===========class CTestSDKSCScreenClearerBase for protected method===============
class CTestSDKSCScreenClearerBase : public CAknScreenClearerBase
    {
public:
    /**
    * Constructor.
    */
    CTestSDKSCScreenClearerBase();
    /**
    * Destructor.
    */
    virtual ~CTestSDKSCScreenClearerBase();

    /**
    * Symbian 2nd phase constructor.
    *
    * @param aParent Parent window group.
    * @param aOrdinalPos Ordinal position of the blank window.
    * @param aBlankAppStatusPane A flag to decide if application status pane area is to blanked or not.
    */
    void ConstructL(RWindowGroup& aParent, TInt aOrdinalPos, TBool aBlankAppStatusPane);
    };
#endif /*C_TESTSDKSCSCREENCLEARERBASE_H*/
