/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test aknpopupform.h
*
*/


#ifndef C_TESTDOMPOPUPFORMEXT_H
#define C_TESTDOMPOPUPFORMEXT_H

class CAknPopupForm;
class MPopupFormProgressCallback;

class CAknPopupFormExt : public CAknPopupForm,
                         public MPopupFormProgressCallback
    {

public: // derived from CAknPopupForm class

    // 2nd phase constructor.
    void DoConstructL();

    /**
    * Play a tone.
    * The tone must have been previously specified.
    * The sound ID is set depending on the tone type.
    * @since 2.6
    */
    void DoPlayTone();
    /**
    * Delete the dialog.
    * Called when the timer completes.
    * A reinterpret_cast to CAknPopupForm* is performed on aThis.
    * @since 2.6
    * @param aThis Pointer to the dialog
    */
    static TInt DoStaticDeleteL( TAny* aThis );
    /**
    * Return a pointer to CAknKeySoundSystem.
    * Call iEikonEnv->AppUi()->KeySounds() and return the pointer returned by it.
    * If there is not app UI return NULL.
    * @since 2.6
    * @return The sound system or NULL
    */
    CAknKeySoundSystem* DoSoundSystem() const;
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
    void DoLayoutAndDraw();

    /**
    * From CEikDialog Performs post-layout dialog initialisation.
    * Timer is started if needed.
    * @since 2.6
    */

    void DoPostLayoutDynInitL();
    /**
    * From CoeControl
    * @since 2.6
    */

    void DoSizeChanged();
    /**
    * From CoeControl
    * @since 2.6
    */
    TKeyResponse DoOfferKeyEventL( const TKeyEvent& aKeyEvent,
                                 TEventCode /*aModifiers*/);

    /**
    * From CoeControl
    * @since 3.2
    */
    void DoHandlePointerEventL(const TPointerEvent& aPointerEvent);

    /**
    * From CoeControl
    * @since 2.6
    */
    void DoActivateGc();

    /**
    * From CoeControl
    * @since 2.6
    */
    void DoDeactivateGc();

public: // derived from MPopupFormProgressCallback class

    /**
    * Callback method
    *   Gets called when a popupform with a
    *   progress bar is dismissed.
    */
    virtual void DialogDismissedL( TInt aButtonId );

    };


#endif // C_TESTDOMPOPUPFORMEXT_H
