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
#if !defined(__AKNEDFORMACCESSOR_H__)
#define __AKNEDFORMACCESSOR_H__

#include <e32base.h>
#include <AknFormAccessor.h>

// forward declarations
class CEikEdwin;

class CAknEdwinFormAccessor : public CBase, public MAknFormAccessor
	{
public:
	/** 
	* C++ constructor
	*
	* @param aEdwin	Pointer to editor owning this form accessor.
	*				Ownership is not transferred
	*/
	IMPORT_C CAknEdwinFormAccessor(CEikEdwin* aEdwin);

	/** 
	* Destructor
	*
	*/
	virtual ~CAknEdwinFormAccessor();

	/** 
	* Sets this form accessors owning editor
	*
	* @param aEdwin	Pointer to editor owning this form accessor.
	*				Ownership is not transferred
	*/
	IMPORT_C void SetEdwin(CEikEdwin* aEdwin);

public:  // from MAknFormAccessor
	/** 
	* Returns the text layout object currently being used by the \form
	* client control currently owning the form accessor
	*
	* @return CTextLayout*	Pointer to text layout object currently in use
	*						by owning control
	*/
	CTextLayout* GetTextLayout() const;

	/** 
	* Returns the text view object currently being used by the \form
	* client control currently owning the form accessor
	*
	* @return CTextView*	Pointer to text layout object currently in use
	*						by owning control
	*/
	CTextView* GetTextView() const;

	/** 
	* Returns the \form client control which owns the form accessor
	*
	* @return CCoeControl*	Pointer to the control which is the client of
	*						\form
	*/
	CCoeControl* FormClientControl() const;

private:
	CEikEdwin* iEdwin;	// not owned
	};

#endif
