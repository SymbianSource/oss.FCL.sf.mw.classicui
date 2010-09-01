/*
* Copyright (c) 2005-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Slider editor class
*
*/


#ifndef __AKNSLIDER_H__
#define __AKNSLIDER_H__

// INCLUDES
#include <eikbctrl.h>
#include <eiklabel.h>
#include <eikimage.h>
#include <avkon.hrh> // For TAknOrientation

// CONSTANTS

// The following is max. length of the entire formatted value text including
// number, special characters and supplied text.
const TInt KValueLabelTextMaxLength = 30;

// Forward declarations
class CGulIcon;
class MAknsSkinInstance;
class CAknSliderExtension;
class CAknSliderData;
struct TAknSliderGfx;

// CLASS DECLARATION
class CAknSlider : public CEikBorderedControl
    {
public: // Enumerations
    /**
    * Elements that currently support custom graphics.
    *
    * @since 3.2
    */
    enum TSliderGfxElements
        {
        /**
        * Left cap component of the slider, without filling. Left cap equals
        * to bottom cap in vertical layout.
        */
        EElemEmptyLeftCap,

        /**
        * Right cap component of the slider, without filling. Right cap equals
        * to top cap in vertical layout.
        */
        EElemEmptyRightCap,
        
        /**
        * Line component of the slider, without filling.
        */
        EElemEmptyLine,
        
        /**
        * Line component of the slider, with filling.
        */
        EElemFilledLine,
        
        /**
        * Left cap component of the slider, with filling.
        */
        EElemFilledLeftCap,
        
        /**
        * Right cap component of the slider, with filling.
        */
        EElemFilledRightCap,
        
        /**
        * Marker component of the slider.
        */
        EElemMarker,
        
        /**
        * Tick mark component of the slider. Small evenly spaced lines,
        * placed vertically in relation to slider itself.
        */
        EElemTickMark,

        /**
        * Marker component of the slider when dragged
        */
        EElemMarkerSelected
        };

    /**
    * Supported slider position indicators.
    *
    * @since 3.2
    */
    enum
        {
        /**
        * Flag for enabling/disabling line filling. With line filling different
        * graphics will be used for the the slider line's left and right sides
        * (the current marker position as pivot). The left side is considered
        * filled line and the right side empty line.
        *
        * When line filling is enabled the graphics element @c EElemFilledLine
        * is used for the left side and @c EElemEmptyLine for the right. If
        * line filling is disabled @c EElemEmptyLine is used for the whole
        * line.
        */
        EPosFilling  = 0x01,
        /**
        * Flag for enabling/disabling line marker (the knob). While disabled
        * marker is not visible, the marker area will still be used for touch
        * input.
        */
        EPosMarker   = 0x02            
        };

    /**
    * Event for slider thumb/marker dragging.
    *
    * @since 5.0
    */
    enum
        {
        /**
        * Slider thumb/marker drag start
        */
        EDragMarkerStart  = 1000,
        /**
        * Slider thumb/marker drag end
        */
        EDragMarkerEnd
        };
        
public:
    /**
    * Default Constructor.
    */
    IMPORT_C CAknSlider();

    /**
    * Destructor.
    */
    IMPORT_C ~CAknSlider();

    /**
    * Sets the value of the slider control and also updates the iValueLabel
    * text. There are the following constraints on the value:
    *    it must be within the current range,
    *    it must be at a value that is minimum + N * stepsize.
    * If these are not both true, then the method will Panic
    *
    * @param aValue Sets the value of the slider.
    */
    IMPORT_C void SetValueL( TInt aValue );

    /**
    * Returns the value of the slider control
    *
    * @return Slider value.
    */
    IMPORT_C TInt Value() const;

    /**
    * Sets the range of the slider control. Maximum value must be greater than
    * the minimum value, or the method will Panic.
    *
    * @param aMinimumValue The minimum value of the slider control
    * @param aMaximumValue The maximum value of the slider control
    */
    IMPORT_C void SetRange( TInt aMinimumValue, TInt aMaximumValue );

    /**
    * Gets the range of the slider control. Maximum value must be greater than
    * the minimum value, or the method will Panic.
    *
    * @since 3.2
    * @param aMinimumValue The minimum value of the slider control
    * @param aMaximumValue The maximum value of the slider control
    */
    IMPORT_C void GetRange( TInt& aMinimumValue, TInt& aMaximumValue );
    
    /**
    * Sets the step size. The step size must divide evenly into the Range. This
    * routine should be called after SetRange if either is called.
    *
    * @param aStepSize The value of the step size
    */
    IMPORT_C void SetStepSize( TInt aStepSize );

    /**
    * Sets the text to the minimum label.
    *
    * @param aText The text passed is set to the minimum label
    */
    IMPORT_C void SetMinimumTextL( const TDesC& aText );

    /**
    * Sets the text to the maximum label.
    *
    * @param aText The text passed is set to the maximum label
    */
    IMPORT_C void SetMaximumTextL( const TDesC& aText );

    /**
    * Sets the value of decimal places. The legal range is 0 - 9 inclusive.
    *
    * @param aDecimalPlaces The value of the decimal place
    */
    IMPORT_C void SetDecimalPlaces( TInt aDecimalPlaces );

    /**
    * Returns the value of decimal place.
    *
    * @return the value of decimal place.
    */
    IMPORT_C TInt DecimalPlaces() const;

    /**
    * Allows setting custom graphics for a certain slider element. Existing
    * icons (custom or default) for the element are discarded. Note that some
    * elements might not be visible until the corresponding functionality is
    * enabled, see @c SetPositionIndicators and @c SetTicksEnabled.
    *
    * Slider takes care of scaling the given icons to the correct size,
    * provided that they have been created with @c AknIconUtils or @c AknsUtils
    * interfaces. It also handles re-scaling the icons if the slider layout
    * changes.
    *
    * If the custom icons are created by using skin items (e.g. using color
    * from skin), remember to change the icons whenever skin changes, see
    * @c CCoeControl::HandleResourceChange. In addition, note that slider can
    * be with horizontal or vertical layout, @see Orientation
    *
    * @param aElement The element ID to which the icons are assigned, one of
    *                 @c TGfxElements.
    *
    * @param aBitmap The icon used for the element, must be non-NULL,
    *                ownership is transferred to slider.
    *
    * @param aMask Optional mask for the aBitmap, can be NULL, ownership
    *              is transferred to slider.
    *
    * @par Exceptions:
    *   Will panic with EAknPanicInvalidValue if the element ID is invalid or
    *   aBitmap is NULL.
    *
    * @since 3.2
    */
    IMPORT_C void SetGraphics( TInt aElement,
                               CFbsBitmap* aBitmap,
                               CFbsBitmap* aMask );
    
    /**
    * Makes an element to use default graphics. Possible custom graphics for
    * the element is discarded.
    *
    * @param aElement The element ID which should use default graphics, one of
    *                 @c TGfxElements.
    *
    * @par Exceptions:
    *   Will panic with EAknPanicInvalidValue if the element index is invalid.
    *
    * @since 3.2
    */
    IMPORT_C void UseDefaultGraphics( TInt aElement );

    /**
    * Queries whether some element is using default graphics.
    *
    * @param aElement The element ID which should use default graphics, one of
    *                 @c TGfxElements.
    *
    * @return ETrue if default graphics is used for the element, EFalse
    *         otherwise (custom graphics used).
    *
    * @par Exceptions:
    *   Will panic with EAknPanicInvalidValue if the element index is invalid.
    *
    * @since 3.2
    */
    IMPORT_C TBool UsesDefaultGraphics( TInt aElement ) const;

    /**
    * Configures line position indicators, which display the slider's current
    * position. Possible indicators are defined in @c EPositionIndicator, at
    * least one of them must be defined (to display some position information).
    * Multiple values can be enabled by using bitwise or, e.g. @c EPosFilling |
    * EPosMarker. The new flags will fully override the old values. The default
    * value is @c EPosMarker.
    *
    * @param aFlags Bitmask containing flags from @c EPositionIndicator. At
    *               least one flag should be set.
    *
    * @par Exceptions:
    *   If none of the flags in @c EPositionIndicator is set, the code defaults
    *   silently to @c EPosMarker.
    *
    * @since 3.2
    */
    IMPORT_C void SetPositionIndicators( TUint32 aFlags );
    
   
    /**
    * Queries the current status of position indicators.
    *
    * @return Bitmask containing flags as defined in @c EPositionIndicator
    *
    * @since 3.2
    */
    IMPORT_C TUint32 PositionIndicators() const;

    /**
    * Queries the current orientation status.
    *
    * @return The current orientation, see @c TAknOrientation.
    *
    * @since 3.2
    */
    IMPORT_C TAknOrientation Orientation() const;

    /**
    * Enables/disables the tick marks. Tick marks are disabled by default.
    * Enabling tick marks affects only the visual appearance of slider. That is,
    * enabling slider step handling is not changed.
    *
    * @param aStatus ETrue to enable tick marks, EFalse to disable.
    *
    * @since 3.2
    */
    IMPORT_C void SetTicksEnabled( TBool aStatus );

    /**
    * Queries the current tick mark status.
    *
    * @return ETrue if tick marks are enabled, EFalse otherwise.
    *
    * @since 3.2
    */
    IMPORT_C TBool TicksEnabled() const;

    /**
    * Sets the tick interval used for drawing the tick marks. Tick interval is
    * in the slider range units (not in pixels). If interval value is set to 0,
    * the slider step size is used as tick interval, see @c SetStepSize. The
    * default interval value is 0.
    *
    * @param aInterval The value set as tick interval, always >= 0.
    *
    * @since 3.2
    */
    IMPORT_C void SetTickInterval( TUint aInterval );

    /**
    * Queries the current tick interval value.
    *
    * @return Current tick interval, always >= 0.
    *
    * @since 3.2
    */
    IMPORT_C TUint TickInterval() const;

    /**
    * Returns slider bitmap to "list pane for setting item" (setting option
    * item slider graphic). Ownership of the returned bitmap is transfered to
    * the caller.
    *
    * @param aValue Current value
    * @param aResourceId Slider resource that contains minimum and maximum
    *                    values
    * @return Slider bitmap. Ownership of the bitmap is transfered to the
    *         caller.
    */
    IMPORT_C static CFbsBitmap* CreateBitmapL( TInt aValue,
                                               TInt aResourceId );

    /**
    * Returns slider bitmap to "list pane for setting item" (setting option
    * item slider graphic). Ownership of the returned bitmap is transfered to
    * the caller.
    *
    * @param aValue Current value
    * @param aMinimumValue Slider minimum value
    * @param aMaximumValue Slider maximum value
    * @return Slider bitmap. Ownership of the bitmap is transfered to the
    *         caller
    */
    IMPORT_C static CFbsBitmap* CreateBitmapL( TInt aValue,
                                               TInt aMinimumValue,
                                               TInt aMaximumValue );

    /**
    * Returns slider icon to "list pane for setting item" (setting option item
    * slider graphic). Ownership of the returned icon is transfered to the
    * caller.
    *
    * @param aValue Current value
    * @param aResourceId Slider resource that contains minimum and maximum
    *                    values
    * @return Slider icon. Ownership of the icon is transfered to the caller
    */
    IMPORT_C static CGulIcon* CreateSetStyleListBoxIconL( TInt aValue,
                                                          TInt aResourceId );

    /**
    * Returns slider icon to "list pane for setting item" (setting option item
    * slider graphic). Ownership of the returned icon is transfered to the
    * caller.
    *
    * @param aValue Current value
    * @param aMinimumValue Slider minimum value
    * @param aMaximumValue Slider maximum value
    * @return Slider bitmap. Ownership of the icon is transfered to the caller
    */
    IMPORT_C static CGulIcon* CreateSetStyleListBoxIconL( TInt aValue,
                                                          TInt aMinimumValue,
                                                          TInt aMaximumValue );
    /**
    * Call CCoeControl::EnableDragEvents()
    *
    * @since 3.2
    */                                                      
    IMPORT_C void EnableDrag();

public:
    /**
    * From CCoeControl, returns the size of the control. And yes, this method
    * is non-const.
    *
    * @return size of the control
    */
    TSize MinimumSize();

    /**
    * From CCoeControl, Handles key event.
    *
    * @param aKeyEvent The key event.
    * @param aType The type of the event.
    * @return Indicates whether the key event was used by this control or not
    */
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent,
                                 TEventCode aType );

    /**
    * From CCoeControl, essential for Dialog/Form construction.
    *
    * @param aReader which reads the values specified in the resource file
    */
    IMPORT_C void ConstructFromResourceL( TResourceReader& aReader );

    /**
    * This function is used for constructing the control.
    *
    * @param aParent Pointer to the parent control.
    * @paran aValue Current value of the slider control.
    * @param aReader which reads the values specified in the resource file.
    */
    IMPORT_C void ConstructFromResourceL( CCoeControl* aParent,
                                          TInt aValue,
                                          TResourceReader& aReader );

    /**
    * This function toggles between edit and view modes
    *
    * @param aType Specifies the mode.
    */
    IMPORT_C void HandleResourceChange( TInt aType );

    /**
     * This function will be called when focus changed.
     *
     * @param aDrawNow if the control needs to call DrawNow().
     */
    IMPORT_C virtual void FocusChanged(TDrawNow aDrawNow);

public:
    /**
    * This function is used specifically in the forms. (For Forms/Dialogs to
    * use with LAF) Returns the number of lines on the control.
    *
    * @return Number of lines
    */
    IMPORT_C TInt NumberOfLines() const;

    /**
    * This routine can be used to combine the resource for a Slider with a
    * value to get the same value text that you would get if you had the
    * instantiated control
    *
    * @param aValue The value to format
    * @param aResourceId AKN_SLIDER resource id
    *
    * @return Transfer of ownership of descriptor containing the value text
    */
    IMPORT_C static HBufC* CreateValueTextInHBufCL( TInt aValue,
                                                    TInt aResourceId );
                                                    
    void SuppressDrawing( TBool aSuppress );

protected:
    /**
    * From CCoeControl, Called by framework when the view size is changed.
    */
    void SizeChanged();

    /**
    * From CCoeControl, Drawing function which draws the control
    *
    * @param aRect Specified area to be drawn
    */
    void Draw( const TRect& aRect ) const;

   /**
    * From CCoeControl, Returns number of components.
    *
    * @return Number of component controls
    */
    IMPORT_C virtual TInt CountComponentControls() const;

    /**
    * From CCoeControl, Returns pointer to particular component
    *
    * @param aIndex Index whose control's pointer has to returned.
    * @return Pointer to component control
    */
    IMPORT_C virtual CCoeControl* ComponentControl( TInt aIndex ) const;

public:
    /**
    * From CCoeControl. Handles pointer event
    *
    * @param aPointerEvent Pointer event to be handled
    */
    IMPORT_C void HandlePointerEventL( const TPointerEvent& aPointerEvent );
    TInt StepSize() const;

private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

protected:
    /**
    * Sets the text to the value label
    */
    IMPORT_C void SetValueTextL();

public:

    /**
    * Report event for thumb/marker dragging via HandleControlEventL
    *
    * @since 5.0
    */ 
    void ReportMarkerDragEvent( TBool aEnable );
    
private:
    /**
    * This function creates the bitmaps and labels. Also it sets the
    * container window for the labels.
    */
    void ConstructL();

    void InitializeBitmapsL();

    /**
    * static routine for setting the value text.
    * @param valueBuf Buffer to hold the result. Must be big enough to hold
    *   value label as formatted from the resources and value provided, though
    *   it is protected from overflow. Contained text will be truncated to
    *   KValueLabelTextMaxLength
    * @param aValue Slider value to format
    * @param aResourceData    resource Id to read from
    */
    static void DoSetValueTextL( TDes& valueBuf, TInt aValue,
                                 const CAknSliderData& aResourceData );
    
    /**
    * This method is used to trap all the accesses to the internal data. It
    * panics with EAknPanicObjectNotFullyConstructed if iData is not
    * constructed, that is, if 2nd stage construction has not taken place (or
    * has failed).
    */
    CAknSliderData* SliderData() const;

    /**
    * This class is a utility to protect StringLoader::Format from being
    * called without a formatting token.
    *
    * StringLoader is used in current implementation. See StringLoader::Format
    * for the semantics of the parameters.
    *
    * The other thing to note is that the output for descriptor must be able
    * to accept up to KValueLabelTextMaxLength characters.
    *
    * @param aOutput Output of format operation
    * @param aFormat Formatting descriptor.
    * @param aValue  Descriptor to substitute for the %U token potentially
    *                present in the formatting descriptor.
    */
    static void FormatWithOrWithoutTokenL( TDes& aOutput,
                                           const TDesC& aFormat,
                                           const TDesC& aValue );

    // layout methods
    void FormSliderLayout1();
    void FormSliderLayout2();
    void FormSliderLayout3();
    void SettingsItemSliderLayout();
    void VerticalSliderLayout();
    void HorizontalSliderLayout();
    void MIDPFormSliderLayout();
    
    void SetLabelColor();

   
    void CreateDecoratorImageFromResourceL( TInt aImageResourceId );

    // Internal access methods
    TInt Layout() const;
    TInt MaximumValue() const;
    TInt MinimumValue() const;
    TInt Range() const;

    // Starts a timer for feedback effect visualization.
    void StartTimerL();

    // Callback for feedback effect.
    static TInt IndicationDrawCallbackL( TAny* aThis );

    // Implementation of the feedback effect.
    void SmallDirectionIndicationL();

    void DrawHorizontalTickMarks( CWindowGc& aGc ) const;
    void DrawVerticalTickMarks( CWindowGc& aGc ) const;

    void TranslateValueL( TInt aDelta, TBool aFeedback = EFalse );

    void GetMarkerRect( TRect& aRect ) const;
    TSize MarkerSize() const;
    TPoint MarkerPos() const;

    void DrawHorizontal( TBool aDrawMarker ) const;
    void DrawVertical( TBool aDrawMarker ) const;

    void DrawHorizontalLine( CWindowGc& aGc ) const;
    void DrawVerticalLine( CWindowGc& aGc ) const;

    void FetchGfx( TAknSliderGfx& aGfx, TInt aElement, const TSize& aSize ) const;
    
    // calculate the correct value according to the input point
    TInt CalcAlignedValue( const TPoint& aPoint ); 

    void StartFeedback( const TPointerEvent* aPointerEvent, TTimeIntervalMicroSeconds32 aTimeout );
    void StopFeedback();
    void ModifyFeedback();
    TInt FeedbackIntensity();
        
    /**
     * Provides the touch active area for setting item slider.
     * 
     * @return Touch active area rect.
     */
    TRect TouchActiveArea() const;

private:
    CEikImage* iImage;
    CEikLabel* iValueLabel;
    CEikLabel* iMinLabel;
    CEikLabel* iMaxLabel;
    CFbsBitmap* iMarkerBmp;
    CFbsBitmap* iMarkerMaskBmp;
    TRect iMarkerArea;
    TRect iLineRect;
    TInt iValue;
    TBool iEditable;
    TRgb iColor;

    // Not used, kept for binary compatibility. Another pointer with same name
    // in iData is really used
    HBufC* iSingularText;

    CAknSliderData* iData;
    CAknSliderExtension* iExt;

    TInt iSpare[4];
};

#endif // __AKNSLIDER_H__

// End of File
