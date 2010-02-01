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
#ifndef FORMCURSORMODIFIER_H
#define FORMCURSORMODIFIER_H

#include <e32base.h>
#include <formcursormodifierint.h>

// forward declarations
class CTextView;
class CTextLayout;

NONSHARABLE_CLASS(CFormCursorModifier) : public CBase, public MFormCursorModifier
	{
private:
	enum TDirectionality
		{
		ELeftToRight,
		ERightToLeft
		};
public:
	/** 
	* 2 phase constructor
	*/
	static CFormCursorModifier* NewL(CTextView* aTextView, CTextLayout* aTextLayout);
	/** 
	* Destructor
	*/
	virtual ~CFormCursorModifier();
	/** 
	* Forwards externally generated events to the appropriate cursor
	* manager handler method
	*/
	void HandleFormCursorModifierEventL(TFormCursorModifierEvent aEvent, TInt aData1, TAny* aData2);
	/** 
	* Allows setting of text view
	*/
	void SetTextView(CTextView* aTextView);
	/** 
	* Allows setting of text layout
	*/
	void SetTextLayout(CTextLayout* aTextLayout);

private:
	CFormCursorModifier(CTextView* aTextView, CTextLayout* aTextLayout);
	void ConstructL();

	void NormaliseCursorPositionFollowingDeleteL();
	void NormaliseCursorPositionFollowingNavigationL();
	void InitialiseCursorPositionL(CEikEdwin* aEdwin);
	void SetDirectionality(TDirectionality aDirectionality);
private:
	// not owned
	CTextView* iTextView;
	CTextLayout* iTextLayout;

	TDirectionality iDirectionality;
	};


#endif
