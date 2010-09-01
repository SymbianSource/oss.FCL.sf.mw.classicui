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


#ifndef HGPOPUPDRAWER_H
#define HGPOPUPDRAWER_H

#include <e32std.h>

// Forward declarations
class CFont;
class CWindowGc;

NONSHARABLE_CLASS( THgPopupDrawer )
    {
public:
    
    THgPopupDrawer();

    void Init( TRect aRect, const CFont* aFont );
    void Draw( CWindowGc& aGc, const TDesC& aDesc );
    void DrawNaviChar( CWindowGc& aGc, const TDesC& aDesc );
    void Draw( CWindowGc& aGc, 
            const TDesC& aDesc1, 
            const TDesC& aDesc2
            );
private:

    void DrawBackground(CWindowGc& aGc, const TRect& aRect);
    void InitFont(CWindowGc& aGc);
    void InitLongestMonth();
    
private:
    
    TRect iRect; // client rect
    const CFont* iFont; // Not own
    TInt iLongestMonth;
    
    };

#endif //HGPOPUPDRAWER_H
