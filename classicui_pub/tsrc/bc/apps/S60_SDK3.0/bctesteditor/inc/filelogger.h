/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:       
*
*/







#ifndef __FILE_LOGGER_H__
#define __FILE_LOGGER_H__

#include <f32file.h>
#include <eikenv.h>

class FileLogger{
    class LogFile{
    public:
        LogFile(){
            _LIT( KLogFile, "C:\\atbtn.log" );
            RFs& fs = CEikonEnv::Static()->FsSession();
            if ( iFile.Open( fs, KLogFile, EFileWrite | EFileShareAny ) != KErrNone )
            {
                iFile.Create( fs, KLogFile, EFileWrite | EFileShareAny );
            }
            
            TInt pos=0;  // this must be 0
            iFile.Seek( ESeekEnd, pos );
        }

        ~LogFile(){ iFile.Close(); }

        RFile& operator()(){ return iFile; }
    private:
        RFile iFile;
    };

public:
    // dll can not hold static vars, so...
    static FileLogger& GetInstance(){
        static FileLogger logger;
        return logger;
    }

    const FileLogger& operator<<(const TDesC& aText)
    {
        LogFile file;
        
        HBufC8* text = HBufC8::NewL( aText.Length() );
        TPtr8 textPtr = text->Des();
        textPtr.Copy( aText );
        file().Write( *text );
        delete text;

        TBuf8<2> enter;
        enter.Append( 13 );
        enter.Append( 10 );
        file().Write( enter );

        return *this;
    }

    const FileLogger& operator<<(TInt n){
        LogFile file;
        
        TInt i=1;
        for(TInt v=n; v!=0; ++i, v/=10){}
        HBufC* text = HBufC::NewL( i );
        TPtr textPtr = text->Des();

        _LIT(KFmt, "%d");
        textPtr.Format( KFmt, n );
        HBufC8*  text8 = HBufC8::NewL( textPtr.Length() );
        TPtr8 textPtr8 = text8->Des();
        textPtr8.Copy(*text);

        file().Write( *text8 );
        delete text;
        delete text8;

        TBuf8<2> enter;
        enter.Append( 13 );
        enter.Append( 10 );
        file().Write( enter );

        return *this;
    }

private:
    FileLogger(){}
};

#endif //__FILE_LOGGER_H__