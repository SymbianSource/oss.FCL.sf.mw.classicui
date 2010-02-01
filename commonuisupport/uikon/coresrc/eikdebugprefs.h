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

#ifndef EIKDEBUGPREFS_H
#define EIKDEBUGPREFS_H

//
//	class CEikDebugPreferences
//

/**
@internalComponent
*/
NONSHARABLE_CLASS(CEikDebugPreferences) : public CBase
	{
public:
	enum TFlag
		{
		EFlagDebugKeysOn				=0x00000001,
		EFlagOOMTestingOnAppStartUp		=0x00000002,
		EFlagOOMTestingOnEiksrvStartUp	=0x00000004,
		EFlagOOMTestingOnConsoleStartUp	=0x00000008
		};
public:
	IMPORT_C static CEikDebugPreferences* New();
	IMPORT_C static CEikDebugPreferences* NewL();
	IMPORT_C static CEikDebugPreferences* NewLC();
	IMPORT_C ~CEikDebugPreferences();
	IMPORT_C void StoreL(RFs& aFileServerSession);
	IMPORT_C TInt Restore(RFs& aFileServerSession); // can be used with or without a CTrapHandler being currently installed
	IMPORT_C void RestoreL(RFs& aFileServerSession);
	IMPORT_C void SetKeysOn(const TBool& aDebugKeysOn);
	IMPORT_C TBool KeysOn() const;
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	inline void SetFlags(TUint aFlags);
	inline TUint Flags() const;
private:
	CEikDebugPreferences();
private:
	TUint iFlags;
	TUint iSpare;
	};

inline void CEikDebugPreferences::SetFlags(TUint aFlags)
	{
	iFlags=aFlags;
	}

inline TUint CEikDebugPreferences::Flags() const
	{
	return iFlags;
	}

#endif	// EIKDEBUGPREFS_H
