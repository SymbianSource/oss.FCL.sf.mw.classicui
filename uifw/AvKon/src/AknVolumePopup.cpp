/*
* Copyright (c) 2004-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Popup Volume indicator
*
*/



// INCLUDE FILES
#include "AknVolumePopup.h"
#include <apgwgnam.h>
#include <eiklabel.h>
#include <StringLoader.h>
#include <barsread.h>
#include <Aknvolumecontrol.h>
#include <AknUtils.h>
#include <AknsDrawUtils.h>
#include <aknconsts.h>
#include <aknappui.h>
#include <aknslider.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <aknlayoutscalable_apps.cdl.h>
#include <layoutmetadata.cdl.h>
#include <skinlayout.cdl.h>
#include <avkon.mbg>
#include <aknbutton.h>
#include <e32math.h>
#include <AknPanic.h>
#include <gulicon.h>
#include <AknsFrameBackgroundControlContext.h>
#include <AknWsEventObserver.h>
#include <AknStatuspaneUtils.h>

#include <touchfeedback.h>
#include <AknTasHook.h>
const TInt KSliderUsed = 0xffff;
const TInt KScrollRepeatTimeout = 250000; // 0.25 seconds
const TReal KWidthSpace = 1.3;
// ============================ MEMBER FUNCTIONS =============================

// ============================================================================
NONSHARABLE_CLASS( CAknVolumePopupExtension ): public CBase,
                                               public MAknWsEventObserver
    {
public:

private:
    CAknVolumePopupExtension();
    void ConstructL();

public:
    ~CAknVolumePopupExtension();
    static CAknVolumePopupExtension* NewL();
    CAknControl* VolumeControl();

    void SetGraphics( TInt aElement, 
                      CFbsBitmap* aBitmap, 
                      CFbsBitmap* aMask );
                  
    void TryLoadDefaultSliderVolumeBitmap();               
    void TryLoadDefaultHorizontalVolumeBitmap(); 
    
    // from MAknWsEventObserver
    void HandleWsEventL(const TWsEvent& aEvent,CCoeControl* aDestination);
public:
    CAknVolumeControl*  iOldVolumeControl;
    CAknSlider*         iSliderControl;
    TSize iMarkerSize;
    CAknsFrameBackgroundControlContext* iBgContext;
    TBool iUseMutedIcon;
    TBool iSpeakerHidden;
    TInt iSliderUsed;
    
    CAknVolumePopup* iParent;
    TBool iClosePopupWhenTapped;
    TBool iHaveDefaultValue;
    TInt iDefaultValue;
    TBool iResetDefaultValue;
    TBool iInitialized;
    TBool iHandlingPointerEvent;
    TBool iWindowGroupCreated;
private:

    TBitFlags32 iFlags;
    };
    
// ----------------------------------------------------------------------------
// CAknVolumePopupExtension::CAknVolumePopupExtension
// ----------------------------------------------------------------------------
//
CAknVolumePopupExtension::CAknVolumePopupExtension()
    : iUseMutedIcon(ETrue),
      iClosePopupWhenTapped(ETrue),
      iHaveDefaultValue(EFalse), 
      iDefaultValue(-1),
      iResetDefaultValue(ETrue)
    {
    }
    
// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
//
CAknVolumePopupExtension::~CAknVolumePopupExtension()
    {
    delete iSliderControl;
    delete iOldVolumeControl;
    delete iBgContext;
    }

// ----------------------------------------------------------------------------
// CAknVolumePopupExtension::NewL
// ----------------------------------------------------------------------------
//
CAknVolumePopupExtension* CAknVolumePopupExtension::NewL()
    {
    
    CAknVolumePopupExtension* self = new( ELeave ) CAknVolumePopupExtension();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// CAknVolumePopupExtension::ConstructL
// ----------------------------------------------------------------------------
//
void CAknVolumePopupExtension::ConstructL()
    {
    }
// ----------------------------------------------------------------------------
// CAknVolumePopupExtension::VolumeControl
// ----------------------------------------------------------------------------
// 
CAknControl* CAknVolumePopupExtension::VolumeControl()
        {
        if( iSliderUsed == KSliderUsed )
            {
            return iSliderControl;
            }
        return iOldVolumeControl;
        } 
// ----------------------------------------------------------------------------
// CAknVolumePopupExtension::SetGraphics
// ----------------------------------------------------------------------------
//
void CAknVolumePopupExtension::SetGraphics( TInt aElement, 
                                       CFbsBitmap* aBitmap, 
                                       CFbsBitmap* aMask )
    {
    // element index is assumed to be valid (no checking)

    if( aElement >= CAknSlider::EElemEmptyLeftCap && 
        aElement <= CAknSlider::EElemMarkerSelected )
        {
        iSliderControl->SetGraphics( aElement , aBitmap, aMask );
        }
    }
  
// ----------------------------------------------------------------------------
// CAknVolumePopupExtension::TryLoadDefaultSliderVolumeBitmap
//
// ----------------------------------------------------------------------------
//     
void CAknVolumePopupExtension::TryLoadDefaultSliderVolumeBitmap()
    {
    iSliderControl->SetGraphics( CAknSlider::EElemTickMark, NULL, NULL );
    }                         
// ----------------------------------------------------------------------------
// CAknVolumePopupExtension::TryLoadDefaultHorizontalVolumeBitmap
//
// ----------------------------------------------------------------------------
//     
void CAknVolumePopupExtension::TryLoadDefaultHorizontalVolumeBitmap()
    {
    const TInt iconIDArray[] = 
        {
        EMbmAvkonQgn_graf_volume_small_off,        
        EMbmAvkonQgn_graf_volume_small_on,
        EMbmAvkonQgn_graf_nslider_marker,
        EMbmAvkonQgn_graf_nslider_marker_selected
        };
    const TInt iconMaskIDArray[] = 
        {
        EMbmAvkonQgn_graf_volume_small_off_mask,        
        EMbmAvkonQgn_graf_volume_small_on_mask,
        EMbmAvkonQgn_graf_nslider_marker_mask,
        EMbmAvkonQgn_graf_nslider_marker_selected_mask
        }; 
    const TAknsItemID iconSkinIDArray[] = 
        {
        KAknsIIDQgnGrafVolumeSmallOff,        
        KAknsIIDQgnGrafVolumeSmallOn,
        KAknsIIDQgnGrafNsliderMarker,
        KAknsIIDQgnGrafNsliderMarkerSelected
        };
        
    const TInt element[] = 
        {
        CAknSlider::EElemEmptyLine,
        CAknSlider::EElemFilledLine,
        CAknSlider::EElemMarker,
        CAknSlider::EElemMarkerSelected
        };
    TInt count = sizeof( iconIDArray )/sizeof(TInt);
    
    TInt err = KErrNone;
    CFbsBitmap* bitmapPtr = NULL;
    CFbsBitmap* maskPtr = NULL;    
    for ( TInt i = 0; i < count; i++ )
        {
        //find new graphic from Skinned bitmap
        TRAP(err, AknsUtils::CreateIconL( AknsUtils::SkinInstance(),
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
            iSliderControl->SetGraphics( element[i], bitmapPtr, maskPtr );
            }          
        }
    }   
    
// ----------------------------------------------------------------------------
// CAknVolumePopupExtension::HandleWsEventL
// ----------------------------------------------------------------------------
//    
void CAknVolumePopupExtension::HandleWsEventL(const TWsEvent& aEvent,CCoeControl* aDestination)
    {
    if( aEvent.Type() == EEventPointer )
        {
        // Touch outside of volume popup, close volume popup
        if( iClosePopupWhenTapped && 
            aEvent.Pointer()->iType == TPointerEvent::EButton1Down &&
            aDestination != iParent )
            {
            MTouchFeedback* feedback = MTouchFeedback::Instance();
            if ( feedback )
                {
                feedback->InstantFeedback( ETouchFeedbackPopUp );
                }
            iParent->CloseVolumePopup();
            }
        }
    }
    
// ---------------------------------------------------------------------------
// CAknVolumePopup::CAknVolumePopup
//
//
// ---------------------------------------------------------------------------
//
CAknVolumePopup::CAknVolumePopup(TInt aFlags):
    iFlags(aFlags),
    iAdjustmentIndicatorOn(ETrue),
    iVertical(EFalse),
    iTimeout(0)
    {
    }


// ---------------------------------------------------------------------------
// CAknVolumePopup::ConstructFromResourceL
// 
// ---------------------------------------------------------------------------
//
EXPORT_C CAknVolumePopup* CAknVolumePopup::ConstructFromResourceL(
                                                           TInt aResourceId )
    {
    // create volume control
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC( reader, aResourceId );

    TInt flags = -1;
    TInt sliderType = reader.ReadInt16();
    if ( sliderType == EAknSliderWithFeedbackStyle )
        {
        TInt feedbackStyle = (TAknFeedbackStyle)reader.ReadInt16();
        flags = reader.ReadInt16();
        }
    else
        {
        flags = sliderType;
        }
    if( flags == -1) // 0xffff
        {
        flags = reader.ReadInt16();
        }        

    if( flags == ENaviPaneVolumeControl ||
        flags == EDynRangeNaviPaneVolumeControl ) 
        {
        CAknVolumePopup* self = new( ELeave ) CAknVolumePopup( KSliderUsed );
        CleanupStack::PopAndDestroy(); // reader
        CleanupStack::PushL( self );
        self->ConstructL( NULL, EFalse, aResourceId );
        CleanupStack::Pop();
        return self;   
        }
    else
        {
    	CAknVolumePopup* self = new( ELeave ) CAknVolumePopup(0);
    	CleanupStack::PopAndDestroy(); // reader
        CleanupStack::PushL( self );
        self->ConstructL( NULL, EFalse, aResourceId );
        CleanupStack::Pop();
        return self;    
        }
    }
    
// ---------------------------------------------------------------------------
// CAknVolumePopup::NewL
//
// ---------------------------------------------------------------------------
//
EXPORT_C CAknVolumePopup* CAknVolumePopup::NewL( CCoeControl* aParent,
                                                     TBool aIsVertical )
    {
    CAknVolumePopup* self = new( ELeave ) CAknVolumePopup(KSliderUsed);
    CleanupStack::PushL( self );
    
    if( aIsVertical )
        {
        self->ConstructL( aParent, ETrue, R_AVKON_VERTICAL_POPUP_SLIDER );
        }
    else
        {
        self->ConstructL( aParent, aIsVertical, R_AVKON_HORIZONTAL_POPUP_SLIDER );
        }
    CleanupStack::Pop();
    AKNTASHOOK_ADDL( self, "CAknVolumePopup" );
    return self;    
    }

// ---------------------------------------------------------------------------
// CAknVolumePopup::ConstructL
// Symbian 2nd phase constructor can leave.
// ---------------------------------------------------------------------------
//
void CAknVolumePopup::ConstructL( CCoeControl* aParent, 
                                  TBool aIsVertical, 
                                  TInt aResourceId )
    {
    iExt = CAknVolumePopupExtension::NewL();
    iVertical = aIsVertical;
    iExt->iSliderUsed = iFlags;
    iExt->iParent = this;
   // create inactivity timer
    iTimer = CPeriodic::NewL(CActive::EPriorityStandard);
    
    // create volume control
    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC( reader, aResourceId );
    TInt sliderType = reader.ReadInt16();
    if ( sliderType == EAknSliderWithFeedbackStyle )
        {
        TInt feedbackStyle = (TAknFeedbackStyle)reader.ReadInt16();
        iFlags = reader.ReadInt16();
        }
    else
        {
        iFlags = sliderType;
        }
    
    if( iFlags == -1) // 0xffff
        {
        iFlags = reader.ReadInt16();
        reader.Rewind( 2 );
        }
        
    reader.Rewind( 2 );

    if ( iFlags == EPopupVolumeControl )
        {
         //use the new style popup volume control
        iFlags = ESmallPopupVolumeControl;
        }

    if( !aParent && (iFlags == ENaviPaneVolumeControl ||
         iFlags == EDynRangeNaviPaneVolumeControl ))
        {
        CreateWindowL();
        DrawableWindow()->SetOrdinalPosition(0, ECoeWinPriorityNeverAtFront);
        }
    else if( !aParent )
        {
        // create a window group for volume popup
        // needed to prevent apps noticing this window
        RWsSession& wsSession = iCoeEnv->WsSession();
        iWindowGroup = RWindowGroup( wsSession );
        User::LeaveIfError( iWindowGroup.Construct( (TUint32) &iWindowGroup, EFalse ) );
        iWindowGroup.AutoForeground(EFalse);

        CApaWindowGroupName* name = CApaWindowGroupName::NewLC( wsSession,
                                                                (TUint32) &iWindowGroup );
        name->SetHidden( ETrue );
        name->SetCaptionL( KVolumePopupWgName ); // FIXME - KSomeUniqueName, available to OOM watcher so this won't be closed
        User::LeaveIfError( name->SetWindowGroupName( iWindowGroup ));
        CleanupStack::PopAndDestroy();  //name
        iWindowGroup.SetOrdinalPosition( 0, ECoeWinPriorityNeverAtFront );

         // create control's window to own window group
        CreateWindowL( &iWindowGroup );
        
        //catch other windows poninter 
        Window().SetNonFading(ETrue); 
        iExt->iWindowGroupCreated = ETrue;
        }
    else
        {
        CreateWindowL( aParent );
        }
        
    if ( CAknEnv::Static()->TransparencyEnabled() )
        {
        Window().SetRequiredDisplayMode( EColor16MA );
        Window().SetTransparencyAlphaChannel();
        Window().SetBackgroundColor(TRgb(~0));
        }
    Window().SetShadowDisabled(ETrue);
    
    
    // Values received from the navi pane volume control resource.
    TInt value    = KErrNotFound;
    TInt minvalue = KErrNotFound;
    TInt maxvalue = KErrNotFound;
    if( iExt->iSliderUsed != KSliderUsed )
        {
        iExt->iOldVolumeControl = new( ELeave )CAknVolumeControl;

        if ( AknLayoutUtils::PenEnabled() )
            iExt->VolumeControl()->SetContainerWindowL(*this);
        
        iExt->iOldVolumeControl->ConstructFromResourceL(reader);	
        }
    else if( iVertical ||
         iFlags == ENaviPaneVolumeControl ||
         iFlags == EDynRangeNaviPaneVolumeControl )
        {
         //use the vertical slider
        iExt->iSliderControl = new( ELeave )CAknSlider;
        iExt->iSliderControl->SetBackground( this );
        
        if ( iFlags == ENaviPaneVolumeControl ||
             iFlags == EDynRangeNaviPaneVolumeControl )
            {
            // Navi pane shows vertical volume popup instead of the old navi
            // pane volume control, but the old style volume control must
            // be also created in order to preserve BC.
            
            // Read and set the initial value and range from the resource
            // before passing it to the CAknVolumeControl.
            TInt int16Length( sizeof( TInt16 ) );
            reader.Advance( int16Length ); // identifier or flags
            if ( iFlags == EDynRangeNaviPaneVolumeControl )
                {
                reader.Advance( int16Length ); // flags
                }

            value = reader.ReadInt16();
            
            if ( iFlags == EDynRangeNaviPaneVolumeControl )
                {
                TPtrC filename = reader.ReadTPtrC();
                
                reader.Advance( 2 * int16Length ); // bitmap and mask ID
                
                minvalue = reader.ReadInt16();
                maxvalue = reader.ReadInt16();
                
                reader.Rewind( 4 * int16Length );
                reader.Rewind( filename.Size() + int16Length ); // filename + length heading
                reader.Rewind( 3 * int16Length );
                }
            else
                {
                reader.Rewind( 2 * int16Length );
                }
            
            iVertical = ETrue;
            iExt->iOldVolumeControl = new ( ELeave ) CAknVolumeControl;
            iExt->iOldVolumeControl->SetContainerWindowL(*this);
            iExt->iOldVolumeControl->ConstructFromResourceL( reader );
            iExt->iOldVolumeControl->SuppressDrawing( ETrue );
            
            // Old volume control was created with the navi pane volume control
            // resource, slider resource is used to create the slider control.
            CleanupStack::PopAndDestroy(); // reader
            iCoeEnv->CreateResourceReaderLC( reader, R_AVKON_VERTICAL_POPUP_SLIDER );
            }

        if(AknLayoutUtils::PenEnabled())
            iExt->VolumeControl()->SetContainerWindowL(*this);
        iExt->iSliderControl->ConstructFromResourceL(this, 0, reader);
        iExt->TryLoadDefaultSliderVolumeBitmap();
        iExt->iSliderControl->ReportMarkerDragEvent( ETrue );
        iExt->iSliderControl->SuppressDrawing( ETrue );
       }           
    else
        {
        iExt->iSliderControl = new( ELeave )CAknSlider;
        iExt->iSliderControl->SetBackground( this );

        if ( AknLayoutUtils::PenEnabled() )
            {
            iExt->VolumeControl()->SetContainerWindowL( *this );
            }
        
        iExt->iSliderControl->ConstructFromResourceL( this, 0, reader );
        iExt->TryLoadDefaultHorizontalVolumeBitmap();
        iExt->iSliderControl->ReportMarkerDragEvent( ETrue );
        iExt->iSliderControl->SuppressDrawing( ETrue );
        }   
    
    
    iExt->VolumeControl()->SetObserver( this );
    if ( iExt->iOldVolumeControl &&
         iExt->iOldVolumeControl != iExt->VolumeControl() )
        {
        // iOldVolumeControl is a navi pane volume control,
        // observer must be set.
        iExt->iOldVolumeControl->SetObserver( this );
        }

    CleanupStack::PopAndDestroy(); // reader
    if ( !( AknLayoutUtils::PenEnabled() ) )
        {
        iExt->VolumeControl()->SetContainerWindowL(*this);
        }

    // In case of volume popup launched from navi pane set the range
    // and value from resource before creating controls.
    if ( iFlags == ENaviPaneVolumeControl ||
         iFlags == EDynRangeNaviPaneVolumeControl )
        {
        if ( minvalue != KErrNotFound && maxvalue != KErrNotFound )
            {
            iExt->iSliderControl->SetRange( minvalue, maxvalue );
            }
            
        if ( value != KErrNotFound )
            {
            iVolume = value;
            iExt->iSliderControl->SetValueL( value );
            }
        }

    if( iExt->iSliderUsed == KSliderUsed )
        {
        iValueType = EAknSliderValueNone;
        }
    else
        {
        iValueType = EAknSliderValuePercentage;
        }
    CreateControlsL();
    SetVolumeLayout();
    // set default behavior
    ShowMuteAsLabel( ETrue );

    // Ensure the popup always gets resource change events via the control 
    // stack. Even if popup is not visible, it need to handle resource change
    // event to adjust position. So add popup to stack in its constructor.
    // Popup does not accept key event and keyboard focus.
    iAvkonAppUi->AddToStackL( this, ECoeStackPriorityDialog+1,
                              ECoeStackFlagRefusesFocus );

    SetVisibilityL(EFalse);    // to make CCoeControl::IsVisible() work

    iExt->iHaveDefaultValue = EFalse;
    iExt->iInitialized = ETrue;
    }
    
// ---------------------------------------------------------------------------
// CAknVolumePopup::CreateControlsL
//
// ---------------------------------------------------------------------------
//
void CAknVolumePopup::CreateControlsL()
    {
    // create label controls
    delete iLabel;
    iLabel = NULL;
    iLabel = new(ELeave) CEikLabel;
    iLabel->SetContainerWindowL( *this );
    iLabel->SetObserver( this );
    SetLabelColor();  
    DoSetValue( Value() );
    
    if(iFlags == EPopupVolumeControl || iFlags == ESmallPopupVolumeControl)
        SetValueType(EAknSliderValuePercentage);
    
    SetValueTextL();

    
    CreateSpeakerL();      

    if( iFlags == ESmallPopupVolumeControl || 
        iFlags == ESmallPopupVolumeControlWithPercent ) 
        {
        TAknTextComponentLayout percentText = 
        AknLayoutScalable_Avkon::popup_side_volume_key_window_t2();
        CFont* font = NULL;
        AknLayoutUtils::FontFromId( percentText.Font(), font );
        iLabel->SetFont( font );                
        // create arrows here.
        CreateLeftRightButtonL();
        }
    else if ( iExt->iSliderUsed != KSliderUsed &&
              iFlags != ENaviPaneVolumeControl &&
              iFlags != EDynRangeNaviPaneVolumeControl )
        {
        delete iMutedLabel;
        iMutedLabel = NULL;
        iMutedLabel = new (ELeave) CEikLabel;
        iMutedLabel->SetContainerWindowL( *this );
        TRgb color;
        if ( iMutedLabel ) // Is not in use in every mode.
            {            
            TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( *iMutedLabel,
                                                            EColorLabelText,
                                                            color) );
            }
        HBufC* txt = StringLoader::LoadL( R_AVKON_POPUP_VOLUME_MUTED, iCoeEnv );
        CleanupStack::PushL( txt );
        iMutedLabel->SetTextL( *txt );
        CleanupStack::PopAndDestroy(); // txt        
        }

    //create "+""-" for vertical slider
    if( iExt->iSliderUsed == KSliderUsed )
        {
        if ( iVertical )
            {               
            // create arrows here.
            CreateUpDownButtonL();
            }
        else 
            {               
            // create arrows here.
            CreateLeftRightButtonL();
            }
        }
    }
// ---------------------------------------------------------------------------
// CAknVolumePopup::SetSpeakerIconL
//
// ---------------------------------------------------------------------------
//
void CAknVolumePopup::CreateSpeakerL()
    {
    if (iSpeaker)
        {
        delete iSpeaker;
        iSpeaker = NULL;
        }
        
    CGulIcon* iconSpeaker  = CGulIcon::NewLC();
    CFbsBitmap* speakerBitmap;
    CFbsBitmap* speakerMask;
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    if( iVertical && iExt->iSliderUsed )
        {
        AknsUtils::CreateColorIconL( skin,
                                     KAknsIIDQgnIndiNsliderUnmuted,
                                     KAknsIIDQsnTextColors,
                                     EAknsCIQsnTextColorsCG19,
                                     speakerBitmap,
                                     speakerMask,
                                     KAvkonBitmapFile,                                 
                                     EMbmAvkonQgn_indi_nslider_unmuted,
                                     EMbmAvkonQgn_indi_nslider_unmuted_mask,
                                     KRgbWhite );
        }
    else
        {
        AknsUtils::CreateColorIconL( skin,
                                     KAknsIIDQgnIndiSpeakerActive,
                                     KAknsIIDQsnTextColors,
                                     EAknsCIQsnTextColorsCG19,
                                     speakerBitmap,
                                     speakerMask,
                                     KAvkonBitmapFile,                                 
                                     EMbmAvkonQgn_indi_speaker,
                                     EMbmAvkonQgn_indi_speaker_mask,
                                     KRgbWhite );
        }
            
    iconSpeaker->SetBitmap( speakerBitmap );
    iconSpeaker->SetMask( speakerMask ); 
    TInt flag = KAknButtonStateHasLatchedFrame|KAknButtonNoFrame;
    if( !iExt->iUseMutedIcon )
        {
        flag = KAknButtonNoFrame;
        }
    //speaker button 
    iSpeaker = CAknButton::NewL( iconSpeaker, 
                              NULL,
                              NULL,
                              NULL, 
                              KNullDesC, 
                              KNullDesC, 
                              flag, 
                              0);
    CleanupStack::Pop();                          
    if( iExt->iUseMutedIcon )
        {
        CGulIcon* iconMute  = CGulIcon::NewLC();
        CFbsBitmap* muteBitmap;
        CFbsBitmap* muteMask;
        if( iVertical && iExt->iSliderUsed )
            {
            AknsUtils::CreateColorIconL(skin,
                                        KAknsIIDQgnIndiNsliderMuted,
                                        KAknsIIDQsnTextColors,
                                        EAknsCIQsnTextColorsCG19,
                                        muteBitmap,
                                        muteMask,
                                        KAvkonBitmapFile,                                 
                                        EMbmAvkonQgn_indi_nslider_muted,
                                        EMbmAvkonQgn_indi_nslider_muted_mask,
                                        KRgbWhite );
            }
        else
            {
            AknsUtils::CreateColorIconL(skin,
                                        KAknsIIDQgnIndiSpeakerMuted,
                                        KAknsIIDQsnTextColors,
                                        EAknsCIQsnTextColorsCG19,
                                        muteBitmap,
                                        muteMask,
                                        KAvkonBitmapFile,                                 
                                        EMbmAvkonQgn_indi_speaker_muted,
                                        EMbmAvkonQgn_indi_speaker_muted_mask,
                                        KRgbWhite );
            }
            
        iconMute->SetBitmap( muteBitmap );
        iconMute->SetMask( muteMask ); 
        iSpeaker->AddStateL( iconMute, 
                                  NULL,
                                  NULL,
                                  NULL, 
                                  KNullDesC, 
                                  KNullDesC, 
                                  1 );
                                                     
        CleanupStack::Pop();         
        }

    if( iSpeaker )
        {
        iSpeaker->SetContainerWindowL( *this );
        iSpeaker->SetObserver( this );        
        }
    } 
            
// ---------------------------------------------------------------------------
// CAknVolumePopup::SetSpeakerIconL
//
// ---------------------------------------------------------------------------
//
void CAknVolumePopup::SetControlIconL( TInt aElement,
                                       CFbsBitmap* aBitmap,
                                       CFbsBitmap* aMask )
    {
    CGulIcon* icon  = CGulIcon::NewLC();
    icon->SetBitmap( aBitmap );
    icon->SetMask( aMask ); 

    switch( aElement )
        {
        case EElemSpeaker:
            {
            CAknButtonState* state = iSpeaker->State(0);
            state->SetIcon( icon );
            }
            break;
        case EElemMute:
            {
            if( iExt->iUseMutedIcon)
                {
                CAknButtonState* state = iSpeaker->State(1);
                state->SetIcon( icon );                
                }
            }
            break;
        case EElemPlusButtonActive:
            {
            CAknButtonState* state = iIncArrow->State(0);
            state->SetIcon( icon );
            }
            break;
        case EElemMinusButtonActive:
            {
            CAknButtonState* state = iDecArrow->State(0);
            state->SetIcon( icon );
            }
            break;
        case EElemPlusButtonInActive:
            {
            CAknButtonState* state = iIncArrow->State(0);
            state->SetDimmedIcon( icon );
            }
            break;
        case EElemMinusButtonInActive:
            {
            CAknButtonState* state = iDecArrow->State(0);
            state->SetDimmedIcon( icon );
            }
            break;
        case EElemPlusButtonSelected:
            {
            CAknButtonState* state = iIncArrow->State(0);
            state->SetPressedIcon( icon );
            }
            break;
        case EElemMinusButtonSelected:
            {
            CAknButtonState* state = iDecArrow->State(0);
            state->SetPressedIcon( icon );
            }
            break;
        default:
           break;
        }
    CleanupStack::Pop();// the ownership of the icon is transfered to button.   	        
    }  
 
// ---------------------------------------------------------------------------
// CAknVolumePopup::CreateLeftRightButtonL
//
// ---------------------------------------------------------------------------
//
void CAknVolumePopup::CreateLeftRightButtonL()
    {
    if ( iDecArrow )
        {
        delete iDecArrow;
        iDecArrow = NULL;
        }
        
    if ( iIncArrow )
        {
        delete iIncArrow;
        iIncArrow = NULL;
        }
        
    iDecArrow = CAknButton::NewL( KAvkonBitmapFile, 
                                  EMbmAvkonQgn_indi_navi_arrow_left, 
                                  EMbmAvkonQgn_indi_navi_arrow_left_mask,
                                  -1, 
                                  -1,
                                  EMbmAvkonQgn_indi_navi_arrow_left, 
                                  EMbmAvkonQgn_indi_navi_arrow_left_mask,
                                  -1,
                                  -1,
                                  KNullDesC, 
                                  KNullDesC, 
                                  KAknButtonNoFrame | KAknButtonKeyRepeat | 
                                                        KAknButtonNoClear, 
                                  0,
                                  KAknsIIDQgnIndiNaviArrowLeft,
                                  KAknsIIDNone,
                                  KAknsIIDQgnIndiNaviArrowLeft
                                  );
    iDecArrow->SetContainerWindowL( *this );
    iDecArrow->SetObserver( this );
    
    iIncArrow = CAknButton::NewL( KAvkonBitmapFile, 
                                  EMbmAvkonQgn_indi_navi_arrow_right, 
                                  EMbmAvkonQgn_indi_navi_arrow_right_mask,
                                  -1, 
                                  -1,
                                  EMbmAvkonQgn_indi_navi_arrow_right, 
                                  EMbmAvkonQgn_indi_navi_arrow_right_mask,
                                  -1,
                                  -1,
                                  KNullDesC, 
                                  KNullDesC, 
                                  KAknButtonNoFrame | KAknButtonKeyRepeat | 
                                                        KAknButtonNoClear, 
                                  0,
                                  KAknsIIDQgnIndiNaviArrowRight,
                                  KAknsIIDNone,
                                  KAknsIIDQgnIndiNaviArrowRight
                                  );
    iIncArrow->SetContainerWindowL( *this );
    iIncArrow->SetObserver( this );                                          
    }
// ---------------------------------------------------------------------------
// CAknVolumePopup::CreateUpDownButtonL
//
// ---------------------------------------------------------------------------
//
void CAknVolumePopup::CreateUpDownButtonL()
    {
    if ( iDecArrow )
        {
        delete iDecArrow;
        iDecArrow = NULL;
        }
        
    if ( iIncArrow )
        {
        delete iIncArrow;
        iIncArrow = NULL;
        }
    if( iVertical && iExt->iSliderUsed )
        {
        CFbsBitmap* bitmap = NULL;
        CFbsBitmap* mask = NULL;
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        AknsUtils::CreateColorIconL( skin,
                                     KAknsIIDQgnIndiNsliderLevelIncrease,
                                     KAknsIIDQsnTextColors,
                                     EAknsCIQsnTextColorsCG19,
                                     bitmap,
                                     mask, 
                                     KAvkonBitmapFile,
                                     EMbmAvkonQgn_indi_nslider_level_increase,
                                     EMbmAvkonQgn_indi_nslider_level_increase_mask,
                                     KRgbWhite ); 

        iIncArrow = CAknButton::NewL( CGulIcon::NewL( bitmap, mask ),  //aIcon
                                      NULL,                            //aDimmedIcon
                                      NULL,                            //aPressedIcon
                                      NULL,                            //aHoverIcon
                                      KNullDesC,                       //aText
                                      KNullDesC,                       //aHelpText
                                      KAknButtonNoFrame | KAknButtonNoClear | KAknButtonKeyRepeat,//aButtonFlags
                                      0                                //aStateFlags
                                     );
                                          
        iIncArrow->SetContainerWindowL( *this );
        iIncArrow->SetObserver( this );
        
        bitmap = NULL;
        mask = NULL;
        AknsUtils::CreateColorIconL( skin,
                                     KAknsIIDQgnIndiNsliderLevelDecrease,
                                     KAknsIIDQsnTextColors,
                                     EAknsCIQsnTextColorsCG19,
                                     bitmap,
                                     mask, 
                                     KAvkonBitmapFile,
                                     EMbmAvkonQgn_indi_nslider_level_decrease,
                                     EMbmAvkonQgn_indi_nslider_level_decrease_mask,
                                     KRgbWhite ); 
        
        iDecArrow = CAknButton::NewL( CGulIcon::NewL( bitmap, mask ),  //aIcon
                                      NULL,                            //aDimmedIcon
                                      NULL,                            //aPressedIcon
                                      NULL,                            //aHoverIcon
                                      KNullDesC,                       //aText
                                      KNullDesC,                       //aHelpText
                                      KAknButtonNoFrame | KAknButtonNoClear | KAknButtonKeyRepeat,//aButtonFlags
                                      0                                //aStateFlags
                                    );
                                                   
        iDecArrow->SetContainerWindowL( *this );
        iDecArrow->SetObserver( this ); 
        }
    else
        {
        iIncArrow =  CAknButton::NewL( KAvkonBitmapFile, 
                                      EMbmAvkonQgn_indi_volume_arrow_up, 
                                      EMbmAvkonQgn_indi_volume_arrow_up_mask,
                                      EMbmAvkonQgn_indi_volume_arrow_up_inactive, 
                                      EMbmAvkonQgn_indi_volume_arrow_up_inactive_mask,
                                      EMbmAvkonQgn_indi_volume_arrow_up_selected, 
                                      EMbmAvkonQgn_indi_volume_arrow_up_selected_mask,
                                      -1,
                                      -1,
                                      KNullDesC, 
                                      KNullDesC, 
                                      KAknButtonNoFrame | KAknButtonNoClear|KAknButtonKeyRepeat, 
                                      0,
                                      KAknsIIDQgnIndiVolumeArrowUp,
                                      KAknsIIDQgnIndiVolumeArrowUpInactive,
                                      KAknsIIDQgnIndiVolumeArrowUpSelected

                                      );

                                
        iIncArrow->SetContainerWindowL( *this );
        iIncArrow->SetObserver( this );
        
        iDecArrow = CAknButton::NewL( KAvkonBitmapFile, 
                                      EMbmAvkonQgn_indi_volume_arrow_down, 
                                      EMbmAvkonQgn_indi_volume_arrow_down_mask,
                                      EMbmAvkonQgn_indi_volume_arrow_down_inactive, 
                                      EMbmAvkonQgn_indi_volume_arrow_down_inactive_mask,
                                      EMbmAvkonQgn_indi_volume_arrow_down_selected, 
                                      EMbmAvkonQgn_indi_volume_arrow_down_selected_mask,
                                      -1,
                                      -1,
                                      KNullDesC, 
                                      KNullDesC, 
                                      KAknButtonNoFrame | KAknButtonKeyRepeat | 
                                                            KAknButtonNoClear, 
                                      0,
                                      KAknsIIDQgnIndiVolumeArrowDown,
                                      KAknsIIDQgnIndiVolumeArrowDownInactive,
                                      KAknsIIDQgnIndiVolumeArrowDownSelected
                                      );                          
        iDecArrow->SetContainerWindowL( *this );
        iDecArrow->SetObserver( this ); 
        }

    }
// ---------------------------------------------------------------------------
// CAknVolumePopup::NewL
// DEPRECATED
// ---------------------------------------------------------------------------
//
EXPORT_C CAknVolumePopup* CAknVolumePopup::NewL ( TUid /*aSharedDataVolumeUid*/,
                                                 const TDesC& /*aKey*/, 
                                                 TInt /*aMinimumValue*/ )
    {
    return CAknVolumePopup::NewL();
    }


// ---------------------------------------------------------------------------
// CAknVolumePopup::NewL
// DEPRECATED
// ---------------------------------------------------------------------------
//
EXPORT_C CAknVolumePopup* CAknVolumePopup::NewL( 
                            TInt /*aMinimumValue = 0 parameter deprecated */ )
    {
    CAknVolumePopup* self = new( ELeave ) CAknVolumePopup(0);
    CleanupStack::PushL( self );
    self->ConstructL( NULL, EFalse );
    CleanupStack::Pop();
    AKNTASHOOK_ADDL( self, "CAknVolumePopup" );
    return self;
    }

// ---------------------------------------------------------------------------
// CAknVolumePopup::~CAknVolumePopup
//
// ---------------------------------------------------------------------------
//
CAknVolumePopup::~CAknVolumePopup()
    {
    AKNTASHOOK_REMOVE();
    // Set the pointer to the observer NULL here, because otherwise
    // this might crash upon the CloseVolumePopup() call when
    // trying to report an event to an invalid observer.
    SetObserver( NULL );
    CloseVolumePopup();
    if( iAvkonAppUi )
		{
		iAvkonAppUi->RemoveFromStack( this );
		}
    if ( iExt->iWindowGroupCreated )
        {
        iWindowGroup.Close();
        }
    delete iTimer;
    delete iSpeaker;

    delete iLabel;
    delete iMutedLabel;
   
    delete iMutedText;
    delete iIncArrow;
    delete iDecArrow;
    
    delete iExt;
    }


// ---------------------------------------------------------------------------
// CAknVolumePopup::HandleVolumeKeyEventL
// ---------------------------------------------------------------------------
//
EXPORT_C TKeyResponse CAknVolumePopup::HandleVolumeKeyEventL(
            const TKeyEvent& /*aEvent*/, TEventCode /*aType*/)
    { return EKeyWasNotConsumed; }  // deprecated


// ---------------------------------------------------------------------------
// CAknVolumePopup::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CAknVolumePopup::CountComponentControls() const
    {
    if( iExt->iSliderUsed == KSliderUsed )
        {
        if ( iExt->iOldVolumeControl )
            {
            // Volume popup launched from navi pane, so old volume
            // control exists also.
            return 6;
            }
        else
            {
            return 5;// iLabel,iSliderControl,iSpeaker,iDecArrow,iIncArrow
            }
        }
        
    else if( iFlags == ESmallPopupVolumeControl || 
             iFlags == ESmallPopupVolumeControlWithPercent )
        {
        return 5;// iLabel, VolumeControl, iSpeaker,iDecArrow,iIncArrow
        }

    return 3; // iLabel, VolumeControl(iMutedLabel), iSpeaker
    }

// ---------------------------------------------------------------------------
// CAknVolumePopup::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CAknVolumePopup::ComponentControl(TInt aIndex) const
    {
    switch (aIndex)
        {
        case 1:
            return iLabel;     
        case 0:
            {
            if(iExt->iSliderUsed != KSliderUsed &&
               iFlags != ESmallPopupVolumeControl && 
               iFlags != ESmallPopupVolumeControlWithPercent &&
               iFlags != ENaviPaneVolumeControl &&
               iFlags != EDynRangeNaviPaneVolumeControl &&
               iMuted )
                {
                return iMutedLabel;
                }
            else
                {
                return iExt->VolumeControl();
                }
            }
        case 2:
            return iSpeaker;
        case 3:
            if( iDecArrow )
                {
                return iDecArrow;
                }
        case 4:
            if( iIncArrow )
                {
                return iIncArrow;
                }
        case 5:
            return iExt->iOldVolumeControl;
         
        default:
            break;
        }
    return NULL;
    }
// ----------------------------------------------------------------------------
// CAknVolumePopup::GetMarkerRect
//
// ----------------------------------------------------------------------------
//
void CAknVolumePopup::GetMarkerRect( TRect& aRect )
    {
    TPoint p;
    TInt min,max;
    GetRange( min, max );
    TSize markerSize( iExt->iMarkerSize );
    TRect volumeControlRect = iExt->VolumeControl()->Rect();    
    if ( iExt->iSliderUsed == KSliderUsed )
        {
        
        TInt pixelRange = volumeControlRect.Height() - markerSize.iHeight;
        TInt pos = ( pixelRange * ( iVolume - min ) / (max-min) );
            
        p.iX = volumeControlRect.iTl.iX;
        p.iY = volumeControlRect.iBr.iY - pos - markerSize.iHeight;

        }
        
    aRect = TRect( p, iExt->iMarkerSize );
    }

 
// ---------------------------------------------------------------------------
// CAknVolumePopup::HandlePointerEventL
// ---------------------------------------------------------------------------
//    
void CAknVolumePopup::HandlePointerEventL(const TPointerEvent &aPointerEvent)
    {
    iExt->iHandlingPointerEvent = ETrue;
    TInt oldValue = Value();

    if ( !AknLayoutUtils::PenEnabled() )
        {
        return;
        }
    //if touch point outside the window, popup volume will be closed. 
    TRect window = TRect(0,0, iParentRect.Width(), iParentRect.Height());
  
    TPointerEvent pointerEvent = aPointerEvent;
    TRect dragRect;
    TRect volumeControlRect = iExt->VolumeControl()->Rect();
    if( iExt->iSliderUsed == KSliderUsed )
        {
        dragRect = TRect( window.iTl.iX, 
                        volumeControlRect.iTl.iY, 
                        window.iBr.iX, 
                        volumeControlRect.iBr.iY );
                        
        }
    switch( aPointerEvent.iType )
        {
        case TPointerEvent::EButton1Down:
        	{
        	if ( iMuted && ( !iSpeakerRect.Contains( aPointerEvent.iPosition ) ) &&
        	     ( !iDecArrow->Rect().Contains( aPointerEvent.iPosition ) ) &&
        	     ( !iIncArrow->Rect().Contains( aPointerEvent.iPosition ) ) )
                	{
                	HandleControlEventL( iSpeaker, EEventStateChanged ); 
                	break;
                	}
        	}
        case TPointerEvent::EButtonRepeat:
        case TPointerEvent::EDrag:
            {
            /*finger touch slider, the pointer fell on the position 
            which is in finger touch area but not in markerarea,
            becuase markerarea pointer can handle by slider.*/
            if( iExt->iSliderUsed == KSliderUsed )  
                {
                if( iVertical && dragRect.Contains( aPointerEvent.iPosition ) &&
                    !volumeControlRect.Contains( aPointerEvent.iPosition ) ) 
                    {
                    pointerEvent.iPosition.iX = volumeControlRect.iTl.iX;
                    }
                else if( dragRect.Contains( aPointerEvent.iPosition ) &&
                    !volumeControlRect.Contains( aPointerEvent.iPosition ) ) 
                    {
                    pointerEvent.iPosition.iY = volumeControlRect.iTl.iY;
                    }
                }
            }
            break;
        default:
            break;
        }
    
    ResetTimer();
    
    //for finger touch and drag
    TRect markerRect;
    GetMarkerRect( markerRect );    
    CCoeControl::HandlePointerEventL( pointerEvent );
    
    markerRect.iTl.iX = window.iTl.iX;
    markerRect.iBr.iX = window.iBr.iX;
    if( dragRect.Contains( aPointerEvent.iPosition ) &&
        !volumeControlRect.Contains( aPointerEvent.iPosition ) &&
        !markerRect.Contains( aPointerEvent.iPosition ) &&
        aPointerEvent.iType != TPointerEvent::EDrag )
        {
        Window().RequestPointerRepeatEvent( KScrollRepeatTimeout, window );
        }
    iExt->iHandlingPointerEvent = EFalse;
    }
// ---------------------------------------------------------------------------
// CAknVolumePopup::Draw
// ---------------------------------------------------------------------------
//
void CAknVolumePopup::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    RRegion clippingReg(aRect);
    
    if( iExt->iSliderUsed == KSliderUsed && iExt->iSliderControl)
        {
        clippingReg.SubRect(iExt->iSliderControl->Rect());
        }
    
    gc.SetClippingRegion( clippingReg );
    
    TAknLayoutRect windowRect;
    windowRect.LayoutRect( iParentRect,
                           AknLayoutScalable_Avkon::bg_popup_sub_pane_cp22());
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.SetPenStyle( CGraphicsContext::ENullPen );                               
    gc.SetBrushColor( windowRect.Color() );
    
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );

    TBool frameDrawn( EFalse );
    if ( CAknEnv::Static()->TransparencyEnabled() )
        {
        // the added flag removes the white bg for transparency
        frameDrawn = AknsDrawUtils::Background( skin, cc, this, gc, 
                                                  windowRect.Rect(), 
                                                  KAknsDrawParamNoClearUnderImage );
        }
    else
        {
        frameDrawn = AknsDrawUtils::Background( skin, cc, this, gc, 
                                                  windowRect.Rect() );
        }

    if( !frameDrawn )
        {
        gc.DrawRect( windowRect.Rect() );
        }
    gc.CancelClippingRegion();
    clippingReg.Close();
    }
    
// ---------------------------------------------------------------------------
// CAknVolumePopup::SetValue
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknVolumePopup::SetValue(TInt aValue)
	{
	if ( iExt->iInitialized )
	    {
	    if(!iExt->iHaveDefaultValue )
            {
            iExt->iDefaultValue = aValue;
            iExt->iHaveDefaultValue = ETrue;
            }
            
    	TInt min, max;
        GetRange(min, max); 
    	if( ( aValue==min ) && ( !iMuted ) )
    		{
    		MutePressed();
    		return;
    		}
        DoSetValue( aValue );
	    }
	}
	    
// ---------------------------------------------------------------------------
// CAknVolumePopup::DoSetValue
// ---------------------------------------------------------------------------
//
void CAknVolumePopup::DoSetValue(TInt aValue)
    {
    if ( iVisible )
        {
        ResetTimer();
        }
    TInt min, max;
    GetRange( min, max );
    // if value is out of bounds then do nothing. 
    if ( aValue < min || aValue > max )
        {
        //__ASSERT_DEBUG(0,User::Panic(_L("CAknVolumePopup"), KErrArgument));
        }
    
    TBool valueChanged( aValue != iVolume );
       
    if ( valueChanged )
        {
        iVolume = aValue;
        }
    //value not changed, but value text can be changed    
    TInt err = KErrNone;   
    if( iFlags == ESmallPopupVolumeControl || 
        iFlags == ESmallPopupVolumeControlWithPercent ||
        iFlags == KSliderUsed ||
        iFlags == ENaviPaneVolumeControl ||
        iFlags == EDynRangeNaviPaneVolumeControl )
        { 
        TRAP(err,SetValueTextL());
        }
   
     if (iVolume == min)
        {
        SetSpeakerMuted( ETrue );        
        }   
    else if ( iVolume > min && iMuted )
        {
        SetSpeakerMuted( EFalse );
        }        
    if ( iExt->iSliderUsed == KSliderUsed ||
         iFlags == ENaviPaneVolumeControl ||
         iFlags == EDynRangeNaviPaneVolumeControl ) 
        {
        if ( valueChanged )
            {
            TRAP(err,iExt->iSliderControl->SetValueL( iVolume ));
            
            if ( iFlags == ENaviPaneVolumeControl ||
                 iFlags == EDynRangeNaviPaneVolumeControl )
                {
                // Navi pane volume control.
                iExt->iOldVolumeControl->SetValue( iVolume );
                }
            }
        }
    else if( iFlags == ESmallPopupVolumeControl || 
        iFlags == ESmallPopupVolumeControlWithPercent )
        {
        if ( valueChanged )
            {
            iExt->iOldVolumeControl->SetValue( iVolume );
            }
        }        
    if( iIncArrow && iDecArrow )
        {
        iIncArrow->SetDimmed(EFalse);
        iDecArrow->SetDimmed(EFalse);
        if( aValue == min )
            {
            iDecArrow->SetDimmed(ETrue);
            }
        else if( aValue == max )
            {
            iIncArrow->SetDimmed(ETrue);
            }
        } 
   
    if ( iVisible )
        {
        SetVisibilityL( ETrue );
        DrawDeferred();
        }
    }

// ----------------------------------------------------------------------------
// CAknVolumePopup::SetValueTextL 
// Sets the text for the value label.
// ----------------------------------------------------------------------------
//
 void CAknVolumePopup::SetValueTextL()
    {
    TBuf<KTextLen> textBuf;
    DoSetValueTextL( textBuf, iVolume );
    iLabel->SetTextL( textBuf );
    }
    

// ----------------------------------------------------------------------------
// CAknVolumePopup::DoSetValueTextL
// ----------------------------------------------------------------------------
//
void CAknVolumePopup::DoSetValueTextL( TDes& aTextBuf, TInt aValue )
    {
    TBuf<KTextLen> valueBuf;
    _LIT( KBareFigure, "%d" );
    _LIT( KPercentageMirror, "%%%d" );
    _LIT( KFraction, "%d/%d" );
    TInt min,max;
    GetRange( min, max );
    iExt->iSpeakerHidden = ETrue;
    switch ( iValueType )
        {
        case EAknSliderValueBareFigure:
            valueBuf.Format( KBareFigure, aValue ); // bare figure
            break;

        case EAknSliderValuePercentage:
            if( AknLayoutUtils::LayoutMirrored() )
                {
            	valueBuf.Format( KPercentageMirror, aValue );
                }
            else
                {
                HBufC* percentage = StringLoader::LoadLC( R_QTN_SELECT_SLIDER_VALUE, aValue );                
               	valueBuf.Copy( *percentage );
            	CleanupStack::PopAndDestroy( percentage );
                }
            break;

        case EAknSliderValueFraction:
            valueBuf.Format( KFraction, aValue, max ); // x/y
            break;

        case EAknSliderValueDecimal:
            {
            TReal r;
            Math::Pow10( r, iDecimalPlaces );
            // First have to format the format.
            TBuf<8> format;
            // This allows for 2 digit field size and/or decimal places
            _LIT( KFormatTemplate, "%%-%d.%df" );
            format.Format( KFormatTemplate,
                           KTextLen,
                           iDecimalPlaces );
            valueBuf.Format( format, aValue / r );
            valueBuf.TrimAll();
            }
            break;
        default:
            iExt->iSpeakerHidden = EFalse;
            break; // valueBuf left empty
        } // end switch

    // Convert this formatted number if necessary to display language-sensitive
    // numerals
    AknTextUtils::DisplayTextLanguageSpecificNumberConversion( valueBuf );

    // A text pointer for the format string

    aTextBuf.Copy( valueBuf.Left( KTextLen ) );
    }


// ---------------------------------------------------------------------------
// CAknVolumePopup::SetRange
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknVolumePopup::SetRange( TInt aMinimumValue, TInt aMaximumValue )
    {
    if( iExt->iDefaultValue<=aMinimumValue )
        {
        iExt->iDefaultValue = aMinimumValue;
        }
    else if( iExt->iDefaultValue>= aMaximumValue )
        {
        iExt->iDefaultValue =  aMaximumValue;
        }
        
    if( iExt->iSliderUsed == KSliderUsed )
        {
        iExt->iSliderControl->SetRange( aMinimumValue, aMaximumValue );
        }
    else
        {
        iExt->iOldVolumeControl->SetRange( aMinimumValue, aMaximumValue );
        }
        
    // the mute's stored value should always be at least the min value
    iStoredLevel = aMinimumValue;
    }


// ---------------------------------------------------------------------------
// CAknVolumePopup::GetRange()
//
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknVolumePopup::GetRange( TInt& aMinimumValue, 
                                         TInt& aMaximumValue )
    {
    if( iExt->iSliderUsed == KSliderUsed )
        {
        iExt->iSliderControl->GetRange( aMinimumValue, aMaximumValue );
        }
    else
        {
        iExt->iOldVolumeControl->GetRange( aMinimumValue, aMaximumValue );
        }

    }


// ---------------------------------------------------------------------------
// CAknVolumePopup::Value
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CAknVolumePopup::Value() const
    {
    if( iExt->iSliderUsed == KSliderUsed )
        {
        return iExt->iSliderControl->Value();
        }
    else
        {
        return iExt->iOldVolumeControl->Value();
        }
    
    }

// ---------------------------------------------------------------------------
// CAknVolumePopup::SetValueType
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknVolumePopup::SetValueType( TInt aValueType )
    {
    if( iExt->iSliderUsed == KSliderUsed )
        {
        iValueType = aValueType;
        DoSetValue( Value() );
        }
    }
   
// ---------------------------------------------------------------------------
// CAknVolumePopup::SetStepSize()
//
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknVolumePopup::SetStepSize( TInt aStepSize )
    {
    if( iExt->iSliderUsed == KSliderUsed )
        {
        return iExt->iSliderControl->SetStepSize( aStepSize );
        }
    }
    
// ---------------------------------------------------------------------------
// CAknVolumePopup::SetAdjustmentIndicatorOn()
//
// ---------------------------------------------------------------------------
//    
EXPORT_C void CAknVolumePopup::SetAdjustmentIndicatorDisplay( TBool aFlag )
    {
    iAdjustmentIndicatorOn = aFlag;
    }
// ---------------------------------------------------------------------------
// CAknVolumePopup::SetTimeOutAsSecond()
//
// ---------------------------------------------------------------------------
//    
EXPORT_C void CAknVolumePopup::SetTimeOutAsSecond( TInt aSecond )
    {
    iTimeout = aSecond;
    }
// ---------------------------------------------------------------------------
// CAknVolumePopup::SetDecimalPlaces()
//
// ---------------------------------------------------------------------------
//     
EXPORT_C void CAknVolumePopup::SetDecimalPlaces( TInt aDecimalPlaces )
    {
    __ASSERT_DEBUG( aDecimalPlaces >= 0, Panic( EAknPanicInvalidValue ) );
    __ASSERT_DEBUG( aDecimalPlaces < 10, Panic( EAknPanicInvalidValue ) );
    iDecimalPlaces = aDecimalPlaces;
    }
// ---------------------------------------------------------------------------
// CAknVolumePopup::SetTitleTextL
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknVolumePopup::SetTitleTextL( const TDesC& aText )
    {
    if ( iFlags != ESmallPopupVolumeControl && 
        iFlags != ESmallPopupVolumeControlWithPercent &&
        iFlags != KSliderUsed )
        {        
        iLabel->SetTextL( aText );
        iLabel->CropText();  // add ellipsis if text does not fit
        }
    if ( iVisible )
        {
        Window().Invalidate( iLabel->Rect() );
        }    
    }

// ---------------------------------------------------------------------------
// CAknVolumePopup::ShowProfileName
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknVolumePopup::ShowProfileName( TBool /*aShowProfile*/ )
    { } // deprecated

// ---------------------------------------------------------------------------
// CAknVolumePopup::ShowMuteAsLabel
// ---------------------------------------------------------------------------
//
/*EXPORT_C*/ void CAknVolumePopup::ShowMuteAsLabel( TBool aShowMuteAsLabel )
    {
    iShowMuteAsLabel = aShowMuteAsLabel;
    }

TKeyResponse CAknVolumePopup::OfferKeyEventL( const TKeyEvent& aKeyEvent,
                                                TEventCode aType )
    { 
    TKeyResponse response( EKeyWasNotConsumed );    
    
    if ( aType == EEventKey )
        {
        switch( aKeyEvent.iCode )
            {
            case EKeyEscape:
                if ( iVisible  )
                    {
                    CloseVolumePopup();
                    response = EKeyWasConsumed;
                    }
                break;
            default:
                break;
            }
        }
        
    return response;
    }
// ---------------------------------------------------------------------------
// CAknVolumePopup::UseMutedIcon
// ---------------------------------------------------------------------------
//    
EXPORT_C void CAknVolumePopup::UseMutedIcon( TBool aFlag )
    {
    iExt->iUseMutedIcon = aFlag;
    CreateSpeakerL();
    }

// ---------------------------------------------------------------------------
// CAknVolumePopup::SetSpeakerMuted
// ---------------------------------------------------------------------------
//
void CAknVolumePopup::SetSpeakerMuted( TBool aMuted )
    {
    if( iSpeaker && iExt->iUseMutedIcon )
        {
        iSpeaker->SetCurrentState( aMuted ? 1 : 0, ETrue );
        }
	    if ( iMuted != aMuted )
        {
        if ( iVisible )
            {
            // skin stuff - find out size of the corner piece
            TAknLayoutRect cornerRect;
            // skinned draw uses submenu popup window skin
            cornerRect.LayoutRect(
                Rect(),                            
                AknLayoutScalable_Avkon::bg_popup_sub_pane_g1() );
                                   
	            Window().Invalidate();
            }
        }
    iMuted = aMuted;
    }
// ---------------------------------------------------------------------------
// CAknVolumePopup::MutePressed
// ---------------------------------------------------------------------------
//
void CAknVolumePopup::MutePressed()
    {
    // not slider
    TInt min, max;
    GetRange(min, max);
    
    // mute indicator was tapped
    if ( iMuted )
        {
        // The popup was muted, so let's restore the value
        if(iStoredLevel == min)
        {
        if( iExt->iSliderUsed == KSliderUsed )
        	iStoredLevel += iExt->iSliderControl->StepSize();
        else
        	iStoredLevel++;
        }
        
        // restore saved value
        DoSetValue(iStoredLevel);
        // Put minimum as default, so if we drag or use SetValue to set the value
        // to mute, we then come out of the mute
        iStoredLevel = min;
        }
    else if(!iMuted)
        {
        // mute the volume popup
        iStoredLevel = Value();
        DoSetValue(min);
        }
    }
// ---------------------------------------------------------------------------
// CAknVolumePopup::StartTimer
// ---------------------------------------------------------------------------
//
void CAknVolumePopup::StartTimer()
    {
    if ( !iTimer->IsActive() )  // should not be
        {
        if( iTimeout != 0 )
            {
             iTimer->Start( iTimeout * 1000000,
                       iTimeout * 1000000,
                       TCallBack( CAknVolumePopup::TimerExpired, this ) );
            }
        else
            {
            iTimer->Start( KInactivityTime,
                           KInactivityTime,
                       TCallBack( CAknVolumePopup::TimerExpired, this ) );
            }
        }
    }
// ---------------------------------------------------------------------------
// CAknVolumePopup::ResetTimer
// ---------------------------------------------------------------------------
//
void CAknVolumePopup::ResetTimer()
    {
    if (iTimer->IsActive())
        {
        iTimer->Cancel();
        }
    if( !Parent() )
        {
        StartTimer();
        }
    }

// ---------------------------------------------------------------------------
// CAknVolumePopup::TimerExpired
// ---------------------------------------------------------------------------
//
TInt CAknVolumePopup::TimerExpired(TAny * aPtr)
    {
    ((CAknVolumePopup*)aPtr)->CloseVolumePopup();
    return EFalse;   // do not restart timer
    }

// ---------------------------------------------------------------------------
// CAknVolumePopup::ShowVolumePopupL
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknVolumePopup::ShowVolumePopupL()
    {
    ResetTimer();
    
    if (iVisible)
        {      
        return;
        }

    MTouchFeedback* feedback = MTouchFeedback::Instance();
    if ( feedback )
        {
        feedback->InstantFeedback( ETouchFeedbackPopUp );
        }
    CleanupStack::PushL(TCleanupItem(CleanupShowVolumePopup, this));
       
    SetVisibilityL(ETrue);
    ActivateL();
    DrawNow();
    // finally, make window visible
    if( !Parent() && (iFlags == ENaviPaneVolumeControl ||
         iFlags == EDynRangeNaviPaneVolumeControl ))
        {
        DrawableWindow()->SetOrdinalPosition(0, ECoeWinPriorityAlwaysAtFront);
        }
    else if( !Parent() )
        {
        iWindowGroup.SetOrdinalPosition( 0, KWindowPosition );
        }
   
    if ( Window().IsFaded() )
        {
        Window().SetFaded( EFalse, RWindowTreeNode::EFadeIncludeChildren );
        }
    CleanupStack::Pop();    // clean volume popup cleanup item
    }
// ---------------------------------------------------------------------------
// CAknVolumePopup::SizeChanged
// ---------------------------------------------------------------------------
//
void CAknVolumePopup::SizeChanged()
    {
    // ensure that rect has right size.
        
    iParentRect = TRect(0,0,Rect().Width(), Rect().Height());

    TAknWindowComponentLayout volumeComponent; // volumecontrol
    TAknWindowComponentLayout iconComponent; // mute/unmute icon
    TAknTextComponentLayout textComponent;
    TRect iconRect;
     
    if ( iFlags == ESmallPopupVolumeControl || 
        iFlags == ESmallPopupVolumeControlWithPercent )
        {   
        // percent field
        textComponent = 
            AknLayoutScalable_Avkon::popup_side_volume_key_window_t2();             
        // arrows
        TAknWindowComponentLayout leftArrow = 
            AknLayoutScalable_Avkon::popup_side_volume_key_window_g2();
        TAknWindowComponentLayout rightArrow = 
            AknLayoutScalable_Avkon::popup_side_volume_key_window_g3();
        
        TAknLayoutRect arrow;
        
        arrow.LayoutRect( Rect(), leftArrow );
        iDecArrow->SetRect( arrow.Rect() );
        
        arrow.LayoutRect( Rect(), rightArrow );
        iIncArrow->SetRect( arrow.Rect() );
        
        // icon component is wrong!
        iconComponent = AknLayoutScalable_Avkon::ai2_mp_volume_pane_g1();        
        iconRect = TRect( TSize( textComponent.H(), textComponent.H() ) );
        
        volumeComponent = AknLayoutScalable_Avkon::navi_navi_volume_pane_cp2();           
                       
        }
    else if ( iExt->iSliderUsed != KSliderUsed &&
              iFlags != ENaviPaneVolumeControl &&
              iFlags != EDynRangeNaviPaneVolumeControl )
        {
       
        volumeComponent = AknLayoutScalable_Avkon::volume_small_pane_cp1();    
        iconComponent = AknLayoutScalable_Avkon::popup_side_volume_key_window_g1();
        TAknLayoutRect r;
        r.LayoutRect( Rect(),
            iconComponent );    
        iconRect = r.Rect();   
        iSpeakerRect = iconRect; 

        TAknLayoutRect mutedLabelRect;
        mutedLabelRect.LayoutRect( Rect(),
                    AknLayoutScalable_Avkon::volume_small_pane_cp1() );
        iMutedLabel->SetRect(mutedLabelRect.Rect()); 
        AknLayoutUtils::LayoutControl(iExt->VolumeControl(),Rect(),volumeComponent);
         
        }
        
    if( iExt->iSliderUsed != KSliderUsed )
        {
    	if( iFlags != ESmallPopupVolumeControl && 
            iFlags != ESmallPopupVolumeControlWithPercent &&
            iFlags != ENaviPaneVolumeControl &&
            iFlags != EDynRangeNaviPaneVolumeControl )
            {
            textComponent = 
                AknLayoutScalable_Avkon::popup_side_volume_key_window_t1();        
            }
        }
    else if( iVertical )
        {
        textComponent = 
            AknLayoutScalable_Avkon::popup_slider_window_t2(0);
        }
     else 
         {
     	 textComponent = 
             AknLayoutScalable_Apps::popup_vtel_slider_window_t1(0);
         }
            
        AknLayoutUtils::LayoutLabel( iLabel, iParentRect, textComponent );
        SetLabelColor();
        AknLayoutUtils::LayoutControl( iExt->VolumeControl(), iParentRect, volumeComponent );
        
    if (  iExt->iSliderUsed != KSliderUsed  )
    {
        if( ( iFlags == ESmallPopupVolumeControl || 
             iFlags == ESmallPopupVolumeControlWithPercent ) )
            {
            TPoint volTL = iExt->VolumeControl()->Rect().iTl;
            volTL += TPoint( iconRect.Width()*KWidthSpace, 0 );
            TSize volSize = iExt->VolumeControl()->Size();
            //small gap between icon and control
            volSize -= TSize(iconRect.Width()*KWidthSpace,0); 
            iExt->VolumeControl()->SetRect( TRect( volTL, volSize ) );
            iSpeakerRect = TRect( iExt->VolumeControl()->Rect().iTl - 
                                  TPoint( iconRect.Size().iWidth*KWidthSpace, 0), 
                                  iconRect.Size() ); 
            }
        }
    else if( iVertical )
        {
        // with icon
        if( !iExt->iSpeakerHidden )
            {
            volumeComponent = AknLayoutScalable_Avkon::slider_pane(0);
            AknLayoutUtils::LayoutControl( iExt->VolumeControl(),
                                           iParentRect,
                                           volumeComponent );
            
            //ic
            TAknLayoutRect r;
            r.LayoutRect( iParentRect, 
                          AknLayoutScalable_Avkon::popup_slider_window_g6(0) );
            iSpeakerRect = r.Rect();
            
            //"+""-" icon
            TRect t;
            TInt touch;
            r.LayoutRect( iParentRect, 
                          AknLayoutScalable_Avkon::popup_slider_window_g4(0) );
            touch = r.Rect().iTl.iX - iParentRect.iTl.iX;
            t.iTl.iX = r.Rect().iTl.iX - touch/2;
            t.iTl.iY = r.Rect().iTl.iY;
            t.iBr.iX = r.Rect().iBr.iX + touch/2;
            t.iBr.iY = r.Rect().iBr.iY;
            iIncArrow->SetRect( t );
            TInt icon = iIncArrow->SetIconSize( r.Rect().Size() );
            r.LayoutRect( iParentRect, 
                          AknLayoutScalable_Avkon::popup_slider_window_g5(0) );
            t.iTl.iX = r.Rect().iTl.iX - touch/2;
            t.iTl.iY = r.Rect().iTl.iY;
            t.iBr.iX = r.Rect().iBr.iX + touch/2;
            t.iBr.iY = r.Rect().iBr.iY;
            iDecArrow->SetRect( t );
            icon = iDecArrow->SetIconSize( r.Rect().Size() );
            
            //marker size
            r.LayoutRect( iParentRect, 
            AknLayoutScalable_Avkon::popup_slider_window_g6(0) );
            iExt->iMarkerSize = r.Rect().Size();
            }
        // with text
        else if( iValueType != EAknSliderValueNone )
            {
            volumeComponent =  AknLayoutScalable_Avkon::slider_pane(1);
            AknLayoutUtils::LayoutControl( iExt->VolumeControl(),
                                           iParentRect,
                                           volumeComponent );
            //"+""-" icon
            TAknLayoutRect r;
            r.LayoutRect( iParentRect, 
                          AknLayoutScalable_Avkon::popup_slider_window_g4(1) );
            iIncArrow->SetRect( r.Rect() );
            r.LayoutRect( iParentRect, 
                          AknLayoutScalable_Avkon::popup_slider_window_g5(1) );
            iDecArrow->SetRect( r.Rect() );
            
            //marker size
            r.LayoutRect( iParentRect, 
            AknLayoutScalable_Avkon::popup_slider_window_g6(0) );
            iExt->iMarkerSize = r.Rect().Size();
            }
        // without icon and text
        else
            {
            volumeComponent = AknLayoutScalable_Avkon::slider_pane(2);
            AknLayoutUtils::LayoutControl( iExt->VolumeControl(),
                                           iParentRect,
                                           volumeComponent );
            
            //"+""-" icon
            TAknLayoutRect r;
            r.LayoutRect( iParentRect, 
                          AknLayoutScalable_Avkon::popup_slider_window_g4(2) );
            iIncArrow->SetRect( r.Rect() );
            r.LayoutRect( iParentRect, 
                          AknLayoutScalable_Avkon::popup_slider_window_g5(2) );
            iDecArrow->SetRect( r.Rect() );
            
            //marker size
            r.LayoutRect( iParentRect, 
            AknLayoutScalable_Avkon::popup_slider_window_g6(0) );
            iExt->iMarkerSize = r.Rect().Size();
            }
        }
    else 
        {
        // Horizontal
        textComponent = 
             AknLayoutScalable_Apps::popup_vtel_slider_window_t1(0);
        volumeComponent = 
             AknLayoutScalable_Apps::vtel_slider_pane(0);  

        AknLayoutUtils::LayoutLabel( iLabel, iParentRect, textComponent );
        SetLabelColor();
        AknLayoutUtils::LayoutControl( iExt->VolumeControl(), iParentRect, volumeComponent );
    
        TAknLayoutRect r;
        r.LayoutRect( iParentRect, 
        AknLayoutScalable_Apps::vtel_slider_pane(0) );
    
        iExt->VolumeControl()->SetRect( r.Rect() );
        r.LayoutRect( iParentRect, 
                      AknLayoutScalable_Apps::popup_vtel_slider_window_g2(0) );
        
        iSpeakerRect = r.Rect();
        
        //"+""-" icon
        r.LayoutRect( iParentRect, 
                       AknLayoutScalable_Apps::popup_vtel_slider_window_g4(0) );
        iIncArrow->SetRect( r.Rect() );
        r.LayoutRect( iParentRect, 
                       AknLayoutScalable_Apps::popup_vtel_slider_window_g3(0) );
        iDecArrow->SetRect( r.Rect() );
        
        //slider pane and marker size
      
        r.LayoutRect( iParentRect, 
        AknLayoutScalable_Apps::vtel_slider_pane_g5(0) );
        iExt->iMarkerSize = r.Rect().Size();
        }
    iSpeaker->SetRect( iSpeakerRect );
    
    // read outer rect and inner rect from layout data
    TAknLayoutRect outerRect;
    outerRect.LayoutRect( iParentRect,
                          AknLayoutScalable_Avkon::bg_popup_sub_pane_cp22());

    TAknLayoutRect innerRect;
    innerRect.LayoutRect( outerRect.Rect(),                            
                          AknLayoutScalable_Avkon::bg_popup_sub_pane_g1() );            
    
    iExt->iBgContext->SetFrameRects( outerRect.Rect(), innerRect.Rect() ); 
    }
// ----------------------------------------------------------------------------
// CAknVolumeControl::SetVolumeLayout(TInt aStyle)
// Pure layout function.
// ----------------------------------------------------------------------------
//
void CAknVolumePopup::SetVolumeLayout()
    {
    // get default parent rectangle (top pane)
    TRect appRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EApplicationWindow,
                                       appRect );
    TInt variety( 0 );
    if ( iFlags == ESmallPopupVolumeControl )
        {       
        variety = 2; 
        }
    else if ( iFlags == ESmallPopupVolumeControlWithPercent )
        {
        variety = 1;
        } 
	TAknLayoutRect r;
    
    if( iExt->iSliderUsed != KSliderUsed )
        {
        r.LayoutRect( appRect,AknLayoutScalable_Avkon::area_top_pane(3) );
        r.LayoutRect( r.Rect(),
            AknLayoutScalable_Avkon::popup_side_volume_key_window( variety ) );    	
        }
    else if ( iVertical ||
              iFlags == ENaviPaneVolumeControl ||
              iFlags == EDynRangeNaviPaneVolumeControl )
        {
        // Same condition for the main pane variety in 
        // CAknNavigationControlContainer::VolumePopupRect()
        TInt mainPaneVariety = 3; // portrait main pane
        if ( AknStatuspaneUtils::HDLayoutActive()  || 
             Layout_Meta_Data::IsLandscapeOrientation() )
            {
            // Full screen main pane variety
            mainPaneVariety = 13;
            }
                    
        r.LayoutRect(appRect,AknLayoutScalable_Avkon::main_pane(mainPaneVariety) );
            
        if( Parent() )
            {
            r.LayoutRect( Parent()->Rect(),
            AknLayoutScalable_Avkon::popup_slider_window(
                Layout_Meta_Data::IsLandscapeOrientation() ) );
            }
        else
            {
            r.LayoutRect( r.Rect(),
            AknLayoutScalable_Avkon::popup_slider_window(
                Layout_Meta_Data::IsLandscapeOrientation() ) );           
            }
        }
    else
        {
        r.LayoutRect( appRect,
            AknLayoutScalable_Apps::main_pane(0) ); 
        r.LayoutRect( r.Rect(),
            AknLayoutScalable_Apps::main_video_tele_pane(0) );
        r.LayoutRect( r.Rect(),
            AknLayoutScalable_Apps::popup_vtel_slider_window(0) );
        }
    
    iParentRect = r.Rect();
    delete iExt->iBgContext;
	iExt->iBgContext = NULL;
	TRAP_IGNORE( iExt->iBgContext = CAknsFrameBackgroundControlContext::NewL(
            KAknsIIDQsnFrPopup, iParentRect, iParentRect, EFalse ) );
    SetRect( iParentRect );  
    }
// ---------------------------------------------------------------------------
// CAknVolumePopup::HandleResourceChange
// ---------------------------------------------------------------------------
//    
void CAknVolumePopup::HandleResourceChange( TInt aType )
    {    
    CCoeControl::HandleResourceChange( aType );
    if ( aType == KAknsMessageSkinChange )
        {
        TRAP_IGNORE( CreateControlsL() );
        SizeChanged();
        }
    else if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        SetVolumeLayout();        
        PositionChanged();       
        }
    }
// ---------------------------------------------------------------------------
// CAknVolumePopup::HandleControlEventL
// ---------------------------------------------------------------------------
//    
void CAknVolumePopup::HandleControlEventL( CCoeControl* aControl,
                                           TCoeEvent aEventType )
    {
    // In case of navi pane volume control we must send the event
    // also to the navigation decorator control to keep the volume levels
    // between the popup and the application in sync.
    if ( iVertical &&
         aControl == iExt->iOldVolumeControl )
        {
        ReportEventL( aEventType );
        }
    
    switch( aEventType )
        {
        case EEventStateChanged:
            {        
            TInt value = -1;
            value = Value();

            if ( aControl == iIncArrow && iExt->VolumeControl() )
                {
                if( iExt->iSliderUsed == KSliderUsed )         
                	value = value + iExt->iSliderControl->StepSize();
                else
                	value++;
                }
            else if ( aControl == iDecArrow && iExt->VolumeControl() )
                {
                if( iExt->iSliderUsed == KSliderUsed )
                	value = value - iExt->iSliderControl->StepSize();
                else
                	value--;
                }
            else if ( aControl == iSpeaker )
                {         
                if( iExt->iUseMutedIcon )
                    MutePressed();
                /**
                * Press speaker icon,Value() should return KVolumePopupMutedValue 
                * or saved value
                */
                }
            if ( aControl != iSpeaker )
                {
	            TInt min, max;
	            GetRange(min, max);
                TBool valueChanged( value != iVolume );                
                DoSetValue(value);
                // because +/- button is already dimmed it does not play sensitive 
                // feedback on last step (in case of button repeat)
                if (( aControl == iDecArrow || aControl == iIncArrow ) &&
                      valueChanged && ( value == min || value == max ) &&
                      !iExt->iHandlingPointerEvent )
                    {
                    MTouchFeedback* feedback = MTouchFeedback::Instance();
                    if ( feedback )
                        {
                        feedback->InstantFeedback( this, ETouchFeedbackSensitiveButton );
                        }
                    }
                }
            ReportEventL( aEventType );
            break;
            }
        case EEventRequestFocus:
            {
            if( aControl == iLabel && iExt->iHaveDefaultValue && iExt->iResetDefaultValue )
                {
                // Restore default value
                DoSetValue( iExt->iDefaultValue );
                ReportEventL( EEventStateChanged );
                }
            break;
            }
        default:
            {
            break;
            }
        }
    }

// ---------------------------------------------------------------------------
// CAknVolumePopup::CleanupShowVolumePopup
// ---------------------------------------------------------------------------
//
void CAknVolumePopup::CleanupShowVolumePopup(TAny* aThis)
    {
    ((CAknVolumePopup*)aThis)->CloseVolumePopup();
    }


// ---------------------------------------------------------------------------
// CAknVolumePopup::CloseVolumePopup
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknVolumePopup::CloseVolumePopup()
    {
    if (iTimer)
        {
        iTimer->Cancel();
        }

    if (iVisible)
        {
        if( !Parent() && (iFlags == ENaviPaneVolumeControl ||
            iFlags == EDynRangeNaviPaneVolumeControl ))
            {
            DrawableWindow()->SetOrdinalPosition(0, ECoeWinPriorityNeverAtFront);
            }
    else if( !Parent() )
            {
            iWindowGroup.SetOrdinalPosition( 0, ECoeWinPriorityNeverAtFront );
            }
        
        TRAP_IGNORE( SetVisibilityL(EFalse) );
        }
    }

// ---------------------------------------------------------------------------
// CAknVolumePopup::SetVisibilityL
// ---------------------------------------------------------------------------
//
void CAknVolumePopup::SetVisibilityL(TBool aVisibility)
    {
    if (aVisibility)
        {
        iAvkonAppUi->UpdateStackedControlFlags(this, 0, ECoeStackFlagRefusesFocus);
        SetFocus(aVisibility);
        if (iVolume == 0 || iMuted )
            {
            if ( iMutedLabel )
                {                
                iMutedLabel->MakeVisible(ETrue);
                }

            if ( iExt->VolumeControl() )
                {
                iExt->VolumeControl()->MakeVisible(ETrue);
                }

            if ( iDecArrow && iIncArrow )
                {                
                iDecArrow->MakeVisible( EFalse );
                iIncArrow->MakeVisible( ETrue );                 
                }
            }
        else            
            {
            TInt min, max;
            GetRange( min, max );
                       
            if ( iMutedLabel )
                { 
                iMutedLabel->MakeVisible(EFalse);
                }
            if( iExt->VolumeControl() )
                {
                iExt->VolumeControl()->MakeVisible(ETrue);
                }
            }
        // "+" "-" switch on/off   
        if( iIncArrow && iDecArrow )
            {
            iIncArrow->MakeVisible( iAdjustmentIndicatorOn );
            iDecArrow->MakeVisible( iAdjustmentIndicatorOn );            
            }
        }
    else
        {
        iAvkonAppUi->UpdateStackedControlFlags(this, ECoeStackFlagRefusesFocus, ECoeStackFlagRefusesFocus);
        SetFocus(aVisibility);
        if( iExt->VolumeControl() )
            {
            iExt->VolumeControl()->MakeVisible(EFalse);
            }
        if ( iMutedLabel )
            { 
            iMutedLabel->MakeVisible(EFalse);
            }
        if ( iDecArrow && iIncArrow )
            {                
            iDecArrow->MakeVisible( EFalse );
            iIncArrow->MakeVisible( EFalse );                 
            }
        }
    if( iSpeaker )
        {
        iSpeaker->MakeVisible( aVisibility && !iExt->iSpeakerHidden );
        }
        
    if( iLabel )
        {
        iLabel->MakeVisible( aVisibility && iValueType != EAknSliderValueNone);
        }

    MakeVisible( aVisibility );

    if( iVisible != aVisibility )
        {
        //Capture pointer event via CAknWsEventMonitor
        CAknWsEventMonitor* eventMonitor = iAvkonAppUi->EventMonitor();
        if( eventMonitor )
            {
            if( aVisibility )
                {
                eventMonitor->AddObserverL( iExt );
                }
            else
                {
                eventMonitor->RemoveObserver( iExt );
                }
            eventMonitor->Enable( aVisibility );
            }
        }
        
    iVisible = aVisibility;
    if( !iVisible )
        {
        ReportEventL( MCoeControlObserver::EEventStateChanged );
        }
    }
    
// ---------------------------------------------------------------------------
// CAknVolumePopup::PositionChanged
// ---------------------------------------------------------------------------
//
void CAknVolumePopup::PositionChanged()
    {
    if ( iExt->iSliderUsed == KSliderUsed || iFlags == ESmallPopupVolumeControl || 
        iFlags == ESmallPopupVolumeControlWithPercent
         )
        {        
        // adjust popup so that if will fit into screen
        TRect appRect;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EApplicationWindow,
                                           appRect); 
        
        // subtract cba's rect if it is visible
        CCoeControl* cba = iAvkonAppUi->Cba();
        if( cba && cba->IsVisible() )
            {
            TAknWindowComponentLayout cbaLayout;
            TAknLayoutRect cbaRect;
            
            if( Layout_Meta_Data::IsLandscapeOrientation() )
                {
                cbaLayout = AknLayoutScalable_Avkon::area_side_right_pane( 0 );
                cbaRect.LayoutRect( appRect, cbaLayout );
                appRect.iBr.iX -= cbaRect.Rect().Width();
                }
            else
                {
                cbaLayout = AknLayoutScalable_Avkon::area_bottom_pane( 0 );
                cbaRect.LayoutRect( appRect, cbaLayout );
                appRect.iBr.iY -= cbaRect.Rect().Height();
                }
            }
        
        TPoint position = Position();
        if( !Parent() )
            {
            if ( Position().iX < appRect.iTl.iX )
                {
                position.iX = appRect.iTl.iX;
                }
            if ( Position().iY < appRect.iTl.iY )
                {
                position.iY = appRect.iTl.iY;
                }
            if ( Position().iX + Rect().Width() > appRect.iBr.iX )
                {
                position.iX = appRect.iBr.iX - Rect().Width();
                }
            if ( Position().iY + Rect().Height()> appRect.iBr.iY )
                {
                position.iY = appRect.iBr.iY - Rect().Height();
                }        
            }
        else
            {
            if ( PositionRelativeToScreen().iX < appRect.iTl.iX )
                {
                iPosition.iX = appRect.iTl.iX - Parent()->PositionRelativeToScreen().iX;
                }
            if ( PositionRelativeToScreen().iY < appRect.iTl.iY )
                {
                iPosition.iY = appRect.iTl.iY - Parent()->PositionRelativeToScreen().iY;
                }
            if ( PositionRelativeToScreen().iX + Rect().Width() > appRect.iBr.iX )
                {
                iPosition.iX = appRect.iBr.iX - Rect().Width() - Parent()->PositionRelativeToScreen().iX;
                }
            if ( PositionRelativeToScreen().iY + Rect().Height()> appRect.iBr.iY )
                {
                iPosition.iY = appRect.iBr.iY - Rect().Height() - Parent()->PositionRelativeToScreen().iY;
                } 
            }
        SetRect( TRect( position, Rect().Size() ) );
        }
    }

    
// ---------------------------------------------------------------------------
// CAknVolumePopup::Draw
// ---------------------------------------------------------------------------
//    
void CAknVolumePopup::Draw( CWindowGc &aGc, 
                            const CCoeControl& aControl, 
                            const TRect& ) const
    {
    /*when the slider's value is minium or maximum, of the user
      press up/down key, the marker will flick. when this happened,
      the background should be draw here, because the drawing is not
      trigered from drawing server.*/
      
    aGc.SetClippingRect( aControl.Rect() );
    
    TAknLayoutRect windowRect;
    
    windowRect.LayoutRect( iParentRect,
                       AknLayoutScalable_Avkon::bg_popup_sub_pane_cp22());  
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );

    TBool frameDrawn( EFalse );
    if ( CAknEnv::Static()->TransparencyEnabled() )
        {
        // the added flag removes the white bg for transparency
        frameDrawn = AknsDrawUtils::Background( skin, cc, this, aGc, 
                                                    aControl.Rect(), 
                                                    KAknsDrawParamNoClearUnderImage );
        }
    else
        {
        frameDrawn = AknsDrawUtils::Background( skin, cc, this, aGc, 
                                                    aControl.Rect() );
        
        }

    if( !frameDrawn )
        {
        aGc.SetBrushStyle( CGraphicsContext::ESolidBrush );
        aGc.SetPenStyle( CGraphicsContext::ENullPen );
        aGc.SetBrushColor( windowRect.Color() );
        aGc.DrawRect( windowRect.Rect() );
        }
    }
      
// ----------------------------------------------------------------------------
// CAknVolumePopup::SetGraphics
// ----------------------------------------------------------------------------
//
EXPORT_C void CAknVolumePopup::SetGraphics( TInt aElement, CFbsBitmap* aBitmap,
                                            CFbsBitmap* aMask )
    {
    if ( aElement < 0 || 
         aElement > EElemMinusButtonSelected || 
         !aBitmap ||
         ( aElement > CAknSlider::EElemMarkerSelected && 
           aElement < EElemSpeaker ) )
        {
        Panic( EAknPanicInvalidValue );
        }
    if( aElement >= EElemSpeaker )
        {
        TRAP_IGNORE( SetControlIconL( aElement,  aBitmap, aMask  ) );
        }
    else
        {
        iExt->SetGraphics( aElement, aBitmap, aMask );
        }              
    }
    
// ----------------------------------------------------------------------------
// CAknVolumePopup::MopSupplyObject
// ----------------------------------------------------------------------------
//    
TTypeUid::Ptr CAknVolumePopup::MopSupplyObject( TTypeUid aId )
    {
    if( aId.iUid == MAknsControlContext::ETypeId && iExt && iExt->iBgContext )
        {
        // Supply background skin context for scroll bars.
        return MAknsControlContext::SupplyMopObject( aId, iExt->iBgContext);
        }

    return CCoeControl::MopSupplyObject( aId );
    }        
// ----------------------------------------------------------------------------
// CAknVolumePopup::SetLabelColor
// ----------------------------------------------------------------------------
//    
void CAknVolumePopup::SetLabelColor()
    {
	TRgb color;
    MAknsSkinInstance *skin = AknsUtils::SkinInstance();
    TInt error = AknsUtils::GetCachedColor( skin,
                                            color,
                                            KAknsIIDQsnTextColors,
                                            EAknsCIQsnTextColorsCG19 );
    if ( !error )
        {
        TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( *iLabel,
                                                            EColorLabelText,
                                                            color) );
        }
    
    }

// ----------------------------------------------------------------------------
// CAknVolumePopup::ClosePopupWhenTapped
// ----------------------------------------------------------------------------
//    
EXPORT_C void CAknVolumePopup::ClosePopupWhenTappedOutside( TBool aEnable )
    {
    iExt->iClosePopupWhenTapped = aEnable;
    }
    
// ----------------------------------------------------------------------------
// CAknVolumePopup::SetDefaultValue
// ----------------------------------------------------------------------------
// 
EXPORT_C void CAknVolumePopup::SetDefaultValue( TInt aValue )
    {
    TInt min,max;
    GetRange( min, max );
    
     __ASSERT_DEBUG( aValue >= min &&
                     aValue<= max,
                     Panic( EAknPanicOutOfRange ) );
                     
    iExt->iDefaultValue = aValue;
    iExt->iHaveDefaultValue = ETrue;
    }

// ----------------------------------------------------------------------------
// CAknVolumePopup::EnableValueFieldTouch
// ----------------------------------------------------------------------------
// 
EXPORT_C void CAknVolumePopup::EnableResetViaValueField( TBool aEnabled )
    {
    iExt->iResetDefaultValue = aEnabled;
    }


//  End of File  
