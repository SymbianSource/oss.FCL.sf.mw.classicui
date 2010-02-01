/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Base class for application specific skin views.
*
*/


#ifndef C_PSLNFWBASEVIEW_H
#define C_PSLNFWBASEVIEW_H

#include "pslnfwplugininterface.h"
#include <ConeResLoader.h>
#include <eikclb.h>

class CPslnFWBaseContainer;
class CAknNavigationDecorator;
class CAknNavigationControlContainer;

/**
*  CPslnFWBaseView view class.
*  Base class for Psln plugin views.
*
*  @lib PslnFramework.lib
*  @since S60 v3.1
*/
class CPslnFWBaseView : public CPslnFWPluginInterface, public MEikListBoxObserver
    {

public:

    /**
    * C++ default constructor
    */
    IMPORT_C CPslnFWBaseView();

    /**
    * Symbian OS default constructor.
    */
    IMPORT_C virtual void ConstructL() = 0;

    /**
    * Destructor.
    */
    IMPORT_C ~CPslnFWBaseView();

    /**
    * This function is used to set the current item in the listbox.
    * @param aIndex Current item.
    */
    IMPORT_C virtual void SetCurrentItem( TInt aIndex );

    /**
    * Returns the container this view has.
    * @return pointer to container, does not transfer ownership.
    */
    IMPORT_C CPslnFWBaseContainer* Container();

    /**
    * Opens the nearest localized resourcefile using aResourceLoader.
    * aResourceLoader should be opened only once before closing it.
    * Otherwise it will raise a panic. Therefore it is better to have
    * multiple resource loaders. Uses KDC_RESOURCE_FILES_DIR.
    *
    * @param aResourceFileName Drive and name of resource file in format
    *                          <path>:<rsc_file_name>
    * @param aResourceLoader Resource loader for the resource. The loader
    *                        must not be opened allready or it will raise
    *                        a panic. It is caller's responsibility to
    *                        close the resource loader after using the
    *                        resource.
    */
    IMPORT_C void OpenLocalizedResourceFileL(
        const TDesC& aResourceFileName,
        RConeResourceLoader& aResourceLoader );

    /**
    * Sames as above, except API user can defined path where to look for
    * resource file.
    *
    * @param aResourceFileName Drive and name of resource file in format
    *                          <path>:<rsc_file_name>
    * @param aResourceLoader Resource loader for the resource. The loader
    *                        must not be opened allready or it will raise
    *                        a panic. It is caller's responsibility to
    *                        close the resource loader after using the
    *                        resource.
    * @param aPath           Path to the resource file. Preferably use
    *                        data caging literals.
    */
    IMPORT_C void OpenLocalizedResourceFileL(
        const TDesC& aResourceFileName,
        RConeResourceLoader& aResourceLoader,
        const TDesC* aPath );

    /**
    * Overrides default navi pane decorator with given one.
    * @param aDecorator navi pane decorator to use.
    */
    IMPORT_C virtual void SetNaviPaneDecorator(
        CAknNavigationDecorator* aDecorator );

    /**
    * From CAknView.
    * Called when view is activated.
    * @param aPrevViewId previous view id.
    * @param aCustomMessageId custom message id.
    * @param aCustomMessage custom message content.
    */
    IMPORT_C void DoActivateL( const TVwsViewId& aPrevViewId,
                               TUid aCustomMessageId,
                               const TDesC8& aCustomMessage );

    /**
    * From CAknView.
    * Called when view is deactivated.
    */
    IMPORT_C void DoDeactivate();

    /**
    * Sets tab index for the view. Since application might insert
    * the view into a tab group with different location than the
    * plugin wants. It is necessary that the application informs
    * plugin the real location. Negative index or index that
    * are greater than tabgroup's last position are ignored.
    *
    * @param aMyTabIndex real tab index of the plugin in the tab group.
    *
    */
    IMPORT_C void SetTabIndex( TInt aMyTabIndex );

    /**
    * Returns the real tab index for the plugin. See API SetTabIndex
    * for details, when using this API might be necessary.
    * It is recommended that this API is used instead of hardcoded
    * constants for tab index, since Psln Framework might assign the
    * plugin to some other location than the plugin prefers.
    *
    * @return the real tab index for the plugin. KErrNotFound is returned,
    * if the tab index has not been set.
    */
    IMPORT_C TInt GetTabIndex() const;

protected:

    /**
    * Sets the correct navi pane for the view (eg. tabs, string etc.).
    * Use when tab group is not to be shown, or plugin handles the tab group
    * itself.
    */
    IMPORT_C virtual void SetNaviPaneL();

    /**
    * Deprecated.
    */
    IMPORT_C virtual void CreateNaviPaneContextL( TInt aResourceId );

    /**
    * Creates container,
    */
    IMPORT_C virtual void CreateContainerL();

    /**
    * Create new container. Called by DoActivateL().
    * Implemented by sub-class.
    */
    IMPORT_C virtual void NewContainerL() = 0;

    /**
    * Sets the correct navi pane for the view (eg. tabs, string etc.).
    * @param aTabLocation indicates the location of view within the Appui
    *                     owned tabgroup.
    */
    IMPORT_C virtual void SetNaviPaneL( const TInt aTabLocation );

    /**
    * From MEikListBoxObserver.
    * Handles listbox events.
    * @param aListBox listbox pointer.
    * @param aEventType event type.
    */
    void HandleListBoxEventL( CEikListBox* aListBox,
        TListBoxEvent aEventType );

    /**
    * Adds given resource text as MSK to CBA.
    *
    * @param aResourceId middle softkey label.
    * @param aCommandId command that should be performed when MSK
    *        is pressed.
    * @since S60 v3.1
    */
    IMPORT_C virtual void SetMiddleSoftKeyLabelL(
        const TInt aResourceId,
        const TInt aCommandId );

    /**
    * Handles Download and Help commands.
    * Unknown commands are forwarded to appUi.
    * @param aCommand command ID - it should match commands given in the psln.hrh.
    */
    IMPORT_C virtual void HandleCommandL( TInt aCommand );

    /**
    * Plugins should implement this virtual method. It allows that the plugin provides a resource
    * ID that the framework should use as title text for the view.
    * @param aResourceId resource ID of title text to use.
    *
    * @since 5.0
    * NOTE that the resource file should be loaded and open.
    */
    IMPORT_C virtual void SetTitlePaneL( TInt& aResourceId );

private:

    /**
    * Handles listbox selection. Called by HandleListBoxEventL.
    * Implement by sub-class.
    */
    virtual void HandleListBoxSelectionL() = 0;

    /**
    * Checks if the tab group is not one of the static views' locations.
    */
    TBool IsValidLocation( const TInt& aLoc ) const;

protected: // data

    /**
    * View UID that was previously active before this view was activated.
    */
    TVwsViewId iPrevViewId;

    /**
    * Pointer to the container
    * Own.
    */
    CPslnFWBaseContainer* iContainer;

    /**
    * Navi pane.
    * Not own.
    */
    CAknNavigationDecorator* iNaviPaneContext;

    /**
    * Pointer to the navi control container
    * Not own.
    */
    CAknNavigationControlContainer* iNaviControlContainer;

    /**
    * Currently selected listbox item.
    */
    TInt iCurrentItem;

    /**
    * First item in the listbox.
    */
    TInt iTopItemIndex;

    /**
    * Resource loader.
    */
    RConeResourceLoader iResourceLoader;

    /**
    * Real tab group index for the view.
    */
    TInt iMyTabIndex;
    };

#endif // C_PSLNFWBASEVIEW_H

// End of File
