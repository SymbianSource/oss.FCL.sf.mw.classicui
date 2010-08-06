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


#ifndef FINDITEMDIALOG_H
#define FINDITEMDIALOG_H

// INCLUDES
#include <coecntrl.h>
#include <coeccntx.h>

#include <eikapp.h>
#include <eikdoc.h>
#include <e32std.h>
#include <eikdialg.h>
#include <AknForm.h>
#include <finditemengine.h>
#include <ConeResLoader.h> // for RConeResourceLoader
#ifndef RD_VIRTUAL_PHONEBOOK
#include <RPbkViewResourceFile.h>
#endif // !RD_VIRTUAL_PHONEBOOK
#include <eikcapc.h>
#include <w32std.h>
#include <AknNaviDecoratorObserver.h>

// AIW
#include <AiwServiceHandler.h>
#include <aiwdialdataext.h>

// FORWARD DECLARATIONS
class CEikRichTextEditor;
class CEikScrollBarFrame;
class CAknTitlePane;
class CAknNavigationControlContainer;
class CAknNavigationDecorator;
class CPbkContactEngine;
class CFindItemController;
#ifndef RD_VIRTUAL_PHONEBOOK
class CPbkDataSaveAppUi;
#endif // !RD_VIRTUAL_PHONEBOOK
class TCoeHelpContext;
class CFindItemVoIPExtension;
class CAknsBasicBackgroundControlContext;
class CRichTextEditorContainer;
class CItemFinderExtension;

// CLASS DECLARATION

/*
*   MFindItemDialogCallBack
*       Pure virtual callback class to enable a controller to communicate with the dialog
*/
class MFindItemDialogCallBack
    {
    public:
        /**
        * Updates editor's selection.
        *   Pure virtual method that needs to be overriden
        *
        * @param aItem Item that will be selected
        */
        virtual void SelectionChangedL( const CFindItemEngine::SFoundItem& aItem ) = 0;
        /**
        * Updates editor's selection.
        *   Pure virtual method that needs to be overriden
        *
        * @param aItem Item that will be selected
        * @param aNext Gives the direction of selections movement
        *   aNext is ETrue if moving forward
        */
        virtual void SelectionChangedL( const CFindItemEngine::SFoundItem& aItem, const TBool aNext ) = 0;

        /**
        * Returns ETrue if items are in same line
        *
        * @param aItem1  First document position to compare
        * @param aItem2  Second document position to compare
        */
        virtual TBool AtSameLine( const TInt& aItem1, const TInt& aItem2 ) = 0;
    };

// CLASS DECLARATION
/**
* CFindItemDialog dialog class
*   This is an interface class for applications to use FindItem.
*   Derived from CAknDialog to enable options menu.
*
* Usage:
*   ----------------------- Copy & Paste -------------------------------
*   CFindItemDialog* dialog = CFindItemDialog::NewL( text, searchCase );
*   dialog->ExecuteLD();
*   --------------------------------------------------------------------
*
*   Text has to be given to dialog as a descriptor.
*   If the application's text is an object derived from CEditableText,
*   like in CEik* editors, there's two possible things that can/need to be
*   done depending on the type of in-memory buffer used:
*       If the text is as a flat buffer, a descriptor can be fetched using
*           TPtrC text = iRichText->Read(0);
*       otherwise a new descriptor need to be created and e.g. richtext's
*       Read() method needs to be called as long as the whole text is
*       inserted to descriptor.
*
*   The dialog will be automatically destroyed by ExecuteLD.
*
*   Use CFindItemMenu class to insert finditem-menuitems to your
*       application's menu. See: finditemmenu.h for more info
*
*   Note ! NewL stores a reference to the text passed as a parameter and
*           uses it when the dialog gets executed so it should not be deleted
*           before the dialog is dismissed.
*
*/
NONSHARABLE_CLASS(CFindItemDialog)
    : public CAknDialog,
    public MFindItemDialogCallBack,
    public MEikScrollBarObserver,
    public MPointerEventObserver,
    public MAknNaviDecoratorObserver
    {

    public: // Constructors and destructor
        /**
        * Destructor.
        */
        IMPORT_C ~CFindItemDialog();
        /**
        * Two-phased constructor.
        *
        * @param aPlainText     Text that will be parsed. Stores the
        *                       reference and uses it when the dialog is
        *                       executed so it should not be destroyed
        *                       before the dialog is dismissed.
        * @param aSearchCase    Identifies what items are we looking for:
        *                           EFindItemSearchPhoneNumberBin
        *                           EFindItemSearchMailAddressBin
        *                           EFindItemSearchURLBin
        *
        * @return Pointer to created CFindItemDialog
        */
        IMPORT_C static CFindItemDialog* NewL( const TDesC& aPlainText,
                const CFindItemEngine::TFindItemSearchCase aSearchCase );

    public: // New functions
        /**
        * Initializes the dialog and calls CAknDialog's
        *   ExecuteLD()
        * This method need to be called to execute the dialog
        * After exiting the dialog gets automatically destroyed
        *
        * @return CAknDialog::ExecuteLD()
        */
        IMPORT_C TInt ExecuteLD();

    public: // Functions from base classes
        /**
        * From MEikCommandObserver Prosesses menucommands
        */
        IMPORT_C void ProcessCommandL( TInt aCommandId );
        /**
        * From CCoeControl Handles key events
        */
        IMPORT_C TKeyResponse OfferKeyEventL(
            const TKeyEvent& aKeyEvent,
            TEventCode aType );

    protected:  // Functions from base classes

        /**
        * From MFindItemDialogCallBack Updates editor's selection.
        *
        * @param aItem Item that will be selected
        */
        void SelectionChangedL( const CFindItemEngine::SFoundItem& aItem );

        /**
        * From MFindItemDialogCallBack Updates editor and selects item
        *
        * @param aItem  Item that will be selected
        * @param aNext  Gives the direction of selections movement
        *                   aNext is ETrue if moving forward
        */
        void SelectionChangedL( const CFindItemEngine::SFoundItem& aItem,
                                const TBool aNext );

        /**
        * From MFindItemDialogCallBack Returns whether positions
        *   are at the same line
        *
        * @param aItem1  First document position to compare
        * @param aItem2  Second document position to compare
        */
        TBool AtSameLine( const TInt& aItem1, const TInt& aItem2 );

        /**
        * From MEikMenuObserver Initializes items on the menu
        *
        * @param aMenuId    Current menu's resource Id
        * @param aMenuPane  Pointer to menupane
        */
        IMPORT_C void DynInitMenuPaneL(TInt aMenuId, CEikMenuPane* aMenuPane);

        /**
        * From CEikDialog Initializes dialog before layout
        */
        void PreLayoutDynInitL();
        /**
        * From CEikDialog Initializes dialog after layout
        */
        void PostLayoutDynInitL();

        /**
        * From CEikDialog Handles button events and looks if the dialog
        *   can be closed
        *
        * @param aButtonId Id of the 'pressed' button
        *
        * @return   EFalse if Options menu was pressed
        *           ETrue otherwise
        */
        TBool OkToExitL( TInt aButtonId );

        /**
        * From CCoeControl
        *   This function is called when Help application is launched.
        *
        * @param aContext Help context
        */
        void GetHelpContext( TCoeHelpContext& aContext) const;

        /**
        * From CAknDialog
        *   This function is called when dialog control is created.
        *
        * @param aControlType Custom control type
        *
        * @return   Control info structure
        *
        */
        SEikControlInfo CreateCustomControlL( TInt aControlType );

        /**
        * From CAknDialog
        *   This function is called to provide access to the contorols.
        *
        * @param aId Provider object Uid
        *
        * @return   Type of object that an object provider is to get.
        *
        */
        TTypeUid::Ptr MopSupplyObject( TTypeUid aId );

        /**
        * From CAknDialog
        *   This function is called when dialog focus has changed.
        *
        */
        void FocusChanged(TDrawNow /*aDrawNow*/);

        /**
        * From CCoeControl
        *   This function is called when dialog resource has changed.
        *
        * @param aType Resource change type
        */
        void HandleResourceChange( TInt aType );

        /**
        * From CCoeControl
        *   This function is called when dialog size has been changed.
        *
        * @param aContext Help context
        */
        void SizeChanged();

        /**
        * From MPointerEventObserver.
        *  This function handles CEikCaptionedControl pointer events.
        *
        * @param aControl Pointer to the control
        * @param aPointerEvent Pointer event
        */
        bool PointerEvent(
            CEikCaptionedControl *aControl,
            const TPointerEvent& aPointerEvent );

        /**
        * From MEikScrollBarObserver.
        *  This function handles CEikScrollBar events.
        * @param aScrollBar Pointer to the scrollbar
        * @param aEventType Event type
        */
        void HandleScrollEventL(
            CEikScrollBar* aScrollBar,
            TEikScrollEvent aEventType );
            
        /**
        * From MAknNaviDecoratorObserver.
        *  This function handles the navi decorator events.        
        * @param aEventID Event id
        */            
        void HandleNaviDecoratorEventL( TInt aEventID );

    private:
        /**
        * Default C++ constructor.
        */
        CFindItemDialog();
        /**
        * C++ constructor
        *
        * @param aPlainText     Text that will be parsed
        * @param aSearchCase    Identifies what items we are looking for:
        *                           EFindItemSearchPhoneNumberBin
        *                           EFindItemSearchMailAddressBin
        *                           EFindItemSearchURLBin
        */
        CFindItemDialog(
            const TDesC& aPlainText,
            const CFindItemEngine::TFindItemSearchCase aSearchCase );

        /**
        * EPOC constructor
        */
        void ConstructL();

        /**
        * Move into previous row, where found item is
        */
        void MoveUpL();

        /**
        * Move into next row, where found item is
        */
        void MoveDownL();

        /**
        * Copies the selected item to clipboard
        */
        void CopyToClipboardL();

        /**
        * Creates a contact card from selected item
        *   Calls ContactAddToExistingL or ContactAddToNewL depending on
        *   whether the user wants to create new contact or add to existing
        */
        void CreateContactCardL( TInt aCommandId );

        /**
        * Creates a contact card from selected item
        */
        void ContactAddToExistingL();

        /**
        * Creates a new contact card from selected item
        */
        void ContactAddToNewL();

        /**
        * Sends message (SMS, MMS or e-mail) to selected item
        *
        * @param aMtmUid    MTM UId of the message type
        */
        void SendMessageL( const TUid aMtmUid );

        /**
        * Goes to URL (selected item) using browser
        *
        * @param aItemtextPtr Selected item
        */
        void GoToUrlL(const TPtr& aItemtextPtr);

        /**
        * Goes to URI (selected item)
        *
        * @return Returns ETrue if Find Item dialog was deleted
        */
        TBool LaunchGenericUriL();

        /**
        * Adds the selected item to bookmarks
        */
        void AddToBookmarkL();

        /**
        * Creates ScrollBarFrame
        */
        void CreateScrollBarFrameL();

        /**
        * Called just before Draw function
        */
        void ActivateL();

        /**
        * Updates ScrollIndicator
        */
        void UpdateScrollIndicatorL();

        /**
        * Updates Navipane
        */
        void UpdateNaviPaneL();

        /**
        * Creates VoIP call
        * @since 3.0
        */
        void CreateInternetCallL();

    private: //data
        // Pointer to controller which controls engine and dialog
        CFindItemController* iController;
        // Plaintext which will be parsed
        TPtrC iPlainText;
        // What we are looking for: phone number, mail- or url-address
        const CFindItemEngine::TFindItemSearchCase iSearchCase;
        // Richtext editor
        CEikRichTextEditor* iEdwin;
        // Titlepane
        CAknTitlePane* iTitlePane;
        // Applications title
        HBufC* iOldTitle;

        // Boolean to display context-sensitive-menu
        TBool iIsSensitiveMenu;

        // Navipane variables
        CAknNavigationControlContainer* iNaviPane;
        CAknNavigationDecorator* iNaviDecorator;
        // ScrollBarFrame
        CEikScrollBarFrame* iSBFrame;
        // Array to enable the scrollbar to know current position.
        CArrayFixFlat<TInt>* iItemArrayForScrollBar;

#ifndef RD_VIRTUAL_PHONEBOOK
        CPbkContactEngine* iPbkEngine;
        CPbkDataSaveAppUi* iPbkDataSave;
        RPbkViewResourceFile iPbkResourceFile;
#endif // !RD_VIRTUAL_PHONEBOOK

        //Resource loader
        RConeResourceLoader iResLoader;

        CIdle* iIdle;

        // AIW related members

        // Service Handler instance.
        CAiwServiceHandler* iServiceHandler;

       // DialData.
        CAiwDialDataExt* iDialData;

        TBool iHideCallMenu;
        // Contains information of the VoIP profiles.
        CFindItemVoIPExtension* iFindItemVoIPExtension;

        CAknsBasicBackgroundControlContext* iBgContext;

        CRichTextEditorContainer* iEdwinContainer;

        TBool iHelpFeatureSupported;

        // Contains information of MMS support
        TBool iMMSFeatureSupported;

        // Contains information of Email over SMS support
        TBool iEmailOverSmsFeatureSupported;

        // Contains information of Email Ui support
        TBool iEmailUiFeatureSupported;

        // Contains information of Audio Messaging support
        TBool iAudioMessagingFeatureSupported;

        // Title pane text.
        HBufC* iTitleText;

        // Tapping offset.
        TPoint iTappingOffset;

        // Current thumb position in scrollbar.
        TInt iThumbPos;

        // Rows used in viewer.
        TInt iRows;
        
        CItemFinderExtension*	iExtension;

    public: // new methods
        void DeleteMeL();
        static TInt DeleteMe(TAny* aThis);

    private: // new methods
        void FormatDialDataL( TInt aCommandId );
        TBool IsSendKeyCallVoIP() const;

};

#endif  // FINDITEMDIALOG_H

// End of File
