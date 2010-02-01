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


#ifndef __HGLIST_H__
#define __HGLIST_H__

// INCLUDES
#include <ganes/HgScroller.h>

// Forward declarations
class CAknsFrameBackgroundControlContext;
class CFbsBitmap;
class CGulIcon;
class CHgListLayoutData;

// CLASS DECLARATION
class CHgList : public CHgScroller
    {
public:
    
    /**
     * Destructor
     */
    IMPORT_C virtual ~CHgList( );
    
protected: // CHgScroller
    virtual TInt GetSelected( TPoint aPosition ) const;
    virtual void HandleSizeChanged();
    virtual void DoDraw(const TRect& aRect ) const;
    void InitItemsL();
    virtual TSize TotalSize() const;
    void FitSelectionToView();
    virtual void FitTopItemToView( TInt aIndex );
    TInt CurrentIndex();
    TBool IsDisplayed( TInt aIndex );
    
protected:
    void DrawHighlight( const TRect& aRect, TRgb& aTextColor ) const;
    virtual TBool DoHandleKeyEvent( const TKeyEvent& aKeyEvent );
    void ResetClippingRect( CWindowGc& aGc ) const;
    TRect ListRect() const;

protected:
    virtual void DrawItem(TInt aIndex, const TRect& aRect) const = 0; 
    
protected: // Constructors
    CHgList ( TInt aItemCount, 
            CGulIcon* aDefaultIcon );

    void ConstructL (const TRect& aRect, RWsSession* aSession );

    void HandleDownArrow();
    void HandleUpArrow();
    void SelectDefaultItem();
    
protected: // DATA
    CHgListLayoutData* iLayoutData;
    
    TInt iRows; // Total number of rows to display
        
    TRgb iColor; // Normal item color
    TRgb iColorBack; // normal item background color
    TRgb iHighlightedColor; // color for highlighted item
    TRgb iHighlightedColorBack; // background color for highlighted item 
    
    TPoint iListOffset;
    };

#endif // __HGLIST_H__
    
// End of File
