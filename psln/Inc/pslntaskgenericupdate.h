/*
* Copyright (c) 2003-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Background task for generic tasks.
*
*/


#ifndef C_PSLNTASKGENERICUPDATE_H
#define C_PSLNTASKGENERICUPDATE_H

#include <e32base.h>
#include <e32std.h>
#include <AknWaitNoteWrapper.h>

class CPslnUi;
class CPslnModel;

/**  Model funtion pointer. */
typedef void ( CPslnModel::* TPslnModelFunctionPtr )();

/**
 *  Background task for generic tasks.
 *
 *
 *  @since S60 v2.0
 */
class CPslnTaskGenericUpdate : public CBase, public MAknBackgroundProcess
    {
public:
    /**
    * C++ constructor.
    * @param aUi reference to UI-class.
    * @param aModelFunc model function pointer.
    * @param aUpdateList ETrue is skin list is needed to update.
    */
    CPslnTaskGenericUpdate( 
        CPslnUi& aUi,
        TPslnModelFunctionPtr aModelFunc, 
        TBool aUpdateList = ETrue );

    /**
    * From MAknBackgroundProcess.
    * Return ETrue when the process is done.
    * @return ETrue if process is ready.
    */
    TBool IsProcessDone() const;

    /**
    * From MAknBackgroundProcess. 
    * Completes one cycle of the process.
    */
    void StepL();

private: // data


    /**
    * Reference to Psln UI-class.
    */
    CPslnUi& iUi;

    /**
    * Psln model function to call.
    */
    TPslnModelFunctionPtr iModelFunc;

    /**
    * Should the skin list be updated.
    */
    TBool iUpdateList;

    /**
    * Has the task been done.
    */
    TBool iDone;

public: // Public data

    /**
    * Error code for the task, if any.
    */
    TInt iCallErr;

    };

#endif // C_PSLNTASKGENERICUPDATE_H
