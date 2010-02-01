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
* Description:         Test case.
*
*/









#include <e32cmn.h>
#include "bctestconf.h"
#include "bcteststrmlogger.h"

const int KMaxLength = 255;

_LIT( KConfFile, "c:\\bctestlog\\config.xml" );
_LIT( KTag, "ITEM");
_LIT( KName, "NAME");
_LIT( KAppUID, "APPUID");
_LIT( KViewUID, "VIEWUID");
_LIT( KTimeout, "TIMEOUT");
_LIT( KVersion, "VER");

_LIT( KLess, "<");
_LIT( KLessSlash, "</");
_LIT( KGreater, ">");

_LIT( KCDataBegin, "<![CDATA[" );
_LIT( KCDataEnd, "]]>" );

//
// helper class
//
struct XMLUtil
    {
	static TPtrC ExtractField( const TDesC& aLine, const TDesC& aName );
	static TPtrC ExtractCData( const TDesC& aLine );

	static TPtrC StartField( const TDesC& aName );
	static TPtrC EndField( const TDesC& aName );

	static TInt  StringToHex( const TDesC& aStr );
	static TInt  StringToDec( const TDesC& aStr );
    };

// ======== MEMBER FUNCTIONS ========

TInt XMLUtil::StringToHex( const TDesC& aStr )
    {
	//ex. 0x101F84E0
	_LIT( KHexPrefix, "0X" );
	TBuf < KMaxLength > str( aStr );
	str.UpperCase();
	TInt res = 0;
	
	if( str.Find( KHexPrefix ) == KErrNotFound )
		return 0;

	for( TInt i = 2; i < str.Length(); ++i )
	    {
		if( TChar( str[i] ).IsDigit() )
		    {
			res = ( res << 4 ) + str[i] - '0';
		    }
		else
		    {
			res = ( res << 4 ) + str[i] - 'A' + 10;
		    }
	    }
	return res;
    }

TInt XMLUtil::StringToDec( const TDesC& aStr )
    {
	//ex. 127
	TLex lex(aStr);
	TInt res=0;
	return lex.Val( res )==KErrNone ? res : 0;
    }

TPtrC XMLUtil::ExtractField( const TDesC& aLine, const TDesC& aName )
    {
	TBuf<KMaxLength> endTag( KLessSlash );	// endTag := </aName>
	endTag += aName;
	endTag += KGreater;

	TInt posBegin = aName.Length()+2;			//"<aName>" length
	TInt posEnd   = aLine.Find( endTag );
	return ExtractCData( aLine.Mid( posBegin, ( posEnd-posBegin ) ) );
    }

TPtrC XMLUtil::ExtractCData( const TDesC& aLine )
    {
	TInt posBegin = KCDataBegin().Length();
	TInt posEnd   = aLine.Find( KCDataEnd );
	return aLine.Mid( posBegin, ( posEnd - posBegin ) );
    }

TPtrC XMLUtil::StartField( const TDesC& aName ) 
    {
	TBuf<KMaxLength> res( KLess );
	res += aName;
	res += KGreater;
	return res;		//res := <aName>
    }

TPtrC XMLUtil::EndField( const TDesC& aName )
    {
	TBuf<KMaxLength> res( KLessSlash );
	res += aName;
	res += KGreater;
	return res;		//res := </aName>
    }

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
CBCTestConf::CBCTestConf()
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestConf::~CBCTestConf()
    {
	CloseConfig();
    }

//static 
CBCTestConf* CBCTestConf::NewLC()
{
    CBCTestConf* self= new ( ELeave) CBCTestConf();
	CleanupStack::PushL(self);
	self->ConstructL();
    return self;
}

// ---------------------------------------------------------------------------
// CBCTestConf::ConstructL. 
// ---------------------------------------------------------------------------
//
void CBCTestConf::ConstructL()
    {
    OpenConfigL();
    }

void CBCTestConf::OpenConfigL()
    {
    RFs& fs = CEikonEnv::Static()->FsSession();
	User::LeaveIfError( 
	    iFile.Open( fs, KConfFile, EFileRead | EFileShareAny ) != KErrNone );
    }

void CBCTestConf::CloseConfig()
	{
	iFile.Close();
	}

TBool CBCTestConf::ReadLineL(TDes& aLine)
    {	
 	TBuf8<1> atom;
	TBuf8<1> enter;
	HBufC16* text = HBufC16::NewL( 1 );

 	for( TInt err = iFile.Read(atom); err == KErrNone 
 	    && atom.Length() > 0; err = iFile.Read( atom ) )
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

TBool CBCTestConf::ReadBlockDataL()
    {
    while( ETrue )
        {
		TBuf<KMaxLength> line;
		if(!ReadLineL(line))
		    {
			break;
		    }

		if( line.Find( XMLUtil::StartField( KTag ) ) != KErrNotFound )
		    {
			iName = _L("");
			iAppUID = iViewUID = iTimeout =0;
		    }
		else if( line.Find( XMLUtil::EndField( KTag ) ) != KErrNotFound )
		    {
			return ETrue;
		    }
		else if( line.Find( XMLUtil::StartField( KName ) ) != KErrNotFound )
		    {
			iName = XMLUtil::ExtractField( line, KName );
	    	}
		else if( line.Find( XMLUtil::StartField( KAppUID ) ) != KErrNotFound )
		    {
			iAppUID = XMLUtil::StringToHex( 
			    XMLUtil::ExtractField( line, KAppUID ) );
		    }
		else if( line.Find( XMLUtil::StartField( KViewUID ) ) != KErrNotFound )
		    {
			iViewUID = XMLUtil::StringToDec( 
			    XMLUtil::ExtractField( line, KViewUID ) );
		    }
		else if( line.Find( XMLUtil::StartField( KTimeout ) ) != KErrNotFound )
		    {
			iTimeout = XMLUtil::StringToDec( 
			    XMLUtil::ExtractField( line, KTimeout ) );
		    }
		else if( line.Find( XMLUtil::StartField( KVersion ) ) != KErrNotFound )
		    {
			iVersion = XMLUtil::StringToDec( 
			    XMLUtil::ExtractField( line, KVersion ) );
		    }
	    }
	return EFalse;
    }

TBool CBCTestConf::NextL()
	{
	return ReadBlockDataL();
	}

const TDesC& CBCTestConf::Name()
	{
    return iName;
	}

TInt CBCTestConf::AppUID()
    {
    return iAppUID;
    }

TInt CBCTestConf::ViewUID()
	{
	return iViewUID;
	}

TInt CBCTestConf::Timeout()
	{
	return iTimeout;
	}

TInt CBCTestConf::Version()
	{
	return iVersion;
	}
