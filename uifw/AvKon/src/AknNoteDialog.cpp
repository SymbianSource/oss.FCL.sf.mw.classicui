/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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

#include <eikimage.h>
#include <eikcapc.h>

#include <eikon.hrh>
#include <touchfeedback.h>
#include "AknUtils.h"
#include "AknPanic.h"

#include "aknborders.h"
#include "aknappui.h"
#include "aknsoundsystem.h"

#include "aknnotedialog.h"
#include "aknnotecontrol.h"
#include "aknnoteattributes.h"
#include "AknDef.h"

#include <AknsFrameBackgroundControlContext.h>
#include "AknDebug.h"

#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
#include <gfxtranseffect/gfxtranseffect.h>
#include <akntransitionutils.h>
#include <akntranseffect.h>

#include <e32property.h>
#include <avkondomainpskeys.h>
#include <aknglobalpopupprioritycontroller.h>
#endif

#include <AknTasHook.h> // for testability hooks
const TInt EEikDialogFlagSleeping   =0x20000;

// -----------------------------------------------------------------------------
// Finds out if this control belongs to the window group that is in focus.
// This information can be used to skip effects when the window group is
// not visible.
//
// @param aThis The control in question.
//
// @return ETrue if the window group is in focus, otherwise EFalse
// -----------------------------------------------------------------------------
//
TBool IsFocusedWindowGroup( CAknNoteDialog* aThis )
    {
    RWindowTreeNode* node = aThis->DrawableWindow();
    // this code finds out if this control belongs to window group
    // that is in focus, there are some rare cases when the latest opened
    // popup goes behind another one (e.g. system lock query -> power key menu)
    // we don't want transition in that case
    RWsSession& wsSession = CEikonEnv::Static()->WsSession();

    if ( !node )
        {
        return EFalse;
        }
    TInt nodeWindowGroupId = node->WindowGroupId();
    TInt focusedWindowGroupId = wsSession.GetFocusWindowGroup();
    
    if ( nodeWindowGroupId == focusedWindowGroupId )
        {
        return ETrue;
        }

    TInt count = wsSession.NumWindowGroups( 0 );

    // because there is not leave here,so no need to use CleanupStack.
    CArrayFixFlat<TInt>* wgIds = new CArrayFixFlat<TInt>( count );
    if ( wgIds )
        {
        // Get list of window group ids from WServ
        wsSession.WindowGroupList( 0, wgIds );

        // Select the first in the list (which will always be the forground app)
        // and we assume that there always will be at least one window group with zero priority
        TInt wgId = (*wgIds)[0];

        delete wgIds;

        if ( focusedWindowGroupId == wgId )
            {
            return ETrue;
            }
        }
    return EFalse;
    }

//////////////////////////////////////////////////////////////////////
// CAknNoteDialogExtension
//////////////////////////////////////////////////////////////////////
NONSHARABLE_CLASS(CAknNoteDialogExtension) : public CBase
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
				                ,public MAknTransitionUtilsObserver
#endif											 
    {
    public:
        static CAknNoteDialogExtension* NewL( CAknNoteDialog& aOwner );
        ~CAknNoteDialogExtension();

#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
        // From MAknTransitionUtilsObserver
		TInt AknTransitionCallback(TInt aEvent, TInt aState = 0, 
                                   const TDesC8* aParams = NULL);
#endif
    private:
        CAknNoteDialogExtension( CAknNoteDialog& aOwner );
        void ConstructL();

    public:
        CAknNoteDialog& iOwner;

#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    // NoteControl() is now protected in CAknNoteDialog, so we need this
    // to start the animation from the callback.
    public:
        CAknNoteControl* iControl;
#endif
    };

CAknNoteDialogExtension::CAknNoteDialogExtension( CAknNoteDialog& aOwner )
    : iOwner( aOwner ) 
    {
    }

CAknNoteDialogExtension* CAknNoteDialogExtension::NewL( CAknNoteDialog& aOwner )
    {
    CAknNoteDialogExtension* self = new( ELeave ) CAknNoteDialogExtension( aOwner );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

void CAknNoteDialogExtension::ConstructL()
    {
    }

CAknNoteDialogExtension::~CAknNoteDialogExtension()
    {
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
	CAknTransitionUtils::RemoveObserver( this, 
	    CAknTransitionUtils::EEventControlTransitionFinished );
#endif
    }

#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
TInt CAknNoteDialogExtension::AknTransitionCallback(TInt /*aEvent*/, 
                                                    TInt /*aState*/, 
                                                    const TDesC8* /*aParams*/)
	{
	TRAP_IGNORE(iControl->StartAnimationL());
	
	CAknTransitionUtils::RemoveObserver( this, 
	    CAknTransitionUtils::EEventControlTransitionFinished );
	     
	return KErrNone;
	}
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EXPORT_C CAknNoteDialog::CAknNoteDialog() : CEikDialog(),
    iTimeoutInMicroseconds(ENoTimeout), iTone(ENoTone)
    {
    AKNTASHOOK_ADD( this, "CAknNoteDialog" );
    }

EXPORT_C CAknNoteDialog::CAknNoteDialog(const TTone& aTone, const TTimeout& aTimeout) :
    CEikDialog(), iTimeoutInMicroseconds(aTimeout), iTone(aTone)
    {
    AKNTASHOOK_ADD( this, "CAknNoteDialog" );
    }

EXPORT_C CAknNoteDialog::CAknNoteDialog(CEikDialog** aSelfPtr,const TTone& aTone, const TTimeout& aTimeout) :
    CEikDialog(), iTimeoutInMicroseconds(aTimeout), iSelfPtr(aSelfPtr), iTone(aTone)
     {
     AKNTASHOOK_ADD( this, "CAknNoteDialog" );
     }

EXPORT_C CAknNoteDialog::~CAknNoteDialog()
    {
    AKNTASHOOK_REMOVE();
// FIXME: Experimental heuristics for determining popup type
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS

    if ( GfxTransEffect::IsRegistered( this ) )
        {
        // abort component effects (possibly appear effect) 
        // if aknnote gets destroyed without user interaction or timers
        GfxTransEffect::NotifyExternalState( ENotifyGlobalAbort );
		GfxTransEffect::Deregister(this); //Always deregister in destructor.
        }
    CAknTransitionUtils::RemoveData( ( TInt )NoteControl() );
#endif    
    
    delete iTimer;
#if defined _DEBUG && defined __WINS__
    if (!(DialogFlags()&EEikDialogFlagWait))
        DbgCheckSelfPtr(iSelfPtr);
#endif
    if (iSelfPtr) 
        {
        *iSelfPtr = NULL;
        iSelfPtr = NULL;
        }

    delete iControlAttributes;
    delete iNoteExtension;
    }

EXPORT_C void CAknNoteDialog::SetTimeout(const TTimeout& aTimeout)
    {
    iTimeoutInMicroseconds = aTimeout;
    }


EXPORT_C void CAknNoteDialog::SetTone(const TTone& aTone)
    {
    iTone = aTone;
    }

EXPORT_C void CAknNoteDialog::SetTextWrapping(TBool aEnabled)
    {
    CAknNoteAttributes* attr = ControlAttributes();
    if ( !attr )
        {
        return; // Nothing else we can do
        }
    if (aEnabled)
        {
        attr->iClearFlags.Set(ENoteNoTextWrapping);
        }
    else
        {
        attr->iFlags.Set(ENoteNoTextWrapping);
        }

    LayoutAndDraw();
    }

EXPORT_C void CAknNoteDialog::SetTextProcessing(TBool aEnabled)
    {
    CAknNoteAttributes* attr = ControlAttributes();
    if ( !attr )
        {
        return; // Nothing else we can do
        }
    if (aEnabled)
        {
        attr->iClearFlags.Set(ENoteNoTextProcessing);
        }
    else
        {
        attr->iFlags.Set(ENoteNoTextProcessing);
        }

    LayoutAndDraw();    
    }

EXPORT_C void CAknNoteDialog::SetImageL(CEikImage* aImage)
    {
    CAknNoteAttributes* attr = ControlAttributes();
    if ( !attr )
        {
        User::Leave(KErrNoMemory);
        }
    attr->SetImageL(aImage);
    
    if (attr->IsLayoutNeeded())
        {
        LayoutAndDraw();
        }   
    }

EXPORT_C void CAknNoteDialog::SetIconL(CEikImage* aIcon)
    {
    CAknNoteAttributes* attr = ControlAttributes();
    if ( !attr )
        {
        User::Leave(KErrNoMemory);
        }
    attr->SetIconL(aIcon);
    
    if (attr->IsLayoutNeeded())
        {
        LayoutAndDraw();
        }   
    }

EXPORT_C void CAknNoteDialog::SetTextNumberL(TInt aNumber)
    {
    CAknNoteAttributes* attr = ControlAttributes();
    if ( !attr )
        {
        User::Leave(KErrNoMemory);
        }
    attr->SetTextNumberL(aNumber);
    
    if (attr->IsLayoutNeeded())
        {
        LayoutAndDraw();
        }   
    }

EXPORT_C void CAknNoteDialog::SetTextPluralityL(const TBool aIsPlural)
    {
    CAknNoteAttributes* attr = ControlAttributes();
    if ( !attr )
        {
        User::Leave(KErrNoMemory);
        }
    attr->SetTextPluralityL(aIsPlural);
    
    if (attr->IsLayoutNeeded())
        {
        LayoutAndDraw();
        }   

    }

EXPORT_C void CAknNoteDialog::SetTextL(const TDesC& aLabel)
    {
    CAknNoteAttributes* attr = ControlAttributes();
    if ( !attr )
        {
        User::Leave(KErrNoMemory);
        }
    if (attr->Text().Compare( aLabel ) )
        {
        attr->SetTextL(aLabel);
        if (attr->IsLayoutNeeded())
            {
            LayoutAndDraw();
            }   
        }
    }

/**
 * @deprecated - use SetTextL
 */
EXPORT_C void CAknNoteDialog::SetCurrentLabelL(TInt /*aControlId*/,const TDesC& aLabel)
    {
    SetTextL(aLabel);
    }

EXPORT_C TKeyResponse CAknNoteDialog::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    /// Only interested in standard key events
    if (aType != EEventKey ||
        (aType == EEventKey && aKeyEvent.iCode == EKeyEscape)
        ) // must pass escape event to dialog.
        {
        return CEikDialog::OfferKeyEventL(aKeyEvent,aType);
        }
    
    /// All short keypresses dismisses the note
    if ( !aKeyEvent.iRepeats )
        {
        StaticDeleteL(this);
        }
    return EKeyWasConsumed;
    }

EXPORT_C void CAknNoteDialog::LayoutAndDraw()
    {
    if (IsActivated())
        {
        TRect screenRect = iAvkonAppUi->ApplicationRect();
        SetSizeAndPosition(PreferredSize( screenRect.Size()/*TSize(AKN_LAYOUT_WINDOW_screen.iW,AKN_LAYOUT_WINDOW_screen.iH)*/));
        DrawNow();

        // Tell the attributes that the note has been fully drawn.
        // Optimized text drawing is allowed only after this.
        CAknNoteAttributes* attr = ControlAttributes();
        if ( attr )
            {
            RDebug::Print(_L("CAknNoteDialog allowing opt. draw, %d"), (TUint)this );            
            attr->AllowOptimizedDrawing();
            }
        }
    }

EXPORT_C TInt CAknNoteDialog::RunLD()
    {
    PlayTone();
    ReportUserActivity();

// FIXME: Experimental heuristics for finding out popup context from image/animation
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS    
    TInt uid = ( TInt )CAknTransitionUtils::GetData( ( TInt )NoteControl() );
    // only change registration, if not registered, don't register
    if ( uid != 0 &&  GfxTransEffect::IsRegistered( this ) ) 
        {
        GfxTransEffect::Register( this, TUid::Uid( uid ) );
        CAknTransitionUtils::RemoveData( ( TInt )NoteControl() );
        }
#endif
        
    return CEikDialog::RunLD();
    }

EXPORT_C TInt CAknNoteDialog::StaticDeleteL(TAny *aThis)
    {
    CAknNoteDialog* self = REINTERPRET_CAST(CAknNoteDialog*,aThis);
        
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS           
    if ( self->IsVisible() && GfxTransEffect::IsRegistered( self ) &&
        IsFocusedWindowGroup( self ) )
		{
        TBool rsWasEnabled( EFalse );
        if( !CAknEnv::Static()->TransparencyEnabled() && self->DrawableWindow() && self->Window().IsRedrawStoreEnabled() )
            {
            rsWasEnabled = ETrue;
            // disable redrawstore during transition to avoid
            // drawing problems behind control
            self->Window().EnableRedrawStore( EFalse );
            }

        GfxTransEffect::NotifyExternalState( ENotifyGlobalAbort ); 

		//If still visible, do a transition to invisible state.
		CAknTransitionUtils::SetAllParents(self);
		GfxTransEffect::Begin(self, KGfxControlDisappearAction);
		GfxTransEffect::NotifyExternalState(ECaptureComponentsBegin, (const TDesC8*)self);
		
		TRect demarcation;
		CAknTransitionUtils::GetDemarcation(CAknTransitionUtils::EPopup, 
		                                    demarcation);
		GfxTransEffect::SetDemarcation(self, demarcation);
		
		self->MakeVisible(EFalse);
		
		GfxTransEffect::NotifyExternalState(ECaptureComponentsEnd, (const TDesC8*)self);
		GfxTransEffect::End(self);
		
		if( !CAknEnv::Static()->TransparencyEnabled() && rsWasEnabled )
            {
            // if redrawstore was on before transition,
            // enable it again
            self->Window().EnableRedrawStore( ETrue );
            }


		}

#endif // RD_UI_TRANSITION_EFFECTS_POPUPS        
    // Only actual delete the note if it's not a sleeping note
    // Deleting a sleeping note is really bad!
    if (!(self->DialogFlags()&EEikDialogFlagSleeping))
        {
        delete self; 
        }
    else
        {
        // Tell subclasses that the dialog is going to sleep
        if (self->iTimer)
            self->iTimer->Cancel();
        self->OkToExitL(KErrCancel);
        self->ExitSleepingDialog();
        self->NoteControl()->Reset();
        }
    return EFalse;
    }


EXPORT_C void CAknNoteDialog::SetSizeAndPosition( const TSize& aSize )
    {
    SetBorder( TGulBorder::ENone );
    CAknNoteControl* note = NoteControl();
    if (note)
        {
        if (!ControlAttributes()->IsLayoutNeeded()) // if we have a note control, there must be attributes also
            return;
        
        if ( AknLayoutUtils::PenEnabled() )
            {
            CEikDialog::SetSizeAndPosition( aSize );
            }
        else
            {
            TRect mainPane;
            AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EPopupParent,
                mainPane );

            TAknWindowLineLayout dialogLay;
            note->WindowLayout( dialogLay );

            AknLayoutUtils::LayoutControl(this, mainPane, dialogLay);
            }
   
        ControlAttributes()->SetLayoutDone();                
        }
    }

EXPORT_C void CAknNoteDialog::PreLayoutDynInitL()
    {
    TransferControlAttributes();

    if ( AknLayoutUtils::PenEnabled() )
        {
        // set to capture globally, if dialog have to be closed when tapped to screen
        if ( DialogFlags()&EEikDialogFlagCloseDialogWhenTapped ) 
            {
            SetGloballyCapturing(ETrue);        
            }
        SetPointerCapture(ETrue);
        }
    }

EXPORT_C void CAknNoteDialog::PostLayoutDynInitL()
    {
    __ASSERT_DEBUG(NoteControl(), Panic(EAknPanicNullPointer));

    CreateExtensionL();

    // In some cases the animation completes it's cycle in wserv 
    // before the note appears on screen, so we're delaying the 
    // start of the animation with an idle object.
    // -- fix withdrawn --
    //iNoteExtension->iIdle = CIdle::NewL( CActive::EPriorityIdle );
    //iNoteExtension->iIdle->Start(TCallBack(CallbackStartAnimationL, this));

    NoteControl()->StartAnimationL();

    if ( iTimeoutInMicroseconds != ENoTimeout )
        {
        if (!iTimer)
            {
            iTimer = CPeriodic::NewL(0);
            }
        if (iTimer->IsActive())
            {
            iTimer->Cancel();
            }
        iTimer->Start(iTimeoutInMicroseconds,iTimeoutInMicroseconds,TCallBack(StaticDeleteL,this));
        }
    }

EXPORT_C void CAknNoteDialog::PlayTone()
    {
    if (iTone != 0 && SoundSystem())
        {
        SoundSystem()->PlaySound(iTone);
        }
    }

EXPORT_C void CAknNoteDialog::ReportUserActivity() const 
    {
#ifdef AVKON_RDEBUG_INFO
    RDebug::Print(_L("Reset user inactivity"));
#endif
    User::ResetInactivityTime();
    }

EXPORT_C CAknNoteControl* CAknNoteDialog::NoteControl()  
    {
    CEikCaptionedControl* linePtr = GetFirstLineOnFirstPageOrNull();
    if (linePtr) 
        {
        return STATIC_CAST( CAknNoteControl*,  linePtr->iControl);
        }
    return NULL;
    }

EXPORT_C CAknKeySoundSystem* CAknNoteDialog::SoundSystem() const
    {
    if (iEikonEnv->AppUi())
        {
        return iAvkonAppUiBase->KeySounds();          
        }
    return NULL;
    }

EXPORT_C CAknNoteAttributes* CAknNoteDialog::ControlAttributes() 
    {
    if (NoteControl() && !iControlAttributes)
        {
        return NoteControl()->Attributes();
        }
    else 
        {
        if (!iControlAttributes)
            {
            iControlAttributes = new CAknNoteAttributes();
            }
        return iControlAttributes;
        }
    }

EXPORT_C void CAknNoteDialog::TransferControlAttributes()
    {
    if (iControlAttributes)
        {
        __ASSERT_DEBUG(NoteControl(),Panic(EAknPanicNullPointer));
        __ASSERT_DEBUG(NoteControl()->Attributes(),Panic(EAknPanicNullPointer));
        *(NoteControl()->Attributes()) =  *iControlAttributes;

        delete iControlAttributes;
        iControlAttributes = NULL;          
        }

    NoteControl()->Attributes()->InvalidateLayout();
    NoteControl()->Layout();
    }

/**
 * Check that the self pointer is not a stack pointer and points to this.
 *
 *   
 *
 * @param aAddr The pointer to be checked
 */
#if defined _DEBUG && defined __WINS__
void CAknNoteDialog::DbgCheckSelfPtr(CEikDialog** aSelfPtr)
    {
    TUint32 addrSeg = TUint32(aSelfPtr) & 0xffff0000;
    TUint32 stackAddrSeg = TUint32(&aSelfPtr) & 0xffff0000;

    // If this assert triggers, it looks like your code is using a stack based pointer
    // as the self-ptr passed in to a non-waiting note dialog. This is a cause of
    // obscure fatal errors and must not be done.
    ASSERT(addrSeg != stackAddrSeg);

    // new check that the self pointer points to this object
    if (aSelfPtr)
        {
        TUint32 self = TUint32(this);
        TUint32 selfPointedTo = TUint32(*aSelfPtr);

        // If this assert triggers, it looks like your code has given this dialog
        // a self-ptr which does not point to itself. Perhaps it was member data of
        // an object which has been deleted, or the pointer has been overwritten.
        ASSERT(self == selfPointedTo || selfPointedTo == NULL);
        }
    }
#else
void CAknNoteDialog::DbgCheckSelfPtr(CEikDialog** /*aSelfPtr*/)
	{
	}
#endif


EXPORT_C void CAknNoteDialog::HandleResourceChange(TInt aType)
    {
    if(aType==KEikDynamicLayoutVariantSwitch)
        {
        if (!IsVisible())
        	{
        	// a invisible note dialog is assumed to be a sleeping dialog
        	// in which case it will update layout when it is roused.
        	return;
        	}
        CEikDialog::HandleResourceChange(aType);
        ControlAttributes()->InvalidateLayout();
        LayoutAndDraw();
        SizeChanged();
        return; // we already did the base call
        }
    else if( aType == KAknsMessageSkinChange )
        {
        if (!IsVisible() && (DialogFlags() & EEikDialogFlagSleeping) )
        	{
        	// a invisible note dialog is assumed to be a sleeping dialog
        	// in which case it will update skin when it is roused.
        	return;
        	}
        SetSkinBackGroundRect();
        if ( NoteControl() && NoteControl()->Attributes() )
            {
            ControlAttributes()->InvalidateLayout();
            
            // Gets the correct image for the skin.
            TRAP_IGNORE(NoteControl()->Attributes()->HandleSkinChangeL());
            TRAP_IGNORE(NoteControl()-> CreateDefaultImageL() );
            
            NoteControl()->Layout();
            }
        }

    CEikDialog::HandleResourceChange(aType);
    }

/**
 * Deprecated methods
 */

/**
 * @deprecated
 */
EXPORT_C TInt CAknNoteDialog::ExecuteDlgLD(const TTimeout aTimeout,const TTone aTone,TInt aResourceID)
    {
    SetTimeout(aTimeout);
    SetTone(aTone);
    return ExecuteLD(aResourceID);
    }

/**
 * @deprecated
 */
EXPORT_C TInt CAknNoteDialog::ExecuteDlgLD(const TTone aTone,TInt aResourceID)
    {
    SetTone(aTone);
    return ExecuteLD(aResourceID);
    }

/**
 * @deprecated
 */
EXPORT_C TInt CAknNoteDialog::ExecuteDlgLD(TInt aResourceId, TInt /*aNoteControlId*/)
    {
    return ExecuteLD(aResourceId);
    }

/**
 * @deprecated
 */
EXPORT_C TInt CAknNoteDialog::RunDlgLD(const TTimeout aTimeout,const TTone aTone)
    {
    SetTimeout(aTimeout);
    SetTone(aTone);
    return RunLD();
    }

/**
 * @deprecated
 */
EXPORT_C TInt CAknNoteDialog::RunDlgLD(const TTone aTone)
    {
    SetTone(aTone);
    return RunLD();
    }

/**
 * @deprecated
 */
EXPORT_C TInt CAknNoteDialog::RunDlgLD()
    {
    return RunLD();
    }

/**
 * @deprecated
 */
EXPORT_C TInt CAknNoteDialog::RunDlgLD(TInt /*aNoteControlId*/)
    {
    return RunLD();
    }

EXPORT_C void CAknNoteDialog::CEikDialog_Reserved_1()
    {
    }

EXPORT_C void CAknNoteDialog::CEikDialog_Reserved_2()
    {
    }

EXPORT_C void CAknNoteDialog::CAknNoteDialog_Reserved()
    {
    }

EXPORT_C void CAknNoteDialog::SizeChanged()
    {  

    CEikDialog::SizeChanged();
    
    SetSkinBackGroundRect();

    if ( NoteControl() )
        {
        NoteControl()->Layout();
        }

    }

void CAknNoteDialog::SetSkinBackGroundRect()
    {
    if (!NoteControl() || !NoteControl()->Attributes())
        {
        return; 
        }
    NoteControl()->SetBgRect(Rect(),PositionRelativeToScreen());    
    }

EXPORT_C void CAknNoteDialog::SetNoMemoryAllocation()
    {
    if (!NoteControl() || !NoteControl()->Attributes())
        {
        User::Invariant(); 
        }
    NoteControl()->Attributes()->iFlags.Set(ENoteDoNotAllocateMem);
    }

void CAknNoteDialog::CreateExtensionL()
    {
    if ( !iNoteExtension )
        {
        iNoteExtension = CAknNoteDialogExtension::NewL(*this);
        }
    }

TInt CAknNoteDialog::CallbackStartAnimationL(TAny* aThis)
    {
    CAknNoteDialog* me = static_cast<CAknNoteDialog*>(aThis);
    me->NoteControl()->StartAnimationL();
    return 0;
    }
//------------------------------------------------------------------------------
// CAknNoteDialog::HandlePointerEventL()
// HandlePointerEventL processes the pointer event directed to the notedialog.
//------------------------------------------------------------------------------
//

EXPORT_C void CAknNoteDialog::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    if ( AknLayoutUtils::PenEnabled() )
        {
        CCoeControl* ctrl = GrabbingComponent();
        CCoeControl::HandlePointerEventL(aPointerEvent);
        
        if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
            {
            if ( DialogFlags()&EEikDialogFlagCloseDialogWhenTapped )
                {
                //Touch release gives pop-up effect if note can be dismissed.
                if ( ctrl )
                    {
                    // if grabbingComponent and dialog has 'close dialog when 
                    // tapped flag', then close dialog here because tapping happened. 
                    if ( !IsBeingDestroyed() )
                        {
                        StaticDeleteL( this );
                        }
                    
                    MTouchFeedback* feedback = MTouchFeedback::Instance();
                    if ( feedback )
                        {
                        feedback->InstantFeedback( ETouchFeedbackPopUp );
                        }
                    }
                }
            }
        }
    }


EXPORT_C void* CAknNoteDialog::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

EXPORT_C void CAknNoteDialog::ExitSleepingDialog()
    {
    CAknNoteControl* ctrl = 0;
    ctrl = NoteControl();
    if ( ctrl )
        { // if there is no animation, just returns KErrGeneral
        ctrl->CancelAnimation();
        }
    CEikDialog::ExitSleepingDialog();
    }

// End of File
