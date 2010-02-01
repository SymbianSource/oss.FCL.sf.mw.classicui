/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test aknindicator.h
*
*/



#ifndef C_TESTDOMINDICATORCONTAINER_H
#define C_TESTDOMINDICATORCONTAINER_H


#include <aknindicatorcontainer.h>

/**
 *  for indirectly testing APIs in aknindicator.h  
 */
class CTestDomIndicatorContainer : public CAknIndicatorContainer
    {

public:

    /**
     * NewL()
     */
    static CTestDomIndicatorContainer* NewL();

    /**
     * NewLC()
     */
    static CTestDomIndicatorContainer* NewLC();

    /**
     * Destructor.
     */
     virtual ~CTestDomIndicatorContainer();

    /**
     * from  CAknIndicatorContainer. 
     * Returns a control determined by control id.
     *
     * @since S60 v5.0 
     * @param anIndex Index of a control to be returned.
     * @return Pointer to control
     */
     virtual CCoeControl* ComponentControl(TInt aIndex) const;

private:

    /**
     * default constructor
     */
    CTestDomIndicatorContainer();

    /**
     * 2-nd constructor
     */
    void ConstructL();

    /**
     * Reserved_1
     *
     * @since S60 v5.0
     */
    virtual void Reserved_1();

    };


#endif // C_TESTDOMINDICATORCONTAINER_H
