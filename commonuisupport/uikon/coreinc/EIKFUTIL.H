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

#ifndef __EIKFUTIL_H__
#define __EIKFUTIL_H__

#include <e32std.h>
#include <f32file.h>
#include <badesca.h>
#include <bautils.h>
#include <eikenv.h>

class CFont;
class CBaflFileSortTable;
class TResourceReader;


/** Provides a set of drive, path and file utility functions.

This class is essentially a thin layer over the BaflUtils class.

@publishedAll 
@released */
NONSHARABLE_CLASS(EikFileUtils)
	{ 
public:
	inline static TBool PathExists(const TDesC& aPath);
	inline static TInt IsFolder(const TDesC& aFullName, TBool& aIsFolder);
	inline static TBool FolderExists(const TDesC& aFolderName);
	inline static TFileName FolderNameFromFullName(const TDesC& aFullName);
	inline static TFileName DriveAndPathFromFullName(const TDesC& aFullName);
	inline static TFileName RootFolderPath(const TBuf<1> aDriveLetter);
	inline static void AbbreviateFileName(const TFileName& aOriginalFileName, TDes& aAbbreviatedFileName);
	IMPORT_C static TFileName AbbreviatePath(TDesC& aPathName, const CFont& aFont, TInt aMaxWidthInPixels);
	inline static TBool UidTypeMatches(const TUidType& aFileUid, const TUidType& aMatchUid);
	inline static TInt Parse(const TDesC& aName);
	IMPORT_C static TFileName ValidateFolderNameTypedByUserL(const TDesC& aFolderNameTypedByUser, const TDesC& aCurrentPath);
	inline static TInt CopyFile(const TDesC& aSourceFullName, const TDesC& aTargetFullName, TUint aSwitch = CFileMan::EOverWrite);
	inline static TInt RenameFile(const TDesC& aOldFullName, const TDesC& aNewFullName, TUint aSwitch = CFileMan::EOverWrite);
	inline static TInt DeleteFile(const TDesC& aSourceFullName, TUint aSwitch=0);
	inline static TInt CheckWhetherFullNameRefersToFolder(const TDesC& aFullName, TBool& aIsFolder);
	inline static TInt MostSignificantPartOfFullName(const TDesC& aFullName, TFileName& aMostSignificantPart);
	inline static TInt CheckFolder(const TDesC& aFolderName);
	inline static TInt DiskIsReadOnly(const TDesC& aFullName, TBool& aIsReadOnly);
	inline static void UpdateDiskListL(const RFs& aFs,CDesCArray& aArray,TBool aIncludeRom,TDriveNumber aDriveNumber);
	inline static void RemoveSystemDirectory(CDir& aDir);
	inline static TBool IsFirstDriveForSocket(TDriveUnit aDriveUnit);
	inline static TInt SortByTable(CDir& aDir,CBaflFileSortTable* aTable);
private:
	EikFileUtils();
	};


/** Tests whether a path exists.

@param aPath The path to check. 
@return ETrue if the path exists, EFalse otherwise. */
inline TBool EikFileUtils::PathExists(const TDesC& aPath)
	{	return BaflUtils::PathExists(CEikonEnv::Static()->FsSession(),aPath);	}

/** Tests whether aFullName is a folder.

@param aFullName The drive and path to test. 
@param aIsFolder On return, indicates whether aFullName is a folder. 
@return KErrNone if successful otherwise another of the system-wide error codes. */
inline TInt EikFileUtils::IsFolder(const TDesC& aFullName, TBool& aIsFolder)
	{	return BaflUtils::IsFolder(CEikonEnv::Static()->FsSession(), aFullName,aIsFolder);	}

/** Tests whether a specified folder exists. 

This returns a boolean value indicating whether the folder exists: see also 
CheckFolder() which returns an error code instead.

@param aFolderName The folder's path.
@return ETrue if the folder exists, EFalse if not. */
inline TBool EikFileUtils::FolderExists(const TDesC& aFolderName)
	{	return BaflUtils::FolderExists(CEikonEnv::Static()->FsSession(), aFolderName);	}

/** Gets a folder name from a path and file name.

@param aFullName The full path and file name from which the folder will be 
obtained. 
@return Folder name */
inline TFileName EikFileUtils::FolderNameFromFullName(const TDesC& aFullName)
	{	return BaflUtils::FolderNameFromFullName(aFullName);	}

/** Parses the specified full path and file name to obtain the drive and path.

@param aFullName The full path and file name from which the drive and path 
will be obtained. 
@return The drive and path. */
inline TFileName EikFileUtils::DriveAndPathFromFullName(const TDesC& aFullName)
	{ 	return BaflUtils::DriveAndPathFromFullName(aFullName);	}

/** Gets the root folder for the specified drive.

@param aDriveLetter The drive letter, C for example. 
@return The root folder for the drive, C:\ for example. */
inline TFileName EikFileUtils::RootFolderPath(const TBuf<1> aDriveLetter)
	{	return BaflUtils::RootFolderPath(aDriveLetter);	}

/** Abbreviates a file name.

If aOriginalFileName is less than the maximum length of aAbbreviatedFileName, 
then the name is simply copied to aAbbreviatedFileName.

If this is not the case, then the left-most characters of aOriginalFileName are 
copied to aAbbreviatedFileName, up to aAbbreviatedFileName's maximum length-1 and 
aAbbreviatedFileName's first character is set to be an ellipsis.

For example, if c:\\home\\letters\\abcdef is the original file name and aAbbreviatedFileName 
allows only 7 characters, the abbreviated file name will be ...abcdef. 
This can be used to display a file or folder name in an error or progress 
dialog.

@param aOriginalFileName Original file name. 
@param aAbbreviatedFileName On return, the abbreviated file name. */
inline void EikFileUtils::AbbreviateFileName(const TFileName& aOriginalFileName, TDes& aAbbreviatedFileName)
	{	BaflUtils::AbbreviateFileName(aOriginalFileName,aAbbreviatedFileName);	}

/** Tests whether two UID types match.

A match is made if each UID in aMatchUid is either identical to the corresponding 
one in aFileUid, or is KNullUid.

@param aFileUid The UID type to match. 
@param aMatchUid The UID type to match against. 
@return ETrue if the UIDs match, EFalse if not. */
inline TBool EikFileUtils::UidTypeMatches(const TUidType& aFileUid, const TUidType& aMatchUid)
	{	return BaflUtils::UidTypeMatches(aFileUid,aMatchUid);	}

/** Tests whether a specified file name can be parsed.

@param aName The file name to parse.
@return KErrNone if the filename can be parsed, otherwise one 
of the system-wide error codes. 
@see TParse */
inline TInt EikFileUtils::Parse(const TDesC& aName)
	{	return BaflUtils::Parse(aName);	}

/** Copies the specified file.

Notes:

- files can be copied across drives

- open files can be copied only if they have been opened using the EFileShareReadersOnly 
file share mode

- the source file's attributes are preserved in the target file

@param aSourceFullName Path indicating the file(s) to be copied. Any path 
components which are not specified here will be taken from the session path. 
@param aTargetFullName Path indicating the directory into which the file(s) 
are to be copied. 
@param aSwitch Optional switch to allow overwriting files with the same name 
in the target directory, or recursion. By default, this function operates with 
overwriting and non-recursively. Switch options are defined using the enum TSwitch. 
If recursive operation is set, any intermediate directories are created. If no overwriting 
is set, any files with the same name are not overwritten, and an error is returned 
for that file.
@return KErrNone if the copy is successful, otherwise another of the system-wide 
error codes. */
inline TInt EikFileUtils::CopyFile(const TDesC& aSourceFullName, const TDesC& aTargetFullName, TUint aSwitch)
	{	return BaflUtils::CopyFile(CEikonEnv::Static()->FsSession(),aSourceFullName,aTargetFullName,aSwitch);	}

/** Renames one or more files or directories. 

This can also be used to move files by specifying different destination and 
source directories, but note that the destination and source directories must be 
on the same drive.

If moving files, you can set aSwitch so that any files with the same name 
that exist in the target directory are overwritten. If aSwitch is set for 
no overwriting, any files with the same name are not overwritten, and an error 
(KErrAlreadyExists) is returned for that file.

This function can only operate non-recursively, so that only the matching 
files located in the single directory specified by aOldFullName may be renamed.

Read-only, system and hidden files may be renamed or moved, and the source 
file's attributes are preserved in the target file, but attempting to rename 
or move an open file will return an error for that file.

@param aOldFullName Path specifying the file or directory to be renamed. 
@param aNewFullName Path specifying the new name for the file or directory. 
Any directories specified in this path which do not exist will be created. 
@param aSwitch Optional, sets whether files are overwritten on the target. 
@return KErrNone if successful otherwise another of the system-wide error codes. */
inline TInt EikFileUtils::RenameFile(const TDesC& aOldFullName, const TDesC& aNewFullName, TUint aSwitch)
	{	return BaflUtils::RenameFile(CEikonEnv::Static()->FsSession(),aOldFullName,aNewFullName,aSwitch);	}

/** Deletes one or more files.

This function may operate recursively or non-recursively. When operating non-recursively, 
only the matching files located in the directory specified in aSourceFullName 
are affected. When operating recursively, all matching files in the directory 
hierarchy below the directory specified in aSourceFullName are deleted.

Attempting to delete read-only or open files returns an error.

@param aSourceFullName Path indicating the file(s) to be deleted. This can 
either be a full path, or a path relative to the session path. Use wildcards 
to specify more than one file. 
@param aSwitch Determines whether this function operates recursively. By default, 
this function operates non-recursively. 
@return KErrNone if aSourceFullName is successfully deleted, otherwise another 
of the system-wide error codes. */
inline TInt EikFileUtils::DeleteFile(const TDesC& aSourceFullName, TUint aSwitch)
	{	return BaflUtils::DeleteFile(CEikonEnv::Static()->FsSession(), aSourceFullName,aSwitch);	}

/** Tests whether a file specification is a valid folder name.

@param aFullName The string to check. 
@param aIsFolder True if aFullName is a valid folder name, otherwise false.
@return KErrNone if successful, otherwise another of the system-wide error codes 
(probably because aFullName cannot be parsed). */
inline TInt EikFileUtils::CheckWhetherFullNameRefersToFolder(const TDesC& aFullName, TBool& aIsFolder)
	{	return BaflUtils::CheckWhetherFullNameRefersToFolder(aFullName,aIsFolder);	}

/** Gets the folder name if the specified item is a valid folder name, otherwise gets the file name.

@param aFullName Item to parse. 
@param aMostSignificantPart On return, the folder or file name.
@return KErrNone if successful otherwise another of the system-wide error codes. */
inline TInt EikFileUtils::MostSignificantPartOfFullName(const TDesC& aFullName, TFileName& aMostSignificantPart)
	{	return BaflUtils::MostSignificantPartOfFullName(aFullName,aMostSignificantPart);	}

/** Tests whether the specified folder exists and can be opened.

This returns an error code if the folder does not exist: see also FolderExists() 
which returns a boolean value.

@param aFolderName The folder's name and path. 
@return KErrNone if aFolderName exists, otherwise another of the system-wide 
error codes. */
inline TInt EikFileUtils::CheckFolder(const TDesC& aFolderName)
	{	return BaflUtils::CheckFolder(CEikonEnv::Static()->FsSession(),aFolderName);	}

/** Tests whether the specified drive is read-only.

@param aFullName File name, including drive. 
@param aIsReadOnly On return, true if the drive is read-only, otherwise false. 
@return KErrNone if successful otherwise another of the system-wide error codes. */
inline TInt EikFileUtils::DiskIsReadOnly(const TDesC& aFullName, TBool& aIsReadOnly)	
	{	return BaflUtils::DiskIsReadOnly(CEikonEnv::Static()->FsSession(),aFullName,aIsReadOnly);	}

/** Gets a list of all drives present on the system.

The file server is interrogated for a list of the drive letters for all available 
drives. The drive letter that corresponds to aDriveNumber is added to the list 
regardless of whether it is present, or is corrupt. Also, the C: drive and the 
primary partitions on removable media slots are forced onto the list, even if 
corrupt or not present.

@param aFs A connected session with the file server. 
@param aArray On return, contains the drive letters that correspond to the available 
drives. The drive letters are uppercase and are in alphabetical order. 
@param aIncludeRom ETrue if the ROM is included as a drive, EFalse otherwise. 
@param aDriveNumber The drive to force into the list, e.g. the drive in the default 
path. */
inline void EikFileUtils::UpdateDiskListL(const RFs& aFs,CDesCArray& aArray,TBool aIncludeRom,TDriveNumber aDriveNumber)
	{	BaflUtils::UpdateDiskListL(aFs,aArray,aIncludeRom,aDriveNumber);	}

/** Removes the System directory from a list of directory entries.

@param aDir Array of directory entries. */
inline void EikFileUtils::RemoveSystemDirectory(CDir& aDir)
	{	BaflUtils::RemoveSystemDirectory(aDir);	}

/** Tests whether the specified drive corresponds to the primary partition 
in a removable media slot.

Note that the function assumes that the D: drive corresponds to the primary 
partition on socket 0, and that the E: drive corresponds to the primary 
partition on socket 1 (a socket is a slot for removable media). This mapping 
may not always be the case because it is set up in the variant layer of Symbian 
OS. 

@param aDriveUnit The drive to check. 
@return True if the drive is the primary partition in a removable media 
slot. True is also returned if the drive is C:. False is returned otherwise. */
inline TBool EikFileUtils::IsFirstDriveForSocket(TDriveUnit aDriveUnit)
	{	return BaflUtils::IsFirstDriveForSocket(aDriveUnit);	}

/** Sorts files by UID.

The caller supplies a table which specifies the order in which files are to be sorted. 
The files whose UID3 is the first UID in the table appear first. The files whose UID3 
is the UID specified second appear next, and so on. Files whose UID3 is not specified 
in the table, and directories, appear at the end of the list, with directories preceding 
the files, and with files sorted in ascending order of UID3.

This function is used for customising how lists of application files are sorted.

@param aDir The array of files and directories to sort. 
@param aTable A sort order table containing the UIDs to use in the sort. 
@return KErrNone if successful otherwise another of the system-wide error codes. */
inline TInt EikFileUtils::SortByTable(CDir& aDir,CBaflFileSortTable* aTable)
	{	return BaflUtils::SortByTable(aDir,aTable);	}


#endif	// __EIKFUTIL_H__
