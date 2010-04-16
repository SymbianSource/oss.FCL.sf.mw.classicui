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
* Description: 
*
*/



#include <AknUtils.h>
#include <AknsUtils.h>
#include <AknIconUtils.h>
#include <bautils.h>

#include "AknSmileyImage.h"

const TInt KFrameMaxInterval = 3*1000*1000; // 30s
const TInt KFrameMonitorStep = 5;           // monitor once per 5 call, for increase performence 
const TInt KMaxSameFrameRepeat = 6;         // 5 * 6, animation frame keep same for 6 times will be stopped

#define DELZ(ptr) {delete (ptr); (ptr)=NULL;}


///////////////////////////////////////////////////////////////////////////////////////////////
// BmpUtils
///////////////////////////////////////////////////////////////////////////////////////////////

class BmpUtils
    {
public:
    static void CopyBitmpL(CFbsBitmap* aDesBmp, const CFbsBitmap* aSrcBmp);
    static TBool BitmpIsSame(const CFbsBitmap* aDesBmp, const CFbsBitmap* aSrcBmp);
    };

void BmpUtils::CopyBitmpL(CFbsBitmap* aDesBmp, const CFbsBitmap* aSrcBmp)
    {
    if(!aDesBmp || !aSrcBmp) return;

    TSize size(aSrcBmp->SizeInPixels());
    if(aDesBmp->SizeInPixels() != size)
        {
        aDesBmp->Reset();
        aDesBmp->Create(size, aSrcBmp->DisplayMode());
        }

    CFbsBitmapDevice* device = CFbsBitmapDevice::NewL(aDesBmp);
    CleanupStack::PushL(device);
    CFbsBitGc* gc = NULL;
    User::LeaveIfError(device->CreateContext(gc));
    CleanupStack::PushL(gc);
    gc->BitBlt(TPoint(), aSrcBmp);
    CleanupStack::PopAndDestroy(2);
    }

TBool BmpUtils::BitmpIsSame(const CFbsBitmap* aDesBmp, const CFbsBitmap* aSrcBmp)
    {
    if(!aDesBmp || !aSrcBmp) return FALSE;
    
    if(aDesBmp->SizeInPixels() == aSrcBmp->SizeInPixels())
        {
        TSize size(aSrcBmp->SizeInPixels());
        TInt scanLineLength = CFbsBitmap::ScanLineLength(size.iWidth, aSrcBmp->DisplayMode());
        TInt length = scanLineLength*size.iHeight;
        
        aDesBmp->BeginDataAccess();
        aSrcBmp->BeginDataAccess();
        TInt result = Mem::Compare((TUint8*)aDesBmp->DataAddress(), length, (TUint8*)aSrcBmp->DataAddress(), length);
        aSrcBmp->EndDataAccess(TRUE);
        aDesBmp->EndDataAccess(TRUE);
        
        if(result == KErrNone) return TRUE;
        }
    
    return FALSE;
    }


///////////////////////////////////////////////////////////////////////////////////////////////
// SmileyUtils
///////////////////////////////////////////////////////////////////////////////////////////////

void SmileyUtils::GetCustomizableResPath(TDes& aResPath, const TDesC& aDefaultResPath)
    {
    aResPath = aDefaultResPath;
    
    aResPath[0] = 'c';
    if(!BaflUtils::FileExists(CCoeEnv::Static()->FsSession(), aResPath))
        {
        aResPath[0] = aDefaultResPath[0];
        }
    };


///////////////////////////////////////////////////////////////////////////////////////////////
// CSmileyImage
///////////////////////////////////////////////////////////////////////////////////////////////

CSmileyImage* CSmileyImage::NewL(const TAknsItemID& aSkinImage, TInt aPkgImage, TBool aIsAnimation, MSmileyImageObserver* aObserver)
    {
    CSmileyImage* self = new (ELeave) CSmileyImage(aSkinImage, aPkgImage, aIsAnimation, aObserver);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(); // self;
    return self;
    }

void CSmileyImage::ConstructL()
    {
    iFrameSnap = new (ELeave) CFbsBitmap;
    iAsynchronousTaskTimer = CPeriodic::NewL(CActive::EPriorityStandard);
    }

CSmileyImage::CSmileyImage(const TAknsItemID& aSkinImage, TInt aPkgImage, TBool aIsAnimation, MSmileyImageObserver* aObserver) : 
iImagePkgItem(aPkgImage), 
iIsAnimation(aIsAnimation), 
iImageObserver(aObserver)
    {
    iImageSkinItem.Set(aSkinImage);
    }

CSmileyImage::~CSmileyImage()
    {
    DoRelease();
    DELZ(iFrameSnap);
    DELZ(iAsynchronousTaskTimer);
    }

void CSmileyImage::LoadL(TInt aRepeat, TInt aDelay)
    {
    StartLoadAsynchronousL(aRepeat, aDelay);
    }

void CSmileyImage::Release()
    {
    DoRelease();
    }

void CSmileyImage::SetSize(const TSize& aSize)
    {
    if(iSize != aSize)
        {
        iSize = aSize;
        if(iFrame)
            {
            AknIconUtils::SetSize(iFrame, aSize);
            }
        }
    }

const TSize& CSmileyImage::Size() const
    {
    return iSize;
    }

TBool CSmileyImage::ReadyToDraw() const
    {
    return iReadyToDraw;
    }

const CFbsBitmap* CSmileyImage::Image() const
    {
    return iFrame;
    }

const CFbsBitmap* CSmileyImage::Mask() const
    {
    return iFrameMask;
    }

void CSmileyImage::BitmapChanged(CFbsBitmap* aBitmap)
    {
    iReadyToDraw = TRUE; // animation is ready

    if(iImageObserver) iImageObserver->BitmapChanged(this, aBitmap);

    TRAP_IGNORE(MonitorAnimationEndedL());
    }

void CSmileyImage::DoLoadL()
    {
    StopAnyAsynchronousTask();
    
    if(iFrame) return;

    TFileName smileyMifName;
    SmileyUtils::GetCustomizableResPath(smileyMifName, KSmileyMif);
    if(iImageSkinItem.iMinor > 0)
        {
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        TRAPD(err, AknsUtils::CreateColorIconL(skin, iImageSkinItem, 
                                               KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG19, 
                                               iFrame, iFrameMask, 
                                               smileyMifName, iImagePkgItem, iImagePkgItem, 
                                               AKN_LAF_COLOR(215)));
        }
    else
        {
        TRAPD(err, AknIconUtils::CreateIconL(iFrame, iFrameMask, smileyMifName, iImagePkgItem, iImagePkgItem));
        }
    
    if(iIsAnimation) // the first frame of animation svg is blank without correct content
        {
        iReadyToDraw = FALSE;
        AknIconUtils::SetObserver(iFrame, this);
        
        StopAnimationAsynchronousL(KFrameMaxInterval);
        }
    else // the first frame of static svg has correct content
        {
        iReadyToDraw = TRUE;
        if(iImageObserver) iImageObserver->BitmapChanged(this, iFrame);
        }

    AknIconUtils::SetSize(iFrame, iSize);
    }

void CSmileyImage::DoRelease()
    {
    StopAnyAsynchronousTask();
    
    if(!iFrame) return;

    DELZ(iFrame);
    DELZ(iFrameMask);
    iFrameSnap->Reset();
    
    iReadyToDraw = FALSE;
    }

void CSmileyImage::StopAnyAsynchronousTask()
    {
    iAsynchronousTaskTimer->Cancel();
    }

void CSmileyImage::MonitorAnimationEndedL()
    {
    // for animation doesn't call back
    StopAnimationAsynchronousL(KFrameMaxInterval);
    
    // for reduce the times of animation monitor
    iFrameCounter++;
    if(iFrameCounter % KFrameMonitorStep) return;
    
    // monitor the end of animation clip, replay or stop animation if ended
    if(BmpUtils::BitmpIsSame(iFrameSnap, iFrame))
        {
        iSameFrameCounter++;
        if(iSameFrameCounter > KMaxSameFrameRepeat)
            {
            StopAnimationAsynchronousL();
            }
        }
    else
        {
        iSameFrameCounter = 0;
        BmpUtils::CopyBitmpL(iFrameSnap, iFrame);
        }
    }

void CSmileyImage::HandleAnimationEndedL()
    {
    DoRelease();
    
    if(iRepeatCount != 0)
        {
        iRepeatCount--;
        DoLoadL();
        }
    }

void CSmileyImage::StartLoadAsynchronousL(TInt aRepeat, TInt aDelayMicroSeconds)
    {
    iRepeatCount = aRepeat;

    iAsynchronousTaskTimer->Cancel();
    iAsynchronousTaskTimer->Start(aDelayMicroSeconds, 1, TCallBack(StartLoadAsynchronousCallBackL,this));
    }

TInt CSmileyImage::StartLoadAsynchronousCallBackL(TAny* aPtr)
    {
    CSmileyImage* self = (CSmileyImage*)aPtr;
    self->StopAnyAsynchronousTask();
    self->DoLoadL();
    return KErrNone;
    }

void CSmileyImage::StopAnimationAsynchronousL(TInt aDelayMicroSeconds)
    {
    iAsynchronousTaskTimer->Cancel();
    iAsynchronousTaskTimer->Start(aDelayMicroSeconds, 1, TCallBack(StopAnimationAsynchronousCallBackL,this));
    }

TInt CSmileyImage::StopAnimationAsynchronousCallBackL(TAny* aPtr)
    {
    CSmileyImage* self = (CSmileyImage*)aPtr;
    self->StopAnyAsynchronousTask();
    self->HandleAnimationEndedL();
    return KErrNone;
    }


// end of file

