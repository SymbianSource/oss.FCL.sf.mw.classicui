/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
*     Provides the CAknDialog-derived interface to Avkon Notes.
*
*/


#ifndef __AKNNOTEDIALOG__
#define __AKNNOTEDIALOG__

#include <eikdialg.h>
#include "avkon.hrh"
class CEikImage;
class CAknKeySoundSystem;
class CAknNoteControl;
class CAknNoteAttributes;
class CAknNoteDialogExtension;


/**
 * The note dialog.
 *
 * Displays a note to the user for: <UL> <LI> Giving notifications. </LI>
 * <LI> Asking questions. </LI> <LI> Showing progress. </LI> </UL>
 *
 * @see CAknNoteControl, CAknNoteAttributes, CAknText
 */
class CAknNoteDialog : public CEikDialog
{

public:

    /**
     * The timeout in microseconds for automatically deleting the dialog.
     */
    enum TTimeout {

        /** 
         * Deprecated (not used).
         * 
         * @deprecated
         */
    EUndefinedTimeout = 0,   
    /// No timeout  
    ENoTimeout = 0,         
    /// 1.5 seconds 
    EShortTimeout = 1500000,
    /// 3 seconds
    ELongTimeout = 3000000,
    /// 0.5 second
    EShortestTimeout = 500000   
    };

    /**
    * The tone played before the dialog is shown.
    *
    * Application specific tones may be played by casting the application
    * defined Sound ID (SID), to @c TTone.
    */
    enum TTone {

        /** No tone is played. */
        ENoTone = 0,		

        /** A confirmation tone is played. */
        EConfirmationTone = EAvkonSIDConfirmationTone, 

        /** A warning tone is played. */
        EWarningTone = EAvkonSIDWarningTone,      

        /** An error tone is played. */
        EErrorTone = EAvkonSIDErrorTone         
    };

public:

    /**
     * C++ default constructor. 
     *
     * Initialises the tone to @c ENoTone and the timeout to @c ENoTimeout. 
     *
     * @see @c TTone, @c TTimeout.
     */
    IMPORT_C CAknNoteDialog();

    /**
     * C++ default constructor.
     *
     * Initialises the tone to @c aTone and the timeout to @c aTimeout. 
     *
     * @param aTone The tone to be played.
     * @param aTimeout The timeout (microseconds). Default is @c ENoTimeout.
     * @see @c TTone, @c TTimeout.
     */
    IMPORT_C CAknNoteDialog(const TTone& aTone, 
                            const TTimeout& aTimeout = ENoTimeout);

    /**
     * C++ default constructor.
     *
     * Initialises the tone to @c aTone and the timeout to @c aTimeout. 
     * Accepts a pointer to @c CEikDialog*. This must be the address of 
     * the dialog pointer. When the dialog deletes itself after a timeout, 
     * the address pointed to by this pointer is set to NULL. The dialog must
     * not be on the stack, it must be on the heap!
     *
     * @param aSelfPtr Pointer to the address of the dialog.
     * @param aTone = @c ENoTone The tone. 
     * @param aTimeout = @c ENoTimeout The timeout (microseconds). 
     * @see @c TTone, @c TTimeout.
     */
    IMPORT_C CAknNoteDialog(CEikDialog** aSelfPtr, 
                            const TTone& aTone = ENoTone, 
                            const TTimeout& aTimeout = ENoTimeout);

    /**
     * Destructor. 
     *
     * Deletes timer and control attributes. If the self pointer is not null, 
     * sets the pointer to point to NULL. 
     */
    IMPORT_C virtual ~CAknNoteDialog();

    /**
     * Sets the dialog timeout. 
     *
     * @see @c TTimeout.
     * @param aTimeout The dialog timeout.
     */
    IMPORT_C void SetTimeout(const TTimeout& aTimeout);

    /**
     * Sets the dialog tone .
     *
     * @see @c TTone.
     * @param aTone The dialog tone.
     */
    IMPORT_C void SetTone(const TTone& aTone);

    /**
     * Enables or disables text wrapping. 
     *
     * Enables or disables text wrapping depending on the values
     * of @c aEnabled (true enables text wrapping). When text wrapping is
     * disabled a new line in the note dialog starts only after a newline 
     * character in the note text. If a line does not fit into the dialog 
     * width it is clipped (the last character is replaced with an 
     * ellipsis sign).
     *
     * This method must be called before @c SetTextL as it only influences 
     * the wrapping of text that it is yet to be set via API.
     *
     * @param aEnabled @c ETrue for enabling text wrapping, @c EFalse for 
     *        disabling it.
     */
    IMPORT_C void SetTextWrapping(TBool aEnabled);

    /**
     * Enables or disables all text processing done by the dialog.
     * This includes text wrapping, text truncation
     * and reordering of bidirectional text.
     *
     * By default, it is enabled.
     *
     * If text processing is disabled, lines are broken only at explicit 
     * line end characters and they are not truncated, but drawn as long
     * as they fit. Also, the dialog does not handle reordering of 
     * the bidirectional text.
     *
     * This method must be called before the text is set.
     *
     * @param aEnabled Enables or disables all text processing.
     */
    IMPORT_C void SetTextProcessing(TBool aEnabled);

    /**
     * Set the dialog image. 
     *
     * Change the image in the note control. Override the image which was 
     * set in the resource file. The dialog takes ownership of the pointer.
     * The note image is the big image or icon which is top right. 
     *
     * @param aImage Pointer to the new image. 
     */
    IMPORT_C void SetImageL(CEikImage* aImage);

    /**
     * Sets the dialog icon. 
     *
     * Changes the number type icon in the note control. 
     *
     * Overrides the icon which was set in the resource file. The dialog takes 
     * ownership of the pointer The numbertype icon is the small icon which 
     * is bottom left in the note (thumbnail icon). 
     * 
     * @param aIcon Pointer to the icon.
     */
    IMPORT_C void SetIconL(CEikImage* aIcon);

    /**
     * Sets the number in the dialog text. 
     *
     * Sets a number in the note text. If the text specified in the resource 
     * file or via  @c SetTextL() has a \%d in it, e.g. "You have \%d new 
     * messages", this number is inserted at the location specified by \%d.  
     *
     * @param aNumber The number to be inserted in the text.
     */
    IMPORT_C void SetTextNumberL(TInt aNumber);

    /**
     * Sets the text plurality for the dialog. 
     *
     * Indicates whether to use plural or singular text. These texts must 
     * have been specified in the resource file.
     *
     * @see @c SetTextNumberL().
     * @param isPlural @c ETrue if plural text should be used, 
     *        @c EFalse otherwise.
     */
    IMPORT_C void SetTextPluralityL(const TBool isPlural);

    /**
     * Sets the dialog text.
     *
     * This method can set a formatted text, 
     * e.g. "You have 1 new message". It can however set an 
     * unformatted text as well, e.g. "You have \%d messages". The plurality of
     * the dialog must be previously specified - if not singular 
     * plurality is used unless there was no singular text specified in the 
     * resource file.
     *
     * @see @c SetTextNumberL(), @c SetTextPluralityL().
     * @param aLabel The note text.
     */
    IMPORT_C void SetTextL(const TDesC& aLabel);

    /**
     * From @c CCoeControl.
     * 
     * Handles key events. 
     *
     * Any event which is not a key press is forwarded to 
     * @c CEikDialog::OfferKeyEventL.
     '
     * Short key press dismiss the note by calling @c StaticDeleteL.
     *
     * @see @c StaticDeleteL(), @c TKeyEvent, @c TEventCode.
     * @param aKeyEvent Key event details.
     * @param aType Type of event (key down, key press, key release, etc).
     * @return Indicates whether or not the key event was used 
     *         by this control. @c EKeyWasConsumed if the control takes action
     *         on the key event or @c EKeyWasNotConsumed otherwise.
     */
    IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,
                                         TEventCode aType);

    /**
     * From @c CCoeControl.
     * 
     * Handles a change to the control's resources of type @c aType
     * which are shared across the environment, e.g. colors or fonts.
     *
     * @param aType Target resource type.
     */
    IMPORT_C void HandleResourceChange(TInt aType);

    /**
     * Do layout and draw the note dialog. 
     *
     * Needed when changing control components (e.g. the text) dynamically. 
     * This is needed because the size of the dialog might change 
     * (e.g. because of bigger text displayed in more lines, etc.)  
     * Set methods call @c LayoutAndDraw() if there is a change that
     * might affect the dialog layout (e.g. text becames bigger and hence
     * requires an extra line).
     *
     * Derived classes that implement this kind of methods should call
     * @c LayoutAndDraw().
     */
    IMPORT_C void LayoutAndDraw();

    /**
     * From @ CEikDialog. 
     *
     * Executes a dialog.
     *
     * Plays a tone (if one was defined) and simulates user activity.
     * Forwards call to @c CEikDialog::RunLD().
     *
     * @return The ID of the button used to dismiss the dialog.
     */
    IMPORT_C virtual TInt RunLD();


    /**
     * From @c CEikDialog. 
     *
     * Exits a sleeping dialog without deleting it.
     */
    IMPORT_C void ExitSleepingDialog();

protected:

    /**
     * From @c CEikDialog. 
     *
     * Sets the size and the position for the layout. 
     *
     * The dialog height and width are retrieved from the control  
     * (if it exists already).If it does not exist, then default values 
     * are used. The client rect is obtained from the application UI. 
     * @c AknLayoutUtils::LayoutControl  is then executed using the client
     * rect and the note width and height.
     * 
     * @see @c AknLayoutUtils::LayoutControl().
     * @param aSize Not used. 
     */
    IMPORT_C void SetSizeAndPosition(const TSize& aSize);

    /**
     * From @c CEikDialog. 
     *
     * Performs dynamic operations before the layout. 
     *
     * Called by the Uikon framework before the dialog layout is executed, this
     * method can be overrwritten to perform specific operations.
     *
     * The following operations are performed:- <UL> <LI> The control attributes
     * are transferred to the control. The local control attributes are copied 
     * into the real control attributes. The local attributes are then deleted.
     * </LI> <LI> If a timeout has been specified the timer is started. The 
     * callback is StaticDeleteL. </LI> <LI> </LI> </UL> 
     * 
     * @see @c CAknNoteAttributes, @c TTimer, @c SetEditableL().
     */
    IMPORT_C void PreLayoutDynInitL(void);

    /**
     * From @c CEikDialog. 
     *
     * Performs dynamic operations after the layout. 
     *
     * Called by the Uikon framework after the dialog layout is executed, this
     * method can be overrwritten to perform specific operations.
     *
     * The following operations are performed:- <UL> <LI> @c StartAnimationL()
     * is called. </LI> </UL> 
     * 
     * @see @c CAknNoteControl::StartAnimationL().
     */
    IMPORT_C void PostLayoutDynInitL();

    /**
     * Plays a tone. 
     *
     * The tone must be previously specified. The sound ID is set 
     * depending on the tone type. The tone is played using 
     * @c CAknKeySoundSystem::playSound(). Derived classes must call this 
     * method if they override @c RunLD() and they wish to play a tone. 
     *
     * @panic EAknPanicNullPointer
     * @see @c TTone, @c CAknKeySoundSystem, @c CAknNoteDialog::RunLD().
     */
    IMPORT_C void PlayTone();

    /**
     * Indicates that there is user activity. 
     *
     * Resets timers which are monitoring user inactivity. This will disable 
     * functionality that checks for user inactivity by listening to 
     * these timers.
     *
     * Derived classes must call this method if they override @c RunLD()
     * and they wish to report user activity in order to dismiss applications
     * such as the screen saver.
     *
     * @see @c User::ResetInactivityTime().
     */
    IMPORT_C void ReportUserActivity() const;

    /**
     * Deletes the note dialog.
     *
     * Called when the timer completes, this method deletes the dialog. A
     * @c reinterpret_cast to @c CAknNoteDialog* is performed on aThis. If the
     * dialog is not a sleeping note then it is deleted. If it is a sleeping
     * dialog then the timer is stopped, @c OkToExitL() is called with 
     * @c KErrCancel and @c ExitSleepingDialog is executed. 
     * 
     * @see @c TTimer, @c OkToExitL(), @c ExitSleepingDialog().
     * @param aThis Pointer to the dialog.
     * @return Always returns @c EFalse.
     */
    IMPORT_C static TInt StaticDeleteL(TAny* aThis);

    /**
     * Gets the control attributes.
     *
     * If the control has already been created this method return the 
     * attributes stored inside the control. If not then the local 
     * attributes are returned. The local attributes are transferred to the 
     * control in @c PreLayoutDynInitL().
     *
     * Derived classes should use this method when trying to access the control
     * attributes.
     * 
     * @return Control attributes.
     */
    IMPORT_C CAknNoteAttributes* ControlAttributes();

    /**
     * Transfers the control attributes from the dialog to the control.
     *
     * Must be called by derived classes in @c PreLayoutDynInitL()
     * if this method is not called then the set of API methods that were
     * invoked before the control is created will not work.
     */
    IMPORT_C void TransferControlAttributes();

    /**
     * Gets the used sound system.
     *
     * Calls @c iEikonEnv->AppUi()->KeySounds() and returns the pointer 
     * returned by the called method. If there is no application UI 
     * return @c NULL. 
     *
     * @see @c CAknKeySoundSystem, @c CAknAppUi.
     * @return Pointer to the used @c CAknKeySoundSystem or @c NULL.
     * @panic EAknPanicNullPointer
     */
    IMPORT_C CAknKeySoundSystem* SoundSystem() const;

    /**
     * Gets the Note control. 
     *
     * Returns the first control on the active page, which is of type
     * @c CAknNoteControl. If no control is found (usually because the 
     * control has not been created yet) then this method returns @c NULL.
     *
     * Derived classes must use this method to get access to the note
     * control.
     *
     * @return Pointer to the note control or @c NULL.
     */
    IMPORT_C CAknNoteControl* NoteControl();

private:
    
    void DbgCheckSelfPtr(CEikDialog** aSelfPtr);

protected:

    /**
     * Note timeout timer.
     */ 
    CPeriodic*          iTimer;		

    /** 
     * Note timeout in microseconds.
     */ 
    TInt                iTimeoutInMicroseconds; 

    /**
     * Used for notes that are not modal. 
     * The calling application has no way of knowing 
     * when the note is deleted. 
     */
    CEikDialog**        iSelfPtr; 

    /**
     * The tone to be played. 
     */
    TTone               iTone;	

    /**
     * Note control attributes.
     */
    CAknNoteAttributes* iControlAttributes;  

private:

    //TInt iSpare; 
    CAknNoteDialogExtension* iNoteExtension;

public:

    /**
     * Set timeout, tone, resource ID and then initialize and launch 
     * the dialog. 
     * 
     * This method is deprecated and should not be used.
     * 
     * @deprecated
     * @param aTimeout Wanted timeout in microseconds.
     * @param aTone Alarm tone.
     * @param aResourceID The ID of the wanted resource.
     * @return Zero, unless it is a waiting dialog. For a waiting dialog,
     *         the return value is the ID of the button that closed the dialog,
     *         or zero if it was the cancel button (@c EEikBidCancel).
     */
    IMPORT_C TInt ExecuteDlgLD(const TTimeout aTimeout,
                               const TTone aTone,
                               TInt aResourceID);

    /**
     * Set tone, resource ID and then initialize and launch 
     * the dialog. 
     * 
     * This method is deprecated and should not be used.
     * 
     * @deprecated
     * @param aTone Alarm tone.
     * @param aResourceID The ID of the wanted resource.
     * @return Zero, unless it is a waiting dialog. For a waiting dialog,
     *         the return value is the ID of the button that closed the dialog,
     *         or zero if it was the cancel button (@c EEikBidCancel).
     */
    IMPORT_C TInt ExecuteDlgLD(const TTone aTone,TInt aResourceID);

    /**
     * Set note control ID, resource ID and then initialize and launch 
     * the dialog. 
     * 
     * This method is deprecated and should not be used.
     * 
     * @deprecated
     * @param aResourceId The ID of the wanted resource.
     * @param aNoteControlId Not used. 
     * @return Zero, unless it is a waiting dialog. For a waiting dialog,
     *         the return value is the ID of the button that closed the dialog,
     *         or zero if it was the cancel button (@c EEikBidCancel).
     */
    IMPORT_C TInt ExecuteDlgLD(TInt aResourceId, TInt aNoteControlId=0);

    /**
     * Set timeout and tone and run the dialog.
     *
     * This method is deprecated and should not be used.
     *
     * @deprecated
     * @param aTimeout Wanted timeout in microseconds.
     * @param aTone Wanted alarm tone.
     * @return The ID of the button used to dismiss the dialog.
     */
    IMPORT_C TInt RunDlgLD(const TTimeout aTimeout,const TTone aTone);

    /**
     * Set tone and run the dialog.
     *
     * This method is deprecated and should not be used.
     *
     * @deprecated
     * @param aTone Wanted alarm tone.
     * @return The ID of the button used to dismiss the dialog.
     */    
    IMPORT_C TInt RunDlgLD(const TTone aTone);

    /**
     * Run the dialog.
     *
     * This method is deprecated and should not be used.
     *
     * @deprecated
     * @return The ID of the button used to dismiss the dialog.
     */    IMPORT_C TInt RunDlgLD();

    /**
     * Set NoteControlID and run the dialog.
     *
     * This method is deprecated and should not be used.
     *
     * @deprecated
     * @param aNoteControlId Not used.
     * @return The ID of the button used to dismiss the dialog.
     */    
    IMPORT_C TInt RunDlgLD(TInt aNoteControlId);

    /** 
     * Sets a new label for the specified dialog.
     *
     * This method is deprecated. @c SetTextL() method should be used 
     * instead.
     *
     * @param aControlId Not used.
     * @param aLabel The new label.
     */ 
    IMPORT_C void SetCurrentLabelL(TInt aControlId,const TDesC& aLabel);

private: 

    IMPORT_C virtual void CEikDialog_Reserved_1();

    IMPORT_C virtual void CEikDialog_Reserved_2();	

private: // new virtual function.

    IMPORT_C virtual void CAknNoteDialog_Reserved();

protected:

    // This method id reserved for CEikAlert usage
    /** 
     * Sets an indication that memory should not be allocated.
     * 
     * This method is reserved for CEikAlert usage.
     */ 
    IMPORT_C void SetNoMemoryAllocation();


private: // from eikdialog

    IMPORT_C void SizeChanged();

    void SetSkinBackGroundRect(); 

private:

    void CreateExtensionL();

    static TInt CallbackStartAnimationL(TAny* aThis);

public:

    /**
     * From @c CCoeControl.
     *
     * Processes the pointer event directed to the dialog.
     * 
     * @param aPointerEvent The pointer event directed to the notedialog.
     */
    IMPORT_C virtual void HandlePointerEventL(
                                        const TPointerEvent& aPointerEvent);

private:

    /**
    * From @c CAknControl.
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
    };


#endif  // __AKNNOTEDIALOG__

// End of file