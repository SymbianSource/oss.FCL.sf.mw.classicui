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
* Description:  test Observer
*
*/


#ifndef C_TESTSDKLISTSLBICOBSERVER_H
#define C_TESTSDKLISTSLBICOBSERVER_H

#include <e32base.h>
#include <eiklbx.h>

class CTestSDKListsLBICObserver : public CBase, public MListBoxItemChangeObserver
{
public:
    //from MListBoxItemChangeObserver
    /**
     * Notification and handling of a list box item change.
     *
     * @param aListBox The source list box of this message.
     */
    virtual void ListBoxItemsChanged(CEikListBox* aListBox);
};

#endif /*C_TESTSDKLISTSLBICOBSERVER_H*/
