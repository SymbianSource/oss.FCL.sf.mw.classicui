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

#ifndef C_SMILEYBMPOBSERVER_H
#define C_SMILEYBMPOBSERVER_H

#include <e32base.h>
#include <AknIconObserver.h>
#include "smileydrawer.h"

class CSmileyDrawer;
class CSmileyImageData;
class CSmileyBmpObserver;

NONSHARABLE_CLASS( CSmileyAsyncDraw ): public CActive
    {
public:
    static const TInt KDrawIntervalMicroSec = 200000;
    
    CSmileyAsyncDraw( CSmileyDrawer& aDrawer );
    ~CSmileyAsyncDraw();
    
// new function
    void AddReplayImage( CSmileyImageData* aImage );
    void CreateReplayImageL();
    void RequestAsyncDraw( TBool aForce = EFalse );
    CSmileyDrawer& SmileyDrawer(){ return iDrawer; };
    TBool IsRequestIntervalBigEnough() const;
    
// from CActive
    void DoCancel();
    void RunL();
   
private:
    CSmileyDrawer& iDrawer;
    RArray<CSmileyImageData*> iReplayImageArray;
    TTime iLastRequestTime;
    TBool iEverActivated;
    };

NONSHARABLE_CLASS( CSmileyBmpObserver ): public CBase, public MAknIconObserver,
    public MSmileyAnimChecker
    {	
public:
    CSmileyBmpObserver( CSmileyAsyncDraw& aAsyncDraw );
    ~CSmileyBmpObserver();
    
// new function
    void SetImageData( CSmileyImageData* aImage );
   
// from  MAknIconObserver   
    void BitmapChanged( CFbsBitmap *aBitmap );
    
// from MSmileyAnimChecker
    TBool IsOnProgress() const;
    void ResetStatus();
    void DoOnAnimStoppedL();
    
private:
// new functions
    void ReplayAnimationL();
    void StopAnimation();
    
private: //data
    CSmileyAsyncDraw& iAsyncDraw;
    // not own
    CSmileyImageData* iImage;
    TBool iIsAnimProgress;
    TBool iIsRegisted;
	};

#endif C_SMILEYBMPOBSERVER_H
