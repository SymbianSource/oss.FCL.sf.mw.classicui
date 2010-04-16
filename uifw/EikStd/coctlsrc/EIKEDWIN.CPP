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


#include <s32mem.h>
#include <s32file.h>
#include <s32std.h>
#include <fldinfo.h>
#include <basched.h>
#include <baclipb.h>
#include <txtglobl.h>
#include <eikdef.h>
#include <fldbase.h>
#ifndef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <txtrich.h>
#else
#include <txtrich.h>
#include <txtclipboard.h>
#include <uikon/eikdefmacros.h>
#include <uikon/eikenvinterface.h> 
#endif
#include <txtfmlyr.h>
#include <txtfrmat.h>
#include <frmtview.h>
#include <barsread.h>
#include <coecobs.h>
#include <coemain.h>
#include <eikedwin.pan>
#include <eikpanic.h>
#include <uikon.hrh>
#include <gulutil.h>
#include <eikenv.h>
#include <eikedwin.h>
#include <eikcoctl.rsg>
#include <avkon.rsg>
#include <gulcolor.h>
#include <eikirfty.h>
#include "LAFEDWIN.H"
#include <lafmain.h>
#include <uiklaf/private/lafenv.h>
#include <aknedsts.h>
#include <frmtlay.h>
#include <tagma.h>
#include <eiksvdef.h>
#include <AknUtils.h>
#include <fepipext.h>
#include <aknedformaccessor.h>
#include <coemop.h>
#include <AknSettingCache.h>
#include <aknenv.h>
#include <AknDef.h>
#include <AknsDrawUtils.h>
#include "aknedwincustomdrawprivate.h"
#include "aknedwindrawingmodifier.h"
#include "FromCursorModifierUtils.h"

#include <AknTasHook.h>
#include <FormCursorModifier.h>
#include <formcursormodifierint.h>
#include <biditext.h>
#include <bidivisual.h>
#include <AknBidiTextUtils.h>

#include "aknedwinphysicshandler.h"
#include "AknEdwinFormExtendedInterfaceProvider.h"
#include "AknNoMatchesIndicatorInlineTextSource.h"
#include "AknPhoneNumberInlineTextSource.h"
#include "AknRichTextPhoneNumberInlineTextSource.h"
#include "AknCompositeInlineTextSource.h"
#include <featmgr.h>
#include <aknconsts.h>
#include <AknPictographInterface.h>
#include <aknappui.h>
#include <jplangutil.h>
#include <AknSgcc.h>
#include <AknLayoutFont.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <aknextendedinputcapabilities.h>
#include <PUAcodes.hrh>
#include <AknFepInternalCRKeys.h> // KAknFepHashKeySelection
#include <eikrted.h>
#include <NumberGroupingCRKeys.h>
#include <aknpointereventsuppressor.h>
#include <aknnotedialog.h>
#include <AknFepGlobalEnums.h>

#include "smileymanager.h"
#include "smileycustomwrap.h"
#include <touchfeedback.h>

GLDEF_C void Panic(TEikEdwinPanic aPanic)
    {
    _LIT(KPanicCat,"EIKON-EDWIN");
    User::Panic(KPanicCat,aPanic);
    }

// For neutral character protection 
enum 
    {
    EEikEdwinLeftToRightMark = 0x200E,
    EEikEdwinRightToLeftMark = 0x200F 
    };

_LIT(KEikEdwinLeftToRightMark, "\x200E" );  // LRM
_LIT(KEikEdwinRightToLeftMark, "\x200F" );  // RLM

// Used by neutral protection code to extract small chunks of the editor at a time 
// while searching for strong characters.
const TInt KLengthAtATime(3);

// Constants for controlling the switching between band and full document formatting
const TInt KFullFormattingUpperThreshold=2000;      // Default initial value
const TInt KPartialFormattingLowerThreshold=1900;   // Default initial value
// This should be consistent with the difference between the two default limits:
const TInt KFormattingThresholdGap=100; 
// This should be significantly bigger than KFormattingThresholdGap (and certainly > 0):
const TInt KMinimumPartialFormattingLength=400; 
const TInt KMinimumFullFormattingLength=KMinimumPartialFormattingLength+KFormattingThresholdGap;

// Unicode sign for S60 "enter" symbol
const TInt KDownwardsArrowWithTipLeftwards  = 0x21B2;
const TInt KDownwardsArrowWithTipRightwards = 0x21B3;

// Unicode for euro sign
const TInt KEuroSign = 0x20AC;
const TInt KSegmSize = 1024;

const TInt KMicroSecondsDelay = 500000;

const TInt KNormalAnimPlayTimes = 2;
const TInt KInfiniteAnimPlayTimes = 0x7ffff;
const TInt KAdditionalPixels = 0x400;

const TInt KFullFormatLengthForSmiley = 5000;

//
// class CEikEdwin::CUndoBuffer
//

class CEikEdwin::CUndoBuffer : public CBase
    {
public:
    static CUndoBuffer* NewL();
    ~CUndoBuffer();
    CBufStore& Store() const;
    CStreamDictionary& Dictionary() const;
    TCursorSelection NewText() const;
    void SetNewText(const TCursorSelection& aSelection);
    TInt OldCursorPos() const;
    void SetOldCursorPos(TInt aPos);
private:
    void ConstructL();
private:
    CBufStore* iStore;
    CStreamDictionary* iDictionary;
    TCursorSelection iNewText;
    TInt iOldCursorPos;
    };

CEikEdwin::CUndoBuffer* CEikEdwin::CUndoBuffer::NewL()
    { // static
    CUndoBuffer* self=new(ELeave) CUndoBuffer;
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop();  // self
    return self;
    }

CEikEdwin::CUndoBuffer::~CUndoBuffer()
    {
    delete iStore;
    delete iDictionary;
    }

void CEikEdwin::CUndoBuffer::ConstructL()
    {
    iStore=CBufStore::NewL(512);
    iDictionary=CStreamDictionary::NewL();
    }

CBufStore& CEikEdwin::CUndoBuffer::Store() const
    {return *iStore;}
CStreamDictionary& CEikEdwin::CUndoBuffer::Dictionary() const
    {return *iDictionary;}
TCursorSelection CEikEdwin::CUndoBuffer::NewText() const
    {return iNewText;}
void CEikEdwin::CUndoBuffer::SetNewText(const TCursorSelection& aSelection)
    {iNewText=aSelection;}
TInt CEikEdwin::CUndoBuffer::OldCursorPos() const
    {return iOldCursorPos;}
void CEikEdwin::CUndoBuffer::SetOldCursorPos(TInt aPos)
    {iOldCursorPos=aPos;}

void CEikEdwin::CEikEdwinExtension::TAknEdwinPictographDrawer::DrawPictographArea()
    {
    }

//
// class CEikEdwinFepSupport
//

NONSHARABLE_CLASS(CEikEdwinFepSupport) : public CBase, public MCoeFepAwareTextEditor, public MCoeFepAwareTextEditor_Extension1, public TCoeInputCapabilities::MCoeFepSpecificExtensions
    {
    friend class CEikEdwin;
public:
    static CEikEdwinFepSupport* New(CEikEdwin& aEdwin);
    virtual ~CEikEdwinFepSupport();
    TBool IsHandledByFepL(TPointerEvent::TType aType, TUint aModifiers, TInt aDocumentPosition);
    /**
    * Set the input capabilities in the edwin fep support object. A copy of the input capabilities
    * is maintained in and owned by the fep support; 
    *
    * @param aInputCapabilities     Reference to desired input capabilities object
    */
    void SetInputCapabilitiesL(const TCoeInputCapabilities& aInputCapabilities);
    const TCoeInputCapabilities* InputCapabilities() const;
    void ConstructStateHolder();
    // from MCoeFepAwareTextEditor_Extension1
    void SetStateTransferingOwnershipL(CState* aState, TUid aTypeSafetyUid);
    CState* State(TUid aTypeSafetyUid); // this function does *not* transfer ownership

private:
    enum TPointerState
        {
        EPointerIsUp,
        EPointerIsDownStartingInsideInlineText,
        EPointerIsDownStartingOutsideInlineText
        };
    struct SPointerEventInInlineText
        {
        inline SPointerEventInInlineText(TPointerEvent::TType aType, TUint aModifiers, TInt aPositionInInlineText) :iType(aType), iModifiers(aModifiers), iPositionInInlineText(aPositionInInlineText) {}
        TPointerEvent::TType iType;
        TUint iModifiers;
        TInt iPositionInInlineText;
        };
private:
    CEikEdwinFepSupport(CEikEdwin& aEdwin);
    void UpdateTextViewAfterChangeInInlineTextL(TBool aParagraphContainingStartPositionOfInlineTextHasChangedFormat,TInt aNumberOfCharactersSuccessfullyDeleted,TInt aNumberOfCharactersSuccessfullyInserted,TInt aError);
    void UpdateTextViewAfterChangeInInlineTextL(TBool aParagraphContainingStartPositionOfInlineTextHasChangedFormat,TInt aNumberOfCharactersSuccessfullyDeleted,TInt aNumberOfCharactersSuccessfullyInserted,TInt aError,TInt aSelectionAnchorPosition);
    void ResetInternalState();

    // from MCoeFepAwareTextEditor
    virtual void StartFepInlineEditL(const TDesC& aInitialInlineText, TInt aPositionOfInsertionPointInInlineText, TBool aCursorVisibility, const MFormCustomDraw* aCustomDraw, MFepInlineTextFormatRetriever& aInlineTextFormatRetriever, MFepPointerEventHandlerDuringInlineEdit& aPointerEventHandlerDuringInlineEdit);
    virtual void UpdateFepInlineTextL(const TDesC& aNewInlineText, TInt aPositionOfInsertionPointInInlineText);
    virtual void SetInlineEditingCursorVisibilityL(TBool aCursorVisibility);
    virtual void CancelFepInlineEdit();
    virtual TInt DocumentLengthForFep() const;
    virtual TInt DocumentMaximumLengthForFep() const;
    virtual void SetCursorSelectionForFepL(const TCursorSelection& aCursorSelection);
    virtual void GetCursorSelectionForFep(TCursorSelection& aCursorSelection) const;
    virtual void GetEditorContentForFep(TDes& aEditorContent, TInt aDocumentPosition, TInt aLengthToRetrieve) const; // must cope with aDocumentPosition being outside the range 0 to DocumentLengthForFep()
    virtual void GetFormatForFep(TCharFormat& aFormat, TInt aDocumentPosition) const;
    virtual void GetScreenCoordinatesForFepL(TPoint& aLeftSideOfBaseLine, TInt& aHeight, TInt& aAscent, TInt aDocumentPosition) const;
    virtual void DoCommitFepInlineEditL();
    virtual MCoeFepAwareTextEditor_Extension1* Extension1(TBool& aSetToTrue);
    virtual void MCoeFepAwareTextEditor_Reserved_2();
    // from MCoeFepAwareTextEditor_Extension1
//  virtual void SetStateTransferingOwnershipL(CState* aState, TUid aTypeSafetyUid);
//  virtual CState* State(TUid aTypeSafetyUid);
    virtual void StartFepInlineEditL(TBool& aSetToTrue, const TCursorSelection& aCursorSelection, const TDesC& aInitialInlineText, TInt aPositionOfInsertionPointInInlineText, TBool aCursorVisibility, const MFormCustomDraw* aCustomDraw, MFepInlineTextFormatRetriever& aInlineTextFormatRetriever, MFepPointerEventHandlerDuringInlineEdit& aPointerEventHandlerDuringInlineEdit);
    virtual void SetCursorType(TBool& aSetToTrue, const TTextCursor& aTextCursor);
    virtual void MCoeFepAwareTextEditor_Extension1_Reserved_3();
    virtual void MCoeFepAwareTextEditor_Extension1_Reserved_4();
    // from TCoeInputCapabilities::MCoeFepSpecificExtensions
    virtual TBool IsValidCharacter(TInt aChar);
    virtual void MCoeFepSpecificExtensions_Reserved_1();
    virtual void MCoeFepSpecificExtensions_Reserved_2();


private:
    CEikEdwin& iEdwin;
    TCursorSelection iOriginalSelection;
    TInt iPositionOfInsertionPointInDocument;
    TInt iPositionOfInlineTextInDocument;
    TInt iLengthOfInlineText;
public: 
    const MFormCustomDraw* iOldCustomDraw; // does not own anything
    MTouchFeedback* iFeedback;
    TBool iSelectionIsCancel;
    TInt iMoveThumbFeedbackNeeded;
private:    
    MFepPointerEventHandlerDuringInlineEdit* iPointerEventHandlerDuringInlineEdit; // does not own anything
    SPointerEventInInlineText iLastPointerEventInInlineText;
    TPointerState iPointerState;
    TCoeInputCapabilities* iInputCapabilities;
    CState* iState;
    TUid iStateTypeSafetyUid;
    TInt iCharsDeleted;
    TInt iCharsInserted;
    TBool iShowCursor;
    };

CEikEdwinFepSupport* CEikEdwinFepSupport::New(CEikEdwin& aEdwin)
    {
    return new CEikEdwinFepSupport(aEdwin);
    }

CEikEdwinFepSupport::~CEikEdwinFepSupport()
    {
    delete iInputCapabilities;
    delete iState;
    }

TBool CEikEdwinFepSupport::IsHandledByFepL(TPointerEvent::TType aType,TUint aModifiers,TInt aDocumentPosition)
    {
    if (iPositionOfInlineTextInDocument>=0)
        {
        __ASSERT_DEBUG((iOriginalSelection.iCursorPos>=0) && (iOriginalSelection.iAnchorPos>=0) && (iPositionOfInsertionPointInDocument>=0) && (iPositionOfInlineTextInDocument>=0) && (iLengthOfInlineText>=0) && (iPointerEventHandlerDuringInlineEdit!=NULL),Panic(EEikPanicBadInlineEditingState1));
        const TInt positionOfFirstCharacterInDocumentAfterInlineText=iPositionOfInlineTextInDocument+iLengthOfInlineText;
        switch (aType)
            {
        case TPointerEvent::EDrag:
        case TPointerEvent::EButton1Up:
            if (iPointerState!=EPointerIsUp)
                {
                break;
                }
            // fall through (only will do this if no preceding TPointerEvent::EButton1Down occurred, either initially or since the previous TPointerEvent::EButton1Up event)
        case TPointerEvent::EButton1Down:
            if ((aDocumentPosition>=iPositionOfInlineTextInDocument) && (aDocumentPosition<=positionOfFirstCharacterInDocumentAfterInlineText))
                {
                iPointerState=EPointerIsDownStartingInsideInlineText;
                }
            else
                {
                iPointerState=EPointerIsDownStartingOutsideInlineText;
                }
            break;
#if defined(__GCC32__)
        default:
            break;
#endif
            }
        const TBool pointerIsDownStartingInsideInlineText=(iPointerState==EPointerIsDownStartingInsideInlineText);
        if (aType==TPointerEvent::EButton1Up)
            {
            iPointerState=EPointerIsUp;
            }
        if (pointerIsDownStartingInsideInlineText)
            {
            if (aDocumentPosition<iPositionOfInlineTextInDocument)
                {
                aDocumentPosition=iPositionOfInlineTextInDocument;
                }
            if (aDocumentPosition>positionOfFirstCharacterInDocumentAfterInlineText)
                {
                aDocumentPosition=positionOfFirstCharacterInDocumentAfterInlineText;
                }
            const TInt positionInInlineText=aDocumentPosition-iPositionOfInlineTextInDocument;
            if ((aType!=iLastPointerEventInInlineText.iType) || (aModifiers!=iLastPointerEventInInlineText.iModifiers) || (positionInInlineText!=iLastPointerEventInInlineText.iPositionInInlineText))
                {
                iLastPointerEventInInlineText.iType=aType;
                iLastPointerEventInInlineText.iModifiers=aModifiers;
                iLastPointerEventInInlineText.iPositionInInlineText=positionInInlineText;
                iPointerEventHandlerDuringInlineEdit->HandlePointerEventInInlineTextL(aType,aModifiers,positionInInlineText);
                }
            return ETrue;
            }
        }
#if defined(_DEBUG)
    else
        {
        __ASSERT_DEBUG((iOriginalSelection.iCursorPos<0) && (iOriginalSelection.iAnchorPos<0) && (iPositionOfInsertionPointInDocument<0) && (iPositionOfInlineTextInDocument<0) && (iLengthOfInlineText<0) && (iOldCustomDraw==NULL) && (iPointerEventHandlerDuringInlineEdit==NULL),Panic(EEikPanicBadInlineEditingState2));
        }
#endif
    return EFalse;
    }

// This method treats the input capabilities slightly oddly in order to avoid re-allocation of Heap
void CEikEdwinFepSupport::SetInputCapabilitiesL(const TCoeInputCapabilities& aInputCapabilities)
    {
    if (iInputCapabilities==NULL)
        {
        iInputCapabilities=new(ELeave) TCoeInputCapabilities(aInputCapabilities); // copy constructor
        }
    else
        {
        *iInputCapabilities=aInputCapabilities;  // Structure copy. OK for T class.
        }
    }

const TCoeInputCapabilities* CEikEdwinFepSupport::InputCapabilities() const
    {
    return iInputCapabilities;
    }

void CEikEdwinFepSupport::ConstructStateHolder()
    {
    iState = new CAknEdwinState(STATIC_CAST(MEikCcpuEditor*, &iEdwin));
    if (iState)
        static_cast<CAknEdwinState*>(iState)->SetObjectProvider(&iEdwin);
    }

#pragma warning (disable: 4355) // warning disabled: "'this' : used in base member initializer list"
CEikEdwinFepSupport::CEikEdwinFepSupport(CEikEdwin& aEdwin)
    :iEdwin(aEdwin),
     iOriginalSelection(-1,-1),
     iPositionOfInsertionPointInDocument(-1),
     iPositionOfInlineTextInDocument(-1),
     iLengthOfInlineText(-1),
     iOldCustomDraw(NULL),
     iFeedback(MTouchFeedback::Instance()),
     iSelectionIsCancel(EFalse),
     iMoveThumbFeedbackNeeded(EFalse),
     iPointerEventHandlerDuringInlineEdit(NULL),
     iLastPointerEventInInlineText((TPointerEvent::TType)-1,0,0),
     iPointerState(EPointerIsUp),
     iInputCapabilities(NULL)
    {
    __DECLARE_NAME(_S("CEikEdwinFepSupport"));
    }

#pragma warning (default: 4355) // warning disabled: "assignment within conditional expression"

void CEikEdwinFepSupport::UpdateTextViewAfterChangeInInlineTextL(TBool aParagraphContainingStartPositionOfInlineTextHasChangedFormat,TInt aNumberOfCharactersSuccessfullyDeleted,TInt aNumberOfCharactersSuccessfullyInserted,TInt aError)
    {
    UpdateTextViewAfterChangeInInlineTextL(aParagraphContainingStartPositionOfInlineTextHasChangedFormat,aNumberOfCharactersSuccessfullyDeleted,aNumberOfCharactersSuccessfullyInserted,aError,iPositionOfInsertionPointInDocument);
    }

void CEikEdwinFepSupport::UpdateTextViewAfterChangeInInlineTextL(TBool aParagraphContainingStartPositionOfInlineTextHasChangedFormat,TInt aNumberOfCharactersSuccessfullyDeleted,TInt aNumberOfCharactersSuccessfullyInserted,TInt aError,TInt aSelectionAnchorPosition)
    {
    TCursorSelection select( iPositionOfInsertionPointInDocument, aSelectionAnchorPosition );
    iEdwin.iTextView->SetPendingSelection( select );    
    
    select.iAnchorPos = iPositionOfInlineTextInDocument;
    select.iCursorPos = select.iAnchorPos + aNumberOfCharactersSuccessfullyInserted;
    if ( iEdwin.iEdwinExtension->iSmiley )
        { 
        TInt textChange( aNumberOfCharactersSuccessfullyInserted - aNumberOfCharactersSuccessfullyDeleted );
        if ( textChange == 0 )
            {
            if ( iCharsDeleted < aNumberOfCharactersSuccessfullyDeleted )
                {
                iEdwin.iEdwinExtension->iSmiley->HandleDeleteL( iPositionOfInlineTextInDocument,
                        aNumberOfCharactersSuccessfullyDeleted - iCharsDeleted );
                iCharsDeleted = aNumberOfCharactersSuccessfullyDeleted;
                }
            if ( iCharsInserted < aNumberOfCharactersSuccessfullyInserted )
                {
                iEdwin.iEdwinExtension->iSmiley->HandleInsertL( 
                        iPositionOfInlineTextInDocument, 
                        ( aNumberOfCharactersSuccessfullyInserted - iCharsInserted ) );
                iCharsInserted = aNumberOfCharactersSuccessfullyInserted;
                }
            }
        else
            {
            if ( textChange > 0 )
                {
                iEdwin.iEdwinExtension->iSmiley->HandleInsertL( 
                    select.iAnchorPos + aNumberOfCharactersSuccessfullyDeleted, 
                    textChange );
                }
            else if ( textChange < 0 )
                {
                iEdwin.iEdwinExtension->iSmiley->HandleDeleteL( aSelectionAnchorPosition,
                    textChange * -1 );
                }
            }
        }
    iEdwin.iTextView->HandleInsertDeleteL( select, aNumberOfCharactersSuccessfullyDeleted,
        aParagraphContainingStartPositionOfInlineTextHasChangedFormat );
    User::LeaveIfError(aError);
    iEdwin.SetScrollBarsL();
    iEdwin.DoReportEventL(MCoeControlObserver::EEventStateChanged);
    if (aParagraphContainingStartPositionOfInlineTextHasChangedFormat)
        {
        iEdwin.ReportEdwinEventL(MEikEdwinObserver::EEventFormatChanged);
        }    
    }

void CEikEdwinFepSupport::ResetInternalState()
    {
    iOriginalSelection.SetSelection(-1,-1);
    iPositionOfInsertionPointInDocument=-1;
    iPositionOfInlineTextInDocument=-1;
    iLengthOfInlineText=-1;
    iOldCustomDraw=NULL;
    iPointerEventHandlerDuringInlineEdit=NULL;
    }


void CEikEdwinFepSupport::StartFepInlineEditL(
      const TDesC& aInitialInlineText,
      TInt aPositionOfInsertionPointInInlineText,
      TBool aCursorVisibility,
      const MFormCustomDraw* aCustomDraw,
      MFepInlineTextFormatRetriever& aInlineTextFormatRetriever,
      MFepPointerEventHandlerDuringInlineEdit& aPointerEventHandlerDuringInlineEdit)
    {
    __ASSERT_ALWAYS(iPositionOfInlineTextInDocument<0,Panic(EEikPanicBadInlineEditingState3)); // assert that we're not currently inline editing
    __ASSERT_DEBUG((iOriginalSelection.iCursorPos<0) && (iOriginalSelection.iAnchorPos<0) && (iPositionOfInsertionPointInDocument<0) && (iPositionOfInlineTextInDocument<0) && (iLengthOfInlineText<0) && (iOldCustomDraw==NULL) && (iPointerEventHandlerDuringInlineEdit==NULL),Panic(EEikPanicBadInlineEditingState4));
    iEdwin.PerformRecordedOperationL();
    CCoeEnv::Static()->ForEachFepObserverCall(FepObserverHandleStartOfTransactionL);
    iEdwin.SetKeyboardRepeatRate(KAknEditorKeyboardRepeatRate);
    iEdwin.CheckNotReadOnlyL();
    iEdwin.iEdwinExtension->iInlineEditing = ETrue;
    iShowCursor = aCursorVisibility;
    CAknEdwinState* state( iEdwin.EditorState() );
    state->SetInlineEditSpan( TCursorSelection( 0, 0 ) );
    const TCursorSelection selection=iEdwin.Selection();
    iOriginalSelection=selection;
    iPositionOfInsertionPointInDocument=selection.iCursorPos;
    iPositionOfInlineTextInDocument=selection.LowerPos();
    iPointerEventHandlerDuringInlineEdit=&aPointerEventHandlerDuringInlineEdit;
    TBool paragraphContainingStartPositionOfInlineTextHasChangedFormat=EFalse;
    TInt numberOfCharactersSuccessfullyDeleted=0;
    TInt numberOfCharactersSuccessfullyInserted=0;
    // handle extended highlights

/* 
WARNING.  do not insert any leaving function calls after the iEdwin.iText->StartFepInlineEditL unless they are trapped
as this will call update-state problems.
*/
    TRAPD(error,
        {
        iEdwin.iTextView->ClearSelectionL();
        iEdwin.iText->StartFepInlineEditL(paragraphContainingStartPositionOfInlineTextHasChangedFormat,numberOfCharactersSuccessfullyDeleted,numberOfCharactersSuccessfullyInserted,iPositionOfInsertionPointInDocument,iPositionOfInlineTextInDocument+aPositionOfInsertionPointInInlineText,aInitialInlineText,iPositionOfInlineTextInDocument,selection.Length(),aInlineTextFormatRetriever);//);
        });
    if (error != KErrNone)
        { // cancel inline editing...
        ResetInternalState();
        User::LeaveIfError(error);
        }
    iLengthOfInlineText=numberOfCharactersSuccessfullyInserted;
    iOldCustomDraw=iEdwin.iLayout->CustomDraw();
    if (aCustomDraw)
        iEdwin.iLayout->SetCustomDraw(aCustomDraw);
/*
The scheme for this component is as follows:
There are 3 levels of call to StartFepInlineEdit (from FEP to here, to CEditable)
As each level contains its' own state to decide which mode it is in, complex issues arise upon a leave.

Basically, if there is a leave, then all three levels must NOT be in inline edit mode.
There are a number of possible ways of achieving this, but the simplest and most efficient has been 
chosen here.  The method which changes the state must occur after the last leaving call in that method
(NB if the state-changing method itself leaves, then this is ok).  That is to say "as soon as the lowest
level has entered inline edit mode, all three levels are committed to inline edit mode, as they cannot 
leave after this point".

Therefore, the two calls below are deliberately trapped (as if they leave it does not matter) 
*/

    TRAP_IGNORE(
        {
        UpdateTextViewAfterChangeInInlineTextL(paragraphContainingStartPositionOfInlineTextHasChangedFormat,numberOfCharactersSuccessfullyDeleted,numberOfCharactersSuccessfullyInserted,error);
        iEdwin.SetCursorVisibilityL(aCursorVisibility);
        });
    }

void CEikEdwinFepSupport::UpdateFepInlineTextL(const TDesC& aNewInlineText,TInt aPositionOfInsertionPointInInlineText)
    {
    __ASSERT_ALWAYS(iPositionOfInlineTextInDocument>=0,Panic(EEikPanicBadInlineEditingState5)); // assert that we're currently inline editing
    __ASSERT_DEBUG((iOriginalSelection.iCursorPos>=0) && (iOriginalSelection.iAnchorPos>=0) && (iPositionOfInsertionPointInDocument>=0) && (iPositionOfInlineTextInDocument>=0) && (iLengthOfInlineText>=0) && (iPointerEventHandlerDuringInlineEdit!=NULL),Panic(EEikPanicBadInlineEditingState6));
    TBool paragraphContainingStartPositionOfInlineTextHasChangedFormat=EFalse;
    TInt numberOfCharactersSuccessfullyDeleted=0;
    TInt numberOfCharactersSuccessfullyInserted=0;
    TRAPD(error,iEdwin.iText->UpdateFepInlineTextL(paragraphContainingStartPositionOfInlineTextHasChangedFormat,numberOfCharactersSuccessfullyDeleted,numberOfCharactersSuccessfullyInserted,iPositionOfInsertionPointInDocument,iPositionOfInlineTextInDocument+aPositionOfInsertionPointInInlineText,aNewInlineText));
    iLengthOfInlineText=numberOfCharactersSuccessfullyInserted;
    UpdateTextViewAfterChangeInInlineTextL(paragraphContainingStartPositionOfInlineTextHasChangedFormat,numberOfCharactersSuccessfullyDeleted,numberOfCharactersSuccessfullyInserted,error);
    iEdwin.ReportEdwinEventL( MEikEdwinObserver::EEventTextUpdate );
    }

void CEikEdwinFepSupport::SetInlineEditingCursorVisibilityL(TBool aCursorVisibility)
    {
    __ASSERT_ALWAYS(iPositionOfInlineTextInDocument>=0,Panic(EEikPanicBadInlineEditingState7)); // assert that we're currently inline editing
    __ASSERT_DEBUG((iOriginalSelection.iCursorPos>=0) && (iOriginalSelection.iAnchorPos>=0) && (iPositionOfInsertionPointInDocument>=0) && (iPositionOfInlineTextInDocument>=0) && (iLengthOfInlineText>=0) && (iPointerEventHandlerDuringInlineEdit!=NULL),Panic(EEikPanicBadInlineEditingState8));
    iEdwin.SetCursorVisibilityL(aCursorVisibility);
    iShowCursor = aCursorVisibility;
    }

void CEikEdwinFepSupport::CancelFepInlineEdit()
    {
    if (iPositionOfInlineTextInDocument>=0)
        {
        __ASSERT_DEBUG((iOriginalSelection.iCursorPos>=0) && (iOriginalSelection.iAnchorPos>=0) && (iPositionOfInsertionPointInDocument>=0) && (iPositionOfInlineTextInDocument>=0) && (iLengthOfInlineText>=0) && (iPointerEventHandlerDuringInlineEdit!=NULL),Panic(EEikPanicBadInlineEditingState11));
        iEdwin.iEdwinExtension->iInlineEditing = EFalse;
        iCharsInserted = 0;
        iCharsDeleted = 0;
        TBool paragraphContainingStartPositionOfInlineTextHasChangedFormat;
        TInt numberOfCharactersSuccessfullyDeleted( 0 );
        TInt numberOfCharactersSuccessfullyInserted( 0 );
        iEdwin.iText->CancelFepInlineEdit(paragraphContainingStartPositionOfInlineTextHasChangedFormat,numberOfCharactersSuccessfullyDeleted,numberOfCharactersSuccessfullyInserted,iPositionOfInsertionPointInDocument,iOriginalSelection.iCursorPos);
        TRAP_IGNORE(
            {
            UpdateTextViewAfterChangeInInlineTextL( 
                paragraphContainingStartPositionOfInlineTextHasChangedFormat, 
                numberOfCharactersSuccessfullyDeleted, 
                numberOfCharactersSuccessfullyInserted, KErrNone, 
                iOriginalSelection.iAnchorPos );
            if ( iEdwin.IsFocused() )
                {
                iEdwin.SetCursorVisibilityL( ETrue );
                }
            });        
        iEdwin.iLayout->SetCustomDraw(iOldCustomDraw);
        ResetInternalState();
        if ( numberOfCharactersSuccessfullyDeleted || numberOfCharactersSuccessfullyInserted )
            {
            TRAP_IGNORE( iEdwin.ReportEdwinEventL( MEikEdwinObserver::EEventTextUpdate ) );
            }
        }
#if defined(_DEBUG)
    else
        {
        __ASSERT_DEBUG((iOriginalSelection.iCursorPos<0) && (iOriginalSelection.iAnchorPos<0) && (iPositionOfInsertionPointInDocument<0) && (iPositionOfInlineTextInDocument<0) && (iLengthOfInlineText<0) && (iOldCustomDraw==NULL) && (iPointerEventHandlerDuringInlineEdit==NULL),Panic(EEikPanicBadInlineEditingState12));
        }
#endif
    }

TInt CEikEdwinFepSupport::DocumentLengthForFep() const
    {
    return iEdwin.TextLength();
    }

TInt CEikEdwinFepSupport::DocumentMaximumLengthForFep() const
    {
    return iEdwin.iTextLimit;
    }

void CEikEdwinFepSupport::SetCursorSelectionForFepL(const TCursorSelection& aCursorSelection)
    {
    TInt cursorPos( aCursorSelection.iCursorPos );
    TInt anchorPos( aCursorSelection.iAnchorPos );
    if ( iEdwin.IsSmileyEnabled() )
        {  
        CSmileyManager* smiley( iEdwin.iEdwinExtension->iSmiley );
        TInt oldPos = ( cursorPos == anchorPos ) ? iEdwin.CursorPos() : anchorPos; 
        smiley->HandleSetCursor( oldPos, cursorPos );       
        if ( aCursorSelection.iCursorPos == aCursorSelection.iAnchorPos )
            {
            anchorPos = cursorPos;
            }
        else
            {
            smiley->HandleSetCursor( cursorPos, anchorPos );
            }
        }
	iEdwin.SetSelectionL( cursorPos, anchorPos );
    iEdwin.ReportEdwinEventL(MEikEdwinObserver::EEventNavigation);
    }

void CEikEdwinFepSupport::GetCursorSelectionForFep(TCursorSelection& aCursorSelection) const
    {
    aCursorSelection=iEdwin.Selection();
    }

void CEikEdwinFepSupport::GetEditorContentForFep(TDes& aEditorContent,TInt aDocumentPosition,TInt aLengthToRetrieve) const
    {
    TInt length( Min( aLengthToRetrieve, iEdwin.TextLength() - aDocumentPosition ) );
    iEdwin.iText->Extract( aEditorContent, aDocumentPosition, length );
    if ( iEdwin.IsSmileyEnabled() )
        {
        CSmileyManager* smiley( iEdwin.iEdwinExtension->iSmiley );
        CAknEdwinState* state( iEdwin.EditorState() );
        if ( state )
            {
            TCursorSelection inlineText( state->CurrentInlineEditSpan() );
            if ( aDocumentPosition >= inlineText.LowerPos() && 
                aDocumentPosition + length <= inlineText.HigherPos() )
                {
                iEdwin.iEdwinExtension->iSmiley->ConvertTextForSmileyL(
                    aDocumentPosition, aEditorContent, EFalse );
                }
            }
        TBool prevIsCode( EFalse );
        for ( TInt i( 0 ); i < length; i++ )
            {
            if ( aEditorContent[i] == CSmileyManager::KCompensateChar )
                {
                if ( i == 0 )
                    {
                    prevIsCode = ( CSmileyManager::IsSmileyCode( 
                        smiley->SmileyCodeByPos( aDocumentPosition ) ) );
                    }
                if ( prevIsCode )
                    {
                    aEditorContent[i] = CSmileyManager::KPlaceHolder;
                    }
                }
            else
                {
                prevIsCode = CSmileyManager::IsSmileyCode( aEditorContent[i] );
                }
            }
        }
    }

void CEikEdwinFepSupport::GetFormatForFep(TCharFormat& aFormat,TInt aDocumentPosition) const
    {
    TCharFormatMask notUsed;
    STATIC_CAST(CGlobalText*,iEdwin.iText)->GetCharFormat(aFormat,notUsed,aDocumentPosition,(aDocumentPosition==iEdwin.TextLength())? 0: 1);
    }

void CEikEdwinFepSupport::GetScreenCoordinatesForFepL(TPoint& aLeftSideOfBaseLine,TInt& aHeight,TInt& aAscent,TInt aDocumentPosition) const
    {
    aDocumentPosition %= ( iEdwin.iText->DocumentLength() + 1 );    
    iEdwin.iTextView->DocPosToXyPosL(aDocumentPosition,aLeftSideOfBaseLine);
    aLeftSideOfBaseLine+=iEdwin.DrawableWindow()->InquireOffset(iEdwin.iCoeEnv->RootWin()); // make position "absolute" (i.e. not relative to the window that iEdwin is using) - note that *any* group window can be passed into InquireOffset to return the desired result, it doesn't have to be an ancestor of the window being used by iEdwin (i.e. this line of code does *not* make the assumption that iEdwin is (even indirectly) attached to iCoeEnv->RootWin())
    iEdwin.iLayout->GetCharacterHeightAndAscentL(aDocumentPosition,aHeight,aAscent);
    }

MCoeFepAwareTextEditor_Extension1* CEikEdwinFepSupport::Extension1(TBool& aSetToTrue)
    {
    aSetToTrue=ETrue;
    return STATIC_CAST(MCoeFepAwareTextEditor_Extension1*, this);
    }

void CEikEdwinFepSupport::DoCommitFepInlineEditL()
    {
    __ASSERT_ALWAYS(iPositionOfInlineTextInDocument>=0,Panic(EEikPanicBadInlineEditingState9)); // assert that we're currently inline editing
    __ASSERT_DEBUG((iOriginalSelection.iCursorPos>=0) && (iOriginalSelection.iAnchorPos>=0) && (iPositionOfInsertionPointInDocument>=0) && (iPositionOfInlineTextInDocument>=0) && (iLengthOfInlineText>=0) && (iPointerEventHandlerDuringInlineEdit!=NULL),Panic(EEikPanicBadInlineEditingState10));
    iEdwin.iEdwinExtension->iInlineEditing = EFalse;
    iCharsInserted = 0;
    iCharsDeleted = 0;
    TBool paragraphContainingStartPositionOfInlineTextHasChangedFormat=EFalse;
    TInt numberOfCharactersSuccessfullyDeleted=0;
    TInt numberOfCharactersSuccessfullyInserted=0;
    TRAPD(error1,iEdwin.iText->CommitFepInlineEditL(paragraphContainingStartPositionOfInlineTextHasChangedFormat,numberOfCharactersSuccessfullyDeleted,numberOfCharactersSuccessfullyInserted,iPositionOfInsertionPointInDocument,iPositionOfInsertionPointInDocument));
    TRAPD(error2,UpdateTextViewAfterChangeInInlineTextL(paragraphContainingStartPositionOfInlineTextHasChangedFormat,numberOfCharactersSuccessfullyDeleted,numberOfCharactersSuccessfullyInserted,error1));
    TCursorSelection select( iPositionOfInlineTextInDocument + 
        numberOfCharactersSuccessfullyInserted, iPositionOfInlineTextInDocument );
    if (iEdwin.iUndoStore!=NULL)
        {
        iEdwin.iUndoStore->SetNewText( select );
        }    
    if ( iEdwin.IsSmileyEnabled() )
        {
        CAknEdwinState* state( iEdwin.EditorState() );
        TCursorSelection inlineSpan( state->CurrentInlineEditSpan() );
        if ( inlineSpan.Length() == 0 || iShowCursor )
            {
            iEdwin.ConvertTextForSmileyL( select, ETrue , EFalse );            
            CSmileyManager* smiley( iEdwin.iEdwinExtension->iSmiley );
            TInt docPos( iEdwin.CursorPos() );
            smiley->HandleSetCursor( select.iAnchorPos, docPos );
            if ( docPos != select.iCursorPos )
                {
                TBool isSelected( iEdwin.SelectionLength() > 0 );
                iEdwin.SetCursorPosL( docPos, isSelected );
                if ( isSelected )
                    {
                    iEdwin.HandleSelectionForSmiley( iEdwin.Selection() );
                    }
                }
            iEdwin.SetAmountToFormatL( EFalse, ETrue );
            iEdwin.DrawDeferred();
            }
        }
    iOriginalSelection.SetSelection(-1,-1);
    iPositionOfInsertionPointInDocument=-1;
    iPositionOfInlineTextInDocument=-1;
    iLengthOfInlineText=-1;
    iEdwin.iLayout->SetCustomDraw(iOldCustomDraw);
    iOldCustomDraw=NULL;
    iPointerEventHandlerDuringInlineEdit=NULL;
    iEdwin.ReportEdwinEventL( MEikEdwinObserver::EEventTextUpdate );
    User::LeaveIfError(error2);
    }

/*MCoeFepAwareTextEditor_Extension1* CEikEdwinFepSupport::Extension1(TBool& aSetToTrue)
    {
    aSetToTrue=ETrue;
    return this;
    }
*/
void CEikEdwinFepSupport::MCoeFepAwareTextEditor_Reserved_2()
    {
    }

void CEikEdwinFepSupport::SetStateTransferingOwnershipL(CState* aState, TUid aTypeSafetyUid)
    {
    MEikCcpuEditor* currentCcpuState=STATIC_CAST(CAknEdwinState*, State(KNullUid))->CcpuState();
    MObjectProvider* currentObjectProvider=STATIC_CAST(CAknEdwinState*, State(KNullUid))->ObjectProvider();
    delete iState;
    iState=aState;
    STATIC_CAST(CAknEdwinState*, State(KNullUid))->SetCcpuState(currentCcpuState);
    STATIC_CAST(CAknEdwinState*, State(KNullUid))->SetObjectProvider(currentObjectProvider);
    iStateTypeSafetyUid.iUid=aTypeSafetyUid.iUid;
    }

MCoeFepAwareTextEditor_Extension1::CState* CEikEdwinFepSupport::State(TUid aTypeSafetyUid)
    {
    if (aTypeSafetyUid.iUid==iStateTypeSafetyUid.iUid)
        {
        return iState;
        }
    return NULL;
    }

void CEikEdwinFepSupport::StartFepInlineEditL(
        TBool& aSetToTrue, 
        const TCursorSelection& aCursorSelection, 
        const TDesC& aInitialInlineText, 
        TInt aPositionOfInsertionPointInInlineText, 
        TBool aCursorVisibility, 
        const MFormCustomDraw* aCustomDraw, 
        MFepInlineTextFormatRetriever& aInlineTextFormatRetriever, 
        MFepPointerEventHandlerDuringInlineEdit& aPointerEventHandlerDuringInlineEdit)
    {
    aSetToTrue=ETrue;
    iEdwin.PerformRecordedOperationL();
    TBool selectionVisible = iEdwin.iTextView->SelectionVisible();
    if (selectionVisible)
    	iEdwin.SetSelectionVisibilityL(EFalse);
    SetCursorSelectionForFepL(aCursorSelection);

    StartFepInlineEditL(aInitialInlineText, aPositionOfInsertionPointInInlineText, aCursorVisibility, aCustomDraw, aInlineTextFormatRetriever, aPointerEventHandlerDuringInlineEdit);
    if (selectionVisible)
    	iEdwin.SetSelectionVisibilityL(ETrue);
    }

void CEikEdwinFepSupport::SetCursorType(TBool& /*aSetToTrue*/, const TTextCursor& aTextCursor)
    {
    TRAP_IGNORE( iEdwin.iTextView->SetCursorWidthTypeL( aTextCursor.iType ) );
    }

void CEikEdwinFepSupport::MCoeFepAwareTextEditor_Extension1_Reserved_3()
    {
    }

void CEikEdwinFepSupport::MCoeFepAwareTextEditor_Extension1_Reserved_4()
    {
    }

TBool CEikEdwinFepSupport::IsValidCharacter(TInt aChar)
    {
    if (aChar == CEditableText::EParagraphDelimiter && 
        (iEdwin.UserFlags() & CEikEdwin::ENoLineOrParaBreaks))
        return EFalse;

    if ((aChar==EKeyEnter || aChar==CEditableText::EParagraphDelimiter) && iEdwin.iEdwinInternalFlags & CEikEdwin::EHasOneLineOnly)
        return EFalse;
    /*
    if (iEdwin.OnlyASCIIChars() && aChar > 0xFF && aChar != KPuaCodeSpaceSymbol)
        return EFalse;
    */
    
    if ( !iEdwin.IsValidChar( aChar ) )
        {
        return EFalse;
        }
        
    return ETrue;
    }


void CEikEdwinFepSupport::MCoeFepSpecificExtensions_Reserved_1()
    {
    }

void CEikEdwinFepSupport::MCoeFepSpecificExtensions_Reserved_2()
    {
    }


//
//  CEikEdwinExtension
//
CEikEdwin::CEikEdwinExtension* CEikEdwin::CEikEdwinExtension::NewL(CEikEdwin* aEdwin)
    {   
    CEikEdwinExtension* self = new (ELeave) CEikEdwinExtension();
    CleanupStack::PushL(self);
    self->ConstructL(aEdwin);
    CleanupStack::Pop();  // self
    return self;
    }

CEikEdwin::CEikEdwinExtension::~CEikEdwinExtension()
    {  
    delete iPhysicsHandler;
    
    // Stop listening CenRep.
    if (iCenRepNotifyHandler)
        {
        iCenRepNotifyHandler->StopListening();
        }
    delete iCenRepNotifyHandler;
    delete iCenRep;

    delete iFormAccessor;
    delete iFormCursorModifier;
    delete iFormExtendedInterfaceProvider;
    delete iPictographInterface;
    delete iExtendedInputCapabilities;
    delete iPtSuppressor;
    if( iDestroyedPtr )
        {
        // Mark the object as destroyed.
        *iDestroyedPtr = ETrue;
        iDestroyedPtr = NULL;
        }
    delete iSmiley;
    delete iSmileyWrap;
    }

EXPORT_C CAknEdwinFormAccessor* CEikEdwin::CEikEdwinExtension::FormAccessor() const
    {
    return iFormAccessor;
    }

EXPORT_C void CEikEdwin::CEikEdwinExtension::SetFormAccessor(CAknEdwinFormAccessor* aFormAccessor)
    {
    iFormAccessor = aFormAccessor;
    }

EXPORT_C void CEikEdwin::CEikEdwinExtension::SetScrollBarSetter(CIdle* aScrollBarSetter)
    {
    iSetScrollBar=aScrollBarSetter;
    }

EXPORT_C CIdle* CEikEdwin::CEikEdwinExtension::ScrollBarSetter()
    {
    return iSetScrollBar;
    }

EXPORT_C const TAvkonEditorCustomWrap& CEikEdwin::CEikEdwinExtension::TextWrapper()
    {
    return iTextWrapper;
    }

EXPORT_C CFormCursorModifier* CEikEdwin::CEikEdwinExtension::FormCursorModifier() const
    {
    return iFormCursorModifier;
    }

void CEikEdwin::CEikEdwinExtension::SetSkinBackgroundControlContext( MAknsControlContext* aBackgroundControlContext)
    {
    iSkinBackgroundControlContext = aBackgroundControlContext;
    iFlags.Set(ESkinBackgroundControlContextHasBeenSetIndex);
    }

MAknsControlContext* CEikEdwin::CEikEdwinExtension::SkinBackgroundControlContext() const
    {
    return iSkinBackgroundControlContext;
    }

TBool CEikEdwin::CEikEdwinExtension::SkinBackgroundControlContextHasBeenSet() const
    {
    return iFlags[ESkinBackgroundControlContextHasBeenSetIndex];
    }

void CEikEdwin::CEikEdwinExtension::SetAlignment(TInt aAlignment)
    {
    iAlignment = aAlignment;
    TUint capabilities = iExtendedInputCapabilities->Capabilities();
    capabilities &= ~( CAknExtendedInputCapabilities::KAknEditorAlignMask );
    switch( iAlignment )
        {
        case EAknEditorAlignCenter:
            capabilities |= 
                CAknExtendedInputCapabilities::EInputEditorAlignCenter;
            break;
        case EAknEditorAlignLeft:
            capabilities |= 
                CAknExtendedInputCapabilities::EInputEditorAlignLeft;
            break;
        case EAknEditorAlignRight:
            capabilities |= 
                CAknExtendedInputCapabilities::EInputEditorAlignRight;
            break;
        case EAknEditorAlignBidi:
            capabilities |= 
                CAknExtendedInputCapabilities::EInputEditorAlignBidi;
            break;
        default:
            break;
        }
    iExtendedInputCapabilities->SetCapabilities( capabilities );
    }

TInt CEikEdwin::CEikEdwinExtension::CurrentAlignment() const
    {
    return iAlignment;
    }

void CEikEdwin::CEikEdwinExtension::SetSuppressBackgroundDrawing( TBool aSuppress )
    {
    iFlags.Assign( ESuppressBackgroundDrawing, aSuppress );
    }

TBool CEikEdwin::CEikEdwinExtension::IsBackgroundDrawingSuppressed() const
    {
    return iFlags[ESuppressBackgroundDrawing];
    }

void CEikEdwin::CEikEdwinExtension::SetPictoCallBack( TCallBack& aCallBack )
    {
    iPictoCallBack = aCallBack;
    }

const TCallBack& CEikEdwin::CEikEdwinExtension::PictoCallBack() const
    {
    return iPictoCallBack;
    }

CEikEdwin::CEikEdwinExtension::CEikEdwinExtension() :
    iAlignment(EAknEditorAlignBidi),
    iSkinIdForText(KErrNotFound),
    iUpperFullFormattingLength(KFullFormattingUpperThreshold),
    iTempCursorPos( KErrNotFound ),
    iTempAnchorPos( KErrNotFound ),
    iThumbPos( KErrNotFound ),
    iEdwin( NULL ),
    iPhysicsHandler( NULL )
    {
    }

void CEikEdwin::CEikEdwinExtension::ConstructL(CEikEdwin* aEdwin)
    {
    iEdwin = aEdwin;
    iFormAccessor = new (ELeave) CAknEdwinFormAccessor(aEdwin);
    iFormCursorModifier = CFormCursorModifier::NewL(aEdwin->TextView(), aEdwin->TextLayout());
    iPictographInterface = CAknPictographInterface::NewL( *aEdwin, iPictographDrawer );
    iExtendedInputCapabilities = CAknExtendedInputCapabilities::NewL();
    iPtSuppressor = CAknPointerEventSuppressor::NewL();

    // Start listening a CenRep key indicating whether hash key selection is active.
    TRAPD(err, iCenRep = CRepository::NewL(KCRUidAknFep));
    if (err == KErrNone)
        {
        iCenRepNotifyHandler = CCenRepNotifyHandler::NewL(*this,
            *iCenRep,
            CCenRepNotifyHandler::EIntKey,
            KAknFepClearDirection);

        iCenRepNotifyHandler->StartListeningL();
        iCenRep->Get(KAknFepClearDirection, iClearDirection);
        }
    iSmileyWrap = new ( ELeave ) CSmileyCustomWrap;
    }

void CEikEdwin::CEikEdwinExtension::CreateFormExtendedInterfaceProviderIfNeededL()
    {
    if ( !iFormExtendedInterfaceProvider )
        iFormExtendedInterfaceProvider = CAknEdwinFormExtendedInterfaceProvider::NewL();
    }

CAknEdwinFormExtendedInterfaceProvider* CEikEdwin::CEikEdwinExtension::FormExtendedInferfaceProvider( ) const
    {
    return iFormExtendedInterfaceProvider;
    }

void CEikEdwin::CEikEdwinExtension::CreatePurePhoneNumberFormatterL( CTextLayout& /*aLayout*/, const CPlainText& aText )
    {
    CreateFormExtendedInterfaceProviderIfNeededL();

    if ( !iPhoneNumberFormatter )
        {
        CAknPhoneNumberInlineTextSource* phoneNumberFormatter = 
            CAknPlainPhoneNumberInlineTextSource::NewL( aText );
        CleanupStack::PushL( phoneNumberFormatter );
        iFormExtendedInterfaceProvider->
            CompositeInlineTextSource().InstallInlineTextSourceL( phoneNumberFormatter );
        CleanupStack::Pop( phoneNumberFormatter );
        iPhoneNumberFormatter = phoneNumberFormatter;
        }
    }


void CEikEdwin::CEikEdwinExtension::CreateNoMatchesIndicatorFormatterL( CTextLayout& aLayout )
    {
    CreateFormExtendedInterfaceProviderIfNeededL();

    if ( !iNoMatchesIndicatorFormatter )
        {
        CAknNoMatchesIndicatorInlineTextSource* noMatchesIndicatorFormatter = CAknNoMatchesIndicatorInlineTextSource::NewL( aLayout );
        CleanupStack::PushL( noMatchesIndicatorFormatter );
        iFormExtendedInterfaceProvider->CompositeInlineTextSource().InstallInlineTextSourceL( noMatchesIndicatorFormatter );
        CleanupStack::Pop( noMatchesIndicatorFormatter );
        iNoMatchesIndicatorFormatter = noMatchesIndicatorFormatter;
        }
    }


void CEikEdwin::CEikEdwinExtension::CreateRichTextPhoneNumberFormatterL( CTextLayout& /*aTextLayout*/, const CRichText& aText )
    {
    CreateFormExtendedInterfaceProviderIfNeededL();

    if ( !iPhoneNumberFormatter )
        {
        CAknRichTextPhoneNumberInlineTextSource* phoneNumberFormatter = 
            CAknRichTextPhoneNumberInlineTextSource::NewL( aText );
        CleanupStack::PushL( phoneNumberFormatter );
        iFormExtendedInterfaceProvider->
            CompositeInlineTextSource().InstallInlineTextSourceL( phoneNumberFormatter );
        CleanupStack::Pop( phoneNumberFormatter );
        iPhoneNumberFormatter = phoneNumberFormatter;
        }

    }

CAknInlineTextSource* CEikEdwin::CEikEdwinExtension::InlineTextSource() const
    {
    CAknEdwinFormExtendedInterfaceProvider* provider = FormExtendedInferfaceProvider();
    if ( provider )
        return &(provider->CompositeInlineTextSource());
    else
        return NULL;
    }

CAknPictographInterface* CEikEdwin::CEikEdwinExtension::PictographInterface() const
    {
    return iPictographInterface;
    }

TInt CEikEdwin::CEikEdwinExtension::ClearDirection() const
    {
    return iClearDirection;
    }

void CEikEdwin::CEikEdwinExtension::HandleNotifyInt(TUint32 aId, TInt aNewValue)
    {
    if (aId == KAknFepClearDirection)
        {
        iClearDirection = (TBool)aNewValue;
        }
    }

// ---------------------------------------------------------------------------
// CEikEdwin::CEikEdwinExtension::EnableKineticScrollingL
// ---------------------------------------------------------------------------
//   
void CEikEdwin::CEikEdwinExtension::EnableKineticScrollingL()
    {
    iFlags.Set( EKineticScrollingEnabled );
    EnablePhysicsL();
    }

// ---------------------------------------------------------------------------
// CEikEdwin::CEikEdwinExtension::EnablePhysicsL
// ---------------------------------------------------------------------------
//   
void CEikEdwin::CEikEdwinExtension::EnablePhysicsL()
    {
    if ( iFlags.IsSet( EKineticScrollingEnabled )
        && !iPhysicsHandler && iEdwin->DrawableWindow() )
        {
        iPhysicsHandler = CAknEdwinPhysicsHandler::NewL( *iEdwin );
        
        InitPhysicsL();   
        if ( iEdwin->iLayout )
            {
            iEdwin->iLayout->RestrictScrollToTopsOfLines( EFalse );
            }
        }
    }

// ---------------------------------------------------------------------------
// CEikEdwin::CEikEdwinExtension::InitPhysicsL
// ---------------------------------------------------------------------------
//   
void CEikEdwin::CEikEdwinExtension::InitPhysicsL()
    {
    if ( iPhysicsHandler )
        {
        if ( iEdwin->iTextView )
            {
            iPhysicsHandler->SetViewRect( iEdwin->AdjustedViewRect() );
            }
        iPhysicsHandler->InitPhysicsL();
        }
    }

//
// class CEikEdwin
//


const TInt KPointerRepeatRate=50000;
// const TInt KBlockDeleteWarningSize=300; // minimum block delete that will elicit a query

EXPORT_C CEikEdwin::~CEikEdwin()
    {
    AKNTASHOOK_REMOVE();
    if ( iEdwinFepSupport )
        {
        CAknEdwinState* edwinState = STATIC_CAST( CAknEdwinState*, iEdwinFepSupport->State(KNullUid) );
        if ( edwinState )
            {                   
            TRAP_IGNORE( edwinState->ReportAknEdStateEventL( MAknEdStateObserver::EAknEdwinDestroy ) );
            }
        }
    SetKeyboardRepeatRate(KAknStandardKeyboardRepeatRate);
    delete iCcpuSupport;
    delete iCustomDrawer;
    delete iEdwinFepSupport;

    if (!(iEdwinUserFlags&EKeepDocument))
        delete iText;
    delete iTextView;
    delete iLayout;
    if (iEdwinExtension)
        {
        delete iEdwinExtension->ScrollBarSetter();
        }
    delete iEdwinExtension;
    delete iSBFrame;
    delete iUndoStore;
    delete iObserverArray;
#ifdef _DEBUG
    TRAPD(err, SetVirtualCursorStateL(EFalse)); //should never leave
    __ASSERT_DEBUG(err==KErrNone,Panic(EEikPanicVirtualCursorLeaveNotExpected));
#else
    TRAP_IGNORE(SetVirtualCursorStateL(EFalse)); //should never leave
#endif // _DEBUG
    
    delete iCharFormatLayer;
    delete iParaFormatLayer;
    }

EXPORT_C CEikEdwin::CEikEdwin()
    : iZoomFactor(iEikonEnv->ScreenDevice()),
    iAvgCharsPerLine(1)
    {
    __DECLARE_NAME(_S("CEikEdwin"));
    LafEdwin::GetDefaultBorder(iBorder);
    iMargins=LafEdwin::Margins();
    BuildEdwinFepSupport();
    iParaFormatLayer = NULL;
    iCharFormatLayer = NULL;

    TRAPD(err, iEdwinExtension = CEikEdwinExtension::NewL(this));
    if (err == KErrNone)
        {
        if (EditorState())
            EditorState()->SetFormAccessor(iEdwinExtension->FormAccessor());
        
        iEdwinExtension->iExtendedInputCapabilities->SetEditorType(
            CAknExtendedInputCapabilities::EEdwinBased );
        }
    AKNTASHOOK_ADD( this, "CEikEdwin" );
    }

EXPORT_C CEikEdwin::CEikEdwin(const TGulBorder& aBorder)
    : CEikBorderedControl(aBorder),
    iZoomFactor(iEikonEnv->ScreenDevice()),
    iAvgCharsPerLine(1)
    {
    __DECLARE_NAME(_S("CEikEdwin"));
    iMargins=LafEdwin::Margins();
    BuildEdwinFepSupport();
    iParaFormatLayer = NULL;
    iCharFormatLayer = NULL;

    TRAPD(err, iEdwinExtension = CEikEdwinExtension::NewL(this));
    if (err == KErrNone)
        {
        if (EditorState())
            EditorState()->SetFormAccessor(iEdwinExtension->FormAccessor());
        
        iEdwinExtension->iExtendedInputCapabilities->SetEditorType(
            CAknExtendedInputCapabilities::EEdwinBased );
        }
    AKNTASHOOK_ADD( this, "CEikEdwin" );
    }

void CEikEdwin::BuildEdwinFepSupport()
    {
    iEdwinFepSupport=CEikEdwinFepSupport::New(*this); // don't leave
    if (iEdwinFepSupport)
        {
        iEdwinFepSupport->ConstructStateHolder();
        if (!iEdwinFepSupport->State(KNullUid))
            {
            delete iEdwinFepSupport;
            iEdwinFepSupport = NULL;
            }
        }
    }

EXPORT_C void CEikEdwin::ConstructFromResourceL(TResourceReader& aReader)
    {
    iEdwinUserFlags=iEdwinUserFlags | aReader.ReadInt32();
    CalculateWidth(aReader.ReadInt16());
    iNumberOfLines=aReader.ReadInt16();
    iTextLimit=aReader.ReadInt16();
    ReadAknResourceL(aReader);
    BaseConstructL();
    }


EXPORT_C TInt CEikEdwin::AknEdwinFlags() const
    {
    if (iEdwinFepSupport && iEdwinFepSupport->State(KNullUid))
        return STATIC_CAST(CAknEdwinState*, iEdwinFepSupport->State(KNullUid))->Flags();
    else
        return 0;
    }

EXPORT_C void CEikEdwin::BaseConstructL()
    {
    if (iEdwinUserFlags&EEdwinAlternativeWrapping)
        SetAvkonWrap(EFalse); 
    else
        SetAvkonWrap(ETrue); // added to make changes in Edwin spacing work. 
    if (iEdwinUserFlags&EUserSuppliedText)
        {
        if (iNumberOfLines)
            {
            TInt height = iNumberOfLines*iEikonEnv->NormalFont()->HeightInPixels()+iBorder.SizeDelta().iHeight
                            +iMargins.iTop+iMargins.iBottom;
            SetEdwinHeight(height);
            }
        }
    else
        {
        CheckIfEdwinIsResizable();
        CParaFormatLayer* paraFormatLayer = (iEdwinInternalFlags&EHasOneLineOnly)
                            ? iEikonEnv->SystemSingleLineParaFormatLayerL()
                            : iEikonEnv->SystemParaFormatLayerL();
        
        SetParaFormatLayer(paraFormatLayer->CloneL());
        SetCharFormatLayer(iEikonEnv->SystemCharFormatLayerL()->CloneL());
        
        CreateTextAndLayoutL(iParaFormatLayer,iCharFormatLayer);
        }

    EnableCcpuSupportL(ETrue);
    if (AknEdwinFlags()&EAknEditorFlagEnableScrollBars)
        {
        CEikScrollBarFrame* scrollFrame = CreatePreAllocatedScrollBarFrameL();
        scrollFrame->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto);
        scrollFrame->SetScrollBarFrameFlags(CEikScrollBarFrame::EVVisible);
        }
    SetVKBStatus();
    }

EXPORT_C void CEikEdwin::SetCharFormatLayer(CCharFormatLayer* aCharFormatLayer)
    {
    ASSERT(aCharFormatLayer);
    if (iCharFormatLayer)
        {
        // copy all the format attributes of the new layer, apply to the already
        // existing format layer, then delete the one passed in (this function was taking ownership)
        // This avoids a problem with ETEXT and CRichText, where CGlobalText::iGlobalCharFormatLayer
        // cannot be changed.
        if (!(iCharFormatLayer->IsIdentical(aCharFormatLayer,EFalse)))
            {
            TRAP_IGNORE(MakeCharFormatLayerMatchL(aCharFormatLayer));
            }
        delete aCharFormatLayer;
        }
    else
        {
        iCharFormatLayer = aCharFormatLayer;
        if (STATIC_CAST(CGlobalText*, Text()))
            {
            STATIC_CAST(CGlobalText*, Text())->SetGlobalCharFormat(iCharFormatLayer);
            }
        }
    }

EXPORT_C void CEikEdwin::SetParaFormatLayer(CParaFormatLayer* aParaFormatLayer)
    {
    ASSERT(aParaFormatLayer);
    if (iParaFormatLayer)
        {
        // copy all the format attributes of the new layer, apply to the already
        // existing format layer, then delete the one passed in (this function was taking ownership)
        // This avoids a problem with ETEXT and CRichText, where CGlobalText::iGlobalCharFormatLayer
        // cannot be changed.
        if (!(iParaFormatLayer->IsIdentical(aParaFormatLayer,EFalse)))
            {
            TRAP_IGNORE(MakeParaFormatLayerMatchL(aParaFormatLayer));
            }
        delete aParaFormatLayer;
        }
    else
        {
        iParaFormatLayer = aParaFormatLayer;
        if (STATIC_CAST(CGlobalText*, Text()))
            {
            STATIC_CAST(CGlobalText*, Text())->SetGlobalParaFormat(iParaFormatLayer);
            }
        }
    }

void CEikEdwin::MakeCharFormatLayerMatchL(CCharFormatLayer* aCharFormatLayer)
    {
    ASSERT(aCharFormatLayer);
    TCharFormat newCharFormat;
    aCharFormatLayer->SenseEffective(newCharFormat);
    TCharFormat currentCharFormat;
    iCharFormatLayer->SenseEffective(currentCharFormat);
    if (!currentCharFormat.IsEqual(newCharFormat))
        {
        TCharFormatMask newCharFormatMask;
        newCharFormatMask.SetAll();
        iCharFormatLayer->SetL(newCharFormat,newCharFormatMask);
        }
    }

void CEikEdwin::MakeParaFormatLayerMatchL(CParaFormatLayer* aParaFormatLayer)
    {
    ASSERT(aParaFormatLayer);
    CParaFormat* newParaFormat=CParaFormat::NewLC();
    CParaFormat* currentParaFormat=CParaFormat::NewLC();
    aParaFormatLayer->SenseEffectiveL(newParaFormat);
    iParaFormatLayer->SenseEffectiveL(currentParaFormat);
    if (!currentParaFormat->IsEqual(*newParaFormat))
        {
        TParaFormatMask newParaFormatMask;
        newParaFormatMask.SetAll();
        iParaFormatLayer->SetL(newParaFormat,newParaFormatMask);
        }
    CleanupStack::PopAndDestroy(2); // currentParaFormat,newParaFormat
    }

EXPORT_C void CEikEdwin::SetSkinBackgroundControlContextL(  MAknsControlContext* aBackgroundControlContext )
    {
    CheckEdwinExtensionL(); // checks if iEdwinExtension is NULL and constucts it if it is
    iEdwinExtension->SetSkinBackgroundControlContext( aBackgroundControlContext );
    }

MAknsControlContext* CEikEdwin::SkinBackgroundControlContext() const
    {
    MAknsControlContext* context = NULL;
    if ( SkinEnabled() ) // Otherwise null is returned
        {
        if ( iEdwinExtension )
            context = iEdwinExtension->SkinBackgroundControlContext();
        // if context is still null we still may return a context, but it has to be from env.
        if ( !context )
            context = AknsDrawUtils::ControlContext( this );
        }
    return context;
    }

TBool CEikEdwin::SkinEnabled() const
    {
    TBool enabled( ETrue );
    // return EFalse only if the background control context has been set by API
    // and the value set is NULL
    if ( iEdwinExtension )
        {
        if (iEdwinExtension->SkinBackgroundControlContextHasBeenSet() )
            if ( !(iEdwinExtension->SkinBackgroundControlContext()) ) // do not use Edwin method here; would cause recursion
                enabled = EFalse;
        }
    return enabled;
    }


void CEikEdwin::UpdateCache(TInt aId)
    {
    CAknSettingCache& cache = CAknEnv::Static()->SettingCache();
    cache.Update(aId);
    }

void CEikEdwin::DrawTextView() const
    {
    if ( IsReadyToDraw() )
        {
        TRect rect = iTextView->ViewRect();    
        Window().Invalidate( rect );
        ActivateGc();
        Window().BeginRedraw( rect );
        TrappedDraw( iTextView->ViewRect() );
        Window().EndRedraw();
        DeactivateGc();
        }
    }

/**
* This routine performs draws in the area around the text view. Most of the work is to drive the 
* custom drawer if present.
*
*/
void CEikEdwin::DrawBackgroundAroundTextView( CWindowGc& gc, 
                                             const TRect& aOuterRect, 
                                             const TRect& aInnerRect, 
                                             const TRgb& aBackgroundColor ) const
    {
    // Skins support
    if ( iCustomDrawer )
        {
        TPoint point(aInnerRect.iTl); // Text layout upper left.
        TZoomFactor map(iZoomFactor);

        // This returns the rectangle actually used. Not used here
        TRect drawn;

        TRect rect=aOuterRect;
        rect.iBr.iY=aInnerRect.iTl.iY;
        iCustomDrawer->DrawBackground(
            MFormCustomDraw::TParam( gc, map, point, rect ), aBackgroundColor, drawn);
        rect.iBr.iY=aOuterRect.iBr.iY;
        rect.iTl.iY=aInnerRect.iBr.iY;
        iCustomDrawer->DrawBackground(
            MFormCustomDraw::TParam( gc, map, point, rect ), aBackgroundColor, drawn);
        rect=aInnerRect;
        rect.iTl.iX=aOuterRect.iTl.iX;
        rect.iBr.iX=aInnerRect.iTl.iX;
        iCustomDrawer->DrawBackground(
            MFormCustomDraw::TParam( gc, map, point, rect ), aBackgroundColor, drawn);
        rect.iTl.iX=aInnerRect.iBr.iX;
        rect.iBr.iX=aOuterRect.iBr.iX;
        iCustomDrawer->DrawBackground(
            MFormCustomDraw::TParam( gc, map, point, rect ), aBackgroundColor, drawn);
        }
    else 
        {
        // Draws with a null pen but solid brush
        DrawUtils::ClearBetweenRects(gc,aOuterRect,aInnerRect);
        }

    }

EXPORT_C CLafEdwinCustomDrawBase* CEikEdwin::CreateCustomDrawL()
    {
    // If we have a text view, then use the constructor that sets it
    CAknEdwinCustomDrawPrivate* customDrawer;
    if ( iTextView )
        {
        CWindowGc& sysGc = SystemGc();
        customDrawer = CAknEdwinCustomDrawPrivate::NewL(iEikonEnv->LafEnv(),*this, iTextView, &sysGc);
        }
    else
        customDrawer = CAknEdwinCustomDrawPrivate::NewL(iEikonEnv->LafEnv(),*this);

    return customDrawer;
    }

void CEikEdwin::DoCreateCustomDrawL()
    {

    if (!(iEdwinUserFlags&ENoCustomDraw))
        {
        if (!iCustomDrawer || iTextView )
            {
            TBool oldCustomDraw = EFalse;
            
            if ( iEdwinFepSupport )
                {
                oldCustomDraw = ( iEdwinFepSupport->iOldCustomDraw && iEdwinFepSupport->iOldCustomDraw == iCustomDrawer );
                }

            delete iCustomDrawer;
            iCustomDrawer = 0;
            iLayout->SetCustomDraw(0);
            iCustomDrawer=CreateCustomDrawL();
            
            if ( oldCustomDraw )
                {
                iEdwinFepSupport->iOldCustomDraw = iCustomDrawer;
                }
            }
        }
    if (!iCustomDrawer)
        { // create a non-Avkon custom drawer that just does colour schemes
        iCustomDrawer=CLafEdwinCustomDrawBase::NewL(iEikonEnv->LafEnv(),*this);
        }

    iLayout->SetCustomDraw(iCustomDrawer);
    }

/**
 * @internal
 */
EXPORT_C void CEikEdwin::CreateTextAndLayoutL(CParaFormatLayer* aParaFormatLayer,CCharFormatLayer* aCharFormatLayer)
    {
    CancelFepTransaction();
    CEditableText::TDocumentStorage storage=(iEdwinUserFlags&ESegmentedStorage)?
                                CEditableText::ESegmentedStorage: CEditableText::EFlatStorage;
    TInt granularity = (iTextLimit != 0 && iTextLimit+2 < CEditableText::EDefaultTextGranularity)
                        ? iTextLimit+2
                        : CEditableText::EDefaultTextGranularity;
    CGlobalText* globalText = (iEdwinInternalFlags&ERichText)
                        ? CRichText::NewL(aParaFormatLayer,aCharFormatLayer,storage,granularity)
                        : CGlobalText::NewL(aParaFormatLayer,aCharFormatLayer,storage,granularity);
    iText=globalText;
    CreateLayoutL(globalText);
    SetHeightForNumOfLinesL();
    DoCreateCustomDrawL();
    if ( iEdwinExtension->iSmiley )
        {
        TextLayout()->SetCustomWrap( iEdwinExtension->iSmileyWrap );
        }
    }

EXPORT_C void CEikEdwin::CheckEdwinExtensionL()
    {
    User::LeaveIfNull(EditorState());
    if (!iEdwinExtension)
        {
        iEdwinExtension = CEikEdwinExtension::NewL(this);
        EditorState()->SetFormAccessor(iEdwinExtension->FormAccessor());
        }
    }


EXPORT_C CEikEdwin::CEikEdwinExtension* CEikEdwin::EdwinExtension()
    {
    return iEdwinExtension;
    }


EXPORT_C void CEikEdwin::ConstructL(TInt aEdwinFlags,TInt aWidthInChars,TInt aTextLimit,TInt aNumberOfLines)
    {
    iEdwinUserFlags |= aEdwinFlags;    
    CalculateWidth(aWidthInChars);
    iTextLimit=aTextLimit;
    iNumberOfLines=aNumberOfLines;
    BaseConstructL();
    }

EXPORT_C void CEikEdwin::SetEdwinObserver(MEikEdwinObserver* aEdwinObserver)
    {
    iEdwinObserver=aEdwinObserver;
    }

/**
 * Add an observer of standard edwin events.  May be called any number of times and
 * is independant of calls to SetEdwinObserver.
 */
EXPORT_C void CEikEdwin::AddEdwinObserverL(MEikEdwinObserver* aEdwinObserver)
    {
    if (!iObserverArray)
        iObserverArray=new(ELeave) CArrayPtrFlat<MEikEdwinObserver>(1);
    iObserverArray->AppendL(aEdwinObserver);
    }

/**
 * Removes aEdwinObserver form the list of observers.  Does nothing if aEdwinObserver isn't an observer.
 */
EXPORT_C void CEikEdwin::RemoveEdwinObserver(MEikEdwinObserver* aEdwinObserver)
    {
    if (iObserverArray)
        {
        const TInt count=iObserverArray->Count();
        for (TInt ii=0;ii<count;ii++)
            {
            if ((*iObserverArray)[ii]==aEdwinObserver)
                {
                iObserverArray->Delete(ii);
                break;
                }
            }
        if (iObserverArray->Count()==0)
            {
            delete iObserverArray;
            iObserverArray=NULL;
            }
        }
    }

EXPORT_C void CEikEdwin::SetDocumentContentL(CGlobalText& aText,TSetContent aContent)
    {
    __ASSERT_DEBUG(&aText,Panic(EEikPanicNullPointer));
    CancelFepTransaction();
    if (aContent==ECopyText)
        CopyDocumentContentL(aText,*((CGlobalText*)iText));
    else
        {
        iText=&aText; // relies on any existing iText having been deleted by the caller
        if (iEdwinInternalFlags&ERichText)
            {
            static_cast<CRichText*>(iText)->SetEditObserver(this);
            TInt startPos=0;
            TInt length=iText->DocumentLength();
            static_cast<CRichText*>(iText)->ParseText(startPos,length,ETrue);
            }
        if (iLayout)
            iLayout->SetLayDoc(&aText);
        else
            CreateLayoutL(&aText);
        DoCreateCustomDrawL();
        }
    CheckRemovePictures(0,iText->DocumentLength());
    CheckValidityOfChars(0,iText->DocumentLength());
    SetAmountToFormatL(ETrue); // performs format
    }

EXPORT_C void CEikEdwin::CopyDocumentContentL(CGlobalText& aInText,CGlobalText& aOutText)
    {
    __ASSERT_DEBUG(&aInText,Panic(EEikPanicNullPointer));
    __ASSERT_DEBUG(&aOutText,Panic(EEikPanicNullPointer));
    aOutText.Reset();
    CBufStore* store=CBufStore::NewLC(1024);
    TStreamId streamId=aInText.StoreL(*store);
    aOutText.RestoreL(*store,streamId);
    RStoreWriteStream paraWriteStream;
    TStreamId paraStreamId=paraWriteStream.CreateLC(*store);
    (aInText.GlobalParaFormatLayer())->ExternalizeL(paraWriteStream);
    CleanupStack::PopAndDestroy(); // paraStreamId
    RStoreReadStream paraReadStream;
    paraReadStream.OpenLC(*store,paraStreamId);
    ((CParaFormatLayer*)(aOutText.GlobalParaFormatLayer()))->InternalizeL(paraReadStream);
    CleanupStack::PopAndDestroy(); // paraReadStream
    RStoreWriteStream charWriteStream;
    TStreamId charStreamId=charWriteStream.CreateLC(*store);
    (aInText.GlobalCharFormatLayer())->ExternalizeL(charWriteStream);
    CleanupStack::PopAndDestroy(); // charStreamId
    RStoreReadStream charReadStream;
    charReadStream.OpenLC(*store,charStreamId);
    ((CCharFormatLayer*)(aOutText.GlobalCharFormatLayer()))->InternalizeL(charReadStream);
    CleanupStack::PopAndDestroy(2); // store and charReadStream
    }

EXPORT_C void CEikEdwin::CalculateWidth(TInt aWidthInChars)
    {
    const CFont* font=iEikonEnv->NormalFont();
    iSize.iWidth=aWidthInChars;
    if (!(iEdwinUserFlags&EWidthInPixels))
        iSize.iWidth*=(iEdwinInternalFlags&ENumericCharacters? font->WidthZeroInPixels(): font->MaxNormalCharWidthInPixels());
    iSize.iWidth+=iBorder.SizeDelta().iWidth+CursorWidth()+LineCursorWidth()+iMargins.iLeft+iMargins.iRight;
    }

void CEikEdwin::SetHeightForNumOfLinesL()
    {
    if (iNumberOfLines==0)
        return;
    iLayout->SetImageDeviceMap(iZoomFactor);
    iLayout->FormatBandL();
    TInt lineHeight = iLayout->FormattedHeightInPixels();
    TInt edwinHeight = iNumberOfLines*lineHeight;
    edwinHeight += iBorder.SizeDelta().iHeight+iMargins.iTop+iMargins.iBottom;
    SetEdwinHeight(edwinHeight);
    }

EXPORT_C TKeyResponse CEikEdwin::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    if (aType!=EEventKey)
        return EKeyWasNotConsumed;
    TKeyEvent keyEvent = aKeyEvent;
    LafEdwin::MapKeyEvent(keyEvent, aType);
    return DoOfferKeyEventL(keyEvent, aType);
    }

TKeyResponse CEikEdwin::DoOfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode /*aType*/)
    {
    TInt code=aKeyEvent.iCode;
    if ( code == EKeyLeftUpArrow || code == EKeyRightUpArrow)
        {
        code = EKeyUpArrow;
        }
    else if ( code == EKeyLeftDownArrow || code == EKeyRightDownArrow)
        {
        code = EKeyDownArrow;
        }
    const TCursorSelection selection=Selection();
    const TInt selectionLength=selection.Length();
    TInt cursorPos=CursorPos();
    const TInt docLength=iText->DocumentLength();

/*
if a 1 line editor, 
and the key is an up/down 
and not holding shift, 
 => ignore the key.
*/
    if (
        (iEdwinInternalFlags&EHasOneLineOnly)&&
        (code==EKeyUpArrow || code==EKeyDownArrow) &&
        (!(aKeyEvent.iModifiers&EModifierShift))
        )
        {
        SetVirtualCursorStateL(EFalse);
        return EKeyWasNotConsumed;
        }
    if (selectionLength==0)
        {
        if (code==EKeyLeftArrow || code==EKeyRightArrow || code==EKeyBackspace)
            SetKeyboardRepeatRate(KAknEditorKeyboardRepeatRate);
        else
            SetKeyboardRepeatRate(KAknStandardKeyboardRepeatRate);

        TBool consume=ETrue;
        TPoint cursorPoint;
        if (iLayout->PosInBand(cursorPos,cursorPoint))
            {
            TPoint pos;
/* 
The following cases were added to stop Up/Down cursors moving the insert point to the
start/end of lines in the case of first/last line.  
However, we should only do this if there is not a shift held down, as otherwise it
is a selection operation
*/
            if (!(aKeyEvent.iModifiers&EModifierShift))
                {
                if (
                    code==EKeyUpArrow && 
                    iLayout->FirstDocPosFullyInBand()==0 &&
                    iLayout->PosInBand(0,pos) && 
                    pos.iY == cursorPoint.iY
                    )
                    {
                    if (cursorPos == 0 || iNumberOfLines == 1)
                        { 
                        consume = EFalse;
                        } 
                    }
                if (consume && code==EKeyDownArrow)
                    {
                    if (iLayout->PosInBand(docLength,pos))
                        {
                        if (pos.iY == cursorPoint.iY)
                            {
                            if (cursorPos == TextLength() || iNumberOfLines == 1)
                                {
                                consume = EFalse;
                                }
                            }
                        }
                    }
                }
            }
        if (!consume)
            {
            SetVirtualCursorStateL(EFalse);
            return EKeyWasNotConsumed;
            }
        }
    if (iEdwinUserFlags&EDisplayOnly)
        return EKeyWasConsumed;
    if ( iEdwinExtension->iDrawInvoked == CEikEdwinExtension::ENotDraw )
        {
        PerformRecordedOperationL();
        }
    const TInt modifiers=aKeyEvent.iModifiers;
    TBool navigation=EFalse;
    TBool formatChange=EFalse;
    TBool select=modifiers&EModifierShift;
    if ( select )
        {        
        CEikButtonGroupContainer* cba( CEikButtonGroupContainer::Current() );
        if ( cba )
            {            
            TInt copyPos( cba->PositionById( EAknFepSoftkeyStartCopy ) );
            TInt cutPos( cba->PositionById( EAknFepSoftkeyStartCut ) );
            if ( copyPos != KErrNotFound || cutPos != KErrNotFound )
                {
                select = EFalse;
                }
            }
        }
    TBool magnify=modifiers&EModifierCtrl;
    const TInt oldLength=iText->DocumentLength();
    if (magnify && ( code == EKeyF18 || ( code<100 && code!=' ' ) ) )////!!! magic number
        {
        TClipboardFunc clipboardFunc=ENoClipboard;
        TBuf<24> buf;
        if (select)
            iCoeEnv->ReadResourceL(buf,R_EIK_EDWIN_SHIFT_CTRL_HOTKEYS);
        else
            iCoeEnv->ReadResourceL(buf,R_EIK_EDWIN_CTRL_HOTKEYS);
        TInt ret=buf.Locate(TChar(code+'a'-1));        
        if ( code == EKeyF18 )
            {
            ret = aKeyEvent.iScanCode;
            }
        switch (ret)
            {
        case EHotKeyCut:
        case EEikCmdEditCut:
            CheckNotReadOnlyL();
            clipboardFunc=ECut;
            formatChange=ETrue;
            break;
        case EHotKeyCopy:
        case EEikCmdEditCopy:
            clipboardFunc=ECopy;
            break;
        case EHotKeyPaste:
            CheckNotReadOnlyL();
            clipboardFunc=EPaste;
            formatChange=ETrue;
            break;
        case EHotKeyUndo:
            UndoL();
            return EKeyWasConsumed;
        case EHotKeyFind:
            if (iEdwinInternalFlags&EHasOneLineOnly)
                return EKeyWasConsumed; 
            if (!TextLength())
                iEikonEnv->InfoMsg(R_EIK_TBUF_NO_TEXT);
            else if (!FindL(NULL))
                iEikonEnv->InfoMsg(R_EIK_TBUF_TEXT_NOT_FOUND);
            else
                navigation=ETrue;
            break;
        case EHotKeyInsertChar:
            RunCharMapDialogL();
            return EKeyWasConsumed;
        default:
            ;
            }
        if (clipboardFunc>ENoClipboard)
            {
            ClipboardL(clipboardFunc);
            return EKeyWasConsumed;
            }

        // Select all
        TChar ctrlStripped( code + 'a' - 1 );
        if ( ctrlStripped == TChar('a') ) // ctrl-a is 0x01
            {
            SelectAllL();
            return EKeyWasConsumed;
            }
        }
    TKeyResponse ret=EKeyWasConsumed;
    TBool reportChange=EFalse;
    TBool formatHasChanged;
    TInt charEditType=CTextLayout::EFCharacterInsert;
    switch (code)
        {
    case EKeyPageUp:
    case EKeyPageDown:
        if (magnify)
            SetCursorPosL((code==EKeyPageUp)? 0: TextLength(),select);
        else
            MoveCursorL((code==EKeyPageUp)? TCursorPosition::EFPageUp: TCursorPosition::EFPageDown, select);
        if(CursorPos()==cursorPos && ((cursorPos==0 && code==EKeyPageUp) ||
            (cursorPos==TextLength() && code==EKeyPageDown)))
            SetVirtualCursorStateL(EFalse);
        CancelInsertCharFormat();
        navigation=ETrue;
        break;
    case EKeyHome:
    case EKeyEnd:
        {
        const TBool cancelFormat=!((code==EKeyHome && selection.iCursorPos==0) ||
                            (code==EKeyEnd && selection.iCursorPos==docLength));
        if (magnify)
            SetCursorPosL((code==EKeyHome? 0 : docLength),select);
        else
            MoveCursorL((code==EKeyHome)? TCursorPosition::EFLineBeg: TCursorPosition::EFLineEnd, select);
        if (cancelFormat)
            {
            CancelInsertCharFormat();
            navigation=ETrue;
            }
        else if(selection.Length()==0)
            SetVirtualCursorStateL(EFalse);
        break;
        }
    case EKeyUpArrow:
    case EKeyDownArrow:
        {
        // Cancelformat should be true unless the key is stuck at the maximum/minimum position.
        // Unfortunately the following code is not bidi: 
        const TBool cancelFormat=!((code==EKeyUpArrow && selection.iCursorPos==0) ||
                            (code==EKeyDownArrow && selection.iCursorPos==docLength));
        if (selectionLength && !select)
            CancelSelectionL(code==EKeyUpArrow? EStart: EEnd);
        else
            {
            if (magnify)
                MoveCursorToChunkStartL(select,EChunkPara,(code==EKeyUpArrow)? EStart: EEnd);
            else if (IsReadOnly() && (iEdwinUserFlags&EAvkonDisableCursor))
                ret = ScrollReadOnlyNoCursorDisplayL(code);
            else
                MoveCursorL((code==EKeyUpArrow)? TCursorPosition::EFLineUp: TCursorPosition::EFLineDown, select);
            }
        if (cancelFormat)
            {
            CancelInsertCharFormat();
            navigation=ETrue;
            }
        else if(selectionLength==0 && ((cursorPos==0 && code==EKeyUpArrow) ||
            (cursorPos==TextLength() && code==EKeyDownArrow)))
            SetVirtualCursorStateL(EFalse); // This logic not Bidi either...in
        break;
        }
    case EKeyLeftArrow:
    case EKeyRightArrow:
        { 
        if (iEdwinFepSupport && iEdwinFepSupport->State(KNullUid)) 
            if  (STATIC_CAST(CAknEdwinState*, iEdwinFepSupport->State(KNullUid))->Flags()&EAknEditorFlagNoLRNavigation)
                return EKeyWasNotConsumed;      

        // This logic is to determine key/position situations that are not causing navigation. 
        // All REAL navigation should set the cancelFormat flag. 
        // However, In Series 60, all left/right keys navigate somewhere because of end-start looping.
        // (In fact the right left keys causing document end to start looping do not even get here. Done in FEP)
        TBool cancelFormat(ETrue);

        if (selectionLength && !select)
            CancelSelectionL(code==EKeyLeftArrow? EStart: EEnd);
        else
            {
            if (magnify)
                MoveCursorToChunkStartL(select,EChunkWord,(code==EKeyLeftArrow)? EStart: EEnd);
            else
                MoveCursorL((code==EKeyLeftArrow)? TCursorPosition::EFLeft: TCursorPosition::EFRight, select);
            }
        if (cancelFormat)
            {
            CancelInsertCharFormat();
            navigation=ETrue;
            }
        else if(selectionLength==0 && ((cursorPos==0 && code==EKeyLeftArrow) ||
            (cursorPos==TextLength() && code==EKeyRightArrow)))
            SetVirtualCursorStateL(EFalse);
        break;
        }
    case EKeyEscape:
        if (selectionLength)
            iTextView->CancelSelectionL();
        break;
    case EKeyBackspace:
        if (magnify && !(modifiers&EModifierPureKeycode))
            break; // prevent Ctrl-H deleting
    case EKeyDelete:
        {
        if (iEdwinExtension)
            {
            if (iEdwinExtension->ClearDirection() > 0)
                {
                if (code == EKeyBackspace)
                    {
                    if (!selectionLength
                     && cursorPos != docLength)
                        {
                        code = EKeyDelete;
                        }
                    }
                else if (code == EKeyDelete && !select)
                    {
                    code = EKeyBackspace;
                    }
                }
            }

        // In case of pressing BS-key or Delete-key with shift-key,
        // Change from BS(or Delete) to Delete(or BS)
        if (select)
            {
            code = (code==EKeyBackspace)? EKeyDelete : EKeyBackspace;
            }

        TBuf<2> newText; // Used for neutral protection
        CheckNotReadOnlyL();

        TCursorSelection toDelete;
        TBool deleteSelection = EFalse;
        TBool replaceSelection = EFalse;
        TBool forwardProtectionNeeded = EFalse;

        if (selectionLength)
            {
            toDelete = selection;
            deleteSelection = ETrue;
            SetSelectionL(toDelete.iCursorPos, toDelete.iAnchorPos);
            }
        else // no selection
            {
            //convert visible codes to original text strings.
            if ( ConvertSmileyForDeleteL( cursorPos, ( code == EKeyBackspace ) ) )
                {
                return EKeyWasConsumed;
                }
            if (code==EKeyDelete)
                toDelete = iTextView->GetForwardDeletePositionL();
            else if (code==EKeyBackspace)
                {
                TInt cursorPos = CursorPos();
                if ( cursorPos > 0 )
                    {
                    TPtrC ptr(iText->Read(cursorPos-1)); 
                    TInt glyphToDelete = ptr[0];
                    if (  (glyphToDelete >= 0x0E01) && (glyphToDelete <= 0x0E5B) 
//                       #ifdef RD_HINDI
                       || (glyphToDelete >= 0x0900) && (glyphToDelete <= 0x097F) //unicode code range for Devanagari. 
//                       #endif //RD_HINDI
                       )
                        {
                        toDelete = TCursorSelection(cursorPos, cursorPos-1);
                        }
                    else
                        {
                        toDelete = iTextView->GetBackwardDeletePositionL();
                        }
                    }
                else
                    toDelete = iTextView->GetBackwardDeletePositionL();                
                }

            if (toDelete.Length() > 1 )
                { // => we have some invisible characters to delete
                SetSelectionL(toDelete.iCursorPos, toDelete.iAnchorPos);
                deleteSelection = ETrue;
                }
            // Neutral charcter protection
            // Copy selection to descriptor
            if ( EditorSupportsNeutralProtection() )
                {
                if ( NeedsNeutralProtection( toDelete.LowerPos(), toDelete.Length(), newText, forwardProtectionNeeded ) )
                    replaceSelection = ETrue;
                }
            }

        if (deleteSelection && !replaceSelection ) // delete select, but no neutral protection
            {
            DeleteHighlightL(formatHasChanged,code==EKeyBackspace);
            const TInt lower=toDelete.LowerPos();
            const TCursorSelection sel(lower,lower);
            iTextView->SetPendingSelection(sel);
            iTextView->HandleInsertDeleteL(sel,toDelete.Length(),formatHasChanged);
            reportChange=ETrue;
            }
        else if ( replaceSelection ) // All neutral protection cases 
            {
            if ( !deleteSelection ) // selection has not been set yet
                SetSelectionL(toDelete.iCursorPos, toDelete.iAnchorPos);
            TInt cursorPosInNewText = newText.Length(); // after neutral protection character(s)
            if (forwardProtectionNeeded) // back it up if one was forward protecting
                cursorPosInNewText--; 
            ReplaceSelectionWithTextL( newText, cursorPosInNewText, formatHasChanged ); 
            reportChange=ETrue;
            formatChange=formatHasChanged;
            }
        else // !deleteSelection  and !replaceSelection => Legacy single character delete
            {
            TInt pos=-1;
            if (code==EKeyDelete)
                pos=cursorPos;
            else if (code==EKeyBackspace)
                {
                pos=cursorPos;
                --pos;
                }
            TBool isPicture=EFalse;
            if (pos>=0)
                {
                TPtrC text=iText->Read(pos,1); // look at the single character
                if (text[0]==CEditableText::EPictureCharacter)
                    {
                    if (!iEikonEnv->QueryWinL(R_EIK_CONFIRM_DELETE_OBJECT_TITLE))
                        return EKeyWasConsumed;
                    isPicture=ETrue;
                    }
                }

            TBool doDelete=EFalse;
            if (code==EKeyBackspace)
                {
                charEditType=CTextLayout::EFLeftDelete;
                if (cursorPos>0)
                    {
                    doDelete=ETrue;
                    --cursorPos;
                    }
                }
            else
                {
                charEditType=CTextLayout::EFRightDelete;
                if (cursorPos<TextLength())
                    doDelete=ETrue;
                }
            if (doDelete)
                {
                TCursorSelection selection=(isPicture? TCursorSelection(cursorPos,cursorPos+1) : TCursorSelection(cursorPos,cursorPos));
                DeleteL(formatHasChanged,selection,code==EKeyBackspace,isPicture);
                if (!isPicture)
                    ClearUndo();
                iTextView->HandleCharEditL(charEditType,formatHasChanged);
                reportChange=ETrue;
                formatChange=formatHasChanged;
                }
            }
        if ( reportChange && iEdwinExtension->iSmiley )
            {
            ConvertTextForSmileyL( TCursorSelection( cursorPos, cursorPos ), 
                ETrue );          
            if ( deleteSelection || replaceSelection )
                {
                SetCursorPosL( cursorPos, EFalse );
                }
            }
        }
        break;
    case '-':
        if (select|magnify)
            code=CEditableText::ENonBreakingHyphen;
        goto InChar;
    case EKeySpace:
        if (select)
            code=CEditableText::ENonBreakingSpace;
        goto InChar;
    case EKeyEnter:
        if ( iEdwinUserFlags & ENoLineOrParaBreaks )
            {       
            return EKeyWasConsumed;
            }
        CheckNotReadOnlyL();
        if (iEdwinInternalFlags&EHasOneLineOnly)
            break;
        code=(select? CEditableText::ELineBreak : CEditableText::EParagraphDelimiter);
        if (code == CEditableText::EParagraphDelimiter)
            NewParagraphL();
        charEditType=(select? CTextLayout::EFCharacterInsert : CTextLayout::EFParagraphDelimiter);
        goto TestMagnify;
    case EKeyTab:
        code=CEditableText::ETabCharacter;
        // Tab characters are disabled in all editors
        // because copy/paste and column/formattedcell listboxes
        // do not work well and any tab characters in the
        // strings will cause crashes in _all_ applications.
        // (implements tabulator section in default event
        // actions spec which says tab is inactive.)
        if (!(iEdwinUserFlags&EAvkonTabsEnabled))
            break;
TestMagnify:
        if (magnify && !(modifiers&EModifierPureKeycode))
            break; // prevent eg Ctrl-I inserting a tab
        goto InChar;
    default:
        if (code>=ENonCharacterKeyBase || !TChar(code).IsPrint() || (!IsValidChar(code)))
            {
            ret=EKeyWasNotConsumed;
            break;
            }
InChar: CheckNotReadOnlyL();
        TChar character(code);
        if ( selectionLength && IsValidNumericCharL(character) )
            {
            TInt pos=DeleteHighlightL(formatHasChanged);
            TRAPD(err,iText->InsertL(pos,character));
            if ( iEdwinExtension->iSmiley )
                {
                iEdwinExtension->iSmiley->HandleInsertL( pos, 1 );
                ConvertTextForSmileyL( TCursorSelection( pos, pos ), ETrue );
                }
            TCursorSelection selection=iTextView->Selection();
            if (err==KErrNone && iUndoStore)
                iUndoStore->SetNewText(TCursorSelection(selection.LowerPos(),selection.LowerPos()+1));
            TCursorSelection pending;
            pending.iCursorPos=selection.LowerPos()+1;
            pending.iAnchorPos=pending.iCursorPos;
            iTextView->SetPendingSelection(pending);
            selection=pending;
            --selection.iAnchorPos;
            iTextView->HandleInsertDeleteL(selection,selectionLength,formatHasChanged);
            User::LeaveIfError(err);
            reportChange=ETrue;
            formatChange=formatHasChanged;
            break;
            }
        if ( (!iTextLimit || TextLength()<iTextLimit) && IsValidNumericCharL(character) )
            {
            iText->InsertL(CursorPos(),character);
            ClearUndo();
            if ( iEdwinExtension->iSmiley )
                {
                TInt cursorPos( CursorPos() );
                iEdwinExtension->iSmiley->HandleInsertL( cursorPos, 1 );
                ConvertTextForSmileyL( TCursorSelection( cursorPos, cursorPos ), 
                    ETrue );
                }
            iTextView->HandleCharEditL(charEditType);
            reportChange=ETrue;
            }
        else
            {
            ClearUndo();
            CEikonEnv::Beep();
            iEikonEnv->InfoMsg(R_EIK_TBUF_MAX_CHARACTERS_REACHED);
            }
        }
    if (reportChange)
        {
        ReportEdwinEventL( MEikEdwinObserver::EEventTextUpdate );
        DoReportEventL( MCoeControlObserver::EEventStateChanged );
        if ( iEdwinExtension->iSmiley )
            {            
            TInt docPos( CursorPos() );
            iEdwinExtension->iSmiley->HandleSetCursor( docPos, 
                docPos );
            if ( docPos != CursorPos() )
                {
                SetCursorPosL( docPos, SelectionLength() > 0 );
                }
            }
        }
    if (navigation)
        { 
        iEdwinExtension->iThumbPos = KErrNotFound;
        ReportEdwinEventL(MEikEdwinObserver::EEventNavigation);
        }
    if (formatChange)
        ReportEdwinEventL(MEikEdwinObserver::EEventFormatChanged);
    if (NeedToChangeFormattingModeL()) 
        SetAmountToFormatL();
    UpdateScrollBarsL();
    return ret;
    }
    
TKeyResponse CEikEdwin::ScrollReadOnlyNoCursorDisplayL(TUint aKeyCode)
    {
    __ASSERT_DEBUG(iTextView,Panic(EEikPanicEdwinNoView));
    TCursorPosition::TMovementType move = (aKeyCode==EKeyUpArrow)? TCursorPosition::EFLineUp: TCursorPosition::EFLineDown;
    // attempt to scroll the display, but prevent blank lines being added to the end
    if (iTextView->ScrollDisplayL(move, CTextLayout::EFDisallowScrollingBlankSpace))
        {
        // make the cursor stay on the screen by matching its movement to the scrolling
        MoveCursorL(move, EFalse);
        return EKeyWasConsumed;
        }
    return EKeyWasNotConsumed;
    }


void CEikEdwin::ReplaceSelectionWithTextL( const TDesC& aNewText,
                                          TInt aPositionOfCursorInNewText,
                                          TBool& aFormatHasChanged )
    {
    CheckNotReadOnlyL(); // leaves if readonly

    // The selection length is preserved as it is used in the HandleInsertDeleteL at the bottom
    TInt deletedChars = iTextView->Selection().Length();

    // Just return if the new text minus the old text does not fit
    if (iTextLimit && (TextLength() - deletedChars + aNewText.Length() > iTextLimit ) )
        return;

    // Delete the selected text from the buffer; 
    TCursorSelection selToDelete = iTextView->Selection();
    TInt pos = selToDelete.iAnchorPos;
    if ( selToDelete.Length() )
        {
        pos=DeleteHighlightL(aFormatHasChanged);
        }

    // Insert new text.
    // This is trapped so that we can get by with one call to HandleInsertDeleteL.
    // However, we need to ensure that HandleInsertDeleteL is called at least after
    // a non-leaving DeleteHighlightL. 
    TInt newTextLength = 0; // if the following leaves, handling will be as if newText has length 0
    TRAPD(err,iText->InsertL(pos,aNewText) );
    if ( err == KErrNone )
        newTextLength = aNewText.Length(); 

    // New selection to be passed to HandleInsertDeleteL.  Span the new text 
    TCursorSelection selection(pos + newTextLength, pos); // Note, cursor pos is first parameter

    // Some undo stuff; unused in S60
    if (err==KErrNone && iUndoStore)
        iUndoStore->SetNewText(selection);

    // Following code is to set up for SetPendingSelection which dictates where the selection/cursor
    // will be after the operation. Zero length selection dictated by aPositionOfCursorInNewText
    TCursorSelection pending;
    pending.iAnchorPos = selection.LowerPos() + Min( newTextLength, aPositionOfCursorInNewText);
    pending.iCursorPos = pending.iAnchorPos;

    iTextView->SetPendingSelection(pending);
/*
Set up for the call for textview to handle the changed content
@param aSelection The start and new length of the changed block. 
@param aDeletedChars The number of deleted characters. 
@param aFormatChanged ETrue if text is to be reformatted from the start of the
paragraph the cursor was on before the edit, EFalse if from the start of the
line the cursor was on before the edit.
@return The number of pixels scrolled horizontally and vertically. ( Ignored )
*/
    (void)iTextView->HandleInsertDeleteL( selection, deletedChars, aFormatHasChanged);
    User::LeaveIfError(err);
    }

EXPORT_C void* CEikEdwin::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CEikEdwin::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    if ( iEdwinFepSupport )
         {
         CAknEdwinState* edwinState =
             STATIC_CAST( CAknEdwinState*,
             iEdwinFepSupport->State(KNullUid) );

         if ( edwinState && ( edwinState->Flags() & EAknEditorFlagChinesePopup ) )
             {
             return;
             }
         }
    
    if ( iEdwinExtension->iDrawInvoked == CEikEdwinExtension::ENotDraw )
        {
        PerformRecordedOperationL();
        }
    TCursorSelection selectionBefore = iTextView->Selection();
    if (IsDimmed())
        {
        // IMHO, dimmed editor should not handle events
        return;
        }

    TBool kineticScrollingEnabled( KineticScrollingEnabled() );
    if ( iEdwinExtension )
        {
        TPoint pos = aPointerEvent.iPosition;
        
        CAknExtendedInputCapabilities::
            MAknEventObserver::TPointerEventReceivedParams params;

        if ( kineticScrollingEnabled &&
            aPointerEvent.iType == TPointerEvent::EButton1Down )
            {
            iEdwinExtension->iPhysicsHandler->InitKineticScrolling(
                aPointerEvent.iPosition );
            }

        params.iPointerEvent = aPointerEvent;
        TTmPosInfo2 posInfo;
        if(iTextView->FindXyPosL(pos, posInfo, NULL)) // not interested in the line
            {
            params.iDocPos = posInfo.iDocPos.iPos;   
            }
        else // Need to call this method for the case where the pen is beyond the last line of text
            {
            params.iDocPos = iTextView->XyPosToDocPosL( pos );
            }
        
        /** The local @c destroyed variable keeps track of the object destroyed state. */
        TBool destroyed = EFalse;
        iEdwinExtension->iDestroyedPtr = &destroyed;
        TRAP_IGNORE (
            iEdwinExtension->iExtendedInputCapabilities->ReportEventL(
                CAknExtendedInputCapabilities::MAknEventObserver::EPointerEventReceived,
                &params );
              )
        if ( !destroyed )
            {
            iEdwinExtension->iDestroyedPtr = NULL;
            }
        else
            {
            return;
            }
        }

    // Kinetic scrolling related code begins
 
    if ( kineticScrollingEnabled )
        {      
        // This FEP related code block needs to perform only if EDisplayOnly
        // flag was NOT SET to match to old functionality.
        // In original code we returned here if EDisplayOnly was set.
        // Now we have to continue (but skip this block of code)
        // because kinetic scrolling is supported also in editors
        // with EDisplayOnly flag and this is handled later in the code.
        
        const TCursorSelection selection( iTextView->Selection() );
        const TPoint pointerPos( aPointerEvent.iPosition );

        if ( !( iEdwinUserFlags & EDisplayOnly ) )
            {
            if ( IsFocused() )
                {
                CancelFepTransaction();
                }
            if ( iEdwinFepSupport && iCoeEnv->Fep() )
                {
                TPoint tempPos( pointerPos );
                const TInt documentPosition =
                    iTextView->XyPosToDocPosL( tempPos );
                    
                if ( iEdwinFepSupport->IsHandledByFepL( aPointerEvent.iType,
                    aPointerEvent.iModifiers, documentPosition ) )
                    {
                    return;
                    }                   
                }
            }
        
        TBool shouldReturn( EFalse );
        iEdwinExtension->iPhysicsHandler->HandleKineticScrolling(
            aPointerEvent, shouldReturn );
        
        if ( shouldReturn )
            {
            return;
            }
     
        } // physics enabled

    // Kinetic scrolling related code ends
     
    // Display only mode, don't handle selection but return here.
    if ( iEdwinUserFlags & EDisplayOnly )
        {
        return;
        }
    
    const TCursorSelection selection( iTextView->Selection() );
    const TPoint pointerPos( aPointerEvent.iPosition );
    
    // Kinetic scrolling not enabled
    if ( !kineticScrollingEnabled )
        {
        if ( IsFocused() )
            {
            CancelFepTransaction();
            }
        if ( iEdwinFepSupport != NULL )
            {
            if ( iEdwinFepSupport != NULL )
                {
                // an optimization so that iTextView->XyPosToDocPosL is not
                // called unnecessarily, since it needs to be called again,
                // after CancelFepTransaction has been called
                if (iCoeEnv->Fep()!=NULL) 
                    {
                    TPoint tempPos( pointerPos );
                    const TInt documentPosition =
                        iTextView->XyPosToDocPosL( tempPos );
                    if ( iEdwinFepSupport->IsHandledByFepL( aPointerEvent.iType,
                        aPointerEvent.iModifiers, documentPosition))
                        {
                        return;
                        }
                    }
                }
            } 
        } // Kinetic scrolling not enabled  
    
    if ( iEdwinExtension->iPtSuppressor->SuppressPointerEvent( aPointerEvent ) )
        {
        return;
        }
    if ( IsFocused() )
        {
        CancelFepTransaction();
        }
    TInt newCursorPos; // initialized a couple of lines below
    {
    TPoint tempPos(pointerPos); // the parameter to iTextView->XyPosToDocPosL gets stomped over, so copy pointerPos into a temporary TPoint object - the curly braces give this object a short lifetime
    TTmPosInfo2 posInfo;
    // newCursorPos needs to be initialised *after* CancelFepTransaction has been called, as CancelFepTransaction 
    // may have changed the contents of the document by cancelling an inline edit, and in particular it may have made 
    // the document shorter
    if(iTextView->FindXyPosL(tempPos, posInfo, NULL)) // not interested in the line
        {
        newCursorPos = posInfo.iDocPos.iPos; // Gives correct value when pen is on right hand part of the character
        }
    else // Need to call this method for the case where the pen is beyond the last line of text
        {
        newCursorPos=iTextView->XyPosToDocPosL(tempPos); 
        }
    }
    TBool select=(aPointerEvent.iModifiers&EModifierShift);
    TBool navigation=EFalse;
    switch (aPointerEvent.iType)
        {
    case TPointerEvent::EButton1Down:
        {
        SetVirtualCursorStateL(ETrue);
        iLastPointerDocPos=CursorPos();
        iLastPointerAnchorPos=selection.iAnchorPos;
        if (iTextView->ViewRect().Contains(pointerPos))
            iEdwinInternalFlags|=ELeftDownInViewRect;
        else
            return;
        if (aPointerEvent.iModifiers&EModifierCtrl)
            iEdwinInternalFlags|=EDragDouble;
        else
            iEdwinInternalFlags&=(~EDragDouble);

        if (iEdwinInternalFlags&EDragDouble)
            {
            TInt startPos,length;
            GetWordInfo(newCursorPos,startPos,length);
            SetSelectionL(startPos+length,startPos);
            }
        else
            {
            if ( iEdwinUserFlags & CEikEdwin::EAvkonDisableCursor )
                {
                iEdwinExtension->iTempCursorPos = newCursorPos;
                iEdwinExtension->iTempSelect = select;
                if ( selection.Length() > 0 && !select )
                    {
                    ClearSelectionL();
                    iEdwinFepSupport->iSelectionIsCancel = ETrue;
                    }
                }
            else
                {
                CAknEdwinState* edwinState = STATIC_CAST( CAknEdwinState*, iEdwinFepSupport->State( KNullUid ) );
                iEdwinExtension->iRecordCursor = newCursorPos;
                // If touch input opened or no selection, set the new position. Otherwise record current position.
                if ( !( selection.iCursorPos != selection.iAnchorPos 
                        && !( edwinState->Flags() & EAknEditorFlagTouchInputModeOpened  ) ) 
                    || (iEdwinUserFlags & EAvkonDisableVKB ) || 
                    ( iEdwinExtension->iExtendedInputCapabilities->Capabilities() & CAknExtendedInputCapabilities::EInputEditorQwertyInputActive ) )
                    {                 
                    EnableRateScrolling( ETrue );
                    SetCursorPosL( newCursorPos, select );
                    EnableRateScrolling( EFalse );
                    
                    // when point at the bottom line ,if it is not the last line CTextview will scroll up
                    // one line. So we record if it scroll and record current point DocPos
                    TPoint testPos = aPointerEvent.iPosition;  
                    if ( newCursorPos != iTextView->XyPosToDocPosL( testPos ) )
                        {
                        iEdwinExtension->iRecordScroll = ETrue;
                        iEdwinExtension->iRecordCursor = iTextView->XyPosToDocPosL( testPos );
                        }
                    else
                        {
                        iEdwinExtension->iRecordScroll = EFalse;    
                        }
                    }                
                }
            }
        break;
        }
    case TPointerEvent::EButtonRepeat:
    case TPointerEvent::EDrag:
    case TPointerEvent::EButton1Up:
        {
        iEdwinFepSupport->iMoveThumbFeedbackNeeded = ETrue;        
        if (!(iEdwinInternalFlags&ELeftDownInViewRect))
            return;
        if ( aPointerEvent.iType == TPointerEvent::EDrag && 
            ( iEdwinUserFlags & CEikEdwin::EAvkonDisableCursor ) &&
            ( iEdwinExtension->iTempCursorPos != KErrNotFound ) )
            {
            SetCursorPosL( iEdwinExtension->iTempCursorPos,
                iEdwinExtension->iTempSelect );
            iEdwinExtension->iTempCursorPos = KErrNotFound;
            }
        if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
            {
            if (!iEdwinExtension->iScrollRect.IsEmpty())
                {
                TPoint point;
                TextLayout()->PosInBand(newCursorPos, point);
                TInt yPos = point.iY;
                TRect lineRect;
                TextLayout()->GetLineRect(yPos, lineRect);                      
                lineRect.iTl += Position();
                lineRect.iBr += Position();


                if (!(iEdwinExtension->iScrollRect.Contains(lineRect.iTl) || iEdwinExtension->iScrollRect.Contains(lineRect.iBr)))
                    {
                    TInt y = (iEdwinExtension->iScrollRect.iTl.iY + iEdwinExtension->iScrollRect.iBr.iY) / 2;
                    if (lineRect.iTl.iY > y)
                        { // Scroll up (cursor is down)
                        TInt num = -1;
                        TRAP_IGNORE( iTextView->ScrollDisplayLinesL(num));
                        }
                    else
                        { // Scroll down (cursor is up)
                        TInt num = 1;
                        TRAP_IGNORE( iTextView->ScrollDisplayLinesL(num));
                        }
                    }
                }

            const TInt newAnchorPos=selection.iAnchorPos;
            if (newCursorPos!=iLastPointerDocPos || newAnchorPos!=iLastPointerAnchorPos)
                navigation=ETrue;
            iLastPointerDocPos=newCursorPos;
            iLastPointerAnchorPos=newAnchorPos;
            iEdwinInternalFlags&=(~ELeftDownInViewRect);

            // We can't open cut-copy-paste menu if dragging started
            if ( IsReadOnly() && IsSelectionVisible() && !( kineticScrollingEnabled
                && iEdwinExtension->iPhysicsHandler->DraggingStarted() ) )
                {
                iEdwinFepSupport->iFeedback->InstantFeedback(
                                                         this,
                                                         ETouchFeedbackPopUp,
                                                         ETouchFeedbackVibra,
                                                         aPointerEvent );
                TRAP_IGNORE (
                    iEdwinExtension->iExtendedInputCapabilities->ReportEventL(
                        CAknExtendedInputCapabilities::MAknEventObserver::EOpenStylusMenuCcpu,
                        NULL );
                      )
                }
            
            if ( iEdwinFepSupport && 
                 iTextView->ViewRect().Contains( pointerPos ) )
                {
                CAknEdwinState* edwinState =
                    STATIC_CAST( CAknEdwinState*,
                    iEdwinFepSupport->State(KNullUid) );

                if ( kineticScrollingEnabled )
                    {                  
                    if ( !IsReadOnly() && !iEdwinExtension->iDragging &&
                        !iEdwinExtension->iPhysicsHandler->DraggingStarted()   
                        )
                        {
                        iEdwinFepSupport->iFeedback->InstantFeedback( this,
                            ETouchFeedbackEditor, ETouchFeedbackVibra,
                            aPointerEvent );
                        }
                    }
                else // Kinetic scrolling not enabled
                    {
                    if ( aPointerEvent.iType == TPointerEvent::EButton1Up && IsFocused() &&
                        ( iEdwinFepSupport->iSelectionIsCancel ||
                        !( iEdwinUserFlags & ( CEikEdwin::EAvkonDisableCursor |
                            iEdwinUserFlags & CEikEdwin::EDisplayOnly |
                            iEdwinUserFlags & CEikEdwin::EReadOnly |
                            iEdwinUserFlags & CEikEdwin::EAvkonNotEditable ) ) ) )
                        {
                        iEdwinFepSupport->iFeedback->InstantFeedback(
                            this,
                            ETouchFeedbackEditor,
                            ETouchFeedbackVibra,
                            aPointerEvent );
                        iEdwinFepSupport->iSelectionIsCancel = EFalse;
                        }
                    } 
                
                TBool kineticDragging = kineticScrollingEnabled &&
                    ( iEdwinExtension->iPhysicsHandler->DraggingStarted() ||
                      iEdwinExtension->iPhysicsHandler->
                      DragThresholdExceeded( aPointerEvent.iPosition ) );
                
                if ( edwinState && !IsReadOnly() &&
                    !iEdwinExtension->iDragging &&
                    !kineticDragging )
                    {
                    TRAP_IGNORE(
                        edwinState->ReportAknEdStateEventL(
                            MAknEdStateObserver::EAknActivatePenInputRequest )
                        );
                    }
                }
            }
        TInt origWordStartPos, origWordLength;
        GetWordInfo(selection.iAnchorPos,origWordStartPos,origWordLength);
        TRect pictRect;
        if (aPointerEvent.iType==TPointerEvent::EButton1Up &&
            iTextView->GetPictureRectangleL(selection.LowerPos(),pictRect))
            {
        iEdwinFepSupport->iMoveThumbFeedbackNeeded = EFalse;        
            break;
            }
        select=ETrue;
        
        TRect viewRect( AdjustedViewRect() );
        
        if ( aPointerEvent.iType != TPointerEvent::EButton1Up &&
            ( ( pointerPos.iY >= viewRect.iBr.iY ) ||              
              ( pointerPos.iY < viewRect.iTl.iY ) ) )
            {            
            TRect rect(TPoint(viewRect.iTl.iX-1000,viewRect.iBr.iY),TSize(viewRect.Width()+2000,2000));
            if ( pointerPos.iY >= viewRect.iBr.iY )                
                {
                MoveCursorL(TCursorPosition::EFLineDown,select);
                }                
            else
                {
                MoveCursorL(TCursorPosition::EFLineUp,select);
                rect.Move(0,-(viewRect.Height()+2000));
                }
            Window().RequestPointerRepeatEvent(KPointerRepeatRate,rect);
            navigation = ETrue;
            iEdwinExtension->iThumbPos = KErrNotFound;
            }
        else if (iEdwinInternalFlags&EDragDouble)
            {
            TInt newWordStartPos,newWordLength;
            GetWordInfo(newCursorPos,newWordStartPos,newWordLength);
            if (selection.iCursorPos>selection.iAnchorPos)
                {
                if (newCursorPos<selection.iAnchorPos)
                    SetSelectionL(newWordStartPos,origWordStartPos+origWordLength);
                else
                    SetCursorPosL(newWordStartPos+newWordLength,select);
                }
            else
                {
                if (newCursorPos>selection.iAnchorPos)
                    SetSelectionL(newWordStartPos+newWordLength,origWordStartPos);
                else
                    SetCursorPosL(newWordStartPos,select);
                }
            }
        else if ( aPointerEvent.iType != TPointerEvent::EButton1Up )
            {
            CAknEdwinState* edwinState = STATIC_CAST( CAknEdwinState*, iEdwinFepSupport->State(KNullUid) );
            // Deal with second selection
            if ( selection.iCursorPos != selection.iAnchorPos && 
                 ( ! ( edwinState->Flags() & EAknEditorFlagTouchInputModeOpened ) )&& 
                 !iEdwinExtension->iDragging 
               )
                {
                if ( newCursorPos != iEdwinExtension->iRecordCursor )
                    {
                    SetCursorPosL( iEdwinExtension->iRecordCursor, EFalse );
                    iEdwinExtension->iDragging = EFalse;
                    iEdwinExtension->iRecordScroll = EFalse;
                    }
                }
            // If CTextView scroll at the bottom line and there is a little drag, 
            // we should ignore the little drag. 
            else if ( newCursorPos == iEdwinExtension->iRecordCursor
                     && iEdwinExtension->iRecordScroll
                     && !iEdwinExtension->iDragging )
                {
                break;
                }
            else
                {
                // Deal with little drag in hardware
                if ( newCursorPos != iEdwinExtension->iRecordCursor )
                    {
                    iEdwinExtension->iDragging = ETrue;
                    }
                else
                    {
                    iEdwinExtension->iDragging = EFalse;   
                    }
                SetCursorPosL( newCursorPos, select );
                iEdwinExtension->iRecordScroll = EFalse;
                }
            }
        iEdwinFepSupport->iMoveThumbFeedbackNeeded = EFalse;        
        break;
        }
    default:
        break;
        }
        if (aPointerEvent.iType == TPointerEvent::EButton1Down 
         || aPointerEvent.iType == TPointerEvent::EDrag
         || aPointerEvent.iType == TPointerEvent::EButtonRepeat )
            {
            const TCursorSelection selectionAfter = iTextView->Selection();
            TBool selectionVisible = iTextView->SelectionVisible();
            TBool paintingPossible = selectionVisible;
            TBool selectionChanged = 
                paintingPossible 
                && (  ( selectionAfter.iCursorPos != selectionBefore.iCursorPos )
                   || ( selectionAfter.iAnchorPos != selectionBefore.iAnchorPos ) );
            const TBool focused=IsFocused();
            const TBool readOnly = IsReadOnly();
            // editor got event, can be focused -> will be focused? 
            TBool editorWillGetFocus = !focused && 
                                       !IsNonFocusing() && 
                                       aPointerEvent.iType == TPointerEvent::EButton1Down;

            TBool editingEnabled = !readOnly;
            if ( iEdwinFepSupport && 
                 iEdwinFepSupport->iFeedback && 
                 ( paintingPossible || editorWillGetFocus ) )
                {
                if ( aPointerEvent.iType == TPointerEvent::EButton1Down && editingEnabled )
                    {
                    // on down event feedback is given if cursor/selection changes
                    if ( paintingPossible && !readOnly || editorWillGetFocus )
                        {
                        iEdwinFepSupport->iFeedback->InstantFeedback( this, ETouchFeedbackBasic );
                        }
                    }
                else  if ( selectionChanged && 
                       ( ( aPointerEvent.iType == TPointerEvent::EDrag ) ||
                         ( aPointerEvent.iType == TPointerEvent::EButtonRepeat ) ) )
                    {
                    
                    // selectionAfter.iCursorPos-1 below is because we need to select the previous char
                    TBool ltr = ( selectionAfter.iCursorPos >= selectionBefore.iCursorPos );
                    TInt readPos = selectionAfter.iCursorPos;
                    if (ltr && readPos > 0)
                        {
                        readPos -= 1; // read previous char
                        }
                    TChar currentSelectedChar = Text()->Read( readPos, 1 )[0]; 
                    TBool isSpace = currentSelectedChar.IsSpace();
                    TBool isText = currentSelectedChar.IsAlpha() 
                                || currentSelectedChar.IsDigit();
                    
                    // case line
                    TInt prevLineNr = TextLayout()->GetLineNumber(selectionBefore.iCursorPos);
                    TInt lineNr = TextLayout()->GetLineNumber(selectionAfter.iCursorPos);
                    if ( prevLineNr != lineNr && ( selection.Length() != 0 ) )
                        {
                        TInt group = ( currentSelectedChar.GetCategory() & 0xF0 );
                        TBool isEmptyLine = ( group == TChar::ESeparatorGroup );
                        TTouchLogicalFeedback fType = ( isEmptyLine ? 
                            ETouchFeedbackEmptyLineSelection : ETouchFeedbackLineSelection );
                        iEdwinFepSupport->iFeedback->InstantFeedback( this, fType );
                        }
                    // case space
                    else if (isSpace)
                        {
                        iEdwinFepSupport->iFeedback->InstantFeedback( this, ETouchFeedbackBlankSelection );
                        }
                    // case text
                    else if (isText)    
                        {
                        iEdwinFepSupport->iFeedback->InstantFeedback( this, ETouchFeedbackTextSelection );
                        }
                    }
                }
            }
    if ( aPointerEvent.iType == TPointerEvent::EButton1Up && iEdwinExtension->iDragging )
        {
        iEdwinExtension->iDragging = EFalse;
        }
    if ( aPointerEvent.iType == TPointerEvent::EButton1Up && iEdwinExtension->iRecordScroll )
        {
        iEdwinExtension->iRecordScroll = EFalse;
        }
    if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
        {
        iEdwinExtension->iRecordCursor = -1;
        }
    if (navigation)
        {
        ReportEdwinEventL(MEikEdwinObserver::EEventNavigation);
        CancelInsertCharFormat();
        }
    }

EXPORT_C void CEikEdwin::FocusChanged(TDrawNow /*aDrawNow*/)
    {
    if (!iTextView)
        return;
    const TBool focused=IsFocused();
    TRAP_IGNORE(SetCursorVisibilityL(focused));
    if (!focused && iEdwinUserFlags&EAlwaysShowSelection)
        ;
    else
        {
        TRAP_IGNORE( SetSelectionVisibilityL( focused ) );// !! inefficient
        }
    if (focused)
        SetCursorSizeAndType();
    else
        SetKeyboardRepeatRate(KAknStandardKeyboardRepeatRate);

    TRAP_IGNORE(SetVirtualCursorStateL(focused));
    if (iCcpuSupport)
        {
        TRAP_IGNORE(iCcpuSupport->HandleFocusChangeL());
        }
    
    if ( iEdwinFepSupport )
        {
        CAknEdwinState* edwinState = STATIC_CAST( CAknEdwinState*, 
            iEdwinFepSupport->State(KNullUid) );
        if ( edwinState )
            {
            if ( !focused )
                {
                TRAP_IGNORE( edwinState->ReportAknEdStateEventL( 
                    MAknEdStateObserver::EAknSyncEdwinState ) );
                }
            else
                {
                if ( edwinState->Flags() & EAknEditorFlagLaunchPenInputAutomatic &&
                    !IsReadOnly() && !IsDimmed() && !( iEdwinUserFlags & EDisplayOnly ) )
                    {
                    edwinState->ReportAknEdStateEventL( 
                            MAknEdStateObserver::EAknActivatePenInputRequest );
                    }
                }
            }
        }
    }

void CEikEdwin::SetCursorSizeAndType()
    {
    TInt first,second;
    AknLayoutUtils::CursorExtensionsFromFont(CursorFontSpec(),first,second);
    iTextView->SetCursorExtensions(first,second);
    iTextView->SetCursorWeight(CursorWidth());
    }

TFontSpec CEikEdwin::CursorFontSpec() const
    {
    if ( iText && iTextView )
        {
        TCharFormat charFormat;
        TCharFormatMask notUsed;
        TInt cursorPos = CursorPos();
        if ( cursorPos > iText->DocumentLength() )
            {
            cursorPos = iText->DocumentLength();
            }
        STATIC_CAST( CGlobalText*, iText )->GetCharFormat( charFormat, notUsed, 
            cursorPos, 0 );
        return charFormat.iFontSpec;
        }
    else
        {
        return iEikonEnv->NormalFont()->FontSpecInTwips();
        }
    }

TInt CEikEdwin::CursorWidth() const
    {
    return AknLayoutUtils::CursorWidthFromFont( CursorFontSpec() );
    }

void CEikEdwin::SetVirtualCursorStateL(TBool aSetSuspended) const
    {
    if(!(iEdwinUserFlags&EIgnoreVirtualCursor))
        {
        TEikVirtualCursor& cursor=iEikonEnv->VirtualCursor();
        if(aSetSuspended && cursor.CursorState(*iEikonEnv)==TEikVirtualCursor::EOn)
            cursor.SetCursorStateL(TEikVirtualCursor::ESuspended,*iEikonEnv);
        else if(!aSetSuspended && cursor.CursorState(*iEikonEnv)==TEikVirtualCursor::ESuspended)
            cursor.SetCursorStateL(TEikVirtualCursor::EOn,*iEikonEnv);
        }
    }

EXPORT_C void CEikEdwin::ActivateL()
    {
    User::LeaveIfNull(iEdwinFepSupport);
    User::LeaveIfNull(iEdwinFepSupport->State(KNullUid));
    __ASSERT_DEBUG(iText,Panic(EEikPanicEdwinNoText));
    
    CRepository* repository = NULL;
    TInt phoneNumberGroupingSupported = 0;
    TRAPD(ret, repository = CRepository::NewL(KCRUidNumberGrouping));
    if (ret == KErrNone)
        {
        ret = repository->Get(KNumberGrouping, phoneNumberGroupingSupported);
        }
    delete repository;
    
    EnableDragEvents();
    Window().SetPointerGrab(ETrue);
    
    TBool suppressNotifyDraw = iEdwinInternalFlags & ESuppressNotifyDraw;

    SetSuppressNotifyDraw( ETrue );
    
    if (!iTextView)
        {
        CreateTextViewL();
        }

    if (IsFocused())
        {
        SetCursorVisibilityL(ETrue);        
        }        
    else
        {
        SetSelectionVisibilityL( EFalse );
        }
            
    DoCreateCustomDrawL(); //  Done after TextView is created so that optimized drawer is constructed

    // Create the required formatters according to the editor set-up
    if ( IsPurePhoneNumberEditor() )
        {
        if ( phoneNumberGroupingSupported )
            {            
            CAknEdwinState* edwinState = STATIC_CAST( CAknEdwinState*, iEdwinFepSupport->State(KNullUid) );            
            edwinState->SetFlags( edwinState->Flags() | EAknEditorFlagNumberGrouping );                    
            iEdwinExtension->CreatePurePhoneNumberFormatterL( *iLayout, *iText );
            }
        }
    else // Make approximation that all other editors have no matches indicator functionality
        {
        iEdwinExtension->CreateNoMatchesIndicatorFormatterL( *iLayout );
        }

    // Rich text editors that have been configured for phone number grouping
    if (iEdwinInternalFlags&ERichText && iEdwinInternalFlags&EPhoneNumberGrouping &&
        phoneNumberGroupingSupported )
        {        
        CAknEdwinState* edwinState = STATIC_CAST( CAknEdwinState*, iEdwinFepSupport->State(KNullUid) );            
        edwinState->SetFlags( edwinState->Flags() | EAknEditorFlagNumberGrouping );                
        iEdwinExtension->CreateRichTextPhoneNumberFormatterL( *iLayout, *(static_cast<CRichText*>(iText)) );
        }

    // Install the custom formatter system if needed
    if ( iEdwinExtension->FormExtendedInferfaceProvider() )
        TextLayout()->SetInterfaceProvider( iEdwinExtension->FormExtendedInferfaceProvider() );

    UpdateScrollBarsL();
    ForceScrollBarUpdateL();

    DoAlignment();
    
    ApplyAutoSelectionL();

    CCoeControl::ActivateL();
    
    SetSuppressNotifyDraw( suppressNotifyDraw );
    }

/**
 * @internal
 */
EXPORT_C void CEikEdwin::CreateTextViewL()
    {
    if (iTextView)
        return;
    __ASSERT_DEBUG(iLayout,Panic(EEikPanicEdwinNoLayout));
    if (iEdwinInternalFlags&EHasOneLineOnly && !(iEdwinUserFlags&ENoHorizScrolling))
        iEdwinUserFlags|=ENoWrap;
    if (iEdwinUserFlags&ENoWrap)
        iLayout->ForceNoWrapping();
    
    TRect innerRect = iBorder.InnerRect( Rect() );
    
    if ( innerRect.Height() < 0 )
        {
        innerRect.SetHeight( 0 );
        }
    
    iTextView=CTextView::NewL(iLayout,innerRect,iEikonEnv->ScreenDevice(),
                                iZoomFactor,&Window(),&iEikonEnv->RootWin(),&iEikonEnv->WsSession());
    // AVKON CHANGE to make less flicker!!!
    // (Need to do here instead of LayoutEdwin, because not everyone
    // seem to use layoutedwin :( )
    iTextView->DisableFlickerFreeRedraw();
    // END

    if (LineCursorWidth())
        SetLineCursorDetailsL();
    if (iText->DocumentLength()>UpperFullFormattingLength())
        SetAmountToFormatL(ETrue);
    FormatTextL();
    iTextView->SetObserver(this);
    
    CheckEdwinExtensionL(); // checks if iEdwinExtension is non-NULL
    iEdwinExtension->FormCursorModifier()->SetTextView(iTextView);
    DoCreateCustomDrawL();
    }

EXPORT_C void CEikEdwin::SizeChanged()
    {
    __ASSERT_DEBUG(iText,Panic(EEikPanicEdwinNoText));
    CheckEdwinHeight();
    TrappedSizeChanged();
    }

EXPORT_C void CEikEdwin::TrappedSizeChanged()
    {
    TRAPD(err,HandleSizeChangedL());
    if (err)
        {
        CWindowGc& gc=SystemGc();
        gc.Activate(Window());
        TRect rect;
        if (iTextView)
            rect=iTextView->ViewRect();
        else
            {
            rect=Rect();
            rect=iBorder.InnerRect(rect);
            }
        gc.Clear(rect);
        gc.Deactivate();
        iEikonEnv->NotifyIdleErrorWhileRedrawing(err);
        }
    }

EXPORT_C void CEikEdwin::HandleSizeChangedL()
    {
    if (!iTextView)
        CreateTextViewL();
#ifdef _DEBUG
    if (iMaximumHeight)
        __ASSERT_DEBUG(iSize.iHeight<=iMaximumHeight, Panic(EEikPanicEdwinHeightGreaterThanMaximum));
#endif
    TBool condition( IsFocused() );
    CAknEdwinState* state( EditorState() );
    TBool noInlineEditSpan( !state || 
        state->CurrentInlineEditSpan().Length() <= 0 );
    condition = ( condition && noInlineEditSpan );
    condition = ( condition && ( iEdwinFepSupport->iLengthOfInlineText <= 0 ) );
    if ( condition )
        {
        SetCursorVisibilityL( EFalse );
        }
    TRect displayRect=iBorder.InnerRect(Rect());
    displayRect=iMargins.InnerRect(displayRect);
    
    // Negative width (and possibly height) seem to break iTextView
    // This can happen if editor's width is less than the margins

    // if width equals to zero, will cause the cursor doesn't display in the right-to-left directionality
    // so we set the width and height to smallest value 1.
    const TInt displayRectWith = 1;
    const TInt displayRectHeight = 1;
    if ( displayRect.Width() <= 0 )
        {
        displayRect.iBr.iX = displayRect.iTl.iX + displayRectWith;
        }

    if ( displayRect.Height() <= 0 )
        {
        displayRect.iBr.iY = displayRect.iTl.iY + displayRectHeight;
        }


    iTextView->SetViewRect(displayRect);
    iLayout->SetWrapWidth(LayoutWidth());
    TViewYPosQualifier yPosQualifier;
    yPosQualifier.SetFillScreen();
    yPosQualifier.SetMakeLineFullyVisible();
    SetAmountToFormatL( EFalse, EFalse ); // Not a new doc; Do not reformat
    if (!(iEdwinInternalFlags & ESuppressFormatting))
        iTextView->HandleGlobalChangeNoRedrawL(yPosQualifier); // This does the reformat
    CalculateLineMetricsForBandFormattingL();
    SetScrollBarsL();
    UpdateScrollBarsL();
    if ( condition )
        {
        SetCursorVisibilityL( ETrue );
        }
    // View size changed, Initialize physics here
    iEdwinExtension->InitPhysicsL();        
    }

EXPORT_C TInt CEikEdwin::CountComponentControls() const
    {
    TInt count=CEikBorderedControl::CountComponentControls();
    if (iSBFrame)
        count+=iSBFrame->CountComponentControls();
    return count;
    }

EXPORT_C CCoeControl* CEikEdwin::ComponentControl(TInt aIndex) const
    {
    TInt baseCount=CEikBorderedControl::CountComponentControls();
    if (aIndex<baseCount)
        return CEikBorderedControl::ComponentControl(aIndex);
    aIndex-=baseCount;
    return iSBFrame->ComponentControl(aIndex);
    }

EXPORT_C void CEikEdwin::SetAmountToFormatL(TBool aIsNewDoc)
    {
    if (!iTextView)
        return;
    const TInt chars=iText->DocumentLength();
    if ( iEdwinExtension->iSmiley && !iEdwinExtension->iDisableConvertInFormat )
        {        
        if ( chars > KFullFormatLengthForSmiley )
            {
            ConvertVisibleTextForSmileyL( ETrue );
            }
        else if ( chars > 0 )
            {
            ConvertTextForSmileyL( TCursorSelection( 0, chars ), ETrue );
            }
        }
    if (chars>UpperFullFormattingLength())
        {
        if (aIsNewDoc)
            {
            iLayout->SetAmountToFormat();
            iTextView->FormatTextL();
            const TInt formattedLines=iLayout->NumFormattedLines();
            const TInt formattedHeight=iLayout->FormattedHeightInPixels();
            iAvgCharsPerLine=iLayout->FormattedLength()/formattedLines;
            iAvgLinesInViewRect=Max(1,(iTextView->ViewRect().Height()*formattedLines)/formattedHeight);
            }
        else
            {
            const TInt numLines=iLayout->NumFormattedLines();
            const TInt docHeight=iLayout->FormattedHeightInPixels();
            iAvgCharsPerLine=iLayout->FormattedLength()/numLines;
            iAvgLinesInViewRect=Max(1,(iTextView->ViewRect().Height()*numLines)/docHeight);
            iLayout->SetAmountToFormat();
            iTextView->HandleGlobalChangeNoRedrawL();
            }
        if (IsReadyToDraw() && iSBFrame && iSBFrame->VScrollBarVisibility()!=CEikScrollBarFrame::EOff)
            UpdateScrollBarsL();
        }
    else
        {
        iAvgCharsPerLine=1;
        iAvgLinesInViewRect=0;
        iLayout->SetAmountToFormat(CTextLayout::EFFormatAllText);
        if (aIsNewDoc)
            iTextView->FormatTextL();
        else
            iTextView->HandleGlobalChangeNoRedrawL();
        }
    } 
    
EXPORT_C void CEikEdwin::SetAmountToFormatL( TBool aIsNewDoc, TBool aReFormat )
    {
    if (aReFormat)
        {
        SetAmountToFormatL( aIsNewDoc );
        return;
        }
        
    if (!iTextView)
        return;
    const TInt chars=iText->DocumentLength();
    if ( iEdwinExtension->iSmiley && !iEdwinExtension->iDisableConvertInFormat )
        {        
        if ( chars > KFullFormatLengthForSmiley )
            {
            ConvertVisibleTextForSmileyL( ETrue );
            }
        else if ( chars > 0 )
            {
            ConvertTextForSmileyL( TCursorSelection( 0, chars ), ETrue );
            }
        }
    if (chars>UpperFullFormattingLength())
        {
        iLayout->SetAmountToFormat(CTextLayout::EFFormatBand);
        }
    else
        {
        iLayout->SetAmountToFormat(CTextLayout::EFFormatAllText);
        }
    }

void CEikEdwin::CalculateLineMetricsForBandFormattingL()
    {
    if ( iLayout)
        {
        if (iLayout->IsFormattingBand())
            {
            const TInt numLines=iLayout->NumFormattedLines();
            const TInt docHeight=iLayout->FormattedHeightInPixels();
            
            // To make sure that division by 0 does not happen in any situation.
            if (numLines > 0)
                {
                iAvgCharsPerLine=iLayout->FormattedLength()/numLines;                
                }
            else
                {
                iAvgCharsPerLine = 1;
                }

            // To make sure that division by 0 does not happen in any situation.
            if (docHeight > 0)
                {
                iAvgLinesInViewRect=Max(1,(iTextView->ViewRect().Height()*numLines)/docHeight);                           
                }
            else
                {
                iAvgLinesInViewRect=0;                
                }
            }
        else
            {
            iAvgCharsPerLine=1;
            iAvgLinesInViewRect=0;
            }
        if (IsReadyToDraw() && iSBFrame && iSBFrame->VScrollBarVisibility()!=CEikScrollBarFrame::EOff)
            UpdateScrollBarsL();        
        }
    }
    
EXPORT_C void CEikEdwin::ReportEdwinEventL(MEikEdwinObserver::TEdwinEvent aEventType)
    {
    if(iCustomDrawer && aEventType==MEikEdwinObserver::EEventFormatChanged)
        iCustomDrawer->LineSpacingChanged();
    if (iEdwinObserver!=NULL)
        iEdwinObserver->HandleEdwinEventL(this,aEventType);
    if (iCcpuSupport)
        iCcpuSupport->HandleSelectionChangeL();
    if (iObserverArray)
        {
        const TInt count=iObserverArray->Count();
        for (TInt ii=0;ii<count;ii++)
            (*iObserverArray)[ii]->HandleEdwinEventL(this,aEventType);
        }
    if ( aEventType == MEikEdwinObserver::EEventScroll || 
        aEventType == MEikEdwinObserver::EEventNavigation 
        )
        {
        HandleScrollForSmileyL();        
        }
    if ( aEventType == MEikEdwinObserver::EEventTextUpdate )
        {
        iEdwinExtension->iExtendedInputCapabilities->ReportEventL( 
                CAknExtendedInputCapabilities::
                    MAknEventObserver::EControlContentUpdatedInternally,
                NULL );
        }
    }
    


EXPORT_C void CEikEdwin::NotifyNewDocumentL()
    {
    __ASSERT_DEBUG(iTextView,Panic(EEikPanicEdwinNoView));
    __ASSERT_DEBUG(iText,Panic(EEikPanicEdwinNoText));
    TViewYPosQualifier yPosQ;
    yPosQ.SetMakeLineFullyVisible();
    yPosQ.SetFillScreen(); // ???
    iTextView->HandleGlobalChangeL(yPosQ);
    TInt topLeftYPos=iTextView->ViewRect().iTl.iY;
    iTextView->SetViewL(0,topLeftYPos,yPosQ);
    iTextView->SetDocPosL(0);
    SetAmountToFormatL(ETrue); // performs formatting
    UpdateScrollBarsL();
    }

EXPORT_C void CEikEdwin::NotifyNewFormatL()
    {
    if(iCustomDrawer)
        iCustomDrawer->LineSpacingChanged();
    __ASSERT_DEBUG(iTextView,Panic(EEikPanicEdwinNoView));
    TViewYPosQualifier yPosQualifier;
    yPosQualifier.SetMakeLineFullyVisible();
    yPosQualifier.SetFillScreen();
    if( !(iEdwinInternalFlags & ESuppressFormatting))
        {
        iTextView->HandleGlobalChangeNoRedrawL(yPosQualifier);
        ForceScrollBarUpdateL();
        // Drawing here is controlled by an internal mechanism
        CAknEdwinDrawingModifier* modifier = AknEdwinDrawingModifier();
        if ( ! (iEdwinInternalFlags & ESuppressNotifyDraw) )
            {
            if ( !(modifier && modifier->InhibitNotifyNewFormatDrawing()) )
                {
                DrawDeferred();                
                } 
            }
        
        }
    }

EXPORT_C void CEikEdwin::SetCursorPosL(TInt aDocPos,TBool aSelect)
    {
    // CTextView::SetDocPosL will cause textview to be drawn. This could happen 
    // before the drawing of editor. So adding following codes to postpone the action to
    // first drawing of editor.
    if ( iEdwinExtension->iDrawInvoked == CEikEdwinExtension::ENotDraw )
        {
        iEdwinExtension->iTempCursorPos = aDocPos;
        iEdwinExtension->iTempSelect = aSelect;
        if ( !aSelect )
            {
            iEdwinExtension->iTempAnchorPos = KErrNotFound;
            }
        return;
        }
        
    if ( IsFocused() )
        {
        CancelFepTransaction(); 
        }

    if (!iTextView)
        CreateTextViewL();
    TInt oldPos( CursorPos() );
    TInt docPos( aDocPos );
    if ( iEdwinExtension->iSmiley )
        {
        iEdwinExtension->iSmiley->HandleSetCursor( oldPos, docPos );
        }
    TCursorSelection select( Selection() );
    select.iCursorPos = docPos;
    if ( !aSelect )
        {        
        select.iAnchorPos = docPos;
        }
    HandleSelectionForSmiley( select );
    iTextView->SetDocPosL( docPos, aSelect );
    ScrollIfAtTopOrBottomL();
    
    if ( iEdwinFepSupport && 
        ( aDocPos != oldPos || ( select.Length() > 0 && !aSelect ) ) )
        {
        CAknEdwinState* edwinState = static_cast<CAknEdwinState*>( iEdwinFepSupport->State(KNullUid) );
        if ( edwinState )
            {
            TRAP_IGNORE( edwinState->ReportAknEdStateEventL( MAknEdStateObserver::EAknCursorPositionChanged ) );
            }
        }
        
    UpdateVertScrollBarThumbL();
    UpdateHorizScrollBarThumb();
    }

EXPORT_C void CEikEdwin::SetDocumentOwnership(TOwnershipType aOwner)
    {
    if (aOwner==EOwnsText)
        iEdwinUserFlags&=~EKeepDocument;
    else
        iEdwinUserFlags|=EKeepDocument;
    }

EXPORT_C void CEikEdwin::SetSelectionL(TInt aCursorPos,TInt aAnchorPos)
    {
    if( IsFocused() )
        {
        CancelFepTransaction();
        }
    if (!iTextView)
        CreateTextViewL();
    if ( iEdwinExtension->iDrawInvoked == CEikEdwinExtension::ENotDraw )
        {        
        iEdwinExtension->iTempCursorPos = aCursorPos;
        iEdwinExtension->iTempAnchorPos = aAnchorPos;
        return;
        }
    if ( IsSmileyEnabled() )
        {
        iEdwinExtension->iSmiley->HandleSetCursor( aAnchorPos, aCursorPos );
        iEdwinExtension->iSmiley->HandleSetCursor( aCursorPos, aAnchorPos );
        }
    TCursorSelection select( aCursorPos, aAnchorPos );    
    HandleSelectionForSmiley( select );
    iTextView->SetSelectionL( select );
    iEdwinExtension->iThumbPos =  KErrNotFound;

    if ( iEdwinFepSupport )
        {
        CAknEdwinState* edwinState = static_cast<CAknEdwinState*>( iEdwinFepSupport->State(KNullUid) );
        if ( edwinState )
            {
            TRAP_IGNORE( edwinState->ReportAknEdStateEventL( MAknEdStateObserver::EAknCursorPositionChanged ) );
            }
        }
    CancelInsertCharFormat();
    UpdateVertScrollBarThumbL();
    UpdateHorizScrollBarThumb();
    }

EXPORT_C void CEikEdwin::SelectAllL()
    {
    CancelFepTransaction();
    SetSelectionL( TextLength(), 0 );
    }

TBool CEikEdwin::OwnsScrollBars() const
    {
    if (!iSBFrame)
        return EFalse;
    return ((iSBFrame->ScrollBarVisibility(CEikScrollBar::EHorizontal)!=CEikScrollBarFrame::EOff)||(iSBFrame->VScrollBarVisibility()!=CEikScrollBarFrame::EOff));
    }

EXPORT_C void CEikEdwin::SetWordWrapL(TBool aWrapIsOn)
    {
    __ASSERT_DEBUG(iText,Panic(EEikPanicEdwinNoText));
    __ASSERT_DEBUG(iLayout,Panic(EEikPanicEdwinNoLayout));
    if (aWrapIsOn)
        {
        iEdwinUserFlags&=~ENoWrap;
        iLayout->ForceNoWrapping(EFalse);
        iLayout->SetWrapWidth(LayoutWidth());
        }
    else
        {
        iEdwinUserFlags|=ENoWrap;
        iLayout->ForceNoWrapping();
        }
    NotifyNewFormatL();
    }

EXPORT_C TInt CEikEdwin::LineCursorWidth() const
    {
    return 0;
    }

EXPORT_C void CEikEdwin::SetLineCursorDetailsL()
    {
    __ASSERT_DEBUG(iTextView,Panic(EEikPanicEdwinNoView));
    iTextView->SetMarginWidths(0,LineCursorWidth());
    }

EXPORT_C void CEikEdwin::SetTextLimit(TInt aLimit)
    {
#if defined(_DEBUG)
    if (aLimit<iText->DocumentLength())
        Panic(EEikPanicEdwinInvalidTextLimit);
#endif
    iTextLimit=aLimit;
    }

EXPORT_C TMargins8 CEikEdwin::Margins() const
    {
    return iMargins;
    }

void CEikEdwin::ApplyAutoSelectionL()
    {
    if ( iEdwinUserFlags & EAvkonNotEditable )
        return;
    const TInt length=TextLength();
    if (iEdwinUserFlags&EJustAutoCurEnd)
        {
        SetCursorPosL(length,EFalse);
        }        
    else if (!(iEdwinUserFlags&ENoAutoSelection))
        {
        SetSelectionL(length,0);        
        }        
    else
        {
        SetCursorPosL(0,EFalse);
        }    
    }

EXPORT_C TSize CEikEdwin::MinimumSize()
    {
    TSize edwinSize = iSize;
    if ((iEdwinUserFlags&EResizable) && (edwinSize.iHeight == 0))
        {
        if ((iMinimumHeight > 0) && (edwinSize.iHeight < iMinimumHeight))
            edwinSize.iHeight = iMinimumHeight;
        }
    return edwinSize;
    }

EXPORT_C void CEikEdwin::SetContainerWindowL(const CCoeControl& aParent)
    {
    if (iEdwinUserFlags&EOwnsWindow && !OwnsWindow())
        CreateWindowL(&aParent);
    else
        CCoeControl::SetContainerWindowL(aParent);

    iEdwinExtension->EnablePhysicsL();
    }

EXPORT_C void CEikEdwin::SetContainerWindowL()
    {
    __ASSERT_DEBUG(iEdwinUserFlags&EOwnsWindow, Panic(EEikPanicEdwinNoWindow));
    if (!OwnsWindow())
        CreateWindowL();

    iEdwinExtension->EnablePhysicsL();   
    }

EXPORT_C TCoeInputCapabilities CEikEdwin::InputCapabilities() const
    {
    if (IsReadOnly())
        {
        TCoeInputCapabilities readOnlyInputCaps( TCoeInputCapabilities::ENavigation );
        readOnlyInputCaps.SetObjectProvider( const_cast<CEikEdwin*>( this ) );
        return readOnlyInputCaps;
        }

    TCoeInputCapabilities inputCaps( LafEdwin::InputCapabilities(),iEdwinFepSupport,NULL,TUid::Uid(0x100056de),iEdwinFepSupport );
    inputCaps.SetObjectProvider( const_cast<CEikEdwin*>( this ) );

    if (iEdwinFepSupport!=NULL)
        {
        const TCoeInputCapabilities* inputCapabilities=iEdwinFepSupport->InputCapabilities();
        
        if (inputCapabilities!=NULL)
            {
            return *inputCapabilities;
            }
        
        // This tries to sense that this is a numeric-only edwin, and
        // set the input caps so that FEP would use the _digit mode_ instead
        // of input language mode when choosing input type and indicator    
        CAknEdwinState* state = static_cast<CAknEdwinState*>( iEdwinFepSupport->State( KNullUid ) );
        if ( state )
            {
            if ( state->PermittedInputModes() == EAknEditorNumericInputMode )
                {
                inputCaps.SetCapabilities( inputCaps.Capabilities() | 
                    TCoeInputCapabilities::EWesternNumericIntegerPositive |
                    TCoeInputCapabilities::EWesternNumericIntegerNegative );
                }
            }
        }
        
    return inputCaps;
    }

EXPORT_C void CEikEdwin::SetInputCapabilitiesL(const TCoeInputCapabilities& aInputCapabilities)
    {
    User::LeaveIfNull(iEdwinFepSupport);
    iEdwinFepSupport->SetInputCapabilitiesL(aInputCapabilities);
    }

EXPORT_C void CEikEdwin::FormatTextL()
    {
    if (iTextView) // else FormatTextL() will get called later, in ActivateL()
        iTextView->FormatTextL();
    }

/**
 * @internal
 */
EXPORT_C void CEikEdwin::CreateLayoutL(MLayDoc* aLayDoc)
    {
    __ASSERT_DEBUG(aLayDoc,Panic(EEikPanicEdwinNoText));

    if ((iEdwinUserFlags&EAvkonEditor))
        {
        iLayout=CTextLayout::NewL(aLayDoc,KMaxTInt); // supply real wrapping width later
        iLayout->SetCustomWrap(&(iEdwinExtension->TextWrapper()));
        
        // This WAS ETrue, then fixed to EFalse, caused regression and now back to
        // ETrue. In case it is true the editor scrolls _always_
        // so that the topmost line is visible, and the baselines are nicely
        // aligned. This had a side effect which sometimes caused editors to
        // display only partial lines in the bottom, even if the cursor was in that
        // line. Setting this to false makes sure that the line where cursor is
        // is always displayed properly, but causes small less-than-linespacing
        // scrolls in some occasions where the editor's size doesn't match the
        // multiple of font and its highlights and line spacing.
        //iLayout->RestrictScrollToTopsOfLines( EFalse );

        if ( KineticScrollingEnabled() )
            {
            // With kinetic scrolling this is set to EFalse.
            // ScrollDisplayPixelsL and ScrollDisplayPixelsNoLimitBorderL
            // won't move content pixel by pixel (but line by line)
            // if this is not EFalse.
            iLayout->RestrictScrollToTopsOfLines( EFalse );
            }
        else
            {
            iLayout->RestrictScrollToTopsOfLines( ETrue );
            }       

        // the default FontHeightIncreaseFactor in FORM is EDefaultFontHeightIncreaseFactor==7,
        // but the Avkon modified FORM change this to 6
        // Moved this modification out and using the provided interface instead
        iLayout->SetFontHeightIncreaseFactor(6);
        // not originally merged in
        //iLayout->SetMinimumLineDescent(0);
        }
    else
        {
        iLayout=CTextLayout::NewL(aLayDoc,KMaxTInt); // supply real wrapping width later
        // Was ETrue, see above.
        iLayout->RestrictScrollToTopsOfLines( EFalse );
        //iLayout->RestrictScrollToTopsOfLines(ETrue);
        // not originally merged in
        //iLayout->SetMinimumLineDescent(0);
        }

    CheckEdwinExtensionL(); // checks if iEdwinExtension is non-NULL
    iEdwinExtension->FormCursorModifier()->SetTextLayout(iLayout);
    }

EXPORT_C void CEikEdwin::SetAvkonWrap(TBool aAvkonWrapIsOn)
    {
    if (aAvkonWrapIsOn)
        iEdwinUserFlags|=EAvkonEditor;
    else
        iEdwinUserFlags&=~EAvkonEditor;
    }

EXPORT_C void CEikEdwin::Draw(const TRect& /*aRect*/) const
    {
    CEikEdwin* me = const_cast< CEikEdwin* > ( this );
    me->iEdwinInternalFlags |= ESkipBackgroundDrawer;

    if ( iTextView )
        {
        const TRect rect=Rect();
        CWindowGc& gc=SystemGc();

        const TRect viewRect=iTextView->ViewRect();

        TRgb dummyColor;
        TRgb backgroundColor = EditorBackgroundColor(dummyColor); 
        gc.SetBrushColor( backgroundColor );

        if ( !IsBackgroundDrawingSuppressed() )
            {
            // Text view may not occupy the whole control area.  So we need to draw in the gaps
            DrawBackgroundAroundTextView( gc, rect, viewRect, backgroundColor );
            }

        TrappedDraw(viewRect);

    #ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
        // Workaround for clipping rect problem in multiline queries with text
        // entries.  Because of differences between CRemoteGc and CWindowGc, 
        // parts of the query wouldn't be drawn by CRemoteGc.  The Reset() call
        // is to cancel the clipping rect.  For some reason, CancelClippingRect()
        // and CancelClippingRegion() don't work.
        gc.Reset();
    #endif
        }

    me->iEdwinInternalFlags &= ~ESkipBackgroundDrawer;
    }

void CleanupReleaseFont(TAny* aFont)
    {
    CFont** fontPtr = (CFont**)aFont;
    CEikonEnv::Static()->ScreenDevice()->ReleaseFont(*fontPtr);
    }

void CEikEdwin::DrawFirstLineTextL() const
    {
   
    HBufC* clipbuf = GetTextInHBufL();
    CleanupStack::PushL(clipbuf);

    TPtrC clipbufPtr = clipbuf->Des();
    TMargins8 margins = Margins();
    const TRect rect(Rect());
    TInt cursorWidth = CursorWidth(); // need to add cursor width to right hand margin
    TRect edwinRect = AknLayoutUtils::RectFromCoords(rect, margins.iLeft, margins.iTop, margins.iRight+cursorWidth, margins.iBottom, ELayoutEmpty, ELayoutEmpty);

    TAknTextLineLayout textLayout = AknLayoutScalable_Avkon::data_form_wide_pane_t1(0).LayoutLine();
    const CAknLayoutFont* font = AknLayoutUtils::LayoutFontFromId( textLayout.FontId());

    // reorder the text
    AknBidiTextUtils::PrepareRunInfoArray(clipbufPtr);

    HBufC* reorderedText = HBufC::NewLC(clipbufPtr.Length() + TBidiLogicalToVisual::KMinCharAvailable);
    TPtr reorderedTextPtr = reorderedText->Des();
    TInt width = edwinRect.Size().iWidth;
    AknBidiTextUtils::ConvertToVisualAndClip(clipbufPtr, reorderedTextPtr, *font, width, width);
    AknTextUtils::ReplaceCharacters( reorderedTextPtr, _L("\x2029"), TChar(' ') );
    CleanupStack::Pop(reorderedText);   
    CleanupStack::PopAndDestroy(clipbuf);   
    CleanupStack::PushL(reorderedText);

    CGraphicsContext::TTextAlign alignment = CGraphicsContext::ELeft;
    switch(CurrentAlignment())
        {
        case EAknEditorAlignLeft:
            alignment = CGraphicsContext::ELeft;
            break;
        case EAknEditorAlignCenter:
            alignment = CGraphicsContext::ECenter;
            break;
        case EAknEditorAlignRight:
            alignment = CGraphicsContext::ERight;
            break;
        case EAknEditorAlignNone: // drop through to default
        case EAknEditorAlignBidi: // drop through to default
        default:
            {
            if (TBidiText::TextDirectionality(reorderedTextPtr) == TBidiText::ELeftToRight)
                alignment = CGraphicsContext::ELeft;
            else
                alignment = CGraphicsContext::ERight;
            }
            break;
        }
        
    CWindowGc& gc=SystemGc();               
    gc.UseFont(font);

    // Following patching up of the GC are now necessary after calling LafCustomDrawerfor background
    gc.SetBrushStyle(CGraphicsContext::ENullBrush);
    gc.SetPenStyle(CGraphicsContext::ESolidPen);
    TRgb textColor=iEikonEnv->ControlColor(EColorControlText,*this);

    gc.SetPenColor(textColor);  // Text color

    // Edwin is assumed to be laid out already with LayoutEdwin. In that case
    // the textpane top is the top of the edwin
    TInt ascent = font->TextPaneTopToBaseline();
    
    gc.DrawText(reorderedTextPtr, edwinRect, ascent, alignment);

    CleanupStack::PopAndDestroy(reorderedText);
    
    gc.DiscardFont(); // So the GC will not try to use the font.
    }

EXPORT_C void CEikEdwin::TrappedDraw(const TRect& aViewRect) const
    {
    if ( iEdwinExtension->iDrawInvoked == CEikEdwinExtension::ENotDraw )
        {
        CEikEdwin* edwin( const_cast<CEikEdwin*>( this ) );
        edwin->iEdwinExtension->iDrawInvoked = CEikEdwinExtension::EDrawing;
        TRAP_IGNORE( edwin->PerformRecordedOperationL(); );
        }
    if (!(iEdwinUserFlags & EAvkonNotEditable))
        {
        TRAPD(err, iTextView->DrawL(aViewRect,SystemGc()) );
        if (err)
            {
            SystemGc().Clear(aViewRect);
            iEikonEnv->NotifyIdleErrorWhileRedrawing(err);
            }
        }
    else
        {
        if(TextLength() == 0) // no text, so nothing to draw.
            return;
            
        // If a non-editable edwin does not vertically fit to the parent window,
        // do not draw the text
        // TODO: commented code below should be flagged run-time
/*        TRect parentRect = DrawableWindow()->GetDrawRect(); 
        if( aViewRect.iTl.iY < parentRect.iTl.iY ||
            aViewRect.iBr.iY > parentRect.iBr.iY ) 
            return;*/
        
        TRAP_IGNORE(DrawFirstLineTextL());      
        }
    }

EXPORT_C void CEikEdwin::SetDimmed(TBool aDimmed)
    {
    CCoeControl::SetDimmed(aDimmed);
    TRgb dimmedColor=iEikonEnv->ControlColor(EColorControlDimmedText,*this); // KEikEdwinDimmedTextColor
    TRgb* pointer=(&dimmedColor);
    if (!aDimmed)
        pointer=NULL;
    if (!iTextView)
        {
        TRAPD(err,CreateTextViewL());
        if (err)
            {
            SystemGc().Clear(iTextView->ViewRect());
            iEikonEnv->NotifyIdleErrorWhileRedrawing(err);
            }
        }
    iTextView->SetTextColorOverride(pointer);
    
    // make scrollbar also dimmed
    if (iSBFrame && iSBFrame->ScrollBarVisibility(CEikScrollBar::EHorizontal)!=CEikScrollBarFrame::EOff)
        {
        CEikScrollBar* sb = iSBFrame-> CEikScrollBarFrame::HorizontalScrollBar();
        sb->SetDimmed(aDimmed);
        }
    if (iSBFrame && iSBFrame->ScrollBarVisibility(CEikScrollBar::EVertical)!=CEikScrollBarFrame::EOff)
        {
        CEikScrollBar* sb = iSBFrame-> CEikScrollBarFrame::VerticalScrollBar();
        sb->SetDimmed(aDimmed);
        }
    }

EXPORT_C void CEikEdwin::DrawContents()
    {
    if ( CAknEnv::Static()->TransparencyEnabled() )
        {
        if ( IsReadyToDraw() )
            {
            // Note that rect may be larger than iTextView->ViewRect(),
            // so we have to make sure the whole area is drawn. The
            // easiest way to achieve this is to call DrawNow.

            const TRect rect=iBorder.InnerRect(Rect());
            DrawNow( rect );
            }
        }
    else
        {
        if ( IsReadyToDraw() )
            {
            const TRect rect=iBorder.InnerRect(Rect());
            CWindowGc& gc=iEikonEnv->SystemGc();

            gc.Activate(Window());
            TrappedDraw(rect); //assumes the SystemGc is active
            gc.Deactivate();
            }
        }
    }

EXPORT_C void CEikEdwin::EditObserver(TInt aStartEdit,TInt aEditLength )
    {
    if( EdwinExtension() )
        {
        if ( EdwinExtension()->InlineTextSource() )
            EdwinExtension()->InlineTextSource()->EditObserver( aStartEdit, aEditLength );
        }
    }

EXPORT_C void CEikEdwin::CancelSelectionL(TEnd aEndOfSelectionToLeaveCursor)
    {
    CancelFepTransaction();
    __ASSERT_DEBUG(iTextView,Panic(EEikPanicEdwinNoView));
    TCursorSelection cursorSelection=iTextView->Selection();
    SetCursorPosL((aEndOfSelectionToLeaveCursor==EStart)? cursorSelection.LowerPos(): cursorSelection.HigherPos(),EFalse);
    }

EXPORT_C void CEikEdwin::MoveCursorL(TCursorPosition::TMovementType aMovement,TBool aSelect)
    {
    CancelFepTransaction();    
    __ASSERT_DEBUG(iTextView,Panic(EEikPanicEdwinNoView));
    if ( aMovement == TCursorPosition::EFLeft || aMovement == TCursorPosition::EFRight )
        {
        if ( AdjustCursorPosByMovementL( aMovement, aSelect ) )
            {
            return;
            }
        }
    TInt oldCursor( CursorPos() );
    TPoint movePoint=iTextView->MoveCursorL( aMovement, aSelect );
    if ( iEdwinExtension->iSmiley )
        {
        TCursorSelection select( 0, 0 );
        if ( AdjustCursorForSmileyL( oldCursor, select ) )
            {
            SetSelectionL( select.iCursorPos, select.iAnchorPos );
            }
        else
            { 
            HandleSelectionForSmiley( select );
            }
        DrawDeferred();
        }
    if ( movePoint.iX )
        UpdateHorizScrollBarThumb();
    if ( movePoint.iY )
        UpdateVertScrollBarThumbL();

    if ( iEdwinFepSupport )
        {
        CAknEdwinState* edwinState = static_cast<CAknEdwinState*>( 
            iEdwinFepSupport->State( KNullUid ) );
        if ( edwinState )
            {
            TRAP_IGNORE( edwinState->ReportAknEdStateEventL( 
                MAknEdStateObserver::EAknCursorPositionChanged ) );
            }
        }
    }

EXPORT_C void CEikEdwin::MoveDisplayL(TCursorPosition::TMovementType aMovement)
    {
    __ASSERT_DEBUG(iTextView,Panic(EEikPanicEdwinNoView));
    
    // Before scrolling into blank space was allowed, but this eventually
    // causes a panic at CTextView::ScrollDisplayL().
    const TInt move=iTextView->ScrollDisplayL(aMovement,CTextLayout::EFDisallowScrollingBlankSpace);
    if (move)
        {
        iEdwinExtension->iThumbPos = KErrNotFound;
        switch (aMovement)
            {
        case TCursorPosition::EFLeft:
        case TCursorPosition::EFRight:
        case TCursorPosition::EFLineBeg:
        case TCursorPosition::EFLineEnd:
            UpdateHorizScrollBarThumb();
            break;
        case TCursorPosition::EFLineUp:
        case TCursorPosition::EFLineDown:
        case TCursorPosition::EFPageUp:
        case TCursorPosition::EFPageDown:
            UpdateVertScrollBarThumbL();
            break;
        default:
            break;
            }
        }
    }

EXPORT_C void CEikEdwin::CancelInsertCharFormat()
    {
    __ASSERT_DEBUG(iText,Panic(EEikPanicEdwinNoText));
    if (iEdwinInternalFlags&ERichText)
        STATIC_CAST(CRichText*,iText)->CancelInsertCharFormat();
    }

EXPORT_C void CEikEdwin::MoveCursorToChunkStartL(TBool aSelect,TChunkSize aChunkSize,TEnd aEndScanningTowards)
    {
    CancelFepTransaction();
    __ASSERT_DEBUG(iText,Panic(EEikPanicEdwinNoText));
    TInt cursorPos=CursorPos();
    TUint flags=CPlainText::EScanToUnitStart|CPlainText::EScanJoinDelimiters;
    if (aEndScanningTowards==EStart)
        flags|=CPlainText::EScanBackwards;
    switch (aChunkSize)
        {
        case EChunkWord:
            iText->ScanWords(cursorPos,flags);
            break;
        case EChunkPara:
            iText->ScanParas(cursorPos,flags);
            break;
        }
    if (cursorPos==CPlainText::EScanEndOfData)
        cursorPos=TextLength();
    SetCursorPosL(cursorPos,aSelect);
    }

EXPORT_C TInt CEikEdwin::CursorPos() const
    {
    __ASSERT_DEBUG(iTextView,Panic(EEikPanicEdwinNoView));
    if ( iEdwinExtension->iDrawInvoked == CEikEdwinExtension::ENotDraw && 
        iEdwinExtension->iTempCursorPos != KErrNotFound )
        {
        return iEdwinExtension->iTempCursorPos;
        }
    else
        {
        TCursorSelection selection=iTextView->Selection();
        return(selection.iCursorPos);
        }
    }

EXPORT_C TInt CEikEdwin::SelectionLength() const
    {
    __ASSERT_DEBUG(iTextView,Panic(EEikPanicEdwinNoView));
    TCursorSelection selection( 0, 0 );
    if ( iEdwinExtension->iDrawInvoked == CEikEdwinExtension::ENotDraw && 
        iEdwinExtension->iTempCursorPos != KErrNotFound && 
        iEdwinExtension->iTempAnchorPos != KErrNotFound )
        {
        selection.iCursorPos = iEdwinExtension->iTempCursorPos;
        selection.iAnchorPos = iEdwinExtension->iTempAnchorPos;
        }
    else
        {
        selection = iTextView->Selection();
        }
    return(selection.Length());
    }

EXPORT_C TInt CEikEdwin::DeleteHighlightL(TBool& aChanged,TBool aIsBackSpace,TBool aPromptConfirmation)
    {
    __ASSERT_DEBUG(iTextView,Panic(EEikPanicEdwinNoView));
    CancelFepTransaction();
    const TCursorSelection selection=iTextView->Selection();
    if (aPromptConfirmation)
        {
        if (!OkToDeleteSelectionL())
            CBaActiveScheduler::LeaveNoAlert();
        }
    iTextView->CancelSelectionL();
    SetCursorPosL(selection.LowerPos(),EFalse);
    DeleteL(aChanged,selection,aIsBackSpace);
    return(selection.LowerPos());
    }

EXPORT_C TBool CEikEdwin::OkToDeleteSelectionL()
    {
    // Avkon behaviour is always to allow deletion of selection, including
    // pictures.
    return ETrue;
    }

struct STempCleanup { CEikEdwin* iEdwin; };

LOCAL_C void DeleteTemp(TAny* aPtr)
    { STATIC_CAST(STempCleanup*,aPtr)->iEdwin->ClearUndo(); }

EXPORT_C void CEikEdwin::DeleteL(TBool& aChanged,const TCursorSelection& aSelection,TBool aIsBackSpace,TBool aAllowUndo)
    {
    __ASSERT_DEBUG(iText,Panic(EEikPanicEdwinNoText));
    CancelFepTransaction();
    if (aAllowUndo && !SetUndoBufferL(aSelection))
        CBaActiveScheduler::LeaveNoAlert();
    STempCleanup tempCleanup;
    tempCleanup.iEdwin=this;
    CleanupStack::PushL(TCleanupItem(DeleteTemp,&tempCleanup));
    const TInt length=Max(1,aSelection.Length());
    if ((iEdwinInternalFlags&ERichText) && aIsBackSpace)
        aChanged=STATIC_CAST(CRichText*,iText)->DelSetInsertCharFormatL(aSelection.LowerPos(),length);
    else
        {
        if (iEdwinInternalFlags&ERichText)
            STATIC_CAST(CRichText*,iText)->CancelInsertCharFormat();
        aChanged=iText->DeleteL(aSelection.LowerPos(),length);
        }
    if ( iEdwinExtension->iSmiley )
        { 
        iEdwinExtension->iSmiley->HandleDeleteL( aSelection.LowerPos(), length );
        }
    CleanupStack::Pop();
    }

EXPORT_C TInt CEikEdwin::TextLength() const
    {
    __ASSERT_DEBUG(iText,Panic(EEikPanicEdwinNoText));
    return(iText->DocumentLength());
    }

void CEikEdwin::SetCursorVisibilityL(TBool aEmphasis)
    {
    TCursor::TVisibility textCursor=(aEmphasis? TCursor::EFCursorFlashing : TCursor::EFCursorInvisible);
    TCursor::TVisibility lineCursor=((iEdwinUserFlags&ELineCursor && aEmphasis)? 
                                        TCursor::EFCursorVisible : TCursor::EFCursorInvisible);
    if (iEdwinUserFlags&EAvkonDisableCursor) 
        { 
        textCursor = TCursor::EFCursorInvisible;
        lineCursor = TCursor::EFCursorInvisible;
        }
    
    iTextView->SetCursorVisibilityL(lineCursor,textCursor);
    CAknEdwinState*edwinState = EditorState();
    if( !edwinState )
    	return;
    if( textCursor != TCursor::EFCursorInvisible )
    	{
        SetAknEditorFlags( edwinState->Flags() | EAknEditorFlagTextCursorVisible );
    	}
    else
    	{
    	SetAknEditorFlags( edwinState->Flags() & ~EAknEditorFlagTextCursorVisible );
    	
        // If cursor is disabled during kinetic scrolling
        // by other party (for any reason), reset flag so that we don't show it again
        // when kinetic scrolling stops
        iEdwinExtension->iCursorWasVisible = EFalse;
    	}
    }

EXPORT_C CPlainText* CEikEdwin::Text() const
    {
    return iText;
    }

/**
 * @internal
 * @deprecated
 */
EXPORT_C CTextView* CEikEdwin::TextView() const
    {
    return iTextView;
    }

/**
 * @internal
 * @deprecated
 */
EXPORT_C CTextLayout* CEikEdwin::TextLayout() const
    {
    return iLayout;
    }
    
EXPORT_C void CEikEdwin::SetZoomFactorL(TZoomFactor* aZoomFactor)
    {
    iZoomFactor=aZoomFactor;
    SetAmountToFormatL(ETrue); // isn't new doc at all !!!
    }

EXPORT_C void CEikEdwin::SetBorderViewMargins(TMargins8 aMargins)
    {
    iMargins=aMargins;
    }

EXPORT_C void CEikEdwin::SetBackgroundColorL(TRgb aBackground)
    {
    if (!iTextView)
        CreateTextViewL();
    
    if (iEdwinExtension)
        {
        iEdwinExtension->iEditorBackgroundColor = aBackground;
        }

    // for legacy reasons
    AknLayoutUtils::OverrideControlColorL(*this, EColorControlBackground, aBackground);
    }

EXPORT_C void CEikEdwin::SetWysiwygModeOn(TInt aLayoutWidth,MGraphicsDeviceMap* aDevice)
    {
    __ASSERT_DEBUG(iLayout,Panic(EEikPanicEdwinNoLayout));
    iLayoutWidth=aLayoutWidth;
    iEdwinInternalFlags|=EWysiwygOn;
    iLayout->SetFormatMode(CLayoutData::EFWysiwygMode,aLayoutWidth,aDevice);
    }

EXPORT_C void CEikEdwin::SetWysiwygModeOff()
    {
    __ASSERT_DEBUG(iLayout,Panic(EEikPanicEdwinNoLayout));
    iLayoutWidth=0;
    iEdwinInternalFlags&=~EWysiwygOn;
    iLayout->SetFormatMode(CLayoutData::EFScreenMode,LayoutWidth(),NULL);
    }

EXPORT_C void CEikEdwin::UpdateLayoutWidth(TInt aLayoutWidth)
    {
    __ASSERT_DEBUG(iLayout,Panic(EEikPanicEdwinNoLayout));
    iLayoutWidth=aLayoutWidth;
    iLayout->SetWrapWidth(aLayoutWidth);
    }

EXPORT_C TInt CEikEdwin::UpperFullFormattingLength() const
    {
    if (iEdwinExtension)
        return iEdwinExtension->iUpperFullFormattingLength;
    else        
        return KFullFormattingUpperThreshold;
    }

EXPORT_C TInt CEikEdwin::LowerPartialFormattingLength() const
    {
    if (iEdwinExtension)
        return iEdwinExtension->iUpperFullFormattingLength - KFormattingThresholdGap;
    else
        return KPartialFormattingLowerThreshold;
    }

EXPORT_C void CEikEdwin::SetSuppressNotifyDraw( TBool aEnabled )
    {
    if (aEnabled)
        iEdwinInternalFlags |= ESuppressNotifyDraw;
    else
        iEdwinInternalFlags &= ~ESuppressNotifyDraw;    
    }

EXPORT_C void CEikEdwin::SetSuppressFormatting( TBool aSuppress )
    {
    if (aSuppress)
        iEdwinInternalFlags |= ESuppressFormatting;
    else
        iEdwinInternalFlags &= ~ESuppressFormatting;    
    }
    
EXPORT_C void CEikEdwin::SetReadOnly(TBool aReadOnly)
    {
    if (aReadOnly)
        iEdwinUserFlags|=EReadOnly;
    else
        iEdwinUserFlags&=~EReadOnly;
    }

EXPORT_C TBool CEikEdwin::IsReadOnly() const
    {
    return iEdwinUserFlags&EReadOnly;
    }

EXPORT_C TInt CEikEdwin::AknEditorFlags() 
    { 
    if (EditorState()) 
        { 
        return EditorState()->Flags(); 
        } 
   return KErrNotFound;     
    }

EXPORT_C void CEikEdwin::SetOnlyASCIIChars(TBool aASCIIOnly)
    {
    if (aASCIIOnly)
        iEdwinUserFlags|=EOnlyASCIIChars;
    else
        iEdwinUserFlags&=~EOnlyASCIIChars;
    }

EXPORT_C TBool CEikEdwin::OnlyASCIIChars() const
    {
    return (iEdwinUserFlags&EOnlyASCIIChars) ||
    (AknEdwinFlags() & EAknEditorFlagLatinInputModesOnly);
    }

TBool CEikEdwin::IsValidChar(TInt aChar) const
    {
    TBool ret( ETrue );
    
    if ( OnlyASCIIChars() && aChar >= 255 )
        {
        if ( aChar == KPuaCodeSpaceSymbol
             || aChar == KEuroSign
             )
            {
            ret = ETrue;
            }
        else if ( ( aChar == KDownwardsArrowWithTipLeftwards ||
                    aChar == KDownwardsArrowWithTipRightwards ||
                    aChar == CEditableText::EParagraphDelimiter ||
                    aChar == CEditableText::ELineBreak ) &&
                  !( iEdwinUserFlags & ENoLineOrParaBreaks ||
                     iEdwinInternalFlags & EHasOneLineOnly ) )
            {
            ret = ETrue;
            }
        else
            {
            ret = EFalse;
            }
        }
    
    return ret;
    }

EXPORT_C void CEikEdwin::CheckNotReadOnlyL()
    {
    if (IsReadOnly())
        {
        NotifyInvalidOperationOnReadOnlyL();
        CBaActiveScheduler::LeaveNoAlert();
        }
    }

EXPORT_C void CEikEdwin::NotifyInvalidOperationOnReadOnlyL()
    {
    iEikonEnv->InfoMsg(R_EIK_TBUF_READONLYFILE);
    }

EXPORT_C void CEikEdwin::SetRightWrapGutter(TInt aGap)
    {
    iRightWrapGutter=aGap;
    }

EXPORT_C void CEikEdwin::GetText(TDes& aDes) const
    {
    __ASSERT_DEBUG(iText,Panic(EEikPanicEdwinNoText));

    // Uncommitted text in inline editing might temporarily exceed the maximum
    // allowed number of characters in editor.
    // So, truncate the text to the max allowed number of characters to prevent
    // any buffer overflows in caller code.
    if ( iTextLimit && TextLength() > iTextLimit )
        {
        iText->Extract( aDes, 0, iTextLimit );
        }
    else
        {
        iText->Extract(aDes); // caller's responsibility to provide long enough buffer
        }
    TCursorSelection select( TextLength(), 0 );
    if ( iTextLimit && TextLength() > iTextLimit )
        {
        select.iCursorPos = iTextLimit;
        }
    TBool hasSmiley( EFalse );
    if ( iEdwinExtension->iSmiley )
        {
        hasSmiley = iEdwinExtension->iSmiley->HasSmileyIconsInText();
        }
    if ( hasSmiley )
        {
        // ensure conversion happens
        iEdwinExtension->iSmiley->ConvertTextForSmileyL( select.LowerPos(), aDes, EFalse );
        }
    }

EXPORT_C HBufC* CEikEdwin::GetTextInHBufL() const
    {
    HBufC* ret=NULL;
    TInt textLength=TextLength();
    if (textLength)
        {
        ret=HBufC::NewL(textLength);
        TPtr ptr=ret->Des();
        GetText(ptr);
        }
    return(ret);
    }

EXPORT_C void CEikEdwin::ClearSelectionL()
    { // !! must ensure with CTextView that this never leaves
    if( IsFocused() )
        {
        CancelFepTransaction();
        }
    HandleSelectionForSmiley( TCursorSelection( 0, 0 ) );
    if (iTextView)
    	{
        iTextView->CancelSelectionL();
        if ( iEdwinFepSupport )
            {
            CAknEdwinState* edwinState = static_cast<CAknEdwinState*>( iEdwinFepSupport->State(KNullUid) );
            if ( edwinState )
                {
                TRAP_IGNORE( edwinState->ReportAknEdStateEventL( MAknEdStateObserver::EAknCursorPositionChanged ) );
                }
            }
    	}
    }

EXPORT_C void CEikEdwin::SetTextL(const TDesC* aDes)
    {
    __ASSERT_DEBUG(iText,Panic(EEikPanicEdwinNoText));
    if( IsFocused() )
        {
        CancelFepTransaction();
        }
    if (iEdwinFepSupport && iEdwinFepSupport->State(KNullUid))
        STATIC_CAST(CAknEdwinState*, iEdwinFepSupport->State(KNullUid))->SetInlineEditSpan(TCursorSelection(0,0));
    
    ClearSelectionL();

    TInt err=0;
    if (aDes && aDes->Length())
        {
        _LIT(KLineBreakCharacter, "\n");
        TInt oldLength=iText->DocumentLength();
        HBufC* segmBuf = HBufC::NewL(KSegmSize);
        CleanupStack::PushL(segmBuf);
        TPtr segmBufPtr = segmBuf->Des();
        TInt strLength = aDes->Length();
        TInt strEnd = strLength - 1;
        TInt segmStart = 0;
        TInt segmEnd = 0;
        TInt insertLength =0;
        while ( strLength > 0 && segmStart <= strEnd && segmEnd <= strEnd)
        {
        if ( strEnd - segmEnd < KSegmSize)
            {
            segmEnd = strEnd;
            insertLength = segmEnd - segmStart + 1;
            }
        else
            {
            segmEnd = segmEnd + KSegmSize;
            insertLength = KSegmSize;
            }
        segmBufPtr = aDes->Mid( segmStart, insertLength);
        AknTextUtils::ReplaceCharacters(segmBufPtr, KLineBreakCharacter,
                      TChar(CEditableText::EParagraphDelimiter));
	    iText->InsertL(oldLength+segmStart,*segmBuf);
	    if ( iEdwinExtension->iSmiley )
	        {
	        iEdwinExtension->iSmiley->HandleInsertL( oldLength+segmStart, 
	            insertLength );	        
	        }
	    segmStart = segmEnd;
	    if ( insertLength < KSegmSize && insertLength > 0)
	        {
	        segmEnd++;	
	        }
	    }
	    
	    CleanupStack::PopAndDestroy(segmBuf);
        TRAP(err,iText->DeleteL(0,oldLength));
        if ( iEdwinExtension->iSmiley )
            {
            iEdwinExtension->iSmiley->HandleDeleteL( 0, oldLength );
            ConvertTextForSmileyL( TCursorSelection( 0, 
                iText->DocumentLength() ), ETrue );
            }
        }
    else
        {
        iText->Reset(); // Duplicates previous behaviour where null pointer argument reset text object
        if ( iEdwinExtension->iSmiley )
            {
            iEdwinExtension->iSmiley->HandleDeleteL( 0, 
                iText->DocumentLength() );
            }
        }

    CheckRemovePictures(0,iText->DocumentLength());
    CheckValidityOfChars(0,iText->DocumentLength());
    iEdwinExtension->iDisableConvertInFormat = ETrue;
    SetAmountToFormatL(ETrue); // performs formatting
    iEdwinExtension->iDisableConvertInFormat = EFalse;
	// Update cursor position as CursorWidth() needs that.
    if (IsReadyToDraw())
        {        
        ApplyAutoSelectionL();
        }
    
    TInt left, right=0;
    if (iLayout && iLayout->CalculateHorizontalExtremesL(left,right,ETrue) && iTextView)
        {
        TInt width=iTextView->ViewRect().Width();
        TInt labels=0, cursor=0;
        iTextView->MarginWidths(labels,cursor);
        width-=labels+cursor+labels+cursor+CursorWidth()+iRightWrapGutter;
        if (left+right<width)
            iTextView->SetLeftTextMargin(0);

        if ( iEdwinExtension )
            {
            iEdwinExtension->iExtendedInputCapabilities->ReportEventL( 
                CAknExtendedInputCapabilities::
                MAknEventObserver::EControlContentUpdatedInternally,
                NULL );
            }
        ReportEdwinEventL( MEikEdwinObserver::EEventTextUpdateAPI );
        if ( iCcpuSupport )
            {
            iCcpuSupport->HandleSelectionChangeL();
            }
        }
    if (IsReadyToDraw())
        {
        UpdateScrollBarsL();
        }

    User::LeaveIfError(err);       
    }

EXPORT_C TCursorSelection CEikEdwin::Selection()    const
    {
    if ( iEdwinExtension->iDrawInvoked == CEikEdwinExtension::ENotDraw && 
        iEdwinExtension->iTempCursorPos != KErrNotFound && 
        iEdwinExtension->iTempAnchorPos != KErrNotFound )
        {        
        return TCursorSelection( iEdwinExtension->iTempCursorPos,
            iEdwinExtension->iTempAnchorPos );
        }
    if (iTextView)
        return(iTextView->Selection());
    return TCursorSelection(0,0);
    }

EXPORT_C TInt CEikEdwin::CountWords()
    {
    __ASSERT_DEBUG(iText,Panic(EEikPanicEdwinNoText));
    return(iText->WordCount());
    }

EXPORT_C void CEikEdwin::SetAllowUndo(TBool aAllow)
    {
    if (aAllow)
        iEdwinUserFlags|=EAllowUndo;
    else
        iEdwinUserFlags&=~EAllowUndo;
    }

EXPORT_C TBool CEikEdwin::SupportsUndo() const
    {
    return iEdwinUserFlags&EAllowUndo;
    }

EXPORT_C TBool CEikEdwin::CanUndo() const
    {
    return (iUndoStore!=NULL);
    }
    
EXPORT_C void CEikEdwin::UndoL()
    {
    CancelFepTransaction();
    if (!SupportsUndo())
        return;
    if (!iUndoStore)
        iEikonEnv->InfoMsg(R_EIK_TBUF_NOTHING_TO_UNDO);
    else
        {
        TBool changed=EFalse;
        TCursorSelection newText=iUndoStore->NewText();
        const TInt oldLength=TextLength();
        if (newText.Length())
            DeleteL(changed,newText,EFalse,EFalse);
        const TInt lower=newText.LowerPos();
        TInt undoneLength=0;
        TRAPD(err,undoneLength=iText->PasteFromStoreL(iUndoStore->Store(),iUndoStore->Dictionary(),lower))
        const TInt cursorPos=iUndoStore->OldCursorPos();
        iTextView->SetPendingSelection(TCursorSelection(cursorPos,cursorPos));
        if ( iEdwinExtension->iSmiley )
            {
            iEdwinExtension->iSmiley->HandleInsertL( lower, undoneLength );
            ConvertTextForSmileyL( TCursorSelection( lower, undoneLength ), ETrue );
            }
        TRAPD(err2,iTextView->HandleInsertDeleteL(TCursorSelection(lower,lower+undoneLength),newText.Length(),changed));
        ClearUndo();
        if (NeedToChangeFormattingModeL())
            SetAmountToFormatL();
        ForceScrollBarUpdateL();
        User::LeaveIfError(err);
        User::LeaveIfError(err2);
        ReportEdwinEventL( MEikEdwinObserver::EEventTextUpdate );
        DoReportEventL( MCoeControlObserver::EEventStateChanged );
        }
    }

EXPORT_C void CEikEdwin::ClearUndo()
    {
    delete iUndoStore;
    iUndoStore=NULL;
    }

/**
 * @internal
 */
EXPORT_C TBool CEikEdwin::SetUndoBufferL(const TCursorSelection& aSelection)
    {
    if (iEdwinUserFlags&EAllowUndo)
        {
        TRAPD(err,DoSetUndoBufferL(aSelection));
        if (err!=KErrNone && iUndoStore!=NULL)
            ClearUndo();
        if (err==KErrNoMemory)
            return iEikonEnv->QueryWinL(R_EIK_TBUF_CANNOT_UNDO_CONFIRM_1,R_EIK_TBUF_CANNOT_UNDO_CONFIRM_2);
        User::LeaveIfError(err);
        }
    return ETrue;
    }

void CEikEdwin::DoSetUndoBufferL(const TCursorSelection& aSelection)
    {
    if (iUndoStore)
        ClearUndo();
    iUndoStore=CUndoBuffer::NewL();
    iText->CopyToStoreL(iUndoStore->Store(),iUndoStore->Dictionary(),aSelection.LowerPos(),aSelection.Length());
    const TInt lowerPos=aSelection.LowerPos();
    iUndoStore->SetNewText(TCursorSelection(lowerPos,lowerPos));
    iUndoStore->SetOldCursorPos(aSelection.iCursorPos);
    }

/**
 * @internal
 */
EXPORT_C void CEikEdwin::SetUndoableText(const TCursorSelection& aSelection)
    {
    iUndoStore->SetNewText(aSelection);
    }


CAknEdwinState* CEikEdwin::EditorState() const
    {
    if (iEdwinFepSupport)
        return static_cast<CAknEdwinState*>(iEdwinFepSupport->State(KNullUid));
    else
        return NULL;
    }

EXPORT_C void CEikEdwin::InsertFromTextFileL(const TFileName& aFileName,const CPlainText::TTextOrganisation aTextOrganisation)
    {
    __ASSERT_DEBUG(iText,Panic(EEikPanicEdwinNoText));
    CancelFepTransaction();
    const TInt oldLength = iText->DocumentLength();
    const TInt cursorPos=CursorPos();
    iEikonEnv->BusyMsgL(R_EIK_TBUF_IMPORTING,500000); // after 0.5 seconds
    iText->ImportTextFileL(cursorPos,aFileName,aTextOrganisation);
    TInt insertLength( iText->DocumentLength() - oldLength );
    CheckValidityOfChars( oldLength, insertLength );
    if ( iEdwinExtension->iSmiley )
        {
        iEdwinExtension->iSmiley->HandleInsertL( cursorPos, insertLength );
        ConvertTextForSmileyL( TCursorSelection( cursorPos, 
            cursorPos + insertLength ), ETrue );
        }
    const TInt newLength=iText->DocumentLength();
    const TInt newCursorPos=cursorPos+newLength-oldLength;
    iTextView->SetPendingSelection(TCursorSelection(newCursorPos,newCursorPos));
    if (NeedToChangeFormattingModeL())
        SetAmountToFormatL();
    else
        iTextView->HandleInsertDeleteL(TCursorSelection(newCursorPos,cursorPos),0,ETrue);
    DrawContents();
    UpdateScrollBarsL();
    ReportEdwinEventL( MEikEdwinObserver::EEventTextUpdate );
    DoReportEventL( MCoeControlObserver::EEventStateChanged );
    iEikonEnv->BusyMsgCancel();
    }

EXPORT_C void CEikEdwin::ClipboardL(TClipboardFunc aClipboardFunc)
    {
    __ASSERT_DEBUG(iTextView,Panic(EEikPanicEdwinNoView));
    
    TInt prevEndPosition( 0 );
    if ( KineticScrollingEnabled() )
        {
        prevEndPosition =
            iLayout->PixelsAboveBand() + AdjustedViewRect().Height();
        }
    
    TBool commitInline( aClipboardFunc == EPaste );
    TCursorSelection selection( 0, 0 );
    CAknEdwinState* state( EditorState() );    
    if ( !commitInline && aClipboardFunc == ECut )
        {    
        selection = iTextView->Selection();
        TInt startOfInline( iEdwinFepSupport->iPositionOfInlineTextInDocument );        
        TInt endOfInline( iEdwinFepSupport->iPositionOfInlineTextInDocument + 
            iEdwinFepSupport->iLengthOfInlineText );
        if ( iEdwinFepSupport->iLengthOfInlineText < 0 )
            {          
            if ( state && state->CurrentInlineEditSpan().Length() > 0 )
                {
                startOfInline = state->CurrentInlineEditSpan().LowerPos();
                endOfInline = state->CurrentInlineEditSpan().HigherPos();
                }
            }
        commitInline = ( selection.LowerPos() < endOfInline && 
            selection.HigherPos() > startOfInline );
        }
    if ( commitInline )
        {
        if ( iEdwinFepSupport->iLengthOfInlineText > 0 )
            {
            iEdwinFepSupport->DoCommitFepInlineEditL();
            SetCursorVisibilityL( ETrue );
            }
        if ( state && state->CurrentInlineEditSpan().Length() > 0 ) 
            {
            state->SetInlineEditSpan( TCursorSelection( 0, 0 ) );
            }
        }
    CancelFepTransaction();
    TBool reportChange=EFalse;
    switch (aClipboardFunc)
        {   
    case ECut:
    case ECopy:
        {
        TCursorSelection selection=iTextView->Selection();
        const TInt selLength=SelectionLength();
        if (!selLength)
            iEikonEnv->InfoMsg(aClipboardFunc==ECut? R_EIK_TBUF_NOTHING_TO_CUT: R_EIK_TBUF_NOTHING_TO_COPY);
        else
            {
            PlaceDataOnClipboardL();
            if (aClipboardFunc==ECopy)
                {
                iEikonEnv->InfoMsg(R_EIK_TBUF_COPIED);
                if (iCcpuSupport)
                    iCcpuSupport->HandleSelectionChangeL();
                }
            else
                {
                TBool formatHasChanged;
                DeleteHighlightL(formatHasChanged,EFalse,EFalse);
                const TInt lower=selection.LowerPos();
                const TCursorSelection pending(lower,lower);
                iTextView->SetPendingSelection(pending);
                selection.iAnchorPos=lower;
                selection.iCursorPos=lower;
                iTextView->HandleInsertDeleteL(selection,selLength,formatHasChanged);
                reportChange=ETrue;
                }
            CAknNoteDialog* dlg = new (ELeave) CAknNoteDialog();
            dlg->SetTimeout( CAknNoteDialog::EShortTimeout );
            dlg->SetTone( CAknNoteDialog::ENoTone );
            dlg->ExecuteLD( R_AVKON_NOTE_CONF_COPIED );            
            }
        break;
        }
    case EPaste:
        RetrieveDataFromClipboardL();
        reportChange=ETrue;
        break;
    default:
#if defined(_DEBUG)
        Panic(EEikPanicEdwinBadClipboardFunc);
#endif
        break;
        }
    
    if ( KineticScrollingEnabled() )
        {
        // If we have deleted some text and previous position (before delete) is
        // out of current editor content, we must move back to inside content.
        TInt formattedHeight( iLayout->FormattedHeightInPixels() );
        if ( prevEndPosition > formattedHeight )
           {
           TInt movement( prevEndPosition - formattedHeight );   
           iEdwinExtension->iPhysicsHandler->MoveScrollIndex( movement );
           }
        }
    
    if (reportChange)
        {
        ReportEdwinEventL( MEikEdwinObserver::EEventTextUpdate );
        DoReportEventL( MCoeControlObserver::EEventStateChanged );
        NotifyEditorStateObserverOfStateChangeL();
        UpdateScrollBarsL();
        }
    }

EXPORT_C void CEikEdwin::PlaceDataOnClipboardL()
    {
    __ASSERT_DEBUG(iText,Panic(EEikPanicEdwinNoText));
    CancelFepTransaction();
    CClipboard* cb=CClipboard::NewForWritingLC(iCoeEnv->FsSession());
    CopyToStoreL(cb->Store(),cb->StreamDictionary());
    cb->CommitL();
    CleanupStack::PopAndDestroy();
    }

void CEikEdwin::RetrieveDataFromClipboardL()
    {
    CancelFepTransaction();
    CClipboard* cb=NULL;
    TRAPD(err,cb=CClipboard::NewForReadingL(iCoeEnv->FsSession()));
    CleanupStack::PushL(cb);
    if (err==KErrPathNotFound || err==KErrNotFound)
        iEikonEnv->LeaveWithInfoMsg(R_EIK_TBUF_NOTHING_TO_PASTE);
    User::LeaveIfError(err);
    PasteFromStoreL(cb->Store(), cb->StreamDictionary());
    CleanupStack::PopAndDestroy();  // cb
    }

EXPORT_C void CEikEdwin::SendDataOverIrL()
    {
    __ASSERT_DEBUG(iText,Panic(EEikPanicEdwinNoText));
    iEikonEnv->IrFactory()->SendDataOverIrL(this);
    }

EXPORT_C void CEikEdwin::ReceiveDataOverIrL()
    { 
    iEikonEnv->IrFactory()->ReceiveDataOverIrL(this);
    }

EXPORT_C void CEikEdwin::CopyToStoreL(CStreamStore& aStore,CStreamDictionary& aDict)
    {
    CancelFepTransaction();
    TCursorSelection selection=Selection();
    CPlainText* text( iText );
    TInt start( selection.LowerPos() );
    HBufC* buf( NULL );
    if ( iEdwinExtension->iSmiley )
        {
        buf = ExtractTextLC( selection );
        text = CPlainText::NewL();
        CleanupStack::PushL( text );
        TPtr ptr( buf->Des() );
        iEdwinExtension->iSmiley->ConvertTextForSmileyL( selection.LowerPos(),
            ptr, EFalse );
        start = 0;
        text->InsertL( start, *buf );                
        }
    text->CopyToStoreL(aStore, aDict, start, selection.Length() );
    if ( iEdwinExtension->iSmiley )
        {
        CleanupStack::PopAndDestroy( text );    
        CleanupStack::PopAndDestroy( buf );
        }
    }

EXPORT_C void CEikEdwin::PasteFromStoreL(CStreamStore& aStore,CStreamDictionary& aDict)
    {
    CancelFepTransaction();
    TStreamId streamId=aDict.At(KClipboardUidTypeRichText);
    if (streamId==KNullStreamId)
        streamId=aDict.At(KClipboardUidTypePlainText);
    TInt nothingResId=(iEdwinInternalFlags&EPasteFromIrStore)? R_EIK_TBUF_UNSUITABLE_IR_TYPE : R_EIK_TBUF_NOTHING_TO_PASTE;
    SetPasteFromIrStore(EFalse); // nothing to leave before this line
    if (streamId==KNullStreamId)
        iEikonEnv->LeaveWithInfoMsg(nothingResId);
    iEikonEnv->BusyMsgL(R_EIK_TBUF_PASTING,500000);
    TCursorSelection selection=iTextView->Selection();
    const TInt oldTextLength=TextLength();
    const TInt selLength=selection.Length();
    TBool formatHasChanged=EFalse;
    if (selLength)
        DeleteHighlightL(formatHasChanged);
    else
        ClearUndo();
    const TInt lengthBeforePaste=TextLength();
    TRAPD(err,DoPasteFromStoreL(aStore,aDict));
    TInt newLength=iText->DocumentLength();
    TInt pastedLength=newLength-lengthBeforePaste;
    if (err!=KErrNone && pastedLength==0)
        {
        ClearUndo();
        User::Leave(err);
        }
    const TInt higher=selection.HigherPos()+newLength-oldTextLength;
    iTextView->SetPendingSelection(TCursorSelection(higher,higher));
    selection.iAnchorPos=selection.LowerPos();
    selection.iCursorPos=selection.iAnchorPos+pastedLength;
    if ( iEdwinExtension->iSmiley )
        {
        iEdwinExtension->iSmiley->HandleInsertL( selection.LowerPos(), 
            selection.Length() );
        ConvertTextForSmileyL( selection, ETrue );
        } 
    if (iUndoStore)
        iUndoStore->SetNewText(selection);
    if ( NeedToChangeFormattingModeL())
        {
        SetAmountToFormatL();
        DrawContents();
        }
    else
        iTextView->HandleInsertDeleteL(selection,selLength,formatHasChanged);
    iEikonEnv->BusyMsgCancel();
    User::LeaveIfError(err);
    }

void CEikEdwin::DoPasteFromStoreL(const CStreamStore& aStore,const CStreamDictionary& aDict)
    {
    const TInt lengthBeforePaste=iText->DocumentLength();
    const TInt cursorPos=CursorPos();
    
    TBool pasteAsPlainText = iEdwinUserFlags & CEikRichTextEditor::EPasteAsPlainText;
    
    CAknEdwinState* state = static_cast<CAknEdwinState*>( iEdwinFepSupport->State( KNullUid ) );    
    if (state && state->PermittedInputModes() == EAknEditorNumericInputMode )
        {
        TBool isDigit(ETrue);
        CPlainText* txtStore = CPlainText::NewL();
        CleanupStack::PushL(txtStore);
        TInt bufferLength = txtStore->PasteFromStoreL(aStore, aDict, 0);
                
        HBufC* txtStoreBuf = txtStore->Read(0).AllocL();
        CleanupStack::PushL( txtStoreBuf ); 
        TPtr text = txtStoreBuf->Des();
        TInt textLength = text.Length();
        
        HBufC* allowedChars = GetAllowedCharsLC();
        for ( TInt ii = 0; ii < textLength; ii++ )
            {
            TChar chr(text[ii]);
            if ((*allowedChars).Locate(chr) == KErrNotFound && text[ii] != 0x2029)
                {
                isDigit = EFalse;
                break;
                }
            }
        CleanupStack::PopAndDestroy(3);//texStore, txtStoreBuf, allowedChars

        if (!isDigit)
            return;        
        }
    if ( (iEdwinInternalFlags & ERichText) && pasteAsPlainText )
        { 
        static_cast<CRichText*>(iText)->PasteFromStoreL( aStore, aDict, cursorPos, CParagraphStyle::EIgnoreNewStyles ); 
        } 
    else 
        { 
        iText->PasteFromStoreL(aStore,aDict,cursorPos); 
        } 
  
    // Remove tabulators from text if found
    TInt length = iText->DocumentLength();
    
    TPtrC ptr= iText->Read(0);
    TInt position = ptr.Mid(0).LocateReverse('\t');
    while (position != KErrNotFound )
        {
        iText->DeleteL( position, 1 );
        position = ptr.Left(position).LocateReverse('\t');
        }
    
    TInt newLength=iText->DocumentLength();
    TInt pastedLength=newLength-lengthBeforePaste;
    CheckRemovePictures(cursorPos,pastedLength);
    const TInt tmp=iText->DocumentLength();
    if (tmp<newLength)
        iEikonEnv->InfoMsg(R_EIK_TBUF_CANNOT_PASTE_OBJECTS);
    CheckValidityOfChars(cursorPos,pastedLength);
    newLength = iText->DocumentLength();
    pastedLength=newLength-lengthBeforePaste;
    if ( iEdwinInternalFlags&EHasOneLineOnly || iEdwinUserFlags&ENoLineOrParaBreaks )
        {
        ReplaceParaDelimitersL( cursorPos, pastedLength );        
        newLength=iText->DocumentLength();
        pastedLength=newLength-lengthBeforePaste;
        }
    const TInt extraChars=newLength-iTextLimit;
    if (iTextLimit && extraChars>0)
        {
        const TInt pos=cursorPos+pastedLength-extraChars;
        DeleteExtraParasL(pos,extraChars);
        const TInt length=iText->DocumentLength()-iTextLimit;
        if (iEdwinInternalFlags&ERichText && length>0)
            STATIC_CAST(CRichText*,iText)->DeleteFromParagraph(pos,length);
        else
            iText->DeleteL(pos,iText->DocumentLength()-iTextLimit); // won't leave
        CEikonEnv::Beep();
        iEikonEnv->InfoMsg(R_EIK_TBUF_MAX_CHARACTERS_REACHED);
        }
    pastedLength=iText->DocumentLength()-lengthBeforePaste;
    
    // The CParagraphStyle::EIgnoreNewStyles doesn't remove italics,
    // bold or underline. We'll try to hack it here.
    if ( (iEdwinInternalFlags & ERichText) && pasteAsPlainText ) 
        { 
        TCharFormat charFormat;
        TCharFormatMask charFormatMask;

        CRichText* text = static_cast<CRichText*>(iText); 
        text->CGlobalText::GetCharFormat( charFormat, charFormatMask, 0, 0 ); 
        charFormatMask.SetAll();
        text->ApplyCharFormatL( charFormat, charFormatMask, cursorPos, pastedLength );
        
        // To make sure that no parts of the text are left formatted with
        // something else than the globalcharformat.
        text->RemoveSpecificCharFormatL( cursorPos, pastedLength );
        }
    
    HandleTextPastedL(cursorPos,pastedLength);
    }
    
void CEikEdwin::ReplaceParaDelimitersL( TInt aStartPos, TInt aLength )
    {
    TPtrC ptr = iText->Read( aStartPos, aLength );
    TInt delimiter[2] = { 0 };    
    _LIT( KSpace, " " );
    while( delimiter[0] >= 0 || delimiter[1] >= 0 )
        {
        delimiter[0] = ptr.Locate( TChar(CEditableText::EParagraphDelimiter) );
        delimiter[1] = ptr.Locate( TChar(CEditableText::ELineBreak) );
        for( TInt i = 0; i < 2; i++ )
            {            
            if ( delimiter[i] >= 0 )
                {
                iText->DeleteL( aStartPos + delimiter[i], 1 );
                iText->InsertL( aStartPos + delimiter[i], KSpace );
                }
            }
        }
    }

void CEikEdwin::DeleteExtraParasL(TInt aStartPos,TInt aLength)
    {
    TInt pos=aStartPos;
    TInt charsRead=0;
    const TBool pastedAtEnd=(aStartPos+aLength==iText->DocumentLength());
    while (charsRead<aLength)
        {
        TPtrC ptr=iText->Read(pos,Min(aLength-charsRead,10));       
        const TInt paraDelimiter=ptr.Locate(TChar(CEditableText::EParagraphDelimiter));
        const TInt lineDelimiter=ptr.Locate(TChar(CEditableText::ELineBreak));
        if (!(iEdwinInternalFlags&ERichText))
            {
            const TInt delimiter=(paraDelimiter==-1? lineDelimiter : (lineDelimiter==-1? 
                                                paraDelimiter : Min(lineDelimiter,paraDelimiter)));
            if (delimiter!=-1)
                {
                iText->DeleteL(pos+delimiter,aLength-(charsRead+delimiter)); // won't leave
                break;
                }
            }
        else
            {
            if (paraDelimiter!=-1)
                {
                if (pastedAtEnd)
                    STATIC_CAST(CRichText*,iText)->DeleteParagraph(pos+paraDelimiter+1,aLength-(charsRead+paraDelimiter));
                else
                    {
                    TChar delimiter(CEditableText::EParagraphDelimiter);
                    TInt startPos=pos+paraDelimiter+1;
                    TInt length=aLength-(charsRead+paraDelimiter)-1;
                    TInt lastParaDelimiter=KErrNotFound;
                    TInt charPos=LocateChar(delimiter,startPos,length);
                    while (charPos!=KErrNotFound)
                        {
                        lastParaDelimiter=startPos+charPos;
                        startPos+=(charPos+1);
                        length-=(charPos+1);
                        charPos=LocateChar(delimiter,startPos,length);
                        }
                    TInt len=aLength-(startPos-aStartPos);
                    if (len>0)
                        STATIC_CAST(CRichText*,iText)->DeleteFromParagraph(startPos,len);
                    if (lastParaDelimiter!=KErrNotFound)
                        {
                        const TInt start=pos+paraDelimiter+1;
                        length=lastParaDelimiter-start+1;
                        STATIC_CAST(CRichText*,iText)->DeleteParagraph(start,length);
                        }
                    }
                }
            if (lineDelimiter!=-1 && (paraDelimiter==-1 || lineDelimiter<paraDelimiter))
                {
                TInt length=aLength-(charsRead+lineDelimiter);
                if (paraDelimiter!=-1)
                    length=paraDelimiter-lineDelimiter;
                STATIC_CAST(CRichText*,iText)->DeleteFromParagraph(pos+lineDelimiter,length);
                break;
                }
            if (paraDelimiter!=-1)
                {
                if (!pastedAtEnd)
                    iText->DeleteL(pos+paraDelimiter,1);
                break;
                }
            }
        const TInt ptrLen=ptr.Length();
        pos+=ptrLen;
        charsRead+=ptrLen;
        }
    }

TInt CEikEdwin::LocateChar(TChar aChar,TInt aStartPos,TInt aLength)
    {
    TInt pos=aStartPos;
    TInt charsRead=0;
    while (charsRead<aLength)
        {
        TPtrC ptr=iText->Read(pos,Min(aLength-charsRead,10));       
        const TInt charPos=ptr.Locate(aChar);
        if (charPos!=KErrNotFound)
            return (charsRead+charPos);
        const TInt ptrLen=ptr.Length();
        pos+=ptrLen;
        charsRead+=ptrLen;
        }
    return KErrNotFound;
    }

EXPORT_C void CEikEdwin::SetPasteFromIrStore(TBool aPasteFromIrStore)
    {
    if (aPasteFromIrStore)
        iEdwinInternalFlags|=EPasteFromIrStore;
    else
        iEdwinInternalFlags&=(~EPasteFromIrStore);
    }

EXPORT_C void CEikEdwin::HandleTextPastedL(TInt /*aStartPos*/,TInt& /*aLength*/)
    {
    }

EXPORT_C void CEikEdwin::CancelFepTransaction()
    {    
    CCoeFep* fep=iCoeEnv->Fep();
    if ( fep!=NULL )
        {
        fep->CancelTransaction();
        }
    }

EXPORT_C void CEikEdwin::HandleTextChangedL()
    {
    ClearSelectionL(); // ?? maybe too late here!!

    // clear inline edit state info
    if (iEdwinFepSupport)
        STATIC_CAST(CAknEdwinState*, iEdwinFepSupport->State(KNullUid))->SetInlineEditSpan(TCursorSelection(0,0));

    SetAmountToFormatL( ETrue );
    
    if (IsReadyToDraw())
        {
        DrawContents();
        UpdateScrollBarsL();
        }
    }

EXPORT_C void CEikEdwin::RunCharMapDialogL()
    {
    CancelFepTransaction();
    ASSERT(iEikonEnv->CDlgDialogFactory());
    iEikonEnv->CDlgDialogFactory()->RunCharMapDlgLD(this);
    }

EXPORT_C void CEikEdwin::ForceScrollBarUpdateL()
    {
    SetScrollBarsL();   
    }

EXPORT_C void CEikEdwin::UpdateScrollBarsL()
    {
    CheckEdwinExtensionL(); // checks if iEdwinExtension is non-NULL
    
    // Updating via CIdle is needed only if kinetic scrolling is not in use
    if ( !KineticScrollingEnabled() )
        {
        if ( !iEdwinExtension->ScrollBarSetter() && OwnsScrollBars() )
            {
            iEdwinExtension->SetScrollBarSetter( CIdle::NewL(
                    CTextView::EFBackgroundFormattingPriority - 1 ) );
            }
        if ( iEdwinExtension->ScrollBarSetter()
                && !iEdwinExtension->ScrollBarSetter()->IsActive() )
            {
            iEdwinExtension->ScrollBarSetter()->Start( TCallBack(
                    CEikEdwin::IdleL, this ) );
            }
        }
    else
        {
        SetScrollBarsL();
        }
    }

void CEikEdwin::UpdateHorizScrollBarThumb()
    {
    __ASSERT_DEBUG(iTextView,Panic(EEikPanicEdwinNoView));
    if (iSBFrame)
        {
        iSBFrame->MoveHorizThumbTo(iTextView->LeftTextMargin());
        }
    }   

void CEikEdwin::UpdateVertScrollBarThumbL()
    {
    __ASSERT_DEBUG(iTextView,Panic(EEikPanicEdwinNoView));
    __ASSERT_DEBUG(iText,Panic(EEikPanicEdwinNoLayout));
    if (iSBFrame)
        {
        if ( KineticScrollingEnabled() )
            {
            if ( iEdwinExtension && iEdwinExtension->iScrolledByScrollBar )
                {
                CEikScrollBar* sb =
                    iSBFrame-> CEikScrollBarFrame::VerticalScrollBar();
                iEdwinExtension->iScrollbarPosition = sb->ThumbPosition();
                return;
                }
            }
        
        CEikScrollBar* sb = iSBFrame-> CEikScrollBarFrame::VerticalScrollBar();
        TInt prevSBPos = sb->ThumbPosition();

        TEikScrollBarModel vertModel;
        SetVertScrollBarModelByCharactersL(vertModel);
        if ( iSBFrame->TypeOfVScrollBar() == CEikScrollBarFrame::EDoubleSpan )
            {
            TAknDoubleSpanScrollBarModel doubleModel( vertModel );
            sb->SetModel( &doubleModel );
            }
        else
            {
            sb->SetModel( &vertModel );
            }            

        TInt newSBPos = sb->ThumbPosition();
        TBool paintingEnabled = !(iEdwinUserFlags&EDisplayOnly) 
        && !(iEdwinUserFlags&EAvkonDisableCursor) 
        && iTextView->SelectionVisible();
        if (iEdwinFepSupport->iFeedback 
            && iEdwinFepSupport->iMoveThumbFeedbackNeeded 
            && (prevSBPos != newSBPos)
            && !paintingEnabled)
            {
            iEdwinFepSupport->iFeedback->InstantFeedback( this, ETouchFeedbackSensitive );
            }
        }        
    }

EXPORT_C CEikScrollBarFrame* CEikEdwin::CreateScrollBarFrameL()
    {
    return CreateScrollBarFrameL(EFalse);
    }

EXPORT_C CEikScrollBarFrame* CEikEdwin::CreateScrollBarFrameL(TBool aPreAlloc)
    {
    if(!iSBFrame)
        {
        iSBFrame=new(ELeave) CEikScrollBarFrame(this, this, aPreAlloc, ETrue);

        // Check which type of scrollbar is to be shown

        if (AknLayoutUtils::DefaultScrollBarType(iAvkonAppUi) == CEikScrollBarFrame::EDoubleSpan)
            {
            iSBFrame->CreateDoubleSpanScrollBarsL(ETrue, EFalse);
            }
        }
    return iSBFrame;
    }
void CEikEdwin::CreateScrollBarFrameLayout(TEikScrollBarFrameLayout& aLayout) const
    {
    aLayout.iInclusiveMargin=iBorder.Margins();
    const TRect inner=iBorder.InnerRect(Rect());
    const TRect& viewRect=iTextView->ViewRect();
    aLayout.iClientMargin.iLeft=viewRect.iTl.iX-inner.iTl.iX;
    aLayout.iClientMargin.iRight=inner.iBr.iX-viewRect.iBr.iX;
    aLayout.iClientMargin.iTop=viewRect.iTl.iY-inner.iTl.iY;
    aLayout.iClientMargin.iBottom=inner.iBr.iY-viewRect.iBr.iY;
    aLayout.iTilingMode=TEikScrollBarFrameLayout::EInclusiveRectConstant;
    }

EXPORT_C TInt CEikEdwin::IdleL(TAny *anObj)
    {
    CEikEdwin* edwin = static_cast<CEikEdwin*>( anObj );
    if ( edwin && !edwin->KineticScrollingEnabled() )
        {
        edwin->SetScrollBarsL();
        }
    return EFalse;
    }

void CEikEdwin::SetScrollBarsL()
    {
    __ASSERT_DEBUG(iText,Panic(EEikPanicEdwinNoText));
    if (!iSBFrame)
        return;
    CheckEdwinExtensionL(); // checks if iEdwinExtension is non-NULL
    
    if ( KineticScrollingEnabled() )
        {
        SetKineticScrollingScrollBarsL();
        return;
        }
    
    if (iEdwinExtension->ScrollBarSetter() && iEdwinExtension->ScrollBarSetter()->IsActive())
        iEdwinExtension->ScrollBarSetter()->Cancel();
    TEikScrollBarModel hSbarModel(0,0,0);
    TEikScrollBarModel vSbarModel(0,0,0);
    TRect rect = AdjustedViewRect();

    rect=iMargins.OuterRect(rect);
    // Ignore scrollbars presence to set the model, Scrollbar Frame will change it as required
    if (iSBFrame->VScrollBarVisibility()!=CEikScrollBarFrame::EOff)
        {
        SetVertScrollBarModelByCharactersL(vSbarModel);
        // Examine the model to see how the "under one screen" flag is to be set:
        if ( vSbarModel.iThumbSpan >= vSbarModel.iScrollSpan )
            {
            iEdwinInternalFlags|=EUnderOneScreenFormattedText;
            }
        else
            {
            iEdwinInternalFlags&=~EUnderOneScreenFormattedText;
            }
        }
    if (iSBFrame->ScrollBarVisibility(CEikScrollBar::EHorizontal)!=CEikScrollBarFrame::EOff)
        {
        if (iEdwinInternalFlags&EWysiwygOn)
            {
            hSbarModel.iScrollSpan=iZoomFactor->HorizontalTwipsToPixels(LayoutWidth());
            TInt labels=0, cursor=0;
            iTextView->MarginWidths(labels,cursor);
            hSbarModel.iScrollSpan+=labels+cursor+LineCursorWidth();
            }
        else
            hSbarModel.iScrollSpan=LayoutWidth();   
        hSbarModel.iThumbSpan=rect.Width();
        hSbarModel.iThumbPosition=iTextView->LeftTextMargin();
        }
    TRect inclusiveRect=Rect();
    TRect clientRect=rect; // claim client is as large as possible
    TEikScrollBarFrameLayout layout;
    CreateScrollBarFrameLayout(layout);
    if (vSbarModel.iThumbSpan)
        {
        const TInt granularityHeight = AdjustedViewRect().Height()/vSbarModel.iThumbSpan;
        if (granularityHeight)
            layout.iClientAreaGranularity.iHeight=granularityHeight;
        }

    TBool sizeChanged = EFalse;
    if (iSBFrame && iSBFrame->TypeOfVScrollBar() == CEikScrollBarFrame::EDoubleSpan)
        {
        // For EDoubleSpan type scrollbar
        TAknDoubleSpanScrollBarModel hDsSbarModel(hSbarModel);
        TAknDoubleSpanScrollBarModel vDsSbarModel(vSbarModel);
        
        TRect inclusiveRectForDoubleSpan = Rect();
        TRect clientRectForDoubleSpan = Rect(); 
        TEikScrollBarFrameLayout layout;
        layout.iTilingMode = TEikScrollBarFrameLayout::EClientRectConstant;
        TInt focusPostion = 0;
        if (!(iLayout->IsFormattingBand()))
        {
        TInt numLines = iLayout->NumFormattedLines();
        if (numLines > 1)
            numLines--;
        else 
            numLines = 1;
            
        TInt height = iLayout->FormattedHeightInPixels();
        TInt lineNo = 0;
        lineNo = iLayout->FirstLineInBand();
        focusPostion = (height*lineNo)/numLines;
        }
        else
        {
        TEikScrollBarModel vertModel;
        SetVertScrollBarModelByCharactersL(vertModel);
            
        focusPostion = vertModel.iThumbPosition;
        }
        
        vDsSbarModel.SetFocusPosition(focusPostion);
        iSBFrame->TileL(&hDsSbarModel, &vDsSbarModel, clientRectForDoubleSpan, inclusiveRectForDoubleSpan, layout);
        }
    else
        {
        // For EArrowHead type scrollbar
        sizeChanged=iSBFrame->TileL(&hSbarModel, &vSbarModel, clientRect, inclusiveRect, layout);
        }
    
    if (!OwnsScrollBars())
        {
        delete iSBFrame;
        iSBFrame=NULL;
        }
    UpdateVertScrollBarThumbL();
    if (!sizeChanged)
        return;
    // else size of client/inclusive rect has changed
    if (layout.iTilingMode==TEikScrollBarFrameLayout::EClientRectConstant)
        {
        iSize=inclusiveRect.Size();
        DrawNow();
        }
    else
        {
        clientRect=iMargins.InnerRect(clientRect);
        iTextView->SetViewRect(clientRect);
        if (!(iEdwinUserFlags&ENoWrap))
            iLayout->SetWrapWidth(LayoutWidth());
        TViewYPosQualifier yPosQualifier;
        yPosQualifier.SetMakeLineFullyVisible();
        iTextView->HandleGlobalChangeNoRedrawL(yPosQualifier);
        CWindowGc& gc=SystemGc();
        ActivateGc();
        gc.SetBrushColor(iEikonEnv->ControlColor(EColorControlBackground,*this));
        DrawUtils::ClearBetweenRects(gc,iBorder.InnerRect(Rect()),clientRect);
        DeactivateGc();
        if (iEdwinInternalFlags&ELockScrollBarState)
            {
            iTextView->HandleGlobalChangeNoRedrawL(yPosQualifier);
            CEikScrollBarFrame::TScrollBarVisibility vis=iSBFrame->VScrollBarVisibility();
            CEikScrollBarFrame::TScrollBarVisibility vVis=(vis==CEikScrollBarFrame::EAuto? CEikScrollBarFrame::EOn : vis);
            vis=iSBFrame->ScrollBarVisibility(CEikScrollBar::EHorizontal);
            CEikScrollBarFrame::TScrollBarVisibility hVis=(vis==CEikScrollBarFrame::EAuto? CEikScrollBarFrame::EOn : vis);
            iSBFrame->SetScrollBarVisibilityL(hVis,vVis);
            }
        else
            iEdwinInternalFlags|=ELockScrollBarState;
        SetAmountToFormatL(); // will call SetScrollBarsL() again if need be
        if (!iLayout->IsFormattingBand())
            SetScrollBarsL();
        iEdwinInternalFlags&=~ELockScrollBarState;
        if (iEdwinInternalFlags&EWysiwygOn && iSBFrame->ScrollBarVisibility(CEikScrollBar::EHorizontal)==CEikScrollBarFrame::EAuto)
            {
            CEikScrollBar* hSBar=iSBFrame->GetScrollBarHandle(CEikScrollBar::EHorizontal);
            if (!hSBar || !hSBar->IsVisible())
                iTextView->SetLeftTextMargin(0);
            }
        iTextView->DrawL(clientRect);
        }
    }

void CEikEdwin::SetKineticScrollingScrollBarsL()
    {
    TEikScrollBarModel hSbarModel( 0, 0, 0 );
    TEikScrollBarModel vSbarModel( 0, 0, 0 );
    TRect rect( AdjustedViewRect() );

    rect = iMargins.OuterRect( rect );
    // Ignore scrollbars presence to set the model,
    // Scrollbar Frame will change it as required
    if ( iSBFrame->VScrollBarVisibility() != CEikScrollBarFrame::EOff )
        {
        if ( iLayout->IsFormattingBand() )
            {
            SetVertScrollBarModelByCharactersL( vSbarModel );
            // Examine the model to see how the "under one screen"
            // flag is to be set:
            if ( vSbarModel.iThumbSpan >= vSbarModel.iScrollSpan )
                {
                iEdwinInternalFlags |= EUnderOneScreenFormattedText;
                }
            else
                {
                iEdwinInternalFlags &= ~EUnderOneScreenFormattedText;
                }
            }
        else
            {
            vSbarModel.iScrollSpan = iLayout->FormattedHeightInPixels();
            vSbarModel.iThumbSpan = AdjustedViewRect().Height();
            if ( vSbarModel.iScrollSpan < vSbarModel.iThumbSpan
                && vSbarModel.iThumbPosition )
                {
                vSbarModel.iScrollSpan = vSbarModel.iThumbSpan
                        + vSbarModel.iThumbPosition;
                iEdwinInternalFlags |= EUnderOneScreenFormattedText;
                }
            else
                {
                iEdwinInternalFlags &= ~EUnderOneScreenFormattedText;
                }
            }
        }
    
    if ( iSBFrame->ScrollBarVisibility( CEikScrollBar::EHorizontal )
            != CEikScrollBarFrame::EOff )
        {
        if ( iEdwinInternalFlags & EWysiwygOn )
            {
            hSbarModel.iScrollSpan = iZoomFactor->HorizontalTwipsToPixels(
                    LayoutWidth() );
            TInt labels = 0, cursor = 0;
            iTextView->MarginWidths( labels, cursor );
            hSbarModel.iScrollSpan += labels + cursor + LineCursorWidth();
            }
        else
            {
            hSbarModel.iScrollSpan = LayoutWidth();
            }
        hSbarModel.iThumbSpan = rect.Width();
        hSbarModel.iThumbPosition = iTextView->LeftTextMargin();
        }
    
    TRect inclusiveRect( Rect() );
    TEikScrollBarFrameLayout layout;
    CreateScrollBarFrameLayout( layout );
    
    if ( vSbarModel.iThumbSpan )
        {
        TInt granularityHeight = AdjustedViewRect().Height()
            / vSbarModel.iThumbSpan;
        if ( granularityHeight )
            layout.iClientAreaGranularity.iHeight = granularityHeight;
        }

    // For EDoubleSpan type scrollbar
    TAknDoubleSpanScrollBarModel hDsSbarModel( hSbarModel );
    TAknDoubleSpanScrollBarModel vDsSbarModel( vSbarModel );

    TRect inclusiveRectForDoubleSpan( Rect() );
    TRect clientRectForDoubleSpan ( Rect() );

    TEikScrollBarFrameLayout layout2;
    layout2.iTilingMode = TEikScrollBarFrameLayout::EClientRectConstant;
        
    TInt focusPosition = 0;
    if ( !( iLayout->IsFormattingBand() ) )
        {
        TInt numLines = iLayout->NumFormattedLines();
        if ( numLines > 1 )
            {
            numLines--;
            }
        else
            {
            numLines = 1;
            }

        TInt height = iLayout->FormattedHeightInPixels();
        TInt lineNo = 0;
        lineNo = iLayout->FirstLineInBand();
        focusPosition = ( height * lineNo ) / numLines;
        }
    else
        {
        TEikScrollBarModel vertModel;
        SetVertScrollBarModelByCharactersL( vertModel );

        focusPosition = vertModel.iThumbPosition;
        }

    vDsSbarModel.SetFocusPosition( focusPosition );
    iSBFrame->TileL( &hDsSbarModel, &vDsSbarModel, clientRectForDoubleSpan,
            inclusiveRectForDoubleSpan, layout2 );

    if ( !OwnsScrollBars() )
        {
        delete iSBFrame;
        iSBFrame = NULL;
        }
    UpdateVertScrollBarThumbL();     
    }

void CEikEdwin::SetVertScrollBarModelByCharactersL(TEikScrollBarModel& aVertModel) const
    {
    __ASSERT_DEBUG(iText,Panic(EEikPanicEdwinNoText));
    __ASSERT_DEBUG(iLayout,Panic(EEikPanicEdwinNoLayout));

    if ( KineticScrollingEnabled() )
        {
        SetKineticScrollingScrollBarModel( aVertModel );
        return;
        }
    
    TRect viewRect( AdjustedViewRect() );
    const TInt formattedLines = Max(1, iLayout->NumFormattedLines());
    const TInt formattedHeight = iLayout->FormattedHeightInPixels();    
    const TInt viewRectHeight = viewRect.Height();
    const TInt totalChars = iText->DocumentLength();    
    const TInt formattedLength = Min( totalChars, iLayout->FormattedLength() );
    const TInt topLeftDocPos=iLayout->FirstDocPosFullyInBand();
    const TInt avgCharsPerLine = iAvgCharsPerLine ? iAvgCharsPerLine : 
        Max( 1, formattedLength / formattedLines );    
    const TInt avgLineHeight = formattedHeight/formattedLines;
    TInt posRange( 0 );
    TInt topPos( iTextView->XyPosToDocPosL( viewRect.iTl ) );
    TInt bottomPos( iTextView->XyPosToDocPosL( viewRect.iBr ) );    
    if( AknLayoutUtils::PenEnabled() )
        {
        if ( !iLayout->IsFormattingBand() )
            {                        
            aVertModel.iThumbSpan = viewRectHeight;
            aVertModel.iScrollSpan = formattedHeight;            
            aVertModel.iThumbPosition = iEdwinExtension->iThumbPos;   
            if ( aVertModel.iThumbPosition == KErrNotFound )
                {
                if ( bottomPos == totalChars )
                    {
                    aVertModel.iThumbPosition = aVertModel.iScrollSpan - 
                        aVertModel.iThumbSpan;
                    TPoint bottomPoint(0,0);
                    iTextView->DocPosToXyPosL(bottomPos,bottomPoint);
                    if ( topPos == 0 && bottomPoint.iY == viewRect.iBr.iY )
                        {
                        aVertModel.iThumbPosition = 0;
                        TInt gapFhAndVh = formattedHeight-viewRectHeight;
                        if (gapFhAndVh < avgLineHeight/2)
                            {      
                            aVertModel.iThumbSpan = viewRectHeight;
                            aVertModel.iScrollSpan = viewRectHeight;
                            }
                        }
                    }
                else
                    {
                    TInt topLine( iLayout->GetLineNumber( topPos ) );
                    aVertModel.iThumbPosition = topLine * formattedHeight / 
                        formattedLines;
                    }                
                }
            }
        else
            {
            aVertModel.iThumbSpan = bottomPos - topPos;
            aVertModel.iScrollSpan = totalChars;        
            aVertModel.iThumbPosition = topPos;
            }
        return;
        }
    else
        {
        // - units for all elements of the model are numbers of characters, not pixels.
        // - character positions refer to the VISIBLE band (not the total formatted text),
        // - scrollspan is the total no. of characters, not pixels, to avoid "bounce" on the 
        //   fractional position (this is because thumb info is sent separately from the whole model at times)
        // - take advantage of form APIs as well as we can 
        aVertModel.iScrollSpan = Max(1,totalChars);
        TInt docPos;
        posRange = iLayout->PosRangeInBand( docPos ); // gives number of characters in visible range 
        }
    
    if (iSBFrame && iSBFrame->TypeOfVScrollBar() == CEikScrollBarFrame::EDoubleSpan)
        {
        // For EDoubleSpan type scrollbar
        // Normally, the thumbspan is just the size of the range of visible characters, and the top of the thumb is
        // index of first character in the view.
        aVertModel.iThumbSpan = Max(1,posRange);
        aVertModel.iThumbPosition = topLeftDocPos; // Simply the top left character   

        // A situation can arise when cursor is near the end of text, and the user is deleting.  This can leave empty lines.
        // Thumbspan must try to measure the whole view - even if there are no characters in some of it.
        // (Note that this problem does not arise when there is very little text in the document and the screen is only half
        // full. In that case thumb and scroll span are equal.)
        // The approach is to invent ficticious characters. Estimate how many characters there would be if the text were as dense
        // as the average formatted line.
        // It is biased against by a factor, so that it does not trigger unless we are in the above situation.
#define KSparseCharactersNumerator 8
#define KSparseCharactersDenominator 10
        // Note deliberate ordering of multiplies and divides to avoid chance of overflow
        TInt estimatedCharsToFillVisibleArea = 
        ( KSparseCharactersNumerator * viewRectHeight / KSparseCharactersDenominator * formattedLength ) 
        / Max(1,formattedHeight);
        TInt excessChars = estimatedCharsToFillVisibleArea - posRange;
        if ( excessChars > 0 && (posRange < totalChars/2 ) ) // Additional cond. that most of text is not showing
            {
            aVertModel.iThumbSpan += excessChars;
            // Also have to increase the span, as these ficticious characters are (sort of) included in the whole document.
            aVertModel.iScrollSpan += excessChars;           
            }            
        }
    else
        {        
        // For scroll-indicator functionality (EArrowHead)
        // - quantize thumb position according to a "line model" to avoid changing values each time the cursor 
        // moves 1 character.         
        // Divide the visible band into a number of lines to get a "line" quantized value.  
        // (This leads to less drawing of the arrowheads, or at least stops that notification earlier)
        // Number of lines is calculated with approximation that the last line is half filled.
        // This is chosen because the correct behaviour is most important when at the (top line is usually filled) 
        // and at the bottom (Sometimes full, sometimes just one character).
        const TInt nLines = ( posRange - avgCharsPerLine/2 ) / avgCharsPerLine + 1;        
        const TInt currentPos = CursorPos();
        const TInt line = Max(0,currentPos - topLeftDocPos) / avgCharsPerLine; // zero-based line number; bigger because of rounding down above. 
        if ( line >= (nLines - 1) ) // last line or too high because of rounding?
            {
            aVertModel.iThumbPosition = topLeftDocPos + posRange - 1; //Clamp to max value
            }
        else
            {
            aVertModel.iThumbPosition = topLeftDocPos + line * avgCharsPerLine;
            }    
        // Although arrowhead implementations probably ignore the thumb span, just ensure its bottom end does not go below
        // the scrollspan.    
        aVertModel.iThumbSpan = Min( aVertModel.iThumbSpan, aVertModel.iScrollSpan - aVertModel.iThumbPosition );
        }
    }

void CEikEdwin::SetKineticScrollingScrollBarModel(
    TEikScrollBarModel& aVertModel ) const
    {
    // This function is related to Rate scrolling implementation.
    //
    // When kinetic scrolling is not enabled, original way
    // (named here as Position Scrolling) is used. When kinetic
    // scrolling is enabled, new way (named here as Rate Scrolling) is used.
    //
    // In Position Scrolling there is always a one-to-one mapping relationship
    // of position between text view and scrollbar. When you scroll one of
    // them, the other one will always be moved to follow the new position of
    // its friend.
    //
    // But there is one issue, the height of the whole document is not accurate
    // but a approximate value according to current band
    // (Band: current formatted text area, including current shown view and
    // some text leading and following it). So the mapping is somehow
    // irregular, that when you scroll the view regularly, the scrollbar will
    // change its position not regularly.
    //
    // When you move text view from Pos1 to Pos2, the scrollbar will be moved
    // from Pos3 to Pos4, and here the Pos4 is only related to Pos2.
    //
    // 
    // Rate Scrolling is designed to make regular scrolling for both text view
    // and scrollbar. The “regular?here is not absolutely regular but more
    // regular than before, or regular to end users. It is also impacted by
    // the Band area changing, but the impact is much smaller than before.
    //
    // When you move text view from Pos1 to Pos2, the scrollbar will be moved
    // from Pos3 to Pos4. Here the Pos4 is related to all Pos1, Pos2 and Pos3.
    // The relationship between them is the Rate.
    //
    // The Rate means how many percentage it has moved to the end boundary. 
    // If you move downwards, expected whole text view height is H, remaining
    // way to the end boundary is (H - Pos1), the Percentage you have moved is
    // offset/(H - Pos1) = (Pos2 - Pos1)/(H - Pos1)
    //
    // So the scrollbar should also move for the same percentage of the
    // remaining way. 
    //
    // This moving behavior is more regular than before, and the visible result
    // proves it.
    //
    // With this way, It can be proved that when text view is scrolled to the
    // end, the scrollbar will also be in the end, and vice versa. 
    //
    // In Rate scrolling way, scrollbar will have different position values
    // if you scroll text view same to X but from different starting position.
    
    TInt formattedLines = Max( 1, iLayout->NumFormattedLines() );
    TInt formattedHeight = iLayout->FormattedHeightInPixels();
    TInt viewRectHeight = AdjustedViewRect().Height();
    TInt totalChars = iText->DocumentLength();
    TInt formattedLength = iLayout->FormattedLength();
    TInt topLeftDocPos = iLayout->FirstDocPosFullyInBand();
    TInt avgCharsPerLine = Max( 1, formattedLength / formattedLines );

    TInt formattedHeightAboveView = iLayout->PixelsAboveBand();
    TInt formattedHeightBelowView = formattedHeight - viewRectHeight
        - formattedHeightAboveView;

    TInt anchorThumbPos = 0;
    TInt avgLineHeight = 0;

    // Approximate top visible line from bottom if we are over half of text,
    // otherwise from top of text. 
    TInt approxTopVisibleLine = 0;

    // Variables only used in this block
    TInt firstFormattedPos = iLayout->FirstFormattedPos();
    TInt lastFormattedPos = firstFormattedPos + formattedLength;
        
    avgLineHeight = formattedHeight / formattedLines;
        
    TInt lineNo = iLayout->GetLineNumber( CursorPos() );
    TInt heightBeforeFormat = ( avgLineHeight * firstFormattedPos )
        / avgCharsPerLine;
    TInt heightAfterFormat = ( avgLineHeight * ( totalChars
        - lastFormattedPos ) ) / avgCharsPerLine;

    const TAknDoubleSpanScrollBarModel* doubleModel =
        static_cast< const TAknDoubleSpanScrollBarModel* >
            ( iSBFrame->CEikScrollBarFrame::VerticalScrollBar()->Model() );

    if ( !iEdwinExtension->iUseRateScroll )
        {
        aVertModel.iScrollSpan = heightBeforeFormat + formattedHeight
            + heightAfterFormat;
        aVertModel.iThumbSpan = viewRectHeight;
        }

    // Rate scrolling

    if ( iEdwinExtension->iUseRateScroll )
        {
        TInt heightAboveView = formattedHeightAboveView + heightBeforeFormat;
        TInt heightBelowView = formattedHeightBelowView + heightAfterFormat;

        TInt curScrollSpan = aVertModel.iScrollSpan
            = doubleModel->ScrollSpan();
        TInt curThumbSpan = aVertModel.iThumbSpan
            = doubleModel->WindowSize();
            
        TInt thumbSpaceAbove = aVertModel.iThumbPosition
            = iSBFrame-> CEikScrollBarFrame::VerticalScrollBar()->ThumbPosition();
                
        TInt thumbSpaceBelow = curScrollSpan - curThumbSpan - thumbSpaceAbove;
            
        // We have moved above
        if ( iEdwinExtension->iScrolledDelta > 0 )//Move above
            {
            TInt prePosition = heightAboveView + iEdwinExtension->iScrolledDelta;
            if ( prePosition == 0 )
                {
                return;
                }
            anchorThumbPos = thumbSpaceAbove
                - iEdwinExtension->iScrolledDelta * thumbSpaceAbove
                / prePosition;
            }
        // We have moved below
        else if ( iEdwinExtension->iScrolledDelta < 0 )//Move below
            {
            TInt postPosition = heightBelowView - iEdwinExtension->iScrolledDelta;
            if ( postPosition == 0 )
                {
                return;
                }
            anchorThumbPos = thumbSpaceAbove
                - iEdwinExtension->iScrolledDelta * thumbSpaceBelow
                / postPosition;
            }
        else
            {
            return;
            }
        } 
    else // Original way, no rate scrolling
        {
         approxTopVisibleLine = topLeftDocPos / avgCharsPerLine;
        if ( approxTopVisibleLine == 0 && topLeftDocPos > 0 )
            {
            approxTopVisibleLine = 1;
            }
        }
    
    if ( iEdwinExtension->iUseRateScroll )
        {
        aVertModel.iThumbPosition = anchorThumbPos;
        }
    else
        {
        aVertModel.iThumbPosition = approxTopVisibleLine * avgLineHeight;
        }
    iEdwinExtension->iScrollbarPosition = aVertModel.iThumbPosition; 
    }

// ---------------------------------------------------------------------------
// CEikEdwin::HandleScrollEventWithPhysicsL
// ---------------------------------------------------------------------------
// 
void CEikEdwin::HandleScrollEventWithPhysics( CEikScrollBar* aScrollBar )
    {
    // Scroll view based on scrollbar thumb position  
    
    const TAknDoubleSpanScrollBarModel * doubleModel =
        static_cast< const TAknDoubleSpanScrollBarModel* >
            ( aScrollBar->Model() );

    TInt curScrollSpan = doubleModel->ScrollSpan();
    TInt curThumbSpan = doubleModel->WindowSize();
    TInt thumbSpaceAbove = aScrollBar->ThumbPosition();
    TInt thumbSpaceBelow = curScrollSpan - curThumbSpan - thumbSpaceAbove;

    TInt moveOffset = thumbSpaceAbove - iEdwinExtension->iScrollbarPosition;

    const TInt formattedLines = Max( 1, iLayout->NumFormattedLines() );
    const TInt formattedHeight = iLayout->FormattedHeightInPixels();
    const TInt viewRectHeight = AdjustedViewRect().Height();
    const TInt totalChars = iText->DocumentLength();
    const TInt formattedLength = iLayout->FormattedLength();
    const TInt avgCharsPerLine = Max( 1, formattedLength / formattedLines );

    const TInt formattedHeightAboveView = iLayout->PixelsAboveBand();
    const TInt formattedHeightBelowView = formattedHeight - viewRectHeight
            - formattedHeightAboveView;

    const TInt firstFormattedPos = iLayout->FirstFormattedPos();
    const TInt lastFormattedPos = firstFormattedPos + formattedLength;
    const TInt heightBeforeFormat = ( formattedHeight * firstFormattedPos )
            / avgCharsPerLine / formattedLines;
    const TInt heightAfterFormat = ( formattedHeight * ( totalChars
            - lastFormattedPos ) ) / avgCharsPerLine / formattedLines;

    const TInt heightAboveView = formattedHeightAboveView + heightBeforeFormat;
    const TInt heightBelowView = formattedHeightBelowView + heightAfterFormat;

    TInt textMovePixels = 0;
    if ( moveOffset > 0 )
        {
        textMovePixels = heightBelowView * moveOffset / ( 0 - thumbSpaceBelow
                - moveOffset );   
        }
    else if ( moveOffset < 0 )
        {
        textMovePixels = heightAboveView * moveOffset / ( moveOffset
                - thumbSpaceAbove );
        }
    else
        {
        return;
        }
    iEdwinExtension->iScrollbarPosition = thumbSpaceAbove;

    // If scrollbar thumb is moved to the beginning or end of scrollbar,
    // ensure that also editor content is moved also exactly to the beginning
    // or end. This is needed because otherwise in some situations editor
    // content is not moved enough. We can't move too much because moving is
    // limited to begin and end of actual editor content.
    if ( thumbSpaceAbove <= 0 )
        {
        textMovePixels += KAdditionalPixels;
        }
    else if ( thumbSpaceAbove >= curScrollSpan - curThumbSpan )
        {
        textMovePixels -= KAdditionalPixels;
        }
    
    iEdwinExtension->iScrolledByScrollBar = ETrue;
    
    // Actual scrolling is done by calling MoveScrollIndex
    iEdwinExtension->iPhysicsHandler->MoveScrollIndex( -textMovePixels );
    
    iEdwinExtension->iScrolledByScrollBar = EFalse;
    }

EXPORT_C void CEikEdwin::HandleScrollEventL(CEikScrollBar* aScrollBar,TEikScrollEvent aEventType)
    {
    __ASSERT_DEBUG(iText,Panic(EEikPanicEdwinNoText));
    __ASSERT_DEBUG(iLayout,Panic(EEikPanicEdwinNoLayout));
    
    TInt thumbPosition=aScrollBar->ThumbPosition();
    TInt thumbSpan = 0;
    if ( aScrollBar->Model()->ScrollBarModelType() == 
        TEikScrollBarModel::EAknDoubleSpanScrollBarModel)
        {
        const TAknDoubleSpanScrollBarModel* doubleModel = 
            static_cast<const TAknDoubleSpanScrollBarModel*>( aScrollBar->Model() );
        thumbSpan = doubleModel->ScrollSpan();
        thumbSpan -= doubleModel->WindowSize();
        }
    else
        {
        thumbSpan = aScrollBar->Model()->MaxThumbPos();
        }
    switch (aEventType&KEikScrollEventBarMask)
        { 
    case KEikScrollEventFromHBar:
        switch (aEventType)
            {
        case EEikScrollLeft:
        case EEikScrollRight:
            MoveDisplayL((aEventType==EEikScrollLeft)? TCursorPosition::EFLeft: TCursorPosition::EFRight);
            break;
        case EEikScrollPageLeft:
        case EEikScrollPageRight:
            {
            TInt singleScrollJump=iTextView->HorizontalScrollJump();
            if (aEventType==EEikScrollPageLeft)
                singleScrollJump=-singleScrollJump;
            const TInt leftTextViewMargin=iTextView->LeftTextMargin();
            const TInt layoutWidth = LayoutWidth();
            const TInt textViewWidth = iTextView->ViewRect().Width();

            TInt leftMargin = (5*singleScrollJump) + leftTextViewMargin; // ?? scroll how far!!
            if (leftMargin < 0)
                leftMargin=0;
            else if (leftMargin>layoutWidth)
                leftMargin=leftTextViewMargin + layoutWidth - textViewWidth;
            iTextView->SetLeftTextMargin(leftMargin); // !! this doesn't actually scroll anything so...
            TRect rect=iBorder.InnerRect(Rect());
            iMargins.InnerRect(rect);
            iTextView->DrawL(rect);
            UpdateScrollBarsL();
            UpdateHorizScrollBarThumb();
            }
            break;
        case EEikScrollThumbDragHoriz:
//      case EEikScrollThumbReleaseHoriz:
            {
            iTextView->SetLeftTextMargin(thumbPosition);
            TRect rect=iBorder.InnerRect(Rect());
            iMargins.InnerRect(rect);
            iTextView->DrawL(rect);
            }
            break;
        default:
            break;
            }
        break;
    case KEikScrollEventFromVBar:
        switch (aEventType)
            {
        default:
            break;
        case EEikScrollTop:
        case EEikScrollBottom:
            {
            TInt docPos=(aEventType==EEikScrollTop)? 0 : iText->DocumentLength();
            TInt yPos=iPosition.iY+iBorder.Margins().iLeft;
            TViewYPosQualifier yPosQ;
            yPosQ.SetMakeLineFullyVisible();
            yPosQ.SetFillScreen();
            iTextView->SetViewL(docPos, yPos, yPosQ);
            UpdateVertScrollBarThumbL();
            UpdateHorizScrollBarThumb();// can also change horizontally
            }
            break;
        case EEikScrollUp:
        case EEikScrollDown:            
        case EEikScrollPageUp:
        case EEikScrollPageDown:            
        case EEikScrollThumbDragVert:
            {
            if ( KineticScrollingEnabled() )
                {
                HandleScrollEventWithPhysics( aScrollBar );
                break;
                }
            
            TRect viewRect( AdjustedViewRect() );            
            TInt docPos( 0 );
            TInt yPos = viewRect.iTl.iY;
            TInt totalChars( iText->DocumentLength() );
            if ( !iLayout->IsFormattingBand() )
                {                
                TInt topLine( thumbPosition * iLayout->NumFormattedLines() /
                    iLayout->FormattedHeightInPixels() + 1 );                
                docPos = iLayout->FirstCharOnLine( topLine );                
                }
            else
                {
                TInt topPos( iTextView->XyPosToDocPosL( viewRect.iTl ) );
                TInt bottomPos( iTextView->XyPosToDocPosL( viewRect.iBr ) );
                TInt visibleRange( bottomPos - topPos );
                
                if ( thumbPosition != thumbSpan )                
                    {   
                    TInt scrollRange( totalChars - visibleRange );
                    docPos = ( TInt )( ( TInt64 )( thumbPosition ) * scrollRange
                        / thumbSpan );
                    if ( iEdwinExtension->iThumbPos > thumbPosition && 
                        docPos >= topPos && topPos != 0)
                        {
                        docPos = (TInt)( topPos - ( TInt64 )( thumbPosition - 
                            iEdwinExtension->iThumbPos ) * scrollRange / thumbSpan );
                        docPos = docPos < 0 ? 0 : docPos;
                        }
                    else if ( iEdwinExtension->iThumbPos < thumbPosition &&
                        docPos <= topPos && bottomPos != totalChars )
                        {
                        docPos = (TInt)( topPos + ( TInt64 )( thumbPosition - 
                            iEdwinExtension->iThumbPos ) * scrollRange / thumbSpan );
                        docPos = docPos > totalChars ? totalChars : docPos; 
                        }
                    }                
                }
            if ( thumbPosition == thumbSpan )
                {
                docPos = totalChars;
                yPos = viewRect.iBr.iY;
                }
            iEdwinExtension->iThumbPos = thumbPosition;
            TViewYPosQualifier yPosQ;
            yPosQ.SetMakeLineFullyVisible();            
            iTextView->SetViewL( docPos, yPos, yPosQ,
                CTextView::EFViewDontDiscardFormat,
                CTextView::EFNoHorizontalScroll);
            UpdateVertScrollBarThumbL();
            }
            break;        
            }
        if (aEventType!=EEikScrollThumbDragVert && iEdwinInternalFlags&EUnderOneScreenFormattedText)
            UpdateScrollBarsL();
        break;
        }
    ReportEdwinEventL( MEikEdwinObserver::EEventScroll );
    }

EXPORT_C TInt CEikEdwin::LayoutWidth() const
    {
    if (iLayoutWidth)
        return iLayoutWidth;
    TMargins margins=iBorder.Margins();
    TInt labels=0, cursor=0;
    if (iTextView)
        iTextView->MarginWidths(labels,cursor);

    TInt width;
   
    if ( iTextView )
        {
        width = iTextView->ViewRect().Width();
        }
    else
        {
        width = iSize.iWidth - ( margins.iLeft + margins.iRight );
        }
    
    return width - ( labels + cursor + CursorWidth() + iRightWrapGutter );
    }

void CEikEdwin::DoReplaceAllL(SEdwinFindModel* aModel,TBool& aTextFound,TBool& aReplaced)
    {
    aReplaced=EFalse;
    aTextFound=EFalse;
    TInt flags=aModel->iFlags;
    //text is found when called from replace dialog.
    if (SelectionLength())
        ClearSelectionL();
    TInt startPos=CursorPos();
    if (flags&EFindDirectionUp)
        startPos+=aModel->iText.Length();
    else
        startPos-=aModel->iText.Length();
    TInt count=-1;
FindAgain:
    count=FindTextL(&aModel->iText,startPos,aModel->iFlags);        
    if (count!=KErrNotFound)
        {
        aReplaced=ETrue;
        aTextFound=ETrue;
        iText->InsertL(count,aModel->iReplaceText);
        iText->DeleteL(count+aModel->iReplaceText.Length(),aModel->iText.Length());
        if (!(flags&EFindDirectionUp))
            startPos=count+aModel->iReplaceText.Length();
        else
            startPos=count;
        goto FindAgain;
        }
    }

EXPORT_C void CEikEdwin::ReplaceAllL(SEdwinFindModel* aModel)
    {
    __ASSERT_DEBUG(iText,Panic(EEikPanicEdwinNoText));
    __ASSERT_DEBUG(iTextView,Panic(EEikPanicEdwinNoView));
    CancelFepTransaction();
    TBool textFound=EFalse;
    TBool replaced=EFalse;
    const TBool undoEnabled=SupportsUndo();
    if (undoEnabled)
        SetAllowUndo(EFalse);
    TRAPD(ret,DoReplaceAllL(aModel,textFound,replaced));
    if (undoEnabled)
        SetAllowUndo(ETrue);
    if (ret==KErrNone)
        {
        if (!textFound)
            DisplayFindTextNotFound(aModel->iText);
        if (replaced)
            {
            ReportEdwinEventL( MEikEdwinObserver::EEventTextUpdate );
            DoReportEventL( MCoeControlObserver::EEventStateChanged );
            NotifyNewFormatL(); //do global format
            }
        if (SelectionLength())
            ClearSelectionL();  
        }
    else
        {
        iEikonEnv->BusyMsgCancel();
        ReportEdwinEventL( MEikEdwinObserver::EEventTextUpdate );
        DoReportEventL( MCoeControlObserver::EEventStateChanged );
        NotifyNewFormatL();//this will fail too if oom.
        User::Leave(ret);
        }
    }    
      
EXPORT_C void CEikEdwin::ReplaceL(SEdwinFindModel* aModel)
    {
    __ASSERT_DEBUG(iText,Panic(EEikPanicEdwinNoText));
    __ASSERT_DEBUG(iTextView,Panic(EEikPanicEdwinNoView));
    
    CancelFepTransaction();
    const TInt oldLength=iText->DocumentLength();
    TBool formatHasChanged;
    TCursorSelection selection=iTextView->Selection();
    const TBool undoEnabled=SupportsUndo();
    if (undoEnabled)
        SetAllowUndo(EFalse);
    TInt startPos=DeleteHighlightL(formatHasChanged,EFalse,EFalse);
    if (undoEnabled)
        SetAllowUndo(ETrue);
    TRAPD(err,iText->InsertL(startPos,aModel->iReplaceText));
    if (aModel->iFlags&EFindDirectionUp)
        {
        selection.iCursorPos=selection.LowerPos();
        selection.iAnchorPos=selection.iCursorPos+aModel->iReplaceText.Length();
        }
    else
        {
        selection.iAnchorPos=selection.LowerPos();
        selection.iCursorPos=selection.iAnchorPos+aModel->iReplaceText.Length();
        }
    const TCursorSelection pending(selection.iCursorPos,selection.iCursorPos);
    iTextView->SetPendingSelection(pending);
    iTextView->HandleInsertDeleteL(selection,aModel->iText.Length(),formatHasChanged);
    if ( NeedToChangeFormattingModeL())
        SetAmountToFormatL();
    ReportEdwinEventL( MEikEdwinObserver::EEventTextUpdate );
    DoReportEventL( MCoeControlObserver::EEventStateChanged );
    User::LeaveIfError(err);
    }    

EXPORT_C TBool CEikEdwin::FindL(const TDesC* aFindText,TInt aFindFlags)
    { 
    TBuf<EEikEdwinFindStringMaxLen>* findText=new(ELeave) TBuf<EEikEdwinFindStringMaxLen>;
    CleanupStack::PushL(findText);
    if (!aFindText)
        {
        GetFindText(findText);
        if (!findText->Length())
            {
            CleanupStack::PopAndDestroy();
            if (SelectionLength())
                ClearSelectionL();
            return EFalse;
            }
        }
    else
        *findText=*aFindText;
    TBool noBusyMessage=(aFindFlags&ENoBusyMessage);
    if(!noBusyMessage)
        iEikonEnv->BusyMsgL(R_EIK_TBUF_SEARCHING,500000); // 0.5s delay 
    TInt startPos=CursorPos();
    TBool isUp=(aFindFlags&EFindDirectionUp);
    TBool findAgain=(aFindFlags&EFindAgain);
    if ((isUp==EFalse) != (findAgain==EFalse))
        startPos=Selection().HigherPos();
    else
        startPos=Selection().LowerPos();
    TInt pos=FindTextL(findText,startPos,aFindFlags);
    if (pos==KErrNotFound) //ie not found
        {
        CleanupStack::PopAndDestroy(); // findText
        if (SelectionLength())
            ClearSelectionL();
        if(!noBusyMessage)
            iEikonEnv->BusyMsgCancel();
        return EFalse;
        }
    if (aFindFlags&EFindDirectionUp)
        SetSelectionL(pos,pos+findText->Length());
    else
        SetSelectionL(pos+findText->Length(),pos);
    CleanupStack::PopAndDestroy(); // findText
    if(!noBusyMessage)
        iEikonEnv->BusyMsgCancel();
    return ETrue;
    }

EXPORT_C TInt CEikEdwin::FindTextL(const TDesC* aFindText,TInt aPos,TInt aFindFlags)
    {
    __ASSERT_DEBUG(iText,Panic(EEikPanicEdwinNoText));
    const TInt docLength=TextLength();
    if (docLength<aPos)
        return KErrNotFound;
    TInt findParams=aFindFlags;
    TBuf<EEikEdwinFindStringMaxLen>* findText=new(ELeave) TBuf<EEikEdwinFindStringMaxLen>;
    CleanupStack::PushL(findText);
    if (aFindText)
        *findText=*aFindText;
    else
        {
        GetFindText(findText);
        findParams&=(~EFindCaseSensitive);
        }
    const TInt findLen=findText->Length();
    if (!findLen || docLength<findLen)
        {
        CleanupStack::PopAndDestroy(); // findText
        return KErrNotFound;
        }
    if (!(findParams&EFindCaseSensitive))
        findText->LowerCase();
    TBuf<EEikEdwinFindStringMaxLen>* docText=new(ELeave) TBuf<EEikEdwinFindStringMaxLen>;
    CleanupStack::PushL(docText);
    TInt count=aPos;
    if (findParams&EFindDirectionUp)
        {
        if (aPos<findText->Length())
            {
            CleanupStack::PopAndDestroy(2); // findText, docText
            return KErrNotFound; 
            }
        count=aPos-findLen;
        }
    FOREVER
        {
        if (count<0 || (count>(docLength-findLen) && !(findParams&EFindDirectionUp)))
            {
            CleanupStack::PopAndDestroy(2); // findText, docText
            return KErrNotFound; 
            }
        *docText=iText->Read(count,findLen);
        TInt docLen=docText->Length();
        while (docLen<findLen) // tried to read across a segment boundary
            {
            docText->Append(iText->Read(count+docLen,findLen-docLen));
            docLen=docText->Length();
            }
        if (!(findParams&EFindCaseSensitive))
            docText->LowerCase();
        if (*findText==*docText)
            {
            if (findParams&EFindWholeWord)
                {
                if ((count==0 || !TCharF(*((iText->Read(count-1,1)).Ptr())).IsAlphaDigit()) &&
                (count+findLen==docLength || !TCharF(*((iText->Read(count+findLen,1)).Ptr())).IsAlphaDigit()))
                    {
                    break;
                    }
                }
            else
                {
                break;
                }
            }
        if (findParams&EFindDirectionUp)
            count--;
        else
            count++;
        }
    CleanupStack::PopAndDestroy(2); // findText, docText
    return count;
    }

EXPORT_C void CEikEdwin::DisplayFindTextNotFound(TDes& aFindText)
    {
    TBuf<80> tmp;
    TRAPD( err, iCoeEnv->ReadResourceL( tmp,R_EIK_TBUF_CANNOT_FIND_TEXT ) );
    if ( err == KErrNone )
        {
        TInt rem = tmp.MaxLength() - tmp.Length() - 1;
        if ( aFindText.Length() > rem )
            {
            TextUtils::TruncateToNumChars( aFindText, rem );
            }
        TBuf<80> buf;
        buf.Format( tmp, &aFindText );
        TextUtils::ClipToFit( buf, *iCoeEnv->NormalFont(), 
            iAvkonAppUi->ApplicationRect().Width() - 20 ); // -20 allows for borders on infomsg
        iEikonEnv->InfoMsg( buf );
        }
    }

EXPORT_C void CEikEdwin::GetFindText(TDes* aSearchText)
    {
    CancelFepTransaction();
    TInt startPos=0;
    TInt length=0;
    if (SelectionLength())
        {
        TCursorSelection selection=Selection();
        startPos=selection.LowerPos();
        length=SelectionLength();
        if (length>EEikEdwinFindStringMaxLen)
            goto GetWord;
        }
    else
        {
GetWord:
        GetWordInfo(CursorPos(),startPos,length);
        }
    if (!length)
        return;
    length=Min(length,EEikEdwinFindStringMaxLen);
    *aSearchText=iText->Read(startPos,length);
    TInt searchLen=aSearchText->Length();
    while (searchLen<length) // tried to read across a segment boundary
        {
        aSearchText->Append(iText->Read(startPos+searchLen,length-searchLen));
        searchLen=aSearchText->Length();
        }
    }

EXPORT_C void CEikEdwin::SetAllowPictures(TBool aAllow)
    {
    if (aAllow)
        iEdwinUserFlags|=EAllowPictures;
    else
        iEdwinUserFlags&=~EAllowPictures;
    }

EXPORT_C void CEikEdwin::CheckRemovePictures(TInt aStartPos,TInt aLength)
    {
    if (iEdwinUserFlags&EAllowPictures)
        return;
    TInt charsRead=0;
    while (charsRead<aLength)
        {
        TPtrC ptr=iText->Read(aStartPos,Min(aLength-charsRead,10));
        const TInt ptrLength=ptr.Length();
        TInt located=0;
        TInt pos=ptr.Locate(TChar(CEditableText::EPictureCharacter));
        while(pos!=-1)
            {
            if (iEdwinInternalFlags&ERichText)
                STATIC_CAST(CRichText*,iText)->DeleteFromParagraph(aStartPos+pos,1);
            else
                {
                TRAP_IGNORE( iText->DeleteL(aStartPos+pos,1));
                }
            ++located;
            ptr.Set(ptr.Ptr(),ptr.Length()-1);
            pos=ptr.Locate(TChar(CEditableText::EPictureCharacter));
            }
        aStartPos+=(ptrLength-located);
        charsRead+=ptrLength;
        }
    }

/*
 * This function will remove the non Ascii character when the UNICODE
 * charaters are not allowed
 */
EXPORT_C void CEikEdwin::CheckValidityOfChars(TInt aStartPos,TInt aLength)
    {
    if (!OnlyASCIIChars())
        return;
    TInt charsRead=0;
    while (charsRead<aLength)
        {
        TBuf<1> buf;
        iText->Extract(buf, aStartPos, 1);
        if (!IsValidChar(buf[0]))
            {
            if (iEdwinInternalFlags&ERichText)
                STATIC_CAST(CRichText*,iText)->DeleteFromParagraph(aStartPos,1);
            else
                {
                TRAP_IGNORE( iText->DeleteL(aStartPos,1));
                }
            if ( iEdwinExtension->iSmiley )
                {
                iEdwinExtension->iSmiley->HandleDeleteL( aStartPos, 1 );
                }
            }
        else
            aStartPos++;//=(ptrLength-located);
        charsRead++;//=ptrLength;
        }

    }

EXPORT_C void CEikEdwin::SetWordDelimiters(TBool aPicture,TBool aPunctuation)
    {
    if (aPicture)
        iEdwinInternalFlags|=EPictureDelimits;
    else
        iEdwinInternalFlags&=~EPictureDelimits;
    if (aPunctuation)
        iEdwinInternalFlags|=EPunctuationDelimits;
    else
        iEdwinInternalFlags&=~EPunctuationDelimits;
    }

EXPORT_C void CEikEdwin::GetWordInfo(TInt aCurrentPos,TInt& aStartPos,TInt& aLength) const
    {
    __ASSERT_DEBUG(iText,Panic(EEikPanicEdwinNoText));
    iText->GetWordInfo(aCurrentPos,aStartPos,aLength,iEdwinInternalFlags&EPictureDelimits,iEdwinInternalFlags&EPunctuationDelimits);
    }

EXPORT_C void CEikEdwin::InsertFieldL(CTextField* aField,TUid aFieldType)
// Takes ownership of aField
// Inserts if there is space for the insert
//
    {
    __ASSERT_DEBUG(aField,Panic(EEikPanicFieldDoesNotExist));
    __ASSERT_DEBUG(iTextView,Panic(EEikPanicEdwinNoView));
    __ASSERT_DEBUG(iText,Panic(EEikPanicEdwinNoText));
    
    CancelFepTransaction();
    TPtr ptr(NULL,0); // a null TPtr
    TInt fieldLength=aField->Value(ptr);
    CleanupStack::PushL(aField);
    if (!((iTextLimit>(TextLength()+fieldLength)) || !iTextLimit))
        {
        iEikonEnv->InfoMsg(R_EIK_TBUF_MAX_CHARACTERS_REACHED);
        CleanupStack::PopAndDestroy(); // aField
        }
    else
        {
        TCursorSelection selection=iTextView->Selection();
        const TInt selectionLength=selection.Length();
        TBool formatHasChanged=EFalse;
        if (selectionLength)
            DeleteHighlightL(formatHasChanged);
        const TInt oldLength=TextLength();
        const TInt cursorPos=CursorPos();
        CleanupStack::Pop(); // InsertFieldL takes ownership of aField
        TRAPD(err,iText->InsertFieldL(cursorPos,aField,aFieldType));
        TRAP(err,iText->UpdateFieldL(cursorPos));
        if (NeedToChangeFormattingModeL())
            TRAP(err,SetAmountToFormatL());
        const TInt fieldLength=TextLength()-oldLength;
        const TInt newCursorPos=selection.LowerPos()+fieldLength;
        iTextView->SetPendingSelection(TCursorSelection(newCursorPos,newCursorPos));
        const TInt anchor=selection.LowerPos();
        selection.iAnchorPos=anchor;
        selection.iCursorPos=anchor+fieldLength;
        if (iUndoStore)
            iUndoStore->SetNewText(selection);
        iTextView->HandleInsertDeleteL(selection,selectionLength,formatHasChanged);
        ReportEdwinEventL( MEikEdwinObserver::EEventTextUpdate );
        DoReportEventL( MCoeControlObserver::EEventStateChanged );
        User::LeaveIfError(err);
        }
    }

EXPORT_C void CEikEdwin::UpdateAllFieldsL()
// move to the start of the document then update all fields
// (must move to the start first because doc may get much shorter)
//
    {
    __ASSERT_DEBUG(iTextView,Panic(EEikPanicEdwinNoView));
    __ASSERT_DEBUG(iText,Panic(EEikPanicEdwinNoText));

    CancelFepTransaction();
    SetCursorPosL(0,EFalse);
    const TInt oldLength=iText->DocumentLength();
    iText->UpdateAllFieldsL();
    if (NeedToChangeFormattingModeL())
        SetAmountToFormatL();
    TViewYPosQualifier yPosQualifier;
    yPosQualifier.SetMakeLineFullyVisible();
    iTextView->HandleGlobalChangeL(yPosQualifier);
    ReportEdwinEventL( MEikEdwinObserver::EEventTextUpdate );
    DoReportEventL( MCoeControlObserver::EEventStateChanged );
    }

EXPORT_C void CEikEdwin::UpdateCurrentFieldL()
// if we're in a field move to the start of it and update it, else do nothing
//
    {
    __ASSERT_DEBUG(iTextView,Panic(EEikPanicEdwinNoView));
    __ASSERT_DEBUG(iText,Panic(EEikPanicEdwinNoText));

    CancelFepTransaction();
    TInt pos = CursorPos();
    TFindFieldInfo info;
    if (iText->FindFields(info,pos))
        {// we are in a field
        // move cursor to start of field
        SetCursorPosL(info.iFirstFieldPos,EFalse);
        const TInt oldLength=iText->DocumentLength();
        // update the field
        iText->UpdateFieldL(pos);
        if (NeedToChangeFormattingModeL())
            SetAmountToFormatL();
        iTextView->HandleRangeFormatChangeL(TCursorSelection(info.iFirstFieldPos,info.iFirstFieldLen),EFalse);
        ReportEdwinEventL( MEikEdwinObserver::EEventTextUpdate );
        DoReportEventL( MCoeControlObserver::EEventStateChanged );
        }
    }

/**
 * Gets the list of logical colors employed in the drawing of the control,
 * paired with an explanation of how they are used. Appends the list to aColorUseList.
 *
 * @since ER5U 
 */
EXPORT_C void CEikEdwin::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const
    {
    CEikBorderedControl::GetColorUseListL(aColorUseList);
    LafEdwin::GetColorUseListL(aColorUseList);
    }

/**
 * Handles a change to the control's resources of type aType
 * which are shared across the environment, e.g. colors or fonts.
 * For this particular control aType can be a request of handling either the caps lock
 * modifier or the virtual cursor state.
 *
 * @since ER5U 
 */
EXPORT_C void CEikEdwin::HandleResourceChange(TInt aType)
    {
    CEikBorderedControl::HandleResourceChange(aType);

    switch (aType)
        {
    case KEikDynamicLayoutVariantSwitch:
        {
        iEdwinExtension->iThumbPos = KErrNotFound;
        SizeChanged();
        if ( !IsReadOnly() && !IsNonFocusing() 
                && !( iEdwinUserFlags & EDisplayOnly ) )
            {
            TInt docPos = CursorPos();
            TRect viewRect( AdjustedViewRect() );
            TViewYPosQualifier yPosQ;
            TInt yPos = ( viewRect.iBr.iY + viewRect.iTl.iY )/2;
            yPosQ.SetMakeLineFullyVisible();
            yPosQ.SetFillScreen();
            TRAP_IGNORE( iTextView->SetViewL( docPos, yPos, yPosQ ) ); 
            }                
        }
        break;
    case KEikMessageVirtualCursorStateChange:
        {
        TEikVirtualCursor& cursor=iEikonEnv->VirtualCursor();
    
        if(!(iEdwinUserFlags&EIgnoreVirtualCursor) && IsFocused()
            && cursor.CursorState(*iEikonEnv)==TEikVirtualCursor::EOn)
            {
            TRAP_IGNORE( cursor.SetCursorStateL(TEikVirtualCursor::ESuspended,*iEikonEnv));
            }
        }
        break;
    case KEikMessageCaptionedControlEditableStateChange:
        {
        iEdwinUserFlags &= ~EAvkonNotEditable;
        }
        break;
    case KEikMessageCaptionedControlNotEditableStateChange:
        {
        iEdwinUserFlags |= EAvkonNotEditable;
        }
        break;
    case KEikInputLanguageChange:
        {
        UpdateCache(KEikInputLanguageChange);
        DoAlignment();
        }
        break;
    default:
        break;
        }
    }


/**
 * Sets the edwin size observer to aObserver. Does not imply transfer of ownership.
 */
EXPORT_C void CEikEdwin::SetEdwinSizeObserver(MEikEdwinSizeObserver* aEdwinSizeObserver)
    {
    iEdwinSizeObserver = aEdwinSizeObserver;
    CheckIfEdwinIsResizable();
    }

void CEikEdwin::CheckIfEdwinIsResizable()
    {
    if (iEdwinSizeObserver!=NULL && iEdwinUserFlags&EResizable)
        {
        iEdwinInternalFlags &= ~EHasOneLineOnly;
        }

    if ((iEdwinSizeObserver==NULL || !(iEdwinUserFlags&EResizable)) && 
        (iNumberOfLines==1))
        {
        iEdwinInternalFlags |= EHasOneLineOnly;
        }
    }

TBool CEikEdwin::IsNewHeightWithinMinimumAndMaximum(TInt aNewHeight) const
// Checks if the new height is within the minimum and maximum edwin height.
    {
    const TInt edwinHeight = iSize.iHeight;
    TBool validHeight = ETrue;
    if (aNewHeight < edwinHeight)
        {
        if ( ((iMinimumHeight > 0) && (iMinimumHeight > aNewHeight) ) ||
            (iMinimumHeight == 0) )
            validHeight =  EFalse;
        }
    else if (aNewHeight > edwinHeight)
        {
        if ((iMaximumHeight > 0) && (iMaximumHeight < aNewHeight))
            validHeight =  EFalse;
        }
    return validHeight;
    }

/**
 * Reports the event EEventSizeChanging to the observer every time the text view height changes.
 *
 *  This routine has been significantly changed for AVKON:  (TimW Aug 2000)
 *  - It deals in numbers of lines rather than pixels for height.
 *  - It is triggers the oberver when the height reduces as well as when it increases.
 *  - It updates iNumberOfLInes
 *
 */
EXPORT_C void CEikEdwin::OnReformatL(const CTextView* /*aTextView*/)
    {
    if (iEdwinInternalFlags&EOnReformatting) 
        return;

    CheckIfEdwinIsResizable();
    if ( (iEdwinSizeObserver) && (iEdwinUserFlags&EResizable) )
        {
        const TInt extraHeight = iBorder.SizeDelta().iHeight+iMargins.iTop+iMargins.iBottom;
#ifdef _DEBUG
        TInt edwinHeightWithBorgersAndMargins = iSize.iHeight;
#endif

        TInt newHeight = TextLayout()->FormattedHeightInPixels() + extraHeight;

        TInt lines = TextLayout()->NumFormattedLines() ;
 

        iEdwinInternalFlags |= EOnReformatting;
//      if (newHeight!=edwinHeightWithBorgersAndMargins) 
        if ( lines != iNumberOfLines ) 
            {
#ifdef _DEBUG
            RDebug::Print(_L("Resizing edwin: newlines = %d, oldlines = %d, newHeight = %d. ehwbm = %d"), lines, iNumberOfLines, newHeight, edwinHeightWithBorgersAndMargins ) ; 
#endif
            iNumberOfLines = lines ;

            TInt minimumHeight = CalcMinimumHeightFromNumOfLinesL();
//          if ( IsEdwinHeightWithinMinimumAndMaximum(newHeight) ||
//              ((edwinHeightWithBorgersAndMargins > newHeight) && (newHeight == minimumHeight)) ||
//              (minimumHeight > newHeight) && (minimumHeight != edwinHeightWithBorgersAndMargins) )
//            if (ETrue)  
//                {
//              if ((minimumHeight > newHeight) && (minimumHeight != edwinHeightWithBorgersAndMargins))
                    newHeight = minimumHeight;
                TSize desirableEdwinSize(iSize.iWidth, newHeight);
                if (iEdwinSizeObserver->HandleEdwinSizeEventL(this, MEikEdwinSizeObserver::EEventSizeChanging, desirableEdwinSize))
                    {
                    DrawDeferred();
                }
//              }
            }
        iEdwinInternalFlags &= ~EOnReformatting;
        }
    }

TInt CEikEdwin::CalcMinimumHeightFromNumOfLinesL() const
    {
    TInt minimumHeight = iSize.iHeight;
    if (iNumberOfLines == 0)
        {
        if (iMinimumHeight > 0 )
            minimumHeight = iMinimumHeight;
        }
    else
        {
        __ASSERT_DEBUG(iLayout,Panic(EEikPanicEdwinNoLayout));
        TInt lineHeight = iLayout->FormattedHeightInPixels();
        const TInt docLength = iLayout->DocumentLength();
        if (docLength > 0)
            {
            const TInt numFormattedLines = iLayout->NumFormattedLines();
            lineHeight = lineHeight / numFormattedLines;
            }
        minimumHeight = (lineHeight * iNumberOfLines) + iBorder.SizeDelta().iHeight+iMargins.iTop+iMargins.iBottom;
        }
    return minimumHeight;
    }

void CEikEdwin::CheckEdwinHeight()
    {
    const TInt height = iSize.iHeight;
    if ( (height >= iMaximumHeight) && (iMaximumHeight > 0) )
        iSize.iHeight = iMaximumHeight;
    else if ( (height < iMinimumHeight) && (iMinimumHeight > 0) )
        iSize.iHeight = iMinimumHeight;
    }

void CEikEdwin::SetEdwinHeight(TInt aHeight)
    {
    if ( (aHeight > iMaximumHeight) && (iMaximumHeight > 0) )
        iSize.iHeight = iMaximumHeight;
    else if ( (aHeight < iMinimumHeight) && (iMinimumHeight > 0) )
        iSize.iHeight = iMinimumHeight;
    else
        iSize.iHeight = aHeight;
    }

/**
 * Returns the minimum edwin height.
 * 
 */
EXPORT_C TInt CEikEdwin::MinimumHeight() const
    {
    return iMinimumHeight;
    } 

/**
 * Returns the maximum edwin height.
 */
EXPORT_C TInt CEikEdwin::MaximumHeight() const
    {
    return iMaximumHeight;
    } 


/**
 * Sets the minimum edwin height to be aHeight. It also adjustes the maximum edwin height when
 * its values is smaller than aHeight.
 */
EXPORT_C void CEikEdwin::SetMinimumHeight(TInt aHeight)
    {
    if (aHeight > iMaximumHeight)
        iMaximumHeight  = aHeight;
    iMinimumHeight = aHeight;
    } 

/**
 * Sets the maximum edwin height to be aHeight. It also adjustes the minimum edwin height when
 * its values is bigger than aHeight.
 */
EXPORT_C void CEikEdwin::SetMaximumHeight(TInt aHeight)
    {
    if (iMinimumHeight > aHeight)
        iMinimumHeight = aHeight;
    iMaximumHeight = aHeight;
    } 

EXPORT_C void CEikEdwin::InsertDeleteCharsL(TInt aInsertPos,const TDesC& aText,const TCursorSelection& aSelection)
    {
    __ASSERT_DEBUG(iText,Panic(EEikPanicEdwinNoText));
    __ASSERT_DEBUG(iTextView,Panic(EEikPanicEdwinNoView));
    const TInt lowerPos=aSelection.LowerPos();
    TBool formatChanged=EFalse;
    const TInt length=aSelection.Length();
    if (iEdwinInternalFlags&ERichText)
        {
        STATIC_CAST(CRichText*,iText)->CancelInsertCharFormat();
        formatChanged=STATIC_CAST(CRichText*,iText)->DelSetInsertCharFormatL(lowerPos,length);
        }
    else
        {
        formatChanged=iText->DeleteL(lowerPos,length);
        if ( iEdwinExtension->iSmiley )
            {
            iEdwinExtension->iSmiley->HandleDeleteL( lowerPos, length );
            }
        }
    iText->InsertL(aInsertPos,aText);
    if ( iEdwinExtension->iSmiley )
        {
        iEdwinExtension->iSmiley->HandleInsertL( aInsertPos, aText.Length() );
        ConvertTextForSmileyL( TCursorSelection( aInsertPos, 
            aInsertPos + aText.Length() ), ETrue );
        }
    iTextView->HandleInsertDeleteL(TCursorSelection(aInsertPos,aInsertPos+aText.Length()),length,formatChanged);
    }

EXPORT_C void CEikEdwin::SetNonPrintingCharsVisibility(TNonPrintingCharVisibility aVisibility)
    {
    __ASSERT_DEBUG(iLayout,Panic(EEikPanicEdwinNoLayout));
    iLayout->SetNonPrintingCharsVisibility(aVisibility);
    }

EXPORT_C TNonPrintingCharVisibility CEikEdwin::NonPrintingCharsVisibility() const
    {
    __ASSERT_DEBUG(iLayout,Panic(EEikPanicEdwinNoLayout));
    return iLayout->NonPrintingCharsVisibility();
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
EXPORT_C void CEikEdwin::WriteInternalStateL(RWriteStream&) const
    {}
#else
EXPORT_C void CEikEdwin::WriteInternalStateL(RWriteStream& aWriteStream) const
    {
    _LIT(KEikLitEdWnCtlStart,"<CEikEdwin>");
    _LIT(KEikLitEdWnCtlEnd,"<\\CEikEdwin>");
    _LIT(KEikLitEdWnUsFlgs,"<iEdwinUserFlags>");
    _LIT(KEikLitEdWnUsFlgsEnd,"<\\iEdwinUserFlags>");
    _LIT(KEikLitEdWnIntFlgs,"<iEdwinInternalFlags>");
    _LIT(KEikLitEdWnIntFlgsEnd,"<\\iEdwinInternalFlags>");
    _LIT(KEikLitEdWnPlnTxt,"<iText>");
    _LIT(KEikLitEdWnPlnTxtEnd,"<\\iText>");
    _LIT(KEikLitEdWnTxtLmt,"<iTextLimit>");
    _LIT(KEikLitEdWnTxtLmtEnd,"<\\iTextLimit>");
    _LIT(KEikLitEdWnNoLns,"<iNumberOfLines>");
    _LIT(KEikLitEdWnNoLnsEnd,"<\\iNumberOfLines>");
    _LIT(KEikLitEdWnLstPtrDPs,"<iLastPointerDocPos>");
    _LIT(KEikLitEdWnLstPtrDPsEnd,"<\\iLastPointerDocPos>");
    _LIT(KEikLitEdWnMrgns, "<iMargins>");
    _LIT(KEikLitEdWnMrgnsEnd, "<\\iMargins>");
    _LIT(KEikLitEdWnAvLnsVwRct,"<iAvgLinesInViewRect>");
    _LIT(KEikLitEdWnAvLnsVwRctEnd,"<\\iAvgLinesInViewRect>");
    _LIT(KEikLitEdWnAvChPrLn,"<iAvgCharsPerLine>");
    _LIT(KEikLitEdWnAvChPrLnEnd,"<\\iAvgCharsPerLine>");
    _LIT(KEikLitEdWnRgWrpGtr,"<iRightWrapGutter>");
    _LIT(KEikLitEdWnRgWrpGtrEnd,"<\\iRightWrapGutter>");
    _LIT(KEikLitEdWnLyWdth,"<iLayoutWidth>");
    _LIT(KEikLitEdWnLyWdthEnd,"<\\iLayoutWidth>");
    _LIT(KEikLitEdWnMinH,"<iMinimumHeight>");
    _LIT(KEikLitEdWnMinHEnd,"<\\iMinimumHeight>");
    _LIT(KEikLitEdWnMaxH,"<iMaximumHeight>");
    _LIT(KEikLitEdWnMaxHEnd,"<\\iMaximumHeight>");
    _LIT(KEikLitEdWnLstPrtAPs,"<iLastPointerAnchorPosition>");
    _LIT(KEikLitEdWnLstPrtAPsEnd,"<\\iLastPointerAnchorPosition>");
    
    aWriteStream << KEikLitEdWnCtlStart;
    aWriteStream << KEikLitEdWnUsFlgs;
    aWriteStream.WriteInt32L(iEdwinUserFlags);
    aWriteStream << KEikLitEdWnUsFlgsEnd;
    aWriteStream << KEikLitEdWnIntFlgs;
    aWriteStream.WriteInt32L(iEdwinInternalFlags);
    aWriteStream << KEikLitEdWnIntFlgsEnd;
    aWriteStream << KEikLitEdWnPlnTxt;
    if(iText->DocumentLength())
        aWriteStream << *iText;
    aWriteStream << KEikLitEdWnPlnTxtEnd;
    aWriteStream << KEikLitEdWnTxtLmt;
    aWriteStream.WriteInt32L(iTextLimit);
    aWriteStream << KEikLitEdWnTxtLmtEnd;
    aWriteStream << KEikLitEdWnNoLns;
    aWriteStream.WriteInt32L(iNumberOfLines);
    aWriteStream << KEikLitEdWnNoLnsEnd;
    aWriteStream << KEikLitEdWnLstPtrDPs;
    aWriteStream.WriteInt32L(iLastPointerDocPos);
    aWriteStream << KEikLitEdWnLstPtrDPsEnd;
    aWriteStream << KEikLitEdWnMrgns;
    aWriteStream.WriteInt8L(iMargins.iLeft);
    aWriteStream.WriteInt8L(iMargins.iRight);
    aWriteStream.WriteInt8L(iMargins.iTop);
    aWriteStream.WriteInt8L(iMargins.iBottom);
    aWriteStream << KEikLitEdWnMrgnsEnd;
    aWriteStream << KEikLitEdWnAvLnsVwRct;
    aWriteStream.WriteInt32L(iAvgLinesInViewRect);
    aWriteStream << KEikLitEdWnAvLnsVwRctEnd;
    aWriteStream << KEikLitEdWnAvChPrLn;
    aWriteStream.WriteInt32L(iAvgCharsPerLine);
    aWriteStream << KEikLitEdWnAvChPrLnEnd;
    aWriteStream << KEikLitEdWnRgWrpGtr;
    aWriteStream.WriteInt32L(iRightWrapGutter);
    aWriteStream << KEikLitEdWnRgWrpGtrEnd;
    aWriteStream << KEikLitEdWnLyWdth;
    aWriteStream.WriteInt32L(iLayoutWidth);
    aWriteStream << KEikLitEdWnLyWdthEnd;
    aWriteStream << KEikLitEdWnMinH;
    aWriteStream.WriteInt32L(iMinimumHeight);
    aWriteStream << KEikLitEdWnMinHEnd;
    aWriteStream << KEikLitEdWnMaxH;
    aWriteStream.WriteInt32L(iMaximumHeight);
    aWriteStream << KEikLitEdWnMaxHEnd;
    aWriteStream << KEikLitEdWnLstPrtAPs;
    aWriteStream.WriteInt32L(iLastPointerAnchorPos);
    aWriteStream << KEikLitEdWnLstPrtAPsEnd;
    CEikBorderedControl::WriteInternalStateL(aWriteStream);
    aWriteStream << KEikLitEdWnCtlEnd;
    }
#endif

EXPORT_C void CEikEdwin::Reserved_2()
    {}

EXPORT_C void CEikEdwin::Reserved_3()
    {}

// Avkon editor extensions
EXPORT_C void CEikEdwin::SetAknEditorCase(TInt aCase)
    {
    if (iEdwinFepSupport && iEdwinFepSupport->State(KNullUid))
        STATIC_CAST(CAknEdwinState*, iEdwinFepSupport->State(KNullUid))->SetDefaultCase(aCase);
    }

EXPORT_C void CEikEdwin::SetAknEditorPermittedCaseModes(TInt aPermittedCaseModes)
    {
    if (iEdwinFepSupport && iEdwinFepSupport->State(KNullUid))
        STATIC_CAST(CAknEdwinState*, iEdwinFepSupport->State(KNullUid))->SetPermittedCases(aPermittedCaseModes);
    }

EXPORT_C void CEikEdwin::SetAknEditorNumericKeymap(TAknEditorNumericKeymap aNumericKeymap)
    {
    if (iEdwinFepSupport && iEdwinFepSupport->State(KNullUid))
        STATIC_CAST(CAknEdwinState*, iEdwinFepSupport->State(KNullUid))->SetNumericKeymap(aNumericKeymap);
    }

EXPORT_C void CEikEdwin::SetAknEditorInputMode(TInt aInputMode)
    {
    if (iEdwinFepSupport && iEdwinFepSupport->State(KNullUid))
        STATIC_CAST(CAknEdwinState*, iEdwinFepSupport->State(KNullUid))->SetDefaultInputMode(aInputMode);
    }

EXPORT_C void CEikEdwin::SetAknEditorAllowedInputModes(TInt aInputModes)
    {
    if (iEdwinFepSupport && iEdwinFepSupport->State(KNullUid))
        STATIC_CAST(CAknEdwinState*, iEdwinFepSupport->State(KNullUid))->SetPermittedInputModes(aInputModes);
    }

EXPORT_C void CEikEdwin::SetAknEditorSpecialCharacterTable(TInt aSCTResId)
    {
    if (iEdwinFepSupport && iEdwinFepSupport->State(KNullUid))
        STATIC_CAST(CAknEdwinState*, iEdwinFepSupport->State(KNullUid))->SetSpecialCharacterTableResourceId(aSCTResId);
    }

EXPORT_C void CEikEdwin::SetAknEditorFlags(TInt aFlags)
    {
    if (iEdwinFepSupport)
        {
        CAknEdwinState* edwinState = STATIC_CAST(CAknEdwinState*, iEdwinFepSupport->State(KNullUid));
        if (edwinState)
            {
            edwinState->SetFlags(aFlags);
            TRAP_IGNORE( edwinState->ReportAknEdStateEventL(MAknEdStateObserver::EAknEdwinStateFlagsUpdate));
            }
        }
    }

EXPORT_C void CEikEdwin::SetAknEditorCurrentInputMode(TInt aInputMode)
    {
    if (iEdwinFepSupport)
        {
        CAknEdwinState* edwinState = STATIC_CAST(CAknEdwinState*, iEdwinFepSupport->State(KNullUid));
        if (edwinState)
            {
            edwinState->SetCurrentInputMode(aInputMode);
            TRAP_IGNORE(edwinState->ReportAknEdStateEventL(MAknEdStateObserver::EAknEdwinStateInputModeUpdate));
            }
        }    
    }

EXPORT_C TInt CEikEdwin::AknEditorCurrentInputMode()
    {
    TInt inputMode = EAknEditorNullInputMode;
    if (iEdwinFepSupport)
        {
        CAknEdwinState* edwinState = STATIC_CAST(CAknEdwinState*, iEdwinFepSupport->State(KNullUid));
        if (edwinState)
            {
            inputMode = edwinState->CurrentInputMode();
            }
        }
    return inputMode;
    }

EXPORT_C void CEikEdwin::SetAknEditorCurrentCase(TInt aCase)
    {
    if (iEdwinFepSupport)
        {
        CAknEdwinState* edwinState = STATIC_CAST(CAknEdwinState*, iEdwinFepSupport->State(KNullUid));
        if (edwinState)
            {
            edwinState->SetCurrentCase(aCase);
            TRAP_IGNORE( edwinState->ReportAknEdStateEventL(MAknEdStateObserver::EAknEdwinStateCaseModeUpdate));
            }
        }
    }

EXPORT_C void CEikEdwin::SetAknEditorLocalLanguage(TLanguage aLanguage)
    {
    if (iEdwinFepSupport)
        {
        CAknEdwinState* edwinState = STATIC_CAST(CAknEdwinState*, iEdwinFepSupport->State(KNullUid));
        if (edwinState)
            {
            edwinState->SetLocalLanguage(aLanguage);
            TRAP_IGNORE( edwinState->ReportAknEdStateEventL(MAknEdStateObserver::EAknEdwinStateLocalLanguageUpdate));
            }
        }
    }

EXPORT_C void CEikEdwin::NotifyEditorStateObserverOfStateChangeL()
    {
    if (iEdwinFepSupport && iEdwinFepSupport->State(KNullUid))
        {
        STATIC_CAST(CAknEdwinState*, iEdwinFepSupport->State(KNullUid))->ReportAknEdStateEventL(MAknEdStateObserver::EAknEdwinStateEventStateUpdate);
        }
    }

EXPORT_C void CEikEdwin::ReadAknResourceL(TResourceReader& aReader)
    {
    SetAknEditorCase(aReader.ReadInt16());
    SetAknEditorPermittedCaseModes(aReader.ReadInt16());
    SetAknEditorNumericKeymap(static_cast<TAknEditorNumericKeymap>(aReader.ReadInt16()));
    SetAknEditorAllowedInputModes(aReader.ReadInt16());
    SetAknEditorInputMode(aReader.ReadInt16());
    SetAknEditorSpecialCharacterTable(aReader.ReadInt32());

    SetAknEditorFlags(aReader.ReadInt16() | AknEdwinFlags());
    
    // added to have a max height
    SetMaximumHeightInLines(aReader.ReadInt16());

    aReader.ReadInt16(); // ignore baseline
    aReader.ReadInt16(); // spare
    
    // The following tries to ensure that those unfortunate number editors that
    // trust the default resource keymapping value don't break.
    if ( iEdwinFepSupport && iEdwinFepSupport->State( KNullUid ) )
        {
        CAknEdwinState* state = static_cast<CAknEdwinState*>( iEdwinFepSupport->State( KNullUid ) );
        
        if ( !( state->PermittedInputModes() & EAknEditorTextInputMode ) && 
             state->NumericKeymap() == EAknEditorAlphanumericNumberModeKeymap )
            {
            // The OLD default value of the resource. This is safe, since alphanumeric is
            // invalid anyway if the editor doesn't allow text input.
            SetAknEditorNumericKeymap( EAknEditorStandardNumberModeKeymap );
            }
        }
    }


EXPORT_C void CEikEdwin::SetSuppressBackgroundDrawing( TBool aSuppress )
    {
    if ( iEdwinExtension )
        {
        iEdwinExtension->SetSuppressBackgroundDrawing( aSuppress );
        }
    }
    
EXPORT_C TBool CEikEdwin::IsBackgroundDrawingSuppressed() const
    {
    TBool ret( EFalse );
    
    if ( iEdwinExtension )
        {
        ret = iEdwinExtension->IsBackgroundDrawingSuppressed();
        }
        
    return ret;
    }
    
EXPORT_C void CEikEdwin::SetTextLinesRect( const TRect& aRect )
    {
    if ( iEdwinExtension )
        {
        iEdwinExtension->iTextLinesRect = aRect;
        }
    }

EXPORT_C void CEikEdwin::SetScrollRect( const TRect & aRect )
    {
    if ( iEdwinExtension )
        {
        iEdwinExtension->iScrollRect = aRect;
        }
    }
    
EXPORT_C TRect CEikEdwin::GetTextLinesRect() const
    {
    if ( iEdwinExtension )
        {
        return iEdwinExtension->iTextLinesRect;
        }
    else
        {
        return TRect(); // Should initialize to empty
        }
    }

EXPORT_C TBool CEikEdwin::CcpuIsFocused() const
    {
    return IsFocused();
    }

EXPORT_C TBool CEikEdwin::CcpuCanCut() const
    {
    CAknEdwinState* state( EditorState() );
    if( state && state->Flags() & EAknEditorFlagFindPane )
    	{
    	return EFalse;
    	}
    return iCcpuSupport && !IsReadOnly() && SelectionLength() != 0;
    }

EXPORT_C void CEikEdwin::CcpuCutL()
    {
    ClipboardL(ECut);
    }

EXPORT_C TBool CEikEdwin::CcpuCanCopy() const
    {
    CAknEdwinState* state( EditorState() );
    if( state && state->Flags() & EAknEditorFlagFindPane )
    	{
    	return EFalse;
    	}
    return iCcpuSupport && SelectionLength() != 0;
    }

EXPORT_C void CEikEdwin::CcpuCopyL()
    {
    ClipboardL(ECopy);
    }

EXPORT_C TBool CEikEdwin::CcpuCanPaste() const
    {
    CAknEdwinState* state( EditorState() );
    if( state && state->Flags() & EAknEditorFlagFindPane )
    	{
    	return EFalse;
    	}
    if (!iCcpuSupport || IsReadOnly())
        return EFalse;

    TRAPD(err, DoCcpuCanPasteL());
    return err == KErrNone;
    }

EXPORT_C void CEikEdwin::CcpuPasteL()
    {
    ClipboardL(EPaste);
    }

EXPORT_C TBool CEikEdwin::CcpuCanUndo() const
    {
    return CanUndo();
    }

EXPORT_C void CEikEdwin::CcpuUndoL()
    {
    UndoL();
    }

void CEikEdwin::DoCcpuCanPasteL() const
    {
    if (!SelectionLength() && (iTextLimit && (TextLength() >= iTextLimit)))
        User::Leave(KErrNotFound);

    CClipboard* cb=CClipboard::NewForReadingL(iCoeEnv->FsSession());
    CleanupStack::PushL(cb);

    TBool richText = ETrue;
    TStreamId streamId=cb->StreamDictionary().At(KClipboardUidTypeRichText);
    if (streamId==KNullStreamId)
        {
        streamId=cb->StreamDictionary().At(KClipboardUidTypePlainText);
        richText = EFalse;
        }
    if (streamId==KNullStreamId)
        User::Leave(KErrNotFound);

    HBufC* allowedChars = GetAllowedCharsLC();
    User::LeaveIfError(CheckAllowedCharsL(*allowedChars, *cb, richText));

    CleanupStack::PopAndDestroy(2); // allowedChars, cb
    }

HBufC* CEikEdwin::GetAllowedCharsLC() const
    {
    if (iEdwinFepSupport && iEdwinFepSupport->State(KNullUid))
        {
        CAknEdwinState* state = STATIC_CAST(CAknEdwinState*, iEdwinFepSupport->State(KNullUid));
        TInt permittedModes = state->PermittedInputModes();

        if ( permittedModes & 
            ~(EAknEditorNumericInputMode | EAknEditorFullWidthNumericInputMode))
            {
            if ( OnlyASCIIChars() )
                {
                // While the specification for what characters actually are
                // allowed in "latin only" editor is underway, we'll do this. Once
                // the spec is set, a more efficient solution with constant
                // unicode ranges is in order..
                const TInt asciiLimit( 256 );
                HBufC* buf = HBufC::NewLC( asciiLimit );
                TPtr ptr( buf->Des() );
                
                for ( TInt i = 1; i < asciiLimit; ++i )
                    {
                    ptr.Append( TChar( i ) );
                    }
                    
                return buf;
                }
            else
                {
                return KNullDesC().AllocLC();
                }
            }

        // EAknEditorNumericInputMode and EAknEditorFullWidthNumericInputMode are only left.
        TInt resId = 0;
        switch (state->NumericKeymap())
            {
            case EAknEditorStandardNumberModeKeymap:
                resId = R_EIK_ALLOWED_STANDARDNUMBERMODEKEYMAP;
                break;
            case EAknEditorPlainNumberModeKeymap:
                resId = R_EIK_ALLOWED_PLAINNUMBERMODEKEYMAP;
                break;
            case EAknEditorCalculatorNumberModeKeymap:
                resId = R_EIK_ALLOWED_CALCULATORNUMBERMODEKEYMAP;
                break;
            case EAknEditorConverterNumberModeKeymap:
                resId = R_EIK_ALLOWED_CONVERTERNUMBERMODEKEYMAP;
                break;
            case EAknEditorToFieldNumberModeKeymap:
                resId = R_EIK_ALLOWED_TOFIELDNUMBERMODEKEYMAP;
                break;
            case EAknEditorFixedDiallingNumberModeKeymap:
            default:
                resId = R_EIK_ALLOWED_FIXEDDIALLINGNUMBERMODEKEYMAP;
                break;
            }

        return iEikonEnv->AllocReadResourceLC(resId);
        }
    else
        {
        User::Leave(KErrNoMemory);
        return NULL;
        }
    }

TInt CEikEdwin::CheckAllowedCharsL(const TDesC& aChars, CClipboard& aClipboard, TBool aRichText) const
    {
    TBool pictographsEnabled = EFalse;
    TBool fullWidthCharactersAllowed = ETrue;

    CAknEdwinState* edwinState = NULL;
    if (iEdwinFepSupport)
        {
        edwinState = STATIC_CAST(CAknEdwinState*, iEdwinFepSupport->State(KNullUid));
        }

    CAknPictographInterface* pictographInterface = iEdwinExtension->PictographInterface();
    if (edwinState)
        {
        if (FeatureManager::FeatureSupported(KFeatureIdJapanese))
            {
            fullWidthCharactersAllowed = edwinState->PermittedInputModes() & (
                EAknEditorFullWidthTextInputMode |
                EAknEditorFullWidthNumericInputMode |
                EAknEditorFullWidthKatakanaInputMode |
                EAknEditorHiraganaKanjiInputMode |
                EAknEditorHiraganaInputMode | 
                EAknEditorTextInputMode
                );
            }
        if (pictographInterface)
            {
            pictographsEnabled = edwinState->Flags() & EAknEditorFlagEnablePictographInput;
            }
        }
    
    if (aChars.Length() == 0 && (pictographsEnabled || !pictographInterface) && fullWidthCharactersAllowed)
        {
        // All characters are allowed to paste.
        return KErrNone;
        }

    CPlainText* txtStore;
    CRichText* richText = STATIC_CAST(CRichText*, Text());
    if (aRichText && richText)
        {
        const CParaFormatLayer* paraFormatLayer=richText->GlobalParaFormatLayer();
        const CCharFormatLayer* charFormatLayer=richText->GlobalCharFormatLayer();
        txtStore = CRichText::NewL(paraFormatLayer, charFormatLayer);
        }
    else
        {
        txtStore = CPlainText::NewL();
        }
    CleanupStack::PushL(txtStore);
    TInt bufferLength = txtStore->PasteFromStoreL(aClipboard.Store(), aClipboard.StreamDictionary(), 0);
    TInt textLength = 0;
    TInt textIndex = 0;
    TBool finished = EFalse;
    TInt err = KErrNone;
    do 
        {
        // EAknEditorNumericInputMode and EAknEditorFullWidthNumericInputMode are the only ones
        // that get this far, so we convert the input to latin if non-ascii chars
        // are allowed in the editor. This can leave if the text in the clipboard is huge.
        HBufC* txtStoreBuf = txtStore->Read( textIndex ).AllocL();
        CleanupStack::PushL( txtStoreBuf ); // in case something leavable is added later
        TPtr text = txtStoreBuf->Des();
        textLength = text.Length();
        
        if (aChars.Length() == 0)
            {
            if (pictographInterface && !pictographsEnabled &&
                pictographInterface->Interface()->ContainsPictographs(text))
                {
                // The clipboard contains pictographs but those are not allowed by the editor.
                finished = ETrue;
                err = KErrNotFound;
                }
            if ( err == KErrNone && !fullWidthCharactersAllowed )
                {
                // Go through clipboard context and check if full-width characters exist.
                for ( TInt ii = 0; ii < textLength; ii++ )
                    {
                    if (JPLangUtil::IsFullWidth(text[ii]) && text[ii] != 0x2029)
                        {
                        // The clipboard contains full-width character(s) but those are not allowed by the editor.
                        err = KErrNotFound;
                        finished = ETrue;
                        break;
                        }
                    }
                }
            }
        else
            {
            if ( !OnlyASCIIChars() )
                {
                AknTextUtils::ConvertDigitsTo( text, EDigitTypeWestern );
                }
                
            // Go through all allowed characters and check if the clipboard contains unallowed characters.
            for (TInt ii=0; ii < textLength; ii++)
                {
                TChar ch = text[ii];
                if (ch.IsPrint() && aChars.Locate(ch) == KErrNotFound)
                    {
                    err = KErrNotFound;
                    finished = ETrue;
                    break;
                    }
                }
            }
        CleanupStack::PopAndDestroy(); // txtStoreBuf
        textIndex += textLength;
        }
    while (!finished && textIndex < bufferLength);

    CleanupStack::PopAndDestroy(txtStore);    
    return err;
    }

EXPORT_C void CEikEdwin::EnableCcpuSupportL(TBool aSupport)
    {
    CAknCcpuSupport* ccpu = NULL;
    CAknEdwinState* edwinState = EditorState(); 
    
    if (aSupport)
        {
        ccpu = new(ELeave) CAknCcpuSupport(this);
        ccpu->SetMopParent(this);
        CleanupStack::PushL(ccpu);
        ccpu->ConstructL();
        CleanupStack::Pop(ccpu);
        if (edwinState)
            {
            edwinState->SetCcpuState(this);                 
            }       
        }
    else
        {       
        if (edwinState)
            {
            edwinState->SetCcpuState(NULL);                 
            }
        }           
            
    delete iCcpuSupport;
    iCcpuSupport = ccpu;
    } 

void CEikEdwin::DoReportEventL(MCoeControlObserver::TCoeEvent aEvent)
    {
    if (iCcpuSupport && aEvent == MCoeControlObserver::EEventStateChanged)
        iCcpuSupport->HandleSelectionChangeL();
    ReportEventL(aEvent);
    }

void CEikEdwin::SetKeyboardRepeatRate(TTimeIntervalMicroSeconds32 aKeyRepeatRate) const
    {
    // test for fixed timeouts (do not require capabilities)
    if (aKeyRepeatRate == TTimeIntervalMicroSeconds32(KAknStandardKeyboardRepeatRate))
        {
        CAknSgcClient::SetKeyboardRepeatRate(EAknApplicationDefaulRepeatRate);
        return;
        }
    else if (aKeyRepeatRate == TTimeIntervalMicroSeconds32(KAknEditorKeyboardRepeatRate))
        {
        CAknSgcClient::SetKeyboardRepeatRate(EAknEditorDefaulRepeatRate);
        return;
        }

    // fall through, this requires capability WriteDeviceData
    TTimeIntervalMicroSeconds32 currentRepeatDelay;
    TTimeIntervalMicroSeconds32 currentRepeatRate;
    iCoeEnv->WsSession().GetKeyboardRepeatRate(currentRepeatDelay, currentRepeatRate);
    if (aKeyRepeatRate!=currentRepeatRate)
        iCoeEnv->WsSession().SetKeyboardRepeatRate(currentRepeatDelay, aKeyRepeatRate);
    }


EXPORT_C void CEikEdwin::SetMaximumHeightInLines(TInt aLines)
    {
    iMaximumHeightInLines=aLines; 
    };

EXPORT_C TInt CEikEdwin::MaximumHeightInLines() const
    {
    return iMaximumHeightInLines;
    };

EXPORT_C void CEikEdwin::AddFlagToUserFlags(TUint32 aFlag)
    {
    iEdwinUserFlags|=aFlag;
    SetVKBStatus(); 
    if ( aFlag & EAvkonEnableSmileySupport )
        {
        EnableSmileySupportL( ETrue );
        }
    }

EXPORT_C void CEikEdwin::RemoveFlagFromUserFlags(TUint32 aFlag)
    {
    iEdwinUserFlags&=~aFlag;
    SetVKBStatus(); 
    if ( aFlag & EAvkonEnableSmileySupport )
        {    
        EnableSmileySupportL( EFalse );
        }
    }

EXPORT_C TUint32 CEikEdwin::UserFlags() const
    {
    return iEdwinUserFlags;
    }

EXPORT_C TTypeUid::Ptr CEikEdwin::MopSupplyObject(TTypeUid aId)
    {
    TRAPD(err, CheckEdwinExtensionL());
    if (err==KErrNone)
        {
        if (iEdwinExtension->FormAccessor() && aId.iUid == MAknFormAccessor::ETypeId)
            {
            return aId.MakePtr(iEdwinExtension->FormAccessor());
            }
        else if ( aId.iUid == CAknExtendedInputCapabilities::ETypeId )
            {
            return aId.MakePtr( iEdwinExtension->iExtendedInputCapabilities );
            }
        }
    return TTypeUid::Null();
    }

EXPORT_C void CEikEdwin::SetAlignment(TInt aAlignment)
    {
    if (iEdwinExtension)
        iEdwinExtension->SetAlignment(aAlignment);
    DoAlignment();
    }

void CEikEdwin::NewParagraphL()
    {
    CheckEdwinExtensionL(); // checks if iEdwinExtension is NULL and constucts it if necessary
    DoAlignment();
    }

TInt CEikEdwin::CurrentAlignment() const
    {
    if (iEdwinExtension)
        return iEdwinExtension->CurrentAlignment();
    return EAknEditorAlignBidi;
    }

void CEikEdwin::DoAlignment()
    {
    CParaFormat paraFormat;
    TParaFormatMask paraFormatMask;

    // Get para format information from existing para format - else it gets overwritten.
    if (iParaFormatLayer)
        {
        TRAPD( err,  iParaFormatLayer->SenseL( &paraFormat, paraFormatMask ) ) ;
        if (err)
            {
#ifdef _DEBUG
            RDebug::Print(_L("CEikEdwin: Error in sensing format\n"));
#endif
            return;
            }
        }

    CAknSettingCache& cache = CAknEnv::Static()->SettingCache();
    paraFormat.iLanguage = ELangEnglish;
    TLanguage currentLanguage = cache.InputLanguage();

    switch (CurrentAlignment())
        {
        case EAknEditorAlignLeft: paraFormat.iHorizontalAlignment = CParaFormat::EAbsoluteLeftAlign; break;
        case EAknEditorAlignRight: paraFormat.iHorizontalAlignment = CParaFormat::EAbsoluteRightAlign; break;
        case EAknEditorAlignCenter: paraFormat.iHorizontalAlignment = CParaFormat::ECenterAlign; break;
        case EAknEditorAlignBidi:
            {
            paraFormat.iHorizontalAlignment = CParaFormat::ELeftAlign;
            paraFormat.iLanguage = currentLanguage;
            break;
            }
        default: paraFormat.iHorizontalAlignment = CParaFormat::ELeftAlign; break;
        }
    paraFormatMask.SetAttrib(EAttParaLanguage);
    paraFormatMask.SetAttrib(EAttAlignment);

    CParaFormatLayer* paraFormatLayer = NULL;
    TBool alignNull = EFalse;
    TRAPD(error, 
        {
        paraFormatLayer = CParaFormatLayer::NewL(&paraFormat,paraFormatMask);
        SetParaFormatLayer(paraFormatLayer);
        if (iTextView)
            {
            NotifyNewFormatL();
            }
        else
            {
            alignNull = ETrue;
            }
        });
    
        if ( alignNull )
            {
#ifdef _DEBUG
            RDebug::Print(_L("CEikEdwin: Alignment found null CEikEdwin::iTextView\n"));
#endif
            }

    if (error)
        {
#ifdef _DEBUG
        RDebug::Print(_L("Error in applying formatting\n"));
#endif
        }
    }

CAknEdwinDrawingModifier* CEikEdwin::AknEdwinDrawingModifier()
    {
    CAknEdwinDrawingModifier* modifier = NULL;  
    MopGetObject( modifier );
    return modifier;
    }

TBool CEikEdwin::EditorSupportsNeutralProtection() const
    {
    TBool ret = ETrue;
    if (!InputCapabilities().FepAwareTextEditor())
        ret = EFalse;

    else if (InputCapabilities().SupportsSecretText())
        ret = EFalse;

    else if ( AknEdwinFlags() & EAknEditorFlagLatinInputModesOnly )
        ret = EFalse;

    else if (iEdwinFepSupport && iEdwinFepSupport->State(KNullUid))
        {
        if ( static_cast<CAknEdwinState*>(iEdwinFepSupport->State(KNullUid))->PermittedInputModes() == EAknEditorNumericInputMode)
            ret = EFalse;
        }
    else if ( !IsValidChar( EEikEdwinLeftToRightMark ) )
        ret = EFalse;

    return ret;
    }


TBool CEikEdwin::NeedsNeutralProtection( TInt aPosOfLowEndOfDelete, TInt aLengthToDelete, TDes& aNewText, TBool& aForwardProtection )
    {
    TBool protect(ETrue);
    if (!EditorSupportsNeutralProtection() || ( aLengthToDelete == 0) )
        protect = EFalse;

    // Perform no neutral protection if the beginning of the text is deleted.
    // Note that there MAY be protection occuring if the delete is from the end so there is 
    // no corresponding text on DocLength
    if ( aPosOfLowEndOfDelete <= 0 )
        protect = EFalse;

    TInt posOfNextCharHigherThanDelete = aPosOfLowEndOfDelete + aLengthToDelete;

    TInt docLen = Text()->DocumentLength();

    // Length to delete should not exceed the document length
    if ( posOfNextCharHigherThanDelete > docLen)
        protect = EFalse;
        
    TBool adjacentPrecedingIsNeutral(EFalse);
    TBool adjacentTrailingIsNeutral(EFalse);

    if ( protect )
        {
        adjacentPrecedingIsNeutral = CharIsNeutral( aPosOfLowEndOfDelete - 1);
        if ( posOfNextCharHigherThanDelete < Text()->DocumentLength() )
            adjacentTrailingIsNeutral = CharIsNeutral( posOfNextCharHigherThanDelete);

        if ( !adjacentPrecedingIsNeutral && !adjacentTrailingIsNeutral )
            protect = EFalse;
        }

    // Inits actually correspond to LTR, but they are only used if the bools indicating 
    // strong directionality found get set
    TBool directionPrecedingDeleteIsRTL(EFalse);
    TBool directionTrailingDeleteIsRTL(EFalse); 
    if ( protect )
        {
        TBool strongPreceding = GetExposedDirectionOfText( aPosOfLowEndOfDelete - 1, EFalse, directionPrecedingDeleteIsRTL );
        TBool strongTrailing = GetExposedDirectionOfText( posOfNextCharHigherThanDelete, ETrue, directionTrailingDeleteIsRTL );
        if (!strongTrailing)
            {
            TFormCursorModifierUtils cursorModifierUtils( *TextView(), *TextLayout() );
            TTmDocPosSpec pos = cursorModifierUtils.DocPos();
            TBool isRTLPara = cursorModifierUtils.IsRightToLeftParagraph(pos);
            directionTrailingDeleteIsRTL = isRTLPara;
            strongTrailing = ETrue;
            }
        if ( !strongPreceding || !strongTrailing)
            protect = EFalse;
        else if ( COMPARE_BOOLS( directionPrecedingDeleteIsRTL, directionTrailingDeleteIsRTL ) )
            protect = EFalse;
        }

    // Obtain ptr to text being deleted
    TPtrC deletedText = Text()->Read( aPosOfLowEndOfDelete, aLengthToDelete) ;

    if ( protect )
        {
        protect = EFalse;
        TBool deletedWasRTL;

        // Check for and do reverse protection
        if ( adjacentPrecedingIsNeutral ) 
            {
            TBool deletedTextIsStrong = GetExposedDirectionOfTextInDescriptor( deletedText, ETrue, deletedWasRTL ); // search forward into deleted stuff
            if ( deletedTextIsStrong && (directionPrecedingDeleteIsRTL == deletedWasRTL))
                {
                protect = ETrue;
                aForwardProtection = EFalse;
                if ( deletedWasRTL )
                    aNewText.Append( KEikEdwinRightToLeftMark );
                else
                    aNewText.Append( KEikEdwinLeftToRightMark );
                }
            }

        // Check for and do forward protection
        // Note it is possible to have both forward and reverse redecoration.
        if ( adjacentTrailingIsNeutral )
            {
            TBool deletedTextIsStrong = GetExposedDirectionOfTextInDescriptor( deletedText, EFalse, deletedWasRTL ); // search backward in deleted stuff
            if (deletedTextIsStrong && (directionTrailingDeleteIsRTL == deletedWasRTL) )
                {
                protect = ETrue;
                aForwardProtection = ETrue;
                if ( deletedWasRTL )
                    aNewText.Append( KEikEdwinRightToLeftMark );
                else
                    aNewText.Append( KEikEdwinLeftToRightMark );
                }
            }
        }

    return protect;
    }

TBool CEikEdwin::GetStrongDirectionality(TChar aChar, TBool& aRightToLeft ) const
    {
    TBool hasStrongDirectionality(EFalse);
    TChar::TBdCategory bdcat = aChar.GetBdCategory();
    
    if (    (bdcat == TChar::ERightToLeft) || 
            (bdcat == TChar::ERightToLeftArabic)
       )
        {
        hasStrongDirectionality = ETrue;
        aRightToLeft = ETrue;
        }
    else if (bdcat == TChar::ELeftToRight) 
        {
        hasStrongDirectionality = ETrue;
        aRightToLeft = EFalse;
        }

    return hasStrongDirectionality;
    }

TBool CEikEdwin::CharIsNeutral( TInt aPos ) const
    {
    TChar ch = Text()->Read( aPos, 1 )[0];
    TChar::TBdCategory bdcat = ch.GetBdCategory();
    return (    bdcat == TChar::EWhitespace || 
                bdcat == TChar::EOtherNeutral );
    }

TBool CEikEdwin::GetExposedDirectionOfTextInDescriptor( const TDesC& aText, TBool aForward, TBool& aIsRightToLeft ) const
    {
    TBool hasStrongCharacter(EFalse);

    TInt length = aText.Length();

    // bail out if there is zero length, 'cos it would add a lot of tests in the rest of the source
    if ( length <= 0 )
        return EFalse;

    TInt start = 0;
    TInt increment = 1;
    TInt limit = length;

    if ( !aForward )
        {
        start = length - 1;
        increment = -1;
        limit = -1; // Limit is one beyond that last executed in the loop
        }
    
    for ( TInt index = start; index != limit; index += increment )
        {
        TBool isRTL;
        if ( GetStrongDirectionality( aText[ index ], isRTL ) )
            {
            hasStrongCharacter = ETrue;
            aIsRightToLeft = isRTL;
            break;
            }
        }

    return hasStrongCharacter;    
    }

/** 
* Start at pos and scan for strong characters.
* Stop at paragraph boundaries. 
* Maximum of KMaxSearch of about 1 line...
*/
TBool CEikEdwin::GetExposedDirectionOfText( TInt aPos, TBool aForward, TBool& aIsRightToLeft ) const
    {
    TBool hasStrongCharacter(EFalse);

    // Access the plain text from the editor, getting a little bit at a time.
    TBool done(EFalse);
    TBool dataLeft(ETrue);

    TInt docLen = Text()->DocumentLength();
    if ( aPos < 0 || aPos >= docLen)
        dataLeft = EFalse;

    // These are the inclusive start and end positions of the chunk of text to look at in the 
    // loop.
    TInt start = aPos;
    TInt end = aPos;
    TInt len;

    while ( !done && dataLeft )
        {
        // Get new end/start position - constrained
        if ( aForward )
            {          
            end = start + KLengthAtATime - 1;
            if ( end >= docLen ) 
                end = docLen - 1;
            }
        else 
            {
            start = end - KLengthAtATime + 1;
            if ( start < 0 )
                start = 0;
            }

        len = end - start + 1;

        if ( len > 0 )
            {
            TPtrC ptr = Text()->Read( start, len );
            TBool isRightToLeft;
            if ( GetExposedDirectionOfTextInDescriptor( ptr, aForward, isRightToLeft ) )
                {
                done = ETrue;
                hasStrongCharacter = ETrue;
                aIsRightToLeft = isRightToLeft;
                }
            else
                {
                // Get new start/end position - constrained
                if (aForward)
                    {
                    start = end + 1;
                    if ( start >= docLen )
                        dataLeft = EFalse;
                    }
                else
                    {
                    end = start - 1;
                    if ( end <= -1 ) 
                        dataLeft = EFalse;
                    }
                }
            }
        else
            dataLeft = EFalse;          

        }
    return hasStrongCharacter;    
    }

EXPORT_C void CEikEdwin::SetPictographAnimationCallBack( TCallBack& aCallBack )
    {
    iEdwinExtension->SetPictoCallBack( aCallBack );
    }

const TCallBack& CEikEdwin::PictographAnimationCallBack() const
    {
    return iEdwinExtension->PictoCallBack();
    }

TBool CEikEdwin::IsPurePhoneNumberEditor() const
    {
    TBool retVal(EFalse);

    if (iEdwinFepSupport && iEdwinFepSupport->State(KNullUid))
        {
        CAknEdwinState* state = STATIC_CAST(CAknEdwinState*, iEdwinFepSupport->State(KNullUid) );
        if ( state->PermittedInputModes() == EAknEditorNumericInputMode && 
            ( state->NumericKeymap() == EAknEditorStandardNumberModeKeymap
            || state->NumericKeymap() == EAknEditorFixedDiallingNumberModeKeymap
            || state->NumericKeymap() == EAknEditorSATHiddenNumberModeKeymap
            || state->NumericKeymap() == EAknEditorSATNumberModeKeymap )
            )
                retVal = ETrue;
        }
    return retVal;
    }
    
EXPORT_C void CEikEdwin::SetTextSkinColorIdL(TInt aAknSkinIdForTextColor)
    {
    CheckEdwinExtensionL();
    iEdwinExtension->iSkinIdForText = aAknSkinIdForTextColor;
    }

EXPORT_C void CEikEdwin::SetHighlightStyleL(TAknsHighlightStyle aStyle)
    {
    CheckEdwinExtensionL();
    iEdwinExtension->iSkinHighlightStyle = aStyle;    
    }

    // for custom drawer, not exported
TInt CEikEdwin::SkinColorId() const
    {
    if (iEdwinExtension)
        {
        return iEdwinExtension->iSkinIdForText;
        }
    return KErrNotFound;
    }

TAknsHighlightStyle CEikEdwin::HighlightStyle() const
    {
    if (iEdwinExtension)
        {
        return iEdwinExtension->iSkinHighlightStyle;
        }
    return EEikEdwinHighlightNormal;    
    }

TRgb CEikEdwin::EditorBackgroundColor(TRgb& aConditionalColor) const
    {
    TRgb color;
    if (iEdwinExtension && iEdwinExtension->iEditorBackgroundColor.IsSet() )
        {
        aConditionalColor = iEdwinExtension->iEditorBackgroundColor.Value();        
        color = aConditionalColor;
        }
    else
        {
        color = CEikonEnv::Static()->ControlColor(EColorControlBackground, *this);
        }
    return color;
    }    

EXPORT_C void CEikEdwin::SetUpperFullFormattingLength( TInt aUpperFullFormattingLimit )
    {
    if ( iEdwinExtension )
        {
        iEdwinExtension->iUpperFullFormattingLength = Max( KMinimumFullFormattingLength, aUpperFullFormattingLimit );
        }
    }

EXPORT_C void CEikEdwin::EnableKineticScrollingL( TBool aEnable )
    {
    if ( iEdwinExtension && aEnable )
        {
        iEdwinExtension->EnableKineticScrollingL();
        }
    }

TBool CEikEdwin::NeedToChangeFormattingModeL() const
    {
    if ( TextLayout() && iText )
        {
        const TInt docLength = iText->DocumentLength();
        TBool bandFormatting = TextLayout()->IsFormattingBand();
        if ( ( !bandFormatting && docLength > UpperFullFormattingLength() )
            || ( bandFormatting && docLength <= LowerPartialFormattingLength() ) )
            {
            return ETrue;
            }
        }
    return EFalse;
    }
    
TRect CEikEdwin::AdjustedViewRect() const
    {        
    TRect mainPaneRect( 0, 0, 0, 0 );    
    AknLayoutUtils::LayoutMetricsRect (AknLayoutUtils::EMainPane, 
            mainPaneRect );
    TInt mainPaneHeight = mainPaneRect.Height();
    
    TRect rect( iTextView->ViewRect() );
    if ( rect.iTl.iY < 0 )
        {
        rect.iTl.iY = 0;
        }    
    if ( rect.iBr.iY > mainPaneHeight )
        {
        rect.iBr.iY = mainPaneHeight;
        }
    return rect;
    }
    
void CEikEdwin::SetVKBStatus()
    {
    TUint cap = iEdwinExtension->iExtendedInputCapabilities->Capabilities();
    if ( iEdwinUserFlags & EAvkonDisableVKB )
        {
        cap |= CAknExtendedInputCapabilities::EInputEditorDisableVKB;    
        }
    else
        {
        cap &= ~CAknExtendedInputCapabilities::EInputEditorDisableVKB;
        }   
    iEdwinExtension->iExtendedInputCapabilities->SetCapabilities( cap );
    }
    
void CEikEdwin::ScrollViewToCursorLineL()
    {
    TInt cursorPos = CursorPos();
    TRect viewRect( AdjustedViewRect() );    
    TInt pixels = -1;
    TBool scroll = EFalse;
    TInt endPos = iTextView->XyPosToDocPosL( viewRect.iBr );  
    while ( cursorPos > endPos && pixels != 0 )
        {        
        pixels = iTextView->ScrollDisplayL( TCursorPosition::EFLineDown );
        if ( pixels != 0 )
            {
            scroll = ETrue;
            }
        endPos = iTextView->XyPosToDocPosL( viewRect.iBr );        
        }
    if ( scroll )
        {
        UpdateScrollBarsL();
        }
    }
    
EXPORT_C void CEikEdwin::SetCursorVisible(TBool aVisible)
    {
    TRAP_IGNORE( SetCursorVisibilityL( aVisible ) );
    }

void CEikEdwin::PerformRecordedOperationL()
    {
    if ( iEdwinExtension->iDrawInvoked == CEikEdwinExtension::ENotDraw ||
        iEdwinExtension->iDrawInvoked == CEikEdwinExtension::EDrawing )
        {        
        if ( iEdwinExtension->iDrawInvoked == CEikEdwinExtension::ENotDraw )
            {
            iEdwinExtension->iDrawInvoked = CEikEdwinExtension::EDrawn;
            }
        if ( iEdwinExtension->iTempCursorPos != KErrNotFound )
            {
            if ( iEdwinExtension->iTempAnchorPos == KErrNotFound )
                {
                SetCursorPosL( iEdwinExtension->iTempCursorPos, 
                    iEdwinExtension->iTempSelect );      
                }
            else
                {
                SetSelectionL( iEdwinExtension->iTempCursorPos, 
                    iEdwinExtension->iTempAnchorPos );
                }            
            }
        iEdwinExtension->iTempCursorPos = KErrNotFound;
        iEdwinExtension->iTempAnchorPos = KErrNotFound;
        if ( iEdwinExtension->iDrawInvoked == CEikEdwinExtension::EDrawing )
            {
            iEdwinExtension->iDrawInvoked = CEikEdwinExtension::EDrawn;
            }
        }
    }

void CEikEdwin::ScrollIfAtTopOrBottomL()
    {
    TInt cursorPos = CursorPos();
    TRect viewRect( AdjustedViewRect() );    
    TPoint cursorPoint;
    if ( ! iTextView->DocPosToXyPosL(cursorPos, cursorPoint) )
        {
        return;
        }
        
    TInt topPos = iTextView->XyPosToDocPosL( viewRect.iTl );
    TInt bottomPos = iTextView->XyPosToDocPosL( viewRect.iBr );
    TPoint cursorLineLeftPiont(viewRect.iTl.iX,cursorPoint.iY );
    TPoint cursorLineRightPiont(viewRect.iBr.iX,cursorPoint.iY ); 
    TInt cursorLineLeftPos = iTextView->XyPosToDocPosL( cursorLineLeftPiont );
    TInt cursorLineRightPos = iTextView->XyPosToDocPosL( cursorLineRightPiont );
    const TInt totalChars = iText->DocumentLength();
    TBool scroll( EFalse );
    if (topPos >= 0 && topPos == cursorLineLeftPos)
        {
        iTextView->ScrollDisplayL( TCursorPosition::EFLineUp );
        UpdateScrollBarsL();
        scroll = ETrue ;
        }        
    if (bottomPos < totalChars && bottomPos == cursorLineRightPos)
        {
        iTextView->ScrollDisplayL( TCursorPosition::EFLineDown );
        UpdateScrollBarsL();
        scroll = ETrue ;
        }
    if ( scroll && iEdwinExtension->iDrawInvoked != 
        CEikEdwinExtension::EDrawing )
        {
        ReportEdwinEventL( MEikEdwinObserver::EEventNavigation );
        }
    }

void CEikEdwin::OnEditorStateFlagChange( TInt aOldFlags, TInt aNewFlags )
    {
    // for chinese popup flag
    TInt chinesePopup( aOldFlags & EAknEditorFlagChinesePopup );
    if ( chinesePopup != ( aNewFlags & EAknEditorFlagChinesePopup ) )
        {
        TRAP_IGNORE( ReportChinesePopupEventL( chinesePopup == 0 ) );
        }    
    }

void CEikEdwin::ReportChinesePopupEventL( TBool aChinesePopupOpen )
    {
    if ( aChinesePopupOpen )
        {
        ReportEdwinEventL( MEikEdwinObserver::EEventChinesePopupOpen );
        }
    else
        {
        ReportEdwinEventL( MEikEdwinObserver::EEventChinesePopupClose );
        }
    }

// for smiley support
void CEikEdwin::EnableSmileySupportL( TBool aEnableSmiley )
    {
    if ( aEnableSmiley && !AknLayoutUtils::LayoutMirrored() )
        {
        if ( !iEdwinExtension->iSmiley )
            {
            iEdwinExtension->iSmiley = CSmileyManager::NewL( *this );
            iEdwinExtension->iSmiley->SetAnimationPlayTimes( KNormalAnimPlayTimes );
            if ( IsReadOnly() || iEdwinUserFlags & EDisplayOnly )
                {
                iEdwinExtension->iSmiley->SetAnimationPlayTimes( 
                    KInfiniteAnimPlayTimes );
                }
            }        
        if ( TextLayout() )
            {
            TextLayout()->SetCustomWrap( iEdwinExtension->iSmileyWrap );
            }
        }    
    else
        {
        delete iEdwinExtension->iSmiley;
        iEdwinExtension->iSmiley = NULL;
        if ( TextLayout() )
            {
            TextLayout()->SetCustomWrap( NULL );
            }
        }
    }

TBool CEikEdwin::IsSmileyEnabled() const
    {
    return ( iEdwinExtension->iSmiley != NULL );
    }

void CEikEdwin::DrawSmileyInTextL( CBitmapContext& aGc, CFont& aFont, 
        const TDesC& aText, const TPoint& aPt )
    {    
    TRect viewRect( AdjustedViewRect() );
    TInt topY( aPt.iY - aFont.AscentInPixels() );
    TInt bottomY( aPt.iY + aFont.DescentInPixels() );
    const TInt KThreshold = 10;
    if ( topY < viewRect.iTl.iY - KThreshold || 
        bottomY > viewRect.iBr.iY + KThreshold )
        {
        return;
        }
    TInt pos( 0 );
    TPoint pt( aPt );
    HBufC* buf( NULL );
    TRAPD( err, 
        {
        pos = iTextView->XyPosToDocPosL( pt );
        buf = HBufC::NewL( aText.Length() );
        });
    if ( err == KErrNone )
        {
        TPtr text( buf->Des() );
        text.Copy( aText );
        TrimText( text );
        TInt smileyWidth( aFont.TextWidthInPixels( KSmileyString ) );
        for ( TInt i( 0 ); i < text.Length(); i++ )
            {
            if ( CSmileyManager::IsSmileyCode( text[i] ) )
                {
                TInt x( pt.iX + aFont.TextWidthInPixels( text.Left( i ) ) );
                TRect rect( x, topY, x + smileyWidth, bottomY );
                iEdwinExtension->iSmiley->DrawIconL( aGc, rect, i + pos );
                }
            }
        }
    delete buf;
    }

void CEikEdwin::ConvertVisibleTextForSmileyL( TBool aTextToCode )
    {
    if ( !iEdwinExtension->iSmiley && !iTextView )
        {
        return;
        }
    TCursorSelection visibleRange( GetVisibleTextRangeL() );
    ConvertTextForSmileyL( visibleRange, aTextToCode );    
    }

void CEikEdwin::ConvertTextForSmileyL( TCursorSelection aSelect, 
    TBool aTextToCode, TBool aRedraw )
    {    
    if ( iEdwinExtension->iSmiley && !iEdwinExtension->iInlineEditing )
        {
        if ( aTextToCode )
            {
            ExtendedRangeForSmiley( aSelect );
            }
        TInt start( aSelect.LowerPos() );   
        TInt length( aSelect.Length() );
        HBufC* buf( ExtractTextLC( aSelect ) );
        TPtr ptr( buf->Des() );
        if ( ptr.Length() > 0 &&
            iEdwinExtension->iSmiley->ConvertTextForSmileyL( aSelect.LowerPos(), 
                ptr, aTextToCode ) )
            {                
            iText->DeleteL( start, length );            
            iText->InsertL( start, ptr );            
            }
        CleanupStack::PopAndDestroy( buf );
        if ( aRedraw )
            {
            DrawDeferred();
            }
        }
    }
    
void CEikEdwin::TrimText( TDes& aText )
    {
    TInt index( -1 );
    const TText KTrimChar = 0xffff;
    for ( TInt i( 0 ); i < aText.Length() && aText[i] == KTrimChar; i++ )
        {        
        index = i;
        }
    if ( index != -1 )
        {
        aText.Delete( 0, index + 1 );
        }
    index = -1;
    for ( TInt i( aText.Length() - 1 ); i >= 0 && aText[i] == KTrimChar; i-- )
        {
        index = i;
        }
    if ( index != -1 )
        {
        aText.Delete( index, aText.Length() - index );
        }        
    }

TCursorSelection CEikEdwin::GetVisibleTextRangeL()
    {
    if ( iTextView )
        {
        TRect viewRect( AdjustedViewRect() );
        TInt start( iTextView->XyPosToDocPosL( viewRect.iTl ) );
        TInt end( iTextView->XyPosToDocPosL( viewRect.iBr ) );
        return TCursorSelection( start, end );
        }
    return TCursorSelection( 0, 0 );
    }

HBufC* CEikEdwin::ExtractTextLC( TCursorSelection aSelect )
    {
    TInt length( aSelect.Length() );
    HBufC* buf( HBufC::NewL( length ) );
    CleanupStack::PushL( buf );
    TPtr ptr( buf->Des() );
    iText->Extract( ptr, aSelect.LowerPos(), length );
    return buf;
    }

void CEikEdwin::ConvertSmileyIconToTextL( TInt aStartPos, TDes& aText )
    {
    if ( iEdwinExtension->iSmiley )
        {
        iEdwinExtension->iSmiley->ConvertTextForSmileyL( aStartPos,
            aText, EFalse );
        }
    }

void CEikEdwin::ExtendedRangeForSmiley( TCursorSelection& aSelect )
    { 
    if ( iEdwinExtension->iSmiley )
        {
        TInt textLength( TextLength() );
        TInt start = aSelect.LowerPos() - CSmileyManager::KMaxLength;
        if ( start < 0 )
            {
            start = 0;
            }
        TInt end = aSelect.HigherPos() + CSmileyManager::KMaxLength;
        if ( end > textLength )
            {
            end = textLength;
            }
        aSelect.iAnchorPos = start;
        aSelect.iCursorPos = end;
        }
    }

TBool CEikEdwin::ConvertSmileyForDeleteL( TInt aDocPos, TBool aBackSpace )
    {
    if ( !iEdwinExtension->iSmiley || ( aDocPos == 0 && aBackSpace ) || 
        ( aDocPos == TextLength() && !aBackSpace ) )
        {
        return EFalse;
        }
    TInt checkPos( aDocPos );
    if ( aBackSpace )
        {
        checkPos--;
        checkPos = checkPos >= 0 ? checkPos : 0;
        }
    if ( CSmileyManager::IsSmileyCode( iEdwinExtension->iSmiley->
        SmileyCodeByPos( checkPos ) ) && 
        !iEdwinExtension->iSmiley->IsDisabledSmileyIcon( checkPos ) )
        {
        TInt codeLength( iEdwinExtension->iSmiley->SmileyLength( checkPos ) );
        iEdwinExtension->iSmiley->DisableSmileyIcon( checkPos );
        TCursorSelection select( aDocPos, aDocPos );
        if ( aBackSpace )
            {
            select.iAnchorPos -= codeLength;
            }
        else
            {
            select.iCursorPos += codeLength;
            }
        ConvertTextForSmileyL( select, EFalse );
        iEdwinExtension->iExtendedInputCapabilities->ReportEventL( 
            CAknExtendedInputCapabilities::
            MAknEventObserver::EControlContentUpdatedInternally,
            NULL );
        return ETrue;
        }
    return EFalse;
    }

void CEikEdwin::ConvertSmileyForDeleteL( const TCursorSelection &aSelect )
    {
    if ( !iEdwinExtension->iSmiley )
        {
        return;
        }

    TInt lowerPos( aSelect.LowerPos() );
    TInt higherPos( aSelect.HigherPos() );

    // Extend the lowerPos to the edge of a smiley
    iEdwinExtension->iSmiley->HandleSetCursor( lowerPos + 1, lowerPos );
    // Extend the higherPos to the edge of a smiley
    iEdwinExtension->iSmiley->HandleSetCursor( higherPos - 1, higherPos );
  
    TCursorSelection select( lowerPos, higherPos );   
    HBufC* buf( ExtractTextLC( select ) );
    TPtr ptr( buf->Des() );
    if ( ptr.Length() > 0 &&
        iEdwinExtension->iSmiley->ConvertTextForSmileyL( lowerPos, 
            ptr, EFalse ) )
        {                
        iText->DeleteL( lowerPos, higherPos - lowerPos );            
        iText->InsertL( lowerPos, ptr );            
        }
    CleanupStack::PopAndDestroy( buf );
    }

void CEikEdwin::HandleScrollForSmileyL()
    {
    if ( !iEdwinExtension->iSmiley )
        {
        return;
        }
    TCursorSelection select( GetVisibleTextRangeL() );
    if ( select.LowerPos() != iEdwinExtension->iVisibleRange.LowerPos() ||
        select.HigherPos() != iEdwinExtension->iVisibleRange.HigherPos() )
        {
        iEdwinExtension->iVisibleRange.iCursorPos = select.iCursorPos;
        iEdwinExtension->iVisibleRange.iAnchorPos = select.iAnchorPos;
        }
    iEdwinExtension->iSmiley->SetVisibleRange( select.LowerPos(), 
        select.Length() );
    }

TBool CEikEdwin::AdjustCursorForSmileyL( TInt aOldCursor, TCursorSelection& aSelect )
    {
    TBool ret( EFalse );
    TCursorSelection select( Selection() );
    TInt cursor( select.iCursorPos );
    iEdwinExtension->iSmiley->HandleSetCursor( aOldCursor, cursor );
    if ( cursor != select.iCursorPos )
        {
        if ( select.iAnchorPos == select.iCursorPos )
            {
            select.iAnchorPos = cursor;
            }
        select.iCursorPos = cursor;        
        ret = ETrue;
        }
    aSelect = select;
    return ret;
    }

TRect CEikEdwin::AdjustDrawRectForSmiley( const TRect& aRect ) const 
    {
    TRect viewRect( AdjustedViewRect() );
    return TRect( viewRect.iTl.iX, aRect.iTl.iY, viewRect.iBr.iX, aRect.iBr.iY );
    }

void CEikEdwin::GetClipRegionForSmiley( RRegion& rgn, CFont& aFont, 
    const TDesC& aText, const TPoint& aPt, const TRect& aDrawRect ) const
    {
    TInt smileyWidth( aFont.TextWidthInPixels( KSmileyString ) );
    TInt topY( aDrawRect.iTl.iY );
    TInt bottomY( aDrawRect.iBr.iY );
    for ( TInt i( 0 ); i < aText.Length(); i++ )
        {
        if ( CSmileyManager::IsSmileyCode( aText[i] ) )
            {
            TInt x( aPt.iX + aFont.TextWidthInPixels( aText.Left( i ) ) );
            TRect rect( x, topY, x + smileyWidth, bottomY );
            rgn.SubRect( rect, NULL );
            }
        }
    }

TBool CEikEdwin::AdjustCursorPosByMovementL( TCursorPosition::TMovementType aMovement, 
    TBool aSelect )
    {
    TBool ret( EFalse );
    if ( iEdwinExtension->iSmiley )
        {
        TInt oldPos( CursorPos() );
        TInt curPos( oldPos );
        if ( aMovement == TCursorPosition::EFLeft )
            {
            curPos--;
            }
        else if ( aMovement == TCursorPosition::EFRight )
            {
            curPos++;
            }
        iEdwinExtension->iSmiley->HandleSetCursor( oldPos, curPos );
        if ( oldPos != curPos )
            {
            SetCursorPosL( curPos, aSelect );
            ret = ETrue;
            }
        }
    return ret;
    }

void CEikEdwin::SetSelectionVisibilityL( TBool isVisable )
    {
    iTextView->SetSelectionVisibilityL(isVisable);
    CAknEdwinState*edwinState = EditorState();
    if( !edwinState )
    	return;
    if(isVisable)
    	{
        SetAknEditorFlags( edwinState->Flags() | EAknEditorFlagSelectionVisible );
    	}
    else
    	{
    	SetAknEditorFlags( edwinState->Flags() & ~EAknEditorFlagSelectionVisible );
    	}
    return;
    }
TBool CEikEdwin::IsSelectionVisible()
	{
	TBool ret = EFalse;
	const TCursorSelection selection=iTextView->Selection();
	if (selection.Length() == 0)
		return ret;
	TPtrC text = iText->Read( selection.LowerPos(), selection.Length() );
	for (TInt i = 0; i < text.Length(); i++)
		{
		TChar character(text[i]);
		if (text[i] == ' ')
			return ETrue;
		
		TChar::TCategory category = character.GetCategory();
		
		if ( !((category&TChar::ESeparatorGroup == TChar::ESeparatorGroup) ||
			   (text[i]>=0x200B && text[i]<=0xFFFC)) )
			{
			ret = ETrue;
			break;
			}
		}
    return ret;
	}

// ---------------------------------------------------------------------------
// CEikEdwin::ScrollView
// ---------------------------------------------------------------------------
// 
TInt CEikEdwin::ScrollView( TInt aPixelsToScroll, TBool& aBorderExceeded, TInt& aRestOfPixels )
    {
    EnableRateScrolling( ETrue );
    TInt scrolledPixels( aPixelsToScroll );
    
    // Normal scrolling, we need to use old function because
    // we know from return value if border has been exceeded
    // This function call updates scrolledPixels to number
    // of actually scrolled pixels.
    
    TRAP_IGNORE( iTextView->ScrollDisplayPixelsL( scrolledPixels ) );
             
    if ( scrolledPixels != aPixelsToScroll )
        {
        // We can't move enough, we have exceeded the border
        // (at the beginning or end of the document)
        if ( aPixelsToScroll != 0 )
            {
            if ( aPixelsToScroll < 0 )
                {
                // End of document. Set flag to tell about that
                iEdwinExtension->iEndBorderExceeded = ETrue;
                aBorderExceeded = ETrue;
                }
            else
                {
                // Beginning of document. Set flag to tell about that
                iEdwinExtension->iStartBorderExceeded = ETrue;
                aBorderExceeded = ETrue;
                }
            
            // Calculate how many pixels more we should scroll and
            // return it in variable
            aRestOfPixels = aPixelsToScroll - scrolledPixels;
                        
            // Set variable how many pixels we are out of border 
            iEdwinExtension->iPixelsOutOfBorder = 0;
            }
        }
       
    if ( scrolledPixels != 0 )
        {
        iEdwinExtension->iScrolledDelta = scrolledPixels;
        TRAP_IGNORE( UpdateVertScrollBarThumbL() );
        iEdwinExtension->iScrolledDelta = 0;
        }
    
    EnableRateScrolling( EFalse );
    return scrolledPixels;    
    }

// ---------------------------------------------------------------------------
// CEikEdwin::ScrollViewWithBounce
// ---------------------------------------------------------------------------
// 
TInt CEikEdwin::ScrollViewWithBounce( TInt aPixelsToScroll,
    TBool& aEndOfBounce, TInt& aRestOfPixels )
    {
    aEndOfBounce = EFalse;
    aRestOfPixels = 0;
    EnableRateScrolling( ETrue );
     
    // We have to check here if we are moving enough so that bounce
    // ends (scrolling over the border toward content). In this case we
    // can use ScrollDisplayPixelsNoLimitBorderL to scroll only to border.
    // After that we have to move to mode where we use ScrollDisplayPixelsL
    // to detect if we exceed border again.
    TBool adjustScrolling( EFalse );
    if ( aPixelsToScroll > 0  && iEdwinExtension->iEndBorderExceeded )
        {
        if ( aPixelsToScroll > - iEdwinExtension->iPixelsOutOfBorder )
            {
            adjustScrolling = ETrue;
            }
        }
    else if ( aPixelsToScroll < 0 &&  iEdwinExtension->iStartBorderExceeded )
        {
        if ( aPixelsToScroll < - iEdwinExtension->iPixelsOutOfBorder )
            {            
            adjustScrolling = ETrue;
            }
        }
    
    if ( adjustScrolling )
        {
        // we are scrolling over the border, calculate how many
        // pixels we can scroll and how many pixels there is rest
        // after movement
        aRestOfPixels = aPixelsToScroll + iEdwinExtension->iPixelsOutOfBorder;
        aPixelsToScroll = -iEdwinExtension->iPixelsOutOfBorder;
        }
    
    // We are out of borders. Call scrolling function that supports bounce-effect
    TRAP_IGNORE( iTextView->ScrollDisplayPixelsNoLimitBorderL( aPixelsToScroll ) );

    // Update variable that tells how near the border we are.
    iEdwinExtension->iPixelsOutOfBorder += aPixelsToScroll;
               
    if ( iEdwinExtension->iStartBorderExceeded
        && iEdwinExtension->iPixelsOutOfBorder <= 0 )
        {
        // We are inside borders, reset flag and tell to caller
        iEdwinExtension->iStartBorderExceeded = EFalse;
        aEndOfBounce = ETrue;
        }
    else if ( iEdwinExtension->iEndBorderExceeded
        && iEdwinExtension->iPixelsOutOfBorder >= 0 )
        {
        // we are inside borders, reset flag and tell to caller
        iEdwinExtension->iEndBorderExceeded = EFalse;
        aEndOfBounce = ETrue;
        }
          
    if ( aPixelsToScroll != 0 )
        {
        TRAP_IGNORE( UpdateVertScrollBarThumbL() );
        }
    EnableRateScrolling( EFalse );
    // Return how many pixels we actually moved. It can be different to
    // value what user requested
    return aPixelsToScroll;  
    }

// ---------------------------------------------------------------------------
// CEikEdwin::PixelsOutOfBorder
// ---------------------------------------------------------------------------
//
TInt CEikEdwin::PixelsOutOfBorder() const
    {
    return iEdwinExtension->iPixelsOutOfBorder;
    }

// ---------------------------------------------------------------------------
// CEikEdwin::EnableRateScrolling
// ---------------------------------------------------------------------------
//
void CEikEdwin::EnableRateScrolling( TBool aEnable )
    {
    // This function is related to Rate scrolling implementation.
    // See comments in function SetKineticScrollingScrollbarModelL
    // for more information about Rate scrolling.
    
    // Use this function to change scrolling mode.
    // If aEnable is EFalse, Position scrolling mode is in use.
    // If aEnable is ETrue, Rate scrolling mode is in use.
    
    iEdwinExtension->iUseRateScroll = aEnable;
    }

// ---------------------------------------------------------------------------
// CEikEdwin::StoreCursorState
// ---------------------------------------------------------------------------
//
void CEikEdwin::StoreCursorState()
    {
    CAknEdwinState* state( EditorState() );
    if ( state && state->Flags() & EAknEditorFlagTextCursorVisible )
        {
        TRAP_IGNORE( SetCursorVisibilityL( EFalse ) );
        iEdwinExtension->iCursorWasVisible = ETrue;
        }
    }

// ---------------------------------------------------------------------------
// CEikEdwin::RestoreCursorState
// ---------------------------------------------------------------------------
//
void CEikEdwin::RestoreCursorState()
    {
    if ( iEdwinExtension->iCursorWasVisible )
        {
        TRAP_IGNORE( SetCursorVisibilityL( ETrue ) );
        iEdwinExtension->iCursorWasVisible = EFalse;
        }
    }

// ---------------------------------------------------------------------------
// CEikEdwin::KineticScrollingEnabled
// ---------------------------------------------------------------------------
//
TBool CEikEdwin::KineticScrollingEnabled() const
    {
    return iEdwinExtension && iEdwinExtension->iPhysicsHandler;
    }


void CEikEdwin::HandleSelectionForSmiley( TCursorSelection aSelect )
    {
    if ( !iEdwinExtension->iSmiley )
        {
        return;
        }
    if ( iCustomDrawer )
        {
        iEdwinExtension->iSmiley->SetHighlightColor( 
            iCustomDrawer->SystemColor( TLogicalRgb::ESystemSelectionBackgroundIndex, 
                KRgbWhite ) );
        }
    iEdwinExtension->iSmiley->HandleSelection( aSelect.LowerPos(), 
        aSelect.Length() );
    }

// ---------------------------------------------------------------------------
// CEikEdwin::SkipBackgroundDrawer
// ---------------------------------------------------------------------------
//
TBool CEikEdwin::SkipBackgroundDrawer() const
    {
    return iEdwinInternalFlags & ESkipBackgroundDrawer;
    }

TBool CEikEdwin::IsValidNumericCharL( TChar aChar )
    { 
    TBool ret(ETrue);
    CAknEdwinState* state = static_cast<CAknEdwinState*>( iEdwinFepSupport->State( KNullUid ) );    
    if (state && state->CurrentInputMode() == EAknEditorNumericInputMode )
    	{
        HBufC* allowedChars = GetAllowedCharsLC();
        if ( (*allowedChars).Length() > 0 && (*allowedChars).Locate( aChar ) == KErrNotFound )
            {
            ret = EFalse;
            }
        CleanupStack::PopAndDestroy(1);//allowedChars
        }
    return ret;
    }

// End of File

