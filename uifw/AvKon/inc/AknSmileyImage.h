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

private: // from MAknIconObserver
    void BitmapChanged(CFbsBitmap* aBitmap);

private:
    void DoLoadL();
    void DoRelease();
    void StopAnyAsynchronousTask();

    void MonitorAnimationEndedL();
    void HandleAnimationEndedL();

private:
    void StartLoadAsynchronousL(TInt aRepeat, TInt aDelayMicroSeconds=0);
    static TInt StartLoadAsynchronousCallBackL(TAny* aPtr);
    
private:
    void StopAnimationAsynchronousL(TInt aDelayMicroSeconds=0);
    static TInt StopAnimationAsynchronousCallBackL(TAny* aPtr);

private:
    TAknsItemID             iImageSkinItem;
    TInt                    iImagePkgItem;
    const TBool             iIsAnimation;
    TSize                   iSize;
    MSmileyImageObserver*   iImageObserver;
    CPeriodic*              iAsynchronousTaskTimer;

private:
    CFbsBitmap*             iFrame;
    CFbsBitmap*             iFrameMask;
    
private:
    CFbsBitmap*             iFrameSnap;
    TInt                    iFrameCounter;
    TInt                    iSameFrameCounter;

private:
    TBool                   iReadyToDraw;
    TInt                    iRepeatCount;

    };


#endif // AKNSMILEYSVGRES_H
