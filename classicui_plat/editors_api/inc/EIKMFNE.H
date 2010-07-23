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


#if !defined(__EIKMFNE_H__)
#define __EIKMFNE_H__

#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>
#endif

#if !defined(__COEDEF_H__)
#include <coedef.h>
#endif

#if !defined(__COEINPUT_H__)
#include <coeinput.h>
#endif

// For MEikCalendarObserver
#if !defined(__EIKCAL_H__)
#include <eikcal.h>	
#endif

#if !defined(__EIKDEF_H__)
#include <eikdef.h>
#endif

#if !defined(__BABITFLAGS_H__)
#include <babitflags.h>
#endif

// For MAknMfneCommandObserver
#if !defined(__AKNMFNECOMMANDOBSERVER)
#include <aknmfnecommandobserver.h>
#endif //!defined(__AKNMFNECOMMANDOBSERVER)

//
// Forward Declarations
//
class CEikonEnv;
class CTimeEditor;
class CDateEditor;

// Skin-related API forward declarations
class MAknsControlContext;

// Extension object within CEikMfne
class CEikMfneExtension;

//
/**
 * Abstract base class for fields within a multi-field numeric editor.
 */
class CEikMfneField : public CBase
	{
public:
    /**
     * The type of highlight.
     */
	enum THighlightType
		{
		/** Inverse video. */
		EInverseVideo,
		/** The cursor is visible in the field so that highlighting is not used. */
		ECursor
		};
protected:
    /**
     * Protected default constructor.
     *
     * Sets the minimum width of the field to zero pixels.
     */
	IMPORT_C CEikMfneField();
public:
	void Draw(CWindowGc& aGc, const CFont& aFont, const TPoint& aTopLeft) const;
	TInt WidthInPixels(const CFont& aFont) const;
	TInt DistanceFromStartOfFieldToEndOfTextInPixels(const CFont& aFont) const;

    /**
     * An implementation of this pure virtual function should
     * get the field's maximum width in pixels.
     *
     * @param aFont The font.
     * @param aShrinkToMinimumSize ETrue to shrink the width to the minimum required.
     * @return The field's maximum width in pixels.
     */
	virtual TInt MaximumWidthInPixels(const CFont& aFont, TBool aShrinkToMinimumSize)=0;

    /**
     * An implementation of this pure virtual function should
     * return the field's input capabilities.
     *
     * @return The field's input capabilities.
     */
	virtual TCoeInputCapabilities InputCapabilities() const=0;
	
	/**
	 * Derived classes' implementation of function should
	 * return whether the field is editable.
	 *
	 * This implementation returns EFalse.
	 *
	 * @return EFalse.
     */
	IMPORT_C virtual TBool IsEditable() const;
	
	/**
	 * Derived classes' implementation of function should
	 * return whether the field is valid
	 *
	 * This implementation returns ETrue.
	 *
	 * @return ETrue.
     */	
	IMPORT_C virtual TBool IsValid() const;
	
	/**
	 * An implementation of this function should get the
	 * field's highlight type.
     * 
     * May only be called if IsEditable() returns ETrue.
     * 
     * This implementation panics in debug builds and returns
     * a dummy value in release builds.
     *
     * @return EInverseVideo.
     */
	IMPORT_C virtual THighlightType HighlightType() const;
	
	/**
	 * An implementation of this function should handle a key event.
     *
     * May only be called if IsEditable() returns ETrue.
     * This implementation panics in debug builds and is
     * empty in release builds.
     *
     * @param aFont The control's font.
     * @param aKeyEvent The key event passed on from the multi-field numeric editor.
     * @param aInterpretLeftAndRightAsEarEvents Not used. 
     * @param aDataAltered On return, indicates whether or not the field
     *                     contents changed. If EFalse, left and right arrow
     *                     key presses indicate a movement to the preceding of
     *                     following field, if ETrue they are ignored.
     * @param aHighlightIncrement On return: -1 indicates the previous field is
     *                            highlighted,0 indicates the highlight is
     *                            unchanged and 1 indicates the following field
     *                            is highlighted.
     */
	IMPORT_C virtual void HandleKey(const CFont& aFont, const TKeyEvent& aKeyEvent, TBool aInterpretLeftAndRightAsEarEvents, TBool& aDataAltered, TInt& aHighlightIncrement);
 	
 	/**
 	* An implementation of this function should
 	* handle de-highlighting the field.
    *
    * May only be called if IsEditable() returns ETrue.
    *
    * This implementation panics in debug builds and is empty
    * in release builds.
    * 
    * @param aFont The control's font.
    * @param aEikonEnv The control's environment.
    * @param aDataAltered On return, set to ETrue if the function caused
    *                     the field's contents to change, otherwise unchanged.
    * @param aError On return, changed to ETrue if an error occurred e.g.
    *               the user entered an invalid value, otherwise unchanged.
    */
	IMPORT_C virtual void HandleDeHighlight(const CFont& aFont, CEikonEnv& aEikonEnv, TBool& aDataAltered, TBool& aError);
	
	const TDesC& FieldText() const;
protected:
    /**
     * Handles a left or right arrow key press.
     *
     * @param aKey Left or right arrow key: either EKeyLeftArrow or EKeyRightArrow. 
     * @param aDataAltered On return, ETrue if data is altered as a result of this function.
     * @param aHighlightIncrement On return, the direction to move the cursor:
     *                            either -1 if aKey is a left arrow key, or 1 if aKey is a right arrow key.
     * @panic 3 In debug builds, if aKey is neither a left nor a right arrow key.
     */
	IMPORT_C void HandleLeftOrRightArrow(TChar aKey, TBool& aDataAltered, TInt& aHighlightIncrement);

    TInt AdditionalWidthForHighlights(const CFont& aFont) const;
private:
	virtual const TDesC& Text() const=0;
protected:
    /**
     * The field's minimum width in pixels.
     */
	TInt iMinimumWidthInPixels;
	};

//

/**
 * A separator field for a multi-field numeric editor.
 *
 * For instance, the character that separates time or date components.
 */
NONSHARABLE_CLASS(CEikMfneSeparator) : public CEikMfneField
	{
private:
	CEikMfneSeparator(HBufC* aText);
public:
    /**
     * Destructor.
     *
     * Deletes the separator text that is owned by the object.
     */
	IMPORT_C virtual ~CEikMfneSeparator();
	
	/**
	 * Allocates and constructs a CEikMfneSeparator from resource.
     * 
     * Uses an MFNE_SEPARATOR resource.
     * 
     * @param aResourceReader The resource reader to use.
     * @return A newly constructed separator field.
     */
	IMPORT_C static CEikMfneSeparator* NewL(TResourceReader& aResourceReader);
	
	/**
	 * Allocates and constructs a separator.
     *
     * @param aText The separator's text. Ownership of aText is transferred.
     * @return A newly constructed separator.
     */
	IMPORT_C static CEikMfneSeparator* NewL(HBufC* aText); // ownership of aText is transferred when everything that can leave has successfully been done
	
	/**
	 * Sets the separator's text.
     *
     * This function transfers ownership of the text and can only be called if the field's text was previously NULL.
     * 
     * @param aText The separator's text.
     * @panic 4 If the separator's text was not previously Null.
     */
	IMPORT_C void SetText(HBufC* aText); // allows later transfer of ownership of text - can only be called if aText was previously NULL
    
private: // framework
	virtual TInt MaximumWidthInPixels(const CFont& aFont, TBool aShrinkToMinimumSize);
	virtual TCoeInputCapabilities InputCapabilities() const;
	virtual const TDesC& Text() const;
private:
	HBufC* iText;
	};

//

/**
 * A number field within a multi-field numeric editor.
 */
NONSHARABLE_CLASS(CEikMfneNumber) : public CEikMfneField
	{
public:
    /**
     * Flags for the number field.
     *
     * EFillWithLeadingZeros, EPreserveOldWidthBeforeEditing and ERepresentsYear can only be set if EPublicallySettableFlags is set.
     */
	enum
		{
		/** Prepends the number field's value with leading zeros up to the maximum allowable width of the field. */
		EFillWithLeadingZeros			=0x1,
		/** The field's minimum width in pixels is set to the current text's width in pixels. */
		EPreserveOldWidthBeforeEditing	=0x2,
		/** The number is a year. */
		ERepresentsYear					=0x4,
		/** Used internally to make sure only the previous three values are set. */
		EPublicallySettableFlags		=EFillWithLeadingZeros|EPreserveOldWidthBeforeEditing|ERepresentsYear
		};
private:
	enum
		{
		EIsBeingEditedWithCursor		=0x8,
		EIsUninitialised				=0x10,
		EFillWithTrailingZeros          =0x20
		};
private:
	CEikMfneNumber(TInt aMinimumValue, TInt aMaximumValue, TUint32 aFlags);
	void ConstructL();
public:
    /**
     * Destructor.
     *
     * Deletes the number field's text.
     */
	IMPORT_C virtual ~CEikMfneNumber();
	
	/**
	 * Allocates and constructs a CEikMfneNumber from resource.
     *
     * Obtains flags and the minimum and maximum values from an MFNE_NUMBER resource. Then calls the overloaded NewL() function.
     *
     * @param aFont The font to use.
     * @param aResourceReader The resource reader to use.
     * @return A newly constructed number field.
	 */
	IMPORT_C static CEikMfneNumber* NewL(const CFont& aFont, TResourceReader& aResourceReader);

    /**
     * Allocates and constructs a CEikMfneNumber with the specified parameters.
     *
     * @param aFont The font to use.
     * @param aMinimumValue The minimum value.
     * @param aMaximumValue The maximum value.
     * @param aInitialValue The initial value. This must be greater than the minimum value and less than the maximum value.
     * @param aFlags The number field's flags. See the Anonymous enum.
     * @return A newly constructed number field.
     * @panic 8 If the initial value is not greater than or equal to the minimum value and less than or equal to the maximum value.
     */
	IMPORT_C static CEikMfneNumber* NewL(const CFont& aFont, TInt aMinimumValue, TInt aMaximumValue, TInt aInitialValue, TUint32 aFlags);
	
	/**
	 * Sets the minimum and maximum allowable values.
     *
     * @param aMinimumValue The minimum value. Must be less than or equal to the maximum value.
     * @param aMaximumValue The maximum value.
     * @param aFont The font in use.
     * @panic 9 If the minimum value is greater than the maximum value or if the minimum/maximum text length is greater than the maximum number of digits.
     */
	IMPORT_C void SetMinimumAndMaximum(TInt aMinimumValue, TInt aMaximumValue, const CFont& aFont); // only values inside the initial minimum and maximum are permitted
	
	/**
	 * Gets the minimum and maximum allowable values.
	 *
	 * @param aMinimumValue On return, the minimum allowable value.
	 * @param aMaximumValue On return, the maximum allowable value.
     */
	IMPORT_C void GetMinimumAndMaximum(TInt& aMinimumValue, TInt& aMaximumValue) const;
	
	/** 
	 * Sets the field's current value.
     * @param aValue The field's current value. This must be between the minimum value and the maximum value.
     * @param aFont The font.
     * @panic 11 In debug builds only, if the value is less than the minimum value or greater than the maximum value.
     */
	IMPORT_C void SetValue(TInt aValue, const CFont& aFont);
 	
 	/**
 	 * Gets the number field's value. Note that this function will leave
 	 * if the value is not valid, i.e. the number of digits is zero
 	 * or the value is outside of the minimum and maximum range.
     *
     * @return The field's value.
     */
	IMPORT_C TInt Value() const;
	
    /**
	 * Returns ETrue if the field contains more than zero
	 * digits.
     *
	 * @return ETrue if the field contains more than zero digits.
     */	
	IMPORT_C virtual TBool IsValid() const;

    /**
     * Sets the uninitialized status of the field.
     * 
     * @param aUninitialised If ETrue, sets the field as uninitialized,
     *                       i.e. it doesn't display anything.
     */
	IMPORT_C void SetUninitialised(TBool aUninitialised);
	
	/**
	 * Gets the uninitialized status of the field.
	 * 
	 * @return ETrue, if the field is set as uninitialized.
	 */
	IMPORT_C TBool IsUninitialised() const;

public:
    /**
     * Sets the digit display type.
     *
     * @since S60 v3.1
     * @param aDigitType The digit display type to bet set for this number field
     * @param aFont The font of the MFNE that owns this field, usually retrieved with CEikMfne::Font()
     */
	IMPORT_C void SetDigitType(TDigitType aDigitType, const CFont& aFont);

    /**
     * Gets the digit display type.
     *
     * @since S60 v3.1
     * @return The digit display type of this number field
     */
	IMPORT_C TDigitType DigitType() const;

	/**
	 * Derive and set digit display type from locale information.
	 *
	 * @since S60 v3.1
	 * @param aFont The font of the MFNE that owns this field, usually retrieved with CEikMfne::Font()
	 */
	IMPORT_C void RefreshDigitType(const CFont& aFont);
	
	void SetTrailingZeros();

public:
	TBool IsTextNull() const;
private: // framework
	virtual TInt MaximumWidthInPixels(const CFont& aFont, TBool aShrinkToMinimumSize);
	virtual TCoeInputCapabilities InputCapabilities() const;
	virtual TBool IsEditable() const;
	virtual THighlightType HighlightType() const;
	virtual void HandleKey(const CFont& aFont, const TKeyEvent& aKeyEvent, TBool aInterpretLeftAndRightAsEarEvents, TBool& aDataAltered, TInt& aHighlightIncrement);
	virtual void HandleDeHighlight(const CFont& aFont, CEikonEnv& aEikonEnv, TBool& aDataAltered, TBool& aError);
	virtual const TDesC& Text() const;
private:
	TInt MaximumNumberOfDigits() const;
	TInt NumberOfDigits() const;
	void SetTextToValue(TInt aValue, const CFont& aFont);
	TInt ValueFromText() const;
	TBool ConvertsIntoValidValue(TInt& aValue) const;

private: // International digit support
	TChar NormalizeDigit(TChar aChar);
	TText ZeroCharacter() const;
	TText NegativeCharacter() const;

private:
	TInt iMinimumValue;
	TInt iMaximumValue;
	TInt iMaxDigits;
	TUint32 iFlags;
	HBufC* iText;
	TChar iNudgeCharMinus;
	TChar iNudgeCharPlus;
	TInt iMaxDigitsMinimumValue;
    TInt iMaxDigitsMaximumValue;
	TDigitType	iDigitType;
	};

//

/**
 * A symbol field for a multi-field numeric editor.
 *
 * For instance, the AM / PM text in a time editor. In this case, the field contains 2 symbolic items one each for the AM and PM text strings.
 */
NONSHARABLE_CLASS(CEikMfneSymbol) : public CEikMfneField
	{
public:
    /**
     * An item within a symbol field in an MFNE.
     */
	NONSHARABLE_CLASS(CItem) : public CBase
		{
	private:
		CItem(TInt aId, TChar aKeyToMatch, HBufC* aText);
	public:
	    /**
	     * Destructor.
         *
         * Deletes the item's text.
         */
		IMPORT_C virtual ~CItem();
		
		/**
		 * Allocates and constructs a symbolic item from resource.
         *
         * Uses a MFNE_SYMBOLIC_ITEM resource.
         * @param aResourceReader The resource reader to use.
         * @return A newly constructed symbolic item.
         */
		IMPORT_C static CItem* NewL(TResourceReader& aResourceReader);
		
		/**
		 * Allocates and constructs a symbolic item.
         *
         * @param aId The ID of the symbolic item that uniquely identifies the item in the field.
         * @param aKeyToMatch The key that represents the item. This is for character matching, not for display.
         * @param aText The text to be drawn. Ownership of aText is transferred when everything that can leave has successfully completed.
         * @return A newly constructed symbolic item.
         */
		IMPORT_C static CItem* NewL(TInt aId, TChar aKeyToMatch, HBufC* aText); // ownership of aText is transferred when everything that can leave has successfully been done
        
        /**
         * Sets the symbolic item's text. 
         * 
         * The item takes ownership of aText.
         * 
         * @param aText The symbolic item's text.
         * @panic 19 In debug builds if the symbolic item's text was not
         *           previously Null.
         */
		IMPORT_C void SetText(HBufC* aText); // allows later transfer of ownership of text - can only be called if aText was previously NULL
	private:
		friend class CEikMfneSymbol;
	private:
		TInt iId;
		TCharF iKeyToMatch;
		HBufC* iText;
		};
private:
	CEikMfneSymbol(TInt aNumSymbolicItems);
public:
    /**
     * Destructor.
     * 
     * Deletes the array of symbolic items owned by the object.
     */
	IMPORT_C virtual ~CEikMfneSymbol();
	
	/**
     * Allocates and constructs a CEikMfneSymbol from resource.
     * 
     * Uses a MFNE_SYMBOL resource. The first item is set as current.
     * 
     * @param aResourceReader The resource reader to use.
     * @return A newly constructed symbol.
     * @panic 15 If there is not more than one symbol.
     */
	IMPORT_C static CEikMfneSymbol* NewL(TResourceReader& aResourceReader);
	
    /**
     * Allocates and constructs a CEikMfneSymbol.
     * 
     * The first item is set as current.
     * 
     * @param aNumSymbolicItems The number of symbolic items. Must be
     * greater than one. All items are set to NULL.
     * @return A newly constructed symbol.
     * @panic 15 If there is not more than one symbol.
     */
	IMPORT_C static CEikMfneSymbol* NewL(TInt aNumSymbolicItems);

    /**
     * Adds the specified symbolic item at the first available position in
     * the array.
     * 
     * This should be called by the container only if construction was not
     * made from resource.
     * 
     * @param aSymbolicItem The symbol to add. Ownership of aSymbolicItem
     * is transferred to this.
     * @param aMakeCurrent ETrue to make the added symbol current.
     * @panic 16 In debug build if the symbolic item array has not yet been
     * created.
     * @panic 17 If the array is full.
     */
	IMPORT_C void AddSymbolicItem(CItem* aSymbolicItem, TBool aMakeCurrent); // to be called by container only if not constructed from resource - ownership of aSymbolicItem is transferred to "this"
	
	/**
     * Sets the current item to the one specified.
     * 
     * 
     * @param aId The id of the new current item.
     * @panic 18 If the specified item does not exist.
     */
	IMPORT_C void SetCurrentSymbolicItemToId(TInt aId);
	
    /**
     * Gets the current symbol's ID.
     * 
     * @return The current symbol's ID.
     */
	IMPORT_C TInt IdOfCurrentSymbolicItem() const;
	
    /**
     * Sets the uninitialized status of the field.
     * 
     * @param aUninitialised If ETrue, sets the field as uninitialized,
     *                       i.e. doesn't display anything.
     */
	IMPORT_C void SetUninitialised(TBool aUninitialised);
	
	/**
	 * Gets the uninitialized status of the field.
	 * 
	 * @return ETrue, if the field is set as uninitialized.
	 */
	IMPORT_C TBool IsUninitialised() const;
	
private: // framework
	virtual TInt MaximumWidthInPixels(const CFont& aFont, TBool aShrinkToMinimumSize);
	virtual TCoeInputCapabilities InputCapabilities() const;
	virtual TBool IsEditable() const;
	virtual THighlightType HighlightType() const;
	virtual void HandleKey(const CFont& aFont, const TKeyEvent& aKeyEvent, TBool aInterpretLeftAndRightAsEarEvents, TBool& aDataAltered, TInt& aHighlightIncrement);
	virtual void HandleDeHighlight(const CFont& aFont, CEikonEnv& aEikonEnv, TBool& aDataAltered, TBool& aError);
	virtual const TDesC& Text() const;
private:
	TInt CurrentSymbolicItem() const;
	void SetCurrentSymbolicItem(TInt aCurrentSymbolicItem);
private:
	TInt iNumSymbolicItems;
	TInt iCurrentSymbolicItem;
	CItem** iSymbolicItems;
	};

//

/**
 * Multi-field numeric editor abstract base class.
 * 
 * This is a set of fields, where a field can be a number, a symbol or
 * a separator. Field classes are derived from CEikMfneField.
 * 
 * Concrete multi-field numeric editors are derived from this class and
 * should provide the following:
 * 
 * * A virtual destructor if the class introduces new data members which
 * are allocated on the heap.
 * 
 * * A ConstructL() function; this is used to initialise a multi-field
 * numeric editor.
 * 
 * * A ConstructFromResourceL() function; this is used to initialise a
 * multi-field numeric editor from a resource.
 * 
 * * A data member to store the editor's value.
 * 
 * * Functions to set and get the editor's value.
 * 
 * * Functions to set the minimum and maximum allowable values.
 */
class CEikMfne : public CEikBorderedControl, public MAknMfneCommandObserver
	{
public:
	// miscellaneous functions
    /**
     * Default constructor.
     */
	IMPORT_C CEikMfne();
	
	/**
     * Destructor.
     * 
     * This function is virtual which ensures that if delete is explicitly
     * called on a CEikMfne pointer which points to a derived class
     * instance, the derived class destructor is called.
     */
	IMPORT_C virtual ~CEikMfne();

    /**
     * Allocates a field array containing aNumFields elements. 
     * 
     * This should be called by the container only if a derived control is
     * not constructed from a resource.
     * 
     * @param aNumFields The number of fields.
     * @panic 20 In debug builds, if there is already a field in the editor.
     */
	IMPORT_C void CreateFieldArrayL(TInt aNumFields); // to be called by container only if not constructed from resource

    /**
     * Adds a field.
     * 
     * The field is added as the first empty element in the field array or,
     * if there is no current field, aField becomes the current field.
     * 
     * This should be called by the container only if a derived control is
     * not constructed from a resource.
     * 
     * Ownership of aField is transferred to this multi-field numeric
     * editor.
     * 
     * @param aField A field.
     * @panic 22 If the field array has not been allocated.
     */
	IMPORT_C void AddField(CEikMfneField* aField); // to be called by container only if not constructed from resource - ownership of aField is transferred to "this"

    /**
     * Deletes the editor's field and the field array.
     * 
     * After a call to this, CreateFieldArrayL() can be called again.
     */
	IMPORT_C void ResetFieldArray(); // after this CreateFieldArrayL() can be called again
	
	/**
     * Gets the control's border margins.
     * 
     * @return The control's margins.
     */
	IMPORT_C TMargins BorderMargins() const;
	
    /**
     * Draws immediately, and then leaves with an info message containing a
     * formatted time/date string.
     * 
     * The time/date is passed to the function, as is the resource which
     * contains the format string which defines how it is to be formatted.
     * 
     * @param aResourceId The resource containing the time/date format. See
     * TTime::FormatL().
     * @param aTimeDate The object containing the time/date to be displayed.
     */
	IMPORT_C void DrawNowAndLeaveWithTimeDateFormatInfoMsgL(TInt aResourceId, const TTime& aTimeDate) const;

    /**
     * Gets the CEikMfneField at the specified index.
     * 
     * @param aField The field index.
     * @return The requested field, or NULL if the index is less than zero
     * or greater than the number of fields.
     */
	IMPORT_C CEikMfneField* Field(TInt aField) const;
	
public:
	// some utility functions which other classes may find useful
	
	/**
     * A utility function which reads seconds, minutes and hours from a
     * resource and returns the corresponding TTime value.
     * 
     * @param aResourceReader A resource reader.
     * @return The time value read from the resource.
     */
	IMPORT_C static TTime ReadTime(TResourceReader& aResourceReader);

    /**
     * A utility function which reads days, months and years from a resource
     * and returns the corresponding TTime value.
     * 
     * @param aResourceReader A resource reader.
     * @return The date value read from the resource. The hours, minutes,
     * seconds values are set to zero.
     */
	IMPORT_C static TTime ReadDate(TResourceReader& aResourceReader);

    /**
     * A utility function which reads seconds, minutes, hours, days, months
     * and years from a resource and returns the corresponding TTime value.
     * 
     * @param aResourceReader A resource reader.
     * @return The time/date value read from the resource.
     */
	IMPORT_C static TTime ReadTimeAndDate(TResourceReader& aResourceReader);
	
    /**
     * Reads a duration value from a resource.
     * 
     * @param aResourceReader A resource reader.
     * @return The duration, in seconds.
     */
	IMPORT_C static TTimeIntervalSeconds ReadDuration(TResourceReader& aResourceReader);
	
    /**
     * Reads a time offset from a resource. 
     * 
     * This is identical to ReadDuration(), except that negative offsets
     * are allowed.
     * 
     * @param aResourceReader A resource reader.
     * @return The duration, in seconds.
     */
	IMPORT_C static TTimeIntervalSeconds ReadTimeOffset(TResourceReader& aResourceReader);
    
    /**
     * Converts a time duration to seconds.
     * 
     * @param aTime The date and time to be converted.
     * @return The time duration in seconds.
     */
	IMPORT_C static TTimeIntervalSeconds Convert(const TTime& aTime);
    
    /**
     * Converts a time duration in seconds to hours, minutes and seconds.
     * 
     * @param aTimeIntervalSeconds The number of seconds to be converted.
     * @return The date/time duration.
     */
	IMPORT_C static TTime Convert(const TTimeIntervalSeconds& aTimeIntervalSeconds);
    //
    /**
     * Gets the index into the field array of the current field.
     * 
     * @return The current field's index.
     */
    inline TInt CurrentField() const;

    /**
     * Gets the number of fields.
     * 
     * @return The number of fields in the editor.
     */
    inline TInt NumFields() const;

public: // AVKON addition
    /**
     * Settable features for MFNE. See SetFeature().
     *
     * @since S60 3.2
     */
    enum TFeatureId
        {
        /** Tries to prevent MFNE drawing outside its rect,
            event if it smaller than MinimumSize().
            0 (or EFalse) parameter disables this, non-zero
            (or ETrue) enables the feature. */
        EClipGcToRect,
        
        /** Disables VKB. Non-zero (or ETrue) parameter disables VKB, 
            0 (or EFalse) enables VKB. When disabled, 
            editor doesn't request PenInputServer to start VKB */ 
        EDisablePenInput,
        
        /** Support finger input. Paramter is TFingerSupportParams.*/ 
        EFingerSupport,
        
        ELaunchPenInputAutomatic,

        EPartialScreenInput
        };
    /** Parameter for finger support feature: 
      * 0 means disable the suppor; 
      * 1 means enable the support;
      * 2 means enable the support with highlight of whole text.
      */
    enum TFingerSupportParams
        {
        EDisaleFingerSupport,
        EnableFingerSupport,
        EnableWithAllHighlight
        };
    
    /**
     * Sets the alignment of the editor. The editor alignments, defined in
     * avkon.hrh, are EAknEditorAlignNone, EAknEditorAlignCenter,
     * EAknEditorAlignLeft, EAknEditorAlignRight or EAknEditorAlignBidi.
     * 
     * @param aAlignment The editor's alignment
     */
    IMPORT_C void SetMfneAlignment(TInt aAlignment);
    
    /**
     * Sets whether the editor consumes up and down key events. If this is
     * set to EFalse, the editor returns EKeyWasNotConsumed upon receiving
     * EKeyDownArrow or EKeyUpArrow key event and doesn't send the key event to
     * the current field.
     * 
     * @param aConsume If EFalse, OfferKeyEventL() returns
     * EKeyWasNotConsumed when up and down key events are received.
     */
    IMPORT_C void SetUpAndDownKeysConsumed(TBool aConsume);

    /**
     * Used for suppressing all editor's background drawing. This is
     * intended for internal use.
     *
     * Note that when this is set, the background is not drawn with skin
     * nor cleared, so the background MUST be drawn by the parent control
     * every time the editor changes.
     *
     * @param aSuppress If ETrue, suppress background drawing
     */
    IMPORT_C void SetSuppressBackgroundDrawing( TBool aSuppress );

    /**
     * Used for setting various flag-like features to the editor.
     *
     * @param aFeatureId The feature id, see TFeatureId
     * @param aFeatureParam The feature parameter. This is usually
     *                      enabled or disabled. For more info, see
     *                      the feature documentation in TFeatureId.
     * @return KErrNone if the feature modification succeeded
     * @since S60 3.2
     **/
    IMPORT_C TInt SetFeature( TInt aFeatureId, TInt aFeatureParam );
     
    /**
     * Used to getting feature statuses.
     *
     * @param aFeatureId The feature id, see TFeatureId
     * @param aFeatureParam On return, the parameter for the feature
     *                      (usually non-zero for an enabled feature
     *                      and zero for disabled)
     * @return KErrNone if the feature is supported and fetching its value
     *                  succeeded
     * @since S60 3.2
     */
    IMPORT_C TInt GetFeature( TInt aFeatureId, TInt& aFeatureParam ) const;

    /**
     * Used for checking if the editor supports a feature.
     * For features, see TFeatureId.
     *
     * @param aFeatureId
     * @return ETrue if the feature is supported
     * @since S60 3.2
     */
    IMPORT_C TBool SupportsFeature( TInt aFeatureId ) const;

    // Highlights a field
    void HighlightField(  TInt aFieldPosition );

    /**
     * Gets a pointer to the CFont object that is used to draw the fields in
     * this editor.
     * 
     * @return A pointer to the CFont object used to draw the fields in
     * this editor.
     */
	IMPORT_C const CFont* Font() const;
	
    /**
     * Sets the font that is used to draw the fields in this editor.
     * 
     * @param aFont A pointer to a CFont object that is used to draw the
     * fields in this editor.
     */
	IMPORT_C void SetFont(const CFont* aFont);

    /**
     * Sets within in the editor an externally owned Skins background control context.
     * This background control context will then be used by the editor to draw background.
     *
     * If this API is not called, then the editor IS skin enabled, (that is CEikMfnes are skin
     * enabled by default) but it will try to find a control context with which to perform background 
     * drawing from the Control Environment, via the Object Provider.
     *
     * Setting this control context to NULL will have the effect of turning off background 
     * skinning. 
     *
     * @param aBackgroundControlContext   Control context to store. Not owned. Can be NULL
     */
    IMPORT_C void SetSkinBackgroundControlContextL( MAknsControlContext* aControlContext );
    
    
    /**
     * From MAknMfneCommandObserver. Allows owning controls to give commands to 
     * MFNE editors. This is interface was added to enable modifying the current field
     * value with touch buttons.
     *
     * @param aCommand Command ID defined in MAknMfneCommandObserver::TMfneCommand
     */
    IMPORT_C void HandleMfneCommandL(TInt aCommand);
    
    /**
     * Sets the MFNE to use the CCoeControl::OverrideColorL() defined
     * color in drawing. If this is set, no skinning will be used
     * in drawing.
     *
     * @param aUseOverrideColors ETrue to make the MFNE use overridden colors.
     * @since S60 v3.2
     */
    IMPORT_C void SetUseOverrideColors( TBool aUseOverrideColors );


public:	// from CCoeControl
    /**
     * Handles key events.
     * 
     * Overrides CCoeControl::OfferKeyEventL(). The key event is passed
     * onto the current field to handle.
     * 
     * @param aKeyEvent The key event.
     * @param aType The type of key event.
     * @return Indicates whether or not the key event was used by this
     * control.
     */
	IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

    /**
     * Prepares for focus loss.
     * 
     * Overrides CCoeControl::PrepareForFocusLossL().
     * 
     * This function should be called when an attempt is made to remove
     * focus from a multi-field numeric editor. It redraws the control, removing
     * highlighting from the current field.
     * 
     * It may be overridden in derived classes to test the validity of
     * information entered into the editor. Derived class versions should include
     * a base function call.
     */
	IMPORT_C virtual void PrepareForFocusLossL();

    /**
     * Gets the minimum size of the control. 
     * 
     * Overrides CCoeControl::MinimumSize().
     *
     * @return The minimum control size.
     */
	IMPORT_C virtual TSize MinimumSize();

    /**
     * Gets the list of logical colours used to draw the control.
     * 
     * The colours are appended to aColorUseList.
     * 
     * Overrides CCoeControl::GetColorUseListL().
     * 
     * @param aColorUseList On return, the colour list.
     */
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u

    /**
     * Handles a change to the control's resources. 
     * 
     * The types of resources handled are those which are shared across the
     * environment, e.g. colours or fonts.
     * 
     * Overrides CCoeControl::HandleResourceChange().
     * 
     * @param aType A message UID value.
     */
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u

    /**
     * Gets the total of the input capabilities of all the editor's fields.
     * 
     * Overrides CCoeControl::InputCapabilities().
     *
     * If this function is overrided in a subclass, the subclass should
     * obtain this class' InputCapabilities' object provider through
     * TCoeInputCapabilities::ObjectProvider() and set that as a part of
     * the subclass' InputCapabilities object provider chain to ensure
     * maximum functionality.
     * 
     * @return The control's input capabilities.
     */
	IMPORT_C virtual TCoeInputCapabilities InputCapabilities() const;

    /**
     * From @c CCoeControl.
     * 
     * Handles pointer events.
     *
     * @param aPointerEvent The pointer event.
     */
	IMPORT_C virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);

    /**
     * Retrieves an object of the same type as that encapsulated in aId.
     * 
     * Overrides CCoeControl::MopSupplyObject().
     * 
     * @param aId An encapsulated object type ID. 
     * @return Encapsulates the pointer to the object provided. Note that
     * the encapsulated pointer may be NULL. 
     */
	IMPORT_C virtual TTypeUid::Ptr MopSupplyObject( TTypeUid aId );

public: // new 
    /**
     * Sets the colors for text and background as skin IDs. Please note that
     * bgcolor overrides skinned draw if set
     * 
     * @since 3.0
     * @param aAknSkinIDForTextColor ID for text color.
     * @param aAknSkinIDForBgColor ID for background color.
     */
    IMPORT_C void SetSkinTextColorL(TInt aAknSkinIDForTextColor, TInt aAknSkinIDForBgColor=KErrNotFound);

protected:
	// framework
    /**
     * Redraws the current field, so removing or displaying the cursor.
     * 
     * If the editor has lost focus, the current field is reset to the
     * first editable field.
     * 
     * @param aDrawNow Whether to draw the control immediately.
     */
	IMPORT_C virtual void FocusChanged(TDrawNow aDrawNow);

    /**
     * Writes the internal state of the control and its components to
     * aStream.
     * 
     * This function is empty in release builds.
     */
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;

	// miscellaneous functions
	
    /**
     * Handles the redrawing associated with a change to the current field.
     * 
     * Called by OfferKeyEventL(), HandlePointerEventL() and
     * PrepareForFocusLossL().
     * 
     * @param aHandleDeHighlight ETrue if the current field has changed so
     * requires de-highlighting.
     * @param aNewCurrentField The index of the field to which the user has
     * moved.
     * @param aOldWidthInPixelsOfOldCurrentField The width in pixels of the
     * previous current field.
     * @param aOldHighlightTypeOfOldCurrentField The highlight type of the
     * previously current field.
     * @param aDataAltered ETrue if the data has been changed.
     * @param aError On return, ETrue if successful, EFalse if not
     * successful.
     */
	IMPORT_C void HandleInteraction(TBool aHandleDeHighlight, TInt aNewCurrentField, TInt aOldWidthInPixelsOfOldCurrentField,
								CEikMfneField::THighlightType aOldHighlightTypeOfOldCurrentField, TBool& aDataAltered, TBool& aError);
								
    /**
     * Empty virtual function.
     * 
     * Called by HandleInteraction() when switching from the current field.
     * Can be implemented by derived classes to maintain consistency between
     * fields, e.g. in a range editor.
     * 
     * @param aField The current field.
     * @param aDrawAllFields On return, whether all fields have changed and
     * need to be redrawn.
     */
	IMPORT_C virtual void FieldIsAboutToBeDeHighlighted(CEikMfneField* aField, TBool& aDrawAllFields); // first occurrence of this virtual function - does nothing by default
	
    /**
     * Gets the size of the multi-field numeric editor.
     * 
     * The width is the sum of the maximum widths of every field.
     * 
     * @return The size of the multi-field numeric editor.
     */
	IMPORT_C TSize MfneSize() const;

    /**
     * Gets the size of the multi-field numeric editor.
     * 
     * The width is the sum of the maximum widths of every field.
     * 
     * @param aShrinkToMinimumSize ETrue to shrink the width to the minimum
     * required for each field.
     * @return The size of the multi-field numeric editor.
     */
	IMPORT_C TSize MfneSize(TBool aShrinkToMinimumSize);

    IMPORT_C virtual void SizeChanged();
    
public:
	static void InvalidFieldAlert();
	static void LeaveWithAlert(TInt aResourceId);	
	void GetCursorInfo( TPoint& aPos, TInt& aHeight, TInt& aWidth, TInt& aAscent );
    void ReportUpdate();
    IMPORT_C virtual void MakeVisible(TBool aVisible);
    void SetCurrentField( TInt aCurrentField );
    void SetValidateCallBack( TCallBack aCallBack );
    void ReportStateChangeEventL();
    void SetFirstEditableField();
    
private:
	// framework
	IMPORT_C virtual void Draw(const TRect& aRect) const;
	
	// new virtual functions
	IMPORT_C virtual void CreatePopoutIfRequiredL();
	// miscellaneous functions

	/**
	 * Draws the specified fields within the MFNE.
	 * All fields between and including the @c aFirstField and @c aLastField
	 * will be drawn.
	 *
	 * @param  aGc                    The graphics context to draw to.
	 * @param  aFirstField            First field to be drawn.
	 * @param  aLastField             Last field to be drawn.
	 * @param  aSkipBackgroundDrawer  @c ETrue to skip the background drawing
	 *                                with a background drawer if it's used
	 *                                for the MFNE. 
	 */
	void DrawRange( CWindowGc& aGc,
                    TInt aFirstField,
                    TInt aLastField,
                    TBool aSkipBackgroundDrawer = EFalse ) const;

	CWindowGc& PreparedGc() const;
	void SetGcToNormalVideo(CWindowGc& aGc) const;
	void SetGcToInverseVideo(CWindowGc& aGc) const;
	void SetGcToDimmedVideo(CWindowGc& aGc) const;
	void DrawCursor();
	void HideCursor();	
	IMPORT_C void Reserved_2();
	IMPORT_C virtual void CEikMfne_Reserved();
	
	void LaunchPenInputL();
	
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

private:
	enum {ENullIndex=KMaxTInt};

	/**
	 * Access to state of whether up/down keys are eaten and used to increment/decrement.  If
	 * these keys are not consumed, then the events are passed on.
	 * 
	 * @return EFalse iff Up and Down keys are not consumed (and acted upon)
	 */
	TBool ConsumesUpAndDownKeys() const;

	/**
	 * This state of enabling means that skinning will actually be drawn
	 * It is a combination of 
	 * - application is skin enabled
	 * - current skin has a background or frame bitmap
	 * It is set during construction and does not change its value after except if the Skin is 
	 * changed, whereupon the control context is re-accessed and checked for bitmaps present
	 *
	 * @return EFalse iff background skin will not be drawn.
	 */
	TBool SkinningBackground() const;

	/** 
	 * Checks if app is skin enabled and that the current control context has bitmap. 
	 * If so, then state is set true.
	 * This should be called at constuction and when HandleResourceChange is called
	 *
	 */ 
	void EvaluateSkinningBackground(); 

    /**
     * Access to Skins background control context that is potentially being used by the Editor.
     *
     * This API will first check to see if an control context has been set by API, and if so, 
     * return that.  If the background control context has been set to NULL by API, then it will
     * return NULL. If the background control context has never been set by API, then this returns
     * the control context (if one exists) that the object obtains from Object Provider.
     * 
     * @return Pointer to control context potentially in use, or NULL.
     */
    MAknsControlContext* SkinBackgroundControlContext() const;

    /**
     * Check for the existence of the extension and create if required.
     */
    void CreateExtensionIfRequiredL();

private:
	TInt iNumFields;
	TInt iCurrentField;
	CEikMfneField** iFields;
	CEikMfneExtension* iExtension;
	const CFont* iFont;
    TInt iAlignment;
    TBitFlags iFlags;
	};

inline TInt CEikMfne::CurrentField() const
    {
    return(iCurrentField);
    }

inline TInt CEikMfne::NumFields() const
    {
    return(iNumFields);
    }

//

/**
 * Integer editor.
 * 
 * This control supports editing a single integer value. If a number is
 * entered which is not within the range specified by the maximum and
 * minimum control values it is automatically reset to the nearest
 * allowable value.
 * 
 * The editor has an associated resource struct NUMBER_EDITOR and
 * control factory identifier EEikCtNumberEditor.
 */
class CEikNumberEditor : public CEikMfne
	{
public:
	// miscellaneous functions
    
    /**
     * Constructor.
     * 
     * This function should be used as the first stage in two stage
     * construction, followed by a call to either ConstructFromResourceL() to
     * initialise the editor's field values from a resource file, or ConstructL()
     * if no resource file is used.
     */
	IMPORT_C CEikNumberEditor();
	
	/**
     * Second-phase constructor.
     * 
     * Completes the construction of an integer editor. It should be called
     * by container only if the editor is not constructed from a resource.
     * 
     * Sets the minimum and maximum values that can be entered into the
     * editor, and the initial value.
     * 
     * @param aMinimumValue The minimum allowable value.
     * @param aMaximumValue The maximum allowable value.
     * @param aInitialValue The initial value.
     */
	IMPORT_C void ConstructL(TInt aMinimumValue, TInt aMaximumValue, TInt aInitialValue); // to be called by container only if not constructed from resource
	
    /**
     * Sets the minimum and maximum editor values.
     * 
     * Only values inside the initial minimum and maximum are permitted.
     * 
     * If the editor's value is outside the new bounds when the function is
     * called, it is reset to the nearest allowable value.
     * 
     * @param aMinimumValue The minimum allowable value.
     * @param aMaximumValue The maximum allowable value.
     * @panic 9 If the minimum is greater than the maximum allowable value.
     */
	IMPORT_C void SetMinimumAndMaximum(TInt aMinimumValue, TInt aMaximumValue); // only values inside the initial minimum and maximum are permitted

    /**
     * Gets the integer editor's minimum and maximum values.
     * 
     * @param aMinimumValue On return, contains the integer editor's
     * minimum allowable value.
     * @param aMaximumValue On return, contains the integer editor's
     * maximum allowable value.
     */
	IMPORT_C void GetMinimumAndMaximum(TInt& aMinimumValue, TInt& aMaximumValue) const;

    /**
     * Sets the integer editor's value.
     * 
     * The control is not redrawn.
     * 
     * @param aNumber The editor's new value.
     * @panic 11 In debug builds, if aNumber is outside the valid range.
     */
	IMPORT_C void SetNumber(TInt aNumber);

    /**
     * Gets the integer editor's value.
     * 
     * @return The integer editor's value.
     * @panic 12 In debug builds, if the editor has no content.
     */
	IMPORT_C TInt Number() const; // can only be called if PrepareForFocusLossL() succeeded

	// framework

	/**
     * Second-phase construction from a resource file.
     * 
     * The function reads the maximum and minimum editor values from a
     * NUMBER_EDITOR resource, and sets the initial number to be the same as the
     * maximum value.
     * 
     * @param aResourceReader A resource file reader.
     */
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aResourceReader);

    // From CCoeControl

    /**
     * From @c CCoeControl.
     * 
     * Handles pointer events.
     *
     * @param aPointerEvent The pointer event.
     */    
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);	
private:
	IMPORT_C virtual void CEikMfne_Reserved();
private:
	void RefreshFromLocale();
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private:
	// none of these pointers owns anything
	CEikMfneNumber* iNumber;
	TInt iSpare;
	};


//
/**
 * Range struct for CEikRangeEditor.
 */
struct SEikRange
	{
	/**
	 * The lower limit.
	 */
	TInt iLowerLimit;

	/**
	 * The upper limit.
	 */
	TInt iUpperLimit;
	};

//

/**
 * Numeric range editor.
 * 
 * This editor supports editing an integer range. It has two fields;
 * the first represents the lower value and the second the upper value. The
 * second value must be greater than, or equal to, the first.
 * 
 * Minimum and maximum values for the editor are specified during
 * construction. If a number is entered which is not within the editor's
 * minimum and maximum values, it is automatically reset to the nearest
 * allowable value.
 * 
 * The editor has an associated resource struct RANGE_EDITOR and
 * control factory identifier EEikCtRangeEditor. 
 */
class CEikRangeEditor : public CEikMfne
	{
public:
	// miscellaneous functions
    
    /**
     * Default constructor.
     * 
     * This function should be used as the first stage in two stage
     * construction, followed by a call to either ConstructFromResourceL() to
     * initialise the editor's field values from a resource file, or ConstructL()
     * if no resource file is used.
     */
	IMPORT_C CEikRangeEditor();

	// ConstructL to be called by container only if not constructed from resource, also ownership of aSeparatorText is transferred when everything that can leave has successfully been done
    /**
     * Second phase constructor.
     * 
     * This function completes construction of a range editor. It sets the
     * minimum and maximum values, initial range and separator text. It
     * should be called by the container only if the control is not constructed
     * from a resource file. 
     * 
     * @param aMinimumValue The minimum value for the range editor.
     * @param aMaximumValue The maximum value for the range editor.
     * @param aInitialRange Struct containing upper and lower range limits.
     * Must be within the minimum and maximum values.
     * @param aSeparatorText The text to be used to separate the numeric
     * values.
     * @panic 8 If the initial lower or upper limit is outside the minimum
     * or maximum bounds.
     */
	IMPORT_C void ConstructL(TInt aMinimumValue, TInt aMaximumValue, const SEikRange& aInitialRange, HBufC* aSeparatorText);

    /**
     * Sets the range editor's minimum and maximum values.
     * 
     * Any values are permitted. If the range values are outside the new
     * minimum / maximum they are changed to be within the new minimum /
     * maximum.
     * 
     * @param aMinimumValue The minimum value for the range editor.
     * @param aMaximumValue The maximum value for the range editor.
     */
	IMPORT_C void SetMinimumAndMaximum(TInt aMinimumValue, TInt aMaximumValue); // only values inside the initial minimum and maximum are permitted

    /**
     * Gets the range editor's minimum and maximum values.
     * 
     * @param aMinimumValue On return, the minimum value for the range
     * editor.
     * @param aMaximumValue On return, the maximum value for the range
     * editor.
     */
	IMPORT_C void GetMinimumAndMaximum(TInt& aMinimumValue, TInt& aMaximumValue) const;

    /**
     * Sets the range editor's current values.
     * 
     * @param aRange Struct containing new range values.
     */
	IMPORT_C void SetRange(const SEikRange& aRange);
	
    /**
     * Gets the range editor's current values.
     * 
     * Can only be called if CEikMfne::PrepareForFocusLossL() succeeded
     * 
     * @return Struct containing current range values.
     */
	IMPORT_C SEikRange Range() const; // can only be called if PrepareForFocusLossL() succeeded
	
	// framework
	
    /**
     * Second phase constructor from resource.
     * 
     * This function completes construction of a newly-allocated range
     * editor. It sets the minimum and maximum values, initial range and
     * separator text as specified by the resource.
     * 
     * @param aResourceReader A resource reader.
     */
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aResourceReader);

    // From CCoeControl

    /**
     * From @c CCoeControl.
     * 
     * Handles pointer events.
     *
     * @param aPointerEvent The pointer event.
     */    
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
private:
	virtual void FieldIsAboutToBeDeHighlighted(CEikMfneField* aField, TBool& aDrawAllFields);
	IMPORT_C virtual void CEikMfne_Reserved();
	void RefreshFromLocale();
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private:
	// none of these pointers owns anything
	CEikMfneNumber* iLowerLimit;
	CEikMfneNumber* iUpperLimit;
	TInt iSpare;
	};


//

/**
 * Specifies an abstract interface for time and date editors where the
 * time and date are set and retrieved using the TTime class.
 */
class CEikTTimeEditor : public CEikMfne
	{
public:
    /**
     * An implementation (of this pure virtual function) should set the
     * range of allowable time values.
     * 
     * This defines the maximum and minimum values that may be entered by
     * the user. 
     * 
     * @param aMinimumTime The minimum allowable value.
     * @param aMaximumTime The maximum allowable value.
     */
	virtual void SetMinimumAndMaximum(const TTime& aMinimumTime, const TTime& aMaximumTime)=0;

    /**
     * An implementation (of this pure virtual function) should get the
     * range of allowable time values.
     * 
     * @param aMinimumTime The minimum allowable value.
     * @param aMaximum The maximum allowable value.
     */
	virtual void GetMinimumAndMaximum(TTime& aMinimumTime, TTime& aMaximum) const=0;
    
    /**
     * An implementation (of this pure virtual function) should set the time
     * in the editor.
     * 
     * @param aTime The time.
     */
	virtual void SetTTime(const TTime& aTime)=0;

    /**
     * An implementation (of this pure virtual function) should get the time
     * from the editor.
     * 
     * Can only be called if CEikMfne::PrepareForFocusLossL() succeeded.
     * 
     * @return The time.
     */
	virtual TTime GetTTime() const=0; // can only be called if PrepareForFocusLossL() succeeded
	};

/**
 * Time editor.
 * 
 * This control allows a time value to be displayed and edited. By
 * default the editor has hours, minutes and seconds fields, although the
 * seconds and hours fields may be omitted. 12 and 24-hour format are
 * supported. When 12-hour format is used, am or pm text will be included as
 * another field, either before or after the time. Locale information is
 * used to determine the time separator characters. Locale information is
 * set and retrieved using class TLocale. 
 * 
 * The upper and lower field bounds are set depending on the format,
 * and times outside these bounds are invalid.
 * 
 * The editor has an associated resource struct TIME_EDITOR and control
 * factory identifier EEikCtTimeEditor. 
 */
class CEikTimeEditor : public CEikTTimeEditor
	{
public:
	// miscellaneous functions
    /**
     * Default constructor.
     * 
     * This function should be used as the first stage in two stage
     * construction, followed by a call to either: ConstructFromResourceL() to
     * initialise the editor's field values from a resource file, or ConstructL()
     * if no resource file is used.
     */
	IMPORT_C CEikTimeEditor();

    /**
     * Destructor.
     * 
     * This frees the resources owned by the time editor, prior to its
     * destruction.
     */
	IMPORT_C virtual ~CEikTimeEditor();

    /**
     * Second phase construction.
     * 
     * This function completes the construction of a newly-allocated time
     * editor, by setting its minimum, maximum and initial values, and the
     * AM/PM text settings - the AM/PM settings and time separator characters
     * specified in class TLocale are honoured. It should be called by the
     * container only if the control is not constructed from a resource file.
     * 
     * If the initial time is outside the bounds specified, it is reset to
     * the nearest available setting.
     * 
     * The aFlags parameter is used to determine whether the seconds or
     * hours fields are required. The minutes field is always present. It may
     * also be used to specify whether or not to force 24 hour time format,
     * overriding the locale's setting.
     * 
     * A panic will occur if the minimum time is later than the maximum
     * time.
     * 
     * @param aMinimumTime The minimum allowable time.
     * @param aMaximumTime The maximum allowable time.
     * @param aInitialTime The initial time.
     * @param aFlags Determines which fields are required and whether or
     * not to force 24 hour formatting. See eikon.hrh EEiktime etc.
     */
	IMPORT_C void ConstructL(const TTime& aMinimumTime, const TTime& aMaximumTime, const TTime& aInitialTime, TUint32 aFlags); // to be called by container only if not constructed from resource

    /**
     * Sets the time editor's value.
     * 
     * @param aTime The new value to which to set the editor's fields.
     */
	IMPORT_C void SetTime(const TTime& aTime);

    /**
     * Gets the time editor's value.
     * 
     * @return The editor's value. (Date values are all zero.)
     */
	IMPORT_C TTime Time() const;

    /**
     * Sets the uninitialized status of the editor.
     * 
     * @param aUninitialised If ETrue, sets the editor as uninitialized,
     *                       i.e. it doesn't display anything.
     */
	IMPORT_C void SetUninitialised(TBool aUninitialised);
	
	/**
	 * Gets the uninitialized status of the editor.
	 * 
	 * @return ETrue, if the editor is set as uninitialized.
	 */	
	IMPORT_C TBool IsUninitialised() const;
	// from CEikTTimeEditor
	
    /**
     * Sets the range of allowable time values.
     * 
     * These define the maximum and minimum values that may be entered by
     * the user.
     * 
     * If the existing time value is outside the bounds set by this
     * function, it is reset to the nearest boundary value.
     * 
     * @param aMinimumTime The minimum allowable value.
     * @param aMaximumTime The maximum allowable value.
     * @panic 38 If the minimum value exceeds the maximum.
     */
	IMPORT_C virtual void SetMinimumAndMaximum(const TTime& aMinimumTime, const TTime& aMaximumTime); // only values inside the initial minimum and maximum are permitted

    /**
     * Gets the range of allowable values that may be entered by the user.
     * 
     * @param aMinimumTime On return, contains the time editor's minimum
     * allowable value.
     * @param aMaximumTime On return, contains the time editor's maximum
     * allowable value.
     */
	IMPORT_C virtual void GetMinimumAndMaximum(TTime& aMinimumTime, TTime& aMaximumTime) const;

	// from CCoeControl

    /**
     * Second phase construction from a resource.
     * 
     * This function completes the construction of a newly-allocated time
     * editor from a TIME_EDITOR resource. The minimum and maximum times, and
     * the flags settings are read from the resource, and ConstructL() is
     * called with these settings. The initial time is set to the maximum time
     * value. Honours the locale's AM/PM text setting and time separators.
     * 
     * @param aResourceReader A resource file reader.
     * 
     */
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aResourceReader);
	
    /**
     * Prepares the editor for focus loss.
     * 
     * This function should be called to validate the editor's contents
     * when an attempt is made to remove focus from the control. If the control
     * value is not within the bounds specified by the minimum and maximum
     * time values, it is reset to the nearest allowable value, the function
     * will leave and will display an appropriate message.
     */
	IMPORT_C virtual void PrepareForFocusLossL();

    /**
     * From @c CCoeControl.
     * 
     * Handles pointer events.
     *
     * @param aPointerEvent The pointer event.
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
private:
	// from CEikTTimeEditor
	virtual void SetTTime(const TTime& aTime);
	virtual TTime GetTTime() const; // can only be called if PrepareForFocusLossL() succeeded
private:
	// miscellaneous functions
	void DoSetMinimumAndMaximum(const TTime& aMinimumTime, const TTime& aMaximumTime);
	IMPORT_C virtual void CEikMfne_Reserved();
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private:
	CTimeEditor* iTimeEditor;
	TTime iMinimumTime;
	TTime iMaximumTime;
	TInt iSpare;
	};


//

// note: TDateTime uses zero based day numbers, so -1 on the day field
#define KAknMinimumDate (TTime(TDateTime(0001, EJanuary, 1-1, 0, 0, 0, 0)))
#define KAknMaximumDate (TTime(TDateTime(9999, EDecember, 31-1, 23, 59, 59, 999999)))

/**
 * Date editor.
 *
 * A date editor has five fields: day, month and year, and two separator 
 * characters. The order of the fields varies depending on the locale's 
 * date format setting. Locale information, which is set and retrieved using 
 * class @c TLocale, is used to determine field order and the characters used 
 * to separate the date components. The upper and lower field bounds are set, 
 * and dates outside these bounds are invalid.
 *
 * The editor can be configured to launch a pop-out calendar dialog, 
 * @c CEikCalendar. This may be used to directly set the day, month and year 
 * values. 
 *
 * The editor has an associated resource struct @c DATE_EDITOR and control 
 * factory identifier @c EEikCtDateEditor.
 *
 */
class CEikDateEditor : public CEikTTimeEditor, private MEikCalendarObserver
	{

public:

    // miscellaneous functions
    /**
     * C++ default constructor.
     */
    IMPORT_C CEikDateEditor();

    /**
     * Destructor.
     */
    IMPORT_C virtual ~CEikDateEditor();

    // to be called by container only if not constructed from resource
    /**
     * Handles 2nd phase construction.
     *
     * This function completes the construction of a newly-allocated date 
     * editor. This function should be used instead of 
     * @c ConstructFromResourceL() when not initialising from a resource file.
     * The editor's minimum, maximum and initial date values are set and the 
     * date format and date separator characters specified in class @c TLocale
     * are honoured.
     * 
     * @param aMinimumDate The minimum allowable date.
     * @param aMaximumDate The maximum allowable date.
     * @param aInitialDate The initial value.
     * @param aWithoutPopoutCalendar If @c ETrue the editor will not have a 
     *        pop-out calendar dialog / icon. If @c EFalse the editor will have
     *        a pop-out calendar dialog / icon.
     */
    IMPORT_C void ConstructL(const TTime& aMinimumDate, 
                             const TTime& aMaximumDate, 
                             const TTime& aInitialDate, 
                             TBool aWithoutPopoutCalendar); 
    
    /**
     * Sets the date editor's value.
     * 
     * @param aDate The editor's value. Time components are ignored.
     */
    IMPORT_C void SetDate(const TTime& aDate);

    /**
     * Gets the date editor's value.
     *
     * @return The editor's date value.
     */
	IMPORT_C TTime Date() const;

    /**
     * Sets date editor to initialised or uninitialised.
     * 
     * @param aUninitialised If @c ETrue then the date editor is set 
     *        to be uninitialised.
     */
	IMPORT_C void SetUninitialised(TBool aUninitialised);

    /**
     * Tests whether the editor is uninitialised.
     * 
     * @return @c ETrue if uninitialised.
     */
	IMPORT_C TBool IsUninitialised() const;

	// from CEikTTimeEditor
	// only values inside the initial minimum and maximum are permitted
    /**
     * From @c CEikTTimeEditor.
     * 
     * Sets the minimum and maximum allowable dates.
     *
     * If the current date is outside the new bounds it is changed to be within
     * them.
     *
     * @param aMinimumDate The minimum allowable value.
     * @param aMaximumDate The maximum allowable value.
     */
    IMPORT_C virtual void SetMinimumAndMaximum(const TTime& aMinimumDate, 
                                               const TTime& aMaximumDate); 
    	
    /**
     * From @c CEikTTimeEditor.
     *
     * Gets the date editor's minimum and maximum values.
     *
     * @param aMinimumDate On return, the minimum allowable value.
     * @param aMaximumDate On return, the maximum allowable value.
     */
    IMPORT_C virtual void GetMinimumAndMaximum(TTime& aMinimumDate, 
                                               TTime& aMaximumDate) const;
	
    // from CCoeControl
    /**
     * From @c CCoeControl.
     *
     * Handles key events.
     *
     * @param aKeyEvent The key event.
     * @param aType The type of key event.
     * @return @c EKeyConsumed if the key has beend handled. 
     */
    IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, 
                                                 TEventCode aType);
	
    /**
     * From @c CCoeControl.
     * 
     * Second-phase construction from a resource file.
     *
     * The function reads the maximum and minimum date values and whether 
     * or not the editor should support a pop-out calendar and/or date icon 
     * from a @c DATE_EDITOR resource. It sets the initial date to be the same 
     * as the maximum date and honours the locale's date format and separators.
     * 
     * @param aResourceReader A resource file reader.
     */
    IMPORT_C virtual void ConstructFromResourceL(TResourceReader& 
                                                 aResourceReader);
	
    /**
     * From @c CCoeControl.
     * 
     * Editor validation.
     *
     * This function should be called before an attempt is made to remove focus
     * from a date editor. If the control value is not within the bounds 
     * specified by the minimum and maximum date values, it is reset to the 
     * nearest allowable value, the function then leaves.
     */
    IMPORT_C virtual void PrepareForFocusLossL();
    
    /**
     * From @c CCoeControl.
     * 
     * Handles pointer events.
     *
     * @param aPointerEvent The pointer event.
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

private:

    // from CEikMfne
    virtual void CreatePopoutIfRequiredL();
    // from CEikTTimeEditor
    virtual void SetTTime(const TTime& aDate);
    virtual TTime GetTTime() const; // can only be called if PrepareForFocusLossL() succeeded

private:

    // from MEikCalendarDialogObserver
    virtual void GetMinimumAndMaximumAndInitialDatesForCalendarL(TTime& aMinimumDate, 
                                                                 TTime& aMaximumDate, 
                                                                 TTime& aInitialDate) const;
    virtual void SetDateFromCalendarAndDrawNow(const TTime& aDate);
    // miscellaneous functions
    void DoSetMinimumAndMaximum(const TTime& aMinimumDate, const TTime& aMaximumDate);
    IMPORT_C virtual void CEikMfne_Reserved();

private:

    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

private:

	CDateEditor* iDateEditor;
	TTime iMinimumDate;
	TTime iMaximumDate;
	TInt iSpare;
	};


//

/**
 * Time and date editor.
 * 
 * This control allows both a time and date to be displayed and edited.
 * It contains the following time fields: hours, minutes and seconds,
 * two time separator characters and am/pm text, and the following date
 * fields: year, month and day, with two date separator characters. The
 * seconds and hours fields are optional and the order of the date fields and
 * the separator characters are locale-dependent. The upper and lower
 * field bounds are set, and dates and times outside these bounds are
 * invalid.
 * 
 * Date field values may be edited directly or via a pop-out calendar
 * dialog.
 * 
 * The editor has an associated resource struct TIME_AND_DATE_EDITOR
 * and control factory identifier EEikCtTimeAndDateEditor. 
 */
class CEikTimeAndDateEditor : public CEikTTimeEditor, private MEikCalendarObserver
	{
public:
	// miscellaneous functions

    /**
     * Default constructor.
     * 
     * This function should be used as the first stage in two stage
     * construction, followed by a call to either ConstructFromResourceL() to
     * initialise the editor's field values from a resource file, or ConstructL()
     * (if no resource file is used). 
     */
	IMPORT_C CEikTimeAndDateEditor();

    /**
     * Destructor. 
     * 
     * This frees the resources owned by the time and date editor, prior to
     * its destruction.
     */
	IMPORT_C virtual ~CEikTimeAndDateEditor();

	// ConstructL to be called by container only if not constructed from resource, also ownership of aInterveningText is transferred when everything that can leave has successfully been done

    /**
     * Second phase construction.
     * 
     * This function completes construction of a newly-allocated date and
     * time editor, by setting the minimum, maximum and initial date and time
     * values. It should be called by the container only if the control is
     * not constructed from a resource file.
     * 
     * The aFlags parameter is used to set whether the seconds or hours
     * fields are not required. The minutes field is always present. It may also
     * be used to specify whether or not to force 24 hour time format,
     * overriding the locale's setting, and whether the editor should have a
     * pop-out calendar dialog.
     * 
     * The locale-dependant date and time settings specified in class
     * TLocale are honoured.
     * 
     * If the initial date/time is outside the bounds specified by the
     * minimum and maximum, it is set to the nearest valid setting.
     * 
     * A panic will occur if the minimum date/time is later than the
     * maximum date/time.
     * 
     * @param aMinimumTimeAndDate The minimum date and time value.
     * @param aMaximumTimeAndDate The maximum date and time value.
     * @param aInitialTimeAndDate The initial date and time value.
     * @param aFlags A bitmask of flags. See eikon.hrh file, EEikTime,
     * EEikDate etc.
     * @param aInterveningText Descriptor containing the text to use to
     * separate the time and date portions of the editor.     
     */
	IMPORT_C void ConstructL(const TTime& aMinimumTimeAndDate, const TTime& aMaximumTimeAndDate, const TTime& aInitialTimeAndDate, TUint32 aFlags, HBufC* aInterveningText=NULL);
	
    /**
     * Sets the values of the time and date editor's fields.
     * 
     * @param aTimeAndDate The new value for the date and time editor's
     * fields.
     */
	IMPORT_C void SetTimeAndDate(const TTime& aTimeAndDate);

    /**
     * Gets the time and date editor's value.
     * 
     * @return The editor's value.
     */
	IMPORT_C TTime TimeAndDate() const;

    /**
     * Sets the uninitialized status of the editor.
     * 
     * @param aUninitialised If ETrue, sets the editor as uninitialized,
     *                       i.e. it doesn't display anything.
     */
	IMPORT_C void SetUninitialised(TBool aUninitialised);
	
	/**
	 * Gets the uninitialized status of the editor.
	 * 
	 * @return ETrue, if the editor is set as uninitialized.
	 */	
	IMPORT_C TBool IsUninitialised() const;
	
	// from CEikTTimeEditor

    /**
     * Sets the range of allowable values.
     * 
     * These define the maximum and minimum time/date values that may be
     * entered by the user.
     * 
     * If the existing date/time value is outside the new bounds, it is
     * reset to the nearest allowable value.
     * 
     * @param aMinimumTimeAndDate The minimum allowable value.
     * @param aMaximumTimeAndDate The maximum allowable value.
     */
	IMPORT_C virtual void SetMinimumAndMaximum(const TTime& aMinimumTimeAndDate, const TTime& aMaximumTimeAndDate); // only values inside the initial minimum and maximum are permitted

    /**
     * Gets the range of allowable values that may be entered by the user.
     * 
     * @param aMinimumTimeAndDate On return, contains the time and date
     * editor's minimum allowable value.
     * @param aMaximumTimeAndDate On return, contains the time and date
     * editor's maximum allowable value.
     */
	IMPORT_C virtual void GetMinimumAndMaximum(TTime& aMinimumTimeAndDate, TTime& aMaximumTimeAndDate) const;

	// from CCoeControl
	
    /**
     * Handles key events.
     * 
     * For example, the Tab key validates and launches a calendar popout.
     * 
     * Calls CEikMfne::OfferKeyEventL() if the control does not consume the
     * key.
     * 
     * @param aKeyEvent The key event.
     * @param aType The type of key event.
     * @return Returns EKeyWasConsumed if the control consumes the key.
     */
	IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

    /**
     * Second phase construction from a resource.
     * 
     * This function completes the construction of a newly-allocated
     * date/time editor from a TIME_AND_DATE_EDITOR resource. The minimum and
     * maximum date/times, the date and time flag settings, and the intervening
     * text are read from the resource, and ConstructL() is called with these
     * settings. The initial date/time is set to the maximum date/time value. 
     * 
     * @param aResourceReader A resource file reader.
     */
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aResourceReader);

    /**
     * Prepares the editor for focus loss.
     * 
     * This function should be called to validate the editor's contents
     * when an attempt is made to remove focus from the control. If the control
     * value is not within the bounds specified by the minimum and maximum
     * date/time values, it is reset to the nearest allowable value, the
     * function will leave and display an appropriate message.
     */
	IMPORT_C virtual void PrepareForFocusLossL();

    /**
     * From @c CCoeControl.
     * 
     * Handles pointer events.
     *
     * @param aPointerEvent The pointer event.
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);	
    
private:
	// from CEikMfne
	virtual void CreatePopoutIfRequiredL();	
	IMPORT_C virtual void CEikMfne_Reserved();
	// from CEikTTimeEditor
	virtual void SetTTime(const TTime& aTimeAndDate);
	virtual TTime GetTTime() const; // can only be called if PrepareForFocusLossL() succeeded
private:
	// from MEikCalendarDialogObserver
	virtual void GetMinimumAndMaximumAndInitialDatesForCalendarL(TTime& aMinimumDate, TTime& aMaximumDate, TTime& aInitialDate) const;
	virtual void SetDateFromCalendarAndDrawNow(const TTime& aDate);
	// miscellaneous functions
	void DoSetMinimumAndMaximum(const TTime& aMinimumTimeAndDate, const TTime& aMaximumTimeAndDate);
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private:
	CTimeEditor* iTimeEditor;
	CDateEditor* iDateEditor;
	TTime iMinimumTimeAndDate;
	TTime iMaximumTimeAndDate;
	TInt iSpare;
	};


//

/**
 * Duration editor.
 * 
 * The duration editor allows a time duration to be displayed and
 * edited. The editor has a clock icon and an edit field with separators for
 * hours, minutes, and seconds. These fields can all be suppressed using
 * the appropriate flags in the resource declaration.
 * 
 * Unlike the time editor control, the duration editor has no am or pm
 * text. This is because the duration is a length of time (from 0 to 24
 * hours), rather than a point in time.
 * 
 * The minimum and maximum values are set, and values outside these
 * limits are invalid.
 * 
 * The editor has an associated resource struct DURATION_EDITOR and
 * control factory identifier EEikCtDurationEditor. 
 */
class CEikDurationEditor : public CEikMfne
	{
public:
	// miscellaneous functions

    /**
     * Default constructor.
     * 
     * This function should be used as the first stage in two stage
     * construction, followed by a call to either ConstructFromResourceL() to
     * initialise the editor's field values from a resource file, or ConstructL()
     * if no resource file is used.
     */
	IMPORT_C CEikDurationEditor();

    /**
     * Destructor.
     * 
     * The destructor frees the resources owned by the duration editor,
     * prior to its destruction.
     */
	IMPORT_C virtual ~CEikDurationEditor();

    /**
     * Second phase construction.
     * 
     * This function completes the construction of a newly-allocated
     * duration editor. This function should be used instead of
     * ConstructFromResourceL() when not initialising from a resource file.
     * 
     * The function sets the editor's minimum, maximum and initial values.
     * The time separator characters specified in class TLocale are honoured.
     * If the initial duration is less than the minimum value the minimum
     * value is used as the initial setting. If the initial duration is greater
     * than the maximum value the maximum value is used as the initial
     * setting.
     * 
     * The aFlags parameter is used to determine whether the seconds or
     * hours fields are not required. The minutes field is always present.
     * Regardless of the value specified in aFlags, 24 hour time format is set,
     * overriding the locale's setting.
     * 
     * @param aMinimumDuration The minimum interval in seconds.
     * @param aMaximumDuration The maximum interval in seconds.
     * @param aInitialDuration The initial interval in seconds.
     * @param aFlags Duration editor flags.
     */
	IMPORT_C void ConstructL(const TTimeIntervalSeconds& aMinimumDuration, const TTimeIntervalSeconds& aMaximumDuration, const TTimeIntervalSeconds& aInitialDuration, TUint32 aFlags);

    /**
     * Sets the minimum and maximum duration values.
     * 
     * The user can only enter values between these bounds.
     * 
     * @param aMinimumDuration The minimum duration.
     * @param aMaximumDuration The maximum duration.
     * @panic 48 If the minimum duration exceeds the maximum.
     */
	IMPORT_C void SetMinimumAndMaximum(const TTimeIntervalSeconds& aMinimumDuration, const TTimeIntervalSeconds& aMaximumDuration); // only values inside the initial minimum and maximum are permitted

    /**
     * Gets the duration editor's minimum and maximum values.
     * 
     * @param aMinimumDuration On return, the minimum value.
     * @param aMaximumDuration On return, the maximum value.
     */
	IMPORT_C void GetMinimumAndMaximum(TTimeIntervalSeconds& aMinimumDuration, TTimeIntervalSeconds& aMaximumDuration) const;

    /**
     * Sets the duration editor's value.
     * 
     * @param aDuration The new value to convert into hours, minutes and
     * seconds and to which the duration editor's fields will be set.
     */
	IMPORT_C void SetDuration(const TTimeIntervalSeconds& aDuration);

    /**
     * Gets the duration editor's value and returns it as a period of
     * seconds.
     * 
     * @return The editor's value in seconds.
     */
	IMPORT_C TTimeIntervalSeconds Duration() const; // can only be called if PrepareForFocusLossL() succeeded

	// framework

    /**
     * Second-phase construction from a resource.
     * 
     * The function reads the maximum and minimum duration values, and the
     * flags settings, from a DURATION_EDITOR resource. It sets the initial
     * duration to be the same as the maximum value and honours the locale's
     * time separators.
     * 
     * @param aResourceReader A resource file reader.
     */
	IMPORT_C void ConstructFromResourceL(TResourceReader& aResourceReader);

    /**
     * Editor validation.
     * 
     * This function should be called when an attempt is made to remove
     * focus from a duration editor. If the editor value is not within the
     * bounds specified by the minimum and maximum duration values, it is reset to
     * the nearest allowable value - the function will leave.
     */
	IMPORT_C void PrepareForFocusLossL();

    // From CCoeControl    
    /**
     * From @c CCoeControl.
     * 
     * Handles pointer events.
     *
     * @param aPointerEvent The pointer event.
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);	
private:
	// miscellaneous functions
	void DoSetMinimumAndMaximum(const TTimeIntervalSeconds& aMinimumDuration, const TTimeIntervalSeconds& aMaximumDuration);
	IMPORT_C virtual void CEikMfne_Reserved();
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private:
	CTimeEditor* iTimeEditor;
	TTimeIntervalSeconds iMinimumDuration;
	TTimeIntervalSeconds iMaximumDuration;
	TInt iSpare;
	};

/**
 * Time offset editor.
 * 
 * This control allows a signed time offset to be displayed and edited.
 * It has the same fields as the time editor control CEikTimeEditor,
 * except there is no AM or PM text because the value is a time offset,
 * positive or negative, from 0 to 24 hours rather than a point in time.
 * 
 * The editor has an associated resource struct TIME_OFFSET_EDITOR and
 * control factory identifier EEikCtTimeOffsetEditor. 
 */
class CEikTimeOffsetEditor : public CEikMfne
	{
public:
	// miscellaneous functions

    /**
     * Default constructor.
     * 
     * This function should be used as the first stage in two stage
     * construction, followed by a call to either ConstructFromResourceL() to
     * initialise the editor's field values from a resource file, or ConstructL()
     * if no resource file is used.
     */
	IMPORT_C CEikTimeOffsetEditor();

    /**
     * Destructor. This frees the resources owned by the time offset editor,
     * prior to its destruction.
     */
	IMPORT_C virtual ~CEikTimeOffsetEditor();

    /**
     * Second phase constructor.
     * 
     * This function completes the construction of a time offset editor, by
     * setting its minimum, maximum and initial values. The time separator
     * characters specified in the system's locale are honoured. It should be
     * called by the container only if the control is not constructed from a
     * resource file.
     * 
     * The aFlags parameter is used to determine whether the seconds or
     * hours fields are displayed by the editor. The minutes field is always
     * displayed. This function forces 24 hour time format for the time offset
     * editor, overriding the locale's setting.
     * 
     * If the initial time offset is outside the bounds specified, it is
     * invalid and will be reset to the upper or lower bound.
     * 
     * The minimum value for a time offset editor is -23:59:59, and the
     * maximum value is 23:59:59.
     * 
     * @param aMinimumTimeOffset The minimum allowable value, in seconds.
     * @param aMaximumTimeOffset The maximum allowable value, in seconds.
     * @param aInitialTimeOffset The initial value, in seconds.
     * @param aFlags Determines which fields are required. Specify
     * CTimeEditor::EWithoutSecondsField for no seconds field,
     * CTimeEditor::EWithoutHoursField for no hours field. 24 hour clock format is set, regardless
     * of the flag setting specified in this parameter.
     */
	IMPORT_C void ConstructL(const TTimeIntervalSeconds& aMinimumTimeOffset, const TTimeIntervalSeconds& aMaximumTimeOffset, const TTimeIntervalSeconds& aInitialTimeOffset, TUint32 aFlags);

    /**
     * Sets the range of allowable offset values. 
     * 
     * These define the maximum and minimum values that may be entered by
     * the user.
     * 
     * If the existing offset value is outside the bounds set by this
     * function, it is reset to the nearest boundary value.
     * 
     * @param aMinimumTimeOffset The minimum allowable value.
     * @param aMaximumTimeOffset The maximum allowable value.
     * @panic 49 If the minimum exceeds the maximum.
     */
	IMPORT_C void SetMinimumAndMaximum(const TTimeIntervalSeconds& aMinimumTimeOffset, const TTimeIntervalSeconds& aMaximumTimeOffset); // only values inside the initial minimum and maximum are permitted

    /**
     * Gets the range of allowable values that may be entered by the user.
     * 
     * @param aMinimumTimeOffset On return, contains the time offset
     * editor’s minimum allowable value.
     * @param aMaximumTimeOffset On return, contains the time offset
     * editor’s maximum allowable value.
     */
	IMPORT_C void GetMinimumAndMaximum(TTimeIntervalSeconds& aMinimumTimeOffset, TTimeIntervalSeconds& aMaximumTimeOffset) const;

    /**
     * Sets the time offset editor's value.
     * 
     * The sign is set according to whether the value specified is positive
     * or negative.
     * 
     * @param aTimeOffset The new offset value to which to assign to the
     * editor.
     */
	IMPORT_C void SetTimeOffset(const TTimeIntervalSeconds& aTimeOffset);

    /**
     * Gets the time offset editor's value converted into seconds.
     * 
     * @return The editor's value in seconds.
     */
	IMPORT_C TTimeIntervalSeconds TimeOffset() const; // can only be called if PrepareForFocusLossL() succeeded

	// framework

    /**
     * Second phase construction from a resource. 
     * 
     * This function completes the construction of a time offset editor
     * from a TIME_OFFSET_EDITOR resource.
     * 
     * The minimum and maximum time offsets, and the flags settings are
     * read from the resource, and ConstructL() is called with these settings.
     * The initial time offset is set to the maximum time offset value.
     * 
     * @param aResourceReader A resource file reader.
     */
	IMPORT_C void ConstructFromResourceL(TResourceReader& aResourceReader);

    /**
     * Prepares editor for focus loss.
     * 
     * This function should be called to validate the editor’s contents
     * when an attempt is made to remove focus from the control.
     * 
     * If the control value is not within the bounds specified by the
     * minimum and maximum time offset values, it is reset to the nearest
     * allowable value. The function then leaves.
     */
	IMPORT_C void PrepareForFocusLossL();

    // From CCoeControl    

    /**
     * From @c CCoeControl.
     * 
     * Handles pointer events.
     *
     * @param aPointerEvent The pointer event.
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);	
    
private:
	// miscellaneous functions
	void DoSetMinimumAndMaximum(const TTimeIntervalSeconds& aMinimumTimeOffset, const TTimeIntervalSeconds& aMaximumTimeOffset);
	IMPORT_C virtual void CEikMfne_Reserved();
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private:
	CTimeEditor* iTimeEditor;
	TTimeIntervalSeconds iMinimumTimeOffset;
	TTimeIntervalSeconds iMaximumTimeOffset;
	// none of these pointers owns anything
	CEikMfneSymbol* iSign;
	TInt iSpare;
	};


//
// Longitude and Latitude editors removed 2.4.2002:

enum
	{
	EEikOrientationNorthSouth   =0x1000,
	EEikOrientationWestEast     =0x2000,
	EEikOrientationMask=EEikOrientationNorthSouth|EEikOrientationWestEast
	};


enum
	{
	EEikDirectionNegative,
	EEikDirectionPositive,
	EEikDirectionMask=EEikDirectionNegative|EEikDirectionPositive
	};


enum TEikCompass
	{
	EEikCompassNorth=EEikOrientationNorthSouth|EEikDirectionNegative,
	EEikCompassSouth=EEikOrientationNorthSouth|EEikDirectionPositive,
	EEikCompassEast=EEikOrientationWestEast|EEikDirectionNegative,
	EEikCompassWest=EEikOrientationWestEast|EEikDirectionPositive
	};


struct SEikDegreesMinutesDirection
	{
	TInt iDegrees;
	TInt iMinutes;
	TInt iSeconds;
	TEikCompass iDirection;
	};

#endif  // __EIKMFNE_H__
// End of file
