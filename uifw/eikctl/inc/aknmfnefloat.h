/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Floating point field for CEikMfne
*
*/

 
#ifndef CAKNMFNEFLOAT_H
#define CAKNMFNEFLOAT_H

#include <eikmfne.h>

/**
 * A floating point field for multi-field numeric editors.
 * 
 * Features of this field:
 * - Functions NOT exported, header file NOT exported anywhere. Commented
 *   for convenience.
 * - Fixed number of fractional digits, to implement the logic seen
 *   in other MFNE's. Can be zero or more, although using a value
 *   greater than ~15 doesn't really make sense (nor is it tested)
 * - Togglable support for NaN value. In case the field is left empty
 *   and NaN is allowed, the field's value equals NaN. Also if the value
 *   is set to be NaN, the field appears to be empty.
 * - Localization support with the CEikMfneNumber-type functions.
 *
 * @lib eikctl.lib
 * @since S60 v3.2
 */
NONSHARABLE_CLASS( CAknMfneFloat ) : public CEikMfneField
    {
public:

    /**
     * Field's flags 
     */
    enum TFlags
        {
        /** If set, the field will allow an empty (NaN) value */
        EAllowNaN = 0x0001
        };

    /**
     * Used to determine what characters are allowed in HandleKey().
     * iAllowedInputFlags is a combination of these. These
     * are pretty self-explanatory.
     */
    enum TAllowedInputFlags
        {
        EDigit            = 0x0001,
        EDecimalSeparator = 0x0002,
        EMinusSign        = 0x0004
        };

    virtual ~CAknMfneFloat();

    /**
     * Creates a new CAknMfneFloat field.
     * To complete construction, call the following functions after this:
     * - SetFlags(), if needed
     * - SetLimits()
     * - SetValue()
     *
     * @since S60 v3.2
     * @param aMaxFractionalDigits The maximum number of fractional digits
     * @return The new CAknMfneFloat object
     */
    static CAknMfneFloat* NewL(
        TInt aMaxFractionalDigits);

    /**
     * Set the minimum and maximum limits.
     *
     * @since S60 v3.2
     * @param aMinimumValue The minimum value
     * @param aMaximumValue The maximum value
     * @return If ETrue, the call caused field's value to change
     */
    TBool SetLimits(
        TReal aMinimumValue,
        TReal aMaximumValue);

    /**
     * Gets the limits
     *
     * @since S60 v3.2
     * @param aMinimumValue On return, the minimum value
     * @param aMaximumValue On return, the maximum value
     */     
    void GetLimits(
        TReal& aMinimumValue,
        TReal& aMaximumValue) const;

    /**
     * Sets the value of the field
     *
     * @since S60 v3.2
     * @param aValue The value to be set
     * @return ETrue, if the value was valid and not changed. The value is
     *         also considered to be valid in case it is rounded to the
     *         limits of the editor's maximum fractional digits.
     */
    TBool SetValue( TReal aValue );
    
    /**
     * Gets the value currently in the field
     *
     * @since S60 v3.2
     * @return The value in the field, parsed by TLex
     */
    TReal Value() const;
    
    /**
     * Calls SetTextFromValueAndNormalize() with the value parsed from
     * the current text.
     *
     * @since S60 v3.2
     * @return ETrue, if the value was significantly changed while
     *         normalizing.
     */
    TBool NormalizeValue();
    
    /**
     * Sets the maximum number of fractional digits.
     *
     * @since S60 v3.2
     * @param aMaxFractionalDigits The maximum number of fractional digits.
     */
    void SetMaxFractionalDigits( TInt aMaxFractionalDigits );
    
    /**
     * Gets the maximum number of fractional digits.
     *
     * @since S60 v3.2
     * @return The maximum number of fractional digits.
     */
    TInt MaxFractionalDigits() const;
    
    /**
     * Sets the field's digit type to match the current number type,
     * as set from General Settings. Calls SetDigitType().
     *
     * @since S60 v3.2
     */
    void RefreshDigitType();
    
    /**
     * Sets the field's digit type.
     *
     * @since S60 v3.2
     * @param aDigitType The digit type to be set.
     */
    void SetDigitType( TDigitType aDigitType );
    
    /**
     * Gets the field's digit type.
     *
     * @since S60 v3.2
     * @return The field's digit type.
     */
    TDigitType DigitType() const;

    /**
     * Sets the field's flags.
     *
     * @since S60 v3.2
     * @param aFlags The flags to be set, see TFlags.
     */
    void SetFlags( TUint aFlags );
    
    /**
     * Gets the field's flags.
     *
     * @since S60 v3.2
     * @return The field's flags.
     */
    TUint Flags() const;
    
private:

    CAknMfneFloat( TInt aMaxFractionalDigits );

    void ConstructL();

// From CEikMfneField

public:

    TInt MaximumWidthInPixels(
        const CFont& aFont,
        TBool aShrinkToMinimumSize);

    TCoeInputCapabilities InputCapabilities() const;

    TBool IsEditable() const;

    // these functions may only be called if
    // IsEditable returns ETrue - all TBool&/TInt& parameters
    // in these functions must be first set to EFalse/0 by the caller
    THighlightType HighlightType() const;

    void HandleKey(
        const CFont& aFont,
        const TKeyEvent& aKeyEvent,
        TBool aInterpretLeftAndRightAsEarEvents,
        TBool& aDataAltered,
        TInt& aHighlightIncrement);

    /**
     * Called when MFNE wants to move highlight/focus from this field.
     * If the entered value contains an error (i.e. is too large or small),
     * aError is set to ETrue.
     */
    void HandleDeHighlight(
        const CFont& aFont,
        CEikonEnv& aEikonEnv,
        TBool& aDataAltered,
        TBool& aError);

private:
    const TDesC& Text() const;

// New internal methods
private:
    TInt MaxNumOfChars() const;
    TReal ValueFromText(const TDesC& aText) const;
    TBool SetTextFromValueAndNormalize( TReal aValue );        
    TChar DecimalSeparator() const;
    void UpdateAllowedInput();
    void ClearFieldIfNecessary( TBool& aDataAltered );
    void TryAppend( TChar aChar, TUint aAllowedFlags, TBool& aDataAltered );
    void TryDelete( TInt aDigits, TBool& aDataAltered );
    TChar NormalizeDigit( TChar aChar ) const;

private:
    TReal   iMinimumValue;
    TReal   iMaximumValue;
    TInt    iMaxPositiveIntegerDigits;
    TInt    iMaxNegativeIntegerDigits;
    TInt    iMaxFractionalDigits;

    HBufC*  iText;

    TBool   iIsBeingEditedWithCursor;
    
    TDigitType iDigitType;
    
    TUint   iAllowedInputFlags;
    TUint   iFlags;        
    
    TChar   iMinusSign;
    TChar   iZero;
    };

#endif // CAKNMFNEFLOAT_H

// end of File