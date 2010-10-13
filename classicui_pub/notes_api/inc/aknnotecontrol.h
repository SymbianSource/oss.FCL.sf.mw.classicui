/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
*
*/



#ifndef AKNNOTECONTROL_H
#define AKNNOTECONTROL_H

// INCLUDES
#include <AknControl.h>
#include <AknUtils.h>

#include <aknprogresstimer.h>
#include <AknBitmapAnimation.h>

// FORWARD DECLARATIONS
class CEikImage;
class CEikLabel;
class CEikProgressInfo;
class CAknNoteAttributes;
class CAknTextControl;
class TAknWindowLineLayout;

// CLASS DECLARATION

/**
* The control for a note dialog.
*
* Manage layout of elements in a note dialog:- the text, the image and
* animation, the progress bar.
*
* @since Series 60 0.9
* @see CAknNoteDialog, CAknNoteAttributes, CAknText
*/
class CAknNoteControl : public CAknControl 
{
friend class CAknNoteAttributes;

public:	
	
	/**
    * C++ default constructor.
    */
	IMPORT_C CAknNoteControl();
	
	/**
    * Destructor.
    */
	IMPORT_C virtual ~CAknNoteControl();
	
	/**
	* Constructs controls from a resource file.
	* @param aRes The resource reader with which to access @c AVKON_NOTE
	* resource.
	*/
	void ConstructFromResourceL(TResourceReader& aRes);

public:

    /**
    * Set the note image. 
    *
    * Set the image in the note attributes. This reduces the
    * size of the image if necessary (only fixed set of
    * image sizes if supported). Perform layout only for
    * the control. The dialog will not be resized. 
    * 
    * @param aImage Pointer to image to set.
    */
    IMPORT_C void SetImageL(CEikImage* aImage);

    /**
    * Set the note animation. 
    *
    * Set the animation in the note attributes.
    * Perform layout only for the control. 
    * The dialog will not be resized. 
    * 
    * @param aResource ID of @c BMPANIM_DATA resource.
    */
	IMPORT_C void SetAnimationL(TInt aResource);

	/**
    * Set the note icon. 
    *
    * Set the icon in the note attributes.
    * Perform layout only for the control. 
    * The dialog will not be resized. 
    * 
    * @param aIcon Pointer to icon to set.
    */
    IMPORT_C void SetIconL(CEikImage* aIcon);

    /**
    * Set the progress bar final value in the note attributes. 
    *  
    * @param aValue The final value for the progress information control. 
    * If it is zero, the value is set to one.
    * @see CEikProgressInfo
    */	
	IMPORT_C void SetFinalProgressValue(TInt aValue);

	/**
    * Increment the progress bar and draw.
    *
    * @param  aIncrement The increment to add to the current progress value.
    * @return 1 if operation hasn't been completed else 0.
    * 
    * @see CEikProgressInfo
    */
	IMPORT_C TInt IncrementBarsAndDraw(TInt aIncrement);

	/**
    * Create the progress bar.
    *
    * @see CEikProgressInfo
    */
	IMPORT_C void CreateProgressBarL();

	/**
    * Return the progress bar.
    *
    * @return Pointer to the progress bar.
    *
    * @see CEikProgressInfo
    */
	IMPORT_C CEikProgressInfo* GetProgressInfo();
	
	/**
    * Start the note animation.
    *
    * @see CAknBitmapAnimation
    */
	IMPORT_C void StartAnimationL();

	/**
    * Stop the note animation.
    * Calls @c CAknBitmapAnimation::CancelAnimation() for animation object.
    * @return @c KErrNone if cancellation successful,
    * @c KErrGenreral if there was no animation object, otherwise another of the
    * system-wide error codes. 
    *
    * @see CAknBitmapAnimation
    */
	IMPORT_C TInt CancelAnimation();

    /**
    * Reset the note text.
    *
    * Perform layout only for the control. 
    * The dialog will not be resized. 
    *
    * @see CAknTextControl
    */
	IMPORT_C void ResetText();

    /**
    * Set whole text for the note control.
    *
    * Perform layout only for the control. 
    * The dialog will not be resized. 
    * @param aText String to set.
    */	
	IMPORT_C void SetTextL(const TDesC& aText);

	/**
    * Set text for a specific line. Any previous text will be overwritten,
    * except for the text that was set for other lines via this method.
    *
    * This method prevents @c ParseTextL from having any effect, hence text
    * control needs to know font and line width to allocate space.
    * 
    * This method is kept for backwards compatibility as the same
    * results could be achieved by the other @c SetTextL with no wrapping
    * enabled (flag in note attributes) and newline characters in the text to
    * indicate a new line.
    *
    * Perform layout only for the control. 
    * The dialog will not be resized. 
    *
    * @param aText String to set.
    * @param aLineNum Specifies the line of the text to be set.
    */
	IMPORT_C void SetTextL(const TDesC& aText,TInt aLineNum);
	
    /**
    * Set the number inside the note text. The text must have been 
    * previously set via resource or via @c SetTextL and must have a
    * \%d or \%N in it.
    *
    * Note:- This method could be replaced by a @c SetTextL method with 
    * a variable number of arguments.
    *
    * Perform layout only for the control. 
    * The dialog will not be resized. 
    *
    * @param aNumber Integer to be set inside the text.
    */	
	IMPORT_C void SetTextNumberL(const TInt aNumber);

    /**
    * Determine which text is to be used, either the text for
    * singular notes, e.g. "You have 1 new message" or the text
    * for plural notes, e.g. "You have %N new messages". These
    * texts must have been set via resource.
    *
    * Note:- This method could be replaced by a @c SetTextL method with 
    * a variable number of arguments.
    *
    * Perform layout only for the control. 
    * The dialog will not be resized. 
    *
    * @param aIsPlural @c ETrue if plural form of the text is needed,
    * otherwise @c EFalse.
    */	
	IMPORT_C void SetTextPluralityL(const TBool aIsPlural);
	
	/**
    * Return the number of lines.
    *
    * @return The number of lines. 
    */
	IMPORT_C TInt NumberOfLines() const;

public:

    /**
    * Do layout.
    *
    * Before doing layout parse the text (This might be redundant except
    * when the control attributs are trasfered but is left here to avoid
    * breaking the functionality of this exported method).
    *
    * Layout is done only if it is needed, i.e. if the attributes indicates
    * that something has changed in such a way that layout needs to be 
    * performed again, e.g. a line of text has been added.
    *
    * This method assumes that the rect of the control has not been changed. 
    * On the contrary, SizeChanged does not assume that the rect is the same
    * and hence always performs layout.
    */
	IMPORT_C void Layout();

	/**
    *
    * This is used by a dialog to layout the control correctly.
    * @return type of layout to be used.
    *
    */
	void WindowLayout( TAknWindowLineLayout& aLayout ) const;

    /**
    * Return the note height. 
    *
    * The note height is taken from the layout compiler and
    * depends on number of lines and the note layout type. 
    * 
    * @return The note height in pixels.
    */
	IMPORT_C TInt NoteHeight() const;

	/**
    * Return the note width. 
    *
    * The note width is taken from the layout compiler. 
    * Contrary to the note height, the note width does not depend on
    * the note layout type or on number of lines. 
    * 
    * @return The note width in pixels.
    */
	IMPORT_C TInt NoteWidth() const;

public:	//Interface to CAknNoteDialog 

    /**
    * Gets the minimun size requided by the control.
    * @return The minimum size required by the control.
    */
	TSize MinimumSize();

	/**
    * Accessor to note attributes stored in @c CAknNoteAttributes.
    * @return Pointer to @c CAknNoteAttributes.
	*/
	CAknNoteAttributes* Attributes() const;

	/**
    * Used by sleeping notes when going to background,
    * in order to stop and delete animations.        
    * Calls @c CancelAnimation(). 
    */
	void Reset();
	
	/**
    * Updates the image according to the current skin.
    */
	void CreateDefaultImageL();

public:
	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

public:
		/**
		* Manage indexes into LAF tables
		*
        * NP   stands for "Note Popup"
        *
        * WNP  stands for "Waiting/progress Note Popup"
        *
        * NWIP stands for "Note With Image Popup"
		*/
		class TIndex 
		{	
		public:

			/**
            * C++ default constructor.
            * @param aNumberOfLines Number of lines.
            * @param aHasNti Determines whether or not there is a number type
            * indication (NTI).
            * @param aImageSize Image size.
            */		
			TIndex(TInt aNumberOfLines, 
			       TBool aHasNti = EFalse, 
			       TSize aImageSize = TSize(0,0));	
		
		public:	

           /**
            * Returns number of lines.
            * @return Number of lines.
            */			
            TInt Lines() const;	
			
		public:	

    	    /**
            * Return index into table "Waiting/progress Note Popup Window
            * Texts Line 1". Index depends on the number of text lines and
            * whether or not there is a number type indication (NTI). See 
            * table in *.lay and LAF specs for working out indexes.
            * @param aLineNum Line number.
            * @return Index into table "Waiting/progress Note Popup Window
            * Texts Line 1".
            */		
			TInt WNPWindowTextsLine1(TInt aLineNum) const;

			/**
            * Return Left index into table "Note With Image Popup Window
            * Texts Line 1". Index depends on number of text lines, whether or
            * not there is a number type indication (NTI). See table in *.lay
            * and LAF specs for working out indexes.
            * @param aLineNum Line number.
            * @return Left index into table "Note With Image Popup Window
            * Texts Line 1".
            */
			TInt NWIPWindowTextsLine1L(TInt aLineNum) const;

        	/**
            * Return Right index into table "Note With Image Popup Window
            * Texts Line 1". Index depends on number of text lines and image
            * size. See table in *.lay and LAF specs for working out indexes.
            *
            * Table has 3 dimensions:-
            * - Dimension 1 is the line number
            * - Dimension 2 is the image width  
            * - Dimension 3 is the image height 
            * 
            * @param aLineNum Line number.
            * @return Right index into table "Note With Image Popup Window
            * Texts Line 1".
            */
			TInt NWIPWindowTextsLine1R(TInt aLineNum) const;

			/**
            * Return Bottom index into table "Note With Image Popup Window
            * Texts Line 1". Index is the same as the number of text lines
            * minus one. See table in *.lay and LAF specs for working out
            * indexes.
            * @param aLineNum Line number.
            * @return Bottom index into table "Note With Image Popup Window
            * Texts Line 1".
            */
			TInt NWIPWindowTextsLine1B(TInt aLineNum) const;

			/**
            * Return Width index into table "Note With Image Popup Window 
            * Texts Line 1". Index depends on number of text lines, whether or
            * not there is a number type indication (NTI) and image size. See
            * table in *.lay and LAF specs for working out indexes.
            *
            * Table has 4 dimensions:-
            * - Dimension 1 indicates the presence of an NTI(index 0 = NO NTI,
            * index 1 = NTI)
            * - Dimension 2 is the line number
            * - Dimension 3 is the image width
            * - Dimension 4 is the image height
            *
            * @param aLineNum Line number.
            * @return Width index into table "Note With Image Popup Window
            * Texts Line 1".
            */
			TInt NWIPWindowTextsLine1W(TInt aLineNum) const;
			
            /**
            * Return indexes for table @c AKN_LAYOUT_WINDOW_popup_note_window.
            * If there are 0-2 lines the index is 0. If there are 3 lines the
            * index is 1, if there are 4 or more lines the index is 2.
            * @return Indexes for table @c AKN_LAYOUT_WINDOW_popup_note_window.
            */
			TInt PopupNoteWindow() const;
	
	        /**
            * Return indexes for table 
            * @c AKN_LAYOUT_WINDOW_popup_note_wait_window. 
            * If there are 0-2 lines the index is 0. If there are 3 lines the
            * index is 1, if there are 4 lines the index is 2.
            * @return Indexes for table 
            * @c AKN_LAYOUT_WINDOW_popup_note_wait_window.
            */
			TInt PopupNoteWaitWindow() const;

		private:	
			void SelfTest() const;	
			TInt ImageWidthIndex() const;
			TInt ImageHeightIndex() const;
			TInt HasNtiIndex() const;

		private:	
			TInt  iNumberOfLines;
			TBool iHasNti;
			TSize iImageSize;
		};	

private:
	//COECONTROL METHODS
	void Draw(const TRect& aRect) const;
	void SizeChanged();
	void DoLayout();
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt anIndex) const;
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private:	
	//LAYOUT METHODS
	TInt NumberTypeIndicationIndex() const;
	TInt ImageWidthIndex() const;

	TInt AnimationIndex();
	void AnimationNoteLayout();

	//Layout for general notes
	void GeneralNoteLayout();
	void GeneralNoteLabelLayout();
	void GeneralNoteIconLayout();

	//Layout for progress and wait notes
	void ProgressNoteLayout();
	void ProgressNoteLabelLayout();
	void ProgressNoteProgressBarLayout();
	void ProgressNoteIconLayout();
	void ProgressNoteNumberTypeIndicationLayout();

	//Layout for image notes
	void ImageNoteLayout();
	void ImageNoteLabelLayout();
	void ImageNoteImageLayout();
	void ImageNoteShadowLayout();
	void ImageNoteNumberTypeIndicationLayout();

	TAknWindowLineLayout GetImageLayout(const TSize& aSize); 
	TAknWindowLineLayout GetImageShadowLayout(const TSize& aSize); 

	TRect LayoutRect() const;
	void SetLineWidthsL();

	
	void ReduceImageIfNeeded();

	void ParseTextL();

private:
	CAknTextControl*    TextControl() const; 

	CEikImage* Image() const; 
	CEikImage* Icon() const; 
	
	CEikProgressInfo* ProgressBar() const; 
	
	CAknProgressTimer* Timer() const; 
	CAknBitmapAnimation* Animation() const; 
	
	TBitFlags&  Flags() const; 

private:
	TInt                iNoteLayout;
	TAknLayoutRect      iShadowRect;
	TBool               iImageHasShadow;
	
	CAknNoteAttributes*  iAttributes;
	CArrayFixFlat<TInt>* iLineWidths;

public:
	/**
	 * @deprecated - use SetTextL() method. 
	 * @param aText aText string to set.
	 */
	 
	IMPORT_C void SetDynamicTextL(const TDesC& aText);
	
	/**
	 * @deprecated - use @c SetTextL().
	 */		
	IMPORT_C void UpdateAndFormatLabelsL(const TDesC& aLabels);
	
	/**
	 * @deprecated - use @c SetTextL().
	 */		
	IMPORT_C void UpdateLabelsL(const TDesC& aLabel1, 
	                            const TDesC& aLabel2=KNullDesC, 
	                            const TDesC& aLabel3=KNullDesC);
	/**
	 * @deprecated - use @c SetTextL().
	 */	 	
	IMPORT_C void UpdateLabels(const TDesC& aLabel1, 
	                           const TDesC& aLabel2=KNullDesC, 
	                           const TDesC& aLabel3=KNullDesC);

	/**
     * @deprecated - label length is taken care of already.
     *
     * Don't use this method anymore. Empty implementation.
     */
	IMPORT_C void SetLabelReserveLengthL(TInt aLength1=0, 
	                                     TInt aLength2=0, 
	                                     TInt aLength3=0);
	
protected: // from MObjectProvider

    /**
    * From @c MObjectProvider. Gets an (@c MAknsControlContext) object whose 
    * type is encapsulated by the specified @c TTypeUid object. Calls 
    * @c SupplyMopObject(TTypeUid aId, CEikButtonGroupContainer* iCba, 
    * CEikMenuBar* iMenu).
    * @since Series 60 2.0
    * @param aId Encapsulates the UID that identifies the type of object
    * required.
    * @return Pointer to the @c MAknsControlContext object provided. Note that
    * the pointer may be @c NULL.
    */
	IMPORT_C TTypeUid::Ptr MopSupplyObject(TTypeUid aId);

public: // new methods

    /**
    * Sets up background rectangle context. 
    * @since Series 60 2.1
    * @param aRect Rectangle position to layout the outer and the inner
    * rectangles of the frame.
    * @param aPos Relative coordinates of parent position in screen. 
    * @param aOwnerNotDialog @c ETrue if the owner is non-dialog control.
    */
	IMPORT_C void SetBgRect(const TRect& aRect, 
	                        const TPoint& aPos, 
	                        TBool aOwnerNotDialog = EFalse);
	                        
	/**
    * @return note layout type 
    * see @c Avkon.hrh for Note dialog constants
    */
	TInt NoteLayout() const;
	};

#endif // AKNNOTECONTROL_H
