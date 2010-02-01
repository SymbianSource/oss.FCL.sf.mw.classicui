/*
* Copyright (c) 2002-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  A default control in the status pane's title pane.
*
*/


#ifndef C_AKNTITLE_H
#define C_AKNTITLE_H

#include <AknControl.h>
#include <coeccntx.h>

class CEikLabel;
class CEikImage;
class CAknTitlePaneExtension;
class CAknTitlePaneLabel;
class MAknTitlePaneObserver;
class TAknTextLineLayout;

/**
 * A default control in the status pane's title pane.
 *
 * @lib avkon.lib
 */
class CAknTitlePane : public CAknControl, public MCoeControlContext
	{
public:
    /**
    * Constructor.
    */
    IMPORT_C CAknTitlePane();

    /**
    * Destructor.
    */
    IMPORT_C ~CAknTitlePane();
    
    /**
    * 2nd phase constructor.
    */
    IMPORT_C void ConstructL();
    
    /**
    * Read title pane data from resource file and show it in
    * the status pane's title pane.
    */
    IMPORT_C void ConstructFromResourceL( TResourceReader& aReader );
    
    /**
    * Set a text and show it in the status pane's title pane.
    * Descriptor is copied to the title pane control and ownership of
    * the original descriptor is left to the application.
    *
    * @param  aText  Text to be shown on the title pane.
    */
    IMPORT_C void SetTextL( const TDesC& aText );
    
    /**
    * Sets text to the title pane.
    *
    * @param  aText	 New text. This object takes ownership of @c aText.
    */
    IMPORT_C void SetText( HBufC* aText );

    /**
    * Set a text and show it in the status pane's title pane.
    * If whole text does not fit into titlepane, it will be scrolled once
    * and then shown in truncated form. 
    *
    * Descriptor is copied to the title pane control and ownership
    * of the original descriptor is left to the application.
    *
    * @since 3.0
    *
    * @param  aText    Text to be shown on the title pane.
    * @param  aScroll  If @c ETrue text is scrolled when needed, otherwise not.
    * 
    */
    IMPORT_C void SetTextL( const TDesC& aText, TBool aScroll );    

    /**
    * Sets text to the title pane. If whole text does not fit into titlepane,
    * it will be scrolled once and then shown in truncated form. 
    *
    * @since 3.0
    *
    * @param  aText   New text. This object takes ownership of @c aText.
    *                 If @c NULL is given then already existing text's
    *                 scrollability will be changed according to @c aScroll.
    * @param aScroll  If ETrue text is scrolled when needed, otherwise not.  
    */
    IMPORT_C void SetText( HBufC* aText, TBool aScroll );
    
    /**
    * Returns text currently in the status pane's title pane.
    * Ownership is not transferred.
    *
    * @return  Text currently shown in the title pane.
    */
    inline const TDesC* Text() const;
    
    /**
    * Set a picture to the title pane and show it in the
    * status pane's title pane.
    * Title pane object takes ownership of the picture.
    * If @c NULL bitmap is passed, previously set image is shown.
    *
    * @param  aBitmap      Bitmap to be set on the title pane.
    * @param  aMaskBitmap  Mask of the bitmap.
    */
    IMPORT_C void SetPicture( const CFbsBitmap* aBitmap,
                              const CFbsBitmap* aMaskBitmap = NULL );
    
    /**
    * Set a picture from file and show it in the status pane's title pane.
    *
    * @param  aFileName  Name of the bitmap file.
    * @param  aMainId    Index of the bitmap in the bitmap file.
    * @param  aMaskId    Index of the bitmap's mask in the bitmap file.
    */
    IMPORT_C void SetPictureFromFileL( const TDesC& aFileName,
                                       TInt aMainId,
                                       TInt aMaskId = -1 );

    /**
    * Set a small picture to the title pane and show it in the
    * status pane's title pane together with text.
    * 
    * Title pane object takes ownership of the picture.
    *
    * If @c NULL bitmap is passed, previously set image is used.
    *
    * @since 3.0
    *
    * @param  aBitmap      Bitmap to be set on the title pane.
    * @param  aMaskBitmap  Mask of the bitmap.
    * @param  aVisible     If @c ETrue, picture is set visible. Otherwise only text is shown.
    */
    IMPORT_C void SetSmallPicture( const CFbsBitmap* aBitmap,
                                   const CFbsBitmap* aMaskBitmap,
                                   TBool aVisible );
    
    /**
    * Set data from resource file and show it in the status pane's title pane.
    *
    * @param  aReader  Resource reader of the title pane data.
    */
    IMPORT_C void SetFromResourceL( TResourceReader& aReader );
    
    /**
    * Set default value to the status pane's title pane.
    * Default value is the name of currently active application.
    */
    IMPORT_C void SetTextToDefaultL();
    
    /**
    * Gets the maximum amount of text rows that title pane is able to display simultaneously
    * in the currently active status pane layout. Typically the return value is 
    * either 2 (default portrait mode layout) or 1 (landscape mode layouts).
    * In the extended status pane layouts the maximum number of lines is always 1.
    *
    * Since release 3.2, regardless of the status pane layout,
    * the maximum number of lines is always 1.
    *
    * @since 3.1
    *
    * @return Maximum number of visible text lines.
    */    
    IMPORT_C TInt MaxNumberOfVisibleTextRows() const;

    /**
    * Sets the number of text rows that can be used to display the text. 
    * The largest allowed value is the the value returned from MaxNumberOfVisibleTextRows() and 
    * the minimum value is always 1.
    *
    * @since 3.1
    *
    * @param  aRows  Number of rows that can be used to display the text.
    */    
    IMPORT_C void SetNumberOfVisibleTextRows( TInt aRows );
    
public: // From base class @c MCoeControlContext.

    /** 
    * Allows to modify graphics context before @c Draw.
    *
    * @param  aGc  Graphics context to be modified.
    */
    IMPORT_C virtual void PrepareContext( CWindowGc& aGc ) const;
    
protected: // From base class @c CCoeControl.

    /**
    * Handles the size change events.
    */
    IMPORT_C virtual void SizeChanged();

    /**
    * Handles the position change events.
    */
    IMPORT_C virtual void PositionChanged();

    /**
	* Handles a change to the control's resources which are shared across
	* the environment, e.g. skin change.
	*
	* @param  aType  Event type.
	*/
    IMPORT_C virtual void HandleResourceChange( TInt aType );

    /**
    * Returns number of controls inside the title pane control.
    *
    * @return Number of component controls.
    */
    IMPORT_C virtual TInt CountComponentControls() const;

    /**
    * Returns a control determined by control index.
    *
    * @param  aIndex  Index of a control to be returned.
    *
    * @return Pointer to the control.
    */
    IMPORT_C virtual CCoeControl* ComponentControl(TInt aIndex) const;
    
public: // From base class @c CCoeControl.

    /**
    * Handles pointer events.
    *
    * @param  aPointerEvent  Pointer event to be handled.
    */
    IMPORT_C void HandlePointerEventL( const TPointerEvent& aPointerEvent );

public: // New methods

    /**
    * Sets observer for title pane events.
    *
    * @param  aObserver  Pointer to title pane observer.
    */
    IMPORT_C void SetTitlePaneObserver( MAknTitlePaneObserver* aObserver );

private: // From base class @c CAknControl.

    IMPORT_C void* ExtensionInterface( TUid aInterface );

public:

    /**
    * Gets title text label.
    * @internal
    */
    CEikLabel* TextLabel();
    
    /**
    * Gets the title image.
    * @internal
    */
    CEikImage* TitleImage();

private:

    void CommonConstructL();
    TUid AppUid() const;

    TInt FormatTitlePaneLabelL( const TInt aOneLineLayoutWidth,
                                const TInt aTwoLineLayoutWidth,
                                const CFont* aOneLineFont,
                                const CFont* aTwoLineFont );

    void ReadFromResourceFileL( TResourceReader& aReader );
    void SetSmallPictureFromFileL( const TDesC& aFileName, TInt aMainId, TInt aMaskId = -1 );
    
private: // From base class @c CCoeControl.

    IMPORT_C virtual void Draw( const TRect& aRect ) const;
    
protected:

    MAknTitlePaneObserver* iTitlePaneObserver;
    
private:
    void SizeChangedInNormalStatusPane();
    void SizeChangedInExtendedStatusPane();
    void SizeChangedInFlatStatusPane();
    void SizeChangedInStaconPane();
    RWindow* StatuspaneContainerWindow() const;
    void SetupTitleLabelEffectL();
    void SetContainerWindowNonFading( TBool aNonFading );
    
    void SetupStaconPaneScrollEffectL();
    void SetupFlatStatusPaneScrollEffectL();
    void SetupNormalStatusPaneScrollEffectL();
    void SetupFlatStatusPaneFadeEffectL();
    void SetupExtendedStatusPaneScrollEffectL();
    void SetupNoEffectL();
    
    TBool TextFits( TAknTextLineLayout& aTextLayout );

private: // Member data

    HBufC*                  iTitleText;
    HBufC*                  iDefaultTitleText;
    CAknTitlePaneLabel*     iTitleLabel;
    TBool                   iImageShown;
    CAknTitlePaneExtension* iExtension;
    };

inline const TDesC* CAknTitlePane::Text() const
    {
    return( iTitleText );
    }

#endif // C_AKNTITLE_H
