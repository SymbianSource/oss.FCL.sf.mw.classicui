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
* Description:  This api can be used by applications to 
				 disable listbox effects on the listbox.
*
*/


#ifndef AKNLISTBOXTFX_H
#define AKNLISTBOXTFX_H

/**
 * API that can be used by applications to affect 
 * listbox effects on the listbox instances used
 * in the application.
 *
 */
class MAknListBoxTfx
	{
public:
	virtual ~MAknListBoxTfx(){};
	
	/**
     * Enable or disable effects for the listbox.
     *
     * @param ETrue to enable effects, EFalse to disable them.
     *
     * @return KErrNone on success, otherwise one of the other system-wide
     *         error codes.
     */
    virtual TInt EnableEffects( TBool aEnable ) = 0;
	};
	
#endif //AKNLISTBOXTFX_H