/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
#ifndef AKNCURSORMANAGER_H
#define AKNCURSORMANAGER_H

#include <e32base.h>

// forward declarations
class CAknEdwinState;
class TTmDocPosSpec;
class CAknEdwinFormAccessor;
class CTextLayout;
class CTextView;

class CAknCursorManager : public CBase
	{
public:
	/** 
	* 2 phase constructor
	*
	* @param
	*/
	static CAknCursorManager* NewL(CAknEdwinState* aEdwinState);

	/** 
	* Destructor
	*/
	virtual ~CAknCursorManager();

	/** 
	* 
	*/
	TTmDocPosSpec DocPos() const;
	/** 
	* 
	*/
	void SetDocPosL(const TTmDocPosSpec& aDocPos);
	/** 
	* 
	*/
	TBool IsRightToLeftParagraph(TTmDocPosSpec aPos);
	/** 
	* 
	*/
	TBool VisualCursorBetweenOpposingChunks();
	/** 
	* 
	*/
	void ToggleVisualDocPosL();
	/** 
	* 
	*/
	void ToggleLogicalDocPosL();

private:
	CAknCursorManager(CAknEdwinState* aEdwinState);
	void ConstructL();

	CAknEdwinFormAccessor* FormAccessor() const;
	CTextLayout* TextLayout() const;
	CTextView* TextView() const;

private:
	CAknEdwinState* iEdwinState; // not owned
	};


#endif
