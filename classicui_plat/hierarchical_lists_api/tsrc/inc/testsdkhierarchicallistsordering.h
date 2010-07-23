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
* Description:  test akntreelist.h
*
*/


#ifndef C_TESTSDKHIERARCHICALLISTSORDERING_H
#define C_TESTSDKHIERARCHICALLISTSORDERING_H

#include <e32base.h>
#include <akncustomtreeordering.h>
#include <akntreelistobserver.h>

class CTestSDKOrdering : public CBase, 
                         public MAknCustomTreeOrdering,
                         public MAknTreeListObserver
    {
public:// Constructors and destructor
    /**
    * C++ default constructor.
    */
    CTestSDKOrdering();
    
    /**
    * Destructor.
    */
    ~CTestSDKOrdering();
    
    /**
    * From class MAknCustomTreeOrdering
    */
    TInt Compare( TAknTreeItemID aFirst, TAknTreeItemID aSecond );
    
    /**
    * From class MAknTreeListObserver
    */
    TInt HandleTreeListEvent( CAknTreeList& aList, TAknTreeItemID aItem, TEvent aEvent );
    };

#endif /*C_TESTSDKHIERARCHICALLISTSORDERING_H*/
