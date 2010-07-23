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
*/

// AknQueryValue.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__AKNQUERYVALUE_H__)
#define __AKNQUERYVALUE_H__


#include <eikenv.h>
#include <babitflags.h>

class MDesCArray;

/**
 * Mixin class representing a value that is accessed as text.
 * <p> The Value can be changed by creating an editor dialog, 
 * which may be either a query or a setting page
 * or optionally by choosing an entry from an array of values. 
 * The array can be accessed as a descriptor array, and the value 
 * can be accessed as a descriptor.
 */
class MAknQueryValue
	{
public:
	/**
	 * Possible modes are query & setting page 
	 * 
	 */
	enum TMode
		{
		EQueryMode,
		ESettingPageMode
		};
protected:
	/**
	 * If EAutoAppendBitIndex is set, 
	 * the query value auto appends new values
	 */
	enum TFlagBits
		{
		ESettingPageModeBitIndex = 0,
		EAutoAppendBitIndex
		};
public:
	virtual ~MAknQueryValue() {}
	
	/**
	 * Returns the array as a descriptor array, 
	 * ownership will be not passed 
	 */	
	virtual const MDesCArray* MdcArray() const = 0;
	
    /**
     * This should be implemented so that it returns the current value as text
     * 
     * @return	descriptor representing current value, new 
     * descriptor is created and left on cleanup stack, ownership passed back to client
    */	
	virtual HBufC* CurrentValueTextLC() = 0;
	
	/**
     * Returns the index in the array of the current value. 
     * If no matches, returns zero
     *
    */
	virtual TInt CurrentValueIndex() const = 0;
	
	/**
     * Changes the current value to correspond to a value in the array.
     *
     * @param aIndex	index in array of value to set as current
    */
	virtual void SetCurrentValueIndex(const TInt aIndex) = 0;
	
    /**
     * Creates an editor within context. If the value is edited and OK'd,
     * the new value will be set as the current value. Otherwise the current value 
     * remains unchanged.
     *
     * @return	ETrue if current value was altered; EFalse otherwise
     */	
	virtual TBool CreateEditorL() = 0;
	
	/**
	 * Set QueryMode to be whether query or settingpage -mode
	 *
     * @param aMode	value from <p>TMode	 
	 */
	virtual void SetQueryMode( MAknQueryValue::TMode aMode ) = 0;

	/**
	 * Override the default resource IDs used if a Setting Page mode query is put up.
	 * All Queryvalue implementations should have default resource set up. Hence this
	 * need not be called unless non-default resource is required.
	 *
	 * THE IMPLEMENTATION OF THESE RESOURCE OVERRIDES IS RESERVED FOR FUTURE VERSIONS
	 * OF SERIES 60. NOT CURRENTLY FUNCTIONAL. DO NOT USE.
	 *
	 * The rules for usage of these ids is the same as that for the CAknSettingPage constructors
	 * that take both these resources
	 *		Editor Resource		Setting Page Resource
	 *			present				present				Both are used (but text & number overridden)
	 *			 = 0					present				Editor resource is used via SP resource 
	 *			present					= 0					default SP resource for the query type is used + this editor resource
	 *
	 * The type of the editor resource is fixed. If editor resource override is being
	 * used, then the resource must be for that control type of editor used in the
	 * CAknQueryValueXXXX class.
	 * 
	 * @param aSettingPageResourceId		AVKON_SETTING_PAGE resource ID to use
	 * @param aSettingPageEditorResourceId	Editor resource ID to use (takes precedence)
	 *
	 */
	virtual void SetSettingPageResourceIds( 
		TInt aSettingPageResourceId, 
		TInt aSettingPageEditorResourceId ) = 0;
	
	/**
	 * Set the QueryValue to append a new user value, if distinct from former value 
	 *
     * @param aAppend	set/unset flag EAutoAppendBitIndex	 
	 */
	virtual void SetAutoAppend( TBool aAppend ) = 0;

protected:
	/**
	 * Method to add the current value to the QueryValueArray if it is new.
	 * The new value is not owned by QueryValue object, but is "given away"
	 *
	 */
	virtual void AppendValueIfNewL() = 0;
private:
	IMPORT_C virtual void Reserved_MAknQueryValue();
   };

/** 
 * Pure virtual class that adds some standard functionality for queries
 *
 */
class CAknQueryValue : public CBase, public MAknQueryValue
	{
public:
	/**
	 * Set QueryMode to be whether query or settingpage -mode
	 *
     * @param aMode	value from <p>TMode	 
	 */
	IMPORT_C virtual void SetQueryMode( MAknQueryValue::TMode aMode );
	
	/**
	 * Override the default resource IDs used if a Setting Page mode query is put up.
	 * 
	 * @param aSettingPageResourceId		AVKON_SETTING_PAGE resource ID to use
	 * @param aSettingPageEditorResourceId	Editor resource ID to use (takes precedence)
	 *
	 */	
	IMPORT_C virtual void SetSettingPageResourceIds( TInt aSettingPageResourceId, TInt aSettingPageEditorResourceId );
	
	/**
	 * Set the QueryValue to append a new user value, if distinct from former value 
	 *
     * @param aAppend	set/unset flag EAutoAppendBitIndex	 
	 */	
	IMPORT_C virtual void SetAutoAppend( TBool aAppend );
	
	/**
	 * Method to add the current value to the QueryValueArray if it is new.
	 * The new value is not owned by QueryValue object, but is "given away"
	 *
	 */	
	IMPORT_C virtual void AppendValueIfNewL();
protected:
	/**
	 * Check if given index is valid within descriptor array
	 *
     * @param aIndex   index to be checked	 	 
	 */
	TBool IsValidIndex(TInt aIndex) 
	{
	if (MdcArray()->MdcaCount() < 1) return ETrue;
	if (aIndex < 0 || aIndex >= MdcArray()->MdcaCount())
	    return EFalse;
	return ETrue;
	}

protected:
    /** 
     * Flags that determine behavior
     *
     */
	TBitFlags16	iFlags;
    /** 
     * Resource id for setting page
     *
     */
	TInt iSettingPageResourceId;
    /** 
     * Resource id for editor in setting page
     *
     */	
	TInt iSettingPageEditorResourceId;
private:
	TInt iSpare;
// from MAknQueryValue
	IMPORT_C void Reserved_MAknQueryValue();
	};

#endif // __AKNQUERYVALUE_H__

