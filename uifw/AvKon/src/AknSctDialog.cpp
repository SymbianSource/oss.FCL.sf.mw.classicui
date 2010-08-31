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
#include <barsread.h>
#include <uikon.hrh>
#include <e32std.h>
#include <eikcapc.h>

#include <aknlayoutscalable_avkon.cdl.h>
#include <layoutmetadata.cdl.h>

#include "aknborders.h"
#include "aknconsts.h"
#include "AknUtils.h"
#include "aknPopupHeadingPane.h"
#include "aknCharMap.h"
#include "aknSctDialog.h"
#include "AknSettingCache.h"
#include "aknenv.h"
#include "AknDef.h"
#include <bautils.h>

#include <AknLayout.lag>
#include <StringLoader.h>
#include <e32property.h>
#include <AvkonInternalCRKeys.h>    // KAknQwertyInputModeActive

#include <featmgr.h> // temporary
#include <PtiIndicDefs.h>
#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikenvinterface.h>
#endif

#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
#include <gfxtranseffect/gfxtranseffect.h>
#include <akntransitionutils.h>
#endif

#include <AknTasHook.h>
#include "aknsctfocushandler.h"

//
// class CAknCharMapDialog
//

// const TInt KHorizontalDialogMargin = 3;
// const TInt KVerticalDialogMargin = 3;

_LIT(KResFileName, "z:\\resource\\avkon.r");

const TInt KWsBufferSize = 16000;
const TInt KAknSctCBaButtonDirections = 3; // bottom, right and left

enum TCharMapDialogFlags
    {
    ECharMapDialogItemSelected = 0x01,
    ECharMapDialogItemLockNumericKeys = 0x02,
    ECharMapDialogRecentCharsRowDisabled = 0x04,
    ECharMapDialogTableExitSelected = 0x08
    };

// ----------------------------------------------------------------------------
// Extension class
//
// ----------------------------------------------------------------------------
//
NONSHARABLE_CLASS(CAknCharMapDialogExtension): public CBase
    {
public:
    static CAknCharMapDialogExtension* NewL(CAknCharMapDialog* aCaller);
    ~CAknCharMapDialogExtension();

private:
    CAknCharMapDialogExtension(CAknCharMapDialog* aCaller);
    void ConstructL();
    static TInt QwertyModeChangeNotification(TAny* aObj);
    void HandleQwertyModeChangeNotification();

public: // New method
    void SetCharacterCaseIfRequiredL();
    
public:
    TInt iFlags;
    TBool iQwertyMode;
    CAknCharMapDialog* iCaller;
    TBool iHaveReceivedKeyEvent;

    TInt iShowAnotherTableCharCase;
    TAknCharMapPictoMode    iPictoMode;
    TAknCharMapEmotionMode  iEmotionMode;

private:
    NONSHARABLE_CLASS(CSubscriber) : public CActive
        {
    public:
        CSubscriber(TCallBack aCallBack, RProperty& aProperty);
        ~CSubscriber();

    public: // New functions
        void SubscribeL();
        void StopSubscribe();

    private: // from CActive
        void RunL();
        void DoCancel();

    private:
        TCallBack   iCallBack;
        RProperty&  iProperty;
        };

private:
    CSubscriber* iQwertyModeStatusSubscriber;
    RProperty iQwertyModeStatusProperty;
    TInt iOldCharCase;
    };

// -----------------------------------------------------------------------------
// CAknCharMapDialogExtension::CAknCharMapDialogExtension
//
// Constructor of extension
// -----------------------------------------------------------------------------
//
CAknCharMapDialogExtension::CAknCharMapDialogExtension(CAknCharMapDialog* aCaller) : 
iFlags(0), iQwertyMode(EFalse), iCaller(aCaller), 
iShowAnotherTableCharCase(-1), iPictoMode(EAknCharMapPictoNoUse), iEmotionMode(EAknCharMapEmotionNoUse)
    {
    }

// -----------------------------------------------------------------------------
// CAknCharMapDialogExtension::~CAknCharMapDialogExtension
//
// Destructor of extension
// -----------------------------------------------------------------------------
//
CAknCharMapDialogExtension::~CAknCharMapDialogExtension()
    {
    // Stop subscribe in PubSub
    if (iQwertyModeStatusSubscriber)
        {
        iQwertyModeStatusSubscriber->StopSubscribe();
        }
    iQwertyModeStatusProperty.Close();
    delete iQwertyModeStatusSubscriber;
    }

// -----------------------------------------------------------------------------
// CAknCharMapDialogExtension::NewL
//
// Symbian 2 phase constructor
// -----------------------------------------------------------------------------
//
CAknCharMapDialogExtension* CAknCharMapDialogExtension::NewL(CAknCharMapDialog* aCaller)
    { // static
    CAknCharMapDialogExtension* self = new (ELeave) CAknCharMapDialogExtension(aCaller);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

// -----------------------------------------------------------------------------
// CAknCharMapDialogExtension::ConstructL
//
// Symbian construction
// -----------------------------------------------------------------------------
//
void CAknCharMapDialogExtension::ConstructL()
    {
    // Start also listening qwerty mode status.
    User::LeaveIfError(iQwertyModeStatusProperty.Attach(KCRUidAvkon,
        KAknQwertyInputModeActive));

    iQwertyModeStatusSubscriber = new (ELeave) CSubscriber(
        TCallBack(QwertyModeChangeNotification, this), iQwertyModeStatusProperty);

    iQwertyModeStatusSubscriber->SubscribeL();

    iOldCharCase=-1; // no default character case at beginning
    }

TInt CAknCharMapDialogExtension::QwertyModeChangeNotification(TAny* aObj)
    {
    if (aObj != NULL)
        {
        static_cast<CAknCharMapDialogExtension*>(aObj)->HandleQwertyModeChangeNotification();
        return KErrNone;
        }
    else
        {
        return KErrArgument;
        }
    }

void CAknCharMapDialogExtension::SetCharacterCaseIfRequiredL()
    {
    TInt value = 0;
    iQwertyModeStatusProperty.Get(value);
    iQwertyMode = value;

    CAknCharMap* charmapControl =
            STATIC_CAST(CAknCharMap*, iCaller->Control(EAknSCTQueryContentId));

    if ( (iQwertyMode) == (charmapControl->CharacterCase() == EAknSCTQwerty) )
        {
        // No change for Qwerty mode
        return;
        }

    if (iQwertyMode)
        {
        iFlags |= ECharMapDialogItemLockNumericKeys;

        iOldCharCase=charmapControl->CharacterCase();
        charmapControl->SetCharacterCaseL(EAknSCTQwerty);
        }
    else
        {
        iFlags &= (~ECharMapDialogItemLockNumericKeys);
        if (iOldCharCase!=-1)
            {
            charmapControl->SetCharacterCaseL(iOldCharCase);
            }
        else
            {
            charmapControl->SetCharacterCaseL(EAknSCTLowerCase);
            iOldCharCase = EAknSCTLowerCase;
            }
        }
    //charmapControl->DrawNow();
    }

void CAknCharMapDialogExtension::HandleQwertyModeChangeNotification()
    {
    TInt value = 0;
    iQwertyModeStatusProperty.Get(value);
    iQwertyMode = value;

    CAknCharMap* charmapControl =
            STATIC_CAST(CAknCharMap*, iCaller->Control(EAknSCTQueryContentId));

    if ( (iQwertyMode) == (charmapControl->CharacterCase() == EAknSCTQwerty) )
        {
        // No change for Qwerty mode
        return;
        }

    if (iQwertyMode)
        {
        iFlags |= ECharMapDialogItemLockNumericKeys;

        iOldCharCase=charmapControl->CharacterCase();
        TRAP_IGNORE( charmapControl->SetCharacterCaseL(EAknSCTQwerty) );
        }
    else
        {
        iFlags &= ~ECharMapDialogItemLockNumericKeys;
        if (iOldCharCase!=-1)
            {
            TRAP_IGNORE( charmapControl->SetCharacterCaseL(iOldCharCase) );
            }
        else
            {
            TRAP_IGNORE( charmapControl->SetCharacterCaseL(EAknSCTLowerCase) );
            iOldCharCase = EAknSCTLowerCase;
            }
        }

        // Reset focus.
    charmapControl->TakeFocus();

    // Draw new characters.
    charmapControl->DrawNow();
    }

// CAknCharMapDialogExtension::CSubscriber
CAknCharMapDialogExtension::CSubscriber::CSubscriber(TCallBack aCallBack, RProperty& aProperty)
    : CActive(EPriorityNormal), iCallBack(aCallBack), iProperty(aProperty)
    {
    CActiveScheduler::Add(this);
    }

CAknCharMapDialogExtension::CSubscriber::~CSubscriber()
    {
    Cancel();
    }

void CAknCharMapDialogExtension::CSubscriber::SubscribeL()
    {
    if (!IsActive())
        {
        iProperty.Subscribe(iStatus);
        SetActive();
        }
    }

void CAknCharMapDialogExtension::CSubscriber::StopSubscribe()
    {
    Cancel();
    }

void CAknCharMapDialogExtension::CSubscriber::RunL()
    {
    if (iStatus.Int() == KErrNone)
        {
        iCallBack.CallBack();
        SubscribeL();
        }
    }

void CAknCharMapDialogExtension::CSubscriber::DoCancel()
    {
    iProperty.Cancel();
    }

// CAknCharMapDialog
EXPORT_C CAknCharMapDialog::CAknCharMapDialog(TInt aCharCase, TDes& aSpecialChars, TInt aCharSetResourceId) : 
    iSpecialChars(&aSpecialChars), iCharCase(aCharCase), iCharSetResourceId(aCharSetResourceId)
    {
    CEikDialog::SetBorder( AknBorderId::EAknBorderNotePopup );
    
    TRAP_IGNORE(iExtension=CAknCharMapDialogExtension::NewL(this));

#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    GfxTransEffect::Register( this, KGfxContextMenuControlUid );
#endif
    
    AKNTASHOOK_ADD( this, "CAknCharMapDialog" );
    }

CAknCharMapDialog::~CAknCharMapDialog()
    {
    AKNTASHOOK_REMOVE();
    
    iAvkonEnv->CancelWsBufferRequest( iWsBufferRequestId );
    
    delete iExtension;
    }

EXPORT_C void CAknCharMapDialog::HandleResourceChange(TInt aType)
    {
    CAknCharMap* charmapControl = static_cast<CAknCharMap*>( Control( EAknSCTQueryContentId ) );

    if (aType==KEikDynamicLayoutVariantSwitch)
        {
        TRAP_IGNORE(iExtension->SetCharacterCaseIfRequiredL());
        //DoLayout();
        }

    CAknDialog::HandleResourceChange(aType);

    if (aType==KEikDynamicLayoutVariantSwitch)
        {
        // Softkeys
        ButtonGroupContainer().MakeVisible(AknLayoutUtils::PenEnabled() ? EFalse : ETrue);

        // Heading
        CAknPopupHeadingPane* headingPane = static_cast< CAknPopupHeadingPane* >( Control( EAknSCTQueryHeadingId ) );
        CEikCaptionedControl *ctrl = GetLineByLineAndPageIndex(0, EAknSCTQueryHeadingId);
        if (AknLayoutUtils::PenEnabled())
            {
            ctrl->SetLatent(ETrue);
            ctrl->SetLatentGroupLineFollows(ETrue);
            TRAP_IGNORE(charmapControl->UpdateInputFieldL());
            }
        else
            {
            ctrl->SetLatent(EFalse);
            ctrl->SetLatentGroupLineFollows(EFalse);
            if ( headingPane && charmapControl )
                {
                TRAP_IGNORE(
                    {
                    headingPane->SetPageL(
                        charmapControl->CurrentPage(),
                        charmapControl->PageCount() );
                        const TDesC* title = (charmapControl->IsJapaneseSctUi()) ?
                        charmapControl->TitleWithSelectingSpecialChar() : charmapControl->Title();
                    if ( title )
                        {
                        headingPane->SetTextL( *title );
                        }
                    });
                }
            //Set softkeys
            TRAP_IGNORE(SetSoftKeyL());
            }
        ctrl->SetFocusing(EFalse);
        DoLayout();
        DrawNow();
        Window().SetVisible( ETrue );
        }
    }

EXPORT_C TBool CAknCharMapDialog::OkToExitL(TInt aButtonId)
    {
    CAknCharMap* charmapControl = STATIC_CAST(CAknCharMap*, Control(EAknSCTQueryContentId));
    
    if (aButtonId == EAknSoftkeyNext)
        {
        TInt page = charmapControl->NextPageL();
        CAknPopupHeadingPane* headingPane = STATIC_CAST(CAknPopupHeadingPane*, Control(EAknSCTQueryHeadingId));
        headingPane->SetPageL(charmapControl->CurrentPage(), page);
        if (page && !AknLayoutUtils::PenEnabled())
            {
            const TDesC* title = charmapControl->IsJapaneseSctUi() ? 
                                 charmapControl->TitleWithSelectingSpecialChar() : 
                                 charmapControl->Title();
            headingPane->SetTextL(*title);
            }

        return(EFalse);
        }

    // Selection key / select softkey adds a character only if 5-key was not used
    // to select multiple characters before.
    if (aButtonId == EAknSoftkeyOk || aButtonId == EAknSoftkeySelect || aButtonId == EAknSoftkeyExit)
        {
        // In Japanese UI, SCT isn't closed by pressing "Select" softkey,
        // but SCT is closed by pressing "Back"(button id is EAknSoftkeyClose).
        MAknSctFocusHandler* handler = charmapControl->FocusHandler();
        if (charmapControl->IsJapaneseSctUi() &&
            aButtonId != EAknSoftkeyExit &&
            handler->FocusedControl() == charmapControl)
            {
            TKeyEvent key;
            key.iCode=EKeySpace;
            key.iModifiers=0;
            handler->FocusedControl()->OfferKeyEventL(key, EEventKey);
            return(EFalse);
            }
        // else
        TKeyEvent key;
        key.iCode=EKeyOK;
        key.iModifiers=0;
        if(handler->FocusedControl()->OfferKeyEventL(key, EEventKey) == EKeyWasNotConsumed)
            {
            return EFalse;
            }
        else
            {
            return handler->ExitWithKey(key.iCode);
            }
        }

    return(ETrue);
    }

EXPORT_C void CAknCharMapDialog::PreLayoutDynInitL()
    {
    CAknCharMap* charmapControl = STATIC_CAST(CAknCharMap*, Control(EAknSCTQueryContentId));

    // Softkeys
    ButtonGroupContainer().MakeVisible(AknLayoutUtils::PenEnabled() ? EFalse : ETrue);

    // Heading
    CAknPopupHeadingPane* headingPane = STATIC_CAST(CAknPopupHeadingPane*, Control(EAknSCTQueryHeadingId));
    headingPane->SetLayout(CAknPopupHeadingPane::EColourSelectionGridHeadingPane);
    charmapControl->SetTitleL(headingPane->PromptText());
    SetLineNonFocusing(EAknSCTQueryHeadingId);
    CEikCaptionedControl *ctrl = GetLineByLineAndPageIndex(0, EAknSCTQueryHeadingId);
    ctrl->SetLatent(AknLayoutUtils::PenEnabled() ? ETrue : EFalse);
    ctrl->SetLatentGroupLineFollows(AknLayoutUtils::PenEnabled() ? ETrue : EFalse);

    // Pictographs
    charmapControl->SetPictoMode(iExtension->iPictoMode);

    // Emotion
    charmapControl->SetEmotionModeL(iExtension->iEmotionMode);

    // ShowAnotherTable
    RArray<TInt> caseTable(3);
    if (iExtension->iShowAnotherTableCharCase > 0)
        {
        caseTable.AppendL(iExtension->iShowAnotherTableCharCase);
        }
    charmapControl->SetCaseTableL(caseTable);
    caseTable.Close();

    // 
    charmapControl->SetBuffer(*iSpecialChars);
    charmapControl->SetCharacterCaseL(iCharCase);

    if (!AknLayoutUtils::PenEnabled())
        {
        if (charmapControl->PageCount() > 1)
            {
            const TDesC* title = charmapControl->IsJapaneseSctUi()?
                                 charmapControl->TitleWithSelectingSpecialChar() : 
                                 charmapControl->Title();
            headingPane->SetPageL(1, charmapControl->PageCount());
            headingPane->SetTextL(*title);
            // Set softkeys
            SetSoftKeyL();
            }
        }
    else
        {
        charmapControl->UpdateInputFieldL();
        }
    
    // Key events should be received even when cba is invisible
    MEikButtonGroup* cba = ButtonGroupContainer().ButtonGroup();
    STATIC_CAST( CEikCba*, cba)->SetButtonGroupFlags( cba->ButtonGroupFlags() | EAknCBAFlagRespondWhenInvisible );
    
    RWsSession& wsSession = iEikonEnv->WsSession();
    TInt myWgId = iEikonEnv->RootWin().Identifier();
    TInt wgPrio = wsSession.GetWindowGroupOrdinalPriority(myWgId);
    // we are already on forgeround, need to update priority differently
    if (wgPrio == ECoeWinPriorityAlwaysAtFront)
        {
        iEikonEnv->RootWin().SetOrdinalPosition(0,ECoeWinPriorityAlwaysAtFront+1);
        }

	/// -- Change Window Priority for dialog and CBA 
	
	DrawableWindow()->SetOrdinalPosition(0,ECoeWinPriorityAlwaysAtFront); //
	ButtonGroupContainer().ButtonGroup()->AsControl()->DrawableWindow()->SetOrdinalPosition(0,ECoeWinPriorityAlwaysAtFront); 	

    }

EXPORT_C void CAknCharMapDialog::SetSizeAndPosition( const TSize& aSize )
    {
    if ( AknLayoutUtils::PenEnabled() )
        {
        CAknDialog::SetSizeAndPosition( aSize );
        CAknCharMap* charmapControl = STATIC_CAST(CAknCharMap*,
                Control(EAknSCTQueryContentId));
        charmapControl->DrawOffscreenBackgroundIfRequired();      
        }
    else
        {
        SetBorder( TGulBorder::ENone ); // No Dialog borders in SCT.
        DoLayout();
        }

    }

EXPORT_C TKeyResponse CAknCharMapDialog::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aModifiers)
    {
    CAknCharMap* charmapControl = STATIC_CAST(CAknCharMap*, Control(EAknSCTQueryContentId));
    CAknPopupHeadingPane* headingPane = STATIC_CAST(CAknPopupHeadingPane*, Control(EAknSCTQueryHeadingId));
    TBool isLockNumericKeys = (iExtension->iFlags&ECharMapDialogItemLockNumericKeys != EFalse);

    if (aModifiers == EEventKey)
        {
        switch (aKeyEvent.iCode)
            {
            case '5':
                if (isLockNumericKeys || aKeyEvent.iRepeats)
                    {
                    return EKeyWasConsumed;
                    }
				break;
            case EKeySpace:     // for Qwerty
                // If there is only one empty position left in the buffer.
                if (iSpecialChars->Length() + 1 >= iSpecialChars->MaxLength())
                    {
                    // Add the selected character to list of special chars
                    charmapControl->OfferKeyEventL(aKeyEvent, aModifiers);
                    TKeyEvent event = {EKeyOK, EKeyOK, 0, 0};
                    return CEikDialog::OfferKeyEventL( event, EEventKey );
                    }
                // No break. Fall through.
            case '2':
            case '4':
            case '6':
            case '8':
                if (isLockNumericKeys && aKeyEvent.iCode!=EKeySpace)
                    {
                    return EKeyWasConsumed;
                    }
            case EKeyLeftArrow:
            case EKeyRightArrow:
            case EKeyUpArrow:
            case EKeyDownArrow:
                {
                TKeyResponse res = charmapControl->OfferKeyEventL(aKeyEvent, aModifiers);
                RefreshTitleAndNavi();
                return res;
                }

            case EKeyEnter:
            case EKeyDevice3:
                {
                TryExitL(EAknSoftkeySelect);
                return EKeyWasConsumed;
                }
                break;
                    
            case '*':
                {
                if (!aKeyEvent.iRepeats) // switch another table when repeat count is 0 only.
                    {
                    if(iExtension->iHaveReceivedKeyEvent)
                        {
                        SwitchTablesOrPagesL();
                        }
                    else
                        {
                        iExtension->iHaveReceivedKeyEvent = ETrue;
                        }
                    }
                }
                break;

            default:
                break;
            }
        }
    else if (aModifiers == EEventKeyUp)
        {
        switch (aKeyEvent.iScanCode)
            {
            case EStdKeyLeftFunc:
            case EStdKeyRightFunc:
                {
                if (!aKeyEvent.iRepeats) // switch another table when repeat count is 0 only.
                    {
                    if (!isLockNumericKeys) // Check whether current input mode is Qwerty.
                        {
                        SwitchTablesOrPagesL();
                        }
                    }
                }
                break;
            default:
                break;
            }
        }
    
    return CEikDialog::OfferKeyEventL( aKeyEvent, aModifiers );
    }

EXPORT_C TInt CAknCharMapDialog::ExecuteLD(TInt aResourceId)
    {
    iWsBufferRequestId = iAvkonEnv->RequestWsBuffer( KWsBufferSize );

    // Prepare real char map
    CEikDialog::PrepareLC(aResourceId);


    // Build up input language spesific avkon resource file
    TBuf<32> fileName(KResFileName);

    TInt langcode= iAvkonEnv->SettingCache().InputLanguage();
    // get the phone language
    TLanguage phoneLanguage = AknLangUtils::UserLanguage();

    if ( (langcode & KAknLanguageMask) == ELangEnglish && phoneLanguage != ELangEnglish  )
        {
        switch ( phoneLanguage )
        	{
        	case ELangThai:
        		langcode = ELangEnglish_Thailand;
        		break;
        			
        	default:
        		break;
        	}
        }
    
    if (langcode < 10)
        {
        fileName.Append('0');
        }
    if(langcode == KLangHindiPhonetic)
        langcode = ELangHindi;
    fileName.AppendNum(langcode);

    TResourceReader reader;

    RFs& fs = iEikonEnv->FsSession();

    // if input language spesific avkon resourcefile exists
    if ( BaflUtils::FileExists(fs, fileName) )
        {
        RResourceFile resourceFile;
        resourceFile.OpenL( fs, fileName );
        CleanupClosePushL( resourceFile ); // push
        resourceFile.ConfirmSignatureL( 0 );

        // if resources with correct id exists
        // -> read characters from resource and copy them to real char map
        if ( resourceFile.OwnsResourceId(aResourceId) )
            {
            HBufC8* resource=resourceFile.AllocReadLC(aResourceId); // push
            reader.SetBuffer(resource);

            // Create input language specific CharMapDialog.
            // Used only for reading input language spesific characters
            // from avkon resource file (avkon.r**).
            TBuf<32> specialChars;
            CAknCharMapDialog* langDialog = new( ELeave ) CAknCharMapDialog(EAknSCTLowerCase, specialChars );
            CleanupStack::PushL( langDialog ); // push

            langDialog->CreateWindowL();
            langDialog->ConstructFromResourceL(reader);

            CAknCharMap* langMap = STATIC_CAST( CAknCharMap*, langDialog->Control( EAknSCTQueryContentId ) );
            CAknCharMap* charMap = STATIC_CAST( CAknCharMap*, Control( EAknSCTQueryContentId ) );
            charMap->CopyCharactersL( *langMap );

            CleanupStack::PopAndDestroy(2); // langDialog, resource

            }

        CleanupStack::PopAndDestroy(); // resourcefile
        }
    
    // get created charmap control
    CAknCharMap* charmapControl = STATIC_CAST(CAknCharMap*, Control(EAknSCTQueryContentId));

    if (iCharSetResourceId)
        {
        TResourceReader reader;
        iCoeEnv->CreateResourceReaderLC(reader, iCharSetResourceId);
        charmapControl->ReadAndAddCharSetFromResourceL(reader);
        CleanupStack::PopAndDestroy(); // reader
        }

    charmapControl->SetObserver(this);

    if ( iExtension && (iExtension->iFlags & ECharMapDialogRecentCharsRowDisabled) )
        {
        charmapControl->DisableRecentCharsRow();
        }
    
    return(RunLD());
    }

EXPORT_C void CAknCharMapDialog::CEikDialog_Reserved_1()
    {
    }

EXPORT_C void CAknCharMapDialog::CEikDialog_Reserved_2()
    {
    }

EXPORT_C void CAknCharMapDialog::CAknCharMapDialog_Reserved()
    {
    }

EXPORT_C void CAknCharMapDialog::ShowNoPictographs()
    {
    iExtension->iPictoMode = EAknCharMapPictoNoUse;
    }

EXPORT_C void CAknCharMapDialog::ShowPictographsFirst()
    {
    iExtension->iPictoMode = EAknCharMapPictoFirst;
    }

EXPORT_C void CAknCharMapDialog::SetEmotionMode(TAknCharMapEmotionMode aEmotionMode)
    {
    iExtension->iEmotionMode = aEmotionMode;
    }

EXPORT_C void CAknCharMapDialog::ShowAnotherTable(TInt aCharCase)
    {
    iExtension->iShowAnotherTableCharCase = aCharCase;
    }

void CAknCharMapDialog::DoLayout()
    {
    TAknLayoutRect dialogLayRect;

    CAknCharMap* charmapControl = STATIC_CAST(CAknCharMap*, Control(EAknSCTQueryContentId));

    // Number of character rows in the special char table.
    TInt rows = charmapControl->HeightInRows();

    if (!AknLayoutUtils::PenEnabled())
        {
        // Main pane without softkeys
        TRect mainPaneRect;
        if(!AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EPopupParent, mainPaneRect))
            {
            mainPaneRect = iAvkonAppUi->ClientRect();
            }

        // Dialog layout, check variety first
        TAknLayoutScalableParameterLimits charMapDialogVariety =
            AknLayoutScalable_Avkon::popup_grid_graphic_window_ParamLimits();

        TInt maxVariety = charMapDialogVariety.LastVariety();

        // Check the CBA, if the orientation is not landscape
        // there is not so much varieties
        AknLayoutUtils::TAknCbaLocation location = AknLayoutUtils::CbaLocation();
        TInt maxVarietyOffset = 0; // the offset for the certain cba location variety
        TInt varietyOffset = maxVariety + 1;

        // landscape variety number must be calculated offset == number of varieties
        // same applies to the variety number for the biggest sized layout for the variety
        if(Layout_Meta_Data::IsLandscapeOrientation())
            {
            varietyOffset = (maxVariety + 1)/KAknSctCBaButtonDirections; // the offset for one variety
            }

        // for right and left cba buttons the max variety is not zero
        // the varities are ordered by the location of the cba and the descending order
        // e.g the biggest sized layout first, the smallest last
        if(location == AknLayoutUtils::EAknCbaLocationRight)
            {
            maxVarietyOffset = varietyOffset;
            }
        else if(location == AknLayoutUtils::EAknCbaLocationLeft)
            {
            maxVarietyOffset = varietyOffset + varietyOffset; // 2*
            }

        TInt varietyNumber = varietyOffset - rows;

        // if more lines than possible to show, use the default
        // (the biggest grid) variety
        if(varietyNumber < 0)
            varietyNumber = 0;
        // if zero rows, use the minimum
        else if(rows<=0)
            varietyNumber -= 1;

        //add the varietyoffset
        varietyNumber += maxVarietyOffset;

        // Layout the dialog size
        dialogLayRect.LayoutRect( mainPaneRect,AknLayoutScalable_Avkon::popup_grid_graphic_window(varietyNumber));
        }
    else
        {
        dialogLayRect.LayoutRect(iAvkonAppUi->ApplicationRect(), AknLayoutScalable_Avkon::popup_grid_graphic2_window(0));
        }
    // Set the retangle for dialog and eventually to CAknCharMap
    SetRect(dialogLayRect.Rect());

    // Need to update popup heading's skin IDs to zero to draw background

    // Offscreen background for picto table.
    charmapControl->DrawOffscreenBackgroundIfRequired();
    }

// -----------------------------------------------------------------------------
// CAknCharMapDialog::HandleControlEventL()
//
// Handles control events from char map table.
// -----------------------------------------------------------------------------
//

EXPORT_C void CAknCharMapDialog::HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType)
    {
    // get charmap control
    CAknCharMap* charmapControl = STATIC_CAST(CAknCharMap*, Control(EAknSCTQueryContentId));

    if ( charmapControl)
        {
        CAknPopupHeadingPane* headingPane = static_cast< CAknPopupHeadingPane* >( Control( EAknSCTQueryHeadingId ) );
        if (headingPane)
            {
            TRAP_IGNORE(
                {
                headingPane->SetPageL(charmapControl->CurrentPage(),charmapControl->PageCount() );
                } );
            }
        if (AknLayoutUtils::PenEnabled())
            {
            TRAP_IGNORE(charmapControl->RefreshNaviPageL());
            }
        }
    if ( iExtension && (aControl == charmapControl) && (aEventType == EEventStateChanged) )
        {
        TInt status = charmapControl->StatusChanged();
        if (status == EAknCharSelectedSpecialCharacter)
            {
            // Something has been selected from CharMap
            iExtension->iFlags |= ECharMapDialogItemSelected;
            }
        else if (status == EAknCharChangedCategory)
            {
            TInt curCategory = charmapControl->CurrentCategory();
            ChangeCategoryL(curCategory);
            }
        else if (status == EAknCharSelectedNextTableButton)
            {
            SwitchTablesL();
            }
        else if (status == EAknCharSelectedTableExitButton)
            {
            TryExitL(EAknSoftkeyExit);
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknCharMapDialog::HandleDialogPageEventL()
//
// Handles closing Charmap dialog after selection has been done with stylus.
// -----------------------------------------------------------------------------
//

EXPORT_C void CAknCharMapDialog::HandleDialogPageEventL(TInt aEventID)
    {
    if ( iExtension && aEventID == MEikDialogPageObserver::EDialogPageTapped )
        {
        if (iExtension->iFlags & ECharMapDialogItemSelected )
            {
            iExtension->iFlags = 0;
            TryExitL(EAknSoftkeyOk);
            }
        else if (iExtension->iFlags == ECharMapDialogTableExitSelected)
            {
            iExtension->iFlags = 0;
            TryExitL(EAknSoftkeyExit);
            }
        }
    }

EXPORT_C void CAknCharMapDialog::LockNumericKeys(TBool aLockStatus)
    {
    if (aLockStatus)
        {
        iExtension->iFlags |= ECharMapDialogItemLockNumericKeys;
        }
    else
        {
        iExtension->iFlags &= (~ECharMapDialogItemLockNumericKeys);
        }
    }

EXPORT_C void CAknCharMapDialog::DisableRecentCharsRow()
    {
    iExtension->iFlags |= ECharMapDialogRecentCharsRowDisabled;
    }

// -----------------------------------------------------------------------------
// CAknCharMapDialog::HandlePointerEventL()
//
// Handles pointer events
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknCharMapDialog::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    if (!Rect().Contains( aPointerEvent.iPosition))
        {
        if(aPointerEvent.iType == TPointerEvent::EButton1Down)
            {
            TryExitL (EAknSoftkeyCancel);
            return;
            }
         else if(aPointerEvent.iType == TPointerEvent::EButton1Up)
            {
            CAknCharMap* charMap = STATIC_CAST( CAknCharMap*, Control( EAknSCTQueryContentId ) );
            charMap->HandlePointerEventL( aPointerEvent);
            }
        }
    else
        {
        CAknDialog::HandlePointerEventL(aPointerEvent);
        }
    }

void CAknCharMapDialog::SwitchTablesOrPagesL()
    {
    if(!SwitchTablesL())
        {
        SwitchPagesL();
        }
    }

TBool CAknCharMapDialog::SwitchTablesL()
    {
    CAknCharMap* charmapControl = STATIC_CAST(CAknCharMap*, Control(EAknSCTQueryContentId));
    CAknPopupHeadingPane* headingPane = STATIC_CAST(CAknPopupHeadingPane*, Control(EAknSCTQueryHeadingId));

    TBool layoutChanged;
    if (charmapControl->SwitchTablesL(layoutChanged))
        {
        ChangeLayoutL(layoutChanged);
        SetSoftKeyL(ETrue);
        return TRUE;
        }
    else
        {
        return FALSE;
        }
    }

void CAknCharMapDialog::SwitchPagesL()
    {
    CAknCharMap* charmapControl = STATIC_CAST(CAknCharMap*, Control(EAknSCTQueryContentId));
    CAknPopupHeadingPane* headingPane = STATIC_CAST(CAknPopupHeadingPane*, Control(EAknSCTQueryHeadingId));
    
    charmapControl->NextPageL();
    RefreshTitleAndNavi();
    }

void CAknCharMapDialog::RefreshTitleAndNavi()
    {
    CAknCharMap* charmapControl = STATIC_CAST(CAknCharMap*, Control(EAknSCTQueryContentId));
    CAknPopupHeadingPane* headingPane = STATIC_CAST(CAknPopupHeadingPane*, Control(EAknSCTQueryHeadingId));
    
    if (!AknLayoutUtils::PenEnabled())
        {
        const TDesC* title = charmapControl->Title();
        headingPane->SetPageL(charmapControl->CurrentPage());
        if (title != charmapControl->Title())
            {
            const TDesC* title = charmapControl->IsJapaneseSctUi() ? 
                                 charmapControl->TitleWithSelectingSpecialChar() : 
                                 charmapControl->Title();
            headingPane->SetTextL(*title);
            }
        }
    else
        {
        charmapControl->RefreshNaviPageL();
        }
    }

void CAknCharMapDialog::ChangeCategoryL(const TInt aCategory)
    {
    TBool layoutChanged;
    CAknCharMap* charmapControl =
        STATIC_CAST(CAknCharMap*, Control(EAknSCTQueryContentId));

    if (charmapControl->ChangeCategoryL( aCategory, layoutChanged ))
        {
        ChangeLayoutL(layoutChanged);
        SetSoftKeyL(ETrue);
        }
    }

void CAknCharMapDialog::ChangeLayoutL(const TBool aLayoutChanged)
    {
    CAknCharMap* charmapControl =
        STATIC_CAST(CAknCharMap*, Control(EAknSCTQueryContentId));
    CAknPopupHeadingPane* headingPane =
        STATIC_CAST(CAknPopupHeadingPane*, Control(EAknSCTQueryHeadingId));
    const TDesC* title = (charmapControl->IsJapaneseSctUi())?
                            charmapControl->TitleWithSelectingSpecialChar()
                            : charmapControl->Title();
    if ( aLayoutChanged )
        {
        // This prevents the ugly graphics anomalies while the window
        // is resized and repositioned.
        Window().SetVisible( EFalse );
        if (!AknLayoutUtils::PenEnabled())
            {
            headingPane->SetTextL(*title);
            headingPane->SetPageL(1, charmapControl->PageCount());
            }
        DoLayout();
        DrawNow();
        Window().SetVisible( ETrue );
        }

    // If the layout is the same, do not set layout again
    // as this causes flicker.
    else
        {
         if (!AknLayoutUtils::PenEnabled())
            {
            headingPane->SetTextL(*title);
            headingPane->SetPageL(1, charmapControl->PageCount());
            }
        else
            {
            charmapControl->RefreshNaviPageL();
            }
        // Offscreen background for picto table.
        charmapControl->DrawOffscreenBackgroundIfRequired();
        DrawNow();
        }
    }

void CAknCharMapDialog::SetSoftKeyL(const TBool aDrawNow /*= EFalse*/)
    {
    CAknCharMap* charmapControl =
        STATIC_CAST(CAknCharMap*, Control(EAknSCTQueryContentId));
    CEikButtonGroupContainer& cba = ButtonGroupContainer();
    TInt labelId(R_AVKON_SOFTKEY_SELECT_TEXT);
    TInt id(EAknSoftkeySelect);
    if (charmapControl->PageCount() > 1)
        {
        labelId = R_AVKON_SOFTKEY_NEXT_TEXT;
        id = EAknSoftkeyNext;
        }
    HBufC* label = StringLoader::LoadL(labelId, iCoeEnv);
    CleanupStack::PushL(label);
    cba.SetCommandL(0, id, label->Des());
    CleanupStack::PopAndDestroy(label); // label

    // In Japanese UI, right softkey is "Back".
    if (charmapControl->IsJapaneseSctUi())
        {
        label = StringLoader::LoadL(R_AVKON_SOFTKEY_JAPAN_SCT_BACK, iCoeEnv);
        CleanupStack::PushL(label);
        cba.SetCommandL(2, EAknSoftkeyClose, label->Des());
        CleanupStack::PopAndDestroy(label); // label
        }

    // Since MSK is enable from the branch of 3.1, set MSK as Select Key
    if (charmapControl->PageCount() > 1 && AknLayoutUtils::MSKEnabled())
        {
        label = StringLoader::LoadL(R_QTN_MSK_SELECT, iCoeEnv);
        CleanupStack::PushL(label);
        cba.SetCommandL(3, EAknSoftkeySelect,label->Des());
        CleanupStack::PopAndDestroy(label); // label
        }

    // Drawing
    if (aDrawNow)
        {
        cba.DrawNow();
        }
    }


//  End of File
