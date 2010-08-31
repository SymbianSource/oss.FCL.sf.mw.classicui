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
* Description:         Write log
*
*/









#ifndef C_CBCTESTLOGGER_H
#define C_CBCTESTLOGGER_H

#include <e32std.h>
#include <e32base.h>
#include <f32file.h>
#include <apadef.h>

class CEikonEnv;

const TInt KLogNameLength = 64;
const TInt KLogBufferLength = 512;

_LIT( KLogRow80,"--------------------\r\n" );
_LIT( KLogLine, "\r\n" );
_LIT( KLogTwoLine, "\r\n\r\n" );

/**
 * Log class. The class will use CEikonEnv::Static, so we have to have the 
 * App to use the class.
 */
class CBCTestLogger: public CBase
    {
public: 

// constructor and destructor
    
    /**
     * Symbian second phase constructor
     */
    static CBCTestLogger* NewL( CEikonEnv* aEikonEnv );
    
    /**
     * Destructor
     */
    virtual ~CBCTestLogger();
    
// new functions

    /**
     * Write custom text to log file.
     * @param aLogText, custom text.
     */        
    void WriteLogL(const TDesC& aLogText);
    
    /**
     * Write custom text to main log file.
     * @param aLogText, custom text
     */
    void WriteMainLogL( const TDesC& aLogText );
    
    /**
     * Get the buffer for formated text.    
     */
    TDes& Buffer();
    
    /**
     * Creates time stamp for log file
     * @param aBuf, the time stamp will be appended to aBuf.
     */
    void CreateTimeStamp( TDes& aBuf );
    
    /**
     * Get the caption of application
     */
    const TDesC& AppCaption();   
            
protected: 

// constructor
    
    /**
     * C++ default constructor
     */
    CBCTestLogger( CEikonEnv* aEikonEnv );
    
    /**
     * Symbian 2nd phase constructor. 
     */
    void ConstructL();
    
// new functions
    
    /**
     * Write text to file.
     * @param aFile a reference of RFile to an opened file
     * @param aText the text to be written
     */
    void WriteToFileL( RFile& aFile, const TDesC& aText ); 
    
private:

    /**
     * Create main log file. If the file is existed and has been modifed
     * recently, new log will be appended to the end of the file. If the 
     * file is existed and has not been modified in recent two days, the
     * file will be replaced.
     */
    void CreateMainLogL();
    
	/**
	* @return EFalse for EOF, otherwise it returns ETrue
	*/
	TBool ReadLineL( RFile& aFile, TDes& aLine );    
        
private: // data
    
    /**
     * log file for autotest results
     */
    TBuf<KLogNameLength> iAtLogFileName;
    
    /**
     * temp storage for log writing
     */
    TBuf<KLogBufferLength> iBuf;
    
    /**
     * log file
     */
    RFile iAtLogFile;
    
    /**
     * not own
     */
    CEikonEnv* iEikEnv;
    
    /**
     * The caption of application
     */
    TApaAppCaption iCaption;
    
    };

#endif // C_CBCTESTLOGGER_H