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
* Description:         Test case class, user will create own test case class by 
*                deriving from the class.
*
*/









#ifndef C_CBCTESTCONFIG_H
#define C_CBCTESTCONFIG_H

#include <e32std.h>
#include <e32base.h>
#include <f32file.h>

#include "bctestlauncherdefs.h"

/**
 *  BC test configurator, read all BC applications from an XML file.
 */
class CBCTestConf : public CBase
    {
public: // constructor
    static CBCTestConf* NewLC();

    /**
    * C++ default constructor
    */ 
    CBCTestConf();

	void ConstructL();
    
    /**
    * Destructor
    */
    virtual ~CBCTestConf();
    
// new funcs

    TBool NextL();

	const TDesC& Name();
	TInt  AppUID();
	TInt  ViewUID();
	TInt  Timeout();
	TInt  Version();
    
private:
	void  OpenConfigL();
	void  CloseConfig();
	TBool ReadBlockDataL();

	/**
	* @return EFalse for EOF, otherwise it returns ETrue
	*/
	TBool ReadLineL( TDes& aLine );

// data
    RFile iFile;

	TBuf<KNameLength> iName;
	TInt iAppUID;
    TInt iViewUID;
    TInt iTimeout;  // [min]
	TInt iVersion;	// S60 30, 31, 32
    };

#endif // C_CBCTESTCONFIG_H
