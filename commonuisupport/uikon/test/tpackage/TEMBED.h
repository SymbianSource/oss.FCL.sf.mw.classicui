// Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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

/**
 @file 
 @internalComponent - Internal Symbian test code 
*/

#ifndef	__TEMBED_H__
#define	__TEMBED_H__

const TInt	KBufLen = 512;

class CViewControl : public CCoeControl, public MCoeControlBrushContext
    {
public:
    void ConstructL(const TRect& aRect);
	~CViewControl();
private: // framework
    void Draw(const TRect& aRect) const;
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
    void SizeChanged();
    void FocusChanged(TDrawNow aDrawNow);
private:
    CFont* iFont;
    };

class CDocument : public CEikDocument
	{
public:
	CDocument(CEikApplication& aApp): CEikDocument(aApp) 
	{ }
private: // from CEikDocument
	CEikAppUi* CreateAppUiL();
private: // from CApaDocument
public:
	TBuf<KBufLen>	iBuf;
	};

#endif


