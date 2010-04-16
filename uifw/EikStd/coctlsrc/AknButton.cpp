/*
* Copyright (c) 2005-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Button component
*
*/


// INCLUDE FILES
#include <aknbutton.h>

#include <gulicon.h>        // CGulIcon
#include <barsread.h>       // TResourceReader
#include <avkon.hrh>
#include <StringLoader.h>   // StringLoader
#include <AknsDrawUtils.h>
#include <AknsControlContext.h>
#include <AknBidiTextUtils.h>
#include <aknlayout.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <AknInfoPopupNoteController.h>
#include <AknPictographInterface.h>
#include <AknPictographDrawerInterface.h>
#include <AknsFrameBackgroundControlContext.h>
#include <aknconsts.h>
#include <layoutmetadata.cdl.h>
#include <AknPriv.hrh>
#include <AknLayoutFont.h>
#include <akniconconfig.h>

#include <AknTasHook.h> // for testability hooks
#include "aknresourceprovider.h"
#include "aknbitmapresourceitem.h"
#include "akncommandbuttonstate.h"

#include <touchfeedback.h>
const TUint KPointerFlag = 3; // second bit
 

// CONSTANTS
enum TSkinItemIdIndex
    {
    KFrameId = 0,
    KCenterId,
    KLatchedFrameId,
    KLatchedCenterId,
    KDimmedFrameId,
    KDimmedCenterId,
    KPressedFrameId,
    KPressedCenterId,
    KLatchedDimmedFrameId,
    KLatchedDimmedCenterId
    };

// ATTENTION, if the values bellow are changed, make the changes in AknButton.h
const TInt KTimeoutBeforeHelpNote = 150; // in milliseconds
const TInt KTimeoutInViewHelpNote = 3000; // in milliseconds

const TInt KKeyRepeatDelay = 500000;   // 0,5 seconds
const TInt KKeyRepeatInterval = 500000; // 0,5 seconds
const TInt KLongPressInterval = 800000; // 0,8 seconds

const TInt KDragEventSensitivity = 1;

// Value table for 70% Transparency 
const TInt KTransparency[256] =
    { 
    0, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 7, 7, 7,
    8, 8, 8, 8, 9, 9, 9, 10, 10, 10, 11, 11, 11, 11, 12, 12, 12, 13, 13, 13,
    14, 14, 14, 14, 15, 15, 15, 16, 16, 16, 17, 17, 17, 17, 18, 18, 18, 19,
    19, 19, 20, 20, 20, 20, 21, 21, 21, 22, 22, 22, 23, 23, 23, 23, 24, 24,
    24, 25, 25, 25, 26, 26, 26, 26, 27, 27, 27, 28, 28, 28, 29, 29, 29, 29,
    30, 30, 30, 31, 31, 31, 32, 32, 32, 32, 33, 33, 33, 34, 34, 34, 35, 35,
    35, 35, 36, 36, 36, 37, 37, 37, 38, 38, 38, 38, 39, 39, 39, 40, 40, 40,
    41, 41, 41, 41, 42, 42, 42, 43, 43, 43, 44, 44, 44, 44, 45, 45, 45, 46,
    46, 46, 47, 47, 47, 47, 48, 48, 48, 49, 49, 49, 50, 50, 50, 50, 51, 51,
    51, 52, 52, 52, 53, 53, 53, 53, 54, 54, 54, 55, 55, 55, 56, 56, 56, 56,
    57, 57, 57, 58, 58, 58, 59, 59, 59, 59, 60, 60, 60, 61, 61, 61, 62, 62,
    62, 62, 63, 63, 63, 64, 64, 64, 65, 65, 65, 65, 66, 66, 66, 67, 67, 67,
    68, 68, 68, 68, 69, 69, 69, 70, 70, 70, 71, 71, 71, 71, 72, 72, 72, 73,
    73, 73, 74, 74, 74, 74, 75, 75, 75, 76, 76, 76, 77, 77 
    };

// -----------------------------------------------------------------------------
// ResizeIcon
// Tries to resize the given icon. If the operation fails the icon is deleted.
// -----------------------------------------------------------------------------
//
static TInt ResizeIcon( CGulIcon*& aIcon, 
                        const TSize& aSize, 
                        TScaleMode aScaleMode )
    {
    TInt retval = KErrNotFound;
    
    if ( aIcon )
        {
        CFbsBitmap* bmp = aIcon->Bitmap();
        
        if ( bmp )
            {
            retval = !( aSize == bmp->SizeInPixels() );
            }
            
        if ( retval != KErrNone )
            {
            retval = AknIconUtils::SetSize( bmp, aSize, aScaleMode );
            }

        // Retval is checked outside of the "if ( bmp )" scope above in order
        // to detect if the given icon's bitmap is NULL. This is required since
        // AknIconUtils::SetSize returns KErrNone for NULL bitmaps and we want
        // to delete icons that couldn't be resized.
        if ( retval != KErrNone )
            {
            delete aIcon;
            aIcon = NULL;
            }
        }
        
    return retval;        
    }
    
static void ReplaceIconStatic( CGulIcon*& aIcon, CGulIcon* aNewIcon, 
                               TScaleMode aScaleMode )
    {
    TSize iconSize( 0, 0 );
    
    if ( aIcon && aIcon->Bitmap() )
        {
        iconSize = aIcon->Bitmap()->SizeInPixels();
        }
        
    delete aIcon;
    aIcon = aNewIcon;
    
    if ( iconSize != TSize( 0, 0 ) )
        {
        ResizeIcon( aIcon, iconSize, aScaleMode );
        }
    }
    
// -----------------------------------------------------------------------------
// CreateAndSetDimmedIconL
// Creates and sets a dimmed icon from the normal icon 
// by making a partially transparent version of it.
//
// @param aIcon The original icon
// @param aDimmedIcon The dimmed icon
// @param aScaleMode The preferred ScaleMode
// -----------------------------------------------------------------------------
static void CreateAndSetDimmedIconL( CGulIcon*& aDimmedIcon, 
                                     const CGulIcon* aIcon, 
                                     TScaleMode aScaleMode )
    {
    if ( aIcon )
        {
        CFbsBitmap* mask = aIcon->Mask();
        
        if ( mask && mask->DisplayMode() == EGray256 )
            {
            CGulIcon* newIcon = CGulIcon::NewLC();
            CFbsBitmap* newPic = new ( ELeave ) CFbsBitmap;
            CleanupStack::PushL( newPic );
            
            newPic->Duplicate( aIcon->Bitmap()->Handle() );
            newIcon->SetBitmap( newPic );

            CFbsBitmap* newMask = new ( ELeave ) CFbsBitmap;
            
            User::LeaveIfError( newMask->Create( 
                newIcon->Bitmap()->SizeInPixels(), EGray256 ) );
            CleanupStack::PushL( newMask );
               
            CFbsBitmapDevice* bitmapDevice = CFbsBitmapDevice::NewL( newMask );
            CleanupStack::PushL( bitmapDevice );
            
            CFbsBitGc* bitGc( NULL );
            User::LeaveIfError( bitmapDevice->CreateContext( bitGc ) );
            CleanupStack::PushL( bitGc );
    
            bitGc->SetPenStyle( CGraphicsContext::ESolidPen );
            bitGc->BitBlt( TPoint( 0, 0 ), mask );
           
            newMask->LockHeap();
            TInt w = mask->SizeInPixels().iWidth; 
            TInt h = mask->SizeInPixels().iHeight;
            TInt dataStride = mask->DataStride() - w; 
            unsigned char* address = (unsigned char *)newMask->DataAddress();  
            
            for ( TInt i = 0; i < h; ++i )
                {
                for ( TInt j = 0; j < w; ++j )
                    {
                    *address = KTransparency[*address];
                    ++address;
                    }
                address += dataStride;         
                }

            newMask->UnlockHeap();
            newIcon->SetMask( newMask );
            ReplaceIconStatic( aDimmedIcon, newIcon, aScaleMode );
                               
            CleanupStack::PopAndDestroy( 2 ); // bitmapDevice, bitGc
            CleanupStack::Pop( 3 ); // newIcon, newPic, newMask
            }
        }
    }
// ============================ EXTENSION CLASS ================================

NONSHARABLE_CLASS( CAknButtonExtension ) : public CBase, MCoeControlHitTest
    {
    friend class CAknButton;    

public:
    // bitflags used to keep track of several button's internal features
    enum TFlags
        {
        EUseAdditionalMask,
        ECheckHitArea,
        EDimmed,
        ELongPressReported,
        EUseDefaultIconSize,
        EKeyRepeatEventReported,
        EUseDefaultMargins
        };
        
    static CAknButtonExtension* NewL( CAknButton& aButton );
    ~CAknButtonExtension();

    // Starts the long press timer.
    void StartLongPressTimerL();
    
    TBool HitRegionContains( const TPoint &aPoint, 
                             const CCoeControl &aControl ) const;

    void HandleFeedbackAreaChange();
private:

    CAknButtonExtension( CAknButton& aButton );
    void ConstructL();

    // Callback method for long press timer.
    static TInt ReportLongPressL( TAny* aThis );

    // Handles long press.
    void DoReportLongPressL();

    // Deletes pressed down bitmaps
    void DeletePressedBmps();

    // Fetches bitmaps from resource provider (if one exists)
    TBool FetchProviderPressedBmpsL();

    // Sets bitmaps to resource provider (if one exists)
    void SetProviderPressedBmpsL();

private: // Data

    CAknButton& iButton;
    CAknButton::TTooltipPosition iTooltipPosition;
    CAknPictographInterface* iPictographInterface; // not owned
    CPeriodic* iLongPressTimer;
    TInt iLongPressInterval;
    TFontUnderline iUnderlineStyle;
    RArray<TAknsItemID> iFrameAndCenterIds;
    CAknButton::TAlignment iVerticalIconAlignment; 
    CAknButton::TAlignment iHorizontalIconAlignment;
    TMargins8 iMargins;
    TSize iIconSize;
    CAknButton::TTextAndIconAlignment iTextAndIconAlignment;
    TBitFlags iFlags;
    MTouchFeedback* iFeedback;
    CFbsBitmap* iPressedDownBmp;
    CFbsBitmap* iPressedDownBmpMask;
    CAknResourceProvider* iResourceProvider;
    };

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknButtonExtension::CAknButtonExtension
// C++ default constructor.
// -----------------------------------------------------------------------------
//
CAknButtonExtension::CAknButtonExtension( CAknButton& aButton )
    : iButton( aButton ),
      iTooltipPosition( CAknButton::EPositionTop ),
      iLongPressTimer( NULL ),
      iLongPressInterval( KLongPressInterval ),
      iUnderlineStyle( EUnderlineOff ),
      iFrameAndCenterIds( 2 ),
      iVerticalIconAlignment( CAknButton::ECenter ),
      iHorizontalIconAlignment( CAknButton::ECenter ),
      iTextAndIconAlignment( CAknButton::EIconBeforeText ),
      iResourceProvider( 0 )
    {
    // default margins, these are applied to both text and icon
    iMargins.SetAllValuesTo( 
        AknLayoutScalable_Avkon::aid_value_unit2().LayoutLine().iW / 10 );
        
    // default icon size
    TRect rect( TSize( 100, 100 ) );
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( rect, 
        AknLayoutScalable_Avkon::toolbar_button_pane_g10().LayoutLine() );
    iIconSize = layoutRect.Rect().Size();
    iFlags.Set( EUseDefaultIconSize );
    iFlags.Set( EUseDefaultMargins );
    }

// -----------------------------------------------------------------------------
// CAknButtonExtension::~CAknButtonExtension
// Destructor.
// -----------------------------------------------------------------------------
//
CAknButtonExtension::~CAknButtonExtension()
    {
    delete iLongPressTimer;
    iPictographInterface = NULL; // not owned
    iFrameAndCenterIds.Close();
    DeletePressedBmps();
    }

// -----------------------------------------------------------------------------
// CAknButtonExtension::NewL
// Symbian two-phased constructor.
// -----------------------------------------------------------------------------
//
CAknButtonExtension* CAknButtonExtension::NewL( CAknButton& aButton )
    {
    CAknButtonExtension* ext = new ( ELeave ) CAknButtonExtension( aButton );
    CleanupStack::PushL( ext );
    ext->ConstructL();
    CleanupStack::Pop( ext );
    return ext;
    }

// -----------------------------------------------------------------------------
// CAknButtonExtension::ConstructL
// Symbian 2nd stage constructor.
// -----------------------------------------------------------------------------
//
void CAknButtonExtension::ConstructL()
    {
    // Normal frame and center
    iFrameAndCenterIds.AppendL( KAknsIIDQsnFrButtonNormal );
    iFrameAndCenterIds.AppendL( KAknsIIDQsnFrButtonCenterNormal );
    // Latched frame and center
    iFrameAndCenterIds.AppendL( KAknsIIDQsnFrButtonPressed );
    iFrameAndCenterIds.AppendL( KAknsIIDQsnFrButtonCenterPressed );
    // Dimmed frame and center
    iFrameAndCenterIds.AppendL( KAknsIIDQsnFrButtonInactive );
    iFrameAndCenterIds.AppendL( KAknsIIDQsnFrButtonCenterInactive );
    // Pressed frame and center
    iFrameAndCenterIds.AppendL( KAknsIIDQsnFrButtonPressed );
    iFrameAndCenterIds.AppendL( KAknsIIDQsnFrButtonCenterPressed );
    // Latched dimmed frame and center
    iFrameAndCenterIds.AppendL( KAknsIIDQsnFrButtonInactive );
    iFrameAndCenterIds.AppendL( KAknsIIDQsnFrButtonCenterInactive );
    }

// -----------------------------------------------------------------------------
// CAknButtonExtension::StartLongPressTimerL
// Starts the long press timer. The timer is constructed when used for the
// first time.
// -----------------------------------------------------------------------------
//
void CAknButtonExtension::StartLongPressTimerL()
    {
    if ( !iLongPressTimer )
        {
        iLongPressTimer = CPeriodic::NewL( CActive::EPriorityStandard );
        }
    else if ( iLongPressTimer->IsActive() )
        {
        iLongPressTimer->Cancel();
        }

    if ( iLongPressInterval > 0 )
        {
        iLongPressTimer->Start( iLongPressInterval, iLongPressInterval,
            TCallBack( ReportLongPressL, this ) );
        }
    }

// -----------------------------------------------------------------------------
// CAknButtonExtension::ReportLongPressL
// -----------------------------------------------------------------------------
//
TInt CAknButtonExtension::ReportLongPressL( TAny* aThis )
    {
    static_cast<CAknButtonExtension*>( aThis )->DoReportLongPressL();
    return 0;
    }

// -----------------------------------------------------------------------------
// CAknButtonExtension::DoReportLongPressL
// -----------------------------------------------------------------------------
//
void CAknButtonExtension::DoReportLongPressL()
    {
    if ( iLongPressTimer && iLongPressTimer->IsActive() )
        {
        iLongPressTimer->Cancel();
        }

    if ( iButton.Observer() )
        {
        iButton.Observer()->HandleControlEventL( &iButton,
            static_cast<MCoeControlObserver::TCoeEvent>(
                 CAknButton::ELongPressEvent ) );

        iFlags.Set( ELongPressReported );
        }
    }


// -----------------------------------------------------------------------------
// CAknButtonExtension::DeletePressedBmps
// Deletes pressed down bitmaps
// -----------------------------------------------------------------------------
//
void CAknButtonExtension::DeletePressedBmps()
    {
    delete iPressedDownBmp;
    delete iPressedDownBmpMask;
    iPressedDownBmp = 0;
    iPressedDownBmpMask = 0;
    }


// -----------------------------------------------------------------------------
// CAknButtonExtension::FetchProviderPressedBmpsL
// Fetches bitmaps from provider (if one exists). Returns ETrue if bitmaps were
// found.
// -----------------------------------------------------------------------------
//
TBool CAknButtonExtension::FetchProviderPressedBmpsL()
    {
    TBool bmpsFetched = EFalse;
    if ( iResourceProvider )
        {
        MAknResourceItem* resourceItem = 0;

        // Check if resource provider has item for KPressedFrameId
        if ( iResourceProvider->GetResourceL( 
                KPressedFrameId, resourceItem ) != KErrNotFound 
            && resourceItem )
            {
            DeletePressedBmps();
            static_cast<CAknBitmapResourceItem*>( resourceItem )->GetBitmaps( 
                iPressedDownBmp, iPressedDownBmpMask );
            delete resourceItem;
            
            // Check if found bitmap size matches with button size
            if ( iPressedDownBmp 
                && iPressedDownBmpMask
                && iPressedDownBmp->SizeInPixels() == iButton.Size() )
                {
                bmpsFetched = ETrue;
                }
            // If not, delete the fetched bitmaps
            else
                {
                DeletePressedBmps();
                }
            }
        }
    return bmpsFetched;
    }


// -----------------------------------------------------------------------------
// CAknButtonExtension::SetProviderPressedBmpsL
// Sets bitmaps to provider (if one exists).
// -----------------------------------------------------------------------------
//
void CAknButtonExtension::SetProviderPressedBmpsL()
    {
    if ( iResourceProvider )
        {
        CAknBitmapResourceItem* resourceItem = 
            CAknBitmapResourceItem::NewL( KPressedFrameId );
        resourceItem->SetBitmapsL( iPressedDownBmp, iPressedDownBmpMask );
        iResourceProvider->SetResourceL( 
            KPressedFrameId, 
            static_cast<MAknResourceItem*>( resourceItem ) );
        }
    }
    
    

//
TBool CAknButtonExtension::HitRegionContains( const TPoint &aPoint, 
    const CCoeControl& /*aControl*/ ) const
    {
    TBool retval = EFalse;
    
    TRAP_IGNORE( retval = iButton.HitAreaContainsL( aPoint, iFlags.IsSet( ECheckHitArea ) ) );

    return retval;
    }

void CAknButtonExtension::HandleFeedbackAreaChange()
    {
    // it is possible that feedback does not exist, eg. while booting.
    // try getting one, and give up if that fails.
    if ( !iFeedback )
        {
        iFeedback = MTouchFeedback::Instance();
        }
    if ( !iFeedback )
        {
        return;
        }
            
    if ( iButton.ButtonFlags() & KAknButtonHitTest )
        {
        // no registry feedback if shaped buttons are used
        iFeedback->RemoveFeedbackArea( &iButton, 0 );
        }
    else
        {
        CFeedbackSpec* spec = CFeedbackSpec::New();
        if (spec)
            {
            spec->AddFeedback( ETouchEventStylusDown, 
                               ETouchFeedbackBasicButton );
            spec->AddFeedback( ETouchEventStylusUp, 
                               ETouchFeedbackBasicButton,
                               ETouchFeedbackVibra );
            iFeedback->SetFeedbackArea( &iButton, 0, iButton.Rect(), spec );
            delete spec;
            }
        }
    }

// ============================ EXTENSION CLASS ================================

NONSHARABLE_CLASS( CAknButtonStateExtension ) : public CBase
    {
    friend class CAknButtonState;

public:
    static CAknButtonStateExtension* NewL();
    ~CAknButtonStateExtension();
    
    void ConfigureExtensionFromResourceL( const TInt aResourceId );
    void ConfigureExtensionFromResourceL( TResourceReader& aReader );
    
private:
    CAknButtonStateExtension();
    void ConstructL();

private: // Data
    TBool iGeneratedDimmedIcon;
    HBufC* iFilePath;
    TInt iBmpId;
    TInt iMaskId;
    TInt iDimmedBmpId;
    TInt iDimmedMaskId;
    TInt iPressedBmpId;
    TInt iPressedMaskId;
    TInt iHoverBmpId;
    TInt iHoverMaskId;
    TAknsItemID iId;
    TAknsItemID iDimmedId;
    TAknsItemID iPressedId;
    TAknsItemID iHoverId;
    TScaleMode iScaleMode;
    };

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknButtonStateExtension::CAknButtonStateExtension
// C++ default constructor.
// -----------------------------------------------------------------------------
//
CAknButtonStateExtension::CAknButtonStateExtension()    
    : iGeneratedDimmedIcon ( EFalse ), iBmpId( -1 ), iMaskId( -1 ),
      iDimmedBmpId( -1 ), iDimmedMaskId( -1 ), iPressedBmpId( -1 ),
      iPressedMaskId( -1 ), iHoverBmpId( -1 ), iHoverMaskId( -1 ),
      iId( KAknsIIDNone ), iDimmedId( KAknsIIDNone ), 
      iPressedId( KAknsIIDNone ), iHoverId( KAknsIIDNone ), 
      iScaleMode( EAspectRatioNotPreserved )
    {
    }

// -----------------------------------------------------------------------------
// CAknButtonStateExtension::~CAknButtonStateExtension
// Destructor.
// -----------------------------------------------------------------------------
//
CAknButtonStateExtension::~CAknButtonStateExtension()
    {
    delete iFilePath;
    }

// -----------------------------------------------------------------------------
// CAknButtonStateExtension::NewL
// Symbian two-phased constructor.
// -----------------------------------------------------------------------------
//
CAknButtonStateExtension* CAknButtonStateExtension::NewL()
    {
    CAknButtonStateExtension* ext = new ( ELeave ) CAknButtonStateExtension;
    CleanupStack::PushL( ext );
    ext->ConstructL();
    CleanupStack::Pop( ext );
    return ext;
    }

// -----------------------------------------------------------------------------
// CAknButtonStateExtension::ConstructL
// Symbian 2nd stage constructor.
// -----------------------------------------------------------------------------
//
void CAknButtonStateExtension::ConstructL()
    {
    } //lint !e1762 function cannot be made const

// -----------------------------------------------------------------------------
// CAknButtonStateExtension::ConfigureExtensionFromResourceL
// -----------------------------------------------------------------------------
//    
void CAknButtonStateExtension::ConfigureExtensionFromResourceL( 
    const TInt aResourceId )    
    {
    
    if ( aResourceId )
        {
        TResourceReader reader;
        CCoeEnv::Static()->CreateResourceReaderLC( reader, aResourceId );
        ConfigureExtensionFromResourceL( reader );
        CleanupStack::PopAndDestroy();
        }    
    }

// -----------------------------------------------------------------------------
// CAknButtonStateExtension::ConfigureExtensionFromResourceL
// -----------------------------------------------------------------------------
//        
void CAknButtonStateExtension::ConfigureExtensionFromResourceL( 
    TResourceReader& aReader )
    {
    TInt version = aReader.ReadInt8();

    // bmp ids 
    TInt major = aReader.ReadInt32();
    TInt minor = aReader.ReadInt32();
    
    if ( major != 0 && minor != 0 )
        {
        iId.Set( major, minor );    
        }

    // dimmed ids
    major = aReader.ReadInt32();
    minor = aReader.ReadInt32();
    
    if ( major != 0 && minor != 0 )
        {
        iDimmedId.Set( major, minor );    
        }

    // pressed ids
    major = aReader.ReadInt32();
    minor = aReader.ReadInt32();
    
    if ( major != 0 && minor != 0 )
        {
        iPressedId.Set( major, minor );    
        }

    // hover ids
    major = aReader.ReadInt32();
    minor = aReader.ReadInt32();
    
    if ( major != 0 && minor != 0 )
        {
        iHoverId.Set( major, minor );    
        }
    }
    
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknButtonState::CAknButtonState
// Constructor
// -----------------------------------------------------------------------------
//
EXPORT_C CAknButtonState::CAknButtonState( const TInt aFlags ) :
                                           iFlags( aFlags )
    {
    }

// -----------------------------------------------------------------------------
// CAknButtonState::~CAknButtonState
// Destructor
// -----------------------------------------------------------------------------
//
EXPORT_C CAknButtonState::~CAknButtonState()
    {
    delete iIcon;
    delete iDimmedIcon;
    delete iPressedIcon;
    delete iHoverIcon;
    delete iText;
    delete iHelpText;
    delete iExtension;
    }

// -----------------------------------------------------------------------------
// CAknButtonState::ConstructFromResourceL
// Constructs the button state from the resources
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButtonState::ConstructFromResourceL( TResourceReader& aReader )
    {
    if ( !iExtension )
        {
        iExtension = CAknButtonStateExtension::NewL();
        }

    // flags
    iFlags = aReader.ReadInt16();

    // txt
    TPtrC txt = aReader.ReadTPtrC();
    SetTextL( txt );

    // helptxt
    TPtrC helpTxt = aReader.ReadTPtrC();
    SetHelpTextL( helpTxt );

    if ( iExtension->iFilePath )
        {
        delete iExtension->iFilePath;
        iExtension->iFilePath = NULL;
        }

    // bmpfile
    iExtension->iFilePath = aReader.ReadTPtrC().AllocL();

    // bmpid & bmpmask
    iExtension->iBmpId = aReader.ReadInt16();
    iExtension->iMaskId = aReader.ReadInt16();

    // dim_bmpid & dim_bmpmask
    iExtension->iDimmedBmpId = aReader.ReadInt16();
    iExtension->iDimmedMaskId = aReader.ReadInt16();

    // press_bmpid & press_bmpmask
    iExtension->iPressedBmpId = aReader.ReadInt16();
    iExtension->iPressedMaskId = aReader.ReadInt16();

    // hover_bmpid & hover_bmpmask
    iExtension->iHoverBmpId = aReader.ReadInt16();
    iExtension->iHoverMaskId = aReader.ReadInt16();

    // extension
    TInt extensionLink = aReader.ReadInt32();
    
    if ( extensionLink != 0 )
        {
        iExtension->ConfigureExtensionFromResourceL( extensionLink );
        }
        
    LoadButtonIcon( iIcon );
    LoadButtonIcon( iDimmedIcon );
    LoadButtonIcon( iPressedIcon );
    LoadButtonIcon( iHoverIcon );
    }

// -----------------------------------------------------------------------------
// CAknButtonState::ConstructL
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButtonState::ConstructL( CGulIcon* aIcon,
                                           CGulIcon* aDimmedIcon,
                                           CGulIcon* aPressedIcon,
                                           CGulIcon* aHoverIcon,
                                           const TDesC& aText,
                                           const TDesC& aHelpText )
    {
    if ( !iExtension )
        {
        iExtension = CAknButtonStateExtension::NewL();
        }

    SetIcon( aIcon );
    SetDimmedIcon( aDimmedIcon );
    SetPressedIcon( aPressedIcon );
    SetHoverIcon( aHoverIcon );
    SetTextL( aText );
    SetHelpTextL( aHelpText );
    }

// -----------------------------------------------------------------------------
// CAknButtonState::
// Symbian 2nd phase constructor.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButtonState::ConstructL( const TDesC& aFilePath,
                                           const TInt aBmpId,
                                           const TInt aMaskId,
                                           const TInt aDimmedBmpId,
                                           const TInt aDimmedMaskId,
                                           const TInt aPressedBmpId,
                                           const TInt aPressedMaskId,
                                           const TInt aHoverBmpId,
                                           const TInt aHoverMaskId,
                                           const TDesC& aText,
                                           const TDesC& aHelpText,
                                           const TAknsItemID& aId,
                                           const TAknsItemID& aDimmedId,
                                           const TAknsItemID& aPressedId,
                                           const TAknsItemID& aHoverId )
    {
    UpdateIconL( aFilePath, aBmpId, aMaskId, aDimmedBmpId, aDimmedMaskId, 
        aPressedBmpId, aPressedMaskId, aHoverBmpId, aHoverMaskId, aId, aDimmedId, 
        aPressedId, aHoverId ); 

    SetTextL( aText );
    SetHelpTextL( aHelpText );
    }

// -----------------------------------------------------------------------------
// CAknButtonState::Icon
// Returns the icon for the normal state.
// -----------------------------------------------------------------------------
//
EXPORT_C const CGulIcon* CAknButtonState::Icon() const
    {
    return iIcon;
    }

// -----------------------------------------------------------------------------
// CAknButtonState::DimmedIcon
// Returns the icon for the dimmed state
// -----------------------------------------------------------------------------
//
EXPORT_C const CGulIcon* CAknButtonState::DimmedIcon() const
    {
    return iDimmedIcon;
    }

// -----------------------------------------------------------------------------
// CAknButtonState::PressedIcon
// Returns the icon for the pressed but not released state.
// -----------------------------------------------------------------------------
//
EXPORT_C const CGulIcon* CAknButtonState::PressedIcon() const
    {
    return iPressedIcon;
    }

// -----------------------------------------------------------------------------
// CAknButtonState::HoverIcon
// Returns the icon for the hover state.
// -----------------------------------------------------------------------------
//
EXPORT_C const CGulIcon* CAknButtonState::HoverIcon() const
    {
    return iHoverIcon;
    }

// -----------------------------------------------------------------------------
// CAknButtonState::Text
// Returns the text inside the button.
// -----------------------------------------------------------------------------
//
EXPORT_C const TDesC& CAknButtonState::Text() const
    {
    if ( iText )
        {
        return *iText;
        }
    else
        {
        return KNullDesC();
        }
    }

// -----------------------------------------------------------------------------
// CAknButtonState::HelpText
// Returns the text inside the help note.
// -----------------------------------------------------------------------------
//
EXPORT_C const TDesC& CAknButtonState::HelpText() const
    {
    if ( iHelpText )
        {
        return *iHelpText;
        }
    else
        {
        return KNullDesC();
        }
    }

// -----------------------------------------------------------------------------
// CAknButtonState::Flags
// Returns the state flags.
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CAknButtonState::Flags() const
    {
    return iFlags;
    }

// -----------------------------------------------------------------------------
// CAknButtonState::SetIcon
// Sets the icon for the normal state.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButtonState::SetIcon( CGulIcon* aIcon )
    {
    ReplaceIcon( iIcon, aIcon );
    
    if ( iExtension->iGeneratedDimmedIcon )
        {
        TRAP_IGNORE( CreateAndSetDimmedIconL( iDimmedIcon, iIcon, 
            iExtension->iScaleMode ) );   
        }
    }

// -----------------------------------------------------------------------------
// CAknButtonState::SetDimmedIcon
// Sets the icon for the dimmed state.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButtonState::SetDimmedIcon( CGulIcon* aDimmedIcon )
    {
    ReplaceIcon( iDimmedIcon, aDimmedIcon );
    }

// -----------------------------------------------------------------------------
// CAknButtonState::SetPressedIcon
// Sets the icon for the pressed but not released state.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButtonState::SetPressedIcon( CGulIcon* aPressedIcon )
    {
    ReplaceIcon( iPressedIcon, aPressedIcon );
    }

// -----------------------------------------------------------------------------
// CAknButtonState::SetHoverIcon
// Sets the icon for the hover state.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButtonState::SetHoverIcon( CGulIcon* aHoverIcon )
    {
    ReplaceIcon( iHoverIcon, aHoverIcon );
    }

// -----------------------------------------------------------------------------
// CAknButtonState::ReplaceIcon
// Replaces the given icon with a new one. If the original icon had its size set
// then the new icon is scaled to that size.
// -----------------------------------------------------------------------------
//
void CAknButtonState::ReplaceIcon( CGulIcon*& aIcon, CGulIcon* aNewIcon )
    {
        ReplaceIconStatic( aIcon, aNewIcon, iExtension->iScaleMode );
    }

    
// -----------------------------------------------------------------------------
// CAknButtonState::SetTextL
// Sets the text inside the button
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButtonState::SetTextL( const TDesC& aText )
    {
    delete iText;
    iText = NULL;

    iText = aText.AllocL();
    }

// -----------------------------------------------------------------------------
// CAknButtonState::SetHelpTextL
// Sets the text inside the help note
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButtonState::SetHelpTextL( const TDesC& aHelpText )
    {
    delete iHelpText;
    iHelpText = NULL;

    iHelpText = aHelpText.AllocL();
    }

// -----------------------------------------------------------------------------
// CAknButtonState::
// Sets state flags.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButtonState::SetFlags( const TInt aFlags )
    {
    iFlags = aFlags;
    }

// -----------------------------------------------------------------------------
// CAknButtonState::UpdateIconL
// Updates button icons. 
// -----------------------------------------------------------------------------
void CAknButtonState::UpdateIconL( const TDesC& aFilePath, 
                                   const TInt aBmpId, 
                                   const TInt aMaskId,
                                   const TInt aDimmedBmpId,
                                   const TInt aDimmedMaskId,
                                   const TInt aPressedBmpId,
                                   const TInt aPressedMaskId,
                                   const TInt aHoverBmpId,
                                   const TInt aHoverMaskId,
                                   const TAknsItemID& aId,
                                   const TAknsItemID& aDimmedId,
                                   const TAknsItemID& aPressedId,
                                   const TAknsItemID& aHoverId )

    {
    if ( !iExtension )
        {
        iExtension = CAknButtonStateExtension::NewL();
        }

    if ( iExtension->iFilePath )
        {        
        delete iExtension->iFilePath;
        iExtension->iFilePath = NULL;
        }

    // try to save some ram by defaulting to avkon bitmap file
    if ( aFilePath != KAvkonBitmapFile )
        {
        iExtension->iFilePath = aFilePath.AllocL();    
        }
    
    iExtension->iBmpId = aBmpId;
    iExtension->iMaskId = aMaskId;
    iExtension->iDimmedBmpId = aDimmedBmpId;
    iExtension->iDimmedMaskId = aDimmedMaskId;
    iExtension->iPressedBmpId = aPressedBmpId;
    iExtension->iPressedMaskId = aPressedMaskId;
    iExtension->iHoverBmpId = aHoverBmpId;
    iExtension->iHoverMaskId = aHoverMaskId;
    iExtension->iId = aId;
    iExtension->iDimmedId = aDimmedId;
    iExtension->iPressedId = aPressedId;
    iExtension->iHoverId = aHoverId;

    LoadButtonIcon( iIcon );
    LoadButtonIcon( iDimmedIcon );
    LoadButtonIcon( iPressedIcon );
    LoadButtonIcon( iHoverIcon );
    }

// -----------------------------------------------------------------------------
// CAknButtonState::SizeChanged
// Scales function graphics to the given size
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButtonState::SizeChanged( const TRect& aRect,
                                            TScaleMode aScaleMode )
    {
    ScaleIcons( aRect.Size(), aScaleMode );
    }

// -----------------------------------------------------------------------------
// CAknButtonState::HasText
// Returns ETrue if the text inside button is not empty or space.
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CAknButtonState::HasText() const
    {
    if ( !iText )
        return EFalse;

    TBool ret = EFalse;
    for ( TInt i = 0; i < iText->Des().Length(); i++ )
        {
        TChar c ( (iText->Des())[i]);

//        TChar::TCategory cat = c.GetCategory();
        if ( !c.IsSpace() /*&& cat != TChar::ECoCategory*/ )
            {
            // not space and not private use char
            ret = ETrue;
            break;
            }
        }

    return ret;
    }

// -----------------------------------------------------------------------------
// CAknButtonState::HasHelp
// Returns ETrue if the text inside the help note is not empty or space.
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CAknButtonState::HasHelp() const
    {
    if ( !iHelpText )
        return EFalse;

    TBool ret = EFalse;
    for ( TInt i = 0; i < iHelpText->Des().Length(); i++ )
        {
        TChar c( ( *iHelpText )[i] );

//        TChar::TCategory cat = c.GetCategory();
        if ( !c.IsSpace() /*&& cat != TChar::ECoCategory*/ )
            {
            // not space and not private use char
            ret = ETrue;
            break;
            }
        }

    return ret;
    }

// -----------------------------------------------------------------------------
// CAknButtonState::HandleResourceChange
// Handles changes in state's environment.
// -----------------------------------------------------------------------------
//
void CAknButtonState::HandleResourceChange( TInt aType )
    {
    // Update icons if skin is changed. KEikDynamicLayoutVariantSwitch event is
    // handled via SizeChanged.
    if ( aType == KAknsMessageSkinChange )
        {
        LoadButtonIcon( iIcon );
        LoadButtonIcon( iDimmedIcon );
        LoadButtonIcon( iPressedIcon );
        LoadButtonIcon( iHoverIcon );

        // generated dimmed state icon has to be regenerated
        if ( iExtension->iGeneratedDimmedIcon )
            {
            TRAP_IGNORE( CreateAndSetDimmedIconL( iDimmedIcon, iIcon, 
                iExtension->iScaleMode ) );
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknButtonState::SetIconScaleMode
// Sets default scaling mode.
// -----------------------------------------------------------------------------
//
void CAknButtonState::SetIconScaleMode( const TScaleMode aScaleMode )
    {
    iExtension->iScaleMode = aScaleMode;
    }
    
// -----------------------------------------------------------------------------
// CAknButtonState::CreateButtonIconL
// Creates one of the icons
// -----------------------------------------------------------------------------
//
void CAknButtonState::CreateButtonIconL( CGulIcon*& aIcon,
                                         const TDesC& aFilePath,
                                         TInt aBmpId,
                                         TInt aMaskId,
                                         const TAknsItemID& aId ) const
    {
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    if ( aIcon )
        {
        if ( ( aId != KAknsIIDNone && skin ) || aBmpId != -1 )
            {
            delete aIcon;
            aIcon = NULL;
            }
        }

    if ( aFilePath == KNullDesC || aBmpId == -1 )
        {
        if ( aId != KAknsIIDNone && skin )
            {
            aIcon = AknsUtils::CreateGulIconL( skin, aId, EFalse );
            }
        }
    else
        {
        if ( aId != KAknsIIDNone && skin )
            {
            aIcon = AknsUtils::CreateGulIconL( skin, aId, aFilePath, aBmpId,
                                               aMaskId);
            }
        else
            {
            CFbsBitmap* bmp;
            CFbsBitmap* mask;
            AknIconUtils::CreateIconLC( bmp, mask, aFilePath, aBmpId, aMaskId);
            aIcon = CGulIcon::NewL( bmp, mask ); // ownership passed
            CleanupStack::Pop( 2 );
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknButtonState::LoadButtonIcon
// Reloads one button icon.
// -----------------------------------------------------------------------------
//
void CAknButtonState::LoadButtonIcon( CGulIcon*& aIcon ) const
    {
    TSize iconSize( 0, 0 );
    
    if ( aIcon && aIcon->Bitmap() )
        {
        iconSize = aIcon->Bitmap()->SizeInPixels();
        }

    TInt bmpId = -1;
    TInt maskId = -1;
    TAknsItemID skinId = KAknsIIDNone;

    if ( &aIcon == &iIcon )
        {
        bmpId = iExtension->iBmpId;
        maskId = iExtension->iMaskId;
        skinId = iExtension->iId;
        }
    else if ( &aIcon == &iPressedIcon )
        {
        bmpId = iExtension->iPressedBmpId;
        maskId = iExtension->iPressedMaskId;
        skinId = iExtension->iPressedId;
        }
    else if ( &aIcon == &iDimmedIcon )
        {
        bmpId = iExtension->iDimmedBmpId;
        maskId = iExtension->iDimmedMaskId;
        skinId = iExtension->iDimmedId;
        }
    else if ( &aIcon == &iHoverIcon )
        {
        bmpId = iExtension->iHoverBmpId;
        maskId = iExtension->iHoverMaskId;
        skinId = iExtension->iHoverId;
        }

    TPtrC16 bitmapFile;
    
    if ( iExtension->iFilePath )
        {
        bitmapFile.Set( *iExtension->iFilePath );
        }
    else
        {
        bitmapFile.Set( KAvkonBitmapFile );
        }

    // aIcon is set to NULL if the next call fails
    TRAP_IGNORE( CreateButtonIconL( aIcon, bitmapFile, bmpId, maskId, skinId ) );
            
    if ( aIcon && iconSize != TSize( 0, 0 ) )
        {
        ResizeIcon( aIcon, iconSize, iExtension->iScaleMode );
        }
    }                                          

// -----------------------------------------------------------------------------
// CAknButtonState::ScaleIcons
// Sets the size for bitmap and mask
// -----------------------------------------------------------------------------
//
TInt CAknButtonState::ScaleIcons( const TSize& aSize, TScaleMode aScaleMode )
    {
    TInt retval = ResizeIcon( iIcon, aSize, aScaleMode );
    retval = Min( retval, ResizeIcon( iPressedIcon, aSize, aScaleMode ) );
    
    // Generated dimmed state icon has to be regenerated
    if ( iExtension->iGeneratedDimmedIcon )
        {
        TRAP_IGNORE ( CreateAndSetDimmedIconL( iDimmedIcon, iIcon, aScaleMode ) );
        }
    else
        {
        retval = Min( retval, ResizeIcon( iDimmedIcon, aSize, aScaleMode ) );
        }
        
    return retval;        
    }

// -----------------------------------------------------------------------------
// CAknButtonState::ScaleMode
// Getter for the current scalemode of the state
// -----------------------------------------------------------------------------
TScaleMode CAknButtonState::ScaleMode() const
    {
    return iExtension->iScaleMode;
    }

// -----------------------------------------------------------------------------
// CAknButtonState::SetGeneratedDimmedIcon
// Whether the dimmed icon of the state is created by owning Button
// -----------------------------------------------------------------------------    
void CAknButtonState::SetGeneratedDimmedIcon( TBool aDimmedIconCreatedByButton )
    {
    iExtension->iGeneratedDimmedIcon = aDimmedIconCreatedByButton;
    }

// -----------------------------------------------------------------------------
// CAknButtonState::Extension
// -----------------------------------------------------------------------------
//
CAknButtonStateExtension* CAknButtonState::Extension() const
    {
    return iExtension;
    }

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknButton::NewL
// Two-phased constructor.
// Constructs an empty button
// -----------------------------------------------------------------------------
//
EXPORT_C CAknButton* CAknButton::NewL()
    {
    CAknButton* self = NewLC();
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CAknButton::NewLC
// Two-phased constructor.
// Constructs an empty button
// -----------------------------------------------------------------------------
//
EXPORT_C CAknButton* CAknButton::NewLC()
    {
    CAknButton* self = new (ELeave) CAknButton( 0 );
    CleanupStack::PushL( self );
    self->ConstructL();
    AKNTASHOOK_ADDL( self, "CAknButton" );
    return self;
    }

// -----------------------------------------------------------------------------
// CAknButton::NewL
// Two-phased constructor.
// Constructs the button from resources.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknButton* CAknButton::NewL( TResourceReader& aReader )
    {
    CAknButton* self = NewLC( aReader );
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CAknButton::NewLC
// Two-phased constructor.
// Constructs the button from resources.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknButton* CAknButton::NewLC( TResourceReader& aReader )
    {
    CAknButton* self = new( ELeave ) CAknButton( 0 );
    CleanupStack::PushL( self );
    self->ConstructL();
    self->ConstructFromResourceL( aReader );
    AKNTASHOOK_ADDL( self, "CAknButton" );
    return self;
    }

// -----------------------------------------------------------------------------
// CAknButton::NewL
// Two-phased constructor.
// Constructs the button from resources.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknButton* CAknButton::NewL( const TInt aResourceId )
    {
    CAknButton* self = NewLC( aResourceId );
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CAknButton::NewLC
// Two-phased constructor.
// Constructs the button from resources.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknButton* CAknButton::NewLC( const TInt aResourceId )
    {
    CAknButton* self = new (ELeave) CAknButton( 0 );
    CleanupStack::PushL( self );
    self->ConstructL();
    self->ConstructFromResourceL( aResourceId );
    AKNTASHOOK_ADDL( self, "CAknButton" );
    return self;
    }

// -----------------------------------------------------------------------------
// CAknButton::NewL
// Two-phased constructor.
// Constructs one state button.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknButton* CAknButton::NewL( CGulIcon* aIcon,
                                       CGulIcon* aDimmedIcon,
                                       CGulIcon* aPressedIcon,
                                       CGulIcon* aHoverIcon,
                                       const TDesC& aText,
                                       const TDesC& aHelpText,
                                       const TInt aButtonFlags,
                                       const TInt aStateFlags )
    {
    CAknButton* self = NewLC( aIcon, aDimmedIcon, aPressedIcon, aHoverIcon,
        aText, aHelpText, aButtonFlags, aStateFlags );
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CAknButton::NewLC
// Two-phased constructor.
// Constructs one state button.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknButton* CAknButton::NewLC( CGulIcon* aIcon,
                                        CGulIcon* aDimmedIcon,
                                        CGulIcon* aPressedIcon,
                                        CGulIcon* aHoverIcon,
                                        const TDesC& aText,
                                        const TDesC& aHelpText,
                                        const TInt aButtonFlags,
                                        const TInt aStateFlags )
    {
    CAknButton* self = new (ELeave) CAknButton( aButtonFlags );
    CleanupStack::PushL( self );
    self->ConstructL( aIcon, aDimmedIcon, aPressedIcon, aHoverIcon, aText,
                      aHelpText, aStateFlags );
    AKNTASHOOK_ADDL( self, "CAknButton" );
    return self;
    }

// -----------------------------------------------------------------------------
// CAknButton::NewL
// Two-phased constructor.
// Constructs one state button.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknButton* CAknButton::NewL( const TDesC& aFilePath,
                                       const TInt aBmpId,
                                       const TInt aMaskId,
                                       const TInt aDimmedBmpId,
                                       const TInt aDimmedMaskId,
                                       const TInt aPressedBmpId,
                                       const TInt aPressedMaskId,
                                       const TInt aHoverBmpId,
                                       const TInt aHoverMaskId,
                                       const TDesC& aText,
                                       const TDesC& aHelpText,
                                       const TInt aButtonFlags,
                                       const TInt aStateFlags,
                                       const TAknsItemID& aId,
                                       const TAknsItemID& aDimmedId,
                                       const TAknsItemID& aPressedId,
                                       const TAknsItemID& aHoverId )
    {
    CAknButton* self = NewLC( aFilePath, aBmpId, aMaskId, aDimmedBmpId,
        aDimmedMaskId, aPressedBmpId, aPressedMaskId, aHoverBmpId, aHoverMaskId,
        aText, aHelpText, aButtonFlags, aStateFlags, aId, aDimmedId, aPressedId,
        aHoverId );
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CAknButton::NewLC
// Two-phased constructor.
// Constructs one state button.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknButton* CAknButton::NewLC( const TDesC& aFilePath,
                                        const TInt aBmpId,
                                        const TInt aMaskId,
                                        const TInt aDimmedBmpId,
                                        const TInt aDimmedMaskId,
                                        const TInt aPressedBmpId,
                                        const TInt aPressedMaskId,
                                        const TInt aHoverBmpId,
                                        const TInt aHoverMaskId,
                                        const TDesC& aText,
                                        const TDesC& aHelpText,
                                        const TInt aButtonFlags,
                                        const TInt aStateFlags,
                                        const TAknsItemID& aId,
                                        const TAknsItemID& aDimmedId,
                                        const TAknsItemID& aPressedId,
                                        const TAknsItemID& aHoverId )
    {
    CAknButton* self = new (ELeave) CAknButton( aButtonFlags );
    CleanupStack::PushL( self );
    self->ConstructL( aFilePath, aBmpId, aMaskId, aDimmedBmpId, aDimmedMaskId,
        aPressedBmpId, aPressedMaskId, aHoverBmpId, aHoverMaskId,
        aText, aHelpText, aStateFlags, aId, aDimmedId, aPressedId, aHoverId );
    AKNTASHOOK_ADDL( self, "CAknButton" );
    return self;
    }

// -----------------------------------------------------------------------------
// CAknButton::CAknButton
// C++ constructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknButton::CAknButton( const TInt aFlags )
    : iFlags( aFlags ),
      iVerticalAlignment( ECenter ),
      iHorizontalAlignment( CGraphicsContext::ECenter ),
      iTextColorTableId( KAknsIIDQsnTextColors ), // TODO
      iTextColorIndex( EAknsCIQsnTextColorsCG80 ), // TODO
      iScaleMode( EAspectRatioNotPreserved ),
      iHelpNoteWaitInterval( KTimeoutBeforeHelpNote ),
      iHelpNoteInViewInterval( KTimeoutInViewHelpNote ),
      iKeyRepeatDelay( KKeyRepeatDelay ),
      iKeyRepeatInterval( KKeyRepeatInterval )
    {
    }

// -----------------------------------------------------------------------------
// CAknButton::ConstructL
// Symbian 2nd phase constructor.
// Constructor for the empty button.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::ConstructL()
    {
    TRgb textColor;
    
    if ( AknsUtils::GetCachedColor( AknsUtils::SkinInstance(), textColor, 
        iTextColorTableId, iTextColorIndex ) == KErrNone )
        {
        OverrideColorL( EColorButtonText, textColor );
        }

    if ( !iStates )
        {
        iStates = new ( ELeave ) CArrayPtrFlat<CAknButtonState>( 2 );
        }

    if ( !iBgContext )
        {
        iBgContext = CAknsFrameBackgroundControlContext::NewL(
            KAknsIIDNone, TRect(), TRect(), EFalse );
        }
  
    if ( !iExtension )
        {
        iExtension = CAknButtonExtension::NewL( *this );
        }

    if ( iFlags & KAknButtonHitTest )
        {
        SetHitTest( iExtension );
        }        

    if ( iFlags & KAknButtonNoFrame )
        {
        iExtension->iMargins.SetAllValuesTo( 0 );
        }
    
    if ( iFlags & KAknButtonTextLeft )
        {
        iHorizontalAlignment = CGraphicsContext::ELeft;
        }
    iExtension->HandleFeedbackAreaChange();
    }

// -----------------------------------------------------------------------------
// CAknButton::ConstructL
// Symbian 2nd phase constructor for 1 state button.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::ConstructL( CGulIcon* aIcon,
                                      CGulIcon* aDimmedIcon,
                                      CGulIcon* aPressedIcon,
                                      CGulIcon* aHoverIcon,
                                      const TDesC& aText,
                                      const TDesC& aHelpText,
                                      const TInt aStateFlags )
    {
    ConstructL();
    AddStateL( aIcon, aDimmedIcon, aPressedIcon, aHoverIcon, aText, aHelpText,
               aStateFlags);
    }

// -----------------------------------------------------------------------------
// CAknButton::ConstructL
// Symbian 2nd phase constructor for 1 state button
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::ConstructL( const TDesC& aFilePath,
                                      const TInt aBmpId,
                                      const TInt aMaskId,
                                      const TInt aDimmedBmpId,
                                      const TInt aDimmedMaskId,
                                      const TInt aPressedBmpId,
                                      const TInt aPressedMaskId,
                                      const TInt aHoverBmpId,
                                      const TInt aHoverMaskId,
                                      const TDesC& aText,
                                      const TDesC& aHelpText,
                                      const TInt aStateFlags,
                                      const TAknsItemID& aId,
                                      const TAknsItemID& aDimmedId,
                                      const TAknsItemID& aPressedId,
                                      const TAknsItemID& aHoverId )
    {
    ConstructL();
    AddStateL( aFilePath, aBmpId, aMaskId, aDimmedBmpId, aDimmedMaskId,
        aPressedBmpId, aPressedMaskId, aHoverBmpId, aHoverMaskId,
        aText, aHelpText, aStateFlags, aId, aDimmedId, aPressedId, aHoverId );
    }

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------
//
EXPORT_C CAknButton::~CAknButton()
    {
    AKNTASHOOK_REMOVE();
    if ( iStates )
        {
        iStates->ResetAndDestroy();
        delete iStates;
        }

    // MTouchFeedback instance lives in AknAppUi. AppUi might be
    // destroyed when this destructor is running. If there is no
    // MTouchFeedback instance there is no need to remove any areas
    // either, as these are ( naturally ) destroyed with
    // MTouchFeedback instance.
    MTouchFeedback* fb = MTouchFeedback::Instance();
    if ( fb )
        {
        fb->RemoveFeedbackForControl( this );
        }

    delete iBgContext;
    delete iDimmedHelpText;
    delete iHelpNote;
    delete iKeyRepeatTimer;
    delete iExtension;
    iFont = NULL;
    }

// -----------------------------------------------------------------------------
// CAknButton::ActivateL
// Sets control as ready to be drawn.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::ActivateL()
    {
    // request for drag events outside the button
    SetAllowStrayPointers();
    // Requesting pointer drag events
    EnableDragEvents();
    
    CAknControl::ActivateL();
    }

// -----------------------------------------------------------------------------
// CAknButton::ConstructFromResourceL
// Constructs controls from a resource file.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::ConstructFromResourceL( TResourceReader& aReader )
    {
    if ( !iExtension )
        {
        iExtension = CAknButtonExtension::NewL( *this );
        }

    // flags
    iFlags = aReader.ReadInt16();

    // state index
    SetStateIndexL( aReader.ReadInt16() );

    // read states
    const TInt stateCount = aReader.ReadInt16();
    for ( TInt ii = 0; ii < stateCount; ii++ )
        {
        CAknButtonState* state = new (ELeave) CAknButtonState( 0 );
        CleanupStack::PushL( state );
        state->ConstructFromResourceL( aReader );
        iStates->AppendL( state );
        CleanupStack::Pop( state );
        }

    aReader.ReadInt32(); // extension link, not used currently

    if ( iFlags & KAknButtonHitTest )
        {
        SetHitTest( iExtension );
        }        

    if ( iFlags & KAknButtonNoFrame )
        {
        iExtension->iMargins.SetAllValuesTo( 0 );
        }

    if ( iFlags & KAknButtonTextLeft )
        {
        iHorizontalAlignment = CGraphicsContext::ELeft;
        }
    iExtension->HandleFeedbackAreaChange();
    }

// -----------------------------------------------------------------------------
// CAknButton::HandleResourceChange
// Handles a change to the control's resources.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::HandleResourceChange( TInt aType )
    {
    // No need to call base class implementation since CountComponentControls
    // is always zero.
        
    if ( aType == KAknsMessageSkinChange || aType == KEikDynamicLayoutVariantSwitch )
        {
        if ( iButtonPressed )
            {
            ResetState();
            DrawDeferred();
            }
        }
        
    // UIFW informs control about lost focus when moved to background.
    // Rest of pointer events are no longer forvarded to control.    
    if ( aType == KAknMessageFocusLost || aType == KEikMessageFadeAllWindows )
        {
        if (iHelpNote)
            {
            iHelpNote->HideInfoPopupNote();
            }
        
        if (iButtonPressed)
            {
            ResetState();
            DrawDeferred();
            }
        return;
        }
    
    if ( iStates )
        {
        for ( TInt i = 0; i < iStates->Count(); ++i )
            {
            CAknButtonState* state = iStates->At( i );
            
            if ( state )
                {
                state->HandleResourceChange( aType );
                }
            }
        }

    if ( aType == KAknsMessageSkinChange )
        {
        TRgb textColor;
        
        if ( AknsUtils::GetCachedColor( AknsUtils::SkinInstance(), textColor, 
                iTextColorTableId, iTextColorIndex ) == KErrNone )
            {
            TRAP_IGNORE( OverrideColorL( EColorButtonText, textColor ) );
            }
    
        // generated pressed frame has to be regenerated
        if ( iFlags & KAknButtonNoFrame && iFlags & KAknButtonPressedDownFrame )
            {
            iExtension->DeletePressedBmps();
            TRAP_IGNORE( CreatePressedDownFrameL() );
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknButton::MinimumSize
// Returns the control's minimum required size. This doesn't include highlight
// area.
// -----------------------------------------------------------------------------
//
EXPORT_C TSize CAknButton::MinimumSize()
    {
    // by default, margins decide the absolute minimum size...
    TInt width = iExtension->iMargins.iLeft + iExtension->iMargins.iRight;
    TInt height = iExtension->iMargins.iTop + iExtension->iMargins.iBottom;
    
    // ...but possible frames may enlarge the required area...
    if ( !( iFlags & KAknButtonNoFrame ) )
        {
        TAknLayoutRect tl;
        tl.LayoutRect( Rect(), 
            AknLayoutScalable_Avkon::toolbar_button_pane_g2().LayoutLine() );

        TAknLayoutRect br;
        br.LayoutRect( Rect(),
            AknLayoutScalable_Avkon::toolbar_button_pane_g5().LayoutLine() );

        TInt frameWidth = tl.Rect().Width() + br.Rect().Width();
        TInt frameHeight = tl.Rect().Height() + br.Rect().Height();
        
        if ( !( iFlags & KAknButtonTextInsideFrame ) )
            {
            width = Max( width, frameWidth );
            height = Max( height, frameHeight );
            }
        else
            {
            width = frameWidth;
            height = frameHeight;
            }
        }
    
    // ...as well as evil flags
    if ( iStates && ( iFlags & KAknButtonSizeFitText ) )
        {
        if ( !iFont )
            {
            iFont = iCoeEnv->NormalFont();
            }

        height += iFont->FontMaxHeight();

        TInt textWidth = 0;
        
        // choose the longest one
        for ( TInt ii = 0; ii < iStates->Count(); ii++ )
            {
            CAknButtonState* state = iStates->At( ii );
            if ( state && state->HasText() )
                {
                TInt tempWidth = iFont->TextWidthInPixels( state->Text() );
                textWidth = Max( textWidth, tempWidth );
                }
            }
            
        width += textWidth;
        }
    
    return TSize( width, height );
    }

// -----------------------------------------------------------------------------
// CAknButton::SetDimmed
// Sets button dimmed. Doesn't redraw.
// Button needs to get pointer events even if it is dimmed to be able to show
// help text in dimmed state. So, the CCoeControl::SetDimmed(TBool) cannot be
// used to set button dimmed if the help text is used.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::SetDimmed( TBool aDimmed )
    {
    if ( aDimmed )
        {
        StopKeyRepeatTimer();
        StopLongPressTimer();
        HideHelp();
        iButtonPressed = EFalse;
        }
    
    if ( aDimmed )
        {
        iExtension->iFlags.Set( CAknButtonExtension::EDimmed );
        }
    else
        {
        iExtension->iFlags.Clear( CAknButtonExtension::EDimmed );
        }
    if ( iExtension->iFeedback )
        {
        if ( aDimmed )
            {
            iExtension->iFeedback->MoveFeedbackAreaToFirstPriority( this, 0 );
            }        
        iExtension->iFeedback->EnableFeedbackForControl( this, !aDimmed && IsVisible() );
        }

    TBool hasHelp ( EFalse );
    
    for ( TInt i = 0; i < iStates->Count(); ++i )
        {
        CAknButtonState* state = iStates->At( i );
        
        if ( state )
            {
            if ( !state->iDimmedIcon )
                {
                TRAP_IGNORE ( CreateAndSetDimmedIconL( state->iDimmedIcon, 
                    state->iIcon, state->ScaleMode() ) );
                state->SetGeneratedDimmedIcon( ETrue );
                }
            
            if ( state->HasHelp() )
                {
                hasHelp = ETrue;
                }
            }
        }
    // None of states has help text, CCoeControl::SetDimmed can be used        
    if ( !hasHelp )
        {
        CCoeControl::SetDimmed( aDimmed );
        }
    }

// -----------------------------------------------------------------------------
// CAknButton::OfferKeyEventL
// Handles key events.
// -----------------------------------------------------------------------------
//
EXPORT_C TKeyResponse CAknButton::OfferKeyEventL( const TKeyEvent& aKeyEvent,
                                                  TEventCode aType )
    {
    if ( IsDimmed() )
        return EKeyWasNotConsumed;

    if ( aType == EEventKeyDown && IsVisible() )
        {
        HideHelp(); // hides help text as soon as the first key event comes.
        }

    if ( aKeyEvent.iScanCode == EStdKeyDevice3 ||
         aKeyEvent.iScanCode == EStdKeyEnter )
        {
        if ( aType == EEventKeyDown )
            {
            iKeyDownReported = ETrue;

            if ( !iButtonPressed )
                {
                // show press changes
                iButtonPressed = ETrue;
                if ( NeedsRedrawWhenPressed() )
                    {
                    DrawNow();
                    }
                }

            if ( iFlags & KAknButtonReportOnKeyDown )
                {
                ChangeState( ETrue );
                if ( Observer() )
                    {
                    Observer()->HandleControlEventL( this,
                        MCoeControlObserver::EEventStateChanged );
                    }
                }

            if ( iFlags & KAknButtonKeyRepeat )
                {
                iExtension->iFlags.Clear( CAknButtonExtension::EKeyRepeatEventReported );
                StartKeyRepeatTimerL();
                }

            if ( iFlags & KAknButtonReportOnLongPress )
                {
                iExtension->iFlags.Clear( CAknButtonExtension::ELongPressReported );
                iExtension->StartLongPressTimerL();
                }
            }

        else if ( aType == EEventKeyUp )
            {
            if ( iButtonPressed )
                {
                iButtonPressed = EFalse;

                if ( NeedsRedrawWhenPressed() )
                    {
                    DrawNow();
                    }
                }

            StopKeyRepeatTimer();
            StopLongPressTimer();

            // The state is not changed, if it is already changed on key
            // down event, or if a long press or a key repeat event is
            // already reported to the observer.
            if ( !( iFlags & KAknButtonReportOnKeyDown ) &&
                 !( iExtension->iFlags.IsSet( CAknButtonExtension::ELongPressReported ) ) &&
                 !( iExtension->iFlags.IsSet( CAknButtonExtension::EKeyRepeatEventReported ) ) &&
                 iKeyDownReported )
                {
                ChangeState( ETrue );
                if ( Observer() )
                    {
                    Observer()->HandleControlEventL( this,
                        MCoeControlObserver::EEventStateChanged );
                    }
                }
            else
                {
                if ( iExtension->iFlags.IsSet( CAknButtonExtension::ELongPressReported ) && iKeyDownReported )
                    {
                    Observer()->HandleControlEventL( this, 
                        static_cast<MCoeControlObserver::TCoeEvent>( 
                        CAknButton::ELongPressEndedEvent ) );
                    }
                iExtension->iFlags.Clear( CAknButtonExtension::ELongPressReported );
                iExtension->iFlags.Clear( CAknButtonExtension::EKeyRepeatEventReported );
                }

            if ( iKeyDownReported && RequestExit() && Observer() )
                {
                Observer()->HandleControlEventL( this,
                    MCoeControlObserver::EEventRequestExit );
                }

            iKeyDownReported = EFalse;
            }
        // we don't want aKeyEvent to go somewhere else :)
        return EKeyWasConsumed;
        }

    return EKeyWasNotConsumed;
    }

// -----------------------------------------------------------------------------
// CAknButton::MakeVisible
// Sets this control as visible or invisible.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::MakeVisible( TBool aVisible )
    {
    if ( aVisible != IsVisible() )
        {
        CAknControl::MakeVisible( aVisible );
        if ( iExtension->iFeedback )
            {
            if ( aVisible )
                {
                iExtension->iFeedback->MoveFeedbackAreaToFirstPriority( this, 
                                                                        0 );
                }
            iExtension->iFeedback->EnableFeedbackForControl( 
                    this, 
                    aVisible && !IsDimmed() );
            }

        CAknButtonState* state = State();
        if ( !aVisible && state && state->HasHelp() )
            {
            HideHelp();
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknButton::PrepareForFocusLossL
// This function is called by the dialog framework immediately before it removes
// keyboard focus from a control within a dialog.
// Currently has empty implementation.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::PrepareForFocusLossL()
    {
    CAknControl::PrepareForFocusLossL(); // empty but it can be changed... :)
    }

// -----------------------------------------------------------------------------
// CAknButton::PrepareForFocusGainL
// Prepares the control for gaining focus.
// Must be used before calling SetFocus() function in case when help note
// should be shown.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::PrepareForFocusGainL()
    {
    CAknControl::PrepareForFocusGainL(); // empty but it can be changed... :)

    CAknButtonState* state = State();
    if ( state && state->HasHelp() && IsVisible() && !IsFocused() )
        {
        iShowHelp = ETrue;
        }
    else
        {
        iShowHelp = EFalse;
        }
    }

// -----------------------------------------------------------------------------
// CAknButton::SizeChanged
// Responds to size changes to sets the size and position of the contents of
// this control.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::SizeChanged()
    {
    // If default icon size from LAF is used re-request that, otherwise trust
    // that size will be updated by the utilising application.
    if ( iExtension->iFlags.IsSet( CAknButtonExtension::EUseDefaultIconSize ) )
        {
        if ( iFlags & KAknButtonNoFrame && !State()->HasText() )
            {
            iExtension->iIconSize = Size();
            }
        else
            {
            TAknLayoutRect layoutRect;
            layoutRect.LayoutRect( Rect(), 
                AknLayoutScalable_Avkon::toolbar_button_pane_g10().LayoutLine() );
            iExtension->iIconSize = layoutRect.Rect().Size();
            }
        }

    // Update margins from LAF if default values are used. This also refreshes
    // icon size in case it overlaps margins.
    CalculateDefaultMargins();
        
    // scale all icons
    ScaleIcons();

    // Pressed down frame has to be regenerated
    if ( iFlags & KAknButtonNoFrame && iFlags & KAknButtonPressedDownFrame ) 
       {
        TRAP_IGNORE( CreatePressedDownFrameL() );
        }

    iExtension->HandleFeedbackAreaChange();
    }

// -----------------------------------------------------------------------------
// CAknButton::HandlePointerEventL
// Handles pointer events.
// @param aPointerEvent is the pointer event.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::HandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    if ( AknLayoutUtils::PenEnabled() )
        {
        if ( !IsVisible() )
            {
            if ( iButtonPressed )
                {
                ResetState();               
                }
            return;
            }
        TBool buttonEvent( TouchArea().Contains( aPointerEvent.iPosition ) );
        CAknButtonState* state = State();
        if ( !state )
            {
            return;
            }            
        
        if ( ( iFlags & KAknButtonHitTest ) && 
             !HitAreaContainsL( aPointerEvent.iPosition, EFalse ) )
            {
            buttonEvent = EFalse;
            }
        
        TBool redrawNeeded(EFalse);
        switch ( aPointerEvent.iType )
            {
            case TPointerEvent::EButton1Down:
                {
                if ( buttonEvent && IsDimmed() )
                    {
                    ShowHelpL();
                    }
                else if ( buttonEvent )
                    {
                    if ( !iButtonPressed )
                        {
                        iButtonPressed = ETrue;
                        // feedback/basic on down event, if hit test is
                        // used. Area registry is used for rectangular
                        // buttons
                        if ( ( iFlags & KAknButtonHitTest ) 
                           && !IsDimmed() 
                           && iExtension->iFeedback )
                            {
                            iExtension->iFeedback->InstantFeedback(
                                                    this,
                                                    ETouchFeedbackBasicButton,
                                                    aPointerEvent );
                            }

                        // make a mark so that we can later test that the button press comes from pointer event
                        iButtonPressed |= KPointerFlag;

                        // Redraw button, if needed
                        if ( NeedsRedrawWhenPressed() )
                            {
                            redrawNeeded = ETrue;
                            }

                        ShowHelpL();
                        }

                    if ( iFlags & KAknButtonReportOnKeyDown )
                        {
                        // State is changed on button down event
                        ChangeState( EFalse );
                        redrawNeeded = ETrue;
                        if ( Observer() )
                            {
                            Observer()->HandleControlEventL( this,
                                MCoeControlObserver::EEventStateChanged );
                            }
                        }

                    if ( iFlags & KAknButtonKeyRepeat )
                        {
                        // Key repeat
                        iExtension->iFlags.Clear( CAknButtonExtension::EKeyRepeatEventReported );
                        StartKeyRepeatTimerL();
                        }

                    if ( iFlags & KAknButtonReportOnLongPress )
                        {
                        iExtension->iFlags.Clear( CAknButtonExtension::ELongPressReported );
                        iExtension->StartLongPressTimerL();
                        }
                    }
                break;
                }

            case TPointerEvent::EDrag:
                {
                iNumberOfDragEvents++;
                if ( iNumberOfDragEvents >= KDragEventSensitivity  )
                    {
                    iNumberOfDragEvents = 0;

                    // Pointer is dragged out of the button area
                    if ( !buttonEvent && iButtonPressed )
                        {
                        // Redraw button, if needed
                        if ( NeedsRedrawWhenPressed() )
                            {
                            iButtonPressed = EFalse;
                            redrawNeeded = ETrue;
                            }
                        iButtonPressed = EFalse;

                        StopKeyRepeatTimer();
                        StopLongPressTimer();

                        if ( !IsFocused() )
                            {
                            HideHelp();
                            }
                        if ( iExtension->iFlags.IsSet( CAknButtonExtension::ELongPressReported ) && Observer() )
                            {
                            Observer()->HandleControlEventL( this, 
                                static_cast<MCoeControlObserver::TCoeEvent>( 
                                CAknButton::ELongPressEndedEvent ) );
                            }
                        iExtension->iFlags.Clear( CAknButtonExtension::ELongPressReported );
                        }

                    // Pointer is dragged back into button area
                    else if ( buttonEvent && !iButtonPressed && !IsDimmed() )
                        {
                        iButtonPressed = ETrue;

                        // Redraw button, if needed
                        if ( NeedsRedrawWhenPressed() )
                            {
                            redrawNeeded = ETrue;
                            }

                        if ( iFlags & KAknButtonKeyRepeat )
                            {
                            // Continue key repeat
                            StartKeyRepeatTimerL();
                            }

                        if ( ( iFlags & KAknButtonReportOnLongPress ) &&
                             !( iExtension->iFlags.IsSet( CAknButtonExtension::ELongPressReported ) ) )
                            {
                            // Restart long press timer
                            StartLongPressTimerL();
                            }
                        }
                    }
                break;
                }

            case TPointerEvent::EButton1Up:
                {
                iNumberOfDragEvents = 0;
                HideHelp();

                StopKeyRepeatTimer();
                StopLongPressTimer();

                if ( iButtonPressed )
                    {
                    // Redraw button, if needed
                    if ( NeedsRedrawWhenPressed() )
                        {
                        iButtonPressed = EFalse;
                        if ( ! ( buttonEvent && iStates->Count() > 1 ) ) 
                            {
                            redrawNeeded = ETrue;
                            }
                        }
                    iButtonPressed = EFalse;
                    }

                if ( buttonEvent && !IsDimmed() )
                    {
                        // feedback/BasicButton on up event, if hit test is
                        // used. Area registry is used for rectangular
                        // buttons
                        if ( ( iFlags & KAknButtonHitTest ) 
                           && iExtension->iFeedback )
                            {
                            iExtension->iFeedback->InstantFeedback(
                                                    this,
                                                    ETouchFeedbackBasicButton,
                                                    ETouchFeedbackVibra,
                                                    aPointerEvent );
                            }
                    // The state is not changed, if it is already changed on key
                    // down event, or if a long press or a key repeat event is
                    // already reported to the observer.
                    if ( !( iFlags & KAknButtonReportOnKeyDown ) &&
                         !( iExtension->iFlags.IsSet( CAknButtonExtension::ELongPressReported ) ) &&
                         !( iExtension->iFlags.IsSet( CAknButtonExtension::EKeyRepeatEventReported ) ) )
                        {
                        ChangeState( EFalse );
                        redrawNeeded = ETrue;
                        if ( Observer() )
                            {
                            Observer()->HandleControlEventL( this,
                                MCoeControlObserver::EEventStateChanged );
                            }
                        }
                   else
                        {
                        if ( iExtension->iFlags.IsSet( CAknButtonExtension::ELongPressReported ) && Observer() )
                            {
                            Observer()->HandleControlEventL( this, 
                                static_cast<MCoeControlObserver::TCoeEvent>( 
                                CAknButton::ELongPressEndedEvent ) );
                            }
                        iExtension->iFlags.Clear( CAknButtonExtension::ELongPressReported );
                        iExtension->iFlags.Clear( CAknButtonExtension::EKeyRepeatEventReported );
                        }

                    if ( RequestExit() && Observer() )
                        {
                        Observer()->HandleControlEventL( this,
                            MCoeControlObserver::EEventRequestExit );
                        }
                    }
                        
                if ( !buttonEvent && !IsDimmed() && Observer() )
                   {
                   Observer()->HandleControlEventL( this,
                        MCoeControlObserver::EEventRequestCancel );
                        
                    if ( iExtension->iFlags.IsSet( CAknButtonExtension::ELongPressReported ) )
                        {
                        Observer()->HandleControlEventL( this, 
                            static_cast<MCoeControlObserver::TCoeEvent>( 
                            CAknButton::ELongPressEndedEvent ) );
                        iExtension->iFlags.Clear( CAknButtonExtension::ELongPressReported );
                        iExtension->iFlags.Clear( CAknButtonExtension::EKeyRepeatEventReported );
                        }                        
                   }

                break;
                }

            default:
                break;
            }
            if (redrawNeeded)    
                {
                DrawNow();
                }
        }
    }

// -----------------------------------------------------------------------------
// CAknButton::PositionChanged
// 
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::PositionChanged()
    {
    if ( iExtension ) iExtension->HandleFeedbackAreaChange();
    CAknControl::PositionChanged();
    }
    
// -----------------------------------------------------------------------------
// CAknButton::FocusChanged
// This function is called whenever a control gains or loses focus.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::FocusChanged( TDrawNow aDrawNow )
    {
    if ( !IsFocused() && iButtonPressed )
        {
        iButtonPressed = EFalse; 
        iKeyDownReported = EFalse; 
        }
    if ( IsVisible() )
        {
        
        if ( IsFocused() && iShowHelp )
            {
            TRAP_IGNORE( ShowHelpL() );
            }
        else
            {
            HideHelp();

            // Stop the timers if active
            StopLongPressTimer();
            StopKeyRepeatTimer();
            }
        if ( !IsBackedUp() && aDrawNow ) 
            {
            DrawNow();
            }
        }

    iShowHelp = EFalse;
    }

// -----------------------------------------------------------------------------
// CAknButton::ExtensionInterface
// For future extensions
// -----------------------------------------------------------------------------
//
EXPORT_C void* CAknButton::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

// -----------------------------------------------------------------------------
// CAknButton::Draw
// Draw a control called by window server.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::Draw( const TRect& /*aRect*/ ) const
    {
    TRect rect( Rect() );
    TAknLayoutRect centerLayout;
    centerLayout.LayoutRect( rect,
        AknLayoutScalable_Avkon::toolbar_button_pane_g1().LayoutLine() );
    TRect innerRect( centerLayout.Rect() );
    TRect highlightRect( HighlightRect() );
    CWindowGc& gc = SystemGc();
    CAknButtonState* state = State();

    // Skin ids are determined here (a bit too early than necessary) so that 
    // we can avoid doing the same thing in DrawMaskedL.
    if ( !( iFlags & KAknButtonNoFrame ) )
        {
        TInt frameIdIndex = KFrameId;

        if ( iButtonPressed )
            {
            frameIdIndex = KPressedFrameId;
            }
        else if ( state && state->Flags() & KAknButtonStateHasLatchedFrame )
            {
            if ( IsDimmed() )
                {
                // dimmed latched frame
                frameIdIndex = KLatchedDimmedFrameId;
                }
            else
                {
                // latched down
                frameIdIndex = KLatchedFrameId;
                }
            }
        else if ( IsDimmed())
            {
            // dimmed frame
            frameIdIndex = KDimmedFrameId;
            }

        if ( SkinIID( frameIdIndex ) != KAknsIIDNone )
            {
            iBgContext->SetFrame( SkinIID( frameIdIndex ) );
            iBgContext->SetCenter( SkinIID( ++frameIdIndex ) );
            iBgContext->SetFrameRects( rect, innerRect );
            }
        }

    if ( !iExtension->iFlags.IsSet( CAknButtonExtension::EUseAdditionalMask ) )
        {
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );

        if ( !( iFlags & KAknButtonNoFrame ) )
            {
            // frame graphics
            if ( !AknsDrawUtils::Background( skin, iBgContext, NULL, gc,
                  rect, KAknsDrawParamNoClearUnderImage ) )
                {
                gc.SetBrushColor( KRgbRed );
                gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
                gc.DrawRect( rect );
                }
                

            if ( IsFocused() && !highlightRect.IsEmpty() )
                {
                iBgContext->SetFrame( KAknsIIDQsnFrButtonHighlight ); 
                iBgContext->SetCenter( KAknsIIDQsnFrButtonHighlightCenter ); 
                iBgContext->SetFrameRects( rect, innerRect );

                // frame graphics
                if ( !AknsDrawUtils::Background( skin, iBgContext, NULL, gc,
                      rect, KAknsDrawParamNoClearUnderImage ) )
                    {
                    gc.SetBrushColor( KRgbRed );
                    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
                    gc.DrawRect( rect );
                    }
                }
            }
        else if ( ( iFlags & KAknButtonNoFrame && iFlags & KAknButtonPressedDownFrame ) &&
                    ( iButtonPressed ||
                    ( state && state->Flags() & KAknButtonStateHasLatchedFrame &&
                    !IsDimmed() ) ) )
            {
            gc.BitBltMasked( Rect().iTl, iExtension->iPressedDownBmp, 
                             TRect( TPoint(0,0), Size() ), 
                             iExtension->iPressedDownBmpMask, EFalse ); 
            }
        }
    else if ( !( iFlags & KAknButtonNoFrame ) )
        {
        if ( AknsUtils::SkinInstance() )
            {
            AknsDrawUtils::Background( AknsUtils::SkinInstance(), iBgContext, this, gc,
                   rect, KAknsDrawParamNoClearUnderImage );
            }
        }

    TBool hasIcon = ( GetCurrentIcon() != NULL );
    TBool hasText = state && state->HasText();

    if ( hasIcon && hasText )
        {
        DrawTextAndIconButton( gc );
        }
    else if ( hasText )
        {
        DrawTextButton( gc );
        }
    else if ( hasIcon )
        {
        DrawIconButton( gc );
        }
    }

// -----------------------------------------------------------------------------
// CAknButton::ConstructFromResourceL
// Constructs controls from a resource file.
// @param aResourceId is the ID for this component's resource
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::ConstructFromResourceL( const TInt aResourceId )
    {
    if ( aResourceId )
        {
        TResourceReader reader;
        iCoeEnv->CreateResourceReaderLC( reader, aResourceId );
        ConstructFromResourceL( reader );
        CleanupStack::PopAndDestroy();
        }
    }

// -----------------------------------------------------------------------------
// CAknButton::SetCurrentState
// Sets active button state index
// @param aStateIndex is the index inside state array
// @param aDrawNow should be ETrue for the button to be redrawn
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::SetCurrentState( const TInt aStateIndex,
                                           const TBool aDrawNow )
    {
    TInt newIndex = -1;
    if ( iStates && iStates->Count() )
        {
        newIndex = aStateIndex % iStates->Count();
        }

    TRAP_IGNORE( SetStateIndexL( newIndex ) );
    if ( aDrawNow )
        {
        DrawNow();
        }
    }

// -----------------------------------------------------------------------------
// CAknButton::AddStateL
// Adds one more state for the button to the end of state array.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::AddStateL( CGulIcon* aIcon,
                                     CGulIcon* aDimmedIcon,
                                     CGulIcon* aPressedIcon,
                                     CGulIcon* aHoverIcon,
                                     const TDesC& aText,
                                     const TDesC& aHelpText,
                                     const TInt aStateFlags )
    {
    CAknButtonState* state = new (ELeave) CAknButtonState( aStateFlags );
    CleanupStack::PushL( state );
    state->ConstructL( aIcon, aDimmedIcon, aPressedIcon, aHoverIcon, aText,
                       aHelpText );
    iStates->AppendL( state );
    CleanupStack::Pop( state );
    }

// -----------------------------------------------------------------------------
// CAknButton::AddStateL
// Adds one more state for the button to the end of state array.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::AddStateL( const TDesC& aFilePath,
                                     const TInt aBmpId,
                                     const TInt aMaskId,
                                     const TInt aDimmedBmpId,
                                     const TInt aDimmedMaskId,
                                     const TInt aPressedBmpId,
                                     const TInt aPressedMaskId,
                                     const TInt aHoverBmpId,
                                     const TInt aHoverMaskId,
                                     const TDesC& aText,
                                     const TDesC& aHelpText,
                                     const TInt aStateFlags,
                                     const TAknsItemID& aId,
                                     const TAknsItemID& aDimmedId,
                                     const TAknsItemID& aPressedId,
                                     const TAknsItemID& aHoverId )
    {
    CAknButtonState* state = new (ELeave) CAknButtonState( aStateFlags );
    CleanupStack::PushL( state );
    state->ConstructL( aFilePath, aBmpId, aMaskId, aDimmedBmpId, aDimmedMaskId,
         aPressedBmpId, aPressedMaskId, aHoverBmpId, aHoverMaskId,
         aText, aHelpText, aId, aDimmedId, aPressedId, aHoverId );
    iStates->AppendL( state );
    CleanupStack::Pop( state );
    }


// -----------------------------------------------------------------------------
// CAknButton::AddStateL
// Adds one more state for the button to the end of state array.
// -----------------------------------------------------------------------------
//
void CAknButton::AddStateL( CGulIcon* aIcon,
                            CGulIcon* aDimmedIcon,
                            CGulIcon* aPressedIcon,
                            CGulIcon* aHoverIcon,
                            const TDesC& aText,
                            const TDesC& aHelpText,
                            const TInt aStateFlags,
                            const TInt aCommandId )
    {
    CAknCommandButtonState* state =
        new (ELeave) CAknCommandButtonState( aStateFlags, aCommandId );
    CleanupStack::PushL( state );
    state->ConstructL( aIcon, aDimmedIcon, aPressedIcon, aHoverIcon, aText,
                       aHelpText );
    iStates->AppendL( state );
    CleanupStack::Pop( state );
    }


// -----------------------------------------------------------------------------
// CAknButton::SetFlags
// Sets the button flags
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::SetButtonFlags( const TInt aFlags )
    {
    if ( !(iFlags & KAknButtonNoFrame ) && aFlags & KAknButtonNoFrame )
        {
        iExtension->iMargins.SetAllValuesTo( 0 );
        }
    if ( aFlags & KAknButtonHitTest )
        {
        SetHitTest( iExtension );
        iExtension->HandleFeedbackAreaChange();
        }
    if ( aFlags & KAknButtonNoFrame && aFlags & KAknButtonPressedDownFrame )
        {
        TRAP_IGNORE ( CreatePressedDownFrameL() );
        }
    iFlags = aFlags;
    }

// -----------------------------------------------------------------------------
// CAknButton::SetFrameAndCenterIds
// Sets specified frame IDs. Can be used when default frame is not suitable.
// Use KAknsIIDNone value in case when some frame or center drawing is not
// needed or KAknsIIDDefault when the default button frame should be used.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::SetFrameAndCenterIds( 
    const TAknsItemID& aFrameId,
    const TAknsItemID& aCenterId,
    const TAknsItemID& aLatchedFrameId,
    const TAknsItemID& aLatchedCenterId,
    const TAknsItemID& aDimmedFrameId,
    const TAknsItemID& aDimmedCenterId,
    const TAknsItemID& aPressedFrameId,
    const TAknsItemID& aPressedCenterId,
    const TAknsItemID& aLatchedDimmedFrameId,
    const TAknsItemID& aLatchedDimmedCenterId  )
    {
    RArray<TAknsItemID>& skinIds = iExtension->iFrameAndCenterIds;
    
    if ( aFrameId != KAknsIIDDefault )
        {
        skinIds[KFrameId] = aFrameId;
        }
    if ( aCenterId != KAknsIIDDefault )
        {
        skinIds[KCenterId] = aCenterId;
        }
    if ( aLatchedFrameId != KAknsIIDDefault )
        {
        skinIds[KLatchedFrameId] = aLatchedFrameId;
        }
    if ( aLatchedCenterId != KAknsIIDDefault )
        {
        skinIds[KLatchedCenterId] = aLatchedCenterId;
        }
    if ( aDimmedFrameId != KAknsIIDDefault )
        {
        skinIds[KDimmedFrameId] = aDimmedFrameId;
        }
    if ( aDimmedCenterId != KAknsIIDDefault )
        {
        skinIds[KDimmedCenterId] = aDimmedCenterId;
        }
    if ( aPressedFrameId != KAknsIIDDefault )
        {
        skinIds[KPressedFrameId] = aPressedFrameId;
        }
    if ( aPressedCenterId != KAknsIIDDefault )
        {
        skinIds[KPressedCenterId] = aPressedCenterId;
        }
    if ( aLatchedDimmedFrameId != KAknsIIDDefault )
        {
        skinIds[KLatchedDimmedFrameId] = aLatchedDimmedFrameId;
        }
    if ( aLatchedDimmedCenterId != KAknsIIDDefault )
        {
        skinIds[KLatchedDimmedCenterId] = aLatchedDimmedCenterId;
        }
    }

// -----------------------------------------------------------------------------
// CAknButton::SetBackgroundIds
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::SetBackgroundIds( 
    const TAknsItemID& aBackgroundId,
    const TAknsItemID& aLatchedBackgroundId,
    const TAknsItemID& aDimmedBackgroundId,
    const TAknsItemID& aPressedBackgroundId,
    const TAknsItemID& aLatchedDimmedBackgroundId )
    {
    CAknButton::SetFrameAndCenterIds( aBackgroundId, aBackgroundId,
                                      aLatchedBackgroundId, 
                                      aLatchedBackgroundId,
                                      aDimmedBackgroundId, aDimmedBackgroundId,
                                      aPressedBackgroundId, 
                                      aPressedBackgroundId,
                                      aLatchedDimmedBackgroundId, 
                                      aLatchedDimmedBackgroundId );
    }

// -----------------------------------------------------------------------------
// CAknButton::SetTextFont
// Sets some specific text font.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::SetTextFont( const CFont* aFont )
    {
    iFont = aFont;
    }

// -----------------------------------------------------------------------------
// CAknButton::SetTextColorIds
// Sets the color table and color index for the button text.
// It will be used on button drawing if color of the text shouldn't be taken
// from text layout.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::SetTextColorIds( const TAknsItemID& aTextColorTableId,
                                           const TInt aTextColorIndex )
    {
    iTextColorTableId = aTextColorTableId;
    iTextColorIndex = aTextColorIndex;

    TRgb textColor;
    
    if ( AknsUtils::GetCachedColor( AknsUtils::SkinInstance(), textColor, 
        iTextColorTableId, iTextColorIndex ) == KErrNone )
        {
        TRAP_IGNORE( OverrideColorL( EColorButtonText, textColor ) );
        DrawDeferred();
        }
    }

// -----------------------------------------------------------------------------
// CAknButton::SetTextHorizontalAlignment
// Sets the horizontal alignment for the text inside the button. It will be used
// if alignment shouldn't be taken from text layout. By default it will be
// centered.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::SetTextHorizontalAlignment(
    const CGraphicsContext::TTextAlign aHorizontalAlignment )
    {
    iHorizontalAlignment = aHorizontalAlignment;
    }

// -----------------------------------------------------------------------------
// CAknButton::SetTextVerticalAlignment
// Sets the vertical alignment for the text inside the button. It will be used
// if alignment shouldn't be taken from text layout. By default it will be
// centered.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::SetTextVerticalAlignment(
    const CAknButton::TAlignment aVerticalAlignment )
    {
    iVerticalAlignment = aVerticalAlignment;
    }

// -----------------------------------------------------------------------------
// CAknButton::SetTextUnderlineStyle
// Sets the text underline style for the text inside the button.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::SetTextUnderlineStyle( TFontUnderline aUnderlineStyle )
    {
    iExtension->iUnderlineStyle = aUnderlineStyle;
    }

// -----------------------------------------------------------------------------
// CAknButton::SetIconScaleMode
// Sets the scale mode for the icon inside the button. The default is
// EAspectRatioNotPreserved.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::SetIconScaleMode( const TScaleMode aScaleMode )
    {
    iScaleMode = aScaleMode;
    
    for ( TInt i = 0; i < iStates->Count(); ++i )
        {
        CAknButtonState* state = iStates->At( i );
        
        if ( state )
            {
            state->SetIconScaleMode( aScaleMode );
            }
        }
    }
    
// -----------------------------------------------------------------------------
// CAknButton::SetIconHorizontalAlignment
// Sets the horizontal alignment for the icon inside the button.
// The default is ECenter
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::SetIconHorizontalAlignment( 
            const CAknButton::TAlignment aHorizontalAlignment )
    {
    iExtension->iHorizontalIconAlignment = aHorizontalAlignment;
    }
// -----------------------------------------------------------------------------
// CAknButton::SetIconVerticalAlignment
// Sets the vertical alignment for the icon inside the button.
// The default is ECenter
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::SetIconVerticalAlignment( 
            const CAknButton::TAlignment aVerticalAlignment )
    {
    iExtension->iVerticalIconAlignment = aVerticalAlignment;
    }

// -----------------------------------------------------------------------------
// CAknButton::SetTextAndIconAlignment
// Sets the icon and text alignment for the button having both
// The default is EIconBeforeText
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::SetTextAndIconAlignment ( 
            const CAknButton::TTextAndIconAlignment aAlignment )
    {
    iExtension->iTextAndIconAlignment = aAlignment;
    }

// -----------------------------------------------------------------------------
// CAknButton::SetHelpNoteTimeouts
// Sets the delay before the help text is shown and also specifies the time for
// how long help text is visible.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::SetHelpNoteTimeouts( const TInt aBeforeTimeout,
                                               const TInt aInViewTimeout )
    {
    if ( aBeforeTimeout >= 0 )
        {
        iHelpNoteWaitInterval = aBeforeTimeout;
        }
    if ( aInViewTimeout >= 0 )
        {
        iHelpNoteInViewInterval = aInViewTimeout;
        }

    if(iHelpNote)
        {
        iHelpNote->SetTimeDelayBeforeShow( iHelpNoteWaitInterval );
        iHelpNote->SetTimePopupInView( iHelpNoteInViewInterval );
        }
    }

// -----------------------------------------------------------------------------
// CAknButton::SetKeyRepeatInterval
// Sets the interval for the key repeat.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::SetKeyRepeatInterval( const TInt aKeyRepeatDelay,
        const TInt aKeyRepeatInterval )
    {
    // Convert time intervals to microseconds
    iKeyRepeatDelay = aKeyRepeatDelay * 1000;
    iKeyRepeatInterval = aKeyRepeatInterval * 1000;
    }

// -----------------------------------------------------------------------------
// CAknButton::SetLongPressInterval
// Sets the interval for the long presses.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::SetLongPressInterval( const TInt aLongPressInterval )
    {
    iExtension->iLongPressInterval = aLongPressInterval * 1000;
    }

// -----------------------------------------------------------------------------
// CAknButton::StateIndex
// Returns the index of the current button state.
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CAknButton::StateIndex() const
    {
    return iStateIndex;
    }

// -----------------------------------------------------------------------------
// CAknButton::EnablePictographsL
// Enables pictograph drawing in the button text.
// Only effective in Japanese variant.
// By default, it is disabled.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::EnablePictographsL( CAknPictographInterface& aInterface )
    {
    iExtension->iPictographInterface = &aInterface;
    }

// -----------------------------------------------------------------------------
// CAknButton::DisablePictographs
// Disables pictograph drawing in the button text.
// Only effective in Japanese variant.
// By default, it is disabled.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::DisablePictographs()
    {
    iExtension->iPictographInterface = NULL;
    }

// -----------------------------------------------------------------------------
// CAknButton::SetHighlightRect
// It will change the default highlight rectangular around
// the focused button
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::SetHighlightRect( const TRect& aRect )
    {
    iHighlightRect = aRect;
    }

// -----------------------------------------------------------------------------
// CAknButton::HighlightRect
// Returns highlight rectangular around button
// -----------------------------------------------------------------------------
//
EXPORT_C TRect CAknButton::HighlightRect() const
    {
    if ( IsNonFocusing() )
        {
        return TRect();
        }
    else
        {
        return iHighlightRect;
        }
    }

// -----------------------------------------------------------------------------
// CAknButton::SetTooltipPosition
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::SetTooltipPosition( const TTooltipPosition aPosition )
    {
    iExtension->iTooltipPosition = aPosition;
    }

// -----------------------------------------------------------------------------
// CAknButton::RequestExit
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::SetRequestExit( const TBool aRequestExit )
    {
    if (aRequestExit)
        {
        iFlags |= KAknButtonRequestExitOnButtonUpEvent;
        }
    else
        {
        iFlags &= ~KAknButtonRequestExitOnButtonUpEvent;
        }
    }

// -----------------------------------------------------------------------------
// CAknButton::IsDimmed
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CAknButton::IsDimmed() const
    {
    return iExtension->iFlags.IsSet( CAknButtonExtension::EDimmed );
    }

// -----------------------------------------------------------------------------
// CAknButton::SetHelpTextL
// Sets the help text for dimmed button
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::SetDimmedHelpTextL( const TDesC& aHelpText )
    {
    delete iDimmedHelpText;
    iDimmedHelpText = NULL;

    iDimmedHelpText = aHelpText.AllocL();
    }

// -----------------------------------------------------------------------------
// CAknButton::ChangeState
// Changes the state of the button
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CAknButton::ChangeState( TBool aDrawNow )
    {
    if ( !iStates || !iStates->Count() )
        {
        return -1;
        }

    TInt newIndex( iStateIndex + 1 );

    if ( iStateIndex == iStates->Count() - 1 )
        {
        newIndex = 0;
        }
    
    TRAP_IGNORE( SetStateIndexL( newIndex ) );
    
    if ( aDrawNow )
        {
        DrawNow();
        }

    return iStateIndex;
    }

// -----------------------------------------------------------------------------
// CAknButton::GetCurrentText
// Returns the texts which will be displayed inside the button for the current
// state.
// -----------------------------------------------------------------------------
//
EXPORT_C const TDesC& CAknButton::GetCurrentText() const
    {
    CAknButtonState* state = State();
    if ( state )
        {
        return state->Text();
        }
    else
        {
        return KNullDesC();
        }
    }

// -----------------------------------------------------------------------------
// CAknButton::GetCurrentIcon
// Returns the right icon for the current state
// -----------------------------------------------------------------------------
//
EXPORT_C const CGulIcon* CAknButton::GetCurrentIcon() const
    {
    CAknButtonState* state = State();
    const CGulIcon* icon = NULL;
    if ( state )
        {
        if ( iButtonPressed && state->PressedIcon() )
            {
            icon = state->PressedIcon();
            }
        else if ( IsDimmed() && state->DimmedIcon() )
            {
            icon = state->DimmedIcon();
            }
        else
            {
            icon = state->Icon();
            }
        }
    return icon;
    }

// -----------------------------------------------------------------------------
// CAknButton::ShowHelpL
// Shows help text for a certain period of time.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::ShowHelpL()
    {
    if ( !IsVisible() )
        {
        return;
        }
    if ( !iHelpNote )
        {
        iHelpNote = CAknInfoPopupNoteController::NewL();
        
        iHelpNote->SetTimeDelayBeforeShow( iHelpNoteWaitInterval );
        iHelpNote->SetTimePopupInView( iHelpNoteInViewInterval );
        iHelpNote->SetTooltipModeL( ETrue );
        }
        
    if ( IsDimmed() && iDimmedHelpText )
        {
        iHelpNote->SetTextL( *iDimmedHelpText );
        }
    else
        {
        CAknButtonState* state = State();
        if ( state && state->HasHelp() )
            {
            iHelpNote->SetTextL( state->HelpText() );
            }
        else
            {
            return;
            }
        }

    UpdateTooltipPosition();
    iHelpNote->ShowInfoPopupNote();
    }

// -----------------------------------------------------------------------------
// CAknButton::HideHelp
// Hides help text after certain interval.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::HideHelp()
    {
    if(iHelpNote)
        {
        iHelpNote->HideInfoPopupNote();
        }
    }

// -----------------------------------------------------------------------------
// CAknButton::State
// Returns current state.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknButtonState* CAknButton::State() const
    {
    return State( iStateIndex );
    }

// -----------------------------------------------------------------------------
// CAknButton::State
// Returns the state under the specified index.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknButtonState* CAknButton::State( const TInt aStateIndex ) const
    {
    CAknButtonState* state = NULL;
    if ( iStates && aStateIndex >= 0 && aStateIndex < iStates->Count() )
        {
        state = iStates->At( aStateIndex );
        }
    return state;
    }

// -----------------------------------------------------------------------------
// CAknButton::Flags
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CAknButton::ButtonFlags() const
    {
    return iFlags;
    }

// -----------------------------------------------------------------------------
// CAknButton::SetMargins
// Sets button's marginals.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::SetMargins( const TMargins8& aMargins )
    {
    iExtension->iFlags.Clear( CAknButtonExtension::EUseDefaultMargins );
    iExtension->iMargins = aMargins;
    SizeChanged();
    }
    
// -----------------------------------------------------------------------------
// CAknButton::SetIconSize
// Sets button's icon size.
// -----------------------------------------------------------------------------
//
EXPORT_C TInt CAknButton::SetIconSize( const TSize& aSize )
    {
    iExtension->iFlags.Clear( CAknButtonExtension::EUseDefaultIconSize );
    iExtension->iIconSize = aSize;
    
    return ScaleIcons();
    }
       
// -----------------------------------------------------------------------------
// CAknButton::ResetState
// Sets button to unpressed state. 
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknButton::ResetState( )
    {
    StopKeyRepeatTimer();
    StopLongPressTimer();
    iButtonPressed = EFalse;
    HideHelp();
    if ( iExtension )
        {
        if ( iExtension->iFlags.IsSet( CAknButtonExtension::ELongPressReported ) && Observer() )
            {
            TRAP_IGNORE( Observer()->HandleControlEventL( this, 
            static_cast<MCoeControlObserver::TCoeEvent>( CAknButton::ELongPressEndedEvent ) ) );
            }
        
        iExtension->iFlags.Clear( CAknButtonExtension::ELongPressReported );
        iExtension->iFlags.Clear( CAknButtonExtension::EKeyRepeatEventReported );
        } 
    }

// -----------------------------------------------------------------------------
// CAknButton::CalculateDefaultMargins
// Calculates default margins.
// -----------------------------------------------------------------------------
//
void CAknButton::CalculateDefaultMargins()
    {
    if ( iExtension->iFlags.IsSet( CAknButtonExtension::EUseDefaultMargins ) )
        {
        if ( !( iFlags & KAknButtonNoFrame ) )
            {
            TAknLayoutRect layoutRect;
            layoutRect.LayoutRect( Rect(), 
                AknLayoutScalable_Avkon::aid_value_unit2().LayoutLine() );
            iExtension->iMargins.SetAllValuesTo( 
                layoutRect.Rect().Size().iWidth / 10 ); // always square 
            }
        }

    if ( iExtension->iFlags.IsSet( CAknButtonExtension::EUseDefaultIconSize ) )
        {
        // ensure that icon size never exceeds the space inside margins
        TRect rectInsideMargins( iExtension->iMargins.InnerRect( Rect() ) );
        
        if ( rectInsideMargins.Size().iWidth < iExtension->iIconSize.iWidth )
            {
            iExtension->iIconSize.iWidth = 
                Max( 0, rectInsideMargins.Size().iWidth );
            }
            
        if ( rectInsideMargins.Size().iHeight < iExtension->iIconSize.iHeight )
            {
            iExtension->iIconSize.iHeight = 
                Max( 0, rectInsideMargins.Size().iHeight );
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknButton::ScaleIcons
// Scales all icons.
// -----------------------------------------------------------------------------
//
TInt CAknButton::ScaleIcons()
    {
    TInt retval = KErrNone;
    
    for ( TInt i = 0; i < iStates->Count(); ++i )
        {
        CAknButtonState* state = iStates->At( i );
        
        if ( state )
            {
            retval = Min( retval, state->ScaleIcons( iExtension->iIconSize,
                                                     iScaleMode ) );
            if ( iExtension->iFlags.IsSet( CAknButtonExtension::EDimmed ) && 
                !state->iDimmedIcon &&
                state->iIcon )
                {
                TRAP_IGNORE( CreateAndSetDimmedIconL( state->iDimmedIcon, 
                    state->iIcon, state->ScaleMode() ) );
                }
            }
        }
        
    return retval;        
    }
    
// -----------------------------------------------------------------------------
// CAknButton::DrawTextButton
// Continues drawing of the button which has only text
// -----------------------------------------------------------------------------
//
void CAknButton::DrawTextButton( CWindowGc& aGc ) const
    {
    CAknButtonState* state = State();
    if ( !state || !state->HasText() )
        return;

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    TRect textRect = iExtension->iMargins.InnerRect( Rect() );

    if ( !( iFlags & KAknButtonNoFrame ) && 
         ( iFlags & KAknButtonTextInsideFrame ) )
        {
        TAknLayoutRect center;
        center.LayoutRect( Rect(), 
            AknLayoutScalable_Avkon::toolbar_button_pane_g1().LayoutLine() );

        textRect = center.Rect();
        }

    aGc.SetBrushStyle( CGraphicsContext::ENullBrush );

    TRgb penColor;
    TRgb brushColor;
    GetTextColors( penColor, brushColor ); 
    aGc.SetPenColor( penColor ); 
    aGc.SetBrushColor( brushColor ); 

    const CFont* font = iFont;
    if ( !font )
        {
        font = iCoeEnv->NormalFont();
        }
    aGc.UseFont( font );

    aGc.SetUnderlineStyle( iExtension->iUnderlineStyle );

    // buffer for visually ordered text
    TBuf<255 + KAknBidiExtraSpacePerLine> visualText; 
    TInt clipWidth = textRect.Width();

    // bidi processing - using AknBidiTextUtils.
    AknBidiTextUtils::ConvertToVisualAndClip(
        state->Text(),
        visualText,
        *font,
        clipWidth,
        clipWidth );

    TInt baselineOffset = 0;
    switch ( iVerticalAlignment )
        {
        case ETop:
            baselineOffset = font->AscentInPixels();
            break;

        case EBottom:
            baselineOffset = textRect.Height();
            break;

        default:  // centered
            baselineOffset = font->AscentInPixels() +
                           ( textRect.Height() - font->AscentInPixels() ) / 2;
        }

    CGraphicsContext::TTextAlign horAlignment = iHorizontalAlignment;

    aGc.DrawText( visualText, textRect, baselineOffset, horAlignment );
    if ( iExtension->iPictographInterface )
        {
        // For Japanese variant only
        iExtension->iPictographInterface->Interface()->DrawPictographsInText(
            aGc, *font, visualText, textRect, baselineOffset, horAlignment );
        }
    }

// -----------------------------------------------------------------------------
// CAknButton::DrawIconButton
// Continues drawing of the button which has only an icon in it
// -----------------------------------------------------------------------------
//
void CAknButton::DrawIconButton( CWindowGc& aGc ) const
    {
    TRect iconRect( iExtension->iMargins.InnerRect( Rect() ) );
    
    aGc.SetBrushStyle( CGraphicsContext::ENullBrush );

    const CGulIcon* icon = GetCurrentIcon();
    if ( !icon )
        return;

    CFbsBitmap* buttonBmp = icon->Bitmap();
    CFbsBitmap* buttonMask = icon->Mask();

    TPoint iconPoint;
    TSize iconSize ( buttonBmp->SizeInPixels());

    switch ( iExtension->iHorizontalIconAlignment )
        {
        case ERight:
            {
            iconPoint.iX = iconRect.iBr.iX - iconSize.iWidth;                        
            }
            break;  

        case ECenter:
            {
            iconPoint.iX = iconRect.iTl.iX + 
            (iconRect.Width() / 2 - iconSize.iWidth / 2 );
            } 
            break;
            
        case ELeft:
            {
            iconPoint.iX = iconRect.iTl.iX;
            }
            break; 
        
        default:
            // Should never come here
            break;
        }

    switch ( iExtension->iVerticalIconAlignment )
        {
        case ETop:
            {
            iconPoint.iY = iconRect.iTl.iY;
            }
            break;
        
        case ECenter:
            {
            iconPoint.iY = iconRect.iTl.iY +
            ( iconRect.Height() / 2 - iconSize.iHeight / 2 );
            }
            break;
          
        case EBottom:
            {
            iconPoint.iY = iconRect.iBr.iY - iconSize.iHeight;
            }
            break;
            
        default:
            // Should never come here
            break;
        }

    if( buttonBmp && buttonMask )
        {
        aGc.BitBltMasked( iconPoint, buttonBmp,
            iconRect.Size(), buttonMask, ETrue );
        }
    else if ( buttonBmp )
        {
        aGc.BitBlt( iconPoint, buttonBmp, iconRect.Size() );
        }
    }

// -----------------------------------------------------------------------------
// CAknButton::DrawTextAndIconButton
// Continues drawing of the button which has both text and icon
// -----------------------------------------------------------------------------
//
void CAknButton::DrawTextAndIconButton( CWindowGc& aGc ) const
    {
    CAknButtonState* state = State();
    if ( !state  || !state->HasText() )
        {
        return;
        }
    
    const CGulIcon* icon = GetCurrentIcon();
    if ( !icon )
        {
        return;
        }

    TRect rect = iExtension->iMargins.InnerRect( Rect() );
    TRect iconRect;
    TRect textRect;
    
    if ( !( iFlags & KAknButtonNoFrame ) &&
          ( iFlags & KAknButtonTextInsideFrame ))
        {
        TAknLayoutRect centerLayout;
        centerLayout.LayoutRect( rect,
        AknLayoutScalable_Avkon::toolbar_button_pane_g1().LayoutLine() );
        rect = centerLayout.Rect();
        }

    CFbsBitmap* buttonBmp = icon->Bitmap();
    CFbsBitmap* buttonMask = icon->Mask();
    TSize iconSize ( buttonBmp->SizeInPixels());
    
    // Set rects for icon and text according to their positioning
    // First icon rect according to icon size - rest is for text
    
    switch ( iExtension->iTextAndIconAlignment )        
        {
        case EIconBeforeText:
            if ( AknLayoutUtils::LayoutMirrored() ) 
                {
                textRect.SetRect( rect.iTl.iX, rect.iTl.iY,
                rect.iBr.iX - iconSize.iWidth, rect.iBr.iY);
                iconRect.SetRect( rect.iTl.iX + 
                    rect.Width() -iconSize.iWidth,
                rect.iTl.iY, rect.iBr.iX, rect.iBr.iY );    
                }
            else
                {
                iconRect.SetRect( rect.iTl.iX, rect.iTl.iY,
                rect.iTl.iX + iconSize.iWidth, rect.iBr.iY);
                textRect.SetRect( rect.iTl.iX + iconSize.iWidth,
                rect.iTl.iY, rect.iBr.iX, rect.iBr.iY );    
                }
            
            break;
            
        case EIconAfterText:
            if ( AknLayoutUtils::LayoutMirrored() ) 
                {
                iconRect.SetRect( rect.iTl.iX, rect.iTl.iY,
                rect.iTl.iX + iconSize.iWidth, rect.iBr.iY);
                textRect.SetRect( rect.iTl.iX + iconSize.iWidth,
                rect.iTl.iY, rect.iBr.iX, rect.iBr.iY );    
                }
            else
                {
                textRect.SetRect( rect.iTl.iX, rect.iTl.iY,
                rect.iBr.iX - iconSize.iWidth, rect.iBr.iY);
                iconRect.SetRect( rect.iTl.iX + 
                    rect.Width() -iconSize.iWidth,
                rect.iTl.iY, rect.iBr.iX, rect.iBr.iY );
                }
            break;
        
        case EIconOverText:
            iconRect.SetRect( rect.iTl.iX, rect.iTl.iY,
            rect.iBr.iX, rect.iTl.iY + iconSize.iHeight );
            textRect.SetRect( rect.iTl.iX, rect.iTl.iY + iconSize.iHeight,
            rect.iBr.iX, rect.iBr.iY );
            break;
            
        case EIconUnderText:
            textRect.SetRect( rect.iTl.iX, rect.iTl.iY,
            rect.iBr.iX, rect.iBr.iY - iconSize.iHeight );
            iconRect.SetRect( rect.iTl.iX, rect.iBr.iY - iconSize.iHeight,
            rect.iBr.iX, rect.iBr.iY );
            break;

        case EOverlay:
            {
            textRect = rect;
            iconRect = rect;
            }
            break;
            
        default:
            return;
        }

    // Draw icon
    TPoint iconPoint;
    switch ( iExtension->iHorizontalIconAlignment )
        {
        case ERight:
            {
            iconPoint.iX = iconRect.iBr.iX - iconSize.iWidth;                        
            }
            break;  

        case ECenter:
            {
            iconPoint.iX = iconRect.iTl.iX + 
            (iconRect.Width() / 2 - iconSize.iWidth / 2 );
            } 
            break;
            
        case ELeft:
            {
            iconPoint.iX = iconRect.iTl.iX;
            }
            break; 
        
        default:
            // Should never come here
            break;
        }

    switch ( iExtension->iVerticalIconAlignment )
        {
        case ETop:
            {
            iconPoint.iY = iconRect.iTl.iY;
            }
            break;
        
        case ECenter:
            {
            iconPoint.iY = iconRect.iTl.iY +
            ( iconRect.Height() / 2 - iconSize.iHeight / 2 );
            }
            break;
          
        case EBottom:
            {
            iconPoint.iY = iconRect.iBr.iY - iconSize.iHeight;
            }
            break;
            
        default:
            // Should never come here
            break;
        }

    if( buttonBmp && buttonMask )
        {
        aGc.BitBltMasked( iconPoint, buttonBmp,
            iconRect.Size(), buttonMask, ETrue );
        }
    else if ( buttonBmp )
        {
        aGc.BitBlt( iconPoint, buttonBmp, iconRect.Size() );
        }

    const CFont* font = iFont;
    if ( !font )
        {
        font = iCoeEnv->NormalFont();
        }
    aGc.UseFont( font );
        
    TRgb penColor;
    TRgb brushColor;
    GetTextColors( penColor, brushColor ); 
    aGc.SetPenColor( penColor ); 
    aGc.SetBrushColor( brushColor ); 

    aGc.SetUnderlineStyle( iExtension->iUnderlineStyle );

    TBuf<255 + KAknBidiExtraSpacePerLine> visualText; // buffer for visually ordered text
    TInt clipWidth = textRect.Width();

    // bidi processing - using AknBidiTextUtils.
    AknBidiTextUtils::ConvertToVisualAndClip(
        state->Text(),
        visualText,
        *font,
        clipWidth,
        clipWidth );

    TInt baselineOffset = 0;
    switch ( iVerticalAlignment )
        {
        case ETop:
            baselineOffset = font->AscentInPixels();
            break;

        case EBottom:
            baselineOffset = textRect.Height();
            break;

        default:  // centered
            baselineOffset = font->AscentInPixels() +
                           ( textRect.Height() - font->AscentInPixels() ) / 2;
        }

    CGraphicsContext::TTextAlign horAlignment = iHorizontalAlignment;

    aGc.DrawText( visualText, textRect, baselineOffset, horAlignment );
    if ( iExtension->iPictographInterface )
        {
        // For Japanese variant only
        iExtension->iPictographInterface->Interface()->DrawPictographsInText(
            aGc, *font, visualText, textRect, baselineOffset, horAlignment );
        }
    }

// -----------------------------------------------------------------------------
// Starts the long press timer.
// -----------------------------------------------------------------------------
//
void CAknButton::StartLongPressTimerL()
    {
    if ( iExtension )
        {
        iExtension->StartLongPressTimerL();
        }
    }

// -----------------------------------------------------------------------------
// Stops the long press timer.
// -----------------------------------------------------------------------------
//
void CAknButton::StopLongPressTimer()
    {
    if ( iExtension && iExtension->iLongPressTimer &&
        iExtension->iLongPressTimer->IsActive() )
        {
        iExtension->iLongPressTimer->Cancel();
        }
    }

// -----------------------------------------------------------------------------
// CAknButton::StartKeyRepeatTimerL
// Starts the timer for the long presses. The timer is constructed when used
// for the first time.
// -----------------------------------------------------------------------------
//
void CAknButton::StartKeyRepeatTimerL()
    {
    if ( !iKeyRepeatTimer )
        {
        iKeyRepeatTimer = CPeriodic::NewL( CActive::EPriorityStandard );
        }
    else if ( iKeyRepeatTimer->IsActive() )
        {
        iKeyRepeatTimer->Cancel();
        }

    if ( iKeyRepeatInterval > 0 )
        {
        iKeyRepeatTimer->Start( iKeyRepeatDelay, iKeyRepeatInterval,
            TCallBack( ReportKeyRepeatL, this ) );
        }
    }

// -----------------------------------------------------------------------------
// Stops the key repeat timer.
// -----------------------------------------------------------------------------
//
void CAknButton::StopKeyRepeatTimer()
    {
    if ( iKeyRepeatTimer && iKeyRepeatTimer->IsActive() )
        {
        iKeyRepeatTimer->Cancel();
        }
    }

// -----------------------------------------------------------------------------
// CAknButton::ReportKeyRepeatL
// Cancel the timer.
// -----------------------------------------------------------------------------
//
TInt CAknButton::ReportKeyRepeatL( TAny* aThis )
    {
    // Fixes TSW error AJUA-7CEF8H 
    User::ResetInactivityTime();
    CAknButton* self = reinterpret_cast< CAknButton* >( aThis );

    if ( self->IsVisible() && 
        !self->iExtension->iFlags.IsSet( CAknButtonExtension::EDimmed ) )
        {
        if ( self->iStates->Count() > 1 )
            {
            self->ChangeState( ETrue );
            }

        if ( self->Observer() )
            {
            self->Observer()->HandleControlEventL( self,
                MCoeControlObserver::EEventStateChanged );
            }

        TBool feedbackNeeded = (self->iStates->Count() > 1) || (self->Observer());
        TBool pointerRepeat = (self->iButtonPressed & KPointerFlag);  // it was caused by pointer event
        if ( self->iExtension->iFeedback && feedbackNeeded && pointerRepeat)
            {
            self->iExtension->iFeedback->InstantFeedback( self, ETouchFeedbackSensitiveButton );
            }

        self->iExtension->iFlags.Set( CAknButtonExtension::EKeyRepeatEventReported );
        }
    else if ( self->iKeyRepeatTimer && self->iKeyRepeatTimer->IsActive() )
        {
        self->iKeyRepeatTimer->Cancel();
        }

    return 1; // CPeriodic ignores return value
    }

// -----------------------------------------------------------------------------
// CAknButton::Extension
// -----------------------------------------------------------------------------
//
CAknButtonExtension* CAknButton::Extension() const
    {
    return iExtension;
    }

// -----------------------------------------------------------------------------
// CAknButton::UpdateTooltipPosition
// -----------------------------------------------------------------------------
//
void CAknButton::UpdateTooltipPosition()
    {
    TPoint position;

    if ( AknsUtils::GetControlPosition( this, position ) != KErrNone )
        {
        position = PositionRelativeToScreen();
        }
    TRect rect( position, Size() );

    TPoint center = rect.Center();

    switch ( iExtension->iTooltipPosition )
        {
        case EPositionTop:
            {
            iHelpNote->SetPositionAndAlignment(
                TPoint( center.iX, rect.iTl.iY ), EHCenterVBottom );
            break;
            }
        case EPositionBottom:
            {
            iHelpNote->SetPositionAndAlignment(
                TPoint( center.iX, rect.iBr.iY ), EHCenterVTop );
            break;
            }
        case EPositionLeft:
            {
            iHelpNote->SetPositionAndAlignment(
                TPoint( rect.iTl.iX, center.iY ), EHRightVCenter );
            break;
            }
        case EPositionRight:
            {
            iHelpNote->SetPositionAndAlignment(
                TPoint( rect.iBr.iX, center.iY ), EHLeftVCenter );
            break;
            }
        default:
            {
            return;
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknButton::RequestExit
// Returns whether button should send EEventRequestExit to command observer
// on button up events.
// -----------------------------------------------------------------------------
//
TBool CAknButton::RequestExit() const
    {
    if ( iFlags & KAknButtonRequestExitOnButtonUpEvent )
        {
        return ETrue;
        }
    else
        {
        return EFalse;
        }
    }

// -----------------------------------------------------------------------------
// CAknButton::ContentRect
// Returns the the rectangle reserved for frame center, or the rect for text and
// icon, if the button has no frames (controls rect for now).
// -----------------------------------------------------------------------------
//
TRect CAknButton::ContentRect() const
    {    
    TRect rect( Size() );
    if ( !( iFlags & KAknButtonNoFrame ) && 
          ( iFlags & KAknButtonTextInsideFrame ) )
        {
        TAknLayoutRect centerLayout;
        centerLayout.LayoutRect( rect,
        AknLayoutScalable_Avkon::toolbar_button_pane_g1().LayoutLine() );
        rect = centerLayout.Rect();        
        }
    return rect;
    }

// -----------------------------------------------------------------------------
// CAknButton::NeedsRedrawWhenPressed
// Returns boolean value indicating whether button needs redraw when it is
// pressed or released without changes in its state.
// -----------------------------------------------------------------------------
//
TBool CAknButton::NeedsRedrawWhenPressed() const
    {
    CAknButtonState* state = State();
    if ( !iButtonPressed && iStates->Count() > 1 )
        {
        return EFalse; 
        }

    if ( iButtonPressed && iFlags & KAknButtonPressedDownFrame )
        {
        return ETrue;
        }
        
    return ( state && state->PressedIcon() ||
             ( !( iFlags & KAknButtonNoFrame ) &&
               !( iFlags & KAknButtonNoFramePressEvent ) &&
               !( state && state->Flags() & KAknButtonStateHasLatchedFrame &&
                  SkinIID( KPressedFrameId ) == SkinIID( KLatchedFrameId ) ) ) );
    }

// -----------------------------------------------------------------------------
// CAknButton::SkinIID
// -----------------------------------------------------------------------------
//
TAknsItemID CAknButton::SkinIID( const TInt aIndex ) const
    {
    if ( iExtension && aIndex >= 0 &&
         aIndex < iExtension->iFrameAndCenterIds.Count() )
        {
        return iExtension->iFrameAndCenterIds[aIndex];
        }
    else
        {
        return KAknsIIDNone;
        }
    }
    
// -----------------------------------------------------------------------------
// CAknButton::HitAreaContainsL
// Checks if a button icon's non-transparent area was tapped.
// -----------------------------------------------------------------------------
//
TBool CAknButton::HitAreaContainsL( const TPoint& aPoint, TBool aCheckHitArea ) const
    {
    TBool buttonEvent( ETrue );

    if ( aCheckHitArea )
        {
        if ( TouchArea().Contains( aPoint ) )
            {
            return ETrue; 
            }
        else
            {
            return EFalse; 
            }
        }
    else if ( iFlags & KAknButtonHitTest )        
        {
        TRect rect( Size() );
        TRect contentRect( ContentRect() );
        
        CFbsBitmap* bitmap = new (ELeave) CFbsBitmap;
        CleanupStack::PushL( bitmap );
        
        User::LeaveIfError( bitmap->Create( rect.Size(), EGray256 ) );
            
        CFbsBitmapDevice* device = CFbsBitmapDevice::NewL( bitmap );
        
        CleanupStack::PushL( device );
        CFbsBitGc* gc = CFbsBitGc::NewL();
        gc->Activate( device );                            
        gc->SetBrushStyle( CGraphicsContext::ENullBrush );

        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );
        
        if ( !(iFlags & KAknButtonNoFrame ) )
            {    
            CAknButtonState* state = State();
            
            TInt frameIdIndex = KFrameId;
            if ( iButtonPressed )
                {
                frameIdIndex = KPressedFrameId;
                }
            else if ( state && state->Flags() & KAknButtonStateHasLatchedFrame )
                {
                if ( IsDimmed() )
                    {
                    // dimmed latched frame
                    frameIdIndex = KLatchedDimmedFrameId;
                    }
                else
                    {
                    // latched down
                    frameIdIndex = KLatchedFrameId;
                    }
                }
            else if ( IsDimmed())
                {
                // dimmed frame
                frameIdIndex = KDimmedFrameId;
                }

            if ( SkinIID( frameIdIndex ) != KAknsIIDNone )
                {
                TAknsItemID frameId = SkinIID( frameIdIndex );
                TAknsItemID centerId = SkinIID( frameIdIndex + 1 );                                       
                
                gc->SetBrushColor( KRgbWhite );
                
                if ( !AknsDrawUtils::DrawFrame( skin, *gc, rect, 
                    contentRect, frameId, centerId, KAknsSDMAlphaOnly ) )
                    {                                                                                    
                    gc->DrawRect( rect );
                    }                                                            
                gc->DrawRect( contentRect );                        
                }
            }
        else if ( GetCurrentIcon() )
            {
            // if button has (only) icon, then mark other parts transparent
            gc->SetBrushColor( KRgbBlack );
            gc->Clear();
            CFbsBitmap* mask = GetCurrentIcon()->Mask();
            if ( mask )
                {
                gc->BitBlt( contentRect.iTl, mask, mask->SizeInPixels() );
                }
            }
        else if ( GetCurrentText() != KNullDesC )
            {
            gc->SetBrushColor( KRgbWhite );
            gc->Clear( contentRect );
            }
        else
            {
            // if this happens.. make the whole button transparent!
            gc->SetBrushColor( KRgbBlack );
            gc->Clear( contentRect );                
            }

        TRgb pixel;
        TPoint point( aPoint - Rect().iTl );
        bitmap->GetPixel( pixel, point );
        
        delete gc;                    
        CleanupStack::PopAndDestroy( 2 ); // bitmap, device

        if ( pixel == KRgbBlack )
            {
            buttonEvent = EFalse;
            }
        } // iFlags & KAknButtonHitTest
    return buttonEvent;
    }

// -----------------------------------------------------------------------------
// CAknButton::UsesDefaultMargins
// Checks if the button uses default margins.
// -----------------------------------------------------------------------------
//
TBool CAknButton::UsesDefaultMargins() const
    {
    return iExtension->iFlags.IsSet( CAknButtonExtension::EUseDefaultMargins );
    }

// -----------------------------------------------------------------------------
// CAknButton::TextColor
// Gets the correct text color.
// -----------------------------------------------------------------------------
//
TRgb CAknButton::TextColor() const
    {
    TRgb color;
    
    if ( IsDimmed() )
        {
        color = iEikonEnv->ControlColor( EColorButtonText, *this );
        color.SetAlpha( 77 );
        }
    else if ( iButtonPressed )
        {
        color = iEikonEnv->ControlColor( EColorButtonTextPressed, *this );
        }
    else
        {
        color = iEikonEnv->ControlColor( EColorButtonText, *this );
        }
        
    return color;
    }
    
// -----------------------------------------------------------------------------
// CAknButton::CreatePressedDownFrameL
// Generates a pressed down mask
// -----------------------------------------------------------------------------
//    
void CAknButton::CreatePressedDownFrameL()
    {

    // Fetch frames from frame provider if one exists
    if ( iExtension->FetchProviderPressedBmpsL() )
        {
        return;
        }

    if ( iExtension->iPressedDownBmp &&
         iExtension->iPressedDownBmp->SizeInPixels() == Size() )
        {
        iExtension->SetProviderPressedBmpsL();
        return;
        }

    iExtension->DeletePressedBmps();

    // Fetch preffered display mode for icon type images
    AknIconConfig::TPreferredDisplayMode displayMode;
    AknIconConfig::PreferredDisplayMode( 
        displayMode, AknIconConfig::EImageTypeIcon );

    iExtension->iPressedDownBmp = new ( ELeave ) CFbsBitmap;
    User::LeaveIfError( iExtension->iPressedDownBmp->Create( Size(),
        displayMode.iBitmapMode) );
    iExtension->iPressedDownBmpMask = new ( ELeave ) CFbsBitmap;
    User::LeaveIfError( iExtension->iPressedDownBmpMask->Create( Size(), 
        displayMode.iMaskMode ) );

    CFbsBitmapDevice* bmpDevice = CFbsBitmapDevice::NewL( 
        iExtension->iPressedDownBmp );
    CleanupStack::PushL( bmpDevice );
     
    CFbsBitGc* bmpGc (NULL );
    User::LeaveIfError( bmpDevice->CreateContext( bmpGc ) );
    CleanupStack::PushL( bmpGc );

    CFbsBitmapDevice* bmpMaskDevice = CFbsBitmapDevice::NewL(
        iExtension->iPressedDownBmpMask );
    CleanupStack::PushL( bmpMaskDevice );
        
    CFbsBitGc* bmpMaskGc( NULL );
    User::LeaveIfError( bmpMaskDevice->CreateContext( bmpMaskGc ) );
    CleanupStack::PushL( bmpMaskGc );

    TRect rect ( Size() );
    TAknLayoutRect centerLayout;
    centerLayout.LayoutRect( rect,
        AknLayoutScalable_Avkon::toolbar_button_pane_g1().LayoutLine() );
    TRect innerRect( centerLayout.Rect() );

    TAknWindowLineLayout unit = AknLayoutScalable_Avkon::aid_value_unit2().LayoutLine();
    innerRect.Shrink( unit.iW/10, unit.iH/10 ); 
        
    AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(),
                              *bmpGc, rect, innerRect,
                              SkinIID( KPressedFrameId ), KAknsIIDDefault,
                              KAknsDrawParamRGBOnly );
        
    AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(), 
                              *bmpMaskGc, rect, innerRect,
                              SkinIID( KPressedFrameId ), KAknsIIDDefault, 
                              KAknsSDMAlphaOnly );

    // Modify mask 50% transparent
    iExtension->iPressedDownBmpMask->LockHeap();
    
    TInt w = iExtension->iPressedDownBmpMask->SizeInPixels().iWidth; 
    TInt h = iExtension->iPressedDownBmpMask->SizeInPixels().iHeight;
    TInt dataStride = iExtension->iPressedDownBmpMask->DataStride() - w; 
    unsigned char* address = (unsigned char *)iExtension->iPressedDownBmpMask->DataAddress();  
    
            
            for ( TInt i = 0; i < h; ++i )
                {
                for ( TInt j = 0; j < w; ++j )
                    {
                    *address >>= 1;
                    ++address;
                    }
                address += dataStride;         
                }

    iExtension->iPressedDownBmpMask->UnlockHeap();

    // Set created frames to frame provider if one exists
    iExtension->SetProviderPressedBmpsL();

    CleanupStack::PopAndDestroy( 4 ); // bmpDevice, bmpGc, bmpMaskDevice, bmpMaskGc
    }


// -----------------------------------------------------------------------------
// CAknButton::HideTooltipWhenAppFaded
// Sets tooltip to show or hide itself when background faded. By default tooltip
// is not shown when background faded. 
// -----------------------------------------------------------------------------
//
void CAknButton::HideTooltipWhenAppFaded( TBool aHide )
    {
    if(iHelpNote)
        {
        iHelpNote->HideWhenAppFaded( aHide ); 
        }
    }


// -----------------------------------------------------------------------------
// CAknButton::CheckHitArea
// This checks hit area for fixed toolbar buttons. 
// -----------------------------------------------------------------------------
//
void CAknButton::CheckHitArea( )
    {
    iExtension->iFlags.Set( CAknButtonExtension::ECheckHitArea );
    SetHitTest( iExtension ); 
    iExtension->HandleFeedbackAreaChange();
    }

// -----------------------------------------------------------------------------
// CAknButton::UseAdditionalMask
// Sets button to use additional masks during drawing.
// -----------------------------------------------------------------------------
//
void CAknButton::UseMaskedDraw( TBool aMaskedDraw )
    {
    if ( aMaskedDraw )
        {
        iExtension->iFlags.Set( CAknButtonExtension:: EUseAdditionalMask );
        }
    else
        {
        iExtension->iFlags.Clear( CAknButtonExtension:: EUseAdditionalMask );
        }
    }


// -----------------------------------------------------------------------------
// Registers resource provider.
// -----------------------------------------------------------------------------
//
void CAknButton::RegisterResourceProvider( CAknResourceProvider* aProvider )
    {
    iExtension->iResourceProvider = aProvider;
    }


// -----------------------------------------------------------------------------
// Unregisters resource provider.
// -----------------------------------------------------------------------------
//
void CAknButton::UnregisterResourceProvider()
    {
    iExtension->iResourceProvider = 0;
    }
    
    
CAknsFrameBackgroundControlContext* CAknButton::BgContext()
    {
    return iBgContext;
    }


// -----------------------------------------------------------------------------
// CAknButton::RemoveCurrentState
// Removes the current state.
// -----------------------------------------------------------------------------
//
void CAknButton::RemoveCurrentState()
    {
    // Can't remove the state if it's the only one left. 
    if ( iStates->Count() > 1 )
        {
        CAknButtonState* state = iStates->At( iStateIndex );
        delete state;
        state = NULL;
        iStates->Delete( iStateIndex );
        
        iStateIndex <= 0 ? iStateIndex = 0 : iStateIndex--;
        DrawNow();
        }
    }


// -----------------------------------------------------------------------------
// CAknButton::CalculateLuminance
// Calculates color's luminance value.
// -----------------------------------------------------------------------------
//
TInt CAknButton::CalculateLuminance( const TRgb& aColor ) const 
    { 
    TInt R = aColor.Red(); 
    TInt G = aColor.Green(); 
    TInt B = aColor.Blue(); 
    // Should be scaled to 0-255? 
    TInt Y = (((66 * R) + (129 * G) + (25 * B) + 128) >> 8) + 16; 
    return Y; 
    } 


// -----------------------------------------------------------------------------
// CAknButton::ConvertColorsForOutlineEffect
// Converts the outline color to be white or black if the fill color is 
// too similar to outline color. 
// -----------------------------------------------------------------------------
//
void CAknButton::ConvertColorsForOutlineEffect( TRgb& aFillColor, TRgb& aOutlineColor ) const 
    { 
    // @todo maybe there is already some conversion utility in multimedia image library? 
    TInt innerLum = CalculateLuminance(aFillColor); 
    TInt outerLum = CalculateLuminance(aOutlineColor); 
    
    // if the defined colours are the same, then change the outline color so that 
    // it's either black or white, contrasting according to the font label text color's brightness 
    TInt difference = outerLum - innerLum; 
    difference = Abs(difference); 
    TInt half = (0xff / 2); // @todo figure out hlsMax somehow 
    TInt threshold = (0xff / 3); // @todo figure out hlsMax somehow, and decide on the threshold! 
    if(difference < threshold) 
        { 
        // if inner luminance is low, the outer luminance should be high, i.e. white 
        aOutlineColor = (innerLum < half) ? KRgbWhite : KRgbBlack; 
        } 
    } 

// -----------------------------------------------------------------------------
// CAknButton::GetTextColors
// Gets correct text colors 
// -----------------------------------------------------------------------------
//
void CAknButton::GetTextColors( TRgb& aPenColor, TRgb& aBrushColor ) const 
    {
    TBool outlineEffectOn = EFalse;
    const CAknLayoutFont* layoutFont = CAknLayoutFont::AsCAknLayoutFontOrNull( iFont ); 
    if ( layoutFont ) 
        {
        outlineEffectOn = layoutFont->FontSpecification().IsOutlineEffectOn(); 
        }

    if ( IsDimmed() ) 
        {
        aPenColor = TextColor(); 
        aBrushColor = iEikonEnv->ControlColor( EColorControlDimmedBackground,*this ); 
        }
    else
        {
        aPenColor = TextColor(); 
        aBrushColor = iEikonEnv->ControlColor( EColorControlBackground,*this );   
        }
    if ( outlineEffectOn )
        {
        ConvertColorsForOutlineEffect( aBrushColor, aPenColor ); 
        }
    }    

// -----------------------------------------------------------------------------
// CAknButton::SetStateIndexL
// Sets new state index
// -----------------------------------------------------------------------------
//
void CAknButton::SetStateIndexL( TInt aNewIndex )
    {
    if ( iStateIndex != aNewIndex )
        {
        iStateIndex = aNewIndex;
        // Create new popup note controller every time state changes
        // (text is not updated properly in help note if this is not done)
        if ( iHelpNote )
            {
            delete iHelpNote;
            iHelpNote = 0;        
            }
        iHelpNote = CAknInfoPopupNoteController::NewL();
        iHelpNote->SetTimeDelayBeforeShow( iHelpNoteWaitInterval );
        iHelpNote->SetTimePopupInView( iHelpNoteInViewInterval );
        iHelpNote->SetTooltipModeL( ETrue );
        }
    }

// -----------------------------------------------------------------------------
// CAknButton::TouchArea
// Returns the button touchable area.
// -----------------------------------------------------------------------------
//
TRect CAknButton::TouchArea() const
    {
    TRect touchRect( Rect() );
    if ( iExtension->iFlags.IsSet( CAknButtonExtension::ECheckHitArea ) )
        {
        TAknLayoutRect layoutRect;
        layoutRect.LayoutRect( Rect(), 
            AknLayoutScalable_Avkon::aid_touch_sctrl_middle( 
            !Layout_Meta_Data::IsLandscapeOrientation() ).LayoutLine() );
        touchRect = layoutRect.Rect();
        }
    return touchRect;
    }
// end of file
