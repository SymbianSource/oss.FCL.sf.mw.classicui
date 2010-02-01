// Copyright (c) 2004-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// Internal interface for the ICL data loader to communicate with the
// ICL data provider.
//

#ifndef ANIMATIONDATALOADEROBSERVER_H
#define ANIMATIONDATALOADEROBSERVER_H

#include <e32def.h>

/** Internal interface used by the ICL data loader to communicate with the
ICL data provider. Not intended for user derivation.

WARNING: Class for internal use ONLY.  Compatibility is not guaranteed in future releases.

@publishedAll*/
class MICLAnimationDataLoaderObserver
	{
public:
	enum TDataLoaderEvent
		{
		EImagePartialConvert,
		EImageConvertComplete,
		};
public:	
	IMPORT_C virtual void DataLoaderEventL(TDataLoaderEvent aMessage, TInt aError) = 0;
	};

#endif // ANIMATIONDATALOADEROBSERVER_H
