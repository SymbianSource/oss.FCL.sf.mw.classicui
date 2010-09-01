/*
* Copyright (c) 2002-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Class declaration for EIKON bordered control.
*
*/


#ifndef __EIKBCTRL_H__
#define __EIKBCTRL_H__

#include <gulbordr.h>
#include <coecntrl.h>
#include <AknControl.h>

/**
 * A control which is drawn surrounded by a rectangular border.
 *
 * The screen appearance of derived classes can be changed by overriding
 * the protected method @c Draw(). By default, this draws a border of the
 * appropriate type around the control.
 *
 * @lib eikcoctl.lib
 * @since S60 0.9
 */
class CEikBorderedControl : public CAknControl
	{
public:

    /**
     * Default C++ Constructor.
     * Constructs a new bordered control that has no border.
     */
	IMPORT_C CEikBorderedControl();
	
	/**
     * Constructor that creates a new bordered control with 
     * a specified border.
     *
     * @param aBorder The border of the control.
     */
	IMPORT_C CEikBorderedControl(const TGulBorder& aBorder);
	
public: /** From @c CCoeControl. */

    /**
     * Checks whether the control has a border.
     *
     * From @c CCoeControl.
     *
     * @return @c ETrue if the control has a border, @c EFalse otherwise.
     */
	IMPORT_C TBool HasBorder() const;
	
	/**
     * Sets the control's adjacency.
     *
     * Declares that a control abuts another control along one edge,
     * and does not need to be drawn with a full border along that side.
     * This is for use by layout engines or any user code which lays out
     * controls next to one another.
     *
     * Its intended use is to remove the double border that may occur if
     * two controls, both with borders, are adjacent within a
     * container control.
     *
     * From @c CCoeControl.
     *
     * @param aAdjacent A value from @c TGulAdjacent declaring
     *                  which edge of this control is shared.
     *
     * @see CCoeControl::SetAdjacent()
     */
	IMPORT_C void SetAdjacent(TInt aAdjacent);
	
	/**
     * <b> Not used in S60. </b>
     *
     * From @c CCoeControl.
     *
     * @param aColorUseList Not used.
     */
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	
	/**
     * Handles a change to the control's resources.
     *
     * The types of resources handled are those which are shared across
     * the environment, e.g. colours or fonts. For colour scheme changes,
     * @c DrawDeferred() is called in order to redraw the control.
     *
     * If overriding this method, the implementation must
     * include a base call to this method.
     *
     * From @c CCoeControl.
	 *
     * @param aType The type of resource that has changed.
     */
	IMPORT_C void HandleResourceChange(TInt aType);
	
	/**
     * Handles pointer events.
     *
     * This function gets called whenever a pointer event occurs in the 
     * control, i.e. when the pointer is within the control's extent, or when 
     * the control has grabbed the pointer.
     * 
     * If overriding this method, the implementation must 
     * include a base call to this method.
     *
     * From @c CCoeControl.
     *
     * @param aPointerEvent The pointer event.
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    
public:

    /**
     * Sets the border type of the control to a type defined in
     * @c TGulBorder::TBorderType.
     *
     * @param aBorderType The border type to be set.
     */
	IMPORT_C void SetBorder(TGulBorder::TBorderType aBorderType);
	
	/**
     * Sets the border type.
     * Any one of the values from the enums @c TGulBorder::TBorderType
     * or @c TGulBorder::TLogicalType specifies a valid border type.
     *
     * Custom border types can be created by selecting
     * one value from enum @c TGulBorder::T3DStyle,
     * one value from enum @c TGulBorder::TConstructionStyle,
     * at most one value from enum @c TGulBorder::TOutlineStyle,
     * at most one value from enum @c TGulBorder::TInlineStyle,
     * at least one value from enum @c TGulBorder::TThickness and
     * at least one value from enum @c TGulBorder::TRounding
     * and performing an OR operation to these.
     *
     * @param aBorderType The border type to be set.
     */
	IMPORT_C void SetBorder(TInt aBorderType);
	
	/**
     * Gets the control's border.
     *
     * @return The border of the control.
     */
	IMPORT_C TGulBorder Border() const;
	
protected: /** From @c CCoeControl. */

    /**
     * Draws the border around the control. This function also clears the
     * central area if the @c IsBlank() method returns @c ETrue.
     *
     * From @c CCoeControl
     *
     * @param aRect Not used.
     *
     * @see CCoeControl::IsBlank()
     * @see Border()
     */
	IMPORT_C void Draw(const TRect& aRect) const;
	
	/**
     * Writes the internal state of the control and its components to @c aWriteStream.
     * Does nothing in release mode.
     *
     * Designed to be overridden and base called from subclasses.
     *
     * From @c CCoeControl
     *
     * @param[in,out] aWriteStream A connected write stream.
     */
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
	
private: /** From @c CAknControl. */

    IMPORT_C void* ExtensionInterface( TUid aInterface );
    
protected:
    
    /** The control's border. */
	TGulBorder iBorder;
	
private:
    TInt iSpare[2];
	};

#endif // __EIKBCTRL_H__
