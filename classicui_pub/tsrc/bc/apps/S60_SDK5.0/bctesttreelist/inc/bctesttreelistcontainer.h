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
* Description:         container
*
*/








#ifndef BCTEST_TREELISTCONTAINER_H
#define BCTEST_TREELISTCONTAINER_H

#include <coecntrl.h>

/**
* container class
*/
class CBCTestTreeListContainer: public CCoeControl
    {
public: // constructor and destructor
    
    /**
     * C++ default constructor
     */
    CBCTestTreeListContainer();
    
    /**
     * Destructor
     */
    virtual ~CBCTestTreeListContainer();
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL( const TRect& aRect );

private: // from CCoeControl    
    
    /**
    * From CCoeControl, Draw.
    * Fills the window's rectangle.
    * @param aRect Region of the control to be (re)drawn.
    */
    void Draw( const TRect& aRect ) const;  
    
    };    

#endif // BCTEST_TEMPLATECONTAINER_H