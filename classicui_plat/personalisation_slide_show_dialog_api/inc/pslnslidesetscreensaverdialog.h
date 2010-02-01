/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Screensaver slideset setting dialog implementation header.
*
*/


#ifndef C_PSLNSLIDESETSCREENSAVERDIALOG_H
#define C_PSLNSLIDESETSCREENSAVERDIALOG_H

#include <pslnslidesetdialog.h>

/**
 *  Provides the dialog functionality for defining Slide Set Settings
 *  for screensavers.
 *
 *  To use this from code, instantiate the ECOM plugin.
 *  Then call ExecuteLD.
 *  Example:
 *
 *    // List all implementations.
 *    REComSession::ListImplementationsL( 
 *       KPslnSlideSetDialogUidInterface, 
 *       array );
 *    CleanupResetAndDestroyPushL( array );
 *
 *    // Load screensaver implementation.
 *    CImplementationInformation* info = 
 *       array[ KPslnScreenSaverSlideSettingDialog ];
 *    TUid implUid = info->ImplementationUid();
 *
 *    // Instantiate plugin.
 *    CPslnSlidesetScreensaverDialogInterface* plugin = 
 *        CPslnSlidesetDialogInterface::NewL( implUid );
 *    CleanupStack::PushL ( plugin );
 *
 *    // Finally execute.
 *    plugin->ExecuteLD();
 *    CleanupStack::Pop( plugin );
 *    CleanupStack::PopAndDestroy(); // array
 *
 *  @lib pslnslidesetdialog.dll
 *  @since S60 3.2
 */
NONSHARABLE_CLASS( CPslnSlidesetScreensaverDialog ): 
    public CPslnSlidesetDialog
    {
public:

    /**
    * Symbian OS two-phased constructor
    * @return Psln Slide Set Setting dialog instance.
    */
    static CPslnSlidesetScreensaverDialog* NewL();

    /**
    * Symbian OS two-phased constructor
    * @return Psln Slide Set Setting dialog instance.
    */
    static CPslnSlidesetScreensaverDialog* NewLC();

    /**
    * Destructor.
    */
    ~CPslnSlidesetScreensaverDialog();

    /**
    * From TPslnSlidesetDialogInterface - executes dialog.
    */
    TInt ExecuteDialogLD();

    /**
    * From TPslnSlidesetDialogInterface - sets dialog flags.
    */
    void SetDialogFlag( const TInt aFlag, const TInt aValue );

    /**
    * From TPslnSlidesetDialogInterface - gets dialog flags.
    */
    TInt GetDialogFlag( const TInt aFlag );

    /**
    * From CEikDialog - prelayouts dialog.
    */
    void PreLayoutDynInitL();

private:

    /**
    * From CAknDialog.
    * Framework method to determine if it OK to exit the dialog.
    */
    TBool OkToExitL( TInt aButtonId );

    /**
    * From CPslnSlidesetDialog.
    * Creates setting page items.
    */
    void CreateListBoxItemsL();

    /**
    * From CCoeControl. Gets Help context.
    */
    void GetHelpContext( TCoeHelpContext& aContext ) const;

    /**
    * Shows slide set duration setting page.
    */
    void ShowDurationSliderL();

    /**
    * Shows slide set backlight period setting page.
    */
    void ShowBacklightSliderL();

    /**
    * C++ constructor.
    */
    CPslnSlidesetScreensaverDialog();

    /**
    * Symbian 2nd phase constructor.
    */
    void ConstructL();

    };

#endif // C_PSLNSLIDESETSCREENSAVERDIALOG_H
