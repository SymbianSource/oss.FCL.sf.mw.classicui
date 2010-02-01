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

#ifndef __EIKDOC_H__
#define __EIKDOC_H__

#include <apparc.h>
#include <savenotf.h>

#ifndef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikdefaulticondefs.h>
#endif

class CEikAppUi;
class CEikApplication;
class CApaWindowGroupName;


/** The base class for all GUI applications' documents. 

In file-based applications, the document represents the data that relates to a 
particular instance of the application, and should handle storing and restoring 
it. In all applications, whether file-based or not, the document is used to create 
the application UI. 

A class derived from CEikDocument must be defined by each GUI application, and minimally 
it must implement CreateAppUiL(). Note that UIs may implement their own document base class, 
derived from CEikDocument, which applications may need to derive from instead. 

The document is created by the application's CreateDocumentL() function.

@publishedAll
@released 
@see CEikApplication::CreateDocumentL()
@see CEikAppUi */
class CEikDocument : public CApaDocument, public MSaveObserver
	{
public: // new functions
	/** Constructs the application UI.
	
	This function is called by the UI framework during application start-up. It should 
	only carry out first phase construction of the app UI, in other words, using new(ELeave). 
	It should not call the app UI's ConstructL(), because the UI framework is responsible 
	for this. Note also that the UI framework takes ownership of the app UI, so the 
	document does not need to destroy it.

	@return A partially-constructed app UI object. */
	virtual CEikAppUi* CreateAppUiL()=0;
	IMPORT_C virtual CFileStore* OpenFileL(TBool aDoOpen,const TDesC& aFilename,RFs& aFs);
	IMPORT_C void PrepareToEditL(MApaEmbeddedDocObserver* aObserver,TBool aReadOnly);
	IMPORT_C void PrepareToEditL();
	IMPORT_C void SetAppFileMode(TUint aMode);
	IMPORT_C TUint AppFileMode() const;
	IMPORT_C virtual void UpdateTaskNameL(CApaWindowGroupName* aWgName);
	IMPORT_C const TApaAppCaption& AppCaption() const;
	IMPORT_C void SetChanged(TBool aHasChanged);
	IMPORT_C void SetEditStoreL(CStreamStore* aStore);
	void SetEditStoreWithoutAppUiNotificationL(CStreamStore* aStore);
	inline CStreamStore* EditStore() const;
	IMPORT_C ~CEikDocument();
public: // from MSaveObserver
	IMPORT_C virtual void SaveL(MSaveObserver::TSaveType aSaveType);
public: // from CApaDocument
	IMPORT_C void NewDocumentL();
	IMPORT_C CFileStore* CreateFileStoreLC(RFs& aFs,const TDesC& aFileName);
	IMPORT_C void EditL(MApaEmbeddedDocObserver* aObserver,TBool aReadOnly=EFalse);
	IMPORT_C void PrintL(const CStreamStore& aSourceStore);
	IMPORT_C void SaveL();
	IMPORT_C void StoreL(CStreamStore& aStore,CStreamDictionary& aStreamDic) const;
	IMPORT_C void RestoreL(const CStreamStore& aStore,const CStreamDictionary& aStreamDic);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C TBool IsEmpty() const;
	IMPORT_C TBool HasChanged() const;
	IMPORT_C virtual void ValidatePasswordL() const; // return EFalse if there *is* a password *and* the user doesn't get it right, ETrue otherwise (ie they get it right or there isn't one). Returns ETrue by default
protected:
	IMPORT_C CEikDocument();
	IMPORT_C CEikDocument(CEikApplication& aApp);
public:
	IMPORT_C virtual void OpenFileL(CFileStore*& aFileStore, RFile& aFile);
private:
	void NullAppUi();
	// reserved functions from CApaDocument
	IMPORT_C virtual void Reserved_2();
protected:
	/** A pointer to the app UI which the document is associated with. */
	CEikAppUi* iAppUi;
	/** A pointer to the file store object which is used to edit the document. */
	CStreamStore* iEditStore;
private:
	TBool iChanged;
	TUint iAppFileMode;
	friend class CEikAppUi;
	};

/** A pointer to the application process associated with this document.

@publishedAll
@released */
#define iEikProcess ((CEikProcess*)Process())

/** A pointer to the application that created this document.

@publishedAll
@released */
#define iEikApplication ((CEikApplication*)Application())

/** Gets the file store object which is used to edit the document.

@return A pointer to the file store object which is used to edit the document. */
inline CStreamStore* CEikDocument::EditStore() const
	{ return(iEditStore); }

#endif	// __EIKDOC_H__

