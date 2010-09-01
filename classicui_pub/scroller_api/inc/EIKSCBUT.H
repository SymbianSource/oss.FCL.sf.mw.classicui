/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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


#if !defined(__EIKSCBUT_H__)
#define __EIKSCBUT_H__

#include <eikbutb.h>
#include <lafpublc.h>

/**
 * CEikScrollButton
 *
 * @deprecated Do not use
 */
class CEikScrollButton : public CEikButtonBase
	{
public:
    /** @deprecated */
	enum TType
		{
		ENudgeLeft=SLafScrollButton::ENudgeLeft, /** @deprecated */
		ENudgeUp=SLafScrollButton::ENudgeUp, /** @deprecated */
		ENudgeRight=SLafScrollButton::ENudgeRight, /** @deprecated */
		ENudgeDown=SLafScrollButton::ENudgeDown, /** @deprecated */
		EPageLeft=SLafScrollButton::EPageLeft, /** @deprecated */
		EPageUp=SLafScrollButton::EPageUp, /** @deprecated */
		EPageRight=SLafScrollButton::EPageRight, /** @deprecated */
		EPageDown=SLafScrollButton::EPageDown, /** @deprecated */
		EHome=SLafScrollButton::EHome, /** @deprecated */
		ETop=SLafScrollButton::ETop, /** @deprecated */
		EEnd=SLafScrollButton::EEnd, /** @deprecated */
		EBottom=SLafScrollButton::EBottom /** @deprecated */
		};

public:

    /** @deprecated */
	enum TTypeOfScrollBar
		{
		ENormal		=0x00, /** @deprecated */
		EArrowHead	=0x01 /** @deprecated */
		};

public: // class specific functions
	
	/** @deprecated */
	IMPORT_C ~CEikScrollButton();
	
	/** @deprecated */
	IMPORT_C CEikScrollButton(TType aType);
	
	/** @deprecated */
	IMPORT_C TType Type() const;

public: // From CCoeControl
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );    
private:
    TInt iSpare;
	};


/**
 * CEikArrowHeadScrollButton
 *
 * @deprecated Do not use
 */

class CEikArrowHeadScrollButton : public CEikScrollButton
	{

public:

    /** @deprecated */
	IMPORT_C static CEikArrowHeadScrollButton* NewL(const CCoeControl* aParent, TType aType);
private:
	CEikArrowHeadScrollButton();
	};



#endif
