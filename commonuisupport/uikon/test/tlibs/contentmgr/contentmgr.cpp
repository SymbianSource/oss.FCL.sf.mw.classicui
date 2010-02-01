// Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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
 @internalComponent - Internal Symbian test code 
*/

#include "contentmgr.h"
#include <apmstd.h>
#include <mdaaudiosampleplayer.h>
#include <apparc.h>
#include <apgcli.h>

GLDEF_C TInt E32Dll(
					)
	{
	return(KErrNone);
	}

//
// class CTestPictureAudio
//

class CTestPictureAudio : public CPicture, public MMdaAudioPlayerCallback
	{
public:
	static CTestPictureAudio* NewL(RFs& aFs,const TDesC& aFileName);
	static CTestPictureAudio* NewL(RFs& aFs,const CStreamStore& aStore,TStreamId aStreamId);
	~CTestPictureAudio();
	//
	void PlayL();
private: // from CPicture
	void Draw(CGraphicsContext& aGc,const TPoint& aTopLeft,const TRect& aClipRect,MGraphicsDeviceMap* aMap) const;
	void ExternalizeL(RWriteStream& aStream) const;
	void GetOriginalSizeInTwips(TSize& aSize) const;
private: // from MMdaAudioPlayerCallback
	void MapcInitComplete(TInt aError, const TTimeIntervalMicroSeconds& aDuration);
	void MapcPlayComplete(TInt aError);
private:
	CTestPictureAudio(RFs& aFs);
	void ConstructL(const TDesC& aFileName);
	void ConstructL(const CStreamStore& aStore,TStreamId aStreamId);
	void CommonConstructL();
	void RestoreL(const CStreamStore& aStore,TStreamId aStreamId);
	void StopPlay();
private:
	RFs& iFs;
	CFbsBitmap* iBitmap;
	CMdaAudioPlayerUtility* iSoundPlayer;
	HBufC8* iPlayBuf;
	TPtr8 iPtr;
	};

_LIT(KBitmapName,"\\system\\data\\contentmgr.mbm");

CTestPictureAudio* CTestPictureAudio::NewL(RFs& aFs,const TDesC& aFileName)
	{ // static
	CTestPictureAudio* self=new(ELeave) CTestPictureAudio(aFs);
	CleanupStack::PushL(self);
	self->ConstructL(aFileName);
	CleanupStack::Pop(); // self
	return self;
	}

CTestPictureAudio* CTestPictureAudio::NewL(RFs& aFs,const CStreamStore& aStore,TStreamId aStreamId)
	{ // static
	CTestPictureAudio* self=new(ELeave) CTestPictureAudio(aFs);
	CleanupStack::PushL(self);
	self->ConstructL(aStore,aStreamId);
	CleanupStack::Pop(); // self
	return self;
	}

CTestPictureAudio::~CTestPictureAudio()
	{
	StopPlay();
	delete iBitmap;
	delete iPlayBuf;
	}

void CTestPictureAudio::PlayL()
	{
	StopPlay();
	iSoundPlayer=CMdaAudioPlayerUtility::NewDesPlayerL(iPtr,*this);
	}

void CTestPictureAudio::Draw(CGraphicsContext& aGc,const TPoint& aTopLeft,const TRect& aClipRect,
												MGraphicsDeviceMap* /*aMap*/) const
	{
	TSize sizeInPixels=iBitmap->SizeInPixels();
	TRect originalRectInPixels(aTopLeft,sizeInPixels);
	aGc.SetClippingRect(aClipRect);
	aGc.DrawBitmap(originalRectInPixels,iBitmap);
	aGc.CancelClippingRect();
	}

void CTestPictureAudio::ExternalizeL(RWriteStream& aStream) const
	{
	aStream.WriteInt32L(iPtr.Length());
	aStream.WriteL(iPtr);
	}

void CTestPictureAudio::GetOriginalSizeInTwips(TSize& aSize) const
	{
	TSize sizeInPixels=iBitmap->SizeInPixels();
	TInt vert=iBitmap->VerticalPixelsToTwips(sizeInPixels.iHeight);
	TInt horiz=iBitmap->HorizontalPixelsToTwips(sizeInPixels.iWidth);
	aSize=TSize(horiz,vert);
	}

void CTestPictureAudio::MapcInitComplete(TInt aError, const TTimeIntervalMicroSeconds& /*aDuration*/)
	{
	if (aError)
		{
		StopPlay();
		return;;
		}
	iSoundPlayer->Play();
	}

void CTestPictureAudio::MapcPlayComplete(TInt /*aError*/)
	{
	StopPlay();
	}

CTestPictureAudio::CTestPictureAudio(RFs& aFs)
	: iFs(aFs), iPtr(NULL,0)
	{}

LOCAL_C void GetFullPath(TDes& aPath)
	{
	TFileName dllName;
	Dll::FileName(dllName);
	TBuf<2> drive=dllName.Left(2);
	aPath.Insert(0,drive);
	}

void CTestPictureAudio::CommonConstructL()
	{
	TFileName bitmapFile=KBitmapName();
	GetFullPath(bitmapFile);
	iBitmap=new(ELeave) CFbsBitmap;
	User::LeaveIfError(iBitmap->Load(bitmapFile));
	}

void CTestPictureAudio::ConstructL(const TDesC& aFileName)
	{
	CommonConstructL(); // creates bitmap
	RFile file;
	User::LeaveIfError(file.Open(iFs,aFileName,EFileRead));
	CleanupClosePushL(file);
	TInt size;
	User::LeaveIfError(file.Size(size));
	iPlayBuf=HBufC8::NewL(size);
	TPtr8 ptr=iPlayBuf->Des();
	iPtr.Set(ptr);
	User::LeaveIfError(file.Read(iPtr));
	CleanupStack::PopAndDestroy(); // file.Close()
	}

void CTestPictureAudio::ConstructL(const CStreamStore& aStore,TStreamId aStreamId)
	{
	CommonConstructL(); // creates bitmap
	// following is a poor example.  There's no reason for us to waste time restoring the embedded
	// stream yet.  We could wait till its really needed but that requires more faffing with Store
	// than can be justified for some quick example code.
	RestoreL(aStore,aStreamId);
	}

void CTestPictureAudio::RestoreL(const CStreamStore& aStore,TStreamId aStreamId)
	{
	RStoreReadStream stream;
	stream.OpenLC(aStore,aStreamId);
	const TInt len=stream.ReadInt32L();
	iPlayBuf=HBufC8::NewL(len);
	TPtr8 ptr=iPlayBuf->Des();
	stream.ReadL(ptr,len);
	CleanupStack::PopAndDestroy(); // stream
	iPtr.Set(ptr);
	}

void CTestPictureAudio::StopPlay()
	{
	delete iSoundPlayer;
	iSoundPlayer=NULL;
	}

//
// class CTestAudioContent
//

class CTestAudioContent : public CBase
	{
public:
	CStreamStore* iHost;
	TFileName iSourceFile;
	};

//
// class CEikTestContentManager
//

_LIT8(KContentDataTypeAudio,"audio/*");
const TUid KTestContentType={5711};

EXPORT_C CEikTestContentManager* CEikTestContentManager::NewL(RFs& aFs)
	{ // static
	CEikTestContentManager* self=new(ELeave) CEikTestContentManager(aFs);
	return self;
	}

EXPORT_C CEikTestContentManager::~CEikTestContentManager()
	{
	}

EXPORT_C void CEikTestContentManager::GetPictureTypeFromDataL(TUid& aPictureType,CBase*& aData,
															  const TDesC& aFileName,const TDesC8& aSrcData) const
	{
	RApaLsSession ls;
	User::LeaveIfError(ls.Connect());
	CleanupClosePushL(ls);
	TDataRecognitionResult res;
	User::LeaveIfError(ls.RecognizeData(aFileName,aSrcData,res));
	CleanupStack::PopAndDestroy(); // ls
	//
	TUid type=KNullUid;
	if (res.iDataType.Des8().MatchF(KContentDataTypeAudio)==0)
		{
		CTestAudioContent* data=new(ELeave) CTestAudioContent;
		data->iSourceFile=aFileName;
		aData=data;
		type=KTestContentType;
		}
	aPictureType=type;
	}

TBool CEikTestContentManager::SupportsPictureType(TUid aPictureType) const
	{
	return (aPictureType==KTestContentType);
	}

const MPictureFactory* CEikTestContentManager::PictureFactory(TUid aPictureType) const
	{
	if (aPictureType==KTestContentType)
		{
		return this;
		}
	return NULL;
	}

TPictureHeader CEikTestContentManager::InsertL(TUid aPictureType,CBase* aData)
	{
	TPictureHeader header;
	if (aPictureType==KTestContentType)
		{
		CPicture* picture=CTestPictureAudio::NewL(iFs,static_cast<CTestAudioContent*>(aData)->iSourceFile);
		header.iPicture=picture;
		header.iPictureType=aPictureType;
		picture->GetOriginalSizeInTwips(header.iSize);
		}
	return header;
	}

void CEikTestContentManager::EditL(const TPictureHeader& aPictureHeader,TBool /*aReadOnly*/)
	{
	CTestPictureAudio* picture=static_cast<CTestPictureAudio*>(aPictureHeader.iPicture.AsPtr());
	picture->PlayL();
	}

void CEikTestContentManager::NewPictureL(TPictureHeader& aHeader,const CStreamStore& aDeferredPictureStore) const
	{
	if (aHeader.iPictureType!=KTestContentType)
		{
		User::Leave(KErrNotSupported);
		}
	TStreamId id=aHeader.iPicture.AsId();
	CTestPictureAudio* picture=CTestPictureAudio::NewL(iFs,aDeferredPictureStore,id);
	aHeader.iPicture=picture;
	}

CEikTestContentManager::CEikTestContentManager(RFs& aFs)
	: iFs(aFs)
	{}
