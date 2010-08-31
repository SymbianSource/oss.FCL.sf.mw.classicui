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
* Description:  EIKON button group base class definitions.
*
*/


#ifndef __EIKBTGRP_H__
#define __EIKBTGRP_H__

#include <e32std.h>

class CCoeControl;
class CEikCommandButton;
class CFbsBitmap;
class MEikCommandObserver;

/**
 * Abstract base class for EIKON button group.
 *
 * @lib eikcoctl.lib
 * @since S60 0.9  
 *
 * @internal
 */
class MEikButtonGroup
    {
public:
    /**
     * Deletes the object.
     */
    void Release();
    
    /**
     * Sets a command button's bitmap, text and command ID.
     *
     * @param aPosition The position within the button group of the button to change. 
     * @param aCommandId Command ID the button will send.
     * @param aText The text for the button.
     * @param aBitmap The bitmap for the button.
     * @param aMask The mask bitmap for aBitmap.
     */    
    virtual void SetCommandL(
        TInt aPosition,
        TInt aCommandId,
        const TDesC* aText,
        const CFbsBitmap* aBitmap,
        const CFbsBitmap* aMask) = 0;
       
    /**
     * Sets a command button's bitmap, text label and command ID.
     * The bitmap, mask, text and command ID are all read from resource.
     *
     * @param aPosition The position within the button group of the button to change.
     * @param aResourceId Resource ID specifying the text, bitmaps and command ID.
     */        
    virtual void SetCommandL(TInt aPosition, 
        TInt aResourceId) = 0;

    /**
     * Initialises the group of command buttons from a resource.
     *
     * @param aResourceId ID of the resource structure specifying the command buttons.
     */    
    virtual void SetCommandSetL(TInt aResourceId) = 0;
    
    /**
     * Adds a command button with a command ID and a label containing both a bitmap and text.
     *
     * @param aPosition The position in the button group for the new button.
     * @param aCommandId Command ID for the new button.
     * @param aText Text for the button.
     * @param aBitmap Bitmap for the button.
     * @param aMask Mask bitmap for aBitmap.
     */    
    virtual void AddCommandL(
        TInt aPosition,
        TInt aCommandId,
        const TDesC* aText,
        const CFbsBitmap* aBitmap,
        const CFbsBitmap* aMask) = 0;
        
    /**
     * Pushes a command button with text, bitmap, mask and a command ID onto a 
     * position's button stack.
     *
     * @param aPosition The position in the button group at which to add the command button.
     * @param aCommandId Command ID the button will send.
     * @param aText Text for the button.
     * @param aBitmap Bitmap for the button.
     * @param aMask Mask bitmap for aBitmap.
     */        
    virtual void AddCommandToStackL(
        TInt aPosition,
        TInt aCommandId,
        const TDesC* aText,
        const CFbsBitmap* aBitmap,
        const CFbsBitmap* aMask) = 0;
       
    /**
     * Pushes a command button onto a position's button stack.
     * The text, bitmap, mask and command ID are all read from resource.
     *
     * @param aPosition The position in the button group at which to push the command button.
     * @param aResourceId ID of a resource specifying the text, bitmaps and command ID.
     */        
    virtual void AddCommandToStackL(TInt aPosition, 
        TInt aResourceId) = 0;
    
    /**
     * As with SetCommandL() but for a set of buttons, also allows the previous 
     * command button to be retrieved by calling RemoveCommand().
     *
     * @param aResourceId Resource describing the set of command buttons.
     */    
    virtual void AddCommandSetToStackL(TInt aResourceId) = 0;

    /**
     * Sets the default command ID for buttons in this button group.
     *
     * @param aCommandId Command to issue if no other is specified.
     */    
    virtual void SetDefaultCommand(TInt aCommandId) = 0;
    
    /**
     * Calculates minimum size required to display the buttons defined in the 
     * specified resource structure.
     *
     * @param aResourceId The ID of the resource structure describing the button group.
     * @return Minimum size required to display the button group defined in the specified 
     *         resource structure.
     */    
    virtual TSize CalcMinimumSizeL(TInt aResourceId) = 0;
    
    /**
     * Removes the command identified by aCommandId, in position aPosition in the 
     * group, from the command stack. Automatically retrieves the previous command 
     * details. Commands are added to the stack by calling AddCommandToStackL.
     *
     * @param aPosition The position in the button group from which to remove the 
     *                  command button.
     * @param aCommandId Command ID.
     */    
    virtual void RemoveCommandFromStack(TInt aPosition, 
        TInt aCommandId) = 0;
    
    /**
     * Returns the command position by command id.
     *
     * @param aCommandId The button's command id.
     * @return The command position in the button group.
     */    
    virtual TInt CommandPos(TInt aCommandId) const = 0;
    
    /**
     * Dims or undims a button without drawing it. 
     *
     * @param aCommandId Command ID of the button to change.
     * @param aDimmed ETrue to dim the specified command. EFalse to undim the specified command.
     */    
    virtual void DimCommand(TInt aCommandId, 
        TBool aDimmed) = 0;
    
    /**
     * Determines whether the button with the specified command ID is dimmed. 
     *
     * @param aCommandId The command ID.
     * @return ETrue if the specified command is dimmed. EFalse if the specified command is 
     *               not dimmed.
     */    
    virtual TBool IsCommandDimmed(TInt aCommandId) const = 0;
    
    /**
     * Makes the button with the specified id either visible, or invisible. 
     *
     * @param aCommandId Specifies the button to alter.

     * @param aVisible ETrue to make the specified button visible. EFalse to make the specified
     *                 button invisible.
     */    
    virtual void MakeCommandVisible(TInt aCommandId, 
        TBool aVisible) = 0;
    
    /**
     * Tests whether the button with the specified command ID is visible.
     *
     * @param aCommandId Specifies the button.
     * @return ETrue if the specified button is visible. EFalse if the specified button is 
     *               not visible.
     */    
    virtual TBool IsCommandVisible(TInt aCommandId) const = 0;
    
    /**
     * Animates the button with the specified id. 
     *
     * @param aCommandId The button to animate.
     */    
    IMPORT_C virtual void AnimateCommand(TInt aCommandId);
    
    /**
     * Returns the button group as a control.
     *
     * @return The button group as a control.
     */    
    virtual CCoeControl* AsControl() = 0;
    
    /**
     * Returns the button group as a control.
     *
     * @return The button group as a control.
     */    
    virtual const CCoeControl* AsControl() const = 0;
    
    /**
     * Sets the boundary rectangle for externally-positioned button groups. 
     * For use by EExternal button groups only.
     *
     * @param aBoundingRect The boundary rectangle to use. The button group attaches itself 
     *                      to the inside of this rectangle.
     */     
    virtual void SetBoundingRect(const TRect& aBoundingRect) = 0;
    
    /**
     * Subtracts the area occupied by the button group from the specified bounding rectangle.
     * This method should be used in preference to querying the container's area at all times.
     * For use by EExternal button groups only.
     *
     * @param aBoundingRect Rectangle to be modified.
     */     
    virtual void ReduceRect(TRect& aBoundingRect) const = 0;

    /**
     * Returns a group control (a button) as a control.
     *
     * @param aCommandId The button's command id.
     * @return The group control as a control.
     */     
    virtual CCoeControl* GroupControlById(TInt aCommandId) const = 0;

    /**
     * Returns a group control (a button) as a command button.
     *
     * @param aCommandId The button's command id.
     * @return The group control as a command button.
     */     
    virtual CEikCommandButton* GroupControlAsButton(TInt aCommandId) const = 0;

    /**
     * Returns the command id by position.
     *
     * @param aCommandPos The command's position.
     * @return The command id.
     */     
    virtual TInt CommandId(TInt aCommandPos) const = 0;
    
    /**
     * Gets the total number of buttons currently present in the group.
     *
     * @return The number of buttons.
     */     
    virtual TInt ButtonCount() const = 0;
    
    /**
     * Gets the button group flags.
     *
     * @return The button group flags.
     */     
    virtual TUint ButtonGroupFlags() const = 0;

    /**
     * Sets the middle softkey command observer.
     *
     * @param aCommandObserver The middle softkey command observer.
     */ 
    virtual void SetMSKCommandObserver(MEikCommandObserver* aCommandObserver) = 0;
    
    /**
     * Dims (but doesn't draw) the button with position aPosition.
     *
     * @param aPosition The position for command to be dimmed.
     * @param aDimmed ETrue for dimming.
     */    
    virtual void DimCommandByPosition(TInt aPosition, 
        TBool aDimmed) = 0;
    
    /**
     * Returns ETrue if the button with position aPosition is dimmed.
     *
     * @param aPosition The position for command to be checked.
     * @return The state of the button.    
     */    
    virtual TBool IsCommandDimmedByPosition(TInt aPosition) const = 0;
    
    /**
     * Sets the the button with position aPosition to be visible if aVisible is ETrue.
     *
     * @param aPosition The position for command to be made visible.
     * @param aVisible EFalse for making button invisible.
     */     
    virtual void MakeCommandVisibleByPosition(TInt aPosition, 
        TBool aVisible) = 0;

    /**
     * Returns ETrue if the button with position aPosition is visible.
     *
     * @param aPosition The position for command to be checked.
     * @return The state of the button.     
     */     
    virtual TBool IsCommandVisibleByPosition(TInt aPosition) const = 0;
    
    /**
     * Animates the button with position aPosition.
     *
     * @param aPosition The position for command to be animated.    
     */  
    virtual void AnimateCommandByPosition(TInt aPosition) = 0;
    
private:
    IMPORT_C void Reserved_1();
    };
    

/**
 * Extends needed functions for enhanced cba.
 *
 * @internal 
 * @since S60 3.0
 */
class MEikEnhancedButtonGroup : public MEikButtonGroup
    {
public:
    /**
     * Used to offer list of commands for softkeys.
     *
     * @param aCommandList A list of command ids to be offered for softkeys.
     */
    IMPORT_C virtual void OfferCommandListL(const RArray<TInt>& aCommandList) = 0;

    /**
     * Used to offer list of commands for softkeys.
     *
     * @param aResourceId Id for CBA resource that defines enhanced cba buttons.
     */
    IMPORT_C virtual void OfferCommandListL(const TInt aResourceId) = 0;
    
    /**
     * Used to check if a certain command have been approved to the current command set.
     *
     * @param aCommandId The id for command which existence should be checked.
     * @return ETrue if command is in control group, otherwise EFalse.
     */ 
    IMPORT_C virtual TBool IsCommandInGroup(const TInt aCommandId) const = 0;
    
    /**
     * Replace existing command with a new command.
     *
     * @param aCommandId Id for command that should be replaced.
     * @param aResourceId Resource id for new enhanced cba button.
     */ 
    IMPORT_C virtual void ReplaceCommand(const TInt aCommandId, const TInt aResourceId) = 0;  
    };

#endif // __EIKBTGRP_H__
