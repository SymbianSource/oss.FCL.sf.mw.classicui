/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
*     Edwin's custom drawer for external use & derivation
*
*
*/


#ifndef     __AKNEDWINCUSTOMDRAWPRIVATE_H__
#define     __AKNEDWINCUSTOMDRAWPRIVATE_H__

#include <lafmain.h>
#include "aknedwincustomdrawbase.h"

class CTextView;
class CTextLayout;
class MAknsControlContext;
class CEikEdwin;


NONSHARABLE_CLASS(CAknEdwinCustomDrawPrivate) : public CAknEdwinCustomDrawBase
	{
public:
	/**
    * Two phase constructor. This can be used when TextView is not present yet
    */
    static CAknEdwinCustomDrawPrivate* NewL(const MLafEnv& aEnv,const CEikEdwin& aEdwin);

    /**
    * Two phase constructor. This should be used when TextView is present
    */
	static CAknEdwinCustomDrawPrivate* NewL(const MLafEnv& aEnv,const CEikEdwin& aEdwin, CTextView* aTextView, CWindowGc* aSystemGc);

    /**
    * Destructor
    */
    virtual ~CAknEdwinCustomDrawPrivate();

public: // from MFormCustomDraw
    /**
    * Draw a chunk of text. Documented in parent class
    */
	void DrawText(const TParam& aParam,const TLineInfo& aLineInfo,const TCharFormat& aFormat,
								   const TDesC& aText,const TPoint& aTextOrigin,TInt aExtraPixels) const;
	/**
    * Draw a section of background according to TParam structure and background color
    * aDrawn must return the rectangle successfuly drawn.
    * Documented in parent class
    */
    void DrawBackground(const TParam& aParam,const TRgb& aBackground,TRect& aDrawn) const;

    /**
    * Draw background lines.
    * Documented in parent class
    */
	void DrawLineGraphics(const TParam& aParam,const TLineInfo& aLineInfo) const;

    TRgb SystemColor(TUint aColorIndex,TRgb aDefaultColor) const;


private:
  	/**
    * Constructor to use if there is no iTextView yet
    */
    CAknEdwinCustomDrawPrivate(const MLafEnv& aEnv,const CEikEdwin& aEdwin);

    /**
    * This constructor is to be used if iTextView exists. It allows an optimized draw
    * to be performed.
    */
	CAknEdwinCustomDrawPrivate(const MLafEnv& aEnv,const CEikEdwin& aEdwin, CTextView* aTextView, CWindowGc* aSystemGc );

	};



#endif
