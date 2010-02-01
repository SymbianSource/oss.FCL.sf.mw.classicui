/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Write logger.
*
*/









#include <eikenv.h>
#include <eikappui.h>
#include <eikapp.h>

#include "bctestlogger.h"

_LIT( KPathBase, "c:\\BCTestLog\\" );  // directory for test results in FFS
_LIT( KTimeFormat, "%:0%J%:1%T%:2%S%:3%+B" );
_LIT( KBCTestLogEnd, "_TestLog.txt" ); // end of auto test log filename
_LIT( KDateTimeFormat, "%-B%/0%1%/1%2%/2%3%/3 %:0%J%:1%T%:2%S%:3%+B" );
_LIT( KMainLog, "c:\\BCTestLog\\BCTestLog.txt" );  // main log file

_LIT( KGeneralLogInfo, "Log file for automated test's results created " );
_LIT( KTimeLogStart, " -- " );
_LIT( KTimeLogEnd, " --\r\n" );
_LIT( KGetTimeFailed, "Getting time failed" );
_LIT( KVersionFile, "c:\\bctestlog\\release_note.txt" );
_LIT( KLineEnd, "\r\n\n" );
_LIT( KVersion, "Version of BC tester:" );

const TInt KTheMaxInterval = 2;
const TInt KTempBufferLenth = 128;
const int KMaxLength = 255;


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// static Constructor
// ---------------------------------------------------------------------------
//
CBCTestLogger* CBCTestLogger::NewL( CEikonEnv* aEikonEnv )
    {
    CBCTestLogger* self = new( ELeave ) CBCTestLogger( aEikonEnv );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//    
CBCTestLogger::CBCTestLogger( CEikonEnv* aEikonEnv ): iEikEnv( aEikonEnv )
    {    
    }
    
// ---------------------------------------------------------------------------
// private Constructor
// ---------------------------------------------------------------------------
// 
CBCTestLogger::~CBCTestLogger()
    {
    iAtLogFile.Close();
    }
    
// ---------------------------------------------------------------------------
// ConstructL, 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestLogger::ConstructL()
    {
    TInt err = KErrNone;    
    
    iEikEnv = CEikonEnv::Static();
    RFs tempServer = iEikEnv->FsSession();    
    
    // \BCTestLog directory created if doesn't exist
    err = tempServer.MkDir( KPathBase );
    if ( err == KErrAlreadyExists || err == KErrNone )  
        {
        err = KErrNone; // Directory already exists - no error
        }        
    else
        {
        User::Leave(err);
        }
        
    // Read version of bc test from realease_note.txt.
    RFile vFile;
    User::LeaveIfError( 
	    vFile.Open( tempServer, KVersionFile, EFileRead | EFileShareAny ) != KErrNone );                
    
    TBuf<KMaxLength> versionLine;
	ReadLineL( vFile, versionLine);
    vFile.Close();
    	    
    // Create autotest results log filename
    iAtLogFileName = KPathBase;
    iAtLogFileName.Append( AppCaption() );
    iAtLogFileName.Append( KBCTestLogEnd );    
    
    // Open log file for autotest results.
    // If the file already exists, replace it.
    err = iAtLogFile.Replace( tempServer,
                              iAtLogFileName,
                              EFileWrite | EFileStreamText );

    if (err != KErrNone)
        {
        User::Leave( err );
        }

    iBuf.Zero();
    // Write version of bc tester in log file.
    iBuf.Append( KVersion );    
    iBuf.Append( versionLine );
    iBuf.Append( KLineEnd );
    iBuf.Append( KGeneralLogInfo );
    TTime homeTime;
    homeTime.HomeTime();
    TBuf<KTempBufferLenth> tempBuf;
    homeTime.FormatL( tempBuf, KDateTimeFormat );    
    iBuf.Append( tempBuf );    
    iBuf.Append( KLogTwoLine );          
    WriteToFileL( iAtLogFile, iBuf );
    
    CreateMainLogL();
    }

// ---------------------------------------------------------------------------
// CBCTestLogger::CreateMainLogL
// ---------------------------------------------------------------------------
//
void CBCTestLogger::CreateMainLogL()
    {
    RFile mainFile;
    RFs tempServer = iEikEnv->FsSession();
    TInt err = mainFile.Create( tempServer, KMainLog, 
        EFileWrite | EFileStreamText );
    if ( err != KErrNone )
        {
        if ( err == KErrAlreadyExists )
            {
            TInt errnum = mainFile.Open( tempServer, KMainLog, 
                EFileRead | EFileStreamText );
            if ( errnum != KErrNone )
                {
                return;
                }
            }
        }    
    CleanupClosePushL( mainFile );
    
    if ( err == KErrNone )
        {
        WriteToFileL( mainFile,  iBuf );
        }
    else if ( err == KErrAlreadyExists )
        {
        TTime modifiedTime;
        TTime homeTime;
        homeTime.HomeTime();
        err = mainFile.Modified( modifiedTime );
        if ( err == KErrNone )
            {
            TTimeIntervalDays days = homeTime.DaysFrom( modifiedTime );
            TInt interval = days.Int();
            if ( interval >= KTheMaxInterval || interval <= -KTheMaxInterval )
                {
                mainFile.Close();
                mainFile.Replace( tempServer, KMainLog,
                    EFileWrite | EFileStreamText );                
                WriteToFileL( mainFile,  iBuf );
                }
            }     
        }
    
    CleanupStack::PopAndDestroy( &mainFile );
    }
    
// ---------------------------------------------------------------------------
// CBCTestLogger::WriteLogL
// Write text to log file.
// ---------------------------------------------------------------------------
//
void CBCTestLogger::WriteLogL( const TDesC& aLogText )
    {    
    WriteToFileL( iAtLogFile, aLogText );
    }
    
// -----------------------------------------------------------------------------
// CBCTestLogger::CreateTimeStamp
// Creates time stamp.
// -----------------------------------------------------------------------------
//
void CBCTestLogger::CreateTimeStamp( TDes& aBuf )
    {    
    TTime homeTime;
    homeTime.HomeTime();
    
    aBuf.Append( KTimeLogStart );
    TBuf<KTempBufferLenth> tempBuf;  
    TRAPD( err, homeTime.FormatL( tempBuf, KTimeFormat ) );
    if ( err != KErrNone ) // FormatL failed
        {
        tempBuf.Zero();
        tempBuf.Append( KGetTimeFailed );
        }        
    aBuf.Append( tempBuf );
    aBuf.Append( KTimeLogEnd );
    }
    
// -----------------------------------------------------------------------------
// CBCTestLogger::Buffer
// Return reference to iBuf.
// -----------------------------------------------------------------------------
//
TDes& CBCTestLogger::Buffer()
    {
    return iBuf;
    }    

// -----------------------------------------------------------------------------
// CBCTestLogger::WriteMainLogL
// Appends given text to main log file (if exists).
// -----------------------------------------------------------------------------
//
void CBCTestLogger::WriteMainLogL(const TDesC& aLogText)
    {    
    TBuf<KLogNameLength> mainLogFileName; // main log file
    mainLogFileName = KMainLog;
    RFile mainLogFile;

    // Open log file for writing.
    TInt err = mainLogFile.Open( iEikEnv->FsSession(),
                                 mainLogFileName,
                                 EFileWrite | EFileStreamText | EFileShareAny);

    if (err != KErrNone)
        {
        return; // log file couldn't be opened, do nothing
        }
    CleanupClosePushL( mainLogFile );
    TInt Pos = 0;
    mainLogFile.Seek( ESeekEnd,Pos );

    WriteToFileL( mainLogFile, aLogText );

    mainLogFile.Flush();
    mainLogFile.Close();
    CleanupStack::PopAndDestroy( &mainLogFile );
    }
    
// -----------------------------------------------------------------------------
// Get the caption of application
// -----------------------------------------------------------------------------
//
const TDesC& CBCTestLogger::AppCaption()
    {
    return iEikEnv->EikAppUi()->Application()->AppCaption();;
    }
    
// -----------------------------------------------------------------------------
// Write unicode text to file
// -----------------------------------------------------------------------------
//
void CBCTestLogger::WriteToFileL( RFile& aFile, const TDesC& aText )
    {
    TPtrC8 buf( (TUint8*)aText.Ptr(), aText.Size() );
    aFile.Write( buf );    
    }
    
TBool CBCTestLogger::ReadLineL(RFile& aFile, TDes& aLine)
    {	
 	TBuf8<1> atom;
	TBuf8<1> enter;
	HBufC16* text = HBufC16::NewL( 1 );

 	for( TInt err = aFile.Read(atom); err == KErrNone 
 	    && atom.Length() > 0; err = aFile.Read( atom ) )
 	    {
 		if(atom[0] == 10 && enter[0] == 13)
 		    {
 			break;
 		    }
 		text->Des().Copy(atom);
		aLine.Append(*text);
		enter = atom;
 	    }

 	delete text;
	return atom.Length()>0;
    }    
