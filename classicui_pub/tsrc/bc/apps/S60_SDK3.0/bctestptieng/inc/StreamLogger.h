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







//
// just for simple use,
// this file doesn't following any code convensions or symbian rules.
//

#ifndef __DLL_LOGGER_H__
#define __DLL_LOGGER_H__

#include <f32file.h>  // link against efsrv.lib
#include <eikenv.h>

#define CERR    StreamLogger::begin()

/**
* usage: StreamLogger::begin()<<"your string"<<yourNumber<<...<<end;
*/
class StreamLogger{

    //
    // internel class
    // use RAII instead of symbian 2 phases contruction.
    //
    class LogFile{
    public:
        LogFile()
        {
            _LIT( KLogFile, "C:\\debug.log" );
            RFs& fs = CEikonEnv::Static()->FsSession();
            if ( file.Open( fs, KLogFile, EFileWrite | EFileShareAny ) != KErrNone )
                file.Create( fs, KLogFile, EFileWrite | EFileShareAny );

            TInt pos=0;  // this must be 0
            file.Seek( ESeekEnd, pos );
        }

        ~LogFile(){
            file.Close();
        }

        RFile& operator()(){ return file; }
    private:
        RFile file;
    };

public:
    ~StreamLogger(){}

    static StreamLogger& begin(){
        StreamLogger* self = new (ELeave) StreamLogger;
        return *self;
    }

    void suicide(){ delete this; }

    StreamLogger& operator<<(const TDesC& aText){
        LogFile file;

        HBufC8* text = HBufC8::NewL( aText.Length() );
        TPtr8 textPtr = text->Des();
        textPtr.Copy( aText );
        file().Write( *text );
        delete text;

        return *this;
    }

    StreamLogger& operator<<(TInt n){
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

        return *this;
    }

    StreamLogger& cr(){
        LogFile file;
        TBuf8<2> enter;
        enter.Append( 13 );
        enter.Append( 10 );
        file().Write( enter );
        return *this;
    }

    typedef StreamLogger& (*_Manipulator)(StreamLogger&);
    StreamLogger& operator<<(_Manipulator op){ return op(*this); }

private:
    StreamLogger(){}    //disable ctor
};

inline StreamLogger& end(StreamLogger& self){ self.suicide(); return self; }

inline StreamLogger& endl(StreamLogger& self){ self.cr(); return self; }

#endif //__FILE_LOGGER_H__
