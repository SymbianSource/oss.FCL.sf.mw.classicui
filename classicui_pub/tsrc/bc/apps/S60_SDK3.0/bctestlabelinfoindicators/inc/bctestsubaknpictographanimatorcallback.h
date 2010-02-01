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
* Description:         MAknPictographAnimatorCallBack's sub class
*
*/









#ifndef T_TBCTESTSUBAKNPICTOGRAPHANIMATORCALLBACK_H
#define T_TBCTESTSUBAKNPICTOGRAPHANIMATORCALLBACK_H

#include <aknpictographdrawerinterface.h> 

/**
 * MAknPictographAnimatorCallBack's sub class
 */
class TBCTestSubAknPictographAnimatorCallBack
    : public MAknPictographAnimatorCallBack
    {    
public: 

// from MAknPictographAnimatorCallBack

    /**
    * This function is called when a redraw is needed for drawing
    * new frames of animated pictographs. It should
    *
    * 1) Draw or clear the background of pictographs
    * 2) If the pictographs are amongst text, draw the text
    * 3) Draw the pictographs using MAknPictographDrawer interface
    *
    * In many cases, it is sufficient to implement this simply by
    * calling CCoeControl::DrawNow for the appropriate control.
    */
    void DrawPictographArea(){}

    };

#endif // T_TBCTESTSUBAKNPICTOGRAPHANIMATORCALLBACK_H
