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

// AknPopupFader.h
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__AKNPOPUPFADER_H__)
#define __AKNPOPUPFADER_H__

#include <e32base.h>

class CCoeControl;

/** MAknFadedComponent is an array of controls
 */
class MAknFadedComponent
	{
public:
    /** CountFadedComponents() returns number of items in the array
     */
	IMPORT_C virtual TInt CountFadedComponents();
    /** FadedComponent() returns specific controls from the array based on index
     */
	IMPORT_C virtual CCoeControl* FadedComponent(TInt aIndex);
	};

/** TAknPopupFader fades controls
 */
class TAknPopupFader
	{
public:
    /** FadeBehindPopup fades components
     * @param aComponent array of controls
     * @param aParent parent control
     * @param aFade true if control is to be faded, false if not
     */
	IMPORT_C void FadeBehindPopup(MAknFadedComponent* aComponent, CCoeControl* aParent, TBool aFade);

public:	// internal
	static void CreateStaticL();

private:
	void FadeBehindPopupL(MAknFadedComponent* aComponent, CCoeControl* aParent, TBool aFade);

private:
	TBool iBackgroundFaded; // unused
	};


#endif
