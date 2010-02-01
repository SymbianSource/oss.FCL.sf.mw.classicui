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
* Description:         Implement MAknProgressDialogCallBack
*
*/









#ifndef C_CBCTESTSUBWAITNOTEWRAPPER_H
#define C_CBCTESTSUBWAITNOTEWRAPPER_H

#include <aknwaitnotewrapper.h>

/**
 * Invoke waitnotewrapper's protected APIs
 */
class CBCTestSubWaitNoteWrapper: public CBase, public MAknBackgroundProcess
    {
public: // constructor and destructor

    /**
     * Symbian 2nd static constructor
     */
    static CBCTestSubWaitNoteWrapper* NewL();

    /**
     * Destructor
     */
    virtual ~CBCTestSubWaitNoteWrapper ();
 
//From MProgressDialogCallBack

	/**
     * Completes one cycle of the process.
     */
    virtual void StepL();

    /**
     * Return true when the process is done.
     */
    virtual TBool IsProcessDone() const;

    /**
     * Callback when the process is finished.
     */
    virtual void ProcessFinished();

    /**
    * Callback when the dialog is dismissed
    */
    virtual void DialogDismissedL( TInt aButtonId );

private: // constructor

    /**
     * C++ default constructor
     */
    CBCTestSubWaitNoteWrapper();

    /**
     * Symbian 2nd constructor
     */
    void ConstructL();

private: // data

	TInt iCounter;
    };

#endif // C_CBCTESTSUBWAITNOTEWRAPPER_H
