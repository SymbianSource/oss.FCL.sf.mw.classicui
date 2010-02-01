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

#ifndef __EIKAPP_H__
#define __EIKAPP_H__

#include <apparc.h>		// class CApaApplication
#include <apaflrec.h>

class CCoeEnv;

/** The base of all Uikon applications. 

CEikApplication builds on CApaApplication, providing a basis for applications 
working within the framework provided by Uikon. It also contains an interface 
to the resource file and the document object belonging to the application.

Each Uikon application class is derived from CEikApplication. Application 
writers must provide at least an implementation of the pure virtual function 
CreateDocumentL().

The application's resource file can be changed from the default by overriding 
ResourceFileName().

@publishedAll 
@released 
@see CEikDocument */
class CEikApplication : public CApaApplication
	{
public:
	IMPORT_C ~CEikApplication();
	inline TInt ResourceFileOffset() const;
	inline CApaProcess* Process() const;
	inline const TApaAppCaption& AppCaption() const;
	IMPORT_C virtual void GetDefaultDocumentFileName(TFileName& aDocumentName) const;
	IMPORT_C virtual TFileName BitmapStoreName() const;
public: // from CApaApplication
	IMPORT_C CDictionaryStore* OpenIniFileLC(RFs& aFs) const;
	IMPORT_C void Capability(TDes8& aInfo) const;
	IMPORT_C void SetToIniFileNameL(TParse& aParser) const;
protected: // from CApaApplication
	IMPORT_C void PreDocConstructL();
	IMPORT_C CApaDocument* CreateDocumentL(CApaProcess* aProcess);
	IMPORT_C void NewAppServerL(CApaAppServer*& aAppServer);
protected: 
	IMPORT_C CEikApplication();
	IMPORT_C void EnsureCaptionIsLocalisedL(const TDesC& aLocalisableResourceFile);
public: 
	IMPORT_C virtual TFileName ResourceFileName() const;
private:
	IMPORT_C virtual void CEikApplication_Reserved1();
	IMPORT_C virtual void CEikApplication_Reserved2();
private: 
	/** 
	@publishedAll 
	@released 
	*/
	virtual CApaDocument* CreateDocumentL()=0;
private: // internal use
	void InitAppNameParserWithPathAndExt(TParse& aParser, const TDesC& aPath, const TDesC& aExt) const;
protected:
	CCoeEnv* iCoeEnv;
	TInt iResourceFileOffset;
private:
	enum
		{
		EFlagCaptionCorrectlyLocalised =  0x00000001
		};	
private:
	CApaProcess* iProcess;
	TApaAppCaption iCaption;
	TApaAppCapabilityBuf* iCapabilityBuf;
	TUint iAppFlags;
	TInt iSpare;
	};

/** Gets the offset value defined for this application's default resource file. 

As the resource file offset can also be accessed through iResourceFileOffset, 
this function should not be needed by any apps.

@return Offset of a resource file. */
inline TInt CEikApplication::ResourceFileOffset() const
	{ return iResourceFileOffset; }


/** Gets the managing process.

@return A pointer to the process object managing this application's documents. */
inline CApaProcess* CEikApplication::Process() const
	{ return iProcess; }


/** Gets the caption for this application.

Captions are displayed in the task list.

@return Application caption. */
inline const TApaAppCaption& CEikApplication::AppCaption() const
	{ return iCaption;	}

#endif	// __EIKAPP_H__
