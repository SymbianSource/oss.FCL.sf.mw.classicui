/*
* Copyright (c) 2002 - 2006 Nokia Corporation and/or its subsidiary(-ies).
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
*
*/


#if !defined(__AKNMESSAGEQUERYDIALOG_H__)
#define __AKNMESSAGEQUERYDIALOG_H__

#include <AknQueryDialog.h>
class CEikImage;
class CAknMessageQueryDialogExtension;

_LIT( KOpeningLinkTag, "<AknMessageQuery Link>" );
_LIT( KClosingLinkTag, "</AknMessageQuery Link>" );
_LIT( KOpeningBoldTag, "<AknMessageQuery Bold>" );
_LIT( KClosingBoldTag, "</AknMessageQuery Bold>" );


/** 
 * Message query dialog. 
 *
 * The dialog contains text that can be scrolled page by page.
 * 
 * If you want to use links and/or bold text among message you
 * must use @c SetMessageTextL method. Formatting text does not
 * work through resource file. If there are incorrect/misplaced
 * tags or tags are within each other, dialog will leave.
 */
class CAknMessageQueryDialog : public CAknQueryDialog
    {

public:

    /** 
     * Two-phased constructor.
     *
     * @param aMessage Text for the dialog.
     * @param aTone=ENoTone Tone played by the dialog.
     */
    IMPORT_C static CAknMessageQueryDialog* NewL(TDesC& aMessage, 
                                        const TTone& aTone = ENoTone);

    /**
     * Destructor.
     */
    IMPORT_C ~CAknMessageQueryDialog();

    /**
     * C++ default constructor.
     *
     * @param aTone Tone played with the dialog.
     */
    IMPORT_C CAknMessageQueryDialog(const TTone aTone);

public:

    /**
     * Sets message text. If you have links in your message you can mark 
     * link texts between tags @c <AknMessageQuery Link> and 
     * @c </AknMessageQuery Link> in the message text. For links see also @c SetLink.
     * Bold text can be achieved using tags @c <AknMessageQuery Bold> and @c </AknMessageQuery Bold>
     * 
     * @param aMessage Message text inside query. Insert '\\n' to get new line. 
     */
    IMPORT_C void SetMessageTextL(const TDesC& aMessage);

    /**
     * Sets header text.
     *
     * @param aHeader Message query header text
     * @deprecated - use @c Heading() + @c CAknPopupHeadingPane API instead
     */
    IMPORT_C void SetHeaderTextL(const TDesC& aHeader);  

    /**
     * @deprecated - use tags within text instead. 
     *
     * Changes the first occurance of @c aLinkText to a link
     * within the Message. If you have many links with the same name,
     * the method will set the links in the order you call them.
     * Before you set a new link you have to bind the 
     * previous one with a callback by calling @c SetLink() function. 
     *
     * Note that you don't have to call this function if you have already 
     * marked your links between tags @c <AknMessageQuery Link> and 
     * @c </AknMessageQuery Link> in the Message. In that
     * case only @c SetLink() method is used.
     *
     * @since S60 2.8
     * @param aLinkText Link text inside message.
     */
    IMPORT_C void SetLinkTextL(const TDesC& aLinkText);

    /**
     * Binds a callback to your link so that the dialog knows 
     * which callback to call when a link is activated by the user.
     *
     * @since S60 2.8
     * @param aCallBack Points to function which is executed when a link is 
     *        activated by a user.
     */
    IMPORT_C void SetLink(TCallBack& aCallBack);

public: // from CCoeControl

    /** 
     * From @c CCoeControl.
     *
     * Handles key events.
     * 
     * If a control wishes to process key events, it should implement this
     * function. The implementation must ensure that the function returns 
     * @c EKeyWasNotConsumed if it does not do anything in response to a 
     * key event, otherwise, other controls or dialogs may be prevented 
     * from receiving the key event. If it is able to process the event it 
     * should return @c EKeyWasConsumed.
     * 
     * @param aKeyEvent The key event. 
     * @param aType The type of key event: @c EEventKey, @c EEventKeyUp or 
     *        @c EEventKeyDown. 
     * @return Indicates whether or not the key event was used
     *         by this control. 
     */
    IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, 
                                         TEventCode);

    /**
     * From @c CCoeControl.
     *
     * Handles pointer events
     *
     * @param aPointerEvent The pointer event.
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent); 

protected: // from CEikDialog

    /** 
     * From @c CEikDialog.
     *
     * Should be derived to perform pre-layout dialog initialisation. 
     *
     * This function is called by the dialog framework before the dialog 
     * is sized and laid out. It may be overloaded to initialise the control
     * values that should influence sizing and layout, the default 
     * implementation is empty.
     */ 
    IMPORT_C virtual void PreLayoutDynInitL();
    
    /** 
     * From @c CEikDialog
     *
     * Sets the size and position of the dialog.
     *
     * Positions the dialog in the centre of the screen by default.
     *
     * @param aSize Not used.
     */ 
    IMPORT_C virtual void SetSizeAndPosition(const TSize& aSize);
    
    /** 
     * From @c CEikDialog
     * 
     * Not implemented.
     */ 
    IMPORT_C virtual void PostLayoutDynInitL();

private:

    /**
     * If the dialog does not have an extension create one.
     *
     * @since S60 2.8
     */
    void CreateExtensionL();

    /**
     * Register/Unregister an observer to extendedinputcapabilities. 
     * Registering is done so that we can receive pointer events from edwin. 
     *
     * @param aRegister, if true then registering, in other case unregister
     * @since S60 3.2
     */
    void RegisterPointerEventObserver( TBool aRegister ); 
    
    /**
     * @since S60 3.0
     * With multiple link support 
     */
    TInt CountLinks() const;         
    TBool SetNextLinkTextLocationL(const TDesC* aLinkText);     // for the non-marked links
    
    void ParseMessageTxtL();
    TBool GetNextTagL(TMsgQueryTag& aTag);
    void SetMsgFormattingL(TMsgQueryTag aTag);
    TBool TaggedMessageL();
    TInt LinksInArray();
    TInt LastLinkInArray();
       
    /**
    * Execute the current link. The link is dehighlighted after the execution.
    * @return ETrue if the link was executed successfully. EFalse if no link
    * is selected or there is no control object.
    */
    TBool ExecuteLinkL();
      
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private: 
    IMPORT_C virtual void CEikDialog_Reserved_1();
    IMPORT_C virtual void CEikDialog_Reserved_2();  
private: 
    IMPORT_C virtual void CAknDialog_Reserved();
private:
    IMPORT_C virtual void CAknQueryDialog_Reserved();
private:
    TDesC* iMessage;
    TDesC* iHeader;
    CEikImage* iHeaderImage;
    // Moved to iMsgQueryExtension
    // TInt iAnimationId;
    CAknMessageQueryDialogExtension * iMsgQueryExtension;
    

public:

    /**
     * From @c MEikCommandObserver. 
     *
     * Acts on the menu selection if menu is showing - pass on to client if 
     * not processed here.
     *
     * Responds to @c EAknSoftkeyView and @c EAknSoftkeyEmpty commands. 
     *
     * @since S60 3.0 
     */
    IMPORT_C virtual void ProcessCommandL( TInt aCommandId );
    
    /**
     * Checks if a link is tapped. If yes and the pointer event was of type 
     * TPointerEvent::EButton1Up, then calls the callback for the tapped link. 
     * 
     * @param aParams information on the position tapped and the pointer event
     * @since S60 3.2
     */
    void CheckLinkTappedL( TAny* aParams ); 


public:

    /**
     * C++ default constructor.
     *
     * @param aMessage Dialog box text.
     * @param aHeader Header for the dialog.
     * @deprecated 
     */ 
    IMPORT_C CAknMessageQueryDialog(TDesC* aMessage, TDesC* aHeader); 

    /**
     * C++ default constructor.
     *
     * @param aMessage Dialog box text.
     * @param aHeader Header for the dialog.
     * @param aHeaderImage Image to be inserted to the header.
     * @deprecated
     */ 
    IMPORT_C CAknMessageQueryDialog(TDesC* aMessage, 
                                    TDesC* aHeader, 
                                    CEikImage *aHeaderImage); 

    /**
     * C++ default constructor.
     *
     * @param aMessage Dialog box text.
     * @param aHeader Header for the dialog.
     * @param aTone Tone for the dialog. 
     * @deprecated
     */ 
    IMPORT_C CAknMessageQueryDialog(TDesC* aMessage, 
                                    TDesC* aHeader, 
                                    const TTone aTone); 

    /**
     * C++ default constructor.
     *
     * @param aMessage Dialog box text.
     * @param aHeader Header for the dialog.
     * @param aHeaderImage Image to be used in the header. 
     * @param aTone Ton for the dialog.
     * @deprecated
     */ 
    IMPORT_C CAknMessageQueryDialog(TDesC* aMessage, 
                                    TDesC* aHeader, 
                                    CEikImage *aHeaderImage, 
                                    const TTone aTone); 
    
    /** 
     * Sets the dialogs texts. 
     *
     * @param aMessage Text to be inserter into the dialog. 
     * @deprecated
     */
    IMPORT_C void SetMessageText(TDesC* aMessage); 
    
    /** 
     * Sets the dialogs texts. 
     *
     * @deprecated
     * @param aMessage Text to be inserter into the dialog. 
     */
    IMPORT_C void SetMessageText(const TDesC& aMessage);

    /** 
     * Sets the dialogs header texts. 
     *
     * @param aHeader Text to be inserter into the dialogs header. 
     * @deprecated
     */
    IMPORT_C void SetHeaderText(TDesC* aHeader);  

    /** 
     * Sets the dialogs header texts. 
     *
     * @param aHeader Text to be inserter into the dialogs header. 
     * @deprecated
     */
    IMPORT_C void SetHeaderText(const TDesC& aHeader);  
    
    /** Update softkey labels depending on whether any link is highlighted.
     * If a link is highlighted, the labels change to "View - <Empty>".
     * If no link i highlighted, the labels change to their previous values ( Ok - Cancel ).
     */
    void UpdateSoftkeyLabels();

    /** 
     * C++ default constructor.
     *
     * @deprecated
     */
    IMPORT_C CAknMessageQueryDialog();
        
    };


#endif // __AKNMESSAGEQUERYDIALOG_H__

//  End of File  
