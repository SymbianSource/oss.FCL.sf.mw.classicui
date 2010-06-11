/*
* Copyright (c) 1997-2006 Nokia Corporation and/or its subsidiary(-ies).
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


#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikdefmacros.h>
#endif
#include <eikscrlb.h>
#include <eikpanic.h>
#include <eikcoctlpanic.h>
#include <eikenv.h>
#include <AknLayout.lag>
#include <eikcba.h>
#include <AknsDrawUtils.h>
#include <AknUtils.h>
#include <aknappui.h>
#include <AknsUtils.h>
#include <AknLayout2ScalableDef.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <AknInfoPopupNoteController.h>
#include <aknpointereventmodifier.h>
#include <AknTasHook.h>
#include <touchfeedback.h>


#include "AknDoubleSpanScrollIndicator.h"
#include "eikscrlb.h"
#include "EIKSBEXT.H"

const TInt KIntensity = 100; // 100%

const TInt KScrollBarWidth=9;
// const TInt KScrollButtonHeight=10;
// const TInt KArrowHeadScrollBarLength=20;

// Constants for double span scrollbar
const TInt KAknDoubleSpanScrollBarWidth = 6;
const TInt KDoubleSpanMaxModelValue     = 0x1FFF7FFF;
const TInt KDoubleSpanMinModelValue     = -0x1FFF7FFF;
const TInt16 KDoubleSpanMaxScaleValue   = 0x3FFF;
const TInt16 KDoubleSpanMinScaleValue   = 1;
const TInt KDoubleSpanMaxRawValue       = 0x8000;

// Mask values for double span scrollbar
const TUint KDoubleSpanModelMaskBitsHigh       = 0xFFFF0000;
const TUint KDoubleSpanModelMaskBitsLow        = 0x0000FFFF;
const TUint KDoubleSpanModelMaskBitsScale      = 0x3FFF0000;
const TUint KDoubleSpanModelMaskBitsType       = 0x3FFFFFFF;
const TUint16 KDoubleSpanModelMaskBitsScale16 = 0x3FFF;

const TInt KScrollRepeatTimeout = 250000; // 0.25 seconds
const TInt KScrollDragTimeout =    66000; // 0.66 seconds means 16 fps

EXPORT_C TBool TEikScrollBarModel::operator==(const TEikScrollBarModel aModel) const
    {
    return ((iScrollSpan==aModel.iScrollSpan)&(iThumbSpan==aModel.iThumbSpan)&(iThumbPosition==aModel.iThumbPosition));
    }

EXPORT_C TEikScrollBarModel::TEikScrollBarModel(TInt aScrollSpan,TInt aThumbSpan,TInt aThumbPosition)
    : iScrollSpan(aScrollSpan),
    iThumbSpan(aThumbSpan),
    iThumbPosition(aThumbPosition)
    {}

EXPORT_C TBool TEikScrollBarModel::ScrollBarUseful() const
    {
    return iThumbSpan<iScrollSpan;
    }

EXPORT_C TInt TEikScrollBarModel::MaxThumbPos() const
    {
    return iScrollSpan-iThumbSpan;
    }

EXPORT_C void TEikScrollBarModel::CheckBounds()
// Ensure the thumbposition remains within it's valid range
    {
    iThumbPosition=Max(0,Min(iThumbPosition,iScrollSpan-1));
    }

TEikScrollBarModel::TEikScrollBarModelType TEikScrollBarModel::ScrollBarModelType() const
    {
    TUint type = (~KDoubleSpanModelMaskBitsType) & iScrollSpan;
    if (type == EAknDoubleSpanScrollBarModel)
        {
        return EAknDoubleSpanScrollBarModel;
        }
    else
        {
        return EEikScrollBarModel;
        }
    }

//
// CEikScrollBar class
//

EXPORT_C CEikScrollBar::~CEikScrollBar()
// Destructor
    {
    AKNTASHOOK_REMOVE();
    DisconnectExternalFrames();
    delete(iButtons.iIncreaseNudge);
    delete(iButtons.iDecreaseNudge);
    delete iExtension;
    }

EXPORT_C CEikScrollBar::CEikScrollBar()
// Default constructor
    {
    SetNonFocusing();
    SetComponentsToInheritVisibility();
    AKNTASHOOK_ADD( this, "CEikScrollBar" );
    }

EXPORT_C void CEikScrollBar::ConstructL(MEikScrollBarObserver* aScrollBarObserver,const CCoeControl* aParent,
                                        TOrientation aOrientation,TInt /*aLength*/,TInt /*aScrollBarFlags*/)
// Second-phase construction
    {
    // If extension has not been created by deriving class, create default extension.
    if (!iExtension)
        {
        iExtension = new(ELeave) CEikScrollBarExtension(this);
        }

    if(AknLayoutUtils::PenEnabled())
        {
        CEikScrollBarExtension* extension = static_cast<CEikScrollBarExtension*> (iExtension);
        extension->SetScrollBarObserver(aScrollBarObserver);
        }

    CreateWindowL(aParent);

    if(aParent)
        SetObserver(aParent->Observer());
    else
        SetObserver(NULL);

    iOrientation=aOrientation;
    // Fix scrollbar frame's position to middle of cba
    CreateRequiredComponentsL();
    Window().SetPointerGrab(ETrue);
    EnableDragEvents();
    MakeVisible(EFalse);
    ActivateL();
    }

EXPORT_C TInt CEikScrollBar::CountComponentControls() const
    {
    TInt controlCount = 0;
    if(iButtons.iIncreaseNudge)
        {
        controlCount++;
        }
    if(iButtons.iDecreaseNudge)
        {
        controlCount++;
        }
    return controlCount;
    }

EXPORT_C CCoeControl* CEikScrollBar::ComponentControl(TInt aIndex) const
    {
    if (aIndex==0)
        return iButtons.iIncreaseNudge;
    else
        return iButtons.iDecreaseNudge;
    }

EXPORT_C void CEikScrollBar::SetLengthL(TInt /*aLength*/)
// Change the scrollbar's length.  Will redraw
    {
    }

EXPORT_C void CEikScrollBar::SetModelL(const TEikScrollBarModel* aModel)
    {
    SetModel(aModel);
    }

EXPORT_C void CEikScrollBar::SetModel(const TEikScrollBarModel* aModel)
// Change the scrollbar model
    {
    if (*aModel==iModel)
        return;
    DoSetModel(aModel);
    }

EXPORT_C void CEikScrollBar::SetLengthAndModelL(TInt /*aLength*/,const TEikScrollBarModel* aModel)
// Change the length and model at once to avoid a double update of the scrollbar
    {
    SetModel(aModel);
    }

EXPORT_C void CEikScrollBar::SetModelThumbPosition(TInt /*aThumbPos*/)
    {
    }

EXPORT_C void CEikScrollBar::SetFocusPosToThumbPos(TInt /*aFocusPosition*/)
    {
    }

EXPORT_C TInt CEikScrollBar::ThumbPosition() const
// Retrun the model's thumb position (eg in response to a scroll event)
    {
    if (iExtension)
        {
        return iExtension->ThumbPosition();
        }
    else
        {
        return 0;
        }
    }

EXPORT_C TInt CEikScrollBar::ScrollBarBreadth() const
// returns the height of a horizontal scrollbar or width of a vertical scrollbar
    {
    if (iExtension)
        {
        return iExtension->ScrollBarBreadth();
        }
    else
        {
        return 0;
        }
    }

EXPORT_C TInt CEikScrollBar::MinVisibleLength(const TInt /*aScrollBarFlags*/)
// STATIC - Calculates the minimum length in which scrollbar will remain "visible" (not necessarily with all it's components though)
    {
    return 0;
    }

EXPORT_C void CEikScrollBar::SetDecreaseButtonsDimmed(TBool /*aDimmed*/)
// Dim out the decrease buttons
    {
    }

EXPORT_C void CEikScrollBar::SetIncreaseButtonsDimmed(TBool /*aDimmed*/)
// Dim out the increase buttons
    {
    }

EXPORT_C void CEikScrollBar::SetAllButtonsDimmed(TBool /*aDimmed*/)
// Dim out all buttons
    {
    }

void CEikScrollBar::CreateRequiredComponentsL()
// Allocates and constructs all the required components of the scrollbar
    {
    if (iExtension)
        {
        iExtension->CreateRequiredComponentsL();
        }
    }

EXPORT_C void CEikScrollBar::CreateButtonL(CAknScrollButton*& /*aButton*/,CAknScrollButton::TType /*aType*/)
// Create the appropriate button
    {
    }

void CEikScrollBar::DestroyButton(CAknScrollButton*& aButton)
// destroy a button
    {
    delete aButton;
    aButton=NULL;
    }

EXPORT_C void CEikScrollBar::SetButtonPositionL(CAknScrollButton* /*aButton*/)
// Calculates and sets a buttons position,making necessary adjustments for densely packed buttons
    {
    }

void CEikScrollBar::DoSetModel(const TEikScrollBarModel* aModel)
// Just change the internal model checking it's valid
    {
    if (iExtension)
        {
        iExtension->DoSetModel(aModel);
        }
    }

void CEikScrollBar::SizeChanged()
    {
    // Update position of components
    if (iButtons.iIncreaseNudge)
        {
        TRAP_IGNORE(SetButtonPositionL(iButtons.iIncreaseNudge));
        }
    if (iButtons.iDecreaseNudge)
        {
        TRAP_IGNORE(SetButtonPositionL(iButtons.iDecreaseNudge));
        }
    }

EXPORT_C TInt CEikScrollBar::DefaultScrollBarBreadth()
    {
    return KScrollBarWidth;
    }

EXPORT_C void CEikScrollBar::HandleControlEventL(CCoeControl* /*aControl*/, TCoeEvent /*aEventType*/)
    {
    }

EXPORT_C void CEikScrollBar::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    CEikBorderedControl::HandlePointerEventL(aPointerEvent);
    }

EXPORT_C void CEikScrollBar::SetExtensionAreaType(TScrollBarExtensionAreaType aType)
    {
    if(ScrollBarType() == CEikScrollBar::EDoubleSpan)
        {
        CAknDoubleSpanScrollBarExtension* extension = static_cast<CAknDoubleSpanScrollBarExtension*> (iExtension);
        extension->iExtensionType = aType;
        }
    }

EXPORT_C void* CEikScrollBar::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CEikScrollBar::Reserved_2()
    {
    }

EXPORT_C void CEikScrollBar::MakeVisible(TBool aVisible)
    {
    if (COMPARE_BOOLS(aVisible, IsVisible()))
        return;

    TAknWindowLineLayout lay(AKN_LAYOUT_WINDOW_Control_pane_elements_Line_1);
    TAknLayoutRect lr;
    lr.LayoutRect( Rect(), lay );
    TRect r( lr.Rect() );
    SetExtent( r.iTl, TSize( aVisible ? r.Width() : 0, 2 * r.Height() ) );

    // Arrow head scroll bar will not be displayed
    if ( iExtension->ScrollBarType() == CEikScrollBar::EArrowHead )
        {
        CCoeControl::MakeVisible( EFalse );
        }
    else
        {
        CCoeControl::MakeVisible( aVisible );
        }


    if (Cba())
        {
        Cba()->UpdateCbaLabels( aVisible );
        }
    }

EXPORT_C void CEikScrollBar::SetContainingCba(CEikCba* aCba)
    {
    // This is technically a compatability break, because it means that SetContainingCba
    // must only be called after ConstructL(). Fortunately, the only place where this API
    // should ever be called is already correct.
    __ASSERT_ALWAYS(iExtension, Panic(EEikPanicScrollBarExtensionNotCreated));
    iExtension->SetContainingCba(aCba);
    }

CEikCba* CEikScrollBar::Cba() const
    {
    if (iExtension)
        return iExtension->Cba();
    else
        return NULL;
    }

void CEikScrollBar::AddExternalFrameL(CEikScrollBarFrame* aFrame)
    {
    __ASSERT_ALWAYS(iExtension, Panic(EEikPanicScrollBarExtensionNotCreated));
    iExtension->AddExternalFrameL(aFrame);
    }

void CEikScrollBar::RemoveExternalFrame(CEikScrollBarFrame* aFrame)
    {
    __ASSERT_ALWAYS(iExtension, Panic(EEikPanicScrollBarExtensionNotCreated));
    iExtension->RemoveExternalFrame(aFrame);
    }

void CEikScrollBar::DisconnectExternalFrames()
    {
    if (iExtension)
        {
        iExtension->DisconnectExternalFrames();
        }
    }

CEikScrollBar::TScrollBarType CEikScrollBar::ScrollBarType()
    {
    if (iExtension)
        {
        return static_cast<CEikScrollBar::TScrollBarType> (iExtension->ScrollBarType());
        }
    return CEikScrollBar::TScrollBarType(ENormalScrollBar);
     }



// ----------------------------------------------------------------------------
// CEikScrollBar::SetScrollBarObserver
//
// Sets scroll bar observer. This enables changing of the observer also after the
// scroll bar has been constructed.
// ----------------------------------------------------------------------------
//
void CEikScrollBar::SetScrollBarObserver(MEikScrollBarObserver* aScrollBarObserver)
    {
    if( !AknLayoutUtils::PenEnabled() )
        {
        return;
        }

    if(ScrollBarType() == CEikScrollBar::EDoubleSpan)
        {
        CAknDoubleSpanScrollBarExtension* extension = static_cast<CAknDoubleSpanScrollBarExtension*> (iExtension);
        extension->SetScrollBarObserver(aScrollBarObserver);
        }
    else
        {
        CEikScrollBarExtension* extension = static_cast<CEikScrollBarExtension*> (iExtension);
        extension->SetScrollBarObserver(aScrollBarObserver);
        }
    }

//
// class CEikScrollBarExtension
//

CEikScrollBarExtension::CEikScrollBarExtension(CEikScrollBar* aParent)
: iExternalFrames(1)
    {
    iParent=aParent;
    }

CEikScrollBarExtension::~CEikScrollBarExtension()
    {
    }


void CEikScrollBarExtension::SetLengthL(TInt /*aLength*/)
    {
    }

void CEikScrollBarExtension::SetModelL(const TEikScrollBarModel* /*aModel*/)
    {
    }

void CEikScrollBarExtension::SetModel(const TEikScrollBarModel* /*aModel*/)
    {
    }

void CEikScrollBarExtension::SetLengthAndModelL(TInt /*aLength*/,const TEikScrollBarModel* /*aModel*/)
    {
    }

void CEikScrollBarExtension::SetModelThumbPosition(TInt /*aThumbPos*/)
    {
    }

void CEikScrollBarExtension::SetFocusPosToThumbPos(TInt /*aFocusPosition*/)
    {
    }

TInt CEikScrollBarExtension::ThumbPosition() const
    {
    return(iParent->iModel.iThumbPosition);
    }

TInt CEikScrollBarExtension::ScrollBarBreadth() const
    {
    if (iParent->iOrientation==CEikScrollBar::EHorizontal)
        return iParent->iSize.iHeight;
    return iParent->iSize.iWidth;
    }

void CEikScrollBarExtension::SetDecreaseButtonsDimmed(TBool /*aDimmed*/)
    {
    }

void CEikScrollBarExtension::SetIncreaseButtonsDimmed(TBool /*aDimmed*/)
    {
    }

void CEikScrollBarExtension::SetAllButtonsDimmed(TBool /*aDimmed*/)
    {
    }

void CEikScrollBarExtension::SetContainingCba(CEikCba* aCba)
    {
    iCba = aCba;
    }

TInt CEikScrollBarExtension::ScrollBarType()
    {
    return CEikScrollBar::EArrowHead;
    }

void CEikScrollBarExtension::CreateButtonL(CAknScrollButton*& /*aButton*/,CAknScrollButton::TType /*aType*/)
    {
    }

void CEikScrollBarExtension::DoSetModel(const TEikScrollBarModel* aModel)
    {
    iParent->iModel=(*aModel);
    iParent->iModel.CheckBounds();

    TInt focusPosition=iParent->iModel.iThumbPosition;
    if ((focusPosition!=-1) && iParent && iParent->iButtons.iIncreaseNudge && iParent->iButtons.iDecreaseNudge)
        {
        iParent->iButtons.iIncreaseNudge->SetPosition(focusPosition, iParent->iModel.iScrollSpan);
        iParent->iButtons.iDecreaseNudge->SetPosition(focusPosition, iParent->iModel.iScrollSpan);
        }
    }

CEikCba* CEikScrollBarExtension::Cba() const
    {
    return iCba;
    }

void CEikScrollBarExtension::AddExternalFrameL(CEikScrollBarFrame* aFrame)
    {
    iExternalFrames.AppendL(aFrame);
    }


void CEikScrollBarExtension::RemoveExternalFrame(CEikScrollBarFrame* aFrame)
    {
    TInt count = iExternalFrames.Count();
    for (TInt ii=count-1; ii>=0; ii--)
        {
        if (iExternalFrames[ii] == aFrame)
            {
            iExternalFrames[ii]->DisconnectExternalScrollBar(iParent);
            iExternalFrames.Delete(ii);
            }
        }
    }

void CEikScrollBarExtension::DisconnectExternalFrames()
    {
    TInt count = iExternalFrames.Count();
    for (TInt ii=count-1; ii>=0; ii--)
        {
        iExternalFrames[ii]->DisconnectExternalScrollBar(iParent);
        }
    iExternalFrames.Reset();
    }

void CEikScrollBarExtension::CreateRequiredComponentsL()
    {
    TBool horiz=(iParent->iOrientation==CEikScrollBar::EHorizontal);
    iParent->CreateButtonL(iParent->iButtons.iDecreaseNudge,horiz ? CAknScrollButton::ENudgeLeft : CAknScrollButton::ENudgeUp);
    iParent->CreateButtonL(iParent->iButtons.iIncreaseNudge,horiz ? CAknScrollButton::ENudgeRight : CAknScrollButton::ENudgeDown);
    }

void CEikScrollBarExtension::DestroyButton(CAknScrollButton*& /*aButton*/)
    {
    }

void CEikScrollBarExtension::SetButtonPositionL(CAknScrollButton* /*aButton*/)
    {
    }


void CEikScrollBarExtension::SetScrollBarObserver(MEikScrollBarObserver* aScrollBarObserver)
    {
    iScrollBarObserver = aScrollBarObserver;
    }

MEikScrollBarObserver* CEikScrollBarExtension::ScrollBarObserver()
    {
    return iScrollBarObserver;
    }

TBool CEikScrollBarExtension::HasModelChanged(const TEikScrollBarModel* /*aModel*/)
    {
    return EFalse;
    }
TInt CEikScrollBarExtension::Reserved_1(){return 0;};
TInt CEikScrollBarExtension::Reserved_2(){return 0;};



//
// class CEikArrowHeadScrollBar
//

EXPORT_C CEikArrowHeadScrollBar::CEikArrowHeadScrollBar(CCoeControl* aParentWindow)
    : iParentControl(aParentWindow)
    {
    AKNTASHOOK_ADD( this, "CEikArrowHeadScrollBar" );
    }

EXPORT_C CEikArrowHeadScrollBar::~CEikArrowHeadScrollBar()
    {
    AKNTASHOOK_REMOVE();
    }

EXPORT_C void CEikArrowHeadScrollBar::ConstructL(MEikScrollBarObserver* aScrollBarObserver,const CCoeControl* aParent,
                                                 TOrientation aOrientation,TInt aLength,TInt aScrollBarFlags)
// Second-phase construction
    {
    iExtension = new(ELeave) CEikScrollBarExtension(this);
    CEikScrollBar::ConstructL(aScrollBarObserver,aParent,aOrientation,aLength,aScrollBarFlags);
    }

void CEikArrowHeadScrollBar::CreateButtonL(CAknScrollButton*& aButton,CAknScrollButton::TType aType)
// Create the appropriate button
    {
    if (aButton)
        return;
    CAknScrollButton* button=CAknScrollButton::NewL(aType);
    CleanupStack::PushL(button);
     button->CreateWindowOnlyForArrowsL(iParentControl);
    button->SetObserver((MCoeControlObserver*)this);
    SetButtonPositionL(button);
    button->SetTypeOfScrollBarUsingButton(CAknScrollButton::EArrowHead);
    CleanupStack::Pop(); // button
    aButton=button;
    }

void CEikArrowHeadScrollBar::SetButtonPositionL(CAknScrollButton* aButton)
    {
    TInt index = aButton->Type()==CAknScrollButton::ENudgeDown ? 1 : 0;
    TAknWindowLineLayout lay( AKN_LAYOUT_TABLE_Control_pane_elements(index) );
    TAknLayoutRect lr;
    lr.LayoutRect( Rect(), lay );
    TRect r( lr.Rect() );
    aButton->SetExtent( r.iTl, TSize( Size().iWidth, r.Height() ) );
    }

EXPORT_C void CEikArrowHeadScrollBar::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    CEikScrollBar::HandlePointerEventL(aPointerEvent);
    }

EXPORT_C void* CEikArrowHeadScrollBar::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

//
// class CAknDoubleSpanScrollBar
//
EXPORT_C CAknDoubleSpanScrollBar::CAknDoubleSpanScrollBar(CCoeControl* aParentWindow)
    : iParentControl(aParentWindow)
    {
    AKNTASHOOK_ADD( this, "CAknDoubleSpanScrollBar" );
    }

EXPORT_C CAknDoubleSpanScrollBar::~CAknDoubleSpanScrollBar()
    {
    AKNTASHOOK_REMOVE();
    if ( iAvkonAppUiBase )
        {
        CAknPointerEventModifier* modifier = iAvkonAppUiBase->PointerEventModifier();
        
        if ( modifier )
            {
            modifier->Pop( *this );
            }
        }
        
    AknsUtils::DeregisterControlPosition( this );
    }

EXPORT_C void CAknDoubleSpanScrollBar::ConstructL(TBool aWindowOwning, MEikScrollBarObserver* aScrollBarObserver,const CCoeControl* aParent,
                                                 TOrientation aOrientation,TInt /*aLength*/,TInt aScrollBarFlags )
    {
    iExtension = new(ELeave) CAknDoubleSpanScrollBarExtension(this);
    CAknDoubleSpanScrollBarExtension* extension = static_cast<CAknDoubleSpanScrollBarExtension*> (iExtension);

    extension->iScrollBarFlags = aScrollBarFlags;
    extension->iExtensionType = ENormalExpandedTouchArea;

    if ( AknLayoutUtils::PenEnabled() )
        {
        extension->SetScrollBarObserver(aScrollBarObserver); // sets also the owning observer

        extension->iPopupController = CAknInfoPopupNoteController::NewL();
        extension->iPopupController->SetTooltipModeL( ETrue );
        extension->iPopupController->SetTimeDelayBeforeShow( 1 );
        extension->iShowPopup = EFalse;
        }

    if (aWindowOwning)
        {
        CreateWindowL(aParent);
        if ( CAknEnv::Static()->TransparencyEnabled() )
            {
            Window().SetRequiredDisplayMode( EColor16MA );
            if ( Window().SetTransparencyAlphaChannel() == KErrNone )
                {
                Window().SetBackgroundColor( ~0 );
                }
            }
        }
    else if(aParent)
        {
        SetContainerWindowL(*aParent);
        }
    else
        {
        User::Leave(KErrArgument);
        }

    if( aParent )
        SetObserver(aParent->Observer());
    else
        SetObserver(NULL);

    iOrientation=aOrientation;
    CreateRequiredComponentsL();

    if (aWindowOwning)
        {
        Window().SetPointerGrab(ETrue);
        EnableDragEvents();
        if (extension->iScrollIndicator)
               extension->iScrollIndicator->SetAsWindowOwning(ETrue);


        // By default set background to transparent
        SetTransparentBackground(ETrue);
        }

    SetComponentsToInheritVisibility(ETrue);
    MakeVisible(EFalse);
    ActivateL();
    }


EXPORT_C void CAknDoubleSpanScrollBar::ConstructL(MEikScrollBarObserver* aScrollBarObserver,const CCoeControl* aParent,
                                                 TOrientation aOrientation,TInt aLength,TInt aScrollBarFlags)
// Second-phase construction, overides method from CEikScrollBar
    {
    ConstructL(ETrue, aScrollBarObserver, aParent, aOrientation, aLength, aScrollBarFlags);
    }


// ----------------------------------------------------------------------------
// CAknDoubleSpanScrollBar::CreateButtonL
//
// Creates buttons for double span scrollbar when __PEN_SUPPORT is enabled
// ----------------------------------------------------------------------------
//
void CAknDoubleSpanScrollBar::CreateButtonL(CAknScrollButton*& aButton, CAknScrollButton::TType aType)
// Create the appropriate button
    {
    if( !AknLayoutUtils::PenEnabled() )
        {
        // No buttons exist in this type of scrollbar
        return;
        }

    if (aButton)
        {
        return;
        }
    CAknScrollButton* button = CAknScrollButton::NewL(aType, CAknScrollButton::ENormal);
    CleanupStack::PushL(button);
    if ( OwnsWindow() && AknLayoutUtils::PenEnabled() )
        {
        button->CreateWindowOnlyForArrowsL( this );
        }
    button->SetContainerWindowL( *this );

    CleanupStack::Pop(); // button
    aButton = button;
    }


// ----------------------------------------------------------------------------
// CAknDoubleSpanScrollBar::SetButtonPositionL
//
// Sets button position when AknLayoutUtils::PenEnabled() returns ETrue
// This function is called from CAknDoubleSpanScrollBar::SizeChanged() function
// The button rectangle should be set in this function according to LAF spec
// ----------------------------------------------------------------------------
//
void CAknDoubleSpanScrollBar::SetButtonPositionL(CAknScrollButton* aButton)
    {
    if( !AknLayoutUtils::PenEnabled() )
        {
        // No buttons exist in this type of scrollbar
        return;
        }

    if ( aButton )
        {
        if( iExtension )
            {
            TAknWindowComponentLayout buttonLayout;
            TAknLayoutRect buttonRect;

            switch(aButton->Type())
                {
                case CAknScrollButton::ENudgeUp:
                    buttonLayout = AknLayoutScalable_Avkon::scroll_sc2_up_pane( 1 );
                    buttonRect.LayoutRect( Rect(), buttonLayout.LayoutLine() );
                    aButton->SetRect( buttonRect.Rect() );
                    break;
                case CAknScrollButton::ENudgeDown:
                    buttonLayout = AknLayoutScalable_Avkon::scroll_sc2_down_pane( 1 );
                    buttonRect.LayoutRect( Rect(), buttonLayout.LayoutLine() );
                    aButton->SetRect( buttonRect.Rect() );
                    break;
                case CAknScrollButton::ENudgeLeft:
                    buttonLayout = AknLayoutScalable_Avkon::scroll_sc2_left_pane();
                    buttonRect.LayoutRect( Rect(), buttonLayout.LayoutLine() );
                    aButton->SetRect( buttonRect.Rect() );
                    break;
                case CAknScrollButton::ENudgeRight:
                    buttonLayout = AknLayoutScalable_Avkon::scroll_sc2_right_pane();
                    buttonRect.LayoutRect( Rect(), buttonLayout.LayoutLine() );
                    aButton->SetRect( buttonRect.Rect() );
                    break;
                default:
                    break;
                }
            }
        }
    }


EXPORT_C void CAknDoubleSpanScrollBar::MakeVisible(TBool aVisible)
    {
    CAknPointerEventModifier* modifier = iAvkonAppUiBase ? iAvkonAppUiBase->PointerEventModifier() : NULL;
    
    if ( modifier )
        {
        CAknDoubleSpanScrollBarExtension* extension = static_cast<CAknDoubleSpanScrollBarExtension*> (iExtension);
        if ( aVisible  && (extension->iScrollIndicator->ScrollSpan() > 0) )
            {
            modifier->Push( *this, ExtensionArea() );
            }
        else
            {
            modifier->Pop( *this );
            }
        }

    CCoeControl::MakeVisible(aVisible);
    }

EXPORT_C TInt CAknDoubleSpanScrollBar::CountComponentControls() const
    {
    TInt controlCount = 0;
    if (iExtension)
        {
        CAknDoubleSpanScrollBarExtension* extension = static_cast<CAknDoubleSpanScrollBarExtension*> (iExtension);
        if (extension->iScrollIndicator)
            {
            controlCount = 1;
            }
        }
    if(AknLayoutUtils::PenEnabled())
        {
        if(iButtons.iIncreaseNudge)
            {
            controlCount++;
            }
        if(iButtons.iDecreaseNudge)
            {
            controlCount++;
            }
        }

    return controlCount;
    }

EXPORT_C CCoeControl* CAknDoubleSpanScrollBar::ComponentControl(TInt aIndex) const
    {
    CCoeControl* control = NULL;
    if (aIndex==0 && iExtension)
        {
        CAknDoubleSpanScrollBarExtension* extension = static_cast<CAknDoubleSpanScrollBarExtension*> (iExtension);
        control = extension->iScrollIndicator;
        }
    if(AknLayoutUtils::PenEnabled())
        {
        if(aIndex == 1)
            {
            control = iButtons.iIncreaseNudge;
            }
        else if(aIndex == 2)
            {
            control = iButtons.iDecreaseNudge;
            }
        }

    return control;
    }


EXPORT_C void CAknDoubleSpanScrollBar::SizeChanged()
    {
    CAknPointerEventModifier* modifier = iAvkonAppUiBase ? iAvkonAppUiBase->PointerEventModifier() : NULL;
    
    if ( modifier && IsVisible() )
        {
        modifier->Update( *this, ExtensionArea() );
        }

    AknsUtils::RegisterControlPosition( this );
    if (iExtension)
        {
        CAknDoubleSpanScrollBarExtension* extension = static_cast<CAknDoubleSpanScrollBarExtension*> (iExtension);
        CAknDoubleSpanScrollIndicator* indicator = extension->iScrollIndicator;
        // set indicator size to same as the whole scrollbar.
        if (indicator)
           {
            TAknWindowComponentLayout combinedRect;

            TInt variety = 0;
            TInt scVariety = 0;
            // No pen check as the layout for the non-pen is not taken from layout data
            // if in future made so, this must be changed to support also non-pen situations
            if( AknLayoutUtils::PenEnabled() )
                {
                if ( iOrientation == EHorizontal)
                    {
                    variety = 2;
                    scVariety = 1;
                    }
                else
                    {
                    variety = 1;
                    }
                }


            combinedRect = TAknWindowComponentLayout::Compose( AknLayoutScalable_Avkon::scroll_pane( scVariety ),
                                                               AknLayoutScalable_Avkon::bg_scroll_pane( variety ) );
            TAknLayoutRect indicatorRect;

            if (OwnsWindow())
                {
                if( AknLayoutUtils::PenEnabled() &&
                    ( extension->iScrollBarFlags & EEnableNudgeButtons ) )
                    {
                    // when the pen support is enabled, the space for arrows must be reserved.
                    indicatorRect.LayoutRect( Rect(), combinedRect.LayoutLine() );
                    indicator->SetRect( indicatorRect.Rect() );
                    }
                else
                    {
                    indicator->SetExtent(TPoint(0,0),Size());
                    }

                if (indicator->TransparentBackground())
                    {
                    // This will refresh the transparency masks
                    SetTransparentBackground(ETrue);
                    }
                }
            else
                {
                if( AknLayoutUtils::PenEnabled() &&
                    ( extension->iScrollBarFlags & EEnableNudgeButtons ) )
                    {
                    // when the pen support is enabled, the space for arrows must be reserved.
                    TRect rect( Position(), Size() );
                    indicatorRect.LayoutRect( rect, combinedRect.LayoutLine() );
                    indicator->SetRect( indicatorRect.Rect() );
                    }
                else
                    {
                    indicator->SetExtent(Position(),Size());
                    }
                }
            }

        if(AknLayoutUtils::PenEnabled())
            {
            if ( !iButtons.iIncreaseNudge || !iButtons.iDecreaseNudge )
                {
                TRAP_IGNORE( CreateRequiredComponentsL() );
                }
            // Set scroll button positions
            TRAP_IGNORE( SetButtonPositionL( iButtons.iIncreaseNudge ) );
            TRAP_IGNORE( SetButtonPositionL( iButtons.iDecreaseNudge ) );
            }
        }
    }


// ----------------------------------------------------------------------------
// CAknDoubleSpanScrollBar::HandlePointerEventL
//
// Handles pointer events.
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknDoubleSpanScrollBar::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    if( !AknLayoutUtils::PenEnabled() || !iExtension)
        {
        return;
        }

    if ( aPointerEvent.iType == TPointerEvent::EButton1Down && GrabbingComponent() != this && OwnsWindow() )
        {
        ClaimPointerGrab( EFalse );
        }

    CAknDoubleSpanScrollBarExtension* extension =
        static_cast<CAknDoubleSpanScrollBarExtension*> (iExtension);
    CAknDoubleSpanScrollIndicator* indicator = extension->iScrollIndicator;

    RDrawableWindow* pointerWindow = &Window();
    TRect rect(indicator->Rect());

    // scale the pointer event position relative to indicator rect
    // this has effect only if the scroll bar is not window owning
    TPoint eventPos(aPointerEvent.iPosition - rect.iTl);

    // use x or y values depending on orientation
    TInt position(eventPos.iY);
    TInt scrollSpanPix(rect.Height());
    if(iOrientation == EHorizontal)
        {
        position = eventPos.iX;
        scrollSpanPix = rect.Width();
        }

    // get current values from the indicator
    TInt scrollSpan(indicator->ScrollSpan());
    TInt thumbSpan(indicator->WindowSize());
    TInt thumbPosition(indicator->FocusPosition());
    TInt thumbSpanPix     = indicator->GetCurrentThumbSpanInPixels();
    TInt thumbPositionPix = indicator->GetCurrentThumbPositionInPixels();
    // clear the pointer down info on pen up and hide info popup
    TInt lastPointerDownOn = extension->iPointerDownOn;
    // The real span area available (as pixels)
    scrollSpanPix -= thumbSpanPix;

            
         // touch release on thumb
         TBool thumbPressed = 
                 ( position < (thumbPositionPix + thumbSpanPix) 
                         && position > thumbPositionPix );
         if ( thumbPressed &&
              aPointerEvent.iType == TPointerEvent::EButton1Up &&
              thumbSpan < scrollSpan )
             {
             MTouchFeedback* feedback = MTouchFeedback::Instance();

             CCoeControl* parent = Parent();
             TBool feedbackEnabled = !IsDimmed() && IsVisible();
             if (parent && feedbackEnabled)
                 {
                 // check the same for the parent
                 feedbackEnabled = !parent->IsDimmed() && parent->IsVisible();
                 }
             if ( feedback && feedbackEnabled )
                 {
                 feedback->InstantFeedback( this, 
                                            ETouchFeedbackBasicSlider, 
                                            ETouchFeedbackVibra, 
                                            aPointerEvent );
                 }
             }
     
    // check that scroll bar is useful
    if (thumbSpan < scrollSpan)
        {
        // check where the pointer down occured
        if(aPointerEvent.iType == TPointerEvent::EButton1Down )
            {
            indicator->SetBackgroudHighlight( ETrue );

            extension->iPointerDownPosition  = position;
            
            if(iButtons.iIncreaseNudge &&
               iButtons.iIncreaseNudge->Rect().Contains(aPointerEvent.iPosition))
                {
                extension->iPointerDownOn = CEikScrollBar::EIncreaseNudgeButton;
                }
            else if(iButtons.iDecreaseNudge &&
                    iButtons.iDecreaseNudge->Rect().Contains(aPointerEvent.iPosition))
                {
                extension->iPointerDownOn = CEikScrollBar::EDecreaseNudgeButton;
                }
            else if (position < thumbPositionPix)
                {
                extension->iPointerDownOn = CEikScrollBar::EDecreaseShaft;
                }
            else if (position < (thumbPositionPix + thumbSpanPix))
                {
                extension->iDragged = EFalse;
                extension->iPointerDownOn = CEikScrollBar::EThumb;
                extension->iPointerOffsetFromThumb = position - thumbPositionPix;

                indicator->SetHandleHighlight( ETrue );
                indicator->DrawDeferred();
                }
            else
                {
                extension->iPointerDownOn = CEikScrollBar::EIncreaseShaft;
                }
            }

        if (aPointerEvent.iType == TPointerEvent::EButton1Up)
            {
            extension->iPointerDownOn = CEikScrollBar::ENone;

            // Highlight off always when the pointer is lifted
            indicator->SetHandleHighlight( EFalse );
            indicator->DrawDeferred();
            indicator->SetBackgroudHighlight( EFalse );

            if ( extension->iPopupController )
                {
                extension->iPopupController->HideInfoPopupNote();
                    extension->iShowPopup = EFalse;
                }
            }

        // respond to the pointer event
        switch(extension->iPointerDownOn)
            {
            case CEikScrollBar::EDecreaseShaft:
            case CEikScrollBar::EIncreaseShaft:
                {
                TEikScrollEvent event = EEikScrollPageUp;
                if(aPointerEvent.iType == TPointerEvent::EButton1Down ||
                   aPointerEvent.iType == TPointerEvent::EButtonRepeat)
                    {
                    if(extension->iPointerDownOn == CEikScrollBar::EDecreaseShaft)
                        {
                        event = iOrientation==EHorizontal ? EEikScrollPageLeft : EEikScrollPageUp;
                        thumbPosition -= thumbSpan;
                        thumbPosition = Max(0, thumbPosition);


                        TInt prevPosValue = extension->ThumbPosition();
                        
                        // This will update the thumb's pixel extent, used
                        // below
                        extension->SetModelThumbPosition(thumbPosition);
                        indicator->SetIndicatorValues(scrollSpan, thumbPosition, thumbSpan, 0, 0);

                        TInt afterPosValue = extension->ThumbPosition();
                        if (prevPosValue != afterPosValue)
                            {
                            MTouchFeedback* feedback = MTouchFeedback::Instance();

                            CCoeControl* parent = Parent();
                            TBool feedbackEnabled = !IsDimmed() && IsVisible();
                            if (parent && feedbackEnabled)
                                {
                                // check the same for the parent
                                feedbackEnabled = !parent->IsDimmed() && parent->IsVisible();
                                }
                            if ( feedback && feedbackEnabled )
                                {
                                feedback->InstantFeedback( this, ETouchFeedbackBasicSlider, aPointerEvent );
                                }
                            }

                        // request pointer repeat until the thumb reaches the pen down position
                        TInt newThumbPosPix = indicator->GetCurrentThumbPositionInPixels();
                        if(position < newThumbPosPix)
                            {
                            TRect ignoreRect(rect);
                            TRect rt = ExtensionArea();
                            if(iOrientation == EVertical)
                                {
                                ignoreRect.iTl = TPoint(rt.iTl.iX, rect.iTl.iY);
                                ignoreRect.iBr = TPoint(ignoreRect.iBr.iX, newThumbPosPix + rect.iTl.iY);
                                }
                            else
                                {
                                ignoreRect.iTl = TPoint(rect.iTl.iX, rt.iTl.iY);
                                ignoreRect.iBr = TPoint(newThumbPosPix, rt.iBr.iY);
                                }
                            // repeat until thumb reaches the stylus down position
                            pointerWindow->RequestPointerRepeatEvent(KScrollRepeatTimeout, ignoreRect);
                            }
                        

                        }
                    else
                        {
                        event = iOrientation==EHorizontal ? EEikScrollPageRight : EEikScrollPageDown;
                        thumbPosition += thumbSpan;
                        thumbPosition = Min((scrollSpan - thumbSpan), thumbPosition);

                        TInt prevPosValue = extension->ThumbPosition();
                        extension->SetModelThumbPosition(thumbPosition);
                        indicator->SetIndicatorValues(scrollSpan, thumbPosition, thumbSpan, 0, 0);

                        TInt afterPosValue = extension->ThumbPosition();
                        if (prevPosValue != afterPosValue)
                            {
                            MTouchFeedback* feedback = MTouchFeedback::Instance();

                            CCoeControl* parent = Parent();
                            TBool feedbackEnabled = !IsDimmed() && IsVisible();
                            if (parent && feedbackEnabled)
                                {
                                // check the same for the parent
                                feedbackEnabled = !parent->IsDimmed() && parent->IsVisible();
                                }
                            if ( feedback && feedbackEnabled )
                                {
                                feedback->InstantFeedback( this, ETouchFeedbackBasicSlider, aPointerEvent );
                                }
                            }

                        // request pointer repeat until the thumb reaches the pen down position
                        TInt newThumbPosPix = indicator->GetCurrentThumbPositionInPixels();
                        newThumbPosPix += thumbSpanPix;

                        if(position > newThumbPosPix )
                            {
                            TRect ignoreRect(rect);
                            TRect rt = ExtensionArea();
                            if(iOrientation == EVertical)
                                {
                                ignoreRect.iTl = TPoint(rt.iTl.iX, newThumbPosPix + rect.iTl.iY);
                                }
                            else
                                {
                                ignoreRect.iTl = TPoint(newThumbPosPix, rt.iTl.iY);
                                }
                            // repeat until thumb reaches the stylus down position
                            pointerWindow->RequestPointerRepeatEvent(KScrollRepeatTimeout, ignoreRect);

                            }
                        
                        }

                    if(indicator->DrawBackgroundState())
                        indicator->DrawNow();
                    else
                        indicator->DrawDeferred();

                    if(extension->ScrollBarObserver())
                        {
                        extension->ScrollBarObserver()->HandleScrollEventL(this, event);
                        }
                    }

                }
                break;

            case CEikScrollBar::EThumb:
                if( aPointerEvent.iType == TPointerEvent::EButton1Down )
                    {
                    MTouchFeedback* feedback = MTouchFeedback::Instance();

                    if ( feedback )
                        {
                        TTouchFeedbackType fbType = TTouchFeedbackType( 
                                                        ETouchFeedbackAudio |
                                                        ETouchFeedbackVibra );
                          
                        feedback->InstantFeedback( this, ETouchFeedbackBasicSlider, fbType, aPointerEvent );
                        }
                    }

                if( aPointerEvent.iType == TPointerEvent::EDrag 
                   || aPointerEvent.iType == TPointerEvent::EButtonRepeat )
                    {
                    // performace improving. Too many drag event received, handling every single event 
                    // will use too much CPU time.
                    TTime now;
                    now.HomeTime();                    
                    if ( extension->iDragged &&
                         now.MicroSecondsFrom( extension->iLastDrag ) 
                         < KScrollDragTimeout )
                        {                        
                        break; // ignore drag for this time
                        }
                    extension->iDragged = ETrue; // after this time, iLastDragged has value.
                    extension->iLastDrag = now;
                    
                    thumbPositionPix = position - extension->iPointerOffsetFromThumb;
                    TInt oldPosition = thumbPosition;
                    TReal newPosition = thumbPositionPix * ( scrollSpan - thumbSpan ) / (TReal)scrollSpanPix;
                    thumbPosition = newPosition;

                    // round the value to the nearest possible position
                    if( TInt(newPosition * 2) >= ((thumbPosition * 2) + 1 ))
                        {
                        ++thumbPosition;
                        }

                    // enforce limits
                    thumbPosition = Max(0, thumbPosition);
                    thumbPosition = Min((scrollSpan - thumbSpan), thumbPosition);

                    if(thumbPosition != oldPosition)
                        {
                        // Smooth continuous tactile feedback is produced
                        // during thumb dragging. The tactile feedback API 
                        // filters out possible re-startings of the effect.
                        MTouchFeedback* feedback = MTouchFeedback::Instance();

                        if ( feedback )
                            {
                            TTimeIntervalMicroSeconds32 timeout( 300000 );
                            feedback->StartFeedback( this, 
                                                     ETouchContinuousSlider, 
                                                     &aPointerEvent, 
                                                     KIntensity, // intensity 100%
                                                     timeout );
                            }
                        extension->SetModelThumbPosition(thumbPosition);
                        indicator->SetIndicatorValues(scrollSpan, thumbPosition, thumbSpan, 0, 0);

                        if(indicator->DrawBackgroundState())
                            indicator->DrawNow();
                        else
                            indicator->DrawDeferred();

                        if(extension->ScrollBarObserver())
                            {
                            extension->ScrollBarObserver()->HandleScrollEventL(
                                this,
                                iOrientation==EHorizontal ? EEikScrollThumbDragHoriz : EEikScrollThumbDragVert);
                            }
                        }
                    // Show popup info
                    if ( extension->iShowPopup && extension->iPopupController )
                        {
                        TPoint infoPoint = PositionRelativeToScreen();

                        if ( iOrientation == EVertical )
                            {
                            if ( AknLayoutUtils::LayoutMirrored() )
                                {
                                infoPoint.iX += Rect().Width();
                                infoPoint.iY += aPointerEvent.iPosition.iY;
                                extension->iPopupController->SetPositionAndAlignment (
                                    infoPoint, EHLeftVCenter );
                                }
                            else
                                {
                                infoPoint.iY += aPointerEvent.iPosition.iY;
                                extension->iPopupController->SetPositionAndAlignment (
                                    infoPoint, EHRightVCenter );
                                }
                            }
                        else if ( iOrientation == EHorizontal )
                            {
                            infoPoint.iX += aPointerEvent.iPosition.iX;
                            extension->iPopupController->SetPositionAndAlignment(
                                infoPoint, EHCenterVBottom );
                            }
                        extension->iPopupController->ShowInfoPopupNote();
                        extension->iShowPopup = EFalse;
                        }
                    }
                break;

            case CEikScrollBar::ENone:
                {
                // Stop the continuous tactile feedback that may be playing
                // at the time due to possible previous thumb dragging.
                MTouchFeedback* feedback = MTouchFeedback::Instance();

                if ( feedback )
                    {
                    feedback->StopFeedback( this );
                    }
                }

                if(lastPointerDownOn == CEikScrollBar::EThumb)
                    {
                    if(extension->ScrollBarObserver())
                        {
                        extension->ScrollBarObserver()->HandleScrollEventL(
                            this,
                            iOrientation==EHorizontal ? EEikScrollThumbReleaseHoriz : EEikScrollThumbReleaseVert);
                        }

                    }
                break;

            case CEikScrollBar::EIncreaseNudgeButton:
                // handle increase scroll button press (right or down button)
                if(aPointerEvent.iType == TPointerEvent::EButton1Down ||
                   aPointerEvent.iType == TPointerEvent::EButtonRepeat)
                    {
                    TInt oldPosition = thumbPosition;
                    thumbPosition++;
                    thumbPosition = Min((scrollSpan - thumbSpan), thumbPosition);

                    if(oldPosition != thumbPosition)
                        {
                        // Note: Depending on layout and style the nudge
                        //       button may be obsolete.
                        // Sensitive feedback given for each "nudge"
                        MTouchFeedback* feedback = MTouchFeedback::Instance();
                        if ( feedback )
                            {
                            feedback->InstantFeedback ( this, ETouchFeedbackBasicSlider, aPointerEvent );
                            }
                        extension->SetModelThumbPosition(thumbPosition);
                        indicator->SetIndicatorValues(scrollSpan, thumbPosition, thumbSpan, 0, 0);
                        if(indicator->DrawBackgroundState())
                            indicator->DrawNow();
                        else
                            indicator->DrawDeferred();
                        }

                    // even if the thumb position did not change (thumb has reached its last
                    // possible position), we must send the event
                    // to the observer, so that it can implement the looping scrolling if necessary
                    if(extension->ScrollBarObserver())
                        {
                        extension->ScrollBarObserver()->HandleScrollEventL(
                            this,
                            iOrientation==EHorizontal ? EEikScrollRight : EEikScrollDown);
                        }
                    // repeat untill stylus is lifted or dragged outside the button
                    TRect nudgeRect( iButtons.iIncreaseNudge->Rect() );

                    pointerWindow->RequestPointerRepeatEvent(KScrollRepeatTimeout, nudgeRect );
                    }

                break;

            case CEikScrollBar::EDecreaseNudgeButton:
                // handle decrease scroll button press (left or up button)
                if(aPointerEvent.iType == TPointerEvent::EButton1Down ||
                   aPointerEvent.iType == TPointerEvent::EButtonRepeat)
                    {
                    TInt oldPosition = thumbPosition;
                    thumbPosition--;
                    thumbPosition = Max(0, thumbPosition);
                    if(oldPosition != thumbPosition)
                        {
                        // Note: Depending on layout and style the nudge
                        //       button may be obsolete.
                        // Sensitive feedback given for each "nudge"
                        MTouchFeedback* feedback = MTouchFeedback::Instance();
                        if ( feedback )
                            {
                            feedback->InstantFeedback ( this, ETouchFeedbackBasicSlider, aPointerEvent );
                            }
                        extension->SetModelThumbPosition(thumbPosition);
                        indicator->SetIndicatorValues(scrollSpan, thumbPosition, thumbSpan, 0, 0);
                        if(indicator->DrawBackgroundState())
                            indicator->DrawNow();
                        else
                            indicator->DrawDeferred();
                        }

                    // even if the thumb position did not change (thumb has reached its first
                    // possible position), we must send the event
                    // to the observer, so that it can implement the looping scrolling if necessary
                    if(extension->ScrollBarObserver())
                        {
                        extension->ScrollBarObserver()->HandleScrollEventL(
                            this,
                            iOrientation==EHorizontal ? EEikScrollLeft : EEikScrollUp);
                        }
                    // repeat untill stylus is lifted or dragged outside the button
                    TRect nudgeRect( iButtons.iDecreaseNudge->Rect() );

                    pointerWindow->RequestPointerRepeatEvent(KScrollRepeatTimeout, nudgeRect );
                    }

                break;

            default:
                break;

            } // end: of switch

        } // end of: if (thumbSpan < scrollSpan)
    }

EXPORT_C void* CAknDoubleSpanScrollBar::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CAknDoubleSpanScrollBar::SetFixedLayoutRect(TRect aScrollBarRect)
    {
    if (iExtension)
        {
        CAknDoubleSpanScrollBarExtension* extension = static_cast<CAknDoubleSpanScrollBarExtension*> (iExtension);
        extension->iFixedLayoutRect = aScrollBarRect;
        SetRect(aScrollBarRect);
        }
    }

EXPORT_C void CAknDoubleSpanScrollBar::SetScrollPopupInfoTextL( const TDesC& aText )
    {
    if ( !AknLayoutUtils::PenEnabled() )
        {
        return;
        }

    if ( iExtension )
        {
        CAknDoubleSpanScrollBarExtension* extension = static_cast<CAknDoubleSpanScrollBarExtension*> (iExtension);

        if ( extension->iPopupController )
            {
            if ( aText.Length() > 0 )
                {
                extension->iPopupController->SetTextL( aText );
                extension->iShowPopup = ETrue;
                }
            else
                {
                extension->iPopupController->HideInfoPopupNote();
                extension->iShowPopup = EFalse;
                }
            }
        }
    }

TRect CAknDoubleSpanScrollBar::FixedLayoutRect()
    {
    TRect fixedLayoutRect;
    if (iExtension)
        {
        CAknDoubleSpanScrollBarExtension* extension = static_cast<CAknDoubleSpanScrollBarExtension*> (iExtension);
        fixedLayoutRect = extension->iFixedLayoutRect;
        }
    return fixedLayoutRect;
    }

void CAknDoubleSpanScrollBar::SetTransparentBackground(TBool aTransparentBackground)
    {
    // In transparency-enabled builds, consider making this function
    // act as if DrawBackground( EFalse ) was called..

    TBool transparencyIsSupported = EFalse; // Transparent windows are not supported for now

    if (iExtension && OwnsWindow() && transparencyIsSupported)
        {
        CAknDoubleSpanScrollBarExtension* extension = static_cast<CAknDoubleSpanScrollBarExtension*> (iExtension);
        CAknDoubleSpanScrollIndicator* indicator = extension->iScrollIndicator;

        if (aTransparentBackground)
            {
            // removed old transparency related code
            }
        else
            {
            Window().SetNonTransparent();
            }

        indicator->SetTransparentBackground(aTransparentBackground);

        }

    }

TBool CAknDoubleSpanScrollBar::DrawBackgroundState()
    {
    CAknDoubleSpanScrollBarExtension* extension = static_cast<CAknDoubleSpanScrollBarExtension*> (iExtension);
    CAknDoubleSpanScrollIndicator* indicator = extension->iScrollIndicator;

    return indicator->DrawBackgroundState();
    }

void CAknDoubleSpanScrollBar::DrawBackground(TBool aDraw)
    {
    CAknDoubleSpanScrollBarExtension* extension = static_cast<CAknDoubleSpanScrollBarExtension*> (iExtension);
    CAknDoubleSpanScrollIndicator* indicator = extension->iScrollIndicator;

    indicator->SetDrawBackgroundState(aDraw);
    }


// ---------------------------------------------------------------------------
// CAknDoubleSpanScrollBar::ResetPressedDownHighlight
// ---------------------------------------------------------------------------
//
void CAknDoubleSpanScrollBar::ResetPressedDownHighlight()
    {
    CAknDoubleSpanScrollBarExtension* extension =
        static_cast<CAknDoubleSpanScrollBarExtension*>( iExtension );
        
    CAknDoubleSpanScrollIndicator* indicator = extension->iScrollIndicator;
    
    indicator->SetHandleHighlight( EFalse );
    }


//
// class CAknDoubleSpanScrollBarExtension
//

CAknDoubleSpanScrollBarExtension::CAknDoubleSpanScrollBarExtension(CEikScrollBar* aParent)
: iExternalFrames(1), iActiveScheduledDraw(NULL)
    {
    iParent=aParent;
    }

CAknDoubleSpanScrollBarExtension::~CAknDoubleSpanScrollBarExtension()
    {
    delete iScrollIndicator;
    iScrollIndicator = NULL;

    if ( iPopupController )
        {
        delete iPopupController;
        iPopupController = NULL;
        }

    if(iActiveScheduledDraw && iActiveScheduledDraw->IsActive())
        iActiveScheduledDraw->Cancel();

    delete iActiveScheduledDraw;
    }


void CAknDoubleSpanScrollBarExtension::SetLengthL(TInt /*aLength*/)
    {
    }

void CAknDoubleSpanScrollBarExtension::SetModelL(const TEikScrollBarModel* /*aModel*/)
    {
    }

void CAknDoubleSpanScrollBarExtension::SetModel(const TEikScrollBarModel* /*aModel*/)
    {
    }

void CAknDoubleSpanScrollBarExtension::SetLengthAndModelL(TInt /*aLength*/,const TEikScrollBarModel* /*aModel*/)
    {
    }

// ----------------------------------------------------------------------------
// CAknDoubleSpanScrollBarExtension::SetModelThumbPosition
// Sets the thumb position to the model. This function has to be used because
// CAknDoubleSpanScrollBar does not have direct access to the model.
// ----------------------------------------------------------------------------
//
void CAknDoubleSpanScrollBarExtension::SetModelThumbPosition(TInt aThumbPos)
    {
    if( !AknLayoutUtils::PenEnabled() )
        {
        return;
        }

    if (iParent->iModel.ScrollBarModelType() == TEikScrollBarModel::EAknDoubleSpanScrollBarModel)
        {
        static_cast <TAknDoubleSpanScrollBarModel*> (&iParent->iModel)->SetFocusPosition(aThumbPos);
        }
    else
        {
        // Incorrect model is used, but in most cases we can work with the TEikScrollBarModel model.
        iParent->iModel.iThumbPosition = aThumbPos;
        }
    }

void CAknDoubleSpanScrollBarExtension::SetFocusPosToThumbPos(TInt /*aFocusPosition*/)
    {
    }

TInt CAknDoubleSpanScrollBarExtension::ThumbPosition() const
    {
    if (iParent->iModel.ScrollBarModelType() == TEikScrollBarModel::EAknDoubleSpanScrollBarModel)
        {
        if( AknLayoutUtils::PenEnabled() )
            {
            // it is more effective to cast the pointer and use it directly
            // than creating a copy of the model just to return a value
            return static_cast <TAknDoubleSpanScrollBarModel*> (&iParent->iModel)->FocusPosition();
            }
        else
            {
            TAknDoubleSpanScrollBarModel& model = static_cast <TAknDoubleSpanScrollBarModel&> (iParent->iModel);
            return model.FocusPosition();
            }
        }
    else
        {
            // Error. User of the API is perhaps assigning values directly to TEikScrollBarModel
            // member variables which is not allowed with EAknDoubleSpanScrollBarModel.
            // #ifdef _DEBUG
            // RDebug::Print(_L("CAknDoubleSpanScrollBarExtension: Please, use TAknDoubleSpanScrollBarModel instead of TEikScrollBarModel"));
            // #endif
            // In most cases we can work with the TEikScrollBarModel model.
            return iParent->iModel.iThumbPosition;
        }
    }

TInt CAknDoubleSpanScrollBarExtension::ScrollBarBreadth() const
    {
    if (iScrollIndicator)
        return iScrollIndicator->IndicatorWidth();
    else
        return KAknDoubleSpanScrollBarWidth;
    }

void CAknDoubleSpanScrollBarExtension::SetDecreaseButtonsDimmed(TBool /*aDimmed*/)
    {
    }

void CAknDoubleSpanScrollBarExtension::SetIncreaseButtonsDimmed(TBool /*aDimmed*/)
    {
    }

void CAknDoubleSpanScrollBarExtension::SetAllButtonsDimmed(TBool /*aDimmed*/)
    {
    }

void CAknDoubleSpanScrollBarExtension::SetContainingCba(CEikCba* /*aCba*/)
    {
    // Not needed in this type of scrollbar
    }

TInt CAknDoubleSpanScrollBarExtension::ScrollBarType()
    {
    return CEikScrollBarFrame::EDoubleSpan;
    }

void CAknDoubleSpanScrollBarExtension::CreateButtonL(CAknScrollButton*& /*aButton*/,CAknScrollButton::TType /*aType*/)
    {
    }

void CAknDoubleSpanScrollBarExtension::DoSetModel(const TEikScrollBarModel* aModel)
    {
    iParent->iModel=(*aModel);
    if (iScrollIndicator)
        {
        if (aModel->ScrollBarModelType() == TEikScrollBarModel::EAknDoubleSpanScrollBarModel)
            {
            const TAknDoubleSpanScrollBarModel* model = static_cast <const TAknDoubleSpanScrollBarModel*> (aModel);

            iScrollIndicator->SetIndicatorValues(model->ScrollSpan(),
                model->FocusPosition(),
                model->WindowSize(),
                model->FieldPosition(),
                model->FieldSize());
            }
        else
            {
            // Error. User of the API is perhaps assigning values directly to TEikScrollBarModel
            // member variables which is not allowed with TAknDoubleSpanScrollBarModel.
            // #ifdef _DEBUG
            // RDebug::Print(_L("CAknDoubleSpanScrollBarExtension: Please, use TAknDoubleSpanScrollBarModel instead of TEikScrollBarModel"));
            // #endif
            // In most cases we can work with the TEikScrollBarModel model.
            iScrollIndicator->SetIndicatorValues(aModel->iScrollSpan,
                aModel->iThumbPosition,
                aModel->iThumbSpan,
                0,
                0);
            }

        if (iParent->OwnsWindow() && iScrollIndicator->TransparentBackground())
            {
            iParent->Window().HandleTransparencyUpdate();
            }
        if(iScrollIndicator->IsVisible())
            {
            if(iScrollIndicator->DrawBackgroundState() && !iParent->OwnsWindow())
                {
                if(HasModelChanged(aModel))
                    {
                    TInt err = KErrNone;
                    if(!iActiveScheduledDraw) // create if not initialized
                        TRAP(err, iActiveScheduledDraw = CIdle::NewL(EPriorityHigh));
                    if(!err && !iActiveScheduledDraw->IsActive())
                        iActiveScheduledDraw->Start(TCallBack(ScheduledDraw,this));
                    }
                }
            else
                {
                iParent->DrawDeferred();                 
                }

            }
        }
    }

TBool CAknDoubleSpanScrollBarExtension::HasModelChanged(const TEikScrollBarModel* aModel)
    {
    if(iPreviousModel.ScrollBarModelType() == TEikScrollBarModel::EAknDoubleSpanScrollBarModel &&
        aModel->ScrollBarModelType() == TEikScrollBarModel::EAknDoubleSpanScrollBarModel)
        {
        TAknDoubleSpanScrollBarModel* previousModel = static_cast<TAknDoubleSpanScrollBarModel*> (&iPreviousModel);
        const TAknDoubleSpanScrollBarModel* model = static_cast<const TAknDoubleSpanScrollBarModel*> (aModel);
        if(previousModel->ScrollSpan() != model->ScrollSpan() ||
        previousModel->FocusPosition() != model->FocusPosition() ||
        previousModel->WindowSize() != model->WindowSize() ||
        previousModel->FieldPosition() != model->FieldPosition() ||
        previousModel->FieldSize() != model->FieldSize())
            {
            iPreviousModel = *aModel;
            return ETrue;
            }
        }
    else if(iPreviousModel.ScrollBarModelType() == TEikScrollBarModel::EEikScrollBarModel &&
        aModel->ScrollBarModelType() == TEikScrollBarModel::EAknDoubleSpanScrollBarModel)
        {
        const TAknDoubleSpanScrollBarModel* model = static_cast<const TAknDoubleSpanScrollBarModel*> (aModel);
        if(iPreviousModel.iScrollSpan != model->ScrollSpan() ||
        iPreviousModel.iThumbPosition != model->FocusPosition() ||
        iPreviousModel.iThumbSpan != model->WindowSize())
            {
            iPreviousModel = *aModel;
            return ETrue;
            }
        }
    else if(iPreviousModel.ScrollBarModelType() == TEikScrollBarModel::EAknDoubleSpanScrollBarModel &&
        aModel->ScrollBarModelType() == TEikScrollBarModel::EEikScrollBarModel)
        {
        TAknDoubleSpanScrollBarModel* previousModel = static_cast<TAknDoubleSpanScrollBarModel*> (&iPreviousModel);
        if(previousModel->ScrollSpan() != aModel->iScrollSpan ||
        previousModel->FocusPosition() != aModel->iThumbPosition ||
        previousModel->WindowSize() != aModel->iThumbSpan)
            {
            iPreviousModel = *aModel;
            return ETrue;
            }
        }
    else
        {
        if(iPreviousModel.iScrollSpan != aModel->iScrollSpan ||
        iPreviousModel.iThumbPosition != aModel->iThumbPosition ||
        iPreviousModel.iThumbSpan != aModel->iThumbSpan)
            {
            iPreviousModel = *aModel;
            return ETrue;
            }
        }
    iPreviousModel = *aModel;
    return EFalse;
    }

CEikCba* CAknDoubleSpanScrollBarExtension::Cba() const
    {
    return NULL; // Not needed in this type of scrollbar
    }

void CAknDoubleSpanScrollBarExtension::AddExternalFrameL(CEikScrollBarFrame* aFrame)
    {
    iExternalFrames.AppendL(aFrame);
    iScrollBarObserver = aFrame->ScrollBarFrameObserver();
    }


void CAknDoubleSpanScrollBarExtension::RemoveExternalFrame(CEikScrollBarFrame* aFrame)
    {
    TInt count = iExternalFrames.Count();
    for (TInt ii=count-1; ii>=0; ii--)
        {
        if (iExternalFrames[ii] == aFrame)
            {
            iExternalFrames[ii]->DisconnectExternalScrollBar(iParent);
            iExternalFrames.Delete(ii);
            }
        }

    count = iExternalFrames.Count();
    if(count == 0) //no externally owned anymore
        {
        iScrollBarObserver = iOwningScrollBarObserver;
        }
    else // set the next external frame as observer
        {
        iScrollBarObserver = iExternalFrames[(count - 1)]->ScrollBarFrameObserver();
        }
    }

void CAknDoubleSpanScrollBarExtension::DisconnectExternalFrames()
    {
    TInt count = iExternalFrames.Count();
    for (TInt ii=count-1; ii>=0; ii--)
        {
        iExternalFrames[ii]->DisconnectExternalScrollBar(iParent);
        }
    iExternalFrames.Reset();
    }

void CAknDoubleSpanScrollBarExtension::CreateRequiredComponentsL()
    {
    if ( !iScrollIndicator )
        {
        iScrollIndicator = CAknDoubleSpanScrollIndicator::NewL( iParent->iOrientation );
        iScrollIndicator->SetContainerWindowL( *iParent );
        iScrollIndicator->SetRect( iParent->Rect() );
        iScrollIndicator->SetComponentsToInheritVisibility(ETrue);
        }

    if ( AknLayoutUtils::PenEnabled() &&
        ( iScrollBarFlags & CEikScrollBar::EEnableNudgeButtons ) )
        {
        TBool horiz=(iParent->iOrientation == CEikScrollBar::EHorizontal);

        if ( !iParent->iButtons.iDecreaseNudge )
            {
            iParent->CreateButtonL(iParent->iButtons.iDecreaseNudge,horiz ? CAknScrollButton::ENudgeLeft : CAknScrollButton::ENudgeUp);
            }

        if ( !iParent->iButtons.iIncreaseNudge )
            {
            iParent->CreateButtonL(iParent->iButtons.iIncreaseNudge,horiz ? CAknScrollButton::ENudgeRight : CAknScrollButton::ENudgeDown);
            }
        }
    }

void CAknDoubleSpanScrollBarExtension::DestroyButton(CAknScrollButton*& /*aButton*/)
    {
    }

void CAknDoubleSpanScrollBarExtension::SetButtonPositionL(CAknScrollButton* /*aButton*/)
    {
    }

void CAknDoubleSpanScrollBarExtension::SetScrollBarObserver(MEikScrollBarObserver* aScrollBarObserver)
    {
    iScrollBarObserver = aScrollBarObserver;

    if(iExternalFrames.Count() == 0)
        {
        iOwningScrollBarObserver = aScrollBarObserver;
        }
    }

MEikScrollBarObserver* CAknDoubleSpanScrollBarExtension::ScrollBarObserver()
    {
    return iScrollBarObserver;
    }

TInt CAknDoubleSpanScrollBarExtension::ScheduledDraw( TAny* aThis )
    {
    static_cast<CAknDoubleSpanScrollBarExtension*>( aThis )->DoScheduledDraw();
    return 0;
    }

void CAknDoubleSpanScrollBarExtension::DoScheduledDraw()
    {
    if(iParent)
        iParent->DrawNow();
    }


TInt CAknDoubleSpanScrollBarExtension::Reserved_1(){return 0;};
TInt CAknDoubleSpanScrollBarExtension::Reserved_2(){return 0;};


//
// TAknDoubleSpanScrollBarModel class
//
//
// This class stores its own model in its base class (TEikScrollBarModel)
// member variables as following:
//
//
// bits 31 to 0
//
// ZZAAAAAAAAAAAAA BBBBBBBBBBBBBBBB   (iScrollSpane)
// CCCCCCCCCCCCCCC DDDDDDDDDDDDDDDD   (iThumbSpan)
// EEEEEEEEEEEEEEE FFFFFFFFFFFFFFFF   (iThumbPosition)
//
// Bits ZZ = model type.
//           00 EikScrollBarModel
//           11 EikScrollBarModel
//           10 TAknDoubleSpanScrollBarModel
//           01 Reserved for future
//
// Bits   AAAAAAAAAAAAA = scale
// Bits BBBBBBBBBBBBBBB = scroll span
// Bits CCCCCCCCCCCCCCC = focus position
// Bits DDDDDDDDDDDDDDD = field position
// Bits EEEEEEEEEEEEEEE = field size
// Bits FFFFFFFFFFFFFFF = window size
//
//
// Reason for this solution is to preserve binary compatibility with the old model.
//
// If this model is not supported by the scrollbar system, then values are stored
// as in the base class for compatibility resons.

EXPORT_C TAknDoubleSpanScrollBarModel::TAknDoubleSpanScrollBarModel()
    {
    if (ModelIsSupported())
        {
        SetScrollBarModelType(EAknDoubleSpanScrollBarModel);
        SetScale(KDoubleSpanMinScaleValue);
        SetScrollSpanValue(0);
        SetFocusPositionValue(0);
        SetFieldPositionValue(0);
        SetFieldSizeValue(0);
        SetWindowSizeValue(0);
        }
    else
        {
        iScrollSpan = 0;
        iThumbSpan = 0;
        iThumbPosition = 0;
        }
    }

EXPORT_C TAknDoubleSpanScrollBarModel::TAknDoubleSpanScrollBarModel(const TEikScrollBarModel& aEikModel)
    {

    if(aEikModel.ScrollBarModelType() == EAknDoubleSpanScrollBarModel)
        {
        const TAknDoubleSpanScrollBarModel* model = static_cast <const TAknDoubleSpanScrollBarModel*> (&aEikModel);

        // if parameter is
        if (model->ModelIsSupported())
            {
            iScrollSpan = aEikModel.iScrollSpan;
            iThumbSpan = aEikModel.iThumbSpan;
            iThumbPosition = aEikModel.iThumbPosition;
            }
        else if(!ModelIsSupported() && model->ModelIsSupported())
            {
            SetScrollBarModelType(EAknDoubleSpanScrollBarModel);
            SetScale(KDoubleSpanMinScaleValue);
            SetScrollSpan(CheckMinMaxValue(model->ScrollSpan()));
            SetFocusPosition(CheckMinMaxValue(model->FocusPosition()));
            SetWindowSize(CheckMinMaxValue(model->WindowSize()));
            SetFieldPositionValue(0);
            SetFieldSizeValue(0);
            }
        }
    // if parameter is only eikscb
    else if(ModelIsSupported() && aEikModel.ScrollBarModelType() == EEikScrollBarModel)
        {
        SetScrollBarModelType(EAknDoubleSpanScrollBarModel);
        SetScale(KDoubleSpanMinScaleValue);
        SetScrollSpan(CheckMinMaxValue(aEikModel.iScrollSpan));
        SetFocusPosition(CheckMinMaxValue(aEikModel.iThumbPosition));
        SetWindowSize(CheckMinMaxValue(aEikModel.iThumbSpan));
        SetFieldPositionValue(0);
        SetFieldSizeValue(0);
        }
    else
        {
        SetScrollBarModelType(EAknDoubleSpanScrollBarModel);
        SetScale(KDoubleSpanMinScaleValue);
        SetScrollSpan(CheckMinMaxValue(aEikModel.iScrollSpan));
        SetFocusPosition(CheckMinMaxValue(aEikModel.iThumbPosition));
        SetWindowSize(CheckMinMaxValue(aEikModel.iThumbSpan));
        SetFieldPositionValue(0);
        SetFieldSizeValue(0);
        }
    }


EXPORT_C TInt TAknDoubleSpanScrollBarModel::ScrollSpan() const
    {
    if (ModelIsSupported())
        {
        // Assert that API user has not set TEikScrollBarModel values directly
        __ASSERT_ALWAYS(ScrollBarModelType() == EAknDoubleSpanScrollBarModel,Panic(EEikPanicOutOfRange));
        return Scale() * ScrollSpanValue();
        }
    else
        {
        return iScrollSpan;
        }
    }

EXPORT_C void TAknDoubleSpanScrollBarModel::SetScrollSpan(TInt aScrollSpan)
    {
    if (ModelIsSupported())
        {
        // Assert that API user has not set TEikScrollBarModel values directly
        __ASSERT_ALWAYS(ScrollBarModelType() == EAknDoubleSpanScrollBarModel,Panic(EEikPanicOutOfRange));
        SetScrollSpanValue(PrepareScaledValue(CheckMinMaxValue(aScrollSpan)));
        }
    else
        {
        iScrollSpan = aScrollSpan;
        }
    }

EXPORT_C TInt TAknDoubleSpanScrollBarModel::FocusPosition() const
    {
    if (ModelIsSupported())
        {
        // Assert that API user has not set TEikScrollBarModel values directly
        __ASSERT_ALWAYS(ScrollBarModelType() == EAknDoubleSpanScrollBarModel,Panic(EEikPanicOutOfRange));
        return Scale() * FocusPositionValue();
        }
    else
        {
        return iThumbPosition;
        }
    }

EXPORT_C void TAknDoubleSpanScrollBarModel::SetFocusPosition(TInt aFocusPosition)
    {
    if (ModelIsSupported())
        {
        // Assert that API user has not set TEikScrollBarModel values directly
        __ASSERT_ALWAYS(ScrollBarModelType() == EAknDoubleSpanScrollBarModel,Panic(EEikPanicOutOfRange));
        SetFocusPositionValue(PrepareScaledValue(CheckMinMaxValue(aFocusPosition)));
        }
    else
        {
        iThumbPosition = aFocusPosition;
        }
    }

EXPORT_C TInt TAknDoubleSpanScrollBarModel::FieldPosition() const
    {
    if (ModelIsSupported())
        {
        // Assert that API user has not set TEikScrollBarModel values directly
        __ASSERT_ALWAYS(ScrollBarModelType() == EAknDoubleSpanScrollBarModel,Panic(EEikPanicOutOfRange));
        return Scale() * FieldPositionValue();
        }
    else
        {
        return 0;
        }
    }

EXPORT_C void TAknDoubleSpanScrollBarModel::SetFieldPosition(TInt aFieldPosition)
    {
    if (ModelIsSupported())
        {
        // Assert that API user has not set TEikScrollBarModel values directly
        __ASSERT_ALWAYS(ScrollBarModelType() == EAknDoubleSpanScrollBarModel,Panic(EEikPanicOutOfRange));
        SetFieldPositionValue(PrepareScaledValue(CheckMinMaxValue(aFieldPosition)));
        }
    else
        {
        // do nothing
        }
    }

EXPORT_C TInt TAknDoubleSpanScrollBarModel::FieldSize() const
    {
    if (ModelIsSupported())
        {
        // Assert that API user has not set TEikScrollBarModel values directly
        __ASSERT_ALWAYS(ScrollBarModelType() == EAknDoubleSpanScrollBarModel,Panic(EEikPanicOutOfRange));
        return Scale() * FieldSizeValue();
        }
    else
        {
        return 0;
        }
    }

EXPORT_C void TAknDoubleSpanScrollBarModel::SetFieldSize(TInt aFieldSize)
    {
    if (ModelIsSupported())
        {
        // Assert that API user has not set TEikScrollBarModel values directly
        __ASSERT_ALWAYS(ScrollBarModelType() == EAknDoubleSpanScrollBarModel,Panic(EEikPanicOutOfRange));
        SetFieldSizeValue(PrepareScaledValue(CheckMinMaxValue(aFieldSize)));
        }
    else
        {
        // do nothing
        }
    }

EXPORT_C TInt TAknDoubleSpanScrollBarModel::WindowSize() const
    {
    if (ModelIsSupported())
        {
        // Assert that API user has not set TEikScrollBarModel values directly
        __ASSERT_ALWAYS(ScrollBarModelType() == EAknDoubleSpanScrollBarModel,Panic(EEikPanicOutOfRange));
        return Scale() * WindowSizeValue();
        }
    else
        {
        return iThumbSpan;
        }
    }

EXPORT_C void TAknDoubleSpanScrollBarModel::SetWindowSize (TInt aWindowSize)
    {
    if (ModelIsSupported())
        {
        // Assert that API user has not set TEikScrollBarModel values directly
        __ASSERT_ALWAYS(ScrollBarModelType() == EAknDoubleSpanScrollBarModel,Panic(EEikPanicOutOfRange));
        SetWindowSizeValue(PrepareScaledValue(CheckMinMaxValue(aWindowSize)));
        }
    else
        {
        iThumbSpan = aWindowSize;
        }
    }

TUint16 TAknDoubleSpanScrollBarModel::Scale() const
    {
    TUint16 scale = TUint16(KDoubleSpanModelMaskBitsScale16 & HighBytes(iScrollSpan));
    return scale;
    }

void TAknDoubleSpanScrollBarModel::SetScale(TUint16 aScale)
    {
    __ASSERT_ALWAYS(aScale != 0,Panic(EEikPanicOutOfRange));
    __ASSERT_ALWAYS(aScale <= KDoubleSpanMaxScaleValue,Panic(EEikPanicOutOfRange));

    iScrollSpan &= ~KDoubleSpanModelMaskBitsScale;
    iScrollSpan |= KDoubleSpanModelMaskBitsScale & (TInt(aScale) << 16);
    }

// getter/setters for raw values without scaling
TInt16 TAknDoubleSpanScrollBarModel::ScrollSpanValue() const
    {
    return LowBytes(iScrollSpan);
    }

void TAknDoubleSpanScrollBarModel::SetScrollSpanValue(TInt16 aScrollSpan)
    {
    SetLowBytes(iScrollSpan, aScrollSpan);
    }

TInt16 TAknDoubleSpanScrollBarModel::FocusPositionValue() const
    {
    return HighBytes(iThumbSpan);
    }

void TAknDoubleSpanScrollBarModel::SetFocusPositionValue(TInt16 aFocusPosition)
    {
    SetHighBytes(iThumbSpan, aFocusPosition);
    }

TInt16 TAknDoubleSpanScrollBarModel::FieldPositionValue() const
    {
    return LowBytes(iThumbSpan);
    }

void TAknDoubleSpanScrollBarModel::SetFieldPositionValue(TInt16 aFieldPosition)
    {
    SetLowBytes(iThumbSpan, aFieldPosition);
    }

TInt16 TAknDoubleSpanScrollBarModel::FieldSizeValue() const
    {
    return HighBytes(iThumbPosition);
    }

void TAknDoubleSpanScrollBarModel::SetFieldSizeValue(TInt16 aFieldSize)
    {
    SetHighBytes(iThumbPosition, aFieldSize);
    }

TInt16 TAknDoubleSpanScrollBarModel::WindowSizeValue() const
    {
    return LowBytes(iThumbPosition);
    }

void TAknDoubleSpanScrollBarModel::SetWindowSizeValue(TInt16 aWindowSize)
    {
    SetLowBytes(iThumbPosition, aWindowSize);
    }

TInt16 TAknDoubleSpanScrollBarModel::LowBytes(TInt aInt) const
    {
    return TInt16(KDoubleSpanModelMaskBitsLow & aInt);
    }

TInt16 TAknDoubleSpanScrollBarModel::HighBytes(TInt aInt) const
    {
    return TInt16((KDoubleSpanModelMaskBitsHigh & aInt) >> 16);
    }

void TAknDoubleSpanScrollBarModel::SetLowBytes(TInt& aInt, TInt16 aValue)
    {
    aInt &= KDoubleSpanModelMaskBitsHigh;
    aInt |= TInt(KDoubleSpanModelMaskBitsLow & aValue);
    }

void TAknDoubleSpanScrollBarModel::SetHighBytes(TInt& aInt, TInt16 aValue)
    {
    aInt &= KDoubleSpanModelMaskBitsLow;
    aInt |= TInt(aValue) << 16;
    }

TInt16 TAknDoubleSpanScrollBarModel::PrepareScaledValue(TInt aNonScaledValue)
    {
     __ASSERT_ALWAYS(KDoubleSpanMinModelValue <= aNonScaledValue && aNonScaledValue <= KDoubleSpanMaxModelValue, Panic(EEikPanicOutOfRange));

    TUint16 requiredScale = KDoubleSpanMinScaleValue;
    if (aNonScaledValue < 0)
        {
        requiredScale = TUint16(( -aNonScaledValue / KDoubleSpanMaxRawValue ) + KDoubleSpanMinScaleValue);
        }
    else
        {
        requiredScale = TUint16(( aNonScaledValue / KDoubleSpanMaxRawValue ) + KDoubleSpanMinScaleValue);
        }

    if ( requiredScale > Scale() )
        {
         ReScale( requiredScale );
        }
    TInt16 scaledValue = TInt16(aNonScaledValue / Scale());
     return scaledValue;
    }

void TAknDoubleSpanScrollBarModel::ReScale(TUint16 aNewScale)
    {
    __ASSERT_ALWAYS(aNewScale != 0,Panic(EEikPanicOutOfRange));
    __ASSERT_ALWAYS(aNewScale <= KDoubleSpanMaxScaleValue,Panic(EEikPanicOutOfRange));

    SetScrollSpanValue(TInt16((ScrollSpanValue() * Scale())/aNewScale));
    SetFocusPositionValue(TInt16((FocusPositionValue() * Scale())/aNewScale));
    SetFieldPositionValue(TInt16((FieldPositionValue() * Scale())/aNewScale));
    SetFieldSizeValue(TInt16((FieldSizeValue() * Scale())/aNewScale));
    SetWindowSizeValue(TInt16((WindowSizeValue() * Scale())/aNewScale));
    SetScale(aNewScale);
    }

void TAknDoubleSpanScrollBarModel::SetScrollBarModelType(TEikScrollBarModelType aModelType)
    {
    iScrollSpan &= KDoubleSpanModelMaskBitsType;
    iScrollSpan |= (~KDoubleSpanModelMaskBitsType) & aModelType;
    }

TInt TAknDoubleSpanScrollBarModel::CheckMinMaxValue(TInt aValue)
    {
    if ((aValue > 0) && (aValue > KDoubleSpanMaxModelValue))
        {
        return KDoubleSpanMaxModelValue;
        }
    if ((aValue < 0) && (aValue < KDoubleSpanMinModelValue))
        {
        return KDoubleSpanMinModelValue;
        }
    return aValue;
    }

TBool TAknDoubleSpanScrollBarModel::ModelIsSupported()
    {
    // Check here feature flags etc. to decide if this device can support this
    // type of model and scrollbars.
    return ETrue;
    }

TRect CAknDoubleSpanScrollBar::ExtensionArea() const
    {
    // Usage of hard-coded parent rectangle is acceptable since we're
    // interested in only about the ratio between scrollbar and extension.
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( TRect( 0, 0, 200, 200 ), AknLayoutScalable_Avkon::listscroll_gen_pane( 0 ).LayoutLine() );
    
    TRect parent( layoutRect.Rect() ); // parent of both extension and scrollbar
    
    layoutRect.LayoutRect( parent, AknLayoutScalable_Avkon::scroll_pane( 0 ).LayoutLine() );
    
    TRect scrollbar( layoutRect.Rect() );
    
    CAknDoubleSpanScrollBarExtension* extension1 = static_cast<CAknDoubleSpanScrollBarExtension*> (iExtension);
    if( extension1->iExtensionType & ENormalExpandedTouchArea )
        layoutRect.LayoutRect( parent, AknLayoutScalable_Avkon::aid_size_touch_scroll_bar( 0 ).LayoutLine() );
    else if( extension1->iExtensionType & EScaleExpandedTouchArea )
        layoutRect.LayoutRect( parent, AknLayoutScalable_Avkon::aid_size_touch_scroll_bar_cale( 0 ).LayoutLine() );
    else
        layoutRect.LayoutRect( parent, AknLayoutScalable_Avkon::aid_size_touch_scroll_bar( 0 ).LayoutLine() );
    TRect extension( layoutRect.Rect() );

    TRect area;
    
    if ( iOrientation == CEikScrollBar::EVertical )
        {
        area.iTl.iX = extension.iTl.iX - scrollbar.iTl.iX;
        area.iTl.iY = scrollbar.iTl.iY - extension.iTl.iY;
        area.iBr.iX = area.iTl.iX + extension.Width();
        area.iBr.iY = iSize.iHeight + ( extension.Height() - scrollbar.Height() );
        }
    else
        {
        area.iTl.iX = scrollbar.iTl.iY - extension.iTl.iY;
        area.iTl.iY = scrollbar.Width() - extension.Width();
        area.iBr.iX = iSize.iWidth + ( extension.Height() - scrollbar.Height() );
        area.iBr.iY = area.iTl.iY + extension.Width();
        }
    
    return area;
    }

