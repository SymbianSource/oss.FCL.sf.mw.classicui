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


#ifndef HGDRAWUTILS_H_
#define HGDRAWUTILS_H_

#include <e32base.h>

class CWindowGc;
class CCoeControl;
class TRgb;
class CHgMarquee;
class TAknWindowComponentLayout;
class TAknTextComponentLayout;
class CGulIcon;
class CGraphicsContext;

void DrawEmptyListImpl_real( const TRect &aClientRect,
                             CGraphicsContext &aGc,
                             TPtrC aText,
                             const TRgb& aColor  );

NONSHARABLE_CLASS( CHgDrawUtils ) : public CBase
    {
public:
    static CHgDrawUtils* NewL( TCallBack& aMarqueeCallback );
    
    virtual ~CHgDrawUtils();
    
public:
    void ResetMarquee();
    void EnableMarquee( TBool aEnable );

    void DrawImage(
            CWindowGc& aGc, 
            const TRect& aRect,
            const TAknWindowComponentLayout& aLayout,
            const CGulIcon& aIcon
            ) const;
    
    void DrawText(
            CWindowGc& aGc, 
            const TRect& aRect,
            const TAknTextComponentLayout& aLayout,
            const TDesC& aText,
            const TRgb& aColor
            ) const;
    
    void DrawTextMarquee(
            CWindowGc& aGc, 
            const TRect& aRect,
            const TAknTextComponentLayout& aLayout,
            const TDesC& aText,
            const TRgb& aColor,
            const TInt& aMarqueeLine
            );
    
    void DrawEmptyText(
            CWindowGc& aGc, 
            const TRect& aRect,
            const TDesC& aText,
            const TRgb& aColor
            ) const;
    
private:
    CHgDrawUtils();
    
    void ConstructL( TCallBack& aMarqueeCallback );
    
private:

    CHgMarquee* iMarquee;

    TInt iMarqueeLine;
    };

#endif // HGDRAWUTILS_H_
