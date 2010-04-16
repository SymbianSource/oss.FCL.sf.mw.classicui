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
* Description:  Handles incall status bubble drawing.
*
*/


// SYSTEM INCLUDE FILES
#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikdefmacros.h>
#endif
#include    <eikimage.h>
#include    <eikenv.h>
#include    <barsread.h>            // Resource reader
#include    <bautils.h>             // erase
#include    <avkon.rsg>
#include    <AknsUtils.h>
#include    <AknsDrawUtils.h>
#include    <aknlayoutscalable_apps.cdl.h>
#include    <layoutmetadata.cdl.h>
#include    <AknIconUtils.h>
#include    <featmgr.h>
#include    <akniconconfig.h>
#include    <coeaui.h>
#include    <coemain.h>
#include    <coreapplicationuisdomainpskeys.h> // KCoreAppUIsAutolockStatus

#include <AknTasHook.h>
// USER INCLUDE FILES
#include    "AknIncallStatusBubble.h"
#include    "AknBitmapAnimation.h"  // Animation definition
#include    "AknUtils.h"
#include    "aknappui.h"
#include    "AknDef.h"
#include    "aknconsts.h"
#include    "AknStatuspaneUtils.h"

// CONSTANTS

// There does not seem to be any way to query WSERV wheter TRANSPARENCY option has been
// defined. We use this constant to decide which way we do things.
// const TBool KTransparentWindowsUsed = EFalse;  // Disabled at the moment for performance reasons.

const TUid KPhoneAppUid      = { 0x100058B3 };
const TUid KPhoneViewUid     = { 0x10282D81 };
const TUid KPhoneVievCommand = { 0x2 }; // forces call handling to foreground
const TUid KVideoCallUid     = { 0x101F8681 }; 

// Note that some icons are masked and some are non-masked.

enum // Grouped by icon layout...
    {
    // Layout1
    EIndexCallstatusQgn_indi_call_active = 0,
    EIndexCallstatusQgn_indi_call_active_mask,
    EIndexCallstatusQgn_indi_call_active_2,
    EIndexCallstatusQgn_indi_call_active_2_mask,
    EIndexCallstatusQgn_indi_call_active_cyph_off,
    EIndexCallstatusQgn_indi_call_active_cyph_off_mask,
    EIndexCallstatusQgn_indi_call_disconn,
    EIndexCallstatusQgn_indi_call_disconn_mask,
    EIndexCallstatusQgn_indi_call_disconn_cyph_off,
    EIndexCallstatusQgn_indi_call_disconn_cyph_off_mask,
    EIndexCallstatusQgn_indi_call_held,
    EIndexCallstatusQgn_indi_call_held_mask,
    EIndexCallstatusQgn_indi_call_held_cyph_off,
    EIndexCallstatusQgn_indi_call_held_cyph_off_mask,
    EIndexCallstatusQgn_indi_call_muted_callsta,
    EIndexCallstatusQgn_indi_call_muted_callsta_mask,
    EIndexCallstatusQgn_indi_call_video_callsta,
    EIndexCallstatusQgn_indi_call_video_callsta_mask,
    EIndexCallstatusQgn_indi_call_video_callsta_1,
    EIndexCallstatusQgn_indi_call_video_callsta_1_mask,
    EIndexCallstatusQgn_indi_call_video_callsta_2,
    EIndexCallstatusQgn_indi_call_video_callsta_2_mask,
    EIndexCallstatusQgn_indi_call_active_emergency,
    EIndexCallstatusQgn_indi_call_active_emergency_mask,
    EIndexCallstatusQgn_indi_call_video_1,
    EIndexCallstatusQgn_indi_call_video_1_mask,
    EIndexCallstatusQgn_indi_call_video_disconn,
    EIndexCallstatusQgn_indi_call_video_disconn_mask,
    EIndexCallStatusQgn_indi_call_voip_active,
    EIndexCallStatusQgn_indi_call_voip_active_mask,
    EIndexCallStatusQgn_indi_call_voip_active_2,
    EIndexCallStatusQgn_indi_call_voip_active_2_mask,
    EIndexCallStatusQgn_indi_call_voip_disconn,
    EIndexCallStatusQgn_indi_call_voip_disconn_mask,
    EIndexCallStatusQgn_indi_call_voip_held,
    EIndexCallStatusQgn_indi_call_voip_held_mask,
    ELayout1End = EIndexCallStatusQgn_indi_call_voip_held_mask,

    // Layout2
    EIndexCallstatusQgn_graf_bubble_incall,
    EIndexCallstatusQgn_graf_bubble_incall_mask,
    EIndexCallstatusQgn_graf_bubble_incall_disconn,
    EIndexCallstatusQgn_graf_bubble_incall_disconn_mask,
    ELayout2End = EIndexCallstatusQgn_graf_bubble_incall_disconn_mask,

    // Layout3
    EIndexCallstatusQgn_indi_call_cyphering_off,
    EIndexCallstatusQgn_indi_call_cyphering_off_mask, // not used, but AknIconUtils & SVG needs this to exist
    //ELayout3End = EIndexCallstatusQgn_indi_call_cyphering_off,
    ELayout3End = EIndexCallstatusQgn_indi_call_cyphering_off_mask,

    // Layout4
    EIndexCallstatusQgn_indi_call_data,
    EIndexCallstatusQgn_indi_call_data_mask, // not used, but AknIconUtils & SVG needs this to exist
    EIndexCallstatusQgn_indi_call_data_hscsd,
    EIndexCallstatusQgn_indi_call_data_hscsd_mask, // not used, but AknIconUtils & SVG needs this to exist
    EIndexCallstatusQgn_indi_call_fax,
    EIndexCallstatusQgn_indi_call_fax_mask, // not used, but AknIconUtils & SVG needs this to exist
    //ELayout4End = EIndexCallstatusQgn_indi_call_fax,
    ELayout4End = EIndexCallstatusQgn_indi_call_fax_mask,

    // Layout5
    EIndexCallstatusQgn_indi_call_line2,
    EIndexCallstatusQgn_indi_call_line2_mask, // not used, but AknIconUtils & SVG needs this to exist
    //ELayout5End = EIndexCallstatusQgn_indi_call_line2
    ELayout5End = EIndexCallstatusQgn_indi_call_line2_mask
    };

// Cleanup stack helper.

NONSHARABLE_CLASS( CCleanupGuard ) : public CBase
    {
    public:
        inline CCleanupGuard() {}
        ~CCleanupGuard();
    public:
        inline void SetItem1( CBase* aItem ) {iItem1 = aItem;}
        inline void SetItem2( CBase* aItem ) {iItem2 = aItem;}
    private:
        CBase* iItem1;
        CBase* iItem2;
    };

CCleanupGuard::~CCleanupGuard()
    {
    delete iItem1;
    delete iItem2;
    }

// ==== CIncallAnim  CLASS ======================

/**
* Helper class for animation control
*/
NONSHARABLE_CLASS( CIncallAnim ) : public CCoeControl
    {
    public:

    enum
        {
        EDefaultCallAnim,
        EVoipCallAnim,
        EVideoCallAnim
        };


    public:
        void ConstructL( CIncallStatusBubble& aImages );
        ~CIncallAnim();
        void MakeVisible( TBool aVisible );

        void ClearAnimation();
        void SetAnimationL( CIncallStatusBubble& aImages,
                            TInt aCallAnimType = EDefaultCallAnim );
        void SetAnimationType( TInt aCallAnimType );
        void CreateBackGroundImageL( const CFbsBitmap* aBubbleBitmap,
                                     const CFbsBitmap* aBubbleMask,
                                     TRect aBubbleRect );

    private:
        void UpdateAnimationL( CIncallStatusBubble& aImages,
                               TInt aCallAnimType = EDefaultCallAnim );
        void SizeChanged();
        void Draw( const TRect& aRect ) const;
    private:
        CAknBitmapAnimation* iIndiAnim;
        CAknBitmapAnimation* iIndiVoIPAnim;
        CAknBitmapAnimation* iIndiVideoAnim;
        CFbsBitmap* iAnimBackGroundImage;
        mutable TBool iIsRunning;
        mutable TBool iIsVoIPRunning;
        mutable TBool iIsVideoRunning;
        TInt iCallAnimType;
    };

// Constructor
void CIncallAnim::ConstructL( CIncallStatusBubble& aImages )
    {
    iCallAnimType = EDefaultCallAnim;

    iAnimBackGroundImage = new ( ELeave ) CFbsBitmap();

    SetAnimationL( aImages );

    ActivateL();

    CCoeControl::MakeVisible( EFalse );
    }

// Destructor
CIncallAnim::~CIncallAnim()
    {
    delete iIndiAnim;
    delete iIndiVoIPAnim;
    delete iIndiVideoAnim;
    delete iAnimBackGroundImage;
    }

void CIncallAnim::CreateBackGroundImageL(const CFbsBitmap* aBubbleBitmap, const CFbsBitmap* aBubbleMask, TRect aBubbleRect)
    {
    if (iAnimBackGroundImage && aBubbleBitmap && aBubbleMask)
        {
        CFbsBitmapDevice* destinationDevice = CFbsBitmapDevice::NewL(iAnimBackGroundImage);
        CleanupStack::PushL(destinationDevice);

        CFbsBitGc* destinationGc;
        User::LeaveIfError( destinationDevice->CreateContext( destinationGc ) );

        TRect rect = Rect();
        rect.Move(-aBubbleRect.iTl);
        destinationGc->BitBltMasked(TPoint(0,0), aBubbleBitmap, rect, aBubbleMask, ETrue);

        delete destinationGc;
        CleanupStack::PopAndDestroy(destinationDevice);
        }
    }

// Position/Size changed
void CIncallAnim::SizeChanged()
    {
    TRect rect( Rect() );

    if ( !iIndiAnim || !iIndiVoIPAnim || !iIndiVideoAnim )
        {
        return;
        }

    if ( Rect().IsEmpty() )
        return;

    if ( ( rect.Size() != iIndiAnim->Size() ) ||
         ( rect.Size() != iIndiVoIPAnim->Size() ) ||
         ( rect.Size() != iIndiVideoAnim->Size() ))
        {
        AknIconConfig::TPreferredDisplayMode mode;
        AknIconConfig::PreferredDisplayMode(mode, AknIconConfig::EImageTypeOffscreen);
        iAnimBackGroundImage->Create(
            Size(),
            mode.iBitmapMode);
        }
    iIndiAnim->SetRect( rect );
    iIndiVoIPAnim->SetRect( rect );
    iIndiVideoAnim->SetRect( rect );
    }

// Draws the animation
void CIncallAnim::Draw( const TRect& /*aRect*/ ) const
    {
    CAknBitmapAnimation* ok = NULL;
    switch (iCallAnimType)
        {
        case EDefaultCallAnim:
            ok = iIndiAnim;
            break;
        case EVoipCallAnim:
            ok = iIndiAnim;
            break;
        case EVideoCallAnim:
            ok = iIndiAnim;
            break;
        default:
            ok = NULL;
            break;
        }
    
    if ( !ok )
        {
        return;
        }


    // Background is no more copied from screen because it does not work very well.
    // Instead we use the image that has been set.
    if (iAnimBackGroundImage)
        {
        // Create frame for background
        CBitmapFrameData* data = NULL;
        TRAPD( error , ( data = CBitmapFrameData::NewL() ) );
        if ( error != KErrNone || data == NULL )
            {
            iIsRunning = EFalse;
            iIsVoIPRunning = EFalse;
            return;
            }

        data->SetBitmapsOwnedExternally( ETrue );
        data->SetBitmap( iAnimBackGroundImage );
        data->SetInterval( -1 );

        // Set frame to animation
        CBitmapAnimClientData* animData;

        if ( iCallAnimType == EVoipCallAnim )
            {
            animData = iIndiVoIPAnim->BitmapAnimData();
            }
        else if ( iCallAnimType == EVideoCallAnim )
            {
            animData = iIndiVideoAnim->BitmapAnimData();
            }
        else
            {
            animData = iIndiAnim->BitmapAnimData();
            }

        animData->SetBackgroundFrame( data );

        // This is a const function so mutable cast is needed
        // to change member variables
        CIncallAnim* mutableThis =
            MUTABLE_CAST( CIncallAnim* , this );

        // Start animation - we can't do a thing if this fails
        if ( iCallAnimType == EVoipCallAnim )
            {
            TRAP( error , iIndiVoIPAnim->StartAnimationL() );
            mutableThis->iIsVoIPRunning = ETrue;
            mutableThis->iIsRunning = EFalse;
            mutableThis->iIsVideoRunning = EFalse;
            }
        else if ( iCallAnimType == EVideoCallAnim )
            {
            TRAP( error , iIndiVideoAnim->StartAnimationL() );
            mutableThis->iIsVoIPRunning = EFalse;
            mutableThis->iIsVideoRunning = ETrue;
            mutableThis->iIsRunning = EFalse;
            }
        else
            {
            TRAP( error , iIndiAnim->StartAnimationL() );
            mutableThis->iIsVoIPRunning = EFalse;
            mutableThis->iIsRunning = ETrue;
            mutableThis->iIsVideoRunning = EFalse;
            }
        }
    }

// Creates new animation frames
void CIncallAnim::SetAnimationL( CIncallStatusBubble& aImages, TInt aCallAnimType )
    {
    iCallAnimType = aCallAnimType;

    // Create new animation
    iIndiAnim = CAknBitmapAnimation::NewL();
    iIndiAnim->SetContainerWindowL( *this );
    iIndiVoIPAnim = CAknBitmapAnimation::NewL();
    iIndiVoIPAnim->SetContainerWindowL( *this );
    iIndiVideoAnim = CAknBitmapAnimation::NewL();
    iIndiVideoAnim->SetContainerWindowL( *this );

    TInt resourceReaderId = 0;
    resourceReaderId = R_BUBBLEMANAGER_ALERTING_ANIM;
    TResourceReader rr;
    iCoeEnv->CreateResourceReaderLC( rr , resourceReaderId );
    iIndiAnim->ConstructFromResourceL(rr);
    CleanupStack::PopAndDestroy(); // rr

    resourceReaderId = R_BUBBLEMANAGER_ALERTING_VOIP_ANIM;
    TResourceReader rr2;
    iCoeEnv->CreateResourceReaderLC( rr2 , resourceReaderId );
    iIndiVoIPAnim->ConstructFromResourceL(rr2);
    CleanupStack::PopAndDestroy(); // rr2

    resourceReaderId = R_BUBBLEMANAGER_ALERTING_VIDEO_ANIM;
    TResourceReader rr3;
    iCoeEnv->CreateResourceReaderLC( rr3 , resourceReaderId );
    iIndiVideoAnim->ConstructFromResourceL(rr3);
    CleanupStack::PopAndDestroy(); // rr3

    UpdateAnimationL( aImages, EDefaultCallAnim );// Normal CS call.
    UpdateAnimationL( aImages, EVoipCallAnim ); // VoIP call.
    UpdateAnimationL( aImages, EVideoCallAnim ); // Video call.
    }

void CIncallAnim::UpdateAnimationL( CIncallStatusBubble& aImages, TInt aCallAnimType )
    {
    // Clear old data:
    CBitmapAnimClientData* animData;
    if ( aCallAnimType == EVoipCallAnim )
        {
        animData = iIndiVoIPAnim->BitmapAnimData();
        }
    else if (iCallAnimType == EVideoCallAnim)
        {
        animData = iIndiVideoAnim->BitmapAnimData();
        }
    else
        {
        animData = iIndiAnim->BitmapAnimData();
        }

    animData->ResetFrameArray();

    // Create frame 1
    CEikImage* image1 = new (ELeave) CEikImage;
    image1->SetPictureOwnedExternally( ETrue );
    CleanupStack::PushL( image1 );

    if ( aCallAnimType == EVoipCallAnim )
        {
        aImages.GetImage(
            *image1,
            EIndexCallStatusQgn_indi_call_voip_active,
            EIndexCallStatusQgn_indi_call_voip_active_mask
            );
        }
    else if (iCallAnimType == EVideoCallAnim)
        {
        aImages.GetImage(
            *image1,
            EIndexCallstatusQgn_indi_call_video_callsta_1,
            EIndexCallstatusQgn_indi_call_video_callsta_1_mask
            );
        }
    else
        {
        aImages.GetImage(
            *image1,
            EIndexCallstatusQgn_indi_call_active,
            EIndexCallstatusQgn_indi_call_active_mask
            );
        }

    CBitmapFrameData* frame1 = CBitmapFrameData::NewL(
        MUTABLE_CAST( CFbsBitmap*, image1->Bitmap() ),
        MUTABLE_CAST( CFbsBitmap*, image1->Mask() ) );

    frame1->SetInterval( KErrNotFound );
    frame1->SetBitmapsOwnedExternally( ETrue );
    CleanupStack::PushL( frame1 );

    animData->AppendFrameL( frame1 ); // Takes ownership

    CleanupStack::Pop( frame1 );
    CleanupStack::PopAndDestroy( image1 );

    // Create frame 2
    CEikImage* image2 = new (ELeave) CEikImage;
    image2->SetPictureOwnedExternally( ETrue );
    CleanupStack::PushL( image2 );

    if ( aCallAnimType == EVoipCallAnim )
        {
        aImages.GetImage(
            *image2,
            EIndexCallStatusQgn_indi_call_voip_active_2,
            EIndexCallStatusQgn_indi_call_voip_active_2_mask
            );
        }
    else if (iCallAnimType == EVideoCallAnim)
        {
        aImages.GetImage(
            *image2,
            EIndexCallstatusQgn_indi_call_video_callsta_2,
            EIndexCallstatusQgn_indi_call_video_callsta_2_mask
            );
        }
    else
        {
        aImages.GetImage(
            *image2,
            EIndexCallstatusQgn_indi_call_active_2,
            EIndexCallstatusQgn_indi_call_active_2_mask
            );
        }

    CBitmapFrameData* frame2 = CBitmapFrameData::NewL(
        MUTABLE_CAST( CFbsBitmap*, image2->Bitmap() ),
        MUTABLE_CAST( CFbsBitmap*, image2->Mask() ) );

    frame2->SetInterval( KErrNotFound );
    frame2->SetBitmapsOwnedExternally( ETrue );
    CleanupStack::PushL( frame2 );

    animData->AppendFrameL( frame2 ); // Takes ownership

    CleanupStack::Pop( frame2 );
    CleanupStack::PopAndDestroy( image2 );
    }

void CIncallAnim::SetAnimationType( TInt aCallAnimType )
    {
    iCallAnimType = aCallAnimType;
    }

// Clears current animation
void CIncallAnim::ClearAnimation()
    {
    if ( iIndiAnim )
        {
        CBitmapAnimClientData* animData = iIndiAnim->BitmapAnimData();
        animData->ResetFrameArray();
        }
    delete iIndiAnim;
    iIndiAnim = NULL;

    if ( iIndiVoIPAnim )
        {
        CBitmapAnimClientData* animData = iIndiVoIPAnim->BitmapAnimData();
        animData->ResetFrameArray();
        }
    delete iIndiVoIPAnim;
    iIndiVoIPAnim = NULL;

    if ( iIndiVideoAnim )
        {
        CBitmapAnimClientData* animData = iIndiVideoAnim->BitmapAnimData();
        animData->ResetFrameArray();
        }
    delete iIndiVideoAnim;
    iIndiVideoAnim = NULL;

    }

// Make visible
void CIncallAnim::MakeVisible( TBool aVisible )
    {
    if ( IsVisible() && !aVisible && iIndiAnim && iIsRunning )
        {
        TInt err = iIndiAnim->CancelAnimation();
        if ( err == KErrNone )
            {
            iIsRunning = EFalse;
            }
        }

    if ( IsVisible() && !aVisible && iIndiVoIPAnim && iIsVoIPRunning )
        {
        TInt err = iIndiVoIPAnim->CancelAnimation();
        if ( err == KErrNone )
            {
            iIsVoIPRunning = EFalse;
            }
        }

    if ( IsVisible() && !aVisible && iIndiVideoAnim && iIsVideoRunning )
        {
        TInt err = iIndiVideoAnim->CancelAnimation();
        if ( err == KErrNone )
            {
            iIsVideoRunning = EFalse;
            }
        }

    CCoeControl::MakeVisible( aVisible ); // a call to parent's method
    }

// ==== CIncallAnim  CLASS ======================

/**
* Helper class for muted icon (has its own window)
*/
NONSHARABLE_CLASS(CIncallMuted) : public CCoeControl
    {
    public:
        void ConstructL( CCoeControl& aParent );
        ~CIncallMuted();

        void SetMutedImage(
            const CFbsBitmap* aBitmap ,
            const CFbsBitmap* aMask );

        TInt CountComponentControls() const;
        CCoeControl* ComponentControl(TInt aIndex) const;
    private:
        void SizeChanged();
        void HandlePointerEventL(const TPointerEvent& aPointerEvent);

    private:
        CEikImage* iMutedImage;
        CIncallStatusBubble *iIncallStatusBubble;
    };

// Constructor
void CIncallMuted::ConstructL( CCoeControl& aParent )
    {
    SetContainerWindowL( aParent );

    iIncallStatusBubble = ( CIncallStatusBubble* ) &aParent;

    iMutedImage = new( ELeave ) CEikImage;
    iMutedImage->SetContainerWindowL( *this );
    iMutedImage->SetPictureOwnedExternally( ETrue );
    iMutedImage->MakeVisible( EFalse );

    SetComponentsToInheritVisibility();
    Window().SetPointerGrab( ETrue );
    EnableDragEvents();
    }

// Destructor
CIncallMuted::~CIncallMuted()
    {
    delete iMutedImage;
    }

// Sets images
void CIncallMuted::SetMutedImage(
    const CFbsBitmap* aBitmap ,
    const CFbsBitmap* aMask )
    {
    iMutedImage->SetPicture( aBitmap , aMask );
    SizeChanged();
    }

// Count component control
TInt CIncallMuted::CountComponentControls() const
    {
    return 1;
    }

// Component control
CCoeControl* CIncallMuted::ComponentControl( TInt /*aIndex*/ ) const
    {
    return iMutedImage;
    }

// New size is checked.
void CIncallMuted::SizeChanged()
    {
    if ( !iMutedImage )
        {
        return;
        }

    iMutedImage->SetRect( Rect() );

    CFbsBitmap* bitmap = (CFbsBitmap*)iMutedImage->Bitmap();
    if ( bitmap )
        {
        AknIconUtils::SetSize( bitmap, Size() );
        }
    }


void CIncallMuted::HandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    CCoeControl::HandlePointerEventL( aPointerEvent );

    iIncallStatusBubble->HandlePointerEventL( aPointerEvent );
    }

// ================ CIncallStatusBubble CLASS ===============

// ================= MEMBER FUNCTIONS =======================

// Constructor
CIncallStatusBubble::CIncallStatusBubble() : iOrder( CompareSkinnedData )
    {
    }

// NewL
CIncallStatusBubble* CIncallStatusBubble::NewL( const TRect& aRect )
    {
    CIncallStatusBubble* self = new ( ELeave ) CIncallStatusBubble;
    CleanupStack::PushL( self );
    self->ConstructL( aRect );
    CleanupStack::Pop();
    AKNTASHOOK_ADDL( self, "CIncallStatusBubble" );
    return self;
    }


// ---------------------------------------------------------
// CIncallStatusBubble::ConstructL(const TRect& aRect)
// EPOC two phased constructor
//
// ---------------------------------------------------------
//
void CIncallStatusBubble::ConstructL( const TRect& aRect )
    {
    iMyWindowGroup=RWindowGroup( iCoeEnv->WsSession() );
    User::LeaveIfError( iMyWindowGroup.Construct( (TUint32)&iMyWindowGroup,
                                                   EFalse ) );
    iMyWindowGroup.SetOrdinalPosition( 0, ECoeWinPriorityMedium );
    CreateWindowL( &iMyWindowGroup );

    // Load bitmaps to an array
    iBitmaps = new ( ELeave ) CArrayPtrFlat<CFbsBitmap>( 4 );
    LoadImagesL();

    // Create skinned animation
    iSmallIndiAnim = new( ELeave ) CIncallAnim;
    iSmallIndiAnim->SetContainerWindowL( *this );
    iSmallIndiAnim->ConstructL( *this );

    // call indication
    iSmallCallIndication = CreateNewEikImageL();

    // bubble icon
    iBubble = CreateNewEikImageL();

    // type indicatiors
    iTypeIndication1 = CreateNewEikImageL();
    iTypeIndication2 = CreateNewEikImageL();

    // skinned muted icon
    iMutedIcon = new(ELeave) CIncallMuted;
    iMutedIcon->ConstructL( *this );
    CEikImage* tmpMutedImage = new(ELeave) CEikImage;
    CleanupStack::PushL( tmpMutedImage );
    tmpMutedImage->SetPictureOwnedExternally( ETrue );
    GetImage(
        *tmpMutedImage,
        EIndexCallstatusQgn_indi_call_muted_callsta,
        EIndexCallstatusQgn_indi_call_muted_callsta_mask
        );
    iMutedIcon->SetMutedImage(tmpMutedImage->Bitmap(), tmpMutedImage->Mask());
    CleanupStack::PopAndDestroy( tmpMutedImage );
    iMutedIcon->MakeVisible( EFalse );

    // Cyph off image
    iCyphOffIcon = CreateNewEikImageL();
    iPressedDown = EFalse; 
    // finnish the job
    MakeVisible( EFalse );
    SetRect( aRect );
    Window().SetPointerGrab( ETrue );
    EnableDragEvents();

    ActivateL();
    }

// ---------------------------------------------------------
// CIncallStatusBubble::CreateNewEikImageL
//
// ---------------------------------------------------------
//
CEikImage* CIncallStatusBubble::CreateNewEikImageL() const
    {
    CEikImage* newImage = new( ELeave ) CEikImage;
    CleanupStack::PushL( newImage );
    newImage->SetContainerWindowL( *this );
    newImage->SetPictureOwnedExternally( ETrue );
    newImage->SetPicture( NULL );
    newImage->MakeVisible( EFalse );
    CleanupStack::Pop(); // newImage
    return newImage;
    }

// ---------------------------------------------------------
// CIncallStatusBubble::LoadImagesL
//
// ---------------------------------------------------------
//
void CIncallStatusBubble::LoadImagesL()
    {
    // These need to be loaded in the same order as defined in the
    // enumeration in the beginning of this file.

    LoadImageL(
        EMbmCallstatusQgn_indi_call_active,
        EMbmCallstatusQgn_indi_call_active_mask );

    LoadImageL(
        EMbmCallstatusQgn_indi_call_active_2,
        EMbmCallstatusQgn_indi_call_active_2_mask );

    LoadImageL(
        EMbmCallstatusQgn_indi_call_active_cyph_off,
        EMbmCallstatusQgn_indi_call_active_cyph_off_mask );

    LoadImageL(
        EMbmCallstatusQgn_indi_call_disconn,
        EMbmCallstatusQgn_indi_call_disconn_mask );

    LoadImageL(
        EMbmCallstatusQgn_indi_call_disconn_cyph_off,
        EMbmCallstatusQgn_indi_call_disconn_cyph_off_mask );

    LoadImageL(
        EMbmCallstatusQgn_indi_call_held,
        EMbmCallstatusQgn_indi_call_held_mask );

    LoadImageL(
        EMbmCallstatusQgn_indi_call_held_cyph_off,
        EMbmCallstatusQgn_indi_call_held_cyph_off_mask );

    LoadImageL(
        EMbmCallstatusQgn_indi_call_muted_callsta,
        EMbmCallstatusQgn_indi_call_muted_callsta_mask );

    LoadImageL(
        EMbmCallstatusQgn_indi_call_video_callsta,
        EMbmCallstatusQgn_indi_call_video_callsta_mask );

    LoadImageL(
        EMbmCallstatusQgn_indi_call_video_callsta_1,
        EMbmCallstatusQgn_indi_call_video_callsta_1_mask );

    LoadImageL(
        EMbmCallstatusQgn_indi_call_video_callsta_2,
        EMbmCallstatusQgn_indi_call_video_callsta_2_mask );

    LoadImageL(
        EMbmCallstatusQgn_indi_call_active_emergency,
        EMbmCallstatusQgn_indi_call_active_emergency_mask );

    LoadImageL(
        EMbmCallstatusQgn_indi_call_video_1,
        EMbmCallstatusQgn_indi_call_video_1_mask );

    LoadImageL(
        EMbmCallstatusQgn_indi_call_video_disconn,
        EMbmCallstatusQgn_indi_call_video_disconn_mask );

    LoadImageL(
        EMbmCallstatusQgn_indi_call_voip_active,
        EMbmCallstatusQgn_indi_call_voip_active_mask );

    LoadImageL(
        EMbmCallstatusQgn_indi_call_voip_active_2,
        EMbmCallstatusQgn_indi_call_voip_active_2_mask );

    LoadImageL(
        EMbmCallstatusQgn_indi_call_voip_disconn,
        EMbmCallstatusQgn_indi_call_voip_disconn_mask );

    LoadImageL(
        EMbmCallstatusQgn_indi_call_voip_held,
        EMbmCallstatusQgn_indi_call_voip_held_mask );

    LoadImageL(
        EMbmCallstatusQgn_graf_bubble_incall,
        EMbmCallstatusQgn_graf_bubble_incall_mask );

    LoadImageL(
        EMbmCallstatusQgn_graf_bubble_incall_disconn,
        EMbmCallstatusQgn_graf_bubble_incall_disconn_mask );

    LoadImageL( EMbmCallstatusQgn_indi_call_cyphering_off );

    LoadImageL( EMbmCallstatusQgn_indi_call_data );

    LoadImageL( EMbmCallstatusQgn_indi_call_data_hscsd );

    LoadImageL( EMbmCallstatusQgn_indi_call_fax );

    LoadImageL( EMbmCallstatusQgn_indi_call_line2 );
    }


// Destructor
CIncallStatusBubble::~CIncallStatusBubble()
    {
    AKNTASHOOK_REMOVE();
    delete iMutedIcon;
    delete iSmallCallIndication;
    delete iSmallIndiAnim;
    delete iTypeIndication1;
    delete iTypeIndication2;
    delete iCyphOffIcon;
    delete iBubble;

    iSkins.ResetAndDestroy();
    delete iSkinnedColourBitmap;

    if ( iBitmaps )
        {
        iBitmaps->ResetAndDestroy( );
        delete iBitmaps;
        }

    iMyWindowGroup.Close();
    }

// ---------------------------------------------------------
// CIncallStatusBubble::SizeChanged()
// Called by framework when the view size is changed
//
// ---------------------------------------------------------
//
void CIncallStatusBubble::SizeChanged()
    {
    // For performance optimization purposes we do not continue if
    // we are not visible. Assumed that SetIncallBubbleFlags() causes
    // this method to be called again.
    if (!IsVisible() && !(iFlags & ESBVisible))
        return;

    TRect rect( Rect() );
    TBool isLandscape( Layout_Meta_Data::IsLandscapeOrientation() );

    // Set componets to right places

    TAknWindowLineLayout layout1(
        AknLayoutScalable_Apps::popup_call_status_window_g1(
            isLandscape ).LayoutLine() );

    TAknWindowLineLayout layout2(
        AknLayoutScalable_Apps::popup_call_status_window_g2(
            isLandscape ).LayoutLine() );

    TAknWindowLineLayout layout3(
        AknLayoutScalable_Apps::popup_call_status_window_g3( isLandscape ).LayoutLine() );

    TAknWindowLineLayout layout4(
        AknLayoutScalable_Apps::call_type_pane_g1().LayoutLine() );

    TAknWindowLineLayout layout5(
        AknLayoutScalable_Apps::call_type_pane_g2().LayoutLine() );

    AknLayoutUtils::LayoutImage( iBubble, rect, layout1 );

    AknLayoutUtils::LayoutControl( iSmallCallIndication, rect, layout2 );

    AknLayoutUtils::LayoutControl( iSmallIndiAnim, rect, layout2 );

    AknLayoutUtils::LayoutControl( iMutedIcon, rect, layout2 );

    TAknLayoutRect callTypeIndicationLayoutRect;
    callTypeIndicationLayoutRect.LayoutRect(
        rect,
        AknLayoutScalable_Apps::call_type_pane( isLandscape ) );
    TRect callTypeIndicationRect( callTypeIndicationLayoutRect.Rect() );
    
    TBool hideTypeIndication = isLandscape && !AknStatuspaneUtils::HDLayoutActive();
    	
    if ( iFlags & ESBVideo )
        {
        // video indicator is different size than others
        AknLayoutUtils::LayoutControl( iTypeIndication1, rect,  layout2 );
        }
    else
        {
        if ( hideTypeIndication )
            {
            // Not shown in landscape, because there's not enough space.
            TRect nullRect( 0, 0, 0, 0 );
            iTypeIndication1->SetRect( nullRect );
            iTypeIndication2->SetRect( nullRect );
            iCyphOffIcon->SetRect( nullRect );
            }
        else
            {
            AknLayoutUtils::LayoutControl( iTypeIndication1,
                                           callTypeIndicationRect,
                                           layout4 );

            AknLayoutUtils::LayoutControl( iTypeIndication2,
                                           callTypeIndicationRect,
                                           layout5 );

            AknLayoutUtils::LayoutControl( iCyphOffIcon,
                                           rect,
                                           layout3 );
            }
        }

    // Bitmaps must be validated (size is set) before they can be used.
    TAknLayoutRect layoutRect;

    TInt ii;

    // Layout group 1
    layoutRect.LayoutRect( rect, layout2 );
    for ( ii = EIndexCallstatusQgn_indi_call_active; ii <= ELayout1End; ii++ )
        {
        AknIconUtils::SetSize( iBitmaps->At(ii), layoutRect.Rect().Size() );
        }

    if ( iSmallCallIndication )
        {
        CFbsBitmap* bitmap = (CFbsBitmap*)iSmallCallIndication->Bitmap();
        if ( bitmap )
            {
            AknIconUtils::SetSize( bitmap, iSmallCallIndication->Rect().Size() );
            }
        }


    // Layout group 2
    layoutRect.LayoutRect( rect, layout1 );
    for ( ii = EIndexCallstatusQgn_graf_bubble_incall; ii < ELayout2End; ii++ )
        {
        AknIconUtils::SetSize( iBitmaps->At(ii), layoutRect.Rect().Size() );
        }

    if ( iBubble )
        {
        CFbsBitmap* bitmap = (CFbsBitmap*)iBubble->Bitmap();
        if ( bitmap )
            {
            AknIconUtils::SetSize( bitmap, iBubble->Rect().Size() );
            }
        }


    // Layout group 3
    layoutRect.LayoutRect( rect, layout3 );
    for ( ii = EIndexCallstatusQgn_indi_call_cyphering_off; ii <= ELayout3End; ii++ )
        {
        if ( hideTypeIndication )
            {
            // Not shown in landscape, because there's not enough space.
            AknIconUtils::SetSize( iBitmaps->At(ii), TSize(0,0) );
            }
        else
            {
            AknIconUtils::SetSize( iBitmaps->At(ii), layoutRect.Rect().Size() );
            }
        }

    if ( iCyphOffIcon )
        {
        CFbsBitmap* bitmap = (CFbsBitmap*)iCyphOffIcon->Bitmap();
        if ( bitmap )
            {
            if ( hideTypeIndication )
                {
                // Not shown in landscape, because there's not enough space.
                AknIconUtils::SetSize( bitmap, TSize(0,0) );
                }
            else
                {
                AknIconUtils::SetSize( bitmap, iCyphOffIcon->Rect().Size() );
                }
            }
        }


    // Layout group 4
    layoutRect.LayoutRect( callTypeIndicationRect, layout4 );
    for ( ii = EIndexCallstatusQgn_indi_call_data; ii <= ELayout4End; ii++ )
        {
        if ( hideTypeIndication )
            {
            // Not shown in landscape, because there's not enough space.
            AknIconUtils::SetSize( iBitmaps->At(ii), TSize(0,0) );
            }
        else
            {
            AknIconUtils::SetSize( iBitmaps->At(ii), layoutRect.Rect().Size() );
            }
        }

    if ( iTypeIndication1 )
        {
        CFbsBitmap* bitmap = (CFbsBitmap*)iTypeIndication1->Bitmap();
        if ( bitmap )
            {
            if ( hideTypeIndication )
                {
                // Not shown in landscape, because there's not enough space.
                AknIconUtils::SetSize( bitmap, TSize(0,0) );
                }
            else
                {
                AknIconUtils::SetSize(bitmap, iTypeIndication1->Rect().Size());
                }
            }
        }


    // Layout group 5
    layoutRect.LayoutRect( callTypeIndicationRect, layout5 );
    for ( ii = EIndexCallstatusQgn_indi_call_line2; ii <= ELayout5End; ii++ )
        {
        if ( hideTypeIndication )
            {
            // Not shown in landscape, because there's not enough space.
            AknIconUtils::SetSize( iBitmaps->At(ii), TSize(0,0) );
            }
        else
            {
            AknIconUtils::SetSize(iBitmaps->At(ii), layoutRect.Rect().Size());
            }
        }

    if ( iTypeIndication2 )
        {
        CFbsBitmap* bitmap = (CFbsBitmap*)iTypeIndication2->Bitmap();
        if ( bitmap )
            {
            if ( hideTypeIndication )
                {
                // Not shown in landscape, because there's not enough space.
                AknIconUtils::SetSize( bitmap, TSize(0,0) );
                }
            else
                {
                AknIconUtils::SetSize(bitmap, iTypeIndication2->Rect().Size());
                }
            }
        }

    Window().SetTransparencyAlphaChannel();
    Window().SetBackgroundColor( ~0 );

    // Update background of animation
    if ( iSmallIndiAnim && iBubble && iBubble->Bitmap() && iBubble->Mask() )
        TRAP_IGNORE( iSmallIndiAnim->CreateBackGroundImageL(
            iBubble->Bitmap(),
            iBubble->Mask(),
            TRect( iBubble->Position(), iBubble->Bitmap()->SizeInPixels() ) ) );

    // Make draw
    DrawDeferred();
    }

// ---------------------------------------------------------
// CIncallStatusBubble::CountComponentControls() const
//
//
// ---------------------------------------------------------
//
TInt CIncallStatusBubble::CountComponentControls() const
    {
    return 7; // bubble, small indi, anim , 2* type icons, cyph off and muted
    }

// ---------------------------------------------------------
// CIncallStatusBubble::ComponentControl(TInt aIndex) const
//
// ---------------------------------------------------------
//
CCoeControl* CIncallStatusBubble::ComponentControl(TInt aIndex) const
    {
    switch ( aIndex )
        {
        case 0:
            return iBubble;
        case 1:
            return iSmallCallIndication;
        case 2:
            return iTypeIndication1;
        case 3:
            return iTypeIndication2;
        case 4:
            return iCyphOffIcon;
        case 5:
            return iSmallIndiAnim;
        case 6:
            return iMutedIcon;
        default:
            return NULL;
        }
    }

// ---------------------------------------------------------
// CIncallStatusBubble::Draw
//
// ---------------------------------------------------------
//
void CIncallStatusBubble::Draw(const TRect& /*aRect*/) const
    {
    CWindowGc&  gc = SystemGc();
    gc.Clear();
    }

// ---------------------------------------------------------
// CIncallStatusBubble::SetFlags
//
// ---------------------------------------------------------
//
void CIncallStatusBubble::SetFlags( const TInt& aFlags )
    {
    iFlags = aFlags;
    SelectImages();
    SizeChanged();
    }

// ---------------------------------------------------------
// CIncallStatusBubble::Flags
// Two versions to eliminate compiler warnings
// ---------------------------------------------------------
//
#ifdef __WINS__
const TInt CIncallStatusBubble::Flags()
    {
    return iFlags;
    }
#else
TInt CIncallStatusBubble::Flags()
    {
    return iFlags;
    }
#endif

// ---------------------------------------------------------
// CIncallStatusBubble::SetFaded
//
// ---------------------------------------------------------
//
void CIncallStatusBubble::SetFaded(TBool aFaded)
    {
    if (!COMPARE_BOOLS(Window().IsFaded(), aFaded))
        {
        iMyWindowGroup.SetFaded(
            aFaded, RWindowTreeNode::EFadeIncludeChildren);
        }
    }

// ---------------------------------------------------------
// CIncallStatusBubble::SelectImages
//
// ---------------------------------------------------------
//
void CIncallStatusBubble::SelectImages()
    {
    if ( ! ( iFlags & ESBVisible ) )
        {
        iSmallCallIndication->MakeVisible( EFalse );
        iBubble->MakeVisible( EFalse );
        iSmallIndiAnim->MakeVisible( EFalse );
        iTypeIndication1->MakeVisible( EFalse );
        iTypeIndication2->MakeVisible( EFalse );
        iCyphOffIcon->MakeVisible( EFalse );
        iMutedIcon->MakeVisible( EFalse );
        return;
        }

    TRect rect( Rect() );

    // first set call indication and bubble image
    TInt indiBitmap = KErrNotFound;
    TInt indiMask = KErrNotFound;
    iSmallIndiAnim->MakeVisible( EFalse );


    GetImage(
        *iBubble,
        EIndexCallstatusQgn_graf_bubble_incall,
        EIndexCallstatusQgn_graf_bubble_incall_mask );
    iBubble->MakeVisible( ETrue );

    switch ( iFlags & (ESBAlerting|ESBActive|ESBOnHold|ESBDisconnected ) ) // two last bits
        {
        case ESBAlerting:
        case ESBActive:
            if ( iFlags & ESBVoIPCall &&
                FeatureManager::FeatureSupported( KFeatureIdCommonVoip ) )
                {
                indiBitmap = EIndexCallStatusQgn_indi_call_voip_active;
                indiMask = EIndexCallStatusQgn_indi_call_voip_active_mask;
                }

            else if ( iFlags & ESBVideo )
                {
                indiBitmap = EIndexCallstatusQgn_indi_call_video_callsta_1;
                indiMask = EIndexCallstatusQgn_indi_call_video_callsta_1_mask;
                }

            else
                {
                indiBitmap = EIndexCallstatusQgn_indi_call_active;
                indiMask = EIndexCallstatusQgn_indi_call_active_mask;
                }
            break;
        case ESBOnHold:
            if ( iFlags & ESBVoIPCall &&
                FeatureManager::FeatureSupported( KFeatureIdCommonVoip ) )
                {
                indiBitmap = EIndexCallStatusQgn_indi_call_voip_held;
                indiMask = EIndexCallStatusQgn_indi_call_voip_held_mask;
                }
            else
                {
                indiBitmap = EIndexCallstatusQgn_indi_call_held;
                indiMask = EIndexCallstatusQgn_indi_call_held_mask;
                }
            break;
        case ESBDisconnected:
            if ( iFlags & ESBVoIPCall &&
                FeatureManager::FeatureSupported( KFeatureIdCommonVoip ) )
                {
                indiBitmap = EIndexCallStatusQgn_indi_call_voip_disconn;
                indiMask = EIndexCallStatusQgn_indi_call_voip_disconn_mask;
                }

            else if ( iFlags & ESBVideo )
                {
                indiBitmap = EIndexCallstatusQgn_indi_call_video_disconn;
                indiMask = EIndexCallstatusQgn_indi_call_video_disconn_mask;
                }

            else
                {
                indiBitmap = EIndexCallstatusQgn_indi_call_disconn;
                indiMask = EIndexCallstatusQgn_indi_call_disconn_mask;
                }

            GetImage(
                *iBubble,
                EIndexCallstatusQgn_graf_bubble_incall_disconn,
                EIndexCallstatusQgn_graf_bubble_incall_disconn_mask );
            break;
        default:
            _LIT(KCallStatus,"CallStatus");
            User::Panic(KCallStatus , 0 );
            break;
        }

    // Cyph off
    if ( iFlags & ESBNoCiphering )
        {
        GetImage(
            *iCyphOffIcon,
            EIndexCallstatusQgn_indi_call_cyphering_off );
        iCyphOffIcon->MakeVisible( ETrue );
        }
    else
        {
        iCyphOffIcon->MakeVisible( EFalse );
        }

    // Muted icon
    if ( iFlags & ESBMuted )
        {
        iMutedIcon->MakeVisible( ETrue );
        }
    else
        {
        iMutedIcon->MakeVisible( EFalse );
        }

    // Animation
    if ( (iFlags & (ESBAlerting|ESBActive|ESBOnHold|ESBDisconnected )) == ESBAlerting )
        {
        if ( iFlags & ESBVoIPCall &&
            FeatureManager::FeatureSupported( KFeatureIdCommonVoip ))
            {
            iSmallIndiAnim->SetAnimationType( CIncallAnim::EVoipCallAnim );  // We have VoIP call.
            }
        else if (iFlags & ESBVideo)
            {
            iSmallIndiAnim->SetAnimationType( CIncallAnim::EVideoCallAnim );  // We have Video call.
            }
        else
            {
            iSmallIndiAnim->SetAnimationType( CIncallAnim::EDefaultCallAnim ); // We have normal CS call.
            }

        iSmallIndiAnim->MakeVisible( ETrue );
        }
    else
        {
        iSmallIndiAnim->MakeVisible( EFalse );
        }


    // Emergency call
    if ( (iFlags & (ESBAlerting|ESBActive|ESBOnHold|ESBDisconnected )) == ESBActive &&
         (iFlags & ESBEmergency) )
        {
        indiBitmap = EIndexCallstatusQgn_indi_call_active_emergency;
        indiMask = EIndexCallstatusQgn_indi_call_active_emergency_mask;
        }


    if ( indiBitmap != KErrNotFound )
        {
        GetImage(
            *iSmallCallIndication,
            indiBitmap ,
            indiMask );

        iSmallCallIndication->MakeVisible( ETrue );
        }



    // set type pane
    TInt picture1 = KErrNotFound;
    TInt picture2 = KErrNotFound;

    TInt mask1 = KErrNotFound;

    if ( iFlags & ESBFax )
        {
        picture1 = EIndexCallstatusQgn_indi_call_fax;
        }
    else if ( iFlags & ESBDataHscsd )
        {
        picture1 = EIndexCallstatusQgn_indi_call_data_hscsd;
        }
    else if ( iFlags & ESBData )
        {
        picture1 = EIndexCallstatusQgn_indi_call_data;
        }
    else if ( iFlags & ESBVideo )
        {
        // type pane is used for video call, it should not be need to use other
        // other types with video call
        picture1 = EIndexCallstatusQgn_indi_call_video_callsta;
        mask1 = EIndexCallstatusQgn_indi_call_video_callsta_mask;
        }

    if ( iFlags & ESBLine2 )
        {
        if ( picture1 == KErrNotFound )
            {
            picture1 = EIndexCallstatusQgn_indi_call_line2;
            }
        else
            {
            picture2 = EIndexCallstatusQgn_indi_call_line2;
            }
        }

    if ( picture1 != KErrNotFound )
        {
        TBool isLandscape( Layout_Meta_Data::IsLandscapeOrientation() );

        GetImage(
            *iTypeIndication1,
            picture1,
            mask1);

        if ( iFlags & ESBVideo )
            {
            // video indicator is different size than others
            AknLayoutUtils::LayoutControl(
                iTypeIndication1,
                rect,
                AknLayoutScalable_Apps::popup_call_status_window_g2(
                    isLandscape ).LayoutLine() );

            // muted icon is never shown with video call
            iMutedIcon->MakeVisible( EFalse );

            // line2 indication never shown with video call
            picture2 = KErrNotFound;
            }
        else
            {
            if ( isLandscape )
                {
                // Not shown in landscape.
                iTypeIndication1->SetRect( TRect( 0, 0, 0, 0 ) );
                }
            else
                {
                TAknLayoutRect callTypeIndicationRect;
                callTypeIndicationRect.LayoutRect(
                    rect,
                    AknLayoutScalable_Apps::call_type_pane() );
                AknLayoutUtils::LayoutControl(
                    iTypeIndication1,
                    callTypeIndicationRect.Rect(),
                    AknLayoutScalable_Apps::call_type_pane_g1().LayoutLine() );
                }
            }

        // "Video hold" does not have its own graphics, so we show it differently for now.
        if ( iFlags & ESBVideo &&
           ((iFlags & ( ESBAlerting | ESBActive | ESBOnHold | ESBDisconnected )) != ESBOnHold))
            {
            iTypeIndication1->MakeVisible( EFalse );
            }
        else
            {
            iTypeIndication1->MakeVisible( ETrue );
            }


        if ( picture2 != KErrNotFound )
            {
            GetImage( *iTypeIndication2,
                      picture2 );
            iTypeIndication2->MakeVisible( ETrue );

            }
        else
            {
            iTypeIndication2->MakeVisible( EFalse );
            }

        }
    else
        {
        iTypeIndication1->MakeVisible( EFalse );
        iTypeIndication2->MakeVisible( EFalse );
        }
    }

// ---------------------------------------------------------
// CIncallStatusBubble::SetRect
//
// ---------------------------------------------------------
//
void CIncallStatusBubble::SetRect( const TRect& aRect )
    {
    CCoeControl::SetRect( aRect );
    }

// ---------------------------------------------------------
// CIncallStatusBubble::MapEnumToSkin
//
// ---------------------------------------------------------
//
void CIncallStatusBubble::MapEnumToSkin(
    const TInt aBmIcon, TAknsItemID& aID )
    {
    switch ( aBmIcon )
        {
        // Skinned bitmap:
        case EIndexCallstatusQgn_indi_call_active:
            aID = KAknsIIDQgnIndiCallActive;
            break;
        case EIndexCallstatusQgn_indi_call_disconn:
            aID = KAknsIIDQgnIndiCallDisconn;
            break;
        case EIndexCallstatusQgn_indi_call_held:
            aID = KAknsIIDQgnIndiCallHeld;
            break;
        case EIndexCallstatusQgn_indi_call_active_2:
            aID = KAknsIIDQgnIndiCallActive2;
            break;
        case EIndexCallstatusQgn_indi_call_muted_callsta:
            aID = KAknsIIDQgnIndiCallMutedCallsta;
            break;
        case EIndexCallstatusQgn_graf_bubble_incall:
            aID = KAknsIIDQgnGrafBubbleIncall;
            break;
        case EIndexCallstatusQgn_graf_bubble_incall_disconn:
            aID = KAknsIIDQgnGrafBubbleIncallDisconn;
            break;
        case EIndexCallStatusQgn_indi_call_voip_active:
            aID = KAknsIIDQgnIndiCallVoipActive;
            break;
        case EIndexCallStatusQgn_indi_call_voip_active_2:
            aID = KAknsIIDQgnIndiCallVoipActive2;
            break;
        case EIndexCallStatusQgn_indi_call_voip_disconn:
            aID = KAknsIIDQgnIndiCallVoipDisconn;
            break;
        case EIndexCallStatusQgn_indi_call_voip_held:
            aID = KAknsIIDQgnIndiCallVoipHeld;
            break;
        case EIndexCallstatusQgn_indi_call_video_callsta:
            aID = KAknsIIDQgnIndiCallVideoCallsta;
            break;
        case EIndexCallstatusQgn_indi_call_video_callsta_1:
            aID = KAknsIIDQgnIndiCallVideoCallsta1;
            break;
        case EIndexCallstatusQgn_indi_call_video_callsta_2:
            aID = KAknsIIDQgnIndiCallVideoCallsta2;
            break;
        case EIndexCallstatusQgn_indi_call_video_disconn:
            aID = KAknsIIDQgnIndiCallVideoCallstaDisconn;
            break;

        // Colour change:
        case EIndexCallstatusQgn_indi_call_data:
        case EIndexCallstatusQgn_indi_call_data_hscsd:
        case EIndexCallstatusQgn_indi_call_fax:
        case EIndexCallstatusQgn_indi_call_line2:
        case EIndexCallstatusQgn_indi_call_cyphering_off:
            aID = KAknsIIDQsnTextColors;
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------
// CIncallStatusBubble::GetSkinForIcon
//
// ---------------------------------------------------------
//
CAknsItemData* CIncallStatusBubble::GetSkinForIcon(
    const TInt aBmIcon )
    {
    CAknsItemData* data = NULL;

    TAknsItemID skinId = KAknsIIDNone;
    MapEnumToSkin( aBmIcon, skinId );
    if ( skinId == KAknsIIDNone )
        {
        return NULL;
        }

    SSkinnedImage skinnedImage;
    skinnedImage.iId = skinId;

    TInt index = iSkins.FindInOrder( &skinnedImage, iOrder );
    if ( index != KErrNotFound )
        {
        data = iSkins[ index ]->iItemData;
        }
    else
        {
        TRAP_IGNORE( data = LoadAndAppendSkinL( skinId ) );
        }
    return data;
    }

// ---------------------------------------------------------
// CIncallStatusBubble::LoadAndAppendSkinL
//
// ---------------------------------------------------------
//
CAknsItemData* CIncallStatusBubble::LoadAndAppendSkinL(
    const TAknsItemID& aId )
    {
    SSkinnedImage* newImage = new(ELeave) SSkinnedImage;
    CleanupStack::PushL( newImage );

    newImage->iId = aId;
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    newImage->iItemData = skin->CreateUncachedItemDataL( aId );

    User::LeaveIfError( iSkins.InsertInOrder( newImage, iOrder ) );
    CleanupStack::Pop( newImage ); // Ownership was given to iSkins array

    return newImage->iItemData;
    }

// ---------------------------------------------------------------------------
// CIncallStatusBubble::GetSkin
// ---------------------------------------------------------------------------
//
TBool CIncallStatusBubble::GetSkin( CEikImage& aImage, const TInt aBmIcon )
    {
    CAknsItemData* data    = GetSkinForIcon( aBmIcon );

    CFbsBitmap* bitmap     = NULL;
    CFbsBitmap* bitmapMask = NULL;

    if ( data )
        {
        switch ( data->Type() )
            {
            case EAknsITMaskedBitmap:
                {
                CAknsMaskedBitmapItemData* maskedBitmapData =
                    static_cast< CAknsMaskedBitmapItemData* >( data );
                bitmapMask = maskedBitmapData->Mask();
                }
                // Flow through
            case EAknsITBitmap:
                {
                CAknsBitmapItemData* bitmapData =
                    static_cast< CAknsBitmapItemData* >( data );
                bitmap = bitmapData->Bitmap();
                }
                break;
            case EAknsITColorTable:
                {
                // If the color for call bubble texts is not defined in the
                // current skin, use gray.
                TRgb colour( KRgbGray );
                MAknsSkinInstance* skin = AknsUtils::SkinInstance();
                AknsUtils::GetCachedColor(
                    skin,
                    colour,
                    KAknsIIDQsnTextColors,
                    EAknsCIQsnTextColorsCG51 );

                // Load the coloured bitmap if not already loaded.
                if ( !iSkinnedColourBitmap )
                    {
                    // Color bitmaps are not anymore supported by scalable
                    // skin server, we create our own color bitmap here.
                    TRAP_IGNORE( iSkinnedColourBitmap = CreateSkinnedColourBitmapL() );
                    }
                // If found, use the full colour bitmap as the image and
                // use the "real" bitmap" as the mask.
                if ( iSkinnedColourBitmap )
                    {
                    bitmap     = iSkinnedColourBitmap;
                    bitmapMask = iBitmaps->At( aBmIcon );
                    }
                }

            default:
                {
                break;
                }
            }
        }

    if ( bitmap )
        {
        aImage.SetBitmap( bitmap );
        aImage.SetMask( bitmapMask ); // Might be NULL
        return ETrue;
        }

    return EFalse;
    }

// ---------------------------------------------------------
// CIncallStatusBubble::CompareSkinnedData
//
// ---------------------------------------------------------
//
TInt CIncallStatusBubble::CompareSkinnedData(
    const SSkinnedImage& aSkin1, const SSkinnedImage& aSkin2 )
    {
    return aSkin1.iId.iMinor-aSkin2.iId.iMinor ?
        aSkin1.iId.iMinor-aSkin2.iId.iMinor :
        aSkin1.iId.iMajor-aSkin2.iId.iMajor;
    }

// ---------------------------------------------------------
// CIncallStatusBubble::LoadImageL
//
// ---------------------------------------------------------
//
void CIncallStatusBubble::LoadImageL( TInt aBitmapId )
    {
    CFbsBitmap* bitmap;
    CFbsBitmap* mask;

    CCleanupGuard* guard = new( ELeave ) CCleanupGuard;
    CleanupStack::PushL( guard );

    AknIconUtils::CreateIconL(
        bitmap, mask, KCallStatusBitmapFile, aBitmapId, aBitmapId ); // use bitmap id for both mask and bitmap because of 1-bit icons

    guard->SetItem1( bitmap );
    guard->SetItem2( mask );

    iBitmaps->AppendL( mask );
    guard->SetItem2( NULL ); // mask
    iBitmaps->AppendL( bitmap );
    guard->SetItem1( NULL ); // bitmap

    CleanupStack::PopAndDestroy(); // guard

    }

// ---------------------------------------------------------
// CIncallStatusBubble::LoadImageL
//
// ---------------------------------------------------------
//
void CIncallStatusBubble::LoadImageL( TInt aBitmapId, TInt aMaskId )
    {
    CFbsBitmap* bitmap;
    CFbsBitmap* mask;

    CCleanupGuard* guard = new( ELeave ) CCleanupGuard;
    CleanupStack::PushL( guard );

    AknIconUtils::CreateIconL(
        bitmap, mask, KCallStatusBitmapFile, aBitmapId, aMaskId );

    guard->SetItem1( bitmap );
    guard->SetItem2( mask );

    iBitmaps->AppendL( bitmap );
    guard->SetItem1( NULL ); // bitmap
    iBitmaps->AppendL( mask );
    guard->SetItem2( NULL ); // mask

    CleanupStack::PopAndDestroy(); // guard
    }

// ---------------------------------------------------------
// CIncallStatusBubble::GetImage
//
// ---------------------------------------------------------
//
void CIncallStatusBubble::GetImage(
    CEikImage& aImage,
    const TInt& aImageId,
    const TInt aImageMaskId )
    {
    if ( GetSkin( aImage, aImageId ) )
        {
        return;
        }

    aImage.SetBitmap( iBitmaps->At( aImageId ) );
    if ( aImageMaskId != KErrNotFound )
        {
        aImage.SetMask( iBitmaps->At( aImageMaskId ) );
        }
    }

// ---------------------------------------------------------
// CIncallStatusBubble::HandleResourceChange
//
// ---------------------------------------------------------
//
void CIncallStatusBubble::HandleResourceChange( TInt aType )
    {
    if ( aType == KAknsMessageSkinChange ||
         aType == KEikDynamicLayoutVariantSwitch )
        {
        // Clear all handles
        iSmallCallIndication->SetPicture( NULL );
        iBubble->SetPicture( NULL );
        iTypeIndication1->SetPicture( NULL );
        iTypeIndication2->SetPicture( NULL );
        iCyphOffIcon->SetPicture( NULL );
        
        iMutedIcon->SetMutedImage( NULL, NULL );

        iSmallIndiAnim->MakeVisible( EFalse );
        iSmallIndiAnim->ClearAnimation();

        // Delete old skins
        iSkins.ResetAndDestroy();
        delete iSkinnedColourBitmap;
        iSkinnedColourBitmap = NULL;

        // Update muted icon
        CEikImage* tmpMutedImage = new CEikImage;
        if ( tmpMutedImage )
            {
            tmpMutedImage->SetPictureOwnedExternally( ETrue );
            GetImage(
                *tmpMutedImage,
                EIndexCallstatusQgn_indi_call_muted_callsta,
                EIndexCallstatusQgn_indi_call_muted_callsta_mask
                );
            iMutedIcon->SetMutedImage(
                tmpMutedImage->Bitmap(), tmpMutedImage->Mask() );
            delete tmpMutedImage;
            }

        // Update animation
        TInt err = KErrNone;
        if ( iFlags & ESBVoIPCall &&
            FeatureManager::FeatureSupported( KFeatureIdCommonVoip ) )
            {
            TRAP( err, iSmallIndiAnim->SetAnimationL( *this, CIncallAnim::EVoipCallAnim ) );
            }
        else if (iFlags & ESBVideo)
            {
            TRAP( err, iSmallIndiAnim->SetAnimationL( *this, CIncallAnim::EVideoCallAnim ) );
            }
        else
            {
            TRAP( err, iSmallIndiAnim->SetAnimationL( *this, CIncallAnim::EDefaultCallAnim ) );
            }

        if ( err )
            {
            iSmallIndiAnim->ClearAnimation();
            }

        // Get the other items:
        SelectImages();
        SizeChanged();
        return;
        }

    CCoeControl::HandleResourceChange(aType);
    }


// ----------------------------------------------------------------------------
// CIncallStatusBubble::HandlePointerEventL
// ----------------------------------------------------------------------------
//
void CIncallStatusBubble::HandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    // the tap event shall be igored when the keyboard is locked
    TInt autolockState = EAutolockOff;
    RProperty::Get( KPSUidCoreApplicationUIs, KCoreAppUIsAutolockStatus, autolockState );
    TPoint pdOffset( 3, 3 );  // Move icon to a little for "pressed" effect
     if ( !Window().IsFaded() && 
          AknLayoutUtils::PenEnabled() && 
          autolockState <= EAutolockOff ) 
         { 
         if ( ( aPointerEvent.iType == TPointerEvent::EButton1Down || 
                aPointerEvent.iType == TPointerEvent::EDrag ) && 
              Rect().Contains( aPointerEvent.iPosition ) ) 
             { 
             // Draw  down effects. 
             if ( ! iPressedDown ) 
                 { 
                 GetImage(
                     *iBubble,
                     EIndexCallstatusQgn_graf_bubble_incall_disconn,
                     EIndexCallstatusQgn_graf_bubble_incall_disconn_mask );

                 TRect newRect = Rect();

                 newRect.Move( PositionRelativeToScreen() + pdOffset );

                 SetRect( newRect );

                 iPressedDown = ! iPressedDown; 
                 } 
             } 
         else if ( aPointerEvent.iType == TPointerEvent::EDrag || 
                   aPointerEvent.iType == TPointerEvent::EButton1Up ) 
             { 
             // Clear pressed down effects. 
               if ( iPressedDown ) 
                   { 
                 GetImage(
                     *iBubble,
                     EIndexCallstatusQgn_graf_bubble_incall,
                     EIndexCallstatusQgn_graf_bubble_incall_mask );

                 TRect newRect = Rect();

                 newRect.Move( PositionRelativeToScreen() - pdOffset );

                 SetRect( newRect );

                   iPressedDown = !iPressedDown; 
                   } 
               
               if ( aPointerEvent.iType == TPointerEvent::EButton1Up && 
                    Rect().Contains( aPointerEvent.iPosition ) ) 
                   { 
                   
                   CCoeEnv* coeEnv = CCoeEnv::Static();
                   CCoeAppUi* appUi = NULL;
                   if ( coeEnv )
                       {
                       appUi = coeEnv->AppUi();
                       }
                   
                   if ( appUi )
                       {
                       if ( ( iFlags & ESBVideo ) && ( iFlags & ESBActive ) )
                           {
                           TVwsViewId viewId( KVideoCallUid, KVideoCallUid );
                           appUi->CreateActivateViewEventL(viewId, KNullUid, KNullDesC8());
                           }
                       else
                           {
                           TVwsViewId diallerView( KPhoneAppUid, KPhoneViewUid );
                           appUi->CreateActivateViewEventL( diallerView,  KPhoneVievCommand, KNullDesC8() );
                           }
                       }
                   }
             }
        }
    else if (aPointerEvent.iType == TPointerEvent::EButton1Up)
        {
        CEikMenuBar* menuBar = CEikonEnv::Static()->AppUiFactory()->MenuBar();            
        if( menuBar && menuBar->IsVisible() )
            {
            //Stops displaying the uifactory's menu bar.
            menuBar->StopDisplayingMenuBar();  
            }
        else
            {
            //Stops displaying the application's menu bar.
            CEikonEnv::Static()->EikAppUi()->StopDisplayingMenuBar();
            }
        }
    }

CFbsBitmap* CIncallStatusBubble::CreateSkinnedColourBitmapL()
    {
    TSize size( Rect().Size() );
    if ( size == TSize( 0, 0 ) )
    {
        return NULL;
    }

    TRgb colour( KRgbGray );
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    AknsUtils::GetCachedColor(
        skin,
        colour,
        KAknsIIDQsnTextColors,
        EAknsCIQsnTextColorsCG51 );

    CFbsBitmap* destinationBitmap = new (ELeave) CFbsBitmap();
    CleanupStack::PushL( destinationBitmap );
    User::LeaveIfNull( destinationBitmap );

    User::LeaveIfError( destinationBitmap->Create( size, EColor16M ) );

    CFbsBitmapDevice* destinationDevice = CFbsBitmapDevice::NewL( destinationBitmap );
    CleanupStack::PushL( destinationDevice );

    CFbsBitGc* destinationGc;
    User::LeaveIfError( destinationDevice->CreateContext( destinationGc ) );

    destinationGc->SetPenColor( colour );
    destinationGc->SetPenStyle( CGraphicsContext::ESolidPen );
    destinationGc->SetBrushColor( colour );
    destinationGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    destinationGc->DrawRect( TRect( size ) );

    delete destinationGc;
    CleanupStack::PopAndDestroy( destinationDevice );
    CleanupStack::Pop( destinationBitmap );

    return destinationBitmap;
    }

// End of File
