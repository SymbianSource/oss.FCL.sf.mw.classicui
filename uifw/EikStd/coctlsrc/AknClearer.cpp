/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Screen clearer.
*
*/


#include <eikappui.h>
#include <eikspane.h>
#include "aknclearer.h"
#include <aknconsts.h>
#include <aknnavi.h>
#include <avkon.mbg>
#include <AknLayout.lag>
#include <AknSgcc.h>
#include <AknUtils.h>
#include <AknsUtils.h>
#include <aknenv.h>
#include <AknsUtils.h>
#include <AknIconUtils.h>
#include <AknsLayeredBackgroundControlContext.h>
#include <aknappui.h>
#include <AknsDrawUtils.h>
#include <mifconvdefs.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <layoutmetadata.cdl.h>
#include <AknStatuspaneUtils.h>

#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikenvinterface.h> 
#endif

#define KWholeScreen (AknLayout::screen().Rect())

#ifdef RD_UI_TRANSITION_EFFECTS_LAYOUT_SWITCH
#include <akntranseffect.h>
#include <akntransitionutils.h>
#endif

enum TAknScreenClearerBaseFlags
	{
	EAknScreenClearerDrawNavi,
	EAknScreenClearerBlankAppStatusPane,
	EAknScreenClearerDrawNaviSolid,
	};

enum 
    {
    ELayerCbaBackground=0,
    ELayerBackground = 1,
    ELayerExtension = 2,
    ELayerStripe = 3,
    ELayerWallpaper = 4,
    ELayerN = 5
    };

    enum 
        {
        ELayerStaconCbaBackground=0,
        ELayerStaconTop = 1,
        ELayerStaconBottom = 2,
        ELayerStaconMain = 3,
        ELayerStaconWallpaper = 4,
        ELayerStaconN = 5
        };

enum 
    {
    ELayerFlatCbaBackground=0,
    ELayerFlatBackground = 1,
    ELayerFlatTl = 2,
    ELayerFlatTr = 3,
    ELayerFlatBl = 4,
    ELayerFlatBr = 5,
    ELayerFlatT = 6,
    ELayerFlatB = 7,
    ELayerFlatR = 8,
    ELayerFlatL = 9,
    ELayerFlatCenter = 10,
    ELayerFlatMain = 11,
    ELayerFlatWallpaper = 12,
    ELayerSCtrl1 = 13,
    ELayerSCtrl2 = 14,
    ELayerSCtrl3 = 15,
    ELayerSCtrl4 = 16,
    ELayerSCtrl5 = 17,
    ELayerFlatN = 18
    };


class CAknScreenClearerBaseExtension : public CBase
    {
    public:
        ~CAknScreenClearerBaseExtension()
            {
            delete iNaviWipe;
            delete iNaviMask;
            delete iBgContext;
            }
    public:
	    CFbsBitmap* iNaviWipe;
        CFbsBitmap* iNaviMask;
        CAknsLayeredBackgroundControlContext* iBgContext;
        TInt iOrdinalPosition;
    };

/* THIS FUNCTION IS NOT USED

static void LoadAndFlipBitmapL( 
    CFbsBitmap* aTrg, const TDesC& aFile, const TInt aIndex )
    {
    User::LeaveIfNull(aTrg);

    CFbsBitmap* sourceBitmap = new (ELeave) CFbsBitmap();   
    CleanupStack::PushL(sourceBitmap);
    User::LeaveIfError(sourceBitmap->Load(aFile, aIndex, ETrue));    
    TSize sourceBitmapSize = sourceBitmap->SizeInPixels();

    User::LeaveIfError(aTrg->Create(sourceBitmapSize, sourceBitmap->DisplayMode()));

    CFbsBitmapDevice* destinationDevice = CFbsBitmapDevice::NewL( aTrg );
    CleanupStack::PushL(destinationDevice);

    CFbsBitGc* destinationGc;
    User::LeaveIfError( destinationDevice->CreateContext( destinationGc ) );

    TRect sourceBitmapBlittingRect( 0,0,1,sourceBitmapSize.iHeight );  

    for ( TInt xPos=sourceBitmapSize.iWidth-1; xPos >= 0; xPos-- )
        {
        destinationGc->BitBlt( TPoint(xPos,0), sourceBitmap, sourceBitmapBlittingRect );
        sourceBitmapBlittingRect.iTl.iX++;
        sourceBitmapBlittingRect.iBr.iX++;
        }

    delete destinationGc;  
    CleanupStack::PopAndDestroy(2); // sourceBitmap, destinationDevice
    }
*/

/* THIS FUNCTION IS NOT USED

static CFbsBitmap* FlipBitmapL( CFbsBitmap* aBitmap )
    {
    User::LeaveIfNull(aBitmap);   

    TSize sourceBitmapSize = aBitmap->SizeInPixels();

    // get a copy of wanted rect of source bitmap to tmpBitmap
    CFbsBitmap* tmpBitmap = new (ELeave) CFbsBitmap();   
    CleanupStack::PushL( tmpBitmap );                      

    User::LeaveIfError( tmpBitmap->Create( sourceBitmapSize, aBitmap->DisplayMode() ) );

    CFbsBitmapDevice* destinationDevice = CFbsBitmapDevice::NewL( tmpBitmap );
    CleanupStack::PushL( destinationDevice );
    
    CFbsBitGc* destinationGc;
    User::LeaveIfError( destinationDevice->CreateContext( destinationGc ) );           
    
    TRect sourceBitmapBlittingRect( 0,0,1,sourceBitmapSize.iHeight );  
    
    for ( TInt xPos=sourceBitmapSize.iWidth-1; xPos >= 0; xPos-- )
        {
        destinationGc->BitBlt( TPoint(xPos,0), aBitmap, sourceBitmapBlittingRect );
        sourceBitmapBlittingRect.iTl.iX++;
        sourceBitmapBlittingRect.iBr.iX++;
        }
    
    delete destinationGc;  
    CleanupStack::PopAndDestroy(); // destinationDevice
    CleanupStack::Pop(); // tmpBitmap
  
    return tmpBitmap;
    }
*/

EXPORT_C CAknScreenClearerBase::~CAknScreenClearerBase()
	{
    delete iExtension;
	}

EXPORT_C void CAknScreenClearerBase::ConstructL(RWindowGroup& aParent, TInt aOrdinalPos, TBool aBlankAppStatusPane)
	{
    iExtension = new (ELeave) CAknScreenClearerBaseExtension();

	CreateWindowL(&aParent);

	iFlags.Assign(EAknScreenClearerBlankAppStatusPane, aBlankAppStatusPane);

	SetShapeL();

	DrawableWindow()->SetOrdinalPosition(aOrdinalPos);
	iExtension->iOrdinalPosition = aOrdinalPos;

	ActivateL();

    // Setup skin background context
    iExtension->iBgContext = CAknsLayeredBackgroundControlContext::NewL(
        KAknsIIDQsnBgAreaStatus, TRect(0,0,1,1), ETrue, ELayerFlatN + 1);

    for (TInt n=0; n<ELayerFlatN; n++)
        {
        iExtension->iBgContext->SetLayerImage( n, KAknsIIDNone );                
        }            

	SetSkinShapeL();

	DrawNow();
	}



EXPORT_C void CAknScreenClearerBase::Draw(const TRect& /*aRect*/) const
	{
	CWindowGc& gc = SystemGc();
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    AknsDrawUtils::Background( skin, iExtension->iBgContext, this, gc, Rect() );

	if (Layout_Meta_Data::IsPenEnabled() && Layout_Meta_Data::IsLandscapeOrientation())
		{
#if 0
	    TRect application_window( KWholeScreen );
		TAknLayoutRect area_side_right_pane;
		TInt variety = 0;
		area_side_right_pane.LayoutRect(application_window, AknLayoutScalable_Avkon::area_side_right_pane(variety));

		CFbsBitmap *mask1 = AknsUtils::GetCachedBitmap( skin, KAknsIIDQgnIndiSctrlSkMaskLsc );
		CFbsBitmap *mask5 = AknsUtils::GetCachedBitmap( skin, KAknsIIDQgnIndiSctrlSkMaskLsc );

		CFbsBitmap *bitmap = new(ELeave)CFbsBitmap;
		CleanupStack::PushL(bitmap);
		bitmap->Create(area_side_right_pane.Rect().Size(), EColor16MA);
        CFbsBitGc* bitmapContext = NULL;
        CFbsBitmapDevice* bitmapDevice =
            CFbsBitmapDevice::NewL( bitmap );
        CleanupStack::PushL( bitmapDevice );
        bitmapDevice->CreateContext( bitmapContext );
        CleanupStack::PushL( bitmapContext );

        TRect area_side_right_pane_rect = area_side_right_pane.Rect();
        area_side_right_pane_rect.iTl = TPoint(0,0);
        
		TAknLayoutRect sctrl_sk_top_pane;
		sctrl_sk_top_pane.LayoutRect(area_side_right_pane_rect, AknLayoutScalable_Avkon::sctrl_sk_top_pane(0));
	
		TAknLayoutRect sctrl_sk_bottom_pane;
		sctrl_sk_bottom_pane.LayoutRect(area_side_right_pane_rect, AknLayoutScalable_Avkon::sctrl_sk_bottom_pane(0));
	
		TAknLayoutRect grid_sctrl_middle_pane;
		grid_sctrl_middle_pane.LayoutRect(area_side_right_pane_rect, AknLayoutScalable_Avkon::grid_sctrl_middle_pane(0));
	
		TAknLayoutRect cell_sctrl_middle_pane1;
		cell_sctrl_middle_pane1.LayoutRect(grid_sctrl_middle_pane.Rect(), AknLayoutScalable_Avkon::cell_sctrl_middle_pane(0,0,0));
		TAknLayoutRect cell_sctrl_middle_pane2;
		cell_sctrl_middle_pane2.LayoutRect(grid_sctrl_middle_pane.Rect(), AknLayoutScalable_Avkon::cell_sctrl_middle_pane(0,0,1));
		TAknLayoutRect cell_sctrl_middle_pane3;
		cell_sctrl_middle_pane3.LayoutRect(grid_sctrl_middle_pane.Rect(), AknLayoutScalable_Avkon::cell_sctrl_middle_pane(0,0,2));
	
		AknsDrawUtils::DrawFrame( skin, *bitmapContext, sctrl_sk_top_pane.Rect(), Convert(sctrl_sk_top_pane.Rect()), KAknsIIDQgnFrSctrlSkButton, KAknsIIDQgnFrSctrlSkButtonCenter);
		AknsDrawUtils::DrawFrame( skin, *bitmapContext, cell_sctrl_middle_pane1.Rect(), Convert2(cell_sctrl_middle_pane1.Rect()), KAknsIIDQgnFrSctrlButton, KAknsIIDQgnFrSctrlButtonCenter);
		AknsDrawUtils::DrawFrame( skin, *bitmapContext, cell_sctrl_middle_pane2.Rect(), Convert2(cell_sctrl_middle_pane2.Rect()), KAknsIIDQgnFrSctrlButton, KAknsIIDQgnFrSctrlButtonCenter);
		AknsDrawUtils::DrawFrame( skin, *bitmapContext, cell_sctrl_middle_pane3.Rect(), Convert2(cell_sctrl_middle_pane3.Rect()), KAknsIIDQgnFrSctrlButton, KAknsIIDQgnFrSctrlButtonCenter);
		AknsDrawUtils::DrawFrame( skin, *bitmapContext, sctrl_sk_bottom_pane.Rect(), Convert(sctrl_sk_bottom_pane.Rect()), KAknsIIDQgnFrSctrlSkButton, KAknsIIDQgnFrSctrlSkButtonCenter);

		TSize size1 = sctrl_sk_top_pane.Rect().Size();
		TSize size5 = sctrl_sk_bottom_pane.Rect().Size();
        AknIconUtils::SetSize(mask1, size1, EAspectRatioNotPreserved);
        AknIconUtils::SetSize(mask5, size5, EAspectRatioNotPreserved);

		gc.BitBltMasked( area_side_right_pane.Rect().iTl+sctrl_sk_top_pane.Rect().iTl, bitmap, sctrl_sk_top_pane.Rect(), mask1, EFalse);
        gc.BitBltMasked( area_side_right_pane.Rect().iTl+sctrl_sk_bottom_pane.Rect().iTl, bitmap, sctrl_sk_bottom_pane.Rect(), mask5, EFalse);
		
        CleanupStack::PopAndDestroy(3); // bitmap, bitmapdevice, bitmapcontext
#endif
		}


    iEikonEnv->WsSession().Flush();
    return;
	}
	
EXPORT_C void CAknScreenClearerBase::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknControl::HandlePointerEventL(aPointerEvent); 
    }	

EXPORT_C void* CAknScreenClearerBase::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CAknScreenClearerBase::HandleStatusPaneSizeChangeL()
	{
	SetShapeL();
	SetSkinShapeL();
	DrawableWindow()->SetOrdinalPosition(iExtension->iOrdinalPosition);
	DrawNow();
	}

void CAknScreenClearerBase::SetShapeL()
	{
	RRegion shape;
	CleanupClosePushL(shape);
    RRegion appStatuspaneShape;
	CleanupClosePushL(appStatuspaneShape);

	CEikStatusPaneBase* sp = CEikStatusPaneBase::Current();
    
    if (iFlags[EAknScreenClearerBlankAppStatusPane])
        {
        shape.AddRect(KWholeScreen);
        }
    else
        {
        shape.AddRect(KWholeScreen);
		sp->GetShapeL(appStatuspaneShape, !iFlags[EAknScreenClearerBlankAppStatusPane], ETrue);
        shape.SubRegion(appStatuspaneShape);
        }

	if (shape.CheckError())
		User::Leave(KErrNoMemory);

	SetRect(KWholeScreen);
	DrawableWindow()->SetShape(shape);

	CleanupStack::PopAndDestroy(2);		// close shapes	

	TBool drawNavi =
		iFlags[EAknScreenClearerBlankAppStatusPane] && 
		sp->IsVisible() && 
		sp->PaneCapabilities(TUid::Uid(EEikStatusPaneUidNavi)).IsInCurrentLayout();

	iFlags.Assign(EAknScreenClearerDrawNavi, drawNavi);
	}



void CAknScreenClearerBase::SetSkinShapeL()
	{	
    for (TInt n=0; n<ELayerFlatN; n++)
        {
        iExtension->iBgContext->SetLayerImage( n, KAknsIIDNone );                
        }            

    TBool widescreenPaneUsed(
        R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL ==
            AVKONENV->StatusPaneResIdForCurrentLayout(
                R_AVKON_STATUS_PANE_LAYOUT_USUAL ) ||
        R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE ==
            AVKONENV->StatusPaneResIdForCurrentLayout(
                R_AVKON_STATUS_PANE_LAYOUT_IDLE ) );
    
    // Check that if in landscape mode statuspane is changed to stacon pane
    TBool staconPaneUsedInLandscape = 
        ( ( R_AVKON_STATUS_PANE_LAYOUT_USUAL !=
                AVKONENV->StatusPaneResIdForCurrentLayout(
                    R_AVKON_STATUS_PANE_LAYOUT_USUAL ) ) &&
          ( R_AVKON_STATUS_PANE_LAYOUT_USUAL_MIRRORED !=
                AVKONENV->StatusPaneResIdForCurrentLayout(
                    R_AVKON_STATUS_PANE_LAYOUT_USUAL ) ) );

    TBool flatStatuspaneusedInLandscape =
        ( R_AVKON_STATUS_PANE_LAYOUT_USUAL_FLAT ==
            AVKONENV->StatusPaneResIdForCurrentLayout(
                R_AVKON_STATUS_PANE_LAYOUT_USUAL ) );
    

    // TRect application_window = iAvkonAppUi->ApplicationRect();
    // This is sometimes needed before iAvkonAppUi->ApplicationRect() is updated
    TRect application_window( KWholeScreen );
    if ( application_window.Width() > application_window.Height() )
        {
        if ( widescreenPaneUsed )
            {
            // Main pane area
            TAknLayoutRect mainPane;
            mainPane.LayoutRect(
                application_window,
                AknLayoutScalable_Avkon::main_pane( 4 ).LayoutLine() );
                
            iExtension->iBgContext->SetLayerImage( ELayerWallpaper,
                                                   KAknsIIDQsnBgAreaMain );
	        iExtension->iBgContext->SetLayerRect( ELayerWallpaper,
	                                              mainPane.Rect() );
            
            // Status pane area
            TAknLayoutRect layoutRect;
            layoutRect.LayoutRect(
                application_window,
                AknLayoutScalable_Avkon::area_top_pane( 8 ).LayoutLine() );
            
            iExtension->iBgContext->SetLayerImage( ELayerBackground,
                                                   KAknsIIDQsnBgAreaStatus );
            iExtension->iBgContext->SetLayerRect( ELayerBackground, layoutRect.Rect() );
            }
        else if ( flatStatuspaneusedInLandscape )
            {
            TInt topVariety = 2;
            TInt spVariety = 2;
            TInt bgVariety = 1;

            TAknLayoutRect control_pane;
            control_pane.LayoutRect(application_window, AKN_LAYOUT_WINDOW_control_pane(application_window));
                        
            TAknWindowLineLayout topLayout = AknLayoutScalable_Avkon::area_top_pane(topVariety).LayoutLine();
                
            TAknLayoutRect layoutRect;
            layoutRect.LayoutRect( application_window, topLayout );
            TRect topLayoutRect = layoutRect.Rect();

            TAknWindowLineLayout statuspaneLayout = AknLayoutScalable_Avkon::status_pane(spVariety).LayoutLine();
            layoutRect.LayoutRect( topLayoutRect, statuspaneLayout );
            TRect spRect = layoutRect.Rect();

            TAknWindowLineLayout bgLayout = AknLayoutScalable_Avkon::bg_status_flat_pane(bgVariety).LayoutLine();
            layoutRect.LayoutRect( spRect, bgLayout );
            TRect bgRect = layoutRect.Rect();                            

            TAknLayoutRect extension;
            extension.LayoutRect( application_window,
                AKN_LAYOUT_WINDOW_main_pane(application_window, 0, 1, 1) );                

            iExtension->iBgContext->SetLayerImage( ELayerFlatMain, KAknsIIDQsnBgAreaMain );
            iExtension->iBgContext->SetLayerRect( ELayerFlatMain, extension.Rect() );
            
            // Wallpaper
            iExtension->iBgContext->SetLayerImage( ELayerFlatWallpaper, KAknsIIDNone );
            iExtension->iBgContext->SetLayerRect( ELayerFlatWallpaper, extension.Rect() );

			// Transparency support
            iExtension->iBgContext->SetLayerImage( ELayerFlatBackground, KAknsIIDQsnBgScreen ); 
            iExtension->iBgContext->SetLayerRect( ELayerFlatBackground, application_window );               

            MAknsSkinInstance* si = AknsUtils::SkinInstance();
	  
    		CAknsItemData* idata = NULL;
            
            if ( si )
                {
    		    TRAP_IGNORE(idata = si->CreateUncachedItemDataL( KAknsIIDQsnFrStatusFlat, EAknsITImageTable ););
                }
    				
    		if (idata)
    		    {
                TAknWindowLineLayout layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g2().LayoutLine();
                layoutRect.LayoutRect( bgRect, layout );
                iExtension->iBgContext->SetLayerImage( ELayerFlatTl, KAknsIIDQsnFrStatusFlatCornerTl ); 
                iExtension->iBgContext->SetLayerRect( ELayerFlatTl, layoutRect.Rect() );
            
                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g3().LayoutLine();
                layoutRect.LayoutRect( bgRect, layout );
                iExtension->iBgContext->SetLayerImage( ELayerFlatTr, KAknsIIDQsnFrStatusFlatCornerTr ); 
                iExtension->iBgContext->SetLayerRect( ELayerFlatTr, layoutRect.Rect());
            
                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g4().LayoutLine();
                layoutRect.LayoutRect( bgRect, layout );            
                iExtension->iBgContext->SetLayerImage( ELayerFlatBl, KAknsIIDQsnFrStatusFlatCornerBl ); 
                iExtension->iBgContext->SetLayerRect( ELayerFlatBl, layoutRect.Rect() );
            
                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g5().LayoutLine();
                layoutRect.LayoutRect( bgRect, layout );            
                iExtension->iBgContext->SetLayerImage( ELayerFlatBr, KAknsIIDQsnFrStatusFlatCornerBr );
                iExtension->iBgContext->SetLayerRect( ELayerFlatBr, layoutRect.Rect() );
            
                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g6().LayoutLine();
                layoutRect.LayoutRect( bgRect, layout );            
                iExtension->iBgContext->SetLayerImage( ELayerFlatT,  KAknsIIDQsnFrStatusFlatSideT); 
                iExtension->iBgContext->SetLayerRect( ELayerFlatT, layoutRect.Rect() );

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g7().LayoutLine();
                layoutRect.LayoutRect( bgRect, layout );            
                iExtension->iBgContext->SetLayerImage( ELayerFlatB, KAknsIIDQsnFrStatusFlatSideB ); 
                iExtension->iBgContext->SetLayerRect( ELayerFlatB, layoutRect.Rect() );

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g9().LayoutLine();
                layoutRect.LayoutRect( bgRect, layout );            
                iExtension->iBgContext->SetLayerImage( ELayerFlatR, KAknsIIDQsnFrStatusFlatSideR ); 
                iExtension->iBgContext->SetLayerRect( ELayerFlatR, layoutRect.Rect() );

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g8().LayoutLine();
                layoutRect.LayoutRect( bgRect, layout );            
                iExtension->iBgContext->SetLayerImage( ELayerFlatL, KAknsIIDQsnFrStatusFlatSideL ); 
                iExtension->iBgContext->SetLayerRect( ELayerFlatL, layoutRect.Rect() );

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g1().LayoutLine();
                layoutRect.LayoutRect( bgRect, layout );            
                iExtension->iBgContext->SetLayerImage( ELayerFlatCenter, KAknsIIDQsnFrStatusFlatCenter ); 
                iExtension->iBgContext->SetLayerRect( ELayerFlatCenter, layoutRect.Rect() );
                }
            else
                {
            	iExtension->iBgContext->SetLayerImage( 0, KAknsIIDQsnFrStatusFlat);
                iExtension->iBgContext->SetLayerRect(0, bgRect);
                }
                
            delete idata;
            iExtension->iBgContext->SetLayerImage( ELayerFlatN, KAknsIIDQsnBgAreaControl );
            iExtension->iBgContext->SetLayerRect( ELayerFlatN, control_pane.Rect() );

            }
        else
            {
            // Landscape with staconpane
            TRect staconTop = TRect(0,0,0,0);
            TRect staconBottom = TRect(0,0,0,0);
            TAknLayoutRect main_pane;
            main_pane.LayoutRect(application_window, AKN_LAYOUT_WINDOW_main_pane(application_window, 0,1,0));

            TAknWindowLineLayout staconTopParent = AknLayoutScalable_Avkon::area_top_pane(2).LayoutLine();
            TAknWindowLineLayout staconBottomParent = AknLayoutScalable_Avkon::area_bottom_pane(2).LayoutLine();

            TAknLayoutRect layoutRect;
            layoutRect.LayoutRect( application_window, staconTopParent );
            TRect staconTopParentRect = layoutRect.Rect();

            layoutRect.LayoutRect( application_window, staconBottomParent );
            TRect staconBottomParentRect = layoutRect.Rect();
                
                
            TAknWindowLineLayout layout = AknLayoutScalable_Avkon::stacon_top_pane().LayoutLine();
            layoutRect.LayoutRect( staconTopParentRect, layout );
            staconTop    = layoutRect.Rect();
                
            layout = AknLayoutScalable_Avkon::stacon_bottom_pane().LayoutLine();
            layoutRect.LayoutRect( staconBottomParentRect, layout );        
            staconBottom = layoutRect.Rect();

            TBool staconPaneRight = EFalse;
            CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
            if (statusPane)
                {
                TInt currentStatusPaneLayoutResId = AVKONENV->StatusPaneResIdForCurrentLayout(statusPane->CurrentLayoutResId());

                staconPaneRight = ((currentStatusPaneLayoutResId == R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_RIGHT) ||
                                   (currentStatusPaneLayoutResId == R_AVKON_STACON_PANE_LAYOUT_EMPTY_SOFTKEYS_RIGHT) ||
                                   (currentStatusPaneLayoutResId == R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_RIGHT));

                }

            iExtension->iBgContext->SetLayerImage( 0, KAknsIIDQsnBgAreaMain );
            if (staconPaneRight)
                {
                iExtension->iBgContext->SetLayerImage( 1, KAknsIIDQsnBgAreaStaconRt );
                iExtension->iBgContext->SetLayerImage( 2, KAknsIIDQsnBgAreaStaconRb );
                }
            else
                {
                iExtension->iBgContext->SetLayerImage( 1, KAknsIIDQsnBgAreaStaconLt );
                iExtension->iBgContext->SetLayerImage( 2, KAknsIIDQsnBgAreaStaconLb );
                }
            iExtension->iBgContext->SetLayerImage( 3, KAknsIIDNone );
            iExtension->iBgContext->SetLayerImage( 4, KAknsIIDNone );
                        
            iExtension->iBgContext->SetLayerRect( 0, main_pane.Rect() );
            iExtension->iBgContext->SetLayerRect( 1, staconTop );
            iExtension->iBgContext->SetLayerRect( 2, staconBottom );
            }                        

	if (Layout_Meta_Data::IsPenEnabled())
		{
		TAknLayoutRect area_side_right_pane;
		TInt variety = 0;
		area_side_right_pane.LayoutRect(application_window, AknLayoutScalable_Avkon::area_side_right_pane(variety));

		TAknLayoutRect sctrl_sk_top_pane;
		sctrl_sk_top_pane.LayoutRect(area_side_right_pane.Rect(), AknLayoutScalable_Avkon::sctrl_sk_top_pane(0));
	
		TAknLayoutRect sctrl_sk_bottom_pane;
		sctrl_sk_bottom_pane.LayoutRect(area_side_right_pane.Rect(), AknLayoutScalable_Avkon::sctrl_sk_bottom_pane(0));
	
		TAknLayoutRect grid_sctrl_middle_pane;
		grid_sctrl_middle_pane.LayoutRect(area_side_right_pane.Rect(), AknLayoutScalable_Avkon::grid_sctrl_middle_pane(0));
	
		TAknLayoutRect cell_sctrl_middle_pane1;
		cell_sctrl_middle_pane1.LayoutRect(grid_sctrl_middle_pane.Rect(), AknLayoutScalable_Avkon::cell_sctrl_middle_pane(0,0,0));
		TAknLayoutRect cell_sctrl_middle_pane2;
		cell_sctrl_middle_pane2.LayoutRect(grid_sctrl_middle_pane.Rect(), AknLayoutScalable_Avkon::cell_sctrl_middle_pane(0,0,1));
		TAknLayoutRect cell_sctrl_middle_pane3;
		cell_sctrl_middle_pane3.LayoutRect(grid_sctrl_middle_pane.Rect(), AknLayoutScalable_Avkon::cell_sctrl_middle_pane(0,0,2));
	


		iExtension->iBgContext->SetLayerImage( ELayerFlatCbaBackground, KAknsIIDQsnBgScreen );


		iExtension->iBgContext->SetLayerRect( ELayerFlatCbaBackground, application_window );
		}




        }
    else
        {
        // Default is portrait 
        TInt spRes = CEikStatusPaneBase::Current()->CurrentLayoutResId();
        if (spRes == R_AVKON_STATUS_PANE_LAYOUT_USUAL_FLAT)
        	{
	        TAknLayoutRect status_pane_thin;
	        status_pane_thin.LayoutRect( application_window, 
	            AknLayoutScalable_Avkon::area_top_pane(6).LayoutLine() );
	        TAknLayoutRect main_pane;
	        main_pane.LayoutRect(application_window, AknLayoutScalable_Avkon::main_pane(7).LayoutLine());
	        TAknLayoutRect control_pane;
	        control_pane.LayoutRect(application_window, AKN_LAYOUT_WINDOW_control_pane(application_window));
	  
	        // Statuspane area
    		CAknsItemData* idata = NULL;            
            MAknsSkinInstance* si = AknsUtils::SkinInstance();
            TAknLayoutRect layoutRect;
            if (si)    				
    		    TRAP_IGNORE(idata = si->CreateUncachedItemDataL( KAknsIIDQsnFrStatusFlat, EAknsITImageTable ););
    				
    		if (idata)
    		    {
                TAknWindowLineLayout layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g2().LayoutLine();
                layoutRect.LayoutRect( status_pane_thin.Rect(), layout );
                iExtension->iBgContext->SetLayerImage( ELayerFlatTl, KAknsIIDQsnFrStatusFlatCornerTl ); 
                iExtension->iBgContext->SetLayerRect( ELayerFlatTl, layoutRect.Rect() );
            
                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g3().LayoutLine();
                layoutRect.LayoutRect( status_pane_thin.Rect(), layout );
                iExtension->iBgContext->SetLayerImage( ELayerFlatTr, KAknsIIDQsnFrStatusFlatCornerTr ); 
                iExtension->iBgContext->SetLayerRect( ELayerFlatTr, layoutRect.Rect());
            
                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g4().LayoutLine();
                layoutRect.LayoutRect( status_pane_thin.Rect(), layout );            
                iExtension->iBgContext->SetLayerImage( ELayerFlatBl, KAknsIIDQsnFrStatusFlatCornerBl ); 
                iExtension->iBgContext->SetLayerRect( ELayerFlatBl, layoutRect.Rect() );
            
                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g5().LayoutLine();
                layoutRect.LayoutRect( status_pane_thin.Rect(), layout );            
                iExtension->iBgContext->SetLayerImage( ELayerFlatBr, KAknsIIDQsnFrStatusFlatCornerBr );
                iExtension->iBgContext->SetLayerRect( ELayerFlatBr, layoutRect.Rect() );
            
                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g6().LayoutLine();
                layoutRect.LayoutRect( status_pane_thin.Rect(), layout );            
                iExtension->iBgContext->SetLayerImage( ELayerFlatT,  KAknsIIDQsnFrStatusFlatSideT); 
                iExtension->iBgContext->SetLayerRect( ELayerFlatT, layoutRect.Rect() );

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g7().LayoutLine();
                layoutRect.LayoutRect( status_pane_thin.Rect(), layout );            
                iExtension->iBgContext->SetLayerImage( ELayerFlatB, KAknsIIDQsnFrStatusFlatSideB ); 
                iExtension->iBgContext->SetLayerRect( ELayerFlatB, layoutRect.Rect() );

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g9().LayoutLine();
                layoutRect.LayoutRect( status_pane_thin.Rect(), layout );            
                iExtension->iBgContext->SetLayerImage( ELayerFlatR, KAknsIIDQsnFrStatusFlatSideR ); 
                iExtension->iBgContext->SetLayerRect( ELayerFlatR, layoutRect.Rect() );

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g8().LayoutLine();
                layoutRect.LayoutRect( status_pane_thin.Rect(), layout );            
                iExtension->iBgContext->SetLayerImage( ELayerFlatL, KAknsIIDQsnFrStatusFlatSideL ); 
                iExtension->iBgContext->SetLayerRect( ELayerFlatL, layoutRect.Rect() );

                layout = AknLayoutScalable_Avkon::bg_status_flat_pane_g1().LayoutLine();
                layoutRect.LayoutRect( status_pane_thin.Rect(), layout );            
                iExtension->iBgContext->SetLayerImage( ELayerFlatCenter, KAknsIIDQsnFrStatusFlatCenter ); 
                iExtension->iBgContext->SetLayerRect( ELayerFlatCenter, layoutRect.Rect() );
                }
            else
                {
            	iExtension->iBgContext->SetLayerImage( 0, KAknsIIDQsnFrStatusFlat);
                iExtension->iBgContext->SetLayerRect(0, status_pane_thin.Rect());
                }                
            delete idata;
      
			// Transparency support
            iExtension->iBgContext->SetLayerImage( ELayerFlatBackground, KAknsIIDQsnBgScreen ); 
            iExtension->iBgContext->SetLayerRect( ELayerFlatBackground, application_window );               
                
	        // main pane
            iExtension->iBgContext->SetLayerImage( ELayerFlatMain, KAknsIIDQsnBgAreaMain );                
	        iExtension->iBgContext->SetLayerRect( ELayerFlatMain, main_pane.Rect() );

	        // control pane
	        iExtension->iBgContext->SetLayerImage( ELayerFlatN, KAknsIIDQsnBgAreaControl );
	        iExtension->iBgContext->SetLayerRect( ELayerFlatN, control_pane.Rect() );
        	}
        else
	        {
	        TAknLayoutRect topArea;
	        topArea.LayoutRect( application_window,
	            AknLayoutScalable_Avkon::area_top_pane(0).LayoutLine() );
	        
	        TAknLayoutRect status_pane_usual;
	        status_pane_usual.LayoutRect( topArea.Rect(), 
	            AknLayoutScalable_Avkon::status_pane(0).LayoutLine() );
	            
	        TAknLayoutRect main_pane;
	        main_pane.LayoutRect(application_window, AKN_LAYOUT_WINDOW_main_pane(application_window, 0,1,1));
	        TAknLayoutRect control_pane;
	        control_pane.LayoutRect(application_window, AKN_LAYOUT_WINDOW_control_pane(application_window));
	  
	        // Statuspane area
	        iExtension->iBgContext->SetLayerImage( ELayerBackground, KAknsIIDQsnBgAreaStatus );
	        iExtension->iBgContext->SetLayerRect( ELayerBackground, status_pane_usual.Rect() );
	        iExtension->iBgContext->SetLayerImage( ELayerExtension, KAknsIIDNone );
	        iExtension->iBgContext->SetLayerImage( ELayerStripe, KAknsIIDQsnBgNavipaneSolid );
	        // skin does not follow avkon LAF, skin wipe is 176x15, not 174x15
	        TAknLayoutRect navi_wipe;
	        navi_wipe.LayoutRect( status_pane_usual.Rect(), 
	            AKN_LAYOUT_WINDOW_Status_pane_elements_Line_1 );
	        TRect skinnedNaviWipeRect(navi_wipe.Rect());
	        skinnedNaviWipeRect.iTl.iX = 0;
	        skinnedNaviWipeRect.iBr.iX = status_pane_usual.Rect().iBr.iX;
	        iExtension->iBgContext->SetLayerRect( ELayerStripe, skinnedNaviWipeRect );
	        // main pane
	        iExtension->iBgContext->SetLayerImage( ELayerWallpaper, KAknsIIDQsnBgAreaMain );
	        iExtension->iBgContext->SetLayerRect( ELayerWallpaper, main_pane.Rect() );
	        // control pane
	        iExtension->iBgContext->SetLayerImage( ELayerN, KAknsIIDQsnBgAreaControl );
	        iExtension->iBgContext->SetLayerRect( ELayerN, control_pane.Rect() );
	        }
        }
	}


EXPORT_C CAknLocalScreenClearer* CAknLocalScreenClearer::NewLC()
	{
	return CAknLocalScreenClearer::NewLC(ETrue);
	}

EXPORT_C CAknLocalScreenClearer* CAknLocalScreenClearer::NewLC(TBool aBlankAppStatusPane)
	{
	CAknLocalScreenClearer* self=new(ELeave) CAknLocalScreenClearer;
	CleanupStack::PushL(self);
	CEikonEnv& eikEnv = *static_cast<CEikonEnv*>(self->ControlEnv());
	self->ConstructL(eikEnv.RootWin(), 0, aBlankAppStatusPane);
	return(self);
	}

EXPORT_C CAknLocalScreenClearer* CAknLocalScreenClearer::NewL(TBool aBlankAppStatusPane)
	{
	CAknLocalScreenClearer* self = CAknLocalScreenClearer::NewLC(aBlankAppStatusPane);
	CleanupStack::Pop(self);
	return(self);
	}
	
EXPORT_C void CAknLocalScreenClearer::HandleResourceChange(TInt aType)
	{
	if (aType == KEikDynamicLayoutVariantSwitch)
		{
		SetShapeL();
		SetSkinShapeL();
		DrawDeferred();		
		}
	}
	
