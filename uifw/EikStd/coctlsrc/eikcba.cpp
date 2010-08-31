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
* Description:  Command button array implementation.
*
*/


#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikdefmacros.h>
#endif
#include <barsread.h>
#include "eikcba.h"
#include <eiklabel.h>
#include <eiksoftkeyimage.h>
#include <eiksoftkeypostingtransparency.h>
#include <eikbtgpc.h>
#include <aknappui.h>
#include <AknUtils.h> // LayoutUtils
#include <aknlayoutscalable_apps.cdl.h>
#include <AknsBasicBackgroundControlContext.h>
#include <AknsMaskedLayerBackgroundControlContext.h>
#include <AknsDrawUtils.h>
#include <AknsConstants.h>
#include <aknconsts.h>
#include <AknSgcc.h>
#include <AknStatuspaneUtils.h>
#include <aknpriv.rsg> // R_ENHANCED_CBA_PRIORITIES
#include <aknlayoutscalable_avkon.cdl.h>
#include <layoutmetadata.cdl.h>
#include <avkon.mbg>
#include <centralrepository.h>
#include <AvkonInternalCRKeys.h>  // KAknMiddleSoftkeyEnabled
#include <cenrepnotifyhandler.h>
#include <AknSkinsInternalCRKeys.h>
#include <aknQueryControl.h>
#include <aknbutton.h>
#include <akniconconfig.h>

#include <akncommandbuttonstate.h>

#include <AknTasHook.h>
#include <akncbacontentobserver.h>
#include <aknitemactionmenu.h>
#include "akncollectionobserver.h"
#include "aknitemactionmenuregister.h"

/**
 * Color value for transparent pixel (ARGB format).
 */
const TUint32 KAknCbaColorKey = 0x00000000;

/**
 * Mask for opaque pixel (ARGB format).
 */
const TUint32 KAknCbaOpaqueMask = 0xFF000000;

/**
 * Mask for outline font in font id.
 */
const TUint32 KOutlineFontMask = 0x00000040;
#include <touchfeedback.h>

inline TAknWindowComponentLayout DoCompose(TAknWindowComponentLayout aLine1, 
    TAknWindowComponentLayout aLine2) 
    { 
    return TAknWindowComponentLayout::Compose(aLine1, aLine2); 
    }

inline TAknTextComponentLayout DoComposeText(TAknWindowComponentLayout aLine1, 
    TAknTextComponentLayout aLine2) 
    { 
    return TAknWindowComponentLayout::ComposeText(aLine1, aLine2); 
    }
    
/**
* Checks if right side pane is active.
* @return ETrue if right side pane is active, EFalse otherwise.
*/
static TBool IsAreaSideRightPaneActive()
    {
    return EFalse;
    }


/**
* Checks if MSK-enabled layout is in use.
*/
static TBool IsMskEnabledLayoutActive()
    {
    TBool result( EFalse );
    
    if ( Layout_Meta_Data::IsMSKEnabled() )
        {
        // First check if MSK is enabled in the layout metadata.
        result = ETrue;
        }
    else
        {
        TInt statusPaneLayout(
            AVKONENV->StatusPaneResIdForCurrentLayout(
                 AknStatuspaneUtils::CurrentStatusPaneLayoutResId() ) );

        if ( statusPaneLayout ==
                 R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE_FLAT_NO_SOFTKEYS ||
             ( statusPaneLayout == R_AVKON_STATUS_PANE_LAYOUT_IDLE_FLAT &&
               AknLayoutUtils::PenEnabled() &&
               !Layout_Meta_Data::IsLandscapeOrientation() ) )
            {
            // MSK is not enabled in the layout metadata, but for
            // these status pane layouts an exception is made.
            result = ETrue;
            }
        }
    
    return result;
    }


/*
 * Checks if bitmap must be updated, i.e. bitmap does not exist or 
 * expected size does not match with actual size.
 */
static TBool IsBitmapUpdateNeeded( CFbsBitmap* aOldBitmap, const TSize& aSize )
    {
    return !aOldBitmap || ( aOldBitmap->SizeInPixels() != aSize );
    }


/**
 * Implementation of class CEikCba - Control button array.
 */
const TInt KNoResource                        = 0;
const TInt KMaxSeries60Softkeys               = 3; // 3 softkeys for S60 with MSK
const TInt KControlArrayCBAButton1Posn        = 0;
const TInt KControlArrayScrollBarPosn         = 1;
const TInt KControlArrayCBAButton2Posn        = 2;
const TInt KControlArrayCBAButtonMSKPosn      = 3;
const TInt KCbaScrollBarButtonWidth           = 9;  // in pixels

/** Alpha value used in drawing CBA button contents in pressed down state. */
const TInt KPressedDownAlphaValue             = 127;


/**
* Local panic definitions.
*/
enum TEikPanicCBA
    {
    EEikPanicCBAControlArraySize,
    EEikPanicCBANullButton,
    EEikPanicCBACannotConvertToCEikCommandButton,
    EEikPanicCBAIsNotEnhancedCba,
    EEikPanicCBAButtonCountDiffersFromCommandTableSize
    };

/**
* Local AknLayout definintions.
*/
enum TAknLayoutFlags
    {
    EAknLayoutCbaInControlPane     = 0x1,
    EAknLayoutCbaInStaconPane      = 0x2,
    EAknLayoutCbaInStaconPaneRight = 0x4,
    EAknLayoutCbaInStaconPaneLeft  = 0x8,
    EAknLayoutCbaInStaconPaneIdle  = 0x10,
    EAknLayoutCbaInRightPane       = 0x20
    };

/**
* Enumeration for CEikCommandTable for fetching commands.
*/
enum TCommandTableCbaPositions
    {
    ECommandTableCommand1Posn = 0,
    ECommandTableCommand2Posn = 1,
    ECommandTableCommand3Posn = 2,
    ECommandTableCommand4Posn = 3
    };

enum TCbaChangeRecordedFlags
    {
    ECbaChangeRecordedLayout,
    ECbaChangeRecordedSkin,
    ECbaChangeRecordedColor,
    ECbaInsideDialog,
    ECbaEmbedded,       // cba is embedded in a parent control (dialog or popup)
    ECbaHasContent,     // cba has content and should be visible when embedded
    ECbaParentAsControl, // cba's parent window group is treated as CCoeControl
    ECbaActivationDelayed, // activation delayed
    ECbaSingleClickEnabled, // single click enabled in appUi
    ECbaItemSoftkeyDisabled, // item specific softkey disabled
    ECbaItemSpecificSoftkeyInUse, // item specific softkey is in use
    ECbaItemSoftkeyDisabledByClient // client has disabled item specific softkey
    };

enum TCbaLayers
    {
    ECbaLayerWallpaper,
    ECbaLayerBackground,
    ECbaLayerN
    };

/**
* Local panic routine.
*/
#if defined(_DEBUG)
LOCAL_C void Panic(TEikPanicCBA aPanic)
    {
    _LIT(KPanicCat,"CBA");
    User::Panic(KPanicCat, aPanic);
    }
#endif


/** 
* Internal extension class.
*/
class CEikCbaExtension : public CBase,
                         public MCenRepNotifyHandlerCallback,
                         public MAknCollectionObserver
    {
public:

    CEikCbaExtension( CEikCba& aOwner ) : iOwner( aOwner ), 
                                          iCbaBgIIDSetExt( EFalse )
                                          ,iLeftFrameMask( NULL ),
                                          iRightFrameMask( NULL ),
                                          iItemActionMenu( NULL )
        {
        };
    
    static CEikCbaExtension* NewL( CEikCba& aOwner )
        {
        CEikCbaExtension* self = new (ELeave) CEikCbaExtension( aOwner );
        CleanupStack::PushL( self );
        self->ConstructL();
        CleanupStack::Pop( self );
        return self;
        }
    
    void ConstructL() 
        {
        // Wallpaper is not drawn by embedded CBA.
        if ( !iOwner.Flags().IsSet( ECbaEmbedded ) )
            {
            iRepository = CRepository::NewL( KCRUidPersonalisation );
            iRepository->Get( KPslnWallpaperType, iWallpaperInUse );
        
            iCRListener = CCenRepNotifyHandler::NewL( *this,
                                                  *iRepository,
                                                  CCenRepNotifyHandler::EIntKey,
                                                  KPslnWallpaperType );
            iCRListener->StartListeningL();
            }
        
        iBackgroundMaskID = KAknsIIDNone;
        iCbaRect = TRect( 0,0,0,0 );
        iIfSkinChanged = EFalse;
        iIfMskIconSet = EFalse;
        iSemiBgID = KAknsIIDNone;

        if ( iOwner.Flags().IsSet( ECbaSingleClickEnabled ) )
            {
            AknItemActionMenuRegister::RegisterCollectionObserverL(
                    *this );
            }
        }
    
    ~CEikCbaExtension() 
        {
        if ( iOwner.Flags().IsSet( ECbaSingleClickEnabled ) )
            {
            AknItemActionMenuRegister::UnregisterCollectionObserver( *this );
            }
        if ( iCRListener )
            {
            iCRListener->StopListening();
            delete iCRListener;
            }

        delete iRepository;
        delete iPressedMSKFrameBitmap;
        delete iLeftFrameMask;
        delete iRightFrameMask;    
        delete iLskPostingOverlayBitmap;
        delete iRskPostingOverlayBitmap;
        delete iBmpFile;
        }
    
    /** From base class MCenRepNotifyHandlerCallback */
    void HandleNotifyInt( TUint32 /*aId*/, TInt aNewValue )
        {
        iWallpaperInUse = aNewValue;
        iOwner.SetSkinBackgroundId( KAknsIIDNone );
        }
        
    void UpdateSoftkeyFrameL( TBool aForcedUpdate )
        {
        if ( !AknLayoutUtils::PenEnabled() )
            {
            return;
            }
        TAknLayoutRect cbarect;
        
        TRect screen;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screen );
        
        TAknWindowComponentLayout applicationWindow(
            AknLayoutScalable_Avkon::application_window( 0 ) );
            
        TRect innerRect;
        TRect outerRect;
        TRect mskOuterRect;
        TRect mskInnerRect;

        if ( iOwner.Flags().IsSet( ECbaEmbedded ) )
            {
            TRect rect ( iOwner.Rect() );
            if ( rect.Width() > 0 && rect.Height() > 0 )
                {
                TAknLayoutRect layoutRect;
                layoutRect.LayoutRect(
                        rect, 
                        AknLayoutScalable_Avkon::popup_sk_window_g1( 0 ) );                    

                TInt margin = layoutRect.Rect().iTl.iX - rect.iTl.iX;
                TInt buttonWidth = ( rect.Width() - margin * 2 ) / 2;
                outerRect = TRect( 0, 0, buttonWidth, 
                                   layoutRect.Rect().Height() );
                    
                layoutRect.LayoutRect( outerRect,
                     AknLayoutScalable_Avkon::bg_sctrl_sk_pane_g1()
                        .LayoutLine() );
                innerRect = layoutRect.Rect();

                MAknsSkinInstance* skin = AknsUtils::SkinInstance();

                const TSize maskSize = outerRect.Size();
                if (skin && ( aForcedUpdate || IsBitmapUpdateNeeded( iLeftFrameMask, maskSize )
                    || IsBitmapUpdateNeeded( iRightFrameMask, maskSize ) ) )
                    {
                    delete iLeftFrameMask;
                    iLeftFrameMask = NULL;
                    delete iRightFrameMask;
                    iRightFrameMask = NULL;
                    }
                }
            }
        else
            {
            TBool rightPaneActive( IsAreaSideRightPaneActive() );
            
            TBool bskLandscape( Layout_Meta_Data::IsLandscapeOrientation() &&
                                !rightPaneActive );
    
            if ( rightPaneActive )
                {
                cbarect.LayoutRect(
                    screen,
                    DoCompose(
                        applicationWindow,
                        AknLayoutScalable_Avkon::area_side_right_pane( 0 ) ).LayoutLine() );
                }
            else
                {            
                cbarect.LayoutRect(
                    screen,
                    DoCompose(
                        applicationWindow,
                        DoCompose(
                            AknLayoutScalable_Avkon::area_bottom_pane( bskLandscape ? 2 : 1 ),
                            AknLayoutScalable_Avkon::control_pane() ) ).LayoutLine() );
                }
                
            TRect cbaRect( cbarect.Rect() );

            TBool mskEnabled( IsMskEnabledLayoutActive() );

            TAknWindowComponentLayout frameLayout;
            if ( rightPaneActive )
                {
                frameLayout = AknLayoutScalable_Avkon::sctrl_sk_top_pane();
                }
            else if ( bskLandscape || mskEnabled )
                {
                frameLayout = AknLayoutScalable_Avkon::control_pane_g6( 0 );
                }
            else
                {
                frameLayout = AknLayoutScalable_Avkon::bg_sctrl_sk_pane_cp1();
                }

            cbarect.LayoutRect( cbaRect, frameLayout );

            outerRect.SetRect( TPoint( 0, 0 ), cbarect.Rect().Size() );
            
            if ( mskEnabled )
                {
                cbarect.LayoutRect(
                    cbaRect,
                    AknLayoutScalable_Avkon::control_pane_g7( 0 ) );
                
                mskOuterRect.SetRect( TPoint( 0, 0 ), cbarect.Rect().Size() );
                }
            else
                {
                
                iUpdateMSKFrameOuterRect.SetRect( 0, 0, 0, 0 );
                }
    
            TAknLayoutRect layoutRect;
            layoutRect.LayoutRect(
                outerRect,
                AknLayoutScalable_Avkon::bg_sctrl_sk_pane_g1().LayoutLine() );
            innerRect = layoutRect.Rect();
            if ( mskEnabled )
                {
                layoutRect.LayoutRect(
                    mskOuterRect,
                    AknLayoutScalable_Avkon::bg_sctrl_sk_pane_g1() );
                mskInnerRect = layoutRect.Rect();
                }
            }

        
        iUpdateFrameOuterRect = outerRect;
        iUpdateFrameInnerRect = innerRect;
        iUpdateMSKFrameOuterRect = mskOuterRect;
        iUpdateMskFrameInnerRect = mskInnerRect;
        }




    /**
     * Merges mask into color bitmap.
     * @internal
     * @since S60 v5.0
     * @param aMask mask to be merged.
     * @param aDestBitmap bitmap to merge mask with.
     */
    static void MergeMaskInto16MA( CFbsBitmap* aMask, CFbsBitmap* aDestBitmap )
        {
        // aMask display mode must be EGray256.
        // aMask must not be compressed in RAM.
        // aDestBitmap display mode must be EColor16MA.
        // aDestBitmap must not be compressed in RAM.
        // aMask size must equal to aDestBitmap size.
        // See UpdatePostingOverlayBitmapL.

        TSize size = aMask->SizeInPixels();
        TUint32 pitch = CFbsBitmap::ScanLineLength( size.iWidth, EGray256 );
        TUint32 destPitch = CFbsBitmap::ScanLineLength( size.iWidth, EColor16MA ) / 4;
        aMask->LockHeap();
        aDestBitmap->LockHeap();
        TUint8* dataAddr = 
            reinterpret_cast<TUint8*>( aMask->DataAddress() );
        TUint32* destAddr = 
            reinterpret_cast<TUint32*>( aDestBitmap->DataAddress() );
        
        for ( TUint32 y = 0; y < size.iHeight; y++ )
            {
            for ( TUint32 x = 0; x < size.iWidth; x++ )
                {
                TUint8 value = (TUint8)dataAddr[ y * pitch + x ];
                // Round mask value to fully opaque or transparent
                if ( value > 0x7f )
                    {
                    // Opaque pixel.
                    destAddr[ y * destPitch + x ] |= KAknCbaOpaqueMask;
                    }
                else
                    {
                    // Transparent pixel
                    destAddr[ y * destPitch + x ] = KAknCbaColorKey;
                    }
                }
            }
        aDestBitmap->UnlockHeap();
        aMask->UnlockHeap();
        }

    /**
     * Updates posting overlay bitmap.
     * @internal
     * @since S60 v5.0
     * @param aBitmap Reference to bitmap pointer to get the new bitmap.
     * @param aRect Rectangle for the CBA button.
     * @param aControl CEikCba control.
     * @param aButton CEikCbaButton control for the button.
     */
    void UpdatePostingOverlayBitmapL(
            CFbsBitmap*& aBitmap,
            const TRect& aRect,
            CEikCbaButton* aButton )
        {
        delete aBitmap;
        aBitmap = NULL;

        // If you modify this method, please make sure that assumptions
        // mentioned in MergeMaskInto16MA still hold.

        CFbsBitmap* bitmap = new ( ELeave ) CFbsBitmap();
        CleanupStack::PushL( bitmap );
        User::LeaveIfError( bitmap->Create( aRect.Size(), EColor16MA ) );

        CFbsBitGc* bitmapContext = NULL;
        CFbsBitmapDevice* bitmapDevice =
            CFbsBitmapDevice::NewL( bitmap );
        CleanupStack::PushL( bitmapDevice );
        User::LeaveIfError( bitmapDevice->CreateContext( bitmapContext ) );
        CleanupStack::PushL( bitmapContext );

        // Zero alpha channel to make bitmap fully transparent
        bitmapContext->SetDrawMode( CGraphicsContext::EDrawModeWriteAlpha );
        bitmapContext->SetBrushColor( TRgb::Color16MA( 0 ) );
        bitmapContext->Clear();

        // Draw button text into bitmap
        if ( aButton )
            {
            CFbsBitmap* textBitmapMask = new ( ELeave ) CFbsBitmap();
            CleanupStack::PushL( textBitmapMask );
            User::LeaveIfError( textBitmapMask->Create( aRect.Size(), EGray256 ) );

            CFbsBitmapDevice* device = CFbsBitmapDevice::NewL( textBitmapMask );
            CleanupStack::PushL( device );
            CFbsBitGc* gc  = NULL;
            User::LeaveIfError( device->CreateContext( gc ) );
            CleanupStack::PushL( gc );

            // Clear bitmap
            gc->SetBrushColor( KRgbBlack );
            gc->Clear();

            aButton->DrawToContext( *bitmapContext, *gc, aRect.iTl );

            CleanupStack::PopAndDestroy( gc );
            CleanupStack::PopAndDestroy( device );

            // Merge text mask into the alpha channel to make the text fully opaque
            MergeMaskInto16MA( textBitmapMask, bitmap );

            CleanupStack::PopAndDestroy( textBitmapMask );
            }

        CleanupStack::PopAndDestroy( 2, bitmapDevice );
        CleanupStack::Pop( bitmap );
        aBitmap = bitmap;
        }
    
    /**
     * Updates posting overlay bitmaps.
     * @param aCbaRect cba rect.
     * @param aLeftButton left button.
     * @param aRightButton right button.
     */
    void UpdatePostingOverlayBitmapsL(
            const TRect& aCbaRect,
            CEikCbaButton* aLeftButton,
            CEikCbaButton* aRightButton,
            TInt aAknLayoutFlags )
        {
        TRect rightSoftKeyButtonRect;
        TRect leftSoftKeyButtonRect;
        if( aAknLayoutFlags & EAknLayoutCbaInRightPane )
            {
        // Read right (top in landscape) softkey layout.      
        TAknWindowLineLayout rightSoftkeyLayout(
            DoCompose( AknLayoutScalable_Avkon::area_side_right_pane( 0 ),
                       AknLayoutScalable_Avkon::sctrl_sk_top_pane() ).LayoutLine() );

        TAknLayoutRect rightSoftkeyLayoutRect;
        rightSoftkeyLayoutRect.LayoutRect( aCbaRect, rightSoftkeyLayout );
            rightSoftKeyButtonRect = rightSoftkeyLayoutRect.Rect() ;

        // Read left (bottom in landscape) softkey layout.       
        TAknWindowLineLayout leftSoftkeyLayout( 
            DoCompose( AknLayoutScalable_Avkon::area_side_right_pane( 0 ),
                       AknLayoutScalable_Avkon::sctrl_sk_bottom_pane() ).LayoutLine() );

        TAknLayoutRect leftSoftkeyLayoutRect;
        leftSoftkeyLayoutRect.LayoutRect( aCbaRect, leftSoftkeyLayout );
            leftSoftKeyButtonRect = leftSoftkeyLayoutRect.Rect() ;
            }
        else if( aAknLayoutFlags & EAknLayoutCbaInControlPane )
            {
            TAknLayoutRect layoutRect;
            TRect rect( 0,0,0,0 );
            if ( AknLayoutUtils::LayoutMirrored() )
                {
                layoutRect.LayoutRect(
                    rect,
                    AknLayoutScalable_Avkon::aid_touch_ctrl_right().LayoutLine() );
                leftSoftKeyButtonRect = layoutRect.Rect();

                layoutRect.LayoutRect(
                    rect,
                    AknLayoutScalable_Avkon::aid_touch_ctrl_left().LayoutLine() );
                rightSoftKeyButtonRect = layoutRect.Rect();
                }
            else
                {
                layoutRect.LayoutRect(
                    rect,
                    AknLayoutScalable_Avkon::aid_touch_ctrl_left().LayoutLine() );
                leftSoftKeyButtonRect = layoutRect.Rect();

                layoutRect.LayoutRect(
                    rect,
                    AknLayoutScalable_Avkon::aid_touch_ctrl_right().LayoutLine() );
                rightSoftKeyButtonRect = layoutRect.Rect();
                }
            }
        else
            {
            TInt variety = 0;
            if ( aAknLayoutFlags & EAknLayoutCbaInStaconPaneLeft )
                {
                variety = 1;
                }

            TAknWindowComponentLayout layout0;
            TAknWindowComponentLayout layout1;
            TAknWindowComponentLayout layout2;

            // Read right (top in landscape) softkey layout.
            layout0 = AknLayoutScalable_Avkon::area_top_pane( 2 );
            layout1 = AknLayoutScalable_Avkon::stacon_top_pane();

            // If clock is shown in stacon, cba area is smaller.
            TInt topCbaVariety = variety;
            if ( AknStatuspaneUtils::ExtendedStaconPaneActive() )
                {
                topCbaVariety += 4;
                }

            layout2 = AknLayoutScalable_Avkon::control_top_pane_stacon( topCbaVariety );

            TAknWindowLineLayout rightSoftkeyLayout(
                DoCompose( layout0,DoCompose( layout1, layout2 ) ).LayoutLine() );

            TAknLayoutRect rightSoftkeyLayoutRect;
            rightSoftkeyLayoutRect.LayoutRect( aCbaRect, rightSoftkeyLayout );
            rightSoftKeyButtonRect = rightSoftkeyLayoutRect.Rect();

            // Read left (bottom in landscape) softkey layout.
            layout0 = AknLayoutScalable_Avkon::area_bottom_pane( 2 );
            layout1 = AknLayoutScalable_Avkon::stacon_bottom_pane();

            // If clock is shown in stacon, cba area is smaller.
            TInt bottomCbaVariety = variety;
            if ( AknStatuspaneUtils::ExtendedStaconPaneActive() )
                {
                bottomCbaVariety += 2;
                }

            layout2 = AknLayoutScalable_Avkon::control_bottom_pane_stacon(
                    bottomCbaVariety );

            TAknWindowLineLayout leftSoftkeyLayout(
                DoCompose( layout0, DoCompose( layout1, layout2 ) ).LayoutLine() );

            TAknLayoutRect leftSoftkeyLayoutRect;
            leftSoftkeyLayoutRect.LayoutRect( aCbaRect, leftSoftkeyLayout );
            leftSoftKeyButtonRect = leftSoftkeyLayoutRect.Rect();
            }
        UpdatePostingOverlayBitmapL(
                iLskPostingOverlayBitmap,
                leftSoftKeyButtonRect,
                aLeftButton );
        UpdatePostingOverlayBitmapL(
                iRskPostingOverlayBitmap,
                rightSoftKeyButtonRect,
                aRightButton );
        }

    /**
     * From MAknCollectionObserver.
     * This method is used to set the item action menu to observer.
     * 
     * @param aItemActionMenu Item action menu. 
     */
    void SetItemActionMenu( CAknItemActionMenu* aItemActionMenu )
        {
        iItemActionMenu = aItemActionMenu;
        }

    /**
     * From MAknCollectionObserver.
     * This method is called when there are changes in collection state.
     * LSK should be hidden when there is no highlight in list.
     * 
     * @param aCollectionVisible ETrue if changed collection is visible.
     */
    void CollectionChanged( TBool aCollectionVisible )
        {
        // Do not update state if invisible collection tries to enable sk
        if ( aCollectionVisible
                || iOwner.Flags().IsClear( ECbaItemSoftkeyDisabled ) )
            {
            iOwner.UpdateItemSpecificSoftkey();
            }
        }

    /**
     * From MAknCollectionObserver.
     * This method returns ETrue if collection observer is active.
     * 
     * @return ETrue if observer is active.
     */
    TBool Active() const
        {
        return iOwner.IsVisible() && !iOwner.IsEmpty();
        }
    
    /*
     * Using the special theme Id draw background
     */
    void DrawSemiTransparencyL(CWindowGc& aGc, 
            const TRect& aRect)
    	{
    	//Temporary inner rectangal value
    	TRect innerRect = aRect;
    	innerRect.Shrink( 5, 5 );
    	if ( iSemiBgID != KAknsIIDNone )
	        {
	        AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(), 
	            aGc, aRect, innerRect, iSemiBgID, iSemiBgCenterID );
	        }
    	}

public:
    
    CEikCba&               iOwner;
    CRepository*           iRepository;
    CCenRepNotifyHandler*  iCRListener;
    TInt                   iWallpaperInUse;
    CFbsBitmap*            iFrameBitmap;
    CFbsBitmap*            iPressedFrameBitmap;        
    CFbsBitmap*            iMSKFrameBitmap;
    CFbsBitmap*            iPressedMSKFrameBitmap;
    CFbsBitmap*            iLskPostingOverlayBitmap;
    CFbsBitmap*            iRskPostingOverlayBitmap;
    TBool                  iEnablePostingTransparency;
    
    TBool                  iCbaBgIIDSetExt;
    TBool                  iIfSkinChanged;
    
    CFbsBitmap*            iLeftFrameMask;
    CFbsBitmap*            iRightFrameMask;
    
    TAknsItemID iBackgroundMaskID;
    TRect iCbaRect;
    TBool                  iIfMskIconSet;
    TAknsItemID            iMSKSkinID;
    HBufC*                 iBmpFile;
    TInt32                 iBmp;
    TInt32                 iBmpM;
    /**
    * Pointer to the CBA button which currently has the pointer grab.
    * Not own. 
    */
    CCoeControl*           iPointerGrabbingButton;
    
    /** Rectangle in which the left (or bottom) softkey frame is drawn to. */
    TRect                  iLeftFrameOuterRect;
    TRect                  iLeftFrameInnerRect;
    
    /** Rectangle in which the right (or top) softkey frame is drawn to. */
    TRect                  iRightFrameOuterRect;
    TRect                  iRightFrameInnerRect;
    
    /** Rectangle in which the middle softkey frame is drawn to if used. */
    TRect                  iMiddleFrameOuterRect;
    TRect                  iMiddleFrameInnerRect;

    /**
     * Content observer.
     */
    TCallBack iContentObserver;
    
    /**
     * Outer rect used in UpdateSoftkeyFrameL method.
     */
    TRect iUpdateFrameOuterRect;
    
    /*
     * Frame and center theme ID, using for semi-transparent  
     */
    TAknsItemID            iSemiBgID;
    TAknsItemID	           iSemiBgCenterID;
    /**
     * Inner rect used in UpdateSoftkeyFrameL method.
     */
    TRect iUpdateFrameInnerRect;

    /**
     * Outer MSK rect used in UpdateSoftkeyFrameL method.
     */
    TRect iUpdateMSKFrameOuterRect;
    /*
    *
    */
    TRect iUpdateMskFrameInnerRect;

    /**
     * Item action menu.
     * Not own.
     */
    CAknItemActionMenu* iItemActionMenu;
    };


CEikCba* CEikCba::NewL(const CEikCba* aPrevious, MEikCommandObserver* aCommandObserver, 
    RWindowGroup* aParentWg)
    { 
    CEikCba* self = CEikCba::NewLC(aPrevious, aCommandObserver, aParentWg); // static
    CleanupStack::Pop( self );
    return self;
    }

CEikCba* CEikCba::NewL(TInt aResourceId, const CEikCba* aPrevious, 
    MEikCommandObserver* aCommandObserver, RWindowGroup* aParentWg)
    { 
    CEikCba* self = CEikCba::NewLC(aResourceId, aPrevious, aCommandObserver, aParentWg); // static
    CleanupStack::Pop( self );
    return self;
    }

CEikCba* CEikCba::NewLC(const CEikCba* aPrevious, MEikCommandObserver* aCommandObserver, 
    RWindowGroup* aParentWg)
    {
    return CEikCba::NewLC(KNoResource, aPrevious, aCommandObserver, aParentWg); // static
    }

CEikCba* CEikCba::NewLC(const CEikCba* aPrevious,
    MEikCommandObserver* aCommandObserver, RWindowGroup* aParentWg,
    TUint aFlags)
    {
    return CEikCba::NewLC(KNoResource, aPrevious, aCommandObserver,
        aParentWg, aFlags);
    }

CEikCba* CEikCba::NewLC(TInt aResourceId, const CEikCba* aPrevious,
    MEikCommandObserver* aCommandObserver, RWindowGroup* aParentWg)
    { 
    CEikCba* self = new(ELeave) CEikCba(aPrevious, aCommandObserver, aParentWg); // static
    CleanupStack::PushL(self);
    self->ConstructL(aResourceId);
    AKNTASHOOK_ADDL( self, "CEikCba" );
    return self;
    }

CEikCba* CEikCba::NewLC(TInt aResourceId, const CEikCba* aPrevious,
    MEikCommandObserver* aCommandObserver, RWindowGroup* aParentWg,
    TUint aFlags)
    {
    CEikCba* self = new(ELeave) CEikCba(aPrevious, aCommandObserver,
        aParentWg, aFlags);
    CleanupStack::PushL(self);
    self->ConstructL(aResourceId);
    AKNTASHOOK_ADDL( self, "CEikCba" );
    return self;
    }


/**
* Destructor.
*/
CEikCba::~CEikCba()
    {
    AKNTASHOOK_REMOVE();
    // Revert the clock and indicator pane area of status pane
    // to use the previous skin background.
    CEikStatusPaneBase* sp = CEikStatusPaneBase::Current();
    if ( sp &&
         iClockIndicBgIID.iMajor &&
         iClockIndicBgIID.iMinor &&
         iIsClockIndicBgIIDSet )
        {
        sp->SetCbaAreaBackgroundID( iClockIndicBgIID,
                                    CEikStatusPaneBase::EDrawDeferred );
        }
        
    AknsUtils::DeregisterControlPosition( this );    
    
    // Remove scroll bar from control array to prevent double deletion
    // but only if has been properly constructed.
    if (iControlArray)
        {
        if (iControlArray->Count() > KControlArrayScrollBarPosn)
            {
            iControlArray->Delete(KControlArrayScrollBarPosn);
            }
        }
        
    if(iEikonEnv && iEikonEnv->EikAppUi())
        {
        iEikonEnv->EikAppUi()->RemoveFromStack(this);
        }
        
    // Don't release font, as we are using layout utils to use SAME font every time.
    
    delete iBrushAndPenContext;
    delete iSBFrame;

    delete iMLBgContext;
    delete iStaconBgContextTop;
    delete iStaconBgContextBottom;

#ifdef RD_ENHANCED_CBA         
     delete iCommandTable;              
#endif // RD_ENHANCED_CBA

    delete iExtension;
    }

/**
* Constructor.
*/
CEikCba::CEikCba(const CEikCba* aPrevious,
    MEikCommandObserver* aCommandObserver, RWindowGroup* aParentWg,
    TUint aFlags)
    : iLink(aPrevious), iCommandObserver(aCommandObserver), iParentWg(aParentWg)
    {
    if (aFlags & CEikButtonGroupContainer::EIsEmbedded)
        {
        // CBA is embedded in another component (eg. dialog/popup/setting page
        iFlags.Set(ECbaEmbedded);
        }

    if ( aFlags & CEikButtonGroupContainer::EParentIsControl )
        {
        iFlags.Set( ECbaParentAsControl );
        }
    
	if ( aFlags & CEikButtonGroupContainer::EDelayActivation )
        {
        iFlags.Set( ECbaActivationDelayed );
        }    

    CAknAppUi* appUi = static_cast<CAknAppUi*>( iCoeEnv->AppUi() );
    if ( appUi && appUi->IsSingleClickCompatible() )
        {
        iFlags.Set( ECbaSingleClickEnabled );
        iFlags.Set( ECbaItemSpecificSoftkeyInUse );
        }

    SetNonFocusing();
    }


void CEikCba::SetContainerWindowL( const CCoeControl& aContainer )
    {
    // CCoeControl::SetContainerWindowL closes the previously own window and
    // deactivates control. Therefore store the activation status and re-set
    // it after the container window has been set.
    
    // Removed to enable drawing of Query Input in one phase 
    //TBool wasActivated = IsActivated();
    // Check that this method was called from CAknQueryControl. Otherwise just
    // bail out so that previous functionality (i.e. the one before SetContainerWindowL
    // was overridded) is preserved.
    CAknQueryControl* queryControl;
    
    queryControl = const_cast<CCoeControl&>( aContainer ).MopGetObject( queryControl );
    
    if ( queryControl == &aContainer )
        {
        CCoeControl::SetContainerWindowL( aContainer );

        // Convert all CEikCbaButtons to CAknButtons
        iFlags.Set( ECbaInsideDialog );

        TAknTextComponentLayout layout = AknLayoutScalable_Apps::cell_vitu2_itu_pane_t1( 0 );
        TAknLayoutText layoutText;
        layoutText.LayoutText(Rect(), layout.LayoutLine() );

        CCoeControl *leftSoftkey = (*iControlArray)[KControlArrayCBAButton1Posn].iControl;
        CCoeControl *rightSoftkey = (*iControlArray)[KControlArrayCBAButton2Posn].iControl;
        
        TInt leftCommandId( (*iControlArray)[KControlArrayCBAButton1Posn].iId );
        TInt rightCommandId( (*iControlArray)[KControlArrayCBAButton2Posn].iId );
        
        TRgb color = layoutText.Color();
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
           
        AknsUtils::GetCachedColor( skin, color, KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG65 );
         
         
        CAknButton* button = CAknButton::NewL();
        button->SetObserver( this );
        
        
        switch ( AknLayoutScalable_Apps::area_vitu2_query_pane_t1( 0 ).J() )
            {
            case ELayoutAlignRight:
                {
                button->SetTextHorizontalAlignment( CGraphicsContext::ERight );
                break;
                }
                
            case ELayoutAlignLeft:
                {
                button->SetTextHorizontalAlignment( CGraphicsContext::ELeft );
                break;
                }
                
            case ELayoutAlignCenter:
            default:
                {
                button->SetTextHorizontalAlignment( CGraphicsContext::ECenter );
                break;
                }
            }

        if ( !static_cast<CEikCbaButton*>( leftSoftkey )->IsImageOn() )
            {
            CEikLabel* label = static_cast<CEikLabel*>( leftSoftkey->ComponentControl( 0 ) );
            
            const TDesC* text = label->Text();
            button->AddStateL( NULL, NULL, NULL, NULL, *text, KNullDesC, 0, leftCommandId );
            
            if ( text->Length() == 0 || !text->Compare( _L(" ") ) )
                {
                button->SetDimmed( ETrue );
                }
            }

        button->OverrideColorL( EColorButtonText, color );
        button->OverrideColorL( EColorButtonTextPressed, color );
        button->OverrideColorL( EColorButtonTextDimmed, color );
        
        button->SetBackgroundIds( KAknsIIDQsnFrFunctionButtonNormal,
            KAknsIIDQsnFrFunctionButtonPressed, KAknsIIDQsnFrFunctionButtonInactive,
            KAknsIIDQsnFrFunctionButtonPressed, KAknsIIDQsnFrFunctionButtonInactive );
            
            
        delete leftSoftkey;
        (*iControlArray)[KControlArrayCBAButton1Posn].iControl = button;
        
        button = CAknButton::NewL();
        button->SetObserver( this );
        
        
        switch ( AknLayoutScalable_Apps::area_vitu2_query_pane_t2( 0 ).J() )
            {
            case ELayoutAlignRight:
                {
                button->SetTextHorizontalAlignment( CGraphicsContext::ERight );
                break;
                }
                
            case ELayoutAlignLeft:
                {
                button->SetTextHorizontalAlignment( CGraphicsContext::ELeft );
                break;
                }
                
            case ELayoutAlignCenter:
            default:
                {
                button->SetTextHorizontalAlignment( CGraphicsContext::ECenter );
                break;
                }
            }
        
        if ( !static_cast<CEikCbaButton*>( rightSoftkey )->IsImageOn() )
            {
            CEikLabel* label = static_cast<CEikLabel*>( rightSoftkey->ComponentControl( 0 ) );
            
            const TDesC* text = label->Text();
            button->AddStateL( NULL, NULL, NULL, NULL, *text, KNullDesC, 0, rightCommandId );
            
            if ( text->Length() == 0 || !text->Compare( _L(" ") ) )
                {
                button->SetDimmed( ETrue );
                }
            }

        button->OverrideColorL( EColorButtonText, color );
        button->OverrideColorL( EColorButtonTextPressed, color );
        button->OverrideColorL( EColorButtonTextDimmed, color );
        
        button->SetBackgroundIds( KAknsIIDQsnFrFunctionButtonNormal,
            KAknsIIDQsnFrFunctionButtonPressed, KAknsIIDQsnFrFunctionButtonInactive,
            KAknsIIDQsnFrFunctionButtonPressed, KAknsIIDQsnFrFunctionButtonInactive );
            
        delete rightSoftkey;
        (*iControlArray)[KControlArrayCBAButton2Posn].iControl = button;

        // CCoeControl::ComponentControl can't be used since base class CEikControlGroup
        // doesn't necessarily return all child controls.
        for ( TInt i = 0; i < iControlArray->Count(); ++i )
            {
            if ( (*iControlArray)[i].iControl )
                {
                (*iControlArray)[i].iControl->SetContainerWindowL( *this );
                }
            }
        }
        
    else if ( iFlags.IsSet( ECbaEmbedded ) && 
            !iFlags.IsSet( ECbaParentAsControl ) )
        {
        if ( OwnsWindow() )
            {
            CloseWindow();
            }
            
        CreateWindowL( &aContainer );
        EnableWindowTransparency();

        RWindow& window = Window();
        window.SetPointerGrab(ETrue);
        EnableDragEvents();
        window.SetShadowDisabled(ETrue);
        
        TBool isEmpty = IsEmpty();

        if ( !isEmpty && !iFlags.IsSet( ECbaHasContent ) )
            {
            iFlags.Set( ECbaHasContent );
            }

        for ( TInt i = 0; i < iControlArray->Count(); ++i )
            {
            if ( (*iControlArray)[i].iControl )
                {
                (*iControlArray)[i].iControl->SetContainerWindowL( *this );
                }
            }
        }
    else
        {
        CCoeControl::SetContainerWindowL( aContainer );            
        }        
    }

void CEikCba::ActivateL()
    {
    CCoeControl::ActivateL();
    }
    
void CEikCba::BaseConstructL()
    {
    if ( iFlags.IsSet( ECbaEmbedded ) && iFlags.IsSet( ECbaParentAsControl ) )
        {
        __ASSERT_DEBUG( iParentWg, User::Invariant() );
        CreateWindowL( (CCoeControl*)iParentWg );
        EnableWindowTransparency();
        iParentWg = NULL;
        iCbaFlags &= ~EEikCbaFlagTransparent;
        }
    else
        {
        CreateWindowL( iParentWg );

        if ( ( ( iCbaFlags & EEikCbaFlagTransparent ) ||
                iCbaFlags & EEikCbaFlagSemiTransparent ) &&
                  CAknEnv::Static()->TransparencyEnabled() )
            {
            Window().SetRequiredDisplayMode( EColor16MA ); // Without this, ACT does not work in all cases in HW
            TInt err = Window().SetTransparencyAlphaChannel();

            if ( err == KErrNone )
                {
                // Set the window initially completely transparent. This needs to be called only once.
                Window().SetBackgroundColor(~0);
                }
            else
                {
                // SetTransparencyAlphaChannel returned an error.
                // Revert back to non-transparent CBA.
                iCbaFlags &= ~EEikCbaFlagTransparent;
                }
            }
        else
            {
            // Transparency not supported or not enabled
            iCbaFlags &= ~EEikCbaFlagTransparent;
            }
        }

    iExtension = CEikCbaExtension::NewL( *this );
    //create bitmap for semi-transparent background
    if ( iCbaFlags & EEikCbaFlagSemiTransparent && iExtension )
        {
        iExtension->iSemiBgID = KAknsIIDQsnHomeBgWidget;
        iExtension->iSemiBgCenterID = KAknsIIDQsnHomeBgWidgetCenter;
        }

    // Skin background is not drawn by embedded CBA.
    if ( !iFlags.IsSet( ECbaEmbedded ) )
        {
        TRect screen;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screen );

        // Construct background control context, SizeChanged will update
        // the layout rectangle.
        iBgIID = AknStatuspaneUtils::IdleLayoutActive() ?
            KAknsIIDQsnBgAreaControlIdle :
            KAknsIIDQsnBgAreaControl;
    
        iMLBgContext = CAknsMaskedLayerBackgroundControlContext::NewL(
            KAknsIIDWallpaper,
            TRect( 0, 0, 1, 1 ),
            ETrue,
            2 );

        // Other context for staconpane

        // There is a need for two layers in each context: one for wallpaper, 
        // the other for skin graphics.
        iStaconBgContextTop = CAknsMaskedLayerBackgroundControlContext::NewL(
            KAknsIIDWallpaper, TRect( 0, 0, 1, 1 ), ETrue, ECbaLayerN );
        iStaconBgContextBottom = CAknsMaskedLayerBackgroundControlContext::NewL(
            KAknsIIDWallpaper, TRect( 0, 0, 1, 1 ), ETrue, ECbaLayerN );
            
        for ( TInt i = 0; i < ECbaLayerN; i++ )
            {
            iStaconBgContextBottom->SetLayerImage( i, KAknsIIDNone );
            }
        
        TAknWindowLineLayout layout( AknLayoutScalable_Avkon::area_top_pane(2).LayoutLine() );
        TAknLayoutRect layoutRect;
        layoutRect.LayoutRect( screen, layout );
        TRect staconTop( layoutRect.Rect() );
    
        layout = AknLayoutScalable_Avkon::area_bottom_pane(2).LayoutLine();
        layoutRect.LayoutRect( screen, layout );        
        TRect staconBottom( layoutRect.Rect() );
    
        // Set layers to stacon contexts.
        // Set bottom as parent to top, so that top is re-drawn, if bottom is drawn.
        iStaconBgContextTop->SetLayerImage( ECbaLayerWallpaper, KAknsIIDWallpaper );
        iStaconBgContextTop->SetLayerRect( ECbaLayerWallpaper, screen );
        iStaconBgContextTop->SetLayerImage( ECbaLayerBackground, KAknsIIDQsnBgAreaStaconRt );
        iStaconBgContextTop->SetLayerRect( ECbaLayerBackground, staconTop );
    
        iStaconBgContextBottom->SetLayerImage( ECbaLayerWallpaper, KAknsIIDWallpaper );
        iStaconBgContextBottom->SetLayerRect( ECbaLayerWallpaper, screen );
        iStaconBgContextBottom->SetLayerImage( ECbaLayerBackground, KAknsIIDQsnBgAreaStaconRb );
        iStaconBgContextBottom->SetLayerRect( ECbaLayerBackground, staconBottom );
        iStaconBgContextBottom->SetParentPos( TPoint( 0, 0 ) );
    
        iStaconBgContextTop->SetParentContext( iStaconBgContextBottom );
    
        TBool idle = AknLayoutFlags() & EAknLayoutCbaInStaconPaneIdle;
        if ( idle )
            {
            iStaconBgContextTop->SetLayerMaskAndSizeL( KAknsIIDQgnGrafBgLscTopMaskIcon, staconTop );
            iStaconBgContextBottom->SetLayerMaskAndSizeL( KAknsIIDQgnGrafBgLscBottomMaskIcon, staconBottom );
            }

        }

    iExtension->UpdateSoftkeyFrameL( EFalse );
    
    CRepository* cenRep = NULL;
    TRAPD(err, cenRep = CRepository::NewL( KCRUidAvkon ));
    if (!err)
        {
        err = cenRep->Get( KAknMiddleSoftkeyEnabled, iMSKEnabledInPlatform );
        delete cenRep;
        }

    RWindow& window = Window();    
    window.SetPointerGrab(ETrue);
    EnableDragEvents();
    window.SetShadowDisabled(ETrue);
    if ( ! ( iCbaFlags & EEikCbaFlagTransparent ) )
        {
        window.SetBackgroundColor(iEikonEnv->ControlColor(EColorToolbarBackground, *this));
        }
    CEikControlGroup::ConstructL(CEikControlGroup::EFromBottomLeft, CEikControlGroup::ELayHorizontally);
    SetLengthInPixels(iAvkonAppUi->ApplicationRect().Width());
    SetNumberOfLines(1, ETrue);
    iBrushAndPenContext = CCoeBrushAndPenContext::NewL();
    CheckSkinAndUpdateContext();    
    iBrushAndPenContext->SetBrushColor(iEikonEnv->ControlColor(EColorToolbarBackground, *this));
    iBrushAndPenContext->SetPenColor(iEikonEnv->ControlColor(EColorToolbarText, *this));
    SetControlContext(iBrushAndPenContext);
    iEikonEnv->EikAppUi()->AddToStackL(this, ECoeStackPriorityCba, ECoeStackFlagRefusesFocus);
    UpdateFonts();

    SetMSKVisibility( MskAllowed() );
    
    if ( !iFlags.IsSet( ECbaEmbedded ) )
        {
        if ( AknStatuspaneUtils::ExtendedFlatLayoutActive() )
            {
            // Store the current skin background ID of the clock and indicator
            // pane area to draw their background correctly if custom CBA
            // background is used.
            CEikStatusPaneBase* sp = CEikStatusPaneBase::Current();
            if ( sp )
                {
                iClockIndicBgIID = sp->CbaAreaBackgroundID();
                if ( iClockIndicBgIID == KAknsIIDQsnBgAreaControlMp )
                    {
                    // Skin background ID needs to be reverted back
                    // in destructor.
                    iIsClockIndicBgIIDSet = ETrue;
                    }
                sp->SetCbaAreaBackgroundID( iBgIID, CEikStatusPaneBase::EDrawDeferred );
                }
            else
                {
                // Default value.
                iClockIndicBgIID = KAknsIIDQsnBgAreaControl;
                }
            }
        }
    }

void CEikCba::ConstructL(TInt aResourceId)
    {
    if (aResourceId != KNoResource)
        {
        TResourceReader reader;
        iCoeEnv->CreateResourceReaderLC(reader, aResourceId);
        iCbaFlags = reader.ReadInt32();        // flags resource
    
        // If using enhanced cba.
        if ( (iCbaFlags & EEikEnhancedButtonGroup) == EEikEnhancedButtonGroup ) 
            { 
#ifdef RD_ENHANCED_CBA            
            iCommandTable = CEikCommandTable::NewL();   
            BaseConstructL(); 
            CreateScrollBarFrameL();    
                                    
            iSize.iWidth = reader.ReadInt16();
            reader.ReadInt32();               // Skip related buttons resource.
            TInt count( reader.ReadInt16() ); // Read the amount of enhanced cba buttons.
            
            for ( TInt ii = 0; ii < count; ii++ )
                {
                TUint8 version( (TUint8)reader.ReadUint8() );
                TInt commandId( 0 );
                TInt longCommandId( 0 );
                CEikEnhancedCbaButton* button = new (ELeave) CEikEnhancedCbaButton;
                button->SetTextBitmapMode( iExtension->iEnablePostingTransparency );
                CleanupStack::PushL( button );
                
                if( version == EEikCbaButtonLink )
                    {                   
                    TInt aButtonId( reader.ReadInt32() ); // Read ENHANCED_CBA_BUTTON id from LLINK.
                    TResourceReader linkReader; // Reader for reading linked resource.
                    iCoeEnv->CreateResourceReaderLC( linkReader, aButtonId );
                    TUint8 ver( linkReader.ReadUint8() );
                    if( ver == EEikEnhancedCbaButton )
                        {
                        button->ConstructFromResourceL( linkReader );               
                        }                     
                    CleanupStack::PopAndDestroy( ); // linkReader                       
                    }
                else if( version == EEikEnhancedCbaButton )
                    {
                    button->ConstructFromResourceL( reader );                       
                    }
                else
                    {
                    CleanupStack::PopAndDestroy( button );
                    continue;  // Jump over the rest.
                    }
                                        
                iCommandTable->AddCommandL( button ); // Transfers ownership.
                CleanupStack::Pop( button );
                }
                
            // Set observer and add to control group if placed in the command table.
            for ( TInt i = 0; i < KMaxButtonsInCommandTable; i++ )
                {
                CEikEnhancedCbaButton* button = iCommandTable->Command( i );
                if( button )
                    {
                    button->SetObserver( Observer() );
                    button->SetLabelFont( iLabelFont );
                    
                    TEikGroupControl groupCtrl(
                        button, 
                        button->CommandId(), 
                        button->Size().iWidth, 
                        TEikGroupControl::ESetLength);
                        
                    groupCtrl.iLongId = 0;
                    AddControlL(groupCtrl); // Transfers ownership.
                    }
                else
                    {
                    // Add dummy button if no command for this index.
                    button = new (ELeave) CEikEnhancedCbaButton;
                    button->SetTextBitmapMode( iExtension->iEnablePostingTransparency );
                    CleanupStack::PushL( button );
                    button->ConstructEmptyButtonL();                    
                    CleanupStack::Pop( button );
                    
                    TEikGroupControl groupCtrl(
                        button, 
                        button->CommandId(), 
                        button->Size().iWidth,
                        TEikGroupControl::ESetLength);
                        
                    AddControlL(groupCtrl);
                    }
                }           
            
            InsertScrollBarL();
            
            // This needs to be after all buttons are inserted to control group.
            SetBoundingRect(TRect());
            
            ActivateL(); 
#else // RD_ENHANCED_CBA
            User::Leave( KErrNotSupported );                       
#endif // RD_ENHANCED_CBA
            }
        else // Not using enhanced cba.
            {
            reader.Rewind(4);
            ConstructFromResourceL(reader);
            }
            
        CleanupStack::PopAndDestroy(); // reader
        }
    else // aResourceId == KNoResource
        {
        BaseConstructL();
        CreateScrollBarFrameL();
        // Alignments for left, right and MSK.
        TGulAlignmentValue anAlignment[3] = {EHLeftVCenter, EHRightVCenter, EHCenterVCenter};
        const TInt commands = MaxCommands();

        for (TInt ii = 0; ii < commands; ii++)
            {
            CEikCbaButton* button = new(ELeave) CEikCbaButton;
            button->SetTextBitmapMode( iExtension->iEnablePostingTransparency );
            button->SetObserver(Observer());
            CleanupStack::PushL(button);
            button->ConstructL(anAlignment[ii]);
            
            // Initialise button size.
            if(Orientation() == ELayHorizontally)
                {
                TSize buttonSize((MinimumSize().iWidth) / commands, button->MinimumSize().iHeight);
                button->SetSize(buttonSize);
                }
                
            TEikGroupControl groupCtrl(button, ii, 0, TEikGroupControl::EAllowStretch);
            AddControlL(groupCtrl);
            button->SetLabelFont(iLabelFont);
            CleanupStack::Pop( button );
            }
            
        InsertScrollBarL(); // into control group
        iMSKset = EFalse;

        // This needs to be after all buttons are inserted to control group.
        SetBoundingRect(TRect());                        

        if ( !iFlags.IsSet( ECbaActivationDelayed ) )
            {
            ActivateL();
            }
        
        // We need to activate MSK in here - it won't be otherwise activated in landscape.
        if ( iMSKEnabledInPlatform && AknLayoutUtils::MSKEnabled() && 
             iControlArray->Count() == (MaxCommands() + 1) ) // scrollbar added
            {
            if ( (*iControlArray)[KControlArrayCBAButtonMSKPosn].iControl )
                {
                (*iControlArray)[KControlArrayCBAButtonMSKPosn].iControl->ActivateL();
                }
            }
        }

    // Set CBA faded in case the softkeys are empty.
    SetFadeState();
    }


void CEikCba::ConstructFromResourceL(TResourceReader& aReader)
    {
    BaseConstructL();
    CreateScrollBarFrameL();
    TGulAlignmentValue anAlignment[3] = {EHLeftVCenter, EHRightVCenter, EHCenterVCenter};
    iCbaFlags = aReader.ReadInt32(); // flags resource
    iSize.iWidth = aReader.ReadInt16();
    aReader.ReadInt32(); // Skip related buttons resource.
        
    // Ignore any commands that won't fit on screen.
    TInt count = Min(aReader.ReadInt16(), MaxCommands()); 
    __ASSERT_DEBUG(iControlArray->Count() <= count + 2, Panic(EEikPanicCBAControlArraySize));
        
    for (TInt ii = 0; ii < count; ii++)
        {
        TUint8 version = (TUint8)aReader.ReadUint8();
        TInt commandId;
        TInt longCommandId;
        if (version == KAknCbaVersion)
            {
            commandId = aReader.ReadInt16();
            longCommandId = aReader.ReadInt16();
            }
        else
            {
            commandId = aReader.ReadInt16();
            longCommandId = 0;
            }
        CEikCbaButton* button = new(ELeave) CEikCbaButton;
        button->SetTextBitmapMode( iExtension->iEnablePostingTransparency );
        button->SetObserver(Observer());
        CleanupStack::PushL(button);
        button->ConstructFromResourceL(aReader, anAlignment[ii]);
        // Initialise button size.
        if(Orientation() == ELayHorizontally)
            {
            TSize buttonSize((MinimumSize().iWidth)/count, button->MinimumSize().iHeight);
            button->SetSize(buttonSize);
            }
        TEikGroupControl groupCtrl(
            button, 
            commandId, 
            button->Size().iWidth, 
            TEikGroupControl::ESetLength);
            
        groupCtrl.iLongId = longCommandId;
        AddControlL(groupCtrl);        
        button->SetLabelFont(iLabelFont);        
        CleanupStack::Pop( button );
        }

    InsertScrollBarL(); // into control group
    iMSKset = ETrue;

    // MSK is not mandatory, so add empty button if resource not found.
    if (iControlArray->Count() < MaxCommands() + 1) // scrollbar added
        {
        iMSKset = EFalse;
        CEikCbaButton* button = new (ELeave) CEikCbaButton;
        button->SetTextBitmapMode( iExtension->iEnablePostingTransparency );
        CleanupStack::PushL( button );
        button->ConstructEmptyButtonL();                    
        CleanupStack::Pop( button );
        TEikGroupControl groupCtrl(button, 0, button->Size().iWidth,TEikGroupControl::ESetLength);
        AddControlL(groupCtrl);
        }
        
    // This needs to be after all buttons are inserted to control group.
    if (iMSKset)
        {
        SetMSKIconL();
        }

    SetBoundingRect(TRect());

    if ( !iFlags.IsSet( ECbaActivationDelayed ) )
        {
        ActivateL();
        }
    
    // We need to activate MSK in here - it won't be otherwise activated in landscape.
    if ( iMSKEnabledInPlatform && AknLayoutUtils::MSKEnabled() && 
         iControlArray->Count() == (MaxCommands() + 1) ) // scrollbar added
        {
        if ( (*iControlArray)[KControlArrayCBAButtonMSKPosn].iControl )
            {
            (*iControlArray)[KControlArrayCBAButtonMSKPosn].iControl->ActivateL();
            }
        }

    // Set CBA faded in case the softkeys are empty.
    SetFadeState();
    }


TInt CEikCba::MaxCommands() const
    {
    return KMaxSeries60Softkeys;
    }

TInt CEikCba::MSKEnabledInPlatform() const
    {
    return iMSKEnabledInPlatform;
    }


// ---------------------------------------------------------------------------
// Sets the middle softkey icon.
// ---------------------------------------------------------------------------
//
void CEikCba::SetMSKIconL()
    {
    // MSK is not supported by dialog-embedded CBAs.
    if ( iFlags.IsSet( ECbaInsideDialog ) || iFlags.IsSet( ECbaEmbedded ) )
        {
        return;
        }
        
    if ( !MskAllowed() )
        {
        return;         
        }
        
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    if ( !skin )
        { 
        return;
        }
    if( iExtension->iIfMskIconSet )
        {
    //	UpdateIconL();
    	return;
        }
    TEikGroupControl &gCtrl = iControlArray->At( KControlArrayCBAButtonMSKPosn );

    CEikCbaButton *button = static_cast<CEikCbaButton*>( gCtrl.iControl );
    if ( !button )
        {
        return;
        }
   
    CFbsBitmap *bitmap = NULL;
    CFbsBitmap *mask = NULL;
      
    TAknLayoutRect qgn_graf_sk_msk;
    TRect rect;
    qgn_graf_sk_msk.LayoutRect(
        rect,
        AknLayoutScalable_Avkon::control_pane_g4( 0 ).LayoutLine() );

    TSize iconSize( qgn_graf_sk_msk.Rect().Width(),
                    qgn_graf_sk_msk.Rect().Height() );
    TInt leftId = (*iControlArray)[KControlArrayCBAButton1Posn].iId;

    TRgb MSKColor;
    TInt errorMSK;

    TInt iconColorId(0);
    TInt leftCBAColorId(0);   
        
    TBool idleState = AknStatuspaneUtils::IdleLayoutActive();
    if ( idleState )
        {
        iconColorId = EAknsCIQsnIconColorsCG28;
        leftCBAColorId = EAknsCIQsnTextColorsCG15;
        
        errorMSK = AknsUtils::GetCachedColor( 
            skin,
            MSKColor,
            KAknsIIDQsnTextColors,
            EAknsCIQsnTextColorsCG57 );
        }
    else if ( iPopupVisible )
        {
        iconColorId = EAknsCIQsnIconColorsCG29;        
        leftCBAColorId = EAknsCIQsnTextColorsCG17; 
            
        errorMSK = AknsUtils::GetCachedColor( 
            skin,
            MSKColor,
            KAknsIIDQsnTextColors,
            EAknsCIQsnTextColorsCG58 );
        }
    else
        {
        iconColorId = EAknsCIQsnIconColorsCG27;                
        leftCBAColorId = EAknsCIQsnTextColorsCG13; 
       
        errorMSK = AknsUtils::GetCachedColor( 
            skin,
            MSKColor,
            KAknsIIDQsnTextColors,
            EAknsCIQsnTextColorsCG56 );
        }
        
    if ( errorMSK )
        {
        // Use black if no color specified for MSK in skin.
        MSKColor = KRgbBlack;
        AknsUtils::GetCachedColor( skin,
                                   MSKColor,
                                   KAknsIIDQsnTextColors,
                                   leftCBAColorId );         
        }
        
    if ( gCtrl.iId == EAknSoftkeyContextOptions )
        {
        // Set context specific options menu icon.
        AknsUtils::CreateColorIconL(
            skin,
            KAknsIIDQgnPropMskMenu,
            KAknsIIDQsnIconColors,
            iconColorId, // There is no color for icon -> use text color.
            bitmap,
            mask,
            KAvkonBitmapFile,
            EMbmAvkonQgn_prop_msk_menu,
            EMbmAvkonQgn_prop_msk_menu_mask,
            MSKColor );
        }
    else if ( gCtrl.iId == EAknSoftkeyDialler )
        {
        // Set context specific options menu icon.
        AknsUtils::CreateColorIconL(
            skin,
            KAknsIIDQgnIndiTpDialler,
            KAknsIIDQsnIconColors,
            iconColorId, // There is no color for icon -> use text color.
            bitmap,
            mask,
            KAvkonBitmapFile,
            EMbmAvkonQgn_indi_tp_dialler,
            EMbmAvkonQgn_indi_tp_dialler_mask,
            MSKColor );
        }
    else if ( leftId == gCtrl.iId)
        {
        if ( leftId != EEikBidBlank &&
             leftId != EAknSoftkeyEmpty &&
             leftId != 0 )
            {
                // Same as left softkey icon.
                AknsUtils::CreateColorIconL(
                    skin, 
                    KAknsIIDQgnPropMskSelect,
                    KAknsIIDQsnIconColors, 
                    iconColorId, // There is no color for icon -> use text color.
                    bitmap, 
                    mask,
                    KAvkonBitmapFile,
                    EMbmAvkonQgn_prop_msk_select, 
                    EMbmAvkonQgn_prop_msk_select_mask,
                    MSKColor );
             }
        }
    
    if ( bitmap ) // Bitmap not set -> do not use image.
        {
        AknIconUtils::DisableCompression( bitmap );
        AknIconUtils::DisableCompression( mask );
        AknIconUtils::SetSize( bitmap, iconSize );
    
    CEikImage* image = new (ELeave) CEikImage;
    image->SetPicture( bitmap, mask );

        // Transfers ownership of the image (image owns bitmap and mask).
        button->SetImage( *image );
        }
    else
        {
        button->ReplaceImageByLabel(); // remove old image
        }
    
    button->SetContainerWindowL( *this );
    }

EXPORT_C TBool CEikCba::UpdateMSKIconL( const TAknsItemID& aId,
    const TDesC& aBmpFile,
    const TInt32 aBmp,
    const TInt32 aBmpM,
    TBool aEnable )
    {
    iExtension->iIfMskIconSet = EFalse;

    // MSK is not supported by dialog-embedded CBAs.
    if (!aEnable)
        {
    	SetMSKIconL();
    	return ETrue;
        }

    delete iExtension->iBmpFile;
    iExtension->iBmpFile = NULL;
    iExtension->iBmpFile = aBmpFile.AllocL();
    
    iExtension->iIfMskIconSet = ETrue;
    iExtension->iMSKSkinID = aId;
    
    iExtension->iBmp = aBmp;
    iExtension->iBmpM = aBmpM;
    
    return UpdateIconL();
    }


// ----------------------------------------------------------------------------
// CEikCba::EnableItemSpecificSoftkey
// ----------------------------------------------------------------------------
//
EXPORT_C void CEikCba::EnableItemSpecificSoftkey( TBool aEnable )
    {
    if ( iFlags.IsSet( ECbaSingleClickEnabled ) )
        {
        iFlags.Assign( ECbaItemSpecificSoftkeyInUse, aEnable );
        
        if ( aEnable )
            {
            UpdateItemSpecificSoftkey();
            }
        else
            {
            TEikGroupControl& leftSoftkey =
                    ( *iControlArray )[KControlArrayCBAButton1Posn];
    
            if ( !iFlags.IsSet( ECbaInsideDialog ) )
                {
                leftSoftkey.iControl->MakeVisible( ETrue );
                }
            else
                {
                leftSoftkey.iControl->SetDimmed( EFalse );
                leftSoftkey.iControl->DrawDeferred();
                }
            }
        }
    }


void CEikCba::SetMSKCommandObserver(MEikCommandObserver* aCommandObserver)
    {
    // aCommandObserver set to NULL when removing observer.
    iMSKCommandObserver = aCommandObserver;
    }

void CEikCba::UpdateCbaLabels(TBool aScrollerOn)
    {
    // This method is called only from scrollbar that has nothing to do with
    // dialog-embedded CBAs -> ignore the call.
    if ( iFlags.IsSet( ECbaInsideDialog ) )
        {
        return;
        }
        
    // Communicate change to CBA buttons.
    for (TInt ii = 0; ii < iControlArray->Count(); ii++) 
        {
        if (ii != KControlArrayScrollBarPosn) // To avoid tinkering with scrollbar.
            {
            TEikGroupControl& gCtrl = iControlArray->At(ii);
            CEikCbaButton* button = STATIC_CAST(CEikCbaButton*, gCtrl.iControl);
            TRAP_IGNORE(button->SwitchToShortTextL(aScrollerOn));
            }
        }
    // Change of text may affect layout.
    SizeChanged();
    DrawDeferred() ;
    }

void CEikCba::SetSBFrameObserver(MEikScrollBarObserver* aObserver)
    {
    if(iSBFrame)
        {
        iSBFrame->SetScrollBarFrameObserver(aObserver);
        }
    }

void CEikCba::SetScrollBarModelL(TEikScrollBarModel* aModel)
    {
    if(iSBFrame)
        {
        VScrollBarAsControl()->SetModelL(aModel);
        }
    }

const CEikCbaScrollBarFrame* CEikCba::ScrollBarFrame() const
    { 
    return STATIC_CAST(const CEikCbaScrollBarFrame*, iSBFrame); 
    }

CAknScrollBar* CEikCba::VScrollBarAsControl()
    {
    return STATIC_CAST(CAknScrollBar*, VScrollBarAsGroupControl().iControl);
    }

void CEikCba::InsertControlL(TEikGroupControl& aGroupControl,TInt aIndex)
    {
    iControlArray->InsertL(aIndex,aGroupControl); // Takes ownership at this point.
    }


void CEikCba::SetCommandL( TInt aPosition,
                           TInt aCommandId,
                           const TDesC* aText, 
                           const CFbsBitmap* /*aBitmap*/,
                           const CFbsBitmap* /*aMask*/ )
    {
    // We need to check if this call changes the softkeys from being
    // empty to having a command or vice versa to be able to maintain
    // correct fade state.
    TBool isEmptyBefore( IsEmpty() );
    
    TEikGroupControl& groupCtrl = (*iControlArray)[aPosition];
    groupCtrl.iId = aCommandId;
    groupCtrl.iLongId = 0;
    if ( !iFlags.IsSet( ECbaInsideDialog ) )
        {
        if ( aText )
            {
            static_cast<CEikCbaButton*>(
                groupCtrl.iControl )->AddCommandL( *aText );
            }

        if ( aPosition == KControlArrayCBAButtonMSKPosn )
            {
            iMSKset = ETrue;
            }
        SetMSKIconL(); // If MSK or left CBA was changed, this sets MSK icon accordingly.

        // Force labels to be re-formatted...
        SizeChanged();
        }
    else if ( aPosition != KControlArrayCBAButtonMSKPosn )
        {
        CAknButton* button = static_cast<CAknButton*>( groupCtrl.iControl );
        CAknCommandButtonState* buttonState =
            static_cast<CAknCommandButtonState*>( button->State() );
        buttonState->SetTextL( *aText );
        buttonState->SetCommand( aCommandId );
        }
    
    TBool isEmptyAfter( IsEmpty() );
    
    if ( !COMPARE_BOOLS( isEmptyBefore, isEmptyAfter ) )
        {
        SetFadeState();
        }

    ReportContentChangedEvent();      
    }


void CEikCba::SetCommandL(TInt aPosition,TInt aResourceId)
    {
    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC(reader,aResourceId);
    TInt version = reader.ReadInt8(); // version
    
#ifdef RD_ENHANCED_CBA
    if( version == EEikCbaButtonLink )
        {
        TInt aButtonId = reader.ReadInt32(); // Read ENHANCED_CBA_BUTTON id from LLINK.
        CleanupStack::PopAndDestroy(); // reader            
        iCoeEnv->CreateResourceReaderLC( reader, aButtonId );
        TUint8 aVersion = reader.ReadUint8();
            
        // Panics if linked resource is not enhanced cba button.
        __ASSERT_DEBUG( aVersion == EEikEnhancedCbaButton, Panic(EEikPanicCBAIsNotEnhancedCba) );

        reader.ReadUint8(); // commandType      
        }
    else if( version == EEikEnhancedCbaButton )
        {
        reader.ReadUint8(); // commandType                              
        }
#endif // RD_ENHANCED_CBA
    TInt commandId(0);
    if (version == KAknCbaVersion)
        {
        commandId = reader.ReadInt16();
        reader.ReadInt16();
        }
    else
        {
        commandId = reader.ReadInt16();
        }
        
    TPtrC text = reader.ReadTPtrC();
    SetCommandL(aPosition, commandId, &text, NULL, NULL);
    CleanupStack::PopAndDestroy(); // reader
    
    ReportContentChangedEvent();
    }
    
/**
* Installs a new set of commands to be associated with the cba buttons.
* The previous command set is restored if there is an error while adding
* the new command set.
*/
void CEikCba::SetCommandSetL(TInt aResourceId)
    {
    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC(reader, aResourceId);

    iCbaFlags = reader.ReadInt32();
    
    if ( ( iCbaFlags & EEikEnhancedButtonGroup ) == EEikEnhancedButtonGroup ) 
        { 
        CleanupStack::PopAndDestroy(); // reader
        OfferCommandListL( aResourceId );
        return;
        }
    
    SetButtonGroupFlags( iCbaFlags );
    reader.ReadInt16(); // Skip width resource.
    reader.ReadInt32(); // Skip related buttons resource.
    const TInt maxCommands = MaxCommands();
    
    // Ignore any commands that won't fit on screen.
    TInt count = Min(reader.ReadInt16(), maxCommands); 

    TInt previousIds[KMaxSeries60Softkeys + 1]; // Uses 16 bytes stack, +1 for scrollbar.
                        
    __ASSERT_DEBUG(iControlArray->Count() <= count + 2, Panic(EEikPanicCBAControlArraySize));

    // Replace the existing command set.
    TInt controlId = 0;
    for (controlId = 0; controlId < count + 1; controlId++) // (+1 for scroll bar)
        {
        if (controlId != KControlArrayScrollBarPosn) // To avoid tinkering with scrollbar.
            {
            // Store the existing commands.
            TEikGroupControl& groupCtrl = (*iControlArray)[controlId];
            previousIds[controlId] = groupCtrl.iId;
            TUint8 version = (TUint8)reader.ReadUint8();
            TInt commandId;        
            TInt errorcode;
                  
            if (version == KAknCbaVersion)
                {
                commandId = reader.ReadInt16();
                reader.ReadInt16(); // Skip long command id.
                }
            else
                {
                commandId = reader.ReadInt16();
                }
            TPtrC text=reader.ReadTPtrC();
            reader.ReadTPtrC();        // bmp filename
            reader.ReadInt16();        // bmp id
            reader.ReadInt16();        // bmp mask id  

            // Add the new commands.
            TRAP(errorcode, AddCommandToStackWithoutSizeChangedL(controlId, commandId, &text));
            if (errorcode)  // In case of error restore previous commands before leave.
                {
                if (controlId > 0)
                    {
                    for (TInt counter = 0; counter < controlId; counter++)
                        {
                        // Do not deal with the scroller as a CEikCbaButton; skip its index.
                        if (counter != KControlArrayScrollBarPosn)
                            {
                            RemoveCommandFromStack(counter,previousIds[counter]);
                            }
                        }
                    }
                User::Leave(errorcode);
                }
            }
        }
    
    // Remove the original commands from the temporary store.
    for (controlId = 0; controlId < count + 1; controlId++) // +1 for scroll bar
        {
        if (controlId != KControlArrayScrollBarPosn)
            {
            TInt controlPosition = controlId;
            if (controlId > 1)
                {
                controlPosition-=1;
                }
            RemovePreviousCommandWithoutSizeChanged(controlId);
            }
        }
    SetMSKIconL();    
    // If MSK was not defined in softkey resources, set MSK command id same as left
    // softkey's command id and set label empty.
    // We can't restore original commands any more, so if setting MSK fails,
    // at least left and right softkeys are set.
    if (count < KControlArrayCBAButtonMSKPosn)
        {
        TRAP_IGNORE( SetCommandL( 
            KControlArrayCBAButtonMSKPosn,
            (*iControlArray)[KControlArrayCBAButton1Posn].iId,
            &KNullDesC, 
            NULL, 
            NULL) );
            
        iMSKset = ETrue;
        }
    else
        {
        SetMSKIconL(); // If MSK id was changed, this sets MSK icon accordingly.
        }
    
    CleanupStack::PopAndDestroy(); // reader

    // Force labels to be re-formatted...
    SizeChanged();
    ReportContentChangedEvent();
    }

void CEikCba::AddCommandL(TInt /*aPosition*/, TInt /*aCommandId*/, const TDesC* /*aText*/, 
    const CFbsBitmap* /*aBitmap*/, const CFbsBitmap* /*aMask*/)
    {
    User::Leave(KErrNotSupported);
    }


void CEikCba::AddCommandToStackWithoutSizeChangedL(TInt aPosition,
                                               TInt aCommandId,
                                               const TDesC* aText)
    {
    // We need to check if this call changes the softkeys from being
    // empty to having a command or vice versa to be able to maintain
    // correct fade state.
    TBool isEmptyBefore( IsEmpty() );
    
    TEikGroupControl& groupCtrl = (*iControlArray)[aPosition];
    
    if ( iFlags.IsSet( ECbaInsideDialog ) )
        {
        CAknButton* button = static_cast<CAknButton*>( groupCtrl.iControl );
        button->AddStateL( NULL, NULL, NULL, NULL, *aText, KNullDesC, 0, aCommandId );
            
        if ( aText->Length() == 0 || !aText->Compare( _L(" ") ) )
            {
            button->SetDimmed( ETrue );
            }
        
        TInt state( button->StateIndex() + 1 );
        
        // DrawDeferred must be used here to reduce flicker,
        // as ECS may cause unnecessary CBA label updates in queries.
        button->SetCurrentState( state, EFalse );
        button->DrawDeferred();
        }
    else
        {
        static_cast<CEikCbaButton*>(groupCtrl.iControl)->PushCommandL(groupCtrl.iId /*aCommandId*/, 
                *aText);
        }
    
    groupCtrl.iId = aCommandId;
    groupCtrl.iLongId = 0;
    
    if ( aPosition == KControlArrayCBAButtonMSKPosn )
        {
        iMSKset = ETrue;
        }
    SetMSKIconL(); // If MSK id was changed, this sets MSK icon accordingly.

    TBool isEmptyAfter( IsEmpty() );

    if ( !COMPARE_BOOLS( isEmptyBefore, isEmptyAfter ) )
        {
        SetFadeState();
        }

    ReportContentChangedEvent();
    }

void CEikCba::AddCommandToStackL( TInt aPosition,
                                  TInt aCommandId,
                                  const TDesC* aText, 
                                  const CFbsBitmap* /*aBitmap*/,
                                  const CFbsBitmap* /*aMask*/ )
    {

    AddCommandToStackWithoutSizeChangedL( aPosition, aCommandId, aText);
    // Force labels to be re-formatted...
    SizeChanged();
    }


void CEikCba::AddCommandToStackL(TInt aPosition, TInt aResourceId)
    {
    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC(reader,aResourceId);
    TUint8 version = (TUint8)reader.ReadInt8();
    TInt commandId(0);
    if (version == KAknCbaVersion)
        {
        commandId = reader.ReadInt16();
        reader.ReadInt16(); // Skip long command id.
        }
    else
        {
        commandId = reader.ReadInt16();
        }
    TPtrC text=reader.ReadTPtrC();
    AddCommandToStackL(aPosition, commandId, &text, NULL, NULL);
    CleanupStack::PopAndDestroy(); // reader
      
    ReportContentChangedEvent();
    }

void CEikCba::AddCommandSetToStackL(TInt aResourceId)
    {
    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC(reader,aResourceId);

    iCbaFlags = reader.ReadInt32(); // Flags resource.
    reader.ReadInt16();             // Skip width resource.
    reader.ReadInt32();             // Skip related buttons resource.
    
    SetButtonGroupFlags( iCbaFlags );
    // Ignore any commands that won't fit on screen.
    const TInt maxCommands = MaxCommands();
    const TInt count = Min(reader.ReadInt16(), maxCommands); 

    __ASSERT_DEBUG(iControlArray->Count() <= count + 2, Panic(EEikPanicCBAControlArraySize));

    for (TInt ii = 0; ii < count + 1; ii++) // +1 for scroll bar
        {
        if (ii != KControlArrayScrollBarPosn) // To avoid tinkering with the scrollbar.
            {
            TUint8 version = (TUint8)reader.ReadUint8();
            TInt commandId;        
            
            if (version == KAknCbaVersion)
                {
                commandId = reader.ReadInt16();
                reader.ReadInt16(); // Skip long command id.
                }
            else
                {
                commandId = reader.ReadInt16();
                }
            TPtrC text = reader.ReadTPtrC();
            reader.ReadTPtrC(); // bmp filename
            reader.ReadInt16(); // bmp id
            reader.ReadInt16(); // bmp mask id
            TInt errorcode;
            TRAP(errorcode, AddCommandToStackWithoutSizeChangedL(ii, commandId, &text));
            if (errorcode) // Restore previous commands before leave.
                {
                if (ii > 0)
                    {
                    for (TInt counter = 0; counter < ii; counter++)
                        {
                        if (counter != KControlArrayScrollBarPosn)
                            {
                            TEikGroupControl& groupCtrl = (*iControlArray)[counter];
                            
                            groupCtrl.iId = 
                                STATIC_CAST(CEikCbaButton*, groupCtrl.iControl)->PopCommand();
                                
                            groupCtrl.iLongId = 0;
                            }
                        }
                    }
                User::Leave(errorcode);
                }
            }
        }
        
    if (count == KControlArrayCBAButtonMSKPosn)
        {
        iMSKset = ETrue;
        }
    SetMSKIconL(); // If MSK id was changed, this sets MSK icon accordingly.

    CleanupStack::PopAndDestroy(); // reader

    // Force labels to be re-formatted...
    SizeChanged();
    ReportContentChangedEvent();
    }

void CEikCba::SetDefaultCommand(TInt /*aCommandId*/)
    {
    }

TSize CEikCba::CalcMinimumSizeL(TInt /*aResourceId*/)
    {
    return MinimumSize();
    }


void CEikCba::RemoveCommandFromStack( TInt aPosition, TInt aCommandId )
    {
    // We need to check if this call changes the softkeys from being
    // empty to having a command or vice versa to be able to maintain
    // correct fade state.
    TBool isEmptyBefore( IsEmpty() );
    
    TEikGroupControl& groupCtrl = (*iControlArray)[aPosition];
    if ( groupCtrl.iId == aCommandId )
        {
        // Command to be removed is topmost.
        if ( iFlags.IsSet( ECbaInsideDialog ) )
            {
            CAknButton* button = static_cast<CAknButton*>( groupCtrl.iControl );
            button->RemoveCurrentState();
            
            CAknCommandButtonState* buttonState =
                static_cast<CAknCommandButtonState*>( button->State() );
                
            groupCtrl.iId     = buttonState->CommandId();
            groupCtrl.iLongId = 0;
                
            if ( buttonState->Text().Length() == 0 ||
                 !buttonState->Text().Compare( _L(" ") ) )
                {
                button->SetDimmed( ETrue );
                }
            }
        else
            {
            groupCtrl.iId = static_cast<CEikCbaButton*>( groupCtrl.iControl )->PopCommand();
            groupCtrl.iLongId = 0;
            }
        }
    else // Command to be removed is not on the top, check the whole stack.
        {
        STATIC_CAST(CEikCbaButton*, groupCtrl.iControl)->RemoveCommand(aCommandId);
        }

    // If MSK or left CBA was changed, this sets MSK icon accordingly.
    TRAP_IGNORE( SetMSKIconL() ); 
    
    // Force labels to be re-formatted...
    SizeChanged();
    
    TBool isEmptyAfter( IsEmpty() );
    
    if ( !COMPARE_BOOLS( isEmptyBefore, isEmptyAfter ) )
        {
        SetFadeState();
        }

    DrawDeferred();
    ReportContentChangedEvent();
    }

void CEikCba::RemovePreviousCommandWithoutSizeChanged(TInt aPosition)
    {
    TEikGroupControl& groupCtrl = (*iControlArray)[aPosition];
    STATIC_CAST(CEikCbaButton*, groupCtrl.iControl)->RemovePreviousCommand();
    }

void CEikCba::RemovePreviousCommand(TInt aPosition)
    {
    RemovePreviousCommandWithoutSizeChanged( aPosition );
    // If MSK or left CBA was changed, this sets MSK icon accordingly.
    TRAP_IGNORE( SetMSKIconL() ); 
    
    // Force labels to be re-formatted...
    SizeChanged();
    ReportContentChangedEvent();
    }


TInt CEikCba::CommandPos(TInt aCommandId) const
    {
    return IndexById(aCommandId);
    }

void CEikCba::DimCommand(TInt aCommandId,TBool aDimmed)
    {
    CCoeControl* control( ButtonById( aCommandId ) );
    if ( control )
        {
        if ( SoftkeyStatusChangeAllowed( IndexById( aCommandId ), aDimmed ) )
            {
            control->SetDimmed( aDimmed );
            }
        }
    }

TBool CEikCba::IsCommandDimmed(TInt aCommandId) const
    {
    if( ButtonById(aCommandId) )
        {
        return ButtonById(aCommandId)->IsDimmed();
        }
    return EFalse;
    }

void CEikCba::MakeCommandVisible(TInt aCommandId, TBool aVisible)
    {
    CCoeControl* control( ButtonById( aCommandId ) );
    if ( control )
        {
        if ( SoftkeyStatusChangeAllowed( IndexById( aCommandId ), !aVisible ) )
            {
            control->MakeVisible( aVisible );
            }
        }
    }

TBool CEikCba::IsCommandVisible(TInt aCommandId) const
    {
    if( ButtonById(aCommandId) )
        {
        return ButtonById(aCommandId)->IsVisible();
        }
    return EFalse;        
    }

void CEikCba::AnimateCommand(TInt /*aCommandId*/)
    {
    }


// ---------------------------------------------------------------------------
// Sets the dimming status of a button with the specified position.
// ---------------------------------------------------------------------------
//
void CEikCba::DimCommandByPosition( TInt aPosition, TBool aDimmed )
    {
    if ( aPosition >= iControlArray->Count() )
        { 
        return;
        }

    if ( SoftkeyStatusChangeAllowed( aPosition, aDimmed ) )
        {
        TEikGroupControl& groupCtrl = ( *iControlArray )[ aPosition ];
        groupCtrl.iControl->SetDimmed( aDimmed );
        }
    }


// ---------------------------------------------------------------------------
// Returns the dimming status of a button with the specified position.
// ---------------------------------------------------------------------------
//
TBool CEikCba::IsCommandDimmedByPosition( TInt aPosition ) const
    {
    if ( aPosition >= iControlArray->Count() ) 
        {
        return EFalse;    
        }

    TEikGroupControl& groupCtrl = (*iControlArray)[aPosition];
    return groupCtrl.iControl->IsDimmed();
    }


// ---------------------------------------------------------------------------
// Sets the visibility of a button with the specified position.
// ---------------------------------------------------------------------------
//
void CEikCba::MakeCommandVisibleByPosition( TInt aPosition, TBool aVisible )
    {
    if ( aPosition >= iControlArray->Count() )
        { 
        return;    
        }

    if ( SoftkeyStatusChangeAllowed( aPosition, !aVisible ) )
        {
        TEikGroupControl& groupCtrl = ( *iControlArray )[ aPosition ];

        if ( !iFlags.IsSet( ECbaInsideDialog ) )
            {
            groupCtrl.iControl->MakeVisible( aVisible );
            }
        else
            {
            // Just dim the button, don't hide it.
            groupCtrl.iControl->SetDimmed( !aVisible );
            groupCtrl.iControl->DrawDeferred();
            }
        }
    }


TBool CEikCba::IsCommandVisibleByPosition(TInt aPosition) const
    {
    if (aPosition >= iControlArray->Count()) 
        {
        return EFalse;    
        }
    TEikGroupControl& groupCtrl = (*iControlArray)[aPosition];

    if ( !iFlags.IsSet( ECbaInsideDialog ) )
        {
        return STATIC_CAST(CEikCbaButton*, groupCtrl.iControl)->IsVisible();
        }
        
    return !groupCtrl.iControl->IsDimmed();
    }

void CEikCba::AnimateCommandByPosition(TInt /*aPosition*/)
    {
    }
    
/*CCoeControl* CEikCba::GroupControlByPosition(TInt aPosition) const
    {
    if (aPosition >= iControlArray->Count())
        { 
        return NULL;
        }
    TEikGroupControl& groupCtrl = (*iControlArray)[aPosition];
    return groupCtrl.iControl;
    }*/


// ---------------------------------------------------------------------------
// CEikCba::ButtonRectByPosition
// Gets a CBA button rectangle.
// ---------------------------------------------------------------------------
//
TRect CEikCba::ButtonRectByPosition( TInt aPosition, TBool aRelativeToScreen )
    {
    TRect rect( 0, 0, 0, 0 );
    
    if ( aPosition >= iControlArray->Count() || aPosition < 0 )
        {
        return rect;
        }

    if ( !AknLayoutUtils::PenEnabled() )
        {
        // Button rectangle is the actual control rect.
        rect = ( *iControlArray )[aPosition].iControl->Rect();
        }
    else
        {
        // In touch layouts the button areas are read from the
        // layout data because they are larger than the actual
        // control size.
        // Also, currently touch layouts do not support MSK,
        // so it's ignored.
        TRect containerRect( Rect() );
        TAknLayoutRect layoutRect;
        TRect button1Rect( 0, 0, 0, 0 );
        TRect button2Rect( 0, 0, 0, 0 );
        TRect buttonMSKRect( 0, 0, 0, 0 );

        if ( iFlags.IsSet( ECbaEmbedded ) )
            {
            TRect rect ( Rect() );
            TAknLayoutRect layoutRect;
            layoutRect.LayoutRect(
                    rect, 
                    AknLayoutScalable_Avkon::popup_sk_window_g1( 0 ) );
            
            // Button widths are calculated based on cba area width
            // margin width is taken from layout
            TInt margin = layoutRect.Rect().iTl.iX - rect.iTl.iX;
            TInt buttonWidth = ( rect.Width() - margin * 2 ) / 2;
            TSize buttonSize ( buttonWidth, layoutRect.Rect().Height() );
                    
            button1Rect = TRect(
                    TPoint( rect.iTl.iX + margin, layoutRect.Rect().iTl.iY ),
                    buttonSize );
            button2Rect = TRect( 
                    TPoint( button1Rect.iBr.iX, layoutRect.Rect().iTl.iY ), 
                    TPoint( rect.iBr.iX - margin, 
                            layoutRect.Rect().iBr.iY ) );
            }
        else if ( AknLayoutFlags() & EAknLayoutCbaInRightPane )
            {
            // Landcsape nHD layout, button parent rectangle
            // is the whole screen so aRelativeToScreen parameter
            // is not taken into account.
            TAknWindowComponentLayout rightAreaLayout(
                AknLayoutScalable_Avkon::area_side_right_pane( 0 ) );
                
            layoutRect.LayoutRect(
                containerRect,
                DoCompose(
                    rightAreaLayout,
                    AknLayoutScalable_Avkon::sctrl_sk_bottom_pane() ).LayoutLine() );
            TRect bottomSKRect( layoutRect.Rect() );

            layoutRect.LayoutRect(
                containerRect,
                DoCompose(
                    rightAreaLayout,
                    AknLayoutScalable_Avkon::sctrl_sk_top_pane() ).LayoutLine() );
            TRect topSKRect( layoutRect.Rect() );

            layoutRect.LayoutRect(
                bottomSKRect,
                AknLayoutScalable_Avkon::aid_touch_sctrl_bottom().LayoutLine() );
            button1Rect = layoutRect.Rect();
    
            layoutRect.LayoutRect(
                topSKRect,
                AknLayoutScalable_Avkon::aid_touch_sctrl_top().LayoutLine() );
            button2Rect = layoutRect.Rect();
            }
        else if ( AknLayoutFlags() & EAknLayoutCbaInControlPane )
            {
            TBool mskDisabled( !MskAllowed() );
                       
            TBool flatLscLayout(
                Layout_Meta_Data::IsLandscapeOrientation() &&
                AknStatuspaneUtils::FlatLayoutActive() );

            if ( mskDisabled && !flatLscLayout ) 
                {
                if ( aRelativeToScreen )
                    {
                    AknLayoutUtils::LayoutMetricsRect(
                        AknLayoutUtils::EControlPane, containerRect );
                    }
    
                if ( AknLayoutUtils::LayoutMirrored() )
                    {
                    layoutRect.LayoutRect(
                        containerRect,
                        AknLayoutScalable_Avkon::aid_touch_ctrl_right().LayoutLine() );
                    button1Rect = layoutRect.Rect();
        
                    layoutRect.LayoutRect(
                        containerRect,
                        AknLayoutScalable_Avkon::aid_touch_ctrl_left().LayoutLine() );
                    button2Rect = layoutRect.Rect();
                    }
                else
                    {
                    layoutRect.LayoutRect(
                        containerRect,
                        AknLayoutScalable_Avkon::aid_touch_ctrl_left().LayoutLine() );
                    button1Rect = layoutRect.Rect();
            
                    layoutRect.LayoutRect(
                        containerRect,
                        AknLayoutScalable_Avkon::aid_touch_ctrl_right().LayoutLine() );
                    button2Rect = layoutRect.Rect();
                    }
                }
            else
                {
                layoutRect.LayoutRect(
                    containerRect,
                    AknLayoutScalable_Avkon::control_pane_g6( 0 ).LayoutLine() );
                button1Rect = layoutRect.Rect();
                
                layoutRect.LayoutRect(
                    containerRect,
                    AknLayoutScalable_Avkon::control_pane_g8( 0 ).LayoutLine() );
                button2Rect = layoutRect.Rect();

            if ( !mskDisabled ) 
                {
                layoutRect.LayoutRect(
                    containerRect,
                    AknLayoutScalable_Avkon::control_pane_g7( 0 ).LayoutLine() );
                buttonMSKRect = layoutRect.Rect();
                }
            else
                {
                buttonMSKRect.SetRect( 0, 0, 0, 0 );
                }
                }
            }
            
        switch ( aPosition )
            {
            case KControlArrayCBAButton1Posn:
                {
                rect = button1Rect;
                break;
                }

            case KControlArrayCBAButton2Posn:
                {
                rect = button2Rect;
                break;
                }

            case KControlArrayCBAButtonMSKPosn:
                {
                rect = buttonMSKRect;
                break;
                }

            default:
                {
                break;
                }
            }
        }
        
    return rect;
    }


CCoeControl* CEikCba::AsControl()
    {
    return this;
    }

const CCoeControl* CEikCba::AsControl() const
    {
    return this;
    }


void CEikCba::SetBoundingRect( const TRect& /*aBoundingRect*/ )
    {
    if ( iFlags.IsSet( ECbaEmbedded ) )
        {
        return;
        }

    // If background skin id has not been set from outside CBA, 
    // update it in case status pane layout has changed
    if ( !iExtension->iCbaBgIIDSetExt )
        {
        iBgIID = AknStatuspaneUtils::IdleLayoutActive() ?
            KAknsIIDQsnBgAreaControlIdle :
            KAknsIIDQsnBgAreaControl;
        }

    // If CBA is inserted into a query dialog then it is positioned by the
    // query control. 
    if ( iFlags.IsSet( ECbaInsideDialog ) )
        {
        return;
        }

    TRect oldRect( Rect() );
    
    TRect screen;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screen );
    
    // Enable the MSK icon if status pane layout is changed from
    // MSK disabled to MSK enabled one.
    TBool mskDisabled( !MskAllowed() );
    
    const TInt aknLayoutFlags = AknLayoutFlags();
    if ( aknLayoutFlags & EAknLayoutCbaInControlPane )
        {
        if ( mskDisabled )
            {
            SetMSKVisibility( EFalse );
            }
        else
            {
            SetMSKVisibility( ETrue );
            TRAP_IGNORE( SetMSKIconL() );
            }
        
        // We must check for landscape mode bottom sks 
        TInt bottomPaneVariety = 1;
        if ( Layout_Meta_Data::IsLandscapeOrientation() )
            {
            bottomPaneVariety = 6;
            }
            
        TAknWindowLineLayout controlPane( DoCompose(
            AknLayoutScalable_Avkon::application_window( 0 ),
            DoCompose( AknLayoutScalable_Avkon::area_bottom_pane( bottomPaneVariety ),
                       AknLayoutScalable_Avkon::control_pane() ) ).LayoutLine() );
        
        TAknLayoutRect cbarect;        
        cbarect.LayoutRect( screen, controlPane );
        
        SetRect( cbarect.Rect() );

        // Set correct window region incase we have been in stacon mode.
        RRegion region;
        region.AddRect( Rect() );
            
        CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
        
        // If status indicators and clock are shown in control pane area,
        // then remove those areas from cba window region.
        // 
        // NOTE: MSK is not supported in landscape.
        //
        if ( statusPane &&
             statusPane->IsVisible() &&
             AknStatuspaneUtils::ExtendedFlatLayoutActive() && 
             ( iBgIID == KAknsIIDQsnBgAreaControl || 
               iBgIID == KAknsIIDQsnBgAreaControlIdle ||
               iBgIID == KAknsIIDQsnBgAreaControlMp ||
               ( iBgIID == KAknsIIDWallpaper &&
                 AknStatuspaneUtils::IdleLayoutActive() ) ) ) 
            {
            TRect digitalClockRect( 0,0,0,0 );
            TRect indicatorRect( 0,0,0,0 );
 
            if ( iBgIID == KAknsIIDQsnBgAreaControlMp )
                {
                if ( !iIsClockIndicBgIIDSet )
                    {
                    statusPane->SetCbaAreaBackgroundID(
                        iBgIID,
                        CEikStatusPaneBase::EDrawDeferred );
                    iIsClockIndicBgIIDSet = ETrue;
                    }
                }
            else
                {
                if ( statusPane->CbaAreaBackgroundID() != iBgIID )
                    {
                    statusPane->SetCbaAreaBackgroundID(
                        iBgIID,
                        CEikStatusPaneBase::EDrawDeferred );
                    }
                }

            TRAPD( err1,
                   indicatorRect = statusPane->PaneRectL( TUid::Uid( 
                        EEikStatusPaneUidIndic ) ) );
                                   
            TRAPD( err2,
                   digitalClockRect = statusPane->PaneRectL( TUid::Uid( 
                        EEikStatusPaneUidDigitalClock ) ) );

            if ( !err1 && !err2 )
                {
                TPoint cbaPositionRelativeToScreen( PositionRelativeToScreen() );
                TRect cbaRectRelativeToScreen( cbaPositionRelativeToScreen, Size() );

                if ( cbaRectRelativeToScreen.Intersects( indicatorRect ) )
                    {
                    indicatorRect.Move(
                        -cbaPositionRelativeToScreen.iX,
                        -cbaPositionRelativeToScreen.iY );
                        
                    region.SubRect( indicatorRect );                              
                    }
                
                if ( cbaRectRelativeToScreen.Intersects( digitalClockRect ) )
                    {
                    digitalClockRect.Move(
                        -cbaPositionRelativeToScreen.iX,
                        -cbaPositionRelativeToScreen.iY );
                        
                    region.SubRect( digitalClockRect );       
                    }
                }
            }

        if ( !region.CheckError() )
            {
            Window().SetShape( region );
            }
        region.Close();
        }
    else if ( aknLayoutFlags & EAknLayoutCbaInRightPane )
        {
        // Softkeys in right pane.
        //
        // We set the rect to whole screen and then set window to 
        // clip other parts than softkey buttons.
        
        TRect rect( screen );              
        SetRect( rect );

        // Read right (top in landscape) softkey layout.      
        TAknWindowLineLayout rightSoftkeyLayout(
            DoCompose( AknLayoutScalable_Avkon::area_side_right_pane( 0 ),
                       AknLayoutScalable_Avkon::sctrl_sk_top_pane() ).LayoutLine() );

        TAknLayoutRect rightSoftkeyLayoutRect;
        rightSoftkeyLayoutRect.LayoutRect( rect, rightSoftkeyLayout );
        TRect rightSoftKeyButtonRect( rightSoftkeyLayoutRect.Rect() );

        // Read left (bottom in landscape) softkey layout.       
        TAknWindowLineLayout leftSoftkeyLayout( 
            DoCompose( AknLayoutScalable_Avkon::area_side_right_pane( 0 ),
                       AknLayoutScalable_Avkon::sctrl_sk_bottom_pane() ).LayoutLine() );

        TAknLayoutRect leftSoftkeyLayoutRect;
        leftSoftkeyLayoutRect.LayoutRect( rect, leftSoftkeyLayout );
        TRect leftSoftKeyButtonRect( leftSoftkeyLayoutRect.Rect() );

        // Set the window shape.
        RRegion region;
        region.AddRect( leftSoftKeyButtonRect );
        region.AddRect( rightSoftKeyButtonRect );
        if ( !region.CheckError() )
            {
            Window().SetShape( region );
            }
        region.Close();
        }
    else
        {
        // Stacon pane (combined status and control pane).
        //
        // Control pane is splitted. We set the rect to whole screen and then set window to 
        // clip other parts than softkey buttons.
        
        TRect rect( screen );              
        SetRect( rect );

        TInt variety = 0;
        if ( AknLayoutFlags() & EAknLayoutCbaInStaconPaneLeft )
            {
            variety = 1;
            }

        TAknWindowComponentLayout layout0;
        TAknWindowComponentLayout layout1;
        TAknWindowComponentLayout layout2;

        // Read right (top in landscape) softkey layout.
        layout0 = AknLayoutScalable_Avkon::area_top_pane( 2 );
        layout1 = AknLayoutScalable_Avkon::stacon_top_pane();

        // If clock is shown in stacon, cba area is smaller.
        TInt topCbaVariety = variety;
        if ( AknStatuspaneUtils::ExtendedStaconPaneActive() 
                || AknStatuspaneUtils::ExtendedLayoutActive() )
            {
            topCbaVariety += 4;
            }

        layout2 = AknLayoutScalable_Avkon::control_top_pane_stacon( topCbaVariety );
        
        TAknWindowLineLayout rightSoftkeyLayout(
            DoCompose( layout0,DoCompose( layout1, layout2 ) ).LayoutLine() );

        TAknLayoutRect rightSoftkeyLayoutRect;
        rightSoftkeyLayoutRect.LayoutRect( rect, rightSoftkeyLayout );
        TRect rightSoftKeyButtonRect( rightSoftkeyLayoutRect.Rect() );

        // Read left (bottom in landscape) softkey layout.
        layout0 = AknLayoutScalable_Avkon::area_bottom_pane( 2 );
        layout1 = AknLayoutScalable_Avkon::stacon_bottom_pane();

        // If clock is shown in stacon, cba area is smaller.
        TInt bottomCbaVariety = variety;
        if ( AknStatuspaneUtils::ExtendedStaconPaneActive() 
                || AknStatuspaneUtils::ExtendedLayoutActive() )
            {
            bottomCbaVariety += 2;
            }
        
        layout2 =
            AknLayoutScalable_Avkon::control_bottom_pane_stacon(
                bottomCbaVariety );
        
        TAknWindowLineLayout leftSoftkeyLayout( 
            DoCompose( layout0, DoCompose( layout1, layout2 ) ).LayoutLine() );

        TAknLayoutRect leftSoftkeyLayoutRect;
        leftSoftkeyLayoutRect.LayoutRect( rect, leftSoftkeyLayout );
        TRect leftSoftKeyButtonRect( leftSoftkeyLayoutRect.Rect() );

        // Set the window shape.
        RRegion region;
        region.AddRect( leftSoftKeyButtonRect );
        region.AddRect( rightSoftKeyButtonRect );
        if ( !region.CheckError() )
            {
            Window().SetShape( region );
            }
        region.Close();        
        }
    
    // The softkey frame needs to be updated if the size or
    // position of CBA was changed. 
    if ( iExtension && Rect() != oldRect )
        {
        TRAP_IGNORE( iExtension->UpdateSoftkeyFrameL( EFalse ) );

        // Finally ensure that MSK drawing is disabled if the status pane
        // layout is changed from MSK enabled to MSK disabled one.
        if ( mskDisabled )
            {
            SetMSKVisibility( EFalse );
            }
        
        DrawDeferred();
        }
    }


// ---------------------------------------------------------------------------
// Subtracts the area occupied by the button group from the specified
// bounding rectangle.
// ---------------------------------------------------------------------------
//
void CEikCba::ReduceRect( TRect& aBoundingRect ) const
    {
    // CBA inside Popup/Query Input does not reduce bounding rect
    if ( iFlags.IsSet( ECbaEmbedded ) || iFlags.IsSet( ECbaInsideDialog ) )
        {
        return;
        }
    
    if ( !IsVisible() )
        {
        return;
        }

    const TInt aknLayoutFlags = AknLayoutFlags();

    if ( aknLayoutFlags & EAknLayoutCbaInControlPane )
        {
        // Cba in control pane.
        if ( aBoundingRect.Intersects( TRect( iPosition, iSize ) ) )
            {
            aBoundingRect.iBr.iY = Position().iY;
            }
        }
    else if ( aknLayoutFlags & EAknLayoutCbaInRightPane )
        {
        // Cba in right pane.

        TRect rect;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, rect );

        const TAknWindowLineLayout rightPaneLayout( 
            AknLayoutScalable_Avkon::area_side_right_pane( 0 ).LayoutLine() );

        TAknLayoutRect rightPaneRect;
        rightPaneRect.LayoutRect( rect, rightPaneLayout );

        const TRect rightPane( rightPaneRect.Rect() );
        
        if ( aBoundingRect.Intersects( rightPane ) )
            {
            // Always on the right side, won't be mirrored.
            aBoundingRect.iBr.iX = rightPane.iTl.iX;
            }
        }
    else
        {
        // CBA in stacon pane.
        if ( iControlArray->Count() != 0 )
            {
            CCoeControl *leftSoftkey =
                (*iControlArray)[KControlArrayCBAButton1Posn].iControl;
            CCoeControl *rightSoftkey =
                (*iControlArray)[KControlArrayCBAButton2Posn].iControl;
            if ( leftSoftkey && rightSoftkey )
                {
                RRegion boundingRegion;
                TRect originalboundingRect( aBoundingRect );
                boundingRegion.AddRect( originalboundingRect );
                
                TRect rect;
                AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen,
                                                   rect );              

                TInt variety = 0;
                if ( aknLayoutFlags & EAknLayoutCbaInStaconPaneLeft )
                    {
                    variety = 1;
                    }

                TAknWindowComponentLayout layout0;
                TAknWindowComponentLayout layout1;
                TAknWindowComponentLayout layout2;

                // Read right (top in landscape) softkey layout.
                layout0 = AknLayoutScalable_Avkon::area_top_pane( 2 );
                layout1 = AknLayoutScalable_Avkon::stacon_top_pane();

                // If clock is shown in stacon, CBA area is smaller.
                TInt topCbaVariety = variety;
                TInt bottomCbaVariety = variety;
                if ( AknStatuspaneUtils::ExtendedStaconPaneActive() )
                    {
                    topCbaVariety += 4;
                    bottomCbaVariety += 2;
                    }
                
                layout2 = AknLayoutScalable_Avkon::control_top_pane_stacon( topCbaVariety );
        
                TAknWindowLineLayout rightSoftkeyLayout(
                    DoCompose( layout0,
                               DoCompose( layout1, layout2 ) ).LayoutLine() );

                TAknLayoutRect rightSoftkeyLayoutRect;
                rightSoftkeyLayoutRect.LayoutRect( rect, rightSoftkeyLayout );
                TRect rightSoftKeyRect( rightSoftkeyLayoutRect.Rect() );

                // Read left (bottom in landscape) softkey layout.
                layout0 = AknLayoutScalable_Avkon::area_bottom_pane( 2 );
                layout1 = AknLayoutScalable_Avkon::stacon_bottom_pane();                
                layout2 = AknLayoutScalable_Avkon::control_bottom_pane_stacon( bottomCbaVariety );
        
                TAknWindowLineLayout leftSoftkeyLayout(
                    DoCompose( layout0,
                               DoCompose( layout1, layout2 ) ).LayoutLine() );

                TAknLayoutRect leftSoftkeyLayoutRect;
                leftSoftkeyLayoutRect.LayoutRect( rect, leftSoftkeyLayout );
                TRect leftSoftKeyRect( leftSoftkeyLayoutRect.Rect() );

                boundingRegion.SubRect( leftSoftKeyRect );
                boundingRegion.SubRect( rightSoftKeyRect );
                
                TInt count = boundingRegion.Count();
                
                TRect largestBoundingRect( 0, 0, 0, 0 );
                TRect boundingRect( 0, 0, 0, 0 );
                for ( TInt j = 0; j < count; j++ )
                    {
                    boundingRect = boundingRegion[j];
                    if ( boundingRect.Height() >= largestBoundingRect.Height() )
                        {
                        largestBoundingRect = boundingRect;
                        }
                    }
                
                // Return largest bounding rect.
                aBoundingRect = largestBoundingRect;
                boundingRegion.Close();    
                }
            }   
        }
    }


CCoeControl* CEikCba::GroupControlById(TInt aCommandId)
    {
    return ButtonById(aCommandId);
    }


CCoeControl* CEikCba::GroupControlById(TInt aCommandId) const
    {
    return ButtonById(aCommandId);
    }

TInt CEikCba::CommandId(TInt aCommandPos) const
    {
    return (*iControlArray)[aCommandPos].iId;
    }

TInt CEikCba::ButtonCount() const
    {
    return (iControlArray->Count()-1); // -1 for scroll bar;
    }

CEikCommandButton* CEikCba::GroupControlAsButton(TInt /*aCommandId*/) const 
    {
    // It is not possible to convert a CBA button to a CEikCommandButton.
    // Please use an interface that does not use a CEikCommandButton conversion,
    // e.g. CEikButtonGroupContainer::SetCommandL().
#if defined(_DEBUG)
    Panic(EEikPanicCBACannotConvertToCEikCommandButton);
#endif
    return NULL;
    }

TUint CEikCba::ButtonGroupFlags() const 
    {
    return iCbaFlags ;
    }

EXPORT_C void CEikCba::SetButtonGroupFlags(TInt aFlags)
    {
    iCbaFlags = aFlags;
    if (( iCbaFlags & EEikCbaFlagTransparent || iCbaFlags & EEikCbaFlagSemiTransparent ) && 
            CAknEnv::Static()->TransparencyEnabled() )
        {
        Window().SetRequiredDisplayMode( EColor16MA );
        TInt err = Window().SetTransparencyAlphaChannel();
        if( err == KErrNone )
            {
            Window().SetBackgroundColor( ~0 );
            if ( iExtension && iExtension->iEnablePostingTransparency )
                {
               	iExtension->iEnablePostingTransparency = EFalse;        	
               	delete iExtension->iLskPostingOverlayBitmap;
               	iExtension->iLskPostingOverlayBitmap = NULL;
               	delete iExtension->iRskPostingOverlayBitmap;
               	iExtension->iRskPostingOverlayBitmap = NULL;
               	BroadcastPostingTransparency( EFalse );
               	}           
            }
        else
            {
            iCbaFlags &= ~EEikCbaFlagTransparent;
            }       
        }
    else
        {
        iCbaFlags &= ~EEikCbaFlagTransparent;
        }
    if ( iCbaFlags & EEikCbaFlagSemiTransparent )
        {
        if ( iExtension )
            {
            iExtension->iSemiBgID = KAknsIIDQsnHomeBgWidget;
            iExtension->iSemiBgCenterID = KAknsIIDQsnHomeBgWidgetCenter;
            }
        }
    else
        {
        if ( iExtension )
            {
            iExtension->iSemiBgID = KAknsIIDNone;
            iExtension->iSemiBgCenterID = KAknsIIDNone;
            }
        }
    
    UpdateFonts();
    }

// -----------------------------------------------------------------------------
// CEikCba::SetSkinBackgroundId
//
// -----------------------------------------------------------------------------
//
EXPORT_C void CEikCba::SetSkinBackgroundId( const TAknsItemID& aIID )
    {
    // Skin background is not drawn by embedded CBA.
    if ( iFlags.IsSet( ECbaEmbedded ) )
        {
        return;
        }

    if ( iBgIID != KAknsIIDNone )
        {
        if ( iBgIID != aIID )
            {
            TRAP_IGNORE( iExtension->UpdateSoftkeyFrameL( EFalse ) );
            }

        iBgIID = aIID;
        iExtension->iCbaBgIIDSetExt = ETrue;
        }

    if ( iMLBgContext )
        {
        DoSetLayers( aIID );

        if ( aIID.iMajor == KAknsIIDQsnBgAreaControlPopup.iMajor &&
             aIID.iMinor == KAknsIIDQsnBgAreaControlPopup.iMinor )
            {
            iPopupVisible = ETrue;
            }
        else
            {
            iPopupVisible = EFalse;
            }
            
        }
        
    CheckSkinAndUpdateContext();
    
    if ( AknStatuspaneUtils::ExtendedFlatLayoutActive() )
        {
        // Clock and indicator pane area must be removed from
        // this window in extended flat layout.
        SetBoundingRect( TRect(0,0,0,0) ); // dummy parameter 
        }
        
    CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
        
    if ( statusPane &&
         ( iIsClockIndicBgIIDSet &&
           iBgIID == KAknsIIDQsnBgAreaControlMp &&
           statusPane->CbaAreaBackgroundID() != iBgIID ) ||
         ( iBgIID == KAknsIIDQsnBgAreaControlMp &&
           AknLayoutFlags() & EAknLayoutCbaInRightPane ) )
        {
        statusPane->SetCbaAreaBackgroundID(
            iBgIID,
            CEikStatusPaneBase::EDrawDeferred );
        }
    }

TKeyResponse CEikCba::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    if (aType != EEventKey)
        {
        return EKeyWasNotConsumed;
        }

    // Return immediately if the control is invisible.
    if (!IsVisible() && !(iCbaFlags&EAknCBAFlagRespondWhenInvisible))
        {
        return EKeyWasNotConsumed;
        }

    TBool shiftControlPressed = 
        (aKeyEvent.iModifiers & EModifierShift) ||
        (aKeyEvent.iModifiers & EModifierLeftShift) ||
        (aKeyEvent.iModifiers & EModifierRightShift) ||
        (aKeyEvent.iModifiers & EModifierCtrl) || 
        (aKeyEvent.iModifiers & EModifierRightCtrl);  

    TKeyResponse response(EKeyWasNotConsumed);

    // AknLaf - changed to use keys defined in AknKeys.h.
    // Left soft key will be returned also when MSK is enabled but not defined.
    if (aKeyEvent.iCode == EKeyCBA1)
        {
        if (KControlArrayCBAButton1Posn < iControlArray->Count())
            {
            // Return immediately if the button is invisible                        
            if ( (*iControlArray)[KControlArrayCBAButton1Posn].iControl &&
                 !(*iControlArray)[KControlArrayCBAButton1Posn].iControl->IsVisible() && 
                 !(iCbaFlags & EAknCBAFlagRespondWhenInvisible) )
                {
                return EKeyWasConsumed;
                }
            TInt shortCommand = (*iControlArray)[KControlArrayCBAButton1Posn].iId;
            TInt longCommand = (*iControlArray)[KControlArrayCBAButton1Posn].iLongId;

            // This will pass key event to application - no softkey command is processed.
            if (shortCommand == EAknSoftkeyForwardKeyEvent)
                {
                return EKeyWasNotConsumed;
                }

            if (aKeyEvent.iRepeats == 0 && shortCommand)
                {
                iCommandObserver->ProcessCommandL((TInt)shortCommand);
                }
            else if (longCommand)
                {
                iCommandObserver->ProcessCommandL((TInt)longCommand);
                }
            response = EKeyWasConsumed;
            }
        }
    else if (aKeyEvent.iCode == EKeyCBA2)
        {
        if (KControlArrayCBAButton2Posn < iControlArray->Count())
            {
            // Return immediately if the button is invisible.
            if ( (*iControlArray)[KControlArrayCBAButton2Posn].iControl &&
                 !(*iControlArray)[KControlArrayCBAButton2Posn].iControl->IsVisible() && 
                 !(iCbaFlags&EAknCBAFlagRespondWhenInvisible) )
                {
                return EKeyWasConsumed;
                }
            TInt shortCommand = (*iControlArray)[KControlArrayCBAButton2Posn].iId;
            TInt longCommand = (*iControlArray)[KControlArrayCBAButton2Posn].iLongId;

            if (!shortCommand && (aKeyEvent.iModifiers & EModifierKeyboardExtend)
                && (aKeyEvent.iScanCode == EStdKeyDevice1))
                {
                shortCommand = EEikBidCancel;
                }
            
            // This will pass key event to application - no softkey command is processed.
            if (shortCommand == EAknSoftkeyForwardKeyEvent)
                {
                return EKeyWasNotConsumed;
                }

            if (aKeyEvent.iRepeats == 0 && shortCommand)
                {
                iCommandObserver->ProcessCommandL((TInt)shortCommand);
                }
            else if (longCommand)
                {
                iCommandObserver->ProcessCommandL((TInt)longCommand);
                }
            response=EKeyWasConsumed;
            }
        }
    // Only take care of MSK if there has been something set to MSK (so that this doesn't break old 
    // cbas with only left and right softkeys set).

    // Do not handle key events with middle softkey if single click is enabled
    else if ( iFlags.IsClear( ECbaSingleClickEnabled )
                && AknLayoutUtils::MSKEnabled()
                && iMSKset
                && aKeyEvent.iCode == EKeyOK
                && !Window().IsFaded() )
        {
        if (KControlArrayCBAButtonMSKPosn < iControlArray->Count())
            {
            // Return immediately if the button is invisible.
            if ( (*iControlArray)[KControlArrayCBAButtonMSKPosn].iControl &&
                 !(*iControlArray)[KControlArrayCBAButtonMSKPosn].iControl->IsVisible() && 
                 !(iCbaFlags&EAknCBAFlagRespondWhenInvisible) )
                {
                return EKeyWasConsumed;
                }

            TInt shortCommand = (*iControlArray)[KControlArrayCBAButtonMSKPosn].iId;
            TInt longCommand = (*iControlArray)[KControlArrayCBAButtonMSKPosn].iLongId;

            // This will pass key event to application - no softkey command is processed.
            if (shortCommand == EAknSoftkeyForwardKeyEvent)
                {
                return EKeyWasNotConsumed;
                }

            if (aKeyEvent.iRepeats == 0 && shortCommand)
                {
                if (iMSKCommandObserver)
                    {
                    iMSKCommandObserver->ProcessCommandL(shiftControlPressed ? 
                        EAknSoftkeyShiftMSK : (TInt)shortCommand);
                    }
                // MSK observer handles shift, no normal MSK after that.
                if (!(iMSKCommandObserver && shiftControlPressed))
                    {
                    iCommandObserver->ProcessCommandL((TInt)shortCommand);
                    }
                }
            else if (longCommand)
                {
                if (iMSKCommandObserver)
                    {
                    iMSKCommandObserver->ProcessCommandL(shiftControlPressed ? 
                        EAknSoftkeyShiftMSK : (TInt)longCommand);
                    }
                // MSK observer handles shift, no normal MSK after that.
                if (!(iMSKCommandObserver && shiftControlPressed))
                    {
                    iCommandObserver->ProcessCommandL((TInt)longCommand);
                    }
                }
            response=EKeyWasConsumed;
            }
        }
    // If MSK is enabled but not defined, we return left softkey.
    // Do not handle key events with middle softkey if single click is enabled
    else if ( iFlags.IsClear( ECbaSingleClickEnabled )
                && AknLayoutUtils::MSKEnabled()
                && !iMSKset
                && aKeyEvent.iCode == EKeyOK
                && !Window().IsFaded() )
        {
        if (KControlArrayCBAButton1Posn < iControlArray->Count())
            {
            // Return immediately if the button is invisible.                      
            if ( (*iControlArray)[KControlArrayCBAButton1Posn].iControl &&
                !(*iControlArray)[KControlArrayCBAButton1Posn].iControl->IsVisible() && 
                !(iCbaFlags&EAknCBAFlagRespondWhenInvisible) )
                {
                return EKeyWasConsumed;
                }

            TInt shortCommand = (*iControlArray)[KControlArrayCBAButton1Posn].iId;
            TInt longCommand = (*iControlArray)[KControlArrayCBAButton1Posn].iLongId;

            // This will pass key event to application - no softkey command is processed.
            if (shortCommand == EAknSoftkeyForwardKeyEvent)
                {
                return EKeyWasNotConsumed;
                }

            if (aKeyEvent.iRepeats == 0 && shortCommand)
                {
                // Send shift + MSK to (listbox) observer even if MSK is not defined.
                if (iMSKCommandObserver && shiftControlPressed)
                    {
                    iMSKCommandObserver->ProcessCommandL(EAknSoftkeyShiftMSK);
                    }
                else
                    {
                    iCommandObserver->ProcessCommandL((TInt)shortCommand);
                    }
                }
            else if (longCommand)
                {
                // Send shift + MSK to (listbox) observer even if MSK is not defined.
                if (iMSKCommandObserver && shiftControlPressed)
                    {
                    iMSKCommandObserver->ProcessCommandL(EAknSoftkeyShiftMSK);
                    }
                else
                    {
                    iCommandObserver->ProcessCommandL((TInt)longCommand);
                    }
                }
            response = EKeyWasConsumed;
            }
        }
        
    return response;
    }

EXPORT_C void* CEikCba::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }


// ---------------------------------------------------------------------------
// Handles pointer events by passing the event to component controls by using
// the base class functionality. In addition this function notifies the
// command observer if a cba button was tapped.
// ---------------------------------------------------------------------------
//
void CEikCba::HandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    if ( !AknLayoutUtils::PenEnabled() )
        {
        return;
        }
    else if ( iFlags.IsSet( ECbaInsideDialog ) )
        {
        CCoeControl::HandlePointerEventL( aPointerEvent );
        return;
        }

    // If a child control is grabbing the pointer, we store the object pointer
    // before calling base class implementation. This is because the up event 
    // releases the pointer grab.
    CCoeControl* grabber = GrabbingComponent();

    // Default base class functionality passes event to child controls.
    CCoeControl::HandlePointerEventL( aPointerEvent );

    // If pointer up event occurred in child control which was grabbing
    // the pointer, it means that the CBA button was clicked.
    
    CEikCbaButton* button1 =
        static_cast<CEikCbaButton*>(
            (*iControlArray)[KControlArrayCBAButton1Posn].iControl );
    CEikCbaButton* button2 =
        static_cast<CEikCbaButton*>(
            (*iControlArray)[KControlArrayCBAButton2Posn].iControl );
    CEikCbaButton* buttonMSK = NULL;
    
    if ( iMSKset && AknLayoutUtils::MSKEnabled() )
        {
        buttonMSK =
            static_cast<CEikCbaButton*>(
                (*iControlArray)[KControlArrayCBAButtonMSKPosn].iControl );
        }
    
    TRect button1Rect;
    TRect button2Rect;
    TRect buttonMSKRect;
    
    if ( AknLayoutFlags() & EAknLayoutCbaInRightPane )
        {
        button1Rect = ButtonRectByPosition( KControlArrayCBAButton1Posn, ETrue );
        button2Rect = ButtonRectByPosition( KControlArrayCBAButton2Posn, ETrue );
        }
    else if ( AknLayoutFlags() & EAknLayoutCbaInControlPane )
        {
        button1Rect   = ButtonRectByPosition( KControlArrayCBAButton1Posn, EFalse );
        button2Rect   = ButtonRectByPosition( KControlArrayCBAButton2Posn, EFalse );
        buttonMSKRect = ButtonRectByPosition( KControlArrayCBAButtonMSKPosn, EFalse );
        }
    else
        {
        button1Rect = button1->Rect();    
        button2Rect = button2->Rect();
        buttonMSKRect = TRect( 0,0,0,0 );
        }   

    // This flag is used to determine whether a pointer hit has
    // happened in the grabbing control. It is needed to prevent
    // the event from passing from one softkey to another.
    TBool noHits = EFalse;

    TBool buttonMSKDown = EFalse;
    TBool button1Down = button1->PressedDown();
    TBool button2Down = button2->PressedDown();
    if ( buttonMSK )
        {
        buttonMSKDown = buttonMSK->PressedDown();
        }

    TBool button1Empty = EFalse;
    if ( !button1->IsImageOn() && button1->IsEmptyText() )
        {
        button1Empty = ETrue;
        }
        
    TBool button2Empty = EFalse;
    if ( !button2->IsImageOn() && button2->IsEmptyText() )
        {
        button2Empty = ETrue;
        }
    
    TBool buttonMSKEmpty = EFalse;
    if ( buttonMSK && !buttonMSK->IsImageOn() && buttonMSK->IsEmptyText() )
        {
        buttonMSKEmpty = ETrue;
        }

    // If hits the left softkey.
    if ( button1Rect.Contains( aPointerEvent.iPosition ) && !button1Empty )
        {
        if ( button1->IsVisible() )
            {
            if ( aPointerEvent.iType == TPointerEvent::EButton1Down )
                {
                button1->SetPressedDown( ETrue );

                // Store the pointer of the button control to be
                // used as the grabbing control, this is required
                // in case the pointer events happens in the extended
                // touch area where the button control doesn't receive 
                // the grab otherwise.
                iExtension->iPointerGrabbingButton = button1;
                }
            else if ( aPointerEvent.iType == TPointerEvent::EButton1Up &&
                      button1->PressedDown() )
                {
                // Accept the up event only if the down event has happened
                // in the same button.
                button1->SetPressedDown( EFalse );
                grabber = iExtension->iPointerGrabbingButton;
                
                // Clear the grabber pointer at up event.
                iExtension->iPointerGrabbingButton = NULL;
                }
            else if ( aPointerEvent.iType == TPointerEvent::EDrag )
                {
                if ( iExtension->iPointerGrabbingButton == button1 )
                    {
                    // Accept the drag event only if the down event has happened
                    // in the same button.
                    button1->SetPressedDown( ETrue );
                    button2->SetPressedDown( EFalse);
                    if ( buttonMSK )
                        {
                        buttonMSK->SetPressedDown( EFalse );
                        }            
                    }
                else
                    {
                    // Don't transfer the event to this button.
                    noHits = ETrue;
                    }
                }
            else
                {
                // The event happened outside the button areas
                // or up event happened inside a button which
                // didn't get the down event.
                noHits = ETrue;
                }
            }
        else
            {
            // Button is inactive
            noHits = ETrue;
            }
        }
    else if ( button2Rect.Contains( aPointerEvent.iPosition ) && !button2Empty )
        {              
        if ( button2->IsVisible() )
            {
            if ( aPointerEvent.iType == TPointerEvent::EButton1Down )
                {
                button2->SetPressedDown( ETrue );
                
                // Store the pointer of the button control to be
                // used as the grabbing control, this is required
                // in case the pointer events happens in the extended
                // touch area where the button control doesn't receive 
                // the grab otherwise.
                iExtension->iPointerGrabbingButton = button2;
                }
            else if ( aPointerEvent.iType == TPointerEvent::EButton1Up &&
                      button2->PressedDown() )
                {
                // Accept the up event only if the down event has happened
                // in the same button.
                button2->SetPressedDown( EFalse );
                grabber = iExtension->iPointerGrabbingButton;
                
                // Clear the grabber pointer at up event.
                iExtension->iPointerGrabbingButton = NULL;
                }
            else if ( aPointerEvent.iType == TPointerEvent::EDrag )
                {
                if ( iExtension->iPointerGrabbingButton == button2 )
                    {
                    // Accept the drag event only if the down event has happened
                    // in the same button.
                    button2->SetPressedDown( ETrue );
                    button1->SetPressedDown( EFalse);
                    if ( buttonMSK )
                        {
                        buttonMSK->SetPressedDown( EFalse );
                        }
                    }
                else
                    {
                    // Don't transfer the event to this button.
                    noHits = ETrue;
                    }
                }
            else
                {
                // The event happened outside the button areas
                // or up event happened inside a button which
                // didn't get the down event.
                noHits = ETrue;
                }
            }
        else
            {
            // Button is inactive
            noHits = ETrue;
            }
        }
    else if ( buttonMSK &&
              !buttonMSKEmpty &&
              buttonMSKRect.Contains( aPointerEvent.iPosition ) )
        {
        if  ( buttonMSK->IsVisible() )
            {
            if ( aPointerEvent.iType == TPointerEvent::EButton1Down )
                {
                buttonMSK->SetPressedDown( ETrue );
                
                // Store the pointer of the button control to be
                // used as the grabbing control, this is required
                // in case the pointer events happens in the extended
                // touch area where the button control doesn't receive 
                // the grab otherwise.
                iExtension->iPointerGrabbingButton = buttonMSK;
                }
            else if ( aPointerEvent.iType == TPointerEvent::EButton1Up &&
                      buttonMSK->PressedDown() )
                {
                // Accept the up event only if the down event has happened
                // in the same button.
                buttonMSK->SetPressedDown( EFalse );
                grabber = iExtension->iPointerGrabbingButton;
                
                // Clear the grabber pointer at up event.
                iExtension->iPointerGrabbingButton = NULL;
                }
            else if ( aPointerEvent.iType == TPointerEvent::EDrag )
                {
                if ( iExtension->iPointerGrabbingButton == buttonMSK )
                    {
                    // Accept the drag event only if the down event has happened
                    // in the same button.
                    buttonMSK->SetPressedDown( ETrue );
                    button2->SetPressedDown( EFalse );
                    button1->SetPressedDown( EFalse );
                    }
                else
                    {
                    // Don't transfer the event to this button.
                    noHits = ETrue;
                    }
                }
            else
                {
                // The event happened outside the button areas
                // or up event happened inside a button which
                // didn't get the down event.
                noHits = ETrue;
                }
            }
        else
            {
            // Button is inactive
            noHits = ETrue;
            }
        }
    else
        {
        if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
            {
            // Clear the grabber pointer at up event.
            iExtension->iPointerGrabbingButton = NULL;
            }

        noHits = ETrue;
        }
    
    if ( noHits )
        {
        button1->SetPressedDown( EFalse );
        button2->SetPressedDown( EFalse );
        if ( buttonMSK )
            {
            buttonMSK->SetPressedDown( EFalse );
            }
        }
    else if ( aPointerEvent.iType != TPointerEvent::EDrag )
        {
        // CBA button has been hit with a down or up event, play feedback
        MTouchFeedback* feedback = MTouchFeedback::Instance();
        if ( feedback )
            {
            TTouchFeedbackType fbType = TTouchFeedbackType( ETouchFeedbackAudio |
                                                            ETouchFeedbackVibra );
            if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
                {
                fbType = ETouchFeedbackVibra;
                }
            feedback->InstantFeedback( this,
                                       ETouchFeedbackBasicButton,
                                       fbType,
                                       aPointerEvent );
            }
        }
        
    if (button1Down != button1->PressedDown() ||
        button2Down != button2->PressedDown() ||
        (buttonMSK && (buttonMSKDown != buttonMSK->PressedDown())))
        {
 
        if ( iFlags.IsSet( ECbaEmbedded ) )
            {
            UpdateLabels( EFalse );
            
            // Redraw only changed buttons. It's assumed that there's no
            // visible MSK if softkeys are embedded.
            TRect invalidRect( button1Rect );
            
            if ( button2Down != button2->PressedDown() )
                {
                invalidRect = button2Rect;
                }

            // TODO: whole control is redrawn as a workaround for NGA bug that
            // causes incorrect drawing of softkey labels when the second
            // button is pressed down after the first one has already been
            // pressed. Actually we should just redraw the invalidRect
            // calculated above.
            DrawNow();
            }
        else
            {
            SizeChanged();
            DrawNow();
            }
        }

    if ( !grabber && !noHits )
        {
        // Set the correct button to claim the pointer grab if the
        // event happened in an extended touch area of the button
        // (the button control didn't receive the event).
        grabber = iExtension->iPointerGrabbingButton;
        }

    if ( aPointerEvent.iType == TPointerEvent::EButton1Up && grabber && !noHits )
        {
        // This check also includes the extended touch space for a button.
        if ( ( button1Rect.Contains( aPointerEvent.iPosition ) &&
               button1Rect.Intersects( grabber->Rect() ) ) ||
             ( button2Rect.Contains( aPointerEvent.iPosition ) &&
               button2Rect.Intersects( grabber->Rect() ) ) ||
             ( buttonMSKRect.Contains( aPointerEvent.iPosition ) &&
               buttonMSKRect.Intersects( grabber->Rect() ) ) )
            {
            TInt buttoncount = iControlArray->Count();
            for ( TInt i = 0; i < buttoncount; i++ )
                {
                if ( (*iControlArray)[i].iControl == grabber )
                    {
                    if ( !IsVisible() )
                        return;
                    
                    // Send the button command to command observer.
                    TInt shortCommand = (*iControlArray)[i].iId;
                    if ( shortCommand &&
                         i == KControlArrayCBAButtonMSKPosn &&
                         iMSKCommandObserver )
                        {
                        iMSKCommandObserver->ProcessCommandL( shortCommand );
                        }

                    if( shortCommand )
                        {
                        iCommandObserver->ProcessCommandL( shortCommand );
                        }

                    break;
                    }
                }
            }
        }
    }


TSize CEikCba::MinimumSize()
    {
    TSize size = CEikControlGroup::MinimumSize();
    size.iWidth = iAvkonAppUi->ApplicationRect().Width();
    const TInt count = iControlArray->Count();
    for (TInt ii = 0; ii < count; ii++)
        {
        size.iHeight = Max(size.iHeight, (*iControlArray)[ii].iControl->MinimumSize().iHeight);
        }
    if (iLink)
        {
        size.iHeight = Max(size.iHeight, iLink->Size().iHeight);
        }
    // Add a standard margin from the laf.
    return size;
    }

/**
* Gets the list of logical colors employed in the drawing of the control,
* paired with an explanation of how they are used. Appends the list to aColorUseList.
*
* @since ER5U 
*/
void CEikCba::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const
    {
    CEikControlGroup::GetColorUseListL(aColorUseList);
        
    TInt commonAttributes = TCoeColorUse::ESurrounds|TCoeColorUse::EActive|TCoeColorUse::ENormal|
        TCoeColorUse::ENeutral;
        
    TCoeColorUse colorUse;

    colorUse.SetLogicalColor(EColorToolbarText);
    colorUse.SetUse(TCoeColorUse::EFore|commonAttributes);
    aColorUseList.AppendL(colorUse);

    colorUse.SetLogicalColor(EColorToolbarBackground);
    colorUse.SetUse(TCoeColorUse::EBack|commonAttributes);
    aColorUseList.AppendL(colorUse);
    }


// ---------------------------------------------------------------------------
// Handles a change to the control's resources of type aType
// which are shared across the environment, e.g. colors or fonts.
// ---------------------------------------------------------------------------
//
void CEikCba::HandleResourceChange( TInt aType )
    {
    CEikControlGroup::HandleResourceChange( aType );
    
    switch ( aType )
        {
        case KAknsMessageSkinChange: 
            {
            if ( IsVisible() )
                {
                DoSkinChange();
                if( iExtension->iIfMskIconSet )
                    {
                    TRAP_IGNORE( UpdateIconL() );
                    }
                }
            else
                {
                iFlags.Set( ECbaChangeRecordedSkin );
                }
            break;
            }

        case KEikColorResourceChange:
            {
            if ( IsVisible() )
                {
                DoColorChange();
                }
            else
                {
                iFlags.Set( ECbaChangeRecordedColor );
                }
            break;
            }

        case KEikDynamicLayoutVariantSwitch:
            {
            if ( IsVisible() )
                {
                DoLayoutChange();
                SetBoundingRect( TRect() );
                if ( iFlags.IsSet( ECbaInsideDialog )
                        || iFlags.IsSet( ECbaEmbedded ) )
                    {
                    DrawDeferred();
                    }
                else
                    {
                    DrawNow();  
                    }
                }
            else
                {
                iFlags.Set( ECbaChangeRecordedLayout );
                }
            break;
            }
                
        case KAknMessageFocusLost:
            {
            if ( iFlags.IsSet( ECbaInsideDialog ) )
                {
                return;
                }


            CEikCbaButton* button1 =
                static_cast<CEikCbaButton*>(
                    (*iControlArray)[KControlArrayCBAButton1Posn].iControl );
            CEikCbaButton* button2 =
                static_cast<CEikCbaButton*>(
                    (*iControlArray)[KControlArrayCBAButton2Posn].iControl );
            CEikCbaButton* buttonMSK = NULL;
            
            if ( iMSKset && AknLayoutUtils::MSKEnabled() )
                {
                buttonMSK =
                    static_cast<CEikCbaButton*>(
                        (*iControlArray)[KControlArrayCBAButtonMSKPosn].iControl );
                }
            
            TBool redrawNeeded( EFalse );
            
            if ( button1 && button1->PressedDown() )
                {
                button1->SetPressedDown( EFalse );
                redrawNeeded = ETrue;
                }
            if ( button2 && button2->PressedDown() )
                {
                button2->SetPressedDown( EFalse );
                redrawNeeded = ETrue;
                }
            if ( buttonMSK && buttonMSK->PressedDown() )
                {
                buttonMSK->SetPressedDown( EFalse );
                redrawNeeded = ETrue;
                }
            
            if ( buttonMSK && iExtension )
                {
                SetBoundingRect( TRect( 0, 0, 0, 0 ) );
                redrawNeeded = ETrue;                    
                }
            if ( redrawNeeded )
                {
                SizeChanged();
                DrawDeferred();
                }
            
            if ( iFlags.IsSet( ECbaItemSpecificSoftkeyInUse ) )
                {
                UpdateItemSpecificSoftkey( EFalse );
                }
            break;
            }

        case KEikMessageUnfadeWindows:
            {
            DoLayoutChange();
            SetFadeState();
            
            if ( iFlags.IsSet( ECbaInsideDialog ) )
                {
                DrawDeferred();
                }
            else
                {
                //When touch unsupported,it's unnecessary to call DrawNow()
                if ( AknLayoutUtils::PenEnabled() )
                    {
                    DrawNow();
                    }
                else
                    {
                    DrawDeferred();
                    }           
                }
                
            break;
            }

        case KEikMessageFadeAllWindows:
            {
            if ( AknLayoutUtils::PenEnabled() &&
                 AknStatuspaneUtils::IdleLayoutActive() )
                {
                SetMSKVisibility( MskAllowed() );
                }                
            SetFadeState();
            break;
            }

        default:
            {
            break;
            }
        }
    }


void CEikCba::DoSkinChange()
    {
    iExtension->iIfSkinChanged = ETrue;
    DoSetLayers( KAknsIIDNone );
    iExtension->iIfSkinChanged = EFalse;
    if ( iExtension )
        {
        TRAP_IGNORE( iExtension->UpdateSoftkeyFrameL( ETrue ) );
        }

    // This is required for skin resource changes (as well as color resource change).
    CheckSkinAndUpdateContext();
    TRAP_IGNORE( SetMSKIconL() );
    SizeChanged();
    
    //Skin change uses DrawNow to flus draw cache before layoutchange.
    DrawNow();
    iFlags.Clear(ECbaChangeRecordedSkin);
    }

void CEikCba::DoColorChange()
    {
    iBrushAndPenContext->SetBrushColor(iEikonEnv->ControlColor(EColorToolbarBackground, *this));
    iBrushAndPenContext->SetPenColor(iEikonEnv->ControlColor(EColorToolbarText, *this));
    Window().SetBackgroundColor(iEikonEnv->ControlColor(EColorToolbarBackground, *this));
    // This is required for skin resource changes (as well as color resource change).
    CheckSkinAndUpdateContext();
    TRAP_IGNORE( SetMSKIconL() );
    SizeChanged();
    iFlags.Clear(ECbaChangeRecordedColor);
    }


void CEikCba::DoLayoutChange()
    {
    SetBoundingRect( TRect() );

    UpdateFonts();

    TBool mskAllowed( MskAllowed() );
    if ( !mskAllowed )
        {
        SetMSKVisibility( EFalse );
        }
    else
        {
        SetMSKVisibility( ETrue );
        TRAP_IGNORE( SetMSKIconL() );
        }

    if ( iFlags.IsSet( ECbaEmbedded ) )
        {
        CEikCbaButton* button1 =
            static_cast<CEikCbaButton*>(
                (*iControlArray)[KControlArrayCBAButton1Posn].iControl );
        CEikCbaButton* button2 =
            static_cast<CEikCbaButton*>(
                (*iControlArray)[KControlArrayCBAButton2Posn].iControl );
        
        if ( button1 )
            {
            button1->SetPressedDown( EFalse );
            }

        if ( button2 )
            {
            button2->SetPressedDown( EFalse );
            }
        }
    
    SizeChanged();
    
    if ( iExtension )
        {
        TRAP_IGNORE( iExtension->UpdateSoftkeyFrameL( EFalse ) );
        }
        
    iFlags.Clear( ECbaChangeRecordedLayout );
    }


void CEikCba::HandleScrollEventL(CEikScrollBar* /*aScrollBar*/, TEikScrollEvent /*aEventType*/)
    {
    User::Leave(KErrNotSupported);
    }

TTypeUid::Ptr CEikCba::MopSupplyObject(TTypeUid aId)
    {
    if (aId.iUid == MAknsControlContext::ETypeId)
        {
        if ( AknLayoutFlags() & EAknLayoutCbaInControlPane ||
             AknLayoutFlags() & EAknLayoutCbaInRightPane )
            {
            return MAknsControlContext::SupplyMopObject( aId, iMLBgContext );
            }
        else
            {
            // Always provide top object to mop-chain.
            // Bottom is parent of Top, so bottom is re-drawn
            // automatically when top is drawn.
            return MAknsControlContext::SupplyMopObject( aId, iStaconBgContextTop );
            }
        }
        
    if ( aId.iUid == CEikCba::ETypeId )
        {
        return aId.MakePtr( this );
        }
        
    return CEikControlGroup::MopSupplyObject(aId);
    }


void CEikCba::Draw( const TRect& aRect ) const
    {
    // Embedded CBA doesn't draw anything
    if ( iFlags.IsSet( ECbaInsideDialog ) )
        {
        return;
        }

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    
    const TRect rect( Rect() );
    CWindowGc& gc = SystemGc();

    TRgb rgb( TRgb::Color16MA( 0 ) );
    gc.SetDrawMode( CGraphicsContext::EDrawModeWriteAlpha );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.SetBrushColor( rgb );        
    gc.Clear();
  
    MAknsControlContext* cc = iMLBgContext;
    
    if ( iFlags.IsSet( ECbaEmbedded ) )
        {
        // Embedded CBA is drawn inside dialog
        if ( AknLayoutUtils::PenEnabled() && iExtension )
            {
            if ( aRect.Intersects( iExtension->iLeftFrameOuterRect ) )
                {
                DrawEmbeddedSoftkey( 
                        iControlArray->At( KControlArrayCBAButton1Posn ),
                        iExtension->iLeftFrameOuterRect, 
                        gc, 
                        iExtension->iLeftFrameMask );
                }
            
            if ( aRect.Intersects( iExtension->iRightFrameOuterRect ) )
                {
                DrawEmbeddedSoftkey( 
                        iControlArray->At( KControlArrayCBAButton2Posn ),
                        iExtension->iRightFrameOuterRect, 
                        gc, 
                        iExtension->iRightFrameMask );
                }
            }
        } //ECbaEmbedded
    else if  ( AknLayoutFlags() & EAknLayoutCbaInControlPane )
        {
        if ( AknLayoutUtils::PenEnabled() || ( iCbaFlags & EEikCbaFlagTransparent)
            ||iExtension->iEnablePostingTransparency )
            {
            TAknLayoutRect layoutRect;
            TRect leftSKRect( iExtension->iLeftFrameOuterRect );
            TRect rightSKRect( iExtension->iRightFrameOuterRect );
            TRect middleSKRect( iExtension->iMiddleFrameOuterRect );

            TSize leftSKSize( leftSKRect.Size() );
            TSize rightSKSize( rightSKRect.Size() );
            TSize middleSKSize( middleSKRect.Size() );
            
            if ( iExtension &&
                 iExtension->iLskPostingOverlayBitmap && 
                 iExtension->iRskPostingOverlayBitmap )
                {
                // This code may be executed if iExtension->iEnablePostingTransparency 
                // holds. Draw graphics with mask information alpha channel for 
                // transparency for posting overlay
                gc.SetDrawMode( CGraphicsContext::EDrawModeWriteAlpha );
                gc.BitBlt( rightSKRect.iTl, iExtension->iRskPostingOverlayBitmap, 
                    TRect( rightSKSize ) );
                gc.BitBlt( leftSKRect.iTl, iExtension->iLskPostingOverlayBitmap, 
                    TRect( leftSKSize ) );
                }
            else if ( !( ( iCbaFlags & EEikCbaFlagTransparent) || ( iCbaFlags & EEikCbaFlagSemiTransparent))  )
                {// Old way to render
                if( !AknsDrawUtils::Background( skin, cc, this, gc, rect ) )
                    {
                    gc.SetPenStyle( CGraphicsContext::ENullPen );
                    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
                    gc.SetBrushColor( AKN_LAF_COLOR( KStatusPaneBackgroundGraphicsColorUsual ) );           
                    gc.DrawRect( rect );
                    }
                if ( iExtension )
                    {
                
                    CEikCbaButton* button1 = static_cast<CEikCbaButton*>(
                        (*iControlArray)[KControlArrayCBAButton1Posn].iControl );
                    CEikCbaButton* button2 = static_cast<CEikCbaButton*>(
                        (*iControlArray)[KControlArrayCBAButton2Posn].iControl );
                    
    		        if ( IsMskEnabledLayoutActive() )
                        {
                        CEikCbaButton* buttonMSK = static_cast<CEikCbaButton*>(
                            (*iControlArray)[KControlArrayCBAButtonMSKPosn].iControl );
                        
                        CFbsBitmap* middleMask =
                            AknsUtils::GetCachedBitmap( skin, KAknsIIDQgnIndiSctrlSkMaskMiddlePrt );
                        AknIconUtils::SetSize( middleMask, middleSKSize, EAspectRatioNotPreserved );

                        if( buttonMSK && buttonMSK->PressedDown() )
                            {
                            AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(),
                                                      gc,
                                                      iExtension->iMiddleFrameOuterRect,
                                                      iExtension->iMiddleFrameInnerRect,
                                                      KAknsIIDQgnFrSctrlSkButtonPressed,
                                                      KAknsIIDQgnFrSctrlSkButtonCenterPressed );
                            }
                        else
                            {
                            AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(),
                                                      gc,
                                                      iExtension->iMiddleFrameOuterRect,
                                                      iExtension->iMiddleFrameInnerRect,
                                                      KAknsIIDQgnFrSctrlSkButton,
                                                      KAknsIIDQgnFrSctrlSkButtonCenter);
                            }
                        
                        }

                    if( button1 && button1->PressedDown() )
                        {
                        AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(),
                                                  gc,
                                                  iExtension->iLeftFrameOuterRect,
                                                  iExtension->iLeftFrameInnerRect,
                                                  KAknsIIDQgnFrSctrlSkButtonPressed,
                                                  KAknsIIDQgnFrSctrlSkButtonCenterPressed );
                        }
                    else
                        {
                        AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(),
                                                  gc,
                                                  iExtension->iLeftFrameOuterRect,
                                                  iExtension->iLeftFrameInnerRect,
                                                  KAknsIIDQgnFrSctrlSkButton,
                                                  KAknsIIDQgnFrSctrlSkButtonCenter);
                        }

                    if( button2 && button2->PressedDown() )
                        {
                        AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(),
                                                  gc,
                                                  iExtension->iRightFrameOuterRect,
                                                  iExtension->iRightFrameInnerRect,
                                                  KAknsIIDQgnFrSctrlSkButtonPressed,
                                                  KAknsIIDQgnFrSctrlSkButtonCenterPressed );
                        }
                    else
                        {
                        AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(),
                                                  gc,
                                                  iExtension->iRightFrameOuterRect,
                                                  iExtension->iRightFrameInnerRect,
                                                  KAknsIIDQgnFrSctrlSkButton,
                                                  KAknsIIDQgnFrSctrlSkButtonCenter);
                        }

                    
                    }
                }
            }
        else
            {
            if ( !AknsDrawUtils::Background( skin, cc, this, gc, rect ) )
                {
                CEikControlGroup::Draw( aRect );
                }
            }
        }
    else if ( AknLayoutFlags() & EAknLayoutCbaInRightPane )
        {
        TRect bottomSKRect;
        TRect topSKRect;
        if ( iExtension )
            {
            bottomSKRect = iExtension->iLeftFrameOuterRect;
            topSKRect    = iExtension->iRightFrameOuterRect;
            }
        
        if ( iExtension &&
             iExtension->iLskPostingOverlayBitmap && 
             iExtension->iRskPostingOverlayBitmap )
            {
            // This code may be executed if iExtension->iEnablePostingTransparency 
            // holds. Draw graphics with mask information alpha channel for 
            // transparency for posting overlay
            gc.SetDrawMode( CGraphicsContext::EDrawModeWriteAlpha );
            gc.BitBlt( topSKRect.iTl, iExtension->iRskPostingOverlayBitmap, 
                TRect( topSKRect.Size() ) );
            gc.BitBlt( bottomSKRect.iTl, iExtension->iLskPostingOverlayBitmap, 
                TRect( bottomSKRect.Size() ) );
            }
        else if ( !( ( iCbaFlags & EEikCbaFlagTransparent) || ( iCbaFlags & EEikCbaFlagSemiTransparent))  )
            {
            // Old way to render
            if( !AknsDrawUtils::Background( skin, cc, this, gc, rect ) )
                {
                gc.SetPenStyle( CGraphicsContext::ENullPen );
                gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
                gc.SetBrushColor( AKN_LAF_COLOR( KStatusPaneBackgroundGraphicsColorUsual ) );           
                gc.DrawRect( rect );
                }
            
            // Draw the softkey frames.
            if ( iExtension )
                {
                
                 CEikCbaButton* button1 = static_cast<CEikCbaButton*>(
                    (*iControlArray)[KControlArrayCBAButton1Posn].iControl );
                CEikCbaButton* button2 = static_cast<CEikCbaButton*>(
                    (*iControlArray)[KControlArrayCBAButton2Posn].iControl );

                if ( button1 && button1->PressedDown() )
                    {
                    AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(),
                                              gc,
                                              iExtension->iLeftFrameOuterRect,
                                              iExtension->iLeftFrameInnerRect,
                                              KAknsIIDQgnFrSctrlSkButtonPressed,
                                              KAknsIIDQgnFrSctrlSkButtonCenterPressed );
                    }
                else
                    {
                    AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(),
                                              gc,
                                              iExtension->iLeftFrameOuterRect,
                                              iExtension->iLeftFrameInnerRect,
                                              KAknsIIDQgnFrSctrlSkButton,
                                              KAknsIIDQgnFrSctrlSkButtonCenter );
                    }

                if ( button2 && button2->PressedDown() )
                    {
                    AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(),
                                              gc,
                                              iExtension->iRightFrameOuterRect,
                                              iExtension->iRightFrameInnerRect,
                                              KAknsIIDQgnFrSctrlSkButtonPressed,
                                              KAknsIIDQgnFrSctrlSkButtonCenterPressed );
                    }
                else
                    {
                    AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(),
                                              gc,
                                              iExtension->iRightFrameOuterRect,
                                              iExtension->iRightFrameInnerRect,
                                              KAknsIIDQgnFrSctrlSkButton,
                                              KAknsIIDQgnFrSctrlSkButtonCenter );
                    }
                }
            }
        else if ( ( iCbaFlags & EEikCbaFlagSemiTransparent) && iExtension )
            {
            if ( iExtension->iSemiBgID != KAknsIIDNone )
                {
                iExtension->DrawSemiTransparencyL( gc, rect );
                }
            }
        else
            {
            // No background since EEikCbaFlagTransparent is set.
            // Do nothing.
            }
        }
    else
        {
        // Combined statusp and control pane

        TRect screen( iAvkonAppUi->ApplicationRect() );

        TInt variety = 0;
        if ( AknLayoutFlags() & EAknLayoutCbaInStaconPaneLeft )
            {
            variety = 1;
            }

        TAknWindowComponentLayout layout0;
        TAknWindowComponentLayout layout1;
        TAknWindowComponentLayout layout2;

        // Read right (top in landscape) softkey layout.
        layout0 = AknLayoutScalable_Avkon::area_top_pane( 2 );
        layout1 = AknLayoutScalable_Avkon::stacon_top_pane();

        // If clock is shown in stacon, cba area is smaller.
        TInt topCbaVariety = variety;
        if ( AknStatuspaneUtils::ExtendedStaconPaneActive() )
            {
            topCbaVariety += 4;
            }

        layout2 = AknLayoutScalable_Avkon::control_top_pane_stacon( topCbaVariety );

        TAknWindowLineLayout rightSoftkeyLayout(
            DoCompose( layout0,DoCompose( layout1, layout2 ) ).LayoutLine() );

        TAknLayoutRect rightSoftkeyLayoutRect;
        rightSoftkeyLayoutRect.LayoutRect( screen, rightSoftkeyLayout );

        // Read left (bottom in landscape) softkey layout.
        layout0 = AknLayoutScalable_Avkon::area_bottom_pane( 2 );
        layout1 = AknLayoutScalable_Avkon::stacon_bottom_pane();

        // If clock is shown in stacon, cba area is smaller.
        TInt bottomCbaVariety = variety;
        if ( AknStatuspaneUtils::ExtendedStaconPaneActive() )
            {
            bottomCbaVariety += 2;
            }

        layout2 =
            AknLayoutScalable_Avkon::control_bottom_pane_stacon(
                bottomCbaVariety );

        TAknWindowLineLayout leftSoftkeyLayout(
            DoCompose( layout0, DoCompose( layout1, layout2 ) ).LayoutLine() );

        TAknLayoutRect leftSoftkeyLayoutRect;
        leftSoftkeyLayoutRect.LayoutRect( screen, leftSoftkeyLayout );

        TRect staconBottom( leftSoftkeyLayoutRect.Rect() );

        // First draw bottom area.
        cc = iStaconBgContextBottom;

        if ( iExtension && iExtension->iLskPostingOverlayBitmap )
            {
            // This code may be executed if iExtension->iEnablePostingTransparency
            // holds. Draw graphics with mask information alpha channel for
            // transparency for posting overlay
            gc.SetDrawMode( CGraphicsContext::EDrawModeWriteAlpha );

            gc.BitBlt( staconBottom.iTl, iExtension->iLskPostingOverlayBitmap,
                TRect( staconBottom.Size() ) );
            }
        else if ( !( iCbaFlags & EEikCbaFlagTransparent) )
            {
            if( !AknsDrawUtils::Background( skin, cc, this, gc, staconBottom ) )
                {
                gc.SetPenStyle(CGraphicsContext::ENullPen);
                gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
                gc.SetBrushColor(AKN_LAF_COLOR(KStatusPaneBackgroundGraphicsColorUsual));
                gc.DrawRect(staconBottom);
                }
            if ( iExtension )
                {
                CEikCbaButton* button1 = static_cast<CEikCbaButton*>(
                    (*iControlArray)[KControlArrayCBAButton1Posn].iControl );

                if ( button1 && button1->PressedDown() )
                    {
                    AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(),
                                              gc,
                                              iExtension->iLeftFrameOuterRect,
                                              iExtension->iLeftFrameInnerRect,
                                              KAknsIIDQgnFrSctrlSkButtonPressed,
                                              KAknsIIDQgnFrSctrlSkButtonCenterPressed );
                    }
                else
                    {
                    AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(),
                                              gc,
                                              iExtension->iLeftFrameOuterRect,
                                              iExtension->iLeftFrameInnerRect,
                                              KAknsIIDQgnFrSctrlSkButton,
                                              KAknsIIDQgnFrSctrlSkButtonCenter );
                    }
                }
            }
        // Then top area.
        cc = iStaconBgContextTop;        

        TRect staconTop( rightSoftkeyLayoutRect.Rect() );

        if ( iExtension && iExtension->iRskPostingOverlayBitmap )
            {
            // This code may be executed if iExtension->iEnablePostingTransparency
            // holds. Draw graphics with mask information alpha channel for
            // transparency for posting overlay
            gc.SetDrawMode( CGraphicsContext::EDrawModeWriteAlpha );

            gc.BitBlt( staconTop.iTl, iExtension->iRskPostingOverlayBitmap,
                TRect( staconTop.Size() ) );
            }
        else if ( !( iCbaFlags & EEikCbaFlagTransparent) )
            {
            if( !AknsDrawUtils::Background( skin, cc, this, gc, staconTop ) )
                {
                gc.SetPenStyle(CGraphicsContext::ENullPen);
                gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
                gc.SetBrushColor(AKN_LAF_COLOR(KStatusPaneBackgroundGraphicsColorUsual));
                gc.DrawRect(staconTop);
                }
            if ( iExtension )
                {

                CEikCbaButton* button2 = static_cast<CEikCbaButton*>(
                    (*iControlArray)[KControlArrayCBAButton2Posn].iControl );

                if ( button2 && button2->PressedDown() )
                    {
                    AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(),
                                              gc,
                                              iExtension->iRightFrameOuterRect,
                                              iExtension->iRightFrameInnerRect,
                                              KAknsIIDQgnFrSctrlSkButtonPressed,
                                              KAknsIIDQgnFrSctrlSkButtonCenterPressed );
                    }
                else
                    {
                    AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(),
                                              gc,
                                              iExtension->iRightFrameOuterRect,
                                              iExtension->iRightFrameInnerRect,
                                              KAknsIIDQgnFrSctrlSkButton,
                                              KAknsIIDQgnFrSctrlSkButtonCenter );
                    }
                }
            }
        }
    gc.SetOpaque( EFalse );        
    }


// ---------------------------------------------------------------------------
// Gets a button control by the specified command ID.
// ---------------------------------------------------------------------------
//
CCoeControl* CEikCba::ButtonById( TInt aCommandId ) const
    {
    return ControlById( aCommandId );
    }


// ---------------------------------------------------------------------------
// Creates the scroll bar frame & sets up the scroll bar.
// ---------------------------------------------------------------------------
//
void CEikCba::CreateScrollBarFrameL()
    {
    if ( !iSBFrame )
        {
        iSBFrame = new (ELeave) CEikCbaScrollBarFrame( this, this, ETrue );
        }
    iSBFrame->ConstructL();
    }


TEikGroupControl CEikCba::VScrollBarAsGroupControl()
    {
    // Extracts vertical scroll bar from the scroll bar frame.       
    TEikGroupControl groupCtrl(iSBFrame->VerticalScrollBar(), 0, 
        KCbaScrollBarButtonWidth,TEikGroupControl::ESetLength);
    return groupCtrl;
    }

void CEikCba::InsertScrollBarL()
    {
    TEikGroupControl SBGroupCtrl = VScrollBarAsGroupControl();
    // Insert vertical scroll bar into cba control group.
    InsertControlL(SBGroupCtrl, KControlArrayScrollBarPosn);
    }


// ---------------------------------------------------------------------------
// Replaces empty scroll bar with actual arrow head scroll bar.
// ---------------------------------------------------------------------------
//
void CEikCba::CreateArrowHeadScrollBarL()
    {
    if ( iSBFrame )
        {
        iSBFrame->SwitchToArrowHeadScrollBarL();
        iSBFrame->VerticalScrollBar()->SetContainingCba( this );
        if ( iControlArray->Count() > KControlArrayScrollBarPosn )
            {
            iControlArray->Delete( KControlArrayScrollBarPosn );
            }
        InsertScrollBarL();
        }
    }


void CEikCba::SizeChanged()
    {
    if ( iFlags.IsSet( ECbaInsideDialog ) )
        {
        Window().SetNonFading( EFalse );
        SizeChangedInsideDialog();
        return;
        }
    else if ( iFlags.IsSet( ECbaEmbedded ) )
        {
        Window().SetNonFading( EFalse );
        SizeChangedInPopup();
        return;
        }
        
    const TInt aknLayoutFlags = AknLayoutFlags();

    if ( aknLayoutFlags & EAknLayoutCbaInControlPane )
        {
        Window().SetNonFading( EFalse );
        SizeChangedInControlPane();
        }
    else if ( aknLayoutFlags & EAknLayoutCbaInRightPane )
        {
        Window().SetNonFading( EFalse );
        SizeChangedInRightPane();
        }
    else
        {
        Window().SetNonFading(ETrue);
        SizeChangedInStaconPane();
        }
    // Set the feedback areas for the softkeys.
    if ( iExtension && iExtension->iEnablePostingTransparency )
        {
        TBool enabled = 
        //    AknLayoutUtils::PenEnabled() &&
      //      ( AknLayoutFlags() & EAknLayoutCbaInRightPane ) &&
            !Rect().IsEmpty();

        if ( enabled )
            {
            CEikCbaButton* button1 =
                static_cast<CEikCbaButton*>(
                    (*iControlArray)[KControlArrayCBAButton1Posn].iControl );
            CEikCbaButton* button2 =
                static_cast<CEikCbaButton*>(
                    (*iControlArray)[KControlArrayCBAButton2Posn].iControl );

            TInt leftId = (*iControlArray)[KControlArrayCBAButton1Posn].iId;
        
            TRAPD( err, iExtension->UpdatePostingOverlayBitmapsL(
                    Rect(),
                    button1,
                    button2,
                    aknLayoutFlags ) );

            if ( err )
                {
                // Bitmaps may not be up-to-date.
                enabled = EFalse;
                }
            }
        
        if ( !enabled )
            {
            // Delete and disable posting overlay support.
            delete iExtension->iLskPostingOverlayBitmap;
            iExtension->iLskPostingOverlayBitmap = NULL;
            delete iExtension->iRskPostingOverlayBitmap;
            iExtension->iRskPostingOverlayBitmap = NULL;
            }

        // Broadcast current state to CEikCbaButtons
        BroadcastPostingTransparency( enabled );
        }
    }

// -----------------------------------------------------------------------------
// CEikCba::CheckSkinAndUpdateContext
//
// -----------------------------------------------------------------------------
//
void CEikCba::CheckSkinAndUpdateContext()
    {
    if (AknsUtils::SkinInstance())
        {
        // Use ENullBrush if there is skin background available.
        iBrushAndPenContext->SetBrushStyle(CGraphicsContext::ENullBrush);
        }
    else
        {
        iBrushAndPenContext->SetBrushStyle(CGraphicsContext::ESolidBrush);
        }
    }

void CEikCba::Reserved_MtsmPosition()
    {
    }

void CEikCba::Reserved_MtsmObject()
    {
    }

TInt CEikCba::AknLayoutFlags() const
    {
    TInt flags = 0;

    TBool controlPane = ETrue;
    TBool staconPane = EFalse;
    TBool staconPaneLeft = EFalse;
    TBool staconPaneRight = EFalse;
    TBool staconPaneIdle = EFalse;
    TBool rightPane = EFalse;

    TInt currentStatusPaneLayoutResId =
        AVKONENV->StatusPaneResIdForCurrentLayout(
            AknStatuspaneUtils::CurrentStatusPaneLayoutResId() ); 
        
    staconPane = 
        ((currentStatusPaneLayoutResId == R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_RIGHT) ||
        (currentStatusPaneLayoutResId == R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_LEFT)  ||
        (currentStatusPaneLayoutResId == R_AVKON_STACON_PANE_LAYOUT_EMPTY_SOFTKEYS_RIGHT) ||
        (currentStatusPaneLayoutResId == R_AVKON_STACON_PANE_LAYOUT_EMPTY_SOFTKEYS_LEFT)  ||        
        (currentStatusPaneLayoutResId == R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_RIGHT) ||
        (currentStatusPaneLayoutResId == R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_LEFT));

    staconPaneRight = 
        ((currentStatusPaneLayoutResId == R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_RIGHT) ||
        (currentStatusPaneLayoutResId == R_AVKON_STACON_PANE_LAYOUT_EMPTY_SOFTKEYS_RIGHT) ||
        (currentStatusPaneLayoutResId == R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_RIGHT));

    staconPaneIdle = 
        ((currentStatusPaneLayoutResId == R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_RIGHT) ||
        (currentStatusPaneLayoutResId == R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_LEFT));

    staconPaneLeft = !staconPaneRight;
    controlPane = !staconPane;        
         
    if ( IsAreaSideRightPaneActive() )
        {
        rightPane = ETrue;
        controlPane = EFalse;
        staconPane = EFalse;
        staconPaneLeft = EFalse;
        staconPaneRight = EFalse;
        staconPaneIdle = EFalse;
        }
    
    if (staconPane)
        {
        flags |= EAknLayoutCbaInStaconPane;
        }
    if (controlPane)
        {
        flags |= EAknLayoutCbaInControlPane;
        }
    if (staconPaneLeft)
        {
        flags |= EAknLayoutCbaInStaconPaneLeft;
        }
    if (staconPaneRight)
        {
        flags |= EAknLayoutCbaInStaconPaneRight;
        }
    if (staconPaneIdle)
        {
        flags |= EAknLayoutCbaInStaconPaneIdle;
        }
    if (rightPane)
        {
        flags |= EAknLayoutCbaInRightPane;
        }

    return flags;
    }


// ---------------------------------------------------------------------------
// Handles size change events in bottom softkey layout.
// ---------------------------------------------------------------------------
//
void CEikCba::SizeChangedInControlPane()
    {
    TRect screen;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screen );
    
    TBool isLandscape( Layout_Meta_Data::IsLandscapeOrientation() );
    TBool flatLscLayout( isLandscape &&
                         AknStatuspaneUtils::FlatLayoutActive() );
    
    // We must check for landscape mode bottom softkeys.
    TInt bottomPaneVariety = isLandscape ? ( flatLscLayout ? 2 : 6 ) : 1;
        
    TAknWindowComponentLayout controlPane(
        DoCompose(
            AknLayoutScalable_Avkon::application_window( 0 ),
            DoCompose(
                AknLayoutScalable_Avkon::area_bottom_pane( bottomPaneVariety ),
                AknLayoutScalable_Avkon::control_pane() ) ) );
    
    TAknLayoutRect cbarect;
    cbarect.LayoutRect( screen, controlPane.LayoutLine() );
    TRect rect( cbarect.Rect().Size() );

    TRect posInScreen( cbarect.Rect() );
    
    TBool mskEnabledInPlatform( iMSKEnabledInPlatform &&
                                IsMskEnabledLayoutActive() );

    TBool mskEnabledInApplication( AknLayoutUtils::MSKEnabled() && iMSKset );
    
    // Set the softkey frame rectangles in touch layouts.
    if ( iExtension && AknLayoutUtils::PenEnabled() )
        {        
        TAknLayoutRect layoutRect;
        TBool frameSizeChanged( EFalse );

        if ( mskEnabledInPlatform || flatLscLayout )
            {
            layoutRect.LayoutRect(
                rect,
                AknLayoutScalable_Avkon::control_pane_g6( 0 ).LayoutLine() );
            frameSizeChanged = layoutRect.Rect() != iExtension->iLeftFrameOuterRect;
            iExtension->iLeftFrameOuterRect = layoutRect.Rect();
            
            layoutRect.LayoutRect( iExtension->iLeftFrameOuterRect,
                     AknLayoutScalable_Avkon::bg_sctrl_sk_pane_g1()
                        .LayoutLine() );
            iExtension->iLeftFrameInnerRect = layoutRect.Rect();
            layoutRect.LayoutRect(
                rect,
                AknLayoutScalable_Avkon::control_pane_g8( 0 ).LayoutLine() );
            frameSizeChanged = frameSizeChanged || layoutRect.Rect() != iExtension->iRightFrameOuterRect;
            iExtension->iRightFrameOuterRect = layoutRect.Rect();
            layoutRect.LayoutRect( iExtension->iRightFrameOuterRect,
                     AknLayoutScalable_Avkon::bg_sctrl_sk_pane_g1()
                        .LayoutLine() );
            iExtension->iRightFrameInnerRect = layoutRect.Rect();

            if ( mskEnabledInPlatform )
                {
                layoutRect.LayoutRect(
                    rect,
                    AknLayoutScalable_Avkon::control_pane_g7( 0 ).LayoutLine() );
                frameSizeChanged = frameSizeChanged || layoutRect.Rect() != iExtension->iMiddleFrameOuterRect;
                iExtension->iMiddleFrameOuterRect = layoutRect.Rect();
                layoutRect.LayoutRect( iExtension->iMiddleFrameOuterRect,
                         AknLayoutScalable_Avkon::bg_sctrl_sk_pane_g1()
                            .LayoutLine() );
                iExtension->iMiddleFrameInnerRect = layoutRect.Rect();
                }
            else
                {
                iExtension->iMiddleFrameOuterRect.SetRect( 0, 0, 0, 0 );
                }
            }
        else
            {
            if ( AknLayoutUtils::LayoutMirrored() )
                {
                layoutRect.LayoutRect(
                    rect,
                    AknLayoutScalable_Avkon::bg_sctrl_sk_pane_cp1().LayoutLine() );
                frameSizeChanged = layoutRect.Rect() != iExtension->iRightFrameOuterRect;
				iExtension->iRightFrameOuterRect = layoutRect.Rect();
                layoutRect.LayoutRect( iExtension->iRightFrameOuterRect,
                         AknLayoutScalable_Avkon::bg_sctrl_sk_pane_g1()
                            .LayoutLine() );
                iExtension->iRightFrameInnerRect = layoutRect.Rect();
            
                layoutRect.LayoutRect(
                    rect,
                    AknLayoutScalable_Avkon::bg_sctrl_sk_pane_cp2().LayoutLine() );
                frameSizeChanged = frameSizeChanged || layoutRect.Rect() != iExtension->iLeftFrameOuterRect;
                iExtension->iLeftFrameOuterRect = layoutRect.Rect();
            
                layoutRect.LayoutRect( iExtension->iLeftFrameOuterRect,
                         AknLayoutScalable_Avkon::bg_sctrl_sk_pane_g1()
                            .LayoutLine() );
                iExtension->iLeftFrameInnerRect = layoutRect.Rect();
                }
            else
                {
                layoutRect.LayoutRect(
                    rect,
                    AknLayoutScalable_Avkon::bg_sctrl_sk_pane_cp1().LayoutLine() );
                frameSizeChanged = layoutRect.Rect() != iExtension->iLeftFrameOuterRect;
                iExtension->iLeftFrameOuterRect = layoutRect.Rect();
            
                layoutRect.LayoutRect( iExtension->iLeftFrameOuterRect,
                         AknLayoutScalable_Avkon::bg_sctrl_sk_pane_g1()
                            .LayoutLine() );
                iExtension->iLeftFrameInnerRect = layoutRect.Rect();
            
                layoutRect.LayoutRect(
                    rect,
                    AknLayoutScalable_Avkon::bg_sctrl_sk_pane_cp2().LayoutLine() );
                frameSizeChanged = frameSizeChanged || layoutRect.Rect() != iExtension->iRightFrameOuterRect;
                iExtension->iRightFrameOuterRect = layoutRect.Rect();
                layoutRect.LayoutRect( iExtension->iRightFrameOuterRect,
                         AknLayoutScalable_Avkon::bg_sctrl_sk_pane_g1()
                            .LayoutLine() );
                iExtension->iRightFrameInnerRect = layoutRect.Rect();
                }
            }

        if ( frameSizeChanged )
            {
            TRAP_IGNORE( iExtension->UpdateSoftkeyFrameL( EFalse ) );
            }
        }
    
    DoSetLayers( KAknsIIDNone );

    TInt textVariety;
    TInt graphVariety;
    
    // Even if the application is not MSK enabled,
    // use MSK layout when MSK is enabled in platform.
    if ( isLandscape )
        {
        if ( mskEnabledInPlatform )
            {
            textVariety  = 3;
            graphVariety = 2;
            }
        else
            {
            TBool extendedLayout( AknStatuspaneUtils::ExtendedFlatLayoutActive() );
            textVariety  = extendedLayout ? 3 : 2;
            graphVariety = extendedLayout ? 3 : 2;
            }
        }
    else if ( mskEnabledInPlatform )
        {
        textVariety  = 3;
        graphVariety = 4;
        }
    else
        {
        textVariety  = 0;
        graphVariety = 4;
        }
        
    if ( iExtension->iEnablePostingTransparency ||
         ( iCbaFlags & EEikCbaFlagTransparent ) || ( iCbaFlags & EEikCbaFlagSemiTransparent ) )
        {
        textVariety = 6; // Outline font used
        }

    // This uses correct coordinates to calculate the positions of softkey labels.
    // Unfortunately we do not have access to the labels inside CEikCbaButtons,
    // that's the reason for a hack with ComponentControl().
    // (This is the only place that knows of all softkeys ...)
    if ( iControlArray->Count() != 0 )
        {
        CCoeControl* leftSoftkey = (*iControlArray)[KControlArrayCBAButton1Posn].iControl;
        CCoeControl* rightSoftkey = (*iControlArray)[KControlArrayCBAButton2Posn].iControl;
        CCoeControl* MSKSoftkey = NULL;
        
        CEikCbaButton* leftSKButton =
            static_cast<CEikCbaButton*>( leftSoftkey );
        CEikCbaButton* rightSKButton =
            static_cast<CEikCbaButton*>( rightSoftkey );
        CEikCbaButton* MSKButton = NULL;
        
        TAknTextLineLayout controlPaneTextLayout;
        
        if ( !leftSKButton->IsImageOn() )
            {
            controlPaneTextLayout =
                AknLayoutScalable_Avkon::control_pane_t1( textVariety ).LayoutLine();
            
            if ( iCbaFlags & EEikCbaFlagOutlineFont )
                {
                // Sets outline font property.
                controlPaneTextLayout.iFont |= KOutlineFontMask;
                }

            CEikLabel* cbaLabel =
                static_cast<CEikLabel*>( leftSoftkey->ComponentControl( 0 ) );
            AknLayoutUtils::LayoutLabel( cbaLabel,
                                         Rect(),
                                         controlPaneTextLayout );
            LayoutControl( leftSKButton, cbaLabel->Rect() );
            leftSKButton->TruncateLabelText();
            }
        else
            {
            TAknLayoutRect qgn_graf_sk_left;
            qgn_graf_sk_left.LayoutRect(
                rect,
                AknLayoutScalable_Avkon::control_pane_g1( graphVariety ).LayoutLine() );
            leftSoftkey->ComponentControl( 0 )->SetRect( qgn_graf_sk_left.Rect() );
            leftSoftkey->SetRect( qgn_graf_sk_left.Rect() );
            }

        if ( !rightSKButton->IsImageOn() )
            {
            controlPaneTextLayout =
                AknLayoutScalable_Avkon::control_pane_t2( textVariety ).LayoutLine();

            if ( iCbaFlags & EEikCbaFlagOutlineFont )
                {
                // Sets outline font property.
                controlPaneTextLayout.iFont |= KOutlineFontMask;
                }

            CEikLabel* cbaLabel =
                static_cast<CEikLabel*>( rightSoftkey->ComponentControl( 0 ) );
            AknLayoutUtils::LayoutLabel( cbaLabel, 
                                         Rect(),
                                         controlPaneTextLayout );
            LayoutControl( rightSKButton, cbaLabel->Rect() );            
            rightSKButton->TruncateLabelText();
            }
        else
            {
            TAknLayoutRect qgn_graf_sk_right;
            qgn_graf_sk_right.LayoutRect(
                rect,
                AknLayoutScalable_Avkon::control_pane_g2( graphVariety ).LayoutLine() );
            rightSoftkey->ComponentControl( 0 )->SetRect( qgn_graf_sk_right.Rect() );
            rightSoftkey->SetRect( qgn_graf_sk_right.Rect() );
            }

        // Scrollbar will go over MSK!!! needs to be fixed.
        if ( VScrollBarAsControl()->Model()->ScrollBarUseful() )
            {
            CCoeControl* scroller = (*iControlArray)[KControlArrayScrollBarPosn].iControl;
            AknLayoutUtils::LayoutControl(
                scroller,
                rect,
                AKN_LAYOUT_WINDOW_Control_pane_elements_Line_1 );
            }

        TInt textMSKVariety = 3;
        TInt graphicMSKVariety = 0;

        if ( mskEnabledInApplication && mskEnabledInPlatform )
            {
            MSKSoftkey = (*iControlArray)[KControlArrayCBAButtonMSKPosn].iControl;
            MSKButton = static_cast<CEikCbaButton*>( MSKSoftkey );
            
            if ( !MSKButton->IsImageOn() )
                {
                controlPaneTextLayout =
                    AknLayoutScalable_Avkon::control_pane_t3(
                        textMSKVariety ).LayoutLine();

                if ( iCbaFlags & EEikCbaFlagOutlineFont )
                    {
                    // Sets outline font property.
                    controlPaneTextLayout.iFont |= KOutlineFontMask;
                    }

                CEikLabel* cbaLabel =
                    static_cast<CEikLabel*>( MSKSoftkey->ComponentControl( 0 ) );
                AknLayoutUtils::LayoutLabel( cbaLabel,
                                             Rect(),
                                             controlPaneTextLayout );
                LayoutControl( MSKButton, cbaLabel->Rect() );            
                MSKButton->TruncateLabelText();
                }
            else
                {
                TAknLayoutRect qgn_graf_sk_msk;
                qgn_graf_sk_msk.LayoutRect(
                    rect,
                    AknLayoutScalable_Avkon::control_pane_g4(
                        graphicMSKVariety ).LayoutLine() );
                TRect rect( qgn_graf_sk_msk.Rect() );                
     
                // aid_value_unit2 is 10ux10u rectangle
                TAknWindowComponentLayout unit( AknLayoutScalable_Avkon::aid_value_unit2() );
                TInt delta = unit.LayoutLine().iW / 10 / 2; // half units
                if ( MSKButton->PressedDown() )
                    {
                    rect.Move( delta, delta );
                    }                                        
                MSKSoftkey->ComponentControl( 0 )->SetRect( rect );
                MSKSoftkey->SetRect( rect );        
                }
            }

        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        const TBool transparentSoftkeys = 
            iExtension->iEnablePostingTransparency || 
            ( iCbaFlags & EEikCbaFlagTransparent ) || 
            ( iCbaFlags & EEikCbaFlagSemiTransparent );
        TRgb leftColor;
        TRgb rightColor;
        TRgb MSKColor;
        TInt errorl;
        TInt errorr;
        TInt errorMSK;

        TBool idleState = AknStatuspaneUtils::IdleLayoutActive();
        if ( idleState )
            {
            errorl = AknsUtils::GetCachedColor( 
                skin,
                leftColor,
                KAknsIIDQsnTextColors,
                EAknsCIQsnTextColorsCG15 );
                
            errorr = AknsUtils::GetCachedColor( 
                skin,
                rightColor,
                KAknsIIDQsnTextColors,
                EAknsCIQsnTextColorsCG16 );
                
            errorMSK = AknsUtils::GetCachedColor( 
                skin,
                MSKColor,
                KAknsIIDQsnTextColors,
                EAknsCIQsnTextColorsCG57 );
            }
        else if ( iPopupVisible )
            {
            errorl = AknsUtils::GetCachedColor( 
                skin,
                leftColor,
                KAknsIIDQsnTextColors,
                EAknsCIQsnTextColorsCG17 );
                
            errorr = AknsUtils::GetCachedColor( 
                skin,
                rightColor,
                KAknsIIDQsnTextColors,
                EAknsCIQsnTextColorsCG18  );
                
            errorMSK = AknsUtils::GetCachedColor( 
                skin,
                MSKColor,
                KAknsIIDQsnTextColors,
                EAknsCIQsnTextColorsCG58 );
            }
        else
            {
            errorl = AknsUtils::GetCachedColor( 
                skin,
                leftColor,
                KAknsIIDQsnTextColors,
                EAknsCIQsnTextColorsCG13 );
                
            errorr = AknsUtils::GetCachedColor( 
                skin,
                rightColor,
                KAknsIIDQsnTextColors,
                EAknsCIQsnTextColorsCG14 );
                
            errorMSK = AknsUtils::GetCachedColor( 
                skin,
                MSKColor,
                KAknsIIDQsnTextColors,
                EAknsCIQsnTextColorsCG56 );
            }

        if ( transparentSoftkeys )
            {
            rightColor = KRgbWhite;
            leftColor = KRgbWhite;
            }
        if ( leftSKButton->PressedDown() )
            {            
            leftColor.SetAlpha( KPressedDownAlphaValue );
            
            AknsUtils::GetCachedColor( 
                skin,
                leftColor,
                KAknsIIDQsnTextColors,
                EAknsCIQsnTextColorsCG69 ); 
                
            if ( transparentSoftkeys )
                {
                // alpha has no effect with display posting.
                leftColor = TRgb( 128, 128, 128 );
                }
            }
        else if ( rightSKButton->PressedDown() )
            {
            rightColor.SetAlpha( KPressedDownAlphaValue );
            
            AknsUtils::GetCachedColor( 
                skin,
                rightColor,
                KAknsIIDQsnTextColors,
                EAknsCIQsnTextColorsCG69 );
                
            if ( transparentSoftkeys )
                {
                // alpha has no effect with display posting.
                rightColor = TRgb( 128, 128, 128 );
                }
            }
        else if ( MSKButton && MSKButton->PressedDown() )
            {
            MSKColor.SetAlpha( KPressedDownAlphaValue );
            
            AknsUtils::GetCachedColor( 
                skin,
                MSKColor,
                KAknsIIDQsnTextColors,
                EAknsCIQsnTextColorsCG69 );
            
            }

        if( !errorl && !errorr )
            {
            // Error ignored
            TRAP( errorl, AknLayoutUtils::OverrideControlColorL( 
                *leftSoftkey,
                EColorLabelText,
                leftColor) );
                
            TRAP( errorr, AknLayoutUtils::OverrideControlColorL( 
                *rightSoftkey,
                EColorLabelText,
                rightColor) );

            if ( transparentSoftkeys )
                {
                // Outline color is black.
                TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( 
                    *leftSoftkey,
                    EColorControlBackground,
                    KRgbBlack ) );
                TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( 
                    *rightSoftkey,
                    EColorControlBackground,
                    KRgbBlack ) );
                }
            }

        if ( mskEnabledInApplication && mskEnabledInPlatform && !errorMSK )
            {
            // Error ignored.
            TRAP( errorMSK, AknLayoutUtils::OverrideControlColorL( 
                *MSKSoftkey,
                EColorLabelText,
                MSKColor) );
            }

        // If MSK colors not set in skin, use left CBA color.
        if ( mskEnabledInApplication && mskEnabledInPlatform && errorMSK && !errorl )
            {
            // Error ignored.
            TRAP( errorMSK,
                {
                AknLayoutUtils::OverrideControlColorL( 
                    *MSKSoftkey,
                    EColorLabelText,
                    leftColor);
                } );
            }
            
        DrawDeferred();
        }

    AknsUtils::RegisterControlPosition( this, posInScreen.iTl );
    }


void CEikCba::SizeChangedInStaconPane()
    {  
    TRect screen( iAvkonAppUi->ApplicationRect() );
    TBool softKeysUpAndDownMirrored = EFalse;

    TInt variety = 0;
    if (AknLayoutFlags() & EAknLayoutCbaInStaconPaneLeft)
        {
        variety = 1;
        }
            
    TAknWindowComponentLayout layout0;
    TAknWindowComponentLayout layout1;
    TAknWindowComponentLayout layout2;
    TAknWindowComponentLayout imageLayout;
    TAknTextComponentLayout textLayout;
    
    // Read right (top in landscape) softkey layout.
    layout0 = AknLayoutScalable_Avkon::area_top_pane(2);
    layout1 = AknLayoutScalable_Avkon::stacon_top_pane();
    
    // If clock is shown in stacon, cba area is smaller.
    TInt topCbaVariety = variety;
    if (AknStatuspaneUtils::ExtendedStaconPaneActive())
        {
        topCbaVariety += 4;
        }

    TInt textVariety = variety;
    if ( iExtension->iEnablePostingTransparency || ( iCbaFlags & EEikCbaFlagTransparent ) )
        {
        textVariety += 2; // Outline font used
        }

    layout2 = AknLayoutScalable_Avkon::control_top_pane_stacon(topCbaVariety);
    imageLayout = AknLayoutScalable_Avkon::control_top_pane_stacon_g1();
    textLayout = AknLayoutScalable_Avkon::control_top_pane_stacon_t1(textVariety);
            
    TAknTextComponentLayout rightSoftKeyTextLayout(
        DoComposeText(layout0, DoComposeText(layout1, DoComposeText(layout2, textLayout))) );
    TAknWindowComponentLayout rightSoftKeyImageLayout(
        DoCompose(layout0, DoCompose(layout1, DoCompose(layout2, imageLayout))) );
    
    // Calculate softkey rects.
    TAknWindowLineLayout rightSoftkeyLayout(
        DoCompose( layout0, DoCompose(layout1, layout2)).LayoutLine() );
    TAknLayoutRect rightSoftkeyLayoutRect;
    rightSoftkeyLayoutRect.LayoutRect(screen, rightSoftkeyLayout);
    TRect rightSoftKeyButtonRect( rightSoftkeyLayoutRect.Rect() );
        
    TAknTextLineLayout   rightSoftkeyTextLayout( rightSoftKeyTextLayout.LayoutLine() );
    TAknWindowLineLayout rightSoftkeyImageLayout( rightSoftKeyImageLayout.LayoutLine() );
    
    // Read left (bottom in landscape) softkey layout.
    layout0 = AknLayoutScalable_Avkon::area_bottom_pane(2);
    layout1 = AknLayoutScalable_Avkon::stacon_bottom_pane();

    // If clock is shown in stacon, cba area is smaller.
    TInt bottomCbaVariety = variety;
    if (AknStatuspaneUtils::ExtendedStaconPaneActive())     
        {
        bottomCbaVariety += 2;
        }

    layout2 = AknLayoutScalable_Avkon::control_bottom_pane_stacon(bottomCbaVariety);    
    imageLayout = AknLayoutScalable_Avkon::control_bottom_pane_stacon_g1();
    textLayout = AknLayoutScalable_Avkon::control_bottom_pane_stacon_t1(textVariety);
            
    TAknTextComponentLayout leftSoftKeyTextLayout(
        DoComposeText(layout0, DoComposeText(layout1, DoComposeText(layout2, textLayout))) );
    TAknWindowComponentLayout leftSoftKeyImageLayout(
        DoCompose(layout0, DoCompose(layout1, DoCompose(layout2, imageLayout))) );
        
    // Calculate softkey rects
    TAknWindowLineLayout leftSoftkeyLayout(
        DoCompose( layout0, DoCompose(layout1, layout2) ).LayoutLine() );
    TAknLayoutRect leftSoftkeyLayoutRect;
    leftSoftkeyLayoutRect.LayoutRect(screen, leftSoftkeyLayout);
    TRect leftSoftKeyButtonRect( leftSoftkeyLayoutRect.Rect() );
        
    TAknTextLineLayout   leftSoftkeyTextLayout( leftSoftKeyTextLayout.LayoutLine() );
    TAknWindowLineLayout leftSoftkeyImageLayout( leftSoftKeyImageLayout.LayoutLine() );
    
    // If softkeys are on the "other" side, then swap the texts and images here...
    if (variety == 1)
        {
        CWsScreenDevice* dev = iEikonEnv->ScreenDevice();
        TPixelsAndRotation sizeAndRotation;
        dev->GetScreenModeSizeAndRotation(dev->CurrentScreenMode(), sizeAndRotation);
        
       TBool isLandscape( Layout_Meta_Data::IsLandscapeOrientation() );

        // If landscape orientation uses 270 degree rotation ( or 0 degree 
        // rotation in case of default portrait rotation uses 90 degree value),
        // only then mirror L & R (actually upper and lower in stacon).
        if ( isLandscape && 
             ( sizeAndRotation.iRotation == CFbsBitGc::EGraphicsOrientationRotated270 ||
               sizeAndRotation.iRotation == CFbsBitGc::EGraphicsOrientationNormal ) )
            {
            softKeysUpAndDownMirrored = ETrue;
            TAknTextLineLayout   tmpTextLineLayout( leftSoftkeyTextLayout );
            TAknWindowLineLayout tmpWindowLineLayout( leftSoftkeyImageLayout );
            TRect                tmpRect( leftSoftKeyButtonRect );
        
            leftSoftKeyButtonRect = rightSoftKeyButtonRect;
            leftSoftkeyTextLayout = rightSoftkeyTextLayout;
            leftSoftkeyImageLayout = rightSoftkeyImageLayout;
        
            rightSoftKeyButtonRect = tmpRect;
            rightSoftkeyTextLayout = tmpTextLineLayout;
            rightSoftkeyImageLayout = tmpWindowLineLayout;
            }
        }
    
    // Set skin background.        
    TRect screenRect( iAvkonAppUi->ApplicationRect() );
    TAknWindowLineLayout layout( AknLayoutScalable_Avkon::area_top_pane(2).LayoutLine() );
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( screenRect, layout );
    TRect staconTop( layoutRect.Rect() );
    
    layout = AknLayoutScalable_Avkon::area_bottom_pane(2).LayoutLine();
    layoutRect.LayoutRect( screenRect, layout );        
    TRect staconBottom( layoutRect.Rect() );

    TBool skLeft = AknLayoutFlags() & EAknLayoutCbaInStaconPaneLeft;
    TBool idle = AknLayoutFlags() & EAknLayoutCbaInStaconPaneIdle;

    TAknsItemID topMaskIID    = KAknsIIDNone;
    TAknsItemID bottomMaskIID = KAknsIIDNone;
    
    if ( idle )
        {    
        if ( skLeft )
            {
            iStaconBgContextTop->SetLayerImage( ECbaLayerBackground, KAknsIIDQsnBgAreaStaconLtIdle );
            iStaconBgContextBottom->SetLayerImage( ECbaLayerBackground, KAknsIIDQsnBgAreaStaconLbIdle );
            }
        else
            {
            iStaconBgContextTop->SetLayerImage( ECbaLayerBackground, KAknsIIDQsnBgAreaStaconRtIdle );
            iStaconBgContextBottom->SetLayerImage( ECbaLayerBackground, KAknsIIDQsnBgAreaStaconRbIdle );
            }
        iStaconBgContextTop->SetLayerImage( ECbaLayerWallpaper, KAknsIIDWallpaper );
        iStaconBgContextTop->SetLayerRect( ECbaLayerWallpaper, screen );
        iStaconBgContextTop->SetLayerRect( ECbaLayerBackground, staconTop );
        
        topMaskIID = KAknsIIDQgnGrafBgLscTopMaskIcon;

        iStaconBgContextBottom->SetLayerImage( ECbaLayerWallpaper, KAknsIIDWallpaper );
        iStaconBgContextBottom->SetLayerRect( ECbaLayerWallpaper, screen );
        iStaconBgContextBottom->SetLayerRect( ECbaLayerBackground, staconBottom );

        bottomMaskIID = KAknsIIDQgnGrafBgLscBottomMaskIcon;
        }
    else
        {
        // If not in idle, then there is no wallpaper, thus clear wallpaper layer.         
        if ( skLeft )
            {
            iStaconBgContextTop->SetLayerImage( ECbaLayerBackground, KAknsIIDQsnBgAreaStaconLt );
            iStaconBgContextBottom->SetLayerImage( ECbaLayerBackground, KAknsIIDQsnBgAreaStaconLb );
            }
        else
            {
            iStaconBgContextTop->SetLayerImage( ECbaLayerBackground, KAknsIIDQsnBgAreaStaconRt );
            iStaconBgContextBottom->SetLayerImage( ECbaLayerBackground, KAknsIIDQsnBgAreaStaconRb );
            }
        iStaconBgContextTop->SetLayerRect( ECbaLayerBackground, staconTop );
        iStaconBgContextTop->SetLayerImage( ECbaLayerWallpaper, KAknsIIDNone );
        topMaskIID = KAknsIIDNone;

        iStaconBgContextBottom->SetLayerRect( ECbaLayerBackground, staconBottom );
        iStaconBgContextBottom->SetLayerImage( ECbaLayerWallpaper, KAknsIIDNone );
        bottomMaskIID = KAknsIIDNone;
        }

    // If setting layer mask fails, ignore the error.
    // This causes UI elements to be opaque and thus parts of the wallpaper is hidden.
    TRAP_IGNORE( 
        iStaconBgContextBottom->SetLayerMaskAndSizeL( bottomMaskIID, staconBottom );
        iStaconBgContextTop->SetLayerMaskAndSizeL( topMaskIID, staconTop );
        );

    TRect cba( Rect() );
    // This uses correct coordinates to calculate the positions of softkey labels.
    // Unfortunately we do not have access to the labels inside CEikCbaButtons,
    // that's the reason for a hack with ComponentControl().
    // (This is the only place that knows of both left and right softkey ...)
    if (iControlArray->Count() != 0)
        {
        CCoeControl *leftSoftkey = (*iControlArray)[KControlArrayCBAButton1Posn].iControl;
        CCoeControl *rightSoftkey = (*iControlArray)[KControlArrayCBAButton2Posn].iControl;
        
        // Left SK.
        if (!(((CEikCbaButton*)leftSoftkey)->IsImageOn()))
            {
            AknLayoutUtils::LayoutLabel((CEikLabel*)leftSoftkey->ComponentControl( 0 ), 
                Rect(), 
                leftSoftkeyTextLayout );                        
            LayoutControl( (CEikCbaButton*)leftSoftkey, 
                leftSoftkey->ComponentControl( 0 )->Rect() );                 
            ((CEikCbaButton*)leftSoftkey)->TruncateLabelText();
            }
        else
            {
            TAknLayoutRect qgn_graf_sk_left;
            qgn_graf_sk_left.LayoutRect(cba, leftSoftkeyImageLayout);
            leftSoftkey->ComponentControl(0)->SetRect(qgn_graf_sk_left.Rect());
            leftSoftkey->SetRect(leftSoftKeyButtonRect);

            // To make sure mop chain is updated, do it here. If not done, only skin background
            //  suffers.
            TRAP_IGNORE(((CEikCbaButton*)leftSoftkey)->SetContainerWindowL(*this)); 
            }
        
        // Right SK.
        if (!(((CEikCbaButton*)rightSoftkey)->IsImageOn()))
            {
            AknLayoutUtils::LayoutLabel((CEikLabel*)rightSoftkey->ComponentControl( 0 ), 
                Rect(), 
                rightSoftkeyTextLayout );
            LayoutControl( (CEikCbaButton*)rightSoftkey, 
                rightSoftkey->ComponentControl( 0 )->Rect() );                 
            ((CEikCbaButton*)rightSoftkey)->TruncateLabelText();
            }
        else
            {
            TAknLayoutRect qgn_graf_sk_right;
            qgn_graf_sk_right.LayoutRect(cba, rightSoftkeyImageLayout);
            rightSoftkey->ComponentControl(0)->SetRect(qgn_graf_sk_right.Rect());
            rightSoftkey->SetRect(rightSoftKeyButtonRect);  

            // To make sure mop chain is updated, do it here. If not done, only skin background 
            // suffers.
            TRAP_IGNORE(((CEikCbaButton*)rightSoftkey)->SetContainerWindowL(*this));
            }
        
        // Landscape mode scrollbar layout is not set here, let application do if needed.
        CCoeControl* scroller = (*iControlArray)[KControlArrayScrollBarPosn].iControl;
        if (scroller)
            {
            scroller->SetSize(TSize(0,0));
            }
        
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();        
        const TBool transparentSoftkeys =
            iExtension->iEnablePostingTransparency ||
            ( iCbaFlags & EEikCbaFlagTransparent );
        TRgb rightSkColor;
        TRgb leftSkColor;

        TInt error1 = 0;
        TInt error2 = 0;

        if (idle)
            {
            error1 = AknsUtils::GetCachedColor( skin, rightSkColor, KAknsIIDQsnTextColors, 
                EAknsCIQsnTextColorsCG41 ); // text #41 stacon area top softkey text in idle #0
                
            error2 = AknsUtils::GetCachedColor( skin, leftSkColor, KAknsIIDQsnTextColors, 
                EAknsCIQsnTextColorsCG42 ); // text #42 stacon area bottom softkey text in idle #0
            }
        else
            {
            error1 = AknsUtils::GetCachedColor( skin, rightSkColor, KAknsIIDQsnTextColors, 
                EAknsCIQsnTextColorsCG39 ); // text #39 stacon area top softkey text #0
                
            error2 = AknsUtils::GetCachedColor( skin, leftSkColor, KAknsIIDQsnTextColors, 
                EAknsCIQsnTextColorsCG40 ); // text #40 stacon area bottom softkey text #0
            }

        if ( transparentSoftkeys )
            {
            rightSkColor = KRgbWhite;
            leftSkColor = KRgbWhite;
            }
        if (softKeysUpAndDownMirrored)
            {
            TRgb tmp = rightSkColor;
            rightSkColor = leftSkColor;
            leftSkColor = tmp;
            }

        if ( ((CEikCbaButton*)leftSoftkey)->PressedDown() )
            {
            leftSkColor.SetAlpha( KPressedDownAlphaValue );
            
            AknsUtils::GetCachedColor( 
                skin,
                leftSkColor,
                KAknsIIDQsnTextColors,
                EAknsCIQsnTextColorsCG69 );
            
            if ( transparentSoftkeys )
                {
                // alpha has no effect with display posting.
                leftSkColor = TRgb( 128, 128, 128 );
                }
            }
        else if ( ((CEikCbaButton*)rightSoftkey)->PressedDown() )
            {
            rightSkColor.SetAlpha( KPressedDownAlphaValue );
            
            AknsUtils::GetCachedColor( 
                skin,
                rightSkColor,
                KAknsIIDQsnTextColors,
                EAknsCIQsnTextColorsCG69 );
        
            if ( transparentSoftkeys )
                {
                // alpha has no effect with display posting.
                rightSkColor = TRgb( 128, 128, 128 );
                }
            }
            
        if( !error1 && !error2 )
            {
            // Error ignored.
            TRAP( error1, AknLayoutUtils::OverrideControlColorL(*leftSoftkey,
                EColorLabelText,
                leftSkColor) );
            TRAP( error2, AknLayoutUtils::OverrideControlColorL(*rightSoftkey,
                EColorLabelText,
                rightSkColor) );
            if ( transparentSoftkeys )
                {
                // outline color is black.
                TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL(
                    *leftSoftkey,
                    EColorControlBackground,
                    KRgbBlack ) );
                TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL(
                    *rightSoftkey,
                    EColorControlBackground,
                    KRgbBlack ) );
                }
            }
        
        if (iStaconLabelFont)
            {
            ((CEikCbaButton*)leftSoftkey)->SetLabelFont(iStaconLabelFont);
            ((CEikCbaButton*)rightSoftkey)->SetLabelFont(iStaconLabelFont);
            }
        
        DrawDeferred();
        }

    AknsUtils::RegisterControlPosition( this, TPoint(0,0) );
    }


//------------------------------------------------------------------------------
// CEikCba::SizeChangedInRightPane()
//------------------------------------------------------------------------------
//
void CEikCba::SizeChangedInRightPane()
    {
    TRect screen;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screen );
           
    TAknWindowComponentLayout rightAreaLayout(
        AknLayoutScalable_Avkon::area_side_right_pane( 0 ) );
        
    TAknWindowComponentLayout topSKLayout(
        DoCompose( rightAreaLayout,
                   AknLayoutScalable_Avkon::sctrl_sk_top_pane() ) );
        
    TAknWindowComponentLayout bottomSKLayout(
        DoCompose( rightAreaLayout,
                   AknLayoutScalable_Avkon::sctrl_sk_bottom_pane() ) );
    
    // Calculate softkey rects.
    
    // Right (top in landscape) softkey layout.
    TAknLayoutRect rightSoftkeyLayoutRect;
    rightSoftkeyLayoutRect.LayoutRect( screen,
                                       topSKLayout.LayoutLine() );
    TRect rightSoftKeyButtonRect( rightSoftkeyLayoutRect.Rect() );
    
    // Left (bottom in landscape) softkey layout.
    TAknLayoutRect leftSoftkeyLayoutRect;
    leftSoftkeyLayoutRect.LayoutRect( screen,
                                      bottomSKLayout.LayoutLine() );
    TRect leftSoftKeyButtonRect( leftSoftkeyLayoutRect.Rect() );
    
    // Set the softkey frame rectangles in touch layouts.
    if ( iExtension && AknLayoutUtils::PenEnabled() )
        {
        TBool frameSizeChanged(
            iExtension->iLeftFrameOuterRect  != leftSoftKeyButtonRect || 
            iExtension->iRightFrameOuterRect != rightSoftKeyButtonRect );
        iExtension->iLeftFrameOuterRect  = leftSoftKeyButtonRect;
        iExtension->iRightFrameOuterRect = rightSoftKeyButtonRect;
        if ( frameSizeChanged )
            {
            TRAP_IGNORE( iExtension->UpdateSoftkeyFrameL( EFalse ) );
            }
        }
    
    // Calculate softkey image and text layouts.
    TInt softkeyTextVariety = 0;
    
    if ( iExtension->iEnablePostingTransparency || ( iCbaFlags & EEikCbaFlagTransparent ) )
        {
        softkeyTextVariety = 1; // Outline font used
        }

    // Right (top in landscape) softkey layout.
    TAknTextLineLayout rightSoftkeyTextLayout( 
        DoComposeText(
            topSKLayout,
            AknLayoutScalable_Avkon::sctrl_sk_top_pane_t1(softkeyTextVariety) ).LayoutLine() );
        
    TAknWindowLineLayout rightSoftkeyImageLayout( 
        DoCompose(
            topSKLayout,
            AknLayoutScalable_Avkon::sctrl_sk_top_pane_g1() ).LayoutLine() );
    
    // Left (bottom in landscape) softkey layout.
    TAknTextLineLayout leftSoftkeyTextLayout( 
        DoComposeText(
            bottomSKLayout,
            AknLayoutScalable_Avkon::sctrl_sk_bottom_pane_t1(softkeyTextVariety) ).LayoutLine() );
        
    TAknWindowLineLayout leftSoftkeyImageLayout( 
        DoCompose(
            bottomSKLayout,
            AknLayoutScalable_Avkon::sctrl_sk_bottom_pane_g1() ).LayoutLine() );
       
    // Set skin background.        
    
    DoSetLayers( KAknsIIDNone );

    TRect cba( Rect() );
    
    // This uses correct coordinates to calculate the positions
    // of softkey labels. Unfortunately we do not have access to
    // the labels inside CEikCbaButtons, that's the reason for a
    // hack with ComponentControl().
    // (This is the only place that knows of both left and right softkey ...)
    if ( iControlArray->Count() != 0 )
        {
        CCoeControl* leftSoftkeyControl =
            (*iControlArray)[KControlArrayCBAButton1Posn].iControl;
        CCoeControl* rightSoftkeyControl =
            (*iControlArray)[KControlArrayCBAButton2Posn].iControl;
            
        CEikCbaButton* leftSoftkey =
            static_cast<CEikCbaButton*>( leftSoftkeyControl );
        CEikCbaButton* rightSoftkey =
            static_cast<CEikCbaButton*>( rightSoftkeyControl );
        
        // Left SK.
        if ( !leftSoftkey->IsImageOn() )
            {
            AknLayoutUtils::LayoutLabel(
                static_cast<CEikLabel*>( leftSoftkeyControl->ComponentControl( 0 ) ),
                cba, 
                leftSoftkeyTextLayout );                        
            LayoutControl(
                leftSoftkey, 
                leftSoftkeyControl->ComponentControl( 0 )->Rect() );                 
            leftSoftkey->TruncateLabelText();
            }
        else
            {
            TAknLayoutRect qgn_graf_sk_left;
            qgn_graf_sk_left.LayoutRect( cba, leftSoftkeyImageLayout );
            leftSoftkeyControl->ComponentControl( 0 )->SetRect( qgn_graf_sk_left.Rect() );
            leftSoftkeyControl->SetRect( leftSoftKeyButtonRect );

            // To make sure mop chain is updated, do it here.
            // If not done, only skin background suffers.
            TRAP_IGNORE( leftSoftkey->SetContainerWindowL( *this ) ); 
            }
        
        // Right SK.
        if ( !rightSoftkey->IsImageOn() )
            {
            AknLayoutUtils::LayoutLabel(
                static_cast<CEikLabel*>( rightSoftkeyControl->ComponentControl( 0 ) ),
                cba, 
                rightSoftkeyTextLayout );
            LayoutControl(
                rightSoftkey, 
                rightSoftkeyControl->ComponentControl( 0 )->Rect() );                 
            rightSoftkey->TruncateLabelText();
            }
        else
            {
            TAknLayoutRect qgn_graf_sk_right;
            qgn_graf_sk_right.LayoutRect( cba, rightSoftkeyImageLayout );
            rightSoftkeyControl->ComponentControl( 0 )->SetRect( qgn_graf_sk_right.Rect() );
            rightSoftkeyControl->SetRect( rightSoftKeyButtonRect );  

            // To make sure mop chain is updated, do it here.
            // If not done, only skin background suffers.
            TRAP_IGNORE( rightSoftkey->SetContainerWindowL( *this ) );
            }
        
        // Landscape mode scrollbar layout is not set here, let application do if needed.
        CCoeControl* scroller = (*iControlArray)[KControlArrayScrollBarPosn].iControl;
        if ( scroller )
            {
            scroller->SetSize( TSize( 0, 0 ) );
            }
        
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();        
        const TBool transparentSoftkeys = 
            iExtension->iEnablePostingTransparency || 
            ( iCbaFlags & EEikCbaFlagTransparent );
             
        TRgb rightSkColor;
        TRgb leftSkColor;

        TInt error1 = 0;
        TInt error2 = 0;
        if ( transparentSoftkeys )
            {
            rightSkColor = KRgbWhite;
            leftSkColor = KRgbWhite;           
            }
        else if ( AknStatuspaneUtils::IdleLayoutActive() )
            {
            // Text #41 stacon area top softkey text in idle #0
            error1 = AknsUtils::GetCachedColor( skin,
                                                rightSkColor,
                                                KAknsIIDQsnTextColors, 
                                                EAknsCIQsnTextColorsCG41 );

            // Text #42 stacon area bottom softkey text in idle #0
            error2 = AknsUtils::GetCachedColor( skin,
                                                leftSkColor,
                                                KAknsIIDQsnTextColors, 
                                                EAknsCIQsnTextColorsCG42 );
            }
        else
            {
            // Text #39 stacon area top softkey text #0
            error1 = AknsUtils::GetCachedColor( skin,
                                                rightSkColor,
                                                KAknsIIDQsnTextColors, 
                                                EAknsCIQsnTextColorsCG39 );

            // Text #40 stacon area bottom softkey text #0
            error2 = AknsUtils::GetCachedColor( skin, 
                                                leftSkColor,
                                                KAknsIIDQsnTextColors, 
                                                EAknsCIQsnTextColorsCG40 );
            }

        if ( leftSoftkey->PressedDown() )
            {
            leftSkColor.SetAlpha( KPressedDownAlphaValue );
            
            AknsUtils::GetCachedColor( 
                skin,
                leftSkColor,
                KAknsIIDQsnTextColors,
                EAknsCIQsnTextColorsCG69 );
            
            
            if ( transparentSoftkeys )
                {
                // alpha has no effect with display posting.
                leftSkColor = TRgb( 128, 128, 128 );
                }
            }
        else if ( rightSoftkey->PressedDown() )
            {
            rightSkColor.SetAlpha( KPressedDownAlphaValue );
            
            AknsUtils::GetCachedColor( 
                skin,
                rightSkColor,
                KAknsIIDQsnTextColors,
                EAknsCIQsnTextColorsCG69 );

            if ( transparentSoftkeys )
                {
                // alpha has no effect with display posting.
                rightSkColor = TRgb( 128, 128, 128 );
                }
            }
            
        if( !error1 && !error2 )
            {
            // Error ignored.
            TRAP( error1,
                  AknLayoutUtils::OverrideControlColorL( *leftSoftkeyControl,
                                                         EColorLabelText,
                                                         leftSkColor ) );
            TRAP( error2,
                  AknLayoutUtils::OverrideControlColorL( *rightSoftkeyControl,
                                                         EColorLabelText,
                                                         rightSkColor ) );
                                                         
            if ( transparentSoftkeys )
                {
                // outline color is black.
                TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( 
                    *leftSoftkeyControl,
                    EColorControlBackground,
                    KRgbBlack ) );
                TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( 
                    *rightSoftkeyControl,
                    EColorControlBackground,
                    KRgbBlack ) );
                }
            }
        
        if ( iRightPaneLabelFont )
            {
            leftSoftkey->SetLabelFont( iRightPaneLabelFont );
            rightSoftkey->SetLabelFont( iRightPaneLabelFont );
            }
        
        DrawDeferred();
        }

    AknsUtils::RegisterControlPosition( this, TPoint( 0, 0 ) );   
    }
    
    
    
void CEikCba::SizeChangedInsideDialog()
    {
    // Give both LSK and RSK buttons half of the available space.
    //
    if ( iControlArray )
        {
        TRect buttonRect1( Rect() );
        TRect buttonRect2( Rect() );
        
        TInt width = ( buttonRect1.iBr.iX - buttonRect1.iTl.iX ) / 2 - 4; 
        
        buttonRect1.iBr.iX = buttonRect1.iTl.iX + width;
        buttonRect2.iTl.iX = buttonRect2.iBr.iX - width;
        
        if ( (*iControlArray)[KControlArrayCBAButton1Posn].iControl )
            {
            (*iControlArray)[KControlArrayCBAButton1Posn].iControl->SetRect( buttonRect1 );
            }
        
        if ( (*iControlArray)[KControlArrayCBAButton2Posn].iControl )
            {
            (*iControlArray)[KControlArrayCBAButton2Posn].iControl->SetRect( buttonRect2 );
            }
        }
    }
    
    
void CEikCba::SizeChangedInPopup()
    {
    TRAP_IGNORE( iExtension->UpdateSoftkeyFrameL( EFalse ) );
    
    TAknLayoutRect layoutRect;
    TRect rect ( Rect() );

    // Button widths are calculated based on cba area width
    // margin width is taken from layout
    layoutRect.LayoutRect(
        rect, 
        AknLayoutScalable_Avkon::popup_sk_window_g1( 0 ) );
    
    TInt margin = layoutRect.Rect().iTl.iX - rect.iTl.iX;
    TInt buttonWidth = ( rect.Width() - margin * 2 ) / 2;
    TSize buttonSize ( buttonWidth, layoutRect.Rect().Height() );
        
    iExtension->iLeftFrameOuterRect = TRect(
            TPoint( rect.iTl.iX + margin, layoutRect.Rect().iTl.iY ), 
            buttonSize );
    iExtension->iRightFrameOuterRect = TRect( 
            TPoint( iExtension->iLeftFrameOuterRect.iBr.iX, 
                    layoutRect.Rect().iTl.iY ), 
            TPoint( rect.iBr.iX - margin, layoutRect.Rect().iBr.iY ) );

    layoutRect.LayoutRect( iExtension->iLeftFrameOuterRect,
                 AknLayoutScalable_Avkon::bg_sctrl_sk_pane_g1()
                     .LayoutLine() );
    iExtension->iLeftFrameInnerRect = layoutRect.Rect();
    UpdateLabels( ETrue );
    
    layoutRect.LayoutRect( iExtension->iRightFrameOuterRect,
                 AknLayoutScalable_Avkon::bg_sctrl_sk_pane_g1()
                     .LayoutLine() );
    iExtension->iRightFrameInnerRect = layoutRect.Rect();
    UpdateLabels( ETrue );
    
    if ( iControlArray->Count() > KControlArrayCBAButtonMSKPosn )
        {
        CCoeControl* msk = 
            (*iControlArray)[KControlArrayCBAButtonMSKPosn].iControl;
        
        if ( msk )
            {
            msk->SetRect( TRect() );
            }
        }
    }
    

void CEikCba::UpdateFonts()
    {
    // Control pane:
    // Use the layout dll to get the right font for the CBA.
    TAknTextLineLayout layout(
        AknLayoutScalable_Avkon::control_pane_t1(
            Layout_Meta_Data::IsLandscapeOrientation() ? 2 : 0 ).LayoutLine() );
    if ( iCbaFlags & EEikCbaFlagOutlineFont )
        {
        // Sets outline font property.
        layout.iFont |= KOutlineFontMask;
        }
    const CFont* customfont = 0;
    iLabelFont = AknLayoutUtils::FontFromId( layout.FontId(), customfont );

    // Stacon pane:
    TAknTextLineLayout staconTextLayout(
        AknLayoutScalable_Avkon::control_bottom_pane_stacon_t1( 0 ).LayoutLine() );

    if ( iCbaFlags & EEikCbaFlagOutlineFont )
        {
        // Sets outline font property.
        staconTextLayout.iFont |= KOutlineFontMask;
        }
    const CFont* staconCustomfont = 0;
    iStaconLabelFont = AknLayoutUtils::FontFromId( staconTextLayout.FontId(),
                                                   staconCustomfont );
    
    // Right pane:    
    TInt rightPaneTextVariety = 0;
    
    if ( iExtension->iEnablePostingTransparency ||
         ( iCbaFlags & EEikCbaFlagTransparent ) || ( iCbaFlags & EEikCbaFlagSemiTransparent ) )
        {
        rightPaneTextVariety = 1; // Outline font used
        }

    TAknTextLineLayout rightPaneTextLayout(
        AknLayoutScalable_Avkon::sctrl_sk_bottom_pane_t1(
            rightPaneTextVariety ).LayoutLine() );

    if ( iCbaFlags & EEikCbaFlagOutlineFont )
        {
        // Sets outline font property.
        rightPaneTextLayout.iFont |= KOutlineFontMask;
        }
    const CFont* rightPaneCustomFont = 0;
    iRightPaneLabelFont = 
        AknLayoutUtils::FontFromId( 
            rightPaneTextLayout.FontId(), rightPaneCustomFont );
    }

// Enhanced CBA

// -----------------------------------------------------------------------------
// Used to offer list of commands for softkeys.
// @param aCommandList A list of command ids to be offered for sofkeys.
// @since 5.0
// -----------------------------------------------------------------------------
#ifdef RD_ENHANCED_CBA
EXPORT_C void CEikCba::OfferCommandListL(const RArray<TInt>& aCommandList)
    {   
    if( !iCommandTable )
        {        
        iCommandTable = CEikCommandTable::NewL();  
        }
    else
        {
        delete iCommandTable;
        iCommandTable = NULL;
        iCommandTable = CEikCommandTable::NewL();
        }
    
    TInt count = aCommandList.Count();
    
    // Stack existing commands for possible leave while adding the new commands.
    RArray<TInt> previousIds;
    CleanupClosePushL( previousIds );
    
    // Store the existing commands.
    for ( TInt i = 0; i < iControlArray->Count(); i++ )
        {
        TEikGroupControl& groupCtrl=(*iControlArray)[i];
        previousIds.AppendL( groupCtrl.iId );        
        }
                        
    iCommandTable->Reset();
           
    for ( TInt ii = 0; ii < count; ii++ )
        {
        TInt resourceId( aCommandList[ii] );
        
        TResourceReader reader;
        iCoeEnv->CreateResourceReaderLC( reader, resourceId );
        
        TUint8 version( (TUint8)reader.ReadUint8() );        
        TInt longCommandId( 0 );
       
        CEikEnhancedCbaButton* button = new (ELeave) CEikEnhancedCbaButton;
        CleanupStack::PushL( button );
        
        if( version == EEikCbaButtonLink )
            {
            TInt aButtonId = reader.ReadInt32(); // Read ENHANCED_CBA_BUTTON id from LLINK
            TResourceReader linkReader; // reader for reading linked resource
            iCoeEnv->CreateResourceReaderLC( linkReader, aButtonId );
            TUint8 ver( linkReader.ReadUint8() );
                    
            if( ver == EEikEnhancedCbaButton )
                {
                button->ConstructFromResourceL( linkReader );               
                }                       
            CleanupStack::PopAndDestroy( ); // linkReader                   
            }
        else if( version == EEikEnhancedCbaButton )
            {
            button->ConstructFromResourceL( reader );                       
            }
        else // command version not regognized
            {
            CleanupStack::PopAndDestroy(2); // button and reader
            continue; // go for next command    
            }
            
        iCommandTable->AddCommandL( button ); 
            
        CleanupStack::Pop( button );
        CleanupStack::PopAndDestroy(); // reader        
        }
        
    for (TInt i = 0; i < KMaxButtonsInCommandTable + 1; i++) // +1 for scrollbar
        {
        if ( i != KControlArrayScrollBarPosn )
            {
            CEikEnhancedCbaButton* button;
            if( i > KControlArrayScrollBarPosn )
                {
                button = iCommandTable->Command( i-1 );
                }               
            else
                {
                button = iCommandTable->Command( i );
                }               
            
            if ( !button )
                {
                button = new (ELeave) CEikEnhancedCbaButton;
                button->SetTextBitmapMode( iExtension->iEnablePostingTransparency );
                CleanupStack::PushL( button );
                button->ConstructEmptyButtonL();
                }
            else
                {
                CleanupStack::PushL( button );
                }
            
            TRAPD( errorcode, AddCommandToStackL( i, button->CommandId(), button->LabelText(), 
                NULL, NULL ) );
            
            if ( errorcode )  // In case of error restore previous commands before leave
                {
                for ( TInt counter = 0; counter < i; counter++ )
                    {
                    // Do not deal with the scroller as a CEikCbaButton; skip its index.
                    if (counter != KControlArrayScrollBarPosn)
                        {
                        // Following adjusts for the fact that the scroller command is
                        // missing from the previousIds array. Same index adjust as later on.
                        TInt indexInPreviousIds = counter;
                        if ( counter > 1 )
                            {
                            indexInPreviousIds = counter - 1; 
                            }                            
                        RemoveCommandFromStack( counter,previousIds[indexInPreviousIds] );
                        }
                    }
            
                User::Leave( errorcode );
                }           
            CleanupStack::PopAndDestroy( button );
            }
        }    
    
    // Remove the original commands from the temporary store. +1 for scroll bar.
    for ( TInt controlId = 0; controlId < KMaxButtonsInCommandTable + 1; controlId++ ) 
        {
        if ( controlId != KControlArrayScrollBarPosn )
            {
            TInt controlPosition = controlId;
            if ( controlId > 1  )
                {
                controlPosition--;
                }                
            RemovePreviousCommand( controlId );
            }
        }
        
    CleanupStack::PopAndDestroy(); // previousIds    
    }
#else // !RD_ENHANCED_CBA
EXPORT_C void CEikCba::OfferCommandListL(const RArray<TInt>& /*aCommandList*/)
    {
    User::Leave( KErrNotSupported );
    }
#endif // RD_ENHANCED_CBA

// -----------------------------------------------------------------------------
// Used to offer list of commands for softkeys.
// @param aResourceId Id for CBA resource that defines enhanced cba buttons.
// @since 5.0
// -----------------------------------------------------------------------------
#ifdef RD_ENHANCED_CBA
EXPORT_C void CEikCba::OfferCommandListL(const TInt aResourceId)
    {
    if ( !iCommandTable ) // This is needed if cba was not constructed with enhanced cba.
        {
        iCommandTable = CEikCommandTable::NewL();
        }
    
    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC(reader, aResourceId);
    iCbaFlags = reader.ReadInt32();
    
    TBool enhancedCba( EFalse );    
    if ( ( iCbaFlags & EEikEnhancedButtonGroup ) == EEikEnhancedButtonGroup ) 
        { 
        enhancedCba = ETrue;
        }
    
    __ASSERT_DEBUG( enhancedCba, Panic(EEikPanicCBAIsNotEnhancedCba) );
    
    reader.ReadInt16(); // Skip width resource.
    reader.ReadInt32(); // Skip related buttons resource.
    
    TInt count = reader.ReadInt16();        
    
    // Stack existing commands for possible leave while adding the new commands.
    RArray<TInt> previousIds;
    CleanupClosePushL( previousIds );  
    
    // Store the existing commands.
    for ( TInt i = 0; i < iControlArray->Count(); i++ )
        {
        TEikGroupControl& groupCtrl = (*iControlArray)[i];
        previousIds.AppendL( groupCtrl.iId );
        }
                        
    iCommandTable->Reset();
    
    // Get new commands.  
    for ( TInt ii = 0; ii < count; ii++ )
        {        
        TUint8 version( (TUint8)reader.ReadUint8() );
        TInt commandId( 0 );
        TInt longCommandId( 0 );
       
        CEikEnhancedCbaButton* button = new (ELeave) CEikEnhancedCbaButton;
        button->SetTextBitmapMode( iExtension->iEnablePostingTransparency );
        CleanupStack::PushL( button );
        
        if( version == EEikCbaButtonLink )
            {           
            TInt aButtonId = reader.ReadInt32(); // Read ENHANCED_CBA_BUTTON id from LLINK
            TResourceReader linkReader; // reader for reading linked resource
            iCoeEnv->CreateResourceReaderLC( linkReader, aButtonId );
            TUint8 ver( linkReader.ReadUint8() );
                    
            if( ver == EEikEnhancedCbaButton )
                {
                button->ConstructFromResourceL( linkReader );               
                }           
                
            CleanupStack::PopAndDestroy(); // linkReader            
            }
        else if( version == EEikEnhancedCbaButton )
            {
            button->ConstructFromResourceL( reader );                       
            }
        else
            {
            CleanupStack::PopAndDestroy( button );
            continue;  // jump over the rest    
            }
            
        iCommandTable->AddCommandL( button );
        
        CleanupStack::Pop( button );
        }       
            
    CleanupStack::PopAndDestroy(); // reader
    
    for (TInt i = 0; i < KMaxButtonsInCommandTable + 1; i++) // +1 for scrollbar
        {
        if ( i != KControlArrayScrollBarPosn )
            {
            CEikEnhancedCbaButton* button;
            if( i > KControlArrayScrollBarPosn )
                {
                button = iCommandTable->Command( i - 1 );
                }           
            else
                {
                button = iCommandTable->Command( i );
                }               
            
            if ( !button )
                {
                button = new (ELeave) CEikEnhancedCbaButton;
                button->SetTextBitmapMode( iExtension->iEnablePostingTransparency );
                CleanupStack::PushL( button );
                button->ConstructEmptyButtonL();
                }
            else
                {
                CleanupStack::PushL( button );
                }
            
            TRAPD( errorcode, AddCommandToStackL( i, button->CommandId(), button->LabelText(), 
                NULL, NULL ) );
            
            if ( errorcode )  // In case of error restore previous commands before leave.
                {
                for ( TInt counter = 0; counter < i; counter++ )
                    {
                    // Do not deal with the scroller as a CEikCbaButton; skip its index.
                    if ( counter != KControlArrayScrollBarPosn )
                        {
                        // Following adjusts for the fact that the scroller command is
                        // missing from the previousIds array. Same index adjust as later on.
                        TInt indexInPreviousIds = counter;
                        if ( counter > 1 )
                            {
                            indexInPreviousIds = counter - 1; 
                            }                            
                        RemoveCommandFromStack( counter, previousIds[indexInPreviousIds] );
                        }
                    }            
                User::Leave( errorcode );
                }           
            CleanupStack::PopAndDestroy( button );
            }       
        }    
    
    // Remove the original commands from the temporary store.  +1 for scroll bar.
    for ( TInt controlId = 0; controlId < KMaxButtonsInCommandTable + 1; controlId++ )
        {
        if ( controlId != KControlArrayScrollBarPosn )
            {
            TInt controlPosition=controlId;
            if ( controlId > 1 )
                {
                controlPosition--;
                }
                
            RemovePreviousCommand( controlId );
            }
        }
    
    CleanupStack::PopAndDestroy(); // previousIds 
    }
#else // !RD_ENHANCED_CBA   
EXPORT_C void CEikCba::OfferCommandListL(const TInt /*aResourceId*/)
    {
    User::Leave( KErrNotSupported );
    }
#endif // RD_ENHANCED_CBA
    
// -----------------------------------------------------------------------------
// Used to check if a certain command have been approved to the current command set.
// @param aCommandId The id for command which existence should be checked.
// @since 5.0
// -----------------------------------------------------------------------------    
#ifdef RD_ENHANCED_CBA  
EXPORT_C TBool CEikCba::IsCommandInGroup(const TInt aCommandId) const
    {
    return ButtonById(aCommandId) ? ETrue : EFalse; // check the iControlArray
    }
#else // !RD_ENHANCED_CBA
EXPORT_C TBool CEikCba::IsCommandInGroup(const TInt /*aCommandId*/) const
    {
    return EFalse;
    }
#endif // RD_ENHANCED_CBA
    
// -----------------------------------------------------------------------------
// Replace existing command with a new command
// @param aCommandId Id for command that should be replaced.
// @param aResourceId Resource id for new enhanced cba button.
// @since 5.0
// -----------------------------------------------------------------------------    
#ifdef RD_ENHANCED_CBA  
EXPORT_C void CEikCba::ReplaceCommand(const TInt aReplaceCommandId, const TInt aResourceId)
    {
    TInt index = IndexById( aReplaceCommandId );
    TRAPD(err, SetCommandL( index, aResourceId ) );     
    }
#else
EXPORT_C void CEikCba::ReplaceCommand(const TInt /*aReplaceCommandId*/, const TInt /*aResourceId*/)
    {
    }
#endif // RD_ENHANCED_CBA

void CEikCba::HandleControlEventL( CCoeControl* aControl, TCoeEvent aEventType )
    {
    if ( !iFlags.IsSet( ECbaInsideDialog ) )
        {
        //User::Panic( _L( "CBA inside dialog" ), KErrNotSupported );
        return;
        }
        
    if ( aEventType == EEventStateChanged )
        {
        TInt command = NULL;
        
        if ( aControl == (*iControlArray)[KControlArrayCBAButton1Posn].iControl )
            {
            command = (*iControlArray)[KControlArrayCBAButton1Posn].iId;
            }
        else if ( aControl == (*iControlArray)[KControlArrayCBAButton2Posn].iControl )
            {
            command = (*iControlArray)[KControlArrayCBAButton2Posn].iId;
            }
        
        // CAknButton sends control event to CEikCba upon pointer event,
        // while also increasing it's state value. Because of the way
        // CAknButton is used as softkey control, and it's states as stack
        // support, we must revert the state back here.
        CAknButton* button = static_cast<CAknButton*>( aControl );
        TInt state( button->StateIndex() );
        if ( state > 0 )
            {
            state--;
            button->SetCurrentState( state, EFalse );
            }
        

        if( command )
            {
            iCommandObserver->ProcessCommandL( command );
            }
        }
    }


void CEikCba::MakeVisible( TBool aVisible )
    {    
    if ( aVisible )
        {
        TBool redrawNeeded( EFalse );

        if ( AknLayoutUtils::PenEnabled() )
            {
            CEikCbaButton* leftSK = static_cast<CEikCbaButton*>(
                    (*iControlArray)[KControlArrayCBAButton1Posn].iControl );
            CEikCbaButton* rightSK = static_cast<CEikCbaButton*>(
                    (*iControlArray)[KControlArrayCBAButton2Posn].iControl );
            CEikCbaButton* middleSK = NULL;
            
            if ( iMSKset && AknLayoutUtils::MSKEnabled() )
                {
                middleSK =
                    static_cast<CEikCbaButton*>(
                        (*iControlArray)[KControlArrayCBAButtonMSKPosn].iControl );
                }            

            if ( leftSK && leftSK->PressedDown() )
                {
                leftSK->SetPressedDown( EFalse );
                redrawNeeded = ETrue;
                }

            if ( rightSK && rightSK->PressedDown() )
                {
                rightSK->SetPressedDown( EFalse );
                redrawNeeded = ETrue;
                }

            if ( middleSK && middleSK->PressedDown() )
                {
                middleSK->SetPressedDown( EFalse );
                redrawNeeded = ETrue;
                }

            if ( redrawNeeded )
                {
                SizeChanged();
                }
            }

        if ( iFlags[ECbaChangeRecordedSkin] )
            {
            DoSkinChange();
            }

        if ( iFlags[ECbaChangeRecordedLayout] )
            {
            DoLayoutChange();
            redrawNeeded = ETrue;
            }

        if ( iFlags[ECbaChangeRecordedColor] )
            {
            DoColorChange();
            }

        TBool isVisible = IsVisible();
        CEikControlGroup::MakeVisible( aVisible );

        if ( redrawNeeded || !isVisible || IsEmpty() )
            {
            if ( iFlags.IsSet( ECbaInsideDialog ) )
                {
                DrawDeferred();
                }
            else
                {
                DrawNow();  
                }
            }
        }
    else
        {
        Window().ClearRedrawStore();
        CEikControlGroup::MakeVisible( aVisible );
        }

    ReportContentChangedEvent();
    }


// -----------------------------------------------------------------------------
// Sets layer images and rects.
// @since 5.0
// -----------------------------------------------------------------------------
void CEikCba::DoSetLayers( const TAknsItemID& aIID )
    {
    // Skin background is not drawn by embedded CBA.
    if ( iFlags.IsSet( ECbaEmbedded ) )
        {
        return;
        }

    TAknLayoutRect cbarect;
    TRect screen;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screen );

    TAknWindowComponentLayout applicationWindow(
        AknLayoutScalable_Avkon::application_window( 0 ) );

    TBool isLandscape( Layout_Meta_Data::IsLandscapeOrientation() );
    TBool rightPaneActive( IsAreaSideRightPaneActive() );
    TBool idleLayout( AknStatuspaneUtils::IdleLayoutActive() );    

    if ( rightPaneActive )
        {
        cbarect.LayoutRect(
            screen,
            DoCompose(
                applicationWindow,
                AknLayoutScalable_Avkon::area_side_right_pane( 0 ) ).LayoutLine() );
        }
    else
        {
        // We must check for landscape mode bottom SKs 
        TInt bottomPaneVariety = 1;
        
        if ( isLandscape )
            {
            // In flat iBgContext is used and flat is "landscape".
            bottomPaneVariety = 6;
            }

        TAknWindowComponentLayout bottomArea(
            AknLayoutScalable_Avkon::area_bottom_pane( bottomPaneVariety ) );
        TAknWindowComponentLayout controlPane(
            AknLayoutScalable_Avkon::control_pane() );
        controlPane = DoCompose(
            applicationWindow,
                DoCompose(
                    bottomArea, controlPane ) );
        cbarect.LayoutRect( screen, controlPane.LayoutLine() );
        }
        
    TRect cbaRect( cbarect.Rect() );

    TAknsItemID myIID( iBgIID );
    TAknsItemID maskIID( KAknsIIDNone );
    
    if ( AknLayoutUtils::PenEnabled() )
        {
        // Widescreen landscape layout or touch portrait.
        
        // Empty the layers.
        for ( TInt i = 0; i < ECbaLayerN; i++ )
            {
            iMLBgContext->SetLayerImage( i, KAknsIIDNone );
            }
        
        TInt currentBgIIDMinor( aIID.iMinor );
        if ( aIID == KAknsIIDNone )
            {
            currentBgIIDMinor = iBgIID.iMinor;
            }
        
        // Right pane CBA areas don't have their own skin
        // backgrounds, so the screen background is used
        // and correct ID is mapped here.
        switch ( currentBgIIDMinor )
            {
            case EAknsMinorNone:
                {
                if ( rightPaneActive )
                    {
                    myIID = idleLayout ? KAknsIIDQsnBgScreenIdle :
                                         KAknsIIDQsnBgScreen;
                    }
                else
                    {
                    myIID = idleLayout ? KAknsIIDQsnBgAreaControlIdle :
                                         KAknsIIDQsnBgAreaControl;
                    }
                break;
                }
            case EAknsMinorQsnBgAreaControl:
            default:
                {
                if ( rightPaneActive )
                    {
                    myIID = idleLayout ? KAknsIIDQsnBgScreenIdle :
                                         KAknsIIDQsnBgScreen;
                    }
                else
                    {
                    myIID = idleLayout ? KAknsIIDQsnBgAreaControlIdle :
                                         KAknsIIDQsnBgAreaControl;
                    }
                break;
                }
            case EAknsMinorQsnBgAreaControlPopup:
                {
                if ( rightPaneActive )
                    {
                    myIID = idleLayout ? KAknsIIDQsnBgScreenIdle :
                                         KAknsIIDQsnBgScreen;
                    }
                else
                    {
                    myIID = idleLayout ? KAknsIIDQsnBgAreaControlIdle :
                                         KAknsIIDQsnBgAreaControlPopup;
                    }
                break;
                }
            case EAknsMinorQsnBgAreaControlIdle:
                {
                if ( rightPaneActive )
                    {
                    myIID = idleLayout ? KAknsIIDQsnBgScreenIdle :
                                         KAknsIIDQsnBgScreen;
                    }
                else
                    {
                    myIID = idleLayout ? KAknsIIDQsnBgAreaControlIdle :
                                         KAknsIIDQsnBgAreaControl;
                    }
                break;
                }
            case EAknsMinorQsnBgAreaControlMp:
                {
                myIID = rightPaneActive ? KAknsIIDQsnBgScreenMp :
                                          KAknsIIDQsnBgAreaControlMp;
                break;
                }
            }
        if ( idleLayout && iExtension && !( iExtension->iWallpaperInUse == 0 ))
            {
            maskIID = KAknsIIDQgnIndiSctrlSkMaskRightPrt;
            }
        else
            {
            maskIID = rightPaneActive ? KAknsIIDQgnGrafBgLscBottomMaskIcon :
                                        KAknsIIDQgnGrafBgPrtBottomMaskIcon;
            }

        if ( idleLayout )
            {
            if ( iExtension && iExtension->iWallpaperInUse == 0 )
                {
                iMLBgContext->SetLayerImage( ECbaLayerWallpaper, myIID );
                iMLBgContext->SetLayerRect(
                    ECbaLayerWallpaper, rightPaneActive ? screen : cbaRect );
                }
            else
                {
                iMLBgContext->SetLayerImage( ECbaLayerWallpaper, KAknsIIDWallpaper );
                iMLBgContext->SetLayerRect( ECbaLayerWallpaper, screen );
                }
            }
        else
            {
            iMLBgContext->SetLayerImage( ECbaLayerWallpaper, KAknsIIDNone );
            maskIID = KAknsIIDNone;
            }

        iMLBgContext->SetLayerImage( ECbaLayerBackground, myIID );
        iMLBgContext->SetLayerRect(
            ECbaLayerBackground, rightPaneActive ? screen : cbaRect );

        if (iExtension &&
            (!(iExtension->iBackgroundMaskID == maskIID && iExtension->iCbaRect == cbaRect) ||
            iExtension->iIfSkinChanged ||
            iExtension->iBackgroundMaskID == KAknsIIDNone))
            {
            TRAP_IGNORE( iMLBgContext->SetLayerMaskAndSizeL(
                maskIID, rightPaneActive ? screen : cbaRect ) );
            iExtension->iBackgroundMaskID = maskIID;  
            iExtension->iCbaRect = cbaRect;
           }
        }
    else // non-nHD layout
        {            
        if ( idleLayout )
            {                
            if ( aIID == KAknsIIDNone )
                {
                myIID = iBgIID;
                }
            
            iMLBgContext->SetLayerImage( ECbaLayerWallpaper, KAknsIIDWallpaper );
            iMLBgContext->SetLayerRect( ECbaLayerWallpaper, screen );
            iMLBgContext->SetLayerImage( ECbaLayerBackground, myIID );
            iMLBgContext->SetLayerRect( ECbaLayerBackground, cbaRect );

            if ( isLandscape )
                {
                maskIID = KAknsIIDQgnGrafBgLscSideRightMaskIcon;
                }
            else
                {
                maskIID = KAknsIIDQgnGrafBgPrtBottomMaskIcon;
                }
            }
        else
            {
            if ( aIID == KAknsIIDNone )
                {
                myIID = KAknsIIDQsnBgAreaControl;
                }
            
            iMLBgContext->SetLayerImage( ECbaLayerBackground, myIID );
            iMLBgContext->SetLayerImage( ECbaLayerWallpaper, KAknsIIDNone );
            iMLBgContext->SetLayerRect( ECbaLayerBackground, cbaRect );
            }

        TRAP_IGNORE( iMLBgContext->SetLayerMaskAndSizeL( maskIID, cbaRect ) );
        }
        
    DrawDeferred();
    }


void CEikCba::LayoutControl( CCoeControl* aControl, const TRect& aRect )
    {   
    if ( !iFlags.IsSet( ECbaInsideDialog ) )
        {
        TRect rect( aRect );        
        // aid_value_unit2 is 10ux10u rectangle.
        TAknWindowComponentLayout unit( AknLayoutScalable_Avkon::aid_value_unit2() );
        // Move 0.5 units to right and down.
        TInt delta = unit.LayoutLine().iW / 10 / 2;
        if ( ( (CEikCbaButton*)aControl )->PressedDown() )
            {
            rect.Move( delta, delta );
            }        
        aControl->SetRect( rect );
        aControl->ComponentControl( 0 )->SetRect( rect );            
        }
    }

void CEikCba::BroadcastPostingTransparency( TBool aEnable )
    {
    // Communicate change to CBA buttons.
    for ( TInt i = 0; i < iControlArray->Count(); i++ ) 
        {
        if ( i != KControlArrayScrollBarPosn ) // To avoid tinkering with scrollbar.
            {
            TEikGroupControl& gCtrl = iControlArray->At( i );
            CEikCbaButton* button = dynamic_cast<CEikCbaButton*>( gCtrl.iControl );
            if ( button )
                {
                button->SetTextBitmapMode( aEnable );
                }
            }
        }
    }


// ---------------------------------------------------------------------------
// CEikCba::SetFadeState
// Sets the CBA faded if it's contents are empty.
// ---------------------------------------------------------------------------
//
void CEikCba::SetFadeState()
    {
    TBool canBeFaded =
        IsEmpty() && !( ( iCbaFlags & EEikCbaFlagTransparent )
        || ( iExtension && iExtension->iEnablePostingTransparency ) );

    // No unfading when system is faded
    if ( !( !canBeFaded
            && static_cast<CAknAppUi*>( iCoeEnv->AppUi() )->IsFaded() ) )
        {
        Window().SetFaded( canBeFaded, RWindowTreeNode::EFadeIncludeChildren );
        }
    }


// ---------------------------------------------------------------------------
// CEikCba::UpdateLabels
// Updates softkey labels in case of embedded softkeys.
// ---------------------------------------------------------------------------
//
void CEikCba::UpdateLabels( TBool aDrawDeferred )
    {
    if ( iControlArray->Count() != 0)
        {
        CCoeControl *leftSoftkey = ( *iControlArray )
            [ KControlArrayCBAButton1Posn ].iControl;
        CCoeControl *rightSoftkey = ( *iControlArray )
            [ KControlArrayCBAButton2Posn ].iControl;
        
        if ( !( ( ( CEikCbaButton* ) leftSoftkey )->IsImageOn() ) )
            {         
            TAknTextLineLayout textLayout(
                AknLayoutScalable_Avkon::popup_sk_window_t1( 0 ).LayoutLine() );
            
            if ( iCbaFlags & EEikCbaFlagOutlineFont )
                {                
                textLayout.iFont |= KOutlineFontMask;
                }
            
            AknLayoutUtils::LayoutLabel( ( CEikLabel* ) 
                leftSoftkey->ComponentControl( 0 ), 
                Rect(), 
                textLayout );    
                  
            LayoutControl( (CEikCbaButton*)leftSoftkey, 
                leftSoftkey->ComponentControl( 0 )->Rect() );            
            ((CEikCbaButton*)leftSoftkey)->TruncateLabelText();
            }
            
        if ( !( ( ( CEikCbaButton* ) rightSoftkey )->IsImageOn() ) )
            {
            TAknTextLineLayout textLayout(
                AknLayoutScalable_Avkon::popup_sk_window_t1_copy1( 0 ).LayoutLine() );

            if ( iCbaFlags & EEikCbaFlagOutlineFont )
                {                
                textLayout.iFont |= KOutlineFontMask;
                }
            AknLayoutUtils::LayoutLabel((CEikLabel*)
                rightSoftkey->ComponentControl( 0 ),
                Rect(), 
                textLayout );        
            LayoutControl( (CEikCbaButton*)rightSoftkey, 
                rightSoftkey->ComponentControl( 0 )->Rect() );            
            ((CEikCbaButton*)rightSoftkey)->TruncateLabelText();
            }
        
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        
        TRgb leftColor;
        TRgb rightColor;
        
        TInt errorl;
        TInt errorr;
            
        if ( iPopupVisible )
            {
            errorl = AknsUtils::GetCachedColor( 
                skin,
                leftColor,
                KAknsIIDQsnTextColors,
                EAknsCIQsnTextColorsCG17 );
                
            errorr = AknsUtils::GetCachedColor( 
                skin,
                rightColor,
                KAknsIIDQsnTextColors,
                EAknsCIQsnTextColorsCG18  );    
            }
        else
            {
            errorl = AknsUtils::GetCachedColor( 
                skin,
                leftColor,
                KAknsIIDQsnTextColors,
                EAknsCIQsnTextColorsCG13 );
                
            errorr = AknsUtils::GetCachedColor( 
                skin,
                rightColor,
                KAknsIIDQsnTextColors,
                EAknsCIQsnTextColorsCG14 );
            }

        if ( ((CEikCbaButton*)leftSoftkey)->PressedDown() )
            {            
            leftColor.SetAlpha( KPressedDownAlphaValue );

            AknsUtils::GetCachedColor( 
                skin,
                leftColor,
                KAknsIIDQsnTextColors,
                EAknsCIQsnTextColorsCG69 ); 
            }
        else if ( ((CEikCbaButton*)rightSoftkey)->PressedDown() )
            {
            rightColor.SetAlpha( KPressedDownAlphaValue );
            
            AknsUtils::GetCachedColor( 
                skin,
                rightColor,
                KAknsIIDQsnTextColors,
                EAknsCIQsnTextColorsCG69 );
            }
            
        if( !errorl && !errorr )
            {
            // Error ignored
            TRAP( errorl, AknLayoutUtils::OverrideControlColorL( 
                *leftSoftkey,
                EColorLabelText,
                leftColor) );
                
            TRAP( errorr, AknLayoutUtils::OverrideControlColorL( 
                *rightSoftkey,
                EColorLabelText,
                rightColor) );        
            }
        
        if ( aDrawDeferred )
            {
            DrawDeferred();
            }
        }
    }
    

// -----------------------------------------------------------------------------
// EikSoftkeyPostingTransparency::MakeTransparent
// -----------------------------------------------------------------------------
//
EXPORT_C TInt EikSoftkeyPostingTransparency::MakeTransparent(
    CEikButtonGroupContainer& aButtonGroupContainer,
    TBool aEnable )
    {
    CEikCba* cba = dynamic_cast<CEikCba*>( aButtonGroupContainer.ButtonGroup() );
    TInt ret = KErrNone;
    if ( cba )
        {
        if ( aEnable && ( cba->ButtonGroupFlags() & EEikCbaFlagTransparent ) )
            {
            // EikSoftkeyPostingTransparency is not supported if 
            // EEikCbaFlagTransparent is enabled
            ret = KErrArgument;
            }
        else
            {
            cba->EnablePostingTransparency( aEnable );
            }
        }
    return ret;
    }

// -----------------------------------------------------------------------------
// CEikCba::EnablePostingTransparency
//
// -----------------------------------------------------------------------------
//
void CEikCba::EnablePostingTransparency( TBool aEnable )
    {
    if ( iExtension )
        {
        if ( iExtension->iEnablePostingTransparency != aEnable )
            {
            iExtension->iEnablePostingTransparency = aEnable;
            
            UpdateFonts();
            
            if ( !aEnable )
                {
                delete iExtension->iLskPostingOverlayBitmap;
                iExtension->iLskPostingOverlayBitmap = NULL;
                delete iExtension->iRskPostingOverlayBitmap;
                iExtension->iRskPostingOverlayBitmap = NULL;

                // Update label text color. SizeChanged
                // will not call BroadcastPostingTransparency in this case.
                // It has to be called directly from here.
                SizeChanged();

                BroadcastPostingTransparency( EFalse );
                }
            else
                {
                // Update background bitmaps. SizeChanged
                // will also call BroadcastPostingTransparency.
                SizeChanged();
                }

            DrawDeferred();
            }
        }
    }


// ---------------------------------------------------------------------------
// CEikCba::IsEmpty
// Checks if the CBA has no commands.
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CEikCba::IsEmpty() const
    {
    TBool isEmpty( ETrue );

    if ( iFlags.IsSet( ECbaInsideDialog ) )
        {
        // Not supported for full screen query.
        isEmpty = EFalse;
        }
    else
        {
        for ( TInt i = 0; i < iControlArray->Count(); i++ )
            {
            if ( i != KControlArrayScrollBarPosn ) // Do not take scrollbar into account.
                {
                TEikGroupControl& gCtrl = iControlArray->At( i );
                if ( gCtrl.iId != EEikBidBlank &&
                     gCtrl.iId != EAknSoftkeyEmpty &&
                    ( gCtrl.iId < 0 || gCtrl.iId > 2 ) )
                    {
                    isEmpty = EFalse;
                    }
                else
                    {
                    if ( gCtrl.iControl &&
                         ( !(static_cast<CEikCbaButton*>(gCtrl.iControl))->IsEmptyText()
                         || (static_cast<CEikCbaButton*>(gCtrl.iControl))->IsImageOn() )  
                        ) 
                        {
                        isEmpty = EFalse;
                        }
                    }
                }
            }
        }

    return isEmpty;
    }
    
    
// ---------------------------------------------------------------------------
// CEikCba::Flags
// Returns flags.
// ---------------------------------------------------------------------------
//
TBitFlags CEikCba::Flags() 
    {
    return iFlags;
    }


// ---------------------------------------------------------------------------
// CEikCba::SetContentObserver
// Sets content observer.
// ---------------------------------------------------------------------------
//
void CEikCba::SetContentObserver( TCallBack aCallBack )
    {
    if ( iExtension )
        {
        iExtension->iContentObserver = aCallBack;
        }
    }


// ---------------------------------------------------------------------------
// CEikCba::ReportContentChangedEvent
// Reports state changed event if cba changed from empty to non-empty
// or vice versa.
// ---------------------------------------------------------------------------
//     
void CEikCba::ReportContentChangedEvent()
    {
    if ( ItemSpecificSoftkey() )
        {
        UpdateItemSpecificSoftkey(
                iExtension->Active() && !Window().IsFaded() );
        }

    if ( !iFlags.IsSet( ECbaEmbedded ) )
        {
        return;
        }

    TBool isEmpty( !IsVisible() || IsEmpty() );
    TBool reportStateChanged( EFalse );
    if ( !isEmpty && !iFlags.IsSet( ECbaHasContent ) )
        {
        reportStateChanged = ETrue;
        iFlags.Set( ECbaHasContent );
        }
    else if ( isEmpty && iFlags.IsSet( ECbaHasContent ) )
        {
        reportStateChanged = ETrue;
        iFlags.Clear( ECbaHasContent );
        }

    // Report state changed event if changed from empty to non-empty
    // or vice versa. Dialog knows to increase its height so that
    // also cba is visible
    if ( reportStateChanged )
        {
        Window().Invalidate();
        if ( iExtension && iExtension->iContentObserver.iFunction )
            {
            iExtension->iContentObserver.CallBack(); // return value ignored
            }
        }
    }

// ---------------------------------------------------------------------------
// CEikCba::DrawEmbeddedSoftkey
// Draws embedded softkey
// ---------------------------------------------------------------------------
//     
void CEikCba::DrawEmbeddedSoftkey( TEikGroupControl& aGroupControl,
                                   const TRect& aRect,
                                   CWindowGc& aGc,
                                   CFbsBitmap* /*aMask*/ ) const
    {
    CEikCbaButton* button = 
        static_cast<CEikCbaButton*>( aGroupControl.iControl );
    
    TAknLayoutRect layoutRect;
    TRect innerRect;
    layoutRect.LayoutRect( aRect,
                 AknLayoutScalable_Avkon::bg_sctrl_sk_pane_g1()
                     .LayoutLine() );
    innerRect = layoutRect.Rect();
   

    if( button->PressedDown() ) // draw PressedFrame
        {
        AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(),
                                  aGc,
                                  aRect,
                                  innerRect,
                                  KAknsIIDQgnFrSctrlSkButtonPressed,
                                  KAknsIIDQgnFrSctrlSkButtonCenterPressed );
        }
    else       // draw Frame
        {
        AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(),
                                  aGc,
                                  aRect,
                                  innerRect,
                                  KAknsIIDQgnFrSctrlSkButton,
                                  KAknsIIDQgnFrSctrlSkButtonCenter);
        }
    }

TBool CEikCba::UpdateIconL()
        {
        if ( iFlags.IsSet( ECbaInsideDialog ) )
            {
            return EFalse;
            }
        
        if ( !iExtension->iIfMskIconSet ||
             !MskAllowed() )
            {
            return EFalse;         
            }
        
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        if ( !skin )
            { 
            return EFalse;
            }
    
        TEikGroupControl &gCtrl = iControlArray->At( KControlArrayCBAButtonMSKPosn );

        CEikCbaButton *button = static_cast<CEikCbaButton*>( gCtrl.iControl );
        if ( !button )
            {
            return EFalse;
            }
   
        CFbsBitmap *bitmap = NULL;
        CFbsBitmap *mask = NULL;
      
        TAknLayoutRect qgn_graf_sk_msk;
        TRect rect;
        qgn_graf_sk_msk.LayoutRect(
            rect,
            AknLayoutScalable_Avkon::control_pane_g4( 0 ).LayoutLine() );

        TSize iconSize( qgn_graf_sk_msk.Rect().Width(),
                        qgn_graf_sk_msk.Rect().Height() );
        
        AknsUtils::CreateIconL(
            skin,
            iExtension->iMSKSkinID,
            bitmap, 
            mask, 
            *iExtension->iBmpFile, 
            iExtension->iBmp, 
            iExtension->iBmpM );
     
        if ( bitmap ) // Bitmap not set -> do not use image.
            {
            AknIconUtils::DisableCompression( bitmap );
            AknIconUtils::DisableCompression( mask );
            AknIconUtils::SetSize( bitmap, iconSize );
            CEikImage* image = new (ELeave) CEikImage;
            image->SetPicture( bitmap, mask );

            // Transfers ownership of the image (image owns bitmap and mask).
            button->SetImage( *image );
            
            SizeChanged();
            
            button->DrawNow();
            }
        else
            {
            button->ReplaceImageByLabel(); // remove old image
            }
    
        button->SetContainerWindowL( *this );
    
        return ETrue;
    	
        }


// ---------------------------------------------------------------------------
// Checks if the middle softkey should be used.
// Should be used with the SetMSKVisibility-method to set MSK visibility
// when on layout changes etc.
// ---------------------------------------------------------------------------
//     
TBool CEikCba::MskAllowed() const
    {
    return ( iMSKEnabledInPlatform &&
             AknLayoutUtils::MSKEnabled() &&
             IsMskEnabledLayoutActive() );
    }


// ---------------------------------------------------------------------------
// CEikCba::SoftkeyStatusChangeAllowed
// Returns ETrue if softkey status change is allowed.
// ---------------------------------------------------------------------------
//     
TBool CEikCba::SoftkeyStatusChangeAllowed(
        TInt aSoftkeyPosition, TBool aDisabled )
    {
    TBool allowChange( ETrue );
    if ( aSoftkeyPosition == KControlArrayCBAButton1Posn )
        {
        if ( aDisabled )
            {
            iFlags.Set( ECbaItemSoftkeyDisabledByClient );
            }
        else
            {
            iFlags.Clear( ECbaItemSoftkeyDisabledByClient );
            if ( iFlags.IsSet( ECbaItemSoftkeyDisabled ) )
                {
                allowChange = EFalse;
                }
            }
        }
    return allowChange;
    }


// ---------------------------------------------------------------------------
// CEikCba::ItemSpecificSoftkey
// Returns item specific softkey control if it state should be updated.
// ---------------------------------------------------------------------------
//
TEikGroupControl* CEikCba::ItemSpecificSoftkey() const
    {
    TEikGroupControl* lsk( NULL );
    if ( iFlags.IsSet( ECbaItemSpecificSoftkeyInUse ) )
        {
        TEikGroupControl& leftSoftkey =
            ( *iControlArray ) [ KControlArrayCBAButton1Posn ];
        if ( leftSoftkey.iId != EAknSoftkeyOptions
                || iFlags.IsSet( ECbaItemSoftkeyDisabled ) )
            {
            lsk = &leftSoftkey;
            }
        }
    return lsk;
    }


// ---------------------------------------------------------------------------
// CEikCba::UpdateItemSpecificSoftkey
// Updates item specific softkey.
// ---------------------------------------------------------------------------
//     
void CEikCba::UpdateItemSpecificSoftkey( TBool aVisibleCollection )
    {
    if ( iFlags.IsSet( ECbaSingleClickEnabled )
            && iExtension && iExtension->iItemActionMenu )
        {
        TEikGroupControl* leftSk = ItemSpecificSoftkey();
        if ( leftSk )
            {
            TBool enableSk( leftSk->iId == EAknSoftkeyOptions ||
                    iExtension->iItemActionMenu->CollectionSoftkeyVisible(
                            aVisibleCollection ) );
            UpdateItemSpecificSoftkey( *leftSk->iControl, enableSk );
            }
        }
    }


// ---------------------------------------------------------------------------
// CEikCba::UpdateItemSpecificSoftkey
// Updates item specific softkey.
// ---------------------------------------------------------------------------
//
void CEikCba::UpdateItemSpecificSoftkey( CCoeControl& aControl, TBool aEnable )
    {
    TBool skEnabled( aControl.IsVisible() && !aControl.IsDimmed() );
    TBool changeState( EFalse );
    if ( !aEnable )
        {
        iFlags.Set( ECbaItemSoftkeyDisabled );
        if ( skEnabled )
            {
            changeState = ETrue;
            }
        }
    else
        {
        iFlags.Clear( ECbaItemSoftkeyDisabled );
        if ( !skEnabled 
                && iFlags.IsClear( ECbaItemSoftkeyDisabledByClient ) )
            {
            changeState = ETrue;
            }
        }
    if ( changeState )
        {
        if ( !iFlags.IsSet( ECbaInsideDialog ) )
            {
            aControl.MakeVisible( aEnable );
            }
        else
            {
            aControl.SetDimmed( !aEnable );
            aControl.DrawDeferred();
            }
        }
    }


//
// class CEikCbaButton
//

CEikCbaButton::~CEikCbaButton()
    {
    AKNTASHOOK_REMOVE();
    delete iLabel;
    if ( iImage )
        {
        iImage->SetMask( iMask );
        }
    delete iImage;    
    delete iSfeMask;
    delete iButtonOptions;
    delete iText;

    }

void CEikCbaButton::ConstructL(TGulAlignmentValue aAlignment)
    {
    iLabel = new(ELeave) CEikLabel;    
    iPressedDown = EFalse;    
    iLabel->SetBufferReserveLengthL(KMaxCbaLabelLength);
    UpdateLabelText(TPtrC());
    iLabel->SetAlignment(aAlignment);

    iButtonOptions = new(ELeave) CArrayFixFlat<SButtonOptions>(1);
    iText = new(ELeave) CDesCArrayFlat(1);

    if ( iUseTextBitmap )
        {
        iLabel->MakeVisible( EFalse );
        }
    AKNTASHOOK_ADDL( this, "CEikCbaButton" );
    }

void CEikCbaButton::AddCommandL(const TDesC& aText)
    {
    UpdateLabelText(aText);
    }

struct STempCleanup
    {
    CDesCArray* iText;
    CArrayFix<CEikCbaButton::SButtonOptions>* iButtonOptions;
    };

LOCAL_C void CleanupTemp(TAny* aPtr)
    {
    STempCleanup& temp = *(STempCleanup*)aPtr;
    const TInt count = temp.iText->Count();
    if (temp.iButtonOptions->Count() == count)
        {
        temp.iButtonOptions->Delete(count - 1);
        }
    temp.iText->Delete(count - 1);
    }

void CEikCbaButton::PushCommandL(TInt aCommandId,const TDesC& aText)
    {
    if (!iButtonOptions)
        {
        iButtonOptions = new(ELeave) CArrayFixFlat<SButtonOptions>(1);
        }
    if (!iText)
        {
        iText = new(ELeave) CDesCArrayFlat(1);
        }

    iText->AppendL(iFullLabelText);

    STempCleanup temp;
    SButtonOptions options;
    temp.iText = iText;
    temp.iButtonOptions = iButtonOptions;
    CleanupStack::PushL(TCleanupItem(CleanupTemp,&temp));
    options.iCommandId = aCommandId;
    options.iDimmed = iLabel->IsDimmed();
    iLabel->SetDimmed(EFalse);
    iButtonOptions->AppendL(options);
    UpdateLabelText(aText);
    CleanupStack::Pop(); // temp
    }

TInt CEikCbaButton::PopCommand()
    {
    if (!iButtonOptions)
        {
        return -1; 
        }

    TInt count = iButtonOptions->Count();
    --count;
        
    if (count < 0)
        {
        return -1;
        }

    const SButtonOptions buttonOptions = (*iButtonOptions)[count];
    iButtonOptions->Delete(count);
    TPtrC text = (*iText)[count];
    UpdateLabelText(text);
    iText->Delete(count);
    if (iButtonOptions->Count() == 0)
        {
        delete iButtonOptions;
        iButtonOptions = NULL;
        delete iText;
        iText = NULL;
        }
    iLabel->SetDimmed(buttonOptions.iDimmed);
    if (!iDoImage)
        {
        iLabel->DrawDeferred();
        }
    else
        {
        iImage->DrawNow();
        }
    return buttonOptions.iCommandId;
    }

void CEikCbaButton::RemoveCommand(TInt aCommandId)
    {
    if (!iButtonOptions)
        {
        return;
        }
    TInt index = IndexFromCommandId(aCommandId);
    if (index != KErrNotFound)
        {
        iButtonOptions->Delete(index);
        iText->Delete(index);
        if (iButtonOptions->Count() == 0)
            {
            delete iButtonOptions;
            iButtonOptions = NULL;
            delete iText;
            iText = NULL;
            }
        }
    }

void CEikCbaButton::RemovePreviousCommand()
    {
    if (!iButtonOptions)
        {
        return;
        }
    TInt index = iButtonOptions->Count() - 2;
    if (index >= 0)
        {
        iButtonOptions->Delete(index);
        iText->Delete(index);
        }
    }

TInt CEikCbaButton::IndexFromCommandId(TInt aCommandId)
    {
    TInt index;
    TKeyArrayFix key(0, ECmpTInt);
    SButtonOptions options;
    options.iCommandId = aCommandId;
    if (iButtonOptions->Find(options, key, index) == KErrNone)
        {
        return index;
        }
    else
        {
        return KErrNotFound;
        }
    }

void CEikCbaButton::SetContainerWindowL(const CCoeControl& aContainer)
    {
    CCoeControl::SetContainerWindowL(aContainer);
    if (!iDoImage)
        {
        iLabel->SetContainerWindowL(aContainer);
        }
    else
        {
        iImage->SetContainerWindowL(aContainer);
        }
    }

void CEikCbaButton::ConstructFromResourceL(TResourceReader& aReader, TGulAlignmentValue anAlignment)
    {
    ConstructL(anAlignment);
    UpdateLabelText(aReader.ReadTPtrC());
    aReader.ReadTPtrC(); // bmp filename
    aReader.ReadInt16(); // bmp id
    aReader.ReadInt16(); // bmp mask id
    }

TSize CEikCbaButton::MinimumSize()
    {
    if (!iDoImage)
        {
        return iLabel->MinimumSize();
        }
    else
        {
        return iImage->MinimumSize();
        }
    }

TInt CEikCbaButton::CountComponentControls() const
    {
    return 1;
    }

CCoeControl* CEikCbaButton::ComponentControl(TInt aIndex) const
    {
    if (aIndex==0)
        {
        if (!iDoImage)
            {
            return iLabel;
            }
        else
            {
            // If SfeMask is available, then check the effect state (iPressedDown).
            if ( iSfeMask )
                {
                if ( iPressedDown )
                    {                
                    iImage->SetMask( iSfeMask );
                    }
                else
                    {
                    iImage->SetMask( iMask );
                    } 
                }
            return iImage;
            }
        }
    return 0;
    }


// ---------------------------------------------------------------------------
// Handles size change events for CBA button.
// ---------------------------------------------------------------------------
//
void CEikCbaButton::SizeChanged()
    {
    // Resizing is done at CEikCba::SizeChanged().
    // We cannot resize here because this control has wrong
    // coordinate system available.

    }


EXPORT_C void CEikCbaButton::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CCoeControl::HandlePointerEventL(aPointerEvent); 
    }    

EXPORT_C void* CEikCbaButton::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

void CEikCbaButton::SetDimmed(TBool aDimmed)
    {
    CCoeControl::SetDimmed(aDimmed);
    if (!iDoImage)
        {
        iLabel->SetDimmed(aDimmed);
        }
    else
        {
        // Drawing dimmed CEikImages don't work (problem in uiklaf).
        //iImage->SetDimmed(aDimmed);
        }
    }


// ---------------------------------------------------------------------------
// Updates the softkey label.
// ---------------------------------------------------------------------------
//
void CEikCbaButton::UpdateLabelText( TPtrC aLabelText )
    {
    // Updates the label text with the given label, using tab delimited
    // label text to identify normal / alternative labels.
    if ( aLabelText.Length() > KMaxCbaLabelLength )
        {
        // Cannot take more chars than maximum buffer size.
        iFullLabelText.Copy( aLabelText.Left( KMaxCbaLabelLength ) );
        }
    else
        {
        iFullLabelText.Copy( aLabelText );        
        }
    
    TInt find = aLabelText.Locate( CEditableText::ETabCharacter );
    if ( find == KErrNotFound )
        {
        iLongLabelText.Set( iFullLabelText );
        iShortLabelText.Set( iFullLabelText );
        }
    else
        {
        iLongLabelText.Set( iFullLabelText.Left( find ) );
        iShortLabelText.Set(
            iFullLabelText.Right( aLabelText.Length() - find - 1 ) );
        }

    // Default to showing the long text.    
    // Won't leave since we've already set maximum buffer length.
    TRAP_IGNORE( iLabel->SetTextL( iLongLabelText ) ); 
    if ( IsReadyToDraw() )
        {
        TruncateLabelText();
        }
    }


void CEikCbaButton::SetTextBitmapMode( TBool aEnableBitmap )
    {
    iUseTextBitmap = aEnableBitmap;
    if ( iLabel )
        {
        iLabel->MakeVisible( !aEnableBitmap );
        }
    }

void CEikCbaButton::DrawToContext( CBitmapContext& aContext, CBitmapContext& aMaskContext, const TPoint& aOffset ) const
    {
    if ( iLabel )
        {
        // Draw text into EColor16MA bitmap
        aContext.SetOrigin( -aOffset );
        iLabel->DrawToContext( aContext, NULL );

        // Update mask
        // The mask should have a black background and the text in white.
        TRgb maskColor = KRgbWhite;
        aMaskContext.SetOrigin( -aOffset );
        iLabel->DrawToContext( aMaskContext, &maskColor );
        }
    }

void CEikCbaButton::SwitchToShortTextL(TBool aShortText)
    {
    if (aShortText)
        {
        iLabel->SetTextL(iShortLabelText);
        }
    else
        {
        iLabel->SetTextL(iLongLabelText);
        }
        
    if (IsReadyToDraw()) 
        {
        TruncateLabelText();
        }
        
    if (!iDoImage)
        {
        iLabel->DrawDeferred();
        }
    else
        {
        iImage->DrawDeferred();
        }
    }

void CEikCbaButton::SetLabelFont(const CFont* aLabelFont)
    {    
    iLabel->SetFont(aLabelFont);
    }

void CEikCbaButton::TruncateLabelText()
    {
    // Truncation removed from here, as it was not bidi-text compatible.
    // Let CEikLabel handle truncation instead.
    iLabel->CropText();
    }

TBool CEikCbaButton::IsEmptyText() const
    {
    if ( iDoImage )
        {
        return EFalse;
        }
        
    TPtrC text( iFullLabelText );
    TBool allSpaces = ETrue;
    
    for ( TInt i = 0; i < text.Length(); ++i )
        {
        if ( !TChar(text[i]).IsSpace() )
            {
            allSpaces = EFalse;
            break;
            }
        }
        
    return allSpaces;
    }

void CEikCbaButton::ConstructEmptyButtonL()
    {
    ConstructL( EHRightVCenter ); // creates label
    _LIT(KEmptyText, "");
    TPtrC16 ptr(KEmptyText);
    UpdateLabelText( ptr );
    }

TBool CEikCbaButton::PressedDown() const
    {    
    return iPressedDown;
    }
    
void CEikCbaButton::SetPressedDown( const TBool aPressedDown )
    {
    iPressedDown = aPressedDown;
    }

// -----------------------------------------------------------------------------
// EikSoftkeyImage::SetImage
//
// -----------------------------------------------------------------------------
//
EXPORT_C void EikSoftkeyImage::SetImage(
    CEikButtonGroupContainer* aButtonGroupContainer, 
    CEikImage& aImage, 
    TBool aLeft)
    { // static
    TInt commandPos = aLeft ? 0 : 2;
    TInt commandId = aButtonGroupContainer->ButtonGroup()->CommandId(commandPos);
    CEikCbaButton* cbaButton = (CEikCbaButton*) aButtonGroupContainer->ControlOrNull(commandId);
    if ( cbaButton )
        {
        cbaButton->SetImage(aImage);
        // Draw button once with old size, as rect size is different with icon and text
        cbaButton->DrawNow();    
        
        aButtonGroupContainer->SetRect(aButtonGroupContainer->Rect());        
        // Draw previosly set image
        cbaButton->DrawNow();
        aButtonGroupContainer->DrawNow();       
        }    
    }

// -----------------------------------------------------------------------------
// EikSoftkeyImage::SetLabel
//
// -----------------------------------------------------------------------------
//
EXPORT_C void EikSoftkeyImage::SetLabel(
    CEikButtonGroupContainer* aButtonGroupContainer, 
    TBool aLeft)
    { // static
    TInt commandPos = aLeft ? 0 : 2;
    TInt commandId = aButtonGroupContainer->ButtonGroup()->CommandId(commandPos);
    CEikCbaButton* cbaButton = (CEikCbaButton*) aButtonGroupContainer->ControlOrNull(commandId);
    if ( cbaButton )
        {
        cbaButton->ReplaceImageByLabel();
        // Draw button once with old size, as rect size is different with icon and text
        cbaButton->DrawNow();
        
        TRect screenRect = iAvkonAppUi->ApplicationRect();
        aButtonGroupContainer->SetBoundingRect(screenRect);   
        // Draw previosly set label
        cbaButton->DrawNow();
        aButtonGroupContainer->DrawNow();      
        }    
    }

// -----------------------------------------------------------------------------
// CEikCbaButton::SetImage
//
// -----------------------------------------------------------------------------
//
void CEikCbaButton::SetImage(CEikImage &aImage)
    {
    iDoImage = ETrue;
   
    if ( iImage )
        {
        iImage->SetMask( iMask );
        }
    delete iImage;        
    delete iSfeMask;
    iSfeMask = NULL;
    iImage = &aImage;
    if ( iImage )
        {                
        TRAP_IGNORE( PrepareImageL() );
        }
    else
        {
        ReplaceImageByLabel();          
        }
    }

// -----------------------------------------------------------------------------
// CEikCbaButton::PrepareImageL
// Prepares Image for softkey feedback effect. Creates needed mask for 
// pressed down state.
// -----------------------------------------------------------------------------
//
void CEikCbaButton::PrepareImageL()
    {
    // 50% transparent pressed down image is made with a alternative mask
    // which is created when a image is set to CEikCbaButton. 
    // Original mask is copied and each of its pixels color components is 
    // halved. Bit-shifting to the right makes color value to half --> 
    // image looks 50% transparent with this mask
    const CFbsBitmap* mask = iImage->Mask(); 
    iMask = mask;    
    
    if ( !iMask )
        {
        return;
        }

    iSfeMask = new (ELeave) CFbsBitmap;                         
    User::LeaveIfError( iSfeMask->Create( mask->SizeInPixels(), mask->DisplayMode() ) );
    
    CFbsBitmapDevice* device = CFbsBitmapDevice::NewL( iSfeMask );        
    CleanupStack::PushL( device );
    
    CFbsBitGc* gc( NULL );
    User::LeaveIfError( device->CreateContext( gc ) );                
    
    gc->SetPenStyle( CGraphicsContext::ESolidPen );                
    gc->BitBlt( TPoint(0,0), mask );                
                    
    iSfeMask->LockHeap();
    TInt w = iSfeMask->SizeInPixels().iWidth; 
    TInt h = iSfeMask->SizeInPixels().iHeight; 
    TInt dataStride = iSfeMask->DataStride() - w; 
    TUint8* address = (TUint8*) iSfeMask->DataAddress();  
  
    for ( TInt i = 0; i < h; ++i )
        {
        for ( TInt j = 0; j < w; j++ )
            {
            *address >>= 1;
            ++address;
            }
        address += dataStride; 
        }
        
    iSfeMask->UnlockHeap();
    CleanupStack::PopAndDestroy( device ); // device        
    
    delete gc;      
    }
// -----------------------------------------------------------------------------
// CEikCbaButton::ReplaceImageByLabel
//
// -----------------------------------------------------------------------------
//
void CEikCbaButton::ReplaceImageByLabel()
    {
    iDoImage = EFalse;
    if ( iImage )
        {
        // avoid mem leak.
        iImage->SetMask( iMask );
        delete iImage;
        iImage = NULL;          
        delete iSfeMask;
        iSfeMask = NULL;
        }    
    }

//
// CEikEnhancedCbaButton
//

// -----------------------------------------------------------------------------
// default constructor
// -----------------------------------------------------------------------------
CEikEnhancedCbaButton::CEikEnhancedCbaButton()
    {
    }

// -----------------------------------------------------------------------------
// default destructor
// -----------------------------------------------------------------------------
CEikEnhancedCbaButton::~CEikEnhancedCbaButton()
    {
    }

// -----------------------------------------------------------------------------
// Sets command type for current button
// @param aCommandType Command type to be set
// -----------------------------------------------------------------------------
#ifdef RD_ENHANCED_CBA
void CEikEnhancedCbaButton::SetCommandType( const TInt aCommandType )
    {
    iCommandType = aCommandType; 
    }
#else    
void CEikEnhancedCbaButton::SetCommandType( const TInt /*aCommandType*/ )
    {
    }
#endif // RD_ENHANCED_CBA
// -----------------------------------------------------------------------------
// returns command's type for current button
// @return TInt command's type 
// -----------------------------------------------------------------------------

TInt CEikEnhancedCbaButton::CommandType() const
    {
#ifdef RD_ENHANCED_CBA    
    return iCommandType;
#else
    return 0;
#endif // RD_ENHANCED_CBA        
    }

// -----------------------------------------------------------------------------
// returns command id for current button
// @return TInt command's id
// -----------------------------------------------------------------------------
TInt CEikEnhancedCbaButton::CommandId() const
    {
#ifdef RD_ENHANCED_CBA    
    return iCommandId;
#else
    return 0;
#endif // RD_ENHANCED_CBA
    }
    
// -----------------------------------------------------------------------------    
// constructs button based on resource definition
// @param aReader created resource reader for reading information from resource file    
// -----------------------------------------------------------------------------
#ifdef RD_ENHANCED_CBA
void CEikEnhancedCbaButton::ConstructFromResourceL(TResourceReader& aReader)
    {   
    // Alignment set to right.
    ConstructL( EHRightVCenter ); // creates label
    iCommandType = aReader.ReadUint8();
    iCommandId = aReader.ReadInt16();
    // iFullLabelText.Copy( aReader.ReadTPtrC() );
    UpdateLabelText( aReader.ReadTPtrC() );
    
    aReader.ReadTPtrC(); // bmp filename
    aReader.ReadInt16(); // bmp id
    aReader.ReadInt16(); // bmp mask id
    }
#else    
void CEikEnhancedCbaButton::ConstructFromResourceL(TResourceReader&)
    {   
    }
#endif // RD_ENHANCED_CBA    
    
// -----------------------------------------------------------------------------
// Constructs empty button with id EAknSoftkeyEmpty
// -----------------------------------------------------------------------------
void CEikEnhancedCbaButton::ConstructEmptyButtonL()
    {
#ifdef RD_ENHANCED_CBA    
    ConstructL( EHRightVCenter ); // creates label
    iCommandType = EEikCommandTypeAnyCommand;
    iCommandId = EAknSoftkeyEmpty;
    _LIT(KEmptyText, "");
    TPtrC16 ptr(KEmptyText);
    UpdateLabelText( ptr );
#endif    
    }

// -----------------------------------------------------------------------------
// Used to get the label's text for the button
// @return TPtrC label text
// -----------------------------------------------------------------------------    
TPtrC* CEikEnhancedCbaButton::LabelText()
    {
#ifdef RD_ENHANCED_CBA    
    return &iLongLabelText; 
#else
    return NULL;
#endif
    }
    
//
// CEikCommandTable
//

CEikCommandTable* CEikCommandTable::NewL()
    {
#ifdef RD_ENHANCED_CBA    
    CEikCommandTable* self = CEikCommandTable::NewLC();
    CleanupStack::Pop( self );
    return self;    
#else
    return NULL;
#endif         
    }
    
CEikCommandTable* CEikCommandTable::NewLC()
    {
#ifdef RD_ENHANCED_CBA    
    CEikCommandTable* self = new (ELeave) CEikCommandTable;
    CleanupStack::PushL( self );
    self->ConstructL();
    return self; 
#else
    return NULL;
#endif       
    }
    
// -----------------------------------------------------------------------------
// Construction for command table
// priority configuration is read from the resource file
// -----------------------------------------------------------------------------
void CEikCommandTable::ConstructL()
    {
#ifdef RD_ENHANCED_CBA    
    // Get the cba priority configuration
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_EIK_CBA_PRIORITIES );
    
    // Amount of buttons (should match with KMaxButtonsInCommandTable).
    TInt count = reader.ReadInt16(); 
    
    __ASSERT_DEBUG( count == KMaxButtonsInCommandTable, 
        Panic(EEikPanicCBAButtonCountDiffersFromCommandTableSize) );
    
    for ( TInt i = 0; i < count; i++ )
        {       
        TInt priorities( reader.ReadInt16() ); // Amount of priorities for current button.
        RArray<TInt> arr;
        for ( TInt ii = 0; ii < priorities; ii++ )
            {
            TInt8 commandType( reader.ReadInt8() );
            arr.Append( commandType );
            }
        iPriorities.Append( arr );
        }
    
    CleanupStack::PopAndDestroy(); // reader
#endif    
    }
    
#ifdef RD_ENHANCED_CBA
CEikCommandTable::CEikCommandTable() : iPriorities(1)
#else    
CEikCommandTable::CEikCommandTable()
#endif // RD_ENHANCED_CBA
    {
    }

    
CEikCommandTable::~CEikCommandTable()
    {
#ifdef RD_ENHANCED_CBA    
    iCommandButtons.Reset(); // Reset array
    for(TInt i = 0; i < iPriorities.Count(); i++)
        {
        iPriorities[i].Reset();
        }
    iPriorities.Reset();
#endif    
    }
    
// -----------------------------------------------------------------------------
// Used to add a command to CommandTable
// @param aButton button to be added
// -----------------------------------------------------------------------------
#ifndef RD_ENHANCED_CBA    
TInt CEikCommandTable::AddCommandL(CEikEnhancedCbaButton* /*aButton*/) 
    {
    return KErrNone;
    }
#else     
TInt CEikCommandTable::AddCommandL(CEikEnhancedCbaButton* aButton) 
    {
    // CommandType tells in which button this command should be placed
    TInt commandType( aButton->CommandType() );
    TInt index( KErrNotFound );
    
    // Find button and index for this button.
    TInt button( 0 );
    for ( button = 0; button < iPriorities.Count(); button++ )
        {
        index = iPriorities[button].Find( commandType );
        if ( index != KErrNotFound )
            {
            CEikEnhancedCbaButton* existingButton = Command( button );
            // If command placed on this index, check if new priority is lower.
            if( existingButton )
                {   
                TInt existingPriority = iPriorities[button].Find( existingButton->CommandType() );          
                
                // Delete existing command button if new command has higher priority (lower index).
                if(  index < existingPriority || existingPriority == KErrNotFound )
                    {
                    delete existingButton;
                    existingButton = NULL;
                    iCommandButtons[button] = aButton;
                    break;
                    }               
                }
            else
                {
                iCommandButtons[button] = aButton;
                break;
                }
            }           
        }
        
    // Delete button if it's not placed.
    if( button == iPriorities.Count() )
        {
        delete aButton;
        aButton = NULL;
        }       
    return KErrNone;
    }
#endif // RD_ENHANCED_CBA    
    
// -----------------------------------------------------------------------------
// Used to check if CommandTable has a button with a certain id.
// @param aCommandId Id to be checked.
// -----------------------------------------------------------------------------
#ifndef RD_ENHANCED_CBA
TBool CEikCommandTable::IsCommandPlaced(const TInt /*aCommandId*/) const
    {
#else // !RD_ENHANCED_CBA  
TBool CEikCommandTable::IsCommandPlaced(const TInt aCommandId) const
    {
    TInt count( iCommandButtons.Count() );
    
    for ( TInt i = 0; i < count; i++ )
        {
        if ( iCommandButtons[i] )
            {
            if ( iCommandButtons[i]->CommandId() == aCommandId )
                {
                return ETrue;
                }              
            }
        }
#endif // RD_ENHANCED_CBA
    return EFalse; // if no match for command id
    }
    
// -----------------------------------------------------------------------------
// Used to replace command with a new command.
// @param aCommandId Id for command that should be replaced.
// @param aResourceId Id for new ENHANCED_CBA_BUTTON resource to be placed in the CommandTable.
// -----------------------------------------------------------------------------
#ifndef RD_ENHANCED_CBA    
void CEikCommandTable::ReplaceCommandL( const TInt /*aCommandId*/, const TInt /*aResourceId*/ )
    {
#else // !RD_ENHANCED_CBA    
void CEikCommandTable::ReplaceCommandL( const TInt aCommandId, const TInt aResourceId )
    {
    // If the command is not in the command table, return.
    if( !IsCommandPlaced( aCommandId ) )
        {
        return;
        }   
    
    TInt index( iCommandButtons.Count() );
    
    CEikEnhancedCbaButton* oldButton = NULL;
    
    for( TInt i = 0; i < index; i++ )
        {
        if( iCommandButtons[i] )
            {
            if( iCommandButtons[i]->CommandId() == aCommandId )
                {
                oldButton = iCommandButtons[i];
                index = i;
                break; // Index is the index of replacement.
                }           
            }           
        }
    
    CEikEnhancedCbaButton* button = new (ELeave) CEikEnhancedCbaButton;
    button->SetTextBitmapMode( iExtension->iEnablePostingTransparency );
    CleanupStack::PushL( button );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, aResourceId );
    
    // Construct new button.
    TUint8 version( (TUint8)reader.ReadUint8() ); // version 
    button->ConstructFromResourceL( reader );   
    CleanupStack::Pop( button );
    CleanupStack::PopAndDestroy(); // reader
    
    // Store new button to command table.
    iCommandButtons[index] = button; // transfers ownership
    
    // Delete old button.
    delete oldButton;
#endif // !RD_ENHANCED_CBA    
    }
    
// -----------------------------------------------------------------------------
// Used to get CEikEnhancedCbaButton for current control button (1-4).
// @param aCommandIndex Index for requested button, use enum TCommandTableCbaPositions.
// @return CEikCbaButton for current position, NULL if no button placed in that position.
// -----------------------------------------------------------------------------
#ifdef RD_ENHANCED_CBA
CEikEnhancedCbaButton* CEikCommandTable::Command( const TInt aCommandIndex )
    {
    return iCommandButtons[aCommandIndex]; 
    }
#else // RD_ENHANCED_CBA
CEikEnhancedCbaButton* CEikCommandTable::Command( const TInt /*aCommandIndex*/ )
    {
    return NULL;
    }
#endif // RD_ENHANCED_CBA

// -----------------------------------------------------------------------------
// Reset CommandTable
// -----------------------------------------------------------------------------    
void CEikCommandTable::Reset()
    {
#ifdef RD_ENHANCED_CBA 
    iCommandButtons.Reset();
#endif // RD_ENHANCED_CBA
    }

// -----------------------------------------------------------------------------
// Sets command observer
// -----------------------------------------------------------------------------
EXPORT_C void AknCbaContentObserver::SetContentObserver( 
        CEikCba* aCba, 
        TCallBack aCallBack )
    {
    if ( aCba )
        {
        aCba->SetContentObserver( aCallBack );
        }
    }

// End of file
