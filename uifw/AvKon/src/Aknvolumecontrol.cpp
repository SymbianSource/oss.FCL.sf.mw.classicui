/*
* Copyright (c) 2002-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Volume editor class
*
*/


// INCLUDE FILES
#include "Aknvolumecontrol.h"
#include <gulicon.h>
#include <AknPanic.h>
#include <AknNaviObserver.h>
#include <AknUtils.h>
#include <barsread.h>
#include <AknStatuspaneUtils.h>
#include <aknnavide.h>
#include <AknsDrawUtils.h>
#include <AknsFrameBackgroundControlContext.h>
#include <aknappui.h>
#include <aknconsts.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <skinlayout.cdl.h>
#include <avkon.mbg>
#include <AknVolumePopup.h>

#include <AknTasHook.h>
#include <touchfeedback.h>
#include <aknlayoutscalable_apps.cdl.h>
// CONSTANTS
const TInt KVolumeMinValue  = 1;
const TInt KVolumeMaxValue  = 10;
const TInt KVolumeLevels    = 10;

const TInt KVolumeButtonDown        = 0x01;
const TInt KVolumeNaviPaneMuted     = 0x02;
const TInt KVolumeStepChange        = 0x04;
const TInt KVolumeLevelNotFound     = 0;
const TInt KVolumeLevelMuteTapped   = 2000;

const TInt KVolumeNaviPaneMutedValue = 0;

// Define the loaded icon types - this affects drawing.
const TInt KGfxModeNotLoaded    = 0;
const TInt KGfxModeNew          = 1;// 1 slider type icon (+mask)
const TInt KGfxModeOld          = 2;// 10 ball icons, one for each volume level (+masks)
const TInt KScrollRepeatTimeout = 250000; // 0.25 seconds
// ----------------------------------------------------------------------------
// Extension class
//
// ----------------------------------------------------------------------------
//
NONSHARABLE_CLASS(CVolumeExtension) : public CBase
    {
    public:
        CVolumeExtension();
        ~CVolumeExtension();

        // Methods for svg drawing
        static TBool UseSvgDrawing();
        void DeleteBitmaps();
        void SetIconSizes( TInt aStyle, const TRect& aParent ) const;

        void LoadBitmapsL( TInt aStyle, const TRect& aParent );
        
        // Sub-methods used by LoadBitmapsL
        void TryLoadBitmapsSkinnedL( MAknsSkinInstance* aSkin );
        void TryLoadBitmapsDefaultLargeL( MAknsSkinInstance* aSkin );
        void TryLoadBitmapsDefaultSmallL( MAknsSkinInstance* aSkin );
        void TryLoadBitmapsNoSkinL();
        
        void CalculateParentRect( TInt aStyle, const TRect& aParent );
        void DrawSvgSmallVolume( TInt aStyle, const TRect& aRect,
                                CBitmapContext& aGc, TInt aValue );
        void DrawSvgSettingsVolume( const TRect& aRect,
                                CWindowGc& aGc, TInt aValue );
        static void CreateSvgSettingsIconL( const TRect& aRect,
                                            TInt aValue, 
                                            CGulIcon* aIcon );
        static void CreateDynRangeStyleSettingsIconL( const TRect& aRect,
                                            TInt aValue, 
                                            CGulIcon* aIcon,
                                            TInt aMinimum,
                                            TInt aMaximum );                                   
                                            
        void DrawSvgSettingsIconL( const TRect& aRect,
                                    TInt aValue,
                                    CGulIcon* aIcon );
        void DrawDynRangeStyleSettingsIconL( const TRect& aRect,
                                    TInt aValue,
                                    CGulIcon* aIcon,
                                    TInt aMinimum, 
                                    TInt aMaximum );
                                    
        TInt GetVolumeLevelByPosition( const TInt& aStyle,
                                       const TPoint& aPoint,
                                       const TRect& aAreaRect ) const;

        TRect RectFromLayout( const TRect& aParent,
                              const TAknWindowComponentLayout& aComponentLayout
                            ) const;

        CFbsBitmap* iActiveIcons[KVolumeLevels];
        CFbsBitmap* iInActiveIcons[KVolumeLevels];
        CFbsBitmap* iActiveMasks[KVolumeLevels];
        CFbsBitmap* iInActiveMasks[KVolumeLevels];

        TRect iParentRect;  // Volume indicator area
        TRect iMuteRect; // Mute indicator rect for tapping 

        TRect iVolumeLevels[ KVolumeLevels ]; // Deprecated
        TInt iFlags;

        // Volume icons will be loaded the first time they are drawn,
        // not when the control is constructed.
        TBool iHasBeenDrawn;
        TFileName iBmpFilename;
        TInt iBmpId;
        TInt iBmpMask;

        CPeriodic* iTimer;
        TInt iEffectTimerCount;
        TInt iAnimatedEffectValue;
        
        TInt iStoredLevel;
        
        // For hi-res volume control implementation
        TInt iMinimumValue;
        TInt iMaximumValue;
        TInt iGfxMode; // Defines which icons are loaded when drawing
        TInt iOldScaleSettingVolume; // for 9 step setting volume
        
        /**
        * Flag to define whether or not this control is topmost on the navi pane's
        * control stack.
        */
        TBool iIsOnNaviStack;
        TInt iOldLevel;
        TBool iReduce;        
        
        TBool iNoDraw;        
        TBool iGrabPoint;

       /**
        * Extended touch area used 
        */
        TBool iUseExtendedTouchArea;
        
       /**
        * Touch area 
        */        
        TRect iTouchArea;
    };

// ----------------------------------------------------------------------------
// CAknVolumeControl::CAknVolumeControl()
// Default constructor.
// ----------------------------------------------------------------------------
//
EXPORT_C CAknVolumeControl::CAknVolumeControl()
    {
    AKNTASHOOK_ADD( this, "CAknVolumeControl" );
    }

// ----------------------------------------------------------------------------
// CAknVolumeControl::~CAknVolumeControl()
// Destructor.
// ----------------------------------------------------------------------------
//
EXPORT_C CAknVolumeControl::~CAknVolumeControl()
    {
    AKNTASHOOK_REMOVE();
    AknsUtils::DeregisterControlPosition( this );
    delete iBitmap;
    delete iMaskBitmap;
    delete iExtension;
    }

// ----------------------------------------------------------------------------
// CAknVolumeControl::SetValue(TInt aValue)
// Sets the value.
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknVolumeControl::SetValue( TInt aValue )
    {
    // NOTE: In settings page layouts (EDynRangeSettingsVolumeControl) 
    // using dynamic min and max values defined in the resource file. The 
    // values cannot be checked in SetValue() because SetValue() is called 
    // before ConstructFromResource() which actually reads the min and max 
    // values as well as the default value even though it is also given in 
    // the settings page constructor parameter.
    //
    if ( !iExtension )
        {
        return;
        }
    
    TBool valueChanged( aValue != iValue );
    
    switch( iStyle )
        {
        case EDynRangeSettingsVolumeControl:
        case EDynRangeNaviPaneVolumeControl:
            // Do not check EDynRangeSettingsVolumeControl because it's value 
            // might be set before the actual min and max are read from the 
            // resource (settings page feature).
            // Navi pane's EDynRangeNaviPaneVolumeControl is also ignored.
            break;
        default:
            __ASSERT_DEBUG( aValue >= iExtension->iMinimumValue && 
                            aValue <= iExtension->iMaximumValue, 
                            Panic( EAknPanicOutOfRange ) );
        }
    
    iValue = aValue;

    if ( iExtension )
        {
        iExtension->iFlags &= ~KVolumeNaviPaneMuted;
        }

    if ( iStyle == ENaviPaneVolumeControl || 
         iStyle == EDynRangeNaviPaneVolumeControl )
        {
        TInt event = MAknNavigationObserver::ENaviEventHandleNavigation;
        if ( iValue <= iExtension->iMinimumValue )
            {
            event=MAknNavigationObserver::ENaviEventLeftMostItemReached;
            if ( iValue == iExtension->iMinimumValue )
                {
                iExtension->iFlags |= KVolumeNaviPaneMuted;
                }
            }
        else if ( iExtension->iMaximumValue == iValue )
            {
            event = MAknNavigationObserver::ENaviEventRightMostItemReached;
            }
        
        TRAP_IGNORE(
            ReportEventL(
                STATIC_CAST( MCoeControlObserver::TCoeEvent, event ) ) );

        if ( valueChanged )
            {
            TRAP_IGNORE(
                ReportEventL(
                    MCoeControlObserver::EEventStateChanged ) );
            }

        SetVolumeLayout( iStyle );
        if ( !iExtension->iNoDraw )
            {
            DrawNow();    
            }        
        
        // Volume popup is used instead of navi pane volume control,
        // pass the new value also to the popup.
        CAknVolumePopup* parent = static_cast<CAknVolumePopup*> ( Parent() );
        if ( parent && parent->ComponentControl( 5 ) == this )
            {
            if ( valueChanged )
                {
                parent->SetValue( aValue );
                }

            if ( iExtension->iIsOnNaviStack && ( valueChanged ||
                aValue == iExtension->iMinimumValue ||
                aValue == iExtension->iMaximumValue ) )
                {
                // Show the popup only if status pane is visible
                // to maintain same kind of functionality as in
                // navi pane volume control.
                CEikStatusPaneBase* sp = CEikStatusPaneBase::Current();
                if ( sp && sp->IsVisible() )
                    {
                    TRAP_IGNORE( parent->ShowVolumePopupL() );
                    }
                }
            }
        }
    }

// ----------------------------------------------------------------------------
// CAknVolumeControl::Value() const
// Returns the value.
// ----------------------------------------------------------------------------
//
EXPORT_C TInt CAknVolumeControl::Value() const
    {
    return iValue;
    }

// ----------------------------------------------------------------------------
// CAknVolumeControl::SetRange()
//
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknVolumeControl::SetRange( TInt aMinimumValue, 
                                           TInt aMaximumValue )
    {
    TBool rangeChanged( aMinimumValue != iExtension->iMinimumValue ||
                        aMaximumValue != iExtension->iMaximumValue );
    
    __ASSERT_DEBUG( aMinimumValue < aMaximumValue, 
                     Panic( EAknPanicInvalidValue ) );
    if ( iExtension )
        {
        iExtension->iMinimumValue = aMinimumValue;
        iExtension->iMaximumValue = aMaximumValue;
        }
        
    // disable old volume control scaling
    if(iExtension->iOldScaleSettingVolume)
        {
        iExtension->iOldScaleSettingVolume = EFalse;
        }
        
    if ( iExtension->iIsOnNaviStack )
        {
        // Volume popup is used instead of navi pane volume control,
        // pass the new range also to the popup.
        CAknVolumePopup* parent = static_cast<CAknVolumePopup*> ( Parent() );

        if ( parent && parent->ComponentControl( 5 ) == this )
            {
            if ( rangeChanged )
                {
                parent->SetRange( aMinimumValue, aMaximumValue );
                }
            }
        }
    }

// ----------------------------------------------------------------------------
// CAknVolumeControl::GetRange()
//
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknVolumeControl::GetRange( TInt& aMinimumValue, 
                                           TInt& aMaximumValue )
    {
    if ( iExtension )
        {
        aMinimumValue = iExtension->iMinimumValue;
        aMaximumValue = iExtension->iMaximumValue;
        }
    }

// ----------------------------------------------------------------------------
// CAknVolumeControl::CreateBitmapL()
//
// ----------------------------------------------------------------------------
//
EXPORT_C CFbsBitmap* CAknVolumeControl::CreateBitmapL(TInt aValue)
    {
    CGulIcon* icon = 
            CreateSetStyleListBoxIconL( aValue ); // now have ownership
    icon->SetBitmapsOwnedExternally( ETrue );
    CFbsBitmap* bitmap = icon->Bitmap();
    CFbsBitmap* mask = icon->Mask();
    delete icon;
    delete mask;
    return bitmap; // Ownership transferred
    }

// ----------------------------------------------------------------------------
// CAknVolumeControl::CreateSetStyleListBoxIconL()
// Draw volume control in setting list item
// ----------------------------------------------------------------------------
//
EXPORT_C CGulIcon* CAknVolumeControl::CreateSetStyleListBoxIconL( TInt aValue )
    {
    
    // Make the icon and put it in the array
    CGulIcon* icon = CGulIcon::NewLC();

    TRect origin;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, origin );

    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect(origin,
                    AknLayoutScalable_Avkon::listscroll_gen_pane(0));
    layoutRect.LayoutRect(layoutRect.Rect(),
                    AknLayoutScalable_Avkon::list_gen_pane(0));
    layoutRect.LayoutRect(layoutRect.Rect(),
                    AknLayoutScalable_Avkon::list_setting_number_pane(0));
    layoutRect.LayoutRect(layoutRect.Rect(),
                    AknLayoutScalable_Avkon::set_value_pane(0));
    layoutRect.LayoutRect(layoutRect.Rect(),
                    AknLayoutScalable_Avkon::volume_small_pane_cp());
    TRect rect(layoutRect.Rect());

    // Move to 0,0
    rect.Move(-rect.iTl.iX,-rect.iTl.iY);

    CVolumeExtension::CreateSvgSettingsIconL( rect, aValue, icon );

    CleanupStack::Pop( icon ); // icon - not owned anymore, do not destroy

    return icon; // Ownership transferred
    }

// ----------------------------------------------------------------------------
// CAknVolumeControl::CreateScalableListBoxIconL()
// Draw a scalable volume control in setting list item
// ----------------------------------------------------------------------------
//
EXPORT_C CGulIcon* CAknVolumeControl::CreateSetDynRangeStyleListBoxIconL( 
                                                                 TInt aValue,
                                                                 TInt aMinimum,
                                                                 TInt aMaximum )
    {
    
    
    // Make the icon and put it in the array
    CGulIcon* icon = CGulIcon::NewLC();

    TRect origin;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, origin );

    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect(origin,
                    AknLayoutScalable_Avkon::listscroll_gen_pane(0));
    layoutRect.LayoutRect(layoutRect.Rect(),
                    AknLayoutScalable_Avkon::list_gen_pane(0));
    layoutRect.LayoutRect(layoutRect.Rect(),
                    AknLayoutScalable_Avkon::list_setting_number_pane(0));
    layoutRect.LayoutRect(layoutRect.Rect(),
                    AknLayoutScalable_Avkon::set_value_pane(0));
    layoutRect.LayoutRect(layoutRect.Rect(),
                    AknLayoutScalable_Avkon::volume_small_pane_cp());
    TRect rect(layoutRect.Rect());

    // Move to 0,0
    rect.Move(-rect.iTl.iX,-rect.iTl.iY);

    CVolumeExtension::CreateDynRangeStyleSettingsIconL( rect, aValue, icon, 
                                                        aMinimum, aMaximum );

    CleanupStack::Pop( icon ); // icon - not owned anymore, do not destroy

    return icon; // Ownership transferred
    }
  
    
// ----------------------------------------------------------------------------
// CAknVolumeControl::HandleNaviStackChange()
// ----------------------------------------------------------------------------
//    
void CAknVolumeControl::HandleNaviStackChange( TBool aIsOnNaviStack )
    {
    if ( iExtension )
        {
        iExtension->iIsOnNaviStack = aIsOnNaviStack;
        }
    }
    
    
// ----------------------------------------------------------------------------
// CAknVolumeControl::MinimumSize()
// Returns the size.
// ----------------------------------------------------------------------------
//
TSize CAknVolumeControl::MinimumSize()
    {
    TAknLayoutRect layout;
    if ( iStyle == ENaviPaneVolumeControl )
        {
        if ( AknStatuspaneUtils::SmallLayoutActive() )
            {
            layout.LayoutRect( Rect(),
                        AknLayoutScalable_Avkon::volume_small2_pane() );        
            }
        else
            {
            layout.LayoutRect( Rect(),
                        AknLayoutScalable_Avkon::volume_small_pane() );        
            }
        
        return layout.Rect().Size();
        }
    else // Setting Page & Popup volume control
        {
        return Rect().Size();
        }
    }

// ----------------------------------------------------------------------------
// CAknVolumeControl::OfferKeyEventL
// Handles the key events.
// ----------------------------------------------------------------------------
//
TKeyResponse CAknVolumeControl::OfferKeyEventL( const TKeyEvent& aKeyEvent,
                                                TEventCode aType )
    {
    if ( aType == EEventKey )
        {
        TInt volumeValue = Value();
        switch( aKeyEvent.iCode )
            {
            case EKeyLeftArrow:
                {
                if (volumeValue > iExtension->iMinimumValue)
                    {
                    volumeValue--;
                    SetValue( volumeValue );
                    if ( iStyle != EDynRangePopupVolumeControl &&
                         !iExtension->iNoDraw )
                        {                        
                        DrawNow();
                        }
                    ReportEventL( MCoeControlObserver::EEventStateChanged );
                    }
                else
                    {
                    CAknVolumePopup* parent =
                        static_cast<CAknVolumePopup*> ( Parent() );
                    if ( iExtension &&
                         iExtension->iIsOnNaviStack &&
                         parent &&
                         parent->ComponentControl( 5 ) == this )
                        {
                        // Show the volume popup even if volume level is not changed
                        // to indicate that a volume adjustment key event has been
                        // received.
                        CEikStatusPaneBase* sp = CEikStatusPaneBase::Current();
                        if ( sp && sp->IsVisible() )
                            {
                            // Show the popup only if status pane is visible
                            // to maintain same kind of functionality as in
                            // navi pane volume control.
                            parent->ShowVolumePopupL();
                            }
                        }
                        
                    if ( iStyle != ESettingsVolumeControl )
                        {
                        TInt event = MAknNavigationObserver::ENaviEventLeftMostItemReached;
                        ReportEventL( 
                            STATIC_CAST( MCoeControlObserver::TCoeEvent, event ) );
                        }
#ifdef RD_ANIMATION_EFFECTS
                    else if (iExtension && (iExtension->iGfxMode == KGfxModeOld))
                        {
                        // only with old volume graphics
                        StartTimerL();
                        }
#endif
                    }
                    
                return EKeyWasConsumed;
                }
            case EKeyRightArrow:
                {
                if ( iExtension && (volumeValue < iExtension->iMaximumValue) )
                    {
                    volumeValue++;
                    SetValue( volumeValue );
                    if ( iStyle != EDynRangePopupVolumeControl && 
                         !iExtension->iNoDraw )
                        {                        
                        DrawNow();
                        }
                    ReportEventL( MCoeControlObserver::EEventStateChanged );                    
                    }
                else
                    {
                    CAknVolumePopup* parent =
                        static_cast<CAknVolumePopup*> ( Parent() );
                    if ( iExtension &&
                         iExtension->iIsOnNaviStack &&
                         parent &&
                         parent->ComponentControl( 5 ) == this )
                        {
                        // Show the volume popup even if volume level is not changed
                        // to indicate that a volume adjustment key event has been
                        // received.
                        CEikStatusPaneBase* sp = CEikStatusPaneBase::Current();
                        if ( sp && sp->IsVisible() )
                            {
                            // Show the popup only if status pane is visible
                            // to maintain same kind of functionality as in
                            // navi pane volume control.
                            parent->ShowVolumePopupL();
                            }
                        }
                        
                    if ( iStyle != ESettingsVolumeControl )
                        {
                        TInt event = MAknNavigationObserver::ENaviEventRightMostItemReached;
                        ReportEventL(
                            STATIC_CAST( MCoeControlObserver::TCoeEvent, event ) );
                        }
#ifdef RD_ANIMATION_EFFECTS
                    else if (iExtension && iExtension->iGfxMode == KGfxModeOld)
                        {
                        // only with old volume graphics
                        StartTimerL();
                        }
#endif
                    }
                    
                return EKeyWasConsumed;
                }
            default:
                break;
            }
        }
    return EKeyWasNotConsumed;
    }

// ----------------------------------------------------------------------------
// CAknVolumeControl::ConstructFromResourceL(TResourceReader& aReader)
// Basic construct from the resource function.
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknVolumeControl::ConstructFromResourceL(
                            TResourceReader& aReader)
    {
    TBool newResourceStructUsed = EFalse;
    
    iStyle=aReader.ReadInt16();
        
    if(iStyle == -1) // 0xfffffff
        {
        newResourceStructUsed = ETrue;
        iStyle=aReader.ReadInt16();
        }
             
    if (iStyle == ESmallPopupVolumeControl || 
        iStyle == ESmallPopupVolumeControlWithPercent )
        {
        iStyle = EDynRangePopupVolumeControl;
        }
    __ASSERT_ALWAYS( iStyle == ESettingsVolumeControl
                     || iStyle == ENaviPaneVolumeControl
                     || iStyle == EPopupVolumeControl
                     || iStyle == EDynRangeSettingsVolumeControl
                     || iStyle == EDynRangeNaviPaneVolumeControl
                     || iStyle == EDynRangePopupVolumeControl,
                     Panic( EAknPanicOutOfRange ) );

    iExtension = new(ELeave) CVolumeExtension;
    iExtension->iTimer = CPeriodic::NewL( CActive::EPriorityStandard );

    TInt value = aReader.ReadInt16();


    TPtrC bmpFile=aReader.ReadTPtrC();
    TFileName filename( bmpFile );
    CompleteWithAppPath( filename );
    TInt bmpId=aReader.ReadInt16();
    TInt bmpMask=aReader.ReadInt16();
    
    if ( iStyle != ESettingsVolumeControl )
        {
        iExtension->iBmpFilename = filename;
        iExtension->iBmpId = bmpId;
        iExtension->iBmpMask = bmpMask;
        
        CreateNaviIconL();
        // Rest of the volume icons will be loaded later.
        }
    
    // Read default min and max volume values from new VOLUME struct used by 
    // new hi-res volume layout resources. These are not defined in older 
    // layout resources so do not read these in this case.
    if( newResourceStructUsed )
        {
        iExtension->iMinimumValue = aReader.ReadInt16();
        iExtension->iMaximumValue = aReader.ReadInt16();
        __ASSERT_DEBUG( iExtension->iMinimumValue < iExtension->iMaximumValue, 
                        Panic( EAknPanicInvalidValue ) );
        
        }
    // setting volume, also dyn range uses 1-10 scale if using old struct
    else if(iStyle == ESettingsVolumeControl || iStyle == EDynRangeSettingsVolumeControl)
        {
        // set scaled value calculation to note the old 1-10 scale with 10 graphics
        iExtension->iOldScaleSettingVolume = ETrue;
        iExtension->iMinimumValue = KVolumeMinValue;
        iExtension->iMaximumValue = KVolumeMaxValue;
        }
    else
        {
        iExtension->iMinimumValue = KVolumeNaviPaneMutedValue;
        iExtension->iMaximumValue = KVolumeMaxValue;
        }
    
    if ( iStyle == EPopupVolumeControl)
        {
        iStyle = EDynRangePopupVolumeControl;
        }
    // SetValue checks iMinimumValue and iMaximumValue which must be read before this
    SetValue( value );
    }

// ----------------------------------------------------------------------------
// CAknVolumeControl::SizeChanged()
// Sets the layout.
// ----------------------------------------------------------------------------
//
void CAknVolumeControl::SizeChanged()
    {
    AknsUtils::RegisterControlPosition( this );
    SetVolumeLayout( iStyle );
    if ( AknLayoutUtils::PenEnabled()&& 
         iExtension &&
         !iExtension->iGrabPoint )
        {
        // Enable drag events, it will then be possible to drag from thumb
        EnableDragEvents();
        
        //Enable dragging to start from thumb and then move outside the slider
        DrawableWindow()->SetPointerGrab( ETrue );
        
        iExtension->iGrabPoint = ETrue;
        }
    }

// ----------------------------------------------------------------------------
// CAknVolumeControl::SetVolumeLayout(TInt aStyle)
// Pure layout function.
// ----------------------------------------------------------------------------
//
void CAknVolumeControl::SetVolumeLayout( TInt aStyle )
    {
    TAknLayoutRect layout;
    TRect rect(Rect());
    TRect parentRect( Rect() );

    switch ( aStyle )
        {
        case ESettingsVolumeControl:
            {
            layout.LayoutRect( rect,
                                AknLayoutScalable_Avkon::volume_set_pane_g1() );
            iStartPos = layout.Rect().iTl;

            if ( iExtension )
                {
                iExtension->CalculateParentRect( aStyle, rect );
                UseExtendedTouchArea();
                return;
                }
            }
            break;

        case ENaviPaneVolumeControl:
        case EDynRangeNaviPaneVolumeControl:        
            {
            MAknsSkinInstance* skin = AknsUtils::SkinInstance();
            TRgb color;
            AknsUtils::GetCachedColor( skin, color, KAknsIIDQsnIconColors,
                                        EAknsCIQsnIconColorsCG7 );
            TRAP_IGNORE ( CreateNaviIconL() );
            if (AknStatuspaneUtils::StaconPaneActive())
                {
                rect = CAknNavigationDecorator::DecoratedControlRect(
                            CAknNavigationDecorator::ENaviVolume );
                layout.LayoutRect( rect,
                        AknLayoutScalable_Avkon::volume_small_pane() );
                iStartPos = TPoint( layout.Rect().iTl.iX ,
                                    layout.Rect().iTl.iY );
                layout.LayoutRect( rect,
                        AknLayoutScalable_Avkon::navi_navi_volume_pane_g1() );
                iBmpPos = TPoint( layout.Rect().iTl.iX ,
                                  layout.Rect().iTl.iY );
                
                }
            else if (AknStatuspaneUtils::IdleLayoutActive())
                {
                layout.LayoutRect( rect,
                    AknLayoutScalable_Avkon::volume_small_pane() );
                iStartPos = TPoint( layout.Rect().iTl.iX - rect.iTl.iX,
                                    layout.Rect().iTl.iY );

                layout.LayoutRect( rect,
                    AknLayoutScalable_Avkon::navi_navi_volume_pane_g1() );
                iBmpPos = TPoint( layout.Rect().iTl.iX - rect.iTl.iX,
                                  layout.Rect().iTl.iY );

                }
            else if ( AknStatuspaneUtils::SmallLayoutActive() )
                {
                //Get the volume strength indicator layout
                layout.LayoutRect( rect,
                    AknLayoutScalable_Avkon::volume_small2_pane() );
                //volume strength indicator start position
                iStartPos = TPoint( layout.Rect().iTl.iX, 
                                    layout.Rect().iTl.iY );
                
                //Bitmap layout
                layout.LayoutRect( parentRect, 
                    AknLayoutScalable_Avkon::status_small_volume_pane_g1()
                    );
                iBmpPos = TPoint( layout.Rect().iTl.iX,
                                  layout.Rect().iTl.iY );
                }
            else
                {
                layout.LayoutRect( rect,
                    AknLayoutScalable_Avkon::volume_small_pane() );
                iStartPos = TPoint( layout.Rect().iTl.iX - rect.iTl.iX,
                                    layout.Rect().iTl.iY );
                layout.LayoutRect( rect,
                    AknLayoutScalable_Avkon::navi_navi_volume_pane_g1() );
                iBmpPos = TPoint( layout.Rect().iTl.iX - rect.iTl.iX,
                                  layout.Rect().iTl.iY );
                }
            if ( iBitmap != NULL )
                {
                AknIconUtils::SetIconColor( iBitmap, color );
                AknIconUtils::SetSize(iBitmap, layout.Rect().Size());
                if ( iExtension )
                    {
                    iExtension->iMuteRect = layout.Rect();
                    }
                }
            }
            break;

        case EPopupVolumeControl:
            // just use given rect!
            iStartPos = TPoint( rect.iTl.iX, rect.iTl.iY ); 
            break;

        default:
            // does not happen
            break;
        }

    if ( iExtension )
        {
        iExtension->CalculateParentRect( aStyle, parentRect );
        }
    }

// ----------------------------------------------------------------------------
// CAknVolumeControl::Draw(const TRect& aRect) const
// Implementation of automatically called control drawing function from 
// CCoeControl.
// ----------------------------------------------------------------------------
//
void CAknVolumeControl::Draw( const TRect& /*aRect*/ ) const
    {
    if ( iExtension->iNoDraw )
        {
        return;
        }
    /*
    * If there are volume graphics in active skin, use those to be compatible 
    * with 2.6 skins, then check for svg graphics. If that fails, draw using 
    * legacy code
    */
    if ( iExtension && !iExtension->iHasBeenDrawn )
        {
        TRAP_IGNORE( iExtension->LoadBitmapsL( iStyle, Rect()
                                               /*iAvkonAppUi->ApplicationRect() */));
        iExtension->iHasBeenDrawn = ETrue;
        }
    
    if( iExtension && iExtension->iGfxMode == KGfxModeNew)
        {
        DrawDynRangeSettingsStyleVolumeControl( iExtension->iParentRect );
        }
    else if( iExtension )
        {
            switch( iStyle )
            {
            case ESettingsVolumeControl:
                DrawSettingsStyleVolumeControl( Rect() );
                break;
            default:
                if( AknsUtils::AvkonSkinEnabled() )
                    {
                    DrawSkinnedDefaultStyleVolumeControl( Rect() );
                    }
                else
                    {
                    DrawDefaultStyleVolumeControl( Rect() );
                    }
                break;
            }    
        }
    
    }

// ----------------------------------------------------------------------------
// CAknVolumeControl::DrawSettingsStyleVolumeControl
//
// ----------------------------------------------------------------------------
//
void CAknVolumeControl::DrawSettingsStyleVolumeControl( const TRect& aRect ) const
    {
    CWindowGc& gc=SystemGc();
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* edCc = AknsDrawUtils::ControlContext( this );
    AknsDrawUtils::Background( skin, edCc, this, gc, aRect );

    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.SetPenStyle(CGraphicsContext::ENullPen);

    if (AknsUtils::AvkonSkinEnabled() && iExtension)
        {
        gc.SetBrushStyle(CGraphicsContext::ENullBrush);
        iExtension->DrawSvgSettingsVolume( iExtension->iParentRect, 
                                           gc, 
                                           ScaledValue() );
        return;
        }
    else
        {
        //I'm not sure whether this branch is useless or not ,so I didn't delete this branch.
        TInt colorIndex = 0;
        for (TInt i=0; i < KVolumeLevels; i++) // there is ten bars
            {
            if ( i < ScaledValue() )
                {
                colorIndex = 1;
                }
            else
                {
                colorIndex = 0;
                }
            TRect rect = Rect();
            TAknWindowLineLayout layout = AKN_LAYOUT_TABLE_Setting_volume_pane_elements_SUB_TABLE_0(i + 1, colorIndex);
            TAknLayoutRect volumeBarLayout;
            volumeBarLayout.LayoutRect(rect, layout);
            if ( iExtension && AknLayoutUtils::PenEnabled() )
                {
                // Store rect for every level. We can then decide what level was clicked
                iExtension->iVolumeLevels[i] = volumeBarLayout.Rect();
                }
            gc.SetBrushColor( volumeBarLayout.Color() );
            gc.DrawRect( volumeBarLayout.Rect() );
            }
        }
    }


// ----------------------------------------------------------------------------
// CAknVolumeControl::DrawDynRangeSettingsStyleVolumeControl
//
// ----------------------------------------------------------------------------
//
void CAknVolumeControl::DrawDynRangeSettingsStyleVolumeControl( 
    const TRect& aVolumeArea ) const
    {
    // !!! Assumptions used: Sizes of iExtension->iInActiveIcons[0],
    // iExtension->iActiveIcons[0], corresponding masks and 
    // aVolumeArea are identical.
    CWindowGc& gc=SystemGc();
    if ( !Background() )
        {
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        MAknsControlContext* edCc = AknsDrawUtils::ControlContext( this );
        
        if ( iStyle != EDynRangePopupVolumeControl )
            {        
            AknsDrawUtils::Background( skin, edCc, this, gc, aVolumeArea );
            }
        }
    else
        {
        Background()->Draw( gc, *this, aVolumeArea );
        }

    // Only skin enabled version should exist
    TRect iconRect(0,0, iExtension->iActiveIcons[0]->SizeInPixels().iWidth,
                        iExtension->iActiveIcons[0]->SizeInPixels().iHeight );

    TRect activeRect;// rect area used for active volume slider icon
    TRect inactiveRect;// rect area used for inactive volume slider icon
    
    CalcVolumeIconAreas( Value(), 
                         aVolumeArea, 
                         activeRect, 
                         inactiveRect );
    
    // Area of the actual icon to be drawn in rect area
    TRect activeIcon( 0, 0, 
                      activeRect.iBr.iX - activeRect.iTl.iX, 
                      activeRect.iBr.iY - activeRect.iTl.iY ); 
    
    // Area of the actual icon to be drawn in rect area
    TRect inactiveIcon( inactiveRect.iTl.iX - aVolumeArea.iTl.iX, 
                        0,
                        inactiveRect.iBr.iX - aVolumeArea.iTl.iX,
                        inactiveRect.iBr.iY - aVolumeArea.iTl.iY );

    gc.BitBltMasked( activeRect.iTl, 
                     iExtension->iActiveIcons[0], 
                     activeIcon, 
                     iExtension->iActiveMasks[0], ETrue );

    gc.BitBltMasked( inactiveRect.iTl, 
                     iExtension->iInActiveIcons[0], 
                     inactiveIcon, 
                     iExtension->iInActiveMasks[0], ETrue );
    // Draw speaker or mute icon
    if ( ( iBitmap != NULL ) && ( iMaskBitmap != NULL ) )
        {
        TRect bmpRect(TPoint(0,0),TSize(iBitmap->SizeInPixels()));
        if (iStyle == EDynRangeNaviPaneVolumeControl)  // popup handles icons itself
            {
            gc.BitBltMasked(iBmpPos, iBitmap, bmpRect, iMaskBitmap, ETrue);
            }
        }    
    }


// ----------------------------------------------------------------------------
// CAknVolumeControl::CalcVolumeIconAreas()
//
// ----------------------------------------------------------------------------
//
void CAknVolumeControl::CalcVolumeIconAreas( const TInt aVolume, 
                                             const TRect& aDrawArea,
                                             TRect& aActiveRect, 
                                             TRect& aInactiveRect ) const
    {
    // Calculate drawing area split between active and inactive icon areas in percentage
    // it is caculating the activeRatio by iOldScaleSettingVolume
    // it is very important for drawing the volumecontrol
    // because the tester requires there must be at least one piece of shadow in it,
    // if we set the iMinimumValue not as (iMinimunValue+1) in HandlePointerEventL and 
    // draw the aActiveRect like this, all things go well. 
    TInt activeRatio;
    if( !iExtension->iOldScaleSettingVolume )
        {
        activeRatio = ( aVolume - iExtension->iMinimumValue ) * 100
                        / ( iExtension->iMaximumValue - iExtension->iMinimumValue );
        }
    
    else
        {
        activeRatio = aVolume * 10;
        }
    aActiveRect.iTl.iX = aDrawArea.iTl.iX;
    aActiveRect.iTl.iY = aDrawArea.iTl.iY;
    aActiveRect.iBr.iX = aDrawArea.iTl.iX + ( aDrawArea.iBr.iX - aDrawArea.iTl.iX ) * activeRatio / 100;
    aActiveRect.iBr.iY = aDrawArea.iBr.iY;
    
    aInactiveRect.iTl.iX = aActiveRect.iBr.iX /*+ 1*/;
    aInactiveRect.iTl.iY = aDrawArea.iTl.iY;
    aInactiveRect.iBr.iX = aDrawArea.iBr.iX;
    aInactiveRect.iBr.iY = aDrawArea.iBr.iY;
    }
    
    
// ----------------------------------------------------------------------------
// CAknVolumeControl::DrawDefaultStyleVolumeControl()
// NON SKINNED DRAW!
// ----------------------------------------------------------------------------
//
void CAknVolumeControl::DrawDefaultStyleVolumeControl( const TRect& /*aRect*/ ) const
    {
    CWindowGc& gc=SystemGc();
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    
    //I'm not sure whether this branch is useless or not ,so I didn't delete this branch.
    TInt volumeLIndex;
    TAknLayoutRect layoutRect;

    if ( AknStatuspaneUtils::IdleLayoutActive() )
        {
        volumeLIndex = 0;
        }
    else
        {
        volumeLIndex = 1;
        }

    TRect parent( TSize( 0, 0 ) );
    TRect volumeNaviPaneRect;   // volume_navi_pane

    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.SetPenStyle(CGraphicsContext::ENullPen); // column drawing should have no outline
    TRgb c1, c2;

    if (iStyle == ENaviPaneVolumeControl)
        {
        layoutRect.LayoutRect( parent, AKN_LAYOUT_WINDOW_volume_navi_pane( volumeLIndex ) );
        volumeNaviPaneRect = layoutRect.Rect();

        layoutRect.LayoutRect( volumeNaviPaneRect, AKN_LAYOUT_TABLE_Volume_pane_elements__one_( 0, 0 ) );
        c1 = layoutRect.Color();
        layoutRect.LayoutRect( volumeNaviPaneRect, AKN_LAYOUT_TABLE_Volume_pane_elements__one_( 0, 1 ) );
        c2 = layoutRect.Color();
        }
    else  // Popup volume needs different colors
        {
        layoutRect.LayoutRect( Rect(), AKN_LAYOUT_TABLE_Volume_pane_elements__one_( 0, 0 ) );
        c1 = layoutRect.Color();
        layoutRect.LayoutRect( Rect(), AKN_LAYOUT_TABLE_Setting_volume_pane_elements_SUB_TABLE_0( 2, 0 ) );
        c2 = layoutRect.Color();
        }

    for (TInt i=0; i < KVolumeLevels; i++) // there is ten bars
        {
        if ( i < ScaledValue())
            {
            gc.SetBrushColor(c1);
            }
        else
            {
            gc.SetBrushColor(c2);
            }

        if ( iStyle != ENaviPaneVolumeControl )
            {
            TRect tempRect( 0, 0, 0, 0 );
            layoutRect.LayoutRect( tempRect, AKN_LAYOUT_TABLE_Volume_pane_elements__one_( i, 0 ) );
            TPoint start( iStartPos.iX + layoutRect.Rect().iTl.iX, iStartPos.iY + layoutRect.Rect().iTl.iY );
            TSize size( layoutRect.Rect().Size() );
            gc.DrawRect( TRect( start, size ) );

            if ( AknLayoutUtils::PenEnabled() )
                {
                // Store rect for every level. We can then decide what level was clicked
                iExtension->iVolumeLevels[i] = layoutRect.Rect();
                }
            }
        else
            {
            layoutRect.LayoutRect( volumeNaviPaneRect, AKN_LAYOUT_TABLE_Volume_pane_elements__one_( i, 0 ) );
            gc.DrawRect( layoutRect.Rect() );

            if ( AknLayoutUtils::PenEnabled() )
                {
                // Store rect for every level. We can then decide what level was clicked
                iExtension->iVolumeLevels[i] = layoutRect.Rect();
                }
            }
        }
    
    }
    
    
// ----------------------------------------------------------------------------
// CAknVolumeControl::DrawSkinnedDefaultStyleVolumeControl()
//
// ----------------------------------------------------------------------------
//
void CAknVolumeControl::DrawSkinnedDefaultStyleVolumeControl( 
    const TRect& /*aRect*/ ) const
    {
    CWindowGc& gc=SystemGc();
    // No test on AknsUtils::AvkonSkinEnabled() because this control is used in
    // the navipane Skinned bitmap.
    if ( !Background() )
        {
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        AknsDrawUtils::Background( skin, 
                               AknsDrawUtils::ControlContext( this ), 
                               this, 
                               gc, 
                               Rect() );
        }
    else
        {
        Background()->Draw( gc, *this, Rect() );
        }


    // Draw speaker or mute icon
    if ( ( iBitmap != NULL ) && ( iMaskBitmap != NULL ) )
        {
        TRect bmpRect(TPoint(0,0),TSize(iBitmap->SizeInPixels()));
        if (iStyle == ENaviPaneVolumeControl)  // popup handles icons itself
            {
            gc.BitBltMasked(iBmpPos, iBitmap, bmpRect, iMaskBitmap, ETrue);
            }
        }
    if ( iExtension )
        {
        if ( ( iStyle != ENaviPaneVolumeControl ) || 
               !( iExtension->iFlags & KVolumeNaviPaneMuted ) )
            {
            iExtension->DrawSvgSmallVolume( iStyle,
                                            iExtension->iParentRect,
                                            gc,
                                            ScaledValue() );
            return;
            }
        }

    }


// ----------------------------------------------------------------------------
// CAknVolumeControl::ExtensionInterface()
//
// ----------------------------------------------------------------------------
//
EXPORT_C void* CAknVolumeControl::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

// ----------------------------------------------------------------------------
// CAknVolumeControl::HandlePointerEventL()
// Processes Volumecontrol's pointer event's.
// This function requests what volume level contains the clicked point
// And then set's new volumelevel according to that.
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknVolumeControl::HandlePointerEventL(
                        const TPointerEvent& aPointerEvent)
    {
    if ( AknLayoutUtils::PenEnabled() && iExtension )
        {
        if ( IsDimmed() )
            {
            iExtension->iFlags &= ~KVolumeButtonDown;
            return;
            }

        TRect rect;
        if ( iExtension->iUseExtendedTouchArea )
            {
            rect = iExtension->iTouchArea;
            }
        else
            {
            AknLayoutUtils::LayoutMetricsRect( 
                    AknLayoutUtils::EApplicationWindow, rect );            
            }

        TInt level = KVolumeLevelNotFound;
        if( !rect.Contains( aPointerEvent.iPosition ) )
            {
            level = Value();
            }
        else
            {
            level = iExtension->GetVolumeLevelByPosition( iStyle, 
                aPointerEvent.iPosition, rect );
            }

        TBool valueChanged( EFalse ); // if pointerevent changes volume level                
        
        switch( aPointerEvent.iType )
            {
            case TPointerEvent::EButton1Down:
                {
                MTouchFeedback* feedback = MTouchFeedback::Instance();
                if ( feedback )
                    {
                    feedback->InstantFeedback( ETouchFeedbackBasicSlider );
                    }
                }
            case TPointerEvent::EDrag:
            case TPointerEvent::EButtonRepeat: // fall trough
                {
                // click was inside VolumeControl
                if ( rect.Contains( aPointerEvent.iPosition ) )
                    {
                    // Pointer down in volumeControl
                    iExtension->iFlags |= KVolumeButtonDown;
                    valueChanged = ETrue;                    
                    }
                Window().RequestPointerRepeatEvent( KScrollRepeatTimeout, rect );
                }
                break;

            case TPointerEvent::EButton1Up:
                {
                // if pointer was putted down inside VolumeControl
                iExtension->iFlags &= ~KVolumeButtonDown;
                }
                break;
            
            default:
                break;                
            }        
        // get clicked volume level depending type of volumebar
        if ( valueChanged )
            {            
            if ( aPointerEvent.iType == TPointerEvent::EButton1Down )
                {
                iExtension->iReduce = ( level <= Value() );
                iExtension->iOldLevel = level;
                }
            if ( level < Value() )
                {
                iExtension->iReduce = ETrue;
                }
            else if ( level > Value() + 1 )
                {
                iExtension->iReduce = ( level < iExtension->iOldLevel );                
                }
            else if ( iExtension->iReduce && 
                ( level == Value() || level == Value() + 1 ) )
                {
                level--;
                }
            }
        //value step change
        // correction should not be done when outside of control
        if( iExtension->iFlags & KVolumeStepChange )
            {
            if( level > Value() )
                {
                level = Value() + 1;
                }
            else if( level < Value() )
                {
                level = Value() - 1;
                }            
            }//value step change over
        if ( level < iExtension->iMinimumValue )
           {
           level = iExtension->iMinimumValue;
           }
       else if ( level > iExtension->iMaximumValue )
           {
           level = iExtension->iMaximumValue;
           }
        
        iExtension->iOldLevel = level;
        
        if ( level == KVolumeLevelMuteTapped )
            {
            if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
                {
                // mute indicator was tapped
                if ( Value() == iExtension->iMinimumValue )
                    {
                    // restore saved value
                    level = iExtension->iStoredLevel; 
                    iExtension->iStoredLevel = iExtension->iMinimumValue;
                    }
                else
                    {
                    // mute
                    iExtension->iStoredLevel = Value();
                    level = iExtension->iMinimumValue;
                    }
                valueChanged = ETrue;
                }
            else
                {
                // ignore 
                return;
                }
            }

        if ( valueChanged && (level != iValue) )
            {
            if ( aPointerEvent.iType == TPointerEvent::EDrag || 
                 aPointerEvent.iType == TPointerEvent::EButtonRepeat )
                {
                MTouchFeedback* feedback = MTouchFeedback::Instance();
                if ( feedback )
                    {
                    feedback->InstantFeedback( this, ETouchFeedbackBasicSlider );    
                    }                
                }
            
            iValue = level;
            SetValue(iValue);
            ReportEventL(MCoeControlObserver::EEventStateChanged);
            DrawDeferred();
            }
        }
    }


// ----------------------------------------------------------------------------
// CAknVolumeControl::HandleNaviDecoratorEventL()
// Observes navigation decorator's events
// currently possibly events are right and left arrow presses by pointer
// increments/decrements volumelevel depending on event.
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknVolumeControl::HandleNaviDecoratorEventL( TInt aEventID )
    {
    if ( AknLayoutUtils::PenEnabled() )
        {
        switch(aEventID)
            {
            case MAknNaviDecoratorObserver::EAknNaviDecoratorEventLeftTabArrow:
                {
                if ( iExtension && iValue > iExtension->iMinimumValue )
                    {
                    iValue -= 1;
                    SetValue( iValue );
                    ReportEventL(MCoeControlObserver::EEventStateChanged);
                    DrawDeferred();
                    }
                }
                break;

            case MAknNaviDecoratorObserver::EAknNaviDecoratorEventRightTabArrow:
                if ( iExtension && iValue < iExtension->iMaximumValue )
                    {
                    iValue+=1;
                    SetValue(iValue);
                    ReportEventL(MCoeControlObserver::EEventStateChanged);
                    DrawDeferred();
                    }
                break;

            default:
                break;
            }
        }
    }


// ----------------------------------------------------------------------------
// CAknVolumeControl::IndicationDrawCallbackL()
//
// ----------------------------------------------------------------------------
//
TInt CAknVolumeControl::IndicationDrawCallbackL( TAny* aThis )
    {
    CAknVolumeControl* volumeControl =
        static_cast<CAknVolumeControl*>(aThis);

    volumeControl->SmallDirectionIndicationL();

    return KErrNone;
    }

// ----------------------------------------------------------------------------
// CAknVolumeControl::SmallDirectionIndicationL()
//
// ----------------------------------------------------------------------------
//
void CAknVolumeControl::SmallDirectionIndicationL()
    {
    // We must calculate redraw area either the biggest or the smallest
    // volume bar

    TRect rect;
    TPoint p;
    TRect srcRect;
    TRect bmpRect;

    // check the icon or bitmap is not null
    TBool checkNull(EFalse);

    // Cancel blinking if moved from min or max position, unless the area is
    // blank. Then redraw and cancel after redraw
    if( iExtension && iValue != iExtension->iAnimatedEffectValue &&
        iExtension->iEffectTimerCount%2 == 0)
        {
        iExtension->iTimer->Cancel();
        return;
        }

    // CDMA case
    if( iExtension && iExtension->iAnimatedEffectValue == 0 )
        {
        iExtension->iAnimatedEffectValue += 1;
        }
    
    TInt scaledValue = ScaledValue(); // scale the value to make possible the dynamic range
    if ( iExtension && iStyle == ESettingsVolumeControl )
        {
        rect = iExtension->RectFromLayout( iExtension->iParentRect,
            AknLayoutScalable_Avkon::volume_set_pane_g(
                            scaledValue - 1 ));
        if (AknsUtils::AvkonSkinEnabled() && iExtension)
            {
            p = TPoint( rect.iTl.iX, rect.iTl.iY );
            srcRect = TRect(0, 0, rect.Width(), rect.Height());
            }
        }
    else  // navipane volume control, popup volume control
        {
        if ( iBitmap != NULL )
            {
            bmpRect = TRect(TPoint(0,0),TSize(iBitmap->SizeInPixels()));
            }
        
        if ( iExtension && AknStatuspaneUtils::SmallLayoutActive() )
            {
            rect = iExtension->RectFromLayout( iExtension->iParentRect,
                AknLayoutScalable_Avkon::volume_small2_pane_g(
                            scaledValue - 1 ) );
            }
        else if( iExtension )
            {
            rect = iExtension->RectFromLayout( iExtension->iParentRect,
                        AknLayoutScalable_Avkon::volume_small_pane_g(
                                scaledValue - 1 ) );
            }
            
        p = TPoint( rect.iTl.iX, rect.iTl.iY );
        srcRect = TRect(0, 0, rect.Width(), rect.Height());
        }

    Window().Invalidate(rect);
    ActivateGc();

    Window().BeginRedraw(rect);
    CWindowGc& gc=SystemGc();
    if( !Background() )
        {
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();

        MAknsControlContext* edCc = AknsDrawUtils::ControlContext( this );
        AknsDrawUtils::Background( skin, edCc, this, gc, rect);        
        }
    else
        {
        Background()->Draw( gc, *this, rect );
        }
    if( iExtension && iExtension->iEffectTimerCount%2 == 1)
        {
        checkNull = ( iExtension->iActiveIcons[
                        scaledValue-1] != NULL )
                    && ( iExtension->iActiveMasks[
                        scaledValue-1] != NULL );
        if (iStyle==ESettingsVolumeControl)
            {
            gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
            gc.SetPenStyle(CGraphicsContext::ENullPen);
            if ( AknsUtils::AvkonSkinEnabled() && iExtension
                 && checkNull )
                {
                gc.SetBrushStyle(CGraphicsContext::ENullBrush);
                gc.BitBltMasked( p, 
                                 iExtension->iActiveIcons[
                                    scaledValue-1],
                                 srcRect,
                                 iExtension->iActiveMasks[
                                    scaledValue-1],
                                 ETrue);
                }
            }
        else
            {
            if ( iExtension && checkNull )
                {
                gc.BitBltMasked( p, 
                                 iExtension->iActiveIcons[
                                    scaledValue-1],
                                 srcRect,
                                 iExtension->iActiveMasks[
                                    scaledValue-1],
                                 ETrue);
                }
            }
        }
    Window().EndRedraw();
    DeactivateGc();
    if( iExtension )
        {
        iExtension->iEffectTimerCount++;
        }

    // Stop timer if done normal-inverted-normal-inverted-normal sequence
    //  or the user has changed the value from the min or max
    if( iExtension && 
        ( iExtension->iEffectTimerCount > 3 || iExtension->iAnimatedEffectValue != iValue ) )
        {
        iExtension->iTimer->Cancel();
        }

    }

// ----------------------------------------------------------------------------
// CAknVolumeControl::StartTimerL()
//
// ----------------------------------------------------------------------------
//
void CAknVolumeControl::StartTimerL()
    {
    if(iExtension->iTimer->IsActive())
        return; // do not re-start as we have the feedback ongoing

    iExtension->iEffectTimerCount = 0;
    iExtension->iAnimatedEffectValue = ScaledValue();

    const TTimeIntervalMicroSeconds32 KVolumeFeedbackActionTime = 160*1000;

    TCallBack callback(IndicationDrawCallbackL,this);
    iExtension->iTimer->Start(KVolumeFeedbackActionTime,
        KVolumeFeedbackActionTime, callback);
    }


// ----------------------------------------------------------------------------
// CAknVolumeControl::CreateNaviIconL()
// (Re)creates the navi pane icon.
// ----------------------------------------------------------------------------
//
void CAknVolumeControl::CreateNaviIconL()
    {
    if ( !iExtension )
        {
        return;
        }

    TInt bmpId = iExtension->iBmpId;
    TInt bmpMask = iExtension->iBmpMask;

    // We compare to avkon.rh STRUCT VOLUME default values
    if ( iExtension->iBmpFilename.CompareF(_L("")) != 0 )
        {
        MAknsSkinInstance *skin = AknsUtils::SkinInstance();
        if ( iExtension->iFlags & KVolumeNaviPaneMuted )
            {
            delete iBitmap;
            iBitmap = NULL;
            delete iMaskBitmap;
            iMaskBitmap = NULL;
            AknsUtils::CreateColorIconL(skin,
                                    KAknsIIDQgnIndiSpeakerMuted,
                                    KAknsIIDQsnTextColors,
                                    EAknsCIQsnTextColorsCG19,
                                    iBitmap,
                                    iMaskBitmap,
                                    KAvkonBitmapFile,                                 
                                    EMbmAvkonQgn_indi_speaker_muted,
                                    EMbmAvkonQgn_indi_speaker_muted_mask,
                                    KRgbWhite );
            }
        else
            {
            if ( bmpId != -1 )
                {
                delete iBitmap;
                iBitmap = NULL;
                delete iMaskBitmap;
                iMaskBitmap = NULL;

                if ( bmpMask != -1 )
                    {
                    AknsUtils::CreateColorIconL( skin,
                            KAknsIIDQgnIndiSpeakerActive,
                            KAknsIIDQsnTextColors,
                            EAknsCIQsnTextColorsCG19,
                            iBitmap,
                            iMaskBitmap,
                            iExtension->iBmpFilename,                                 
                            bmpId,
                            bmpMask,
                            KRgbWhite );
                    // sizes are set in setlayoutl
                    }
                else
                    {
                    iBitmap = AknIconUtils::CreateIconL(
                                iExtension->iBmpFilename, bmpId );
                    }
                }
            }
        }
    }



// ----------------------------------------------------------------------------
// CAknVolumeControl::ScaledValue()
//
// ----------------------------------------------------------------------------
//
TInt CAknVolumeControl::ScaledValue() const
    {
    TInt scaledValue = iValue;
    if(iExtension && !iExtension->iOldScaleSettingVolume)
        {
        scaledValue = 10 * ( iValue - iExtension->iMinimumValue ) 
           / ( iExtension->iMaximumValue - iExtension->iMinimumValue );
        }
    return scaledValue;
    }


// ----------------------------------------------------------------------------
// CAknVolumeControl::UseExtendedTouchArea
//
// ----------------------------------------------------------------------------
//
void CAknVolumeControl::UseExtendedTouchArea()
    {
    TRect touchActiveArea;
    TPoint winPosition( Window().AbsPosition() );
    TRect appRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EApplicationWindow,
            appRect );
    TAknLayoutRect mainpaneRect;
    mainpaneRect.LayoutRect( appRect, AknLayoutScalable_Apps::main_pane(3) );
    touchActiveArea = mainpaneRect.Rect();

    touchActiveArea.Move( touchActiveArea.iTl.iX - winPosition.iX,
            touchActiveArea.iTl.iY - winPosition.iY );
    iExtension->iTouchArea = touchActiveArea;
    iExtension->iUseExtendedTouchArea = ETrue;
    }


// ----------------------------------------------------------------------------
// CVolumeExtension::
//
// ----------------------------------------------------------------------------
//
CVolumeExtension::CVolumeExtension():
    iMinimumValue( KVolumeNaviPaneMutedValue ), 
    iMaximumValue( KVolumeMaxValue ), 
    iGfxMode( KGfxModeNotLoaded ),
    iOldScaleSettingVolume(EFalse),
    iGrabPoint( EFalse )
    {
    iFlags |= KVolumeStepChange;
    }

// ----------------------------------------------------------------------------
// CAknVolumeControl::HandleResourceChange()
// Handles a change to CAknVolumeControl's resources.
// Currently it handles the change of Skins
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknVolumeControl::HandleResourceChange(TInt aType)
    {
    if ((aType==KAknsMessageSkinChange) || (aType == KEikColorResourceChange)
            || (aType == KEikDynamicLayoutVariantSwitch))
        {
        SizeChanged();
        if ( iExtension )
            {
            iExtension->iHasBeenDrawn = EFalse;
            }
        }
    CCoeControl::HandleResourceChange( aType );
    }
    
void CAknVolumeControl::SuppressDrawing( TBool aSuppress )
    {
    if ( iExtension )
        {
        iExtension->iNoDraw = aSuppress;    
        }    
    }

// ----------------------------------------------------------------------------
// CVolumeExtension::~CVolumeExtension
//
// ----------------------------------------------------------------------------
//
CVolumeExtension::~CVolumeExtension()
    {
    DeleteBitmaps();
    if(iTimer && iTimer->IsActive())
        iTimer->Cancel();
    delete iTimer;
    }

// ----------------------------------------------------------------------------
// CVolumeExtension::UseSvgDrawing
//
// ----------------------------------------------------------------------------
//
TBool CVolumeExtension::UseSvgDrawing()
    {
    return ETrue;
    }

// ----------------------------------------------------------------------------
// CVolumeExtension::DeleteBitmaps
//
// ----------------------------------------------------------------------------
//
void CVolumeExtension::DeleteBitmaps()
    {
    TInt i;

    for( i = 0; i < KVolumeLevels; i++)
        {
        delete iActiveIcons[i];
        iActiveIcons[i] = NULL;
        delete iActiveMasks[i];
        iActiveMasks[i] = NULL;
        delete iInActiveIcons[i];
        iInActiveIcons[i] = NULL;
        delete iInActiveMasks[i];
        iInActiveMasks[i] = NULL;
        }
    }

// ----------------------------------------------------------------------------
// CVolumeExtension::SetIconSizes
//
// ----------------------------------------------------------------------------
//
void CVolumeExtension::SetIconSizes( TInt aStyle, const TRect& aParent ) const
    {
    TSize s;

    if( iGfxMode == KGfxModeOld )
        {
        for( TInt i = 0; i < KVolumeLevels; i++)
            {
            switch ( aStyle )
                {
                case ESettingsVolumeControl:
                    s = RectFromLayout( aParent,
                        AknLayoutScalable_Avkon::volume_set_pane_g(i) ).Size();
                    break;
                case ENaviPaneVolumeControl:
                    {
                    TRect parentRect(aParent);
                    if ( AknStatuspaneUtils::SmallLayoutActive() )
                        {
                        parentRect = RectFromLayout(
                                    parentRect,
                                    AknLayoutScalable_Avkon::volume_small2_pane()
                                    );
                        s = RectFromLayout(
                                parentRect,
                                AknLayoutScalable_Avkon::volume_small2_pane_g( i ) 
                                ).Size();
                        }
                    else
                        {
                        parentRect = RectFromLayout(
                                    parentRect,
                                    AknLayoutScalable_Avkon::volume_small_pane()
                                    );
                        s = RectFromLayout(
                                parentRect,
                                AknLayoutScalable_Avkon::volume_small_pane_g(i) 
                                ).Size();
                        }
                    }
                    break;
                case EPopupVolumeControl:
                    s = RectFromLayout(
                            aParent,
                            AknLayoutScalable_Avkon::volume_small_pane_g( i ) 
                            ).Size();
                    break;
                case EDynRangeSettingsVolumeControl:
                case EDynRangeNaviPaneVolumeControl:
                case EDynRangePopupVolumeControl:
                    s.iHeight = iParentRect.Height();
                    s.iWidth = iParentRect.Width();
                    break;
                default:
                    // can not happen
                    break;
                }
            if ( iActiveIcons[i] != NULL )
                {
                AknIconUtils::SetSize( iActiveIcons[i],
                                    s, EAspectRatioNotPreserved );
                }
            if ( iInActiveIcons[i] != NULL )
                {
                AknIconUtils::SetSize( iInActiveIcons[i],s,
                                        EAspectRatioNotPreserved );
                }
            }
        }
    else
        {
        s.iHeight = iParentRect.Height();
        s.iWidth = iParentRect.Width();

        if ( iActiveIcons[0] != NULL )
            {
            AknIconUtils::SetSize( iActiveIcons[0], s, 
                                   EAspectRatioNotPreserved );
            }
        if ( iInActiveIcons[0] != NULL )
            {
            AknIconUtils::SetSize( iInActiveIcons[0], s,
                                   EAspectRatioNotPreserved );
            }

        }
   
    }

// ----------------------------------------------------------------------------
// CVolumeExtension::LoadBitmapsL
//
// Multiple fallback levels for loading bitmaps:
// 1. Try loading new bitmaps using skin (icons will be scaled)
// 2. Try loading old bitmaps using skin (either small or large icons)
// 3. Load new bitmaps without skins (icons will be scaled)
// ----------------------------------------------------------------------------
//
void CVolumeExtension::LoadBitmapsL( TInt aStyle, const TRect& aParent )
    {
    DeleteBitmaps();

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    TInt err = -1;// Init to any value but 0

//TODO: Verify that new skins are available and loaded

    // 1. Load new with skin           
    TRAP( err, TryLoadBitmapsSkinnedL( skin ) );
    iGfxMode = KGfxModeNew;

    // 2. Load old with skin
    if( err ) 
        {
        switch( aStyle ) 
            {
            case ESettingsVolumeControl:
                TRAP( err, TryLoadBitmapsDefaultLargeL( skin ) );
                iGfxMode = KGfxModeOld;
                break;
            case ENaviPaneVolumeControl:
            case EPopupVolumeControl:
                TRAP( err, TryLoadBitmapsDefaultSmallL( skin ) );
                iGfxMode = KGfxModeOld;
                break;
            }
        }
    
    // 3. Load new without skin
    if( err )
        {
        iGfxMode = KGfxModeNotLoaded;
        TRAP( err, TryLoadBitmapsNoSkinL() ); // Last chance - must succeed.
        iGfxMode = KGfxModeNew;
        }
    // There absolutely are no whatsoever icons available  -> abort!
    User::LeaveIfError( err );

    SetIconSizes( aStyle, aParent );
    }


// ----------------------------------------------------------------------------
// CVolumeExtension::TryLoadBitmapsSkinnedL
//
// ----------------------------------------------------------------------------
//
void CVolumeExtension::TryLoadBitmapsSkinnedL( MAknsSkinInstance* aSkin )
    {
    AknsUtils::CreateIconL(
        aSkin,
        KAknsIIDQgnGrafVolumeSetOff,
        iInActiveIcons[0],
        iInActiveMasks[0],
        KNullDesC, // Disables fallback
        EMbmAvkonQgn_graf_volume_small_off,
        EMbmAvkonQgn_graf_volume_small_off_mask ) ;

    AknsUtils::CreateIconL(
        aSkin,
        KAknsIIDQgnGrafVolumeSetOn,
        iActiveIcons[0],
        iActiveMasks[0],
        KNullDesC, // Disables fallback
        EMbmAvkonQgn_graf_volume_small_on,
        EMbmAvkonQgn_graf_volume_small_on_mask );
    }


// ----------------------------------------------------------------------------
// CVolumeExtension::
//
// ----------------------------------------------------------------------------
//
void CVolumeExtension::TryLoadBitmapsDefaultSmallL( MAknsSkinInstance* aSkin )
    {
    const TAknsItemID iconOffSkinIDArray[] = 
        {
        KAknsIIDQgnGrafVolumeSmall1Off,
        KAknsIIDQgnGrafVolumeSmall2Off,
        KAknsIIDQgnGrafVolumeSmall3Off,
        KAknsIIDQgnGrafVolumeSmall4Off,
        KAknsIIDQgnGrafVolumeSmall5Off,
        KAknsIIDQgnGrafVolumeSmall6Off,
        KAknsIIDQgnGrafVolumeSmall7Off,
        KAknsIIDQgnGrafVolumeSmall8Off,
        KAknsIIDQgnGrafVolumeSmall9Off,
        KAknsIIDQgnGrafVolumeSmall10Off
        };
    const TAknsItemID iconOnSkinIDArray[] = 
        {
        KAknsIIDQgnGrafVolumeSmall1On,
        KAknsIIDQgnGrafVolumeSmall2On,
        KAknsIIDQgnGrafVolumeSmall3On,
        KAknsIIDQgnGrafVolumeSmall4On,
        KAknsIIDQgnGrafVolumeSmall5On,
        KAknsIIDQgnGrafVolumeSmall6On,
        KAknsIIDQgnGrafVolumeSmall7On,
        KAknsIIDQgnGrafVolumeSmall8On,
        KAknsIIDQgnGrafVolumeSmall9On,
        KAknsIIDQgnGrafVolumeSmall10On
        };
    const TInt iconOffIDArray[] = 
        {
        EMbmAvkonQgn_graf_volume_small_1_off,
        EMbmAvkonQgn_graf_volume_small_2_off,
        EMbmAvkonQgn_graf_volume_small_3_off,
        EMbmAvkonQgn_graf_volume_small_4_off,
        EMbmAvkonQgn_graf_volume_small_5_off,
        EMbmAvkonQgn_graf_volume_small_6_off,
        EMbmAvkonQgn_graf_volume_small_7_off,
        EMbmAvkonQgn_graf_volume_small_8_off,
        EMbmAvkonQgn_graf_volume_small_9_off,
        EMbmAvkonQgn_graf_volume_small_10_off
        };
    const TInt iconOffMaskIDArray[] = 
        {
        EMbmAvkonQgn_graf_volume_small_1_off_mask,
        EMbmAvkonQgn_graf_volume_small_2_off_mask,
        EMbmAvkonQgn_graf_volume_small_3_off_mask,
        EMbmAvkonQgn_graf_volume_small_4_off_mask,
        EMbmAvkonQgn_graf_volume_small_5_off_mask,
        EMbmAvkonQgn_graf_volume_small_6_off_mask,
        EMbmAvkonQgn_graf_volume_small_7_off_mask,
        EMbmAvkonQgn_graf_volume_small_8_off_mask,
        EMbmAvkonQgn_graf_volume_small_9_off_mask,
        EMbmAvkonQgn_graf_volume_small_10_off_mask
        };
    const TInt iconOnIDArray[] = 
        {
        EMbmAvkonQgn_graf_volume_small_1_on,
        EMbmAvkonQgn_graf_volume_small_2_on,
        EMbmAvkonQgn_graf_volume_small_3_on,
        EMbmAvkonQgn_graf_volume_small_4_on,
        EMbmAvkonQgn_graf_volume_small_5_on,
        EMbmAvkonQgn_graf_volume_small_6_on,
        EMbmAvkonQgn_graf_volume_small_7_on,
        EMbmAvkonQgn_graf_volume_small_8_on,
        EMbmAvkonQgn_graf_volume_small_9_on,
        EMbmAvkonQgn_graf_volume_small_10_on
        };
    const TInt iconOnMaskIDArray[] = 
        {
        EMbmAvkonQgn_graf_volume_small_1_on_mask,
        EMbmAvkonQgn_graf_volume_small_2_on_mask,
        EMbmAvkonQgn_graf_volume_small_3_on_mask,
        EMbmAvkonQgn_graf_volume_small_4_on_mask,
        EMbmAvkonQgn_graf_volume_small_5_on_mask,
        EMbmAvkonQgn_graf_volume_small_6_on_mask,
        EMbmAvkonQgn_graf_volume_small_7_on_mask,
        EMbmAvkonQgn_graf_volume_small_8_on_mask,
        EMbmAvkonQgn_graf_volume_small_9_on_mask,
        EMbmAvkonQgn_graf_volume_small_10_on_mask
        };
    
    for ( TInt i=0; i<10; i++ )
        {
        AknsUtils::CreateIconL( 
                aSkin, 
                iconOffSkinIDArray[i],
                iInActiveIcons[i],
                iInActiveMasks[i],
                KNullDesC,
                iconOffIDArray[i],
                iconOffMaskIDArray[i]
                );
        AknsUtils::CreateIconL( 
                aSkin, 
                iconOnSkinIDArray[i],
                iActiveIcons[i],
                iActiveMasks[i],
                KNullDesC,
                iconOnIDArray[i],
                iconOnMaskIDArray[i]
                );
        }
    }
    
    
// ----------------------------------------------------------------------------
// CVolumeExtension::
//
// ----------------------------------------------------------------------------
//
void CVolumeExtension::TryLoadBitmapsDefaultLargeL( MAknsSkinInstance* aSkin )
    {
    const TAknsItemID iconOffSkinIDArray[] = 
        {
        KAknsIIDQgnGrafVolumeSet1Off,
        KAknsIIDQgnGrafVolumeSet2Off,
        KAknsIIDQgnGrafVolumeSet3Off,
        KAknsIIDQgnGrafVolumeSet4Off,
        KAknsIIDQgnGrafVolumeSet5Off,
        KAknsIIDQgnGrafVolumeSet6Off,
        KAknsIIDQgnGrafVolumeSet7Off,
        KAknsIIDQgnGrafVolumeSet8Off,
        KAknsIIDQgnGrafVolumeSet9Off,
        KAknsIIDQgnGrafVolumeSet10Off
        };
    const TAknsItemID iconOnSkinIDArray[] = 
        {
        KAknsIIDQgnGrafVolumeSet1On,
        KAknsIIDQgnGrafVolumeSet2On,
        KAknsIIDQgnGrafVolumeSet3On,
        KAknsIIDQgnGrafVolumeSet4On,
        KAknsIIDQgnGrafVolumeSet5On,
        KAknsIIDQgnGrafVolumeSet6On,
        KAknsIIDQgnGrafVolumeSet7On,
        KAknsIIDQgnGrafVolumeSet8On,
        KAknsIIDQgnGrafVolumeSet9On,
        KAknsIIDQgnGrafVolumeSet10On
        };
    const TInt iconOffIDArray[] = 
        {
        EMbmAvkonQgn_graf_volume_set_1_off,
        EMbmAvkonQgn_graf_volume_set_2_off,
        EMbmAvkonQgn_graf_volume_set_3_off,
        EMbmAvkonQgn_graf_volume_set_4_off,
        EMbmAvkonQgn_graf_volume_set_5_off,
        EMbmAvkonQgn_graf_volume_set_6_off,
        EMbmAvkonQgn_graf_volume_set_7_off,
        EMbmAvkonQgn_graf_volume_set_8_off,
        EMbmAvkonQgn_graf_volume_set_9_off,
        EMbmAvkonQgn_graf_volume_set_10_off
        };
    const TInt iconOffMaskIDArray[] = 
        {
        EMbmAvkonQgn_graf_volume_set_1_off_mask,
        EMbmAvkonQgn_graf_volume_set_2_off_mask,
        EMbmAvkonQgn_graf_volume_set_3_off_mask,
        EMbmAvkonQgn_graf_volume_set_4_off_mask,
        EMbmAvkonQgn_graf_volume_set_5_off_mask,
        EMbmAvkonQgn_graf_volume_set_6_off_mask,
        EMbmAvkonQgn_graf_volume_set_7_off_mask,
        EMbmAvkonQgn_graf_volume_set_8_off_mask,
        EMbmAvkonQgn_graf_volume_set_9_off_mask,
        EMbmAvkonQgn_graf_volume_set_10_off_mask
        };
    const TInt iconOnIDArray[] = 
        {
        EMbmAvkonQgn_graf_volume_set_1_on,
        EMbmAvkonQgn_graf_volume_set_2_on,
        EMbmAvkonQgn_graf_volume_set_3_on,
        EMbmAvkonQgn_graf_volume_set_4_on,
        EMbmAvkonQgn_graf_volume_set_5_on,
        EMbmAvkonQgn_graf_volume_set_6_on,
        EMbmAvkonQgn_graf_volume_set_7_on,
        EMbmAvkonQgn_graf_volume_set_8_on,
        EMbmAvkonQgn_graf_volume_set_9_on,
        EMbmAvkonQgn_graf_volume_set_10_on
        };
    const TInt iconOnMaskIDArray[] = 
        {
        EMbmAvkonQgn_graf_volume_set_1_on_mask,
        EMbmAvkonQgn_graf_volume_set_2_on_mask,
        EMbmAvkonQgn_graf_volume_set_3_on_mask,
        EMbmAvkonQgn_graf_volume_set_4_on_mask,
        EMbmAvkonQgn_graf_volume_set_5_on_mask,
        EMbmAvkonQgn_graf_volume_set_6_on_mask,
        EMbmAvkonQgn_graf_volume_set_7_on_mask,
        EMbmAvkonQgn_graf_volume_set_8_on_mask,
        EMbmAvkonQgn_graf_volume_set_9_on_mask,
        EMbmAvkonQgn_graf_volume_set_10_on_mask
        };

    for ( TInt i=0; i<10; i++ )
        {
        AknsUtils::CreateIconL( 
                aSkin, 
                iconOffSkinIDArray[i],
                iInActiveIcons[i],
                iInActiveMasks[i],
                KNullDesC,
                iconOffIDArray[i],
                iconOffMaskIDArray[i]
                );
        AknsUtils::CreateIconL( 
                aSkin, 
                iconOnSkinIDArray[i],
                iActiveIcons[i],
                iActiveMasks[i],
                KNullDesC,
                iconOnIDArray[i],
                iconOnMaskIDArray[i]
                );
        }
    
    }


// ----------------------------------------------------------------------------
// CVolumeExtension::TryLoadBitmapsNoSkinL
//
// ----------------------------------------------------------------------------
//
void CVolumeExtension::TryLoadBitmapsNoSkinL()
    {
    AknIconUtils::CreateIconL(
            iInActiveIcons[0],
            iInActiveMasks[0],
            KAvkonBitmapFile,
            EMbmAvkonQgn_graf_volume_small_off,
            EMbmAvkonQgn_graf_volume_small_off_mask );
    AknIconUtils::CreateIconL(
            iActiveIcons[0],
            iActiveMasks[0],
            KAvkonBitmapFile,
            EMbmAvkonQgn_graf_volume_small_on,
            EMbmAvkonQgn_graf_volume_small_on_mask );
    }
    
// ----------------------------------------------------------------------------
// CVolumeExtension::CalculateParentRect
//
// ----------------------------------------------------------------------------
//
void CVolumeExtension::CalculateParentRect( TInt aStyle, const TRect& aParent )
    {
    switch (aStyle)
        {
        case ENaviPaneVolumeControl:
        case EDynRangeNaviPaneVolumeControl:
                {
                // Rect() gives navi_navi_volume_pane in the control hierarchy.
                if ( AknStatuspaneUtils::SmallLayoutActive() )
                    {
                    iParentRect = RectFromLayout(
                                aParent,
                                AknLayoutScalable_Avkon::volume_small2_pane()
                                );
                    }
                else
                    {
                    iParentRect = RectFromLayout(
                                aParent,
                                AknLayoutScalable_Avkon::volume_small_pane()
                                );
                    }
                }
            break;
        case ESettingsVolumeControl:
        case EPopupVolumeControl:
        default:
            iParentRect = aParent; // Rect()
            break;
        }
    }

// ----------------------------------------------------------------------------
// CVolumeExtension::DrawSvgSmallVolume
//
// ----------------------------------------------------------------------------
//
void CVolumeExtension::DrawSvgSmallVolume(
                        TInt aStyle,
                        const TRect& aRect,
                        CBitmapContext& aGc,
                        TInt aValue
                        )
    {
    TRect r;
    for (TInt i = 0; i < KVolumeLevels; i++)
        {
        if ( aStyle == EPopupVolumeControl )
            {
            r = RectFromLayout( aRect,
                        AknLayoutScalable_Avkon::volume_small_pane_g( i ) );
            }
        else // navi pane volume control
            {
            if ( AknStatuspaneUtils::SmallLayoutActive() )
                {
                r = RectFromLayout( aRect,
                        AknLayoutScalable_Avkon::volume_small2_pane_g( i ) );
                }
            else
                {
                r = RectFromLayout( aRect,
                        AknLayoutScalable_Avkon::volume_small_pane_g( i ) );
                }
            }
            
        TPoint p( r.iTl.iX, r.iTl.iY );
        TRect srcRect(0, 0, r.Width(), r.Height());

        if ( AknLayoutUtils::PenEnabled() )
            {
            // Store rect for every level.
            // We can then decide what level was clicked
            iVolumeLevels[i] = r;
            }

        if ( i < aValue )
            {
            if ( ( iActiveIcons[i] != NULL ) && ( iActiveMasks[i] != NULL ) )
                {
                aGc.BitBltMasked( p, iActiveIcons[i],
                                    srcRect, iActiveMasks[i], ETrue);
                }
            }
        else
            {
            if ( ( iInActiveIcons[i] != NULL ) 
                && ( iInActiveMasks[i] != NULL ) )
                {
                aGc.BitBltMasked( p, iInActiveIcons[i], 
                                    srcRect, iInActiveMasks[i], ETrue);
                }
            }
        }
    }

// ----------------------------------------------------------------------------
// CVolumeExtension::DrawSvgSettingsVolume
//
// ----------------------------------------------------------------------------
//
void CVolumeExtension::DrawSvgSettingsVolume( const TRect& aRect,
                        CWindowGc& aGc, TInt aValue )
    {
    TRect r;
    for (TInt i = 0; i < KVolumeLevels; i++)
        {
        r = RectFromLayout( aRect,
                    AknLayoutScalable_Avkon::volume_set_pane_g( i ) );
        TPoint p( r.iTl.iX, r.iTl.iY );
        TRect srcRect(0, 0, r.Width(), r.Height());

        if ( AknLayoutUtils::PenEnabled() )
            {
            // Store rect for every level.
            // We can then decide what level was clicked
            iVolumeLevels[i] = r;
            }

        if ( i < aValue )
            {
            if ( ( iActiveIcons[i] != NULL ) && ( iActiveMasks[i] != NULL ) )
                {
                aGc.BitBltMasked( p, iActiveIcons[i],
                                    srcRect, iActiveMasks[i], ETrue);
                }
            }
        else
            {
            if ( ( iInActiveIcons[i] != NULL )
                    && ( iInActiveMasks[i] != NULL ) )
                {
                aGc.BitBltMasked( p, iInActiveIcons[i], srcRect, 
                                    iInActiveMasks[i], ETrue);
                }
            }
        }
    }

// ----------------------------------------------------------------------------
// CVolumeExtension::
//
// ----------------------------------------------------------------------------
//
void CVolumeExtension::CreateSvgSettingsIconL(
                const TRect& aRect, TInt aValue, CGulIcon* aIcon )
    {
    CVolumeExtension* extension = new (ELeave) CVolumeExtension;
    CleanupStack::PushL( extension );

    extension->LoadBitmapsL( ENaviPaneVolumeControl, aRect );
    extension->DrawSvgSettingsIconL( aRect, aValue, aIcon );

    CleanupStack::PopAndDestroy(); // extension
    }
// ----------------------------------------------------------------------------
// CVolumeExtension::
//
// ----------------------------------------------------------------------------
//
void CVolumeExtension::CreateDynRangeStyleSettingsIconL( const TRect& aRect, 
                                                    TInt aValue, 
                                                    CGulIcon* aIcon, 
                                                    TInt aMinimum,
                                                    TInt aMaximum )
    {
    CVolumeExtension* extension = new (ELeave) CVolumeExtension;
    CleanupStack::PushL( extension );

    extension->LoadBitmapsL( EDynRangeSettingsVolumeControl, aRect );
    extension->DrawDynRangeStyleSettingsIconL( aRect, aValue, aIcon, aMinimum, aMaximum );

    CleanupStack::PopAndDestroy(); // extension
    }
// ----------------------------------------------------------------------------
// CVolumeExtension::
//
// ----------------------------------------------------------------------------
//
void CVolumeExtension::DrawSvgSettingsIconL(
                const TRect& aRect, TInt aValue, CGulIcon* aIcon )
    {
    __ASSERT_DEBUG( ( aValue >= iMinimumValue )
                            && (aValue <= iMaximumValue), 
                    Panic(EAknPanicOutOfRange) );
    if( iGfxMode == KGfxModeNew )
        {
        DrawDynRangeStyleSettingsIconL( aRect, aValue, aIcon, iMinimumValue, iMaximumValue );            
        }
    else
        {
            
        // The actual bitmap
        CFbsBitmap* bitmap = new (ELeave) CFbsBitmap;
        CleanupStack::PushL( bitmap );

        bitmap->Create( aRect.Size(),
                    CCoeEnv::Static()->ScreenDevice()->DisplayMode() );
        CFbsBitGc* fbsBitGc = CFbsBitGc::NewL();
        CleanupStack::PushL( fbsBitGc );
        CFbsBitmapDevice* bmpDevice = CFbsBitmapDevice::NewL( bitmap );
        CleanupStack::PushL( bmpDevice );
        fbsBitGc->Activate( bmpDevice );

        TRect r;

        for (TInt i = 0; i < KVolumeLevels; i++)
            {
            r = RectFromLayout( aRect,
                    AknLayoutScalable_Avkon::volume_small_pane_cp_g(i));
            TPoint p( r.iTl.iX, r.iTl.iY );
            TRect srcRect(0, 0, r.Width(), r.Height());

            if ( AknLayoutUtils::PenEnabled() )
                {
                // Store rect for every level.
                // We can then decide what level was clicked
                iVolumeLevels[i] = r;
                }

            if ( i < aValue )
                {
                if ( iActiveIcons[i] != NULL )
                    {
                    AknIconUtils::SetSize( iActiveIcons[i], r.Size() );
                    fbsBitGc->BitBlt( p, iActiveIcons[i], srcRect );
                    }
                }
            else
                {
                if ( iInActiveIcons[i] != NULL )
                    {
                    AknIconUtils::SetSize( iInActiveIcons[i], r.Size() );
                    fbsBitGc->BitBlt( p, iInActiveIcons[i], srcRect );
                    }
                }
            }
                
        CleanupStack::PopAndDestroy( 2 ); // bmpDevice, fbsBitGc
        aIcon->SetBitmap( bitmap ); // Transfers ownership
        CleanupStack::Pop(); // bitmap

        // The mask
        CFbsBitmap* mask = new (ELeave) CFbsBitmap;
        CleanupStack::PushL( mask );

        mask->Create( aRect.Size(), iActiveMasks[0]->DisplayMode() );
        fbsBitGc = CFbsBitGc::NewL();
        CleanupStack::PushL( fbsBitGc );
        bmpDevice = CFbsBitmapDevice::NewL( mask );
        CleanupStack::PushL( bmpDevice );
        fbsBitGc->Activate( bmpDevice );
        fbsBitGc->SetPenStyle( CGraphicsContext::ENullPen );
        fbsBitGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
        fbsBitGc->SetBrushColor( KRgbBlack );
        fbsBitGc->DrawRect( TRect( aRect.Size() ) );

        fbsBitGc->SetBrushStyle( CGraphicsContext::ENullBrush );

        for ( TInt i = 0; i < KVolumeLevels; i++ )
            {
            r = RectFromLayout( aRect,
                    AknLayoutScalable_Avkon::volume_small_pane_cp_g( i ) );
            TPoint p( r.iTl.iX, r.iTl.iY );
            TRect srcRect( 0, 0, r.Width(), r.Height() );

            if ( i < aValue )
                {
                if ( ( iActiveMasks[i] != NULL ) )
                    {
                    AknIconUtils::SetSize( iActiveMasks[i], r.Size() );
                    fbsBitGc->BitBlt( p, iActiveMasks[i], srcRect );
                    }
                }
            else
                {
                if ( iInActiveMasks[i] != NULL )
                    {
                    AknIconUtils::SetSize( iInActiveMasks[i], r.Size() );
                    fbsBitGc->BitBlt( p, iInActiveMasks[i], srcRect );
                    }
                }
            }

        CleanupStack::PopAndDestroy( 2 ); // bmpDevice, fbsBitGc
        aIcon->SetMask( mask ); // Transfers ownership
        CleanupStack::Pop(); // mask
        }
    }
// ----------------------------------------------------------------------------
// CVolumeExtension::
//
// ----------------------------------------------------------------------------
//
void CVolumeExtension::DrawDynRangeStyleSettingsIconL( const TRect& aRect, 
                                                  TInt aValue, 
                                                  CGulIcon* aIcon, 
                                                  TInt aMinimum, 
                                                  TInt aMaximum )
    {
    __ASSERT_DEBUG( ( aValue >= aMinimum )
                            && (aValue <= aMaximum), 
                    Panic(EAknPanicOutOfRange) );
    
    // The actual bitmap
    CFbsBitmap* bitmap = new (ELeave) CFbsBitmap;
    CleanupStack::PushL( bitmap );

    bitmap->Create( aRect.Size(),
                CCoeEnv::Static()->ScreenDevice()->DisplayMode() );
    CFbsBitGc* fbsBitGc = CFbsBitGc::NewL();
    CleanupStack::PushL( fbsBitGc );
    CFbsBitmapDevice* bmpDevice = CFbsBitmapDevice::NewL( bitmap );
    CleanupStack::PushL( bmpDevice );
    fbsBitGc->Activate( bmpDevice );

    TRect r( aRect );
    // the following is original code
    // TRect activeRect(r.iTl.iX, r.iTl.iY, r.Width() * aValue/( aMaximum - aMinimum + 1 ), r.Height()); 
    // but the following is changed 
    // just remove +1 from denominator, because it should be aMaximum - aMinimum 
    // and caculate the activeRect seperately according to the iOld ScaleSettingVolume.
    TInt range;
    if( iOldScaleSettingVolume )
        {
        range = KVolumeLevels ;      
        } 
    else
        {
        range = aMaximum - aMinimum ;
        }
    TRect activeRect(r.iTl.iX, r.iTl.iY, r.Width() * aValue/range, r.Height()); 
    TRect inActiveRect( activeRect.iBr.iX, activeRect.iTl.iY, r.iBr.iX, r.iBr.iY );

   if ( iActiveIcons[0] != NULL && iInActiveIcons[0] != NULL )
       {
       // add the last parameter for every SetSize() function
       // In order to make the solid graphic has the same size as the volume control                 
       AknIconUtils::SetSize( iActiveIcons[0], r.Size(),EAspectRatioNotPreserved );
       fbsBitGc->BitBlt( activeRect.iTl, iActiveIcons[0], activeRect );
       AknIconUtils::SetSize( iInActiveIcons[0], r.Size(),EAspectRatioNotPreserved );
       fbsBitGc->BitBlt( inActiveRect.iTl, iInActiveIcons[0], inActiveRect );       

       }

    CleanupStack::PopAndDestroy( 2 ); // bmpDevice, fbsBitGc
    aIcon->SetBitmap( bitmap ); // Transfers ownership
    CleanupStack::Pop(); // bitmap

    // The mask
    CFbsBitmap* mask = new (ELeave) CFbsBitmap;
    CleanupStack::PushL( mask );

    mask->Create( aRect.Size(), iActiveMasks[0]->DisplayMode() );
    fbsBitGc = CFbsBitGc::NewL();
    CleanupStack::PushL( fbsBitGc );
    bmpDevice = CFbsBitmapDevice::NewL( mask );
    CleanupStack::PushL( bmpDevice );
    fbsBitGc->Activate( bmpDevice );
    fbsBitGc->SetPenStyle( CGraphicsContext::ENullPen );
    fbsBitGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    fbsBitGc->SetBrushColor( KRgbBlack );
    fbsBitGc->DrawRect( TRect( aRect.Size() ) );

    fbsBitGc->SetBrushStyle( CGraphicsContext::ENullBrush );
    
   if ( iActiveMasks[0] != NULL && iInActiveMasks[0] != NULL )
       {
       // add the last parameter for every SetSize() function
       // In order to make the solid graphic has the same size as the volume control   
       AknIconUtils::SetSize( iActiveMasks[0], r.Size(),EAspectRatioNotPreserved );
       fbsBitGc->BitBlt( activeRect.iTl, iActiveMasks[0], activeRect );
       AknIconUtils::SetSize( iInActiveMasks[0], r.Size(),EAspectRatioNotPreserved );
       fbsBitGc->BitBlt( inActiveRect.iTl, iInActiveMasks[0], inActiveRect );
       } 
          
    CleanupStack::PopAndDestroy( 2 ); // bmpDevice, fbsBitGc
    aIcon->SetMask( mask ); // Transfers ownership
    CleanupStack::Pop(); // mask
    }

// ----------------------------------------------------------------------------
// CVolumeExtension::RectFromLayout
//
// ----------------------------------------------------------------------------
//
TRect CVolumeExtension::RectFromLayout(const TRect& aParent,
                const TAknWindowComponentLayout& aComponentLayout) const
    {
    TAknWindowLineLayout lineLayout = aComponentLayout.LayoutLine();
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect(aParent,lineLayout);
    return layoutRect.Rect();
    }

// ----------------------------------------------------------------------------
// CVolumeExtension::GetVolumeLevelByPosition()
// This function Searches which iVolumeLevels array's element (TRect) contains
// aPoint. The array is ordered so that the index can then be used to return 
// correct volume level. aAreaRect is used to add volumelevel's height to cover
// whole area so user does not need to click "inside" level. This function also
// calculates gap between volumelevel rects and returns correct volumelevel
// also from clicks to these gaps
// ----------------------------------------------------------------------------
//
TInt CVolumeExtension::GetVolumeLevelByPosition( const TInt& ,
                                                 const TPoint& aPoint, 
                                                 const TRect& aAreaRect ) const
    {
    if ( AknLayoutUtils::PenEnabled() )
        {
        TInt volumeLevel = KVolumeLevelNotFound; 
        TInt range = iMaximumValue - iMinimumValue ;
        // Use hi-res volume control with dynamic volume range
        if( iGfxMode == KGfxModeNew )
            {
            // Check the point's position in iParentRect x-axis. Use this to 
            // define a value between iMinimumValue  and iMaximumValue. Step 
            // size is always 1 (value is rounded up).
             TInt pointInVolumeAxis = aPoint.iX - iParentRect.iTl.iX;
            // This rouds up to integer.
            TInt total( pointInVolumeAxis * range );
            TInt volumePosition = total / iParentRect.Width() + iMinimumValue;
            if ( total % iParentRect.Width() > 0 )
                {
                volumePosition++;
                }             
            
            if( volumePosition >= iMinimumValue && volumePosition <= iMaximumValue )
                {
                volumeLevel = volumePosition;
                }
            else if(volumePosition > iMaximumValue)
                {
                volumeLevel = iMaximumValue;
                }
            else
                {
                volumeLevel = iMinimumValue;
                }
            }
        // Use old volume implementation with range [0,10]
        else 
            {
            TRect nextRect;
            TRect thisRect = iVolumeLevels[0];
            
            if ( iMuteRect.Contains( aPoint ))
                {
                return KVolumeLevelMuteTapped;
                }

            for (TInt i = 1; i <= KVolumeLevels; i++)
                {
                // do not read next rect, if this is last round
                if ( i < KVolumeLevels )
                    {
                    // read rect for volume level i
                    nextRect = iVolumeLevels[i];

                    // set thisRect to contain half of gap between this and next
                    //  rect
                    // + 1 because right and bottom borders are not "inside" rect
                    thisRect.iBr.iX = (nextRect.iTl.iX - thisRect.iBr.iX)/2
                                        + thisRect.iBr.iX;

                    // set nextRect to contain other half of gap
                    //  between these two rects
                    nextRect.iTl.iX = thisRect.iBr.iX;
                    }

                // set volumebars where pointer is accepted
                //  for it to be as high as area.
                thisRect.iTl.iY = aAreaRect.iTl.iY;
                thisRect.iBr.iY = aAreaRect.iBr.iY;

                if ( thisRect.Contains( aPoint ))
                    {
                    // Because array is zero indexed, but volumes starts at 1
                    //--> Conversion by adding one before return.
                    // (and here so that it needs to be done only once)
                    volumeLevel = i;
                    volumeLevel = volumeLevel * range/KVolumeLevels;
                    break;
                    }
                thisRect = nextRect;
                }
            if( aPoint.iX > iVolumeLevels[KVolumeLevels-1].iBr.iX )
                {
                volumeLevel = iMaximumValue;
                }
            else if( aPoint.iX < iVolumeLevels[0].iBr.iX )
                {
                volumeLevel = iMinimumValue;    
                }
            }
        return volumeLevel;
        }
    else
        {
        // Should not occur, just prevent complier's warning
        return 0;
        }
    }

//  End of File
