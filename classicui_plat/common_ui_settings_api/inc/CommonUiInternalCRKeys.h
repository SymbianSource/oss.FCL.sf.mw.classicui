/*
* Copyright (c) 2002-2006 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:  Internal Central Repository keys.
*
*/


#ifndef COMMONUI_INTERNAL_CR_KEYS_H
#define COMMONUI_INTERNAL_CR_KEYS_H

const TUid KCRUidCommonUi = { 0x101F8772 };

/**
 * Automatic highlight.
 *
 * Possible values:
 * 0: off
 * 1: on (default value)
 */
const TUint32 KCuiAutomaticHighlight = 0x00000001;

/**
 * Minimum number of digits.
 *
 * Possible values:
 * Allowed number of digits that can be handled as phone number is determined 
 * by Symbian SW. Default value is 5.
 */
const TUint32 KCuiMinDigitsToFind = 0x00000002;

/**
 * A list of application Uids that support progressive download. 
 *
 * Possible values:
 * Max. amount of Uids is 64. They must be in hexadecimal format and separated
 * by semicolon. 
 *
 * Example: 0x10005A3E;0x102072C3
 */
const TInt KCuiProgDownloadUids = 0x00000003;

/**
 * A list of mime types for the 1st Uid in the Uid-list (KCuiProgDownloadUids).
 *
 * Possible values:
 * Max. length of the list is 1024 characters. Wildcards are allowed. Mime 
 * types must be separated by semicolon.
 *
 * Example: video/vnd.rn-realvideo;application/vnd.rn-realmedia
 *
 * Note: Key Int range 0x00000004 - 0x00000043 is reserved for mime-type sets 
 * i.e. value 0x00000004 (KCuiMimeTypeSet1) is reserved for the mime-types of 
 * the 1st Uid defined in the Uid-list, 0x00000005 (KCuiMimeTypeSet2) for the 
 * 2nd, 0x00000006 (KCuiMimeTypeSet3) for the 3rd, etc.
 */
const TInt KCuiMimeTypeSet1 = 0x00000004;

/**
 * A list of mime types for the 2nd Uid in the Uid-list (KCuiProgDownloadUids).
 *
 * Possible values:
 * Max. length of the list is 1024 characters. Wildcards are allowed. Mime 
 * types must be separated by semicolon.
 *
 * Example: video/vnd.rn-realvideo;application/vnd.rn-realmedia
 *
 * Note: Key Int range 0x00000004 - 0x00000043 is reserved for mime-type sets 
 * i.e. value 0x00000004 (KCuiMimeTypeSet1) is reserved for the mime-types of 
 * the 1st Uid defined in the Uid-list, 0x00000005 (KCuiMimeTypeSet2) for the 
 * 2nd, 0x00000006 (KCuiMimeTypeSet3) for the 3rd, etc.
 */
const TInt KCuiMimeTypeSet2 = 0x00000005;

#endif

// End of File
