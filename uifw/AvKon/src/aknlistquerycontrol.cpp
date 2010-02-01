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


#include <e32std.h>
#include <barsread.h>
#include <eikfrlb.h>  

#include <AknLayoutDef.h>
#include <AknLayout.lag>

#include "AknPanic.h"
#include "AknUtils.h"

#include "aknQueryControl.h"   
#include "aknlistquerycontrol.h"

#include <AknsDrawUtils.h>
#include <AknsBasicBackgroundControlContext.h>

#include <eikdialg.h>
#include <eikdialogext.h>

#include <AknTasHook.h> // for testability hooks
EXPORT_C CAknListQueryControl::CAknListQueryControl()
    {
    AKNTASHOOK_ADD( this, "CAknListQueryControl" );
    }

EXPORT_C void CAknListQueryControl::FocusChanged(TDrawNow aDrawNow)
    {
    if (iListBox) iListBox->SetFocus(IsFocused(), aDrawNow);
    if (iHeading) iHeading->SetFocus(IsFocused(), aDrawNow);
    }

EXPORT_C void CAknListQueryControl::ConstructFromResourceL(TResourceReader &aRes)
    {
    if( CAknEnv::Static()->TransparencyEnabled() )
        {
        CEikDialog* dlg;
        MopGetObject( dlg );
        if ( dlg )
            {
            dlg->Extension()->iPublicFlags.Set( CEikDialogExtension::EClipChildControlRect );
            }
        }

    
    TInt actuallisttype = 0;
    TInt listtype = aRes.ReadInt16();
    if (listtype != EAknListQueryWithMsgBox)
        {
        SEikControlInfo controlInfo=EikControlFactory::CreateByTypeL(listtype);
	    iListType = listtype;
        iListBox = STATIC_CAST(CEikFormattedCellListBox*, controlInfo.iControl);
        iListBox->SetContainerWindowL(*this);
        iListBox->CopyControlContextFrom(this);
        iListBox->ConstructFromResourceL(aRes);                
        }
    else
        {
        actuallisttype = aRes.ReadInt16();
        SEikControlInfo controlInfo=EikControlFactory::CreateByTypeL(actuallisttype);
	    iListType = actuallisttype;
        iListBox = STATIC_CAST(CEikFormattedCellListBox*, controlInfo.iControl);
        iListBox->SetContainerWindowL(*this);
        iListBox->CopyControlContextFrom(this);
        iListBox->ConstructFromResourceL(aRes);
        
        TPtrC msg = aRes.ReadTPtrC();
        iMessageBox = new(ELeave)CAknMessageQueryControl;
        iMessageBox->SetContainerWindowL(*this);
        iMessageBox->CopyControlContextFrom(this);
        iMessageBox->SetListQLayout(ETrue);
        iMessageBox->SetMessageTextL(&msg);
        }
        
    TPtrC label = aRes.ReadTPtrC();
    iHeading = new(ELeave)CAknPopupHeadingPane;
    iHeading->SetContainerWindowL(*this);
    iHeading->CopyControlContextFrom(this);
    iHeading->ConstructL(label);
    iHeading->SetLayout( CAknPopupHeadingPane::EListHeadingPane );

    TPtrC bmpFile=aRes.ReadTPtrC();
    TInt bmpId=aRes.ReadInt16();
    TInt bmpMask=aRes.ReadInt16();
    TInt animationId = aRes.ReadUint32();
    if ( animationId != 0 )
        {
        iHeading->SetHeaderAnimationL( animationId );
        }
    else if ( bmpFile.CompareF(KNullDesC) != 0)
        {
        CEikImage* image = new(ELeave) CEikImage;
        CleanupStack::PushL( image );
        image->CreatePictureFromFileL(bmpFile,bmpId,bmpMask);
        iHeading->SetHeaderImageL( image );
        CleanupStack::PopAndDestroy(); // image
        }
    }

EXPORT_C CAknListQueryControl::~CAknListQueryControl()
    {
    AKNTASHOOK_REMOVE();
    delete iListBox;
    delete iHeading;
    delete iMessageBox;    
    }

EXPORT_C TSize CAknListQueryControl::MinimumSize() 
    {
    if ( !Heading() )
        {
		if (iLayout && iLayout->iListRect.Valid())
			{
			return TSize(iLayout->iListRect.Rect().Size().iWidth, TRect(TPoint(0,0),iLayout->iListRect.Rect().iBr).Size().iHeight );
			}
        return TSize(30,30); // this should be enough for all layouts - can't be taken from LAF
        }

	if (iLayout && iLayout->iListRect.Valid())
		{
		return TSize(iLayout->iListRect.Rect().Size().iWidth, TRect(TPoint(0,0),iLayout->iListRect.Rect().iBr).Size().iHeight);
		}

    return TSize(50,50); // this should be enough for all layouts - can't be taken from LAF
    }

EXPORT_C TInt CAknListQueryControl::CountComponentControls() const
    {
    TInt count = 1;
    if ( iListBox->ScrollBarFrame() )
        {
        count++;
        }
    if (Heading()) 
    	{
    	count++;	
    	}
    if (MessageBox())
    	{
    	count++;
    	}    	
    return count;
    }

EXPORT_C CCoeControl* CAknListQueryControl::ComponentControl(TInt anIndex) const
    {
    if ( anIndex == 0 )
        {
        return iListBox;
        }
    if ( iListBox->ScrollBarFrame() )
        {
        if ( anIndex == 1)
            {
            // Actually listbox owns scrollbar and is the parent control for it,
            // but scrollbar rect is outside of listbox rect. That's why we
            // need to return non-window owning scrollbar here.
            return iListBox->ScrollBarFrame()->ComponentControl(0);
            }
        else if ( anIndex == 2 )
            {
            return Heading();
            }
        else if ( anIndex == 3 )
            {
            return MessageBox();
            }
        }
    else if ( anIndex == 1 ) // no scrollbar
        {
        return Heading();
        }
    else if ( anIndex == 2 ) // no scrollbar
        {
        return MessageBox();
        }
    return 0;
    }

EXPORT_C TKeyResponse CAknListQueryControl::OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType)
    {
    return iListBox->OfferKeyEventL(aKeyEvent, aType);
    }

EXPORT_C void CAknListQueryControl::Draw(const TRect &aRect) const
    {
    CWindowGc& gc=SystemGc();
    //This isn't needed as background is also drawn in this method.
    //AknPopupLayouts::HandleDraw(iEikonEnv, gc, *iLayout, iListBox, Heading());
    
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );
    
    TRect bgRect = Rect();
    bgRect.iBr.iY = iLayout->iWindowRect.iBr.iY;    
    
    if( CAknEnv::Static()->TransparencyEnabled() )
        {
        if ( aRect != iListBox->Rect() )
            {
            TRegionFix<4> dontDrawRegion;
            TRegionFix<16> drawRegion;
            dontDrawRegion.AddRect( iListBox->Rect() );
            if ( Heading() )
                {
                dontDrawRegion.AddRect(Heading()->Rect());
                }
            /*if ( MessageBox() )
                {
                dontDrawRegion.AddRect(MessageBox()->Rect());
                }*/
            drawRegion.AddRect( bgRect );
            drawRegion.SubRegion( dontDrawRegion );
            gc.SetClippingRegion( drawRegion );
            AknsDrawUtils::Background( skin, cc, this, gc, bgRect, KAknsDrawParamNoClearUnderImage );
            gc.CancelClippingRegion();
            }
        }
    else
        {
        AknsDrawUtils::Background( skin, cc, this, gc, bgRect );
        }
    }

EXPORT_C void CAknListQueryControl::SetLayout(TAknPopupWindowLayoutDef *aLayout)
    {
    iLayout = aLayout;
    }
    
EXPORT_C void CAknListQueryControl::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 

    CAknControl::HandlePointerEventL(aPointerEvent);
    }

EXPORT_C void* CAknListQueryControl::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }
    
CAknMessageQueryControl* CAknListQueryControl::MessageBox() const
    {
    return iMessageBox;
    }    

// End of File
