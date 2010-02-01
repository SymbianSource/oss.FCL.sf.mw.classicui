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


#ifndef __AKNCOMPAKB_H__
#define __AKNCOMPAKB_H__

#include <AknControl.h>

#include "akncompautils.h"
#include "akncompasrvclient.h"
#include "akncompabutton.h"

class CAknCompaSide;
class CAknsBasicBackgroundControlContext;
class TAknWindowComponentLayout;
class TAknLayoutScalableParameterLimits;
class CRepository;

/**
 * Compatibility mode keyboard component.
 *
 * The component is used by CAknAppUiBase to present a keyboard
 * for compatibility mode application.
 *
 * @lib compamode.lib
 * @since S60 v5.0
 */
NONSHARABLE_CLASS(CAknCompaKb) : public CAknControl,
    public MCoeForegroundObserver
    {
    enum
        {
        EButtonsGranularity = 24,
        };

public: // constructors and destructor

    static CAknCompaKb* NewL(TInt aCompaScreenMode, TBool aMakeVisible);

    ~CAknCompaKb();

public: // new functions

    void SimulateKeyPressL(TInt aScanCode, TBool aDown);

    void SetPenButtonUpL();

    void SetButtonsUpL();    

    TBool IsForeground();

    void DisaTransEffects(bool aDisable);

private: // new functions

    CAknCompaKb(TInt aCompaScreenMode);

    void ConstructL(TBool aMakeVisible);

    void SkinChanged();
    
    TRect RectFromLayout(const TRect& aParent,
        const TAknWindowComponentLayout& aComponentLayout);

    void LayoutControl();
    
    void LayoutButtonControls();

    void LayoutButtonGrid(TRect aParentRect, TInt& aButtonCount,
        TInt aRows, TInt aColumns);
        
    void SetSkinBackground();

    TBool InCompaScreenMode();
private: // from CCoeControl

    TInt CountComponentControls() const;

    CCoeControl* ComponentControl(TInt aIndex) const;

    void Draw(const TRect& aRect) const;

    void HandleResourceChange(TInt aType);

    void ActivateL();

    void MakeVisible(TBool aVisible);

private: // from MCoeForegroundObserver

    void HandleGainingForeground();
    void HandleLosingForeground();

private: // data

    TRgb iSkinColor;
    CFbsBitGc* iBitGc;

    CFbsBitmapDevice* iBitmapDevice;

    TRect iCompaRect;

    // Background bitmap, owned
    CFbsBitmap* iSkinBmp;

    // Background context
    CAknsBasicBackgroundControlContext* iBgContext;

    TInt iCompaScreenMode;
    TInt iRockerGridSize;
    // Button controls. Owned
    RPointerArray<CAknCompaButton> iButtons;
    TInt iPenButtonIndex; // button array index of pen button

    // Controls to fill sides of compa-mode window
    CAknCompaSide* iLeftSide;
    CAknCompaSide* iRightSide;

    RAknCompaSrvSession iCompaSrvSession;

    CRepository* iThemesCenRep; // repository controlling transition effects
    struct
        {
        bool iInEikSrv:1; // running in eikon server
        bool iInAknCapSrv:1; // running in AknCap server
        bool iInGlobalUiSrv:1; // running in akncapserver/aknnfysrv/eiksrv
        bool iLayoutDone:1; // control size/position has been set
        bool iEffectsDisa:1; // transition effects are disabled
        bool iForeground:1; // application is foreground
        } iFlags;
    };

#endif // __AKNCOMPAKB_H__
