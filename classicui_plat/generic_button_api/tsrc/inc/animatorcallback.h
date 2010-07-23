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
* Description:  Test AknButton.h
*
*/


#ifndef C_AnimatorCallBack_H
#define C_AnimatorCallBack_H

/*
 * Include files
 */
#include <aknpictographdrawerinterface.h>
#include <aknbutton.h>

#include "testsdkgenericbutton.h"

/*
 * This class is wrote for construction a parameter
 */
class CPictographAnimatorCallBack:public CBase, public MAknPictographAnimatorCallBack
    {
public:
    /*
     * Constructor
     */
    CPictographAnimatorCallBack();
    /*
     *Destructor
     */
    ~CPictographAnimatorCallBack();
    /*
     * The pure vitual function's implement
     */
    virtual void DrawPictographArea(); 
    };

#endif

//End file


