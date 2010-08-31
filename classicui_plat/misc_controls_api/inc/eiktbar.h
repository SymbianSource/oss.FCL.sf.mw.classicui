/*
* Copyright (c) 2002-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Class declaration for EIKON toolbar control.
*
*/


#ifndef __EIKTBAR_H__
#define __EIKTBAR_H__

#include <eikctgrp.h>
#include <coecobs.h>
#include <eikbtgrp.h>
#include <eikbtgpc.h>

// Forward declarations

class MEikCommandObserver;
class TEikButtonCoordinator;
class CEikCommandButton;
class CCoeBrushAndPenContext;

/**
 * A vertical group of controls displayed down the right-hand side of the
 * screen in an application.
 *
 * It contains buttons which are used to issue application commands,
 * and other controls. A toolband may also be created using this class,
 * by setting the @c EEikToolBarHorizontal flag and initialising from a
 * @c TOOLBAND resource.
 *
 * @lib eikcoctl.lib
 * @since S60 0.9
 */
class CEikToolBar : public CEikControlGroup,
                    public MCoeControlObserver,
                    public MEikButtonGroup
	{
public:

    /**
     * Destructor.
     * Deletes the toolbar's brush and pen context and control types.
     */
	IMPORT_C ~CEikToolBar();
	
	/**
     * Default C++ constructor.
     * Creates a new toolbar object, but does not initialise any of
     * its heap-stored members.
     */
	IMPORT_C CEikToolBar();
	
	/**
	 * Completes construction of a default-constructed toolbar.
	 *
     * The command observer interface defines a method for creating custom
     * controls on the toolbar from user-defined IDs specified in the
     * resource @c aResourceId.
     *
     * IDs for controls which cannot be constructed using
     * @c EikControlFactory::CreateByTypeL() are passed to this object's
     * command observer for construction.
     *
     * Applications requiring custom controls in their toolbars should
     * override their AppUI's @c CreateCustomCommandControlL() method,
     * inherited from @c MEikCommandObserver.
     *
     * @param aCommandObserver Sets the command observer for this toolbar.
     *                         The observer's @c ProcessCommandL()
     *                         function is invoked when a toolbar command
     *                         is invoked by the user.
     *                         @see MEikCommandObserver::ProcessCommandL().
     *                         Typically the observer is the
     *                         application's AppUI.
     *
     * @param aResourceId      The ID of a @c TOOLBAR or @c TOOLBAND
     *                         resource structure.
     *
     * @param aBoundingRect    Defines the rectangle to which the toolbar's
     *                         extent must be limited. This is typically given
     *                         by @c CEikAppUi::ClientRect(), which returns
     *                         the extent of the whole application window,
     *                         less the extent of any toolbars that already
     *                         exist and are owned by the AppUI.
     *
     * @panic EIKCOCTL-36      If the control on the toolbar cannot be
     *                         constructed.
     */
	IMPORT_C void ConstructL( MEikCommandObserver* aCommandObserver,
	                          TInt aResourceId,
	                          const TRect& aBoundingRect );
	
	/**
	 * Creates a toolbar from a resource definition,
	 * but does not set its extent or activate it.
	 *
	 * This function is used by @c ConstructL(), applications will
	 * not typically need to use it.
	 *
	 * @param aCommandObserver Specifies the object in which
	 *                         @c HandleCommandL() is called when a toolbar
	 *                         command is invoked, typically the application's
	 *                         AppUI.
	 *
	 * @param aResourceId      The resource that defines the toolbar.
	 *
	 * @panic EIKCOCTL-36      If the control on the toolbar cannot be
	 *                         constructed.
	 */
	IMPORT_C void StaticConstructL( MEikCommandObserver* aCommandObserver,
	                                TInt aResourceId );
	
	/**
	 * Sets the toolbar's command observer.
	 * Applications will not typically need to use this function.
	 *
	 * @param aCommandObserver The command observer for this toolbar.
	 *                         When a command is invoked in the toolbar,
	 *                         @c HandleCommandL() is called in the observer.
	 */
	IMPORT_C void SetCommandObserver(MEikCommandObserver* aCommandObserver);
	
	/**
	 * Sets the button co-ordinator for a group of buttons in a toolbar.
	 *
	 * @param aId           Command identifying a toolbar button. 
	 * @param aCount        The number of buttons in the group. 
	 * @param aCoordinator  The button coordinator. 
	 */
	IMPORT_C void CoordinateButtons( TInt aId,
	                                 TInt aCount,
	                                 TEikButtonCoordinator* aCoordinator );
	
	/**
	 * Sets the state of the specified button and draws the button
	 * to show the new state.
	 *
	 * @param aId    The command that identifies the button.
	 * @param aState @c ETrue to set the button, @c EFalse to clear the button.
	 */
	IMPORT_C void SetButtonStateOn(TInt aId,TBool aState);
	
	/**
	 * Delays activation of the toolbar when constructed.
	 *
	 * This function sets the toolbar flag @c EEikToolBarDelayActivation.
	 * If this flag is set when @c ConstructL() is called on the toolbar,
	 * the toolbar will be constructed but not activated.
	 *
	 * The application can subsequently activate the toolbar by calling
	 * @c CCoeControl::ActivateL().
	 *
	 * @return @c ETrue to delay activation of the toolbar.
	 */
	IMPORT_C TBool DelayActivation() const;
	
public: /** From @c CCoeControl. */

    /**
	 * Second-phase construction from a resource.
	 * This is called by @c StaticConstructL() with an appropriate reader.
	 *
	 * From @c CCoeControl
	 *
	 * @param aReader     A resource reader pointing at a @c TOOLBAR or
	 *                    @c TOOLBAND resource defining the toolbar.
	 * @panic EIKCOCTL-36 If the control on the toolbar cannot be constructed.
	 */
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	
	/**
	 * Sets the toolbar dimmed or not dimmed.
	 * Dimming usually indicates that user input is not accepted.
	 *
	 * From @c CCoeControl
	 *
	 * @param aDimmed @c ETrue to set as dimmed ,
	 *                @c EFalse to set as not dimmed.
	 */
	IMPORT_C void SetDimmed(TBool aDimmed);
	
	/**
	 * Gets the list of logical colours used to draw the control.
	 * Appends the list to @c aColorUseList paired with an explanation
	 * of how the colours are used.
     *
	 * From @c CCoeControl
	 *
	 * @param[in,out] aColorUseList The list of logical colours. 
	 */
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	
	/**
     * Handles a change to the control's resources.
     *
     * The types of resources handled are those which are shared across
     * the environment, e.g. colours or fonts. For colour scheme changes,
     * @c DrawDeferred() is called in order to redraw the control.
     *
     * If overriding this method, the implementation must
     * include a base call to this method.
     *
     * From @c CCoeControl.
	 *
     * @param aType The type of resource that has changed.
     */
	IMPORT_C void HandleResourceChange(TInt aType);
	
	/**
     * Handles pointer events.
     *
     * This function gets called whenever a pointer event occurs in the 
     * control, i.e. when the pointer is within the control's extent, or when 
     * the control has grabbed the pointer.
     * 
     * If overriding this method, the implementation must 
     * include a base call to this method.
     *
     * From @c CCoeControl.
     *
     * @param aPointerEvent The pointer event.
     */
	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	
public: /** From @c CEikControlGroup. */

    /**
     * Adds a control to the control group.
     *
	 * From @c CEikControlGroup
	 *
	 * @param aControl    The control to add to the control group
	 * @param aId         The control's ID.
	 * @panic EIKCOCTL-26 If the control does not exist.
	 */
	IMPORT_C void AddControlL(CCoeControl* aControl,TInt aId);
	
	/**
	 * Adds a control wrapped with its ID and length to the control group.
	 *
	 * From @c CEikControlGroup
	 *
	 * @param aGroupControl The wrapped control to add.
	 * @panic EIKCOCTL-26   If the control does not exist.
	 */
	IMPORT_C void AddControlL(TEikGroupControl& aGroupControl);
	
public: // but not exported

    /**
	 * Adds a control type to the control type array.
	 *
	 * @internal
	 *
	 * @param aType The control type to be added.
	 */
	void AddControlTypeL(TInt aType);
	
	/**
	 * Removes a control type from the control type array.
	 *
	 * @internal
	 *
	 * @param aIndex Index of the control type to be removed
	 *               in the control type array.
	 */
	void RemoveControlType(TInt aIndex);
	
	/**
	 * Used to check if a control is a button type control or not.
	 *
	 * @internal
	 *
	 * @param  aIndex Index of the control.
	 * @return @c ETrue, if the control is a button type control.
	 */
	TBool ControlIsButton(TInt aIndex) const;
	
public: /** From @c MEikButtonGroup. */

    /**
     * Sets the toolbar's bounding rectangle.
     * This function has a different effect on the toolbar's extent,
     * depending on whether the toolbar is vertical or horizontal.
     *
     * For a vertical toolbar, sets the toolbar height to equal the
     * height of the bounding rectangle.
     *
     * For a horizontal toolbar (toolband), sets the toolband width
     * to equal the width of the bounding rectangle.
     *
	 * From @c MEikButtonGroup
	 *
	 * @param aBoundingRect The toolbar's bounding rectangle.
	 */
	IMPORT_C void SetBoundingRect(const TRect& aBoundingRect);
	
	/**
	 * Shrinks a rectangle to exclude the toolbar area.
     * This function reduces the size of the rectangle passed into the
     * function so that on return, the area occupied by the toolbar or toolband
     * is removed from the rectangle. It is provided to prevent drawing
     * over an existing toolbar or toolband.
     *
	 * From @c MEikButtonGroup
	 *
	 * @param[in,out] aBoundingRect Specifies a rectangle which, on return,
	 *                              is shrunk to exclude the toolbar’s extent.
	 */
	IMPORT_C void ReduceRect(TRect& aBoundingRect) const;
	
protected:

    /**
     * Writes the internal state of the control and its
     * components to @c aWriteStream.
     * Does nothing in release mode.
     *
     * Designed to be overridden and base called from subclasses.
     *
     * From @c CCoeControl
     *
     * @param[in,out] aWriteStream A connected write stream.
     */
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
	
private:

	CEikCommandButton* ButtonByIndex(TInt aIndex) const;	
	void SetCurrentId(TInt aPosition,TInt aId);	
	TInt CurrentId(TInt aPosition) const;	
	TEikGroupControl& GroupControlByIndex(TInt aIndex) const;	
	TInt IndexFromPosition(TInt aPos) const;
	
private: /** From @c MEikButtonGroup */

	void SetCommandL( TInt aPosition,
	                  TInt aCommandId,
	                  const TDesC* aText,
	                  const CFbsBitmap* aBitmap,
	                  const CFbsBitmap* aMask );
	                  
	void SetCommandL(TInt aPosition,TInt aResourceId);
	void SetCommandSetL(TInt aResourceId);
	void AddCommandL( TInt aPosition,
	                  TInt aCommandId,
	                  const TDesC* aText,
	                  const CFbsBitmap* aBitmap,
	                  const CFbsBitmap* aMask );
	void AddCommandToStackL( TInt aPosition,
	                         TInt aCommandId,
	                         const TDesC* aText,
	                         const CFbsBitmap* aBitmap,
	                         const CFbsBitmap* aMask );
	void AddCommandToStackL(TInt aPosition,TInt aResourceId);
	void AddCommandSetToStackL(TInt aResourceId);
	void SetDefaultCommand(TInt aCommandId);
	TSize CalcMinimumSizeL(TInt aResourceId);
	void RemoveCommandFromStack(TInt aPosition,TInt aCommandId);
	TInt CommandPos(TInt aCommandId) const;
	void DimCommand(TInt aCommandId,TBool aDimmed);
	TBool IsCommandDimmed(TInt aCommandId) const;
	void MakeCommandVisible(TInt aCommandId,TBool aVisible);
	TBool IsCommandVisible(TInt aCommandId) const;
	CCoeControl* AsControl();
	const CCoeControl* AsControl() const;
	CCoeControl* GroupControlById(TInt aCommandId) const;
	CEikCommandButton* GroupControlAsButton(TInt aCommandId) const;
	TInt CommandId(TInt aCommandPos) const;
	TInt ButtonCount() const;
	TUint ButtonGroupFlags() const;

    void SetMSKCommandObserver(MEikCommandObserver* aCommandObserver);
    void DimCommandByPosition(TInt aPosition,TBool aDimmed);
    TBool IsCommandDimmedByPosition(TInt aPosition) const;
    void MakeCommandVisibleByPosition(TInt aPosition,TBool aVisible);
    TBool IsCommandVisibleByPosition(TInt aPosition) const;
    void AnimateCommandByPosition(TInt aPosition);

private: /** From @c MCoeControlObserver */
	IMPORT_C void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEvent);
	
private:
	IMPORT_C void Reserved_2();
	
private: /** From @c CAknControl */

    IMPORT_C void* ExtensionInterface( TUid aInterface );
private:
	void BaseConstructL();
	TInt ControlCount() const;
private:
	TInt                    iToolBarFlags;
	MEikCommandObserver*    iCommandObserver;
	CCoeBrushAndPenContext* iBrushAndPenContext;
	CArrayFix<TInt>*        iControlTypes; 
	};

#endif // __EIKTBAR_H__
