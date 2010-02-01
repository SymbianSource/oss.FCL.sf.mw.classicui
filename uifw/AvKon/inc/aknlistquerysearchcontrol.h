/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description: 
*   Implementation of CAknListQuerySearchControl
*
*/


#ifndef AKNLISTQUERYSEARCHCONTROL_H
#define AKNLISTQUERYSEARCHCONTROL_H

#include <aknsfld.h>

/**
* List query search control class
*   This class is needed to control find box in list queries
*/

class CAknListQuerySearchControl : public CCoeControl 
    {
public:
    CAknSearchField *iFind;
    ~CAknListQuerySearchControl() { delete iFind; }
    void Draw(const TRect &) const
    {
    // this removes flicker from CEikDialog's Draw().
    }
    void SizeChanged() { }

    /**
    * From CCoeControl
    *   Returns number of controls inside the query control
    * @return   Number of component controls
    */
    TInt CountComponentControls() const
    {
    return iFind ? 1 : 0;
    }

    /**
    * From CCoeControl
    *   Returns a control determined by control id
    * @param    anIndex     Index of a control to be returned
    * @return   CCoeControl Pointer to control
    */
    CCoeControl* ComponentControl(TInt anIndex) const
    {
    if (iFind && anIndex==0)
        return iFind;
    return 0;
    }
    };

#endif
