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
* Description:  AVKON smiley data model.
*
*/




#ifndef AKNSMILEYMODEL_H
#define AKNSMILEYMODEL_H

// INCLUDES
#include <AknIconObserver.h>

#include "AknSmileyImage.h"


// CLASS DECLARATION


////////////////////////////////////////////////////////////////////

const TInt KSmileyNameLength = 8;

NONSHARABLE_CLASS(TSmileyIconInfo)
    {
public:
    TSmileyIconInfo();
    TSmileyIconInfo(const TSmileyIconInfo& aInfo);
    void Reset();

    TBuf<KSmileyNameLength> iName;
    TInt iId;
    TAknsItemID iSkinItemID;    // from skin
    TInt iDefaultThumbnailID;   // from mif
    TInt iDefaultAnimationID;   // from mif
    };

////////////////////////////////////////////////////////////////////

class CSmileyIcon;

class MSmileyIconObserver
    {
public:
    virtual void ThumbnailLoaded(CSmileyIcon* aSmileyIcon)=0;
    virtual void AnimationChanged(CSmileyIcon* aSmileyIcon)=0;
    };

////////////////////////////////////////////////////////////////////

class CSmileyIcon : public CBase, public MSmileyImageObserver
    {
public:
    static CSmileyIcon* NewL(const TSmileyIconInfo& aInfo, MSmileyIconObserver* aObserver);
    virtual ~CSmileyIcon();

private:
    CSmileyIcon(const TSmileyIconInfo& aInfo, MSmileyIconObserver* aObserver);
    void ConstructL();

public:
    const TDesC& Name() const               { return iInfo.iName; }
    TInt Id() const                         { return iInfo.iId; }

    TBool ReadyToDraw() const;
    const CFbsBitmap* Image() const;
    const CFbsBitmap* Mask() const;

public:
    void LoadThumbnailL();
    TBool ThumbnailReady() const;
    
    void PlayAnimationL(TInt aRepeat, TInt aDelay);
    void StopAnimation();

public:
    void SetSize(const TSize& aSize);
    const TSize& Size() const;

private: // from MSmileyImageObserver
    virtual void BitmapChanged(CSmileyImage* aSmileyImage, CFbsBitmap* aBitmap);

private:
    TBool ShouldShowAnimation() const;

private:
    const TSmileyIconInfo   iInfo;
    MSmileyIconObserver*    iSmileyIconObserver;

    CSmileyImage*           iThumbnailImage;
    CSmileyImage*           iAnimationImage;

    };

typedef RArray<CSmileyIcon*> RSmileyIconPtrArray;


////////////////////////////////////////////////////////////////////

class CSmileyTnumbnailAsynLoader : public CBase
    {
public:
    CSmileyTnumbnailAsynLoader();
    ~CSmileyTnumbnailAsynLoader();

    void AddTaskL(CSmileyIcon* aSmileyIcon);
    void DiscardAll();
    TInt TaskCount() const;
    void DoNextTaskL();

private:
    RSmileyIconPtrArray     iTaskArray;
    TBool                   iIsLoading;
    
    };

////////////////////////////////////////////////////////////////////

class CSmileyModel : public CBase, public MSmileyIconObserver
    {
public:
    CSmileyModel(MSmileyIconObserver* aObserver);
    ~CSmileyModel();

public:
    void LoadResourceL();
    void ReleaseResource();
    void LoadThumbnailAsyn(TInt aIndex);
    void SetSize(const TSize& aSize);

public:
    enum TIconId
        {
        EIconSwitchToSmiley = 0, 
        EIconSwitchToSct,
        EIconSmiley
        };

    CSmileyIcon* operator[](TInt aIndex) const;
    TInt Count() const;

private: // from MSmileyIconObserver
    virtual void ThumbnailLoaded(CSmileyIcon* aSmileyIcon);
    virtual void AnimationChanged(CSmileyIcon* aSmileyIcon);

private:
    MSmileyIconObserver*        iSmileyIconObserver;
    RSmileyIconPtrArray         iSmileyIconArray;
    CSmileyTnumbnailAsynLoader  iSmileyThumbnailLoader;
    
    };

#endif // AKNSMILEYMODEL_H
