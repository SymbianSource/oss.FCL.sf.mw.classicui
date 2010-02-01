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
//

#ifndef __EIKEMBAL_H__
#define __EIKEMBAL_H__

#include <e32base.h>
#include <f32file.h>
#include <bamdesca.h>
#include <apadef.h>
#include <apaid.h>

class CEikDocument;
class CApaProcess;
class RApaLsSession;


/** Provides a list of all embeddable applications on the device. 

Hidden applications are omitted from the list. The list is sorted by UID.

@see TApaAppCapability::iAppIsHidden
@publishedAll 
@released */
class CEikEmbeddableAppList : public CArrayFixFlat<TApaAppInfo>, public MDesCArray
	{
public:
	IMPORT_C CEikEmbeddableAppList();
	IMPORT_C ~CEikEmbeddableAppList();
	IMPORT_C void ConstructL();
	IMPORT_C void ConstructL(const TApaEmbeddabilityFilter& aFilter);
	IMPORT_C CEikDocument* CreateEmbeddedDocumentL(TInt aIndex,CApaProcess* aProcess);
private: // from MDesCArray
	IMPORT_C TInt MdcaCount() const;
	IMPORT_C TPtrC MdcaPoint(TInt aIndex) const;
private: // Reserved methods
	IMPORT_C virtual void CEikEmbeddableAppList_Reserved1();
	IMPORT_C virtual void CEikEmbeddableAppList_Reserved2();
private: // utility methods
	TInt GetAppListL(const TApaEmbeddabilityFilter& aFilter);
	TInt DoGetAppListL(RApaLsSession& aLs, const TApaEmbeddabilityFilter& aFilter);
	void SortAppListL();
private:
	TInt iCEikEmbeddableAppList_Reserved1;
	};

#endif	// __EIKEMBAL_H__
