// Copyright (c) 2001-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include <barsc2.h>
#include <barsread2.h>
#include <bautils.h>
#include <apgcli.h>
#include <apsscan.h>

#include "eikerror.h"
#include <uikon.hrh>
#include "eikdefconstinternal.h"
#include "eikdefconst.h"
#include <errorres.rsg>

_LIT(KErrorResDirName,"?:\\Resource\\Errors\\*.R*");
_LIT(KAppErrorResDirName,"?:\\Resource\\Apps_Errors\\*_errors.R*");

const TUint16 KFirstDriveLetter='A';
const TUid KUidErrorResourceFileType = { 0x102027BD };

//
// class CErrorFileFsMonitor
//

NONSHARABLE_CLASS(CErrorFileFsMonitor) : public CBase
	{
public:
	static CErrorFileFsMonitor* NewLC(RFs& aFs, CEikErrorResolver& aErrorResolver, const TDesC& aPath);
	~CErrorFileFsMonitor();
	inline const TDesC& Path() const;
private:
	inline CErrorFileFsMonitor(CEikErrorResolver& aErrorResolver);
	void ConstructL(RFs& aFs, const TDesC& aPath);
	inline void Start();
	static TInt FsMonitorCallBack(TAny* aSelf);
	void HandleFsMonitorCallBack();
private:
	CApaFsMonitor* iMonitor;
	CEikErrorResolver& iErrorResolver;
	HBufC* iPath;
	};

inline CErrorFileFsMonitor::CErrorFileFsMonitor(CEikErrorResolver& aErrorResolver)
	: iErrorResolver(aErrorResolver), iPath(NULL)
	{
	}

inline const TDesC& CErrorFileFsMonitor::Path() const
	{
	return *iPath;
	}
	
inline void CErrorFileFsMonitor::Start()
	{
	iMonitor->Start(ENotifyAll);
	}

CErrorFileFsMonitor* CErrorFileFsMonitor::NewLC(RFs& aFs,CEikErrorResolver& aErrorResolver,const TDesC& aPath)
	{ // static
	CErrorFileFsMonitor* self=new(ELeave) CErrorFileFsMonitor(aErrorResolver);
	CleanupStack::PushL(self);
	self->ConstructL(aFs, aPath);
	return self;
	}

CErrorFileFsMonitor::~CErrorFileFsMonitor()
	{
	delete iPath;
	delete iMonitor;
	}

void CErrorFileFsMonitor::ConstructL(RFs& aFs,const TDesC& aPath)
	{
	iMonitor = CApaFsMonitor::NewL(aFs,aPath,TCallBack(FsMonitorCallBack,this));
	iPath = aPath.AllocL();	
	Start();
	}

TInt CErrorFileFsMonitor::FsMonitorCallBack(TAny* aSelf)
	{ // static
	REINTERPRET_CAST(CErrorFileFsMonitor*,aSelf)->HandleFsMonitorCallBack();
	return 0;
	}

void CErrorFileFsMonitor::HandleFsMonitorCallBack()
	{
	iErrorResolver.HandleFileSystemChange(Path());
	}

// 
// class CErrorSet
// 

NONSHARABLE_CLASS(CErrorSet) : public CBase, public MBackupObserver
	{ // typically, all the errors associated with a single component or subsystem
public:
	NONSHARABLE_CLASS(TErrorInfo)
		{
	public:
		TInt iFlags;
		TInt iErrorTextResId;
		};
	NONSHARABLE_CLASS(RErrorGroup)
		{
	public:
		void Close();
	public:
		TInt iTitleTextResId;	// Common title for errors in group
		TInt iStartErrorCode;	// First error code in group
		RArray<TErrorInfo> iErrorInfoArray;	// Array of info of errors in group
		};
public:
	static CErrorSet* NewLC(CCoeEnv& aEnv,const TDesC& aResFileName);
	~CErrorSet();
	CEikErrorResolver::TFoundError TryGetErrorText(CEikonEnv& aEnv, TDes& aErrorText, TInt aError, CEikonEnv::TErrorValidity& aErrorValidity, TDes& aTitleText,
								TInt& aErrorResId, TUint& aFlags, TBool aIsMemoryAllocatedByErrResolver);
	void DoTryGetErrorTextL(CEikonEnv& aEnv, TDes& aErrorText, TDes& aTitleText, TInt aErrorTextId, TInt aTitleTextId, 
							TBool aIsMemoryAllocatedByErrResolver) const;
	inline const TDesC& ResFileName() const;	
	inline TInt ResFileOffset() const;
public: // from MBackupObserver
	void ChangeFileLockL(const TDesC& aFileName,TFileLockFlags aFlags);
private:
	CErrorSet(CCoeEnv& aEnv);
	void ConstructL(const TDesC& aResFileName);
public:
	RArray<RErrorGroup> iErrorGroupArray;
private:
	HBufC* iResFileName;
	TInt iResFileOffset;
	CBaBackupSessionWrapper* iBackupSession;
	TBool iTryLoadRes;
	CCoeEnv& iCoeEnv; 
	};



//
// class CErrorSet::RErrorGroup
//

void CErrorSet::RErrorGroup::Close()
	{
	iErrorInfoArray.Close();
	}

//
// class CErrorSet
//

CErrorSet* CErrorSet::NewLC(CCoeEnv& aEnv,const TDesC& aResFileName)
	{
	CErrorSet* self=new(ELeave) CErrorSet(aEnv);
	CleanupStack::PushL(self);
	self->ConstructL(aResFileName);
	return self;
	}

CErrorSet::~CErrorSet()
	{
	for (TInt ii=iErrorGroupArray.Count()-1;ii>=0;ii--)
		iErrorGroupArray[ii].Close();

	iErrorGroupArray.Close();
	if (iResFileName)
		{
		if (iBackupSession)
			iBackupSession->DeregisterFile(*iResFileName);
		
		iCoeEnv.DeleteResourceFile(iResFileOffset);
		}
		
	delete iResFileName;
	delete iBackupSession;	
	}

inline const TDesC& CErrorSet::ResFileName() const
	{return *iResFileName;}

inline TInt CErrorSet::ResFileOffset() const
	{return iResFileOffset;}

void CErrorSet::ChangeFileLockL(const TDesC& aFileName,TFileLockFlags aFlags)	// from MBackupObserver
	{
	if (aFlags!=EReleaseLockReadOnly && aFileName.CompareF(*iResFileName)==0)
		{
		if (aFlags == EReleaseLockNoAccess)
			{
			iCoeEnv.DeleteResourceFile(iResFileOffset);
			iResFileOffset = 0;
			iTryLoadRes = EFalse;
			}
		else // aFlags==ETakeLock
			{
			TRAPD(err,iResFileOffset=iCoeEnv.AddResourceFileL(*iResFileName));
			if (err)
				iTryLoadRes = ETrue;	// Try again on demand in TryGetErrorText.
			}
		}
	}

const TInt KErrSetGranularity = 4;

CErrorSet::CErrorSet(CCoeEnv& aEnv)
	: iErrorGroupArray(KErrSetGranularity), iCoeEnv (aEnv)
	{}

void CErrorSet::ConstructL(const TDesC& aResFileName)
	{
	iResFileName = aResFileName.AllocL();
	iResFileOffset = iCoeEnv.AddResourceFileL(aResFileName);
	
	CBaBackupSessionWrapper* backup = CBaBackupSessionWrapper::NewL();
	CleanupStack::PushL(backup);
	backup->RegisterFileL(*iResFileName,*this);
	iBackupSession = backup;
	CleanupStack::Pop(backup);
	}

CEikErrorResolver::TFoundError CErrorSet::TryGetErrorText(CEikonEnv& aEnv,TDes& aErrorText,TInt aError, CEikonEnv::TErrorValidity& aErrorValidity,
														  TDes& aTitleText, TInt& aErrorResId, TUint& aFlags, TBool aIsMemoryAllocatedByErrResolver)
	{
	CEikErrorResolver::TFoundError ret = CEikErrorResolver::EErrorNotFound;
	if(iTryLoadRes)
		{
		TRAPD(err,iResFileOffset=iCoeEnv.AddResourceFileL(*iResFileName));
		iTryLoadRes = (err!=KErrNone);
		}
		
	if (iResFileOffset!=0) // ==0 => file closed for backup
		{
		for (TInt ii=iErrorGroupArray.Count()-1;ii>=0 && ret==CEikErrorResolver::EErrorNotFound;ii--)
			{
			const RErrorGroup& errorGroup=iErrorGroupArray[ii];
			const TInt index=errorGroup.iStartErrorCode-aError;
			if (index>=0 && index<errorGroup.iErrorInfoArray.Count())
				{
				TErrorInfo errorInfo=errorGroup.iErrorInfoArray[index];
				if (errorInfo.iFlags&EErrorResPanicErrorFlag)
					{
					// --- Some errors are never meant to get to the UI level ---
					// --- Those of them that do, result in a panic ---
					aErrorValidity=CEikonEnv::EErrorNumInvalid;
					aErrorText.Zero();
					}
				else if (errorInfo.iFlags&EErrorResBlankErrorFlag)
					{
					// --- Error code can be ignored from the users' perspective ---
					// --- Return blank error text ---
					aErrorText.Zero();
					}
				else if (errorInfo.iFlags&EErrorResUnknownErrorFlag)
					{
					// --- Error not recognised by ErrorRes ---
					// --- Will be passed on to CEikonEnv for interpretation ---
					aEnv.DoGetErrorText(aErrorText,KErrUnknown);
					}
				else
					{
					// --- S60(Nokia) has unlimited error text and title text sizes so dealt differently in CErrorSet::DoTryGetErrorTextL()
					if (!aIsMemoryAllocatedByErrResolver)
						aEnv.ReadResource(aErrorText, errorInfo.iErrorTextResId);
					}

				TRAPD(err, DoTryGetErrorTextL(aEnv, aErrorText, aTitleText, errorInfo.iErrorTextResId, errorGroup.iTitleTextResId, aIsMemoryAllocatedByErrResolver));
				if (!err)
					{
					aErrorResId = errorInfo.iErrorTextResId;
					aFlags = errorInfo.iFlags;
					}
				else
					{
					aFlags = EErrorResOOMErrorFlag;
					}
				ret = CEikErrorResolver::EErrorFound;
				}
			}
		}
		
	return ret;
	}

void CErrorSet::DoTryGetErrorTextL(CEikonEnv& aEnv, TDes& aErrorText, TDes& aTitleText, TInt aErrorTextId, TInt aTitleTextId, TBool aIsMemoryAllocatedByErrResolver) const
	{
	if (aIsMemoryAllocatedByErrResolver && !aErrorText.Length() && aErrorTextId)
		{
		HBufC* errText = aEnv.AllocReadResourceL(aErrorTextId);

		// Checks whether the memory allocated for aErrorText by the client is greater than the length of the error text.
		if (aErrorText.MaxLength() >= errText->Length())
			aErrorText.Copy(*errText);
		else
			{
			// If the memory allocated by the client is less than the length of the error text
			// read from the resource file, the error text length is returned to the client in the descriptor
			aErrorText.Num(errText->Length());
			}
		delete errText;	
		}

	if (aTitleTextId)
		{
		HBufC* titleText = aEnv.AllocReadResourceL(aTitleTextId);
		
		// Checks whether the memory allocated for aTitleText by the client is greater than the error title text.
		if (aTitleText.MaxLength() >= titleText->Length())
			aTitleText.Copy(*titleText);
		else
			{
			// If the memory allocated by the client is less than the length of the error title text read from 
			// the resource file, then the error title text length is returned to the client in the descriptor
			aTitleText.Num(titleText->Length());
			}
		delete titleText;
		}
	}









//
// class CEikErrorResolver
//

EXPORT_C CEikErrorResolver* CEikErrorResolver::NewL(CEikonEnv& aEnv)
	{
	CEikErrorResolver* self=new(ELeave) CEikErrorResolver(aEnv);
	return self;
	}

CEikErrorResolver::CEikErrorResolver(CEikonEnv& aEnv)
	: iEnv(aEnv), iErrorArray(1)
	{}
	
CEikErrorResolver::~CEikErrorResolver()
	{
	iErrorArray.ResetAndDestroy();
	iErrorArray.Close();
	if (iFsMonitors)
		iFsMonitors->ResetAndDestroy();
	
	delete iFsMonitors;
	}

EXPORT_C CEikonEnv::TErrorValidity CEikErrorResolver::ResolveErrorWithTitle(TDes& aErrorText, TDes& aTitleText, TInt aError)
	{
	TInt dummyId;
	TUint dummyFlags;
	TBool dummyIsMemoryAllocatedByErrResolver = EFalse;
	return ResolveErrorWithTitle(aErrorText, aTitleText, aError, dummyId, dummyFlags, dummyIsMemoryAllocatedByErrResolver);
	}

EXPORT_C CEikonEnv::TErrorValidity CEikErrorResolver::ResolveErrorWithTitle(TDes& aErrorText, TDes& aTitleText, TInt aError, TInt& aErrorResId, TUint& aFlags, TBool aIsMemoryAllocatedByErrResolver)
	{
	CEikonEnv::TErrorValidity ret=CEikonEnv::EErrorNumValid;
	TRAPD(err, DoResolveErrorL(aErrorText, aError, KNullUid, ret, aTitleText, aErrorResId, aFlags, aIsMemoryAllocatedByErrResolver));
    if (err)
    	{
    	if (err == aError)	// For S60 unknown error text is returned if error is not found in the error resource file(errorres.rss)
    		aFlags = EErrorResUnknownErrorFlag;
    	else
			aFlags = EErrorResOOMErrorFlag;    	
    	}
	return ret;
	}

EXPORT_C CEikonEnv::TErrorValidity CEikErrorResolver::ResolveError(TDes& aErrorText,TInt aError,TUid aApp)
	{
	CEikonEnv::TErrorValidity ret=CEikonEnv::EErrorNumValid;
	if (aError<0 && aError>=KLastSystemWideErrCode)
		iEnv.DoGetErrorText(aErrorText,aError);
	else
		{
		TBuf<KEikErrorResolverMaxTextLength> titleText;
		TInt dummyId;
		TUint dummyFlags;
		TBool dummyIsMemoryAllocatedByErrResolver = EFalse;
		TRAPD(err, DoResolveErrorL(aErrorText,aError,aApp,ret, titleText, dummyId, dummyFlags, dummyIsMemoryAllocatedByErrResolver));
		if (err)
			{
			if (err < KLastSystemWideErrCode)
				err = KErrUnknown;

			iEnv.DoGetErrorText(aErrorText,err);
			}
		}
	
	return ret;
	}

void CEikErrorResolver::HandleFileSystemChange(const TDesC& aDriveAndPath)
	{
	const TInt count = iErrorArray.Count();
	for (TInt ii = count-1; ii >= 0; ii--)
		{
		CErrorSet* errorSet=iErrorArray[ii];
		const TPtrC errorSetPath(TParsePtrC(errorSet->ResFileName()).DriveAndPath());
		if (aDriveAndPath.CompareF(errorSetPath) == 0)
			{
			delete errorSet;
			iErrorArray.Remove(ii);
			iErrorArray.Compress();
			}
		}
	}

void CEikErrorResolver::DoResolveErrorL(TDes& aErrorText,TInt aError,TUid aApp,CEikonEnv::TErrorValidity& aErrorValidity, TDes& aTitleText,
											TInt& aErrorResId, TUint& aFlags, TBool aIsMemoryAllocatedByErrResolver)
	{
	// Check in the list of cached localised error resource files to see if the 
	// resource file with the text for this error has already been read.
	if(ResolveErrorFromCachedList(aErrorText, aError, aErrorValidity, aTitleText, aErrorResId, aFlags, aIsMemoryAllocatedByErrResolver) != EErrorNotFound)
		return;	// Got a text for aError from a currently loaded error resource file.
	
	// Continue, as the right resource file has not yet been loaded.
	
	// Go on a hunt for a text for aError.
	// As we iterate from drive 'A' to 'Z' NearestLanguageFile will return the best match for that drive.
	// However we can't stop there as there could be a better match on another drive. We use the downgrade
	// path to decide which match is best
	RArray<TLanguage> downgradePath;
	CleanupClosePushL(downgradePath);
	BaflUtils::GetDowngradePathL(iEnv.FsSession(), User::Language(), downgradePath);

	// We add ELangNone at the end of the array to make sure that .rsc files take
	// precedence over other languages that are not in the downgrade path
	downgradePath.Append(ELangNone);
	CErrorSet* errorSetBestMatch = NULL;
	CleanupStack::PushL(errorSetBestMatch);
	TInt indexBestMatch = downgradePath.Count();
	CEikErrorResolver::TStoreErrors storeErrors;
	TDriveList driveList;
	User::LeaveIfError(iEnv.FsSession().DriveList(driveList));

	TInt drive = EDriveY; // Look at Z last to enable ROM to be overriden by files on other drives.
	FOREVER
		{
		if(driveList[drive])	// If the drive is present
			{
			CErrorSet* newErrorSetMatch = 0;
			TLanguage newLanguageMatch = ELangNone;
			if(ScanDriveL(drive, aErrorText, aError, aApp, aErrorValidity, 
				storeErrors, newErrorSetMatch, newLanguageMatch, aTitleText, aErrorResId, aFlags, aIsMemoryAllocatedByErrResolver) == EErrorFound)
				{
				// Check if the new language appears before the best match in the downgrade path
				TInt j = 0;
				while (j < indexBestMatch)
					{
					if (newLanguageMatch == downgradePath[j])
						{
						indexBestMatch = j;
						CleanupStack::PopAndDestroy(errorSetBestMatch);
						errorSetBestMatch = newErrorSetMatch;
						CleanupStack::PushL(errorSetBestMatch);
						break;
						}
					j++;
					}
	
				if (!errorSetBestMatch)
					{
					CleanupStack::Pop(errorSetBestMatch);
					errorSetBestMatch = newErrorSetMatch;
					CleanupStack::PushL(errorSetBestMatch);
					}
	
				if (newErrorSetMatch != errorSetBestMatch)
					delete newErrorSetMatch;
				}
			}
			
		if (drive == EDriveA)
			{
			// Looked at all writable disks.
			// Now try the ROM.
			drive = EDriveZ;
			}
		else if (drive == EDriveZ)
			{
			// Looked everywhere, can't find a text for aError.
			// Propagate and let ResolveError() deal with it.
			if (!errorSetBestMatch)
				User::Leave(aError);
			else
				break;
			}
		else
			drive--;	// Examine the next disk.
		}
		
	// Call TryGetErrorText on the best match we found to make sure 
	// we return the correct data. 
	const TInt offset = errorSetBestMatch->ResFileOffset();
	if (offset)
		{
		iEnv.DeleteResourceFile(offset);
		iEnv.AddResourceFileL(errorSetBestMatch->ResFileName());		
		}
	
	errorSetBestMatch->TryGetErrorText(iEnv,aErrorText,aError,aErrorValidity, aTitleText, aErrorResId, aFlags, aIsMemoryAllocatedByErrResolver);
	if (storeErrors==EStoreErrors)
   		{
  		User::LeaveIfError(iErrorArray.Append(errorSetBestMatch));
  		CleanupStack::Pop(errorSetBestMatch);
   		}
    else
    	CleanupStack::PopAndDestroy(errorSetBestMatch);	
    
    CleanupStack::PopAndDestroy(&downgradePath);
	}
	
/*
Scan the specified drive for resolving the error text for the Error Id (aError).
Preference is given to System wide Error over Application specific Error.
So, first scan the resource files present in the Resource\Errors folder to 
resolve the error text for the system wide Error Id. If error text is 
resolved then return EErrorFound. Else, if Application Uid (aApp) is not Null 
then try to resolve for application specific errors by scanning the 
resource files present in \Resource\Apps_Errors folder if error text is resolved 
then return EErrorFound else return EErrorNotFound.
*/
CEikErrorResolver::TFoundError CEikErrorResolver::ScanDriveL(TInt aDrive,TDes& aErrorText, TInt aError, TUid aApp, CEikonEnv::TErrorValidity& aErrorValidity,
				CEikErrorResolver::TStoreErrors& aStoreErrors, CErrorSet*& aErrorSet, TLanguage& aLanguage, TDes& aTitleText,TInt& aErrorResId, TUint& aFlags, TBool aIsMemoryAllocatedByErrResolver)
	{
	CEikErrorResolver::TFoundError found = EErrorNotFound;
	
	// Take the path for system error resource files and prepend the drive letter
	TFileName pathName(KErrorResDirName);
	pathName[0] = static_cast<unsigned short>(KFirstDriveLetter + aDrive);
	aStoreErrors = CEikErrorResolver::EStoreErrors;
	
	// Now, scan resource files present in \Resource\Errors folder for System wide error by passing Null Uid
	found = ScanResourceFilesL(pathName, aErrorText, aError, aErrorValidity, aErrorSet, 
								aLanguage, KNullUid, aTitleText, aErrorResId, aFlags, aIsMemoryAllocatedByErrResolver);
	
	// If not found and we got an app UID, look for app specific error
	if(found == EErrorNotFound && aApp != KNullUid)	
		{
		pathName.Copy(KAppErrorResDirName);
		pathName[0] = static_cast<unsigned short>(KFirstDriveLetter + aDrive);
		// Only store 'global' system errors, app specific errors not stored.
		aStoreErrors = CEikErrorResolver::EStoreNone;
		// Scan the resource files present in \Resource\Apps_Errors for Application Specific Error by passing Application Uid.
		found = ScanResourceFilesL(pathName, aErrorText, aError, aErrorValidity, aErrorSet, 
									aLanguage, aApp, aTitleText, aErrorResId, aFlags, aIsMemoryAllocatedByErrResolver);
		}
	
	return found;
	}
	
/* 
Scan the Resource Files present in the Resource\Errors folder or Resource\Apps_Errors
to resolve the error text for the system wide Error Id or Application Specific Error Id.
Resolving the application specific error text is done by reading only files whose 
application name (obtained from aAppUid) matches with the application name extracted from pathname(aPath).
If error text is resolved then return EErrorFound else return EErrorNotFound.
*/
CEikErrorResolver::TFoundError CEikErrorResolver::ScanResourceFilesL(const TDesC& aPath, TDes& aErrorText,
							TInt aError, CEikonEnv::TErrorValidity& aErrorValidity, CErrorSet*& aErrorSet, 
							TLanguage& aLanguage, TUid aAppUid,	TDes& aTitleText, TInt& aErrorResId, TUint& aFlags, TBool aIsMemoryAllocatedByErrResolver)
	{
	TParsePtrC parse(aPath);
	TPtrC driveAndPath = parse.DriveAndPath();
	CEikErrorResolver::TFoundError foundError = EErrorNotFound;
	
	// Get a list of all the error text resource files in the aPath folser of the drive
	CDir* files = NULL;
	if (iEnv.FsSession().GetDir(aPath, KEntryAttNormal, ESortNone, files)==KErrNone)
		{		
		CleanupStack::PushL(files);
		
		// If we don't have a file monitor for this dir, create one now in anticipation of finding some error files
		const TInt fileCount = files->Count();
		if (fileCount > 0)
			AddMonitorForResourceFolderL(aPath);	
		
		if(aAppUid != KNullUid)	// If we're looking for an application specific error
			{
			// Try to get the application exe name from the aAppUid.
			RApaLsSession localSession;
			CleanupClosePushL(localSession);
			User::LeaveIfError(localSession.Connect());
			TApaAppInfo appInfo;
			localSession.GetAppInfo(appInfo, aAppUid);
			CleanupStack::PopAndDestroy(&localSession);

			// Create a path from the app exe name appended with "_errors"
			_LIT(KErrors,"_errors");
			RBuf appFileName;
			appFileName.CleanupClosePushL();
			TParsePtrC parseRes(appInfo.iFullName);
			const TInt maxSizeofFileName = driveAndPath.Length() + parseRes.Name().Length() + KErrors().Length();
			appFileName.CreateL(driveAndPath, maxSizeofFileName);
			appFileName.Append(parseRes.Name());
			appFileName.Append(KErrors);
			
			// Look for application specific error text
			foundError = GetErrorMsgFromResourceFileL(appFileName, aErrorText, aError, aErrorValidity, 
														aErrorSet, aLanguage, aAppUid, aTitleText, 
														aErrorResId, aFlags, aIsMemoryAllocatedByErrResolver);
			CleanupStack::PopAndDestroy();	// appFileName
			}
		else	// If we're looking for a general system error
			{
			// Look through all the resource files in the system error folder
			for (TInt ii = 0; ii < fileCount && !foundError; ii++)
				{
				// Create a path with the drive, path, and resource file name
				const TEntry& entry = (*files)[ii];
				TFileName resFileName = driveAndPath;
				TParse parseRes;
				parseRes.Set(entry.iName, 0, 0);
				resFileName.Append(parseRes.Name());	
				
				// Look for the error
				foundError = GetErrorMsgFromResourceFileL(resFileName, aErrorText, aError, aErrorValidity, 
															aErrorSet, aLanguage, KNullUid, aTitleText, 
															aErrorResId, aFlags, aIsMemoryAllocatedByErrResolver);
				}
			}

		CleanupStack::PopAndDestroy(files);
		}

	return foundError;
	}

void CEikErrorResolver::AddMonitorForResourceFolderL(const TDesC& aPath)
	{
	TParsePtrC parse(aPath);
	TPtrC driveAndPath = parse.DriveAndPath();
	const TDriveNumber drive = static_cast<TDriveNumber>(aPath[0]-KFirstDriveLetter);
	
	TBool addMonitor = (drive!=EDriveZ);	// Never monitor the ROM drive
	if (addMonitor)
		{
		if (!iFsMonitors)	// Create a list for the monitors if none existis...
			iFsMonitors = new(ELeave) CArrayPtrFlat<CErrorFileFsMonitor>(4);
		else	// ...else look to see if a monitor of this drive already exist
			{
			const TInt monitorCount = iFsMonitors->Count();
			for (TInt jj = 0; jj < monitorCount; jj++)
				{
				if ((*iFsMonitors)[jj]->Path().CompareF(driveAndPath) == 0)
					{
					addMonitor = EFalse;	// One already exists!
					break;
					}
				}
			}
			
		if (addMonitor)	// Create and add a monitor for this drive if none alrady exists
			{
			CErrorFileFsMonitor* monitor = CErrorFileFsMonitor::NewLC(iEnv.FsSession(), *this, driveAndPath);
			iFsMonitors->AppendL(monitor);
			CleanupStack::Pop(monitor);
			}
		}
	}

CEikErrorResolver::TFoundError CEikErrorResolver::ResolveErrorFromCachedList(TDes& aErrorText,TInt aError,
																			CEikonEnv::TErrorValidity& aErrorValidity, TDes& aTitleText, TInt& aErrorResId, TUint& aFlags, TBool aIsMemoryAllocatedByErrResolver)
	{
	CEikErrorResolver::TFoundError ret=EErrorNotFound;
	const TInt arrayCount=iErrorArray.Count();
	for (TInt ii = 0; ii < arrayCount && ret == EErrorNotFound; ii++)
		{
		CErrorSet* errorSet = iErrorArray[ii];
		ret = errorSet->TryGetErrorText(iEnv,aErrorText,aError,aErrorValidity, aTitleText, aErrorResId, aFlags, aIsMemoryAllocatedByErrResolver);
		}
		
	return ret;
	}

TBool CEikErrorResolver::ResourceFileIsLoaded(const TDesC& aResFileName) const
	{
	TBool loaded = EFalse;
	const TInt count = iErrorArray.Count();
	for (TInt ii = 0; ii < count && !loaded; ii++)
		{
		const CErrorSet* errorSet=iErrorArray[ii];
		loaded = (errorSet->ResFileName().CompareF(aResFileName)==0);
		}
		
	return loaded;
	}
	
	
CEikErrorResolver::TFoundError CEikErrorResolver::GetErrorMsgFromResourceFileL(const TDesC& aResFileName,
						TDes& aErrorText, TInt aError, CEikonEnv::TErrorValidity& aErrorValidity,
						CErrorSet*& aErrorSet, TLanguage& aLanguage, TUid aAppUid, TDes& aTitleText, 
						TInt& aErrorResId, TUint& aFlags, TBool aIsMemoryAllocatedByErrResolver) const
	{
	CEikErrorResolver::TFoundError foundError = EErrorNotFound;
	TBool fileExists = ETrue;
	
	// As NearestLanguageFile() requires the suffix to be 'sc' and not whatever 
	// number we found make a new path + filename ending in .rsc
	_LIT(KRsc, ".rsc");
	TFileName resFileName(aResFileName);
	resFileName.Append(KRsc);

	// Find the best localized version of the resource file
	BaflUtils::NearestLanguageFile(iEnv.FsSession(), resFileName, aLanguage);
	if(aAppUid != KNullUid)	
		fileExists = BaflUtils::FileExists(iEnv.FsSession(), resFileName);

	// Check whether the application specific error file is present.  If found absent then get out of loop.
	// On multi-lingual ROMs, the line BaflUtils::NearestLanguageFile(..) may return the same 
 	// filename for several different input files.
	if (fileExists && !ResourceFileIsLoaded(resFileName))
		{
		aErrorSet = NULL;
		TRAPD(err, aErrorSet = CreateErrorSetFromResourceFileL(resFileName));
		if(err == KErrNoMemory)
			User::LeaveNoMemory();
		else if(err)
			return foundError;

		// Try to find the error in the new error set
		foundError = aErrorSet->TryGetErrorText(iEnv, aErrorText, aError, aErrorValidity, aTitleText, aErrorResId, aFlags, aIsMemoryAllocatedByErrResolver);

		// If the error wasn't found in this file, delete it to save memory
		if (foundError != EErrorFound)
			{
			delete aErrorSet;
			aErrorSet = NULL;
			}
		}

	return foundError;
	}


CErrorSet* CEikErrorResolver::CreateErrorSetFromResourceFileL(const TDesC& aResFileName) const
	{
	CErrorSet* errorSet = CErrorSet::NewLC(iEnv, aResFileName);
	
	// Check that this resource file doesn't have the same NAME as another that is already loaded.
	// If it does we won't be able to use Cone to read this file so must reject it as corrupt.
	for (TInt kk = iErrorArray.Count()-1; kk >= 0; kk--)
		{
		const CErrorSet* set = iErrorArray[kk];
		if (set->ResFileOffset() == errorSet->ResFileOffset())
			User::Leave(KErrCorrupt);
		}
		
	// Open the resource file and check that it is really a resource file
	CResourceFile* rf = CResourceFile::NewLC(iEnv.FsSession(), aResFileName, 0, 0);
	if((rf->UidType()[1] != KNullUid) && (rf->UidType()[1] != KUidErrorResourceFileType))
		User::Leave(KErrCorrupt);	// Not a resource file!

	rf->ConfirmSignatureL(); // need to call this to correctly set up rf's internal offset.
	
	// Open the reader at the ERROR_SET resource.
	// Unfortunately the format of the resource file errorres.rss has been changed
	// so that the ERROR_SET resource is no longer at position 2. This cannot be
	// changed back to position 2 due to it being read by legacy applications. In order to 
	// avoid adding padding to all other resource files containing ERROR_SET, look for the
	// ERROR_SET resource for the file errorres.rss at the correct location for that file,
	// and at position 2 for all other resource files.
	_LIT(KErrorResFileName, "errorres.r");
	const TInt KRIMask(0x00000fff);
	RResourceReader reader;		
	TFileName resFileNameLower = aResFileName;
	resFileNameLower.LowerCase();		
	if (resFileNameLower.Find(KErrorResFileName) != KErrNotFound)
		{
		reader.OpenLC(rf, R_ERROR_RES_BASE_LIST&KRIMask); // Use the location of the named ERROR_SET R_ERROR_RES_BASE_LIST as the index 
		}
	else
		{
		reader.OpenLC(rf, 2); // Assume second resource is the index
		}

	// Read the first 16-bit number from the resource
	// In the original format this is the error text array count.
	// A count of zero signals that the resource is on a newer format,
	// where the next 16-bit is the version number (first new supported is v2),
	// then followed by the 16-bit array count.

	const TInt KResourceFormatVersion2 = 2;
	
	const TInt newResourceFormatIndicationOrArrayCount = reader.ReadInt16L();
	TInt arrayCount = 0;
	TInt resourceVersion = 0;
	if (newResourceFormatIndicationOrArrayCount == 0)	// If not a poitive integer, so not an array count, then...
		{
		// ...new resource format!
		// Read the version number and check we support it
		resourceVersion = reader.ReadInt16L();
		if(resourceVersion == KResourceFormatVersion2)
			arrayCount = reader.ReadInt16L();
		else
			{
			ASSERT(0);					// Panic debug builds
			User::Leave(KErrCorrupt);	// Leave in release builds
			}
		}
	else	// Old resource (original) format
		arrayCount = newResourceFormatIndicationOrArrayCount;

	// Iterate through all the error blocks and add the data to the error set
	for (TInt ii = 0; ii < arrayCount; ii++)
		{
		CErrorSet::RErrorGroup errorGroup;
		CleanupClosePushL(errorGroup);
		
		if (resourceVersion == KResourceFormatVersion2)
			errorGroup.iTitleTextResId = reader.ReadInt32L();	// Read the title text LLINK index

		errorGroup.iStartErrorCode = reader.ReadInt32L();		// Read the start code of this block of codes
		const TInt errSetResId = reader.ReadInt32L();			// Read the LLINK index to this block

		// Create a new resource reader and load the block of errors
		RResourceReader reader2;								
		reader2.OpenLC(rf, errSetResId);
		
		// Load all the error text IDs and flags for the errors in this block 
		// and add them to the array (text strings are not loaded until needed!)
		const TInt errorCount = reader2.ReadInt16L();
		for (TInt jj = 0; jj < errorCount; jj++)
			{
			CErrorSet::TErrorInfo errorInfo;
			errorInfo.iFlags = reader2.ReadInt8L();
			errorInfo.iErrorTextResId = reader2.ReadInt32L();	// Read the error text LLINK index
			
			User::LeaveIfError(errorGroup.iErrorInfoArray.Append(errorInfo));	// Add to the cache
			}

		CleanupStack::PopAndDestroy(&reader2);
		
		errorSet->iErrorGroupArray.AppendL(errorGroup);
		CleanupStack::Pop(&errorGroup);
		}

	CleanupStack::PopAndDestroy(2, rf); // reader, rf
	CleanupStack::Pop(errorSet);
	return errorSet;
	}

