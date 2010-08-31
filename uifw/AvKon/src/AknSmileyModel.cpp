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


#include <barsread.h>
#include <AknUtils.h>
#include <aknlayoutscalable_avkon.cdl.h>

#include <centralrepository.h>
#include <AvkonInternalCRKeys.h>

#include <smiley.rsg>
#include <smiley.mbg>

#include "AknSmileyModel.h"
#include "AknSmileyImage.h"


///////////////////////////////////////////////////////////////////////////////////////////////
// TSmileyIconInfo
///////////////////////////////////////////////////////////////////////////////////////////////

TSmileyIconInfo::TSmileyIconInfo()
    {
    Reset();
    }

TSmileyIconInfo::TSmileyIconInfo(const TSmileyIconInfo& aInfo) : 
iName(aInfo.iName), 
iId(aInfo.iId), 
iSkinItemID(aInfo.iSkinItemID), 
iDefaultThumbnailID(aInfo.iDefaultThumbnailID), 
iDefaultAnimationID(aInfo.iDefaultAnimationID)
    {
    }

void TSmileyIconInfo::Reset()
    {
    iName.Zero();
    iId = 0;
    iSkinItemID.Set(0, 0);
    iDefaultThumbnailID = 0;
    iDefaultAnimationID = 0;
    }



///////////////////////////////////////////////////////////////////////////////////////////////
// CSmileyIcon
///////////////////////////////////////////////////////////////////////////////////////////////

CSmileyIcon* CSmileyIcon::NewL(const TSmileyIconInfo& aInfo, MSmileyIconObserver* aObserver)
    {
    CSmileyIcon* self = new (ELeave) CSmileyIcon(aInfo, aObserver);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(); // self;
    return self;
    }

void CSmileyIcon::ConstructL()
    {
    iThumbnailImage = CSmileyImage::NewL(iInfo.iSkinItemID, iInfo.iDefaultThumbnailID, FALSE, this);
    
    if(iInfo.iSkinItemID.iMinor==0 && iInfo.iDefaultAnimationID>0)
        {
        iAnimationImage = CSmileyImage::NewL(iInfo.iSkinItemID, iInfo.iDefaultAnimationID, TRUE, this);
        }
    }

CSmileyIcon::CSmileyIcon(const TSmileyIconInfo& aInfo, MSmileyIconObserver* aObserver) : 
iInfo(aInfo), iSmileyIconObserver(aObserver)
    {
    }

CSmileyIcon::~CSmileyIcon()
    {
    delete iThumbnailImage;
    delete iAnimationImage;
    }

TBool CSmileyIcon::ReadyToDraw() const
    {
    TBool thumbnailCanDraw = iThumbnailImage->ReadyToDraw();
    TBool animationCanDraw = iAnimationImage ? iAnimationImage->ReadyToDraw() : FALSE;
    
    return (thumbnailCanDraw || animationCanDraw);
    }

const CFbsBitmap* CSmileyIcon::Image() const
    {
    if(ShouldShowAnimation())
        {
        return iAnimationImage->Image();
        }
    else
        {
        return iThumbnailImage->Image();
        }
    }

const CFbsBitmap* CSmileyIcon::Mask() const
    {
    if(ShouldShowAnimation())
        {
        return iAnimationImage->Mask();
        }
    else
        {
        return iThumbnailImage->Mask();
        }
    }

void CSmileyIcon::LoadThumbnailL()
    {
    iThumbnailImage->LoadL();
    }

TBool CSmileyIcon::ThumbnailReady() const
    {
    return iThumbnailImage->ReadyToDraw();
    }

void CSmileyIcon::PlayAnimationL(TInt aRepeat, TInt aDelay)
    {
    if(iAnimationImage)
        {
        iAnimationImage->LoadL(aRepeat, aDelay);
        }
    }

void CSmileyIcon::StopAnimation()
    {
    if(iAnimationImage)
        {
        iAnimationImage->Release();
        }
    }

void CSmileyIcon::SetSize(const TSize& aSize)
    {
    iThumbnailImage->SetSize(aSize);
    
    if(iAnimationImage)
        {
        iAnimationImage->SetSize(aSize);
        }
    }

const TSize& CSmileyIcon::Size() const
    {
    return iThumbnailImage->Size();
    }

void CSmileyIcon::BitmapChanged(CSmileyImage* aSmileyImage, CFbsBitmap* /*aBitmap*/)
    {
    if(aSmileyImage == iThumbnailImage)
        {
        if(iSmileyIconObserver) iSmileyIconObserver->ThumbnailLoaded(this);
        }
    else
        {
        if(iSmileyIconObserver) iSmileyIconObserver->AnimationChanged(this);
        }
    }

TBool CSmileyIcon::ShouldShowAnimation() const
    {
    return (iAnimationImage && iAnimationImage->ReadyToDraw());
    }



///////////////////////////////////////////////////////////////////////////////////////////////
// CSmileyTnumbnailAsynLoader
///////////////////////////////////////////////////////////////////////////////////////////////

CSmileyTnumbnailAsynLoader::CSmileyTnumbnailAsynLoader()
    {
    
    }

CSmileyTnumbnailAsynLoader::~CSmileyTnumbnailAsynLoader()
    {
    iTaskArray.Close();
    }

void CSmileyTnumbnailAsynLoader::AddTaskL(CSmileyIcon* aSmileyIcon)
    {
    if(aSmileyIcon)
        {
        iTaskArray.Append(aSmileyIcon);
        if(!iIsLoading)
            {
            DoNextTaskL();
            }
        }
    }

void CSmileyTnumbnailAsynLoader::DiscardAll()
    {
    iTaskArray.Reset();
    }

TInt CSmileyTnumbnailAsynLoader::TaskCount() const
    {
    return iTaskArray.Count();
    }

void CSmileyTnumbnailAsynLoader::DoNextTaskL()
    {
    TInt count = TaskCount();
    if(count > 0)
        {
        CSmileyIcon* icon = iTaskArray[0];
        iTaskArray.Remove(0);
        
        if(icon->ThumbnailReady())
            {
            DoNextTaskL();
            }
        else
            {
            icon->LoadThumbnailL();
            iIsLoading = TRUE;
            }
        }
    else
        {
        iIsLoading = FALSE;
        }
    }



///////////////////////////////////////////////////////////////////////////////////////////////
// CSmileyModel
///////////////////////////////////////////////////////////////////////////////////////////////

CSmileyModel::CSmileyModel(MSmileyIconObserver* aObserver) : iSmileyIconObserver(aObserver)
    {
    }

CSmileyModel::~CSmileyModel()
    {
    ReleaseResource();
    
    iSmileyIconArray.Close();
    }

void CSmileyModel::LoadResourceL()
    {
    if(Count() > 0) return;
    
    // append sct & smiley switch icon
        {
        TSmileyIconInfo info;
        info.iSkinItemID = KAknsIIDQgnIndiSwitchSmiley2;
        info.iDefaultThumbnailID = EMbmSmileyQgn_indi_switch_smiley2;
        iSmileyIconArray.Append(CSmileyIcon::NewL(info, this));
        
        info.iSkinItemID = KAknsIIDQgnIndiSwitchSct2;
        info.iDefaultThumbnailID = EMbmSmileyQgn_indi_switch_sct2;
        iSmileyIconArray.Append(CSmileyIcon::NewL(info, this));
        }

    // append image resourece
    TResourceReader reader;
    TFileName smileyRscName;
    SmileyUtils::GetCustomizableResPath(smileyRscName, KSmileyRsc);
    TInt offset = CCoeEnv::Static()->AddResourceFileL(smileyRscName);
    CCoeEnv::Static()->CreateResourceReaderLC(reader, R_SMILEY_ICONS_INFO);

    TInt count(reader.ReadInt16());
    for(TInt id(1); id<=count; id++)
        {
        TSmileyIconInfo info;
        
        info.iId = id; // id
        
        TBool isAnimation = (reader.ReadInt16() == 1);
        TInt16 code = reader.ReadInt16();
        TInt bmpId1 = reader.ReadInt32();
        TInt maskId1 = reader.ReadInt32();
        TInt bmpId2 = reader.ReadInt32();
        TInt maskId2 = reader.ReadInt32();
        
        if(bmpId2 > 0)
            {
            info.iDefaultThumbnailID = bmpId2;
            info.iDefaultAnimationID = bmpId1;
            }
        else
            {
            info.iDefaultThumbnailID = bmpId1;
            info.iDefaultAnimationID = 0;
            }

        TBuf<64> smileyName = reader.ReadTPtrC(); // strings
        TInt pos = smileyName.Find(_L(" "));
        if(pos > 0) smileyName.SetLength(pos);
        info.iName = smileyName;

        iSmileyIconArray.Append(CSmileyIcon::NewL(info, this));
        }
    
    CCoeEnv::Static()->DeleteResourceFile(offset);
    CleanupStack::PopAndDestroy(); // reader

    }

void CSmileyModel::ReleaseResource()
    {
    // reset array
    for(TInt i(0); i<Count(); i++)
        {
        delete iSmileyIconArray[i];
        iSmileyIconArray[i] = NULL;
        }
    iSmileyIconArray.Reset();
    
    // reset task loader
    iSmileyThumbnailLoader.DiscardAll();
    }

void CSmileyModel::LoadThumbnailAsyn(TInt aIndex)
    {
    TRAP_IGNORE(iSmileyThumbnailLoader.AddTaskL((*this)[aIndex]));
    }

void CSmileyModel::SetSize(const TSize& aSize)
    {
    for(TInt i(0); i<Count(); i++)
        {
        iSmileyIconArray[i]->SetSize(aSize);
        }
    }

CSmileyIcon* CSmileyModel::operator[](TInt aIndex) const
    {
    if(aIndex>=0 && aIndex<Count())
        {
        return iSmileyIconArray[aIndex];
        }
    else
        {
        return NULL;
        }
    }

TInt CSmileyModel::Count() const
    {
    return iSmileyIconArray.Count();
    }

void CSmileyModel::ThumbnailLoaded(CSmileyIcon* aSmileyIcon)
    {
    TRAP_IGNORE(iSmileyThumbnailLoader.DoNextTaskL());

    if(iSmileyIconObserver) iSmileyIconObserver->ThumbnailLoaded(aSmileyIcon);
    }

void CSmileyModel::AnimationChanged(CSmileyIcon* aSmileyIcon)
    {
    if(iSmileyIconObserver) iSmileyIconObserver->AnimationChanged(aSmileyIcon);
    }


// end of file

