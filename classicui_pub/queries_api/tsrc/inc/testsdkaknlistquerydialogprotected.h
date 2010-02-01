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
* Description:  Test aknlistquerydialog.h
*
*/

#ifndef C_CTESTCAKNLISTQUERYDIALOG_H
#define C_CTESTCAKNLISTQUERYDIALOG_H

//INCLUDE
#include <aknlistquerydialog.h>

// CLASS DECLARATION

/**
 * Test protected API of CAknListQueryDialog
 */
class CTestCAknListQueryDialog:public CAknListQueryDialog
{
//friend class
friend class CTestSDKQueries;

public:
    /*
     * Constructor
     */
    CTestCAknListQueryDialog( TInt* aIndex );
    
    /*
     * Constructor
     */
    CTestCAknListQueryDialog( CListBoxView::CSelectionIndexArray* aSelectionIndexArray );
        
    
    /*
     * Destructor
     */
    virtual ~CTestCAknListQueryDialog();
};

#endif /*C_CTESTCAKNLISTQUERYDIALOG_H*/

//End file


