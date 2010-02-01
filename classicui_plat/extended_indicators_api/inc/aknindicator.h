/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Status indicator control.
*
*/


#ifndef AKNINDICATOR_H
#define AKNINDICATOR_H

//  INCLUDES
#include <e32base.h>
#include <bitstd.h>
#include <bitdev.h>
#include <barsread.h>
#include <coecntrl.h>
#include <avkon.hrh>
#include <AknsItemID.h>

// CONSTANTS

/** Indicator state when it's on, but not visible. */
const TInt KIndicatorNotShown = -1;

// FORWARD DECLARATIONS
class CCoeControl;
class CAknIndicatorContainer;
class CAknIndicatorExtension;
class CAknIndicatorFader;
class MAknIndicatorObserver;

/**
 *  Base interface class for status indicator control.
 *
 *  This is an abstract interface class from which the status
 *  indicator control derives from. It declares the basic indicator
 *  funtionality.
 *
 *  @lib avkon.lib
 *  @since 0.9
 */
class MAknIndicator
    {
public:
    
    /**
     * Possible indicator states.
     */
    enum TIndicatorState
        {
        EIndicatorOff     = EAknIndicatorStateOff,
        EIndicatorOn      = EAknIndicatorStateOn,
        EIndicatorAnimate = EAknIndicatorStateAnimate
        };
    
    /**
     * Indicator layout modes.
     * Usual layout mode is used in usual status pane layouts
     * and wide layout mode is used in idle status pane layouts.
     */
    enum TLayoutMode
        {
        ELayoutModeUsual,
        ELayoutModeWide
        };

public:
    
    /**
     * Constructs the object from resource.
     *
     * @param  aReader  Resource reader
     * @param  aParent  Pointer to the indicator container.
     */
    virtual void ConstructFromResourceL( TResourceReader& aReader,
                                         CAknIndicatorContainer* aParent ) = 0;
                                         
    /**
     * Sets the indicator state.
     * For possible values @see TIndicatorState.
     *
     * @param  aState  New indicator state.
     */
    virtual void SetIndicatorState( TInt aState ) = 0;
    
    /**
     * Gets the indicator state.
     *
     * @return  Current state of the indicator.
     */
    virtual TInt IndicatorState() = 0;
    
    /**
     * Checks if this indicator is a text indicator.
     *
     * @return  @c ETrue if the indicator is a text indicator,
     *          @c EFalse otherwise.
     */
    virtual TBool TextIndicator() = 0;
    
    /**
     * Returns the display priority of the indicator.
     *
     * @return  Indicator priority.
     */
    virtual TInt Priority() = 0;
    
    /**
     * Sets the layout mode of the indicator.
     * For possible values @see TLayoutMode.
     *
     * @param  aMode  Layout mode to be set.
     */
    virtual void SetLayoutMode( TLayoutMode aMode ) = 0;
    
    /**
     * Returns the size of the indicator icon.
     *
     * @return  Size of the indicator icon.
     */
    virtual TSize IconSize() = 0;

    /**
     * Returns the UID of the indicator.
     *
     * @return  UID of the indicator.
     */
    virtual TUid Uid() const = 0;

protected:

    /** Current indicator state. */
    TInt iState;
    
    /** Indicator UID. */
    TInt iUid;

    /**
     * Narrow priority, used in prioritizing the indicators in
     * usual status pane layouts.
     */
    TInt iNarrowPriority;
    
    /**
     * Wide priority, used in prioritizing the indicators in
     * idle status pane layouts.
     */
    TInt iWidePriority;
    };


/**
 *  Default status indicator control.
 *
 *  Default control for a status indicators shown in the status pane's
 *  indicator pane and navi pane. This control is used also for
 *  editing state indicators in queries and in search field's find
 *  indicators. 
 *
 *  @lib avkon.lib
 *  @since 0.9
 */
NONSHARABLE_CLASS( CAknIndicator ) : public CCoeControl,
                                     public MAknIndicator
    {

friend class CAknIndicatorContainer;
friend class CAknIndicatorDataObserver; 

public:

    /**
     * Default constructor.
     * Creates @c EUniversalIndicators indicator.
     */
    CAknIndicator();

    /**
     * Default constructor.
     * Creates an indicator from the specified context.
     * Possible types are:
     *   - EUniversalIndicators,
     *   - ENaviPaneEditorIndicators
     *   - EQueryEditorIndicators
     *
     * @param  aIndicatorContext  Indicator context.
     */
    CAknIndicator( TInt aIndicatorContext );

    /**
     * Destructor.
     */
    ~CAknIndicator();

public: // From base class @c MAknIndicator.

    /** 
     * Constructs the object from resource.
     *
     * @param  aReader  Resource reader.
     * @param  aParent  Pointer to the indicator container.
     */
    virtual void ConstructFromResourceL( TResourceReader& aReader,
                                         CAknIndicatorContainer* aParent );

    /**
     * Sets the indicator state.
     * The state can be one of the following:
     *   - EAknIndicatorStateOff
     *   - EAknIndicatorStateOn
     *   - EAknIndicatorStateAnimate
     *
     * @param  aState  A state to be set to the indicator.
     */
    virtual void SetIndicatorState( TInt aState );

    /** 
     * Return a current state of the indicator.
     *
     * @return Current state of the indicator.
     */
    virtual TInt IndicatorState();

    /**
     * Checks if this indicator is a text indicator.
     *
     * @return @c ETrue if this indicator is dynamic textual message length 
     *         indicator (@c EAknNaviPaneEditorIndicatorMessageLength).
     */
    virtual TBool TextIndicator();

    /** 
     * Returns UID of the indicator.
     *
     * @return UID of the indicator.
     */
    virtual TUid Uid() const;

    /** 
     * Returns the priority of the indicator in the current layout mode.
     *
     * @return The priority of the indicator in the current layout mode.
     */
    virtual TInt Priority();

    /** 
     * Set layout mode of the indicator.
     * Indicators can have different priorities and bitmaps in
     * different layout modes.
     *
     * @param  aMode  Layout mode.
     */
    virtual void SetLayoutMode( TLayoutMode aMode );

    /**
     * Returns the size of the indicator bitmap.
     *
     * @return The size of the indicator bitmap.
     */
    virtual TSize IconSize();

public: // New methods

    /** 
     * Sets value to the message length indicator
     * (@c EAknNaviPaneEditorIndicatorMessageLength).
     *
     * Panics if this is not a message length indicator.
     *
     * @param  aString  Value of the indicator.
     */
    void SetIndicatorValueL( const TDesC& aString );

   /** 
    * Sets value to the progress bar indicator 
    * (@c EAknNaviPaneEditorIndicatorProgressBar).
    *
    * Panics if this is not progress bar indicator.
    *
    * @since 2.1
    *
    * @param  aValue     Current progress value of the task that bar describes.
    * @param  aMaxValue  Progress value when the task is finished.
    *
    */
    void SetIndicatorValue( TInt aValue, TInt aMaxValue );

    /**
     * Sets fader object for this indicator.
     *
     * @internal
     *
     * @param  aFader  A fader which will take care of fading this
     *                 indicator if needed. Used only in stacon pane layouts.
     *
     */
    void SetIndicatorFader( CAknIndicatorFader* aFader );

    /**
     * @deprecated Indicator observer is not used anymore.
     *
     * @param  aIndicatorObserver  Not used.
     *
     */
    IMPORT_C void SetIndicatorObserver(
        MAknIndicatorObserver* aIndicatorObserver );
    
public : // From base class @c CCoeControl.
    
    /**
     * Handles pointer events,
     *
     * @param  aPointerEvent  Pointer event to be handled.
     */
    IMPORT_C void HandlePointerEventL( const TPointerEvent& aPointerEvent );
    
public : // New methods
    
    /**
     * Sets the multi-color mode of this indicator.
     * In multi-color mode the indicator icon can be drawn with
     * multiple colors, otherwise it's drawn using one color
     * defined by the current skin.
     *
     * @param  aMultiColor  @c ETrue to set the multi-color mode on,
     *                      @c EFalse otherwise.
     */
    void SetMultiColorMode( TBool aMultiColor );
    
    /**
     * Checks if this indicator is drawn in multi-color mode.
     *
     * @return  @c ETrue if the indicator is drawn in multi-color,
     *          @c EFalse otherwise.
     */
    TBool MultiColorMode() const;

    void SetIndicatorPosition( TInt aPosition );
    
    TInt IndicatorPosition() const;
    
    /**
     * from CCoeControl 
     *
     * Responds to changes in the position of a control.
     *
     */
    IMPORT_C virtual void PositionChanged();

    /**
     * Returns the bitmap and mask index in the AVKON bitmap file
     * corresponding the icon of the specified indicator.
     *
     * This utility method can be used to retrieve the correct
     * indicator icon in case an application wishes to draw the indicator.
     *
     * @param       aIndicatorContext  Indicator context in which the indicator
     *                                 belongs to, @see TIndicatorContext.
     * @param       aIndicatorId       ID of the status indicator.
     * @param[out]  aBitmapIndex       On return contains the index of the
     *                                 bitmap in @c avkon.mbg.
     * @param[out]  aBitmapIndex       On return contains the index of the
     *                                 mask in @c avkon.mbg.
     */
    IMPORT_C static void GetBitmapIndexL( TInt  aIndicatorContext,
                                          TInt  aIndicatorID,
                                          TInt& aBitmapIndex,
                                          TInt& aMaskIndex );
        
private: // From base class @c CCoeControl.

    /**
     * Draws the control.
     *
     * @param  aRect  Not used.
     */
    virtual void Draw( const TRect& aRect ) const;

protected: // From base class @c CCoeControl.

    /**
     * Handles size change events.
     */
    virtual void SizeChanged();

private: // New methods

    void LoadIndicatorBitmapsL( TResourceReader& aReader, TInt aCount );
    
    void LoadIndicatorBitmapsL( TResourceReader& aReader,
                                TInt aCount,
                                TBool aCreateBitmaps );
                                
    void CreateLoadedIndicatorBitmapsL();
    
    void SetAnimateState( TInt aAnimState );
    
    void Animate();
    
    void SetSvgIconSize( CFbsBitmap*& aBitmap, TInt aLayoutMode );

    /**
     * Handles a change to the control's resources.
     *
     * @param  aType  Event type.
     */
    void HandleResourceChange( TInt aType );
    
    TRgb SelectColor( TInt aLayoutMode ) const;
    
    TRgb ActiveColor( TInt aLayoutMode );
    
    void SelectColorSkin( TInt aLayoutMode,
                          TAknsItemID& aColorGroup,
                          TInt& aColorIndex ) const;
                          
    void ActiveColorSkin( TInt aLayoutMode,
                          TAknsItemID& aColorGroup,
                          TInt& aColorIndex ) const;

    /**
     * Deletes the indicator bitmaps.
     */
    void DeleteBitmaps();
    
    HBufC* Text() const;
    
    TBool DynamicTextIndicator() const;
    
    void SetupDynamicIndicatorTextL( TInt aWidth );

private:

    /**
     * Array containing the indicator bitmaps.
     * Own.
     */
    typedef CArrayPtrFlat<CFbsBitmap> CAknBitmapQueue;
    CAknBitmapQueue* iIndicatorBitmaps[2];
    
    /** Current layout mode of the indicator. */
    TLayoutMode iLayoutMode;

    /**
     * Indicator container control to which this indicator belongs to.
     * Not own.
     */
    CAknIndicatorContainer* iParent;
    
    /**
     * Internal extension class.
     * Own.
     */
    CAknIndicatorExtension* iExtension;
    
    /**
     * The bitmap file which contains the indicator icon.
     * Own.
     */
    HBufC* iBitmapFile;
    
    /** Current animation frame for an animated indicator. */
    TInt iAnimState;
    
    /** Count of frames for an animated indicator. */
    TInt iCountOfAnimStates;
    
    /** Flag indicating whether or not this indicator is a text indicator. */
    TBool iIndicatorTypeText;
    
    /** Indicator context in which this indicator belongs to. */
    TInt iIndicatorContext;

    /**
     * Text displayed as an editor indicator.
     * Own.
     */
    HBufC* iIndicatorText;
    
    /** Current value for the progress bar indicator. */
    TInt iProgressBarValue;
    
    /** Maximum value for the progress bar indicator. */
    TInt iProgressBarMaxValue;
    };

#endif // AKNINDICATOR_H
       
// End of File
