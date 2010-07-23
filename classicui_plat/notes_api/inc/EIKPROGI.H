/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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


#if !defined(__EIKPROGI_H__)
#define __EIKPROGI_H__

#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>
#endif

#if !defined(__EIKON_HRH__)
#include <eikon.hrh>
#endif

class TGulBorder;
class CEikProgressInfoExtension;

/**
* Control used to indicate the progress of an operation.
*
* Progress consists of a rectangular block that grows during an increment and 
* shrinks during a decrement. The control can have progress text within the bar 
* that provides updated information on how far the operation has progressed. 
* The text can be displayed as either a percentage or a fraction. The bar can 
* also have a series of invisible splits, or lines. These splits are displayed 
* by the rectangular blocks as it fills the bar. When the control is in this 
* mode progress text cannot be used. 
*
* This class has an associated @c PROGRESSINFO resource and @c EEikCtProgInfo 
* control factory identifier.
*/
class CEikProgressInfo : public CEikBorderedControl
	{
	
public:
    
    /**
     * Defines the progress control's type.
     */
    struct SInfo
        {
        /**
         * The type of text for the progress information control. This can be 
         * percentage or fraction. See the @c TEikProgressTextType enum.
         */
        TEikProgressTextType iTextType;

        /** 
         * The total number of splits in the progress information control. This
         * is optional.
         */
        TInt iSplitsInBlock;

        /** 
         * The final value of the progress information control that, when 
         * reached, indicates completion.
         */
        TInt iFinalValue;

        /** The width of the control in pixels. */
        TInt iWidth;
    
        /** The height of the progress information control. */
        TInt iHeight;
        };

    /**
     * Defines the layout and colours for a progress information control.
     */
    struct SLayout
        {
        /** 
         * The colour for the part of the control that indicates the progress
         * that has been made. By default, the value of the @c TLogicalColor 
         * enum's @c EColorControlHighlightBackground datum.
         */
        TRgb iFillColor;

        /**
         * The colour for sections of the control that indicate the progress yet
         * to be made. By default, the value of the @c TLogicalColor enum's 
         * @c EColorControlBackground datum.
         */
        TRgb iEmptyColor;

        /**
         * The colour for the optional progress text that is displayed i.e. 
         * the filled portion of the control. By default, the value of the 
         * @c TLogicalColor enum's @c EColorControlHighlightText datum.
         */
        TRgb iFillTextColor;

        /**
         * Optional progress text that appears in the empty portion of the 
         * control. By default, the value of the @c TLogicalColor enum's 
         * @c EColorControlText datum.
         */
        TRgb iEmptyTextColor;

        /**
         * The font to use for the optional progress text. By default, the 
         * environment's normal font.
         */
        const CFont* iFont;

        /**
         * The gap between the blocks in the control that indicate the progress 
         * made. By default, one pixel.
         */
        TInt iGapBetweenBlocks;
        };

    /**
     * Destructor.
     */
    IMPORT_C ~CEikProgressInfo();
    
    /** 
     * C++ default constructor.
     */
    IMPORT_C CEikProgressInfo();
    
    /**
     * Constructs a progress information control using the information held in 
     * the specified @c SInfo struct. Uses default layout values.
     *
     * @param aProgInfo Holds information about the type of progress 
     *        information control.
     */
    IMPORT_C CEikProgressInfo(const SInfo& aProgInfo);
    
    /**
     * Adds the specified increment to the current progress value and, if the 
     * progress value has increased, redraws the control.
     *
     * @param aInc The increment to add to the current progress value.
     */
    IMPORT_C void IncrementAndDraw(TInt aInc);
    
    /**
     * Sets the specified value as the new progress value and redraws the 
     * control if the new value differs from the old value.
     *
     * @param aValue The new progress value.
     */
    IMPORT_C void SetAndDraw(TInt aValue);
    
    /**
     * From @c CCoeControl.
     *
     * Constructs a progress information control from a @c PROGRESSINFO 
     * resource. Uses default layout values.
     * 
     * @param aReader The resource reader to use.
     */
    IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
    
    /**
     * Sets the layout for the control.
     *
     * @param aLayout The layout for the control.
     */
    IMPORT_C void SetLayout(const SLayout& aLayout);
    
    /**
     * Sets the control's border.
     *
     * @param aBorder The control's border.
     */
    IMPORT_C void SetBorder(const TGulBorder& aBorder);
    
    /**
     * Sets the final value for the progress information control. This value 
     * indicates the operation being monitored is complete.
     *
     * @param aFinalValue The final value for the progress information control.
     *        If this is specified as zero, the value is set to one.
     */
    IMPORT_C void SetFinalValue(TInt aFinalValue);
    
    /**
     * By default Symbian 2nd phase constructor is private.
     */
    IMPORT_C void ConstructL(); // AKNLAF

    /**
     * Gets a pointer to the information used to define the progress information
     * control's type.
     *
     * @return The information that defines the type of progress 
     *         information control.
     */
    inline const SInfo& Info() const { return(iInfo); }
    
    /**
     * Gets a pointer to the colours and layout of the progress information 
     * control.
     *
     * @return Defines the layout of the control.
     */
    inline const SLayout& Layout() const { return(iLayout); }
    
    /**
     * Gets the current value, indicating how far the operation has progressed.
     *
     * @return The value for how far the operation has progressed.
     */
    inline TInt CurrentValue() const { return(iCurrentValue); }

protected:
    
    /**
     * Evaluates the progress text.
     *
     * @param[out] aTextBuf On return, the evaluted text. This is the same
     *                 as the return value.
     * @return The evaluated text. Null if progress information is not 
     *         held as text. A percentage if it is held as a percentage. 
     *         Otherwise, the current value and final value separated by 
     *         a slash. Subclassers may wish to use their own buffer.
     **/
    IMPORT_C virtual const TDesC* EvaluateText(TDes& aTextBuf) const;

public: // from CCoeControl

    /**
     * From @c CCoeControl.
     *
     * Activates the progress information control.
     */
    IMPORT_C void ActivateL();

    /**
     * From @c CCoeControl.
     *
     * Gets the minimum size required to draw the control.
     *
     * @return Two-dimensional size as a width and a height value.
     */
    IMPORT_C TSize MinimumSize();

    /**
     * From @c CCoeControl.
     *
     * Recalculates the control's size in response to a size change.
     */
    IMPORT_C void SizeChanged();

    /**
     * From @c CCoeControl.
     *
     * Gets a list of the logical colours used to draw the control, appended 
     * to @c aColorUseList.
     *
     * @param[out] aColorUseList On return, the colours used to draw 
     *             the control.
     */
    IMPORT_C virtual void GetColorUseListL(
                                CArrayFix<TCoeColorUse>& aColorUseList) const;

    /**
     * From @c CCoeControl.
     *
     * Handles a change to the control's resources.
     *
     * @param aType A message UID value.
     */
    IMPORT_C virtual void HandleResourceChange(TInt aType);

    /**
     * From @c CCoeControl.
     *
     * Handles pointer events. This function gets called whenever a pointer
     * event occurs in the control, i.e. when the pointer is within 
     * the control's extent, or when the control has grabbed the pointer. 
     * The control should implement this function to handle pointer events.
     *
     * Note: events of type @c EButton1Down are processed before 
     * @c HandlePointerEventL() is called, in order to transfer keyboard focus 
     * to the control in which the @c EButton1Down event occurred.
     * If overriding @c HandlePointerEventL(), the implementation must include 
     * a base call to @c CCoeControl's @c HandlePointerEventL().
     *
     * @param aPointerEvent The pointer event.
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);	

protected: //from CCoeControl

    /**
     * From @c CCoeControl.
     *
     * Writes the internal state of the control and its components to a stream.
     * This function is empty in release builds. It is intended to be overridden
     * and base called by subclasses.
     *
     * @since App-Framework_6.1
     * @param aWriteStream The internal state of the control and its components.
     */
    IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;

private: // from CCoeControl

    IMPORT_C void Draw(const TRect& aRect) const;
    IMPORT_C void Reserved_2();	

private:

    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

private: // internal use

	void Construct();
	void CheckSizeCalculated();
	void DrawPartial()const; // AKNLAF
	void DrawProgressBarForeground(CWindowGc& aGc) const; //AKNLAF
	void DrawProgressBarBackground(CWindowGc& aGc) const; //AKNLAF
	TInt FilledWidth() const; //AKNLAF
    
private:

	SInfo iInfo;
	SLayout iLayout;
	TInt iCurrentValue;
	TBool iHeightWasSupplied;
	CFbsBitmap* iBitmap; // AKNLAF
	CFbsBitmap* iBackgroundBitmap; // AKNLAF Not used, extension!
	CFbsBitmap* iBitmapMask; // AKNLAF
	//CFbsBitmap* iBackgroundBitmapMask; // AKNLAF
    CEikProgressInfoExtension* iExtension;

private:

    void LoadBitmapsL();
    void SetBitmapSizes();
    void DeleteBitmaps();
	};


#endif  // __EIKPROGI_H__
