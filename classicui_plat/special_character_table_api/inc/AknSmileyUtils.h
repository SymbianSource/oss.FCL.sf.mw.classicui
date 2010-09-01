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
* Description:  AVKON smiley utils.
*
*/




#ifndef AKNSMILEYUTILS_H
#define AKNSMILEYUTILS_H

// INCLUDES
#include <AknUtils.h>

// CLASS DECLARATION


////////////////////////////////////////////////////////////////////

class CAknSmileyIcon : public CBase
    {
protected:
    CAknSmileyIcon();

protected:
    virtual ~CAknSmileyIcon();

public:
    virtual const CFbsBitmap* Image() const;
    virtual const CFbsBitmap* Mask() const;
    virtual TBool ReadyToDraw() const;
    virtual const TSize& Size() const;
    virtual void PlayAnimationL(TInt aRepeat=0, TInt aDelay=0);
    virtual void StopAnimation();
    };

////////////////////////////////////////////////////////////////////

class MAknSmileyObserver
    {
public:
    virtual void SmileyStillImageLoaded(CAknSmileyIcon* aSmileyIcon)=0;
    virtual void SmileyAnimationChanged(CAknSmileyIcon* aSmileyIcon)=0;
    };

////////////////////////////////////////////////////////////////////

class CAknSmileyManager : public CBase
    {
public:
    IMPORT_C static CAknSmileyManager* NewL(MAknSmileyObserver* aObserver);
    IMPORT_C ~CAknSmileyManager();

private:
    CAknSmileyManager();
    void ConstructL(MAknSmileyObserver* aObserver);

public:
    IMPORT_C TInt ConvertCodesToTextL(TDes& aText);
    IMPORT_C TInt ConvertTextToCodesL(TDes& aText);
    IMPORT_C const TDesC& Text(TChar aCode) const;
    IMPORT_C TBool IsSmiley(TChar aCode) const;

public:
    IMPORT_C void SetSize(const TSize& aSize);
    IMPORT_C void SetSizeByFont(const CFont* aFont);
    
public:
    IMPORT_C void DrawText(CWindowGc& aGc, const TDesC& aText, const CFont* aFont, const TPoint& aPosition) const;
    IMPORT_C void DrawText(CWindowGc& aGc, const TDesC& aText, const TAknLayoutText& aLayout, TBool aUseLogicalToVisualConversion=EFalse) const;
    IMPORT_C void DrawText(CWindowGc& aGc, const TDesC& aText, const CFont* aFont, const TRect& aBox, TInt aBaselineOffset, 
                           CGraphicsContext::TTextAlign aAlignment=CGraphicsContext::ELeft, TInt aLeftMargin=0) const;

public:
    IMPORT_C TInt Count() const;
    IMPORT_C CAknSmileyIcon* Smiley(TChar aCode) const;
    IMPORT_C CAknSmileyIcon* operator[](TInt aIndex) const;
    
public:
    class CExtension;
    CExtension* iExtension;
    
    };

#endif // AKNSMILEYUTILS_H
