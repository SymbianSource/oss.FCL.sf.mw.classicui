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
* Description:  Test aknmessagequerycontrol.h
*
*/

#ifndef C_TESTSDKAKNMESSAGEQUERYCONTROLPROTECTED_H
#define C_TESTSDKAKNMESSAGEQUERYCONTROLPROTECTED_H

//INCLUDE 
#include <aknmessagequerycontrol.h>

/*
 * The API of CAknMessageQueryControl class's protected function
 */
class CTestCAknMessageQueryControl:public CAknMessageQueryControl
    {
    //friend class 
    friend class CTestSDKQueries;
    
    };

#endif /*C_TESTSDKAKNMESSAGEQUERYCONTROLPROTECTED_H*/

//End file


