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

#ifndef __EIKPROC_H__
#define __EIKPROC_H__

#include <apparc.h>
#include <eikdef.h>

class CFileStore;
class CEikDocument;

/** The controlling process for an application. 

An instance of this class is created by the Uikon environment. This instance 
calls CApaProcess::AddNewDocumentL() to load the application DLL and 
construct the new application which runs in this environment. 

It also provides services related to an application's main (non-embedded) document, 
including: 
- saving the main document to a direct file store
- providing the name of the most recently accessed file
- getting the name of the application DLL associated with a document.

@publishedAll 
@released */
NONSHARABLE_CLASS(CEikProcess) : public CApaProcess
	{
public:
	/** Used as a parameter by CEikProcess::SetLastUsedFileL() and LastUsedFileL() 
	to indicate whether the function relates to the last opened or last created file.*/
	enum TLastUsedFile
		{
		/** Last opened file.*/
		ELastOpenFile,
		/** Last created file. */
		ELastCreatedFile
		};
public:
	static CEikProcess* NewL(const RFs& aFs, TProcessId aProcessId=KNullProcessId);
	IMPORT_C TPtrC CommandTailEnd() const;
	IMPORT_C TFileName MainDocFolder() const;
	IMPORT_C void SetLastUsedFileL(TLastUsedFile aType,const TDesC& aFileName) const;
	IMPORT_C TFileName LastUsedFileL(TLastUsedFile aType) const;
	IMPORT_C void SetMainStore(CFileStore* aMainStore);
	IMPORT_C CFileStore* MainStore() const;
	IMPORT_C void AppFromDocL(TDes& aLibraryName,const TDesC& aDocumentName) const;
	IMPORT_C void SaveToDirectFileStoreL(CEikDocument* aDoc,const TFileName* aNewFileName=NULL);
	IMPORT_C void SaveToDirectFileStoreL(CEikDocument* aDoc,const TFileName* aNewFileName,TBool aReopen,TFileName* aTempFile=NULL);
	IMPORT_C ~CEikProcess();
private:
	CEikProcess(const RFs& aFs);
	void GetLibraryNameL(TDes& aLibraryName,const CFileStore& aDocStore, const CStreamDictionary& aStreamDic) const;
	void OpenNewFileL(const TFileName* aNewFileName, const TParse& aNewFilePath);
	CDictionaryStore* OpenMainAppIniFileLC() const;
private:
	TPtrC iCommandTailEnd;
	CFileStore* iMainStore;
	};

#endif	// __EIKPROC_H__
