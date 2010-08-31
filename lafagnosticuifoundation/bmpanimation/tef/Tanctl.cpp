// Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

/**
 @file
 @test
 @internalComponent - Internal Symbian test code 
*/

#include <barsread.h>
#include <eikenv.h>
#include <eikappui.h>
#include <eikapp.h>
#include <fbs.h>
#include <bmpancli.h>
#include "Tanctl.h"


void CAnimateFramesCtl::Panic(TEikAnimationPanic aPanic)
	{
	_LIT(KPanicCat,"TBMPANIM-Animation");
	User::Panic(KPanicCat, aPanic);
	}

CAnimateFramesCtl* CAnimateFramesCtl::NewL()
	{ // static
	CAnimateFramesCtl* self=new(ELeave) CAnimateFramesCtl();
	CleanupStack::PushL(self);
	self->BaseConstructL();
	CleanupStack::Pop();
	return self;
	}

CAnimateFramesCtl::CAnimateFramesCtl() :
	iAnimDll(iEikonEnv->WsSession()),
	iFlags(EWaitForRedrawing)
	{
	}

CAnimateFramesCtl::~CAnimateFramesCtl()
	{
	delete iAnimation;
	delete iBitmapAnimData;
	delete iStartAnimationIdler;
	iAnimDll.Close();
	}

//
//
void CAnimateFramesCtl::BaseConstructL()
	{
	iBitmapAnimData = CBitmapAnimClientData::NewL();
	iAnimation = new (ELeave) RBitmapAnim(iAnimDll);
	_LIT(DllName, "BMPANSRV.DLL");
	User::LeaveIfError(iAnimDll.Load(DllName));
	}

// Creates a resource reader from the animation aResourceId
void CAnimateFramesCtl::StaticConstructL(TInt aResourceId)
    {
    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC(reader,aResourceId);
    ConstructFromResourceL(reader);
	CleanupStack::PopAndDestroy();
    }

//
// 
void CAnimateFramesCtl::ConstructFromResourceL(TResourceReader& aReader)
	{
	iBitmapAnimData->SetFrameInterval(aReader.ReadInt16());
	iBitmapAnimData->SetPlayMode((CBitmapAnimClientData::TPlayMode)aReader.ReadInt16());
	iBitmapAnimData->SetFlash(aReader.ReadInt8());
	TFileName ptr(aReader.ReadTPtrC());	// filename
    if (!ptr.Length())
		ptr = KTBmpAnimMBMFilePath;//vm iEikonEnv->EikAppUi()->Application()->BitmapStoreName();
// Start reading the data frames
    TInt listFrameLink=aReader.ReadInt32();
	if (listFrameLink)
		{
		TResourceReader framesReader;
		iCoeEnv->CreateResourceReaderLC(framesReader, listFrameLink);
		const TInt count=framesReader.ReadInt16();
		CBitmapFrameData* frameData = NULL;
		for (TInt ii=0;ii<count;++ii)
			{
			//read the frame data from resource	
			frameData = ReadFrameDataFromResourceL(framesReader, ptr);
			CleanupStack::PushL(frameData);
			iBitmapAnimData->AppendFrameL(frameData);
			CleanupStack::Pop(); // frameData
			}
		CleanupStack::PopAndDestroy();
		}
    TInt backgroundLink=aReader.ReadInt32();
	if (backgroundLink > 0)
		{
		TResourceReader backgroundReader;
		iCoeEnv->CreateResourceReaderLC(backgroundReader, backgroundLink);
		//read the frame data from resource
		CBitmapFrameData* backgroundData = ReadFrameDataFromResourceL(backgroundReader, ptr);
		CleanupStack::PushL(backgroundData);
		iBitmapAnimData->SetBackgroundFrame(backgroundData);
		CleanupStack::Pop(); // backgroundData
		CleanupStack::PopAndDestroy(); // backgroundReader
		}
	}


//
//
CBitmapFrameData* CAnimateFramesCtl::ReadFrameDataFromResourceL(TResourceReader& aFramesReader, const TDesC& aFileName)
	{
	CBitmapFrameData* frameData = CBitmapFrameData::NewL();
	CleanupStack::PushL(frameData);
	frameData->SetInterval(aFramesReader.ReadInt16());
	TPoint position;
	position.iX = aFramesReader.ReadInt16();
	position.iY = aFramesReader.ReadInt16();
	frameData->SetPosition(position);
	const TInt bmpId = aFramesReader.ReadInt16();
	const TInt maskId = aFramesReader.ReadInt16();
	if (bmpId >= 0)
		{
		CFbsBitmap* bitmap = iEikonEnv->CreateBitmapL(aFileName, bmpId);
		frameData->SetBitmap(bitmap);
		if (maskId >= 0)
			{
			CFbsBitmap* mask = iEikonEnv->CreateBitmapL(aFileName, maskId);
			frameData->SetMask(mask);
			}
		}
	CleanupStack::Pop();
	return frameData;
	}

//
//
void CAnimateFramesCtl::CancelAnimationL()
	{
	__ASSERT_ALWAYS(iAnimation, Panic(EEikPanicAnimationNoRAnimation));
	if (IsInitialisationComnpleted())
		iAnimation->StopL();
	}

//
//
void CAnimateFramesCtl::CompleteAnimationInitialisationL()
	{
	__ASSERT_ALWAYS(iAnimation, Panic(EEikPanicAnimationNoRAnimation));
	__ASSERT_ALWAYS(SetAnimationWindowL(), Panic(EEikPanicAnimationNoWindow));
	iAnimation->SetBitmapAnimDataL(*iBitmapAnimData);
	iAnimation->SetPositionL(iPosition);
	iFlags |= EInitialisationCompleted;
	}

//
//
TSize CAnimateFramesCtl::MinimumSize()
	{
	return iBitmapAnimData->Size();
	}

//
//
void CAnimateFramesCtl::PositionChanged()
	{
	if ( (iAnimation) && IsInitialisationComnpleted() )
		iAnimation->SetPositionL(iPosition);
	}

//
//
TBool CAnimateFramesCtl::SetAnimationWindowL()
	{
	RWindow* window = &Window();
	if (window)
		{	
		iAnimation->ConstructL(*window);
		return ETrue;
		}
	return EFalse;
	}

void CAnimateFramesCtl::SetAnimationCtlWindowL(CCoeControl* aParent)
	{
	if (aParent)
		SetContainerWindowL(*aParent);
	else
		CreateWindowL();
	}

//
void CAnimateFramesCtl::SetFrameIndexL(TInt aIndex)
	{
	if (IsInitialisationComnpleted())
		iAnimation->DisplayFrameL(aIndex);
	}

//
void CAnimateFramesCtl::SetFrameIntervalL(TInt aInterval)
	{
	if (IsInitialisationComnpleted())
		iAnimation->SetFrameIntervalL(aInterval);
	}
//
//
void CAnimateFramesCtl::SizeChanged()
	{
	if ( (iAnimation) && IsInitialisationComnpleted() )
		iAnimation->SetPositionL(iPosition);
	}

//
//
void CAnimateFramesCtl::StartAnimationL()
	{
	if (iFlags&EWaitForRedrawing)
		{
		CreateAndStartIdlerL();
		iFlags &= ~EWaitForRedrawing;
		}
	else
		{
		if (!IsInitialisationComnpleted())
			CompleteAnimationInitialisationL();
		iAnimation->StartL();
		}
	}

void CAnimateFramesCtl::SetBitmapAnimationDataL()
	{
	}

void CAnimateFramesCtl::CreateAndStartIdlerL()
	{
	if (!iStartAnimationIdler)
		iStartAnimationIdler = CBitmapAnimIdler::NewL();
	iStartAnimationIdler->Cancel();
	iStartAnimationIdler->Start(TCallBack(StartAnimationCallBackL,this));
	}

TInt CAnimateFramesCtl::StartAnimationCallBackL(TAny* aThis)
	{ // static
	CAnimateFramesCtl* self=(CAnimateFramesCtl*)aThis;
	self->StartAnimationL();
	return(EFalse); // single shot callback
	}


// Idle class

CBitmapAnimIdler* CBitmapAnimIdler::NewL()
	{
	CBitmapAnimIdler* self=new(ELeave) CBitmapAnimIdler;
	CActiveScheduler::Add(self);
	return(self);
	}


