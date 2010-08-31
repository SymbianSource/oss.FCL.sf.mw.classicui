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
* Description:  Stores attributes of note control. Since these attributes are
*                sometimes stored by the dialog before constructing the 
*                control, this class is the interface for passing attributes 
*                from the dialog to the control.
*
*/

#include <barsread.h>
#include <eikimage.h>
#include <eiklabel.h>
#include <eikprogi.h>

#include <avkon.hrh>
#include <avkon.mbg>
#include <avkon.rsg>

#include "AknPanic.h"
#include "aknconsts.h"

#include <aknprogresstimer.h>
#include <AknBitmapAnimation.h>

#include "aknnotecontrol.h"
#include <aknnoteattributes.h>
#include "akntextcontrol.h"

#include <AknsFrameBackgroundControlContext.h>
#include <AknsUtils.h>
#include <apgicnfl.h>

#include <AknsDrawUtils.h>
#include <AknsConstants.h>

#include <AknPictographInterface.h>
#include <AknPictographDrawerInterface.h>

#include <aknappui.h>
#include <aknlayoutscalable_avkon.cdl.h>

// FIXME: Experimental heuristics for finding out popup context from image/animation
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
#include <akntransitionutils.h>
#endif

/**
 * This constructor is called by the dialog
 */
CAknNoteAttributes::CAknNoteAttributes() : iSkinIdForImage(KAknsIIDNone)
    {
    InvalidateLayout();
    }

/**
 * This constructor is called by the control
 */
CAknNoteAttributes::CAknNoteAttributes(CAknNoteControl* aControl) : iNoteControl(aControl),  
    iSkinIdForImage(KAknsIIDNone)
    {
    InvalidateLayout();
    }

CAknNoteAttributes::~CAknNoteAttributes()
    {
    delete iNoteText;
    if ( iImage && iImage->IsPictureOwnedExternally() )
        {
        delete ((CApaMaskedBitmap*) iImage->Bitmap());
        }
    delete iImage;
    
    delete iImageFile;
    
    if ( iIcon && iIcon->IsPictureOwnedExternally() )
        {
        delete ((CApaMaskedBitmap*) iIcon->Bitmap());
        }   
    delete iIcon;

    delete iProgressBar;

    delete iTimer;    
    delete iAnimation;

    delete iBgContext; 
    delete iBrushAndPenContext;
    }

/*
* Copy attributes of aAttributes
* Called by dialog during prelayoutdyninit to transfer 
* attributes stored locally. Trasfer pointer ownership
*/
CAknNoteAttributes& CAknNoteAttributes::operator=(CAknNoteAttributes& aAttributes)
    {
    if (&aAttributes == this)
        return *this;

    if (aAttributes.iNoteText && iNoteText)
        *iNoteText = *aAttributes.iNoteText;

#define __TRANSFER_PTR_(P1,P2)  if (P1) { delete P2; P2 = P1; P1 = NULL; } 

    if ( aAttributes.iImage)
        {
        if ( iImage && iImage->IsPictureOwnedExternally())
            {
            delete ((CApaMaskedBitmap*) iImage->Bitmap());
            }
        __TRANSFER_PTR_(aAttributes.iImage,iImage);
        }

    if ( aAttributes.iIcon )
        {
        if ( iIcon && iIcon->IsPictureOwnedExternally() ) 
            {
            delete ((CApaMaskedBitmap*) iIcon->Bitmap());
            }
        __TRANSFER_PTR_(aAttributes.iIcon,iIcon);
        }   

    __TRANSFER_PTR_(aAttributes.iProgressBar,iProgressBar);

    __TRANSFER_PTR_(aAttributes.iTimer,iTimer);

    if (aAttributes.iAnimation)
        {
        iAnimationID = aAttributes.iAnimationID;
        }

    __TRANSFER_PTR_(aAttributes.iAnimation,iAnimation);


#undef __TRANSFER_PTR_
    
    iFlags.iFlags |= aAttributes.iFlags.iFlags; 

    //Flags that are cleared via the dialog API are stored in iClearFlags
    //and are used to cancel any flags that might have been set in the 
    //resource file (API has priority over resource file)
    iFlags.iFlags &= ~(aAttributes.iClearFlags.iFlags); 
    TRAP_IGNORE(TransferToControlL());
        
    InvalidateLayout();
    return *this;
    }

/**
* Transfer CCoeControl derived classed to CAknNoteControl by calling
* SetContainerWindowL for all CCoeControl owned classes
*/
void CAknNoteAttributes::TransferToControlL()
    {
    if (!iNoteControl)
        return;
    
    if (iNoteText)
        {
        iNoteText->SetContainerWindowL(*iNoteControl);
        
        TCallBack cb( StaticPictographCallBack, this );
        iNoteText->SetPictographCallBackL( cb );
        }

    if (iAnimation)
        iAnimation->SetContainerWindowL(*iNoteControl);
    
    if (iImage)
        iImage->SetContainerWindowL(*iNoteControl);
    
    if (iIcon)
        iIcon->SetContainerWindowL(*iNoteControl);

    if (iProgressBar)
        iProgressBar->SetContainerWindowL(*iNoteControl);
    }

void CAknNoteAttributes::TransferToControlL(CCoeControl* aControl)
    {
    if (iNoteControl && aControl)
        aControl->SetContainerWindowL(*iNoteControl);
    }


/*
* Construct attributes using resource file information
* Mainly called by control during initialisation
*/ 
void CAknNoteAttributes::ConstructFromResourceL(TResourceReader& aRes)
    {
    delete iNoteText;
    iNoteText = NULL;
	
	delete iImageFile;
	iImageFile = NULL;

    if ( !iBrushAndPenContext && iNoteControl )
        {
        iBrushAndPenContext=CCoeBrushAndPenContext::NewL();
        iBrushAndPenContext->SetBrushStyle(CGraphicsContext::ENullBrush);
        iNoteControl->SetControlContext(iBrushAndPenContext);        
        }
    iNoteText = CAknTextControl::NewL(CAknText::ENotFormatted);
    iNoteText->ConstructFromResourceL(aRes);

    TCallBack cb( StaticPictographCallBack, this );
    iNoteText->SetPictographCallBackL( cb );

    TransferToControlL(iNoteText);
    
    const TPtrC imageFile = aRes.ReadTPtrC();
    iImageFile = imageFile.AllocL();
    iImageId = aRes.ReadInt16();
    iImageMask = aRes.ReadInt16();
    
    const TPtrC iconFile = aRes.ReadTPtrC();
    const TInt iconId = aRes.ReadInt16();
    const TInt iconMask = aRes.ReadInt16();
    TInt animationId = aRes.ReadUint32();
    TInt flagIndexes = aRes.ReadInt16();
    
    TInt majorSkinIdForImage = EAknsMajorNone;
    TInt minorSkinIdForImage = EAknsMinorNone;
    
    iFlags.SetValue(flagIndexes);
       
    // Checks whether note is using AVKON_NOTE_SKINNED resource.
    if (iFlags.IsSet(ENoteWithSkinnableGraphics))
        {
        majorSkinIdForImage = aRes.ReadUint32();
        minorSkinIdForImage = aRes.ReadUint32();
        }

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    
    if (iImageFile->CompareF(KNullDesC) != 0)
        {
        iImage = new(ELeave) CEikImage;
        
        // Check for skin icon.
        if (iFlags.IsSet(ENoteWithSkinnableGraphics))
            {
            iSkinIdForImage.Set(majorSkinIdForImage, minorSkinIdForImage);
            }
        else
            {
            iSkinIdForImage = GetSkinnedBitmapID(iImageId);
            }

        CFbsBitmap* bitmap = NULL;
        CFbsBitmap* mask = NULL;
       
        AknsUtils::CreateIconL(
            skin, iSkinIdForImage,
            bitmap, mask,
            *iImageFile,
            iImageId, iImageMask);

        iImage->SetPicture(bitmap,mask);

        TransferToControlL(iImage);
        
// FIXME: Experimental heuristics for finding out popup context from image/animation
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
        // Check if the image file is the standard one
        if ( iImageFile->CompareF( AknIconUtils::AvkonIconFileName() ) == 0 )
            {
            switch ( iImageId )
                {
                case EMbmAvkonQgn_note_ok:
                    CAknTransitionUtils::SetData( ( TInt )iNoteControl, 
                        ( TAny* )KGfxConfirmationNoteControlUid.iUid );
                    break;
                case EMbmAvkonQgn_note_error:
                    CAknTransitionUtils::SetData( ( TInt )iNoteControl, 
                        ( TAny* )KGfxErrorNoteControlUid.iUid );
                    break;
                case EMbmAvkonQgn_note_info:
                    CAknTransitionUtils::SetData( ( TInt )iNoteControl, 
                        ( TAny* )KGfxInformationNoteControlUid.iUid );
                    break;
                case EMbmAvkonQgn_note_warning:
                    CAknTransitionUtils::SetData( ( TInt )iNoteControl, 
                        ( TAny* )KGfxWarningNoteControlUid.iUid );
                    break;
                case EMbmAvkonQgn_note_progress:
                    CAknTransitionUtils::SetData( ( TInt )iNoteControl, 
                        ( TAny* )KGfxWaitNoteControlUid.iUid );
                    break;
                default:
                    break;
                }
            }
#endif      
        }

    if (iconFile.CompareF(KNullDesC) != 0)
        {
        iIcon = new(ELeave) CEikImage;
        TAknsItemID id = GetSkinnedBitmapID(iconId);

        CFbsBitmap* bitmap = NULL;
        CFbsBitmap* mask = NULL;
       
        AknsUtils::CreateIconL(
            skin, id,
            bitmap, mask,
            iconFile,
            iconId, iconMask);
         
        iIcon->SetPicture(bitmap,mask);
        
        TransferToControlL(iIcon);
        }

    if (animationId != 0)
        {
        if (!iAnimation)
            {// no animation previously set
            SetAnimationL(animationId);
            }
        }
        
    if ( !iBgContext)
        {
        iBgContext = CAknsFrameBackgroundControlContext::NewL( 
            KAknsIIDQsnFrPopup, TRect(0,0,1,1), TRect(0,0,1,1), ETrue);
        }
    }

/**
* Set methods here, mainly used by CAknNoteControl exported API
* In brief, this is a private avkon implementation of the
* note control exported API (Set methods). The reason for
* implementing this API here is because the note dialog usually
* needs to call this API before the control is constructed.
* Therefore, the dialog can now use this API and then transfer
* the attributes from its locall instance of CAknNoteAttributes to
* an instance of CAknNoteAttributes owned by the control. This
* is done via the TransferL method as soon as the control as been 
* initialised.
*
*/  
    
/**
 * Set a new animation 
 *
 * Redo layout and full redraw (partial layout and redraw left
 * for future extensions)
 */
void CAknNoteAttributes::SetAnimationL(TInt aResourceId)
    {
    if (aResourceId <= 0)
        return;

    delete iAnimation;
    iAnimation = NULL;
    iAnimation = CAknBitmapAnimation::NewL();

    iAnimationID = aResourceId;

    if (iAnimationID == R_QGN_GRAF_WAIT_BAR_ANIM)
        {
        iAnimation->SetScaleModeForAnimationFrames(EAspectRatioNotPreserved);
        }

    CCoeEnv* coe = CCoeEnv::Static();

    TAknsItemID iid;
    iid.Set( EAknsMajorAvkon, aResourceId );
    
    TBool animation ( EFalse );
    TRAPD( err, animation = iAnimation->ConstructFromSkinL ( iid ) );
    
    if ( err != KErrNone || !animation )
        {
        TResourceReader readerForAnimation;
        coe->CreateResourceReaderLC(readerForAnimation,aResourceId);
        iAnimation->ConstructFromResourceL(readerForAnimation);
        CleanupStack::PopAndDestroy(); // readerForAnimation
        }

// FIXME: Experimental heuristics for finding out popup context from image/animation
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    switch ( aResourceId )
        {
        case EAknsMinorQgnNoteOkAnim:
            CAknTransitionUtils::SetData( ( TInt )iNoteControl, 
                ( TAny* )KGfxConfirmationNoteControlUid.iUid );
            break;
        case EAknsMinorQgnNoteErrorAnim:
            CAknTransitionUtils::SetData( ( TInt )iNoteControl, 
                ( TAny* )KGfxErrorNoteControlUid.iUid );
            break;
        case EAknsMinorQgnNoteInfoAnim:
            CAknTransitionUtils::SetData( ( TInt )iNoteControl, 
                ( TAny* )KGfxInformationNoteControlUid.iUid );
            break;
        case EAknsMinorQgnNoteWarningAnim:
            CAknTransitionUtils::SetData( ( TInt )iNoteControl, 
                ( TAny* )KGfxWarningNoteControlUid.iUid );
            break;
        case EAknsMinorQgnGrafBarWaitAnim:
            CAknTransitionUtils::SetData( ( TInt )iNoteControl, 
                ( TAny* )KGfxWaitNoteControlUid.iUid );
            break;
        default:
            break;
        }
#endif
    
    // If the image exists, but the dialog does not need it (is neither progress
    // nor wait dialog), delete the image
    if (iImage && iNoteControl->NoteLayout() != EProgressLayout &&
        iNoteControl->NoteLayout() != EWaitLayout )
        {
        delete iImage;
        iImage = NULL;
        }        

    TransferToControlL(iAnimation);
    if (iNoteControl)
        {
        iNoteControl->ParseTextL();
        }
    InvalidateLayout();    
    }

void CAknNoteAttributes::StartAnimationL()
    {
    if (iAnimation)
        {
        SetAnimationBackGroundFrameL();
        iAnimation->StartAnimationL();
        iAnimation->AnimationHasStarted( ETrue );
        iFlags.Set(ENoteAnimationStarted);
        }
    }

TInt CAknNoteAttributes::CancelAnimation()
    {
    iFlags.Clear(ENoteAnimationStarted);
    if (iAnimation)
        return iAnimation->CancelAnimation();
    else
        return KErrGeneral;
    }

/**
 * Set a new image 
 *
 * Redo layout and full redraw (partial layout and redraw left
 * for future extensions)
 */
void CAknNoteAttributes::SetImageL(CEikImage* aImage)
    { 
    TSize oldSize; 
    TRect oldRect;

    if (iImage)
        {
        oldSize = iImage->Bitmap()->SizeInPixels();
        oldRect = iImage->Rect();
        // skinned bitmaps behave badly..
        if ( iImage->IsPictureOwnedExternally() )
            {
            delete ((CApaMaskedBitmap*) iImage->Bitmap());
            }
        }

    delete iImage;
    iImage = aImage;

    // if animation is already set and it is not a waitbar - delete it
    if (iNoteControl && iNoteControl->NoteLayout() != EProgressLayout && iNoteControl->NoteLayout() != EWaitLayout )
        {
        delete iAnimation;
        iAnimation = NULL;
        }    

    if (iImage)
        {
        if (iNoteControl)
            { 
            TransferToControlL(iImage);
            iNoteControl->ReduceImageIfNeeded();

            TSize size(iImage->Bitmap()->SizeInPixels());
            if (size != TSize(0,0) && size == oldSize)
                {
                iImage->SetRect(oldRect);
                iImage->ActivateL();
                iImage->DrawNow();
                }
            else
                {
                iNoteControl->ParseTextL();
                InvalidateLayout();
                }
            }
        }
    }

/**
 * Set a new icon
 *
 * Redo layout and full redraw (partial layout and redraw left
 * for future extensions)
 */
void CAknNoteAttributes::SetIconL(CEikImage* aIcon)
    {
    if ( iIcon && iIcon->IsPictureOwnedExternally() )
        {
        delete ((CApaMaskedBitmap*) iIcon->Bitmap());
        }   
    delete iIcon;
    iIcon = aIcon;

    TransferToControlL(iIcon);
    if (iNoteControl)
        {
        iNoteControl->ParseTextL();
        }
    InvalidateLayout();
    }

//
// PROGRESS RELATED METHODS
//

void CAknNoteAttributes::SetFinalProgressValue(TInt aValue)
    {
    if (iProgressBar)
        iProgressBar->SetFinalValue(aValue);
    }

TInt CAknNoteAttributes::IncrementBarsAndDraw(TInt aIncrement)
    {
    if (!iProgressBar)
        return 0;

    TInt returnValue = 1;
    iProgressBar->IncrementAndDraw(aIncrement);
    CEikProgressInfo::SInfo info = iProgressBar->Info();
    if (iProgressBar->CurrentValue() == info.iFinalValue)
        returnValue = 0;
    return returnValue;
    }

void CAknNoteAttributes::CreateProgressBarL()
    {
    if (iProgressBar)
        {
        return;
        }

    TInt numLines = iNoteText->NumberOfLines();

    // New parameter added to Wait_or_progress_note_pop_up_window_elements_Line_2 layout API.
    TInt tIndex = 0;
    if (numLines == 3)
        {
        tIndex = 1;
        }
    if (numLines >= 4)
        {
        tIndex = 2;
        }
    TRect mainPane = iAvkonAppUi->ClientRect();
    TAknLayoutRect parent;
    
    AknLayoutUtils::TAknCbaLocation cbaLocation( AknLayoutUtils::CbaLocation() );
    TInt variety( 0 );
    
    if ( cbaLocation == AknLayoutUtils::EAknCbaLocationRight )
        {
        variety = 3;
        }
    else if ( cbaLocation == AknLayoutUtils::EAknCbaLocationLeft )
        {
        variety = 6;
        }
    else
        {
        variety = 0;
        }
        
    parent.LayoutRect(mainPane, AknLayoutScalable_Avkon::popup_note_wait_window( variety + tIndex ));
    
    TAknLayoutRect layRect;
    layRect.LayoutRect(parent.Rect(), AKN_LAYOUT_WINDOW_Wait_or_progress_note_pop_up_window_elements_Line_2(tIndex));
        
    CEikProgressInfo::SInfo info;
    info.iHeight = layRect.Rect().Height();//lay.iH;
    info.iWidth = layRect.Rect().Width();//lay.iW;
    
    info.iFinalValue = 1;
    info.iSplitsInBlock = 0;
    info.iTextType = EEikProgressTextNone;
    
    iProgressBar = new(ELeave) CEikProgressInfo(info);
    iProgressBar->ConstructL();
    
    TransferToControlL(iProgressBar);
    InvalidateLayout();
    }


//
// LABEL TEXT RELEATED SET METHODS
//

void CAknNoteAttributes::SetTextPluralityL(TBool aIsPlural)
    {
    if (!iNoteText)
        iNoteText = CAknTextControl::NewL();

    TInt numLines = iNoteText->NumberOfLines();
    iNoteText->SetTextPluralityL(aIsPlural);
    AttemptOptimizedTextDrawingL(numLines);
    }

void CAknNoteAttributes::SetTextNumberL(TInt aNumber)
    {
    if (!iNoteText)
        iNoteText = CAknTextControl::NewL();

    TInt numLines = iNoteText->NumberOfLines();
    iNoteText->SetTextNumberL(aNumber);
    AttemptOptimizedTextDrawingL(numLines);
    }

void CAknNoteAttributes::SetTextL(const TDesC& aText)
    {
    if (!iNoteText)
        iNoteText = CAknTextControl::NewL();

    TInt numLines = iNoteText->NumberOfLines();
    iNoteText->SetTextL(aText);
    AttemptOptimizedTextDrawingL(numLines);
    }

void CAknNoteAttributes::SetTextL(const TDesC& aText, TInt aLineNum, const CFont* aFont, CArrayFixFlat<TInt>* aLineWidths )
    {
    if (!iNoteText)
        iNoteText = CAknTextControl::NewL();

    TInt numLines = iNoteText->NumberOfLines();

    iNoteText->SetTextL(aText, aLineNum, aFont, aLineWidths);
    AttemptOptimizedTextDrawingL(numLines);
    }

TPtrC CAknNoteAttributes::Text() const
    {
    if (iNoteText)
        return iNoteText->Text();
    return TPtrC(0,0);
    }

void CAknNoteAttributes::ParseTextL(const CFont* aFont, CArrayFixFlat<TInt>* aLineWidths)
    {    
    if (!iNoteText)
        return;

    CAknTextControl::TWrapMethod mode;

    if (iFlags.IsSet(ENoteDoNotAllocateMem))
        {
        mode = CAknTextControl::ENoAllocation;
        }
    else if (iFlags.IsSet(ENoteNoTextProcessing))
        {
        mode = CAknTextControl::ENoProcessing;
        }
    else if (iFlags.IsSet(ENoteNoTextWrapping))
        {
        mode = CAknTextControl::ELine;
        }
    else
        {
        mode = CAknTextControl::EWord;
        }

    iNoteText->ParseTextL(aFont,aLineWidths,mode);
    }

void CAknNoteAttributes::AttemptOptimizedTextDrawingL(TInt aOldNumberOfLines)
    {
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = iBgContext;
    
    if (iNoteControl)
        {
        iNoteControl->ParseTextL();
        if (aOldNumberOfLines == iNoteText->NumberOfLines() && iAllowOptimizedDrawing )
            {
            for (TInt i=0; i < iNoteText->NumberOfLines(); i++)
                {
                if (iNoteText->LineModified(i))
                    {
                    TRect lineRect = iNoteText->Line(i)->Rect();
                    iNoteControl->Window().Invalidate( lineRect );
                    iNoteControl->ActivateGc();
                    iNoteControl->Window().BeginRedraw( lineRect );
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
                    AknsDrawUtils::Background( 
                        skin, cc, iNoteControl, iNoteControl->SystemGc(), iNoteText->Line(i)->Rect() );
#else                   
                    AknsDrawUtils::Background( 
                        skin, cc, iNoteControl, iNoteControl->iCoeEnv->SystemGc(), iNoteText->Line(i)->Rect() );
#endif
                    iNoteText->Line(i)->Draw( lineRect );

                    iNoteControl->Window().EndRedraw();
                    iNoteControl->DeactivateGc();

                    iNoteText->SetLineModified(i,EFalse);
                    }
                }
            }
        else
            {
            InvalidateLayout(); 
            }
        }
    }

TBool CAknNoteAttributes::IsLayoutNeeded(const TLayoutType& aType) const
    {
    __ASSERT_DEBUG(aType == EControl || aType == EDialog ,Panic(EAknPanicInvalidValue));
    if (aType == EControl)
        {
        return iFlags.IsSet(ENoteNeedLayoutControl);
        }
    else if (aType == EDialog)
        {
        return iFlags.IsSet(ENoteNeedLayoutDialog);
        }
    return EFalse; 
    }

void  CAknNoteAttributes::SetLayoutDone(const TLayoutType& aType)
    {
    __ASSERT_DEBUG(aType == EControl || aType == EDialog ,Panic(EAknPanicInvalidValue));
    if (aType == EControl)
        {
        iFlags.Clear(ENoteNeedLayoutControl);
        }
    else if (aType == EDialog)
        {
        iFlags.Clear(ENoteNeedLayoutDialog);
        }
    }

void CAknNoteAttributes::InvalidateLayout()
    {
    iFlags.Set(ENoteNeedLayoutControl);
    iFlags.Set(ENoteNeedLayoutDialog);
    }

EXPORT_C TAknsItemID CAknNoteAttributes::GetSkinnedBitmapID(TInt aIcon)
    {
    TAknsItemID id;
    id.Set(0,0);

    switch(aIcon)
        {
        case EMbmAvkonQgn_note_info:
            id = KAknsIIDQgnNoteInfo;
            break;

        case EMbmAvkonQgn_note_error:
            id = KAknsIIDQgnNoteError;
            break;

        case EMbmAvkonQgn_note_ok:
            id = KAknsIIDQgnNoteOk;
            break;

        case EMbmAvkonQgn_note_warning:
            id = KAknsIIDQgnNoteWarning;
            break;
        
        case EMbmAvkonQgn_note_query:
            id = KAknsIIDQgnNoteQuery; 
            break;

        case EMbmAvkonQgn_note_progress:
            id = KAknsIIDQgnNoteProgress;
            break;

        case EMbmAvkonQgn_note_alarm_calendar:
            id = KAknsIIDQgnNoteAlarmCalendar;
            break;

        case EMbmAvkonQgn_note_alarm_clock:
            id = KAknsIIDQgnNoteAlarmClock;
            break;

        case EMbmAvkonQgn_note_alarm_misc:
            id = KAknsIIDQgnNoteAlarmMisc;
            break;
        
        case EMbmAvkonQgn_note_batt_charging:
            id = KAknsIIDQgnNoteBattCharging;
            break;
        
        case EMbmAvkonQgn_note_batt_full:
            id = KAknsIIDQgnNoteBattFull;
            break;
        
        case EMbmAvkonQgn_note_batt_low:
            id = KAknsIIDQgnNoteBattLow;
            break;
        
        case EMbmAvkonQgn_note_batt_not_charging:
            id = KAknsIIDQgnNoteBattNotCharging;
            break;

        case EMbmAvkonQgn_note_batt_recharge:
            id = KAknsIIDQgnNoteBattRecharge;
            break;

        case EMbmAvkonQgn_note_erased:
            id = KAknsIIDQgnNoteErased;
            break;

        case EMbmAvkonQgn_note_keyguard:
            id = KAknsIIDQgnNoteKeyguard;
            break;

        case EMbmAvkonQgn_note_call:
            id = KAknsIIDQgnNoteCall;
            break;

        case EMbmAvkonQgn_note_copy:
            id = KAknsIIDQgnNoteCopy;
            break;

        case EMbmAvkonQgn_note_im_message:
            id = KAknsIIDQgnNoteImMessage;
            break;

        case EMbmAvkonQgn_note_mail:
            id = KAknsIIDQgnNoteMail;
            break;

        case EMbmAvkonQgn_note_message:
            id = KAknsIIDQgnNoteMessage;
            break;

        case EMbmAvkonQgn_note_mms:
            id = KAknsIIDQgnNoteMms;
            break;

        case EMbmAvkonQgn_note_move:
            id = KAknsIIDQgnNoteMove;
            break;

        case EMbmAvkonQgn_note_remote_mailbox:
            id = KAknsIIDQgnNoteRemoteMailbox;
            break;

        case EMbmAvkonQgn_note_sml:
            id = KAknsIIDQgnNoteSml;
            break;

        case EMbmAvkonQgn_note_voice:
            id = KAknsIIDQgnNoteVoice;
            break;

        case EMbmAvkonQgn_note_voice_found:
            id = KAknsIIDQgnNoteVoiceFound;
            break;

        case EMbmAvkonQgn_note_warr:
            id = KAknsIIDQgnNoteWarr;
            break;

        default:
            break;
        }
    return id;
    }

void CAknNoteAttributes::SetAnimationBackGroundFrameL()
    {
    // R_QGN_GRAF_WAIT_BAR_ANIM case is OK without background frame.
    if (iAnimation && iAnimationID != R_QGN_GRAF_WAIT_BAR_ANIM)
        {
        // Not set background frame, if there is only one frame in animation.
        CBitmapAnimClientData *animClientData = iAnimation->BitmapAnimData();
        if (animClientData != NULL && animClientData->FrameArray().Count() <= 1)
            {
            return;
            }
    
        const TDisplayMode displayMode( CCoeEnv::Static()->ScreenDevice()->DisplayMode() );

        // Create skinned background frame
        
        CFbsBitmap* bitmap = new(ELeave) CFbsBitmap;
        CleanupStack::PushL(bitmap);
        
        User::LeaveIfError( bitmap->Create( iAnimation->Rect().Size(), displayMode ) );
        
        CFbsBitmapDevice* doubleBufferDev = CFbsBitmapDevice::NewL( bitmap );
        CleanupStack::PushL(doubleBufferDev);    
        
        CFbsBitGc* doubleBufferGc = 0;
        User::LeaveIfError( doubleBufferDev->CreateContext( doubleBufferGc ) );    
        CleanupStack::PushL(doubleBufferGc);    
        
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        MAknsControlContext* cc = iBgContext;
        
        AknsDrawUtils::DrawBackground( skin, cc, iNoteControl, *doubleBufferGc,
            TPoint(0,0), iAnimation->Rect(), KAknsDrawParamDefault );
#if 0              
        // waitbar background border
        if ( iAnimationID == R_QGN_GRAF_WAIT_BAR_ANIM )
            {   
            CFbsBitmap* frameL = NULL;
            CFbsBitmap* frameCenter = NULL;
            CFbsBitmap* frameR = NULL;
            CFbsBitmap* lMask = NULL;
            CFbsBitmap* centerMask = NULL;
            CFbsBitmap* rMask = NULL;
            
            AknIconUtils::CreateIconLC( frameL, lMask, KAvkonBitmapFile, EMbmAvkonQgn_graf_bar_frame_side_l, EMbmAvkonQgn_graf_bar_frame_side_l_mask  );
            AknIconUtils::CreateIconLC( frameCenter, centerMask, KAvkonBitmapFile, EMbmAvkonQgn_graf_bar_frame_center, EMbmAvkonQgn_graf_bar_frame_center_mask);
            AknIconUtils::CreateIconLC( frameR, rMask, KAvkonBitmapFile, EMbmAvkonQgn_graf_bar_frame_side_r, EMbmAvkonQgn_graf_bar_frame_side_r_mask  );

            TAknLayoutRect frameGraphicLayout;
            
            frameGraphicLayout.LayoutRect( iAnimation->Rect(), AknLayoutScalable_Avkon::wait_border_pane_g1() );            
            User::LeaveIfError( AknIconUtils::SetSize( frameL, frameGraphicLayout.Rect().Size(), EAspectRatioNotPreserved ) );

            frameGraphicLayout.LayoutRect( iAnimation->Rect(), AknLayoutScalable_Avkon::wait_border_pane_g2() );
            User::LeaveIfError( AknIconUtils::SetSize( frameCenter, frameGraphicLayout.Rect().Size(), EAspectRatioNotPreserved ) );

            frameGraphicLayout.LayoutRect( iAnimation->Rect(), AknLayoutScalable_Avkon::wait_border_pane_g3() );
            User::LeaveIfError( AknIconUtils::SetSize( frameR, frameGraphicLayout.Rect().Size(), EAspectRatioNotPreserved ) );
               
            TPoint centerPoint( frameL->SizeInPixels().iWidth, 0 );
            TPoint rightPoint( centerPoint.iX + frameCenter->SizeInPixels().iWidth, 0 );

            doubleBufferGc->BitBltMasked( TPoint( 0, 0), frameL, 
                                          TRect( TPoint( 0, 0 ), frameL->SizeInPixels() ),
                                          lMask, EFalse );

            doubleBufferGc->BitBltMasked( centerPoint, frameCenter, 
                                          TRect( frameCenter->SizeInPixels() ),
                                          centerMask, EFalse );

            doubleBufferGc->BitBltMasked( rightPoint, frameR, 
                                          TRect( frameR->SizeInPixels() ),
                                          rMask, EFalse );

            CleanupStack::PopAndDestroy( 6 );
            if ( iAnimation->BitmapAnimData()->PlayMode() == CBitmapAnimClientData::EPlay )
                iAnimation->BitmapAnimData()->SetPlayMode(CBitmapAnimClientData::ECycle);
            }  
#endif
            
        CleanupStack::PopAndDestroy(2); // doubleBufferGc, doubleBufferDev
   
        // finally set background frame
        CBitmapFrameData* data = CBitmapFrameData::NewL();
        data->SetBitmapsOwnedExternally( EFalse );
        data->SetBitmap( bitmap );
        
        // Set frame to animation
        iAnimation->BitmapAnimData()->SetBackgroundFrame( data ); // gets ownership
        
        CleanupStack::Pop(bitmap); // bitmap
        }       
    }

// Callback for doing a redraw when animating pictographs
TInt CAknNoteAttributes::StaticPictographCallBack( TAny* aPtr )
    {
    CAknNoteAttributes* me = static_cast<CAknNoteAttributes*>( aPtr );
    me->PictographCallBack();
    return KErrNone;
    }

void CAknNoteAttributes::PictographCallBack()
    {
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = iBgContext;

    for ( TInt i = 0 ; i < iNoteText->NumberOfLines() ; i++ )
        {
        CAknPictographInterface* picto = iNoteText->PictographInterface();

        // Only update the note line if it contains pictographs

        if ( picto->Interface()->ContainsPictographs( 
            *( iNoteText->Line( i )->Text() ) ) )
            {
            TRect lineRect = iNoteText->Line(i)->Rect();
            iNoteControl->Window().Invalidate( lineRect );

            iNoteControl->ActivateGc();
            iNoteControl->Window().BeginRedraw();

            AknsDrawUtils::Background(
                skin,
                cc,
                iNoteControl,
                iNoteControl->iCoeEnv->SystemGc(),
                lineRect );

            iNoteControl->Window().EndRedraw();
            iNoteControl->DeactivateGc();

            // Redraw the label after the background
            iNoteText->Line( i )->ActivateL(); // Never leaves
            iNoteText->Line( i )->DrawNow();
            iNoteText->SetLineModified( i, EFalse );
            }
        }
    }

void CAknNoteAttributes::AllowOptimizedDrawing()
    {
    iAllowOptimizedDrawing = ETrue;
    }
    
void CAknNoteAttributes::HandleSkinChangeL()
    {
    // Reload animation every time
    SetAnimationL(iAnimationID);
    
    // iImageId is null with no sense
    if (!iImage || !iImageFile || !iImageId)
        {
        return;
        }
    
    // Check for skin icon.
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;
   
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
   
    AknsUtils::CreateIconL(
        skin, 
        iSkinIdForImage,
        bitmap, 
        mask,
        *iImageFile,
        iImageId, 
        iImageMask);

    if (iImage->IsPictureOwnedExternally())
        {
        delete ((CApaMaskedBitmap*) iImage->Bitmap());
        }

    iImage->SetPicture(bitmap, mask);    
    }

// End of File
