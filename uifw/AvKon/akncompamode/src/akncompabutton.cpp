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
* Description:  Compatibility keyboard button
*
*/



#include <barsread.h>
#include <fbs.h>
#include <gulicon.h>
#include <AknsSkinInstance.h>
#include <AknsUtils.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <coecntrl.h>
#include <touchfeedback.h>

#include "akncompabutton.h"
#include "akncompakb.h"

// --------------------------------------------------------------------------
// Factory function
// --------------------------------------------------------------------------
CAknCompaButton* CAknCompaButton::NewLC(TResourceReader& aReader)
    {
    CAknCompaButton* self = new(ELeave) CAknCompaButton(0);
    CleanupStack::PushL(self);
    self->ConstructL();
    self->ConstructFromResourceL(aReader);
    return self;
    }

// --------------------------------------------------------------------------
// Constructor
// --------------------------------------------------------------------------
CAknCompaButton::CAknCompaButton(TInt aFlags):CAknButton(aFlags)
    {
    }

// --------------------------------------------------------------------------
// Update colors for text and icon
// --------------------------------------------------------------------------
void CAknCompaButton::UpdateColors()
    {   
    TRgb buttonColor;
    
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    AknsUtils::GetCachedColor( skin, buttonColor,
        KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG20 );
    
    // If button has text, updating text colors
    if (iFlags.iHasText)
        {        
        TRAP_IGNORE(AknLayoutUtils::OverrideControlColorL(*this, 
            EColorButtonText, buttonColor));
        
        TRAP_IGNORE(AknLayoutUtils::OverrideControlColorL(*this, 
            EColorButtonTextPressed, buttonColor));
        }
       
    // If button has icon, updating icon color
    if (iFlags.iHasIcon)
        {                 
        CFbsBitmap* bitmap = State()->Icon()->Bitmap();
                                                          
        // Not updating colors of rocker button icons,
        // they remain original in all skin themes
        if (!iFlags.iIsRocker)
            {
            AknIconUtils::SetIconColor(bitmap, buttonColor);
            }
        AknIconUtils::SetSize(bitmap, iIconSize, EAspectRatioPreserved);
        }
    }

// --------------------------------------------------------------------------
// Set layout for text and icon
// --------------------------------------------------------------------------
void CAknCompaButton::LayoutIconAndText()
    {
    TRect parentRect(Rect());
    TAknLayoutText buttonText;

    if (iFlags.iHasText)
        {
        // Button contains text
        buttonText.LayoutText(parentRect,
            AknLayoutScalable_Avkon::cell_cmode_itu_pane_t2_cp(0,0,0));
        SetTextFont(buttonText.Font());
        }

    if (iFlags.iHasIcon)
        {
        TAknLayoutRect layoutRect;
         
        if (iFlags.iHasText)
            {
            // Button contains text and icon
            layoutRect.LayoutRect(parentRect, AknLayoutScalable_Avkon::
                cell_cmode_itu_pane_g1_cp(0,0,0).LayoutLine());
            iIconSize = layoutRect.Rect().Size();

            TInt margin = (buttonText.TextRect().Height() * 2);
            SetMargins(TMargins8(0,0,margin,0));
            SetTextHorizontalAlignment(CGraphicsContext::ERight);
            SetIconHorizontalAlignment(CAknButton::ERight);
            SetTextAndIconAlignment(CAknButton::EIconAfterText);
            }
        else
            {
            // Button contains only icon
            layoutRect.LayoutRect(parentRect, AknLayoutScalable_Avkon::
                cell_cmode_rocker_pane_g1_cp(0,0,0).LayoutLine());
            TRect tmp = layoutRect.Rect();
            tmp.Shrink(5,5);
            iIconSize = tmp.Size();
            SetMargins(TMargins8(0,0,0,0));
            }

        SetIconScaleMode(EAspectRatioPreserved);
        SetIconSize(iIconSize);
        }
    }

// --------------------------------------------------------------------------
// Check if button is locked down
// --------------------------------------------------------------------------
TBool CAknCompaButton::IsLockedDown()
    {
    return iFlags.iLongTap;
    }

// --------------------------------------------------------------------------
// Check if button is pressed
// --------------------------------------------------------------------------
TBool CAknCompaButton::IsPressed()
    {
    return iButtonPressed;
    }

// --------------------------------------------------------------------------
// Check if button is a rocker button
// --------------------------------------------------------------------------
TBool CAknCompaButton::IsRocker()
    {
    return iFlags.iIsRocker;
    }

// --------------------------------------------------------------------------
// Get icon from a resource
// --------------------------------------------------------------------------
CGulIcon* CAknCompaButton::GetIconLC(TInt aBmpId, TInt aMaskId )
    {
    _LIT(KBmpFilePath, "z:\\resource\\apps\\avkon2.mif");

    CFbsBitmap* bitmap;
    CFbsBitmap* mask;

    AknIconUtils::CreateIconL(bitmap, mask, KBmpFilePath, aBmpId,
        aMaskId);    
    CGulIcon* icon = CGulIcon::NewL(bitmap, mask);
    CleanupStack::PushL(icon);
    return icon;
    }

// --------------------------------------------------------------------------
// Construct button from a resource
// --------------------------------------------------------------------------
void CAknCompaButton::ConstructFromResourceL(TResourceReader& aReader)
    {
    iScanCode = aReader.ReadInt16();
    TInt textId = aReader.ReadInt32();
    HBufC* buttonText = textId ?
        iCoeEnv->AllocReadResourceLC(textId) : HBufC::NewLC(0);

    TInt bmpId = 0;
    TInt maskId = 0;

    bmpId = aReader.ReadInt16();
    maskId = aReader.ReadInt16();

    CGulIcon* icon = NULL;
    if (bmpId > 0)
        {
        icon = GetIconLC(bmpId, maskId);
        }                    
    AddStateL(icon, NULL, NULL, NULL, *buttonText, KNullDesC, 0);    
    
    if (icon)
        {
        CleanupStack::Pop(); // icon
        }
        
    iFlags.iIsRocker =
        iScanCode == EStdKeyUpArrow || iScanCode == EStdKeyDownArrow ||
        iScanCode == EStdKeyLeftArrow || iScanCode == EStdKeyRightArrow ||
        iScanCode == EStdKeyDevice3;

    iFlags.iHasIcon = (icon != NULL);
    iFlags.iHasText = (textId != 0);

    CleanupStack::PopAndDestroy(); // buttonText
    }

// --------------------------------------------------------------------------
// Set button to up state
// --------------------------------------------------------------------------
void CAknCompaButton::SetButtonUpL()
    {
    
    FeedEventToAknButtonL(EButtonUp);
    // AknButton does not offer an option to change state on both up and
    // down events. Since we have set AknButton flag to change state on
    // down events, we have to bring state up "manually" even when up
    // event was sent to button.
    static_cast<CAknCompaKb*>(Parent())->
        SimulateKeyPressL(iScanCode, EFalse);
        
    }

// --------------------------------------------------------------------------
// Get button key scan code
// --------------------------------------------------------------------------
TInt CAknCompaButton::ScanCode()
    {
    return iScanCode;
    }

// --------------------------------------------------------------------------
// Make button ready to draw
// --------------------------------------------------------------------------
void CAknCompaButton::ActivateL()
    {
    // CAknButton::ActivateL() is overriden to prevent it to enable pointer
    // drag events and stray events
    CAknControl::ActivateL();
    }

// --------------------------------------------------------------------------
// Pointer event handling
// --------------------------------------------------------------------------
void CAknCompaButton::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    // We want button to get into pressed state only when
    // stylus down occurs on it (not getting into pressed
    // state when dragged out and back again).
    // Button stays in a down state unless stulys up occurs
    // on top of it or less than x distance from it (button
    // can be left down by dragging stylus out of it far enough).
    // CAknButton doesn't offer this kind of behaviour.
    // Therefore pointer up events are handled here.

    // The framework calls button's HandlePointerEventL() if stylus
    // down hits the button or subsequent stulys up event
    if (aPointerEvent.iType == TPointerEvent::EButton1Down)
        {
        iFlags.iLongTap = EFalse; // long tap leaves key down
        TactileFeedback();

        // CAknButton::HandlePointerEventL() checks PenEnabled() which
        // returns false current layout is QVGA. Therefore use key-event
        // to put button into down state.
        FeedEventToAknButtonL(EButtonDown);
        }
    else if (aPointerEvent.iType == TPointerEvent::EButton1Up)
        {
        // If pen button is "locked down", it is released if any other than
        // rocker button is released. This way user doesn't have to release
        // it manually after copy-paste or list marking.
        if (!iFlags.iIsRocker && iScanCode != EStdKeyRightShift)
            {
            static_cast<CAknCompaKb*>(Parent())->SetPenButtonUpL();
            }

        if (!iFlags.iLongTap)
            {
            SetButtonUpL();
            }
        }
    else
        {} // lint
    }

// --------------------------------------------------------------------------
// Handle control events from CAknButton
// --------------------------------------------------------------------------
void CAknCompaButton::HandleControlEventL(CCoeControl* /*aControl*/,
    TCoeEvent aEventType)
    {
    switch(aEventType)
        {
        // Button reports of state change when it is pressed
        case EEventStateChanged:
            static_cast<CAknCompaKb*>(Parent())->
                SimulateKeyPressL(iScanCode, ETrue); // key down
            break;
        // Button reports of long press
        case CAknButton::ELongPressEvent:
            TactileFeedback();
            iFlags.iLongTap = ETrue;
            break;
        default:
            break;
        }
    }

// --------------------------------------------------------------------------
// Feed button event to AknButton
// --------------------------------------------------------------------------
void CAknCompaButton::FeedEventToAknButtonL(TButtonState aState)
    {
    // Feed key-event to AknButton to change it's state
    static const TKeyEvent keyEvent = {0, EStdKeyDevice3, 0, 0};
    OfferKeyEventL(keyEvent,
        aState ==  EButtonDown ? EEventKeyDown:EEventKeyUp);
    }

// --------------------------------------------------------------------------
// Give tactile feedback for touch event
// --------------------------------------------------------------------------
void CAknCompaButton::TactileFeedback()
    {
    // Feedback/basic on down event
    MTouchFeedback* feedback = MTouchFeedback::Instance();
    if (feedback)
        {
        feedback->InstantFeedback( this, ETouchFeedbackBasic );
        }
    }

// --------------------------------------------------------------------------
// Handle changes to button resources
// --------------------------------------------------------------------------
void CAknCompaButton::HandleResourceChange(TInt aType)
    {
    
    // No need to call CAknButton::HandleResourceChange(),
    // button icon and text is updated by CompaButton      
    if(aType == KAknsMessageSkinChange)
        {
        UpdateColors();
        }
    }
