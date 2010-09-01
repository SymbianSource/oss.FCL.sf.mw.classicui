/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  AVKON smiley image.
*
*/




#ifndef AKNSMILEYIMAGE_H
#define AKNSMILEYIMAGE_H

// INCLUDES
#include <AknIconObserver.h> 


// CLASS DECLARATION

class CSmileyImage;

////////////////////////////////////////////////////////////////////

_LIT(KSmileyMif, "z:\\resource\\apps\\smiley.mif");
_LIT(KSmileyRsc, "z:\\resource\\smiley.rsc");

class SmileyUtils
    {
public:
    static void GetCustomizableResPath(TDes& aResPath, const TDesC& aDefaultResPath);
    };

////////////////////////////////////////////////////////////////////

class MSmileyImageObserver
    {
public:
    virtual void BitmapChanged(CSmileyImage* aSmileyImage, CFbsBitmap* aBitmap)=0;
    };

////////////////////////////////////////////////////////////////////

// CSmileyImage can be a still or animated svg image

class CSmileyImage : public CBase, public MAknIconObserver
    {
public:
    static CSmileyImage* NewL(const TAknsItemID& aSkinImage, TInt aPkgImage, TBool aIsAnimation, MSmileyImageObserver* aObserver);
    virtual ~CSmileyImage();

private:
    CSmileyImage(const TAknsItemID& aSkinImage, TInt aPkgImage, TBool aIsAnimation, MSmileyImageObserver* aObserver);
    void ConstructL();

public:
    void LoadL(TInt aRepeat=0, TInt aDelay=0); // can load static and animation image
    void Release();
    void SetSize(const TSize& aSize);
    const TSize& Size() const;
    
public:
    TBool ReadyToDraw() const;
    const CFbsBitmap* Image() const;
    const CFbsBitmap* Mask() const;

private:
    void BitmapChanged(CFbsBitmap* aBitmap); // from MAknIconObserver
    void MonitorAnimationEndedL();

private:
    void DoLoadL();
    void DoRelease();
    void DoHandleEndedL();

private:
    inline void StopAsynchronousTaskTimer();
 
    void StartLoadAsynchronousL(TInt aDelayMicroSeconds=0);
    static TInt StartLoadAsynchronousCallBackL(TAny* aPtr);

    void StopAnimationAsynchronousL(TInt aDelayMicroSeconds=0);
    static TInt StopAnimationAsynchronousCallBackL(TAny* aPtr);

private:
    TAknsItemID             iImageSkinItemId;
    const TInt              iImageMifPkgItemId;
    const TBool             iIsAnimation;

private:
    MSmileyImageObserver*   iImageObserver;
    CPeriodic*              iAsynchronousTaskTimer;

private:
    TSize                   iSize;
    CFbsBitmap*             iFrame;
    CFbsBitmap*             iFrameMask;
    TBool                   iReadyToDraw;

private: // for animation
    TInt                    iRepeatCount;
    CFbsBitmap*             iFrameSnap;
    TInt                    iFrameCounter;
    TInt                    iSameFrameCounter;

    };


#endif // AKNSMILEYSVGRES_H
