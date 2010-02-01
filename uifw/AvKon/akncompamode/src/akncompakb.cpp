/*
* Copyright (c) 2007-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Compatibility mode keyboard UI component
*
*/


#include <e32base.h>
#include <AknsUtils.h> 
#include <AknsSkinInstance.h>
#include <AknsDrawUtils.h>
#include <AknsBasicBackgroundControlContext.h>
#include <centralrepository.h>
#include <AvkonInternalCRKeys.h>
#include <pslninternalcrkeys.h>
#include <aknlayoutscalable_avkon.cdl.h>

#include "akncompakb.h"
#include "akncompaside.h"

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
CAknCompaKb* CAknCompaKb::NewL(TInt aCompaScreenMode, TBool aMakeVisible)
    {
    CAknCompaKb* self = new (ELeave) CAknCompaKb(aCompaScreenMode);
    CleanupStack::PushL(self);
    self->ConstructL(aMakeVisible);
    CleanupStack::Pop(self);
    return self;
    }

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
void CAknCompaKb::ConstructL(TBool aMakeVisible)
    {
    // Connect to key server is not delayed until buttons are pressed
    // as we don't want application to fail while it's executing due
    // to a key press.
    // Optimization: akncapserver/aknnfysrv/eiksrv have compakeyboard
    // always instantiated. akncapserver/aknnfysrv simulate raw events
    // without compakeysrv. Eikon server doesn't have capability to
    // simulate raw events directly. In this case connection to the key
    // server press is delayed until a key is pressed. This way key server
    // is not running all the time.
    RProcess process;
    TSecureId secureId = process.SecureId();
    iFlags.iInEikSrv = AknCompaUtils::IsEikSrv(secureId);
    iFlags.iInAknCapSrv = AknCompaUtils::IsAknCapSrv(secureId);
    iFlags.iInGlobalUiSrv = AknCompaUtils::IsGlobalUiSrv(secureId);
    if (!iFlags.iInGlobalUiSrv)
        {
        User::LeaveIfError(iCompaSrvSession.Connect());
        iThemesCenRep = CRepository::NewL(KCRUidThemes);
        }

    // Transition effects do not work in compa-mode (centered window). They
    // are disabled when screen mode is compa-mode. In case device was
    // powered off while effects were disabled, restore transition effects
    // state.
    if (iFlags.iInAknCapSrv)
        {
        // Enable transition effects if device was powered off while
        // we had them disabled.
        if (iCompaSrvSession.Connect() == KErrNone)
            {
            iCompaSrvSession.RestoreTransEffects();
            iCompaSrvSession.Close();
            }
        }

    CreateWindowL();
    RWindow& window = Window();
    // Prevent fading when application displays a dialog
    window.SetNonFading(ETrue);
    // Ordinal priority is not usually set for application windows
    // (only for window groups). Compa keyboard is set to high ordinary
    // priority. This keeps it always at front and prevents other windows
    // (eg. menus, dialogs) capturing pointer events.
    // If an application would set one it's own windows to higher
    // priority, it could capture pointer events but menus and dialogs
    // wouldn't work either in that case.
    const TInt KOrdinalPriority = ECoeWinPriorityAlwaysAtFront + 1;
    window.SetOrdinalPosition(window.OrdinalPosition(), KOrdinalPriority);
    // Request pointer up event event if stylus is dragged out of this window
    window.SetPointerGrab(ETrue);
    // Capture pointer events from this window group. This prevents
    // touch working in application window even when the application
    // doesn't observe layout's PenEnabled.
    window.SetPointerCapture(RWindowBase::TCaptureEnabled);
    
    iBgContext = CAknsBasicBackgroundControlContext::NewL(
        KAknsIIDQsnBgScreen, Rect(), ETrue);

    // Get skin background, this method is used to update it also
    SkinChanged();

    // Construct buttons
    AknCompaUtils::ReadButtonsL(iButtons, iPenButtonIndex, *iCoeEnv);
    for(TInt i = 0; i < iButtons.Count(); i++)
        {
        CAknCompaButton* button = iButtons[i];
        button->SetContainerWindowL(*this);
        button->SetObserver(button);
        }

    iLeftSide = CAknCompaSide::NewL();
    iRightSide = CAknCompaSide::NewL();
    
    // Set constrol and buttons size and position. If control is left
    // invisible, screen mode is not compa-mode and layout is postponed
    // until screen mode is compa-mode.
    if (aMakeVisible)
        {
        LayoutControl();
        }

    // Add to control stack to receive KEikDynamicLayoutVariantSwitch
    // events
    iCoeEnv->AppUi()->AddToStackL(this, ECoeStackPriorityDefault,
        ECoeStackFlagRefusesAllKeys);

    iCoeEnv->AddForegroundObserverL(*this);

    // Compa-mode keyboard is made visible in the case of a normal
    // applications. Compa-keyboard is also created for servers
    // that display global/notes notifications but left invisible.
    // Visibility of the keyboard is controlled according to current
    // screen mode. It's visible only in compa screen mode. Note:
    // It's also possible for a screen mode to change (e.g. due to
    // some application exiting) while a global note is on display.
    if (aMakeVisible)
        {
        ActivateL();
        }
    }

// --------------------------------------------------------------------------
// Constructor
// --------------------------------------------------------------------------
CAknCompaKb::CAknCompaKb(TInt aCompaScreenMode):
    iButtons(EButtonsGranularity)
    {
    iCompaScreenMode = aCompaScreenMode;
    }

// --------------------------------------------------------------------------
// Destructor
// --------------------------------------------------------------------------
CAknCompaKb::~CAknCompaKb()
    {
    iCoeEnv->AppUi()->RemoveFromStack(this);
    iCoeEnv->RemoveForegroundObserver(*this);

    iButtons.ResetAndDestroy();
    delete iLeftSide;
    delete iRightSide;

    delete iBgContext;

    // Keyserver sends up events if client has any keys in down state
    // when session is closed
    iCompaSrvSession.Close();

    delete iThemesCenRep;
    }

// --------------------------------------------------------------------------
// Simulate a key press to application
// --------------------------------------------------------------------------
void CAknCompaKb::SimulateKeyPressL(TInt aScanCode, TBool aDown)
    {
    if (!iFlags.iInGlobalUiSrv)
        {
        // Key press is simulated via a server as SwEvent capability
        // is needed
        iCompaSrvSession.SimulateKeyEventL(aScanCode, aDown);
        }
    else if (iFlags.iInEikSrv)
        {
        // Eikon server. Connect to key server only when needed.
        // Connection to key server should succeed as it is already
        // started by an application that set screen mode to compa.
        if (iCompaSrvSession.Handle() == KNullHandle)
            {
	        User::LeaveIfError( iCompaSrvSession.Connect() );
            }
        if (iCompaSrvSession.Handle() != KNullHandle)
            {
            iCompaSrvSession.SimulateKeyEventL(aScanCode, aDown);
            }
        }
    else
        {
        // akncapserver and aknnfysrv don't use compakeysrv
        TRawEvent rawEvent;        
        rawEvent.Set(
            aDown ? TRawEvent::EKeyDown:TRawEvent::EKeyUp, aScanCode);
        RWsSession& wsSession = iCoeEnv->WsSession();
        wsSession.SimulateRawEvent(rawEvent);
        wsSession.Flush();
        }
    }

// --------------------------------------------------------------------------
// Set "pen" button to up state
// --------------------------------------------------------------------------
void CAknCompaKb::SetPenButtonUpL()
    {
    if (iPenButtonIndex != KErrNotFound)
        {
        CAknCompaButton* compaButton = iButtons[iPenButtonIndex];
        if (compaButton->IsPressed())
            {
            compaButton->SetButtonUpL();
            }
        }
    }

// --------------------------------------------------------------------------
// Set buttons to up state
// --------------------------------------------------------------------------
void CAknCompaKb::SetButtonsUpL()
    {
    TInt cnt = iButtons.Count();
    for(TInt i = 0; i < cnt; i++)
        {
        CAknCompaButton* compaButton = iButtons[i];
        if (compaButton->IsPressed())
            {
            compaButton->SetButtonUpL();            
            }
        }
    }

// --------------------------------------------------------------------------
// Check is compa-mode application is on foreground
// --------------------------------------------------------------------------
TBool CAknCompaKb::IsForeground()
    {
    // Voice command application is launched on top of foreground application
    // in QHD mode. If it is launched on top of compa-mode application
    // the screen gets messed up. Compa-mode app is showing behind voice
    // dialer but wserv right shifting is lost. Workaround for this is to
    // switch idle screen to foreground before voice commander is launched.
    // Switch to idle screen if this is a regular application or if global
    // note is showing on top of compa-mode application.
    return !iFlags.iInGlobalUiSrv || InCompaScreenMode();
    }

// --------------------------------------------------------------------------
// Disable transition effects in compa-mode
// --------------------------------------------------------------------------
void CAknCompaKb::DisaTransEffects(bool aDisable)
    {
    // Transition effects cannot be disabled per application. They can be
    // disabled globally from central repository. Transition effects are
    // disabled whenever screen mode changes to compa-mode by AknCapServer.
    if (iFlags.iInAknCapSrv && iFlags.iEffectsDisa != aDisable)
        {
        if (iCompaSrvSession.Handle() == KNullHandle)
            {
	        User::LeaveIfError( iCompaSrvSession.Connect() );
            }
        if (iCompaSrvSession.Handle() != KNullHandle)
            {
            if (aDisable)
                {
                iCompaSrvSession.DisaTransEffects();
                }
            else
                {
                iCompaSrvSession.RestoreTransEffects();
                iCompaSrvSession.Close();
                }
            iFlags.iEffectsDisa = aDisable;
            }
        }
    }

// ---------------------------------------------------------------------------
// Return wanted layout rectangle
// ---------------------------------------------------------------------------
TRect CAknCompaKb::RectFromLayout( const TRect& aParent,
    const TAknWindowComponentLayout& aComponentLayout )
    {
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect(aParent, aComponentLayout.LayoutLine());
         
    return layoutRect.Rect();
    }

// --------------------------------------------------------------------------
// Layout compamode controls
// --------------------------------------------------------------------------
void CAknCompaKb::LayoutControl()
    {   
    TPoint origin =
        iCoeEnv->ScreenDevice()->GetScreenModeOrigin(iCompaScreenMode);
    
    TRect screenRect;
    AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EScreen, screenRect);
    
    // parent rect for all compamode components      
    iCompaRect = RectFromLayout(screenRect,
        AknLayoutScalable_Avkon::compa_mode_pane());
                  
    TRect compaKbRect = RectFromLayout(iCompaRect,
        AknLayoutScalable_Avkon::compa_mode_pane_g3());
       
    AknCompaUtils::ScaleRect(compaKbRect, -origin.iX, 0);    
    SetRect(compaKbRect);    
    
    // side controls
    TRect leftSide = RectFromLayout(iCompaRect,
        AknLayoutScalable_Avkon::compa_mode_pane_g1());
    
    TRect rightSide = RectFromLayout(iCompaRect,
        AknLayoutScalable_Avkon::compa_mode_pane_g2());
    
    AknCompaUtils::ScaleRect(rightSide, -origin.iX, 0); 
    iRightSide->SetRect(rightSide);
    
    // Support for not centered compa window.
    // Left side control has to be moved to other side if not centered
    if(origin.iX == 0)
        {
        origin.iX -= screenRect.Width();
        }

    AknCompaUtils::ScaleRect(leftSide, -origin.iX, 0);   
    iLeftSide->SetRect(leftSide);
         
    LayoutButtonControls();   
    SetSkinBackground();
    iFlags.iLayoutDone = ETrue;
    }

// --------------------------------------------------------------------------
// Layout button controls
// --------------------------------------------------------------------------
void CAknCompaKb::LayoutButtonControls()
    {                  
    TRect rockerRect = RectFromLayout(iCompaRect,
        AknLayoutScalable_Avkon::main_comp_mode_rocker_pane_cp());

    TRect ituRect = RectFromLayout(iCompaRect,
        AknLayoutScalable_Avkon::main_comp_mode_itu_pane_cp());
    
    if (iButtons.Count() > 0)
        {
        TAknLayoutScalableParameterLimits buttonLimits =
            AknLayoutScalable_Avkon::cell_cmode_rocker_pane_cp_ParamLimits();

        // Calculating number of rocker pane buttons
        iRockerGridSize = ((buttonLimits.LastRow() + 1) *
            (buttonLimits.LastColumn() + 1));

        TInt buttonCount = 0;
  
        LayoutButtonGrid(rockerRect, buttonCount, buttonLimits.LastRow(),
            buttonLimits.LastColumn());

        buttonLimits =
            AknLayoutScalable_Avkon::cell_cmode_itu_pane_cp_ParamLimits();

        LayoutButtonGrid(ituRect, buttonCount, buttonLimits.LastRow(),
            buttonLimits.LastColumn());

        for(TInt i = 0; i < iButtons.Count(); i++)
            {
            CAknCompaButton* button = iButtons[i];        
            TRect rect = button->Rect();    
            AknCompaUtils::ScaleRect(rect, 0, -iCompaRect.Height());
                    
            button->SetRect(rect);    
            button->UpdateColors();
            button->LayoutIconAndText();
            }
        }
    }


// --------------------------------------------------------------------------
// Layout grid of buttons
// --------------------------------------------------------------------------
void CAknCompaKb::LayoutButtonGrid(TRect aParentRect, TInt& aButtonCount,
    TInt aRows, TInt aColumns)
    {
    for(TInt row = 0; row <= aRows; row++)
        {
        for(TInt col = 0; col <= aColumns; col++)
            {
            if(aButtonCount < iRockerGridSize)
                {
                AknLayoutUtils::LayoutControl(iButtons[aButtonCount],
                    aParentRect, AknLayoutScalable_Avkon::
                    cell_cmode_rocker_pane_cp(0,col,row));
                }
            else
                {
                AknLayoutUtils::LayoutControl(iButtons[aButtonCount],
                    aParentRect, AknLayoutScalable_Avkon::
                    cell_cmode_itu_pane_cp(0,col,row));
                }
            aButtonCount++;
            }
        }
    }

// --------------------------------------------------------------------------
// 
// --------------------------------------------------------------------------
void CAknCompaKb::SetSkinBackground()
    {
    TPoint origin =
        iCoeEnv->ScreenDevice()->GetScreenModeOrigin(iCompaScreenMode);
    
    TPoint origo(0, 0);

    // Skin background context
    iBgContext->SetParentPos(origo);
    AknCompaUtils::ScaleRect(iCompaRect, -origin.iX, 0);
    iBgContext->SetRect(iCompaRect);
    
    iLeftSide->SetBackground(origin);
    iRightSide->SetBackground(origin);
    
    }

// --------------------------------------------------------------------------
// Check if current screen mode is compa-mode
// --------------------------------------------------------------------------
TBool CAknCompaKb::InCompaScreenMode()
    {
    return iCoeEnv->ScreenDevice()->CurrentScreenMode() ==
        iCompaScreenMode;
    }

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
TInt CAknCompaKb::CountComponentControls() const
    {
    return iButtons.Count();
    }

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
CCoeControl* CAknCompaKb::ComponentControl(TInt aIndex) const
    {
    return iButtons[aIndex];
    }

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
void CAknCompaKb::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
   
    // If skin background draw fails, flat color will be used
    if(!AknsDrawUtils::Background(skin, iBgContext, this, gc, aRect))
        {
        gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
        gc.SetPenColor(iSkinColor);
        gc.SetBrushColor(iSkinColor);     
        gc.DrawRect(Rect());
        }

    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.SetPenColor(iSkinColor);
    gc.SetBrushColor(iSkinColor);

    // Draw background rects for rocker buttons.
    // These are drawn under the buttons to achieve transparency effect.    
    for(TInt i = 0; i < iButtons.Count(); i++)
        {
        CAknCompaButton* button = iButtons[i];
           
        if (button->IsRocker())
            {
            gc.DrawRect(button->Rect());
            }
        }  
    }
    
// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
void CAknCompaKb::HandleResourceChange(TInt aType)
    {
    switch(aType)
        {
        // Compa-mode application is fixed to QVGA layout and cannot change.
        // When Avkon notify server is displaying a global note, it's
        // possible for layout to change. Compa-keyboard is hidden if
        // screen mode changes out of compa-mode.
        case KEikDynamicLayoutVariantSwitch:
            {
            TBool isScreenModeCompa = InCompaScreenMode();
            if (isScreenModeCompa && !iFlags.iLayoutDone)
                {
                // In global UI-servers, buttons size and position is set
                // only when compa-mode is entered first time.
                if (!iFlags.iLayoutDone)
                    {
                    LayoutControl();
                    // In practise ActivateL() will not leave as it allocates
                    // no resources
                    TRAP_IGNORE(ActivateL());
                    }
                }
            else
                {
                if (iFlags.iLayoutDone && iFlags.iInGlobalUiSrv)
                    {
                    MakeVisible(isScreenModeCompa);
                    }
                }
            }
            break;
        case KAknsMessageSkinChange:
            SkinChanged();
            break;
        default:
            break;
        }
    CCoeControl::HandleResourceChange(aType);
    }

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
void CAknCompaKb::ActivateL()
    {
    iLeftSide->ActivateL();
    iRightSide->ActivateL();
    CCoeControl::ActivateL();
    }

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
void CAknCompaKb::MakeVisible(TBool aVisible)
    {
    CCoeControl::MakeVisible(aVisible);
    iLeftSide->MakeVisible(aVisible);
    iRightSide->MakeVisible(aVisible);
    }

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
void CAknCompaKb::HandleGainingForeground()
    {
    iFlags.iForeground = ETrue;

    // Wait for transition effects to go into disabled. This is needed
    // in WINSCW as effects use CFbsBitGc::SetClippingRegion() which
    // panics. Global ui-servers may also be in foreground when screen
    // mode changes to foreground. For example when screen saver deactivates.
    // In this case they disable effects in KEikDynamicLayoutVariantSwitch
    // event and rely on timing of there being no draw events before effects
    // are disabled.
    if (!iFlags.iInGlobalUiSrv)
        {
        AknCompaUtils::WaitTransEffectsOff(*iThemesCenRep);
        }
    }

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
void CAknCompaKb::HandleLosingForeground()
    {
    iFlags.iForeground = EFalse;

    // AknAppUi filters stylus up events even if app leaves foreground.
    // Bring all buttons up to prevent them being left down.
    TRAP_IGNORE(SetButtonsUpL());

    // If running in eikon server, close connection to key server in
    // order to allow it to exit if no compa mode applications are
    // running
    if (iFlags.iInEikSrv)
        {
        iCompaSrvSession.Close();
        }
    }

// --------------------------------------------------------------------------
// Handle skin change event
// --------------------------------------------------------------------------
void CAknCompaKb::SkinChanged()
    {
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    // Update color for rocker button backgrounds
    AknsUtils::GetCachedColor(skin, iSkinColor, KAknsIIDQsnTextColors,
        EAknsCIQsnTextColorsCG20);
    }
