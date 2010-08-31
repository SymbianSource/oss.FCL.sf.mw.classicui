/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
#include "AknAdaptiveSearchGrid.h"
#include <AknsDrawUtils.h>
#include <layoutmetadata.cdl.h>
#include <aknlayoutscalable_apps.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>

#include <AknsListBoxBackgroundControlContext.h>
#include <AknsBasicBackgroundControlContext.h>
#include <AknsFrameBackgroundControlContext.h>
#include <numberconversion.h>  // For page indicator

#include <eikedwin.h>
#include <akninfrm.h>       // CAknInputFrame 
#include <avkon.mbg>        // Bitmaps for "dummy" find pane
#include <aknconsts.h>      // KAvkonBitmapFile
#include <featmgr.h>        // FeatureManager
#include <aknViewAppUi.h>   // CAknViewAppUi
#include <akntoolbar.h> 

#include "aknSfldIndicatorFactory.h"
#include "aknsfldIndicator.h"
#include <aknEditStateIndicator.h>
#include <eikbtgpc.h> 
#include <aknsfld.h> //for TSearchFieldStyle

#include <touchfeedback.h>

#include "akntrace.h"
// CONSTANTS
const TInt KPortraitMaxSize = 0;
const TInt KLandscapeMaxSize = 1;

const TInt KPortraitMultiPage = 0;
const TInt KLandscapeMultiPage = 1;
const TInt KPortraitSinglePage = 2;
const TInt KLandscapeSinglePage = 3;

const TInt KPortraitToolbarMaxSize = 18;


_LIT( KSlashOfPageIndicator, "/" );
_LIT( KSpaceCharacter, " " );
const TInt KCloseAndClearButtonCount = 2;  

   
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CAknAdaptiveSearchGrid* 
CAknAdaptiveSearchGrid::NewL( const TInt aTextLimit, TInt aFieldStyle )
    {
    CAknAdaptiveSearchGrid* self = CAknAdaptiveSearchGrid::NewLC( aTextLimit, 
                                                                  aFieldStyle );
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CAknAdaptiveSearchGrid* 
CAknAdaptiveSearchGrid::NewLC( const TInt aTextLimit, TInt aFieldStyle )
    {
    CAknAdaptiveSearchGrid* self = new ( ELeave ) CAknAdaptiveSearchGrid ( aTextLimit );
    CleanupStack::PushL( self );
    self->ConstructL( aFieldStyle );
    return self;
    }

// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::CAknAdaptiveSearchGrid()
// C++ default constructor.
// -----------------------------------------------------------------------------
//
CAknAdaptiveSearchGrid::CAknAdaptiveSearchGrid( const TInt aTextLimit )
    : iCloseButton( NULL ),     
      iDeleteButton( NULL ),
      iPrevButton( NULL ),
      iNextButton( NULL ),
      iLastFocusedButton( NULL ),
      iTextLimit( aTextLimit ),
      iShown( EFalse ),
      iNumOfPages( 1 ),
      iGridChars( NULL ),
      iAppUi( iAvkonAppUi ),     
      iAdaptiveSearchGridObserver( NULL ),
      iLayoutChanged(EFalse),
      iPopupFindpane(EFalse)
    {      
    __ASSERT_DEBUG( iAppUi, User::Invariant() );
    SetMopParent( iAppUi );
    }

// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::~CAknAdaptiveSearchGrid()
// Destructor.
// -----------------------------------------------------------------------------
//
CAknAdaptiveSearchGrid::~CAknAdaptiveSearchGrid()
    { 
    _AKNTRACE_FUNC_ENTER;
    CEikonEnv::Static()->EikAppUi()->RemoveFromStack( this );
    delete iBgContextOfFindPane;
    delete iBgContextOfControlPane;
    delete iSkinContextOfFindPane; 
    delete iInputFrame;
 
    // Clear current region of AS
    iCurrentRegion.Clear();    
    iButtonArray.ResetAndDestroy();
    
    if ( iEditor )
        {
        TRAP_IGNORE(iEditor->TextView()->SetCursorVisibilityL( 
            TCursor::EFCursorInvisible, TCursor::EFCursorInvisible ));
        delete iEditor;
        }   
    if( iGridChars )
        {
        delete iGridChars;
        iGridChars = NULL;
        }               
    if( iCloseButton )
        {
        delete iCloseButton;
        iCloseButton = NULL;
        }
    if( iDeleteButton )
        {
        delete iDeleteButton;
        iDeleteButton = NULL;
        }
    if( iPrevButton )
        {
        delete iPrevButton;
        iPrevButton = NULL;
        }
    if( iNextButton )
        {
        delete iNextButton;
        iNextButton = NULL;
        }
    if( iPageIndicator )
        {
        delete iPageIndicator;
        iPageIndicator = NULL;
        }
       
    CAknWsEventMonitor* eventMonitor = iAppUi->EventMonitor();    
    eventMonitor->Enable( EFalse ); 
    eventMonitor->RemoveObserver( this ); 
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::ConstructL()
// Symbian 2nd phase constructor.
// -----------------------------------------------------------------------------
//
void CAknAdaptiveSearchGrid::ConstructL( TInt aFieldStyle )
    {   
    _AKNTRACE_FUNC_ENTER;
    
    _AKNTRACE( "[%s][%s] Search Field Style : %d", "CAknAdaptiveSearchGrid", __FUNCTION__, aFieldStyle );
    CreateWindowL();
    
    if( CAknEnv::Static()->TransparencyEnabled() )
        {
        Window().SetRequiredDisplayMode( EColor16MA );
        TInt err = Window().SetTransparencyAlphaChannel();
        if ( err == KErrNone )
            {
            Window().SetBackgroundColor(~0);
            }
        }        

    CAknWsEventMonitor* eventMonitor = iAppUi->EventMonitor();    
    eventMonitor->AddObserverL( this );
    eventMonitor->Enable();
    
    iSkinContextOfFindPane = CAknsListBoxBackgroundControlContext::NewL( KAknsIIDQsnBgAreaControlPopup, 
                                                                         TRect(0,0,0,0), 
                                                                         EFalse, 
                                                                         KAknsIIDNone, 
                                                                         TRect(0,0,0,0) );   
    iBgContextOfFindPane = CAknsFrameBackgroundControlContext::NewL( KAknsIIDQsnFrInput, 
                                                                     TRect(0,0,0,0), 
                                                                     TRect(0,0,0,0), 
                                                                     EFalse );    
    iBgContextOfControlPane = CAknsBasicBackgroundControlContext::NewL( KAknsIIDQgnGrafAdaptSearchPageBg, 
                                                                        TRect(0,0,0,0), EFalse );          
    // Init components
    InitControlsL( aFieldStyle );
    InitGrid();   
    _AKNTRACE_FUNC_EXIT;
    }   
 
// ---------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::InitControls()
// Initiates find pane and page indicator. 
// Create control buttons: close, delete, next page, prev page 
// ---------------------------------------------------------------------------
//
void CAknAdaptiveSearchGrid::InitControlsL( TInt aFieldStyle )
    {    
    CGulIcon* gulIcon = NULL;
     
    gulIcon = GetColorIconL( 0 );   
    iCloseButton = CAknButton::NewL( gulIcon, NULL, NULL, NULL, KNullDesC, 
                                     KNullDesC, 0, 0 );   
    iCloseButton->SetBackgroundIds( KAknsIIDQsnFrFunctionButtonNormal,
            KAknsIIDQsnFrFunctionButtonPressed, KAknsIIDQsnFrFunctionButtonInactive,
            KAknsIIDQsnFrFunctionButtonPressed, KAknsIIDQsnFrFunctionButtonInactive );   
    iCloseButton->SetObserver( this );
    iCloseButton->SetContainerWindowL( *this );  
    
    gulIcon = GetColorIconL( 1 );   
    iDeleteButton = CAknButton::NewL( gulIcon, NULL, NULL, NULL, KNullDesC, 
                                      KNullDesC, KAknButtonKeyRepeat, 0 ); 
    iDeleteButton->SetBackgroundIds( KAknsIIDQsnFrFunctionButtonNormal,
            KAknsIIDQsnFrFunctionButtonPressed, KAknsIIDQsnFrFunctionButtonInactive,
            KAknsIIDQsnFrFunctionButtonPressed, KAknsIIDQsnFrFunctionButtonInactive );        
    iDeleteButton->SetObserver( this );
    iDeleteButton->SetContainerWindowL( *this );
    
    gulIcon = GetColorIconL( 2 );   
    iPrevButton = CAknButton::NewL( gulIcon, NULL, NULL, NULL, KNullDesC, 
                                    KNullDesC, KAknButtonKeyRepeat, 0 ); 
    iPrevButton->SetBackgroundIds( KAknsIIDQsnFrFunctionButtonNormal,
            KAknsIIDQsnFrFunctionButtonPressed, KAknsIIDQsnFrFunctionButtonInactive,
            KAknsIIDQsnFrFunctionButtonPressed, KAknsIIDQsnFrFunctionButtonInactive );   
    iPrevButton->SetObserver( this );
    iPrevButton->SetContainerWindowL( *this );    
    
    gulIcon = GetColorIconL( 3 );
    iNextButton = CAknButton::NewL( gulIcon, NULL, NULL, NULL, KNullDesC, 
                                    KNullDesC, KAknButtonKeyRepeat, 0 );     
    iNextButton->SetBackgroundIds( KAknsIIDQsnFrFunctionButtonNormal,
            KAknsIIDQsnFrFunctionButtonPressed, KAknsIIDQsnFrFunctionButtonInactive,
            KAknsIIDQsnFrFunctionButtonPressed, KAknsIIDQsnFrFunctionButtonInactive );                                   
    iNextButton->SetObserver( this ); 
    iNextButton->SetContainerWindowL( *this );

    TUint flags = 0;
    switch ( aFieldStyle )
        {
        case CAknSearchField::EPopupAdaptiveSearch:
            flags |= CAknInputFrame::EPopupLayout;
            iPopupFindpane = ETrue;
            break;
        case CAknSearchField::EPopupAdaptiveSearchWindow:
            flags |= CAknInputFrame::EPopupWindowLayout;
            flags |= CAknInputFrame::EFixedFindWithoutLine;
            break;
        }
    iEditor = new (ELeave) CEikEdwin;   
    
    iInputFrame = CAknInputFrame::NewL( iEditor, 
                                        EFalse, 
                                        KAvkonBitmapFile, 
                                        EMbmAvkonQgn_indi_find_glass, 
                                        EMbmAvkonQgn_indi_find_glass_mask, 
                                        flags );                     

    iEditor->SetContainerWindowL( *this );
    iInputFrame->SetContainerWindowL( *this );
    
    AknEditUtils::ConstructEditingL( iEditor,
                                     iTextLimit,
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
    iEditor->AddFlagToUserFlags( CEikEdwin::EAvkonDisableVKB );
    
    if ( FeatureManager::FeatureSupported( KFeatureIdJapanese ) )
        {
        iEditor->SetAknEditorPermittedCaseModes( EAknEditorCharactersLowerCase );
        }

    TInt editorFlags = EAknEditorFlagNoT9 | 
                       EAknEditorFlagNoLRNavigation |
                       EAknEditorFlagForceTransparentFepModes |
                       EAknEditorFlagNoEditIndicators |
                       EAknEditorFlagFindPane;

    iEditor->SetAknEditorFlags( editorFlags );
    iEditor->CreateTextViewL(); 

    iInputFrame->SetInputContext( iBgContextOfFindPane );
    iEditor->SetSkinBackgroundControlContextL( iBgContextOfFindPane );
  
    TRgb textColor = KRgbBlack;
    TInt error = AknsUtils::GetCachedColor( AknsUtils::SkinInstance(), 
                                            textColor, 
                                            KAknsIIDQsnTextColors, 
                                            EAknsCIQsnTextColorsCG19);
    if( !error )
        {
        TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL(*iEditor, EColorLabelText, textColor) );       
        }   
    
    // Create label for page indicator
    iPageIndicator = new (ELeave) CEikLabel;
    iPageIndicator->SetObserver( this );
    iPageIndicator->SetContainerWindowL( *this );
    iPageIndicator->SetTextL( KNullDesC );    
    }     
 
 CGulIcon* CAknAdaptiveSearchGrid::GetColorIconL( TInt aIndex )
    {    
    // order: Close, Backspace, Previous, Next    
     _AKNTRACE( "[%s][%s] color icon index : %d", "CAknAdaptiveSearchGrid", __FUNCTION__, aIndex );
    TAknsItemID skinIdArray[] = 
        {
        KAknsIIDQgnIndiSctClose,
        KAknsIIDQgnIndiAdaptSearchBackspace,
        KAknsIIDQgnIndiSctPagePrev,
        KAknsIIDQgnIndiSctPageNext,
        KAknsIIDQgnIndiKeypadSpace
        };
    TInt bitmapIds [] =
        {
        EMbmAvkonQgn_indi_sct_close,
        EMbmAvkonQgn_indi_adapt_search_backspace,
        EMbmAvkonQgn_indi_sct_page_prev,
        EMbmAvkonQgn_indi_sct_page_next,
        EMbmAvkonQgn_indi_keypad_space
        };
    TInt maskIds [] =
        {
        EMbmAvkonQgn_indi_sct_close_mask,
        EMbmAvkonQgn_indi_adapt_search_backspace_mask,
        EMbmAvkonQgn_indi_sct_page_prev_mask,
        EMbmAvkonQgn_indi_sct_page_next_mask,
        EMbmAvkonQgn_indi_keypad_space_mask
        };
        
    CFbsBitmap *icon = NULL;
    CFbsBitmap *mask = NULL;    
    
    TAknsItemID colorGroup = KAknsIIDQsnIconColors;
    TInt textColorIndex = EAknsCIQsnIconColorsCG30;    
    // space belong to another color group
    if( aIndex == 4 )
        {        
        colorGroup = KAknsIIDQsnTextColors; 
        textColorIndex = EAknsCIQsnTextColorsCG65;        
        }
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();    
    if( aIndex == 0 )
        {        
        AknsUtils::CreateIconL( skin, skinIdArray[aIndex],                                           
                                icon, mask, KAvkonBitmapFile, 
                                bitmapIds[aIndex], maskIds[aIndex] );    
        }
    else
        {        
        AknsUtils::CreateColorIconL( skin, skinIdArray[aIndex],
                                           colorGroup,
                                           textColorIndex,
                                           icon, mask, 
                                           KAvkonBitmapFile, 
                                           bitmapIds[aIndex],
                                           maskIds[aIndex],
                                           KRgbBlack );    
        } 

    CGulIcon* gulIcon = CGulIcon::NewL( icon, mask );    
    return gulIcon;
    }

// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::UpdateLayoutVariant()
// Update layout variant. This should be done when 
// KEikDynamicLayoutVariantSwitch message recieved. 
// -----------------------------------------------------------------------------
// 
void CAknAdaptiveSearchGrid::UpdateLayoutVariant()
    {
    _AKNTRACE_FUNC_ENTER;
    InitGrid(); 
    UpdatePageAndRowCount();                 
    if( IsShown() )
        {
        ControlsPositions();
        TRAP_IGNORE( UpdateVisibleButtonsL() );  
        ShowControls();           
        }
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::UpdateSkinL()
// Update adaptive search grid skin. This should be done when 
// KAknsMessageSkinChange message recieved. 
// -----------------------------------------------------------------------------
//  
void CAknAdaptiveSearchGrid::UpdateSkinL()
    {
    CGulIcon* gulIcon = NULL;
    gulIcon = GetColorIconL( 0 );        
    iCloseButton->State()->SetIcon( gulIcon );
    CGulIcon* gulIcon1 = NULL;
    gulIcon1 = GetColorIconL( 1 );        
    iDeleteButton->State()->SetIcon( gulIcon1 );
    CGulIcon* gulIcon2 = NULL;
    gulIcon2 = GetColorIconL( 2 );        
    iPrevButton->State()->SetIcon( gulIcon2 );      
    CGulIcon* gulIcon3 = NULL;
    gulIcon3 = GetColorIconL( 3 );        
    iNextButton->State()->SetIcon( gulIcon3 );
    
    UpdateVisibleButtonsL();                        
        
    if( iNumOfPages > 1 )
        {   
        // Page pane & page indicator   
        TRect page_pane = RectFromLayout( Rect(), AknLayoutScalable_Apps::afind_page_pane( iLayoutOption) );    
        if( AknsUtils::AvkonSkinEnabled() )
            {           
            TRgb textColor = KRgbBlack; 
            TInt error = AknsUtils::GetCachedColor( AknsUtils::SkinInstance(), 
                                                    textColor, 
                                                    KAknsIIDQsnTextColors, 
                                                    EAknsCIQsnTextColorsCG19);
            if( !error )                    
                AknLayoutUtils::OverrideControlColorL(*iPageIndicator, EColorLabelText, textColor);                                        
            }               
        iBgContextOfControlPane->SetRect( page_pane );     
        }
    }
// CAknAdaptiveSearchGrid::InitGridButtons()
// Initiates buttons array of the adaptive search grid.
// iTotalGridButtons should be calculated in advance by caling InitGrid() 
// -----------------------------------------------------------------------------
//
void CAknAdaptiveSearchGrid::InitGridButtons()
    { 
    iButtonArray.ResetAndDestroy();         
    //EKKG-7LZB4U. When SizeChanged() is invoked, maybe iLastFocusedButton keeps invaild point. 
    iLastFocusedButton = NULL;      
    for ( TInt i = 0; i < iTotalGridButtons; i++ )
        {
        TRAP_IGNORE( iButtonArray.Append( CreateButtonL() ) );
        }
    }   
    
// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::CreateButtonL
// Create a button from Text or Resource. 
// Set to button observer and container window
// -----------------------------------------------------------------------------
//
CAknButton* CAknAdaptiveSearchGrid::CreateButtonL()
    {   
    CAknButton* button = CAknButton::NewL( NULL, NULL, NULL, NULL,
        KNullDesC, KNullDesC , KAknButtonSizeFitText, 0 );        
        
    if ( button )
        {       
        button->SetObserver( this );        
        button->SetContainerWindowL( *this ); 
        button->SetBackground(this);
        button->SetTextColorIds( KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG65 );
        button->ActivateL();
        return button;
        }
    else
        {
        CleanupStack::PopAndDestroy( button );
        User::LeaveNoMemory(); 
        return NULL;
        }  
    }
  
// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::RectFromLayout
// -----------------------------------------------------------------------------
//
TRect CAknAdaptiveSearchGrid::RectFromLayout( const TRect& aParent,
        const TAknWindowComponentLayout& aComponentLayout ) const
    {
    TAknWindowLineLayout lineLayout = aComponentLayout.LayoutLine();
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( aParent, lineLayout );
    return layoutRect.Rect();
    }
             
// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::InitGrid
// Calculate max grid size and total amount of buttons for initialisation
// -----------------------------------------------------------------------------
//
void CAknAdaptiveSearchGrid::InitGrid()
    {  
    TInt layout_option;
           
    if( Layout_Meta_Data::IsLandscapeOrientation() )
        {
        CAknToolbar* toolbar = iAppUi->CurrentFixedToolbar();
        iLayoutOption = KLandscapeSinglePage; 
        layout_option = KLandscapeMaxSize;
        if ( toolbar && toolbar->IsShown() )
             iToolbarShown = ETrue;
        else
            iToolbarShown = EFalse;
        }
    else
        {        
        CAknToolbar* toolbar = iAppUi->CurrentFixedToolbar();
        iLayoutOption = KPortraitSinglePage;
                 
        if ( toolbar && toolbar->IsShown() )
            {
            iToolbarShown = ETrue;              
            layout_option = KPortraitToolbarMaxSize;
            }    
        else
            {
            iToolbarShown = EFalse;            
            layout_option = KPortraitMaxSize;
            }
        }
    
    TRect appWindow;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EApplicationWindow, appWindow );
    TRect currentWindowRect = RectFromLayout( appWindow, AknLayoutScalable_Apps::popup_adpt_find_window(layout_option) );     
    
    // TODO: Remove this once the layout is fixed so that the adaptive search
    // grid doesn't go over the control pane area in BSK landscape layout.
    if ( Layout_Meta_Data::IsLandscapeOrientation() )
        {
        TRect controlPaneRect;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EControlPane,
                                           controlPaneRect );
        currentWindowRect.iBr.iY = controlPaneRect.iTl.iY;
        
        TRect mainPaneRect;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane,
                                           mainPaneRect );
        CAknToolbar* toolbar = iAppUi->CurrentFixedToolbar();   
        if ( !toolbar 
             || !toolbar->IsVisible()
             || mainPaneRect.iBr.iX <= toolbar->Position().iX 
           )
            {          
            currentWindowRect.iBr.iX = mainPaneRect.iBr.iX;
            }
        }
        
    TRect grid_pane = RectFromLayout( currentWindowRect, AknLayoutScalable_Apps::grid_afind_pane( iLayoutOption ) );
    TRect button_rect = RectFromLayout( grid_pane, AknLayoutScalable_Apps::cell_afind_pane( iLayoutOption, 0, 0 ) );  
    TSize button_rect_size = button_rect.Size();
    TSize grid_pane_size = grid_pane.Size();    
    
    iNumOfCols = grid_pane_size.iWidth/button_rect_size.iWidth;
    iNumOfRows = grid_pane_size.iHeight/button_rect_size.iHeight;   
    iTotalGridButtons = iNumOfCols*iNumOfRows;

    //For ELJG-7VC8Q2, calculate the length of overlap section
    TRect popup_find_pane = RectFromLayout( Rect(), AknLayoutScalable_Avkon::popup_find_window() );
    TRect find_pane = RectFromLayout( Rect(), AknLayoutScalable_Apps::find_pane_cp01( iLayoutOption ) );
    iOverlapLength = (find_pane.iTl.iY - popup_find_pane.iTl.iY)/iNumOfRows + 1;

    
    // max amount of char buttons on the one page
    iMaxAmountOfButtons = iTotalGridButtons - KCloseAndClearButtonCount;
    
    SetRect( currentWindowRect );
    }

// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::Draw
// From MCoeControlBackground
// Draw the background for a given control.
// The text drawer that shall be used to draw text on the specific background 
// can be fetched through the GetTextDrawer() method. 
// -----------------------------------------------------------------------------
//    
void CAknAdaptiveSearchGrid::Draw( CWindowGc& aGc, const CCoeControl& /*aControl*/, 
         const TRect& aRect ) const 
    {
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this ); 
    aGc.SetBrushColor( KRgbWhite );
    aGc.SetPenColor( KRgbBlack );
    aGc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    aGc.DrawRect( aRect );   
    }

// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::Draw()
// Draws the display.
// -----------------------------------------------------------------------------
//

void CAknAdaptiveSearchGrid::Draw( const TRect& /*aRect*/ ) const
    {  
    if( iNumOfPages > 1 )
        {
        // Page pane    
        TRect page_pane;
        CWindowGc& gc = SystemGc();             
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();                
        page_pane = RectFromLayout( Rect(), AknLayoutScalable_Apps::afind_page_pane(iLayoutOption) );
        
        AknsDrawUtils::Background( skin, iBgContextOfControlPane, gc, page_pane );
        }
    }

// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::SizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CAknAdaptiveSearchGrid::SizeChanged()
    {         
    InitGridButtons();       
    GridButtonsPositions();      
    }

// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::MopSupplyObject
// Retrieves an object of the same type as that encapsulated in aId.
// -----------------------------------------------------------------------------
//    
TTypeUid::Ptr CAknAdaptiveSearchGrid::MopSupplyObject( TTypeUid aId )
    {
    if ( aId.iUid == MAknsControlContext::ETypeId && iSkinContextOfFindPane )
        {
        return MAknsControlContext::SupplyMopObject( aId, iSkinContextOfFindPane );
        }
    return MAknsControlContext::SupplyMopObject( aId, NULL );
    }

// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::CountComponentControls
// Gets the number of controls contained in a compound control.
// -----------------------------------------------------------------------------
//   
TInt CAknAdaptiveSearchGrid::CountComponentControls() const
    {
    // buttons + controls + search field ( editor, input frame )    
    return iButtonArray.Count()+5+2; 
    } 

// -----------------------------------------------------------------------------
// Sets text into search field.
// Gets one parameters:
// const TDesC& aSearchTxt      - Reference to the text buffer.
// -----------------------------------------------------------------------------      
//                   
void CAknAdaptiveSearchGrid::SetSearchTextToFindPane( const TDesC& aSearchTxt )
    { 
    _AKNDEBUG(
               _LIT( KClassName, "CAknAdaptiveSearchGrid" );
               _LIT( KFunctionName, "SetSearchTextToFindPane" );
               _LIT( KFormat, "[%S][%S] search text is: %S");
               _AKNTRACE( KFormat, 
               &KClassName, &KFunctionName, &aSearchTxt );
               );

    TRAP_IGNORE( iEditor->SetTextL( &aSearchTxt ) );
    if ( iShown )
        {
        TRAP_IGNORE(iEditor->TextView()->SetCursorVisibilityL( TCursor::EFCursorFlashing,
                                                           TCursor::EFCursorFlashing ));
        }
    TInt curPos = iEditor->TextLength(); 
    //This set selection all off
    TRAP_IGNORE( iEditor->SetSelectionL( curPos, curPos ) ); 
    iEditor->DrawNow();
    } 
    
// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::ComponentControlh
// Gets the specified component of a compound control.
// -----------------------------------------------------------------------------
//    
CCoeControl* CAknAdaptiveSearchGrid::ComponentControl( TInt aIndex ) const
    {
    if(aIndex < iButtonArray.Count() && aIndex >= 0)
        {
        return iButtonArray[aIndex]; 
        }       
    else
        {
        switch(aIndex - iButtonArray.Count() )
            {
            case 0:
                return iNextButton;
            case 1: 
                return iPrevButton;
            case 2: 
                return iCloseButton;
            case 3: 
                return iDeleteButton;
            case 4:
                return iPageIndicator;
            case 5:
                return iInputFrame; 
            case 6:
                return iEditor;                             
            default:
                return NULL;
            }
        }
    }   
    
// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::SetAdaptiveSearchGridVisibility
// Shows or hides grid.
// The position of the top left corner should be set in advance.
// -----------------------------------------------------------------------------
//
void CAknAdaptiveSearchGrid::SetVisibilityL( TBool aVisible, TBool aSelectAll )
    {
    _AKNTRACE( "[%s][%s] Visible : %d", "CAknAdaptiveSearchGrid", __FUNCTION__, aVisible );
    if ( aVisible )
        {      
        SetFocus( ETrue);  
        iCurrentPage = 1;
        ShowL();
        if ( iEditor )
            {
            iEditor->SetFocus( ETrue );
            TInt curPos = iEditor->TextLength(); 
            iEditor->SetCursorPosL( curPos, EFalse );
            if ( aSelectAll) 
                {
                iEditor->SelectAllL();
                }
            }    
        }
    else
        {
        HideL();
        }    
    }

// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::SetButtonGridChars
// 
// -----------------------------------------------------------------------------
//
void CAknAdaptiveSearchGrid::SetButtonGridChars( const TDesC& aGridChars )
    {
     _AKNDEBUG(
               _LIT( KClassName, "CAknAdaptiveSearchGrid" );
               _LIT( KFunctionName, "SetButtonGridChars" );
               _LIT( KFormat, "[%S][%S] grid char is: %S");
               _AKNTRACE( KFormat, 
               &KClassName, &KFunctionName, &aGridChars );
               );

    if( iGridChars )
        {
        delete iGridChars; 
        iGridChars = NULL;
        }

    TRAPD( error, iGridChars = HBufC::NewL( aGridChars.Length() ) );
    if ( error == KErrNone )
            {
            iGridChars->Des().Copy( aGridChars );
            }       

    UpdatePageAndRowCount();
    if( IsShown() )
        {   
        ControlsPositions();    
        TRAP_IGNORE( UpdateVisibleButtonsL() );         
        ShowControls();
        DrawNow();
        }       
    }
    
// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::GridButtonsPositions
// Calculates position of the adaptive search grid buttons.
// iButtonArray should be initialized with buttons in advance 
// -----------------------------------------------------------------------------
//      
void CAknAdaptiveSearchGrid::GridButtonsPositions()
    {
    if( ( iButtonArray.Count() == 0) || (iNumOfPages < 1 ) ) 
        return; 
    
    TRect grid_pane = RectFromLayout( Rect(), AknLayoutScalable_Apps::grid_afind_pane(iLayoutOption) );             
    TRect cell_pane;
    
    TInt temp = 0;          
    for ( TInt j = 0; j < iNumOfRows; j++ )
        {
        for ( TInt i = 0; i < iNumOfCols; i++ ) 
            {
            cell_pane = RectFromLayout( grid_pane, AknLayoutScalable_Apps::cell_afind_pane( iLayoutOption, i, j ) );  
            iButtonArray[temp]->SetRect( cell_pane );
            temp++;
            }               
        }
    TInt variety = 1;
    if( iNumOfPages > 1 )
        variety = 0;
    
    iButtonIconSize = RectFromLayout( cell_pane, AknLayoutScalable_Apps::cell_afind_pane_g1( variety, 0, 0 ) ).Size();  
    }
    
    
// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::ControlsPositions
// Calculates position of the adaptive search gridcontrols.
// -----------------------------------------------------------------------------
//  
void CAknAdaptiveSearchGrid::ControlsPositions()
    {
    TRect cell_pane; 
    
    TRect grid_pane = RectFromLayout( Rect(), AknLayoutScalable_Apps::grid_afind_pane( iLayoutOption ) );   
    TRect find_pane; 
     
    if(iPopupFindpane)
        {
        find_pane = RectFromLayout( Rect(), AknLayoutScalable_Avkon::popup_find_window() );
        }
    else
        {
        find_pane = RectFromLayout( Rect(), AknLayoutScalable_Apps::find_pane_cp01( iLayoutOption ) );
        } 
    _AKNTRACE( "[%s][%s] rect of find pane is %d %d %d %d ", "CAknAdaptiveSearchGrid", __FUNCTION__,
            find_pane.iTl.iX, find_pane.iTl.iY, find_pane.iBr.iX, find_pane.iBr.iY );   
    iInputFrame->SetRect( find_pane ); 
    iSkinContextOfFindPane->SetRect( find_pane );        
   
    // Backspace and close buttons
    cell_pane = RectFromLayout( grid_pane, AknLayoutScalable_Apps::cell_afind_pane(iLayoutOption, iNumOfCols-2, iNumOfRows-1) );        
   
    // For ELJG-7VC8Q2, move delete button up
    if(iPopupFindpane && ( iLayoutOption == KPortraitSinglePage ||iLayoutOption == KLandscapeSinglePage))
        {
        cell_pane.iBr.iY = cell_pane.iBr.iY - iOverlapLength*iNumOfRows;          
        cell_pane.iTl.iY = cell_pane.iTl.iY - iOverlapLength*(iNumOfRows-1); 
        }
     _AKNTRACE( "[%s][%s] rect of delete button is %d %d %d %d ", "CAknAdaptiveSearchGrid", __FUNCTION__,
            cell_pane.iTl.iX, cell_pane.iTl.iY, cell_pane.iBr.iX, cell_pane.iBr.iY );
    iDeleteButton->SetRect( cell_pane );    
    cell_pane = RectFromLayout( grid_pane, AknLayoutScalable_Apps::cell_afind_pane(iLayoutOption, iNumOfCols-1, iNumOfRows-1) );        
   
    // For ELJG-7VC8Q2, move close button up
    if(iPopupFindpane && ( iLayoutOption == KPortraitSinglePage ||iLayoutOption == KLandscapeSinglePage))
        {
        cell_pane.iBr.iY = cell_pane.iBr.iY - iOverlapLength*iNumOfRows;          
        cell_pane.iTl.iY = cell_pane.iTl.iY - iOverlapLength*(iNumOfRows-1); 
        }

     _AKNTRACE( "[%s][%s] rect of close button is %d %d %d %d ", "CAknAdaptiveSearchGrid", __FUNCTION__,
                cell_pane.iTl.iX, cell_pane.iTl.iY, cell_pane.iBr.iX, cell_pane.iBr.iY );
    iCloseButton->SetRect( cell_pane ); 

    // For ELJG-7VC8Q2, Move all the buttons up when there is only one page
    if(iPopupFindpane)
        {
        TInt temp = 0;    
        for ( TInt j = 0; j < iNumOfRows; j++ )
            {
            for ( TInt i = 0; i < iNumOfCols; i++ ) 
                {
                cell_pane = RectFromLayout( grid_pane, AknLayoutScalable_Apps::cell_afind_pane( iLayoutOption, i, j ) );             
                if(iLayoutOption == KPortraitSinglePage ||iLayoutOption == KLandscapeSinglePage )   
                    {
                    cell_pane.iTl.iY -=iOverlapLength*j;
                    cell_pane.iBr.iY -=iOverlapLength*(j+1); 
                    }
                iButtonArray[temp]->SetRect( cell_pane );
                temp++;
                }               
            } 
        }

   
    if ( Layout_Meta_Data::IsLandscapeOrientation() && AknLayoutUtils::LayoutMirrored() )
        {
        SetCornerAndSize( EHLeftVTop, Rect().Size()); 
        }   
   
    if( iNumOfPages > 1 )
        {       
        if( iLayoutOption == KLandscapeMultiPage )
            {
            TRect cont_pane = RectFromLayout( Rect(), AknLayoutScalable_Apps::grid_afind_control_pane(iLayoutOption) );  
            cell_pane = RectFromLayout( cont_pane, AknLayoutScalable_Apps::cell_afind_grid_control_pane(0,0) ); 
            
            // For ELJG-7VC8Q2, Move delete button up
            if(iPopupFindpane)
                {
                cell_pane.iBr.iY = cell_pane.iBr.iY - iOverlapLength*(iNumOfRows+1);
                }

            _AKNTRACE( "[%s][%s] rect of delete button is %d %d %d %d ", "CAknAdaptiveSearchGrid", __FUNCTION__,
                        cell_pane.iTl.iX, cell_pane.iTl.iY, cell_pane.iBr.iX, cell_pane.iBr.iY ); 
            iDeleteButton->SetRect( cell_pane );        
            cell_pane = RectFromLayout( cont_pane, AknLayoutScalable_Apps::cell_afind_grid_control_pane(0,1) ); 

            // For ELJG-7VC8Q2, Move close button up
            if(iPopupFindpane)
                {
                cell_pane.iBr.iY = cell_pane.iBr.iY - iOverlapLength*(iNumOfRows+1);        
                }

            _AKNTRACE( "[%s][%s] rect of close button is %d %d %d %d ", "CAknAdaptiveSearchGrid", __FUNCTION__,
                        cell_pane.iTl.iX, cell_pane.iTl.iY, cell_pane.iBr.iX, cell_pane.iBr.iY );
            iCloseButton->SetRect( cell_pane );         
            }
        // Page pane    
        TRect page_pane;       
        page_pane = RectFromLayout( Rect(), AknLayoutScalable_Apps::afind_page_pane( iLayoutOption) );  
        _AKNTRACE( "[%s][%s] rect of page pane is %d %d %d %d ", "CAknAdaptiveSearchGrid", __FUNCTION__,
                page_pane.iTl.iX, page_pane.iTl.iY, page_pane.iBr.iX, page_pane.iBr.iY );
        AknLayoutUtils::LayoutLabel( iPageIndicator, Rect(), 
        TAknWindowComponentLayout::ComposeText( AknLayoutScalable_Apps::afind_page_pane( iLayoutOption ), 
        AknLayoutScalable_Apps::afind_page_pane_t1() ).LayoutLine() );
        
        // Next and previous buttons
        if ( !AknLayoutUtils::LayoutMirrored() )
            {
            cell_pane = RectFromLayout( page_pane, AknLayoutScalable_Apps::afind_page_pane_g2( iLayoutOption) );  
            
            // For ELJG-7VC8Q2, Move prev button up
            if(iPopupFindpane)
                {
                cell_pane.iBr.iY = cell_pane.iBr.iY - iOverlapLength*(iNumOfRows+1);
                }
            _AKNTRACE( "[%s][%s] rect of pre page button is %d %d %d %d ", "CAknAdaptiveSearchGrid", __FUNCTION__,
                                cell_pane.iTl.iX, cell_pane.iTl.iY, cell_pane.iBr.iX, cell_pane.iBr.iY );
            iPrevButton->SetRect( cell_pane );
            cell_pane = RectFromLayout( page_pane, AknLayoutScalable_Apps::afind_page_pane_g3( iLayoutOption) );  
            
            // For ELJG-7VC8Q2, Move next button up
            if(iPopupFindpane)
                {
                cell_pane.iBr.iY = cell_pane.iBr.iY - iOverlapLength*(iNumOfRows+1);
                }
            _AKNTRACE( "[%s][%s] rect of next page button is %d %d %d %d ", "CAknAdaptiveSearchGrid", __FUNCTION__,
                                cell_pane.iTl.iX, cell_pane.iTl.iY, cell_pane.iBr.iX, cell_pane.iBr.iY );
            iNextButton->SetRect( cell_pane );  
            }
        else
            {
            cell_pane = RectFromLayout( page_pane, AknLayoutScalable_Apps::afind_page_pane_g2( iLayoutOption) ); 

             // For ELJG-7VC8Q2, Move next button up
            if(iPopupFindpane)
                {
                cell_pane.iBr.iY = cell_pane.iBr.iY - iOverlapLength*(iNumOfRows+1);
                } 
            _AKNTRACE( "[%s][%s] rect of next page button is %d %d %d %d ", "CAknAdaptiveSearchGrid", __FUNCTION__,
                                cell_pane.iTl.iX, cell_pane.iTl.iY, cell_pane.iBr.iX, cell_pane.iBr.iY );
            iNextButton->SetRect( cell_pane );       
            cell_pane = RectFromLayout( page_pane, AknLayoutScalable_Apps::afind_page_pane_g3( iLayoutOption) ); 
            
             // For ELJG-7VC8Q2, Move pre button up
            if(iPopupFindpane)
                {
                cell_pane.iBr.iY = cell_pane.iBr.iY - iOverlapLength*(iNumOfRows+1);
                }
 
            _AKNTRACE( "[%s][%s] rect of pre page button is %d %d %d %d ", "CAknAdaptiveSearchGrid", __FUNCTION__,
                                cell_pane.iTl.iX, cell_pane.iTl.iY, cell_pane.iBr.iX, cell_pane.iBr.iY );
            iPrevButton->SetRect( cell_pane );   
            }    
        
        if( AknsUtils::AvkonSkinEnabled() )
            {           
            TRgb textColor = KRgbWhite; 
            TInt error = AknsUtils::GetCachedColor( AknsUtils::SkinInstance(), 
                                                    textColor, 
                                                    KAknsIIDQsnTextColors, 
                                                    EAknsCIQsnTextColorsCG19);
            if( !error )
                {
                TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL(*iPageIndicator, EColorLabelText, textColor) );  
                }                      
            }               
        iBgContextOfControlPane->SetRect( page_pane );     
        }            
    }

// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::NextPage()
// Show next page of adaptive search grid and activate it.
// -----------------------------------------------------------------------------
//
void CAknAdaptiveSearchGrid::NextPage()
    {
    if( iNumOfPages == 1 )
        {
        return;
        }
    else
        {
        if( iCurrentPage == iNumOfPages )
            {
            iCurrentPage = 1;
            }
        else
            {
            iCurrentPage++;
            }
        _AKNTRACE( "[%s][%s] current page is : %d ", "CAknAdaptiveSearchGrid", __FUNCTION__, iCurrentPage );
        TRAP_IGNORE( UpdateVisibleButtonsL() );
        TRAP_IGNORE( UpdatePageIndicatorL() );
        DrawNow();
        }
    }

// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::PrevPage()
// Show previous page of adaptive search grid and activates it.
// -----------------------------------------------------------------------------
//
void CAknAdaptiveSearchGrid::PrevPage()
    {
    if(iNumOfPages == 1)
        {
        return;
        }
    else
        {
        if( iCurrentPage == 1 )
            {
            iCurrentPage = iNumOfPages;
            }
        else
            {
            iCurrentPage--;
            }
        _AKNTRACE( "[%s][%s] current page is : %d ", "CAknAdaptiveSearchGrid", __FUNCTION__, iCurrentPage );
        TRAP_IGNORE( UpdateVisibleButtonsL() );
        TRAP_IGNORE( UpdatePageIndicatorL() );
        DrawNow();
        }
    }


// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::UpdatePageIndicatorL() 
// -----------------------------------------------------------------------------
//
void CAknAdaptiveSearchGrid::UpdatePageIndicatorL()
    {
    // Create text buffer for page indicator
    // 10 is a length of page indicator 
    HBufC* textPageIndicator = HBufC::NewL( 10 );       
    HBufC* temp_text = NULL;
    TRAPD( err, temp_text = HBufC::NewL(10) );
    if( err )
        {
        TRAP_IGNORE( iPageIndicator->SetTextL( KSlashOfPageIndicator ) );
        return;
        }
    TPtr ptr_temp_text = temp_text->Des();
    TPtr ptr_page_number = textPageIndicator->Des();    
   
    NumberConversion::FormatNumber( ptr_page_number, iCurrentPage, AknTextUtils::NumericEditorDigitType() );
    ptr_page_number.Append( KSlashOfPageIndicator );           
    NumberConversion::FormatNumber( ptr_temp_text, iNumOfPages, AknTextUtils::NumericEditorDigitType() );
    ptr_page_number.Append( ptr_temp_text );  
                
    TRAP_IGNORE( iPageIndicator->SetTextL( ptr_page_number ) );
    delete temp_text;
    if ( textPageIndicator )    
        {
        delete textPageIndicator;
        textPageIndicator = NULL;
        }
    }

// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::ShowControls()
// Show and hide controls of adaptive search grid.
// -----------------------------------------------------------------------------
//
void CAknAdaptiveSearchGrid::ShowControls()
    {
    if( iNumOfPages == 1 )
        {
        iNextButton->MakeVisible( EFalse );     
        iPrevButton->MakeVisible( EFalse );       
        iPageIndicator->MakeVisible( EFalse );
        }
    else
        {   
        iNextButton->MakeVisible( ETrue );  
        iPrevButton->MakeVisible( ETrue );          
        iPageIndicator->MakeVisible( ETrue );   
        }
    iCloseButton->MakeVisible( ETrue );
    iDeleteButton->MakeVisible( ETrue );
    iInputFrame->MakeVisible( ETrue ); 
    iEditor->MakeVisible( ETrue );
    }
    
// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::AdaptiveSearchGridShowL()
// Makes adaptive search grid visible and activates it.
// -----------------------------------------------------------------------------
//  
void CAknAdaptiveSearchGrid::ShowL()
    {      
    _AKNTRACE_FUNC_ENTER;
    if( (iButtonArray.Count() == 0) || (iNumOfPages < 1 ) )
        {
        SetShown( EFalse );
        return;
        }       
    
    DrawableWindow()->SetOrdinalPosition( 0, ECoeWinPriorityNormal ); 
    CEikonEnv::Static()->EikAppUi()->AddToStackL( this );   
   
    if( Window().IsFaded()  )
        {
        Window().SetNonFading( ETrue );       
        }
        
    CAknToolbar* toolbar = iAppUi->CurrentFixedToolbar();
    TBool needRelayout = EFalse;
    if( Layout_Meta_Data::IsLandscapeOrientation())
        {
        if ( iLayoutOption == KPortraitMultiPage || iLayoutOption == KPortraitSinglePage )
            {       
            needRelayout = ETrue;
            }
        else if ( toolbar && toolbar->IsVisible() && iToolbarShown == EFalse )
            {
            needRelayout = ETrue;
            }
            
        }
    else if ( iLayoutOption == KLandscapeMultiPage || iLayoutOption == KLandscapeSinglePage )
        {       
        needRelayout = ETrue;
        }
    else if ( toolbar && toolbar->IsShown() && iToolbarShown == EFalse )
        {
        needRelayout = ETrue;
        }
    
    if( iLayoutChanged )
        {
        needRelayout = ETrue;
        iLayoutChanged = EFalse;
        }
   
    if ( needRelayout )
        {
        InitGrid(); 
        UpdatePageAndRowCount(); 
        }
   

    CAknWsEventMonitor* eventMonitor = iAppUi->EventMonitor();
    if ( !eventMonitor->IsEnabled() )
        {
        eventMonitor->AddObserverL( this );
        eventMonitor->Enable();    
        }   
                                        
    ControlsPositions();
    UpdateVisibleButtonsL();    
    ShowControls();
    
    // Make grid visible
    SetShown( ETrue );
    
    // Notify observer, that adaptive search grid was shown
    if ( Observer() )
         {
         Observer()->HandleControlEventL( this, MCoeControlObserver::EEventStateChanged );
         }
         
    ActivateL(); 
    DrawNow();              
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::SetShown
// Sets the flag on or off.
// -----------------------------------------------------------------------------
//
void CAknAdaptiveSearchGrid::SetShown( const TBool aShown )
    {
    iShown = aShown;
    _AKNTRACE( "[%s][%s] set show : %d ", "CAknAdaptiveSearchGrid", __FUNCTION__, aShown );
    CCoeControl::MakeVisible( aShown );
    }
    
// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::HideAdaptiveSearchGrid()
// Disactivate adaptive search grid and hides it.
// -----------------------------------------------------------------------------
//
void CAknAdaptiveSearchGrid::HideL()
    {
    _AKNTRACE_FUNC_ENTER;
    if ( !iShown ) // nothing to hide
        {
        return;
        }  
  
    iEditor->TextView()->SetCursorVisibilityL( 
        TCursor::EFCursorInvisible, TCursor::EFCursorInvisible);
            
    SetFocus( EFalse );
    //fix for TSW error EKDN-7KW9P2
    SetShown( EFalse );
            
    if( iAdaptiveSearchGridObserver )
        {
        iAdaptiveSearchGridObserver->ProcessCommandL( CAknAdaptiveSearchGrid::ECloseGridPressed );        
        }
    CEikonEnv::Static()->EikAppUi()->RemoveFromStack(this);
    DrawableWindow()->SetOrdinalPosition( 0, ECoeWinPriorityNeverAtFront );       
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::FocusChanged
// This function is called whenever a control gains or loses focus.
// -----------------------------------------------------------------------------
// 
void CAknAdaptiveSearchGrid::FocusChanged( TDrawNow aDrawNow )
    {
    if ( !iShown || IsNonFocusing() )
        {
        return; // nothing should be done in this case 
        }      
    if ( !IsFocused() && iLastFocusedButton )               
        iLastFocusedButton->ResetState();        
    
    iInputFrame->SetFocus( IsFocused(), aDrawNow );
    }        
        

// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::HandleWsEventL
// Handles window server events.
// -----------------------------------------------------------------------------
//
void CAknAdaptiveSearchGrid::HandleWsEventL( const TWsEvent& aEvent, CCoeControl* aDestination )
    {  
        _AKNTRACE( "[%s][%s] Ws Event Type : %d ", "CAknAdaptiveSearchGrid", __FUNCTION__, aEvent.Type() );
    if ( !iShown )
        {
        return; // nothing should be done in this case 
        }      
         
    if ( aEvent.Type() == EEventKeyDown && aEvent.Key()->iScanCode != EStdKeyApplication10 )     
        {        
        HideL();
        return;          
        }
         
    if( aEvent.Type() == EEventPointer )
        {     
        TPointerEvent& pointerEvent = *aEvent.Pointer();
        
        if( pointerEvent.iType == TPointerEvent::EButton1Down ) 
            {     
             if( iInputFrame->Rect().Contains(pointerEvent.iPosition) || 
                aDestination != this )
                {  
            MTouchFeedback* feedback = MTouchFeedback::Instance();
            
            // according to Touch UI spec tapping on input frame should cause feedback, 
            // even if action is to cancel dialog..
            if ( feedback )
                {
                feedback->InstantFeedback( this, ETouchFeedbackBasic );
                }
                
                HideL();
                return;                          
                }                             
            }   
        }                     
    }
        
       
// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::HandleControlEventL
// Handles an event from an observed adaptive search grid item.
// -----------------------------------------------------------------------------
//
void CAknAdaptiveSearchGrid::HandleControlEventL( CCoeControl* aControl, TCoeEvent aEventType )
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s][%s] Control Event Type : %d ", "CAknAdaptiveSearchGrid", __FUNCTION__, aEventType );
    switch ( aEventType )
        {
        case MCoeControlObserver::EEventRequestExit:
            {
            HideL();
            break;
            } 
       case EEventRequestFocus:
            FocusChanged( EDrawNow );
            break;     
       case MCoeControlObserver::EEventStateChanged:      
            {
            if( iNumOfPages > 1 && aControl == iPrevButton)
                {
                iLastFocusedButton = iPrevButton;
                PrevPage();            
                break;              
                }
            if( iNumOfPages > 1 && aControl == iNextButton  )
                {
                iLastFocusedButton = iNextButton;               
                NextPage();            
                break;              
                }
            if( aControl == iCloseButton )
                {
                iLastFocusedButton = iCloseButton;
                HideL();                      
                if(iAdaptiveSearchGridObserver)
                    iAdaptiveSearchGridObserver->ProcessCommandL( CAknAdaptiveSearchGrid::ECloseGridPressed);       
                
                break;              
                }           
            if( aControl == iDeleteButton )
                {
                iLastFocusedButton = iDeleteButton;            
                if( iAdaptiveSearchGridObserver )   
                    iAdaptiveSearchGridObserver->ProcessCommandL( CAknAdaptiveSearchGrid::EDeleteLastCharPressed );              
                break;              
                }               
            if( iAdaptiveSearchGridObserver )
                {
                // index of pressed button = index of pressed char
                TInt button_index = iButtonArray.Find( static_cast<CAknButton*>( aControl) );
                if( button_index != KErrNotFound )
                    {                   
                    CAknButton* button = static_cast<CAknButton*>(iButtonArray[button_index]);
                    iLastFocusedButton = button;
                    CAknButtonState* bState = button->State();
                    TInt char_position = iGridChars->Find( bState->Text() );                    
                    if( iAdaptiveSearchGridObserver )                   
                        iAdaptiveSearchGridObserver->ProcessCommandL( char_position );                      
                    }
                }               
            break;  
                }      
        default:
            {
            break;
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }       

// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::UpdateVisibleButtonsL()
// -----------------------------------------------------------------------------
//
void CAknAdaptiveSearchGrid::UpdateVisibleButtonsL()
    {    
    _AKNTRACE_FUNC_ENTER;
    if ( iGridChars )
        {
        // Clear current region of AS
        iCurrentRegion.Clear();
               
        TPtr ptr = iGridChars->Des();
        TInt numOfChars = ptr.Length();    
        CAknButton* button = NULL;
        CAknButtonState* bState = NULL;
        TRect button_rect;  
        CGulIcon* icon = NULL;  
        TBool IsIndic = EFalse;     
        TInt shift_Ind = 0;  
                    
        // If Devanagari ( halant character is present ) 
        if ( KErrNotFound != ptr.Locate(0x094D) )
            {
            IsIndic = ETrue;
            }

        // Hide all the buttons at the beginning for now. 
        CAknButton* tmpButton = NULL;    
        for( TInt i = 0; i < iButtonArray.Count(); i++ )
            {
            tmpButton = static_cast<CAknButton*>( iButtonArray[i] );            
            tmpButton->MakeVisible( EFalse );
            }
                
        TInt tempTotalGridButtons = iTotalGridButtons - KCloseAndClearButtonCount;               
        if( iNumOfPages == 1 )
            {       
            for ( TInt i = 0; i < tempTotalGridButtons; i++ )
                {
                button = static_cast<CAknButton*>( iButtonArray[tempTotalGridButtons-i-1] );
                TInt charPosition = numOfChars-i-1-shift_Ind;
                if ( charPosition >= 0 ) 
                    {
                    bState = button->State();
                    if ( ptr.Mid(charPosition, 1) == KSpaceCharacter )
                        {  
                         // Create icon for space button                        
                        icon = GetColorIconL( 4 );
                        AknIconUtils::SetSize( icon->Bitmap(), iButtonIconSize );
                              
                        bState->SetTextL( KNullDesC );                          
                        bState->SetIcon( icon );
                        button->SetIconSize( iButtonIconSize );                                      
                        }
                    else
                        {
                        if( bState->Icon() )
                            {
                            bState->SetIcon( NULL );          
                            }       
                        // If Devanagari
                        if ( IsIndic && charPosition >= 2  
                            && ptr[charPosition-1] == 0x094D )
                            {                           
                            bState->SetTextL( ptr.Mid(charPosition-2, 3) );                             
                            shift_Ind+=2;
                            }
                        else
                            {                                   
                            bState->SetTextL( ptr.Mid(charPosition, 1) );
                            }
                        }                  
                    button_rect = button->Rect();
                    _AKNTRACE( "[%s][%s] rect of button %s is %d %d %d %d ", "CAknAdaptiveSearchGrid", __FUNCTION__, bState->Text().Ptr(), 
                            button_rect.iTl.iX, button_rect.iTl.iY, button_rect.iBr.iX, button_rect.iBr.iY );
                    iCurrentRegion.AddRect( button_rect );
                    button->MakeVisible( ETrue );
                    }
                else
                    {
                    button->MakeVisible( EFalse );
                    }       
                }   
            }           
        else
            {   
            if( Layout_Meta_Data::IsLandscapeOrientation() )
                    {
                    tempTotalGridButtons = iTotalGridButtons - iNumOfCols; 
                    } 
            UpdatePageIndicatorL();
            TInt numOfCharsInPrevPages = (iCurrentPage-1)*(tempTotalGridButtons);
            shift_Ind = 0;
            if ( IsIndic )
                {
                for (TInt tempItr = 0; tempItr < numOfCharsInPrevPages; ++tempItr)
                    {
                    if ( numOfChars-tempItr >= 3 && 0x094D == ptr[tempItr+1] )
                        {
                        numOfCharsInPrevPages+=2;
                        tempItr+=2;
                        }
                    }
                }            
                
            if( iCurrentPage == iNumOfPages )
                {
                // last page
                TInt charsOnLastPage = numOfChars -  numOfCharsInPrevPages; 
                TInt offset = tempTotalGridButtons - charsOnLastPage;   
                
                for ( TInt i = tempTotalGridButtons-1 ; i >= 0 ; --i )
                    {
                    button = static_cast<CAknButton*>(iButtonArray[i+shift_Ind]);
                    if( i < offset )
                        {
                        button->MakeVisible( EFalse );                  
                        }
                    else
                        {                   
                        bState = button->State();
                        TInt CharPosition = numOfCharsInPrevPages + i - offset; 
                        if( ptr.Mid(CharPosition, 1) == KSpaceCharacter )
                            {  
                             // Create icon for space button                                      
                            icon = GetColorIconL( 4 );
                            AknIconUtils::SetSize( icon->Bitmap(), iButtonIconSize );
                                  
                            bState->SetTextL( KNullDesC );                          
                            bState->SetIcon( icon );
                            button->SetIconSize( iButtonIconSize );                      
                            }
                        else
                            {
                            if( bState->Icon() )
                                {
                                bState->SetIcon( NULL );          
                                }                       
                             // If Devanagari
                            if ( IsIndic && CharPosition >= 2  
                                 && (ptr[CharPosition-1] == 0x094D) )
                                {                           
                                bState->SetTextL( ptr.Mid(CharPosition-2, 3) );                             
                                //i-=2;
                                //shift_Ind+=2;
                                offset+=2;
                                }
                            else
                                {                                   
                                bState->SetTextL( ptr.Mid(CharPosition, 1));                      
                                }                 
                            }                  
                        button_rect = button->Rect();
                        _AKNTRACE( "[%s][%s] rect of button %s is %d %d %d %d ", "CAknAdaptiveSearchGrid", __FUNCTION__, bState->Text().Ptr(), 
                                                button_rect.iTl.iX, button_rect.iTl.iY, button_rect.iBr.iX, button_rect.iBr.iY );
                        iCurrentRegion.AddRect( button_rect );
                        button->MakeVisible( ETrue );
                        }
                    }
                }
            else
                {   
                TInt start = numOfCharsInPrevPages;
                TInt end = start + tempTotalGridButtons;        
                //reset shift_Ind
                shift_Ind = 0;

                for ( TInt i = 0; i < numOfChars; i++ )
                    {
                    if ( ( i >= start) && (i < end) )
                        {   
                        button = static_cast<CAknButton*>(iButtonArray[i-start-shift_Ind]);
                        bState = button->State();               
                        if( ptr.Mid(i, 1) == KSpaceCharacter )
                            {  
                            // Create icon for space button                        
                            icon = GetColorIconL( 4 );
                            AknIconUtils::SetSize( icon->Bitmap(), iButtonIconSize );
                                  
                            bState->SetTextL( KNullDesC );                          
                            bState->SetIcon( icon );
                            button->SetIconSize( iButtonIconSize );                  
                            }
                        else
                            {
                            if( bState->Icon() )
                                {
                                bState->SetIcon( NULL );          
                                }                                       
                            //If Devanagari
                            if ( IsIndic && (numOfChars-i)>=3  
                                && (ptr[i+1] == 0x094D) )
                                {                           
                                bState->SetTextL( ptr.Mid(i, 3) );                             
                                shift_Ind+=2;
                                i+=2;
                                if ( numOfChars - end > 2 )
                                    {
                                    end+=2;
                                    }
                                else
                                    {
                                    end = numOfChars;
                                    }
                                }
                            else
                                {                                   
                                bState->SetTextL( ptr.Mid(i, 1) );
                                }
                            }                  
                        button_rect = button->Rect();
                        _AKNTRACE( "[%s][%s] rect of button %s is %d %d %d %d ", "CAknAdaptiveSearchGrid", __FUNCTION__, bState->Text().Ptr(), 
                                                button_rect.iTl.iX, button_rect.iTl.iY, button_rect.iBr.iX, button_rect.iBr.iY );
                        iCurrentRegion.AddRect( button_rect );
                        button->MakeVisible( ETrue );
                        
                        }                   
                    }
                    if( !Layout_Meta_Data::IsLandscapeOrientation() )
                        {
                        tempTotalGridButtons = iTotalGridButtons;
                        }
                    for ( TInt i = tempTotalGridButtons; i < tempTotalGridButtons+iNumOfCols; i++ )
                        {
                        button = static_cast<CAknButton*>(iButtonArray[i]);
                        button->MakeVisible( EFalse );  
                        }           
                }               
            }        
        button_rect = iDeleteButton->Rect();
        _AKNTRACE( "[%s][%s] rect of delete button is %d %d %d %d ", "CAknAdaptiveSearchGrid", __FUNCTION__,
                                button_rect.iTl.iX, button_rect.iTl.iY, button_rect.iBr.iX, button_rect.iBr.iY );
        iCurrentRegion.AddRect( button_rect );
        button_rect = iCloseButton->Rect();
        _AKNTRACE( "[%s][%s] rect of close button is %d %d %d %d ", "CAknAdaptiveSearchGrid", __FUNCTION__,
                                button_rect.iTl.iX, button_rect.iTl.iY, button_rect.iBr.iX, button_rect.iBr.iY );
        iCurrentRegion.AddRect( button_rect );
        button_rect = iInputFrame->Rect();
        _AKNTRACE( "[%s][%s] rect of Input Frame is %d %d %d %d ", "CAknAdaptiveSearchGrid", __FUNCTION__,
                                        button_rect.iTl.iX, button_rect.iTl.iY, button_rect.iBr.iX, button_rect.iBr.iY );
        iCurrentRegion.AddRect( button_rect );
        if( iNumOfPages > 1 )
            {
            TRect page_pane;       
            page_pane = RectFromLayout( Rect(), AknLayoutScalable_Apps::afind_page_pane(iLayoutOption) );   
            _AKNTRACE( "[%s][%s] rect of page pane is %d %d %d %d ", "CAknAdaptiveSearchGrid", __FUNCTION__,
                    page_pane.iTl.iX, page_pane.iTl.iY, page_pane.iBr.iX, page_pane.iBr.iY );
            iCurrentRegion.AddRect( page_pane );
            }    
        }
    Window().SetShape( iCurrentRegion );
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::UpdatePageAndRowCount
// -----------------------------------------------------------------------------
//
void CAknAdaptiveSearchGrid::UpdatePageAndRowCount()
    {    
    _AKNTRACE_FUNC_ENTER;
    if ( iGridChars )
        {
        TPtr ptr = iGridChars->Des();
        TInt numOfChars = ptr.Length();
        
        // If Devanagari ( halant character is present )
        TInt numOfIndicCharsNotShown(0);
        for ( TInt i = 0; i < numOfChars; ++i )
            {     
            if ( (*iGridChars)[i] == 0x094D )
                numOfIndicCharsNotShown+=2;
            }       
        numOfChars -=numOfIndicCharsNotShown;   
        
        // the row update is not needed as the layout change goes through init
        if(( numOfChars <= iTotalGridButtons - KCloseAndClearButtonCount) || ( numOfChars == iMaxAmountOfButtons )) 
            {
            //one page
            iCurrentPage = 1;
            iNumOfPages = 1;
                        
            if( iLayoutOption == KPortraitMultiPage )
                {
                iNumOfRows = iNumOfRows + 1; // one row for the page pane               
                iTotalGridButtons = iNumOfCols*iNumOfRows; // update new max number of buttons
                }
            
            TInt lastLayoutOption = iLayoutOption;
            iLayoutOption = Layout_Meta_Data::IsLandscapeOrientation() ? 
                KLandscapeSinglePage : KPortraitSinglePage;
            if( lastLayoutOption != iLayoutOption )
                {            
                iLayoutChanged = ETrue;                
                }
            }
        else
            {
            if( iLayoutOption == KPortraitSinglePage )
                {
                iNumOfRows = iNumOfRows - 1; // one row for the page pane               
                iTotalGridButtons = iNumOfCols*iNumOfRows; // update new max number of buttons
                }
              
            TInt tempTotalGridButtons = iTotalGridButtons; 
             
            if( !Layout_Meta_Data::IsLandscapeOrientation() )
                {
                iLayoutOption = KPortraitMultiPage;
                tempTotalGridButtons = tempTotalGridButtons - KCloseAndClearButtonCount; 
                }
            else
                {
                iLayoutOption = KLandscapeMultiPage;
                tempTotalGridButtons = tempTotalGridButtons - iNumOfCols;
                }    

            iCurrentPage = 1;       
            iNumOfPages = numOfChars/tempTotalGridButtons;
            
            // the last page
            if( numOfChars > iNumOfPages*(tempTotalGridButtons) )
                iNumOfPages++;          
            }
        }
    _AKNTRACE( "[%s][%s] number of page is : %d  current page is : %d ", "CAknAdaptiveSearchGrid", __FUNCTION__, iNumOfPages, iCurrentPage );
    _AKNTRACE( "[%s][%s] number of row is : %d  number of total grid button is : %d ", "CAknAdaptiveSearchGrid", __FUNCTION__, iNumOfRows, iTotalGridButtons );
    _AKNTRACE( "[%s][%s] Adaptive search grid layout option is : %d ", "CAknAdaptiveSearchGrid", __FUNCTION__, iLayoutOption );
    _AKNTRACE_FUNC_EXIT;
    }
    
// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::HandleResourceChange
// Handles a change to the control's resources.
// -----------------------------------------------------------------------------
//
void CAknAdaptiveSearchGrid::HandleResourceChange( TInt aType ) 
    {    
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "[%s][%s] Event Type : %d ", "CAknAdaptiveSearchGrid", __FUNCTION__, aType );
    switch( aType )
        {
        case KEikDynamicLayoutVariantSwitch:
            {
            UpdateLayoutVariant();
            break;
            }
        case KAknsMessageSkinChange:
            {
            TRAP_IGNORE( UpdateSkinL() );
            break;
            }
        default:
            {
            break;
            }
        }
        
    CAknControl::HandleResourceChange( aType );
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::IsShown
// Returns adaptive search grid visibility at this moment 
// -----------------------------------------------------------------------------
//
TBool CAknAdaptiveSearchGrid::IsShown() const
    {
    return iShown; 
    }

// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::SetAdaptiveSearchGridObserver
// Sets the observer for the adaptive search grid
// -----------------------------------------------------------------------------
//
void CAknAdaptiveSearchGrid::SetAdaptiveSearchGridObserver( 
    MAknAdaptiveSearchGridObserver* aObserver ) 
    {
    iAdaptiveSearchGridObserver = aObserver;
    }

// -----------------------------------------------------------------------------
// CAknAdaptiveSearchGrid::AdaptiveSearchGridObserver
// Returns a pointer to the adaptive search grid observer.
// -----------------------------------------------------------------------------
//
MAknAdaptiveSearchGridObserver* CAknAdaptiveSearchGrid::AdaptiveSearchGridObserver() 
    {
    return iAdaptiveSearchGridObserver;
    }
        
// End of File

