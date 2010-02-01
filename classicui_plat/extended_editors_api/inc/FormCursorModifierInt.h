/*
* Copyright (c) 1997-2003 Nokia Corporation and/or its subsidiary(-ies).
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



#if !defined(__FORMCURSORMODIFIERINT_H__)
#define __FORMCURSORMODIFIERINT_H__

class MFormCursorModifier
	{
public:
	enum TFormCursorModifierEvent
		{
		/**
		*
		*/
		EEventNull,
		/**
		*
		*/
		EEventInitialiseEditor,
		/**
		*
		*/
		EEventInlineEditUpdate,
		/**
		*
		*/
		EEventInsertion,
		/**
		*
		*/
		EEventDeletion,
		/**
		*
		*/
		EEventNavigation,
		/**
		* These events are expected to be called by the Form client,
		* as only it knows the current input directionality
		*/
		EEventInputDirectionIsLeftToRight,
		EEventInputDirectionIsRightToLeft
		};
public:
	virtual void HandleFormCursorModifierEventL(TFormCursorModifierEvent aEvent, TInt aData1, TAny* aData2) = 0;
	};

#endif
