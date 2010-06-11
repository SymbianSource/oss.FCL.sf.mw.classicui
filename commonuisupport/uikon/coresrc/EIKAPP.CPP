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

#include <eikapp.h>
#include <s32file.h>	// class CDictionaryFileStore
#include <coemain.h>
#include <eikenv.h>
#include <bautils.h>
#include <coeutils.h>
#include <apgicnfl.h>
#include "APFDEF.H"
#include <apgcli.h>
#include <barsc2.h>
#include <barsread2.h>

_LIT(KAppResourcePath,"\\Resource\\Apps\\");

/** Default constructor.

The default constructor is empty, and there are no NewL() or NewLC() functions 
as Uikon applications are created automatically by the application DLL framework 
when applications are started. */
EXPORT_C CEikApplication::CEikApplication() : iCoeEnv (CCoeEnv::Static())
	{
	}

/** Destructor. 

Deletes any resources acquired by this CEikApplication during its construction 
phases. */
EXPORT_C CEikApplication::~CEikApplication()
	{
	iCoeEnv->DeleteResourceFile(iResourceFileOffset);
	delete iCapabilityBuf;
	iProcess = NULL;	// Not owned
	}

/**
Initiates the aParser object with the name of the application and the 
aPath and aExt specified.

@internalTechnology
*/
void CEikApplication::InitAppNameParserWithPathAndExt(TParse& aParser, const TDesC& aPath, const TDesC& aExt) const
	{
	const TFileName libPath = AppFullName();
	const TParsePtrC parsePtr(libPath);
	const TDriveName driveName = parsePtr.Drive();
	const TPtrC appName = parsePtr.Name();
	
	TParse parse;
	parse.Set(appName,&aExt, NULL);
	aParser.Set(parse.FullName(),&driveName,&aPath);
	}

/** Gets the localized name of the resource file used by this application. 

By default, this file has an extension of .rsc and uses the same name 
as the application file located in the same directory. Language variants 
are supported through BaflUtils::NearestLanguageFile().

@return The name of the resource file. Used by PreDocConstructL(). */
EXPORT_C TFileName CEikApplication::ResourceFileName() const
	{ // !! needs to cope with multi-lingual apps
	TParse parse;
	_LIT(KResFileDefaultExt,".rsc");
	InitAppNameParserWithPathAndExt(parse, KAppResourcePath, KResFileDefaultExt);

	TFileName name = parse.FullName();
	BaflUtils::NearestLanguageFile(iEikonEnv->FsSession(), name);
	return name;
	}

/** Gets the localized name of the bitmap file used by this application. 

By default, this file has an extension of .mbm and uses the same name 
as the application file in the same directory. Language variants 
are supported using BaflUtils::NearestLanguageFile().

@return The name of the bitmap store for this application. */
EXPORT_C TFileName CEikApplication::BitmapStoreName() const
	{ // !! needs to cope with multi-lingual apps
	TParse parse;
	_LIT(KBmpFileDefaultExt,".mbm");
	InitAppNameParserWithPathAndExt(parse, KAppResourcePath, KBmpFileDefaultExt);

	TFileName name = parse.FullName();
	BaflUtils::NearestLanguageFile(iEikonEnv->FsSession(),name);
	return name;
	}

/** Creates a new document.

This function is called by the application DLL framework during application startup
to create a new instance of the document associated with this application. 
This implementation of the function makes a record of the CApaProcess argument, 
and returns a document created by the un-parameterised, private, overload. */
EXPORT_C CApaDocument* CEikApplication::CreateDocumentL(CApaProcess* aProcess)
	{
	ASSERT(!iProcess);
	iProcess = aProcess;
	return CreateDocumentL();	// pure virtual implemented by each application
	}

/** Prepares for document creation.

This function is called by the application DLL framework to complete construction and 
initialise the new application object. After this function has been called, the 
CEikApplication can create document objects. If there is a default resource file for 
this app, then it is added to the control environment.

If this function leaves, this should be treated as if construction had failed, 
and the object should be destroyed by the caller. */
EXPORT_C void CEikApplication::PreDocConstructL()
	{
	// Import the application's default resource file, if any
	TFileName* fileName=new(ELeave) TFileName;
	CleanupStack::PushL(fileName);
	*fileName=ResourceFileName();
	if (fileName->Length() && ConeUtils::FileExists(*fileName))
	   	iResourceFileOffset=iCoeEnv->AddResourceFileL(*fileName);
	RApaLsSession ls;
	CleanupClosePushL(ls);
	if(ls.Connect() == KErrNone)
		{
	// Try to get the localized application caption from AppArc.
	// Fall back to the old way if we can't get a localized caption.
		if ((iAppFlags&EFlagCaptionCorrectlyLocalised)==0)
			{
			TApaAppInfo info;
			User::LeaveIfError(ls.GetAppInfo(info, AppDllUid()));
			if (info.iCaption.Length()>0)
				{
				iCaption=info.iCaption;
				iAppFlags|=EFlagCaptionCorrectlyLocalised; 
				}
			}
		delete iCapabilityBuf;
		iCapabilityBuf=NULL;
		iCapabilityBuf=new(ELeave) TApaAppCapabilityBuf();
		User::LeaveIfError(ls.GetAppCapability(*iCapabilityBuf, AppDllUid()));
		}
	CleanupStack::PopAndDestroy(&ls); 
	if ((iAppFlags&EFlagCaptionCorrectlyLocalised)==0)
		{
		*fileName=AppFullName();
		TParsePtrC parse(*fileName);
		iCaption=parse.Name();
	 	}		
	CleanupStack::PopAndDestroy(fileName);
	}


/** Gets the default document name for this application.

@param aDocumentName On return, contains the default document file name. */
EXPORT_C void CEikApplication::GetDefaultDocumentFileName(TFileName& aDocumentName) const
	{
	TApaAppCaption candidate;
	
	// Try to get the application's default document file name from the application's
	// resource file. By convension, the default document file name TBUF is always located 
	// at the beginning of the applicaton's resource file, after the RSS_SIGNATURE and 
	// before the EIK_APP_INFO (i.e. with an offset of EDefaultNameResourceOffset).
	if (iResourceFileOffset)
	    {
		iCoeEnv->ReadResource(candidate, EDefaultNameResourceOffset+iResourceFileOffset);
		if (!candidate.Length())
			{
			aDocumentName.Zero();
			return;
			}
		}
	//If this application has no resource file, use the same behavior as above.
	else		
		{
		aDocumentName.Zero();
		return;
		}
	
	// Make sure we got the full document name including drive and path
	TParse parse;
	parse.Set(candidate, &aDocumentName, NULL);
	aDocumentName = parse.FullName();
	}

EXPORT_C CDictionaryStore* CEikApplication::OpenIniFileLC(RFs& aFs) const
/** Opens the application's .ini file, if one exists. 

If a .ini file does not exist for this application, or if it is corrupt, 
this function creates one and opens that. .ini files are located on system drive, 
in the same directory as the application EXE.

@param aFs File server session to use. 
@return Pointer to the dictionary store for the .ini file. */
	{
	// get the path of the ini file
	TParse parser;
	SetToIniFileNameL(parser);
	// ensure that all directories in the path exist 
	aFs.MkDirAll(parser.FullName()); // ignore the error //
	// open the ini file if it exists, otherwise create a new one
	CDictionaryStore* inifile=NULL;
	// if first attempt to open ini fails because of corrupt file, delete it and try again.
	TRAPD(err,inifile=CDictionaryFileStore::OpenL(aFs,parser.FullName(),AppDllUid()));
	if (err==KErrNone)
		CleanupStack::PushL(inifile);
	else if (err==KErrEof || err==KErrCorrupt)
		{
		User::LeaveIfError(aFs.Delete(parser.FullName()));
		inifile=CDictionaryFileStore::OpenLC(aFs,parser.FullName(),AppDllUid());
		err=KErrNone;
		}
	User::LeaveIfError(err);
	return inifile;
	}

EXPORT_C void CEikApplication::SetToIniFileNameL(TParse& aParser) const
/** Sets a supplied file name parser to contain the path of this application's 
.ini file.

@param aParser A file name parser. On return, this contains the path of 
the application's ini file. */
	{
	TChar sysDrive = RFs::GetSystemDriveChar();
	RBuf defaultDrive;
	_LIT(KColon,":");
	TInt maxSizeOfFileName = KColon().Length() + 1;
	defaultDrive.CreateL(maxSizeOfFileName);
	defaultDrive.Append(sysDrive);
	defaultDrive.Append(KColon());
	defaultDrive.CleanupClosePushL();
	RFs& fs = iEikonEnv->FsSession();
	TFileName fullName;
	User::LeaveIfError(fs.PrivatePath(fullName));

	TParsePtrC ptr(AppFullName());
	fullName.Append(ptr.Name());

	User::LeaveIfError(aParser.SetNoWild(KIniFileExtension,&defaultDrive,&fullName));
	CleanupStack::PopAndDestroy(&defaultDrive);
	}

EXPORT_C void CEikApplication::Capability(TDes8& aInfo) const
/** Gets the application's capabilities.

Application developers should not need to override this function. */
	{
	TApaAppCapability::CopyCapability(aInfo, *iCapabilityBuf);
	}

EXPORT_C void CEikApplication::NewAppServerL(CApaAppServer*& /*aAppServer*/)
/** Virtual function called by the framework when the application
has been launched as a server application.
Applications that wish to be used as server applications must
override this function to return their implementation of the server.

Base class implementation of this function leaves with KErrNotSupported, 
to prevent non-server applications from being launched as server applications. 

@param aAppServer The server pointer to be set. */
	{
	User::Leave(KErrNotSupported);
	}

EXPORT_C void CEikApplication::CEikApplication_Reserved1()
	{
	}
	
EXPORT_C void CEikApplication::CEikApplication_Reserved2()
	{
	}

/** Calling this method will ensure that the application Caption has been localized.
This is called at the start of applications override of CEikApplication's
CreateDocumentL, when application needs to started in Critical 
phase of Start-Up.

@param aLocalisableResourceFile Location of the localized resource file 
*/
EXPORT_C void CEikApplication::EnsureCaptionIsLocalisedL(const TDesC& aLocalisableResourceFile)
	{
	if (!(iAppFlags&EFlagCaptionCorrectlyLocalised))
		{
		TFileName name(aLocalisableResourceFile);
		BaflUtils::NearestLanguageFile(iEikonEnv->FsSession(), name);
		RResourceReader resourceReader;
		CResourceFile *resourceFile = CResourceFile::NewLC(iEikonEnv->FsSession(),aLocalisableResourceFile,0,0);
		resourceReader.OpenLC(resourceFile, 1);

		resourceReader.ReadUint32L(); 
		resourceReader.ReadUint32L();
		
		TPtrC captionShort = resourceReader.ReadTPtrCL();

		resourceReader.ReadUint32L();
		resourceReader.ReadUint32L(); 

		// read caption
		TPtrC caption = resourceReader.ReadTPtrCL();
		iCaption = caption;
		iAppFlags|=EFlagCaptionCorrectlyLocalised;
		CleanupStack::PopAndDestroy(2, resourceFile);
		}
	}


