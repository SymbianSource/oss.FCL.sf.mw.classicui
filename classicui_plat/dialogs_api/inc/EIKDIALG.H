/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef __EIKDIALG_H__
#define __EIKDIALG_H__

#ifndef __COECOBS_H__
#include <coecobs.h>
#endif

#ifndef __COECCNTX_H__
#include <coeccntx.h>
#endif

#ifndef __EIKBCTRL_H__
#include <eikbctrl.h>
#endif

#ifndef __EIKDPOBS_H__
#include <eikdpobs.h>
#endif

#ifndef __BADESCA_H__
#include <badesca.h>
#endif 

#ifndef __GULFTFLG_HRH__
#include <gulftflg.hrh>
#endif



//
// Header files needed by deprecated interfaces.
//

#ifndef __EIKBUTB_H__
#include <eikbutb.h>
#endif

#ifndef __EIKBTGPC_H__
#include <eikbtgpc.h>
#endif

#include <AknPopupFader.h>

// constant definitions
const TInt KAknMediatorFacade(0x10275076);


class CEikMover;
class CEikCaptionedControl;
class CEikCapCArray;
class CEikDialogPageSelector;
class CEikButtonGroupContainer;
class CEikDialogButtonCommandObserver;
class MEikCommandObserver;
class CAknDialog;
class CAknNoteDialog;

struct SEikControlInfo;

class  CEikDialogExtension ;
// <SKIN>
class CAknsListBoxBackgroundControlContext ;
//
// Forward declarations needed by deprecated interfaces.
//

class CEikLabel;
class CGlobalText;
class MAknDialogMediatorObserver;
struct SEikRange;
struct SEikDegreesMinutesDirection;


/**
 * The @c CEikDialog class provides an instantiable base class for dialogs. 
 * Controls can be added directly to this class but it is normal to create
 * a subclass to handle the controls appearing on the dialog dynamically.
 */
class CEikDialog : public CEikBorderedControl,
                   public MCoeControlObserver,
                   public MEikDialogPageObserver,
                   public MCoeControlContext, 
                   public MAknFadedComponent
    { 

public:

    DECLARE_TYPE_ID(0x10282EA8)
    
	/**
     * C++ default constructor.
     */
    IMPORT_C CEikDialog(); 

    /**
     * Destructor.
     */
	IMPORT_C ~CEikDialog(); 

    /**
     * Loads, displays, and destroys the dialog.
     *
     * This function loads the specified dialog from a resource and displays
     * it. The method then destroys the dialog when it exits, therefore there
     * is no need for the application program to destroy the dialog.
     *
     * In the resource file, use the @c EEikBidOk dialog button ID for an 
     * OK/Done/Continue button and @c EEikBidCancel for a Cancel button.
     *
     * The function returns immediately unless @c EEikDialogFlagWait has been 
     * specified in the @c DIALOG resource. If @c EEikDialogFlagWait is 
     * specified, it returns when the dialog exits.
     * 
     * @param aResourceId The resource ID of the dialog to load.
     * @return Zero, unless it is a waiting dialog. For a waiting dialog, 
     *         the return value is the ID of the button that closed the dialog, 
     *         or zero if it was the cancel button (@c EEikBidCancel).
     */
	IMPORT_C virtual TInt ExecuteLD(TInt aResourceId);
	
    /**
     * Prepares the dialog, constructing it from the specified resource.
     * 
     * @param aResourceId The resource ID of the dialog.
     */
    IMPORT_C virtual void PrepareLC(TInt aResourceId);

    /**
     * Reads the dialog resources into the dialog, constructing it from the specified resource.
     * The function is only to help loading dialog resources and 
     * extracting dialog data, in other cases use (@c PrepareLC()).
     * Unlike PrepareLC(), it does not add the dialog to control stack.
     * @since 3.2
     * 
     * @param aResourceId The resource ID of the dialog.
     */
    IMPORT_C void ReadResourceLC(TInt aResourceId);

    /**
     * Runs the dialog and returns the ID of the button used to dismiss it.
     *
     * The dialog is destroyed on exit.
     *
     * This function is called by the dialog framework (@c ExecuteLD()) to 
     * perform dynamic construction (layout) and to display/destroy the 
     * dialog. Static construction of the dialog must already be complete 
     * before this function is called, e.g. using @c PrepareLC().
     *
     * The function returns immediately unless @c EEikDialogFlagWait has 
     * been specified in the @c DIALOG resource. If @c EEikDialogFlagWait is    
     * specified it returns when the dialog exits.
     *
     * @return The ID of the button used to dismiss the dialog.
     */
    IMPORT_C virtual TInt RunLD();

    /**
     * Sets the dialog title text from a descriptor.
     *
     * @deprecated
     * @param aText The descriptor containing the new title text.
     */
    IMPORT_C void SetTitleL(const TDesC& aText);
	
    /**
     * Sets the dialog title text from a resource.
     *
     * @deprecated
     * @param aResourceId The ID of the resource containing the title text.
     */
    IMPORT_C void SetTitleL(TInt aResourceId);
	
    /**
     * Sets the specified page to be dimmed or undimmed. The page is redrawn
     * immediately.
     *
     * @param aPageId The ID of the page to be dimmed.
     * @param aDimmed @c ETrue to dim the page, @c EFalse to un-dim it.
     */
    IMPORT_C void SetPageDimmedNow(TInt aPageId,TBool aDimmed);
	
    /**
     * Sets the specified dialog line to a non-focusing state. After this
     * function is called, the line will never be given keyboard focus.
     * 
     * @param aControlId The ID of the control in the line which is to be 
     *        set as non-focusing.
     */
    IMPORT_C void SetLineNonFocusing(TInt aControlId);
	
    /**
     * Dims and deactivates, or un-dims and re-activates, the specified line.
     *
     * @param aControlId The ID of the line to dim or un-dim.
     * @param aDimmed @c ETrue to dim the line, @c EFalse to un-dim it.
     */
    IMPORT_C void SetLineDimmedNow(TInt aControlId,TBool aDimmed);
	
    /**
     * Makes the specified control visible or invisible. This function affects
     * the specified control, the visibility of the caption is not affected.
     *
     * @param aControlId The ID of the control to make visible or invisible.
     * @param aVisible @c ETrue to make the control visible. 
     *        @c EFalse to make the control invisible.
     */
    IMPORT_C void MakeLineVisible(TInt aControlId,TBool aVisible);
	
    /**
     * Makes the whole specified line visible and active or invisible and 
     * inactive. This function affects both the specified control and
     * the caption.
     *
     * @param aControlId The ID of the control on the line to make visible 
     *        or invisible.
     * @param aVisible @c ETrue to make the line visible. @c EFalse to make the 
     *        line invisible.
     */
    IMPORT_C void MakeWholeLineVisible(TInt aControlId,TBool aVisible);
	
    /**
     * Deletes the specified dialog line.
     *
     * @param aControlId The dialog line to delete.
     * @param aRedraw Whether to redraw the page. Default value is @c ETrue.
     */
    IMPORT_C void DeleteLine(TInt aControlId, TBool aRedraw=ETrue);
	
    /**
     * Inserts a line in the dialog. The function takes as arguments the page
     * and line index at which the line is to be inserted, and the resource used
     * to construct it.
     * 
     * @param aIndex The index at which the line is to be inserted.
     * @param aResourceId The ID of the resource which defines the line.
     * @param aPageId The page on which the line is to be added.
     */
    IMPORT_C void InsertLineL(TInt aIndex,TInt aResourceId,TInt aPageId=0);
	
    /**
     * Makes the specified panel button visible or invisible.
     *
     * @param aButtonId The ID of the panel button to make visible or invisible.
     * @param aVisible @c ETrue to make the panel visible. 
     *        @c EFalse to make it invisible.
     */
    IMPORT_C void MakePanelButtonVisible(TInt aButtonId,TBool aVisible);

    /**
     * Tries to change focus to the specified line. Fails if the line ID is not
     * valid. Calls @c PrepareForFocusTransitionL() before focus is given to
     * the line.
     *
     * @param aControlId The ID of the line to focus.
     */
    IMPORT_C void TryChangeFocusToL(TInt aControlId);
	
    /**
     * Switches the latent line. The latent line is switched from
     * @c aNoLongerLatent to @c aBecomesLatent. If dialog lines are latent they
     * are not visible and are not taken into account when laying out the
     * dialog. Latent lines can then be swapped around on the dialog later.
     *
     * @param aBecomesLatent The line ID of the line to become latent.
     * @param aNoLongerLatent The line ID of the line to that is no longer 
     *        latent.
     */
    IMPORT_C void SwitchLineLatency(TInt aBecomesLatent,TInt aNoLongerLatent);
	
    /**
     * Sets the specified page to be densely packed, or normally packed. This
     * reduces the spacing between the dialog's lines.
     *
     * @param aPageId The ID of the page to be densely packed.
     * @param aDensePacking @c ETrue for dense packing. @c EFalse for normal 
     *        packing.
     */
    IMPORT_C void SetPageDensePacking(TInt aPageId,TBool aDensePacking);
	
    /**
     * Dynamically constructs a dialog with the specified flags and buttons 
     * and with a single activated empty page with ID 0. The dialog is therefore
     * ready to dynamically add lines to.
     *
     * @param aFlags Dialog flags.
     * @param aButtonsId Dialog buttons.
     */
    IMPORT_C void ConstructAutoDialogLC(TInt aFlags,TInt aButtonsId);
	
    /**
     * Sets controllers return value.
     *
     * @param[in] aControlId Control identifier for wanted caption controller.
     * @param[in] aControlType Type of control.
     * @param[out] aReturnValue Controllers return value.
     * @deprecated
     */
    IMPORT_C void DeclareItemAuto(TInt aControlId,
                                  TInt aControlType,
                                  TAny* aReturnValue);
	
    /**
     * Lays out the dialog, setting it to take its preferred size and 
     * position for the screen.
     *
     * @since 5.1 
     */
    IMPORT_C void Layout();
	
    /**
     * Gets the preferred size of a dialog. The maximum size that the dialog
     * must fit within must be specified, e.g. the size of the physical screen.
     *
     * @param aMaxSize The maximum size of the area in which the dialog must
     *        fit.
     * @return The preferred size of the dialog.
     */
    IMPORT_C TSize PreferredSize(const TSize& aMaxSize) const;
	
    /**
     * Creates a control line on the page ID specified active page in 
     * the dialog. 
     * The line can thereafter be accessed through the identifier @c aControlId.
     * A control of type @c aControlType is created by the control factory and
     * the return value of the line set to @c aReturnValue. If the value of 
     * @c aControlType is not known to the control factory then the construction
     * of the control must be handled by @c CreateCustomControlL().
     *
     * @param aCaption The caption to appear in the dialog line.
     * @param aControlId The ID of the active page on which the control 
     *        line is to be created.
     * @param aControlType The type of control to create.
     * @param aReturnValue Deprecated. A random pointer.
     * @return A pointer to the newly created control.
     */
    IMPORT_C CCoeControl* CreateLineByTypeL(const TDesC& aCaption,
                                            TInt aControlId,
                                            TInt aControlType,
                                            TAny* aReturnValue);
	
    /**
     * Creates a control line on the caption specified active page 
     * in the dialog. 
     * The line can thereafter be accessed through the identifier 
     * @c aControlId.
     * A control of type @c aControlType is created by the control 
     * factory and the return value of the line set to @c aReturnValue.
     * If the value of @c aControlType is not known to the control factory
     * then the construction of the control must be handled by 
     * @c CreateCustomControlL().
     * 
     * @param aCaption The active page on which the control line is 
     *        to be created.
     * @param aPageId The ID of the active page on which the control line is
     *        to be created.
     * @param aControlId The ID of the control. After the line is created this
     *        can be used to access it.
     * @param aControlType The type of control to create.
     * @param aReturnValue Deprecated. A random pointer.
     * @return A pointer to the newly created control.
     */
    IMPORT_C CCoeControl* CreateLineByTypeL(const TDesC& aCaption,
                                            TInt aPageId,
                                            TInt aControlId,
                                            TInt aControlType,
                                            TAny* aReturnValue);
	
    /**
     * Sets the specified control's caption text from a descriptor.
     * 
     * @param aControlId The ID of the control for which the caption 
     *        text is being set.
     * @param aText The text for the caption.
     */
    IMPORT_C void SetControlCaptionL(TInt aControlId,const TDesC& aText);
	
    /**
     * Sets the specified control's caption text from a resource.
     *
     * @param aControlId The ID of the control for which the caption 
     *        text is being set.
     * @param aResourceId The ID of the resource containing the text for
     *        the caption.
     */
    IMPORT_C void SetControlCaptionL(TInt aControlId,TInt aResourceId);
	
    /**
     * Gets a pointer to the specified control's caption.
     *
     * @param aControlId The ID of the control for which the label is required.
     * @return A pointer to the caption.
     */
    IMPORT_C CEikLabel* ControlCaption(TInt aControlId) const;

    /**
     * Returns a pointer to the specified control. 
     * 
     * Panics if the control ID is invalid. Does not imply transfer 
     * of ownership. 
     *
     * @param aControlId The ID of the control for which a pointer is required.
     * @return A pointer to the control with ID aControlId.
     */ 
    IMPORT_C CCoeControl* Control(TInt aControlId) const;

    /**
     * Gets a pointer to the specified control. 
     * 
     * @param aControlId The ID of the control for which a pointer is required.
     * @return A pointer to the control with ID aControlId, or 
     *         NULL if it doesn't exist.
     */
    IMPORT_C CCoeControl* ControlOrNull(TInt aControlId) const;
	
    /**
     * Gets a reference to the dialog's command button container.
     *
     * @return The dialog's button group container.
     */
    IMPORT_C CEikButtonGroupContainer& ButtonGroupContainer() const;
	
    /**
     * Gets a reference to the dialog title bar.
     *
     * @return A reference to the dialog title bar.
     */ 
    IMPORT_C CEikMover& Title() const;
	
    /**
     * Gets a page id for the current page.
     * 
     * @return Page id.
     */
    IMPORT_C TInt ActivePageId() const;
    
    /**
     * Activates the first page on the dialog. At least one page must be active
     * before this method can be used.
     */
    IMPORT_C void ActivateFirstPageL() const;



// To Support Edit/View state switch for forms (Sapphire DFRD)
// This breaks Binary Compatibility

    /**
     * Sets the dialog to either editable or uneditable
     *
     * @param aEditable @c ETrue if dialog is editable.
     *        @c EFalse if dialog is uneditable.
     */
	IMPORT_C void SetEditableL( TBool aEditable ) ;
	
    /**
     * Checks if the dialog is editable.
     * 
     * @return @c ETrue if editable.
     */
    IMPORT_C TBool IsEditable() const ;


public: // from CCoeControl

    /**
     * From @c CCoeControl.
     *
     * Handles a key event. Overrides @c CCoeControl::OfferKeyEventL().
     *
     * @param aKeyEvent The key event.
     * @param aType The type of key event: @c EEventKey, @c EEventKeyUp 
     *        or @c EEventKeyDown.
     * @return Indicates whether or not the key event was used by this control.
     *         @c EKeyWasConsumed if the control takes action on the key event
     *         or @c EKeyWasNotConsumed otherwise.
     */
    IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,
                                         TEventCode aType);
	
    /**
     * From @c CCoeControl.
     *
     * Responds to a change in focus.
     *
     * This is called whenever the control gains or loses focus, as a result 
     * of a call to @c SetFocus(). A typical use of @c FocusChanged() is to 
     * change the appearance of the control, for example by drawing a focus 
     * rectangle around it.
     *
     * The default implementation is empty, and should be overridden by the 
     * @c CCoeControl-derived class.
     *
     * @param aDrawNow Contains the value that was passed to it by 
     *        @c SetFocus().
     */
    IMPORT_C void FocusChanged(TDrawNow aDrawNow);
	
    /**
     * From @c CCoeControl.
     *
     * Gets the list of logical colours used to draw the control.
     *
     * The list includes an explanation of how each colour is used. 
     * The default implementation is empty.
     *
     * If overriding @c GetColorUseListL(), the implementation must include 
     * a base call to @c CCoeControl's @c GetColorUseListL().
     * 
     * @since ER5U
     * @param &aColorUseList The colour list.
     */
    IMPORT_C virtual void GetColorUseListL(
        CArrayFix<TCoeColorUse>& aColorUseList) const; 
        // not available before Release 005u
	
    /**
     * From @c CCoeControl.
     *
     * Handles a change to the control's resources.
     * 
     * The types of resources handled are those which are shared across the 
     * environment, e.g. colours or fonts. For colour scheme changes, 
     * @c DrawDeferred() is called in order to redraw the control.
     * 
     * If overriding @c HandleResourceChange(), the implementation must include
     * a base call to @c CCoeControl's @c HandleResourceChange().
     * 
     * @since ER5U
     * @param aType A message UID value.
     */ 
    IMPORT_C virtual void HandleResourceChange(TInt aType);			
            // not available before Release 005u

    /**
     * From @c CCoeControl.
     *
     * Gets the control's input capabilities.
     * 
     * Classes that override @c CCoeControl::OfferKeyEventL() should also 
     * override this function, returning a @c TCoeInputCapabilities object 
     * whose attributes correspond to the behaviour of the @c OfferKeyEventL() 
     * function. The default implementation returns 
     * @c TCoeInputCapabilities::ENone.
     * 
     * It is not necessary to call @c InputCapabilities() on any component 
     * controls from inside a class's @c InputCapabilities() function. This 
     * is done automatically by the UI Control Framework.
     * 
     * @since ER5U
     * @return The control's input capabilities. 
     */
    IMPORT_C TCoeInputCapabilities InputCapabilities() const;
	
    /**
     * From @c CCoeControl.
     *
     * Sets the dialog visibility
     * 
     * @param aVisible @c ETrue control is visible.
     *        @c EFalse control is invisible.
     */
    IMPORT_C void MakeVisible(TBool aVisible);
    
    /**
     * From @c CCoeControl.
     *
     * Handles pointer events.
     *
     * This function gets called whenever a pointer event occurs in the 
     * control, i.e. when the pointer is within the control's extent, 
     * or when the control has grabbed the pointer. The control should 
     * implement this function to handle pointer events.
     *
     * Note: events of type @c EButton1Down are processed before 
     * @c HandlePointerEventL() is called, in order to transfer keyboard 
     * focus to the control in which the @c EButton1Down event occurred.
     *
     * If overriding @c HandlePointerEventL(), the implementation must include
     * a base call to @c CCoeControl's @c HandlePointerEventL().
     *
     * @param aPointerEvent The pointer event.
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

protected: // from MEikDialogPageObserver

    /**
     * From @c MEikDialogPageObserver.
     *
     * Should be implemented to prepare for focus transition from the 
     * current line. 
     *
     * For example to validate the contents of the current control.
     */
    IMPORT_C virtual void PrepareForFocusTransitionL();
	
    /**
     * From @c MEikDialogPageObserver.
     * 
     * Should be implemented to take any action required when the active 
     * dialog page is changed.
     *
     * Not implemented.
     * 
     * @param aPageId The ID of the page being switched to.
     */
    IMPORT_C virtual void PageChangedL(TInt aPageId);
	
    /** 
     * From @c MEikDialogPageObserver
     * 
     * Should be implemented to take any action required when the current 
     * line is changed to @c aControlId. 
     *
     * Not implemented.
     *
     * @param aControlId The ID of the control being switched to.
     */
    IMPORT_C virtual void LineChangedL(TInt aControlId);

public: // from MEikDialogPageObserver
	
    /** 
     * From @c MEikDialogPageObserver.
     *
     * Creates a control line in the dialog.on the active page with caption
     * text @c aCaption.
     * The line can thereafter be accessed through the identifier 
     * @c aControlId.
     * A control of type @c aControlType is created by the @c Eikon 
     * control factory and the return value of the line set to @c aReturnValue.
     * If the value of @c aControlType is not known to the Eikon control 
     * factory then the construction of the control must be handled by 
     * @c CreateCustomControlL.
     * 
     * @param aControlType The type of the custom control.
     * @return Information for the custom control.
     */
    IMPORT_C virtual SEikControlInfo CreateCustomControlL(TInt aControlType);
	
    /**
     * From @c MEikDialogPageObserver.
     * 
     * For forms only:
     * Ths should be overriden with mappings between the base control types 
     * that form knows how to layout.
     * 
     * Always returns @c MEikDialogPageObserver::EUnknownType. 
     *
     * @param aControlType Not used.
     * @return Current implementation always 
     *         returns @c MEikDialogPageObserver::EUnknownType.
     */
    IMPORT_C MEikDialogPageObserver::TFormControlTypes 
        ConvertCustomControlTypeToBaseControlType(TInt aControlType) const;
	
    /**
     * From @c MEikDialogPageObserver. 
     * 
     * Should be implemented to get the custom auto value for the custom control
     * @c aControl of type @c aControlType with return value @c aReturnValue. 
     *
     * This method is included in the interface to support deprecated legacy
     * code only.
     *
     * Not implemented. 
     * 
     * @param aReturnValue The custom controls return value.
     * @param aControlType The type of the custom control.
     * @param aControl The control whose auto value is being retrieved.
     * @deprecated
     */
    IMPORT_C virtual void GetCustomAutoValue(TAny* aReturnValue,
                                             TInt aControlType,
                                             const CCoeControl* aControl);

protected: // from MCoeControlContext

    /**
     * From @c MCoeControlContext.
     * 
     * Initialises graphics context settings.
     *
     * This function should be implemented by derived classes to initialise
     * the graphics context, given by @c aGc, with the required settings. 
     *
     * @param aGc The graphics context to be initialised.
     */
	IMPORT_C void PrepareContext(CWindowGc& aGc) const;

protected: //from CCoeControl

    /**
     * From @c CCoeControl.
     *
     * Writes the internal state to the given stream.
     * 
     * @param[out] aWriteStream Target stream.
     */ 
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;

private: // from CCoeControl

	IMPORT_C void Draw(const TRect& aRect) const;

protected:

    /**
     * Returns the number of the control components.
     * 
     * In Avkon returns 2 as the button group container is not internal.
     *
     * @return Number of control components. 
     */
	IMPORT_C TInt CountComponentControls() const;

    /**
     * Returns a pointer to the component control at the specified index 
     * in the component control list.
     *
     * Does not imply transfer of ownership.
     *
     * @param aIndex The index of the required component control.
     * @return The required component control.
     */
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;

protected:

    /**
     * Gets number of lines in the specified page. 
     * 
     * @param aPageIndex Index of the page container. 
     * @return The number of lines in the page.
     */
	IMPORT_C TInt GetNumberOfLinesOnPage(TInt aPageIndex) const;

    /** 
     * Gets number of pages in the page selector.
     * 
     * @return The number of pages. 
     */ 
	IMPORT_C TInt GetNumberOfPages() const;

    /**
     * Gets specified line from specified page.
     *
     * @param aLineIndex Index of the requested line. 
     * @param aPageIndex Index of the requested page. 
     * @return The wanted line.
     */ 
	IMPORT_C CEikCaptionedControl* GetLineByLineAndPageIndex(TInt aLineIndex, 
                                                      TInt aPageIndex) const;

private:
	
    IMPORT_C void SizeChanged();
	
    IMPORT_C TSize MinimumSize();
	
    IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	
    IMPORT_C void Reserved_2();

private:

    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );

protected: // from MCoeControlObserver

    /**
     * From @c MCoeControlObserver. 
     *
     * Handles control events. 
     * 
     * The default implementation handles events of type @c EEventStateChanged,
     * @c EEventInteractionRefused, and @c EEventPrepareFocusTransition by 
     * calling @c HandleControlStateChangeL(), @c HandleInteractionRefused(),
     * and @c PrepareForFocusTransitionL() respectively.
     *
     * Overrides @c MCoeControlObserver::HandleControlEventL().
     * 
     * @param aControl The control reporting the event.
     * @param aEventType The event type.
     */ 
	IMPORT_C void HandleControlEventL(CCoeControl* aControl,
                                      TCoeEvent aEventType);

protected: // new functions

    /**
     * Tries to exit the dialog when the specified button is pressed, if this 
     * button should exit the dialog.
     *
     * See @c OkToExitL() to determine which buttons can exit the dialog.
     * 
     * This will fail if user exit is prevented by the 
     * @c EEikDialogFlagNoUserExit flag. If the @c EEikDialogFlagNotifyEsc flag
     * is not set and the dialog has been cancelled it immediately deletes 
     * itself.
     * 
     * @param aButtonId The id of the pressed button.
     */
    IMPORT_C void TryExitL(TInt aButtonId);
	
    /**
     * Adjusts the IDs of all controls on a specified page. 
     *
     * The adjustment consists of incrementing all the control IDs by 
     * @c aControlIdDelta.
     * 
     * @param aPageId The page on which the control IDs are to be adjusted.
     * @param aControlIdDelta The amount to increment the IDs.
     */
    IMPORT_C void AdjustAllIdsOnPage(TInt aPageId,TInt aControlIdDelta);
	
    /** 
     * Protected constructor creates a sleeping dialog from a resource. 
     *
     * A sleeping dialog is one which can be displayed at any time since 
     * its memory resources are pre-allocated.
     * 
     * @param aResourceId The resource ID of the dialog to be constructed.
     */ 
    IMPORT_C void ConstructSleepingDialogL(TInt aResourceId);
	
    /**
     * Protected construction of a high priority sleeping dialog from 
     * a resource. 
     *
     * A sleeping dialog is one which can be displayed at any time since 
     * its memory resources are pre-allocated. 
     * 
     * @param aResourceId The resource ID of the dialog to be constructed.
     */ 
    IMPORT_C void ConstructSleepingAlertDialogL(TInt aResourceId);
	
    /** 
     * Rouses a sleeping dialog by dynamically constructing the dialog and
     * then bringing it to the front.
     *
     * Derived dialogs should pre-allocate any memory they need for 
     * initialisation during construction via @c ConstructFromResourceL() 
     * for each individual control. Derived versions of @c PreLayoutDynInitL()
     * cannot rely on allocating any further memory.
     *
     * @return Zero.
     */ 
    IMPORT_C TInt RouseSleepingDialog();

    /**
     * Exits sleeping dialog without deleting it.
     */ 
    IMPORT_C void ExitSleepingDialog();
	
    /** 
     * Gets the ID of the control in the focused line.
     * 
     * @return Current control ID.
     */ 
    IMPORT_C TInt IdOfFocusControl() const;
	
    /**
     * Gets the line index of the specified control.
     *
     * The control must be on the active page.
     *
     * @param aControl The control for which the line index is required.
     * @return The line index, or @c KErrNotFound if the control is not on the
     *         active page.
     */ 
    IMPORT_C TInt FindLineIndex(const CCoeControl& aControl) const;

    /**
     * Gets a pointer to the line containing the specified control. 
     *
     * This does not imply transfer of ownership from the dialog.
     *
     * @param aControlId The ID of the control.
     * @return A pointer to the line containing the control identified by
     *         @c aControlId.
     */ 
    IMPORT_C CEikCaptionedControl* Line(TInt aControlId) const;

    /**
     * Gets a pointer to the current line.
     *
     * This does not imply transfer of ownership from the dialog.
     *
     * @return A pointer to the current line.
     */
    IMPORT_C CEikCaptionedControl* CurrentLine() const;
	
    /**
     * Rotates the focus by a specified number of steps.
     *
     * Each line is a step, as are dialog tabs.
     *
     * @param aDelta The number of steps.
     * @return @c ETrue if rotation of focus is successful, 
     *         @c EFalse if there are no lines in the dialog or the rotation is
     *         otherwise unsuccessful.
     */ 
    IMPORT_C TBool RotateFocusByL(TInt aDelta);
	
    /**
     * Gets the index of the dialog's active page.
     *
     * Pages are indexed from 0 in the order they are added.
     *
     * @return The index of the active page.
     */ 
    IMPORT_C TInt ActivePageIndex() const;
	
    /**
     * Recalculates the minimum sizes of the lines on the active page.
     *
     * Overrides @c CCoeControl::ResetLineMinimumSizes().
     */
    IMPORT_C void ResetLineMinimumSizes();
	
    /**
     * Swaps the dialog's button group container with a new container.
     *
     * The dialog takes ownership of the new container. A pointer to the old
     * button group container is returned and ownership of this object is 
     * transferred to the calling object.
     *
     * @param aContainer The new button group container.
     * @return A pointer to the old button group container. This is no longer
     *         owned by the dialog.
     */
    IMPORT_C CEikButtonGroupContainer* SwapButtonGroupContainer(
                                        CEikButtonGroupContainer* aContainer);
	
    /**
     * Gets a pointer to the dialog's internal button command observer. 
     *
     * This is required when creating a new button group container for 
     * the dialog.
     * 
     * A dialog uses a proxy to observe button commands. This means dialog
     * subclasses can directly observe commands, either issued by controls 
     * added to the dialog pages, or by menus launched by the dialog.
     *
     * @since 5.1
     * @return A pointer to the dialog's internal button
     *         command observer.
     */ 
    IMPORT_C MEikCommandObserver* ButtonCommandObserver() const;

protected: // new functions

    /**
     * Not implemented.
     *
     * @param aButtonId Not used.
     * @return Always return @c ETrue.
     */
    IMPORT_C virtual TBool OkToExitL(TInt aButtonId);
	
    /**
     * Initializes the dialog's controls before the dialog is sized and 
     * layed out. Empty by default.
     */
    IMPORT_C virtual void PreLayoutDynInitL();
	
    /**
     * Initializes the dialog's controls after the dialog has been sized 
     * but before it has been activated. Empty by default.
     */
    IMPORT_C virtual void PostLayoutDynInitL();
	
    /**
     * Sets the line which initally receives focus.
     * This is the first focusable line on the first page in the
     * dialog by default. Reimplementations of this method must
     * activate a page before doing anything else.
     */
    IMPORT_C virtual void SetInitialCurrentLine();
	
    /**
     * Handles a state change in the control with id aControlId. 
     * Empty by default.
     *
     * @param aControlId Not used.
     */
    IMPORT_C virtual void HandleControlStateChangeL(TInt aControlId);
	
    /**
     * Should handle an attempt by the user to activate a dimmed button with
     * id aControlId. Prints an info message by default.
     *
     * Not implemented / Does nothing in Avkon.
     *
     * @param aControlId Not used.
     */
    IMPORT_C virtual void HandleInteractionRefused(TInt aControlId);
	
    /**
     * Sets the size and position of the dialog given the specified size hint.
     *
     * The parameter is ignored if the @c FlagFillAppClientRect is set.
     * Otherwise it it centered and given the size that was asked for.
     *
     * @param aSize The new size.
     */
    IMPORT_C virtual void SetSizeAndPosition(const TSize& aSize);
	
    /**
     * Returns the border style for this dialog.
     *
     * @return Border style. Always returns @c AknBorderId::EAknBorderNotePopup.
     */
    IMPORT_C virtual TInt BorderStyle();
	
    // Added for Avkon

    /**
     * Routine to map the button id ( Avkon softkey command id) to 
     * @c CEikBidCancel if it is a "cancel" type command type. 
     *
     * The following cases are mapped to a give an @c ExecuteLD return value 
     * of 0:
     *
     *		@c EAknSoftkeyCancel:
     *		@c EAknSoftkeyBack:
     *		@c EAknSoftkeyNo:
     *
     * Other cases are left unchanged.
     * 
     * This operation is performed at the last minute and does not affect other
     * processing in @c CEik/AknDialog. 
     *
     * It is a framework method; It can be overridded to obtain customized 
     * behaviour.
     *
     * @param aButtonId input id to map. 
     * @return 0 for re-mapped negative command ids other values 
     *         are returned as their original command id values.
     */
    IMPORT_C virtual TInt MappedCommandId( TInt aButtonId );
	
    /**
     * Get form flags of the active page
     *
     * @return Active page's form flags 
     */ 
    IMPORT_C TInt FormFlagsFromActivePage();

/* The following two methods are deprecated
	GetFirstLineOnFirstPageOrNull
	ControlsOnPage

instead the functionality can be achieved by
	TInt GetNumberOfLinesOnPage(TInt aPageIndex) const;
	TInt GetNumberOfPages() const;
	CEikCaptionedControl* GetLineByLineAndPageIndex(TInt aLineIndex, 
	                                                TInt aPageIndex) const;
*/

    /**
     * Gets first line of the first page. 
     * 
     * @deprecated
     * @return Pointer to the first line of the first page. If NULL there is no
     *         such line.
     */
	IMPORT_C virtual CEikCaptionedControl* GetFirstLineOnFirstPageOrNull();

    /**
     * Gets all lines in the given page.
     *
     * @param aControls After execution holds all captions in the page.
     * @param aPageId ID of the target page.
     * @deprecated
     */
    IMPORT_C void ControlsOnPage(RArray<CEikCaptionedControl*>& aControls, 
                                 TInt aPageId) const;

    


protected: // from MObjectProvider

    /**
     * From @c MObjectProvider.
     *
     * Retrieves an object of the same type as that encapsulated in aId.
     *
     * This function is used to allow controls to ask their owners for 
     * access to other objects that they own.
     *
     * Other than in the case where NULL is returned, the object returned 
     * must be of the same object type - that is, the @c ETypeId member of 
     * the object pointed to by the pointer returned by this function must 
     * be equal to the iUid member of aId.
     *
     * @param aId An encapsulated object type ID. 
     * @return Encapsulates the pointer to the object provided. 
     *         Note that the encapsulated pointer may be NULL. 
     */ 
    IMPORT_C TTypeUid::Ptr MopSupplyObject(TTypeUid aId);

private: // new functions

    IMPORT_C virtual void CEikDialog_Reserved_1();
	
    IMPORT_C virtual void CEikDialog_Reserved_2();

private: // internal functions
	
    void BaseConstructL();

    void StaticConstructL(TInt aResourceId);
	
    void DynamicConstructL();
	
    void CreateTitleBarL();
	
    void CreateButtonGroupContainerL(TInt aResourceId);
	
    void CreatePageSelectorL();
	
    void CreatePageSelectorL(TInt aResourceId);
	
    TInt WaitAsRequired();
	
    void StopWaitingAsRequired();
	
    TKeyResponse TryAnimateButtonAndExitL(TInt aKeycode);
	
    void GetAutoValues();
	
    void CommonConstructSleepingDialogL(TInt aResourceId);
	
    void SetBorderStyle();
	
    void FadeBehindPopup(TBool aFade);
	
    void DoFadeBehindPopup(TBool aFade);

	void DoResourceChangeLayout();
	
    /**
     * Handles embedded softkey state change.
     *
     * @internal
     * @since S60 v5.2
     */
    void HandleEmbeddedSofkeyStateChange();

    /**
     * Call back method to handle @c CEikCba content changes.
     *
     * @internal
     * @since S60 v5.2
     * @param aAny pointer to @c CEikDialog instance.
     * @return error code.
     */         
    static TInt HandleEmbeddedSoftkeyStateChangeCallBack( TAny* aAny );
    
    /**
     * Enables/disables content observer.
     *
     * @internal
     * @since S60 v5.2
     * @param aEnabled ETrue to enable, EFalse to disable.
     */
    void EnableContentObserver( TBool aEnabled );

    // From MAknFadedComponent
	
    IMPORT_C virtual TInt CountFadedComponents();
	
    IMPORT_C virtual CCoeControl* FadedComponent(TInt aIndex);

private:

    CEikMover* iTitleBar;
	
    CEikDialogPageSelector* iPageSelector;
	
    CEikButtonGroupContainer* iButtonGroupContainer;
	
    CEikDialogButtonCommandObserver* iButtonCommandObserver;
	
    TInt iDialogFlags;
	
    TInt* iExitConfirmed;

	TBool iIsEditable ;
	
    TAknPopupFader iPopupFader;
	
    CActiveSchedulerWait iWait;		// owned, safe to use as direct member data.

public :

	/**
	* Access to CEikDialog's extension object. 
	* 
	* @return Pointer to extension object. 
    *         Constructed in @c CEikDialog::BaseContructL	
    */
	IMPORT_C CEikDialogExtension* Extension() const;

private :

    CEikDialogExtension* iExtension ; // owned

private:

    friend class CEikDialogButtonCommandObserver;
	
    friend class CEikDialogExtension;
	
    friend class CAknDialog;
    
    friend class CAknCharMap;

    friend class CAknCharMapDialog;
	
    friend class CAknNoteDialog;
    
    friend class CAknMediatorFacade;

public: // added JIn to allow access to dialog flags.

    /**
     * Gets flags of the dialog.
     *
     * @return Dialog flags.
     */
    IMPORT_C TInt DialogFlags();

protected: 

    /** 
     * Sets the current Dialog into the Page selector
     */ 
    void RegisterDialgWithPageSelector();

//
// Deprecated interfaces.
// Defined in EIKDLGUT.CPP.
//
public: // Declare auto interfaces.

    /**
     * @deprecated Not supported.
     */
    IMPORT_C void DeclareAutoTextEditorL(TInt aId,TDes* aText);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void DeclareAutoNumberEditor(TInt aId,TInt* aNumber);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void DeclareAutoRangeEditor(TInt aId,SEikRange* aRange);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void DeclareAutoTimeEditor(TInt aId,TTime* aTime);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void DeclareAutoDateEditor(TInt aId,TTime* aDate);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void DeclareAutoTimeAndDateEditor(TInt aId,TTime* aTimeAndDate);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void DeclareAutoDurationEditor(TInt aId,
                                        TTimeIntervalSeconds* aDuration);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void DeclareAutoTimeOffsetEditor(TInt aId,
                                        TTimeIntervalSeconds* aTimeOffset);

//	IMPORT_C void DeclareAutoLatitudeEditor(TInt aId,
//                                      SEikDegreesMinutesDirection* aLatitude);
//	IMPORT_C void DeclareAutoLongitudeEditor(TInt aId,SEikDegreesMinutesDirection* aLongitude);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void DeclareAutoFixedPointEditor(TInt aId,TInt* aValue);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void DeclareAutoSecretEditor(TInt aId,TDes* aText);

public: // Add auto interfaces.

    /**
     * @deprecated Not supported.
     */
    IMPORT_C void AddAutoTextEditorL(const TDesC& aPrompt,TInt aId,TInt aFlags,TInt aWidthInChars,TInt aNoOfLines,TDes* aReturn);

    /**
     * @deprecated Not supported.
     */
    IMPORT_C void AddAutoGlobalTextEditorL(const TDesC& aPrompt,TInt aId,TInt aFlags,TInt aWidthInChars,TInt aNoOfLines,TInt aTextLimit,CGlobalText* aReturn,TInt aFontControlFlags=EGulFontControlAll,TInt aFontNameFlags=EGulNoSymbolFonts);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void AddAutoRichTextEditorL(const TDesC& aPrompt,TInt aId,TInt aFlags,TInt aWidthInChars,TInt aNoOfLines,TInt aTextLimit,CGlobalText* aReturn,TInt aFontControlFlags=EGulFontControlAll,TInt aFontNameFlags=EGulNoSymbolFonts);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void AddAutoNumberEditorL(const TDesC& aPrompt,TInt aId,TInt aMin,TInt aMax,TInt* aReturn);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void AddAutoRangeEditorL(const TDesC& aPrompt,TInt aId,TInt aMin,TInt aMax,HBufC* aSeparatorText,SEikRange* aReturn);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void AddAutoTimeEditorL(const TDesC& aPrompt,TInt aId,const TTime& aMin,const TTime& aMax,TBool aNoSeconds,TTime* aReturn);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void AddAutoDateEditorL(const TDesC& aPrompt,TInt aId,const TTime& aMin,const TTime& aMax, TBool aNoPopout,TTime* aReturn);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void AddAutoTimeAndDateEditorL(const TDesC& aPrompt,TInt aId,const TTime& aMin,const TTime& aMax,TBool aNoSeconds,TBool aNoPopout,HBufC* aInterveningText,TTime* aReturn);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void AddAutoDurationEditorL(const TDesC& aPrompt,TInt aId,const TTimeIntervalSeconds& aMin,const TTimeIntervalSeconds& aMax,TBool aNoSeconds,TTimeIntervalSeconds* aReturn);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void AddAutoTimeOffsetEditorL(const TDesC& aPrompt,TInt aId,const TTimeIntervalSeconds& aMin,const TTimeIntervalSeconds& aMax,TBool aNoSeconds,TTimeIntervalSeconds* aReturn);

//	IMPORT_C void AddAutoLatitudeEditorL(const TDesC& aPrompt,TInt aId,HBufC* aDegreeSign,HBufC* aMinuteSign,HBufC* aSecondSign,HBufC* aTextForNorth,TChar aKeyToMatchForNorth,HBufC* aTextForSouth,TChar aKeyToMatchForSouth,SEikDegreesMinutesDirection* aReturn,TInt aFlags=0);
//	IMPORT_C void AddAutoLongitudeEditorL(const TDesC& aPrompt,TInt aId,HBufC* aDegreeSign,HBufC* aMinuteSign,HBufC* aSecondSign,HBufC* aTextForEast,TChar aKeyToMatchForEast,HBufC* aTextForWest,TChar aKeyToMatchForWest,SEikDegreesMinutesDirection* aReturn,TInt aFlags=0);

    /**
     * @deprecated Not supported.
     */
    IMPORT_C void AddAutoFloatEditorL(const TDesC& aPrompt,TInt aId,const TReal& aMin,const TReal& aMax,TReal* aReturn);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void AddAutoFixedPointEditorL(const TDesC& aPrompt,TInt aId,TInt aMin,TInt aMax,TInt* aRetValue,TInt aDecimalPlaces);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void AddAutoSecretEditorL(const TDesC& aPrompt,TInt aId,TDes* aReturn);

protected: // Set state interfaces.

    /**
     * @deprecated Not supported.
     */
    IMPORT_C void SetLabelL(TInt aControlId, const TDesC& aDes);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void SetLabelL(TInt aControlId, TInt aResourceId);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void SetLabelReserveLengthL(TInt aControlId, TInt aLength);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void SetEdwinTextL(TInt aControlId, const TDesC* aDes);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void SetTextEditorTextL(TInt aControlId,const CGlobalText* aGlobalText);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void ResetSecretEditor(TInt aControlId);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void SetFloatingPointEditorValueL(TInt aControlId, const TReal* aValue);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void SetFixedPointEditorValueL(TInt aControlId,TInt aValue);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void SetFixedPointEditorDecimal(TInt aControlId, TInt aDecimal);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void SetNumberEditorMinAndMax(TInt aControlId, TInt aMinimumValue, TInt aMaximumValue); // only values inside the initial min and max are permitted
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void SetNumberEditorValue(TInt aControlId, TInt aNumber);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void SetFloatEditorMinAndMax(TInt aControlId,TInt aMin,TInt aMax);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void SetFloatEditorValueL(TInt aControlId,TReal aFloat);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void SetRangeEditorMinAndMax(TInt aControlId, TInt aMinimumValue, TInt aMaximumValue); // only values inside the initial min and max are permitted
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void SetRangeEditorValue(TInt aControlId, const SEikRange& aRange);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void SetTTimeEditorMinAndMax(TInt aControlId, const TTime& aMinimumTime, const TTime& aMaximumTime); // only values inside the initial min and max are permitted
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void SetTTimeEditorValue(TInt aControlId, const TTime& aTime);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void SetDurationEditorMinAndMax(TInt aControlId, const TTimeIntervalSeconds& aMinimumDuration, const TTimeIntervalSeconds& aMaximumDuration); // only values inside the initial min and max are permi
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void SetDurationEditorValue(TInt aControlId, const TTimeIntervalSeconds& aDuration);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void SetTimeOffsetEditorMinAndMax(TInt aControlId, const TTimeIntervalSeconds& aMinimumTimeOffset, const TTimeIntervalSeconds& aMaximumTimeOffset); // only values inside the initial min and max are
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void SetTimeOffsetEditorValue(TInt aControlId, const TTimeIntervalSeconds& aTimeOffset);

//	IMPORT_C void SetLatitudeEditorValue(TInt aControlId, const SEikDegreesMinutesDirection& aLatitude);
//	IMPORT_C void SetLongitudeEditorValue(TInt aControlId, const SEikDegreesMinutesDirection& aLongitude);

    /**
     * @deprecated Not supported.
     */
    IMPORT_C void SetListBoxCurrentItem(TInt aControlId, TInt aItem);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void SetFileNameL(TInt aControlId, const TDesC* aFileName);

protected: // Get state interfaces.

    /**
     * @deprecated Not supported.
     */
    IMPORT_C void GetLabelText(TDes& aDes,TInt aControlId) const;
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void GetEdwinText(TDes& aDes,TInt aControlId) const;
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void GetTextEditorText(CGlobalText*& aGlobalText,TInt aControlId);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void GetSecretEditorText(TDes& aDes,TInt aControlId) const;
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C TReal FloatingPointEditorValue(TInt aControlId) const;
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C TInt FixedPointEditorValue(TInt aControlId) const;
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C TInt FixedPointEditorDecimal(TInt aControlId) const;
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C TReal FloatEditorValue(TInt aControlId) const;
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C TInt NumberEditorValue(TInt aControlId) const;
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C SEikRange RangeEditorValue(TInt aControlId) const;
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C TTime TTimeEditorValue(TInt aControlId) const;
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C TTimeIntervalSeconds DurationEditorValue(TInt aControlId) const;
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C TTimeIntervalSeconds TimeOffsetEditorValue(TInt aControlId) const;

//	IMPORT_C SEikDegreesMinutesDirection LatitudeEditorValue(TInt aControlId) const;
//	IMPORT_C SEikDegreesMinutesDirection LongitudeEditorValue(TInt aControlId) const;

    /**
     * @deprecated Not supported.
     */
    IMPORT_C void GetAutoValuesFromPage(CEikCapCArray* aLines);
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C TInt ListBoxCurrentItem(TInt aControlId) const;
	
    /**
     * @deprecated Not supported.
     */
    IMPORT_C void GetFileName(TFileName* aFileName,TInt aControlId) const;

    /**
     * Only has effect on forms, call this after adding or deleting lines.
     *
     * @param aRedraw Whether to redraw the page. Usually expect this to be
     *        @c ETrue.
     */
    IMPORT_C void UpdatePageL(TBool aRedraw);

public:

    /**
     * From @c CEikDialog (@c MEikDialogPageObserver).
     *
     * The interface method which is called when dialog page is tapped with
     * a stylus.
     *
     * @param aEventID An event identification number.
     */
    IMPORT_C virtual void HandleDialogPageEventL(TInt aEventID);

    /**
    * Instantiates mediator support and send a command with given parameters
    * when a dialog is brought to display.
    *
    * @since 3.1
    * @param aDialogIndex unique index to identify a dialog within the category.
    * @param aCatUid  gategory uid, if default paramter is passed, application
    *        uid is used as a category.
    */
    IMPORT_C void PublishDialogL(TInt aDialogIndex, TUid aCatUid = KNullUid);

    /**
    * Instantiates mediator support and passes possible feedback to given
    * intance. If no observer is set, dialog tries to handle feedback by it
    * self.
    * Please note that no commands will be instantiated unless command
    * identifiers are are set using @c PublishDialogL.
    *
    * @since 3.1
    * @param  aObserver Pointer to instance implementing
    *         @c MAknDialogMediatorObserver API. Can be NULL.
    */
    IMPORT_C void SetMediatorObserver(MAknDialogMediatorObserver* aObserver);
    
    /* @since 3.1
     * Tries to slide the dialog to the screen. If there is not enough memory for
     * sliding, the dialog appears as before.
     *
     * Method is exported because of delayed notes.
     *
     * @return void 
     */
    IMPORT_C void SlideDialog();

public:
	/** @since 3.2
     * Sets dialog to be multilinequery.
	 * 
	 * This is called by multiline query only. Changes tab-key behaviour
	 * of the dialog page. Tab key works differently for forms and
	 * multiline queries.
	 *
     * @param aIsMultilineQuery Whether this dialog is multiline query
     */
	IMPORT_C void SetMultilineQuery(TBool aIsMultilineQuery);
    };

#endif
