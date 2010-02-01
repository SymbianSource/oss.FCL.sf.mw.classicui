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

// EIKSLBD.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
#if !defined(__EIKSLBD_H__)
#define __EIKSLBD_H__

#include <eikslb.h>

#include <e32base.h>
#include <gdi.h>

#include <eikfrlbd.h>
/**
*  CSettingsListBoxData can draw list items for settings lists
* Special feature of this class is the horizontal lines dividing setting
* items and the style of highlight for settings.
*  @lib avkon
*  @since 0.0
*/
class CSettingsListBoxData : public CFormattedCellListBoxData
	{
public: // from CEikFormattedCellListBox
	CSettingsListBoxData() : iXPos(19) { }
	IMPORT_C static CSettingsListBoxData* NewL();
	IMPORT_C virtual void Draw(const TListItemProperties& aItemProperties,
				   CWindowGc& aGc,
				   const TDesC* aText,
				   const TRect& aRect,
				   TBool aHighlight,
				   const TColors& aColors) const;
public:
	void SetLineXPosition(TInt x) { iXPos = x; }
	TInt LineXPosition() const { return iXPos; }
private:
	TInt iXPos;
	};


#endif



