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
*      This file defines the CAknColourSelectionGrid class
*
*/



#ifndef __AKNCOLOURSELECTIONGRID_H
#define __AKNCOLOURSELECTIONGRID_H

//  INCLUDES
#include <e32base.h>
#include <AknDialog.h>
#include <eiklbo.h>
#include <coecobs.h>

// FORWARD DECLARATIONS
class CColorGrid;
class CNoneField;
class CAknGrid;
class CAknColourSelectionGridExtension;

// CLASS DECLARATION

/**
* Colour selection grid
*
* This class can be used when application offers to user
* possibility to choose colour. There is also possibility to select
* nothing.
*
* use example:
*
* TBool noneExist = ETrue;
* TBool noneChosen = EFalse;
* TRgb  colour = KRgbDarkGray;
* CArrayFixFlat<TRgb>* colours = new(ELeave) CArrayFixFlat<TRgb>(6);
*
* colours->AppendL(KRgbBlack);
* colours->AppendL(KRgbDarkGray);
*
*   CAknColourSelectionGrid *d = CAknColourSelectionGrid::NewL(
*                                                 colours,
*                                                 noneExist,
*                                                 noneChosen,
*                                                 colour);
*
*   d->ExecuteLD();
*
*
*  @lib avkon
*  @since 2.0
*/

NONSHARABLE_CLASS(CAknColourSelectionGrid) : public CAknDialog, public MEikListBoxObserver
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        *
        * NewL() Creates dialog
        *
        * @since 2.0
        *
        * @param aColours array of colors for grid
        *
        * @param aNoneExist boolean flag does none exist in dialog
        *
        * @param aNoneChosen Dialog sets boolean value is none chosen
        * If value is EFalse in start, some colour will be active in start
        *
        * @param aColourChosen Dialog sets the value of color chosen
        * If starting value aNoneChosen is EFalse, starting value of
        * aColours tells witch colour is active when grid starts
        *
        */
        IMPORT_C static CAknColourSelectionGrid* NewL(
                            CArrayFixFlat<TRgb> *aColours,
                            TBool aNoneExist,
                            TBool& aNoneChosen,
                            TRgb& aColourChosen);

        /**
        * ExecuteLD() runs dialog, waits user to make his choise
        * and destroys dialog
        *
        * @since 2.0
        */
        IMPORT_C TBool ExecuteLD();


    private: // Constructor
        /**
        * C++ default constructor.
        */
        CAknColourSelectionGrid();


    public: // Destructor
        /**
        * Destructor
        */
        IMPORT_C ~CAknColourSelectionGrid();



    private: // New functions

        /**
        * Grid() returns control to grid
        *
        * @since 2.0
        * @return Control to grid
        */
        CAknGrid *Grid() const;


    private: // Functions from base classes
        /**
        * From CAknDialog.
        *
        * Handles key events
        *
        * @since 2.0
        * @param aKeyEvent
        * @param aType
        * @return was the key event handled
        */
        TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType) ;

        /**
        * From CAknDialog.
        *
        * If ok is pressed, writes values for iColorChosen and iNoneChosen
        *
        * @since 2.0
        * @param aKeycode
        * @return allways ETrue
        */
        TBool OkToExitL(TInt aKeycode);

        /**
        * From CEikDialog
        * @since 2.0
        */
        void  PreLayoutDynInitL();
        /**
        * From CEikDialog
        * @since 2.0
        */
        void  PostLayoutDynInitL();
        /**
        * From CEikDialog
        * @since 2.0
        * @param aControlType
        * @return created control
        */
        SEikControlInfo CreateCustomControlL(TInt aControlType);

        /**
        * From CEikDialog
        * @since 2.0
        * @param aSize not in use
        */
        virtual void SetSizeAndPosition(const TSize& aSize);

        /**
        * From CCoeControl
        * @since 2.0
        */
        virtual void ActivateL();


        /**
        * From MEikListBoxObserver
        * Handles list box events
        * @param aListBox pointer to observed listbox
        * @param aEventType Event to be handled
        */
        void HandleListBoxEventL(CEikListBox* aListBox, TListBoxEvent aEventType);

    public:
        /**
        * From MCoeControlObserver
        * Handles control events from nonebutton.
        * @param aControl Pointer to observed control
        * @param aEventType type of event to be handled
        */
        void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);

        /**
        * From MDialogPageObserver
        * Handles dialogpage events
        * @param aEventID event to be handled
        */
        void HandleDialogPageEventL(TInt aEventID);

        /**
        * From CoeControl
        * @since 3.2
        * Handles pointer events
        */
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

    private: // Data
        CColorGrid* iGrid;
        CNoneField* iNoneBox;
        TInt iIndex;
        CFbsBitmap* iBitmap;
        TBool iNoneExist;
        TBool* iNoneChosen;
        TRgb* iColourChosen;
        CArrayFixFlat<TRgb>* iColours;
        TInt iWsBufferRequestID;
        CAknColourSelectionGridExtension *iExtension;
    };

#endif  // __AKNCOLOURSELECTIONGRID_H
