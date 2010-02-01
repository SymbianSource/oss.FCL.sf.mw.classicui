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
* Description:  Popup form for adding custom controls to popup dialog
*
*/


#ifndef __AKNPOPUPFORM__
#define __AKNPOPUPFORM__

//  INCLUDES
#include <avkon.hrh>
#include <AknDialog.h>
#include <babitflags.h>

// DATA TYPES

/**
 * The tone played before the dialog is shown.
   Application specific tones may be played by casting the application
   defined Sound ID (SID), to TTone
*/
enum TTone {
    ENoTone = 0,
    EConfirmationTone = EAvkonSIDConfirmationTone,
    EWarningTone = EAvkonSIDWarningTone,
    EErrorTone = EAvkonSIDErrorTone,
    EInformationTone = EAvkonSIDInformationTone,
    EAlertTone = EAvkonSIDInformationTone
    };
/**
 * The type the popupform represents.
   Used to determine the right skin background.
*/
enum TPopupFormType {
    EAknQuery,
    EAknNote
    };

/**
 * The type of the animation.
 * Used to calculate the sizes of the editor and the form.
*/
enum TAnimationType {
    ERegularAnimation,
    EWaitAnimation
    };

enum TPopupFormInternalFlags
    {
    EPopupFormHasHeading = 1,
    EPopupFormHasImage,
    EPopupFormHasAnimation,
    EPopupFormHasWaitAnim,
    EPopupFormHasProgbar,
    EPopupFormHasEditor,
    EPopupFormHasSpacer,
    EPopupFormUsesPlainFont
    };

enum TPopupFormControlType
    {
    EPopupFormUnknown = -1,
    EPopupFormHeading = 1,
    EPopupFormImage,
    EPopupFormAnimation,
    EPopupFormWaitAnim,
    EPopupFormProgbar,
    EPopupFormEditor,
    EPopupFormSpacer,
    };

// FORWARD DECLARATIONS
class CAknKeySoundSystem;
class CEikScrollBarFrame;
class CEikSpacer;
class CEikProgressInfo;
class CEikRichTextEditor;
class CEikImage;
class CEikCaptionedControl;
class CAknsBasicBackgroundControlContext;
class CAknPopupFormExtension;
class CAknBitmapAnimation;
class TAknMultiLineTextLayout;

/**
 * The callback class.
 * Users of progress info should inherit from this
 * and implement DialogDismissedL.
*/
class MPopupFormProgressCallback
    {
    public:
        /**
        * Callback method
        *   Gets called when a popupform with a
        *   progress bar is dismissed.
        */
        virtual void DialogDismissedL( TInt aButtonId ) = 0;
    };

// CLASS DECLARATION
/**
*  General popup component
*
*  @lib avkon.lib
*  @since 2.6
*/
class CAknPopupForm : public CAknDialog
    {
    public: // Constructors and destructor

        /**
        * C++ default constructor.
        */
        IMPORT_C CAknPopupForm();
        /**
        * C++ default constructor.
        */
        IMPORT_C CAknPopupForm( const TTone& aTone, const TInt aTimeout,
                       const TPopupFormType& aType );
        /**
        * Two-phased constructor.
        */
        IMPORT_C static CAknPopupForm* NewLC( const TTone& aTone,
                                    const TInt aTimeout = 0,
                                    const TPopupFormType& aType = EAknNote );
        /**
        * Two-phased constructor.
        */
        IMPORT_C static CAknPopupForm* NewL( const TTone& aTone,
                                    const TInt aTimeout = 0, const
                                    TPopupFormType& aType = EAknNote );
        /**
        * Two-phased constructor.
        */
        IMPORT_C static CAknPopupForm* NewLC();
        /**
        * Two-phased constructor.
        */
        IMPORT_C static CAknPopupForm* NewL();
        /**
        * Destructor.
        */
        IMPORT_C virtual ~CAknPopupForm();

    protected:
        /**
        * 2nd phase constructor.
        * Derived classes must call this method
        */
        IMPORT_C void ConstructL();


    public: // New functions

        /**
        * Sets the dialog timeout.
        * @since 2.6
        * @param aTimeoutInSeconds The timeout. If 0 then Cancel the timer.
        */
        IMPORT_C void SetTimeout( const TInt aTimeoutInSeconds );
        /**
        * Sets the dialog tone.
        * @since 2.6
        * @param aTone The tone
        */
        IMPORT_C void SetTone( const TTone aTone );
        /**
        * Sets the dialog type.
        * @since 2.6
        * @param aType The type this dialog represents (note or query)
        */
        IMPORT_C void SetPopupFormType( const TPopupFormType aType );
        /**
        * Sets the dialog title.
        * @since 2.6
        * @param aTitle The title
        */
        IMPORT_C void SetTitleL( const TDesC& aTitle );
        /**
        * Sets the dialog text.
        * @since 2.6
        * @param aText The text
        */
        IMPORT_C void SetTextL( const TDesC* aText );
        /**
        * Increments the progress bar by given value. Draws the bar to the new value.
        * @since 2.6
        * @param aIncrement The increment value
        */
        IMPORT_C void IncrementProgressBarAndDraw( const TInt aIncrement );

        /**
        * Sets the progress bar to given value. Draws the bar to the new value.
        * @since 2.8
        * @param aValue The new value
        */
        IMPORT_C void SetProgressBarAndDraw( const TInt aValue );

        /**
        * Draw the dialog.
        * @since 2.6
        */
        IMPORT_C void  Draw( const TRect& /*aRect*/ ) const;
        /**
        * Finds the control of the given type on the dialog.
        * @since 2.6
        * @param aIncrement The control type to find.
        * @return Control of the given type. If it was not found, return 0.
        */
        IMPORT_C CEikCaptionedControl* GetControlByControlType( TInt aControlType ) const;
        /**
        * Return the progress info control.
        * @since 2.6
        * @return The progress info control. If there is no progress info
        * control on the form, return NULL.
        */
        IMPORT_C CEikProgressInfo* ProgressInfo();
        /**
        * Change the image on the form.
        * @since 2.6
        * @param aImage The new image.
        */
        IMPORT_C void SetImageL( const CEikImage* aImage);
        /**
        * Set the callback object whose DialogDismissedL method is to be
        * called after this popup form dismisses.
        * @since 2.6
        * @param aCallback The callback object.
        */
        IMPORT_C void SetCallback( MPopupFormProgressCallback* aCallback );
        /**
        * This must be called when the dialog must be dismissed.
        * It stops the timer and deletes the dialog.
        * @since 2.6
        */
        IMPORT_C void ProcessFinishedL();

    public: // Functions from base classes
        /**
        * From CAknDialog   Prepares the dialog, constructing it
        *                   from the specified resource.
        * @since 2.6
        * @param aResourceID The resource ID of the dialog.
        */
        IMPORT_C void PrepareLC( TInt aResourceID );
        /**
        * From CAknDialog   Runs the dialog and returns the ID of
        *                   the button used to dismiss it.
        * @since 2.6
        * @return The ID of the button used to dismiss the dialog.
        */
        IMPORT_C virtual TInt RunLD();
        /**
        * From CEikdialog   EIKON provides an implementation of this function,
        *                   which positions the dialog in the centre of the screen.
        *                   However, it can be overridden by derived classes.
        * @param aSize      The size for the dialog.
        */
        IMPORT_C void SetSizeAndPosition( const TSize& aSize );
        /**
        * From CCoeControl  Sets control as ready to be drawn.
        * @since 2.6
        */
        IMPORT_C void ActivateL();
        /**
        * From CEikDialog   Called by the dialog framework, returns true if
        *                   the dialog can exit, false otherwise.
        * @since 2.6
        */
        IMPORT_C TBool OkToExitL( TInt aButtonId );

        /**
        * Handles a change to the control's resources of type aType
        * which are shared across the environment, e.g. colors or fonts.
        *
        * @since ER5U
        */
        IMPORT_C void HandleResourceChange( TInt aType );

       /**
        * @internal
        */
        void RedrawHeading();


    protected: // New functions
        /**
        * Play a tone.
        * The tone must have been previously specified.
        * The sound ID is set depending on the tone type.
        * @since 2.6
        */
        IMPORT_C void PlayTone();
        /**
        * Delete the dialog.
        * Called when the timer completes.
        * A reinterpret_cast to CAknPopupForm* is performed on aThis.
        * @since 2.6
        * @param aThis Pointer to the dialog
        */
        IMPORT_C static TInt StaticDeleteL( TAny* aThis );
        /**
        * Return a pointer to CAknKeySoundSystem.
        * Call iEikonEnv->AppUi()->KeySounds() and return the pointer returned by it.
        * If there is not app UI return NULL.
        * @since 2.6
        * @return The sound system or NULL
        */
        IMPORT_C CAknKeySoundSystem* SoundSystem() const;
        /**
        * Do layout and draw.
        *
        * Needed when adding/removing/changing control components dynamically.
        * This is needed because the size of the dialog might change
        * (e.g. because of bigger text displayed in more lines, etc.)
        * Set methods call LayoutAndDraw if there is a chance that
        * might affect the dialog layout (e.g. text becomes bigger and hence
        * requires an extra line).
        * @since 2.6
        */
        IMPORT_C void LayoutAndDraw();

    private: // New functions
        /**
        * Do layout for the label
        * @since 2.6
        */
        void LabelLayout();
        /**
        * Do layout for the editor
        * @since 2.6
        */
        void EditorLayout();
        /**
        * Do layout for the image
        * @since 2.6
        */
        void ImageLayout();
        /**
        * Do layout for the progress bar
        * @since 2.6
        */
        void ProgressBarLayout();
        /**
        * Do layout for the spacer
        * @since 2.6
        */
        void SpacerLayout();
        /**
        * Do layout for the regular animation,
        * which is shown in the place of an image
        * @since 2.6
        */
        void AnimationLayoutL();
        /**
        * Calculate number of the screens needed to show the text.
        * Store the number to iNumberOfScreens member.
        * @since 2.6
        */
        void CalculateNumberOfScreens();
        /**
        * Update the scroll indicator to reflect iNumberOfScreens
        * @since 2.6
        */
        void UpdateScrollIndicatorL();
        /**
        * Indicate that there is user activity.
        * @since 2.6
        */
        void ReportUserActivity() const;
        /**
        * Starts the animation, if there is one.
        * @since 2.6
        */
        void StartAnimationL();
        /**
        * Determines the type of the animation.
        * @since 2.6
        */
        TAnimationType DetermineAnimationType( const CAknBitmapAnimation* aAnimation );
        /**
        * @internal
        */
        CAknPopupFormExtension* Extension();

    protected: // Functions from base classes

        /**
        * From CEikDialog Performs post-layout dialog initialisation.
        * Timer is started if needed.
        * @since 2.6
        */
        IMPORT_C void PostLayoutDynInitL();
        /**
        * From CoeControl
        * @since 2.6
        */
        IMPORT_C void SizeChanged();
        /**
        * From CoeControl
        * @since 2.6
        */
        IMPORT_C TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent,
                                     TEventCode /*aModifiers*/);

        /**
        * From CoeControl
        * @since 3.2
        */
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

    private: // Functions from base classes
        /**
        * From CoeControl
        * @since 2.6
        */
        IMPORT_C TInt CountComponentControls() const;
        /**
        * From CoeControl
        * @since 2.6
        */
        IMPORT_C CCoeControl* ComponentControl( TInt aIndex ) const;

    public:
        /**
        * Insert a control from resource to the popup form
        * @since 2.6
        * @param aIndex      The index where control is inserted to.
        * @param aResourceId The id of the resource the control is read from.
        */
        IMPORT_C void InsertControlL( const TInt aIndex, const TInt aResourceId );
        /**
        * Delete a control from the popup form
        * @since 2.6
        * @param aControlType The control type to delete.
        */
        IMPORT_C void DeleteControl( const TInt aControlType );
        /**
        * Tells if the text in the editor is scrollable
        * @since 2.6
        * @return ETrue if the text is scrollable, EFalse otherwise.
        */
        IMPORT_C TBool TextIsScrollable();
        /**
        * Return the bitflags
        * @since 2.6
        * @return TBitFlags The bitflags
        */
        IMPORT_C TBitFlags& Flags();
        /**
        * Finds the control of the given popup form control type on the dialog.
        * @since 2.6
        * @param aControl The control type to find.
        * @return Control of the given type. If it was not found, return 0.
        */
        IMPORT_C CEikCaptionedControl* GetControlByControlTypeL( TPopupFormControlType aControl ) const;
        /**
        * Delete a control from the popup form
        * @since 2.6
        * @param aControl The popup form control type to delete.
        */
        IMPORT_C void DeleteControl( const TPopupFormControlType aControl );
        /**
        * Tells popup form in which resource index wait animation is
        * @since 2.8
        * @param aIndex The index in which wait animation is.
        */
        IMPORT_C void SetWaitAnimationResourceIndex( const TInt aIndex );
        /**
        * Insert a control to the popup form and tell if it is
        * wait animation.
        * @since 2.8
        * @param aControl The popup form control type to insert.
        */
        IMPORT_C void InsertControlL( const TInt aIndex, const TInt aResourceId, const TBool aIsWaitAnimation );


    private:
        /**
        * Adds/removes flags.
        * Called after the content of the popupform has changed.
        * @since 2.6
        * @param aControlType  The control type the change affects.
        * @param aInsert       ETrue if inserting the control, EFalse if deleting.
        */
        void UpdateFlags( const TPopupFormControlType aControlType, const TBool aInsert );
        /**
        * Clears an area specified by aRect.
        * @since 2.6
        * @param aRect  The area to clear.
        */
        void ClearArea( const TRect& aRect );
        /**
        * Starts the timeout timer. Called when the popupform is executed and
        * when the timeout is set during execution.
        * @since 2.6
        */
        void StartTimeoutTimerL();
        /**
        * Returns the control type of given TPopupFormControl
        * @since 2.6
        * @param Popup form control
        * @return Control type
        */
        TInt ControlType(const TPopupFormControlType aControl) const;
        /**
        * Returns the popup form control type of given captioned control
        * @since 2.6
        * @param Control, whose type is to be checked
        * @return Popup form control type
        */
        TPopupFormControlType PopupFormControlType ( CEikCaptionedControl* aControl );
        /**
        * Actually deletes the control from popup form. DeleteControl functions
        * call this function.
        * @since 2.6
        * @param Control to delete.
        */
        void DoDeleteControlL( CEikCaptionedControl* aControl );
        /**
        * Do layout for the wait animation.
        * @since 2.8
        */
        void WaitAnimationLayoutL();
        /**
        * Determines if we are using a short or long progress bar/
        * wait animation.
        * @since 2.8
        */
        TInt DetermineBarLayoutVariant() const;
        /**
        * Sets sizes for animation frames.
        * @since 2.8
        */
        void SetAnimationSize( TPopupFormControlType aType, CEikCaptionedControl* aAnimation );

        /**
        * Determines the right layout for editors
        * @since 3.0
        */
        TAknMultiLineTextLayout EditorTextLineLayout();

        /**
        * Calculates the number of visible lines in the editor
        * @since 3.0
        */
        TInt NumberOfVisibleLines() const;

        /**
        * Determines the right rect for the window
        * @since 3.1
        */
        TRect PopupWindowRect() const;

    private: // member variables

        friend class CAknPopupFormExtension;

        CCoeBrushAndPenContext*             iBrushAndPenContext;
        CEikScrollBarFrame*                 iSBFrame;
        TInt                                iTimeoutInSeconds;
        TTone                               iTone;
        TPopupFormType                      iType;
        CPeriodic*                          iTimer;
        TBitFlags                           iFlags;

        // array for storing the controls (not used at the moment)
        CArrayPtrFlat<CEikCaptionedControl>*   iItemArray;

        TInt                                iNoOfDialogLines;
        TInt                                iNoOfEditorLines;
        TInt                                iNoOfScreens;
        TInt                                iCurrentLine;
        TSize                               iFormSize; //not used
        MPopupFormProgressCallback*         iCallback;

        CAknPopupFormExtension* iExtension;

};

#endif // __AKNPOPUPFORM__

// End of File
