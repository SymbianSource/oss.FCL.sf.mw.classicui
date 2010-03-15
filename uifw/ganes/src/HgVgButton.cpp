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

// INCLUDE FILES

#include "HgVgButton.h"
#include "HgVgHelper.h"
#include <VG/vgu.h>
#include <gulicon.h>



// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CHgVgButton::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CHgVgButton* CHgVgButton::NewL( const TSize& aSize, const TPoint& aPosition, 
        const CGulIcon& aIcon )
    {
    CHgVgButton* self = new ( ELeave ) CHgVgButton( aSize, aPosition );
    CleanupStack::PushL (self );
    self->ConstructL(aIcon);
    CleanupStack::Pop ( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CHgVgButton::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CHgVgButton::ConstructL (const CGulIcon& aIcon)
    {
    iImage = HgVgHelper::CreateVgImageFromIconL(aIcon);    
    }

// -----------------------------------------------------------------------------
// CHgVgButton::CHgVgButton()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CHgVgButton::CHgVgButton( const TSize& aSize, const TPoint& aPosition ) :
iSize(aSize),
iPosition(aPosition),
iImage(VG_INVALID_HANDLE),
iEnabled(ETrue),
iPointerDown(EFalse)
    {


    }
        
// -----------------------------------------------------------------------------
// CHgVgButton::~CHgVgButton()
// Destructor.
// -----------------------------------------------------------------------------
//
CHgVgButton::~CHgVgButton ( )
    {

    
    }

// -----------------------------------------------------------------------------
// CHgVgButton::HandlePointerEvent()
// -----------------------------------------------------------------------------
//
TBool CHgVgButton::HandlePointerEvent(const TPointerEvent& aEvent)
    {
    if (!iEnabled)
        return EFalse;
    
    TRect rect(iPosition, iSize);
    TBool result = EFalse;

    if( aEvent.iType == TPointerEvent::EButton1Down && 
            rect.Contains(aEvent.iPosition) && !iPointerDown )
        {
        iPointerDown = ETrue;
        result = ETrue;
        }
    else if( aEvent.iType == TPointerEvent::EButton1Up )
        {
        iPointerDown = EFalse;
        result = EFalse;
        }
    
    return result;
    }

// -----------------------------------------------------------------------------
// CHgVgButton::Enabled()
// -----------------------------------------------------------------------------
//
TBool CHgVgButton::IsEnabled() const
    {
    return iEnabled;
    }

// -----------------------------------------------------------------------------
// CHgVgButton::Position()
// -----------------------------------------------------------------------------
//
const TPoint& CHgVgButton::Position() const
    {
    return iPosition;
    }
 
// -----------------------------------------------------------------------------
// CHgVgButton::Size()
// -----------------------------------------------------------------------------
//
const TSize& CHgVgButton::Size() const
    {
    return iSize;
    }
  
// -----------------------------------------------------------------------------
// CHgVgButton::SetEnabled()
// -----------------------------------------------------------------------------
//
void CHgVgButton::SetEnabled(TBool aEnabled)
    {
    iEnabled = aEnabled;
    }

// -----------------------------------------------------------------------------
// CHgVgButton::SetPosition()
// -----------------------------------------------------------------------------
//
void CHgVgButton::SetPosition(const TPoint& aPosition)
    {
    iPosition = aPosition;
    }
 
// -----------------------------------------------------------------------------
// CHgVgButton::SetSize()
// -----------------------------------------------------------------------------
//
void CHgVgButton::SetSize(const TSize& aSize)
    {
    iSize = aSize;
    }
 
 
// -----------------------------------------------------------------------------
// CHgVgButton::SetIconL()
// -----------------------------------------------------------------------------
//
void CHgVgButton::Draw(const TRect& aWindowRect, TReal aAlpha)
    {
    if (iEnabled)
        {
        TRgb color(KRgbWhite);
        color.SetAlpha(aAlpha * 255.0f);
        HgVgHelper::DrawImageColorized(iImage, color, iPosition, aWindowRect, EFalse, iLandscape);
        }
    }

// -----------------------------------------------------------------------------
// CHgVgButton::EnableLanscapeRendering()
// -----------------------------------------------------------------------------
//
void CHgVgButton::EnableLandscapeRendering(TBool aEnabled)
{
    iLandscape = aEnabled;
}


// End of File
