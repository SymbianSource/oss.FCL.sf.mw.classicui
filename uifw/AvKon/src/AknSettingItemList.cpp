/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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
*    Support for setting item lists and their setting
*    items.  THe setting item list owns a listbox and an array of
*    setting items. The latter provides a MDesCArray interface for the
*    listbox model.
*
*    Setting Items are abstractions of data types, that
*    have a capability to launch setting pages.
*
*
*/


#include <gulicon.h>
#include <coemain.h>

//For TResourceReader
#include <barsread.h>

#include <avkon.hrh>
#include <avkon.rsg>
#include <avkon.mbg>

// For Numbered and unnumbered setting style lists
#include <aknlists.h>
#include <aknnotewrappers.h>

#include <aknlayoutscalable_avkon.cdl.h>
#include <aknconsts.h>

// For layout switch events
#include "AknDef.h"

// For proper icon array management
#include "AknIconArray.h"

#include "aknsettingitemlist.h"
#include "akntextsettingpage.h"
#include "aknvolumesettingpage.h"
#include "aknslidersettingpage.h"
#include "aknmfnesettingpage.h"
#include "aknpopupsettingpage.h"
#include "aknpasswordsettingpage.h"
#include <AknsConstants.h>

#include "akntrace.h"

const TInt KAknSettingItemMaxNumberDigits = 3; // for the setting item numbers
const TInt KAknSettingItemArrayGranularity = 5;
const TInt KAknSettingItemTimeBufferLength = 30;
const TInt KAknSettingItemIpTextBufferLength = 15; //Assumes 4 fields of 3 + 3 dots


// Separator for listbox text decoration
_LIT(KListBoxTextSeparator, "\t");

// Format for a number
_LIT(KAknSettingItemDecimalFormat, "%d" );

// Space used for listbox and time offset text formatting
_LIT(KAknSettingItemSingleSpace, " " );

// Plus and minus used for listbox time offset
_LIT(KAknSettingItemPlus, "+" );
_LIT(KAknSettingItemMinus, "-" );

// Empty IP address
_LIT(KAknSettingItemEmptyIpAddress, "0.0.0.0" );

enum TAknSettingItemListPanic
    {
    EAknPanicSettingItemListUnused,
    EAknPanicSettingItemListNoEmptyText,
    EAknPanicSettingItemListInsufficientResource,
    EAknPanicSettingItemListInconsistentControlType,
    EAknPanicSettingItemListInvalidPasswordMode,
    EAknPanicSettingItemListInvalidDateMode,
    EAknPanicSettingItemListInvalidEnumeratedValue,
    EAknPanicSettingItemListWrongNumberOfValues,
    EAknPanicSettingItemListRequiredValueNotInArray,
    EAknPanicSettingItemListInvalidIndex,
    EAknPanicSettingItemListConstructionNotComplete,
    EAknPanicSettingItemListArrayLengthsMisMatch,
    EAknPanicSettingItemListNotBinaryCompatible,
    EAknPanicSettingItemListInvalidPointer,
    EAknPanicSettingItemListBadIcon
    };

GLDEF_C void Panic(TAknSettingItemListPanic aPanic)
    {
    _LIT(KPanicCat,"Setting Item List");
    User::Panic(KPanicCat, aPanic);
    }

// -------------------------------
// CAknSettingItemExtension
// -------------------------------
//

NONSHARABLE_CLASS( CAknSettingItemExtension ) : CBase
    {
    public:

    static CAknSettingItemExtension* NewL();
    ~CAknSettingItemExtension();
    void CreateLockIconL(CArrayPtr<CGulIcon>* aIconArray);

    protected:
    void ConstructL();

    private:
    CAknSettingItemExtension();

    //members
    public:
    TInt iLockIconIndex;
    TInt iLockIconHighlightIndex;

    private:

    };

CAknSettingItemExtension::CAknSettingItemExtension()
: iLockIconIndex(KErrNotFound), iLockIconHighlightIndex(KErrNotFound)
    {
    }
CAknSettingItemExtension::~CAknSettingItemExtension()
    {
    }

void CAknSettingItemExtension::ConstructL()
    {
    }

CAknSettingItemExtension* CAknSettingItemExtension::NewL()
    {
    CAknSettingItemExtension* settingExtension = new (ELeave) CAknSettingItemExtension;
    CleanupStack::PushL(settingExtension);
    settingExtension->ConstructL();
    CleanupStack::Pop(settingExtension);
    return settingExtension;
    }

void CAknSettingItemExtension::CreateLockIconL(CArrayPtr<CGulIcon>* aIconArray)
    {
    // START of lock icon creation

    // Create the lock icon as the last icon in the table
    CFbsBitmap* skinnedBitmap = NULL;
    CFbsBitmap* skinnedMask = NULL;

    // Make the icon and put it in the array
    CGulIcon* icon = CGulIcon::NewL();
    CleanupStack::PushL(icon);

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    // Create color icon
    AknsUtils::CreateColorIconL(skin, KAknsIIDQgnIndiSettProtectedAdd,
                                KAknsIIDQsnIconColors, EAknsCIQsnIconColorsCG13,
                                skinnedBitmap, skinnedMask, KAvkonBitmapFile,
                                EMbmAvkonQgn_indi_sett_protected_add,
                                EMbmAvkonQgn_indi_sett_protected_add_mask, KRgbBlack);

    icon->SetMask(skinnedMask);// ownership transferred
    icon->SetBitmap(skinnedBitmap); // ownership transferred

    if(iLockIconIndex == KErrNotFound)
        {
        aIconArray->AppendL( icon );
        iLockIconIndex = aIconArray->Count() - 1;
        }
    else
        {
        delete aIconArray->At(iLockIconIndex);
        aIconArray->Delete(iLockIconIndex);
        aIconArray->InsertL(iLockIconIndex, icon);
        }

    CleanupStack::Pop(); // icon

    // Create the lock icon for highlight
    skinnedBitmap = NULL;
    skinnedMask = NULL;

    // Make the icon and put it in the array
    icon = CGulIcon::NewL();
    CleanupStack::PushL(icon);

    // Create color icon
    AknsUtils::CreateColorIconL(skin, KAknsIIDQgnIndiSettProtectedAdd,
                                KAknsIIDQsnIconColors, EAknsCIQsnIconColorsCG16,
                                skinnedBitmap, skinnedMask, KAvkonBitmapFile,
                                EMbmAvkonQgn_indi_sett_protected_add,
                                EMbmAvkonQgn_indi_sett_protected_add_mask, KRgbBlack);


    icon->SetMask(skinnedMask);// ownership transferred
    icon->SetBitmap(skinnedBitmap); // ownership transferred

    if(iLockIconHighlightIndex == KErrNotFound)
        {
        aIconArray->AppendL( icon );
        iLockIconHighlightIndex = aIconArray->Count() - 1;
        }
    else
        {
        delete aIconArray->At(iLockIconHighlightIndex);
        aIconArray->Delete(iLockIconHighlightIndex);
        aIconArray->InsertL(iLockIconHighlightIndex, icon);
        }

    CleanupStack::Pop(); // icon

    // END of lock icon creation
    }
// -------------------------------
// CAknSettingItem
// -------------------------------
//
// public:

/**
* Default constructor.
*/
EXPORT_C CAknSettingItem::CAknSettingItem( TInt aIdentifier) : iIdentifier( aIdentifier )
    {
    }
EXPORT_C CAknSettingItem::~CAknSettingItem()
    {
    delete iExtension;
    delete iSettingName;
    delete iListBoxText;
    delete iEmptyItemText;
    delete iCompulsoryText;
    }

EXPORT_C void CAknSettingItem::ConstructL(
    const TBool aIsNumberedStyle,
    const TInt aOrdinal,
    const TDesC& aSettingName,
    CArrayPtr<CGulIcon>* aIconArray,
    TInt aSettingPageResourceId,
    TInt aEditorControlType,
    TInt aSettingEditorResourceId,
    TInt aAssociatedResourceId)
    {
    _AKNTRACE_FUNC_ENTER;
    iExtension = CAknSettingItemExtension::NewL();

    if ( aIsNumberedStyle )
        iFlags |= EIsNumberedStyle;
    else
        iFlags &= (~EIsNumberedStyle);

    iOrdinal = aOrdinal;

    HBufC* newText = aSettingName.AllocL();
    delete( iSettingName ); // after the AllocL succeeds
    iSettingName = newText;

    iIconArray = aIconArray;

    iSettingPageResourceId = aSettingPageResourceId;
    iEditorControlType = aEditorControlType;
    iSettingEditorResourceId = aSettingEditorResourceId;
    iAssociatedResourceId = aAssociatedResourceId;

    // Give the derived classes a chance to use the additional resource id:
    CompleteConstructionL();

    // Perform the initial load of the data
    LoadL();

    CFbsBitmap* bitmap = CreateBitmapL(); // This is a test to see if the setting item HAS a bitmap to offfer
    if ( bitmap )
        {
        CleanupStack::PushL(bitmap);
        // Make the icon and put it in the array
        CGulIcon* icon = CGulIcon::NewL();
        icon->SetBitmap( bitmap ); // ownership transferred
        CleanupStack::Pop(); // bitmap;

        CleanupStack::PushL( icon );
        iIconArray->AppendL( icon );
        CleanupStack::Pop(); // icon

        iIconIndex = iIconArray->Count() - 1;
        iFlags |= EHasIcon;

        // This is repeated to catch any mask information that might be available
        bitmap = CreateBitmapL();
        if ( bitmap )
            icon->SetBitmap( bitmap ); // ownership transferred
        }
    else
        {
        iFlags &= (~EHasIcon);
        }

    // Finally this sets up the text for the MDcaPoint calls from listbox
    UpdateListBoxTextL();

    _AKNTRACE_FUNC_EXIT;
    }
/**
* This routine is used to replace the old bitmap with a new one.
*
*/
void CAknSettingItem::UpdateBitmapL()
    {
    if (HasIcon() )
        {
        CFbsBitmap* bitmap = CreateBitmapL();
        if ( bitmap )
            {
            // This deletes the old one as the bitmaps are owned
            iIconArray->At(iIconIndex)->SetBitmap( bitmap );
            }
        }

    }

EXPORT_C void CAknSettingItem::StoreL()
    {
    }
EXPORT_C void CAknSettingItem::LoadL()
    {
    }
EXPORT_C CFbsBitmap* CAknSettingItem::CreateBitmapL()
    {
    return 0;
    }
EXPORT_C TBool CAknSettingItem::IsNumberedStyle() const
    {
    return (iFlags & EIsNumberedStyle );
    }
EXPORT_C TBool CAknSettingItem::IsHidden() const
    {
    return (iFlags & EIsHidden );
    }

EXPORT_C void CAknSettingItem::SetHidden(TBool aHidden)
    {
    if ( aHidden )
        iFlags |= EIsHidden;
    else
        iFlags &= (~EIsHidden);
    // Note the the client code needs to do any recalculation and re-presentation of the listbox
    }


EXPORT_C TPtrC CAknSettingItem::SettingName()
    {
    return (TPtrC) *iSettingName;
    }

/**
* Returns the ordinal for the setting. Only valid the numberstyle is Numbered;
* if not it returns the "NOt displaeyd" value
*/

EXPORT_C TInt CAknSettingItem::SettingNumber() const
    {
    if (IsNumberedStyle())
        return iOrdinal;
    else
        return EAknSettingPageNoOrdinalDisplayed;
    }

EXPORT_C HBufC* CAknSettingItem::ListBoxText()
    {
    return iListBoxText;
    }

EXPORT_C const TDesC& CAknSettingItem::SettingTextL()
    {
    return EmptyItemText();
    }

EXPORT_C TBool CAknSettingItem::HasIcon() const
    {
    return (iFlags & EHasIcon );
    }

EXPORT_C void CAknSettingItem::EditItemL( TBool /* aCalledFromMenu */)
    {
    }

EXPORT_C void CAknSettingItem::HandleSettingPageEventL(CAknSettingPage* /* aSettingPage */,MAknSettingPageObserver::TAknSettingPageEvent /* aEventType */ )
    {
    _AKNTRACE_FUNC_ENTER;
    UpdateListBoxTextL();
    _AKNTRACE_FUNC_EXIT;
    }
/**
*
*/
EXPORT_C void CAknSettingItem::SetSettingPage( CAknSettingPage* aSettingPage )
    {
    iSettingPage = aSettingPage;
    }

/**
*
*/
EXPORT_C CAknSettingPage* CAknSettingItem::SettingPage() const
    {
    return iSettingPage;
    }

/**
*
*  Set up the setting page in the standard way
*
*
*/
EXPORT_C void CAknSettingItem::SetUpStandardSettingPageL()
    {
    SettingPage()->SetSettingTextL( SettingName() );

    if ( IsNumberedStyle() )
        {
        SettingPage()->SetSettingNumberL( SettingNumber() );
        SettingPage()->SetNumbered(ETrue);
        }
    else
        SettingPage()->SetNumbered(EFalse); // Suppress the numbering
    }

/**
*
*
*
*/
EXPORT_C TInt CAknSettingItem::SettingPageResourceId() const
    {
    return iSettingPageResourceId;
    }

/**
* Access method for the setting editor resource id
*
*
*/
EXPORT_C TInt CAknSettingItem::SettingEditorResourceId() const
    {
    return iSettingEditorResourceId;
    }

/**
* Access function for the associated resource Id
*
*
*/
EXPORT_C TInt CAknSettingItem::AssociatedResourceId() const
    {
    return iAssociatedResourceId;
    }

EXPORT_C void CAknSettingItem::UpdateListBoxTextL()
    {
    _AKNTRACE_FUNC_ENTER;

    // Get rid of the old value
    delete iListBoxText;
    iListBoxText = 0;

    // Update the bitmap
    UpdateBitmapL();

    if((iFlags & EViewOnly) || (iFlags & EProtected))
        {
        iExtension->CreateLockIconL(iIconArray);
        }

    // Calculate the right length
    TInt lengthRequired = 2 * KAknSettingItemMaxNumberDigits;
    lengthRequired += 4 * KListBoxTextSeparator().Length();
    lengthRequired += (SettingName().Length() );
    lengthRequired += (SettingTextL().Length() );
    if (iCompulsoryText)
        {
        lengthRequired += (iCompulsoryText->Length() );
        }

    if ( ProtectionState() == ESettingItemViewOnly ||
            ProtectionState() == ESettingItemProtected )
        {
        lengthRequired += 4 * KAknSettingItemMaxNumberDigits; // 4*3
        }

    // Create the buffer
    iListBoxText = HBufC::NewL( lengthRequired );

    TPtr listBoxTextPtr = iListBoxText->Des();
    if ( iFlags & EIsNumberedStyle )
        {
        // Locale-specific number conversion of this is done in listbox code, so not
        // done here
        listBoxTextPtr.Format( KAknSettingItemDecimalFormat, iOrdinal );
        }
    else
        {
        listBoxTextPtr.Copy( KAknSettingItemSingleSpace );
        }
    listBoxTextPtr.Append( KListBoxTextSeparator ); // index 1
    listBoxTextPtr.Append( SettingName() );
    listBoxTextPtr.Append( KListBoxTextSeparator ); // index 2
    if ( HasIcon() )
        {
        TBuf<KAknSettingItemMaxNumberDigits> iconIndexText;
        iconIndexText.Format( _L("%d"), iIconIndex ); // bitmap index encoding; not locale specific!
        listBoxTextPtr.Append( iconIndexText );
        }

    listBoxTextPtr.Append( KListBoxTextSeparator ); // index 3

    // The text put into the setting item list has had its non-printing chracters replace
    // by spaces:
    HBufC* settingText = SettingTextL().AllocL();
    TPtr settingPtr = settingText->Des();
    listBoxTextPtr.Append(ReplaceNonPrintingCharacters( settingPtr ) );
    delete settingText;

    if (iCompulsoryText)
        {
        listBoxTextPtr.Append( KListBoxTextSeparator ); // index 4
        listBoxTextPtr.Append( *iCompulsoryText );
        }

    if ( ProtectionState() == ESettingItemViewOnly ||
            ProtectionState() == ESettingItemProtected )
        {
        // icon coloring is supported in lists by using upper and lower 16 bits of the icon index number to
        // include the both non-highlight and highligh icon index in the same number
        TBuf<KAknSettingItemMaxNumberDigits*4> protectedIconIndexText;
        TInt iconIndex = iExtension->iLockIconIndex;
        iconIndex |= iExtension->iLockIconHighlightIndex << 16; // shift one word, to get the highlight to upper part
        protectedIconIndexText.Format( _L("%d"), iconIndex ); // bitmap index encoding; not locale specific!

        if (!iCompulsoryText)
            listBoxTextPtr.Append( KListBoxTextSeparator ); // index 4

        listBoxTextPtr.Append( KListBoxTextSeparator ); //index 5
        listBoxTextPtr.Append( KListBoxTextSeparator ); // index 6 -> icon 2
        listBoxTextPtr.Append( protectedIconIndexText );
        }
    _AKNTRACE_FUNC_EXIT;
    }

/**
*
* Complete the construction using the additional resource id. This is called from within ConstructXXXL routines.
* Note that Load() will not have been called yet, so the setting is still uninitialized in terms of its data content
* after this has finished. Otherwise, the instance should be ready.
*
*/
EXPORT_C void CAknSettingItem::CompleteConstructionL()
    {
    }

EXPORT_C void CAknSettingItem::SetEmptyItemTextL( const TDesC& aEmptyItemText )
    {
    delete iEmptyItemText;
    iEmptyItemText = NULL;
    iEmptyItemText = aEmptyItemText.AllocL();
    }

EXPORT_C void CAknSettingItem::SetCompulsoryIndTextL( const TDesC& aCompulsoryText )
    {
    delete iCompulsoryText;
    iCompulsoryText = NULL;
    iCompulsoryText = aCompulsoryText.AllocL();
    }

EXPORT_C TDesC& CAknSettingItem::EmptyItemText() const
    {
    __ASSERT_ALWAYS( iEmptyItemText , Panic( EAknPanicSettingItemListNoEmptyText ) );
    return *iEmptyItemText;
    }

TInt CAknSettingItem::EditorControlType() const
    {
    return iEditorControlType;
    }

EXPORT_C TBool CAknSettingItem::SetIconMask( CFbsBitmap* aMask )
    {
    TBool successfullyTransferred( EFalse );
    if (HasIcon() && aMask )
        {
        __ASSERT_DEBUG( !iIconArray->At(iIconIndex)->BitmapsOwnedExternally() , Panic( EAknPanicSettingItemListBadIcon ) );
        // This deletes the old one as the bitmaps are owned internally
        iIconArray->At(iIconIndex)->SetMask( aMask );
        successfullyTransferred = ETrue;
        }
    return successfullyTransferred;
    }

CFbsBitmap* CAknSettingItem::SetIconMaskAndReturnBitmap( CGulIcon* aIcon )
    {
    CFbsBitmap* returnedBitmap = NULL;

    if ( aIcon )
        {
        aIcon->SetBitmapsOwnedExternally( ETrue );
        CFbsBitmap* bitmap = aIcon->Bitmap();
        CFbsBitmap* mask = aIcon->Mask();
        delete aIcon; // does not own the bitmaps, so let it go

        // Nothing leaves for the rest of the routine. No Pushing

        // always return the bitmap and transfer ownership if there is one.
        if ( bitmap )
            returnedBitmap = bitmap;

        // Set the mask if there is a bitmap, an icon and a mask
        TBool maskOwnershipTransferred(EFalse);
        if ( bitmap && mask && HasIcon() )
            maskOwnershipTransferred = SetIconMask( mask );
        if ( !maskOwnershipTransferred )
            delete mask;

        }
    return returnedBitmap;
    }

// For managing item hiding
EXPORT_C TInt CAknSettingItem::VisibleIndex()
    {
    return iVisibleIndex;
    }

void CAknSettingItem::SetVisibleIndex( TInt aVisibleIndex)
    {
    iVisibleIndex = aVisibleIndex;
    }

void CAknSettingItem::SetOrdinal( TInt aOrdinal )
    {
    iOrdinal = aOrdinal;
    }

EXPORT_C void CAknSettingItem::SetSettingPageFlags( TInt aFlagPattern)
    {
    iSettingPageFlags = aFlagPattern;
    _AKNTRACE( "[%s][%s] iSettingPageFlags = %d", "CAknSettingItem", __FUNCTION__, iSettingPageFlags );
    }

EXPORT_C TInt CAknSettingItem::SettingPageFlags( ) const
    {
    return iSettingPageFlags;
    }

void CAknSettingItem::SetParentListBox( const CEikFormattedCellListBox* aListBox )
    {
    iParentListBox = aListBox;
    }

EXPORT_C TInt CAknSettingItem::Identifier() const
    {
    return iIdentifier;
    }

TPtrC CAknSettingItem::ReplaceNonPrintingCharacters( TDes& aText )
    {
    /*
    *
    *  this methdod is needed for stripping tab's away, so user
    *  entered text can not crash the listbox
    *
    *  0x0001 should not be stripped away, since it is used as
    *  separator for different length localization strings
    *
    *  0x200F and 0x200E are token for RTL and LTR.
    *
    */
    for(TInt i = 0; i < aText.Length(); i++)
        {
        TChar c (aText[i]);

        if ( !c.IsPrint() && c != 0x0001 && c != 0x200F && c != 0x200E )
            {
            TLanguage lang = User::Language();
            if ( ELangThai == lang && c == 0x200B )
            	continue;
            aText[i] = ' ';
            }
        }
    return (TPtrC) aText;
    }

EXPORT_C void CAknSettingItem::CAknSettingItem_Reserved()
    {
    }

EXPORT_C void CAknSettingItem::SetProtectionState( CAknSettingItem::TSettingItemProtection aProtected )
    {
    _AKNTRACE( "[%s][%s] aProtected = %d", "CAknSettingItem", __FUNCTION__, aProtected );
    if (aProtected == ENoSettingItemProtection)
        {
        iFlags |= ENoProtection;
        iFlags &= (~(EViewOnly | EProtected));
        }
    else if(aProtected == ESettingItemViewOnly)
        {
        iFlags |= EViewOnly;
        iFlags &= (~(ENoProtection | EProtected));
        }
    else if(aProtected == ESettingItemProtected)
        {
        iFlags |= EProtected;
        iFlags &= (~(ENoProtection | EViewOnly));
        }
    }

EXPORT_C CAknSettingItem::TSettingItemProtection CAknSettingItem::ProtectionState()
    {
    TSettingItemProtection isProtected = ENoSettingItemProtection;

    if(iFlags & ENoProtection)
        isProtected = ENoSettingItemProtection;
    else if(iFlags & EViewOnly)
        isProtected = ESettingItemViewOnly;
    else if(iFlags & EProtected)
        isProtected = ESettingItemProtected;

    return isProtected;
    }
// ---------------------------------------
// CAknTextSettingItem
//
//----------------------------------------

EXPORT_C CAknTextSettingItem::CAknTextSettingItem( TInt aIdentifier, TDes& aText ):
    CAknSettingItem(aIdentifier), iExternalText( aText ), iInternalTextPtr(0,0)
    {
    // iInternalTextPtr points to no buffer, so no allocation is done here
    }

EXPORT_C CAknTextSettingItem::~CAknTextSettingItem()
    {
    delete iInternalText;
    }

EXPORT_C void CAknTextSettingItem::StoreL()
    {
    // Copy the internal to the external
    iExternalText.Copy(iInternalText->Des() );
    }

EXPORT_C void CAknTextSettingItem::LoadL()
    {
    // iInternalText is always deleted and re-created.
    delete iInternalText;
    iInternalText = 0;
    // New buffer is long enough for the maximum length of the external buffer.
    iInternalText = HBufC::NewL(iExternalText.MaxLength());
    // Use Set so that the whole TPtr is just overwritten - and gets a new buffer
    // Note that the TPtr's buffer is owned by iInternalText, hence the old one is
    // already deleted - see above.
    iInternalTextPtr.Set(iInternalText->Des() );
    iInternalTextPtr.Copy( iExternalText );
    }

EXPORT_C const TDesC& CAknTextSettingItem::SettingTextL()
    {
    if ( iInternalText->Length() > 0 )
        return *iInternalText;
    else
        return EmptyItemText();
    }

EXPORT_C void CAknTextSettingItem::EditItemL( TBool /* aCalledFromMenu */)
    {
    _AKNTRACE_FUNC_ENTER;
    TPtrC settingName = SettingName();
    CAknSettingPage* dlg = new( ELeave )CAknTextSettingPage(
        &settingName,
        SettingNumber(),
        EditorControlType(),
        SettingEditorResourceId(),
        SettingPageResourceId(),
        iInternalTextPtr,
        SettingPageFlags() ); // Flags
    SetSettingPage( dlg );
    SettingPage()->SetSettingPageObserver(this);

    if(ProtectionState() == CAknSettingItem::ESettingItemViewOnly)
        SettingPage()->SetEditState(EFalse);

    SettingPage()->ExecuteLD(CAknSettingPage::EUpdateWhenChanged);
    SetSettingPage(0); // it is deleted now
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C TPtr& CAknTextSettingItem::InternalTextPtr()
    {
    return iInternalTextPtr;
    }

EXPORT_C TPtrC CAknTextSettingItem::ExternalText()
    {
    return (TPtrC)(iExternalText);
    }

EXPORT_C void CAknTextSettingItem::SetExternalText( TDesC& aNewExternalText )
    {
    iExternalText.Copy( aNewExternalText );
    }

EXPORT_C void CAknTextSettingItem::CAknSettingItem_Reserved()
    {
    };

// ---------------------------------------
// CAknIntegerSettingItem
//
//----------------------------------------

EXPORT_C CAknIntegerSettingItem::CAknIntegerSettingItem( TInt aIdentifier, TInt& aValue ):
    CAknSettingItem(aIdentifier), iExternalValue( aValue ), iInternalTextPtr(0,0)
    {
    }
EXPORT_C CAknIntegerSettingItem::~CAknIntegerSettingItem()
    {
    delete iInternalText;
    }

EXPORT_C void CAknIntegerSettingItem::CompleteConstructionL()
    {
    // Prepare the date buffer
    iInternalText = HBufC::NewMaxL(EAknMaxIntegerDigits);
    }
EXPORT_C void CAknIntegerSettingItem::StoreL()
    {
    // Copy the internal to the external
    iExternalValue = iInternalValue;
    }
EXPORT_C void CAknIntegerSettingItem::LoadL()
    {
    iInternalValue = iExternalValue;
    }

EXPORT_C const TDesC& CAknIntegerSettingItem::SettingTextL()
    {
    _AKNTRACE( "[%s][%s][%d].", "CAknIntegerSettingItem", __FUNCTION__, __LINE__ );
    // set the text ptr again. Its buffers are always owned by some else, so
    // removing the reference from the TPtr is OK.
    iInternalTextPtr.Set(iInternalText->Des());
    iInternalTextPtr.Format(KAknIntegerFormat, iInternalValue );
    AknTextUtils::DisplayTextLanguageSpecificNumberConversion(iInternalTextPtr);
    return iInternalTextPtr;
    }


EXPORT_C TInt& CAknIntegerSettingItem::InternalValueRef()
    {
    return iInternalValue;
    }

EXPORT_C TInt& CAknIntegerSettingItem::ExternalValueRef()
    {
    return iExternalValue;
    }

EXPORT_C void CAknIntegerSettingItem::SetExternalValue( TInt& aValue )
    {
    iExternalValue  = aValue;
    }

EXPORT_C void CAknIntegerSettingItem::CAknSettingItem_Reserved()
    {
    };

EXPORT_C CAknIntegerEdwinSettingItem::CAknIntegerEdwinSettingItem( TInt aIdentifier, TInt& aValue ):
    CAknIntegerSettingItem(aIdentifier, aValue)
    {}

EXPORT_C void CAknIntegerEdwinSettingItem::EditItemL( TBool /* aCalledFromMenu */)
    {
    _AKNTRACE_FUNC_ENTER;
    TPtrC settingName = SettingName();
    CAknSettingPage* dlg = new( ELeave )CAknIntegerSettingPage(
        &settingName,
        SettingNumber(),
        EditorControlType(),
        SettingEditorResourceId(),
        SettingPageResourceId(),
        InternalValueRef(),
        SettingPageFlags() ); // Flags

    SetSettingPage( dlg );
    SettingPage()->SetSettingPageObserver(this);

    if(ProtectionState() == CAknSettingItem::ESettingItemViewOnly)
        SettingPage()->SetEditState(EFalse);

    SettingPage()->ExecuteLD(CAknSettingPage::EUpdateWhenChanged);
    SetSettingPage( 0 );

    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CAknIntegerEdwinSettingItem::CAknSettingItem_Reserved()
    {
    };


// ---------------------------------------
// CAknPasswordSettingItem
//
//----------------------------------------

EXPORT_C CAknPasswordSettingItem::CAknPasswordSettingItem( TInt aIdentifier, enum CAknPasswordSettingItem::TAknPasswordSettingItemMode aPasswordMode, TDes& aPassword ):
    CAknTextSettingItem(aIdentifier, aPassword ), iPasswordMode( aPasswordMode )
    {
    }

EXPORT_C void CAknPasswordSettingItem::CompleteConstructionL( )
    {
    _AKNTRACE_FUNC_ENTER;
    if ( AssociatedResourceId() != 0 )
        {

        TResourceReader reader;
        CEikonEnv::Static()->CreateResourceReaderLC( reader, AssociatedResourceId() );

        TPtrC text = reader.ReadTPtrC();  // LTEXT name;
        iBlankingText.Copy( text );
        iBlankingText.Copy( text.Left( Min( KMaxPasswordBlankingTextLength, text.Length() ) ) );

        // Read the Old password confirmation LLINK
        iOldPasswordQueryResourceId = reader.ReadInt32();

        CleanupStack::PopAndDestroy(); // reader
        }

    // No blanking text, then read the password blanking from AVKON resource
    if ( iBlankingText.Length() == 0 )
        {
        HBufC* blankingText;

        if ( iPasswordMode == ENumeric )
            blankingText = CCoeEnv::Static()->AllocReadResourceLC( R_AVKON_NUMERIC_PASSWORD_BLANKING_TEXT );
        else
            blankingText = CCoeEnv::Static()->AllocReadResourceLC( R_AVKON_ALPHA_PASSWORD_BLANKING_TEXT );

        iBlankingText.Copy( blankingText->Left( Min( KMaxPasswordBlankingTextLength, blankingText->Length() ) ) );
        CleanupStack::PopAndDestroy(); // blankingText
        }
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C const TDesC& CAknPasswordSettingItem::SettingTextL()
    {
    if ( InternalTextPtr().Length() != 0 )
        return iBlankingText;
    else
        return EmptyItemText();
    }

EXPORT_C void CAknPasswordSettingItem::EditItemL( TBool /* aCalledFromMenu */)
    {
    _AKNTRACE_FUNC_ENTER;
    const TPtrC oldPassword = ExternalText();
    TPtrC settingName = SettingName();

    // Allocate a new password to the length of the internal buffer
    HBufC* newPasswordBuf = HBufC::NewLC( InternalTextPtr().MaxLength() );
    TPtr newPassword( newPasswordBuf->Des() );

    CAknSettingPage* dlg = 0;

    switch ( iPasswordMode )
        {
        case EAlpha:
            dlg = new( ELeave )CAknAlphaPasswordSettingPage(
                &settingName,
                SettingNumber(),
                EditorControlType(),
                SettingEditorResourceId(),
                SettingPageResourceId(),
                newPassword,
                oldPassword );

            break;

        case ENumeric:
            dlg = new( ELeave )CAknNumericPasswordSettingPage(
                &settingName,
                SettingNumber(),
                EditorControlType(),
                SettingEditorResourceId(),
                SettingPageResourceId(),
                newPassword,
                oldPassword );
            break;

        default:
            __ASSERT_ALWAYS(0, Panic(EAknPanicSettingItemListInvalidPasswordMode ) );
            break;
        }

    SetSettingPage( dlg );
    SettingPage()->SetSettingPageObserver(this);

    if(ProtectionState() == CAknSettingItem::ESettingItemViewOnly)
        SettingPage()->SetEditState(EFalse);

    // Copy the new password text in if return value is ETrue
    if ( SettingPage()->ExecuteLD(CAknSettingPage::EUpdateWhenChanged) )
        InternalTextPtr().Copy( newPassword );

    SetSettingPage( 0 );

    CleanupStack::PopAndDestroy(); // newPasswordBuf

    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CAknPasswordSettingItem::CAknSettingItem_Reserved()
    {
    };

// ---------------------------------------
// CAknVolumeSettingItem
//
//----------------------------------------

EXPORT_C CAknVolumeSettingItem::CAknVolumeSettingItem( TInt aIdentifier, TInt& aVolume ):
    CAknSettingItem(aIdentifier), iExternalVolume( aVolume )
    {
    }

EXPORT_C void CAknVolumeSettingItem::StoreL()
    {
    // Copy the internal to the external
    iExternalVolume = iInternalVolume;
    }

EXPORT_C void CAknVolumeSettingItem::LoadL()
    {
    iInternalVolume = iExternalVolume;
    }

EXPORT_C const TDesC& CAknVolumeSettingItem::SettingTextL()
    {
    return KAknSettingItemSingleSpace;
    }

EXPORT_C void CAknVolumeSettingItem::EditItemL( TBool /* aCalledFromMenu */)
    {
    _AKNTRACE_FUNC_ENTER;

    TPtrC settingName = SettingName();

    CAknVolumeSettingPage* dlg = new( ELeave )CAknVolumeSettingPage(
        &settingName,
        SettingNumber(),
        EditorControlType(),
        SettingEditorResourceId(),
        SettingPageResourceId(),
        InternalVolumeValue() );
    SetSettingPage( dlg );
    SettingPage()->SetSettingPageObserver(this);

    if(ProtectionState() == CAknSettingItem::ESettingItemViewOnly)
        SettingPage()->SetEditState(EFalse);

    SettingPage()->ExecuteLD(CAknSettingPage::EUpdateWhenChanged);
    SetSettingPage(0);
    UpdateListBoxTextL(); // update bitmap

    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C TInt& CAknVolumeSettingItem::InternalVolumeValue()
    {
    return iInternalVolume;
    }

/**
* This method is used to generate an appropriate bitmap for the current internal value
*
*/
EXPORT_C CFbsBitmap* CAknVolumeSettingItem::CreateBitmapL()
    {
    _AKNTRACE_FUNC_ENTER;

    CGulIcon* icon = NULL;
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, SettingPageResourceId() );

    TInt number= reader.ReadInt16();
    TPtrC settingText = reader.ReadTPtrC();
    TPtrC hintText = reader.ReadTPtrC();
    TInt cba = reader.ReadInt32();
    TInt menuBarId = reader.ReadInt32();
    TInt controlType = reader.ReadInt16();
    TInt editorResourceId = reader.ReadInt32();
    CleanupStack::PopAndDestroy(); // reader

    CCoeEnv::Static()->CreateResourceReaderLC( reader, editorResourceId );

    TInt style = reader.ReadInt16();

    if ( style == EDynRangeSettingsVolumeControl )
        {
        TInt value = reader.ReadInt16();
        TPtrC bmpFile=reader.ReadTPtrC();
        TInt bmpId=reader.ReadInt16();
        TInt bmpMask=reader.ReadInt16();
        TInt min= reader.ReadInt16();
        TInt max = reader.ReadInt16();

        icon = CAknVolumeControl::CreateSetDynRangeStyleListBoxIconL( InternalVolumeValue(),min,max );
        }
    else
        {
        icon = CAknVolumeControl::CreateSetStyleListBoxIconL( InternalVolumeValue() );
        }
    CleanupStack::PopAndDestroy(); // reader


    CFbsBitmap* returnedBitmap = SetIconMaskAndReturnBitmap( icon ); // ownership of icon transfered,

    _AKNTRACE_FUNC_EXIT;
    return returnedBitmap; // and this transfers ownership to caller
    }

EXPORT_C void CAknVolumeSettingItem::CAknSettingItem_Reserved()
    {
    };

// ---------------------------------------
// CAknSliderSettingItem
//
//----------------------------------------

EXPORT_C CAknSliderSettingItem::CAknSliderSettingItem( TInt aIdentifier, TInt& aSliderValue ):
    CAknSettingItem(aIdentifier), iExternalSliderValue( aSliderValue )
    {
    }

EXPORT_C void CAknSliderSettingItem::StoreL()
    {
    // Copy the internal to the external
    iExternalSliderValue = iInternalSliderValue;
    }

EXPORT_C void CAknSliderSettingItem::LoadL()
    {
    iInternalSliderValue = iExternalSliderValue;
    }

EXPORT_C const TDesC& CAknSliderSettingItem::SettingTextL()
    {
    return KAknSettingItemSingleSpace;
    }


EXPORT_C TInt& CAknSliderSettingItem::InternalSliderValue()
    {
    return iInternalSliderValue;
    }

EXPORT_C void CAknSliderSettingItem::EditItemL( TBool /* aCalledFromMenu */)
    {
    CreateAndExecuteSettingPageL();
    }

EXPORT_C void CAknSliderSettingItem::CreateAndExecuteSettingPageL()
    {
    _AKNTRACE_FUNC_ENTER;

    CAknSettingPage* dlg = CreateSettingPageL();

    SetSettingPage( dlg );
    SettingPage()->SetSettingPageObserver(this);

    if(ProtectionState() == CAknSettingItem::ESettingItemViewOnly)
        SettingPage()->SetEditState(EFalse);

    SettingPage()->ExecuteLD(CAknSettingPage::EUpdateWhenChanged);
    SetSettingPage(0);
    UpdateListBoxTextL();

    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C CAknSettingPage* CAknSliderSettingItem::CreateSettingPageL()
    {
    TPtrC text = SettingName();
    return new( ELeave )CAknSliderSettingPage(&text,SettingNumber(),EAknCtSlider,
                                              SettingEditorResourceId(), SettingPageResourceId(), iInternalSliderValue);
    }


/**
* This method is used to generate an appropriate bitmap for the current internal value
*
*/
EXPORT_C CFbsBitmap* CAknSliderSettingItem::CreateBitmapL()
    {
    _AKNTRACE_FUNC_ENTER;
    TInt editorResource = SettingEditorResourceId();
    if ( ( editorResource == 0 ) && ( SettingPageResourceId() != 0 ) )
        {
        TInt editorType;
        CAknSettingPage::GetEditorResourceInfoL( SettingPageResourceId(), editorType, editorResource );
        __ASSERT_ALWAYS( editorType == EAknCtSlider, Panic( EAknPanicSettingItemListInconsistentControlType ) );
        }
    __ASSERT_ALWAYS( editorResource , Panic( EAknPanicSettingItemListInsufficientResource ) );


    CGulIcon* icon = CAknSlider::CreateSetStyleListBoxIconL( InternalSliderValue(), editorResource  );
    CFbsBitmap* returnedBitmap = SetIconMaskAndReturnBitmap( icon ); // ownership of icon transfered,

    _AKNTRACE_FUNC_EXIT;
    return returnedBitmap; // and this transfers ownership to caller
    }

EXPORT_C void CAknSliderSettingItem::CAknSettingItem_Reserved()
    {
    };

// ---------------------------------------
// CAknTimeOrDateSettingItem
//
//----------------------------------------

EXPORT_C CAknTimeOrDateSettingItem::CAknTimeOrDateSettingItem( TInt aIdentifier, enum CAknTimeOrDateSettingItem::TAknTimeOrDateSettingItemMode aTimeOrDateMode, TTime& aTime ):
    CAknSettingItem(aIdentifier), iExternalTime( aTime ), iInternalTextPtr(0,0), iTimeFormatPtr(0,0), iTimeOrDateMode (aTimeOrDateMode )
    {
    }


EXPORT_C CAknTimeOrDateSettingItem::~CAknTimeOrDateSettingItem()
    {
    delete iTimeFormat;
    delete iInternalText;
    }


/**
*
* Complete the construction
*
*/

EXPORT_C void CAknTimeOrDateSettingItem::CompleteConstructionL()
    {
    _AKNTRACE_FUNC_ENTER;
    // Prepare the date buffer
    iInternalText = HBufC::NewL(KAknSettingItemTimeBufferLength);
    // and the format buffer
    // Set up according to default

    delete iTimeFormat;
    iTimeFormat = NULL;
    switch ( iTimeOrDateMode )
        {
        case ETime:
            iTimeFormat = CCoeEnv::Static()->AllocReadResourceL( R_QTN_TIME_USUAL_WITH_ZERO );
            break;

        case EDate:
            iTimeFormat = CCoeEnv::Static()->AllocReadResourceL( R_QTN_DATE_USUAL_WITH_ZERO );
            break;

        default:
            __ASSERT_ALWAYS(0, Panic(EAknPanicSettingItemListInvalidDateMode) );
            break;

        }

    iTimeFormatPtr.Set(iTimeFormat->Des());

    _AKNTRACE_FUNC_EXIT;
    }


EXPORT_C void CAknTimeOrDateSettingItem::StoreL()
    {
    // Copy the internal to the external
    iExternalTime = iInternalTime;
    }

EXPORT_C void CAknTimeOrDateSettingItem::LoadL()
    {
    iInternalTime = iExternalTime;
    }

EXPORT_C const TDesC& CAknTimeOrDateSettingItem::SettingTextL()
    {

    // set the text ptr again
    iInternalTextPtr.Set(iInternalText->Des());
    iInternalTime.FormatL(iInternalTextPtr, TimeFormatString());
    AknTextUtils::DisplayTextLanguageSpecificNumberConversion(iInternalTextPtr);
    return iInternalTextPtr;
    }

EXPORT_C void CAknTimeOrDateSettingItem::SetTimeFormatStringL( const TDesC& aTimeFormat )
    {
    delete iTimeFormat;
    iTimeFormat = 0;
    iTimeFormat = aTimeFormat.AllocL();
    // Use Set so that the whole TPtr is just overwritten - and gets a new buffer
    iTimeFormatPtr.Set(iTimeFormat->Des() );
    }

EXPORT_C const TPtrC CAknTimeOrDateSettingItem::TimeFormatString()
    {
    return TPtrC(iTimeFormatPtr);
    }


EXPORT_C void CAknTimeOrDateSettingItem::EditItemL( TBool /* aCalledFromMenu */)
    {
    _AKNTRACE_FUNC_ENTER;
    TPtrC text = SettingName();
    CAknSettingPage* dlg = 0;

    switch ( iTimeOrDateMode )
        {
        case ETime:
            dlg = new( ELeave )CAknTimeSettingPage(
                &text,
                SettingNumber(),
                EditorControlType(),
                SettingEditorResourceId(),
                SettingPageResourceId(),
                iInternalTime);

            break;

        case EDate:
            dlg = new( ELeave )CAknDateSettingPage(
                &text,
                SettingNumber(),
                EditorControlType(),
                SettingEditorResourceId(),
                SettingPageResourceId(),
                iInternalTime);
            break;

        default:
            __ASSERT_ALWAYS(0, Panic(EAknPanicSettingItemListInvalidDateMode) );
            break;
        }

    SetSettingPage( dlg );
    SettingPage()->SetSettingPageObserver(this);

    if(ProtectionState() == CAknSettingItem::ESettingItemViewOnly)
        SettingPage()->SetEditState(EFalse);

    SettingPage()->ExecuteLD(CAknSettingPage::EUpdateWhenChanged);
    SetSettingPage(0);

    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CAknTimeOrDateSettingItem::CAknSettingItem_Reserved()
    {
    };


// ---------------------------------------
// CAknTimeOffsetSettingItem
//
//----------------------------------------

EXPORT_C CAknTimeOffsetSettingItem::CAknTimeOffsetSettingItem( TInt aIdentifier, TTimeIntervalSeconds& aTime ):
    CAknSettingItem(aIdentifier), iExternalTime( aTime ), iInternalTextPtr(0,0), iTimeFormatPtr(0,0)
    {
    }


EXPORT_C CAknTimeOffsetSettingItem::~CAknTimeOffsetSettingItem()
    {
    delete iTimeFormat;
    delete iInternalText;
    }


/**
*
* Complete the construction
*
*/

EXPORT_C void CAknTimeOffsetSettingItem::CompleteConstructionL()
    {
    _AKNTRACE_FUNC_ENTER;
    // Prepare the date buffer
    iInternalText = HBufC::NewL(KAknSettingItemTimeBufferLength);
    // and the format buffer
    // Set up according to default

    delete iTimeFormat;
    iTimeFormat = NULL;

    iTimeFormat = CCoeEnv::Static()->AllocReadResourceL( R_QTN_TIME_DURAT_SHORT );

    iTimeFormatPtr.Set(iTimeFormat->Des());

    _AKNTRACE_FUNC_EXIT;
    }


EXPORT_C void CAknTimeOffsetSettingItem::StoreL()
    {
    // Copy the internal to the external
    iExternalTime = iInternalTime;
    }

EXPORT_C void CAknTimeOffsetSettingItem::LoadL()
    {
    iInternalTime = iExternalTime;
    }

EXPORT_C const TDesC& CAknTimeOffsetSettingItem::SettingTextL()
    {
    _AKNTRACE_FUNC_ENTER;
    // set the text ptr again
    TBool minus = EFalse;

    TInt timeInSeconds = iInternalTime.Int();
    if (timeInSeconds<0)
        {
        minus = ETrue;
        timeInSeconds = -timeInSeconds;
        }

    TTimeIntervalHours hours = (timeInSeconds - timeInSeconds%3600)/3600;
    TTimeIntervalMinutes minutes = (timeInSeconds%3600 - timeInSeconds%60)/60;
    TTimeIntervalSeconds seconds = timeInSeconds%60;

    TTime time(0);
    time += hours;
    time += minutes;
    time += seconds;

    HBufC* buf;
    buf = HBufC::NewL(KAknSettingItemTimeBufferLength);
    CleanupStack::PushL(buf);

    TPtr bufPtr(0,0);

    bufPtr.Set(buf->Des());

    time.FormatL(bufPtr, TimeFormatString());
    AknTextUtils::DisplayTextLanguageSpecificNumberConversion(bufPtr);

    iInternalTextPtr.Set(iInternalText->Des());

    if (minus)
        {
        iInternalTextPtr = KAknSettingItemMinus;
        }
    else
        {
        iInternalTextPtr = KAknSettingItemPlus;
        }
    iInternalTextPtr += KAknSettingItemSingleSpace;
    iInternalTextPtr += bufPtr;
    CleanupStack::Pop(); //buf

    delete buf;

    _AKNTRACE_FUNC_EXIT;
    return iInternalTextPtr;
    }

EXPORT_C void CAknTimeOffsetSettingItem::SetTimeFormatStringL( const TDesC& aTimeFormat )
    {
    _AKNTRACE( "[%s][%s][%d]", "CAknTimeOffsetSettingItem", __FUNCTION__, __LINE__ );
    delete iTimeFormat;
    iTimeFormat = 0;
    iTimeFormat = aTimeFormat.AllocL();
    // Use Set so that the whole TPtr is just overwritten - and gets a new buffer
    iTimeFormatPtr.Set(iTimeFormat->Des() );
    }

EXPORT_C const TPtrC CAknTimeOffsetSettingItem::TimeFormatString()
    {
    return TPtrC(iTimeFormatPtr);
    }


EXPORT_C void CAknTimeOffsetSettingItem::EditItemL( TBool /* aCalledFromMenu */)
    {
    _AKNTRACE_FUNC_ENTER;
    TPtrC text = SettingName();
    CAknSettingPage* dlg = 0;

    dlg = new( ELeave )CAknTimeOffsetSettingPage(
        &text,
        SettingNumber(),
        EditorControlType(),
        SettingEditorResourceId(),
        SettingPageResourceId(),
        iInternalTime);
    //interval);

    SetSettingPage( dlg );
    SettingPage()->SetSettingPageObserver(this);

    if(ProtectionState() == CAknSettingItem::ESettingItemViewOnly)
        SettingPage()->SetEditState(EFalse);

    SettingPage()->ExecuteLD(CAknSettingPage::EUpdateWhenChanged);
    SetSettingPage(0);

    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CAknTimeOffsetSettingItem::CAknSettingItem_Reserved()
    {
    };


// ---------------------------------------
// CAknIpFieldSettingItem
//
//----------------------------------------

EXPORT_C CAknIpFieldSettingItem::CAknIpFieldSettingItem( TInt aIdentifier, TInetAddr& aIpAddress ):
    CAknSettingItem(aIdentifier), iExternalIpAddress( aIpAddress ), iInternalTextPtr(0,0)
    {
    }


EXPORT_C CAknIpFieldSettingItem::~CAknIpFieldSettingItem()
    {
    delete iInternalText;
    }


/**
*
* Complete the construction
*
*/

EXPORT_C void CAknIpFieldSettingItem::CompleteConstructionL()
    {
    // Allocate the ip text buffer
    iInternalText = HBufC::NewL(KAknSettingItemIpTextBufferLength);
    }


EXPORT_C void CAknIpFieldSettingItem::StoreL()
    {
    // Copy the internal to the external
    iExternalIpAddress = iInternalIpAddress;
    }

EXPORT_C void CAknIpFieldSettingItem::LoadL()
    {
    iInternalIpAddress = iExternalIpAddress;
    }

EXPORT_C const TDesC& CAknIpFieldSettingItem::SettingTextL()
    {
    // set the text ptr again
    iInternalTextPtr.Set(iInternalText->Des());

    if ( iInternalIpAddress.IsUnspecified() )
        {
        iInternalTextPtr.Copy(KAknSettingItemEmptyIpAddress);
        }
    else
        {
        iInternalIpAddress.Output(iInternalTextPtr);
        }
    return iInternalTextPtr;
    }


EXPORT_C void CAknIpFieldSettingItem::EditItemL( TBool /* aCalledFromMenu */)
    {
    _AKNTRACE_FUNC_ENTER;
    TPtrC text = SettingName();
    CAknSettingPage* dlg = 0;

    dlg = new( ELeave )CAknIpFieldSettingPage(
        &text,
        SettingNumber(),
        EditorControlType(),
        SettingEditorResourceId(),
        SettingPageResourceId(),
        iInternalIpAddress);

    SetSettingPage( dlg );
    SettingPage()->SetSettingPageObserver(this);

    if(ProtectionState() == CAknSettingItem::ESettingItemViewOnly)
        SettingPage()->SetEditState(EFalse);

    SettingPage()->ExecuteLD(CAknSettingPage::EUpdateWhenChanged);
    SetSettingPage(0);

    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CAknIpFieldSettingItem::CAknSettingItem_Reserved()
    {
    };



//
//
EXPORT_C CAknEnumeratedItemBase::CAknEnumeratedItemBase( TInt aEnumerationValue, TAny* aValue ):
    iEnumerationValue( aEnumerationValue ), iValue ( aValue )
    {
    }

EXPORT_C CAknEnumeratedItemBase::~CAknEnumeratedItemBase()
    {
    }

EXPORT_C TInt CAknEnumeratedItemBase::EnumerationValue() const
    {
    return iEnumerationValue;
    }

EXPORT_C void CAknEnumeratedItemBase::SetEnumerationValue( TInt aNewEnumerationValue )
    {
    _AKNTRACE( "[%s][%s] aNewEnumerationValue = %d", "CAknEnumeratedItemBase",
            __FUNCTION__, aNewEnumerationValue );
    iEnumerationValue = aNewEnumerationValue;
    }

EXPORT_C TAny* CAknEnumeratedItemBase::Value() const
    {
    return iValue;
    }

EXPORT_C void CAknEnumeratedItemBase::SetValue( TAny* aNewValue )
    {
    iValue = aNewValue;
    }


//
// Implementation of CAknEnumeratedTextSettingItem
//
//

#define EMPTY_LIST (NumberOfItems() == 0)

EXPORT_C CAknEnumeratedTextSettingItem::CAknEnumeratedTextSettingItem(
    TInt aIdentifier ):        CAknSettingItem(aIdentifier)
    {
    }

EXPORT_C CAknEnumeratedTextSettingItem::~CAknEnumeratedTextSettingItem()
    {
    DeleteAndZeroPrimaryArrays();
    delete iSettingPageText;
    }

/**
*
* Complete the construction using the additional resource id.
* This reads in the two sets of texts : texts for for the setting item list display
* and texts for any setting page that may be raised.
*
* This also sets the empty listbox text
*/
EXPORT_C void CAknEnumeratedTextSettingItem::CompleteConstructionL( )
    {
    _AKNTRACE_FUNC_ENTER;

    if ( AssociatedResourceId() )
        {
	    TResourceReader reader;
	    CEikonEnv::Static()->CreateResourceReaderLC( reader, AssociatedResourceId() );

	    iTextPopupFlags = reader.ReadInt16();        // Flags

	    iEnumeratedTextArrayResourceId = reader.ReadInt32(); // LLINK to values
	    iPoppedUpTextArrayResourceId = reader.ReadInt32(); // optional LLINK to values

	    /* Throw away */  reader.ReadInt32();                // For future needs

	    CleanupStack::PopAndDestroy(); // reader

	    // Read in the texts to be used in the setting item list
	    CEikonEnv::Static()->CreateResourceReaderLC( reader, iEnumeratedTextArrayResourceId );

	    TInt numberOfItems = reader.ReadInt16();        // item count

	    // Construct the array
	    iEnumeratedTextArray = new (ELeave) CArrayPtrFlat<CAknEnumeratedText>( KAknSettingItemArrayGranularity );
	    iPoppedUpTextArray = new (ELeave) CArrayPtrFlat<HBufC>(KAknSettingItemArrayGranularity);

	    TInt index = 0;
	    //Loop through all the texts
	    for ( index=0; index < numberOfItems ; ++index )
	        {
	        TInt value = reader.ReadInt16();
	        TPtrC text = reader.ReadTPtrC();  // LTEXT name;
	        HBufC* thisText = text.AllocLC(); // pushed thisText
	        TPtr thisTextDes = thisText->Des();
	        AknTextUtils::DisplayTextLanguageSpecificNumberConversion(thisTextDes);
	        CAknEnumeratedText* enumeratedText = new (ELeave) CAknEnumeratedText( value, thisText);
	        CleanupStack::Pop(); // thisText
	        CleanupStack::PushL( enumeratedText );
	        iEnumeratedTextArray->AppendL( enumeratedText );
	        CleanupStack::Pop(); // enumeratedText
	        }

	    CleanupStack::PopAndDestroy(); // reader

	    // If the "Popped Up" resource is non-zero, then read it in too
	    if ( iPoppedUpTextArrayResourceId )
	        {
	        // Read in the texts to be used in the setting item list
	        CEikonEnv::Static()->CreateResourceReaderLC( reader, iPoppedUpTextArrayResourceId );

	        //        Read the item count
	        TInt numberOfItems = reader.ReadInt16();        // item count

	        //Loop through all the texts
	        for ( index=0; index < numberOfItems ; ++index )
	            {
	            TPtrC text = reader.ReadTPtrC();// LTEXT name;
	            if ( text.Length() > 0 )
	                {
	                HBufC* thisText = text.AllocLC();
	                TPtr thisTextDes = thisText->Des();
	                AknTextUtils::DisplayTextLanguageSpecificNumberConversion(thisTextDes);

	                iPoppedUpTextArray->AppendL(thisText);
	                CleanupStack::Pop(); // thisText
	                }
	            else
	                iPoppedUpTextArray->AppendL(0); // zero pointers for the zero length texts
	            }

	        CleanupStack::PopAndDestroy(); // reader

	        }
        }

    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C CArrayPtr<CAknEnumeratedText>* CAknEnumeratedTextSettingItem::EnumeratedTextArray() const
    {
    return iEnumeratedTextArray;
    }

EXPORT_C CArrayPtr<HBufC>* CAknEnumeratedTextSettingItem::PoppedUpTextArray() const
    {
    return iPoppedUpTextArray;
    }

/**
* Set the enumerated arrays.
* Ownership of these arrays and their contents is wholly given over to the setting item
* object.
*
*/
EXPORT_C void CAknEnumeratedTextSettingItem::SetEnumeratedTextArrays( CArrayPtr<CAknEnumeratedText>* aEnumeratedTextArray,
                                                                      CArrayPtr<HBufC>* aPoppedUpTextArray )
    {
    __ASSERT_ALWAYS( aEnumeratedTextArray, Panic( EAknPanicSettingItemListInvalidPointer ) );
    __ASSERT_ALWAYS( aPoppedUpTextArray, Panic( EAknPanicSettingItemListInvalidPointer ) );
    DeleteAndZeroPrimaryArrays();
    iEnumeratedTextArray = aEnumeratedTextArray;
    iPoppedUpTextArray = aPoppedUpTextArray;
    }

/**
* The virtual method LoadL() is called as the base class's best guess as to what needs to be
* done at this point.
*/
EXPORT_C void CAknEnumeratedTextSettingItem::HandleTextArrayUpdateL()
    {
    LoadL();
    }

// Construct the Text Popup with the Setting Page texts.
//This may be different from the values
// on the setting item list
EXPORT_C void CAknEnumeratedTextSettingItem::SetSettingPageTextL()
    {
    _AKNTRACE_FUNC_ENTER;

    delete iSettingPageText;
    iSettingPageText = 0;
    iSettingPageText = new(ELeave) CDesCArrayFlat(KAknSettingItemArrayGranularity);

    TBool textIsSet;
    TInt numberOfItems = NumberOfItems();
    for ( TInt index = 0; index < numberOfItems ; index++ )
        {
        textIsSet = EFalse;
        HBufC* poppedUpText;
        if ( index < iPoppedUpTextArray->Count() ) // Note popped up text array may be shorter than numberOfItems
            {
            if ( (poppedUpText = iPoppedUpTextArray->At( index ) ) != 0 )
                {
                iSettingPageText->AppendL( poppedUpText->Des() );
                textIsSet = ETrue;
                }
            }

        if (!textIsSet)
            iSettingPageText->AppendL( iEnumeratedTextArray->At( index )->Value()->Des() );
        }

    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C CDesCArray* CAknEnumeratedTextSettingItem::SettingPageTextArray() const
    {
    return iSettingPageText;
    }


EXPORT_C TInt CAknEnumeratedTextSettingItem::NumberOfItems() const
    {
    if ( iEnumeratedTextArray )
        return iEnumeratedTextArray->Count();
    else
        return 0;
    }


/**
* Find the index of the enumeration that matches the input value
* -1 is returned if the value is not in the enumerated text array
*
*/
EXPORT_C TInt CAknEnumeratedTextSettingItem::IndexFromValue( TInt aInputValue ) const
    {
    // Find this value in the enumerated items
    TInt indexToFind = -1;
    TInt numItems = EnumeratedTextArray()->Count();
    for ( TInt index = 0; index < numItems ; index++ )
        {
        if ( aInputValue == EnumeratedTextArray()->At( index )->EnumerationValue() )
            {
            indexToFind = index;
            break;
            }
        }
    _AKNTRACE( "[%s][%s] return value = %d", "CAknEnumeratedTextSettingItem",
            __FUNCTION__, indexToFind );
    return indexToFind;
    }

void CAknEnumeratedTextSettingItem::DeleteAndZeroPrimaryArrays()
    {
    if ( iEnumeratedTextArray )
        {
        iEnumeratedTextArray->ResetAndDestroy();
        delete iEnumeratedTextArray;
        iEnumeratedTextArray = 0;
        }
    if ( iPoppedUpTextArray )
        {
        iPoppedUpTextArray->ResetAndDestroy();
        delete iPoppedUpTextArray;
        iPoppedUpTextArray = 0;
        }
    }

EXPORT_C void CAknEnumeratedTextSettingItem::CAknSettingItem_Reserved()
    {
    };


//
// Implementation of CAknEnumeratedTextPopupSettingItem
//


EXPORT_C CAknEnumeratedTextPopupSettingItem::CAknEnumeratedTextPopupSettingItem(
    TInt aIdentifier,
    TInt& aValue ):
    CAknEnumeratedTextSettingItem(aIdentifier), iExternalValue( aValue )
    {
#ifdef __DEBUG__
    __ASSERT_DEBUG( sizeof( CAknEnumeratedTextPopupSettingItem ) == 0x0000008c , Panic( EAknPanicSettingItemListNotBinaryCompatible ) );
#endif
    }

EXPORT_C CAknEnumeratedTextPopupSettingItem::~CAknEnumeratedTextPopupSettingItem()
    {
    delete iQueryValue;
    delete iQueryTextArray; // This does not own the objects it points to
    }

/**
*
* Complete the construction using the additional resource id.
* This reads in the two binary texts.
* Note that Load() will not have been called yet, so the setting is still uninitialized in terms of its data content
* after this has finished. Otherwise, the instance should be ready.
*
*/

EXPORT_C void CAknEnumeratedTextPopupSettingItem::CompleteConstructionL( )
    {
    _AKNTRACE_FUNC_ENTER;
    CAknEnumeratedTextSettingItem::CompleteConstructionL();
    _AKNTRACE_FUNC_EXIT;
    }


EXPORT_C void CAknEnumeratedTextPopupSettingItem::StoreL()
    {
    // Copy the internal to the external
    iExternalValue = iInternalValue;
    }

EXPORT_C void CAknEnumeratedTextPopupSettingItem::LoadL()
    {
    iInternalValue = iExternalValue;

    // Find this value in the enumerated items
    iSelectedIndex = IndexFromValue( iInternalValue );

    if (iSelectedIndex == -1 && !EMPTY_LIST)
        {
        // There may be some sort of error here
        // Depends on if there is a requirement to support "nothing selected"
        __ASSERT_ALWAYS(0, Panic(EAknPanicSettingItemListInvalidEnumeratedValue) );
        }
    }


EXPORT_C const TDesC& CAknEnumeratedTextPopupSettingItem::SettingTextL()
    {
    if (EMPTY_LIST) return EmptyItemText();
    return *(EnumeratedTextArray()->At( iSelectedIndex )->Value());
    }

EXPORT_C MAknQueryValue* CAknEnumeratedTextPopupSettingItem::QueryValue() const
    {
    return iQueryValue;
    }

/**
* Launch the setting page for this setting.
*
*
*/
EXPORT_C void CAknEnumeratedTextPopupSettingItem::EditItemL( TBool /* aCalledFromMenu */)
    {
    _AKNTRACE_FUNC_ENTER;

    SetSettingPageTextL();
    CreateTextArrayL();

    CreateQueryValueL();
    CreateAndExecuteSettingPageL();

    UpdateInternalValuesL();
    UpdateListBoxTextL();

    _AKNTRACE_FUNC_EXIT;
    }

// Construct the Text Popup with the Setting Page texts.
//This may be different from the values
// on the setting item list
void CAknEnumeratedTextPopupSettingItem::SetSettingPageTextL()
    {
    CAknEnumeratedTextSettingItem::SetSettingPageTextL();
    }

void CAknEnumeratedTextPopupSettingItem::CreateTextArrayL()
    {
    delete iQueryTextArray;
    iQueryTextArray = 0;
    iQueryTextArray = CAknQueryValueTextArray::NewL();
    iQueryTextArray->SetArray( *(SettingPageTextArray()) );
    }

//Set the same datearray into all the values, and set initial index values
void CAknEnumeratedTextPopupSettingItem::CreateQueryValueL()
    {
    delete iQueryValue;
    iQueryValue = 0;
    iQueryValue = CAknQueryValueText::NewL();
    iQueryValue->SetArrayL(iQueryTextArray);
    if (!EMPTY_LIST)
        iQueryValue->SetCurrentValueIndex(iSelectedIndex);
    }

EXPORT_C void CAknEnumeratedTextPopupSettingItem::CreateAndExecuteSettingPageL()
    {
    _AKNTRACE_FUNC_ENTER;

    CAknSettingPage* dlg = CreateSettingPageL();
    CleanupStack::PushL(dlg);
    SetSettingPage( dlg );

    SettingPage()->SetSettingPageObserver(this);
    SetUpStandardSettingPageL();

    CleanupStack::Pop(dlg);

    if(ProtectionState() == CAknSettingItem::ESettingItemViewOnly)
        SettingPage()->SetEditState(EFalse);


    SettingPage()->ExecuteLD(CAknSettingPage::EUpdateWhenChanged);
    SetSettingPage(0);

    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C CAknSettingPage* CAknEnumeratedTextPopupSettingItem::CreateSettingPageL()
    {
    TPtrC settingName = SettingName();
    return new( ELeave )CAknPopupSettingPage( &settingName, SettingNumber(),
                                              EditorControlType(), SettingEditorResourceId(), SettingPageResourceId(),*iQueryValue);
    }

void CAknEnumeratedTextPopupSettingItem::UpdateInternalValuesL()
    {
    _AKNTRACE_FUNC_ENTER;

    if (!EMPTY_LIST)
        {
        iSelectedIndex = iQueryValue->CurrentValueIndex();
// Check if new value has been added
        if ( iSelectedIndex >= EnumeratedTextArray()->Count() )
            {
            // calculate the next enumeration value.
            TInt nextFreeEnum = FindNextEnumerationValue();
            // Create the new enumeration (number, text) object
            HBufC* newText = iQueryValue->CurrentValueTextLC();
            CAknEnumeratedText* newEnumeratedText = new (ELeave) CAknEnumeratedText( nextFreeEnum, newText );
            // Ownership of newText has been given to newEnumeratedText.
            CleanupStack::Pop(); // newText
            CleanupStack::PushL( newEnumeratedText );
            EnumeratedTextArray()->AppendL( newEnumeratedText );
            CleanupStack::Pop(); // newEnumeratedText
            iNumberOfItems++; // Now we have one more item
            }
        // Assert the tie between iNumberOfItems and iEnumeratedItemArray-Count()
        __ASSERT_DEBUG( (NumberOfItems() == EnumeratedTextArray()->Count()), Panic( EAknPanicSettingItemListArrayLengthsMisMatch ) );
        // Asserts on the in-range-ness of iSelectedIndex are done inside the array access:
        iInternalValue = EnumeratedTextArray()->At( iSelectedIndex )->EnumerationValue();
        }

    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CAknEnumeratedTextPopupSettingItem::SetExternalValue( TInt aNewValue )
    {
    iExternalValue = aNewValue;
    }

EXPORT_C void CAknEnumeratedTextPopupSettingItem::SetInternalValue( TInt aNewValue )
    {
    iInternalValue = aNewValue;
    }

EXPORT_C TInt CAknEnumeratedTextPopupSettingItem::ExternalValue() const
    {
    return iExternalValue;
    }

EXPORT_C TInt CAknEnumeratedTextPopupSettingItem::InternalValue() const
    {
    return iInternalValue;
    }

EXPORT_C void CAknEnumeratedTextPopupSettingItem::SetSelectedIndex( TInt aNewIndex )
    {
    iSelectedIndex = aNewIndex;
    }

/**
* Find the index of the enumeration that matches the input value
* -1 is returned if the value is not in the enumerated text array
*
*/
EXPORT_C TInt CAknEnumeratedTextPopupSettingItem::IndexFromValue( TInt aInputValue ) const
    {
    _AKNTRACE( "[%s][%s] aInputValue = %d", "CAknEnumeratedTextPopupSettingItem", __FUNCTION__, aInputValue );
    return CAknEnumeratedTextSettingItem::IndexFromValue( aInputValue );
    }

EXPORT_C CArrayPtr<CAknEnumeratedText>* CAknEnumeratedTextPopupSettingItem::EnumeratedTextArray() const
    {
    return CAknEnumeratedTextSettingItem::EnumeratedTextArray();
    }

EXPORT_C CArrayPtr<HBufC>* CAknEnumeratedTextPopupSettingItem::PoppedUpTextArray() const
    {
    return CAknEnumeratedTextSettingItem::PoppedUpTextArray();
    }

TInt CAknEnumeratedTextPopupSettingItem::FindNextEnumerationValue() const
    {
    _AKNTRACE_FUNC_ENTER;
    // loop through the enumerated texts and record the highest enumeration value
    TInt highestEnumValue = -1; // value chosen so as to return 0 if empty array
    TInt enumInArray;
    TInt count = EnumeratedTextArray()->Count();
    for ( TInt index = 0; index < count; ++index )
        {
        enumInArray = EnumeratedTextArray()->At(index)->EnumerationValue();
        if (highestEnumValue < enumInArray )
            highestEnumValue = enumInArray;
        }

    _AKNTRACE_FUNC_EXIT;
    return (++highestEnumValue);
    }

EXPORT_C void CAknEnumeratedTextPopupSettingItem::CAknSettingItem_Reserved()
    {
    };

// ==============================================================================
// CAknBinaryPopupSettingItem
// ==============================================================================


EXPORT_C CAknBinaryPopupSettingItem::CAknBinaryPopupSettingItem(
    TInt aIdentifier,
    TBool& aBinaryValue ):
    CAknEnumeratedTextPopupSettingItem(aIdentifier, (TInt&)aBinaryValue )
    {
    }

/**
*
* Complete the construction using the additional resource id.
* This reads in the two binary texts This is called from within ConstructXXXL routines.
* Note that Load() will not have been called yet, so the setting is still uninitialized in terms of its data content
* after this has finished. Otherwise, the instance should be ready.
*
*/

EXPORT_C void CAknBinaryPopupSettingItem::CompleteConstructionL( )
    {
    _AKNTRACE_FUNC_ENTER;

    CAknEnumeratedTextPopupSettingItem::CompleteConstructionL();

    __ASSERT_DEBUG( EnumeratedTextArray() , Panic(EAknPanicSettingItemListConstructionNotComplete) );
    // that there are 2 values
    __ASSERT_DEBUG( EnumeratedTextArray()->Count() == 2 , Panic(EAknPanicSettingItemListWrongNumberOfValues) );
    // that the values are 0 and 1
    __ASSERT_DEBUG( IndexFromValue( 0 ) != -1 , Panic(EAknPanicSettingItemListRequiredValueNotInArray) );
    __ASSERT_DEBUG( IndexFromValue( 1 ) != -1 , Panic(EAknPanicSettingItemListRequiredValueNotInArray) );

    _AKNTRACE_FUNC_EXIT;
    }


EXPORT_C void CAknBinaryPopupSettingItem::StoreL()
    {
    SetExternalValue( InternalValue() );
    }


EXPORT_C void CAknBinaryPopupSettingItem::LoadL()
    {
    // Regularize the external value to 0 or 1
    TInt tempExternalValue = 0;
    if ( ExternalValue() )
        tempExternalValue = 1;

    SetExternalValue( tempExternalValue );

    // This then sets the internal value
    CAknEnumeratedTextPopupSettingItem::LoadL();
    }

/**
* Launch the setting page for this setting.
*
*
*/
EXPORT_C void CAknBinaryPopupSettingItem::EditItemL( TBool aCalledFromMenu )
    {
    _AKNTRACE_FUNC_ENTER;

    // Use base class for the main functionality
    if ( aCalledFromMenu )
        {
        CAknEnumeratedTextPopupSettingItem::EditItemL( aCalledFromMenu );
        // Check if another value has been added.  We should not have to handle this in
        // Binary setting page
        // Note, however, that because of index discipline below, the 3rd item that might have
        // been added will not ever be selected. Only when the list is popped up again, will the user's
        // (ignored) choice be present
        __ASSERT_DEBUG( EnumeratedTextArray()->Count() == 2 , Panic(EAknPanicSettingItemListWrongNumberOfValues) );
        __ASSERT_DEBUG( InternalValue() < 2 , Panic(EAknPanicSettingItemListInvalidIndex) );
        }
    else if(ProtectionState() == ESettingItemViewOnly)
        {
        // Do not toggle!
        }
    else
        {

        // Toggle the value and update the listbox text
        if ( InternalValue() )
            SetInternalValue(0);
        else
            SetInternalValue(1);

        TInt index = IndexFromValue( InternalValue() );
        if (index >= 0 )
            SetSelectedIndex( index );
        else // put the seletion on the first in the list
            SetSelectedIndex( 0 );

        UpdateListBoxTextL();

        }

    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CAknBinaryPopupSettingItem::CAknSettingItem_Reserved()
    {
    };


/**
* This constructor merely initializes the empty string descriptor required for formatting the
* listbox text
*
*/
EXPORT_C CAknBigSettingItemBase::CAknBigSettingItemBase( TInt aIdentifier ): CAknSettingItem( aIdentifier ), iEmptyString( KNullDesC )
    {
    }

/**
* Just returns the pre-set empty string
*
*/
EXPORT_C const TDesC& CAknBigSettingItemBase::SettingTextL()
    {
    return iEmptyString;
    }

EXPORT_C void CAknBigSettingItemBase::CAknSettingItem_Reserved()
    {
    };

//========================================


EXPORT_C CAknSettingItemArray::CAknSettingItemArray(TInt aGranularity, TBool aIsNumbered, TInt aInitialOrdinal ) :
    CArrayPtrFlat<CAknSettingItem>( aGranularity ), iIsNumbered( aIsNumbered ), iInitialOrdinal( aInitialOrdinal )
    {
    }

EXPORT_C CAknSettingItemArray::~CAknSettingItemArray()
    {
    }

EXPORT_C TInt CAknSettingItemArray::MdcaCount() const
    {
    return VisibleCount();
    }

EXPORT_C TPtrC16 CAknSettingItemArray::MdcaPoint(TInt aVisibleIndex ) const
    {
    TInt indexToUse = ItemIndexFromVisibleIndex( aVisibleIndex );
    return ( (TPtrC)( *(At( indexToUse )->ListBoxText() ) ) );
    }


EXPORT_C void CAknSettingItemArray::SetVisibleCount( TInt aVisibleCount )
    {
    iVisibleCount = aVisibleCount;
    }

EXPORT_C void CAknSettingItemArray::RecalculateVisibleIndicesL()
    {
    _AKNTRACE_FUNC_ENTER;

    TInt count = Count();
    TInt visibleIndex = -1;
    for ( TInt index = 0; index < count; ++index )
        {
        CAknSettingItem* item = At( index );
        if ( !( item->IsHidden() ) )
            {
            visibleIndex++;
            item->SetVisibleIndex( visibleIndex );
            if ( !(iFlags & EAknSettingItemIncludeHiddenInOrdinal ) )
                item->SetOrdinal( iInitialOrdinal + visibleIndex );
            else
                item->SetOrdinal( iInitialOrdinal + index );

            item->UpdateListBoxTextL();
            }
        else
            {
            item->SetVisibleIndex( -1 );
            item->SetOrdinal( -1 );
            }
        }
    // The last index used gives the count (but add one first).
    SetVisibleCount( visibleIndex+1 );

    _AKNTRACE_FUNC_EXIT;

    }
EXPORT_C TInt CAknSettingItemArray::VisibleCount() const
    {
    return iVisibleCount;
    }

EXPORT_C TInt CAknSettingItemArray::ItemIndexFromVisibleIndex( TInt aVisibleIndex ) const
    {
    // go through item array until the one that returns the passed parameter is found
    TInt count = Count();
    for ( TInt index = 0; index < count; ++index )
        {
        if ( At( index )->VisibleIndex() == aVisibleIndex )
            return index;
        }
    return -1;
    }

EXPORT_C void CAknSettingItemArray::SetInitialOrdinal( TInt aInitialOrdinal )
    {
    iInitialOrdinal = aInitialOrdinal;
    }

EXPORT_C void CAknSettingItemArray::SetFlags( TInt aFlags )
    {
    iFlags = aFlags;
    }


// -------------------------------
// CAknSettingItemList
// -------------------------------

EXPORT_C CAknSettingItemList::CAknSettingItemList()
    {
    }

EXPORT_C CAknSettingItemList::~CAknSettingItemList()
    {
    delete iSettingItemListBox;

    if (iSettingItemArray)
        {
        iSettingItemArray->ResetAndDestroy();
        delete iSettingItemArray;
        }

    delete iSettingItemListTitle;
    }


EXPORT_C CCoeControl* CAknSettingItemList::ComponentControl(TInt /*aIndex*/) const
    {
    return iSettingItemListBox;
    }


EXPORT_C TInt CAknSettingItemList::CountComponentControls() const
    {
    return 1;
    }

/**
* Construct from resource using a new resource reader
*
*/
EXPORT_C void CAknSettingItemList::ConstructFromResourceL( TInt aResourceId )
    {
    _AKNTRACE_FUNC_ENTER;

    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC( reader, aResourceId );
    ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy(); // reader

    _AKNTRACE_FUNC_EXIT;
    }

/**
* This is the principal resource-reading Construct routine
*
*
*/
EXPORT_C void CAknSettingItemList::ConstructFromResourceL( TResourceReader& aReader )
    {
    _AKNTRACE_FUNC_ENTER;

    if ( &(Window()) == 0  )
        CreateWindowL();


    // Flags read first
    iFlags = aReader.ReadInt16();                // WORD flags

    TPtrC settingListTitle = aReader.ReadTPtrC();                // LTEXT title
    HBufC* newText = settingListTitle.AllocL();
    if (iSettingItemListTitle)
        delete( iSettingItemListTitle ); // after the AllocL succeeds
    iSettingItemListTitle = newText;

    iInitialOrdinal = aReader.ReadInt16();        // WORD initial_number

    // Create the listbox in the right style
    if ( IsNumberedStyle() )
        iSettingItemListBox = new(ELeave) CAknSettingNumberStyleListBox();
    else
        iSettingItemListBox = new(ELeave) CAknSettingStyleListBox();

    iSettingItemListBox->ConstructL( this, CEikListBox::ELeftDownInViewRect);

    TPoint pos = iEikonEnv->EikAppUi()->ClientRect().iTl;
    TSize size = iSettingItemListBox->MinimumSize();
    SetExtent( pos,size );


    // Set up the CBA
    iSettingItemListBox->CreateScrollBarFrameL(ETrue);
    iSettingItemListBox->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOn, CEikScrollBarFrame::EAuto);

    // The setting array
    iSettingItemArray= new(ELeave)CAknSettingItemArray(KAknSettingItemArrayGranularity, IsNumberedStyle(), iInitialOrdinal );

    // Transfer the flags to the item array
    iSettingItemArray->SetFlags( iFlags );
    // Make the icon array
    CArrayPtrFlat<CGulIcon>* iconArray = new(ELeave) CAknIconArray(KAknSettingItemArrayGranularity);
    CleanupStack::PushL( iconArray );

    // In case there is no empty text in resource, this can be set from resource.  In order
    // to get this only once, we can read the default empty text into an HBufC now

    HBufC* defaultEmptyText = iCoeEnv->AllocReadResourceLC(R_AVKON_SELEC_SETT_VAL_FIELD_NONE); // Pushed defaultEmptyText

    // Read the number of items and then loop
    const TInt numberOfItems = aReader.ReadInt16();                                // item count
    TInt id;
    for (TInt ii=0; ii < numberOfItems ; ++ii )
        {
        id = aReader.ReadInt16();                                                                // WORD identifier
        TPtrC settingName = aReader.ReadTPtrC();                                // LTEXT name;

        TInt settingPageResourceId = aReader.ReadInt32();                // LLINK setting_page_resource
        TInt editorControlType = aReader.ReadInt16();                        // WORD control type
        TInt settingEditorResourceId = aReader.ReadInt32();                // LLINK setting_editor_resource
        TInt associatedResourceId = aReader.ReadInt32();                // LLINK associated_resource
        TPtrC emptyText = aReader.ReadTPtrC();                                        // LTEXT empty_text
        TPtrC compulsoryText = aReader.ReadTPtrC();
        // Extension for future development
        /* reserved */ aReader.ReadInt32();

        // Call the factory for setting item
        CAknSettingItem* settingItem = CreateSettingItemL( id );
        if ( settingItem )
            {
            CleanupStack::PushL( settingItem );
            // If no empty text was read from resource, then supply it from the default
            if ( emptyText.Length() != 0 )
                settingItem->SetEmptyItemTextL( emptyText );
            else
                settingItem->SetEmptyItemTextL( *defaultEmptyText );

            settingItem->SetCompulsoryIndTextL( compulsoryText );
            settingItem->ConstructL(
                IsNumberedStyle(),
// This is just an initial provision for the ordinal value
// It may later one be adjusted for hidden items
                iInitialOrdinal + ii,
                settingName,
                iconArray,
                settingPageResourceId,
                editorControlType,
                settingEditorResourceId,
                associatedResourceId );

            settingItem->SetParentListBox( iSettingItemListBox );

            iSettingItemArray->AppendL( settingItem ); // Ownership is transferred
            CleanupStack::Pop(); // settingItem
            }
        }

    CleanupStack::PopAndDestroy(); // defaultEmptyText

    // Initial ordinal needed for dynamic numbering
    iSettingItemArray->SetInitialOrdinal( iInitialOrdinal );

    // Set up the visible indices in the listbox and update things
    HandleChangeInItemArrayOrVisibilityL();

    // Looks like we have no choice but to give ownership of this to the listbox
    // There is no flag as there is for the item data
    ListBox()->ItemDrawer()->FormattedCellData()->SetIconArrayL(iconArray);

    CleanupStack::Pop(); // iconArray now has ownership transferred

    CTextListBoxModel* model=ListBox()->Model();
    model->SetItemTextArray(iSettingItemArray);
    model->SetOwnershipType(ELbmDoesNotOwnItemArray); // Ownership retained by SettingItemList

    TRect mainpaneRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, mainpaneRect );
    iSettingItemListBox->SetRect(TRect(mainpaneRect.Size()));

    ListBox()->SetCurrentItemIndex(0);
    ListBox()->SetListBoxObserver(this);
    ListBox()->UpdateScrollBarsL();

    _AKNTRACE_FUNC_EXIT;
    }

/**
* This is an example implementation of this routine.  It shows the typical structure.  Nothing else besides the
* C++ constuction of objects conforming to CAknSettingItem should be done.
*
* It may be useful to retain the default constuction of an object with run time type of CAknSettingItem.  This will
* allow visibility of the data in the resource file at least.
*
*/
EXPORT_C CAknSettingItem* CAknSettingItemList::CreateSettingItemL( TInt identifier )
    {
    _AKNTRACE( "[%s][%s][%d].", "CAknSettingItemList", __FUNCTION__, __LINE__ );

    CAknSettingItem* settingItem;

    switch (identifier)
        {
        case 1:
            settingItem = new (ELeave) CAknSettingItem(identifier);
            return settingItem;


        default:
            settingItem = new (ELeave) CAknSettingItem(identifier);
            return settingItem;

        }
    }

EXPORT_C TKeyResponse CAknSettingItemList::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    _AKNTRACE( "[%s][%s][%d].", "CAknSettingItemList", __FUNCTION__, __LINE__ );
    // All events are sent to the listbox,
    if (iSettingItemListBox)
        return iSettingItemListBox->OfferKeyEventL( aKeyEvent, aType );
    else
        return EKeyWasNotConsumed;
    }

EXPORT_C void CAknSettingItemList::LoadSettingsL()// call Load() on each item in the MAknSettingItemArray.
    {
    TUint number = SettingItemArray()->Count();
    TUint index;
    for ( index = 0; index < number; index++ )
        {
        SettingItemArray()->At( index )->LoadL();
        }
    UpdateAllListBoxTextsL();
    }
EXPORT_C void CAknSettingItemList::StoreSettingsL() //  call StoreL() on each item in the MAknSettingItemArray
    {

    TUint number = SettingItemArray()->Count();
    for (TUint index = 0; index < number; index++ )
        {
        SettingItemArray()->At( index )->StoreL();
        }

    }
// Has an initial number (so that numbers can increment over several dialog pages, for instance )
EXPORT_C void CAknSettingItemList::SetIncludeHiddenInOrdinal( TBool aInclude )
    {
    _AKNTRACE( "[%s][%s] aInclude = %d", "CAknSettingItemList", __FUNCTION__, aInclude );
    if ( aInclude )
        iFlags |= EAknSettingItemIncludeHiddenInOrdinal;
    else
        iFlags &= (~EAknSettingItemIncludeHiddenInOrdinal);
    // Update the copy of the flags in the array
    if ( SettingItemArray() )
        SettingItemArray()->SetFlags( iFlags );
    }

/**
* Framework method for launching the setting page.
*
*/
EXPORT_C void CAknSettingItemList::EditItemL(TInt aIndex, TBool aCalledFromMenu )
    {
    _AKNTRACE_FUNC_ENTER;

    // Check if the setting page is locked
    if(SettingItemArray()->At(aIndex)->ProtectionState() ==
        CAknSettingItem::ESettingItemProtected)
        //show dialog
        {
        // R_QTN_SELEC_PROTECTED_SETTING
        HBufC* warningText =
            CCoeEnv::Static()->AllocReadResourceLC( R_QTN_SELEC_PROTECTED_SETTING );

        CAknWarningNote* warningNote = new (ELeave) CAknWarningNote;
        warningNote->ExecuteLD(warningText->Des());

        CleanupStack::PopAndDestroy(); // warningText
        }
    else
        {
        // launch the setting page index
        SettingItemArray()->At(aIndex)->EditItemL( aCalledFromMenu );
        iSettingItemListBox->View()->DrawItem( iSettingItemListBox->CurrentItemIndex() );
        }

    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C TBool CAknSettingItemList::IsNumberedStyle()
    {
    return ( iFlags & EAknSettingItemNumberedStyle );
    }

EXPORT_C CAknSettingItemArray* CAknSettingItemList::SettingItemArray() const
    {
    return ( iSettingItemArray );
    }

EXPORT_C CEikFormattedCellListBox* CAknSettingItemList::ListBox()
    {
    return ( iSettingItemListBox );
    }

EXPORT_C void CAknSettingItemList::HandleListBoxEventL(CEikListBox* aListBox, TListBoxEvent aEventType)
    {
    _AKNTRACE( "[%s][%s] aListBox = 0x%x, aEventType = %d", "CAknSettingItemList", __FUNCTION__, aListBox, aEventType );

    switch(aEventType)
        {
        case EEventEnterKeyPressed: // Can be enter key (In Series 60, OK key)
        case EEventItemDoubleClicked: // Or double click event
        case EEventItemSingleClicked:
            {
            TInt itemIndex = SettingItemArray()->ItemIndexFromVisibleIndex( aListBox->CurrentItemIndex() );
            if ( itemIndex >= 0 )
                {
                EditItemL( itemIndex, EFalse );
                aListBox->View()->DrawItem( aListBox->CurrentItemIndex() );
                }
            }
            break;

        default:
            break;
        }
    }


//It is the responsibility of the client to call this whenever it hides or deletes
//SettingItems
EXPORT_C void CAknSettingItemList::HandleChangeInItemArrayOrVisibilityL()
    {
    _AKNTRACE_FUNC_ENTER;

    // Save the original highlight position. This will be -1 if there isn't one.

    TInt originalHighlight = ListBox()->CurrentItemIndex();
    //Listbox is only aware of the visible list (corresponding to "VisibleIndex");



    //the actual list of ALL items (visible and invisible) corresponds to
    //the "SettingItemIndex"
    TInt originalSettingItemIndex = -1;

    // Possibly, there is no highlight yet, but if there is...
    if ( originalHighlight >= 0 )
        {
        // get the setting item index that corresponds to it
        originalSettingItemIndex = SettingItemArray()->
            ItemIndexFromVisibleIndex( originalHighlight );
        }

    //Save the distance of the highlight from the top of the view window
    //in order to try to preserve it after allowing for item deletions.
    //this will be <0 if there is no highlight
    TInt originalDistanceOfHighlightFromTopOfView = originalHighlight
        - ListBox()->TopItemIndex();


    // Now recalculate the indices
    SettingItemArray()->RecalculateVisibleIndicesL();

    ListBox()->View()->CalcDataWidth();
    ListBox()->View()->CalcBottomItemIndex();
    ListBox()->UpdateScrollBarsL();

    //ListBox assumes it's down to the client to ensure each time an item
    //is added or deleted, the currentSettingItemIndex is recalculated.
    //Thus if someone asynchronously deletes/hides an item without recalcing the SettingItemIndex
    //then we're stuck.
    TInt currentSettingItemIndex =        originalSettingItemIndex;

    //We don't know if we will be able to position our highlight at the same place on
    //the screen, various items may have been made invisible,
    //So we now sort out which item will be at the top of the viewable window
    // Scan backwards starting from currentSettingItem until we find a visible item.
    TInt currentHighlight = -1;

    for ( ; currentSettingItemIndex >= 0; --currentSettingItemIndex )
        {
        if ( !( SettingItemArray()->At(currentSettingItemIndex)->IsHidden() ) )
            // i.e.,if visible
            {
            currentHighlight = SettingItemArray()->
                At(currentSettingItemIndex)->VisibleIndex();
            break;
            }
        }


    // If none found, then go to first visible item (which will be AFTER
    // the original position)
    if ( currentSettingItemIndex < 0 )
        {
        if ( ListBox()->Model()->NumberOfItems() > 0 )
            currentHighlight = 0;
        }


    // if there is a highlight, set current item
    if ( currentHighlight >= 0 )
        {
        //if there are enough visible items above the highlight to return the highlight
        //to the same position on the screen then do so,
        //else draw it at the top of the screen.
        if (currentHighlight >= (originalDistanceOfHighlightFromTopOfView+1) )
            ListBox()->SetTopItemIndex(currentHighlight
                                       - originalDistanceOfHighlightFromTopOfView);
        else
            ListBox()->SetTopItemIndex(0);

        ListBox()->SetCurrentItemIndex( currentHighlight );
        ListBox()->DrawNow();
        }

    _AKNTRACE_FUNC_EXIT;
    }


EXPORT_C void CAknSettingItemList::FocusChanged(TDrawNow aDrawNow)
    {
    TBool isFocused = IsFocused();
    ListBox()->SetFocus(isFocused, aDrawNow);
    }

EXPORT_C void CAknSettingItemList::HandleResourceChange( TInt aType )
    {
    _AKNTRACE( "[%s][%s] aType = %d", "CAknSettingItemList", __FUNCTION__, aType );
    if(aType == KEikDynamicLayoutVariantSwitch)
        {
        TRect mainpaneRect;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, mainpaneRect );

        if ( OwnsWindow() )
            {
            SetRect(mainpaneRect);
            }
        else
            {
            SetRect( TRect( mainpaneRect.Size() ) );
            }

        ListBox()->SetRect( TRect( mainpaneRect.Size() ) );
        }

    if( aType == KAknsMessageSkinChange || aType == KEikDynamicLayoutVariantSwitch)
        {
        TRAP_IGNORE( UpdateAllListBoxTextsL() );
        }
    // put the list ok
    CAknControl::HandleResourceChange(aType);
    }

EXPORT_C void CAknSettingItemList::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    _AKNTRACE_FUNC_ENTER;
    CAknControl::HandlePointerEventL(aPointerEvent);
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void* CAknSettingItemList::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

void CAknSettingItemList::UpdateAllListBoxTextsL() const
    {
    _AKNTRACE_FUNC_ENTER;
    TUint number = SettingItemArray()->Count();
    TUint index;
    for ( index = 0; index < number; index++ )
        {
        SettingItemArray()->At( index )->UpdateListBoxTextL();
        }
    _AKNTRACE_FUNC_EXIT;
    }
// End of File
