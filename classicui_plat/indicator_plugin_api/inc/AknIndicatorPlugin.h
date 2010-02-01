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
* Description:  Indicator ECOM Plugin interface declaration.
*
*/


#ifndef C_AKNINDICATORPLUGIN_H
#define C_AKNINDICATORPLUGIN_H

// INCLUDES
#include <ecom/ecom.h>
#include <AknIndicatorPluginImplUIDs.hrh>

// FORWARD DECLARATIONS
class CGulIcon;
class CAknIndicatorPopupContent;

// CONSTANTS
// Interface UID for Indicator Plugin interface
const TUid KAknIndicatorPluginIfUid = { KAknIndicatorPluginInterfaceUid };

/**
*  @c CAknIndicatorPlugin has to be implemented
*  by each ECOM based indicator tap handler plugin.
*
*  A single indicator ECOM plugin can implement the functionality
*  for multiple indicators, since the indicator UID is always passed to
*  the interface.
*
*  Each indicator ECOM plugin has to implement the @c HandleIndicatorTapL()
*  method, as well as the TextL() method for at least indicators
*  which have a function link
*
*  The implementation for @c HandleIndicatorTapL() should provide eg. a
*  direct access to the indicator-related settings or
*  launch the application whose indicator is in question.
*
*  @lib avkon.lib
*  @since 5.0
*/
class CAknIndicatorPlugin : public CBase
{
public:

    enum TAknIndicatorPluginTextTypes
        {
        EAknIndicatorPluginLinkText = 1,
        EAknIndicatorPluginInformationText
        };

public: // Constructors and destructor

    /**
    * Two-phased constructor.
    *
    * @param  aImplUid  Implementation UID of the plugin.
    *
    * @return  Pointer to an object of @c CAknIndicatorPlugin.
    */
    IMPORT_C static CAknIndicatorPlugin* NewL( const TUid& aImplUid );

    /**
    * Destructor.
    */
    IMPORT_C virtual ~CAknIndicatorPlugin();

public: // New functions

    /**
    * Implements tap actions for the indicator in question (@c aUid).
    *
    * @param  aUid  UID of the indicator.
    */
    virtual void HandleIndicatorTapL( const TInt aUid ) = 0;
    
    /**
    * Returns the description used as link text, displayed with
    * the indicator icon in the indicator popup.
    *
    * @param       aUid       UID of the indicator.
    * @param[out]  aTextType  Type of the text,
    *                         @see TAknIndicatorPluginTextTypes.
    *
    * @return  Indicator description or link text.
    *          Ownership is transferred.
    */
    IMPORT_C virtual HBufC* TextL( const TInt aUid, TInt& aTextType );
    
    /**
    * Returns the indicator icon used in the indicator popup.
    * If the implementation return @c NULL, then the
    * indicator pane icon is used in the popup.
    *
    * The implementation should always re-create the icon
    * when this method is called, because the color of the
    * icon is updated by calling this method when skin changes.
    *
    * @param   aUid  UID of the indicator.
    *
    * @return  The indicator icon.
    *          Ownership is not transferred.
    */
    IMPORT_C virtual const CGulIcon* IconL( const TInt aUid );
    
    /**
    * Method to update the plugin's data in the indicator popup.
    *
    * When an indicator's icon or text changes, the plugin
    * implementation for that indicator should call this method.
    *
    * @param  aUid  UID of the indicator to be updated.
    */
    IMPORT_C void UpdateL( TInt aUid );
    
    /**
    * Set the observer of the plugin's data.
    *
    * @internal This is automatically called by the framework when loading
    *           the plugin, and should not be overridden by the plugin.
    *
    * @param  aPluginObserver  Pointer to the observer.
    */
    void SetPluginObserver( CAknIndicatorPopupContent* aPluginObserver );
    
private: // Member data

    /** Implementation UID of the indicator tap handler. */
    TUid iDtor_ID_Key;
    
    /**
    * Pointer to the plugin's indicator data change observer.
    * Not own.
    */
    CAknIndicatorPopupContent* iPluginObserver;
};

#endif  // C_AKNINDICATORPLUGIN_H

// End of File
