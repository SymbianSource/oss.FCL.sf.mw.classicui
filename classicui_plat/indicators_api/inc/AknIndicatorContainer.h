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
* Description:  A default control in the status pane's small indicator pane.
*                Editor indicators uses also same control in the navigation
*                pane and in queries.
*
*/


#ifndef AKNINDICATORCONTAINER_H
#define AKNINDICATORCONTAINER_H

//  INCLUDES
#include <AknControl.h>
#include <eikspane.h>

class CIncallStatusBubble;
class CAknIndicator;
class CAknIndicatorContainerExtension;
class CAknPictographInterface;
class MAknIndicatorObserver;

/**
 * The default control in the status pane's small indicator pane.
 * This container is also used for the status indicators in navi pane and
 * for editor indicators in queries.
 */
class CAknIndicatorContainer : public CAknControl, public MEikStatusPaneObserver
	{
friend class CAknIndicatorContainerExtension;
friend class CAknIndicatorDataObserver;
public:

    /**
    * Layout orientations of the indicator container.
    * These are used to specify how the indicators are laid
    * out inside the indicator container.
    */
    enum TLayoutOrientation
        {
        EVertical,  ///< Indicators are arranged vertically.
        EHorizontal ///< Indicators are arranged horizontally.
        };

    /** Alignment of the indicators. */
    enum TIndicatorAlignment
        {
        ELeft,   ///< Indicators are aligned on the left side.
        ERight   ///< Indicators are aligned on the right side.
        };

    /**
    * Context of the indicator container.
    * These are used to specify what type of status indicators
    * the indicator container contains.
    */
    enum TIndicatorContext
        {
        EUniversalIndicators = 0,   ///< Universal status indicators.
        ENaviPaneEditorIndicators,  ///< Editor indicators shown in navi pane.
        EQueryEditorIndicators,     ///< Editor indicators shown in queries.
        EFindIndicators             ///< Search field indicators.
        };

    /**
    * Position of a indicator.
    * These are used for invidual indicators to coarsely specify
    * where they are positioned inside the indicator container.
    */
    enum TIndicatorPosition
        {
        ELeftSide,  ///< Indicator positioned on the left side.
        ERightSide, ///< Indicator positioned on the right side.
        EMiddle     ///< Indicator positioned in the middle.
        };

    /** Additional flags that can be used for custom indicators. */
    enum TCustomIndicatorFlags
    	{
    	EMultiColorIndicator       = 0x1, ///< Indicator is multi-colored.
    	EIndicatorPositionInverted = 0x2  ///< Indicator's position is inverted.
    	};

    /** Layout modes of indicator container. */
    enum TLayoutMode
		{
		ELayoutModeUsual, ///< Used for universal indicators when not in idle.
		ELayoutModeWide   ///< Used for navi pane indicators and universal indicators in idle.
		};

public:

    /**
    * Default constructor.
    * Creates an @c EUniversalIndicators object.
    */
    IMPORT_C CAknIndicatorContainer();

    /**
    * Constructor. Creates @c EUniversalIndicators, @c ENaviPaneEditorIndicators
    * or @c EQueryEditorIndicators object.
    *
    * @param  aIndicatorContext  Indicator container context.
    */
    IMPORT_C CAknIndicatorContainer( TInt aIndicatorContext );

    /**
    * Destructor.
    */
    IMPORT_C ~CAknIndicatorContainer();

    /**
    * Second-phase constructor.
    */
    IMPORT_C void ConstructL();

    /**
    * Sets indicator state. The state can be one of the following:
    *   - @c EAknIndicatorStateOff
    *
	*   - @c EAknIndicatorStateOn
	*
	*   - @c EAknIndicatorStateAnimate
	*
	* Editor indicators do not support animation.
    *
    * @param  aIndicatorId  ID of the indicator to be modified.
    * @param  aState        A state to be set to the indicator.
    * @param  aDrawNow      A flag to indicate if the indicator
    *                       is redrawn with this call.
    */
    IMPORT_C void SetIndicatorState( TUid aIndicatorId,
                                     TInt aState,
                                     TBool aDrawNow = ETrue );

    /**
    * Return the current state of an indicator.
    *
    * @param  aIndicatorId  ID of the indicator.
    * @return Current state of the indicator.
    */
    IMPORT_C TInt IndicatorState( TUid aIndicatorId );

    /**
    * Sets value to the message length indicator
    * (@c EAknNaviPaneEditorIndicatorMessageLength).
    *
    * @param  aIndicatorId  ID of the indicator to be modified.
    * @param  aString       Value of the indicator.
    */
    IMPORT_C void SetIndicatorValueL( TUid aIndicatorId, const TDesC& aString );

    /**
    * Sets value to the incall status bubble indicator on the
    * top of the status pane.
    *
    * @param  aFlags  Mode of the bubble.
    */
    IMPORT_C void SetIncallBubbleFlags( const TInt& aFlags );

    /**
    * Constructs the object from resource.
    *
    * @param  aReader  Resource reader.
    */
    IMPORT_C void ConstructFromResourceL( TResourceReader& aReader );

    /**
    * Returns the context of the indicator container.
    *
    * @return Context of the indicator container.
    */
    IMPORT_C TInt IndicatorContext() const;


public: // From base class @c MEikStatusPaneObserver.

    /**
    * The @c MEikStatusPaneObserver interface allows a status pane observer
    * to pick up changes in the size or position of the status pane.
    * Such events will be as a result of layout changes which
    * cause an actual change in the status pane rectangle.
    */
    IMPORT_C void HandleStatusPaneSizeChange();

public: // From base class @c CCoeControl.

    /**
    * Handles pointer events.
    *
    * @param  aPointerEvent  The pointer event.
    */
    IMPORT_C void HandlePointerEventL( const TPointerEvent& aPointerEvent );

protected: // From base class @c CCoeControl.

    /**
	* Handles a change to the control's resources of type @c aType
	* which are shared across the environment, e.g. color scheme change.
    * Responds fade events and fades incall status bubble window group.
    *
	* @param  aType  Event type.
	*/
   	IMPORT_C virtual void HandleResourceChange( TInt aType );

    /**
    * Handles size change events.
    */
    IMPORT_C virtual void SizeChanged();

    /**
    * Handles position change events.
    */
    IMPORT_C virtual void PositionChanged();

    /**
    * Returns number of controls inside the context pane control.
    *
    * @return Amount of component controls.
    */
    IMPORT_C virtual TInt CountComponentControls() const;

    /**
    * Returns a control determined by control index.
    *
    * @param  aIndex  Index of a control to be returned.
    * @return Pointer to control
    */
    IMPORT_C virtual CCoeControl* ComponentControl( TInt aIndex ) const;

private: // From base class @c CCoeControl.

    IMPORT_C virtual void Draw(const TRect& aRect) const;

private: // From base class @c CAknControl.

    IMPORT_C void* ExtensionInterface( TUid aInterface );

private:

    virtual void Reserved_1();
    void PrioritizeIndicatorsL();

   	static TInt TickerCallback( TAny* aThis );
    TInt DoTick();

    void IncallBubbleSizeChanged( TBool aAllowIdleStateBubble );

    void SizeChangedInSmallStatusPane();

    void SizeChangedInNormalStatusPane();

    void SizeChangedInStaconPane();

    void SizeChangedInFlatStatusPane();

    void SizeChangedInExtendedStatusPane();

    void SizeChangedInIdleExtendedStatusPane();

	void SizeChangedInIdleVertical();

    void SetContainerWindowNonFading( TBool aNonFading );

    void SetupIndicatorLayoutModes();

    TInt SelectIndicatorLayoutMode();

	void CreateIndicatorFromPaneResourceL( TUid aUid,
	                                       TInt aIndicatorPaneResourceId,
	                                       TInt aCustomIndicatorFlags );

	TBool IndicatorExists( TUid aUid ) const;

	void CreateIncallBubbleL();

	TBool UpdateSmallLayoutL();

	void SetIncallBubbleDisabled( TBool aDisabled );

	void ResetAnimTicker( TBool bForeground );

public:

    /**
    * Sets value to the progress bar indicator
    * (@c EAknNaviPaneEditorIndicatorProgressBar).
    * Panics if the specified indicator is not a progress bar indicator.
    *
    * @since 2.1
    * @param  aIndicatorId  ID of the indicator to be modified.
    * @param  aValue        Current progress of the task that bar describes.
    * @param  aMaxValue     Progress value when task is finished.
    *
    */
    IMPORT_C void SetIndicatorValue( TUid aIndicatorId,
                                     TInt aValue,
                                     TInt aMaxValue );

    /**
    * Redraws those indicators that are visible and contain pictographs.
    */
    void DrawPictographArea();

    /**
    * Returns the pictograph interface owned by the indicator container,
    * or @c NULL if pictographs are not supported.
    */
    CAknPictographInterface* PictographInterface() const;


    /**
    * Sets whether incall bubble is shown also on the top of the idle
    * status pane. Normally it is shown only in usual statuspane layouts,
    * but with this method it can be set to shown also in idle.
    *
    * NOTE: This method works only if indicatorcontainer is used as container
    *       for universal indicators.
    *
    * @param  aAllowed  If true incall bubble is shown also in idle statuspane.
    *                   Otherwise bubble is shown only in usual statuspane
    *                   layouts.
    */
    IMPORT_C void SetIncallBubbleAllowedInIdle( TBool aAllowed );

    /**
    * Sets whether incall bubble is shown on the top of the usual status pane.
    * Normally it is shown in usual statuspane layouts, but with this
    * method it can prevent it to be shown.
    *
    * NOTE: This method works only if indicatorcontainer is used as
    *       container for universal indicators.
    *
    * @param  aAllowed  If true incall bubble is shown in usual statuspane.
    */
    IMPORT_C void SetIncallBubbleAllowedInUsual( TBool aAllowed );


    /**
    * Sets observer for given indicator.
    *
    * @param  aIndicatorObserver  Observer of the indicator.
    * @param  aIndicatorUid       UID of indicator to be observed.
    */
    IMPORT_C void SetIndicatorObserver( MAknIndicatorObserver* aIndicatorObserver,
                                        TUid aIndicatorUid );

    /**
    * Creates a custom indicator.
    * Indicators created with this method can be used in addition
    * to default indicators.
    *
    * @since 3.1
    *
    * @param  aIndicatorResourceId   Resource ID of INDICATOR struct to be used
    *                                in costructing indicator.
    *        	                     UID in the resource is ignored, a dynamic
    *                                UID is given to indicator and returned
    *                                to caller.
    * @param  aCustomIndicatorFlags  Flags that can be used to set additional
    *                                indicator properties.
    *                                  - @c EMultiColorIndicator:
    *                                       Indicator is shown as multicolor
    *                                       (default is 2-color).
    *                                  - @c EIndicatorPositionInverted:
    *                                       Indicator is aligned to the opposite
    *                                       side than default (default is right
    *                                       side). Note that this flag does not
    *                                       quarantee exact location for the
    *                                       indicator, indicators are shown in
    *                                       priority order and location may vary
    *                                       and look different in different layouts.
    *
    * @return UID of the new indicator.
    *
    */
	IMPORT_C TUid CreateIndicatorFromResourceL( TInt aIndicatorResourceId,
	                                            TInt aCustomIndicatorFlags );


    /**
    * Replaces the icon of the given indicator.
    *
    * @since 3.1
    * @param  aIndicator   UID of the indicator.
    * @param  aState       State which icon is replaced (@c EAknIndicatorStateOn
    *                      or @c EAknIndicatorStateAnimate)
    * @param  aLayoutMode  Layout mode of the icon to be replaced
    *                      (@c ELayoutModeUsual or @c ELayoutModeWide)
    * @param  aIconBitmap  Bitmap of the new icon. Ownership is transferred to
    *                      @c CAknIndicatorContainer.
    * @param  aIconMask    Mask of the new icon. Ownership is transferred to
    *                      @c CAknIndicatorContainer.
    * @param  aIconIndex   If parameter aState is @c EAknIndicatorStateAnimate,
    *                      then this parameter must contain the index of the
    *                      icon to be replaced in the animation sequence.
    *                      Old icon must exist for given index so that the
    *                      number of animation frames does not change.
    */
	IMPORT_C void ReplaceIndicatorIconL( TUid aIndicator,
	                                     TInt aState,
	                                     TInt aLayoutMode,
	                                     CFbsBitmap* aIconBitmap,
	                                     CFbsBitmap* aIconMask,
	                                     TInt aIconIndex = 0 );

private:

    /** Array of the indicators. */
   	typedef CArrayPtrFlat<CAknIndicator> CAknIndicatorQueue;
    CAknIndicatorQueue* iIndicators;

    /** Layout orientations. */
    TLayoutOrientation iLayoutOrientation;
    TLayoutOrientation iPreviousLayoutOrientation;

    /** Alignment of the indicators. */
    TIndicatorAlignment iAlignment;

    /** Number of indicators shown. */
    TInt iIndicatorsShown;

    /** Number of animated indicators shown. */
    TInt iAnimatedIndicatorsShown;

    /** Extension class. */
    CAknIndicatorContainerExtension* iExtension;

    /** Context of the indicators. */
    TInt iIndicatorContext;

    /** Indicator animation timer. */
   	CPeriodic* iTicker;

   	/** Reserved for future use. */
    TBool iSpare2;

    /** Synchronization value used in the indicator animations. */
    TInt iSynchronizingValue;

    /** Small incall status bubble. */
    CIncallStatusBubble* iIncallBubble;
    };

#endif // AKNINDICATORCONTAINER_H

// End of File
