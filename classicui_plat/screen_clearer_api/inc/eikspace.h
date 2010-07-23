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
* Description:  Class declaration for EIKON spacer control.
*
*/


#ifndef __EIKSPACE_H__
#define __EIKSPACE_H__

#include <AknControl.h>
#include <gdi.h>

// Forward declarations
class TResourceReader;

/**
 * An invisible control that is used to provide a space between
 * visible controls. It has a width, a height and a color.
 * The spacer is normally drawn using the background color
 * so that it is invisible.
 *
 * Its associated resource struct is @c SPACER and its control
 * factory identifier is @c EEikCtSpacer.
 *
 * @lib eikctl.lib
 * @since S60 0.9
 */
class CEikSpacer : public CAknControl
    {
public:

    /**
     * Default C++ constructor.
     * The spacer's color is initialised to white.
     */
    IMPORT_C CEikSpacer();
    
    /**
     * C++ constructor with a width, height and color.
     *
     * @param aWidth  The spacer's width.
     * @param aHeight The spacer's height.
     * @param aColor  The spacer's color.
     */
	IMPORT_C CEikSpacer(TInt aWidth,TInt aHeight,TRgb aColor);
	
	/**
     * Destructor.
     */
    IMPORT_C ~CEikSpacer();
    
    /**
     * Sets the spacer's width.
     *
     * @param aWidth The spacer's width.
     */
	IMPORT_C void SetWidth(TInt aWidth);
	
	/**
     * Sets the spacer's height.
     *
     * @param aHeight The spacer's height.
     */
	IMPORT_C void SetHeight(TInt aHeight);
	
	/**
     * Sets the spacer's color.
     *
     * @param aColor The spacer's color.
     */
	IMPORT_C void SetColor(TRgb aColor);
	
	/**
     * Specifies whether the spacer is drawn using the standard brush color.
     *
     * If the "Is clear" flag is set, the spacer's color value is ignored,
     * and it is drawn using the brush color defined in the system's
     * standard graphics context. By default, the "Is clear" flag is unset.
     *
     * @param aClear @c ETrue to set the "Is clear" flag,
     *               @c EFalse to unset it.
     */
	IMPORT_C void SetClear(TBool aClear);
	
public: // From @c CCoeControl.

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
    
private: /** From @c CCoeControl. */

    void ConstructFromResourceL(TResourceReader& aReader);

	void Draw(const TRect& aRect) const;
	
private: /** From @c CAknControl. */

    IMPORT_C void* ExtensionInterface( TUid aInterface );
    
private:
	TRgb iColor;
	TBool iClear;
    };

#endif // __EIKSPACE_H__
