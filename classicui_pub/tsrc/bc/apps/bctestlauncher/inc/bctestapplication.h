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









#ifndef C_CBCTESTAPPLICATION_H
#define C_CBCTESTAPPLICATION_H

#include <e32std.h>
#include <e32base.h>

#include "bctestlauncherdefs.h"

class CEikonEnv;

/**
 *  Test Application, represent all bc test applications.
 */
class CBCTestApplication : public CBase
    {
public: // constructor
    static CBCTestApplication* NewL( const TDesC& aName, 
            TInt aAppUID, TInt aViewUID, 
			TInt aTimeout = 1, TInt aVersion = 30 );

    /**
    * C++ default constructor
	* @param aTimeout, in min
    */ 
    CBCTestApplication( const TDesC& aName, TInt aAppUID, TInt aViewUID = 1, 
		TInt aTimeout = 1, TInt aVersion = 30 );
    
    /**
    * Destructor
    */
    virtual ~CBCTestApplication();
    
// new funcs

    void RunL( TInt aCommand );
    const TDesC& Name(){ return iName; }

	/**
	* select the application to run
	*/
	void Select(TBool aSelected = ETrue){ iSelected = aSelected; }
    
private:
    void StartAutoTest();
    void SetupL();
    void TearDown();
    void WatchDogL();
    void KeyPress( TInt aCode, TInt aScanCode );
    TInt GetFreeMem();

// data    

    TBuf<KNameLength> iName;
    TInt  iAppUID;
    TInt  iViewUID;
    TInt  iTimeout;  // [min]
	TInt  iVersion;	 // 30, 31, 32
	TBool iSelected;
	
    /**
     * point to CEikonEnv,
     * not own.
     */
    CEikonEnv* iEikEnv;	
    };

#endif // C_CBCTESTAPPLICATION_H
