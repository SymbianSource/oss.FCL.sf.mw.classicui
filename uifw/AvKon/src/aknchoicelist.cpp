/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  CAknChoiceList - Choice list for S60 
*
*/


#include <AknControl.h>
#include <aknlists.h>
#include <aknbutton.h>
#include <avkon.hrh> // AknButton flags
#include <barsread.h> // TResourceReader
#include <AknInfoPopupNoteController.h> // Tooltip
#include "aknchoicelist.h"

#include <AknLayout2ScalableDef.h>
#include <aknlayoutscalable_avkon.cdl.h>

#include <AknsFrameBackgroundControlContext.h> 
#include <AknsConstants.h>
#include <avkon.mbg>
#include <aknglobalpopupprioritycontroller.h>
#include <touchfeedback.h>
#include <AknTasHook.h>
#include <akntranseffect.h>
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
#include <akntransitionutils.h>
#endif

#include "akntrace.h"

// CONSTANTS

const TInt KTimeoutBeforeTooltipNote = 150; // in milliseconds
const TInt KTimeoutInViewTooltipNote = 3000; // in milliseconds

// CLASS DECLARATION

/**
* CAknChoiceListPopupList
* This is a List to be used in side of CAknChoiceListPopup. 
* We had to create a own list for this because currently AvKon 
* lists are not parent relative but main pane relative.
* @internal This should not be used anywhere else!
*/

NONSHARABLE_CLASS(CAknChoiceListPopupList): public CEikFormattedCellListBox
    {
public: // Functions from base classes

    // ---------------------------------------------------------
    // CAknChoiceListPopupList::SizeChanged()
    // ---------------------------------------------------------
    //
    void SizeChanged()
        {   
        CEikFormattedCellListBox::SizeChanged(); 
        TRAP_IGNORE( SizeChangedL() );
        
        TAknLayoutRect cellRect;
        cellRect.LayoutRect( Rect(), 
            AknLayoutScalable_Avkon::list_single_choice_list_pane(0) );

        CFormattedCellListBoxItemDrawer *itemDrawer( ItemDrawer() );

        itemDrawer->SetItemCellSize( cellRect.Rect().Size() );
        }

    TSize MinimumSize()
        {    
        return Size();
        }
    
    // ---------------------------------------------------------
    // CAknChoiceListPopupList::CreateItemDrawerL
    // Item drawer construction
    // ---------------------------------------------------------
    //
    void CreateItemDrawerL()
    {
        CFormattedCellListBoxData* data=CFormattedCellListBoxData::NewL();
        CleanupStack::PushL( data );   

        TAknLayoutText itemText;
        itemText.LayoutText( Rect(), AknLayoutScalable_Avkon::list_single_choice_list_pane_t1(0) );
        const CFont* font = itemText.Font();

        iItemDrawer=new (ELeave) CFormattedCellListBoxItemDrawer( 
            Model(), 
            font, 
            data
            ); //takes ownership
        // Let the choice list background context control the grid skinning
        ItemDrawer()->FormattedCellData()->SetSkinEnabledL( EFalse );
        // Marquee can be requested.. ;) 
        ItemDrawer()->FormattedCellData()->EnableMarqueeL( EFalse );
        CleanupStack::Pop();
    }

    // ---------------------------------------------------------
    // CAknChoiceListPopupList::UpdateTextColors
    // Skin items
    // ---------------------------------------------------------
    //    
    void UpdateTextColors()
    {
        TRgb color( KRgbBlack );  // sane default for nonskinned case
        if ( AknsUtils::AvkonSkinEnabled() )
            {
            AknsUtils::GetCachedColor( AknsUtils::SkinInstance(),
                                   color, KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG8 );
            }

        ItemDrawer()->SetTextColor( color );
        ItemDrawer()->SetBackColor( AKN_LAF_COLOR( 0 ) );

        if ( AknsUtils::AvkonSkinEnabled() )
            {
            AknsUtils::GetCachedColor( AknsUtils::SkinInstance(),
                                   color, KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG8 );
            }

        ItemDrawer()->SetHighlightedTextColor( color );
        ItemDrawer()->SetHighlightedBackColor( AKN_LAF_COLOR( 0 ) );    
    }
        
private:

    // -----------------------------------------------------------------------------
    // CAknChoiceListPopupList::SizeChangedL
    // -----------------------------------------------------------------------------
    //
    void SizeChangedL()
        {
        CFormattedCellListBoxItemDrawer* itemDrawer = ItemDrawer();
        CFormattedCellListBoxData* d = itemDrawer->FormattedCellData();        

        TAknLayoutRect cellRect;
        cellRect.LayoutRect( Rect(), 
            AknLayoutScalable_Avkon::list_single_choice_list_pane(0) );
        
        TRect cell( cellRect.Rect() );

        SetItemHeightL( cell.Height() );

        d->SetTextSubCellL( 0, AknLayoutScalable_Avkon::list_single_choice_list_pane_t1(0) );    
        }       

    };    

// CLASS DECLARATION
/**
*  Control container for choice list
*/
NONSHARABLE_CLASS( CAknChoiceListPopup ) : public CCoeControl,
                  public MEikListBoxObserver,                  
                  MEikCommandObserver
    {
public:      
    CAknChoiceListPopup() : iIndex( -1 ), iCancelled( EFalse )
        {
        AKNTASHOOK_ADD( this, "CAknChoiceListPopup" );
        }

    // Symbian OS default constructor can leave.
    void ConstructL()
        {
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
        SetComponentsToInheritVisibility();    
        CreateChoiceListL();
        Window().SetShadowDisabled( ETrue );

        Window().SetPointerGrab( ETrue );
        SetGloballyCapturing( ETrue );

        MakeVisible( EFalse );

        TRect nullRect( 0, 0, 0, 0 );
        
        iBgContext = CAknsFrameBackgroundControlContext::NewL(
                KAknsIIDQsnFrPopupSub, nullRect, nullRect, EFalse );        
                
        if ( AknLayoutUtils::PenEnabled() )
            {
            SetGloballyCapturing( ETrue );
            SetPointerCapture( ETrue );
            }
        iList->UpdateTextColors();
        }
        
    // Destructor
    ~CAknChoiceListPopup()
        {  
        AKNTASHOOK_REMOVE();
        AknGlobalPopupPriorityController::RemovePopupPriority(*this);
        delete iCba;
        delete iList;
        delete iBgContext;
        }

// New functions
public: 
    
    // ---------------------------------------------------------
    // CAknChoiceListPopup::CloseChoiceList
    // Dismisses CAknChoiceListPopup
    // from the screen and removes it from the control stack
    // ---------------------------------------------------------
    //
    void CloseChoiceList()
        {
        if ( iIsDisplayed )
            {
            MakeVisible( EFalse );    

            if (iCba)
                AknGlobalPopupPriorityController::RemovePopupPriority(*iCba->ButtonGroup()->AsControl());
            delete iCba;
            iCba = NULL;

            SetFocus( EFalse );            

            iAvkonAppUi->RemoveFromStack( this );
            iEikonEnv->BringForwards( EFalse );
            AknGlobalPopupPriorityController::ShowPopup(*this, EFalse);
            
            if ( AknLayoutUtils::PenEnabled() )
                {
                SetPointerCapture( EFalse );
                }
            
            if( iCancelled )
                {
                TRAP_IGNORE( Observer()->HandleControlEventL( this, MCoeControlObserver::EEventRequestCancel ) );
                }
            else
                {
                TRAP_IGNORE( Observer()->HandleControlEventL( this, MCoeControlObserver::EEventStateChanged ) );  
                }
            DrawNow();
            }
        iIsDisplayed = EFalse;    
        }

    // ---------------------------------------------------------
    // CAknChoiceListPopup::UpdateControlContext
    // ---------------------------------------------------------
    //
    void UpdateControlContext()
        {
        TRect rectParent( Rect() );
                          
        TAknLayoutRect layoutRect;
        TInt variety = 0;

        // check if scrollbar-layout should be selected
        if ( iList->Model()->ItemTextArray()->MdcaCount() > 6 )
            {
            variety = 1;

            TRAP_IGNORE( iList->ScrollBarFrame()->SetScrollBarVisibilityL(
                CEikScrollBarFrame::EOff, CEikScrollBarFrame::EOn) );            
            
            AknLayoutUtils::LayoutVerticalScrollBar( iList->ScrollBarFrame(), 
                rectParent, 
                AknLayoutScalable_Avkon::scroll_pane_cp23().LayoutLine()
            );                    
            }
        else
            {
            TRAP_IGNORE( iList->ScrollBarFrame()->SetScrollBarVisibilityL(
                CEikScrollBarFrame::EOff, CEikScrollBarFrame::EOff) );
                
            // Enable scrolling
            iList->DisableScrolling( EFalse );   
            }
            
        layoutRect.LayoutRect( rectParent, 
            AknLayoutScalable_Avkon::list_choice_list_pane( variety ).LayoutLine() );        
        iList->SetRect( layoutRect.Rect() );
                
        TAknLayoutRect innerRect;
        innerRect.LayoutRect( 
            rectParent, 
            AknLayoutScalable_Avkon::list_choice_list_pane(0).LayoutLine() 
            );
        
        iBgContext->SetFrameRects(rectParent, innerRect.Rect());        
        }

    // ---------------------------------------------------------
    // CAknChoiceListPopup::SetItemsL
    // set content array
    // ---------------------------------------------------------
    //      

    void SetItemsL( CDesCArray& aArray )
        {              
        // Set list items.
        CTextListBoxModel* model = iList->Model();    
        model->SetItemTextArray( &aArray );        
        iList->HandleItemAdditionL();
        // We don't want to transfer ownership
        model->SetOwnershipType( ELbmDoesNotOwnItemArray );        
        }
        
    // ---------------------------------------------------------
    // CAknChoiceListPopup::SelectedItem()
    // Ask selected item from the choice list
    // ---------------------------------------------------------
    //
    TInt SelectedItem() const
        {
        return iIndex;
        }
        
    void SetSelectedItem( const TInt aIndex )
        {        
        if ( aIndex >= 0 )
            {
            iIndex = aIndex;                        
            if ( iIsDisplayed && aIndex < iList->Model()->ItemTextArray()->MdcaCount() )
                {                
                iList->SetCurrentItemIndexAndDraw( aIndex );
                }
            }       
        else
            {
            iIndex = -1;            
            }        
        }
    
    // ---------------------------------------------------------
    // CAknChoiceListPopup::SetPopupSizeAndLocation
    // ---------------------------------------------------------
    //
    void SetPopupSizeAndLocation( const TRect& aRect )
        {        
        if ( iIsDisplayed ) 
            {            
            Window().Invalidate();
            }
        SetRect( aRect );        
        TAknLayoutRect listRect;
        
        TInt variety = 0;
        if ( iList->Model()->ItemTextArray()->MdcaCount() > 6 )
            {            
            variety = 1;
            }
        listRect.LayoutRect( aRect, AknLayoutScalable_Avkon::list_choice_list_pane( variety ) );        
        iList->SetSize( listRect.Rect().Size() );        
        }

    void OpenChoiceListL()
        {    
        if ( iIsDisplayed || iList->Model()->ItemTextArray()->MdcaCount() == 0 )
            {            
            return;
            }

        if ( AknLayoutUtils::PenEnabled() )
            {
            SetPointerCapture( ETrue );
            }
        
        iIsDisplayed = ETrue;
        AknGlobalPopupPriorityController::AddPopupToControlStackL( *this );
        iEikonEnv->BringForwards( ETrue );
        DrawableWindow()->SetOrdinalPosition( 0 );    
        AknGlobalPopupPriorityController::ShowPopup(*this, ETrue);
        
        // this will fix possibly corrupted index        
        if ( iIndex < iList->Model()->ItemTextArray()->MdcaCount() && iIndex >= 0 )
            {
            iList->SetCurrentItemIndex( iIndex );
            }
        else if ( iList->Model()->ItemTextArray()->MdcaCount() > 0 )
            {
            iList->SetCurrentItemIndex( 0 );
            }
        CreateCbaL();
        ActivateL();
        MakeVisible( ETrue );
        SetFocus( ETrue );
        iList->SetFocus( ETrue );      
        iCancelled = EFalse;
        UpdateControlContext(); 
        DrawNow();  
        }

// Functions from base classes
public: 

    // ---------------------------------------------------------
    // CAknChoiceListPopup::Draw
    // Symbian OS framework drawing function. Draws the window shadows and
    // outline frame.
    // ---------------------------------------------------------
    //
    void Draw(const TRect& aRect) const
        {                
        CWindowGc& gc = SystemGc();
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        if ( !AknsDrawUtils::Background( skin, iBgContext, gc, aRect ) )
            {
            SystemGc().Clear( aRect );
            }
        
        }
    
    // ---------------------------------------------------------
    // CAknChoiceListPopup::SizeChanged
    // ---------------------------------------------------------
    //
    void SizeChanged()
        {        
        CCoeControl::SizeChanged();        
        UpdateControlContext();
        }

    // ---------------------------------------------------------
    // CAknChoiceListPopup::HandleResourceChange
    // ---------------------------------------------------------
    //
    void HandleResourceChange(TInt aType)
        {
        CCoeControl::HandleResourceChange(aType);
        if ( iCba )
            {
            iCba->HandleResourceChange(aType);
            }
        if( aType == KEikDynamicLayoutVariantSwitch )
            {
            MakeVisible( ETrue );
            }
        if ( aType == KAknsMessageSkinChange )
            {
            iList->UpdateTextColors();
            }
        }

    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
        { 
        if ( aType == EEventKey )
            {            
            if ( aKeyEvent.iScanCode == EStdKeyUpArrow || 
                 aKeyEvent.iScanCode == EStdKeyDownArrow || 
                 aKeyEvent.iScanCode == EStdKeyEnter ||
                 aKeyEvent.iScanCode == EStdKeyDevice3 )
                {            
                return iList->OfferKeyEventL(aKeyEvent, aType);    
                }
            else
                {
                CloseChoiceList();
                return EKeyWasConsumed;                
                }            
            }
        return EKeyWasNotConsumed;          
        }

private:

     // ---------------------------------------------------------
    // CAknChoiceListPopup::CountComponentControls
    // ---------------------------------------------------------
    //
    TInt CountComponentControls() const
        {
        return 1;
        }

    // ---------------------------------------------------------
    // CAknChoiceListPopup::ComponentControl
    // ---------------------------------------------------------
    //
    CCoeControl* ComponentControl(TInt aIndex) const
        {
        if ( aIndex == 0 )
            {            
            return iList;
            }
        return NULL;    
        }

    // ---------------------------------------------------------
    // CAknChoiceListPopup::HandlePointerEventL
    // Decides what to do when pen is used and choice list is active
    // ---------------------------------------------------------
    //
    void HandlePointerEventL(const TPointerEvent &aPointerEvent)
        {
        
        if ( AknLayoutUtils::PenEnabled() )
            {
            
            // Make sure that scrolling is enabled for choicelist
            if ( iList->ScrollingDisabled() )
                {
                iList->DisableScrolling( EFalse );
                }
                    
            TRect ctrlArea = iList->Rect();
            
            if ( aPointerEvent.iType == TPointerEvent::EButton1Down )
                {
                if ( !ctrlArea.Contains( aPointerEvent.iPosition ) )
                    {
                    iCancelled = ETrue;
                    SetSelectedItem( iIndex );
                    CloseChoiceList();
                    return;
                    }

                TInt index;
                if ( iList->View()->XYPosToItemIndex( aPointerEvent.iPosition, index ))
                    {                         
                    if ( !iAvkonAppUi->IsSingleClickCompatible() )
                        {
                        // Pressed Down Effect
                        iList->View()->ItemDrawer()->SetFlags( 
                                CListItemDrawer::EPressedDownState );            
                        }  
                    }
                }
            CCoeControl::HandlePointerEventL( aPointerEvent );
            }
        }

    // ---------------------------------------------------------
    // CAknChoiceListPopup::ProcessCommandL
    // Softkey event handling
    // ---------------------------------------------------------
    //
    void ProcessCommandL(TInt aCommandId)
        {
        switch (aCommandId)
            {
            case EAknSoftkeyCancel:
                iCancelled = ETrue;
                CloseChoiceList();
                break;
            case EAknSoftkeySelect:
                iCancelled = EFalse;
                HandleListBoxEventL( iList, EEventEnterKeyPressed );
                break;
            default:
                return;
            }
        }

    // ---------------------------------------------------------
    // CAknChoiceListPopup::HandleListBoxEventL
    // Handles item selection in the grid
    // ---------------------------------------------------------
    //
    void HandleListBoxEventL(CEikListBox* aListBox, TListBoxEvent aEventType)
        {
        if ( aListBox == iList 
            && ( aEventType == EEventEnterKeyPressed 
            || aEventType == EEventItemClicked  
            || aEventType == EEventItemSingleClicked ) )
            {        
            iIndex = iList->CurrentItemIndex();        
            CloseChoiceList();
            }                
        }
    
    TTypeUid::Ptr MopSupplyObject(TTypeUid aId)
        {
        if ( aId.iUid == MAknsControlContext::ETypeId )
            {
            return ( MAknsControlContext::SupplyMopObject( aId, iBgContext ) ) ;
            }
        if ( iCba )
            {            
            return MAknsControlContext::SupplyMopObject(aId, (MAknsControlContext*)iCba);
            }
        return TTypeUid::Null();            
        }

private:

    // ---------------------------------------------------------
    // CAknChoiceListPopup::CreateChoiceListL
    // Choice list construction (component control of CAknChoiceListPopup)
    // ---------------------------------------------------------
    //
    void CreateChoiceListL()
        {
        ASSERT(!iList);
        iList = new ( ELeave ) CAknChoiceListPopupList;    
        iList->SetContainerWindowL( *this );
        iList->ConstructL( this, EAknListBoxSelectionList );    
        iList->CreateScrollBarFrameL( ETrue );         
        iList->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff, CEikScrollBarFrame::EOn);
        iList->SetListBoxObserver(this);    
        iList->SetMopParent( this );        
       }


    // ---------------------------------------------------------
    // CAknChoiceListPopup::CreateCbaL
    // Softkey construction (component control of CAknChoiceListPopup)
    // ---------------------------------------------------------
    //
    void CreateCbaL()
        {
        ASSERT(!iCba);
        
        iCba = CEikButtonGroupContainer::NewL(CEikButtonGroupContainer::ECba,
                                              CEikButtonGroupContainer::EHorizontal,
                                              this, R_AVKON_SOFTKEYS_SELECT_CANCEL__SELECT);
        AknGlobalPopupPriorityController::AddSubPopupL(*this, *iCba->ButtonGroup()->AsControl());
        AknGlobalPopupPriorityController::AddPopupToControlStackL(*iCba->ButtonGroup()->AsControl(),
            ECoeStackPriorityCba, ECoeStackFlagRefusesFocus );
        iCba->DrawDeferred();
        }
    
// Data
private:    
    CAknChoiceListPopupList* iList;
    CEikButtonGroupContainer* iCba;
    TInt iIndex;
    TBool iIsDisplayed;
    CAknsFrameBackgroundControlContext* iBgContext;
    TBool iCancelled;
    };

// --------------------------------------------------------------------------
// Two-phased constructor.
// --------------------------------------------------------------------------
//
EXPORT_C CAknChoiceList* CAknChoiceList::NewL( CCoeControl* aParent, 
    CDesCArray* aItemArray, TInt aFlags, CAknButton* aButton )
    {
    _AKNTRACE_FUNC_ENTER;
    CAknChoiceList* self = NewLC( aParent, aItemArray, aFlags, aButton );
    CleanupStack::Pop( self );
    _AKNTRACE_FUNC_EXIT;
    return self;
    }

EXPORT_C CAknChoiceList* CAknChoiceList::NewLC( CCoeControl* aParent, 
    CDesCArray* aItemArray, TInt aFlags, CAknButton* aButton )
    {
    _AKNTRACE_FUNC_ENTER;
    CAknChoiceList* self = new (ELeave) CAknChoiceList;
    CleanupStack::PushL( self );
    self->ConstructL( aParent, aItemArray, aFlags, aButton );
    AKNTASHOOK_ADDL( self, "CAknChoiceList" );
    _AKNTRACE_FUNC_EXIT;
    return self;    
    }

// --------------------------------------------------------------------------
// default constructor.
// --------------------------------------------------------------------------
//
CAknChoiceList::CAknChoiceList() : 
    iSelectedIndex( 0 ),   
    iIsClosed( ETrue ),
    iTooltipWaitInterval( KTimeoutBeforeTooltipNote ),
    iTooltipInViewInterval( KTimeoutInViewTooltipNote ),
    iTooltipPosition( EPositionTop )
    {
    }
    
// --------------------------------------------------------------------------
// default destructor.
// --------------------------------------------------------------------------
//
CAknChoiceList::~CAknChoiceList()
    {
    _AKNTRACE_FUNC_ENTER;
    AKNTASHOOK_REMOVE();
    if ( !iIsClosed )
        {
        HideChoiceList();
        }

    delete iButton; 
    delete iLabel;
     
    if( iArray )
        {
        iArray->Reset();      
        }    
    delete iArray;      
    delete iPopup;
    delete iTooltipText;
    delete iTooltip;
    _AKNTRACE_FUNC_EXIT;
    }

// --------------------------------------------------------------------------
// CAknChoiceList::ConstructL 
// --------------------------------------------------------------------------
//
void CAknChoiceList::ConstructL( CCoeControl* aParent, 
    CDesCArray* aItemArray, TInt aFlags, CAknButton* aButton )
    {
    _AKNTRACE_FUNC_ENTER;
    if ( ! iTooltip )
        {
        iTooltip = CAknInfoPopupNoteController::NewL();
        }
    
    iTooltip->SetTimeDelayBeforeShow( iTooltipWaitInterval );
    iTooltip->SetTimePopupInView( iTooltipInViewInterval );
    iTooltip->SetTooltipModeL( ETrue );

    iFlags = aFlags;
    SetContainerWindowL( *aParent );    
    
    iPopup = new (ELeave) CAknChoiceListPopup;
    iPopup->ConstructL();
    iPopup->SetObserver( this );
    
    iArray = aItemArray;
    
    // Check here which type of choice list is used and construct them properly   
    if ( iFlags & EAknChoiceListWithoutCurrentSelection )    
        {        
        SetButtonL( aButton );                   
        }
    else if ( iFlags & EAknChoiceListWithCurrentSelection ) 
        {           
        ConstructTypicalChoiceListL();       
        }
    
    SetComponentsToInheritVisibility( ETrue );
    _AKNTRACE_FUNC_EXIT;
    }

// --------------------------------------------------------------------------
// CAknChoiceList::SizeChanged 
// --------------------------------------------------------------------------
//
void CAknChoiceList::SizeChanged()
    {
    _AKNTRACE_FUNC_ENTER;
    if ( iFlags & EAknChoiceListWithCurrentSelection ) 
        {
        
        TAknWindowLineLayout layout = AknLayoutScalable_Avkon::choice_list_pane().LayoutLine();                
        
        // width is taken from given rect, height is fixed value from layout data
        iSize = TSize( Size().iWidth, layout.iH );
        TRect parent( Rect() );
              
        AknLayoutUtils::LayoutLabel( 
            iLabel, 
            parent, 
            AknLayoutScalable_Avkon::choice_list_pane_t1().LayoutLine() 
            );        
        // Override font color
        if ( AknsUtils::AvkonSkinEnabled() )
            {
           TRgb textColor;

            if ( AknsUtils::GetCachedColor( AknsUtils::SkinInstance(), textColor, 
                KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG8) == KErrNone )
                {
                TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( 
                    *iLabel, EColorLabelText, textColor) );
                }
            }
        TAknLayoutRect buttonLayoutRect;
        buttonLayoutRect.LayoutRect( parent, AknLayoutScalable_Avkon::choice_list_pane_g1().LayoutLine() );            
        
        iButton->SetRect( buttonLayoutRect.Rect() );
        }
    else if ( iFlags & EAknChoiceListWithoutCurrentSelection )
        {
        iButton->SetRect( Rect() );
        }

    // if Choice list is open then update it by opening and closing it.
        if ( !iIsClosed )
            {
            SetPopupRect();
            }
    }

// --------------------------------------------------------------------------
// CAknChoiceList::Draw
// --------------------------------------------------------------------------
//
EXPORT_C void CAknChoiceList::Draw( const TRect& /*aRect*/ ) const
    {
    }

EXPORT_C void CAknChoiceList::PositionChanged()
    {
    _AKNTRACE_FUNC_ENTER;
    CAknControl::PositionChanged();
    _AKNTRACE_FUNC_EXIT;
    }

// --------------------------------------------------------------------------
// CAknChoiceList::ComponentControl 
// --------------------------------------------------------------------------
//    
EXPORT_C CCoeControl* CAknChoiceList::ComponentControl( TInt aIndex ) const
    {
    switch ( aIndex )
        {
        case 0: 
            return (CCoeControl*)iButton;            
        case 1: 
            return (CCoeControl*)iLabel;
        default:
            return NULL;
        }
    
    }

// --------------------------------------------------------------------------
// CAknChoiceList::CountComponentControls
// --------------------------------------------------------------------------
//
EXPORT_C TInt CAknChoiceList::CountComponentControls() const
    {  
    TInt count = 1; // always button
    
    // If using the default type of choice list then using two controls inside this control
    if ( iFlags & EAknChoiceListWithCurrentSelection )
        {
        count++;
        }    
   
    return count;
    }

// --------------------------------------------------------------------------
// CAknChoiceList::ShowChoiceList 
// --------------------------------------------------------------------------
//
EXPORT_C TInt CAknChoiceList::ShowChoiceListL()
    {
    _AKNTRACE_FUNC_ENTER;
    if( !iIsClosed || iArray->Count() < 1 )
        {
        _AKNTRACE("ShowChoiceListL: !iIsClosed or iArray->Count() < 1, return");
        return KErrGeneral;
        }
    
    // Set choice list to opened mode 
    iIsClosed = EFalse;        
    iPopup->SetItemsL( *iArray );        
    SetSelectedIndex( iSelectedIndex );
    SetPopupRect();                
    iPopup->OpenChoiceListL();
    
    _AKNTRACE_FUNC_EXIT;
    return KErrNone;  
    } 

// --------------------------------------------------------------------------
// CAknChoiceList::HideChoiceList 
// --------------------------------------------------------------------------
//
EXPORT_C void CAknChoiceList::HideChoiceList() 
    {
    iPopup->CloseChoiceList();
    iIsClosed = ETrue;
    iSelectedIndex = iPopup->SelectedItem();
    }

// --------------------------------------------------------------------------
// CAknChoiceList::SetTooltipTextL 
// --------------------------------------------------------------------------
//
EXPORT_C void CAknChoiceList::SetTooltipTextL( const TDesC& aText )
    {
    _AKNTRACE("CAknChoiceList::SetTooltipTextL aText=%S", &aText);
    delete iTooltipText;
    iTooltipText = NULL;
    
    iTooltipText = aText.AllocL();
    }

// --------------------------------------------------------------------------
// CAknChoiceList::SetTooltipTimeouts 
// --------------------------------------------------------------------------
//
EXPORT_C void CAknChoiceList::SetTooltipTimeouts( const TInt aBeforeTimeout,
                                                  const TInt aInViewTimeout )
    {
    if ( aBeforeTimeout >= 0 )
        {
        iTooltipWaitInterval = aBeforeTimeout;
        }
    if ( aInViewTimeout >= 0 )
        {
        iTooltipInViewInterval = aInViewTimeout;
        }
    iTooltip->SetTimeDelayBeforeShow( iTooltipWaitInterval );
    iTooltip->SetTimePopupInView( iTooltipInViewInterval );
    }

// --------------------------------------------------------------------------
// CAknChoiceList::SetTooltipPosition
// --------------------------------------------------------------------------
//
EXPORT_C void CAknChoiceList::SetTooltipPosition( 
    TTooltipPosition aPosition )
    {
    iTooltipPosition = aPosition;
    }
    
// --------------------------------------------------------------------------
// CAknChoiceList::SetButtonL
// --------------------------------------------------------------------------
//
EXPORT_C void CAknChoiceList::SetButtonL( CAknButton* aButton )
    {
    if ( iButton )
        {
        delete iButton;
        iButton = NULL;
        }
        
    iButton = aButton;  
    iButton->SetObserver( this );
    iButton->SetContainerWindowL( *this ); 
    }

// --------------------------------------------------------------------------
// CAknChoiceList::SetSelectedIndex 
// --------------------------------------------------------------------------
//
EXPORT_C void CAknChoiceList::SetSelectedIndex( const TInt aIndex )
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE("SetSelectedIndex: aIndex=%d", aIndex);
    if ( !iArray )
        {
        _AKNTRACE("SetSelectedIndex: no iArray, return");
        return;
        }
        
    if ( aIndex >= -1 && aIndex < iArray->Count() )
        {        
        iSelectedIndex = aIndex;
        }
    else
        {
        iSelectedIndex = 0;
        }
    if ( !iIsClosed )
        {        
        iPopup->SetSelectedItem( iSelectedIndex );
        }
    if ( iFlags & EAknChoiceListWithCurrentSelection )
        {
        TRAP_IGNORE( UpdateLabelL() );    
        Window().Invalidate( iLabel->Rect() );
        }    
    
    SizeChanged();
    _AKNTRACE_FUNC_EXIT;
    }

// --------------------------------------------------------------------------
// CAknChoiceList::MinimumSize
// --------------------------------------------------------------------------
//
EXPORT_C TSize CAknChoiceList::MinimumSize()
    {       
    TSize size;
    
    // Although if there's only a button then it's size is used.
    if ( iFlags & EAknChoiceListWithoutCurrentSelection )
        {
        size = iButton->MinimumSize();
        }  
    else
        {
        size = Size();
        }
    
    return size;    
    }
    
// --------------------------------------------------------------------------
// CAknChoiceList::HandleControlEvent
// --------------------------------------------------------------------------
//
EXPORT_C void CAknChoiceList::HandleControlEventL( CCoeControl* aControl,TCoeEvent aEventType )
    {
    _AKNTRACE_FUNC_ENTER;
    if ( ( aControl == iButton || aControl == iLabel ) && aEventType == EEventStateChanged )
        {          
        if ( iIsClosed )
            {
            ShowChoiceListL();
            }        
        }
    // Popup is closed
    else if ( !iIsClosed && aControl == iPopup && 
              ( aEventType == EEventStateChanged || aEventType == EEventRequestCancel ) )
        {
        if( aEventType == EEventStateChanged )
            {
            iSelectedIndex = iPopup->SelectedItem();
            SetSelectedIndex( iPopup->SelectedItem() );
            }
        iIsClosed = ETrue;        
        
        if ( Observer() )
            {
            Observer()->HandleControlEventL( this, aEventType );    
            }        
        }
    _AKNTRACE_FUNC_EXIT;
    }
        
// --------------------------------------------------------------------------
// CAknChoiceList::HandleResourceChange
// --------------------------------------------------------------------------
//
EXPORT_C void CAknChoiceList::HandleResourceChange( TInt aType )
    {
    _AKNTRACE_FUNC_ENTER;
    CCoeControl::HandleResourceChange( aType );
    
    if ( aType == KAknsMessageSkinChange )
        {
        if ( !(iFlags & EAknChoiceListWithoutCurrentSelection) )
            {            
            // has to be done for button update
            TRAP_IGNORE( ConstructTypicalChoiceListL() );
            }
        // Item colors
        iPopup->HandleResourceChange( aType );

        // Label color
        if ( AknsUtils::AvkonSkinEnabled() && iLabel )
            {
           TRgb textColor;

            if ( AknsUtils::GetCachedColor( AknsUtils::SkinInstance(), textColor, 
                KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG8) == KErrNone )
                {
                TRAP_IGNORE( 
                    AknLayoutUtils::OverrideControlColorL( 
                        *iLabel, EColorLabelText, textColor) );
                }
            }
        }
    else if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        SizeChanged();
        }    
    _AKNTRACE_FUNC_EXIT;
    }

// --------------------------------------------------------------------------
// CAknChoiceList::OfferKeyEventL
// --------------------------------------------------------------------------
//
EXPORT_C TKeyResponse CAknChoiceList::OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType )
    {
    _AKNTRACE_FUNC_ENTER;
    if ( aType == EEventKey )
        {        
        if ( iIsClosed && ( aKeyEvent.iScanCode == EStdKeyEnter ||
             aKeyEvent.iScanCode == EStdKeyDevice3 ) )
            {            
            ShowChoiceListL();
            return EKeyWasConsumed;
            }    
        else if ( !iIsClosed )
            {
            return iPopup->OfferKeyEventL( aKeyEvent, aType );        
            }
        return EKeyWasNotConsumed;        
        }
    _AKNTRACE_FUNC_EXIT;
    return EKeyWasNotConsumed;        
    }

// --------------------------------------------------------------------------
// CAknChoiceList::HandlePointerEventL
// --------------------------------------------------------------------------
//
void CAknChoiceList::HandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    _AKNTRACE_FUNC_ENTER;
    CCoeControl::HandlePointerEventL( aPointerEvent );
    
    if ( !AknLayoutUtils::PenEnabled() || !iLabel )
        {
        return;
        }
    
    MTouchFeedback* feedback = MTouchFeedback::Instance();
    switch ( aPointerEvent.iType )
        {
        case TPointerEvent::EButton1Down:
            {
            if ( feedback && iArray->Count() > 0 )
                {
                feedback->InstantFeedback(
                    this,
                    ETouchFeedbackBasicItem,
                    aPointerEvent );
                }     
            if ( Rect().Contains( aPointerEvent.iPosition ))
                {
                ShowTooltipL();               
                }
            }
            break;
            
        case TPointerEvent::EDrag:
            {
            if ( !Rect().Contains( aPointerEvent.iPosition ))   
                {
                iTooltip->HideInfoPopupNote();
                }
            }
            break;
            
        case TPointerEvent::EButton1Up:
            {
            if ( feedback && iArray->Count() > 0 )
                {
                if ( CAknTransitionUtils::TransitionsEnabled( 
                        AknTransEffect::EComponentTransitionsOff ) )
                    {
                    feedback->InstantFeedback(
                        this,
                        ETouchFeedbackPopupOpen,
                    	aPointerEvent );
                    }
                else
                    {
                    feedback->InstantFeedback(
                        this,
                        ETouchFeedbackPopUp,
                    	aPointerEvent );
                    }
                }
            iTooltip->HideInfoPopupNote();        
            TRect ctrlArea = iLabel->Rect();
            if ( ctrlArea.Contains( aPointerEvent.iPosition ))
                {
                HandleControlEventL( iLabel, EEventStateChanged );
                }
            }
            break;
        }
    _AKNTRACE_FUNC_EXIT;
    }

// --------------------------------------------------------------------------
// CAknChoiceList::SelectedIndex
// --------------------------------------------------------------------------
//
EXPORT_C TInt CAknChoiceList::SelectedIndex() const
    {    
    return iSelectedIndex;
    }
    
// --------------------------------------------------------------------------
// CAknChoiceList::SetItems 
// --------------------------------------------------------------------------
//
EXPORT_C void CAknChoiceList::SetItems( CDesCArray* aArray )
    {            
    if ( iArray && aArray && iArray != aArray )
        {
        iArray->Reset();
        delete iArray;
        iArray = NULL;
        }                
    iArray = aArray;    
    TRAP_IGNORE( iPopup->SetItemsL( *iArray ) );
    
    if ( !iIsClosed )
        {
        if ( iArray && iArray->Count() > 0 )
            {            
            SetPopupRect();
            }
        else
            {
            HideChoiceList();
            }
        }    
    SetSelectedIndex( 0 );
    }
    
// --------------------------------------------------------------------------
// CAknChoiceList::SetItems
// --------------------------------------------------------------------------
//
EXPORT_C void CAknChoiceList::SetItemsL( TInt aResourceId )
    {        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, aResourceId );    
    CDesCArray* array;    
    array = reader.ReadDesC16ArrayL();   
    iSelectedIndex = 0;
    
    CleanupStack::PopAndDestroy(); // reader

    if ( iArray )
        {
        iArray->Reset();
        delete iArray;
        iArray = NULL;
        }                  
    iArray = array;      
    iPopup->SetItemsL( *iArray );      
    
    if ( !iIsClosed )
        {
        if ( iArray->Count() > 0 )
            {            
            SetPopupRect();
            }
        else
            {
            HideChoiceList();
            }
        }
    SetSelectedIndex( 0 );                
    }

    

// --------------------------------------------------------------------------
// CAknChoiceList::AddItemL 
// --------------------------------------------------------------------------
//
EXPORT_C TInt CAknChoiceList::AddItemL( const TDesC* aDesC )
    {
    _AKNTRACE("CAknChoiceList::AddItemL: aDesC=%S", aDesC);
    iArray->AppendL( *aDesC );    
    iPopup->SetItemsL( *iArray );    
    
    if ( !iIsClosed )
        {        
        SetPopupRect();                
        }
    UpdateLabelL();
    TInt index = iArray->Count() - 1; // return new items index
    return index;
    }

// --------------------------------------------------------------------------
// CAknChoiceList::RemoveItem 
// --------------------------------------------------------------------------
//    
EXPORT_C void CAknChoiceList::RemoveItem( const TInt aIndex )
    {
    _AKNTRACE("CAknChoiceList::RemoveItem: aIndex=%d", aIndex);
    // if the choice list is open then just return. 
      
    if( aIndex < iArray->Count() && aIndex >= 0 )
        {
        iArray->Delete( aIndex );    
        if ( aIndex <= iSelectedIndex && iSelectedIndex > -1 )
            {
            iSelectedIndex--;
            }
        SetSelectedIndex( iSelectedIndex );
        }          
        
    if ( !iIsClosed )
        {        
        if ( iArray->Count() > 0 )
            {
            TRAP_IGNORE( iPopup->SetItemsL( *iArray ) );        
            SetPopupRect();                
            }
        else 
            {
            HideChoiceList();
            }
        }
    
    }

// --------------------------------------------------------------------------
// CAknChoiceList::SetFlags
// --------------------------------------------------------------------------
//    
EXPORT_C void CAknChoiceList::SetFlags( const TInt aFlags )
    {
    // List type must be remained if not inculed in aFlags
    if ( !( aFlags & EAknChoiceListWithCurrentSelection )&&
         !( aFlags & EAknChoiceListWithoutCurrentSelection ) )
        {
        if ( iFlags & EAknChoiceListWithCurrentSelection )
            {
            iFlags = aFlags | EAknChoiceListWithCurrentSelection;
            }
        else 
            {
            iFlags = aFlags | EAknChoiceListWithoutCurrentSelection;
            }
        }
    else
        {
        iFlags = aFlags;
        }
    }

// --------------------------------------------------------------------------
// CAknChoiceList::Flags
// --------------------------------------------------------------------------
//    
EXPORT_C TInt CAknChoiceList::Flags() const
    {    
    return iFlags;
    }
    
// --------------------------------------------------------------------------
// CAknChoiceList::InsertItemL
// --------------------------------------------------------------------------
//    
EXPORT_C TInt CAknChoiceList::InsertItemL( TInt aIndex, const TDesC& aText )
    {
    ASSERT( iArray );
    if ( aIndex >= 0 && aIndex <= iArray->Count() )
        {
        iArray->InsertL( aIndex, aText );
        if ( aIndex <= iSelectedIndex )
            {
            SetSelectedIndex( ++iSelectedIndex );
            }
        }
    else
        {
        aIndex = iArray->Count();
        iArray->InsertL( aIndex, aText );
        }   
    iPopup->SetItemsL( *iArray );   
    if ( !iIsClosed )
        {
        SetPopupRect();
        }        
    return aIndex;    
    }
    
// --------------------------------------------------------------------------
// CAknChoiceList::ConstructTypicalChoiceListL
// --------------------------------------------------------------------------
//
void CAknChoiceList::ConstructTypicalChoiceListL()
    {
    CGulIcon* icon = AknsUtils::CreateGulIconL( AknsUtils::SkinInstance(),
                                       KAknsIIDQgnPropSetButton,
                                       AknIconUtils::AvkonIconFileName(),
                                       EMbmAvkonQgn_prop_set_button,
                                       EMbmAvkonQgn_prop_set_button_mask  );
 
  
    CAknButton* button = CAknButton::NewL(
        icon, 
        NULL, 
        NULL, 
        NULL, 
        KNullDesC, 
        KNullDesC, 
        KAknButtonNoFrame, 
        0 
        );     
    
    SetButtonL( button );    
    SetSelectedIndex( iSelectedIndex );  
    }
    
// --------------------------------------------------------------------------
// CAknChoiceList::SetPopupRect
// --------------------------------------------------------------------------
//
void CAknChoiceList::SetPopupRect()
    {    
    TInt numItems( iArray->Count() );
    if ( numItems == 0 )
        {
        return;
        }  
        
    // height must be adjusted. Max variety is 5 (6 visible items)    
    if ( numItems > 6 )
        {
        numItems = 6;
        }
    
    TAknWindowComponentLayout window = AknLayoutScalable_Avkon::
        popup_choice_list_window( numItems - 1 );
    
    TAknWindowLineLayout layout = window.LayoutLine();
    
    TInt height( layout.iH );
    TInt width;
    
        width = Size().iWidth;

    TPoint position; 
    
    // allowed rect
    TRect clientRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, clientRect );
       
    if ( iFlags & EAknChoiceListPositionLeft ) 
        {
        position = TPoint( PositionRelativeToScreen() - TPoint( width, 0 ) ); 
        }
    else if ( iFlags & EAknChoiceListPositionRight )
        {
        position = TPoint( PositionRelativeToScreen() + TPoint( width, 0 ) );         
        }
    else if ( iFlags & EAknChoiceListPositionBottom )// bottom
        {
        position = TPoint( PositionRelativeToScreen() + TPoint(0, Size().iHeight ) ); 
        }
    else // with current selection locate popup on top of the area
        {        
        position = TPoint( PositionRelativeToScreen() - TPoint(0, height ) );     
        }  

    // Horizontal check, readjusted if needed.
    if ( position.iX < clientRect.iTl.iX )
        {
        position.iX = clientRect.iTl.iX;
        }
    else if ( ( position.iX + width ) > clientRect.iBr.iX )
        {
        position.iX = clientRect.iBr.iX - width;
        } 
        
    // Vertical check, readjusted if needed.
    if ( position.iY < clientRect.iTl.iY )
        {
        position.iY = clientRect.iTl.iY;
        }
    else if ( ( position.iY + height ) > clientRect.iBr.iY )
        {
        position.iY = clientRect.iBr.iY - height;
        }
    TRect old (iPopup->Rect() );
    iPopup->SetPopupSizeAndLocation( TRect( position, TSize( width, height ) ) );  
    Window().Invalidate( old );
    }
    
// --------------------------------------------------------------------------
// CAknChoiceList::UpdateLabelL
// --------------------------------------------------------------------------
//
void CAknChoiceList::UpdateLabelL()
    {
    if ( !iFlags & EAknChoiceListWithCurrentSelection )
        {
        return;
        }
    if ( !iLabel )
        {
        iLabel = new (ELeave) CEikLabel;
        iLabel->SetContainerWindowL( *this );
        
        // Set font
        TAknTextComponentLayout labelLayout = 
            AknLayoutScalable_Avkon::choice_list_pane_t1();
        iLabel->SetFont( AknLayoutUtils::FontFromId( labelLayout.Font() ) );

        // Set font color
        if ( AknsUtils::AvkonSkinEnabled() )
            {
           TRgb textColor;

            if ( AknsUtils::GetCachedColor( AknsUtils::SkinInstance(), textColor, 
                KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG8) == KErrNone )
                {
                TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( 
                    *iLabel, EColorLabelText, textColor) );
                }
            }
        }
    
    if ( iSelectedIndex >= 0 && iArray->Count() > 0 )
        {        
        TPtrC text = iArray->MdcaPoint( iSelectedIndex ); 
        if ( &text )
            {        
            iLabel->SetTextL( text );  
            }
        }        
    else if ( iSelectedIndex == -1 || iArray->Count() == 0 )
        {
        iLabel->SetTextL( KNullDesC );
        }
    else
        {
        iSelectedIndex = 0;
        UpdateLabelL();
        }
    }    

// --------------------------------------------------------------------------
// CAknChoiceList::ShowTooltipL
// --------------------------------------------------------------------------
//
void CAknChoiceList::ShowTooltipL()
    {
    if ( !iTooltipText || (iTooltipText->Length() <= 0 ))
        {
        return;
        }
    iTooltip->SetTextL( *iTooltipText );
    
    
    // Position the tooltip
    TPoint position;
    
    if ( AknsUtils::GetControlPosition( this, position ) != KErrNone )
        {
        position = PositionRelativeToScreen();
        }
        
    TRect rect( position, Size() );
    TPoint center = rect.Center();
    
    switch ( iTooltipPosition )
        {
        case EPositionTop:
            {
            iTooltip->SetPositionAndAlignment(
                TPoint( center.iX, rect.iTl.iY ), EHCenterVBottom );
            break;
            }
        case EPositionBottom:
            {
            iTooltip->SetPositionAndAlignment(
                TPoint( center.iX, rect.iBr.iY ), EHCenterVTop );
            break;
            }
        case EPositionLeft:
            {
            iTooltip->SetPositionAndAlignment(
                TPoint( rect.iTl.iX, center.iY ), EHRightVCenter );
            break;
            }
        case EPositionRight:
            {
            iTooltip->SetPositionAndAlignment(
                TPoint( rect.iBr.iX, center.iY ), EHLeftVCenter );
            break;
            }
        default:
            {
            return;
            }
        }
    iTooltip->ShowInfoPopupNote();        
    }
//  End of File
