// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// Defines mix-in interace to break dependencey of Eikon Application UI 
// on EikIr library
// 
//

#ifndef __EIKIRFTY_H__
#define __EIKIRFTY_H__

#include <f32file.h>
#include <e32base.h>
#include <eikdef.h>

class CEikEdwin;

/**
@publishedPartner 
@released
*/
class MEikIrFactory
	{
public:
	virtual void SendDataOverIrL(CEikEdwin* aEditor) = 0;
	virtual void ReceiveDataOverIrL(CEikEdwin* aEditor) = 0;
	};


#endif	// __EIKIRFTY_H__
