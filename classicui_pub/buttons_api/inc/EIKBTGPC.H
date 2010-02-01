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
* Description:  EIKON button group container class definition.
*
*/


#ifndef __EIKBTGPC_H__
#define __EIKBTGPC_H__

#include <coecntrl.h>
#include <eikbtgrp.h>
#include <eikcmobs.h>
#include <lafpublc.h>
#include <uikon.hrh>

#include <AknControl.h>

class MEikCommandObserver;
class CEikButtonGroupStack;
class CEikCommandButton;
class CEikListBox;

/**
 * The CEikButtonGroupContainer class provides a wrapper around the different button arrays
 * used in pen and no-pen devices. 
 *
 * @lib eikcoctl.lib 
 * @since S60 0.9 
 */
NONSHARABLE_CLASS(CEikButtonGroupContainer) : public CAknControl, public MEikCommandObserver
    {
public:
    /** 
     * Declares an object type for a class, in order to allow the object
     * provider mechanism to locate and provide objects from the class.
     */
    DECLARE_TYPE_ID(0x101F4107)

    /**
     * Describes how the container is being used.
     *
     * The enumeration is used by the system to create the appropriate (UI variant-specific)
     * button group for the specified type.
     */
    enum TUse
        {
        EView          = SLafButtonGroupContainer::EView,         ///< In a view.
        EDialog        = SLafButtonGroupContainer::EDialog,       ///< In a dialog.
        EToolbar       = SLafButtonGroupContainer::EToolbar,      ///< In a toolbar.
        ECba           = SLafButtonGroupContainer::ECba,          ///< In a control button array.
        EDialogButtons = SLafButtonGroupContainer::EDialogButtons ///< In dialog buttons.
        };
        
    /**
     * Describes the orientation of the container.
     */        
    enum TOrientation
        {
        EVertical   = SLafButtonGroupContainer::EVertical,  ///< Buttons are laid out vertically.
        EHorizontal = SLafButtonGroupContainer::EHorizontal ///< Buttons are laid out horizontally.
        };
        
    /**
     * Relative positions of the container and the control which uses it.
     */        
    enum TLocation
        {
        /** The button group is internal to the control which is using it. E.g. dialog buttons. */
        EInternal   = SLafButtonGroupContainer::EInternal, 
        
        /** The button group is external to the control which is using it. E.g. toolbar or cba. */
        EExternal   = SLafButtonGroupContainer::EExternal  
        };
        
    /**
     * Flags for the display of hotkeys.
     */        
    enum THotKeyFlags
        {
        EShowHotKey      = 0x01, ///< Hotkeys for commands should be shown.
        EPlainHotKey     = 0x02  ///< Hotkeys for commands should not be shown.
        };
        
    /** 
     * Additional flags.
     */         
    enum TFlags
        {
        EAddToStack      = 0x01, ///< Not used.
        EDelayActivation = 0x02, ///< If set, the container is not activated during construction.
        EUseMaxSize      = 0x04,  ///< Not used.
        EIsEmbedded      = 0x08, ///< Embedded in a dialog or popup.
        EParentIsControl = 0x10  ///< Parent window group is treated as CCoeControl.
        };
        
    /**
     * Defines the positions for each command.   
     */   
    enum TCommandPosition
        {
        ELeftSoftkeyPosition    = 0, ///< Position for left softkey.
        ERightSoftkeyPosition   = 2, ///< Position for right softkey.
        EMiddleSoftkeyPosition  = 3  ///< Position for middle softkey.
        };
        
public:
    /**
     * Creates a button group container in its own window.
     *
     * @param aUse The button group's type. 
     * @param aOrientation The button group's orientation. You need specify this 
     *                     only for devices that can layout their buttons either 
     *                     horizontally or vertically.
     * @param aCommandObserver A command observer to be notified of commands on 
     *                         the container.
     * @param aResourceId A resource containing descriptions of buttons in the group. 
     *                    This can be NULL if buttons are to be added dynamically.
     * @param aFlags The button group's flags.
     * @return Button group container object.
     */ 
    IMPORT_C static CEikButtonGroupContainer* NewL(
        TUse aUse,
        TOrientation aOrientation,
        MEikCommandObserver* aCommandObserver,
        TInt aResourceId,
        TUint aFlags = EAddToStack);

    /**
     * Creates a button group container in its parent control's window.
     *
     * @param aUse The button group's type.
     * @param aOrientation The button group's orientation. You need specify this 
     *                     only for devices that can layout their buttons either 
     *                     horizontally or vertically.
     * @param aCommandObserver A command observer to be notified of commands on 
     *                         the container.
     * @param aResourceId A resource containing descriptions of buttons in the group. 
     *                    This can be NULL if buttons are to be added dynamically.
     * @param aParent The control's parent.
     * @param aFlags The button group's flags.
     * @return Button group container object.
     */         
    IMPORT_C static CEikButtonGroupContainer* NewL(
        TUse aUse,
        TOrientation aOrientation,
        MEikCommandObserver* aCommandObserver,
        TInt aResourceId,
        const CCoeControl& aParent,
        TUint aFlags = EAddToStack);

    /**
     * Creates a button group container in given window group.
     *
     * @param aUse The button group's type.
     * @param aOrientation The button group's orientation. You need specify this 
     *                     only for devices that can layout their buttons either 
     *                     horizontally or vertically.
     * @param aCommandObserver A command observer to be notified of commands on 
     *                         the container.
     * @param aResourceId A resource containing descriptions of buttons in the group. 
     *                    This can be NULL if buttons are to be added dynamically.
     * @param aParentWg The parent window group.
     * @param aFlags The button group's flags.
     * @return Button group container object.
     */        
    IMPORT_C static CEikButtonGroupContainer* NewL(
        TUse aUse,
        TOrientation aOrientation,
        MEikCommandObserver* aCommandObserver,
        TInt aResourceId,
        RWindowGroup& aParentWg,
        TUint aFlags = EAddToStack);

    /**
     * Destructor.
     */        
    IMPORT_C ~CEikButtonGroupContainer();

    /**
     * Gets a pointer to an application's currently active CEikButtonGroupContainer (if any).
     *
     * Returns NULL if there are no containers active or none suitable for sharing. 
     * Ownership of the returned pointer is not transferred.
     *
     * @return Pointer to the button group container.
     */    
    IMPORT_C static CEikButtonGroupContainer* Current();
    
public:
    /**
     * Sets a command button's text label and command ID.
     *
     * @param aPosition The position within the button group of the button to change.
     *                  If the position is out of range this function raises a panic.
     * @param aCommandId Command ID the button will send.
     * @param aText Text for the button.
     */
    inline void SetCommandL(
        TInt aPosition, 
        TInt aCommandId, 
        const TDesC& aText);

    /**
     * Sets a command button's bitmap and command ID.
     *
     * @param aPosition The position within the button group of the button to change. 
     *                  If the position is out of range this function raises a panic.
     * @param aCommandId Command ID the button will send.
     * @param aBitmap The bitmap for the button.
     * @param aMask The mask bitmap for aBitmap.
     */    
    inline void SetCommandL(
        TInt aPosition, 
        TInt aCommandId, 
        const CFbsBitmap& aBitmap,
        const CFbsBitmap& aMask);

    /**
     * Sets a command button's bitmap, text and command ID.
     *
     * @param aPosition The position within the button group of the button to change. 
     *                  If the position is out of range, the function raises a panic.
     * @param aCommandId Command ID the button will send.
     * @param aText The text for the button.
     * @param aBitmap The bitmap for the button.
     * @param aMask The mask bitmap for aBitmap.
     */        
    inline void SetCommandL(
        TInt aPosition, 
        TInt aCommandId, 
        const TDesC& aText,
        const CFbsBitmap& aBitmap,
        const CFbsBitmap& aMask);

    /**
     * Sets a command button's bitmap and command ID. The bitmap and its mask are read
     * from a file.
     *
     * @param aPosition The position within the button group of the button to change.
     *                  If the position is out of range, the function raises a panic.
     * @param aCommandId Command ID the button will send.
     * @param aFile A multi-bitmap file, containing mask and bitmap images.
     * @param aBitmapId ID of the bitmap within aFile.
     * @param aMaskId ID of the mask within aFile.
     */        
    inline void SetCommandL(
        TInt aPosition, 
        TInt aCommandId, 
        const TDesC& aFile,
        TInt aBitmapId,
        TInt aMaskId);

    /**
     * Sets a command button's bitmap, text label and command ID. The bitmap and its 
     * mask are read from a file.
     *
     * @param aPosition The position within the button group of the button to change.
     *                  If the position is out of range, the function raises a panic.
     * @param aCommandId Command ID the button will send.
     * @param aText The text for the button.
     * @param aFile A multi-bitmap file, containing mask and bitmap images.
     * @param aBitmapId ID of the bitmap within aFile.
     * @param aMaskId ID of the mask within aFile.
     */        
    inline void SetCommandL(
        TInt aPosition, 
        TInt aCommandId, 
        const TDesC& aText,
        const TDesC& aFile,
        TInt aBitmapId,
        TInt aMaskId);

    /**
     * Sets a command button's bitmap, text label and command ID. The bitmap, mask,
     * text and command ID are all read from resource.
     *
     * @param aPosition The position within the button group of the button to change.
     *                  If the position is out of range, the function raises a panic.
     * @param aResourceId Resource ID specifying the text, bitmaps and command ID.
     */        
    inline void SetCommandL(
        TInt aPosition, 
        TInt aResourceId);

    /**
     * Sets a command button's text. The button to change is identified by its command ID.
     *
     * @param aCommandId Command ID of the button to change.
     * @param aText The text for the button.
     * @leave KErrNotFound The ID cannot be matched to any button.
     */        
    inline void SetCommandL(
        TInt aCommandId, 
        const TDesC& aText);

    /**
     * Sets a command button's bitmap and mask. The button to change is identified 
     * by its command ID.
     *
     * @param aCommandId Command ID of the button to change.
     * @param aBitmap Bitmap for the button.
     * @param aMask Mask bitmap for aBitmap.
     * @leave KErrNotFound The ID cannot be matched to any button.
     */        
    inline void SetCommandL(
        TInt aCommandId, 
        const CFbsBitmap& aBitmap,
        const CFbsBitmap& aMask);

    /**
     * Sets a command button's bitmap, mask and text. The button to change is 
     * identified by its command ID.
     *
     * @param aCommandId Command ID of the button to change.
     * @param aText Text for the button.
     * @param aBitmap Bitmap for the button.
     * @param aMask Mask bitmap for aBitmap.
     */        
    inline void SetCommandL(
        TInt aCommandId, 
        const TDesC& aText,
        const CFbsBitmap& aBitmap,
        const CFbsBitmap& aMask);

    /**
     * Sets a command button's bitmap and mask. The bitmap and mask are read from 
     * a multi bitmap file. The button to change is identified by its command ID.
     *
     * @param aCommandId Command ID of the button to change.
     * @param aFile A multi-bitmap file, containing mask and bitmap images.
     * @param aBitmapId ID of the bitmap within aFile.
     * @param aMaskId ID of the mask within aFile.
     */        
    inline void SetCommandL(
        TInt aCommandId, 
        const TDesC& aFile,
        TInt aBitmapId,
        TInt aMaskId);

    /**
     * Sets a command button's bitmap, mask and text. The bitmap and its mask are read 
     * from a multi bitmap file. The button to change is identified by its command ID.
     *
     * @param aCommandId Command ID of the button to change.
     * @param aText Text for the button.
     * @param aFile  A multi-bitmap file, containing mask and bitmap images.
     * @param aBitmapId ID of the bitmap within aFile.
     * @param aMaskId ID of the mask within aFile.
     */        
    inline void SetCommandL(
        TInt aCommandId, 
        const TDesC& aText,
        const TDesC& aFile,
        TInt aBitmapId,
        TInt aMaskId);

    /**
     * Initialises the group of command buttons from a resource.
     *
     * @param aResourceId ID of the resource structure specifying the command buttons.
     */        
    IMPORT_C void SetCommandSetL(
        TInt aResourceId);   

    /**
     * Adds a command button with a text label and command ID.
     *
     * @param aPosition The position in the button group for the new button.
     * @param aCommandId Command ID for the new button.
     * @param aText Text for the button.          
     */   
    inline void AddCommandL(
        TInt aPosition, 
        TInt aCommandId,
        const TDesC& aText);

    /**
     * Adds a command button with a bitmap label and command ID.
     *
     * @param aPosition The position in the button group for the new button.
     * @param aCommandId Command ID for the new button.
     * @param aBitmap Bitmap for the button.
     * @param aMask Mask bitmap for aBitmap.
     */        
    inline void AddCommandL(
        TInt aPosition, 
        TInt aCommandId,
        const CFbsBitmap& aBitmap,
        const CFbsBitmap& aMask);

    /**
     * Adds a command button with a command ID and a label containing both 
     * a bitmap and text.
     *
     * @param aPosition The position in the button group for the new button.
     * @param aCommandId Command ID for the new button.
     * @param aText Text for the button.
     * @param aBitmap Bitmap for the button.
     * @param aMask Mask bitmap for aBitmap.
     */        
    inline void AddCommandL(
        TInt aPosition, 
        TInt aCommandId,
        const TDesC& aText,
        const CFbsBitmap& aBitmap,
        const CFbsBitmap& aMask);

    /**
     * Adds a command button with a command ID and a bitmap which is read from a file.
     *
     * @param aPosition The position in the button group for the new button.
     * @param aCommandId Command ID for the new button.
     * @param aFile Multi-bitmap file containing the bitmap and mask.
     * @param aBitmapId ID of the bitmap within aFile.
     * @param aMaskId ID of the mask within aFile.
     */        
    inline void AddCommandL(
        TInt aPosition, 
        TInt aCommandId,
        const TDesC& aFile,
        TInt aBitmapId,
        TInt aMaskId);

    /**
     * Adds a command button with a command ID and a label containing both a bitmap 
     * and text. The bitmap and mask are read from file.
     *
     * @param aPosition The position in the button group for the new button.
     * @param aCommandId Command ID for the new button.
     * @param aText Text for the button.
     * @param aFile Multi-bitmap file containing the bitmap and mask.
     * @param aBitmapId ID of the bitmap within aFile.
     * @param aMaskId ID of the mask within aFile.
     */        
    inline void AddCommandL(
        TInt aPosition, 
        TInt aCommandId,
        const TDesC& aText,
        const TDesC& aFile,
        TInt aBitmapId,
        TInt aMaskId);

    /**
     * Pushes a command button with a text label and command ID onto a position's 
     * button stack. This function behaves similarly to SetCommandL() but allows 
     * the previous command button to be retrieved by calling RemoveCommandFromStack().
     *
     * @param aPosition The position in the button group at which to add the command button. 
     * @param aCommandId Command ID the button will send.
     * @param aText Text for the button.
     */        
    inline void AddCommandToStackL(
        TInt aPosition,
        TInt aCommandId,
        const TDesC& aText);

    /**
     * Pushes a command button with a bitmap, mask and command ID onto a position's 
     * button stack. This function behaves similarly to SetCommandL() but allows the 
     * previous command button to be retrieved by calling RemoveCommandFromStack(). 
     *
     * @param aPosition The position in the button group at which to add the command button.
     * @param aCommandId Command ID the button will send.
     * @param aBitmap Bitmap for the button.
     * @param aMask Mask bitmap for aBitmap.
     */        
    inline void AddCommandToStackL(
        TInt aPosition,
        TInt aCommandId,
        const CFbsBitmap& aBitmap,
        const CFbsBitmap& aMask);

    /**
     * Pushes a command button with text, bitmap, mask and a command ID onto a position's
     * button stack. This function behaves similarly to SetCommandL() but allows the 
     * previous command button to be retrieved by calling RemoveCommandFromStack().
     *
     * @param aPosition The position in the button group at which to add the command button.
     * @param aCommandId Command ID the button will send.
     * @param aText Text for the button.
     * @param aBitmap Bitmap for the button.
     * @param aMask Mask bitmap for aBitmap.
     */        
    inline void AddCommandToStackL(
        TInt aPosition,
        TInt aCommandId,
        const TDesC& aText,
        const CFbsBitmap& aBitmap,
        const CFbsBitmap& aMask);

    /**
     * Pushes a command button with a bitmap, mask and command ID onto a position's button 
     * stack. The bitmap and mask are read from a file. This function behaves similarly to 
     * SetCommandL() but allows the previous command button to be retrieved by calling 
     * RemoveCommandFromStack().
     *
     * @param aPosition The position in the button group at which to add the command button.
     * @param aCommandId Command ID the button will send.
     * @param aFile A multi-bitmap file containing mask and bitmap.
     * @param aBitmapId Index into the file of the bitmap.
     * @param aMaskId Index into the file of the bitmap mask.
     */        
    inline void AddCommandToStackL(
        TInt aPosition,
        TInt aCommandId,
        const TDesC& aFile,
        TInt aBitmapId,
        TInt aMaskId);

    /**
     * Pushes a command button with text, bitmap, mask and command button onto a position's 
     * button stack. The bitmap and mask are read from a file. This function behaves similarly
     * to SetCommandL() but allows the previous command button to be retrieved by calling 
     * RemoveCommandFromStack(). 
     *
     * @param aPosition The position in the button group at which to push the command button.
     * @param aCommandId Command ID the button will send.
     * @param aText Text for the button.
     * @param aFile A multi-bitmap file containing mask and bitmap.
     * @param aBitmapId Index into the file of the bitmap.
     * @param aMaskId Index into the file of the bitmap mask.
     */        
    inline void AddCommandToStackL(
        TInt aPosition,
        TInt aCommandId,
        const TDesC& aText,
        const TDesC& aFile,
        TInt aBitmapId,
        TInt aMaskId);

    /**
     * Pushes a command button onto a position's button stack. The text, bitmap, mask and 
     * command ID are all read from resource. This function behaves similarly to 
     * SetCommandL() but allows the previous command button to be retrieved by calling 
     * RemoveCommandFromStack().
     *
     * @param aPosition The position in the button group at which to push the command button.
     * @param aResourceId ID of a resource specifying the text, bitmaps and command ID.
     */        
    inline void AddCommandToStackL(
        TInt aPosition,
        TInt aResourceId);

    /**
     * As with SetCommandL() but for a set of buttons, also allows the previous command 
     * button to be retrieved by calling RemoveCommand().
     *
     * @param aResourceId Resource describing the set of command buttons.
     */        
    IMPORT_C void AddCommandSetToStackL(
        TInt aResourceId);

    /**
     * Removes the command identified by aCommandId, in position aPosition in the group,
     * from the command stack. Automatically retrieves the previous command details. 
     * Commands are added to the stack by calling AddCommandToStackL.
     *
     * @param aPosition The position in the button group from which to remove the 
     *                  command button.
     * @param aCommandId Command ID.
     */        
    IMPORT_C void RemoveCommandFromStack(TInt aPosition, TInt aCommandId);

    /**
     * Sets the default command ID for buttons in this container.
     *
     * @param aCommandId Command to issue if no other is specified.
     */    
    IMPORT_C void SetDefaultCommand(TInt aCommandId); 

    /**
     * Calculates minimum size required to display the buttons defined in the specified
     * resource structure.
     *
     * @param aResourceId The ID of the resource structure describing the button group.
     * @return Minimum size required to display the button group defined in the specified resource structure.
     */    
    IMPORT_C TSize CalcMinimumSizeL(TInt aResourceId) const;    

    /**
     * Places the command in position aPosition in the group on the cleanup stack. Typically 
     * used when a control or view changes the contents of two or more buttons on receipt of 
     * focus. After altering one command with a call to AddCommandToStackL() the push is made 
     * to guarantee the display will be left in a consistent state if the second (and any 
     * subsequent) calls to AddCommandToStackL() fail. Only a single command can be pushed 
     * for each position.
     *
     * @param aPosition Position in the container of the button to push.
     */    
    IMPORT_C void CleanupCommandPushL(TInt aPosition);

    /**
     * Removes a command from the cleanup stack without destroying it.
     */    
    inline void CleanupCommandPop();

    /**
     * Removes one or more commands from the cleanup stack without destroying them.
     *
     * @param aCount Number of commands to pop.
     */    
    IMPORT_C void CleanupCommandPop(TInt aCount);       

    /**
     * Removes a single command which was pushed onto the cleanup stack. It does this by 
     * calling CleanupCommandPushL(), rolling back to the previous details. The command
     * button popped is destroyed.
     */    
    inline void CleanupCommandPopAndDestroy();

    /**
     * Removes one or more commands which were pushed onto the cleanup stack. It does this 
     * by calling CleanupCommandPushL(), rolling back to the previous details. The command 
     * buttons popped are destroyed.
     *
     * @param aCount Number of commands to pop and destroy.
     */    
    inline void CleanupCommandPopAndDestroy(TInt aCount);   

    /**
     * Gets the maximum number of buttons that can be supported by the device.
     *
     * @return The number of command buttons supported.
     */    
    IMPORT_C TInt MaxCommands() const;

    /**
     * Gets the total number of buttons currently present in the group.
     *
     * @return The number of buttons.
     */    
    IMPORT_C TInt ButtonCount() const;
    
    /**
    * Dims (but doesn't draw) the button with id aCommandId if aDimmed is ETrue. If two 
    * buttons have the same id, the button to be dimmed is undefined.
    *
    * @param aCommandId The id for command to be dimmed.
    * @param aDimmed ETrue for dimming.
    */
    IMPORT_C void DimCommand(TInt aCommandId, TBool aDimmed);
    
    /**
    * Returns ETrue if the button with id aCommandId is dimmed. If two buttons have 
    * the same id, the results of this check are undefined.
    *
    * @param aCommandId The id for command to be checked.
    * @return The state of the button.    
    */
    IMPORT_C TBool IsCommandDimmed(TInt aCommandId) const;
    
    /**
    * Sets the the button with id aCommandId to be visible if aVisible is ETrue. If two 
    * buttons have the same id, the button to be altered is undefined.
    *
    * @param aCommandId The id for command to be made visible.
    * @param aVisible EFalse for making button invisible.
    */
    IMPORT_C void MakeCommandVisible(TInt aCommandId, TBool aVisible);

    /**
    * Returns ETrue if the button with id aCommandId is visible. If two buttons have 
    * the same id, the results are undefined.
    *
    * @param aCommandId The id for command to be checked.
    * @return The state of the button.     
    */
    IMPORT_C TBool IsCommandVisible(TInt aCommandId) const;

    /**
    * Animates the button with id aCommandId. If two buttons have the same id, the 
    * button to be animated is undefined.
    *
    * @since S60 3.1
    * @param aCommandId The id for command to be animated.   
    */
    IMPORT_C void AnimateCommand(TInt aCommandId);
    
    /**
    * Dims (but doesn't draw) the button with position aPosition.
    *
    * @since S60 3.1
    * @param aPosition The position for command to be dimmed.
    * @param aDimmed ETrue for dimming.
    */
    IMPORT_C void DimCommandByPosition(TCommandPosition aPosition, TBool aDimmed);
    
    /**
    * Returns ETrue if the button with position aPosition is dimmed.
    *
    * @since S60 3.1
    * @param aPosition The position for command to be checked.
    * @return The state of the button.    
    */
    IMPORT_C TBool IsCommandDimmedByPosition(TCommandPosition aPosition) const;
    
    /**
    * Sets the the button with position aPosition to be visible if aVisible is ETrue.
    *
    * @since S60 3.1
    * @param aPosition The position for command to be made visible.
    * @param aVisible EFalse for making button invisible.
    */
    IMPORT_C void MakeCommandVisibleByPosition(TCommandPosition aPosition, TBool aVisible);
    
    /**
    * Returns ETrue if the button with position aPosition is visible.
    *
    * @since S60 3.1
    * @param aPosition The position for command to be checked.
    * @return The state of the button.     
    */
    IMPORT_C TBool IsCommandVisibleByPosition(TCommandPosition aPosition) const;
    
    /**
    * Animates the button with position aPosition.
    *
    * @since S60 3.1
    * @param aPosition The position for command to be animated.    
    */
    IMPORT_C void AnimateCommandByPosition(TCommandPosition aPosition);

    /**
     * Gets the button group's location. Typically the button group is external to the 
     * view which is using it. In some cases, such as in dialogs with button panels, 
     * the button group is internal to the control which is using it.
     *
     * @return The button group's location.
     */  
    IMPORT_C TLocation Location() const;
    
    /**
     * Gets a pointer to the command button with the specified command Id.
     *
     * @param aCommandId Command ID of the button.
     * @return Pointer to the command button CEikCommandButton, NULL if there 
     *         was no button with Id aCommandId.
     */      
    IMPORT_C CEikCommandButton* CommandButtonOrNull(TInt aCommandId) const;
    
    /**
     * Sets the boundary rectangle for externally-positioned button groups. 
     * For use by EExternal button groups only.
     * 
     * @param aRect The boundary rectangle to use. The button group attaches 
     *              itself to the inside of this rectangle.
     */    
    IMPORT_C void SetBoundingRect(const TRect& aRect);

    /**
     * Subtracts the area occupied by the button group from the specified bounding 
     * rectangle. This method should be used in preference to querying the container's 
     * area at all times. For use by EExternal button groups only.
     * 
     * @param aBoundingRect Rectangle to be modified.
     */        
    IMPORT_C void ReduceRect(TRect& aBoundingRect) const;

    /**
     * Gets a pointer to the control (button) with the specified command ID. 
     * This method is intended to allow access to standard CCoeControl functionality 
     * only. Casting the return value is likely to fail on different devices.
     *
     * @param aCommandId Command ID of the button to get.
     * @return Pointer to a CCoeControl, NULL if there was no button at aCommandId.
     */
    IMPORT_C CCoeControl* ControlOrNull(TInt aCommandId) const;
    
    /**
     * Gets a pointer to the the button with the specified command Id.
     *
     * @param aCommandId Command ID of the button to obtain.
     * @return The button object.
     */    
    IMPORT_C CEikCommandButton* ButtonById(TInt aCommandId) const;
    
    /**
     * Gets the position in the group of the button with the specified command Id.
     * The return value is undefined if two buttons share the same id.
     *
     * @param aCommandId Identifies the command.
     * @return The command's container position.
     */     
    IMPORT_C TInt PositionById(TInt aCommandId) const;
    
    /**
     * Updates a command's hotkey and whether the key is displayed. 
     * This function is only supported by containers being used for dialog buttons.
     *
     * @param aCommandId Identifies the command to update.
     * @param aFlags Whether to display the hotkey.
     * @param aKeyId Hotkey identifier.
     */    
    IMPORT_C void UpdateHotKey(TInt aCommandId, THotKeyFlags aFlags, TInt aKeyId);
    
    /**
     * Changes the command observer for the button at aPos to aCommandObserver. 
     * Panics if an updated observer is already present. This function should be followed 
     * by RemoveCommandObserver() when you need to put back the original observer.
     *
     * @param aPos The button's position.
     * @param aCommandObserver The command observer.
     */    
    IMPORT_C void UpdateCommandObserverL(TInt aPos, MEikCommandObserver& aCommandObserver);
    
    /**
     * Removes the temporary observer for the button at aPos, replacing it with the
     * observer that was present when UpdateCommandObserverL() was called.
     *
     * @param aPos The button's position.
     */    
    IMPORT_C void RemoveCommandObserver(TInt aPos);
    
    /**
     * Checks for existence of updated command observer for the button at aPosition.
     *
     * @since S60 3.2
     * @param aPosition The position for button to be checked.
     * @return ETrue, if updated command observer exists.
     */    
    IMPORT_C TBool UpdatedCommandObserverExists(TCommandPosition aPosition) const;
    
    /**
     * Tests whether the button group has explicitly been instructed to suppress redraws.
     * Some button groups may not activate themselves during construction, in which 
     * case, they need to be activated by the client. This method allows the client 
     * to enquire whether this is necessary.
     *
     * @return ETrue if the button group will suppress redraws, otherwise EFalse.
     */    
    IMPORT_C TBool DelayActivation() const;
    
    /**
     * Returns the container's button group.
     *
     * @return Pointer to the button group object. Ownership is not transferred.
     */    
    inline MEikButtonGroup* ButtonGroup();
    
    /**
     * Returns the button group type.
     *
     * @return The button group type.
     */    
    inline TUse ButtonGroupType();
    
    /**
    * Internal method for setting markable list's MSK observer.
    * This observer is called before default CBA observer if MSK is pressed.
    * Observer is removed by passing NULL as parameter.
    *
    * @since S60 3.1
    * @param aMSKObserverOwner
    * @param aCommandObserver
    */
    void UpdateMSKCommandObserver(
        CEikListBox* aMSKObserverOwner, 
        MEikCommandObserver* aCommandObserver);
    
public: // From CCoeControl.
    /**
     * From CCoeControl.
     * Gets the control's minimum required size.
     *
     * @return The minimum size required by the control.
     */ 
    IMPORT_C TSize MinimumSize();
    
    /**
     * From CCoeControl.
     * Handles key events.
     *
     * @param aKeyEvent The key event. 
     * @param aType The type of key event: EEventKey, EEventKeyUp or EEventKeyDown. 
     * @return Indicates whether or not the key event was used by this control. 
     */     
    IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
    
    /**
     * From CCoeControl.
     * Sets this control as visible or invisible.
     *
     * @param aVisible ETrue to make the control visible, EFalse to make it invisible. 
     */     
    void MakeVisible(TBool aVisible);
    
    /**
     * From CCoeControl.
     * Writes the internal state of the control and its components to aStream.
     * Does nothing in release mode.
     *
     * @param aWriteStream The output stream.
     */     
    IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
    
public:
    /**
     * Formerly from MTopSetMember<CEikButtonGroupContainer>, now reserved.
     */ 
    IMPORT_C virtual void Reserved_MtsmPosition();
    
    /**
     * Formerly from MTopSetMember<CEikButtonGroupContainer>, now reserved.
     */     
    IMPORT_C virtual void Reserved_MtsmObject();

public: // New functions for enhanced cba support.
    /**
     * Used to offer list of commands for softkeys.
     *
     * @since S60 3.2
     * @param aCommandList A list of command ids to be offered for softkeys.
     */
    IMPORT_C void OfferCommandListL(const RArray<TInt>& aCommandList);
    
    /**
     * Used to offer list of commands for softkeys.
     *
     * @since S60 3.2
     * @param aResourceId Id for CBA resource that defines enhanced cba buttons.
     */ 
    IMPORT_C void OfferCommandListL(const TInt aResourceId);

    /**
     * Used to check if a certain command have been approved to the current command set
     *
     * @since S60 3.2
     * @param aCommandId The id for command which existence should be checked.
     * @return ETrue if command is in control group, otherwise EFalse.
     */     
    IMPORT_C TBool IsCommandInGroup(const TInt aCommandId) const;
    
    /**
     * Replaces command with another.
     *
     * @since S60 3.2 
     * @param aCommandId Id for command that should be replaced.
     * @param aResourceId Resource id for new enhanced cba button.
     */     
    IMPORT_C void ReplaceCommand(const TInt aCommandId, const TInt aResourceId);

private:
    enum TCommandOp {ESet, EAdd, EPush};
    
private:
    class TCmdPos
        {
    public:
        inline TCmdPos();
        inline TCmdPos(TInt aPos, TInt aCmd);
    public:
        TInt iPos;
        TInt iCmd;
        };
        
    class TCmdObserver
        {
    public:
        inline TCmdObserver(TInt aPos, MEikCommandObserver& aObserver);
    public:
        TInt iPos;
        MEikCommandObserver& iObserver;
        };
        
    class CCmdObserverArray : public CArrayFixFlat<TCmdObserver>
        {
    public:
        inline CCmdObserverArray();
        TInt FindIndex(TInt aPos);
        };
        
private:
    CEikButtonGroupContainer(TUse aUse);
    
    void ConstructL(
        TOrientation aOrientation,
        MEikCommandObserver* aCommandObserver,
        TInt aResourceId,
        RWindowGroup* aParentWg,
        TUint aFlags);
        
    IMPORT_C void DoSetCommandL(
        TInt aPosition,
        TInt aCommandId,
        const TDesC* aText,
        const CFbsBitmap* aBitmap,
        const CFbsBitmap* aMask,
        TCommandOp aOp);
        
    IMPORT_C void DoSetCommandL(
        TInt aPosition,
        TInt aCommandId,
        const TDesC* aText,
        const TDesC& aFile,
        TInt aBitmapId,
        TInt aMaskId,
        TCommandOp aOp);
        
    IMPORT_C void DoSetCommandL(
        TInt aCommandId,
        const TDesC* aText,
        const CFbsBitmap* aBitmap,
        const CFbsBitmap* aMask,
        TCommandOp aOp);
        
    IMPORT_C void DoSetCommandL(
        TInt aCommandId,
        const TDesC* aText,
        const TDesC& aFile,
        TInt aBitmapId,
        TInt aMaskId,
        TCommandOp aOp);
        
    IMPORT_C void DoSetCommandL(
        TInt aPosition,
        TInt aResourceId,
        TCommandOp aOp);
    
    inline CCoeControl* ButtonGroupAsControl() const;
    void UpdateRect();
    static void CleanupCommandDestroy(TAny* aPtr);
    TCmdPos DoCleanupCommandPop();
    void DoCleanupCommandPopAndDestroy();

private: // from CCoeControl
    TInt CountComponentControls() const;
    CCoeControl* ComponentControl(TInt aIndex) const;
    void SizeChanged();

private: // from MEikCommandObserver
    void ProcessCommandL(TInt aCommandId);
    CCoeControl* CreateCustomCommandControlL(TInt aControlType);

private:
    MEikButtonGroup* iButtonGroup;
    TUse iUse;
    CArrayFix<TCmdPos>* iCommandsCleanup;
    MEikCommandObserver* iCommandObserver;
    CCmdObserverArray* iObserverArray;
    TDblQueLink iBtLink;
    CEikListBox* iMSKObserverOwner;
    TInt iSpare;
    TInt iValid;
private:
    friend class CCmdObserverArray;
    friend class CEikButtonGroupStack;
    };


// Inline function implementations.

inline void CEikButtonGroupContainer::SetCommandL(
    TInt aPosition,
    TInt aCommandId,
    const TDesC& aText)
    {
    DoSetCommandL(aPosition, aCommandId, &aText, NULL, NULL, ESet);
    }

inline void CEikButtonGroupContainer::SetCommandL(
    TInt aPosition,
    TInt aCommandId,
    const CFbsBitmap& aBitmap,
    const CFbsBitmap& aMask)
    {
    DoSetCommandL(aPosition, aCommandId, NULL, &aBitmap, &aMask, ESet);
    }

inline void CEikButtonGroupContainer::SetCommandL(
    TInt aPosition,
    TInt aCommandId,
    const TDesC& aText,
    const CFbsBitmap& aBitmap,
    const CFbsBitmap& aMask)
    {
    DoSetCommandL(aPosition, aCommandId, &aText, &aBitmap, &aMask, ESet);
    }

inline void CEikButtonGroupContainer::SetCommandL(
    TInt aPosition,
    TInt aCommandId,
    const TDesC& aFile,
    TInt aBitmapId,
    TInt aMaskId)
    {
    DoSetCommandL(aPosition, aCommandId, NULL, aFile, aBitmapId, aMaskId, ESet);
    }

inline void CEikButtonGroupContainer::SetCommandL(
    TInt aPosition,
    TInt aCommandId,
    const TDesC& aText,
    const TDesC& aFile,
    TInt aBitmapId,
    TInt aMaskId)
    {
    DoSetCommandL(aPosition, aCommandId, &aText, aFile, aBitmapId, aMaskId, ESet);
    }

inline void CEikButtonGroupContainer::SetCommandL(
    TInt aPosition,
    TInt aResourceId)
    {
    DoSetCommandL(aPosition, aResourceId, ESet);
    }

inline void CEikButtonGroupContainer::SetCommandL(
    TInt aCommandId,
    const TDesC& aText)
    {
    DoSetCommandL(aCommandId, &aText, NULL, NULL, ESet);
    }

inline void CEikButtonGroupContainer::SetCommandL(
    TInt aCommandId,
    const CFbsBitmap& aBitmap,
    const CFbsBitmap& aMask)
    {
    DoSetCommandL(aCommandId, NULL, &aBitmap, &aMask, ESet);
    }

inline void CEikButtonGroupContainer::SetCommandL(
    TInt aCommandId,
    const TDesC& aText,
    const CFbsBitmap& aBitmap,
    const CFbsBitmap& aMask)
    {
    DoSetCommandL(aCommandId, &aText, &aBitmap, &aMask, ESet);
    }

inline void CEikButtonGroupContainer::SetCommandL(
    TInt aCommandId,
    const TDesC& aFile,
    TInt aBitmapId,
    TInt aMaskId)
    {
    DoSetCommandL(aCommandId, NULL, aFile, aBitmapId, aMaskId, ESet);
    }

inline void CEikButtonGroupContainer::SetCommandL(
    TInt aCommandId,
    const TDesC& aText,
    const TDesC& aFile,
    TInt aBitmapId,
    TInt aMaskId)
    {
    DoSetCommandL(aCommandId, &aText, aFile, aBitmapId, aMaskId, ESet);
    }

inline void CEikButtonGroupContainer::AddCommandL(
    TInt aPosition,
    TInt aCommandId,
    const TDesC& aText)
    {
    DoSetCommandL(aPosition, aCommandId, &aText, NULL, NULL, EAdd);
    }

inline void CEikButtonGroupContainer::AddCommandL(
    TInt aPosition,
    TInt aCommandId,
    const CFbsBitmap& aBitmap,
    const CFbsBitmap& aMask)
    {
    DoSetCommandL(aPosition, aCommandId, NULL, &aBitmap, &aMask, EAdd);
    }

inline void CEikButtonGroupContainer::AddCommandL(
    TInt aPosition,
    TInt aCommandId,
    const TDesC& aText,
    const CFbsBitmap& aBitmap,
    const CFbsBitmap& aMask)
    {
    DoSetCommandL(aPosition, aCommandId, &aText, &aBitmap, &aMask, EAdd);
    }

inline void CEikButtonGroupContainer::AddCommandL(
    TInt aPosition,
    TInt aCommandId,
    const TDesC& aFile,
    TInt aBitmapId,
    TInt aMaskId)
    {
    DoSetCommandL(aPosition, aCommandId, NULL, aFile, aBitmapId, aMaskId, EAdd);
    }

inline void CEikButtonGroupContainer::AddCommandL(
    TInt aPosition,
    TInt aCommandId,
    const TDesC& aText,
    const TDesC& aFile,
    TInt aBitmapId,
    TInt aMaskId)
    {
    DoSetCommandL(aPosition, aCommandId, &aText, aFile, aBitmapId, aMaskId, EAdd);
    }

inline void CEikButtonGroupContainer::AddCommandToStackL(
    TInt aPosition,
    TInt aCommandId,
    const TDesC& aText)
    {
    DoSetCommandL(aPosition, aCommandId, &aText, NULL, NULL, EPush);
    }

inline void CEikButtonGroupContainer::AddCommandToStackL(
    TInt aPosition,
    TInt aCommandId,
    const CFbsBitmap& aBitmap,
    const CFbsBitmap& aMask)
    {
    DoSetCommandL(aPosition, aCommandId, NULL, &aBitmap, &aMask, EPush);
    }

inline void CEikButtonGroupContainer::AddCommandToStackL(
    TInt aPosition,
    TInt aCommandId,
    const TDesC& aText,
    const CFbsBitmap& aBitmap,
    const CFbsBitmap& aMask)
    {
    DoSetCommandL(aPosition, aCommandId, &aText, &aBitmap, &aMask, EPush);
    }

inline void CEikButtonGroupContainer::AddCommandToStackL(
    TInt aPosition,
    TInt aCommandId,
    const TDesC& aFile,
    TInt aBitmapId,
    TInt aMaskId)
    {
    DoSetCommandL(aPosition, aCommandId, NULL, aFile, aBitmapId, aMaskId, EPush);
    }

inline void CEikButtonGroupContainer::AddCommandToStackL(
    TInt aPosition,
    TInt aCommandId,
    const TDesC& aText,
    const TDesC& aFile,
    TInt aBitmapId,
    TInt aMaskId)
    {
    DoSetCommandL(aPosition, aCommandId, &aText, aFile, aBitmapId, aMaskId, EPush);
    }

inline void CEikButtonGroupContainer::AddCommandToStackL(
    TInt aPosition,
    TInt aResourceId)
    {
    DoSetCommandL(aPosition, aResourceId, EPush);
    }

inline void CEikButtonGroupContainer::CleanupCommandPop()
    {
    CleanupCommandPop(1);
    }

inline void CEikButtonGroupContainer::CleanupCommandPopAndDestroy()
    {
    CleanupStack::PopAndDestroy();
    }

inline void CEikButtonGroupContainer::CleanupCommandPopAndDestroy(TInt aCount)
    {
    CleanupStack::PopAndDestroy(aCount);
    }

inline MEikButtonGroup* CEikButtonGroupContainer::ButtonGroup()
    {
    return iButtonGroup;
    }

inline CEikButtonGroupContainer::TUse CEikButtonGroupContainer::ButtonGroupType()
    {
    return iUse;
    }

#endif // __EIKBTGPC_H__
