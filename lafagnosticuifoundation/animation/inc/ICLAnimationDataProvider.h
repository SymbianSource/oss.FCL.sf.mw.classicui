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
//

#ifndef __ICLANIMATIONDATAPROVIDER_H__
#define __ICLANIMATIONDATAPROVIDER_H__

#include <animationdataprovider.h>

#include <e32std.h>
#include <animationframe.h>
#include <animationmixins.h>

#ifndef SYMBIAN_ENABLE_SPLIT_HEADERS
// For phase2 CICLAnimationDataProvider needs refactoring to convert it's derivation from
// MICLAnimationDataLoaderObserver to having a CAnimationDataLoaderObserver* member
#include <animationdataloaderobserver.h>
#endif //SYMBIAN_ENABLE_SPLIT_HEADERS


_LIT8(KBitmapAnimationDataType, "bitmap");

class CICLAnimationDataLoader;

/**
Data provider for frame based animations.

This data provider expects to be provided with a file which can be interpreted
as an animation using the Image Conversion Library (ICL).  An example would be
an animated GIF.  The default data type for this provider is "bitmap".

@see CBitmapAnimator
@publishedAll
@released
*/
class CICLAnimationDataProvider : public CAnimationDataProvider, public MICLAnimationDataLoaderObserver
	{
public:
    IMPORT_C CICLAnimationDataProvider();
    IMPORT_C ~CICLAnimationDataProvider();
    IMPORT_C void SetFileL(RFs & aFs, const TFileName& aFileName);
    IMPORT_C TPtrC8 DataType();
    virtual void StartL();
protected:
	IMPORT_C virtual void CICLAnimationDataProvider_Reserved1();
	IMPORT_C virtual void CICLAnimationDataProvider_Reserved2();
	// From CAnimationDataProvider
	IMPORT_C virtual void CAnimationDataProvider_Reserved1();
	IMPORT_C virtual void CAnimationDataProvider_Reserved2();
private:
	TInt iCICLAnimationDataProvider_Reserved;
private:
    CAnimationFrame::THandles CurrentFrame() const;
    void DecodeImageL();
    void DataDeliveryL();
    void Reset();
    // From MICLAnimationDataLoaderObserver
    virtual void DataLoaderEventL(TDataLoaderEvent aEvent, TInt aError);
private: 
	CICLAnimationDataLoader* iDataLoader;
	CAnimationFrame* iCurrentFrame;
	TInt iFlags;
	};

#endif //__ICLANIMATIONDATAPROVIDER_H__

