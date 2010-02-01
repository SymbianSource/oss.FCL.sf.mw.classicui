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
* Description:  Test AknInputBlock.h
*
*/


/**
 *INCLUDES
 */
#ifndef C_CACTIVEEXAMPLE_H
#define C_CACTIVEEXAMPLE_H

#include <e32base.h>
#include <e32def.h>

/**
 * Class CActiveExample is a active object
 */
class CActiveExample : public CActive
{
public:
    /**
     * consturction
     */
    CActiveExample();
    /*
     * Desturction
     */
    virtual ~CActiveExample();
    /*
     * Tne DoCancel function is be transfered by Cancel();
     */ 
    virtual void DoCancel();
    /*
     *  Second-phase constructor
     */
    void ConstructL();
    /*
     * The NewL function
     */
    static CActiveExample* NewL();
    /*
     * The NewLC function;
     */
    static CActiveExample* NewLC();
    /*
     * The active object's start function
     */
    void Start(TTimeIntervalMicroSeconds32 aDelay);
    /*
     * This function is return the value of flag
     */
    TBool Getflag();
    /*
     * This function is used to set the value of flag
     */
    void Setfalg( TBool aFlag );

private:
    /*
     * This is a flag be use justice some funtions that be tested if correct
     */
    TBool iFlag;
    /*
     * RnuL function
     */
    virtual void RunL();
    
private:
    enum TActiveExampleState
    {
        EUninitialized,
        EInitialized,
        EError
    };

private:
    TInt    iState;
    RTimer  iTimer;
};

#endif /*CACTIVEEXAMPLE_H_*/

// End of File
