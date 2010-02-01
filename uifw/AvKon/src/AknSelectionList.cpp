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
#include "aknselectionlist.h"
#include <aknsfld.h>
#include <eikfrlbd.h>
#include <eikclb.h>
#include <eikclbd.h>
#include <AknPanic.h>
#include <eikcapc.h>
#include <AknUtils.h>
#include <AknIconArray.h>
#include <aknappui.h>
#include <avkon.mbg>
#include "AknDebug.h"
#include "akntrace.h"

// LOCAL FUNCTION PROTOTYPES

// ==================== EXTENSION CLASS ====================
NONSHARABLE_CLASS(CAknSelectionListDialogExtension) : public CBase
    {
    public:        
        CAknSelectionListDialogExtension();
        ~CAknSelectionListDialogExtension();    

    public:
        CIdle *iIdle;
    };
   
// -----------------------------------------------------------------------------
// CAknSelectionListDialogExtension::CAknSelectionListDialogExtension()
// 
// Constructor
// -----------------------------------------------------------------------------
//  
CAknSelectionListDialogExtension::CAknSelectionListDialogExtension()
    {
    iIdle = NULL;
    }
    
// -----------------------------------------------------------------------------
// CAknSelectionListDialogExtension::~CAknSelectionListDialogExtension()
// 
// Destructor
// -----------------------------------------------------------------------------
// 
CAknSelectionListDialogExtension::~CAknSelectionListDialogExtension()
    {
    delete iIdle;
    }
    
// ==================== EXTENSION CLASS ====================
NONSHARABLE_CLASS(CAknMarkableListDialogExtension) : public CBase
    {
    public:        
        CAknMarkableListDialogExtension();
        ~CAknMarkableListDialogExtension();    

    public:
        CIdle *iIdle;
    };

// -----------------------------------------------------------------------------
// CAknMarkableListDialogExtension::CAknMarkableListDialogExtension()
// 
// Constructor
// -----------------------------------------------------------------------------
//  
CAknMarkableListDialogExtension::CAknMarkableListDialogExtension()
    {
    iIdle = NULL;
    }

// -----------------------------------------------------------------------------
// CAknMarkableListDialogExtension::~CAknMarkableListDialogExtension()
// 
// Destructor
// -----------------------------------------------------------------------------
// 
CAknMarkableListDialogExtension::~CAknMarkableListDialogExtension()
    {
    delete iIdle;
    }
    
// ==================== LOCAL FUNCTIONS ====================

class CFindControl : public CCoeControl 
    {
public:
    CAknSearchField *iFind;
    ~CFindControl() { delete iFind; }
    void Draw(const TRect &) const
    {
    // this removes flicker from CEikDialog's Draw().
    }
    void SizeChanged()
        {
        _AKNTRACE_FUNC_ENTER;
        TRect mainPane;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, mainPane );
        
        TAknLayoutRect listRect;
    
        listRect.LayoutRect( mainPane, AknLayout::list_gen_pane(0) );

        TRect r( listRect.Rect() );
        iPosition = TPoint( r.iTl );
        iSize.SetSize( r.Width(), r.Height() );
        _AKNTRACE( "[%s][%s] size: w = %d, h = %d.",
                "CFindControl", __FUNCTION__, iSize.iWidth, iSize.iHeight );
        _AKNTRACE_FUNC_EXIT;
        }

    TSize MinimumSize()
        {
        if ( iFind )
            {
            if ( iFind->Size() != TSize( 0, 0 ) )
                {
                return iFind->Size();
                }
            }
            
        return iSize;
        }
    };


// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//

EXPORT_C CAknSelectionListDialog* CAknSelectionListDialog::NewL(TInt &aValue, MDesCArray *aArray, TInt aMenuBarResourceId, MEikCommandObserver *aCommand)
    {
    _AKNTRACE( "[%s][%s] aValue = %d, aMenuBarResourceId = %d.",
            "CAknSelectionListDialog", __FUNCTION__, aValue, aMenuBarResourceId );
    CAknSelectionListDialog *dialog = NewLC(aValue, aArray, aMenuBarResourceId, aCommand);
    CleanupStack::Pop();
    return dialog;
    }

EXPORT_C CAknMarkableListDialog* CAknMarkableListDialog::NewL(TInt &aValue, CArrayFix<TInt> *aSelectedItems, MDesCArray *aArray, TInt aMenuBarResourceId, TInt aOkMenuBarId, MEikCommandObserver *aCommand)
    {
    _AKNTRACE( "[%s][%s] aValue = %d, aMenuBarResourceId = %d, aOkMenuBarId = %d.",
            "CAknMarkableListDialog", __FUNCTION__, aValue, aMenuBarResourceId, aOkMenuBarId );
    CAknMarkableListDialog *dialog = NewLC(aValue, aSelectedItems, aArray, aMenuBarResourceId, aOkMenuBarId, aCommand);
    CleanupStack::Pop();
    return dialog;
    }

EXPORT_C CAknSelectionListDialog *CAknSelectionListDialog::NewLC(TInt &aValue, MDesCArray *aArray, TInt aMenuBarResourceId, MEikCommandObserver *aCommand)
    {
    _AKNTRACE( "[%s][%s] aValue = %d, aMenuBarResourceId = %d.",
            "CAknSelectionListDialog", __FUNCTION__, aValue, aMenuBarResourceId );
    CAknSelectionListDialog *dialog = new(ELeave)CAknSelectionListDialog(aValue,aArray, aCommand);
    CleanupStack::PushL(dialog);
    dialog->ConstructL(aMenuBarResourceId); 
    return dialog;
    }

EXPORT_C CAknMarkableListDialog *CAknMarkableListDialog::NewLC(TInt &aValue, CArrayFix<TInt> *aSelectedItems, MDesCArray *aArray, TInt aMenuBarResourceId, TInt aOkMenuBarId, MEikCommandObserver *aCommand)
    {
    _AKNTRACE( "[%s][%s] aValue = %d, aMenuBarResourceId = %d, aOkMenuBarId = %d.",
            "CAknMarkableListDialog", __FUNCTION__, aValue, aMenuBarResourceId, aOkMenuBarId );
    CAknMarkableListDialog *dialog = new(ELeave)CAknMarkableListDialog(aValue,aSelectedItems, aArray, aMenuBarResourceId, aOkMenuBarId, aCommand);
    CleanupStack::PushL(dialog);
    dialog->ConstructL(aMenuBarResourceId);
    return dialog;
    }

// -----------------------------------------------------------------------------
//  CAknSelectionListDialog::ConstructL()
// 
// Constructs extension class
// -----------------------------------------------------------------------------
// 
EXPORT_C void CAknSelectionListDialog::ConstructL(TInt aMenuTitleResourceId)
    {
    _AKNTRACE( "[%s][%s] aMenuTitleResourceId = %d.",
            "CAknSelectionListDialog", __FUNCTION__, aMenuTitleResourceId );
    CAknDialog::ConstructL(aMenuTitleResourceId);
    iExtension = new (ELeave) CAknSelectionListDialogExtension;     
    }

// -----------------------------------------------------------------------------
//  CAknMarkableListDialog::ConstructL()
// 
// Constructs extension class
// -----------------------------------------------------------------------------
// 
EXPORT_C void CAknMarkableListDialog::ConstructL(TInt aMenuTitleResourceId)
    {
    _AKNTRACE( "[%s][%s] aMenuTitleResourceId = %d.",
            "CAknMarkableListDialog", __FUNCTION__, aMenuTitleResourceId );
    CAknDialog::ConstructL(aMenuTitleResourceId);
    iMarkableExtension = new (ELeave) CAknMarkableListDialogExtension;     
    }

EXPORT_C CAknSelectionListDialog::CAknSelectionListDialog(TInt &aIndex, MDesCArray *aArray, MEikCommandObserver *aCommand)
    : iEnterKeyPressed(EFalse),
      iSelectedItem(&aIndex),
      iArray(aArray),
      iCmdObserver(aCommand)
    {       
    }

EXPORT_C CAknMarkableListDialog::CAknMarkableListDialog(TInt &aIndex, CArrayFix<TInt> * aSelectedItems, MDesCArray *aArray, TInt aMenuBarResourceId, TInt aOkMenuBarResourceId, MEikCommandObserver *aCommand)
    : CAknSelectionListDialog(aIndex,aArray, aCommand),
      iSelectionIndexArray(aSelectedItems),
      iMenuBarResourceId(aMenuBarResourceId),
      iOkMenuBarResourceId(aOkMenuBarResourceId)
    {
    }
       
EXPORT_C CAknSelectionListDialog::~CAknSelectionListDialog()
    {
    if (iAvkonAppUi)
    iAvkonAppUi->RemoveFromStack( this );        
    delete iExtension;
    }

EXPORT_C CAknMarkableListDialog::~CAknMarkableListDialog()
    {
    delete iMarkableExtension;
    }

EXPORT_C CCoeControl* CAknSelectionListDialog::ComponentControl(TInt aIndex) const
    {
    if (aIndex == CAknDialog::CountComponentControls() )
    {
    return FindBox();
    }
    return CAknDialog::ComponentControl(aIndex);
    }

EXPORT_C TInt CAknSelectionListDialog::CountComponentControls() const
    {
    TInt newitems = 0;
    if (FindBox()) newitems++;
    return CAknDialog::CountComponentControls() + newitems;
    }

EXPORT_C TBool CAknSelectionListDialog::OkToExitL(TInt aButtonId)
    {
    TBool b = CAknDialog::OkToExitL(aButtonId);
    *iSelectedItem = ListBox()->CurrentItemIndex();
    if (FindBox())
    {
    if (*iSelectedItem != -1)
        *iSelectedItem = STATIC_CAST(CAknFilteredTextListBoxModel*,ListBox()->Model())->Filter()->FilteredItemIndex(*iSelectedItem);
    }
    _AKNTRACE( "[%s][%s] return value = %d.",
            "CAknSelectionListDialog", __FUNCTION__, b );
    return b;
    }

EXPORT_C void CAknSelectionListDialog::Draw(const TRect &) const
    {
    // this removes flicker from CEikDialog's Draw().
    }

EXPORT_C void CAknSelectionListDialog::ProcessCommandL(TInt aCommand)
    {
    _AKNTRACE( "[%s][%s] aCommand = %d.",
            "CAknSelectionListDialog", __FUNCTION__, aCommand );
    CAknDialog::ProcessCommandL(aCommand);
    if (FindBox() && iFindType == EPopupFind) 
        {
        AknFind::HandleFindPopupProcessCommandL(aCommand, ListBox(), FindBox(), this);
        DrawNow();
        }

    if (iCmdObserver) iCmdObserver->ProcessCommandL(aCommand);
    switch(aCommand)
    {
    case EAknCmdOpen:
        iEnterKeyPressed = ETrue;
        break;
    default:
        SelectionListProcessCommandL(aCommand);
        break;
    };
    }

EXPORT_C void CAknSelectionListDialog::SelectionListProcessCommandL(TInt aCommand)
    {
    _AKNTRACE( "[%s][%s] aCommand = %d.",
            "CAknSelectionListDialog", __FUNCTION__, aCommand );
    AknSelectionService::HandleSelectionListProcessCommandL(aCommand, ListBox());
    }

EXPORT_C void CAknSelectionListDialog::HandleListBoxEventL( CEikListBox* /*aListBox*/, TListBoxEvent aEventType )
    {
    _AKNTRACE( "[%s][%s] aEventType = %d.",
            "CAknSelectionListDialog", __FUNCTION__, aEventType );
    switch(aEventType)
        {
        case EEventItemDoubleClicked:
        case EEventItemSingleClicked:
            {
            if ( AknLayoutUtils::PenEnabled() )
                {
                delete iExtension->iIdle;
                iExtension->iIdle = NULL;
                iExtension->iIdle = CIdle::NewL(CActive::EPriorityIdle);
                if (iExtension->iIdle)
                    {                                  
                    iExtension->iIdle->Start(TCallBack(ExitViaIdle,this)); 
                    }
                }
            else
                {
                ProcessCommandL(EAknCmdOpen);
                // Should do nothing after this - the dialog might be deleted..
                }
            }
            break;
        case EEventEnterKeyPressed:
            {
            ProcessCommandL(EAknCmdOpen);
            // Should do nothing after this - the dialog might be deleted..
            }
            break;
        default:
            break;
        };
    }

// -----------------------------------------------------------------------------
// CAknSelectionListDialog::ExitViaIdle()
// 
// Callback function to exit dialog after selecting something with tapping it. 
// This prevents dialog to be destroyed before dialog page's handlepointereventl
// is fully completed.
// -----------------------------------------------------------------------------
// 
TInt CAknSelectionListDialog::ExitViaIdle(TAny* aSelectionList )
    {  
    _AKNTRACE( "[%s][%s] aSelectionList = 0x%x.",
            "CAknSelectionListDialog", __FUNCTION__, aSelectionList );
    CAknSelectionListDialog *selectionListDlg = (CAknSelectionListDialog*) aSelectionList; 
    TRAP_IGNORE(selectionListDlg->TryExitL(EAknSoftkeyOk));
    return EFalse;
    }  
 
EXPORT_C TKeyResponse CAknSelectionListDialog::OfferKeyEventL(const TKeyEvent& aKeyEvent,
                                  TEventCode aType)
    {
    _AKNTRACE( "[%s][%s] aKeyEvent(iCode = %d, iScanCode = %d, iModifiers = %d, iRepeats = %d) aType = %d.",
            "CAknSelectionListDialog", __FUNCTION__, aKeyEvent.iCode, aKeyEvent.iScanCode, aKeyEvent.iModifiers, aKeyEvent.iRepeats, aType );
    // must pass escape event to dialog - findbox and listbox "eat" escape events
    TKeyResponse res = EKeyWasNotConsumed;
    if ( aType == EEventKey && aKeyEvent.iCode == EKeyEscape )
        {
        res = CAknDialog::OfferKeyEventL(aKeyEvent, aType);
        }
        
    if ( res == EKeyWasConsumed ) 
        return res;

    TBool needRefresh = EFalse;
    res = AknFind::HandleFindOfferKeyEventL(aKeyEvent, aType, this, ListBox(), FindBox(), iFindType==EPopupFind, needRefresh);
    if (needRefresh && FindBox())
    {
    if (iFindType == EPopupFind)
        {
//      AknFind::HandlePopupFindSizeChanged(Control(EFindControl), ListBox(), FindBox());
        AknFind::HandlePopupFindSizeChanged(this, ListBox(), FindBox());
        }
    else if ( iFindType == EFixedFind || iFindType == EAdaptiveFind )
        {
//      AknFind::HandleFixedFindSizeChanged(Control(EFindControl),(CAknColumnListBox*)ListBox(), FindBox());
        AknFind::HandleFixedFindSizeChanged(this,(CAknColumnListBox*)ListBox(), FindBox());
        }
    DrawNow();
    }
    if ( res == EKeyWasConsumed ) 
    return res;
    // Give the events to listbox first! This is because otherwise all events do not go to the controls!
    // Dialogs filter out KeyUp/KeyDown events. If we do not do this, marking is broken; Sometimes it does
    // not mark list items correctly.
    if (aKeyEvent.iCode == EKeyLeftArrow || aKeyEvent.iCode == EKeyRightArrow)
    {
    // Multipage dialogs need the left/right keys
    res = CAknDialog::OfferKeyEventL(aKeyEvent, aType);
    }
    else
    res = ListBox()->OfferKeyEventL(aKeyEvent, aType);
    if ( res == EKeyWasNotConsumed )
    {
    res = CAknDialog::OfferKeyEventL(aKeyEvent, aType);
    }
    else 
    {
    }
    if (iEnterKeyPressed)
    TryExitL(EAknSoftkeyOk);
    // should do nothing after this.
    return res;
    }

EXPORT_C CEikListBox *CAknSelectionListDialog::ListBox() const
    {
    return (CEikListBox*)Control(ESelectionListControl);
    }

EXPORT_C CAknSearchField *CAknSelectionListDialog::FindBox() const
    {
    CFindControl *control = (CFindControl*)ControlOrNull(EFindControl);
    if (control) { return control->iFind; }
    return NULL;
    }

EXPORT_C void CAknSelectionListDialog::SetupFind(TFindType aType)
    {
    _AKNTRACE( "[%s][%s] aType = %d.",
            "CAknSelectionListDialog", __FUNCTION__, aType );
    iFindType = aType;
    }

EXPORT_C TBool CAknSelectionListDialog::IsAcceptableListBoxType(TInt /*aControlType*/, TBool &/*aIsFormattedCellListBox*/) const
    {
    return EFalse;
    }

EXPORT_C TBool CAknSelectionListDialog::IsFormattedCellListBox() const
    {
    CEikCaptionedControl *line = Line(ESelectionListControl);
    TInt controlType = line->iControlType;
    TBool result = EFalse;
    if (IsAcceptableListBoxType(controlType, result))
    return result;

    switch(controlType)
    {
    case EAknCtSingleListBox:
    case EAknCtSingleNumberListBox:
    case EAknCtSingleHeadingListBox:
    case EAknCtSingleGraphicListBox:
    case EAknCtSingleGraphicHeadingListBox:
    case EAknCtSingleNumberHeadingListBox:
    case EAknCtSingleLargeListBox:
        return EFalse;
    case EAknCtDoubleListBox:
    case EAknCtDoubleNumberListBox:
    case EAknCtDoubleTimeListBox:
    case EAknCtDoubleLargeListBox:
    case EAknCtDoubleGraphicListBox:
    case EAknCtSettingListBox:
    case EAknCtSettingNumberListBox:
        return ETrue;
    default:
        // If you hit this assert, you should derive from this dialog and
        // implement IsAcceptableListBoxType() method.
        __ASSERT_DEBUG(0, Panic(EAknPanicNotSupported));
        return ETrue;
    }
    }

EXPORT_C CArrayPtr<CGulIcon>* CAknSelectionListDialog::IconArray() const
    {
    if (IsFormattedCellListBox())
    {
    return ((CEikFormattedCellListBox*)ListBox())->ItemDrawer()->FormattedCellData()->IconArray();  
    }
    else
    {
    return ((CEikColumnListBox*)ListBox())->ItemDrawer()->ColumnData()->IconArray();
    }
    }

EXPORT_C void CAknSelectionListDialog::SetIconArrayL(CArrayPtr<CGulIcon>* aIcons)
    {
    CArrayPtr<CGulIcon>* oldicons = IconArray();
    if (oldicons)
        {
        oldicons->ResetAndDestroy();
        delete oldicons;
        }

    if (IsFormattedCellListBox())
    {
    ((CEikFormattedCellListBox*)ListBox())->ItemDrawer()->FormattedCellData()->SetIconArray(aIcons);    
    }
    else
    {
    ((CEikColumnListBox*)ListBox())->ItemDrawer()->ColumnData()->SetIconArray(aIcons);      
    }
    
    }

EXPORT_C SEikControlInfo CAknSelectionListDialog::CreateCustomControlL(TInt aControlType)
    {
    _AKNTRACE( "[%s][%s] aControlType = %d.",
            "CAknSelectionListDialog", __FUNCTION__, aControlType );
    CFindControl *control1= NULL;
    TBool findControl = EFalse;
    if (aControlType == EAknCtSelectionListFixedFind)
        {
        iFindType = EFixedFind;
        findControl = ETrue;
        }
    if (aControlType == EAknCtSelectionListPopupFind)
        {
        iFindType = EPopupFind;
        findControl = ETrue;
        }
    if (aControlType == EAknCtSelectionListAdaptiveFind)
        {
        iFindType = EAdaptiveFind;
        findControl = ETrue;
        }    
    if (findControl)
        {
        control1 = new (ELeave) CFindControl;
        }
    SEikControlInfo info;
    info.iControl = control1;
    info.iFlags = 0;
    info.iTrailerTextId = 0;
    return info;
    }

EXPORT_C void CAknSelectionListDialog::PreLayoutDynInitL()
    {    
    _AKNTRACE_FUNC_ENTER;
    CEikCaptionedControl *line = Line(ESelectionListControl);
    TInt controlType = line->iControlType;
    switch(controlType)
    {
    case EAknCtSingleNumberListBox:
    case EAknCtSingleGraphicListBox:
    break;
    default:
    // Only 2 different list layouts are available for fixed find.
    // => if other layouts are used, turn the find to popup find
    // automatically.
    if ( iFindType == EFixedFind || iFindType == EAdaptiveFind )
        {
        iFindType = EPopupFind;
        }
    };

    CFindControl *control1 = (CFindControl*)ControlOrNull(EFindControl);
    CAknSearchField *control = NULL;
    CAknSearchField::TSearchFieldStyle flags = CAknSearchField::EFixed;
    if (control1)
        {
        if (iFindType == EPopupFind)
            flags = CAknSearchField::EPopup;
        if (iFindType == EFixedFind)
            flags = CAknSearchField::EFixed;
        if (iFindType == EAdaptiveFind)
            flags = CAknSearchField::EAdaptive;
        control = CAknSearchField::NewL( *control1, flags, 0, 40 );
        control1->iFind = control;
        }
    
    CAknDialog::PreLayoutDynInitL();
    iAvkonAppUi->AddToStackL(this);
    
    CEikListBox *listbox = ListBox();
    CEikTextListBox *txtlistbox = (CEikTextListBox*)listbox;
    
    // Listbox items
    if (iArray)
    {
    txtlistbox -> Model() -> SetItemTextArray( iArray );
    txtlistbox -> Model() -> SetOwnershipType( ELbmDoesNotOwnItemArray );
    }
    
    // Scrollbar
    listbox->CreateScrollBarFrameL(ETrue);
    listbox->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto);
    
    // Listbox observer
    listbox->SetListBoxObserver(this);
    
    
    if (FindBox())
        {
        if (iFindType == EPopupFind)
            {
            STATIC_CAST(CAknFilteredTextListBoxModel*,ListBox()->Model())->CreateFilterL(ListBox(),FindBox());
            }
        else if ( iFindType == EFixedFind || iFindType == EAdaptiveFind )
            {
            // Fixed find is only available with list_single_graphic_pane
            __ASSERT_DEBUG(!IsFormattedCellListBox(), Panic(EAknPanicOutOfRange));
            STATIC_CAST(CAknFilteredTextListBoxModel*,ListBox()->Model())->CreateFilterL(ListBox(),FindBox());

            }
        } 
    _AKNTRACE_FUNC_EXIT;
    }


EXPORT_C void CAknSelectionListDialog::SetSizeAndPosition(const TSize &/*aSize*/)
    {
    TRect mainPane;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, mainPane );
    _AKNTRACE( "[%s][%s] mainPane(l = %d, t = %d, r = %d, b = %d).",
            "CAknSelectionListDialog", __FUNCTION__, mainPane.iTl.iX, mainPane.iTl.iY,\
            mainPane.iBr.iX, mainPane.iBr.iY );
    SetRect( mainPane );
    
    if (FindBox())
        {
        if (iFindType == EPopupFind)
            {
            TBool findPaneVisible = FindBox()->IsFocused();         
            FindBox()->MakeVisible( findPaneVisible );   
            AknFind::HandlePopupFindSizeChanged( this, ListBox(), FindBox() );
            }
        else if ( iFindType == EFixedFind || iFindType == EAdaptiveFind )
            {
            AknFind::HandleFixedFindSizeChanged( this,(CAknColumnListBox*)ListBox(), FindBox());    
            }
        }
    }

EXPORT_C void CAknSelectionListDialog::PostLayoutDynInitL()
    {
    _AKNTRACE_FUNC_ENTER;
    CAknDialog::PostLayoutDynInitL();
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CAknSelectionListDialog::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    _AKNTRACE( "[%s][%s] aPointerEvent(iType = %d, iModifiers = %d, iPosition(iX = %d, iY = %d), iParentPosition(iX = %d, iY = %d)).",
            "CAknSelectionListDialog", __FUNCTION__, aPointerEvent.iType, aPointerEvent.iModifiers, \
            aPointerEvent.iPosition.iX, aPointerEvent.iPosition.iY, aPointerEvent.iParentPosition.iX, aPointerEvent.iParentPosition.iY );
    CAknDialog::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CAknSelectionListDialog::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

EXPORT_C void CAknSelectionListDialog::CEikDialog_Reserved_1()
    {
    }

EXPORT_C void CAknMarkableListDialog::CEikDialog_Reserved_1()
    {
    }

EXPORT_C void CAknSelectionListDialog::CEikDialog_Reserved_2()
    {
    }

EXPORT_C void CAknMarkableListDialog::CEikDialog_Reserved_2()
    {
    }

EXPORT_C void CAknSelectionListDialog::CAknDialog_Reserved()
    {
    }

EXPORT_C void CAknMarkableListDialog::CAknDialog_Reserved()
    {
    }

EXPORT_C void CAknSelectionListDialog::CAknSelectionListDialog_Reserved()
    {
    }

EXPORT_C void CAknMarkableListDialog::CAknSelectionListDialog_Reserved()
    {
    }


EXPORT_C void CAknMarkableListDialog::HandleListBoxEventL( CEikListBox* aListBox, TListBoxEvent aEventType )
    {
    _AKNTRACE( "[%s][%s] aListBox = 0x%x, aEventType = %d.",
            "CAknMarkableListDialog", __FUNCTION__, aListBox, aEventType );
    if ( AknLayoutUtils::PenEnabled() )
        {
        switch(aEventType)
            {
            case EEventEnterKeyPressed:
                {
            /* Do nothing -- offerkeyevent handles this */
                }
                break;
            case EEventItemClicked:
                {    
                const CListBoxView::CSelectionIndexArray *selections = aListBox->SelectionIndexes();
                
                // if current item is only selected item and control or shift is not pressed same time, 
                // then select tapped index. 
                if ( aListBox->View()->ItemIsSelected( aListBox->View()->CurrentItemIndex() ) &&
                     selections->Count() == 1 && 
                     !((aListBox->EventModifiers() & EModifierCtrl) ||
                       (aListBox->EventModifiers() & EModifierShift)) )
                    {
                    // Close dialog via idle object. 
                    delete iMarkableExtension->iIdle;
                    iMarkableExtension->iIdle = NULL;
                    iMarkableExtension->iIdle = CIdle::NewL(CActive::EPriorityIdle);
                    if (iMarkableExtension->iIdle)
                        {                                  
                        iMarkableExtension->iIdle->Start(TCallBack(ExitViaIdle,this)); 
                        }
                    }
                }
            default:
                break;
            };
        }
    else
        {
        switch(aEventType)
            {
            case EEventEnterKeyPressed:
            case EEventItemDoubleClicked:
                {
                /* Do nothing -- offerkeyevent handles this */
                }
                break;
            default:
                break;
            }
        }
    }


EXPORT_C void CAknMarkableListDialog::SelectionListProcessCommandL(TInt aCommand)
    {
    _AKNTRACE( "[%s][%s] aCommand = %d.", "CAknMarkableListDialog", __FUNCTION__, aCommand );
    AknSelectionService::HandleMarkableListProcessCommandL( aCommand, ListBox() );
    }

EXPORT_C void CAknMarkableListDialog::ProcessCommandL(TInt aCommand)
    {
    _AKNTRACE( "[%s][%s] aCommand = %d.", "CAknMarkableListDialog", __FUNCTION__, aCommand );
    CAknSelectionListDialog::ProcessCommandL( aCommand );
    }

EXPORT_C TBool CAknMarkableListDialog::OkToExitL(TInt aButtonId)
    {
    TBool b = CAknSelectionListDialog::OkToExitL(aButtonId);
    if (iSelectionIndexArray)
    {
    const CArrayFix<TInt> *array = ListBox()->SelectionIndexes();
    if (FindBox())
        {
        STATIC_CAST(CAknFilteredTextListBoxModel*,ListBox()->Model())->Filter()->UpdateSelectionIndexesL();
        array = STATIC_CAST(CAknFilteredTextListBoxModel*,ListBox()->Model())->Filter()->SelectionIndexes();
        }
    TInt numberOfItems(array->Count());
    iSelectionIndexArray->Reset();
    for(TInt i(0); i<numberOfItems; i++)
        iSelectionIndexArray->AppendL(array->At(i));
    }
    _AKNTRACE( "[%s][%s] return value = %d.", "CAknMarkableListDialog", __FUNCTION__, b );
    return b;
    }


EXPORT_C void CAknMarkableListDialog::PreLayoutDynInitL()
    {
    _AKNTRACE_FUNC_ENTER;
    CAknSelectionListDialog::PreLayoutDynInitL();
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CAknMarkableListDialog::PostLayoutDynInitL()
    {
    _AKNTRACE_FUNC_ENTER;
    CAknSelectionListDialog::PostLayoutDynInitL();
    
// Check if we need default icons
    TBool iconsNeeded = EFalse;
    if ( IsFormattedCellListBox() )
        {
        CFormattedCellListBoxData *boxData = ((CEikFormattedCellListBox*)ListBox())->ItemDrawer()->FormattedCellData();
        if ( ! boxData->IconArray() ) iconsNeeded = ETrue;
        }
    else
        {
        CColumnListBoxData *boxData = ((CEikColumnListBox*)ListBox())->ItemDrawer()->ColumnData();
        if ( ! boxData->IconArray() ) iconsNeeded = ETrue;
        }

    // loading default bitmaps
    if ( iconsNeeded )
        {
        CArrayPtr<CGulIcon>* icons = new (ELeave) CAknIconArray(4);
        CleanupStack::PushL( icons );
        CGulIcon* icon = CGulIcon::NewLC();
        CFbsBitmap* bitmap;
        CFbsBitmap* mask;

        MAknsSkinInstance *skin = AknsUtils::SkinInstance();
        
        AknsUtils::CreateIconL( skin,
                                KAknsIIDQgnIndiMarkedAdd,
                                bitmap,
                                mask,
                                AknIconUtils::AvkonIconFileName(),
                                EMbmAvkonQgn_indi_marked_add,
                                EMbmAvkonQgn_indi_marked_add_mask );
            
        icon->SetBitmap( bitmap );
        icon->SetMask( mask );

        icons->AppendL(icon);
        CleanupStack::Pop(); // icon
 
        if ( IsFormattedCellListBox() )
            {
            CFormattedCellListBoxData *boxData = ((CEikFormattedCellListBox*)ListBox())->ItemDrawer()->FormattedCellData();
            boxData->SetIconArray( icons );
            }
        else
            {
            CColumnListBoxData *boxData = ((CEikColumnListBox*)ListBox())->ItemDrawer()->ColumnData();
            boxData->SetIconArray( icons );
            }
        CleanupStack::Pop(); // icons
        }

    CEikListBox *listbox = ListBox();
    // final listbox setup
    listbox -> ActivateL ();
    
    // Initial highlight position
    listbox -> SetCurrentItemIndex (0);

    _AKNTRACE_FUNC_EXIT;
    }    

EXPORT_C void CAknMarkableListDialog::DynInitMenuPaneL(TInt aResourceId, CEikMenuPane *aMenuPane)
    {
    _AKNTRACE( "[%s][%s] aResourceId = %d.", "CAknMarkableListDialog", __FUNCTION__, aResourceId );
    AknSelectionService::HandleMarkableListDynInitMenuPane(aResourceId, aMenuPane, ListBox());
    CAknSelectionListDialog::DynInitMenuPaneL(aResourceId, aMenuPane);
    }

EXPORT_C TKeyResponse CAknMarkableListDialog::OfferKeyEventL(const TKeyEvent& aKeyEvent,
                                  TEventCode aType)
    {
    _AKNTRACE( "[%s][%s] aKeyEvent(iCode = %d, iScanCode = %d, iModifiers = %d, iRepeats = %d) aType = %d.",
            "CAknMarkableListDialog", __FUNCTION__, aKeyEvent.iCode, aKeyEvent.iScanCode, aKeyEvent.iModifiers, aKeyEvent.iRepeats, aType );
    TKeyResponse retval = EKeyWasNotConsumed;

    TBool shiftKeyPressed = (aKeyEvent.iModifiers & EModifierShift);
    if (aKeyEvent.iCode == EKeyOK && aType == EEventKey 
    && !shiftKeyPressed && iOkMenuBarResourceId && ListBox()->SelectionIndexes()->Count() > 0)
    {
        iMenuBar->SetMenuTitleResourceId( iOkMenuBarResourceId );
        // This must be trapped so that menubar will be restored on leave
        TRAP_IGNORE(iMenuBar->TryDisplayMenuBarL( ) );
        iEikonEnv->EikAppUi( )->HandleStackChanged( );
        iMenuBar->SetMenuTitleResourceId( iMenuBarResourceId );
        retval = EKeyWasConsumed;   
    }
    else
    {
    retval = CAknSelectionListDialog::OfferKeyEventL(aKeyEvent, aType);
    }
    return retval;
    }

EXPORT_C void CAknMarkableListDialog::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    _AKNTRACE( "[%s][%s] aPointerEvent(iType = %d, iModifiers = %d, iPosition(iX = %d, iY = %d), iParentPosition(iX = %d, iY = %d)).",
            "CAknMarkableListDialog", __FUNCTION__, aPointerEvent.iType, aPointerEvent.iModifiers, \
            aPointerEvent.iPosition.iX, aPointerEvent.iPosition.iY, aPointerEvent.iParentPosition.iX, aPointerEvent.iParentPosition.iY );
    CAknSelectionListDialog::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CAknMarkableListDialog::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

//
// DEPRECATED METHODS, DO NOT USE THESE
// 
EXPORT_C CAknMarkableListDialog* CAknMarkableListDialog::NewL(TInt &aValue, CArrayFix<TInt> *aSelectedItems, MDesCArray *aArray, TInt aMenuBarResourceId, MEikCommandObserver *aCommand)
    {
#ifdef AVKON_RDEBUG_INFO
    RDebug::Print(_L("CAknMarkableListDialog::NewL is deprecated, please do not use it!"));
#endif
    CAknMarkableListDialog *dialog = NewLC(aValue, aSelectedItems, aArray, aMenuBarResourceId, NULL, aCommand);
    CleanupStack::Pop();
    return dialog;
    }

//
// DEPRECATED METHODS, DO NOT USE THESE
// 
EXPORT_C CAknMarkableListDialog *CAknMarkableListDialog::NewLC(TInt &aValue, CArrayFix<TInt> *aSelectedItems, MDesCArray *aArray, TInt aMenuBarResourceId, MEikCommandObserver *aCommand)
    {
#ifdef AVKON_RDEBUG_INFO
    RDebug::Print(_L("CAknMarkableListDialog::NewLC() is deprecated, please do not use it!"));
#endif
    CAknMarkableListDialog *dialog = new(ELeave)CAknMarkableListDialog(aValue,aSelectedItems, aArray, aMenuBarResourceId, NULL, aCommand);
    CleanupStack::PushL(dialog);
    dialog->ConstructL(aMenuBarResourceId);
    return dialog;
    }

//
// DEPRECATED METHODS, DO NOT USE THESE
// 
EXPORT_C CAknMarkableListDialog::CAknMarkableListDialog(TInt &aIndex, CArrayFix<TInt> * aSelectedItems, MDesCArray *aArray, MEikCommandObserver *aCommand)
    : CAknSelectionListDialog(aIndex,aArray, aCommand),
      iSelectionIndexArray(aSelectedItems),
      iMenuBarResourceId(NULL),
      iOkMenuBarResourceId(NULL)
    {
#ifdef AVKON_RDEBUG_INFO
    RDebug::Print(_L("CAknMarkableListDialog::CAknMarkableListDialog is deprecated, please do not use it!"));
#endif
    }

//  End of File  



