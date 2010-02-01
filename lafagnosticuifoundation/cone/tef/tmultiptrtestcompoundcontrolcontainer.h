// Copyright (c) 2008-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

#ifndef __CONTROLTESTCONTAINER_H__
#define __CONTROLTESTCONTAINER_H__

#include "tmultiptrtestcontrol.h"
#include "tmultiptrtestchildcontrol.h"
/**
 The window-owning container control
*/

class CMultPtrTestCompoundControlContainer : public CCoeControl
    {
public:
    CMultPtrTestCompoundControlContainer();
    ~CMultPtrTestCompoundControlContainer();
    void ConstructL( const TRect& aRect );

public: // From CCoeControl.
	void Draw( const TRect& ) const;
	void HandlePointerEventL( const TPointerEvent& aPointerEvent );

public:
    CMultiPtrTestChildControl* iChildOne;
    CMultiPtrTestChildControl* iChildTwo;
    };


#endif // __CONTROLTESTCONTAINER_H__

