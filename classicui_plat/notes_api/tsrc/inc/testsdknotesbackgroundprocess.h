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
* Description:  Test AknWaitNoteWrapper.h
*
*/

#ifndef C_TESTSDKNOTESBACKGROUNDPROCESS_H
#define C_TESTSDKNOTESBACKGROUNDPROCESS_H

//  INCLUDES
#include <aknwaitnotewrapper.h>

    /**
    *  CTestSDKNotesBackGroundProcess test class 
    */
class CTestSDKNotesBackGroundProcess : public CBase,
                                       public MAknBackgroundProcess
    {
public:// Constructors and destructor
    
    /**
    * C++ default constructor.
    */
    CTestSDKNotesBackGroundProcess();
    
    /**
    * Destructor.
    */
    ~CTestSDKNotesBackGroundProcess();
    
    // from class MAknBackgroundProcess
    void StepL();
    
    // from class MAknBackgroundProcess
    TBool IsProcessDone() const;
    };

#endif /*C_TESTSDKNOTESBACKGROUNDPROCESS_H*/
