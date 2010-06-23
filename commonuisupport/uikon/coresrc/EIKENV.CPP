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
// mm: 
// Areas of improvement:
// * Move the CEikErrorResolver to EikSrv as it is only used there
// * Fix ineffective deprecation tags on KeyPressLabel(), Version(), and SetVerboseInfoReporting()
// * Review CCoeDataStorage
// * Make ControlStackReadyL() @internalTechnology (and rename it)
// * Check documentatoin of SetAutoForwarding()
// 
//


#include <e32uid.h>
#include <e32hal.h>
#include <basched.h>
#include <barsread.h>
#include <bautils.h>
#include "baerror.h"
#include <bassnd.h>
#include <txtrich.h>
#include <txtfmlyr.h>
#include <txtfrmat.h>
#include <mparser.h>
#include <savenotf.h>
#include <apparc.h>
#include <apgdoor.h>
#include <apgicnfl.h>
#include <apgcli.h>
#include <apgwgnam.h>
#include <prnsetup.h>
#include <gulbordr.h>
#include <gulcolor.h>
#include <gulfont.h>
#include <gulicon.h>
#include <fepbase.h>
#include <coecntrl.h>
#include <coeerror.h>
#include <coesndpy.h>
#include "CoeDataStorage.h"
#include <eikenv.h>
#include <eikappui.h>
#include <eikdoc.h>
#include <eikapp.h>
#include <eikmsg.h>
#include <eikdebug.h>

#include <eikproc.h>
#include <eikrutil.h>
#include <eiksfont.h>
#include <eikdll.h>
#include <eiksvdef.h>
#include <eikpanic.h>
#include <uiklafgt/eikcore.rsg>
#include <uiklafgt/eikpriv.rsg>
#include <eikvcurs.h>
#include <eiksrvs.h>
#include "eikerror.h"
#include <uiklaf/private/lafshut.h>
#include <ecom/ecom.h>
#include <eikserverapp.h>
#include "EIKSRVC.H"

#include "eikdebugprefs.h"
#include "eikprivate.h"
#include "eikenvextra.h"
#include "eikautomenutitlearray.h"
#include "eikenvinterface.h"
#include <graphics/cone/coeerrorconsts.h>
#include "eikdefconst.h"
#include "eikdefconstinternal.h"
#include "EIKLIBRY.H"
#include "EIKDGFTY.H"

GLDEF_C void Panic(TEikPanic aPanic)
	{
	_LIT(KPanicCat,"EIKON");
	User::Panic(KPanicCat,aPanic);
	}

/**
@internalComponent
*/
const TUid KUikonLibraryUid = {KUidUikonLibraryValue};


/**
@internalComponent
*/
NONSHARABLE_CLASS(CEikErrorIdler) : public CIdle
	{
public:
	static CEikErrorIdler* NewL();
private:
	CEikErrorIdler() : CIdle(EPriorityLow) { }
public:
	TTime iTime;
	TInt iError;
	TInt iContext;
	};

CEikErrorIdler* CEikErrorIdler::NewL()
	{
	CEikErrorIdler* self=new(ELeave) CEikErrorIdler;
	CActiveScheduler::Add(self);
	return(self);
	}


//
// class CEikStartUpViewActivator
//
/**
This is a high-priority async view activator, used by the CEikonEnv to activate the application's 
default view on application startup in the foreground, as the view server won't do it.

@internalComponent
@see CActive
*/
NONSHARABLE_CLASS(CEikStartUpViewActivator) : public CActive
	{
public:
	static CEikStartUpViewActivator* NewL(CEikAppUi& aAppUi, CEikonEnv& aEikonEnv, CEikStartUpViewActivator*& aOwner);
	virtual ~CEikStartUpViewActivator();
private:
	CEikStartUpViewActivator(CEikAppUi& aAppUi, CEikonEnv& aEikonEnv, CEikStartUpViewActivator*& aOwner);
private: // from CActive
	void DoCancel();
	void RunL();
	TInt RunError(TInt aError);
private:
	CEikAppUi& iAppUi;
	CEikonEnv& iEnv;
	CEikStartUpViewActivator*& iOwner;
	};

const TInt KStartUpViewActivatorPriority = EActivePriorityFepLoader+10;

CEikStartUpViewActivator* CEikStartUpViewActivator::NewL(CEikAppUi& aAppUi, CEikonEnv& aEikonEnv, CEikStartUpViewActivator*& aOwner)
	{
	return new(ELeave) CEikStartUpViewActivator(aAppUi, aEikonEnv, aOwner);
	}

CEikStartUpViewActivator::~CEikStartUpViewActivator()
	{
	Cancel();
	iOwner = NULL;
	}

CEikStartUpViewActivator::CEikStartUpViewActivator(CEikAppUi& aAppUi, CEikonEnv& aEikonEnv, CEikStartUpViewActivator*& aOwner)
	: CActive(KStartUpViewActivatorPriority), iAppUi(aAppUi), iEnv(aEikonEnv), iOwner(aOwner)
	{
	CActiveScheduler::Add(this);
	TRequestStatus* status = &iStatus;
	User::RequestComplete(status, KErrNone);
	SetActive();
	}

void CEikStartUpViewActivator::DoCancel()
	{
	}

void CEikStartUpViewActivator::RunL()
	{
	RWsSession& ws = iEnv.WsSession();
	const TInt numWgs = ws.NumWindowGroups(0);
	CArrayFixFlat<TInt>* windowList = new(ELeave) CArrayFixFlat<TInt>(numWgs);
	CleanupStack::PushL(windowList);
	ws.WindowGroupList(0, windowList);
	const TInt wgId = iEnv.RootWin().Identifier();
	if ((ws.GetFocusWindowGroup() == wgId || (windowList->Count() > 0 && windowList->At(0) == wgId))  
		&& (iEnv.IsSchedulerRunning()))
		{
		iAppUi.ActivateTopViewL();	
		}
	CleanupStack::PopAndDestroy(windowList); 	
	delete this;
	}

TInt CEikStartUpViewActivator::RunError(TInt aError)
	{
	delete this;
	return aError;
	}


//
// class CEikonEnv
//

enum TEikEnvFlags
	{
	EAutoForwarding,
	EVerboseInfoReporting,
	EStartedAsServerApp
	};

// @deprecated
EXPORT_C TVersion CEikonEnv::Version()
/** Gets the Uikon version that is currently running.

@return The Uikon version. */
    { // static
    const TInt KEikMajorVersionNumber=1;
	const TInt KEikMinorVersionNumber=0;
	const TInt KEikBuildVersionNumber=106;
    return(TVersion(KEikMajorVersionNumber,KEikMinorVersionNumber,KEikBuildVersionNumber));
    }

EXPORT_C const CFont* CEikonEnv::AnnotationFont() const
/** Gets the standard annotation font for this environment.

It is highly recommended to use CCoeControl::ScreenFont() instead of 
this function.

@see CCoeControl::ScreenFont()
@see CCoeFontProvider

@return Pointer to the annotation font. */
	{
	const TLogicalFont lf( TUid::Uid(KLafUidAnnotationFontVal) );
	return LafEnv::MatchFont(*iFontArray, lf);
	}

EXPORT_C const CFont* CEikonEnv::TitleFont() const
/** Gets the standard title font for this environment.

It is highly recommended to use CCoeControl::ScreenFont() instead of 
this function.

@see CCoeControl::ScreenFont()
@see CCoeFontProvider

@return Pointer to the title font. */
	{
	const TLogicalFont lf( TUid::Uid(KLafUidTitleFontVal) );
	return LafEnv::MatchFont(*iFontArray,lf);
	}

EXPORT_C const CFont* CEikonEnv::LegendFont() const
/** Gets the standard legend font for this environment.

It is highly recommended to use CCoeControl::ScreenFont() instead of 
this function.

@see CCoeControl::ScreenFont()
@see CCoeFontProvider

@return Pointer to the legend font. */
	{
	const TLogicalFont lf( TUid::Uid(KLafUidLegendFontVal) );
	return LafEnv::MatchFont(*iFontArray, lf);
	}

EXPORT_C const CFont* CEikonEnv::SymbolFont() const
/** Gets the standard symbol font for this environment.

It is highly recommended to use CCoeControl::ScreenFont() instead of 
this function.

@see CCoeControl::ScreenFont()
@see CCoeFontProvider

@return Pointer to the symbol font. */
	{
	const TLogicalFont lf( TUid::Uid(KLafUidSymbolFontVal) );
	return LafEnv::MatchFont(*iFontArray, lf);
	}

EXPORT_C const CFont* CEikonEnv::DenseFont() const
/** Gets the standard dense font for this environment.

It is highly recommended to use CCoeControl::ScreenFont() instead of 
this function.

@see CCoeControl::ScreenFont()
@see CCoeFontProvider

@return Pointer to the dense font. */
	{
	const TLogicalFont lf( TUid::Uid(KLafUidDenseFontVal) );
	return LafEnv::MatchFont(*iFontArray, lf);
	}

EXPORT_C const CFont* CEikonEnv::Font(const TLogicalFont& aLogicalFont) const
/** Gets the nearest match to the specified font. 

It is highly recommended to use CCoeControl::ScreenFont() instead of 
this function.

@see CCoeControl::ScreenFont()
@see CCoeFontProvider

The return value is never NULL.

@param aLogicalFont The font for which a match is sought. 
@return Pointer to the font that most closely matches aLogicalFont. */
	{
	return LafEnv::MatchFont(*iFontArray,aLogicalFont);
	}


/**
Framework function. 
Creates array of system fonts. 
*/
EXPORT_C void CEikonEnv::InitSystemFontsL()
	{
    InitSystemResourceFileL();
	InitPrivateResourceFileL();

	ASSERT(!iFontArray);
	iFontArray = new(ELeave) CArrayPtrFlat<CLafSystemFont>(2);
 	LafEnv::CreateSystemFontsL(*this,*iFontArray);

	const TLogicalFont lf( TUid::Uid(KLafUidNormalFontVal) );
	iNormalFont = LafEnv::MatchFont(*iFontArray, lf);
    }

/**
Creates and populates array of bitmaps.
@internalComponent
*/
void CEikonEnv::InitSystemBitmapsL()
	{
	ASSERT(!iBitmapArray);
	iBitmapArray = new(ELeave) CArrayPtrFlat<CFbsBitmap>(2);
	LafEnv::CreateSystemBitmapsL(*this, *iBitmapArray);
    }

EXPORT_C CEikonEnv::CEikonEnv()
/** Default C++ constructor. 

Allocates memory for the new CEikonEnv object; invoke using new(ELeave). 
The second phase constructor should be called after the constructor 
for the environment to be correctly initialised. */
    {
    }

EXPORT_C CEikonEnv::~CEikonEnv()
/** Destructor

Frees any resources allocated by this CEikonEnv during construction. */
	{
	delete iExtension;	
	BaflUtils::ReleaseIdealLanguage();

	DeleteResourceFile(iPrivateResourceFileOffset);
	delete iAppUiFactoryArray;
	delete iAutoMenuTitleArray;
	delete iSingleLineParaFormatLayer;
	delete iParaFormatLayer;
	delete iCharFormatLayer;
	delete iColorList;
	delete iLogicalBorderProxy;
	delete iLafEnv;
	CRichText::DeactivateParserDefaults();
	delete iOOMErrorText;
	if (iClockDll)
		iClockDll->Destroy();
	RApaLsSession::ClearFsSession();
	}

/**
Framework function
*/
EXPORT_C void CEikonEnv::DestroyEnvironment()
	{
	// CRichText::DeactivateParserDefaults must be called in DestroyEnvironment 
	// rather than in the destructor as internally it calls virtual functions 
	// that may (indirectly) use certain features of the CCoeEnv/CEIkonEnv 
	// object (e.g. its focus-observers)
	CRichText::DeactivateParserDefaults(); 
	
	User::Free(iKeyPressLabels);
	
	if (iAlertWin)
		iAlertWin->Release();

	iAlertWin = NULL;
	iAlertWinInitialized = EFalse;
	
	if (iDebugKeys)
		{
		iDebugKeys->Release();
		iDebugKeys = NULL;
		}

	delete iErrorIdler;
	iErrorIdler = NULL;

	if (iBitmapArray)
		{
		iBitmapArray->ResetAndDestroy();
		delete iBitmapArray;
		iBitmapArray = NULL;
		}

	if (iInfoMsgWin)
		{
		iInfoMsgWin->Release();
		iInfoMsgWin = NULL; // CEikonEnv::HandleError uses "!iInfoMsgWin" to test whether we are fully constructed or not, and thus whether the infra-structure is in place so that it can actually handle the error
		}

	BusyMsgCancel();
	if (!LafEnv::PolicyItem(LafEnv::ELAfEnvPolicyDeferredEnvironmentDeletion))
        {
        delete iExtension;
        iExtension = NULL; // NULL it here to prevent double-deletion of this member in ~CEikonEnv.
        }

    DeleteResourceFile(iSystemResourceFileOffset);
    // The order of destruction is important but doesn't really follow a clear logic
    // Some of the CCoeStatic are deleted before the libraries are closed because they may depend on them
    // On the other hand another set of CCoeStatic must be closed after the libraries are closed because the libraries depend on them
    // This was changed to fix a defect (DEF068403), hopefully there will be no cases where this fails, we may have to give up on trying to close 
    // everything ourselves and just let the kernel do it
    CCoeEnv::DestroyEnvironmentStatic();

    if (iFontArray)
		{
		LafEnv::ReleaseSystemFonts(*iFontArray);
		delete iFontArray;
		iFontArray = NULL;
		iNormalFont = NULL; // to prevent CCoeEnv also trying to release it
		}

    if (LafEnv::PolicyItem(LafEnv::ELAfEnvPolicyDeferredEnvironmentDeletion))
		{
		if(!iAppUi) // Ensure libraries are deleted if we get a leave before the AppUi is set 
			CloseLibraries();      
		}
    else
        CloseLibraries();      

    CCoeEnv::DestroyEnvironmentEnd();
    delete this;
    }

const TInt KUidBaflDllValue16 = 0x10003A0F; // !!! should be in BAERROR.H

/**
Handler for extended error codes.  Passes aError to AppUi for handling first.
@internalComponent
@param aError - standard error code passed in
@return - enumerated value (internalComponent - see baerrhand.h)
*/
TErrorHandlerResponse CEikonEnv::PrepareToHandleError(TInt aError)
	{
	// Note that ErrorText() and ErrorContextText() used below returns TDes reference,
	// that is used to set the texts in CCoeEnv.
	
	if (aError != KErrExtendedWithText)
		ErrorContextText().Zero();
	
	const SExtendedError& extErr = CBaActiveScheduler::ExtendedError();
	
	// Itterate over all AppUis (there may be nested embedded ones)
	// to allow one to override the error handling below.
	CEikAppUi* appUi = EikAppUi();
	while (appUi)
		{	
		TErrorHandlerResponse ret = appUi->HandleError(aError, extErr, ErrorText(), ErrorContextText());
		if (ret != EErrorNotHandled)	// Abort of the error was handled
			return ret;
		
		appUi = appUi->ContainerAppUi();
		}
	
	TErrorHandlerResponse ret = EAlertDisplay;
	if (aError == KErrExtendedWithText)		// Ignore the deprecated KErrExtendedWithText message
		return ret;
	
	// If the error was not explicitly handed by any AppUi	

   	TInt resourceId = iSystemResourceFileOffset+1-aError;
	if (aError==KErrExtended)	// Handle legacy supprt for "KErrExtended" emitted by BAFL CBaActiveScheduler
		{
		if (extErr.iInformation)
			ret = EInfoDisplay;
		
		resourceId = extErr.iErrorNumber;
		switch (extErr.iComponent.iUid)
			{
		case 0:
			break;
		case KUidBaflDllValue16:
			resourceId += R_EIK_BAFL_ERROR_OFFSET;
			break;
		case KUidConeDllValue16:
			resourceId += R_EIK_CONE_ERROR_OFFSET;
			break;
		case KUidBaflErrorHandlerValue:
			ret = CBaErrorHandler::CallBack(extErr.iErrorNumber, ErrorText(), ErrorContextText());
			if (ret != EErrorNotHandled)
				return ret;
			ret = EAlertDisplay; 
			//fall through
		default:
			resourceId = iSystemResourceFileOffset+1-KErrUnknown;
			}

		ReadResource(ErrorText(),resourceId);	// Read the error text from resource and set it as the error text		
		}
	else if (aError == KErrNoMemory || extErr.iErrorNumber == KErrNoMemory)
		ErrorText() = *iOOMErrorText; // use pre-allocated text, as ReadResource may try to allocate memory
	else
		GetErrorText(ErrorText(), aError);
		
	return ret;
	}

/** Handles an error that has occurred in the application.

It first offers the error to the app UI's HandleError() function. If that 
does not handle it, this function displays an alert window or an info 
message containing some appropriate text, read from a system resource file.

@param aError One of the standard system error codes.
@publishedAll 
@released */
EXPORT_C void CEikonEnv::HandleError(TInt aError)
    {
	BusyMsgCancel();
	if (aError == KLeaveWithoutAlert)
		return;
	
	if (!iInfoMsgWin) // not finished initializing
		{
        if (LafEnv::PolicyItem(LafEnv::ELafEnvPolicyExitIfErrorDuringStartup))
            User::Exit(aError); // not finished initialising
        else
			return;
		}
	
	const TErrorHandlerResponse type = PrepareToHandleError(aError);
	DoHandleError(type);
    }

/** Handles the specified error. 

This function reads the error context text from the resource identified by 
aContextResourceId.

@param aError ID of the error to handle. 
@param aContextResourceId ID of the resource from which the context is read. */
EXPORT_C void CEikonEnv::HandleErrorWithContext(TInt aError, TInt aContextResourceId)
	{
	const TErrorHandlerResponse type = PrepareToHandleError(aError);
	if (!ErrorContextText().Length())
		ReadResource(ErrorContextText(),aContextResourceId);
	
	DoHandleError(type);
	}


void CEikonEnv::DoHandleError(TErrorHandlerResponse aType)
	{
	if (aType==EInfoDisplay)
		InfoMsg(ErrorText());
	else if (aType==EAlertDisplay)
		{
		if (ErrorContextText().Length())
			AlertWin(ErrorContextText(), ErrorText());
		else
			AlertWin(ErrorText(), ErrorContextText());
		}
	}

/** Notifies this environment that an idle error occurred while redrawing was in 
progress.

@param aError ID of the idle error. */
EXPORT_C void CEikonEnv::NotifyIdleErrorWhileRedrawing(TInt aError)
	{
	NotifyIdleError(aError,R_EIK_TBUF_ERROR_WHILE_REDRAWING);
	}

/** Notifies this environment of an idle error. 

This function reads the error context text from the resource identified by aContextResourceId. 
Calling this method will only trigger one error dialog per minute. Calling it any more frequent
will result in no action.

@param aError ID of the idle error. 
@param aContextResourceId ID of the resource from which the context text is read. */
EXPORT_C void CEikonEnv::NotifyIdleError(TInt aError,TInt aContextResourceId)
	{
	TTime time;
	time.UniversalTime();
	TTimeIntervalSeconds gap;
	const TInt err = time.SecondsFrom(iErrorIdler->iTime,gap);
	if (!err && gap < TTimeIntervalSeconds(60))
		return; // less than one minute since previous notification

	iErrorIdler->iError = aError;
	iErrorIdler->iContext = aContextResourceId;
	iErrorIdler->iTime = time;
	iErrorIdler->Cancel();
	iErrorIdler->Start(TCallBack(IdleErrorCallBack,this));
	}


/**
Static callback function for use with Idle Object (iErrorIdler).
Standard Symbian OS callback paradigm.
@internalComponent
@param aThis  Pointer to self, requires casting to call non-static function
@return always EFalse
*/
TInt CEikonEnv::IdleErrorCallBack(TAny* aThis)
	{ // static
	CEikonEnv* self = (CEikonEnv*)aThis;
	self->HandleErrorWithContext(self->iErrorIdler->iError, self->iErrorIdler->iContext);
	return EFalse; // single shot callback
	}

/**
@publishedAll 
@deprecated
*/
EXPORT_C void CEikonEnv::LeaveWithErrorContext(TInt aError,const TDesC& aContextText)
	{
	GetErrorText(ErrorText(),aError);
	BaflUtils::CopyWithTruncation(ErrorContextText(),aContextText);
	User::Leave(KErrExtendedWithText);	// Leave with a code of KErrExtendedWithText
	}


/** Displays an error message appropriate to the error code aError in an alert window. 
The message is read from a resource file and has a maximum of 256 characters.

@param aError Error code.
@param aAppUid Application UID. By default, this is KNullUid. If a non null UID is 
specified and the error code is not known to UIKON, then the UID enables an 
application-specific error resource file to be scanned (if one exists) to try to 
resolve the error. */
EXPORT_C void CEikonEnv::ResolveError(TInt aError,TUid aAppUid) const
	{
	TBuf<KEikErrorResolverMaxTextLength> errText;
	GetErrorText(errText,aError,aAppUid);
	const_cast<CEikonEnv*>(this)->AlertWin(errText);
	}

/** Gets the text for a standard error code.

@param aDes On return, contains the error text.
@param aError Error code.

@publishedAll 
@released */
EXPORT_C void CEikonEnv::GetErrorText(TDes& aDes,TInt aError) const
    {
	GetErrorText(aDes,aError,KNullUid);
	}


/**	Gets the text for an error code, in the specified application.

It returns whether the error code is valid or not.

@param aDes On return, contains the error text.
@param aError Error number.
@param aAppUid  Application UID.
@return EErrorNumValid if the error code is valid, EErrorNumInvalid if the error code is invalid.

@publishedAll 
@released */
EXPORT_C CEikonEnv::TErrorValidity CEikonEnv::GetErrorText(TDes& aDes,TInt aError,TUid aAppUid) const
	{
	CEikonEnv::TErrorValidity ret = CEikonEnv::EErrorNumValid;
	
	if (IsEiksrvThread())	// If this is the EikSrv, get the text directly from the error resolver...
		ret = const_cast<CEikonEnv*>(this)->iEikEnvExtra->iErrorResolver->ResolveError(aDes,aError,aAppUid);
	else	// ... else connect to EikSrv and get the error text from it.
		{
		REikAppUiSession eiksrv;
		if (eiksrv.Connect()==KErrNone)
			{
			ret = eiksrv.ResolveError(aDes,aError,aAppUid);	// This calls into EikSrv's copy of this method, see above.
			eiksrv.Close();
			}
		else
			DoGetErrorText(aDes,aError);
		}
	return ret;
    }

/**	Gets the text for an error code, in the specified application.

It returns whether the error code is valid or not.

@param aErrorText On return, contains the error text.
@param aError Error number.
@param aTitleText On return, contains the title text of the error.
@return EErrorNumValid if the error code is valid, EErrorNumInvalid if the error code is invalid.

@publishedAll 
@released */
EXPORT_C CEikonEnv::TErrorValidity CEikonEnv::GetErrorTextAndTitle(TDes& aErrorText, TInt aError, TDes& aTitleText) const
	{
	TInt resId = 0;
	TUint flags = 0;
	return DoGetErrorTextAndTitle(aErrorText, aError, resId, flags, aTitleText);
	}


/** 
N.B. This method is also called from the CTextResolver::DoResolveErrorStringL() 
in the textresolver.cpp, located in the tools/s60_header_compat component, part 
of the CoreOS agreement.

@param aErrorText On return, contains the error text.
@param aError Error number.
@param aFlags Output parameter - Error Resource Flag.
@param aTextId Output parameter - Error Text Resource Id.
@param aTitleText On return, contains the title text of the error.

@param aIsMemoryAllocatedByErrResolver is mainly used by the CTextResolver::DoResolveErrorStringL() to indicate that 
memory for error text is unlimited, ie., the memory for the error text is allocated by the text resolver.
By default it is EFalse.
@return EErrorNumValid if the error code is valid, EErrorNumInvalid if the error code is invalid.

@internalTechnology */
EXPORT_C CEikonEnv::TErrorValidity CEikonEnv::DoGetErrorTextAndTitle(TDes& aErrorText, TInt aError, TInt& aTextId, TUint& aFlags, TDes& aTitleText, TBool aIsMemoryAllocatedByErrResolver) const
	{
	CEikonEnv::TErrorValidity errValidity = CEikonEnv::EErrorNumValid;

	if (IsEiksrvThread())	// If this is the EikSrv, get the text directly from the error resolver...
		errValidity = iEikEnvExtra->iErrorResolver->ResolveErrorWithTitle(aErrorText, aTitleText, aError, aTextId, aFlags, aIsMemoryAllocatedByErrResolver);
	else
		{
		// ... else connect to EikSrv and get the error text from it.
		REikAppUiSession eiksrv;
		TInt err = eiksrv.Connect();
		if (!err)
			{
			TRAP(err, errValidity = eiksrv.ResolveErrorWithTitleL(aErrorText, aError, aTextId, aFlags, aTitleText, aIsMemoryAllocatedByErrResolver)); // This calls into EikSrv's copy if this method, see above.
			eiksrv.Close();
			}
		}
	return errValidity;
	}

EXPORT_C void CEikonEnv::DoGetErrorText(TDes& aDes, TInt aError) const
/** Exported for testing only.
@internalTechnology */
    {
	const TInt error = ((aError > KErrNotFound || aError < KLastSystemWideErrCode) ? KErrUnknown : aError);
    ReadResource(aDes, iSystemResourceFileOffset+1-error);
    }

EXPORT_C void CEikonEnv::SetAlertWin(MEikAlertWin* aAlertWin)
/** Sets the enviroment's alert window.

@param aAlertWin A custom alert window.

@publishedPartner 
@released */
	{
	if (iAlertWin)
		iAlertWin->Release();

	iAlertWin = aAlertWin;
	}

EXPORT_C void CEikonEnv::AlertWin(const TDesC& aMsg)
/** Displays the environment's alert window containing a single line message.

@param aMsg Message to be displayed in the alert window. */
	{
    AlertWin(aMsg, TPtrC());
	}

EXPORT_C void CEikonEnv::AlertWin(const TDesC& aMsg1,const TDesC& aMsg2)
/** Displays an alert window with a brief message.

@param aMsg1 First line of the message. 
@param aMsg2 Second line of the message. */
	{
    if (iAlertWinInitialized)
		iAlertWin->RunAlert(aMsg1, aMsg2);
	else
		LafEnv::DisplayAlertAsNotifier(aMsg1, aMsg2);
	}
	
/**
Framework function
*/
EXPORT_C void CEikonEnv::DestroyScreen()
    {
	if (iEikEnvExtra)
		{
		delete iEikEnvExtra->iAppServer;
		delete iEikEnvExtra->iViewActivator;
		delete iEikEnvExtra->iErrorResolver;
		delete iEikEnvExtra;
		iEikEnvExtra = NULL;
		}
		
	delete iProcess; // not before screen is destroyed, in case there are bitmap pictures in the document
	delete iWgName; // may be accessed during destruction of AppUi
    CCoeEnv::DestroyScreen();
    }

EXPORT_C void CEikonEnv::LeaveWithInfoMsg(TInt aResourceId,...)
/** Displays a formatted information message and then leaves.

@param aResourceId ID of a TBUF resource used to hold the string.
@param ... List of items to be formatted. */
    {
    if (aResourceId)
        {
	    VA_LIST list;
        VA_START(list,aResourceId);
        InfoMsg(aResourceId,list);
        }
    CBaActiveScheduler::LeaveNoAlert();
    }

EXPORT_C void CEikonEnv::VerboseInfoMsg(const TDesC& aDes)
/** Displays an information message if verbose information reporting has been set.

The message is not displayed if verbose information reporting has not been 
set.

@param aDes Message to display. */
	{
    if (iEikonEnvFlags[EVerboseInfoReporting])
		InfoMsg(aDes);
	}

EXPORT_C void CEikonEnv::InfoMsg(const TDesC& aDes)
/** Displays a message in the system default corner of the screen.

The message disappears after a few seconds. 

@param aDes The message to display. */
	{
    iInfoMsgWin->StartDisplay(aDes,EHRightVTop);
	}

EXPORT_C void CEikonEnv::InfoMsgWithAlignment(TGulAlignment aCorner,const TDesC& aDes)
/** Displays a message in the specified corner of the screen.

The message disappears after a few seconds. 

@param aCorner The screen corner the message is displayed in. 
@param aDes The message to display. */
	{
    iInfoMsgWin->StartDisplay(aDes,aCorner);
	}

EXPORT_C void CEikonEnv::InfoMsg(TInt aResourceId,VA_LIST aList)
/** Displays a message in the system default corner of the screen.

A TBUF resource string is used to build the message at run-time from arbitrary 
data in a similar way to C's printf(). The message disappears after a few seconds. 

@param aResourceId ID of a TBUF resource used to hold the string.
@param aList List of values to be formatted. */
    {
    TEikInfoMsgBuf formatString;
	ReadResource(formatString,aResourceId);
	
	TEikInfoMsgBuf messageString;
	messageString.FormatList(formatString,aList);
	
	InfoMsg(messageString);
    }

EXPORT_C void CEikonEnv::InfoMsg(TInt aResourceId,...)
/** Displays a message in the system default corner of the screen.

A TBUF resource string is used to build the message at run-time from arbitrary 
data in a similar way to C's printf(). The message disappears after a few seconds. 

@param aResourceId ID of a TBUF resource used to hold the string.
@param ... List of items to be formatted. */
    {
    VA_LIST list;
    VA_START(list,aResourceId);
    InfoMsg(aResourceId,list);
    }

EXPORT_C void CEikonEnv::InfoMsgWithAlignment(TGulAlignment aCorner,TInt aResourceId,VA_LIST aList)
/** Displays a message in the specified corner of the screen.

The information message is built at run-time from a formatting string 
defined as a TBUF resource and a list of arbitrary data.

@param aCorner The corner of the screen the message is displayed in.
@param aResourceId ID of a TBUF resource used to hold the string.
@param aList List of values to be formatted. */
    {
    TEikInfoMsgBuf formatString;
	ReadResource(formatString,aResourceId);
	
	TEikInfoMsgBuf messageString;
	messageString.FormatList(formatString,aList);
	
	InfoMsgWithAlignment(aCorner,messageString);
    }

EXPORT_C void CEikonEnv::InfoMsgWithAlignment(TGulAlignment aCorner,TInt aResourceId,...)
/** Displays a message in the specified corner of the screen.

The information message is built at run-time from a formatting string 
defined as a TBUF resource and a list of arbitrary data.

@param aCorner The corner of the screen the message is displayed in.
@param aResourceId ID of a TBUF resource used to hold the string.
@param ... List of items to be formatted. */
    {
    VA_LIST list;
    VA_START(list,aResourceId);
    InfoMsgWithAlignment(aCorner,aResourceId,list);
    }

EXPORT_C void CEikonEnv::InfoMsgWithDuration(const TDesC& aDes, TTimeIntervalMicroSeconds32 aDuration)
/** Displays an info message for a specified period. 

@param aDes Message to display.
@param aDuration Duration of message. */
	{
	iInfoMsgWin->StartDisplaySpecifyingDuration(aDes,EHRightVTop,aDuration);
	}

EXPORT_C void CEikonEnv::InfoMsgWithDuration(TInt aResourceId, TTimeIntervalMicroSeconds32 aDuration,...)
/** Displays an info message for a specified period. 

The text displayed is supplied in a resource file, as a string with some formatting 
information for extra arguments.  These extra arguments are supplied through the 
variable argument list which is also passed into this function.

@param aResourceId ID of a TBUF resource used to hold the string.
@param aDuration Duration of the message. 
@param ... List of values to be formatted. */	
	{
	VA_LIST list;
	VA_START(list,aDuration);
	InfoMsgWithDuration(aResourceId,aDuration,list);
	}

EXPORT_C void CEikonEnv::InfoMsgWithDuration(TInt aResourceId, TTimeIntervalMicroSeconds32 aDuration, VA_LIST aList)
/** Displays an info message for a specified period. 

The text displayed is supplied in a resource file, as a string with some formatting 
information. Values for the formatting information are supplied as extra arguments. 
These extra arguments are packaged in a VA_LIST object which is also passed 
into this function.

@param aResourceId ID of a TBUF resource used to hold the string.
@param aDuration Duration of message.
@param aList List of values. */
	{
	TEikInfoMsgBuf formatString;
	ReadResource(formatString,aResourceId);
	
	TEikInfoMsgBuf messageString;
	messageString.FormatList(formatString,aList);
	
	InfoMsgWithDuration(messageString,aDuration);
	}

EXPORT_C void CEikonEnv::InfoMsgWithAlignmentAndDuration(TGulAlignment aCorner,const TDesC& aDes, TTimeIntervalMicroSeconds32 aDuration)
/** Displays an info message with a specified alignment for a specified period. 

The text displayed is supplied in a descriptor argument, and aligned using 
the aCorner parameter.

@param aCorner The screen corner the message is displayed in. 
@param aDes Message to display.
@param aDuration Duration of message. */
	{
    iInfoMsgWin->StartDisplaySpecifyingDuration(aDes,aCorner,aDuration);
	}

EXPORT_C void CEikonEnv::InfoMsgWithAlignmentAndDuration(TGulAlignment aCorner,TInt aResourceId, TTimeIntervalMicroSeconds32 aDuration,...)
/** Displays an info message with a specified alignment for a specified period. 

The text displayed is supplied in a resource file, as a string with some formatting 
information for extra arguments.  These extra arguments are supplied through the 
variable argument list which is also passed into this function.  The text is aligned 
using the aCorner parameter.

@param aCorner The screen corner the message is displayed in. 
@param aResourceId ID of a TBUF resource used to contain the string.
@param aDuration Duration of message. 
@param ... List of values to be formatted. */
	{
	VA_LIST list;
	VA_START(list,aDuration);
	InfoMsgWithAlignmentAndDuration(aCorner,aResourceId,aDuration,list);	
	}

EXPORT_C void CEikonEnv::InfoMsgWithAlignmentAndDuration(TGulAlignment aCorner,TInt aResourceId, TTimeIntervalMicroSeconds32 aDuration,VA_LIST aList)
/** Displays an info message with a specified alignment for a specified period. 

The text displayed is supplied in a resource file, as a string with some formatting 
information. Values for the formatting information are supplied as extra arguments. 
These extra arguments are packaged in a VA_LIST object which is also passed 
into this function. The text is aligned using the aCorner parameter.

@param aCorner The screen corner the message is displayed in. 
@param aResourceId ID of a TBUF resource used to contain the string.
@param aDuration Duration of message.
@param aList List of values. */
	{
	TEikInfoMsgBuf formatString;
	ReadResource(formatString,aResourceId);
	
	TEikInfoMsgBuf messageString;
	messageString.FormatList(formatString,aList);
	
	InfoMsgWithAlignmentAndDuration(aCorner,messageString,aDuration);
	}

EXPORT_C void CEikonEnv::InfoMsgCancel()
/** Cancels the currently displaying information message. */
    {
   	if (iInfoMsgWin)
		iInfoMsgWin->CancelDisplay();
    }


/**
@internalComponent
Sets up iBusyMsgWin (pointer to non-owned interface)
*/
void CEikonEnv::PrepareBusyMsgL()
	{
	if(!iBusyMsgWin)
		iBusyMsgWin = LafEnv::NewBusyMsgWinL(*this);
	}

EXPORT_C void CEikonEnv::BusyMsgL(const TDesC& aDes)
/** Displays a flashing busy message in the system default corner of the screen.

@param aDes Message to display. */
	{
	PrepareBusyMsgL();
    iBusyMsgWin->StartDisplay(aDes,LafEnv::DefaultBusyMsgCorner());
	}

EXPORT_C void CEikonEnv::BusyMsgL(const TDesC& aDes,TGulAlignment aCorner)
/** Displays a flashing busy message in the specified corner of the screen.

@param aDes Message to display.
@param aCorner Corner of the screen in which to display the message. */
	{
	PrepareBusyMsgL();
	iBusyMsgWin->StartDisplay(aDes,aCorner);
	}

EXPORT_C void CEikonEnv::BusyMsgL(TInt aResourceId)
/** Displays a flashing busy message in the system default corner of the screen.

The message's text is read from resource.

@param aResourceId ID of the resource that specifies the text to display. */
	{
    TEikBusyMsgBuf msg; 
    ReadResource(msg,aResourceId);
	BusyMsgL(msg);
	}

EXPORT_C void CEikonEnv::BusyMsgL(const TDesC& aDes,TTimeIntervalMicroSeconds32 aInitialDelay)
/** Displays a flashing busy message in the system default corner of the screen for a specific amount of time.

@param aDes Message to display.
@param aInitialDelay Delay in microseconds before the message is first shown. */
	{
	BusyMsgL(aDes,LafEnv::DefaultBusyMsgCorner(),aInitialDelay);
	}

EXPORT_C void CEikonEnv::BusyMsgL(const TDesC& aDes,TGulAlignment aCorner,TTimeIntervalMicroSeconds32 aInitialDelay)
/** Displays a flashing busy message for a specific amount of time in the corner of the screen indicated by aCorner.

@param aDes Message to display.
@param aCorner Corner of the screen in which to display the message.
@param aInitialDelay Delay in microseconds before the message is first shown. */
	{
	PrepareBusyMsgL();
	iBusyMsgWin->StartDisplaySpecifyingInitialDelay(aDes,aCorner,aInitialDelay);
	}

EXPORT_C void CEikonEnv::BusyMsgL(TInt aResourceId,TTimeIntervalMicroSeconds32 aInitialDelay)
/** Displays a flashing busy message in the system default corner of the screen for a specific amount of time.

The message's text is read from resource.

@param aInitialDelay Delay in microseconds before the message is first shown. 
@param aResourceId The ID of a text resource specifying the message text. */
	{
    TEikBusyMsgBuf msg; 
    ReadResource(msg,aResourceId);
	BusyMsgL(msg,aInitialDelay);
	}

EXPORT_C void CEikonEnv::BusyMsgCancel()
/** Cancels any existing busy message. */
    {
	if(iBusyMsgWin) 
		iBusyMsgWin->Release();
	
	iBusyMsgWin = NULL;
    }

EXPORT_C void CEikonEnv::AddAutoMenuTitleL(CEikAutoMenuTitle* aTitle)
/** Adds a menu title to the menu bar for all applications.

Takes ownership of aTitle at the end of the function. Push the 
CEikAutoMenuTitle object on the cleanup stack before calling this method, 
and pop it after.

@param aTitle Menu title to add to all applications' menu bars. 
@publishedPartner 
@released */
	{
	if (!iAutoMenuTitleArray)
		iAutoMenuTitleArray = new(ELeave) CEikAutoMenuTitleArray();
	
	iAutoMenuTitleArray->AppendL(aTitle);
	}

EXPORT_C TEikVirtualCursor& CEikonEnv::VirtualCursor()
/** Gets the virtual cursor.

@return Virtual cursor. */
	{
	return iVirtualCursor;
	}


/**
@internalTechnology
*/
void CEikonEnv::UpdateColorListL()
	{
	if (!iColorList)
		User::Leave(KErrNotFound);

    LafEnv::UpdateColorListL( iColorList );
	LafEnv::UpdateSystemBitmapsL(*this, *iBitmapArray, *iColorList);
	}

/**
Calls Laf implementation of UpdateSystemFontsL() to update local array of system fonts
*/
EXPORT_C void CEikonEnv::UpdateSystemFontsL()
    {
    LafEnv::UpdateSystemFontsL( this, *iFontArray );
    }

/** Emits a beep. 

This method is deprecated.

@deprecated */
EXPORT_C void CEikonEnv::Beep()
    { // static
    LafEnv::Beep();
    }

/**
Framework function
*/
EXPORT_C TInt CEikonEnv::ResourceFileVersionNumber() const
    {
    return EEikResourceSignatureValue;
    }

EXPORT_C void CEikonEnv::AddWindowShadow(CCoeControl* aWinArea)
/** Adds a window shadow of the standard height to a control. */
    {
    aWinArea->DrawableWindow()->SetShadowHeight(LafEnv::ShadowHeight());
    }


EXPORT_C void CEikonEnv::SetDebugKeys(MEikDebugKeys* aDebugKeys)
/** Sets a debug keys object. This function enables the default debug 
keys to be overridden with custom ones. The debug keys object only receives 
key events in debug builds or, in release builds, if the 
CEikDebugPreferences::EFlagDebugKeysOn flag has been set.

Must be called before the environment object has been fully constructed, e.g.
from a control (widget) library initialisation function, or it will have no effect.
Must be called only once.

@param aDebugKeys A custom debug keys object. 
@publishedPartner
@released */
	{
	// Prevent malicious code from resetting the debug keys
	__ASSERT_ALWAYS(!iDebugKeys && aDebugKeys, Panic(EEikPanicDebugKeysAlreadySet));	
	iDebugKeys = aDebugKeys;
	}

/** Called by the framework to finish environment construction once the control stack 
has been created and is ready. 
*/
EXPORT_C void CEikonEnv::ControlStackReadyL()
	{
	InitDebugKeysL();		
	InitAlertWinL();
	ASSERT(!iErrorIdler);	// Assert called only once
	iErrorIdler = CEikErrorIdler::NewL();
	}

/**
@internalTechnology
*/	
void CEikonEnv::InitDebugKeysL()
	{
	if (IsEiksrvThread())
		{
		//create CEikDebugPreferences object locally for eiksrv thread
		CEikDebugPreferences* const debugPreferences = CEikDebugPreferences::NewLC();
		TRAPD(err, debugPreferences->RestoreL(FsSession()));
		if (err == KErrNoMemory) // ignore other errors
			User::Leave(err);

		const TUint flags = debugPreferences->Flags();
#ifndef _DEBUG
		if (flags & CEikDebugPreferences::EFlagDebugKeysOn)
#endif
			{
			ASSERT(iDebugKeys);
			iDebugKeys->ConstructL(); // after control stack initialized
			}
		CleanupStack::PopAndDestroy(debugPreferences);
		}
	else
		{
		REikAppUiSession uiSession;
		User::LeaveIfError(uiSession.Connect());
		CleanupClosePushL(uiSession);
		
		//Get debug preferences object from uikon server.
		CEikDebugPreferences* const debugPreferences = uiSession.GetDebugPreferencesL();
		CleanupStack::PushL(debugPreferences);
		
		if (debugPreferences->Flags() & CEikDebugPreferences::EFlagDebugKeysOn)
			{
			ASSERT(iDebugKeys);
			iDebugKeys->ConstructL(); // after control stack initialized
			}
		CleanupStack::PopAndDestroy(2); //debugPreferences & uiSession
		}
	}
	

EXPORT_C void CEikonEnv::ConstructL()
/** Second-phase constructor. 

This calls the next overload with ETrue as the parameter. */
	{
	ConstructL(ETrue);
	}

EXPORT_C void CEikonEnv::ConstructL(TBool aInitialFocusState)
/** Second-phase constructor. 

Calls the next overload with a default window group ID which will be ignored.

@param aInitialFocusState The window group's initial focus state. If ETrue, keyboard 
focus is enabled, if EFalse, keyboard focus is disabled. */
	{
	ConstructL(aInitialFocusState, 0); // 0 is not a valid window group ID and will be ignored
	}

/** Second-phase constructor. 

@param aInitialFocusState The window group's initial focus state. If ETrue, keyboard 
focus is enabled, if EFalse, keyboard focus is disabled. 
@param aWindowGroupID The window group ID of the parent window */
EXPORT_C void CEikonEnv::ConstructL(TBool aInitialFocusState, TInt aWindowGroupID)
	{
	// iEikEnvExtra might have been created in ConstructAppFromCommandLineL() so check for
	// existence before allocating it.
	if(!iEikEnvExtra)
		iEikEnvExtra = CEikEnvExtra::NewL(*this);
	
	LafEnv::HandleExtensionEventL(*this, LafEnv::ELafEnvPreCoeEnvConstructL );
	CCoeEnv::ConstructL(aInitialFocusState, iEikEnvExtra->iDefaultScreenNumber, aWindowGroupID); // Added May 04 - support for Multiple screens.
	RApaLsSession::SetFsSessionL(FsSession());
	LafEnv::HandleExtensionEventL(*this, LafEnv::ELafEnvPostCoeEnvConstructL );
	const TBool isEiksrv = IsEiksrvThread();
	// Enable wserv priority control on apps.
	if(!isEiksrv)
		User::SetPriorityControl(ETrue);
	
	if (isEiksrv)
		{
		iEikEnvExtra->iErrorResolver=CEikErrorResolver::NewL(*this);
  		iEikEnvExtra->iAppLanguage = User::Language();
		if (iEikEnvExtra->iAppLanguage != ELangNone)
			{
			// set the app language in baflutils, this is used in order to load the correct language
  			// resource files
  			BaflUtils::SetIdealLanguage(iEikEnvExtra->iAppLanguage);
			}
		}
	
	InitColorSchemeL();
	LoadParserListL();
	iLafEnv = new(ELeave) CEikLafEnv();
	iEditableControlStandardHeight = LafEnv::EditableControlStandardHeight(*iLafEnv);
	InitSystemBitmapsL();
	iWgName = CApaWindowGroupName::NewL(iWsSession);
	ReadResourceL(iNudgeChars,R_EIK_TBUF_NUDGE_CHARS);
	iVirtualCursor.SetCursorStateL(TEikVirtualCursor::EOff, *this);
	LoadLibrariesL();
	
	// Create a CEikLogicalBorder that implements the MGulLogicalBorder interface and forward 
	// the calls to the LafEnv object that actually implementing the functionality
	iLogicalBorderProxy = new(ELeave) CEikLogicalBorderProxy();
	GulTls::SetLogicalBorder(iLogicalBorderProxy);
	
	iOOMErrorText = AllocReadResourceL(iSystemResourceFileOffset+1-KErrNoMemory);
	InitInfoMsgL(); // CEikonEnv::HandleError relies on this being the last thing to be constructed (it uses it to test whether it has been fully constructed or not, and thus whether the infra-structure is in place so that it can actually handle the error)	
	}


/**
@internalComponent
*/
LOCAL_C void DeletePointerToPointer(TAny* aPointerToPointer)
	{
	delete *STATIC_CAST(CBase**, aPointerToPointer);
	}

/**
@internalComponent
*/
LOCAL_C void RemoveResourceFile(TAny* aResourceFile)
	{
	CCoeEnv::Static()->DeleteResourceFile(REINTERPRET_CAST(TInt, aResourceFile));
	}

/**
@internalComponent
*/
LOCAL_C void DeleteArrayOfResourceFilesRemovingEach(CCoeEnv& aCoeEnv, CArrayFix<TInt>* aArrayOfResourceFiles)
	{
	for (TInt i=aArrayOfResourceFiles->Count()-1; i>=0; --i)
		{
		aCoeEnv.DeleteResourceFile((*aArrayOfResourceFiles)[i]);
		}
	delete aArrayOfResourceFiles;
	}

/**
@internalComponent
*/
LOCAL_C void DeleteArrayOfResourceFilesRemovingEach(TAny* aArrayOfResourceFiles)
	{
	DeleteArrayOfResourceFilesRemovingEach(*CCoeEnv::Static(), STATIC_CAST(CArrayFix<TInt>*, aArrayOfResourceFiles));
	}

/**
@internalComponent
*/
LOCAL_C void CleanupEComImplInfoArray(TAny* aObject)
//
// Used for cleanup of objects on stack if a function leaves.
//
	{
	reinterpret_cast<RImplInfoPtrArray*>(aObject)->ResetAndDestroy();
	}


/**
This function forms part of the construction process (called by ConstructL)
Creates and populates array of libaries.
Loads ECOM plugins with interface UID KUikonLibraryUid
Adds control factories to control factory array.
Adds resource file offsets to resource file offset array

@internalComponent
*/
void CEikonEnv::LoadLibrariesL()
	{
	// Create array to store CEikLibrary classes
	iLibraries = new(ELeave) CArrayPtrFlat<CEikLibrary>(1);
	
	// Create the array for holding control (widget) factories.
	ASSERT(!iControlFactoryFuncArray);
	CArrayFix<TCreateByTypeFunction>* controlFactoryFuncArray = new(ELeave) CArrayFixFlat<TCreateByTypeFunction>(2);
	CleanupStack::PushL(TCleanupItem(DeletePointerToPointer, &controlFactoryFuncArray));
	
	// Create the array for holding resource file offsets
	ASSERT(!iResourceFileOffsetArray);
	CArrayFix<TInt>* resourceFileOffsetArray=new(ELeave) CArrayFixFlat<TInt>(2);
	CleanupStack::PushL(TCleanupItem(DeleteArrayOfResourceFilesRemovingEach, resourceFileOffsetArray));
	
	// Get the list of all ECOM control factory plug-ins
	RImplInfoPtrArray plugInArray;
	REComSession::ListImplementationsL(KUikonLibraryUid,plugInArray);

	// Push the plugin array on the stack
	CleanupStack::PushL(TCleanupItem(CleanupEComImplInfoArray, &plugInArray));
	const TInt numLibsToLoad = plugInArray.Count();
	// if the plugin count is zero dont load any thing
	for(TInt i = 0; i < numLibsToLoad; i++)
		{
		TUid implementationUid = plugInArray[i]->ImplementationUid();
		CEikLibrary2* eikLibrary = CEikLibrary2::LoadLibraryL(implementationUid);
		__ASSERT_ALWAYS(eikLibrary, Panic(EEikPanicNoLibraryEntryPoint));
		
		CleanupStack::PushL(eikLibrary);
		iLibraries->AppendL(eikLibrary);
		CleanupStack::Pop(eikLibrary);
		
		eikLibrary->InitializeL();

		// Append each of the plug-in's control factories to the common list of factories
		CArrayFix<TCreateByTypeFunction>* ctrlFactories = eikLibrary->ControlFactoryArrayL();
		if (ctrlFactories)
			{
			// we already have a control factory array so add any new factories to this
			CleanupStack::PushL(ctrlFactories);
		
			TInt count = ctrlFactories->Count();
			for (TInt jj = 0; jj < count; jj++)
				controlFactoryFuncArray->AppendL((*ctrlFactories)[jj]);
		
			CleanupStack::PopAndDestroy(ctrlFactories);
			ctrlFactories = NULL;	// don't use below
			}
			
		// Load the resource files associated with the control factories
		CArrayFix<TFileName>* resFiles = eikLibrary->ResourceFileArrayL();
		if(resFiles)
			{
			CleanupStack::PushL(resFiles);
			const TInt count = resFiles->Count();
			for(TInt ii = 0; ii < count; ii++)
				{
				TFileName& name = (*resFiles)[ii];
				if(name.Length())
					{
					BaflUtils::NearestLanguageFile(FsSession(),name);
					const TInt offset = AddResourceFileL(name);
					CleanupStack::PushL(TCleanupItem(RemoveResourceFile, reinterpret_cast<TAny*>(offset)));
					resourceFileOffsetArray->AppendL(offset);
					CleanupStack::Pop(reinterpret_cast<TAny*>(offset));
					}
				}
			CleanupStack::PopAndDestroy(resFiles);
			resFiles = NULL;	// don't use below
			}
		}

	CleanupStack::Pop(&plugInArray);
	plugInArray.ResetAndDestroy();
	plugInArray.Close();
	
	iControlFactoryFuncArray = controlFactoryFuncArray;
	iResourceFileOffsetArray = resourceFileOffsetArray;
	CleanupStack::Pop(2, &controlFactoryFuncArray);
	iAutoLoadedResourceFiles = resourceFileOffsetArray->Count(); // use this count to check that additional libraries have been removed on close
	iAutoLoadedControlFactories = controlFactoryFuncArray->Count(); // use this count to check that additional libraries have been removed on close
	}

/**
Returns control factory function array (pointer)
@internalTechnology
*/
CArrayFix<TCreateByTypeFunction>* CEikonEnv::ControlFactoryFuncArray() const
	{
	return iControlFactoryFuncArray;
	}


/**
Deletes arrays of resource file offsets, Control Factory functions and libraries.
@internalComponent
*/
void CEikonEnv::CloseLibraries()
	{
	// Delete the dynamic DLL-owned resource files
	if(iResourceFileOffsetArray)
		{
		__ASSERT_DEBUG(iResourceFileOffsetArray->Count() <= iAutoLoadedResourceFiles, Panic(EEikPanicResourceFileNotRemoved));
		DeleteArrayOfResourceFilesRemovingEach(iResourceFileOffsetArray);
		}
		
	// Assert all libraries	loaded by the application developer has be closed
	__ASSERT_DEBUG((!iControlFactoryFuncArray) || (iControlFactoryFuncArray->Count() <= iAutoLoadedControlFactories), Panic(EEikPanicControlFactoryNotRemoved));
	delete iControlFactoryFuncArray;

	// Delete all DLL-owned data
	if(iLibraries)
		{
		const TInt count = iLibraries->Count();
		for(TInt ii = 0; ii < count; ii++)
			delete (*iLibraries)[ii];
		delete iLibraries;
		}
	}


/**
Calls (virtual) PostAppUiInitializeL on all loaded libraries.

@internalTechnology
@see CEikLibrary::PostAppUiInitializeL 
*/
void CEikonEnv::PostAppUiInitializeL()
	{
	if(iLibraries)
		{
		const TInt count = iLibraries->Count();
		for(TInt ii = 0; ii < count; ii++)
			{
			TRAP_IGNORE((*iLibraries)[ii]->PostAppUiInitializeL());
			}
		}
	}


EXPORT_C TInt CEikonEnv::AddLibraryL(TCreateByTypeFunction aControlFactory, TFileName* aResourceFile)
/** Adds the control factory and resource file to the Eikon Environment.
This function does not add the control factory if it is NULL.

@param aControlFactory Control factory that has to be added to the Eikon Environment.
@param aResourceFile Resource file that has to be added to the Eikon Environment.
@return Zero, if the resource file is NULL otherwise the offset value defined for this resource file.

@publishedPartner 
@released
*/
	{
	TInt resourceFileOffset=0;
	// Add control factory function
	if(aControlFactory)
		{
		ASSERT(iControlFactoryFuncArray);
		iControlFactoryFuncArray->AppendL(aControlFactory);
		iAutoLoadedControlFactories++;
		}
		
	// Add resource file
	if(aResourceFile && aResourceFile->Length())
		{
		ASSERT(iResourceFileOffsetArray);
		BaflUtils::NearestLanguageFile(FsSession(),*aResourceFile);
		resourceFileOffset = AddResourceFileL(*aResourceFile);
		iResourceFileOffsetArray->AppendL(resourceFileOffset);
		iAutoLoadedResourceFiles++;
		}
		
	// Must be stored by calling application
	// and used when calling RemoveLibrary
	return resourceFileOffset;
	}

EXPORT_C void CEikonEnv::RemoveLibrary(TCreateByTypeFunction aControlFactory, TInt aResourceFileOffset)
/**
@internalTechnology
*/
	{
	if(aControlFactory)
		{
		ASSERT(iControlFactoryFuncArray);
		const TInt count = iControlFactoryFuncArray->Count() - 1;
		for(TInt ii = count; ii > 0; ii--)
			{
			if((*iControlFactoryFuncArray)[ii] == aControlFactory)
				{
				iControlFactoryFuncArray->Delete(ii);
				break;
				}
			}
		}
		
	if(aResourceFileOffset)
		{
		ASSERT(iResourceFileOffsetArray);
		const TInt count = iResourceFileOffsetArray->Count() - 1;
		for(TInt jj = count; jj > 0; jj--)
			{
			if((*iResourceFileOffsetArray)[jj] == aResourceFileOffset)
				{
				DeleteResourceFile(aResourceFileOffset);
				iResourceFileOffsetArray->Delete(jj);
				break;
				}
			}
		}
	}


/**
@internalComponent
*/
void CEikonEnv::InitSystemResourceFileL()
    {
	iSystemResourceFileOffset = LafEnv::LoadCoreResFileL(*this);
	iKeyPressLabels = AllocReadResourceAsDes8L(R_EIK_KEYPRESS_LABELS);
    }

/**
@internalComponent
*/
void CEikonEnv::InitPrivateResourceFileL()
    {
	iPrivateResourceFileOffset = LafEnv::LoadPrivResFileL(*this);
    }

/**
@internalComponent
*/
void CEikonEnv::InitInfoMsgL()
	{
	MEikInfoMsgWin* newInfoMsgWin = LafEnv::NewInfoMsgWinL(*this, this->RootWin());
	if (iInfoMsgWin)
		iInfoMsgWin->Release();	
	iInfoMsgWin = newInfoMsgWin;
	}

/**
@internalComponent
*/
void CEikonEnv::InitAlertWinL()
	{	
	TRAPD(err,iAlertWin->ConstructL());
	if (err)
		{
		iAlertWin->Release();
		iAlertWin=NULL;
		User::Leave(err);
		}

	iAlertWinInitialized = ETrue;
	}

EXPORT_C void CEikonEnv::AllocInfoMsg()
/** Constructs an allocation information message. 

The message includes the total number of cells allocated on the 
current thread's heap and the total space allocated to them. */
    {
    TInt allocSize = 0;
	TInt allocCount = User::Heap().AllocSize(allocSize);
    LafEnv::InfoNote(R_EIK_DBG_TBUF_ALLOC_INFO, allocCount, allocSize);
    }

EXPORT_C void CEikonEnv::WservAllocInfoMsg()
/** Creates a window server allocation information message from resource. 

The message indicates the number of resources currently open for the window 
server session. */
    {
    LafEnv::InfoNote(R_EIK_DBG_TBUF_WSERV_COUNT, iWsSession.ResourceCount());
    }

EXPORT_C void CEikonEnv::FservAllocInfoMsg()
/** Creates a file server allocation information message from resource. 

The message indicates the number of resources currently open for the file 
server session. */
    {
    LafEnv::InfoNote(R_EIK_DBG_TBUF_FSERV_COUNT, iFsSession.ResourceCount());
    }

EXPORT_C RAnimDll& CEikonEnv::ClockDllL()
/** Gets the animated DLL that is used to animate the toolbar clock of the  
application using this CEikonEnv.

@return Reference to the RAnimDll. */
    {
    if (!iClockDll)
        {
        iClockDll=new(ELeave) RAnimDll(iWsSession);
		const TDesC& clockDllName = LafEnv::ClockDllName();
        TInt err=iClockDll->Load(clockDllName);
        if (err)
            {
            iClockDll->Destroy();
            iClockDll=NULL;
            User::Leave(err);
            }
        }
    return(*iClockDll);
    }

EXPORT_C CWsBitmap* CEikonEnv::CreateBitmapL(const TDesC& aFileName,TInt aId)
/** Loads, allocates and returns a pointer to a bitmap loaded from a multi-bitmap 
file (.mbm). 

If aFileName is an empty TDesC, then a default value of 
z:\resource\uiklaf\eikon.mbm is used. If the default can't be found the alternative
default location z:\Resource\Apps\eikon.mbm will be used.
If a wildcard character ("*") is specified as the file name, the default application
resource file will be used.

If the function leaves it will also display an error dialog to the user. 

@param aFileName File name specifying the bitmap file to load. 
@param aId Number of the bitmap in the file. 
@return Pointer to the loaded bitmap. Ownership is transferred to the caller.*/
	{
	return CreateBitmapL(aFileName, aId, ETrue);
	}
	
EXPORT_C CWsBitmap* CEikonEnv::CreateBitmapL(const TDesC& aFileName,TInt aId, TBool aShowDlgIfErr)
/** Loads, allocates and returns a pointer to a bitmap loaded from a multi-bitmap 
file (.mbm). 

If aFileName is an empty TDesC, then a default value of 
z:\resource\uiklaf\eikon.mbm is used. If the default can't be found the alternative
default location z:\Resource\Apps\eikon.mbm will be used.
If a wildcard character ("*") is specified as the file name, the default application
resource file will be used.

@param aFileName File name specifying the bitmap file to load. 
@param aId Number of the bitmap in the file. 
@param aShowDlgIfErr If true then the function will also display an error dialog if it leaves. 
@return Pointer to the loaded bitmap. Ownership is transferred to the caller.*/
	{
	_LIT(KDefaultBitmapPath,"z:\\Resource\\Uiklaf\\eikon.mbm");
	_LIT(KAlternativeDefaultBitmapPath,"z:\\Resource\\Apps\\eikon.mbm");
	TPtrC cacheKey; // this is a "key" used to search for associated files in iEikEnvExtra->iLocalizedFilenameCache
	TBuf<20> cacheKeyForDefaultBitmap;
	TFileName localizedFileName;
	// check if we are dealing with the application's default bitmap file 
	const TBool isDefaultBitmap = (aFileName==KEikDefaultAppBitmapStore);
	TBool isDefaultBitmapPath = EFalse;
	if (isDefaultBitmap)
		{
		_LIT(KLitFormat,"::%08x"); // the double colon is to make it an illegal file-name so that it can never be confused with an actual file-name
		cacheKeyForDefaultBitmap.Format(KLitFormat, EikAppUi()); // using EikAppUi() for this works in the case of embedded applications in the local process, i.e. where there are multiple CCoeAppUi objects in the same process, each will need to refer to a different default bitmap-file
		cacheKey.Set(cacheKeyForDefaultBitmap);
		}
	else if (aFileName.Length()==0)
		{
		cacheKey.Set(KDefaultBitmapPath);
		isDefaultBitmapPath = ETrue;
		}
	else
		cacheKey.Set(aFileName);

	if (!iEikEnvExtra->FindLocalizedBitmapFilenameInCache(cacheKey, localizedFileName))
		{
		if (isDefaultBitmap)
			{ // use default application specific mbm file. The full path of the file is needed
			  // to deal correctly with embedded documents.
			CEikApplication* eikapp = EikAppUi()->Application();
			if (eikapp)
				localizedFileName = eikapp->BitmapStoreName();
			else
				User::LeaveNoMemory();
			}
		else
			{ // all other things, eg. ui specific mbm files, Eikon.mbm - here "cacheKey" is the unlocalized file-name
			TParsePtrC parse(cacheKey);
			if (parse.DrivePresent())
				localizedFileName=cacheKey;
			else
				{
				TFindFile findFile(iFsSession);
				CDir* dir=NULL;
				TInt error = findFile.FindWildByDir(parse.NameAndExt(), parse.Path(), dir);
				delete dir;
				if (error)
					{
					if (aShowDlgIfErr)
						{			
						ErrorContextL(error,localizedFileName);
						}
					else
						User::Leave(error);
					}
				else
					localizedFileName=findFile.File();
				}

			BaflUtils::NearestLanguageFile(iFsSession,localizedFileName);
			}

		iEikEnvExtra->CacheLocalizedBitmapFilenameL(cacheKey,localizedFileName);
		}

	CWsBitmap* tmp=new(ELeave) CWsBitmap(iWsSession);
	TInt ret=tmp->Load(localizedFileName,aId);
	if (ret)
		{
		delete(tmp);
		if (isDefaultBitmapPath)
			return CreateBitmapL(KAlternativeDefaultBitmapPath, aId, aShowDlgIfErr);

		if (aShowDlgIfErr)
			{
			ErrorContextL(ret,localizedFileName);
			}
		else
			User::Leave(ret);
		}

	tmp->SetSizeInTwips(iScreen);
	return(tmp);
	}
	
/**
@internalComponent
*/
void CEikonEnv::ErrorContextL(TInt aError,const TDesC& aContextText)
	{
	GetErrorText(ErrorText(),aError);
	BaflUtils::CopyWithTruncation(ErrorContextText(),aContextText);
	User::Leave(KErrExtendedWithText);
	}

EXPORT_C CGulIcon* CEikonEnv::CreateIconL(const TDesC& aFileName,TInt aBitmapId,TInt aMaskId)
/** Creates an icon. 

The icon is created by loading the image bitmap identified by aBitmapId and the mask 
identified by aMaskId from the resource file aFileName. It returns a pointer to the 
icon and transfers ownership.

@param aFileName The resource file name. If this is zero, the Uikon resource 
file will be used. If the wildcard character ('*') is specified, the default 
application resource file will be used. 
@param aBitmapId The bitmap ID. 
@param aMaskId The bitmap mask ID. 
@return Pointer to the created icon. */
	{
	CGulIcon* icon=CGulIcon::NewLC();
	CWsBitmap* bmp=CreateBitmapL(aFileName,aBitmapId);
	icon->SetBitmap(bmp);
	if(aMaskId!=-1)
		{
		bmp=CreateBitmapL(aFileName,aMaskId);
		icon->SetMask(bmp);
		}
	CleanupStack::Pop(); // icon
	return icon;
	}

EXPORT_C CGulIcon* CEikonEnv::CreateIconFromMaskedBitmapL(const CApaMaskedBitmap& aApaMaskedBitmap)
/** Creates an icon from a masked bitmap. 

The icon is created by copying the image bitmap and mask from the masked bitmap 
aApaMaskedBitmap. It returns a pointer to the icon and transfers ownership to the 
caller.

@param aApaMaskedBitmap The masked bitmap from which the icon is created. 
@return Pointer to the icon. */
	{ // static
	CGulIcon* icon=CGulIcon::NewLC();
	icon->SetBitmapsOwnedExternally(EFalse);
	CFbsBitmap* bitmap=new(ELeave) CFbsBitmap;
	CleanupStack::PushL(bitmap);
	User::LeaveIfError(bitmap->Duplicate(aApaMaskedBitmap.Handle()));
	CleanupStack::Pop(bitmap);
	icon->SetBitmap(bitmap);
	CFbsBitmap* mask=new(ELeave) CFbsBitmap;
	CleanupStack::PushL(mask);
	User::LeaveIfError(mask->Duplicate(aApaMaskedBitmap.Mask()->Handle()));
	CleanupStack::Pop(mask);
	icon->SetMask(mask);	
	CleanupStack::Pop(icon);
	return icon;
	}

EXPORT_C CParaFormatLayer* CEikonEnv::SystemSingleLineParaFormatLayerL()
/** Gets the single line paragraph format layer if it exists. 

If one does not exist, it calls CEikonEnv::NewDefaultSingleLineParaFormatLayerL() 
to create a new one.

@return Single line paragraph format layer. */
    {
    if (!iSingleLineParaFormatLayer)
        iSingleLineParaFormatLayer=NewDefaultSingleLineParaFormatLayerL();
    return(iSingleLineParaFormatLayer);
    }

EXPORT_C CParaFormatLayer* CEikonEnv::SystemParaFormatLayerL()
/** Gets the paragraph format layer if it exists. 

If it does not exist, it calls CEikonEnv::NewDefaultParaFormatLayerL() 
to create a new one.

@return Paragraph format layer. */
    {
    if (!iParaFormatLayer)
        iParaFormatLayer=NewDefaultParaFormatLayerL();
    return(iParaFormatLayer);
    }

EXPORT_C CCharFormatLayer* CEikonEnv::SystemCharFormatLayerL()
/** Gets the character format layer, if it exists. 

If it does not exist, it calls CEikonEnv::NewDefaultCharFormatLayerL() 
to create a new one.

@return Character format layer. */
    {
    if (!iCharFormatLayer)
        iCharFormatLayer=NewDefaultCharFormatLayerL();
    return(iCharFormatLayer);
    }

EXPORT_C CParaFormatLayer* CEikonEnv::NewDefaultSingleLineParaFormatLayerL()
/** Creates a default paragraph format layer suitable for a single line of text.

It has an inter line spacing of zero.

@return A new CParaFormatLayer suitable for a single line of text. 
The caller takes ownership.*/
    { // static
    CParaFormat* format=CParaFormat::NewLC();
	format->iLineSpacingInTwips=0;
	TParaFormatMask mask;
	mask.SetAttrib(EAttLineSpacing);
    CParaFormatLayer* layer=CParaFormatLayer::NewL(format,mask);
	CleanupStack::PopAndDestroy(); // format
	return layer;
    }

EXPORT_C CParaFormatLayer* CEikonEnv::NewDefaultParaFormatLayerL()
/** Creates a default paragraph format layer suitable for multiple lines of text.

It uses the default inter line spacing, which is UI specific.

@return A new CParaFormatLayer suitable for text that has more than one line. 
The caller takes ownership. */
    { // static
    CParaFormat* format=CParaFormat::NewLC();
	format->iLineSpacingInTwips=LafEnv::DefaultLineSpacingInTwips();
	TParaFormatMask mask;
	mask.SetAttrib(EAttLineSpacing);
    CParaFormatLayer* layer=CParaFormatLayer::NewL(format,mask);
	CleanupStack::PopAndDestroy(); // format
	return layer;
    }

#define KEikDefaultCharFormatColor KRgbBlack

EXPORT_C CCharFormatLayer* CEikonEnv::NewDefaultCharFormatLayerL()
/** Creates a default character format layer.

@return A new default CCharFormatLayer. The caller takes ownership. */
    { // static
    TCharFormatMask defaultCharFormatMask;
	TBuf<KMaxTypefaceNameLength> typeface;
	CEikonEnv* self=CEikonEnv::Static();
	self->ReadResource(typeface,R_EIK_DEFAULT_CHAR_FORMAT_TYPEFACE);

	TResourceReader reader;
	self->CreateResourceReaderLC(reader,R_EIK_DEFAULT_CHAR_FORMAT_HEIGHT);
	TInt height=reader.ReadInt16();
	CleanupStack::PopAndDestroy(); // reader

	TCharFormat defaultCharFormat(typeface,height);
	defaultCharFormatMask.SetAttrib(EAttFontTypeface);
	defaultCharFormatMask.SetAttrib(EAttFontHeight);
	LafEnv::PrepareCharFormatAndMask(defaultCharFormat,defaultCharFormatMask);
    return CCharFormatLayer::NewL(defaultCharFormat,defaultCharFormatMask);
    }

EXPORT_C void CEikonEnv::GetPrinterNamesL(CPrinterModelList* aModelNameList,CDesCArray& aPrinterNameList)
/** Gets the printer names from a CPrinterModelList.

The printer names are returned through aPrinterNameList.

@param aModelNameList Input list of printer model information. 
@param aPrinterNameList On return, contains all the printer names from aModelNameList. */
	{//static
	aPrinterNameList.Reset();
	const TInt count=aModelNameList->ModelCount();
	for (TInt i=0;i<count;i++)
		{
		TPrinterModelName name=(*aModelNameList)[i].iModelName;
		aPrinterNameList.AppendL(name);
		}
	}

EXPORT_C void CEikonEnv::LaunchPopupMenuL(TInt aResourceId,const TPoint& aTargetPos,TPopupTargetPosType aTargetType,const CEikHotKeyTable* aHotKeyTable)
/** Allows an application to launch a popup menu, by calling the app UI's 
LaunchPopupMenuL() function.

@param aResourceId ID of the resource that defines the menu to be launched.
@param aTargetPos Position of the corner of the menu identified by aTargetType.
@param aTargetType The corner of the menu by which the menu will be positioned.
@param aHotKeyTable Optional menu hotkey table. 

@publishedAll 
@released */
    {
    EikAppUi()->LaunchPopupMenuL(aResourceId,aTargetPos,aTargetType,aHotKeyTable);
    }

EXPORT_C void CEikonEnv::AddDialogLikeControlToStackL(CCoeControl* aControl)
/** Adds a dialog-like control (with a control stack priority of ECoeStackPriorityDialog) 
to the control stack.

It leaves with no alert if a control with a priority between ECoeStackPriorityDialog and 
ECoeStackPriorityFep is already being displayed by the appUi.

@param aControl The control to add. */
    {
	CEikAppUi* appUi=EikAppUi();
	if (appUi->IsDisplayingControlBetweenPriorities(ECoeStackPriorityDialog, ECoeStackPriorityCba) 
	|| appUi->IsDisplayingControlBetweenPriorities(ECoeStackPriorityCba, ECoeStackPrioritySoftkey) 
	|| appUi->IsDisplayingControlBetweenPriorities(ECoeStackPrioritySoftkey, ECoeStackPriorityFep))
		 CBaActiveScheduler::LeaveNoAlert();
	aControl->SetPointerCapture(ETrue);
    appUi->AddToStackL(aControl,ECoeStackPriorityDialog);
    }

EXPORT_C void CEikonEnv::AddAlertDialogLikeControlToStackL(CCoeControl* aControl)
/** Adds an alert dialog-like control (with a control stack priority of ECoeStackPriorityAlert) 
to the control stack. 

Alert dialogs are used to indicate errors to the user.

It leaves with no alert if a control with a priority between ECoeStackPriorityAlert 
and ECoeStackPriorityFep is already being displayed by the appUi.

@param aControl The control to add. */
    {
	CEikAppUi* appUi=EikAppUi();
	if (appUi->IsDisplayingControlBetweenPriorities(ECoeStackPriorityAlert, ECoeStackPrioritySoftkey)
	|| appUi->IsDisplayingControlBetweenPriorities(ECoeStackPrioritySoftkey, ECoeStackPriorityFep))
		CBaActiveScheduler::LeaveNoAlert();
	aControl->SetPointerCapture(ETrue);
    appUi->AddToStackL(aControl,ECoeStackPriorityAlert);
    }

EXPORT_C void CEikonEnv::AddSleepingDialogToStackL(CCoeControl* aControl)
/** Adds a sleeping dialog to the control stack, with a control stack priority 
of ECoeStackPriorityDialog.

Sleeping dialogs pre-allocate their resources - they are not initially visible.

@param aControl The control to add. */
	{
	aControl->SetPointerCapture(ETrue);
    EikAppUi()->AddToStackL(aControl,ECoeStackPriorityDialog,ECoeStackFlagRefusesAllKeys|ECoeStackFlagRefusesFocus|ECoeStackFlagSharable);
	}

EXPORT_C void CEikonEnv::AddSleepingAlertDialogToStackL(CCoeControl* aControl)
/** Adds a sleeping dialog to the control stack, with a control stack priority 
of ECoeStackPriorityAlert. 

Sleeping dialogs pre-allocate their resources - they are not initially visible.

@param aControl The control to add. */
	{
	aControl->SetPointerCapture(ETrue);
    EikAppUi()->AddToStackL(aControl,ECoeStackPriorityAlert,ECoeStackFlagRefusesAllKeys|ECoeStackFlagRefusesFocus|ECoeStackFlagSharable);
	}

EXPORT_C void CEikonEnv::RemoveFromStack(CCoeControl* aControl)
/** Removes a control from the control stack.

@param aControl The control to remove. */
    {
	CCoeAppUi* const appUi=EikAppUi();
	if (appUi)
	    appUi->RemoveFromStack(aControl);
    }

EXPORT_C void CEikonEnv::RouseSleepingDialog(CCoeControl* aControl,TBool aRoused)
/** Sets a sleeping dialog's state.

@param aControl The sleeping dialog to rouse or put to sleep. 
@param aRoused ETrue to rouse aControl, EFalse to put it to sleep. */
	{
    CEikAppUi* appUi=EikAppUi();
	appUi->UpdateStackedControlFlags(aControl,aRoused? 0: ECoeStackFlagRefusesAllKeys|ECoeStackFlagRefusesFocus,ECoeStackFlagRefusesAllKeys|ECoeStackFlagRefusesFocus);
	appUi->HandleStackChanged();
	}

EXPORT_C void CEikonEnv::DrawCursor(const CCoeControl* aControl,const TPoint& aPosition,TInt aWidth)
/** Calls the other overload of DrawCursor() using the environment's 
standard screen font for the cursor's ascent and height.

@param aControl Control to draw in.
@param aPosition Position of the cursor's baseline in the control's 
co-ordinate space.
@param aWidth Cursor width. */
    {
    DrawCursor(aControl,aPosition,aWidth,iNormalFont->AscentInPixels(),iNormalFont->HeightInPixels());
    }

EXPORT_C void CEikonEnv::DrawCursor(const CCoeControl* aControl,const TPoint& aPosition,TInt aWidth,TInt aAscent,TInt aHeight)
/** Draws the text cursor into a control with the specified position and width. 

The cursor's height and ascent are by default suitable for this CEikonEnv's 
normal font. If aControl is not focused when this function is called, a panic 
is raised.

@param aControl Control to draw into. 
@param aPosition Position of the cursor's baseline in the control's co-ordinate 
space. 
@param aWidth Cursor width. 
@param aAscent Cursor ascent. 
@param aHeight Cursor height. */
    {
    if (!aControl->IsFocused())
        Panic(EEikPanicCursorControlNotFocused);
    TTextCursor cursor;
    cursor.iType=TTextCursor::ETypeRectangle;
    cursor.iHeight=aHeight;
    cursor.iWidth=aWidth;
    cursor.iAscent=aAscent;
    cursor.iFlags=0;
    cursor.iColor=KRgbWhite;
    iRootWin.SetTextCursor(*aControl->DrawableWindow(),aPosition,cursor);
    iCursorWindow=aControl;
    }

EXPORT_C void CEikonEnv::HideCursor(const CCoeControl* aControl)
/** Removes the text cursor from a control. 

In debug builds, a panic is raised when this function is called on 
a control which is not the cursor owner.

@param aControl Control owning the cursor. */
    {
    if (aControl!=iCursorWindow)
#ifdef _DEBUG
        Panic(EEikPanicControlNotCursorOwner); // would steal cursor
#else
		return;
#endif
    iCursorWindow=NULL;
    iRootWin.CancelTextCursor();
    }

EXPORT_C TPtrC CEikonEnv::KeyPressLabel(TInt aIndex) const
/**	Returns the indexed keypress label. A keypress label is the text that 
is displayed on some buttons to identify which key press activates them. 
Examples might include Esc, Enter, Tab. Keypress labels are read from a 
resource file and are UI-specific.

@param aIndex The position of the element within the array of keypress labels.
@return The keypress label.

@publishedPartner 
@released 
*/
    {
    TResourceReader reader;
    return(reader.ReadTPtrC(aIndex, iKeyPressLabels));
    }

EXPORT_C TBool CEikonEnv::ConfirmLossOfAllChangesL() const
/** Displays a dialog asking the user to confirm that all changes will be lost to the 
current document, and returns the response.

@return Whether the user wants to lose all changes. */
	{
    return(QueryWinL(R_EIK_TBUF_CONFIRM_ALL_LOST,R_EIK_TBUF_Y_DISCARDS));
	}

EXPORT_C TBool CEikonEnv::QueryWinL(TInt aFirstLineId,TInt aSecondLineId) const
/** Requests a yes or no response from the user using a modal query dialog. 

The query text is read from the passed resource IDs.

User input cannot continue outside a modal dialog until the dialog is
dismissed, although applications can be switched.

@param aFirstLineId ID of resource describing the first line. 
@param aSecondLineId ID of resource describing the second line. 
@return User's response to the question, either ETrue or EFalse. */
	{
	return InfoWinOrQueryWinL(aFirstLineId,aSecondLineId, ETrue);
	}

EXPORT_C TBool CEikonEnv::QueryWinL(const TDesC& aFirstLine,const TDesC& aSecondLine)
/** Requests a yes or no response from the user using a modal query dialog.

@param aFirstLine First line of query text. 
@param aSecondLine Second line of query text. 
@return User's response. */
	{
	CEikonEnv *env = CEikonEnv::Static();
	ASSERT(env && env->RequestQueryDialogFunc());
	(*(env->RequestQueryDialogFunc()))();		// Call the RequestQueryDialogFunc that calls SetQueryDialog()
	MEikInfoDialog* queryDialog = env->QueryDialog();
	User::LeaveIfNull(queryDialog);
	return(queryDialog->RunDlgLD(KEikResIdQueryDialog, aFirstLine,aSecondLine));
	}

EXPORT_C void CEikonEnv::InfoWinL(TInt aFirstLineId,TInt aSecondLineId) const
/** Displays a modal information dialog with a one or two-line info message read from the 
passed resources.

@param aFirstLineId ID of the resource describing the first line. 
@param aSecondLineId ID of the resource describing the second line. */
	{
	InfoWinOrQueryWinL(aFirstLineId,aSecondLineId);
	}

EXPORT_C void CEikonEnv::InfoWinL(const TDesC& aFirstLine,const TDesC& aSecondLine)
/** Displays a modal information dialog with the specified lines of text. 

@param aFirstLine First line of dialog text. 
@param aSecondLine Second line of dialog text. */
	{
	CEikonEnv *env = CEikonEnv::Static();
	ASSERT(env->RequestInfoDialogFunc());
	(*(env->RequestInfoDialogFunc()))();	// Call the RequestInfoDialogFunc that calls SetInfoDialog()
	MEikInfoDialog* infoDialog = env->InfoDialog();
	User::LeaveIfNull(infoDialog);
	infoDialog->RunDlgLD(KEikResIdInfoDialog, aFirstLine,aSecondLine);
	}


/**
Sets up query or info box text using IDs to read from resource file.  
Calls QueryWinL or InfoWinL according to final param
@param aFirstLineId Id of resource text
@param aSecondLineId Id of resource text
@param aIsQueryWin ETrue if response expected, EFalse if info win only
@return User's response from a QueryWin, ETrue from an InfoWin
@see CEikonEnv::QueryWinL(const TDesC& aFirstLine,const TDesC& aSecondLine)
@see CEikonEnv::InfoWinL(const TDesC& aFirstLine,const TDesC& aSecondLine)
@internalComponent
*/
TBool CEikonEnv::InfoWinOrQueryWinL(TInt aFirstLineId,TInt aSecondLineId,TBool aIsQueryWin) const
	{
	HBufC* const firstLine = AllocReadResourceLC(aFirstLineId);
	const TDesC* secondLine = &KNullDesC;
	TInt numberToPopAndDestroy=1;
	if (aSecondLineId)
		{
		secondLine = AllocReadResourceLC(aSecondLineId);
		++numberToPopAndDestroy;
		}

	TBool response = ETrue;	
	if (aIsQueryWin)
		response = QueryWinL(*firstLine,*secondLine);
	else
		InfoWinL(*firstLine,*secondLine);
		
	CleanupStack::PopAndDestroy(numberToPopAndDestroy, firstLine);
	return response;
	}

EXPORT_C void CEikonEnv::SetQueryDialog(MEikInfoDialog* aQueryDialog)
/** Sets the query dialog.

@param aQueryDialog The query dialog. */
	{
	iQueryDialog = aQueryDialog;
	}

EXPORT_C void CEikonEnv::SetInfoDialog(MEikInfoDialog* aInfoDialog)
/** Sets the dialog.

@param aInfoDialog The information dialog. */
	{
	iInfoDialog = aInfoDialog;
	}

EXPORT_C MEikInfoDialog* CEikonEnv::QueryDialog() const
/** Gets the query dialog for this environment.

@return The query dialog.  */
	{
	return iQueryDialog;
	}

EXPORT_C MEikInfoDialog* CEikonEnv::InfoDialog() const
/** Gets the info dialog for this environment.

@return The info dialog. */
	{
	return iInfoDialog;
	}

EXPORT_C void CEikonEnv::SetRequestQueryDialogFunc(TRequestDialogFunc aQueryDialogFunc)
/** Sets the request query dialog.

@param aQueryDialogFunc Request query dialog. */
	{
	iQueryDialogFunc = aQueryDialogFunc;
	}

EXPORT_C void CEikonEnv::SetRequestInfoDialogFunc(TRequestDialogFunc aInfoDialogFunc)
/** Sets the request information dialog.

@param aInfoDialogFunc The request information dialog. */
	{
	iInfoDialogFunc = aInfoDialogFunc;
	}

/**
@internalComponent
@return Request query dialog
*/
TRequestDialogFunc CEikonEnv::RequestQueryDialogFunc()
	{
	return iQueryDialogFunc;
	}

/**
@internalComponent
@return Request information dialog
*/
TRequestDialogFunc CEikonEnv::RequestInfoDialogFunc()
	{
	return iInfoDialogFunc;
	}

/**
@internalComponent
@return ETrue if threadname is EIKAPPUI_SERVER_THREAD_NAME
*/
TBool CEikonEnv::IsEiksrvThread() const
	{
	TName threadName=RThread().Name();
	return (threadName.CompareC(EIKAPPUI_SERVER_THREAD_NAME)==KErrNone);
	}

//internalise printer port flag 
EXPORT_C void InternalizeL(TEikPortFlag& aThing,RReadStream& aStream)
/** Internalises the printer port flag.

This function is provided so that print dialogs can restore the 
printer port setting from the app's ini file.

@param aThing On return, contains the printer port setting read 
from the specified stream.
@param aStream Stream to read from.
@leave KErrCorrupt The printer port flag read from the stream is 
invalid.*/
	{
	TInt thing = aStream.ReadUint8L();
	if (thing > EFilePort) // or whatever the range check is
		User::Leave(KErrCorrupt);
	
	aThing = TEikPortFlag(thing);
	}

EXPORT_C CPrintSetup* CEikonEnv::NewDefaultPrintSetupL()
/** Creates and returns a pointer to a new default printer setup object.

@return A default printer setup object. */
    {
	if(!iPrintDialogFactory)
		User::Leave(KErrNotSupported);	// We used to panic here, but it's valid for this to be NULL if printing is not supported
	
	return iPrintDialogFactory->NewDefaultPrintSetupL();
    }

EXPORT_C void CEikonEnv::SetVerboseInfoReporting(TBool aVerbose)
/** Sets the Verbose Information Reporting state.

@param aVerbose ETrue to set Verbose Information Reporting, EFalse otherwise.
@publishedPartner 
@released 
*/
//@publishedAll @deprecated
	{
    iEikonEnvFlags.Assign(EVerboseInfoReporting, aVerbose);
	}

/** Use this method to set whether the application's window group shall be automatically 
brought to the foreground when the user taps on it.

@param aForwarding ETrue to set autoforwarding on, EFalse otherwise. */
EXPORT_C void CEikonEnv::SetAutoForwarding(TBool aAutoBringToForeground)
	{
    iEikonEnvFlags.Assign(EAutoForwarding, aAutoBringToForeground);
	if (aAutoBringToForeground && iForwardsCount <= 0)
		iRootWin.SetOrdinalPosition(0, ECoeWinPriorityNeverAtFront);
	}

#pragma warning( disable : 4706 )

EXPORT_C void CEikonEnv::BringForwards(TBool aForwards, TInt aPriority)
/** Repositions the root window group in the stacking hierarchy, or pushes it to 
the back. 

Calls to this function are ignored if the autoforward flag is set to ETrue.

@param aForwards ETrue to reposition the root window group at aPriority. EFalse 
to push the root window group to the back. 
@param aPriority If aForwards is ETrue then this argument determines where 
the root window group is placed in the stacking hierarchy. */
	{
	if (aForwards)
		{
		if((!iForwardsCount++) && (iEikonEnvFlags[EAutoForwarding]))
    		iRootWin.SetOrdinalPosition(0,aPriority); 
		}
	else if (!--iForwardsCount)
		{
		if (iEikonEnvFlags[EAutoForwarding])
			{
   			iRootWin.SetOrdinalPosition(0,ECoeWinPriorityNeverAtFront); 
			}
		} 
	}
	
#pragma warning( default : 4706 )

EXPORT_C MPictureFactory* CEikonEnv::PictureFactory() const
/** Gets the picture factory for this environment.

@return The picture factory. */
	{
	return const_cast<MPictureFactory*>(&iEikEnvExtra->PictureFactory());	// this method should have returned const
	}

/** Gets a picture factory object in the environment which supports the specified 
picture type. 

If none exists, then the function returns NULL.

@param aPictureType The picture type.
@return A picture factory which supports the picture type aPictureType. NULL 
if no such factory exists in this environment. */
EXPORT_C MEikPictureFactory* CEikonEnv::ExtendedPictureFactory(TUid aPictureType) const
	{
	if (aPictureType != KUidPictureTypeDoor)
		{
		const TInt count=iEikEnvExtra->PictureFactories().Count();
		for (TInt ii=0; ii < count; ii++)
			{
			const MEikPictureFactory& factory = iEikEnvExtra->PictureFactory(ii);
			if (factory.SupportsPictureType(aPictureType))
				return const_cast<MEikPictureFactory*>(&factory);	// this method should have returned const
			}
		}

	return NULL;
	}

EXPORT_C void CEikonEnv::AddPictureFactoryL(MEikPictureFactory& aFactory)
/** Adds the picture factory to the set of factories maintained by the Uikon environment.

@param aFactory The picture factory to add. */
	{
	iEikEnvExtra->AppendPictureFactoryL(&aFactory);
	}

EXPORT_C void CEikonEnv::RemovePictureFactory(TUid aFactoryId)
/** Removes the specified picture factory, if it exists, from the set of picture 
factories owned by the Uikon environment.

@param aFactoryId The Id of the picture factory to be removed. */
	{
	TInt ii = iEikEnvExtra->PictureFactories().Count();
	while (ii > 0)
		{
		ii--;
	    const MEikPictureFactory& factory = iEikEnvExtra->PictureFactory(ii);
	    if (factory.Id() == aFactoryId)
			{
			iEikEnvExtra->DeletePictureFactory(ii);
			// Should really return here, but BR was not approved (see BR2081)
			}
		}
	}

// duplicated in EIKPROC.CPP
const TUid KUidEikLastOpenFile={0x100000fb};


/**
For debugging purposes only.  Set __UHEAP_SETFAIL using command line parameter
@internalComponent
@param command line
*/
void CEikonEnv::SetCommandLineDebugMemFailL(const CApaCommandLine& aCommandLine)
	{
#if !defined(_DEBUG)
	(void)aCommandLine;
#else
	const TInt debugMemFail=aCommandLine.DebugMemFail();
	if (debugMemFail!=0)
		{
		__UHEAP_SETFAIL(RHeap::EFailNext, debugMemFail);
		}
#endif
	}

EXPORT_C void CEikonEnv::ConstructAppFromCommandLineL(const TApaApplicationFactory& aApplicationFactory,const CApaCommandLine& aCommandLine)
/** Initialises an application

Constructs a new application consisting of a CEikAppUi, a CEikApplication, 
and a CEikDocument. The new application starts with a new controlling 
process and runs in this Uikon environment. The new application is passed 
any command line file using the function CEikAppUi::ProcessCommandParametersL().

@param aApplicationFactory The factory to use to create the application
@param aCommandLine The command line used to initialise the new application.
@see TApaApplicationFactory */
	{
	 // Check if there was an error in CCoeEnv's c'tor. Leave if there was.
 	const TInt coeEnvConstructionError = CoeEnvConstructorError();
 	User::LeaveIfError(coeEnvConstructionError);

	// Construct iEikEnvExtra here so that the app language can be stored in it
	if (!iEikEnvExtra)
		iEikEnvExtra = CEikEnvExtra::NewL(*this);
	
	TApaCommand command = aCommandLine.Command();
	
	// Connect to the AppArc server
	RApaLsSession apparcServer; 
	CleanupClosePushL(apparcServer);
	TInt err = apparcServer.Connect();
	
	// Store application language for later use
	StoreAppLanguageL(apparcServer);
	
	// Set default screen
	if (aCommandLine.IsDefaultScreenSet())	// Either use the command line parameter if set
		iEikEnvExtra->iDefaultScreenNumber = aCommandLine.DefaultScreen();
	else
		{	// Or use the default screen for the application, kept by AppArc
		if (!err)
			err = apparcServer.GetDefaultScreenNumber(iEikEnvExtra->iDefaultScreenNumber, RProcess().Type()[2]);
		
		if (err)
			iEikEnvExtra->iDefaultScreenNumber = 0;
		}
	// Close AppArc server session
	CleanupStack::PopAndDestroy(&apparcServer);
	
	// Construct application environment
	const TBool startAppInForeground = (command!=EApaCommandBackground && command!=EApaCommandBackgroundAndWithoutViews);
	ConstructL(startAppInForeground, aCommandLine.ParentWindowGroupID());
		
	// Init instrumentation (i.e. profiling) of application startup
	SetAppStartupInstrumentationEventIdBaseL(aCommandLine.AppStartupInstrumentationEventIdBase());
	
	// Create the application process
	iProcess = CEikProcess::NewL(iFsSession, aCommandLine.ParentProcessId());
			
	// Start application as "application server"?
	const TUint serverDifferentiator = aCommandLine.ServerRequired();
	if (serverDifferentiator)
		iEikonEnvFlags.Set(EStartedAsServerApp);
	
#ifdef _DEBUG
	SetCommandLineDebugMemFailL(aCommandLine);
#endif // _DEBUG

	// Push the application to the background?
	if (!startAppInForeground)
		{
		iRootWin.SetOrdinalPosition(-1000);
		iRootWin.EnableReceiptOfFocus(ETrue);
		if (RProcess().Priority() <= EPriorityForeground)
			RThread().SetProcessPriority(EPriorityBackground); 
		}

	// Create the document object using the application factory
	CEikDocument& doc = *static_cast<CEikDocument*>(iProcess->AddNewDocumentL(aApplicationFactory));
	iProcess->SetMainDocument(&doc);
	UpdateTaskNameL();
	
	// Create app server if requested
	if(serverDifferentiator)
		{
		CApaAppServer* server = NULL;
		CApaApplication* app = doc.Application();
		app->NewAppServerL(server);
		iEikEnvExtra->iAppServer = static_cast<CEikAppServer*>(server);
		iEikEnvExtra->iAppServer->ConstructUniqueL(serverDifferentiator, app->AppDllUid());
		}

	// Prepare the document for editing, this includes creating the AppUi object
	doc.PrepareToEditL(); // creates AppUi
	CEikAppUi& appUi = *EikAppUi();
	
	// Unless we are running the application without views, initialize the view manager
	const TBool runAppWithoutViews = (command==EApaCommandRunWithoutViews || command==EApaCommandBackgroundAndWithoutViews);
	if (!runAppWithoutViews)
		appUi.CheckInitializeViewsL(appUi.Application()->AppDllUid());

	// If the application is starting in the foreground, create a high-priority async view activator, 
	// as the ViewSrv won't activate the top view automatically
	if (startAppInForeground && command!=EApaCommandViewActivate )
		iEikEnvExtra->iViewActivator = CEikStartUpViewActivator::NewL(appUi, *this, iEikEnvExtra->iViewActivator);
	
	// Get the file name associated with the document, and set it on the process CApaProcess object
	const TBool doOpen = appUi.ProcessCommandParametersL(const_cast<CApaCommandLine&>(aCommandLine));
	TUnlimitedFileName* const modifiedDocumentName = TUnlimitedFileName::NewLC(aCommandLine.DocumentName());
	iProcess->SetMainDocFileNameL(*modifiedDocumentName);
	UpdateTaskNameL();
	
	
	TBool openByFileName = (modifiedDocumentName->Length());
	CFileStore* docStore = NULL;
	CleanupStack::PushL(TCleanupItem(DeletePointerToPointer, &docStore));
	
	RFile file;
	CleanupClosePushL(file);
	aCommandLine.GetFileByHandleL(file);
	TBool receivedFileHandle=EFalse;
	if (file.SubSessionHandle() != KNullHandle)
		{
		receivedFileHandle = ETrue;
		CFileStore* const KIllegalPointer=(CFileStore*)0x1;
		docStore = KIllegalPointer;
		TRAP(err, doc.OpenFileL(docStore, file));

		if ((err) || (docStore != KIllegalPointer)) // if the OpenFileL call in the statement above sets docStore either to a real object or to NULL, then we don't want to open the file by name (i.e. we don't want to call the 3-parameter overload of OpenFileL below) as we've already opened the file by file-handle here)
			openByFileName = EFalse;
		if (docStore == KIllegalPointer)
			docStore = NULL;
		else
			receivedFileHandle = EFalse;
		}
		
	CleanupStack::PopAndDestroy(&file);
	if (openByFileName)
		{
		TRAP(err, docStore = doc.OpenFileL(doOpen, *modifiedDocumentName, FsSession()));
		}
		
	if (err==KErrCorrupt || err==KErrEof)
        {
        if (LafEnv::PolicyItem( LafEnv::ELafEnvPolicyDeleteCorruptDocumentAndContinue))
            {
		    // The document is bust, so throw it away.
		    User::LeaveIfError(FsSession().Delete(*modifiedDocumentName));
		    if (doOpen)
			    {
			    // Create new file.
			    docStore = doc.OpenFileL(EFalse, *modifiedDocumentName, FsSession());
			    // Alert the user that we've thrown away their data, but don't leave.
			    HandleError(err);
			    err = KErrNone;
			    }
            }
        }

	if (err==KErrCorrupt || err==KErrEof)
		{ // remove "last used file" stream from app ini file
		CDictionaryStore* iniFile=appUi.Application()->OpenIniFileLC(FsSession());
		if (iniFile!=NULL)
			{
			iniFile->RemoveL(KUidEikLastOpenFile);
			iniFile->CommitL();
			CleanupStack::PopAndDestroy(iniFile);
			}
		}
	User::LeaveIfError(err);
	if (docStore)
	    {
	    doc.SetEditStoreWithoutAppUiNotificationL(docStore);
	    iProcess->SetMainStore(docStore); // takes ownership of docStore
	    }
   	CleanupStack::Pop(&docStore);
   	
	if ((modifiedDocumentName->Length()>0) || receivedFileHandle)
		appUi.HandleModelChangeL();

    CleanupStack::PopAndDestroy(modifiedDocumentName);

    // If not, the app will Rendezvous at its convenience.
    if( AppUi()->FrameworkCallsRendezvous() )
		RProcess::Rendezvous(KErrNone);
    	
 	SetAppReady();
	}

EXPORT_C void CEikonEnv::UpdateTaskNameL()
/** Updates the process and thread name from the caption. */
	{
	CEikDocument* eikDoc = (CEikDocument*)(iProcess->MainDocument());
	eikDoc->UpdateTaskNameL(iWgName);
	// Create a local copy of the CApaWindowGroupName's caption descriptor.
	TBuf<KMaxFileName> caption( iWgName->Caption() );
	
	// Adjust the caption name such that it satisfies the following conditions:-
	// - Its length should not exceed 66 characters. An additional 14 chars(giving the maximum of 80) are added by the kernel. 
	// - ASCII character less than 0x20 or greater than 0x7e should be removed.
	// - Special characters '?' ':' '*' should be replaced by '_'.
	const TInt maxCaption = 66;
	TBool setCaption = EFalse;
	
	if( caption.Length() > maxCaption )
		{
		caption.SetLength( maxCaption );
		
		setCaption = ETrue;
		}

	TInt i = 0;
	for(; i < caption.Length(); i++ )
		{
		if( ((caption[ i ] < 0x20) || (caption[ i ] > 0x7e))
		||  (('?' == caption[ i ]) || (':' == caption[ i ]) || ('*' == caption[ i ])) )
			{
			caption[ i ] = '_';
			
			setCaption = ETrue;
			}
		
		}

	if( setCaption )
		{
		iWgName->SetCaptionL( caption );
		}
	
	User::LeaveIfError( User::RenameThread(caption) );
	User::LeaveIfError( User::RenameProcess(caption) );
	iWgName->SetWindowGroupName(iRootWin);
	}

EXPORT_C void CEikonEnv::DisplayTaskList() 
/** Displays tasks present in the Task List.
@publishedAll 
@released 
*/
	{
	TEikServEvent taskListMsg=EEikServShowTaskList;
	SendEventToEikonServer(EEventUser, &taskListMsg, sizeof(taskListMsg));
	}

EXPORT_C void CEikonEnv::DismissTaskList() 
/** Causes the task list, if displayed, to be closed.
@publishedAll 
@released 
*/
	{
	TEikServEvent taskListMsg=EEikServHideTaskList;
	SendEventToEikonServer(EEventUser, &taskListMsg, sizeof(taskListMsg));
	}

EXPORT_C void CEikonEnv::SendEventToEikonServer(TInt aEvent,const TAny* aPtr,TInt aLength)
/** Sends the event to the Eikon Server.

@param aEvent Event that has to be sent to Eikon Server.
@param aPtr Pointer to the message that has to be sent to Eikon Server.
@param aLength Length of the message that has to be sent to Eikon Server.

@publishedPartner 
@released
*/
	{
    TWsEvent event;
	event.SetType(aEvent);
	if (aLength>TWsEvent::EWsEventDataSize)
		Panic(EEikPanicOverlongEikonServerMessage);
	Mem::Copy(event.EventData(),aPtr,aLength);
	TInt wgId=iWsSession.FindWindowGroupIdentifier(0, __EIKON_SERVER_NAME, 0);
	iWsSession.SendEventToWindowGroup(wgId,event);
	}

EXPORT_C void CEikonEnv::SetBusy(TBool aBusy)
/** Sets the application's busy state.

@param aBusy ETrue to set as busy, EFalse otherwise. */
	{
	TBool busyChanged=EFalse;
	if (aBusy)
		{
		if (!iBusyCount++)
			{
			iWgName->SetBusy(ETrue);
			busyChanged=ETrue;
			}
		}
	else
		{
		if (!--iBusyCount)
			{
			iWgName->SetBusy(EFalse);
			busyChanged=ETrue;
			}
		}
	if (busyChanged)
		iWgName->SetWindowGroupName(iRootWin);
	}

EXPORT_C TBool CEikonEnv::IsBusy() const
/** Tests whether the application is marked as busy.

@return ETrue if the application is busy, EFalse otherwise. */
	{
	return iWgName->IsBusy();
	}

EXPORT_C void CEikonEnv::SetSystem(TBool aSystem)
/** Sets the application's system attribute.

While the system attribute is set, the application cannot be closed down e.g. by using
the @c TApaTask::EndTask function unless the requester has the capability PowerMgmt.

@param aSystem ETrue to set the system attribute, EFalse to unset it. */
	{
	iWgName->SetSystem(aSystem);
	iWgName->SetWindowGroupName(iRootWin);
	}

EXPORT_C TBool CEikonEnv::IsSystem() const
/** Tests the value of the system attribute.

@return ETrue if the system attribute is set, otherwise EFalse. */
	{
	return iWgName->IsSystem();
	}

EXPORT_C void CEikonEnv::SetDocNameIsAFile(TBool aDocNameIsAFile)
/** Sets whether a document name is a file.

@param aDocNameIsAFile ETrue to set the document name as a file, EFalse otherwise. */
	{
	iWgName->SetDocNameIsAFile(aDocNameIsAFile);
	iWgName->SetWindowGroupName(iRootWin);
	}

EXPORT_C TBool CEikonEnv::DocNameIsAFile() const
/** Tests whether the document name is a file.

@return ETrue if the document name is a file. EFalse otherwise. */
	{
	return iWgName->DocNameIsAFile();
	}

EXPORT_C void CEikonEnv::SetRespondsToShutdownEvent(TBool aRespondsToShutdownEvent)
/** Sets whether the application responds to shutdown events.

@param aRespondsToShutdownEvent ETrue if the application responds to shutdown 
events, EFalse otherwise. */
	{
	iWgName->SetRespondsToShutdownEvent(aRespondsToShutdownEvent);
	iWgName->SetWindowGroupName(iRootWin);
	}

EXPORT_C TBool CEikonEnv::RespondsToShutdownEvent() const
/** Tests whether the application responds to shutdown events.

@return ETrue if the application responds to shutdown events, EFalse otherwise. */
	{
	return iWgName->RespondsToShutdownEvent();
	}

EXPORT_C void CEikonEnv::SetRespondsToSwitchFilesEvent(TBool aRespondsToSwitchFilesEvent)
/** Sets whether the application responds to switch files events.

@param aRespondsToSwitchFilesEvent ETrue if the application responds to switch 
files events, EFalse otherwise. */
	{
	iWgName->SetRespondsToSwitchFilesEvent(aRespondsToSwitchFilesEvent);
	iWgName->SetWindowGroupName(iRootWin);
	}

EXPORT_C TBool CEikonEnv::RespondsToSwitchFilesEvent() const
/** Tests whether an application responds to switch files events.

@return ETrue if the application responds to switch files events, EFalse otherwise. */
	{
	return iWgName->RespondsToSwitchFilesEvent();
	}

EXPORT_C CColorList* CEikonEnv::CreateSystemColorListL()
/** Creates and returns a system colour list, which is a palette of standard 
colours used by the system.

The list is read from a system colour scheme file. The function returns NULL
if no such file can be found. In this case, clients are expected to create 
the list using some other means (typically from a resource file).

@return Pointer to the system colour list, or NULL. */
	{
	return CCoeDataStorage::GetL(*this).GetSystemColorListL();
	}

EXPORT_C CColorList* CEikonEnv::CreateSystemColorListL(const CColorList& aColorList)
/** Creates and returns a system colour list, which is a palette of standard 
colours used by the system, and merges it with the colour list specified.
CColorList::AddColorArrayL() should be called before this function.

@param aColorList The color list to merge in.
@return Pointer to the system colour list. */
	{
	CColorList* colorList = CreateSystemColorListL();
	if(colorList)
		CleanupStack::PushL(colorList);
	else
		colorList = CColorList::NewLC();

	colorList->MergeL(aColorList);
	CleanupStack::Pop(colorList);
	return colorList;
	}

EXPORT_C void CEikonEnv::UpdateSystemColorListL(const CColorList& aColorList)
/** Replaces the system colour list with the list specified.

If no system colour list exists, one is created.

@param aColorList The new colour list.
@capability WriteDeviceData		To protect against tampering.
*/
	{
	CCoeDataStorage::GetL(*this).SetSystemColorListL(aColorList);
	}

EXPORT_C TRgb CEikonEnv::ControlColor(TLogicalColor aLogicalColor, const CCoeControl& aControl) const
/** Gets the physical (TRgb) colour which corresponds to the logical colour specified 
from the application's colour list.

If the colour of the control specified in aControl has been overridden using 
CCoeControl::OverrideColorL(), this function will return the overridden colour.

@param aLogicalColor A logical colour value. 
@param aControl A pointer to the control itself. 
@return The physical colour which corresponds to aLogicalColor. */
	{
	TRgb color = Color(aLogicalColor);		// Get default color
	aControl.GetColor(aLogicalColor, color);	// Get overriden color, if any
	return color;
	}

/**
Creates and populates a colour list, a palette of standard colours used by the system.
If the first attempt fails a separate executable, Z:\\SYS\\BIN\\UPDATESYSTEMCOLORLIST.EXE, is run to update system colours.
@return populated colour list.  Ownership is passed to caller.
*/
// Export this for >9.0 but not before
EXPORT_C CColorList* CEikonEnv::PopulateColorArrayL()
	{
	CColorList* colorList = CreateSystemColorListL();
	if (!colorList)
		{
		_LIT(KExeName,"Z:\\SYS\\BIN\\UPDATESYSTEMCOLORLIST.EXE");
		RProcess process;
		TRequestStatus processState;
		const TInt err = process.Create(KExeName,KNullDesC);
	  	User::LeaveIfError(err);
		CleanupClosePushL(process);
		process.Logon(processState);
		process.Resume();
		User::WaitForRequest(processState);
		CleanupStack::PopAndDestroy(&process);
		colorList = CreateSystemColorListL();
		}
	return colorList;
	}

/**
@internalComponent
*/
void CEikonEnv::InitColorSchemeL()
	{
	if (!iColorList)
        iColorList = LafEnv::CreateColorListL(*this);
	}

/**
@internalComponent
*/
LOCAL_C void ReleaseParser(TAny* aSelf)
	{REINTERPRET_CAST(MParser*,aSelf)->Release();}

/**
@internalComponent
*/
void CEikonEnv::LoadParserListL()
	{
	TInt index=0;
	FOREVER
		{
		MParser* parser = LafEnv::CreateTextParserL(index++);
		if (!parser)
			break;
		
		CleanupStack::PushL(TCleanupItem(ReleaseParser,parser));
		CRichText::ActivateDefaultParserL(parser);
		CleanupStack::Pop(); // parser
		}
	}


EXPORT_C void CEikonEnv::SetAppUiFactoryL(MEikAppUiFactory* aAppUiFactory)
/**
@internalComponent  
*/
	{
	if (!iAppUiFactoryArray)
		iAppUiFactoryArray = new(ELeave) CArrayFixFlat<TEikAppUiFactory>(1);
	
	AddAppUiFactoryL(aAppUiFactory);
	}

EXPORT_C MEikAppUiFactory* CEikonEnv::AppUiFactory() const
/** Gets the application UI factory object.

This object implements the MEikAppUiFactory interface.

@return App UI factory interface or NULL. */
	{
	const TInt index = iAppUiFactoryArray->Count() - 1;
	return (index >= 0 ? (*iAppUiFactoryArray)[index].iFactory : NULL);
	}

EXPORT_C MEikAppUiFactory* CEikonEnv::AppUiFactory(const CEikAppUi& aAppUi) const
/** Gets the application UI factory object for the specified app UI.

If the specified app UI does not exist in this environment, the function returns 
NULL. Otherwise the function returns an object which implements the MEikAppUiFactory 
interface. 

@param aAppUi The app UI for this application.
@return The app UI factory object, or NULL if aAppUi does't exist in this environment. */
	{
	MEikAppUiFactory* ret = NULL;
	for (TInt ii=iAppUiFactoryArray->Count();--ii>=0;)
		{
		TEikAppUiFactory factory=(*iAppUiFactoryArray)[ii];
		if (factory.iAppUi==&aAppUi || (ii==0 && !aAppUi.ContainerAppUi()))
			{
			ret=factory.iFactory;
			break;
			}
		}
	return ret;
	}


EXPORT_C void CEikonEnv::AddAppUiFactoryL(MEikAppUiFactory* aAppUiFactory)
/**
@internalComponent 
*/
	{
	TEikAppUiFactory factory;
	factory.iAppUi = EikAppUi();
	factory.iFactory = aAppUiFactory;
	iAppUiFactoryArray->AppendL(factory);
	}

EXPORT_C void CEikonEnv::RemoveAppUiFactory()
/**
@internalComponent 
*/
	{
	const TInt index = iAppUiFactoryArray->Count() - 1;
	iAppUiFactoryArray->Delete(index);
	}

/**
@publishedPartner
@deprecated

Use CCoeStatic instead
*/
EXPORT_C void CEikonEnv::SetExtension(CBase* aExtension)
	{
	delete iExtension;
	iExtension = aExtension;
	}


EXPORT_C void CEikonEnv::WriteInternalStateOfStackedControlsL()
/**
Writes the internal state of all CCoeControls on the control stack into a file
c:\\debuglog_#APPNAME#(#NUMBER#) in the Symbian OS filing system. Works in debug mode only.

@internalTechnology
*/
	{
	#ifdef _DEBUG
	_LIT(KStdLogFilePrefix,":\\Debug_log_%S");	
	TFileName fileName;
	RBuf stdLogFormat;
	TChar sysDrive = RFs::GetSystemDriveChar();
	TInt maxSizeOfFileName = KStdLogFilePrefix().Length() + 1;
	stdLogFormat.CreateL(maxSizeOfFileName);
	stdLogFormat.Append(sysDrive);
	stdLogFormat.Append(KStdLogFilePrefix());
	stdLogFormat.CleanupClosePushL();
	fileName.Format(stdLogFormat,&(EikAppUi()->Application()->AppCaption()));
	CleanupStack::PopAndDestroy(&stdLogFormat);
	CApaApplication::GenerateFileName(iFsSession,fileName);
	RFileWriteStream writeStream;
	writeStream.PushL();
	User::LeaveIfError(writeStream.Create(iFsSession,fileName,EFileWrite));
	EikAppUi()->WriteInternalStateOfStackedControlsL(writeStream);
	writeStream.CommitL();
	CleanupStack::PopAndDestroy(); //writeStream.Close()
	#endif
	}

EXPORT_C const CFbsBitmap* CEikonEnv::TexturedBitmap() const
/**	
@publishedAll 
@deprecated
*/
	{
	TUid uid = TUid::Uid(KLafUidEikonTexturedVal);
	return LafEnv::MatchBitmap(*iBitmapArray, uid);
	}

EXPORT_C const CFbsBitmap* CEikonEnv::GrayBitmap() const
/**
@publishedAll 
@deprecated
*/
	{
	const TUid uid = TUid::Uid(KLafUidEikonGrayVal);
	return LafEnv::MatchBitmap(*iBitmapArray, uid);
	}

EXPORT_C const CFbsBitmap* CEikonEnv::OptionBitmap() const
/** Gets the bitmap that is used by horizontal option buttons in this 
environment.

@publishedAll 
@deprecated

@return A pointer to the option bitmap. */
	{
	const TUid uid = TUid::Uid(KLafUidEikonOptiVal);
	return LafEnv::MatchBitmap(*iBitmapArray, uid);
	}

EXPORT_C const CFbsBitmap* CEikonEnv::HighlightedOptionBitmap() const
/**	
@internalComponent 
*/
	{
	TUid uid = TUid::Uid(KLafUidEikonOptihVal);
	return LafEnv::MatchBitmap(*iBitmapArray, uid);
	}

EXPORT_C const CFbsBitmap* CEikonEnv::OptionMaskBitmap() const
/**	
@publishedAll 
@deprecated
*/
	{
	const TUid uid = TUid::Uid(KLafUidEikonOptimVal);
	return LafEnv::MatchBitmap(*iBitmapArray, uid);
	}

EXPORT_C const CFbsBitmap* CEikonEnv::Bitmap(TUid aBmpUid) const
/** Gets the specified bitmap. 

This function returns a bitmap from the list of bitmaps by using the UID as an index.

@param aUidBmp The UID of the bitmap to retrieve. 
@return Pointer to the bitmap. */
	{
	return LafEnv::MatchBitmap(*iBitmapArray, aBmpUid);
	}

EXPORT_C MLafEnv& CEikonEnv::LafEnv() const
/**	
@publishedPartner 
@released
*/
	{
	return *iLafEnv;
	}

EXPORT_C TDisplayMode CEikonEnv::DefaultDisplayMode() const
/** Gets the default display mode for the window server session with the maximum 
possible number of colours.

@return Default display mode. */
	{
	TInt numGrays = 0;
	TInt numColors = 0;
	return WsSession().GetDefModeMaxNumColors(numColors, numGrays);
	}

/**
@internalComponent
*/
void CEikonEnv::SetAppReady()
	{
	iWgName->SetAppReady(ETrue);
	iWgName->SetWindowGroupName(iRootWin);
	}

EXPORT_C CEikAppServer* CEikonEnv::AppServer() const
/** Gets required application server for running the application.

@return Pointer to the application server which is derived from CEikAppServer. */
	{
	if (iEikEnvExtra)
		return iEikEnvExtra->iAppServer;
	else
		return NULL;
	}

EXPORT_C TBool CEikonEnv::StartedAsServerApp() const
/** Gets whether server is required or not.

@return ETrue if application requires a server, EFalse otherwise. */
	{
	return iEikonEnvFlags[EStartedAsServerApp];
	}

/**
Sets language in iEikEnvExtra and baflutils. Gets language from application if possible, device otherwise.
@param aLsSession  (open) session to apparc server
@internalComponent
*/
void CEikonEnv::StoreAppLanguageL(const RApaLsSession& aLsSession)
	{
	TBool err = KErrNone;
	const TBool validSession = aLsSession.Handle();
	if(validSession)
		{
		// Get the app UID from the process, then use it to get the application language 
		// from apparc 
		const TUid appUid(RProcess().Type()[2]);
		err = aLsSession.ApplicationLanguage(appUid, iEikEnvExtra->iAppLanguage);
		}

	// If we can't get the language successfully then set it to the language of the device  	
	if(err || !validSession)
		iEikEnvExtra->iAppLanguage = User::Language();	

	// Set the app language in baflutils, this is used in order to load the correct language
	// resource files
	if (iEikEnvExtra->iAppLanguage != ELangNone)
		User::LeaveIfError(BaflUtils::SetIdealLanguage(iEikEnvExtra->iAppLanguage));
	else // In the case of ELangNone, set the app-language to be the device's language
		iEikEnvExtra->iAppLanguage = User::Language();	// Don't set ideal language (see PDEF102771)

	}


/**
@internalTechnology
*/	
TLanguage CEikonEnv::ApplicationLanguage() const
	{
	return iEikEnvExtra->iAppLanguage;
	}

/**
@internalTechnology
*/	
void CEikonEnv::PostAppUiDestroy()
    {
    CloseLibraries();

    delete iAppUiFactoryArray;
    iAppUiFactoryArray = NULL;  

    delete iAutoMenuTitleArray;  
    iAutoMenuTitleArray = NULL;
    }

/**
@internalTechnology
*/  
TInt CEikonEnv::ConstructorError() const
    {
    return CoeEnvConstructorError();
    }

EXPORT_C void CEikonEnv::CEikonEnv_Reserved_1()
	{
	}
	
EXPORT_C void CEikonEnv::CEikonEnv_Reserved_2()
	{
	}
	
EXPORT_C void CEikonEnv::CEikonEnv_Reserved_3()
	{
	}
	
EXPORT_C void CEikonEnv::CEikonEnv_Reserved_4()
	{
	}
	
EXPORT_C void CEikonEnv::CEikonEnv_Reserved_5()
	{
	}
	
EXPORT_C void CEikonEnv::CEikonEnv_Reserved_6()
	{
	}
	
EXPORT_C void CEikonEnv::CEikonEnv_Reserved_7()
	{
	}
	
EXPORT_C void CEikonEnv::CEikonEnv_Reserved_8()
	{
	}
	
EXPORT_C void CEikonEnv::CEikonEnv_Reserved_9()
	{
	}
	
EXPORT_C void CEikonEnv::CEikonEnv_Reserved_10()
	{
	}

