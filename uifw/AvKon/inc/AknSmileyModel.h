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
#include <AknsItemID.h>
#include "AknSmileyUtils.h"
#include "AknSmileyImage.h"


// CLASS DECLARATION


////////////////////////////////////////////////////////////////////

const TInt KSmileyNameLength = 8;
typedef TBuf<KSmileyNameLength> TSmileyText;
typedef RArray<TSmileyText> RSmileyTextArray;
typedef RArray<TChar> RSmileyCodeArray;

NONSHARABLE_CLASS(TSmileyIconInfo)
    {
public:
    TSmileyIconInfo();
    TSmileyIconInfo(const TSmileyIconInfo& aInfo);
    void Reset();
    
    TInt iIndex;
    TAknsItemID iSkinItemID;        // from skin
    TInt iDefaultStillImageID;      // from mif
    TInt iDefaultAnimationImageID;  // from mif
    };

////////////////////////////////////////////////////////////////////

class CSmileyIcon : public CAknSmileyIcon, public MSmileyImageObserver
    {
public:
    static CSmileyIcon* NewL(const TSmileyIconInfo& aInfo, MAknSmileyObserver* aObserver);
    virtual ~CSmileyIcon();

private:
    CSmileyIcon(MAknSmileyObserver* aObserver);
    void ConstructL(const TSmileyIconInfo& aInfo);

public: // from AknSmileyIcon
    virtual const CFbsBitmap* Image() const;
    virtual const CFbsBitmap* Mask() const;
    virtual TBool ReadyToDraw() const;
    virtual void SetSize(const TSize& aSize);
    virtual const TSize& Size() const;
    virtual void PlayAnimationL(TInt aRepeat=0, TInt aDelay=0);
    virtual void StopAnimation();

private: // from MSmileyImageObserver
    virtual void BitmapChanged(CSmileyImage* aSmileyImage, CFbsBitmap* aBitmap);
    
public:
    TInt Index() const;
    void LoadStillImageL(TInt aDelay=0);
    TBool StillImageIsReadyToDraw() const;
    TBool AnimationImageIsReadyToDraw() const;

    void AddVariant(const TDesC& aText, TChar aBaseCode);
    TInt VariantCount() const;
    const TDesC& Text(TInt aVariant=0) const;
    TChar Code(TInt aVariant=0) const;

private:
    MAknSmileyObserver*     iSmileyIconObserver;
    TInt                    iIndex;
    CSmileyImage*           iStillImage;
    CSmileyImage*           iAnimationImage;
    RSmileyTextArray        iTextArray;
    RSmileyCodeArray        iCodeArray;
    };

typedef RArray<CSmileyIcon*> RSmileyIconPtrArray;
NONSHARABLE_CLASS(TSmileyCodeIndex)
    {
public:
    TSmileyCodeIndex(CSmileyIcon* aSmileyIcon, TInt aVariant=0) : iSmileyIcon(aSmileyIcon), iVariant(aVariant) {}
    CSmileyIcon* Smiley() const                                 { return iSmileyIcon; }
    const TDesC& Text() const                                   { return iSmileyIcon->Text(iVariant); }
private:
    CSmileyIcon*    iSmileyIcon;
    TInt            iVariant;
    };
typedef RArray<TSmileyCodeIndex> RSmileyCodeIndexArray;


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
    RSmileyIconPtrArray     iLoadingTaskArray;
    
    };

////////////////////////////////////////////////////////////////////

class CSmileyTextTreeNode;

class CSmileyModel : public CBase, public MAknSmileyObserver
    {
public:
    CSmileyModel(MAknSmileyObserver* aObserver);
    virtual ~CSmileyModel();

public:
    void LoadResourceL();
    void ReleaseResource();

public:
    TInt ConvertCodesToTextL(TDes& aText);
    TInt ConvertTextToCodesL(TDes& aText);
    const TDesC& Text(TChar aCode) const;
    TBool IsSmiley(TChar aCode) const;
    
public:
    void SetSize(const TSize& aSize);
    void SetSizeByFont(const CFont* aFont);
    
public:
    void DrawText(CWindowGc& aGc, const TDesC& aText, const CFont* aFont, const TPoint& aPosition) const;
    void DrawText(CWindowGc& aGc, const TDesC& aText, const TAknLayoutText& aLayout, TBool aUseLogicalToVisualConversion=EFalse) const;
    void DrawText(CWindowGc& aGc, const TDesC& aText, const CFont* aFont, const TRect& aBox, TInt aBaselineOffset, 
                  CGraphicsContext::TTextAlign aAlignment=CGraphicsContext::ELeft, TInt aLeftMargin=0) const;

private:
    void DrawText(CWindowGc& aGc, const TDesC& aText, const CFont* aFont, const TRect& aBox, const TPoint& aOffset) const;
    
public:
    TInt Count() const;
    CAknSmileyIcon* Smiley(TChar aCode) const;
    CAknSmileyIcon* operator[](TInt aIndex) const;

private: // from MSmileyIconObserver
    virtual void SmileyStillImageLoaded(CAknSmileyIcon* aSmileyIcon);
    virtual void SmileyAnimationChanged(CAknSmileyIcon* aSmileyIcon);

public: // for smiley picker
    CAknSmileyIcon* SwitchToSmileyIcon() const;
    CAknSmileyIcon* SwitchToSctIcon() const;
    TChar SwitchToSmileyCode() const;
    TChar SwitchToSctCode() const;

    TChar SmileyCode(TInt aIndex, TInt aVariant=0) const;
    TChar SmileyCode(const CAknSmileyIcon* aSmileyIcon) const;

    void LoadStillImagesL(const TDesC& aText);
    void PlayAnimationL(const TDesC& aText, TInt aRepeat=0, TInt aDelay=0);
    void StopAnimation(const TDesC& aText);
    
private:
    void LoadStillImageL(TChar aChar);
    void PlayAnimationL(TChar aChar, TInt aRepeat=0, TInt aDelay=0);
    void StopAnimation(TChar aChar);

private:
    const TDesC& Text(TInt aIndex, TInt aVariant=0) const;
    TInt ArrayCount() const;

private:
    MAknSmileyObserver*         iSmileyIconObserver;
    CSmileyTnumbnailAsynLoader  iSmileyLoader;
    RSmileyIconPtrArray         iSmileyIconArray;
    RSmileyCodeIndexArray       iSmileyCodeIndexArray;
    
    CSmileyTextTreeNode*        iTextSearchTree;
    TBuf<1024*2>                iConvertBuffer;
    
    };

#endif // AKNSMILEYMODEL_H
