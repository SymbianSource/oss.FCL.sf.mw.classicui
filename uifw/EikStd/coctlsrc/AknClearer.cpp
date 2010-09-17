/*
* Copyright (c) 2002-2010 Nokia Corporation and/or its subsidiary(-ies).
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
#include <alf/alfcompositionutility.h>

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
	EAknScreenClearerBlankAppStatusPane
	};

enum 
    {
    ELayerBackground = 0,
    ELayerExtension = 1,
    ELayerStripe = 2,
    ELayerWallpaper = 3,
    ELayerN = 4
    };

enum 
    {
    ELayerStaconTop = 0,
    ELayerStaconBottom = 1,
    ELayerStaconMain = 2,
    ELayerStaconWallpaper = 3,
    ELayerStaconN = 4
    };

enum 
    {
    ELayerFlatBackground = 0,
    ELayerFlatTl = 1,
    ELayerFlatTr = 2,
    ELayerFlatBl = 3,
    ELayerFlatBr = 4,
    ELayerFlatT = 5,
    ELayerFlatB = 6,
    ELayerFlatR = 7,
    ELayerFlatL = 8,
    ELayerFlatCenter = 9,
    ELayerFlatMain = 10,
    ELayerFlatWallpaper = 11,
    ELayerFlatN = 12
    };


class CAknScreenClearerBaseExtension : public CBase
    {
public:
    ~CAknScreenClearerBaseExtension()
        {
        delete iBgContext;
        }
public:
    CAknsLayeredBackgroundControlContext* iBgContext;
    TInt iOrdinalPosition;
	TBool iTransparent;
    };


EXPORT_C CAknScreenClearerBase::~CAknScreenClearerBase()
	{
    delete iExtension;
	}


void CAknScreenClearerBase::CreateExtensionL()
	{
	if ( !iExtension )
		{
		iExtension = new (ELeave) CAknScreenClearerBaseExtension;
		}
	}


void CAknScreenClearerBase::SetTransparent( TBool aTransparent )
    {
    iExtension->iTransparent = aTransparent;
    }


EXPORT_C void CAknScreenClearerBase::ConstructL(RWindowGroup& aParent, TInt aOrdinalPos, TBool aBlankAppStatusPane)
	{
	CreateExtensionL();

	CreateWindowL(&aParent);

	if ( iExtension->iTransparent )
		{
		EnableWindowTransparency();
		}

#ifndef NO_ALF_OBSERVER
    CAlfEffectObserver* alfEffectObserver = CAlfEffectObserver::NewL(); 
    alfEffectObserver->SetDistractionWindow(*DrawableWindow());
    delete alfEffectObserver;
#endif

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

    if ( !iExtension->iTransparent )
        {
        AknsDrawUtils::Background( skin, iExtension->iBgContext, this, gc, Rect() );
        }
    else
        {
        gc.SetDrawMode( CGraphicsContext::EDrawModeWriteAlpha );
        gc.Clear( Rect() );
        gc.Reset();
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
    
	// Set the clearer window's size so that it covers the screen in both
	// portrait and landscape orientations simultaneously.
	// This is done in order to prevent NGA from drawing control groups
	// underneath the fullscreen foreground application in cases the clearer
	// orientation can't be readily updated during the layout switch, due
	// to e.g. application startup taking a long time.
	// Note that only the clearer window's size is set to be larger, the
	// skin background is still the screen size so that the skin background
	// won't get stretched.
	TRect screenRect( KWholeScreen );
	TRect squareScreenRect( screenRect );
    if ( squareScreenRect.Width() > squareScreenRect.Height() )
        {
        squareScreenRect.SetHeight( squareScreenRect.Width() );
        }
    else
        {
        squareScreenRect.SetWidth( squareScreenRect.Height() );
        }
	
    if ( iFlags[EAknScreenClearerBlankAppStatusPane] )
        {
        shape.AddRect( squareScreenRect );
        }
    else
        {
        // Square shape is used only if the clearer is used to clear the
        // whole screen.
        shape.AddRect( screenRect );
		sp->GetShapeL( appStatuspaneShape,
		               !iFlags[EAknScreenClearerBlankAppStatusPane],
		               ETrue );
        shape.SubRegion( appStatuspaneShape );
        }

	if ( shape.CheckError() )
	    {
		User::Leave( KErrNoMemory );
	    }

	SetRect( iFlags[EAknScreenClearerBlankAppStatusPane] ? squareScreenRect :
                                                           screenRect );
	DrawableWindow()->SetShape( shape );

	CleanupStack::PopAndDestroy( 2, &shape ); // close shapes
	}



void CAknScreenClearerBase::SetSkinShapeL()
	{	
    for (TInt n=0; n<ELayerFlatN; n++)
        {
        iExtension->iBgContext->SetLayerImage( n, KAknsIIDNone );                
        }            

    CAknEnv* aknEnv = AVKONENV;
    
    TInt usualSpLayout =
        aknEnv->StatusPaneResIdForCurrentLayout(
            R_AVKON_STATUS_PANE_LAYOUT_USUAL );
    
    TInt idleSpLayout =
        aknEnv->StatusPaneResIdForCurrentLayout(
            R_AVKON_STATUS_PANE_LAYOUT_IDLE );
    
    TBool widescreenPaneUsed =
        ( usualSpLayout == R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL ) ||
        ( idleSpLayout  == R_AVKON_WIDESCREEN_PANE_LAYOUT_IDLE );
    
    TBool flatStatuspaneusedInLandscape =
        ( usualSpLayout == R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL_FLAT ) ||
        ( usualSpLayout == R_AVKON_STATUS_PANE_LAYOUT_USUAL_FLAT );
    

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
                TInt currentStatusPaneLayoutResId = aknEnv->StatusPaneResIdForCurrentLayout(statusPane->CurrentLayoutResId());

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


EXPORT_C CAknLocalScreenClearer* CAknLocalScreenClearer::NewLC(TBool aBlankAppStatusPane, TBool aTransparent)
	{
	CAknLocalScreenClearer* self=new(ELeave) CAknLocalScreenClearer;
	CleanupStack::PushL(self);
	self->CreateExtensionL();
	self->SetTransparent(aTransparent);
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


EXPORT_C CAknLocalScreenClearer* CAknLocalScreenClearer::NewL(TBool aBlankAppStatusPane, TBool aTransparent)
	{
	CAknLocalScreenClearer* self = CAknLocalScreenClearer::NewLC(aBlankAppStatusPane, aTransparent);
	CleanupStack::Pop(self);
	return(self);
	}


EXPORT_C void CAknLocalScreenClearer::HandleResourceChange(TInt aType)
	{
	if (aType == KEikDynamicLayoutVariantSwitch)
		{
        TRAP_IGNORE(
            SetShapeL();
            SetSkinShapeL();
            );
		DrawDeferred();		
		}
	}
	
