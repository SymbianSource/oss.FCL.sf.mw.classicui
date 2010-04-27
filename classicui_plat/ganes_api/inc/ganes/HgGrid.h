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


#ifndef HGGRID_H_
#define HGGRID_H_

// INCLUDES
#include <ganes/HgScroller.h>

class CHgGridLayoutData;

// CLASS DECLARATION
class CHgGrid : public CHgScroller
    {
public: // CONSTRUCTORS & DESTRUCTOR
    
    /**
     * Creates new HgGrid.
     * 
     * @param aRect Rect that the control draws onto.
     * @param aItemCount Total count of items in the grid
     * @param aDefaultIcon Default icon to be used.
     * @param aSession Window server session for DSA. Default is NULL and DSA is disabled.
     * 
     * @return HgGrid-object
     */
    IMPORT_C static CHgGrid* NewL(
            const TRect& aRect, 
            TInt aItemCount, 
            CGulIcon* aDefaultIcon = NULL,
            RWsSession* aSession = NULL ); 
    
    /**
     * Destructor.
     */
    IMPORT_C virtual ~CHgGrid ( );

public:
    
    /**
     * Returns preferred image size that should be used when passing images.
     */
    IMPORT_C static TSize PreferredImageSize();

    /**
     * Set landscape scrolling support. If enabled lanscape scrolling
     * is on only in landscape orientation. InitScreenL must be called after
     * this to relayout the grid.
     * 
     * @param aSupportLandscapeScrolling Landscape scrolling supported or not.
     */
    IMPORT_C void SetLandscapeScrollingSupport( TBool aSupportLandscapeScrolling );
    
    /**
     * Set toolbar visibilty. The toolbar visibility ETrue changes the lanscape layout to 
     * fill the toolbar space with grid content.
     * 
     * @param aToolbarVisible Is toolbar visible or not.
     */
    IMPORT_C void SetToolbarVisibility( TBool aToolbarVisible );
    
protected: // CHgScroller
    TInt GetSelected( TPoint aPosition ) const;
    void HandleSizeChanged();
    void InitItemsL();
    TSize TotalSize() const;
    void DoDraw(const TRect& aRect ) const;
    TBool DoHandleKeyEvent( const TKeyEvent& aEvent );
    void FitSelectionToView();
    void FitTopItemToView( TInt aIndex );
    TInt CurrentIndex();
    TBool IsDisplayed( TInt aIndex );
    void HandleScrollbarVisibilityChange(TBool aVisible);
    
private: // Constructors
    CHgGrid( TInt aItemCount, 
            CGulIcon* aDefaultIcon );
    
    void ConstructL (const TRect& aRect, RWsSession* aSession );

private:
    void DrawHighlight( const TRect& aOuterRect ) const;
    
    void HandleDownArrow();
    void HandleUpArrow();
    void HandleRightArrow();
    void HandleLeftArrow();
    void SelectDefaultItem();
    
    TRect GridRect() const;
    void DrawCols( TInt aRow, const TRect& aRect, TInt aYPos ) const;
    void DrawRows( TInt aCol, const TRect& aRect, TInt aXPos ) const;
    void DrawItem( TInt aIndex, const TRect& aRect ) const;
    
    void CalculateSizes();
    void ChangeSelectedIndex( TInt aMove );
    
private: // DATA
    CHgGridLayoutData* iLayoutData;
    
    TInt iRows; // Total number of rows to display
    TInt iCols; // Total number of cols to display

    TInt iRowWidth;
    TBool iLandScapeScrollingSupported;
    TBool iToolbarVisible;
    };

#endif // HGGRID_H_
// End of File
