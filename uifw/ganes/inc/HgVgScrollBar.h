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

#ifndef HGVGSCROLLBAR_H_
#define HGVGSCROLLBAR_H_

// INCLUDES
#include <ganes/HgScroller.h>
#include <e32base.h>
#include <VG/openvg.h>
#include <gulcolor.h>

// FORWARD DECLARATIONS

class MHgScrollbarObserver;
class CHgScrollbar;

/**
 * Helper class for drawing and interacting scrollbars.
 */
NONSHARABLE_CLASS(CHgVgScrollBar) : CBase
    {
public:

    /**
     * Creates new CHgVGScrollBar.
     *
     * @param aObserver observer for the scrollbar.
     */
    static CHgVgScrollBar* NewL( MHgScrollbarObserver& aObserver, 
            TRect aScrollbarRect,
                        TSize aTotalSize,
                        TSize aViewSize,
                        TBool aLandscapeScrolling,
                        CHgScroller::THgScrollBarType aScrollBarType );
            
    // Destructor.
    virtual ~CHgVgScrollBar();

public: // METHODS
    
    void SetViewPosition( TPoint aPosition );
    
    TBool HandlePointerEventL( const TPointerEvent& aEvent );

    void Draw(const TRect& aWindowRect, TReal aAlpha) const;
    
    TBool IsEnabled() const;
    
    void SetEnabled(TBool aEnabled);
    
    void ResizeL(MHgScrollbarObserver& aObserver, TRect aScrollbarRect,
            TSize aTotalSize,
            TSize aViewSize,
            TBool aLandscapeScrolling,
            CHgScroller::THgScrollBarType aScrollBarType);
    
    void EnableLandscapeRendering(TBool aEnabled);

protected: // Constructors
    CHgVgScrollBar(  );

    void ConstructL (MHgScrollbarObserver& aObserver, TRect aScrollbarRect,
            TSize aTotalSize,
            TSize aViewSize,
            TBool aLandscapeScrolling,
            CHgScroller::THgScrollBarType aScrollBarType);

protected: // Internal implementation

    void CreateImagesL();

    void DrawImage(const TPoint& aPosition, VGImage aImage, 
            const TSize& aSize, const TRect& aWindowRect, TReal aAlpha) const;
    
private:
    TBool iEnabled;
    
    CHgScrollbar* iScrollbar;

    VGImage iScrollbarBg;
    VGImage iScrollbarHandleBg;
    VGImage iScrollbarHandle;
    VGImage iScrollbarBgSelected;
    VGImage iScrollbarHandleSelected;
    
    TBool iLandscape;
                    
    };

#endif /* HGVGSCROLLBAR */
