/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  smiley utility class
*
*/

#ifndef C_SMILEYDRAWER_H
#define C_SMILEYDRAWER_H

#include <e32base.h>
#include <e32std.h>
#include <coecntrl.h>

class CSmileyModel;
class CFbsBitmap;
class CBitmapContext;
class CFbsBitGc;
class CSmileyImageData;
class CSmileyIcon;
class CEikEdwin;
class CSmileyAsyncDraw;
class CSmileyDrawer;

class MSmileyAnimChecker
    {
public:
    virtual TBool IsOnProgress() const = 0;
    virtual void ResetStatus() = 0;
    virtual void DoOnAnimStoppedL() = 0;
    };

NONSHARABLE_CLASS( TSmileyAnimCheckerWrapper )
    {
public:
    TSmileyAnimCheckerWrapper( MSmileyAnimChecker* aAnimChecker, TInt aMaxCheckTimes );
    TBool IsContainingAnimChecker( const MSmileyAnimChecker* aAnimChecker ) const;
    void CheckAnimProgressL();
    
private: // data
    // not own
    MSmileyAnimChecker* iAnimChecker;
    TInt iCheckTimes;
    TInt iMaxCheckTimes;
    };

/**
 *  class for reading and interpreting infomation stored in CenRep
 *
 *  @lib ?library
 *  @since S60 v5.0
 */

NONSHARABLE_CLASS( CSmileyDrawer ): public CBase
    {  
public:
    static const TInt KDisplayTimes = 2;
    
public:   
// constructor
    CSmileyDrawer( CSmileyModel& aModel, CEikEdwin& aEdwin );    
    ~CSmileyDrawer();

// new functions
    void DrawTextView();

    void SetHighlightColor( TRgb aColor );
    TRgb HighlightColor(){ return iHighlightColor; };
  
    void DrawImageByIconL( CBitmapContext& aGc, CSmileyIcon* aNode );
    void CreateImageByIconL( CSmileyIcon* aIcon );
    void CreateImageL( CSmileyImageData* aImage );
    
    void SetPlayTimes( TInt aPlayTimes ){ iPlayTimes = aPlayTimes; };
    
    void SetVisibleRange( TInt aDocPos, TInt aLength )
        {
        iVisibleStart = aDocPos;
        iVisibleLength = aLength;
        };
    
    void StartAnimTimerL();
    static TInt AnimTimerCallbackL( TAny* aPtr );
    void CheckAnimStatusL();
    void RegisterAnimChecker( MSmileyAnimChecker* aAnimChecker );
    void RemoveAnimChecker( MSmileyAnimChecker* aAnimChecker );
    CEikEdwin& Editor(){ return iEdwin; };
    
private:
    void DrawHighlightBmpL( CBitmapContext& aGc, CFbsBitmap* aBmp, 
        CFbsBitmap* aMask, TPoint& aPt );
    CSmileyImageData* FindImageDataByCode( TText aCode );
    CSmileyImageData* CreateImageDataL( TText aCode );

private: // data
    CSmileyModel& iModel;
    CEikEdwin& iEdwin;
    
    RPointerArray<CSmileyImageData> iImageArray;
    
    TRgb iHighlightColor;
    TInt iPlayTimes;
    TInt iVisibleStart;
    TInt iVisibleLength;
    // own
    CSmileyAsyncDraw* iAsyncDraw;
    // own
    CPeriodic* iPeriodic;
    RArray<TSmileyAnimCheckerWrapper> iAnimArray;
    };

#endif C_SMILEYDRAWER_H
