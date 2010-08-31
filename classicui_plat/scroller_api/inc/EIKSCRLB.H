/*
* Copyright (c) 1997-2006 Nokia Corporation and/or its subsidiary(-ies).
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

		
#if !defined(__EIKSCRLB_H__)
#define __EIKSCRLB_H__

#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>
#endif

#if !defined(__EIKSBOBS_H__)
#include <eiksbobs.h>
#endif

#if !defined(__AKNSCBUT_H__)
#include <aknscbut.h>
#endif

#include <lafpublc.h>

class CEikCba;
class CAknDoubleSpanScrollIndicator;
class CEikScrollBarExtensionImpl;
class CEikScrollBarExtension;
class CAknDoubleSpanScrollBarExtension;

const TInt KEikScrollEventFromVBar=0;
const TInt KEikScrollEventFromHBar=0x01;
const TInt KEikScrollEventBarMask=0x01;

// sets all bits in EButtonsXxx range
const TInt KButtonPositionMask=KLafScrollBarButtonPositionMask; 

// sets all bits in determining which components exist
const TInt KDisplayComponentsMask=0x1f; 


/**
 * Scroll bar models encapsulate the range of integers which a scroll bar can 
 * represent, from zero to n, and the current position of the scroll bar thumb
 * within that range.
 *
 * Supported from Symbian 5.0.
 */
class TEikScrollBarModel
    {
	
public:
	
    /**
     * C++ default constructor. Creates, allocates and initialises a new @c 
     * TEikScrollBarModel.
     */
    inline TEikScrollBarModel();

    /**
     * Constructor. Creates, allocates and initialises a new @c 
     * TEikScrollBarModel.
     *
     * @param aScrollSpan The span of this model, numbered from zero.
     * @param aThumbSpan Number of positions spanned by the thumb.In default
     *        this is zero.
     * @param aThumbPosition Position of the thumb within the model span. In
     *        default this is zero.
     */	
    IMPORT_C TEikScrollBarModel(TInt aScrollSpan,
                                TInt aThumbSpan=0,
                                TInt aThumbPosition=0);

    /**
     * Tests two models for equality. The two models are the current model and
     * the model specified by @c aModel.
     *
     * @param The model against which the current model is tested. 
     *
     * @return @c ETrue if the two models are equal.
     */	
    IMPORT_C TBool operator==(const TEikScrollBarModel aModel) const;

    /**
     * Tests two models for inequality. The two models are the current model 
     * and the model specified by @c aModel.
     *
     * @param The model against which the current model is tested. 
     * @return @c ETrue if the two models are not equal.
     */	
    inline TBool operator!=(const TEikScrollBarModel aModel) const; 

public:

    /** 
     * Tests whether the scroll bar model is useful. Scroll bar models are only
     * useful if their thumb span is smaller than their entire span.
     *
     * @return Whether this scroll bar can be used.
     */
    IMPORT_C TBool ScrollBarUseful() const;

    /**
     * Gets the maximum position possible for the low edge of the thumb within
     * the total span.
     *
     * @return Maximum value possible for @c iThumbPosition.
     */
    IMPORT_C TInt MaxThumbPos() const;

    /**
     * Ensures that the thumb position remains within its valid range by
     * altering it if necessary.
     */
    IMPORT_C void CheckBounds();

    /** 
     * Type of scroll bar model. The different models store the scrolling
     * information in different way, so correct model must be used with correct
     * scrollbar type.
     */
    enum TEikScrollBarModelType
        {

        /** This model type is for storing data for the arrowhead scrollbar. */
        EEikScrollBarModel               = 0x00000000,

        /** This model type is for storing data for the spanned scrollbar. */
        EAknDoubleSpanScrollBarModel     = 0x80000000
        };        

    /**
     * Gets type of scroll bar model which is one of the enum values from @c 
     * TEikScrollBarModelType enum.
     */
    TEikScrollBarModel::TEikScrollBarModelType ScrollBarModelType() const;

public:

    /** Entire range of integers for this model. */
    TInt iScrollSpan;

    /** Range spanned by the thumb. */
    TInt iThumbSpan;

    /** Position of the low edge of the thumb within 0...@c iScrollSpan. */
    TInt iThumbPosition;            
    };

inline TEikScrollBarModel::TEikScrollBarModel() {}
inline TBool TEikScrollBarModel::operator!=(const TEikScrollBarModel aModel) const { return !(*this==aModel); }


//
// TAknDoubleSpanScrollBarModel class
//
// This class is binary compatible with TEikScrollBarModel and can
// be used in places where TEikScrollBarModel is used but few restrictions exist:
//
// - Base class (TEikScrollBarModel) public members must NOT be accessed directly.
// - Base class (TEikScrollBarModel) public methods must NOT be called.
//
// If this model is not supported by the scrollbar system, then values are stored
// as in the base class for compatibility resons. See ModelIsSupported()-method 
// documentation for more information.
//
class TAknDoubleSpanScrollBarModel : public TEikScrollBarModel
	{

public:
    
   /**
    * Default constructor.
    */
    IMPORT_C TAknDoubleSpanScrollBarModel();

   /**
    * Constructor which converts TEikScrollBarModel into TAknDoubleSpanScrollBarModel.
    *
    * @since    2.6
    * @param    aEikModel a model that will be converted.
    * 
    * Allowed range for TEikScrollBarModel values is from 0x1FFF7FFF to -0x1FFF7FFF. 
    * Values outside the allowed range will be truncated to max or min value. 
    * Value will be internally  stored with 15 bit accuracy, this means 
    * that the actual stored value may differ from the value given as parameter.
    * 
    * Values will be converted as:
    * 
    * TEikScrollBarModel        TAknDoubleSpanScrollBarModel
    * ------------------        ----------------------------
    * iScrollSpan          ->    ScrollSpan
    * iThumbPosition       ->    FocusPosition
    * iThumbSpan           ->    WindowSize
    * 0                    ->    FieldPosition            
    * 0                    ->    FieldSize
    *
    *
    * Values will be internally  stored with 15 bit accuracy, this means that the 
    * actual stored value may differ from the value given inside parameter.
    *
    */
    IMPORT_C TAknDoubleSpanScrollBarModel(const TEikScrollBarModel& aEikModel);
    
    
   /**
    *  Set methods for model attributes. These MUST be used instead of setting
    *  base class model values directly.
    *
    *  @since    2.6
    *  @param    aValue Value to be stored. Allowed range 0x1FFF7FFF to -0x1FFF7FFF. 
    *                   Value outside the allowed range will be truncated to max
    *                   or min value. Value will be internally  stored with 
    *                   15 bit accuracy, this means that the actual stored value
    *                   may differ from the value given as parameter.
    *
    *                   This inaccuracy means that e.g. following can happen:
    *                       TInt value1 = 23456789;                   
    *                       TInt value2 = 0;                   
    *
    *                       model.SetScrollSpan(value1);
    *                       value2 = model.ScrollSpan();
    *                       if (value1 != value2)
    *                           {
    *                           // we can end up here !!!!  
    *                           }
    *
    */
    IMPORT_C void SetScrollSpan(TInt aValue);    // Size of the scrolled list. 
    IMPORT_C void SetFocusPosition(TInt aValue); // Position of the current field in the list.
    IMPORT_C void SetWindowSize(TInt aValue);    // Size of the visible part of the list. 
    IMPORT_C void SetFieldSize(TInt aValue);     // Size of the current field. (Optional double span)
    IMPORT_C void SetFieldPosition(TInt aValue); // Position inside the current field. (Optional double span)  
    
    
   /**
    *  Get methods for model attributes. These MUST be used instead of getting
    *  base class model values directly.
    *
    * @since    2.6
    * @return   Values from range 0x1FFF7FFF to -0x1FFF7FFF. 
    *           Values are internally  stored with 15 bit accuracy, this means that 
    *           the returned value may differ from the value which was set using the
    *           corresponding set method. Difference can be about 0x3FFF in the high
    *           end of the range.
    *
    */
    IMPORT_C TInt ScrollSpan() const;    // Size of the scrolled list.
    IMPORT_C TInt FocusPosition() const; // Position of the current field in the list.
    IMPORT_C TInt WindowSize() const;    // Size of the visible part of the list. 
    IMPORT_C TInt FieldSize() const;     // Size of the current field. (Optional double span)
    IMPORT_C TInt FieldPosition() const; // Position inside the current field. (Optional double span)


   /**
    * This method can be used to query if this model type is supported by the device. If model 
    * is not supported then this model and the behaviour of ALL methods defaults to TEikScrollBarModel 
    * behaviour with following rules:
    *
    * TAknDoubleSpanScrollBarModel              TEikScrollBarModel
    * ----------------------------              ------------------  
    * ScrollSpan methods                ->      iScrollSpan
    * FocusPosition methods             ->      iThumbPosition
    * WindowSize methods                ->      iThumbSize
    * FieldPosition methods             ->      N/A
    * FieldSize methods                 ->      N/A
    *
    * @since    2.6
    * @return   ETrue if this model is supported by the devices scrollbar system. Otherwise EFalse is
    *           returned.
    *
    */
    static TBool ModelIsSupported();

private:   
   /**
    * Gets the internal scale value. 
    *
    * @since    2.6
    * @return   Internal scaling value.
    *
    */
    TUint16 Scale() const;

   /**
    * Sets the internal scale value. 
    *
    * @since    2.6
    * @param    aScale  New internal scaling value.
    *
    */
    void SetScale(TUint16 aScale);    

private:   
   /**
    *  Get methods for model attributes values without scaling.
    *
    *  @since    2.6
    *  @return   Stored value without scaling. 
    *
    */
    TInt16 ScrollSpanValue() const;
    TInt16 FocusPositionValue() const;
    TInt16 FieldPositionValue() const;
    TInt16 FieldSizeValue() const;
    TInt16 WindowSizeValue() const;

   /**
    *  Set methods for model attributes values without scaling.
    *
    *  @since    2.6
    *  @param    aValue Value without scaling to be stored. 
    *
    */
    void SetScrollSpanValue(TInt16 aValue);
    void SetFocusPositionValue(TInt16 aValue);
    void SetFieldPositionValue(TInt16 aValue);
    void SetFieldSizeValue(TInt16 aValue);
    void SetWindowSizeValue(TInt16 aValue);

   /**
    *  Gets two lowest bytes from TInt and constructs TInt16 from those.
    *
    *  @since    2.6
    *  @param    aInt  Value from which the lowest bytes are extracted.     
    *  @return   TInt16 constructed from two lowest bytes.
    */
    TInt16 LowBytes(TInt aInt) const;

   /**
    *  Gets two highest bytes from TInt and constructs TInt16 from those.
    *
    *  @since    2.6
    *  @param    aInt  Value from which the highest bytes are extracted.     
    *  @return   TInt16 constructed from two highest bytes.
    */    
    TInt16 HighBytes(TInt aInt) const;
    
    
   /**
    *  Sets two lowest bytes of TInt.
    *
    *  @since    2.6
    *  @param    aInt    TInt of which the lowest bytes are set.     
    *  @param    aValue  Value for the lowest bytes.     
    */    
    void SetLowBytes(TInt& aInt, TInt16 aValue);

   /**
    *  Sets two highest bytes of TInt.
    *
    *  @since    2.6
    *  @param    aInt    TInt of which the highest bytes are set.     
    *  @param    aValue  Value for the highest bytes.     
    */        
    void SetHighBytes(TInt& aInt, TInt16 aValue);
    
    
   /**
    *  Constructs a scaled TInt16 value from given TInt value. Changes
    *  internal member variable values using ReScale()-method if needed.
    *
    *  @since    2.6
    *  @param    aNonScaledValue    Value which will be changed to scaled one.
    *  @return   Scaled value.
    */        
    TInt16 PrepareScaledValue(TInt aNonScaledValue);
    
   /**
    *  Changes the used scale value and updates all stored attribute values
    *  if needed.
    *
    *  @since    2.6
    *  @param    aNewScale    New value to be used scaling.
    *
    */        
    void ReScale(TUint16 aNewScale);
    
   /**
    *  Sets the scrollbar type.
    *
    *  @since    2.6
    *  @param    aModelType    Scrollbar type. Supported types are 
    *                          EEikScrollBarModel and EAknDoubleSpanScrollBarModel.
    *
    */        
    void SetScrollBarModelType(TEikScrollBarModelType aModelType);

   /**
    *  Checks if given parameter is between internal min and max values.
    *
    *  @since    2.6
    *  @param    aValue        Value to be checked.
    *  @return                 Checked value which will be between internal min 
    *                          and max values. 
    *
    */        
    TInt CheckMinMaxValue(TInt aValue);
    };


//
// CEikScrollBar
//

class CEikScrollThumb;
class CEikScrollBarFrame;
  
/**
 * The CEikScrollBar class implements a scroll bar. Scroll bars are used when
 * the contents of a view require a greater area than can be physically 
 * displayed. Scroll bars allow a user to move different parts of the content
 * into the view and to indicate what proportion of the total contents are 
 * visible at any one time.
 */
class CEikScrollBar : public CEikBorderedControl, public MCoeControlObserver
	{
friend class CEikScrollBarExtension;
friend class CAknDoubleSpanScrollBarExtension;
    
public:

    /** Scroll bar orientation. */
    enum TOrientation
        {
        /** Scroll bar is oriented vertically. */
        EVertical = SLafScrollBar::EVertical,

        /** Scroll bar is oriented horizontally. */
        EHorizontal = SLafScrollBar::EHorizontal
        };

    /** Type of the scroll bar.*/	
    enum TScrollBarType
        {
        /** Normal scrollbar. */		
        ENormalScrollBar =0x0,

        /** Used scrollbar type is an old one. (arrows in the CBA-area) */		
        EArrowHead =0x200,

        /** 
         * The created scrollbar is the current and commonly used in Series 60
         * platform, spanned scrollbar. (scrollable bar on the right side of
         *  the control, like in windows etc.).
         */		
        EDoubleSpan =0x400
        };

    /** 
     * Scroll bar initialisation flags. The default is for the scroll bar
     * to have both a shaft and a thumb. 
     */	
    enum TEikScrollBarFlags
    	{
    	/**  */	
    	EEikScrollBarDefaultBehaviour = 
    	    SLafScrollBar::EEikScrollBarDefaultBehaviour,

    	/** Does not display nudge buttons.*/	
    	EEikScrollBarNoNudgeButtons =
    	    SLafScrollBar::EEikScrollBarNoNudgeButtons,

    	/** Has buttons which move it a page at a time. */	
    	EEikScrollBarHasPageButtons =
    	    SLafScrollBar::EEikScrollBarHasPageButtons,	

    	/** Has buttons which move it its entire extent. */	
    	EEikScrollBarHasHomeEndButtons =
    	    SLafScrollBar::EEikScrollBarHasHomeEndButtons,

    	/** Central area is empty. */	
    	EEikScrollBarNoShaftOrThumb =
    	    SLafScrollBar::EEikScrollBarNoShaftOrThumb,	

    	/** Central area has no scroll thumb. */	
    	EEikScrollBarShaftButNoThumb =
    	    SLafScrollBar::EEikScrollBarShaftButNoThumb,	

    	/** Buttons are placed at the start of the bar. */	
    	EButtonsAtStartOfShaft =
    	    SLafScrollBar::EButtonsAtStartOfShaft,	

    	/** Buttons are placed at the end of the bar. */	
    	EButtonsAtEndOfShaft =
    	    SLafScrollBar::EButtonsAtEndOfShaft,			

    	/** 
    	 * Buttons are placed at either end of the bar @c
    	 * (EButtonsAtStartOfShaft | @c EButtonsAtEndOfShaft).
    	 */	
    	EButtonsEitherSideOfShaft =
    	    SLafScrollBar::EButtonsEitherSideOfShaft,

    	/** 
    	 * Buttons do not automatically dim when scroll bar is at its maximum
    	 * extent.
    	 */	
    	ENoAutoDimming =
    	    SLafScrollBar::ENoAutoDimming,
    	    
    	/** Enable the nudge buttons. */
    	EEnableNudgeButtons = 0x0200,
    	
    	/** Disable the expanded touch area. */
    	EDisableExpandedTouchArea = 0x0400
    	};

    /** Type of the scroll extension area.*/
     enum TScrollBarExtensionAreaType
        {
        /** Normal scrollbar extension area. */
        ENormalExpandedTouchArea,

        /** Scale scrollbar extension area. */
        EScaleExpandedTouchArea,

        /** none scrollbar extension area. */
        ENoExpandedTouchArea
        };

    typedef TEikScrollBarFlags TAknScrollBarFlags;

public:

    /**
     * Destructor.
     */
    IMPORT_C ~CEikScrollBar();

    /**
     * C++ default constructor.
     */	
    IMPORT_C CEikScrollBar();

public:

    /** 
     * Second phase constructor of the scroll bar. 
     *
     * @param aScrollBarObserver The scroll bar observer which is to be 
     *        informed of scroll events by this scroll bar. 
     * @param aParent Parent control for this new scroll bar. 
     * @param aOrientation Orientation of the new scroll bar. 
     * @param aLength Not used. 
     * @param aScrollBarFlags Not used. 
     */
    IMPORT_C virtual void ConstructL(
                MEikScrollBarObserver* aScrollBarObserver,
                const CCoeControl* aParent,
                TOrientation aOrientation,
                TInt aLength,
                TInt aScrollBarFlags=EEikScrollBarDefaultBehaviour);

    /** 
     * Not implemented.
     * 
     * @param aLength Not used.
     */
    IMPORT_C void SetLengthL(TInt aLength);

    /** 
     * Change the scrollbar model.
     * 
     * @param aModel The new model to use.
     */
    IMPORT_C void SetModelL(const TEikScrollBarModel* aModel);

    /** 
     * Change the scrollbar model.
     * 
     * @param aModel The new model to use.
     */
    IMPORT_C void SetModel(const TEikScrollBarModel* aModel);

    /** 
     * Change the model at once to avoid a double update of the scroll bar.
     * 
     * @param aLength Not used. 
     * @param aModel New scroll bar model.
     */
    IMPORT_C void SetLengthAndModelL(TInt aLength,
                                     const TEikScrollBarModel* aModel);

    /** 
     * Not implemented.
     * 
     * @param aThumbPos Not used.
     */
    IMPORT_C void SetModelThumbPosition(TInt aThumbPos);

    /** 
     * Not implemented.
     * 
     * @param aFocusPosition Not used.
     */
    IMPORT_C void SetFocusPosToThumbPos(TInt aFocusPosition);

    /** 
     * Gets the default width of the scroll bar.
     * 
     * @return Default scroll bar breadth.
     */
    IMPORT_C static TInt DefaultScrollBarBreadth();

    /**
     * Allows scroll bar observer to be changed also after the construction. 
     * This function is not exported, but the applications can use it via
     * @c CEikScrollBarFrame::SetScrollBarFrameObserver function.
     *
     * @param aScrollBarObserver New observer replacing the previous (if any).
     */
    void SetScrollBarObserver(MEikScrollBarObserver* aScrollBarObserver);

    /**
     * Gets the scroll bar model used by this scroll bar.
     */
    inline const TEikScrollBarModel* Model() const;

    /** 
     * Gets the position within the scroll bar model. This function would
     * normally be called by an @c MEikScrollBarObserver implementation in 
     * response to a scroll bar event.
     * 
     * @return Current position within the scroll bar model’s range.
     */
    IMPORT_C TInt ThumbPosition() const;

    /** 
     * Gets the height of a horizontal scrollbar or width of a vertical 
     * scrollbar.
     * 
     * @return Scroll bar breadth.
     */
    IMPORT_C TInt ScrollBarBreadth() const;

    /** 
     * Not implemented.
     * 
     * @param aScrollBarFlags Not used.
     *
     * @return Zero.
     */
    IMPORT_C static TInt MinVisibleLength(const TInt aScrollBarFlags);

    /** 
     * Not implemented.
     * 
     * @param aDimmed Not used.
     */
    IMPORT_C void SetDecreaseButtonsDimmed(TBool aDimmed);

    /** 
     * Not implemented.
     * 
     * @param aDimmed Not used.
     */
    IMPORT_C void SetIncreaseButtonsDimmed(TBool aDimmed);

    /** 
     * Not implemented.
     * 
     * @param aDimmed Not used.
     */
    IMPORT_C void SetAllButtonsDimmed(TBool aDimmed);

    /** 
     * Gets handle to the controls that draw arrows in the both ends of spanned
     * scrollbar. These arrows are for pen support to enable exact moving of
     * the scrollbar with pen. The arrow is tapped with the pen to move the
     * scrollbar with one step.
     *
     * @return Pointer to the increace button.
     */
    inline CAknScrollButton* IncreaseNudgeButton() const;
    	
    /** 
     * Gets handle to the controls that draw arrows in the both ends of spanned
     * scrollbar. These arrows are for pen support to enable exact moving of
     * the scrollbar with pen. The arrow is tapped with the pen to move the
     * scrollbar with one step.
     *
     * @return Pointer to the decreace button.
     */
    inline CAknScrollButton* DecreaseNudgeButton() const;

    // This function should only be used by CEikCba
    /** 
     * Sets command button area. This function should only be used by @c 
     * CEikCba.
     * 
     * @param aCba Command button area.
     * @panic EEikPanicScrollBarExtensionNotCreated Extension of 
     *        the scroll bar not created.
     */
    IMPORT_C void SetContainingCba(CEikCba* aCba);

    /** 
     * From @c CCoeControl.
     *
     * Sets this control as visible or invisible.
     * 
     * If @c MakeVisible() is used to make a component visible, and the control
     * captures the pointer (see @c CapturesPointer()), @c MakeVisible() throws
     * away any pending pointer events for that control.
     * 
     * @param aVisible @c ETrue to make the control visible, @c EFalse to make 
     *        it invisible.
     */
    IMPORT_C void MakeVisible(TBool aVisible);

    // 
    /** 
     * From @c CCoeControl
     *
     * Called by the framework to handle pointer events. 
     * 
     * @param aPointerEvent A pointer event.
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

    /**
     * Not implemented.
     *
     * @param aType The extension area to use.
     */

    IMPORT_C void SetExtensionAreaType(TScrollBarExtensionAreaType aType);
protected:      

    /** 
     * From @c CCoeControl
     *
     * Gets the specified scrollbar component. Each component control is 
     * identified by an index, where the index depends on the order the 
     * controls were added: the first is given an index of 0, the next an index
     * of 1.
     * 
     * @param aIndex The index of the control to get.
     *
     * @return The component control with an index of aIndex.
     */
    IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;

    /** 
     * From @cCCoeControl.
     *
     * Gets the number of controls contained in this scrollbar.
     * 
     * @return The number of component controls contained by this scrollbar.
     */
    IMPORT_C TInt CountComponentControls() const;

private: // from MCoeControlObserver
    IMPORT_C virtual void HandleControlEventL(CCoeControl* aControl, 
                                              TCoeEvent aEventType);
private: // virtual - reserved from CCoeControl
    IMPORT_C virtual void Reserved_2();
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

protected:

    /**
     * The scroll bar frame is a control assemblage manager that relates a 
     * control, or control body, to two scroll bars and a corner window. A 
     * corner window is that part of the screen that is common to both the 
     * horizontal, and the vertical elements of a scroll bar.
     *
     * This class helps with access to, and set up of, scroll bars and also
     * with the layout of the scrolled control or control body. A scroll bar
     * frame is not a control, but it does implement the standard control 
     * composite pattern to manage the assemblage.
     */
    friend class CEikScrollBarFrame;

    // enums
    /** 
     * Flags to determine whether there are visible components and whether to
     * dim the increase, or decrease, buttons.
     */
    enum TPrivateScrollBarFlags
        {

        /** There are no visible components in the scroll bar. */
        ENoComponentsToDisplay          =0x10000,

        /** Dim the increase buttons. */
        EIncreaseButtonsDimmed          =0x20000,

        /** Dim the decrease buttons. */
        EDecreaseButtonsDimmed          =0x40000
        };

    /** Determines where on a scroll bar a pointer down event occurred. */
    enum TPointerDownOn
        {
        /** No pointer down event occurred on the scroll bar. */
        ENone,

        /** A pointer down event occurred on the home button. */
        EHomeButton,

        /** A pointer down event occurred on the decrease page button. */
        EDecreasePageButton,

        /** A pointer down event occurred on the decrease nudge button. */
        EDecreaseNudgeButton,

        /** A pointer down event occurred on the decrease shaft button. */
        EDecreaseShaft,

        /** A pointer down event occurred on the scroll bar thumb. */
        EThumb,

        /** A pointer down event occurred on the increase shaft button. */
        EIncreaseShaft,

        /** A pointer down event occurred on the increase nudge button. */
        EIncreaseNudgeButton,

        /** A pointer down event occurred on the increase page button. */
        EIncreasePageButton,

        /** A pointer down event occurred on the end button. */
        EEndButton
        };

    /** Determines whether to redraw the scroll bar shaft. */
    enum TShaftRedrawRequired
        {
        /** Do not redraw the scroll bar shaft. */
        ENoRedrawRequired,

        /** Redraw the scroll bar shaft. */
        ERedrawShaft
        };

    /** Determines which buttons are displayed. */
    enum TWhichButtons
        {
        /** Display the increase buttons only. */
        EIncreaseOnly,

        /** Display the decrease buttons only. */
        EDecreaseOnly,

        /** Display all buttons. */
        EAll
        };

    /** 
     * Encapsulates pointers to the scroll bar buttons. A maximum of three 
     * pairs of buttons are available, you may choose to use only one pair or
     * two pairs.
     */
    struct SEikScrollBarButtons
        {
        /** Pointer to the decrease nudge button. */
        CAknScrollButton* iDecreaseNudge;

        /** Pointer to the increase nudge button. */
        CAknScrollButton* iIncreaseNudge;
        };


private:
    // construction/destruction
    IMPORT_C virtual void CreateButtonL(CAknScrollButton*& aButton,
                                        CAknScrollButton::TType aType);

    void SizeChanged();

    // set state functions
    void DoSetModel(const TEikScrollBarModel* aModel);

    CEikCba* Cba() const;

    // These functions are for use only be CEikScrollBarFrame (a friend class)
    void AddExternalFrameL(CEikScrollBarFrame* aFrame);
    void RemoveExternalFrame(CEikScrollBarFrame* aFrame);

    void DisconnectExternalFrames();

protected:

    /** 
     * Allocates and constructs all the required components of the scrollbar.
     */
    void CreateRequiredComponentsL();

    /** 
     * Destroys a button.
     *
     * @param aButton A button that will be destroyed.
     */
    void DestroyButton(CAknScrollButton*& aButton);

    /** 
     * Not implemented 
     * 
     * @param aButton Not used. 
     */
    IMPORT_C virtual void SetButtonPositionL(CAknScrollButton* aButton);

public:

    /** 
     * Gets the scroll bar type.
     * 
     * @return Value of the enum @c TScrollBarType.
     */
    TScrollBarType ScrollBarType();

public:

    /** Not used, but cannot be removed due binary compatibility issues. */
    TDblQueLink iSBLink;

protected:

    /** Scroll bar buttons struct. */
    SEikScrollBarButtons iButtons;

    /** Scroll bar orientation. */
    TOrientation iOrientation;

private:
    TEikScrollBarModel iModel;

protected:    

    /** A pointer to @c CEikScrollBarExtensionImpl class. */
    CEikScrollBarExtensionImpl* iExtension;
  };


/**
 * The CEikArrowHeadScrollBar class is a scroll bar which uses only
 * two small nudge button arrows to scroll up and down. It has no shaft.
 * It therefore takes up very little space.
 *
 * @since ER5U 
 * @ internal
 * Internal to Symbian
 *
 */
class CEikArrowHeadScrollBar : public CEikScrollBar
	{
public:
	IMPORT_C CEikArrowHeadScrollBar(CCoeControl* aParentWindow);
	IMPORT_C ~CEikArrowHeadScrollBar();
public: // from CEikScrollBar
	IMPORT_C void ConstructL(MEikScrollBarObserver* aScrollBarObserver,const CCoeControl* aParent,
				TOrientation aOrientation,TInt aLength,TInt aScrollBarFlags=EEikScrollBarDefaultBehaviour);
public: // From CCoeControl
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);	
private: // from CEikScrollBar
	void CreateButtonL(CAknScrollButton*& aButton,CAknScrollButton::TType aType);
	void SetButtonPositionL(CAknScrollButton* aButton);
private:
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private:
	CCoeControl* iParentControl;
    TInt iSpare;
	};


/**
 * The CAknDoubleSpanScrollBar class is a scroll bar without buttons, 
 * but it has a shaft. Additionally it has in its shaft a double 
 * span feature which means that there can be another thumb inside the thumb 
 * if needed.
 *
 * This class uses TAknDoubleSpanScrollBarModel instead of TEikScrollBarModel
 * as its internal scrollbar model. TAknDoubleSpanScrollBarModel in binary 
 * compatible with TEikScrollBarModel. User must take care that TAknDoubleSpanScrollBarModel 
 * is really used in API calls in places where TEikScrollBarModel is declared.
 * 
 * @since 2.6 
 *
 */
class CAknDoubleSpanScrollBar : public CEikScrollBar
	{
public:
	IMPORT_C CAknDoubleSpanScrollBar(CCoeControl* aParentWindow);
	IMPORT_C ~CAknDoubleSpanScrollBar();

   /**
    * Sets fixed layout to scrollbar. If set, then scrollbar size
    * changes done by the CEikScrollBarFrame class are disabled. 
    *
    * @since    2.6
    * @param    aScrollBarRect     Scrollbar rectangle.         
    *
    */     
    IMPORT_C void SetFixedLayoutRect(TRect aScrollBarRect);

   /**
    * Method for constructing the object.
    *
    * @since    2.6
    * @param    aWindowOwning       True if scrollbar is to be a window owning control. 
    * @param    aScrollBarObserver  Same as in CEikScrollBar::ConstructL()
    * @param    aParent             Same as in CEikScrollBar::ConstructL()
    * @param    aOrientation        Same as in CEikScrollBar::ConstructL()
    * @param    aLength             Same as in CEikScrollBar::ConstructL()    
    * @param    aScrollBarFlags     Same as in CEikScrollBar::ConstructL()
    *
    */     
    IMPORT_C void ConstructL(TBool aWindowOwning, MEikScrollBarObserver* aScrollBarObserver,const CCoeControl* aParent,
				TOrientation aOrientation,TInt aLength,TInt aScrollBarFlags=EEikScrollBarDefaultBehaviour);

   /**
    * Sets scroll popup info text to be shown while dragging with stylus.
    * Popup is shown until next pointer up event.
    * KNullDesC parameter can be used to hide popup earlier.
    * 
    * @since    3.2
    * @param    aText               Text to be shown
    *
    */  
    IMPORT_C void SetScrollPopupInfoTextL( const TDesC& aText );

   /**
    * Gets the fixed layoutrect of the scrollbar.    
    * @since    2.6
    * @return   Scrollbar rectangle. 
    *
    */     
    TRect FixedLayoutRect();

public: // from CEikScrollBar
	IMPORT_C void ConstructL(MEikScrollBarObserver* aScrollBarObserver,const CCoeControl* aParent,
				TOrientation aOrientation,TInt aLength,TInt aScrollBarFlags=EEikScrollBarDefaultBehaviour);
    IMPORT_C void MakeVisible(TBool aVisible);

public: // from CCoeControl
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);    

protected: // from CCoeControl
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
    IMPORT_C TInt CountComponentControls() const;

private:  // from CCoeControl
    IMPORT_C void SizeChanged();
    
public:
	
	TBool DrawBackgroundState();
	
	void DrawBackground(TBool aDrawHorizontal);
	
    /**
     * Resets pressed down highlight so that default highlight is used when
     * the scrollbar is drawn.
     *
     * @since S60 5.2
     */
    void ResetPressedDownHighlight();
	
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private: // from CEikScrollBar
	void CreateButtonL(CAknScrollButton*& aButton,CAknScrollButton::TType aType);
	void SetButtonPositionL(CAknScrollButton* aButton);

   /**
    * Sets scrollbar background transparency as given in the parameter.
    * 
    * @param    aTransparentBackground   If ETrue then scrollbar will have transparent background.
    * @since    2.6
    *
    */     
    void SetTransparentBackground(TBool aTransparentBackground);

    /**
    * Calculates scrollbar's extension area relative to its own position.
    */
    TRect ExtensionArea() const;
private:
	CCoeControl* iParentControl;
    TInt iSpare;
	};


//
// Inlines
//


inline const TEikScrollBarModel* CEikScrollBar::Model() const
	{ return &iModel; }

inline CAknScrollButton* CEikScrollBar::IncreaseNudgeButton() const
	{ return iButtons.iIncreaseNudge; }

inline CAknScrollButton* CEikScrollBar::DecreaseNudgeButton() const
	{ return iButtons.iDecreaseNudge; }


#endif
