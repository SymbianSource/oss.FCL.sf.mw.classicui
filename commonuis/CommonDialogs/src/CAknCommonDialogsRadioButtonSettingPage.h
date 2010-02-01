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
* Description:  Setting page for non-multidrive memory selection setting page.
*
*/


#ifndef CAKNCOMMONDIALOGSRADIOBUTTONSETTINGPAGE_H
#define CAKNCOMMONDIALOGSRADIOBUTTONSETTINGPAGE_H

// INCLUDES
#include <aknradiobuttonsettingpage.h>
#include "maknmemoryselectiondriveobserver.h"

// FORWARD DECLARATIONS
class MAknCommonDialogsEventObserver;
class CEikButtonGroupContainer;
class CAknMemorySelectionModel;
//  CLASS DEFINITION
/**
*  A class derived from CAknRadioButtonSettingPage in order to catch events
*  and report them to the event handler.
*
*  @lib CommonDialogs.lib
*  @since 1.2
*/
NONSHARABLE_CLASS(CAknCommonDialogsRadioButtonSettingPage) : public CAknRadioButtonSettingPage,
                                                             public MAknMemorySelectionDriveObserver
    {
    public:     // Constructors and destructors

        /**
        * Constructor.
        * @param aResourceId A parameter for CAknRadioButtonSettingPage.
        * @param aCurrentSelectionIndex A reference to selected item.
        * @param aObserver An observer to which events are reported.
        * @param aModel for UpdateAndRedrawItem.
        */
        CAknCommonDialogsRadioButtonSettingPage(
            TInt aResourceId,
            TInt& aCurrentSelectionItem,
            const MDesCArray* aItemArray,
            MAknCommonDialogsEventObserver& aObserver,
            CAknMemorySelectionModel* aModel );

        ~CAknCommonDialogsRadioButtonSettingPage();

    public:     // Functions from base classes

        /**
        * From CAknSettingPage
        * A method for getting button group container pointer.
        */
        CEikButtonGroupContainer* Cba() const;

        /**
        * From MAknMemoryCardInsertObserver
        * Update setting page with new memory names
        * @param aItemArray Memory names from memory selection model
        */
        void NotifyDrivesChangedL(const MDesCArray* aItemArray);

    private:    // Functions from base classes

        /**
        * From CAknSettingPage
        * Overwritten method from CAknSettingPage in order to catch
        * a dialog close event.
        */
        TBool OkToExitL( TBool aAccept );

        /**
        * From CCoeControl
        */
        TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );
        
        /**
        * From MEikCommandObserver
         *
        * @param	aCommandId	Event Id from the soft-key
        */
        void ProcessCommandL(TInt aCommandId);
        
        /**
        * For update item text 
        */
        void UpdateAndRedrawItemL();
    private:    // Data

        // Ref: observer.
        MAknCommonDialogsEventObserver& iObserver;
        CAknMemorySelectionModel* iModel;
        TBool iUpdateItem ;        
    };

#endif // CAKNCOMMONDIALOGSRADIOBUTTONSETTINGPAGE_H

// End of File
