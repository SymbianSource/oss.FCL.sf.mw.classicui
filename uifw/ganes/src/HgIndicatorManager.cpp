/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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


#include "HgIndicatorManager.h"

#include "HgConstants.h"
#include <ganes/HgItem.h>

#include <AknIconUtils.h>
#include <avkon.mbg>
#include <AknsDrawUtils.h>
#include <gulicon.h>
#include <AknUtils.h>
#include <ganes.mbg>
#include <AknLayout2ScalableDef.h>


CHgIndicatorManager* CHgIndicatorManager::NewL()
    {
    CHgIndicatorManager* self = new (ELeave) CHgIndicatorManager;
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

CHgIndicatorManager::~CHgIndicatorManager()
    {
    delete iDrmIcon;
    delete iDrmExpIcon;
    delete iVideoIcon;
    delete iPlaybackIndicatorIcon;
    delete iMmcIcon;
    delete iMarkIcon;
    delete iMarkIconOff;
    delete iPauseIndicatorIcon;
    delete iBrokenPlaylistIcon;
    delete iBrokenTrackIcon; 
    delete iCorruptedTrackIcon;
    delete iMassStorageIcon;
    delete iNewVideoIcon;
    delete iPhoneStorageIcon;
    delete iNewPodcastIcon;
    delete iPlayedPodcastIcon;
    delete iCompletelyPlayedPodcastIcon;
    delete iMoveUpIcon;
    delete iMoveDownIcon;
    delete iMoveUpDownIcon;
    }

void CHgIndicatorManager::InitIndicatorsL( const TSize& aIndicatorSize )
    {
    // Non-Skinned icons
    // Broken Playlist icon
    InitIconL( iBrokenPlaylistIcon, 
            EMbmGanesQgn_graf_mup_lst_brokenplayl, 
            EMbmGanesQgn_graf_mup_lst_brokenplayl_mask, 
            aIndicatorSize );
    
    // Broken track icon
    InitIconL( iBrokenTrackIcon, 
            EMbmGanesQgn_graf_mup_lst_brokentrack, 
            EMbmGanesQgn_graf_mup_lst_brokentrack_mask, 
            aIndicatorSize );
    
    // Corrupted track icon
    InitIconL( iCorruptedTrackIcon, 
            EMbmGanesQgn_graf_mup_lst_corrupttrack, 
            EMbmGanesQgn_graf_mup_lst_corrupttrack_mask, 
            aIndicatorSize );
    
    // New podcast icon 
    InitIconL( iNewPodcastIcon, 
            EMbmGanesQgn_graf_mup_lst_pdc_new, 
            EMbmGanesQgn_graf_mup_lst_pdc_new_mask, 
            aIndicatorSize );
    
    // Played podcast icon 
    InitIconL( iPlayedPodcastIcon, 
            EMbmGanesQgn_graf_mup_lst_pdc_partplay, 
            EMbmGanesQgn_graf_mup_lst_pdc_partplay_mask, 
            aIndicatorSize );

    // Completely played podcast icon 
    InitIconL( iCompletelyPlayedPodcastIcon, 
            EMbmGanesQgn_graf_mup_lst_pdc_compplay, 
            EMbmGanesQgn_graf_mup_lst_pdc_compplay_mask, 
            aIndicatorSize );

    // Video icon
    InitIconL( iVideoIcon,
            EMbmGanesQgn_indi_media_thumbnail, 
            EMbmGanesQgn_indi_media_thumbnail_mask, 
            aIndicatorSize );

    // Skinned icons
    // Mark icon
    InitIconL( iMarkIcon, KAknsIIDQgnPropCheckboxOn, 
            EMbmGanesQgn_prop_checkbox_on, 
            EMbmGanesQgn_prop_checkbox_on_mask, 
            aIndicatorSize );

    // Mark icon, off state
    InitIconL( iMarkIconOff, KAknsIIDQgnPropCheckboxOff, 
            EMbmGanesQgn_prop_checkbox_off, 
            EMbmGanesQgn_prop_checkbox_off_mask, 
            aIndicatorSize );

    // DRM valid icon
    InitIconL( iDrmIcon, KAknsIIDQgnPropDrmRightsValidSuper, 
            EMbmGanesQgn_prop_drm_rights_valid_super, 
            EMbmGanesQgn_prop_drm_rights_valid_super_mask, 
            aIndicatorSize );
    
    // DRM expired icon
    InitIconL( iDrmExpIcon, KAknsIIDQgnPropDrmRightsExpSuper, 
            EMbmGanesQgn_prop_drm_rights_exp_super, 
            EMbmGanesQgn_prop_drm_rights_exp_super_mask, 
            aIndicatorSize );
    
    // Playback icon
    InitIconL( iPlaybackIndicatorIcon, KAknsIIDQgnIndiMupPlay, 
            EMbmGanesQgn_indi_mup_play, 
            EMbmGanesQgn_indi_mup_play_mask, 
            aIndicatorSize );
    
    // Pause icon
    InitIconL( iPauseIndicatorIcon, KAknsIIDQgnIndiMupPause, 
            EMbmGanesQgn_indi_mup_pause, 
            EMbmGanesQgn_indi_mup_pause_mask, 
            aIndicatorSize );
    
    // New Video icon
    InitIconL( iNewVideoIcon, KAknsIIDQgnPropFmgrFileVideo, 
            EMbmGanesQgn_prop_fmgr_file_video, 
            EMbmGanesQgn_prop_fmgr_file_video_mask, 
            aIndicatorSize );
    
    // Phone memory icon
    InitIconL( iPhoneStorageIcon, KAknsIIDQgnPropPhoneMemc, 
            EMbmGanesQgn_prop_phone_memc, 
            EMbmGanesQgn_prop_phone_memc_mask, 
            aIndicatorSize );

    // MMC memory icon
    InitIconL( iMmcIcon, KAknsIIDQgnPropMmcMemc, 
            EMbmGanesQgn_prop_mmc_memc, 
            EMbmGanesQgn_prop_mmc_memc_mask, 
            aIndicatorSize );
    
    // Mass memory icon
    InitIconL( iMassStorageIcon, KAknsIIDQgnPropFmgrMsSmall, 
            EMbmGanesQgn_prop_fmgr_ms_small, 
            EMbmGanesQgn_prop_fmgr_ms_small_mask, 
            aIndicatorSize );

    // Move up icon
    InitIconL( iMoveUpIcon, KAknsIIDQgnGrafMupAdtlReorderUp, 
            EMbmGanesQgn_graf_mup_adtl_reorder_up, 
            EMbmGanesQgn_graf_mup_adtl_reorder_up_mask, 
            aIndicatorSize );
    
    // Move down icon
    InitIconL( iMoveDownIcon, KAknsIIDQgnGrafMupAdtlReorderDown, 
            EMbmGanesQgn_graf_mup_adtl_reorder_down, 
            EMbmGanesQgn_graf_mup_adtl_reorder_down_mask, 
            aIndicatorSize );
    
    // Move updown icon
    InitIconL( iMoveUpDownIcon, KAknsIIDQgnGrafMupAdtlReorderUpdown, 
            EMbmGanesQgn_graf_mup_adtl_reorder_updown, 
            EMbmGanesQgn_graf_mup_adtl_reorder_updown_mask, 
            aIndicatorSize );
    }

void CHgIndicatorManager::DrawIndicators( 
        CWindowGc& aGc,
        const TRect& aRect,
        TInt aFlags, 
        TAknWindowComponentLayout aFirstIndicatorLayout, 
        TAknWindowComponentLayout aSecondIndicatorLayout,
        TBool aMarkingMode
        ) const
    {
    TAknLayoutRect secondIndicator;
    secondIndicator.LayoutRect(aRect, aSecondIndicatorLayout);

    TAknLayoutRect firstIndicator;
    firstIndicator.LayoutRect(aRect, aFirstIndicatorLayout);
    
    TAknLayoutRect rect = secondIndicator;
    TBool memIndicator = EFalse;
    TInt indicatorsDrawn = 0;
    
    if( aFlags & CHgItem::EHgItemFlagMarked )
        {
        rect.DrawImage(aGc, iMarkIcon->Bitmap(), iMarkIcon->Mask());
        ++indicatorsDrawn;
        rect = firstIndicator;
        }
    else if(aMarkingMode)
        {
        rect.DrawImage(aGc, iMarkIconOff->Bitmap(), iMarkIconOff->Mask());
        ++indicatorsDrawn;
        rect = firstIndicator;    
        }
    
    if( DrawIndicator(aGc, rect, aFlags, memIndicator) )
        {
        ++indicatorsDrawn;
        rect = firstIndicator;
        }
    
    if( indicatorsDrawn == 1 && !memIndicator )
        {
        if( aFlags & CHgItem::EHgItemFlagsMmc )
            {
            rect.DrawImage(aGc, iMmcIcon->Bitmap(), iMmcIcon->Mask() );        
            }
        else if( aFlags & CHgItem::EHgItemFlagsMassStorageIndicator )
            {
            rect.DrawImage(aGc, iMassStorageIcon->Bitmap(), iMassStorageIcon->Mask() );        
            }
        else if( aFlags & CHgItem::EHgItemFlagsPhoneStorageIndicator )
            {
            rect.DrawImage(aGc, iPhoneStorageIcon->Bitmap(), iPhoneStorageIcon->Mask() );        
            }
        }
    
    }

TBool CHgIndicatorManager::DrawIndicator( 
        CWindowGc& aGc,
        TAknLayoutRect& aRect,
        TInt aFlags,
        TBool& aMemIndicator
        ) const
    {
    TBool ret = EFalse;
    
    if( aFlags & CHgItem::EHgItemFlagsPlaybackIndicator )
        {
        aRect.DrawImage(aGc, iPlaybackIndicatorIcon->Bitmap(), iPlaybackIndicatorIcon->Mask() ); 
        ret = ETrue;
        }
    else if( aFlags & CHgItem::EHgItemFlagsPauseIndicator )
        {
        aRect.DrawImage(aGc, iPauseIndicatorIcon->Bitmap(), iPauseIndicatorIcon->Mask() ); 
        ret = ETrue;
        }
    else if( aFlags & CHgItem::EHgItemFlagsDrmRightsValid )
        {
        aRect.DrawImage(aGc, iDrmIcon->Bitmap(), iDrmIcon->Mask() ); 
        ret = ETrue;
        }
    else if( aFlags & CHgItem::EHgItemFlagsDrmRightsExpired )
        {
        aRect.DrawImage(aGc, iDrmExpIcon->Bitmap(), iDrmExpIcon->Mask() ); 
        ret = ETrue;
        }
    else if( aFlags & CHgItem::EHgItemFlagsVideo )
        {
        aRect.DrawImage(aGc, iVideoIcon->Bitmap(), iVideoIcon->Mask() ); 
        ret = ETrue;
        }    
    else if( aFlags & CHgItem::EHgItemFlagsBrokenPlaylistIndicator )
        {
        aRect.DrawImage(aGc, iBrokenPlaylistIcon->Bitmap(), iBrokenPlaylistIcon->Mask() ); 
        ret = ETrue;
        }
    else if( aFlags & CHgItem::EHgItemFlagsBrokenTrackIndicator )
        {
        aRect.DrawImage(aGc, iBrokenTrackIcon->Bitmap(), iBrokenTrackIcon->Mask() ); 
        ret = ETrue;
        }
    else if( aFlags & CHgItem::EHgItemFlagsCorruptedTrackIndicator )
        {
        aRect.DrawImage(aGc, iCorruptedTrackIcon->Bitmap(), iCorruptedTrackIcon->Mask() ); 
        ret = ETrue;
        }
    else if( aFlags & CHgItem::EHgItemFlagsNewVideoIndicator )
        {
        aRect.DrawImage(aGc, iNewVideoIcon->Bitmap(), iNewVideoIcon->Mask() );         
        ret = ETrue;
        }
    else if( aFlags & CHgItem::EHgItemFlagsNewPodcastIndicator )
        {
        aRect.DrawImage(aGc, iNewPodcastIcon->Bitmap(), iNewPodcastIcon->Mask() );         
        ret = ETrue;
        }
    else if( aFlags & CHgItem::EHgItemFlagsPlayedPodcastIndicator )
        {
        aRect.DrawImage(aGc, iPlayedPodcastIcon->Bitmap(), iPlayedPodcastIcon->Mask() );         
        ret = ETrue;
        }
    else if( aFlags & CHgItem::EHgItemFlagsCompletelyPlayedPodcastIndicator )
        {
        aRect.DrawImage(aGc, iCompletelyPlayedPodcastIcon->Bitmap(), iCompletelyPlayedPodcastIcon->Mask() );         
        ret = ETrue;
        }
    else if( aFlags & CHgItem::EHgItemFlagsMoveUpIndicator )
        {
        aRect.DrawImage(aGc, iMoveUpIcon->Bitmap(), iMoveUpIcon->Mask() );         
        ret = ETrue;
        }
    else if( aFlags & CHgItem::EHgItemFlagsMoveDownIndicator )
        {
        aRect.DrawImage(aGc, iMoveDownIcon->Bitmap(), iMoveDownIcon->Mask() );         
        ret = ETrue;
        }
    else if( aFlags & CHgItem::EHgItemFlagsMoveUpDownIndicator )
        {
        aRect.DrawImage(aGc, iMoveUpDownIcon->Bitmap(), iMoveUpDownIcon->Mask() );         
        ret = ETrue;
        }
    else if( aFlags & CHgItem::EHgItemFlagsMmc )
        {
        aRect.DrawImage(aGc, iMmcIcon->Bitmap(), iMmcIcon->Mask() ); 
        ret = ETrue;
        aMemIndicator = ETrue;
        }
    else if( aFlags & CHgItem::EHgItemFlagsMassStorageIndicator )
        {
        aRect.DrawImage(aGc, iMassStorageIcon->Bitmap(), iMassStorageIcon->Mask() );
        ret = ETrue;
        aMemIndicator = ETrue;
        }
    else if( aFlags & CHgItem::EHgItemFlagsPhoneStorageIndicator )
        {
        aRect.DrawImage(aGc, iPhoneStorageIcon->Bitmap(), iPhoneStorageIcon->Mask() );
        ret = ETrue;
        aMemIndicator = ETrue;
        }
    return ret;
    }

// -----------------------------------------------------------------------------
// CHgIndicatorManager::InitIconL()
// -----------------------------------------------------------------------------
//
void CHgIndicatorManager::InitIconL( CGulIcon*& aIcon,
                                TInt aIconIndex,
                                TInt aMaskIndex,
                                TSize aSize )
    {
    if( !aIcon )
        {
        CFbsBitmap* bitmap, *mask;
        AknIconUtils::CreateIconL( 
                bitmap, 
                mask, 
                KGanesMif, 
                aIconIndex, 
                aMaskIndex );
        aIcon = CGulIcon::NewL(bitmap, mask);
        }

    AknIconUtils::SetSize(aIcon->Bitmap(), aSize);        
    }

// -----------------------------------------------------------------------------
// CHgIndicatorManager::InitIconL()
// -----------------------------------------------------------------------------
//
void CHgIndicatorManager::InitIconL( CGulIcon*& aIcon,
                                const TAknsItemID& aItemId,
                                TInt aIconIndex,
                                TInt aMaskIndex,
                                TSize aSize )
    {
    if( !aIcon )
        {
        aIcon = AknsUtils::CreateGulIconL( 
                AknsUtils::SkinInstance(), 
                aItemId, 
                KGanesMif, 
                aIconIndex, 
                aMaskIndex );
        }

    AknIconUtils::SetSize(aIcon->Bitmap(), aSize);        
    }

// -----------------------------------------------------------------------------
// CHgIndicatorManager::InitIconL()
// -----------------------------------------------------------------------------
//
void CHgIndicatorManager::InitColorIconL( CGulIcon*& aIcon,
                                const TAknsItemID& aItemId,
                                TInt aIconIndex,
                                TInt aMaskIndex,
                                TSize aSize )
    {
    if( !aIcon )
        {
        TRgb defaultColour( KRgbWhite );
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        
        AknsUtils::GetCachedColor( skin,
                defaultColour,
                KAknsIIDQsnIconColors,
                EAknsCIQsnIconColorsCG13 );
        
        CFbsBitmap *bitmap,*mask;
        AknsUtils::CreateColorIconL( 
                skin, 
                aItemId, 
                KAknsIIDQsnIconColors,
                EAknsCIQsnIconColorsCG13,
                bitmap, 
                mask,
                KGanesMif, 
                aIconIndex, 
                aMaskIndex,
                defaultColour );
        
        aIcon = CGulIcon::NewL(bitmap, mask);
        }

    AknIconUtils::SetSize(aIcon->Bitmap(), aSize);        
    }

TInt CHgIndicatorManager::CountIndicators( TInt aFlags )
    {
    TInt count = 0;
    aFlags &= (~CHgItem::EHgItemFlagsIconOverlayIndicator); // overlayindicator not counted
    while(aFlags)
        {
        count += aFlags & 0x1;
        aFlags = aFlags >> 1;
        }
    return count > KMaxNumberOfTitleIndicators ? KMaxNumberOfTitleIndicators : count;
    }

CHgIndicatorManager::CHgIndicatorManager()
    {
    
    }

void CHgIndicatorManager::ConstructL()
    {
    
    }
