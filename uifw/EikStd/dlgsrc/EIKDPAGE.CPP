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


#include <barsread.h>
#include <coemain.h>
#include <eikenv.h>
#include <eikcapc.h>
#ifndef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <eikfctry.h>
#else
#include <eikfctry.h>
#include <uikon/eikctrlstatus.h>
#endif
#include <eikcapca.h>
#include <eikedwin.h>
#include <eikappui.h>
#include <eikdpage.h>
#include <eikdpsel.h>
#include <eikdialg.pan>
#include <eikform.pan>
#include <eikon.hrh>
#include <eikdialogext.h>
#include <eikseced.h>
#include <eikmfne.h>
#include <eikfpne.h> 
#include <avkon.hrh>
#include <avkon.rsg>
#include <AknUtils.h> 
#include <eikscrlb.h>
#include <AknsDrawUtils.h>
#include <AknsUtils.h>
#include <skinlayout.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include "EIKFANIM.H"

#include <touchfeedback.h>

#include <AknTasHook.h> // for testability hooks
#include "aknformphysics.h"
#include "aknrecordinggc.h"
#include <aknphysics.h>
#include <aknappui.h>
#include <AknPriv.hrh>

//
// Global constants.
//

const TInt KSpaceFromTitle=0 ; 
const TInt KSpaceFromBottom=0 ;
const TInt KPageArrayGranularity=4;
const TInt KLineArrayGranularity=4;

/*
 *  The following set of static functions return value which have been hard coded from the Series 60 Skins LAF v2.0
 *  If a layout DLL becomes available the hard-coded values may be replaced with equivalent Macros.
 *  NOTE THAT THESE ARE COPIES OF FUNCTIONS IN EIKCAPC.CPP
 */

LOCAL_D TRect EditFrameTopLeftRect( const TRect& aParentRect )
    {// Skins LAF table 5.24 Line 2
    TAknLayoutRect topLeft ;
    topLeft.LayoutRect( aParentRect, SkinLayout::Input_field_skin_placing__general__Line_2() ); 
    return topLeft.Rect() ;
    }

LOCAL_D TRect EditFrameBottomRightRect( const TRect& aParentRect )
    {// Skins LAF table 5.24 Line 5
    TAknWindowLineLayout l( SkinLayout::Input_field_skin_placing__general__Line_5() );
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( aParentRect, l );
    TRect rectInputField( layoutRect.Rect() );

    return rectInputField;
    }

NONSHARABLE_CLASS(CDialogPageExtension) : public CBase
    {
public:
    enum TFlags
        {
        ELineHandlerCalled
        };
    static CDialogPageExtension* NewL();
    ~CDialogPageExtension();

    void Feedback( CEikDialogPage* aControl, TTouchLogicalFeedback aFeedback ) const;
    /**
     * Produces vibra-only feedback. Event filtering by pointer event is used..
     */
    void SilentFeedback( CEikDialogPage* aDPage, 
                         TTouchLogicalFeedback aFeedback, 
                         const TPointerEvent& aPointerEvent ) const;
    
    void HandleFormFeedback( CEikDialogPage* aControl, const TPointerEvent& aPointerEvent, TInt aTouchedLineIndex, TInt aCurrentLine );

protected:  
    void ConstructL();
    
private:
    CDialogPageExtension();
    CDialogPageExtension(const CDialogPageExtension& aExtension);
    
public: 
    TInt iPopFieldEvents;    
    TBool iExternalScrollbar;
    TBool iIsDoubleQuery;
    TBool iFocusedClicked;
    TInt iPreviousThumbPosition;
    TBool iPreviousThumbDirection;
    MTouchFeedback* iFeedback;
    TBitFlags iFlags;
    /**
    * @c iDestroyedPtr is used for the object destruction check.
    * If it has non-null value, the destruction check is turned on, and
    * the value points to a local boolean variable that keeps the destroyed state.
    */
    TBool* iDestroyedPtr;
    
    TPoint iDragStartPosition;
    TPoint iLastPointerPos;
    TTime iStartTime;
    CAknRecordingGc* iRecordingGc;
    TBool iHandlingScrollEvent;
    CPeriodic* iHighlightTimer;
    TInt iLastTouchedLine;
    TPoint iSynchronizedPosition;
    TBool iScrolling;
    TBool iScrolled;
    TBool iInitialLayoutDone;
    TBool iHandlingResourceChange;
    TInt iCapturingItem;
    // record the center point Y value of current view when touch down an item
    TInt iOldCenterY;
    // top item in current view, -1 if item's Y is negative
    TInt iTopItem;
    // bottom item in current view, fields count when Y is larger than
    // the last item's Y
    TInt iBottomItem; 

    /**
     * Boolean used to check if application is single touch compatible.
     */
    TBool iUsesSingleClick;
    // It is used to distinguish if the focus item has changed.
    TBool iFocusItemChanged;
    };

CDialogPageExtension::CDialogPageExtension()
    {
    }

CDialogPageExtension* CDialogPageExtension::NewL()
    {
    CDialogPageExtension* extension = new (ELeave) CDialogPageExtension();
    CleanupStack::PushL(extension);
    extension->ConstructL();
    CleanupStack::Pop(extension); //extension
    
    return extension;
    }

CDialogPageExtension::~CDialogPageExtension()
    {
    delete iHighlightTimer;
    delete iRecordingGc;
    
    if( iDestroyedPtr )
        {
        // Mark the object as destroyed.
        *iDestroyedPtr = ETrue;
        iDestroyedPtr = NULL;
        }
    }
    
CDialogPageExtension::CDialogPageExtension(const CDialogPageExtension& /*aExtension*/)
    {
    }

void CDialogPageExtension::ConstructL()
    {
    iFeedback = MTouchFeedback::Instance();
    iHighlightTimer = CPeriodic::NewL( CActive::EPriorityStandard );
    iCapturingItem = KErrNotFound;
    }

void CDialogPageExtension::HandleFormFeedback(
    CEikDialogPage* aDPage,
    const TPointerEvent& aPointerEvent,
    TInt aTouchedLineIndex,
    TInt aCurrentLine )
    {
    // note, that iFormControl is checked in Feedback()
    if ( aPointerEvent.iType == TPointerEvent::EButton1Down &&
        aCurrentLine != aTouchedLineIndex && aDPage->LineOnPageOrNull( 0 ) ) 
        {
        // feedback for edit/view mode form, when non-focused line is clicked
        // feedback for focused item is responsibility of the item
        // no feedback with focus change when single click is enabled
        if ( !iUsesSingleClick )
            {
            Feedback( aDPage, ETouchFeedbackSensitiveItem );
            }
        iFocusItemChanged = ETrue;
        }

    else if ( aPointerEvent.iType == TPointerEvent::EButton1Down &&
        aTouchedLineIndex == aCurrentLine && aDPage->LineOnPageOrNull( 0 ) )
        {
        // Feedback for view mode form, when focused item is
        // clicked. Basically same case as for msk simulation later on
        // the function, but on pointer
        // down. iExtension->iFocusedClicked is not valid here, since
        // it can't be known in this phase whether user drags pointer
        // away.
        Feedback( aDPage, ETouchFeedbackBasicItem );
        iFocusItemChanged = EFalse;
        }

    else if ( aPointerEvent.iType == TPointerEvent::EButton1Up &&
            aDPage->LineOnPageOrNull( 0 ) )
        {// when focus changed, it should not send feedback on up event.
        //when up event comes, aTouchedLineIndex always equal to aCurrentLine
        if ( !iFocusItemChanged )
            {
            SilentFeedback( aDPage, ETouchFeedbackBasicItem, aPointerEvent );
            }
        }
    }

void CDialogPageExtension::Feedback( CEikDialogPage* aDPage, 
                                     TTouchLogicalFeedback aFeedback ) const
    {
    if ( aDPage
        && aDPage->IsForm()
        && iFeedback
        && !aDPage->IsDimmed()
        && aDPage->IsVisible() )
        {
        iFeedback->InstantFeedback( aFeedback );
        }
    }

void CDialogPageExtension::SilentFeedback( CEikDialogPage* aDPage, 
                                           TTouchLogicalFeedback aFeedback, 
                                           const TPointerEvent& aPointerEvent ) const
    {
    if ( aDPage
        && aDPage->IsForm()
        && iFeedback
        && !aDPage->IsDimmed()
        && aDPage->IsVisible() )
        {
        iFeedback->InstantFeedback( aDPage, aFeedback, ETouchFeedbackVibra, aPointerEvent );
        }
    }

class CAknPaneScroll : public CBase
{
public:
    enum TScrollChangeType
        {
        ENoChange = 0,
        ETopChanged = 1,
        EBottomChanged = 2,
        ESizeChanged = 4,
        EFocusChanged = 8
        };
    CAknPaneScroll(CCoeControl* /*ctrl*/) : iTop(0), iMiddle(-1), iBottom(-1) { }
    void SetLines(CEikCapCArray *aLines) { iLines = aLines; }
    void SetOutsideRect(TRect aRect); // this is list_form_gen_pane
    TScrollChangeType ExposeLine(TInt aLine, TBool aShowWholeLine=ETrue);
    TInt Top() const {return iTop; }
    TInt Middle() const {return iMiddle; }
    TInt Bottom() const {return iBottom; }
private:
    TRect iOutsideRect;
    CEikCapCArray *iLines;
    TInt iTop, iMiddle, iBottom;
    TInt iOldTop, iOldMiddle, iOldBottom;
    TInt iOldFocus;
};

CAknPaneScroll::TScrollChangeType CAknPaneScroll::ExposeLine(TInt aLine, TBool /*aShowWholeLine*/)
{
    if (aLine < 0 || aLine >= iLines->Count()) return ENoChange;
    
    TInt top = iTop;
    TInt middle = iMiddle;
    TInt bottom = iBottom;
    
    TBool switchDir = iLines->CalcItemIndexes(top, middle, bottom, iOutsideRect.Size());

    if (switchDir && iTop == -1) { iTop = top; iMiddle = -1; iBottom = -1; }
    if (switchDir && iBottom == -1) { iTop = -1; iMiddle = -1; iBottom = bottom; }
    if (aLine < top) { iTop = aLine; iMiddle = -1; iBottom=-1; }
    else if (aLine >= iLines->Count() - bottom) { iBottom = iLines->Count() - 1 - aLine; iMiddle = -1; iTop=-1; }

    TScrollChangeType change = ENoChange;
    if (iOldTop != top) { change = TScrollChangeType(change | ETopChanged); }
    if (iOldBottom != bottom) { change = TScrollChangeType(change | EBottomChanged); }
    if (iOldMiddle != middle) { change = TScrollChangeType(change | ESizeChanged); }
    if (iOldFocus != aLine) {change = TScrollChangeType(change | EFocusChanged); }

    iOldTop = top;
    iOldMiddle = middle;
    iOldBottom = bottom;
    iOldFocus = aLine;
    return change;
}

void CAknPaneScroll::SetOutsideRect(TRect aRect) { iOutsideRect = aRect; }

//
// CEikDialogPage.
//

CEikDialogPage::~CEikDialogPage()
    {
    AKNTASHOOK_REMOVE();
    // Page observer needs to be nulled or an already deleted instance is
    // called when pointer up event is handled. This is valid only for dialogs
    // that have embedded virtual inputs.
    iPageObserver = NULL;
    delete iPhysics;
    delete iLines;
    delete iScroll;    
    delete iExtension;
    }

CEikDialogPage* CEikDialogPage::NewL(TInt aPageId,RWindow& aViewWin,CEikScrollBarFrame& aSBFrame,const CEikDialogPageContainer& aParent,MEikDialogPageObserver* aPageObserver)
    {
    CEikDialogPage* self=CEikDialogPage::NewLC(aPageId,aViewWin,aSBFrame,aParent,aPageObserver);
    CleanupStack::Pop();
    return self;
    }

void CEikDialogPage::CommonConstructCodeBetweenNewL(CEikDialogPage& aDialogPage, const CEikDialogPageContainer& aParent)
    {
/* 
Added the next line as normal window heirarchy does not hold for dialogs, so the 
container window mechanism cannot be used to find the menu / CBA, which is used
in the MOP system for scrollers.
*/
    aDialogPage.SetPageContainer(&aParent);
    aDialogPage.ConstructL();
    aDialogPage.CopyControlContextFrom(&aParent);
    };

CEikDialogPage* CEikDialogPage::NewLC(TInt aPageId,RWindow& aViewWin,CEikScrollBarFrame& aSBFrame,const CEikDialogPageContainer& aParent,MEikDialogPageObserver* aPageObserver)
    {
    CEikDialogPage* self=new(ELeave) CEikDialogPage(aPageId,aViewWin,aSBFrame,aPageObserver);
    CleanupStack::PushL(self);
    CommonConstructCodeBetweenNewL(*self,aParent); 
    AKNTASHOOK_ADDL( self, "CEikDialogPage" );
    return self;
    }

CEikDialogPage* CEikDialogPage::NewL(TInt aPageId,RWindow& aViewWin,CEikScrollBarFrame& aSBFrame,const CEikDialogPageContainer& aParent,MEikDialogPageObserver* aPageObserver,TResourceReader& aReader)
    {
    CEikDialogPage* self=CEikDialogPage::NewLC(aPageId,aViewWin,aSBFrame,aParent,aPageObserver,aReader);
    CleanupStack::Pop();
    return self;
    }

CEikDialogPage* CEikDialogPage::NewLC(TInt aPageId,RWindow& aViewWin,CEikScrollBarFrame& aSBFrame,const CEikDialogPageContainer& aParent,MEikDialogPageObserver* aPageObserver,TResourceReader& aReader)
    {
    CEikDialogPage* self=new(ELeave) CEikDialogPage(aPageId,aViewWin,aSBFrame,aPageObserver);
    CleanupStack::PushL(self);
    CommonConstructCodeBetweenNewL(*self,aParent);
    self->ConstructFromResourceL(aReader);
    AKNTASHOOK_ADDL( self, "CEikDialogPage" );
    return self;
    }

CEikDialogPage::CEikDialogPage(TInt aPageId,RWindow& /*aViewWin*/,
    CEikScrollBarFrame& /*aSBFrame*/,MEikDialogPageObserver* aPageObserver)
    : iPageObserver(aPageObserver),
        iPageId(aPageId),iCurrentLine(-1)
    {
    SetBlank();
    SetComponentsToInheritVisibility();
    }

void CEikDialogPage::ConstructL()
    {
    iLines=new(ELeave)CEikCapCArray(KLineArrayGranularity);
    SetContainerWindowL( *iPageContainer );
    Window().SetPointerGrab(ETrue); 
    Window().SetShadowDisabled(ETrue);
    Window().SetBackgroundColor(iEikonEnv->ControlColor(EColorDialogBackground,*this));
    iScroll = new(ELeave)CAknPaneScroll(this);
    iScroll->SetLines(iLines);
    iExtension = CDialogPageExtension::NewL();
    }

void CEikDialogPage::ConstructFromResourceL(TResourceReader& aReader, TBool aFormControl )
    {
    iFormControl = aFormControl ;

    if ( IsForm() )
        {
        if ( iAvkonAppUi )
            {
            iExtension->iUsesSingleClick = 
                iAvkonAppUi->IsSingleClickCompatible();
            }
        
        iPhysics = CAknFormPhysics::NewL( *this, *iExtension->iRecordingGc );
        iExtension->iRecordingGc = new ( ELeave ) CAknRecordingGc( &SystemGc() );
        }
        
    const TInt lineCount=aReader.ReadInt16();
    if (lineCount==EEikDlgMainPageIndirect)
        {
        TInt indirectRid=aReader.ReadInt32();
        if (!indirectRid)
            return;
        TResourceReader indirectReader;
        iCoeEnv->CreateResourceReaderLC(indirectReader,indirectRid);
        ConstructFromResourceL(indirectReader);
        CleanupStack::PopAndDestroy();
        return;
        }

    // This section modified to handle FORM structure (which contains DIALOG_LINE structs )
    // There might be lines on the page already
    for (TInt ii=0;ii<lineCount;ii++)
        {
        CEikCaptionedControl* thisLine=ConstructLineL(aReader); 
/* 
Second argument used to be used to set previous line.  This has been moved into a 
AfterAddingNewLinesL, in an attempt to group code which has to be executed together
*/
        CleanupStack::PushL(thisLine);

        iLines->AppendL(thisLine);
        CleanupStack::Pop(); // thisLine
        thisLine->iIsFormControl = aFormControl ;
        if ( aFormControl )
            {
            thisLine->GetAknLayoutValuesL() ;   // should cause the control to have size.
            if ( iFormFlags )
            thisLine->SetFormFlags( iFormFlags ) ;
            }       
// allow the caption to know the one above itself
        AfterAddingNewLinesL(iLines->LineIndexFromId(thisLine->iId));
        }

    SetDensePacking( !iFormControl ) ;
    if (!iScroll)
        {
        iScroll = new(ELeave)CAknPaneScroll(this);
        }
    iScroll->SetLines(iLines);
    }

void CEikDialogPage::ConstructFormFromResourceL( TResourceReader& aReader ) 
    {
    iFormFlags = TInt16(aReader.ReadInt16()) ;
    iFormLayout = (iFormFlags&EEikFormUseDoubleSpacedFormat) ? EDouble : ESingle;
    ConstructFromResourceL( aReader, ETrue ) ;
    }

CCoeControl* CEikDialogPage::CreateLineByTypeL(const TDesC& aCaption,TInt aLineId,TInt aControlType,TAny* aReturnValue)
    {
    ShowFocus( EFalse, EFalse ) ;  // Turn the focus off the current line.  
    CEikCaptionedControl* line=new(ELeave) CEikCaptionedControl;
    CleanupStack::PushL(line);
    line->SetComponentsToInheritVisibility();
    // Try to insert line above the currently selected line.  If no line is currently selected then append (TimW 22/5/00)
    // INSERTION SHOULD BE BELOW!

    TInt oldLine = iCurrentLine;
    
    if ( (iCurrentLine != -1) && (iCurrentLine < iLines->Count()) )
        {
        iLines->InsertL( iCurrentLine+1, line ) ;
        ++iCurrentLine;
        }
    else
        {
        iLines->AppendL( line ) ;
        iCurrentLine = iLines->Count() - 1 ;
        }
// used to update CaptionedControlAfter field upon adding new lines.
    CleanupStack::Pop(); // "line" is now owned by iLines.
    ConstructByTypeL(aControlType,line,this); // line owns control, dialog owns line - no need for cleanup stack.
    line->SetCaptionL(aCaption);

    line->iId=aLineId;
    __ASSERT_DEBUG(line->IsNonFocusing() || aLineId!=0, Panic(EEikDialogPanicFocusableLineWithIdZero));
    line->iReturnValue=aReturnValue;
    AfterAddingNewLinesL(iCurrentLine); 
    TInt targetLine = iCurrentLine;
    iCurrentLine = oldLine;

    ChangeFocusTo( targetLine );

    // physics engine needs to be updated when lines are added after the initial layout
    UpdatePhysics();

    return line->iControl;
    }

CEikCaptionedControl* CEikDialogPage::ConstructLineL(TInt aResourceId)
    {
    TResourceReader resourceReader;
    iCoeEnv->CreateResourceReaderLC(resourceReader,aResourceId);
    CEikCaptionedControl* line=ConstructLineL(resourceReader);
    CleanupStack::PopAndDestroy(); // resourceReader
    return line;
    }

CEikCaptionedControl* CEikDialogPage::ConstructLineL(TResourceReader& aReader)
    {
    CEikCaptionedControl* line=new(ELeave) CEikCaptionedControl;
    CleanupStack::PushL(line);
    line->iIsFormControl=iFormControl; 
    line->SetComponentsToInheritVisibility();
    TInt controlType=aReader.ReadInt16();
    TResourceReader* reader=(&aReader);
    TInt indirectRid=0;
    if (controlType==EEikDlgItemIndirect)
        {
        indirectRid=aReader.ReadInt32();
        TResourceReader indirectReader;
        iCoeEnv->CreateResourceReaderLC(indirectReader,indirectRid);
        controlType=indirectReader.ReadInt16();
        reader=(&indirectReader);
        }

    ConstructByTypeL(controlType,line,this);
    line->ConstructFromResourceL(*reader);
    if (indirectRid)
        CleanupStack::PopAndDestroy();
    CleanupStack::Pop(); // line
    return line;
    }

void CEikDialogPage::ConstructByTypeL(TInt aType,CEikCaptionedControl* aLine,CCoeControl* aContainer)
    {
    SEikControlInfo controlInfo=EikControlFactory::CreateByTypeL(aType);
    if (!controlInfo.iControl)
        controlInfo=CreateCustomControlL(aType);
    aLine->iIsFormControl=iFormControl; 
    aLine->iControl=controlInfo.iControl;
    aLine->iControlType=aType;
    aLine->SetContainerWindowL(*aContainer);
    aLine->CopyControlContextFrom(aContainer);
    aLine->SetObserver(this);
    controlInfo.iControl->SetContainerWindowL(*aContainer);
    controlInfo.iControl->SetObserver(this);

    // Skins requires the routine of object provider through the captioned control
    if (iFormControl)
        controlInfo.iControl->SetMopParent(aLine);

    controlInfo.iControl->CopyControlContextFrom(aContainer);

    if (controlInfo.iFlags&EEikControlHasEars)
        aLine->SetUsesEars();
    if (controlInfo.iFlags&EEikControlIsNonFocusing)
        {
        aLine->SetNonFocusing();
        controlInfo.iControl->SetNonFocusing();
        }
    if (controlInfo.iFlags&EEikControlHasExtraAscent)
        aLine->SetExtraAscent();
    if (controlInfo.iTrailerTextId)
        {
        HBufC* tmp=iCoeEnv->AllocReadResourceLC(controlInfo.iTrailerTextId);
        aLine->SetTrailerL(tmp->Des());
        CleanupStack::PopAndDestroy(); // tmp
        }
    }

SEikControlInfo CEikDialogPage::CreateCustomControlL(TInt aControlType)
    {
    ASSERT(iPageObserver);
    return iPageObserver->CreateCustomControlL(aControlType);
    }

void CEikDialogPage::SetActiveL()
    {
    ActivateL();
    MakeVisible(ETrue);        
    
    if(AknLayoutUtils::PenEnabled())
    {
    if (iFormControl && iPageContainer->ScrollBar())
        {        
        iPageContainer->ScrollBar()->SetScrollBarFrameObserver(this);
        }
    }

    UpdateScrollBarL();
    MakeEdwinScrollbarsVisibleL(ETrue);

    const TInt numLines=iLines->Count();
    for (TInt ii=0;ii<numLines;ii++)
        {
        CEikCaptionedControl* line=(*iLines)[ii];
        if (line->IsLatent())
            line->MakeVisible(EFalse);

        else if ( IsForm() )
            line->ActivateL() ;
        }
    AknsUtils::RegisterControlPosition( this ) ;
    TInt count = iLines->Count();
    for (TInt i = 0; i<count; i++)
        {
        CEikCaptionedControl *capCtrl = (*iLines)[i];
        AknsUtils::RegisterControlPosition(capCtrl);
        AknsUtils::RegisterControlPosition(capCtrl->iCaption);
        AknsUtils::RegisterControlPosition(capCtrl->iControl);
        AknsUtils::RegisterControlPosition(capCtrl->iTrailer);
        AknsUtils::RegisterControlPosition(capCtrl->iBitmap);

    if ( capCtrl->iIsFormControl && iCurrentLine != i)
        {

        if (capCtrl->ControlIsAnEdwin(capCtrl->iControlType))
            {
            CEikEdwin *edwin = (CEikEdwin*)capCtrl->iControl;
            TRAP_IGNORE(edwin->TextView()->SetDocPosL(0)
                );
            }
       }

        }
    }

void CEikDialogPage::SetActiveAndFocusL()
    {
    SetActiveL();
    SetEditableL(iIsEditable, ETrue);
    //When active a page, need to show the focus in that page.
    ShowFocus( ETrue, EFalse ) ;
    // Display the focus on the current line 
    if ( iCurrentLine == -1 || IsForm() )
        {
        SetInitialFocus() ;
        }
    
    ExposeLine( iCurrentLine, EFalse );
    UpdateScrollBarL();
    }

void CEikDialogPage::SetInactiveL()
    {
    MakeEdwinScrollbarsVisibleL(EFalse);
    MakeVisible(EFalse);
    }

void CEikDialogPage::MakeEdwinScrollbarsVisibleL(TBool aVisible)
    {
    const TInt numLines=iLines->Count();
    for (TInt ii=0;ii<numLines;ii++)
        {
        CEikCaptionedControl* thisLine=(*iLines)[ii];
        const TInt controlType(thisLine->iControlType);
        if (thisLine->ControlIsAnEdwin(controlType))
            {
            CEikEdwin* edwin=(CEikEdwin*)thisLine->iControl;
            if(edwin->Text())
                edwin->ForceScrollBarUpdateL();
            CEikScrollBarFrame* frame=edwin->ScrollBarFrame();
            if (frame)
                {
                TInt count=frame->CountComponentControls();
                for (TInt jj=0;jj<count;jj++)
                    frame->ComponentControl(jj)->MakeVisible(aVisible);
                }
            }
        }
    }

TInt CEikDialogPage::PageId() const
    {
    return iPageId;
    }

TInt CEikDialogPage::LineId(const CCoeControl& aControl) const
    {
    TInt lineIndex=iLines->FindLineIndex(&aControl);
    if (lineIndex>=0)
        return (*iLines)[lineIndex]->iId;

    return KErrNotFound;
    }

TBool CEikDialogPage::SetInitialFocus()
    {
    TBool focusSet=EFalse;

    const TInt numLines=iLines->Count();
    for (TInt ii=0;ii<numLines;ii++)
        {
        CEikCaptionedControl* line=(*iLines)[ii];
        if (line->IsNonFocusing() || line->IsDimmed() || !(line->IsVisible()))
            continue;
        ChangeFocusTo(ii);
        focusSet=ETrue;
        
        if ( IsForm() )
            {
            // move line with initial focus to the screen
    		iLines->MoveLineToScreen( ii, iPhysics->ViewTopY(), ETrue );
            }
        break;
        }

    return focusSet;
    }

TKeyResponse CEikDialogPage::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    TKeyResponse response=EKeyWasNotConsumed;

    if (!(PageContainer()->PageSelector()->Dialg()->DialogFlags() & EEikDialogFlagDontEatUpDownEvents))
        {
        if (aType != EEventKey)
        return response;
        }

    const TInt numLines=iLines->Count();
    if ((iCurrentLine>-1)&&(iCurrentLine<numLines))
        {
        // If the control changes size as a result of offering it the key event then it will be
        // necessary to reformat the page
        if ((aKeyEvent.iCode != EKeyTab && aKeyEvent.iCode != EKeyPrevious && aKeyEvent.iCode != EKeyNext) || (*iLines)[iCurrentLine]->ControlIsAPopfield((*iLines)[iCurrentLine]->iControlType) ) // tab keys are not offered to child controls
            {
            response=(*iLines)[iCurrentLine]->OfferKeyEventL(aKeyEvent,aType);
            }
        iExtension->iFocusedClicked = EFalse;
        }
    if (aType == EEventKey && response==EKeyWasConsumed)
        ReportEventL(MCoeControlObserver::EEventStateChanged);
    else if (aType == EEventKey && (
            aKeyEvent.iCode==EKeyUpArrow 
            || aKeyEvent.iCode==EKeyDownArrow 
            || aKeyEvent.iCode==EKeyTab
            || aKeyEvent.iCode==EKeyNext
            || aKeyEvent.iCode==EKeyPrevious
            ))
        response=OfferUpDownKeyEventL(aKeyEvent,aType,ENonCyclic);
    return response;
    }

TKeyResponse CEikDialogPage::OfferUpDownKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType,TFocusNavigationMode aFocusNavigationMode)
    {
    TKeyResponse response=EKeyWasNotConsumed;
    if (aType==EEventKey)
        {
        const TInt numLines=iLines->Count();
        if ((iCurrentLine>-1)&&(iCurrentLine<numLines))
            { 
            if (!iFormControl || (*iLines)[iCurrentLine]->iIsEditable  ) // non form controls should not have editable concept
                {
                // 1. Tab events are never forwarded.
                // 2. If it's a non-form dialog, then it is forwarded.
                // 3. If it's a form dialog, then it is forwarded if it's not 
                //    next/previous nor line is a popup field.
                if ( aKeyEvent.iCode != EKeyTab && 
                     ( !iFormControl ||
                       ( aKeyEvent.iCode != EKeyPrevious && aKeyEvent.iCode != EKeyNext ) || 
                       ( *iLines)[iCurrentLine]->ControlIsAPopfield((*iLines)[iCurrentLine]->iControlType ) ) )
                    {
                    response=(*iLines)[iCurrentLine]->OfferKeyEventL(aKeyEvent,aType);
                    }
                }
            else
                response=EKeyWasNotConsumed ;
            }
        if (response!=EKeyWasConsumed && 
            (aKeyEvent.iCode==EKeyUpArrow 
            || aKeyEvent.iCode==EKeyDownArrow 
            || aKeyEvent.iCode==EKeyTab
            || aKeyEvent.iCode==EKeyNext
            || aKeyEvent.iCode==EKeyPrevious
            ))
            {
            iExtension->iFocusedClicked = ETrue;
            
            switch (aFocusNavigationMode)
                {
                case ECyclic:
                    iExtension->iScrolled = ETrue;                    
                    response=HandleCyclicFocusNavigationKeyL(aKeyEvent);
                    break;
                    
                case ENonCyclic:
                    iExtension->iScrolled = ETrue;                    
                    response=HandleNonCyclicFocusNavigationKeyL(aKeyEvent);
                    break;
                    
                default:
                    break;
                };

            if (response==EKeyWasConsumed)
                ReportEventL(MCoeControlObserver::EEventStateChanged);
            }
        }

    if (response==EKeyWasConsumed)
        UpdateScrollBarThumb();

    return response;
    }

TKeyResponse CEikDialogPage::HandleNonCyclicFocusNavigationKeyL(const TKeyEvent& aKeyEvent)
    {
    TKeyResponse response=EKeyWasNotConsumed;
    TBool up = EFalse;
    TBool down = EFalse;
    TBool tab = EFalse;
    TInt naviCount = 1;
    switch (aKeyEvent.iCode)
        {
        case EKeyPrevious:
            naviCount = aKeyEvent.iRepeats + 1;
        case EKeyUpArrow:
            up = ETrue;
            break;
        case EKeyNext:
            naviCount = aKeyEvent.iRepeats + 1;
        case EKeyDownArrow:
            down = ETrue;
            break;
        case EKeyTab:
            tab = ETrue;
            if (aKeyEvent.iModifiers & EModifierShift)
                {
                up = ETrue;
                }
            else
                {
                down = ETrue;
                }
            break;
        default:
            ASSERT(EFalse);
        };
    
    if (up)
        {
        if (iCurrentLine!=TopFocusableLine()||(iExtension->iIsDoubleQuery&&tab))
           {
           if (RotateFocusByL(-1*naviCount))
               response=EKeyWasConsumed;
           }
        }
    if (down)
        {
        if (iCurrentLine!=BottomFocusableLine()||(iExtension->iIsDoubleQuery&&tab))
            {
            if (RotateFocusByL(+1*naviCount))
                response=EKeyWasConsumed;
            }
        else if (aKeyEvent.iRepeats>0)
            {
            response=EKeyWasConsumed;
            }

        }

    return response;
    }

TKeyResponse CEikDialogPage::HandleCyclicFocusNavigationKeyL(const TKeyEvent& aKeyEvent)
    {
    TKeyResponse response=EKeyWasNotConsumed;

    switch (aKeyEvent.iCode)
        {
        case EKeyUpArrow:
            if (!(iCurrentLine==TopFocusableLine() && aKeyEvent.iRepeats>0)) // Check not reached top from a repeated key event.
                {
                if (RotateFocusByL(-1))
                    response=EKeyWasConsumed;
                }
            break;
        case EKeyDownArrow:
            if (!(iCurrentLine==BottomFocusableLine() && aKeyEvent.iRepeats>0)) // Check not reached bottom from a repeated key event.
                {
                if (RotateFocusByL(+1))
                    response=EKeyWasConsumed;
                }
            break;
        default:
            ASSERT(EFalse);
        }

    return response;
    }

TBool CEikDialogPage::OwnsLine(TInt aLineId) const
    {
    TBool ownsLine=EFalse;

    const TInt numLines=iLines->Count();
    for (TInt ii=0;ii<numLines;ii++)
        {
        if ((*iLines)[ii]->iId==aLineId)
            {
            ownsLine=ETrue;
            break;
            }
        }

    return ownsLine;
    }

void CEikDialogPage::SetDimmed(TBool aDimmed)
    {
    CCoeControl::SetDimmed(aDimmed);

    const TInt numLines=iLines->Count();
    for (TInt ii=0;ii<numLines;ii++)
        {
        CEikCaptionedControl* thisLine=(*iLines)[ii];
        thisLine->iControl->SetDimmed(aDimmed);
        thisLine->CheckDimmedDisplayState();
        }
    }

TBool CEikDialogPage::RotateFocusByL(TInt aDelta)
    {
    TInt numLines=iLines->Count();
    if (numLines == 0)
        return(EFalse);
    
    // If form is in view mode and highlight is hidden then the first
    // navigation key press just displays the highlight.
    if ( IsForm() && !IsEditable() && !HighlightVisible() )
        {
        HighlightVisible( ETrue );
        
        TInt lineIndex = iLines->FocusableLine( iCurrentLine,
                iPhysics->ViewTopY() );
        
        if ( lineIndex != KErrNotFound )
            {
            if ( lineIndex == iCurrentLine )
                {
                CEikCaptionedControl* line = (*iLines)[iCurrentLine];
                ShowFocus( ETrue, ETrue );
                }
            else
                {
                iExtension->iLastTouchedLine = lineIndex;
                HandleHighlightTimer();
                }
            }
        
        return ETrue;
        }
    
    TInt max=numLines-1;
    TInt currentLine=iCurrentLine;
    while (numLines--)
        {
        currentLine+=aDelta;


        if (currentLine<0)
            currentLine=0;
        else if (currentLine>max)
            currentLine=max;

        (*iLines)[currentLine]->ActivateL() ;  // ensure that the current line is activated.

        if (!(LineIsFocusable(currentLine)))
            continue;

        PrepareForFocusTransitionL();

        if (!(LineIsFocusable(currentLine)))
            continue;

        ChangeFocusToAndExposeL(currentLine);
        LineChangedL((*iLines)[currentLine]->iId);
        iExtension->iFocusedClicked = ETrue;
        return(ETrue);
        }
        
    return EFalse;
    }

void CEikDialogPage::ChangeFocusToAndExposeL( TInt aLine, TBool /*aShowWholeControl*/ )
    {
    if ( aLine < 0 || aLine == iCurrentLine )
        return;
    
    TInt oldLine = iCurrentLine;
    
    if( aLine != iCurrentLine )
        (*iLines)[iCurrentLine]->ScrollBackEditor();
    
    ChangeFocusTo( aLine );
    ExposeLine( iCurrentLine, EFalse );

    if ( oldLine != iCurrentLine )
        {
        
        // If secret editor, cursor position should be update again to reflect
        // screen scroll caused by ExposeLine(...)
        CEikCaptionedControl* currentLine=(*iLines)[iCurrentLine];
        if( IsForm() && currentLine->ControlIsASecretEditor(currentLine->iControlType) )
            {
            ShowFocus(ETrue, EFalse);
            }
        
        DrawDeferred();
        }
    }

TInt CEikDialogPage::TopFocusableLine() const
    {
    const TInt numLines=iLines->Count();
    for (TInt i=0;i<numLines;i++)
        {
        if (LineIsFocusable(i))
            return i;
        }

    return KErrNotFound;
    }

TInt CEikDialogPage::BottomFocusableLine() const
    {
    const TInt numLines=iLines->Count();
    for (TInt i=numLines-1;i>=0;i--)
        {
        if (LineIsFocusable(i))
            return i;
        }

    return KErrNotFound;
    }

TBool CEikDialogPage::LineIsFocusable(TInt aLine) const
    {
    TBool focusable(ETrue);
    CEikCaptionedControl* line=(*iLines)[aLine];

    if (line->IsNonFocusing() || line->IsDimmed() || !(line->IsVisible()))
        focusable=EFalse;

    return focusable;
    }

void CEikDialogPage::SetDensePacking(TBool aDensePacking)
    {
    iLines->SetDensePacking(aDensePacking);
    }

void CEikDialogPage::InsertLineL(TInt aPosition,TInt aResourceId)
    {
    // alteration is bloated but should not provide any side-effects.
    if (!iFormControl)
        {
        CEikCaptionedControl* line=ConstructLineL(aResourceId);
        CleanupStack::PushL(line);
        iLines->InsertL(aPosition,line);
        CleanupStack::Pop(); // line
        line->RegisterPageWithCaptionControl(this);
        return;
        }
    ShowFocus( EFalse,EFalse ) ; 
    CEikCaptionedControl* line=ConstructLineL(aResourceId);
    CleanupStack::PushL(line);
    line->SetComponentsToInheritVisibility(); 
    iLines->InsertL(aPosition,line);
    CleanupStack::Pop(); // line now owned by iLines.
    AfterAddingNewLinesL(aPosition); 
/* 
iCurrentLine should be increased as it is relative to the lines in that page
and we have just added a new line before it in the page.
*/
    if (iCurrentLine>=aPosition) 
        iCurrentLine++;
    }

void CEikDialogPage::DeleteLine(TInt aLineId, TBool aRedraw)
    {
    TInt index( LineIndex( aLineId ) ) ;
    if ( index == iCurrentLine ) // we're deleting the current line
        {
// If this is the last line then move the focus to the line above.  (becomes -1 if last line)
        if( iCurrentLine == iLines->Count() - 1 )
            iCurrentLine-- ;
/* 
LastExposedLine is needed for when to remember control positions in forms.
If we've deleted that line, forget it.
*/      iLastExposedLine=-1; 
        }
    else
        {
/* Since iCurrentLine is relative to the positions in the form, if we've deleted a line which
comes before it in the list, we should reduce iCurrentLine by 1.
Same is true for LastExposedLine.
*/
        if (index<iCurrentLine)
            {
            iCurrentLine--;
            iLastExposedLine--;
            }
        }
// Actually delete the line.
    TInt lineIndex = LineIndex( aLineId );

    // delete line's cached draw commands
    if ( IsForm() )
        {
        iExtension->iRecordingGc->DeleteLine( lineIndex );
        }

    iLines->DeleteLine( lineIndex ); 
    
    ReconsiderPageSize();

    if (aRedraw)
        {
        if (iCurrentLine!=-1)
            {
            TInt targetLine = iCurrentLine ;
            iCurrentLine = -1 ;
            ChangeFocusTo( targetLine ) ;
            ExposeLine( targetLine, EFalse ) ;
            ShowFocus( ETrue, EFalse ) ;
            }

        DrawNow();
        TRAP_IGNORE(UpdateScrollBarL()); // if OOM, scrollbar will not be updated - No great loss.
        }
    }

void CEikDialogPage::AdjustAllIds(TInt aControlIdDelta)
    {
    iLines->AdjustAllIds(aControlIdDelta);
    }

TInt CEikDialogPage::FocusLineL(TInt aLineId)
    {
    TInt lineIndex=LineIndex(aLineId);

    if (lineIndex==KErrNotFound)
        return KErrNotFound;

    PrepareForFocusTransitionL();
// Show whole line, not scroll into line.
    ChangeFocusToAndExposeL(lineIndex, ETrue); 
    LineChangedL(aLineId);
    return KErrNone;
    }

TInt CEikDialogPage::FocusedLineId() const
    {
    if (iCurrentLine>=0)
        return (*iLines)[iCurrentLine]->iId;
    return 0;
    }

void CEikDialogPage::GetAutoValues()
    {
    const TInt numLines=iLines->Count();
    for (TInt ii=0;ii<numLines;ii++)
        {
        CEikCaptionedControl* line=(*iLines)[ii];
        TAny* returnValue=line->iReturnValue;
        if (!returnValue)
            continue;
        CCoeControl* control=line->iControl;
        switch (line->iControlType)
            {
        case EEikCtEdwin:
            ((CEikEdwin*)control)->GetText(*(TDes*)returnValue);
            break;
        case EEikCtSecretEd:
            ((CEikSecretEditor*)control)->GetText(*(TDes*)returnValue);
            break;

        case EEikCtFlPtEd:
            (*(TReal*)returnValue)=((CEikFloatingPointEditor*)control)->Value();
            break;
        case EEikCtFxPtEd:
            (*(TInt*)returnValue)=((CEikFixedPointEditor*)control)->Value();
            break;

        case EEikCtNumberEditor:
            (*(TInt*)returnValue)=((CEikNumberEditor*)control)->Number();
            break;
        case EEikCtRangeEditor:
            (*(SEikRange*)returnValue)=((CEikRangeEditor*)control)->Range();
            break;
        case EEikCtTimeEditor:
            (*(TTime*)returnValue)=((CEikTimeEditor*)control)->Time();
            break;
        case EEikCtDateEditor:
            (*(TTime*)returnValue)=((CEikDateEditor*)control)->Date();
            break;
        case EEikCtTimeAndDateEditor:
            (*(TTime*)returnValue)=((CEikTimeAndDateEditor*)control)->TimeAndDate();
            break;
        case EEikCtDurationEditor:
            (*(TTimeIntervalSeconds*)returnValue)=((CEikDurationEditor*)control)->Duration();
            break;
        case EEikCtTimeOffsetEditor:
            (*(TTimeIntervalSeconds*)returnValue)=((CEikTimeOffsetEditor*)control)->TimeOffset();
            break;

        default:
            ASSERT(iPageObserver);
            iPageObserver->GetCustomAutoValue(returnValue,line->iControlType,control);
            break;
            }
        }
    }

TInt CEikDialogPage::LineIndex(TInt aLineId)
    {
    const TInt numLines=iLines->Count();
    for (TInt ii=0;ii<numLines;ii++)
        {
        if ((*iLines)[ii]->iId==aLineId)
            return ii;
        }

    return KErrNotFound;
    }

TInt CEikDialogPage::YPosToLine2(TInt aYPos) const
    {
    return iLines->YPosToLine( Rect(), iScroll->Top(), iScroll->Middle(), iScroll->Bottom(), aYPos );
    }

TInt CEikDialogPage::LineToYPos(TInt& aLine) const
//
// Calcs YPos of line relative to the ViewWin and adjusts aLine if its out of bounds
    {
    ASSERT(iLines);
    const TInt numLines=iLines->Count();
    ASSERT(numLines>0);
    if (aLine<0)
        aLine=0;
    else if (aLine>=numLines)
        aLine=numLines-1;
    return (*iLines)[aLine]->Position().iY; // TPREMOVAL +iDataWinPos.iY;
    }

void CEikDialogPage::ExposeLine(TInt aLine, TBool aForceResize, TBool aShowWholeLine) 
//
/* Exposes the given line so that its fully visible in the ViewWin
*/  {
    if ( iSize.iHeight == 0 || aLine == -1 )
        {
        return;
        }

    CAknPaneScroll::TScrollChangeType change = iScroll->ExposeLine( aLine, aShowWholeLine );
    
    if ( change == CAknPaneScroll::ENoChange && !aForceResize )
        {
        return;
        }

    CEikCaptionedControl* capCtrl = (*iLines)[aLine];
    capCtrl->MinimumSize();
    TInt controlHeight (ControlHeight( aLine ));
    TInt focusedControlsPositionInDataWin (capCtrl->Position().iY);

    if ( IsForm() )
        {
        focusedControlsPositionInDataWin = iLines->LineIndexToYPosition( aLine, 0 );
        }
    
    TInt topYPosOfControlWhichMustBeViewable = focusedControlsPositionInDataWin;
    TInt bottomYPosOfControlWhichMustBeViewable = focusedControlsPositionInDataWin+controlHeight;
    TInt controlType = capCtrl->iControlType;

    // make the default value for where we'd like the datawinpos offset to be the current value
    TInt idealDataWindowPosition = 0;
    /* 
    If it's not a form, the values set above should be fine
    */
    if ( iFormControl && !aShowWholeLine )
        {
        if ( aLine == iLastExposedLine && !capCtrl->ControlIsAnEdwin( controlType ) && iFormControl ) 
            {
            /*
            We want to position this control as near to the place it was before as possible
            Important for growing and shrinking of popupfields.
            Hence set the datawin as the remembered position
            (the position is stored relative to the view win, hence the calculation)
            */
            idealDataWindowPosition = (-1*topYPosOfControlWhichMustBeViewable)+iLastExposedLineViewWinYPosition;

            topYPosOfControlWhichMustBeViewable = iLastExposedLineViewWinYPosition;
            bottomYPosOfControlWhichMustBeViewable = topYPosOfControlWhichMustBeViewable + controlHeight;
            }
        }

    SetDataPosition( topYPosOfControlWhichMustBeViewable, bottomYPosOfControlWhichMustBeViewable, aForceResize ); 
  
    if ( aLine != iLastExposedLine )
        {
        iLastExposedLine = aLine;
        iLastExposedLineViewWinYPosition = topYPosOfControlWhichMustBeViewable + idealDataWindowPosition;
        }
    }

void CEikDialogPage::SetDataPosition( TInt aTopY, TInt aBottomY, TBool aForceResize )
    {
    // update rect only if the currently focused control doesn't fit
    if ( iFormControl )
        {
        TInt topY = iPhysics->ViewTopY();
        TInt maxBottomY = topY + iSize.iHeight;

        if ( aForceResize || aTopY < topY || aBottomY > maxBottomY )
            {
            TInt totalHeight = 0;
            TInt count = iLines->Count();
            TPoint viewCenter( iPhysics->ViewCenter() );
            
            for ( TInt i = 0; i < count; ++i )
                {
                totalHeight += (*iLines)[i]->Rect().Height();
                }
            
            if ( totalHeight > iSize.iHeight )
                {
                if( aTopY < topY )
                    {
                    viewCenter.iY = iPhysics->ViewCenter().iY - topY + aTopY;
                    }                       
                else if( aBottomY > maxBottomY )
                    {
                    viewCenter.iY = iPhysics->ViewCenter().iY + aBottomY - maxBottomY;
                    }                       
                else if( totalHeight < ( iPhysics->ViewCenter().iY + iPhysics->ViewCenterDistance() ) )
                    {
                    viewCenter.iY = totalHeight - iPhysics->ViewCenterDistance();
                    }
                else 
                    {
                    viewCenter.iY = iPhysics->ViewCenter().iY;
                    }                        
                }
            else
                {
                viewCenter.iY = iPhysics->ViewCenterDistance();
                }

            iPhysics->SetViewCenter( viewCenter );
            iLines->MoveLineToScreen( iCurrentLine, iPhysics->ViewTopY(), ETrue );
            }
        }
    }
                    
/*
class CDummy: public CCoeControl
    {
    public:
        TBool IsReadyToDraw() const
            {
            return CCoeControl::IsReadyToDraw();
            }
    };
    
    if ( iPhysics )
        {
        // Awful hack below is used to prevent some unwanted drawing that would
        // otherwise occur during form's initialization.
        //
        // Unfortunately CCoeControl::IsActivated is protected so we need to
        // work around that somehow...
        CCoeControl* parent = WindowOwningParent();
        
        if ( parent )
            {
            CDummy* fakeParent = reinterpret_cast<CDummy*>( parent );
            TBool isReadyToDraw = fakeParent->IsReadyToDraw();
            
            if ( isReadyToDraw )
                {
                DrawNow();
                }
            }
        }
*/                    

TInt CEikDialogPage::ControlHeight(TInt aLineIndex) const
    {
    return (*iLines)[aLineIndex]->Size().iHeight;
    }

void CEikDialogPage::SizeChanged()
    {
    // update form area's size to scroll control
    iScroll->SetOutsideRect( Rect() );
    iLines->SetRect( Rect(), iScroll->Top(), iScroll->Middle(), iScroll->Bottom() );

    if ( (iLines->Count() > 0 ) && ( iCurrentLine >= 0 ) )
        {
        ExposeLine( iCurrentLine, EFalse );
        }

    TRAP_IGNORE( UpdateScrollBarL() ); // ignore any errors.
    AknsUtils::RegisterControlPosition( this ); 

    UpdatePhysics();
    iExtension->iInitialLayoutDone = ETrue;
    }

TSize CEikDialogPage::MinimumSize()
    {
    return TSize( iLines->MinimumSize().iWidth, 0 );   // Can be zero height
    }

void CEikDialogPage::PrepareForFocusLossL()
    {
    PrepareForFocusTransitionL();
    }

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 *
 * @internal
 * @since App-Framework_6.1
 */
#ifndef _DEBUG
void  CEikDialogPage::WriteInternalStateL(RWriteStream&) const
    {}
#else
void  CEikDialogPage::WriteInternalStateL(RWriteStream& aWriteStream) const
    {
    CCoeControl::WriteInternalStateL(aWriteStream);
    }
#endif

TSize CEikDialogPage::PreferredSize() const
    {
    return CONST_CAST(CEikDialogPage*,this)->iLines->MinimumSize();
    }

TBool CEikDialogPage::HandleEdwinSizeEventL(CEikEdwin* aEdwin, TEdwinSizeEvent aEventType, TSize aDesirableEdwinSize)
    {
    switch (aEventType)
        {
    case EEventSizeChanging:

        if ( iFormFlags & EFormResizeOptimisationFlag ) // Flag indicates that resizing is not necessary now (it will be done later)
            return EFalse ;
        if (iCurrentLine>=0&& iIgnoreFurtherEdwinResizeEvents!=aEdwin)
            return ResizeEdwinToFitTextL(aEdwin, EDrawNow, aDesirableEdwinSize);
        break;
    default:
        break;
        }
    return EFalse;
    }

/** 
 * From MEikEdwinObserver. Look for navigation and editor text update events, as scrolling
 might be required to keep cursor visible.
 */
void CEikDialogPage::HandleEdwinEventL(CEikEdwin* aEdwin,TEdwinEvent aEventType)
    {
    if ( IsForm() && ( aEventType == EEventTextUpdate
            || aEventType == EEventTextUpdateAPI ) )
        {
        CEikCaptionedControl* line = NULL;
        TInt controlType = -1;
        
        for ( TInt i = 0; i < iLines->Count(); ++i )
            {
            line = (*iLines)[i];
            controlType = line->ControlType();
            
            if ( line->ControlIsAnEdwin( controlType ) )
                {
                if ( line->iControl == aEdwin )
                    {
                    RecordLineL( i );
                    
                    if ( i != iCurrentLine )
                        {
                        DrawNow();
                        }
                        
                    break;
                    }
                }
            }
        }
    
    if( iCurrentLine == iLastExposedLine || iCurrentLine == -1 )
        return;
    if( aEventType == EEventNavigation || aEventType == EEventTextUpdate )
        {
        ExposeLine( iCurrentLine, EFalse );
            
        UpdateScrollBarL();
        }
    }

/**
 * Handle events caused by popup field controls, and resize if necessary
 */
void CEikDialogPage::HandlePopupFieldEventL(CAknPopupField* aPopupField, TAknPopupFieldEvent aEventType, TInt /*aHint*/)
    {
    switch (aEventType)
        {
    case EAknPopupFieldEventValueChange:
        {
        CEikCaptionedControl* line = NULL;
        for ( TInt i = 0; i < iLines->Count(); ++i )
            {
            line = (*iLines)[i];
            if ( line->iControl == aPopupField )
                {
                if ( IsForm() )
                    {
                    RecordLineL( i );
                    }
                DrawNow();
                break;
                }
            }
        break;  
        }
    case EAknPopupFieldEventModeChange:
        {
        TInt index = iCurrentLine;
        
        if(iIsEditable && (iExtension->iPopFieldEvents != 0))
            {           
            iExtension->iPopFieldEvents = 0;
            SetScbState(EFalse);
            }
        else
            {
            iExtension->iPopFieldEvents = 1;
            }     
                
        ReconsiderPageSize();
        ExposeLine( index, ETrue );
        DrawNow();

        UpdateScrollBarL();
        PrepareToDrawVerticalLine();
        break;
        }
    default:
        break;
        }
    }

void CEikDialogPage::PrepareToDrawVerticalLine() const
    { // to avoid flushes, we resize skin frame bitmaps before actual draw.
      // NOTE, this should be possiblie to call from SizeChanged() or OfferKeyEventL() method :-) (the GC?)

    if (AknsUtils::AvkonSkinEnabled())
        {
        MAknsSkinInstance* skin = AknsUtils::SkinInstance() ;
        MAknsControlContext* cc = AknsDrawUtils::ControlContext( this ) ;
        if ( CurrentLine() )
            {                 
            TRect rectNotToDrawOuter( CurrentLine()->Rect() ) ;
            TRect rectNotToDrawInner ;

            if ( iIsEditable )
                {
                rectNotToDrawInner.iTl = EditFrameTopLeftRect( rectNotToDrawOuter ).iBr ;
                rectNotToDrawInner.iBr = EditFrameBottomRightRect( rectNotToDrawOuter ).iTl ;
                AknsDrawUtils::PrepareFrame( skin,
                                             rectNotToDrawOuter,
                                             rectNotToDrawInner,
                                             KAknsIIDQsnFrInput,
                                             KAknsIIDDefault ) ;
                }

            }       
        
        }
    
    }

void CEikDialogPage::DrawVerticalLine() const
    {       
    }

void CEikDialogPage::HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType)
    {
    switch (aEventType)
        {
    case EEventPrepareFocusTransition:
        PrepareForFocusTransitionL();
        break;
    case EEventRequestFocus:
        ChangeFocusTo(FindLineIndex(aControl));
        break;
    case EEventStateChanged:
/*
if current line is at the top/bottom of the visible page
AND the page is in edit mode,
redraw the line in the captionedcontrol.
*/
        if (iCurrentLine!=-1)
            {
            CEikCaptionedControl* line = (*iLines)[iCurrentLine];
            if (line->ControlIsAnEdwin(line->iControlType))
                {
                if  (
                    (IsAtOrOffBottomOfPage(STATIC_CAST(CEikEdwin*,line->iControl))) || 
                    (IsAtOrOffTopOfPage(STATIC_CAST(CEikEdwin*,line->iControl)))
                    )
                    {
                    line->DrawClosingLine();
                    }
                }
            }
            
        if ( IsForm() )
            {
            CEikCaptionedControl* line = NULL;
            for ( TInt i = 0; i < iLines->Count(); ++i )
                {
                line = (*iLines)[i];
                if ( line->iControl == aControl )
                    {
                    RecordLineL( i );
                    break;
                    }
                }
            }

        PassOnEventL(aControl,aEventType);
        break;
    case EEventRequestExit:
    case EEventRequestCancel:
    case EEventInteractionRefused:
    default:
        break;
        }
    }

void CEikDialogPage::PassOnEventL(CCoeControl* aControl,MCoeControlObserver::TCoeEvent aEvent)
    {
    MCoeControlObserver* observer=Observer();
    if (observer)
        observer->HandleControlEventL(aControl,aEvent);
    }

TBool CEikDialogPage::ResizeEdwinToFitTextL(CEikEdwin* aEdwin, TDrawNow /*aDrawNow*/, TSize aDesirableEdwinSize)
//
    {
    TInt edwinYPosBefore = aEdwin->Position().iY;
    TInt edwinHeightBefore = aEdwin->Size().iHeight;

    const TInt maxHeight=iSize.iHeight-(KSpaceFromTitle+KSpaceFromBottom);
    TInt height = aDesirableEdwinSize.iHeight;
    if (height > maxHeight)
        height = maxHeight;

    TSize size = aEdwin->Size();
    TInt maximumEdwinHeight = aEdwin->MaximumHeight();
// ensure maxheight as dynamic construction may be done whilst form is of zero height.
    if ((maximumEdwinHeight > maxHeight) && maxHeight) 
        aEdwin->SetMaximumHeight(maxHeight);    // Can't be bigger than form itself
    else if ((maximumEdwinHeight == 0) && (size.iHeight == height))
        return EFalse;
   
    if ( (maximumEdwinHeight > 0) && (height > maximumEdwinHeight))
        height=maximumEdwinHeight;  // Can't be bigger than edwin itself
    size.iHeight = height;

    // Must force a size change on current captioned contrl even if control doesn't change size (so that edwin is resized by aknutils)
    aEdwin->SetSize(size);  
    ReconsiderPageSize();
    ExposeLine(iCurrentLine, ETrue);
    PrepareToDrawVerticalLine(); // do flushes here.

/* improved redraw code
Due to some unpleasantness about dialogs, forms and requirements, to get caption controls
to draw properly requires a call to draw now.  A system initiated draw does not work correctly

Therefore the drawing code has been tailored to minimise redraws and improve behaviour, whilst
cleaning up the marks left behind from shrinking edwins, etc.
*/
    TInt edwinYPosAfter = aEdwin->Position().iY;
    TInt edwinHeightAfter =  aEdwin->Size().iHeight;

/*
if the control is at the bottom of the page it could have initiated scrolling
which requires a full redraw.
*/
    DrawDeferred();
    if (edwinHeightBefore!=edwinHeightAfter)
        {
/* 
The scrollbar is updated here rather than in the more generic SizeChanged
as SizeChanged occurs multiple times on creation of multiline forms.
*/
        TRAP_IGNORE(UpdateScrollBarL()); // ignore any errors 
        }
    return ETrue;
    }


static TInt CountNumberOfLines_Edwin(CEikEdwin *aEdwin, TRect aRect, TInt numOfLines)
    {
    TInt edwinLines = numOfLines;
    TInt count = 0;
    for(TInt i=0;i<edwinLines;i++)
        {
        TInt scrolledLines = aEdwin->TextLayout()->FirstLineInBand();
        TInt docPos = aEdwin->TextLayout()->FirstCharOnLine(scrolledLines + i+1);
        TPoint point;
        aEdwin->TextLayout()->PosInBand(docPos, point);
        TInt yPos = point.iY;
        TRect lineRect;
        aEdwin->TextLayout()->GetLineRect(yPos, lineRect);
        lineRect.iTl += aEdwin->Position();
        lineRect.iBr += aEdwin->Position();
        if (aRect.Contains(lineRect.iTl) && aRect.Contains(lineRect.iBr))
            count++;
        }   
    return count;
    }
static TInt CountNumberOfLines_Ctrl(CCoeControl *aControl, TRect aRect)
    {
    TRect rect = TRect(aControl->Position(), aControl->Size());
    TInt count = 0;
    if (aRect.Contains(rect.iTl) && aRect.Contains(rect.iBr))
        count ++;
    return count;
    }

static TInt CountNumberOfVisibleLines(CEikCaptionedControl *aControl, TRect aClipRect)
    {
    TInt count = 0;
    if (aControl->ControlIsAnEdwin(aControl->iControlType))
        count += CountNumberOfLines_Edwin((CEikEdwin*)aControl->iControl, aClipRect, aControl->NumberOfLines());
    else
        count += CountNumberOfLines_Ctrl(aControl->iControl, aClipRect);
    count += CountNumberOfLines_Ctrl(aControl->iCaption, aClipRect);
    return count;
    }

static TInt NumberOfTextLinesVisible(CEikCapCArray *aLines, TInt aItem, TRect aClipRect)
    {
    if (aItem < 0) return 0;
    CEikCaptionedControl *control = (*aLines)[aItem];
    return CountNumberOfVisibleLines(control, aClipRect);   
    }


void CEikDialogPage::HandleScrollEventL(CEikScrollBar* aScrollBar,TEikScrollEvent aEventType)
    {
    iExtension->iHandlingScrollEvent = ETrue;

    switch (aEventType)
        {
        case EEikScrollPageUp:
        case EEikScrollPageDown:
        case EEikScrollThumbDragVert:
            iExtension->iScrolled = ETrue;
            iExtension->iScrolling = ETrue;
            iLines->MoveLineToScreen( iCurrentLine, 0, EFalse );
            break;

        default:
            break;
        }

    iPhysics->ViewPositionChanged( TPoint( iPhysics->ViewCenter().iX, 
            aScrollBar->ThumbPosition() + iPhysics->ViewCenterDistance() ), ETrue );

    switch (aEventType)
        {
        case EEikScrollPageUp:
        case EEikScrollPageDown:
        case EEikScrollThumbReleaseVert:
            iExtension->iScrolling = EFalse;
            iLines->MoveLineToScreen( iCurrentLine, iPhysics->ViewTopY(), ETrue );
            break;

        default:
            break;
        }
    
    iExtension->iHandlingScrollEvent = EFalse;
    }

TBool CEikDialogPage::LineHandlerCalled() const
    {
    return iExtension->iFlags.IsSet( CDialogPageExtension::ELineHandlerCalled );
    }    
    
TRect MainPane()
    {
    TRect mainPaneRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, mainPaneRect );
    return mainPaneRect;
    }

void CEikDialogPage::UpdateScrollBarL()
    {
    // Only forms in S60 need dialog's scrollbar.
    if ( !iFormControl || !iPageContainer->ScrollBar() || iSize.iHeight == 0 || iSize.iWidth == 0 || iExtension->iHandlingScrollEvent )
        {
        return;
        }

    CAknScrollBar* scrollBar = STATIC_CAST(CAknScrollBar*, iPageContainer->ScrollBar()->VerticalScrollBar());

    if (scrollBar)
        {
        TInt top = iScroll->Top();
        TInt middle = iScroll->Middle();
        TInt bottom = iScroll->Bottom();
        TRect parent( Rect() );
        TBool topmostPartial = top == -1;
        iLines->CalcItemIndexes(top, middle, bottom, parent.Size());
        TInt extraLines = topmostPartial ? NumberOfTextLinesVisible(iLines, top-1, parent) : 0;
        iExtension->iPreviousThumbPosition = iLines->NumberOfTextLinesBeforeLine( top - extraLines );

        // Using form layout, since this is used by AknForm only
        TAknWindowComponentLayout layout = TAknWindowComponentLayout::Compose( 
            AknLayoutScalable_Avkon::listscroll_form_pane(),  
            AknLayoutScalable_Avkon::scroll_pane_cp8());
            
        TRect scrollBarParent( MainPane().Size()/*mainPaneRect.Size()*/ );
    
        AknLayoutUtils::LayoutVerticalScrollBar(iPageContainer->ScrollBar(), scrollBarParent, layout.LayoutLine());
        if(!ScbState() &&  iCurrentLine!=-1 && iCurrentLine < iLines->Count() )
        	{
    		CEikCaptionedControl *ctrl = (*iLines)[iCurrentLine];
        	if(ctrl->ControlIsAPopfield(ctrl->iControlType))
				{
	            CAknPopupField::EAknPopupFieldSelectionMode mode = ((CAknPopupField*)ctrl->iControl)->SelectionMode();
	            if (mode == CAknPopupField::EAknPopupFieldSelectionListMode)
	                {
	                return;
	                }
				}        		
        	UpdateScrollBarThumb();
        	}
        }
    }
    

void CEikDialogPage::UpdateScrollBarThumb()
    {
    if ( !iFormControl || !iPageContainer->ScrollBar() || ScbState() )
        {
        return;
        }

    CAknScrollBar* scrollBar = STATIC_CAST(CAknScrollBar*, iPageContainer->ScrollBar()->VerticalScrollBar());
    
    if ( scrollBar )
        {
        TEikScrollBarModel vertModel;

        // scrollbar's accuracy is one pixel
        // TODO: replace iLines->MinimumSize with world size, presumably saved in CAknFormPhysics
        vertModel.iScrollSpan = iLines->MinimumSize().iHeight;
        vertModel.iThumbSpan = iSize.iHeight - iSize.iHeight % 2;
        vertModel.iThumbPosition = Max( iPhysics->ViewTopY(), 0 );

        iExtension->iPreviousThumbPosition = vertModel.iThumbPosition;
        TRAP_IGNORE(scrollBar->SetModelL(&vertModel)); // won't leave now, but can't guarantee forever        
        iPageContainer->ScrollBar()->Tile(&vertModel);
        iPageContainer->ScrollBar()->SetVFocusPosToThumbPos(vertModel.iThumbPosition);
        }
    }

CCoeControl* CEikDialogPage::ComponentControl(TInt aIndex) const
    {
    if ( IsForm() && !iExtension->iHandlingResourceChange)
        {
        if ( iCurrentLine != -1 && !iExtension->iScrolling )
            {
            return (*iLines)[iCurrentLine];
            }
            
        return NULL;
        }
        
    // Ensure that the current line is the last control returned
    if ( iCurrentLine != -1 )
        {
        if ( aIndex == CountComponentControls() -1 )
            return ((*iLines)[iCurrentLine]);
        else if ( aIndex < iCurrentLine )
            return ((*iLines)[aIndex]);
        else
            return ((*iLines)[aIndex+1]);
        }
    else
        return((*iLines)[aIndex]);
    }

TInt CEikDialogPage::CountComponentControls() const
    {
    if ( IsForm() && !iExtension->iHandlingResourceChange)
        {
        if ( iCurrentLine != -1 && !iExtension->iScrolling )
            {
            return 1;
            }
            
        return 0;
        }
        
    return iLines->Count();
    }

void CEikDialogPage::PrepareForFocusTransitionL()
    {
    if (iPageObserver)
        iPageObserver->PrepareForFocusTransitionL();
    }

void CEikDialogPage::ReportPageChangedL()
    {
    if (iPageObserver)
        iPageObserver->PageChangedL(PageId());
    }

void CEikDialogPage::LineChangedL(TInt aControlId)
    {
    if (iPageObserver)
        iPageObserver->LineChangedL(aControlId);
// update scrollbar
    UpdateScrollBarL();
    PrepareToDrawVerticalLine();
    }

void CEikDialogPage::ShowFocus(TBool aFocus, TBool aRedraw)
    {
    if (iCurrentLine>=0)
        {
        if ( iExtension && iExtension->iUsesSingleClick && aFocus )
            {
            aFocus = HighlightVisible();
            }
        
        (*iLines)[iCurrentLine]->SetCurrent(aFocus, aRedraw);

        if (aRedraw)
            (*iLines)[iCurrentLine]->DrawNow();
        else 
            (*iLines)[iCurrentLine]->DrawDeferred(); 
        }
    }

void CEikDialogPage::ChangeFocusTo(TInt aLineIndex)
    {
    TInt oldLine = iCurrentLine;
    
    if (aLineIndex==iCurrentLine)
        return;
    ShowFocus( EFalse, EFalse );
    iCurrentLine=aLineIndex;
    ShowFocus(ETrue, EFalse );

    if ( ( oldLine != iCurrentLine && IsForm() ) && 
            iExtension->iInitialLayoutDone )
        {
        if ( oldLine != -1 )
            {
            iLines->MoveLineToScreen( oldLine, 0, EFalse );
            RecordLineL( oldLine );
            }

		RecordLineL( iCurrentLine );
		iLines->MoveLineToScreen( iCurrentLine, iPhysics->ViewTopY(), ETrue );
		}
    }

TInt CEikDialogPage::FindLineIndex(const CCoeControl* aControl) const
    {
    return(iLines->FindLineIndex(aControl));
    }

/**
 * Gets the list of logical colors employed in the drawing of the control,
 * paired with an explanation of how they are used. Appends the list into aColorUseList.
 */
void CEikDialogPage::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const
    {
    TCoeColorUse colorUse;
    colorUse.SetLogicalColor(EColorDialogBackground);
    colorUse.SetUse(TCoeColorUse::EBack|TCoeColorUse::ESurrounds|TCoeColorUse::EActive|TCoeColorUse::ENormal|TCoeColorUse::ENeutral);
    aColorUseList.AppendL(colorUse);
    }

/**
 * Handles a change to the control's resources of type aType
 * which are shared across the environment, e.g. colors or fonts.
 */
void CEikDialogPage::HandleResourceChange(TInt aType)
    {
    if ( aType==KEikDynamicLayoutVariantSwitch )
        {
        const TInt numLines=iLines->Count();
        for ( TInt i=0; i < numLines; i++ )
            {
            CEikCaptionedControl* thisLine=(*iLines)[i];
            thisLine->iControl->HandleResourceChange(aType);
            }
        }

    if ( aType != KEikDynamicLayoutVariantSwitch || !IsForm() )
        {
        iExtension->iHandlingResourceChange = ETrue;
        CCoeControl::HandleResourceChange(aType);
        iExtension->iHandlingResourceChange = EFalse;
        }
    
// Removed, because disables transparency
    if (!CAknEnv::Static()->TransparencyEnabled() || 
        (PageContainer()->PageSelector()->Dialg()->DialogFlags() & EEikDialogFlagFillAppClientRect ||
        PageContainer()->PageSelector()->Dialg()->DialogFlags() & EEikDialogFlagFillScreen) )
        {
        Window().SetBackgroundColor(iEikonEnv->ControlColor(EColorDialogBackground,*this));
        }

    if ( IsForm() )
        {
        switch ( aType )
            {
            case KEikDynamicLayoutVariantSwitch:
                for ( TInt i = 0; i  < iLines->Count(); ++i ) 
                    {
                    (*iLines)[i]->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
                    }
                
                ReconsiderPageSize();

                if ( iCurrentLine != KErrNotFound )
                    {
                    if( iLastExposedLine != -1 )
                        {
                        iLastExposedLineViewWinYPosition = iLines->LineIndexToYPosition( iLastExposedLine, 0 );
                        }

                    iExtension->iScrolling = EFalse;
                    ExposeLine( iCurrentLine, ETrue );
                    (*iLines)[iCurrentLine]->DrawNow();
                    }
                
                DrawDeferred();
                break;

            case KAknsMessageSkinChange:
                ReconsiderPageSize();

                if ( iCurrentLine != KErrNotFound )
                    {
                    ExposeLine( iCurrentLine, ETrue );
                    }
                break;
                
            case KAknMessageFocusLost:
                if ( !IsEditable() && iExtension && 
                    iExtension->iUsesSingleClick && HighlightVisible() )
                    {
                    HighlightVisible( EFalse );
                    
                    CEikCaptionedControl* line = (*iLines)[iCurrentLine];
            
                    if ( line )
                        {
                        ShowFocus( EFalse, ETrue );
                        }
                    }
                break;

            default:
                break;
            }
        }
    }

CCoeControl* CEikDialogPage::Control(TInt aLineId) const
    {
    return(Line(aLineId)->iControl);
    }

CCoeControl* CEikDialogPage::ControlOrNull(TInt aLineId) const
    {
    TInt index=iLines->LineIndexFromId(aLineId);
    if (index<0)
        return(NULL);
    return((*iLines)[index]->iControl);
    }

CEikCaptionedControl* CEikDialogPage::Line(TInt aLineId) const
    {
    CEikCaptionedControl* line=LineOrNull(aLineId);
    if (line)
        return line;

    ASSERT(EFalse); // Not found.
    return NULL;
    }

CEikCaptionedControl* CEikDialogPage::LineOrNull(TInt aLineId) const
    {
    TInt index=iLines->LineIndexFromId(aLineId);
    if (index<0)
        return NULL;    // Not found.
    return((*iLines)[index]);
    }

CEikCaptionedControl* CEikDialogPage::CurrentLine() const
    {
    if (iCurrentLine>=0)
        return (*iLines)[iCurrentLine];

    return NULL;
    }

void CEikDialogPage::FocusChanged(TDrawNow /*aDrawNow*/)
    {
    if (iCurrentLine>=0 && !IsFocused())
        {
        CEikCaptionedControl* currentLine=(*iLines)[iCurrentLine];
        currentLine->SetCurrent(EFalse);
        }
    }

void CEikDialogPage::ResetLineMinimumSizes()
    {
    iLines->ResetMinimumSizes();
    }

TKeyResponse CEikDialogPage::OfferHotKeysKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
/* 
Changed from offering the hot key to every control on the page in order of appearance, until 
someone accepts the hotkey, to only offering the hot key to the current line and then, only if 
it accepts hotkeys.

  Added Enter key as a special case... 
*/
    if ( (iCurrentLine!=-1) && (iCurrentLine < iLines->Count()) )
        if ( (*iLines)[iCurrentLine]->OfferHotKeys() ||
            (*iLines)[iCurrentLine]->TakesEnterKey() && (aKeyEvent.iCode==EKeyEnter)
            )
            if (!IsForm()|| iIsEditable)
                return (*iLines)[iCurrentLine]->iControl->OfferKeyEventL(aKeyEvent,aType);
    return EKeyWasNotConsumed;
    }

TBool CEikDialogPage::TakesEnterKey()
    {
    if (iCurrentLine<0)
        return EFalse;
    return (*iLines)[iCurrentLine]->TakesEnterKey();
    }

void CEikDialogPage::SetEditableL( TBool aEditable, TBool /*aActivePage*/ ) 
    {
    // Tell each of the controls on the page (which are part of a form) of their editable state.  

    iIsEditable = aEditable;

    HighlightVisible( aEditable );
    
    if ( iExtension->iUsesSingleClick )
        {
        ShowFocus( EFalse );
        }
    
    const TInt numLines=iLines->Count() ;
/* if a form, no currently selected line, in edit mode,  and there is a line 
available (we know this as iLines->Count()>0), then select the first line.
*/
    if ((iFormControl) && (iCurrentLine==-1) && 
        (aEditable) && (iLines->Count()>0))
        iCurrentLine=0;
    for ( TInt ii = 0 ; ii < numLines ; ii++ )
        {
        if ( (*iLines)[ii]->iIsFormControl  )
            {
            (*iLines)[ii]->SetEditableL( aEditable,  !( iFormFlags & EEikFormHideEmptyFields ) ) ;
            CEikCaptionedControl* theLine =  (*iLines)[ii];
            if (theLine->ControlIsAnEdwin(theLine->iControlType))
                { 
/* 
Set the edwin out to have the correct width, but
  @ Make the line invisible, to prevent redraws.
  @ stop any edwin resize events being acted on (done by iIgnoreFurtherEdwinResizeEvents)
*/
                iIgnoreFurtherEdwinResizeEvents=STATIC_CAST(CEikEdwin*,theLine->iControl);
                theLine->MakeVisible(EFalse);
                theLine->PositionFormComponents();
                theLine->MakeVisible(ETrue);
                iIgnoreFurtherEdwinResizeEvents=0;
                if (aEditable)
                    {
/* 
Set the cursor position correctly for each edwin
@ if it's before the current line, set it to the end of the edwin
@ if it is or is after the current line, set it to the start of the edwin
*/
                    CEikEdwin* edwinPtr = STATIC_CAST(CEikEdwin*,theLine->iControl);
                    //filter enterkay.
                    //edwinPtr->AddFlagToUserFlags(CEikEdwin::ENoLineOrParaBreaks);
                    if (ii<=iCurrentLine)
                        edwinPtr->SetCursorPosL(edwinPtr->TextLength(),EFalse);
                    else
                        edwinPtr->SetCursorPosL(0,EFalse);
                    }
                }           
            }
        }
/* 
if changing to view mode, 
and the currentline is now non-focussing (invisible)
Then set iCurrentLine to the top focusable control
*/
    if ((iFormControl)&&(!aEditable)&&(iCurrentLine!=-1))
        {
        CEikCaptionedControl* line = (*iLines)[iCurrentLine];
        if (line->IsNonFocusing())
            {
// break the news to the old focussed line.
            ShowFocus(EFalse, EFalse);
// now set the new currentline value.
            iCurrentLine=TopFocusableLine();
            }
        }

    if ( ( iCurrentLine >= 0 ) && ( (*iLines)[iCurrentLine]->iIsFormControl ) )
        (*iLines)[iCurrentLine]->SetCurrent( ETrue ) ;
    
    ReconsiderPageSize();

    if ((iLines->Count()>0) && (iCurrentLine >= 0))
        {
        ExposeLine(iCurrentLine,ETrue); 
        }
  }

TBool CEikDialogPage::AnythingToDisplay() const
    {
    // assume Form control... shouldnt be called otherwise (Panic?)
    for (TInt i=0;i<iLines->Count();i++)
        {
        if ((*iLines)[i]->IsDisplayable())
            {
            return ETrue;
            };
        }

    return EFalse;
    }

// <SKIN> New function (Averell 2) to permit skinning the No Data screen.  New AknDrawWithSkins() utility requires 'this'
void CEikDialogPage::DrawEmptyListL( CWindowGc& aGc ) 
    {
     HBufC* dataBuffer=0;
    dataBuffer=iEikonEnv->AllocReadResourceLC(R_AVKON_NO_DATA );
    AknDrawWithSkins::DrawEmptyList(TRect(TPoint(1,7),TPoint(177,135)),aGc,*dataBuffer, this );
    CleanupStack::PopAndDestroy(); // finished with current val of dataBuffer 
    }

void CEikDialogPage::Draw(const TRect& /*aRect*/) const
    {
    if ( iFormControl )
        {
        // added this to see if anything on the page is visible.
        // if not, this is used to display the No data found screen.
        TBool anythingToShow= AnythingToDisplay();
    
        CWindowGc& windowGcRef = SystemGc(); // needed for DrawEmptyList

        if (!anythingToShow)
            {
            // Have to call non const leaving function...  Ignore the TRAP as result is cosmetic only.
            TRAP_IGNORE( const_cast<CEikDialogPage*>(this)->DrawEmptyListL( windowGcRef ) ) ;
            }
        else
            DrawVerticalLine();
        
        
        if ( IsForm() )
            {
            TInt delta = iPhysics->ViewCenter().iY;
            delta -= iPhysics->ViewCenterDistance();
            TInt topY = delta;
            delta *= -1;
            
            TAknLayoutRect formtLayoutRect;
            formtLayoutRect.LayoutRect(Rect(), AknLayoutScalable_Avkon::listscroll_form_pane().LayoutLine());
            formtLayoutRect.LayoutRect(formtLayoutRect.Rect(), AknLayoutScalable_Avkon::list_form_gen_pane().LayoutLine());


            TRect targetRect( formtLayoutRect.Rect() );
            targetRect.iBr.iY = topY + targetRect.Height();
            targetRect.iTl.iY = topY;

            TInt lineToSkip = -1;
            
            if ( !iExtension->iScrolling )
                {
                lineToSkip = iCurrentLine;
                }
            
            iExtension->iRecordingGc->FlushBuffer( targetRect, lineToSkip );
            }
        }
    }

void CEikDialogPage::AfterAddingNewLinesL(TInt aNewLineAdded)
    {
/**
* void CEikDialogPage::AfterAddingNewLinesL(TInt aNewLineAdded)
* 
* Context : Every time a line is added, this should be called
*
* Function:
*   It is used to :
*   #1 register the the dialog page with the caption control.
*   #2 register the control on this line (e.g. an edwin) with the one above it 
*   #3 call Register component on the line, to set up listeners, etc.
*   #4 Set the editable value to whatever the dialog page's editable value is.
*/
    __ASSERT_DEBUG(iLines && (aNewLineAdded<=iLines->Count()), Panic(EEikDialogPanicErrorDuringAddingLine));
    if (aNewLineAdded== -1)
        return; // line has not been added yet.
    CEikCaptionedControl* lineAdded = iLines->At(aNewLineAdded);
// if aNewLineAdded is zero, then there is no line above, else set value.
    CEikCaptionedControl* lineVisuallyAboveAndNumericallyBelow = 
                        (!aNewLineAdded)? 0:iLines->At(aNewLineAdded-1);
    // #1
    lineAdded->RegisterPageWithCaptionControl(this);
    // #2
    if (lineVisuallyAboveAndNumericallyBelow && iLines->At(aNewLineAdded)->iControl) 
        // there is a line above this one and it has a control 
        lineAdded->iControl->SetNeighbor(lineVisuallyAboveAndNumericallyBelow->iControl);
    // #3
    RegisterComponentL(lineAdded->iControlType, lineAdded->iControl, lineAdded); 
    // #4
    lineAdded->SetEditableL(iIsEditable);

    // The next is needed or phonebook's  "add field" / date will not work correctly.
    if (IsActivated())
        {
        DrawDeferred();
        }

    if (iFormControl)
        {
        lineAdded->SetPictographCallBack();
        }

    if ( IsForm() )
        {
        if ( aNewLineAdded < ( iLines->Count() - 1 ) )
            {
            // new line was added as the last line
            iExtension->iRecordingGc->InsertLineL( aNewLineAdded );
            }
        else
            {
            // new line was inserted between existing line
            iExtension->iRecordingGc->AppendLineL();
            }
        }

    ExposeLine( aNewLineAdded, EFalse );

    if ( IsForm() && iSize.iHeight != 0 && aNewLineAdded != -1 )
        iLines->MoveLineToScreen( aNewLineAdded, iPhysics->ViewTopY(), EFalse );
    }

TInt CEikDialogPage::GetFormFlags() const
    {return iFormFlags;};

void CEikDialogPage::SetFormFlag( TInt16 aFlag, TBool aEnable ) 
    {
    if ( aFlag >= EFormResizeOptimisationFlag ) // Dynamic Flags only - static flags are unaffected.
        {
        if ( aEnable )
            iFormFlags |= aFlag ;
        else if ( !aEnable )
            iFormFlags &= (~aFlag) ;
        }
    }

CEikCaptionedControl* CEikDialogPage::LineOnPageOrNull(TInt aLine) const
    {
    if (iLines) // if iLines, and there are enough lines on the page
        if (iLines->Count() > aLine)
            return (*iLines)[aLine];
    return 0;
    }

void CEikDialogPage::RegisterComponentL(TInt aControlType, CCoeControl* aControl, CEikCaptionedControl* aLine)
    {
/*
 Private method to deal with registering components with forms/dialogs correctly so that
 observers, etc are created.
 */
    if ( aControl && aLine->ControlIsAnEdwin( aControlType ) )
        {
        CEikEdwin* edwin=STATIC_CAST(CEikEdwin*,aControl);
        edwin->SetEdwinSizeObserver( this );
        edwin->SetEdwinObserver( this ) ;
        // Pre-empt the growth of Edwin.  It mustn't get any bigger.
        if ( !iFormControl )
            {
            edwin->SetMaximumHeight( iSize.iHeight );
            }
        }
    if (aControl && 
        ( aControlType==EAknCtPopupField || aControlType==EAknCtPopupFieldText))
        {
        CAknPopupField* popupField=0;
        if (aControlType==EAknCtPopupField)
            popupField = (CAknPopupField*)aControl ;
        else 
            popupField = (CAknPopupFieldText*)aControl ;
        popupField->SetPopupFieldObserver(this);
        popupField->SetMaxNumberOfLinesPermitted(aLine->MaximumNumberOfControlLinesOnVisiblePage());
        }
    if ( aControl && aLine->ControlIsAMfne( aControlType ) )
        {
        aControl->SetObserver( this );
        }
    if ( iFormControl )
        {
        // Tell the line that it is on a form - activate it to enable it draw its highlight box
        aLine->iIsFormControl = iFormControl ;
        if ( iFormFlags )
            aLine->SetFormFlags( iFormFlags ) ;

        aLine->GetAknLayoutValuesL() ;  // should cause the control to have size.
        }
    };


void CEikDialogPage::SetPageContainer(const CEikDialogPageContainer* aPageContainer)
    {
    iPageContainer=aPageContainer;
    }

const CEikDialogPageContainer* CEikDialogPage::PageContainer() const
    {
    return iPageContainer;
    }

void CEikDialogPage::ReconsiderPageSize()
    {
    if ( !Rect().IsEmpty() )
        {
        iLines->SetRect( Rect(), iScroll->Top(), iScroll->Middle(), iScroll->Bottom() );
        }
    }

EXPORT_C void CEikDialogPage::SetFormLayout(TFormLayoutSelection aLayout)
    {
    __ASSERT_DEBUG(iFormControl , Panic(EEikFormPanicSettingDoublePageFormLayoutOnNonForm));
    iFormLayout=aLayout;    
    };

EXPORT_C CEikDialogPage::TFormLayoutSelection CEikDialogPage::FormLayout() const
    {
    return iFormLayout;
    }

TBool CEikDialogPage::IsEditable() const
    {
    return iIsEditable;
    }

TBool CEikDialogPage::IsForm() const
    {
    return iFormControl;
    }

void CEikDialogPage::SetDoubleQuery(TBool aIsDoubleQuery)
    {   
    iExtension->iIsDoubleQuery = aIsDoubleQuery;    
    }

CEikFormAnim* CEikDialogPage::AcquireAnim(
    TBool aAcquire, MEikFormAnimObserver* aObserver ) const
    {
    if( iPageContainer )
        return iPageContainer->AcquireAnim( aAcquire, aObserver );

    return NULL;
    }

TBool CEikDialogPage::IsAtOrOffTopOfPage(const CCoeControl* aControl) const
    {
    if (!iLines||!aControl)
        return EFalse;
    TInt lineIndex = FindLineIndex(aControl);
    if (lineIndex==-1)
        return EFalse;
    CEikCaptionedControl* capCtrl =(*iLines)[lineIndex];
    if (!capCtrl)
        return EFalse;
    if (capCtrl->Rect().iTl.iY<=0 )
        return ETrue;
    else
        return EFalse;
    }

TBool CEikDialogPage::IsAtOrOffBottomOfPage(const CCoeControl* aControl) const
    {
    if (!iLines|| !aControl)
        return EFalse;
    TInt lineIndex = FindLineIndex(aControl);
    if (lineIndex==-1)
        return EFalse;
    CEikCaptionedControl* capCtrl =(*iLines)[lineIndex];
    if (!capCtrl)
        return EFalse;
    if (capCtrl->Rect().iBr.iY>=(iSize.iHeight))
        return ETrue;
    else
        return EFalse;
    
    }

/* 
return True if off the top
return False if off the top
*/

TBool CEikDialogPage::VisibleSizeOnPage(TInt& aHeightOfControlVisibleOnPage, const CCoeControl* aControl) const
    {
    if (!iLines|| !aControl)
        {
        aHeightOfControlVisibleOnPage=0;
        return EFalse;
        }
    TInt lineIndex = FindLineIndex(aControl);
    if (lineIndex==-1)
        {
        aHeightOfControlVisibleOnPage=0;
        return EFalse;
        }
    CEikCaptionedControl* capCtrl =(*iLines)[lineIndex];
    aHeightOfControlVisibleOnPage=capCtrl->Rect().Height();
    return EFalse;
    }

TSize CEikDialogPage::RealDataSize() const
    {
    if (iLines)
        if (iLines->Count()>0)
            return TRect((*iLines)[0]->Rect().iTl,(*iLines)[iLines->Count()-1]->Rect().iBr).Size();
    return iSize;
    }

TInt CEikDialogPage::NumberOfLines() const
    {
    if (iLines)
        return iLines->Count();
    return 0;
    }

CEikCaptionedControl* CEikDialogPage::LineByIndex(TInt aIndex) const
    {
    if (iLines->Count() > aIndex && aIndex>=0)
        return (*iLines)[aIndex];
    return 0;
    }

EXPORT_C void* CEikDialogPage::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }   

// ---------------------------------------------------------------------------
// CEikDialogPage::HandleFormPointerEventL
// ---------------------------------------------------------------------------
//
void CEikDialogPage::HandleFormPointerEventL( const TPointerEvent& aPointerEvent )
    {
    if ( LineHandlerCalled() )
        {
        return;
        }
    
    TInt touchedLine = iLines->YPositionToLineIndex( aPointerEvent.iPosition.iY + iPhysics->ViewTopY() );
    TBool callDefaultImplementation = ETrue;
    
    // Tapping form's empty area takes no action of any kind. Also bounce
    // effect can't be stopped.
    if ( ( aPointerEvent.iType == TPointerEvent::EButton1Down && touchedLine == KErrNotFound ) || !iPhysics->CanBeStopped() )
        {
        IgnoreEventsUntilNextPointerUp();
        return;
        }

    CEikCaptionedControl* newLine = NULL;
    TInt controlType = KErrNotFound;

    if ( touchedLine != KErrNotFound )
        {
        newLine = (*iLines)[touchedLine];
        controlType = newLine->iControlType;
        }

    TBool textSelected = EFalse;

    if ( touchedLine != iCurrentLine && newLine && 
            !iExtension->iUsesSingleClick )
        {
        if ( !newLine->ControlIsAPopfield( controlType ) )
            {
            callDefaultImplementation = EFalse;
            }
        }

    if ( iCurrentLine != -1 && iCurrentLine == iExtension->iLastTouchedLine )
        {
        CEikCaptionedControl* currentLine = (*iLines)[iCurrentLine];
        
        if ( currentLine->ControlIsAnEdwin( currentLine->iControlType ) )
            {
            CEikEdwin* edwin = static_cast<CEikEdwin*>( currentLine->iControl );
            textSelected = edwin->SelectionLength();
            
            if ( textSelected == edwin->TextLength() )
                {
                textSelected = EFalse;
                }
            }
        }
        
    if ( aPointerEvent.iType == TPointerEvent::EButton1Down && touchedLine != KErrNotFound )
        {
        iExtension->iOldCenterY = iPhysics->ViewCenter().iY;
        TInt bottom = iExtension->iOldCenterY + iSize.iHeight - iSize.iHeight / 2;
        if ( bottom < 0 )
            {
            iExtension->iBottomItem = -1;
            }
        else
            {
            iExtension->iBottomItem = bottom / (*iLines)[0]->Size().iHeight;
            if ( iExtension->iBottomItem > iLines->Count() )
                {
                iExtension->iBottomItem = iLines->Count();
                }
            }
        TInt upper = iExtension->iOldCenterY - iSize.iHeight / 2;
        if ( upper <= 0 )
            {
            iExtension->iTopItem = -1;
            }
        else
            {
            iExtension->iTopItem = upper / (*iLines)[0]->Size().iHeight;
            if ( iExtension->iTopItem > iLines->Count() )
                {
                iExtension->iTopItem = iLines->Count();
                }
            }
        iExtension->iScrolling = EFalse;
        iExtension->HandleFormFeedback( this, aPointerEvent, touchedLine, iCurrentLine );
        
        TBool wasScrolling = ( iPhysics->OngoingPhysicsAction() != 
            CAknPhysics::EAknPhysicsActionNone );
        iPhysics->Stop();
        iExtension->iLastTouchedLine = touchedLine;
        iExtension->iDragStartPosition = aPointerEvent.iPosition;
        iExtension->iLastPointerPos = aPointerEvent.iPosition;
        iExtension->iStartTime.HomeTime();

        if ( touchedLine != iCurrentLine )
            {
            iExtension->iFocusedClicked = EFalse;

            if ( iExtension->iUsesSingleClick )
                {
                if ( !wasScrolling )
                    {
                    HighlightVisible( ETrue );
                    HighlightTimerCallBack( this );
                    }
                }
            else
                {
                iExtension->iHighlightTimer->Cancel();
                iExtension->iHighlightTimer->Start( 
                    TTimeIntervalMicroSeconds32( iPhysics->HighlightDelay() * 1000 ),
                    TTimeIntervalMicroSeconds32( iPhysics->HighlightDelay() * 1000 ),
                    TCallBack( HighlightTimerCallBack, this ) );
                }
            }
        else
            {
            iExtension->iFocusedClicked = ETrue;
            
            if ( !IsEditable() && iExtension->iUsesSingleClick )
                {
                CEikCaptionedControl* currentLine = (*iLines)[iCurrentLine];
                
                if ( currentLine )
                    {
                    HighlightVisible( ETrue );
                    ShowFocus( ETrue, ETrue );
                    }
                }
            }
        }

    if ( aPointerEvent.iType == TPointerEvent::EDrag )
        {
        TPoint drag( iExtension->iDragStartPosition - aPointerEvent.iPosition );
        
        if ( Abs( drag.iY ) > iPhysics->DragThreshold() )
            {
            iExtension->iHighlightTimer->Cancel();

            if ( !iExtension->iScrolling && !textSelected )
                {
                if ( !IsEditable() && iExtension->iUsesSingleClick && 
                     HighlightVisible() )
                    {
                    HighlightVisible( EFalse );
                    
                    CEikCaptionedControl* currentLine = (*iLines)[iCurrentLine];
                    
                    if ( currentLine )
                        {
                        ShowFocus( EFalse, ETrue );
                        }
                    }

                iExtension->iScrolling = ETrue;
                iExtension->iScrolled = ETrue;
                iExtension->iLastPointerPos = aPointerEvent.iPosition;
                RemovePressedDownHighlight();
                iLines->MoveLineToScreen( iCurrentLine, 0, EFalse );
                callDefaultImplementation = EFalse;
                }
            }

        if ( iExtension->iScrolling )
            {
            iPhysics->SetPanningPosition( 
                TPoint( 0, iExtension->iLastPointerPos.iY - aPointerEvent.iPosition.iY ) );
            iExtension->iLastPointerPos = aPointerEvent.iPosition;
            }
        //For secret editor display
        CEikCaptionedControl* currentLine=(*iLines)[iCurrentLine];
        if( currentLine->ControlIsASecretEditor(currentLine->iControlType) )
            {
            CEikSecretEditor* edwin=(CEikSecretEditor*)currentLine->iControl;
            edwin->EnableCursor( EFalse );
            }
        }                                
    
    if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
        {
        iExtension->HandleFormFeedback( this, aPointerEvent, touchedLine, iCurrentLine );
        if ( !IsEditable() && iExtension->iUsesSingleClick && 
             HighlightVisible() )
            {
            HighlightVisible( EFalse );
            
            CEikCaptionedControl* currentLine = (*iLines)[iCurrentLine];

            if ( currentLine )
                {
                ShowFocus( EFalse, ETrue );
                }
            }

        TPoint drag( iExtension->iDragStartPosition - aPointerEvent.iPosition );
        
        if ( !textSelected )
            {
            if ( !iPhysics->StartFlick( drag, iExtension->iStartTime ) )
                {
                iExtension->iScrolling = EFalse;
                
                if ( iPageObserver && GrabbingComponent() )
                    {
                    iPageObserver->HandleDialogPageEventL( MEikDialogPageObserver::EDialogPageTapped );
                    }
                }
            else 
                {
                callDefaultImplementation = EFalse;
                
                if ( !iExtension->iScrolling )
                    {
                    // feedback is given every time when new item 
                    // appears to the screen -> follows the visual feedback
                    iExtension->SilentFeedback( this, ETouchFeedbackSensitiveItem, aPointerEvent );
                    // It might happen that there are no drag events between down and
                    // up if the distance is short enough.
                    iExtension->iHighlightTimer->Cancel();
                    iExtension->iScrolling = ETrue;
                    iExtension->iScrolled = ETrue;
                    iLines->MoveLineToScreen( iCurrentLine, 0, EFalse );
                    RemovePressedDownHighlight();
                    }
                }
            }
        }

    // forward pointer event to line's observer
    if ( touchedLine == iCurrentLine && newLine && 
            ( iExtension->iFocusedClicked || 
            ( !IsEditable() && iExtension->iUsesSingleClick ) ) && 
            !iExtension->iScrolling )
        {
        MPointerEventObserver* observer = newLine->PointerEventObserver();
        
        if ( observer )
            {
            iExtension->iFlags.Set( CDialogPageExtension::ELineHandlerCalled );
            observer->PointerEvent( newLine, aPointerEvent );
            iExtension->iFlags.Clear( CDialogPageExtension::ELineHandlerCalled );
            }
        }
    
    TBool mskPress = EFalse;

    // If the stylus is up above already focused line - emulate an MSK press
    if ( iFormControl && !iIsEditable && // in view mode
        aPointerEvent.iType == TPointerEvent::EButton1Up &&
        touchedLine == iCurrentLine &&
        ( iExtension->iFocusedClicked || iExtension->iUsesSingleClick ) &&
        !iExtension->iScrolling )
        {
        mskPress = ETrue;
        callDefaultImplementation = EFalse;
        }
    
    if ( callDefaultImplementation && ( iExtension->iFocusedClicked || 
            iExtension->iUsesSingleClick ) && newLine )
        {
        if ( newLine->ControlIsAPopfield( controlType ) )
            {
            if(aPointerEvent.iType == TPointerEvent::EButton1Down)
                {
            	newLine->HandlePointerEventL(aPointerEvent);
            	iExtension->iCapturingItem = touchedLine;       
                }
            else if(aPointerEvent.iType == TPointerEvent::EButton1Up)
                {
                newLine->HandlePointerEventL(aPointerEvent);  
                }
            }
        else
            {            
            CCoeControl::HandlePointerEventL( aPointerEvent );
            }
         }
         
    if ( mskPress )
        {
        TKeyEvent key;
        key.iCode=EKeyOK;
        key.iModifiers=0;
        key.iRepeats = 0;
        CEikonEnv::Static()->SimulateKeyEventL( key, EEventKey );
        }
    }


// ---------------------------------------------------------------------------
// CEikDialogPage::UpdatePhysics
// ---------------------------------------------------------------------------
//
void CEikDialogPage::UpdatePhysics()
    {
    if ( IsForm() )
        {
        TPoint viewCenter( iSize.iWidth / 2, 0 );
        
        if ( iLines->Count() > 0 )
            {
            viewCenter.iY = Abs( (*iLines)[0]->Rect().iTl.iY - iPosition.iY );
            }
            
        viewCenter.iY += iPhysics->ViewCenterDistance();
        
        if ( iExtension->iInitialLayoutDone )
            {
            TInt oldScreenHeight = iPhysics->ViewSize().iHeight;
            TInt delta = ( iPhysics->ViewCenterDistance() ) - 
                ( oldScreenHeight / 2 );

            viewCenter = iPhysics->ViewCenter();
            viewCenter.iY += delta;
            }

        TSize worldSize( iLines->MinimumSize() );
        worldSize.iHeight = Max( worldSize.iHeight, iSize.iHeight );

        TRAP_IGNORE( iPhysics->InitPhysicsL( worldSize, iSize, viewCenter ) );
        TRAP_IGNORE( UpdateScrollBarL() );
        }
    }


// ---------------------------------------------------------------------------
// CEikDialogPage::HighlightTimerCallBack
// ---------------------------------------------------------------------------
//
TInt CEikDialogPage::HighlightTimerCallBack( TAny* aPtr )
    {
    CEikDialogPage* me = static_cast<CEikDialogPage*>( aPtr );
    me->HandleHighlightTimer();
    
    return 0;
    }


// ---------------------------------------------------------------------------
// CEikDialogPage::HandleHighlightTimer
// ---------------------------------------------------------------------------
//
void CEikDialogPage::HandleHighlightTimer()
    {
    iExtension->iHighlightTimer->Cancel();
    
    TInt touchedLine = iExtension->iLastTouchedLine;
    
    if ( ( touchedLine < iLines->Count() ) && ( touchedLine != iCurrentLine ) )
        {
        (*iLines)[touchedLine]->ActivateL();
        
        if ( LineIsFocusable( touchedLine ) )
            {
            TRAP_IGNORE( PrepareForFocusTransitionL() );
            ChangeFocusToAndExposeL( touchedLine );
            LineChangedL( (*iLines)[touchedLine]->iId );
            }
        }
    }



// ---------------------------------------------------------------------------
// CEikDialogPage::HighlightVisible
// ---------------------------------------------------------------------------
//
TBool CEikDialogPage::HighlightVisible() const
    {
    if ( IsEditable() || !iExtension->iUsesSingleClick )
        {
        return ETrue;
        }
    
    return iHighlightVisible;
    }


// ---------------------------------------------------------------------------
// CEikDialogPage::ScrollCacheByPixels
// ---------------------------------------------------------------------------
//
void CEikDialogPage::ScrollCacheByPixels( 
		TInt /*aDelta*/, const TDesC& /*aDebugMsg*/, TBool aDrawNow )
    {
    if ( iLines->Count() <= 0 )
        return;
    TInt bottomItem, upperItem;
    TInt bottom = iPhysics->ViewCenter().iY + iSize.iHeight - iSize.iHeight / 2;
    if ( bottom < 0 )
        {
        bottomItem = -1;
        }
    else
        {
        bottomItem = bottom / (*iLines)[0]->Size().iHeight;
        if ( bottomItem > iLines->Count() )
            {
            bottomItem = iLines->Count();
            }
        }
    TInt upper = iPhysics->ViewCenter().iY - iSize.iHeight / 2;
    if ( upper <= 0 )
        {
        upperItem = -1;
        }
    else
        {
        upperItem = upper / (*iLines)[0]->Size().iHeight;
        if ( upperItem > iLines->Count() )
            {
            upperItem = iLines->Count();
            }
        }
    if ( upperItem == -1 || bottomItem == iLines->Count() )
        {
        if ( upperItem != iExtension->iTopItem || bottomItem != iExtension->iBottomItem )
            {
            iExtension->SilentFeedback( this, ETouchFeedbackSensitiveItem, TPointerEvent() );
            }
        }
    else if ( upperItem >= 0 || bottomItem < iLines->Count() )
        {
        if ( upperItem < iExtension->iTopItem || bottomItem > iExtension->iBottomItem )
            {
            iExtension->SilentFeedback( this, ETouchFeedbackSensitiveItem, TPointerEvent() );
            }
        }
    iExtension->iBottomItem = bottomItem;
    iExtension->iTopItem = upperItem;
    if ( aDrawNow )
        {
        TRAP_IGNORE( UpdateScrollBarL() );
        DrawNow();
        }
    }


// ---------------------------------------------------------------------------
// CEikDialogPage::UpdateLineInCache
// ---------------------------------------------------------------------------
//
void CEikDialogPage::UpdateLineInCache( CEikCaptionedControl* aLine )
    {
    TInt lineIndex = iLines->FindLineIndex( aLine );
    
    if ( lineIndex != KErrNotFound )
        {
        if ( aLine->Position() != TPoint( 1000, 0 ) )
            {
            iExtension->iRecordingGc->SetLineRect( lineIndex, TRect( TPoint( 1000, 0 ), aLine->Rect().Size() ) );
            }
        else
            {
            iExtension->iRecordingGc->SetLineRect( lineIndex, aLine->Rect() );
            iExtension->iRecordingGc->PurgeLine( lineIndex );

            Parent()->Parent()->Parent()->SetCustomGc( iExtension->iRecordingGc );
            
            aLine->DrawForeground( aLine->Rect() );
            DrawControl( aLine );

            Parent()->Parent()->Parent()->SetCustomGc( NULL );
            }    
        }

    if ( iExtension->iInitialLayoutDone )
        {
        UpdatePhysics();
        }
    }


// ---------------------------------------------------------------------------
// CEikDialogPage::Synchronize
// ---------------------------------------------------------------------------
//
void CEikDialogPage::Synchronize()
    {
    iExtension->iScrolling = EFalse;
    iLines->MoveLineToScreen( iCurrentLine, iPhysics->ViewTopY(), ETrue );
    }


// ---------------------------------------------------------------------------
// CEikDialogPage::DrawControl
// ---------------------------------------------------------------------------
//
void CEikDialogPage::DrawControl( CCoeControl* aControl ) const
    {
    TInt count = aControl->CountComponentControls();
    RDrawableWindow* parentWindow = aControl->DrawableWindow();
    
    for ( TInt i = 0; i < count; ++i )
        {
        CCoeControl* control = aControl->ComponentControl( i );
        RDrawableWindow* childWindow = control->DrawableWindow();
        
        // Test whether child control has its own window. In that case skip
        // recording since child windows can't be scrolled.
        if ( parentWindow->WsHandle() != childWindow->WsHandle() )
            {
            continue;
            }
        
        control->DrawForeground( control->Rect() );
        DrawControl( control );
        }
    }


// ---------------------------------------------------------------------------
// CEikDialogPage::RecordLinesL
// ---------------------------------------------------------------------------
//
void CEikDialogPage::RecordLinesL()
    {
    Parent()->Parent()->Parent()->SetCustomGc( iExtension->iRecordingGc );
    
    iExtension->iRecordingGc->PurgeBuffer();

    CEikCaptionedControl* line = NULL;
    
    for ( TInt i = 0; i < iLines->Count(); ++i )
        {
        line = (*iLines)[i];
        iExtension->iRecordingGc->PrepareForNewLineL( line->Rect() );
        line->DrawForeground( line->Rect() );
        DrawControl( line );
        }

    Parent()->Parent()->Parent()->SetCustomGc( NULL );
    }


// ---------------------------------------------------------------------------
// CEikDialogPage::RecordLineL
// ---------------------------------------------------------------------------
//
void CEikDialogPage::RecordLineL( TInt aLine )
    {
    Parent()->Parent()->Parent()->SetCustomGc( iExtension->iRecordingGc );
    
    CEikCaptionedControl* line = (*iLines)[aLine];
    
    if ( line )
        {
        iExtension->iRecordingGc->ReplaceLineL( aLine );
        line->DrawForeground( (line->Rect() ) );
        DrawControl( line );
        }
    
    Parent()->Parent()->Parent()->SetCustomGc( NULL );
    }


// ---------------------------------------------------------------------------
// CEikDialogPage::ScrollByPixels
// ---------------------------------------------------------------------------
//
void CEikDialogPage::ScrollByPixels( TInt aDelta )
    {
    if ( aDelta != 0 )
        {
        iLines->ScrollByPixels( aDelta );
        TRAP_IGNORE( UpdateScrollBarL() );
        DrawNow();
        TRAP_IGNORE( RecordLinesL() );
        }
    }


// ---------------------------------------------------------------------------
// CEikDialogPage::RemovePressedDownHighlight
// ---------------------------------------------------------------------------
//
void CEikDialogPage::RemovePressedDownHighlight()
    {
    if ( iCurrentLine != -1 )
        {
        CEikCaptionedControl* currentLine = (*iLines)[iCurrentLine];
        
        if ( currentLine && currentLine->PressedDownState() )
            {
            currentLine->SetPressedDownState( EFalse );
            if ( IsForm() )
                {
                RecordLineL( iCurrentLine );
                }
            }
        }
    }


// ---------------------------------------------------------------------------
// CEikDialogPage::HighlightVisible
// ---------------------------------------------------------------------------
//
void CEikDialogPage::HighlightVisible( TBool aVisible )
    {
    if ( !IsEditable() )
        {
        iHighlightVisible = aVisible;
        }
    }


//------------------------------------------------------------------------------------
// CEikDialogPage::HandlePointerEventL()
// Function notifys the pages observer that the page has been tapped. (stylus down&up)
// The first tap to a dialog line sets focus to it (on stylus down),the second tap
// on the same line emulates an MSK press (on stylus up). It works also when the dialog
// is just opened and the (first) focused line is tapped. Any dragging to another line
// prevents the MSK press emulation on the subsequent stylus up event.

// iExtension->iFocusClicked is used as a flag to indicate that the focus was previously
// moved to the current line. At the function beginning, if the stylus is down on the same
// line as the previous time, it means the current line is focused, and an MSK press must
// be emulated on the stylus up event. If iExtension->iFocusClicked is not set at a stylus
// up event, nothing happens: it means that the previous stylus down event just moved
// the focus to this line.


/*
Tactile feedback changes here potentially affect
- forms                - can be distinquished with IsForm(). Feedback is handled here
- notes and notifiers  - own feedback implementation-> should not be handled here
- queries              - own feedback implementation -> should not be handled here
- sct                  - own feedback implementation-> should not be handled here
- popup form           - no need for feedback
- color selection grid - own feedback implementation-> should not be handled here

and of course any 3rd party stuff, which can not be reasonably handled here without
knowing how the 3rd party stuff should work.

---> only trigger feedback for form here. Anything else will be wrong.
*/


//------------------------------------------------------------------------------------
//
void CEikDialogPage::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    // Forms have their own specialized pointer event handling if panning and flicking
    // are enabled.
    if ( IsForm() )
        {
        HandleFormPointerEventL( aPointerEvent );
        return;
        }
    // Pointer event is not handled at all if the dialog page has no lines. If an event
    // would be handled in such situation if would crash in several places inside this
    // method and the methods called from here. Also in some occasions such a dialog page
    // indicates that the dialog is not fully constructed yet.
    
    // Leaving pointer event handling undone is quite safe assumption since a dialog without
    // lines is empty. There's nothing that could happen when such a dialog is tapped e.g.
    // it can't be dismissed since it doesn't have any CAknNoteControls etc. And if a client
    // application wanted to alter this behaviour it would need to override this method anyway.
    if( !AknLayoutUtils::PenEnabled() || iLines->Count() == 0 || LineHandlerCalled() )
        {
        return;
        }
    
    if ( PageContainer()->PageSelector()->Dialg()->Extension()->iPublicFlags.IsSet( CEikDialogExtension::EUseVirtualInput ) )
        {
        PageContainer()->PageSelector()->Dialg()->Extension()->iPublicFlags.Set( CEikDialogExtension::EDelayedExit );
        }
    
    CCoeControl* grabbingComponent = GrabbingComponent(); 
    TBool callDefaultImplementation = ETrue;
    TBool focusItem = EFalse;
    // YPosToLine is scaled to iDataWinPos, so add it to pointer Y position
    TInt yPosition = aPointerEvent.iPosition.iY; // + iDataWinPos.iY;
    TInt touchedLineIndex = YPosToLine2( yPosition );
    // If the stylus is down and the touched line is already the current one,
    // mark this fact in iExtension->iFocusedClicked to be used later when the stylus is up.
    
    if ( touchedLineIndex != KErrNotFound && 
         iExtension->iCapturingItem != KErrNotFound &&
         touchedLineIndex != iExtension->iCapturingItem )
        {
        iExtension->iCapturingItem = KErrNotFound;
        }
        
    // Click outside of items - do nothing
    if ( touchedLineIndex == KErrNotFound )
        {
        // Pan & flick capturing pointer events
        if ( iExtension->iCapturingItem != KErrNotFound )
            {
            CEikCaptionedControl* capturingItem = 
                (*iLines)[iExtension->iCapturingItem];
            const TInt type ( capturingItem->iControlType );
            if ( capturingItem->ControlIsAPopfield( type ) )
                {
                capturingItem->iControl->HandlePointerEventL( aPointerEvent );
                if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
                    {
                    iExtension->iCapturingItem = KErrNotFound;
                    }
                }
            }
            
        if( aPointerEvent.iType == TPointerEvent::EDrag || aPointerEvent.iType == TPointerEvent::EButtonRepeat )
            {
            TInt numLines=iLines->Count();
            for (TInt ii=0;ii<numLines;ii++)
                {
                //If dragging out of forms, no pressed down effect.
                CEikCaptionedControl* thisLine=(*iLines)[ii];
                const TInt controlType(thisLine->iControlType);
                if(thisLine->ControlIsAnEdwin(controlType) || thisLine->ControlIsAMfne(controlType))
                    {
                    if( thisLine->PressedDownState() )
                        {
                        thisLine->SetPressedDownState( EFalse );
                        thisLine->DrawDeferred();
                        }
                    }
                }
            CAknControl::HandlePointerEventL(aPointerEvent);        
            }
        // Forward point up event also.
        if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
            {
            CAknControl::HandlePointerEventL(aPointerEvent);
            }
        return;
        }
    
    if ( aPointerEvent.iType == TPointerEvent::EButton1Down &&
        iCurrentLine == touchedLineIndex )
        {
        iExtension->iFocusedClicked = ETrue;
        }

    if ( (NumberOfLines() > 0 && !grabbingComponent) ||
        (IsForm() && !iIsEditable) )
        {     
        CEikCaptionedControl *currCtrl = (*iLines)[touchedLineIndex];
        MPointerEventObserver *obs = currCtrl->PointerEventObserver();
        TBool ret = ETrue;
        if (obs)
            {
            iExtension->iFlags.Set( CDialogPageExtension::ELineHandlerCalled );
            ret = obs->PointerEvent(currCtrl, aPointerEvent);
            iExtension->iFlags.Clear( CDialogPageExtension::ELineHandlerCalled );
            }

        // first move highlight to correct dialog line
        if ( ret && touchedLineIndex != iCurrentLine )
            {   
            // activate line.          
            (*iLines)[touchedLineIndex]->ActivateL();              

            // focus line if it is possible, PointerUp have not cause scrolling. 
            if ( LineIsFocusable(touchedLineIndex) && 
                aPointerEvent.iType != TPointerEvent::EButton1Up )
                {    
                focusItem = ETrue;
                                        
                CEikCaptionedControl* newLine = (*iLines)[touchedLineIndex];
                const TInt controlType(newLine->iControlType);
                 
                // all other than colorselection grid or popupfield does just move highlight. 
                // CSelGrid have also focus to clicked color    
                if ( !newLine->ControlIsAColourSelGrid(controlType) &&
                    !newLine->ControlIsAPopfield(controlType) )
                    {                    
                    callDefaultImplementation = EFalse;         
                    }
                }
            } 
        }
    
    // If the stylus is dragged to a new line, focus that line and
    // cancel the "Focused line clicked" mode (if any) for the next
    // stylus up event (then no MSK press will be emulated)
    if ( ( aPointerEvent.iType == TPointerEvent::EDrag || 
           aPointerEvent.iType == TPointerEvent::EButtonRepeat ) && 
           touchedLineIndex != iCurrentLine )
        {
        if ( !(*iLines)[touchedLineIndex]->IsNonFocusing() )
            {
            focusItem = ETrue;
            }
            
        iExtension->iFocusedClicked = EFalse;
        }

    // Click handling
    
    TBool mskPress = EFalse;
    // If the stylus is up above already focused line - emulate an MSK press
    if ( iFormControl && !iIsEditable && // in view mode
        aPointerEvent.iType == TPointerEvent::EButton1Up &&
        touchedLineIndex == iCurrentLine &&
        iExtension->iFocusedClicked )
        {
        mskPress = ETrue;
        iExtension->iFocusedClicked = EFalse;
        }

    /**
    * The local @c destroyed variable keeps track of the object destroyed state.
    */
    TBool destroyed = EFalse;
        
    if ( callDefaultImplementation )
        {
        CEikCaptionedControl* currentLine = (*iLines)[touchedLineIndex];
        const TInt controlType(currentLine->iControlType);
        
        iExtension->iDestroyedPtr = &destroyed;
        if ( currentLine->ControlIsAPopfield(controlType) ) 
            {
            if(aPointerEvent.iType == TPointerEvent::EButton1Down)
                {
                currentLine->HandlePointerEventL(aPointerEvent);
                iExtension->iCapturingItem = touchedLineIndex;       
                }
            else if(aPointerEvent.iType == TPointerEvent::EButton1Up)
                {
                currentLine->HandlePointerEventL(aPointerEvent);  
                }
            }
        else
            {            
            CCoeControl::HandlePointerEventL(aPointerEvent);        
            }
        if ( !destroyed )
            {
            iExtension->iDestroyedPtr = NULL;
            }
        else
            {
            return;
            }
        }

    if (iCurrentLine >= 0)
        { 
        CEikCaptionedControl *ctrl = (*iLines)[iCurrentLine];
        const TInt ctrlType(ctrl->iControlType);
        if (ctrl->ControlIsAPopfield(ctrlType))
            {
            CAknPopupField::EAknPopupFieldSelectionMode mode = ((CAknPopupField*)ctrl->iControl)->SelectionMode();
            if (mode == CAknPopupField::EAknPopupFieldSelectionListMode)
                {
                focusItem = EFalse;
                }
            }
        }
        
    TBool clear = EFalse;
    if ( PageContainer()->PageSelector()->Dialg()->Extension()->iPublicFlags.IsSet( CEikDialogExtension::EUseVirtualInput ) )
        {
        clear = ETrue;
        }
        
    if ( focusItem || iExtension->iFocusedClicked)
        {
        iExtension->HandleFormFeedback( this, aPointerEvent, touchedLineIndex, iCurrentLine );
        }
                
    if ( focusItem )
        {
        PrepareForFocusTransitionL();
        
        (*iLines)[iCurrentLine]->ScrollBackEditor();
        ShowFocus( EFalse, EFalse );
        iCurrentLine = touchedLineIndex;
        ShowFocus( ETrue, EFalse );        
        ExposeLine( iCurrentLine, EFalse );
        LineChangedL((*iLines)[touchedLineIndex]->iId);
        }

    else if (iPageObserver && grabbingComponent && aPointerEvent.iType == TPointerEvent::EButton1Up)
        { 
        iPageObserver->HandleDialogPageEventL(MEikDialogPageObserver::EDialogPageTapped);
        }
    
    if (mskPress)
        {
        TKeyEvent key;
        key.iCode=EKeyOK;
        key.iModifiers=0;
        key.iRepeats = 0;
        CEikonEnv::Static()->SimulateKeyEventL(key, EEventKey);
        // SimulateKeyEventL has to be last, because it can
        // possibly delete the dialog.. Must not do anything
        // to the dialog after the call.
        }

    if ( clear )
        {
        PageContainer()->PageSelector()->Dialg()->Extension()->iPublicFlags.Clear( CEikDialogExtension::EDelayedExit );
        }
    }

void CEikDialogPage::SetScbState(TBool aExternal)
    {
    iExtension->iExternalScrollbar = aExternal;
    }
    
TBool CEikDialogPage::ScbState() const
    {
    return iExtension->iExternalScrollbar;
    }

//
// CEikDialogPageContainer.
//

CEikDialogPageContainer::~CEikDialogPageContainer()
    {
    AKNTASHOOK_REMOVE();
    delete iAnimation;
    if(iPageArray)
        iPageArray->ResetAndDestroy();
    delete iPageArray;
    delete iSBFrame;
    }

CEikDialogPageContainer* CEikDialogPageContainer::NewL(const CCoeControl& aParent,MEikDialogPageObserver* aPageObserver)
    {
    CEikDialogPageContainer* self=CEikDialogPageContainer::NewLC(aParent,aPageObserver);
    CleanupStack::Pop();
    return self;
    }

CEikDialogPageContainer* CEikDialogPageContainer::NewLC(const CCoeControl& aParent,MEikDialogPageObserver* aPageObserver)
    {
    CEikDialogPageContainer* self=new(ELeave) CEikDialogPageContainer(aPageObserver);
    CleanupStack::PushL(self);
    self->ConstructL(aParent);
    AKNTASHOOK_ADDL( self, "CEikDialogPageContainer" );
    return self;
    }

CEikDialogPageContainer::CEikDialogPageContainer(MEikDialogPageObserver* aPageObserver)
    : iPageObserver(aPageObserver),iActivePage(0), iForm(EFalse)
    {
    SetHitTest( this );
    }

void CEikDialogPageContainer::CommonConstructL(const CCoeControl& aParent)
    {
    iContext=this;
    SetContainerWindowL( aParent );
    CreatePageArrayL();
    }

void CEikDialogPageContainer::ConstructL(const CCoeControl& aParent)
    {
    CommonConstructL(aParent);
    }

void CEikDialogPageContainer::ConstructFromResourceL(TResourceReader& aReader,const CCoeControl& aParent)
    {
    CommonConstructL(aParent);

    const TInt numPages=aReader.ReadInt16();
    for (TInt ii=0;ii<numPages;ii++)
        {
        AddPageL(ii,aReader);
        }
    }

void CEikDialogPageContainer::CreatePageArrayL()
    {
    iPageArray=new(ELeave) CArrayPtrFlat<CEikDialogPage>(KPageArrayGranularity);
    }

void CEikDialogPageContainer::CreateScrollBarL(const CCoeControl& aParent)
    {
    if (!iSBFrame) 
        {
        iSBFrame=new(ELeave) CEikScrollBarFrame((CCoeControl*)&aParent, NULL, ETrue);
        iSBFrame->CreateDoubleSpanScrollBarsL(ETrue, EFalse, ETrue, EFalse); // window owning scrollbar
        iSBFrame->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto);
        iSBFrame->SetScrollBarFrameFlags(CEikScrollBarFrame::EVVisible);
        iSBFrame->DrawBackground( EFalse, EFalse );
        }
    }

void CEikDialogPageContainer::SetActivePageByIdL(TInt aPageId)
    {
    // ToDo : unroll this loop
    const TInt numPages=iPageArray->Count();
    for (TInt ii=0;ii<numPages;ii++)
        {
        CEikDialogPage* thisPage=(*iPageArray)[ii];
        if (thisPage->PageId()==aPageId)
            {
            if (iActivePage>=0)
                (*iPageArray)[iActivePage]->SetInactiveL();
            thisPage->SetActiveAndFocusL();
            if(iActivePage!=ii)
                {
                thisPage->ReportPageChangedL();
                iActivePage=ii;
                }
            return;
            }
        }

    ASSERT(EFalse); // aPageId not found.
    }

void CEikDialogPageContainer::SetActivePageByIndexL(TInt aPageIndex)
    {
    const TInt numPages=iPageArray->Count();
    
    if(aPageIndex>=0 && aPageIndex<numPages)
        {
        CArrayPtr<CEikDialogPage>& pageArray = *iPageArray;
        if (iActivePage>=0)
            pageArray[iActivePage]->SetInactiveL();
        pageArray[aPageIndex]->SetActiveAndFocusL();
        if(iActivePage!=aPageIndex)
            {
            pageArray[aPageIndex]->ReportPageChangedL();
            iActivePage=aPageIndex;
            }
        return;
        }

    ASSERT(EFalse); // aPageIndex not found.
    }

TInt CEikDialogPageContainer::ActivateFirstPageL()
    {
    // Activate first page that isn't dimmed.
    // SetToolTips() ;
    const TInt numPages=iPageArray->Count();
    for (TInt ii=0;ii<numPages;ii++)
        {
        CEikDialogPage* thisPage=(*iPageArray)[ii];
        if (!(thisPage->IsDimmed()))
            {
            if (iActivePage>=0)
                (*iPageArray)[iActivePage]->SetInactiveL();
            thisPage->SetActiveAndFocusL();
            if(iActivePage!=ii)
                {
                thisPage->ReportPageChangedL();
                iActivePage=ii;
                }
            return thisPage->PageId();
            }
        }

    // All dimmed, so activate first.
    CEikDialogPage* firstPage=(*iPageArray)[0];
    if (iActivePage>=0)
        (*iPageArray)[iActivePage]->SetInactiveL();
    firstPage->SetActiveAndFocusL();    
    if(iActivePage!=0)
        {
        firstPage->ReportPageChangedL();
        iActivePage=0;
        }
    return firstPage->PageId();
    }

TInt CEikDialogPageContainer::PageId(TInt aIndex) const
 
    {
    return (*iPageArray)[aIndex]->PageId();
    }

TInt CEikDialogPageContainer::PageIdFromLineId(TInt aLineId) const
    {
    const TInt numPages=iPageArray->Count();
    for (TInt ii=0;ii<numPages;ii++)
        {
        CEikDialogPage* thisPage=(*iPageArray)[ii];
        if (thisPage->OwnsLine(aLineId))
            return thisPage->PageId();
        }

    return KErrNotFound;
    }

TBool CEikDialogPageContainer::SetInitialFocus()
    {
    TBool pageAcceptedFocus=(*iPageArray)[iActivePage]->SetInitialFocus();

    if (pageAcceptedFocus)
        SetFocus(ETrue,ENoDrawNow);

    return pageAcceptedFocus;
    }

void CEikDialogPageContainer::AddPageL(TInt aPageId)
    {
    CEikDialogPage* newPage=CEikDialogPage::NewLC(aPageId,Window(),*iSBFrame,*this,iPageObserver);
    newPage->SetObserver(Observer());
    newPage->MakeVisible(EFalse);
    if(iPageArray->Count())
        newPage->MakeVisible(EFalse);
    iPageArray->AppendL(newPage);
    CleanupStack::Pop();
    newPage->SetPageContainer(this);
    }

void CEikDialogPageContainer::AddPageL(TInt aPageId,TResourceReader& aReader)
    {
    CEikDialogPage* newPage=CEikDialogPage::NewLC(aPageId,Window(),*iSBFrame,*this,iPageObserver,aReader);
    newPage->SetObserver(Observer());
    newPage->CopyControlContextFrom(this);
    if(iPageArray->Count())
        newPage->MakeVisible(EFalse);
    iPageArray->AppendL(newPage);
    CleanupStack::Pop();
    newPage->SetPageContainer(this);
    }

CEikCaptionedControl* CEikDialogPageContainer::Line(TInt aLineId) const
    {
    CEikCaptionedControl* line=LineOrNull(aLineId);
    if (line)
        return line;

    ASSERT(EFalse); // Not found.
    return NULL;
    }

CEikCaptionedControl* CEikDialogPageContainer::LineOrNull(TInt aLineId) const
    {
    CEikCaptionedControl* line=NULL;
    const TInt numPages=iPageArray->Count();
    for (TInt ii=0;ii<numPages;ii++)
        {
        line=(*iPageArray)[ii]->LineOrNull(aLineId);
        if (line)
            return line;
        }

    return NULL; // Not found.
    }

CEikCaptionedControl* CEikDialogPageContainer::CurrentLine() const
    {
    if(iActivePage>=0)
        return (*iPageArray)[iActivePage]->CurrentLine();
    else
        return NULL;
    }

void CEikDialogPageContainer::SetPageDensePacked(TInt aPageId,TBool aDensePacked)
    {
    (*iPageArray)[PageIndex(aPageId)]->SetDensePacking(aDensePacked);
    }

void CEikDialogPageContainer::SetAllPagesDensePacked(TBool aDensePacked)
    {
    const TInt numPages=iPageArray->Count();
    for (TInt ii=0;ii<numPages;ii++)
        (*iPageArray)[ii]->SetDensePacking(aDensePacked);
    }

void CEikDialogPageContainer::SetPageDimmed(TInt aPageId,TBool aDimmed,TDrawNow aDrawNow)
    {
    CEikDialogPage* pageToDim=(*iPageArray)[PageIndex(aPageId)];
    pageToDim->SetDimmed(aDimmed);
    if (aDrawNow==EDrawNow)
        pageToDim->DrawNow();
    }

TInt CEikDialogPageContainer::PageIndex(TInt aPageId) const
    {
    const TInt numPages=iPageArray->Count();
    for (TInt ii=0;ii<numPages;ii++)
        {
        if ((*iPageArray)[ii]->PageId()==aPageId)
            return ii;
        }

    return KErrNotFound;
    }

TInt CEikDialogPageContainer::LineId(const CCoeControl& aControl) const
    {
    const TInt numPages=iPageArray->Count();
    for (TInt ii=0;ii<numPages;ii++)
        {
        TInt thisId=(*iPageArray)[ii]->LineId(aControl);
        if (thisId!=KErrNotFound)
            return thisId;
        }

    return KErrNotFound;
    }

TBool CEikDialogPageContainer::IsActivePageDimmed() const
    {
    return (*iPageArray)[iActivePage]->IsDimmed();
    }

void CEikDialogPageContainer::InsertLineL(TInt aPosition,TInt aPageId,TInt aResourceId)
    {
    TInt pageIndex;

    if (aPageId==0)
        pageIndex=iActivePage;
    else
        pageIndex=PageIndex(aPageId);

    (*iPageArray)[pageIndex]->InsertLineL(aPosition,aResourceId);
    }

void CEikDialogPageContainer::DeleteLine(TInt aLineId, TBool aRedraw)
    {
    (*iPageArray)[PageIndex(PageIdFromLineId(aLineId))]->DeleteLine(aLineId, aRedraw);
    }

void CEikDialogPageContainer::AdjustAllIds(TInt aPageId,TInt aControlIdDelta)
    {
    (*iPageArray)[PageIndex(aPageId)]->AdjustAllIds(aControlIdDelta);
    }

CCoeControl* CEikDialogPageContainer::CreateLineByTypeL(const TDesC& aCaption,TInt aLineId,TInt aControlType,TAny* aReturnValue)
    {
    return (*iPageArray)[iActivePage]->CreateLineByTypeL(aCaption,aLineId,aControlType,aReturnValue);
    }

CCoeControl* CEikDialogPageContainer::CreateLineByTypeL(const TDesC& aCaption,TInt aPageId,TInt aLineId,TInt aControlType,TAny* aReturnValue)
    {
    TInt pageIndex = PageIndex(aPageId);
    ASSERT(pageIndex >= 0 && (*iPageArray)[pageIndex]);
    CCoeControl* control=(*iPageArray)[pageIndex]->CreateLineByTypeL(aCaption,aLineId,aControlType,aReturnValue);
    return control;
    }

TInt CEikDialogPageContainer::FocusLineL(TInt aLineId)
//
// If a page change is required, returns the new page index.
// Else returns -1.
//
    {
    // Try active page first.
    TInt lineFocused=(*iPageArray)[iActivePage]->FocusLineL(aLineId);
    if (lineFocused==KErrNone)
        return -1;

    // Line not found.
    ASSERT(EFalse);
    return EFalse;
    }

TInt CEikDialogPageContainer::FindPageIndexForLineId(TInt aLineId)
//
// If a page change is required, returns the new page index.
// Else returns -1.
    {
    // Try active page first.
    TInt lineIndex=(*iPageArray)[iActivePage]->LineIndex(aLineId);
    if (lineIndex!=KErrNotFound)
        return -1;

    const TInt numPages=iPageArray->Count();
    for (TInt ii=0;ii<numPages;ii++)
        {
        CEikDialogPage* thisPage=(*iPageArray)[ii];
        
        if (ii!=iActivePage)
            lineIndex=thisPage->LineIndex(aLineId);

        if (lineIndex!=KErrNotFound)
            {
            return ii;
            }
        }

    // Line not found.
    ASSERT(EFalse);
    return EFalse;
    }

TInt CEikDialogPageContainer::FocusedLineId() const
    {
    return (*iPageArray)[iActivePage]->FocusedLineId();
    }

void CEikDialogPageContainer::GetAutoValues()
    {
    const TInt numPages=iPageArray->Count();
    for (TInt ii=0;ii<numPages;ii++)
        (*iPageArray)[ii]->GetAutoValues();
    }

void CEikDialogPageContainer::Draw(const TRect& /*aRect*/) const
    {
    }

TInt CEikDialogPageContainer::NumPages() const
    {
    return iPageArray->Count();
    }

void CEikDialogPageContainer::SizeChanged()
    {
    TRect rect( Rect() );
    const TInt numPages = iPageArray->Count();
    
    for ( TInt i = 0; i < numPages; ++i )
        {
        (*iPageArray)[i]->SetRect( rect );
        }
    }

TKeyResponse CEikDialogPageContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    return (*iPageArray)[iActivePage]->OfferKeyEventL(aKeyEvent,aType);
    }

TKeyResponse CEikDialogPageContainer::OfferUpDownKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType,CEikDialogPage::TFocusNavigationMode aFocusNavigationMode)
    {
    return (*iPageArray)[iActivePage]->OfferUpDownKeyEventL(aKeyEvent,aType,aFocusNavigationMode);
    }

TInt CEikDialogPageContainer::ActivePageId() const
    {
    return (*iPageArray)[iActivePage]->PageId();
    }

TInt CEikDialogPageContainer::ActivePageIndex() const
    {
    return iActivePage;
    }

TSize CEikDialogPageContainer::MinimumSize()
    {
//  The DPC reports a minimum size that is the max of all its contained DPs, independently 
//  for height and width

    TSize minSize(0,0);

    TInt numPages=iPageArray->Count();
    for (TInt ii=0;ii<numPages;ii++)
        {
        TSize thisPageSize((*iPageArray)[ii]->MinimumSize());
        if (thisPageSize.iWidth>minSize.iWidth)
            minSize.iWidth=thisPageSize.iWidth;
        if (thisPageSize.iHeight>minSize.iHeight)
            minSize.iHeight=thisPageSize.iHeight;
        }

//  Comment by RSD 11.09.2001: The following looks like the min size is never allowed to 
//  shrink...
    minSize.iHeight=Max(minSize.iHeight,iSize.iHeight);
    minSize.iWidth=Max(minSize.iWidth,iSize.iWidth);
    return minSize;
    }

void CEikDialogPageContainer::PrepareForFocusLossL()
    {
    (*iPageArray)[iActivePage]->PrepareForFocusLossL();
    }

TInt CEikDialogPageContainer::CountComponentControls() const
    {
    TInt i = 0;
    if (iSBFrame) 
        i = iSBFrame->CountComponentControls();
    return (iActivePage>=0 ? 1 : 0) + i;
    }

CCoeControl* CEikDialogPageContainer::ComponentControl(TInt aIndex) const
    {
    if (aIndex==0 && iActivePage>=0)
        return (*iPageArray)[iActivePage];
    
    __ASSERT_ALWAYS(iSBFrame, User::Invariant());
   
    return iSBFrame->ComponentControl(aIndex-(iActivePage>=0?1:0));
    }

TSize CEikDialogPageContainer::PreferredSize(const TSize& aMaxSize) const
    {
    TSize preferredSize(0,0);

    const TInt numPages=iPageArray->Count();
    for (TInt ii=0;ii<numPages;ii++)
        {
        TSize thisPageSize((*iPageArray)[ii]->PreferredSize());
        if (thisPageSize.iWidth>preferredSize.iWidth)
            preferredSize.iWidth=thisPageSize.iWidth;
        if (thisPageSize.iHeight>preferredSize.iHeight)
            preferredSize.iHeight=thisPageSize.iHeight;
        }

    preferredSize.iWidth=Min(aMaxSize.iWidth,preferredSize.iWidth);

    return preferredSize;
    }

void CEikDialogPageContainer::ActivateL()
    {
    // Pass the activate event to child controls always.
    CCoeControl::ActivateL();
    //
    // Have to do this here instead of CEikCaptionedControl::ActivateL, because CaptionedControl has no
    // activateL overridden.
    const TInt numPages=iPageArray->Count();

    for (TInt ii=0;ii<numPages;ii++)
        {
        CEikDialogPage *page = (*iPageArray)[ii];
        TInt numLines = page->NumberOfLines();
        for(int i=0;i<numLines;i++)
            {
            CEikCaptionedControl *capCC = page->LineByIndex(i);
        
             if ( capCC->iIsFormControl && page->FindLineIndex(page->CurrentLine()) != i)
                 {

                 if (capCC->ControlIsAnEdwin(capCC->iControlType))
                     {
                     CEikEdwin *edwin = (CEikEdwin*)capCC->iControl;
                     TRAP_IGNORE(edwin->TextView()->SetDocPosL(0)
                           );
                     }
                 }
             }
         }  
    }

void CEikDialogPageContainer::FocusChanged(TDrawNow aDrawNow)
    {
    (*iPageArray)[iActivePage]->SetFocus(IsFocused(),aDrawNow);
    }

void CEikDialogPageContainer::PrepareContext(CWindowGc& /*aGc*/) const
    {
    }

void CEikDialogPageContainer::ResetLineMinimumSizes()
    {
    (*iPageArray)[iActivePage]->ResetLineMinimumSizes();
    }

TInt CEikDialogPageContainer::FindLineIndex(const CCoeControl& aControl) const
    {
    CCoeControl* nonConstControlPtr=CONST_CAST(CCoeControl*,&aControl);
    return (*iPageArray)[iActivePage]->FindLineIndex(nonConstControlPtr);
    }

TBool CEikDialogPageContainer::RotateFocusByL(TInt aDelta)
    {
    return (*iPageArray)[iActivePage]->RotateFocusByL(aDelta);
    }

TKeyResponse CEikDialogPageContainer::OfferHotKeysKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    return (*iPageArray)[iActivePage]->OfferHotKeysKeyEventL(aKeyEvent,aType);
    }

TBool CEikDialogPageContainer::TakesEnterKey()
    {
    return (*iPageArray)[iActivePage]->TakesEnterKey();
    }

CEikDialogPage* CEikDialogPageContainer::Page( TInt aPageID ) 
    {
    // Try returning index, not pageID
    if ( aPageID >=1 )
        return (*iPageArray)[ aPageID - 1 ] ;
    else
        // Single page only
        return ( *iPageArray )[ aPageID ] ;
    }

void CEikDialogPageContainer::SetEditableL( TBool aEditable )
    {
    iIsEditable=aEditable;
    (*iPageArray)[iActivePage]->SetEditableL( aEditable, ETrue ) ;
    (*iPageArray)[iActivePage]->UpdateScrollBarL();
    }

CEikFormAnim* CEikDialogPageContainer::AcquireAnim(
    TBool aAcquire, MEikFormAnimObserver* aObserver ) const
    {
    // You could add assertions here to make sure animation usage is exclusive
    // (animation must be unacquired before anyone can acquire it).
    // Unfortunately, CaptionedControl::SetCurrent usage is currently not
    // exclusive.
    if( iAnimation )
        {
        if( aAcquire )
            {
            iAnimation->SetObserver( aObserver );
            return iAnimation;
            }
        else // Unacquire
            {
            iAnimation->SetObserver( NULL );
            return NULL;
            }
        }

    return NULL;
    }

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 *
 * @internal
 * @since App-Framework_6.1
 */
#ifndef _DEBUG
void CEikDialogPageContainer::WriteInternalStateL(RWriteStream&) const
    {}
#else
void CEikDialogPageContainer::WriteInternalStateL(RWriteStream& aWriteStream) const
    {
    CCoeControl::WriteInternalStateL(aWriteStream);
    }
#endif

void CEikDialogPageContainer::HandleResourceChange(TInt aType)
    {
    // Animation is skin dependent, whenever skin changes animation changes
    // too.
    if( KAknsMessageSkinChange == aType )
        {
        if( iAnimation )
            {
            iAnimation->ReleaseAnimation();
            }
        }

    CCoeControl::HandleResourceChange(aType);

    if(aType==KEikDynamicLayoutVariantSwitch)
        {
        SizeChanged();
        }

    TInt numPages = iPageArray->Count();
    for (TInt ii=0; ii<numPages; ii++)
        {
        if (ii != iActivePage)      // active page already done by CCoeControl::HandleResourceChange()
            (*iPageArray)[ii]->HandleResourceChange(aType);
        }
    }

const CEikDialogPageSelector* CEikDialogPageContainer::PageSelector() const 
    {
    return iPageSelector;
    }

void CEikDialogPageContainer::SetPageSelector(const CEikDialogPageSelector* aPageSelector)
    {
    iPageSelector = aPageSelector;
    }

void CEikDialogPageContainer::SetPageFormSized()
    {
    iForm = ETrue;

    //
    // Form layout
    //
    
    /** Dialog page container and page have the same size */
    TRect mainPaneRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, mainPaneRect );
    mainPaneRect = TRect( mainPaneRect.Size() );    // Moving to point (0, 0)
    TAknLayoutRect formPaneLt;
    formPaneLt.LayoutRect( mainPaneRect, AknLayoutScalable_Avkon::listscroll_form_pane().LayoutLine() );
    formPaneLt.LayoutRect( formPaneLt.Rect(), AknLayoutScalable_Avkon::list_form_gen_pane().LayoutLine() );
    
    //
    // End of form layout
    //

    if ( formPaneLt.Rect() != Rect() )
        {
        // TODO: use static method to do variation between traditional scrolling and panning when available
        //SetRect( formPaneLt.Rect() );
        SetRect( mainPaneRect );
        }

    /** Only forms have line highlight animations. Animation creation is delayed
      * here.
      */
    if ( !iAnimation )
        {
        TRAPD( err, iAnimation = CEikFormAnim::NewL() );
        
        if ( KErrNone != err )
            {
            iAnimation = NULL;
            }
        }
    }

CEikScrollBarFrame* CEikDialogPageContainer::ScrollBar() const
    {
    return iSBFrame;
    }

TBool CEikDialogPageContainer::HitRegionContains( const TPoint& /*aPoint*/, const CCoeControl& /*aControl*/ ) const
    {
    if ( iActivePage >= 0 )
        {
        return !(*iPageArray)[iActivePage]->LineHandlerCalled();
        }
        
    return ETrue;
    }

