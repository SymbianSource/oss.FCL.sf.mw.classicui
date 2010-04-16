/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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

// AKNBITMAPANIMATION.CPP
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//
#include <barsread.h>
#include <eikenv.h>
#include <fbs.h>
#include <AknBitmapAnimation.h>
#include <bmpanconsts.h>
#include <AknsUtils.h>
#include <AknsItemDef.h>
#include <AknIconUtils.h>
#include <AknPanic.h>
#include <AknUtils.h>

#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
#include <akntransitionutils.h>
#include <avkondomainpskeys.h>
#include <e32property.h>
#endif

// CONSTANTS

// The value for this frame delay interval should be kept big
// enough because otherwise the first and (only) frame of the animation
// will not be shown at all by bitmap animation framework.
// This value is used only in skin forward comparability purposes.
const TInt KSkinForwardCompatibilityFrameDelayInterval = 1000;

#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
const TInt KWaitForUiEffectDelay = 50000;
#endif

RAknBitmapAnim::RAknBitmapAnim(RAnimDll& aAnimDll)
: RBitmapAnim(aAnimDll)
	{
	}

TInt RAknBitmapAnim::Stop()
	{
	return CommandReply(EBitmapAnimCommandStopAnimation);
	}

void RAknBitmapAnim::StartAndKeepLastFrameL()
	{
	User::LeaveIfError(CommandReply(EBitmapAnimCommandStartAnimationAndKeepLastFrame));
	}

enum TInternalFlags
	{
	EInitialisationCompleted	     =	0x0001,
	EAnimationStarted			     =	0x0002,
	EAnimationFinished			     =	0x0004,
	EAnimationTimerStarted           =	0x0008,
    EAnimationExcludeFramesFromCache =  0x0010,
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    EWaitingForUiEffect              =  0x0020,
#endif
    EAnimationSingleFrame            =  0x0040
	};

enum TAknAnimationPanic
	{
	EAknPanicAnimationNoControlContext,
	EAknPanicAnimationNoRAnimation,
	EAknPanicAnimationNoWindow,
	EAknPanicAnimationMethodToBeRemoved
	};

GLDEF_C void Panic(TAknAnimationPanic aPanic)
	{
	_LIT(KPanicCat,"Animation");
	User::Panic(KPanicCat, aPanic);
	}

const TInt KConversionFromMillisecondsToMicroseconds = 1000;

//
//
EXPORT_C CAknBitmapAnimation* CAknBitmapAnimation::NewL()
	{ // static
	CAknBitmapAnimation* self=new(ELeave) CAknBitmapAnimation();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self;
	}

CAknBitmapAnimation::CAknBitmapAnimation() :
	iAnimDll(iEikonEnv->WsSession()),
	iAnimation(iAnimDll),
	iScaleModeFrames(EAspectRatioPreserved),
    iScaleModeBackgroundFrame(EAspectRatioPreserved)
	{
	}

EXPORT_C CAknBitmapAnimation::~CAknBitmapAnimation()
	{
    CancelAnimation();
	delete iTimer;
	iAnimation.Close();
	delete iBitmapAnimData;
	iAnimDll.Close();
	}

EXPORT_C RBitmapAnim& CAknBitmapAnimation::Animation()
	{
	return iAnimation;
	}

EXPORT_C CBitmapAnimClientData* CAknBitmapAnimation::BitmapAnimData() const
	{
	return iBitmapAnimData;
	}
//
//
void CAknBitmapAnimation::ConstructL()
	{
	iBitmapAnimData = CBitmapAnimClientData::NewL();
	_LIT(DllName, "Z:\\SYS\\BIN\\BMPANSRV.DLL");
	User::LeaveIfError(iAnimDll.Load(DllName));
	iTimer = CPeriodic::NewL(CActive::EPriorityStandard);
	}
//
// 

void CAknBitmapAnimation::Draw(const TRect& /*aRect*/) const
	{
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
	CWindowGc& gc = SystemGc();
	CWindowGc& coegc = iCoeEnv->SystemGc();
	TBool hascustomgc = (&gc != &coegc);
	TInt frameCount( BitmapAnimData()->FrameArray().Count() );
	if ( frameCount > 0 && ( ( iFlags & EAnimationStarted ) || iGainedFocus || 
	     hascustomgc ) )
		{
        gc.Reset();		
#else 
    TInt frameCount( BitmapAnimData()->FrameArray().Count() );  
	if ( ( iFlags & EAnimationStarted ) || iGainedFocus )
		{
		CWindowGc& gc=SystemGc();
        gc.Reset();		
#endif

		TInt endFrame = frameCount - 1;
		if (0 <= endFrame)
		    {
    		TPoint pos = BitmapAnimData()->FrameArray().At(endFrame)->Position();
    		pos += Position();
    		CFbsBitmap* bit  = BitmapAnimData()->FrameArray().At(endFrame)->Bitmap();
    		CFbsBitmap* mask = BitmapAnimData()->FrameArray().At(endFrame)->Mask();

    		if (mask)
    			{
    			gc.BitBltMasked(pos,bit,TRect(TPoint(0,0),bit->SizeInPixels()),mask,ETrue);
    			}
    		else
    			{
    			gc.BitBlt(pos,bit,TRect(TPoint(0,0),bit->SizeInPixels()));
    			}
		    }
		}
	}


void CAknBitmapAnimation::FocusChanged(TDrawNow /*aDrawNow*/)
    {
	if ( BitmapAnimData()->FrameArray().Count() == 1 )
	    {
	    // focus loss and gain may cause the animation not to appear in
	    // confirmation queries -> draw one frame animation also here
        if ( IsFocused() )
            {
            DrawDeferred();
            iGainedFocus = ETrue;
            }
        else
            {
            iGainedFocus = EFalse;
            }
	    }
    }

// -----------------------------------------------------------------------------
// CAknBitmapAnimation::ConstructFromSkinL
// (documented in the header).
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CAknBitmapAnimation::ConstructFromSkinL( 
    const TAknsItemID& aItemID )
    {
    TBool unknownPlayMode = EFalse;
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    if( !skin ) 
        {
        User::Leave( KErrNotSupported );
        }

    CAknsBmpAnimItemData* animData = static_cast<CAknsBmpAnimItemData*>(
        skin->CreateUncachedItemDataL( aItemID, EAknsITBmpAnim ) );
    if( !animData ) 
        {
        return EFalse;
        }
    CleanupStack::PushL( animData );

    iBitmapAnimData->SetFrameInterval( animData->FrameInterval() );
    
    CBitmapAnimClientData::TPlayMode playMode = static_cast<CBitmapAnimClientData::TPlayMode>(animData->PlayMode());
    
    if (playMode != CBitmapAnimClientData::EPlay &&
		playMode != CBitmapAnimClientData::ECycle &&
		playMode != CBitmapAnimClientData::EBounce)
		{
		unknownPlayMode = ETrue;
		playMode = CBitmapAnimClientData::EPlay;    		
		
		if (!animData->FrameInterval())
			{
			iBitmapAnimData->SetFrameInterval(KSkinForwardCompatibilityFrameDelayInterval);    			
			}
		}
    
    iBitmapAnimData->SetPlayMode(playMode);
    iBitmapAnimData->SetFlash( animData->Flash() );
    iBitmapAnimData->ResetFrameArray();

    TAknsBmpAnimFrameInfo* frameInfos = animData->FrameInfos();

    TBool result = ETrue;

    TInt n = animData->NumberOfImages();
    for( TInt i=0; i<n; i++ )
        {
        CAknsBitmapItemData* bmpData = static_cast<CAknsBitmapItemData*>(
            skin->CreateUncachedItemDataL( animData->ImageIID( i ), EAknsITBitmap ) );
        CleanupStack::PushL( bmpData );
        
        if( bmpData )
            {
            CBitmapFrameData* targetFrameData = CBitmapFrameData::NewL( 
                bmpData->Bitmap() );
            bmpData->SetBitmap( NULL ); // Detaches ownership

            if( bmpData->Type() == EAknsITMaskedBitmap )
                {
                CAknsMaskedBitmapItemData* maskedData = 
                    static_cast<CAknsMaskedBitmapItemData*>( bmpData );
                targetFrameData->SetMask( maskedData->Mask() );
                maskedData->SetMask( NULL ); // Detaches ownership
                }            

            if( frameInfos )
                {
    			// if the playmode is not recognized the frame interval should be set to -1
                // this way the frame internal set on animation level takes precedence
                targetFrameData->SetInterval( (unknownPlayMode?-1:frameInfos[i].iTime) );
                targetFrameData->SetPosition( TPoint(
                    frameInfos[i].iPosX, frameInfos[i].iPosY ) );
                }
        
            if( (i==n-1) && animData->LastFrameBackground() )
                {
                iBitmapAnimData->SetBackgroundFrame( targetFrameData );
                }
            else
                {
                CleanupStack::PushL( targetFrameData );
                iBitmapAnimData->AppendFrameL( targetFrameData );
                CleanupStack::Pop(); // targetFrameData
                }
            }
        else
            {
            result = EFalse;
            }

        CleanupStack::PopAndDestroy(); // bmpData
        }

    CleanupStack::PopAndDestroy(); // animData
    return result;
    }

EXPORT_C void CAknBitmapAnimation::ConstructFromResourceL(TResourceReader& aReader)
	{
    // Read identifier byte. It may be used later to identify the used resource struct.
    TInt8 identifier = aReader.ReadInt8();
    __ASSERT_DEBUG( identifier <= KAknBMPAnimVersion, Panic( EAknPanicNotSupported ) );

	if (identifier == KAknBMPAnimVersion)
	    {
        TAknsItemID iid;
        iid.Set( EAknsMajorAvkon, aReader.ReadInt32());
        if (ConstructFromSkinL(iid))
            {
        	iBitmapAnimData->SetFrameInterval(aReader.ReadInt16());
            iBitmapAnimData->SetPlayMode((CBitmapAnimClientData::TPlayMode)aReader.ReadInt16());
            iBitmapAnimData->SetFlash(aReader.ReadInt8());
            aReader.ReadTPtrC(); // filename
            aReader.ReadInt32(); // frames                                              
            aReader.ReadInt32(); // background frame data                                                  
            if ( iBitmapAnimData->FrameArray().Count() == 1 )
                {
                iFlags |= EAnimationSingleFrame;
                iFlags |= EInitialisationCompleted;
                }                
            return;
            }
	    }

	iBitmapAnimData->SetFrameInterval(aReader.ReadInt16());
	iBitmapAnimData->SetPlayMode((CBitmapAnimClientData::TPlayMode)aReader.ReadInt16());
	iBitmapAnimData->SetFlash(aReader.ReadInt8());
	iBitmapAnimData->ResetFrameArray();
	
	TFileName appName(aReader.ReadTPtrC()); // filename
	if (appName.Length())
	    {
	    TInt err = CompleteWithAppPath(appName);
	    if (err != KErrNotSupported)
    	    User::LeaveIfError(err);	
	    }

// Start reading the data frames
    TInt listFrameLink=aReader.ReadInt32();
	if (listFrameLink)
		{
		TResourceReader framesReader;
		iCoeEnv->CreateResourceReaderLC(framesReader, listFrameLink);
		const TInt count=framesReader.ReadInt16();
		CBitmapFrameData* frameData = NULL;
		for (TInt ii=0;ii<count;++ii)
			{
			//read the frame data from resource
			frameData = CreateFrameDataFromResourceL(framesReader, appName, identifier);
			CleanupStack::PushL(frameData);
			iBitmapAnimData->AppendFrameL(frameData);
			CleanupStack::Pop(frameData);
			}
		CleanupStack::PopAndDestroy();
		}
// Start reading the background frame data
    TInt backgroundFrameLink=aReader.ReadInt32();
	if (backgroundFrameLink)
		{
		TResourceReader framesReader;
		iCoeEnv->CreateResourceReaderLC(framesReader, backgroundFrameLink);
		const TInt count=framesReader.ReadInt16();
		CBitmapFrameData* frameData = NULL;
		for (TInt ii=0;ii<count;++ii)
			{
			//read the background frame from resource
			frameData = CreateFrameDataFromResourceL(framesReader, appName, identifier);
			iBitmapAnimData->SetBackgroundFrame(frameData);
			}
		CleanupStack::PopAndDestroy();
		}
	if ( iBitmapAnimData->FrameArray().Count() == 1 )
	    {
	    iFlags |= EAnimationSingleFrame;
	    iFlags |= EInitialisationCompleted;
	    }
	}


//
//
CBitmapFrameData* CAknBitmapAnimation::CreateFrameDataFromResourceL(TResourceReader& aFramesReader,
                                                                    const TDesC& aFileName,
                                                                    const TInt8 aVersion)
	{
	CBitmapFrameData* frameData = CBitmapFrameData::NewL();
	CleanupStack::PushL(frameData);
	frameData->SetInterval(aFramesReader.ReadInt16());
	TPoint position;
	position.iX = aFramesReader.ReadInt16();
	position.iY = aFramesReader.ReadInt16();
	frameData->SetPosition(position);
	const TInt bmpId = aFramesReader.ReadInt16();
	const TInt maskId = aFramesReader.ReadInt16();
	CFbsBitmap *bitmap, *mask;
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

	if (bmpId >= 0 && maskId>= 0)
		{
		if (aVersion == KAknBMPAnimVersion)
		    {
            TAknsItemID iid;
            TInt major = aFramesReader.ReadInt32();
            TInt minor = aFramesReader.ReadInt32();
            iid.Set( major, minor);
    		AknsUtils::CreateIconLC(skin, iid, bitmap, mask, aFileName, bmpId, maskId);
		    }
		else
		    {
            AknIconUtils::CreateIconLC(bitmap, mask, aFileName, bmpId, maskId);
		    }
		frameData->SetBitmap(bitmap);
		frameData->SetMask(mask);
		CleanupStack::Pop(2); // bitmap, mask
		}
	else if (bmpId >= 0)		
		{
		bitmap = AknIconUtils::CreateIconL(aFileName, bmpId);
		frameData->SetBitmap(bitmap);
		}
	else
		{
		// Do nothing. Panic can also be considered here.				
		}		
	CleanupStack::Pop(frameData); //frameData
	return frameData;
	}

//
//
EXPORT_C TInt CAknBitmapAnimation::CancelAnimation()
	{
#ifdef _DEBUG
        RDebug::Print(_L("CAknBitmapAnimation::CancelAnimation instance:%x"),this);
#endif //_DEBUG
    TInt err = 0;

#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
	if(!(iFlags & EWaitingForUiEffect))
		{
#endif
    if ( ( iFlags & EAnimationStarted // callback completed 
        || iFlags &EAnimationTimerStarted ) // animation is started, but callback not yet complete
        && !( iFlags & EAnimationSingleFrame ) )
        {
    	err = iAnimation.Stop(); 
        }
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
		}
	iFlags &= ~EWaitingForUiEffect;
#endif
    if (iTimer)
		{
		iTimer->Cancel();
		iFlags &= ~EAnimationTimerStarted;
		}

	iFlags &= ~EAnimationStarted;
    return err;
	}

//
//
void CAknBitmapAnimation::CompleteAnimationInitialisationL()
	{
	SetAnimationWindowL();
	iAnimation.SetBitmapAnimDataL(*iBitmapAnimData);
	iAnimation.SetPositionL(iPosition);
	iFlags |= EInitialisationCompleted;
	}

//
//
TBool CAknBitmapAnimation::IsInitialisationCompleted() 
	{ 
	return iFlags&EInitialisationCompleted;
	}

//
//
EXPORT_C TSize CAknBitmapAnimation::MinimumSize()
	{
	return iBitmapAnimData->Size();
	}

//
//
void CAknBitmapAnimation::PositionChanged()
	{
	if (IsInitialisationCompleted())
		{
		TRAP_IGNORE(iAnimation.SetPositionL(iPosition));
		}
	}

//
//
void CAknBitmapAnimation::SetAnimationWindowL()
	{
	iAnimation.ConstructL(Window());
	}

//
EXPORT_C void CAknBitmapAnimation::SetFrameIndexL(TInt aIndex)
	{
	if (!IsInitialisationCompleted())
		CompleteAnimationInitialisationL();
	if ( !( iFlags & EAnimationSingleFrame ) )
	    {
	    iAnimation.DisplayFrameL(aIndex);
	    }
	}

//
EXPORT_C void CAknBitmapAnimation::SetFrameIntervalL(TInt aFrameIntervalInMilliSeconds)
	{
	if (!IsInitialisationCompleted())
		CompleteAnimationInitialisationL();
	iAnimation.SetFrameIntervalL(aFrameIntervalInMilliSeconds);
	}
//
//
void CAknBitmapAnimation::SizeChanged()
	{
#ifdef _DEBUG
        RDebug::Print(_L("CAknBitmapAnimation::SizeChanged instance:%x"),this);
#endif //_DEBUG
	// background frame needs also to be resized
	if (BitmapAnimData()->BackgroundFrame())
	{				
		CFbsBitmap* bit  = BitmapAnimData()->BackgroundFrame()->Bitmap();
		if (iFlags & EAnimationExcludeFramesFromCache)
		    {
		    AknIconUtils::ExcludeFromCache(bit);
		    }
		AknIconUtils::SetSize(bit, Rect().Size(),iScaleModeBackgroundFrame);
	}

	TInt endFrame = BitmapAnimData()->FrameArray().Count()-1;
	for (TInt i=0;i<=endFrame;i++)
		{
		CFbsBitmap* bit  = BitmapAnimData()->FrameArray().At(i)->Bitmap();
		if (iFlags & EAnimationExcludeFramesFromCache)
		    {
		    AknIconUtils::ExcludeFromCache(bit);
		    }
		AknIconUtils::SetSize(bit, Rect().Size(),iScaleModeFrames);
		}
	}

#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
LOCAL_C TInt WaitForUiEffect(TAny* aArg)
	{
	CAknBitmapAnimation* self = (CAknBitmapAnimation*)aArg;
	self->StartAnimationL();
	return EFalse;
	}
#endif

//
//
EXPORT_C void CAknBitmapAnimation::StartAnimationL()
	{
#ifdef _DEBUG
        RDebug::Print(_L("CAknBitmapAnimation::StartAnimationL instance:%x"),this);
#endif //_DEBUG
        
    if ( iFlags & EAnimationSingleFrame )
        {
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS  
        iFlags &= ~EWaitingForUiEffect;
#endif        
        iFlags |= EAnimationStarted;       
        DrawDeferred();
        return;
        }

#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
	TInt redirectstatus = 0;
    RProperty::Get(KPSUidAvkonDomain, KAknTfxServerRedirectionStatus, redirectstatus );
    TBool isredirected = (redirectstatus & ETfxScreenRedirected);
    
    // this is executed as long as transition is running, then the aknbitmapanimation
    // switches to "normal" mode and WaitForUiEffect callback isn't called anymore
    if(  CAknTransitionUtils::GetData(EDontAnimateBitmaps) || isredirected )
    	{
    	if( !(iFlags & EAnimationTimerStarted) && !( iFlags & EWaitingForUiEffect ) )
	    	{
	     	iFlags |= EWaitingForUiEffect;
			TCallBack callback(WaitForUiEffect, this);
			iTimer->Cancel();
			iTimer->Start(KWaitForUiEffectDelay, KWaitForUiEffectDelay, callback); 
	    	}
    	}
    else
    	{
    	iFlags &= ~EWaitingForUiEffect;
#endif
		if (!IsInitialisationCompleted())
			{
			CompleteAnimationInitialisationL();
			}
		else
	        {
	        // Otherwise, update animation data since it may have changed
	        iAnimation.SetBitmapAnimDataL(*iBitmapAnimData);
		        // This call updates the cached background frame content for the animation.
		        // It is also very important to call this function only after calling
		        // iAnimation.SetBitmapAnimDataL()
		        iAnimation.SetPositionL(iPosition);
	        }
		iAnimation.StartAndKeepLastFrameL();
		if (!(iFlags & EAnimationTimerStarted))
			{ // if animation timer has not started, start timer
			TCallBack callback(AnimationStartedCallback, this);
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
            iTimer->Cancel(); //when popup animations are enabled the timer might already be started
#endif //RD_UI_TRANSITION_EFFECTS_POPUPS
			iTimer->Start(iBitmapAnimData->DurationInMilliSeconds()*KConversionFromMillisecondsToMicroseconds/2, 1/*just the once*/, callback); // a delay of half the animation time
			iFlags |= EAnimationTimerStarted;
			}
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    	}
#endif		
	}


// -----------------------------------------------------------------------------
// CAknBitmapAnimation::SetScaleModeForAnimationFrames
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknBitmapAnimation::SetScaleModeForAnimationFrames(TScaleMode aMode)
    {
	iScaleModeFrames = aMode;
    }

// -----------------------------------------------------------------------------
// CAknBitmapAnimation::SetScaleModeForAnimationBackgroundFrame
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknBitmapAnimation::SetScaleModeForAnimationBackgroundFrame(TScaleMode aMode)
    {
    iScaleModeBackgroundFrame = aMode;
    }

// -----------------------------------------------------------------------------
// CAknBitmapAnimation::ExcludeAnimationFramesFromCache
// -----------------------------------------------------------------------------
//    
EXPORT_C void CAknBitmapAnimation::ExcludeAnimationFramesFromCache()
    {
    iFlags |= EAnimationExcludeFramesFromCache;
    }

TInt CAknBitmapAnimation::AnimationHasStarted(TBool aHasStarted)
	{
	if (aHasStarted)
	    {
	    iFlags |= EAnimationStarted;
	    DrawDeferred();
	    }
	if (iTimer)

#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS	
if( !( iFlags & EWaitingForUiEffect ) )
	{
	iTimer->Cancel();
	}
#else
	iTimer->Cancel();
#endif
	return KErrNone;
	}

TInt CAknBitmapAnimation::AnimationStartedCallback(TAny* aPtr)
	{
	CAknBitmapAnimation* ptr = (CAknBitmapAnimation*)aPtr;
	return ptr->AnimationHasStarted(ETrue);
	}
