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



#include <eikenv.h>
#include <eikappui.h>
#include <eikdebug.h>
#include <s32file.h>

#include "eikdebugprefs.h"

// The dial dialog preferences UID incremented by 1
const TUid KEikDebugPreferencesUID={0x10000167};

//
//	class CEikDebugPreferences
//

/**
 *
 * Constructs a new <code>CEikDebugPreferences</code> object.
 *
 * @since    7.0
 * @return "CEikDebugPreferences*"
 *           Pointer to the new <code>CEikDebugPreferences</code> object.
 *
 */
EXPORT_C CEikDebugPreferences* CEikDebugPreferences::New()
	{
	return new CEikDebugPreferences;
	}

/**
 *
 * Constructs a new <code>CEikDebugPreferences</code> object. Object is
 * not placed on to the cleanup stack.
 *
 * @since   7.0
 * @return "CEikDebugPreferences*"
 *			 Pointer to the new <code>CEikDebugPreferences</code> object.
 */
EXPORT_C CEikDebugPreferences* CEikDebugPreferences::NewL()
	{
	return new(ELeave) CEikDebugPreferences;
	}

/**
 *
 * Constructs a new <code>CEikDebugPreferences</code> object, and
 * pushes itself on to the cleanup stack.
 *
 * @since 7.0
 * @return "CEikDebugPreferences*"
 *			 Pointer to the new <code>CEikDebugPreferences</code> object.
 * 
 */
EXPORT_C CEikDebugPreferences* CEikDebugPreferences::NewLC()
	{
	CEikDebugPreferences* self=new(ELeave) CEikDebugPreferences;
	CleanupStack::PushL(self);
	return self;
	}

CEikDebugPreferences::CEikDebugPreferences()
:	iFlags(0)
	{
	}

EXPORT_C CEikDebugPreferences::~CEikDebugPreferences()
	{
	}

/**
 * Wrapper around the <code>void CEikDebugPreferences::RestoreL(RFs& aFileServerSession)</code>.
 * Also, trap harness is created, using<code>CTrapCleanup::New()</code>, if already
 * not present for the current thread.
 * 
 * @param	  "RFs& aFileServerSession"
 *			   Current session with the File Server.
 * @return	  "TInt"
 *             Returns one of the system wide error codes.  
 * @since      7.0
 */
EXPORT_C TInt CEikDebugPreferences::Restore(RFs& aFileServerSession)
	{
	CTrapCleanup* trapCleanup=NULL;
	if (User::TrapHandler()==NULL)
		{
		trapCleanup=CTrapCleanup::New();
		}
	TRAPD(error, CEikDebugPreferences::RestoreL(aFileServerSession));
	delete trapCleanup;
	return error;
	}

EXPORT_C void CEikDebugPreferences::RestoreL(RFs& aFileServerSession)
	{
	CDictionaryStore* iniFile=CDictionaryFileStore::SystemLC(aFileServerSession);
	if (iniFile->IsPresentL(KEikDebugPreferencesUID))
		{
		RDictionaryReadStream stream;
		stream.OpenLC(*iniFile,KEikDebugPreferencesUID);
		InternalizeL(stream);
		CleanupStack::PopAndDestroy(&stream);
		}
	CleanupStack::PopAndDestroy(iniFile);
	}

EXPORT_C void CEikDebugPreferences::StoreL(RFs& aFileServerSession)
	{
	CDictionaryStore* iniFile=CDictionaryFileStore::SystemLC(aFileServerSession);
	
	RDictionaryWriteStream stream;
	stream.AssignLC(*iniFile,KEikDebugPreferencesUID);
	ExternalizeL(stream);
	stream.CommitL();
	CleanupStack::PopAndDestroy(); // stream

	iniFile->CommitL();
	CleanupStack::PopAndDestroy(); //iniFile
	}

EXPORT_C void CEikDebugPreferences::SetKeysOn(const TBool& aDebugKeysOn)
	{
	if(aDebugKeysOn)
		{
		iFlags|=EFlagDebugKeysOn;
		}
	else
		{
		iFlags&=~EFlagDebugKeysOn;
		}
	}

EXPORT_C TBool CEikDebugPreferences::KeysOn() const
	{
	return iFlags & EFlagDebugKeysOn;
	}

/**
Externalises the debug preferences object to a write stream.
@internalComponent
*/
EXPORT_C void CEikDebugPreferences::ExternalizeL(RWriteStream& aStream) const
	{
	aStream.WriteInt16L(CEikonEnv::Version().iBuild);
	aStream.WriteUint8L(iFlags);
	}

/**
Internalises the debug preferences object from a read stream.
@internalComponent
*/
EXPORT_C void CEikDebugPreferences::InternalizeL(RReadStream& aStream)
	{
	aStream.ReadInt16L(); // the version - this is not currently used and so is discarded
	iFlags = aStream.ReadUint8L();
	}

