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
* Description:  Test aknquerydialog.h
*
*/

#ifndef C_TESTSDKAKNQUERYDIALOGPROTECTED_H
#define C_TESTSDKAKNQUERYDIALOGPROTECTED_H

//INCLUDE
#include <aknquerydialog.h>

/*
 * The API of CAknQueryDialog class's protected function
 */
class CTestCAknQueryDialog:public CAknQueryDialog
    {
    //friend class
    friend class CTestSDKQueries;
    
    };

/*
 * The API of CAknNumberQueryDialog class's protected function
 */
class CTestCAknNumberQueryDialog:public CAknNumberQueryDialog
    {
    //friend class
    friend class CTestSDKQueries;
    
    };

/*
 * The API of CAknTextQueryDialog class's protected function
 */
class CTestCAknTextQueryDialog:public CAknTextQueryDialog
    {
    //friend class
    friend class CTestSDKQueries;
    
    };

/*
 * The API of CAknTimeQueryDialog class's protected function
 */
class CTestCAknTimeQueryDialog:public CAknTimeQueryDialog
    {
    //friend class
    friend class CTestSDKQueries;
    
    };

/*
 * The API of CAknDurationQueryDialog class's protected function
 */
class CTestCAknDurationQueryDialog:public CAknDurationQueryDialog
    {
    //friend class
    friend class CTestSDKQueries;
    
    };

/*
 * The API of CAknFloatingPointQueryDialog class's protected function
 */
class CTestCAknFloatingPointQueryDialog:public CAknFloatingPointQueryDialog
    {
    //friend class
    friend class CTestSDKQueries;
    
    };

/*
 * The API of CAknIpAddressQueryDialog class's protected function
 */
class CTestCAknIpAddressQueryDialog:public CAknIpAddressQueryDialog
    {
    //friend class
    friend class CTestSDKQueries;
    
    };

/*
 * The API of CAknFixedPointQueryDialog class's protected function
 */
class CTestCAknFixedPointQueryDialog:public CAknFixedPointQueryDialog
    {
    //friend class
    friend class CTestSDKQueries;
    
    };

/*
 * The API of CAknMultiLineDataQueryDialog class's protected function
 */
class CTestCAknMultiLineDataQueryDialog:public CAknMultiLineDataQueryDialog
    {
    //friend class
    friend class CTestSDKQueries;
    
public:
    /*
     * Constructor
     */
    CTestCAknMultiLineDataQueryDialog( const TTone& aTone );
    
    /*
     * Destructor
     */
    ~CTestCAknMultiLineDataQueryDialog();
    };

/*
 * The API of CAknMultiLineIpQueryDialog class's protected function
 */
class CTestCAknMultiLineIpQueryDialog:public CAknMultiLineIpQueryDialog
    {
    //friend class
    friend class CTestSDKQueries;
    
    };

#endif

//End file



