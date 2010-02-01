/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Focus change interface class for sct controls.
*
*/


#ifndef AKNSCTFOCUSHANDLER_H
#define AKNSCTFOCUSHANDLER_H

/**
 *  Focus change interface class for sct controls.
 * *
 *  @lib 5.0
 *  @since S60 v5.0
 */
class MAknSctFocusHandler
    {   
public:
        /**
     	* Returns pointer to the focused control.
	    *
     	* @since S60 5.0
     	* @return pointer to the focused control.
     	*/
        virtual CCoeControl* FocusedControl() = 0;

    	/**
     	* Enter control and highlight position (aX, aY).
    	*
     	* @since S60 5.0
     	* @param aX horizontal coordinate.
     	* @param aY vertical coordinate.
     	* @return whether entry was successful.
     	*/
        virtual TBool EnterControl(TInt aX, TInt aY) = 0;   

    	/**
     	* Move control highlight to position (aX, aY).
    	*
     	* @since S60 5.0
     	* @param aX horizontal coordinate.
     	* @param aY vertical coordinate.
     	*/
        virtual void MoveFocus(TInt aX, TInt aY) = 0;

	    /**
     	* Return whether possible to exit control with a key.
    	*
     	* @since S60 5.0
     	* @param aKeycode keycode for checking exit.
     	* @return whether it is possible to exit with a key.
     	*/
        virtual TBool ExitWithKey(TInt aKeycode) = 0;          

    	/**
     	* Leaves focused control.
	    *
     	* @since S60 5.0
     	* @return whether leave was successful.
     	*/
        virtual TBool LeaveControl() = 0;      
    };

#endif // AKNSCTFOCUSHANDLER_H
