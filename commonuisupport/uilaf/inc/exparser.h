// Copyright (c) 1999-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// An example parser
// 
//

#ifndef __EXPARSER_H__
#define __EXPARSER_H__

#include <mparser.h>

class CRichText;
class TCharFormat;

class ExampleParser
	{
public:
	EXPORT_C static MParser* NewParserL();
	};

class CExampleParser : public CBase, public MParser
	{
public:
	inline CExampleParser();
public: // from MParser
	void Release();
	TBool ParseThisText(const CRichText& aTextObj,TBool aAllowBack,TInt aStartScan,
							TInt aScanLength,TInt& aStartTag, TInt& aTagLength);
	const TDesC& CreateDoItText(const CRichText& aTextObj,TInt aStartText,TInt aLength);
	void ActivateThisTextL(const CRichText& aTextObj,TInt aStartText,TInt aLength);
	TBool ReformatOnRecognise() const;
	TBool ReformatOnRollover() const;
	void GetRecogniseFormat(TCharFormat& aFormat);
	void GetRolloverFormat(TCharFormat& aFormat);
	};

inline CExampleParser::CExampleParser()
	{}

#endif
