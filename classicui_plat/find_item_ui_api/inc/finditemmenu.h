/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef FINDITEMMENU_H
#define FINDITEMMENU_H

//  INCLUDES
#include <e32base.h>
#include <finditemengine.h>
#include <ConeResLoader.h>
#include <ItemFinder.h>

// AIW related headers
#include <AiwServiceHandler.h>
#include <aiwdialdataext.h>

#include <apparc.h> // MApaEmbeddedDocObserver
#include <AiwCommon.h>

#include <cenrepnotifyhandler.h>

// FORWARD DECLARATIONS
class CRepository;
class CEikMenuPane;
#ifndef RD_VIRTUAL_PHONEBOOK
class CPbkContactEngine;
class CPbkDataSaveAppUi;
class RPbkViewResourceFile;
#endif // !RD_VIRTUAL_PHONEBOOK
class CFindItemVoIPExtension;
class CCommonUiMPEngineApiLoader;

// CLASS DECLARATION

NONSHARABLE_CLASS(CCommonUiRepositoryWatcher) : public CBase, public MCenRepNotifyHandlerCallback
    {
public:
    static CCommonUiRepositoryWatcher* NewL(
        const TUid aUid,
        const TUint32 aKey,
        CCenRepNotifyHandler::TCenRepKeyType aKeyType,
        TCallBack aCallBack,
        CRepository* aRepository);

    ~CCommonUiRepositoryWatcher();

    TUint32 ChangedKey();

public: // from MCenRepNotifyHandlerCallback
    void HandleNotifyInt    (TUint32 aKey, TInt aNewValue);
    void HandleNotifyError  (TUint32 aKey, TInt aError, CCenRepNotifyHandler* aHandler);

private:
    CCommonUiRepositoryWatcher(
        const TUid aUid,
        const TUint32 aKey,
        TCallBack aCallBack,
        CRepository* aRepository);

    void ConstructL(CCenRepNotifyHandler::TCenRepKeyType aKeyType);

    void ConstructL();

private:
    TUid                    iUid;
    TUint32                 iKey;
    TUint32                 iChangedKey;
    TCallBack               iCallBack;
    CRepository*            iRepository;
    CCenRepNotifyHandler*   iNotifyHandler;

    };
// aiw call back funtion
NONSHARABLE_CLASS( MPBAiwNotify ) : public MAiwNotifyCallback
    {
public:
    IMPORT_C virtual TInt HandleNotifyL(TInt aCmdId, TInt aEventId,
            CAiwGenericParamList& aEventParamList,
            const CAiwGenericParamList& aInParamList);
    };
/**
*  CFindItemMenu - class to provide (localized) "Find Item" menu items
*   for applications to dynamically build Options menu.
*
*   Usage:
*       See Find Item design document for complete example.
*
*/
NONSHARABLE_CLASS(CFindItemMenu) :public CBase
    {
    public:  // Constructors and destructor 
        /**  
        * Enumeration for menu items that can be handled 
        * via SetMenuItemVisibility
        * If you add more items, numbering must follow sequence
        * 1,2,4,8,16,32,...*/
        enum TMenuItem
            {
            ECallItem = 1
            };  
    
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        *
        * @param aCommandId     Starting point of command ids that the
        *                       application has to supply aCommandId will
        *                       be used for the "FindItem" menu commands, so
        *                       it and cascading three resource id's should
        *                       be unused.
        */
        IMPORT_C static CFindItemMenu* NewL( const TInt aCommandId );

        /**
        * Two-phased constructor. Pointer is left to CleanupStack.
        *
        * @param aCommandId     Starting point of command ids that the
        *                       application has to supply aCommandId will
        *                       be used for the "FindItem" menu commands, so
        *                       it and cascading three resource id's should
        *                       be unused.
        */
        IMPORT_C static CFindItemMenu* NewLC( const TInt aCommandId );

        /**
        * Destructor.
        */
        virtual ~CFindItemMenu();

    public:

        /**
        * Inserts the FindItem menu item into menupane
        *
        * @param aMenuPane  a Menupane that the items will be added
        * @param aIndex     Position in menupane where items will be added,
        *                   i.e. a command id of the previous menuitem
        */
        IMPORT_C void DisplayFindItemMenuItemL( CEikMenuPane& aMenuPane,
                                                const TInt aIndex );

        /**
        * Displays the FindItem cascade menu
        *
        * @param aMenuPane  a Menupane that the items will be displayed
        */
        IMPORT_C void DisplayFindItemCascadeMenuL( CEikMenuPane&
                                                    aMenuPane ) const;

        /**
        * Allows the application's HandleCommandL() method to
        *   switch appropriately on menuselections
        *
        * @param    aCommandId  a Command id to check
        *
        * @return   Whether the command id was a valid.
        */
        IMPORT_C TBool CommandIsValidL( const TInt aCommandId ) const;

        /**
        * Gives a search case for a command id
        *
        * @param    aCommandId  a Command id to check
        *
        * @return   Enumeration that can be given to CFindItemDialog's NewL()
        */
        IMPORT_C CFindItemEngine::TFindItemSearchCase SearchCase(
                                            const TInt aCommandId ) const;

        /**
        * @since Series 60 2.6
        * Notify find menu to update items in menupane. Called in applications
        * DynInitMenuPane for main menu or context menu. Application shuold provide
        * all unknown menupanes to this method. (AIW, add to contacts etc.)
        *
        * @param    aRecource      MenuId of particular menu (defaults to KErrNone)
        * @param    aMenuPane      Menupane to update (defaults to null)
        */
        IMPORT_C void UpdateItemFinderMenuL(TInt aResource=KErrNotFound,CEikMenuPane* aMenuPane = 0);

        /**
        * @since Series 60 2.6
        * Request to handle find specific command. Called in applications HandleCommandL().
        * AknItemFinder related members must be set before calling this method.
        * As the method does not return value, application should check the command validity
        * by using CommandIsValidL() before passing command to find menu
        *
        * @param    aCommand      Command to be handled, if find menu does not recognize command,
        *                         method does nothing.
        */
        IMPORT_C void HandleItemFinderCommandL(TInt aCommand);

        /**
        * @since Series 60 2.6
        * Initialized AIW menu and interests.
        * Must be called once after construction of class in order to enable AIW
        *
        * @param    aResource        Applications main menupane resource id
        */
        IMPORT_C void AttachItemFinderMenuL(TInt aResource);

        /**
        * @since Series 60 2.6
        * Set callback number .
        * Must be called before before menu is initialized (AddItemFinderMenuL())
        * if callback number is found in message
        * @param    aPhonenumber       Callback number
        */
        IMPORT_C void SetCallbackNumber (const TDesC& aPhoneNumber);

        /**
        * @since Series 60 2.7
        * Make a call. If callback number is initialised, first we query from user
        * to which number (CallBack number or aSenderDescriptor) we should make that call.
        * @param    aSenderDescriptor       Number to which we should call
        */
        IMPORT_C void HandleCallL(const TDesC& aSenderDescriptor);

        /**
        * @since Series 60 3.0
        * Make a VoIP call. If callback number is initialised, first we query from user
        * to which number (CallBack number or aSenderDescriptor) we should make that call.
        * @param    aSenderDescriptor       Number to which we should call
        */
        IMPORT_C void HandleVoIPCallL(const TDesC& aSenderDescriptor);

        /**
        * @since Series 60 3.2
        * Sets the highlight status of the sender field to indicate if this field is
        * currently being highlighted or not (set to EFalse by default).
        * This setting has impact only when automatic find is turned on and focus
        * is in the header. 
        * @param    aStatus     ETrue if sender field is currently highlighted, 
        *                       otherwise EFalse.
        */
        IMPORT_C void SetSenderHighlightStatus( TBool aStatus );

        /**
        * @since Series 60 3.2
        * Sets the contents of the sender field shown on the display.
        * This setting has impact only when automatic find is turned on and focus
        * is in the header.        
        * @param    aText       Sender contents currently shown on the display.
        */
        IMPORT_C void SetSenderDisplayText( const TDesC& aText );
        
        /**
        * @since Series 60 3.2
        * Initialize members needed to update items in menupane. Called in applications
        * DynInitMenuPane for main menu or context menu
        *
        * @param    aItemFinder    Pointer to CommonUi item finder instance
        * @param    aMenuPane      Menupane where an items will be added
        * @param    aIndex         Position in menupane where the item
        *                          will be added i.e. a command id of the
        *                          previous menuitem (usually EFindItemMenuPlaceHolder)
        *                          When AIW in use, this command will be deleted from menu
        * @param    aSenderDescriptor   Possible sender number/address, can be KNullDesC
        *                               If not a phone number, corrct type must be set via
        *                               SetSenderDescriptorType()
        * @param    aSenderKnown   Is sender known ( defaults to EFalse )
        * @param    aIsContextMenu Is menu context menu ( defaults to EFalse )
        */
        IMPORT_C void AddItemFindMenuL(
                                    CItemFinder* aItemFinder,
                                    CEikMenuPane* aMenuPane,
                                    TInt aIndex,
                                    const TDesC& aPhoneNumber,
                                    TBool aKnownSender = EFalse,
                                    TBool aIsContextMenu = EFalse);

        /**
        * @since Series 60 3.2
        * Sets item type for sender descriptor (defaults to EPhoneNumber)
        * Must be called before before menu is initialized (AddItemFindMenuL())
        * if descriptor type is not phone number.
        *
        * @param    aType        Which kind of data sender descriptor contains
        */
        IMPORT_C void SetSenderDescriptorType(CItemFinder::TItemType aType);                            
             
        /**
        * Sets menu item visibility 
        * Must be called before before menu is initialized (AddItemFindMenuL())
        * 
        * @since Series 60 3.2
        * @param    aItem        menu item
        * @param    aVisible     ETrue = menu item allowed (visible), 
        *                        EFalse = menu item not allowed.
        */
        IMPORT_C void SetMenuItemVisibility( 
            CFindItemMenu::TMenuItem aItem,
            TBool aVisible );                           
                  
    private:

        /**
        * C++ default constructor.
        */
        CFindItemMenu();

        /**
        * ConstructL
        */
        void ConstructL( const TInt aCommandId );

        /**
        * Loads the resource for menuitems
        */
        void LoadResourceFileL();

        /**
        * Adds the menu item to menupane
        *
        * @param    aMenuPane   Menupane where an item will be added
        * @param    aCommandId  Command id of the item
        * @param    aIndex      Position in menupane where the item
        *                       will be added i.e. a command id of the
        *                       previous menuitem
        * @param    aCascadeId  Item's cascade id
        * @param    aText       Text of the menuitem
        */
        void AddMenuItemL(
            CEikMenuPane& aMenuPane,
            TInt aCommandId,
            TInt aIndex,
            TInt aCascadeId,
            const TDesC& aText ) const;

        // Item finder item handling ( not AIW based )

        void CallL();
        void VoIPCallL(); // creates VoIP call
        void SendMessageL( const TUid aMtmUid );
        void GoToUrlL(TUid aHandlerAppUid);
        void AddToBookmarkL();
        void CreateContactCardL( TInt aCommandId );
        void AddToGalleryL();

        void AutoFindStatusChangedL();
        static TInt AutoFindStatusChanged(TAny* aThis);

        // added parameter to define the dial data type.
        TBool FormatDialDataL( TBool aFormatVoIPDialData );
        void LaunchGenericUriL();
        HBufC* ChooseNumberQueryL(TInt& aIndex);
        void LoadMPEngineApiL();
        void CopyToClipboardL();

        CItemFinder::TItemType CurrentItemType();
        HBufC* CurrentItemDescriptor();
        void SetFindModeL( TInt aFlags );
        TBool ItemFinderExists();
        TPtrC CurrentSelection(); 
        
    private:
        /**
        * Enumeration for menu command ids
        */
        enum TFindCase
            {
            EFindUrlAddress = 1,
            EFindMailAddress = 2,
            EFindPhoneNumber = 3
            };

    private:    // Data
        // Command id which will be given in construction
        CCoeEnv* iCoeEnv;

        TInt iFindItemCommandId;
        // Resource file offset
        TInt iResourceFileOffset;

        // String for cascaded FindItem menu
        HBufC* iFindItemMenuItemString;
        // String for Url menuitem
        HBufC* iFindItemUrlItemString;
        // String for Mail menuitem
        HBufC* iFindItemMailItemString;
        // String for Phone menuitem
        HBufC* iFindItemPhoneItemString;
        //String for Tel Internet menuitem
        HBufC* iFindItemTelInternetItemString;
        // Is Menuitem added
        TBool iFindItemMenuItemAdded;
        //Resource loader
        RConeResourceLoader iResLoader;


        // Item finder related members
        CItemFinder* iAutomaticFind; // not owned                
        
        CEikMenuPane* iMenuPane;  // not owned
        HBufC* iSenderDescriptor; // owned, possible sender number
        TBool iIsSenderKnown; // Shall we show add to Contacts for sender
        TBool iIsContextMenu;
        TInt iIndex;

#ifndef RD_VIRTUAL_PHONEBOOK
        CPbkContactEngine* iPbkEngine;
        CPbkDataSaveAppUi* iPbkDataSave;
        RPbkViewResourceFile* iRPbkResourceFile;
#endif // !RD_VIRTUAL_PHONEBOOK

        CItemFinder::TItemType iSenderDescType;

        // AIW related members
        CAiwServiceHandler* iServiceHandler;

        CRepository* iCommonUiRepository;
        CCommonUiRepositoryWatcher* iCommonUiRepositoryWatcher;

        TBool iHideCallMenu;

        // Is sender field currently highlighted.
        TBool iSenderHighlighted;

        // The sender contents shown on display.
        HBufC* iSenderDisplayText;
        
        // DialData.
        CAiwDialDataExt* iDialData;

        // Possible callback number, owned.
        HBufC* iCallbackNumber; 

        // Contains information of the VoIP profiles.
        CFindItemVoIPExtension* iFindItemVoIPExtension;

        // Contains information of MMS support
        TBool iMMSFeatureSupported;

        // Contains information of Audio Messaging support
        TBool iAudioMessagingFeatureSupported;

        // Contains information of Email over SMS support
        TBool iEmailOverSmsFeatureSupported;

        // Contains information of MMS support
        TBool iEmailUiFeatureSupported;

        // Contains information of the internet call support
        TBool iVoIPFeatureSupported;

        // A handle to a dynamically loadable DLL.
        RLibrary iMPEngineDll;

        // Has the Npd Api DLL already been loaded.
        TBool iMPEngineDllLoaded;

        // Loads MPEngine Api DLL dynamically to memory.
        CCommonUiMPEngineApiLoader* iMPEngineApi;
                 
        /**
        * Menu item flags
        */
        TInt iMenuItemFlags;
        MPBAiwNotify iCallback;
   };

#endif      // FINDITEMMENU_H

// End of File
