/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Compatibility mode keyboard button
*
*/


#ifndef __AKNCOMPABUTTON_H__
#define __AKNCOMPABUTTON_H__

#include <coecobs.h>    // MCoeControlObserver
#include <aknbutton.h>

/**
 * Compatibility mode keyboard button
 *
 * Single button of compa-keyboard
 *
 * @since S60 v5.0
 */
NONSHARABLE_CLASS(CAknCompaButton) : public CAknButton,
    public MCoeControlObserver
    {
public: // types
    enum TButtonState
        {
        EButtonUp,
        EButtonDown,
        ENumStates
        };

public: // constructors

    static CAknCompaButton* NewLC(TResourceReader& aReader);

public: // new functions

    void SetButtonUpL();
    TInt ScanCode();
    void UpdateColors();
    void LayoutIconAndText();
    TBool IsLockedDown();
    TBool IsPressed();
    TBool IsRocker();
   
protected: // from CAknButton

    void ConstructFromResourceL(TResourceReader& aReader);

    void ActivateL();

    void HandlePointerEventL(const TPointerEvent& aPointerEvent);
   
//    void Draw( const TRect& aRect ) const;
    
private: // functions
    CAknCompaButton(TInt aFlags);   

    void FeedEventToAknButtonL(TButtonState aState);
    void TactileFeedback();
    CGulIcon* GetIconLC(TInt aBmpId, TInt aMaskId);

private: // from MCoeControlObserver

    /**
    * This function is called when a control for which this control is the
    * observer calls CCoeControl::ReportEventL(). Button pointer events are
    * handled here.
    * @param aControl The control that sent the event.
    * @param aEventType The event type. 
    */
    void HandleControlEventL(CCoeControl *aControl, TCoeEvent aEventType);

    void HandleResourceChange(TInt aType);

private: // data
    TInt iScanCode;
    TSize iIconSize;
   
    struct
        {
        bool iHasIcon:1;
        bool iHasText:1;
        bool iLongTap:1; // long tap event received
        bool iIsRocker:1; // button is a rocker button
        } iFlags;
    };

#endif // __AKNCOMPABUTTON_H__
