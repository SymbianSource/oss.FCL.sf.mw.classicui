/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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


#include "AknSmileyUtils.h"
#include "AknSmileyModel.h"



///////////////////////////////////////////////////////////////////////////////////////////////
// CAknSmileyIcon
///////////////////////////////////////////////////////////////////////////////////////////////

CAknSmileyIcon::CAknSmileyIcon()
    {
    
    }

CAknSmileyIcon::~CAknSmileyIcon()
    {
    
    }

const CFbsBitmap* CAknSmileyIcon::Image() const
    {
    return NULL;
    }

const CFbsBitmap* CAknSmileyIcon::Mask() const
    {
    return NULL;
    }

TBool CAknSmileyIcon::ReadyToDraw() const
    {
    return FALSE;
    }

const TSize KSize;
const TSize& CAknSmileyIcon::Size() const
    {
    return KSize;
    }

void CAknSmileyIcon::PlayAnimationL(TInt /*aRepeat*/, TInt /*aDelay*/)
    {

    }

void CAknSmileyIcon::StopAnimation()
    {

    }


///////////////////////////////////////////////////////////////////////////////////////////////
// CAknSmileyManager
///////////////////////////////////////////////////////////////////////////////////////////////

class CAknSmileyManager::CExtension : public CSmileyModel
    {
public:
    CExtension(MAknSmileyObserver* aObserver) : CSmileyModel(aObserver) {};
    };

EXPORT_C CAknSmileyManager* CAknSmileyManager::NewL(MAknSmileyObserver* aObserver)
    {
    CAknSmileyManager* self = new (ELeave) CAknSmileyManager();
    CleanupStack::PushL(self);
    self->ConstructL(aObserver);
    CleanupStack::Pop(); // self;
    return self;
    }

void CAknSmileyManager::ConstructL(MAknSmileyObserver* aObserver)
    {
    iExtension = new (ELeave) CExtension(aObserver);
    iExtension->LoadResourceL();
    }

CAknSmileyManager::CAknSmileyManager()
    {
    
    }

EXPORT_C CAknSmileyManager::~CAknSmileyManager()
    {
    delete iExtension;
    }

EXPORT_C TInt CAknSmileyManager::ConvertCodesToTextL(TDes& aText)
    {
    return iExtension->ConvertCodesToTextL(aText);
    }

EXPORT_C TInt CAknSmileyManager::ConvertTextToCodesL(TDes& aText)
    {
    return iExtension->ConvertTextToCodesL(aText);
    }

EXPORT_C const TDesC& CAknSmileyManager::Text(TChar aCode) const
    {
    return iExtension->Text(aCode);
    }

EXPORT_C TBool CAknSmileyManager::IsSmiley(TChar aCode) const
    {
    return iExtension->IsSmiley(aCode);
    }

EXPORT_C void CAknSmileyManager::SetSize(const TSize& aSize)
    {
    iExtension->SetSize(aSize);
    }

EXPORT_C void CAknSmileyManager::SetSizeByFont(const CFont* aFont)
    {
    iExtension->SetSizeByFont(aFont);
    }

EXPORT_C void CAknSmileyManager::DrawText(CWindowGc& aGc, const TDesC& aText, const CFont* aFont, const TPoint& aPosition) const
    {
    iExtension->DrawText(aGc, aText, aFont, aPosition);
    }

EXPORT_C void CAknSmileyManager::DrawText(CWindowGc& aGc, const TDesC& aText, const TAknLayoutText& aLayout, TBool aUseLogicalToVisualConversion) const
    {
    iExtension->DrawText(aGc, aText, aLayout, aUseLogicalToVisualConversion);
    }

EXPORT_C void CAknSmileyManager::DrawText(CWindowGc& aGc, const TDesC& aText, const CFont* aFont, const TRect& aBox, TInt aBaselineOffset, 
                                          CGraphicsContext::TTextAlign aAlignment, TInt aLeftMargin) const
    {
    iExtension->DrawText(aGc, aText, aFont, aBox, aBaselineOffset, aAlignment, aLeftMargin);
    }

EXPORT_C TInt CAknSmileyManager::Count() const
    {
    return iExtension->Count();
    }

EXPORT_C CAknSmileyIcon* CAknSmileyManager::Smiley(TChar aCode) const
    {
    return iExtension->Smiley(aCode);
    }

EXPORT_C CAknSmileyIcon* CAknSmileyManager::operator[](TInt aIndex) const
    {
    return iExtension->operator[](aIndex);
    }


// end of file

