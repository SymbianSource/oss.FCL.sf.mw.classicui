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
* Description:  Class declaration for EIKON aligned control.
*
*/


#ifndef __EIKALIGN_H__
#define __EIKALIGN_H__

#include <coecntrl.h>
#include <gulalign.h>
#include <gulutil.h>
#include <AknControl.h>

/**
 * Extends @c CAknControl to support control alignment and margins.
 *
 * @lib eikcoctl.lib
 * @since S60 0.9
 */
class CEikAlignedControl : public CAknControl
	{
public:

    /**
     * C++ default constructor.
     */
	IMPORT_C CEikAlignedControl();
	
	/**
	 * Destructor
	 */
	IMPORT_C ~CEikAlignedControl();
	
	/**
	 * Sets all of the control's margins.
	 *
	 * @param aValue The number of pixels to which all margins will be set.
	 */
	IMPORT_C void SetAllMarginsTo(TInt aValue);
	
	/**
	 * Sets the control's alignment.
     *
	 * @param aAlign The alignment to be set to the control.
	 */
	IMPORT_C void SetAlignment(TGulAlignmentValue aAlign);
	
public: /** From @c CCoeControl. */

    /**
     * Handles pointer events.
     *
     * This function gets called whenever a pointer event occurs in the 
     * control, i.e. when the pointer is within the control's extent, or when 
     * the control has grabbed the pointer. The control should implement this 
     * function to handle pointer events.
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
     * Writes the internal state of the control and its components
     * to @c aWriteStream.
     *
     * Does nothing in release mode.
     * Designed to be overridden and base called from subclasses.
     *
     * From @c CCoeControl.
     *
     * @param[in,out] aWriteStream A connected write stream.
     */
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
	
private: /** From @c CAknControl. */

    IMPORT_C void* ExtensionInterface( TUid aInterface );
    
public:
    /** The control's margins. */
	TMargins8 iMargin;
	
	/** The control's alignment. */
	TGulAlignment iAlignment;

private:
    TInt iSpare[2];
	};

#endif // __EIKALIGN_H__
