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
* Description:  Defines ECOM interface for Slide set setting dialog.
*
*/


#ifndef C_PSLNSLIDESETDIALOGINTERFACE_H
#define C_PSLNSLIDESETDIALOGINTERFACE_H

#include <ecom/ecom.h>
#include <AknDialog.h>

// Constants used in ECOM implementation
const TUid KPslnSlideSetPluginInterfaceUid    = { 0x102823AD };
// Defines Wallpaper setting dialog entry in implementation table
const TInt KPslnWallpaperSlideSettingDialog = 0;
// Defines Screen Saver setting dialog entry in implementation table
const TInt KPslnScreenSaverSlideSettingDialog = 1;

// Defines type of slide set setting dialog.
enum TPslnSlideSetDialogType
    {
    EPslnScreensaverDialog,
    EPslnWallpaperDialog
    };

/**
 *  ECOM interface definition for setting dialog.
 *
 *  This interface defines interface for slide setting dialog base.
 *
 *  @lib pslnslidesetdialog.dll
 *  @since S60 3.2
 */

class CPslnSlidesetDialogInterface : public CAknDialog
    {
public:

    // Defines dialog launch mode.
    enum TPslnSlideSetLaunchMode
        {
        // Dialog is launched normally and 
        // user made selections are immediately activated
        EPslnNormal,
        // Dialog is launched for configuration only.
        // Settings need to be separately activated.
        EPslnConfigureOnly
        };

    // Defines dialog configurability state.
    enum TPslnSlideSetConfigurability
        {
        // State is unknown. Settings need to be defined.
        EPslnUnknown,
        // Dialog settings need to be configured before activation.
        EPslnNeedsToBeConfigured,
        // Slide set can directly activate - no need to define settings.
        EPslnDirectActivationPossible
        };

    // Defines dialog flags.
    enum TPslnSlideSetDialogFlags
        {
        // Type of dialog.
        EPslnDialogType,
        // For what purpose the dialog is launched.
        EPslnLaunchMode,
        // Can the slide set be directly activated.
        EPslnConfigurability
        };

    /**
    * Creates new Psln ECOM plugin for slideset dialog having the given UID.
    * Uses Leave code KErrNotFound if implementation is not found.
    *
    * @param aImplementationUid Implementation UID of the plugin to be
    *        created.
    */
    static CPslnSlidesetDialogInterface* NewL( const TUid aImplementationUid );

    /**
    * Destructor.
    */
    inline ~CPslnSlidesetDialogInterface();

    /**
    * Reserved for future use/plugin's custom functionality. This can be
    * overwritten if plugin needs to have custom functionality which cannot
    * be fulfilled otherwise.
    */
    virtual inline TAny* CustomOperationL( TAny* aParam1, TAny* aParam2 );

    /*
    * Executes dialog.
    *
    */
    virtual TInt ExecuteDialogLD() = 0;
    
    /*
    * Defines dialog flag. Currently supported flags are defined in 
    * TPslnSlideSetDialogFlags.
    * @param aFlag which flag to set new state to.
    * @param aValue new value of flag.
    */
    virtual void SetDialogFlag( const TInt aFlag, const TInt aValue ) = 0;

    /*
    * Inqueries for dialog flags. Currently supported flags are defined in 
    * TPslnSlideSetDialogFlags.
    * @param aFlag which flag to retrieve status for 
    *        (see TPslnSlideSetDialogFlags for details)
    * @return current value of the flag.
    *
    */
    virtual TInt GetDialogFlag( const TInt aFlag ) = 0;

private: // data

    /**
     * ECOM plugin instance UID.
     */
     TUid iDtor_ID_Key;

    };


#include "pslnslidesetdialoginterface.inl"


#endif // C_PSLNSLIDESETDIALOGINTERFACE_H
