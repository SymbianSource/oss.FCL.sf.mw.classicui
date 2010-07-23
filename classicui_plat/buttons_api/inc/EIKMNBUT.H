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
* Description:  Uikon legacy button that launches a menu when activated
*
*/


#if !defined(__EIKMNBUT_H__)
#define __EIKMNBUT_H__

#if !defined(__EIKMOBS_H__)
#include <eikmobs.h>
#endif										 

#if !defined(__EIKCMBUT_H__)
#include <eikcmbut.h>
#endif

class CEikMenuPane;

/**
 *  This class implements a command button that, when pressed, raises a Menu pane.
 *
 *  This class does NOT implement S60 look-and-feel and is not skinned.
 *
 *  @lib eikcoctl.dll
 *  @since S60 1.0
 */
class CEikMenuButton : public CEikCommandButton, private MEikMenuObserver
{
public:
    /**
    * C++ constructor
    */
    IMPORT_C CEikMenuButton();
    
    /**
    * destructor
    */
    IMPORT_C ~CEikMenuButton();

    /**
    * 2nd phase constructor using a MNBUT resource struct
    *
    * @param aReader    A constructed resource reader.
    */
    IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
    
    /**
    * Launch the related menu pane
    * 
    * @param aObserver Mandatory supplied menu observer pointer.
    */
    IMPORT_C void LaunchPopupMenuL(MEikMenuObserver* aObserver);
    
    /**
    * Set the menu pane id to be launched when the control is activated.
    * 
    * @param aMenuPaneId  Resource ID of the menu pane to be launched
    */
    IMPORT_C void SetMenuPaneId(TInt aMenuPaneId);
    
protected:

    /**
    * From CCoeControl
    *
    * Serialize the state of the control to the given stream
    *
    * @param aWriteStream   Stream to write to
    */
    IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;

public: // from CEikButtonBase

    /**
    * Triggers the change of appearance of the button that is associated with the button being pressed
    */
    IMPORT_C void Animate();

public: // From CCoeControl
    
    /**
    * From CCoeControl
    *
    * Framework method called when a pointer event is found to be within this control's boundaries. 
    * The default implementation causes the associated menu to be presented to the screen.
    *
    * @param aPointerEvent  Pointer event to process
    */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

private: 
 
    /**
    * From MEikCommandObserver
    *
    * Framework method called to processs a command ID
    *
    * @param aCommandId ID of the command to respond to.
    */
    IMPORT_C void ProcessCommandL(TInt aCommandId);
    
    /**
    * From MEikMenuObserver
    *
    * Called by the Uikon framework to handle the emphasising or de-emphasising of 
    * a menu window. 
    * 
    * CEikMenuBar objects call this on their observer to emphasise 
    * themselves when they are displayed, and de-emphasise themselves when they 
    * stop displaying.
    * 
    * @param aMenuControl The menu control
    * @param aEmphasis ETrue to emphasize the menu, EFalse otherwise
    */
    IMPORT_C void SetEmphasis(CCoeControl* aMenuControl,TBool aEmphasis);
    
private:
    void ClosePopupMenu();
    void DoLaunchPopupMenuL();
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
    
private:
    /**
    *  The object to receive the menu events
    *  Not Owned
    */
    MEikMenuObserver* iMenuObserver;
    
    /**
    * Holds a menu pane object to be popped up
    * Owned
    */
    CEikMenuPane* iMenuPopup;
    
    /**
    * Resource ID of the menu pane
    */
    TInt iMenuPaneId;
    
    TInt iSpare;
    };

#endif
