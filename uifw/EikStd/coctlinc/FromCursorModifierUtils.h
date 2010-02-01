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
#ifndef FROMCURSORMODIFIERUTILS_H
#define FROMCURSORMODIFIERUTILS_H

#include <e32base.h>

// forward declarations
class TTmDocPosSpec;
class CTextLayout;
class CTextView;

NONSHARABLE_CLASS(TFormCursorModifierUtils)
	{
public:
	/** 
	* C++ Constructor
	*/
	TFormCursorModifierUtils(CTextView& aTextView, CTextLayout& aTextLayout);

	/** 
	* Destructor
	*/
	virtual ~TFormCursorModifierUtils();
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
	CTextView& iTextView;
	CTextLayout& iTextLayout;
	};


#endif
