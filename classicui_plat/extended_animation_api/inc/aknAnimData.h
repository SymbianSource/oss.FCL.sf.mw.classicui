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
*
*/


// AknAnimData.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Animation Data class


#if !defined(__AKNANIMDATA_H__)
#define __AKNANIMDATA_H__

#include <e32std.h>
#include <gdi.h>

class TResourceReader;



class TAnimLineDrawStep
	{
public:
	inline TPoint StartPoint();
	inline TPoint EndPoint();
public:
	TUint16 iSteps;
	TInt16 iStartX;
	TInt16 iStartY;
	TInt16 iEndX;
	TInt16 iEndY;
	};

class TAnimBlitStep
	{
public:
	TPoint StartPoint();
	TPoint EndPoint();
	TSize Size();
public:
	TUint16 iSteps;
	TInt16 iSrcX;
	TInt16 iSrcY;
	TInt16 iDestX;
	TInt16 iDestY;
	TUint16 iWidth;
	TUint16 iHeight;
	};

class TAnimSlideStep
	{
public:
	TPoint StartPoint();
	TPoint EndPoint();
	TSize Size();
public:
	TUint16 iSteps;
	TInt16 iSrcX;
	TInt16 iSrcY;
	TInt16 iSlideToX;
	TInt16 iSlideToY;
	TInt16 iSlideFromX;
	TInt16 iSlideFromY;
	TUint16 iWidth;
	TUint16 iHeight;
	};

class TAnimWaitStep
	{
public:
	TUint16 iSteps;
	};

class TAnimSetColorStep
	{
public:
	TRgb Color();
public:
	TUint8 iRed;
	TUint8 iGreen;
	TUint8 iBlue;
	};


class TAnimUserStep
	{
public:
	TInt Param1();
	TInt Param2();
	TInt Param3();
	TInt Param4();
	TInt Param5();
	TInt Param6();
	};


union UStepData
	{
	TAnimLineDrawStep iLineDrawStep;
	TAnimBlitStep iBlitStep;
	TAnimSetColorStep iSetColorStep;
	TAnimSlideStep	iSlideStep;
	TAnimWaitStep iWaitStep;
	};

class TAnimStep 
	{

public:
	inline TAnimStep();
	inline TAnimLineDrawStep* LineDrawStep();
	inline TAnimBlitStep* BlitStep();
	inline TAnimSetColorStep* SetColorStep();
	inline TAnimSlideStep* SlideStep();
	inline TAnimWaitStep* WaitStep();
	inline void SetType(TUint8 aType);
	inline TUint8 Type();
private:
	TUint8 iType;
	TUint16 iSteps;
	UStepData iStepData;
	};


class TAnimMultiStep
	{
public:
	inline TAnimMultiStep(TAnimStep aStep);
public:
	TAnimStep iDrawStep;
	TUint16 iSubStep;
	};

class CAknAnimationData : public CArrayFixFlat<TAnimStep>
	{
public:
	IMPORT_C CAknAnimationData();
	IMPORT_C ~CAknAnimationData();
	IMPORT_C void ConstructFromResourceL(TInt aResourceId);
	IMPORT_C void SetScreenSize(TSize aSize);
	IMPORT_C void SetViewBitmap(CFbsBitmap* aViewBitmap);
	IMPORT_C void SetOldBitmap(CFbsBitmap* aOldBitmap);
	IMPORT_C void SetClearOldView();
	IMPORT_C TBool ClearOldView();
	IMPORT_C TBool WaitBetweenSections();
	IMPORT_C void SetWaitForeverAtEnd();
	IMPORT_C TBool WaitForeverAtEnd();
	IMPORT_C TBool DrawNextAnimationStep(CBitmapContext& aGc);
	IMPORT_C TInt Interval();
protected:
	IMPORT_C void ConstructL();
	IMPORT_C virtual TBool DrawUserAnimationStep(CBitmapContext& aGc, TAnimMultiStep& aStep);
	IMPORT_C virtual void ConstructUserAnimationStepL(TAnimStep& aAnimStep, TResourceReader& aReader);
private:
	void ReadAnimStepL(TResourceReader& aReader);
	TBool DrawPendingAnimationSteps(CBitmapContext& aGc);
	TBool ExecutePendingAnimationStep(CBitmapContext& aGc, TAnimMultiStep* aStep);
private:
	TUint16 iFlags;
	CArrayFixFlat<TAnimMultiStep>* iPendingSteps;
	CArrayFixFlat<TUint8>* iDrawStepsPerAnimStep;
protected:
	TSize iScreenSize;
	CFbsBitmap* iViewBitmap;
	CFbsBitmap* iOldBitmap;
	TInt iCurrentDrawStep;
	TInt iCurrentAnimStep;
	TRgb iDrawColor;
	TInt iInterval;
	};




// Inline functions

inline TAnimLineDrawStep* TAnimStep::LineDrawStep()
	{
	return &(iStepData.iLineDrawStep);
	}

inline TAnimBlitStep* TAnimStep::BlitStep()
	{
	return &(iStepData.iBlitStep);
	}

inline TAnimSetColorStep* TAnimStep::SetColorStep()
	{
	return &(iStepData.iSetColorStep);
	}

inline TAnimSlideStep* TAnimStep::SlideStep()
	{
	return &(iStepData.iSlideStep);
	}

inline TAnimWaitStep* TAnimStep::WaitStep()
	{
	return &(iStepData.iWaitStep);
	}


inline void TAnimStep::SetType(TUint8 aType)
	{
	iType = aType;
	}

inline TUint8 TAnimStep::Type()
	{
	return iType;
	}


inline TAnimStep::TAnimStep()
	{
	}


inline TAnimMultiStep::TAnimMultiStep(TAnimStep aStep)
:iDrawStep(aStep), iSubStep(0)
	{
	}


#endif




