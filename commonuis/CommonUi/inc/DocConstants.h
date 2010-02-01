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
* Description:  CDocumentHandler constants.
*
*/


#if !defined DOCCONSTANTS_H
#define DOCCONSTANTS_H


// Dummy filtering mime type. If this mime type is given as
// a content type parameters dochandler does nothing
// (just returns KErrNone).
_LIT8(KDummyMimeType, "text/vnd.nokia.filtering");

// Empty string
_LIT8(KNullText,"");

// Stream Uid's
const TUid KUidEmbedInputStream  = { 0x1000 };
const TUid KUidEmbedOutputStream = { 0x2000 };

// Application UID's needed in code
//const TUid KMediaGalleryUID3 = { 0x200009EE };//fix for Gallery remove 
const TUid KImageViewerUID = { 0x101f4d90 };
const TUid KAppManagerUID3 = { 0x101F8512 };
const TUid KFileManagerUID3 = { 0x101F84EB };
const TUid KPhotosUID3 = { 0x200009EE };
const TUid KMusicPlayerAppUid = { 0x102072C3 };
const TUid KVideoCenterAppUid = { 0x200159B2 };
// Landmark UI app
const TInt KLandmarkHandler  = 0x101F85C1;

// Length of maximum of file extension, for example ".html"
const TInt KLengthOfFileExtension = 5;

// This value is needed when parsing resources.
const TInt KRIMask(0x00000fff);

// Own resource file
_LIT( KDocResourceFileName, "z:\\resource\\documenthandlerui.rsc" );
// Temporary place to save which MIME-type is not recognized
//_LIT (KDocTempPath,  "d:\\system\\temp\\" );
_LIT (KDocTempPath,  "\\system\\temp\\" );
// This is used for temporary saving if d: drive is full.
_LIT (KDocTempPath2, "c:\\system\\temp\\" );  
// We save temp directory to under process private directory
//_LIT (KDocTemp,  "temp\\" );
// Last resort default file name for unnamed documents
_LIT( KDocFallBackName, "Data" );
//  Root of C-drive
//_LIT (KDocMemoryRoot,  "c:" );
//  Root of C-drive, used when saving to process privatepath
//_LIT (KDocDDriveRoot,  "d:" );

// Place where applications resource files should be found
_LIT( resourceaApps, "\\resource\\apps\\");
// Extension for resource files
_LIT( resExt, ".rsc" );
// Error message, CStringResourceReader::ReadResourceString might return  
// this if filename is not fetched.
_LIT( errorStr, "Resolving Error" );

// Mime-type of flash files
_LIT(KFlashMimeType, "application/x-shockwave-flash");

// Hard coded MIME-types
_LIT8( KDocMimeCalendar,     "text/calendar"                     );
_LIT8( KDocMimeCalendar2,    "text/X-vCalendar"                 );
_LIT8( KDocMimeCard,         "text/X-vCard"                      );
/*
_LIT( KDocExtCalendar,      ".vcs"                              );
_LIT( KDocExtCard,          ".vcf"                              );
_LIT8( KDocMimeAmr,          "audio/x-amr"                       );
_LIT( KDocExtAmr,           ".amr"                              );
_LIT8( KDocMimeWbmp,         "image/vnd.wap.wbmp"                );
_LIT( KDocExtWbmp,          ".wbmp"                             );
_LIT8( KDocMimeWmlc,         "application/vnd.wap.wmlc"          );
_LIT( KDocExtWmlc,          ".wmlc"                             );
_LIT8( KDocMimeOtaBitmap,    "image/vnd.nokia.ota-bitmap"        );
_LIT( KDocExtOtaBitmap,     ".ota"                              );
_LIT8( KDocMimeXOtaBitmap,   "image/x-ota-bitmap"                );
*/
_LIT( KDocMimeJad,          "text/vnd.sun.j2me.app-descriptor"  );
_LIT( KDocExtJad,           ".jad"                              );
/*
_LIT8( KDocMimeJar1,         "application/vnd.sun.java-archive"  );
_LIT8( KDocMimeJar2,         "application/java-archive"         );
_LIT( KDocExtJar,           ".jar"                              );
*/
_LIT8( KDocMimeMSWord,         	"application/msword"            );
_LIT8( KDocMimeMSExcel,        	"application/msexcel"           );
_LIT8( KDocMimeMSPowerPoint,   	"application/x-mspowerpoint"    );
_LIT8( KDocMimePdf,   		   	"application/pdf"		        );
_LIT8( KDocMimeZip1,           	"application/zip"               );
_LIT8( KDocMimeZip2, 			"application/x-compressed"		);
_LIT8( KDocMimeZip3,			"application/x-zip-compressed"	); 
_LIT8( KDocMimeZip4,			"multipart/x-zip"				);
_LIT8( KDocMimeTextPlain,		"text/plain"	    			);

_LIT( KMIMETypeImage,           "image/"                        );
_LIT( KMIMETypeRingTone,        "application/vnd.nokia.ringing-tone");
_LIT( KMIMETypeAudio,           "audio/"                        );
_LIT( KMIMETypeAudioMp4,        "audio/mp4"                     );
_LIT( KMIMETypeAudioMpeg,       "audio/mpeg"                    );
_LIT( KMIMETypeVideo,           "video/"                        );
_LIT( KMIMETypeVideoReal,       "application/vnd.rn-realmedia"  );
_LIT( KMIMETypeVideoSdp,        "application/sdp"               );
_LIT( KMIMETypeSvg,             "image/svg+xml"                 );

/**
* Result from the "save as" query.
*/
enum TDocSaveAsResult
    {
    EDocFileCancelWrite = -1203, // Cancel the operation
    EDocFileOverWrite,          // Overwrite
    EDocFileRenameNew           // Rename
    };

/**
* Service mode.
* Some mime types e.g. text/x-vCalendar can not be saved
* (there is no sense of doing it), but can be opened. Others can be
* Saved but not opened. Names should be rather self-explanatory.
*/
enum TDocServiceMode
{
    EDocOpenAndSave,            // Handler can open and save the data type
    EDocOpenOnly,               // Handler can only open the data type
    EDocSaveOnly                // Handler can only open the data type
};

#endif // DOCCONSTANTS_H
            
// End of File
