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
// EIKSBEXT.H
//
// This file contains extensions to classes declared in EIKSCRLB.H
//
		
#if !defined(__EIKSBEXT_H__)
#define __EIKSBEXT_H__

#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>
#endif

#if !defined(__EIKSBOBS_H__)
#include <eiksbobs.h>
#endif

#if !defined(__AKNSCBUT_H__)
#include <aknscbut.h>
#endif

#include <lafpublc.h>

#include "eiksbfrm.h"

//
// class CEikScrollBarExtensionImpl
//
// This class is a abstarct class of which derivied class contains most of the
// logic of CEikScrollBar (and its derived classes). This class is declared as
// "C"-type class instead of "M"-type class because of legacy destruction sequence
// reasons.
//
class CEikScrollBarFrame;
class CEikScrollBar;
class MEikScrollBarObserver;
class CAknInfoPopupNoteController;
class CAknTouchAreaControl;

class CEikScrollBarExtensionImpl : public CBase
    {
public:
	virtual void SetLengthL(TInt aLength)=0;
	virtual void SetModelL(const TEikScrollBarModel* aModel)=0;
	virtual void SetModel(const TEikScrollBarModel* aModel)=0;
	virtual void SetLengthAndModelL(TInt aLength,const TEikScrollBarModel* aModel)=0;
	virtual void SetModelThumbPosition(TInt aThumbPos)=0;
	virtual void SetFocusPosToThumbPos(TInt aFocusPosition)=0;
	virtual TInt ThumbPosition() const=0;
	virtual TInt ScrollBarBreadth() const=0;
	virtual void SetDecreaseButtonsDimmed(TBool aDimmed)=0;
	virtual void SetIncreaseButtonsDimmed(TBool aDimmed)=0;
	virtual void SetAllButtonsDimmed(TBool aDimmed)=0;
	virtual void SetContainingCba(CEikCba* aCba)=0;
	virtual void CreateButtonL(CAknScrollButton*& aButton,CAknScrollButton::TType aType)=0;
	virtual void DoSetModel(const TEikScrollBarModel* aModel)=0;
	virtual CEikCba* Cba() const=0;
	virtual void AddExternalFrameL(CEikScrollBarFrame* aFrame)=0;
	virtual void RemoveExternalFrame(CEikScrollBarFrame* aFrame)=0;
	virtual void DisconnectExternalFrames()=0;
	virtual void CreateRequiredComponentsL()=0;
	virtual void DestroyButton(CAknScrollButton*& aButton)=0;
	virtual void SetButtonPositionL(CAknScrollButton* aButton)=0;
	virtual TInt ScrollBarType()=0;
	virtual void SetScrollBarObserver(MEikScrollBarObserver* aScrollBarObserver)=0;
	virtual MEikScrollBarObserver* ScrollBarObserver()=0;
	virtual TBool HasModelChanged(const TEikScrollBarModel* aModel) =0;
private:
    virtual TInt Reserved_1()=0;
    virtual TInt Reserved_2()=0;
    };

//
// class CEikScrollBarExtension
//
// This class is an extension class for CEikScrollBar class. 
//
NONSHARABLE_CLASS(CEikScrollBarExtension) : public CEikScrollBarExtensionImpl
	{
public:
	CEikScrollBarExtension(CEikScrollBar* aParent);
    ~CEikScrollBarExtension();
	virtual void SetLengthL(TInt aLength);
	virtual void SetModelL(const TEikScrollBarModel* aModel);
	virtual void SetModel(const TEikScrollBarModel* aModel);
	virtual void SetLengthAndModelL(TInt aLength,const TEikScrollBarModel* aModel);
	virtual void SetModelThumbPosition(TInt aThumbPos);
	virtual void SetFocusPosToThumbPos(TInt aFocusPosition);
	virtual TInt ThumbPosition() const;
	virtual TInt ScrollBarBreadth() const;
	virtual void SetDecreaseButtonsDimmed(TBool aDimmed);
	virtual void SetIncreaseButtonsDimmed(TBool aDimmed);
	virtual void SetAllButtonsDimmed(TBool aDimmed);
	virtual void SetContainingCba(CEikCba* aCba);
	virtual void CreateButtonL(CAknScrollButton*& aButton,CAknScrollButton::TType aType);
	virtual void DoSetModel(const TEikScrollBarModel* aModel);
	virtual CEikCba* Cba() const;
	virtual void AddExternalFrameL(CEikScrollBarFrame* aFrame);
	virtual void RemoveExternalFrame(CEikScrollBarFrame* aFrame);
	virtual void DisconnectExternalFrames();
	virtual void CreateRequiredComponentsL();
	virtual void DestroyButton(CAknScrollButton*& aButton);
	virtual void SetButtonPositionL(CAknScrollButton* aButton);
    virtual TInt ScrollBarType();
    virtual void SetScrollBarObserver(MEikScrollBarObserver* aScrollBarObserver);
	virtual MEikScrollBarObserver* ScrollBarObserver();
	virtual TBool HasModelChanged(const TEikScrollBarModel* aModel);
private:
    virtual TInt Reserved_1();
    virtual TInt Reserved_2();

public: 
	CEikCba* iCba;
	CArrayFixFlat<CEikScrollBarFrame*> iExternalFrames;
	
	MEikScrollBarObserver* iScrollBarObserver;
private:
    CEikScrollBar* iParent;
    TInt           iSpare1;
    TInt           iSpare2;
    TInt           iSpare3;
	};

//
// class CAknDoubleSpanScrollBarExtension
//
// This class is an extension class for CAknDoubleSpanScrollBar class. 
//
NONSHARABLE_CLASS(CAknDoubleSpanScrollBarExtension) : public CEikScrollBarExtensionImpl
    {
public:
    CAknDoubleSpanScrollBarExtension(CEikScrollBar* aParent);
    ~CAknDoubleSpanScrollBarExtension();
    virtual void SetLengthL(TInt aLength);
    virtual void SetModelL(const TEikScrollBarModel* aModel);
    virtual void SetModel(const TEikScrollBarModel* aModel);
    virtual void SetLengthAndModelL(TInt aLength,const TEikScrollBarModel* aModel);
    virtual void SetModelThumbPosition(TInt aThumbPos);
    virtual void SetFocusPosToThumbPos(TInt aFocusPosition);
    virtual TInt ThumbPosition() const;
    virtual TInt ScrollBarBreadth() const;
    virtual void SetDecreaseButtonsDimmed(TBool aDimmed);
    virtual void SetIncreaseButtonsDimmed(TBool aDimmed);
    virtual void SetAllButtonsDimmed(TBool aDimmed);
    virtual void SetContainingCba(CEikCba* aCba);
    virtual void CreateButtonL(CAknScrollButton*& aButton,CAknScrollButton::TType aType);
    virtual void DoSetModel(const TEikScrollBarModel* aModel);
    virtual CEikCba* Cba() const;
    virtual void AddExternalFrameL(CEikScrollBarFrame* aFrame);
    virtual void RemoveExternalFrame(CEikScrollBarFrame* aFrame);
    virtual void DisconnectExternalFrames();
    virtual void CreateRequiredComponentsL();
    virtual void DestroyButton(CAknScrollButton*& aButton);
    virtual void SetButtonPositionL(CAknScrollButton* aButton);
    virtual TInt ScrollBarType();
    virtual void SetScrollBarObserver(MEikScrollBarObserver* aScrollBarObserver);
	virtual MEikScrollBarObserver* ScrollBarObserver();
	virtual TBool HasModelChanged(const TEikScrollBarModel* aModel);
	static TInt ScheduledDraw( TAny* aThis );
	void DoScheduledDraw();
private:
    virtual TInt Reserved_1();
    virtual TInt Reserved_2();
public:
    CAknDoubleSpanScrollIndicator* iScrollIndicator;
	CArrayFixFlat<CEikScrollBarFrame*> iExternalFrames;
    TRect iFixedLayoutRect;
    
    MEikScrollBarObserver* iScrollBarObserver;
    TInt iPointerDownOn;
    TInt iPointerDownPosition;
    TInt iPointerOffsetFromThumb;
    
    CAknInfoPopupNoteController* iPopupController;
    TBool iShowPopup;
    MEikScrollBarObserver* iOwningScrollBarObserver;
    CAknTouchAreaControl* iTouchAreaControl;
    TInt iScrollBarFlags;
    /** extension area type. */
    TInt iExtensionType;
    TBool iDragged;
    TTime iLastDrag;
private:
    CEikScrollBar* iParent;
    CIdle*         iActiveScheduledDraw;
    TInt           iSpare2;
    TInt           iSpare3;
    TEikScrollBarModel iPreviousModel;
    };

//
// class CEikScrollBarFrameExtension
//
// This class is an extension class for CEikScrollBarFrame class. 
//    

class CEikScrollBarFrameExtension
	{
public:
    CEikScrollBarFrameExtension();
    ~CEikScrollBarFrameExtension();

public: 
	CCoeControl* iParentWindow;
    CEikScrollBarFrame::SBarData iH;
    MEikScrollBarObserver* iScrollBarObserver;
	};

#endif
