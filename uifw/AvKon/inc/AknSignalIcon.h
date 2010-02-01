/*
* Copyright (c) 2004-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Control to show signal icon indicator on the status pane's
*                signal pane.
*
*/


#ifndef AKNSIGNALICON_H
#define AKNSIGNALICON_H

#include <coecntrl.h>

/**
* Signal icon control for the status pane's signal pane.
* This control is also used in the universal status indicator popup's
* signal pane.
* The control loads and draws signal icon indicator graphics.
*
* @lib avkon.lib
*/
NONSHARABLE_CLASS( CAknSignalIcon ) : public CCoeControl
	{
public:
  
    /**
    * Destructor.
    */
    ~CAknSignalIcon();
    
    /**
    * Two-phased constructor.
    */
    static CAknSignalIcon* NewL();
    
    /**
    * Two-phased constructor.
    */
    static CAknSignalIcon* NewLC();
    
    /**
    * Set a custom signal icon.
    *
    * @param  aIcon  The new icon to be set.
    */
    void SetSignalIcon( CFbsBitmap* aIcon );
    
    /**
    * Set a mask for the custom signal icon.
    *
    * @param  aMask  The new mask to be set.
    */
    void SetSignalIconMask( CFbsBitmap* aMask );
    
    /**
    * Set the draw blanker state, which controls whether
    * or not the icon is drawn.
    *
    * @param  aDrawBlank  New draw blanker state,
    *                     @c EFalse to draw the signal icon,
    *                     @c ETrue otherwise.
    */
    void SetDrawBlank( TBool aDrawBlank );
    
    /**
    * Gets the current draw blanker state.
    *
    * @return  The state of draw blanker.
    */
    TBool DrawBlank();

    /**
    * Sets the offline state.
    * If offline state is on, then the icon is not drawn,
    * unless offline icon visiblity is set on with
    * @c SetOffLineIconDraw().
    *
    * @param  aOffLine  New offline state.
    */
    void SetOffLine( TBool aOffLine );

    /**
    * Gets the current offline state.
    *
    * @return  The offline state.
    */
    TBool OffLine();

    /**
    * Sets the color index to be used when loading
    * the signal icon.
    *
    * @param  aColorIndex  The color index to be set.
    */
    void SetColorIndex( TInt aColorIndex );
    
    /**
    * Returns the current signal icon color index.
    *
    * @return  The color index.
    */
    TInt ColorIndex();
    
    /**
    * Loads the signal icon to be displayed.
    * 
    * @param  aIconState       ID of the signal state, @see signal indicator
    *                          states in @c avkon.hrh.
    * @param  aIconColorIndex  Color index of the icon.
    * @param  aForceLoad       Forces the loading of the signal icon,
    *                          even if it's already loaded.
    */
    void LoadIconL( TInt aIconState,
                    TInt aIconColorIndex,
                    TBool aForceLoad = EFalse );
    
    /**
    * Sets whether or not a signal icon is drawn
    * in offline state.
    *
    * @param  aOn  @c ETrue to draw offline icon, @c EFalse otherwise.
    */
    void SetOffLineIconDraw( TBool aOn );
    
protected: // From base class @c CCoeControl.

    /**
    * From @c CCoeControl.
    * Handles size change events.
    */
    void SizeChanged();

    /**
    * From @c CCoeControl.
    * Handles position change events.
    */
	void PositionChanged();

    /**
     * From @c CCoeControl.
	 * Handles a change to the control's resources of type @c aType,
	 * which are shared across the environment.
	 *
	 * @param  aType  Event type.
	 */
	void HandleResourceChange( TInt aType );

          
private: // From base class @c CCoeControl.
    
    /**
    * From @c CCoeControl.
    * Draws the icon.
    *
    * @param  aRect  Not used.
    */
    virtual void Draw( const TRect& aRect ) const;

private:

    /**
    * Default constructor.
    */
    CAknSignalIcon();
    
    /**
    * Second-phase constructor.
    */
    void ConstructL();

private:
    
    /**
    * Signal icon.
    * Own.
    */
    CFbsBitmap* iSignalIcon;
    
    /**
    * Signal icon mask.
    * Own.
    */
    CFbsBitmap* iSignalIconMask;
    
    /** Signal icon's color index. */
	TInt        iColorIndex;
	
	/** Draw blanker state. */
    TBool       iDrawBlank;
    
    /** Offline state. */
    TBool       iOffLine;
    
    /** Signal state. */
    TInt        iIconState;
    
    /** Flag defining whether or not the offline icon is drawn. */
    TBool       iShowOffLineIcon;
    };

#endif // AKNSIGNALICON_H
