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
* Description:  implement MListBoxSelectionObserver
*
*/


#ifndef C_TESTSDKLISTSLBSOBSERVER_H
#define C_TESTSDKLISTSLBSOBSERVER_H

#include <eiklbx.h>

class CTestSDKListsLBSObserver : public CBase, public MListBoxSelectionObserver
{
public:
    // from MListBoxSelectionObserver
    /**
     * Notification of entering and leaving marking mode. Marking mode
     * is enabled by long pressing shift, ctrl or hash keys (when hash key marking is enabled).
     *
     * @param aListBox The source list box of this message.
     * @param aSelectionModeEnabled ETrue, when entering selection (marking) mode.
     */
    virtual void SelectionModeChanged(CEikListBox* aListBox, TBool aSelectionModeEnabled);
};

#endif /*C_TESTSDKLISTSLBSOBSERVER_H*/
