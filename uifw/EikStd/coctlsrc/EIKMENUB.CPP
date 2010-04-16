/*
* Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
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


#include <eikmenub.h>
#include <eikmenup.h>
#include <eikmobs.h>
#include <eikhkeyt.h>
#include <eikon.hrh>
#include <barsread.h>
#include <eikenv.h>
#include <eikcmobs.h>
#include <gulutil.h>
#include <eikbtgpc.h>
#include <eikkeys.h>
#include <eikappui.h>
#include <aknappui.h>
#include <aknborders.h>     // AKNLAF
#include <aknenv.h>
#include <AknUtils.h>

#include <gulcolor.h>
#include <gulicon.h>
#include "LAFMENUB.H"
#include "LAFMENUP.H"
#include "eikmop.h"

#include <avkon.rsg>
#include <avkon.hrh>
#include <AknLayout.lag>
#include <aknsoundsystem.h>
#include <AknPopupFader.h>
#include <AiwServiceHandler.h>

#include <gfxtranseffect/gfxtranseffect.h> 
#include <akntranseffect.h>
#include <akntransitionutils.h>
#include "avkoninternalpskeys.h" //KAknMenuOptionNoTaskSwapper
#include <AknCapServerDefs.h>
#include <e32property.h>

#include <AknTasHook.h>

#include <touchfeedback.h>
#include <aknitemactionmenu.h>
#include "aknitemactionmenuregister.h"
#include <AknPriv.hrh>
#include "akntrace.h"

enum { EEikMenuBarTitleArrayGranularity=10 };
enum { EEikMenuBarPosArrayGranularity=2 };
const TInt KExtraBaselineOffsetForFirstPaneItem=4;

NONSHARABLE_CLASS(CEikMenuBarExtension) : public CBase, public MAknFadedComponent
    {
public:
    static CEikMenuBarExtension* NewL(CEikMenuBar* aBar);
    ~CEikMenuBarExtension();

    void FadeBehindPopup(TBool aFade);

    /**
     * Sets item specific commands dimmed if highlight is not visible.
     */
    void SetItemCommandsDimmedL();

public: // from MAknFadedComponent
    TInt CountFadedComponents();
    CCoeControl* FadedComponent(TInt aIndex);

private:
    CEikMenuBarExtension(CEikMenuBar* aBar);
    void ConstructL();

private:
    CEikMenuBar* iBar;
    TAknPopupFader iFader;
public:
    TInt iContextMenuTitleResourceId;
    TInt iOriginalMenuTitleResourceId;
    
    CEikMenuBar::TMenuType iMenuType;

    
    // controls fader and transition aborting behaviour
    // with transition effects
    TBool iDoingMenuCloseTransition;

    /**
     * Item action menu.
     * Not own.
     */
    CAknItemActionMenu* iItemActionMenu;
    };


CEikMenuBarExtension* CEikMenuBarExtension::NewL(CEikMenuBar* aBar)
    {
    CEikMenuBarExtension* self = new(ELeave) CEikMenuBarExtension(aBar);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

CEikMenuBarExtension::~CEikMenuBarExtension()
    {
    AknItemActionMenuRegister::UnregisterMenuBar( *iBar );
    iBar = NULL;
    }

void CEikMenuBarExtension::FadeBehindPopup(TBool aFade)
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "iDoingMenuCloseTransition: %d",  iDoingMenuCloseTransition );
    if( iDoingMenuCloseTransition == EFalse )
        {
        iFader.FadeBehindPopup(this, iBar, aFade);
        }
    _AKNTRACE_FUNC_EXIT;
    }


void CEikMenuBarExtension::SetItemCommandsDimmedL()
    {
    if ( !iItemActionMenu )
        {
        AknItemActionMenuRegister::RegisterMenuBarL( *iBar );
        }
    // hide item-specific commands if highlight not visible 
    if ( iBar->GetMenuType() != CEikMenuBar::EMenuContext
            && iItemActionMenu
            && !iItemActionMenu->CollectionHighlightVisible() )
        {
        iBar->iMenuPane->SetItemCommandsDimmed();
        }
    }


CEikMenuBarExtension::CEikMenuBarExtension(CEikMenuBar* aBar)
    :iBar(aBar),
     iDoingMenuCloseTransition(EFalse),
     iItemActionMenu( NULL )
    {
    }

void CEikMenuBarExtension::ConstructL()
    {
    }

TInt CEikMenuBarExtension::CountFadedComponents()
    {
    TInt count = 1; // the cba

    // count the menu pane and it's cascade panes
    CEikMenuPane* pane = iBar->iMenuPane;
    while (pane)
        {
        count++;
        pane = pane->CascadeMenuPane();
        }

    return count;
    }

CCoeControl* CEikMenuBarExtension::FadedComponent(TInt aIndex)
    {
    if (aIndex == 0)
        return iBar->iMenuCba;

    // count down the list of cascade menus to find the one in question
    aIndex--;
    CEikMenuPane* pane = iBar->iMenuPane;
    while (aIndex > 0 && pane != NULL)
        {
        aIndex--;
        pane = pane->CascadeMenuPane();
        }

    return pane;
    }


//
// class CTitleArray
//

EXPORT_C CEikMenuBar::CTitleArray::~CTitleArray()
    {
    ResetAndDestroy();
    }

EXPORT_C CEikMenuBar::CTitleArray::CTitleArray()
    : CArrayPtrFlat<CEikMenuBarTitle>(EEikMenuBarTitleArrayGranularity)
    {
    __DECLARE_NAME(_S("CEikMenuBar::CTitleArray"));
    }

/**
 * Adds the menu bar title aMenuTitle to the end of the array owned by the menu bar
 * and transfers ownership.
 */
EXPORT_C void CEikMenuBar::CTitleArray::AddTitleL(CEikMenuBarTitle* aMenuTitle)
    {
    AppendL(aMenuTitle);
    }


void CEikMenuBar::CTitleArray::DeleteResource(TInt aResource)
    {
    TInt count = Count();
    for (TInt ii=0; ii<count; ii++)
        {
        CEikMenuBarTitle* title = At(ii);
        if (title->iData.iMenuPaneResourceId == aResource)
            {
            delete title;
            Delete(ii);
            return;
            }
        }
    }



//
// class CEikMenuBarTitle
//

//const TInt KTitleGranularity=1;
//const TInt KIconOwnedExternally       = 0x01;
//const TInt KSameBitmapAndMask     = 0x10;
//const TInt KTitleWithImageMask        = 0xf000;


EXPORT_C CEikMenuBarTitle::CEikMenuBarTitle()
    {}

EXPORT_C CEikMenuBarTitle::~CEikMenuBarTitle()
    {
    delete iIcon;
    }

EXPORT_C void CEikMenuBarTitle::SetIcon(CGulIcon* aIcon)
    {
    if (iIcon)
        delete iIcon;
    iIcon = aIcon;
    }

/**
 * Returns the value of the extra left margin for the title text which will take into account the
 * width of the title icon.
 */
TInt CEikMenuBarTitle::ExtraLeftMargin() const
    {
    CFbsBitmap* bitmap = IconBitmap();
    TInt extraMargin = 0;
    if (bitmap != NULL)
        extraMargin = bitmap->SizeInPixels().iWidth;
    return extraMargin;
    }

/**
 * Adjusts the value of the title text baseline offset aBaseLine to take into account the any
 * size of any title icon.
 */
void CEikMenuBarTitle::CalculateBaseLine(TInt& aBaseLine, TInt& aTitleHeight)
    {
    CFbsBitmap* bitmap = IconBitmap();
    if (bitmap != NULL)
        {
        TInt tempBaseline = aBaseLine;
        const TSize bitmapSize(bitmap->SizeInPixels());
        if (bitmapSize.iHeight > aTitleHeight)
            {
            tempBaseline += ((bitmapSize.iHeight - aTitleHeight) >> 1);
            aTitleHeight = bitmapSize.iHeight; 
            }
        if (tempBaseline > aBaseLine)
            aBaseLine = tempBaseline;
        }
    }

/**
 * Draws the title icon to the graphics context aGc, inside the rect aRect with an offset from the left side of
 * the rectangle of size aLeftMargin
 */
EXPORT_C void CEikMenuBarTitle::DrawIcon(CWindowGc& aGc, TRect aRect, TInt aLeftMargin) const
    {
    CFbsBitmap* bitmap = IconBitmap();
    if (bitmap != NULL)
        {
        TSize imageSize = bitmap->SizeInPixels();
        aRect.iTl.iX += aLeftMargin;
        TInt height = aRect.iBr.iY - aRect.iTl.iY;
        if (height > imageSize.iHeight)
            aRect.iTl.iY += (TInt) ((height - imageSize.iHeight) / 2 );
        aGc.BitBltMasked(aRect.iTl, bitmap, imageSize, IconMask(), ETrue);
        }
    }

/**
 * Sets the title icon to be ownded externally if aOwnedExternally is ETrue.
 */
EXPORT_C void CEikMenuBarTitle::SetBitmapsOwnedExternally(TBool aOwnedExternally)
    {
    iIcon->SetBitmapsOwnedExternally(aOwnedExternally);
    }

/**
 * Returns a pointer to the picture bitmap of the title icon.
 * Does not normally imply transfer of ownership.
 */
EXPORT_C CFbsBitmap* CEikMenuBarTitle::IconBitmap() const
    {
    if (iIcon)
        return iIcon->Bitmap();
    return NULL;
    }

/**
 * Returns a pointer to the mask bitmap of the title icon.
 * Does not normally imply transfer of ownership.
 */
EXPORT_C CFbsBitmap* CEikMenuBarTitle::IconMask() const
    {
    if (iIcon)
        return iIcon->Mask();
    return NULL;
    }

/**
 * Sets the picture bitmap for the title icon to aBitmap.
 * Transfers ownership unless the bitmaps are owned externally.
 */
EXPORT_C void CEikMenuBarTitle::SetIconBitmapL(CFbsBitmap* aBitmap)
    {
    if (!iIcon)
        iIcon=CGulIcon::NewL();

    iIcon->SetBitmap(aBitmap);
    }

/**
 * Sets the mask bitmap for the title icon to aMask.
 * Transfers ownership unless the bitmaps are owned externally.
 */
EXPORT_C void CEikMenuBarTitle::SetIconMaskL(CFbsBitmap* aMask)
    {
    if (!iIcon)
        iIcon=CGulIcon::NewL();

    iIcon->SetMask(aMask);
    }

/**
 * Constructs an new icon for the title, taking ownership of the picture bitmap
 * aBitmap and the mask bitmap aMask unless the icon bitmaps have been set to be
 * owned externally.
 */
EXPORT_C void CEikMenuBarTitle::CreateIconL(CFbsBitmap* aBitmap, CFbsBitmap* aMask)
    {
    if (iIcon)
        delete iIcon;
    iIcon = CGulIcon::NewL(aBitmap, aMask);
    }


//
// class CEikMenuBar
//

//const TInt KEikMenuBarHBorder=8;
//const TInt KEikMenuBarVBorder=2;
//const TInt KEikMenuMnenPad=3;
//const TInt KEikMaxMenuTitlePadding=10;
//const TInt KEikNumOfSideButtons=5;
//const TInt KEikSidebarPopupXPos=5;
//const TInt KMenuPaneOverlap=1;

//const TInt KMenuTitleLeftSpace = 12;
//const TInt KMenuTitleRightSpace = 12;
//const TInt KMenuTitleLeftSmallSpace = 2;
//const TInt KMenuTitleRightSmallSpace = 2;

inline TBool CEikMenuBar::MenuHasItems() const
    {
    return iMenuFlags&EMenuHasItems;
    }

inline void CEikMenuBar::SetMenuHasItems()
    {
    iMenuFlags|=EMenuHasItems;
    }

inline TBool CEikMenuBar::MenuHasPane() const
    {
    return iMenuFlags&EMenuHasPane;
    }

inline void CEikMenuBar::SetMenuHasPane()
    {
    iMenuFlags|=EMenuHasPane;
    }

inline TBool CEikMenuBar::TitleArrayOwnedExternally() const
    {
    return iMenuFlags&ETitleArrayOwnedExternally;
    }

EXPORT_C CEikMenuBar::~CEikMenuBar()
    {
    AKNTASHOOK_REMOVE();
    // Inform FEP about the destruction.
    MEikMenuObserver* fepMenuObserver =  CAknEnv::Static()->FepMenuObserver();
    if ( fepMenuObserver )
        {
        fepMenuObserver->ProcessCommandL( EAknCmdEditMenuClose );
        }

    delete iPastMenuPosArray;
    iPastMenuPosArray = NULL;
    
    delete iHotKeyTable;
    iHotKeyTable = NULL;
    
    if ( iMenuPane )
        {
        // make sure imenupane is not visible
        // otherwise Deregister may try to draw
        // when closing application
        iMenuPane->MakeVisible( EFalse );
        // deregister main options menu component
        GfxTransEffect::Abort( iMenuPane );
        GfxTransEffect::Deregister( iMenuPane );
        delete iMenuPane;
        iMenuPane = NULL;
        }
    
    if ( !TitleArrayOwnedExternally() && iTitleArray )
        {
        ResetTitleArray();
        delete iTitleArray;
        iTitleArray = NULL;
        }
        
    delete iExt;
    iExt = NULL;
    
    if ( iMenuCba ) // should have been deleted before, but still...
        {
        delete iMenuCba;
        iMenuCba = NULL;
        }
        
    iMenuObserver = NULL; // not owned
    iEditMenuObserver = NULL;
    iActiveEditMenuObserver = NULL;
    
    }

EXPORT_C CEikMenuBar::CEikMenuBar()
    : iSelectedTitle(ENothingSelected)
    {
    __DECLARE_NAME(_S("CEikMenuBar"));
    iBorder=TGulBorder(AknBorderId::EAknBorderMenuPopup);
    AKNTASHOOK_ADD( this, "CEikMenuBar" );
    }

/**
 * Resets the menu bar's title array and destroys its elements.
 *
 * @since ER5U
 */
void CEikMenuBar::ResetTitleArray()
    {
    if (iTitleArray)
        iTitleArray->ResetAndDestroy();
    }

/**
 * Creates a new menu bar title array if one does not already exist. Resets and destroys the elements
 * of an existing array..
 *
 * @since ER5U
 */
void CEikMenuBar::CreateTitleArrayL()
    {
    if (iTitleArray)
        iTitleArray->ResetAndDestroy();
    else
        iTitleArray=new(ELeave) CTitleArray;
    }

/**
 * Sets the flags on the menu pane owned by the menu bar to aFlags.
 *
 * @since ER5U
 */
void CEikMenuBar::SetMenuPaneFlag(TInt aFlag)
    {
    iMenuPane->SetScrollBarOnLeft(aFlag&EEikMenuItemScrollBarLeft);
    iMenuPane->SetArrowHeadScrollBar(aFlag&EEikMenuItemScrollBarArrowHead);
    }


EXPORT_C void CEikMenuBar::ConstructL(MEikMenuObserver* aMenuObserver,TInt aHotKeyResourceId,TInt aMenuTitleResourceId)
    {
    iExt = CEikMenuBarExtension::NewL(this);

    iMenuObserver=aMenuObserver;
    iMenuHotKeyResourceId=aHotKeyResourceId;
    iMenuTitleResourceId=aMenuTitleResourceId;
    iBaseLine=iEikonEnv->NormalFont()->AscentInPixels()+KExtraBaselineOffsetForFirstPaneItem;
    iPastMenuPosArray=new(ELeave) CArrayFixFlat<SPosition>(EEikMenuBarPosArrayGranularity);
    CreateTitleArrayL();

    iMenuPane=new(ELeave) CEikMenuPane(iMenuObserver);
    iMenuPane->SetMopParent(this);
    iMenuPane->SetBorder(AknBorderId::EAknBorderMenuPopup);
    iMenuPane->SetParent( this );
    MakeVisible(EFalse);
    // register main options menu component
    GfxTransEffect::Register( iMenuPane, KGfxOptionsMenuControlUid, EFalse );
    GfxTransEffect::Enable();
    }

/**
 * Constructs the menu bar using the resource reader aReader.
 */
EXPORT_C void CEikMenuBar::ConstructFromResourceL(TResourceReader& aReader)
    {
    TInt count=aReader.ReadInt16();
    while (count--)
        {
        CEikMenuBarTitle* title = new(ELeave) CEikMenuBarTitle;
        CleanupStack::PushL(title);
        title->iData.iMenuPaneResourceId=aReader.ReadInt32();
        title->iTitleFlags=0;
        const TPtrC ptr=aReader.ReadTPtrC();
        title->iData.iText=ptr;
        title->iTitleFlags=aReader.ReadInt32();
        // Skip over icon info
        aReader.ReadTPtrC();
        aReader.ReadInt16();
        aReader.ReadInt16();
        iTitleArray->AddTitleL(title);
        aReader.ReadInt32(); // extension link
        CleanupStack::Pop();
        }
    aReader.ReadInt32(); // extension link
    }

EXPORT_C void CEikMenuBar::FindCommandIdInResourceL(TInt aCommandId,TInt& aPaneindex,TInt& aItemindex)
    {
    aPaneindex=-1;
    aItemindex=-1;
    TResourceReader reader;

    TInt panes=iTitleArray->Count();
    for (TInt pindex=0;pindex<panes;++pindex)
        {
        CEikMenuBarTitle* title=(*iTitleArray)[pindex];
        ControlEnv()->CreateResourceReaderLC(reader,title->iData.iMenuPaneResourceId);
        const TInt count=reader.ReadInt16();
        for (TInt iindex=0;iindex<count;++iindex)
            {
            TInt commandId=reader.ReadInt32();
            reader.ReadInt32(); //cascadeId
            reader.ReadInt32(); // data flags
            reader.ReadTPtrC();
            reader.ReadTPtrC();
            reader.ReadInt32(); // title flags
            reader.ReadTPtrC(); // bitmap file
            reader.ReadInt16(); // bitmapId
            reader.ReadInt16(); // bitmapMaskId
            reader.ReadInt32(); // item extension
            if (commandId==aCommandId)
                {
                aItemindex=iindex;
                break;
                }
            }
        if (aItemindex>=0)
            {
            aPaneindex=pindex;
            CleanupStack::PopAndDestroy(); // buffer(reader)
            return;
            }
        CleanupStack::PopAndDestroy(); // buffer(reader)
        }
    }


EXPORT_C void CEikMenuBar::ChangeMenuBarL(TInt /*aHotKeyResourceId*/,TInt /*aMenuTitleResourceId*/,TBool /*aDisplayNow*/)
    {
    }

void CEikMenuBar::SaveCurrentMenuPositionL()
//Save position on current menu
//See if current menu is already on past menu array.
//If it is, just change the cursor value, if it is not
//add a new element to the array.
    {
    const TInt count = iPastMenuPosArray->Count();
    for (TInt ii = 0; ii < count; ++ii)
        {
        if ((*iPastMenuPosArray)[ii].iMenuId == iMenuTitleResourceId)
            {
            (*iPastMenuPosArray)[ii].iMenuCursorPos = iCursor;
            return;
            }
        }
    SPosition menuPos;
    menuPos.iMenuId = iMenuTitleResourceId;
    menuPos.iMenuCursorPos = iCursor;
    iPastMenuPosArray->AppendL(&menuPos, sizeof(menuPos));
    }

void CEikMenuBar::SetCursorPositionFromArray()
//Set cursor position
//Check position array to see if menu previously displayed and use that last position.
    {
    const TInt count=iPastMenuPosArray?iPastMenuPosArray->Count():0;
    for (TInt ii=0;ii<count;++ii)//Use same count as above cos we wont be interested in menu we have just added to the list
        {
        if ((*iPastMenuPosArray)[ii].iMenuId==iMenuTitleResourceId)
            {
            iCursor=(*iPastMenuPosArray)[ii].iMenuCursorPos;
            return;
            }
        }
    iCursor.iMenuPaneIndex=0;   
    iCursor.iMenuItemIndex=0;
    }

EXPORT_C CEikHotKeyTable* CEikMenuBar::SetHotKeyTable(CEikHotKeyTable* /*aHotKeyTable*/)
    {
    return NULL;
    }

EXPORT_C void CEikMenuBar::SetMenuTitleResourceId(TInt aMenuTitleResourceId)
    {
    SetCursorPositionFromArray();  // defaults set here if this menu not previously displayed
    if (iMenuPane && !MenuHasPane())
        {       
        iMenuPane->SetSelectedItem(0); 
        }
    iSelectedTitle=ENothingSelected;
    iMenuTitleResourceId=aMenuTitleResourceId;
    }

EXPORT_C void CEikMenuBar::SetContextMenuTitleResourceId(TInt aMenuTitleResourceId)
    {
    SetCursorPositionFromArray();  // defaults set here if this menu not previously displayed
    if (iMenuPane && !MenuHasPane())
        {       
        iMenuPane->SetSelectedItem(0); 
        }
    iSelectedTitle=ENothingSelected;
    iExt->iContextMenuTitleResourceId=aMenuTitleResourceId;
    }

EXPORT_C void CEikMenuBar::SetMenuTitleArray(CTitleArray* /*aTitleArray*/)
    {
    }

/**
 * Sets the menu bar title array to be owned externally if aOwnedExternally is ETrue.
 *
 * since ER5U
 */
EXPORT_C void CEikMenuBar::SetTitleArrayOwnedExternally(TBool /*aOwnedExternally*/)
    {
    }

EXPORT_C TKeyResponse CEikMenuBar::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    const TInt code=aKeyEvent.iCode;

    if (MenuHasPane())
        {
        iMenuPane->OfferKeyEventL(aKeyEvent, aType);
        return (aKeyEvent.iScanCode == EStdKeyYes ? EKeyWasNotConsumed : EKeyWasConsumed);
        }
    else
        {
        switch (code)
            {
            case EEikSidebarMenuKey:
            case EKeyMenu:
                TryDisplayMenuBarL();
                return EKeyWasConsumed;
            default:
                break;
            }
        }

    if (!MenuHasItems())  // menu bar not currently displayed
        return EKeyWasNotConsumed;

    // When displaying, the menu bar must comsume all keys, even those it doesn't use.
    // So use callback here to see if app wants key.
    iMenuObserver->OfferKeyToAppL(aKeyEvent, aType);
    return EKeyWasConsumed;

    }



LOCAL_C void CleanupMenu(TAny* aPtr)
    {
    ((CEikMenuBar*)aPtr)->StopDisplayingMenuBar();
    }

EXPORT_C TInt CEikMenuBar::SelectedTitle()
    {
    return iCursor.iMenuPaneIndex;
    }

EXPORT_C TInt CEikMenuBar::SelectedItem()
    {
    return iCursor.iMenuItemIndex;
    }

EXPORT_C void CEikMenuBar::TryDisplayMenuBarL()
    {
    if (MenuHasItems())
        return; // menu already being displayed
    iActiveEditMenuObserver = iEditMenuObserver;
    CleanupStack::PushL(TCleanupItem(CleanupMenu,this));
    StartDisplayingMenuBarL();
    CleanupStack::Pop();
    }

EXPORT_C void CEikMenuBar::TryDisplayContextMenuBarL()
    {
    if (MenuHasItems() || !iExt || !iExt->iContextMenuTitleResourceId)
        return; // menu already being displayed or no extension or no context resource id
    iActiveEditMenuObserver = iEditMenuObserver;
    CleanupStack::PushL(TCleanupItem(CleanupMenu,this));
    // use context specific menu resource for this menu
    iExt->iOriginalMenuTitleResourceId = iMenuTitleResourceId;
    iMenuTitleResourceId = iExt->iContextMenuTitleResourceId;
    SetMenuType(EMenuContext);
    StartDisplayingMenuBarL();
    CleanupStack::Pop();
    }


void CEikMenuBar::HideMenuPane()
    {
    if (MenuHasPane())
        {
        iCursor.iMenuPaneIndex=iSelectedTitle; // !! check this can never be -1
        iCursor.iMenuItemIndex=iMenuPane->SelectedItem();
        iMenuPane->CancelActiveMenuPane();
        iMenuFlags&=~EMenuHasPane;
        iMenuPane->Reset();
        iMenuPane->MakeVisible(EFalse);
        }
    iSelectedTitle=ENothingSelected;
    }


EXPORT_C void CEikMenuBar::MoveHighlightToL(TInt /*aNewSelectedTitle*/,TInt /*aNewSelectedItem*/)
    {
    }

EXPORT_C void CEikMenuBar::StopDisplayingMenuBar()
    {
    _AKNTRACE_FUNC_ENTER;
    if (iMenuFlags&ESoundsInstalled)
        {
        iAvkonAppUi->KeySounds()->PopContext();
        iMenuFlags &= ~ESoundsInstalled;
        }
    if( !iExt->iDoingMenuCloseTransition && IsDisplayed() )
        {
        // abort component effects
        GfxTransEffect::Abort();
        }

    iAvkonEnv->UnRegisterIntermediateState(this);

    delete iMenuCba;
    iMenuCba = NULL;

    iMenuObserver->SetEmphasis(this,EFalse);
    iMenuFlags&=~EMenuHasItems;
    HideMenuPane();
    MEikMenuObserver* fepMenuObserver =  CAknEnv::Static()->FepMenuObserver();
    if (fepMenuObserver)
        fepMenuObserver->SetEmphasis(this, EFalse);
    if (iActiveEditMenuObserver)
        iActiveEditMenuObserver->SetEmphasis(this, EFalse);
    iActiveEditMenuObserver=NULL;       // forget active observer till menu next added
    iMenuPane->SetFocus(EFalse);
    iMenuPane->Close();
    iTitleArray->ResetAndDestroy();
    if (OwnsWindow())
        CloseWindow();
    
    // normal options menu must be restored if context specific menu was displayed
    if (iExt && iMenuTitleResourceId == iExt->iContextMenuTitleResourceId &&
        iExt->iOriginalMenuTitleResourceId)
        {
        iMenuTitleResourceId = iExt->iOriginalMenuTitleResourceId;
        SetMenuType(EMenuOptions);
        }

    if (iMenuFlags&EBackgroundFaded)
        {
        if (iExt)
            iExt->FadeBehindPopup(EFalse);
        iMenuFlags &= ~EBackgroundFaded;
        }
    _AKNTRACE_FUNC_EXIT;
    }

void CEikMenuBar::StartDisplayingMenuBarL()
    {
    _AKNTRACE_FUNC_ENTER;
    // Inform AIW framework that a menu bar is being launched.
    CAiwServiceHandler::ReportMenuLaunch();

    CreateWindowL(iCoeEnv->RootWin());
    const TSize screenSize = iAvkonAppUi->ApplicationRect().Size();

    __ASSERT_DEBUG(iMenuCba == NULL, User::Panic(_L("CEikMenuBar"), KErrAlreadyExists));
    TInt softkeyResourceId = R_AVKON_SOFTKEYS_SELECT_CANCEL__SELECT;
    if ((User::Language() & KAknLanguageMask) == ELangJapanese)
        {
        // In Japanese UI language Select-Back softkey combination is used.
        // Command Id for Back is same as for Cancel.
        softkeyResourceId = R_AVKON_SOFTKEYS_SELECT_BACK__SELECT;
        }    
    
    iMenuPane->ConstructL(NULL, iActiveEditMenuObserver);

    MEikMenuObserver* fepMenuObserver =  CAknEnv::Static()->FepMenuObserver();

    iMenuObserver->RestoreMenuL(this,iMenuTitleResourceId,MEikMenuObserver::EMenuBar);
            
    if (fepMenuObserver)
        {
        AddFEPMenuL();
        fepMenuObserver->DynInitMenuBarL(iMenuTitleResourceId, this);
        }

    TInt titles = iTitleArray->Count() - 1;
    
    if ( titles < 0 )
        {
        delete iMenuCba;
        iMenuCba = NULL;
        iTitleArray->ResetAndDestroy();
        iMenuPane->Close();
        return;
        }
        
    // Create the menu pane using the last pane in the menu bar
    iMenuObserver->RestoreMenuL(iMenuPane,(*iTitleArray)[titles]->iData.iMenuPaneResourceId,MEikMenuObserver::EMenuPane);
    if (fepMenuObserver)
        fepMenuObserver->DynInitMenuPaneL((*iTitleArray)[titles]->iData.iMenuPaneResourceId,iMenuPane);
    if (iActiveEditMenuObserver)
        iActiveEditMenuObserver->DynInitMenuPaneL((*iTitleArray)[titles]->iData.iMenuPaneResourceId,iMenuPane);

    titles = iTitleArray->Count() - 2;
    iMenuPane->FilterDimmedItems();

    // Add the remaining menu panes from right to left at the end of the current pane
    while (titles >= 0)
        {
        TInt resource = (*iTitleArray)[titles]->iData.iMenuPaneResourceId;
        iMenuPane->AddMenuItemsL(resource, 0, ETrue);       
        iMenuObserver->DynInitMenuPaneL(resource,iMenuPane);
        if (fepMenuObserver)
            fepMenuObserver->DynInitMenuPaneL(resource,iMenuPane);
        if (iActiveEditMenuObserver)
            iActiveEditMenuObserver->DynInitMenuPaneL(resource,iMenuPane);
        iExt->SetItemCommandsDimmedL();
        iMenuPane->FilterDimmedItems();
        titles--;
        }
    iMenuObserver->SetEmphasis(this,ETrue);
	iMenuCba = CEikButtonGroupContainer::NewL(CEikButtonGroupContainer::ECba, 
	    CEikButtonGroupContainer::EHorizontal,
	    this, softkeyResourceId, *iMenuPane, 
	    CEikButtonGroupContainer::EIsEmbedded | 
	    CEikButtonGroupContainer::EDelayActivation );
	    
    CEikCba* cba = static_cast<CEikCba*>( iMenuCba->ButtonGroup() );
    if ( cba )
        {
        iMenuPane->SetEmbeddedCba( cba );
        }
    
    MTouchFeedback* feedback = MTouchFeedback::Instance();
    if ( feedback )
        {
        feedback->FlushRegistryUpdates();
        }        
    
       TInt taskSwapper ( ETaskSwapper );
       RProperty::Get(
                KPSUidAvkonInternal, 
                KAknMenuOptionNoTaskSwapper, 
                taskSwapper);      
    if ( iMenuPane->NumberOfItemsInPane() != 0 && iExt->iMenuType == EMenuOptions && taskSwapper == ETaskSwapper )      
        {
        // 'Active Applications' menu item is added at the first item of the 
        // options menu after other menu items are added.
        iMenuPane->AddMenuItemsL(R_AVKON_MENUPANE_TASK_SWAPPER);
        }

    if (iMenuPane->NumberOfItemsInPane() == 0)
        {
        delete iMenuCba;
        iMenuCba = NULL;
        iMenuObserver->SetEmphasis(this,EFalse);
        iTitleArray->ResetAndDestroy();
        iMenuPane->Close();
        return;
        }

    if (!(iMenuFlags&EBackgroundFaded))
        {
        iExt->FadeBehindPopup(ETrue);
        iMenuFlags |= EBackgroundFaded;
        }

    iMenuCba->SetBoundingRect(TRect(TPoint(0,0), screenSize));

    SetMenuHasPane();
    SetMenuHasItems();

    TInt positionOffTaskSwapper;
    if (iMenuPane->MenuItemExists(EAknCmdTaskSwapper, positionOffTaskSwapper))
        {
        // Default selected item is just after 'Active Applications' menu 
        // item if it exists.
        iMenuPane->SetSelectedItem(positionOffTaskSwapper + 1);
        }
    else
        {
        iMenuPane->SetSelectedItem( 0 );
        }     
    
    iMenuPane->SetFocus(ETrue);
    if (fepMenuObserver)
        fepMenuObserver->SetEmphasis(this, ETrue);
    if (iActiveEditMenuObserver)
        iActiveEditMenuObserver->SetEmphasis(this, ETrue);
    
    // Set the position of the menu pane to the top of the CBA area, 
    // and set the width to the width of the screen
    TPoint menuPosition = TPoint(0, screenSize.iHeight - iMenuCba->Size().iHeight);

    if(AknLayoutUtils::PenEnabled())
        {
        // menu pane captures all pointer events, and forwards them to CBA if neccessary
        iMenuPane->SetGloballyCapturing(ETrue);
        iMenuPane->SetPointerCapture(ETrue);
        MTouchFeedback* feedback = MTouchFeedback::Instance();
        if ( feedback )
            {
            TTouchLogicalFeedback fbLogicalType = ETouchFeedbackPopUp;
            if ( CAknTransitionUtils::TransitionsEnabled( AknTransEffect::EComponentTransitionsOff ) )
                {
                fbLogicalType = ETouchFeedbackPopupOpen;
                }
            feedback->InstantFeedback(
                                   this,
                                   fbLogicalType,
                                   ETouchFeedbackVibra,
                                   TPointerEvent() );
            }      
        }
    
    iMenuPane->MakeVisible( EFalse );

    // options menu launch animation
    TBool optMenuFg = iAvkonAppUi->IsForeground();
    
    if( optMenuFg )
        {
        GfxTransEffect::Begin( iMenuPane, KGfxControlAppearAction );
        } 
    
    iMenuPane->StartDisplayingMenuPane(NULL, menuPosition, NULL, screenSize.iWidth, EPopupTargetBottomLeft);
    iMenuCba->ActivateL();

    iAvkonEnv->RegisterIntermediateStateL(this);
    iAvkonAppUi->KeySounds()->PushContextL(R_AVKON_DEFAULT_SKEY_LIST);
    iMenuFlags |= ESoundsInstalled;

    if( optMenuFg )
        { 
        TRect demarcation;
        CAknTransitionUtils::GetDemarcation( CAknTransitionUtils::EOptionsMenu, 
                                         demarcation );
        GfxTransEffect::SetDemarcation( iMenuPane, demarcation );
        GfxTransEffect::End( iMenuPane );
        }
    _AKNTRACE_FUNC_EXIT;
    }


EXPORT_C void CEikMenuBar::Draw(const TRect& /*aRect*/) const
    {

    }

EXPORT_C void CEikMenuBar::DrawItem(TInt /*aItem*/) const
    {
    }

EXPORT_C void* CEikMenuBar::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CEikMenuBar::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    const TRect rect=Rect();
    if (!rect.Contains(aPointerEvent.iPosition))
        {
        switch (aPointerEvent.iType)
            {
        case TPointerEvent::EButton1Down:
        case TPointerEvent::EButton1Up:
            ProcessCommandL( EAknSoftkeyCancel );
            iMenuObserver->ProcessCommandL(EEikCmdCanceled); // shouldn't Leave in practiceReportCancelled();
            return;
        case TPointerEvent::EDrag:
            // dragging off a pane sometimes sends the events to the bar; this code redirects the event
            // to the pane so that highlighing can be removed.
            if (iMenuPane)
                {
                TPoint panepos= iMenuPane->Position();
                TRect panerect= TRect(panepos, iMenuPane->Size());
                if (!panerect.Contains(aPointerEvent.iPosition))
                    {
                    TPointerEvent aPEvent=aPointerEvent;
                    aPEvent.iPosition=aPointerEvent.iPosition - panepos;
                    iMenuPane->HandlePointerEventL(aPEvent);
                    }
                }
            return;
        default:
            return;
            }
        }
    const TInt yPos=aPointerEvent.iPosition.iY;
    if (yPos<2 || yPos>iSize.iHeight-2)
        return;
    const TInt xPos=aPointerEvent.iPosition.iX;
    const TInt count=iTitleArray->Count();
    for (TInt ii=0;ii<count;++ii)
        {
        CEikMenuBarTitle* title=(*iTitleArray)[ii];
        if (xPos<title->iPos)
            return;
        if (xPos<title->iPos+title->iWidth)
            {
            MoveHighlightToL(ii);
            return;
            }
        }
    }

EXPORT_C TCoeInputCapabilities CEikMenuBar::InputCapabilities() const
    {
    return TCoeInputCapabilities(TCoeInputCapabilities::EAllText); // Max length parameter removed for Release15
    }

EXPORT_C CEikMenuBar::SCursor CEikMenuBar::SetMenuCursor(const SCursor& aCursor)
    {
    SCursor ret=iCursor;
    iCursor=aCursor;
    return ret;
    }

/**
 * Gets the list of logical colors employed in the drawing of the control,
 * paired with an explanation of how they are used. Appends the list to aColorUseList.
 *
 * @since ER5U
 */
EXPORT_C void CEikMenuBar::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const
    {
    LafMenuBar::GetColorUseListL(aColorUseList);
    }

/**
 * Handles a change to the control's resources of type aType
 * which are shared across the environment, e.g. colors or fonts.
 *
 * @since ER5U
 */
EXPORT_C void CEikMenuBar::HandleResourceChange(TInt aType)
    {
    if ( aType == KEikDynamicLayoutVariantSwitch 
        || aType == KEikMessageWindowsFadeChange 
        || aType == KEikMessageUnfadeWindows
        || aType == KEikMessageFadeAllWindows
        || aType == KAknMessageFocusLost
        || ( IsDisplayed() && aType == KAknsMessageSkinChange ) )
        {
        if ( iMenuPane ) 
            {
            iMenuPane->HandleResourceChange( aType );
            }
        }
    }

EXPORT_C void CEikMenuBar::Reserved_1()
    {}

EXPORT_C void CEikMenuBar::Reserved_2()
    {}

void CEikMenuBar::ProcessCommandL(TInt aCommandId)
    {
    TRect demarcation;
    switch (aCommandId)
        {
// AKNLAF start
        case EAknSoftkeyOk:
            iMenuPane->ActivateCurrentItemL();
            break;
        case EAknSoftkeySelect:
            iMenuPane->ActivateCurrentItemL();
            break;
        case EAknSoftkeyCancel:
            // options menu cancel animation, does not apply to the case
            // when something is chosen from the menu
            GfxTransEffect::Begin( iMenuPane, KGfxControlDisappearAction );
                    
            iExt->iDoingMenuCloseTransition = ETrue;            
            StopDisplayingMenuBar();
            iExt->iDoingMenuCloseTransition = EFalse;
                        
            CAknTransitionUtils::GetDemarcation( 
                CAknTransitionUtils::EOptionsMenu, demarcation );
            GfxTransEffect::SetDemarcation( iMenuPane, demarcation );
            GfxTransEffect::End( iMenuPane );
            
            // do the fading a bit later than in StopDisplayingMenuBar
            iExt->FadeBehindPopup( EFalse );
            
	        if ( AknLayoutUtils::PenEnabled() )
                {
                MTouchFeedback* feedback = MTouchFeedback::Instance();
                if ( feedback )
                    {
                    TTouchLogicalFeedback fbLogicalType = ETouchFeedbackPopUp;
                    if ( CAknTransitionUtils::TransitionsEnabled( AknTransEffect::EComponentTransitionsOff ) )
                        {
                        fbLogicalType = ETouchFeedbackPopupClose;
                        }
                    feedback->InstantFeedback(
                                           this,
                                           fbLogicalType,
                                           ETouchFeedbackVibra,
                                           TPointerEvent() );
                    }
                }
            break;
// AKNLAF end
        default:
            break;
        }
    }


EXPORT_C void CEikMenuBar::ReduceRect(TRect& aRect) const
    {
    if (!IsVisible())
        return;
    aRect.iTl.iY+=iSize.iHeight;
    }


void CEikMenuBar::AddFEPMenuL()
    {
    if (iPreventFepMenu)
        {
        iPreventFepMenu = EFalse;
        iTitleArray->DeleteResource(R_AVKON_MENUPANE_LANGUAGE_DEFAULT);
        iTitleArray->DeleteResource(R_AVKON_MENUPANE_EDITTEXT_DEFAULT);
        iTitleArray->DeleteResource(R_AVKON_MENUPANE_FEP_DEFAULT);
        }
    else
        {
        AddMenuIfNotPresentL(R_AVKON_MENUPANE_LANGUAGE_DEFAULT);
        AddMenuIfNotPresentL(R_AVKON_MENUPANE_EDITTEXT_DEFAULT);
        AddMenuIfNotPresentL(R_AVKON_MENUPANE_FEP_DEFAULT);
        }
    }

void CEikMenuBar::AddMenuIfNotPresentL(TInt aResourceId)
    {
    TInt titleCount = iTitleArray->Count();
    for (TInt ii=0; ii<titleCount; ii++)
        {
        if ((*(iTitleArray))[ii]->iData.iMenuPaneResourceId == aResourceId)
            return;
        }

    // Automatically add the FEP menu to the top of the menu
    CEikMenuBarTitle* title = new(ELeave) CEikMenuBarTitle;
    CleanupStack::PushL(title);
    title->iData.iMenuPaneResourceId = aResourceId;
    title->iTitleFlags=0;
    iTitleArray->AddTitleL(title);
    CleanupStack::Pop();
    }


EXPORT_C CEikMenuPane* CEikMenuBar::MenuPane()
    {
    return iMenuPane;
    }

EXPORT_C CEikMenuBar::CTitleArray* CEikMenuBar::TitleArray()
    {
    return iTitleArray;
    }

EXPORT_C void CEikMenuBar::SetEditMenuObserver(MEikMenuObserver* aEditMenuObserver)
    {
    iEditMenuObserver = aEditMenuObserver;
    }

void CEikMenuBar::UpdateTitleTextBaseline()
    {
    iBaseLine = LafMenuBar::NormalFont(iEikonEnv->LafEnv())->AscentInPixels() + LafMenuBar::ExtraBaselineOffsetForFirstPaneItem();
    if (iTitleArray)
        {
        const TInt count = iTitleArray->Count();
        TInt maxTitleHeight = LafMenuBar::NormalFont(iEikonEnv->LafEnv())->HeightInPixels();
        TInt baselineOffset = 0;
        for (TInt ii = 0; ii < count; ii++)
            {
            CEikMenuBarTitle* title=(*iTitleArray)[ii];
            title->CalculateBaseLine(iBaseLine, maxTitleHeight);
            }
        iBaseLine += baselineOffset;
        }
    }
EXPORT_C void CEikMenuBar::RemoveEditMenuObserver(MEikMenuObserver* aEditMenuObserver)
    {
    if (iActiveEditMenuObserver == aEditMenuObserver)
        iActiveEditMenuObserver = NULL;
    if (iEditMenuObserver == aEditMenuObserver)
        iEditMenuObserver = NULL;
    }

//
// class CEikMenuPaneTitle
//

EXPORT_C CEikMenuPaneTitle::CEikMenuPaneTitle(CEikMenuBar* aMenuBar)
    : iMenuBar(aMenuBar)
    {
    AKNTASHOOK_ADD( this, "CEikMenuPaneTitle" );
    }

EXPORT_C void CEikMenuPaneTitle::ConstructL()
    {
    }

EXPORT_C void CEikMenuPaneTitle::SetSelectedTitle(TInt /*aSelectedTitle*/)
    {
    }

EXPORT_C void CEikMenuPaneTitle::Draw(const TRect& /*aRect*/) const
    {
    }

EXPORT_C void CEikMenuPaneTitle::HandlePointerEventL(const TPointerEvent&)
    {
    }

EXPORT_C void* CEikMenuPaneTitle::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C TMargins CEikMenuPaneTitle::Margins() const
    {
    return iBorder.Margins();
    }

EXPORT_C void CEikMenuPaneTitle::Close()
    {
    }

/**
 * Gets the list of logical colors employed in the drawing of the control,
 * paired with an explanation of how they are used. Appends the list to aColorUseList.
 *
 * @since ER5U
 */
EXPORT_C void CEikMenuPaneTitle::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const
    {
    LafMenuPaneTitle::GetColorUseListL(aColorUseList);
    }

/**
 * Handles a change to the control's resources of type aType
 * which are shared across the environment, e.g. colors or fonts.
 *
 * @since ER5U
 */
EXPORT_C void CEikMenuPaneTitle::HandleResourceChange(TInt /*aType*/)
    {
    }
/**
 * Allows the client to determine if the menubar instance is displayed ("UP")
 *
 * @since Avkon 
 */
EXPORT_C TBool CEikMenuBar::IsDisplayed()
    {
    return MenuHasPane();
    }

EXPORT_C void CEikMenuBar::SetMenuType(TMenuType aMenuType)
    {
    iExt->iMenuType = aMenuType;
    }

EXPORT_C CEikMenuBar::TMenuType CEikMenuBar::GetMenuType() const
    {
    return iExt->iMenuType;
    }


EXPORT_C TBool CEikMenuBar::ItemSpecificCommandsEnabled() const
    {
    TBool enabled( ETrue );
    if ( iExt->iItemActionMenu &&
            !iExt->iItemActionMenu->CollectionHighlightVisible() )
        {
        enabled = EFalse;
        }
    return enabled;
    }


void CEikMenuBar::SetItemActionMenu( CAknItemActionMenu* aItemActionMenu )
    {
    if ( aItemActionMenu )
        {
        iExt->iItemActionMenu = aItemActionMenu;
        iExt->iItemActionMenu->SetMenuBar( iMenuObserver, this );
        }
    }


CAknItemActionMenu* CEikMenuBar::ItemActionMenu() const
    {
    return iExt->iItemActionMenu;
    }

CEikMenuPane* CEikMenuBar::PopulateItemActionMenuL(
        CAknItemActionMenu& aItemActionMenu )
    {
    CEikMenuPane* menuPane( NULL );
    CAiwServiceHandler::ReportMenuLaunch();
    if ( !iExt->iItemActionMenu )
        {
        SetItemActionMenu( &aItemActionMenu );
        }

    if ( iMenuTitleResourceId )
        {
        menuPane = CEikMenuPane::NewItemCommandMenuL( iMenuObserver );
        CleanupStack::PushL( menuPane );
        iMenuObserver->RestoreMenuL(
                this,
                iMenuTitleResourceId,
                MEikMenuObserver::EMenuBar );
        TInt titles = iTitleArray->Count();
        if ( titles > 0 )
            {
            titles--;
            while ( titles >= 0 )
                {
                TInt resource
                    = ( *iTitleArray )[ titles ]->iData.iMenuPaneResourceId;

                if ( iCoeEnv->IsResourceAvailableL( resource ) )
                    {
                    menuPane->AddMenuItemsL( resource, 0 );
                    iMenuObserver->DynInitMenuPaneL( resource, menuPane );                    
                    }
                titles--;
                }
            menuPane->AddMenuItemsToItemActionMenuL(
                    iExt->iItemActionMenu->MenuData() );
            }
        iTitleArray->ResetAndDestroy();
        CleanupStack::Pop( menuPane );
        }
    return menuPane;
    }


void CEikMenuBar::CloseState()
    {
    StopDisplayingMenuBar();
    }

EXPORT_C void CEikMenuBar::TryDisplayMenuBarWithoutFepMenusL()
    {
    iPreventFepMenu = ETrue;
    TryDisplayMenuBarL();
    }

TTypeUid::Ptr CEikMenuBar::MopSupplyObject(TTypeUid aId)
    {
    return SupplyMopObject(aId, iMenuCba);
    }
