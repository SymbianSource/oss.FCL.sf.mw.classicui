/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
*
*/


#ifndef HGSCROLLBAROBSERVERIFACE_H_
#define HGSCROLLBAROBSERVERIFACE_H_

#include <e32base.h>

class MHgScrollbarObserver
    {
public:
    /**
     */
    virtual void ScrollBarPositionChanged( const TPoint& aNewPosition ) = 0;

    virtual void HandleNaviStripChar( const TChar& aChar ) = 0;
    };

#endif /* HGSCROLLBAROBSERVERIFACE_H_ */
