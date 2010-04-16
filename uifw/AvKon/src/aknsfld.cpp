/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
#include <aknenv.h>
#include <eikdef.h>
#include <aknsfld.h>
#include <akninfrm.h>   
#include <avkon.mbg>

#include <aknappui.h>
#include <eikon.rsg>        
#include <eikenv.h>
#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikenvinterface.h>
#endif
#include <txtglobl.h>
#include <gulfont.h>
#include <txtfrmat.h>
#include <eikedwin.h>
#include <uikon.hrh>
#include <aknconsts.h>
#include <aknEditStateIndicator.h>
#include <featmgr.h>                

#include <AknsListBoxBackgroundControlContext.h>
#include <AknsFrameBackgroundControlContext.h>
#include <AknsUtils.h>
#include "AknAdaptiveSearch.h"
#include <StringLoader.h>

#include <centralrepository.h>      // CenRep for AS
#include <AvkonInternalCRKeys.h>    // CenRep for AS

#include <AknTasHook.h>
#include <touchfeedback.h>

#include "aknSfldIndicatorFactory.h"
#include "aknsfldIndicator.h"

#include <eikbtgpc.h>
#include <eiklbx.h>
#include <skinlayout.cdl.h>

#include "akntrace.h"  // trace

using namespace SkinLayout;

// CONSTANTS
const TInt EUseSkinContext = 0x01;
const TInt EParentAbsolute = 0x02;
const TInt ETileIIDNone    = 0x04;
NONSHARABLE_CLASS(CHwKbSubscriber) : public CActive
    {
public:
    CHwKbSubscriber( TAny* aPtr, RProperty& aProperty );
    ~CHwKbSubscriber();
    
public: // New functions
    void SubscribeL();
    void StopSubscribe();
    static TInt HandlePropertyChaned( TAny* aPtr );
private: // from CActive
    void RunL();
    void DoCancel();
    
private:
    TCallBack  iCallBack;
    RProperty&  iProperty;
    };

CHwKbSubscriber::CHwKbSubscriber( TAny* aPtr, RProperty& aProperty )
    :CActive(EPriorityNormal), iCallBack( TCallBack( HandlePropertyChaned, aPtr)), 
     iProperty(aProperty)
    {
    CActiveScheduler::Add(this);
    }

CHwKbSubscriber::~CHwKbSubscriber()
    {
    Cancel();
    }

void CHwKbSubscriber::SubscribeL()
    {
    if (!IsActive())
        {
        iProperty.Subscribe(iStatus);
        SetActive();
        }
    }

void CHwKbSubscriber::StopSubscribe()
    {
    Cancel();
    }

TInt CHwKbSubscriber::HandlePropertyChaned( TAny* aPtr )
    {
    if ( aPtr )
        {
        TRAPD(err, 
              static_cast<CAknSearchField*>(aPtr)->HandleHWKeyboardModeChangeL());
        return err;
        }
    else
        {
        return KErrArgument;
        }
    }

void CHwKbSubscriber::RunL()
    {
    if (iStatus.Int() == KErrNone)
        {
        iCallBack.CallBack();
        SubscribeL();
        }
    }

void CHwKbSubscriber::DoCancel()
    {
    iProperty.Cancel();
    }


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknSearchField::CAknSearchField
// C++ default constructor.
// -----------------------------------------------------------------------------
//
CAknSearchField::CAknSearchField()
    {
    }
    
// -----------------------------------------------------------------------------
// CAknSearchField::~CAknSearchField
// Destructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknSearchField::~CAknSearchField()
    {
    AKNTASHOOK_REMOVE();
    if ( iCBAObserverUpdated && iCba )
        {
        iCba->RemoveCommandObserver( 2 );
        if ( iBackedAppUi && !iBackedAppUi->IsAppClosing() )
            {
            iCba->RemoveCommandFromStack( 2, EAknSoftkeyCancel );
            }
        }
    delete iEditor;
    delete iAdaptiveSearch;    
    delete iInputFrame;    
    delete iSkinContext;
    delete iInputContext; 
    delete iIndicator;
    delete iHwKbSub;
    iHwKeyboardPro.Close();
    }  
    
// -----------------------------------------------------------------------------
// CAknSearchField::NewL
// -----------------------------------------------------------------------------
//
EXPORT_C CAknSearchField* CAknSearchField::NewL( const CCoeControl& aParent, 
                                                 TSearchFieldStyle aFieldStyle, 
                                                 CGulIcon* aIcon, 
                                                 TInt aTextLimit )
    { 
    _AKNTRACE_FUNC_ENTER;
    CAknSearchField* self=new(ELeave) CAknSearchField();
    CleanupStack::PushL( self );
    _AKNTRACE( "[%s][%s] aSearchFieldStyle: %d", 
                            "CAknSearchField", __FUNCTION__, aFieldStyle );
    self->ConstructL( aParent, aFieldStyle, aIcon, aTextLimit );
    CleanupStack::Pop(); 
    AKNTASHOOK_ADDL( self, "CAknSearchField" );
    _AKNTRACE_FUNC_EXIT;
    return self;
    }   
        
NONSHARABLE_CLASS( CSearchFieldEditor ) : public CEikEdwin
    {
public:
    IMPORT_C TCoeInputCapabilities InputCapabilities() const;
    };
EXPORT_C TCoeInputCapabilities CSearchFieldEditor::InputCapabilities() const
    {
    TCoeInputCapabilities c( TCoeInputCapabilities::EAllText 
                | TCoeInputCapabilities::EWesternAlphabetic );
    c.MergeWith( CEikEdwin::InputCapabilities() );    
    return c;
    }
    
// -----------------------------------------------------------------------------
// CAknSearchField::ConstructL
// -----------------------------------------------------------------------------
//
void CAknSearchField::ConstructL( const CCoeControl& aParent,
                                  TSearchFieldStyle aFieldStyle,
                                  CGulIcon* aIcon, TInt aTextLimit )
    {
    SetMopParent( const_cast<CCoeControl*>(&aParent) );    
    iBackedAppUi = iAvkonAppUi;
    TFileName path(KAvkonBitmapFile);
    TInt bitmapId;
    TInt bitmapMaskId;    
    iIsPopup = EFalse; 
    TUint32 flags = NULL;

    iEditor = new ( ELeave ) CSearchFieldEditor;
    TBool isShowIndicator = EFalse;
    TBool ASEnabled = EFalse;
    if( AknLayoutUtils::PenEnabled())
        {
        ASEnabled = GetASStatusAndSubKbLayoutL( isShowIndicator );
        }
    else
        {
        isShowIndicator = ETrue;
        }         

    // Adaptive search is not allowed in popups anymore
    if ( aFieldStyle == EPopupAdaptiveSearch )
        {
        aFieldStyle = EPopup;
        }
    else if ( aFieldStyle == EPopupAdaptiveSearchWindow )
        {
        aFieldStyle = EPopupWindow;
        }

    switch ( aFieldStyle )
        {
        case EFixed:
            bitmapId = EMbmAvkonQgn_indi_find_glass;
            bitmapMaskId = EMbmAvkonQgn_indi_find_glass_mask;
            CreateWindowL( &aParent ); // This is now non-window owning control
            break;
        case ESearchWithoutLine:
            flags |= CAknInputFrame::EFixedFindWithoutLine;
        // FALL THROUGH/ no break here.
        case ESearch:
            bitmapId = EMbmAvkonQgn_indi_find_glass;
            bitmapMaskId = EMbmAvkonQgn_indi_find_glass_mask;
            SetContainerWindowL( aParent ); // This is now non-window owning control
            break;
        case EPopup:
            bitmapId = EMbmAvkonQgn_indi_find_glass;
            bitmapMaskId = EMbmAvkonQgn_indi_find_glass_mask;
            flags |= CAknInputFrame::EPopupLayout;
            CreateWindowL(); 
            iIsPopup = ETrue;
            if ( CAknEnv::Static()->TransparencyEnabled() )
                {
                Window().SetRequiredDisplayMode( EColor16MA );
                TInt err = Window().SetTransparencyAlphaChannel();
                if ( err == KErrNone )                    
                    Window().SetBackgroundColor(~0);                    
                }            
            break;
        case EPinb:
            bitmapId = EMbmAvkonQgn_indi_find_glass_pinb;
            bitmapMaskId = EMbmAvkonQgn_indi_find_glass_pinb_mask;
            flags |= CAknInputFrame::EPinbLayout;
            SetContainerWindowL( aParent ); // This is now non-window owning control
            break;
        case EClockApp:
            bitmapId = EMbmAvkonQgn_indi_find_glass;
            bitmapMaskId = EMbmAvkonQgn_indi_find_glass_mask;
            flags |= CAknInputFrame::EClockAppLayout;
            SetContainerWindowL( aParent ); // This is now non-window owning control
            break;
        case EPopupWindow:
            bitmapId = EMbmAvkonQgn_indi_find_glass;
            bitmapMaskId = EMbmAvkonQgn_indi_find_glass_mask;

            if ( AknLayoutUtils::PenEnabled() )
                {
                flags |= CAknInputFrame::EPopupWindowEmbeddedSoftkeys;
                }

            flags |= CAknInputFrame::EPopupWindowLayout;
            flags |= CAknInputFrame::EFixedFindWithoutLine;
            SetContainerWindowL( aParent ); // This is now non-window owning control
            break;
        case EAdaptiveSearch:
            bitmapId = EMbmAvkonQgn_indi_find_glass;
            bitmapMaskId = EMbmAvkonQgn_indi_find_glass_mask;
            SetContainerWindowL( aParent );  
            iColumnFlag = 0xFFFFFFFF;     
            if( AknLayoutUtils::PenEnabled() )
                {
                iAdaptiveSearch = CAknAdaptiveSearch::NewL( aTextLimit, aFieldStyle );       
                iAdaptiveSearch->SetSearchField( this );         
                if ( ASEnabled )
                    {
                    iEditor->AddFlagToUserFlags( CEikEdwin::EAvkonDisableVKB );
                    }
                TInt edwinFlag( iEditor->AknEdwinFlags() );
                iEditor->SetAknEditorFlags( edwinFlag | 
                        EAknEditorFlagAdaptiveSearch );
                }                    
            break; 
        case EAdaptive:
            bitmapId = EMbmAvkonQgn_indi_find_glass;
            bitmapMaskId = EMbmAvkonQgn_indi_find_glass_mask;
            CreateWindowL( &aParent ); 
            iColumnFlag = 0xFFFFFFFF; 
            if( AknLayoutUtils::PenEnabled() )
                {
                iAdaptiveSearch = CAknAdaptiveSearch::NewL( aTextLimit, aFieldStyle );       
                iAdaptiveSearch->SetSearchField( this ); 
                if ( ASEnabled )
                    {
                    iEditor->AddFlagToUserFlags( CEikEdwin::EAvkonDisableVKB );
                    }
                TInt edwinFlag( iEditor->AknEdwinFlags() );
                iEditor->SetAknEditorFlags( edwinFlag | 
                        EAknEditorFlagAdaptiveSearch );
                }                      
            break;
        case EPopupAdaptiveSearch:
            bitmapId = EMbmAvkonQgn_indi_find_glass;
            bitmapMaskId = EMbmAvkonQgn_indi_find_glass_mask;
            flags |= CAknInputFrame::EPopupLayout;
            CreateWindowL(); 
            iColumnFlag = 0xFFFFFFFF; 
            iIsPopup = ETrue;
            if( AknLayoutUtils::PenEnabled() )
                {
                iAdaptiveSearch = CAknAdaptiveSearch::NewL( aTextLimit, aFieldStyle );       
                iAdaptiveSearch->SetSearchField( this );  
                if ( ASEnabled )
                    {
                    iEditor->AddFlagToUserFlags( CEikEdwin::EAvkonDisableVKB );
                    }
                TInt edwinFlag( iEditor->AknEdwinFlags() );
                iEditor->SetAknEditorFlags( edwinFlag | 
                        EAknEditorFlagAdaptiveSearch );
                }          
            if ( CAknEnv::Static()->TransparencyEnabled() )
                {
                Window().SetRequiredDisplayMode( EColor16MA );
                TInt err = Window().SetTransparencyAlphaChannel();
                if ( err == KErrNone )                    
                    Window().SetBackgroundColor(~0);                    
                }                    
            break;
        case EPopupAdaptiveSearchWindow:
            bitmapId = EMbmAvkonQgn_indi_find_glass;
            bitmapMaskId = EMbmAvkonQgn_indi_find_glass_mask;

            if ( AknLayoutUtils::PenEnabled() )
                {
                flags |= CAknInputFrame::EPopupWindowEmbeddedSoftkeys;
                }

            flags |= CAknInputFrame::EPopupWindowLayout;
            flags |= CAknInputFrame::EFixedFindWithoutLine;
            SetContainerWindowL( aParent ); 
            iColumnFlag = 0xFFFFFFFF;   
            if( AknLayoutUtils::PenEnabled() )
                {
                iAdaptiveSearch = CAknAdaptiveSearch::NewL( aTextLimit, aFieldStyle );       
                iAdaptiveSearch->SetSearchField( this );  
                if ( ASEnabled )
                    {
                    iEditor->AddFlagToUserFlags( CEikEdwin::EAvkonDisableVKB );
                    }
                TInt edwinFlag( iEditor->AknEdwinFlags() );
                iEditor->SetAknEditorFlags( edwinFlag | 
                        EAknEditorFlagAdaptiveSearch );
                }             
            break;
/*     case EInput:
            bitmapId = EMbmAvkonInput;
            bitmapMaskId = EMbmAvkonInputm;
            SetFocus( ETrue );
            break;
        case EUrl:
            bitmapId = EMbmAvkonUrlm;
            bitmapMaskId = EMbmAvkonUrl;
            break;
*/
        default:
            bitmapId = 0;
            bitmapMaskId = 0;
            path = KNullDesC;
            SetContainerWindowL( aParent ); 
            break;
        }
    if ( !aIcon )
        {
        iInputFrame = CAknInputFrame::NewL( iEditor, EFalse, path, bitmapId, bitmapMaskId, 
                                            isShowIndicator ? 
                                            flags | CAknInputFrame::EShowIndicators :
                                            flags );
        }
    else
        {
        iInputFrame = CAknInputFrame::NewL( iEditor, EFalse, NULL, 
                                            flags | CAknInputFrame::EShowIndicators);
        }
    TAknLayoutId layout;
    iAvkonEnv->GetCurrentLayoutId( layout );
    if (layout == EAknLayoutIdAPAC && !AknLayoutUtils::PenEnabled()
        || FeatureManager::FeatureSupported( KFeatureIdChinese ) )
        {
        if ( aFieldStyle != EClockApp )
            {
            iIndicator = AknSearchFieldIndicatorFactory::CreateIndicatorL();
            if ( iIndicator ) // iIndicator is NULL if KFeatureIdAvkonApac is not supported.
                {
                iIndicator->SetContainerWindowL( *this );
                iIndicator->SetSearchFieldStyle( aFieldStyle );                
                if ( !isShowIndicator )
                    {
                    iIndicator->MakeVisible( EFalse );
                    }
                }
            }
        }
    iInputFrame->SetContainerWindowL( *this );
    iEditor->SetContainerWindowL( *this );
    AknEditUtils::ConstructEditingL( iEditor,
                                     aTextLimit,
                                     1,
                                     EAknEditorCharactersLowerCase,
                                     EAknEditorAlignLeft,
                                     EFalse,
                                     ETrue,
                                     EFalse );
    iEditor->SetObserver( this );
    iEditor->SetBorder( TGulBorder::ENone );
    iEditor->SetAknEditorInputMode( EAknEditorTextInputMode );
    iEditor->SetAknEditorAllowedInputModes( EAknEditorTextInputMode |
                                            EAknEditorNumericInputMode ); 

    if ( FeatureManager::FeatureSupported(KFeatureIdJapanese) )
        {
        iEditor->SetAknEditorPermittedCaseModes(EAknEditorCharactersLowerCase);
        }

    TInt editorFlags = iEditor->AknEdwinFlags() |
                       EAknEditorFlagNoT9 | 
                       EAknEditorFlagNoLRNavigation |
                       EAknEditorFlagForceTransparentFepModes |
                       EAknEditorFlagNoEditIndicators |
                       EAknEditorFlagFindPane;
    iEditor->SetAknEditorFlags( editorFlags );
    iEditor->CreateTextViewL();      
    if ( aFieldStyle == EPopup || 
         aFieldStyle == EFixed ||
         aFieldStyle == EPopupAdaptiveSearch || 
         aFieldStyle == EAdaptive )
        {
        iFlags |= EParentAbsolute;
        }

    if( aFieldStyle == ESearchWithoutLine )        
        iFlags |= ETileIIDNone;          
        
    SetupSkinContextL();    
    if ( aIcon )        
        iInputFrame->SetIcon( aIcon ); // May not leave after this    
    if ( aFieldStyle == EPopup || aFieldStyle == EPopupAdaptiveSearch )
        {
        iEditor->SetFocus( EFalse );
        }
    else 
        {      
        iEditor->SetFocus( ETrue );
        }  
    if ( AknsUtils::AvkonSkinEnabled() )        
        iFlags |= EUseSkinContext;    
    iStyle = aFieldStyle;      
    ActivateL();
    }
    
// -----------------------------------------------------------------------------
// CAknSearchField::SetLinePos
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknSearchField::SetLinePos( TInt aLinePos )
    {
    iLinePos = aLinePos;
    TAknsItemID tileIID = KAknsIIDQsnBgColumnA;
    if ( iLinePos == 1 || iLinePos == 0 )
        {
        tileIID = KAknsIIDNone;
        }
    if ( iLinePos == 3 )
        {
        tileIID = KAknsIIDQsnBgColumnAB;
        }
    iSkinContext->SetTiledBitmap( tileIID );
    TAknWindowLineLayout tile = Column_background_and_list_slice_skin_placing_Line_2();
    if ( iLinePos == 1 )
        {
        tile = Column_background_and_list_slice_skin_placing_Line_1();
        }    
    if ( iLinePos == 3 )
        {
        tile = Column_background_and_list_slice_skin_placing_Line_3();
        }
    TRect main_pane;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, main_pane );     
    TRect clientRect( TRect(TPoint(0,0), main_pane.Size() ) );
    TAknLayoutRect tileRect;
    tileRect.LayoutRect( clientRect, tile );  
    iSkinContext->SetTiledRect( tileRect.Rect() );
    }
    
// -----------------------------------------------------------------------------
// CAknSearchField::OfferKeyEventL
// -----------------------------------------------------------------------------
//
EXPORT_C TKeyResponse CAknSearchField::OfferKeyEventL( const TKeyEvent& aKeyEvent,
                                             TEventCode aType )
    {
    if ( aKeyEvent.iCode == EKeyRightArrow )
        {
        if ( iEditor->CursorPos() == iEditor->TextLength() )
            return EKeyWasNotConsumed;
        }
    if ( aKeyEvent.iCode == EKeyLeftArrow )
        {
        if ( iEditor->CursorPos() == 0 )
            return EKeyWasNotConsumed;
        }
    if ( aKeyEvent.iCode == EKeyUpArrow )
        {
        // this is because searchfield should not eat up/down arrows.
        // otherwise this breaks markable lists in phonebook.
        // (obviously edwins have been changed so they eat the key.)
        return EKeyWasNotConsumed;
        }
    if ( aKeyEvent.iCode == EKeyDownArrow )
        {
        return EKeyWasNotConsumed;
        }
    // listbox needs the enter key - it is not acceptable for 
    // searchfield to eat it.
    if ( aKeyEvent.iCode == EKeyEnter || aKeyEvent.iCode == EKeyOK )
        {
        return EKeyWasNotConsumed;
        }   
     if( aKeyEvent.iCode == EKeyNo ) 
        {        
        if ( iAdaptiveSearch )
            {
            iAdaptiveSearch->HideAdaptiveSearchGridL();              
            }
        if ( iIsPopup ) 
            {
            ResetL();       
            TBool needRefresh;
            AknFind::HandleFindPaneVisibility( this, ETrue, EFalse, needRefresh );
            if ( needRefresh && iListBox && iParent )
                {
                AknFind::HandlePopupFindSizeChanged( iParent, iListBox, this );
                CAknFilteredTextListBoxModel* model = static_cast<CAknFilteredTextListBoxModel*> ( iListBox->Model() );                
                if ( model->Filter() )
                    {
                    model->Filter()->ResetFilteringL();
                    }             
                iListBox->DrawNow();
                }    
            }        
        }                   
    TKeyResponse response = iEditor->OfferKeyEventL( aKeyEvent, aType );
    return response;
    }    

// -----------------------------------------------------------------------------
// CAknSearchField::HandlePointerEventL
// -----------------------------------------------------------------------------
//
void CAknSearchField::HandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    if(  AknLayoutUtils::PenEnabled() )
        {  
        if ( iAdaptiveSearch && aPointerEvent.iType == TPointerEvent::EButton1Down )
            {
            if( AdaptiveSearchEnabled() )
                {
                iEditor->AddFlagToUserFlags( CEikEdwin::EAvkonDisableVKB ); 
                MTouchFeedback* feedback = MTouchFeedback::Instance();
                if ( feedback )
                    {
                    feedback->InstantFeedback( ETouchFeedbackBasic );
                    }
                TBool selectall = FeatureManager::FeatureSupported( KFeatureIdChinese )
                    && iEditor->SelectionLength() == iEditor->TextLength();
                iAdaptiveSearch->InvertAdaptiveSearchGridVisibilityL( selectall );          
                }
            else
                {                   
                iEditor->RemoveFlagFromUserFlags( CEikEdwin::EAvkonDisableVKB );
                CAknControl::HandlePointerEventL( aPointerEvent );
                }
            }
        else            
            {
            iEditor->RemoveFlagFromUserFlags( CEikEdwin::EAvkonDisableVKB );           
            CAknControl::HandlePointerEventL( aPointerEvent );
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknSearchField::ShowAdaptiveSearchGrid
// Show adaptive search grid. For the application's menu
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknSearchField::ShowAdaptiveSearchGrid() const   
    {    
    _AKNTRACE_FUNC_ENTER;
    CAknSearchField* searchField = const_cast<CAknSearchField*>( this );
    if( iAdaptiveSearch && searchField->AdaptiveSearchEnabled() )
        {
        TRAP_IGNORE( iAdaptiveSearch->ShowAdaptiveSearchGridL() );              
        }                                   
    _AKNTRACE_FUNC_EXIT;
    }
    
// -----------------------------------------------------------------------------
// CAknSearchField::TextLength
// Returns the length of search text.
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CAknSearchField::TextLength() const   
    {
    return iEditor->TextLength();
    }

// -----------------------------------------------------------------------------
// CAknSearchField::GetSearchText
// Returns the text of search field by writing it into the buffer aSearchText.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknSearchField::GetSearchText( TDes& aSearchTxt ) const
    {
    _AKNTRACE_FUNC_ENTER;
    // caller's responsibility to provide long enough buffer
    iEditor->GetText( aSearchTxt ); 
    
    _AKNDEBUG(
    _LIT( KClassName, "CAknSearchField" );
    _LIT( KFunctionName, "GetSearchText" );
    _LIT( KFormat, "[%S][%S] aSearchTxt: %S" );
    _AKNTRACE( KFormat, &KClassName, &KFunctionName, &aSearchTxt );
    );

    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CAknSearchField::SetSearchTextL 
// Sets text into search field.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknSearchField::SetSearchTextL( const TDesC& aSearchTxt )
    {
    iEditor->SetTextL( &aSearchTxt );
    TInt curPos = iEditor->TextLength(); 
    iEditor->SetSelectionL( curPos, curPos );  //This set selection all off
    }

// -----------------------------------------------------------------------------
// CAknSearchField::SelectSearchTextL
// Selects the whole search text.                          
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknSearchField::SelectSearchTextL()
    {
    iEditor->SelectAllL();
    }

// -----------------------------------------------------------------------------
// CAknSearchField::ResetL
//  Clears text in the search field.                          
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknSearchField::ResetL()
    {
    TBuf<2> str;
    str.Zero();
    iEditor->SetTextL( &str );
    }

// -----------------------------------------------------------------------------
// CAknSearchField::SetInfoTextL
// Sets additional info text to the search field.                         
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknSearchField::SetInfoTextL( const TDesC& aText )
    {
    iInputFrame->SetInfoTextL( aText );
    }

// -----------------------------------------------------------------------------
// CAknSearchField::ClipboardL
// Calls editor's ClipboardL function.                         
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknSearchField::ClipboardL( CEikEdwin::TClipboardFunc aClipboardFunc )
    {
    iEditor->ClipboardL( aClipboardFunc );
    }

EXPORT_C void CAknSearchField::SetSkinEnabledL( const TBool aEnabled )
    {
    if ( aEnabled )
        {
        iFlags |= EUseSkinContext;
        }
    else
        {
        iFlags &= ( ~EUseSkinContext );
        }
    }

// -----------------------------------------------------------------------------
// CAknSearchField::HandleControlEventL                         
// -----------------------------------------------------------------------------
//
void CAknSearchField::HandleControlEventL( CCoeControl* /*aControl*/, TCoeEvent aEventType )
    {
    switch ( aEventType )
        {
        case EEventRequestFocus:
            FocusChanged( EDrawNow );
            break;
        case EEventStateChanged:
            if (Observer())
                {
                Observer()->HandleControlEventL(this, EEventStateChanged);
                }
            break;
        default:
            break;
        }
    }

// -----------------------------------------------------------------------------
// CAknSearchField::ProcessCommandL
// Processes popup find right softkey (Cancel). This closes popup find
// and returns softkey processing to underlying control.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknSearchField::ProcessCommandL( TInt aCommandId )
    {
    if ( aCommandId == EAknSoftkeyCancel )
        {
        ResetL();
        // To provent last text filckering when next time it pop out.
        DrawNow();
        TBool needRefresh;
        AknFind::HandleFindPaneVisibility( this, ETrue, EFalse, needRefresh );
        if ( needRefresh && iListBox && iParent )
            {
            AknFind::HandlePopupFindSizeChanged( iParent, iListBox, this );

            CAknFilteredTextListBoxModel* model = static_cast<CAknFilteredTextListBoxModel*> ( iListBox->Model() );
            
            if ( model->Filter() )
                {
                model->Filter()->ResetFilteringL();
                }

            if ( iOldItemIndex >= 0 &&
                 iOldItemIndex < model->NumberOfItems())
                {
                iListBox->SetCurrentItemIndex( iOldItemIndex );
                }
                
            if( iAdaptiveSearch )
                {
                iAdaptiveSearch->HideAdaptiveSearchGridL();              
                }                  
            iListBox->DrawNow();
            }
        }
    }

TInt CAknSearchField::CountComponentControls() const
    {  
    if ( iIndicator )
        {
        return 3;
        }
    else
       {
       return 2;             
       }    
    }

CCoeControl* CAknSearchField::ComponentControl( TInt aIndex ) const
    {
    CCoeControl* control = NULL;

    if ( aIndex == 0 )
        {
        control = iInputFrame;
        }
    else if ( aIndex == 1 && iIndicator)
        {
        control =  iIndicator;
        }
    else
        {
        control = iEditor;
        }      
    return control;
    }

void CAknSearchField::SizeChanged()
    {
    iInputFrame->SetRect( Rect() );

    if ( iIndicator )
        {
        iIndicator->SetRect( Rect() );
        }   
   
    TRAP_IGNORE( SetupSkinContextL() );
    }

void CAknSearchField::FocusChanged( TDrawNow /*aDrawNow*/ )
    {
    if ( iEditor && IsVisible() )
        {
        iEditor->SetFocus( IsFocused() );
        }       

    if ( iIsPopup && IsFocused() && !iCBAObserverUpdated )
        {
        // non-leaving function, TRAP possible CBA update leaves.
        // if CBA updating leaves, do nothing
        TRAP_IGNORE( UpdatePopupCBAL() );
        }

    if ( iIsPopup && !IsFocused() && iCBAObserverUpdated )
        {
        RestorePopupCBA();
        }
    }

EXPORT_C TSize CAknSearchField::MinimumSize()
    {
    // Returns minimum size. Minimum size depends on zoom factor.
    return TSize( 0, 0 );
    }

EXPORT_C void CAknSearchField::MakeVisible( TBool aVisible )
    {
    _AKNTRACE_FUNC_ENTER;
    
    CCoeControl::MakeVisible( aVisible );
    
    _AKNTRACE( "[%s][%s] aVisible: %d", 
    		"CAknSearchField", __FUNCTION__, aVisible );
        
    if ( iEditor )
        {
        // IsFocused() can not return standand boolean value to compare
        TBool focused = iEditor->IsFocused() ? ETrue : EFalse;
        _AKNTRACE( "[%s][%s] Is Editor Foucused: %d", 
            	"CAknSearchField", __FUNCTION__, focused );
        // "EHMS-7KVGXV"
        if ( focused != aVisible )
            {
            iEditor->SetFocus( aVisible );
            }
        }        
    _AKNTRACE_FUNC_EXIT;
    }

void CAknSearchField::HandleResourceChange( TInt aType )
	{
	if( aType == KAknsMessageSkinChange )
		{
		CAknSearchField* searchField = const_cast<CAknSearchField*>( this );
		if( iAdaptiveSearch && searchField->AdaptiveSearchEnabled() )
			{
			TRAP_IGNORE( iAdaptiveSearch->UpdateGridSkinL() );
			}
		}
	CAknControl::HandleResourceChange( aType );
	}

TTypeUid::Ptr CAknSearchField::MopSupplyObject( TTypeUid aId )
    {
    if( aId.iUid == MAknsControlContext::ETypeId && iFlags & EUseSkinContext )
        {
        return MAknsControlContext::SupplyMopObject( aId, iSkinContext );
        }
    return SupplyMopObject( aId, (MAknEditingStateIndicator*)iIndicator );
    }


void CAknSearchField::UpdatePopupCBAL()
    {
    // Change right CBA for popup find
    CEikButtonGroupContainer* cba = CEikButtonGroupContainer::Current();
    if ( cba == NULL ) return; //no CBAs - do nothing

    HBufC* label = StringLoader::LoadL( R_AVKON_SOFTKEY_CANCEL, iCoeEnv );
    CleanupStack::PushL( label );
    cba->AddCommandToStackL( 2, EAknSoftkeyCancel, label->Des() );
    CleanupStack::PopAndDestroy(); // label
    cba->DrawNow();      
    
    if( !cba->UpdatedCommandObserverExists(CEikButtonGroupContainer::ERightSoftkeyPosition) )
        {
        TRAPD( error, cba->UpdateCommandObserverL(2, *this) );
        
         if ( error == KErrNone )
            {
            iCBAObserverUpdated = ETrue;
            }   
        }           
    iCba = cba;
    }

void CAknSearchField::RestorePopupCBA()
    {
    // Restore right CBA to what it was
    CEikButtonGroupContainer* cba = CEikButtonGroupContainer::Current();
    
    // if view switch happened, Current() might return different cba;
    // no use for modifying it.
    if ( iCba != cba ) return;
    
    if ( cba )
        {
        cba->RemoveCommandObserver( 2 );
        cba->RemoveCommandFromStack( 2, EAknSoftkeyCancel );
        cba->DrawNow();
        }
    iCBAObserverUpdated = EFalse;
    iCba = NULL;
    }

void CAknSearchField::SetListbox( CEikListBox *aListBox )
    {
    if( iListBox != aListBox )
        {
        iListBox = aListBox;
        if( iParent )
            {
            if ( iIsPopup )
                {
                AknFind::HandlePopupFindSizeChanged( iParent, iListBox, this );
                }
            else
                {
                AknFind::HandleFixedFindSizeChanged( iParent, (CAknColumnListBox*)iListBox, this );
                }
            }
        }         
    }

void CAknSearchField::SetParentCtrl( CCoeControl *aParent )
    {
    iParent = aParent;
    }

TBool CAknSearchField::IsPopup()
    {
    return iIsPopup;
    }

// -----------------------------------------------------------------------------
// CAknSearchField::Editor
// Access to the edwin owned by the search field.
// -----------------------------------------------------------------------------
//
EXPORT_C CEikEdwin& CAknSearchField::Editor() const
    {
    return *iEditor;
    }

// -----------------------------------------------------------------------------
// CAknSearchField::SetupSkinContextL
// -----------------------------------------------------------------------------
//
void CAknSearchField::SetupSkinContextL()
    {
    TAknsItemID tileIID = KAknsIIDQsnBgColumnA;
    if (iLinePos == 1 || iLinePos == 0)
        {
        tileIID = KAknsIIDNone;
        }
    if (iLinePos == 3)
        {
        tileIID = KAknsIIDQsnBgColumnAB;
        }    
    if( iFlags & ETileIIDNone )
        {
        tileIID = KAknsIIDNone;
        }    
    TAknWindowLineLayout tile =
        Column_background_and_list_slice_skin_placing_Line_2();    
    if (iLinePos==1)
        {
        tile = Column_background_and_list_slice_skin_placing_Line_1();
        }    
    if (iLinePos==3)
        {
        tile = Column_background_and_list_slice_skin_placing_Line_3();
        }    
    TRect screen;  // was mainpane
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screen );    
    TAknLayoutRect tileRect;
    tileRect.LayoutRect(screen, tile);  
    TBool parentAbsolute = iFlags & EParentAbsolute;
    if ( !iSkinContext )
        {
        iSkinContext = CAknsListBoxBackgroundControlContext::NewL(
            KAknsIIDQsnBgAreaMainListGene, 
            screen,
            parentAbsolute,
            tileIID,
            tileRect.Rect() );
        }
    else
        {
        iSkinContext->SetRect( screen );
        }
    if ( !iInputContext )
        {
        iInputContext = CAknsFrameBackgroundControlContext::NewL(
            KAknsIIDQsnFrInput, TRect(0,0,0,0), TRect(0,0,0,0), EFalse );
        }
    iInputFrame->SetInputContext( iInputContext );
    iEditor->SetSkinBackgroundControlContextL( iInputContext );
    if ( parentAbsolute )
        {
        iSkinContext->SetParentPos( iAvkonAppUi->ClientRect().iTl );
        }
    }

void CAknSearchField::HandleHWKeyboardModeChangeL()
    {
    _AKNTRACE_FUNC_ENTER;
    TInt isHwKbOpen = 0;
    iHwKeyboardPro.Get( isHwKbOpen );    
    if ( isHwKbOpen != 0 ) // QWERTY open
        {
        if ( iIndicator )
            {
            iIndicator->SetRect( Rect() );
            iIndicator->MakeVisible( ETrue );
            }
        iInputFrame->SetFlags( iInputFrame->Flags() 
                               | CAknInputFrame::EShowIndicators );
        iInputFrame->SetRect( Rect() );
        
        if ( iAdaptiveSearch )
            {
            iAdaptiveSearch->HideAdaptiveSearchGridL();
            }
        else
            {
            // Enforce focus to edwin to get cursor and indicator,
            // Hidden find pane should ignore this.
            if ( !IsFocused() && IsVisible() )
				{
				SetFocus( ETrue );
				}
            }
        
        }
    else
        {
        iIndicator->MakeVisible(EFalse);
        iInputFrame->SetFlags( iInputFrame->Flags() 
                               & ~CAknInputFrame::EShowIndicators );
        iInputFrame->SetRect( Rect() );
        }
    // we need CAknInputFrame::SizeChanged to redo layout
    iInputFrame->SetRect( Rect() );

    iEditor->SelectAllL();
    DrawNow();
    _AKNTRACE_FUNC_EXIT;
    }

TBool CAknSearchField::GetASStatusAndSubKbLayoutL( TBool& aShowIndicator )
    {
    _AKNTRACE_FUNC_ENTER;
    CRepository* cenrep = NULL;
    TRAPD( ret, cenrep = CRepository::NewL( KCRUidAvkon ) );
    CleanupStack::PushL( cenrep );
    TBool isAsEnable = EFalse;
    if ( ret == KErrNone )
        {        
        ret = cenrep->Get( KAknAvkonAdaptiveSearchEnabled, isAsEnable );
        if ( FeatureManager::FeatureSupported( KFeatureIdChinese ))
            {
            ret = iHwKeyboardPro.Attach( KCRUidAvkon, 
                    KAknKeyBoardLayout );
            if ( ret == KErrNone )
                {
                iHwKbSub = new(ELeave) CHwKbSubscriber( this, iHwKeyboardPro);
                TInt kb = 0;
                if ( iHwKeyboardPro.Get(kb) == KErrNone )
                    {
                    _AKNTRACE( "[%s][%s] Keyboard Layout: %d", 
                            "CAknSearchField", __FUNCTION__, kb );
                    // show indicator when handware is open
                    aShowIndicator = kb != 0;
                    _AKNTRACE( "[%s][%s] Show Indicator: %d", 
                                "CAknSearchField", __FUNCTION__, aShowIndicator );
                    }
                iHwKbSub->SubscribeL();
                }
            }
        }                
    CleanupStack::PopAndDestroy( cenrep );    
    _AKNTRACE_FUNC_EXIT;
    return isAsEnable;
    }

void CAknSearchField::SetOldItemIndex( TInt aOldItemIndex )
    {
    iOldItemIndex = aOldItemIndex;
    }

TInt CAknSearchField::OldItemIndex()
    {
    return iOldItemIndex;
    }
 
// -----------------------------------------------------------------------------
// CAknSearchField::SetAdaptiveGridChars
// Set adaptive search grid characters.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknSearchField::SetAdaptiveGridChars( const TDesC& aGridChars ) const
    {
    _AKNTRACE_FUNC_ENTER;
    if( iAdaptiveSearch )
        {
        _AKNDEBUG(
        _LIT( KClassName, "CAknSearchField" );
        _LIT( KFunctionName, "SetAdaptiveGridChars" );
        _LIT( KFormat, "[%S][%S] aGridChars: %S" );
        _AKNTRACE( KFormat, &KClassName, &KFunctionName, &aGridChars );
        );
        TRAP_IGNORE( iAdaptiveSearch->SetButtonCharsL( aGridChars ) );
        }
    _AKNTRACE_FUNC_EXIT;
    }   

// -----------------------------------------------------------------------------
// CAknSearchField::SetListColumnFilterFlags
// Set flag of columns for adaptive search grid.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknSearchField::SetListColumnFilterFlags( const TBitFlags32 aFlag )
    {
    iColumnFlag = aFlag;
    }

EXPORT_C TBitFlags32 CAknSearchField::ListColumnFilterFlags() const 
    {
    return iColumnFlag;
    }
    
EXPORT_C CAknSearchField::TSearchFieldStyle CAknSearchField::SearchFieldStyle() const
    {
    return iStyle;
    }
    
// -----------------------------------------------------------------------------
// CAknSearchField::AddAdaptiveSearchTextObserverL
// Adds an adaptive search text observer. Duplicates are not checked 
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknSearchField::AddAdaptiveSearchTextObserverL( 
                                        MAdaptiveSearchTextObserver* aObserver )
    {
    if( iAdaptiveSearch )
        {
        iAdaptiveSearch->AddAdaptiveSearchTextObserverL( aObserver );
        }
    }

// ----------------------------------------------------------------------------- 
// CAknSearchField::RemoveAdaptiveSearchTextObserver
// Removes an adaptive search text observer. 
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CAknSearchField::RemoveAdaptiveSearchTextObserver( 
                                        MAdaptiveSearchTextObserver* aObserver )
    {
    if( iAdaptiveSearch )
        {
        return iAdaptiveSearch->RemoveAdaptiveSearchTextObserver( aObserver );
        }
    return EFalse;
    }
    
// -----------------------------------------------------------------------------
// CAknSearchField::AdaptiveSearchEnabled
// Check adaptive search availability from cenrep
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CAknSearchField::AdaptiveSearchEnabled()
    {
    if ( !iAdaptiveSearch )
        {
        return EFalse;
        }       
    CRepository* repository = NULL;
    TBool ASEnabled;
    TRAPD( ret, repository = CRepository::NewL( KCRUidAvkon ) );
    if ( ret == KErrNone )
        {
        ret = repository->Get( KAknAvkonAdaptiveSearchEnabled, ASEnabled );
        }
    delete repository;    
    TInt isHwKbOpen = 0;
    if ( iHwKbSub )
        {
        iHwKeyboardPro.Get( isHwKbOpen );
        }
    return ASEnabled && isHwKbOpen == 0;
    }   
// -----------------------------------------------------------------------------
// CAknSearchField::SetLanguageChangedFlag
// Set language changed flag for AS 
// -----------------------------------------------------------------------------
//
void CAknSearchField::SetLanguageChangedFlag( TBool aLanguageChanged )
    {   
    iLanguageChanged = aLanguageChanged;
    }
    
// -----------------------------------------------------------------------------
// CAknSearchField::LanguageChanged
// Notify client that input language was changed in settings for AS 
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CAknSearchField::LanguageChanged() const
    {   
    return iLanguageChanged;
    }
    
// End of File
