/*
* Copyright (c) 2002-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation of the navi pane container control.
*
*/


// SYSTEM INCLUDE FILES
#include <eikfutil.h>
#include <eiklabel.h>
#include <eikimage.h>
#include <layoutmetadata.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <fbs.h>
#include <avkon.rsg>
#include <centralrepository.h>
#include <AknSkinsInternalCRKeys.h>
#include <AknsDrawUtils.h>
#include <AknsLayeredBackgroundControlContext.h>
#include <mifconvdefs.h>
#include <akniconconfig.h>

#include <AknTasHook.h>
// USER INCLUDE FILES
#include "aknenv.h"
#include "AknDef.h"
#include "aknappui.h"
#include "aknconsts.h"
#include "akntabgrp.h"
#include "aknnavide.h"
#include "AknIndicatorContainer.h"
#include "AknVolumePopup.h"
#include "AknUtils.h"
#include "AknBitmapMirrorUtils.h"
#include "avkon.hrh"
#include "aknnavi.h"
#include "aknnavilabel.h"
#include "akncontext.h"
#include "AknSignalNotify.h"
#include "AknNaviForegroundObserver.h"
#include "AknNaviConstants.h"
#include "aknEditStateIndicator.h"
#include "AknStatuspaneUtils.h"
#include "akntitle.h"
#include "AknTitlePaneLabel.h"
#include "AknDebug.h"

const TInt KAknNaviPaneStackGranularity = 2;
/**
* Extension class for CAknNavigationControlContainer.
*/
class CAknNavigationControlContainerExtension : public CBase
    {
public:
    CAknNavigationControlContainerExtension(){};
    ~CAknNavigationControlContainerExtension(){};

public:
    TInt                        iCurrentColorScheme;
    CAknNaviForegroundObserver* iForegroundObserver;
    TBool                       iDestructionOngoing;
    CFbsBitmap*                 iNaviColorBitmap;
    TInt                        iPreferredNaviDecoratorLayoutStyle;
    TBool                       iIsActiveIdle;
    };



// ----------------------------------------------------------------------------
// CAknNavigationControlContainer::CAknNavigationControlContainer
// Default constructor.
// ----------------------------------------------------------------------------
//
EXPORT_C CAknNavigationControlContainer::CAknNavigationControlContainer() :
    iStatusPane( CEikStatusPaneBase::Current() )
    {
    AKNTASHOOK_ADD( this, "CAknNavigationControlContainer" );
    }


// ----------------------------------------------------------------------------
// CAknNavigationControlContainer::~CAknNavigationControlContainer
// Destructor.
// ----------------------------------------------------------------------------
//
EXPORT_C CAknNavigationControlContainer::~CAknNavigationControlContainer()
    {
    AKNTASHOOK_REMOVE();
    if ( iExtension )
        {
        iExtension->iDestructionOngoing = ETrue;
        }

    AknsUtils::DeregisterControlPosition( this );

    delete iNaviDecoratorFromResource;

    if ( iNaviPaneControls )
        {
        const TInt last = iNaviPaneControls->Count() - 1;
        TInt ii = 0;
        for ( ii = last; ii >= 0; ii-- )
            {
            Pop( iNaviPaneControls->At( ii ) );
            }
        delete iNaviPaneControls;
        }

    for ( TInt jj = 0; jj < 4; jj++ )
        {
        delete iNaviArrowBitmap[ jj ];
        }

    if ( iExtension )
        {
        delete iExtension->iForegroundObserver;
        delete iExtension->iNaviColorBitmap;
        delete iExtension;
        }
    }


// ----------------------------------------------------------------------------
// CAknNavigationControlContainer::ConstructL
// Second-phase constructor.
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknNavigationControlContainer::ConstructL()
    {
    if ( !iExtension )
        {
        iExtension =
            new (ELeave) CAknNavigationControlContainerExtension();
        iExtension->iCurrentColorScheme = ColorScheme();
        iExtension->iForegroundObserver =
            CAknNaviForegroundObserver::NewL( this );
        iExtension->iIsActiveIdle = AknStatuspaneUtils::IsActiveIdle();
        }

    if ( !iNaviPaneControls )
        {
        iNaviPaneControls =
            new (ELeave) CAknNaviPaneStack( KAknNaviPaneStackGranularity );
        }

    // creating color bitmap
    LoadNaviColorBitmapL();

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    AknsUtils::CreateIconL( skin,
                            KAknsIIDQgnIndiNaviArrowLeft,
                            iNaviArrowBitmap[ 0 ],
                            iNaviArrowBitmap[ 1 ],
                            KAvkonBitmapFile,
                            EMbmAvkonQgn_indi_navi_arrow_left,
                            EMbmAvkonQgn_indi_navi_arrow_left_mask );

    AknsUtils::CreateIconL( skin,
                            KAknsIIDQgnIndiNaviArrowRight,
                            iNaviArrowBitmap[ 2 ],
                            iNaviArrowBitmap[ 3 ],
                            KAvkonBitmapFile,
                            EMbmAvkonQgn_indi_navi_arrow_right,
                            EMbmAvkonQgn_indi_navi_arrow_right_mask );

    }


// ----------------------------------------------------------------------------
// CAknNavigationControlContainer::ConstructFromResourceL
// Resource constructor.
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknNavigationControlContainer::ConstructFromResourceL(
    TResourceReader& aReader )
    {
    ConstructL();
    iNaviDecoratorFromResource =
        ConstructNavigationDecoratorFromResourceL( aReader );
    if ( iNaviDecoratorFromResource )
        {
        PushL( *iNaviDecoratorFromResource );
        }
    }


// ----------------------------------------------------------------------------
// CAknNavigationControlContainer::ConstructNavigationDecoratorFromResourceL
// Creates a decorated navi pane control from resource.
// ----------------------------------------------------------------------------
//
EXPORT_C CAknNavigationDecorator* CAknNavigationControlContainer::ConstructNavigationDecoratorFromResourceL(
    TResourceReader& aReader )
    {
    TInt controlType = aReader.ReadInt16(); // type
    CAknNavigationDecorator* decoratedNaviObject = NULL;

    switch ( controlType )
        {
        case ENaviDecoratorControlNone:
            {
            PushDefaultL();
            break;
            }

        case ENaviDecoratorControlTabGroup:
            {
            decoratedNaviObject  = CreateTabGroupL( aReader );
            break;
            }

        case ENaviDecoratorLabel:
            {
            decoratedNaviObject  = CreateNavigationLabelL( aReader );
            break;
            }

        case ENaviDecoratorImage:
            {
            decoratedNaviObject  = CreateNavigationImageL( aReader );
            break;
            }

        case ENaviDecoratorToolTip:
            {
            decoratedNaviObject  = CreateMessageLabelL( aReader );
            break;
            }

        default:
            {
            break;
            }
        }

    return decoratedNaviObject;
    }


// ----------------------------------------------------------------------------
// CAknNavigationControlContainer::CreateTabGroupL
// Creates a decorated tab group control to use in navi pane.
// ----------------------------------------------------------------------------
//
EXPORT_C CAknNavigationDecorator* CAknNavigationControlContainer::CreateTabGroupL()
    {
    TBool penEnabled( AknLayoutUtils::PenEnabled() );

    CAknTabGroup* tabGroup = CAknTabGroup::NewL( *this );

    // Tab group to the clean up stack in first line of NewL function.
    CAknNavigationDecorator* decoratedTabGroup =
        CAknNavigationDecorator::NewL( this,
                                       tabGroup,
                                       CAknNavigationDecorator::ETabGroup );

    if ( penEnabled )
        {
        // Set tab group as an observer of the decorator for right/left
        // arrows tapping.
        decoratedTabGroup->SetNaviDecoratorObserver( tabGroup );
        }

    CleanupStack::PushL( decoratedTabGroup );

    decoratedTabGroup->SetContainerWindowL( *this );

    // Navi arrows are not used for tab group in touch layouts.
    decoratedTabGroup->MakeScrollButtonVisible( !penEnabled );

    tabGroup->SetRect(
        CAknNavigationDecorator::DecoratedTabControlRect(
            !AknStatuspaneUtils::UsualLayoutActive(),
            !penEnabled ) );

    CleanupStack::Pop( decoratedTabGroup );

    decoratedTabGroup->SetObserver( this );

    return decoratedTabGroup;
    }


// ----------------------------------------------------------------------------
// CAknNavigationControlContainer::CreateTabGroupL
// Creates a decorated tab group control to use in navi pane.
// ----------------------------------------------------------------------------
//
EXPORT_C CAknNavigationDecorator* CAknNavigationControlContainer::CreateTabGroupL(
    MAknTabObserver *aObserver )
    {
    CAknNavigationDecorator* navDec = CreateTabGroupL();
    CAknTabGroup* tabGroup =
        static_cast<CAknTabGroup*>( navDec->DecoratedControl() );
    tabGroup->SetObserver( aObserver );

    return navDec;
    }


// ----------------------------------------------------------------------------
// CAknNavigationControlContainer::CreateTabGroupL
// Creates a decorated tab group control to use in navi pane.
// ----------------------------------------------------------------------------
//
EXPORT_C CAknNavigationDecorator* CAknNavigationControlContainer::CreateTabGroupL(
    TResourceReader& aReader, MAknTabObserver* aObserver )
    {
    CAknNavigationDecorator *navDec = CreateTabGroupL( aReader );

    CAknTabGroup* tabGroup =
        static_cast<CAknTabGroup*>( navDec->DecoratedControl() );
    tabGroup->SetObserver( aObserver );

    return navDec;
    }


// ----------------------------------------------------------------------------
// CAknNavigationControlContainer::CreateTabGroupL
// Creates a decorated tab group control to use in navi pane.
// ----------------------------------------------------------------------------
//
EXPORT_C CAknNavigationDecorator* CAknNavigationControlContainer::CreateTabGroupL(
    TResourceReader& aReader)
    {
    CAknNavigationDecorator* decoratedTabGroup;
    decoratedTabGroup  = CreateTabGroupL();
    CleanupStack::PushL( decoratedTabGroup );

    CAknTabGroup* tabGroup =
        static_cast<CAknTabGroup*>( decoratedTabGroup->DecoratedControl() );

    TInt width = aReader.ReadInt16();
    tabGroup->SetTabFixedWidthL( width );
    TInt activeIndex = aReader.ReadInt16();

    TInt count = aReader.ReadInt16(); // Tab count
    for ( TInt ii = 0; ii < count; ii++ )
        {
        tabGroup->AddTabL( aReader );
        }
    tabGroup->SetActiveTabByIndex( activeIndex );

    CleanupStack::Pop( decoratedTabGroup );
    return decoratedTabGroup;
    }


// ----------------------------------------------------------------------------
// CAknNavigationControlContainer::CreateNavigationLabelL
// Creates a decorated navigation label control to use in navi pane.
// ----------------------------------------------------------------------------
//
EXPORT_C CAknNavigationDecorator* CAknNavigationControlContainer::CreateNavigationLabelL(
    const TDesC& aText )
    {
    CAknNaviLabel* label = new (ELeave) CAknNaviLabel;
    CleanupStack::PushL( label );

    label->SetContainerWindowL( *this );
    label->SetTextL( aText );
    label->SetNaviLabelType( CAknNaviLabel::EAdditionalInfoLabel );

    CleanupStack::Pop( label );
    CAknNavigationDecorator* decoratedLabel =
        CAknNavigationDecorator::NewL( this,
                                       label,
                                       CAknNavigationDecorator::ENaviLabel );
    CleanupStack::PushL( decoratedLabel );

    decoratedLabel->SetContainerWindowL( *this );
    decoratedLabel->SetControlContext( this );
    decoratedLabel->MakeScrollButtonVisible( EFalse );

    CleanupStack::Pop( decoratedLabel );

    return decoratedLabel;
    }


// ----------------------------------------------------------------------------
// CAknNavigationControlContainer::CreateNavigationLabelL
// Creates a decorated navigation label control to use in navi pane.
// ----------------------------------------------------------------------------
//
EXPORT_C CAknNavigationDecorator* CAknNavigationControlContainer::CreateNavigationLabelL(
    TResourceReader& aReader )
    {
    HBufC* txt = aReader.ReadHBufCL();  // Label text
    CAknNavigationDecorator* decoratedLabel = NULL;

    if ( txt )
        {
        CleanupStack::PushL( txt );
        decoratedLabel = CreateNavigationLabelL( *txt );
        CleanupStack::PopAndDestroy( txt );
        }
    else
        {
        decoratedLabel = CreateNavigationLabelL( KNullDesC );
        }

    return decoratedLabel;
    }


// ----------------------------------------------------------------------------
// CAknNavigationControlContainer::CreateNavigationImageL
// Creates a decorated navigation image control to use in navi pane.
// ----------------------------------------------------------------------------
//
EXPORT_C CAknNavigationDecorator* CAknNavigationControlContainer::CreateNavigationImageL(
    const CFbsBitmap* aBitmap, const CFbsBitmap* aMaskBitmap )
    {
    CEikImage* image = new (ELeave) CEikImage;
    CleanupStack::PushL( image );

    image->SetContainerWindowL( *this );

    TAknWindowComponentLayout layout;
    if ( AknStatuspaneUtils::StaconPaneActive() )
        {
        layout = TAknWindowComponentLayout::Compose(
                    AknLayoutScalable_Avkon::navi_navi_pane_stacon( 1 ),
                    AknLayoutScalable_Avkon::navi_navi_icon_text_pane() );
        }
    else
        {
        layout = TAknWindowComponentLayout::Compose(
                    AknLayoutScalable_Avkon::navi_navi_pane(),
                    AknLayoutScalable_Avkon::navi_navi_icon_text_pane() );
        }

    TRect parent( Rect() );
    TAknLayoutRect imageLayoutRect;
    imageLayoutRect.LayoutRect( parent, layout );
    TRect imageRect( imageLayoutRect.Rect() );

    image->SetRect( imageRect );

    image->SetPictureOwnedExternally( ETrue );
    image->SetPicture( aBitmap, aMaskBitmap );
    CleanupStack::Pop( image );

    CAknNavigationDecorator* decoratedImage =
        CAknNavigationDecorator::NewL( this,
                                       image,
                                       CAknNavigationDecorator::ENaviImage );

    CleanupStack::PushL( decoratedImage );
    decoratedImage->SetContainerWindowL( *this );
    CleanupStack::Pop( decoratedImage );

    decoratedImage->MakeScrollButtonVisible( EFalse );

    // Ownership of aBitmap and aMaskBitmap is moved to decoratedImage object
    // after all leaving methods.
    image->SetPictureOwnedExternally( EFalse );
    return decoratedImage;
    }


// ----------------------------------------------------------------------------
// CAknNavigationControlContainer::CreateNavigationImageL
// Creates a decorated navigation image control to use in navi pane.
// ----------------------------------------------------------------------------
//
EXPORT_C CAknNavigationDecorator* CAknNavigationControlContainer::CreateNavigationImageL(
    TResourceReader& aReader )
    {
    CAknNavigationDecorator* decoratedLabel = NULL;

    HBufC* bitmapFile = aReader.ReadHBufCL(); // bmp filename
    TInt   bitmapId   = aReader.ReadInt16();  // bmp id
    TInt   maskId     = aReader.ReadInt16();  // bmp mask id

    if ( bitmapFile )
        {
        CleanupStack::PushL( bitmapFile );

        TFileName fileName( *bitmapFile );
        CompleteWithAppPath( fileName );

        if ( bitmapId != KErrNotFound )
            {
            CFbsBitmap* bitmap;

            if ( maskId != KErrNotFound )
                {
                CFbsBitmap* mask;
                AknIconUtils::CreateIconL( bitmap,
                                           mask,
                                           fileName,
                                           bitmapId,
                                           maskId );

                TAknLayoutRect rect;

                TAknWindowComponentLayout layout;
                if ( AknStatuspaneUtils::StaconPaneActive() )
                    {
                    layout = TAknWindowComponentLayout::Compose(
                                AknLayoutScalable_Avkon::navi_navi_pane(),
                                AknLayoutScalable_Avkon::navi_navi_tabs_pane() );
                    }
                else
                    {
                    layout = AknLayoutScalable_Avkon::navi_navi_tabs_pane();
                    }

                rect.LayoutRect( Rect(), layout );

                AknIconUtils::SetSize( bitmap, rect.Rect().Size() );

                decoratedLabel = CreateNavigationImageL( bitmap, mask );
                }
            else
                {
                bitmap = AknIconUtils::CreateIconL( fileName, bitmapId );
                TAknLayoutRect rect;

                TAknWindowComponentLayout layout;
                if ( AknStatuspaneUtils::StaconPaneActive() )
                    {
                    layout = TAknWindowComponentLayout::Compose(
                                AknLayoutScalable_Avkon::navi_navi_pane(),
                                AknLayoutScalable_Avkon::navi_navi_tabs_pane() );
                    }
                else
                    {
                    layout = AknLayoutScalable_Avkon::navi_navi_tabs_pane();
                    }

                rect.LayoutRect( Rect(), layout );
                AknIconUtils::SetSize( bitmap, rect.Rect().Size() );

                decoratedLabel = CreateNavigationImageL( bitmap );
                }
            }
        CleanupStack::PopAndDestroy( bitmapFile );
        }

    return decoratedLabel;
    }


// ----------------------------------------------------------------------------
// CAknNavigationControlContainer::CreateMessageLabelL
// Creates a decorated message label control to use in navi pane.
// ----------------------------------------------------------------------------
//
EXPORT_C CAknNavigationDecorator* CAknNavigationControlContainer::CreateMessageLabelL(
    const TDesC& aText )
    {
    CAknNavigationDecorator* decoratedLabel = CreateNavigationLabelL( aText );

    CAknNaviLabel* label = STATIC_CAST( CAknNaviLabel*,
                                        decoratedLabel->DecoratedControl() );

    label->SetNaviLabelType( CAknNaviLabel::EHintText );

    decoratedLabel->SetControlType( CAknNavigationDecorator::EHintText );

    return decoratedLabel;
    }


// ----------------------------------------------------------------------------
// CAknNavigationControlContainer::CreateMessageLabelL
// Creates a decorated message label control to use in navi pane.
// ----------------------------------------------------------------------------
//
EXPORT_C CAknNavigationDecorator* CAknNavigationControlContainer::CreateMessageLabelL(
    TResourceReader& aReader )
    {
    HBufC* txt = aReader.ReadHBufCL();  // message text
    CAknNavigationDecorator* decoratedLabel = NULL;
    if ( txt )
        {
        CleanupStack::PushL( txt );
        decoratedLabel = CreateMessageLabelL( *txt );
        CleanupStack::PopAndDestroy( txt );
        }
    else
        {
        decoratedLabel = CreateMessageLabelL( KNullDesC );
        }
    return decoratedLabel;
    }


// ----------------------------------------------------------------------------
// CAknNavigationControlContainer::CreateVolumeIndicatorL
// Deprecated, creates a volume popup control.
// ----------------------------------------------------------------------------
//
EXPORT_C CAknNavigationDecorator* CAknNavigationControlContainer::CreateVolumeIndicatorL(
    TInt aResourceId )
    {
    // Navi pane volume control is no longer supported from release 5.0 on,
    // but to maintain BC a volume popup control is launched instead.
    CAknVolumePopup* volumeIndicator =
        CAknVolumePopup::ConstructFromResourceL( aResourceId );
    
    CleanupStack::PushL( volumeIndicator );
    
    CAknNavigationDecorator* decoratedVolumeIndicator =
        CAknNavigationDecorator::NewL( this,
                                       volumeIndicator,
                                       CAknNavigationDecorator::ENaviVolume );
    
    // Set the volume popup's position.    
    volumeIndicator->SetRect( VolumePopupRect() );
                                       
    CleanupStack::Pop( volumeIndicator );

    return decoratedVolumeIndicator;
    }


// ----------------------------------------------------------------------------
// CAknNavigationControlContainer::CreateEditorIndicatorContainerL
// Creates a decorated editor indicator container control to use in navi pane.
// ----------------------------------------------------------------------------
//
EXPORT_C CAknNavigationDecorator* CAknNavigationControlContainer::CreateEditorIndicatorContainerL()
    {
    CAknIndicatorContainer* editorIndicatorContainer =
        new (ELeave) CAknIndicatorContainer(
            CAknIndicatorContainer::ENaviPaneEditorIndicators );

    CleanupStack::PushL( editorIndicatorContainer );

    editorIndicatorContainer->SetContainerWindowL( *this );

    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC( reader,
                                     R_AVKON_NAVI_PANE_EDITOR_INDICATORS );
    editorIndicatorContainer->ConstructFromResourceL( reader );

    // Update the signal icon state from status pane layout in small status pane
    // to keep those two in sync.
    if ( iStatusPane &&
         ( iStatusPane->CurrentLayoutResId() ==
            R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE ||
           iStatusPane->CurrentLayoutResId() ==
            R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE_MIRRORED ) )
        {
        editorIndicatorContainer->SetIndicatorState(
            TUid::Uid( EAknNaviPaneEditorIndicatorGprs ),
            EAknIndicatorStateOn,
            EFalse );
        }

    CleanupStack::PopAndDestroy();  // resource reader

    CleanupStack::Pop( editorIndicatorContainer ); // editorIndicatorContainer

    CAknNavigationDecorator* decoratedEditorIndicatorContainer =
        CAknNavigationDecorator::NewL( this,
                                       editorIndicatorContainer,
                                       CAknNavigationDecorator::EEditorIndicator );

    CleanupStack::PushL( decoratedEditorIndicatorContainer );

    decoratedEditorIndicatorContainer->SetContainerWindowL( *this );
    CleanupStack::Pop( decoratedEditorIndicatorContainer );

    decoratedEditorIndicatorContainer->MakeScrollButtonVisible( EFalse );

    return decoratedEditorIndicatorContainer;
    }


// ----------------------------------------------------------------------------
// CAknNavigationControlContainer::PushDefaultL
// Pushes the default (empty) navi pane control to the navi pane control stack.
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknNavigationControlContainer::PushDefaultL(
    TBool aAllowDuplicates )
    {
    if ( !aAllowDuplicates )
        {
        const TInt last = iNaviPaneControls->Count() - 1;
        for ( TInt ii = last; ii >= 0; ii-- )
            {
            if ( !( iNaviPaneControls->At( ii ) ) )
                {
                iNaviPaneControls->Delete( ii );
                break; // Same reference only once in the stack
                }
            }
        }
    const TInt lastAfterDelete = iNaviPaneControls->Count() - 1;

    // This is required in case the empty navi pane is pushed to the stack, and
    // the previous navi pane has a direction indication animation ongoing,
    // in which case the arrow indicator would remain visible on the
    // empty navi pane.
    //
    // Also, if the previous navi pane control is volume control, which
    // now launches a volume popup, and the popup is visible, then it's closed.
    //
    CAknNavigationDecorator* naviControl = NULL;
    for ( TInt jj = lastAfterDelete; jj >= 0; jj-- )
        {
        naviControl = iNaviPaneControls->At( jj );
        if ( naviControl )
            {
            naviControl->CancelTimer();
            
            if ( naviControl->ControlType() ==
                    CAknNavigationDecorator::ENaviVolume )
                {
                CAknVolumePopup* volumePopup =
                    static_cast<CAknVolumePopup*> (
                        naviControl->iDecoratedControl );
                if ( volumePopup )
                    {
                    volumePopup->CloseVolumePopup();
                    }
                }
            }
        }

    if (lastAfterDelete >= 0 &&
        IsFepOwnedEditorIndicatorControl( iNaviPaneControls->At(lastAfterDelete) ))
        {
        // Insert after FEP owned editor indicator object.
        iNaviPaneControls->InsertL(lastAfterDelete, NULL);
        }
    else
        {
        iNaviPaneControls->AppendL( NULL );
        DrawDeferred();
        }

    // Notify contextpane and signalpane that possibly the naviwipe drawing has
    // been changed.
    TRAP_IGNORE( NotifyNaviWipeStatusL() );
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::PushL
// Pushes a decorated navi pane control to the navi pane control stack.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknNavigationControlContainer::PushL(
    CAknNavigationDecorator& aNaviPaneControl )
    {
    TBool isLandscape( Layout_Meta_Data::IsLandscapeOrientation() );
    
    if ( AknStatuspaneUtils::FlatLayoutActive() &&
         iExtension->iPreferredNaviDecoratorLayoutStyle )
        {
        // In flat status pane layout it's possible to use the narrow
        // navi pane variant.
        CAknNavigationDecorator::TAknNaviControlLayoutStyle layoutStyle;
        if ( iExtension->iPreferredNaviDecoratorLayoutStyle ==
                CAknNavigationDecorator::ENaviControlLayoutNarrow )
            {
            // Narrow layout set as preferred, use it.
            layoutStyle = CAknNavigationDecorator::ENaviControlLayoutNarrow;
            }
        else
            {
            // Otherwise use the normal layout.
            layoutStyle = CAknNavigationDecorator::ENaviControlLayoutNormal;
            }

        // Check if the layout style is supported in the current layout.
        if ( aNaviPaneControl.NaviControlLayoutStyleSupported( layoutStyle ) )
            {
            aNaviPaneControl.SetNaviControlLayoutStyle( layoutStyle );
            
            if ( isLandscape )
                {
                // In landscape flat status pane layout use the automatic
                // navi pane layout mode, so that the navi pane gives
                // space to the title pane when necessary.
                aNaviPaneControl.SetNaviControlLayoutMode(
                    CAknNavigationDecorator::ENaviControlLayoutModeAutomatic );
                }
            else
                {
                // In portrait use the forced mode.
                aNaviPaneControl.SetNaviControlLayoutMode(
                    CAknNavigationDecorator::ENaviControlLayoutModeForced );
                }
            }
        }
    else if ( iExtension->iPreferredNaviDecoratorLayoutStyle ==
                  CAknNavigationDecorator::ENaviControlLayoutWide ||
              ( AknStatuspaneUtils::UsualLayoutActive() &&
                !isLandscape &&
                ( aNaviPaneControl.ControlType() !=
                      CAknNavigationDecorator::ETabGroup ||
                   AknLayoutUtils::PenEnabled() ) ) )
        {
        // In usual portrait status pane layout use the wide navi pane
        // layout. Exception is tab group control in non-touch devices,
        // for which the normal layout is used.
        if ( aNaviPaneControl.NaviControlLayoutStyleSupported(
                CAknNavigationDecorator::ENaviControlLayoutWide ) )
            {
            aNaviPaneControl.SetNaviControlLayoutStyle(
                CAknNavigationDecorator::ENaviControlLayoutWide );
            aNaviPaneControl.SetNaviControlLayoutMode(
                CAknNavigationDecorator::ENaviControlLayoutModeForced );
            }
        }
    else
        {
        // Otherwise use the normal layout.
        aNaviPaneControl.SetNaviControlLayoutStyle(
            CAknNavigationDecorator::ENaviControlLayoutNormal );
        aNaviPaneControl.SetNaviControlLayoutMode(
            CAknNavigationDecorator::ENaviControlLayoutModeAutomatic );
        }

    TRect rect( Rect() );
    aNaviPaneControl.SetRect( rect );

    // If the object already exists in the stack, delete it first.
    const TInt last = iNaviPaneControls->Count() - 1;
    for ( TInt ii = last; ii >= 0; ii-- )
        {
        if ( iNaviPaneControls->At(ii) == &aNaviPaneControl )
            {
            iNaviPaneControls->Delete(ii);
            break; // Same reference only once in the stack
            }
        }

    // If the top most object is an editor indicator control, insert
    // new object after it. New object is put to the top otherwise.
    const TInt lastAfterDelete = iNaviPaneControls->Count() - 1;

    // This is required in case the empty navi pane is pushed to the stack, and
    // the previous navi pane has a direction indication animation ongoing,
    // in which case the arrow indicator would remain visible on the
    // empty navi pane.
    //
    // Also, if the previous navi pane control is volume control, which
    // now launches a volume popup, and the popup is visible, then it's closed.
    //
    CAknNavigationDecorator* naviControl = NULL;
    for ( TInt jj = lastAfterDelete; jj >= 0; jj-- )
        {
        naviControl = iNaviPaneControls->At( jj );
        if ( naviControl )
            {
            naviControl->CancelTimer();
            
            if ( naviControl->ControlType() ==
                    CAknNavigationDecorator::ENaviVolume )
                {
                CAknVolumePopup* volumePopup =
                    static_cast<CAknVolumePopup*> (
                        naviControl->iDecoratedControl );
                if ( volumePopup )
                    {
                    volumePopup->CloseVolumePopup();
                    // Tell the volume control that it's no longer the topmost
                    // control on the navi stack.
                    static_cast<CAknVolumeControl*>(
                        naviControl->DecoratedControl() )->HandleNaviStackChange( EFalse );
                    }
                }
            }
        }

    if ( lastAfterDelete >= 0 &&
         IsFepOwnedEditorIndicatorControl(
            iNaviPaneControls->At(lastAfterDelete) ) )
        {
        HandleVisibilityOfNonFepOwnedIndicatorControl( &aNaviPaneControl,
                                                       EFalse );
        // Insert new object after after FEP owned editor indicator object
        iNaviPaneControls->InsertL( lastAfterDelete, &aNaviPaneControl );

        // Tell the navi pane control that it is in this status pane
        aNaviPaneControl.SetNaviStack( this );
        aNaviPaneControl.ActivateL();

        if ( rect != Rect() )
            {
            aNaviPaneControl.SetRect( Rect() );
            }
        }
    else
        {
        if ( lastAfterDelete >= 0 &&
             IsFepOwnedEditorIndicatorControl( &aNaviPaneControl ) )
            {
            HandleVisibilityOfNonFepOwnedIndicatorControl(
                iNaviPaneControls->At( lastAfterDelete ), EFalse );
            }
        // Put new object to the top
        iNaviPaneControls->AppendL( &aNaviPaneControl );

        // Tell the navi pane control that it is in this status pane
        aNaviPaneControl.SetNaviStack( this );
        
        if ( aNaviPaneControl.ControlType() != CAknNavigationDecorator::ENaviVolume )
            {
            aNaviPaneControl.ActivateL();

            if ( rect != Rect() )
                {
                aNaviPaneControl.SetRect( Rect() );
                }
                
            DrawDeferred();
            }
         else
            {
            // If the navi pane control is of the ENaviVolume type, a volume popup
            // is shown instead.
            CAknVolumeControl* volumeControl =
                static_cast<CAknVolumeControl*> ( aNaviPaneControl.DecoratedControl() );
            
            // Check also that we are on the foreground.
            if ( volumeControl &&
                 iExtension &&
                 iExtension->iForegroundObserver &&
                 iExtension->iForegroundObserver->HasForegroundGained() )
                {
                // Tell the volume control that it's the topmost
                // control on the navi stack.
                volumeControl->HandleNaviStackChange( ETrue );
                }
            }
        }

    // Notify contextpane and signalpane that possibly the naviwipe drawing has
    // been changed.
    TRAP_IGNORE( NotifyNaviWipeStatusL() );
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::Pop
// Pops the topmost control from the navi stack.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknNavigationControlContainer::Pop()
    {
    const TInt last = iNaviPaneControls->Count() - 1;
    if ( last >= 0 )
        {
        if ( IsFepOwnedEditorIndicatorControl( iNaviPaneControls->At(last) ) )
            {
            if ( last > 0)
                {
                // Tell the control that it is removed from this status pane
                CAknNavigationDecorator* controlToDelete =
                    iNaviPaneControls->At( last - 1 );
                if ( controlToDelete )
                    {
                    controlToDelete->SetNaviStack( NULL );
                    }

                iNaviPaneControls->Delete( last - 1 );
                DrawDeferred();
                }
            }
        else
            {
            // Tell the control that it is removed from this status pane
            CAknNavigationDecorator* controlToDelete =
                iNaviPaneControls->At( last );

            if ( controlToDelete )
                {
                if ( controlToDelete->ControlType() ==
                    CAknNavigationDecorator::ENaviVolume )
                    {
                    CAknVolumePopup* volumePopup =
                        static_cast<CAknVolumePopup*> ( controlToDelete->iDecoratedControl );

                    if ( volumePopup )
                        {
                        // Tell the volume control that it's no longer the topmost
                        // control on the navi stack.
                        static_cast<CAknVolumeControl*>(
                            controlToDelete->DecoratedControl() )->HandleNaviStackChange( EFalse );
                        volumePopup->CloseVolumePopup();
                        }
                    }
                
                controlToDelete->SetNaviStack( NULL );
                }

            iNaviPaneControls->Delete( last );
            DrawDeferred();
            }
        }
    
    // Volume control must be informed if it's the topmost control in the navi
    // pane stack after popping and we have the foreground.
    TInt lastAfterDelete = iNaviPaneControls->Count() - 1;
    if ( lastAfterDelete >= 0 )
        {
        CAknNavigationDecorator* naviControl = NULL;

        naviControl = iNaviPaneControls->At( lastAfterDelete );
        if ( naviControl &&
             iExtension &&
             iExtension->iForegroundObserver &&
             iExtension->iForegroundObserver->HasForegroundGained() )
            {
            if ( naviControl->ControlType() ==
                    CAknNavigationDecorator::ENaviVolume )
                {
                CAknVolumePopup* volumePopup =
                    static_cast<CAknVolumePopup*> (
                        naviControl->iDecoratedControl );

                if ( volumePopup )
                    {
                    // Tell the volume control that it's the topmost
                    // control on the navi stack.
                    static_cast<CAknVolumeControl*>(
                        naviControl->DecoratedControl() )->HandleNaviStackChange( ETrue );
                    }
                }
            else
                {
                // Initialize the layout timer if necessary.
                naviControl->SetNaviControlLayoutMode(
                    naviControl->NaviControlLayoutMode() );
                }
            }
        }
        
    // Notify contextpane and signalpane that possibly the naviwipe drawing has
    // been changed.
    TRAP_IGNORE( NotifyNaviWipeStatusL() );
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::Pop
// Pops a navi pane control from the navi stack.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknNavigationControlContainer::Pop(
    CAknNavigationDecorator* aControl )
    {
    const TInt last = iNaviPaneControls->Count() - 1;
    TInt ii = 0;
    for ( ii = last; ii >= 0; ii-- )
        {
        if ( iNaviPaneControls->At(ii) == aControl )
            {
            // Tell the control that it is not in this navi pane now.
            if ( aControl )
                {
                if ( aControl->ControlType() == CAknNavigationDecorator::ENaviVolume )
                    {
                    CAknVolumePopup* volumePopup =
                        static_cast<CAknVolumePopup*> ( aControl->iDecoratedControl );

                    if ( volumePopup )
                        {
                        static_cast<CAknVolumeControl*>(
                            aControl->DecoratedControl() )->HandleNaviStackChange( EFalse );
                        volumePopup->CloseVolumePopup();
                        }
                    }
                
                aControl->SetNaviStack( NULL );
                }

            iNaviPaneControls->Delete(ii);
            break; // Same reference only once in the stack
            }
        }

    if ( ii == last )  // Drawn only if topmost control was popped
        {
        const TInt lastAfterDelete = iNaviPaneControls->Count() - 1;
        if ( lastAfterDelete >= 0 )
            {
            HandleVisibilityOfNonFepOwnedIndicatorControl(
                iNaviPaneControls->At( lastAfterDelete ), ETrue );
                
            CAknNavigationDecorator* naviControl = NULL;

            naviControl = iNaviPaneControls->At( lastAfterDelete );
            if ( naviControl &&
                 iExtension &&
                 iExtension->iForegroundObserver &&
                 iExtension->iForegroundObserver->HasForegroundGained() )
                {
                // Volume control must be informed if it's the topmost control
                // in the navi pane stack after popping
                // and we have the foreground.
                if ( naviControl->ControlType() ==
                        CAknNavigationDecorator::ENaviVolume )
                    {
                    CAknVolumePopup* volumePopup =
                        static_cast<CAknVolumePopup*> (
                            naviControl->iDecoratedControl );

                    if ( volumePopup )
                        {
                        static_cast<CAknVolumeControl*>(
                            naviControl->DecoratedControl() )->HandleNaviStackChange( ETrue );
                        }
                    }
                else
                    {
                    // Initialize the layout timer if necessary.
                    naviControl->SetNaviControlLayoutMode(
                        naviControl->NaviControlLayoutMode() );
                    }
                }
            }
        DrawDeferred();
        }
        
    // Notify contextpane and signalpane that possibly the naviwipe drawing has
    // been changed.
    TRAP_IGNORE( NotifyNaviWipeStatusL() );
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::Top
// Returns the topmost control on the navi stack.
// ---------------------------------------------------------------------------
//
EXPORT_C CAknNavigationDecorator* CAknNavigationControlContainer::Top()
    {
    return Top( ETrue );
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::Top
// Returns the topmost control on the navi stack.
// ---------------------------------------------------------------------------
//
EXPORT_C CAknNavigationDecorator* CAknNavigationControlContainer::Top(
    TBool aIgnoreFepEditorIndicator ) const
    {
    CAknNavigationDecorator* topMostControl = NULL;

    const TInt last = iNaviPaneControls->Count() - 1;
    if ( last >= 0 )
        {
        topMostControl = iNaviPaneControls->At( last );
        if ( IsFepOwnedEditorIndicatorControl( topMostControl ) &&
             aIgnoreFepEditorIndicator )
            {
            if ( last > 0)
                {
                topMostControl = iNaviPaneControls->At( last - 1 );
                }
            }
        }

    return topMostControl;
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::ReplaceL
// Replaces an existing navi pane control with another one.
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CAknNavigationControlContainer::ReplaceL(
    CAknNavigationDecorator& aToBeReplaced,
    CAknNavigationDecorator& aReplacement )
    {
    const TInt last = iNaviPaneControls->Count() - 1;
    for ( TInt ii = last; ii >= 0; ii-- )
        {
        if ( iNaviPaneControls->At( ii ) == &aToBeReplaced )
            {
            TBool redrawNeeded = EFalse;
            aReplacement.SetRect( Rect() );
            
            // If the replaced control is volume control, then
            // ensure that the parent control is not set and the
            // volume control must be informed about the
            // navi stack change.
            if ( aToBeReplaced.ControlType() ==
                    CAknNavigationDecorator::ENaviVolume )
                {
                CAknVolumePopup* volumePopup =
                    static_cast<CAknVolumePopup*> (
                        aToBeReplaced.iDecoratedControl );

                if ( volumePopup )
                    {
                    volumePopup->CloseVolumePopup();
                    }

                static_cast<CAknVolumeControl*>(
                    aToBeReplaced.DecoratedControl() )->HandleNaviStackChange( EFalse );
                }
            
            aToBeReplaced.SetNaviStack( NULL );
            iNaviPaneControls->Delete(ii);
            iNaviPaneControls->InsertL( ii, &aReplacement);
            aReplacement.SetNaviStack( this );
            
            // If the replacing control is volume control, then
            // ensure that the parent control is not set and the
            // volume control must be informed about the
            // navi stack change.
            if ( aReplacement.ControlType() ==
                    CAknNavigationDecorator::ENaviVolume )
                {
                CAknVolumePopup* volumePopup =
                    static_cast<CAknVolumePopup*> (
                        aReplacement.iDecoratedControl );

                if ( volumePopup )
                    {
                    volumePopup->CloseVolumePopup();
                    }
                    
                static_cast<CAknVolumeControl*>(
                    aReplacement.DecoratedControl() )->HandleNaviStackChange( ETrue );
                }
            else
                {
                // Must not to do this for volume popup.
                aReplacement.ActivateL();
                }

            if ( ii == last )
                {
                redrawNeeded = ETrue; // Top item replaced, redraw is needed.
                }

            // Delete second copy of aReplacement if it existed on the
            // stack before ReplaceL call.
            for (TInt jj = last; jj >= 0; jj--)
                {
                if ( jj != ii && iNaviPaneControls->At(jj) == &aReplacement )
                    {
                    iNaviPaneControls->Delete(jj);
                    if ( jj == last )
                        {
                        redrawNeeded = ETrue; // Top item deleted, redraw is needed.
                        }
                    break; // Same reference only once in the stack
                    }
                }

            if ( redrawNeeded )
                {
                // Initialize the layout timer if necessary.
                aReplacement.SetNaviControlLayoutMode(
                    aReplacement.NaviControlLayoutMode() );
                    
                // Redraw if top most item was replaced.
                DrawDeferred();
                }
            return KErrNone;
            }
        }
    return KErrNotFound;
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::ResourceDecorator
// ---------------------------------------------------------------------------
//
EXPORT_C CAknNavigationDecorator* CAknNavigationControlContainer::ResourceDecorator()
    {
    CAknNavigationDecorator* naviDecorator = iNaviDecoratorFromResource;

    // The ownership of the object is moved to the application.
    iNaviDecoratorFromResource = NULL;
    return naviDecorator;
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::NaviArrowBitmap
// Gets the bitmap for the left or right navigation arrow.
// ---------------------------------------------------------------------------
//
CFbsBitmap& CAknNavigationControlContainer::NaviArrowBitmap( TInt aId )
    {
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    TAknsItemID iid = KAknsIIDNone;
    if ( aId < 2 )
        {
        iid = KAknsIIDQgnIndiNaviArrowLeft;
        }
    else
        {
        iid = KAknsIIDQgnIndiNaviArrowRight;
        }

    CFbsBitmap* skinBitmap = NULL;
    CFbsBitmap* skinMask   = NULL;
    AknsUtils::GetCachedMaskedBitmap( skin, iid, skinBitmap, skinMask );

    TBool narrowLayoutInUse( EFalse );
    CAknNavigationDecorator* topControl = Top( ETrue );
    if ( topControl &&
         topControl->NaviControlLayoutStyle() == 
            CAknNavigationDecorator::ENaviControlLayoutNarrow )
        {
        narrowLayoutInUse = ETrue;
        }

    TSize arrowSize( CAknNavigationDecorator::NaviArrowRect(
        CAknNavigationDecorator::ELeftButton, narrowLayoutInUse ).Size() );

    if ( skinBitmap )
        {
        AknIconUtils::SetSize( skinBitmap, arrowSize );
        }
    if ( skinMask )
        {
        AknIconUtils::SetSize( skinMask, arrowSize );
        }
    
    // Set also the default navi arrow bitmap to correct size here.
    AknIconUtils::SetSize( iNaviArrowBitmap[aId], arrowSize );

    if( ( aId & 1 ) && skinMask ) // If aId is odd and mask exists
        {
        return *skinMask;
        }
    else if( skinBitmap )
        {
        return *skinBitmap;
        }

    return *iNaviArrowBitmap[aId];
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::SizeChanged
// Handles size change events.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknNavigationControlContainer::SizeChanged()
    {
    TRect rect( Rect() );

    // No fading if staconpane is active.
    SetContainerWindowNonFading( AknStatuspaneUtils::StaconPaneActive() );

    TBool narrowLayoutInUse( EFalse );
    CAknNavigationDecorator* topControl = Top( ETrue );
    if ( topControl &&
         topControl->NaviControlLayoutStyle() == 
            CAknNavigationDecorator::ENaviControlLayoutNarrow )
        {
        narrowLayoutInUse = ETrue;
        }

    TSize naviArrowSize(
        CAknNavigationDecorator::NaviArrowRect(
            CAknNavigationDecorator::ELeftButton, narrowLayoutInUse ).Size() );

    AknIconUtils::SetSize( iNaviArrowBitmap[ 0 ], naviArrowSize );
    AknIconUtils::SetSize( iNaviArrowBitmap[ 2 ], naviArrowSize );

    const TInt last = iNaviPaneControls->Count() - 1;

    if ( last >= 0 && iNaviPaneControls->At( last ) )
        {
        if ( iNaviPaneControls->At( last )->ControlType() ==
                 CAknNavigationDecorator::ENaviVolume )
            {
            // Volume popup's position must be set here.
            iNaviPaneControls->At( last )->iDecoratedControl->SetRect(
                VolumePopupRect() );
            if( last - 1 >= 0 )
            	{
            		iNaviPaneControls->At( last - 1 )->SetRect( rect );
            	}
            }
        else
            {
            iNaviPaneControls->At( last )->SetRect( rect );
            }
        }

    AknsUtils::RegisterControlPosition( this );

    // Notify contextpane and signalpane that possibly the naviwipe drawing has
    // been changed.
    TRAP_IGNORE( NotifyNaviWipeStatusL() );
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::HandleResourceChange
// Handles resource change events.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknNavigationControlContainer::HandleResourceChange( TInt aType )
    {
    // CCoeControl::HandleResourceChange forwards events only to topmost items.
    // We try this to forward the event and hope that it does not
    // break too much things.
    if ( aType == KEikDynamicLayoutVariantSwitch ||
         aType == KEikColorResourceChange ||
         aType == KAknsMessageSkinChange )
        {
        const TInt last = iNaviPaneControls->Count() - 1;
        TInt ii = 0;
        CAknNavigationDecorator* control;
        for ( ii = last; ii >= 0; ii-- )
            {
            control = iNaviPaneControls->At( ii );
            if ( control )
                {
                if ( control->ControlType() ==
                         CAknNavigationDecorator::ENaviVolume )
                    {
                    // Volume popup's position must be set here.
                    control->iDecoratedControl->SetPosition(
                        VolumePopupRect().iTl );
                    }
                    
                control->HandleResourceChange( aType );
                }
            }
        }
    else
        {
        CCoeControl::HandleResourceChange( aType ) ;
        }

    if ( aType == KEikColorResourceChange ||
         aType == KEikDynamicLayoutVariantSwitch ||
         aType == KAknsMessageSkinChange )
        {
        TInt colorScheme = ColorScheme();
        if ( colorScheme != iExtension->iCurrentColorScheme ||
             aType == KEikDynamicLayoutVariantSwitch ||
             aType == KAknsMessageSkinChange )
            {
            iExtension->iCurrentColorScheme = colorScheme;

            // updating color bitmap
            TRAP_IGNORE( LoadNaviColorBitmapL() );
            }
        DrawDeferred();
        }
    else if ( aType == KEikMessageFadeAllWindows )
        {
        // Close the volume popup if navi pane is faded.
        CAknNavigationDecorator* topControl = Top();
    
        if ( topControl &&
             topControl->ControlType() == CAknNavigationDecorator::ENaviVolume )
            {
            CAknVolumePopup* volumePopup =
                static_cast<CAknVolumePopup*> ( topControl->iDecoratedControl );

            if ( volumePopup )
                {
                volumePopup->CloseVolumePopup();
                }
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::CountComponentControls
// Report number of component controls.
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CAknNavigationControlContainer::CountComponentControls() const
    {
    const TInt last = iNaviPaneControls->Count() - 1;
    if ( last < 0 || !iNaviPaneControls->At( last ) )
        {
        return 1;
        }

    return 2;
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::ComponentControl
// Return a contained control.
// ---------------------------------------------------------------------------
//
EXPORT_C CCoeControl* CAknNavigationControlContainer::ComponentControl(
    TInt aIndex ) const
    {
    CCoeControl* control = NULL;
    
    if ( aIndex == 0 )
        {
        control = iExtension->iForegroundObserver;
        }
    else if ( aIndex == 1 )
        {
        // Return top item from the navi stack.
        // If the top is Volume Control, Return the one next to the top
        CAknNavigationDecorator *naviDecorator = iNaviPaneControls->At( iNaviPaneControls->Count() - 1 );
        if ( naviDecorator->ControlType() == CAknNavigationDecorator::ENaviVolume )
            {
            if ( iNaviPaneControls->Count() - 2 >= 0 )\
                {
                control = iNaviPaneControls->At( iNaviPaneControls->Count() - 2 );
                }
            }
        
        if ( control == NULL)
            {
            control = naviDecorator;
            }
        }
    
    return control;
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::HandleControlEventL
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknNavigationControlContainer::HandleControlEventL(
    CCoeControl* aControl,
    TCoeEvent aEventType )
    {
    switch ( aEventType )
        {
        case EEventStateChanged:
            {
            const TInt last = iNaviPaneControls->Count() - 1;
            // Drawn only if the object that sent the event is
            // topmost at the stack
            if ( last > KErrNotFound &&
                 aControl == iNaviPaneControls->At( last ) )
                {
                DrawDeferred();
                }
            }
            break;
        default:
            break;
        }
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::Draw
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknNavigationControlContainer::Draw(
    const TRect& /*aRect*/ ) const
    {
    if ( iExtension->iIsActiveIdle )
        {
        return;
        }

    CWindowGc& gc = SystemGc();

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    if( !skin )
        {
        // We are in the middle of AppUi destructor, abort to reduce flicker.
        return;
        }

    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );

    TRect rect( Rect() );

    //
    // Navi pane is located in COMBINED CONTROL/STATUSPANE
    //
    if ( AknStatuspaneUtils::StaconPaneActive() )
        {
        //
        // - Navi wipe is never used
        // - No offset in right, left or top
        //
        if( !AknsDrawUtils::Background( skin, cc, this, gc, rect ) )
            {
            gc.SetPenStyle( CGraphicsContext::ENullPen );
            gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
            gc.SetBrushColor(
                AKN_LAF_COLOR( KStatusPaneBackgroundGraphicsColorUsual ) );

            gc.DrawRect( rect );
            }
        return;
        }
    //
    // Navi pane is located in SMALL STATUSPANE
    //
    else if ( AknStatuspaneUtils::SmallLayoutActive() )
        {
        // This component is drawn differently in small statuspane.
        //
        // - Navi wipe is never used
        // - No offset in right, left or top
        //
        gc.SetPenStyle( CGraphicsContext::ENullPen );
        gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
        gc.SetBrushColor(
            AKN_LAF_COLOR( KStatusPaneBackgroundGraphicsColorUsual ) );

        if( !AknsDrawUtils::Background( skin, cc, this, gc, rect ) )
            {
            gc.DrawRect( rect );
            }
        return;
        }
    //
    // Navi pane is located in FLAT STATUSPANE
    //
    else if ( AknStatuspaneUtils::FlatLayoutActive() )
        {
        //
        // - Navi wipe is never used
        // - No offset in right, left or top
        //
        if( !AknsDrawUtils::Background( skin, cc, this, gc, rect ) )
            {
            gc.SetPenStyle( CGraphicsContext::ENullPen );
            gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
            gc.SetBrushColor(
                AKN_LAF_COLOR( KStatusPaneBackgroundGraphicsColorUsual ) );
            gc.DrawRect( rect );
            }

        if ( iStatusPane && !AknLayoutUtils::PenEnabled() )
            {
            // Draw title text or image that overlaps to navipane area.
            CCoeControl* navicontrol      = NULL;
            CCoeControl* titlecontrol     = NULL;
            CCoeControl* titlepaneControl = NULL;
        
            TRAP_IGNORE( navicontrol =
                            iStatusPane->ContainerControlL(
                                TUid::Uid( EEikStatusPaneUidNavi ) ) );
            TRAP_IGNORE( titlecontrol =
                            iStatusPane->ContainerControlL(
                                TUid::Uid( EEikStatusPaneUidTitle ) ) );
            TRAP_IGNORE( titlepaneControl =
                            iStatusPane->ControlL(
                                TUid::Uid( EEikStatusPaneUidTitle ) ) );

            if ( navicontrol && titlecontrol && titlepaneControl )
                {
                TRect naviRect(
                    navicontrol->Position().iX,
                    navicontrol->Position().iY,
                    navicontrol->Position().iX + navicontrol->Size().iWidth,
                    navicontrol->Position().iY + navicontrol->Size().iHeight );

                TRect titleRect(
                    titlecontrol->Position().iX,
                    titlecontrol->Position().iY,
                    titlecontrol->Position().iX + titlecontrol->Size().iWidth,
                    titlecontrol->Position().iY + titlecontrol->Size().iHeight );

                TInt offset = titleRect.iTl.iX;

                titleRect.Intersection( naviRect );
                TRect intersection = titleRect;
                intersection.iTl.iX -= offset;
                intersection.iBr.iX -= offset;

                CAknTitlePane* titlePane =
                    dynamic_cast<CAknTitlePane*> ( titlepaneControl );

                CAknNavigationDecorator* topControl = Top( ETrue );

                if ( titlePane && topControl &&
                     topControl->NaviControlLayoutStyle() == 
                        CAknNavigationDecorator::ENaviControlLayoutNarrow )
                    {
                    CEikImage* titleImage = titlePane->TitleImage();

                    CAknTitlePaneLabel* titleLabel =
                        static_cast<CAknTitlePaneLabel*>(
                            titlePane->TextLabel() );
                    
                    if ( titleImage )
                        {
                        if ( titleImage->Mask() )
                            {
                            gc.BitBltMasked( TPoint( 0, 0 ),
                                             titleImage->Bitmap(),
                                             intersection,
                                             titleImage->Mask(),
                                             ETrue );
                            }
                        else
                            {
                            gc.BitBlt( TPoint( 0, 0 ),
                                       titleImage->Bitmap(),
                                       intersection );
                            }
                        }
                    else if ( titleLabel &&
                              titleLabel->TextAsBitmap() &&
                              titleLabel->TextAsMask() )
                        {
                        gc.BitBltMasked( TPoint( 0, 0 ),
                                         titleLabel->TextAsBitmap(),
                                         intersection,
                                         titleLabel->TextAsMask(),
                                         ETrue );
                        }
                    }
                }
            }

        return;
        }
    //
    // Navi pane is located in NORMAL STATUSPANE
    //
    else
        {
        TBool naviWipeUsed = NaviWipeUsed();

        TBool skinnedNaviWipeDrawn  = EFalse;
        TBool skinnedNaviSolidDrawn = EFalse;
        TBool defaultNaviWipeDrawn  = EFalse;
        TBool defaultNaviSolidDrawn = EFalse;

        // If naviwipe is to be used, try first skinned draw...
        if ( naviWipeUsed )
            {
            skinnedNaviWipeDrawn = DrawSkinnedNaviWipe( gc, rect, skin, cc );
            }

        // If naviwipe is to be used and skinned draw failed,
        // draw default wipe draw...
        if ( naviWipeUsed && !skinnedNaviWipeDrawn )
            {
            defaultNaviWipeDrawn = DrawDefaultNaviWipe( gc, rect );
            }

        // If naviwipe is not to be drawn or the nawiwipe draws has failed for
        // some reason then draw solid. Try skinned solid draw first...
        if ( !skinnedNaviWipeDrawn && !defaultNaviWipeDrawn )
            {
            skinnedNaviSolidDrawn = DrawSkinnedNaviSolid( gc, rect, skin, cc );
            }

        // If not any above is the case, then draw the default solid here.
        if ( !skinnedNaviWipeDrawn &&
             !defaultNaviWipeDrawn &&
             !skinnedNaviSolidDrawn &&
             !defaultNaviSolidDrawn )
            {
            defaultNaviSolidDrawn = DrawDefaultNaviSolid( gc, rect );
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::HandlePointerEventL
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknNavigationControlContainer::HandlePointerEventL(
    const TPointerEvent& aPointerEvent )
    {
    CAknControl::HandlePointerEventL( aPointerEvent );
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::ExtensionInterface
// ---------------------------------------------------------------------------
//
EXPORT_C void* CAknNavigationControlContainer::ExtensionInterface(
    TUid /*aInterface*/ )
    {
    return NULL;
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::ColorScheme
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CAknNavigationControlContainer::ColorScheme()
    {
    TInt colorScheme = 0;

    CRepository* repository = NULL;
    TRAPD( ret, repository = CRepository::NewL( KCRUidPersonalisation ) );
    if ( ret == KErrNone )
        {
        ret = repository->Get( KPslnColorPalette, colorScheme );
        }
    delete repository;
    
#ifdef AVKON_RDEBUG_INFO
    _LIT( KDMsg, "Cenrep CAknNavigationControlContainer::ColorScheme %d" );
    RDebug::Print( KDMsg, colorScheme );
#endif

    if ( colorScheme < 0 ||
         colorScheme >= TInt( sizeof( KNaviWipeBitmaps ) / sizeof( TInt ) ) )
        {
        // If shared data returned illegal color scheme
        // value default blue scheme is returned.
        colorScheme = 0;
        }

    return colorScheme;
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::NotifyNaviWipeStatusL
// ---------------------------------------------------------------------------
//
void CAknNavigationControlContainer::NotifyNaviWipeStatusL()
    {
    if ( iExtension && iExtension->iDestructionOngoing )
        {
        return;
        }

    // If flat statuspane is active, then we don't have navi wipe on/off,
    // but instead we bring title pane to the foreground or let navipane
    // partially cover titlepane. But also in this we had to update naviwipe
    // statuses, because layout might need to be switched.
    if ( AknStatuspaneUtils::FlatLayoutActive() )
        {
        RWindow* naviwindow      = NULL;
        CCoeControl* navicontrol = NULL;

        RWindow* titlewindow      = NULL;
        CCoeControl* titlecontrol = NULL;
        
        RWindow* emptywindow      = NULL;
        CCoeControl *emptycontrol = NULL;

        if ( iStatusPane )
            {
            TRAP_IGNORE( navicontrol =
                            iStatusPane->ContainerControlL(
                                TUid::Uid( EEikStatusPaneUidNavi ) ) );
            if ( navicontrol )
                {
                RDrawableWindow* drawableWindow = navicontrol->DrawableWindow();
                if ( drawableWindow )
                    {
                    // trust that container is always RWindow
                    naviwindow = static_cast <RWindow*> ( drawableWindow );
                    }
                }

            TRAP_IGNORE( titlecontrol =
                            iStatusPane->ContainerControlL(
                                TUid::Uid( EEikStatusPaneUidTitle ) ) );
            if ( titlecontrol )
                {
                RDrawableWindow* drawableWindow = titlecontrol->DrawableWindow();
                if ( drawableWindow )
                    {
                    // trust that container is always RWindow
                    titlewindow = static_cast <RWindow*> ( drawableWindow );
                    }
                }
            
            TRAP_IGNORE( emptycontrol = 
                            iStatusPane->ContainerControlL(
                                    TUid::Uid( EEikStatusPaneUidEmpty) ) );
            if ( emptycontrol )
                {
                RDrawableWindow *drawableWindow = emptycontrol->DrawableWindow();
                if ( drawableWindow )
                    {
                    emptywindow = static_cast <RWindow*> ( drawableWindow );
                    }
                }
            }

        const TInt last = iNaviPaneControls->Count() - 1;
        if ( ( last < 0 || !( iNaviPaneControls->At( last ) ) ) ||
             ( last >= 0 &&
               iNaviPaneControls->At( last ) && 
               iNaviPaneControls->At( last )->ControlType() ==
                   CAknNavigationDecorator::ENaviVolume ) )
            {
            // If not controls in navi stack, send navipane behind of titlepane
            // Minus ordinal ordinal position number always means set
            // the window to be the last one of the windows with the same
            // ordinal priority
            if ( iExtension->iIsActiveIdle )//Added for active idle's transparent
            	{
            if ( titlewindow )
                {
                titlewindow->SetOrdinalPosition( 4 );
                }
            if ( naviwindow )
                {
                naviwindow->SetOrdinalPosition( 5 );
                }
            if ( emptywindow )
                {
                emptywindow->SetOrdinalPosition( 6 );
                }
              }
           else
             {
             if ( titlewindow )
                {
                titlewindow->SetOrdinalPosition( -1 );
                }
            if ( naviwindow )
                {
                naviwindow->SetOrdinalPosition( -1 );
                }
            if ( emptywindow )
                {
                emptywindow->SetOrdinalPosition( -1 );
                }
             }
            }
        else
            {
            // If  controls in navi stack, send titlepane behind the navipane.
            // Minus ordinal ordinal position number always means set
            // the window to be the last one of the windows with the same
            // ordinal priority
            if ( iExtension->iIsActiveIdle )//Added for active idle's transparent
            	{
            if ( naviwindow )
                {
                naviwindow->SetOrdinalPosition( 4 );
                }
            if ( titlewindow )
                {
                titlewindow->SetOrdinalPosition( 5 );
                }
            if ( emptywindow )
                {
                emptywindow->SetOrdinalPosition( 6 );
                }
              }
              else
              	{
             if ( naviwindow )
                {
                naviwindow->SetOrdinalPosition( -1 );
                }
            if ( titlewindow )
                {
                titlewindow->SetOrdinalPosition( -1 );
                }
            if ( emptywindow )
                {
                emptywindow->SetOrdinalPosition( -1 );
                }
              	}
            }

        // Finally request titlepane to refresh itself.
        if( titlecontrol )
            {
            titlecontrol->SetSize( titlecontrol->Size() );
            titlecontrol->DrawDeferred();
            DrawDeferred();
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::HandleLosingForeground
// ---------------------------------------------------------------------------
//
void CAknNavigationControlContainer::HandleLosingForeground()
    {
    // If volume popup is shown when the navi pane loses foreground,
    // then the popup needs to be closed if shown, and the volume control
    // told that it's not the topmost control.    
    CAknNavigationDecorator* topControl = Top();
    
    if ( topControl )
        {
        if ( topControl &&
             topControl->ControlType() == CAknNavigationDecorator::ENaviVolume )
            {
            CAknVolumePopup* volumePopup =
                static_cast<CAknVolumePopup*> (
                    topControl->iDecoratedControl );

            if ( volumePopup )
                {
                volumePopup->CloseVolumePopup();
                static_cast<CAknVolumeControl*>(
                    topControl->DecoratedControl() )->HandleNaviStackChange( EFalse );
                }
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::HandleGainingForegroundL
// ---------------------------------------------------------------------------
//
void CAknNavigationControlContainer::HandleGainingForegroundL()
    {
    if ( iExtension && iExtension->iDestructionOngoing )
        {
        return;
        }
        
    // Inform the volume popup about the foreground gain if it's the
    // topmost control on the navi stack.
    CAknNavigationDecorator* topControl = Top();
    if ( topControl )
        {
        if ( topControl &&
             topControl->ControlType() == CAknNavigationDecorator::ENaviVolume )
            {
            CAknVolumePopup* volumePopup =
                static_cast<CAknVolumePopup*> ( topControl->iDecoratedControl );

            if ( volumePopup )
                {
                static_cast<CAknVolumeControl*>(
                    topControl->DecoratedControl() )->HandleNaviStackChange( ETrue );
                }
            }
        }
    
    NotifyNaviWipeStatusL();
    }
    

// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::NaviWipeUsed
// Naviwipe graphics is no more used (since 3.0).
// ---------------------------------------------------------------------------
//
TBool CAknNavigationControlContainer::NaviWipeUsed() const
    {
    return EFalse;
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::IsFepOwnedEditorIndicatorControl
// Checks whether a navi decorator is an editor indicator control owned
// by a FEP.
// ---------------------------------------------------------------------------
//
TBool CAknNavigationControlContainer::IsFepOwnedEditorIndicatorControl(
    CAknNavigationDecorator* aDecorator ) const
    {
    TBool fepOwnedIndicator = EFalse;
    MAknEditingStateIndicator* fepIndicator =
        CAknEnv::Static()->EditingStateIndicator();
    if ( aDecorator &&
         aDecorator->ControlType() == CAknNavigationDecorator::EEditorIndicator &&
         fepIndicator &&
         fepIndicator->IndicatorContainer() == aDecorator->DecoratedControl() )
        {
        fepOwnedIndicator = ETrue;
        }

    return fepOwnedIndicator;
    }


// -----------------------------------------------------------------------------
// CAknNavigationControlContainer::HandleVisibilityOfNonFepOwnedIndicatorControl
// -----------------------------------------------------------------------------
//
void CAknNavigationControlContainer::HandleVisibilityOfNonFepOwnedIndicatorControl(
    CAknNavigationDecorator* aDecorator,
    TBool aVisible )
    {
    if ( aDecorator &&
         aDecorator->ControlType() == CAknNavigationDecorator::EEditorIndicator &&
         !IsFepOwnedEditorIndicatorControl( aDecorator ) )
        {
        aDecorator->DecoratedControl()->MakeVisible( aVisible );
        }
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::DrawDefaultNaviWipe
// Naviwipe graphics is no more used (since 3.0).
// ---------------------------------------------------------------------------
//
TBool CAknNavigationControlContainer::DrawDefaultNaviWipe(
    CWindowGc& /*aGc*/,
    const TRect& /*aRect*/ ) const
    {
    return EFalse;
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::DrawDefaultNaviSolid
// ---------------------------------------------------------------------------
//
TBool CAknNavigationControlContainer::DrawDefaultNaviSolid(
    CWindowGc& aGc,
    const TRect& aRect ) const
    {
    TRect rect( aRect );

    // screen
    TRect screenRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screenRect );

    // application window
    TAknLayoutRect applicationWindowLayoutRect;
    applicationWindowLayoutRect.LayoutRect(
        screenRect,
        AknLayoutScalable_Avkon::application_window( 0 ) );
    TRect applicationWindowRect( applicationWindowLayoutRect.Rect() );

    // status pane
    TAknLayoutRect statusPaneLayoutRect;
    statusPaneLayoutRect.LayoutRect(
        applicationWindowRect,
        AknLayoutScalable_Avkon::status_pane( 0 ) );
    TRect statusPaneRect( statusPaneLayoutRect.Rect() );

    // navi pane
    TAknLayoutRect naviPaneLayoutRect;
    if ( !Layout_Meta_Data::IsLandscapeOrientation() )
        {
        naviPaneLayoutRect.LayoutRect(
            statusPaneRect,
            AknLayoutScalable_Avkon::navi_pane( 5 ) );
        }
    else
        {
        if ( AknStatuspaneUtils::StaconPaneActive() )
            {
            TInt skVariety = AknStatuspaneUtils::StaconSoftKeysRight() ? 2 : 3;
            naviPaneLayoutRect.LayoutRect(
                statusPaneRect,
                AknLayoutScalable_Avkon::navi_pane_stacon( skVariety ) );
            }
        else
            {
            naviPaneLayoutRect.LayoutRect(
                statusPaneRect,
                AknLayoutScalable_Avkon::navi_pane( 0 ) );
            }
        }
    TRect naviPaneRect( naviPaneLayoutRect.Rect() );

    // navi wipe graphics
    TAknLayoutRect naviWipeGraphicsLayoutRect;
    naviWipeGraphicsLayoutRect.LayoutRect(
        statusPaneRect,
        AknLayoutScalable_Avkon::status_pane_g1( 0 ) );
    TRect naviWipeGraphicsRect( naviWipeGraphicsLayoutRect.Rect() );

    TRect naviWipeNaviPanePart( naviWipeGraphicsRect );

    if ( naviWipeNaviPanePart.Intersects( naviPaneRect ) )
        {
        naviWipeNaviPanePart.Intersection( naviPaneRect );
        // calculate new origo, relative to navipane rect.
        naviWipeNaviPanePart.iTl.iX -= naviPaneRect.iTl.iX;
        naviWipeNaviPanePart.iTl.iY -= naviPaneRect.iTl.iY;
        naviWipeNaviPanePart.iBr.iX -= naviPaneRect.iTl.iX;
        naviWipeNaviPanePart.iBr.iY -= naviPaneRect.iTl.iY;
        }

    // Finally check where naviwipe intersects this rect
    if ( naviWipeNaviPanePart.Intersects( rect ) )
        {
        naviWipeNaviPanePart.Intersection( rect );
        }

    // Clear first to enable 1 pixel borders
    aGc.SetPenStyle( CGraphicsContext::ENullPen );
    aGc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    aGc.SetBrushColor( AKN_LAF_COLOR( KStatusPaneBackgroundColor ) );
    aGc.DrawRect( rect );

    // Draw the rect
    aGc.SetPenStyle( CGraphicsContext::ENullPen );
    aGc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    aGc.SetBrushColor(
        AKN_LAF_COLOR( KStatusPaneBackgroundGraphicsColorUsual ) );
    aGc.DrawRect( naviWipeNaviPanePart );

    return ETrue;
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::DrawSkinnedNaviSolid
// Naviwipe graphics is no more used (since 3.0).
// ---------------------------------------------------------------------------
//
TBool CAknNavigationControlContainer::DrawSkinnedNaviWipe(
    CWindowGc& /*aGc*/,
    const TRect& /*aRect*/,
    MAknsSkinInstance* /*skin*/,
    MAknsControlContext* /*aCc*/) const
    {
    return EFalse;
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::DrawSkinnedNaviSolid
// ---------------------------------------------------------------------------
//
TBool CAknNavigationControlContainer::DrawSkinnedNaviSolid(
    CWindowGc& aGc,
    const TRect& aRect,
    MAknsSkinInstance* aSkin,
    MAknsControlContext* aCc ) const
    {
    TRect rect( aRect );

    aGc.SetPenStyle( CGraphicsContext::ENullPen );
    aGc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    aGc.SetBrushColor( AKN_LAF_COLOR( KStatusPaneBackgroundColor ) );

    return AknsDrawUtils::Background( aSkin, aCc, this, aGc, rect );
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::MopSupplyObject
// ---------------------------------------------------------------------------
//
TTypeUid::Ptr CAknNavigationControlContainer::MopSupplyObject( TTypeUid aId )
    {
    if ( aId.iUid == CAknNavigationControlContainer::ETypeId )
        {
        // Return self, this code makes it possible to workaround the fact
        // that statuspane controls cannot be safely casted after
        // retrieving them using CEikStatusPaneBase::ControlL().
        //
        // So now the caller could do something like this rather safely:
        //
        // CEikStatusPaneBase* statusPane = CEikStatusPaneBase::Current();
        // CAknNavigationControlContainer* naviPane = NULL;
        //
        //if (statusPane &&
        //    statusPane->PaneCapabilities(TUid::Uid(EEikStatusPaneUidNavi)).IsInCurrentLayout())
        //    {
        //    CCoeControl* control = statusPane->ControlL(TUid::Uid( EEikStatusPaneUidNavi ));
        //    control->MopGetObject(naviPane);
        //    }
        //
        //if (naviPane)
        //  {
        //  // The retrieved control was type of CAknNavigationControlContainer
        //  }
        //else
        //  {
        //  // The retrieved control was NOT type of CAknNavigationControlContainer.
        //  // Someone has perhaps swap the control in the statuspane.
        //  }
        return aId.MakePtr( this );
        }

    return CCoeControl::MopSupplyObject( aId );
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::LoadNaviColorBitmapL
// ---------------------------------------------------------------------------
//
void CAknNavigationControlContainer::LoadNaviColorBitmapL()
    {
    if ( !iExtension )
        {
        return;
        }

    if ( iExtension->iNaviColorBitmap )
        {
        delete iExtension->iNaviColorBitmap;
        iExtension->iNaviColorBitmap = NULL;
        }

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    TRgb color( KRgbGray );

    if ( AknStatuspaneUtils::StaconPaneActive() )
        {
        AknsUtils::GetCachedColor( skin,
                                   color,
                                   KAknsIIDQsnIconColors,
                                   EAknsCIQsnIconColorsCG25 );
        }
    else
        {
        AknsUtils::GetCachedColor( skin,
                                   color,
                                   KAknsIIDQsnIconColors,
                                   EAknsCIQsnIconColorsCG7 );
        }

    // Parent rect is searched from laf data because it can be zero sized when
    // this method gets called from constructor.

    // screen
    TRect screenRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screenRect );

    // app window
    TAknLayoutRect applicationWindowLayoutRect;
    applicationWindowLayoutRect.LayoutRect(
        screenRect,
        AknLayoutScalable_Avkon::application_window( 0 ) );
    TRect applicationWindowRect( applicationWindowLayoutRect.Rect() );

    // statuspane
    TAknLayoutRect statusPaneLayoutRect;
    statusPaneLayoutRect.LayoutRect( applicationWindowRect,
                                     AknLayoutScalable_Avkon::status_pane( 0 ) );
    TRect statusPaneRect( statusPaneLayoutRect.Rect() );

    // navi pane
    TAknLayoutRect naviPaneLayoutRect;
    if ( !Layout_Meta_Data::IsLandscapeOrientation() )
        {
        naviPaneLayoutRect.LayoutRect( statusPaneRect,
                                       AknLayoutScalable_Avkon::navi_pane( 5 ) );
        }
    else
        {
        if ( AknStatuspaneUtils::StaconPaneActive() )
            {
            TInt skVariety = AknStatuspaneUtils::StaconSoftKeysRight() ? 2 : 3;
            naviPaneLayoutRect.LayoutRect( statusPaneRect,
                                           AknLayoutScalable_Avkon::navi_pane_stacon( skVariety ) );
            }
        else
            {
            naviPaneLayoutRect.LayoutRect( statusPaneRect,
                                           AknLayoutScalable_Avkon::navi_pane( 0 ) );
            }
        }
    TRect naviPaneRect( naviPaneLayoutRect.Rect() );

    TRect parentRect( 0, 0, naviPaneRect.Width(), naviPaneRect.Height() );

    TAknLayoutRect rect;
    rect.LayoutRect( parentRect,
                     TAknWindowComponentLayout::Compose(
                        AknLayoutScalable_Avkon::navi_navi_pane(),
                        AknLayoutScalable_Avkon::navi_navi_pane_g1( 0 ) ) );

    iExtension->iNaviColorBitmap = new (ELeave) CFbsBitmap();

    AknIconConfig::TPreferredDisplayMode mode;
    AknIconConfig::PreferredDisplayMode( mode, AknIconConfig::EImageTypeOffscreen );
    
    //To fix TSW Error:ELLI-7UU67E, we have to adjust color bitmap size so as to be
    //different from arrow bitmap mask size, since it is weird that the arrow icon can't
    //be shown correctly when they were the same size.
    //This may be removed when NGA is stable enough.
    TSize arrowSize( rect.Rect().Size().iWidth, rect.Rect().Size().iHeight-1 );
    
    TInt err = iExtension->iNaviColorBitmap->Create( arrowSize,
                                                     mode.iBitmapMode );
    if ( err != KErrNone )
        {
        delete iExtension->iNaviColorBitmap;
        iExtension->iNaviColorBitmap = NULL;
        return;
        }

    CFbsBitmapDevice* destinationDevice =
        CFbsBitmapDevice::NewL( iExtension->iNaviColorBitmap );
    CleanupStack::PushL( destinationDevice );

    CFbsBitGc* destinationGc;
    User::LeaveIfError( destinationDevice->CreateContext( destinationGc ) );

    destinationGc->SetPenColor( color );
    destinationGc->SetPenStyle( CGraphicsContext::ESolidPen );
    destinationGc->SetBrushColor( color );
    destinationGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    destinationGc->DrawRect( TRect( rect.Rect().Size() ) );

    delete destinationGc;
    CleanupStack::PopAndDestroy( destinationDevice );
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::NaviColorBitmap
// ---------------------------------------------------------------------------
//
CFbsBitmap* CAknNavigationControlContainer::NaviColorBitmap() const
    {
    CFbsBitmap* bitmap = NULL;
    
    if ( iExtension )
        {
        bitmap = iExtension->iNaviColorBitmap;
        }
    
    return bitmap;
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::CurrentNaviWipeBitmap
// Returns the index of the navi wipe graphics to be used.
// ---------------------------------------------------------------------------
//
TInt CAknNavigationControlContainer::CurrentNaviWipeBitmap()
    {
    TInt bitmapId =
        KNaviWipeBitmaps[CAknNavigationControlContainer::ColorScheme()];

    // Do some safety checkings for the bitmap & mask values as AknIconUtils
    // cannot cope with situation where one of them is in the mbm range and
    // other in mif range. Default to blue if necessary.
    if ( EMbmAvkonQgn_graf_navi_wipe_blue_mask > KMifIdFirst )
        {
        if ( bitmapId < KMifIdFirst && bitmapId != KNaviDrawWithSolidColor )
            {
            bitmapId = EMbmAvkonQgn_graf_navi_wipe_blue;
            }
        }
    else
        {
        if ( bitmapId > KMifIdFirst && bitmapId != KNaviDrawWithSolidColor )
            {
            bitmapId = EMbmAvkonQgn_graf_navi_wipe_blue;
            }
        }

    return bitmapId;
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::SetBackgroundContextAttributes
// Naviwipe graphics is no more used (since 3.0)
// ---------------------------------------------------------------------------
//
void CAknNavigationControlContainer::SetBackgroundContextAttributes(
    CCoeControl* /*aControl*/, TBool /*aNaviWipeUsed*/ )
    {
    return;
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::SetContainerWindowNonFading
// Allows/disallows fading of the navi pane.
// ---------------------------------------------------------------------------
//
void CAknNavigationControlContainer::SetContainerWindowNonFading(
    TBool aNonFading )
    {
    if ( iStatusPane )
        {
        CCoeControl* control = NULL;
        TRAPD( err,
               control = iStatusPane->ContainerControlL(
                            TUid::Uid( EEikStatusPaneUidNavi ) ) );

        if ( !err && control )
            {
            control->DrawableWindow()->SetNonFading( aNonFading );
            }
        }
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::VolumePopupRect
// Gets the area for volume popup control from the layout data.
// ---------------------------------------------------------------------------
//
TRect CAknNavigationControlContainer::VolumePopupRect()
    {
    TAknLayoutRect layoutRect;

    TRect appRect;
    AknLayoutUtils::LayoutMetricsRect(
        AknLayoutUtils::EApplicationWindow,
        appRect );
    
    if ( AknStatuspaneUtils::HDLayoutActive() || 
         Layout_Meta_Data::IsLandscapeOrientation() )
        {
        layoutRect.LayoutRect(
            appRect,
            AknLayoutScalable_Avkon::main_pane( 13 ) );
        }
    else
        {
        layoutRect.LayoutRect(
            appRect,
            AknLayoutScalable_Avkon::main_pane( 3 ) );
        }
    
    layoutRect.LayoutRect(
        layoutRect.Rect(),
        AknLayoutScalable_Avkon::popup_slider_window(
            Layout_Meta_Data::IsLandscapeOrientation() )  );
    
    return layoutRect.Rect();
    }


// ---------------------------------------------------------------------------
// CAknNavigationControlContainer::SetPreferredNaviDecoratorLayoutStyle
// Sets the preferred navi decorator layout.
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknNavigationControlContainer::SetPreferredNaviDecoratorLayoutStyle(
    TInt aLayoutStyle )
    {
    iExtension->iPreferredNaviDecoratorLayoutStyle = aLayoutStyle;
    }

//  End of File
