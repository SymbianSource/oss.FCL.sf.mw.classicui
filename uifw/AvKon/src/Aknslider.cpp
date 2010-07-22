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
* Description:
*
*/


// INCLUDE FILES
#include <AknUtils.h>
#include <barsread.h>
#include <eikenv.h>
#include <AknDef.h>
#include <AknPanic.h>
#include <avkon.hrh>
#include <avkon.mbg>
#include <e32math.h>
#include <bitstd.h>
#include <bitdev.h>
#include <aknconsts.h>
#include <StringLoader.h>
#include <AknsDrawUtils.h>
#include <centralrepository.h>
#include <AvkonInternalCRKeys.h>
#include <AknsFrameBackgroundControlContext.h>
#include <gulicon.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <aknlayoutscalable_apps.cdl.h>
#include <layoutmetadata.cdl.h>
#include <AknIconUtils.h>
#include <AknBidiTextUtils.h>

#include <AknTasHook.h>
#include "aknslider.h"

#include <touchfeedback.h>

// Large enough for a 20 digit number or fraction with two 9 digit numbers.
// This number is not in the header as it does not need to be known by the
// client.
const TInt KAknSliderValueLabelValueMaxLength = 20;

// This value is used to account for the safety demands of StringLoader. It
// requires extra length in the target descriptor of its formatting than you
// would expect.
const TInt KAknSliderFormatKeyLength = 2;

// This value is the optimum number of repeat key events to get through the
// range of the slider.

const TInt KAknSliderFeedbackActionTime = 160 * 1000; // Interval, microseconds

// Default draw color 
const TInt KAknSliderDefaultDrawColor = 120;
const TInt KScrollRepeatTimeout = 250000; // 0.25 seconds
const TInt KStableFeedbackIntesity = 100;
const TInt KFeedbackTimeout = 100000;
const TInt KNoFeedbackTimeout = 0;
const TInt KStepThreshold = 15;
// ============================================================================
// Internal class to hold slider control data, primarily coming from resource.
NONSHARABLE_CLASS( CAknSliderData ): public CBase
    {
public:
    static CAknSliderData* NewLC( TInt aResourceId );
    static CAknSliderData* NewL( TResourceReader& aReader );
    ~CAknSliderData();

    void SetRange( TInt aMinimumValue, TInt aMaximumValue );
    inline TInt Range() const
        {
        return iMaximumValue - iMinimumValue;
        }

    void SetDecimalPlaces( TInt aDecimalPlaces );
    inline TInt DecimalPlaces() const
        {
        return iDecimalPlaces;
        }


private:
    CAknSliderData();
    void ConstructFromResourceL( TInt aResourceId );
    void ConstructFromResourceL( TResourceReader& aReader );

    // Copy constructor, declared not defined -> disabled
    CAknSliderData( const CAknSliderData& aData );
    // Assignment operator, declared not defined -> disabled
    const CAknSliderData& operator=( const CAknSliderData& aData );

public:
    TInt iMinimumValue;
    TInt iMaximumValue;
    TInt iStepSize;
    TInt iValueType;
    TInt iLayout;
    HBufC* iText; // Owned

    // Text to be used for the singular label if needed. Owned
    HBufC* iSingularText;

    HBufC* iMinimumLabelText; // Owned
    HBufC* iMaximumLabelText; // Owned
    TInt iDecoratorImageId;
    TAknFeedbackStyle iFeedbackStyle;
        
private:
    TInt iDecimalPlaces;

    // NOTE! This class is only for storing the data read from slider resource.
    // Do not add any unnecessary members to this class, such data and
    // functionality should go to the extension instead.
    };


// ----------------------------------------------------------------------------
// CAknSliderData::NewLC
// ----------------------------------------------------------------------------
//
CAknSliderData* CAknSliderData::NewLC( TInt aResourceId )
    {
    CAknSliderData* self = new ( ELeave ) CAknSliderData();
    CleanupStack::PushL( self );
    self->ConstructFromResourceL( aResourceId );
    return self;
    }


// ----------------------------------------------------------------------------
// CAknSliderData::NewL
// ----------------------------------------------------------------------------
//
CAknSliderData* CAknSliderData::NewL( TResourceReader& aReader )
    {
    CAknSliderData* self = new ( ELeave ) CAknSliderData();
    CleanupStack::PushL( self );
    self->ConstructFromResourceL( aReader );
    CleanupStack::Pop( self );
    return self;
    }


// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------
//
CAknSliderData::CAknSliderData()
    {
    // Derived from CBase -> members zeroed
    }


// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
//
CAknSliderData::~CAknSliderData()
    {
    delete iText;
    delete iSingularText;
    delete iMinimumLabelText;
    delete iMaximumLabelText;
    }

// ----------------------------------------------------------------------------
// CAknSliderData::ConstructFromResourceL
// ----------------------------------------------------------------------------
//
void CAknSliderData::ConstructFromResourceL( TInt aResourceId )
    {
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, aResourceId );
    ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy(); // reader
    }


// ----------------------------------------------------------------------------
// CAknSliderData::ConstructFromResource
// ----------------------------------------------------------------------------
//
void CAknSliderData::ConstructFromResourceL( TResourceReader& aReader )
    {
    TInt sliderType = aReader.ReadInt16();
    if ( sliderType == EAknSliderWithFeedbackStyle )
        {
        iFeedbackStyle = (TAknFeedbackStyle)aReader.ReadInt16();
        iLayout = aReader.ReadInt16();
        }
    else
        {
        // old resource struct used -> actually sliderType contains
        // layout information
        iLayout = sliderType;
        if ( iLayout > EAknSliderLayoutHorizontal )
            {
            iLayout = EAknSliderLayoutHorizontal;
            }
        }
        
    TInt min = aReader.ReadInt16();
    TInt max = aReader.ReadInt16();
    SetRange( min, max );
    iStepSize = aReader.ReadInt16();
    iValueType = aReader.ReadInt16();
    SetDecimalPlaces( aReader.ReadInt16() );
    iSingularText = aReader.ReadHBufCL();
    iMinimumLabelText = aReader.ReadHBufCL();
    iMaximumLabelText = aReader.ReadHBufCL();
    iText = aReader.ReadHBufCL();

    // Extension link for graphics
    iDecoratorImageId = aReader.ReadInt32();
    if ( !iDecoratorImageId )
        {
        iDecoratorImageId = R_AVKON_SLIDER_CONTRAST_GRAPHICS;
        }
    }


// ----------------------------------------------------------------------------
// CAknSliderData::SetRange
// ----------------------------------------------------------------------------
//
void CAknSliderData::SetRange( TInt aMinimumValue, TInt aMaximumValue )
    {
    __ASSERT_ALWAYS( aMaximumValue > aMinimumValue,
                     Panic( EAknPanicOutOfRange ) );

    iMaximumValue = aMaximumValue;
    iMinimumValue = aMinimumValue;
    }


// ----------------------------------------------------------------------------
// CAknSliderData::SetDecimalPlaces
// ----------------------------------------------------------------------------
//
void CAknSliderData::SetDecimalPlaces( TInt aDecimalPlaces )
    {
    __ASSERT_DEBUG( aDecimalPlaces >= 0, Panic( EAknPanicInvalidValue ) );
    __ASSERT_DEBUG( aDecimalPlaces < 10, Panic( EAknPanicInvalidValue ) );
    iDecimalPlaces = Abs( aDecimalPlaces );
    }
    
    
// ============================================================================
NONSHARABLE_STRUCT( TAknSliderGfx )
    {
    TAknSliderGfx(): iRgb( NULL ), iMask( NULL )
        {}

    CFbsBitmap* iRgb; // Referenced.
    CFbsBitmap* iMask; // Referenced.
    // customized graphics flag
    TInt iCustomizedFlag; // if use default, then value = 0, else value = 1
    };

// ============================================================================
NONSHARABLE_CLASS( CAknSliderExtension ): public CBase
    {
public:

    // Symbols for bitflags.
    enum TFlags
        {
        EFlagHorizontal,
        EFlagFillEnabled,
        EFlagMarkerEnabled,
        EFlagTickMarksEnabled,
        EFlagTickBelowOrRight,
        EFlagPointerDown,
        EFlagDraggingThumb,
        EFlagValueStepChange,
        EFlagPlayingContinuousFb,
        EFlagCount // must be the last flag
        };

private:
    CAknSliderExtension();
    // Copy constructor, declared not defined -> disabled
    CAknSliderExtension( const CAknSliderExtension& );
    // Assignment operator, declared not defined -> disabled
    const CAknSliderExtension& operator=( const CAknSliderExtension& );

    void ConstructL();

public:
    ~CAknSliderExtension();
    static CAknSliderExtension* NewL();

    void SetGraphics( TInt aElement, 
                      CFbsBitmap* aBitmap, 
                      CFbsBitmap* aMask,
                      TBool aCustomize = ETrue);
    void UseDefaultGraphics( TInt aElement );
    TBool UsesDefaultGraphics( TInt aElement ) const;
    TBool UsesDefaultGraphics() const;
    void GetGfx( TAknSliderGfx& aGfx, TInt aElement ) const;
    
    void DeleteBitmaps();
    void TryLoadNSliderBitmap(TBool aFromSkin, MAknsSkinInstance* aSkin );
    void TryLoadNSliderVerticalBitmap( MAknsSkinInstance* aSkin );                         
    inline void SetFlag( TInt aFlagIndex )
        {
        ASSERT( 0 <= aFlagIndex && aFlagIndex < EFlagCount );
        iFlags.Set( aFlagIndex );
        }

    inline void ClearFlag( TInt aFlagIndex )
        {
        ASSERT( 0 <= aFlagIndex && aFlagIndex < EFlagCount );
        iFlags.Clear( aFlagIndex );
        }

    inline TBool IsFlagSet( TInt aFlagIndex ) const
        {
        ASSERT( 0 <= aFlagIndex && aFlagIndex < EFlagCount );
        return iFlags.IsSet( aFlagIndex );
        }

public:
    CFbsBitmap* iLineIcon; // Owned.
    CFbsBitmap* iLineIconMask; // Owned.
 
    TRect iLeftCapRect; // The default value is zero -> no left line cap
    TRect iRightCapRect; // The default value is zero -> no right line cap
    
    TRect iTickRect;

    CPeriodic* iTimer; // Owned.
    TInt iEffectTimerCount;
    TRect iThumbRect; // Equals GetMarkerRect
    TUint iTickInterval;
    TPoint iPenInputPos;//remember pointer input position

    TBool iReportMarkerDragEvent;
    TRect iTouchDownArea;
    TRect iTouchActiveArea;
    TBool iNoDraw;
        
private:
    // If EFlagHorizontal is not set, the orientation is vertical.
    TBitFlags32 iFlags;

    // Stores the element graphics (rgb icon and mask icon) as bitmaps. Bitmaps
    // are owned.
    TAknSliderGfx iGfx[CAknSlider::EElemMarkerSelected + 1];
    };


// ----------------------------------------------------------------------------
// CAknSliderExtension::CAknSliderExtension
// ----------------------------------------------------------------------------
//
CAknSliderExtension::CAknSliderExtension()
    {
    // slider is derived from CBase -> members zeroed
    SetFlag( EFlagMarkerEnabled );//default is marker enable
    SetFlag( EFlagHorizontal ); //default is horizontal enable
    SetFlag( EFlagValueStepChange); //default is step change enable
    
    // Don't report drag event as default setting
    iReportMarkerDragEvent = EFalse;
    }


// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
//
CAknSliderExtension::~CAknSliderExtension()
    {
    if( iTimer )
        {
        iTimer->Cancel();
        }
    
    delete iTimer;
    delete iLineIcon;
    delete iLineIconMask;
    
    DeleteBitmaps();
    }


// ----------------------------------------------------------------------------
// CAknSliderExtension::ConstructL
// ----------------------------------------------------------------------------
//
void CAknSliderExtension::ConstructL()
    {
    // Create icon for line
    AknsUtils::CreateIconL( AknsUtils::SkinInstance(),
        KAknsIIDQgnGrafLinePrimaryHorizontal, iLineIcon, iLineIconMask,
        KAvkonBitmapFile, EMbmAvkonQgn_graf_line_primary_horizontal,
        EMbmAvkonQgn_graf_line_primary_horizontal_mask );
    
    // Set default value
    for ( int i = 0; i <= CAknSlider::EElemMarkerSelected; ++i )
        {
        iGfx[i].iRgb = NULL;
        iGfx[i].iMask = NULL;
        iGfx[i].iCustomizedFlag = 0;
        }
        
    iTimer = CPeriodic::NewL( CActive::EPriorityStandard );
    }


// ----------------------------------------------------------------------------
// CAknSliderExtension::NewL
// ----------------------------------------------------------------------------
//
CAknSliderExtension* CAknSliderExtension::NewL()
    {
    
    CAknSliderExtension* self = new( ELeave ) CAknSliderExtension();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// CAknSliderExtension::TryLoadNewSliderBitmap
//
// ----------------------------------------------------------------------------
//
void CAknSliderExtension::TryLoadNSliderBitmap( TBool aFromSkin, MAknsSkinInstance* aSkin )
    {
    
    const TInt iconIDArray[] = 
        {
        EMbmAvkonQgn_graf_nslider_end_left,
        EMbmAvkonQgn_graf_nslider_end_right,
        EMbmAvkonQgn_graf_nslider_middle,
        EMbmAvkonQgn_graf_nslider_marker,
        EMbmAvkonQgn_graf_nslider_marker_selected
        };
    const TInt iconMaskIDArray[] = 
        {
        EMbmAvkonQgn_graf_nslider_end_left_mask,
        EMbmAvkonQgn_graf_nslider_end_right_mask,
        EMbmAvkonQgn_graf_nslider_middle_mask,
        EMbmAvkonQgn_graf_nslider_marker_mask,
        EMbmAvkonQgn_graf_nslider_marker_selected_mask
        }; 
    const TAknsItemID iconSkinIDArray[] = 
        {
        KAknsIIDQgnGrafNsliderEndLeft,
        KAknsIIDQgnGrafNsliderEndRight,
        KAknsIIDQgnGrafNsliderMiddle,
        KAknsIIDQgnGrafNsliderMarker,
        KAknsIIDQgnGrafNsliderMarkerSelected
        };
        
    const TInt element[] = 
        {
        CAknSlider::EElemEmptyLeftCap,
        CAknSlider::EElemEmptyRightCap,
        CAknSlider::EElemEmptyLine,
        CAknSlider::EElemMarker,
        CAknSlider::EElemMarkerSelected
        };
    TInt arrayTotal = sizeof( iconIDArray )/sizeof(TInt);

    TInt err = KErrNone;
    for ( TInt i = 0; i < arrayTotal; i++ )
        {
        CFbsBitmap* bitmapPtr = NULL;
        CFbsBitmap* maskPtr = NULL;
        
        if( aFromSkin )
            {
            //find new graphic from Skinned bitmap
            TRAP(err, AknsUtils::CreateIconL( aSkin,
                iconSkinIDArray[i],
                bitmapPtr,
                maskPtr,
                KNullDesC,
                iconIDArray[i],
                iconMaskIDArray[i] ));
            }
        //find new graphic from mif file
        else
            {
             TRAP(err, AknIconUtils::CreateIconL(
                bitmapPtr,
                maskPtr,
                KAvkonBitmapFile,
                iconIDArray[i],
                iconMaskIDArray[i] ));            
            }
        if( !err )
            {
            SetGraphics( element[i], bitmapPtr, maskPtr );
            }           
        }
    }
    
  
// ----------------------------------------------------------------------------
// CAknSliderExtension::TryLoadNewSliderBitmap
//
// ----------------------------------------------------------------------------
//
void CAknSliderExtension::TryLoadNSliderVerticalBitmap( MAknsSkinInstance* aSkin )
    {
    
    const TInt iconIDArray[] = 
        {
        EMbmAvkonQgn_graf_nslider_vertical_top,        
        EMbmAvkonQgn_graf_nslider_vertical_bottom,
        EMbmAvkonQgn_graf_nslider_vertical_middle,
        EMbmAvkonQgn_graf_nslider_vertical_marker,
        EMbmAvkonQgn_graf_nslider_vertical_tick_major,
        EMbmAvkonQgn_graf_nslider_vertical_marker
        };
    const TInt iconMaskIDArray[] = 
        {
        EMbmAvkonQgn_graf_nslider_vertical_top_mask,
        EMbmAvkonQgn_graf_nslider_vertical_bottom_mask,
        EMbmAvkonQgn_graf_nslider_vertical_middle_mask,
        EMbmAvkonQgn_graf_nslider_vertical_marker_mask,
        EMbmAvkonQgn_graf_nslider_vertical_tick_major_mask,
        EMbmAvkonQgn_graf_nslider_marker_mask
        }; 
    const TAknsItemID iconSkinIDArray[] = 
        {
        KAknsIIDNone,//KAknsIIDQgnGrafNsliderVerticalTop,        
        KAknsIIDNone,//KAknsIIDQgnGrafNsliderVerticalBottom,
        KAknsIIDNone,//KAknsIIDQgnGrafNsliderVerticalMiddle,
        KAknsIIDNone,// KAknsIIDQgnGrafNsliderVerticalMarker,
        KAknsIIDNone,// KAknsIIDQgnGrafNsliderVerticalTIckMajor,
        KAknsIIDNone//KAknsIIDQgnGrafNsliderVerticalMarker
        };
        
    const TInt element[] = 
        {
        CAknSlider::EElemEmptyLeftCap,
        CAknSlider::EElemEmptyRightCap,
        CAknSlider::EElemEmptyLine,
        CAknSlider::EElemMarker,
        CAknSlider::EElemTickMark,
        CAknSlider::EElemMarkerSelected
        };

    TInt arrayTotal = sizeof( iconIDArray )/sizeof(TInt);

    TInt err = KErrNone;
    CFbsBitmap* bitmapPtr = NULL;
    CFbsBitmap* maskPtr = NULL;    
    for ( TInt i = 0; i < arrayTotal; i++ )
        {
        //find new graphic from Skinned bitmap
        TRAP(err, AknsUtils::CreateIconL( aSkin,
            iconSkinIDArray[i],
            bitmapPtr,
            maskPtr,
            KNullDesC,
            iconIDArray[i],
            iconMaskIDArray[i] ));

        // find new graphic from mif file
       if ( err )
            {
             TRAP(err,AknIconUtils::CreateIconL(
                bitmapPtr,
                maskPtr,
                KAvkonBitmapFile,
                iconIDArray[i],
                iconMaskIDArray[i] ));      
            } 
        if( !err )
            {
            SetGraphics( element[i], bitmapPtr, maskPtr, EFalse );
            }          
        }
    } 
// ----------------------------------------------------------------------------
// CAknSliderExtension::DeleteBitmaps
//
// ----------------------------------------------------------------------------
//
void CAknSliderExtension::DeleteBitmaps()
    {
    TInt i;

    for( i = 0; i <= CAknSlider::EElemMarkerSelected; i++)
        {
        delete iGfx[i].iRgb;
        iGfx[i].iRgb = NULL;
        delete iGfx[i].iMask;
        iGfx[i].iMask = NULL;
      
        }
    }
   
// ----------------------------------------------------------------------------
// CAknSliderExtension::SetGraphics
// ----------------------------------------------------------------------------
//
void CAknSliderExtension::SetGraphics( TInt aElement, 
                                       CFbsBitmap* aBitmap, 
                                       CFbsBitmap* aMask, 
                                       TBool aCustomize )
    {
    // element index is assumed to be valid (no checking)
    
    // no need to set rgb or mask to NULL as we are assigning and won't leave
    delete iGfx[aElement].iRgb;
    iGfx[aElement].iRgb = aBitmap;

    delete iGfx[aElement].iMask;
    iGfx[aElement].iMask = aMask;
    
    // Set the flag to 1
    iGfx[aElement].iCustomizedFlag = aCustomize;
    
    switch( aElement )
        {
        case CAknSlider::EElemFilledLine:
            {
            SetFlag( EFlagFillEnabled );          
            }
            break;
         case CAknSlider::EElemMarker:
            {
            SetFlag( EFlagMarkerEnabled );          
            }
            break;           
        case CAknSlider::EElemTickMark:
            {
            if( aBitmap==NULL && aMask==NULL )
                {
                ClearFlag( EFlagTickMarksEnabled );
                }
            else
                {
                SetFlag( EFlagTickMarksEnabled );   
                }
            }
            break;
        default:
            break;
    
        }
    }

    
// ----------------------------------------------------------------------------
// CAknSliderExtension::UseDefaultGraphics
// ----------------------------------------------------------------------------
//
void CAknSliderExtension::UseDefaultGraphics( TInt aElement )
    {
    // element index is assumed to be valid (no checking)
    
    delete iGfx[aElement].iRgb;
    iGfx[aElement].iRgb = NULL;

    delete iGfx[aElement].iMask;
    iGfx[aElement].iMask = NULL;
    
    iGfx[aElement].iCustomizedFlag = 0;
    }



// ----------------------------------------------------------------------------
// CAknSliderExtension::UsesDefaultGraphics
// ----------------------------------------------------------------------------
//
TBool CAknSliderExtension::UsesDefaultGraphics( TInt aElement ) const
    {
    // element index is assumed to be valid (no checking)
    
    if ( iGfx[aElement].iCustomizedFlag == 0 )
        {
        return ETrue;
        }
    return EFalse;
    }
    
// ----------------------------------------------------------------------------
// CAknSliderExtension::UsesDefaultGraphics
// ----------------------------------------------------------------------------
//
TBool CAknSliderExtension::UsesDefaultGraphics() const
    {
    // element index is assumed to be valid (no checking)

    TBool ret(ETrue);

    ret = ret && UsesDefaultGraphics( CAknSlider::EElemEmptyLeftCap ) && 
                 UsesDefaultGraphics( CAknSlider::EElemEmptyRightCap ) &&
                 UsesDefaultGraphics( CAknSlider::EElemEmptyLine );

    return ret;
    }
    
// ----------------------------------------------------------------------------
// CAknSliderExtension::GetGfx
// ----------------------------------------------------------------------------
//
void CAknSliderExtension::GetGfx( TAknSliderGfx& aGfx, TInt aElement ) const
    {
    // element index is assumed to be valid (no checking)
    
    aGfx = iGfx[aElement];
    }


// ============================================================================
// An internal helper class for creating slider graphics for option setting
// item.
NONSHARABLE_CLASS( CAknSliderIconizer ): public CBase
    {
public:
    static void CreateSettingsIconL( const TRect& aRect, TInt aValue,
                                     CGulIcon* aIcon, const TInt aMinValue,
                                     const TInt aMaxValue );
                                     
    static void ReSizeDefaultSettingsIcons( const TRect& aParent,
                                        CAknSliderIconizer* aIcon );
    static void ReSizeNewSettingsIcons( const TRect& aParent,
                                        CAknSliderExtension* aExtension,
                                        CAknSliderIconizer* aIcon,
                                        TInt aValue, 
                                        const TInt aMinValue, 
                                        const TInt aMaxValue );
private:
    CAknSliderIconizer();
    ~CAknSliderIconizer();
    void DrawSettingsIconL( const TRect& aRect, TInt aValue, CGulIcon* aIcon,
                            const TInt aMinValue, const TInt aMaxValue , 
                            TBool aFlagFilled ) const;
    
    void DrawDefaultSettingsIconL( const TRect& aParent, 
                                   TInt aValue, 
                                   CFbsBitGc* aFbsBitGc,
                                   const TInt aMinValue,
                                    const TInt aMaxValue ) const;
    void DrawNewSettingsIconL( const TRect& aParent, 
                               TInt aValue, 
                               CFbsBitGc* aFbsBitGc,
                               const TInt aMinValue, 
                               const TInt aMaxValue, 
                               TBool aFilledFlag ) const;           
                                
private:
    // Stores the element graphics (rgb icon and mask icon) as bitmaps. Bitmaps
    // are owned.
    TAknSliderGfx iSettingGfx[CAknSlider::EElemMarkerSelected + 1];
   
    };


// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------
//
CAknSliderIconizer::CAknSliderIconizer()
    {
    // Derived from CBase -> members zeroed
    }


// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
//
CAknSliderIconizer::~CAknSliderIconizer()
    {
    }


// ----------------------------------------------------------------------------
// CAknSliderIconizer::CreateSettingsIconL
// ----------------------------------------------------------------------------
//
void CAknSliderIconizer::CreateSettingsIconL(
        const TRect& aRect, TInt aValue, CGulIcon* aIcon,
        const TInt aMinValue, const TInt aMaxValue )
    {
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    
    CAknSliderIconizer* iconizer = new ( ELeave ) CAknSliderIconizer;
    CleanupStack::PushL( iconizer );
    
    // Set default value
    for ( int i = 0; i <= CAknSlider::EElemMarkerSelected; ++i )
        {
        iconizer->iSettingGfx[i].iRgb = NULL;
        iconizer->iSettingGfx[i].iMask = NULL;
        iconizer->iSettingGfx[i].iCustomizedFlag = 0;
        }

    // aRect = set_value_pane
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( aRect,
                        AknLayoutScalable_Avkon::slider_set_pane_cp3() );
    TRect sliderPane = layoutRect.Rect();
     CAknSliderExtension* extension = CAknSliderExtension::NewL();
    CleanupStack::PushL( extension );
           
    // Load bitmaps
    //1.load new graphics from skin
    extension->TryLoadNSliderBitmap( ETrue, skin );
    
    if( extension->UsesDefaultGraphics() )
        {
        //2. load old graphic from skin
        TRAPD( err, { 
                    AknsUtils::CreateIconL( skin,
                        KAknsIIDQgnIndiSliderSet,
                        iconizer->iSettingGfx[CAknSlider::EElemMarker].iRgb, 
                        iconizer->iSettingGfx[CAknSlider::EElemMarker].iMask,
                        KNullDesC,
                        EMbmAvkonQgn_indi_slider_edit,
                        EMbmAvkonQgn_indi_slider_edit_mask );

                    AknsUtils::CreateIconL( skin, 
                        KAknsIIDQgnGrafLinePrimaryHorizontal,
                        iconizer->iSettingGfx[CAknSlider::EElemEmptyLine].iRgb, 
                        iconizer->iSettingGfx[CAknSlider::EElemEmptyLine].iMask,
                        KNullDesC,
                        EMbmAvkonQgn_graf_line_primary_horizontal,
                        EMbmAvkonQgn_graf_line_primary_horizontal_mask );
                    } );
        if( !err )
            {
            ReSizeDefaultSettingsIcons( sliderPane, iconizer );
            }
                        
        //3.load new from mif, must success

        else
            {
            extension->TryLoadNSliderBitmap( EFalse, skin );
            }
        }

    
    //new slider layout
    ReSizeNewSettingsIcons( sliderPane, extension, iconizer, 
                                aValue, aMinValue,aMaxValue );
          
    iconizer->DrawSettingsIconL( aRect, 
                                 aValue, 
                                 aIcon, 
                                 aMinValue, 
                                 aMaxValue,
                  extension->IsFlagSet(CAknSliderExtension::EFlagFillEnabled));
    
    CleanupStack::PopAndDestroy(); // extension, the bitmaps loaded deleted here
    if( iconizer->iSettingGfx[CAknSlider::EElemMarker].iCustomizedFlag == 0 )
        {
        delete iconizer->iSettingGfx[CAknSlider::EElemMarker].iRgb;
        iconizer->iSettingGfx[CAknSlider::EElemMarker].iRgb = NULL; 
        delete iconizer->iSettingGfx[CAknSlider::EElemMarker].iMask;
        iconizer->iSettingGfx[CAknSlider::EElemMarker].iMask = NULL;
        }
    if( iconizer->iSettingGfx[CAknSlider::EElemEmptyLine].iCustomizedFlag == 0 )
        {
        delete iconizer->iSettingGfx[CAknSlider::EElemEmptyLine].iRgb;
        iconizer->iSettingGfx[CAknSlider::EElemEmptyLine].iRgb = NULL; 
        delete iconizer->iSettingGfx[CAknSlider::EElemEmptyLine].iMask;
        iconizer->iSettingGfx[CAknSlider::EElemEmptyLine].iMask = NULL;
        }
    CleanupStack::PopAndDestroy( iconizer );
    }
// ----------------------------------------------------------------------------
// CAknSliderIconizer::ReSizeDefaultSettingsIcons
// ----------------------------------------------------------------------------
//
void CAknSliderIconizer::ReSizeDefaultSettingsIcons( const TRect& aParent,
                                                 CAknSliderIconizer* aIcon )
    {
    TAknLayoutRect temp;
    TRect lineRect,markerRect;    
    //old slider layout
    temp.LayoutRect( aParent,
                        AknLayoutScalable_Avkon::slider_set_pane_g1() );
    lineRect = temp.Rect();
    temp.LayoutRect( aParent,
                        AknLayoutScalable_Avkon::slider_set_pane_g2() );
    markerRect = temp.Rect();
    if( aIcon->iSettingGfx[CAknSlider::EElemEmptyLine].iRgb != NULL &&
        aIcon->iSettingGfx[CAknSlider::EElemMarker].iRgb != NULL )
        {
    AknIconUtils::SetSize( aIcon->iSettingGfx[CAknSlider::EElemEmptyLine].iRgb,
                           lineRect.Size(),
                           EAspectRatioNotPreserved );
    AknIconUtils::SetSize( aIcon->iSettingGfx[CAknSlider::EElemMarker].iRgb, 
                           markerRect.Size() );  
        }
    }
    
// ----------------------------------------------------------------------------
// CAknSliderIconizer::ReSizeNewSettingsIcons
// ----------------------------------------------------------------------------
//
void CAknSliderIconizer::ReSizeNewSettingsIcons( const TRect& aParent,
                                                 CAknSliderExtension* aExtentsion,
                                                 CAknSliderIconizer* aIcon,TInt aValue, 
                                                 const TInt aMinValue, 
                                                 const TInt aMaxValue )
    {
    TAknLayoutRect temp;
    TRect lineRect,markerRect,leftCapRect,rightCapRect,tickRect;
    temp.LayoutRect( aParent,
                AknLayoutScalable_Avkon::slider_set_pane_g4() );
    lineRect = temp.Rect();
    
    temp.LayoutRect( aParent,
            AknLayoutScalable_Avkon::slider_set_pane_g3() );
    leftCapRect = temp.Rect();
    
    temp.LayoutRect( aParent,
            AknLayoutScalable_Avkon::slider_set_pane_g5() );
    rightCapRect = temp.Rect();
    
    temp.LayoutRect( aParent,
            AknLayoutScalable_Avkon::slider_set_pane_g6() );
    markerRect = temp.Rect();
    
    temp.LayoutRect( aParent,
            AknLayoutScalable_Avkon::slider_set_pane_g7() );
    
    tickRect = temp.Rect();

    TSize size;
    for ( int i = 0; i <= CAknSlider::EElemMarkerSelected; ++i )
        {
        if( !aExtentsion->UsesDefaultGraphics(i) )
            {
            aExtentsion->GetGfx( aIcon->iSettingGfx[i], i );
            
            switch( i )
                {
                case CAknSlider::EElemEmptyLine:
                    {
                    size = lineRect.Size();
                    break;
                    }
                case CAknSlider::EElemMarker:
                case CAknSlider::EElemMarkerSelected:
                    {
                    size = markerRect.Size();
                    break;
                    }
                case CAknSlider::EElemTickMark:
                    {
                    size = tickRect.Size();
                    break;
                    }
                case CAknSlider::EElemEmptyLeftCap:
                    {
                    size = leftCapRect.Size();
                    break;
                    }
                case CAknSlider::EElemEmptyRightCap:
                    {
                    size = rightCapRect.Size();
                    break;
                    }
                case CAknSlider::EElemFilledLeftCap:
                    {
                    size = leftCapRect.Size();
                    break;
                    }
                case CAknSlider::EElemFilledRightCap:
                    {
                    size = rightCapRect.Size(); 
                    break;
                    }
                case CAknSlider::EElemFilledLine:
                    {
                    TInt bmpRun = lineRect.Width() + 
                                  leftCapRect.Width() + 
                                  rightCapRect.Width() - 
                                  markerRect.Width();
                    TInt pos = ( ( bmpRun * ( aValue - aMinValue ) ) /
                                 (aMaxValue - aMinValue ) );

                    TPoint markerPos = TPoint( pos + markerRect.iTl.iX, markerRect.iTl.iY );
        
                    size.iWidth = markerPos.iX + (markerRect.Width()/2) - 
                                  lineRect.iTl.iX;
                    size.iHeight = lineRect.Height();
                    break;
                    }
                default:
                Panic( EAknPanicInvalidValue );
                }
            if( aIcon->iSettingGfx[i].iRgb != NULL &&
                aIcon->iSettingGfx[i].iMask != NULL )
                {
                AknIconUtils::SetSize( aIcon->iSettingGfx[i].iRgb, 
                                       size, 
                                       EAspectRatioNotPreserved );
                AknIconUtils::SetSize( aIcon->iSettingGfx[i].iMask, 
                                       size, 
                                       EAspectRatioNotPreserved );
                aIcon->iSettingGfx[i].iCustomizedFlag = 1;                
                }
            }
        }
    }
// ----------------------------------------------------------------------------
// CAknSliderIconizer::DrawSettingsIconL
// ----------------------------------------------------------------------------
//
void CAknSliderIconizer::DrawSettingsIconL(
        const TRect& aRect, TInt aValue, CGulIcon* aIcon,
        const TInt aMinValue, const TInt aMaxValue, TBool aFilledFlag ) const
    {
    // The actual bitmap
    CFbsBitmap* bitmap = new ( ELeave ) CFbsBitmap;
    CleanupStack::PushL( bitmap );

    User::LeaveIfError( bitmap->Create(
            aRect.Size(), CCoeEnv::Static()->ScreenDevice()->DisplayMode() ) );
    CFbsBitGc* fbsBitGc = CFbsBitGc::NewL();
    CleanupStack::PushL( fbsBitGc );
    CFbsBitmapDevice* bmpDevice = CFbsBitmapDevice::NewL( bitmap );
    CleanupStack::PushL( bmpDevice );
    fbsBitGc->Activate( bmpDevice );

    TRect outerRect;
    TRect innerRect;
    TRect origin;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, origin );

    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( origin,
                        AknLayoutScalable_Avkon::listscroll_gen_pane( 0 ) );
    layoutRect.LayoutRect( layoutRect.Rect(),
                        AknLayoutScalable_Avkon::list_gen_pane( 0 ) );
    layoutRect.LayoutRect( layoutRect.Rect(),
                        AknLayoutScalable_Avkon::list_setting_number_pane( 0 ) );
    TRect listSettingPaneRect( layoutRect.Rect() );

    // 1. Background skinning
    TAknLayoutRect innerLayRect;

    // New style LAF data used
#ifdef RD_LIST_STRETCH
    
    // check list stretching from cenrep
    TBool stretchingEnabled;
    CRepository* cenRep = CRepository::NewL( KCRUidAvkon );
    cenRep->Get( KAknAutomaticListStretching, stretchingEnabled );
    delete cenRep;

    if ( Layout_Meta_Data::IsLandscapeOrientation() &&
         Layout_Meta_Data::IsListStretchingEnabled() &&
         stretchingEnabled )
        {
        layoutRect.LayoutRect( listSettingPaneRect,
                        AknLayoutScalable_Avkon::set_value_pane_vc( 0 ) );        
        }
    else
        {
        layoutRect.LayoutRect( listSettingPaneRect,
                        AknLayoutScalable_Avkon::set_value_pane( 0 ) );
        }
#else
    layoutRect.LayoutRect( listSettingPaneRect,
                        AknLayoutScalable_Avkon::set_value_pane( 0 ) );
#endif
    layoutRect.LayoutRect( layoutRect.Rect(),
                        AknLayoutScalable_Avkon::bg_set_opt_pane( 0 ) );
    innerLayRect.LayoutRect( layoutRect.Rect(),
                        AknLayoutScalable_Avkon::bg_set_opt_pane_g1() );

    // Move to 0,0
    outerRect = layoutRect.Rect();
    TPoint skinOffset( -outerRect.iTl.iX, -outerRect.iTl.iY );

    innerRect = innerLayRect.Rect();

    outerRect.Move( skinOffset );
    innerRect.Move( skinOffset );


    // Frame IID for qsn_fr_set_opt_foc_xxxxx
    const TAknsItemID *frameId = &KAknsIIDQsnFrSetOptFoc;

    // Make a control context:
    CAknsFrameBackgroundControlContext* cc =
        CAknsFrameBackgroundControlContext::NewL(
                *frameId, outerRect, innerRect, EFalse );
    CleanupStack::PushL( cc );

    TPoint dstPos( 0, 0 );

    AknsDrawUtils::DrawBackground( AknsUtils::SkinInstance(), cc, NULL,
        *fbsBitGc, dstPos, outerRect, KAknsDrawParamDefault );
    CleanupStack::PopAndDestroy(); // cc

    // 2. Draw the line and marker on top of the background
    // aRect = set_value_pane
    layoutRect.LayoutRect( aRect,
                        AknLayoutScalable_Avkon::slider_set_pane_cp3() );
    TRect parent = layoutRect.Rect();
    

    //new graphic or old
    if( iSettingGfx[CAknSlider::EElemEmptyLeftCap].iCustomizedFlag != 1 &&
        iSettingGfx[CAknSlider::EElemEmptyRightCap].iCustomizedFlag != 1 )
        {
        DrawDefaultSettingsIconL( parent, aValue, fbsBitGc, 
                                  aMinValue, aMaxValue );
        }                               
     else
        {
        DrawNewSettingsIconL(  parent, aValue, fbsBitGc, aMinValue, 
                               aMaxValue, aFilledFlag );
        }                            


    CleanupStack::PopAndDestroy( 2 ); // bmpDevice, fbsBitGc

    // Transfers ownership, so all we need to do is to..
    aIcon->SetBitmap( bitmap );
    CleanupStack::Pop(); // bitmap

    // 3. The mask
    CFbsBitmap* mask = new ( ELeave ) CFbsBitmap;
    CleanupStack::PushL( mask );

    TDisplayMode mode = iSettingGfx[CAknSlider::EElemEmptyLine].iMask->DisplayMode();
    if ( mode == ENone )
        {
        mode = EGray256;
        }
               
    User::LeaveIfError( mask->Create( aRect.Size(), mode ) );
    fbsBitGc = CFbsBitGc::NewL();
    CleanupStack::PushL( fbsBitGc );
    bmpDevice = CFbsBitmapDevice::NewL( mask );
    CleanupStack::PushL( bmpDevice );
    fbsBitGc->Activate( bmpDevice );
    fbsBitGc->SetPenStyle( CGraphicsContext::ENullPen );
    fbsBitGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    fbsBitGc->SetBrushColor( KRgbWhite );
    fbsBitGc->DrawRect( TRect( aRect.Size() ) );
    fbsBitGc->SetBrushStyle( CGraphicsContext::ENullBrush );
    
     AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(), *fbsBitGc,
                              outerRect, innerRect,
                              KAknsIIDQsnFrSetOptFoc,
                              KAknsIIDQsnFrSetOptFocCenter,
                              KAknsSDMAlphaOnly );   
 
    CleanupStack::PopAndDestroy( 2 ); // bmpDevice, fbsBitGc

    // Transfers ownership, so all we need to do is to..
    aIcon->SetMask( mask );
    CleanupStack::Pop(); // mask
    
    }
 // ----------------------------------------------------------------------------
// CAknSliderIconizer::DrawDefaultSettingsIconL
// ----------------------------------------------------------------------------
//     
void CAknSliderIconizer::DrawDefaultSettingsIconL(
        const TRect& aParent, TInt aValue, CFbsBitGc* aFbsBitGc,
        const TInt aMinValue, const TInt aMaxValue ) const
    {
    TRect lineRect, markerRect;
    TInt bitmapRun;
    TAknLayoutRect layoutRect;
      
    layoutRect.LayoutRect( aParent,
                    AknLayoutScalable_Avkon::slider_set_pane_g1() );

    lineRect = layoutRect.Rect(); 
    TAknLayoutRect markerLayout;
    markerLayout.LayoutRect( aParent,
                        AknLayoutScalable_Avkon::slider_set_pane_g2() );
    markerRect = markerLayout.Rect(); 
    bitmapRun = lineRect.Width() - markerRect.Width();
    
    //new graphic and old graphic is in the same place
    aFbsBitGc->BitBltMasked( TPoint( lineRect.iTl.iX, lineRect.iTl.iY ),
                        iSettingGfx[CAknSlider::EElemEmptyLine].iRgb,
                        TRect( 0, 0, lineRect.Width(), lineRect.Height()),
                        iSettingGfx[CAknSlider::EElemEmptyLine].iMask,
                        EFalse);
     // Calculate the correct position where to draw the marker
    
    TInt range = aMaxValue - aMinValue;
    // It is this expression which determines the functional direction of
    // the slider in its drawing (but not its event handling).
    TInt pos = ( ( bitmapRun * ( aValue - aMinValue ) ) / range );

    TPoint markerPos = TPoint( pos + markerRect.iTl.iX, markerRect.iTl.iY );
    TRect srcRect( 0, 0, markerRect.Width(), markerRect.Height() );
                                 
    aFbsBitGc->BitBltMasked( markerPos, 
                  iSettingGfx[CAknSlider::EElemMarker].iRgb, 
                  srcRect,
                  iSettingGfx[CAknSlider::EElemMarker].iMask,
                  EFalse); 
    }
// ----------------------------------------------------------------------------
// CAknSliderIconizer::DrawNewSettingsIconL
// ----------------------------------------------------------------------------
//    
void CAknSliderIconizer::DrawNewSettingsIconL(
        const TRect& aParent, TInt aValue, CFbsBitGc* aFbsBitGc,
        const TInt aMinValue, const TInt aMaxValue, TBool aFilledFlag ) const
    {
    TRect lineRect, markerRect, leftCapRect, rightCapRect, tickRect;
    TInt bitmapRun;
    TAknLayoutRect layoutRect;
          
    layoutRect.LayoutRect( aParent,
            AknLayoutScalable_Avkon::slider_set_pane_g4() );
    lineRect = layoutRect.Rect();
    
    layoutRect.LayoutRect( aParent,
            AknLayoutScalable_Avkon::slider_set_pane_g3() );
    leftCapRect = layoutRect.Rect();
    
    layoutRect.LayoutRect( aParent,
            AknLayoutScalable_Avkon::slider_set_pane_g5() );
    rightCapRect = layoutRect.Rect();
    
    layoutRect.LayoutRect( aParent,
            AknLayoutScalable_Avkon::slider_set_pane_g6() );
    markerRect = layoutRect.Rect();
    
    layoutRect.LayoutRect( aParent,
            AknLayoutScalable_Avkon::slider_set_pane_g7() );
    
    tickRect = layoutRect.Rect();
    bitmapRun = lineRect.Width() +
                leftCapRect.Width() +
                rightCapRect.Width() - 
                markerRect.Width();
                
         //new graphic and old graphic is in the same place
    aFbsBitGc->BitBltMasked( TPoint( lineRect.iTl.iX, lineRect.iTl.iY ),
                            iSettingGfx[CAknSlider::EElemEmptyLine].iRgb,
                            TRect( 0, 0, lineRect.Width(), lineRect.Height()),
                            iSettingGfx[CAknSlider::EElemEmptyLine].iMask,
                            EFalse);
     //leftcap, rightcap,filled line,tick                                      
    aFbsBitGc->BitBltMasked( TPoint( leftCapRect.iTl.iX, leftCapRect.iTl.iY ),
                            iSettingGfx[CAknSlider::EElemEmptyLeftCap].iRgb,
                            TRect(0, 0, leftCapRect.Width(), leftCapRect.Height()),
                            iSettingGfx[CAknSlider::EElemEmptyLeftCap].iMask,
                            EFalse);
    aFbsBitGc->BitBltMasked( TPoint( rightCapRect.iTl.iX, rightCapRect.iTl.iY ),
                            iSettingGfx[CAknSlider::EElemEmptyRightCap].iRgb,
                            TRect( 0, 0, rightCapRect.Width(), rightCapRect.Height()),
                            iSettingGfx[CAknSlider::EElemEmptyRightCap].iMask,
                            EFalse );
    // Calculate the correct position where to draw the marker
    
    TInt range = aMaxValue - aMinValue;
    // It is this expression which determines the functional direction of
    // the slider in its drawing (but not its event handling).
    TInt pos = ( ( bitmapRun * ( aValue - aMinValue ) ) / range );

    TPoint markerPos = TPoint( pos + markerRect.iTl.iX, markerRect.iTl.iY );
                              
    //filled enable, draw filled line
    if( aFilledFlag )
        {
        // filled line and cap
        TInt fillWidth = markerPos.iX + markerRect.Width()/2 - lineRect.iTl.iX;
        aFbsBitGc->BitBltMasked( TPoint( lineRect.iTl.iX, lineRect.iTl.iY ),
                        iSettingGfx[CAknSlider::EElemFilledLine].iRgb,
                        TRect(0, 0, fillWidth, lineRect.Height()),
                        iSettingGfx[CAknSlider::EElemFilledLine].iMask,
                        EFalse);
        //left cap always filled
        if( aValue != aMinValue )
            {
            aFbsBitGc->BitBltMasked( TPoint( lineRect.iTl.iX, lineRect.iTl.iY ),
                        iSettingGfx[CAknSlider::EElemFilledLeftCap].iRgb,
                        TRect(0, 0, leftCapRect.Width(), leftCapRect.Height()),
                        iSettingGfx[CAknSlider::EElemFilledLine].iMask,
                        EFalse);               
            }

        //only when the line filled, the right cap filled                
        if( aValue >= aMaxValue )
            {
            aFbsBitGc->BitBltMasked( TPoint( lineRect.iTl.iX, lineRect.iTl.iY ),
                        iSettingGfx[CAknSlider::EElemFilledRightCap].iRgb,
                        TRect( 0, 0, rightCapRect.Width(), rightCapRect.Height()),
                        iSettingGfx[CAknSlider::EElemFilledLine].iMask,
                        EFalse);                
            }

        }
    else
        {
         TRect srcRect( 0, 0, markerRect.Width(), markerRect.Height() );
        
        aFbsBitGc->BitBltMasked( markerPos, 
                          iSettingGfx[CAknSlider::EElemMarker].iRgb, 
                          srcRect,
                          iSettingGfx[CAknSlider::EElemMarker].iMask,
                          EFalse);        
        }
                      
                    
    }
// ============================================================================

// ----------------------------------------------------------------------------
// Default constructor
// ----------------------------------------------------------------------------
//
EXPORT_C CAknSlider::CAknSlider()
    {
    // Derived from CBase -> members zeroed
    AKNTASHOOK_ADD( this, "CAknSlider" );
    }


// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
//
EXPORT_C CAknSlider::~CAknSlider()
    {
    AKNTASHOOK_REMOVE();
    AknsUtils::DeregisterControlPosition( this );
    delete iValueLabel;
    delete iMinLabel;
    delete iMaxLabel;
    delete iMarkerBmp;
    delete iMarkerMaskBmp;
    delete iImage;
    delete iData;
    delete iExt;
    }


// ----------------------------------------------------------------------------
// CAknSlider::ConstructL
// Creates the labels.
// ----------------------------------------------------------------------------
//
void CAknSlider::ConstructL()
    {
    iExt = CAknSliderExtension::NewL();

    InitializeBitmapsL();
    

    iValueLabel = new( ELeave ) CEikLabel;
    iValueLabel->UseLogicalToVisualConversion( EFalse );
    iValueLabel->SetContainerWindowL( *this );

    iMinLabel = new( ELeave ) CEikLabel;
    iMinLabel->SetContainerWindowL( *this );

    iMaxLabel = new( ELeave ) CEikLabel;
    iMaxLabel->SetContainerWindowL( *this );

    if ( AknLayoutUtils::PenEnabled() && ( &Window() != NULL ) )
        {
        // Enable drag events, it will then be possible to drag from thumb
        EnableDragEvents();
        //Enable dragging to start from thumb and then move outside the slider
        DrawableWindow()->SetPointerGrab( ETrue );
        }        
    }
    

// ----------------------------------------------------------------------------
// CAknSlider::InitializeBitmapsL
// ----------------------------------------------------------------------------
//
void CAknSlider::InitializeBitmapsL()
    {
    
    if ( iExt->iLineIcon )
        {
        delete iExt->iLineIcon;
        iExt->iLineIcon = NULL;
        delete iExt->iLineIconMask;
        iExt->iLineIconMask = NULL;
        }
    iExt->DeleteBitmaps(); 
           
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    
   if( Layout() == EAknSliderLayoutVertical ) //vertical
        {
        //1.load default graphic for new vertical slider
        iExt->ClearFlag( CAknSliderExtension::EFlagHorizontal );
        iExt->TryLoadNSliderVerticalBitmap( skin );

        }
        
   else if ( Layout() == EAknSliderLayoutHorizontal )
            {
            iExt->TryLoadNSliderBitmap( ETrue, skin  ); 
            }
  
   else // horizonal
        {
        //1.load new from skin
        iExt->TryLoadNSliderBitmap( ETrue, skin  );  
        if( iExt->UsesDefaultGraphics() )
            {
            //2.load old from skin
            TRAPD( err,
                {
                AknsUtils::CreateIconL( skin, 
                                        KAknsIIDQgnGrafLinePrimaryHorizontal,
                                        iExt->iLineIcon, 
                                        iExt->iLineIconMask,
                                        KNullDesC,
                                        EMbmAvkonQgn_graf_line_primary_horizontal,
                                        EMbmAvkonQgn_graf_line_primary_horizontal_mask);
                AknsUtils::CreateIconL( skin, 
                                        KAknsIIDQgnIndiSliderEdit,
                                        iMarkerBmp, 
                                        iMarkerMaskBmp,
                                        KNullDesC,
                                        EMbmAvkonQgn_indi_slider_edit,
                                        EMbmAvkonQgn_indi_slider_edit_mask);
                                        
                } );                                  
            //3.load new from mif, must success.
            if( err )
                {
                
                iExt->TryLoadNSliderBitmap( EFalse, skin );
                }
            }

         }
    
    }


// ----------------------------------------------------------------------------
// CAknSlider::SetValueL
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknSlider::SetValueL( TInt aValue )
    {
    // Note that this assert will panic any value that is not aligned on the
    // step size relative to the minimum value;
    __ASSERT_DEBUG( aValue >= MinimumValue() &&
                    aValue<= MaximumValue() &&
                    ( aValue-MinimumValue() ) % StepSize() == 0,
                    Panic( EAknPanicOutOfRange ) );
    iValue = aValue;
    if ( iValueLabel != NULL )
        {
        SetValueTextL();
        }
    }


// ----------------------------------------------------------------------------
// CAknSlider::Value
// ----------------------------------------------------------------------------
//
EXPORT_C TInt CAknSlider::Value() const
    {
    return iValue;
    }


// ----------------------------------------------------------------------------
// CAknSlider::CreateBitmapL
// Returns slider bitmap to "list pane for setting item" (setting option item
// slider graphic). Ownership of the bitmap is transferred to the caller.
// ----------------------------------------------------------------------------
//
EXPORT_C CFbsBitmap* CAknSlider::CreateBitmapL( TInt aValue, TInt aResourceId )
    {
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, aResourceId );

    reader.ReadInt16(); // ignore layout
    TInt minValue = reader.ReadInt16();
    TInt maxValue = reader.ReadInt16();
    CleanupStack::PopAndDestroy(); // reader

    return CreateBitmapL( aValue, minValue, maxValue );
    }


// ----------------------------------------------------------------------------
// CAknSlider::CreateBitmapL
// Returns slider bitmap to "list pane for setting item" (setting option item
// slider graphic). Ownership of the bitmap is transferred to the caller.
// ----------------------------------------------------------------------------
//
EXPORT_C CFbsBitmap* CAknSlider::CreateBitmapL(
        TInt aValue, TInt aMinimumValue, TInt aMaximumValue )
    {
    CGulIcon* icon = CreateSetStyleListBoxIconL(
            aValue, aMinimumValue, aMaximumValue ); // now have ownership
    icon->SetBitmapsOwnedExternally( ETrue );
    CFbsBitmap* bitmap = icon->Bitmap();
    CFbsBitmap* mask = icon->Mask();
    delete icon;
    delete mask;
    return bitmap; // ownership transferred
    }


// ----------------------------------------------------------------------------
// CAknSlider::CreateSetStyleListBoxIconL
// Returns slider icon to "list pane for setting item" (setting option item
// slider graphic). Ownership of the icon is transferred to the caller.
// ----------------------------------------------------------------------------
//
EXPORT_C CGulIcon* CAknSlider::CreateSetStyleListBoxIconL(
        TInt aValue, TInt aResourceId )
    {
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, aResourceId );

    reader.ReadInt16(); // ignore layout
    TInt minValue = reader.ReadInt16();
    TInt maxValue = reader.ReadInt16();
    CleanupStack::PopAndDestroy(); // reader
    
    return CreateSetStyleListBoxIconL( aValue, minValue, maxValue );
    }


// ----------------------------------------------------------------------------
// CAknSlider::CreateSetStyleListBoxIconL
// Returns slider icon to "list pane for setting item" (setting option item
// slider graphic). Ownership of the icon is transferred to the caller.
// ----------------------------------------------------------------------------
//
EXPORT_C CGulIcon* CAknSlider::CreateSetStyleListBoxIconL(
        TInt aValue, TInt aMinimumValue, TInt aMaximumValue )
    {
    __ASSERT_ALWAYS( aMaximumValue > aMinimumValue,
                     Panic( EAknPanicOutOfRange ) );
    __ASSERT_ALWAYS( ( aValue <= aMaximumValue ) &&
                     ( aValue >= aMinimumValue ),
                     Panic( EAknPanicOutOfRange ) );

    // Make the icon and put it in the array
    CGulIcon* icon = CGulIcon::NewLC();

    TRect origin;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, origin );

    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( origin,
                        AknLayoutScalable_Avkon::listscroll_gen_pane( 0 ) );
    layoutRect.LayoutRect( layoutRect.Rect(),
                        AknLayoutScalable_Avkon::list_gen_pane( 0 ) );
    layoutRect.LayoutRect( layoutRect.Rect(),
                        AknLayoutScalable_Avkon::list_setting_number_pane( 0 ) );
    TRect listSettingPaneRect( layoutRect.Rect());
#ifdef RD_LIST_STRETCH
    // check list stretching from cenrep
    TBool stretchingEnabled;
    CRepository* cenRep = CRepository::NewL( KCRUidAvkon );
    cenRep->Get( KAknAutomaticListStretching, stretchingEnabled );
    delete cenRep;

    if ( Layout_Meta_Data::IsLandscapeOrientation() &&
         Layout_Meta_Data::IsListStretchingEnabled() &&
         stretchingEnabled )
        {
        layoutRect.LayoutRect( layoutRect.Rect(),
                        AknLayoutScalable_Avkon::set_value_pane_vc( 0 ) );
        }
    else
        {
        layoutRect.LayoutRect( layoutRect.Rect(),
                        AknLayoutScalable_Avkon::set_value_pane( 0 ) );
        }
#else
    layoutRect.LayoutRect( layoutRect.Rect(),
                        AknLayoutScalable_Avkon::set_value_pane( 0 ) );
#endif    
    TRect setValuePaneRect( layoutRect.Rect() );
    TRect rect( setValuePaneRect );

    // Move to 0,0
    rect.Move( -rect.iTl.iX, -rect.iTl.iY );
    CAknSliderIconizer::CreateSettingsIconL( rect, aValue, icon,
                                              aMinimumValue, aMaximumValue );
    CleanupStack::Pop( icon ); // icon - not owned anymore, do not destroy
    return icon; // ownership transferred
    }


// ----------------------------------------------------------------------------
// CAknSlider::SetRange
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknSlider::SetRange( TInt aMinimumValue, TInt aMaximumValue )
    {
    SliderData()->SetRange( aMinimumValue, aMaximumValue );
    }

// ----------------------------------------------------------------------------
// CAknSlider::GetRange
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknSlider::GetRange( TInt& aMinimumValue, TInt& aMaximumValue )
    {
    aMaximumValue = MaximumValue();
    aMinimumValue = MinimumValue();
    }

// ----------------------------------------------------------------------------
// CAknSlider::SetStepSize
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknSlider::SetStepSize( TInt aStepSize )
    {
    // This assert is only done for CAknSlider, as the step size is not
    // particularly relevant for the data; That is, if you are just interested
    // in CAknSliderData in order to format a value label, then you might want
    // to ignore the restrictions on stepsize
    __ASSERT_ALWAYS( aStepSize != 0 && SliderData()->Range() % aStepSize == 0,
                     Panic( EAknPanicOutOfRange ) );
    SliderData()->iStepSize = aStepSize;
    }


// ----------------------------------------------------------------------------
// CAknSlider::SetValueTextL 
// Sets the text for the value label.
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknSlider::SetValueTextL()
    {
    TBuf<KValueLabelTextMaxLength + KAknBidiExtraSpacePerLine> textBuf;
    DoSetValueTextL( textBuf, iValue, *SliderData() );
    AknBidiTextUtils::ConvertToVisualAndClipL( textBuf,
                                               *( iValueLabel->Font() ),
                                               iValueLabel->Size().iWidth,
                                               iValueLabel->Size().iWidth );
    iValueLabel->SetTextL( textBuf );
    }
    

// ----------------------------------------------------------------------------
// CAknSlider::DoSetValueTextL
// ----------------------------------------------------------------------------
//
void CAknSlider::DoSetValueTextL( TDes& aTextBuf, TInt aValue,
                                  const CAknSliderData& aSliderData )
    {
    TBuf<KAknSliderValueLabelValueMaxLength> valueBuf;
    _LIT( KBareFigure, "%d" );
    _LIT( KFraction, "%d/%d" );

    switch ( aSliderData.iValueType )
        {
        case EAknSliderValueBareFigure:
            valueBuf.Format( KBareFigure, aValue ); // bare figure
            break;

        case EAknSliderValuePercentage:
            {
            TInt num = ( 100 * ( aValue - aSliderData.iMinimumValue ) ) / 
                         aSliderData.Range();                                
            HBufC* percentage = StringLoader::LoadLC( R_QTN_SELECT_SLIDER_VALUE,num ); 
            valueBuf.Copy( *percentage );
            CleanupStack::PopAndDestroy( percentage );              
            }            
            break;

        case EAknSliderValueFraction:
            valueBuf.Format( KFraction, aValue, aSliderData.iMaximumValue ); // x/y
            break;

        case EAknSliderValueDecimal:
            {
            TReal r;
            Math::Pow10( r, aSliderData.DecimalPlaces() );
            // First have to format the format.
            TBuf<8> format;
            // This allows for 2 digit field size and/or decimal places
            _LIT( KFormatTemplate, "%%-%d.%df" );
            format.Format( KFormatTemplate,
                           KAknSliderValueLabelValueMaxLength,
                           aSliderData.DecimalPlaces() );
            valueBuf.Format( format, aValue / r );
            valueBuf.TrimAll();
            }
            break;
        default:
            break; // valueBuf left empty
        } // end switch

    // Convert this formatted number if necessary to display language-sensitive
    // numerals
    AknTextUtils::DisplayTextLanguageSpecificNumberConversion( valueBuf );

    // A text pointer for the format string
    TPtr formatPtr( 0, 0 );

    if ( aSliderData.iText != NULL )
        {
        formatPtr.Set( aSliderData.iText->Des() );
        }

    if ( aSliderData.iSingularText != NULL )
        {
        // format with %U in the supplied text. But only if value = 1 and we
        // are using bare figure layout
        if ( ( aValue == 1 ) &&
             ( aSliderData.iValueType == EAknSliderValueBareFigure ) )
            {
            formatPtr.Set( aSliderData.iSingularText->Des() );
            }
        }

    if ( formatPtr.Length() > 0 )
        {
        FormatWithOrWithoutTokenL( aTextBuf, formatPtr, valueBuf );
        }
    else
        {
        aTextBuf.Copy( valueBuf.Left( KAknSliderValueLabelValueMaxLength ) );
        }
    }


// ----------------------------------------------------------------------------
// CAknSlider::FormatWithOrWithoutTokenL
//
// This method is used to protect the call to StringLoader::Format against
// passing it texts with no token. If you do, it panics.
//
// The protection here is still far from perfect, as only % is looked for. So
// there is still a problem.
//
// StringLoader itself should take on this responsibility and not panic. In
// this case, the call to this routine would just be the code in the 2nd half.
// ----------------------------------------------------------------------------
//
void CAknSlider::FormatWithOrWithoutTokenL(
        TDes& aOutput, const TDesC& aFormat, const TDesC& aValue )
    {
    if ( aFormat.Locate('%') == -1 )
        {
        aOutput.Copy( aFormat.Left( KValueLabelTextMaxLength ) );
        }
    else
        {
        // We can know that the length of the resulting formatted string will
        // be less than or equal to the sum of the two lengths Wierd effects in
        // string loader mean we have to add 2 more (It adds key length instead
        // of subtracting it sometimes)....
        TInt safeLength = aValue.Length() + aFormat.Length() +
                          KAknSliderFormatKeyLength;

        // No leaving methods are going to be called
        HBufC* wholeTextBuf = HBufC::NewL( safeLength );
        TPtr wholeTextPtr = wholeTextBuf->Des();

        // Value for when no %U or when there is no number (%NU)
        TInt keyIndex = -1;
        StringLoader::Format( wholeTextPtr, aFormat, keyIndex, aValue );
        aOutput.Copy( wholeTextPtr.Left( KValueLabelTextMaxLength ) );

        delete wholeTextBuf;
        }
    }


// ----------------------------------------------------------------------------
// DoSetLabelTextL
// Local function to gather together arabization of minimum/maximum strings.
// Static to make the function local to this compilation unit only (i.e. not
// polluting the global namespace).
// ----------------------------------------------------------------------------
static void DoSetLabelTextL( const TDesC& aText, CEikLabel* aLabel )
    {
    if ( aLabel )
        {
        HBufC* localBuf = aText.AllocLC();
        TPtr ptr = localBuf->Des();
        AknTextUtils::DisplayTextLanguageSpecificNumberConversion( ptr );
        aLabel->SetTextL( ptr ); // Makes copy of buffer
        CleanupStack::PopAndDestroy( localBuf );
        }
    }


// ----------------------------------------------------------------------------
// CAknSlider::SetMinimumTextL
// Sets the text for the minimum label.
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknSlider::SetMinimumTextL( const TDesC& aText )
    {
    DoSetLabelTextL( aText, iMinLabel );
    }


// ----------------------------------------------------------------------------
// CAknSlider::SetMaximumTextL
// Sets the text for the maximum label.
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknSlider::SetMaximumTextL( const TDesC& aText )
    {
    DoSetLabelTextL( aText, iMaxLabel );
    }


// ----------------------------------------------------------------------------
// CAknSlider::MinimumSize
// ----------------------------------------------------------------------------
//
TSize CAknSlider::MinimumSize()
    {
    TInt index = 0;

    if ( iEditable )
        {
        if ( Layout() == EAknFormSliderLayout3 )
            {
            index = 0;
            }
        else if ( Layout() == EAknFormSliderLayout2 )
            {
            index = 1;
            }
        else if ( Layout() == EAknFormSliderLayout1 )
            {
            index = 2;
            } 
        }

    TAknLayoutRect temp, layout;
    temp.LayoutRect( TRect( 0, 0, 0, 0 ),
                             AknLayoutScalable_Avkon::Screen() );
                             
    layout.LayoutRect( temp.Rect(),
                       AknLayoutScalable_Avkon::listscroll_form_pane() );
    temp.LayoutRect( layout.Rect(),
                     AknLayoutScalable_Avkon::list_form_gen_pane() );
    layout.LayoutRect( temp.Rect(),
                       AknLayoutScalable_Avkon::form_field_slider_pane( index ) );

    return layout.Rect().Size();
    }


// ----------------------------------------------------------------------------
// CAknSlider::OfferKeyEventL
// Handles the key events.
// ----------------------------------------------------------------------------
//
TKeyResponse CAknSlider::OfferKeyEventL(
        const TKeyEvent& aKeyEvent, TEventCode aType )
    {
    // If not a key event or in view mode
    if ( aType != EEventKey || !iEditable )
        {
        return EKeyWasNotConsumed;
        }

    TInt step = StepSize();
    TBool hor = iExt->IsFlagSet( CAknSliderExtension::EFlagHorizontal );
    iExt->iPenInputPos = TPoint( -1, -1 );

    if ( EKeyLeftArrow == aKeyEvent.iCode && hor )
        {
        TranslateValueL( -step );
        }
    else if ( EKeyRightArrow == aKeyEvent.iCode && hor )
        {
        TranslateValueL( step );
        }
    else if ( EKeyDownArrow == aKeyEvent.iCode && !hor )
        {
        TranslateValueL( -step );
        }
    else if ( EKeyUpArrow == aKeyEvent.iCode && !hor )
        {
        TranslateValueL( step );
        }
    else
        {
        return EKeyWasNotConsumed;
        }

    return EKeyWasConsumed;
    }


// ----------------------------------------------------------------------------
// CAknSlider::ConstructFromResourceL
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknSlider::ConstructFromResourceL( TResourceReader& aReader )
    {
    iData = CAknSliderData::NewL( aReader );
    ConstructL();

    // Apply constraints on the read stepsize here
    SetStepSize( StepSize() );

    // Set the labels up
    if ( SliderData()->iMinimumLabelText )
        {
        SetMinimumTextL( *( SliderData()->iMinimumLabelText ) );
        }

    if ( SliderData()->iMaximumLabelText )
        {
        SetMaximumTextL( *( SliderData()->iMaximumLabelText ) );
        }

    // Create graphics if needed
    if ( Layout() == EAknSettingsItemSliderLayoutWithGraphics )
        {
        CreateDecoratorImageFromResourceL( SliderData()->iDecoratorImageId );
        }

    TAknLayoutRect layoutRect;
    TRect containerRect;
    if( Layout() == EAknSliderLayoutVertical )
        {
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EApplicationWindow,
                                       containerRect );

        layoutRect.LayoutRect(containerRect,AknLayoutScalable_Avkon::main_pane(13) );
        containerRect = layoutRect.Rect();
        
        layoutRect.LayoutRect( containerRect,
            AknLayoutScalable_Avkon::popup_slider_window(0) );
        containerRect = layoutRect.Rect();   
         
        SetRect( containerRect );
        }
    else if( Layout() == EAknSliderLayoutHorizontal )
        {
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EApplicationWindow,
                                       containerRect );

        layoutRect.LayoutRect(containerRect,AknLayoutScalable_Apps::main_pane(0) );
        containerRect = layoutRect.Rect();
        
        layoutRect.LayoutRect( containerRect,
            AknLayoutScalable_Apps::main_video_tele_pane(0) );
        containerRect = layoutRect.Rect();
        
        layoutRect.LayoutRect( containerRect,
            AknLayoutScalable_Apps::popup_vtel_slider_window(0) );
        containerRect = layoutRect.Rect();

        SetRect( containerRect );
        }
    else
        {
        SetRect( MinimumSize() );
        }
   
    
    SetValueTextL();
    }


// ----------------------------------------------------------------------------
// CAknSlider::ConstructFromResourceL
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknSlider::ConstructFromResourceL(
        CCoeControl* aParent, TInt aValue, TResourceReader& aReader )
    {
    SetContainerWindowL( *aParent );
    ConstructFromResourceL( aReader ); // Call basic ConstructFromResourceL()
    SetValueL( aValue );
    ActivateL();
    //DrawNow();
    }


// ----------------------------------------------------------------------------
// CAknSlider::HandleResourceChange
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknSlider::HandleResourceChange( TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );
    
    switch ( aType )
        {
        case KEikMessageCaptionedControlEditableStateChange:
            {
            iEditable = ETrue;
            MTouchFeedback* feedback = MTouchFeedback::Instance();
            if ( feedback )
                {
                feedback->EnableFeedbackForControl( this, ETrue );
                }
            }            
            break;
        case KEikMessageCaptionedControlNotEditableStateChange:
            {
            iEditable = EFalse;
            MTouchFeedback* feedback = MTouchFeedback::Instance();
            if ( feedback )
                {
                feedback->EnableFeedbackForControl( this, EFalse );
                }       
            }            
            break;

        case KAknsMessageSkinChange:
            {
            SetLabelColor();
            }
            break;
        default:
            break;
        }
    }


// ----------------------------------------------------------------------------
// CAknSlider::CountComponentControls
// Standard CCoeControl routine to return the number of component controls.
// ----------------------------------------------------------------------------
//
EXPORT_C TInt CAknSlider::CountComponentControls() const
    {
    TInt count = 0;
    CCoeControl* controls[] = { iValueLabel, iMaxLabel, iMinLabel, iImage };
    for ( TUint ii = 0; ii < sizeof( controls ) / sizeof( CCoeControl* ); ++ii )
        {
        if ( controls[ii] )
            {
            count++;
            }
        }
    return count;
    }


// ----------------------------------------------------------------------------
// CAknSlider::ComponentControl
// Standard CCoeControl routine to return the control at a given index
// ----------------------------------------------------------------------------
//
EXPORT_C CCoeControl* CAknSlider::ComponentControl( TInt aIndex ) const
    {
    CCoeControl* controls[] = { iValueLabel, iMaxLabel, iMinLabel, iImage };
    for ( TUint ii = 0; ii < sizeof( controls ) / sizeof( CCoeControl* ); ++ii )
        {
        if ( controls[ii] && aIndex-- == 0 )
            {
            return controls[ii];
            }
        }
    return NULL;
    }


// ----------------------------------------------------------------------------
// CAknSlider::SizeChanged
// Sets the layout.
// ----------------------------------------------------------------------------
//
void CAknSlider::SizeChanged()
    {
    switch ( Layout() )
        {
        case EAknFormSliderLayout1:
            {
            FormSliderLayout1();
            break;
            }
        case EAknFormSliderLayout2:
            {
            FormSliderLayout2();
            break;
            }
        case EAknFormSliderLayout3:
            {
            FormSliderLayout3();
            break;
            }
        case EAknSettingsItemSliderLayout:
        case EAknSettingsItemSliderLayoutWithGraphics:
      
            {
            SettingsItemSliderLayout();
            break;
            }
        case EAknMIDPFormSliderLayout:
            {
            MIDPFormSliderLayout();
            break;
            }
         case EAknSliderLayoutVertical:        
            {
            VerticalSliderLayout();
            break;
            } 
        case EAknSliderLayoutHorizontal:
            {
            HorizontalSliderLayout();
            break;
            }
                      
        default:
            break;
        }

    TAknLayoutRect horLine;

    if ( Layout() == EAknSettingsItemSliderLayout ||
         Layout() == EAknSettingsItemSliderLayoutWithGraphics  ||
         Layout() == EAknSliderLayoutVertical ||
         Layout() == EAknSliderLayoutHorizontal )
        {
        horLine.LayoutRect( iMarkerArea,
                AKN_LAYOUT_WINDOW_Slider_pane_elements_Line_1 );
        }
    else
        {
        horLine.LayoutRect( iMarkerArea,
                AKN_LAYOUT_WINDOW_Slider_pane_elements__form__Line_1 );
        }

    TRect horRect = horLine.Rect();
    iColor = horLine.Color();

    SetLabelColor();
    AknsUtils::RegisterControlPosition( this );
    }


// ----------------------------------------------------------------------------
// CAknSlider::FormSliderLayout1
// Pure layout function. Value label is shown in the same place in View and
// Edit modes.
// ----------------------------------------------------------------------------
//
void CAknSlider::FormSliderLayout1()
    {
    TRect rect = Rect();
    AknLayoutUtils::LayoutLabel( iValueLabel, rect,
            AKN_LAYOUT_TEXT_Form_slider_field_texts_Line_2 );

    TAknLayoutRect layoutRect;
     
    // slider_form_pane
    TAknLayoutRect temp, layout;
    temp.LayoutRect( rect,
                AknLayoutScalable_Avkon::slider_cont_pane( 2 ) );

    layout.LayoutRect( temp.Rect(),
                AknLayoutScalable_Avkon::slider_form_pane( 1 ) );
    iMarkerArea = layout.Rect();
                
    // Load new slider layout if exist
    if(  !(iExt->UsesDefaultGraphics()) )
        {
        temp.LayoutRect( layout.Rect(),
                AknLayoutScalable_Avkon::slider_form_pane_g4() );
        iLineRect = temp.Rect();
        
        temp.LayoutRect( layout.Rect(),
                AknLayoutScalable_Avkon::slider_form_pane_g3() );
        iExt->iLeftCapRect = temp.Rect();
        
        temp.LayoutRect( layout.Rect(),
                AknLayoutScalable_Avkon::slider_form_pane_g5() );
        iExt->iRightCapRect = temp.Rect();
        
        temp.LayoutRect( layout.Rect(),
                AknLayoutScalable_Avkon::slider_form_pane_g7() ); 
        iExt->iTickRect = temp.Rect();
   
        temp.LayoutRect( layout.Rect(),        
                AknLayoutScalable_Avkon::slider_form_pane_g6() );
        iExt->iThumbRect = temp.Rect();
        
        }
    else
        {
        temp.LayoutRect( layout.Rect(),
                         AknLayoutScalable_Avkon::slider_form_pane_g1() );
        AknIconUtils::SetSize( iExt->iLineIcon, temp.Rect().Size() );
        iLineRect = temp.Rect();
        
        temp.LayoutRect( layout.Rect(),
                         AknLayoutScalable_Avkon::slider_form_pane_g2() );
        iExt->iThumbRect = temp.Rect(); 
        }
    }


// ----------------------------------------------------------------------------
// CAknSlider::FormSliderLayout2
// Pure layout function. Value label is not shown in the same place in Edit
// mode.
// ----------------------------------------------------------------------------
//
void CAknSlider::FormSliderLayout2()
    {
    TRect rect = Rect();
    if ( iEditable )
        {
        AknLayoutUtils::LayoutLabel( iMinLabel, rect,
                AKN_LAYOUT_TEXT_Form_slider_field_texts_Line_3( 0, 0 ) );
        AknLayoutUtils::LayoutLabel( iMaxLabel, rect,
                AKN_LAYOUT_TEXT_Form_slider_field_texts_Line_3( 2, 2 ) );

        TAknLayoutRect temp, layout;
        temp.LayoutRect( rect,
                AknLayoutScalable_Avkon::slider_cont_pane( 1 ) );

        layout.LayoutRect( temp.Rect(),
                AknLayoutScalable_Avkon::slider_form_pane( 0 ) );
        iMarkerArea = layout.Rect();
        //Load new slider layout if exist
        if( !(iExt->UsesDefaultGraphics() ) )
            {
            temp.LayoutRect( layout.Rect(),
                    AknLayoutScalable_Avkon::slider_form_pane_g4() );
            iLineRect = temp.Rect();
            
            temp.LayoutRect( layout.Rect(),
                    AknLayoutScalable_Avkon::slider_form_pane_g3() );
            iExt->iLeftCapRect = temp.Rect();
            
            temp.LayoutRect( layout.Rect(),
                    AknLayoutScalable_Avkon::slider_form_pane_g5() );
            iExt->iRightCapRect = temp.Rect();
            
            temp.LayoutRect( layout.Rect(),
                    AknLayoutScalable_Avkon::slider_form_pane_g7() );
            iExt->iTickRect = temp.Rect(); 
                   
            temp.LayoutRect( layout.Rect(),        
                    AknLayoutScalable_Avkon::slider_form_pane_g6() );
            iExt->iThumbRect = temp.Rect();
            }
        else
            {
            temp.LayoutRect( layout.Rect(),
                             AknLayoutScalable_Avkon::slider_form_pane_g1() );
            AknIconUtils::SetSize( iExt->iLineIcon, temp.Rect().Size() );
            iLineRect = temp.Rect();
            
            temp.LayoutRect( layout.Rect(),
                             AknLayoutScalable_Avkon::slider_form_pane_g2() );
            iExt->iThumbRect = temp.Rect();  
            }

        if ( iValueLabel )
            {
            // Label must not overlap control but width is used to set view
            // mode text
            TSize tempSize = iValueLabel->Size();
            iValueLabel->SetSize( TSize( tempSize.iWidth, 0 ) );
            }
        }
    else
        {
        AknLayoutUtils::LayoutLabel( iValueLabel, rect,
                AKN_LAYOUT_TEXT_Form_slider_field_texts_Line_2 );
        }
    }


// ----------------------------------------------------------------------------
// CAknSlider::FormSliderLayout3
// Pure layout function. Value label is not shown in the same place in Edit
// mode.
// ----------------------------------------------------------------------------
//
void CAknSlider::FormSliderLayout3()
    {
    TRect rect = Rect();
    
    if ( iEditable )
        {
        AknLayoutUtils::LayoutLabel( iValueLabel, rect,
                AKN_LAYOUT_TEXT_Form_slider_field_texts_Line_2 );
        AknLayoutUtils::LayoutLabel( iMinLabel, rect,
                AKN_LAYOUT_TEXT_Form_slider_field_texts_Line_3( 0, 1 ) );
        AknLayoutUtils::LayoutLabel( iMaxLabel, rect,
                AKN_LAYOUT_TEXT_Form_slider_field_texts_Line_3( 2, 3 ) );

        TAknLayoutRect temp, layout;
        temp.LayoutRect( rect,
                AknLayoutScalable_Avkon::slider_cont_pane( 0 ) );

        // slider layout with value, min and max labels
        layout.LayoutRect( temp.Rect(),
                AknLayoutScalable_Avkon::slider_form_pane( 0 ) );
        iMarkerArea = layout.Rect();
        //Load new slider layout if exist
        if( !(iExt->UsesDefaultGraphics()) )
            {
            temp.LayoutRect( layout.Rect(),
                    AknLayoutScalable_Avkon::slider_form_pane_g4() );
            iLineRect = temp.Rect();
            
            temp.LayoutRect( layout.Rect(),
                    AknLayoutScalable_Avkon::slider_form_pane_g3() );
            iExt->iLeftCapRect = temp.Rect();
            
            temp.LayoutRect( layout.Rect(),
                    AknLayoutScalable_Avkon::slider_form_pane_g5() );
            iExt->iRightCapRect = temp.Rect();
            
            temp.LayoutRect( layout.Rect(),
                    AknLayoutScalable_Avkon::slider_form_pane_g7() );
            iExt->iTickRect = temp.Rect();
                    
            temp.LayoutRect( layout.Rect(),        
                    AknLayoutScalable_Avkon::slider_form_pane_g6() );
            iExt->iThumbRect = temp.Rect();
            }
        else
            {
            temp.LayoutRect( layout.Rect(),
                             AknLayoutScalable_Avkon::slider_form_pane_g1() );
            AknIconUtils::SetSize( iExt->iLineIcon, temp.Rect().Size() );
            iLineRect = temp.Rect(); 
            
            temp.LayoutRect( layout.Rect(),
                             AknLayoutScalable_Avkon::slider_form_pane_g2() );
            iExt->iThumbRect = temp.Rect(); 
            }
        }
    else
        {
        AknLayoutUtils::LayoutLabel( iValueLabel, rect,
                AKN_LAYOUT_TEXT_Form_slider_field_texts_Line_2 );
        }
    }


// ----------------------------------------------------------------------------
// CAknSlider::SettingsItemSliderLayout
// Pure layout function.
// ----------------------------------------------------------------------------
//
void CAknSlider::SettingsItemSliderLayout()
    {
    TRect rect = Rect();
    iEditable = ETrue;
  
    TAknLayoutRect temp, layoutRect;    
    if ( Layout() == EAknSettingsItemSliderLayout) 
    
        {
        AknLayoutUtils::LayoutLabel( iValueLabel, rect,
                AknLayoutScalable_Avkon::setting_slider_pane_t1_copy1( 0 ) );
        AknLayoutUtils::LayoutLabel( iMinLabel, rect,
                AknLayoutScalable_Avkon::setting_slider_pane_t2_copy1( 0 ) );
        AknLayoutUtils::LayoutLabel( iMaxLabel, rect,
                AknLayoutScalable_Avkon::setting_slider_pane_t3_copy1( 0 ) );
        layoutRect.LayoutRect( rect, 
                AknLayoutScalable_Avkon::slider_set_pane_copy1( 0 ) );
        // Indication rect for setting slider pane
        iExt->iTouchDownArea = Rect();
        
        iExt->iTouchActiveArea = TouchActiveArea();
        }

    if ( Layout() == EAknSettingsItemSliderLayoutWithGraphics  )
        {
        AknLayoutUtils::LayoutLabel( iMinLabel, rect,
                AknLayoutScalable_Avkon::setting_slider_graphic_pane_t1_copy1( 0 ) );
        AknLayoutUtils::LayoutLabel( iMaxLabel, rect,
                AknLayoutScalable_Avkon::setting_slider_graphic_pane_t2_copy1( 0 ) );
        AknLayoutUtils::LayoutImage( iImage, rect,
                AknLayoutScalable_Avkon::setting_slider_graphic_pane_g1_copy1( 0 ) );
        AknIconUtils::SetSize( const_cast<CFbsBitmap*>( iImage->Bitmap() ),
                               iImage->Size(), EAspectRatioNotPreserved );
        layoutRect.LayoutRect( rect, 
                AknLayoutScalable_Avkon::slider_set_pane_cp_copy1( 0 ) );
        // Indication rect for setting slider pane
        iExt->iTouchDownArea = Rect();

        iExt->iTouchActiveArea = TouchActiveArea();
        }

    iMarkerArea = layoutRect.Rect();

    //new horizonal slider
    if( !(iExt->UsesDefaultGraphics()))
        {
        temp.LayoutRect( iMarkerArea,
                AknLayoutScalable_Avkon::slider_set_pane_g4_copy1(0) );
        iLineRect = temp.Rect();
        temp.LayoutRect( iMarkerArea,
                AknLayoutScalable_Avkon::slider_set_pane_g3_copy1(0) );
        iExt->iLeftCapRect = temp.Rect();
        temp.LayoutRect( iMarkerArea,
                AknLayoutScalable_Avkon::slider_set_pane_g5_copy1(0) );
        iExt->iRightCapRect = temp.Rect();
        temp.LayoutRect( iMarkerArea,
                AknLayoutScalable_Avkon::slider_set_pane_g7_copy1(0) );
        iExt->iTickRect = temp.Rect();
        temp.LayoutRect( iMarkerArea,        
                AknLayoutScalable_Avkon::slider_set_pane_g6_copy1(0) );
        iExt->iThumbRect = temp.Rect();
        }
     else //default slider 
        {
        temp.LayoutRect( iMarkerArea,
                AknLayoutScalable_Avkon::slider_set_pane_g1_copy1() );
        AknIconUtils::SetSize( iExt->iLineIcon, temp.Rect().Size() );
        iLineRect = temp.Rect(); 
        temp.LayoutRect( iMarkerArea,
                AknLayoutScalable_Avkon::slider_set_pane_g2_copy1() );
        iExt->iThumbRect = temp.Rect();
        }
    }


// ----------------------------------------------------------------------------
// CAknSlider::VerticalSliderLayout
// Pure layout function.
// ----------------------------------------------------------------------------
//
void CAknSlider::VerticalSliderLayout()
    {
    TRect rect = Rect();
    iEditable = ETrue;
    
    TAknLayoutRect temp, layoutRect;    
    if( !(iExt->UsesDefaultGraphics()))
        {
        iMarkerArea = rect;
        temp.LayoutRect( iMarkerArea,
        AknLayoutScalable_Avkon::small_volume_slider_vertical_pane_g2() );
        iLineRect = temp.Rect();
        
        temp.LayoutRect( iMarkerArea,
               AknLayoutScalable_Avkon::small_volume_slider_vertical_pane_g3() );
        iExt->iThumbRect = temp.Rect();
        }
    else
        {
        AknLayoutUtils::LayoutLabel( iValueLabel, rect,
                AknLayoutScalable_Avkon::setting_slider_pane_t1(1) );
        AknLayoutUtils::LayoutLabel( iMinLabel, rect,
                AknLayoutScalable_Avkon::setting_slider_pane_t2(1) );
        AknLayoutUtils::LayoutLabel( iMaxLabel, rect,
                AknLayoutScalable_Avkon::setting_slider_pane_t3(1) );

        iMarkerArea = rect;
        //new vertical slider    

        temp.LayoutRect( iMarkerArea,
                AknLayoutScalable_Avkon::slider_pane_g3(0) );
        iLineRect = temp.Rect();
        
        temp.LayoutRect( iMarkerArea,
                AknLayoutScalable_Avkon::slider_pane_g1(0) );
        iExt->iLeftCapRect = temp.Rect();
        
        temp.LayoutRect( iMarkerArea,
                AknLayoutScalable_Avkon::slider_pane_g2(0) );
        iExt->iRightCapRect = temp.Rect();
        
        temp.LayoutRect( iMarkerArea,
                AknLayoutScalable_Avkon::slider_pane_g3(0) );
        iExt->iTickRect = temp.Rect(); 
               
        temp.LayoutRect( iMarkerArea,        
                AknLayoutScalable_Avkon::slider_pane_g4(0) );
        iExt->iThumbRect = temp.Rect();        
        }
    }    
// ----------------------------------------------------------------------------
// CAknSlider::HorizontalSliderLayout
// Pure layout function.
// ----------------------------------------------------------------------------
//    
void CAknSlider::HorizontalSliderLayout()  
    {
    TRect rect = Rect();
    iEditable = ETrue;
    
    TAknLayoutRect temp, layoutRect;
    if( !( iExt->UsesDefaultGraphics() ) )
        {
        iMarkerArea = rect;
        temp.LayoutRect( iMarkerArea,
        AknLayoutScalable_Apps::vtel_slider_pane_g2(0) );
        AknIconUtils::SetSize( iExt->iLineIcon, rect.Size() );
        iLineRect = Rect();
        
        /*temp.LayoutRect( iMarkerArea,
                AknLayoutScalable_Apps::vtel_slider_pane_g4(0) );
        iExt->iLeftCapRect = temp.Rect();
        
        temp.LayoutRect( iMarkerArea,
                AknLayoutScalable_Apps::vtel_slider_pane_g3(0) );
        iExt->iRightCapRect = temp.Rect();*/
        
        temp.LayoutRect( rect,
               AknLayoutScalable_Apps::vtel_slider_pane_g5(0) );
        iExt->iThumbRect = temp.Rect();
        }
    else
        {
        AknLayoutUtils::LayoutLabel( iValueLabel, rect,
                AknLayoutScalable_Avkon::setting_slider_pane_t1(0) );
        AknLayoutUtils::LayoutLabel( iMinLabel, rect,
                AknLayoutScalable_Avkon::setting_slider_pane_t2(0) );
        AknLayoutUtils::LayoutLabel( iMaxLabel, rect,
                AknLayoutScalable_Avkon::setting_slider_pane_t3(0) );
        layoutRect.LayoutRect( rect, 
                AknLayoutScalable_Avkon::slider_set_pane(0) );

        iMarkerArea = layoutRect.Rect();
        //new vertical slider    

        temp.LayoutRect( iMarkerArea,
                AknLayoutScalable_Avkon::slider_set_pane_g4(0) );
        iLineRect = temp.Rect();
        
        temp.LayoutRect( iMarkerArea,
                AknLayoutScalable_Avkon::slider_set_pane_g3(0) );
        iExt->iLeftCapRect = temp.Rect();
        
        temp.LayoutRect( iMarkerArea,
                AknLayoutScalable_Avkon::slider_set_pane_g5(0) );
        iExt->iRightCapRect = temp.Rect();
        
        temp.LayoutRect( iMarkerArea,
                AknLayoutScalable_Avkon::slider_set_pane_g7(0) );
        iExt->iTickRect = temp.Rect(); 
               
        temp.LayoutRect( iMarkerArea,        
                AknLayoutScalable_Avkon::slider_set_pane_g6(0) );
        iExt->iThumbRect = temp.Rect();        
        }   
    }
// ----------------------------------------------------------------------------
// CAknSlider::MIDPFormSliderLayout
// Pure layout function. Value, min and max labels are shown.
// ----------------------------------------------------------------------------
//
void CAknSlider::MIDPFormSliderLayout()
    {
    TRect rect = Rect();
    if ( iEditable )
        {
        AknLayoutUtils::LayoutLabel( iValueLabel, rect,
                AknLayoutScalable_Avkon::form2_midp_gauge_slider_pane_t1() );

        TAknLayoutRect layout, temp;
        layout.LayoutRect( rect,
                AknLayoutScalable_Avkon::form2_midp_gauge_slider_cont_pane(0) );
        AknLayoutUtils::LayoutLabel( iMinLabel, layout.Rect(),
                AknLayoutScalable_Avkon::form2_midp_gauge_slider_pane_t2_cp01(0) );
        AknLayoutUtils::LayoutLabel( iMaxLabel, layout.Rect(),
                AknLayoutScalable_Avkon::form2_midp_gauge_slider_pane_t3_cp01(1) );  
        temp.LayoutRect( layout.Rect(),
                AknLayoutScalable_Avkon::form2_midp_slider_pane_cp01(0));  
        iMarkerArea = temp.Rect();   
        temp.LayoutRect( iMarkerArea,
                AknLayoutScalable_Avkon::form2_midp_slider_pane_g2(0) );   
        AknIconUtils::SetSize( iExt->iLineIcon, temp.Rect().Size() );
        iLineRect = temp.Rect();
        
        temp.LayoutRect( iMarkerArea,
                AknLayoutScalable_Avkon::form2_midp_slider_pane_g1(0) );
        iExt->iLeftCapRect = temp.Rect();
        
        temp.LayoutRect( iMarkerArea,
                AknLayoutScalable_Avkon::form2_midp_slider_pane_g3(0) );
        iExt->iRightCapRect = temp.Rect();
        
        temp.LayoutRect( iMarkerArea,
                AknLayoutScalable_Avkon::slider_form_pane_g7(0) );
        iExt->iTickRect = temp.Rect(); 
        
        temp.LayoutRect( iMarkerArea,
                         AknLayoutScalable_Avkon::slider_form_pane_g2() );
        iExt->iThumbRect = temp.Rect(); 
        }
    else
        {
        AknLayoutUtils::LayoutLabel( iValueLabel, rect,
                AKN_LAYOUT_TEXT_Form_slider_field_texts_Line_2 );
        }
    }

// ----------------------------------------------------------------------------
// CAknSlider::Draw
// Implementation of automatically called control drawing function from
// CCoeControl.
// ----------------------------------------------------------------------------
//
void CAknSlider::Draw( const TRect& /*aRect*/ ) const
    {
    if ( iExt->IsFlagSet( CAknSliderExtension::EFlagHorizontal ) )
        {
        DrawHorizontal( ETrue );
        }
    else // must be vertical
        {
        DrawVertical( ETrue );
        }
    }


// ----------------------------------------------------------------------------
// CAknSlider::DrawHorizontalTickMarks
//
// Draws horizontal tick marks. The slider grows rightwards and tick marks are
// placed above or below the line. If tick mark interval is zero the repeat
// step size is used as the interval.
//
// Slider range is not a pixel space, conversion must be done from
// slider range to actual pixel range. Using one pixel width for the
// tick interval in pixel space is not possible, as rounding errors
// would cumulate. Each tick pixel coordinate must be separately
// determined.
//
// Slider range [r1, r2] e Z, pixel range [p1, p2] e Z. Mapping from
// slider range position r to pixel range position p:
//
//            | (r - r1)(p2 - p1) |
//   p = p1 + | ----------------- |
//            |_     r2 - r1     _|
//
// Flooring indicates truncation caused by integer division.
// ----------------------------------------------------------------------------
//
void CAknSlider::DrawHorizontalTickMarks( CWindowGc& aGc ) const
    {
    TAknSliderGfx gfx;
    FetchGfx( gfx, EElemTickMark, iExt->iTickRect.Size() );

    if ( !gfx.iRgb )
        {
        aGc.SetBrushStyle( CWindowGc::ESolidBrush );
        aGc.SetBrushColor( AKN_LAF_COLOR( KAknSliderDefaultDrawColor ) );
        }

    const TInt mw = MarkerSize().iWidth; // Marker width
    const TInt r1 = SliderData()->iMinimumValue; // Slider range start
    const TInt r2 = SliderData()->iMaximumValue; // Slider range end
    // Note that r2 - r1 > 0 as slider quarantees that
    // SliderData()->iMinimumValue < SliderData()->iMaximumValue.

    const TInt p1 = iMarkerArea.iTl.iX + mw / 2; // Pixel range start
    const TInt p2 = p1 + iMarkerArea.Width() - mw; // Pixel range end

    // Interval between tick marks, if zero then use step spacing.
    // StepSize is always >= 1, therefore s cannot be zero which would
    // lead to infinite loop below.
    const TInt s = ( 0 == iExt->iTickInterval ) ? StepSize():
                                                  iExt->iTickInterval;
                                                  
    const TInt tickWidth = iExt->iTickRect.Size().iWidth;
    
    // If tick width is even, handle as if it was uneven. The extra column of
    // pixels is aligned to right side of the tick mark middle position.
    const TInt off = ( tickWidth / 2 ) -
                     ( ( tickWidth % 2 == 0 ) ? 1: 0 );
                     

    TRect rect = iExt->iTickRect;

    for ( int r = r1; r <= r2; r += s )
        {
        // Current pos in the range -> current pos on screen, r2 - r1 > 0
        // always (see comment above).
        rect.iTl.iX = p1 + ( ( r - r1 ) * ( p2 - p1 ) ) / ( r2 - r1 ) - off;
        rect.iBr.iX = rect.iTl.iX + tickWidth;

        if ( gfx.iRgb && gfx.iMask )
            {
            aGc.BitBltMasked( rect.iTl, gfx.iRgb, rect.Size(), gfx.iMask, EFalse );
            }
        else if ( gfx.iRgb )
            {
            aGc.BitBlt( rect.iTl, gfx.iRgb, rect.Size() );
            }
        else
            {
            aGc.DrawRect( rect );
            }
        }
    aGc.SetBrushStyle( CGraphicsContext::ENullBrush );
    }


// ----------------------------------------------------------------------------
// CAknSlider::DrawVerticalTickMarks
//
// Draws vertical tick marks. The slider grows upwards and tick marks are
// placed to the left or right of the line. If tick mark interval is zero the
// repeat step size is used as the interval. Implementation is similar to
// DrawHorizontalTickMarks, the major difference is that in vertical mode
// slider range and pixel range grow to different directions.
// ----------------------------------------------------------------------------
//
void CAknSlider::DrawVerticalTickMarks( CWindowGc& aGc ) const
    {
    TAknSliderGfx gfx;
    FetchGfx( gfx, EElemTickMark, iExt->iTickRect.Size() );

    if ( !gfx.iRgb )
        {
        aGc.SetBrushStyle( CWindowGc::ESolidBrush );
        aGc.SetBrushColor( AKN_LAF_COLOR( KAknSliderDefaultDrawColor ) );
        }

    const TInt mh = MarkerSize().iHeight; // Marker height
    const TInt r1 = SliderData()->iMinimumValue; // Slider range start
    const TInt r2 = SliderData()->iMaximumValue; // Slider range end
    // Note that r2 - r1 > 0 as slider quarantees that
    // SliderData()->iMinimumValue < SliderData()->iMaximumValue.

    const TInt p2 = iMarkerArea.iBr.iY - mh / 2; // Pixel range end
    const TInt p1 = p2 - iMarkerArea.Height() + mh; // Pixel range start

    // Interval between tick marks, if zero then use step spacing.
    // StepSize is always >= 1, therefore s cannot be zero which would
    // lead to infinite loop below.
    const TInt s = ( 0 == iExt->iTickInterval ) ? StepSize():
                                                  iExt->iTickInterval;

    const TInt tickHeight = iExt->iTickRect.Size().iHeight;
    
    // If tick width is even, handle as if it was uneven. The extra column of
    // pixels is aligned above the tick mark middle position.
    const TInt off = ( tickHeight / 2 ) -
                     ( ( tickHeight % 2 == 0 ) ? 1: 0 );

    TRect rect = iExt->iTickRect;
    for ( int r = r1; r <= r2; r += s )
        {
        // Current pos in the range -> current pos on screen, r2 - r1 > 0,
        // checked above
        rect.iBr.iY = p2 - ( ( r - r1 ) * ( p2 - p1 ) ) / ( r2 - r1 ) + off;
        rect.iTl.iY = rect.iBr.iY - tickHeight;

        if ( gfx.iRgb && gfx.iMask )
            {
            aGc.BitBltMasked( rect.iTl, gfx.iRgb, rect.Size(), gfx.iMask, EFalse );
            }
        else if ( gfx.iRgb )
            {
            aGc.BitBlt( rect.iTl, gfx.iRgb, rect.Size() );
            }
        else
            {
            aGc.DrawRect( rect );
            }
        }
    }


// ----------------------------------------------------------------------------
// CAknSlider::CreateDecoratorImageFromResourceL
// ----------------------------------------------------------------------------
//
void CAknSlider::CreateDecoratorImageFromResourceL( TInt aImageResourceId )
    {
    iImage = new ( ELeave ) CEikImage();
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, aImageResourceId );
    iImage->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy(); // reader
    }


// ----------------------------------------------------------------------------
// CAknSlider::SetDecimalPlaces
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknSlider::SetDecimalPlaces( TInt aDecimalPlaces )
    {
    SliderData()->SetDecimalPlaces( aDecimalPlaces );
    }


// ----------------------------------------------------------------------------
// CAknSlider::DecimalPlaces
// ----------------------------------------------------------------------------
//
EXPORT_C TInt CAknSlider::DecimalPlaces() const
    {
    return SliderData()->DecimalPlaces();
    }


// ----------------------------------------------------------------------------
// CAknSlider::SetGraphics
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknSlider::SetGraphics( TInt aElement, CFbsBitmap* aBitmap,
                                       CFbsBitmap* aMask )
    {
    if ( aElement < 0 || aElement > EElemMarkerSelected )//|| !aBitmap )
        {
        Panic( EAknPanicInvalidValue );
        }

    iExt->SetGraphics( aElement, aBitmap, aMask );
    }

    
// ----------------------------------------------------------------------------
// CAknSlider::UseDefaultGraphics
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknSlider::UseDefaultGraphics( TInt aElement )
    {
    if ( aElement < 0 || aElement > EElemMarkerSelected )
        {
        Panic( EAknPanicInvalidValue );
        }

    iExt->UseDefaultGraphics( aElement );
    }


// ----------------------------------------------------------------------------
// CAknSlider::UsesDefaultGraphics
// ----------------------------------------------------------------------------
//
EXPORT_C TBool CAknSlider::UsesDefaultGraphics( TInt aElement ) const
    {
    if ( aElement < 0 || aElement > EElemMarkerSelected )
        {
        Panic( EAknPanicInvalidValue );
        }

    return iExt->UsesDefaultGraphics( aElement );
    }


// ----------------------------------------------------------------------------
// CAknSlider::SetPositionIndicators
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknSlider::SetPositionIndicators( TUint32 aFlags )
    {
    iExt->ClearFlag( CAknSliderExtension::EFlagFillEnabled );
    iExt->ClearFlag( CAknSliderExtension::EFlagMarkerEnabled );

    if ( EPosFilling & aFlags )
        {
        iExt->SetFlag( CAknSliderExtension::EFlagFillEnabled );
        }
    else
        {
        // If no position indicator is set, always default to visible
        // marker
        iExt->SetFlag( CAknSliderExtension::EFlagMarkerEnabled );
        }

    if ( EPosMarker & aFlags )
        {
        iExt->SetFlag( CAknSliderExtension::EFlagMarkerEnabled );
        }
    }


// ----------------------------------------------------------------------------
// CAknSlider::PositionIndicators
// ----------------------------------------------------------------------------
//
EXPORT_C TUint32 CAknSlider::PositionIndicators() const
    {
    TUint32 flags = 0;

    if ( iExt->IsFlagSet( CAknSliderExtension::EFlagMarkerEnabled ) )
        {
        flags |= EPosMarker;
        }

    if ( iExt->IsFlagSet( CAknSliderExtension::EFlagFillEnabled ) )
        {
        flags |= EPosFilling;
        }

    return flags;
    }


// ----------------------------------------------------------------------------
// CAknSlider::Orientation
// ----------------------------------------------------------------------------
//
EXPORT_C TAknOrientation CAknSlider::Orientation() const
    {
    if ( iExt->IsFlagSet( CAknSliderExtension::EFlagHorizontal ) )
        {
        return EAknOrientationHorizontal;
        }
    return EAknOrientationVertical;
    }


// ----------------------------------------------------------------------------
// CAknSlider::SetTicksEnabled
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknSlider::SetTicksEnabled( TBool aStatus )
    {
    if ( aStatus )
        {
        iExt->SetFlag( CAknSliderExtension::EFlagTickMarksEnabled );
        }
    else
        {
        iExt->ClearFlag( CAknSliderExtension::EFlagTickMarksEnabled );
        }
    }


// ----------------------------------------------------------------------------
// CAknSlider::TicksEnabled
// ----------------------------------------------------------------------------
//
EXPORT_C TBool CAknSlider::TicksEnabled() const
    {
    return iExt->IsFlagSet( CAknSliderExtension::EFlagTickMarksEnabled );
    }


// ----------------------------------------------------------------------------
// CAknSlider::SetTickInterval
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknSlider::SetTickInterval( TUint aInterval )
    {
    iExt->iTickInterval = aInterval;
    }


// ----------------------------------------------------------------------------
// CAknSlider::TickInterval
// ----------------------------------------------------------------------------
//
EXPORT_C TUint CAknSlider::TickInterval() const
    {
    return iExt->iTickInterval;
    }


// ----------------------------------------------------------------------------
// CAknSlider::NumberOfLines
// ----------------------------------------------------------------------------
//
EXPORT_C TInt CAknSlider::NumberOfLines() const
    {
    TInt noOfLines = 1;

    if ( iEditable )
        {
        switch ( Layout() )
            {
            case EAknFormSliderLayout1: // drop through
            case EAknFormSliderLayout2:
                noOfLines = 2;
                break;
            case EAknFormSliderLayout3:
                noOfLines = 3;
                break;
            default:
                break;
            }
        }

    return noOfLines;
    }


// ----------------------------------------------------------------------------
// CAknSlider::CreateValueTextInHBufCL
//
// Returns the text that would appear at the top of the slider setting page if
// it were opened Ownership of the text buffer is transferred to the caller.
// ----------------------------------------------------------------------------
//
EXPORT_C HBufC* CAknSlider::CreateValueTextInHBufCL(
        TInt aValue, TInt aResourceId )
    {
    CAknSliderData* sliderResourceData = CAknSliderData::NewLC( aResourceId );

    __ASSERT_DEBUG( aValue >= sliderResourceData->iMinimumValue &&
                    aValue <= sliderResourceData->iMaximumValue,
                    Panic( EAknPanicOutOfRange ) );

    TBuf<KValueLabelTextMaxLength> textBuffer;
    CAknSlider::DoSetValueTextL( textBuffer, aValue, *sliderResourceData );

    CleanupStack::PopAndDestroy(); // sliderResourceData
    HBufC* valueTextBufC = textBuffer.AllocL();
    return valueTextBufC;
    }

// ----------------------------------------------------------------------------
// CAknSlider::StepSize
// ----------------------------------------------------------------------------
//
TInt CAknSlider::StepSize() const
    {
    return iData->iStepSize;
    }


// ----------------------------------------------------------------------------
// CAknSlider::Layout
// ----------------------------------------------------------------------------
//
TInt CAknSlider::Layout() const
    {
    return iData->iLayout;
    }


// ----------------------------------------------------------------------------
// CAknSlider::MaximumValue
// ----------------------------------------------------------------------------
//
TInt CAknSlider::MaximumValue() const
    {
    return iData->iMaximumValue;
    }


// ----------------------------------------------------------------------------
// CAknSlider::MinimumValue
// ----------------------------------------------------------------------------
//
TInt CAknSlider::MinimumValue() const
    {
    return iData->iMinimumValue;
    }


// ----------------------------------------------------------------------------
// CAknSlider::Range
// ----------------------------------------------------------------------------
//
TInt CAknSlider::Range() const
    {
    return iData->Range();
    }


// ----------------------------------------------------------------------------
// CAknSlider::SliderData
// ----------------------------------------------------------------------------
//
CAknSliderData* CAknSlider::SliderData() const
    {
    // This method is used to trap all the accesses to the internal data when
    // the 2nd stage construction has not taken place
    __ASSERT_DEBUG( iData, Panic( EAknPanicObjectNotFullyConstructed ) );
    return iData;
    }


// ----------------------------------------------------------------------------
// CAknSlider::HandlePointerEventL
//
// Handles slider's pointer events. This function calculates thumb position
// when button down happens. Then it compares position to thumb position and if
// pointerevent was for the thumb it will set dragging on. Otherwise, the thumb
// will be moved to down position.
//
// If value have to be changed with this pointerevent, the new value have to be
// calculated. The calculation is based for drawing, so we have to find "what
// value" would be drawn to clicked position and thus deside what value was
// selected from slider.
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknSlider::HandlePointerEventL( const TPointerEvent& aEvent )
    {
    if ( !AknLayoutUtils::PenEnabled() )
        {
        return;
        }

    if ( IsDimmed() )
        {
        iExt->ClearFlag( CAknSliderExtension::EFlagPointerDown );
        iExt->ClearFlag( CAknSliderExtension::EFlagDraggingThumb );
        return;
        }
    
    TBool thumbMoved = EFalse;
    TBool valueChanged = EFalse;
    TBool upFromDrag = EFalse;
    TRect mrect;
    GetMarkerRect( mrect );    
    TInt reportDragEvent(0);// if this value is 0, it means no need to report
    TBool hor = iExt->IsFlagSet( CAknSliderExtension::EFlagHorizontal );
    
    //Setting pane slider use extended touch area to hand pointer event
    TRect touchDownArea;
    TRect touchActiveArea;
    if( Layout() == EAknSettingsItemSliderLayout ||
        Layout() == EAknSettingsItemSliderLayoutWithGraphics
        )
        {
        touchDownArea = iExt->iTouchDownArea;
        touchActiveArea = iExt->iTouchActiveArea;
        }
    else
        {
        touchDownArea = iMarkerArea;
        touchActiveArea = iMarkerArea;
        }
        
    if( iEditable )
        {
         switch ( aEvent.iType )
            {
            case TPointerEvent::EButton1Down:
                {
                if ( touchDownArea.Contains( aEvent.iPosition ) )
                    {
                    TInt stepCount = SliderData()->Range() / SliderData()->iStepSize;
                    if ( stepCount <= KStepThreshold )
                        {
                        MTouchFeedback* feedback = MTouchFeedback::Instance();
                        if ( feedback )
                            {
                            feedback->InstantFeedback( this, ETouchFeedbackBasicSlider, aEvent );
                            }
                        }
                       // repeat until thumb reaches the stylus down position    
                    iExt->iPenInputPos = aEvent.iPosition;

                    // Click was inside and down slider marker area
                    iExt->SetFlag( CAknSliderExtension::EFlagPointerDown );
                    // Start draggint even if the click was not inside thumb rect
                    if ( mrect.Contains( aEvent.iPosition ) )
                        {
                        MTouchFeedback* feedback = MTouchFeedback::Instance();
                        if ( feedback )
                            {
                            feedback->InstantFeedback( this, ETouchFeedbackBasicSlider, aEvent );
                            }
                        iExt->SetFlag( CAknSliderExtension::EFlagDraggingThumb );
                        reportDragEvent = EDragMarkerStart;
                        }                    
                    // Marker icon changes - draw
                    if ( !iExt->iNoDraw )
                        {
                        DrawDeferred();  
                        }
                    valueChanged = ETrue;
                    }
                }
                break;
            case TPointerEvent::EButtonRepeat:
                {
                if ( touchActiveArea.Contains( aEvent.iPosition ) )
                    {
                    // repeat until thumb reaches the stylus down position    
                    iExt->iPenInputPos = aEvent.iPosition;

                    // Click was inside and down slider marker area
                    iExt->SetFlag( CAknSliderExtension::EFlagPointerDown );
                    // Start draggint even if the click was not inside thumb rect
                    if ( mrect.Contains( aEvent.iPosition ) )
                        {
                        iExt->SetFlag( CAknSliderExtension::EFlagDraggingThumb );
                        reportDragEvent = EDragMarkerStart;
                        }                    
                    // Marker icon changes - draw
                    if ( !iExt->iNoDraw )
                        {
                        DrawDeferred();    
                        }
                    valueChanged = ETrue;
                    }
                    if ( mrect.Contains( aEvent.iPosition ) )
                        {
                        StopFeedback();
                        }
                }
                break;
            // Drag can out of touchDownArea to support finger touch out of range,
            // when the pointer fall down the thumb,then use touchDragArea  
            case TPointerEvent::EDrag:
                {
                if ( ( iExt->IsFlagSet( CAknSliderExtension::EFlagDraggingThumb ) ||
                       touchActiveArea.Contains( aEvent.iPosition ) ) &&
                     iExt->IsFlagSet( CAknSliderExtension::EFlagPointerDown ) )
                    {
                    if ( hor && aEvent.iPosition.iX != iExt->iPenInputPos.iX )
                        {
                        thumbMoved = ETrue;
                        }
                    if ( !hor && aEvent.iPosition.iY != iExt->iPenInputPos.iY )
                        {
                        thumbMoved = ETrue;
                        }
                    iExt->iPenInputPos = aEvent.iPosition;
                    valueChanged = ETrue;
                    }
                if ( !iExt->IsFlagSet( CAknSliderExtension::EFlagDraggingThumb ) &&
                     !touchActiveArea.Contains( aEvent.iPosition ))
                    {
                        StopFeedback();
                    }
                }
                break; 
                
            case TPointerEvent::EButton1Up:
                {
                if ( iExt->IsFlagSet( CAknSliderExtension::EFlagDraggingThumb ) &&
                     iExt->IsFlagSet( CAknSliderExtension::EFlagPointerDown ) )
                    {
                    iExt->iPenInputPos = aEvent.iPosition;
                    valueChanged = ETrue;
                    upFromDrag = ETrue;
                    reportDragEvent = EDragMarkerEnd;
                    }
                iExt->ClearFlag( CAknSliderExtension::EFlagPointerDown );
                iExt->ClearFlag( CAknSliderExtension::EFlagDraggingThumb );
                if ( mrect.Contains( aEvent.iPosition ) )
                    {
                    MTouchFeedback* feedback = MTouchFeedback::Instance();
                    if ( feedback )
                        {
                        feedback->InstantFeedback( this,
                                                   ETouchFeedbackBasicSlider,
                                                   ETouchFeedbackVibra,
                                                   aEvent );
                        }
                    }
                StopFeedback();

                // Marker icon changes - draw
                if ( !iExt->iNoDraw )
                    {
                    DrawDeferred();    
                    }
                }
                break;
                
            default:
                break;
            }       
        }

                        
    TBool valueStepChange = iExt->IsFlagSet( CAknSliderExtension::EFlagValueStepChange );
    
    // if pointerevent causes value changing, we have to calculate the
    // clicked value.
    if ( valueChanged )
        {
        TInt betweenSteps;
        TInt value = Value();
        TBool isDragThumb = EFalse;

        if( (iExt->IsFlagSet( CAknSliderExtension::EFlagDraggingThumb ) &&
            iExt->IsFlagSet( CAknSliderExtension::EFlagPointerDown )) || 
            !valueStepChange || upFromDrag )
            {
            //not value step or drag happened
            isDragThumb = ETrue;
            value = CalcAlignedValue( iExt->iPenInputPos );
            }
        else if( !mrect.Contains( aEvent.iPosition ) )
            {// value step change begin
            TInt step = StepSize();
            TInt halfStepRange(0);
            TBool repeat = ( ( aEvent.iType == TPointerEvent::EButton1Down ) ||
            ( aEvent.iType == TPointerEvent::EButtonRepeat ) ) ? ETrue : EFalse;

            if(!hor)
                {
                halfStepRange = (iMarkerArea.Height() - mrect.Height())/( 2 * Range() );
                if( aEvent.iPosition.iY < mrect.iTl.iY + mrect.Height()/2 - halfStepRange )
                    {
                    TranslateValueL( step, repeat );
                    value = iValue;
                    }
                else if( aEvent.iPosition.iY > mrect.iTl.iY + mrect.Height()/2 + halfStepRange )
                    {
                    TranslateValueL( -step, repeat );
                    value = iValue;
                    }
                else
                    {
                    value = iValue;
                    }
                }
             else
                {
                halfStepRange = (iMarkerArea.Width() - mrect.Width())/( 2 * Range() );
                if( aEvent.iPosition.iX < mrect.iTl.iX + mrect.Width()/2 - halfStepRange )
                    {
                    TranslateValueL( -step, repeat );
                    value = iValue;
                    }
                else if( aEvent.iPosition.iX > mrect.iTl.iX + mrect.Width()/2 + halfStepRange )
                    {
                    TranslateValueL( step, repeat );
                    value = iValue;
                    }
                else
                    {
                    value = iValue;
                    }     
                }

                Window().RequestPointerRepeatEvent( KScrollRepeatTimeout, touchActiveArea );
             }// value step change over
        
        // calculate how many pixels was clicked between steps
        betweenSteps = value % StepSize();

        if ( betweenSteps != 0 )
            {
            value = value - betweenSteps;

            // if click was nearer or middle of values, then move it to
            // next possible value
            if ( betweenSteps > ( StepSize() / 2 ) )
                {
                value = value + StepSize();
                }
            }

        // Move to Max/Min values if value is not withing range
        if ( value > MaximumValue() )
            {
            value = MaximumValue();
            }
        else if ( value < MinimumValue() )
            {
            value = MinimumValue();
            }
        if( value == MinimumValue() )
            {
            //The value is minimum value, but the pointer fell on the position which is
            //less than minimum + 1 position.
            if( hor && 
                aEvent.iPosition.iX < iMarkerArea.iTl.iX + iExt->iThumbRect.Width() / 2 + 
                             ( iMarkerArea.iTl.iX - iExt->iThumbRect.Width() ) / Range() )
                {
                iExt->iPenInputPos = 
                      TPoint( iMarkerArea.iTl.iX + iExt->iThumbRect.Width() / 2, 
                              iMarkerArea.iTl.iY );                
                thumbMoved = EFalse;
                }
            
            if( !hor && 
                aEvent.iPosition.iY > iMarkerArea.iBr.iY - iExt->iThumbRect.Height() / 2 - 
                             ( iMarkerArea.iTl.iY - iExt->iThumbRect.Height() ) / Range() )
                {
                iExt->iPenInputPos = 
                          TPoint( iMarkerArea.iBr.iX,
                                  iMarkerArea.iTl.iY - iExt->iThumbRect.Height() / 2 );                
                thumbMoved = EFalse;
                }
            }
        if( value == MaximumValue() )
            {
            if( hor )
                {
                iExt->iPenInputPos.iX = iMarkerArea.iTl.iX - iExt->iThumbRect.Width() / 2;
                thumbMoved = EFalse;
                }
            else
                {
                iExt->iPenInputPos.iY = iMarkerArea.iTl.iY + iExt->iThumbRect.Height() / 2;
                thumbMoved = EFalse;
                }
            }
        if ( thumbMoved )
            {
            StartFeedback( &aEvent, KFeedbackTimeout );
            }
        if ( iValue != value )
            {
            SetValueL( value );
            if ( &Window() != NULL )
                {                
                ReportEventL( MCoeControlObserver::EEventStateChanged );
                if ( !iExt->iNoDraw )
                    {
                    DrawDeferred();    
                    }
                }
            }
        else if( isDragThumb ) // fix TSW EAKH-7FAF63
            {
            // smoothly
            DrawDeferred();
            }
        }
        
    // Report drag event if it is needed
    if( iExt->iReportMarkerDragEvent && reportDragEvent )
        {
        ReportEventL( static_cast<MCoeControlObserver::TCoeEvent>(reportDragEvent) );
        }
    }


// ----------------------------------------------------------------------------
// CAknSlider::CalcAlignedValue
// ----------------------------------------------------------------------------
//
TInt CAknSlider::CalcAlignedValue( const TPoint& aPoint ) 
    {
    TBool hor = iExt->IsFlagSet( CAknSliderExtension::EFlagHorizontal );
    TInt bitmapRun = 0;
    TInt returnValue = MinimumValue();
    
    if ( hor )
        {
        bitmapRun = iMarkerArea.Width() - iExt->iThumbRect.Width();
        returnValue = ( ( Range() * ( aPoint.iX - iMarkerArea.iTl.iX -
            iExt->iThumbRect.Width() / 2 ) + bitmapRun / 2 ) / bitmapRun ) + MinimumValue();
        }
    else
        {
        bitmapRun = iMarkerArea.Height() - iExt->iThumbRect.Height();
        returnValue = ( ( Range() * ( iMarkerArea.iBr.iY - aPoint.iY -
            iExt->iThumbRect.Height() / 2 ) + bitmapRun / 2 ) / bitmapRun ) + MinimumValue();
        }
    return returnValue;
    }


// ----------------------------------------------------------------------------
// CAknSlider::ExtensionInterface
// ----------------------------------------------------------------------------
//
EXPORT_C void* CAknSlider::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }


// ----------------------------------------------------------------------------
// CAknSlider::StartTimerL
// ----------------------------------------------------------------------------
//
void CAknSlider::StartTimerL()
    {
    if ( iExt->iTimer->IsActive() )
        {
        return; // do not re-start as we have the feedback ongoing
        }

    iExt->iEffectTimerCount = 0;

    TCallBack callback( IndicationDrawCallbackL, this );
     iExt->iTimer->Start(
            TTimeIntervalMicroSeconds32( KAknSliderFeedbackActionTime ),
            KAknSliderFeedbackActionTime, callback );
    }


// ----------------------------------------------------------------------------
// CAknSlider::IndicationDrawCallbackL
// ----------------------------------------------------------------------------
//
TInt CAknSlider::IndicationDrawCallbackL( TAny* aThis )
    {
    CAknSlider* slider = static_cast<CAknSlider*>( aThis );
    slider->SmallDirectionIndicationL();
    return KErrNone;
    }


// ----------------------------------------------------------------------------
// CAknSlider::SmallDirectionIndicationL
// ----------------------------------------------------------------------------
//
void CAknSlider::SmallDirectionIndicationL()
    {
    Window().Invalidate( iMarkerArea );
    ActivateGc();
    Window().BeginRedraw( iMarkerArea );
    CWindowGc& gc = SystemGc();
    gc.SetBrushStyle( CGraphicsContext::ENullBrush );
    gc.SetBrushColor( AKN_LAF_COLOR( 0 ) );
    gc.SetPenColor( AKN_LAF_COLOR( 0 ) );

    if( !Background() )
        {
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        MAknsControlContext* cc = NULL;        
        if ( AknsUtils::AvkonSkinEnabled() )
            {
            cc = AknsDrawUtils::ControlContext( this );
            }         
        AknsDrawUtils::Background( skin, cc, this, gc, Rect() );
        }
     else
        {
        TRect rect = Window().GetDrawRect();
        Background()->Draw( gc, *this, rect );
        }
    
    TBool drawMarker = EFalse;
    if ( iExt->iEffectTimerCount % 2 == 1 )
        {
        drawMarker = ETrue;
        }

    if ( iExt->IsFlagSet( CAknSliderExtension::EFlagHorizontal ) )
        {
        DrawHorizontal( drawMarker );
        }
    else // Must be vertical
        {
        DrawVertical( drawMarker );
        }

    Window().EndRedraw();
    DeactivateGc();

    iExt->iEffectTimerCount++;

    // Stop timer if done normal-inverted-normal-inverted-normal sequence
    if ( iExt->iEffectTimerCount > 3 )
        {
        iExt->iTimer->Cancel();
        }
    }


// ----------------------------------------------------------------------------
// CAknSlider::TranslateValueL
//
// Moves the current slider value by aDelta. If the value of aDelta is
// negative, the current value is decremented by |aDelta|. If the value of
// aDelta is positive, the current value is incremented by |aDelta|.
// ----------------------------------------------------------------------------
//
void CAknSlider::TranslateValueL( TInt aDelta, TBool aFeedback )
    {
    TInt sliderValue = Value();

    sliderValue += aDelta;
    
    // calculate how many pixels was clicked between steps
    TInt betweenSteps = sliderValue % StepSize();
        
    if ( betweenSteps != 0 )
        {
        sliderValue = sliderValue - betweenSteps;

        // if click was nearer or middle of values, then move it to
        // next possible value
        if ( betweenSteps > ( StepSize() / 2 ) )
            {
            sliderValue = sliderValue + StepSize();
            }
        }
    
    if ( sliderValue > MaximumValue() )
        {
        sliderValue = MaximumValue();
        }
    else if ( sliderValue < MinimumValue() )
        {
        sliderValue = MinimumValue();
        }
    

    TInt oldSliderValue = Value();
    SetValueL( sliderValue );

    ReportEventL( MCoeControlObserver::EEventStateChanged );

    // start the timer if we tried to move the slider but the slider did
    // not move (in either maximum or minimum already).
#ifdef RD_ANIMATION_EFFECTS
    if ( sliderValue == oldSliderValue )
        {
        StartTimerL();
        }
#endif

    if ( sliderValue != oldSliderValue )
        {
        if( aFeedback )
            {
            TInt stepCount = SliderData()->Range() / SliderData()->iStepSize;
            if ( stepCount > KStepThreshold )
                {
                if ( iExt->IsFlagSet( CAknSliderExtension::EFlagPlayingContinuousFb ))
                    {
                    if ( SliderData()->iFeedbackStyle == EAknSliderFbDynamic )
                        {
                        ModifyFeedback();
                        }
                    }
                else
                    {
                    StartFeedback( NULL, KNoFeedbackTimeout );
                    }
                }
            else
                {
                MTouchFeedback* feedback = MTouchFeedback::Instance();
                if ( feedback )
                    {
                    feedback->InstantFeedback( this, ETouchFeedbackBasicSlider );
                    }
                }            
            }

        Window().Invalidate( Rect() );
        }
    }    


// ----------------------------------------------------------------------------
// CAknSlider::GetMarkerRect
//
// Returns the marker rectangle (the knob). Note that this is not equal to
// iMarkerArea.
// ----------------------------------------------------------------------------
//
void CAknSlider::GetMarkerRect( TRect& aRect ) const
    {
    aRect = TRect( MarkerPos(), MarkerSize());
    }


// ----------------------------------------------------------------------------
// CAknSlider::MarkerSize
//
// Returns the marker size (the knob). Note that this is not equal to
// iMarkerArea.Size(). 
// ----------------------------------------------------------------------------
//
TSize CAknSlider::MarkerSize() const
    {
    return iExt->iThumbRect.Size();
    }


// ----------------------------------------------------------------------------
// CAknSlider::MarkerPos
//
// Returns the marker position (knob). Note that this is not equal to
// iMarkerArea.iTl. 
// ----------------------------------------------------------------------------
//
TPoint CAknSlider::MarkerPos() const
    {
    TPoint p;

    if ( iExt->IsFlagSet( CAknSliderExtension::EFlagHorizontal ) )
        {
        TSize markerSize( MarkerSize() );
        TInt pixelRange = iMarkerArea.Width() - markerSize.iWidth;
        TInt pos = ( pixelRange * ( iValue - MinimumValue() ) / Range() );
        
        if ( AknLayoutUtils::PenEnabled() && 
             iMarkerArea.Contains( iExt->iPenInputPos ) &&
             &Window() != NULL )
            {
            if( !iExt->IsFlagSet( CAknSliderExtension::EFlagValueStepChange ) ||
              ( iExt->IsFlagSet( CAknSliderExtension::EFlagDraggingThumb ) &&
                iExt->IsFlagSet( CAknSliderExtension::EFlagPointerDown ) ) )
                {
                p.iX = iExt->iPenInputPos.iX - ( markerSize.iWidth ) / 2;
                }
            else
                {
                p.iX = iMarkerArea.iTl.iX + pos;
                }
            } 
        else
            {
            p.iX = iMarkerArea.iTl.iX + pos;
            }       
        p.iY = iMarkerArea.iTl.iY;
        }
    else
        {
        TSize markerSize( MarkerSize() );
        TInt pixelRange = iMarkerArea.Height() - markerSize.iHeight;
        TInt pos = ( pixelRange * ( iValue - MinimumValue() ) / Range() );
        
        p.iX = iMarkerArea.iTl.iX;
        if ( AknLayoutUtils::PenEnabled() && 
             iMarkerArea.Contains( iExt->iPenInputPos ) &&
             &Window() != NULL )
            {
            if( !iExt->IsFlagSet( CAknSliderExtension::EFlagValueStepChange ) ||
              ( iExt->IsFlagSet( CAknSliderExtension::EFlagDraggingThumb ) &&
                iExt->IsFlagSet( CAknSliderExtension::EFlagPointerDown ) ) )
                {
                p.iY = iExt->iPenInputPos.iY - ( markerSize.iHeight ) / 2;
                }
            else
                {
                p.iY = iMarkerArea.iBr.iY - pos - markerSize.iHeight;
                }
            }
        else
            {
            p.iY = iMarkerArea.iBr.iY - pos - markerSize.iHeight;
            } 
        }
    return p;
    }


// ----------------------------------------------------------------------------
// CondBlit
//
// Helper C-function for conditional blitting, static to make the function
// visible to this compilation unit only.
// ----------------------------------------------------------------------------
//
inline static void CondBlit( CWindowGc& aGc, const TPoint& aPoint,
        const CFbsBitmap* aBitmap, const TSize& aSourceSize,
        const CFbsBitmap* aMask, TBool aInvertMask = ETrue )
    {
    const TPoint origin( 0, 0 );
    
    aGc.SetBrushStyle( CGraphicsContext::ENullBrush );
    aGc.SetPenStyle( CGraphicsContext::ENullPen );
    aGc.SetBrushColor( AKN_LAF_COLOR( 0 ) );
    aGc.SetPenColor( AKN_LAF_COLOR( 0 ) );
    
    if ( aBitmap && aMask )
        {
        aGc.BitBltMasked( aPoint, aBitmap, 
                          TRect( origin, aSourceSize ), 
                          aMask, aInvertMask );
        }
    else if ( aBitmap )
        {
        aGc.BitBlt( aPoint, aBitmap, TRect( origin, aSourceSize) );
        }
    else
        {
        // If no bitmap resource, it doesn't need to render default color any more
        /*aGc.SetBrushStyle( CGraphicsContext::ESolidBrush );
        aGc.SetBrushColor( AKN_LAF_COLOR( KAknSliderDefaultDrawColor ) );
        aGc.SetPenStyle( CGraphicsContext::ESolidPen );
        aGc.SetPenColor( AKN_LAF_COLOR( KAknSliderDefaultDrawColor ) );
        aGc.DrawRect( TRect( aPoint, aSourceSize ) );*/
        }
    }


// ----------------------------------------------------------------------------
// CAknSlider::DrawHorizontal
// ----------------------------------------------------------------------------
//
void CAknSlider::DrawHorizontal( TBool aDrawMarker ) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetBrushStyle( CGraphicsContext::ENullBrush );
    gc.SetBrushColor( AKN_LAF_COLOR( 0 ) );
    gc.SetPenColor( AKN_LAF_COLOR( 0 ) );

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = NULL;

    if ( AknsUtils::AvkonSkinEnabled() )
        {
        cc = AknsDrawUtils::ControlContext( this );
        }

    if ( !FindBackground() )
        {
        AknsDrawUtils::Background( skin, cc, this, gc, Rect() );
        }
    
    // Don't draw slider in form view mode
    if ( !( Layout() == EAknSettingsItemSliderLayout ||
            Layout() == EAknSettingsItemSliderLayoutWithGraphics || 
            Layout() == EAknSliderLayoutVertical ||
            Layout() == EAknSliderLayoutHorizontal ||
            iEditable ) )
        {
        return;
        }

    DrawHorizontalLine( gc ); // Draw line and end caps

    // Draw the tick marks, if any
    if ( iExt->IsFlagSet( CAknSliderExtension::EFlagTickMarksEnabled ) )
        {
        DrawHorizontalTickMarks( gc );
        }

    // Draw the marker
    if ( iExt->IsFlagSet( CAknSliderExtension::EFlagMarkerEnabled ) &&
        aDrawMarker )
        {
        TRect rect;
        TAknSliderGfx gfx;

        GetMarkerRect( rect );
        if ( iExt->IsFlagSet( CAknSliderExtension::EFlagPointerDown ) )
            {
            FetchGfx( gfx, EElemMarkerSelected, rect.Size() );
            }
        else
            {
            FetchGfx( gfx, EElemMarker, rect.Size() );
            }

        CondBlit( gc, rect.iTl, gfx.iRgb, rect.Size(), gfx.iMask, ETrue );
        }
   }


// ----------------------------------------------------------------------------
// CAknSlider::DrawVertical
// ----------------------------------------------------------------------------
//
void CAknSlider::DrawVertical( TBool aDrawMarker ) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetBrushStyle( CGraphicsContext::ENullBrush );
    gc.SetBrushColor( AKN_LAF_COLOR( 0 ) );
    gc.SetPenColor( AKN_LAF_COLOR( 0 ) );
    
    // Don't draw slider in form view mode
    if ( !( Layout() == EAknSettingsItemSliderLayout ||
            Layout() == EAknSettingsItemSliderLayoutWithGraphics || 
            Layout() == EAknSliderLayoutVertical||
            Layout() == EAknSliderLayoutHorizontal ||
            iEditable ) )
        {
        return;
        }
    
    DrawVerticalLine( gc ); // Draw line and end caps

    // Draw the tick marks, if any
    if ( iExt->IsFlagSet( CAknSliderExtension::EFlagTickMarksEnabled ) )
        {
        DrawVerticalTickMarks( gc );
        }

    // Draw the marker
    if ( iExt->IsFlagSet( CAknSliderExtension::EFlagMarkerEnabled ) &&
        aDrawMarker )
        {
        TRect rect;
        TAknSliderGfx gfx;

        GetMarkerRect( rect );
        if ( iExt->IsFlagSet( CAknSliderExtension::EFlagPointerDown ) )
            {
            FetchGfx( gfx, EElemMarkerSelected, rect.Size() );
            }
        else
            {
            FetchGfx( gfx, EElemMarker, rect.Size() );
            }

        CondBlit( gc, rect.iTl, gfx.iRgb, rect.Size(), gfx.iMask, ETrue );
        }
    }


// ----------------------------------------------------------------------------
// CAknSlider::DrawHorizontalLine
// ----------------------------------------------------------------------------
//
void CAknSlider::DrawHorizontalLine( CWindowGc& aGc ) const
    {
    TPoint pos;
    TSize size;
    TAknSliderGfx gfx;

    TRect mrect;
    GetMarkerRect( mrect );
    TInt markerW2 = mrect.Width() / 2;
    
    // End caps and line use the same height
    size = iExt->iLeftCapRect.Size();
        
    // Draw the left cap, if any
    if ( iExt->iLeftCapRect.Size().iWidth > 0 )
        {
        pos = iExt->iLeftCapRect.iTl;        
        FetchGfx( gfx, EElemEmptyLeftCap, size );
        CondBlit( aGc, pos, gfx.iRgb, size, gfx.iMask );

        // Fill the left cap if needed
        if ( iExt->IsFlagSet( CAknSliderExtension::EFlagFillEnabled ) && 
             iValue != MinimumValue())
            {
            FetchGfx( gfx, EElemFilledLeftCap, size );
            CondBlit( aGc, pos, gfx.iRgb, size, gfx.iMask );
            }
        }

    // Draw the right cap, if any
    if ( iExt->iRightCapRect.Size().iWidth > 0 )
        {
        pos = iExt->iRightCapRect.iTl; 
        FetchGfx( gfx, EElemEmptyRightCap, size );
        CondBlit( aGc, pos, gfx.iRgb, size, gfx.iMask );

        // Fill the right cap if needed
        if ( iExt->IsFlagSet( CAknSliderExtension::EFlagFillEnabled ) &&
             iValue >= MaximumValue() )
            {
            FetchGfx( gfx, EElemFilledRightCap, size );
            CondBlit( aGc, pos, gfx.iRgb, size, gfx.iMask );
            }
        }

    // Draw the line
    FetchGfx( gfx, EElemEmptyLine, iLineRect.Size() );
    CondBlit( aGc, iLineRect.iTl, gfx.iRgb, iLineRect.Size(), gfx.iMask );

    // Draw the line filling, if any
    if ( iExt->IsFlagSet( CAknSliderExtension::EFlagFillEnabled ) )
        {
        if( Layout() == EAknSliderLayoutHorizontal )
            {
            //pos.SetXY( iLineRect.iTl.iX + mrect.Width(), mrect.iTl.iY );
            pos.SetXY( iLineRect.iTl.iX, mrect.iTl.iY );
            size  = iLineRect.Size();
            FetchGfx( gfx, EElemFilledLine, size );
            //size.iWidth = iLineRect.iBr.iX - ( mrect.iTl.iX + mrect.Width() );
            size.iWidth = mrect.iTl.iX - iLineRect.iTl.iX;
        
        
            if ( MaximumValue() == iValue )
                {
                pos = iLineRect.iTl;
                size.iWidth = iLineRect.Width();
                }
            if ( MinimumValue() == iValue )
                {
                //pos.SetXY( iLineRect.iTl.iX, mrect.iTl.iY + markerH2/*iLineRect.iBr.iY*/ );
                //size.iHeight = size.iHeight - markerH2;
                }
           
            CondBlit( aGc, iLineRect.iTl, gfx.iRgb, size, gfx.iMask );
            }
        else
            {
            size.iWidth = mrect.iTl.iX + markerW2 - iLineRect.iTl.iX ;
            FetchGfx( gfx, EElemFilledLine, size );
            if ( MaximumValue() == iValue )
                {
                size.iWidth = iLineRect.Width();
                }

        CondBlit( aGc, iLineRect.iTl, gfx.iRgb, size, gfx.iMask );
            }
        }
    }

// ----------------------------------------------------------------------------
// RectBlit
//
// Helper C-function for conditional blitting, static to make the function
// visible to this compilation unit only.
// ----------------------------------------------------------------------------
//
inline static void RectBlit( CWindowGc& aGc, const TPoint& aTl,
        const TSize& aSize, const TInt aPosY,
        const CFbsBitmap* aBitmap, const CFbsBitmap* aMask )
    {
    aGc.SetBrushStyle( CGraphicsContext::ENullBrush );
    aGc.SetPenStyle( CGraphicsContext::ENullPen );
    aGc.SetBrushColor( AKN_LAF_COLOR( 0 ) );
    aGc.SetPenColor( AKN_LAF_COLOR( 0 ) );
    
    if ( aBitmap && aMask )
        {
        aGc.BitBltMasked( aTl,
                          aBitmap,
                          TRect( TPoint( 0, aPosY ),
                                 TSize( aSize.iWidth, aSize.iHeight - aPosY ) ),
                          aMask,
                          ETrue );
        }
    else if ( aBitmap )
        {
        aGc.BitBlt( aTl,
                    aBitmap,
                    TRect( TPoint(0, aPosY),
                           TSize( aSize.iWidth, aSize.iHeight - aPosY ) ) );
        }
    else
        {
        // If no bitmap resource, it doesn't need to render default color any more
        /*aGc.SetBrushStyle( CGraphicsContext::ESolidBrush );
        aGc.SetBrushColor( AKN_LAF_COLOR( KAknSliderDefaultDrawColor ) );
        aGc.SetPenStyle( CGraphicsContext::ESolidPen );
        aGc.SetPenColor( AKN_LAF_COLOR( KAknSliderDefaultDrawColor ) );
        aGc.DrawRect( TRect( aTl, TSize( aSize.iWidth, aSize.iHeight - aPosY ) ) );*/
        }
    }


// ----------------------------------------------------------------------------
// CAknSlider::DrawVerticalLine
// ----------------------------------------------------------------------------
//
void CAknSlider::DrawVerticalLine( CWindowGc& aGc ) const
    {
    TPoint pos;
    TSize size;
    TAknSliderGfx gfx;

    TRect mrect;
    GetMarkerRect( mrect );

    TInt markerH2 = mrect.Height() / 2;
    TInt fromTop(0);

    // End caps and line use the same width
    size = iExt->iLeftCapRect.Size();

    // Draw the bottom cap, if any
    if ( iExt->iLeftCapRect.Size().iWidth > 0 )
        {
        pos = iExt->iLeftCapRect.iTl;
        FetchGfx( gfx, EElemEmptyLeftCap, size );
        CondBlit( aGc, pos, gfx.iRgb, size, gfx.iMask );

        // Fill the bottom cap if needed
        if ( iExt->IsFlagSet( CAknSliderExtension::EFlagFillEnabled ) )
            {
            //bottom cap filled when all the line filled
            FetchGfx( gfx, EElemFilledLeftCap, size );
            RectBlit( aGc, pos, size, fromTop,
                      gfx.iRgb, gfx.iMask );
            }
        }

    // Draw the top cap, if any
    if ( iExt->iRightCapRect.Size().iWidth > 0 )
        {
        pos = pos = iExt->iRightCapRect.iTl;

        FetchGfx( gfx, EElemEmptyRightCap, size );
        CondBlit( aGc, pos, gfx.iRgb, size, gfx.iMask );

        if ( iExt->IsFlagSet( CAknSliderExtension::EFlagFillEnabled ) && 
             iValue >= MaximumValue() )
            {
            FetchGfx( gfx, EElemFilledRightCap, size );
            RectBlit( aGc, pos, size, fromTop, gfx.iRgb, gfx.iMask );
            }
        }
        
    // Draw the line
    FetchGfx( gfx, EElemEmptyLine, iLineRect.Size() );
    CondBlit( aGc, iLineRect.iTl, gfx.iRgb, iLineRect.Size(), gfx.iMask );

    // Draw the line filling, if any
    if ( iExt->IsFlagSet( CAknSliderExtension::EFlagFillEnabled ) )
        {
        pos.SetXY( iLineRect.iTl.iX, mrect.iTl.iY + mrect.Height() );
        size  = iLineRect.Size();
        FetchGfx( gfx, EElemFilledLine, size );
        size.iHeight = iLineRect.iBr.iY - ( mrect.iTl.iY + mrect.Height() );
        
        
        if ( MaximumValue() == iValue )
            {
            pos = iLineRect.iTl;
            size.iHeight = iLineRect.Height();
            }
        if ( MinimumValue() == iValue )
            {
            //pos.SetXY( iLineRect.iTl.iX, mrect.iTl.iY + markerH2/*iLineRect.iBr.iY*/ );
            //size.iHeight = size.iHeight - markerH2;
            }
        RectBlit( aGc, pos, iLineRect.Size(),
                  iLineRect.Height() - size.iHeight,
                  gfx.iRgb, gfx.iMask );
        }
    }


// ----------------------------------------------------------------------------
// CAknSlider::FetchGfx
// ----------------------------------------------------------------------------
//
void CAknSlider::FetchGfx(
        TAknSliderGfx& aGfx, TInt aElement, const TSize& aSize ) const
    {
    if ( aElement < 0 || aElement > EElemMarkerSelected )
        {
        Panic( EAknPanicInvalidValue );
        }

    TScaleMode mode = EAspectRatioNotPreserved; // default ratio
    
    // Step 1: Check if custom graphics have been defined for this element.
    if ( !iExt->UsesDefaultGraphics( aElement ) || 
          Layout() == EAknSliderLayoutVertical ||
          Layout() == EAknSliderLayoutHorizontal )
        {
        iExt->GetGfx( aGfx, aElement );
        if ( ( aElement == EElemEmptyLine ) || ( aElement == EElemFilledLine ) )
            {
            mode = EAspectRatioNotPreserved;
            }
        
        if ( aGfx.iRgb )
            {
            AknIconUtils::SetSize( aGfx.iRgb, aSize, mode );
            }
        if ( aGfx.iMask )
            {
            AknIconUtils::SetSize( aGfx.iMask, aSize, mode );
            }
            
        return;
        }
    else
        {
        aGfx.iRgb = NULL;
        aGfx.iMask = NULL;
        }
        
    // Step 2: No custom graphics, try Avkon icons.    
    if( Layout() != EAknSliderLayoutVertical && Layout() != EAknSliderLayoutHorizontal )//vertical is always customized
       {
        if ( EElemEmptyLine == aElement )
            {
            aGfx.iRgb = iExt->iLineIcon;
            aGfx.iMask = iExt->iLineIconMask;
            }
        else if ( EElemMarker == aElement ||
                  EElemMarkerSelected == aElement )
            {
            aGfx.iRgb = iMarkerBmp;
            aGfx.iMask = iMarkerMaskBmp;
            }
        }

    //resize the graphic    
    if ( aGfx.iRgb )
        {
        AknIconUtils::SetSize( aGfx.iRgb, aSize, mode );
        }
    if ( aGfx.iMask )
        {
        AknIconUtils::SetSize( aGfx.iMask, aSize, mode );
        }

    }

// ----------------------------------------------------------------------------
// CAknSlider::EnableDrag
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknSlider::EnableDrag()
    {
    EnableDragEvents();
    }

// ----------------------------------------------------------------------------
// CAknSlider::SetLabelColor
// ----------------------------------------------------------------------------
//

void CAknSlider::SetLabelColor()
    {
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    TRgb color;
    TInt error;
    if ( Layout() != EAknSettingsItemSliderLayout &&
         Layout() != EAknSettingsItemSliderLayoutWithGraphics  &&
         Layout() != EAknSliderLayoutVertical &&
         Layout() != EAknSliderLayoutHorizontal ) 
        {
        error = AknsUtils::GetCachedColor( skin, color,
                    KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG8 );
        }
    else
        {
        error = AknsUtils::GetCachedColor( skin, color,
                    KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG7 );
        }

    if ( !error )
        {
        // ignore error
        TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL(
                        *iMinLabel, EColorLabelText, color ) );
        TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL(
                        *iMaxLabel, EColorLabelText, color ) );
        TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL(
                        *iValueLabel, EColorLabelText, color ) );
        }

    AknsUtils::GetCachedColor( skin, color, KAknsIIDQsnLineColors,
                               EAknsCIQsnLineColorsCG8 );
    iColor = color;
    }

// ----------------------------------------------------------------------------
// CAknSlider::ReportMarkerDragEvent
// ----------------------------------------------------------------------------
//
void CAknSlider::ReportMarkerDragEvent( TBool aEnable )
    {
    iExt->iReportMarkerDragEvent = aEnable;
    }

void CAknSlider::SuppressDrawing( TBool aSuppress )
    {
    iExt->iNoDraw = aSuppress;
    }

// ----------------------------------------------------------------------------
// CAknSlider::FocusChanged
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknSlider::FocusChanged(TDrawNow /*aDrawNow*/)
    {
    if ( !IsFocused() )
        {
        iExt->ClearFlag( CAknSliderExtension::EFlagPointerDown );
        iExt->ClearFlag( CAknSliderExtension::EFlagDraggingThumb );
        // Marker icon changes - draw
        if ( !iExt->iNoDraw )
            {
            DrawDeferred();    
            }
        }
    }

// ----------------------------------------------------------------------------
// CAknSlider::StartFeedback
// ----------------------------------------------------------------------------
//
void CAknSlider::StartFeedback( const TPointerEvent* aPointerEvent, TTimeIntervalMicroSeconds32 aTimeout )
    {
    MTouchFeedback* feedback = MTouchFeedback::Instance();
    if ( feedback )
        {
        TInt intensity = KStableFeedbackIntesity;
        if ( SliderData()->iFeedbackStyle == EAknSliderFbDynamic )
            {
            intensity = FeedbackIntensity();
            }
        feedback->StartFeedback( this, ETouchContinuousSlider, aPointerEvent, intensity, aTimeout );
        iExt->SetFlag( CAknSliderExtension::EFlagPlayingContinuousFb );
        }
    }

// ----------------------------------------------------------------------------
// CAknSlider::StopFeedback
// ----------------------------------------------------------------------------
//
void CAknSlider::StopFeedback() 
    {
    iExt->ClearFlag( CAknSliderExtension::EFlagPlayingContinuousFb );
    MTouchFeedback* feedback = MTouchFeedback::Instance();
    if ( feedback )
        {
        feedback->StopFeedback( this );
        }
    }

// ----------------------------------------------------------------------------
// CAknSlider::ModifyFeedback
// ----------------------------------------------------------------------------
//
void CAknSlider::ModifyFeedback() 
    {
    TInt intensity = FeedbackIntensity();
    MTouchFeedback* feedback = MTouchFeedback::Instance();
    if ( feedback )
        {
        feedback->ModifyFeedback( this, intensity );
        }
    }


// ----------------------------------------------------------------------------
// CAknSlider::FeedbackIntensity
// ----------------------------------------------------------------------------
//
TInt CAknSlider::FeedbackIntensity() 
    {
    TRect mrect;
    GetMarkerRect( mrect );
    TBool hor = iExt->IsFlagSet( CAknSliderExtension::EFlagHorizontal );

    if ( hor )
        {
        TInt position = mrect.iTl.iX  - iMarkerArea.iTl.iX;
        return TReal( position )/TReal( iMarkerArea.Width()-mrect.Width() )*100;    
        }
    else
        {
        TInt position = iMarkerArea.iBr.iY - mrect.iBr.iY;
        return TReal( position )/TReal( iMarkerArea.Height()-mrect.Height() )*100;    
        }
    }


// ---------------------------------------------------------------------------
// Provides the touch active area for setting page slider.
// ---------------------------------------------------------------------------
//
TRect CAknSlider::TouchActiveArea() const
    {
    TRect touchActiveArea;
    TPoint winPosition( Window().AbsPosition() );

    TRect appRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EApplicationWindow,
                                       appRect );
    TAknLayoutRect mainpaneRect;
    mainpaneRect.LayoutRect( appRect, AknLayoutScalable_Apps::main_pane(3) );
    touchActiveArea = mainpaneRect.Rect();

    // Convert main pane rect location to slider window coordinates
    touchActiveArea.Move(
            touchActiveArea.iTl.iX - winPosition.iX,
            touchActiveArea.iTl.iY - winPosition.iY );
    return touchActiveArea;
    }

//  End of File

