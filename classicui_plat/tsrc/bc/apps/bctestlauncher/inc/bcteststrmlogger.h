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









#ifndef C_CBCTESTSTREMLOGGER_H
#define C_CBCTESTSTREMLOGGER_H

#include <eikenv.h>
#include <e32const.h>

#define LOG		CBCTestStreamLogger::BeginLC()

_LIT(KLogFileName, "c:\\bctestLog\\summary.log");  // main log file

/**
 * CBCTestLauncherApp application class.
 * Provides factory to create concrete document object.
 */
class CBCTestStreamLogger : public CBase
    {
public:  
// Constructors and destructor        

	/**
    * Two-phased constructor.
    */
    static CBCTestStreamLogger& BeginLC( 
        const TDesC& aFileName = KLogFileName );

	/**
    * Destructor.
    */
    virtual ~CBCTestStreamLogger();

// New methods

	/**
	* Suicide self
	*/
	void Suicide();

	/**
	* stream a string out
	* @param aText, the text u want to stream out
	*/
    CBCTestStreamLogger& operator<<(const TDesC& aText);

	/**
	* stream a number out
	* @param aNum, the number u wnat to stream out
	*/
	CBCTestStreamLogger& operator<<(TInt aNum);

	/**
	* stream out a new line
	*/
	CBCTestStreamLogger& CRL();

	/**
	* stream manipulator dispatcher
	* @param aOp, the manipulator function pointer
	*/
	typedef CBCTestStreamLogger& (*Manipulator)( CBCTestStreamLogger& );
	CBCTestStreamLogger& operator<<(Manipulator aOp);

private:

    /**
    * C++ default constructor. disable it!
    */
    CBCTestStreamLogger();

	/**
	* Symbian 2nd phase ctor
	*/
	void ConstructL(const TDesC& aFileName);

// data
	TBuf<KMaxPath> iFileName;
    };

namespace BCTest
    {
	CBCTestStreamLogger& End(CBCTestStreamLogger& self);
	CBCTestStreamLogger& EndLine(CBCTestStreamLogger& self);
    }

#endif //C_CBCTESTSTREMLOGGER_H

