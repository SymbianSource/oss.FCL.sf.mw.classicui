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

#include <eikproc.h>
#include <eikdoc.h>
#include <s32file.h>
#include <basched.h>
#include <eikpanic.h>
#include <apacmdln.h>
#include <apparc.h>
#include "APFDEF.H"
#include <eikenv.h>



/**
Static two phase construction 
@param aFs File server session
@param aProcessId May be KNullProcessId @see CApaProcess::ConstructL
@return Instantiated and constructed process object.
*/
CEikProcess* CEikProcess::NewL(const RFs& aFs, TProcessId aProcessId)
	{ // static
	CEikProcess* self=new(ELeave) CEikProcess(aFs);
	CleanupStack::PushL(self);
	if(KNullProcessId==aProcessId)
		{
		self->ConstructL();
		}
	else
		{
		self->ConstructL(aProcessId);
		}
	CleanupStack::Pop(self);
	return self;
	}


/**
Constructor
@param aFs File server session
@internalComponent
*/
CEikProcess::CEikProcess(const RFs& aFs)
	: CApaProcess(aFs)
	{}

EXPORT_C CEikProcess::~CEikProcess()
/** Destructor.

Destroys the main document. */
	{
	DestroyDocument(MainDocument()); // pre-empt this call at superclass level
	delete(iMainStore); // delete this only after document has been deleted
	}

/**
Returns the command tail end - i.e. command line parameters
@return CommandTailEnd.
*/
EXPORT_C TPtrC CEikProcess::CommandTailEnd() const
	{
	return iCommandTailEnd;
	}

EXPORT_C TFileName CEikProcess::MainDocFolder() const
/** Returns the drive and path of the main document. 

@return The drive and path of the main document. This excludes the filename. */
	{
	TParse parse;
	parse.Set(MainDocFileName(),NULL,NULL);
	return(parse.DriveAndPath());
	}

EXPORT_C void CEikProcess::SetMainStore(CFileStore* aMainStore)
/** Sets the file store that stores the main document. 

A main store must have been set before you can call SaveToDirectFileStoreL().

@param aMainStore The file store object which is used to store the main document. */

	{
	iMainStore=aMainStore;
	}

struct STemp
	{
	RFs* iFs;
	TParse iFile;
	};

/**
@internalComponent
*/
LOCAL_C void DeleteTemp(TAny* aPtr)
	{
	STemp& temp=*(STemp*)aPtr;
	temp.iFs->Delete(temp.iFile.FullName());
	}

EXPORT_C void CEikProcess::SaveToDirectFileStoreL(CEikDocument* aDoc,const TFileName* aNewFileName,TBool aReopen,TFileName* aTempFile)
/** Saves the main document optionally to a new file, and optionally opens it.

@param aDoc The main document.
@param aNewFileName The optional new filename for the main document. 
This file should not already exist. If specified, a new file with 
this name is created, and the main document is saved to it; aTempFile 
is not used. If NULL, the main document is saved to a temporary file, 
whose name is returned in aTempFile. 
@param aReopen If true, the main document file is set to the contents of 
any temporary file created, if applicable, and the newly created main document 
file is opened for writing. If false, the temporary file (if created) or the 
main document file remains closed.
@param aTempFile If not NULL, on return, this holds the path and filename of 
the temporary file created and into which the document was saved.
@panic EIKON 44 The main store has not been allocated.
@panic EIKON 45 The main store is not a direct file store (its first UID is not 
KDirectFileStoreLayoutUid). */
	{
	__ASSERT_ALWAYS( iMainStore ,Panic(EEikPanicProcessNoStore));
	__ASSERT_ALWAYS( iMainStore->Type()[0]==KDirectFileStoreLayoutUid ,Panic(EEikPanicProcessWrongStoreType));
	//
	RFs& fsSession=FsSession();
	STemp temp;					// for temporary file name and cleanup-deletion
	CDirectFileStore* store=NULL;
	if (aNewFileName)
		{
		// save to the new filename supplied, and open this new file as iMainDoc
		store = CDirectFileStore::CreateLC(fsSession,*aNewFileName,EFileWrite);
		}
	else
		{// overwrite iMainDocFileName, but save to a temporary first
		// make sure the temp directory is on the same drive as the file and that it exists
		TPtrC tempFile;
		if(aTempFile && aTempFile->Length())
			{
			tempFile.Set(*aTempFile);
			}
		else
			{
			tempFile.Set(MainDocFileName());
			}
		TParsePtrC ptr(tempFile);
		TPtrC drive=ptr.Drive();
		TFileName tempName;
		_LIT(KFormat,"\\private\\%08x\\");
		tempName.Format(KFormat,RThread().SecureId().iId);
		User::LeaveIfError(temp.iFile.Set(drive,&tempName,NULL) ); // abuse temp.iFile
		fsSession.MkDirAll(temp.iFile.DriveAndPath());
		// create temp file
		tempName.Zero();
		RFile file;
		User::LeaveIfError(file.Temp(fsSession,temp.iFile.DriveAndPath(),tempName,EFileWrite));
		temp.iFs=&fsSession;
		temp.iFile.Set(tempName,NULL,NULL);		// set for deletion if it goes wrong now
		CleanupStack::PushL(TCleanupItem(DeleteTemp,&temp));
		store = CDirectFileStore::NewLC(file);
		if (aTempFile)
			{
			*aTempFile=temp.iFile.FullName();
			}
		}
	store->SetTypeL(iMainStore->Type());
	// store main in temp
	CStreamDictionary* streamDic=CStreamDictionary::NewL();
	CleanupStack::PushL(streamDic);
	MainDocument()->StoreL(*store,*streamDic);
	// write root stream
	WriteRootStreamL(*store,*streamDic,*aDoc->Application());
	CleanupStack::PopAndDestroy(streamDic);
	// close the new store
	store->CommitL();
	CleanupStack::PopAndDestroy(store);
	if (aNewFileName==NULL)
		{
		CleanupStack::Pop(&temp); // temporary file deleter
		}
	if (aReopen)
		{
		// close the old store
		delete iMainStore;
		iMainStore=NULL;
		TRAPD(err,OpenNewFileL(aNewFileName,temp.iFile));
		if (err!=KErrNone)
			{
			if (iMainStore!=NULL)
				{
				User::Leave(err);
				}
			CBaActiveScheduler::Exit();
			}
		}
	}

EXPORT_C void CEikProcess::SaveToDirectFileStoreL(CEikDocument* aDoc,const TFileName* aNewFileName)
/** Saves the main document optionally to a new file.

If aNewFileName is specified, a new file with that name is created, and the 
main document is saved to it. This file is opened for writing.

If aNewFileName is NULL, the main document is saved and is opened for writing.

@param aDoc The main document.
@param aNewFileName The optional new filename for the main document. This file 
should not already exist.
@panic EIKON 44 The main store has not been allocated.
@panic EIKON 45 The main store is not a direct file store (its first UID is not 
KDirectFileStoreLayoutUid). */
	{
	SaveToDirectFileStoreL(aDoc,aNewFileName,ETrue);
	}


/**
Opens file.  Updates MainDocFileName, opens file as direct file store.
@param aNewFileName May be null
@param aNewFilePath Used if aNewFileName is null.
@internalComponent
@see CApaProcess::MainDocFileName()
*/
void CEikProcess::OpenNewFileL(const TFileName* aNewFileName,const TParse& aNewFilePath)
	{
	if (!aNewFileName)
		{
		RFs& fsSession=FsSession();
		const TInt err=fsSession.Replace(aNewFilePath.FullName(),MainDocFileName());
		iMainStore=CDirectFileStore::OpenL(fsSession,MainDocFileName(),EFileShareExclusive);
		User::LeaveIfError(err);
		}
	else
		{
		SetMainDocFileName(*aNewFileName);
		// open new file
		iMainStore=CDirectFileStore::OpenL(FsSession(),MainDocFileName(),EFileShareExclusive);
		}
	}

EXPORT_C CFileStore* CEikProcess::MainStore() const
/** Gets a pointer to the main store. This is the file store that 
holds the main document.

@return The main store, or NULL if it has not been set. */
	{
	return iMainStore;
	}

EXPORT_C void CEikProcess::AppFromDocL(TDes& aLibraryName,const TDesC& aDocumentName) const
/** Gets the name of the application DLL associated with the specified document. 

@param aLibraryName On return, holds the path and filename of the application DLL.
@param aDocumentName The path and filename of the document file.
@leave KErrCorrupt The document file is not valid (its UID2 must be KUidAppDllDoc). */
	{
	CFileStore* docStore;
	CStreamDictionary* streamDic=CApaProcess::ReadRootStreamLC(FsSession(),docStore,aDocumentName,EFileRead);
	CleanupStack::PushL(docStore);
	GetLibraryNameL(aLibraryName,*docStore,*streamDic);
	CleanupStack::PopAndDestroy(2); // streamDic and docStore
	}

/**
@param aLibraryName Ouput parameter, contains full application name on return
@param aDocStore File store containing the library
@param aStreamDic Stream dictionary within file store.
@internalComponent
*/
void CEikProcess::GetLibraryNameL(TDes& aLibraryName,const CFileStore& aDocStore,const CStreamDictionary& aStreamDic) const
	{
	TApaAppIdentifier appId=ReadAppIdentifierL(aDocStore,aStreamDic);
	aLibraryName=appId.iFullName;
	}

const TUid KUidEikLastOpenFile={0x100000fb};
const TUid KUidEikLastCreatedFile={0x100000fc};

EXPORT_C void CEikProcess::SetLastUsedFileL(TLastUsedFile aType,const TDesC& aFileName) const
/** Sets the name of either the last opened or the last created file. 

The information is written to the .ini file of the application associated 
with the main document. It attempts to create an .ini file if one does not exist.

@param aType Indicates whether aFileName is the name of the last opened or last 
created file.
@param aFileName The name of the last opened or last created file.*/
	{
	CDictionaryStore* iniFile=OpenMainAppIniFileLC();
	if (iniFile==NULL)
		return;
	RDictionaryWriteStream writeStream;
	writeStream.AssignLC(*iniFile,aType==ELastOpenFile? KUidEikLastOpenFile: KUidEikLastCreatedFile);
	writeStream << aFileName;
	writeStream.CommitL();
	CleanupStack::PopAndDestroy(); // writeStream
	iniFile->CommitL();
	CleanupStack::PopAndDestroy(); // inifile
	}

// implementation changed; function now never leaves.
EXPORT_C TFileName CEikProcess::LastUsedFileL(TLastUsedFile aType) const
/** Gets the name of either the last opened or last created file. 

The information is read from the .ini file of the application associated with 
the main document. The function cannot leave. If an error occurs, the function 
returns an empty filename.

@param aType Indicates whether the function should return the name of the last 
opened or last created file.
@return The name of the last opened or last created file.*/
	{
	TFileName ret;
	CDictionaryStore* iniFile=NULL;
	TRAPD(inierr, iniFile=OpenMainAppIniFileLC();
		if (iniFile)
			CleanupStack::Pop(););
	if (!inierr)
		{
		if (iniFile!=NULL)
			{
			CleanupStack::PushL(iniFile);
			RDictionaryReadStream readStream;
			TRAPD(err,readStream.OpenL(*iniFile,aType==ELastOpenFile? KUidEikLastOpenFile: KUidEikLastCreatedFile));
			if (!err)
				{
				TRAP(err,readStream >> ret);
				readStream.Close();
				}
			CleanupStack::PopAndDestroy(); // iniFile
			}
		}
	return(ret);
	}


/**
@return Application's ini file
@see CApaApplication::OpenIniFileLC(RFs &aFs)
@internalComponent
*/
CDictionaryStore* CEikProcess::OpenMainAppIniFileLC() const
	{
 	CDictionaryStore* iniFile=((CEikProcess*)this)->MainDocument()->Application()->OpenIniFileLC(FsSession());
	return(iniFile);
	}
