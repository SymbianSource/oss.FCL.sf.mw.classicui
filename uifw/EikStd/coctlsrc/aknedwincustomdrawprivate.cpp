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


// INCLUDE FILES
#include "aknedwincustomdrawprivate.h"
#include <lafmain.h>
#include <AknsDrawUtils.h>
#include <frmtview.h>
#include <coecntrl.h>
#include <eikedwin.h>
#include <eikenv.h> // for AKN_LAF_COLOR macro
#include <AknUtils.h>
#include <gdi.h>


CAknEdwinCustomDrawPrivate* CAknEdwinCustomDrawPrivate::NewL(const MLafEnv& aEnv,const CEikEdwin& aControl)
	{ // static
	CAknEdwinCustomDrawPrivate* self =
        new(ELeave) CAknEdwinCustomDrawPrivate(aEnv,aControl);

    CleanupStack::PushL( self );
    self->CAknEdwinCustomDrawBase::ConstructL();
    CleanupStack::Pop();
    
    return self;
	}

CAknEdwinCustomDrawPrivate* CAknEdwinCustomDrawPrivate::NewL(const MLafEnv& aEnv,const CEikEdwin& aControl, CTextView* aTextView, CWindowGc* aSystemGc)
	{ // static
	CAknEdwinCustomDrawPrivate* self =
        new( ELeave ) CAknEdwinCustomDrawPrivate(aEnv, aControl, aTextView, aSystemGc);

    CleanupStack::PushL( self );
    self->CAknEdwinCustomDrawBase::ConstructL();
    CleanupStack::Pop();
    
    return self;
	}

CAknEdwinCustomDrawPrivate::~CAknEdwinCustomDrawPrivate()
    {
	}

CAknEdwinCustomDrawPrivate::CAknEdwinCustomDrawPrivate(const MLafEnv& aEnv,const CEikEdwin& aEdwin ) :
	CAknEdwinCustomDrawBase( aEnv, aEdwin )
	{
	}

CAknEdwinCustomDrawPrivate::CAknEdwinCustomDrawPrivate(const MLafEnv& aEnv,const CEikEdwin& aEdwin, CTextView* aTextView, CWindowGc* aSystemGc ) :
	CAknEdwinCustomDrawBase( aEnv, aEdwin, aTextView, aSystemGc )
	{
	}

void CAknEdwinCustomDrawPrivate::DrawText(const TParam& aParam,const TLineInfo& aLineInfo,const TCharFormat& aFormat, const TDesC& aText, const TPoint& aTextOrigin, TInt aExtraPixels) const
	{
	CAknEdwinCustomDrawBase::DrawText(aParam, aLineInfo, aFormat, aText, aTextOrigin, aExtraPixels);
	}

void CAknEdwinCustomDrawPrivate::DrawBackground(const TParam& aParam,const TRgb& aBackground,TRect& aDrawnRect) const
	{
	CAknEdwinCustomDrawBase::DrawBackground( aParam, aBackground, aDrawnRect ); // Base Call
	}

void CAknEdwinCustomDrawPrivate::DrawLineGraphics(const TParam& aParam,const TLineInfo& aLineInfo ) const
	{
    CAknEdwinCustomDrawBase::DrawLineGraphics( aParam, aLineInfo ); // Base Call
	}

TRgb CAknEdwinCustomDrawPrivate::SystemColor(TUint aColorIndex,TRgb aDefaultColor) const
    {
    return CAknEdwinCustomDrawBase::SystemColor( aColorIndex, aDefaultColor );
    }

