/*
* Copyright (c) 2000-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Uikon legacy labelled button control
*
*/

#if !defined (__EIKLBBUT_H__)
#define __EIKLBBUT_H__

#if !defined(__COECNTRL_H__)
#include <coecntrl.h>
#endif

#if !defined(__COECOBS_H__)
#include <coecobs.h>
#endif

#include <AknControl.h>

class CEikCommandButtonBase;
class CEikLabel;

/**
 *  This class combines a command button with a label and a hotkey binding.  
 *
 *  The label is used to display a text describing a hotkey.  The hotkey is set via API or resource, as the ASCII code 
 *  of the key that is combined with CTRL to form the hotkey combination. E.g. setting the hotkey to decimal 65 
 *  will bind CTRL+'A' as the hotkey. "CTRL+A" will be displayed in the label.
 *
 *  This class does not implement S60 look-and-feel and is not skinned.
 *
 *  @lib eikcoctl
 *  @since S60 1.0
 */
 class CEikLabeledButton : public CAknControl, private MCoeControlObserver
    {
public:
    /**
    * Options for display of the hotkey shortcut
    */
    enum TFlags
        {
        EShowHotKey = 0x01,   // Hot keys are displayed
        EPlainHotKey = 0x02    // Hot keys are displayed plain
        };
public:

    /**
    * Constructor
    */
    IMPORT_C CEikLabeledButton();

    /**
    * C++ Destructor
    */
    IMPORT_C ~CEikLabeledButton();

    /**
    * 2nd Stage constructor
    *
    * @param aButton    Sets the button to use as the active part of the CEikLabeledButton
    */
    IMPORT_C void ConstructL(CEikCommandButtonBase* aButton,TInt aHotKeyCode,TInt aFlags);

    /**
    * Access to the button component of the labeled button
    *
    * @return   Pointer to the button component. No ownership is transferred.
    */
    IMPORT_C CEikCommandButtonBase* Button() const;

    /**
    * Access to the label component of the labeled button
    *
    * @return   Pointer to the CEikLabel component. No ownership is transferred.
    */
    IMPORT_C CEikLabel* Label() const;

    /**
    * Access the hotkey code
    *
    * @return   The hot key code
    */
    IMPORT_C TInt HotKeyCode() const;

    /**
    * Access to hot key setting
    *
    * @return   EFase iff ShowsHotKeys is not set
    */
    IMPORT_C TBool ShowsHotKey() const;

    /**
    * Access the key display mode
    *
    * @return EFalse if the key mode is not set to Plain
    */
    IMPORT_C TBool PlainHotKey() const;

    /**
    * Cause the button to animate and to generate its command ID
    */
    IMPORT_C void Animate();

    /**
    * Change the hot key binding
    *
    * @param aKeyCode   Key to use (along with pressing CTRL) as the hotkey
    */
    IMPORT_C void UpdateHotKey(TInt aKeyCode,TFlags aFlags);

// from CCoeControl    
public:
    /**
    * From CCoeControl
    *
    * CONE framework is requesting that the passed-in key be handled.
    *
    *  @param aKeyEvent     Wserv event type
    *  @param aKeyCode      Key code
    */ 
    IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
    
    /**
    * From CCoeControl
    *
    * Construct the object from resource
    * 
    * @param aReader  Fully constructed resource reader
    */
    IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
    
    /**
    * From CCoeControl
    *
    * Reports to the caller the minimum size that the control can be, given its contents.
    *
    *  @return  The minimum size
    */    
    IMPORT_C TSize MinimumSize();
    
    /**
    * From CCoeControl
    *
    * Sets the control whose window is to be used as a container for this control
    *
    *  @param aContainer control
    */
    IMPORT_C void SetContainerWindowL(const CCoeControl& aContainer);
    
    /**
    * From CCoeControl
    *
    * Sets the button to be inactive. The button is drawn with a dimmed effect. 
    *
    *  @param aDimmed   If not EFalse, set the state to dimmed. Otherwise set to non-dimmed
    */
    IMPORT_C void SetDimmed(TBool aDimmed);
    
    /**
    * From CCoeControl
    *
    * Obtain the list of colors to be used by this control
    *
    *  @param aColorUseList
    */
    IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u

    /**
    * From CCoeControl
    *
    * This is called when resource or layout or other display-affecting setting has changed.
    * Change the internals of the control so that it is ready for a subsequent SizeChanged call.
    *
    *  @param aType  Type of resource or setting that has changed
    */    
    IMPORT_C void HandleResourceChange(TInt aType);			// not available before Release 005u
    
    /**
    * From CCoeControl
    *
    * Report the input capabilities of the control
    * 
    * @return   A copy of the object holding the capabilities of this control
    */
    IMPORT_C TCoeInputCapabilities InputCapabilities() const; // not available before Release 006

    /**
    * From CCoeControl
    *
    * Handle a pointer event coming from the CONE framework
    * 
    * @param aPointerEvent  Event to handle
    */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

protected: 
    /**
    * From CCoeControl
    *
    * Serialize the state of the control
    *
    * @param aWriteStream   Output stream for the serialization
    */
    IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
    
private:
    /**
    * From CCoeControl
    *
    * Returns the number of component controls
    *
    *  @return  Number of component controls
    */
    TInt CountComponentControls() const;
    
    /**
    * From CCoeControl
    *
    * Return a pointer to the component control at the give index.
    *
    *  @return  Pointer to the conponent control. No ownership is transferred
    */
    CCoeControl* ComponentControl(TInt aIndex) const;
    
    void SizeChanged();

    void Reserved_2();
    
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private: 
    /**
    * from MCoeControlObserver
    */
    void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
private:
    void CreateLabelL();
    void UpdateHotKeyL();
private:
    /**
    * Contained command button object. 
    * Owned
    */ 
    CEikCommandButtonBase* iButton;
    
    /** 
    * Contained label to implement the text
    * Owned
    */
    CEikLabel* iLabel; // Owned
    
    TInt iHotKeyCode;
    TInt iLButFlags;

    TInt iSpare[2];
    };

#endif
