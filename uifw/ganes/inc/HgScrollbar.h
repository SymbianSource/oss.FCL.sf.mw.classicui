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


#ifndef HGSCROLLBAR_H_
#define HGSCROLLBAR_H_


#include <e32base.h>
#include <ganes/HgScroller.h>

struct TPointerEvent;
class TAknsItemID;
class CWindowGc;
class CFbsBitmap;
class CGulIcon;
class CFont;

class MHgScrollbarObserver;

NONSHARABLE_CLASS( CHgScrollbar ) : public CBase
    {
public:
    static CHgScrollbar* NewL( MHgScrollbarObserver& aObserver );
    
    virtual ~CHgScrollbar();
    
public:

    void InitScrollBarL(
            TRect aScrollbarRect,
            TSize aTotalSize,
            TSize aViewSize,
            TBool aLandscapeScrolling );
    
    void SetViewPosition( TPoint aPosition );
    
    TBool HandlePointerEventL( const TPointerEvent& aEvent );

    void Draw( CWindowGc& aGc );

    const CGulIcon* ScrollbarBg() const;
    
    const CGulIcon* ScrollbarHandleBg() const;
    
    const CGulIcon* ScrollbarHandle() const;
    
    const CGulIcon* ScrollbarBgSelected() const;
    
    const CGulIcon* ScrollbarHandleSelected() const;
    
    const TRect& ScrollbarRect() const;
    
    const TPoint& HandlePosition() const;
    
    TBool IsStatic() const;
    
    TBool IsDragging() const;
    
    TBool Handler() const;
    
    void Reset();
        
protected:
    CHgScrollbar( MHgScrollbarObserver& aObserver );
    
    void ConstructL();
    
private:

    void DrawScrollbar( CWindowGc& aGc );

    TBool HandleScrollBarPointerEvent( const TPointerEvent& aEvent );    
    
    void CheckHandlePosition( TBool aReportChange );
    
    void InitIconsL( TBool aInitBgIcons );
    
    void CreateIconL( CGulIcon*& aIcon, TSize aSize);
    
    void DrawIconL( CGulIcon& aIcon,
            const TAknsItemID& aTop,
            const TAknsItemID& aMiddle,
            const TAknsItemID& aBottom );

    void DrawBitmapL( CGulIcon& aIcon,
            const TAknsItemID& aItem,
            const TRect& aDestRect );

    void ScaleBitmapL( const TRect& aDestRect,
            CFbsBitmap* aDest,
            const CFbsBitmap* aSrc);

private:
    MHgScrollbarObserver& iObserver;
    
    CGulIcon* iScrollbarBg;
    CGulIcon* iScrollbarHandleBg;
    CGulIcon* iScrollbarHandle;
    CGulIcon* iScrollbarBgSelected;
    CGulIcon* iScrollbarHandleSelected;

    TRect iScrollbarRect;
    TRect iNaviRect;
    TPoint iHandlePosition;
    TPoint iPrevDrag;
    TSize iTotalSize;
    TSize iViewSize;
    TSize iHandleSize;
    TBool iLandscapeScrolling;
    TBool iDragging;
    TBool iHandler;
    TBool iStatic;
    
    TInt iScrollLength;
    TInt iTotalLength;
    };

#endif /*HGSCROLLBAR_H_*/
