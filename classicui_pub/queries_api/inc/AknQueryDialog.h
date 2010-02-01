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
* Description:  Implementation of query dialogs.
*
*/


#ifndef AKNQUERYDIALOG_H
#define AKNQUERYDIALOG_H

//  INCLUDES
#include <eikdialg.h>
#include <AknForm.h>
#include <eiklbx.h>
#include <eiktxlbx.h>
#include <eikcmobs.h>
#include <aknpopuplayout.h>
#include <aknintermediate.h>
#include <aknQueryControl.h>
#include <aknpopuplayout.h>
#include <aknmultilinequerycontrol.h>
#include <aknlistquerycontrol.h>
#include <aknintermediate.h>
#include <aknquerydata.h>
#include <avkon.hrh>

class CAknKeySoundSystem;
class TInetAddr;
class CAknQueryDialogExtension;
class CAknMultilineQueryDialogExtension;

/**
 * General query dialog
 *
 * Use for confirmation queries
 */
class CAknQueryDialog : public CAknDialog , public MAknQueryControlObserver
    {
    friend class CAknQueryDialogExtension;
    public:

        /**
         * Enumeration for tones.
         *
         * The tone played before the dialog is shown. Application specific
         * tones may be played by casting the application defined Sound ID
         * (SID), to @c TTone
         **/
      enum TTone {

        /**
         * No tone is played
        */
        ENoTone = 0,

        /**
         * A confirmation tone is played.
        */
        EConfirmationTone = EAvkonSIDConfirmationTone,

        /**
         * A warning tone is played.
        */
        EWarningTone = EAvkonSIDWarningTone,

        /**
         * An error tone is played.
        */
        EErrorTone = EAvkonSIDErrorTone
        };

    public:

        /**
         * Second phase construction required to align with multiline queries API
         * In future might use MAknQueryData mixin in the base class, hence requiring
         * second phase construction.
         *
         * @return pointer to CAknQueryDialog
        */
        IMPORT_C static CAknQueryDialog* NewL(const TTone& aTone = ENoTone);

        /**
         *
         * @return pointer to CAknTextQueryDialog
        */
        IMPORT_C static CAknQueryDialog* NewL(TDes& aText, const TTone& aTone = ENoTone);

        /**
         *
         * @return pointer to CAknNumberQueryDialog
        */
        IMPORT_C static CAknQueryDialog* NewL(TInt& aNumber, const TTone& aTone = ENoTone);

        /**
         *
         * @return pointer to CAknTimeQueryDialog
        */
        IMPORT_C static CAknQueryDialog* NewL(TTime& aTime, const TTone& aTone = ENoTone);

        /**
         *
         * @return pointer to CAknDurationQueryDialog
        */
        IMPORT_C static CAknQueryDialog* NewL(TTimeIntervalSeconds& aTime, const TTone& aTone = ENoTone);

        /**
         *
         * @return pointer to CAknFloatQueryDialog
        */
        IMPORT_C static CAknQueryDialog* NewL(TReal& aNumber, const TTone& aTone = ENoTone);

        /**
         *
         * @return pointer to CAknIpQueryDialog
        */
        IMPORT_C static CAknQueryDialog* NewL(TInetAddr& aInetAddr, const TTone& aTone = ENoTone);

        /**
         * Not yet totally implemented!
         *
         * @return pointer to CAknLocationQueryDialog
        */
        IMPORT_C static CAknQueryDialog* NewL(TPosition &aValue, const TTone &aTone = ENoTone);

    public:
        IMPORT_C virtual ~CAknQueryDialog();

        /**
         * Construction
         *
         * @deprecated: will be made protected - use NewL
        */
        IMPORT_C CAknQueryDialog(const TTone& aTone);

    public:

        /**
         * Return pointer to query heading or NULL
         *
        */
        IMPORT_C virtual CAknPopupHeadingPane* QueryHeading() const;

        /**
         * Deprecated method to return pointer to query heading or NULL (use QueryHeading())
         *
         * @deprecated - will be removed (use QueryHeading() method instead)
        */
        IMPORT_C CAknPopupHeadingPane* Heading() const;

        /**
         * Set prompt text for query. This this will override text given in constructor.
         *
         * @param aPrompt  Text for prompt
        */
        IMPORT_C void SetPromptL(const TDesC& aPrompt);

        /**
         * Set visibility of the left softkey. Softkey is hidden when data in the query is not acceptable.
         * @param aVisible EFalse hides softkey label, ETrue shows it.
        */
        IMPORT_C void MakeLeftSoftkeyVisible(TBool aVisible);

        /**
         * Enable or disable emergency call support.  This method is only valid in
         * numeric queries (secret or normal).
         *
         * Default is Off for both.
         *
         * @param aOnOff    Sets emergency call support active or inactive, if feature is available in
         *                  current type of control
         */
        IMPORT_C void SetEmergencyCallSupport( TBool aOnOff );

        /**
         * Removes the editor indicators for this dialog.
         * Used to ensure this dialog does not own any editor indicators.
         * before opening another dialog which outlasts this one.
        */
        IMPORT_C void RemoveEditorIndicator();

        /**
         * This method can be used to set predictive text entry permitted.  The default
         * Query behaviour is to supress predictive entry (over-riding editor resource
         * flags that may indicate otherwise.
         *
         * This may be called at any time prior to activation of the query.
         *
         * @param aPermitted    ETrue - allow predictive text entry
         *
         */
        IMPORT_C void SetPredictiveTextInputPermitted( TBool aPermitted );

        /**
         * Runs the querydialog and returns the ID of the button used to dismiss it.
         * The dialog is destroyed on exit.
         *
        */
        IMPORT_C TInt RunLD();

        /**
         * Call PrepareLC and display dialog.
         *
         * Identical to version in CEikDialog but need to override
         * this because of version with prompt,
         * compiler will complain if this is not implemented in
         * derived class as well
         *
         * @param aResourceId    resource for query
        */
        IMPORT_C TInt ExecuteLD(TInt aResourceId);

        /**
         * Call PrepareLC and display dialog.
         *
         * @param aResourceId    resource for query
         * @param aPrompt    text for query prompt
        */
        IMPORT_C TInt ExecuteLD(TInt aResourceId, const TDesC& aPrompt);

    public:// from CCoeControl

        /**
         * From @c CCoeControl<p>
         * Handle key events. When a key event occurs,
         * until one of them returns EKeyWasConsumed to indicate that it processed the key event.
         * CONE calls this function for each control on the control stack,
         * @param aKeyEvent  The key event.
         * @param aType      The type of the event: EEventKey, EEventKeyUp or EEventKeyDown.
         * @return           Indicates whether or not the key event was used by this control.
        */
        IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

        /**
         * Handles pointer events
        */
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

    public:

        /**
         * Return the maximum possible length of the query text
         * This is (in order of precedence, and assuming they are valid
         * i.e. less than or equal to the length of the descriptor passed to
         * return the value) dependent on:<p>
         * 1) aApiValue<p>
         * 2) Resource set value held in aControl<p>
         * 3) The MaxLength of the descriptor
         * @return maximum text length
        */
        IMPORT_C static TInt MaxTextLength(const CAknQueryControl* aControl, const TDes& aDataText, TInt aApiValue) ;

    protected://from CEikdialog

        /**
         * From @c CEikdialog<p>
         * EIKON provides an implementation of this function,
         * which positions the dialog in the centre of the screen.
         * However, it can be overridden by derived classes.
         * @param aSize      The size for the dialog.
        */
        IMPORT_C void SetSizeAndPosition(const TSize& aSize);

        /**
         * From @c CEikdialog<p>
         * This function is called by the EIKON dialog framework just before the dialog is activated, but before it is sized,
         * and before PostLayoutDynInitL() is called.
        */
        IMPORT_C void PreLayoutDynInitL(void);

        /**
         * From @c CEikdialog<p>
         * This function is called by the EIKON dialog framework just before the dialog is activated,
         * after it has called PreLayoutDynInitL() and the dialog has been sized.
        */
        IMPORT_C void PostLayoutDynInitL();

        /**
         * From @c CEikdialog<p>
         * This function is called by the EIKON framework
         * if the user activates a button in the button panel.
         * It is not called if the Cancel button is activated,
         * unless the EEikDialogFlagNotifyEsc flag is set.
         * @param aButtonId  The ID of the button that was activated
         * @return           Should return ETrue if the dialog should exit, and EFalse if it should not.
        */
        IMPORT_C virtual TBool OkToExitL(TInt aButtonId);

    public://from MAknQueryControlObeserver

        /**
        * From @c MAknQueryControlObserver<p>
        * Gets called when editor sends size event.
        * @param aQueryControl  Pointer to query control which sent the event
        * @param aEventType     Type of the event
        */
        IMPORT_C TBool HandleQueryEditorSizeEventL(CAknQueryControl* aQueryControl, TQueryControlEvent aEventType);

        /**
        * From @c MAknQueryControlObserver<p>
        * Gets called when editor sends state event
        * @param aQueryControl  Pointer to query control which sent the event
        * @param aEventType     Type of the event
        * @param aStatus        Editor validation status
        */
        IMPORT_C TBool HandleQueryEditorStateEventL(CAknQueryControl* aQueryControl, TQueryControlEvent aEventType, TQueryValidationStatus aStatus);

        /**
        * Called by OfferkeyEventL(), gives a change to dismiss the query even with
        * keys different than Enter of Ok.
        */
        IMPORT_C virtual TBool NeedToDismissQueryL(const TKeyEvent& aKeyEvent);

        /**
        * Called by NeedToDismissQueryL(), gives a change to either accept or reject
        * the query. Default implementation is to accept the query if the Left soft
        * key is displayed and reject it otherwise. Left softkey is only displayed if
        * the query has valid data into it.
        */
        IMPORT_C virtual void DismissQueryL();

    protected:

        /**
        * If the query text is ok (retrieved form query control) then display the
        * left soft key, otherwise hide it.
        */
        IMPORT_C virtual void  UpdateLeftSoftKeyL();

        /**
        * Set the prompt inside the query control. If dialog is active redo
        * layout and draw.
        */
        IMPORT_C virtual void DoSetPromptL();

        /**
        * Return pointer to query control or NULL
        *
        */
        IMPORT_C virtual CAknQueryControl* QueryControl() const;

    protected: //implementation, intended to be used but not overwritten

        /**
        * Plays tone
        */
        void  PlayTone();

        /**
        * Resets system's inactivity timer
        */
        void  ReportUserActivity() const ;

        /**
        * Recreates layout and redraws the dialog
        */
        void  LayoutAndDraw();

        /**
        * Returns left CBA short key press
        * @return Id of the left CBA
        */
        TInt  GetLeftCBAShortKeyPress();

        /**
        * Returns right CBA short key press
        * @return Id of the right CBA
        */
        TInt  GetRightCBAShortKeyPress();

        /**
        * Returns whether the left softkey is visible
        * @return ETrue is the left softkey is visible
        */
        TBool IsLeftSoftkeyVisible();

    protected:

        /**
         * Prompt access for derived classes
         */
        IMPORT_C TPtrC Prompt() const;

        /**
         * @return query tone
        */
        TTone& Tone() { return iTone; }

        /**
         * @return query tone
        */
        const TTone& Tone() const { return iTone; }

        /**
         * @return query flags
        */
        TBitFlags16& Flags() { return iFlags; }

        /**
         * @return query flags
        */
        const TBitFlags16& Flags() const { return iFlags; }

        /**
         * @return query sound system
        */
        CAknKeySoundSystem* SoundSystem() const { return iSoundSystem; }

    protected: // collected code for accessing Dialog state.

        /**
         * To be used to go through every control in the dialog, on every page,
         * in Dialog-internal storage order, until a control with that type is found.
         * If such a control is not found, a null pointer will be returned.
         * @param aControlType - Enum used to identify the control type on that CEikCaptionedControl Line
         * @param aLineIndex - Optional argument, if used contains reference to an int which holds the initial
         *       line to start searching on, and on finding a control of that type, is
         *       assigned the next position to start searching.
         * @param aPageIndex - Optional argument, if used contains reference to an int which holds the initial
         *       dialog page to start searching on, and on finding a control of that type, is
         *       assigned the page that the control was found on.
         *
        */
        CCoeControl* FindControlOnAnyPageWithControlType(TInt aControlType, TInt* aLineIndex=0, TInt* aPageIndex=0) const;

    protected:

        /**
         * Tone which is played when the query is executed
         * These will be made private, use protected methods
         *
         * @deprecated.
        */
        TTone  iTone;

        /** Prompt text*/
        TDesC *iPrompt;

        /** Caption Retriever*/
        CAknQueryDialogExtension* iExtension;

        /**
        * Flags for emergency call support
        * Need these at least to store the ECS state until the control exists
        */
        TBitFlags16 iFlags;

        /** Spare variable for further development */
        TInt iSpare_1;

        /** Sound system*/
        CAknKeySoundSystem* iSoundSystem;

    public:

        /**
         * @deprecated do not use
         */
        IMPORT_C CAknQueryDialog();

        /**
         * @deprecated do not use
        */
        IMPORT_C CAknQueryDialog(TDesC& aPrompt,const TTone& aTone = ENoTone);

        /**
         * @deprecated - use QueryHeading() method instead
         */
        IMPORT_C void SetHeaderTextL(const TDesC& aHeader);

        /**
         * @deprecated - use QueryHeading() method instead
         */
        IMPORT_C void SetHeaderImageL(CEikImage* aImage);

        /**
         * @deprecated - use RunLD or ExecuteLD instead
         */
        IMPORT_C TInt RunDlgLD(TInt aResourceId);

        /**
         * @deprecated - use other version of MaxTextLength
         */
        IMPORT_C static TInt MaxTextLength(const CAknQueryControl* aControl, const TDes* aDataText, TInt aApiValue);

    private:
        //From CAknControl
        IMPORT_C void* ExtensionInterface( TUid aInterface );

    private:
        IMPORT_C virtual void CEikDialog_Reserved_1();
        IMPORT_C virtual void CEikDialog_Reserved_2();

    private:
        IMPORT_C virtual void CAknDialog_Reserved();

    private:// new function
        IMPORT_C virtual void CAknQueryDialog_Reserved();
    
    public:        
        /**       
         * From CCoeControl.       
         * Gets the control's input capabilities.       
         *       
         * @return The control's input capabilities.       
         */          
        IMPORT_C TCoeInputCapabilities InputCapabilities() const;
        
        /**
         * Enable or disable support to change the CBA labels of the query
         * according to the current ECS state. It's necessary to enable this
         * alongside with ECS for touch and full screen queries.
         *  
         * Note that if enabling this, then it's not necessary to call  
         * @c SetEmergencyCallSupport( ETrue ) additionally, as when
         * enabling this, @c CAknQueryControl::EEmergencyCallsEnabledByAPI
         * will also be set. To enable the ECS via this method, it must
         * be called prior to @c PreLayoutDynamicInitL.
         * 
         * If this is enabled for CAknQueryDialog-derived classes, then
         * the @c OkToExitL implementation of those should forward the
         * @c EAknSoftkeyEmergencyCall events to the base class' OkToExitL
         * for the emergency call event to be handled. 
         * 
         * This method is only valid in numeric queries (secret or normal),
         * default is Off for both.
         *
         * @param  aOnOff  @c ETrue to enable the ECS CBA support,
         *                 @c EFalse otherwise.
         */
        IMPORT_C void SetEmergencyCallSupportForCBA( TBool aOnOff );

    };

//-------------------------------------
//class CAknTextQuerydialog
//-------------------------------------

//Deprecated
#define CAknStaticSizeDataQuerydialog CAknTextQueryDialog

/**
*This class should be used when user is reguest to enter plain text, secret text, phonenumber or PIN-code
*/
class CAknTextQueryDialog : public CAknQueryDialog
    {

    public://construction and destruction

        /**
         * Second phase construction required to align API with multiline queries
         * and because in future MAknQueryData will be used.
        */
        IMPORT_C static CAknTextQueryDialog* NewL(TDes& aDataText, const TTone& aTone = ENoTone);

    public:

        /**
         * C++ Constructor.
         *
        */
        IMPORT_C CAknTextQueryDialog(TDes& aDataText, const TTone& aTone = ENoTone);

        /**
         * C++ Destructor.
         */
        IMPORT_C virtual ~CAknTextQueryDialog();

    public://New functions

        /**
        * Set max lenght for editor. This overrides the max lenght given in resource.
        *
        * @param aLength    Max lenght.
        */
        IMPORT_C void SetMaxLength(TInt aLength);

        /**
        * Return true if the length of the text is bigger
        * than zero and if there
        * is at least a character which is not a space
        */
        IMPORT_C  virtual TBool CheckIfEntryTextOk() const;

        /**
        * Changes default input mode of a secret editor. By default input mode
        * in secret editor is alpha input mode (EAknEditorSecretAlphaInputMode
        * from uikon.hrh). By using this method the default input mode can be
        * changed to numeric input mode (EAknEditorNumericInputMode).
        *
        * @since 2.1
        * @param aInputMode Default input mode in the secret editor.
        *   Only EAknEditorNumericInputMode and EAknEditorSecretAlphaInputMode
        *   are supported.
        */
        IMPORT_C void SetDefaultInputMode(TInt aInputMode);

    protected://from CEikDialog

        /**
        * From @c CEikdialog<p>
        * This function is called by the EIKON dialog framework
        * just before the dialog is activated, after it has called
        * PreLayoutDynInitL() and the dialog has been sized.
        */
        IMPORT_C void PreLayoutDynInitL();

        /**
        * From @c CEikdialog<p>
        * This function is called by the EIKON framework
        * if the user activates a button in the button panel.
        * It is not called if the Cancel button is activated,
        * unless the EEikDialogFlagNotifyEsc flag is set.
        * @param aButtonId  The ID of the button that was activated
        * @return           Should return ETrue if the dialog should exit, and EFalse if it should not.
        */
        IMPORT_C virtual TBool OkToExitL(TInt aButtonId);

    public://from MAknQueryControlObserver

        /**
        * From @c MAknQueryControlObserver<p>
        * Gets called when editor sends size event
        * @param aQueryControl  Pointer to query control which sent the event
        * @param aEventType     Type of the event
        */
        IMPORT_C TBool HandleQueryEditorSizeEventL(CAknQueryControl* aQueryControl, TQueryControlEvent aEventType);

    public://from CCoeControl

        /**
        * Handles pointer events
        */
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

    protected:

        /**
        * Called by PreLayoutDynInit(), set the control observer, the text and
        * the maximum length of the text
        */
        void SetControlTextL();

        /**
         * @return data
        */
        inline TDes& Text() { return iDataText; }

        /**
         * @return data
        */
        inline const TDesC& Text() const { return iDataText; }

    protected:

        /**
         * Max length for text
         *
         * @deprecated
         * This data will become private
         * Use Text() and MaxTextLength() instead
         */
        TInt  iTextMaxLength;

        /**
         * Text for editor. When query is approved text from editor is stored here
         */
        TDes& iDataText;

        /** @deprecated - not used anymore */
        TBool iEditorTextOk;

    public:

        /**
        * deprecated do not use
        */
        IMPORT_C CAknTextQueryDialog(TDes& aDataText, TDesC& aPrompt,const TTone& aTone = ENoTone);

    private:
        /**
        * From CAknControl
        */
        IMPORT_C void* ExtensionInterface( TUid aInterface );

    private:
        IMPORT_C virtual void CEikDialog_Reserved_1();
        IMPORT_C virtual void CEikDialog_Reserved_2();

    private:
        IMPORT_C virtual void CAknDialog_Reserved();

    private:
        IMPORT_C virtual void CAknQueryDialog_Reserved();

    private: // Data
        TInt iSpare;
    };

//---------------------------------
//class CAknNumberQuerydialog
//---------------------------------

/**
*This class should be used when user is reguest to enter number
*/
class CAknNumberQueryDialog : public CAknQueryDialog
    {

    public:

        /**
         * Second phase construction required to align API with multiline queries
         * and because in future MAknQueryData will be used.
        */
        IMPORT_C static CAknNumberQueryDialog* NewL(TInt& aNumber, const TTone& aTone = ENoTone);

    public:

        /**
         * C++ Constructor.
         */
        IMPORT_C CAknNumberQueryDialog(TInt& aNumber, const TTone& aTone = ENoTone);

        /**
         * C++ Destructor.
         */
        IMPORT_C virtual ~CAknNumberQueryDialog();

    public:

        /**
        * Set maximum and minimum to editor. This override values given in resource.
        *
        * @param aMinimumValue    Minimumm number
        * @param aMaximumValue    Maximum number.
        */
        IMPORT_C void SetMinimumAndMaximum(TInt aMinimumValue, TInt aMaximumValue); // only values inside the initial minimum and maximum are permitted

    public://from CCoeControl

       /**
        * Handles pointer events
        */
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

    protected://from CEikDialog

        /**
        * From @c CEikdialog<p>
        * This function is called by the EIKON dialog framework
        * just before the dialog is activated, after it has called
        * PreLayoutDynInitL() and the dialog has been sized.
        */
        IMPORT_C void PreLayoutDynInitL();

        /**
        * From @c CEikdialog<p>
        * This function is called by the EIKON framework
        * if the user activates a button in the button panel.
        * It is not called if the Cancel button is activated,
        * unless the EEikDialogFlagNotifyEsc flag is set.
        * @param aButtonId  The ID of the button that was activated
        * @return           Should return ETrue if the dialog should exit, and EFalse if it should not.
        */
        IMPORT_C virtual TBool OkToExitL(TInt aButtonId);

        /**
         * @return data
        */
        inline TInt& Number() { return iNumber; }

        /**
         * @return data
        */
        inline const TInt& Number() const { return iNumber; }

    private:
        /**
        * From CAknControl
        */
        IMPORT_C void* ExtensionInterface( TUid aInterface );

    private:
        IMPORT_C virtual void CEikDialog_Reserved_1();
        IMPORT_C virtual void CEikDialog_Reserved_2();

    private:
        IMPORT_C virtual void CAknDialog_Reserved();

    private:
        IMPORT_C virtual void CAknQueryDialog_Reserved();

    protected:

        /**
         * @deprecated - will become private - use Number() instead
         */
         TInt& iNumber;

    private: // Data
        TInt iSpare;
    };

//-------------------------------------
//class CAknTimeQueryDialog
//-------------------------------------

/**
*This class should be used when user is reguest to enter time or date
*/
class CAknTimeQueryDialog : public CAknQueryDialog
    {

    public:

        /**
         * Second phase construction required to align API with multiline queries
         * and because in future MAknQueryData will be used.
        */
        IMPORT_C static CAknTimeQueryDialog* NewL(TTime& aTime, const TTone& aTone = ENoTone);

    public:

        /**
         * C++ Constructor
         */
        IMPORT_C CAknTimeQueryDialog(TTime& aTime, const TTone& aTone = ENoTone);

        /**
         * C++ Destructor.
         */
        IMPORT_C virtual ~CAknTimeQueryDialog();

    public://New functions

        /**
        * Set maximum and minimum times to editor. This override values given in resource.
        * Only values inside the initial minimum and maximum are permitted
        *
        * @param aMinimum    Minimumm time
        * @param aMaximum    Maximum time.
        */
        IMPORT_C void SetMinimumAndMaximum(const TTime& aMinimum, const TTime& aMaximum);

    public://From CCoeControl

        /**
        * Handles pointer events
        */
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

    protected://from CEikDialog

        /**
        * From @c CEikdialog<p>
        * This function is called by the EIKON dialog framework
        * just before the dialog is activated, after it has called
        * PreLayoutDynInitL() and the dialog has been sized.
        */
        IMPORT_C void PreLayoutDynInitL();

        /**
        * From @c CEikdialog<p>
        * This function is called by the EIKON framework
        * if the user activates a button in the button panel.
        * It is not called if the Cancel button is activated,
        * unless the EEikDialogFlagNotifyEsc flag is set.
        * @param aButtonId  The ID of the button that was activated
        * @return           Should return ETrue if the dialog should exit, and EFalse if it should not.
        */
        IMPORT_C virtual TBool OkToExitL(TInt aButtonId);

        /**
         * @return data
        */
        inline TTime& Time() { return iTime; }

        /**
         * @return data
        */
        inline const TTime& Time() const { return iTime; }

    protected:

        /**
         * @deprecated - will become private - use Time() instead
         */
        TTime& iTime;

    public:

        /**
        * deprecated - do not use
        */
        IMPORT_C CAknTimeQueryDialog(TTime& aTime,TDesC& aPrompt,const TTone& aTone = ENoTone);

    private:
        /**
        * From CAknControl
        */
        IMPORT_C void* ExtensionInterface( TUid aInterface );

    private:
        IMPORT_C virtual void CEikDialog_Reserved_1();
        IMPORT_C virtual void CEikDialog_Reserved_2();

    private:
        IMPORT_C virtual void CAknDialog_Reserved();

    private:
        IMPORT_C virtual void CAknQueryDialog_Reserved();

    private: // Data
        TInt iSpare;
    };

//----------------------------------
//class CAknDurationQuerydialog
//----------------------------------

/**
*This class should be used when user is reguest to enter duration
*/
class CAknDurationQueryDialog : public CAknQueryDialog
    {

    public:

        /**
         * Second phase construction required to align API with multiline queries
         * and because in future MAknQueryData will be used.
        */
        IMPORT_C static CAknDurationQueryDialog* NewL(TTimeIntervalSeconds& aTime, const TTone& aTone = ENoTone);

    public:

        /**
         * - deprecated (use NewL instead)
         */
        IMPORT_C CAknDurationQueryDialog(TTimeIntervalSeconds& aDuration, const TTone& aTone = ENoTone);

        /**
         * C++ Destructor.
         */
        IMPORT_C virtual ~CAknDurationQueryDialog();

    public://new

        /**
        * Set maximum and minimum durations to editor. This override values given in resource.
        * Only values inside the initial minimum and maximum are permitted.
        *
        * @param aMinimumDuration   Minimumm duration
        * @param aMaximumDuration   Maximum duration.
        */
        IMPORT_C void SetMinimumAndMaximum(const TTimeIntervalSeconds& aMinimumDuration, const TTimeIntervalSeconds& aMaximumDuration);

    public: // From CCoeControl

        /**
        * Handles pointer events
        */
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

    protected://from CEikDialog

        /**
        * From @c CEikdialog<p>
        * This function is called by the EIKON dialog framework
        * just before the dialog is activated, after it has called
        * PreLayoutDynInitL() and the dialog has been sized.
        */
        IMPORT_C void PreLayoutDynInitL();

        /**
         * From @c CEikdialog<p>
         * This function is called by the EIKON framework
         * if the user activates a button in the button panel.
         * It is not called if the Cancel button is activated,
         * unless the EEikDialogFlagNotifyEsc flag is set.
         * @param aButtonId  The ID of the button that was activated
         * @return           Should return ETrue if the dialog should exit, and EFalse if it should not.
        */
        IMPORT_C virtual TBool OkToExitL(TInt aButtonId);

        /**
         * @return data
        */
        inline TTimeIntervalSeconds& Duration() { return iDuration; }

        /**
         * @return data
        */
        inline const TTimeIntervalSeconds& Duration() const { return iDuration; }

    private:
        /**
        * From CAknControl
        */
        IMPORT_C void* ExtensionInterface( TUid aInterface );

    private:
        IMPORT_C virtual void CEikDialog_Reserved_1();
        IMPORT_C virtual void CEikDialog_Reserved_2();

    private:
        IMPORT_C virtual void CAknDialog_Reserved();

    private:
        IMPORT_C virtual void CAknQueryDialog_Reserved();

    protected:
        /**
         * @deprecated - will become private. Use Duration() instead.
         */
         TTimeIntervalSeconds& iDuration;

    private: // Data
        TInt iSpare;
    };

//----------------------------------
//class CAknFloatingPointQueryDialog
//----------------------------------

/**
*This class should be used when user is reguest to enter a flotaing point number
*/
class CAknFloatingPointQueryDialog : public CAknQueryDialog
    {

    public:
        /**
         * Second phase construction required to align API with multiline queries
         * and because in future MAknQueryData will be used.
        */
        IMPORT_C static CAknFloatingPointQueryDialog* NewL(TReal& aNumber, const TTone& aTone = ENoTone);

    public:
        /**
         * deprecated (use NewL instead)
         */
        IMPORT_C CAknFloatingPointQueryDialog(TReal& aNumber, const TTone& aTone = ENoTone);

        /**
         * C++ Destructor.
         */
        IMPORT_C virtual ~CAknFloatingPointQueryDialog();

    public:
        /**
        * Set maximum and minimum durations to editor. This override values given in resource.
        * only values inside the initial minimum and maximum are permitted
        *
        * @param aMinimumNumber   Minimumm duration
        * @param aMaximumNumber   Maximum duration.
        */
        IMPORT_C void SetMinimumAndMaximum(const TReal& aMinimumNumber, const TReal& aMaximumNumber);

    public://From CCoeControl

       /**
        * Handles pointer events
        */
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

    protected://from CEikDialog

        /**
        * From @c CEikdialog<p>
        * This function is called by the EIKON dialog framework
        * just before the dialog is activated, after it has called
        * PreLayoutDynInitL() and the dialog has been sized.
        */
        IMPORT_C void PreLayoutDynInitL();

        /**
         * From @c CEikdialog<p>
         * This function is called by the EIKON framework
         * if the user activates a button in the button panel.
         * It is not called if the Cancel button is activated,
         * unless the EEikDialogFlagNotifyEsc flag is set.
         * @param aButtonId  The ID of the button that was activated
         * @return           Should return ETrue if the dialog should exit, and EFalse if it should not.
        */
        IMPORT_C virtual TBool OkToExitL(TInt aButtonId);

        /**
         * @return data
        */
        inline TReal& Number() { return iNumber; }

        /**
         * @return data
        */
        inline const TReal& Number() const { return iNumber; }

    private:
        /**
        * From CAknControl
        */
        IMPORT_C void* ExtensionInterface( TUid aInterface );

    private:
        IMPORT_C virtual void CEikDialog_Reserved_1();
        IMPORT_C virtual void CEikDialog_Reserved_2();

    private:
        IMPORT_C virtual void CAknDialog_Reserved();

    private:
        IMPORT_C virtual void CAknQueryDialog_Reserved();

    protected:
        /**
         * @deprecated - will become private - use Number() instead
         */
        TReal& iNumber;

    private:
        TInt iSpare;
    };


//--------------------------------------
//class CAknMultilineDataQuerydialog
//--------------------------------------

/**
 * Query dialog with data input on more than one line (2 lines at the moment).
 *
 * Object of this class is created by using NewL method and by passing
 * parameters as appropriate.
 *
 * Attention: When deriving from this class, you must call @c SetDataL() during
 *            second phase construction.
 *
 * Enumeration for tones. The tone played before the dialog is shown.
 * Application specific tones may be played by casting the application defined
 * Sound ID @c (SID), to @c TTone.
 *
 * Enumeration values: <br>
 * @c ENoTone No tone is played.<br>
 * @c EConfirmationTone A confirmation tone is played. <br>
 * @c EWarningTone A warning tone is played. <br>
 * @c EErrorTone An error tone is played. <br>
 */
class CAknMultiLineDataQueryDialog : public CAknQueryDialog
    {
    friend class CAknMultilineQueryDialogExtension;

    public:

        /**
         * Creates a new instance of a multiline dialog.
         *
         * @param aTime1 First line parameter.
         * @param aTime2 Second line parameter.
         * @param aTone Reference to @c TTone enumeration. Default is @c
         *        ENoTone.
         * @return Pointer to a multiline dialog object.
         */
        IMPORT_C static CAknMultiLineDataQueryDialog* NewL(
                TTime& aTime1,
                TTime& aTime2,
                TTone aTone = ENoTone);

        /**
         * Creates a new instance of a multiline dialog.
         *
         * @param aText1 First line parameter.
         * @param aText2 Second line parameter.
         * @param aTone Reference to @c TTone enumeration. Default is @c
         *        ENoTone.
         * @return Pointer to a multiline dialog object.
         */
        IMPORT_C static CAknMultiLineDataQueryDialog* NewL(
                TDes& aText1,
                TDes& aText2,
                TTone aTone = ENoTone);

        /**
         * Creates a new instance of a multiline dialog.
         *
         * @param aText1 First line parameter.
         * @param aTime2 Second line parameter.
         * @param aTone Reference to @c TTone enumeration. Default is @c
         *        ENoTone.
         * @return Pointer to a multiline dialog object.
         */
        IMPORT_C static CAknMultiLineDataQueryDialog* NewL(
                TDes& aText1,
                TTime& aTime2,
                TTone aTone = ENoTone);

        /**
         * Creates a new instance of a multiline dialog.
         *
         * @param aText1 First line parameter.
         * @param aNum2 Second line parameter.
         * @param aTone Reference to @c TTone enumeration. Default is @c
         *        ENoTone.
         * @return Pointer to a multiline dialog object.
         */
        IMPORT_C static CAknMultiLineDataQueryDialog* NewL(
                TDes& aText1,
                TInt& aNum2,
                TTone aTone = ENoTone);

        /**
         * Creates a new instance of a multiline dialog.
         *
         * @param aText1 First line parameter.
         * @param aDur2 Second line parameter.
         * @param aTone Reference to @c TTone enumeration. Default is @c
         *        ENoTone.
         * @return Pointer to a multiline dialog object.
         */
        IMPORT_C static CAknMultiLineDataQueryDialog* NewL(
                TDes& aText1,
                TTimeIntervalSeconds& aDur2,
                TTone aTone = ENoTone);

        /**
         * Creates a new instance of a multiline dialog.
         *
         * @param aTime1 First line parameter.
         * @param aDur2 Second line parameter.
         * @param aTone Reference to @c TTone enumeration. Default is @c
         *        ENoTone.
         * @return Pointer to a multiline dialog object.
         */
        IMPORT_C static CAknMultiLineDataQueryDialog* NewL(
                TTime& aTime1,
                TTimeIntervalSeconds& aDur2,
                TTone aTone = ENoTone);

        /**
         * Creates a new instance of a multiline dialog.
         *
         * @param aNum1 First line parameter.
         * @param aNum2 Second line parameter.
         * @param aTone Reference to @c TTone enumeration. Default is @c
         *        ENoTone.
         * @return Pointer to multiline dialog object.
         */
        IMPORT_C static CAknMultiLineDataQueryDialog* NewL(
                TInt& aNum1,
                TInt& aNum2,
                TTone aTone = ENoTone);

         /**
         * Creates a new instance of a multiline dialog.
         *
         * @param aPos Position parameter.
         * @param aTone Reference to @c TTone enumeration. Default is @c
         *        ENoTone.
         * @return Pointer to multiline dialog object.
         */
        IMPORT_C static CAknMultiLineDataQueryDialog* NewL(TPosition &aPos, TTone aTone = ENoTone);


        /**
         * Destructor.
         */
        IMPORT_C virtual ~CAknMultiLineDataQueryDialog();

    protected:

        /**
         * Sets the query data for the first and the second line. Must be
         * called by derived classes during second phase construction (@c
         * NewL() method).
         */
        template <class T1, class T2> void SetDataL(T1& aData1, T2& aData2)
            {
            /** First line data. */
            iFirstData  = new (ELeave) TAknQueryData<T1>(aData1);

            /** Second line data. */
            iSecondData = new (ELeave) TAknQueryData<T2>(aData2);
            }

        /**
         * Utility function called by @c NewL() method - should really be
         * private but it is left here to show to people extending this class
         * what their @c NewL() method should do.
         *
         * Creates new instance of the multiline dialog.
         *
         * @param aData1 First line parameter.
         * @param aData2 Second line parameter.
         * @param aTone Reference to @c TTone enum.
         */

        template <class T1, class T2> static CAknMultiLineDataQueryDialog*
            DoNewL(T1& aData1, T2& aData2, const TTone& aTone)
            {
                CAknMultiLineDataQueryDialog* self =
                            new (ELeave) CAknMultiLineDataQueryDialog(aTone);

                CleanupStack::PushL(self);

                self->SetDataL(aData1,aData2);

                CleanupStack::Pop(self);
                return self;
            }

    protected:

        /**
         * C++ default constructor.
         *
         * @param aTone Reference to @c TTone enumeration.
         */
        IMPORT_C CAknMultiLineDataQueryDialog(const TTone& aTone);

    public:

        /**
         * Sets a prompt text for the query. This will override the text given
         * in the constructor.
         *
         * @param aFirstPrompt Text for prompt on the first query line.
         * @param aSecondPrompt Text for prompt on the second query line.
         */
        IMPORT_C void SetPromptL(const TDesC& aFirstPrompt,
                                 const TDesC& aSecondPrompt);

    public:

        /**
         * Sets a max length for the first editor in a query.
         *
         * @param aFirstTextEditorMaxLength Max length for editor
         */
        IMPORT_C void SetMaxLengthOfFirstEditor(
                                TInt aFirstTextEditorMaxLength);

        /**
         * Sets a max length for the second editor in a query.
         *
         * @param aSecondTextEditorMaxLength Max length for editor.
         */
        IMPORT_C void SetMaxLengthOfSecondEditor(
                                TInt aSecondTextEditorMaxLength);

    public: // From CCoeControl

        /**
         * From @c CCoeControl.
         *
         * Handles pointer events.
         *
         * @param aPointerEvent The pointer event.
         */
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

    protected://from CEikDialog

        /**
         * From @c CEikdialog<p>
         * This function is called by the @c EIKON framework if the user
         * activates a button in the button panel. It is not called if the @c
         * Cancel button is activated, unless the @c EEikDialogFlagNotifyEsc
         * flag is set.
         *
         * @param aButtonId The ID of the button that was activated.
         * @return @c ETrue if the dialog should exit and @c
         *         EFalse if it should not exit.
         */
        IMPORT_C virtual TBool OkToExitL(TInt aButtonId);

         /**
         * From @c CEikdialog<p>
         * This function is called by the EIKON dialog framework
         * just before the dialog is activated, after it has called
         * PreLayoutDynInitL() and the dialog has been sized.
         * Note:<p>
         * Control values that should not influence the sizing and layout are
         * set using @c PostLayoutDynInitL().
         */
        IMPORT_C void PreLayoutDynInitL();

        /**
         * From @c CCoeControl.
         *
         * Handles a change to the control's resources. The types of resources
         * handled are those which are shared across the environment, e.g.
         * colours or fonts.
         *
         * @since Symbian 5.1.
         *
         * @param aType A message UID value. The most common is @c
         *        KEikMessageColorSchemeChange which controls get when the
         *        colour scheme is changed. Other examples include: @c
         *        KEikMessageFadeAllWindows, @c KEikMessageUnfadeWindows, @c
         *        KEikMessageZoomChange, @c
         *        KEikMessageVirtualCursorStateChange, @c KEikMessageCapsLock,
         *        @c KEikMessagePrepareForSave.
         */
        IMPORT_C void HandleResourceChange(TInt aType);

    protected:

        /**
        * If the query text is ok (retrieved form query controls)  the left
        * soft key is displayed, otherwise it is hidden.
        */
        IMPORT_C void UpdateLeftSoftKeyL();

        /**
        * Sets the prompt inside the query control.
        */
        IMPORT_C void DoSetPromptL();

    protected:

         /**
          * Allows dismissing of queries. Same as base class implementation only take into
          * consideration both controls
         */
        IMPORT_C TBool NeedToDismissQueryL(const TKeyEvent& aKeyEvent);

    protected:

        /**
         * Access to 1st query control
         *
         * @return Pointer to the control of the first line.
         */
        IMPORT_C CAknMultilineQueryControl* FirstControl() const;

        /**
         * Access to 2nd query control
         *
         * @return Pointer to the control of the second line.
         */
        IMPORT_C CAknMultilineQueryControl* SecondControl() const;

        /**
         * Gets a querycontrol.
         *
         * @return Pointer to the control of the first line.
         */
         IMPORT_C CAknQueryControl* QueryControl() const;

        /**
         * Not implemented.
         *
         * @return NULL.
         */
        IMPORT_C CAknPopupHeadingPane* QueryHeading() const;

    protected:

        /**
         * Data access.
         *
         * Derived class can use this method to get access to the query
         * data. The query data is a reference stored in @c TAknQueryData, see
         * @c aknquerydata.h
         *
         * The client ultimately owns the data this reference references and so
         * it should never need to call these methods.
         *
         * Derived class however, might need to set or get the data and hence
         * this method have been provided. The derived class is responsible
         * for choosing the correct type, if not the cast will fail.
         */
        template<class T>
            T& FirstData(const T&)
            { return STATIC_CAST(TAknQueryData<T>*,iFirstData)->iData; }

        /**
         * Data access.
         *
         * Derived class can use this method to get access to the query
         * data. The query data is a reference stored in @c TAknQueryData, see
         * @c aknquerydata.h
         *
         * The client ultimately owns the data this reference references and so
         * it should never need to call these methods.
         *
         * Derived class however, might need to set or get the data and hence
         * this method have been provided. The derived class is responsible
         * for choosing the correct type, if not the cast will fail.
         */
        template<class T>
            T& SecondData(const T&)
            { return STATIC_CAST(TAknQueryData<T>*,iSecondData)->iData; }

        /**
         * Data access.
         *
         * Derived class can use this method to get access to the query
         * data. The query data is a reference stored in @c TAknQueryData, see
         * @c aknquerydata.h
         *
         * The client ultimately owns the data this reference references and so
         * it should never need to call these methods.
         *
         * Derived class however, might need to set or get the data and hence
         * this method have been provided. The derived class is responsible
         * for choosing the correct type, if not the cast will fail.
         */
        template<class T>
            const T& FirstData(const T&) const
            { return STATIC_CAST(TAknQueryData<T>*,iFirstData)->iData; }

        /**
         * Data access.
         *
         * Derived class can use this method to get access to the query
         * data. The query data is a reference stored in @c TAknQueryData, see
         * @c aknquerydata.h
         *
         * The client ultimately owns the data this reference references and so
         * it should never need to call these methods.
         *
         * Derived class however, might need to set or get the data and hence
         * this method have been provided. The derived class is responsible
         * for choosing the correct type, if not the cast will fail.
         */
        template<class T>
            const T& SecondData(const T&) const
            { return STATIC_CAST(TAknQueryData<T>*,iSecondData)->iData; }

        /**
         * Prompts access for derived classes.
         *
         * @return Pointer to the data of the second line.
         */
        IMPORT_C TPtrC SecondPrompt() const;

    private:
        void HandleOrientationSwitch();
        TBool FirstLineEnabled() const;
        TBool SecondLineEnabled() const;
        TInt CurrentLine() const;

    private:
        TDesC* iSecondPrompt;
        MAknQueryData* iFirstData;
        MAknQueryData* iSecondData;

        TInt iFirstEditorMaxLength;
        TInt iSecondEditorMaxLength;

    public:

        /**
         * Constructor.
         *
         * @param aTime First line parameter.
         * @param aTime2 Second line parameter.
         * @param aPrompt First prompt value. NULL in default.
         * @param aPrompt2 Second prompt value. NULL in default.
         * @param aTone Reference to @c TTone enum. Default is @c ENoTone.
         */
        IMPORT_C CAknMultiLineDataQueryDialog(
                TTime* aTime,
                TTime* aTime2,
                TDesC* aPrompt=NULL,
                TDesC* aPrompt2=NULL,
                const TTone& aTone = ENoTone);

        /**
         * Constructor.
         *
         * @param aDataText First line parameter.
         * @param aDataText2 Second line parameter.
         * @param aPrompt First prompt value. NULL in default.
         * @param aPrompt2 Second prompt value. NULL in default.
         * @param aTone Reference to @c TTone enum. Default is @c ENoTone.
         */
        IMPORT_C CAknMultiLineDataQueryDialog(
                TDes* aDataText,
                TDes* aDataText2,
                TDesC* aPrompt=NULL,
                TDesC* aPrompt2=NULL,
                const TTone& aTone = ENoTone);

        /**
         * Constructor.
         *
         * @param aDataText First line parameter.
         * @param aTime Second line parameter.
         * @param aPrompt First prompt value. NULL in default.
         * @param aPrompt2 Second prompt value. NULL in default.
         * @param aTone Reference to @c TTone enum. Default is @c ENoTone.
         */
        IMPORT_C CAknMultiLineDataQueryDialog(
                TDes* aDataText,
                TTime* aTime,
                TDesC* aPrompt=NULL,
                TDesC* aPrompt2=NULL,
                const TTone& aTone = ENoTone);

        /**
         * Constructor.
         *
         * @param aDataText First line parameter.
         * @param aNumber Second line parameter.
         * @param aPrompt First prompt value. NULL in default.
         * @param aPrompt2 Second prompt value. NULL in default.
         * @param aTone Reference to @c TTone enum. Default is @c ENoTone.
         */
        IMPORT_C CAknMultiLineDataQueryDialog(
                TDes* aDataText,
                TInt* aNumber,
                TDesC* aPrompt=NULL,
                TDesC* aPrompt2=NULL,
                const TTone& aTone = ENoTone);

        /**
         * Constructor.
         *
         * @param aDataText First line parameter.
         * @param aDuration Second line parameter.
         * @param aPrompt First prompt value. NULL in default.
         * @param aPrompt2 Second prompt value. NULL in default.
         * @param aTone Reference to @c TTone enum. Default is @c ENoTone.
         */
        IMPORT_C CAknMultiLineDataQueryDialog(
                TDes* aDataText,
                TTimeIntervalSeconds* aDuration,
                TDesC* aPrompt=NULL,
                TDesC* aPrompt2=NULL,
                const TTone& aTone = ENoTone);

        /**
         * Constructor.
         *
         * @param aTime First line parameter.
         * @param aDuration Second line parameter.
         * @param aPrompt First prompt value. NULL in default.
         * @param aPrompt2 Second prompt value. NULL in default.
         * @param aTone Reference to @c TTone enum. Default is @c ENoTone.
         */
        IMPORT_C CAknMultiLineDataQueryDialog(
                TTime* aTime,
                TTimeIntervalSeconds* aDuration,
                TDesC* aPrompt=NULL,
                TDesC* aPrompt2=NULL,
                const TTone& aTone = ENoTone);

        /**
         * Constructor.
         *
         * @param aNumber First line parameter.
         * @param aNumber2 Second line parameter.
         * @param aPrompt First prompt value. NULL in default.
         * @param aPrompt2 Second prompt value. NULL in default.
         * @param aTone Reference to @c TTone enum. Default is @c ENoTone.
         */
        IMPORT_C CAknMultiLineDataQueryDialog(
                TInt* aNumber,
                TInt* aNumber2,
                TDesC* aPrompt=NULL,
                TDesC* aPrompt2=NULL,
                const TTone& aTone = ENoTone);

    private:
        /**
        * From CAknControl
        */
        IMPORT_C void* ExtensionInterface( TUid aInterface );

    private:
        IMPORT_C virtual void CEikDialog_Reserved_1();
        IMPORT_C virtual void CEikDialog_Reserved_2();

    private:
        IMPORT_C virtual void CAknDialog_Reserved();

    private:
        IMPORT_C virtual void CAknQueryDialog_Reserved();

    protected:
        /**
         * Deprecated - use data access template methods instead
         * A text of the first line.
         * @deprecated Use data access template methods instead.
         */
        TDes16* iText;

        /**
         * Deprecated do not use
         * A text of the secondline.
         * @deprecated Use data access template methods instead.
         */
        TDes16* iSecondText;
    };

//Deprecated
//This one is included here for backwards compatibility
//and will be removed as soon as apps using listquerydialog
//include it directly
#include <aknlistquerydialog.h>


//---------------------------------
//class CAknIpAddressQueryDialog
//---------------------------------

/**
 * This class should be used when user is reguest to enter IP address
 *
 * @since 2.1
*/

NONSHARABLE_CLASS(CAknIpAddressQueryDialog) : public CAknQueryDialog
    {

    public:
        /**
         * Second phase construction
         *
        */
        IMPORT_C static CAknIpAddressQueryDialog* NewL(TInetAddr& aInetAddr, const TTone& aTone = ENoTone);

    private:
        CAknIpAddressQueryDialog(TInetAddr& aInetAddr, const TTone& aTone = ENoTone);

    public:
        /**
         * C++ Destructor.
         */
        IMPORT_C virtual ~CAknIpAddressQueryDialog();

    public:
        /**
        * Set maximum and minimum addresses to editor. This override values given in resource.
        * only values inside the initial minimum and maximum are permitted
        *
        * @param aMinimumAddress   Minimumm address
        * @param aMaximumAddress   Maximum address.
        */
        IMPORT_C void SetMinimumAndMaximum(const TInetAddr& aMinimumAddress, const TInetAddr& aMaximumAddress);

        /**
        * Allows dismissing of queries.
        * Clients can override this and implement something different.
        *
        */
        IMPORT_C virtual TBool NeedToDismissQueryL(const TKeyEvent& aKeyEvent);


    protected:

        /**
        * @return pointer to query control or NULL
        *
        */
        IMPORT_C virtual CAknQueryControl* QueryControl() const;

    protected://from CEikDialog

        /**
        * From CEikdialog   EIKON provides an implementation of this function,
        *                   which positions the dialog in the centre of the screen.
        *                   However, it can be overridden by derived classes..
        * @param aSize      The size for the dialog.
        */
        IMPORT_C void SetSizeAndPosition(const TSize& aSize);

        /**
         * From @c CEikdialog<p>
         * This function is called by the EIKON dialog framework just before the dialog is activated, but before it is sized,
         * and before PostLayoutDynInitL() is called.
        */
        IMPORT_C void PreLayoutDynInitL();

        /**
         * From @c CEikdialog<p>
         * This function is called by the EIKON dialog framework just before the dialog is activated,
         * after it has called PreLayoutDynInitL() and the dialog has been sized.
        */
        IMPORT_C void PostLayoutDynInitL();

        /**
        * Set the prompt inside the query control. If dialog is active redo
        * layout and draw.
        */
        IMPORT_C virtual void DoSetPromptL();

        /**
         * From @c CEikdialog<p>
         * This function is called by the EIKON framework
         * if the user activates a button in the button panel.
         * It is not called if the Cancel button is activated,
         * unless the EEikDialogFlagNotifyEsc flag is set.
         * @param aButtonId  The ID of the button that was activated
         * @return           Should return ETrue if the dialog should exit, and EFalse if it should not.
        */
        IMPORT_C virtual TBool OkToExitL(TInt aButtonId);

        /**
        * If the query text is ok (retrieved form query control) then display the
        * left soft key, otherwise hide it.
        */
         IMPORT_C void UpdateLeftSoftKeyL();

        /**
         * @return data
        */
         inline TInetAddr& InetAddr() { return iInetAddr; }

        /**
         * @return data
        */
         inline const TInetAddr& InetAddr() const { return iInetAddr; }

    private:
        IMPORT_C virtual void CEikDialog_Reserved_1();
        IMPORT_C virtual void CEikDialog_Reserved_2();

    private:
        IMPORT_C virtual void CAknDialog_Reserved();

    private:
        IMPORT_C virtual void CAknQueryDialog_Reserved();

    protected:
        /**
         * data
         */
         TInetAddr& iInetAddr;
    };


//---------------------------------
//class CAknFixedPointQueryDialog
//---------------------------------

/**
 * This class should be used when user is reguest to enter IP address
 *
 * @since 2.1
*/

NONSHARABLE_CLASS(CAknFixedPointQueryDialog) : public CAknQueryDialog
    {
    public:
        /**
         * Second phase construction
         *
        */
        IMPORT_C static CAknFixedPointQueryDialog* NewL(TInt& aNumber, const TTone& aTone);

    private:
        CAknFixedPointQueryDialog(TInt& aNumber, const TTone& aTone = ENoTone);

    public:

        /**
         * C++ Destructor.
         */
        IMPORT_C virtual ~CAknFixedPointQueryDialog();

    public: //new
        /**
        * Set maximum and minimum addresses to editor. This override values given in resource.
        *
        * @param aMinimumValue   Minimumm value
        * @param aMaximumValue   Maximum value.
        */
        IMPORT_C void SetMinimumAndMaximum(TInt aMinimumValue, TInt aMaximumValue); // only values inside the initial minimum and maximum are permitted

        IMPORT_C virtual TBool NeedToDismissQueryL(const TKeyEvent& aKeyEvent);


    protected:

        /**
        * Usage:
        * CAknExtQueryControl* control = STATIC_CAST(CAknExtQueryControl*,QueryControl());
        *
        */
        IMPORT_C virtual CAknQueryControl* QueryControl() const;

    protected://from CEikDialog

        /**
        * From CEikdialog   EIKON provides an implementation of this function,
        *                   which positions the dialog in the centre of the screen.
        *                   However, it can be overridden by derived classes..
        * @param aSize      The size for the dialog.
        */
        IMPORT_C void SetSizeAndPosition(const TSize& aSize);

        /**
         * From @c CEikdialog<p>
         * This function is called by the EIKON dialog framework just before the dialog is activated, but before it is sized,
         * and before PostLayoutDynInitL() is called.
        */
        IMPORT_C void PreLayoutDynInitL();

        /**
         * From @c CEikdialog<p>
         * This function is called by the EIKON dialog framework just before the dialog is activated,
         * after it has called PreLayoutDynInitL() and the dialog has been sized.
        */
        IMPORT_C void PostLayoutDynInitL();

        /**
        * Set the prompt inside the query control. If dialog is active redo
        * layout and draw.
        */
        IMPORT_C virtual void DoSetPromptL();

        /**
         * From @c CEikdialog<p>
         * This function is called by the EIKON framework
         * if the user activates a button in the button panel.
         * It is not called if the Cancel button is activated,
         * unless the EEikDialogFlagNotifyEsc flag is set.
         * @param aButtonId  The ID of the button that was activated
         * @return           Should return ETrue if the dialog should exit, and EFalse if it should not.
        */
        IMPORT_C virtual TBool OkToExitL(TInt aButtonId);

        /**
        * If the query text is ok (retrieved form query control) then display the
        * left soft key, otherwise hide it.
        */
        IMPORT_C void UpdateLeftSoftKeyL();

        /**
         * @return data
        */
        inline TInt& Number() { return iNumber; }

        /**
         * @return data
        */
        inline const TInt& Number() const { return iNumber; }

    private:
        IMPORT_C virtual void CEikDialog_Reserved_1();
        IMPORT_C virtual void CEikDialog_Reserved_2();
    private:
        IMPORT_C virtual void CAknDialog_Reserved();
    private:
        IMPORT_C virtual void CAknQueryDialog_Reserved();
    private:
         TInt& iNumber;
    };


//--------------------------------------
//class CAknMultilineIpQueryDialog
//--------------------------------------

/**
 * Query Dialog with data input on more than one line (2 lines at the moment)
 *
 * Create using NewL methods and passing parameters as appropriate.
 *
 * Attention: When deriving from this class, you must call SetDataL during
 *            second phase construction.
 *
 * @since 2.1
 *
 */
NONSHARABLE_CLASS(CAknMultiLineIpQueryDialog) : public CAknMultiLineDataQueryDialog
    {
    friend class CAknMultilineQueryDialogExtension;
    public:
        /**
         * Second phase construction
         *
        */
        IMPORT_C static CAknMultiLineIpQueryDialog* NewL(TInetAddr&  aAddress1,  TInetAddr&  aAddress2, TTone aTone = ENoTone);

        IMPORT_C virtual ~CAknMultiLineIpQueryDialog();

    protected:
        /**
         * Set the query data for first and second line
         * Must be called by derived classes during second phase construction
         * (NewL method)
         */
        template <class T1, class T2> void SetDataL(T1& aData1, T2& aData2)
            {
            iFirstData  = new (ELeave) TAknQueryData<T1>(aData1);
            iSecondData = new (ELeave) TAknQueryData<T2>(aData2);
            }

        /**
         * Utility function called by NewL methods - should really be private
         * but it is left here to show to people extending this class what
         * their NewL method should do
         */
        template <class T1, class T2> static CAknMultiLineIpQueryDialog*
            DoNewL(T1& aData1, T2& aData2, const TTone& aTone)
            {
                CAknMultiLineIpQueryDialog* self = new (ELeave) CAknMultiLineIpQueryDialog(aTone);
                CleanupStack::PushL(self);

                self->SetDataL(aData1,aData2);

                CleanupStack::Pop(self);
                return self;
            }

    private:
        CAknMultiLineIpQueryDialog(const TTone& aTone);

    public:

        /**
        * Set prompt text for query. This this will override text given in constructor.
        *
        * @param aFirstPrompt   Text for prompt on the first query line
        * @param aSecondPrompt  Text for prompt on the second query line
        */
        IMPORT_C void SetPromptL(const TDesC& aFirstPrompt, const TDesC& aSecondPrompt);

    public:

        /**
        * Sets max length for the first editor in a query
        * @param aFirstTextEditorMaxLength  Max length for editor
        */
        IMPORT_C void SetMaxLengthOfFirstEditor(TInt aFirstTextEditorMaxLength);

        /**
        * Sets max length for the second editor in a query
        * @param aSecondTextEditorMaxLength  Max length for editor
        */
        IMPORT_C void SetMaxLengthOfSecondEditor(TInt aSecondTextEditorMaxLength);

    protected://from CEikDialog

        /**
         * From @c CEikdialog<p>
         * This function is called by the EIKON framework
         * if the user activates a button in the button panel.
         * It is not called if the Cancel button is activated,
         * unless the EEikDialogFlagNotifyEsc flag is set.
         * @param aButtonId  The ID of the button that was activated
         * @return           Should return ETrue if the dialog should exit, and EFalse if it should not.
        */
        IMPORT_C virtual TBool OkToExitL(TInt aButtonId);

        /**
         * From @c CEikdialog<p>
         * This function is called by the EIKON dialog framework just before the dialog is activated, but before it is sized,
         * and before PostLayoutDynInitL() is called.
        */
        IMPORT_C void PreLayoutDynInitL();

        IMPORT_C void HandleResourceChange(TInt aType);

    protected:
        /**
        * If the query text is ok (retrieved form query controls) then display the
        * left soft key, otherwise hide it.
        */
        IMPORT_C void UpdateLeftSoftKeyL();

        /**
        * Set the prompt inside the query control. If dialog is active redo
        * layout and draw.
        */
        IMPORT_C void DoSetPromptL();

    protected:
        /**
         * Called by OfferkeyEventL(), gives a change to dismiss the query even with
         * keys different than Enter of Ok.
         *
         * @param aKeyEvent  Key event which will be checked
         * @return           Should the query be dismissed
         */
        IMPORT_C TBool NeedToDismissQueryL(const TKeyEvent& aKeyEvent);

    protected:
        /**
         * Access to 1st query control
         *
         * @return Pointer to the control of the first line.
         */
        IMPORT_C CAknExtMultilineQueryControl* FirstControl() const;

         /**
         * Access to 2nd query control
         *
         * @return Pointer to the control of the second line.
         */
        IMPORT_C CAknExtMultilineQueryControl* SecondControl() const;

         /**
         * Not implemented.
         *
         * @return NULL.
         */
        IMPORT_C CAknQueryControl* QueryControl() const;

    protected:
        /**
         * Prompt access for derived classes
         */
        IMPORT_C TPtrC SecondPrompt() const;

    private:
        void HandleOrientationSwitch();
        TBool FirstLineEnabled() const;
        TBool SecondLineEnabled() const;
        TInt CurrentLine() const;

    private:
        TDesC* iSecondPrompt;

        MAknQueryData* iFirstData;
        MAknQueryData* iSecondData;

        TInt iFirstEditorMaxLength;
        TInt iSecondEditorMaxLength;

    private:
        TDes16* iText;
        TDes16* iSecondText;
    };

#endif // AKNQUERYDIALOG_H
