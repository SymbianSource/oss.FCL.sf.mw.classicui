/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef __AKNSCIND_H
#define __AKNSCIND_H

#ifndef __AKNSCBUT_H
#include <aknscbut.h>
#endif

// CLASS DEFINITIONS
class CEikImage;
class CGulIcon;
/**
CAknScrollIndicator

This class implements the bitmap drawing routines and indicating functionality of Avkon's 
up and down scrolling indicator.

This is class is used by CAknScrollbutton.
*/

NONSHARABLE_CLASS(CAknScrollIndicator) : public CCoeControl
	{			
public:
	static CAknScrollIndicator* NewL(CAknScrollButton::TType aType);
	static CAknScrollIndicator* NewL(CAknScrollButton::TType aType, CAknScrollButton::TTypeOfScrollBar aTypeOfScrollBar);
	virtual ~CAknScrollIndicator(); 

public: // new functions
	void DrawScrollIndicator(const TRect& aRect);
	void SetPosition(const TInt aFocusPosition, const TInt aScrollSpan);
	void SetWindowOwning( const TBool aBool );
	
private:
	CAknScrollIndicator(CAknScrollButton::TType aType);
	void ConstructL();
	void ConstructL(CAknScrollButton::TTypeOfScrollBar aTypeOfScrollBar);

private:
	CEikImage* iBitmap;
    TInt iFocusPosition;
	TInt iScrollSpan;
	CAknScrollButton::TType iType;
    CFbsBitmap* iColorBitmap;
    CFbsBitGc* iColorBmpGc;
    CFbsBitmapDevice* iColorBmpDev;
	//off-screen bitmap for masking
    CFbsBitmap* iMaskBitmap;
    CFbsBitGc* iMaskBmpGc;
    CFbsBitmapDevice* iMaskBmpDev;
    CAknScrollButton::TTypeOfScrollBar iTypeOfScrollBar;
    CGulIcon* iIcon;
    TBool iIsWindowOwningScrollBar;
	};

#endif

