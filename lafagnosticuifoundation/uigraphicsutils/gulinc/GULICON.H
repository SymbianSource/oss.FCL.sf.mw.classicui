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


#if !defined(__GULICON_H__)
#define __GULICON_H__  

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

class CFbsBitmap;

class CGulIcon : public CBase
/** Packages two bitmaps, one each for an icon image and its mask. 

@publishedAll
@released */
	{
public:
	IMPORT_C static CGulIcon* NewLC();
	IMPORT_C static CGulIcon* NewL();
	IMPORT_C static CGulIcon* NewL(CFbsBitmap* aBitmap, CFbsBitmap* aMask=NULL);
	//
	IMPORT_C void SetBitmap(CFbsBitmap* aBitmap);
	IMPORT_C void SetMask(CFbsBitmap* aMask);
	IMPORT_C CFbsBitmap* Bitmap() const;
	IMPORT_C CFbsBitmap* Mask() const;
	IMPORT_C void SetBitmapsOwnedExternally(TBool aOwnedExternally);
	IMPORT_C TBool BitmapsOwnedExternally() const;
	//
	IMPORT_C ~CGulIcon();
private:
	CGulIcon();
private:
	CFbsBitmap* iBitmap;
	CFbsBitmap* iMask;
	TBool iBitmapsOwnedExternally;
	};

#endif
