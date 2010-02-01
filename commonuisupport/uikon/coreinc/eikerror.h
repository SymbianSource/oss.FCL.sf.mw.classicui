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

#ifndef __EIKERROR_H__
#define __EIKERROR_H__

#include <e32base.h>
#include <f32file.h>
#include <babackup.h>
#include <eikenv.h>

class CErrorFileFsMonitor;
class CErrorSet;

/** @internalAll */
NONSHARABLE_CLASS(CEikErrorResolver) : public CBase
	{
public:
	enum TFoundError
		{
		EErrorNotFound	= EFalse,
		EErrorFound		= ETrue,
		};
public:
	IMPORT_C static CEikErrorResolver* NewL(CEikonEnv& aEnv);
	~CEikErrorResolver();
	inline CEikonEnv::TErrorValidity ResolveError(TDes& aErrorText,TInt aError);
	IMPORT_C CEikonEnv::TErrorValidity ResolveError(TDes& aErrorText,TInt aError,TUid aApp);
	IMPORT_C CEikonEnv::TErrorValidity ResolveErrorWithTitle(TDes& aErrorText, TDes& aTitleText, TInt aError);
	IMPORT_C CEikonEnv::TErrorValidity ResolveErrorWithTitle(TDes& aErrorText, TDes& aTitleText, TInt aError, TInt& aErrorResId, TUint& aFlags, TBool aIsMemoryAllocatedByErrResolver);
public:
	void HandleFileSystemChange(const TDesC& aDriveAndPath);
private:
	enum TStoreErrors {EStoreNone, EStoreErrors};
private:
	CEikErrorResolver(CEikonEnv& aEnv);
	void AddMonitorForResourceFolderL(const TDesC& aPath);
	void DoResolveErrorL(TDes& aErrorText,TInt aError,TUid aApp,CEikonEnv::TErrorValidity& aErrorValidity, TDes& aTitleText,
							TInt& aErrorResId, TUint& aFlags, TBool aIsMemoryAllocatedByErrResolver);
	TFoundError ScanDriveL(TInt aDrive, TDes& aErrorText, TInt aError, TUid aApp,
									CEikonEnv::TErrorValidity& aErrorValidity, CEikErrorResolver::TStoreErrors& aStoreErrors,
									CErrorSet*& aErrorSet, TLanguage& aLanguage, TDes& aTitleText,TInt& aErrorResId, TUint& aFlags, 
									TBool aIsMemoryAllocatedByErrResolver);
	TFoundError ScanResourceFilesL(const TDesC& aPath, TDes& aErrorText, TInt aError, 
									CEikonEnv::TErrorValidity& aErrorValidity, CErrorSet*& aErrorSet, TLanguage& aLanguage, TUid aAppUid,
									TDes& aTitleText,TInt& aErrorResId, TUint& aFlags, TBool aIsMemoryAllocatedByErrResolver);
	CErrorSet* CreateErrorSetFromResourceFileL(const TDesC& aResFileName) const;
	TFoundError ResolveErrorFromCachedList(TDes& aErrorText,TInt aError,CEikonEnv::TErrorValidity& aErrorValidity, TDes& aTitleText,TInt& aErrorResId, 
											TUint& aFlags, TBool aIsMemoryAllocatedByErrResolver);
	TBool ResourceFileIsLoaded(const TDesC& aResFileName) const;
	TFoundError GetErrorMsgFromResourceFileL(const TDesC& aResFileName,TDes& aErrorText,TInt aError, 
	                                         CEikonEnv::TErrorValidity& aErrorValidity, CErrorSet*& aErrorSet, 
	                                         TLanguage& aLanguage, TUid aAppUid, TDes& aTitleText, 
											 TInt& aErrorResId, TUint& aFlags, TBool aIsMemoryAllocatedByErrResolver) const;
private:
	CEikonEnv&					iEnv;
	RPointerArray<CErrorSet>	iErrorArray;
	CArrayPtr<CErrorFileFsMonitor>*	iFsMonitors;
	};


inline CEikonEnv::TErrorValidity CEikErrorResolver::ResolveError(TDes& aErrorText,TInt aError)
	{return ResolveError(aErrorText,aError,KNullUid);}

#endif	// __EIKERROR_H__
