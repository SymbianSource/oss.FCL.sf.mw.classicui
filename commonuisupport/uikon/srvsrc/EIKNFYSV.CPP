// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include "EIKNFYSV.H"
#include <barsread.h>
#include <coemain.h>
#include <eikenv.h>
#include <eikmsg.h>
#include <e32uid.h>
#include <e32notif.h>
#include "EIKSRV.PAN"
#include "eiknotapi.h"
#include <bafindf.h>
#include <uiklaf/private/lafenv.h>
#include "EIKDEBUG.H"
#include <uiklaf/private/pluginuid.hrh>
#include "eikscchange.h"

_LIT(KPanicClient_CEikServNotifySession,"Eiksrv Cli(Nfy)");

const TInt KQueued = 1;
const TInt KNullClientId = 0;
const TUid KNonExistentUid = {KNullUidValue}; 

/**
@internalComponent
*/
_LIT8(KEikNotifierPaused,"Eik_Notifier_Paused");

/**
@internalComponent
*/
_LIT8(KEikNotifierResumed,"Eik_Notifier_Resumed");

#include <ecom/publicregistry.h>
#include <uikon.hrh>
static const TUid KUidPluginInterfaceNotifiers = {KUikonUidPluginInterfaceNotifiers};


const TUint KNotifierMessageOpCodeLast = 10;
const TUint KRangeCount = 5;

const TInt KOpCodeRanges[KRangeCount] = 
	{	
	ENotifierNotify,
	ECancelNotifier, 
	EStartNotifierAndGetResponse, 
	EUpdateNotifierAndGetResponse,
	KNotifierMessageOpCodeLast,
	};

const TUint8 KElementsIndex[KRangeCount] =
	{
	CPolicyServer::EAlwaysPass, //Allways passing no capability required      [0-2]
	CPolicyServer::ECustomCheck, //Custom check for the Notifier Client's SID (ECancelNotifier and EUpdateNotifier) [3-4]
	CPolicyServer::EAlwaysPass,	//Allways passing no capability required       [5-8]
	CPolicyServer::ECustomCheck,//Custom check for the Notifier Client's SID  (EUpdateNotifierAndGetResponse)[9-(KNotifierMessageOpCodeLast-1)]
	CPolicyServer::ENotSupported, //Not Supported					 		   [KNotifierMessageOpCodeLast-End]
	};

const CPolicyServer::TPolicy KEikServNotifyServerPolicy =
	{
	CPolicyServer::EAlwaysPass, 
	KRangeCount,
	KOpCodeRanges,
	KElementsIndex, 	
	};

/**
@internalComponent 
*/
NONSHARABLE_CLASS(CDiscoverNewImplementation) : public CActive
	{
public:
	static CDiscoverNewImplementation* NewL(CEikSrvNotifierManager& aManager);
	void Start();
	~CDiscoverNewImplementation();
private:
	CDiscoverNewImplementation(CEikSrvNotifierManager& aManager);
	void ConstructL();
	void RunL();
	void DoCancel();
private:
	CEikSrvNotifierManager& iManager;
	REComSession* iEComSession;
	CActiveScheduler*  iScheduler;
	};

/**
@internalComponent 
*/
NONSHARABLE_CLASS(CPluginTrack) : public CBase
	{
public:
	NONSHARABLE_CLASS(TNotifierInfo)
		{
	public:
		TNotifierInfo(TUid aNotifierPluginUid, TUid aNotifierPluginChannelUid);
	public:
		TUid iNotifierPluginUid;
		TUid iNotifierPluginChannelUid;
		};
public:
	CPluginTrack();
	~CPluginTrack();
public:
	TUid iDllUid;
	TUid iPluginImplementationUid;
	TUid iDtr_key;
	RArray<TNotifierInfo> iNotifierInfo;
	};


//
// class CEikServNotifyServer
//

CEikServNotifyServer::CEikServNotifyServer(TInt aPriority, MEikServNotifyAlert* aAlert)
	: CPolicyServer(aPriority, KEikServNotifyServerPolicy), iAlert(aAlert)
	//
	// private c'tor - initialize using NewL()
	//
	{
	}

EXPORT_C  CEikServNotifyServer::~CEikServNotifyServer()
	{
	SetIsExiting();
	
	if (iAlert)
		iAlert->Release();
	
	if (iInfoMsg)
		iInfoMsg->Release();
		
	iInfoMsgGroupWin.Close();
	delete iManager;
	}

EXPORT_C CEikServNotifyServer* CEikServNotifyServer::NewL(MEikServNotifyAlert* aAlert)
	//
	// static - Create and start the server
	{
	CEikServNotifyServer* server = new (ELeave) CEikServNotifyServer(EActivePriorityIpcEventsHigh, aAlert);
	CleanupStack::PushL(server);
	server->ConstructL();
	CleanupStack::Pop(); // server
	return server;
	}

EXPORT_C void CEikServNotifyServer::StartL()
	{
	CServer2::StartL(__NOTIFIER_NAME);
	}

void CEikServNotifyServer::SetIsExiting()
	{
	iExiting = ETrue;
	}

TBool CEikServNotifyServer::IsExiting() const
	{
	return iExiting;
	}

void CEikServNotifyServer::ConstructL()
	//
	// private second phase construction - initialise using NewL()
	//
	{
	// notifier info print
	CEikonEnv* env = CEikonEnv::Static();
	RWsSession& wsSession = env->WsSession();
	iInfoMsgGroupWin = RWindowGroup(wsSession);
	User::LeaveIfError(iInfoMsgGroupWin.Construct((TUint32)this, EFalse)); // EFalse disables key events
	iInfoMsgGroupWin.SetOrdinalPosition(0, ECoeWinPriorityAlwaysAtFront-1);
	
	iInfoMsg = LafEnv::NewInfoMsgWinL(*env, iInfoMsgGroupWin);
	
	// notifier manager
	iManager = CEikSrvNotifierManager::NewL();
	iManager->RegisterL();
	}

EXPORT_C void CEikServNotifyServer::DisplayNotifier(const TDesC& aTitle,const TDesC& aLabel, const TDesC& aBut1, const TDesC& aBut2, MEikNotifyAlertCompletionObserver* aObserver)
	{
	if(iAlert)
		iAlert->DisplayNotifier(aTitle, aLabel, aBut1, aBut2, aObserver);
	}

EXPORT_C void CEikServNotifyServer::DisplayInfoPrint(const TDesC& aDes)
	{
	if(iInfoMsg)
		iInfoMsg->StartDisplay(aDes, EHRightVTop);
	}

CSession2* CEikServNotifyServer::NewSessionL(const TVersion &aVersion,const RMessage2&) const
	{
	const TVersion version(1,0,0); // !! liaise with RNotify client-side class in E32
	if (!User::QueryVersionSupported(version,aVersion))
		User::Leave(KErrNotSupported);
		
	return CEikServNotifySession::NewL();
	}

CPolicyServer::TCustomResult CEikServNotifyServer::CustomSecurityCheckL(const RMessage2& aMsg, TInt& /*aAction*/, TSecurityInfo& /*aMissing*/)
//aAction is not set because default value to it is already set(CPolicyServer::EFailClient)
//aMissing is not set because it is not needed as we aren't overriding CheckFailedL
	{
	const TUid notifierUid = TUid::Uid(aMsg.Int0());
	const TSecureId clientSid = aMsg.SecureId();

	const TInt count = iAsyncSecureInfoQueue.Count();
	for(int i = 0; i < count; i++)
		{
		if(iAsyncSecureInfoQueue[i].iSecureId == clientSid)
			return CPolicyServer::EPass;
		}
	
	return CPolicyServer::EFail;
	}

//
// class TNotifierMessageInfo
//

TNotifierMessageInfo::TNotifierMessageInfo(const RMessage2& aMessage, CEikServNotifySession& aEikServNotifySession)
 : iMessage(aMessage), iEikServNotifySession(aEikServNotifySession)
	{
	}

//
// class CEikServNotifySession
//

CEikServNotifySession* CEikServNotifySession::NewL()
	{
	CEikServNotifySession* const notifySession = new(ELeave) CEikServNotifySession;
	CleanupStack::PushL(notifySession);
	notifySession->ConstructL();
	CleanupStack::Pop(notifySession);
	return notifySession;
	}

CEikServNotifySession::~CEikServNotifySession()
	{
	const CEikServNotifyServer& server = Server();
	if (!server.IsExiting())
		server.Manager()->HandleClientExit(iClientId);
	
	iServer = NULL;
	delete iEikSrvPendingAlert;
	delete iBuffer;
	}
	
CEikServNotifySession::CEikServNotifySession() : iClientId(reinterpret_cast<TInt>(this))
	{
	}

void CEikServNotifySession::ConstructL()
	{
	iEikSrvPendingAlert = new(ELeave) CEikSrvPendingAlert(*this);
	}

void CEikServNotifySession::ServiceL(const RMessage2 &aMessage)
	//
	// Service requests
	//
	{
	DEBUGPRINT3(_L("CEikServNotifySession::ServiceL(), UID: 0x%X op:%D"),aMessage.Int0(),aMessage.Function());

	TBool completeMessage = ETrue;
	switch (aMessage.Function())
		{
	case ENotifierNotify:
		DisplayAlert(aMessage);
		completeMessage = EFalse; // Completed in HandleAlertCompletion
		break;
	case ENotifierInfoPrint:
		DisplayInfoMsg(aMessage);
		break;
	case EStartNotifier:
		StartNotifierL(aMessage);
		break;
	case ECancelNotifier:
		{
		TInt result = NotifierCancel(aMessage);
		if(result == KErrNone)
			{
			result = Server().Manager()->NotifierCancel(TUid::Uid(aMessage.Int0()));
			}
		aMessage.Complete(result);
		completeMessage = EFalse;
		}
		break;
	case EUpdateNotifier:
		{
		UpdateNotifierL(aMessage);
		completeMessage = EFalse; // Completed in UpdateNotifierL
		}
		break;
	case EStartNotifierAndGetResponse:
		{
		TBool cleanupComplete = ETrue;
		StartNotifierAndGetResponseL(aMessage, cleanupComplete);
		completeMessage = EFalse; // the plug-in has responsibility for completing the message (either synchronously or asynchronously)
		}
		break;
	case EUpdateNotifierAndGetResponse:
		UpdateNotifierAndGetResponseL(aMessage);
		completeMessage = EFalse;
		break;
	default:
		aMessage.Complete(KErrNotSupported);
		break;
		}
		
	if (completeMessage && !aMessage.IsNull())
		aMessage.Complete(KErrNone);

	DEBUGPRINT3(_L("CEikServNotifySession::ServiceL() finished, UID: 0x%X Message completed: %U"),aMessage.Int0(),completeMessage);
	}

void CEikServNotifySession::DisplayAlert(const RMessage2& aMessage)
	//
	// Display an alert
	//
	{
	iLengthOfCombinedBuffer = aMessage.GetDesLength(1);
	if (iLengthOfCombinedBuffer < 0)
		return;

	iLengthOfFirstLineOfMessage = (static_cast<TUint>(aMessage.Int2())>>16);
	iLengthOfSecondLineOfMessage = (aMessage.Int2()&KMaxTUint16);
	iLengthOfFirstButtonOfMessage = (static_cast<TUint>(aMessage.Int3())>>16);
	iLengthOfSecondButtonOfMessage = (aMessage.Int3()&KMaxTUint16);
	
	if (iLengthOfCombinedBuffer != iLengthOfFirstLineOfMessage + iLengthOfSecondLineOfMessage + 
									iLengthOfFirstButtonOfMessage + iLengthOfSecondButtonOfMessage)
		{
		aMessage.Panic(KPanicClient_CEikServNotifySession,EEikSrvClientPanicInconsistentMessageParameters);
		return;
		}
		
	HBufC* const combinedBuffer = HBufC::New(iLengthOfCombinedBuffer);
	if(!combinedBuffer)
		return;

	TPtr combinedBuffer_asWritable(combinedBuffer->Des());
	const TInt error = aMessage.Read(1, combinedBuffer_asWritable);
	if (error)
		{
		delete combinedBuffer;
		return;
		}
		
	__ASSERT_DEBUG(iBuffer == NULL, User::Invariant());	
	iBuffer = combinedBuffer;
	
	RNotifierMessageInfoQueue& queue = Server().AsyncMessageQueue();
	const TInt err = queue.Append(TNotifierMessageInfo(aMessage,*this));
	if (!err && queue.Count() == 1) // if the only thing in the queue is what we've just put in it...
		PrepareDisplayAlert();
	}

void CEikServNotifySession::PrepareDisplayAlert()
	{
	const RNotifierMessageInfoQueue& queue = Server().AsyncMessageQueue();
	//Getting the first element from the queue
	ASSERT(queue.Count());
	const TNotifierMessageInfo& firstInQueue = queue[0];
	
	//Getting the parameters for the notifier message to display	
	const TInt lengthOfFirstLine = firstInQueue.iEikServNotifySession.iLengthOfFirstLineOfMessage;
	const TInt lengthOfSecondLine = firstInQueue.iEikServNotifySession.iLengthOfSecondLineOfMessage;
	const TInt lengthOfFirstButton = firstInQueue.iEikServNotifySession.iLengthOfFirstButtonOfMessage;
	const TInt lengthOfSecondButton = firstInQueue.iEikServNotifySession.iLengthOfSecondButtonOfMessage;
	
	const TPtrC firstLineOfMessage(firstInQueue.iEikServNotifySession.iBuffer->Left(lengthOfFirstLine));
	const TPtrC secondLineOfMessage(firstInQueue.iEikServNotifySession.iBuffer->Mid(lengthOfFirstLine,lengthOfSecondLine));
	const TPtrC firstButtonOfMessage(firstInQueue.iEikServNotifySession.iBuffer->Mid(lengthOfFirstLine+lengthOfSecondLine,lengthOfFirstButton));
	const TPtrC secondButtonOfMessage(firstInQueue.iEikServNotifySession.iBuffer->Mid(lengthOfFirstLine+lengthOfSecondLine+lengthOfFirstButton,lengthOfSecondButton));
	
	// after this line we can guarantee that HandleAlertCompletion will be called (assuming that the call to MEikServNotifyAlert's virtual function DisplayNotifier (which is called inside the DisplayNotifier call below) is well-behaved)
	Server().DisplayNotifier(firstLineOfMessage, secondLineOfMessage, firstButtonOfMessage, secondButtonOfMessage, &firstInQueue.iEikServNotifySession);
	}

void CEikServNotifySession::HandleAlertCompletion(const TInt aButtonVal)
	{
	RNotifierMessageInfoQueue& queue = Server().AsyncMessageQueue();
	__ASSERT_ALWAYS(queue.Count() > 0,Panic(EEikServPanicNotifyAlertQueueEmpty));
	
	const TNotifierMessageInfo& firstInQueue = queue[0];
	firstInQueue.iMessage.Complete(firstInQueue.iMessage.Write(0, TPckgC<TInt>(aButtonVal == EEikBidCancel ? 0 : 1)));
	if (firstInQueue.iEikServNotifySession.iBuffer)
		{
		delete firstInQueue.iEikServNotifySession.iBuffer;
		firstInQueue.iEikServNotifySession.iBuffer = NULL;
		}
		
	queue.Remove(0);
	if (queue.Count())
		iEikSrvPendingAlert->TriggerNext();
	}

void CEikServNotifySession::DisplayNextPendingAlert()
	{
	if (Server().AsyncMessageQueue().Count() >= 1)
		PrepareDisplayAlert();
 	}

void CEikServNotifySession::DisplayInfoMsg(const RMessage2& aMessage)
	//
	// Display an info message
	//
	{
	TBuf<400> msg;
	const TInt err = aMessage.Read(0, msg);
	aMessage.Complete(err);
	if(!err)
		Server().DisplayInfoPrint(msg);
	}

HBufC8* CEikServNotifySession::GetRemoteInputBufferLC(const RMessage2& aMessage, TInt aSlot)
	{
	HBufC8* const inputBuffer = HBufC8::NewLC(User::LeaveIfError(aMessage.GetDesLength(aSlot)));
	TPtr8 input(inputBuffer->Des());
	aMessage.ReadL(aSlot, input);
	return inputBuffer;
	}


void CEikServNotifySession::StartNotifierL(const RMessage2& aMessage)
	{
	HBufC8* const inputBuffer = GetRemoteInputBufferLC(aMessage, 1);
	const TUid notifierUid = TUid::Uid(aMessage.Int0());
	const TSecureId secureId = aMessage.SecureId();
	RNotifierSecureInfoQueue& secureInfoQueue = Server().AsyncSecureInfoQueue();
	secureInfoQueue.AppendL(TNotifierSecureInfo(notifierUid, secureId));
	
	if (!aMessage.Int2()) // if the third parameter is null
		{
		TRAPD(err, Server().Manager()->NotifierStartL(TUid::Uid(aMessage.Int0()),*inputBuffer,NULL,iClientId));
		if(err)
			{
			secureInfoQueue.Remove(secureInfoQueue.Count()-1);
			User::Leave(err);
			}
		}
	else
		{
		HBufC8* const responseBuffer = HBufC8::NewLC(User::LeaveIfError(aMessage.GetDesMaxLength(2)));
		TPtr8 response(responseBuffer->Des());
		TRAPD(err, Server().Manager()->NotifierStartL(TUid::Uid(aMessage.Int0()), *inputBuffer, &response, iClientId));
		if(err)
			{
			secureInfoQueue.Remove(secureInfoQueue.Count()-1);
			User::Leave(err);
			}
			
		aMessage.WriteL(2,response);
		CleanupStack::PopAndDestroy(responseBuffer);
		}
		
	CleanupStack::PopAndDestroy(inputBuffer);
	}

void CEikServNotifySession::UpdateNotifierL(const RMessage2& aMessage)
	{
	const RNotifierSecureInfoQueue& secureInfoQueue=Server().AsyncSecureInfoQueue();
	const TUid notifierUid = TUid::Uid(aMessage.Int0());
	const TInt queueTotal = secureInfoQueue.Count();
	TBool completeMessage = EFalse;
	for(TInt i = 0; i < queueTotal; i++)
		{
		if(secureInfoQueue[i].iNotifierUid == notifierUid && secureInfoQueue[i].iSecureId == aMessage.SecureId())
			{
			HBufC8* const inputBuffer = GetRemoteInputBufferLC(aMessage, 1);
			if (!aMessage.Int2()) // if the third parameter is null
				{
				TRAPD(err, Server().Manager()->NotifierUpdateL(TUid::Uid(aMessage.Int0()), *inputBuffer, NULL, iClientId));
				aMessage.Complete(err);
				}
			else
				{
				HBufC8* const outputBuffer = HBufC8::NewLC(User::LeaveIfError(aMessage.GetDesMaxLength(2)));
				TPtr8 output(outputBuffer->Des());
				TRAPD(err, Server().Manager()->NotifierUpdateL(notifierUid, *inputBuffer, &output, iClientId));
				if(!err)
					aMessage.WriteL(2,*outputBuffer);
					
				CleanupStack::PopAndDestroy(outputBuffer);
				aMessage.Complete(err);
				}
			completeMessage = ETrue;
			CleanupStack::PopAndDestroy(inputBuffer);
			break;
			}
		}
		
	if (!completeMessage)
		aMessage.Complete(KErrNotFound);
	}

void CEikServNotifySession::StartNotifierAndGetResponseL(const RMessage2& aMessage,TBool& aCleanupComplete)
	{
	HBufC8* const inputBuffer = GetRemoteInputBufferLC(aMessage, 1);
	const TUid notifierUid = TUid::Uid(aMessage.Int0());
	const TSecureId secureId = aMessage.SecureId();
	RNotifierSecureInfoQueue& secureInfoQueue = Server().AsyncSecureInfoQueue();
	secureInfoQueue.AppendL(TNotifierSecureInfo(notifierUid,secureId));
	
	TRAPD(err, Server().Manager()->NotifierStartAndGetResponseL(TUid::Uid(aMessage.Int0()), *inputBuffer, 2, aMessage, iClientId, aCleanupComplete));
	if(err)
		{
		secureInfoQueue.Remove(secureInfoQueue.Count()-1);
		User::Leave(err);
		}
		
	CleanupStack::PopAndDestroy(inputBuffer);
	}

void CEikServNotifySession::UpdateNotifierAndGetResponseL(const RMessage2& aMessage)
	{
	const RNotifierSecureInfoQueue& secureInfoQueue=Server().AsyncSecureInfoQueue();
	const TUid notifierUid = TUid::Uid(aMessage.Int0());
	const TInt queueTotal = secureInfoQueue.Count();
	TBool completeMessage = ETrue;
	for(TInt i = 0; i < queueTotal; i++)
		{
		if(secureInfoQueue[i].iNotifierUid == notifierUid && secureInfoQueue[i].iSecureId == aMessage.SecureId())
			{
			HBufC8* const inputBuffer = GetRemoteInputBufferLC(aMessage, 1);
			Server().Manager()->NotifierUpdateAndGetResponseL(notifierUid, *inputBuffer, 2, aMessage, iClientId);
			CleanupStack::PopAndDestroy(inputBuffer);
			completeMessage = EFalse;
			break;
			}
		}
		
	if (completeMessage)
		aMessage.Complete(KErrNotSupported); // The client that initially created or connected to the notifier was not found
	}


TInt CEikServNotifySession::NotifierCancel(const RMessage2& aMessage)
	{
	RNotifierSecureInfoQueue& secureInfoQueue = Server().AsyncSecureInfoQueue();
	const TUid notifierUid = TUid::Uid(aMessage.Int0());
	const TSecureId secureId = aMessage.SecureId();
	TInt queueTotal = secureInfoQueue.Count();
	
	for(TInt i = 0; i < queueTotal; i++)
		{
		if(secureInfoQueue[i].iNotifierUid == notifierUid && secureInfoQueue[i].iSecureId == secureId)
			{
			secureInfoQueue.Remove(i);
			return KErrNone;
			}
		}
	return KErrNotFound;
	}

CEikServNotifySession::CEikSrvPendingAlert::CEikSrvPendingAlert(CEikServNotifySession& aEikServNotifySession)
 : CActive(EActivePriorityClockTimer), iEikServNotifySession(aEikServNotifySession)
	{
	CActiveScheduler::Add(this);
	}

CEikServNotifySession::CEikSrvPendingAlert::~CEikSrvPendingAlert()
	{
	Cancel();
	}

void CEikServNotifySession::CEikSrvPendingAlert::TriggerNext()
	{
	iStatus = KRequestPending;
	SetActive();
	TRequestStatus* status = &iStatus;
	User::RequestComplete(status, KErrNone);
	}

void CEikServNotifySession::CEikSrvPendingAlert::DoCancel()
	{
	}

void CEikServNotifySession::CEikSrvPendingAlert::RunL()
	{
	iEikServNotifySession.DisplayNextPendingAlert();
	}
//
//CEikSrvNotifierWrapper
//

CEikSrvNotifierWrapper::CEikSrvNotifierWrapper(MEikSrvNotifierBase2* aNotifier)
	: iNotifier(aNotifier)
	{
	}

CEikSrvNotifierWrapper::~CEikSrvNotifierWrapper()
	{
	if(iNotifier)
		iNotifier->Release();
	}

void CEikSrvNotifierWrapper::RegisterNotifierL()
	{
	iInfo = iNotifier->RegisterL();
	}

//
//CEikSrvNotifierRemover
//

CEikSrvNotifierRemover* CEikSrvNotifierRemover::NewL()
	{//static
	CEikSrvNotifierRemover* self = new(ELeave) CEikSrvNotifierRemover();
	CActiveScheduler::Add(self);
	return self;
	}

CEikSrvNotifierRemover::CEikSrvNotifierRemover()
	: CActive(EPriorityHigh)	// high priority active object, s.t. it gets run before any more requests to cservers in the eiksrv thread.
	{
	}

CEikSrvNotifierRemover::~CEikSrvNotifierRemover()
	{
	Cancel();
	}

void CEikSrvNotifierRemover::Start(CEikSrvNotifierManager* aManager, CArrayPtr<CEikSrvNotifierWrapper>* aObservedList)
	{
	__ASSERT_ALWAYS(aObservedList, Panic(EEikServPanicNullObservedList));
	iManager = aManager;
	iObservedList = aObservedList;
	SetActive();
	iStatus = KRequestPending;
	TRequestStatus* status = &iStatus;
	User::RequestComplete(status, KErrNone);
	}

void CEikSrvNotifierRemover::RunL()
	{
	const TInt maxIndex = iObservedList->Count() - 1;
	for(TInt ii = maxIndex; ii >= 0; ii--)
		{
		CEikSrvNotifierWrapper* notifierWrapper = iObservedList->At(ii);
		const MEikSrvNotifierBase2::TNotifierInfo info = notifierWrapper->iNotifier->Info();
		const TUid plugInDllUid = notifierWrapper->iPlugInDllUid;
		if(notifierWrapper->iIsReadyForRemoval)
			{
			if(plugInDllUid != KNullUid)	// only cancel if it comes from one of the transient dlls !
				{
				delete notifierWrapper;
				iObservedList->Delete(ii);	// resize the CEikSrvNotifierWrapper array
				}
			}
		}
	}

void CEikSrvNotifierRemover::DoCancel()
	{
	}

//
//CEikSrvNotifierManager
//

CEikSrvNotifierManager* CEikSrvNotifierManager::NewL()
	{
	CEikSrvNotifierManager* self = new (ELeave) CEikSrvNotifierManager;
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(); // self
	return self;
	}

CEikSrvNotifierManager::~CEikSrvNotifierManager()
	{
	if (iObservedList)
		{
		iObservedList->ResetAndDestroy();
		delete iObservedList;
		}
	
	// This calls REComSession::DestroyedImplementation which closes plug-in libraries, 
	// hence must be called *after* the virtual Release function is called on the 
	// plug-ins (inside the iObservedList->ResetAndDestroy() call above)
	iPluginUidList.ResetAndDestroy(); 
	iPluginUidList.Close();
		
	delete iChannelMonitor;
	delete iActivityMonitor;
	delete iQueue;
	delete iNotifierRemover;
	delete iDiscoverNewImplementation;
	}

LOCAL_C void DeleteTempMArray(TAny* aPtr)
	{
	CArrayPtr<MEikSrvNotifierBase2>* array = reinterpret_cast<CArrayPtr<MEikSrvNotifierBase2>*>(aPtr);
	const TInt count = array->Count();
	for(TInt ii = 0; ii < count; ii++)
		(*array)[ii]->Release();

	delete array;
	}

LOCAL_C void DeleteTempCArray(TAny* aPtr)
	{
	CArrayPtr<CEikSrvNotifierWrapper>* const array = reinterpret_cast<CArrayPtr<CEikSrvNotifierWrapper>*>(aPtr);
	array->ResetAndDestroy();
	delete array;
	}


CArrayPtr<CEikSrvNotifierWrapper>* CEikSrvNotifierManager::CreateNotifierArrayFromPlugInArrayL(CArrayPtr<MEikSrvNotifierBase2>* aPlugInArray, const TUidType& /*aUidType*/)
	{
	User::LeaveIfNull(aPlugInArray);
	const TInt count = aPlugInArray->Count();
	CleanupStack::PushL(TCleanupItem(DeleteTempMArray,aPlugInArray));
	const TInt arrayIncrement = Max(1, count);	// at least one
	
	CArrayPtrFlat<CEikSrvNotifierWrapper>* retArray = new (ELeave)CArrayPtrFlat<CEikSrvNotifierWrapper>(arrayIncrement);
	CleanupStack::PushL(TCleanupItem(DeleteTempCArray,retArray));
	for(TInt ii = 0; ii < count; ii++)
		{
		MEikSrvNotifierBase2* notif = aPlugInArray->At(0);
		notif->SetManager(this);
		CEikSrvNotifierWrapper* notifier = new (ELeave) CEikSrvNotifierWrapper(notif);
		aPlugInArray->Delete(0);	// remove notif from aPlugInArray
		CleanupStack::PushL(notifier);
		retArray->AppendL(notifier);
		CleanupStack::Pop(notifier);
		}
		
	CleanupStack::Pop(retArray);
	CleanupStack::PopAndDestroy(aPlugInArray);
	return retArray;
	}

void CEikSrvNotifierManager::UpdateHighestPriorityNotifiersOnThisChannelOfTheirPausingOrResuming(TUid aChannelUid, TUid aHighestPriorityNotifierOnThisChannelUid, const TDesC8& aBuffer)
	{
	const TInt count = iObservedList->Count();
	for (TInt jj = 0; jj < count; jj++)
		{
		MEikSrvNotifierBase2* notifForUpdate = ((*iObservedList)[jj])->iNotifier;
		const MEikSrvNotifierBase2::TNotifierInfo infoForUpdate = notifForUpdate->Info();
		if (infoForUpdate.iUid == aHighestPriorityNotifierOnThisChannelUid && infoForUpdate.iChannel == aChannelUid)
			{
			TRAP_IGNORE(notifForUpdate->UpdateL(aBuffer));
			}
		}
	}

void CEikSrvNotifierManager::TryAddNotifiersFromNotifierArrayL(CArrayPtr<CEikSrvNotifierWrapper>* aNotifierArray, TInt& aRollBackChannels)
	{
	const TInt maxIndex = aNotifierArray->Count() - 1;
	for(TInt ii = maxIndex; ii >= 0; ii--)
		{
		CEikSrvNotifierWrapper* notifier = aNotifierArray->At(ii);
		iObservedList->AppendL(notifier);		// notifier is owned by aNotifierArray, so should this fail, everything is ok. 
		aNotifierArray->Delete(ii);	// wan't to get this pointer out of aNotifierArray asap to avoid double deletion from cleanup stack.
		const MEikSrvNotifierBase2::TNotifierInfo& info = notifier->iInfo;
		DEBUGPRINT4(_L("CEikSrvNotifierManager::TryAddNotifiersFromNotifierArrayL; Adding notifier: UID 0x%X, priority %d, channel 0x%X"),info.iUid,info.iPriority,info.iChannel);
		
		if (!iChannelMonitor->AlreadyHasChannel(info.iChannel))
			{
			iChannelMonitor->AddNewChannelL(info.iChannel);
			++aRollBackChannels;
			}
		}
	}

CEikSrvNotifierManager::CEikSrvNotifierManager()
	{
	}

void CEikSrvNotifierManager::ConstructL()
	{
	iObservedList = new(ELeave) CArrayPtrSeg<CEikSrvNotifierWrapper>(6);
	iChannelMonitor = CChannelMonitor::NewL();
	iActivityMonitor = CActivityMonitor::NewL();
	iQueue = CEikNotifierQueue::NewL();
	iNotifierRemover = CEikSrvNotifierRemover::NewL();
	iDiscoverNewImplementation = CDiscoverNewImplementation::NewL(*this);
	}

struct SActivityCleanup
	{
	CActivityMonitor* iMonitor;
	TUid iNotifier;
	TInt iClientId;
	};

LOCAL_C void CleanupActivityMonitor(TAny* aPtr)
	{
	SActivityCleanup& cleanup = *reinterpret_cast<SActivityCleanup*>(aPtr);
	cleanup.iMonitor->Remove(cleanup.iNotifier, cleanup.iClientId);
	}

class MNotifierStarter
	{
public:
	virtual TInt StartAlreadyActiveNotifierL(MEikSrvNotifierBase2& aNotifier, const TDesC8& aBuffer) = 0;
	virtual void StartInactiveNotifierL(MEikSrvNotifierBase2& aNotifier, const TDesC8& aBuffer, TDes8* aResponse) = 0;
	virtual CEikNotifierQueue::CQueueItem* NewQueueItemLC(const MEikSrvNotifierBase2::TNotifierInfo& aInfo, TInt aClientId, const TDesC8& aBuffer) = 0;
	};

class MNotifierUpdater
	{
public:
	virtual void UpdateActiveNotifierL(MEikSrvNotifierBase2& aNotifier, const TDesC8& aBuffer, TDes8* aResponse) = 0;
	};

//
// class TSynchronousNotifierUpdater
//

NONSHARABLE_CLASS(TSynchronousNotifierUpdater) : public MNotifierUpdater
	{
public:
	inline TSynchronousNotifierUpdater() {}
private:
	virtual void UpdateActiveNotifierL(MEikSrvNotifierBase2& aNotifier, const TDesC8& aBuffer, TDes8* aResponse);
	};

void TSynchronousNotifierUpdater::UpdateActiveNotifierL(MEikSrvNotifierBase2& aNotifier, const TDesC8& aBuffer, TDes8* aResponse)
	{
	if (aResponse)
		aResponse->Copy(aNotifier.UpdateL(aBuffer));
	else
		aNotifier.UpdateL(aBuffer);
	}

NONSHARABLE_CLASS(TAsynchronousNotifierUpdater) : public MNotifierUpdater
	{
public:
	TAsynchronousNotifierUpdater(TInt aReplySlot, const RMessage2& aMessage);
private: // from TSynchronousNotifierUpdater
	void UpdateActiveNotifierL(MEikSrvNotifierBase2& aNotifier, const TDesC8& aBuffer, TDes8* aResponse);
private:
	TInt iReplySlot;
	const RMessage2& iMessage;
	};

TAsynchronousNotifierUpdater::TAsynchronousNotifierUpdater(TInt aReplySlot, const RMessage2& aMessage)
	:iReplySlot(aReplySlot), iMessage(aMessage)
	{
	}

void TAsynchronousNotifierUpdater::UpdateActiveNotifierL(MEikSrvNotifierBase2& aNotifier, const TDesC8& aBuffer, TDes8* /*aResponse*/)
	{
	aNotifier.UpdateL(aBuffer, iReplySlot, iMessage);
	}

//
// class CEikSrvNotifierManager
// 

void CEikSrvNotifierManager::DoNotifierStartL(MNotifierStarter& aNotifierStarter,TBool& aCleanupComplete,TUid aNotifierUid,TUid aChannelUid,const TDesC8& aBuffer,TDes8* aResponse, TInt aClientId)
	{
	TInt result = KErrNotFound;
	RArray<TInt> notifierPositions;
	CleanupClosePushL(notifierPositions);
	
	LookForNotifierInObservedListL(aNotifierUid, aChannelUid, notifierPositions);
	
	for (TInt ii = 0; ii < notifierPositions.Count(); ii++)
		{
		MEikSrvNotifierBase2* notif = ((*iObservedList)[notifierPositions[ii]])->iNotifier;
		const MEikSrvNotifierBase2::TNotifierInfo info = notif->Info();
		if(!NotifierHandlesScreenMode(notif))
			User::Leave(KErrNotSupported);

		if (iActivityMonitor->IsNotifierActive(aNotifierUid, info.iChannel))
			result = aNotifierStarter.StartAlreadyActiveNotifierL(*notif, aBuffer);
		else if (info.iPriority > iChannelMonitor->ActivityLevel(info.iChannel))
			{
			TUid notifier;
			MEikSrvNotifierBase2::TNotifierPriority priority;
			const TBool channelWasActive = iActivityMonitor->IsChannelActive(info.iChannel, notifier, priority);
			iActivityMonitor->AddL(info, aClientId);
			
			SActivityCleanup cleanup;
			cleanup.iMonitor = iActivityMonitor;
			cleanup.iNotifier = aNotifierUid;
			cleanup.iClientId = aClientId;
			CleanupStack::PushL(TCleanupItem(CleanupActivityMonitor,&cleanup));
			
			aCleanupComplete = EFalse;
			aNotifierStarter.StartInactiveNotifierL(*notif,aBuffer,aResponse);
			CleanupStack::Pop(&cleanup);
			
			if (channelWasActive)
				UpdateHighestPriorityNotifiersOnThisChannelOfTheirPausingOrResuming(info.iChannel, notifier, KEikNotifierPaused);

			iChannelMonitor->UpdateChannel(info.iChannel, info.iPriority);
			if (result != KQueued)
				result = KErrNone;
			}
		else
			{
			if (iQueue->IsAlreadyQueued(info.iUid, info.iChannel))
				result = KErrAlreadyExists;
			else
				{
				CEikNotifierQueue::CQueueItem* const queueCopy = aNotifierStarter.NewQueueItemLC(info,aClientId,aBuffer);
				iQueue->QueueItemL(queueCopy);
				CleanupStack::Pop(queueCopy);
				result = KQueued;
				}
			}
		}
		
	User::LeaveIfError(result);
	CleanupStack::PopAndDestroy(&notifierPositions);
	}

class TSynchronousNotifierStarter : public MNotifierStarter
	{
public:
	inline TSynchronousNotifierStarter() {}
private: // from MNotifierStarter
	TInt StartAlreadyActiveNotifierL(MEikSrvNotifierBase2& aNotifier, const TDesC8& aBuffer);
	void StartInactiveNotifierL(MEikSrvNotifierBase2& aNotifier, const TDesC8& aBuffer, TDes8* aResponse);
	CEikNotifierQueue::CQueueItem* NewQueueItemLC(const MEikSrvNotifierBase2::TNotifierInfo& aInfo, TInt aClientId, const TDesC8& aBuffer);
private:
	};

TInt TSynchronousNotifierStarter::StartAlreadyActiveNotifierL(MEikSrvNotifierBase2&,const TDesC8&)
	{
	return KErrAlreadyExists;
	}

void TSynchronousNotifierStarter::StartInactiveNotifierL(MEikSrvNotifierBase2& aNotifier, const TDesC8& aBuffer, TDes8* aResponse)
	{
	if(aResponse)
		aResponse->Copy(aNotifier.StartL(aBuffer));
	else
		aNotifier.StartL(aBuffer);
	}

CEikNotifierQueue::CQueueItem* TSynchronousNotifierStarter::NewQueueItemLC(const MEikSrvNotifierBase2::TNotifierInfo& aInfo, 
														TInt aClientId, const TDesC8& aBuffer)
	{
	return CEikNotifierQueue::CQueueItem::NewLC(aInfo, aClientId, aBuffer, RMessage2(), -1);
	}

void CEikSrvNotifierManager::NotifierStartL(TUid aNotifierUid, const TDesC8& aBuffer, TDes8* aResponse, TInt aClientId)
	{
	TBool notUsed = ETrue;
	TSynchronousNotifierStarter notifierStarter;
	DoNotifierStartL(notifierStarter, notUsed, aNotifierUid, KNonExistentUid, aBuffer, aResponse, aClientId);
	}

TInt CEikSrvNotifierManager::NotifierUpdateL(TUid aNotifierUid, const TDesC8& aBuffer, TDes8* aResponse, TInt aClientId)
	{
	TSynchronousNotifierUpdater notifierUpdater;
	return DoNotifierUpdateL(notifierUpdater, aNotifierUid, aBuffer, aResponse, aClientId);
	}

TBool CEikSrvNotifierManager::NotifierHandlesScreenMode(MEikSrvNotifierBase2* aNotifier)
	{
	const TInt screenMode = CEikonEnv::Static()->ScreenDevice()->CurrentScreenMode();
	if(screenMode != 0)
		{
		const TInt notifierCapabilities = aNotifier->NotifierCapabilites();
		if(notifierCapabilities == ENoSpecialCapabilities)
			return EFalse;
		}
		
	return ETrue;
	}

void CEikSrvNotifierManager::LookForNotifierInObservedListL(TUid aNotifierUid, TUid aChannelUid, RArray<TInt>& aNotifierPositions)
	{
    CleanupClosePushL(aNotifierPositions);
	const TInt count = iObservedList->Count();
	for (TInt ii = 0; ii < count; ii++)
		{
		MEikSrvNotifierBase2* notif = ((*iObservedList)[ii])->iNotifier;
		const MEikSrvNotifierBase2::TNotifierInfo info = notif->Info();
		if (info.iUid == aNotifierUid && (aChannelUid == KNonExistentUid || info.iChannel == aChannelUid))
			User::LeaveIfError(aNotifierPositions.Append(ii));
		}
	CleanupStack::Pop(&aNotifierPositions);
	}

void CEikSrvNotifierManager::NotifierStartAndGetResponseL(TUid aNotifierUid, const TDesC8& aBuffer, TInt aReplySlot,
														  const RMessage2& aMessage, TInt aClientId, TBool& aCleanupComplete)
	{
	NotifierStartAndGetResponseL(aNotifierUid, KNonExistentUid, aBuffer, aReplySlot, aMessage, aClientId, aCleanupComplete);
	}

//
// class TAsynchronousNotifierStarter
//

NONSHARABLE_CLASS(TAsynchronousNotifierStarter) : public MNotifierStarter
	{
public:
	TAsynchronousNotifierStarter(TInt aReplySlot,const RMessage2& aMessage);
private: // from MNotifierStarter
	TInt StartAlreadyActiveNotifierL(MEikSrvNotifierBase2& aNotifier,const TDesC8& aBuffer);
	void StartInactiveNotifierL(MEikSrvNotifierBase2& aNotifier,const TDesC8& aBuffer,TDes8* aResponse);
	CEikNotifierQueue::CQueueItem* NewQueueItemLC(const MEikSrvNotifierBase2::TNotifierInfo& aInfo,TInt aClientId,const TDesC8& aBuffer);
private:
	TInt iReplySlot;
	const RMessage2& iMessage;
	};

TAsynchronousNotifierStarter::TAsynchronousNotifierStarter(TInt aReplySlot, const RMessage2& aMessage)
	:iReplySlot(aReplySlot), iMessage(aMessage)
	{
	}

TInt TAsynchronousNotifierStarter::StartAlreadyActiveNotifierL(MEikSrvNotifierBase2& aNotifier, const TDesC8& aBuffer)
	{
	aNotifier.StartL(aBuffer, iReplySlot, iMessage); // asynch notifier can decide whether to support multiple clients
	return KErrNone;
	} 

void TAsynchronousNotifierStarter::StartInactiveNotifierL(MEikSrvNotifierBase2& aNotifier, const TDesC8& aBuffer, TDes8* /*aResponse*/)
	{
	aNotifier.StartL(aBuffer, iReplySlot, iMessage);
	}

CEikNotifierQueue::CQueueItem* TAsynchronousNotifierStarter::NewQueueItemLC(const MEikSrvNotifierBase2::TNotifierInfo& aInfo, 
														TInt aClientId, const TDesC8& aBuffer)
	{
	__ASSERT_DEBUG(!iMessage.IsNull(), User::Invariant());
	return CEikNotifierQueue::CQueueItem::NewLC(aInfo, aClientId, aBuffer, iMessage, iReplySlot);
	}

// 
// class CEikSrvNotifierManager
//

void CEikSrvNotifierManager::NotifierStartAndGetResponseL(TUid aNotifierUid, TUid aChannelUid, const TDesC8& aBuffer, TInt aReplySlot,
														  const RMessage2& aMessage, TInt aClientId, TBool& aCleanupComplete)
	{
	TAsynchronousNotifierStarter notifierStarter(aReplySlot, aMessage);
	TBuf8<1> notUsed;
	DoNotifierStartL(notifierStarter, aCleanupComplete, aNotifierUid, aChannelUid, aBuffer, &notUsed, aClientId);
	}

void CEikSrvNotifierManager::NotifierUpdateAndGetResponseL(TUid aNotifierUid, const TDesC8& aBuffer, TInt aReplySlot,
														  const RMessage2& aMessage, TInt aClientId)
	{
	TAsynchronousNotifierUpdater notifierUpdater(aReplySlot, aMessage);
	TBuf8<1> notUsed;
	DoNotifierUpdateL(notifierUpdater, aNotifierUid, aBuffer, &notUsed, aClientId);
	}

TInt CEikSrvNotifierManager::DoNotifierUpdateL(MNotifierUpdater& aNotifierUpdater, TUid aNotifierUid, const TDesC8& aBuffer, TDes8* aResponse, TInt aClientId)
	{
	TInt result = KErrNotFound;
	TInt foundNotifs = 0;
	const TInt count = iObservedList->Count();
	for (TInt ii = 0; ii < count; ii++)
		{
		MEikSrvNotifierBase2* notif=((*iObservedList)[ii])->iNotifier;
		const MEikSrvNotifierBase2::TNotifierInfo info=notif->Info();
		if(info.iUid == aNotifierUid)
			{
			if (iActivityMonitor->IsNotifierActive(aNotifierUid,info.iChannel))
				{
				if (!iActivityMonitor->IsClientPresent(aNotifierUid,info.iChannel,aClientId))
					iActivityMonitor->AddL(info,aClientId);

				aNotifierUpdater.UpdateActiveNotifierL(*notif,aBuffer,aResponse);
				foundNotifs++;
				}
			else
				{
				; // not all channels have been started yet so update the queue
				}

			result = KErrNone;
			}
		}

	if (!foundNotifs && !result) // No active notifs found
		result = KErrNotReady;
	
	User::LeaveIfError(result); //leave because return code is not handled
	return result;
	}

TInt CEikSrvNotifierManager::NotifierCancel(TUid aNotifierUid)
	{
/*
  1. Old notif always gets cancelled.
  2. fetch next item from each channel.  If non-NULL, start these items now
  3. if item fails to start call NotifierCancel for that uid, cancelling all 
     channels regardless of whether they were already running
*/
	TInt result = KErrNotFound;
	const TInt count = iObservedList->Count();
	for (TInt ii = 0; ii < count; ii++)
		{
		MEikSrvNotifierBase2* notif = ((*iObservedList)[ii])->iNotifier;
		const MEikSrvNotifierBase2::TNotifierInfo info = notif->Info();
		if (info.iUid == aNotifierUid)
			{
			// This will cause the client request to be set to complete by the notifier's Cancel
			// (if it has been implemented properly) unless the notifier has never been started
			// (the notifier's StartL function has never been called).
			// If the notifier has never been started it is in the queue and 
			// CEikNotifierQueue::RemoveNotifier will complete the client request instead of the notifier.
			notif->Cancel();
			((*iObservedList)[ii])->iIsReadyForRemoval = ETrue;	// record that this notifier will be removed if it's from a transient type dll.
			if(iNotifierRemover)
				{
				iNotifierRemover->Cancel();
				iNotifierRemover->Start(this, iObservedList);
				}
				
			iActivityMonitor->RemoveNotifier(aNotifierUid,info.iChannel);
			iQueue->RemoveNotifier(aNotifierUid);
			
			//check channel activity and get highest priority on channnel
			TUid notifier;
			MEikSrvNotifierBase2::TNotifierPriority priority;
			if (iActivityMonitor->IsChannelActive(info.iChannel, notifier, priority))
				{
				// Check if priority of a queued item on the same channel is greater 
				const MEikSrvNotifierBase2::TNotifierPriority queuePriority = 
						(MEikSrvNotifierBase2::TNotifierPriority)iQueue->GetHighestQueuePriority(info.iChannel);
				
				if (queuePriority > priority)
					{
					iChannelMonitor->UpdateChannel(info.iChannel, MEikSrvNotifierBase2::ENotifierPriorityLowest);
					StartNextFromQueue(info.iChannel);
					}
				else
					{
					UpdateHighestPriorityNotifiersOnThisChannelOfTheirPausingOrResuming(info.iChannel, notifier, KEikNotifierResumed);
					iChannelMonitor->UpdateChannel(info.iChannel, priority);
					}
				}
			else
				{
				iChannelMonitor->UpdateChannel(info.iChannel, MEikSrvNotifierBase2::ENotifierPriorityLowest);
				StartNextFromQueue(info.iChannel);
				}
				
			result = KErrNone;
			}
		}
		
	return result;
	}

struct SCleanupMessage
	{
	TBool* iDoCleanup;
	const RMessage2* iMessage;
	};

LOCAL_C void CleanupStartAndGetResponse(TAny* aPtr)
	{
	SCleanupMessage& cleanup = *reinterpret_cast<SCleanupMessage*>(aPtr);
	if (cleanup.iDoCleanup)
		cleanup.iMessage->Complete(KErrNoMemory);
	}

void CEikSrvNotifierManager::StartNextFromQueue(TUid aChannel)
	{
	CEikNotifierQueue::CQueueItem* next = iQueue->FetchItem(aChannel);	// Transfer ownership of CQueueItem from the queue
	if (next)
		{
		const TUid notif = next->iInfo.iUid;
		TRAPD(err, DoStartQueuedItemLD(next));	// Safely consumes CQueueItem "next"
		if (err)
			NotifierCancel(notif);
		}
	}
	
void CEikSrvNotifierManager::DoStartQueuedItemLD(CEikNotifierQueue::CQueueItem* aItem)	
	{
	CleanupStack::PushL(aItem);

	if (aItem->iMessage.IsNull())
		NotifierStartL(aItem->iInfo.iUid, aItem->Buffer(), NULL, aItem->iClientId);
	else
		{
		TBool doCleanup = ETrue;
		SCleanupMessage cleanup;
		cleanup.iDoCleanup = &doCleanup;
		cleanup.iMessage = &aItem->iMessage;
		CleanupStack::PushL(TCleanupItem(CleanupStartAndGetResponse, &cleanup));
		NotifierStartAndGetResponseL(aItem->iInfo.iUid, aItem->iInfo.iChannel, aItem->Buffer(), 
									aItem->iReplySlot, aItem->iMessage, aItem->iClientId, doCleanup);
		CleanupStack::Pop(&cleanup);
		}

	CleanupStack::PopAndDestroy(aItem);
	}

void CEikSrvNotifierManager::HandleClientExit(TInt aClientId)
	{
	TUid notifier = KNullUid;
	while (iActivityMonitor->NotifierForClient(notifier, aClientId))
		{
		const TInt count = iObservedList->Count();
		for (TInt ii = 0; ii < count; ii++)
			{
			MEikSrvNotifierBase2* notif = ((*iObservedList)[ii])->iNotifier;
			if (notif->Info().iUid == notifier)
				NotifierCancel(notifier);
			}
			
		iActivityMonitor->Remove(notifier,aClientId);
		}
		
	iActivityMonitor->RemoveClient(aClientId);
	iQueue->RemoveClient(aClientId);
	}

void CEikSrvNotifierManager::StartNotifierL(TUid aNotifierUid,const TDesC8& aBuffer,TDes8& aResponse)
	{
	NotifierStartL(aNotifierUid,aBuffer,&aResponse,KNullClientId);
	}

void CEikSrvNotifierManager::CancelNotifier(TUid aNotifierUid)
	{
	NotifierCancel(aNotifierUid);
	}

void CEikSrvNotifierManager::UpdateNotifierL(TUid aNotifierUid,const TDesC8& aBuffer,TDes8& aResponse)
	{
	NotifierUpdateL(aNotifierUid,aBuffer,&aResponse,KNullClientId);
	}

void CEikSrvNotifierManager::HandleScreenDeviceChangedL()
	{ 
	//notify any active notifiers of a screen changed event, if they don't support a screen mode change.
	//they are cancelled and the list of notifiers is iterated through again to check for any 
	//queued notifiers that may have been made active.
	const TInt count = iObservedList->Count();
	MEikSrvNotifierBase2::TNotifierInfo notifierInfo;
	for (TInt ii = 0; ii < count; ii++)
		{
		MEikSrvNotifierBase2* notifier = (*iObservedList)[ii]->iNotifier;
		notifierInfo = notifier->Info();
		if(iActivityMonitor->IsNotifierActive(notifierInfo.iUid, notifierInfo.iChannel))
			{
			const TInt notifierCapabilities = notifier->NotifierCapabilites();
			if(notifierCapabilities == ENoSpecialCapabilities)
				{
				//Notifier does not support flip events so cancel it.
				NotifierCancel(notifierInfo.iUid);
				}
			else if(notifierCapabilities&EScreenDeviceChangeSupported)
				{
				notifier->HandleSystemEventL(KUidEventScreenModeChanged);
				}
			}
		}
	}

//
// CChannelMonitor
//

CChannelMonitor* CChannelMonitor::NewL()
	{
	CChannelMonitor* self = new(ELeave) CChannelMonitor;
	return self;
	}

TInt CChannelMonitor::NumberOfChannels() const
	{
	return iMonitor.Count();
	}

void CChannelMonitor::DeleteChannel(TInt aIndex)
	{
	__ASSERT_ALWAYS((aIndex >= 0) && (aIndex < iMonitor.Count()), Panic(EEikServPanicChannelIndexOutOfRange));
	iMonitor.Delete(aIndex);
	}

TBool CChannelMonitor::AlreadyHasChannel(TUid aChannel) const
	{
	const TInt count = iMonitor.Count();
	for (TInt ii = 0; ii < count; ii++)
		{
		if (iMonitor[ii].iChannel == aChannel)
			return ETrue;
		}
		
	return EFalse;
	}

TInt CChannelMonitor::ActivityLevel(TUid aChannel) const
	{
	const TInt count = iMonitor.Count();
	for (TInt ii = 0; ii < count; ii++)
		{
		const TChannelActivity activity = iMonitor[ii];
		if (activity.iChannel == aChannel)
			return activity.iHighestPriorityRunning;
		}
		
	return 0;
	}

void CChannelMonitor::UpdateChannel(TUid aChannel, TInt aLevel)
	{
	const TInt count = iMonitor.Count();
	for (TInt ii = 0; ii < count; ii++)
		{
		TChannelActivity& activity = iMonitor[ii];
		if (activity.iChannel == aChannel)
			{
			activity.iHighestPriorityRunning = aLevel;
			break;
			}
		}
	}

CChannelMonitor::CChannelMonitor()
	:iMonitor(3)
	{}

//
// class CNotifierActivity
//

CActivityMonitor::CNotifierActivity* CActivityMonitor::CNotifierActivity::NewLC(const MEikSrvNotifierBase2::TNotifierInfo& aInfo,TInt aClientId)
	{ // static
	CNotifierActivity* self=new(ELeave) CNotifierActivity(aInfo);
	CleanupStack::PushL(self);
	self->ConstructL(aClientId);
	return self;
	}

CActivityMonitor::CNotifierActivity::~CNotifierActivity()
	{
	iClientArray.Reset();
	}

TInt CActivityMonitor::CNotifierActivity::Find(TInt aClientId) const
	{
	TInt index=KErrNotFound;
	const TInt count=iClientArray.Count();
	for (TInt ii=0;ii<count;ii++)
		{
		TInt clientId=iClientArray[ii];
		if (clientId==aClientId)
			{
			index=ii;
			break;
			}
		}
		
	return index;
	}

CActivityMonitor::CNotifierActivity::CNotifierActivity(const MEikSrvNotifierBase2::TNotifierInfo& aInfo)
	: iInfo(aInfo), iClientArray(1)
	{}

void CActivityMonitor::CNotifierActivity::ConstructL(TInt aClientId)
	{
	iClientArray.AppendL(aClientId);
	}

//
// class CActivityMonitor
//

CActivityMonitor* CActivityMonitor::NewL()
	{ // static
	CActivityMonitor* self=new(ELeave) CActivityMonitor();
	return self;
	}

CActivityMonitor::~CActivityMonitor()
	{
	iMonitor.ResetAndDestroy();
	}

void CActivityMonitor::AddL(const MEikSrvNotifierBase2::TNotifierInfo& aInfo,TInt aClientId)
	{
	const TInt index = Find(aInfo.iUid,aInfo.iChannel);
	if (index == KErrNotFound)
		{
		CNotifierActivity* activity = CNotifierActivity::NewLC(aInfo,aClientId);
		iMonitor.AppendL(activity);
		CleanupStack::Pop(); // activity
		}
	else
		iMonitor[index]->iClientArray.AppendL(aClientId);
	}

void CActivityMonitor::Remove(TUid aNotifierUid,TInt aClientId)
	{
	const TInt index = Find(aNotifierUid);
	if (index != KErrNotFound)
		{
		CNotifierActivity* activity=iMonitor[index];
		const TInt clientIndex=activity->Find(aClientId);
		if (clientIndex != KErrNotFound)
			{
			if (activity->iClientArray.Count()==1)
				{
				delete activity;
				iMonitor.Delete(index);
				}
			else
				activity->iClientArray.Delete(index);
			}
		}
	}

void CActivityMonitor::RemoveNotifier(TUid aNotifierUid,TUid aChannel)
	{
	const TInt index = Find(aNotifierUid,aChannel);
	if (index != KErrNotFound)
		{
		delete iMonitor[index];
		iMonitor.Delete(index);
		}
	}

void CActivityMonitor::RemoveClient(TInt aClientId)
	{
	TInt ii = 0;
	while (ii < iMonitor.Count())
		{
		CNotifierActivity* ptr = iMonitor[ii];
		const TInt index = ptr->Find(aClientId);
		if (index != KErrNotFound)
			ptr->iClientArray.Delete(index);
			
		if (ptr->iClientArray.Count()==0)
			{
			iMonitor.Delete(ii);
			delete ptr;
			}
		else
			++ii;
		}
	}

TBool CActivityMonitor::IsNotifierActive(TUid aNotifierUid,TUid aChannel) const
	{
	const TInt index = Find(aNotifierUid,aChannel);
	return (index != KErrNotFound);
	}

TBool CActivityMonitor::IsClientPresent(TUid aNotifierUid,TUid aChannel,TInt aClientId) const
	{
	TBool found = EFalse;
	const TInt index = Find(aNotifierUid,aChannel);
	if (index != KErrNotFound)
		found = (iMonitor[index]->Find(aClientId) != KErrNotFound);
	
	return found;
	}

TBool CActivityMonitor::IsChannelActive(TUid aChannel,TUid& aNotifier,MEikSrvNotifierBase2::TNotifierPriority& aHighestPriority) const
	{
	TBool isChannelActive = EFalse;
	const TInt count = iMonitor.Count();
	for (TInt ii = 0; ii < count; ii++)
		{
		const MEikSrvNotifierBase2::TNotifierInfo info=iMonitor[ii]->iInfo;
		if (info.iChannel == aChannel)
			{
			if ((!isChannelActive) || (aHighestPriority < (MEikSrvNotifierBase2::TNotifierPriority)info.iPriority))
				{
				isChannelActive = ETrue;
				aNotifier = info.iUid;
				aHighestPriority = (MEikSrvNotifierBase2::TNotifierPriority)info.iPriority;
				}
			}
		}
		
	return isChannelActive;
	}

TBool CActivityMonitor::NotifierForClient(TUid& aNotifierUid, TInt aClientId) const
	{
	TBool isOnlyClient = EFalse;
	aNotifierUid = KNullUid;
	const TInt count = iMonitor.Count();
	for (TInt ii = 0; ii < count; ii++)
		{
		CNotifierActivity* ptr = iMonitor[ii];
		if (ptr->Find(aClientId) != KErrNotFound)
			{
			aNotifierUid = ptr->iInfo.iUid;
			isOnlyClient = ptr->iClientArray.Count()==1;
			break;
			}
		}
		
	return isOnlyClient;
	}

CActivityMonitor::CActivityMonitor()
	: iMonitor(1)
	{}

TInt CActivityMonitor::Find(TUid aNotifierUid) const
	{
	const TInt count = iMonitor.Count();
	for (TInt ii = 0; ii < count; ii++)
		{
		if (iMonitor[ii]->iInfo.iUid == aNotifierUid)
			return ii;
		}
		
	return KErrNotFound;
	}

TInt CActivityMonitor::Find(TUid aNotifierUid, TUid aChannel) const
	{
	const TInt count = iMonitor.Count();
	for (TInt ii = 0; ii < count; ii++)
		{
		const CNotifierActivity* ptr = iMonitor[ii];
		if (ptr->iInfo.iUid == aNotifierUid && ptr->iInfo.iChannel == aChannel)
			return ii;
		}

	return KErrNotFound;
	}

//
// class CQueueItem
//

CEikNotifierQueue::CQueueItem* CEikNotifierQueue::CQueueItem::NewLC(const MEikSrvNotifierBase2::TNotifierInfo& aInfo, TInt aClientId, 
																	const TDesC8& aBuffer, const RMessage2& aMessage,TInt aReplySlot)
	{
	CQueueItem* self=new(ELeave) CQueueItem(aInfo,aClientId,aMessage,aReplySlot);
	CleanupStack::PushL(self);
	self->ConstructL(aBuffer);
	return self;
	}

CEikNotifierQueue::CQueueItem::~CQueueItem()
	{
	delete iBuffer;
	}

CEikNotifierQueue::CQueueItem::CQueueItem(const MEikSrvNotifierBase2::TNotifierInfo& aInfo, TInt aClientId, 
											const RMessage2& aMessage, TInt aReplySlot)
	:iInfo(aInfo),
	 iClientId(aClientId),
	 iMessage(aMessage),
	 iReplySlot(aReplySlot),
	 iBuffer(NULL)
	{
	}

void CEikNotifierQueue::CQueueItem::ConstructL(const TDesC8& aBuffer)
	{
	iBuffer=aBuffer.AllocL();
	}

//
// class CEikNotifierQueue
//

CEikNotifierQueue* CEikNotifierQueue::NewL()
	{
	CEikNotifierQueue* self = new (ELeave) CEikNotifierQueue;
	return self;
	}

/**
Get the queue item from the notifier queue. CQueueItem ownership is transfered from
the queue to the caller.
*/
CEikNotifierQueue::CQueueItem* CEikNotifierQueue::FetchItem(TUid aChannel)
	{
	CEikNotifierQueue::CQueueItem* result = NULL;
	TInt priority = MEikSrvNotifierBase2::ENotifierPriorityLowest-1;
	TInt index = KErrNotFound;
	
	const TInt count = iQueue.Count();
	for (TInt ii = 0; ii < count; ii++)
		{
		CEikNotifierQueue::CQueueItem* item = iQueue[ii];
		if (item->iInfo.iChannel == aChannel && item->iInfo.iPriority > priority)
			{
			index = ii;
			priority = item->iInfo.iPriority;
			result = item;
			}
		}

	if (index != KErrNotFound)
		iQueue.Delete(index);

	return result;
	}

TBool CEikNotifierQueue::IsAlreadyQueued(TUid aNotifier,TUid aChannel) const
	{
	const TInt count = iQueue.Count();
	for (TInt ii = 0; ii < count; ii++)
		{
		CEikNotifierQueue::CQueueItem* item = iQueue[ii];
		if (item->iInfo.iUid == aNotifier && item->iInfo.iChannel == aChannel)
			return ETrue;
		}

	return EFalse;
	}

void CEikNotifierQueue::RemoveClient(TInt aClientId)
	{
	const TInt count = iQueue.Count();
	for (TInt ii = count-1; ii >= 0; ii--)
		{
		CEikNotifierQueue::CQueueItem* item = iQueue[ii];
		TInt clientId = item->iClientId;
		if (clientId == aClientId)
			{
			delete item;
			iQueue.Delete(ii);
			}
		}
	}


TInt CEikNotifierQueue::GetHighestQueuePriority(TUid aChannel)
	{
	TInt priority = MEikSrvNotifierBase2::ENotifierPriorityLowest-1;
	
	const TInt count = iQueue.Count();
	for (TInt ii = 0; ii < count; ii++)
		{
		CEikNotifierQueue::CQueueItem* item=iQueue[ii];
		if (item->iInfo.iChannel == aChannel && item->iInfo.iPriority>priority)
			priority = item->iInfo.iPriority;
		}

	return priority;
	}

const CEikNotifierQueue::CQueueItem& CEikNotifierQueue::At(TInt aIndex) const
	{
	__ASSERT_DEBUG((aIndex>=0) && (aIndex < iQueue.Count()),Panic(EEikServPanicQueueIndexOutOfRange));
	return *(iQueue.At(aIndex));
	}

void CEikNotifierQueue::RemoveNotifier(TUid aNotifierUid)
	{
	const TInt count=iQueue.Count();
	for(TInt ii = count -1; ii >= 0; --ii)
		{
		if(iQueue[ii]->iInfo.iUid==aNotifierUid)
			{
			if (!iQueue[ii]->iMessage.IsNull())
    			{
    			// The notifiers in the queue have never been started and so
    			// they have no pointer to the RMessage2 (it is passed in as argument 
    			// to the StartL function but it has never been called). The framework
    			// has to complete the request.
    			iQueue[ii]->iMessage.Complete(KErrCancel);
    			}
			iQueue.Delete(ii);
			}
		}
	}



//

LOCAL_C void ReleaseOnCleanup(TAny* aObject)
//
// Used for cleanup of objects on stack if a function leaves.
//
	{
	REINTERPRET_CAST(RImplInfoPtrArray*,(aObject))->ResetAndDestroy();
	REINTERPRET_CAST(RImplInfoPtrArray*,(aObject))->Close();
	}

TInt FindInOrderFunction(const CPluginTrack& aPluginTrack1,const CPluginTrack& aPluginTrack2)
//
// This function is used to find a plugin with specific implementation uid in the list.
// It is internally called by RPointerArray function FindInOrder.
//
	{
	return (aPluginTrack1.iPluginImplementationUid.iUid - aPluginTrack2.iPluginImplementationUid.iUid);
	}

void CEikSrvNotifierManager::RegisterL()
//
// Register the plugins at bootup
//
	{
	//This is the list where we have the information of all the ECOM plugin i,e
	// 1. The plugin implementatiuon UID
	// 2. The Number of instances of recognizer in an single implementation
	// 3. The Plugin Destructor Key
	iPluginUidList.Reset();

	// Array to return all implementations in an interface
	RImplInfoPtrArray plugInArray;
	
	// ListImplementationsL leaves if it cannot find anything so trap the error and ignore it.
	REComSession::ListImplementationsL(KUidPluginInterfaceNotifiers, plugInArray);

	// Push the plugin array on the stack
	CleanupStack::PushL(TCleanupItem(ReleaseOnCleanup,&plugInArray));
	
	// it the plugin count is zero dont load any thing
	for(TInt i=plugInArray.Count()-1; i>=0; --i)
		{
		TUid chosenUid = {0};
		chosenUid = plugInArray[i]->ImplementationUid();
		TRAPD(err, DoAddPlugInL(chosenUid));
		if(err)
			{
			DEBUGPRINT3(_L("CEikSrvNotifierManager::RegisterL() DoAddPlugInL leaved with error:%d for plugin:0x%x"), err, chosenUid);
			}
		}

	CleanupStack::Pop(&plugInArray);
	plugInArray.ResetAndDestroy();
	plugInArray.Close();

	//Sort the Pluginlist array
	TLinearOrder<CPluginTrack> linearOrder (&FindInOrderFunction);
	iPluginUidList.Sort(linearOrder);

	//Start the discovery of newly added plugins so that we can detect a runtime installation
	iDiscoverNewImplementation->Start();

	}

CArrayPtr<CEikSrvNotifierWrapper>* CEikSrvNotifierManager::LoadPlugInAndPopulateNotifierArrayL(TUid aUid)
//
// Loads the notifier plugins depending on the chosen implementation uid.
//
	{
    DEBUGPRINT2(_L("CEikSrvNotifierManager:: LoadPlugInAndPopulateNotifierArrayL: Loading Plugin: Uid 0x%X"), aUid );

	TUid destructorKey;
	// Tells that its a dll	& simulating a Notifier for Type V2.
	TUidType aUidType(KDynamicLibraryUid, KUidNotifierPlugInV2, aUid);
	destructorKey.iUid = 0;

	//Create implementation for the choosen UID. 
	CArrayPtr<MEikSrvNotifierBase2>* array = reinterpret_cast<CArrayPtr<MEikSrvNotifierBase2>*>(
												REComSession::CreateImplementationL(aUid, destructorKey));

	// passes ownership of 'array'. Array is internally destroyed.
	CArrayPtr<CEikSrvNotifierWrapper>* retArray = CreateNotifierArrayFromPlugInArrayL(array,aUidType);	

	// Copys the destructor key to the destructorKey variable in CEikSrvNotifierWrapper class.
	// Also construct the wrapper class which gets the notifier registration information in the member
	// variables.
	const TInt retArrayCount = retArray->Count();
	for (TInt i = 0; i < retArrayCount; i++)
		{
		CEikSrvNotifierWrapper* const notifier = retArray->At(i);
		notifier->RegisterNotifierL();
		notifier->iDestructorKey = destructorKey;
		}

	return retArray;
	}


TBool CEikSrvNotifierManager::IsImplementationRemoved(TUid aImplementationUid, RImplInfoPtrArray& aPlugInArray)
// 
// Finds if a particular implementation is present in the ecom registry returned data
//
	{
	for (TInt i=aPlugInArray.Count()-1; i>=0; --i)
		{
		if(aImplementationUid == aPlugInArray[i]->ImplementationUid())
			return EFalse;
		}
			
	return ETrue;
	}

// 
// Finds if a particular implementation is newly added in the ecom registry returned data
//
TBool CEikSrvNotifierManager::IsImplementationAdded(TUid aImplementationUid)
	{
	for (TInt i=iPluginUidList.Count()-1; i>=0; --i)
		{
		if(aImplementationUid==(iPluginUidList[i])->iPluginImplementationUid)
			return EFalse;
		}

	return ETrue;
	}

void CEikSrvNotifierManager::CheckForEcomPluginInstallUninstall()
//
// This function finds out the whether an ecom notifier has been installed or removed
//
	{
	// Array to return all implementations in an interface)
	RImplInfoPtrArray plugInArray;
	
	// ListImplementationsL leaves if it cannot find anything so trap the error and ignore it.
	TRAP_IGNORE(REComSession::ListImplementationsL(KUidPluginInterfaceNotifiers, plugInArray));
	CleanupStack::PushL(TCleanupItem(ReleaseOnCleanup, &plugInArray));
	
	TBool doUpdate = EFalse;
	
	// If an implementation is not present in the iPluginUidList then its added. 
	for(TInt i = plugInArray.Count()-1; i>=0; --i)	
		{
		TUid uid = plugInArray[i]->ImplementationUid();
		if(IsImplementationAdded(uid))
			{
			// Add the implementation which is not present in the plugin array and also 
			// update the plugintrack with new implementation and its dll uid.
			TRAPD(err,DoAddPlugInL(uid));
			if(err)
				{
				DEBUGPRINT3(_L("CEikSrvNotifierManager::CheckForEcomPluginInstallUninstall() DoAddPlugInL leaved with error:%d for plugin:0x%x"), err, uid);
				}
				
			doUpdate = ETrue;
			}
		}

	// If a implementation is not present in present in the plugInArray then its removed. 
	for(TInt j = iPluginUidList.Count()-1; j >= 0; --j)
		{
		if(IsImplementationRemoved((iPluginUidList[j])->iPluginImplementationUid, plugInArray))
			UnloadEComPlugInImplementation(j);	//Remove the implementation
		}
	
	if(doUpdate)
		{//Sort the Pluginlist array
		TLinearOrder<CPluginTrack> linearOrder(&FindInOrderFunction);
		iPluginUidList.Sort(linearOrder);
		}

	CleanupStack::Pop(&plugInArray);
	plugInArray.ResetAndDestroy();
	plugInArray.Close();
	}

void CEikSrvNotifierManager::UnloadEComPlugInImplementation(TInt aIndex)
// 
// Remove the Ecom notifier plugins from the particular implementation
//
	{
	//Remove the Ecom notifier plugins from the particular implementation
	for (TInt i = (iPluginUidList[aIndex])->iNotifierInfo.Count()-1 ; i >=0 ; --i)
		{
		//find in the observed global list the notifier with same Notifier UID, channel UID & destruction key
		for (TInt j = iObservedList->Count()-1; j >=0  ; --j)
			{
			CEikSrvNotifierWrapper* notifier = iObservedList->At(j);
			MEikSrvNotifierBase2::TNotifierInfo info = notifier->iInfo;
			const CPluginTrack& pluginTrack = *iPluginUidList[aIndex];
			const CPluginTrack::TNotifierInfo& info2 = pluginTrack.iNotifierInfo[i];
			if ((info2.iNotifierPluginUid == info.iUid) &&
				(info2.iNotifierPluginChannelUid == info.iChannel) &&
				(pluginTrack.iDtr_key == notifier->iDestructorKey))
				{
				//Delete the notifier
				iObservedList->Delete(j);
				}
			}
		}

	//Remove the implementation
	delete iPluginUidList[aIndex];
	iPluginUidList.Remove(aIndex);
	}

void CEikSrvNotifierManager::DoAddPlugInL(TUid aUid)
// 
// Add plugins depending on the implementation UID
//
	{
	CArrayPtr<CEikSrvNotifierWrapper>* array = LoadPlugInAndPopulateNotifierArrayL(aUid);
	User::LeaveIfNull(array);
	CleanupStack::PushL(TCleanupItem(DeleteTempCArray,array));
	TInt rollBackChannels = 0;	// required for removing any added channels should this function fail part way through

	const TInt currentObsListIndx = iObservedList->Count();
	TRAPD(error, TryAddNotifiersFromNotifierArrayL(array, rollBackChannels));
	if(error)
		{
		TInt indexToDelete;
		for(TInt jj = 0; jj < rollBackChannels; jj++)
			{
			indexToDelete = iChannelMonitor->NumberOfChannels() - 1; 
			iChannelMonitor->DeleteChannel(indexToDelete);
			}
		User::Leave(error);
		}
	CleanupStack::PopAndDestroy(array);

	//Add the new added plugin to the track list
	CPluginTrack* pluginTrack = new(ELeave) CPluginTrack;
	CleanupStack::PushL(pluginTrack);
	pluginTrack->iPluginImplementationUid = aUid;
	//Add the notifier info to the track pluginlist after successful loading and roll back
	const TInt obsListCount = iObservedList->Count();
	for (TInt i = currentObsListIndx; i < obsListCount; i++)
		{
		CEikSrvNotifierWrapper* notifier = iObservedList->At(i);
		pluginTrack->iDtr_key = notifier->iDestructorKey;
		CPluginTrack::TNotifierInfo notifInfo(notifier->iInfo.iUid,notifier->iInfo.iChannel);
		User::LeaveIfError(pluginTrack->iNotifierInfo.Append(notifInfo));
		}

	User::LeaveIfError(iPluginUidList.Append(pluginTrack));
	CleanupStack::Pop(pluginTrack);
	}

//
// class CDiscoverNewImplementation
//

CDiscoverNewImplementation::CDiscoverNewImplementation(CEikSrvNotifierManager& aManager): CActive(EActivePriorityDefault) , iManager(aManager)
//
// Constructor.
//
	{
	// make and install the active scheduler
	CActiveScheduler::Add(this); // install as active scheduler
	}

void CDiscoverNewImplementation::ConstructL()
//
// 2 phase construction. opens a econ server session.
//
	{
	iEComSession = &REComSession::OpenL();
	}

CDiscoverNewImplementation::~CDiscoverNewImplementation()
// 
// Destructor. Closes ecom file server session and cancels the active object itself.
//
	{
	Cancel();
	iEComSession->Close();
	}

CDiscoverNewImplementation *CDiscoverNewImplementation::NewL(CEikSrvNotifierManager& aManager)
// 
// Static method to instantiate the class. Notifier manager class pointer is passed as a 
//  argument.
//
	{
	CDiscoverNewImplementation* self = new (ELeave) CDiscoverNewImplementation(aManager);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

void CDiscoverNewImplementation::Start()
// 
// Places an outstanding request to active schedular for asynchronous event by ecom server.
//  Mostly it will be an installation or unstallation of the ecom based sis files.
//
	{
	iEComSession->NotifyOnChange(iStatus);
	SetActive();
	}

void CDiscoverNewImplementation::RunL()
// 
// Called when an asynchronous request from ecom server is invoked.
//
	{
	_LIT(KCDiscoverNewImplementationPanic,"CDiscoverNewImplementation Paniced");
	__ASSERT_ALWAYS(!IsActive(),User::Panic(KCDiscoverNewImplementationPanic,KErrCompletion));

	//Check wether plugin was installed or removed
	iManager.CheckForEcomPluginInstallUninstall();
	//Restart the active Object
	Start();
	}

void CDiscoverNewImplementation::DoCancel()
//
// If user want to cancel the active object request. The ecom server outstanding request will
// also get cancelled.
//
	{
	iEComSession->CancelNotifyOnChange(iStatus);
	}

//
// class CPluginTrack::TNotifierInfo
//

CPluginTrack::TNotifierInfo::TNotifierInfo(TUid aNotifierPluginUid, TUid aNotifierPluginChannelUid)
//
// Constructor.
//
	{
	iNotifierPluginUid = aNotifierPluginUid;
	iNotifierPluginChannelUid = aNotifierPluginChannelUid;
	}

//
// class CPluginTrack
//

CPluginTrack::CPluginTrack()
// 
// Constructor
//
	{
	iPluginImplementationUid.iUid = 0;
	iDtr_key.iUid = 0;
	}

CPluginTrack::~CPluginTrack()
// 
// Destructor.
//
	{
	iNotifierInfo.Reset();
	iNotifierInfo.Close();
	if(iDtr_key.iUid)
		{
		REComSession::DestroyedImplementation(iDtr_key);
		}
	}
//

//
// class TNotifierSecureInfo
//

TNotifierSecureInfo::TNotifierSecureInfo(const TUid aNotifierUid, const TSecureId aSecureId)
 : iNotifierUid(aNotifierUid), iSecureId(aSecureId)
	{
	}

