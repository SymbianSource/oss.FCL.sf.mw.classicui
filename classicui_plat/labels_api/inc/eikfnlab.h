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
* Description:  Class declaration for EIKON file name label control.
*
*/


#ifndef __EIKFNLAB_H__
#define __EIKFNLAB_H__

#include <eikbctrl.h>

// forward declarations
class CEikLabel;

/**
 * File name label is a bordered control that displays the application name.
 *
 * @lib eikcoctl.lib
 * @since S60 0.9
 */
class CEikFileNameLabel : public CEikBorderedControl
	{
public:
    
    /**
     * C++ Default Constructor.
     * Sets the default border.
     */
	IMPORT_C CEikFileNameLabel();
	
	/**
	 * Destructor.
	 */
	IMPORT_C ~CEikFileNameLabel();
	
	/**
	 * Second phase constructor.
	 * Completes the construction of a file name label control.
	 */
	IMPORT_C void ConstructL();
	
	/**
	 * Updates the file name label with the name of the application.
	 * If the application is file-based, then the file name of the
	 * main document will be shown.
	 * Otherwise the label will be the application's caption.
	 */
	IMPORT_C void UpdateL();
	
public:	/** From @c CCoeControl. */

    /**
     * <b> Not used in S60. </b>
     *
     * From @c CCoeControl
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
	 * Sets the control's minimum required size.
	 *
     * This function should be overridden by the concrete control class if the
     * control is to be displayed inside a dialog.
     *
     * Dialogs set the size and position of their components
     * automatically, and use this function to enquire the minimum size that
     * a control requires.
     *
     * Other container controls that automatically calculate the layout
     * of their components may also use this function.
     *
     * From @c CCoeControl.
     *
     * @return The minimum size required by the control.
	 */
	IMPORT_C TSize MinimumSize();
	
	/**
     * Handles pointer events.
     *
     * This function gets called whenever a pointer event occurs in the 
     * control, i.e. when the pointer is within the control's extent, or when 
     * the control has grabbed the pointer.
     *
     * If the pointer event occurs within this control, the function
     * will launch the task swapper.
     * 
     * If overriding this method, the implementation must 
     * include a base call to this method.
     *
     * From @c CCoeControl.
     *
     * @param aPointerEvent The pointer event.
     */
	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	
protected:

    /**
     * Draws the borders of the control.
     *
     * The screen appearance of derived classes can be changed by overriding
     * this method. By default, this draws a border of the appropriate
     * type around the control.
     *
     * From @c CCoeControl.
     *
     * @param aRect Not used.
     */
	IMPORT_C void Draw(const TRect& aRect) const;
	
private: /** From @c CCoeControl. */

	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	
	IMPORT_C TInt CountComponentControls() const;
	
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
	
	IMPORT_C void SizeChanged();
	
private: /** From @c CAknControl. */

    IMPORT_C void* ExtensionInterface( TUid aInterface );
    
private:
	CEikLabel* iLabel;
	TInt iSpare;
	};

#endif // __EIKFNLAB_H__
