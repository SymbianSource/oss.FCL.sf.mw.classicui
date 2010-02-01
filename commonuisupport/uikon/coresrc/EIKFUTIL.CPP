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
 
#include <e32hal.h>
#include <f32file.h>
#include <barsread.h>
#include <apparc.h>
#include <eikenv.h> 
#include <eikfutil.h>
#include <uiklafgt/eikcore.rsg>


/**
Adds a textual message to certain error codes
@param aErrorCode Standard system error code.
@internalComponent
*/
LOCAL_D void ReportErrorAndLeaveL(TInt aErrorCode)
	{
	// reports the error to the user (in some way) and always leaves
	if (aErrorCode == KErrNone)
		return;
	if ((aErrorCode == KErrNotReady) || (aErrorCode == KErrCorrupt))
		{
		CEikonEnv* env = CEikonEnv::Static();
		if (aErrorCode == KErrNotReady)
			env->LeaveWithInfoMsg(R_EIK_TBUF_DISK_NOT_PRESENT);
		else 
			env->LeaveWithInfoMsg(R_EIK_TBUF_CANNOT_BE_READ);
		}
	else
		User::Leave(aErrorCode);
	}

EXPORT_C TFileName EikFileUtils::AbbreviatePath(TDesC& aPathName, const CFont& aFont, TInt aMaxWidthInPixels)
/** Gets an abbreviated path.

Calculates the space that is available to display aPathName according to the 
font size and the display width. If there is sufficient space then aPathName 
is returned. If there is not sufficient space, aPathName is abbreviated 
to fit the available space, prefixed with an ellipsis and the abbreviation 
is returned.

@param aPathName The full path name. 
@param aFont The font used to display the path. 
@param aMaxWidthInPixels The available display width in pixels. 
@return The abbreviated path. */
	{
	TInt widthOfOriginalText = aFont.TextWidthInPixels(aPathName);
	TInt pathNameLen = aPathName.Length();
	// return original filename if it fits into available space
	if ((widthOfOriginalText <= aMaxWidthInPixels) || (pathNameLen == 0))
		{
		return TFileName(aPathName);
		}
	const TChar ellipsis(0x2026);
	if (aMaxWidthInPixels <= 0)
		{
		TBuf<1> bufEllipsis;
		bufEllipsis.Append(ellipsis);
		return TFileName(bufEllipsis);
		}	
	// compute the estimated position of the start of the abbreviated pathname based
	// on the average pixel width of a character of the original pathname
	TInt estimatedPos = pathNameLen - (aMaxWidthInPixels * pathNameLen) / widthOfOriginalText;
	if (estimatedPos >= pathNameLen)
		{
		estimatedPos = pathNameLen -1;
		}
	else if (estimatedPos <= 0)
		{
		estimatedPos = 0;
		}
	TChar tmpChar;
	TFileName pathName(aPathName); // create a non-const copy of the pathname for further manipulations
	TPtr tmpPathName = pathName.MidTPtr(estimatedPos);	
	tmpChar = tmpPathName[0];
	tmpPathName[0] = ellipsis;
	TInt widthOfCurrentText = aFont.TextWidthInPixels(tmpPathName);
	if (widthOfCurrentText <  aMaxWidthInPixels) // text fits into available space
		{
		for(TInt i = estimatedPos - 1; i >= 0; --i) // extend text until it is too long
			{
			tmpPathName[0] = tmpChar; // restore the original character
			tmpPathName.Set(pathName.MidTPtr(i)); // extend pathname by one character and set ellipsis
			tmpChar = tmpPathName[0];
			tmpPathName[0] = ellipsis;
			widthOfCurrentText = aFont.TextWidthInPixels(tmpPathName);
			if(widthOfCurrentText > aMaxWidthInPixels) // found shortest pathname that doesn't fit into max width
				{
				tmpPathName.Set(pathName.MidTPtr(i + 1));
				tmpPathName[0] = ellipsis;
				break;
				}
			}
		}
	else if (widthOfCurrentText >  aMaxWidthInPixels) // text doesn't fit into available space
		{
		for(TInt i = estimatedPos + 1; i < pathNameLen; ++i) // shorten text until it fits
			{
			tmpPathName[0] = tmpChar; // restore the original character
			tmpPathName.Set(pathName.MidTPtr(i)); // shorten pathname by one character and set ellipsis
			tmpChar = tmpPathName[0];
			tmpPathName[0] = ellipsis;
			widthOfCurrentText = aFont.TextWidthInPixels(tmpPathName);
			if(widthOfCurrentText <= aMaxWidthInPixels) // found longest pathname that fits into max width
				{
				break;
				}
			}	
		}
	return tmpPathName;	
	}

EXPORT_C TFileName EikFileUtils::ValidateFolderNameTypedByUserL(const TDesC& aFolderNameTypedByUser, const TDesC& aCurrentPath)
/** Checks if a folder name (without drive or path) is valid and if it is, 
returns the full name of the folder.

Leaves with an appropriate info message if the folder name is invalid.

@param aFolderNameTypedByUser Folder name to check. 
@param aCurrentPath Path to which to add the folder. 
@return aFolderNameTypedByUser appended to aCurrentPath. */
	{
	CEikonEnv* env = CEikonEnv::Static();
	TFileName newFolderFullName = aCurrentPath;
	TInt retCode=BaflUtils::ValidateFolderNameTypedByUserL(env->FsSession(),aFolderNameTypedByUser,aCurrentPath, newFolderFullName);
	switch(retCode)
		{
		case KErrNone:
			break;
		case KErrArgument:
			env->LeaveWithInfoMsg(R_EIK_TBUF_NO_FOLDERNAME_SPECIFIED);
			break;
		case KErrBadName:
			env->LeaveWithInfoMsg(R_EIK_TBUF_INVALID_FOLDER_NAME);
			break;
		case KErrTooBig:
			env->LeaveWithInfoMsg(R_EIK_TBUF_FOLDERNAME_TOO_LONG);
			break;
		default:
			ReportErrorAndLeaveL(retCode);
			break;
		};
	return newFolderFullName;
	}
