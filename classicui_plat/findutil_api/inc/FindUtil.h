/*
* Copyright (c) 2002-2004 Nokia Corporation and/or its subsidiary(-ies). 
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of the License "Eclipse Public License v1.0"
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



#ifndef __FINDUTIL_H__
#define __FINDUTIL_H__

#include <e32base.h>

/**
* Identify the match policy for FindUtil API
*/
enum TMatchPolicy
{
    EDefault,
    ECustomConverter
};

/**
* Interface for the conversion of find string
*/
class MFindStringConverter
    {
public:
    virtual void Converter(const TDesC& aSourStr, TDes& aDestStr) = 0;
    };
    
/**
* FindUtil API
*/
class MFindUtil
	{
public:
	virtual TBool Match(const TDesC& aContactsField, const TDesC& aWord) = 0;
	virtual TBool MatchRefineL( const TDesC& aItemString, const TDesC &aSearchText) = 0;
	virtual TBool IsWordValidForMatching(const TDesC& aWord) = 0;
	virtual TBool MatchAdaptiveRefineL( const TDesC& aItemString, const TDesC &aSearchText, HBufC*& aNextChars ) = 0;	
	virtual TBool MatchRefineL( const TDesC& aItemString, const TDesC& aSearchText, 
                                TMatchPolicy aPolicy, MFindStringConverter* aConverter) = 0;
	};

/**
* CFindUtil instance gives access to MFindUtil interface.
*/
NONSHARABLE_CLASS(CFindUtil) : public CBase
    {
    public: // Constructors and destructor

        /**
        * Creates a new CFindUtil instance.
        * In those language variants, where FindUtil is not used,
        * this method returns NULL.
        */
        IMPORT_C static CFindUtil* NewL();
        IMPORT_C ~CFindUtil();

    public: // New functions
        MFindUtil* Interface() {return iInterface;}

    private: // Private constructors
        CFindUtil();
        void ConstructL();

    private: // Data
        MFindUtil* iInterface;
        RLibrary iLib;
    };

#endif
