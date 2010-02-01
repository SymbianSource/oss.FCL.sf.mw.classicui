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
* Description:  Plugin utility used for automatic tags ( http, email, phone numbers, URI schemes )
*                syntax highlighting in text viewers
*
*
*/


// INCLUDES
#include <eikrted.h>
#include <txtrich.h> // for CRichText
#include "ItemFinder.h"
#include <finditemengine.h>
#include <commonphoneparser.h>
#include <txtfrmat.h>
#include <AknUtils.h> // for AknUtils
#include <AknsUtils.h>

// scheme recog
#include <ecom/ecom.h>
#include <ecom/implementationinformation.h>

#include <centralrepository.h>
#include <CommonUiInternalCRKeys.h>

// CONSTANTS
const TInt KMINTAGLENGTH(5);
_LIT( KHTTPPREFIX, "http://");
_LIT( RTSP, "rtsp");
_LIT( KTELPREFIX, "tel:");

const TInt KItemFinderMinDigitsToFind = 5;
#define SCHEME_INTERFACE_DEF TUid( TUid::Uid(0x101f8534) ) // we don't want header dependency to browser utilities

NONSHARABLE_CLASS(CSchemeResolver): public CBase
    {
public:
    CSchemeResolver(){};
    static CSchemeResolver* NewL();
    inline CArrayPtrFlat<HBufC>& SupportedSchemes(){ return *iSupportedArray; };
    ~CSchemeResolver();
private:
    void ConstructL();
    CArrayPtrFlat<HBufC>* iSupportedArray;
    RImplInfoPtrArray iEcomInfoArray;
    };

CSchemeResolver* CSchemeResolver::NewL()
    {
    CSchemeResolver* me = new (ELeave) CSchemeResolver();
    CleanupStack::PushL( me );
    me->ConstructL();
    CleanupStack::Pop();
    return me;
    }

void CSchemeResolver::ConstructL()
    {
    //perform plugin scan
    iSupportedArray = new (ELeave) CArrayPtrFlat<HBufC>( 5 );
    REComSession::ListImplementationsL( SCHEME_INTERFACE_DEF, iEcomInfoArray );
    for ( TInt i = 0; i < iEcomInfoArray.Count() ; i++ )
        {
        HBufC* data = HBufC::NewLC( iEcomInfoArray[ i ]->DataType().Length() );
        data->Des().Copy( iEcomInfoArray[ i ]->DataType() );
        iSupportedArray->AppendL( data );
        CleanupStack::Pop();
        }
    iEcomInfoArray.ResetAndDestroy(); // we don't need this anymore
    }

CSchemeResolver::~CSchemeResolver()
    {
    iEcomInfoArray.ResetAndDestroy();
    if (iSupportedArray)
        {
        iSupportedArray->ResetAndDestroy();
        }
    delete iSupportedArray;
    }

NONSHARABLE_CLASS(CItemFinderAsyncParser): public CActive
    {
public:
    static CItemFinderAsyncParser* NewL( CEikRichTextEditor* aEditor, TInt* aFirstVisible, TInt aMinDigitsToFind );
    void SetCallbackObserver( CItemFinder* aObserver ){ iObserver = aObserver; };
    ~CItemFinderAsyncParser();
    void RunL();
    void DoCancel();
    CFindItemEngine* iFIE;
    CArrayPtrFlat<CItemFinder::CFindItemExt>* iMarkedItems;
private:
    CItemFinderAsyncParser( CEikRichTextEditor* aEditor, TInt* aFirstVisible, TInt aMinDigitsToFind );
    CEikRichTextEditor* iEditor;
    TInt& iFirstVisible;
    CItemFinder* iObserver; // not owned
    TInt iMinDigitsToFind;
};

CItemFinderAsyncParser::CItemFinderAsyncParser( CEikRichTextEditor* aEditor, TInt* aFirstVisible, TInt aMinDigitsToFind )
    :CActive( CActive::EPriorityIdle ), iEditor( aEditor ), iFirstVisible( *aFirstVisible ), iMinDigitsToFind( aMinDigitsToFind )
    {
    CActiveScheduler::Add(this);
    iStatus = KRequestPending;
    SetActive();
    TRequestStatus* ptr = &iStatus;
    User::RequestComplete( ptr, KErrNone );// RunL will be called when everything with higher priority has completed
    }

CItemFinderAsyncParser* CItemFinderAsyncParser::NewL( CEikRichTextEditor* aEditor, TInt* aFirstVisible, TInt aMinDigitsToFind )
    {
    return new (ELeave) CItemFinderAsyncParser( aEditor, aFirstVisible, aMinDigitsToFind );
    }

CItemFinderAsyncParser::~CItemFinderAsyncParser()
    {
    Cancel(); // does nothing
    delete iFIE;
    if ( iMarkedItems )
        {
        iMarkedItems->ResetAndDestroy();
        }
    delete iMarkedItems;
    }

void CItemFinderAsyncParser::RunL()
    {
    TInt fullLength = Min( iEditor->TextLength(), 0xffff );
    const TDesC& text = iEditor->Text()->Read( 0, fullLength );
    TInt searchAll = CFindItemEngine::EFindItemSearchURLBin
        |CFindItemEngine::EFindItemSearchMailAddressBin
        |CFindItemEngine::EFindItemSearchPhoneNumberBin
        |CFindItemEngine::EFindItemSearchScheme;
    if ( !iFIE )
        {
        iFIE = CFindItemEngine::NewL( text, (CFindItemEngine::TFindItemSearchCase)searchAll, iMinDigitsToFind );
        }
    else
        {
        iFIE->DoNewSearchL( text, (CFindItemEngine::TFindItemSearchCase)searchAll, iMinDigitsToFind );
        }
    delete iMarkedItems;
    iMarkedItems = 0;
    iMarkedItems = new ( ELeave ) CArrayPtrFlat<CItemFinder::CFindItemExt>( 10 );
    iEditor->RefreshParsersL();
    if ( iObserver && iObserver->CallbackToExtObserver() == EFalse )
        {
        iEditor->SetCursorPosL( 0, EFalse ); // need to rollback in order to make sure that line will remain same
        if ( iFirstVisible > 0 )
            {
            iEditor->SetCursorPosL( iFirstVisible, EFalse ); // Magic, parsing forces screen to first item (?)
            }
        iObserver->NextItemOrScrollL( iFirstVisible ? CItemFinder::EInit : CItemFinder::EInitDown );
        }
    }

void CItemFinderAsyncParser::DoCancel()
    {
    }

EXPORT_C CItemFinder::CFindItemExt::~CFindItemExt()
		{
		if ( iItemDescriptor ) 
				delete iItemDescriptor;
		}
	
CItemFinder::~CItemFinder()
    {
    CRichText::DeactivateParser(this);   
    if ( iCurrentItemExt )
        {
        delete iCurrentItemExt;
        }    
    if ( iExternalLinks )
        {
        iExternalLinks->ResetAndDestroy();
        delete iExternalLinks;
        }
    if ( iAsyncParser )
        {
        delete iAsyncParser;
        }    
    if ( iSchemeResolver )
        {
        delete iSchemeResolver;
        }    
    }

CItemFinder::CItemFinder( TInt aFindFlags ): iFlags( aFindFlags )
    {}

void CItemFinder::ConstructL()
    {
    iMinDigitsToFind = KItemFinderMinDigitsToFind; // default
    iCurrentItemExt = new (ELeave) CFindItemExt();
    CRichText::ActivateParserL(this);
    iSchemeResolver = CSchemeResolver::NewL();
    iMinDigitsToFind = GetMinDigitsToFindL(); // variated.
    }

TInt CItemFinder::GetMinDigitsToFindL()
    {
    TInt err = KErrNone;
    CRepository* variation = CRepository::NewL( KCRUidCommonUi );
    TInt value;
    err = variation->Get( KCuiMinDigitsToFind, value );
    delete variation;
    if ( err != KErrNone )
        {
        value = KItemFinderMinDigitsToFind;
        }
    return value;
  }

EXPORT_C CItemFinder* CItemFinder::NewL( TInt aFindFlags )
    {
    CItemFinder* me = new (ELeave) CItemFinder( aFindFlags );
    CleanupStack::PushL( me );
    me->ConstructL();
    CleanupStack::Pop();
    return me;
    }

EXPORT_C TBool CItemFinder::NextItemOrScrollL( TFindDirection aDirection )
    {
    TBool allowScroll = ETrue;
    if ( !iEditor || !(*iEditor)  )
        {
        return EFalse;
        }
    if ( aDirection == EInit || aDirection == EInitUp || aDirection == EInitDown )
        {
        if ( aDirection == EInitUp )
            {
            iPreviousDirection = ENextUp;
            iCurrentStart = iCurrentEnd = (*iEditor)->TextLength() - 1;
            if ( iCurrentStart > 0 )
                {
                (*iEditor)->SetCursorPosL( iCurrentEnd, EFalse );
                if ( iAsyncParser && iAsyncParser->iMarkedItems && iAsyncParser->iMarkedItems->Count() > 0 )
                    // Check manually if the last item ends to last character in editor
                    // as CRichText can't handle this correctly
                    {
                    if ( iCurrentStart <= iAsyncParser->iMarkedItems->At( iAsyncParser->iMarkedItems->Count() - 1 )->iEnd )
                        {
                        ResolveAndSetItemTypeL( iAsyncParser->iMarkedItems->At( iAsyncParser->iMarkedItems->Count() - 1 )->iStart );
                        }
                    }
                }
            }
        else if ( aDirection == EInitDown )
            {
            iPreviousDirection = ENextDown;
            (*iEditor)->SetCursorPosL(0,EFalse);
            ResolveAndSetItemTypeL(0);
            }
        iFirstVisible = (*iEditor)->TextLayout()->FirstDocPosFullyInBand();
        (*iEditor)->TextView()->SetCursorVisibilityL( TCursor::EFCursorInvisible, TCursor::EFCursorInvisible );
        if ( iPreviousDirection == 0 )// just initialising
            {
            (*iEditor)->SetCursorPosL( iFirstVisible, EFalse );
            return EFalse;
            }
        // Search first tag on screen
        // and set the cursor but if none found, don't scroll
        allowScroll=EFalse;
        aDirection = iPreviousDirection;
        // check if we didn't scroll full display but only part of it
        TPoint dummy;
        if ( iCurrentStart != iCurrentEnd && (*iEditor)->TextLayout()->PosInBand( iCurrentStart, dummy ) )
            {
            (*iEditor)->SetCursorPosL( iCurrentStart, EFalse );
            if ( (*iEditor)->TextLayout()->PosInBand( iCurrentEnd, dummy ) )
                {
                // old selection should remain. basically this should be
                // the case only when tag was partly visible in previous screen
                (*iEditor)->SetSelectionL( iCurrentStart, iCurrentEnd );
                return ETrue;
                }
            }
        else if ( iPreviousDirection == ENextDown )
            { // to ensure correct scrolling of items
            (*iEditor)->SetCursorPosL( iFirstVisible, EFalse );
            }
        }
    TBool ret = EFalse;
    TInt nextItem = KErrNotFound;
    // Scroll cursor over tag or update page.
    iPreviousDirection = aDirection;
    TInt cursorPos = (*iEditor)->CursorPos();
    if ( aDirection == ENextDown )
        {
        if ( (*iEditor)->SelectionLength() )
            {
            cursorPos = iCurrentEnd;
            }
        if ( cursorPos == 0 )
            {
            ResolveAndSetItemTypeL( 0 );
            if ( iCurrentEnd != iCurrentStart )
                {
                TPoint pos;
                if ( ((*iEditor)->TextLayout()->PosInBand( iCurrentEnd, pos ) ) ) // tag does not continue over screen
                    {
                    NextItemOrScrollL( EInit ); // will set the selection
                    return ETrue;
                    }
                }
            }
        nextItem = (*iEditor)->RichText()->PositionOfNextTag( cursorPos, this );
        if ( nextItem != KErrNotFound )
            { // check whether the tag is on visible screen
            TPoint dummy;
            if ( !(*iEditor)->TextLayout()->PosInBand( nextItem, dummy ) )
                {
                nextItem = KErrNotFound;
                }
            }
        if ( allowScroll && nextItem == KErrNotFound )
            {
            (*iEditor)->MoveDisplayL( TCursorPosition::EFPageDown );
            if ( (*iEditor)->TextLayout()->FirstDocPosFullyInBand() != iFirstVisible )
                {// If keypress was effective.
                ret = ETrue;
                NextItemOrScrollL( EInit );
                }
            }
        }
    else
        {
        if ( (*iEditor)->SelectionLength() )
            {
            cursorPos = iCurrentStart;
            }
        nextItem = (*iEditor)->RichText()->PositionOfPrevTag( cursorPos, this );
        /* if nextItem is KErrNotFound can mean cursorPos is in the middel of an valid item.
         * so if cursorPos is in the middle of an vaild item, make sure that we adjust it to 
         * end of the item so that PositionOfPrevTag works fine
         */
        if( nextItem == KErrNotFound )
            {
            if ( cursorPos > 0 )
                {
                cursorPos -= 1;
                TInt temp = (*iEditor)->RichText()->PositionOfNextTag( cursorPos, this );
                if( temp != KErrNotFound )
                    {
                    cursorPos = temp;
                    }
                else
                    {
                    cursorPos = ( *iEditor )->TextLength();
                    }
                }
            nextItem = ( *iEditor )->RichText()->PositionOfPrevTag( cursorPos, this );
            }
        if ( nextItem >=0 && nextItem < iFirstVisible )
            {
            nextItem = KErrNotFound;
            }
        if ( allowScroll && nextItem == KErrNotFound )
            {
            (*iEditor)->MoveDisplayL( TCursorPosition::EFPageUp );
            TInt currPos = (*iEditor)->TextLayout()->FirstDocPosFullyInBand();
            if ( currPos != iFirstVisible )
                {// If keypress was effective.
                ret = ETrue;
                NextItemOrScrollL( EInit );
                }
            }
        }
    if ( nextItem != KErrNotFound || !allowScroll )
        {
        // Check !allowScroll for the case display was scrolled but previous item is still visible
        // and no new tag found, just make the selection visible again
        ret = ETrue;
        if ( nextItem != KErrNotFound )
            {
            iCurrentStart = nextItem;
            ResolveAndSetItemTypeL();
            }
        if ( iCurrentItemExt->iItemType != ENoneSelected )
            {
            TPoint pos;
            if ( ( !(*iEditor)->TextLayout()->PosInBand( iCurrentEnd ,pos ) ) ) // tag continues over screen
                {
                // lets check if we can scroll to show whole tag
                // if not, we'll just show what can be fitted to screen with hl
                (*iEditor)->TextLayout()->DocPosToXyPosL( iFirstVisible, pos );
                TRect lineRect;
                TPoint tagStart;
                (*iEditor)->TextLayout()->GetLineRect( pos.iY, lineRect );
                (*iEditor)->TextLayout()->DocPosToXyPosL( iCurrentStart, tagStart );
                if (!lineRect.Contains(tagStart) && allowScroll )
                    {
                    (*iEditor)->MoveDisplayL( TCursorPosition::EFPageDown );
                    while ( !(*iEditor)->TextLayout()->PosInBand( iCurrentStart, pos ) )
                        {
                        (*iEditor)->MoveDisplayL( TCursorPosition::EFLineUp );
                        }
                    NextItemOrScrollL(EInit);
                    }
                else if ( !lineRect.Contains( tagStart ) )
                    {
                    // we are not allowed to scroll, dont show highligh
                    iCurrentStart = iCurrentEnd = iFirstVisible;
                    ResetCurrentItem();
                    return ret;
                    }
                }
            else if ( nextItem == KErrNotFound )
                {
                // if the current end visible,and next item invisible, no select
                iCurrentStart = iCurrentEnd = iFirstVisible;
                ResetCurrentItem();
                return ret;
                }
            }
        if ( iCurrentStart < iCurrentEnd )
            {
            (*iEditor)->SetSelectionL( iCurrentStart, iCurrentEnd );
            }
        else
            {
            ResetCurrentItem(); // no item selected
            }
        }
    return ret;
    }

EXPORT_C void CItemFinder::SetFindModeL( TInt aFindFlags )
    {
    if ( iFlags != aFindFlags )
        {
        iFlags = aFindFlags;
        if ( iEditor && *iEditor )
            {
            User::LeaveIfError ( RefreshEditor() );
            }
        }
    if ( !aFindFlags && iEditor && *iEditor )
        {
        if (!iExternalObserver) // do not align if no control to scrolling
            {
            iCurrentEnd = iCurrentStart;
            iFirstVisible = (*iEditor)->TextLayout()->FirstDocPosFullyInBand();
            (*iEditor)->SetCursorPosL( iFirstVisible, EFalse );
            }
        ResetCurrentItem();
        }
    }

EXPORT_C void CItemFinder::SetEditor( CEikRichTextEditor** aEditor )
    {
    iEditor=aEditor;
    if ( aEditor && *aEditor && (*aEditor)->TextLength() )
        {
        TRAP_IGNORE( (*aEditor)->SetHighlightStyleL( EEikEdwinHighlightLink ) );
        if ( iAsyncParser )
            {
            // We are changing the editor used, strange.
            delete iAsyncParser;
            iAsyncParser = 0;
            }
        iMarkedArrayComplete = EFalse;
        TRAPD( err, iAsyncParser = CItemFinderAsyncParser::NewL( *iEditor, &iFirstVisible, iMinDigitsToFind ) ); // can't signal failure to client.
        if ( !err )
            {
            iAsyncParser->SetCallbackObserver( this );
            }
        }
    }

// From MParser
EXPORT_C TBool CItemFinder::ParseThisText(
    const CRichText& aTextObj,
    TBool /*aAllowBack*/,
    TInt aStartScan,
    TInt aScanLength,
    TInt& aStartTag,
    TInt& aTagLength )
    {
    TBool ret = EFalse;
    if ( iEditor && *iEditor && (*iEditor)->RichText() != &aTextObj )
        {
        return ret;
        }
    if ( !iAsyncParser || iAsyncParser->IsActive() || !iAsyncParser->iMarkedItems )
        {
        return ret; // Asynch parser not ready
        }
    TInt lastInRange = aStartScan + aScanLength;
    aStartTag = lastInRange;
    CFindItemEngine::SFoundItem item = { 0, 0 };
    HBufC* tag = 0;
    TInt engineFlags = EngineFlags();
    // Find (next) external item.
    CFindItemExt* externalItem = NULL;
    if ( iExternalLinks )
        {
        TInt externalIndex = 0;
        while ( externalIndex < iExternalLinks->Count() )
            {
            CFindItemExt* tmp = iExternalLinks->At( externalIndex );
            if ( tmp && ( tmp->iStart >= aStartScan ))
                {
                externalItem = tmp;
                switch( externalItem->iItemType )
                    {
                    case EUrlAddress:
                        item.iItemType = CFindItemEngine::EFindItemSearchURLBin;
                        break;
                    case EUriScheme:
                        item.iItemType = CFindItemEngine::EFindItemSearchScheme;
                        break;
                    default: // only EUrlAddress and EUriScheme supported
                        item.iItemType = (CFindItemEngine::TFindItemSearchCase)0;
                        break;
                    }
                if(item.iItemType&engineFlags)
                	{
                	tag = externalItem->iItemDescriptor->Des().Alloc(); // Null if failed.
                	item.iStartPos = externalItem->iStart;
                    item.iLength = externalItem->iEnd - item.iStartPos + 1;
                	break;
                	}
                }
            externalIndex++;
            }
        }
    // Find (next) internal item.
    iAsyncParser->iFIE->ResetPosition();
    CFindItemEngine::SFoundItem internalItem = { 0, 0 };
    if ( iAsyncParser->iFIE->Item( internalItem ) )
        {
        do
            {
            if ( ( internalItem.iStartPos >= aStartScan ) && ( internalItem.iItemType & engineFlags ) )
                {
                CFindItemEngine::SFoundItem scrollItem = { 0, 0 };
                while ( iAsyncParser->iFIE->NextItem( scrollItem ) ) // Find longest overridden item.
                    {
                    if ( scrollItem.iStartPos == internalItem.iStartPos )
                        {
                        if ( internalItem.iLength == scrollItem.iLength )
                            {
                            if ( internalItem.iItemType & CFindItemEngine::EFindItemSearchScheme ) // Check if valid scheme.
                                {
                                if ( !SchemeSupported( (*iEditor)->Text()->Read( internalItem.iStartPos, internalItem.iLength ) ) )
                                    {
                                    internalItem = scrollItem;
                                    }
                                }
                            }
                        else if ( ( scrollItem.iItemType & engineFlags ) && ( internalItem.iLength < scrollItem.iLength ) )
                            {
                            internalItem = scrollItem;
                            }
                        else if ( ( scrollItem.iItemType & CFindItemEngine::EFindItemSearchURLBin )
                                  && ( internalItem.iLength > scrollItem.iLength ) 
                                  && !SchemeSupported( (*iEditor)->Text()->Read( internalItem.iStartPos, internalItem.iLength ) ) )
                            {
                            // this is because URL is included in URI scheme
                            internalItem = scrollItem;
                            }
                        }
                    else
                        {
                        iAsyncParser->iFIE->PrevItem(scrollItem);
                        break;
                        }
                    }
               if ( internalItem.iItemType & CFindItemEngine::EFindItemSearchScheme ) // Check if valid scheme.
                    {
                    if ( SchemeSupported( (*iEditor)->Text()->Read( internalItem.iStartPos, internalItem.iLength ) ) )
                        {
                        break;
                        }
                    }
                else if ( internalItem.iLength >= MinLengthForItemType( internalItem.iItemType ) ) // Check if valid length.
                    {
                    break;
                    }
                }
            } while ( iAsyncParser->iFIE->NextItem( internalItem ) );
        }
   
    // Use internal item as item.
    TBool internalUsed( EFalse );
    if ( ( internalItem.iLength >0 ) && (internalItem.iStartPos>=aStartScan) &&( internalItem.iItemType&engineFlags )&& ( !externalItem || ( internalItem.iStartPos + internalItem.iLength - 1 ) < externalItem->iStart ) )
        {
        item = internalItem;
        delete tag; // Allocated for external link.
        tag = (*iEditor)->Text()->Read( item.iStartPos, item.iLength ).Alloc(); // Null if failed.
        internalUsed = ETrue;
        }
    // Add item as a marked item.
    if ( item.iStartPos >= aStartScan && ( item.iStartPos + item.iLength ) <= lastInRange &&
        item.iItemType & engineFlags &&
        ( ( internalUsed && item.iLength >= MinLengthForItemType( item.iItemType ) ) || !internalUsed ) &&
        tag )
        {
        TBool schemeNotSupported( EFalse );
        if ( item.iItemType & CFindItemEngine::EFindItemSearchScheme ) // Check if scheme valid.
            {
            if ( !SchemeSupported( tag->Des() ) )
                {
                schemeNotSupported = ETrue;
                ret = EFalse;
                }
            }
        if ( !schemeNotSupported ) // Add if valid item
            {
            aStartTag = item.iStartPos;
            aTagLength = item.iLength;
            TInt err = KErrNone;
            if ( !iMarkedArrayComplete )
                {
                // Resolve type and tag.
                TItemType type = ENoneSelected;
                switch( item.iItemType )
                    {
                    case CFindItemEngine::EFindItemSearchURLBin:
                        type = EUrlAddress;
                        break;
                    case CFindItemEngine::EFindItemSearchMailAddressBin:
                        type = EEmailAddress;
                        break;
                    case CFindItemEngine::EFindItemSearchPhoneNumberBin:
                        type = EPhoneNumber;
                        break;
                    case CFindItemEngine::EFindItemSearchScheme:
                        {
                        type = EUriScheme;
                        const TDesC& pref = tag->Des().Left( 4 );
                        if ( pref.CompareF( KHTTPPREFIX().Left( 4 ) ) == 0 || pref.CompareF( RTSP ) == 0 )
                            {
                            type = EUrlAddress;
                            }
                        }
                        break;
                    default:
                        break;
                    }
                CFindItemExt* newItem = NULL;
                TRAP( err, // Non-leaving method
                    {
                    newItem = new (ELeave) CFindItemExt();
                    newItem->iItemType = type;
                    newItem->iItemDescriptor = tag->Des().AllocL();
                    newItem->iStart = aStartTag;
                    newItem->iEnd = aStartTag + aTagLength - 1;
                    iAsyncParser->iMarkedItems->AppendL( newItem ); // Ownership changed.
                    newItem = NULL;
                    } );
                delete newItem;
                }
            if ( !err )
                {
                ret = ETrue;
                }
            }
        }
    delete tag;
    if ( !ret || ( ( aStartTag + aTagLength ) == (*iEditor)->TextLength() ) ) // iMarkedList complete
        {
        iMarkedArrayComplete = ETrue;
        }
    return ret;
    }

TInt CItemFinder::MinLengthForItemType( TInt aItemType )
    {
    TInt length = KMINTAGLENGTH; // by default
    if ( aItemType == CFindItemEngine::EFindItemSearchPhoneNumberBin )
        {
        length = iMinDigitsToFind; // For phone numbers
        }
    return length;
    }

EXPORT_C const TDesC& CItemFinder::CreateDoItText(
    const CRichText& /*aTextObj*/,
    TInt /*aStartText*/,
    TInt /*aLength*/)
    {
    return KNullDesC();
    }

EXPORT_C void CItemFinder::ActivateThisTextL(
    const CRichText& /*aTextObj*/,
    TInt /*aStartText*/,
    TInt /*aLength*/)
    {
    // We don't need this
    }

EXPORT_C TBool CItemFinder::ReformatOnRecognise() const
    {
    return ETrue;
    }

EXPORT_C TBool CItemFinder::ReformatOnRollover() const
    {
    return EFalse; // Rollover formating causes too much "unwanted" parsing.
    }

EXPORT_C void CItemFinder::GetRecogniseFormat( TCharFormat& aFormat )
    {
    aFormat.iFontPresentation.iUnderline = EUnderlineOn;
    TRgb color( KRgbBlue );
    AknsUtils::GetCachedColor( AknsUtils::SkinInstance(), color, KAknsIIDQsnHighlightColors,EAknsCIQsnHighlightColorsCG3 );
    aFormat.iFontPresentation.iTextColor = color;
    }

EXPORT_C void CItemFinder::GetRolloverFormat( TCharFormat& /*aFormat*/ )
    {
    }

EXPORT_C TBool CItemFinder::ConfirmCursorOverTag(
    const CRichText& /*aTextObj*/,
    TInt /*aTagStart*/,
    TInt /*aTagLen*/,
    TInt /*aCurPos*/)
    {
    return ETrue;
    }

EXPORT_C void CItemFinder::Release()
    {
    iEditor = 0; // This makes parser to ignore practically all request from outside
    }

EXPORT_C void CItemFinder::MParser_Reserved_2()
    {
    }

EXPORT_C void CItemFinder::ResetCurrentItem()
    {
    if ( iCurrentItemExt )
        {
        iCurrentItemExt->iItemType = ENoneSelected;
        delete iCurrentItemExt->iItemDescriptor;
        iCurrentItemExt->iItemDescriptor = 0;
        iCurrentItemExt->iStart = 0;
        iCurrentItemExt->iEnd = 0;
        }
    }

EXPORT_C TInt CItemFinder::PositionOfNextItem( TFindDirection aDirection )
    {
    if ( iAsyncParser && !iAsyncParser->IsActive() ) // exists only when editor is set
        {
        // Going down
        if ( aDirection != ENextUp )
            {
            if ( (*iEditor)->CursorPos() == 0 && // check if the first char starts the tag
                iCurrentItemExt->iItemType == ENoneSelected &&
                iAsyncParser->iMarkedItems &&
                iAsyncParser->iMarkedItems->Count() > 0 &&
                iAsyncParser->iMarkedItems->At(0)->iStart == 0 )
                {
                return 0;
                }
            return (*iEditor)->RichText()->PositionOfNextTag( (*iEditor)->CursorPos(), this );
            }
        else
            {
            return (*iEditor)->RichText()->PositionOfPrevTag( (*iEditor)->CursorPos(), this );
            }
        }
    return KErrNotFound;
    }

EXPORT_C void CItemFinder::ResolveAndSetItemTypeL( TInt aStart ) // defaults to KErrNotFound
    {
    if ( aStart != KErrNotFound )
        {
        iCurrentStart = aStart;
        }
    ResetCurrentItem(); // Reset item.
    if ( !iAsyncParser || iAsyncParser->IsActive() ) // Text not parsed
        {
        return;
        }
    iCurrentEnd = iCurrentStart;
    TInt count = iAsyncParser->iMarkedItems->Count();
    for ( TInt i = 0; i < count; i++ ) // Set item.
        {
        if ( iAsyncParser->iMarkedItems->At( i )->iStart == iCurrentStart )
            {
            iCurrentItemExt->iStart = iAsyncParser->iMarkedItems->At( i )->iStart;
            iCurrentStart = iCurrentItemExt->iStart;
            iCurrentItemExt->iEnd = iAsyncParser->iMarkedItems->At( i )->iEnd;
            iCurrentEnd = iCurrentItemExt->iEnd + 1;
            if ( iAsyncParser->iMarkedItems->At( i )->iItemDescriptor )
                {
                delete iCurrentItemExt->iItemDescriptor;
                iCurrentItemExt->iItemDescriptor = 0;
                iCurrentItemExt->iItemDescriptor = iAsyncParser->iMarkedItems->At( i )->iItemDescriptor->AllocL();
                }
            DoResolveAndSetItemTypeL( iAsyncParser->iMarkedItems->At( i ) );
            break;
            }
        }
    }

EXPORT_C void CItemFinder::AddObserver( MItemFinderObserver& aObserver )
    {
    iExternalObserver = &aObserver;
    }

// Utilities
TInt CItemFinder::EngineFlags()
    {
    TInt fieFlags( 0 );
    if ( iFlags & EUrlAddress )
        {
        fieFlags |= CFindItemEngine::EFindItemSearchURLBin;
        }
    if ( iFlags & EEmailAddress )
        {
        fieFlags |= CFindItemEngine::EFindItemSearchMailAddressBin;
        }
    if ( iFlags & EPhoneNumber )
        {
        fieFlags |= CFindItemEngine::EFindItemSearchPhoneNumberBin;
        }
    if ( iFlags & EUrlAddress || iFlags & EUriScheme )
        {
        fieFlags |= CFindItemEngine::EFindItemSearchScheme;
        }
    return fieFlags;
    }

void CItemFinder::InsertPrefixToUrl()
    {
    if ( iCurrentItemExt && iCurrentItemExt->iItemType == EUrlAddress )
        {
        const TDesC& pref = iCurrentItemExt->iItemDescriptor->Des().Left( 4 );
        if ( pref.CompareF( KHTTPPREFIX().Left( 4 ) ) == 0 || pref.CompareF( RTSP ) == 0 )
            {
            return; // prefix already exists.
            }
        HBufC* tmp = iCurrentItemExt->iItemDescriptor->ReAlloc( iCurrentItemExt->iItemDescriptor->Length() + KHTTPPREFIX().Length() );
        if ( tmp )
            {
            iCurrentItemExt->iItemDescriptor = tmp;
            iCurrentItemExt->iItemDescriptor->Des().Insert( 0, KHTTPPREFIX );
            }
        }
    }

TBool CItemFinder::SchemeSupported( const TDesC& aScheme )
    {
    if ( aScheme.Left( KTELPREFIX().Length() ).CompareF( KTELPREFIX ) == 0 )
        {
        if ( CommonPhoneParser::IsValidPhoneNumber( aScheme.Mid( 4 ), CommonPhoneParser::EPlainPhoneNumber) )
            {
            return EFalse; // will be handled as pure phone number later on.
            }
        }
    if ( iFlags & EUrlAddress || iFlags & EUriScheme )
        {
        TInt schLength = aScheme.Locate( ':' );
        if ( schLength > 0 )
            {
            TInt suppCount = iSchemeResolver->SupportedSchemes().Count();
            for ( TInt i = 0; i < suppCount; i++ )
                {
                if ( aScheme.Length() >= schLength && iSchemeResolver->SupportedSchemes().At(i)->Des().CompareF( aScheme.Left( schLength ) ) == 0)
                    {
                    return ETrue;
                    }
                }
            }
        }
    return EFalse;
    }

TBool CItemFinder::CallbackToExtObserver()
    {
    if ( iExternalObserver )
        {
        iExternalObserver->HandleParsingComplete();
        return ETrue;
        }
    return EFalse;
    }

EXPORT_C TBool CItemFinder::ItemWasTappedL( const TPoint aTappedPoint )
    {
    if ( !iAsyncParser || iAsyncParser->IsActive() )
        {
        return EFalse;
        }
    TInt pos = 0;
    TInt len = (*iEditor)->TextLayout()->PosRangeInBand( pos );
    TRect rect;
    TInt i = 0;
    while ( i < iAsyncParser->iMarkedItems->Count() ) // Check visible items
        {
        TInt end = iAsyncParser->iMarkedItems->At( i )->iEnd;
        if ( end < pos )
            {
             i++;
            continue; // Item not visible.
            };
        TInt start = iAsyncParser->iMarkedItems->At( i )->iStart;
        if ( start >= ( pos + len ) )
            {
            break; // Item not visible.
            }
        TInt lastLine = (*iEditor)->TextLayout()->GetLineNumber( end );
        TInt nextLine = 0;
        TInt lastPos = start;
        do // Check all rects of one item.
            {
            rect = (*iEditor)->TextLayout()->GetLineRectL( start, end );
            if ( rect.Contains( aTappedPoint ) ) // Item rect tapped.
                {
                iFirstVisible = (*iEditor)->TextLayout()->FirstDocPosFullyInBand();
                ResetCurrentItem();
                iCurrentItemExt->iStart = iAsyncParser->iMarkedItems->At( i )->iStart;
                iCurrentStart = iCurrentItemExt->iStart;
                iCurrentItemExt->iEnd = iAsyncParser->iMarkedItems->At( i )->iEnd;
                iCurrentEnd = iCurrentItemExt->iEnd + 1;
                DoResolveAndSetItemTypeL( iAsyncParser->iMarkedItems->At( i ) );
                (*iEditor)->SetSelectionL( iCurrentEnd, iCurrentStart );
                return ETrue; // Hit
                }
            TPoint midPoint( rect.iBr.iX, ( rect.iBr.iY + rect.iTl.iY ) / 2 );
            lastPos = (*iEditor)->TextLayout()->XyPosToDocPosL( midPoint );
            start = lastPos + 1;
            nextLine = (*iEditor)->TextLayout()->GetLineNumber( lastPos );
            } while ( nextLine != lastLine );
        i++;
        }
    return EFalse; // No hit
    }

void CItemFinder::DoResolveAndSetItemTypeL( const CFindItemExt* aItem )
    {
    if ( aItem )
        {
        iCurrentItemExt->iItemType = aItem->iItemType;
        if ( aItem->iItemType != ENoneSelected && iCurrentEnd >= iCurrentStart )
            {
            if ( !iCurrentItemExt->iItemDescriptor )
                {
                iCurrentItemExt->iItemDescriptor = aItem->iItemDescriptor->AllocL();
                }
            if ( iCurrentItemExt->iItemType == EUrlAddress )
                {
                InsertPrefixToUrl(); // old url types need prefix in order to work w/ schemehandler
                }
            if ( iCurrentItemExt->iItemType == EUriScheme )
                {
                // some schemes (ie. "old ones") have special handling
                const TDesC& pref = iCurrentItemExt->iItemDescriptor->Des().Left( 4 );
                if ( pref.CompareF( KHTTPPREFIX().Left( 4 ) ) == 0 || pref.CompareF( RTSP ) == 0 )
                    {
                    iCurrentItemExt->iItemType = EUrlAddress;
                    }
                }
            }
        }
    }

EXPORT_C TInt CItemFinder::SetExternalLinks( CArrayPtrFlat<CFindItemExt>* aLinks )
    {
    TInt error = KErrNone;
    if ( iExternalLinks ) // Remove existing links.
        {
        iExternalLinks->ResetAndDestroy();
        delete iExternalLinks;
        iExternalLinks = 0;
        }
    // Add an external link validated by engine
    TInt linkCount = aLinks ? aLinks->Count() : 0;
    if ( linkCount > 0 )
        {
        iExternalLinks = new CArrayPtrFlat<CItemFinder::CFindItemExt>( linkCount );
        if ( !iExternalLinks ) // Error: no memory.
            {
            return EFalse;
            }
        CFindItemEngine* fie = NULL; // For validation.
        TInt linkIndex = 0;
        do
            {
            CFindItemExt* link = aLinks->At( linkIndex++ );                   
            TInt flag = 0;
            switch ( link->iItemType )
                {
                case EUrlAddress:
                    flag = CFindItemEngine::EFindItemSearchURLBin;
                    break;
                case EUriScheme:                    
                    if ( !SchemeSupported( link->iItemDescriptor->Des() ) )
                        {
                        continue;
                        } 
                    flag = CFindItemEngine::EFindItemSearchScheme;                        
                    break;
                default: // Ignore unsupported types.
                    continue;
                }                                                   
            if ( !fie )
                {
                TRAP( error, fie = CFindItemEngine::NewL( link->iItemDescriptor->Des(), (CFindItemEngine::TFindItemSearchCase)flag ) );
                }
            else
                {
                TRAP( error, fie->DoNewSearchL( link->iItemDescriptor->Des(), (CFindItemEngine::TFindItemSearchCase)flag ) );
                }
            if ( error != KErrNone ) // Error: find engine fails.
                {
                iExternalLinks->ResetAndDestroy();
                delete iExternalLinks;
                iExternalLinks = 0;
                delete fie;
                return EFalse;                
                }                
            if ( fie->ItemCount() ) // Link was found.
                {                
                CFindItemEngine::SFoundItem item = fie->ItemArray()->At( 0 );
                const TDesC& text = link->iItemDescriptor->Des().Mid( item.iStartPos, item.iLength );
                if ( link->iItemDescriptor->Des().CompareF( text ) == 0 )
                    {                    
                    CFindItemExt* newItem = 0;                    
                    newItem = new CFindItemExt();
                    error = KErrNoMemory;                                        
                    if ( newItem )
                        {                        
                        newItem->iItemDescriptor = link->iItemDescriptor->Alloc();
                        if ( newItem->iItemDescriptor )
                            {                                                                                                                                                                 
                            newItem->iItemType = link->iItemType;
                            newItem->iStart = link->iStart;
                            newItem->iEnd = link->iEnd;
                            error = KErrNone;
                            TRAP( error, iExternalLinks->AppendL( newItem ) );                                                        
                            }
                        }                                                                 
                     if ( error != KErrNone ) // Error: cannot set ext. links.
                        {
                        iExternalLinks->ResetAndDestroy();
                        delete iExternalLinks;
                        iExternalLinks = 0;
                        delete newItem->iItemDescriptor;
                        delete newItem;
                        delete fie;
                        return EFalse;
                        }                                                                     
                    }
                }                       
            }
        while ( linkIndex < linkCount );                
        delete fie; 
        }
    error = RefreshEditor(); // With ext. links.
    if ( error != KErrNone )
        {
        iExternalLinks->ResetAndDestroy();
        delete iExternalLinks;
        iExternalLinks = 0;
        (void)RefreshEditor();
        }    
    return error;
    }

EXPORT_C CItemFinder::CFindItemExt& CItemFinder::CurrentItemExt()
    {
    return *iCurrentItemExt;
    }

EXPORT_C TPtrC CItemFinder::CurrentSelection()
    {
    if ( iEditor && *iEditor ) // if editor used.
        {
        return (*iEditor)->Text()->Read( (*iEditor)->Selection().LowerPos(), (*iEditor)->Selection().Length() );      
        }
    else
        {
        HBufC* buffer = CurrentItemExt().iItemDescriptor;
        if ( buffer )
            {
            return *buffer;
            }
        else
            {
            return KNullDesC();
            }
        }
    }

TInt CItemFinder::RefreshEditor()
    {
    TInt error = KErrNone;
    TRAP( error, // Non-leaving method.
        {
        if ( iAsyncParser )
            {
            iFirstVisible = (*iEditor)->TextLayout()->FirstDocPosFullyInBand();
            iMarkedArrayComplete = EFalse;
            if ( iAsyncParser->iMarkedItems )
                {
                iAsyncParser->iMarkedItems->ResetAndDestroy();
                }
            (*iEditor)->RefreshParsersL();
            (*iEditor)->SetCursorPosL( 0, EFalse );
            ResolveAndSetItemTypeL( iFirstVisible );
            (*iEditor)->SetCursorPosL( iFirstVisible, EFalse );
            iPreviousDirection = ENextDown;
            NextItemOrScrollL( EInit );
            }
        else if ( (*iEditor)->TextLength() )
            {
            iMarkedArrayComplete = EFalse;
            iAsyncParser = CItemFinderAsyncParser::NewL( *iEditor, &iFirstVisible, iMinDigitsToFind );
            iAsyncParser->SetCallbackObserver( this );
            }
        } ); // TRAP
    return error;
    }

// End of File
