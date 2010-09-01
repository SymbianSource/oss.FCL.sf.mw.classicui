/*
* Copyright (c) 2001-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Base class for legacy Uikon buttons
*
*/


#if !defined(__EIKBUTB_H__)
#define __EIKBUTB_H__

#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>
#endif

#if !defined(__UIKON_HRH__)
#include <uikon.hrh>
#endif

#include <eikon.hrh>

#include <lafpublc.h>

class TEikButtonCoordinator;

/**
* Possible button behaviours 
*/
enum TButtonBehavior
	{
	EEikButtonStaysClear=EEikButStaysClear,
	EEikButtonStaysSet=EEikButStaysSet,
	EEikButtonLatches=EEikButLatches,
	EEikButtonReportsOnPointerDown=EEikButReportOnPointerDown
	};
	
/**
 *  Base class for button controls
 *
 *  This class defines behavior available to all button classes.
 *
 *  @lib eikcoctl
 *  @since S60 1.0
 */
class CEikButtonBase : public CEikBorderedControl
	{
public:
    /**
     * C++ constructor
     */
    IMPORT_C CEikButtonBase();
    
    /**
     * C++ destructor
     */     
    IMPORT_C ~CEikButtonBase();
    
public:

    /**
     * States that the button can be in.
     */     
    enum TState
        {
        EClear		  	=0,
        ESet			=1,
        EIndeterminate  =2
        };
		
public: // new functions
    /**
     * Access the state
     *
     * @return The state of the button
     */     
    IMPORT_C TState State() const;
    
    /**
     * Set the state of the button.
     *
     * @param aState The state the button is to be set to.
     */     
    IMPORT_C void SetState(TState aState);
    
    /**
     * Cause the button to animate. The appearance changes to the "pressed in" state. Subsequent 
     *  behaviour depends upon the SetBehavior setting
     */     
    IMPORT_C virtual void Animate();
    
    /**
     * Sets the coordinator for the button.
     *
     * @param aButCoord The coordinator to set for these button
     */     
    IMPORT_C void SetCoordinator(TEikButtonCoordinator* aButCoord);
    
    /**
     * Sets the button’s behaviour. A button can be made to stay set or stay clear. It can also be made a latching button.
     *
     * @param aBehavior Behaviour to use
     */     
    IMPORT_C void SetBehavior(TButtonBehavior aBehavior);
    
    /**
     * Sets the control to ignore the next pointer up event
     */     
    IMPORT_C void SetIgnoreNextPointerUp();
    
protected:
    /**
    * The draw state of the button.
    */
    enum TDrawState
        {
        EDrawClear					=SLafButtonBase::EDrawClear,
        EDrawSet					=SLafButtonBase::EDrawSet,
        EDrawIndeterminate			=SLafButtonBase::EDrawIndeterminate,
        EDrawClearPressed			=SLafButtonBase::EDrawClearPressed,
        EDrawSetPressed				=SLafButtonBase::EDrawSetPressed,
        EDrawIndeterminatePressed	=SLafButtonBase::EDrawIndeterminatePressed
        };

protected: // new functions
    /**
     * Set whether the control should report on pointer down
     */     
    IMPORT_C void SetReportOnPointerDown();
    
    /**
     *  Access the draw state defined in SLafButtonBase
     *
     * @return The draw state of the control
     */     
    IMPORT_C TDrawState DrawState() const;
    
    /**
     * Returns whether the button is currently pressed.
     *
     * @return EFalse if the button is not pressed
     */     
    IMPORT_C TBool IsPressed() const;
    
    /**
     * Sets the button to be tri-state
     */     
    IMPORT_C void SetAllowTristate();
    
    /**
     * Transfers the draw state to the referenced button
     *
     * @param aTargetButton button to transfer the 
     */     
    IMPORT_C void CopyDrawStateTo(CEikButtonBase* aTargetButton) const;
    
public:	// from CCoeControl
    /**
     *  From CCoeControl
     * 
     * Obtain the color use list for this control
     *
     * @param aColorUseList Output; upon non-leaving return, constains the color use list
     */     
    IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
    
    /**
     *  From CCoeControl
     * 
     *  Perform necessary operations when resource changes.  This includes layout switches, or other events
     *  that affect appearance.
     *
     * @param aType Type of resouce changed
     */     
    IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
    
    /**
     *  From CCoeControl
     * 
     *  Serialize the control's state. For testing
     *
     * @param aWriteStream  Stream to write to.
     */     
    IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
    
private: // from CCoeControl
    IMPORT_C void Reserved_2();

private: // new functions
    /**
    * Called but button framework when the state of the control has changed
    */
    IMPORT_C virtual void StateChanged();
    IMPORT_C virtual void Reserved_3();

public:
    /**
     *  From CCoeControl
     * 
     * A pointer event is being routed to this control for handling
     *
     * @param aPointerEvent Wserv pointer event
     */     
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    
    /**
     *  From CCoeControl
     * 
     * A key event is being being given to the control for handling
     *
     * @param aKeyEvent     Key event code
     * @param aType            Type of event (i.e.. EEventKey, EEventKeyUp, EEventKeyDown)
     * @return EKeyWasConsumed or EKeyWasNotConsumed
     */     
    IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

    /**
     *  From CCoeControl
     * 
     * Interface used by the FEP or others to determine what type of input the control requires.
     *
     * @return A value indicating what input is required.
     */     
    IMPORT_C TCoeInputCapabilities InputCapabilities() const; 
    
private:
    /**
    * From CAknControl
    * 
    * Interface for extending virtual functionality of CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
    
private: // internal use only
    TBool ClickCompleted();

private:
    enum { EIgnoreNextPointerUp=0x1000 };

protected:
    /**
    * Flags for the button class hierarchy
    */ 
    TInt iButFlags;
    
private:
    /**
    * Button co-ordinator associated with this button
    */ 
    TEikButtonCoordinator* iButCoord;
    
    TInt iSpare[2];
    };

/**
 *  Button coordinator class
 * 
 * This class performs simple coordination functions on a set of buttons. It ensures that only
 * one button of those sharing a coordinator is set at once.
 *
 *  @lib eikcoctl
 *  @since S60 1.0
 */
class TEikButtonCoordinator
	{
public:
    /**
    * Constructor
    */
    IMPORT_C TEikButtonCoordinator();
    
    /**
    * Set the current chosen button to the passed-in object. 
    * Any previously selected button is set to the Clear state and re-drawn.
    *
    * @param aChosenButton Button to set as the new chosen button.
    */
    IMPORT_C void SetChosenButton(CEikButtonBase* aChosenButton);		

private:
    /**
    * Records the currently chosen button associated with this co-ordinator object.
    */
    CEikButtonBase* iChosenButton;
    };		 

#endif // __EIKBUTB_H__
