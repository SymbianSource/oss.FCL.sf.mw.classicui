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


#ifndef HGSCROLLERWITHTITLE_H_
#define HGSCROLLERWITHTITLE_H_

// INCLUDES
#include <coecntrl.h>
#include <coemain.h>

// FORWARD DECLARATIONS
class CGulIcon;
class CHgScroller;
class CHgListLayoutData;
class CHgItem;

// CLASS DECLARATION

/**
 * Compound control that compounds a static title element
 * and HgScroller. Scroller is owned by this control but it can be
 * accessed freely. However, user of this class
 * should not call InitScreenL for the scroller, because it is this classes
 * responsibility to set correct size for the HgScroller. 
 */
class CHgScrollerWithTitle : public CCoeControl
    {
public:
        
    // Possible scroller types. Used to define the scroller type
    // for this compound control
    enum THgScrollerType
        {
        EHgScrollerDoubleGraphicList,
        EHgScrollerDoubleTextList,
        EHgScrollerSingleGraphicList,
        EHgScrollerSingleLargeList,
        EHgScrollerSingleTextList,
        EHgScrollerGrid,
        EHgScrollerSingleTextListWithIcon,
        EHgScrollerDoubleGraphicListFlat
        };
    
    /**
     * Creates new CHgScrollerWithTitle.
     * 
     * @param aRect Rect that the control draws onto.
     * @param aItemCount Total count of items in the grid
     * @param aScrollerType Type of the scroller control.
     * @param aDefaultIcon Default icon to be used.
     * 
     * @return CHgScrollerWithTitle-object
     */
    IMPORT_C static CHgScrollerWithTitle* NewL( const TRect& aRect, 
            TInt aItemCount,
            THgScrollerType aScrollerType,
            CGulIcon* aDefaultIcon = NULL );
        
public: // Destructor.
    
    virtual ~CHgScrollerWithTitle();
    
public: // CCoeControl
    
    void Draw(const TRect& aRect ) const;
    void SizeChanged();
    TInt CountComponentControls() const;
    CCoeControl* ComponentControl(TInt aIndex) const;
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );
    void FocusChanged(TDrawNow aDrawNow);

public: // NEW FUNCTIONS
    
    /**
     * Re-inits the grid display area. 
     * 
     * @param aRect New display rect
     */
    IMPORT_C void InitScreenL( const TRect& aRect );
    
    /*
     * Get CHgScroller compound control. 
     * 
     * Notice, you shouldn't call
     * InitScreenL for the CHgScroller, instead this classes InitScreenL should
     * be used to set the size of this control.
     * 
     * @return Compound control.
     */
    IMPORT_C CHgScroller& Scroller();
    
    /*
     * Get the title element.
     * 
     * @return Title item (CHgItem). 
     */
    IMPORT_C CHgItem& TitleItem();
    
    /**
     * Returns preferred image size that should be used when setting image to title.
     */
    IMPORT_C static TSize PreferredImageSize();    
    
protected: // Constructors

    CHgScrollerWithTitle( );

    void ConstructL(const TRect& aRect, 
            TInt aItemCount,
            THgScrollerType aScrollerType,
            CGulIcon* aDefaultIcon );
    
protected:
    CHgScroller* iScroller; // Compound control. Own
    CHgListLayoutData* iLayoutData; // Layout data stroge. Own
    CHgItem* iTitleItem; // Title element. Own

    TRgb iColor; // Text color
    TRect iTitleRect; // Drawing rect for the title.
    };

#endif /*HGSCROLLER_H_*/
