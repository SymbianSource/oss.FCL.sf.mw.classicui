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
* Description:  Test eikfrlbd.h
*
*/

#ifndef C_TESTSDKLISTSLBABDRAWER_H
#define C_TESTSDKLISTSLBABDRAWER_H

#include <e32base.h>
#include <eikfrlbd.h>

class CTestSDKListsLBABDrawer : public CBase, public MListBoxAnimBackgroundDrawer
{
public:
    /*
     * constructor
     */
    CTestSDKListsLBABDrawer();

    /*
     * destructor
     */
    virtual ~CTestSDKListsLBABDrawer();

    /**
     * @param aGc Bitmapped graphical context to draw to.
     * @return 
     */ 
    virtual TBool DrawHighlightAnimBackground( CFbsBitGc& aGc ) const;
};

#endif /*C_TESTSDKLISTSLBABDRAWER_H*/
