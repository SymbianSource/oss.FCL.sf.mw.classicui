// Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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

/**
 @file
 @internalComponent - Internal Symbian test code  
*/


#ifndef altdoc_H 
#define altdoc_H 

#include <eikdoc.h>

class CAltDocument : public CEikDocument
	{
public:
	CAltDocument(CEikApplication& aApp);
private: //From CQikDocument
	CEikAppUi* CreateAppUiL();
	};
 
#endif 
