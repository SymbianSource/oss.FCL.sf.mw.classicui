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
* Description:  Test navigation_pane_api
*
*/


#ifndef C_TESTSDKNAVIPANENAVILBL_H
#define C_TESTSDKNAVIPANENAVILBL_H

// INCLUDES
#include <aknnavilabel.h>


/**
 * the class derived from the CAknNaviLabel  class
 */
class CTestSDKNavipaneNaviLblExt: public CAknNaviLabel
{
public://from CCoeControl

    /**
    * From CCoeControl. Handle the size change events.
    */
    virtual void SizeChanged();

    /**
    * From CCoeControl.  Draw a control.  
    *
    * @param aRect The region of the control to be redrawn.   
    */
    void Draw(const TRect& aRect) const;
    
public:// Construtor

    /**
     * C++ default constructor.
     */ 
    CTestSDKNavipaneNaviLblExt();

    };

#endif // C_TESTSDKNAVIPANENAVILBL_H
