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
* Description:         test case
*
*/









#ifndef BCTEST_FORICONSCASE_H
#define BCTEST_FORICONSCASE_H

#include <akniconobserver.h>
#include <AknIconUtils.h>

#include "bctestcase.h"

class CBCTestSliderAndIconsContainer;
class CCoeControl;
class CEikonEnv;

/**
* test case for various list classes
*/
class CBCTestForIcons: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestForIcons* NewL( CBCTestSliderAndIconsContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCTestForIcons();
    
public: // from CBCTestCase
    
    /**
    * Execute corresponding test functions for UI command
    * @param aCmd, UI command
    */
    void RunL( TInt aCmd );

protected: // new functions
    
    /**
    * Build autotest script
    */
    void BuildScriptL();
    
    /**
     * Test TestIconsL
     */
    void TestIconsL();
        
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestForIcons( CBCTestSliderAndIconsContainer* aContainer );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
     /**
     * TestAknIconUtilsL
     */
    void TestAknIconUtilsL();
    
    /**
     * TestCAknIconL
     */
    void TestCAknIconL();
    
private: // data
    
    /**
     * Pointer to container.
     * not own
     */
    CBCTestSliderAndIconsContainer* iContainer;
    
    };

/**
* test case for MAknIconObserver
*/    
class CBCTestIconObserver: public MAknIconObserver, public CBase
    {
    void BitmapChanged( CFbsBitmap *aBitmap );
    };


/**
* test case for MAknIconFileProvider
*/
class CBCTestFileProvider: public CBase, public MAknIconFileProvider
    {
public:

// constructor and destructor
    
    CBCTestFileProvider();
    
    ~CBCTestFileProvider();
    
// from MAknIconFileProvider
    
    void RetrieveIconFileHandleL( 
        RFile& aFile, const TIconFileType aType ); 
    
    void Finished();
    
private: // data

    /**
     * Not Own
     */
    CEikonEnv* iEnv;    
    
    };
    
#endif // BCTEST_FORICONS_H