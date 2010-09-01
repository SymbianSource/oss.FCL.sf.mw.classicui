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

const TInt KFrameMaxInterval = 3*1000*1000; // 3s
const TInt KFrameMonitorStep = 5;           // monitor once per 5 call, for increase performence 
const TInt KMaxSameFrameRepeat = 6;         // 5 * 6, animation whose frame keep the same for 6 times call back, it will be stopped

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
    if(!aDesBmp || !aSrcBmp) return EFalse;
    
    if(aDesBmp->SizeInPixels() == aSrcBmp->SizeInPixels())
        {
        TSize size(aSrcBmp->SizeInPixels());
        TInt scanLineLength = CFbsBitmap::ScanLineLength(size.iWidth, aSrcBmp->DisplayMode());
        TInt length = scanLineLength*size.iHeight;
        
        aDesBmp->BeginDataAccess();
        aSrcBmp->BeginDataAccess();
        TInt result = Mem::Compare((TUint8*)aDesBmp->DataAddress(), length, (TUint8*)aSrcBmp->DataAddress(), length);
        aSrcBmp->EndDataAccess(ETrue);
        aDesBmp->EndDataAccess(ETrue);
        
        if(result == KErrNone) return ETrue;
        }
    
    return EFalse;
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
iImageMifPkgItemId(aPkgImage), 
iIsAnimation(aIsAnimation), 
iImageObserver(aObserver)
    {
    iImageSkinItemId.Set(aSkinImage);
    }

CSmileyImage::~CSmileyImage()
    {
    DoRelease();
    DELZ(iFrameSnap);
    DELZ(iAsynchronousTaskTimer);
    }

void CSmileyImage::LoadL(TInt aRepeat, TInt aDelay)
    {
    iRepeatCount = aRepeat;
    
    if(aDelay > 0)
        {
        StartLoadAsynchronousL(aDelay);
        }
    else
        {
        DoLoadL();
        }
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
    iReadyToDraw = ETrue; // animation is ready

    if(iImageObserver) iImageObserver->BitmapChanged(this, aBitmap);

    TRAP_IGNORE(MonitorAnimationEndedL());
    }

void CSmileyImage::MonitorAnimationEndedL()
    {
    // for animation doesn't call back
    StopAnimationAsynchronousL(KFrameMaxInterval);
    
    // for reduce the times of animation monitor
    iFrameCounter++;
    if(iFrameCounter % KFrameMonitorStep) return;
    
    // for not call back any more
    StopAnimationAsynchronousL(KFrameMaxInterval);
    
    // monitor the end of animation clip, replay or stop animation if ended
    if(BmpUtils::BitmpIsSame(iFrameSnap, iFrame))
        {
        iSameFrameCounter++;
        if(iSameFrameCounter > KMaxSameFrameRepeat)
            {
            StopAnimationAsynchronousL(); // can not stop animation synchronously
            }
        }
    else
        {
        iSameFrameCounter = 0;
        BmpUtils::CopyBitmpL(iFrameSnap, iFrame);
        }
    }

void CSmileyImage::DoLoadL()
    {
    StopAsynchronousTaskTimer();

    if(iFrame) return;

    TFileName smileyMifName;
    SmileyUtils::GetCustomizableResPath(smileyMifName, KSmileyMif);

    if(iImageSkinItemId.iMinor > 0)
        {
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        TRAP_IGNORE(AknsUtils::CreateColorIconL(skin, iImageSkinItemId, 
                                                KAknsIIDQsnTextColors,EAknsCIQsnTextColorsCG19, 
                                                iFrame,iFrameMask, 
                                                smileyMifName, iImageMifPkgItemId,iImageMifPkgItemId, 
                                                AKN_LAF_COLOR(215)));
        }
    else
        {
        TRAP_IGNORE(AknIconUtils::CreateIconL(iFrame,iFrameMask,smileyMifName,iImageMifPkgItemId,iImageMifPkgItemId));
        }
    
    if(iIsAnimation) // the first frame of animation svg is blank without correct content
        {
        iReadyToDraw = EFalse;
        AknIconUtils::SetObserver(iFrame, this);
        StopAnimationAsynchronousL(KFrameMaxInterval); // monitor for no callback
        }
    else // the first frame of static svg has correct content
        {
        iReadyToDraw = ETrue;
        if(iImageObserver) iImageObserver->BitmapChanged(this, iFrame);
        }

    AknIconUtils::SetSize(iFrame, iSize);
    }

void CSmileyImage::DoRelease()
    {
    StopAsynchronousTaskTimer();

    if(!iFrame) return;

    DELZ(iFrame);
    DELZ(iFrameMask);
    iFrameSnap->Reset();
    
    iReadyToDraw = EFalse;
    }

void CSmileyImage::DoHandleEndedL()
    {
    DoRelease();
    
    if(iRepeatCount != 0)
        {
        iRepeatCount--;
        DoLoadL();
        }
    }

void CSmileyImage::StopAsynchronousTaskTimer()
    {
    iAsynchronousTaskTimer->Cancel();
    }

void CSmileyImage::StartLoadAsynchronousL(TInt aDelayMicroSeconds)
    {
    StopAsynchronousTaskTimer();
    iAsynchronousTaskTimer->Start(aDelayMicroSeconds, 1, TCallBack(StartLoadAsynchronousCallBackL,this));
    }

TInt CSmileyImage::StartLoadAsynchronousCallBackL(TAny* aPtr)
    {
    CSmileyImage* self = (CSmileyImage*)aPtr;
    self->StopAsynchronousTaskTimer();
    self->DoLoadL();
    return KErrNone;
    }

void CSmileyImage::StopAnimationAsynchronousL(TInt aDelayMicroSeconds)
    {
    StopAsynchronousTaskTimer();
    iAsynchronousTaskTimer->Start(aDelayMicroSeconds, 1, TCallBack(StopAnimationAsynchronousCallBackL,this));
    }

TInt CSmileyImage::StopAnimationAsynchronousCallBackL(TAny* aPtr)
    {
    CSmileyImage* self = (CSmileyImage*)aPtr;
    self->StopAsynchronousTaskTimer();
    self->DoHandleEndedL();
    return KErrNone;
    }


// end of file

