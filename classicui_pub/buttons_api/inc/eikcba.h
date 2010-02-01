/*
* Copyright (c) 2002-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  EIKON control button array and cba button class definitions.
*
*/


#ifndef __EIKCBA_H__
#define __EIKCBA_H__

#include <eikctgrp.h>
#include <badesca.h>
#include <eikbtgrp.h>
#include <eiksbobs.h>
#include <eiksbfrm.h>

#include <eikimage.h>
#include <AknControl.h>
#include <AknsItemData.h> // TAknsItemID
#include <babitflags.h>   // TBitFlags

class CEikLabel;
class CEikCbaButton;
class CCoeBrushAndPenContext;
class MEikCommandObserver;
class TCoeColorUse;

class CAknScrollBar;
class TEikScrollBarModel;

class CEikEnhancedCbaButton;
class CEikCommandTable;

class CAknsBasicBackgroundControlContext;
class CAknsLayeredBackgroundControlContext;
class CAknsMaskedLayerBackgroundControlContext;
class CEikCbaExtension;

const TInt KMaxCbaLabelLength = 32;
const TInt KMaxButtonsInCommandTable = 4;

/**
 * Defines a Control Button Array control, used in Avkon to define the softkeys in the
 * control pane.
 *
 * @lib eikcoctl.lib
 * @since S60 0.9  
 */
NONSHARABLE_CLASS(CEikCba) :
    public CEikControlGroup, 
    public MEikEnhancedButtonGroup, 
    public MEikScrollBarObserver,
    public MCoeControlObserver
    {
public: 
    /** 
     * Declares an object type for a class, in order to allow the object
     * provider mechanism to locate and provide objects from the class.
     */
    DECLARE_TYPE_ID(0x101F4105)

    /**
     * Creates a new control button array.
     *
     * @internal
     * @param aPrevious Previous Cba, used in MinimumSize().
     * @param aCommandObserver Command observer for softkey events.
     * @param aParentWg The parent window group.
     * @return Control button array object.
     */
    static CEikCba* NewL(
        const CEikCba* aPrevious, 
        MEikCommandObserver* aCommandObserver, 
        RWindowGroup* aParentWg);
        
    /**
     * Creates a new control button array.
     *
     * @internal
     * @param aResourceId A resource describing the Cba.
     * @param aPrevious Previous Cba, used in MinimumSize().
     * @param aCommandObserver Command observer for softkey events.
     * @param aParentWg The parent window group.
     * @return Control button array object.
     */        
    static CEikCba* NewL(
        TInt aResourceId,
        const CEikCba* aPrevious,
        MEikCommandObserver* aCommandObserver,
        RWindowGroup* aParentWg);
        
    /**
     * Creates a new control button array.
     *
     * @internal
     * @param aPrevious Previous Cba, used in MinimumSize().
     * @param aCommandObserver Command observer for softkey events.
     * @param aParentWg The parent window group.
     * @return Control button array object.
     */        
    static CEikCba* NewLC(
        const CEikCba* aPrevious,
        MEikCommandObserver* aCommandObserver,
        RWindowGroup* aParentWg);

    /**
     * Creates a new control button array
     *
     * @since S60 5.2
     * @internal
     * @param aPrevious Previous Cba, used in MinimumSize()
     * @param aCommandObserver Command observer for softkey events
     * @param aParentWg The parent window group
     * @param aFlags CEikButtonGroupContainer::EIsEmbedded if CBA is embedded
     *               inside another control (popup/dialog/setting page)
     * @return Control button array object
     */        
    static CEikCba* NewLC(
        const CEikCba* aPrevious,
        MEikCommandObserver* aCommandObserver,
        RWindowGroup* aParentWg, TUint aFlags );
        
    /**
     * Creates a new control button array.
     *
     * @internal
     * @param aResourceId A resource describing the Cba.
     * @param aPrevious Previous Cba, used in MinimumSize().
     * @param aCommandObserver Command observer for softkey events.
     * @param aParentWg The parent window group.
     * @return Control button array object.
     */         
    static CEikCba* NewLC(
        TInt aResourceId,
        const CEikCba* aPrevious,
        MEikCommandObserver* aCommandObserver,
        RWindowGroup* aParentWg);

    /**
     * Creates a new control button array
     *
     * @since S60 5.2
     * @internal
     * @param aResourceId A resource describing the Cba
     * @param aPrevious Previous Cba, used in MinimumSize()
     * @param aCommandObserver Command observer for softkey events
     * @param aParentWg The parent window group
     * @param aFlags CEikButtonGroupContainer::EIsEmbedded if CBA is embedded
     *               inside another control (popup/dialog/setting page)
     * @return Control button array object
     */         
    static CEikCba* NewLC(
        TInt aResourceId,
        const CEikCba* aPrevious,
        MEikCommandObserver* aCommandObserver,
        RWindowGroup* aParentWg, TUint aFlags );
        
    /**
     * Destructor.
     */        
    ~CEikCba();

public: // new methods
    /**
     * Gets the maximum number of buttons that can be supported by the device.
     *
     * @internal
     * @return The number of command buttons supported.
     */
    TInt MaxCommands() const;
    
    /**
     * Updates the cba labels.
     *
     * @internal
     * @param aScrollerOn If this is set, the short labels are used instead 
     *                    of the long ones. To be used if there is an (old style) 
     *                    scroller between the softkeys.     
     */    
    void UpdateCbaLabels(TBool aScrollerOn);
    
    /**
     * For checking whether the middle softkey is supported in the platform.
     * 
     * @internal
     * @return ETrue if the middle softkey is supported in the plaftorm.
     */
    TInt MSKEnabledInPlatform() const;

    /** 
     * Sets the scroll bar frame observer.
     * 
     * @internal
     * @param aObserver The scroll bar frame observer.
     */ 
    void SetSBFrameObserver(MEikScrollBarObserver* aObserver);

    /** 
     * Sets the scroll bar model.
     *
     * @internal
     * @param aModel The scroll bar model.
     */ 
    void SetScrollBarModelL(TEikScrollBarModel* aModel);
    
    /** 
     * Returns the scroll bar frame.
     *
     * @internal
     * @return The scroll bar frame.
     */ 
    const CEikCbaScrollBarFrame* ScrollBarFrame() const;
    
    /** 
     * Returns the vertical scroll bar as a control.
     *
     * @internal The vertical scroll bar as a control
     */
    CAknScrollBar* VScrollBarAsControl();

    /** 
     * Replaces empty scroll bar with actual arrow head scroll bar.
     *
     * @internal
     * @since S60 3.0
     */    
    void CreateArrowHeadScrollBarL(); 

     /** 
     * For external set the MSK icon
     * Returns ETrue if option is ok, EFalse is not.
     * @param aId icon bitmap IID
     * @param aBmpFile file path.
     * @param aBmp Bitmap ID.
     * @param aBmpM Bitmap mask ID.
     * @param aEnable ETrue for set icon, EFalse for use default icon.
     */
    IMPORT_C TBool UpdateMSKIconL( 
        const TAknsItemID& aId,
        const TDesC& aBmpFile,
        const TInt32 aBmp,
        const TInt32 aBmpM,
        TBool aEnable);

    /**
     * Enables or disables item specific softkey. If enabled then SK1's 
     * visibility is determined by the screen content. If there's a list or 
     * grid with visible highlight (i.e. highlight is brought visible via 
     * hardware keys) on the display or SK1's associated command is 
     * @c EAknSoftkeyOptions then SK1 is visible, otherwise it's hidden. This
     * method has no effect if the the application isn't single click enabled. 
     * Item specific softkey is enabled by default.
     *
     * @since S60 5.2
     *
     * @param aEnable ETrue to enable item specific softkey, EFalse to disable.
     */
     IMPORT_C void EnableItemSpecificSoftkey( TBool aEnable );

public:
    /**
     * From CEikControlGroup.
     * Adds a wrapped control to the control group array at the given index position.
     * Overridden to prevent setting container window.
     * 
     * @param aGroupControl The control to add to the group.
     * @param aIndex The index for the added control.
     */
    void InsertControlL(TEikGroupControl& aGroupControl, TInt aIndex);

    /**
     * From MEikButtonGroup.
     * Sets a command button's text and command ID. Note that this implementation does 
     * not support bitmap and mask.
     *
     * @param aPosition The position within the button group of the button to change. 
     * @param aCommandId Command ID the button will send.
     * @param aText The text for the button.     
     * @param aBitmap Not used.
     * @param aMask Not used.
     */     
    void SetCommandL(
        TInt aPosition,
        TInt aCommandId,
        const TDesC* aText,
        const CFbsBitmap* aBitmap,
        const CFbsBitmap* aMask);
        
    /**
     * From MEikButtonGroup.
     * Sets a command button's text label and command ID. The text and command ID are all 
     * read from resource. Note that this implementation does not support bitmap and mask.
     *
     * @internal     
     *
     * @param aPosition The position within the button group of the button to change.
     * @param aResourceId Resource ID specifying the text and command ID.
     *
     */        
    void SetCommandL(TInt aPosition, TInt aResourceId);
    
    /**
     * From MEikButtonGroup.
     * Initialises the group of command buttons from a resource.
     * Note that this implementation does not support bitmap and mask.
     *
     * @internal     
     *
     * @param aResourceId ID of the resource structure specifying the command buttons.     
     */    
    void SetCommandSetL(TInt aResourceId);

    /**
     * From MEikButtonGroup.
     * Not supported.
     *
     * @internal     
     *
     * @param aPosition Not used.
     * @param aCommandId Not used.
     * @param aText Not used.
     * @param aBitmap Not used.
     * @param aMask Not used.
     * @leave KErrNotSupported If called.
     */    
    void AddCommandL(
        TInt aPosition,
        TInt aCommandId,
        const TDesC* aText,
        const CFbsBitmap* aBitmap,
        const CFbsBitmap* aMask);
       
    /**
     * From MEikButtonGroup.
     * Pushes a command button with text and a command ID onto a position's button stack.
     * Note that this implementation does not support bitmap and mask.
     *
     * @internal     
     *
     * @param aPosition The position in the button group at which to add the command button.
     * @param aCommandId Command ID the button will send.
     * @param aText Text for the button.
     * @param aBitmap Not used.
     * @param aMask Not used.
     */        
    void AddCommandToStackL(
        TInt aPosition,
        TInt aCommandId,
        const TDesC* aText,
        const CFbsBitmap* aBitmap,
        const CFbsBitmap* aMask);
       
    /**
     * From MEikButtonGroup.
     * Pushes a command button onto a position's button stack. The text and command ID are all 
     * read from resource. Note that this implementation does not support bitmap and mask.
     *
     * @internal     
     *
     * @param aPosition The position in the button group at which to push the command button.
     * @param aResourceId ID of a resource specifying the text and command ID.
     */        
    void AddCommandToStackL(TInt aPosition, TInt aResourceId);
    
    /**
     * From MEikButtonGroup.
     * As with SetCommandL() but for a set of buttons, also allows the previous command button 
     * to be retrieved by calling RemoveCommand(). Note that this implementation does not 
     * support bitmap and mask.
     *
     * @internal     
     *
     * @param aResourceId Resource describing the set of command buttons.
     */    
    void AddCommandSetToStackL(TInt aResourceId);
    
    /**
     * From MEikButtonGroup.
     * Not supported.
     *
     * @internal     
     * 
     * @param aCommandId Not used.
     */    
    void SetDefaultCommand(TInt aCommandId);
    
    /**
     * From MEikButtonGroup.
     * Calculates minimum size required to display the buttons defined in the 
     * specified resource structure.
     *
     * @internal     
     *
     * @param aResourceId The ID of the resource structure describing the button group.
     * @return Minimum size required to display the button group defined in the specified 
     *         resource structure.     
     */    
    TSize CalcMinimumSizeL(TInt aResourceId);
    
    /**
     * From MEikButtonGroup.
     * Removes the command identified by aCommandId, in position aPosition in the 
     * group, from the command stack. Automatically retrieves the previous command 
     * details. Commands are added to the stack by calling AddCommandToStackL.
     *
     * @internal     
     *
     * @param aPosition The position in the button group from which to remove the 
     *                  command button.
     * @param aCommandId Command ID.     
     */    
    void RemoveCommandFromStack(TInt aPosition, TInt aCommandId);
    
    /**
     * From MEikButtonGroup.
     * Returns the command position by command id.
     *
     * @internal     
     *
     * @param aCommandId The button's command id.
     * @return The command position in the button group.     
     */    
    TInt CommandPos(TInt aCommandId) const;

    /**
     * From MEikButtonGroup.
     * Dims or undims a button without drawing it. 
     *
     * @internal     
     *
     * @param aCommandId Command ID of the button to change.
     * @param aDimmed ETrue to dim the specified command. EFalse to undim the specified command.
     */
    void DimCommand(TInt aCommandId, TBool aDimmed);
    
    /**
     * From MEikButtonGroup.
     * Determines whether the button with the specified command ID is dimmed. 
     *
     * @internal     
     *
     * @param aCommandId The command ID.
     * @return ETrue if the specified command is dimmed. EFalse if the specified command is 
     *               not dimmed.
     */    
    TBool IsCommandDimmed(TInt aCommandId) const;
    
    /**
     * From MEikButtonGroup.
     * Makes the button with the specified id either visible, or invisible. 
     *
     * @internal     
     *
     * @param aCommandId Specifies the button to alter.

     * @param aVisible ETrue to make the specified button visible. EFalse to make the specified
     *                 button invisible.     
     */    
    void MakeCommandVisible(TInt aCommandId, TBool aVisible);

    /**
     * From MEikButtonGroup.
     * Tests whether the button with the specified command ID is visible.
     *
     * @internal     
     *
     * @param aCommandId Specifies the button.
     * @return ETrue if the specified button is visible. EFalse if the specified button is 
     *               not visible.
     */    
    TBool IsCommandVisible(TInt aCommandId) const;
    
    /**
     * From MEikButtonGroup.
     * Not supported.
     *
     * @internal     
     *
     * @param aCommandId Not used.
     */    
    void AnimateCommand(TInt aCommandId);

    /**
     * From MEikButtonGroup.
     * Returns the button group as a control.
     *
     * @internal     
     *
     * @return The button group as a control.
     */    
    CCoeControl* AsControl();
    
    /**
     * From MEikButtonGroup.
     * Returns the button group as a control.
     *
     * @internal     
     *
     * @return The button group as a control.
     */    
    const CCoeControl* AsControl() const;
    
    /**
     * From MEikButtonGroup.
     * Sets the boundary rectangle for externally-positioned button groups. 
     * For use by EExternal button groups only.
     *
     * @internal     
     *
     * @param aBoundingRect Not used.
     */    
    void SetBoundingRect(const TRect& aBoundingRect);
    
    /**
     * From MEikButtonGroup.
     * Subtracts the area occupied by the button group from the specified bounding rectangle.
     * This method should be used in preference to querying the container's area at all times.
     * For use by EExternal button groups only.
     *
     * @internal     
     *
     * @param aBoundingRect Rectangle to be modified.
     */    
    void ReduceRect(TRect& aBoundingRect) const;
    
    /**
     * Returns a group control (a button) as a control.
     *
     * @internal
     *
     * @param aCommandId The button's command id.
     * @return The group control as a control.
     */
    CCoeControl* GroupControlById(TInt aCommandId);

    /**
     * From MEikButtonGroup.
     * Returns a group control (a button) as a control.
     *
     * @internal     
     *
     * @param aCommandId The button's command id.
     * @return The group control as a control.
     */    
    CCoeControl* GroupControlById(TInt aCommandId) const;
    
    /**
     * From MEikButtonGroup.
     * Returns the command id by position.
     *
     * @internal     
     *
     * @param aCommandPos The command's position.
     * @return The command id.
     */    
    TInt CommandId(TInt aCommandPos) const;
    
    /**
     * From MEikButtonGroup.
     * Gets the total number of buttons currently present in the group.
     *
     * @internal     
     *
     * @return The number of buttons.
     */
    TInt ButtonCount() const;
    
    /**
     * Removes previous command.
     * 
     * @internal
     *
     * @param aPosition The command's position.
     */
    void RemovePreviousCommand(TInt aPosition);

    /**
     * From MEikButtonGroup.
     * Not supported, because it is not possible to convert a CBA button to a 
     * CEikCommandButton. Calling this in debug build causes a panic, otherwise
     * NULL is just returned.
     *
     * @internal     
     * 
     * @param aCommandId Not used.
     */
    CEikCommandButton* GroupControlAsButton(TInt aCommandId) const;
    
    /**
     * From MEikButtonGroup.
     * Gets the button group flags.
     *
     * @internal     
     *
     * @return The button group flags.
     */
    TUint ButtonGroupFlags() const;
    
    /**
     * Sets the button group flags.
     *
     * @internal     
     *
     * @param aFlags The button group flags.
     */
    IMPORT_C void SetButtonGroupFlags(TInt aFlags);

    /**
     * Sets the skin background for this control button array. The new background is used 
     * for all the subsequent drawing operations. This method does not itself cause a repaint.
     *
     * @internal     
     *
     * @param aIID Skin item ID of the new background. This is one of the constants
     *             defined in AknsConstants.h, and the usual values are KAknsIIDQsnBgAreaControl, 
     *             KAknsIIDQsnBgAreaControlPopup, and KAknsIIDQsnBgAreaControlIdle.
     * @since S60 2.0
     */
    IMPORT_C void SetSkinBackgroundId(const TAknsItemID& aIID);

    /**
     * Sets the middle softkey icon.
     *
     * @internal
     *
     * @since S60 3.1
     */
    void SetMSKIconL();
    
    /**
     * From MEikButtonGroup.
     * Sets the middle softkey command observer.
     *
     * @internal     
     * 
     * @param aCommandObserver The middle softkey command observer.
     * @since S60 3.1
     */
    void SetMSKCommandObserver(MEikCommandObserver* aCommandObserver);
    
    /**
     * From MEikButtonGroup.
     * Dims (but doesn't draw) the button with position aPosition.
     *
     * @internal     
     *
     * @param aPosition The position for command to be dimmed.
     * @param aDimmed ETrue for dimming.
     */    
    void DimCommandByPosition(TInt aPosition, TBool aDimmed);
    
    /**
     * From MEikButtonGroup.
     * Returns ETrue if the button with position aPosition is dimmed.
     *
     * @internal     
     *
     * @param aPosition The position for command to be checked.
     * @return The state of the button.    
     */    
    TBool IsCommandDimmedByPosition(TInt aPosition) const;
    
    /**
     * From MEikButtonGroup.
     * Sets the the button with position aPosition to be visible if aVisible is ETrue.
     *
     * @internal     
     *
     * @param aPosition The position for command to be made visible.
     * @param aVisible EFalse for making button invisible.
     */    
    void MakeCommandVisibleByPosition(TInt aPosition, TBool aVisible);

    /**
     * From MEikButtonGroup.
     * Returns ETrue if the button with position aPosition is visible.
     *
     * @internal     
     *
     * @param aPosition The position for command to be checked.
     * @return The state of the button.  
     */    
    TBool IsCommandVisibleByPosition(TInt aPosition) const;
    
    /**
     * From MEikButtonGroup.
     * Not supported.
     *
     * @internal     
     * 
     * @param aPosition Not used.
     */    
    void AnimateCommandByPosition(TInt aPosition);
    
    /**
     * Returns a group control (a button) as a control.
     *
     * @internal
     *
     * @param aPosition The button's position.
     * @return The group control as a control.
     */
//    CCoeControl* GroupControlByPosition(TInt aPosition) const;

    /**
    * Gets a CBA button rectangle. This can be used in touch layouts to
    * get the whole rectangle of the CBA button, as the button areas
    * are larger than the actual button control in touch layouts.
    *
    * @param  aPosition          Position of the button.
    * @param  aRelativeToScreen  If @c ETrue, the returned rectangle
    *                            coordinates are relative to the screen
    *                            rectangle, otherwise they are relative
    *                            to the CBA area. Note that this parameter is
    *                            only taken into account in touch layouts, and
    *                            in nHD landscape mode the returned rectangle
    *                            is always relative to the screen regardless
    *                            of this parameter.
    *
    * @return Rectangle of the specified button.
    */
    TRect ButtonRectByPosition( TInt aPosition,
                                TBool aRelativeToScreen );
    
    /**
     * Enable or disable transparent rendering.
     *
     * @internal
     * @since S60 v5.0
     * @param aEnable ETrue to enable transparency,
     *                EFalse to disable.
     */
    void EnablePostingTransparency( TBool aEnable );

    /**
     * Returns TBitFlags.
     *
     * @internal
     * @since S60 v5.2
     * @return TBitFlags.
     */
    TBitFlags Flags();

    /**
     * Sets content observer.
     * 
     * @internal
     * @since S60 v5.2
     * @param aCallBack call back to notify of content changes.
     */
    void SetContentObserver( TCallBack aCallBack );

public:
    /**
     * Formerly from MTopSetMember<CEikCba>, now reserved.
     */
    virtual void Reserved_MtsmPosition();
    
    /**
     * Formerly from MTopSetMember<CEikCba>, now reserved.
     */
    virtual void Reserved_MtsmObject();

public: // from CCoeControl
    /**
     * From CCoeControl.
     * Handles key events.
     * 
     * @param aKeyEvent The key event. 
     * @param aType The type of key event: EEventKey, EEventKeyUp or EEventKeyDown. 
     * @return Indicates whether or not the key event was used by this control.
     */
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
    
    /**
     * From CCoeControl.
     * Sets the control's minimum required size.
     * 
     * @return The minimum size required by the control.
     */    
    TSize MinimumSize();
    
    /**
     * From CCoeControl.
     * Gets the list of logical colours used to draw the control.
     * The list includes an explanation of how each colour is used.
     * 
     * @param aColorUseList The colour list.
     */    
    void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
    
    /**
     * From CCoeControl.
     * Handles a change to the control's resources.
     * 
     * @param aType A message UID value. 
     */     
    void HandleResourceChange(TInt aType);
    
    /**
     * From CCoeControl.
     * Sets this control as visible or invisible.
     * 
     * @param aVisible ETrue to make the control visible, EFalse to make it invisible.
     */      
    void MakeVisible(TBool aVisible);
 
    /**
     * From CCoeControl. 
     * Handles pointer events.
     *
     * @param aPointerEvent The pointer event
     */
    void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    
    /**
    * From CCoeControl.
    * Sets the control's containing window by copying it from aContainer.
    *
    * @param aContainer The compound control that is the container for this control
    */
    void SetContainerWindowL( const CCoeControl& aContainer );
    
    void ActivateL();

public: // from MEikEnhancedButtonGroup
    /**
     * From MEikEnhancedButtonGroup.
     * Used to offer list of commands for softkeys.
     *
     * @param aCommandList A list of command ids to be offered for softkeys.
     */
    IMPORT_C void OfferCommandListL(const RArray<TInt>& aCommandList);
    
    /**
     * From MEikEnhancedButtonGroup.
     * Used to offer list of commands for softkeys.
     *
     * @param aResourceId Id for CBA resource that defines enhanced cba buttons.
     */    
    IMPORT_C void OfferCommandListL(const TInt aResourceId);
    
    /**
     * From MEikEnhancedButtonGroup.
     * Used to check if a certain command have been approved to the current command set.
     *
     * @param aCommandId The id for command which existence should be checked.
     * @return ETrue if command is in control group, otherwise EFalse.
     */    
    IMPORT_C TBool IsCommandInGroup(const TInt aCommandId) const;
    
    /**
     * From MEikEnhancedButtonGroup.
     * Replace existing command with a new command.
     *
     * @param aCommandId Id for command that should be replaced.
     * @param aResourceId Resource id for new enhanced cba button.
     */    
    IMPORT_C void ReplaceCommand(const TInt aCommandId, const TInt aResourceId);
    
public: // From MCoeControlObserver
    void HandleControlEventL( CCoeControl* aControl, TCoeEvent aEventType );

private:
    /**
     * From CAknControl
     */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

protected:
    /** 
     * From MEikScrollBarObserver
     * Handles scroll events. This function is called by the CEikScrollBar object with which 
     * this scroll bar observer object is registered. Implementations should handle scroll 
     * events appropriately.
     *
     * @param aScrollBar Pointer to the originating scroll bar object.
     * @param aEventType A scroll event. 
     */
    virtual void HandleScrollEventL(CEikScrollBar* aScrollBar, TEikScrollEvent aEventType);

    /**
     * From CCoeControl
     * Retrieves an object of the same type as that encapsulated in aId.
     * This function is used to allow controls to ask their owners for access to other 
     * objects that they own.
     * 
     * @param aId An encapsulated object type ID.
     * @return Encapsulates the pointer to the object provided. Note that the encapsulated 
     * pointer may be NULL. 
     */
    TTypeUid::Ptr MopSupplyObject(TTypeUid aId);

    /**
     * From CCoeControl.
     * Draws the control.
     * 
     * @param aRect Rectangle to draw on.
     */    
    void Draw(const TRect& aRect) const;

public:

    /**
     * Checks if the CBA contains no commands.
     * Note that this returns always @c EFalse if the CBA belongs
     * to a full screen query.
     *
     * @internal
     *
     * @return  @c ETrue if the CBA buttons are empty, @c EFalse otherwise.
     *
     * @since 5.0
     */
    IMPORT_C TBool IsEmpty() const;

    /**
     * Returns ETrue if softkey status change is allowed.
     * 
     * @param aSofkeyPosition Softkey position.
     * @param aDisabled ETrue if softkey is to be disabled.
     * @return ETrue if softkey status change is allowed.
     */
    TBool SoftkeyStatusChangeAllowed(
            TInt aSofkeyPosition, TBool aDisabled );

    /**
     * Returns item specific softkey if it state should be updated.
     * 
     * @return Item specific softkey.
     */
    TEikGroupControl* ItemSpecificSoftkey() const;

    /**
     * Updates item specific softkey.
     * 
     * @param aVisibleCollection ETrue if state should be updated according
     * to visible collection.
     */
    void UpdateItemSpecificSoftkey( TBool aVisibleCollection = ETrue );


private: // new methods

    CEikCba(
        const CEikCba* aPrevious, 
        MEikCommandObserver* aCommandObserver, 
        RWindowGroup* aParentWg,
        TUint aFlags = 0 );
    void BaseConstructL();
    void ConstructL(TInt aResourceId);
    void ConstructFromResourceL(TResourceReader& aReader);
    CCoeControl* ButtonById( TInt aCommandId ) const;
    void CreateScrollBarFrameL();
    void InsertScrollBarL();
    TEikGroupControl VScrollBarAsGroupControl();
    void CheckSkinAndUpdateContext();
    
    TInt AknLayoutFlags() const;
    void SizeChangedInControlPane();
    void SizeChangedInStaconPane();
    void SizeChangedInRightPane();
    void UpdateFonts();
    
    void DoSkinChange();
    void DoColorChange();
    void DoLayoutChange();
    
    void SizeChangedInsideDialog();
    
    /**
     * Handles size change events in case of embedded softkeys.
     */
    void SizeChangedInPopup();

    /**
     * Updates softkey labels in case of embedded softkeys.
     *
     * @param aDrawDeferred ETrue to cause a redraw event.
     */
    void UpdateLabels( TBool aDrawDeferred );

    /**
     * Layouts given cba control to it's rect correctly. This function is 
     * used to layout every text and image inside of @c CEikCba.
     *
     * @param aControl CBA Control that is to be layouted
     * @param aRect the rect where control should be layouted.      
     */
    void LayoutControl(CCoeControl* aControl, const TRect& aRect);        
    
    void DoSetLayers( const TAknsItemID& aIID );
    
    /**
     * Broadcasts transparency information
     * to CEikCbaButtons.
     */
    void BroadcastPostingTransparency( TBool aEnable );

    /**
    * Sets the CBA fading according to button content.
    */
    void SetFadeState();
    
    /**
     * A better version of AddCommandToStackL
     * Pushes a command button with text and a command ID onto a position's button stack.
     * SizeChanged() is not called, so it need to be done after that.
     * Note that this implementation does not support bitmap and mask.
     *
     * @internal     
     *
     * @param aPosition The position in the button group at which to add the command button.
     * @param aCommandId Command ID the button will send.
     * @param aText Text for the button.
     */        
    void AddCommandToStackWithoutSizeChangedL(
        TInt aPosition,
        TInt aCommandId,
        const TDesC* aText);
    
    /**
     * Removes previous command but do not call SizeChanged And SetMSKIconL.
     * 
     * @internal
     *
     * @param aPosition The command's position.
     */
    void RemovePreviousCommandWithoutSizeChanged(TInt aPosition);

    /**
     * Reports state changed event if cba changed from empty to non-empty
     * or vice versa.
     */
    void ReportContentChangedEvent();
    
    /**
     * Draws embedded softkey.
     *
     * @internal
     * 
     * @param aGroupControl TEikGroupControl used to get access to CBA button.
     * @param aRect Softkey rectangle
     * @param aGc Graphics context
     * @param aMask Mask
     */
    void DrawEmbeddedSoftkey( TEikGroupControl& aGroupControl,
    		const TRect& aRect,
    		CWindowGc& aGc,
    		CFbsBitmap* aMask ) const;
    TBool UpdateIconL();
    		
    /**
     * Checks if the middle softkey should be used.
     *
     * @internal
     *
     * @return @c ETrue if MSK is to be used, @c EFalse otherwise.
     */
    TBool MskAllowed() const;

    /**
     * Updates item specific softkey.
     * 
     * @param aControl Item specifc softkey control.
     * @param aEnable ETrue if control should be enabled, EFalse if disabled.
     */
    void UpdateItemSpecificSoftkey( CCoeControl& aControl, TBool aEnable );

private: // from CCoeControl
    void SizeChanged();

private: // data
    TUint                   iCbaFlags;
    
    /** Used to maintain the original settings if a client needs to temporarily change its cba. */
    const CEikCba*          iLink; 
    
    CCoeBrushAndPenContext* iBrushAndPenContext;
    MEikCommandObserver*    iCommandObserver;
    CEikCbaScrollBarFrame*  iSBFrame;
    RWindowGroup*           iParentWg;
    
    /** New member variable that stores commands in correct order. */
    CEikCommandTable*   iCommandTable;
    
    /** For MSK. */
    TBool iMSKset;
    
    /** For MSK, caches CenRep value. */
    TBool iMSKEnabledInPlatform;
    
    /** Additional observer for MSK. This is called first and default observer after that. */
    MEikCommandObserver* iMSKCommandObserver;
    
    // From extension.
    const CFont* iLabelFont;
    const CFont* iStaconLabelFont;
    const CFont* iRightPaneLabelFont;
    TBool iPopupVisible;
    TBitFlags iFlags;

    /** Old background context. */
    CAknsBasicBackgroundControlContext* iBgContext;
    
    /** Old stacon background context. */
    CAknsLayeredBackgroundControlContext* iStaconBgContext;

    /** Masked layer backgrounds. */
    CAknsMaskedLayerBackgroundControlContext* iMLBgContext;
    CAknsMaskedLayerBackgroundControlContext* iStaconBgContextTop;
    CAknsMaskedLayerBackgroundControlContext* iStaconBgContextBottom;
    
    TAknsItemID iBgIID;

    /**
     * Skin background ID for the status pane controlled region
     * of the CBA area in bottom softkey landscape mode.
     */
    TAknsItemID iClockIndicBgIID;
    TBool       iIsClockIndicBgIIDSet;
    
    CEikCbaExtension* iExtension;
    };

/**
 * EIKON CBA button class definition.
 *
 * @internal
 * @lib eikcoctl.lib
 * @since S60 0.9 
 */
class CEikCbaButton : public CAknControl
    {
public:
    /**
     * Holds information about command id and dimming status for a button.
     */
    struct SButtonOptions
        {
        TInt iCommandId;
        TBool iDimmed;
        };
public:
    /**
     * Destructor.
     */
    ~CEikCbaButton();
    
    /**
     * Constructs a new CBA button instance.
     *
     * @param aAlignment Alignment for label.
     */
    void ConstructL(TGulAlignmentValue aAlignment);
public:
    /**
     * Updates the label text with the given label.
     *
     * @param aText The new label text.
     */
    void AddCommandL(const TDesC& aText);
    
    /**
     * Pushes a command into button stack.
     *
     * @param aCommandId The command to be pushed.
     * @param aText Text for the button.
     */    
    void PushCommandL(TInt aCommandId, const TDesC& aText);
    
    /**
     * Pops a command from the button stack.
     *
     * @return The button's command id. KErrNotFound if the button stack is empty.
     */    
    TInt PopCommand();
    
    /**
     * Removes a command from the button stack.
     *
     * @param aCommandId The command to be removed.
     */    
    void RemoveCommand(TInt aCommandId);
    
    /**
     * Removes the previous command from the button stack.
     */    
    void RemovePreviousCommand();
    
    /**
     * Switches the button's text to short or long depending on the parameter given.
     *
     * @param aShortText ETrue for short text, EFalse for the long text.
     */     
    void SwitchToShortTextL(TBool aShortText);
    
    /**
     * Sets the labels font.
     *
     * @param aLabelFont The font to be used.
     */    
    void SetLabelFont(const CFont* aLabelFont);
    
    /**
     * Truncates the label. This is done by CEikLabel.
     */    
    void TruncateLabelText();

    /**
     * Checks if text is empty in this button.
     */
    TBool IsEmptyText() const;
    
public:
    /**
     * From CCoeControl.
     * Sets the control's containing window by copying it from aContainer.
     * 
     * @param aContainer The compound control that is the container for this control.
     */
    void SetContainerWindowL(const CCoeControl& aContainer);
    
    /**
     * Constructs the control from a resource file.
     *
     * @param aReader The resource reader.
     * @param anAlignment Alignment for label.
     */
    void ConstructFromResourceL(TResourceReader& aReader, TGulAlignmentValue anAlignment);
    
    /** 
     * From CCoeControl.
     * Sets the control's minimum required size.
     * 
     * @return The minimum size required by the control.
     */
    TSize MinimumSize();
    
    /**
     * From CCoeControl.
     * Sets the control to be dimmed.
     *
     * @param aDimmed ETrue to dim the control, EFalse to set the control as not dimmed.
     */
    void SetDimmed(TBool aDimmed);
    
    /** 
     * From CCoeControl.
     * Handles pointer events.
     * 
     * @param aPointerEvent The pointer event.
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    
public:
    /**
     * Sets the button's image.
     * 
     * @param aImage The image to be set.
     */
    void SetImage(CEikImage &aImage);
    
    /**
     * Replaces the buttons image with label.
     */    
    void ReplaceImageByLabel();
    
    /**
     * Returns whether the button has image set. 
     * 
     * @return ETrue if the button has image set, EFalse otherwise.
     */        
    inline TBool IsImageOn() const {return iDoImage;};
    
    /**
     * Constructs empty button with id EAknSoftkeyEmpty
     */
    void ConstructEmptyButtonL();

protected:
    /**
     * Returns the button's index by command id.
     *
     * @param aCommandId The button's command id.
     * @return The button's index.
     */
    TInt IndexFromCommandId(TInt aCommandId);
    
    /**
     * Updates the label text with the given label.
     *
     * @param aText The new label text.
     */    
    void UpdateLabelText(TPtrC aLabelText);

private: 
    /**
     * From CCoeControl.
     * Gets the number of controls contained in a compound control.
     *
     * @return The number of component controls contained by this control.
     */
    TInt CountComponentControls() const;
    
    /**
     * From CCoeControl.
     * Gets an indexed component of a compound control.
     *
     * @param The index of the control.
     * @return The component control with an index of aIndex.
     */    
    CCoeControl* ComponentControl(TInt aIndex) const;
    
    /**
     * From CCoeControl.
     * Responds to changes to the size and position of the contents of this control.
     */    
    void SizeChanged();
    
    /**
     * From CAknControl.
     */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

public: // new functions
    /**
     * Returns the state of @c CEikCbaButton. 
     *
     * @return Boolean value for CEikCbaButtons state. ETrue if button is 
     *         pressed down. Otherwise returns EFalse.
     */ 
    TBool PressedDown() const;
    
    /**
     * Changes the state of @c CEikCbaButton. Button's state is stored in a 
     * member variable.
     *
     * @param  aPressedDown  The state that button has. @c ETrue if button's
     *                       state is pressed down. @c EFalse for normal,
     *                       not pressed state.
     */
    void SetPressedDown( const TBool aPressedDown );

    /**
     * Enables bitmap mode and hides the label. The text is drawn by CEikCba
     * in bitmap mode.
     * @internal
     * @since S60 v5.0
     * @param aEnableBitmap ETrue to enable bitmap mode. EFalse to work in the
     *                      standard way.
     */
    void SetTextBitmapMode( TBool aEnableBitmap );

    /**
     * Draws the button text and mask to give graphics contexts. Background
     * is not drawn.
     * @internal
     * @since S60 v5.0
     * @param aContext     Graphics context to render the text itself into.
     * @param aMaskContext Graphics context to render the text mask into.
     * @param aOffset      Offset between the coordinate system of the target
     *                     bitmap context relative to screen coordinates.
     */
    void DrawToContext(
        CBitmapContext& aContext,
        CBitmapContext& aMaskContext,
        const TPoint& aOffset ) const;
    
    /**
         * Returns the textual value of the button
         * @internal
         * @since S60 v5.0         
         */
    inline TPtrC FullLabelText() { return iFullLabelText;};

private:    
    void PrepareImageL();
    
protected:
    TBuf<KMaxCbaLabelLength> iFullLabelText;
    TPtrC iLongLabelText;
    TPtrC iShortLabelText;
    CEikLabel* iLabel;
    CDesCArray* iText;
    CArrayFix<SButtonOptions>* iButtonOptions;
    CEikImage* iImage;
    /** Original mask for softkey image. */
    const CFbsBitmap* iMask;
    /** Feedback effects transparency mask for softkey image. */
    CFbsBitmap* iSfeMask;
    TBool iDoImage;
    /** ETrue if should use text bitmap mode. */
    TBool iUseTextBitmap;
    /** Buttons state. */
    TBool iPressedDown;
    };

/**
 * Specialization of CEikCbaButton for the new Enhanced CBA button.
 *
 * @lib eikcoctl.lib
 * @since S60 3.0
 */
class CEikEnhancedCbaButton : public CEikCbaButton
    {
public:
    /**
     * Default constructor.
     */
    CEikEnhancedCbaButton();

    /**
     * Destructor.
     */
    ~CEikEnhancedCbaButton();
    
    /**
     * Returns the command type for current button.
     *
     * @return The command type.
     */
    TInt CommandType() const;
    
    /**
     * Sets command type for current button.
     *
     * @param aCommandType Command type to be set.
     */
    void SetCommandType(const TInt aCommandType);
    
    /**
     * Returns the command id for current button.
     *
     * @return The command id.
     */
    TInt CommandId() const; 
    
    /**
     * Constructs a button based on resource definition.
     *
     * @param aReader Resource reader for reading information from resource file.
     */
    void ConstructFromResourceL(TResourceReader& aReader);
    
    /**
     * Constructs empty button with id EAknSoftkeyEmpty.
     */
    void ConstructEmptyButtonL();
    
    /**
     * Used to get the label text for the button.
     *
     * @return Pointer to the label text.
     */
    TPtrC* LabelText();

private: // data
    TInt iCommandType; 
    TInt iCommandId;
    };

/**
 * Holds (enhanced) CBA commands and handles command ordering due to placement rules.
 *
 * @lib eikcoctl.lib
 * @since S60 3.0 
 *
 * @internal 
 */
NONSHARABLE_CLASS(CEikCommandTable) : public CBase
    {
public:
    /**
     * Constructs a new command table instance.
     * 
     * @return The new command table.
     */
    static CEikCommandTable* NewL();
    
    /**
     * Constructs a new command table instance.
     * 
     * @return The new command table.
     */    
    static CEikCommandTable* NewLC();
    
    /** 
     * Destructor.
     */
    ~CEikCommandTable();    
        
    /**
     * Used to add a command to CommandTable.
     *
     * @param aButton The button to be added.
     * @return KErrNone if addition was successful.
     */
    TInt AddCommandL(CEikEnhancedCbaButton* aButton);
    
    /**
     * Used to check if command table has a button with a certain id.
     *
     * @param aCommandId The id to be checked.
     * @return ETrue if command is placed in the command table.
     */
    TBool IsCommandPlaced(const TInt aCommandId) const;
    
    /**
     * Used to replace command with a new command.
     *
     * @param aCommandId Id for command that should be replaced.
     * @param aResourceId Id for new ENHANCED_CBA_BUTTON resource to be placed in the 
     *                    CommandTable.
     */
    void ReplaceCommandL(const TInt aCommandId, const TInt aResourceId);
    
    /**
     * Used to get CEikEnhancedCbaButton for current control button (1-4).
     *
     * @param aCommandIndex Index for requested button, use enum TCommandTableCbaPositions.
     * @return CEikCbaButton for current position, NULL if no button placed in that position.
     */
    CEikEnhancedCbaButton* Command(const TInt aCommandIndex);
    
    /**
     * Reset CommandTable.
     */
    void Reset();
    
private: // member functions
    /**
     * Constructor.
     */
    CEikCommandTable();
    
    /**
     * Constructs command table with device button priorities.
     */
    void ConstructL();
    
private: // data
    /** Displayed commands. */
    TFixedArray<CEikEnhancedCbaButton*, KMaxButtonsInCommandTable> iCommandButtons;
    
    /** Priority order for each button. */
    RArray< RArray<TInt> > iPriorities; 
    };

#endif // __EIKCBA_H__
