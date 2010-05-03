/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test transition_effect_utilities_api
*
*/


#ifndef C_TESTDOMUTILITIESOBSERVER_H
#define C_TESTDOMUTILITIESOBSERVER_H

#include <akntransitionutils.h>
#include <akntransparentcamerasettingpage.h>

/**
 *  CTestDomUtilitiesObserver class create just for test CAknTransitionUtils
 */
class CTestDomUtilitiesObserver : public CBase,public MAknTransitionUtilsObserver
    { 
    
public:

    /**
     * C++ default constructor
     */ 
    CTestDomUtilitiesObserver();
    
    /**
     * C++ default destructor
     */ 
    virtual ~CTestDomUtilitiesObserver();
    
    /**
     * Callback function
     */ 
    TInt AknTransitionCallback( TInt, TInt,const TDesC8* );
    };

#endif //C_TESTDOMUTILITIESOBSERVER_H

// End of file
