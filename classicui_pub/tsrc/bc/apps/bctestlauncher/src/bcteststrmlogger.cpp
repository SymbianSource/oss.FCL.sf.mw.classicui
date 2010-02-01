/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Handles log writing.
*
*/









#include <f32file.h>
#include <eikenv.h>

#include "bcteststrmlogger.h"

//
// helper class
//
class CLogFile: public CBase
	{
public:
	static CLogFile& CreateLC( const TDesC& aFileName );
	virtual ~CLogFile();
	RFile& operator()();

private:
	RFile iFile;
	};

//=====================Helper class Member functions==========================

// ---------------------------------------------------------------------------
// CLogFile::CreateLC()
// ---------------------------------------------------------------------------
//
CLogFile& CLogFile::CreateLC( const TDesC& aFileName )
	{
	CLogFile* self = new( ELeave ) CLogFile;
	CleanupStack::PushL( self );

	RFs& fs = CEikonEnv::Static()->FsSession();
	if ( self->iFile.Open( fs, aFileName, EFileWrite | EFileShareAny ) 
	    != KErrNone )
		{
		self->iFile.Create( fs, aFileName, EFileWrite | EFileShareAny );
		}
		
	TInt pos=0;  // this must be 0
	self->iFile.Seek( ESeekEnd, pos );
	return *self;
	}

// ---------------------------------------------------------------------------
// CLogFile::~CLogFile()
// ---------------------------------------------------------------------------
//
CLogFile::~CLogFile()
	{
	iFile.Close();
	}

// ---------------------------------------------------------------------------
// CLogFile::operator()
// ---------------------------------------------------------------------------
//
RFile& CLogFile::operator()()
	{ 
	return iFile; 
	}

//=====================Member functions=======================================

// ---------------------------------------------------------------------------
// CBCTestStreamLogger::BeginLC()
// ---------------------------------------------------------------------------
//
CBCTestStreamLogger& CBCTestStreamLogger::BeginLC( const TDesC& aFileName )
    {
    CBCTestStreamLogger* self = new( ELeave ) CBCTestStreamLogger();
    CleanupStack::PushL( self );
	self->ConstructL( aFileName );
    return *self;
    }

// ---------------------------------------------------------------------------
// CBCTestStreamLogger::CBCTestStreamLogger()
// ---------------------------------------------------------------------------
//
CBCTestStreamLogger::CBCTestStreamLogger()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestStreamLogger::ConstructL()
// ---------------------------------------------------------------------------
//
void CBCTestStreamLogger::ConstructL( const TDesC& aFileName )
    {
	iFileName = aFileName;
    }

// ---------------------------------------------------------------------------
// CBCTestStreamLogger::~CBCTestStreamLogger()
// ---------------------------------------------------------------------------
//
CBCTestStreamLogger::~CBCTestStreamLogger()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestStreamLogger::Suicide()
// ---------------------------------------------------------------------------
//
void CBCTestStreamLogger::Suicide()
	{ 
	CleanupStack::PopAndDestroy();	//self
	}

// ---------------------------------------------------------------------------
// CBCTestStreamLogger::operator<<(const TDesC& aText)
// ---------------------------------------------------------------------------
//
CBCTestStreamLogger& CBCTestStreamLogger::operator<<( const TDesC& aText )
	{
	CLogFile& file = CLogFile::CreateLC( iFileName );
	HBufC8* text = NULL;
	TRAPD( result, text = HBufC8::NewL( aText.Length() ) );
	if ( result != KErrNone )
	    {
	    User::Leave( result );
	    }
	TPtr8 textPtr = text->Des();
	textPtr.Copy( aText );
	file().Write( *text );
	delete text;
	CleanupStack::PopAndDestroy();	//file
	
	return *this;
	}

// ---------------------------------------------------------------------------
// CBCTestStreamLogger::operator<<(TInt aNum)
// ---------------------------------------------------------------------------
//
CBCTestStreamLogger& CBCTestStreamLogger::operator<<( TInt aNum )
	{
	CLogFile& file = CLogFile::CreateLC( iFileName );
	
	TInt i = 1;
	for( TInt v = aNum; v != 0; ++i, v /= 10 )
		{
		}
	HBufC* text = NULL;
	TRAPD( result, text = HBufC::NewL( i ) );
	TPtr textPtr = text->Des();
	
	_LIT(KFmt, "%d");
	textPtr.Format( KFmt, aNum );
	HBufC8* text8 = NULL;
	TRAP( result, text8 = HBufC8::NewL( textPtr.Length() ) );
	if ( result != KErrNone )
	    {
	    User::Leave( result );
	    }	
	TPtr8 textPtr8 = text8->Des();
	textPtr8.Copy(*text);
	
	file().Write( *text8 );
	delete text;
	delete text8;
	CleanupStack::PopAndDestroy();	//file

	return *this;
    }

// ---------------------------------------------------------------------------
// CBCTestStreamLogger::CRL()
// ---------------------------------------------------------------------------
//
CBCTestStreamLogger& CBCTestStreamLogger::CRL()
	{
	CLogFile& file = CLogFile::CreateLC( iFileName );
	TBuf8<2> enter;
	enter.Append( 13 );
	enter.Append( 10 );
	file().Write( enter );
	CleanupStack::PopAndDestroy();	//file
	return *this;
	}

// ---------------------------------------------------------------------------
// CBCTestStreamLogger::operator<<( CBCTestStreamLogger::Manipulator aOp )
// ---------------------------------------------------------------------------
//
CBCTestStreamLogger& CBCTestStreamLogger::operator<<(
		CBCTestStreamLogger::Manipulator aOp )
	{
	return aOp( *this );
	}

namespace BCTest
	{
	CBCTestStreamLogger& End( CBCTestStreamLogger& self )
		{ 
		self.Suicide(); 
		return self; 
		}

	CBCTestStreamLogger& EndLine( CBCTestStreamLogger& self )
		{ 
		self.CRL(); 
		return self; 
		}
	}
