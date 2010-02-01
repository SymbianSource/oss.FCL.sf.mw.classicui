/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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



#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikctrlstatus.h>
#include <uikon/eikenvinterface.h>
#endif
#include <eikcolib.h>
#include <eikappui.h>
#include <eiktbar.h>
#include <eikcoctl.rsg>
#include <eikenv.h>
#include <eikdoc.h>
#include <eiklabel.h>
#include <uikon.hrh>
#include <eikapp.h>
#include <eikmenub.h>
#include <eikhkeyt.h>
#include <eikhkeyc.h>
#include <eikpanic.h>
#include <eikcmbut.h>
#include <eiksfont.h>
#include <eikedwin.h>
#include <eikmnbut.h>
#include <eikimage.h>
#include <eiklbbut.h>
#include <eiktxlbx.h>
#include <eikfnlab.h>
#include <eikbtgpc.h>
#include <eikscrlb.h>
#include <uiklaf/private/lafappui.h>
#include "LAFMENUB.H"
#include <eikbtpan.h>
#include <barsread.h>
#include <barsc.h>
#include <eikcba.h>
#include "eikmop.h"
#include <AknSgcc.h>
#include <AknLayout.lag>
#include <eikcoctlpanic.h>
#include <akntoolbar.h>
#include <akntoolbarextension.h>
#include <aknappui.h>

#ifdef RD_SCALABLE_UI_V2
#include <featmgr.h>
#include <bldvariant.hrh>
#include <akntouchpane.h>
#include <AknStatuspaneUtils.h>
#include <aknpriv.rsg>
#endif // RD_SCALABLE_UI_V2

#include <layoutmetadata.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <AknPriv.hrh>
#include <aknlayout.cdl.h>

// Static DLL functions
GLDEF_C void Panic(TEikPanic aPanic)
    {
    _LIT(KPanicCat,"EIKCOCTL");
    User::Panic(KPanicCat,aPanic);
    }

GLDEF_C void Panic(TEikCoCtlPanic aPanic)
    {
    _LIT(KPanicCat,"AVKON-EIKCOCTL");
    User::Panic(KPanicCat,aPanic);
    }

///////////////////////////////////////////////////////////////////////////////////////
//
// CEikAppUiFactoryExtension
//
///////////////////////////////////////////////////////////////////////////////////////
    
class CEikAppUiFactoryExtension : public CBase
    {
    public:
        static CEikAppUiFactoryExtension* NewL();
        void ReadAppInfoResourceExtensionL( TInt aResourceId );
        ~CEikAppUiFactoryExtension();
        void CreateDefaultToolbarL();
    private:
        CEikAppUiFactoryExtension();
        void ConstructL();
    public:
        CEikButtonGroupContainer* iCba;
        CAknTouchPane* iTouchPane;
        CAknToolbar* iPopupToolbar;
        CAknToolbar* iViewPopupToolbar; // not owned
        CAknToolbar* iFixedToolbar; 
        CAknToolbar* iViewFixedToolbar; // not owned
        TBool iSplitInput;
    };
    
CEikAppUiFactoryExtension* CEikAppUiFactoryExtension::NewL()
    {
    CEikAppUiFactoryExtension* self = new(ELeave) CEikAppUiFactoryExtension;
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
CEikAppUiFactoryExtension::~CEikAppUiFactoryExtension()
    {
    delete iCba;
#ifdef RD_SCALABLE_UI_V2 
    delete iTouchPane;
    delete iFixedToolbar; 
#endif // RD_SCALABLE_UI_V2
    delete iPopupToolbar;

    }
    
CEikAppUiFactoryExtension::CEikAppUiFactoryExtension()
    {
    iSplitInput = EFalse;
    }
    
void CEikAppUiFactoryExtension::ConstructL()
    {
    }
    
void CEikAppUiFactoryExtension::ReadAppInfoResourceExtensionL( TInt aExtResourceId )
    {    
    struct SEikAppInfoExtension
        {
        TInt iTouchPaneId;
        TInt iPopupToolbarId;
        TInt iSpare1Id;
        TInt iSpare2Id;
        } appInfoExt;
       
        TPtr8 ptr( ( TText8* )&appInfoExt, sizeof( appInfoExt ) );
        // set all members of appInfo to zero, in case of ignored 
        // leave during resource reading
        ptr.FillZ(ptr.MaxLength());     

    // if application resource structure has extension    
    if ( aExtResourceId )
        {
        CCoeEnv::Static()->ReadResourceAsDes8L( ptr, aExtResourceId );
        }
        
#ifdef RD_SCALABLE_UI_V2
    FeatureManager::InitializeLibL();
    if ( FeatureManager::FeatureSupported( KFeatureIdPenSupport ) )
        {
        delete iTouchPane; iTouchPane = NULL;

        if ( appInfoExt.iTouchPaneId )
            {
            iTouchPane = CAknTouchPane::NewL( appInfoExt.iTouchPaneId );
            }
        else
            {
            iTouchPane = CAknTouchPane::NewL();
            }
        }
    FeatureManager::UnInitializeLib();
#endif // RD_SCALABLE_UI_V2
        
    if ( appInfoExt.iPopupToolbarId )
        {
        if ( iPopupToolbar )
            {
            delete iPopupToolbar;
            iPopupToolbar = NULL;
            }
        iPopupToolbar = CAknToolbar::NewL( appInfoExt.iPopupToolbarId );
        CEikonEnv* eikEnv = CEikonEnv::Static();
        CAknAppUi* base = (CAknAppUi*)eikEnv->EikAppUi();
        if (base)
            {
            iPopupToolbar->SetMopParent(base);
            }
#ifdef RD_SCALABLE_UI_V2 
        if ( iPopupToolbar->ToolbarFlags() & KAknToolbarFixed )
            {
            iFixedToolbar = iPopupToolbar; 
            iPopupToolbar = NULL; 
            }
        if ( iTouchPane )
            {
            iPopupToolbar->SetObserver( iTouchPane );
            }
#endif // RD_SCALABLE_UI_V2
        }
    if ( !iFixedToolbar ) 
        {
        CreateDefaultToolbarL();
        }
    }
    
void CEikAppUiFactoryExtension::CreateDefaultToolbarL()
    {
    if ( !iFixedToolbar ) 
        {
        iFixedToolbar = CAknToolbar::NewL( R_AKNPRIV_TOOLBAR );
        CEikonEnv* eikEnv = CEikonEnv::Static();
        CAknAppUi* base = (CAknAppUi*)eikEnv->EikAppUi();
        if (base)
            {
            iFixedToolbar->SetMopParent(base);
            }
        }
    }

///////////////////////////////////////////////////////////////////////////////////////
//
// CEikCoCtlLibrary
//
///////////////////////////////////////////////////////////////////////////////////////
CEikCoCtlLibrary::CEikCoCtlLibrary()
    {
    }

///////////////////////////////////////////////////////////////////////////////////////
//
// ResourceFile
//
///////////////////////////////////////////////////////////////////////////////////////
EXPORT_C TFileName CEikCoCtlLibrary::ResourceFile()
    {
    _LIT(KResFileName,"z:\\resource\\eikcoctl.rsc");
    return KResFileName();
    }

///////////////////////////////////////////////////////////////////////////////////////
//
// ControlFactory
//
///////////////////////////////////////////////////////////////////////////////////////
EXPORT_C TCreateByTypeFunction  CEikCoCtlLibrary::ControlFactory()
    {
    return CreateByTypeL;
    }

/**
 * @internal
 * Internal to Symbian
 * @since App-Framework_6.1
 */
EXPORT_C TCreateButtonGroupByTypeFunction CEikCoCtlLibrary::ButtonGroupFactory()
    {//static
    return CreateButtonGroupByTypeL;
    }

///////////////////////////////////////////////////////////////////////////////////////
//
// CreateByTypeL
//
///////////////////////////////////////////////////////////////////////////////////////
SEikControlInfo CEikCoCtlLibrary::CreateByTypeL(TInt aControlType)
    {
    SEikControlInfo controlInfo;
    controlInfo.iControl = NULL;
    controlInfo.iTrailerTextId = 0;
    controlInfo.iFlags = 0;

    switch (aControlType)
        {
    case EEikCtEdwin:
        controlInfo.iControl = new(ELeave) CEikEdwin;
        break;
    case EEikCtListBox:
        controlInfo.iControl = new(ELeave) CEikTextListBox;
        break;
    case EEikCtLabel:
        controlInfo.iControl = new(ELeave) CEikLabel;
        controlInfo.iFlags = EEikControlIsNonFocusing|EEikControlHasExtraAscent;
        break;
    case EEikCtImage:
        controlInfo.iControl = new(ELeave) CEikImage;
        controlInfo.iFlags = EEikControlIsNonFocusing;
        break;
    case EEikCtCommandButton:
        controlInfo.iControl= new(ELeave) CEikCommandButton;
        controlInfo.iFlags = EEikControlIsNonFocusing;
        break;
    case EEikCtFileNameLabel:
        controlInfo.iControl = new(ELeave) CEikFileNameLabel;
        controlInfo.iFlags = EEikControlIsNonFocusing;
        break;
    case EEikCtMenuButton:
        controlInfo.iControl= new(ELeave) CEikMenuButton;
        break;
    case EEikCtTextButton:
        controlInfo.iControl= new(ELeave) CEikTextButton;
        controlInfo.iFlags = EEikControlIsNonFocusing;
        break;
    case EEikCtBitmapButton:
        controlInfo.iControl= new(ELeave) CEikBitmapButton;
        controlInfo.iFlags = EEikControlIsNonFocusing;
        break;
    case EEikCtLabeledButton:
        controlInfo.iControl = new(ELeave) CEikLabeledButton;
        controlInfo.iFlags = EEikControlIsNonFocusing;
        break;
    case EEikCtTwoPictureCommandButton:
        controlInfo.iControl= new(ELeave) CEikTwoPictureCommandButton;
        controlInfo.iFlags = EEikControlIsNonFocusing;
        break;
    case EEikCtInverterCommandButton:
        controlInfo.iControl= new(ELeave) CEikInverterCommandButton;
        controlInfo.iFlags = EEikControlIsNonFocusing;
        break;
    case EEikCtScrollBar:
        controlInfo.iControl    = new(ELeave) CEikScrollBar;
        controlInfo.iFlags  = EEikControlIsNonFocusing;
        break;
    case EAknCtToolbarExtension:
        controlInfo.iControl = CAknToolbarExtension::NewL();
        break;
    default:
        break;
        }
    return controlInfo;
    }

/**
 * Creates the button group identified by aButtonGroupType, if it exists in this button
 * group factory.  Extra required information is supplied in aCreationData.  If the button group
 * is to be added to the button group stack then this can be set in aAddToButtonGroupStack.
 * If the aButtonGroupType value does not exist, then it returns NULL.
 *
 * @internal
 * Internal to Symbian
 * @since App-Framework_6.1
 */
MEikButtonGroup* CEikCoCtlLibrary::CreateButtonGroupByTypeL(TInt aButtonGroupType,EikButtonGroupFactory::TCreationData& aCreationData,TBool& aAddToButtonGroupStack)
    {//static
    MEikButtonGroup* buttonGroup = NULL;

    switch (aButtonGroupType)
        {
    case EEikBgToolBar:
        {
        CEikToolBar* toolBar=new(ELeave) CEikToolBar;
        CleanupStack::PushL(toolBar);
        TRect rect(CCoeEnv::Static()->ScreenDevice()->SizeInPixels());
        toolBar->ConstructL(aCreationData.iCommandObserver,aCreationData.iResourceId,rect);
        CleanupStack::Pop(); // toolBar
        buttonGroup = toolBar;
        }
        break;
    case EEikBgButtonPanel:
        {
        CEikButtonPanel* buttonPanel=new(ELeave) CEikButtonPanel;
        CleanupStack::PushL(buttonPanel);
        CEikButtonGroupContainer* container = static_cast<CEikButtonGroupContainer*>(aCreationData.iCommandObserver);
        buttonPanel->SetContainerWindowL(*container);
        buttonPanel->SetCommandObserver(aCreationData.iCommandObserver);
        if (aCreationData.iResourceId==0)
            buttonPanel->ConstructL();
        else
            {
            TResourceReader reader;
            CCoeEnv::Static()->CreateResourceReaderLC(reader,aCreationData.iResourceId);
            buttonPanel->ConstructFromResourceL(reader);
            CleanupStack::PopAndDestroy(); // reader
            }
        if (aCreationData.iOrientation==CEikButtonGroupContainer::EHorizontal)
            buttonPanel->SetHorizontal();
        CleanupStack::Pop(); // buttonPanel
        buttonGroup = buttonPanel;
        }
        break;
    case EEikBgCba:
        {
        buttonGroup = CEikCba::NewLC(aCreationData.iResourceId, NULL,
            aCreationData.iCommandObserver, aCreationData.iParentWg,
            aCreationData.iFlags);
        CleanupStack::Pop(); // cba
        aAddToButtonGroupStack=ETrue;
        }
        break;
    default:
        break;
        }
    return buttonGroup;
    }


/**
 * @internal
 */
EXPORT_C CEikAppUiFactory::CEikAppUiFactory()
    : iSidebarPopupId(-1)
    {
    }

/**
 * @internal
 */
CEikAppUiFactory::~CEikAppUiFactory()
    {
    CCoeAppUi* appUi = CEikonEnv::Static()->EikAppUi();
    if ( appUi )
        appUi->RemoveFromStack(iMenuBar);
    delete(iMenuBar);
    delete(iToolBar);
    delete(iToolBand);
    delete(iTitleBand);
    delete(iStatusPane);
    delete(iExtension);
    }

CEikCommandButton* CEikAppUiFactory::CreateStandardTabButtonL() const
    {
    CEikCommandButton *tabButton= new(ELeave) CEikCommandButton;
    CleanupStack::PushL(tabButton);
    TBuf<1> buf;
    buf.Append(TChar(ESymFontTabout));
    tabButton->SetTextL(buf);
    tabButton->Label()->SetFont(CEikonEnv::Static()->SymbolFont());
    const TInt height = CEikonEnv::Static()->EditableControlStandardHeight();
    tabButton->SetSize(TSize(height+3,height));
    CleanupStack::Pop();
    return(tabButton);
    }

void CEikAppUiFactory::CreateEmbeddedL(CEikonEnv& aEikonEnv)
    {
    CEikAppUiFactory* embeddedAppUiFactory = new(ELeave) CEikAppUiFactory();
    CleanupStack::PushL(embeddedAppUiFactory);
    aEikonEnv.AddAppUiFactoryL(embeddedAppUiFactory);
    CleanupStack::Pop();
    }

void CEikAppUiFactory::DestroyEmbedded(CEikonEnv& aEikonEnv)
    {
    aEikonEnv.RemoveAppUiFactory();
    delete this;
    }

void CEikAppUiFactory::CreateResourceIndependentFurnitureL(CEikAppUi* aAppUi)
    {
#ifdef RD_SCALABLE_UI_V2
    FeatureManager::InitializeLibL();
    if ( FeatureManager::FeatureSupported( KFeatureIdPenSupport ) )
        {
        if ( !iExtension )
            {
            iExtension = CEikAppUiFactoryExtension::NewL();
            }

        if ( iExtension && !( iExtension->iTouchPane ) )
            {
            iExtension->iTouchPane = CAknTouchPane::NewL();
            }
            
        if ( iExtension )
            {
            iExtension->CreateDefaultToolbarL();
            }
        }
    FeatureManager::UnInitializeLib();
#endif // RD_SCALABLE_UI_V2

    if(aAppUi->ContainerAppUi())
        {
        AddTitleBandL(aAppUi);
        }
    CEikonEnv* eikEnv = CEikonEnv::Static();
    if (eikEnv->StatusPaneCoreResId() != 0)
        {
        iStatusPane = CEikStatusPane::NewL(*eikEnv, &eikEnv->RootWin(), eikEnv->StatusPaneCoreResId(), EEikStatusPaneUseDefaults);
        CAknSgcClient::HandleChangeL(); // has to be called after iStatusPane is assigned
        }
    }

void CEikAppUiFactory::AddTitleBandL(CEikAppUi* /*aAppUi*/)
    {
/* AKNLAF - Series 60 does not require a title band for embedded apps
    iTitleBand=new(ELeave) CEikToolBar;
    iTitleBand->StaticConstructL(aAppUi,R_EIK_TBAR_TITLE);
    TBuf<64> tmp;
    const TApaAppCaption& object=aAppUi->Document()->AppCaption();
    const TApaAppCaption& container=aAppUi->ContainerAppUi()->Document()->AppCaption();
    CCoeEnv::Static()->Format128(tmp,R_EIK_TBUF_TITLE_BAR_LABEL,&object,&container);
    STATIC_CAST(CEikLabel*,iTitleBand->ControlById(EEikCidTitleBarLabel))->SetTextL(tmp);
    CCoeControl* ctrl=iTitleBand->ControlById(EEikCidTitleBatFileNameLabel);
    if (ctrl)
        {
        const TInt index=iTitleBand->IndexById(EEikCidTitleBatFileNameLabel);
        CArrayFix<TEikGroupControl>* ctrlArray=iTitleBand->ControlArray();
        if (index==ctrlArray->Count()-1)
            {
            const TInt width=(iToolBar ? iToolBar->Size().iWidth : KEikStdFileNameLabelWidth);
            (*ctrlArray)[index].SetLength(width);
            STATIC_CAST(CEikFileNameLabel*,iTitleBand->ControlById(EEikCidTitleBatFileNameLabel))->UpdateL();
            }
        }
    const TRect rect(aAppUi->ApplicationRect());
    iTitleBand->SetBoundingRect(rect);
    if (!(iTitleBand->DelayActivation()))
        iTitleBand->ActivateL();
*/
    }


TRect CEikAppUiFactory::ClientRect()
    {
    CCoeEnv* env = CCoeEnv::Static();
    TRect rect = LafAppUi::ClientRect( *env, *this );

#ifdef RD_SCALABLE_UI_V2
    if ( TouchPane() )
        {
        TouchPane()->ReduceRect( rect );
        }

    CAknToolbar* toolbar = CurrentFixedToolbar();

    // reduce fixed toolbar's area
    if ( toolbar )
        {
        TInt flags = toolbar->ToolbarFlags();

        if ( flags & KAknToolbarFixed && !( flags & KAknToolbarDefault ) )
            {
            toolbar->ReduceRect( rect );
            }
        }

	  // recaculate the client rect is splitinput is enabled.
    if ( iExtension && iExtension->iSplitInput )
        {
        TInt inputTop = rect.iBr.iY;
        TAknLayoutRect splitwnd;
		TRect screenRect ;
		AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screenRect );

        if ( Layout_Meta_Data::IsLandscapeOrientation() )
            {
            splitwnd.LayoutRect( screenRect, AknLayoutScalable_Avkon::popup_fep_vkbss_window (0).LayoutLine() );
            TRect wndRc = splitwnd.Rect();
            inputTop = wndRc.iTl.iY;
            }
        else
            {
            splitwnd.LayoutRect( screenRect, AknLayoutScalable_Avkon::popup_fep_ituss_window(0).LayoutLine() );
            TRect wndRc = splitwnd.Rect();
            inputTop = wndRc.iTl.iY;
            }
        rect.iBr.iY = rect.iBr.iY > inputTop ? inputTop : rect.iBr.iY;
        rect.iTl.iY = 0;
        }

#endif // RD_SCALABLE_UI_V2	

    return rect;
    }

void CEikAppUiFactory::ReadAppInfoResourceL(TInt aResourceFileOffset, CEikAppUi* aAppUi)
    {
    const TInt resourceFileOffset=(aResourceFileOffset)? aResourceFileOffset : aAppUi->Application()->ResourceFileOffset();
    SEikAppInfo appInfo;
    TPtr8 ptr((TText8*)&appInfo,sizeof(appInfo));
    ptr.FillZ(ptr.MaxLength());     // set all members of appInfo to zero, in case of ignored leave during resource reading
    CCoeEnv::Static()->ReadResourceAsDes8L(ptr,EAppInfoResourceOffset+resourceFileOffset);
    
    if (!iExtension)
        {
        iExtension = CEikAppUiFactoryExtension::NewL();
        }

    iExtension->ReadAppInfoResourceExtensionL(appInfo.iExtensionId);

    if (appInfo.iMenuBarId)
        {
        iMenuBar=new(ELeave) CEikMenuBar;
        iMenuBar->ConstructL(aAppUi,appInfo.iHotKeysId,appInfo.iMenuBarId);
        aAppUi->AddToStackL(iMenuBar,ECoeStackPriorityMenu,ECoeStackFlagRefusesFocus);
        if (LafMenuBar::IsAlwaysVisible())
            {
            iMenuBar->TryDisplayMenuBarL();
            }
        }
    TRect boundingRect=ClientRect(); // make toolband stretch to the screen width by default
    // !!! Toolbar / CBA decision should be made in the LAF.
    CEikonEnv* eikEnv = CEikonEnv::Static();
    if (eikEnv->StatusPaneCoreResId() != 0)
        {
        iStatusPane = CEikStatusPane::NewL(*eikEnv, &eikEnv->RootWin(), eikEnv->StatusPaneCoreResId(), appInfo.iStatusPaneId);
        CAknSgcClient::HandleChangeL(); // has to be called after iStatusPane is assigned
        iStatusPane->ReduceRect(boundingRect);

#ifdef RD_SCALABLE_UI_V2
        // Hide touch pane when compatible statuspane is no active
        if ( TouchPane() && !AknStatuspaneUtils::TouchPaneCompatibleLayoutActive() )
            {
            TouchPane()->MakeVisible( EFalse );
            }
#endif // RD_SCALABLE_UI_V2

#ifdef RD_SCALABLE_UI_V2
        // Hide toolbar when compatible statuspane is not active
        if ( iExtension->iFixedToolbar && ( !AknStatuspaneUtils::TouchPaneCompatibleLayoutActive() ||
            appInfo.iStatusPaneId == R_AVKON_STATUS_PANE_LAYOUT_EMPTY ) )
            {
            iExtension->iFixedToolbar->SetToolbarVisibility( EFalse );
            }
#endif // RD_SCALABLE_UI_V2


        }

    if (appInfo.iCbaId)
        {
        iExtension->iCba = CEikButtonGroupContainer::NewL(CEikButtonGroupContainer::ECba,
            CEikButtonGroupContainer::EHorizontal/*LafCba::Orientation()*/, aAppUi,appInfo.iCbaId);
        iExtension->iCba->SetBoundingRect(boundingRect);
        iExtension->iCba->ReduceRect(boundingRect);
//      iToolBar=CEikButtonGroupContainer::NewL(CEikButtonGroupContainer::ECba,
//                                              CEikButtonGroupContainer::EVertical,
//                                              aAppUi,appInfo.iCbaId);
//      iToolBar->SetBoundingRect(boundingRect);
        }
    if (appInfo.iToolBarId)
        {
        iToolBar=CEikButtonGroupContainer::NewL(CEikButtonGroupContainer::EToolbar,CEikButtonGroupContainer::EVertical,
                                                aAppUi,appInfo.iToolBarId);
        iToolBar->SetBoundingRect(boundingRect);
        }
    if (aAppUi->ContainerAppUi())
        AddTitleBandL(aAppUi);
    if (appInfo.iToolBandId)
        {
        boundingRect.iTl.iY=ClientRect().iTl.iY;
        iToolBand=new(ELeave) CEikToolBar;
        iToolBand->StaticConstructL(aAppUi,appInfo.iToolBandId);
        if (iTitleBand)
            iToolBand->SetAdjacent(EGulAdjTop);
        iToolBand->SetBoundingRect(boundingRect);
        if (!iToolBand->DelayActivation())
            iToolBand->ActivateL();
        if (iToolBar) // in case toolbar/band overlap, put bar in front
            iToolBar->DrawableWindow()->SetOrdinalPosition(0);
        }
    if (iTitleBand) // put title band in front
        iTitleBand->DrawableWindow()->SetOrdinalPosition(0);
    
    }

void CEikAppUiFactory::LaunchPopupMenuL(
                            TInt aResourceId,
                            const TPoint& aTargetPos,
                            TPopupTargetPosType aTargetType,
                            const CEikHotKeyTable* aHotKeyTable,
                            CEikAppUi* aAppUi)
    {
    ClosePopup(aAppUi);
    iPopup=new(ELeave) CEikMenuPane(aAppUi);
    TRAPD(err,DoLaunchPopupL(aResourceId,aTargetPos,aHotKeyTable,aTargetType, aAppUi));
    if (err)
        {
        ClosePopup(aAppUi);
        User::Leave(err);
        }
    }

void CEikAppUiFactory::DoLaunchPopupL(TInt aResourceId,
                                      const TPoint& aTargetPos,
                                      const CEikHotKeyTable* aHotKeyTable,
                                      TPopupTargetPosType aTargetType,
                                      CEikAppUi* aAppUi)
    {
    iPopup->ConstructL(NULL);
    aAppUi->RestoreMenuL(iPopup,aResourceId,MEikMenuObserver::EMenuPane);
    iPopup->SetPointerCapture(ETrue);
    aAppUi->AddToStackL(iPopup,ECoeStackPriorityDialog);
    iPopup->StartDisplayingMenuPane(aHotKeyTable,aTargetPos,NULL,0,aTargetType);
    }

void CEikAppUiFactory::ClosePopup(CEikAppUi* aAppUi)
    {
    if (iPopup)
        {
        aAppUi->RemoveFromStack(iPopup);
        delete(iPopup);
        iPopup=NULL;
        }
    iSidebarPopupId=-1;
    }

void CEikAppUiFactory::StopDisplayingMenuBar()
    {
    if (iMenuBar)
            iMenuBar->StopDisplayingMenuBar();
    }

void CEikAppUiFactory::HandleSideBarMenuL(
                            TInt aResourceId,
                            const TPoint& aPos,
                            const CEikHotKeyTable* aHotKeyTable,
                            CEikAppUi* aAppUi)
    {
    TBool launchSidebarPopup(iSidebarPopupId!=aResourceId && (aResourceId==R_EIK_SIDEBAR_EDIT_MENU || aResourceId==R_EIK_SIDEBAR_IRDA_MENU));
    if (iPopup)
        ClosePopup(aAppUi);// sets iSidebarPopupId to -1
    if (aResourceId==0) // 0 indicates menu bar
        {
        iMenuBar->TryDisplayMenuBarL();
        const TInt title=iMenuBar->SelectedTitle();
        const TInt item=iMenuBar->SelectedItem();
        iMenuBar->MoveHighlightToL(title, (item>=0?item:0));
        return;
        }
    // otherwise a popup menu
    if (iMenuBar)
        iMenuBar->StopDisplayingMenuBar();
    if (launchSidebarPopup)
        {
        LaunchPopupMenuL(aResourceId,aPos,EPopupTargetTopLeft,aHotKeyTable, aAppUi);
        iSidebarPopupId=aResourceId;
        }
    }


void CEikAppUiFactory::CreateHotKeyControlL(TInt aResourceId, CEikAppUi* aAppUi)
    {
    CEikHotKeyTable* table=new(ELeave) CEikHotKeyTable;
    CleanupStack::PushL(table);
    table->ConstructFromResourceL(aResourceId);
    CEikHotKeyControl* control=new(ELeave) CEikHotKeyControl(table,aAppUi);
    CleanupStack::Pop(); // table now owned by control
    CleanupStack::PushL(control);
    aAppUi->AddToStackL(control,ECoeStackPriorityMenu,ECoeStackFlagRefusesFocus|ECoeStackFlagOwnershipTransfered);
    CleanupStack::Pop();
    }

CEikMenuBar* CEikAppUiFactory::MenuBar() const
    {
    return iMenuBar;
    }

CEikMenuBar* CEikAppUiFactory::SwapMenuBar(CEikMenuBar* aMenu)
    {
    CEikMenuBar* oldMenu=iMenuBar;
    iMenuBar=aMenu;
    return oldMenu;
    }

CEikMenuPane* CEikAppUiFactory::Popup() const
    {
    return iPopup;
    }

CEikButtonGroupContainer* CEikAppUiFactory::ToolBar() const
    {
   // return iToolBar;
    return (iExtension ? iExtension->iCba : NULL);
    }

CEikButtonGroupContainer* CEikAppUiFactory::SwapButtonGroup(CEikButtonGroupContainer* aNewGroup)
    {
    CEikButtonGroupContainer* old=iToolBar;
    iToolBar=aNewGroup;
    return old;
    }

CEikToolBar* CEikAppUiFactory::ToolBand() const
    {
    return iToolBand;
    }

CEikToolBar* CEikAppUiFactory::TitleBand() const
    {
    return iTitleBand;
    }

CEikStatusPane* CEikAppUiFactory::StatusPane() const
    {
    return iStatusPane;
    }

CEikButtonGroupContainer* CEikAppUiFactory::Cba() const
    {
    return (iExtension ? iExtension->iCba : NULL);
    }

CEikToolBar* CEikAppUiFactory::SwapToolBar(CEikToolBar* aToolBar,TToolBarType aType)
    {
    CEikToolBar* old=NULL;
    if (aType==EBand)
        {
        old=iToolBand;
        iToolBand=aToolBar;
        }
    else // aType==ETitle
        {
        old=iTitleBand;
        iTitleBand=aToolBar;
        }
    return old;
    }

void CEikAppUiFactory::HandleResourceChangeL(TInt aType)
    {
	
    if ( iExtension )
        {
        if ( aType == KAknSplitInputEnabled )
            {
            iExtension->iSplitInput = ETrue;
            }
        else if ( aType == KAknSplitInputDisabled )
            {
            iExtension->iSplitInput = EFalse;
            }
        }
    
    if(iStatusPane)
        iStatusPane->HandleResourceChange(aType);
    if(iExtension && iExtension->iCba)
        iExtension->iCba->HandleResourceChange(aType);
    if(iMenuBar)
        iMenuBar->HandleResourceChange(aType);
    if(iToolBar)
        iToolBar->HandleResourceChange(aType);
    if(iToolBand)
        iToolBand->HandleResourceChange(aType);
    if(iTitleBand)
        iTitleBand->HandleResourceChange(aType);
    if(iPopup)
        iPopup->HandleResourceChange(aType);
#ifdef RD_SCALABLE_UI_V2
    if (TouchPane())
        TouchPane()->HandleResourceChange(aType);
#endif // RD_SCALABLE_UI_V2
    }

EXPORT_C CAknTouchPane* CEikAppUiFactory::TouchPane() const
    {
    return (iExtension ? iExtension->iTouchPane : NULL);
    }

// -----------------------------------------------------------------------------
// CEikAppUiFactory::PopupToolbar
// Returns the toolbar for the application or NULL.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknToolbar* CEikAppUiFactory::PopupToolbar() const
    {
    // if there is specific floating toolbar for appui then that will be 
    // returned, otherwise fixed toolbar or NULL
    if ( iExtension )
        {
        if ( iExtension->iPopupToolbar ) 
            {
            return iExtension->iPopupToolbar; 
            }
        else 
            {
#ifdef RD_SCALABLE_UI_V2
            return iExtension->iFixedToolbar; 
#else 
            return NULL; 
#endif

            }
        }
    return NULL; 
    }
    
// -----------------------------------------------------------------------------
// CEikAppUiFactory::CurrentPopupToolbar
// If current view has toolbar it will return that one, otherwise it will return 
// application toolbar or NULL.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknToolbar* CEikAppUiFactory::CurrentPopupToolbar() const
    {
    // if there is specific toolbar for the view then this one will be returned, otherwise
    // application toolbar will be returned.
    if (!iExtension)
        return NULL;

    return iExtension->iViewPopupToolbar ?  iExtension->iViewPopupToolbar:  
                                            iExtension->iPopupToolbar;    
    }


    
// -----------------------------------------------------------------------------
// CEikAppUiFactory::CurrentFixedToolbar
// If current view has fixed toolbar it will return that one, otherwise it will 
// return application fixed toolbar or NULL.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknToolbar* CEikAppUiFactory::CurrentFixedToolbar() const
    {
    // if there is specific toolbar for the view then this one will be returned, otherwise
    // application toolbar will be returned.
    if (!iExtension)
        return NULL;

    return iExtension->iViewFixedToolbar ? iExtension->iViewFixedToolbar :
                                           iExtension->iFixedToolbar;                                       
    }


// -----------------------------------------------------------------------------
// CEikAppUiFactory::SetViewPopupToolbar
// Sets view specific toolbar when view is activated. Called by CAknView
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikAppUiFactory::SetViewPopupToolbar(CAknToolbar* aViewPopupToolbar)
    {
    // not sure if we should try to create extension here	
    if (iExtension)
        iExtension->iViewPopupToolbar = aViewPopupToolbar;
    }

// -----------------------------------------------------------------------------
// CEikAppUiFactory::SetViewPopupToolbar
// Sets view specific toolbar when view is activated. Called by CAknView
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikAppUiFactory::SetViewFixedToolbar(CAknToolbar* aViewFixedToolbar)
    {
    // not sure if we should try to create extension here	
    if (iExtension)
        iExtension->iViewFixedToolbar = aViewFixedToolbar;
    }



void CEikAppUiFactory::ReduceRect(TScreenFurniture aScreenFurniture,TRect& aRect) const
    {
    switch (aScreenFurniture)
        {
    case EMenuBar:
        if (iMenuBar)
            iMenuBar->ReduceRect(aRect);
        break;
    case EButtonGroup:
        if (iToolBar)
            iToolBar->ReduceRect(aRect);
        break;
    case EToolBand:
        if (iToolBand)
            iToolBand->ReduceRect(aRect);
        break;
    case ETitleBand:
        if (iTitleBand)
            iTitleBand->ReduceRect(aRect);
        break;
    case EStatusPane:
        {
        CEikStatusPaneBase* statusPane=CEikStatusPaneBase::Current();
        if (statusPane)
            statusPane->ReduceRect(aRect);
        break;
        }
    case ECba:
        if (iExtension && iExtension->iCba)
            iExtension->iCba->ReduceRect(aRect);
        break;
    default:
        break;
        }
    }

TTypeUid::Ptr CEikAppUiFactory::MopSupplyObject(TTypeUid aId)
    {
    return SupplyMopObject(aId, (iExtension ? iExtension->iCba : NULL), iMenuBar);
    }

//////////////////////////////////////////////////////////////////////////////////////
//
// END OF FILE
//
//////////////////////////////////////////////////////////////////////////////////////
