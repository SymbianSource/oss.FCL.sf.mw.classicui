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
*
*/



#ifndef     __AKN_LIST_QUERY_CONTROL_H
#define     __AKN_LIST_QUERY_CONTROL_H

#include <AknControl.h>

#include <aknPopupHeadingPane.h>
#include <aknmessagequerycontrol.h>

class CEikFormattedCellListBox;
struct TAknPopupWindowLayoutDef;

/**
 * List query control class.
 */
class CAknListQueryControl : public CAknControl
    {
    public:
        /**
        * Constructor
        */
        IMPORT_C CAknListQueryControl();
    
        /**
        * Constructs control from resources
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aRes);

        /**
        * Destructor
        */
        IMPORT_C virtual ~CAknListQueryControl();

        /**
        * From CCoeControl
        *
        * @return   Minimum size of the control
        */
        IMPORT_C TSize MinimumSize();

        /**
        * From CCoeControl
        *   Returns number of controls inside the query control
        * @return   Number of component controls
        */
        IMPORT_C TInt CountComponentControls() const;

        /**
        * From CCoeControl
        *   Returns a control determined by control id
        * @param    anIndex     Index of a control to be returned
        * @return   CCoeControl Pointer to control
        */
        IMPORT_C CCoeControl* ComponentControl(TInt anIndex) const;

        /**
        * From CCoeControl
        *   Handles key events - Gets called by CONE
        * @param    aKeyEvent   The key event
        * @param    aType       The type of the event
        * @return   Indicates whether or not the key event was
        *               used by this control
        */
        IMPORT_C TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType);

        /**
        * From CCoeControl
        *   Draws the control
        * @param    aRect   The region of the control to be redrawn
        */
        IMPORT_C void Draw(const TRect& aRect) const;

        /**
        * Sets layout for list query control
        * @param aLayout    Layout to be set
        */
        IMPORT_C void SetLayout(TAknPopupWindowLayoutDef* aLayout);

        IMPORT_C void FocusChanged(TDrawNow aDrawNow);

        /**
        * Returns pointer to listbox
        * @return   Pointer to CEikFormattedCellListBox
		*/
        inline CEikFormattedCellListBox* Listbox() const;

        /**
        * Returns pointer to heading
        * @return   Pointer to CAknPopupHeadingPane
		*/
        inline CAknPopupHeadingPane* Heading() const;

        /**
        * Return type of the list
        * @return Type of the list
        */
        inline TInt Listtype() const;

        /**
        * From CCoeControl.     
        * Handles pointer events
        */
    	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    	
    	/**
        * Get pointer to messageControl if such exists.
        * @since 3.0
        */
        CAknMessageQueryControl* MessageBox() const;

    private:
        /**
        * From CAknControl
        */
        IMPORT_C void* ExtensionInterface( TUid aInterface );

    private:
        CEikFormattedCellListBox* iListBox;
        CAknPopupHeadingPane*     iHeading;
        TInt                      iListType;
        TAknPopupWindowLayoutDef* iLayout;
        CAknMessageQueryControl*  iMessageBox;        

        TInt iSpare[1];

	public:

		/**
		 * Deprecated - do not use
		 */
        inline CEikFormattedCellListBox* listbox() const;
    };

inline CEikFormattedCellListBox *CAknListQueryControl::Listbox() const 
	{ 
	return iListBox; 
	}

inline CAknPopupHeadingPane *CAknListQueryControl::Heading() const 
    {
    if ( iHeading && iHeading->Prompt() )
        return iHeading;
    return 0;
    }

inline TInt CAknListQueryControl::Listtype() const 
	{ 
	return iListType; 
	}

/**
 * Deprecated methods
 */
inline CEikFormattedCellListBox* CAknListQueryControl::listbox() const 
	{ 
	return Listbox();
	}

#endif
