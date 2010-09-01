/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Wallpaper slideset setting dialog implementation header.
*
*/


#ifndef C_PSLNSLIDESETWALLPAPERDIALOG_H
#define C_PSLNSLIDESETWALLPAPERDIALOG_H

#include <pslnslidesetdialog.h>

/**
 *  Provides the dialog functionality for defining Slide Set Settings
 *  for wallpapers and screensavers.
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
 *    // Load wallpaper implementation.
 *    CImplementationInformation* info = 
 *       array[ KPslnWallpaperSlideSettingDialog ];
 *    TUid implUid = info->ImplementationUid();
 *
 *    // Instantiate plugin.
 *    CPslnWallpaperSlidesetDialogInterface* plugin = 
 *        CPslnSlidesetDialogInterface::NewL( implUid );
 *    CleanupStack::PushL ( plugin );
 *    // Finally execute.
 *    plugin->ExecuteLD();
 *    CleanupStack::Pop( plugin );
 *    CleanupStack::PopAndDestroy(); // array
 *
 *  To configure the slide set without activating it, 
 *  call SetDialogFlag prior to calling ExecuteLD.
 *  Use parameters
 *      PslnSlidesetDialogInterface::EPslnLaunchMode and
 *      PslnSlidesetDialogInterface::EPslnConfigureOnly.
 *
 *  @lib pslnslidesetdialog.dll
 *  @since S60 3.2
 */
NONSHARABLE_CLASS( CPslnWallpaperSlidesetDialog ): 
    public CPslnSlidesetDialog
    {
public:

    /**
    * Symbian OS two-phased constructor
    * @return Psln Slide Set Setting dialog instance.
    */
    static CPslnWallpaperSlidesetDialog* NewL();

    /**
    * Symbian OS two-phased constructor
    * @return Psln Slide Set Setting dialog instance.
    */
    static CPslnWallpaperSlidesetDialog* NewLC();

    /**
    * Destructor.
    */
    ~CPslnWallpaperSlidesetDialog();

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

    /**
    * From CAknDialog.
    * Called by framework to process commands invoked by the user.
    */
    void ProcessCommandL( TInt aCommandId );

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
    * Shows interval period setting page.
    */
    void ShowIntervalListL();

    /*
    * Deduce if the slide set can activate directly (i.e.
    * no need to set settings).
    */
    TInt DeduceActivationModeL();

    /*
    * Append one interval value to list. Makes also language
    * dependant conversion for the text.
    */
    void AppendIntervalItemL( TInt aResourceText );

    /**
    * C++ constructor.
    */
    CPslnWallpaperSlidesetDialog();

    /**
    * Symbian 2nd phase constructor.
    */
    void ConstructL();
    };


#endif // C_PSLNSLIDESETWALLPAPERDIALOG_H
