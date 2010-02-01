// Copyright (c) 2004-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//


#ifndef __EIKINFOMSGWIN_H__
#define __EIKINFOMSGWIN_H__

/** An interface class for creating customized info message windows
WARNING: For internal use ONLY. Compatibility is not guaranteed in future releases.


@publishedPartner 
@released */
class MEikInfoMsgWin
	{
public:

	/** Displays an information message window for a specified duration.
	@param aText The text for the information message.
	@param aCorner The alignment for the information message.
	@param aDuration The time period for the information message. */
    virtual void StartDisplaySpecifyingDuration(const TDesC& aText, TGulAlignment aCorner, TTimeIntervalMicroSeconds32 aDuration) = 0;
	
	/** Displays the message window with the specified text and alignment.
	@param aText The text to display in the message. 
	@param aCorner The position in which the message window will appear. There 
	are 9 options for this, each square of a 3 by 3 matrix on the screen. */	
	virtual void StartDisplay(const TDesC& aText, TGulAlignment aCorner) =0;
	
	/** Stops displaying the message window. 
	*/	
	virtual void CancelDisplay() =0;
	
	/** Deletes the object, calling it's private destructor.
	*/	
	virtual void Release() = 0;
	};
	
#endif	// __EIKINFOMSGWIN_H__
