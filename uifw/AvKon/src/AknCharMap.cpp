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
* Description: Special character table.
*
*/


// INCLUDE FILES
#include <txtetext.h>
#include <barsread.h>
#include <eikappui.h>
#include <eikenv.h>
#include <aknenv.h>
#include <eiksbfrm.h>
#include <eikscrlb.h>
#include <eikdialogext.h>
#include <bidivisual.h>
#include <avkon.rsg>
#include "AknPanic.h"
#include "avkon.hrh"
#include "AknUtils.h"
#include <aknlayoutscalable_avkon.cdl.h>
#include <layoutmetadata.cdl.h>
#include <AknLayout.lag>
#include "aknCharMap.h"
#include "aknappui.h"
#include "aknconsts.h"
#include "AknDef.h"
#include <PUAcodes.hrh>
#include <s32file.h>
#include <AknPanic.h>
#include "aknSctDialog.h" // CAknCharmapDialog
#include <aknPopupHeadingPane.h>
//#include <aknfep.rsg>
#include <bautils.h>
#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikenvinterface.h>
#endif

#include <AknTasHook.h>
// For the TEikScrollBarModelType
#include <eikscrlb.h>

#include <AknsDrawUtils.h>
#include <AknPictographInterface.h>
#include <featmgr.h>
#include <StringLoader.h>

#include <AvkonInternalCRKeys.h>    // KCRUidAvkon, KAknRecentSctData
#include <centralrepository.h>      // CRepository
#include <AknsFrameBackgroundControlContext.h>

#include <aknbutton.h>
#include <gdi.h>
#include <eikedwin.h>
#include <gulbordr.h>
#include <touchfeedback.h>
#include <eiklabel.h>
#include <aknphysics.h>

#include "PictograhGrouping.h"
#include "AknSettingCache.h"
#include "aknsctfocushandler.h"

#include "AknSmileyModel.h"

_LIT(KResFileName, "z:\\resource\\avkon.r");

const TInt KAknSctCBaButtonDirections = 3; // bottom, right and left

const TUint KThaiSCTCombiningSymbolAdd = 0xE900;

enum
    {
    EAknCharMapButton1DownInGrid = 0x00000001,
    EAknCharMapHasBeenScrolledByDrag = 0x00000002,
    EAknCharMapCharsAllocated = 0x00000004, // flag that iChars points to HBufC
    EAknCharMapPressedDown = 0x00000008   // flag for press down effect
    };


const TUint KHistoryEmptyChar = CEditableText::ETabCharacter;
const TUint KHistoryEmptyCharForDisplay = CEditableText::ESpace;

const TInt KAknSctRadioOn = 1;
const TInt KAknSctRadioOff = 0;
const TInt KAreaIdRecent = 0;
const TInt KAreaIdMain   = 1;
const TInt KAreaIdTail   = 2;


// ----------------------------------------------------------------------------
// TEmotionUtils definition
// ----------------------------------------------------------------------------
//

const TUint KEmotionCharBase = 0xf880;

class TEmotionUtils
    {
public:
    static TBool IsEmotionChar(TChar aChar);
    static TChar EmotionChar(TInt aId);
    static TInt EmotionId(TChar aChar);
    static TChar EmotionSwitchToSmileyChar();
    static TChar EmotionSwitchToSctChar();
    };

TBool TEmotionUtils::IsEmotionChar(TChar aChar)
    {
    return (aChar >= KEmotionCharBase);
    }

TChar TEmotionUtils::EmotionChar(TInt aId)
    {
    return (KEmotionCharBase + aId);
    }

TInt TEmotionUtils::EmotionId(TChar aChar)
    {
    return (TInt)(aChar - KEmotionCharBase);
    }

TChar TEmotionUtils::EmotionSwitchToSmileyChar()
    {
    return KEmotionCharBase + CSmileyModel::EIconSwitchToSmiley;
    }

TChar TEmotionUtils::EmotionSwitchToSctChar()
    {
    return KEmotionCharBase + CSmileyModel::EIconSwitchToSct;
    }


// ----------------------------------------------------------------------------
// CAknCharMapHistory definition
// ----------------------------------------------------------------------------
//
/**
 *  Recent data management when a Special characters or a Pictograph characters 
 *  @lib avkon.lib
 *  @since 2.8
 *
 */
class CAknCharMapHistory : public CBase
    {
    public: // Constructors and destructor
        /**
        * Two-phased constructor.
        */
        static CAknCharMapHistory* NewL();

        /**
        * Destructor.
        */
        ~CAknCharMapHistory();

    public: // enum
        enum THistoryType
            {
            EHistoryTypeNull = -1,
            EHistoryTypeFull = 0,
            EHistoryTypeHalf,
            EHistoryTypePicto,
            EHistoryTypePicto2,
            EHistoryTypeMax
            };
        
        enum THistoryFilter
            {
            EHistoryFilterMixed = 0, // text and emotion
            EHistoryFilterTextOnly,
            EHistoryFilterEmotionOnly,
            EHistoryFilterMax
            };
        
        enum THistorySize
            {
            KHistoryBufferSize = 15
            };

    public: // New functions
        /**
        * Load recent characters from file.
        * @since 2.8
        */
        TInt LoadL();
        /**
        * Reset recent data arrary.
        * @since 2.8
        */
        void ResetArray();
        /**
        * Store recent data to file.
        * @since 2.8
        */
        TInt SaveL();
        /**
        * Get recent data.
        * @since 2.8
        * @param aHistoryType The kind of charctor map, refer to THistoryType
        */
        const TDesC& RecentString(THistoryType aHistoryType, THistoryFilter aHistoryFilter=EHistoryFilterMixed);
        /**
        * Insert a character which select on SCT/Picto.
        * @since 2.8
        * @param aHistoryType The kind of charctor map, refer to THistoryType
        * @param aChar    Insert a character
        */
        void InsertChar(THistoryType aHistoryType, const TChar aChar);

    private:
        /**
        * C++ default constructor.
        * @since 2.8
        */
        CAknCharMapHistory();

        /**
        * By default Symbian 2nd phase constructor is private.
        * @since 2.8
        */
        void ConstructL();
        
    private:
        /**
        * Insert a character to a HBufC.
        * @param aHistoryBuf ahistory buffer
        * @param aChar    Insert a character
        */
        void InsertCharToHistoryBuf(TDes& aHistoryBuf, const TChar aChar);

    private:    // Data
        // Recent characters
        TBuf<KHistoryBufferSize> iMixedHistoryArray[EHistoryTypeMax];
        TBuf<KHistoryBufferSize> iTextHistoryArray[EHistoryTypeMax];
        TBuf<KHistoryBufferSize> iEmotionHistory;
        
        enum TBufferCount
            {
            KHistoryBufferCount = (EHistoryTypeMax+EHistoryTypeMax+1)
            };
    };


// ----------------------------------------------------------------------------
// Navi button class definition
// ----------------------------------------------------------------------------
//
NONSHARABLE_CLASS(CAknSctNaviButton) : public CBase
    {
    public:
        static CAknSctNaviButton* NewL(
            const CCoeControl& aParent,
            TInt aButtonId,
            TResourceReader& reader);
        ~CAknSctNaviButton();

    private:
        CAknSctNaviButton(TInt aButtonId);
        void ConstructL(
            const CCoeControl& aParent,
            TResourceReader& reader);

    public:
        void SetFocused(TBool aState);
        void SetEnabled(TBool aState);
        TBool IsFocused();
        TBool IsEnabled();

    public:
        CAknButton* iButtonControl;
        TInt iButtonId;
        TBool iPressed;
        TBool iRepeat;
    };

// ----------------------------------------------------------------------------
// Table Navi class definition
// ----------------------------------------------------------------------------
//
NONSHARABLE_CLASS(CAknSctTableNavi) : public CAknControl, public MAknSctFocusHandler
    {
    public:
        CAknSctTableNavi(CAknCharMap* aCharMap, CAknCharMapExtension* aExtension);
        ~CAknSctTableNavi();

    public:  // from CCoeControl
        TInt CountComponentControls() const;
        CCoeControl* ComponentControl( TInt aIndex ) const;
        virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode);
        void ConstructFromResourceL(TResourceReader& aReader);
        virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
        virtual TSize MinimumSize();
        virtual void SizeChanged();

    public: // from MAknSctFocusHandler
        virtual CCoeControl* FocusedControl();
        virtual TBool EnterControl(TInt aX, TInt aY);
        virtual void MoveFocus(TInt aX, TInt aY);
        virtual TBool ExitWithKey(TInt aKeycode);
        virtual TBool LeaveControl();

    public:
        TInt TableCount();
        void TableExitL();
        static TInt DoTableExit(TAny* aThis);
        void UpdateNextTableButtonL();

    private:
        TInt ButtonPosition(TInt aButtonIndex) const;
        TInt SetStatusChanged();
        void NextTableL();

    private:  // data
        TInt iButtonIndex;
        RPointerArray<CAknSctNaviButton> iButtonArray;
        CAknCharMap* iCharMap;
        CAknCharMapExtension* iExtension;
        CIdle *iIdle;
        
        TInt iPressedButtonIndex;
    };

// ----------------------------------------------------------------------------
// Navigator class definition
// ----------------------------------------------------------------------------
//
NONSHARABLE_CLASS(CAknSctPageNavi) : public CAknControl, public MAknSctFocusHandler, public MCoeControlObserver
    {
    public:
        CAknSctPageNavi( CAknCharMap* aCharMap, CAknCharMapExtension* aExtension);
        ~CAknSctPageNavi();

    public: // new methods
       void UpdatePageTitleL() const;

    public:  // from CCoeControl
        TInt CountComponentControls() const;
        CCoeControl* ComponentControl( TInt aIndex ) const;
        virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode);
        void ConstructFromResourceL(TResourceReader& aReader);
        virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
        virtual TSize MinimumSize();
        virtual void SizeChanged();
        virtual void Draw(const TRect& aRect) const;

    public: // from MCoeControlObserver
        void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType); // for button repeat

    public:  // from MAknSctFocusHandler
        virtual CCoeControl* FocusedControl();
        virtual TBool EnterControl(TInt aX, TInt aY);
        virtual void MoveFocus(TInt aX, TInt aY);
        virtual TBool ExitWithKey(TInt aKeycode);
        virtual TBool LeaveControl();

    private:
        TBool IsNextButton() const;

    private:  // data
        TInt iButtonIndex;
        RPointerArray<CAknSctNaviButton> iButtonArray;
        CAknCharMap* iCharMap;
        CAknCharMapExtension* iExtension;
        CEikLabel* iTitle;
    };

// ----------------------------------------------------------------------------
// Category button class defintion
// ----------------------------------------------------------------------------
//
class CAknSctCategoryButton : public CBase
    {
    public:
        static CAknSctCategoryButton* NewL(
            const CCoeControl& aParent,
            TResourceReader& reader,
            TInt aCategoryButtonId,
            TInt aSctCaseId);
        ~CAknSctCategoryButton();
    private:
        CAknSctCategoryButton(
            TInt aCategoryButtonId,
            TInt aSctCaseId);
        void ConstructL(
            const CCoeControl& aParent,
            TResourceReader& reader);

    public:
        void SetFocused(TBool aState);

    public:
        CAknButton* iButtonControl;     // own
        TInt        iButtonId;
        TInt        iSctCaseId;
        TBool       iValid;
    };

// ----------------------------------------------------------------------------
// Radio button class defintion
// ----------------------------------------------------------------------------
//
class CAknSctRadioButton : public CAknControl, public MAknSctFocusHandler
    {
    public:
        enum TAknSctRadioButtonFlags
            {
            EAknSctRadioButtonResize = 0x1,
            EAknSctRadioButtonEnd
            };
    public:
        CAknSctRadioButton();
        CAknSctRadioButton(CAknCharMap* aCharMap,
                           CAknCharMapExtension* aExtension);
        ~CAknSctRadioButton();
    public: // from MAknSctFocusHandler
        virtual CCoeControl* FocusedControl();
        virtual TBool EnterControl(TInt aX, TInt aY);
        virtual void MoveFocus(TInt aX, TInt aY);
        virtual TBool ExitWithKey(TInt aKeycode);
        virtual TBool LeaveControl();

    public:  // from CCoeControl
        TInt CountComponentControls() const;
        CCoeControl* ComponentControl( TInt aIndex ) const;
        virtual TKeyResponse OfferKeyEventL(
            const TKeyEvent& aKeyEvent, TEventCode);
        void ConstructFromResourceL(TResourceReader& aReader);

        /**
         * This function handles pointer events directed at the charmapdialog.
         * @param aPointerEvent The pointer event directed at the charmapdialog.
         */
        virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);

        virtual TSize MinimumSize();
        virtual void SizeChanged();
        virtual void Draw(const TRect& aRect) const;

    public:  // New function
        // The number of Buttons
        inline TInt Count() const;

        void SetCurrentCategory(TInt aCategory);
        void SetValidSctCase(TInt aSctCase);
        void RemoveInvalidButton();

    private:  // data
        RPointerArray<CAknSctCategoryButton> iButtonArray;
        MCoeControlObserver* iObserver;
        TInt iFlags;
        CAknCharMapExtension* iExtension;
        CAknCharMap* iCharMap;
        TInt iButtonIndex;
        TInt iEntryIndex;
    };
// end of CAknSctRadioButton class definition

// ----------------------------------------------------------------------------
// Extension class defintion
// ----------------------------------------------------------------------------
//
NONSHARABLE_CLASS(CAknCharMapExtension) : 
    public CBase,
    public MObjectProvider,
    public MAknSctFocusHandler,
    public MSmileyIconObserver
    {
    public:
        CAknCharMapExtension();
        ~CAknCharMapExtension();

    public: // new methods
        void SetCharMapControl(CAknCharMap* aCtrl);
        MAknSctFocusHandler* FocusHandler();

    public: // from MAknSctFocusHandler
        virtual CCoeControl* FocusedControl();
        virtual TBool EnterControl(TInt aX, TInt aY);
        virtual void MoveFocus(TInt aX, TInt aY);
        virtual TBool ExitWithKey(TInt aKeycode);
        virtual TBool LeaveControl();

    protected:
        TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
        MObjectProvider* MopNext();
        
    private: // from MSmileyIconObserver
        virtual void ThumbnailLoaded(CSmileyIcon* aSmileyIcon);
        virtual void AnimationChanged(CSmileyIcon* aSmileyIcon);
        
    public:
        TBool IsEmotionEnabled() const;
        TBool IsShowingEmotion() const;
        TBool NeedEmotionSwitchIcon() const;
        HBufC* ReadEmotionHBufCL();
        void LoadEmotionTumbnails(const TDesC& aSctChars);
        void SetEmotionSize(const TSize& aSize);

        CSmileyIcon* EmotionIcon(TChar aEmotionChar);
        TBool DrawEmotion(CWindowGc& aGc, const TRect& aRect, TChar aEmotionChar);
        void HandleFocusStatusChanged(TChar aChar, TBool aIsFocused);

    public: // data
        MCoeControlObserver *iObserver;
        HBufC* iCharsQwerty;
        HBufC* iTitleBuf;

        TUint iFlags;
        TInt iMaxVisibleRows;
        CAknsFrameBackgroundControlContext* iBgContext;
        MObjectProvider* iCharMap;
        TBool iMenuSct; // Is SCT used in editing menu
        TBool iKeyOkEvent; // ETrue is set after pressing OK Key

        // FeatureManager
        TBool iPictographsBuffer;         // ETrue means Picto is valid.
        TBool iPictographsBufferGrouping; // ETrue means Picto grouping is valid.
        TBool iJapaneseSctUi;       // Title and Softkey for Japanese varinat
        TBool iHasCategoryButtonUi; // Has Category button UI
        CAknSctRadioButton* iRadioButton;
        TInt  iCurrentCategory;     // defined enum TAknSCTCategoryButton on avkon.hrh

        // QHD layout.
        CAknCharMap* iCharMapProxy;
        MAknSctFocusHandler* iFocusHandler;
        CAknSctTableNavi* iTableNavi;
        CAknSctPageNavi* iPageNavi;
        HBufC* iEntryBuf;
        CEikLabel* iCategoryTitle;
        CEikLabel* iCategoryEntry;
        TBool iSelectAllowed;
        
        // Whether or not kinetic scrolling is enabled in the device.
        // Focus scrolling is disabled if kinetic scrolling is used.
        TBool iKineticScrolling;
        // Indicates whether menu sct is highlighted or not.
        TBool iMenuSctHighlighted;
        
    public: // for Emotion
        HBufC* iCharsSmiley;
        CSmileyModel iSmileyModel;
        TChar iLastFocusedSmileyChar;
        TBool iIsShowingEmotion;
        TBool iIsEnableEmotion;

    public: // Single click        
       /**
        * Is single click mode enabled
        */
        TBool iSingleClickEnabled;

       /**
        * Is highlight visible
        */
        TBool iHighlightVisible;         
    };

// ----------------------------------------------------------------------------
// Navi button class implementation
// ----------------------------------------------------------------------------
//
CAknSctNaviButton* CAknSctNaviButton::NewL(const CCoeControl& aParent, TInt aButtonId, TResourceReader& aReader)
    {
    CAknSctNaviButton* self = new( ELeave ) CAknSctNaviButton(aButtonId);
    CleanupStack::PushL( self );
    self->ConstructL(aParent, aReader);
    CleanupStack::Pop();
    return self;
    }

CAknSctNaviButton::CAknSctNaviButton(TInt aButtonId) : iButtonId(aButtonId)
    {
    }

void CAknSctNaviButton::ConstructL(const CCoeControl& aParent, TResourceReader& aReader)
    {
    iButtonControl = CAknButton::NewL(aReader);
    iButtonControl->SetContainerWindowL(aParent);
    }

CAknSctNaviButton::~CAknSctNaviButton()
    {
    delete iButtonControl;
    }

void CAknSctNaviButton::SetFocused(TBool aState)
    {
    iButtonControl->SetFocus(aState);
    iButtonControl->DrawNow();
    }

void CAknSctNaviButton::SetEnabled(TBool aState)
    {
    iButtonControl->MakeVisible(aState);
    }

TBool CAknSctNaviButton::IsFocused()
    {
    return iButtonControl->IsFocused();
    }

TBool CAknSctNaviButton::IsEnabled()
    {
    return iButtonControl->IsVisible();
    }

// ----------------------------------------------------------------------------
// Table navi class implementation
// ----------------------------------------------------------------------------
//
CAknSctTableNavi::CAknSctTableNavi(CAknCharMap* aCharMap, CAknCharMapExtension* aExtension) : 
iCharMap(aCharMap), iExtension(aExtension)
    {
    }

CAknSctTableNavi::~CAknSctTableNavi()
    {
    if (iButtonArray.Count())
        {
        iButtonArray.ResetAndDestroy();
        }
    iButtonArray.Close();
    delete iIdle;
    }

TInt CAknSctTableNavi::CountComponentControls() const
    {
    return iButtonArray.Count();
    }

CCoeControl* CAknSctTableNavi::ComponentControl( TInt aIndex ) const
    {
    CCoeControl* rtn;
    if (aIndex < iButtonArray.Count())
        {
        rtn = iButtonArray[aIndex]->iButtonControl;
        }
    else
        {
        rtn = NULL;
        }
    return rtn;
    }

TKeyResponse CAknSctTableNavi::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aModifiers)
    {
    CAknSctNaviButton* buttonObj = iButtonArray[iButtonIndex];
    buttonObj->iButtonControl->OfferKeyEventL(aKeyEvent,aModifiers);
    TKeyResponse response = EKeyWasNotConsumed;
    TUint code=aKeyEvent.iCode;
    switch (code)
        {
        case EKeyEnter:
        case EKeyOK:
            {
            switch (buttonObj->iButtonId)
                {
                case EAknSctTableNaviExit:
                    {
                    iExtension->iKeyOkEvent = ETrue;
                    TableExitL();
                    response = EKeyWasConsumed;
                    }
                    break;
                // add all supported table types here.
                case EAknSctTableNaviSpecialChar:
                case EAknSctTableNaviEmotion:
                    {
                    NextTableL();
                    response = EKeyWasConsumed;
                    }
                    break;
                default:
                    break;
                }
            }
            break;
        case EKeyLeftArrow:
        case '4':
            {
            MoveFocus(-1,0);
            response = EKeyWasConsumed;
            }
            break;
        case EKeyRightArrow:
        case '6':
            {
            MoveFocus(1,0);
            response = EKeyWasConsumed;
            }
            break;
        case EKeyUpArrow:
        case '2':
            {
            response = EKeyWasConsumed;
            if ((iButtonIndex==0) && !Layout_Meta_Data::IsLandscapeOrientation())
                {
                // Left page button.
                if (iExtension->iPageNavi && iExtension->iPageNavi->EnterControl(0,0))
                    {
                    LeaveControl();
                    }
                }
            else
                {
                // Last radio button.
                if ((iButtonIndex==0) && iExtension->iRadioButton)
                    {
                    if (iExtension->iRadioButton->EnterControl(0,iExtension->iRadioButton->Count()-1))
                        {
                        LeaveControl();
                        }
                    break;
                    }

                // Grid bottom row.
                TInt xPos = ButtonPosition(iButtonIndex);
                if (iCharMap->ColMax(0) > iCharMap->ColMax(xPos))
                    {
                    xPos = iCharMap->RowMax(iCharMap->ColMax(0));
                    }

                if (iExtension->EnterControl(xPos,iCharMap->ColMax(xPos)))
                    {
                    LeaveControl();
                    break;
                    }
                }
            }
            break;
            
        case EKeyDownArrow:
        case '8':
            {
            response = EKeyWasConsumed;
            
            // First radio button.
            if ((iButtonIndex==0) && iExtension->iRadioButton)
                {
                if (iExtension->iRadioButton->EnterControl(0,0))
                    {
                    LeaveControl();
                    }
                break;
                }
            
            // Grid top row.
            TInt xPos = ButtonPosition(iButtonIndex);
            if (iExtension->EnterControl(xPos,iCharMap->ColMin(xPos)))
                {
                LeaveControl();
                break;
                }
            }
            break;
            
        default:
            break;
        }
    return response;
    }

void CAknSctTableNavi::TableExitL()
    {
    delete iIdle;
    iIdle = 0;
    iIdle = CIdle::NewL(CActive::EPriorityIdle);
    iIdle->Start(TCallBack(DoTableExit, this));
    }

TInt CAknSctTableNavi::DoTableExit(TAny* aThis)
    {
    return ((CAknSctTableNavi*)aThis)->SetStatusChanged();
    }

TInt CAknSctTableNavi::ButtonPosition(TInt aButtonIndex) const
    {
    // buttons behind the 1th are behavior as one button
    return (aButtonIndex==0) ? 0 : 1;
    }

TInt CAknSctTableNavi::SetStatusChanged()
    {
    TRAPD(err, iCharMap->SetStatusChanged(EAknCharSelectedTableExitButton));
    return err;
    }

void CAknSctTableNavi::NextTableL()
    {
    iCharMap->SetStatusChanged(EAknCharSelectedNextTableButton);
    }

void CAknSctTableNavi::ConstructFromResourceL(TResourceReader& aReader)
    {
    // Table navi buttons.
    TInt counts = aReader.ReadInt16();
    for (TInt i = 0; i < counts; i++)
        {
        TInt buttonId = aReader.ReadInt16();
        TInt resId = aReader.ReadInt32();
        TResourceReader buttonReader;
        iCoeEnv->CreateResourceReaderLC(buttonReader, resId);
        CAknSctNaviButton* buttonObj = CAknSctNaviButton::NewL(*this, buttonId, buttonReader);
        iButtonArray.Append(buttonObj);
        CleanupStack::PopAndDestroy(); // buttonReader
        }
    }

void CAknSctTableNavi::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    if (AknLayoutUtils::PenEnabled() && Rect().Contains(aPointerEvent.iPosition))
        {
        if (aPointerEvent.iType == TPointerEvent::EButton1Down)
            {
            iPressedButtonIndex = -1;
            
            for (TInt index = 0; index < iButtonArray.Count(); index++)
                {
                CAknSctNaviButton* buttonObj = iButtonArray[index];
                if(buttonObj->IsEnabled())
                    {
                    TRect buttonRect = buttonObj->iButtonControl->Rect();
                    if (buttonRect.Contains(aPointerEvent.iPosition))
                        {
                        iPressedButtonIndex = index;
                        }
                    }
                }
            }
        else if (aPointerEvent.iType == TPointerEvent::EButton1Up)
            {
            if(iPressedButtonIndex >= 0)
                {
                CAknSctNaviButton* buttonObj = iButtonArray[iPressedButtonIndex];
                if(buttonObj->IsEnabled())
                    {
                    iButtonIndex = iPressedButtonIndex;
                    
                    TRect buttonRect = buttonObj->iButtonControl->Rect();
                    if (buttonRect.Contains(aPointerEvent.iPosition))
                        {
                        switch (buttonObj->iButtonId)
                            {
                            case EAknSctTableNaviExit:
                                {
                                iExtension->iKeyOkEvent = ETrue;
                                TableExitL();
                                }
                                return;
                                
                            case EAknSctTableNaviSpecialChar:
                            case EAknSctTableNaviEmotion:
                                {
                                NextTableL();
                                }
                                return;
                                
                            default:
                                break;
                            }
                        }
                    }
                }
            }
        }
    
    CCoeControl::HandlePointerEventL(aPointerEvent);
    }

TSize CAknSctTableNavi::MinimumSize()
    {
    return Rect().Size();
    }

void CAknSctTableNavi::SizeChanged()
    {
    if (iButtonArray.Count()>0)
        {

        TInt ctrlVariety = 2;
        TInt cellVariety = 1;
        if(!iCharMap->IsJapaneseSctUi())
            {
            ctrlVariety = (iCharMap->TableCount()>1) ? 0 : 1;
            cellVariety = 0;
            }
        
        TAknLayoutRect cellLayRect, buttonLayRect;
        TRect buttonRect;

        // Table exit.
        cellLayRect.LayoutRect(Rect(), AknLayoutScalable_Avkon::cell_graphic2_control_pane(ctrlVariety,0));
        buttonLayRect.LayoutRect(cellLayRect.Rect(), AknLayoutScalable_Avkon::bg_button_pane_cp05(cellVariety));
        buttonRect = buttonLayRect.Rect();

        TAknLayoutRect iconLayRect;
        iconLayRect.LayoutRect(buttonRect, AknLayoutScalable_Avkon::cell_graphic2_control_pane_g1(cellVariety));
        TSize iconSize = iconLayRect.Rect().Size();

        CAknSctNaviButton* buttonObj = iButtonArray[0];
        buttonObj->iButtonControl->SetRect(buttonRect);
        buttonObj->iButtonControl->SetHighlightRect(buttonRect);
        buttonObj->iButtonControl->SetIconScaleMode(EAspectRatioPreserved);
        buttonObj->iButtonControl->SetIconSize(iconSize);
        buttonObj->SetEnabled(ETrue);

        // Table change.
        if (iCharMap->TableCount() > 1)
            {
            cellLayRect.LayoutRect(Rect(), AknLayoutScalable_Avkon::cell_graphic2_control_pane(ctrlVariety,1));
            buttonLayRect.LayoutRect(cellLayRect.Rect(), AknLayoutScalable_Avkon::bg_button_pane_cp05(cellVariety));
            buttonRect = buttonLayRect.Rect();
            
            for (TInt i(1); i<iButtonArray.Count(); i++)
                {
                CAknSctNaviButton* buttonObj = iButtonArray[i];
                buttonObj->iButtonControl->SetRect(buttonRect);
                buttonObj->iButtonControl->SetHighlightRect(buttonRect);
                buttonObj->iButtonControl->SetIconScaleMode(EAspectRatioPreserved);
                buttonObj->iButtonControl->SetIconSize(iconSize);
                buttonObj->SetEnabled(ETrue);
                }
            }

        TRAP_IGNORE(UpdateNextTableButtonL());
        }
    }


void CAknSctTableNavi::UpdateNextTableButtonL()
    {
    
    TBool isFocused = EFalse;
    
    // table switch buttons stay in one place.
    for(TInt index(1); index<iButtonArray.Count(); index++)
        {
        CAknSctNaviButton* buttonObj = iButtonArray[index];
        if(buttonObj->IsEnabled())
            {
            isFocused = buttonObj->IsFocused();
            }
        }
    
    // fresh focused button
    for (TInt index(1); index<iButtonArray.Count(); index++)
        {
        CAknSctNaviButton* buttonObj = iButtonArray[index];
        if (iCharMap->TableCount() > 1)
            {
            switch (iCharMap->NextTableCase())
                {
                case EAknCharMapTableSpecialChar:
                    {
                    TBool isShown = EFalse;
                    if(iExtension->IsShowingEmotion())
                        {
                        isShown = (buttonObj->iButtonId==EAknSctTableNaviSpecialChar);
                        }
                    else
                        {
                        isShown = (buttonObj->iButtonId==EAknSctTableNaviEmotion);
                        }
                    buttonObj->SetEnabled(isShown);
                    buttonObj->SetFocused(isShown && isFocused);
                    if(isShown && isFocused)
                        {
                        iButtonIndex = index;
                        }
                    }
                    break;

                default:
                    buttonObj->SetEnabled(EFalse);
                    break;
                }
            }
        else
            {
            buttonObj->SetEnabled(EFalse);
            }
        }
    }

CCoeControl* CAknSctTableNavi::FocusedControl()
    {
    return this;
    }

TBool CAknSctTableNavi::EnterControl(TInt aX, TInt /*aY*/)
    {
    if (IsVisible())
        {
        if ((aX >= 0) && (aX < iButtonArray.Count()))
            {
            TInt index = aX;
            if (AknLayoutUtils::LayoutMirrored()) // reverse.
                {
                index = (iButtonArray.Count() - 1) - aX;
                }

            index = ButtonPosition(index);

            for(; index<iButtonArray.Count(); index++)
                {
                CAknSctNaviButton* buttonObj = iButtonArray[index];
                if (buttonObj->IsEnabled())
                    {
                    iButtonIndex = index;
                    iExtension->iFocusHandler = this;
                    buttonObj->SetFocused(ETrue);
                    return ETrue;
                    }
                }
            }
        }
    return EFalse;
    }

void CAknSctTableNavi::MoveFocus(TInt aX, TInt /*aY*/)
    {
    TInt delta = aX;
    if (AknLayoutUtils::LayoutMirrored()) // reverse.
        {
        delta = -aX;
        }

    TInt buttonIndex = iButtonIndex + delta;

    // loop until find next position
    for (TInt i = 0; i < iButtonArray.Count(); i++)
        {

        if (buttonIndex > iButtonArray.Count() - 1) // goto Next control
            {
            if (!Layout_Meta_Data::IsLandscapeOrientation())
                {
                // First radio button.
                if (iExtension->iRadioButton)
                    {
                    if (iExtension->iRadioButton->EnterControl(0,0))
                        {
                        LeaveControl();
                        }
                    break;
                    }
                // Grid start.
                if (iExtension->EnterControl(0,iCharMap->ColMin(0)))
                    {
                    LeaveControl();
                    }
                }
            else
                {
                // Left page button.
                if (iExtension->iPageNavi &&
                    iExtension->iPageNavi->EnterControl(0,0))
                    {
                    LeaveControl();
                    }
                }
            break;
            }

        else if (buttonIndex < 0) // goto Prev control
            {
            if (!Layout_Meta_Data::IsLandscapeOrientation())
                {
                // Right page button.
                if (iExtension->iPageNavi &&
                    iExtension->iPageNavi->EnterControl(1,0))
                    {
                    LeaveControl();
                    }
                }
            else
                {
                // Grid end.
                TInt posY = iCharMap->ColMax(0);
                if (iExtension->EnterControl(iCharMap->RowMax(posY),posY))
                    {
                    LeaveControl();
                    }
                }
            break;
            }

        if (iButtonArray[buttonIndex]->IsEnabled()) // goto next button in This control
            {
            CAknSctNaviButton* buttonObj;
            buttonObj = iButtonArray[iButtonIndex];
            buttonObj->SetFocused(EFalse);
            iButtonIndex = buttonIndex;
            buttonObj = iButtonArray[iButtonIndex];
            buttonObj->SetFocused(ETrue);
            break;
            }
        
        buttonIndex += (delta < 0) ? -1 : 1; // get next position
        }
    }

TBool CAknSctTableNavi::LeaveControl()
    {
    for (TInt i = 0; i < iButtonArray.Count(); i++ )
        {
        iButtonArray[i]->SetFocused(EFalse);
        }
    return ETrue;
    }

TBool CAknSctTableNavi::ExitWithKey(TInt /*aKeycode*/)
    {
    if (iButtonArray[iButtonIndex]->iButtonId != EAknSctTableNaviExit)
        {
        return EFalse;
        }
    else
        {
        return ETrue;
        }
    }

// ----------------------------------------------------------------------------
// Page Navi class implementation
// ----------------------------------------------------------------------------
//
CAknSctPageNavi::CAknSctPageNavi(
    CAknCharMap* aCharMap,
    CAknCharMapExtension* aExtension)
    :iCharMap(aCharMap),
    iExtension(aExtension)
    {
    }

CAknSctPageNavi::~CAknSctPageNavi()
    {
    if (iButtonArray.Count())
        {
        iButtonArray.ResetAndDestroy();
        }
    iButtonArray.Close();
    delete iTitle;
    }

TInt CAknSctPageNavi::CountComponentControls() const
    {
    TInt num= 0;
    if (iTitle)
        {
        num++;
        }
    if (iButtonArray.Count() > 0)
        {
        num += iButtonArray.Count();
        }
    return num;
    }

CCoeControl* CAknSctPageNavi::ComponentControl( TInt aIndex ) const
    {
    if (iTitle)
        {
        if ( aIndex == 0 )
            {
            return iTitle;
            }
        aIndex--;
        }
    if (iButtonArray.Count() > 0)
        {
        return iButtonArray[ aIndex ]->iButtonControl;
        }
    return NULL;
    }

TKeyResponse CAknSctPageNavi::OfferKeyEventL(
    const TKeyEvent& aKeyEvent,
    TEventCode aModifiers)
    {
    CAknSctNaviButton* buttonObj = iButtonArray[iButtonIndex];
    buttonObj->iButtonControl->OfferKeyEventL(aKeyEvent,aModifiers);
    TKeyResponse response = EKeyWasNotConsumed;
    TUint code=aKeyEvent.iCode;
    switch (code)
        {
        case EKeyEnter:
        case EKeyOK:
            {
            switch (buttonObj->iButtonId)
                {
                case EAknSctPageNaviPrevPage:
                    {
                    iCharMap->PrevPageL();
                    }
                    break;
                case EAknSctPageNaviNextPage:
                    {
                    iCharMap->NextPageL();
                    }
                    break;
                default:
                    return EKeyWasConsumed;
                }
            buttonObj->SetFocused(ETrue);
            response = EKeyWasConsumed;
            UpdatePageTitleL();
            }
            break;
        case EKeyLeftArrow:
        case '4':
            {
            MoveFocus(-1,0);
            response = EKeyWasConsumed;
            }
            break;
        case EKeyRightArrow:
        case '6':
            {
            MoveFocus(1,0);
            response = EKeyWasConsumed;
            }
            break;
        case EKeyUpArrow:
        case '2':
            {
            response = EKeyWasConsumed;
            if (!Layout_Meta_Data::IsLandscapeOrientation())
                {
                if (iExtension->iRadioButton && !IsNextButton())
                    {
                    // Last radio button.
                    if (iExtension->iRadioButton->EnterControl(
                        0,iExtension->iRadioButton->Count()-1))
                        {
                        LeaveControl();
                        }
                    break;
                    }
                }
            TInt xPos;
            if (!Layout_Meta_Data::IsLandscapeOrientation())
                {
                xPos = IsNextButton() ? iCharMap->MaxCols() - 1 : 0;
                }
            else
                {
                if (IsNextButton())
                    {
                    xPos = iCharMap->MaxCols() - 1;
                    }
                else
                    {
                    xPos = !iExtension->iRadioButton ?
                        iCharMap->TableCount() : iCharMap->MaxCols()-2;
                    }
                }
            if (iCharMap->ColMax(0) > iCharMap->ColMax(xPos))
                {
                xPos = iCharMap->RowMax(iCharMap->ColMax(0));
                }
            // Grid bottom row.
            if (iExtension->EnterControl(xPos,iCharMap->ColMax(xPos)))
                {
                LeaveControl();
                break;
                }
            }
            break;
        case EKeyDownArrow:
        case '8':
            {
            response = EKeyWasConsumed;
            if (!Layout_Meta_Data::IsLandscapeOrientation())
                {
                if (!IsNextButton())
                    {
                    // First table button.
                    if (iExtension->iTableNavi &&
                        iExtension->iTableNavi->EnterControl(0,0))
                        {
                        LeaveControl();
                        break;
                        }
                    }
                else
                    {
                    // Grid top row.
                    TInt xPos = iCharMap->MaxCols() - 1;
                    if (iExtension->EnterControl(xPos,iCharMap->ColMin(xPos)))
                        {
                        LeaveControl();
                        break;
                        }
                    }
                }
            else
                {
                TInt xPos;
                if (IsNextButton())
                    {
                    xPos = iCharMap->MaxCols() - 1;
                    }
                else
                    {
                    xPos = !iExtension->iRadioButton ?
                        iCharMap->TableCount() : iCharMap->MaxCols() - 2;
                    }
                // Grid top row.
                if (iExtension->EnterControl(xPos,iCharMap->ColMin(xPos)))
                    {
                    LeaveControl();
                    break;
                    }
                }
            }
            break;
        default:
            break;
        }
    return response;
    }

TBool CAknSctPageNavi::IsNextButton() const
    {
    if (iButtonIndex < iButtonArray.Count() && iButtonArray[iButtonIndex])
        {
        return iButtonArray[iButtonIndex]->iButtonId == EAknSctPageNaviNextPage;
        }
    return EFalse;
    }

void CAknSctPageNavi::ConstructFromResourceL(TResourceReader& aReader)
    {
    TInt counts = aReader.ReadInt16();
    for (TInt i = 0; i < counts; i++)
        {
        TInt buttonId = aReader.ReadInt16();
        TInt resId = aReader.ReadInt32();
        TResourceReader oneButtonReader;
        iCoeEnv->CreateResourceReaderLC(oneButtonReader, resId);
        CAknSctNaviButton* buttonObj =
            CAknSctNaviButton::NewL(*this, buttonId, oneButtonReader);
        buttonObj->iButtonControl->SetObserver(this); // for handling control events.
        iButtonArray.Append(buttonObj);
        CleanupStack::PopAndDestroy(); // oneButtonReader
        }
    iTitle = new (ELeave) CEikLabel;
    }

void CAknSctPageNavi::HandleControlEventL(
    CCoeControl* aControl,
    TCoeEvent aEventType)
    {
    if (aEventType == EEventStateChanged && AknLayoutUtils::PenEnabled()) // action on key repeat
        {
        for (TInt index=0; index < iButtonArray.Count(); index++)
            {
            CAknSctNaviButton* buttonObj = iButtonArray[index];
            TRect buttonRect = buttonObj->iButtonControl->Rect();
            if (buttonObj->iButtonControl == aControl)
                {
                if (buttonObj->IsEnabled() && buttonObj->iPressed)
                    {
                    iButtonIndex = index;
                    switch (buttonObj->iButtonId)
                        {
                        case EAknSctPageNaviPrevPage:
                            {
                            buttonObj->iRepeat = ETrue; // Set button repeat.
                            iCharMap->PrevPageL();
                            UpdatePageTitleL();
                            }
                            break;
                        case EAknSctPageNaviNextPage:
                            {
                            buttonObj->iRepeat = ETrue; // Set button repeat.
                            iCharMap->NextPageL();
                            UpdatePageTitleL();
                            }
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
        }
    }

void CAknSctPageNavi::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    if (AknLayoutUtils::PenEnabled() && Rect().Contains(aPointerEvent.iPosition))
        {
        if (aPointerEvent.iType == TPointerEvent::EButton1Down)
            {
            for (TInt index=0; index < iButtonArray.Count(); index++)
                {
                CAknSctNaviButton* buttonObj = iButtonArray[index];
                buttonObj->iPressed = EFalse;
                buttonObj->iRepeat = EFalse;
                TRect buttonRect = buttonObj->iButtonControl->Rect();
                if (buttonRect.Contains(aPointerEvent.iPosition))
                    {
                    if (buttonObj->IsEnabled())
                        {
                        buttonObj->iButtonControl->SetButtonFlags(KAknButtonKeyRepeat);
                        buttonObj->iPressed = ETrue; // Set button pressed.
                        }
                    }
                }
            }
        else if (aPointerEvent.iType == TPointerEvent::EButton1Up) // action on button release.
            {
            for (TInt index=0; index < iButtonArray.Count(); index++)
                {
                CAknSctNaviButton* buttonObj = iButtonArray[index];
                TRect buttonRect = buttonObj->iButtonControl->Rect();
                if (buttonRect.Contains(aPointerEvent.iPosition))
                    {
                    if (buttonObj->IsEnabled())
                        {
                        if (buttonObj->iPressed && !buttonObj->iRepeat)
                            {
                            iButtonIndex = index;
                            switch (buttonObj->iButtonId)
                                {
                                case EAknSctPageNaviPrevPage:
                                    {
                                    iCharMap->PrevPageL();
                                    UpdatePageTitleL();
                                    }
                                    break;
                                case EAknSctPageNaviNextPage:
                                    {
                                    iCharMap->NextPageL();
                                    UpdatePageTitleL();
                                    }
                                    break;
                                default:
                                    break;
                                }
                            }
                        }
                    }
                buttonObj->iPressed = EFalse; // Button released.
                buttonObj->iRepeat = EFalse;
                }
            }
        }
    CCoeControl::HandlePointerEventL(aPointerEvent);
    }

TSize CAknSctPageNavi::MinimumSize()
    {
    return Rect().Size();
    }

void CAknSctPageNavi::SizeChanged()
    {

    TAknLayoutRect pageButtonLayRect;
    TInt pageVariate = !iCharMap->IsJapaneseSctUi() ? ((iCharMap->TableCount() > 1) ? 0 : 1) : 2;
                       
    CAknSctNaviButton* buttonObj;
    TRect rect;

    buttonObj = iButtonArray[0];
    buttonObj->iButtonControl->SetButtonFlags(0);
    if (!AknLayoutUtils::LayoutMirrored())
        {
        buttonObj->iButtonId = EAknSctPageNaviPrevPage;
        pageButtonLayRect.LayoutRect(Rect(),AknLayoutScalable_Avkon::bg_button_pane_cp10(pageVariate));
        }
    else
        {
        buttonObj->iButtonId = EAknSctPageNaviNextPage;
        pageButtonLayRect.LayoutRect(Rect(),AknLayoutScalable_Avkon::bg_button_pane_cp11(pageVariate));
        }
    rect = pageButtonLayRect.Rect();
    buttonObj->iButtonControl->SetRect(rect);
    buttonObj->iButtonControl->SetHighlightRect(rect);
    TAknLayoutRect pageButtonIconLayRect;
    pageButtonIconLayRect.LayoutRect(pageButtonLayRect.Rect(), AknLayoutScalable_Avkon::graphic2_pages_pane_g1(pageVariate));
    buttonObj->iButtonControl->SetIconScaleMode(EAspectRatioPreserved);
    TSize iconSize = pageButtonIconLayRect.Rect().Size();
    buttonObj->iButtonControl->SetIconSize(iconSize);

    buttonObj = iButtonArray[1];
    buttonObj->iButtonControl->SetButtonFlags(0);
    if (!AknLayoutUtils::LayoutMirrored())
        {
        buttonObj->iButtonId = EAknSctPageNaviNextPage;
        pageButtonLayRect.LayoutRect(Rect(), AknLayoutScalable_Avkon::bg_button_pane_cp11(pageVariate));
        }
    else
        {
        buttonObj->iButtonId = EAknSctPageNaviPrevPage;
        pageButtonLayRect.LayoutRect(Rect(), AknLayoutScalable_Avkon::bg_button_pane_cp10(pageVariate));
        }
    rect = pageButtonLayRect.Rect();
    buttonObj->iButtonControl->SetRect(rect);
    buttonObj->iButtonControl->SetHighlightRect(rect);
    buttonObj->iButtonControl->SetIconScaleMode(EAspectRatioPreserved);
    buttonObj->iButtonControl->SetIconSize(iconSize);

    // Page text.
    TRect parentRect = Rect();
    AknLayoutUtils::LayoutLabel(iTitle, parentRect, AknLayoutScalable_Avkon::graphic2_pages_pane_t1(pageVariate).LayoutLine());

    // Page text color
    TAknLayoutText textLayout;
    textLayout.LayoutText(parentRect, AknLayoutScalable_Avkon::graphic2_pages_pane_t1(pageVariate));
    TRect textRect = textLayout.TextRect();
    TRgb color = textLayout.Color();
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    if (skin)
        {
        (void)AknsUtils::GetCachedColor(skin, color, KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG6);
        }
    TRAP_IGNORE(AknLayoutUtils::OverrideControlColorL(*iTitle, EColorLabelText, color));
    TRAP_IGNORE(UpdatePageTitleL());
    }

void CAknSctPageNavi::Draw(const TRect& /*aRect*/) const
    {
    TRAP_IGNORE(UpdatePageTitleL());
    }

void CAknSctPageNavi::UpdatePageTitleL() const
    {
    CArrayFix<TInt>* numbers = new(ELeave)CArrayFixFlat<TInt>(2);
    CleanupStack::PushL(numbers);
    numbers->AppendL(iCharMap->CurrentPage());
    numbers->AppendL(iCharMap->PageCount());
    HBufC* page =
        StringLoader::LoadL(
            R_AVKON_SPECIAL_CHARACTERS_PAGE_INDICATOR, *numbers, iEikonEnv);
    CleanupStack::PopAndDestroy(); // numbers
    iTitle->SetTextL(page->Des());
    iTitle->SetBrushStyle(CGraphicsContext::ENullBrush);
    delete page;
    }

CCoeControl* CAknSctPageNavi::FocusedControl()
    {
    return this;
    }

TBool CAknSctPageNavi::EnterControl(TInt aX, TInt /*aY*/)
    {
    if (IsVisible())
        {
        if ((aX >= 0) && (aX < iButtonArray.Count()))
            {
            CAknSctNaviButton* buttonObj;
            buttonObj = iButtonArray[iButtonIndex];
            buttonObj->SetFocused(EFalse);
            TInt index = aX;
            if (AknLayoutUtils::LayoutMirrored()) // reverse.
                {
                index = iButtonArray.Count() - 1 - aX;
                }
            buttonObj = iButtonArray[index];
            if (buttonObj->IsEnabled())
                {
                iButtonIndex = index;
                iExtension->iFocusHandler = this;
                buttonObj->SetFocused(ETrue);
                return ETrue;
                }
            }
        }
    return EFalse;
    }

void CAknSctPageNavi::MoveFocus(TInt aX, TInt /*aY*/)
    {
    TInt delta = aX;
    TInt buttonIndex = iButtonIndex + delta;
    for (TInt i = 0; i < iButtonArray.Count(); i++)
        {
        if (buttonIndex > iButtonArray.Count() - 1) // Next control.
            {
            if (!AknLayoutUtils::LayoutMirrored())
                {
                if (!Layout_Meta_Data::IsLandscapeOrientation())
                    {
                    // First table button.
                    if (iExtension->iTableNavi &&
                        iExtension->iTableNavi->EnterControl(0,0))
                        {
                        LeaveControl();
                        break;
                        }
                    }
                else
                    {
                    // First radio button.
                    if (iExtension->iRadioButton &&
                        iExtension->iRadioButton->EnterControl(0,0))
                        {
                        LeaveControl();
                        break;
                        }
                    // Grid start.
                    TInt yPos = iCharMap->ColMin(0);
                    if (iExtension->EnterControl(iCharMap->RowMin(yPos),yPos))
                        {
                        LeaveControl();
                        break;
                        }
                    }
                }
            else
                {
                if (!Layout_Meta_Data::IsLandscapeOrientation())
                    {
                    // Grid end.
                    TInt yPos = iCharMap->ColMax(0);
                    if (iExtension->EnterControl(iCharMap->RowMax(yPos),yPos))
                        {
                        LeaveControl();
                        break;
                        }
                    }
                else
                    {
                    // Last table button.
                    TInt xPos = iCharMap->TableCount() - 1;
                    if (iExtension->iTableNavi &&
                        iExtension->iTableNavi->EnterControl(xPos,0))
                        {
                        LeaveControl();
                        break;
                        }
                    }
                }
            break;
            }
        else if (buttonIndex < 0) // Prev control
            {
            if (!AknLayoutUtils::LayoutMirrored())
                {
                if (!Layout_Meta_Data::IsLandscapeOrientation())
                    {
                    // Grid end.
                    TInt yPos = iCharMap->ColMax(0);
                    if (iExtension->EnterControl(iCharMap->RowMax(yPos),yPos))
                        {
                        LeaveControl();
                        break;
                        }
                    }
                else
                    {
                    // Last table button.
                    if (iExtension->iTableNavi && 
                        iExtension->iTableNavi->EnterControl(iCharMap->TableCount()-1,0))
                        {
                        LeaveControl();
                        break;
                        }
                    }
                }
            else
                {
                if (!Layout_Meta_Data::IsLandscapeOrientation())
                    {
                    // First table button.
                    if (iExtension->iTableNavi &&
                        iExtension->iTableNavi->EnterControl(0,0))
                        {
                        LeaveControl();
                        break;
                        }
                    }
                else
                    {
                    // Grid start.
                    TInt yPos = iCharMap->ColMin(0);
                    if (iExtension->EnterControl(iCharMap->RowMin(yPos),yPos))
                        {
                        LeaveControl();
                        break;
                        }
                    }
                }
            }

        if (iButtonArray[buttonIndex]->IsEnabled()) // This control
            {
            CAknSctNaviButton* buttonObj;
            buttonObj = iButtonArray[iButtonIndex];
            buttonObj->SetFocused(EFalse);
            iButtonIndex = buttonIndex;
            buttonObj = iButtonArray[iButtonIndex];
            buttonObj->SetFocused(ETrue);
            break;
            }
        buttonIndex += (delta < 0) ? -1 : 1;
        }
    }

TBool CAknSctPageNavi::LeaveControl()
    {
    for (TInt i = 0; i < iButtonArray.Count(); i++ )
        {
        iButtonArray[i]->SetFocused(EFalse);
        }
    return ETrue;
    }

TBool CAknSctPageNavi::ExitWithKey(TInt /*aKeycode*/)
    {
    return EFalse;
    }

// ----------------------------------------------------------------------------
// Category button class implementation
// ----------------------------------------------------------------------------
//
CAknSctCategoryButton* CAknSctCategoryButton::NewL(
    const CCoeControl& aParent,
    TResourceReader& reader,
    TInt aCategoryButtonId,
    TInt aSctCaseId)
    {
    CAknSctCategoryButton* self =
        new( ELeave ) CAknSctCategoryButton(aCategoryButtonId, aSctCaseId);

    CleanupStack::PushL( self );
    self->ConstructL(aParent, reader);
    CleanupStack::Pop();

    return self;
    }

CAknSctCategoryButton::CAknSctCategoryButton(
    TInt aCategoryButtonId,
    TInt aSctCaseId)
    : iButtonId(aCategoryButtonId)
    , iSctCaseId(aSctCaseId)
    {
    }

void CAknSctCategoryButton::ConstructL(
    const CCoeControl& aParent,
    TResourceReader& aReader)
    {
    iButtonControl = CAknButton::NewL(aReader);
    iButtonControl->SetContainerWindowL(aParent);
    }

CAknSctCategoryButton::~CAknSctCategoryButton()
    {
    delete iButtonControl;
    }

void CAknSctCategoryButton::SetFocused(TBool aState)
    {
    iButtonControl->SetFocus(aState);
    iButtonControl->DrawNow();
    }


// ----------------------------------------------------------------------------
// Radio button class implementation
// ----------------------------------------------------------------------------
//
CAknSctRadioButton::CAknSctRadioButton()
    {
    }

CAknSctRadioButton::CAknSctRadioButton(
    CAknCharMap* aCharMap,
    CAknCharMapExtension* aExtension)
    :iExtension(aExtension),
    iCharMap(aCharMap)
    {
    }

CAknSctRadioButton::~CAknSctRadioButton()
    {
    iButtonArray.ResetAndDestroy();
    iButtonArray.Close();
    }

TInt CAknSctRadioButton::CountComponentControls() const
    {
    return iButtonArray.Count();
    }

CCoeControl* CAknSctRadioButton::ComponentControl( TInt aIndex ) const
    {
    if (aIndex < iButtonArray.Count())
        {
        return iButtonArray[aIndex]->iButtonControl;
        }
    return NULL;
    }

TKeyResponse CAknSctRadioButton::OfferKeyEventL(
    const TKeyEvent& aKeyEvent,
    TEventCode /*aModifiers*/)
    {
    TKeyResponse responce = EKeyWasNotConsumed;
    TUint code=aKeyEvent.iCode;
    switch (code)
        {
        case EKeyEnter:
        case EKeyOK:
            {
            if (AknLayoutUtils::PenEnabled())
                {
                // Grid.
                TInt yPos = iCharMap->ColMin(0);
                TInt xPos = iCharMap->RowMin(yPos);
                if (iExtension->EnterControl(xPos,yPos))
                    {
                    CAknButton* buttonCtrlObj;
                    TInt currentIndex;
                    TInt newIndex;
                    for (TInt index=0; index < iButtonArray.Count(); index++)
                        {
                        buttonCtrlObj = iButtonArray[index]->iButtonControl;
                        currentIndex = buttonCtrlObj->StateIndex();
                        if (index == iButtonIndex)
                            {
                            newIndex = KAknSctRadioOn;
                            }
                        else
                            {
                            newIndex = KAknSctRadioOff;
                            }
                        if (currentIndex != newIndex)
                            {
                            buttonCtrlObj->SetCurrentState(newIndex, ETrue);
                            if (newIndex == KAknSctRadioOn)
                                {
                                iExtension->iCurrentCategory =
                                    iButtonArray[index]->iButtonId;
                                iCharMap->SetStatusChanged(EAknCharChangedCategory);
                                }
                            }
                        }
                    LeaveControl();
                    }
                }
            responce = EKeyWasConsumed;
            }
            break;
        case EKeyLeftArrow:
        case '4':
            {
            responce = EKeyWasConsumed;
            if (AknLayoutUtils::PenEnabled())
                {
                TInt yPos = iButtonIndex - 1;
                if (iCharMap->RowMax(yPos) < 0)
                    {
                    if (Layout_Meta_Data::IsLandscapeOrientation())
                        {
                        if (iExtension->iRadioButton)
                            {
                            // Right page button.
                            if (iExtension->iPageNavi &&
                                iExtension->iPageNavi->EnterControl(1,0))
                                {
                                LeaveControl();
                                break;
                                }
                            }
                        }
                    // Next button up.
                    MoveFocus(0,-1);
                    break;
                    }
                else
                    {
                    //Previous row end.
                    TInt xPos = iCharMap->RowMax(yPos);
                    if (iExtension->EnterControl(xPos,yPos))
                        {
                        LeaveControl();
                        break;
                        }
                    }
                break;
                }
            // Move by grid.
            iCharMap->TakeFocus();
            TInt xPos = iCharMap->CursorPos().iX;
            TInt yPos = iCharMap->CursorPos().iY;
            if (xPos == 0)
                {
                iCharMap->MoveFocus(-1,0);
                }
            iCharMap->ShowFocus();
            }
            break;
        case EKeyRightArrow:
        case '6':
            {
            responce = EKeyWasConsumed;
            if (AknLayoutUtils::PenEnabled())
                {
                TInt yPos = iButtonIndex;
                if (iCharMap->RowMax(yPos) < 0)
                    {
                    // Next button down.
                    MoveFocus(0,1);
                    break;
                    }
                else
                    {
                    // 1st cell in the row.
                    if (iExtension->EnterControl(0,yPos))
                        {
                        LeaveControl();
                        break;
                        }
                    }
                break;
                }
            // Move by grid.
            iCharMap->TakeFocus();
            TInt xPos = iCharMap->CursorPos().iX;
            TInt yPos = iCharMap->CursorPos().iY;
            if (xPos == iCharMap->RowMax(yPos))
                {
                iCharMap->MoveFocus(1,0);
                }
            iCharMap->ShowFocus();
            }
            break;
        case EKeyDownArrow:
        case '8':
            {
            MoveFocus(0, 1);
            responce = EKeyWasConsumed;
            }
            break;
        case EKeyUpArrow:
        case '2':
            {
            MoveFocus(0,-1);
            responce = EKeyWasConsumed;
            }
            break;
        default:
            break;
        }
    return responce;
    }

void CAknSctRadioButton::ConstructFromResourceL(TResourceReader& aReader)
    {
    TInt counts = aReader.ReadInt16();
    TResourceReader reader;
    TInt categorybutton_id;
    TInt sctcase_id;
    TInt resId;
    CAknSctCategoryButton* buttonObj;
    TBool allowCreation;

    for (TInt index=0; index < counts; index++)
        {
        allowCreation = EFalse;
        // button id
        categorybutton_id = aReader.ReadInt16();
        sctcase_id = aReader.ReadInt16();
        switch (categorybutton_id)
            {
            case EAknSCTCategoryButtonHalfCase:
            case EAknSCTCategoryButtonFullCase:
                allowCreation = ETrue;
                break;
            case EAknSCTCategoryButtonPicto:
                if (iExtension->iPictographsBuffer)
                    {
                    allowCreation = ETrue;
                    }
                break;
            case EAknSCTCategoryButtonPicto1:
            case EAknSCTCategoryButtonPicto2:
                if (iExtension->iPictographsBuffer &&
                    iExtension->iPictographsBufferGrouping)
                    {
                    allowCreation = ETrue;
                    }
                break;
            default:
                break;
            }

        if (allowCreation)
            {
            // read the button resource
            resId = aReader.ReadInt32();
            iCoeEnv->CreateResourceReaderLC( reader, resId );
            // create Category button object
            buttonObj = CAknSctCategoryButton::NewL(
                *this, reader, categorybutton_id, sctcase_id);
            // Append button
            iButtonArray.Append(buttonObj);
            CleanupStack::PopAndDestroy(); // reader
            }
        else
            {
            // Skip data
            resId = aReader.ReadInt32();
            }
        }

    }

void CAknSctRadioButton::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    TRect rect(Rect());
    if (AknLayoutUtils::PenEnabled() && rect.Contains(aPointerEvent.iPosition))
        {
        if (aPointerEvent.iType == TPointerEvent::EButton1Down)
            {
            CAknButton* buttonCtrlObj;
            TRect rectButton;
            TInt currentIndex;
            TInt newIndex;
            for (TInt index=0; index < iButtonArray.Count(); index++)
                {
                buttonCtrlObj = iButtonArray[index]->iButtonControl;
                rectButton = buttonCtrlObj->Rect();
                currentIndex = buttonCtrlObj->StateIndex();

                if (rectButton.Contains(aPointerEvent.iPosition))
                    {
                    newIndex = KAknSctRadioOn;
                    }
                else
                    {
                    newIndex = KAknSctRadioOff;
                    }
                if (currentIndex != newIndex)
                    {
                    buttonCtrlObj->SetCurrentState(newIndex, ETrue);
                    if (newIndex == KAknSctRadioOn)
                        {
                        if (AknLayoutUtils::PenEnabled())
                            {
                            iButtonIndex = index;
                            }
                        iExtension->iCurrentCategory =
                            iButtonArray[index]->iButtonId;
                        iCharMap->SetStatusChanged(EAknCharChangedCategory);
                        }
                    }
                }
            }
        else if (aPointerEvent.iType == TPointerEvent::EDrag)
            {
            }
        else if (aPointerEvent.iType == TPointerEvent::EButton1Up)
            {
            }
        }
    else
        {
        CCoeControl::HandlePointerEventL(aPointerEvent);
        }
    }

TSize CAknSctRadioButton::MinimumSize()
    {
    TAknLayoutRect oneButtonLayRect;
    if (!AknLayoutUtils::PenEnabled())
        {
        TAknLayoutScalableParameterLimits charMapDialogVariety =
            AknLayoutScalable_Avkon::popup_grid_graphic_window_ParamLimits();

        // Main pane without softkeys
        TRect mainPaneRect;
        if(!AknLayoutUtils::LayoutMetricsRect(
            AknLayoutUtils::EPopupParent, mainPaneRect))
            {
            mainPaneRect = iAvkonAppUi->ClientRect();
            }

        // Calc the variety
        TInt maxVariety = charMapDialogVariety.LastVariety();

        TAknLayoutRect popupGridLayRect;
        popupGridLayRect.LayoutRect(mainPaneRect,
            AknLayoutScalable_Avkon::popup_grid_graphic_window(maxVariety));

        // Calculate the size relatively
        TRect relativeDialog(TPoint(0,0),popupGridLayRect.Rect().Size());

        // Get the layout of the actual character grid with scrollbar
        TAknLayoutRect gridWithScrollLayRect;
        gridWithScrollLayRect.LayoutRect(relativeDialog,
            AknLayoutScalable_Avkon::listscroll_popup_graphic_pane());

        TAknLayoutRect categoryButtonLayRect;
        categoryButtonLayRect.LayoutRect(gridWithScrollLayRect.Rect(),
            AknLayoutScalable_Avkon::grid_sct_catagory_button_pane());

        oneButtonLayRect.LayoutRect(categoryButtonLayRect.Rect(),
            AknLayoutScalable_Avkon::cell_sct_catagory_button_pane());
        }
    else
        {
        TAknLayoutRect popupGridLayRect;
        popupGridLayRect.LayoutRect(iAvkonAppUi->ApplicationRect(),
            AknLayoutScalable_Avkon::popup_grid_graphic2_window(0));

        TAknLayoutRect oneButtonLayRect;
        TAknLayoutRect categoryButtonLayRect;
        if (!Layout_Meta_Data::IsLandscapeOrientation())
            {
            oneButtonLayRect.LayoutRect(popupGridLayRect.Rect(),
                AknLayoutScalable_Avkon::grid_graphic2_control_pane(4));

            categoryButtonLayRect.LayoutRect(popupGridLayRect.Rect(),
                AknLayoutScalable_Avkon::grid_graphic2_catg_pane(0));
            }
        else
            {
            oneButtonLayRect.LayoutRect(popupGridLayRect.Rect(),
                AknLayoutScalable_Avkon::grid_graphic2_control_pane(5));

            categoryButtonLayRect.LayoutRect(popupGridLayRect.Rect(),
                AknLayoutScalable_Avkon::grid_graphic2_catg_pane(1));

            }
        }

    TSize size(oneButtonLayRect.Rect().Width(),
        oneButtonLayRect.Rect().Height() * iButtonArray.Count());
    return size;
    }

void CAknSctRadioButton::SizeChanged()
    {
    TRect base;
    if (!AknLayoutUtils::PenEnabled())
        {
        TAknLayoutScalableParameterLimits charMapDialogVariety =
            AknLayoutScalable_Avkon::popup_grid_graphic_window_ParamLimits();

        // Main pane without softkeys
        TRect mainPaneRect;
        if(!AknLayoutUtils::LayoutMetricsRect(
            AknLayoutUtils::EPopupParent, mainPaneRect))
            {
            mainPaneRect = iAvkonAppUi->ClientRect();
            }

        // Calc the variety
        TInt maxVariety = charMapDialogVariety.LastVariety();

        TAknLayoutRect popupGridLayRect;
        popupGridLayRect.LayoutRect(mainPaneRect,
            AknLayoutScalable_Avkon::popup_grid_graphic_window(maxVariety));

        // Calculate the size relatively
        TRect relativeDialog(TPoint(0,0), popupGridLayRect.Rect().Size());

        // Get the layout of the actual character grid with scrollbar
        TAknLayoutRect gridWithScrollLayRect;
        gridWithScrollLayRect.LayoutRect(relativeDialog,
            AknLayoutScalable_Avkon::listscroll_popup_graphic_pane());

        TAknLayoutRect categoryButtonLayRect;
        categoryButtonLayRect.LayoutRect(gridWithScrollLayRect.Rect(),
            AknLayoutScalable_Avkon::grid_sct_catagory_button_pane());

        TAknLayoutRect oneButtonLayRect;
        oneButtonLayRect.LayoutRect(categoryButtonLayRect.Rect(),
            AknLayoutScalable_Avkon::cell_sct_catagory_button_pane());

        base = oneButtonLayRect.Rect();
        }
    else
        {
        TAknLayoutRect popupGridLayRect;
        popupGridLayRect.LayoutRect(iAvkonAppUi->ApplicationRect(),
            AknLayoutScalable_Avkon::popup_grid_graphic2_window(0));

        TAknLayoutRect oneButtonLayRect;
        TAknLayoutRect categoryButtonLayRect;
        if ( !Layout_Meta_Data::IsLandscapeOrientation() )
            {
            oneButtonLayRect.LayoutRect(popupGridLayRect.Rect(),
                AknLayoutScalable_Avkon::grid_graphic2_control_pane(4));

            categoryButtonLayRect.LayoutRect(popupGridLayRect.Rect(),
                AknLayoutScalable_Avkon::grid_graphic2_catg_pane(0));
            }
        else
            {
            oneButtonLayRect.LayoutRect(popupGridLayRect.Rect(),
                AknLayoutScalable_Avkon::grid_graphic2_control_pane(5));

            categoryButtonLayRect.LayoutRect(popupGridLayRect.Rect(),
                AknLayoutScalable_Avkon::grid_graphic2_catg_pane(1));

            }
        base.iTl = categoryButtonLayRect.Rect().iTl;
        base.SetSize(oneButtonLayRect.Rect().Size());
        }

    if (iButtonArray.Count() > 0)
        {
        CAknButton* buttonCtrlObj;

        TMargins8 margins;
        margins.iTop = 1;
        margins.iBottom = 0;
        margins.iLeft = 0;
        margins.iRight = 0;

        // Change the size of buttons
        for (TInt index=0; index < iButtonArray.Count(); index++)
            {
            buttonCtrlObj = iButtonArray[index]->iButtonControl;
            if (buttonCtrlObj)
                {
                if (AknLayoutUtils::PenEnabled())
                    {
                    buttonCtrlObj->SetHighlightRect(base);
                    }
                buttonCtrlObj->SetRect( base );
                buttonCtrlObj->SetIconSize( base.Size() );
                buttonCtrlObj->SetMargins( margins );
                buttonCtrlObj->SetIconScaleMode(EAspectRatioPreserved);
                base.Move(TPoint(0, base.Size().iHeight));
                }
            }
        }
    }

void CAknSctRadioButton::Draw(const TRect& /*aRect*/) const
    {
    // no draw
    }

/**
 * Returns ETrue if the aFlag bitfield in iFlags is set, EFalse if it
 * is clear
 */
inline TInt CAknSctRadioButton::Count() const
    {
    return iButtonArray.Count();
    }

void CAknSctRadioButton::SetCurrentCategory(TInt aCategory)
    {
    CAknSctCategoryButton* buttonObj;
    TInt status;

    for (TInt index=0; index < iButtonArray.Count(); index++)
        {
        buttonObj = iButtonArray[index];
        status = (buttonObj->iButtonId == aCategory)?
                     KAknSctRadioOn : KAknSctRadioOff;
        buttonObj->iButtonControl->SetCurrentState(status, ETrue);
        }
    }

void CAknSctRadioButton::SetValidSctCase(TInt aSctCase)
    {
    CAknSctCategoryButton* buttonObj;

    for (TInt index=0; index < iButtonArray.Count(); index++)
        {
        buttonObj = iButtonArray[index];
        if (buttonObj->iSctCaseId == aSctCase)
            {
            buttonObj->iValid = ETrue;
            break;
            }
        // Here is the special case for Half-width/Lower/Upper
        else if (buttonObj->iSctCaseId == EAknSCTHalfCase
              && (aSctCase == EAknSCTLowerCase
                 || aSctCase == EAknSCTUpperCase)
                )
            {
            buttonObj->iValid = ETrue;
            break;
            }
        }
    }

void CAknSctRadioButton::RemoveInvalidButton()
    {
    CAknSctCategoryButton* buttonObj;

    for (TInt index=iButtonArray.Count()-1; index >= 0; index--)
        {
        buttonObj = iButtonArray[index];
        if (!buttonObj->iValid)
            {
            if (buttonObj->iSctCaseId == EAknSCTHalfCase)
                {
                if (iButtonArray.Count() > 1)
                    {
                    delete buttonObj;
                    iButtonArray.Remove(index);
                    }
                }
            else
                {
                delete buttonObj;
                iButtonArray.Remove(index);
                }
            }
        }
    }

CCoeControl* CAknSctRadioButton::FocusedControl()
    {
    return this;
    }

TBool CAknSctRadioButton::EnterControl(TInt /*aX*/, TInt aY)
    {
    if (IsVisible())
        {
        if ((aY >= 0) && (aY < Count()))
            {
            if (iExtension->iHasCategoryButtonUi)
                {
                iEntryIndex = aY;
                iExtension->iFocusHandler = this;
                if (AknLayoutUtils::PenEnabled())
                    {
                    iButtonIndex = aY;
                    CAknSctCategoryButton* buttonObj =
                        iButtonArray[iButtonIndex];
                    buttonObj->SetFocused(ETrue);
                    }
                return ETrue;
                }
            }
        }
    return EFalse;
    }

void CAknSctRadioButton::MoveFocus(TInt /*aX*/, TInt aY)
    {
    CAknSctCategoryButton* buttonObj;
    CAknButton* buttonCtrlObj;
    TInt buttonIndex = iButtonIndex + aY;
    if (buttonIndex > iButtonArray.Count() - 1)
        {
        if (!AknLayoutUtils::PenEnabled())
            {
             // First radio button.
            buttonIndex = 0;
            }
        else
            {
            if (!Layout_Meta_Data::IsLandscapeOrientation())
                {
                // Left page button.
                if (iExtension->iPageNavi &&
                    iExtension->iPageNavi->EnterControl(0,0))
                    {
                    LeaveControl();
                    return;
                    }
                }
            else
                {
                // First table button.
                if (iExtension->iTableNavi &&
                    iExtension->iTableNavi->EnterControl(0,0))
                    {
                    LeaveControl();
                    return;
                    }
                }
            }
        }
    else if (buttonIndex < 0)
        {
         if (!AknLayoutUtils::PenEnabled())
            {
            // Last radio button.
            buttonIndex = iButtonArray.Count() - 1;
            }
         else
            {
            // First table button.
            if (iExtension->iTableNavi &&
                iExtension->iTableNavi->EnterControl(0,0))
                {
                LeaveControl();
                return;
                }
            }
        }

    if (!AknLayoutUtils::PenEnabled())
        {
        buttonObj = iButtonArray[iButtonIndex];
        buttonCtrlObj = buttonObj->iButtonControl;
        buttonCtrlObj->SetCurrentState(KAknSctRadioOff, ETrue);
        iButtonIndex = buttonIndex;
        buttonObj = iButtonArray[iButtonIndex];
        buttonCtrlObj = buttonObj->iButtonControl;
        buttonCtrlObj->SetCurrentState(KAknSctRadioOn, ETrue);
        iExtension->iCurrentCategory =
            iButtonArray[buttonIndex]->iButtonId;
        iCharMap->SetStatusChanged(EAknCharChangedCategory);
        }
    else
        {
        buttonObj = iButtonArray[iButtonIndex];
        buttonObj->SetFocused(EFalse);
        iButtonIndex = buttonIndex;
        buttonObj = iButtonArray[iButtonIndex];
        buttonObj->SetFocused(ETrue);
        }
    }

TBool CAknSctRadioButton::LeaveControl()
    {
    for (TInt i = 0; i < iButtonArray.Count(); i++ )
        {
        iButtonArray[i]->SetFocused(EFalse);
        }
    return ETrue;
    }

TBool CAknSctRadioButton::ExitWithKey(TInt /*aKeycode*/)
    {
    return EFalse;
    }

// ----------------------------------------------------------------------------
// Extension class implementation
// ----------------------------------------------------------------------------
//
CAknCharMapExtension::CAknCharMapExtension() : iSmileyModel(this)
,iSingleClickEnabled( iAvkonAppUi->IsSingleClickCompatible() )
    {
    iObserver = NULL;
    iPictographsBuffer = FeatureManager::FeatureSupported(KFeatureIdJapanesePicto);
    iPictographsBufferGrouping = FeatureManager::FeatureSupported(KFeatureIdJapanesePictographsGrouping);
    iKineticScrolling = CAknPhysics::FeatureEnabled();

    TRAP_IGNORE(iSmileyModel.LoadResourceL());
    }

TTypeUid::Ptr CAknCharMapExtension::MopSupplyObject(TTypeUid aId)
    {
    return MAknsControlContext::SupplyMopObject(aId, iBgContext );
    }

MObjectProvider* CAknCharMapExtension::MopNext()
    {
    return iCharMap;
    }

CAknCharMapExtension::~CAknCharMapExtension()
    {
    delete iCharsSmiley;
    delete iCharsQwerty;
    delete iBgContext;

    delete iRadioButton;
    delete iTitleBuf;

    delete iPageNavi;
    delete iTableNavi;
    delete iCategoryTitle;
    delete iCategoryEntry;
    delete iEntryBuf;
    }

void CAknCharMapExtension::SetCharMapControl(CAknCharMap* aCtrl)
    {
    iCharMapProxy = aCtrl;
    }

MAknSctFocusHandler* CAknCharMapExtension::FocusHandler()
    {
    return iFocusHandler;
    }

CCoeControl* CAknCharMapExtension::FocusedControl()
    {
    return iCharMapProxy;
    }

TBool CAknCharMapExtension::EnterControl(TInt aX, TInt aY)
    {
    if(iCharMapProxy->EnterControl(aX, aY))
        {
        iFocusHandler = this;
        iCharMapProxy->HandleFocusStatusChanged();
        return ETrue;
        }
    else
        {
        return EFalse;
        }
    }

void CAknCharMapExtension::MoveFocus(TInt aX, TInt aY)
    {
    iCharMapProxy->TakeFocus();
    TRAP_IGNORE(iCharMapProxy->MoveFocus(aX, aY));
    }

TBool CAknCharMapExtension::LeaveControl()
    {
    return iCharMapProxy->LeaveControl();
    }

TBool CAknCharMapExtension::ExitWithKey(TInt /*aKeycode*/)
    {
    return ETrue;
    }

void CAknCharMapExtension::ThumbnailLoaded(CSmileyIcon* /*aSmileyIcon*/)
    {
    iCharMapProxy->DrawDeferred();
    }

void CAknCharMapExtension::AnimationChanged(CSmileyIcon* /*aSmileyIcon*/)
    {
    iCharMapProxy->DrawCursor();
    }

TBool CAknCharMapExtension::IsEmotionEnabled() const
    {
    return iIsEnableEmotion;
    }

TBool CAknCharMapExtension::IsShowingEmotion() const
    {
    return iIsShowingEmotion;
    }

TBool CAknCharMapExtension::NeedEmotionSwitchIcon() const
    {
    // Emotion switch char
    TBool needEmotionSwitchIcon = (!AknLayoutUtils::PenEnabled() && IsEmotionEnabled() && !iMenuSct);
    return needEmotionSwitchIcon;
    }

HBufC* CAknCharMapExtension::ReadEmotionHBufCL()
    {
    TInt smileyCount = iSmileyModel.Count();
    HBufC* charsSmiley = HBufC::NewL(smileyCount);
    TPtr charsSmileyPtr(charsSmiley->Des());
    for(TInt id(CSmileyModel::EIconSmiley); id<smileyCount; id++)
        {
        charsSmileyPtr.Append(TEmotionUtils::EmotionChar(id));
        }
    
    return charsSmiley;
    }

void CAknCharMapExtension::LoadEmotionTumbnails(const TDesC& aSctChars)
    {
    for(TInt i(0); i<aSctChars.Length(); i++)
        {
        iSmileyModel.LoadThumbnailAsyn(TEmotionUtils::EmotionId(aSctChars[i]));
        }
    }

void CAknCharMapExtension::SetEmotionSize(const TSize& aSize)
    {
    TInt unit = Min(aSize.iWidth, aSize.iHeight);
    iSmileyModel.SetSize(TSize(unit,unit));
    }

CSmileyIcon* CAknCharMapExtension::EmotionIcon(TChar aEmotionChar)
    {
    if(TEmotionUtils::IsEmotionChar(aEmotionChar))
        {
        return iSmileyModel[TEmotionUtils::EmotionId(aEmotionChar)];
        }
    else
        {
        return NULL;
        }
    }

TBool CAknCharMapExtension::DrawEmotion(CWindowGc& aGc, const TRect& aRect, TChar aEmotionChar)
    {
    CSmileyIcon* icon = EmotionIcon(aEmotionChar);
    if(icon && icon->ReadyToDraw())
        {
        TRect iconRect(TPoint(),icon->Size());
        TInt xoffset = (aRect.Width() - iconRect.Width()) / 2;
        TInt yoffset = (aRect.Height() - iconRect.Height()) / 2;

        aGc.BitBltMasked(aRect.iTl+TPoint(xoffset,yoffset), icon->Image(), iconRect, icon->Mask(), FALSE);
        return ETrue;
        }
    else
        {
        return EFalse;
        }
    }

const TInt KEmotionAnimationRepeatCount = 30; // 30 times
const TInt KEmotionAnimationDelay = 150*1000; // 0.15s

void CAknCharMapExtension::HandleFocusStatusChanged(TChar aChar, TBool aIsFocused)
    {
    CSmileyIcon* lastIcon = EmotionIcon(iLastFocusedSmileyChar);
    if(lastIcon)
        {
        lastIcon->StopAnimation();
        }
    
    CSmileyIcon* focusedIcon = EmotionIcon(aChar);
    if(focusedIcon)
        {
        if(aIsFocused)
            {
            if(iHighlightVisible)
                {
                TRAP_IGNORE(focusedIcon->PlayAnimationL(KEmotionAnimationRepeatCount, KEmotionAnimationDelay));
                }
            }
        else
            {
            focusedIcon->StopAnimation();
            }
        }
    
    iLastFocusedSmileyChar = aChar;
    }


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknCharMapHistory::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CAknCharMapHistory* CAknCharMapHistory::NewL()
    {
    CAknCharMapHistory* self = new (ELeave) CAknCharMapHistory;
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

// -----------------------------------------------------------------------------
// CAknCharMapHistory::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CAknCharMapHistory::ConstructL()
    {
    LoadL();
    }

// -----------------------------------------------------------------------------
// CAknCharMapHistory::CAknCharMapHistory
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CAknCharMapHistory::CAknCharMapHistory()
    {
    }

// Destructor
CAknCharMapHistory::~CAknCharMapHistory()
    {
    ResetArray();
    }

// -----------------------------------------------------------------------------
// CAknCharMapHistory::LoadL()
// Load recent characters from file
// -----------------------------------------------------------------------------
//
TInt CAknCharMapHistory::LoadL()
    {
    // get the value of recently characters
    const TInt length = KHistoryBufferSize * KHistoryBufferCount;
    TBuf<length> buf;

    CRepository* repository = CRepository::NewLC(KCRUidAvkon);
    TInt err = repository->Get(KAknRecentSctData, buf); // Get KAknRecentSctData value
    if (err == KErrNone)
        {
        if (buf.Length() != length) // buffer is not wanted
            {
            buf.Fill(KHistoryEmptyChar, length); // set default characters (default=tab character)
            err = repository->Set(KAknRecentSctData, buf); // Create KAknRecentSctData key
            }
        }
    CleanupStack::PopAndDestroy(repository); // repository
    
    // reset arrary
    ResetArray();

    // set recently characters to array
    TInt parsePos = 0;
    for (TInt i=0; i<EHistoryTypeMax; i++)
        {
        if (err != KErrNone)
            {
            // if err occurs, empty characters are set to recently characters.
            iMixedHistoryArray[i].Fill(KHistoryEmptyChar, KHistoryBufferSize);
            iTextHistoryArray[i].Fill(KHistoryEmptyChar, KHistoryBufferSize);
            }
        else
            {
            // parse from buf
            iMixedHistoryArray[i].Copy(buf.Mid(parsePos, KHistoryBufferSize)); // mixed 
            parsePos += KHistoryBufferSize;
            
            iTextHistoryArray[i].Copy(buf.Mid(parsePos, KHistoryBufferSize)); // text
            parsePos += KHistoryBufferSize;
            }
        }

    if (err != KErrNone)
        {
        iEmotionHistory.Fill(KHistoryEmptyChar, KHistoryBufferSize);
        }
    else
        {
        // parse from buf
        iEmotionHistory.Copy(buf.Mid(parsePos, KHistoryBufferSize));
        }

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CAknCharMapHistory::ResetArray()
// Reset recent arrary
// -----------------------------------------------------------------------------
//
void CAknCharMapHistory::ResetArray()
    {
    for(TInt i=0; i<EHistoryTypeMax; i++)
        {
        iMixedHistoryArray[i].Zero();
        iTextHistoryArray[i].Zero();
        }

    iEmotionHistory.Zero();
    }

// -----------------------------------------------------------------------------
// CAknCharMapHistory::SaveL()
// Save recent characters
// -----------------------------------------------------------------------------
//
TInt CAknCharMapHistory::SaveL()
    {
    // save all recent used characters to buffer
    const TInt length = KHistoryBufferSize * KHistoryBufferCount;
    TBuf<length> buf;
    
    for (TInt i=0; i<EHistoryTypeMax; i++)
        {
        buf.Append(iMixedHistoryArray[i]);
        buf.Append(iTextHistoryArray[i]);
        }
    
    buf.Append(iEmotionHistory);

    // Set KAknRecentSctData value
    CRepository* repository = CRepository::NewLC(KCRUidAvkon);
    TInt err = repository->Set(KAknRecentSctData, buf);
    CleanupStack::PopAndDestroy(repository); // repository
    
    return err;
    }

// -----------------------------------------------------------------------------
// CAknCharMapHistory::RecentString()
// Get recent data
// -----------------------------------------------------------------------------
//
const TDesC& CAknCharMapHistory::RecentString(THistoryType aHistoryType, THistoryFilter aHistoryFilter)
    {
    __ASSERT_ALWAYS((EHistoryTypeFull<=aHistoryType && aHistoryType<EHistoryTypeMax), Panic(EAknPanicInvalidValue));
    
    switch(aHistoryFilter)
        {
        case EHistoryFilterMixed:
            break;
            
        case EHistoryFilterTextOnly:
            return iTextHistoryArray[aHistoryType];
            
        case EHistoryFilterEmotionOnly:
            return iEmotionHistory;

        default:
            break;
        }
    
    return iMixedHistoryArray[aHistoryType];
    }

// -----------------------------------------------------------------------------
// CAknCharMapHistory::InsertChar()
// Insert a character which select on SCT/Picto.
// -----------------------------------------------------------------------------
//
void CAknCharMapHistory::InsertChar(THistoryType aHistoryType, const TChar aChar)
    {
    __ASSERT_ALWAYS((EHistoryTypeFull<=aHistoryType && aHistoryType<EHistoryTypeMax), Panic(EAknPanicInvalidValue));

    InsertCharToHistoryBuf(iMixedHistoryArray[aHistoryType], aChar);

    if(TEmotionUtils::IsEmotionChar(aChar))
        {
        InsertCharToHistoryBuf(iEmotionHistory, aChar);
        }
    else
        {
        InsertCharToHistoryBuf(iTextHistoryArray[aHistoryType], aChar);
        }
    }

void CAknCharMapHistory::InsertCharToHistoryBuf(TDes& aHistoryBuf, const TChar aChar)
    {
    TInt pos = aHistoryBuf.Locate(aChar);
    if(pos != 0)
        {
        if(pos == KErrNotFound)
            {
            aHistoryBuf.SetLength(aHistoryBuf.Length() - 1);
            }
        else
            {
            aHistoryBuf.Delete(pos, 1);
            }
        
        TBuf<1> charBuf;
        charBuf.Append(aChar);
        aHistoryBuf.Insert(0, charBuf);
        }
    }


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknCharMap::LengthOfRecentChar()
// Get the length of the recent charactors.
// -----------------------------------------------------------------------------
//
TInt CAknCharMap::LengthOfRecentChar()
    {
    TInt len(0);
    if ( iChars != NULL )
        {
        for ( TInt index=0; index < iMaxColumns; index++ )
            {
            if ( (*iChars)[index] != KHistoryEmptyChar )
                {
                len++;
                }
            else
                {
                break;
                }
            }
        }
    return len;
    }


EXPORT_C CAknCharMap::CAknCharMap() : iMaxColumns(-1)
    {
    // Must be created here to get the member variables available
    TRAPD(err, iExtension = new (ELeave) CAknCharMapExtension);
    iExtension->iCharMap = this;

    if(err)
        return;

    iExtension->iFlags = 0x00;

    // if feature language is Japanese
    CAknEnv* env = CAknEnv::Static();
    if (env)
        {
        if (env->IsFeatureLanguage(KFeatureIdJapanese))
            {
            iExtension->iJapaneseSctUi = ETrue;
            iExtension->iHasCategoryButtonUi = ETrue;
            }
        }
    iExtension->iFocusHandler = iExtension;
    iExtension->SetCharMapControl(this);
	
    if ( iExtension->iSingleClickEnabled )
        {
        iExtension->iHighlightVisible = EFalse;
        }
    
    DoLayout();
    
    AKNTASHOOK_ADD( this, "CAknCharMap" );
    }

EXPORT_C CAknCharMap::~CAknCharMap()
    {
    AKNTASHOOK_REMOVE();

    delete iCharsBufferFull;
    delete iCharsBufferHalf;
    delete iCharsBufferLower;
    delete iCharsBufferUpper;
    delete iCharsBufferNumeric;
    delete iPictographsBuffer;
    delete iPictographsBuffer2;
    
    delete iSBFrame;
    delete iPictoInterface;

    delete iOffscreenBg;
    delete iBitmapDevice;
    delete iBitmapGc;

    delete iTitleDefault;
    delete iTitleFull;
    delete iTitleHalf;
    delete iTitlePicto;
    delete iTitlePicto2;

    // menu sct replaces the iChars with on HBufC
    if (iExtension->iFlags & EAknCharMapCharsAllocated) // iChars  contains HBufC
        {                                               // so delete it
        delete iChars;
        }


    delete iExtension;
    delete iCharMapHistory;

    iSpecialCharCases.Close();
    iSpecialCharPages.Close();
    iPictographCases.Close();
    iPictographPages.Close();
    MTouchFeedback* feedback = MTouchFeedback::Instance();
    feedback->RemoveFeedbackForControl( this );
   }

void CAknCharMap::DoLayout()
    {
    TAknTextLineLayout specialCharItemLayout;
    if (AknLayoutUtils::PenEnabled() && !Extension()->iMenuSct)
        {
        if ( Layout_Meta_Data::IsLandscapeOrientation() )
            {
            specialCharItemLayout =
                AknLayoutScalable_Avkon::cell_graphic2_pane_t1(1);
            }
        else if (IsJapaneseSctUi())
            {
            specialCharItemLayout =
                AknLayoutScalable_Avkon::cell_graphic2_pane_t1(2);
            }
        else
            {
            specialCharItemLayout =
                AknLayoutScalable_Avkon::cell_graphic2_pane_t1(0);
            }
        }
    else
        {
        specialCharItemLayout =
            AknLayoutScalable_Avkon::cell_graphic_popup_pane_t2();
        }
    iFont = AknLayoutUtils::FontFromId ( specialCharItemLayout.FontId() );
    if (iPictoInterface)
        {
        __ASSERT_ALWAYS(iFont, Panic(EAknPanicNullPointer));
        iCurrentPictographHeight = EHeight16;
        iPictoInterface->Interface()->SelectPictographHeightForFont(*iFont,iCurrentPictographHeight);
        }
    iIsMirrored = AknLayoutUtils::LayoutMirrored();
    iDrawnBefore = EFalse;
    CountMaxColumnsAndCellSizes();
    SizeChanged();

    // load Emotion icon resource, but not load images
    TSize iconSize(iGridItemWidth,iGridItemHeight);
    iconSize.iWidth = iconSize.iWidth * 2 / 3;
    iconSize.iHeight = iconSize.iHeight * 2 / 3;
    Extension()->SetEmotionSize(iconSize);
    }


EXPORT_C void CAknCharMap::ConstructFromResourceL(TResourceReader& aReader)
    {
    CEikDialog* dlg;
    MopGetObject(dlg);
    CEikDialogExtension* dlgExtension = dlg ? dlg->Extension():NULL;
    if (dlgExtension)
        {
        if (CAknEnv::Static()->TransparencyEnabled())
            {
            // CAknCharMapDialog doesn't have extension
            dlgExtension->iPublicFlags.Set(
                CEikDialogExtension::EClipChildControlRect);
            }

        if (AknLayoutUtils::PenEnabled()) // for full screen touch ui.
            {
            dlgExtension->iPublicFlags.Set(
                CEikDialogExtension::EUseVirtualInput);
            }
        else
            {
            dlgExtension->iPublicFlags.Clear(
                CEikDialogExtension::EUseVirtualInput);
            }
        }

    // Special character set.
    ReadCharSetFromResourceL(aReader);

    // Pictograph character set.
    TBool offscreen = EFalse;
    if ( iExtension->iPictographsBuffer )
        {
        CreatePictoCharL();
        offscreen = ETrue;
        }

    SetCharacterCaseL(EAknSCTLowerCase);

    // Recent character set.
    if (!iCharMapHistory)
        {
        iCharMapHistory = CAknCharMapHistory::NewL();
        AppendRecentCharL();
        }

    // Touch support.
    if (AknLayoutUtils::PenEnabled())
        {
        if ( DrawableWindow() )
            {
            EnableDragEvents();
            SetGloballyCapturing(ETrue);
            SetPointerCapture(ETrue);
            }
        }

    // Alternate components.
    if (AknLayoutUtils::PenEnabled())
        {
        if (iExtension->iHasCategoryButtonUi)
            {
            EnableCategoryInputFieldL();
            EnableCategoryButtonsL();
            }
        EnableNavigationButtonsL();
        }
    else
        {
        if (iExtension->iHasCategoryButtonUi)
            {
            EnableCategoryButtonsL();
            }
        }

    // Offscreen background.
    if (offscreen)
        {
        CreateOffscreenBackgroundL();
        }

    iExtension->iBgContext = 
    CAknsFrameBackgroundControlContext::NewL(KAknsIIDQsnFrPopup, TRect(0,0,1,1), TRect(0,0,1,1), EFalse);
    }


EXPORT_C TInt CAknCharMap::HeightInRows()
    {
    return (iShowCasesRef->Count()>1 ? iMaxColumns+1 : iRows);
    }

EXPORT_C void CAknCharMap::SetEmotionModeL(TAknCharMapEmotionMode aEmotionMode)
    {
    TBool isCurrentEnable = iExtension->iIsEnableEmotion;
    
    switch(aEmotionMode)
        {
        case EAknCharMapEmotionUse:
            iExtension->iIsShowingEmotion = EFalse;
            iExtension->iIsEnableEmotion = ETrue;
            break;

        case EAknCharMapEmotionFirst:
            iExtension->iIsShowingEmotion = ETrue;
            iExtension->iIsEnableEmotion = ETrue;
            break;

        default:
            iExtension->iIsShowingEmotion = EFalse;
            iExtension->iIsEnableEmotion = EFalse;
            break;
        }

    if(isCurrentEnable!=iExtension->iIsEnableEmotion && iExtension->NeedEmotionSwitchIcon())
        {
        DisableRecentCharsRow();
        AppendRecentCharL();
        SetCharacterCaseL(iSpecialCharCase);
        }
    }

EXPORT_C void CAknCharMap::SetCharacterCaseL(TInt aCharCase)
    {
    __ASSERT_DEBUG( iExtension, Panic(EAknPanicInvalidResourceData));
    
    // PictoMode
    if(aCharCase & EAknCharMapPictoNoUse)
        {
        SetPictoMode(EAknCharMapPictoNoUse);
        }
    else if(aCharCase & EAknCharMapPictoFirst)
        {
        SetPictoMode(EAknCharMapPictoFirst);
        }

    // EmotionMode
    if(aCharCase & EAknCharMapEmotionNoUse)
        {
        SetEmotionModeL(EAknCharMapEmotionNoUse);
        }
    else if(aCharCase & EAknCharMapEmotionUse)
        {
        SetEmotionModeL(EAknCharMapEmotionUse);
        }
    else if(aCharCase & EAknCharMapEmotionFirst)
        {
        SetEmotionModeL(EAknCharMapEmotionFirst);
        }
    
    // do set character case
    iSpecialCharCase = aCharCase & KCharMapCaseMask;

    if (iChaMapTableCase != EAknCharMapTableSpecialChar)
        {
        if (iCaseIndex == 1)
            {
            iChars = iPictographsBuffer2;
            }
        else
            {
            iChars = iPictographsBuffer;
            }
        iShowCasesRef = &iPictographCases;
        iShowPagesRef = &iPictographPages;
        }
    else
        {
        iShowCasesRef = &iSpecialCharCases;
        iShowPagesRef = &iSpecialCharPages;
        
        // default
        iSpecialCharCase = EAknSCTLowerCase;
        iChars = iCharsBufferLower;
        
        if(iExtension->iCharsSmiley && iExtension->IsShowingEmotion())
            {
            iChars = iExtension->iCharsSmiley;
            }
        else if (iCharsBufferUpper && iSpecialCharCase==EAknSCTUpperCase)
            {
            iChars = iCharsBufferUpper;
            }
        else if (iCharsBufferNumeric && iSpecialCharCase==EAknSCTNumeric)
            {
            iChars = iCharsBufferNumeric;
            }
        else if (iCharsBufferFull && iSpecialCharCase==EAknSCTFullCase)
            {
            iChars = iCharsBufferFull;
            }
        else if (iCharsBufferHalf && iSpecialCharCase==EAknSCTHalfCase)
            {
            iChars = iCharsBufferHalf;
            }
        else if (iExtension->iCharsQwerty && iSpecialCharCase==EAknSCTQwerty)
            {
            iChars = iExtension->iCharsQwerty;
            }
        }

    // calculate page count for all pages
    iSpecialCharPages.Reset(); // reset the current page count for different charsets
    TRAP_IGNORE(
        {
        iSpecialCharPages.AppendL( PageCountFromChars(*iChars) );
        for (TInt i(1); i < iSpecialCharCases.Count(); ++i)
            {
            HBufC* chars = CharsFromCase(iSpecialCharCases[i]);
            if (chars)
                {
                iSpecialCharPages.AppendL( PageCountFromChars(*chars) );
                }
            }
        } );

    __ASSERT_ALWAYS( iChars && iChars->Length()>0, Panic(EAknPanicInvalidResourceData));
    
    iRows = ((iChars->Length() - 1) / iMaxColumns ) + 1 ;
    iFirstVisibleRow = 0;
    iAnimated = EFalse;
    iCursorPos = TPoint(0, 0);

    if ( (iChaMapTableCase!=EAknCharMapTableSpecialChar && !iPictoInterface->Interface()->IsPictograph((*iChars)[0])) || 
         (iChaMapTableCase==EAknCharMapTableSpecialChar && (*iChars)[0]==KHistoryEmptyChar && !Extension()->iMenuSct) )
        {
        iCursorPos = TPoint(0, 1);
        }

    iExtension->iCurrentCategory = Category();
    if (iExtension->iRadioButton)
        {
        iExtension->iRadioButton->SetCurrentCategory(iExtension->iCurrentCategory);
        }

    // Create and set the scb visible even though there is nothing to scroll
    delete iSBFrame;
    iSBFrame=NULL;

    if ( !AknLayoutUtils::PenEnabled() && !Extension()->iMenuSct )    // No scrollbars in use.
        {
        iSBFrame=new(ELeave) CEikScrollBarFrame(this, NULL, ETrue);
        iSBFrame->CreateDoubleSpanScrollBarsL(EFalse, EFalse, ETrue, EFalse); // non-window owning scrollbar
        iSBFrame->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff,CEikScrollBarFrame::EAuto);
        iSBFrame->VerticalScrollBar()->SetMopParent(iExtension);
        UpdateScrollIndicatorL();
        }
    
    iExtension->LoadEmotionTumbnails(*iChars);

    CAknSctPageNavi* pageNavi = Extension()->iPageNavi;
    if(pageNavi)
        {
        pageNavi->MakeVisible(PageCount()>1);
        }
    
    HandleFocusStatusChanged();
    
    }

EXPORT_C void CAknCharMap::SetBuffer(TDes& aSpecialChars)
    {
    iFetcherCharsBuffer = &aSpecialChars;
    }

void CAknCharMap::ReadCharSetFromResourceL(TResourceReader& aReader)
    {
    __ASSERT_DEBUG(iExtension, Panic(EAknPanicInvalidResourceData));

    iChars = NULL;
    
    delete iCharsBufferHalf;
    iCharsBufferHalf = NULL;
    delete iCharsBufferFull;
    iCharsBufferFull = NULL;
    delete iCharsBufferLower;
    iCharsBufferLower = NULL;
    delete iCharsBufferUpper;
    iCharsBufferUpper = NULL;
    delete iCharsBufferNumeric;
    iCharsBufferNumeric = NULL;
    delete iExtension->iCharsQwerty;
    iExtension->iCharsQwerty = NULL;
    delete iExtension->iCharsSmiley;
    iExtension->iCharsSmiley = NULL;

    TInt component_count=aReader.ReadInt16();
    for (TInt ii=0;ii<component_count;ii++)
        {
        TInt component_id=aReader.ReadInt16();
        switch(component_id)
            {
            case EAknSCTLowerCase:
                iCharsBufferLower = aReader.ReadHBufCL();
                break;
            case EAknSCTUpperCase:
                iCharsBufferUpper = aReader.ReadHBufCL();
                break;
            case EAknSCTNumeric:
                iCharsBufferNumeric = aReader.ReadHBufCL();
                break;
            case EAknSCTFullCase:
                iCharsBufferFull = AppendTextL(iCharsBufferFull, aReader.ReadHBufCL());
                break;
            case EAknSCTHalfCase:
                iCharsBufferHalf = AppendTextL(iCharsBufferHalf, aReader.ReadHBufCL());
                break;
            case EAknSCTQwerty:
                 iExtension->iCharsQwerty = aReader.ReadHBufCL();
                 break;
            default:
                break;
            }
        }
    
    iExtension->iCharsSmiley = iExtension->ReadEmotionHBufCL();

    // EFalse is set to iSetRecentSct variable when setting special
    // characters from resouce.
    iSetRecentSct = EFalse;
    }


void CAknCharMap::ReadAndAddCharSetFromResourceL(TResourceReader& aReader)
    {
    ReadCharSetFromResourceL( aReader );

    // Add recent used characters
    if ( iCharMapHistory )
        {
        delete iCharMapHistory;
        iCharMapHistory = NULL;
        }
    iCharMapHistory = CAknCharMapHistory::NewL();
    AppendRecentCharL();
    }

EXPORT_C TSize CAknCharMap::MinimumSize()
    {
    TRect rect;
    if (!AknLayoutUtils::PenEnabled() || Extension()->iMenuSct)
        {
        TRect mainPaneRect;
        if(!AknLayoutUtils::LayoutMetricsRect(
            AknLayoutUtils::EPopupParent, mainPaneRect))
            {
            mainPaneRect = iAvkonAppUi->ClientRect();
            }

        TAknLayoutScalableParameterLimits charMapDialogVariety =
            AknLayoutScalable_Avkon::popup_grid_graphic_window_ParamLimits();

        TInt maxVariety = charMapDialogVariety.LastVariety();

        AknLayoutUtils::TAknCbaLocation location = AknLayoutUtils::CbaLocation();
        TInt maxVarietyOffset = 0;
        TInt varietyOffset = maxVariety + 1;

        if(Layout_Meta_Data::IsLandscapeOrientation())
            {
            varietyOffset = (maxVariety + 1) / KAknSctCBaButtonDirections;
            }

        if(location == AknLayoutUtils::EAknCbaLocationRight)
            {
            maxVarietyOffset = varietyOffset;
            }
        else if(location == AknLayoutUtils::EAknCbaLocationLeft)
            {
            maxVarietyOffset = varietyOffset + varietyOffset;
            }

        TInt varietyNumber = varietyOffset - iRows;

        if(varietyNumber < 0)
            {
            varietyNumber = 0;
            }
        else if(iRows<=0)
            {
            varietyNumber -= 1;
            }

        varietyNumber += maxVarietyOffset;

        TAknLayoutRect popupGridLayRect;
        popupGridLayRect.LayoutRect( mainPaneRect,
            AknLayoutScalable_Avkon::popup_grid_graphic_window(varietyNumber));

        TAknLayoutRect gridWithScrollLayRect;
        gridWithScrollLayRect.LayoutRect(popupGridLayRect.Rect(),
            AknLayoutScalable_Avkon::listscroll_popup_graphic_pane());

        rect = gridWithScrollLayRect.Rect();
        }
    else
        {
        TAknLayoutRect popupGridLayRect;
        popupGridLayRect.LayoutRect(iAvkonAppUi->ApplicationRect(),
            AknLayoutScalable_Avkon::popup_grid_graphic2_window(0));

        rect = popupGridLayRect.Rect();
        }

    return rect.Size();
    }


// This method is needed to set correct initial value to scroll indicator.
EXPORT_C void CAknCharMap::ActivateL()
    {
    CCoeControl::ActivateL();
    if (iRows > iExtension->iMaxVisibleRows)
        {
        UpdateScrollIndicatorL();
        }
    }


EXPORT_C TKeyResponse CAknCharMap::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aModifiers)
    {
    // Other key events.
    if (iExtension->iFocusHandler->FocusedControl() != this)
        {
        return iExtension->iFocusHandler->FocusedControl()->OfferKeyEventL(aKeyEvent, aModifiers);
        }

    // Grid key events.
    if( ((*iChars)[0] == KHistoryEmptyChar) &&
        ((*iChars)[iChars->Length()-1] == KHistoryEmptyChar))
        {
        return EKeyWasConsumed;
        }
    
    TUint code=aKeyEvent.iCode;
	
    // First key event enables the highlight
    if ( iExtension->iSingleClickEnabled && !iExtension->iHighlightVisible )
        {
        if ( code == EKeyUpArrow || code == EKeyDownArrow || 
             code == EKeyLeftArrow || code == EKeyRightArrow || 
             code == EKeyEnter )
            {
            iExtension->iHighlightVisible = ETrue;
            iCursorPos = TPoint( 0, 0 );
            DrawCursor();
            HandleFocusStatusChanged();
            return EKeyWasConsumed;
            }
        }
    
    switch (code)
        {
        case EKeyLeftArrow:
        case '4':
            {
            if (iExtension->iRadioButton && (iCursorPos.iX == 0)) // Radio button.
                {
                if (iExtension->iRadioButton->EnterControl(iCursorPos.iX,iCursorPos.iY))
                    {
                    LeaveControl();
                    break;
                    }
                }

            if (AknLayoutUtils::PenEnabled())
                {
                if (!iIsMirrored)
                    {
                    if ((iCursorPos.iX == 0) && (iCursorPos.iY == ColMin(0)))
                        {
                        if (!Layout_Meta_Data::IsLandscapeOrientation())
                            {
                            // Last table button.
                            if (iExtension->iTableNavi &&
                                iExtension->iTableNavi->EnterControl(TableCount() - 1,0))
                                {
                                LeaveControl();
                                break;
                                }
                            }
                        else
                            {
                            // Right page button.
                            if (iExtension->iPageNavi &&
                                iExtension->iPageNavi->EnterControl(1,0))
                                {
                                LeaveControl();
                                break;
                                }
                            }
                        }
                    }
                else
                    {
                    if (((iCursorPos.iY == ColMax(0)) && (iCursorPos.iX == RowMax(ColMax(0)))))
                        {
                        if (!Layout_Meta_Data::IsLandscapeOrientation())
                            {
                            // Left page button.
                            if (iExtension->iPageNavi &&
                                iExtension->iPageNavi->EnterControl(0,0))
                                {
                                LeaveControl();
                                break;
                                }
                            }
                        else
                            {
                            // First table button.
                            if (iExtension->iTableNavi &&
                                iExtension->iTableNavi->EnterControl(0,0))
                                {
                                LeaveControl();
                                break;
                                }
                            }
                        }
                    }
                }
            MoveFocus(-1,0);
            break;
            }
        case EKeyRightArrow:
        case '6':
            {
            if (iExtension->iRadioButton &&
                (iCursorPos.iX == RowMax(iCursorPos.iY)) &&
                    (iCursorPos.iY <= (iExtension->iRadioButton->Count() - 2)))
                {
                // Radio button.
                if (iExtension->iRadioButton->EnterControl(iCursorPos.iX,iCursorPos.iY+1))
                    {
                    LeaveControl();
                    break;
                    }
                }
            if (AknLayoutUtils::PenEnabled())
                {
                if (!iIsMirrored)
                    {
                    if ((iCursorPos.iY == ColMax(0)) &&
                        (iCursorPos.iX == RowMax(ColMax(0))))
                        {
                        if (!Layout_Meta_Data::IsLandscapeOrientation())
                            {
                            // Left page button.
                            if (iExtension->iPageNavi &&
                                iExtension->iPageNavi->EnterControl(0,0))
                                {
                                LeaveControl();
                                break;
                                }
                            }
                        else
                            {
                            // First table button.
                            if (iExtension->iTableNavi &&
                                iExtension->iTableNavi->EnterControl(0,0))
                                {
                                LeaveControl();
                                break;
                                }
                            }
                        }
                    }
                else
                    {
                    if ((iCursorPos.iY == ColMin(0)) &&
                        (iCursorPos.iX == 0))
                        {
                        if (!Layout_Meta_Data::IsLandscapeOrientation())
                            {
                            // First table button.
                            if (iExtension->iTableNavi &&
                                iExtension->iTableNavi->EnterControl(0,0))
                                {
                                LeaveControl();
                                break;
                                }

                            }
                        else
                            {
                            // Left page button.
                            if (iExtension->iPageNavi &&
                                iExtension->iPageNavi->EnterControl(1,0))
                                {
                                LeaveControl();
                                break;
                                }
                            }
                        }
                    }
                }
            MoveFocus(1,0);
            break;
            }
        case EKeyUpArrow:
        case '2':
            {
            if (AknLayoutUtils::PenEnabled())
                {
                if (iCursorPos.iY == ColMin(iCursorPos.iX))
                    {
                    if (!iExtension->iRadioButton && iCursorPos.iX < TableCount())
                        {
                        // Table button up.
                        if ( iExtension->iTableNavi &&
                            iExtension->iTableNavi->EnterControl(iCursorPos.iX,0))
                            {
                            LeaveControl();
                            break;
                            }
                        }
                    else
                        {
                        if (iCursorPos.iX == MaxCols() - 1)
                            {
                            // Right page button.
                            if ( iExtension->iPageNavi &&
                                iExtension->iPageNavi->EnterControl(1,0))
                                {
                                LeaveControl();
                                break;
                                }
                            }
                        if (Layout_Meta_Data::IsLandscapeOrientation())
                            {
                            if ((!iExtension->iRadioButton &&
                                 (iCursorPos.iX == TableCount())) ||
                               ((iExtension->iRadioButton) &&
                                 (iCursorPos.iX == MaxCols()-2)))
                                {
                                // Left page button.
                                if ( iExtension->iPageNavi &&
                                    iExtension->iPageNavi->EnterControl(0,0))
                                    {
                                    LeaveControl();
                                    break;
                                    }
                                }
                            }
                        // Grid bottom row.
                        if (ColMax(0) > ColMax(iCursorPos.iX))
                            {
                            EnterControl(RowMax(ColMax(0)), ColMax(0));
                            break;
                            }
                        EnterControl(iCursorPos.iX, ColMax( iCursorPos.iX));
                        break;
                        }
                    }
                }
            MoveFocus(0,-1);
            break;
            }
        case EKeyDownArrow:
        case '8':
            {
            if (AknLayoutUtils::PenEnabled())
                {
                if (iCursorPos.iY == ColMax(iCursorPos.iX))
                    {
                    if (iCursorPos.iX > RowMax(ColMax(0)))
                        {
                        // Grid last item.
                        EnterControl(RowMax(ColMax(0)), ColMax(0));
                        break;
                        }
                    if ((iCursorPos.iX == MaxCols() - 1) ||
                        (!Layout_Meta_Data::IsLandscapeOrientation() &&
                            iExtension->iRadioButton &&
                                (iCursorPos.iX == MaxCols() - 2)))
                        {
                        // Right page button.
                        if (iExtension->iPageNavi &&
                            iExtension->iPageNavi->EnterControl(1,0))
                            {
                            LeaveControl();
                            break;
                            }
                        }
                    if ((Layout_Meta_Data::IsLandscapeOrientation() &&
                            !iExtension->iRadioButton &&
                                (iCursorPos.iX == TableCount())) ||
                        (!Layout_Meta_Data::IsLandscapeOrientation() &&
                            (iCursorPos.iX == 0)) ||
                        (Layout_Meta_Data::IsLandscapeOrientation() &&
                            iExtension->iRadioButton &&
                                (iCursorPos.iX == MaxCols() - 2)))
                        {
                        // Left page button.
                        if (iExtension->iPageNavi &&
                            iExtension->iPageNavi->EnterControl(0,0))
                            {
                            LeaveControl();
                            break;
                            }
                        }
                    if (!iExtension->iRadioButton &&
                            iCursorPos.iX < TableCount())
                        {
                         // Table button down.
                        if (iExtension->iTableNavi &&
                            iExtension->iTableNavi->EnterControl(iCursorPos.iX,0))
                            {
                            LeaveControl();
                            break;
                            }
                        }
                    // Grid top row.
                    EnterControl(iCursorPos.iX, ColMin(iCursorPos.iX));
                    break;
                    }
                }
            MoveFocus(0,1);
            break;
            }
        case '5':
        case EKeySpace:
            {
            AppendFocusSctToDestinationBufferL();
            }
            break;
        case EKeyEnter:
        case EKeyOK:
            if(!Extension()->iKeyOkEvent)
                {
                if(AppendFocusSctToDestinationBufferL())
                    {
                    Extension()->iKeyOkEvent = ETrue;
                    }
                else
                    {
                    return EKeyWasNotConsumed;
                    }
                }
            break;
        default:
            return EKeyWasNotConsumed;

        }
    return EKeyWasConsumed;
    }

EXPORT_C TCoeInputCapabilities CAknCharMap::InputCapabilities() const
    {
    return TCoeInputCapabilities(TCoeInputCapabilities::EAllText);
    }

/**
* Control position of this control is registered for skin library when necessary
* in CEikDialogPage::SetDataPosition, so we do not do that in this method.
*/
EXPORT_C void CAknCharMap::SizeChanged()
    {
    
    if (!AknLayoutUtils::PenEnabled() || Extension()->iMenuSct)
        {
        TRect mainPaneRect;
        if(!AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EPopupParent, mainPaneRect))
            {
            mainPaneRect = iAvkonAppUi->ClientRect();
            }

        TAknLayoutScalableParameterLimits charMapDialogVariety =
            AknLayoutScalable_Avkon::popup_grid_graphic_window_ParamLimits();

        TInt maxVariety = charMapDialogVariety.LastVariety();

        AknLayoutUtils::TAknCbaLocation location = AknLayoutUtils::CbaLocation();
        TInt maxVarietyOffset = 0;
        TInt varietyOffset = maxVariety + 1;
        if(Layout_Meta_Data::IsLandscapeOrientation())
            {
            varietyOffset = (maxVariety + 1) / KAknSctCBaButtonDirections;
            }
        if(location == AknLayoutUtils::EAknCbaLocationRight)
            {
            maxVarietyOffset = varietyOffset;
            }
        else if(location == AknLayoutUtils::EAknCbaLocationLeft)
            {
            maxVarietyOffset = varietyOffset + varietyOffset;
            }

        TInt varietyNumber = varietyOffset - iRows;
        if(varietyNumber < 0)
            {
            varietyNumber = 0;
            }
        else if(iRows<=0)
            {
            varietyNumber -= 1;
            }
        varietyNumber += maxVarietyOffset;

        TAknLayoutRect popupGridLayRect;
        popupGridLayRect.LayoutRect(mainPaneRect, AknLayoutScalable_Avkon::popup_grid_graphic_window(varietyNumber));

        TRect relativePopup(TPoint(0,0), popupGridLayRect.Rect().Size());

        TAknLayoutRect gridWithScrollLayRect;
        gridWithScrollLayRect.LayoutRect(relativePopup, AknLayoutScalable_Avkon::listscroll_popup_graphic_pane());

        TAknLayoutRect gridLayRect;
        if (iExtension->iHasCategoryButtonUi)
            {
            gridLayRect.LayoutRect(gridWithScrollLayRect.Rect(), AknLayoutScalable_Avkon::grid_graphic_popup_pane(2));
            }
        else
            {
            gridLayRect.LayoutRect(gridWithScrollLayRect.Rect(), AknLayoutScalable_Avkon::grid_graphic_popup_pane(0));
            }

        // Grid.
        TRect contentRect = Extension()->iMenuSct ? Rect() : gridLayRect.Rect();
        if ( Extension()->iMenuSct )
            {
            contentRect.iBr.iY -= (contentRect.Height() - Rect().Height());
            }
        iOffset.iY = contentRect.iTl.iY + 1;
        iGridTopLeft.iY = contentRect.iTl.iY;
        if ( iIsMirrored )
            {
            iOffset.iX = contentRect.iBr.iX - iGridItemWidth + 1;
            iGridTopLeft.iX = contentRect.iBr.iX - iGridItemWidth;
            }
        else
            {
            iOffset.iX = contentRect.iTl.iX + 1;
            iGridTopLeft.iX = contentRect.iTl.iX;
            }

        // Category buttons.
        if (iExtension && iExtension->iHasCategoryButtonUi)
            {
            if (iExtension->iRadioButton)
                {
                TAknLayoutRect categoryButtonLayRect;
                categoryButtonLayRect.LayoutRect(gridWithScrollLayRect.Rect(),AknLayoutScalable_Avkon::grid_sct_catagory_button_pane());

                TAknLayoutRect oneButtonLayRect;
                oneButtonLayRect.LayoutRect(categoryButtonLayRect.Rect(),AknLayoutScalable_Avkon::cell_sct_catagory_button_pane());

                TSize size(oneButtonLayRect.Rect().Width(), oneButtonLayRect.Rect().Height()*iExtension->iRadioButton->Count());
                TRect rectRadio(categoryButtonLayRect.Rect().iTl, size);
                iExtension->iRadioButton->SetRect(rectRadio);
                }
            }


        // Background context.
        if(iExtension && iExtension->iBgContext)
            {
            TInt varietyNumber = Layout_Meta_Data::IsLandscapeOrientation() ? 1 : 0;
            TAknLayoutRect innerRect;
            innerRect.LayoutRect(relativePopup, AknLayoutScalable_Avkon::bg_popup_window_pane_g1(varietyNumber));
            iExtension->iBgContext->SetFrameRects( relativePopup, innerRect.Rect() );
            }

        TRAP_IGNORE( UpdateScrollIndicatorL() );
        }
    else
        {
        
        TInt variety;
        if (!IsJapaneseSctUi())
            {
            variety = Layout_Meta_Data::IsLandscapeOrientation() ? 3 : 1;
            if(TableCount() > 1) variety--;
            }
        else
            {
            variety = Layout_Meta_Data::IsLandscapeOrientation() ? 5 : 4;
            }
        
        // Popup.
        TAknLayoutRect popupGridLayRect;
        popupGridLayRect.LayoutRect(iAvkonAppUi->ApplicationRect(), AknLayoutScalable_Avkon::popup_grid_graphic2_window(0));
        TRect popupGridRect = popupGridLayRect.Rect();

        // Grid.
        TAknLayoutRect gridLayRect;
        gridLayRect.LayoutRect(popupGridRect, AknLayoutScalable_Avkon::grid_graphic2_pane(variety));
        TRect gridRect = gridLayRect.Rect();

        iOffset.iY = gridRect.iTl.iY + 1;
        iGridTopLeft.iY = gridRect.iTl.iY;
        if ( iIsMirrored )
            {
            iOffset.iX = gridRect.iBr.iX - iGridItemWidth + 1;
            iGridTopLeft.iX = gridRect.iBr.iX - iGridItemWidth;
            }
        else
            {
            iOffset.iX = gridRect.iTl.iX + 1;
            iGridTopLeft.iX = gridRect.iTl.iX;
            }

        // Category
        if (iExtension->iHasCategoryButtonUi && iExtension->iRadioButton) // Radio buttons.
            {
            TAknLayoutRect oneButtonLayRect;
            TAknLayoutRect categoryButtonLayRect;
            TInt oneButtonLayVariety, categoryButtonLayVariety;
            
            if (Layout_Meta_Data::IsLandscapeOrientation())
                {
                oneButtonLayVariety = 5;
                categoryButtonLayVariety = 1;
                }
            else
                {
                oneButtonLayVariety = 4;
                categoryButtonLayVariety = 0;
                }
            
            oneButtonLayRect.LayoutRect(popupGridRect, AknLayoutScalable_Avkon::grid_graphic2_control_pane(oneButtonLayVariety));
            categoryButtonLayRect.LayoutRect(popupGridRect, AknLayoutScalable_Avkon::grid_graphic2_catg_pane(categoryButtonLayVariety));

            TSize size(oneButtonLayRect.Rect().Width(), 
                       oneButtonLayRect.Rect().Height() * iExtension->iRadioButton->Count());
            TRect rectRadio(categoryButtonLayRect.Rect().iTl, size);
            iExtension->iRadioButton->SetRect(rectRadio);
            }

        // Table navigation.
        if (iExtension->iTableNavi)
            {
            TAknLayoutRect tableNaviLayRect;
            tableNaviLayRect.LayoutRect(popupGridRect, AknLayoutScalable_Avkon::grid_graphic2_control_pane(variety));
            iExtension->iTableNavi->SetRect(tableNaviLayRect.Rect());
            }

        // Page navigation.
        if (iExtension->iPageNavi)
            {
            if (PageCount() > 1)
                {
                iExtension->iPageNavi->MakeVisible(ETrue);
                
                TAknLayoutRect pageNaviLayRect;
                pageNaviLayRect.LayoutRect(popupGridRect, AknLayoutScalable_Avkon::graphic2_pages_pane(variety));
                iExtension->iPageNavi->SetRect(pageNaviLayRect.Rect());
                }
            else
                {
                iExtension->iPageNavi->MakeVisible(EFalse);
                }
            }

        // Background context.
        if(iExtension->iBgContext)
            {
            TAknLayoutRect innerRect;
            innerRect.LayoutRect(popupGridRect, AknLayoutScalable_Avkon::bg_popup_window_pane_cp21(variety));

            TRect relativePopupRect(TPoint(0,0), popupGridRect.Size());
            iExtension->iBgContext->SetFrameRects(relativePopupRect,innerRect.Rect());
            }

        }
    }

EXPORT_C void CAknCharMap::HandleResourceChange(TInt aType)
    {
    TRAP_IGNORE(DoHandleResourceChangeL(aType));
    CCoeControl::HandleResourceChange(aType);
    }

void CAknCharMap::DoHandleResourceChangeL(TInt aType)
    {
    if (aType == KEikDynamicLayoutVariantSwitch)
        {
        TInt pos = (iFirstVisibleRow + iCursorPos.iY) * iMaxColumns + iCursorPos.iX;

        // Cursor position before layout switch.
        TInt previousCursorPosition;
        TInt previousLength = iMaxColumns;
        if (pos < previousLength)
            {
            previousCursorPosition = pos; // recent char
            }
        else
            {
            previousCursorPosition = pos - previousLength; // grid.
            }

        // Disabled because the buffer content may change due to diffent layout.
        TBool recentWasSet = iSetRecentSct;
        if (recentWasSet) DisableRecentCharsRow();

        // Calculate the new magnitudes (iMaxColumns, etc.).
        DoLayout();

        // Append right amount of recent characters due to different layout.
        if (recentWasSet) AppendRecentCharL();

        // Sets the character case because the buffer content may have changed.
        SetCharacterCaseL(iSpecialCharCase);

        // Calculates the index position of the cursor in the char table and
        // update the x and y positions for the new grid with it
        TInt currentCursorPosition = previousCursorPosition;
        TInt currentLength = iMaxColumns; // iMaxColumns may have changed.
        if (pos < previousLength) // recent char
            {
            if (pos >= currentLength) // cannot be shown.
                {
                currentCursorPosition = 0;
                }
            }
        else // grid cell
            {
            currentCursorPosition += currentLength;
            }

        // the new first row is the top row on the page where the new focus is.
        iFirstVisibleRow = iExtension->iMaxVisibleRows *
            (currentCursorPosition / (iMaxColumns * iExtension->iMaxVisibleRows));

        // the cursor positions are relative to current page
        iCursorPos.iY = (currentCursorPosition -
            (iMaxColumns * iFirstVisibleRow)) / iMaxColumns;

        iCursorPos.iX = currentCursorPosition -
            (iMaxColumns * iFirstVisibleRow) - (iMaxColumns * iCursorPos.iY);

        iOldCursorPos.iY = (previousCursorPosition -
            (iMaxColumns * iFirstVisibleRow)) / iMaxColumns;

        iOldCursorPos.iX = previousCursorPosition -
            (iMaxColumns * iFirstVisibleRow) - (iMaxColumns * iOldCursorPos.iY);

        // for full screen touch UI.
        CEikDialog* dlg;
        MopGetObject(dlg);
        CEikDialogExtension* dlgExtension = dlg ? dlg->Extension() : NULL;
        if (dlgExtension)
            {
            if (AknLayoutUtils::PenEnabled())
                {
                dlgExtension->iPublicFlags.Set(CEikDialogExtension::EUseVirtualInput);
                }
            else
                {
                dlgExtension->iPublicFlags.Clear(CEikDialogExtension::EUseVirtualInput);
                }
            }

        // Sets alternate UI controls.
        if (iExtension->iHasCategoryButtonUi)
            {
            if (AknLayoutUtils::PenEnabled())
                {
                EnableCategoryInputFieldL();
                EnableNavigationButtonsL();
                }
            else
                {
                DisableCategoryInputFieldL();
                DisableNavigationButtonsL();
                }
            EnableCategoryButtonsL();
            }
        else
            {
            DisableCategoryInputFieldL();
            DisableCategoryButtonsL();
            if (AknLayoutUtils::PenEnabled())
                {
                EnableNavigationButtonsL();
                }
            else
                {
                DisableNavigationButtonsL();
                }
            }

        // and finally updates the page counts (from setcasetable)
        iSpecialCharPages.Reset(); // reset the current page count for different charsets
        iSpecialCharPages.AppendL( PageCountFromChars(*iChars) );
        for (TInt i(1); i < iSpecialCharCases.Count(); ++i)
            {
            HBufC* chars = CharsFromCase(iSpecialCharCases[i]);
            if (chars) iSpecialCharPages.AppendL( PageCountFromChars(*chars) );
            }

        if (iExtension->iPictographsBuffer && iPictoInterface)
            {
            __ASSERT_ALWAYS(iPictoInterface->Interface(), Panic(EAknPanicNullPointer));
            iPictographPages.Reset();
            iPictographCases.Reset();
            iPictographPages.AppendL( PageCountFromChars(*iPictographsBuffer) );
            iPictographCases.AppendL(EAknCharMapTablePicto);
            if (iExtension->iPictographsBufferGrouping)
                {
                iPictographPages.AppendL( PageCountFromChars(*iPictographsBuffer2) );
                iPictographCases.AppendL( EAknCharMapTablePicto2 );
                }
            }

        UpdateScrollIndicatorL();
        RefreshNaviPageL();

        // create the background again as the background size has changed
        // !resize an option but the cost only differs with the creation of the graphic objects!
        CreateOffscreenBackgroundL();
        iOffscreenBgDrawn = EFalse;
        }


    if( aType == KAknsMessageSkinChange )
        {
        iOffscreenBgDrawn = EFalse;
        }
    }

void CAknCharMap::EnableNavigationButtonsL()
    {
    if ( iExtension )
        {
        if ( !iExtension->iTableNavi )
            {
            iExtension->iTableNavi = new(ELeave) CAknSctTableNavi(this, iExtension);
            iExtension->iTableNavi->SetContainerWindowL(*this);
            TResourceReader reader;
            iCoeEnv->CreateResourceReaderLC(reader, R_AVKON_SCT_TABLE_NAVI_CONTROL);
            iExtension->iTableNavi->ConstructFromResourceL(reader);
            iExtension->iTableNavi->SetNonFocusing();
            iExtension->iTableNavi->SetMopParent(iExtension);
            CleanupStack::PopAndDestroy(); // reader
            }

        iExtension->iTableNavi->MakeVisible(ETrue);

        if ( !iExtension->iPageNavi )
            {
            iExtension->iPageNavi = new(ELeave) CAknSctPageNavi(this, iExtension);
            iExtension->iPageNavi->SetContainerWindowL(*this);
            TResourceReader reader;
            iCoeEnv->CreateResourceReaderLC(reader, R_AVKON_SCT_PAGE_NAVI_CONTROL);
            iExtension->iPageNavi->ConstructFromResourceL(reader);
            iExtension->iPageNavi->SetNonFocusing();
            iExtension->iPageNavi->SetMopParent(iExtension);
            CleanupStack::PopAndDestroy(); // reader
            }

        iExtension->iPageNavi->MakeVisible(ETrue);
        }
    }

void CAknCharMap::DisableNavigationButtonsL()
    {
    if ( iExtension && iExtension->iTableNavi )
        {
        iExtension->iTableNavi->MakeVisible( EFalse );
        }
    if ( iExtension && iExtension->iPageNavi )
        {
        iExtension->iPageNavi->MakeVisible( EFalse );
        }
    }

void CAknCharMap::EnableCategoryButtonsL()
    {
    if (!iExtension->iRadioButton)
        {
        iExtension->iRadioButton = new(ELeave) CAknSctRadioButton(this, iExtension);
        iExtension->iRadioButton->SetContainerWindowL(*this);
        TResourceReader reader;
        iCoeEnv->CreateResourceReaderLC(reader, R_AVKON_SCT_CATEGORY_BUTTON_CONTROL);
        iExtension->iRadioButton->ConstructFromResourceL(reader);
        iExtension->iRadioButton->SetNonFocusing();
        iExtension->iRadioButton->SetMopParent(iExtension);
        CleanupStack::PopAndDestroy(); // reader
        }
    iExtension->iRadioButton->MakeVisible(ETrue);
    }

void CAknCharMap::DisableCategoryButtonsL()
    {
    if (iExtension && iExtension->iRadioButton)
        {
        iExtension->iRadioButton->MakeVisible(EFalse);
        }
    }

void CAknCharMap::EnableCategoryInputFieldL()
    {
    TAknLayoutRect popupGridLayRect;
    popupGridLayRect.LayoutRect(iAvkonAppUi->ApplicationRect(),
        AknLayoutScalable_Avkon::popup_grid_graphic2_window(0));

    // Enable title field.
    if (!iExtension->iCategoryTitle)
        {
        iExtension->iCategoryTitle = new(ELeave) CEikLabel;
        iExtension->iCategoryTitle->SetContainerWindowL(*this);
        iExtension->iCategoryTitle->SetTextL(KNullDesC());
        }
    Extension()->iCategoryTitle->SetBrushStyle(CGraphicsContext::ENullBrush);
    TInt variety = Layout_Meta_Data::IsLandscapeOrientation() ? 1 : 0;
    AknLayoutUtils::LayoutLabel(iExtension->iCategoryTitle, popupGridLayRect.Rect(),
        AknLayoutScalable_Avkon::popup_grid_graphic2_window_t1(variety));
    TAknLayoutText titleLayRect;
    titleLayRect.LayoutText(popupGridLayRect.Rect(),
        AknLayoutScalable_Avkon::popup_grid_graphic2_window_t1(variety).LayoutLine());
    TRgb color = titleLayRect.Color();
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    if( skin )
        {
        (void)AknsUtils::GetCachedColor(skin, color,
            KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG6);
        }
    TRAP_IGNORE(AknLayoutUtils::OverrideControlColorL(*(iExtension->iCategoryTitle),
        EColorLabelText, color));
    if (iExtension->iPictographsBuffer && iPictoInterface)
        {
        iExtension->iCategoryTitle->EnablePictographsL(*iPictoInterface);
        }
    iExtension->iCategoryTitle->MakeVisible(ETrue);


    // Enable entry field.
    if (!iExtension->iCategoryEntry)
        {
        iExtension->iCategoryEntry = new(ELeave) CEikLabel;
        iExtension->iCategoryEntry->SetContainerWindowL(*this);
        iExtension->iCategoryEntry->SetTextL(KNullDesC());
        }
    Extension()->iCategoryEntry->SetBrushStyle(CGraphicsContext::ENullBrush);
    AknLayoutUtils::LayoutLabel(iExtension->iCategoryEntry, popupGridLayRect.Rect(),
        AknLayoutScalable_Avkon::popup_grid_graphic2_window_t2(variety));
    TAknLayoutText entryLayRect;
    entryLayRect.LayoutText(popupGridLayRect.Rect(),
        AknLayoutScalable_Avkon::popup_grid_graphic2_window_t2(variety).LayoutLine());
    color = entryLayRect.Color();
    if( skin )
        {
        (void)AknsUtils::GetCachedColor(skin, color,
            KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG6);
        }
    TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL(*(iExtension->iCategoryEntry),
        EColorLabelText, color));
    if (iExtension->iPictographsBuffer && iPictoInterface)
        {
        iExtension->iCategoryEntry->EnablePictographsL(*iPictoInterface);
        }
    iExtension->iCategoryEntry->MakeVisible(ETrue);

    UpdateInputFieldL();
    }

void CAknCharMap::DisableCategoryInputFieldL()
    {
    if (iExtension->iCategoryTitle)
        {
        iExtension->iCategoryTitle->MakeVisible(EFalse);
        }

    if (iExtension->iCategoryEntry)
        {
        iExtension->iCategoryEntry->MakeVisible(EFalse);
        }
    }


void CAknCharMap::Draw(const TRect& /*aRect*/) const
    {
    TInt cursorPos = 0;

    CWindowGc& gc=SystemGc();
    gc.UseFont(iFont);

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );

    TRect rect = Rect();

    if (!AknLayoutUtils::PenEnabled() || Extension()->iMenuSct)
        {
        TRect mainPaneRect;
        if(!AknLayoutUtils::LayoutMetricsRect(
            AknLayoutUtils::EPopupParent, mainPaneRect))
            {
            mainPaneRect = iAvkonAppUi->ClientRect();
            }

        TAknLayoutScalableParameterLimits charMapDialogVariety =
            AknLayoutScalable_Avkon::popup_grid_graphic_window_ParamLimits();

        TInt maxVariety = charMapDialogVariety.LastVariety();

        AknLayoutUtils::TAknCbaLocation location = AknLayoutUtils::CbaLocation();
        TInt maxVarietyOffset = 0;
        TInt varietyOffset = maxVariety + 1;

        if(Layout_Meta_Data::IsLandscapeOrientation())
            {
            varietyOffset = (maxVariety + 1) / KAknSctCBaButtonDirections;
            }

        if(location == AknLayoutUtils::EAknCbaLocationRight)
            {
            maxVarietyOffset = varietyOffset;
            }
        else if(location == AknLayoutUtils::EAknCbaLocationLeft)
            {
            maxVarietyOffset = varietyOffset + varietyOffset; // 2*
            }

        TInt varietyNumber = varietyOffset - iRows;

        if(varietyNumber < 0)
            {
            varietyNumber = 0;
            }
        else if(iRows<=0)
            {
            varietyNumber -= 1;
            }
        varietyNumber += maxVarietyOffset;

        TAknLayoutRect popupGridLayRect;
        popupGridLayRect.LayoutRect(mainPaneRect,
            AknLayoutScalable_Avkon::popup_grid_graphic_window(varietyNumber));

        // Background height.
        TInt backgroundHeightOffset =
            popupGridLayRect.Rect().Height() - rect.iBr.iY;

        rect.iBr.iY += backgroundHeightOffset;
        }
    else
        {
        TAknLayoutRect popupGridLayRect;
        popupGridLayRect.LayoutRect(iAvkonAppUi->ApplicationRect(),
            AknLayoutScalable_Avkon::popup_grid_graphic2_window(0));

        // Background height.
        TInt backgroundHeightOffset =
            popupGridLayRect.Rect().Height() - rect.iBr.iY;

        rect.iBr.iY += backgroundHeightOffset * 2;
        }

    // Grid (main).
    if ( !Extension()->iMenuSct )
        {
        // 1) Draw the background

        // Check if we got an offscreen bitmap allocated for skin background and
        // there is bitmap background in the current skin.
        if ( iOffscreenBg )
            {
            DrawOffscreenBackgroundIfRequired();
            gc.BitBlt( rect.iTl, iOffscreenBg );
            }
        else
            {
            if( CAknEnv::Static()->TransparencyEnabled() )
                {
                TRegionFix<10> clipReg;
                clipReg.AddRect(rect);
                if ( iFirstVisibleRow == 0 && iSetRecentSct )
                    {
                    TPoint pos = iGridTopLeft;
                    TInt endX = pos.iX + iGridItemWidth * iMaxColumns + 1;
                    TInt endY = pos.iY + iGridItemHeight;
                    // eliminate the overlap area between menu sct and the first menu item.
                    if ( Extension()->iMenuSct )
                        {
                        endY--;
                        }
                    clipReg.SubRect( TRect( pos, TPoint( endX, endY ) ) );
                    }
                // Take scroll bar out of clip region
                if (iSBFrame)
                    {
                    clipReg.SubRect(iSBFrame->GetScrollBarHandle(
                        CEikScrollBar::EVertical)->Rect());
                    }
                gc.SetClippingRegion(clipReg);
                }
            AknsDrawUtils::Background( skin, cc, this, gc, rect,KAknsDrawParamNoClearUnderImage);
            if( CAknEnv::Static()->TransparencyEnabled() )
                {
                gc.CancelClippingRegion();
                }
            }

        gc.SetPenStyle(CGraphicsContext::ESolidPen);
        gc.SetBrushStyle(CGraphicsContext::ENullBrush);
        gc.SetPenSize(TSize(1,1));

        // 2) Draw the grid
        DrawGrid(gc);
        }

    // Grid (recent).
    if (iFirstVisibleRow==0 && iSetRecentSct)
        {
        DrawRecentCharFrame(gc);
        }

    // Cell items.
    TInt charIndex = iFirstVisibleRow * iMaxColumns;
    cursorPos = iCursorPos.iX + iCursorPos.iY * iMaxColumns;
    TInt numberOfChars = NumberOfVisibleChars();
    TBool highlighted = EFalse;
    for (TInt j = 0; j < numberOfChars; j++)
        {

        // emotions in next line are all ready to draw
        if((j%iMaxColumns) == 0)
            {
            if(!EmotionsAreAllReadyToDraw(charIndex, iMaxColumns)) break;
            }
        
        // grid is focused and cursor pos is same with the current index.
        if ( iExtension->iMenuSct )
        	{
            highlighted = iExtension->iMenuSctHighlighted && 
                          (iExtension->iFocusHandler->FocusedControl()==this) && 
                          (j==cursorPos);
        	}
        else
        	{
        	highlighted = ((iExtension->iFocusHandler->FocusedControl()==this) && (j==cursorPos));
        	}
        DrawItem(gc, CursorRect(j, charIndex), charIndex, highlighted, EFalse);
        charIndex++;
        }
    iDrawnBefore = ETrue;
    gc.DiscardFont();
    }

//--------------------------------------------------------------
// Return how many chars to be drawn
//--------------------------------------------------------------
//
TInt CAknCharMap::NumberOfVisibleChars() const
    {
    TInt numberOfCharsToBeDrawn = iChars->Length();
    numberOfCharsToBeDrawn -= (iFirstVisibleRow * iMaxColumns);
    if ( numberOfCharsToBeDrawn > (iExtension->iMaxVisibleRows * iMaxColumns))
        {
        numberOfCharsToBeDrawn = iExtension->iMaxVisibleRows * iMaxColumns;
        }
    __ASSERT_DEBUG( numberOfCharsToBeDrawn >= 1, Panic(EAknPanicOutOfRange));

    if(Extension()->iMenuSct)
        {
        return Min(iExtension->iMaxVisibleRows * iMaxColumns, iChars->Length());
        }
    return numberOfCharsToBeDrawn;
    }

/**
*
* Local method to return the RTL mirrored character for the (LTR) input character
*
* The method has buffers ready to accept surrogate pairs when they become supported in the
* descriptor methods.
*
* The return buffer is padded with extra characters that in theory may arise in bidirectional
* conversion, but since only one character is input, no leading "zero width joiner" will be
* at index 0.  Hence, the resulting character at 0 is returned, with no check for the zero width
* joiner.
*/
TChar MirrorChar(TChar a)
    {
    TBuf<2> buf; // ready for when surrogate pairs need handling
    buf.Append(a);
    TBidirectionalState::TRunInfo ri;
    TBidiLogicalToVisual bl2v(buf, ETrue, &ri, 1); // Only 1 run info element passed
    bl2v.Reorder();
    TBuf<2+TBidiLogicalToVisual::KMinCharAvailable> result;
    bl2v.GetVisualLine(result, 0, buf.Length(), 0xFFFF);
    // Always use index 0 as this situation can not result in a zero-width joiner at index 0
    return result[0];  // This return is not surrogate pair-ready
    }

//-------------------------------------------------------------------------
// Set the pen, color, brush, etc. before drawing the frame of a special char
// item.
// Note: The frame is inside the cell.
//-------------------------------------------------------------------------
//
void CAknCharMap::SetItemFrameStyle( CWindowGc& aGc) const
    {
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );
    TRgb colorFrame = AKN_LAF_COLOR(215);
    AknsUtils::GetCachedColor( skin, colorFrame,
        KAknsIIDQsnLineColors, EAknsCIQsnLineColorsCG7 );
    aGc.SetPenColor(colorFrame);
    aGc.SetPenSize(TSize(1,1));
    }

//--------------------------------------------------------------
// Draw the rect edge lines which are inside the cell and around
// the char.
//--------------------------------------------------------------
//
void CAknCharMap::DrawItemFrame( CWindowGc& aGc,
        const TRect& aItemRect, TInt aCharIndex,
        TBool aHighlighted,
        TBool /*aDrawBackground*/ ) const
    {
    SetItemFrameStyle(aGc);

    if(IsRecentChar(aCharIndex))
        {
        // recent char hasn't inner frames.
        return;
        }
    if( aHighlighted )
        {
        aGc.DrawRect( aItemRect );
        }
    }

//--------------------------------------------------------------
// brush the background rect inside the cell.
//--------------------------------------------------------------
//
void CAknCharMap::DrawItemShade( CWindowGc& aGc,
        const TRect& aItemRect, TInt /*aCharIndex*/,
        TBool aHighlighted,
        TBool aDrawBackground ) const
    {

    TRect innerRect = aItemRect;
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );

    if( aHighlighted )
        {
        TRgb color = AKN_LAF_COLOR(210);
		
        if( !( iExtension->iFlags & EAknCharMapPressedDown ) 
            || iExtension->iSingleClickEnabled )
            {
            AknsUtils::GetCachedColor( skin, 
                    color, 
                    KAknsIIDQsnHighlightColors, 
                    EAknsCIQsnHighlightColorsCG1 );
            }
			
        else
            {
            AknsUtils::GetCachedColor( skin, color, KAknsIIDQsnHighlightColors, EAknsCIQsnHighlightColorsCG2 );
            }
        aGc.SetBrushColor(color);
        aGc.Clear( innerRect );
        }
    else if( aDrawBackground )
        {
        if ( iExtension->iBgContext )
            {
            cc = iExtension->iBgContext;
            }
        AknsDrawUtils::Background( skin, cc, this, aGc, innerRect );
        }
    }

void CAknCharMap::DrawItem(
    CWindowGc& aGc,
    const TRect& aSctPosition,
    TInt aCharIndex,
    TBool aHighlighted,
    TBool aDrawBackground ) const
    {
    if (iChaMapTableCase!=EAknCharMapTableSpecialChar && iPictoInterface)
        {
        DrawPicto(aGc, aSctPosition, aCharIndex, aHighlighted, aDrawBackground);
        return;
        }
    
    if ( iExtension->iSingleClickEnabled &&
         !iExtension->iHighlightVisible )
        {
        aHighlighted = EFalse;
        }
    
    DrawItemShade(aGc, aSctPosition, aCharIndex, aHighlighted, aDrawBackground);
    
    DrawItemFrame(aGc, aSctPosition, aCharIndex, aHighlighted, aDrawBackground);

    TAknTextLineLayout specialCharItemLayout;
    if (AknLayoutUtils::PenEnabled() && !Extension()->iMenuSct)
        {
        if ( Layout_Meta_Data::IsLandscapeOrientation() )
            {
            specialCharItemLayout = AknLayoutScalable_Avkon::cell_graphic2_pane_t1(1);
            }
        else if (IsJapaneseSctUi())
            {
            specialCharItemLayout = AknLayoutScalable_Avkon::cell_graphic2_pane_t1(2);
            }
        else
            {
            specialCharItemLayout = AknLayoutScalable_Avkon::cell_graphic2_pane_t1(0);
            }
        }
    else
        {
        specialCharItemLayout = AknLayoutScalable_Avkon::cell_graphic_popup_pane_t2();
        }

    TRect textRect = aSctPosition;
    if( IsRecentChar(aCharIndex) )
        {
        textRect.Move(0, -1);       //because height of recent char frame decreased 1.
        if( Extension()->iMenuSct )
            {
            textRect.Move(0, -1);   //because menu sct will also shrink 1.
            }
        }
    TAknLayoutText textLayout;
    textLayout.LayoutText(textRect, specialCharItemLayout);

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );

    TRgb color;
    TBuf<1> symbol;
    TChar character = '\t';
    character = (*iChars)[ aCharIndex ];

    // Is Mirrored language (Arabic or Hebrew) used as input language
    TBool mirroredLanguage(
        AknTextUtils::CurrentScriptDirectionality() == TBidiText::ERightToLeft);

    //  Obtain mirrored forms
    if ( mirroredLanguage )
        {
        TChar oldCharacter( character );
        character = MirrorChar( oldCharacter );
        }
    // Note: the character is now mirrored.  The following visual substitution may need to be
    // aware of this:

    _LIT(KChar,"%c");

    // Special cases if needed to use PUA symbols on screen
    if ( (character == CEditableText::EParagraphDelimiter) || (character == 0x000A) ) // Line feed
        {
        if ( mirroredLanguage )
            {
            symbol.Format(KChar, KPuaCodeMirroredLineFeedSymbol); // Symbol for mirrored line feed
            }
        else
            {
            symbol.Format(KChar, KPuaCodeLineFeedSymbol); // Symbol for line feed
            }
        }
    else if ( character == CEditableText::ESpace ) // Space
        {
        symbol.Format(KChar, KPuaCodeSpaceSymbol); // Symbol for space
        }
    else if ( character == 0x3000 ) // Full width Space
        {
        symbol.Format(KChar, KPuaCodeFullWidthSpaceSymbol); // Symbol for space
        }
    else if ( character == 0x200E ) // RLM
        {
        symbol.Format(KChar, KPuaCodeRightToLeftSymbol); // Symbol for RLM
        }
    else if ( character == 0x200F ) // LRM
        {
        symbol.Format(KChar, KPuaCodeLeftToRightSymbol); // Symbol for LRM
        }
    else if ( ( character == 0x0E31 ||
        0x0E33 <= character && character <= 0x0E3A) ||
        (0x0E47 <= character && character <= 0x0E4E) ) // Thai SCT-cases
        {
        symbol.Format(KChar, TUint(character)+KThaiSCTCombiningSymbolAdd);
        }
    else if ( character == KHistoryEmptyChar )
        {
        symbol.Format(KChar, KHistoryEmptyCharForDisplay);
        }
    else  // Defaul case - show symbol as it is
        {
        symbol.Format(KChar, static_cast<TInt>(character));
        }

    if ( aHighlighted )
        {
        AknsUtils::GetCachedColor( skin, color,
            KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG24 );
        }
    else
        {
        AknsUtils::GetCachedColor( skin, color,
            KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG19 );
        }
    
    if(TEmotionUtils::IsEmotionChar(symbol[0]))
        {
        iExtension->DrawEmotion(aGc, textLayout.TextRect(), symbol[0]);
        }
    else
        {
        textLayout.DrawText( aGc, symbol, EFalse, color );
        }
    
    }


//-------------------------------------------------------
// Set the color, pen, style for drawing recent char map
// frame
//-------------------------------------------------------
//
void CAknCharMap::SetRecentCharFrameStyle( CWindowGc& aGc) const
    {
    TRgb colorRecentLine = AKN_LAF_COLOR(215);
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    AknsUtils::GetCachedColor( skin, colorRecentLine,
            KAknsIIDQsnLineColors, EAknsCIQsnLineColorsCG7 );
    aGc.SetPenColor(colorRecentLine);
    aGc.SetPenSize(TSize(2,2));
    }

//-------------------------------------------------------
// Draw the outter thick frame for the all recent chars.
//-------------------------------------------------------
//
void CAknCharMap::DrawRecentCharFrame( CWindowGc& aGc) const
    {
    MAknsSkinInstance*   skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = iExtension->iBgContext;
    if ( !cc )
        {
        cc = AknsDrawUtils::ControlContext( this );
        }

    TPoint pos = iGridTopLeft;
    TInt endX = pos.iX + iGridItemWidth * iMaxColumns + 1;
    TInt endY = pos.iY + iGridItemHeight;
    TRect drawRect(TPoint(pos.iX, pos.iY), TPoint(endX, endY));
    // eliminate the overlap area between menu sct and the first menu item.
    if ( Extension()->iMenuSct )
        {
        drawRect = Rect();
        endY--;
        }

    AknsDrawUtils::Background( skin, cc, this, aGc, drawRect );

    SetRecentCharFrameStyle(aGc);
    if(iIsMirrored)
        {
        pos.iX = iGridTopLeft.iX - ((iMaxColumns - 1) * iGridItemWidth);
        endX = iGridTopLeft.iX + iGridItemWidth + 1;
        }

    aGc.DrawRect( TRect(TPoint(pos.iX-1, pos.iY-1), TPoint(endX, endY)));
    
    MTouchFeedback* feedback = MTouchFeedback::Instance();
    CFeedbackSpec* spec = CFeedbackSpec::New();

    if ( spec && feedback )
        {
        CAknCharMap* mutableThis = MUTABLE_CAST( CAknCharMap* ,this );
        TInt recentChars = mutableThis->LengthOfRecentChar();
        TRect rect;
        spec->AddFeedback( ETouchEventStylusDown, 
                           ETouchFeedbackBasicItem );
        rect.SetRect( pos, TPoint( pos.iX + recentChars * iGridItemWidth, pos.iY + iGridItemHeight ));
        if ( iIsMirrored )
            {
            TInt emptyRecentSlots = iMaxColumns - recentChars;
            rect.Move( emptyRecentSlots * iGridItemWidth, 0 );
            }
        feedback->SetFeedbackArea( this, KAreaIdRecent, rect, spec );
        
        delete spec;
        }
    }

//-------------------------------------------------------
// Set the pen, color, brush, etc. to draw the char map
// grid
//-------------------------------------------------------
//
void CAknCharMap::SetGridStyle( CWindowGc& aGc) const
    {
    TRgb colorLine = AKN_LAF_COLOR(219);
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    AknsUtils::GetCachedColor( skin, colorLine,
            KAknsIIDQsnLineColors, EAknsCIQsnLineColorsCG5 );
    aGc.SetPenColor(colorLine);
    aGc.SetPenSize(TSize(1,1));
    }

//-------------------------------------------------------
// draw the char map grid
// Note: only draw the grid, do not draw the recent char
// map frame.
//-------------------------------------------------------
//
void CAknCharMap::DrawGrid( CWindowGc& aGc) const
    {
    SetGridStyle(aGc);

    //
    // a better method: (0~MaxChars) do:[:each| each drawRect.]
    //
    const TSize gridItemRectSize( iGridItemWidth + 1, iGridItemHeight + 1);
    TInt numberOfCells = NumberOfVisibleChars();
    TPoint pos = iGridTopLeft;
    TInt ii=0;
    if (iFirstVisibleRow == 0 && iSetRecentSct)
        {
        pos.iY += iGridItemHeight;  //skip the recent char area
        ii=iMaxColumns;
        }
    else
        {
        // remove area for recent characters because they does not exist in this view
        MTouchFeedback* feedback = MTouchFeedback::Instance();
        if ( feedback )
            {
            feedback->RemoveFeedbackArea( this, KAreaIdRecent );
            }
        }
    for(; ii < numberOfCells; ++ii)
        {
        aGc.DrawRect(TRect( pos, gridItemRectSize ));

        if ( iIsMirrored )
            {
            pos.iX -= iGridItemWidth;
            }
        else
            {
            pos.iX += iGridItemWidth;
            }

        if( (ii+1) % iMaxColumns == 0 )
            {
            pos.iX  = iGridTopLeft.iX;   //reset for each row.
            pos.iY += iGridItemHeight;
            }
        }
    MTouchFeedback* feedback = MTouchFeedback::Instance();
    CFeedbackSpec* spec = CFeedbackSpec::New();

    if ( feedback && spec )
        {
        TInt orphans = NumberOfVisibleChars() % iMaxColumns;
        TInt rows = NumberOfVisibleChars() / iMaxColumns;
        CAknCharMap* mutableThis = MUTABLE_CAST( CAknCharMap* ,this );
        TInt recentChars = mutableThis->LengthOfRecentChar();    
        TRect rectMain;
        TPoint nextTopLeft = iGridTopLeft;    

        if ( CurrentPage() == 1 )
            {
            nextTopLeft.iY += iGridItemHeight;
            if ( rows > 0 )
                rows--;
            }

        rectMain.SetRect( nextTopLeft, TPoint(nextTopLeft.iX + iMaxColumns * iGridItemWidth, nextTopLeft.iY + rows * iGridItemHeight) );
        if ( iIsMirrored )
            {
            rectMain.Move( ( 1 - iMaxColumns ) * iGridItemWidth, 0 );
            }

        spec->AddFeedback( ETouchEventStylusDown, 
                           ETouchFeedbackBasicItem );
        if ( rows )
            {
            feedback->SetFeedbackArea( this, KAreaIdMain, rectMain, spec );
            }
        else
            {
            feedback->RemoveFeedbackArea( this, KAreaIdMain );
            }

        nextTopLeft.iY = rectMain.iBr.iY;
            
        if ( orphans )
            {
            TRect rectOrphans;
            rectOrphans.SetRect( TPoint( iGridTopLeft.iX, pos.iY), TPoint( iGridTopLeft.iX + orphans * iGridItemWidth, pos.iY + iGridItemHeight) );
            if ( iIsMirrored )
                {
                rectOrphans.Move( ( 1 - orphans ) * iGridItemWidth, 0 );
                }

            feedback->SetFeedbackArea( this, KAreaIdTail, rectOrphans, spec );
            }
        else
            {
            // remove feedback area for tail area because all rows of grid has maximum number of characters
            feedback->RemoveFeedbackArea( this, KAreaIdTail );
            }
        
        delete spec;
        }        
    }

// Optimizes drawing. Only cursor is drawn.
void CAknCharMap::DrawCursor() const
    {
    // Whole SCT has to be drawn at least once.
    // If the user presses arrow key before SCT has been drawn,
    // only cursor position is drawn without this check.
    if ( !iDrawnBefore )
        {
        DrawNow();
        }
    else
        {
        CWindowGc& gc = SystemGc();
        // Only redraw old and new cursor position cells
        if( !CAknEnv::Static()->TransparencyEnabled() )
            {
            ActivateGc();
            gc.UseFont(iFont);
            }

        TInt cursorPos = 0;
        if ( iOldCursorPos != iCursorPos )
            {
            // Redraw only if old pos different from current pos
            cursorPos = iOldCursorPos.iX + iOldCursorPos.iY * iMaxColumns;
            DrawCell( cursorPos, EFalse );
            }

        cursorPos = iCursorPos.iX + iCursorPos.iY * iMaxColumns;
        DrawCell( cursorPos, (iExtension->iFocusHandler->FocusedControl()==this) );

        if( !CAknEnv::Static()->TransparencyEnabled() )
            {
            gc.DiscardFont();
            DeactivateGc();
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknCharMap::DrawCell
// -----------------------------------------------------------------------------
//
void CAknCharMap::DrawCell(
    TInt aCursorPos,
    TBool aHighLighted ) const
    {
    // calculate character index
    TInt charIndex = aCursorPos + iFirstVisibleRow * iMaxColumns;
    if(charIndex >= iChars->Length())
        {
        return;
        }

    // If we are only redrawing for animations, no need to draw non-animated items.
    if (iChaMapTableCase!=EAknCharMapTableSpecialChar && iPictoInterface)
        {
        if ( iAnimated && 
             !iPictoInterface->Interface()->IsAnimated((*iChars)[charIndex],iCurrentPictographHeight) )
            {
            return;
            }
        }

    TRect rect = CursorRect( aCursorPos, charIndex );

    if( CAknEnv::Static()->TransparencyEnabled() )
        {

        const TBool backedUp = IsBackedUp();
        if ( !backedUp )
            {
            Window().Invalidate( rect );
            Window().BeginRedraw( rect );
            }

        ActivateGc();
        CWindowGc& gc = SystemGc();
        gc.UseFont(iFont);

        DrawItem( SystemGc(), rect, charIndex, aHighLighted, ETrue );

        gc.DiscardFont();
        DeactivateGc();

        if ( !backedUp )
            {
            Window().EndRedraw();
            }
        }
    else
        {
        if ( !Extension()->iMenuSct )
            {
            Window().Invalidate( rect );
            Window().BeginRedraw( rect );
            DrawItem( SystemGc(), rect, charIndex, aHighLighted, ETrue );
            Window().EndRedraw();
            }
        else
            {
            DrawItem( SystemGc(), rect, charIndex, aHighLighted, ETrue );
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknCharMap::CursorRect
// -----------------------------------------------------------------------------
//
TRect CAknCharMap::CursorRect( TInt aCursorPos, TInt aCharIndex) const
    {
    TPoint pos = iOffset;

    if (iIsMirrored)
        {
        pos.iX -= (aCursorPos % iMaxColumns) * iGridItemWidth;
        }
    else // Not mirrored
        {
        pos.iX += (aCursorPos % iMaxColumns) * iGridItemWidth;
        }

    pos.iY += (aCursorPos / iMaxColumns) * iGridItemHeight;
    TRect res = TRect( pos, TSize( iGridItemWidth - 2, iGridItemHeight - 2 ) );
    if(IsRecentChar(aCharIndex))
        {
        res.iBr.iY --; //because the width of recent char frame is 2 but not 1.
        }
     // Eliminate the overlap between menu sct and the first menu option' item
     if ( Extension()->iMenuSct )
        {
        res.iBr.iY --;
        }
    return res;
    }

// -----------------------------------------------------------------------------
// CAknCharMap::MoveCursorL
// -----------------------------------------------------------------------------
//
void CAknCharMap::MoveCursorL(TInt aDeltaX, TInt aDeltaY)
    {
    __ASSERT_DEBUG(
        (aDeltaX <= 1) && (aDeltaX >= -1) &&
        (aDeltaY <= 1) && (aDeltaY >= -1) &&
        ((aDeltaX * aDeltaY) == 0), Panic(EAknPanicOutOfRange));

    if (iIsMirrored)
        aDeltaX = -aDeltaX;

    iOldCursorPos = iCursorPos;
    TInt oldFirstVisibleRow = iFirstVisibleRow;

    TInt globalYPos = iCursorPos.iY + iFirstVisibleRow;
    TInt lastColumnOnLastRow(0);
    if ( Extension()->iMenuSct )
        {
        lastColumnOnLastRow = LengthOfRecentChar() - 1;
        }
    else
        {
        lastColumnOnLastRow = (iChars->Length() - 1) % iMaxColumns;
        }

    TInt checktable(-1);
    TInt skipchar = aDeltaX != 0 ? 1: 0;
    TBool caseChange(EFalse);

    // First line is NULL when Cursor was second line
    if ( (iCursorPos.iY+iFirstVisibleRow == 1) && 
         ( (iChaMapTableCase!=EAknCharMapTableSpecialChar && !iPictoInterface->Interface()->IsPictograph((*iChars)[0])) || 
           (iChaMapTableCase==EAknCharMapTableSpecialChar && (*iChars)[0]==KHistoryEmptyChar) ) 
       )
        {
        caseChange = ETrue;
        // Cursor was on the second line
        if (aDeltaY < 0)
            {
            globalYPos--;
            }
        // Cursor was on the second line and first position
        if (aDeltaX < 0 && iCursorPos.iX == 0)
            {
            globalYPos--;
            //iCursorPos.iY = 0;
            iCursorPos.iX = 0;
            }
        }
    else
        {
        TInt delta = aDeltaX != 0 ? aDeltaX: aDeltaY;
        TInt next = aDeltaX != 0 ? aDeltaX: 0;
        TInt charIndex = iCursorPos.iX +
                (iCursorPos.iY + aDeltaY + iFirstVisibleRow) * iMaxColumns; //the x index includes the current row

        for(TInt i(0); i <= iMaxColumns; ++i)
            {
            if (aDeltaY < 0 && charIndex < 0)
                {
                charIndex = 0;
                caseChange = ETrue; // prev case
                }
            if (aDeltaY > 0 && iChars->Length() <= charIndex) // index 0 length 1 etc.
                {
                // set Position(iCursorPos.iX, 0)
                charIndex = iChars->Length() - 1;//iCursorPos.iX;
                i = charIndex;
                caseChange = ETrue; // next case
                }
            if (aDeltaX < 0 && charIndex <= 0)
                {
                charIndex = iChars->Length() - 1;
                caseChange = ETrue; // prev case
                }
            if (aDeltaX > 0 && iChars->Length() - 1 <= charIndex)
                {
                charIndex = 0;
                caseChange = ETrue; // next case
                }
            if (caseChange && iShowCasesRef->Count() > 1)
                {
                // change case
                break;
                }
            if ( (iChaMapTableCase!=EAknCharMapTableSpecialChar && iPictoInterface->Interface()->IsPictograph((*iChars)[charIndex+next])) || 
                 (iChaMapTableCase==EAknCharMapTableSpecialChar && (*iChars)[charIndex+next]!=KHistoryEmptyChar) )
                {
                break;
                }
            charIndex += delta;
            skipchar++;
            }
        }

    if (aDeltaX < 0)
        {
        // Cursor was moved to left.
        if (iCursorPos.iX > skipchar - 1)
            {
            iCursorPos.iX -= skipchar;
            }
        else
            {
            if (skipchar > iMaxColumns)
                {
                globalYPos--;
                iCursorPos.iX = iMaxColumns;
                }
            // Go to previous line
            globalYPos--;
            if (globalYPos < 0)
                {
                // Cursor was on the first line - go to last line.
                globalYPos = iRows - 1;
                // x - position to the last item on the last row.
                iCursorPos.iX = lastColumnOnLastRow;
                checktable = iMaxColumns;
                }
            else
                {
                // x - position to last column.
                iCursorPos.iX = iMaxColumns - skipchar;
                }
            }
        }

    if (aDeltaX > 0)
        {
        // Cursor was moved to right.
        if (globalYPos < iRows - 1)
            {
            // Not in the last row.
            if (iCursorPos.iX < iMaxColumns - skipchar)
                {
                // If not on the last columns, move cursor to next column.
                iCursorPos.iX += skipchar;
                }
            else
                {
                // Cursor was on last column,
                // move to first column of the next line.
                iCursorPos.iX = 0;
                globalYPos++;
                }
            }
        else
            {
            // Currently on the last row.
            if ( iCursorPos.iX < lastColumnOnLastRow )
                {
                // If there are more items on this row, move cursor to next item.
                iCursorPos.iX++;
                }
            else
                {
                // No more item on the current row.
                // Move to first item on the first row.
                iCursorPos.iX = 0;
                checktable = 0;
                globalYPos = 0;
                }
            }
        }

    if (aDeltaY < 0)
        {
        iCursorPos.iX -= skipchar;
        if (iCursorPos.iX < 0)
            {
            iCursorPos.iX += (iMaxColumns - 1);
            globalYPos--;
            }
        // Cursor was moved to up.
        if (globalYPos > 0)
            {
            // Cursor was not on the first line - move it to previous row.
            globalYPos--;
            }
        else
            {
            checktable = iCursorPos.iX;
            // Move cursot to last to row.
            globalYPos = iRows - 1;
            if (iCursorPos.iX > lastColumnOnLastRow)
                {
                // No items in the current column on the last row -
                // move cursor to last item on the row.
                iCursorPos.iX = lastColumnOnLastRow;
                }
            }
        }

    if (aDeltaY > 0)
        {
        iCursorPos.iX = (iCursorPos.iX + skipchar) % iMaxColumns;
        globalYPos += (iCursorPos.iX + skipchar) / iMaxColumns;
        // Cursor was moved to down.
        if (globalYPos < iRows - 1)
            {
            // Cursor is not on the last row. Move cursor to next row.
            globalYPos++;
            if (globalYPos == iRows - 1 && iCursorPos.iX > lastColumnOnLastRow)
                {
                // No items in the current column on the last row -
                // move cursor to last item on the row.
                iCursorPos.iX = lastColumnOnLastRow;
                }
            }
        else
            {
            // Cursor was at the last row - move it to the first row.
            globalYPos = 0;
            checktable = iCursorPos.iX;
            }
        }
    iCursorPos.iY = globalYPos - iFirstVisibleRow;

    if (globalYPos < iFirstVisibleRow)
        {
        // Cursor was moved from the top row.
        if (globalYPos <= 0)
            {
            iFirstVisibleRow = 0;
            iCursorPos = TPoint(iCursorPos.iX, 0);
            }
        else
            {
            // If cursor was moved up out of the visible area - show it again.
            iFirstVisibleRow -= iExtension->iMaxVisibleRows;
            iCursorPos = TPoint(iCursorPos.iX, iExtension->iMaxVisibleRows - 1);
            }
        }

    if (globalYPos > iFirstVisibleRow + iExtension->iMaxVisibleRows - 1)
        {
        if (globalYPos == iRows - 1)
            {
            // When cursor has moved from the top line,
            // it is adjusted to a page boundary.
            iFirstVisibleRow = VisibleRows();
            iCursorPos = TPoint(
                iCursorPos.iX,
                (iRows - 1) % iExtension->iMaxVisibleRows
                );
            }
        else
            {
            // If cursor was moved down out of the visible area - show it again.
            iFirstVisibleRow += iExtension->iMaxVisibleRows;
            iCursorPos = TPoint(iCursorPos.iX, 0);
            }
        }

    TInt increment(1);
    if (aDeltaY < 0 || aDeltaX < 0)
        {
        increment = -1;
        }
    if (checktable >= 0 && SwitchAnotherTableL(increment) > 0)
        {
        TInt lastColumnOnLastRow = ((iChars->Length() - 1) % iMaxColumns);
        TPoint pt(checktable, 0);
        if (aDeltaY < 0 || aDeltaX < 0)
            {
            iFirstVisibleRow =
                ((*iShowPagesRef)[iCaseIndex] - 1) * iExtension->iMaxVisibleRows;
            pt.iX = Min(pt.iX, lastColumnOnLastRow);
            pt.iY = iRows - 1;
            if (iRows > iExtension->iMaxVisibleRows)
                {
                pt.iY -= (((iRows-1) / iExtension->iMaxVisibleRows) * iExtension->iMaxVisibleRows);
                }

            }
        else if (iRows == 1)
            {
            pt.iX = Min(pt.iX, lastColumnOnLastRow);
            }
        else if (caseChange)
            {
            // When first line is NULL, cursor is moved to the second line
            TInt index = pt.iX + (pt.iY + iFirstVisibleRow) * iMaxColumns;
            for (; index >= 0 ; index--)
                {
                if ( (iChaMapTableCase!=EAknCharMapTableSpecialChar && iPictoInterface->Interface()->IsPictograph((*iChars)[index])) || 
                     (iChaMapTableCase==EAknCharMapTableSpecialChar && (*iChars)[index] != KHistoryEmptyChar) )
                    {
                    break;
                    }
                }
            if (index < 0)
                {
                pt.iY = 1;
                }
            else
                {
                pt.iX = index;
                }
            }
        
        HandleFocusStatusChanged();

        iCursorPos = pt;
        UpdateScrollIndicatorL();
        DrawNow();
        }
    else
        {
        if (caseChange)
            {
            TPoint pt(iCursorPos);
            // When first line is NULL, cursor is moved to the second line
            TInt index = pt.iX + (pt.iY + iFirstVisibleRow) * iMaxColumns;
            for (; index >= 0 ; index--)
                {
                if ( (iChaMapTableCase!=EAknCharMapTableSpecialChar && iPictoInterface->Interface()->IsPictograph((*iChars)[index])) || 
                     (iChaMapTableCase==EAknCharMapTableSpecialChar && (*iChars)[index]!=KHistoryEmptyChar) )
                    {
                    break;
                    }
                }
            if (index < 0)
                {
                pt.iY = 1;
                }
            else
                {
                pt.iX = (index % iMaxColumns);
                }
            iCursorPos = pt;
            }

        if ((iRows > iExtension->iMaxVisibleRows) &&
            (iOldCursorPos.iY + oldFirstVisibleRow != iCursorPos.iY + iFirstVisibleRow))
            {
            UpdateScrollIndicatorL();
            }
        
        HandleFocusStatusChanged();

        if (oldFirstVisibleRow == iFirstVisibleRow)
            {
                // Draw only cursor if the view to the content was not scrolled.
            DrawCursor();
            }
        else
            {
            DrawNow();
            }
        }
    }

void CAknCharMap::UpdateScrollIndicatorL()
    {
    if ( !iSBFrame )
        {
        return;
        }
    TEikScrollBarModel hSbarModel;
    TEikScrollBarModel vSbarModel;

    TEikScrollBarFrameLayout layout;

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

    TInt varietyNumber = varietyOffset - iRows;

    // if more lines than possible to show, use the default
    // (the biggest grid) variety
    if(varietyNumber < 0)
        varietyNumber = 0;
    // if zero rows, use the minimum
    else if(iRows<=0)
        varietyNumber -= 1;

    //add the varietyoffset
    varietyNumber += maxVarietyOffset;

    // Layout the dialog size
    TAknLayoutRect dialogLayRect;
    dialogLayRect.LayoutRect( mainPaneRect,
        AknLayoutScalable_Avkon::popup_grid_graphic_window(varietyNumber));

    TRect dialogRect = dialogLayRect.Rect();

    // Get the layout of the actual character grid with scrollbar
    TAknLayoutRect gridWithScrollLayRect;

    gridWithScrollLayRect.LayoutRect(TRect(TPoint(0,0),TSize(dialogRect.Size())),
        AknLayoutScalable_Avkon::listscroll_popup_graphic_pane());

    // Calculate the relative rect for the grid
    TRect parent = gridWithScrollLayRect.Rect();

    TAknWindowComponentLayout scrollbarLayout;
    if (iExtension->iHasCategoryButtonUi)
        {
        scrollbarLayout = AknLayoutScalable_Avkon::scroll_pane_cp5(1);
        }
    else
        {
        scrollbarLayout = AknLayoutScalable_Avkon::scroll_pane_cp5(0);
        }

    vSbarModel.iScrollSpan = PageCount() * iExtension->iMaxVisibleRows;
    vSbarModel.iThumbSpan = iExtension->iMaxVisibleRows;

    if (iSBFrame && iSBFrame->TypeOfVScrollBar() == CEikScrollBarFrame::EDoubleSpan)
        {
        // For EDoubleSpan type scrollbar
        vSbarModel.iThumbPosition = (CurrentPage()-1) * iExtension->iMaxVisibleRows;
        TAknDoubleSpanScrollBarModel hDsSbarModel(hSbarModel);
        TAknDoubleSpanScrollBarModel vDsSbarModel(vSbarModel);

        iSBFrame->Tile(&vDsSbarModel);
        AknLayoutUtils::LayoutVerticalScrollBar(iSBFrame, parent,
        scrollbarLayout);
        iSBFrame->SetVFocusPosToThumbPos(vDsSbarModel.FocusPosition());
        }
    else
        {
        // For EArrowHead type scrollbar
        vSbarModel.iThumbPosition = iCursorPos.iY + iFirstVisibleRow;
        iSBFrame->TileL(&hSbarModel,&vSbarModel,parent,parent,layout);
        iSBFrame->SetVFocusPosToThumbPos(vSbarModel.iThumbPosition);
        }
    }

void CAknCharMap::Reserved_1()
    {
    }

void CAknCharMap::Reserved_2()
    {
    }

const TDesC* CAknCharMap::LowerCaseCharacters() const
    {
    return iCharsBufferLower;
    }

const TDesC* CAknCharMap::UpperCaseCharacters() const
    {
    return iCharsBufferUpper;
    }

const TDesC* CAknCharMap::NumericCharacters() const
    {
    return iCharsBufferNumeric;
    }

void CAknCharMap::CopyCharactersL( const CAknCharMap& aCharMap )
    {
    const TDesC* chars = aCharMap.LowerCaseCharacters();
    if ( chars )
        {
        delete iCharsBufferLower;
        iCharsBufferLower = NULL;
        if (Extension()->iMenuSct)
            {
            iCharsBufferLower = chars->Mid(iMaxColumns).AllocL();
            }
        else
            {
            iCharsBufferLower = chars->AllocL();
            }
        }

    chars = aCharMap.UpperCaseCharacters();
    if ( chars )
        {
        delete iCharsBufferUpper;
        iCharsBufferUpper = NULL;
        if (Extension()->iMenuSct)
            {
            iCharsBufferUpper = chars->Mid(iMaxColumns).AllocL();
            }
        else
            {
            iCharsBufferUpper = chars->AllocL();
            }
        }

    chars = aCharMap.NumericCharacters();
    if ( chars )
        {
        delete iCharsBufferNumeric;
        iCharsBufferNumeric = NULL;
        if (Extension()->iMenuSct)
            {
            iCharsBufferNumeric = chars->Mid(iMaxColumns).AllocL();
            }
        else
            {
            iCharsBufferNumeric = chars->AllocL();
            }
        }

    chars = NULL;
    if (aCharMap.iExtension)
        {
        chars = aCharMap.iExtension->iCharsQwerty;
        }
    if ( chars )
        {
        delete iExtension->iCharsQwerty;
        iExtension->iCharsQwerty = NULL;
        if (Extension()->iMenuSct)
            {
            iExtension->iCharsQwerty = chars->Mid(iMaxColumns).AllocL();
            }
        else
            {
            iExtension->iCharsQwerty = chars->AllocL();
            }
        }
    }

void CAknCharMap::DrawPictographArea()
    {
    if (iChaMapTableCase != EAknCharMapTableSpecialChar)
        {
        CWindowGc& gc = SystemGc();
        if( !CAknEnv::Static()->TransparencyEnabled() )
            {
            ActivateGc();
            gc.UseFont( iFont );
            }

        // Calculate the number of items.
        TInt numberOfCharsToBeDrawn = iChars->Length();
        numberOfCharsToBeDrawn -= (iFirstVisibleRow * iMaxColumns);
        if ( numberOfCharsToBeDrawn > (iExtension->iMaxVisibleRows * iMaxColumns))
            {
            numberOfCharsToBeDrawn = iExtension->iMaxVisibleRows * iMaxColumns;
            }
        __ASSERT_DEBUG( numberOfCharsToBeDrawn >= 1, Panic(EAknPanicOutOfRange));

        // Draw all items. Implementation takes care that only animated
        // items are actually redrawn.

        iAnimated = ETrue;

        TInt cursorPos = iCursorPos.iX + iCursorPos.iY * iMaxColumns;

        for (TInt j = 0; j < numberOfCharsToBeDrawn; j++)
            {
            DrawCell( j, j == cursorPos );
            }

        iAnimated = EFalse;

        if( !CAknEnv::Static()->TransparencyEnabled() )
            {
            gc.DiscardFont();
            DeactivateGc();
            }
        }
    }

TInt CAknCharMap::PageCount() const
    {
    TInt page(0);
    for (TInt i(0); i < iShowCasesRef->Count(); ++i)
        {
        page += (*iShowPagesRef)[i];
        }

    return page;
    }

TInt CAknCharMap::CurrentPage() const
    {
    TInt page(0);
    for (TInt i(0); i < iCaseIndex; ++i)
        {
        page += (*iShowPagesRef)[i];
        }

    return ((iCursorPos.iY + iFirstVisibleRow) / iExtension->iMaxVisibleRows) + 1 + page;
    }


TBool CAknCharMap::HasPictoInterface() const
    {
    return (iPictoInterface != NULL);
    }

TBool CAknCharMap::SwitchTablesL(TBool& aLayoutChanged)
    {
    aLayoutChanged = EFalse;

    TBool result(EFalse);

    if (iPictoInterface)
        {
        TInt oldVisibleRows = Min(iRows, iExtension->iMaxVisibleRows);

        iChaMapTableCase = (iChaMapTableCase!=EAknCharMapTableSpecialChar) ? EAknCharMapTableSpecialChar : EAknCharMapTablePicto;
        iCaseIndex = 0;

        // In case picto, char case must be kept same as previous value.
        TInt charcase = (iChaMapTableCase==EAknCharMapTableSpecialChar) ? iSpecialCharCases[iCaseIndex] : iSpecialCharCase;
        SetCharacterCaseL(charcase);

        TInt visibleRows = Min(iRows, iExtension->iMaxVisibleRows);

        // Return also information whether the layout changed or not.
        aLayoutChanged = (oldVisibleRows != visibleRows);

        if (!AknLayoutUtils::PenEnabled())
            {
            UpdateScrollIndicatorL();
            }
        else
            {
            UpdateInputFieldL();
            }

        if (aLayoutChanged)
            {
            // If the number of the visible row is changed,
            // it is necessary to re-create the background.
            CreateOffscreenBackgroundL();
            }

        result = ETrue;
        }
    else
        {
        result = SwitchSctAndEmotionL();
        }

    return result;
    }

void CAknCharMap::CreateOffscreenBackgroundL()
    {
    // Offscreen background bitmap for pictograph table - needed for performance.
    // It is created always even if the current skin does not contain bitmap
    // background, because skin change is done in a non-leaving function
    // HandleResourceChange so memory allocations should not be done there.

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );

    iOffscreenBgDrawn = EFalse;

    TRect popupGridRect;
    if (!AknLayoutUtils::PenEnabled() || Extension()->iMenuSct)
        {
        TRect mainPaneRect;
        if(!AknLayoutUtils::LayoutMetricsRect(
            AknLayoutUtils::EPopupParent, mainPaneRect))
            {
            mainPaneRect = iAvkonAppUi->ClientRect();
            }
        TAknLayoutScalableParameterLimits charMapDialogVariety =
            AknLayoutScalable_Avkon::popup_grid_graphic_window_ParamLimits();

        TInt maxVariety = charMapDialogVariety.LastVariety();

        AknLayoutUtils::TAknCbaLocation location = AknLayoutUtils::CbaLocation();
        TInt maxVarietyOffset = 0;
        TInt varietyOffset = maxVariety + 1;
        if(Layout_Meta_Data::IsLandscapeOrientation())
            {
            varietyOffset = (maxVariety + 1) / KAknSctCBaButtonDirections;
            }

        if(location == AknLayoutUtils::EAknCbaLocationRight)
            {
            maxVarietyOffset = varietyOffset;
            }
        else if(location == AknLayoutUtils::EAknCbaLocationLeft)
            {
            maxVarietyOffset = varietyOffset + varietyOffset;
            }
        TInt varietyNumber = varietyOffset - iRows;

        if(varietyNumber < 0)
            {
            varietyNumber = 0;
            }
        else if(iRows<=0)
            {
            varietyNumber -= 1;
            }

        varietyNumber += maxVarietyOffset;

        TAknLayoutRect popupGridLayRect;
        popupGridLayRect.LayoutRect(mainPaneRect,
            AknLayoutScalable_Avkon::popup_grid_graphic_window(varietyNumber));

        popupGridRect = popupGridLayRect.Rect();
        }
    else
        {
        TAknLayoutRect popupGridLayRect;
        popupGridLayRect.LayoutRect(iAvkonAppUi->ApplicationRect(),
            AknLayoutScalable_Avkon::popup_grid_graphic2_window(0));

        popupGridRect = popupGridLayRect.Rect();
        }


    if(iOffscreenBg)
        {
        delete iOffscreenBg;
        iOffscreenBg = NULL;
        }

    iOffscreenBg = new( ELeave ) CFbsBitmap;
    TDisplayMode mode = iCoeEnv->ScreenDevice()->DisplayMode();

    // This is larger rect that is actually needed for the charmap
    // control - the problem is that we do not know the changed rect
    // of the charmap control yet (because the dialog is just about
    // to resize itself).

    if(iBitmapDevice)
        {
        delete iBitmapDevice;
        iBitmapDevice = NULL;
        }

    if(iBitmapGc)
        {
        delete iBitmapGc;
        iBitmapGc = NULL;
        }

    User::LeaveIfError(
        iOffscreenBg->Create( popupGridRect.Size(), mode ) );
    iBitmapDevice = CFbsBitmapDevice::NewL( iOffscreenBg );
    User::LeaveIfError( iBitmapDevice->CreateContext( iBitmapGc ) );

    }

TInt CAknCharMap::NextPageL()
    {
    HandleFocusStatusChanged(EFalse);
    
    TInt page(0);
    iFirstVisibleRow =
        (((iCursorPos.iY + iFirstVisibleRow) / iExtension->iMaxVisibleRows) + 1)
                                                    * iExtension->iMaxVisibleRows;
    if (iFirstVisibleRow > VisibleRows())
        {
        iFirstVisibleRow = 0;

        if(iFirstVisibleRow == 0 &&
        ( (iChaMapTableCase!=EAknCharMapTableSpecialChar && !iPictoInterface->Interface()->IsPictograph((*iChars)[0])) || 
          (iChaMapTableCase==EAknCharMapTableSpecialChar && (*iChars)[0]==KHistoryEmptyChar)) )
            {
            iCursorPos = TPoint(0, 1);
            }
        else
            {
            iCursorPos = TPoint(0, 0);
            }

        page = SwitchAnotherTableL(1);
        }
    else
        {
        if(iFirstVisibleRow == 0 &&
        ( (iChaMapTableCase!=EAknCharMapTableSpecialChar && !iPictoInterface->Interface()->IsPictograph((*iChars)[0])) || 
          (iChaMapTableCase==EAknCharMapTableSpecialChar && (*iChars)[0] == KHistoryEmptyChar)) )
            {
            iCursorPos = TPoint(0, 1);
            }
        else
            {
            iCursorPos = TPoint(0, 0);
            }

        }
    UpdateHeadingPane( ETrue );
    UpdateScrollIndicatorL();
    HandleFocusStatusChanged();
    DrawNow();

    return page;
    }

TInt CAknCharMap::PrevPageL()
    {
    HandleFocusStatusChanged(EFalse);
    
    TInt page(0);
    TInt firstVisibleRow =
        (((iCursorPos.iY + iFirstVisibleRow) / iExtension->iMaxVisibleRows) - 1) *
            iExtension->iMaxVisibleRows;
    if (firstVisibleRow < 0)
        {
        SwitchAnotherTableL(-1);
        iFirstVisibleRow = ((*iShowPagesRef)[iCaseIndex] - 1 ) * iExtension->iMaxVisibleRows;
        if(iFirstVisibleRow == 0 &&
            ( (iChaMapTableCase!=EAknCharMapTableSpecialChar && !iPictoInterface->Interface()->IsPictograph((*iChars)[0])) || 
              (iChaMapTableCase==EAknCharMapTableSpecialChar && (*iChars)[0] == KHistoryEmptyChar)) )
            {
            iCursorPos = TPoint(0, 1);
            }
        else
            {
            iCursorPos = TPoint(0, 0);
            }
        }
    else
        {
        iFirstVisibleRow = firstVisibleRow;
        if(iFirstVisibleRow == 0 &&
            ( (iChaMapTableCase!=EAknCharMapTableSpecialChar && !iPictoInterface->Interface()->IsPictograph((*iChars)[0])) || 
              (iChaMapTableCase==EAknCharMapTableSpecialChar && (*iChars)[0] == KHistoryEmptyChar)) )
            {
            iCursorPos = TPoint(0, 1);
            }
        else
            {
            iCursorPos = TPoint(0, 0);
            }
        }
    UpdateHeadingPane( ETrue );
    UpdateScrollIndicatorL();
    HandleFocusStatusChanged();
    DrawNow();

    return page;
    }

HBufC* CAknCharMap::AppendTextL(HBufC* aChars, HBufC* aText)
    {
    if (!aChars)
        {
        return aText;
        }

    aChars = aChars->ReAllocL(aChars->Length() + aText->Length());
    aChars->Des().Append(aText->Des());
    delete aText;

    return aChars;
    }

void CAknCharMap::DrawPicto(
    CWindowGc& aGc,
    const TRect& aSctPosition,
    TInt aCharIndex,
    TBool aHighlighted,
    TBool aDrawBackground ) const
    {
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    if (aHighlighted)
        {
        //aGc.SetPenColor(AKN_LAF_COLOR(215));
        TRgb color = AKN_LAF_COLOR(215);
        AknsUtils::GetCachedColor( skin, color,
            KAknsIIDQsnLineColors, EAknsCIQsnLineColorsCG7 );
        aGc.SetPenColor(color);
        if (!IsRecentChar(aCharIndex))
            {
            aGc.DrawRect( aSctPosition );
            }

        // Shrink by one pixel in all directions.
        TRect innerRect = aSctPosition;
        if (!IsRecentChar(aCharIndex))
            {
            innerRect.Shrink(1,1);
            }


        color = AKN_LAF_COLOR(210);
        AknsUtils::GetCachedColor(skin,color,
            KAknsIIDQsnHighlightColors,EAknsCIQsnHighlightColorsCG1);
        aGc.SetBrushColor(color);
        aGc.Clear( innerRect );
        }

    // Draw the background of the item if requested
    else if ( aDrawBackground )
        {
        if ( iOffscreenBg )
            {
            TRect offscreenRect = aSctPosition;
            if (IsRecentChar(aCharIndex))
                {
                TRgb colorRecentLine = AKN_LAF_COLOR(215);
                AknsUtils::GetCachedColor( skin, colorRecentLine,
                        KAknsIIDQsnLineColors, EAknsCIQsnLineColorsCG7 );
                aGc.SetPenColor(colorRecentLine);
                // draw top line
                aGc.DrawLine( aSctPosition.iTl,
                    TPoint( aSctPosition.iBr.iX, aSctPosition.iTl.iY ) );
                // draw under line
                aGc.DrawLine( TPoint( aSctPosition.iTl.iX, aSctPosition.iBr.iY - 1 ),
                              TPoint( aSctPosition.iBr.iX, aSctPosition.iBr.iY - 1) );
                if (aCharIndex == 0)
                    {
                    // draw left line
                    aGc.DrawLine( aSctPosition.iTl,
                        TPoint( aSctPosition.iTl.iX, aSctPosition.iBr.iY ) );
                    }
                if (aCharIndex == (iMaxColumns-1) )
                    {
                    // draw right line
                    aGc.DrawLine( TPoint( aSctPosition.iBr.iX -1, aSctPosition.iTl.iY ),
                                  TPoint( aSctPosition.iBr.iX -1, aSctPosition.iBr.iY ) );
                    }
                }
            TPoint topleft = offscreenRect.iTl;

            // Our offscreen bitmap's origo is in the control rect's top left.
            offscreenRect.Move( -( Rect().iTl ) );
            aGc.BitBlt( topleft, iOffscreenBg, offscreenRect );
            }
        else
            {
            aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
            aGc.SetBrushColor(AKN_LAF_COLOR(0));

            TRect innerRect = aSctPosition;
            if (IsRecentChar(aCharIndex))
                {
                innerRect.Shrink(1,1);
                }
            aGc.Clear( innerRect );
            }
        }
    if (iPictoInterface->Interface()->IsPictograph((*iChars)[aCharIndex]))
        {
        if (iExtension->iPictographsBufferGrouping)
            {
            TAknPictographDrawingMode drawingMode =
                aHighlighted?EDrawingModeWhite:EDrawingModeNormal;
            iPictoInterface->Interface()->SetPictographDrawingMode(drawingMode);
            }
        iPictoInterface->Interface()->DrawPictograph(
            aGc,
            aSctPosition,
            (*iChars)[aCharIndex],
            iCurrentPictographHeight );
        }
    }

void CAknCharMap::DrawOffscreenBackgroundIfRequired() const
    {
    if ( iOffscreenBg )
        {
        if ( !iOffscreenBgDrawn )
            {

            MAknsSkinInstance* skin = AknsUtils::SkinInstance();
            MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );

            TRect popupGridRect;
            if (!AknLayoutUtils::PenEnabled() || Extension()->iMenuSct)
                {
                TRect mainPaneRect;
                if(!AknLayoutUtils::LayoutMetricsRect(
                    AknLayoutUtils::EPopupParent, mainPaneRect))
                    {
                    mainPaneRect = iAvkonAppUi->ClientRect();
                    }
                TAknLayoutScalableParameterLimits charMapDialogVariety =
                    AknLayoutScalable_Avkon::popup_grid_graphic_window_ParamLimits();

                TInt maxVariety = charMapDialogVariety.LastVariety();

                AknLayoutUtils::TAknCbaLocation location =
                    AknLayoutUtils::CbaLocation();
                TInt maxVarietyOffset = 0;
                TInt varietyOffset = maxVariety + 1;
                if(Layout_Meta_Data::IsLandscapeOrientation())
                    {
                    varietyOffset = (maxVariety + 1)/KAknSctCBaButtonDirections;
                    }

                if(location == AknLayoutUtils::EAknCbaLocationRight)
                    {
                    maxVarietyOffset = varietyOffset;
                    }
                else if(location == AknLayoutUtils::EAknCbaLocationLeft)
                    {
                    maxVarietyOffset = varietyOffset + varietyOffset;
                    }
                TInt varietyNumber = varietyOffset - iRows;

                if(varietyNumber < 0)
                    {
                    varietyNumber = 0;
                    }
                else if(iRows<=0)
                    {
                    varietyNumber -= 1;
                    }
                varietyNumber += maxVarietyOffset;

                TAknLayoutRect popupGridLayRect;
                popupGridLayRect.LayoutRect(mainPaneRect,
                    AknLayoutScalable_Avkon::popup_grid_graphic_window(varietyNumber));

                popupGridRect = popupGridLayRect.Rect();

                popupGridRect.iTl.iY = Rect().iTl.iY;
                popupGridRect.Move(-popupGridRect.iTl.iX,0);
                TPoint point = TPoint( 0, 0 );
                AknsDrawUtils::DrawBackground(
                    skin,
                    cc,
                    this,
                    *iBitmapGc,
                    point,
                    popupGridRect,
                    KAknsDrawParamDefault );
                }
            else
                {
                TAknLayoutRect popupGridLayRect;
                popupGridLayRect.LayoutRect(iAvkonAppUi->ApplicationRect(),
                    AknLayoutScalable_Avkon::popup_grid_graphic2_window(
                        0));

                popupGridRect = popupGridLayRect.Rect();

                popupGridRect.iTl.iY = Rect().iTl.iY;
                popupGridRect.Move(-popupGridRect.iTl.iX,0);
                TPoint point = TPoint( 0, 0 );
                AknsDrawUtils::DrawBackground(
                    skin,
                    cc,
                    this,
                    *iBitmapGc,
                    point,
                    popupGridRect,
                    KAknsDrawParamDefault );
                }
            iOffscreenBgDrawn = ETrue;
            }
        }
    }

EXPORT_C CCoeControl* CAknCharMap::ComponentControl(TInt aIndex) const
    {
    if (iSBFrame && iSBFrame->TypeOfVScrollBar() == CEikScrollBarFrame::EDoubleSpan)
        {
        if ( aIndex == 0 )
            {
            return iSBFrame->VerticalScrollBar();
            }
        aIndex--;
        }

    if (iExtension->iRadioButton)
        {
         if ( aIndex == 0 )
            {
            return iExtension->iRadioButton;
            }
        aIndex--;
        }

    if (iExtension->iCategoryTitle)
        {
        if ( aIndex == 0 )
            {
            return iExtension->iCategoryTitle;
            }
        aIndex--;
        }
    if (iExtension->iCategoryEntry)
        {
        if ( aIndex == 0 )
            {
            return iExtension->iCategoryEntry;
            }
        aIndex--;
        }

    if (iExtension->iTableNavi)
        {
         if ( aIndex == 0 )
            {
            return iExtension->iTableNavi;
            }
        aIndex--;
        }
    if (iExtension->iPageNavi)
        {
         if ( aIndex == 0 )
            {
            return iExtension->iPageNavi;
            }
        aIndex--;
        }

    return NULL;
    }

EXPORT_C TInt CAknCharMap::CountComponentControls() const
    {
    TInt num = 0;
    if (iSBFrame && iSBFrame->TypeOfVScrollBar() == CEikScrollBarFrame::EDoubleSpan)
        {
        num++;
        }
    if (iExtension->iRadioButton)
        {
        num++;
        }
    if (iExtension->iCategoryTitle)
        {
        num++;
        }
    if (iExtension->iCategoryEntry)
        {
        num++;
        }
    if (iExtension->iTableNavi)
        {
        num++;
        }
    if (iExtension->iPageNavi)
        {
        num++;
        }
    return num;
    }

void CAknCharMap::SetPictoMode(TAknCharMapPictoMode aMode)
    {
    if (aMode == EAknCharMapPictoNoUse)
        {
        delete iPictoInterface;
        iPictoInterface = NULL;
        }
    else if (aMode == EAknCharMapPictoFirst)
        {
        iChaMapTableCase = EAknCharMapTablePicto;
        }
    }

void CAknCharMap::SetCaseTableL(const RArray<TInt> & aCase)
    {

    // set current case characters to display on SCT
    HBufC* currentcasechars = iCharsBufferLower;
    if (iCharsBufferUpper && iSpecialCharCase==EAknSCTUpperCase)
        currentcasechars = iCharsBufferUpper;
    else if (iCharsBufferNumeric && iSpecialCharCase==EAknSCTNumeric)
        currentcasechars = iCharsBufferNumeric;
    else if (iCharsBufferFull && iSpecialCharCase==EAknSCTFullCase)
        currentcasechars = iCharsBufferFull;
    else if (iCharsBufferHalf && iSpecialCharCase==EAknSCTHalfCase)
        currentcasechars = iCharsBufferHalf;
    else if (iExtension->iCharsQwerty && iSpecialCharCase==EAknSCTQwerty)
        currentcasechars = iExtension->iCharsQwerty;

    iSpecialCharPages.AppendL( PageCountFromChars(*currentcasechars) );

    iSpecialCharCases.AppendL( iSpecialCharCase );
    if (iExtension->iRadioButton)
        {
        // Set the sct case mode to valid
        iExtension->iRadioButton->SetValidSctCase(iSpecialCharCase);
        }

    if (aCase.Count() > 0)
        {
        for (TInt i(0); i < aCase.Count(); ++i)
            {
            HBufC* chars = CharsFromCase(aCase[i]);
            if (chars)
                {
                iSpecialCharCases.AppendL( aCase[i] );
                iSpecialCharPages.AppendL( PageCountFromChars(*chars) );
                if (iExtension->iRadioButton)
                    {
                    // Set the sct case mode to valid
                    iExtension->iRadioButton->SetValidSctCase(aCase[i]);
                    }
                }
            }
        }

    if (iExtension->iPictographsBuffer && iPictoInterface)
        {
        __ASSERT_ALWAYS(
            iPictoInterface->Interface(), Panic(EAknPanicNullPointer));

        iPictographPages.AppendL( PageCountFromChars(*iPictographsBuffer) );
        iPictographCases.AppendL(EAknCharMapTablePicto);
        if (iExtension->iPictographsBufferGrouping)
            {
            iPictographPages.AppendL( PageCountFromChars(*iPictographsBuffer2) );
            iPictographCases.AppendL(EAknCharMapTablePicto2);
            if (iExtension->iRadioButton)
                {
                // Set the sct case mode to valid
                iExtension->iRadioButton->SetValidSctCase(EAknSCTPictograph1);
                iExtension->iRadioButton->SetValidSctCase(EAknSCTPictograph2);
                }
            }
        else
            {
            if (iExtension->iRadioButton)
                {
                // Set the sct case mode to valid
                iExtension->iRadioButton->SetValidSctCase(EAknSCTPictograph);
                }
            }
        }

    if (iExtension->iRadioButton)
        {
        // Remove invalid category buttons
        iExtension->iRadioButton->RemoveInvalidButton();
        __ASSERT_DEBUG( iExtension->iRadioButton->Count() > 0,
            Panic(EAknPanicInvalidValue));
        }
    }

void CAknCharMap::SetTitleL(TPtrC aTitle)
    {
    iTitleDefault = HBufC::NewL(aTitle.Length());
    iTitleDefault->Des().Copy(aTitle);

    HBufC* title;
    if (iExtension->iPictographsBufferGrouping)
        {
        title = StringLoader::LoadLC(
            R_AVKON_SPECIAL_CHARACTERS_PICTOGRAPH1, iCoeEnv);
        iTitlePicto = HBufC::NewL(title->Length());
        iTitlePicto->Des().Copy(*title);
        CleanupStack::PopAndDestroy(title); // title

        title = StringLoader::LoadLC(
            R_AVKON_SPECIAL_CHARACTERS_PICTOGRAPH2, iCoeEnv);
        iTitlePicto2 = HBufC::NewL(title->Length());
        iTitlePicto2->Des().Copy(*title);
        CleanupStack::PopAndDestroy(title); // title
        }
    else
        {
        title = StringLoader::LoadLC(
            R_AVKON_SPECIAL_CHARACTERS_PICTOGRAPH, iCoeEnv);
        iTitlePicto = HBufC::NewL(title->Length());
        iTitlePicto->Des().Copy(*title);
        CleanupStack::PopAndDestroy(title); // title
        // Picto2 isn't used.
        iTitlePicto2 = NULL;
        }

    title = StringLoader::LoadLC(
        R_AVKON_SPECIAL_CHARACTERS_HALF_SYMBOL, iCoeEnv);
    iTitleHalf = HBufC::NewL(title->Length());
    iTitleHalf->Des().Copy(*title);
    CleanupStack::PopAndDestroy(); // title

    title = StringLoader::LoadLC(
        R_AVKON_SPECIAL_CHARACTERS_FULL_SYMBOL, iCoeEnv);
    iTitleFull = HBufC::NewL(title->Length());
    iTitleFull->Des().Copy(*title);
    CleanupStack::PopAndDestroy(); // title
    }

const TDesC* CAknCharMap::Title() const
    {
    HBufC* title = iTitleDefault;
    if (iChaMapTableCase == EAknCharMapTableSpecialChar)
        {
        if (iSpecialCharCase == EAknSCTHalfCase)
            {
            title = iTitleHalf;
            }
        if (iSpecialCharCase == EAknSCTFullCase)
            {
            title = iTitleFull;
            }
        }
    else
        {
        if (iCaseIndex == 1)
            {
            title = iTitlePicto2;
            }
        else
            {
            title = iTitlePicto;
            }
        }
    return title;
    }

TInt CAknCharMap::SwitchAnotherTableL(TInt aIncrement)
    {
    TInt page(0);
    if (iShowCasesRef->Count() > 1)
        {
        iCaseIndex += aIncrement;
        if (iShowCasesRef->Count() - 1 < iCaseIndex)
            {
            iCaseIndex = 0;
            }
        if (iCaseIndex < 0)
            {
            iCaseIndex = iShowCasesRef->Count() - 1;
            }
        SetCharacterCaseL((*iShowCasesRef)[iCaseIndex]);
        page = PageCount();
        }
    return page;
    }

void CAknCharMap::CountMaxColumnsAndCellSizes()
    {
    TRect mainPaneRect;
    if (!AknLayoutUtils::PenEnabled() || Extension()->iMenuSct)
        {
        if(!AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EMainPane, mainPaneRect))
            {
            mainPaneRect = iAvkonAppUi->ClientRect();
            }

        TAknLayoutScalableParameterLimits charMapDialogVariety =
            AknLayoutScalable_Avkon::popup_grid_graphic_window_ParamLimits();

        TInt maxVariety = charMapDialogVariety.LastVariety();

        AknLayoutUtils::TAknCbaLocation location = AknLayoutUtils::CbaLocation();
        TInt maxVarietyOffset = 0;
        TInt varietyOffset = maxVariety + 1;
        if(Layout_Meta_Data::IsLandscapeOrientation())
            {
            varietyOffset = (maxVariety + 1) / KAknSctCBaButtonDirections;
            }

        if(location == AknLayoutUtils::EAknCbaLocationRight)
            {
            maxVarietyOffset = varietyOffset;
            }
        else if(location == AknLayoutUtils::EAknCbaLocationLeft)
            {
            maxVarietyOffset = varietyOffset + varietyOffset;
            }

        TAknLayoutRect popupGridLayRect;
        popupGridLayRect.LayoutRect(mainPaneRect,
            AknLayoutScalable_Avkon::popup_grid_graphic_window(maxVarietyOffset));

        TAknLayoutRect gridWithScrollLayRect;
        gridWithScrollLayRect.LayoutRect(popupGridLayRect.Rect(),
            AknLayoutScalable_Avkon::listscroll_popup_graphic_pane());


        TAknLayoutRect gridLayRect;
        if (iExtension->iHasCategoryButtonUi)
            {
            gridLayRect.LayoutRect(gridWithScrollLayRect.Rect(),
                AknLayoutScalable_Avkon::grid_graphic_popup_pane(2));
            }
        else
            {
            gridLayRect.LayoutRect(gridWithScrollLayRect.Rect(),
                AknLayoutScalable_Avkon::grid_graphic_popup_pane(0));
            }

        TRect gridRect = Extension()->iMenuSct ? Rect(): gridLayRect.Rect();

        TAknLayoutRect firstCellLayRect;
        firstCellLayRect.LayoutRect(gridRect,
            AknLayoutScalable_Avkon::cell_graphic_popup_pane_cp2(0,0,0));

        TRect firstCellRect;
        if ( Extension()->iMenuSct )
            {
            firstCellRect = TRect( TPoint(0, 0),
                 TSize( firstCellLayRect.Rect().Width(), Rect().Height() ) );
            }
        else
            {
            firstCellRect = firstCellLayRect.Rect();
            }

        TAknLayoutRect rightCellLayRect;
        rightCellLayRect.LayoutRect(gridRect,
            AknLayoutScalable_Avkon::cell_graphic_popup_pane_cp2(0,1,0));

        // Max columns.
        iMaxColumns = gridRect.Width() / firstCellRect.Width();

        // Max visible rows.
        iExtension->iMaxVisibleRows = gridRect.Height() / firstCellRect.Height();

        // Cell width.
        iGridItemWidth =
            rightCellLayRect.Rect().iTl.iX - firstCellLayRect.Rect().iTl.iX;
        if (iGridItemWidth < 0)
            {
            iGridItemWidth = -iGridItemWidth;
            }

        // Cell height.
        if ( Extension()->iMenuSct )
            {
            iGridItemHeight = firstCellRect.Height();
            }
        else
            {
            TAknLayoutRect downCellLayRect;
            downCellLayRect.LayoutRect(gridRect,
                AknLayoutScalable_Avkon::cell_graphic_popup_pane_cp2(0,0,1));
            iGridItemHeight =
                downCellLayRect.Rect().iTl.iY - firstCellLayRect.Rect().iTl.iY;
            }
        }
    else
        {
        TAknLayoutRect popupGridLayRect;
        popupGridLayRect.LayoutRect(iAvkonAppUi->ApplicationRect(),
            AknLayoutScalable_Avkon::popup_grid_graphic2_window(0));

        TRect popupGridRect = popupGridLayRect.Rect();

        TInt gridVariety;
        if (!IsJapaneseSctUi())
            {
            if(!Layout_Meta_Data::IsLandscapeOrientation())
                {
                gridVariety = (TableCount() > 1) ? 0 : 1;
                }
            else
                {
                gridVariety = (TableCount() > 1) ? 2 : 3;
                }
            }
        else
            {
            gridVariety = !Layout_Meta_Data::IsLandscapeOrientation() ? 4 : 5;
            }

        TAknLayoutRect gridLayRect;
        gridLayRect.LayoutRect(popupGridRect,
            AknLayoutScalable_Avkon::grid_graphic2_pane(gridVariety));

        TRect gridRect = gridLayRect.Rect();

        TAknLayoutRect firstCellLayRect;
        firstCellLayRect.LayoutRect(popupGridRect,
            AknLayoutScalable_Avkon::aid_size_cell_graphic2(gridVariety,0,0));

        TRect firstCellRect = firstCellLayRect.Rect();

        // Max columns.
        iMaxColumns = gridRect.Width() / firstCellRect.Width();

        // Max visible rows.
        iExtension->iMaxVisibleRows = gridRect.Height() / firstCellRect.Height();

        // Cell width.
        iGridItemWidth = firstCellRect.Width();

        // Cell height.
        iGridItemHeight = firstCellRect.Height();
        }
    }

HBufC* CAknCharMap::CharsFromCase(TInt aCharCase) const
    {
   __ASSERT_DEBUG( iExtension, Panic(EAknPanicInvalidValue));

    HBufC* chars = NULL;
    switch (aCharCase)
        {
        case EAknSCTLowerCase:
            chars = iCharsBufferLower;
            break;
        case EAknSCTUpperCase:
            chars = iCharsBufferUpper;
            break;
        case EAknSCTNumeric:
            chars = iCharsBufferNumeric;
            break;
        case EAknSCTFullCase:
            chars = iCharsBufferFull;
            break;
        case EAknSCTHalfCase:
            chars = iCharsBufferHalf;
            break;
        case EAknSCTQwerty:
             chars = iExtension->iCharsQwerty;
            break;
        default:
            break;
        }
    return chars;
    }

TInt CAknCharMap::PageCountFromChars(TDesC& aChars) const
    {
    TInt page(aChars.Length() / (iExtension->iMaxVisibleRows * iMaxColumns));
    if ((page * (iExtension->iMaxVisibleRows * iMaxColumns)) != aChars.Length())
        {
        page++;
        }
    return page;
    }

TInt CAknCharMap::VisibleRows() const
    {
    TInt count((*iShowPagesRef)[iCaseIndex] - 1);
    return count * iExtension->iMaxVisibleRows;
    }

void CAknCharMap::CreatePictoCharL()
    {
    if (!iExtension->iPictographsBuffer)
        {
        return;
        }

    delete iPictographsBuffer;
    iPictographsBuffer = NULL;
    delete iPictographsBuffer2;
    iPictographsBuffer2 = NULL;
    delete iPictoInterface;
    iPictoInterface = NULL;

    iPictoInterface = CAknPictographInterface::NewL(*this, *this);
    if (iPictoInterface)
        {
        __ASSERT_ALWAYS(iFont, Panic(EAknPanicNullPointer));
        iCurrentPictographHeight = EHeight16;
        iPictoInterface->Interface()->SelectPictographHeightForFont(*iFont,iCurrentPictographHeight);
        }

    // set pictograph characters
    if (iExtension->iPictographsBufferGrouping)
        {
        for (TInt index=0; index < 2; index++)
            {
            PictograhGrouping::TAknPictographGroupType type =
                ( index == 0 )? PictograhGrouping::TAknPictographGroup1
                                : PictograhGrouping::TAknPictographGroup2;
            // get pictograph characters
            HBufC* temp = PictograhGrouping::AllocStringLC(type);
            HBufC* buf = HBufC::NewL(temp->Length());
            TPtr ptr(buf->Des());
            ptr.Append(*temp);
            CleanupStack::PopAndDestroy(temp); // temp

            if ( index == 0 )
                {
                iPictographsBuffer = buf;
                }
            else
                {
                iPictographsBuffer2 = buf;
                }
            }
        }
    else if ( iPictoInterface )
        {
        // get pictograph characters
        HBufC* temp =
            iPictoInterface->Interface()->SupportedPictographCodesL();
        CleanupStack::PushL(temp);

        iPictographsBuffer = HBufC::NewL(temp->Length());
        TPtr ptr = iPictographsBuffer->Des();
        ptr.Append(*temp);
        CleanupStack::PopAndDestroy(temp); // temp

        // picto2 is not used.
        iPictographsBuffer2 = NULL;
        }

    // EFalse is set to iSetRecentPic variable when setting special
    // characters from resouce.
    iSetRecentPic = EFalse;
    }

//--------------------------------------------------------------------------
// void CAknCharMap::HandlePointerEventL()
// The function works in two different ways. First (1), if the pointer is set
// down or dragged the "focus" shall either move to it or follow the pointer.
// Second (2) when the pointer is lifted the char below the pointer is set in
// to the array in which all the special characters are placed by the normal
// (rocker) method.
//--------------------------------------------------------------------------
EXPORT_C void CAknCharMap::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    if ( AknLayoutUtils::PenEnabled() && Rect().Contains(aPointerEvent.iPosition))
        {
        if (iExtension->iFocusHandler->FocusedControl() != this)// Tapping will move focus to grid.
            {
            iExtension->iFocusHandler->LeaveControl();
            iExtension->iFocusHandler = iExtension;
            }

        TInt newGridX; // For the whole
        TInt newGridY; // For the whole grid.
        TInt yInPixels = aPointerEvent.iPosition.iY - iGridTopLeft.iY;
        newGridY = yInPixels / iGridItemHeight;

        newGridX = -1;

        if ( iIsMirrored )
            {
            TInt topRight = iGridTopLeft.iX - ( iMaxColumns - 1 ) * iGridItemWidth;
            TInt topLeft = iGridTopLeft.iX + iGridItemWidth;
            if ( ( aPointerEvent.iPosition.iX > topRight ) &&
                ( aPointerEvent.iPosition.iX < topLeft ) )
                {
                newGridX = ( topLeft - aPointerEvent.iPosition.iX ) / iGridItemWidth;
                }
            }
        else if ((aPointerEvent.iPosition.iX - iGridTopLeft.iX) > 0)
            {
            newGridX = (aPointerEvent.iPosition.iX - iGridTopLeft.iX) / iGridItemWidth;
            }

        // The pointer has been set down or dragged into the area of the grid. (it might be in
        // the "white space" at the end of the grid)
        if ((yInPixels >= 0 && yInPixels < iGridItemHeight * iExtension->iMaxVisibleRows) &&
            // When the pointer is in rows except the recent character row
            ((((newGridY + iFirstVisibleRow) != 0) && newGridX < iMaxColumns && newGridX >= 0) ||
            // When the pointer is in the recent character row
            ( (newGridY + iFirstVisibleRow == 0) && (newGridX< LengthOfRecentChar()))) )
            {
            // For any action to be taken, the pointer event must either be a Button1Down or a drag event
            // which has originated from a Button1Down in to the grid.
            if (iExtension->iFlags&EAknCharMapHasBeenScrolledByDrag ||
                aPointerEvent.iType == TPointerEvent::EButton1Down  ||
                iExtension->iFlags&EAknCharMapButton1DownInGrid)
                {
                if (aPointerEvent.iType == TPointerEvent::EButton1Down)
                    {
                    iExtension->iSelectAllowed = ETrue; // enable selection.
                    }
                iExtension->iFlags |= EAknCharMapButton1DownInGrid;
                TUint globalY = newGridY + iFirstVisibleRow;
                if (iChars->Length() > globalY * iMaxColumns + newGridX)
                    {
                    if (aPointerEvent.iType == TPointerEvent::EButton1Down ||
                        aPointerEvent.iType == TPointerEvent::EDrag)
                        {
                        if (iCursorPos.iX+(iCursorPos.iY+iFirstVisibleRow)*iMaxColumns < iChars->Length())
                            {
                            iOldCursorPos = iCursorPos;
                            }
                        else
                            {
                            iOldCursorPos.iX = 0;
                            iOldCursorPos.iY = 0;
                            }

                        iCursorPos.iY = newGridY;
                        iCursorPos.iX = newGridX;

                        if( iExtension->iSingleClickEnabled && 
                            iExtension->iHighlightVisible &&
                            aPointerEvent.iType == TPointerEvent::EDrag )
                            {
                            TInt focusPos = iCursorPos.iX + ( iFirstVisibleRow + 
                                    iCursorPos.iY ) * iMaxColumns;
                            TInt oldFocusPos = iOldCursorPos.iX + (
                                    iFirstVisibleRow + 
                                    iOldCursorPos.iY ) * iMaxColumns;
                            if ( focusPos != oldFocusPos )
                                {
                                iExtension->iHighlightVisible = EFalse;
                                iExtension->iSelectAllowed = EFalse;
                                }
                            }
                        
                        if ( aPointerEvent.iType == TPointerEvent::EButton1Down )
                            {
                            iExtension->iFlags |= EAknCharMapPressedDown;
                            }
                        else if ( iOldCursorPos != iCursorPos )
                            {
                            iExtension->iFlags &= (~EAknCharMapPressedDown);
                            }
                                
                        // down event on an item, play feedback
                        MTouchFeedback* feedback = MTouchFeedback::Instance();
                        if ( feedback &&
                             aPointerEvent.iType == TPointerEvent::EButton1Down )
                            {
                            feedback->InstantFeedback( this, ETouchFeedbackBasicItem );
                            }
                        if ( aPointerEvent.iType == TPointerEvent::EDrag &&
                             iCursorPos != iOldCursorPos )
                            {
                            // Disable selection.
                            iExtension->iSelectAllowed = EFalse;

                            if ( iExtension->iKineticScrolling )
                                {
                                // Don't allow changing the item by dragging.
                                iCursorPos = iOldCursorPos;
                                }
                            }

                        if( aPointerEvent.iType == TPointerEvent::EButton1Down )
                            {
                            if( iExtension->iSingleClickEnabled )
                                {
                                iExtension->iHighlightVisible = ETrue;
                                }
                        
                            HandleFocusStatusChanged();
                            }
                        
                        DrawCursor();
                        }
                    else if (aPointerEvent.iType == TPointerEvent::EButton1Up)
                        {
                        // Observe that selection has been changed, so char map dialog can get
                        // selected char, add it to text and close.
                        if (iExtension->iObserver &&
                            iExtension->iFlags & EAknCharMapPressedDown)
                            {
                            iStatusChanged =
                                iExtension->iSelectAllowed ?
                                    EAknCharSelectedSpecialCharacter : EAknCharNoSelection;
                            // up event hit the same item that was selected by down event,
                            // play feedback
                            MTouchFeedback* feedback = MTouchFeedback::Instance();
                            if ( feedback )
                                {
                                feedback->InstantFeedback( this, 
                                                           ETouchFeedbackBasicItem,
                                                           ETouchFeedbackVibra,
                                                           TPointerEvent() );
                                }

                            iExtension->iObserver->HandleControlEventL(
                                this, MCoeControlObserver::EEventStateChanged);
                            }
                        }
                    }
                // The user tapped on a cell which does not have item. Remove highlight
                else if ( iExtension->iSingleClickEnabled ) 
                    {
                    iExtension->iHighlightVisible = EFalse;
                    DrawCursor();
                    }
                }
            }
        else if ( iExtension->iSingleClickEnabled )
            {
            iExtension->iHighlightVisible = EFalse;
            DrawCursor();
            }
			
        CCoeControl::HandlePointerEventL(aPointerEvent);

        // if Stylus is lifted we clear all flags.
        if (aPointerEvent.iType == TPointerEvent::EButton1Up)
            {
            iExtension->iFlags &= (~EAknCharMapButton1DownInGrid);
            iExtension->iFlags &= (~EAknCharMapHasBeenScrolledByDrag);
            iExtension->iFlags &= (~EAknCharMapPressedDown);
            if ( !iSBFrame )
                {
                return;
                }
            CEikScrollBar* vScrollBar = iSBFrame->VerticalScrollBar();
            if(vScrollBar)
                {
                vScrollBar->HandlePointerEventL(aPointerEvent);
                }
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknCharMap::SetObserver
// Sets the observer.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknCharMap::SetObserver( MCoeControlObserver* aObserver  )
    {
    if (iExtension)
        {
        iExtension->iObserver = aObserver;
        }
    }

// -----------------------------------------------------------------------------
// CAknCharMap::HandleScrollEventL
// Handles the different scroll events so that the map reacts accordingly.
// -----------------------------------------------------------------------------
//
void CAknCharMap::HandleScrollEventL(
    CEikScrollBar* aScrollBar,
    TEikScrollEvent aEventType)
    {
    TBool update = EFalse;

    switch (aEventType)
        {
        case EEikScrollUp:
        case EEikScrollPageUp:
            {
            // nothing done if we are already on the first page.
            if (iFirstVisibleRow != 0)
                {
                iFirstVisibleRow -= iExtension->iMaxVisibleRows;
                update = ETrue;
                }
            if(iFirstVisibleRow == 0 &&
            ( (iChaMapTableCase!=EAknCharMapTableSpecialChar && !iPictoInterface->Interface()->IsPictograph((*iChars)[0])) || 
              (iChaMapTableCase==EAknCharMapTableSpecialChar && (*iChars)[0]==KHistoryEmptyChar)) )
                {
                iCursorPos = TPoint(0, 1);
                }
            else
                {
                iCursorPos = TPoint(0, 0);
                }

            UpdateHeadingPane( ETrue );
            UpdateScrollIndicatorL();
            }
        break;
        case EEikScrollDown:
        case EEikScrollPageDown:
            {
            // nothing done if we are already on the last page.
            if (iFirstVisibleRow != (PageCount() -1 ) * iExtension->iMaxVisibleRows)
                {
                iFirstVisibleRow += iExtension->iMaxVisibleRows;
                update = ETrue;
                }
            iCursorPos = TPoint(0, 0);
            UpdateHeadingPane( ETrue );
            UpdateScrollIndicatorL();
            }
        break;
        case EEikScrollThumbDragVert:
            {
            TInt thumbPosition;
            TInt halfPage = iExtension->iMaxVisibleRows/2;
            // Ask which type of scrollbar is shown
            CAknAppUi* appUi = iAvkonAppUi;
            TBool isDoubleSpan =
                CEikScrollBarFrame::EDoubleSpan == iSBFrame->TypeOfVScrollBar();
            if (isDoubleSpan)
                {
                thumbPosition =
                    static_cast <const TAknDoubleSpanScrollBarModel*>
                        (aScrollBar->Model())->FocusPosition();
                }
            else
                {
                thumbPosition = aScrollBar->Model()->iThumbPosition;
                }

            // If the slider is in the range of less then a half page from a possible correct thumb position.
            // thus 0 <= iFirstVisibleRow - thumbPosition < halfPage. Or in the other direction:
            // 0 <= thumbPosition - iFirstVisibleRow < halfPage
            if (!((0 <= iFirstVisibleRow - thumbPosition &&
                        iFirstVisibleRow - thumbPosition < halfPage )||
                  (0 <= thumbPosition - iFirstVisibleRow &&
                        thumbPosition - iFirstVisibleRow < halfPage)))
                {
                TReal toRound = thumbPosition/(TReal)iExtension->iMaxVisibleRows;
                if (toRound * 2 > (TInt)toRound * 2 + 1)
                    {
                    toRound++;
                    }
                iFirstVisibleRow = (TInt)toRound * iExtension->iMaxVisibleRows;
                if(iFirstVisibleRow == 0 &&
                ( (iChaMapTableCase!=EAknCharMapTableSpecialChar && !iPictoInterface->Interface()->IsPictograph((*iChars)[0])) || 
                  (iChaMapTableCase==EAknCharMapTableSpecialChar && (*iChars)[0]==KHistoryEmptyChar)) )
                    {
                    iCursorPos = TPoint(0, 1);
                    }
                else
                    {
                    iCursorPos = TPoint(0, 0);
                    }
                UpdateHeadingPane( EFalse );
                update = ETrue;
                }
            }
        break;
        case EEikScrollThumbReleaseVert:
            {
            UpdateScrollIndicatorL();
            }
        break;
        case EEikScrollLeft: // flow through
        case EEikScrollRight: // flow through
        case EEikScrollPageLeft: // flow through
        case EEikScrollPageRight: // flow through
        case EEikScrollThumbDragHoriz: // flow through
        case EEikScrollThumbReleaseHoriz: // flow through
            // do nothing
            break;
        default:
            // do nothing
            break;
        }
     // If we have move up to the first page we check the first low is empty or not and
     // set iCursorPos respective
    if (iFirstVisibleRow == 0 and iCursorPos.iY == 0)
        {
         if ( (iChaMapTableCase!=EAknCharMapTableSpecialChar && !iPictoInterface->Interface()->IsPictograph((*iChars)[iCursorPos.iX])) || 
              (iChaMapTableCase==EAknCharMapTableSpecialChar && (*iChars)[iCursorPos.iX]==KHistoryEmptyChar && !Extension()->iMenuSct) )
            {
            iCursorPos =  TPoint(iCursorPos.iX, 1);
            }
        }
// If we have moved down to the last page we check that the cursor is in a place where it can be
// drawn.
    if (iFirstVisibleRow == (iRows/iExtension->iMaxVisibleRows) * iExtension->iMaxVisibleRows)
        {
        // the old cursor is set to a "safe" position where it at least can be.
        iOldCursorPos.iX = 0;
        iOldCursorPos.iY = 0;
        // if the last page has only one line which isn't filled complitely.
        if (iChars->Length()%iMaxColumns - 1 < iCursorPos.iX && iRows%iExtension->iMaxVisibleRows == 1)
            {
            iCursorPos.iX = iChars->Length()%iMaxColumns - 1;
            }
        // If the cursor is in a position where it would go unto a spot with out
        // a character when scrolled.
        if (iCursorPos.iY + iFirstVisibleRow >= iRows)
            {
            if (iChars->Length()%iMaxColumns > iCursorPos.iX)
                {
                iCursorPos.iY = iRows - 1 - iFirstVisibleRow;
                }
            else
                {
                iCursorPos.iY = iRows - 2 - iFirstVisibleRow;
                }
            }
        // If the cursor is actually on the last row, but is still in the
        // area where there is now chars. (the rest of the last row)
        if (iChars->Length() <= (iFirstVisibleRow + iCursorPos.iY) * iMaxColumns + iCursorPos.iX && 
            iCursorPos.iY + iFirstVisibleRow + 1 == iRows)
            {
            iCursorPos.iY--;
            }
        // if the corrections did not help and the cursor is in the area
        // where there is a valid row, but no chars anymore
        }

    // to avoid flicker we draw only if there really was something new to draw.
    if (update)
        {
        if (iExtension->iObserver)
            {
            iExtension->iObserver->HandleControlEventL(this, MCoeControlObserver::EEventRequestFocus);
            }
        
        HandleFocusStatusChanged();
        DrawDeferred();
        }
    }

// -----------------------------------------------------------------------------
// CAknCharMapHistory::AppendRecentCharL()
// Append the recent data to SCT/Picto data
// -----------------------------------------------------------------------------
//
void CAknCharMap::AppendRecentCharL()
    {
    __ASSERT_ALWAYS( iCharMapHistory, Panic(EAknPanicInvalidValue));
    __ASSERT_DEBUG( iExtension, Panic(EAknPanicInvalidValue));
    
    if(iSetRecentSct) return;

    for (TInt index=0; index < 8; index++ )
        {
        
        CAknCharMapHistory::THistoryType historyType = CAknCharMapHistory::EHistoryTypeNull;
        HBufC** charsBuf = NULL;

        switch (index)
            {
            case 0:
                historyType = CAknCharMapHistory::EHistoryTypeFull;
                charsBuf = &iCharsBufferFull;
                break;
            case 1:
                historyType = CAknCharMapHistory::EHistoryTypeHalf;
                charsBuf = &iCharsBufferHalf;
                break;
            case 2:
                historyType = CAknCharMapHistory::EHistoryTypeHalf;
                charsBuf = &iCharsBufferLower;
                break;
            case 3:
                historyType = CAknCharMapHistory::EHistoryTypeHalf;
                charsBuf = &iCharsBufferUpper;
                break;
            case 4:
                historyType = CAknCharMapHistory::EHistoryTypeHalf;
                charsBuf = &iCharsBufferNumeric;
                break;
            case 5:
                historyType = CAknCharMapHistory::EHistoryTypePicto;
                charsBuf = &iPictographsBuffer;
                break;
            case 6:
                historyType = CAknCharMapHistory::EHistoryTypePicto2;
                charsBuf = &iPictographsBuffer2;
                break;
            case 7:
                historyType = CAknCharMapHistory::EHistoryTypeHalf;
                charsBuf = &iExtension->iCharsQwerty;
                break;
            default:
                break;
            }
        
        TPtrC textHistory = iCharMapHistory->RecentString(historyType, CAknCharMapHistory::EHistoryFilterTextOnly);
        
        *charsBuf = InsertSwitchCharAndHistoryToCharsBufL(*charsBuf, 
                                                          TEmotionUtils::EmotionSwitchToSmileyChar(), 
                                                          textHistory);
        }
    
    // Emotion history
    TPtrC emotionHistory = iCharMapHistory->RecentString(CAknCharMapHistory::EHistoryTypeFull, CAknCharMapHistory::EHistoryFilterEmotionOnly);
    iExtension->iCharsSmiley = InsertSwitchCharAndHistoryToCharsBufL(iExtension->iCharsSmiley, 
                                                                     TEmotionUtils::EmotionSwitchToSctChar(), 
                                                                     emotionHistory);

    // ETrue are set to each variable when setting the recent used characters.
    iSetRecentSct = ETrue;
    iSetRecentPic = ETrue;
    }

HBufC* CAknCharMap::InsertSwitchCharAndHistoryToCharsBufL(HBufC* aCharsBuf, TChar aSwitchChar, const TDesC& aHistory)
    {
    if (aCharsBuf)
        {
        // Check whether recent charcters are included in base charcters.
        TBuf<CAknCharMapHistory::KHistoryBufferSize+5> insertBuffer;
        for (TInt index=0; index<aHistory.Length(); index++)
            {
            TChar txt = aHistory[index];
            if(aCharsBuf->Locate(txt)!=KErrNotFound || TEmotionUtils::IsEmotionChar(txt) || txt==KHistoryEmptyChar)
                {
                insertBuffer.Append(txt);
                }
            }

        while(insertBuffer.Length() < iMaxColumns)  // empty history stuff
            {
            insertBuffer.Append(KHistoryEmptyChar);
            }
        
        insertBuffer.SetLength(iMaxColumns);        // max length is one line
        
        // Emotion switch char
        if(Extension()->NeedEmotionSwitchIcon())
            {
            insertBuffer.Append(aSwitchChar);
            }

        // insert to des buffer
        TInt charsLength = insertBuffer.Length() + aCharsBuf->Length(); // history + Emotion swich char + text
        aCharsBuf = aCharsBuf->ReAllocL(charsLength);
        aCharsBuf->Des().Insert(0, insertBuffer);                       // history
        }

    return aCharsBuf;
    }

// -----------------------------------------------------------------------------
// CAknCharMapHistory::IsRecentChar()
// Check whether the character(of index) is recent data, or not
// The default value of first argument is 0.
// -----------------------------------------------------------------------------
//
TBool CAknCharMap::IsRecentChar(TInt aIndex /*=0*/) const
    {
    TBool rtn = EFalse;
    if (iCharMapHistory)
        {
        switch (iChaMapTableCase)
            {
            case EAknCharMapTableSpecialChar:
                switch (iSpecialCharCase)
                    {
                    case EAknSCTHalfCase:
                    case EAknSCTLowerCase:
                    case EAknSCTUpperCase:
                    case EAknSCTNumeric:
                    case EAknSCTQwerty:
                    case EAknSCTFullCase:
                        if (aIndex<iMaxColumns && iSetRecentSct)
                            {
                            rtn = ETrue;
                            }
                        break;
                    default:
                        break;
                    }
                break;
            case EAknCharMapTablePicto:
            case EAknCharMapTablePicto2:
                if (aIndex<iMaxColumns && iSetRecentSct)
                    {
                    rtn = ETrue;
                    }
                break;
            default:
                break;
            }
        }
    return rtn;
    }

// -----------------------------------------------------------------------------
// CAknCharMapHistory::SaveRecentDataL()
// Save the recent data
// -----------------------------------------------------------------------------
//
void CAknCharMap::SaveRecentDataL(TChar aChar)
    {
    __ASSERT_ALWAYS( iCharMapHistory, Panic(EAknPanicInvalidValue));

    CAknCharMapHistory::THistoryType historyType = CAknCharMapHistory::EHistoryTypeNull;

    switch (iChaMapTableCase)
        {
        case EAknCharMapTableSpecialChar:
            switch (iSpecialCharCase)
                {
                case EAknSCTHalfCase:
                case EAknSCTLowerCase:
                case EAknSCTUpperCase:
                case EAknSCTNumeric:
                case EAknSCTQwerty:
                    historyType = CAknCharMapHistory::EHistoryTypeHalf;
                    break;
                case EAknSCTFullCase:
                    historyType = CAknCharMapHistory::EHistoryTypeFull;
                    break;
                default:
                    break;
                }
            break;
            
        case EAknCharMapTablePicto:
        case EAknCharMapTablePicto2:
            historyType = (iCaseIndex==0) ? CAknCharMapHistory::EHistoryTypePicto : CAknCharMapHistory::EHistoryTypePicto2;
            break;
            
        default:
            break;
        }
    
    if (historyType > CAknCharMapHistory::EHistoryTypeNull)
        {
        iCharMapHistory->InsertChar(historyType, aChar);
        }

    // Save recent data
    iCharMapHistory->SaveL();
    }

// -----------------------------------------------------------------------------
// CAknCharMap::ConstructMenuSctRowL()
// Constructs the SCT for editing menu.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknCharMap::ConstructMenuSctRowL()
    {
    Extension()->iMenuSct = ETrue;
    TResourceReader reader;

    TInt resourceId = R_AVKON_MENU_SCT_ROW_DEFAULT_CONTENTS;
    if (FeatureManager::FeatureSupported(KFeatureIdChinese))
        {
        resourceId = R_AVKON_MENU_SCT_ROW_DEFAULT_CONTENTS_CHINESE;
        }

    CCoeEnv::Static()->CreateResourceReaderLC( reader, resourceId );
    ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    }


EXPORT_C void CAknCharMap::ConstructMenuSctRowL(TInt aResourceId)
    {
    Extension()->iMenuSct = ETrue;
    Extension()->iMenuSctHighlighted = ETrue;
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader,
                                aResourceId );
    ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    }


// -----------------------------------------------------------------------------
// CAknCharMap::ConstructMenuSctRowFromDialogL()
// Constructs the SCT for editing menu from the set resource.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknCharMap::ConstructMenuSctRowFromDialogL(TInt aResourceId)
    {
    Extension()->iMenuSct = ETrue;
    Extension()->iMenuSctHighlighted = ETrue;

    CEikDialog* dialog = new(ELeave) CEikDialog();
    dialog->ReadResourceLC(aResourceId);
    CAknCharMap* charmapControl = STATIC_CAST(CAknCharMap*, dialog->Control(EAknSCTQueryContentId));

    // the code below emulates ConstructFromResourceL(), but gets value from charmapControl
    CopyCharactersL(*charmapControl);     // replaces ReadCharSetFromResourceL()
    CleanupStack::PopAndDestroy(dialog);
    TBuf<32> fileName(KResFileName);
    TInt langcode= iAvkonEnv->SettingCache().InputLanguage();
    if (langcode < 10)
        {
        fileName.Append('0');
        }
    fileName.AppendNum(langcode);
    TResourceReader reader;
    RFs& fs = iEikonEnv->FsSession();
    if ( BaflUtils::FileExists(fs, fileName) )
        {
        RResourceFile resourceFile;
        resourceFile.OpenL( fs, fileName );
        CleanupClosePushL( resourceFile ); // push
        resourceFile.ConfirmSignatureL( 0 );
        if ( resourceFile.OwnsResourceId(aResourceId) )
            {
            HBufC8* resource=
                resourceFile.AllocReadLC(aResourceId); // push
            reader.SetBuffer(resource);
            TBuf<32> specialChars;
            CAknCharMapDialog* langDialog =
                new( ELeave ) CAknCharMapDialog(
                    EAknSCTLowerCase, specialChars );
            CleanupStack::PushL( langDialog ); // push
            langDialog->CreateWindowL();
            langDialog->ConstructFromResourceL(reader);
            CAknCharMap* langMap = STATIC_CAST( CAknCharMap*,
                langDialog->Control( EAknSCTQueryContentId ) );
            CopyCharactersL( *langMap );
            CleanupStack::PopAndDestroy(2); // langDialog, resource
            }
        CleanupStack::PopAndDestroy(); // resourcefile
        }

    if ( iExtension->iPictographsBuffer )
        {
        CreatePictoCharL();
        }

    if (!iCharMapHistory)
        {
        iCharMapHistory = CAknCharMapHistory::NewL();
        iSetRecentSct = ETrue;
        iSetRecentPic = ETrue;
        }

    if ( iExtension->iPictographsBuffer )
        {
        CreateOffscreenBackgroundL();
        }

    delete iExtension->iBgContext;
    iExtension->iBgContext = NULL;

    if ( DrawableWindow() && AknLayoutUtils::PenEnabled() )
        {
        EnableDragEvents();
        SetGloballyCapturing( ETrue );
        SetPointerCapture( ETrue );
        }
    }

// -----------------------------------------------------------------------------
// CAknCharMap::HighlightSctRow()
// Highlight the row of recent used character according to argument.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknCharMap::HighlightSctRow(TBool aHighlight)
    {
    // If the row is empty, nothing to do
    if (LengthOfRecentChar() == 0)
        {
        return;
        }
    
    HandleFocusStatusChanged(aHighlight);
    
    CWindowGc& gc = SystemGc();
    if( !CAknEnv::Static()->TransparencyEnabled() )
        {
        ActivateGc();
        gc.UseFont(iFont);
        }

    TInt cursorPos = iCursorPos.iX + iCursorPos.iY * iMaxColumns;
    DrawCell( cursorPos, aHighlight );

    if( !CAknEnv::Static()->TransparencyEnabled() )
        {
        gc.DiscardFont();
        DeactivateGc();
        }
    // Menu SCT is being used.
    if ( Extension()->iMenuSct )
    	{
    	Extension()->iMenuSctHighlighted = aHighlight;
    	}
    }
// -----------------------------------------------------------------------------
// CAknCharMap::SetMenuSctRect()
// Sets the rect for menu SCT.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknCharMap::SetMenuSctRect( const TRect& aRect )
    {
    
    if(Rect() == aRect) return;
    
    SetRect( aRect );

    if ( !iIsMirrored )
        {
        iGridTopLeft = aRect.iTl;
        iOffset.iX = aRect.iTl.iX + 1;
        iOffset.iY = aRect.iTl.iY + 1;
        }
    else
        {
        iGridTopLeft.iX = aRect.iBr.iX;
        iGridTopLeft.iY = aRect.iTl.iY;
        iOffset.iX = aRect.iTl.iX + 1;
        iOffset.iY = aRect.iTl.iY + 1;
        }


    DoLayout();
    
    if (iCharMapHistory)
        {
        CAknCharMapHistory::THistoryType charmap = CAknCharMapHistory::EHistoryTypeNull;
        
        switch (iSpecialCharCase)
            {
            case 0: // lower
                charmap = CAknCharMapHistory::EHistoryTypeHalf;
                break;
            case 1: // upper
                charmap = CAknCharMapHistory::EHistoryTypeHalf;
                break;
            case 2: // numeric
                charmap = CAknCharMapHistory::EHistoryTypeHalf;
                break;
            case 3: // full
                charmap = CAknCharMapHistory::EHistoryTypeFull;
                break;
            case 4: // half
                charmap = CAknCharMapHistory::EHistoryTypeHalf;
                break;
            case 5: // qwerty
                charmap = CAknCharMapHistory::EHistoryTypeHalf;
                break;
            case 6: // picto
                charmap = CAknCharMapHistory::EHistoryTypePicto;
                break;
            case 7: // picto 2
                charmap = CAknCharMapHistory::EHistoryTypePicto2;
                break;
            default:
                break;
            }
        
        CAknCharMapHistory::THistoryFilter historyFilter;
        if(iExtension->IsEmotionEnabled())
            {
            historyFilter = CAknCharMapHistory::EHistoryFilterMixed;
            }
        else
            {
            historyFilter = CAknCharMapHistory::EHistoryFilterTextOnly;
            }
        
        const TDesC& recentChars = iCharMapHistory->RecentString(charmap, historyFilter);
        
        // if iChars already contains HBufC, delete iChars and reset ichars
        if (iExtension->iFlags & EAknCharMapCharsAllocated)
            {
            delete iChars;
            iChars = NULL;
            if (iChaMapTableCase != EAknCharMapTableSpecialChar)
                {
                if (iCaseIndex == 1)
                    {
                    iChars = iPictographsBuffer2;
                    }
                else
                    {
                    iChars = iPictographsBuffer;
                    }
                iShowCasesRef = &iPictographCases;
                iShowPagesRef = &iPictographPages;
                }
            else
                {
                iShowCasesRef = &iSpecialCharCases;
                iShowPagesRef = &iSpecialCharPages;
                iChars = iCharsBufferLower;
                if (iCharsBufferUpper && iSpecialCharCase==EAknSCTUpperCase)
                    iChars = iCharsBufferUpper;
                else if (iCharsBufferNumeric && iSpecialCharCase==EAknSCTNumeric)
                    iChars = iCharsBufferNumeric;
                else if (iCharsBufferFull && iSpecialCharCase==EAknSCTFullCase)
                    iChars = iCharsBufferFull;
                else if (iCharsBufferHalf && iSpecialCharCase==EAknSCTHalfCase)
                    iChars = iCharsBufferHalf;
                else if (iExtension->iCharsQwerty && iSpecialCharCase==EAknSCTQwerty)
                    iChars = iExtension->iCharsQwerty;

                if(iChars == iCharsBufferLower)
                    {
                    iSpecialCharCase = EAknSCTLowerCase;
                    }
                }
            // mark that iChars doesn't point to HBufC
            iExtension->iFlags &= (~EAknCharMapCharsAllocated);
            }
        iRows = 1;
        TPtrC realChars = iChars->Des(); // get only the SCT chars

        // Check whether recent charcters are included in base charcters.
        HBufC* newrecent = HBufC::New(recentChars.Length());
        if( newrecent == NULL)
            {
            return;
            }

        TPtr ptrrecent(newrecent->Des());
        ptrrecent.Copy(recentChars);
        for (TInt index=0; index < ptrrecent.Length(); index++)
            {
            if (ptrrecent[index] != KHistoryEmptyChar)
                {
                if(TEmotionUtils::IsEmotionChar(ptrrecent[index]))
                    {
                    continue;
                    }
                else
                    {
                    TInt err = realChars.Locate(ptrrecent[index]);
                    if (err == KErrNotFound)
                        {
                        ptrrecent.Delete(index,1);
                        ptrrecent.Append(KHistoryEmptyChar);
                        index--;
                        }                       
                    }
                }
            }
        if (iExtension->iFlags & EAknCharMapCharsAllocated) // iChars already contains HBufC
            {                                               // so delete old instance
            delete iChars;
            iChars = NULL;
            }

        iChars = newrecent;
        iChars->Des().SetLength(iMaxColumns);
        if (iChaMapTableCase==EAknCharMapTableSpecialChar && (*iChars)[0] == KHistoryEmptyChar)
            {
            iCursorPos = TPoint(0, 1);
            }
        if (iCursorPos.iX >= iMaxColumns)
            {
            iCursorPos = TPoint(0, 0);
            }
        iExtension->iFlags |= EAknCharMapCharsAllocated; // mark that iChars points to HBufC
        }
    
    iExtension->LoadEmotionTumbnails(*iChars);

    HandleFocusStatusChanged();
    }

// -----------------------------------------------------------------------------
// CAknCharMap::CharacterCase()
// Get current character case.
// -----------------------------------------------------------------------------
//
TInt CAknCharMap::CharacterCase()
    {
    return iSpecialCharCase;
    }

// -----------------------------------------------------------------------------
// CAknCharMap::DisableRecentCharsRow()
// Hides the first row that shows recent characters.
// -----------------------------------------------------------------------------
//
void CAknCharMap::DisableRecentCharsRow()
    {
    if(!iSetRecentSct) return;
    
    iSetRecentSct = EFalse;
    iSetRecentPic = EFalse;
    
    TInt insertedLength = iMaxColumns;
    
    // Emotion switch char
    if(Extension()->NeedEmotionSwitchIcon())
        {
        insertedLength++;
        }

    for (TInt index=0; index < 8; index++ )
        {
        HBufC** base = NULL;
        
        switch (index)
            {
            case 0:
                base = &iCharsBufferFull;
                break;
            case 1:
                base = &iCharsBufferHalf;
                break;
            case 2:
                base = &iCharsBufferLower;
                break;
            case 3:
                base = &iCharsBufferUpper;
                break;
            case 4:
                base = &iCharsBufferNumeric;
                break;
            case 5:
                base = &iPictographsBuffer;
                break;
            case 6:
                base = &iExtension->iCharsQwerty;
                break;
            case 7:
                base = &iPictographsBuffer2;
                break;
            default:
                break;
            }
        
        if (*base)
            {
            // Remove recent characters from the beginning.
            // Length of removed characters is iMaxColumns
            (*base)->Des().Delete(0, insertedLength);
            }
        }
    
    // delete Emotion history
    iExtension->iCharsSmiley->Des().Delete(0, insertedLength);
    }


// -----------------------------------------------------------------------------
// CAknCharMap::Extension
// Asserts that extension object has been created.
// -----------------------------------------------------------------------------
//
CAknCharMapExtension* CAknCharMap::Extension() const
    {
    __ASSERT_ALWAYS( iExtension, Panic( EAknPanicNullPointer ) );
    return iExtension;
    }

// -----------------------------------------------------------------------------
// CAknCharMap::UpdateHeadingPane
// Updates page number and title in Heading Pane.
// -----------------------------------------------------------------------------
//
void CAknCharMap::UpdateHeadingPane( TBool aUpdateTitle )
    {
    if (iExtension->iObserver &&
        !AknLayoutUtils::PenEnabled() && !Extension()->iMenuSct)
        {
        CAknCharMapDialog* dialog =
            static_cast<CAknCharMapDialog*>(iExtension->iObserver );
        CAknPopupHeadingPane* headingPane =
            static_cast< CAknPopupHeadingPane* >
                (dialog-> Control( EAknSCTQueryHeadingId ) );

        if ( headingPane )
            {
            TRAP_IGNORE(
                {
                // Update heading pane's page number
                headingPane->SetPageL( CurrentPage(), PageCount() );

                // Update also title if requested
                if ( aUpdateTitle)
                    {
                    const TDesC* title = (IsJapaneseSctUi())?
                                         TitleWithSelectingSpecialChar()
                                         :Title();
                    if ( title )
                        {
                        //
                        headingPane->SetTextL( *title );
                        }
                    }
                } );
            }
        }
    }




void CAknCharMap::SetStatusChanged(const TInt aStatusChanged)
    {
    iStatusChanged = aStatusChanged;
    if (iExtension->iObserver)
        {
        TRAP_IGNORE( iExtension->iObserver->HandleControlEventL(this, MCoeControlObserver::EEventStateChanged) );
        }
    }

TInt CAknCharMap::StatusChanged()
    {
    return iStatusChanged;
    }

TInt CAknCharMap::CurrentCategory()
    {
    return iExtension->iCurrentCategory;
    }

TInt CAknCharMap::Category()
    {
    TInt category = EAknSCTCategoryButtonHalfCase;
    if (iChaMapTableCase == EAknCharMapTableSpecialChar)
        {
        if (iSpecialCharCase == EAknSCTFullCase)
            {
            category = EAknSCTCategoryButtonFullCase;
            }
        }
    else
        {
        if (iExtension->iPictographsBufferGrouping)
            {
            category = (iCaseIndex == 1) ?
                EAknSCTCategoryButtonPicto2 : EAknSCTCategoryButtonPicto1;
            }
        else
            {
            category = EAknSCTCategoryButtonPicto;
            }
        }
    return category;
    }

/**
 * Change to new category
 */
TBool CAknCharMap::ChangeCategoryL(const TInt aCategory, TBool& aLayoutChanged)
    {
    TBool result(ETrue);

    aLayoutChanged = EFalse;

    TInt oldVisibleRows = iRows;
    if (oldVisibleRows > iExtension->iMaxVisibleRows)
        {
        oldVisibleRows = iExtension->iMaxVisibleRows;
        }

    switch (aCategory)
        {
        case EAknSCTCategoryButtonHalfCase:
            iChaMapTableCase = EAknCharMapTableSpecialChar;
            SetCharacterCaseL(EAknSCTHalfCase);
            break;
        case EAknSCTCategoryButtonFullCase:
            iChaMapTableCase = EAknCharMapTableSpecialChar;
            SetCharacterCaseL(EAknSCTFullCase);
            break;
        case EAknSCTCategoryButtonPicto:
            iChaMapTableCase = EAknCharMapTablePicto;
            iCaseIndex = 0;
            SetCharacterCaseL(iSpecialCharCase);
            break;
        case EAknSCTCategoryButtonPicto1:
            iChaMapTableCase = EAknCharMapTablePicto;
            iCaseIndex = 0;
            SetCharacterCaseL(iSpecialCharCase);
            break;
        case EAknSCTCategoryButtonPicto2:
            iChaMapTableCase = EAknCharMapTablePicto;
            iCaseIndex = 1;
            SetCharacterCaseL(iSpecialCharCase);
            break;
        default:
            Panic(EAknPanicOutOfRange);
            break;
        }

    TInt visibleRows = iRows;
    if (visibleRows > iExtension->iMaxVisibleRows)
        {
        visibleRows = iExtension->iMaxVisibleRows;
        }

    // Return also information whether the layout changed or not.
    aLayoutChanged = ( oldVisibleRows != visibleRows );

    UpdateScrollIndicatorL();

    UpdateInputFieldL();

    RefreshNaviPageL();

    if (aLayoutChanged)
        {
        // If the number of the visible row is changed,
        // it is necessary to re-create the background.
        CreateOffscreenBackgroundL();
        }
    return result;
    }


TBool CAknCharMap::IsSupportCategoryButtonUi() const
    {
    return (iExtension)? iExtension->iHasCategoryButtonUi : EFalse;
    }

TBool CAknCharMap::IsJapaneseSctUi() const
    {
    return (iExtension)? iExtension->iJapaneseSctUi : EFalse;
    }

// -----------------------------------------------------------------------------
// CAknCharMap::TitleWithSelectingSpecialChar()
// Return the title string with the selecting special characters
// -----------------------------------------------------------------------------
//

const TDesC* CAknCharMap::TitleWithSelectingSpecialChar()
    {
    const TDesC* title = Title();
    TRAPD(err, CreateTitleWithSelectingSpecialCharL(title));
    if (err != KErrNone)
        {
        return title;
        }
    else
        {
        return Extension()->iTitleBuf;
        }
    }

// -----------------------------------------------------------------------------
// CAknCharMap::ChangeFocusSct()
// Change the current focus either Grid or Category buttons
// If aFocusOn is EFalse, from Grid to Category buttons,
// If aFocusOn is ETrue, from Category buttons to Grid
// -----------------------------------------------------------------------------
//
void CAknCharMap::ChangeFocusSct(TBool aFocusOn)
    {
    CWindowGc& gc = SystemGc();
    if( !CAknEnv::Static()->TransparencyEnabled() )
        {
        ActivateGc();
        gc.UseFont(iFont);
        }

    TInt cursorPos = iCursorPos.iX + iCursorPos.iY * iMaxColumns;
    DrawCell( cursorPos, aFocusOn );

    if( !CAknEnv::Static()->TransparencyEnabled() )
        {
        gc.DiscardFont();
        DeactivateGc();
        }
    }

// -----------------------------------------------------------------------------
// CAknCharMap::CreateTitleWithSelectingSpecialCharL()
// Create the string mixing title and the selecting special characters,
// and Set it to Extension()->iTitleBuf.
// -----------------------------------------------------------------------------
//
void CAknCharMap::CreateTitleWithSelectingSpecialCharL(const TDesC* aTitle)
    {
    const TDesC* title = aTitle;
    if ( title )
        {
        if (!AknLayoutUtils::PenEnabled())
            {
            CAknCharMapDialog* dialog =
                static_cast<CAknCharMapDialog*>(iExtension->iObserver);
            CAknPopupHeadingPane* headingPane =
                static_cast<CAknPopupHeadingPane*>(
                    dialog->Control(EAknSCTQueryHeadingId));
            if (Extension()->iTitleBuf)
                {
                delete Extension()->iTitleBuf;
                Extension()->iTitleBuf =NULL;
                }
            Extension()->iTitleBuf =
                HBufC::NewL(title->Length() + iFetcherCharsBuffer->Length());
            TPtr titlePtr(Extension()->iTitleBuf->Des());
            HBufC* tempBuf = iFetcherCharsBuffer->AllocLC();
            TPtr tempPtr(tempBuf->Des());

            CCoeControl* titleCtrl = (CCoeControl*)headingPane->Prompt();
            TRect promptRect = titleCtrl->Rect();

            TInt varietyIndex = (AknLayoutUtils::PenEnabled())? 3 : 1;
            TAknTextComponentLayout textLayout =
                AknLayoutScalable_Avkon::heading_pane_t1(varietyIndex);

            TRect parentRect;
            TAknLayoutRect popupRect;
            if(!AknLayoutUtils::LayoutMetricsRect(
                AknLayoutUtils::EPopupParent, parentRect))
                {
                parentRect = iAvkonAppUi->ClientRect();
                }
            popupRect.LayoutRect(parentRect,
                AknLayoutScalable_Avkon::popup_window_general(1));

            TAknLayoutRect headingRect;
            TAknWindowComponentLayout headingPaneLayout =
                AknLayoutScalable_Avkon::heading_pane(0);
            headingRect.LayoutRect(TRect(TPoint(0,0),
                popupRect.Rect().Size()), headingPaneLayout);
            parentRect = headingRect.Rect();

            TAknLayoutText textRect;
            textRect.LayoutText(parentRect, textLayout);
            TInt controlWidth = textRect.TextRect().Width();

            const CFont* promptFont =
                AknLayoutUtils::FontFromId( textLayout.Font() );

            TInt titleWidth = promptFont->TextWidthInPixels(*title);
            TInt textWidth = promptFont->TextWidthInPixels(tempPtr);
            FOREVER
                {
                if (titleWidth >= controlWidth)
                    {
                    titlePtr.Append(*title);
                    break;
                    }
                if (controlWidth >= (titleWidth + textWidth))
                    {
                    titlePtr.Append(*title);
                    titlePtr.Append(tempPtr);
                    break;
                    }
                if (tempPtr.Length() > 1)
                    {
                    tempPtr.Delete(0,1);
                    tempPtr[0] = CEditableText::EEllipsis;
                    textWidth = promptFont->TextWidthInPixels(tempPtr);
                    }
                else
                    {
                    titleWidth = controlWidth + 1;
                    }
                }
            CleanupStack::PopAndDestroy(tempBuf);
            }
        }
    }

void CAknCharMap::RefreshNaviPageL()
    {
    if (iExtension->iPageNavi)
        {
        iExtension->iPageNavi->UpdatePageTitleL();
        }
    }

TAknChaMapTableCase CAknCharMap::NextTableCase() const
    {
    return EAknCharMapTableSpecialChar; // Currently no other maps supported.
    }

MAknSctFocusHandler* CAknCharMap::FocusHandler()
    {
    return iExtension->iFocusHandler;
    }

CCoeControl* CAknCharMap::FocusedControl()
    {
    return this;
    }

TBool CAknCharMap::EnterControl(TInt aX, TInt aY)
    {
    if ((aY < 0) || (aY >= iExtension->iMaxVisibleRows))
        {
        return EFalse; // Out of grid.
        }

    if ((aX < 0) || (aX >= iMaxColumns))
        {
        return EFalse; // Out of grid.
        }

    TInt pos = 0;

    CWindowGc& gc = SystemGc();
    if(!CAknEnv::Static()->TransparencyEnabled())
        {
        ActivateGc();
        gc.UseFont(iFont);
        }

    // clear cell
    pos = iCursorPos.iX + iCursorPos.iY * iMaxColumns;
    DrawCell( pos, EFalse );

    iCursorPos = TPoint(aX, aY); // new pos.

    // highlight cell
    pos = iCursorPos.iX + iCursorPos.iY * iMaxColumns;
    DrawCell( pos, ETrue );

    UpdateHeadingPane( ETrue );

    if( !CAknEnv::Static()->TransparencyEnabled() )
        {
        gc.DiscardFont();
        DeactivateGc();
        }

    return ETrue;
    }

void CAknCharMap::MoveFocus(TInt aX, TInt aY)
    {
    TRAP_IGNORE(MoveCursorL(aX,aY));
    }

TBool CAknCharMap::LeaveControl()
    {
    HandleFocusStatusChanged(EFalse);
    
    CWindowGc& gc = SystemGc();
    if( !CAknEnv::Static()->TransparencyEnabled() )
        {
        ActivateGc();
        gc.UseFont(iFont);
        }

    TInt pos = iCursorPos.iX + iCursorPos.iY * iMaxColumns;
    DrawCell( pos, EFalse );

    if( !CAknEnv::Static()->TransparencyEnabled() )
        {
        gc.DiscardFont();
        DeactivateGc();
        }

    return ETrue;
    }

TInt CAknCharMap::TableCount() const
    {
    // Numbers of tables excluding pictographs.
    // there will be sct table and Emotion table(if enabled)
    return Extension()->IsEmotionEnabled() ? 2 : 1;
    }

void CAknCharMap::UpdateInputFieldL()
    {
    if (!iExtension)
        {
        return; // Not ready for updates.
        }

    TInt variety = Layout_Meta_Data::IsLandscapeOrientation() ? 1 : 0;

    // Update title field.
    const TDesC* title = Title();
    if (iExtension->iCategoryTitle && title)
        {
        iExtension->iCategoryTitle->SetTextL(*title);
        Window().Invalidate(iExtension->iCategoryTitle->Rect());
        iExtension->iCategoryTitle->SetBrushStyle(
            CGraphicsContext::ENullBrush);
        }

    // Update entry field.
    if (iExtension->iCategoryEntry &&
        iFetcherCharsBuffer && iFetcherCharsBuffer->Length()>0)
        {
        if (Extension()->iEntryBuf)
            {
            delete Extension()->iEntryBuf;
            Extension()->iEntryBuf =NULL;
            }
        Extension()->iEntryBuf =
            HBufC::NewL(iFetcherCharsBuffer->Length());
        TPtr entryPtr(Extension()->iEntryBuf->Des());

        HBufC* tempBuf = iFetcherCharsBuffer->AllocLC();
        TPtr tempPtr(tempBuf->Des());

        TInt variety =
            Layout_Meta_Data::IsLandscapeOrientation() ? 1 : 0;
        const CFont* entryFont = AknLayoutUtils::FontFromId(
            AknLayoutScalable_Avkon::popup_grid_graphic2_window_t2(variety).Font());
        TInt entryWidth = entryFont->TextWidthInPixels(tempPtr);

        TInt controlWidth = Extension()->iCategoryEntry->Size().iWidth;

        FOREVER
            {
            if (entryWidth < controlWidth)
                {
                entryPtr.Append(tempPtr);
                break;
                }
            if (tempPtr.Length() > 1)
                {
                tempPtr.Delete(0,1);
                tempPtr[0] = CEditableText::EEllipsis;
                entryWidth = entryFont->TextWidthInPixels(tempPtr);
                }
            else
                {
                entryWidth = controlWidth + 1;
                }
            }

        Extension()->iCategoryEntry->SetTextL(tempPtr);
        Window().Invalidate(iExtension->iCategoryEntry->Rect());
        Extension()->iCategoryEntry->SetBrushStyle(
            CGraphicsContext::ENullBrush);

        CleanupStack::PopAndDestroy(tempBuf);
        }
    }

TInt CAknCharMap::RowMin(TInt aRow) const
    {
    TInt index = KErrNotFound;
    if ((aRow >= 0) && (aRow < iExtension->iMaxVisibleRows))
        {
        TInt start = (iFirstVisibleRow + aRow) * iMaxColumns;
        for (TInt i = 0; i < iMaxColumns; i++)
            {
            TInt pos = start + i;
            if ((pos >= 0) && (pos < iChars->Length()))
                {
                if ((*iChars)[pos] != KHistoryEmptyChar)
                    {
                    index = i; // the first valid cell in the row.
                    break;
                    }
                }
            }
        }
    return index;
    }

TInt CAknCharMap::RowMax(TInt aRow) const
    {
    TInt index = KErrNotFound;
    if ((aRow >= 0) && (aRow < iExtension->iMaxVisibleRows))
        {
        TInt start = (iFirstVisibleRow + aRow) * iMaxColumns;
        for (TInt i = iMaxColumns - 1; i >= 0; i--)
            {
            TInt pos = start + i;
            if ((pos >= 0) && (pos < iChars->Length()))
                {
                if ((*iChars)[pos] != KHistoryEmptyChar)
                    {
                    index = i; // the last valid cell in the row.
                    break;
                    }
                }
            }
        }
    return index;
    }

TInt CAknCharMap::ColMin(TInt aCol) const
    {
    TInt index = KErrNotFound;
    if ((aCol >= 0) && (aCol < iMaxColumns))
        {
        TInt start = iFirstVisibleRow * iMaxColumns + aCol;
        for (TInt i = 0; i < iExtension->iMaxVisibleRows; i++)
            {
            TInt pos = start + iMaxColumns * i;
            if ((pos >= 0) && (pos < iChars->Length()))
                {
                if ((*iChars)[pos] != KHistoryEmptyChar)
                    {
                    index = i; // the first valid cell in the column.
                    break;
                    }
                }
            }
        }
    return index;
    }

TInt CAknCharMap::ColMax(TInt aCol) const
    {
    TInt index = KErrNotFound;
    if ((aCol >= 0) && (aCol < iMaxColumns))
        {
        TInt start = iFirstVisibleRow * iMaxColumns + aCol;
        for (TInt i = iExtension->iMaxVisibleRows - 1; i >= 0; i--)
            {
            TInt pos = start + iMaxColumns * i;
            if ((pos >= 0) && (pos < iChars->Length()))
                {
                if ((*iChars)[pos] != KHistoryEmptyChar)
                    {
                    index = i; // the last valid cell in the column.
                    break;
                    }
                }
            }
        }
    return index;
    }

TInt CAknCharMap::MaxCols() const
    {
    return iMaxColumns;
    }

TBool CAknCharMap::TakeFocus()
    {
    TInt success = EFalse;
    if (iExtension->iFocusHandler->FocusedControl() != this)
        {
        iExtension->iFocusHandler->LeaveControl();
        iExtension->iFocusHandler = iExtension;
        success = ETrue;
        }
    return success;
    }

void CAknCharMap::ShowFocus()
    {
    ChangeFocusSct(ETrue);
    }

TPoint CAknCharMap::CursorPos()
    {
    return iCursorPos;
    }


// for emotion added

void CAknCharMap::HandleFocusStatusChanged(TBool aIsFocused)
    {
    TInt focusPos = iCursorPos.iX + (iFirstVisibleRow + iCursorPos.iY) * iMaxColumns;
    if(focusPos>=0 && focusPos<iChars->Length())
        {
        aIsFocused &= (iExtension->iFocusHandler->FocusedControl()==this);
        iExtension->HandleFocusStatusChanged((*iChars)[focusPos], aIsFocused);
        }
    }

TBool CAknCharMap::EmotionsAreAllReadyToDraw(TInt aIndex, TInt aCount) const
    {
    for(TInt i(0); i<aCount; i++)
        {
        if(aIndex < iChars->Length())
            {
            TChar name = (*iChars)[aIndex++];
            CSmileyIcon* icon = iExtension->EmotionIcon(name);
            if(icon && !icon->ReadyToDraw())
                {
                return EFalse;
                }
            }
        else
            {
            break;
            }
        }
    
    return ETrue;
    }

void CAknCharMap::GetFocusSctName(TChar& aChar, TDes& aName) const
    {
    TInt pos = iMaxColumns * (iFirstVisibleRow + iCursorPos.iY) + iCursorPos.iX;
    
    aChar = (*iChars)[pos];
    
    aName.Zero();
    
    if(TEmotionUtils::IsEmotionChar(aChar))
        {
        CSmileyIcon* icon = iExtension->EmotionIcon(aChar);
        if ( icon )
            {
            aName.Append(icon->Name());
            }
        }
    else
        {
        aName.Append(aChar);
        }
    }

TBool CAknCharMap::HaveBufferToAppendFocusSct() const
    {
    TChar sctChar;
    TBuf<10> sctName;
    GetFocusSctName(sctChar, sctName);
    
    return ( iFetcherCharsBuffer->Length() + sctName.Length() < iFetcherCharsBuffer->MaxLength() );
    }

TBool CAknCharMap::AppendFocusSctToDestinationBufferL()
    {
    TBool appended = EFalse;
    
    TChar sctChar;
    TBuf<10> sctName;
    GetFocusSctName(sctChar, sctName);

    if(Extension()->NeedEmotionSwitchIcon() && 
       (sctChar==TEmotionUtils::EmotionSwitchToSctChar() || sctChar==TEmotionUtils::EmotionSwitchToSmileyChar()))
        {
        SwitchSctAndEmotionL();
        }
    else if(iFetcherCharsBuffer->Length() + sctName.Length() < iFetcherCharsBuffer->MaxLength())
        {
        iFetcherCharsBuffer->Append(sctName);

        if (iCharMapHistory)
            {
            SaveRecentDataL(sctChar);
            }
        
        appended = ETrue;
        }
    else
        {
        return EFalse; // return here
        }
        
    if (!Extension()->iMenuSct)
        {
        UpdateHeadingPane( ETrue );
        }
    
    if (iExtension->iCategoryEntry)
        {
        iExtension->iCategoryEntry->SetTextL(*iFetcherCharsBuffer);
        UpdateInputFieldL();
        }

    return appended;

    }

TBool CAknCharMap::SwitchSctAndEmotionL()
    {
    if(Extension()->IsEmotionEnabled())
        {
        Extension()->iIsShowingEmotion = !Extension()->IsShowingEmotion();
        
        SetCharacterCaseL(iSpecialCharCase);
        
        CAknSctTableNavi* tableNavi = Extension()->iTableNavi;
        if(tableNavi)
            {
            tableNavi->UpdateNextTableButtonL();
            }

        DrawNow();
        
        return ETrue;
        }
    else
        {
        return EFalse;
        }
    }


//  End of File
