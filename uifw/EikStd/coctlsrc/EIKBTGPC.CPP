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

#include <barsread.h>
#include <coemain.h>
#include <eikbtgpc.h>
#include <eikbtgrp.h>
#include <eikbtgps.h>
#include <eikenv.h>
#include <eikcmobs.h>
#include <eiktbar.h>
#include <eikbtpan.h>
#include <eikpanic.h>
#include "LAFBTGPC.H"
#include <eikbgfty.h>
#include <uikon.hrh>
#include <eikcmbut.h>
#include <aknenv.h>
#include <AknLayout.lag>
#include <AknIconUtils.h>
#include <aknappui.h>
#include <AknUtils.h>
#include <eiklbx.h>

#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikenvinterface.h> 
#endif

#include <AknTasHook.h>
const TInt KCleanupNoCommand = -1;
const TInt KNoCommand = 0;
const TInt KIsValid = 1;

inline CEikButtonGroupContainer::TCmdPos::TCmdPos()
    : iPos(KCleanupNoCommand), iCmd(KNoCommand)
    {
    }
    
inline CEikButtonGroupContainer::TCmdPos::TCmdPos(TInt aPos, TInt aCmd)
    : iPos(aPos), iCmd(aCmd)
    {
    }

inline CEikButtonGroupContainer::TCmdObserver::TCmdObserver(TInt aPos, 
    MEikCommandObserver& aObserver)
    : iPos(aPos), iObserver(aObserver)
    {
    }

inline CEikButtonGroupContainer::CCmdObserverArray::CCmdObserverArray()
    : CArrayFixFlat<CEikButtonGroupContainer::TCmdObserver>(1)
    {
    }

TInt CEikButtonGroupContainer::CCmdObserverArray::FindIndex(TInt aPos)
    {
    const TInt count = Count();
    TInt index = KErrNotFound;
    for (TInt ii = 0; ii < count; ii++)
        {
        if (At(ii).iPos == aPos)
            {
            index = ii;
            break;
            }
        }
    return index;
    }

inline CCoeControl* CEikButtonGroupContainer::ButtonGroupAsControl() const
    {
    CCoeControl* ctrl = iButtonGroup->AsControl();
    // __ASSERT_DEBUG(ctrl...
    return ctrl;
    }

/**
 * Creates a button group container in its own window. Requesting aUse as either EView or 
 * EDialog will create the default button set for the host device; the other options are 
 * included primarily for testing. aOrientation is required only for dialogs on pen based 
 * machines that may layout their buttons either horizontally or vertically. aResourceId 
 * may be NULL if buttons are to be added dynamically.
 */
EXPORT_C CEikButtonGroupContainer* CEikButtonGroupContainer::NewL(
    TUse aUse,
    TOrientation aOrientation,
    MEikCommandObserver* aCommandObserver,
    TInt aResourceId,
    TUint aFlags)
    { // static
    CEikButtonGroupContainer* self = new(ELeave) CEikButtonGroupContainer(aUse);
    CleanupStack::PushL(self);
    self->ConstructL(aOrientation, aCommandObserver, aResourceId, NULL, aFlags);
    CleanupStack::Pop(); // self
    AKNTASHOOK_ADDL( self, "CEikButtonGroupContainer" );
    return self;
    }

/**
 * Creates a button group container in aParent's window. Requesting aUse as either EView or 
 * EDialog will create the default button set for the host device; the other options are 
 * included primarily  for testing. aOrientation is required only for dialogs on pen based 
 * machines that may layout their buttons either horizontally or vertically. aResourceId 
 * may be NULL if buttons are to be added dynamically.
 */
EXPORT_C CEikButtonGroupContainer* CEikButtonGroupContainer::NewL(
    TUse aUse,
    TOrientation aOrientation,
    MEikCommandObserver* aCommandObserver,
    TInt aResourceId,
    const CCoeControl& aParent,
    TUint aFlags)
    { // static
    CEikButtonGroupContainer* self = new(ELeave) CEikButtonGroupContainer(aUse);
    CleanupStack::PushL(self);
    self->SetContainerWindowL(aParent);

    RWindowGroup* targetGroup = NULL;
    
    if ( aFlags & EIsEmbedded )
        {
        aFlags |= EParentIsControl;
        targetGroup = (RWindowGroup*)&aParent;
        }
    
    self->ConstructL(aOrientation, aCommandObserver, aResourceId, targetGroup,
            aFlags);
    CleanupStack::Pop(); // self
    AKNTASHOOK_ADDL( self, "CEikButtonGroupContainer" );
    return self;
    }

/**
 * Creates a button group container in aParentWg window group. Requesting aUse as either EView or 
 * EDialog will create the default button set for the host device; the other options are 
 * included primarily  for testing. aOrientation is required only for dialogs on pen based 
 * machines that may layout their buttons either horizontally or vertically. aResourceId 
 * may be NULL if buttons are to be added dynamically.
 */
EXPORT_C CEikButtonGroupContainer* CEikButtonGroupContainer::NewL(
    TUse aUse,
    TOrientation aOrientation,
    MEikCommandObserver* aCommandObserver,
    TInt aResourceId,
    RWindowGroup& aParentWg,
    TUint aFlags)
    { // static
    CEikButtonGroupContainer* self = new(ELeave) CEikButtonGroupContainer(aUse);
    CleanupStack::PushL(self);
    self->ConstructL(aOrientation, aCommandObserver, aResourceId, &aParentWg, aFlags);
    CleanupStack::Pop(); // self
    AKNTASHOOK_ADDL( self, "CEikButtonGroupContainer" );
    return self;
    }

EXPORT_C CEikButtonGroupContainer::~CEikButtonGroupContainer()
    {
    AKNTASHOOK_REMOVE();
    AVKONENV->InformCbaDeletion(this);
    CEikButtonGroupStack::Remove(*this);
    if (iButtonGroup)
        {
        iButtonGroup->Release();
        }
    if (iMSKObserverOwner)
        {
        iMSKObserverOwner->InformMSKButtonGroupDeletion();
        iMSKObserverOwner = NULL;
        }
    delete iCommandsCleanup;
    iCommandsCleanup = NULL;
    delete iObserverArray;
    iValid = KErrNotFound;
    iObserverArray = NULL;
    }

/**
 * Returns a pointer to an app's currently active CEikButtonGroupContainer (if any).
 * Returns NULL if there are no containers active or none suitable for sharing.
 * Ownership of the pointer returned is not transferred.
 */
EXPORT_C CEikButtonGroupContainer* CEikButtonGroupContainer::Current()
    { // static
    return CEikButtonGroupStack::Current();
    }

/**
 * Removes the command identified by aCommandId, in position aPosition in the group, from the
 * command stack. Automatically retrieves the previous command details.
 *
 * Commands are added to the stack by calling AddCommandToStackL. 
 */
EXPORT_C void CEikButtonGroupContainer::RemoveCommandFromStack(TInt aPosition, TInt aCommandId)
    {
    iButtonGroup->RemoveCommandFromStack(aPosition, aCommandId);
    }

EXPORT_C void CEikButtonGroupContainer::SetDefaultCommand(TInt aCommandId)
    {
    iButtonGroup->SetDefaultCommand(aCommandId);
    }

EXPORT_C TSize CEikButtonGroupContainer::CalcMinimumSizeL(TInt aResourceId) const
    {
    return iButtonGroup->CalcMinimumSizeL(aResourceId);
    }

void CEikButtonGroupContainer::CleanupCommandDestroy(TAny* aPtr)
    { // static
    REINTERPRET_CAST(CEikButtonGroupContainer*, aPtr)->DoCleanupCommandPopAndDestroy();
    }

/**
 * Places the command in position aPosition in the group on the cleanup stack. Typically used
 * when a control or view changes the contents of two or more buttons on receipt of focus. 
 * After altering one command with a call to AddCommandToStackL the push is made to
 * guarantee the display will be left in a consistent state if the second (and any subsequent)
 * calls to AddCommandToStackL fail.
 *
 * Only a single command can be pushed for each position.
 */
EXPORT_C void CEikButtonGroupContainer::CleanupCommandPushL(TInt aPosition)
    {
    const TInt count = iCommandsCleanup->Count();
    TBool pushed = EFalse;
    for (TInt ii = 0; ii < count; ii++)
        {
        TCmdPos& cmdPos = (*iCommandsCleanup)[ii];
        __ASSERT_ALWAYS(cmdPos.iPos != aPosition, Panic(EEikPanicButtonGroupDuplicateCleanupPos));  
        if (cmdPos.iPos == KCleanupNoCommand)
            {
            cmdPos.iPos = aPosition;
            cmdPos.iCmd = iButtonGroup->CommandId(aPosition);
            pushed = ETrue;
            break;
            }
        }
    __ASSERT_ALWAYS(pushed, Panic(EEikPanicButtonGroupCleanupCorrupt));
    CleanupStack::PushL(TCleanupItem(CleanupCommandDestroy, this));
    }

/**
 * Removes a command (or aCount commands) altered by calling AddCommandToStackL from the cleanup
 * stack without changing its state.
 */
EXPORT_C void CEikButtonGroupContainer::CleanupCommandPop(TInt aCount)
    {
    while (aCount--)
        {
        DoCleanupCommandPop();
        CleanupStack::Pop();
        }
    }

CEikButtonGroupContainer::TCmdPos CEikButtonGroupContainer::DoCleanupCommandPop()
    {
    const TInt count = iCommandsCleanup->Count();
    TInt index = -1;
    for (TInt ii = 0; ii < count; ii++)
        {
        if ((*iCommandsCleanup)[ii].iPos == KCleanupNoCommand)
            {
            index = ii - 1;
            __ASSERT_DEBUG(index != -1, Panic(EEikPanicButtonGroupCleanupCorrupt));
            break;
            }
        }
    if (index == -1)
        { // all cleanup slots are filled
        index = count-1;
        }
    TCmdPos cmdPos = (*iCommandsCleanup)[index];
    iCommandsCleanup->At(index) = TCmdPos();
    return cmdPos;
    }

void CEikButtonGroupContainer::DoCleanupCommandPopAndDestroy()
    {
    TCmdPos cmdPos = DoCleanupCommandPop();
    RemoveCommandFromStack(cmdPos.iPos, cmdPos.iCmd);
    }

/**
 * Returns the maximum number of commands a particular device supports.
 */
EXPORT_C TInt CEikButtonGroupContainer::MaxCommands() const
    {
    return 4; // !!! need to get this from LAF
    }

/**
 * Returns the number of buttons currently present.
 */
EXPORT_C TInt CEikButtonGroupContainer::ButtonCount() const
    {
    return iButtonGroup->ButtonCount();
    }

EXPORT_C void CEikButtonGroupContainer::DimCommand(TInt aCommandId, TBool aDimmed)
    {
    iButtonGroup->DimCommand(aCommandId, aDimmed);
    }

EXPORT_C TBool CEikButtonGroupContainer::IsCommandDimmed(TInt aCommandId) const
    {
    return iButtonGroup->IsCommandDimmed(aCommandId);
    }

EXPORT_C void CEikButtonGroupContainer::MakeCommandVisible(TInt aCommandId, TBool aVisible)
    {
    iButtonGroup->MakeCommandVisible(aCommandId, aVisible);
    }

EXPORT_C TBool CEikButtonGroupContainer::IsCommandVisible(TInt aCommandId) const
    {
    return iButtonGroup->IsCommandVisible(aCommandId);
    }

EXPORT_C void CEikButtonGroupContainer::AnimateCommand(TInt aCommandId)
    {
    iButtonGroup->AnimateCommand(aCommandId);
    }

EXPORT_C void CEikButtonGroupContainer::DimCommandByPosition(TCommandPosition aPosition, 
    TBool aDimmed)
    {
    iButtonGroup->DimCommandByPosition((TInt)aPosition, aDimmed);
    }

EXPORT_C TBool CEikButtonGroupContainer::IsCommandDimmedByPosition(TCommandPosition aPosition) const
    {
    return iButtonGroup->IsCommandDimmedByPosition((TInt)aPosition);
    }

EXPORT_C void CEikButtonGroupContainer::MakeCommandVisibleByPosition(TCommandPosition aPosition, 
    TBool aVisible)
    {
    iButtonGroup->MakeCommandVisibleByPosition((TInt)aPosition, aVisible);
    }

EXPORT_C TBool CEikButtonGroupContainer::IsCommandVisibleByPosition(
    TCommandPosition aPosition) const
    {
    return iButtonGroup->IsCommandVisibleByPosition((TInt)aPosition);
    }

EXPORT_C void CEikButtonGroupContainer::AnimateCommandByPosition(TCommandPosition aPosition)
    {
    iButtonGroup->AnimateCommandByPosition((TInt)aPosition);
    }


EXPORT_C TSize CEikButtonGroupContainer::MinimumSize()
    {
    TSize size = ButtonGroupAsControl()->MinimumSize();
    // add borders size from LAF
    return size;
    }

CEikButtonGroupContainer::CEikButtonGroupContainer(TUse aUse)
    : iUse(aUse)
    {
    SetComponentsToInheritVisibility();
    }

void CEikButtonGroupContainer::ConstructL(
    TOrientation aOrientation,
    MEikCommandObserver* aCommandObserver,
    TInt aResourceId,
    RWindowGroup* aParentWg,
    TUint aFlags)
    {
    iValid = KIsValid;
    iCommandObserver = aCommandObserver;
    const TInt numCmds = MaxCommands();
    iCommandsCleanup = new(ELeave) CArrayFixFlat<TCmdPos>(numCmds);
    for (TInt ii = 0; ii < numCmds; ii++)
        {
        iCommandsCleanup->AppendL(TCmdPos());
        }

    TInt buttonType = LafButtonGroupContainer::ButtonType(iUse);

    TBool addToButtonGroupStack = EFalse;
    
    EikButtonGroupFactory::TCreationData creationData(
        iUse,
        this,
        aResourceId,
        aParentWg,
        aFlags,
        aOrientation);
        
    iButtonGroup = (MEikButtonGroup*)EikButtonGroupFactory::CreateButtonGroupByTypeL(
        buttonType,
        creationData,
        addToButtonGroupStack);
        
    __ASSERT_ALWAYS(iButtonGroup, Panic(EEikPanicButtonGroupNotFoundInFactory));
    if(addToButtonGroupStack)
        {
        CEikButtonGroupStack::AddL(*this);
        }

    SetContainerWindowL(*(iButtonGroup->AsControl()));
    SetParent( NULL );

    // __ASSERT_DEBUG(iButtonGroup==NULL...
    if (!(aFlags&EDelayActivation))
        {
        ActivateL();
        }
    }

/**
 * Sets the text, bitmaps and command ids specified at aResourceId into the buttons.
 *
 * @since ER5U 
 */
EXPORT_C void CEikButtonGroupContainer::SetCommandSetL(TInt aResourceId)
    {
    iButtonGroup->SetCommandSetL(aResourceId);
    }

/**
 * As with SetCommandL but allows the previous command to be retrieved at 
 * any time by calling RemoveCommand.  Panics if aPosition is out of range.
 *
 * @since ER5U 
 */
EXPORT_C void CEikButtonGroupContainer::AddCommandSetToStackL(TInt aResourceId)
    {
    iButtonGroup->AddCommandSetToStackL(aResourceId);
    }

EXPORT_C void CEikButtonGroupContainer::DoSetCommandL(
    TInt aPosition,
    TInt aCommandId,
    const TDesC* aText,
    const CFbsBitmap* aBitmap,
    const CFbsBitmap* aMask,
    TCommandOp aOp)
    {
    TPtrC text;
    if (aText)
        {
        text.Set(*aText);
        }
    else
        {
        text.Set(KNullDesC);
        }
    
    switch (aOp)
        {
        case ESet:
            iButtonGroup->SetCommandL(aPosition, aCommandId, &text, aBitmap, aMask);
            break;
        case EAdd:
            iButtonGroup->AddCommandL(aPosition, aCommandId, &text, aBitmap, aMask);
            break;
        case EPush:
            // slightly wasteful - could check whether extra slot is required first        
            iCommandsCleanup->AppendL(TCmdPos()); 
            iButtonGroup->AddCommandToStackL(aPosition, aCommandId, &text, aBitmap, aMask);
            break;
        }
    }

EXPORT_C void CEikButtonGroupContainer::DoSetCommandL(
    TInt aPosition,
    TInt aCommandId,
    const TDesC* aText,
    const TDesC& aFile,
    TInt aBitmapId,
    TInt aMaskId,
    TCommandOp aOp)
    {
    CFbsBitmap* bitmap = AknIconUtils::CreateIconL(aFile, aBitmapId);
    CleanupStack::PushL(bitmap);
    CFbsBitmap* mask = AknIconUtils::CreateIconL(aFile, aMaskId);
    CleanupStack::PushL(mask);
    DoSetCommandL(aPosition, aCommandId, aText, bitmap, mask, aOp);
    CleanupStack::Pop(2); // bitmap, mask
    }

EXPORT_C void CEikButtonGroupContainer::DoSetCommandL(
    TInt aCommandId,
    const TDesC* aText,
    const CFbsBitmap* aBitmap,
    const CFbsBitmap* aMask,
    TCommandOp aOp)
    {
    const TInt pos = PositionById(aCommandId);
    if (pos == KErrNotFound)
        {
        User::LeaveIfError(KErrNotFound);
        }
    DoSetCommandL(pos, aCommandId, aText, aBitmap, aMask, aOp);
    }

EXPORT_C void CEikButtonGroupContainer::DoSetCommandL(
    TInt aCommandId,
    const TDesC* aText,
    const TDesC& aFile,
    TInt aBitmapId,
    TInt aMaskId,
    TCommandOp aOp)
    {
    const TInt pos = PositionById(aCommandId);
    if (pos == KErrNotFound)
        {
        User::LeaveIfError(KErrNotFound);
        }
    DoSetCommandL(pos, aCommandId, aText, aFile, aBitmapId, aMaskId, aOp);
    }

EXPORT_C void CEikButtonGroupContainer::DoSetCommandL(
    TInt aPosition, 
    TInt aResourceId, 
    TCommandOp aOp)
    {
    switch(aOp)
        {
        case ESet:
            iButtonGroup->SetCommandL(aPosition, aResourceId);
            break;
        case EAdd:
            User::Leave(KErrNotSupported);
            break;
        case EPush:
            iButtonGroup->AddCommandToStackL(aPosition, aResourceId);
            break;
        };
    }

/**
 * Returns the location of the button group. Typically the button group is external to the view 
 * which is using it. In some cases, such as in dialogs with button panels, the button group is 
 * internal to the control which is using it.
 */
EXPORT_C CEikButtonGroupContainer::TLocation CEikButtonGroupContainer::Location() const
    {
    return CEikButtonGroupContainer::TLocation (LafButtonGroupContainer::Location(iUse));
    }

/**
 * Returns the command button given by aCommandId.
 *
 * @since App-Framework_6.1 
 */
EXPORT_C CEikCommandButton* CEikButtonGroupContainer::CommandButtonOrNull(TInt aCommandId) const
    {
    return iButtonGroup->GroupControlAsButton(aCommandId);
    }

/**
 * Sets the boundary rectangle to aRect. The button group attaches itself to the inside of this 
 * rectangle.
 */
EXPORT_C void CEikButtonGroupContainer::SetBoundingRect(const TRect& aRect)
    {
    iButtonGroup->SetBoundingRect(aRect);
    UpdateRect();
    }

/**
 * Subtracts the area occupied by the button group from aBoundingRect. This method should 
 * be used in preference to querying the container's area at all times.
 */
EXPORT_C void CEikButtonGroupContainer::ReduceRect(TRect& aBoundingRect) const
    {
    iButtonGroup->ReduceRect(aBoundingRect);
    CONST_CAST(CEikButtonGroupContainer*, this)->UpdateRect();
    }

void CEikButtonGroupContainer::UpdateRect()
    {
    CCoeControl* ctrl = ButtonGroupAsControl();
    const TRect rect = ctrl->Rect();
    // TP: PositionRelativeToScreen() causes unnecessary Flush(). Thus it cannot be used.
    iPosition = rect.iTl;
    
    TRect screenRect = iAvkonAppUi->ApplicationRect();
    
#ifdef RD_SCALABLE_UI_V2
    // ctrl position and size should be right
    iPosition = ctrl->Position();
    iSize = ctrl->Size();
#else // RD_SCALABLE_UI_V2
    // For safety, still use the old code in portrait mode
    if (screenRect.Width() < screenRect.Height())
        {
        TAknWindowLineLayout layout(AKN_LAYOUT_WINDOW_control_pane(TSize(screenRect.Size())));
        TAknLayoutRect layoutRect;
        layoutRect.LayoutRect(screenRect, layout);
        iPosition.iY += screenRect.Height() - layoutRect.Rect().Height();
        iSize = rect.Size();
        }
    else
        {
        iPosition = ctrl->Position();
        iSize = ctrl->Size();
        }
#endif // RD_SCALABLE_UI_V2
    }


/**
 * Returns a pointer to the control with id aCommandId. This method is intended to allow access
 * to standard CCoeControl functionality only. Casting the return value is likely to fail on
 * different devices.
 */
EXPORT_C CCoeControl* CEikButtonGroupContainer::ControlOrNull(TInt aCommandId) const
    {
    return iButtonGroup->GroupControlById(aCommandId);
    }

/**
 * Returns a pointer to the button with id aCommandId. May return NULL on some devices.
 */
EXPORT_C CEikCommandButton* CEikButtonGroupContainer::ButtonById(TInt aCommandId) const
    {
    return iButtonGroup->GroupControlAsButton(aCommandId);
    }
    
/**
 * Returns the position in the group of the command identified by aCommandId. The return value is 
 * undefined if two buttons share the same id.
 */
EXPORT_C TInt CEikButtonGroupContainer::PositionById(TInt aCommandId) const
    {
    return iButtonGroup->CommandPos(aCommandId);
    }

/**
 * Changes the hotkey association for the command identified by aCommandId to the hot key flags 
 * aFlags and the key id aKeyId. Only supported for dialogs.
 */
EXPORT_C void CEikButtonGroupContainer::UpdateHotKey(
    TInt aCommandId, 
    THotKeyFlags aFlags, 
    TInt aKeyId)
    {
    if (!(iUse == EDialog || iUse == EDialogButtons))
        {
        return;
        }
    TRAP_IGNORE(STATIC_CAST(CEikButtonPanel*, ButtonGroupAsControl())->UpdateHotKeyL(
        aCommandId, (CEikLabeledButton::TFlags)aFlags, aKeyId));
    }

/**
 * Temporarily change the command observer for the button at aPos to aCommandObserver.
 * Panics if an updated observer is already present.
 */
EXPORT_C void CEikButtonGroupContainer::UpdateCommandObserverL(
    TInt aPos, 
    MEikCommandObserver& aCommandObserver)
    {
    if (!iObserverArray)
        {
        iObserverArray = new(ELeave) CCmdObserverArray();
        }
    else
        {
        __ASSERT_ALWAYS(iObserverArray->FindIndex(aPos) == KErrNotFound, 
            Panic(EEikPanicButtonGroupDuplicateObserver));
        }
    TCmdObserver obs(aPos,aCommandObserver);
    iObserverArray->AppendL(obs);
    }
    
EXPORT_C TBool CEikButtonGroupContainer::UpdatedCommandObserverExists(
    TCommandPosition aPosition) const
    {
    if ( !iObserverArray )
        {
        return EFalse;
        }
    const TInt pos = iObserverArray->FindIndex( aPosition );
    if ( pos != KErrNotFound )
        {
        return ETrue;
        }
    return EFalse; // no command observer found
    }

void CEikButtonGroupContainer::UpdateMSKCommandObserver(
    CEikListBox* aMSKObserverOwner,
    MEikCommandObserver* aCommandObserver)
    {
    // badly coded applications may call this method for different listboxes
    // e.g. by activating more than one listbox for one view and never unfocusing them.
    // If this happens, the first MSK observer set will be used and other observers will
    // be discarded.
    if (iMSKObserverOwner && iMSKObserverOwner != aMSKObserverOwner && aCommandObserver)
        {
        // this will prevent listbox from calling already deleted buttongroup
        aMSKObserverOwner->InformMSKButtonGroupDeletion();
        return;
        }
    
    if (aCommandObserver == NULL && iMSKObserverOwner == aMSKObserverOwner)
        {
        iMSKObserverOwner = NULL;
        }
    else
        {
        iMSKObserverOwner = aMSKObserverOwner;
        }
        
    if (iButtonGroup)
        {
        iButtonGroup->SetMSKCommandObserver(aCommandObserver);    
        }
    }
    
/**
 * Remove the temporary observer for the command at aPos.
 */
EXPORT_C void CEikButtonGroupContainer::RemoveCommandObserver(TInt aPos)
    {
    if ( iValid != KIsValid )
        {
        return;
        }
    const TInt pos = ( iObserverArray? iObserverArray->FindIndex(aPos) : KErrNotFound );
    if (pos != KErrNotFound)
        {
        iObserverArray->Delete(pos);
        if (iObserverArray->Count() == 0)
            {
            delete iObserverArray;
            iObserverArray = NULL;
            }
        }
    }

/**
 * Has the button group been explicitly instructed to suppress redraws
 */
EXPORT_C TBool CEikButtonGroupContainer::DelayActivation() const
    {
    TUint flags = iButtonGroup->ButtonGroupFlags();
    return (flags&EDelayActivation);
    }

EXPORT_C TKeyResponse CEikButtonGroupContainer::OfferKeyEventL(
    const TKeyEvent& aKeyEvent, 
    TEventCode aType)
    {
    return ButtonGroupAsControl()->OfferKeyEventL(aKeyEvent,aType);
    }

void CEikButtonGroupContainer::MakeVisible(TBool aVisible)
    {
    ButtonGroupAsControl()->MakeVisible(aVisible);
    CCoeControl::MakeVisible(aVisible);
    }

TInt CEikButtonGroupContainer::CountComponentControls() const
    {
    return 1;
    }

CCoeControl* CEikButtonGroupContainer::ComponentControl(TInt aIndex) const
    {
    if (aIndex == 0)
        {
        return ButtonGroupAsControl();
        }
    return NULL;
    }

void CEikButtonGroupContainer::SizeChanged()
    {
    TRect rect(Rect());
    // subtract any margins
    ButtonGroupAsControl()->SetRect(rect);
    }

void CEikButtonGroupContainer::ProcessCommandL(TInt aCommandId)
    {
    // check for different observer
    const TInt cmdPos = PositionById(aCommandId);
    const TInt pos = (iObserverArray ? iObserverArray->FindIndex(cmdPos) : KErrNotFound);
    if (pos != KErrNotFound)
        {
        (*iObserverArray)[pos].iObserver.ProcessCommandL(aCommandId);
        }
    else // otherwise, pass event on to standard observer
        {
        iCommandObserver->ProcessCommandL(aCommandId);
        }
    }

CCoeControl* CEikButtonGroupContainer::CreateCustomCommandControlL(TInt aControlType)
    {
    CCoeControl* ctrl = NULL;
    if (iCommandObserver)
        {
        ctrl = iCommandObserver->CreateCustomCommandControlL(aControlType);
        }
    return ctrl;
    }

EXPORT_C void CEikButtonGroupContainer::Reserved_MtsmPosition()
    {
    }

EXPORT_C void CEikButtonGroupContainer::Reserved_MtsmObject()
    {
    }
    
#ifndef RD_ENHANCED_CBA
EXPORT_C void CEikButtonGroupContainer::OfferCommandListL(const RArray<TInt>& /*aCommandList*/)
    {
#else // RD_ENHANCED_CBA
EXPORT_C void CEikButtonGroupContainer::OfferCommandListL(const RArray<TInt>& aCommandList)
    {
    static_cast<MEikEnhancedButtonGroup*>(iButtonGroup)->OfferCommandListL( aCommandList );
#endif  
    }

#ifndef RD_ENHANCED_CBA
EXPORT_C void CEikButtonGroupContainer::OfferCommandListL(const TInt /*aResourceId*/)
    {
#else // RD_ENHANCED_CBA    
EXPORT_C void CEikButtonGroupContainer::OfferCommandListL(const TInt aResourceId)
    {
    static_cast<MEikEnhancedButtonGroup*>(iButtonGroup)->OfferCommandListL( aResourceId );
#endif
    }
    
#ifdef RD_ENHANCED_CBA  
EXPORT_C TBool CEikButtonGroupContainer::IsCommandInGroup(const TInt aCommandId) const
    {
    return static_cast<MEikEnhancedButtonGroup*>(iButtonGroup)->IsCommandInGroup( aCommandId );
    }
#else
EXPORT_C TBool CEikButtonGroupContainer::IsCommandInGroup(const TInt /*aCommandId*/) const
    {
    return EFalse;
    }
#endif      

    
#ifndef RD_ENHANCED_CBA
EXPORT_C void CEikButtonGroupContainer::ReplaceCommand(
    const TInt /*aCommandId*/, 
    const TInt /*aResourceId*/)
    {
#else //  RD_ENHANCED_CBA
EXPORT_C void CEikButtonGroupContainer::ReplaceCommand(
    const TInt aCommandId, 
    const TInt aResourceId )
    {
    static_cast<MEikEnhancedButtonGroup*>(iButtonGroup)->ReplaceCommand( aCommandId, aResourceId );
#endif  
    }


/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 *
 * @internal
 * @since App-Framework_6.1
 */
#ifndef _DEBUG
EXPORT_C void CEikButtonGroupContainer::WriteInternalStateL(RWriteStream&) const
    {
    }
#else
EXPORT_C void CEikButtonGroupContainer::WriteInternalStateL(RWriteStream& aWriteStream) const
    {
    _LIT(KEikLitBtgrpcCtlSt, "<CEikButtonGroupContainer>");
    _LIT(KEikLitBtgrpcCtlEnd, "<\\CEikButtonGroupContainer>");
    _LIT(KEikLitBtgrpcCtlBtGrp, "<iButtonGroup>");
    _LIT(KEikLitBtgrpcCtlBtGrpEnd, "<\\iButtonGroup>");
    _LIT(KEikLitBtgrpcCtlUse, "<iUse>");
    _LIT(KEikLitBtgrpcCtlUseEnd, "<\\iUse>");
    _LIT(KEikLitBtgrpcCtlCleanup, "<iCommandsCleanup>");
    _LIT(KEikLitBtgrpcCtlCleanupEnd, "<\\iCommandsCleanup>");
    _LIT(KEikLitBtgrpcCtlObs, "<iCommandObserver>");
    _LIT(KEikLitBtgrpcCtlObsEnd, "<\\iCommandObserver>");
    _LIT(KEikLitBtgrpcCtlObsArray, "<iObserverArray>");
    _LIT(KEikLitBtgrpcCtlObsArrayEnd, "<\\iObserverArray>");
    _LIT(KEikLitBtgrpcCtlQLnk, "<iBtLink>");
    _LIT(KEikLitBtgrpcCtlQLnkEnd, "<\\iBtLink>");

    aWriteStream << KEikLitBtgrpcCtlSt;
    aWriteStream << KEikLitBtgrpcCtlBtGrp;
    aWriteStream.WriteInt32L((TInt)iButtonGroup);
    aWriteStream << KEikLitBtgrpcCtlBtGrpEnd;
    aWriteStream << KEikLitBtgrpcCtlUse;
    aWriteStream.WriteInt32L((TInt)iUse);
    aWriteStream << KEikLitBtgrpcCtlUseEnd;

    aWriteStream << KEikLitBtgrpcCtlCleanup;
    const TInt cmdCount = (iCommandsCleanup ? iCommandsCleanup->Count() : 0);
    for(TInt i = 0; i < cmdCount; i++)
        {
        TCmdPos& pos=(*iCommandsCleanup)[i];
        aWriteStream.WriteInt32L(pos.iCmd);
        aWriteStream.WriteInt32L(pos.iPos);
        }
    aWriteStream << KEikLitBtgrpcCtlCleanupEnd;
    aWriteStream << KEikLitBtgrpcCtlObs;
    aWriteStream.WriteInt32L((TInt)iCommandObserver);
    aWriteStream << KEikLitBtgrpcCtlObsEnd;

    aWriteStream << KEikLitBtgrpcCtlObsArray;
    const TInt obsCount = (iObserverArray ? iObserverArray->Count() :0);
    for(TInt j = 0; j < obsCount; j++)
        {
        TCmdObserver& obs = (*iObserverArray)[j];
        aWriteStream.WriteInt32L((TInt)&(obs.iObserver));
        aWriteStream.WriteInt32L(obs.iPos);
        }
    aWriteStream << KEikLitBtgrpcCtlObsArrayEnd;
    aWriteStream << KEikLitBtgrpcCtlQLnk;
    aWriteStream.WriteInt32L((TInt)iBtLink.iPrev);
    aWriteStream.WriteInt32L((TInt)iBtLink.iNext);
    aWriteStream << KEikLitBtgrpcCtlQLnkEnd;
    CCoeControl::WriteInternalStateL(aWriteStream);
    aWriteStream << KEikLitBtgrpcCtlEnd;
    }
#endif
