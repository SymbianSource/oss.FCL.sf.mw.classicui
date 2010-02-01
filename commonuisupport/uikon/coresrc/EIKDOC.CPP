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

#include <eikdoc.h>
#include <eikapp.h>
#include <s32file.h>
#include <s32std.h>
#include <eikappui.h>
#include <eikproc.h>
#include <apgwgnam.h>
#include <apaid.h>

/** Constructor for CEikDocument */
EXPORT_C CEikDocument::CEikDocument()
	{
	}

EXPORT_C CEikDocument::CEikDocument(CEikApplication& aApp)
	:CApaDocument(aApp,*aApp.Process())
/** Constructs a new document.

This constructor is typically called from a derived UI-specific 
document class constructor.

@param aApp The application instance that is creating the document. */
	{
	}

EXPORT_C CEikDocument::~CEikDocument()
/** Destructor. */
	{
	}

EXPORT_C void CEikDocument::NewDocumentL()
/** This empty function can be implemented in file-based applications 
to initialise a new default document.

It is called by the UI framework during application start-up when the 
application is launched without a document being associated with it and 
when no default document exists. */
	{
	}

EXPORT_C CFileStore* CEikDocument::CreateFileStoreLC(RFs& aFs,const TDesC& aFileName)
/** Creates a file store for a new default document.

This function is called by the UI framework during application start-up, 
as part of creating a default document.
 
@param aFs The file server session to use.
@param aFileName The path and name of the file to create.
@return The newly created file store. */
	{
	CFileStore* store=CDirectFileStore::ReplaceLC(aFs,aFileName,EFileShareExclusive);
	TUidType fileUid(KDirectFileStoreLayoutUid,KUidAppDllDoc,Application()->AppDllUid());
	store->SetTypeL(fileUid);
	CStreamDictionary* streamDic=CStreamDictionary::NewL();
	CleanupStack::PushL(streamDic);
	StoreL(*store,*streamDic); // now the store will be fully initialized
	Process()->WriteRootStreamL(*store,*streamDic,*Application());
	store->CommitL();
	CleanupStack::PopAndDestroy(); // streamDic
	return store;
	}

EXPORT_C void CEikDocument::PrintL(const CStreamStore& /*aStore*/)
/** Prints a document without opening it first.

This function is empty. It might be used to print a document directly from a 
shell or file manager application rather than from the document's associated 
application, using default print parameters.

@param aStore The stream store which holds the document. */
	{
	}

EXPORT_C void CEikDocument::StoreL(CStreamStore& /*aStore*/,CStreamDictionary& /*aStreamDic*/) const
/** Stores the document.

This function is empty. Applications that need to persist data must provide 
their own implementation of this function, and RestoreL().

This function is called by CEikAppUi::SaveL().

@param aStore Stream store which holds one or more streams, each of which is generally 
used to store the state of an object (by calling ExternalizeL()).
@param aStreamDic Stream dictionary which is used to store the IDs of the streams 
in the store so they can be identified and restored later. 
@see CEikAppUi::SaveL() */
	{
	}

EXPORT_C void CEikDocument::ExternalizeL(RWriteStream& /*aStream*/) const
/** Externalises an object to a write stream.

Implementations of this function are normally called from StoreL().

@param aStream A write stream inside the stream store passed to StoreL(), 
to which the object's state is written. */
	{
	}

EXPORT_C void CEikDocument::RestoreL(const CStreamStore& /*aStore*/,const CStreamDictionary& /*aStreamDic*/)
/** Restores the document.

This function is empty. Applications that need to persist data must provide 
their own implementation of this function, and StoreL().

This function is called by the UI framework during application start-up when there is 
a document associated with the application.

@param aStore Stream store which holds the document's state.
@param aStreamDic Stream dictionary which holds the IDs of the streams in the store. */
	{
	}

EXPORT_C void CEikDocument::SaveL()
/** Saves the document's state.

It calls StoreL() to save the document and also stores the application's identifier, 
(a TApaAppIdentifier). The document is left open and its 'Has changed' flag is unset. 

This function is called by CEikAppUi::SaveL(). */
	{
	iEikProcess->SaveToDirectFileStoreL(this);
	iChanged=EFalse;
	}

EXPORT_C void CEikDocument::SaveL(MSaveObserver::TSaveType /*aSaveType*/)
/** Saves the document's state. 

This function is called by the UI framework when it needs to close down the 
application and the parameter provides the reason. For instance, it might 
be due to RAM running out. 

This function simply calls the other overload, and ignores the parameter. 
Applications should override this function if they need to take account of 
the parameter.

@param aSaveType Notification code. This indicates to the application why 
this function was called. */
	{
	// by default, just save all app data
	if (iEikProcess->MainStore())
		SaveL();
	}

EXPORT_C TBool CEikDocument::IsEmpty() const
/** Tests whether the document contains any content.

This implementation always returns ETrue. Any applications that 
persist data may optionally override it. It is not called by the UI 
framework.

@return Always ETrue (in CEikDocument). */
	{
	return(ETrue);
	}

EXPORT_C TBool CEikDocument::HasChanged() const
/** Gets the document's 'Has changed' flag.

The flag is set and unset using SetChanged(). Also, calling SaveL() 
unsets it. 

CEikAppUi::SaveAnyChangesL() tests the value of this flag to identify 
whether the document needs to be saved. 

@return The value of the document's 'Has changed' flag. 
@see CEikAppUi::SaveAnyChangesL() */
	{
	return(iChanged);
	}

EXPORT_C void CEikDocument::ValidatePasswordL() const
/**
Checks the document password. The default implementation is empty.

If a document is intended to be password protected, the UI application should provide an implementation 
that forces the user to enter the password and validate the input.
If the document is protected by a password and the password entered by the user is incorrect, 
the function should leave with KErrLocked, otherwise it should just return. */
	{
	CApaDocument::ValidatePasswordL();
	}

EXPORT_C void CEikDocument::EditL(MApaEmbeddedDocObserver* aObserver,TBool aReadOnly)
/** Creates an embedded document's app UI and opens the document for editing or viewing.

@param aObserver Optional pointer to an embedded document observer. This is informed 
when editing is complete. An observer should only be supplied if the document is 
embedded.
@param aReadOnly If ETrue, the embedded document is opened as read-only. 
@leave KErrNotSupported An observer is specified but the application is not embeddable. */
	{
	TApaAppCapabilityBuf buf;
	Application()->Capability(buf);
	TApaAppCapability::TEmbeddability embeddability=buf().iEmbeddability;
	if (aObserver && embeddability==TApaAppCapability::ENotEmbeddable)
		User::Leave(KErrNotSupported);
	TRAPD(err,PrepareToEditL(aObserver,aReadOnly));
	if (err)
		{
		delete iAppUi;
		iAppUi=NULL;
		User::Leave(err);
		}
	iAppUi->HandleModelChangeL();
	if (embeddability==TApaAppCapability::EEmbeddable
	 || embeddability==TApaAppCapability::EEmbeddableOnly
	 || embeddability==TApaAppCapability::EEmbeddableUiOrStandAlone
	 || embeddability==TApaAppCapability::EEmbeddableUiNotStandAlone)
		{
		iAppUi->CheckInitializeViewsL(Application()->AppDllUid());
		iAppUi->ActivateTopViewL();
		}
	}

EXPORT_C void CEikDocument::SetEditStoreL(CStreamStore* aStore)
/** Sets the document's stream store.

This function is called by the UI framework during application start-up.
@param aStore The stream store. */
	{
	iEditStore=aStore;
	iAppUi->HandleModelChangeL();
	}

void CEikDocument::SetEditStoreWithoutAppUiNotificationL(CStreamStore* aStore)
/** @internalComponent */
	{
	iEditStore=aStore;
	}

EXPORT_C void CEikDocument::PrepareToEditL(MApaEmbeddedDocObserver* aObserver,TBool aReadOnly)
/** Prepares an embedded document for editing by creating its app UI.

This function is called by EditL().
@param aObserver Pointer to an embedded document observer. This is notified 
when editing is complete. 
@param aReadOnly If ETrue, the embedded document is opened as read-only. */
	{
	iAppUi=CreateAppUiL();
	iAppUi->SetDocument(this);
	iAppUi->SetEmbeddedDocInfo(aObserver,aReadOnly);
	iAppUi->ConstructL(); // causes the CCoeEnv object to take ownership of iAppUi (the implementation of this virtual function must call CEikAppUi::ConstructL or CEikAppUi::BaseConstructL before calling any other leaving function)
	}

EXPORT_C void CEikDocument::PrepareToEditL()
/** Prepares a main (non-embedded) document for editing, by creating its app UI.

This function is called by the UI framework during application start-up. */
	{
	PrepareToEditL(NULL,NULL);
	}
	
/**
Deletes reference to associated appUi
@internalComponent
*/
void CEikDocument::NullAppUi()
	{
	iAppUi=NULL;
	}

EXPORT_C void CEikDocument::SetChanged(TBool aHasChanged)
/** Sets this document's 'Has changed' flag.

@param aHasChanged New value for the 'Has changed' flag. */
	{
	iChanged=aHasChanged;
	}

EXPORT_C const TApaAppCaption& CEikDocument::AppCaption() const
/** Gets the caption of the application that created the document. 

The application's caption is usually specified in its localisable resource file. 
@return The caption of the application that created the document. 
@see CEikApplication::AppCaption(). */
	{
	return(iEikApplication->AppCaption());
	}

EXPORT_C void CEikDocument::SetAppFileMode(TUint aMode)
/** Sets the document's file sharing and access mode.

@param aMode The new file sharing and access mode. This is a bitwise OR of 
values enumerated in TFileMode.
@see TFileMode */
	{
	iAppFileMode=aMode;
	}

EXPORT_C TUint CEikDocument::AppFileMode() const
/** Gets the document's file sharing and access mode.

By default, the access mode is EFileShareExclusive|EFileWrite, 
except when the file could not be opened for exclusive writing, in 
which case, its default access mode is EFileRead|EFileShareReadersOnly.

@return The file sharing and access mode. This is a bitwise OR of 
values enumerated in TFileMode.
@see TFileMode */
	{
    return iAppFileMode;
	}

EXPORT_C void CEikDocument::UpdateTaskNameL(CApaWindowGroupName* aWgName)
/** Updates a window group (or task) name with information about a main 
(non-embedded) document.

The window group name is updated to contain the application's caption and UID, and 
the filename of the main document. 

The filename is also written to the application's ini file, to identify the 
application's most recently opened file. An ini file is created if one doesn't 
exist. 

This function is called by the UI framework during application start-up.

@param aWgName Window group (or task) name. On return, this is updated to contain 
information about the main document. */
	//
	// default window group name
	//
	{
    const TPtrC docName=iEikProcess->MainDocFileName();
	if (docName.Length())
		{
		TRAP_IGNORE(iEikProcess->SetLastUsedFileL(CEikProcess::ELastOpenFile,docName));
		}
	const TPtrC name=AppCaption();
	aWgName->SetCaptionL(name);
	aWgName->SetAppUid(Application()->AppDllUid());
	aWgName->SetDocNameL(docName);
	}

EXPORT_C CFileStore* CEikDocument::OpenFileL(TBool aDoOpen,const TDesC& aFilename,RFs& aFs)
/** Restores the document's state from the specified file, or creates a new 
default document. 

If aDoOpen is true, the function tries to open the file for exclusive writing. If that 
fails, it tries to open it for reading only. If that fails, it leaves.
	
If aDoOpen is false, the function creates a new default document whose 
path and name are specified in aFilename.

This function is called by the UI framework during application start-up.

@param aDoOpen True to open an existing file, false to create a new default file.
@param aFilename The path and name of the file to open or create.
@param aFs File server session to use.
@return The file store that stores the main document. */
	{
	CFileStore* docStore=NULL;
	TUint appFileMode=EFileShareExclusive|EFileWrite;
	if (aDoOpen)
		{
		CStreamDictionary* streamDic=NULL;
		TRAPD(err,
		streamDic=CApaProcess::ReadRootStreamLC(aFs,docStore,aFilename,appFileMode);
		CleanupStack::Pop(););
		if (err==KErrNone)
			CleanupStack::PushL(streamDic);
		else
			{
			appFileMode=EFileRead|EFileShareReadersOnly;
			if (err==KErrAccessDenied || err==KErrInUse)
				streamDic=CApaProcess::ReadRootStreamLC(aFs,docStore,aFilename,appFileMode);
			else
				User::Leave(err);
			}
		CleanupStack::PushL(docStore);
		RestoreL(*docStore,*streamDic);
		CleanupStack::Pop();// docStore
		CleanupStack::PopAndDestroy(); // streamDic
		}
	else
		{
		NewDocumentL();
		aFs.MkDirAll(aFilename);
		docStore=CreateFileStoreLC(aFs,aFilename);
		docStore->CommitL();
		CleanupStack::Pop();  // docStore
		}
	iAppFileMode=appFileMode;
	return docStore;
	}

EXPORT_C void CEikDocument::OpenFileL(CFileStore*& aFileStore, RFile& aFile)
/** Restores the document's state from the specified file.

This virtual function should be overridden if the file is not a "native" 
Symbian OS file (i.e. is not a CFileStore). In this case, the override should 
set the aFileStore parameter to NULL.

Overrides of this function must only set aFileStore once all leave-prone operations 
have succesfully completed.

This function is called by the UI framework during application start-up.

When a file is opened, the current write position is automatically set to the start of the file, therefore 
there is no need to call RFile::Seek(ESeekStart,0).
A call to RFile::Close() should be made when the file handle is no longer required.
The file handle should not be passed to another process or application as it will be closed automatically 
when its associated file-server session is closed.

@see RFile
@see RFs

@param aFileStore This is set by the function to the file store that stores 
the main document, if the file is a "native" Symbian OS file, otherwise it 
is set to NULL.
@param aFile The path and name of the file to read from. */
	{
	CFileStore* fileStore=NULL;
	CStreamDictionary* const streamDictionary=CApaProcess::ReadRootStreamLC(fileStore, aFile);
	CleanupStack::PushL(fileStore);
	RestoreL(*fileStore, *streamDictionary);
	CleanupStack::Pop(fileStore);
	CleanupStack::PopAndDestroy(streamDictionary);
	iAppFileMode=0;
	aFileStore=fileStore;
	}

EXPORT_C void CEikDocument::Reserved_2()
	{}
