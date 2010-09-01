/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Unit multi-field numeric editor
*
*/


#ifndef CAKNUNITEDITOR_H
#define CAKNUNITEDITOR_H

#include <eikmfne.h>

class CAknMfneFloat;
class CAknMfneSeparator;

/**
 * A multi-field numeric editor for displaying and editing a floating value
 * and an associated label.
 *
 * CAknUnitEditor is a multi-field numeric editor (MFNE), which is used for
 * displaying and editing floating point numeric data with a textual
 * label. Unit in the class name refers to a unit of measurement, for
 * example distance or speed, hence a typical use case might be an editor
 * which is used to edit an altitude value for a position in a GPS
 * application.
 *
 * Creating the editor is carried out by using either NewL() or
 * NewLC() function followed by a call to either ConstructL()
 * or ConstructFromResourceL() function. Note that if the editor is
 * not constructed fully, most functions will panic with KERN-EXEC 3.
 *
 * The value to be shown by the editor must be set at construction, and
 * can be later set using SetValue(). The current value of the editor
 * can be retrieved using Value().
 *
 * Minimum and maximum limits can be set using the function
 * SetMinimumAndMaximum(). NaN values for this function are
 * not supported, and will cause undefined behaviour.
 *
 * The editor supports a label shown next to the value. This label can be
 * set to a custom value (referred to as custom unit), or a set of
 * predefined and localized units can be used. See TAknUnitEditorUnits in
 * eikon.hrh and the two overloads of SetUnitL(). Note that the editor
 * discards the custom unit when a localized unit is set, so setting
 * the localized unit back to EAknUnitEditorCustomUnit clears
 * the unit.
 *
 * The editor supports variable number of fractional digits. A value
 * with no fractional part at all can also be displayed and edited. This
 * feature can be used with the function SetMaxFractionalDigits(), and
 * the corresponding getter MaxFractionalDigits(). Values set using
 * construction functions or SetValue() are rounded to correspond
 * with the number of fractional digits, so data loss may occur in such
 * case.
 *
 * The editor also supports an uninitialized state, which in practice means
 * that it can have nothing to display and in such case contains a
 * 'not a number' (NaN) value. This state can be allowed by the using the flag
 * EAknUnitEditorAllowUninitialized, found in TAknUnitEditorFlags in
 * eikon.hrh. For more information about NaN, see Math::IsNaN() and
 * TRealX::SetNaN().
 *
 * @lib eikctl.lib
 * @since S60 v3.2
 */
NONSHARABLE_CLASS( CAknUnitEditor ) : public CEikMfne
    {
public:
    /**
     * Creates a new CAknUnitEditor object. The client must call ConstructL()
     * or ConstructFromResourceL() after calling this function.
     *
     * @return The created CAknUnitEditor.
     */
    IMPORT_C static CAknUnitEditor* NewL();
    
    /**
     * Creates a new CAknUnitEditor object, leaving it in the cleanup stack.
     * The client must call ConstructL() or ConstructFromResourceL()
     * after calling this function.
     *
     * @return The created CAknUnitEditor.
     */
    IMPORT_C static CAknUnitEditor* NewLC();

    /**
     * C++ destructor. Deletes all owned member data.
     */
    virtual ~CAknUnitEditor();

    /**
     * Second-phase constructor. This should be called after creating a
     * new editor object with NewL() or NewLC(), if the
     * editor is not constructed from a resource.
     *
     * @param aMinimumValue The minimum allowable value.
     * @param aMaximumValue The maximum allowable value.
     * @param aInitialValue The initial value, can be NaN if the editor
     *                      is set to support it by using the
     *                      EAknUnitEditorAllowedUninitialized flag.
     * @param aMaxFractionalDigits The maximum number of fractional digits.
     * @param aUnit The unit type, see TAknUnitEditorUnits
     *              in eikon.hrh. Can be set to EAknUnitEditorCustomUnit
     *              or zero if you plan on using a custom unit.
     * @param aFlags The editor flags, see TAknUnitEditorFlags
     *               in eikon.hrh. This can be set to zero if no flags
     *               are desired. This is also the default parameter.
     * @leave KErrNotSupported If the given predefined unit type, aUnit,
     *                         is not found.
     * @see TAknUnitEditorUnits
     * @see TAknUnitEditorFlags
     */
    IMPORT_C void ConstructL(
        TReal aMinimumValue, TReal aMaximumValue,
        TReal aInitialValue,
        TInt aMaxFractionalDigits, TInt aUnit, TUint aFlags = 0 );
    
    /**
     * Second-phase constructor. This should be called after creating a
     * new editor object with NewL() or NewLC(), if the
     * editor is constructed from a resource. The resource structure
     * used in creating the editor is AVKON_UNIT_EDITOR.
     *
     * @param aResourceReader A resource file reader.
     * @leave KErrNotSupported If the predefined unit type in the resource
     *                         is not found.
     * @see AVKON_UNIT_EDITOR
     */        
    IMPORT_C void ConstructFromResourceL( TResourceReader& aResourceReader );

    /**
     * Sets a value to the editor. If the value is too large or small it is
     * set to maximum or minimum value, respectively. In case of an 
     * unallowed NaN the value is set to be the maximum value.
     *
     * @param aValue The value to be set.
     * @return ETrue, if the value was valid and not changed. The value is
     *         also considered to be valid in case it is rounded to the
     *         limits of the editor's maximum fractional digits.
     */
    IMPORT_C TBool SetValue( TReal aValue );
    
    /**
     * Gets the value from the editor.
     *
     * @return The value from the editor.
     */
    IMPORT_C TReal Value() const;
    
    /**
     * Tests if particular predefined unit type is supported.
     *
     * @param aUnit The predefined unit type, from the enum
     *              TAknUnitEditorUnits.
     * @return ETrue, if the given predefined unit type is supported.
     * @see TAknUnitEditorUnits
     */
    IMPORT_C TBool SupportsUnit( TInt aUnit ) const;
    
    /**
     * Sets the custom unit type. There's no actual limit for the length of
     * the text, but if the unit text overflows, it will not be wrapped.
     *
     * @param aUnit The unit type to be set.
     */
    IMPORT_C void SetUnitL( const TDesC& aUnit );
    
    /**
     * Sets the predefined and localized unit type. If the given unit type
     * is EAknUnitEditorCustomUnit, the unit field is emptied and a
     * subsequent call to SetUnitL( const TDesC& aUnit ) is needed.
     *
     * @param aUnit The predefined unit type, from the enum
     *              TAknUnitEditorUnits.
     * @leave KErrNotSupported If the given predefined unit type is not found.
     * @see TAknUnitEditorUnits
     */
    IMPORT_C void SetUnitL( TInt aUnit );

    /**
     * Gets the current unit type as a descriptor. This returns the textual
     * representation of the unit field, regardless of the way it was set.
     *
     * @param aDes On return, contains the editor's unit type if it fits in
     *             the given descriptor.
     * @return Zero, if the function executed successfully. Otherwise the
     *         minimum length needed for the editor's content.
     */
    IMPORT_C TInt GetUnit( TDes& aDes ) const;
    
    /**
     * Gets the current unit type as an predefined unit type id,
     * from the enum TAknUnitEditorUnits. Returns EAknUnitEditorCustomUnit
     * if the last unit set was a custom unit.
     *
     * @return The current unit type identifier. EAknUnitEditorCustomUnit
     *         if custom unit was set.
     * @see TAknUnitEditorUnits  
     */
    IMPORT_C TInt Unit() const;

    /**
     * Sets the maximum number of digits to show in the fractional part of
     * the value. The maximum number of fractional digits is limited
     * to eight. Setting a value outside of valid range (0 to 8) has
     * no effect in release builds, and panics in debug builds.
     *
     * @param aFractionalDigits The maximum number of digits in the
     *                          fractional part. Can be zero to eight.
     * @panic 1 In debug builds only, if aMaxFractionalDigits is out of
     *          range.
     */
    IMPORT_C void SetMaxFractionalDigits( TInt aMaxFractionalDigits );
    
    /**
     * Gets the maximum number of digits in the fractional part of the
     * value.
     *
     * @return The maximum number of digits in the fractional part
     */
    IMPORT_C TInt MaxFractionalDigits() const;
    
    /**
     * Sets the minimum and maximum editor values. NaN values are not
     * supported, and will cause undefined behaviour.
     *
     * @param aMinimumValue The minimum allowable value
     * @param aMaximumValue The maximum allowable value
     */
    IMPORT_C void SetMinimumAndMaximum(
        TReal aMinimumValue, TReal aMaximumValue );
    
    /**
     * Gets the minimum and maximum editor values.
     *
     * @param aMinimumValue On return, contains the editor's minimum value
     * @param aMaximumValue On return, contains the editor's maximum value
     */
    IMPORT_C void GetMinimumAndMaximum(
        TReal& aMinimumValue, TReal& aMaximumValue ) const;
        
    /**
     * Sets the editor flags, see TAknUnitEditorFlags in eikon.hrh.
     *
     * @param aFlags The editor flags. Note that this overrides all
     *               the flags. Use zero if no flags are desired.
     * @see TAknUnitEditorFlags
     */
    IMPORT_C void SetFlags( TUint aFlags );
    
    /**
     * Gets the editor flags, see TAknUnitEditorFlags in eikon.hrh.
     *
     * @return The editor flags.
     * @see TAknUnitEditorFlags
     */
    IMPORT_C TUint Flags() const;
    
// from base class CEikMfne

    /**
     * From CEikMfne.
     * Validates the values in the editor. This function should be called
     * before removing focus from the editor.
     *
     * @leave KLeaveWithoutAlert If the value in the field had an error
     *                           in it.
     */
    IMPORT_C void PrepareForFocusLossL();
    
protected:

    /**
     * From CEikMfne.
     * Deals with focus changes.
     *
     * @param aDrawNow Whether to draw the control immediately.
     */
     void FocusChanged( TDrawNow aDrawNow );

private:

    /**
     * C++ constructor.
     */
    CAknUnitEditor();
    
    /**
     * Checks if the unit field label should be visible.
     *
     * @return ETrue, if the unit field should be visible.
     */
    TBool UnitFieldVisibility() const;
    
private: // data

    /**
     * Bit flags
     */
    TUint iFlags;
    
    /**
     * The limit for predefined unit indices
     */
    const TInt iUnitLimit;
    
    /**
     * Value of the current unit type, as in enum
     * TAknUnitEditorUnits.
     */
    TInt iUnitType;

    /**
     * Helper pointer to float value field
     * Not own.
     */
    CAknMfneFloat* iFloatField;
    
    /**
     * Helper pointer to separator field
     * Not own.
     */
    CAknMfneSeparator* iSeparatorField;
    
    /**
     * Helper pointer to unit field
     * Not own.
     */
    CAknMfneSeparator* iUnitField;
    
    };

#endif // CAKNUNITEDITOR_H
