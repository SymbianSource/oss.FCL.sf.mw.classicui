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
*/


// INCLUDE FILES
#include <eikimage.h>
#include <eikcapc.h>

#include <avkon.rsg>

#include <avkon.hrh>
#include <aknappui.h>
#include <aknextendedinputcapabilities.h>

#include "aknPopupHeadingPane.h"
#include "aknconsts.h"
#include "aknborders.h"
#include "AknUtils.h"

#include "aknmessagequerycontrol.h"
#include "aknmessagequerydialog.h"

#include <applayout.cdl.h>
#include <layoutmetadata.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <touchfeedback.h>

#include <AknTasHook.h> // for testability hooks
#include "AknHeadingPaneTouchObserver.h"


// CONSTANTS
const TInt KMaxLinks = 64;

const TInt KLinkStartTagLength = 22;
const TInt KLinkEndTagLength = 23;
const TInt KBoldStartTagLength = 22;
const TInt KBoldEndTagLength = 23;


class CAknMessageQueryDialogExtension : public CBase, public CAknExtendedInputCapabilities::MAknEventObserver,
                                        public MAknHeadingPaneTouchObserver
    {
public:
    CAknMessageQueryDialogExtension( CAknMessageQueryDialog* aParent  ) : iParent(aParent),
                                                                          iControlRegisted( EFalse ) {}
    ~CAknMessageQueryDialogExtension()
        {       
        TInt count = iFormatTextArray.Count();
        for ( TInt i = 0; i < count; i++ )
            {
            delete iFormatTextArray[i];        
            }
        iCallBackArray.Close();
        iFormatTextLocationArray.Close();
        iFormatTextArray.Close();
        iFormatTypeArray.Close();
        
        if ( iDestroyedPtr )
            {
            // Mark the object as destroyed.
            *iDestroyedPtr = ETrue;
            iDestroyedPtr = NULL;
            }
        }
            
    /** From CAknExtendedInputCapabilities::MAknEventObserver
    */
    void HandleInputCapabilitiesEventL( TInt aEvent, TAny* aParams ) 
        {
        if ( aEvent == CAknExtendedInputCapabilities::MAknEventObserver::EPointerEventReceived )
            {
            iParent->CheckLinkTappedL(aParams); 
            }   
        }
        
    /**
    * From MAknHeadingPaneTouchObserver
    * Processes heading pane pointer events. On the pen down events, any link is dehighlighted.
    */
    void HandleHeadingPanePointerEventL( CAknPopupHeadingPane* /*aHeadingPane*/, const TPointerEvent& aPointerEvent )
        {
        if( aPointerEvent.iType == TPointerEvent::EButton1Down && iCtrl )
            {
            iCtrl->DehighlightLink();
            }
        }

public:
    
    TInt iAnimationId;
        
    RArray<TCallBack> iCallBackArray;
    RArray<TInt> iFormatTextLocationArray;
    RArray<TDesC*> iFormatTextArray;
    RArray<TMsgQueryTag> iFormatTypeArray;
        
    TInt iLinkCount; // values between 0 and KMaxLinks-1
    TBool iMarkedLinks;
    TInt iButtonGroupPreviouslyChanged;
    CAknMessageQueryDialog* iParent;
    TBool iControlRegisted; 
    CAknMessageQueryControl* iCtrl;
    
    /**
    * @c iDestroyedPtr is used for the object destruction check.
    * If it has non-null value, the destruction check is turned on, and
    * the value points to a local boolean variable that keeps the destroyed state.
    */
    TBool* iDestroyedPtr;
    TBool iIsInEditor;
    };
    

EXPORT_C CAknMessageQueryDialog* CAknMessageQueryDialog::NewL( TDesC& aMessage, const TTone& aTone )
    {
    CAknMessageQueryDialog* self = new ( ELeave ) CAknMessageQueryDialog( aTone );
    CleanupStack::PushL( self );
    self->SetMessageTextL( aMessage );
    CleanupStack::Pop(); //self
    AKNTASHOOK_ADDL( self, "CAknMessageQueryDialog" );
    return self;
    }

//@deprecated
EXPORT_C CAknMessageQueryDialog::CAknMessageQueryDialog() : CAknQueryDialog( ENoTone )
    {
#ifndef RD_NO_DIALOG_BORDERS
    iBorder = AknBorderId::EAknBorderNotePopup;
#else
    iBorder = TGulBorder::ENone;
#endif
    }

EXPORT_C CAknMessageQueryDialog::CAknMessageQueryDialog( const TTone aTone ) : CAknQueryDialog( aTone )
    {
#ifndef RD_NO_DIALOG_BORDERS
    iBorder = AknBorderId::EAknBorderNotePopup;
#else
    iBorder = TGulBorder::ENone;
#endif
    }

//@deprecated
EXPORT_C CAknMessageQueryDialog::CAknMessageQueryDialog( TDesC* aMessage, TDesC* aHeader ) 
    : CAknQueryDialog( ENoTone ), iMessage( aMessage ), iHeader( aHeader )
    {
#ifndef RD_NO_DIALOG_BORDERS
    iBorder = AknBorderId::EAknBorderNotePopup;
#else
    iBorder = TGulBorder::ENone;
#endif
    }

//@deprecated
EXPORT_C CAknMessageQueryDialog::CAknMessageQueryDialog( TDesC* aMessage, TDesC* aHeader, CEikImage *aHeaderImage )
    : CAknQueryDialog( ENoTone ), iMessage( aMessage ), iHeader( aHeader ), iHeaderImage( aHeaderImage )
    {
#ifndef RD_NO_DIALOG_BORDERS
    iBorder = AknBorderId::EAknBorderNotePopup;
#else
    iBorder = TGulBorder::ENone;
#endif
    }

//@deprecated
EXPORT_C CAknMessageQueryDialog::CAknMessageQueryDialog( TDesC* aMessage, TDesC* aHeader, const TTone aTone )
    : CAknQueryDialog( aTone ), iMessage( aMessage ), iHeader( aHeader )
    {
#ifndef RD_NO_DIALOG_BORDERS
    iBorder = AknBorderId::EAknBorderNotePopup;
#else
    iBorder = TGulBorder::ENone;
#endif
    }

//@deprecated
EXPORT_C CAknMessageQueryDialog::CAknMessageQueryDialog( TDesC* aMessage, TDesC* aHeader, CEikImage *aHeaderImage, const TTone aTone )
    : CAknQueryDialog( aTone ), iMessage( aMessage ), iHeader( aHeader ), iHeaderImage( aHeaderImage )
    {
#ifndef RD_NO_DIALOG_BORDERS
    iBorder = AknBorderId::EAknBorderNotePopup;
#else
    iBorder = TGulBorder::ENone;
#endif
    }

EXPORT_C CAknMessageQueryDialog::~CAknMessageQueryDialog()
    {
    AKNTASHOOK_REMOVE();
    delete iMessage;
    delete iHeader;
    delete iHeaderImage;
    RegisterPointerEventObserver( EFalse ); 
    delete iMsgQueryExtension;
    }

EXPORT_C void CAknMessageQueryDialog::SetMessageTextL( const TDesC& aMessage )
    {
    delete iMessage;
    iMessage = NULL;
    iMessage = aMessage.AllocL();
    }

EXPORT_C void CAknMessageQueryDialog::SetLinkTextL( const TDesC& aLinkText )
    {
    if ( !iMsgQueryExtension )
        {
        CreateExtensionL();
        }

    if ( iMsgQueryExtension->iMarkedLinks ) 
        {
        return;            
        }
    else if ( iMsgQueryExtension->iLinkCount < KMaxLinks ) 
        {        
        if ( LinksInArray() > iMsgQueryExtension->iLinkCount )
            {
            // SetLinkText is already set and method resets it
            TInt lastIndex = LastLinkInArray();
            if (lastIndex == -1)
                {
                return; //something went wrong - go away
                }
            iMsgQueryExtension->iFormatTextArray[lastIndex] = aLinkText.AllocL();
            }
        else
            {
            // SetLinkTextL creates new callback in the callback array for the new link
            iMsgQueryExtension->iFormatTextArray.Append( aLinkText.AllocL() );
            iMsgQueryExtension->iFormatTypeArray.Append( EMsgQueryLink );
               
            // If the other method SetLink has been already called 
            // the new link is finished by adding the link count
            if ( iMsgQueryExtension->iCallBackArray.Count() > iMsgQueryExtension->iLinkCount )
                {
                iMsgQueryExtension->iLinkCount++;                                            
                }                
            }
        }
    }

EXPORT_C void CAknMessageQueryDialog::SetLink( TCallBack& aCallBack )
    {
    if ( !iMsgQueryExtension )
        {
        TRAPD( Err, CreateExtensionL() );
        if ( Err != KErrNone )
            {
            return;
            }
        }
           
    if ( !iMsgQueryExtension->iMarkedLinks && iMessage )
        {
        TInt index = iMessage->Find( KOpeningLinkTag );
        
        if ( index != KErrNotFound ) 
            {
            iMsgQueryExtension->iMarkedLinks = ETrue;
            }
        else 
            {
            iMsgQueryExtension->iMarkedLinks = EFalse;
            }
        iMsgQueryExtension->iLinkCount = CountLinks();
        }
        
    if ( iMsgQueryExtension->iMarkedLinks )
        {
        if ( iMsgQueryExtension->iCallBackArray.Count() < iMsgQueryExtension->iLinkCount )
            {
            // SetLink creates new callback in the callback array for the new link
            iMsgQueryExtension->iCallBackArray.Append( aCallBack );                
            }
        }         
    else if ( iMsgQueryExtension->iLinkCount < KMaxLinks ) 
        {
        if ( iMsgQueryExtension->iCallBackArray.Count() > iMsgQueryExtension->iLinkCount ) 
            {
            // SetLink is already set and method resets it
            iMsgQueryExtension->iCallBackArray[iMsgQueryExtension->iCallBackArray.Count()-1] = aCallBack;            
            }
        else
            {
            // SetLink creates new callback in the callback array for the new link
            iMsgQueryExtension->iCallBackArray.Append( aCallBack );
                
            // If the other method SetLinkText has been already called 
            // the new link is finished by adding the link count
            
            if ( LinksInArray() > iMsgQueryExtension->iLinkCount )                        
                {
                iMsgQueryExtension->iLinkCount++;                                            
                }                
            }
        }
    }


/**
 * @deprecated and will be removed - Use SetMessageTextL instead
 */
EXPORT_C void CAknMessageQueryDialog::SetMessageText( const TDesC& aMessage )
    {
    TRAP_IGNORE( SetMessageTextL( aMessage ) );
    }

/**
 * @deprecated - use Heading() + CAknPopupHeadingPane API
 */
EXPORT_C void CAknMessageQueryDialog::SetHeaderTextL( const TDesC& aHeader )
    {
    delete iHeader;
    iHeader = NULL;
    iHeader = aHeader.AllocL();
    }

/**
 * @deprecated and will be removed - Use SetHeaderTextL instead
 */
EXPORT_C void CAknMessageQueryDialog::SetHeaderText( const TDesC& aHeader )
    {
    TRAP_IGNORE( SetHeaderTextL( aHeader ) );
    }

//@deprecated
EXPORT_C void CAknMessageQueryDialog::SetMessageText( TDesC* aMessage )
    {
    delete iMessage;
    iMessage = aMessage;
    }

//@deprecated
EXPORT_C void CAknMessageQueryDialog::SetHeaderText( TDesC* aHeader )
    {
    delete iHeader;
    iHeader = aHeader;
    }

EXPORT_C void CAknMessageQueryDialog::PreLayoutDynInitL()
    {
    if ( !iMsgQueryExtension )
        {
        CreateExtensionL();
        }      
        
    //old style with no tags
    if ( iMessage && iMsgQueryExtension )
        {
        if ( !iMsgQueryExtension->iMarkedLinks && iMsgQueryExtension->iLinkCount >0  )
            {
            for ( TInt count = 0; count < iMsgQueryExtension->iLinkCount; count++ )
                {
                if ( !SetNextLinkTextLocationL( iMsgQueryExtension->iFormatTextArray[count] ) ) 
                    {
                    break;
                    }
                }
            }
        else if ( TaggedMessageL() )
            {      
            iMsgQueryExtension->iMarkedLinks = ETrue;
            ParseMessageTxtL();
            }          
        }
    
    SetLineNonFocusing( EAknMessageQueryHeaderId );  
        
    CAknMessageQueryControl* msgCtrl = STATIC_CAST( CAknMessageQueryControl*, Control( EAknMessageQueryContentId ) );

    if ( iMsgQueryExtension )
        {
        iMsgQueryExtension->iCtrl = msgCtrl;
        }
    
    if ( iMessage && iMsgQueryExtension )
        {
        msgCtrl->SetMessageTextWithFormattingL( iMessage, &iMsgQueryExtension->iFormatTextArray, &iMsgQueryExtension->iFormatTextLocationArray, &iMsgQueryExtension->iFormatTypeArray );
        RegisterPointerEventObserver( ETrue ); 
        }    
    else if ( iMessage )
        {
        msgCtrl->SetMessageTextL( iMessage );
        }
    
    msgCtrl->SetMopParent( this );
    delete iMessage;
    iMessage = NULL;

    CAknPopupHeadingPane* headingPane = STATIC_CAST( CAknPopupHeadingPane*, Control( EAknMessageQueryHeaderId ) );
    if ( iHeader )
        {
        headingPane->SetTextL( *iHeader );
        delete iHeader;
        iHeader = NULL;
        }
        
    if ( iMsgQueryExtension && iMsgQueryExtension->iAnimationId > 0 )
        {
        headingPane->SetHeaderAnimationL( iMsgQueryExtension->iAnimationId );
        }
    else if ( iHeaderImage )
        {
        headingPane->SetHeaderImageL( iHeaderImage );
        }
        
    if (headingPane)
        {
        headingPane->SetLayout(CAknPopupHeadingPane::EMessageQueryHeadingPane); // Use message query heading layout.    
        headingPane->SetTouchObserver( iMsgQueryExtension );
        }
    }

   
EXPORT_C void CAknMessageQueryDialog::SetSizeAndPosition( const TSize& aSize )
    {
    if ( AknLayoutUtils::PenEnabled() )
        {
        // Ideally line below would be replaced with base class call. However
        // CAknQueryDialog's functionality relies on method
        // CAknQueryDialog::QueryControl that doesn't return message query
        // control -> dialog's size won't be set in the base class.
        SetRect( TRect( AknPopupUtils::Position( aSize, this ), aSize ) ); 
        }
    else
        {
        TAknLayoutRect dialogLayout;
        
        CAknMessageQueryControl* messageQueryControl =
            STATIC_CAST( CAknMessageQueryControl*,
                Control( EAknMessageQueryContentId ) );
        
        TInt numberOfLines = messageQueryControl->Lines();
        
        // Number of rows that fits to the dialog
        const TInt rowsPerPage =
            AknLayoutScalable_Avkon::popup_info_list_pane_t1_ParamLimits().
                LastRow() + 1;
        
        numberOfLines =
            numberOfLines > rowsPerPage ? rowsPerPage : numberOfLines;
        numberOfLines--;
        if ( numberOfLines < 0 ) 
            {
            numberOfLines = 0;    
            }

        TRect mainPane;
        AknLayoutUtils::LayoutMetricsRect(
            AknLayoutUtils::EPopupParent, mainPane );
            
        TInt variety = 0;
        AknLayoutUtils::TAknCbaLocation cbaLocation =
            AknLayoutUtils::CbaLocation();
        
        if (cbaLocation == AknLayoutUtils::EAknCbaLocationRight)
            { // Variety numbers for right CBA are 6-11
            variety = numberOfLines + 6;
            }
        else if (cbaLocation == AknLayoutUtils::EAknCbaLocationLeft)
            { // Variety numbers for left CBA are 12-17
            variety = numberOfLines + 12;
            }
        else // bottom
            {
            variety = numberOfLines;
            }

        dialogLayout.LayoutRect(mainPane,
            AknLayoutScalable_Avkon::popup_query_sat_info_window( variety ) );
        TRect dialogRect( dialogLayout.Rect() );
        if( QueryHeading()->PromptText() == KNullDesC )
            {
            TAknLayoutRect headingPaneLayout;
            headingPaneLayout.LayoutRect(dialogRect,
                AknLayoutScalable_Avkon::heading_pane_cp5() );
            dialogRect.iTl.iY += headingPaneLayout.Rect().Height();
            }
        // No Dialog borders in message queries
        SetBorder( TGulBorder::ENone ); 
        SetRect( dialogRect ); 
        }
    }
   

EXPORT_C void CAknMessageQueryDialog::PostLayoutDynInitL()
    {
    }


EXPORT_C TKeyResponse CAknMessageQueryDialog::OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aModifiers )
    {
    
    TInt code=aKeyEvent.iCode;

    switch ( code )
        {
        case EKeyUpArrow:
        case EKeyDownArrow:
            {
            CAknMessageQueryControl* messageQueryControl = STATIC_CAST( CAknMessageQueryControl*, Control( EAknMessageQueryContentId ) );
            if ( messageQueryControl )
                {
                TKeyResponse answer = messageQueryControl->OfferKeyEventL( aKeyEvent, aModifiers );   
                if ( answer == EKeyWasConsumed && iMsgQueryExtension )
                    {
                    UpdateSoftkeyLabels();
                    }
                return answer;  
                }
            }
            break;      
        case EKeyEnter:
        case EKeyOK:    
            {
            if ( iMsgQueryExtension && iMsgQueryExtension->iLinkCount > 0 )
                {
                if( ExecuteLinkL() )
                    return EKeyWasConsumed;
                }
            TryExitL(EEikBidOk);
            return EKeyWasConsumed;
            }

        default:
            break;
        }
    return CAknQueryDialog::OfferKeyEventL( aKeyEvent, aModifiers );
    }
    
    
/**
 *From MEikCommandObserver (act on the menu selection if menu is showing - pass on to client if not processed here)
 */
EXPORT_C void CAknMessageQueryDialog::ProcessCommandL(TInt aCommandId)
    {
    CAknDialog::ProcessCommandL(aCommandId);    
    
    // Respond to softkey event
    switch (aCommandId)
        {
        case EAknSoftkeyView:
            {
            if ( iMsgQueryExtension && iMsgQueryExtension->iLinkCount > 0 )
                {
                if( ExecuteLinkL() )
                    return;
                }
            }
            break;
        case EAknSoftkeyEmpty: // SoftkeyEmpty also comes to this observer, but is ingnored
        default:
            break;
        }   
    }


TInt CAknMessageQueryDialog::CountLinks() const 
    {
    if ( iMsgQueryExtension->iLinkCount > 0 ) 
        {
        return iMsgQueryExtension->iLinkCount;    
        }
    // TInt previouslySearched = 0;
    TInt index = 0;
    TInt count = -1;
    TPtrC clippedTextOut = iMessage->Mid( 0 );
    TPtrC clippedTextIn = clippedTextOut.Mid( 0 );        
    while ( index != KErrNotFound )
        {
        count++;
        index = clippedTextOut.Find( KOpeningLinkTag );            
        clippedTextOut.Set( clippedTextIn.Mid( index+1 ) );
        clippedTextIn.Set( clippedTextOut.Mid( 0 ) );
        }    
    return count;
    }    

TBool CAknMessageQueryDialog::SetNextLinkTextLocationL( const TDesC* aLinkText )
    {        
    TInt linkTextLocation = 0;
    TInt previouslySearched = 0;
    if ( iMessage && iMessage->Length() > 0 && aLinkText->Length() > 0 )
        {
        HBufC* messageBuf = iMessage->AllocL();
        if ( messageBuf )
            {
            TPtrC clippedMessageTextOld = iMessage->Mid( 0 ); // pointer to the descriptor data                
            TPtrC clippedMessageTextNew = clippedMessageTextOld; 
            linkTextLocation = clippedMessageTextNew.Find( *aLinkText );          
            if ( linkTextLocation != KErrNotFound ) 
                {            
                while ( iMsgQueryExtension->iFormatTextLocationArray.Find( linkTextLocation ) != KErrNotFound )
                    {
                    previouslySearched += linkTextLocation+1;
                    clippedMessageTextNew.Set( clippedMessageTextOld.Mid( linkTextLocation+1 ) );
                    clippedMessageTextOld.Set( clippedMessageTextNew.Mid( 0 ) );
                    linkTextLocation = clippedMessageTextNew.Find( *aLinkText );                    
                    if ( linkTextLocation == KErrNotFound ) 
                        {
                        return EFalse;    
                        }
                    }
                linkTextLocation += previouslySearched;
                }
            else 
                {
                return EFalse;                    
                }
            }
        delete messageBuf;
        }      
     iMsgQueryExtension->iFormatTextLocationArray.Append( linkTextLocation );         
     return ETrue;
    }
    
void CAknMessageQueryDialog::CreateExtensionL()
    {
    if ( !iMsgQueryExtension )
        {
        iMsgQueryExtension = new ( ELeave ) CAknMessageQueryDialogExtension(this);
        }
    }
    
void CAknMessageQueryDialog::ParseMessageTxtL()
    {
    if ( iMessage && iMessage->Length() > 0 )
        {
        TMsgQueryTag tag;        

        while (GetNextTagL(tag))
            {
            SetMsgFormattingL(tag);
            }            
        }
    }
    
void CAknMessageQueryDialog::SetMsgFormattingL(TMsgQueryTag aTag)
    {
    TInt openingTag = KErrNotFound;
    TInt closingTag = KErrNotFound;
    TInt startLength = 0;
    TInt endLength = 0;
    
    if (aTag == EMsgQueryLink)
        {
        openingTag = iMessage->Find( KOpeningLinkTag );
        closingTag = iMessage->Find( KClosingLinkTag );
        startLength = KLinkStartTagLength;
        endLength = KLinkEndTagLength;                
        }
    else if (aTag == EMsgQueryBold)
        {
        openingTag = iMessage->Find( KOpeningBoldTag );
        closingTag = iMessage->Find( KClosingBoldTag );
        startLength = KBoldStartTagLength;
        endLength = KBoldEndTagLength;                
        }
    else User::Leave(KErrCorrupt);
                   
    HBufC* messageBuf = iMessage->AllocL();    
    TPtr message = messageBuf->Des();
                
    message.Delete( closingTag, endLength );
    message.Delete( openingTag, startLength );

    iMsgQueryExtension->iFormatTextArray.Append( message.MidTPtr( openingTag, closingTag - openingTag - startLength ).AllocL() );
    iMsgQueryExtension->iFormatTextLocationArray.Append( openingTag );
    iMsgQueryExtension->iFormatTypeArray.Append( aTag );
    delete iMessage;
    iMessage = messageBuf;        
    }    
                
TBool CAknMessageQueryDialog::GetNextTagL(TMsgQueryTag& aTag)
    {
    TInt indexLinkStart = iMessage->Find( KOpeningLinkTag );
    TInt indexLinkEnd = iMessage->Find( KClosingLinkTag );
    TInt indexBoldStart = iMessage->Find( KOpeningBoldTag );
    TInt indexBoldEnd = iMessage->Find( KClosingBoldTag );
    
    //no tags found
    if (indexLinkStart == KErrNotFound && indexLinkEnd == KErrNotFound && indexBoldStart == KErrNotFound && indexBoldEnd == KErrNotFound)
        {
        return EFalse;
        }

    //start tag found without end tag or vice versa
    if ((indexLinkStart != KErrNotFound && indexLinkEnd == KErrNotFound) || (indexLinkStart == KErrNotFound && indexLinkEnd!= KErrNotFound))
        {
        User::Leave(KErrCorrupt);
        }
    if ((indexBoldStart!= KErrNotFound && indexBoldEnd == KErrNotFound) || (indexBoldStart == KErrNotFound && indexBoldEnd!= KErrNotFound))
        {
        User::Leave(KErrCorrupt);
        } 
        
    //tags in incorrect order
    if ( indexLinkStart != KErrNotFound && indexLinkStart > indexLinkEnd)
        {
        User::Leave(KErrCorrupt);
        }
    if (indexBoldStart != KErrNotFound && indexBoldStart > indexBoldEnd)
        {
        User::Leave(KErrCorrupt);
        }

    //link tags & no bold tags
    if (indexBoldStart == KErrNotFound)
        {
        aTag = EMsgQueryLink;
        return ETrue;
        }
    //bold tags & no link tags
    else if (indexLinkStart == KErrNotFound)
        {
        aTag = EMsgQueryBold;
        return ETrue;
        }
        
    //next tag pair is link start & link end
    if (indexLinkStart < indexBoldStart && indexLinkStart < indexBoldEnd
            && indexLinkEnd < indexBoldStart && indexLinkEnd < indexBoldEnd)
        {
        aTag = EMsgQueryLink;
        return ETrue;
        }
    //next tag pair is bold start & bold end
    else if (indexBoldStart < indexLinkStart && indexBoldStart < indexLinkEnd
            && indexBoldEnd < indexLinkStart && indexBoldEnd < indexLinkEnd)
        {
        aTag = EMsgQueryBold;
        return ETrue;
        }
    //there are bold & link tags within each other - not permitted
    else
        {
        User::Leave(KErrCorrupt);
        }

    //should never get here   
    return EFalse;
    }      
    
TBool CAknMessageQueryDialog::TaggedMessageL()       
    {       
    if (iMessage->Find(KOpeningLinkTag) != KErrNotFound) return ETrue;
    if (iMessage->Find(KOpeningBoldTag) != KErrNotFound) return ETrue;    
    if (iMessage->Find(KClosingLinkTag) != KErrNotFound) return ETrue;    
    if (iMessage->Find(KClosingBoldTag) != KErrNotFound) return ETrue;
    
    return EFalse;
    }
    
    
TInt CAknMessageQueryDialog::LinksInArray()       
    {
    if (!iMsgQueryExtension) 
        {
        return 0;
        }
        
    TInt linkCount = 0;    
    for ( TInt count = 0; count < iMsgQueryExtension->iFormatTypeArray.Count(); count++ )
        {
        if (iMsgQueryExtension->iFormatTypeArray[count] == EMsgQueryLink)
            {
            linkCount++;
            }
        }
    return linkCount;
    }
    
    
TInt CAknMessageQueryDialog::LastLinkInArray()       
    {
    if (!iMsgQueryExtension) 
        {
        return -1;
        }
        
    TInt lastLinkIndex = -1;
    for ( TInt count = iMsgQueryExtension->iFormatTypeArray.Count(); count >= 0; count-- )
        {
        if (iMsgQueryExtension->iFormatTypeArray[count] == EMsgQueryLink)
            {
            lastLinkIndex = count;
            break;
            }
        }
    return lastLinkIndex;
    }                                  
    
EXPORT_C void CAknMessageQueryDialog::HandlePointerEventL( const TPointerEvent& aPointerEvent ) 
    { 
    CEikEdwin* edwin = NULL; 
    CAknMessageQueryControl* msgCtrl = static_cast<CAknMessageQueryControl*>( Control( EAknMessageQueryContentId ) );
    if( msgCtrl )
        {
        edwin = static_cast<CEikEdwin*>( msgCtrl->ComponentControl( 0 ) );
        }
    
    switch (aPointerEvent.iType)
        {
        case TPointerEvent::EButton1Down:
            {
            if ( edwin && ( edwin->Rect().Contains( aPointerEvent.iPosition ) ) )
                iMsgQueryExtension->iIsInEditor = ETrue;
            }
            break;
        case TPointerEvent::EButton1Up:
            {
            iMsgQueryExtension->iIsInEditor = EFalse;
            if (!Rect().Contains( aPointerEvent.iPosition) && msgCtrl)
                {
                msgCtrl->HandlePointerEventL(aPointerEvent);    
                }
            }
            break;
        case TPointerEvent::EDrag:
        case TPointerEvent::EButtonRepeat:
              {
              if ( !Rect().Contains( aPointerEvent.iPosition) && iMsgQueryExtension->iIsInEditor && edwin )
                  {
                  edwin->HandlePointerEventL(aPointerEvent);        
                  return;
                  }
              }
             break;
          default:
              break;
           
        }
    // This is a bit of a hack to support non window owning scroll bar.
    // CAknQueryDialog and CEikDialogPage will stop pointer event processing
    // if it occurs outside of the dialog area. If scroll bar has received
    // pointer down, hand pointer up to it regardless where it occurred.
    if (AknLayoutUtils::PenEnabled() &&
        aPointerEvent.iType != TPointerEvent::EButton1Down &&
        msgCtrl && msgCtrl->ScrollBarGrabbing())
        {
        msgCtrl->HandlePointerEventL(aPointerEvent);
        }
    else
        {
        CAknQueryDialog::HandlePointerEventL( aPointerEvent );
        }
    }

EXPORT_C void* CAknMessageQueryDialog::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

EXPORT_C void CAknMessageQueryDialog::CEikDialog_Reserved_1()
    {
    }

EXPORT_C void CAknMessageQueryDialog::CEikDialog_Reserved_2()
    {
    }

EXPORT_C void CAknMessageQueryDialog::CAknDialog_Reserved()
    {
    }

EXPORT_C void CAknMessageQueryDialog::CAknQueryDialog_Reserved()
    {
    }

void CAknMessageQueryDialog::CheckLinkTappedL( TAny* aParams )
    {
    if ( iMsgQueryExtension->iLinkCount <= 0 )
        {
        return; 
        }
    CAknExtendedInputCapabilities::MAknEventObserver::TPointerEventReceivedParams aInfo = 
        *((CAknExtendedInputCapabilities::MAknEventObserver::TPointerEventReceivedParams*)aParams); 
    CAknMessageQueryControl* messageQueryControl = STATIC_CAST( CAknMessageQueryControl*, Control( EAknMessageQueryContentId ) );

    if ( messageQueryControl )
        {
        TBool linkTapped = messageQueryControl->LinkTappedL( aInfo.iDocPos );
        
        if ( linkTapped && 
            aInfo.iPointerEvent.iType == TPointerEvent::EButton1Down )
            {
            MTouchFeedback* feedback = MTouchFeedback::Instance();
            if ( feedback )
                {
                feedback->InstantFeedback( this, ETouchFeedbackSensitive );            
                }
            }
        
        UpdateSoftkeyLabels();
        if( linkTapped && aInfo.iPointerEvent.iType == TPointerEvent::EButton1Up )
            {
            ExecuteLinkL();
            }
        }
    }

void CAknMessageQueryDialog::RegisterPointerEventObserver( TBool aRegister )
    {
    if( !iMsgQueryExtension || ( !aRegister && !iMsgQueryExtension->iControlRegisted  ) )
        {
        return;
        }
        
    CAknMessageQueryControl* msgCtrl = STATIC_CAST( CAknMessageQueryControl*, Control( EAknMessageQueryContentId ) );
    CEikEdwin* edwin = (CEikEdwin*)msgCtrl->ComponentControl( 0 ); 
        
    MObjectProvider* mop = edwin->InputCapabilities().ObjectProvider();
    
    if ( mop )
        {
        CAknExtendedInputCapabilities* extendedInputCapabilities = 
        mop->MopGetObject( extendedInputCapabilities );

        if ( extendedInputCapabilities ) 
            {
            if ( aRegister )
                {
                iMsgQueryExtension->iControlRegisted = ETrue;
                extendedInputCapabilities->RegisterObserver( iMsgQueryExtension );
                }
            else 
                {
                extendedInputCapabilities->UnregisterObserver( iMsgQueryExtension );                
                }
            }
        }
    }
    
void CAknMessageQueryDialog::UpdateSoftkeyLabels()
    {
    CAknMessageQueryControl* control = STATIC_CAST( CAknMessageQueryControl*, Control( EAknMessageQueryContentId ) );

    if ( control && control->LinkHighLighted() )
        {
        if ( !iMsgQueryExtension->iButtonGroupPreviouslyChanged ) 
            {   
            TRAP_IGNORE( ButtonGroupContainer().AddCommandSetToStackL( R_AVKON_SOFTKEYS_VIEW_EMPTY ) );
            TRAP_IGNORE( ButtonGroupContainer().UpdateCommandObserverL( CEikButtonGroupContainer::ELeftSoftkeyPosition, *this ) );
            TRAP_IGNORE( ButtonGroupContainer().UpdateCommandObserverL( CEikButtonGroupContainer::ERightSoftkeyPosition, *this ) );
            TRAP_IGNORE( ButtonGroupContainer().UpdateCommandObserverL( CEikButtonGroupContainer::EMiddleSoftkeyPosition, *this ) );
            ButtonGroupContainer().DrawNow();
            iMsgQueryExtension->iButtonGroupPreviouslyChanged = ETrue;
            }
         }
    else
        {
        if ( iMsgQueryExtension->iButtonGroupPreviouslyChanged ) 
            {                            
            ButtonGroupContainer().RemoveCommandObserver( CEikButtonGroupContainer::ELeftSoftkeyPosition );
            ButtonGroupContainer().RemoveCommandObserver( CEikButtonGroupContainer::ERightSoftkeyPosition );
            ButtonGroupContainer().RemoveCommandObserver( CEikButtonGroupContainer::EMiddleSoftkeyPosition );
            ButtonGroupContainer().RemoveCommandFromStack( CEikButtonGroupContainer::ELeftSoftkeyPosition, EAknSoftkeyView );
            ButtonGroupContainer().RemoveCommandFromStack( CEikButtonGroupContainer::ERightSoftkeyPosition, EAknSoftkeyEmpty );
            ButtonGroupContainer().RemoveCommandFromStack( CEikButtonGroupContainer::EMiddleSoftkeyPosition, EAknSoftkeyView );
            ButtonGroupContainer().DrawNow();
            iMsgQueryExtension->iButtonGroupPreviouslyChanged = EFalse; 
            }
        }
    }
    
/**
* CAknMessageQueryDialog::ExecuteLinkL() checks for the object destruction after
* the link execution.
*/    
    
TBool CAknMessageQueryDialog::ExecuteLinkL()
    {
    CAknMessageQueryControl* control = STATIC_CAST( CAknMessageQueryControl*, Control( EAknMessageQueryContentId ) );
    if( !control )
        {
        return EFalse;
        }
    if( !control->LinkHighLighted() )
        {
        return EFalse;
        }
    TInt curLink = control->CurrentLink();
    /**
    * The local @c destroyed variable keeps track of the object destroyed state.
    */
    TBool destroyed = EFalse;
    iMsgQueryExtension->iDestroyedPtr = &destroyed;
    TRAPD( err, iMsgQueryExtension->iCallBackArray[curLink].CallBack() );
    if ( !destroyed )
        {
        iMsgQueryExtension->iDestroyedPtr = NULL;
        }
    User::LeaveIfError( err );
    if ( !destroyed )
        {
        control->DehighlightLink();
        }
    return ETrue;
    }

//  End of File     
