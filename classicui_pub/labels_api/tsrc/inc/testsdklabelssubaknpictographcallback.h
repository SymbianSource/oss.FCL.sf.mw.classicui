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
* Description:  Test EIKLABEL.H, eikfnlab.h
*
*/


#ifndef C_TESTSDKLABELSSUBAKNPICTOGRAPHCALLBACK_H
#define C_TESTSDKLABELSSUBAKNPICTOGRAPHCALLBACK_H

#include <aknpictographdrawerinterface.h> 
#include <aknpictographinterface.h> 
#include <coecntrl.h>

class CTestSDKLabelsSubAknPictographCallBack : public CCoeControl, 
                                               public MAknPictographAnimatorCallBack 
    {
public:
    /**
    * Two-phased constructor.
    */
    static CTestSDKLabelsSubAknPictographCallBack* NewLC();
    
    /**
    * destructor
    */
    ~CTestSDKLabelsSubAknPictographCallBack();
    
    /**
    *  DrawPictographArea test function for testing the 
    * Test DrawPictographArea function
    */
    void DrawPictographArea();
    
    /**
    *  Interface test function for testing the 
    * Test Interface function
    */
    CAknPictographInterface* Interface();
    
private:
    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();
    
    /**
    * Constructors
    */
    CTestSDKLabelsSubAknPictographCallBack();
    
private://Data
    
    CAknPictographInterface* iInterface;
    };

#endif /*C_TESTSDKLABELSSUBAKNPICTOGRAPHCALLBACK_H*/
