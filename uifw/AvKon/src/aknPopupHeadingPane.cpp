/*
* Copyright (c) 2002-2005 Nokia Corporation and/or its subsidiary(-ies).
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


#include <barsread.h>

#include <eiklabel.h>
#include <eikimage.h>
#include <avkon.rsg>
#include <avkon.hrh>

#include <AknLayoutDef.h>
#include <AknLayout.lag>
#include <avkon.mbg>

#include "AknPanic.h"
#include "aknPopupHeadingPane.h"
#include "akntextcontrol.h"
#include "AknBitmapAnimation.h"
#include "aknconsts.h"

#include <AknsDrawUtils.h>
#include <StringLoader.h>

#include <AknsUtils.h>
#include <AknIconUtils.h>

#include <AknUtils.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <layoutmetadata.cdl.h>
#include <aknbutton.h>
#include "AknHeadingPaneTouchObserver.h"

// ================= Extension class ========================
NONSHARABLE_CLASS(CAknPopupHeadingPaneExtension) : public CBase
    {
    public:
        CAknPopupHeadingPaneExtension();
        ~CAknPopupHeadingPaneExtension();

    public: // data 
		TAknsItemID iFrameId;
		TAknsItemID iFrameCenterId;
		MAknHeadingPaneTouchObserver* iTouchObserver;
    };

CAknPopupHeadingPaneExtension::CAknPopupHeadingPaneExtension()
    {
    }

CAknPopupHeadingPaneExtension::~CAknPopupHeadingPaneExtension()
    {
    }



class CAknPopupHeadingAttributes: public CBase, public MCoeControlObserver
    {
    public:
        void SetEnableCloseButton();
        TBool IsEnableCloseButton() const;
        static TInt CallBackByOneShot(TAny* aThisPtr);

    public: // from MCoeControlObserver
        virtual void HandleControlEventL(CCoeControl *aControl, TCoeEvent aEventType);
    public:
        CAknPopupHeadingPane::THeadingPaneLayout iLayout;
        CCoeBrushAndPenContext* iBrushAndPenContext;
        CAknTextControl*    iPage;
        CAknButton*         iCloseButton;
        CAsyncCallBack*     iAsyncOneShot;

        TInt iCurrentPage;
        TInt iMaxPage;
        TBool iEnableCloseButton;

        ~CAknPopupHeadingAttributes()
            {
            if (iAsyncOneShot)
                {
                iAsyncOneShot->Cancel();
                delete iAsyncOneShot;
                iAsyncOneShot = NULL;
                }
            delete iBrushAndPenContext;
            delete iPage;
            delete iCloseButton;
            }
    };

void CAknPopupHeadingAttributes::SetEnableCloseButton()
    {
    CAknEnv* env = CAknEnv::Static();
    TBool japaneseUi = (env && env->IsFeatureLanguage(KFeatureIdJapanese))?
                        ETrue : EFalse;
    if (AknLayoutUtils::PenEnabled() && japaneseUi)
        {
        iEnableCloseButton = ETrue;
        }
    else
        {
        iEnableCloseButton = EFalse;
        }
    }

TBool CAknPopupHeadingAttributes::IsEnableCloseButton() const
    {
    return iEnableCloseButton;
    }

/**
 * Call back function:
 */
TInt CAknPopupHeadingAttributes::CallBackByOneShot(TAny* /*aThisPtr*/)
    {
    // Simulate RSK down key event
    TKeyEvent key;
    key.iCode = EKeyCBA2; // = EKeyDevice1
    // Special flag that implies the simulated key event is sent by this  call back function
    key.iModifiers = EModifierKeyboardExtend;
    key.iScanCode = EStdKeyDevice1;
    key.iRepeats = 0;
    TRAP_IGNORE( CCoeEnv::Static()->SimulateKeyEventL(key, EEventKey) );
    return KErrNone;
    }
void CAknPopupHeadingAttributes::HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType)
    {
    if (aControl == iCloseButton)
        {
        // Handle the event sent by Close button control
        switch (aEventType)
            {
            case MCoeControlObserver::EEventRequestExit:
                {
                if (!iAsyncOneShot)
                	{
                    iAsyncOneShot = new (ELeave) CAsyncCallBack(EPriorityHigh);
                    // setting call back
                    TCallBack callback(CallBackByOneShot, this);
                    iAsyncOneShot->Set(callback);
                    iAsyncOneShot->CallBack();
                	}
                }
                break;
            default:
                break;
            }
        }
    }

EXPORT_C CAknPopupHeadingPane::~CAknPopupHeadingPane()
    {
    AknsUtils::DeregisterControlPosition(this);
    delete iExtension;
    delete iPrompt;
    delete iHeaderImage;
    delete iAnimation;
    delete iAttributes;
    }

EXPORT_C void CAknPopupHeadingPane::ConstructL(TPtrC aText)
    {
    if ( ! iAttributes )
        {
        iAttributes = new ( ELeave ) CAknPopupHeadingAttributes;
        iAttributes->iBrushAndPenContext=CCoeBrushAndPenContext::NewL();
        iAttributes->iBrushAndPenContext->SetBrushStyle(CGraphicsContext::ENullBrush);
        SetControlContext(iAttributes->iBrushAndPenContext);        
        }
        
    if (!iPrompt)
        {
        iPrompt = CAknTextControl::NewL();
        iPrompt->SetContainerWindowL(*this);
        }

    if (!iAttributes->iPage)
        {
        iAttributes->iPage = CAknTextControl::NewL();
        iAttributes->iPage->SetContainerWindowL(*this);
        iAttributes->iPage->MakeVisible(EFalse);
        }

    if (!iAttributes->iCloseButton)
        {
        TResourceReader reader;
        CEikonEnv::Static()->CreateResourceReaderLC( reader, R_AVKON_SCT_HEADING_CLOSE_BUTTON );
        iAttributes->iCloseButton = CAknButton::NewL(reader);
        iAttributes->iCloseButton->SetContainerWindowL(*this);
        iAttributes->iCloseButton->SetObserver(iAttributes);
        iAttributes->iCloseButton->SetRequestExit( ETrue );
        iAttributes->iCloseButton->MakeVisible(EFalse);
        CleanupStack::PopAndDestroy(); //reader buffer
        iAttributes->SetEnableCloseButton();
        }

    if ( !iExtension )
        {
        iExtension = new (ELeave) CAknPopupHeadingPaneExtension;    
        }

    iExtension->iFrameId = KAknsIIDQsnFrPopupHeading;
    iExtension->iFrameCenterId = KAknsIIDQsnFrPopupHeadingCenter;


    SetTextL(aText);
    SetNonFocusing();
    iAttributes->iLayout = EQueryHeadingPane; // QueryHeadingPane by default
    }

EXPORT_C void CAknPopupHeadingPane::ConstructFromResourceL(TResourceReader &aReader)
    {
    if ( ! iAttributes )
        {
        iAttributes = new ( ELeave ) CAknPopupHeadingAttributes;
        iAttributes->iBrushAndPenContext=CCoeBrushAndPenContext::NewL();
        iAttributes->iBrushAndPenContext->SetBrushStyle(CGraphicsContext::ENullBrush);
        SetControlContext(iAttributes->iBrushAndPenContext);        
        }
        
    if (!iPrompt)
        {
        iPrompt = CAknTextControl::NewL();
        iPrompt->SetContainerWindowL(*this);
        }

    if (!iAttributes->iPage)
        {
        iAttributes->iPage = CAknTextControl::NewL();
        iAttributes->iPage->SetContainerWindowL(*this);
        iAttributes->iPage->MakeVisible(EFalse);
        }

    if (!iAttributes->iCloseButton)
        {
        TResourceReader reader;
        CEikonEnv::Static()->CreateResourceReaderLC( reader, R_AVKON_SCT_HEADING_CLOSE_BUTTON );
        iAttributes->iCloseButton = CAknButton::NewL(reader);
        iAttributes->iCloseButton->SetContainerWindowL(*this);
        iAttributes->iCloseButton->MakeVisible(EFalse);
        iAttributes->iCloseButton->SetObserver(iAttributes);
        iAttributes->iCloseButton->SetRequestExit( ETrue );
        CleanupStack::PopAndDestroy(); //reader buffer
        iAttributes->SetEnableCloseButton();
        }

    SetTextL(aReader.ReadTPtrC());

    HBufC* bitmapFile = aReader.ReadHBufCL();        // bmp filename
    TInt bitmapId = aReader.ReadInt16();        // bmp id
    TInt maskId = aReader.ReadInt16();        // bmp mask id
    if (bitmapFile != NULL)
        {
        CleanupStack::PushL(bitmapFile);                        
        iHeaderImage = new (ELeave) CEikImage;
        iHeaderImage->SetContainerWindowL(*this);
        iHeaderImage->SetNonFocusing();
        iHeaderImage->SetAlignment(EHCenterVCenter);
            
        if (bitmapId != -1)
            {
            CFbsBitmap* bitmap;                
            if (maskId != -1)
                {
                CFbsBitmap* mask;
                AknIconUtils::CreateIconLC(bitmap, mask, *bitmapFile, bitmapId, maskId);
                TAknLayoutRect layout;
                layout.LayoutRect(Rect(), AknLayoutScalable_Avkon::heading_pane_g2()); // Icon
                User::LeaveIfError(AknIconUtils::SetSize(bitmap, layout.Rect().Size()));
                iHeaderImage->SetPicture(bitmap, mask);
                iHeaderImage->SetPictureOwnedExternally(EFalse);
                CleanupStack::Pop(2);    //bitmap, mask
                }
            else
                {
                bitmap = AknIconUtils::CreateIconL(*bitmapFile, bitmapId);
                CleanupStack::PushL(bitmap);
                TAknLayoutRect layout;
                layout.LayoutRect(Rect(), AknLayoutScalable_Avkon::heading_pane_g2()); // Icon
                User::LeaveIfError(AknIconUtils::SetSize(bitmap, layout.Rect().Size()));
                iHeaderImage->SetPicture(bitmap);
                iHeaderImage->SetPictureOwnedExternally(EFalse);
                CleanupStack::Pop();    //bitmap
                }
            }
        CleanupStack::PopAndDestroy();        // bitmapFile
        }    

    TInt animationId = aReader.ReadUint32();
    if (animationId != 0)
        {
        if (!iAnimation)
            {// no animation previously set
            SetHeaderAnimationL(animationId);
            }
        }

    iHeadingLayoutRef = aReader.ReadUint32();
    
	// extension needed for heading skinning    
    if ( !iExtension )
        {
        iExtension = new (ELeave) CAknPopupHeadingPaneExtension;    
        }
        
	iExtension->iFrameId = KAknsIIDQsnFrPopupHeading;  
	iExtension->iFrameCenterId = KAknsIIDQsnFrPopupHeadingCenter;        

    SetNonFocusing();
    }

EXPORT_C void CAknPopupHeadingPane::SetTextL(TPtrC aText)
    {
    __ASSERT_DEBUG(iPrompt,Panic(EAknPanicNullPointer));
    iPrompt->SetTextL(aText);

    __ASSERT_DEBUG(iAttributes->iPage,Panic(EAknPanicNullPointer));
    // Reset page number when be more than one page
    if (iAttributes->iMaxPage > 1)
        {
        HBufC* page = PageTextL();
        CleanupStack::PushL(page);
        iAttributes->iPage->SetTextL(*page);
        CleanupStack::PopAndDestroy(); // page
        }

    DoSetPromptL();
    if (!Rect().IsEmpty())
        {
        SizeChanged();
        }
    }

EXPORT_C void CAknPopupHeadingPane::SetHeaderImageOwnedL(CEikImage *aImage)
    { 
    delete iHeaderImage;
    iHeaderImage = aImage;

    if ( iHeaderImage )
        {
        iHeaderImage->SetContainerWindowL(*this);
        iHeaderImage->SetNonFocusing();
        iHeaderImage->SetAlignment(EHCenterVCenter);
        }

    DoSetPromptL();
    if (!Rect().IsEmpty())
        {
        SizeChanged();
        }
    }
    
EXPORT_C void CAknPopupHeadingPane::SetHeaderImageL(CEikImage *aImage)
    {
    if ( !iHeaderImage )
        {
        iHeaderImage = new (ELeave) CEikImage;
        iHeaderImage->SetContainerWindowL(*this);
        iHeaderImage->SetNonFocusing();
        iHeaderImage->SetAlignment(EHCenterVCenter);
        }
    
    CFbsBitmap* bitmap = new  (ELeave) CFbsBitmap();
    CleanupStack::PushL(bitmap);                
    CFbsBitmap* mask = new (ELeave) CFbsBitmap();                 
    bitmap->Duplicate(aImage->Bitmap()->Handle());
    mask->Duplicate(aImage->Mask()->Handle());
    iHeaderImage->SetPicture(bitmap, mask); 
    iHeaderImage->SetPictureOwnedExternally(EFalse);
    CleanupStack::Pop(); // bitmap

    DoSetPromptL();
    if (!Rect().IsEmpty())
        {
        SizeChanged();
        }
    }    

EXPORT_C void CAknPopupHeadingPane::SetHeaderAnimationL( TInt aResourceId )
    {
    if (aResourceId <= 0)
        {
        return;
        }

    // If header image set, delete it!
    delete iHeaderImage;
    iHeaderImage = NULL;

    delete iAnimation;
    iAnimation = NULL;
    iAnimation = CAknBitmapAnimation::NewL();

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC(reader,aResourceId);
    iAnimation->ConstructFromResourceL(reader);
    CleanupStack::PopAndDestroy(); //reader buffer
        
    iAnimation->SetContainerWindowL(*this);
    iAnimation->SetNonFocusing();

    DoSetPromptL();
    if (!Rect().IsEmpty())
        {
        SizeChanged();
        }
    }

EXPORT_C void CAknPopupHeadingPane::SetLayout( THeadingPaneLayout aLayout )
    {
    iAttributes->iLayout = aLayout;
    }

void CAknPopupHeadingPane::DoSetPromptL()
    {
    __ASSERT_DEBUG(iPrompt,Panic(EAknPanicNullPointer));

    CArrayFixFlat<TInt>* lineWidths = new(ELeave)CArrayFixFlat<TInt>(1);
    CleanupStack::PushL(lineWidths);

    TAknTextComponentLayout textLayout = AknLayoutScalable_Avkon::heading_pane_t1(0);
    if (iHeaderImage || iAnimation)
        {
        textLayout = AknLayoutScalable_Avkon::heading_pane_t1(2);
        }
    
    if (iAttributes->iPage->IsVisible())
        {
        TInt varietyIndex = (AknLayoutUtils::PenEnabled())? 3 : 1;
        textLayout = AknLayoutScalable_Avkon::heading_pane_t1(varietyIndex);
        }

    TRect parentRect;
    TAknLayoutRect popupRect;
    if(!AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EMainPane, parentRect))
        {
        parentRect = iAvkonAppUi->ClientRect();
        }
    popupRect.LayoutRect(parentRect, AknLayoutScalable_Avkon::popup_window_general(1));
        
    TAknLayoutRect headingRect;
    TAknWindowComponentLayout headingPaneLayout;
    if (iAttributes->iLayout == EMessageQueryHeadingPane)
        {
        headingPaneLayout = AknLayoutScalable_Avkon::heading_pane_cp5();        
        }
    else
        {
        headingPaneLayout = AknLayoutScalable_Avkon::heading_pane(0);
        }
    headingRect.LayoutRect(TRect(TPoint(0,0),popupRect.Rect().Size()), headingPaneLayout);
    parentRect = headingRect.Rect();

    TAknLayoutText textRect;
    textRect.LayoutText(parentRect, textLayout);

    lineWidths->AppendL(textRect.TextRect().Width());           
    
    const CFont* promptFont = AknLayoutUtils::FontFromId( textLayout.Font() );
    iPrompt->ParseTextL(promptFont, lineWidths);      
    
    CleanupStack::PopAndDestroy(); //lineWidths

    lineWidths = new(ELeave)CArrayFixFlat<TInt>(1);
    CleanupStack::PushL(lineWidths);

    TInt varietyIndex = (iAttributes->IsEnableCloseButton())? 1 : 0;
    textLayout = AknLayoutScalable_Avkon::heading_pane_t2(varietyIndex);
    textRect.LayoutText(parentRect, textLayout);

    lineWidths->AppendL(textRect.TextRect().Width());
    const CFont* fontUsed = AknLayoutUtils::FontFromId( textLayout.Font() );
    iAttributes->iPage->ParseTextL(fontUsed, lineWidths);
    CleanupStack::PopAndDestroy(); //lineWidths
    }


EXPORT_C void CAknPopupHeadingPane::SizeChanged()
    {
    if (iAttributes->iLayout == EQueryHeadingPane)
        {
        LayoutQueryHeadingPane();
        }
    else if (iAttributes->iLayout == EColourSelectionGridHeadingPane)
        {
        LayoutColourSelectionGridHeadingPane();
        }
    else if (iAttributes->iLayout == EMessageQueryHeadingPane)
        {
        LayoutMessageQueryHeadingPane();
        }
    else
        {
        LayoutListHeadingPane();
        }
        
    if (iHeaderImage)
        {
        TAknLayoutRect layout;
        layout.LayoutRect(Rect(), AknLayoutScalable_Avkon::heading_pane_g2());
        AknIconUtils::SetSize(CONST_CAST(CFbsBitmap*, iHeaderImage->Bitmap()), layout.Rect().Size());    	
        }
        
    AknsUtils::RegisterControlPosition(this);
    }


void CAknPopupHeadingPane::LayoutQueryHeadingPane()
    {
    TRect parentRect = Rect();
        
    TAknLayoutRect headingLayoutRect;
    headingLayoutRect.LayoutRect(parentRect, AknLayoutScalable_Avkon::heading_pane(0));
    TRect headingrect(headingLayoutRect.Rect());                
            
    iPrompt->SetRect(headingrect);
    iAttributes->iPage->SetRect(headingrect);

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    TRgb color;
    TInt error = AknsUtils::GetCachedColor( skin,
                                            color,
                                            KAknsIIDQsnTextColors,
                                            EAknsCIQsnTextColorsCG19 );


    TInt headingPaneTextIndex = 0;
    // Layout the heading text
    if (iPrompt->NumberOfLines() > 0)
        {
        if ( iHeaderImage || iAnimation )
            {
            headingPaneTextIndex = 2;
            if ( iAnimation )
                {
                AknLayoutUtils::LayoutControl(iAnimation, headingrect, AknLayoutScalable_Avkon::heading_pane_g2() ); // Icon
                }
            else
                {
                AknLayoutUtils::LayoutImage(iHeaderImage, headingrect, AknLayoutScalable_Avkon::heading_pane_g2() ); // Icon
                }
            }
        else if (iAttributes->iPage->IsVisible())
            {
            // Page number layout needed.
            headingPaneTextIndex = (AknLayoutUtils::PenEnabled())? 3 : 1;
            }

       TAknTextComponentLayout headingPrompt = AknLayoutScalable_Avkon::heading_pane_t1(headingPaneTextIndex);

        AknLayoutUtils::LayoutLabel(iPrompt->Line(0), headingrect, headingPrompt);
        if (!error)
            {
            // Ignore error
            TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( *iPrompt->Line(0), 
                                                                 EColorLabelText, color ) );
            }
        }

    // Layout page number text
    if (iAttributes->iPage->IsVisible() && iAttributes->iPage->NumberOfLines() > 0)
        {
        TInt varietyIndex = (iAttributes->IsEnableCloseButton())? 1 : 0;
        TAknTextComponentLayout headingPrompt2 = AknLayoutScalable_Avkon::heading_pane_t2(varietyIndex);

        AknLayoutUtils::LayoutLabel(iAttributes->iPage->Line(0), headingrect, headingPrompt2);
        if (!error)
            {
            // Ignore error
            TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( *iAttributes->iPage->Line(0), 
                                                                 EColorLabelText, color ) );
            }
        }

    // Layout close button
    if (iAttributes->IsEnableCloseButton())
        {
        TAknLayoutRect buttonLayoutRect;
        buttonLayoutRect.LayoutRect(headingrect, AknLayoutScalable_Avkon::heading_pane_g1());
        iAttributes->iCloseButton->SetRect(buttonLayoutRect.Rect());
        iAttributes->iCloseButton->MakeVisible(ETrue);
        }

    }

void CAknPopupHeadingPane::LayoutListHeadingPane()
    {
    TRect headingrect = Rect();
    iPrompt->SetRect(headingrect);    

    if (iPrompt->NumberOfLines() > 0)
        {
        TAknTextComponentLayout textLayout = AknLayoutScalable_Avkon::heading_pane_t1(0);

        if (iAnimation || iHeaderImage)
            {
            textLayout = AknLayoutScalable_Avkon::heading_pane_t1(1);
            }

        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        TRgb color;
        TInt error = AknsUtils::GetCachedColor( skin, color,
                                                KAknsIIDQsnTextColors,
                                                EAknsCIQsnTextColorsCG19 );

        AknLayoutUtils::LayoutLabel(iPrompt->Line(0), headingrect, textLayout);

        if (!error)
            {
            // Ignore error
            TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL(
                       *iPrompt->Line(0), 
                       EColorLabelText, color ) );
            }
        TAknWindowLineLayout icon( AknLayoutScalable_Avkon::heading_pane_g2() ); // Icon
        if ( iAnimation )
            {
            AknLayoutUtils::LayoutControl(iAnimation, headingrect, icon );
            }
        else if ( iHeaderImage )
            {
            TAknLayoutRect r;
            r.LayoutRect( Rect(), icon );
            AknLayoutUtils::LayoutImage(iHeaderImage, headingrect, icon );
            }
        }
    }

void CAknPopupHeadingPane::LayoutColourSelectionGridHeadingPane()
    {
    TAknWindowLineLayout headingPaneWindowLine;       
    if (iAttributes->iLayout == EColourSelectionGridHeadingPane)
        {
        headingPaneWindowLine = AknLayoutScalable_Avkon::heading_pane_cp4();
        }
    else
        {
        headingPaneWindowLine = AknLayoutScalable_Avkon::heading_pane(1);
        }
    
    TAknLayoutRect headingLayoutRect;
    headingLayoutRect.LayoutRect(Rect(), headingPaneWindowLine);
    TRect headingrect = headingLayoutRect.Rect();
    iPrompt->SetRect(headingrect);
    iAttributes->iPage->SetRect(headingrect);
    
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    TRgb color;
    TInt error = AknsUtils::GetCachedColor( skin,
        color,
        KAknsIIDQsnTextColors,
        EAknsCIQsnTextColorsCG19 );
        
    TInt headingPaneTextIndex = 0;
    // Layout the heading text
    if (iPrompt->NumberOfLines() > 0)
        {
        if ( iHeaderImage || iAnimation )
            {
            headingPaneTextIndex = 2;
            if ( iAnimation )
                {
                AknLayoutUtils::LayoutControl(iAnimation, headingrect, AknLayoutScalable_Avkon::heading_pane_g2() ); // Icon
                }
            else
                {
                AknLayoutUtils::LayoutImage(iHeaderImage, headingrect, AknLayoutScalable_Avkon::heading_pane_g2() ); // Icon
                }
            }
        else if (iAttributes->iPage->IsVisible())
            {
            // Page number layout needed.
            headingPaneTextIndex = (AknLayoutUtils::PenEnabled())? 3 : 1;
            }
            
        TAknTextComponentLayout headingPrompt = AknLayoutScalable_Avkon::heading_pane_t1(headingPaneTextIndex);
        
        AknLayoutUtils::LayoutLabel(iPrompt->Line(0), headingrect, headingPrompt);
        if (!error)
            {
            // Ignore error
            TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( *iPrompt->Line(0), 
                EColorLabelText, color ) );
            }
        }
    
    // Layout page number text
    if (iAttributes->iPage->IsVisible() && iAttributes->iPage->NumberOfLines() > 0)
        {
        TInt varietyIndex = (iAttributes->IsEnableCloseButton())? 1 : 0;
        TAknTextComponentLayout headingPrompt2 = AknLayoutScalable_Avkon::heading_pane_t2(varietyIndex);

        AknLayoutUtils::LayoutLabel(iAttributes->iPage->Line(0), headingrect, headingPrompt2);

        if (!error)
            {
            // Ignore error
            TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( *iAttributes->iPage->Line(0), 
                EColorLabelText, color ) );
            }
        }

    // Layout close button
    if (iAttributes->IsEnableCloseButton())
        {
        TAknLayoutRect buttonLayoutRect;
        buttonLayoutRect.LayoutRect(headingrect, AknLayoutScalable_Avkon::heading_pane_g1());
        iAttributes->iCloseButton->SetRect(buttonLayoutRect.Rect());
        iAttributes->iCloseButton->MakeVisible(ETrue);
        }
    }

void CAknPopupHeadingPane::LayoutMessageQueryHeadingPane()
    {
    TRect parentRect = Rect();
        
    TAknLayoutRect headingLayoutRect;
    headingLayoutRect.LayoutRect(parentRect, AknLayoutScalable_Avkon::heading_pane_cp5());
    TRect headingrect(headingLayoutRect.Rect());                
    iPrompt->SetRect(headingrect);
    iAttributes->iPage->SetRect(headingrect);

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    TRgb color;
    TInt error = AknsUtils::GetCachedColor( skin,
                                            color,
                                            KAknsIIDQsnTextColors,
                                            EAknsCIQsnTextColorsCG19 );


    TInt headingPaneTextIndex = 0;
	// Layout the heading text
    if (iPrompt->NumberOfLines() > 0)
        {
        if ( iHeaderImage || iAnimation )
            {
            headingPaneTextIndex = 2;            
            if ( iAnimation )
                {
                AknLayoutUtils::LayoutControl(iAnimation, headingrect, AknLayoutScalable_Avkon::heading_pane_g2() ); // Icon
                }
            else
                {
                AknLayoutUtils::LayoutImage(iHeaderImage, headingrect, AknLayoutScalable_Avkon::heading_pane_g2() ); // Icon
                }
            }
        else if (iAttributes->iPage->IsVisible())
            {
            // Page number layout needed.
            headingPaneTextIndex = (AknLayoutUtils::PenEnabled())? 3 : 1;
            }
       TAknTextComponentLayout headingPrompt = AknLayoutScalable_Avkon::heading_pane_t1(headingPaneTextIndex);

        AknLayoutUtils::LayoutLabel(iPrompt->Line(0), headingrect, headingPrompt);
        if (!error)
            {
            // Ignore error
            TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( *iPrompt->Line(0), 
                                                                 EColorLabelText, color ) );
            }
        }

    // Layout page number text
    if (iAttributes->iPage->IsVisible() && iAttributes->iPage->NumberOfLines() > 0)
        {
        TInt varietyIndex = (iAttributes->IsEnableCloseButton())? 1 : 0;
        TAknTextComponentLayout headingPrompt2 = AknLayoutScalable_Avkon::heading_pane_t2(varietyIndex);

        AknLayoutUtils::LayoutLabel(iAttributes->iPage->Line(0), headingrect, headingPrompt2);
  
        if (!error)
            {
            // Ignore error
            TRAP_IGNORE( AknLayoutUtils::OverrideControlColorL( *iAttributes->iPage->Line(0), 
                                                                 EColorLabelText, color ) );
            }
        }

    // Layout close button
    if (iAttributes->IsEnableCloseButton())
        {
        TAknLayoutRect buttonLayoutRect;
        buttonLayoutRect.LayoutRect(headingrect, AknLayoutScalable_Avkon::heading_pane_g1());
        iAttributes->iCloseButton->SetRect(buttonLayoutRect.Rect());
        iAttributes->iCloseButton->MakeVisible(ETrue);
        }
    }

EXPORT_C TSize CAknPopupHeadingPane::MinimumSize()
    {
    if (iPrompt->NumberOfLines() == 0)
        {
        return TSize(0,0);
        }

    TRect popupRect = Rect();
    TRect mainPaneRect;
    if( iAttributes->iLayout == EColourSelectionGridHeadingPane )
        {
        if(!AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EPopupParent, mainPaneRect))
            {
            mainPaneRect = iAvkonAppUi->ClientRect();
            }
        }
    else
        {
        if(!AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EMainPane, mainPaneRect))
            {
            mainPaneRect = iAvkonAppUi->ClientRect();
            }
        }

    TAknWindowComponentLayout popupWindowLayout;
    TAknLayoutRect popupLayoutRect;
    if ( iAttributes->iLayout == EColourSelectionGridHeadingPane )
        {
        TInt colourPopupVariety = 0;
        if (Layout_Meta_Data::IsLandscapeOrientation())
            {
            switch (AknLayoutUtils::CbaLocation())
                {
                case AknLayoutUtils::EAknCbaLocationBottom:
                    //Bottom softkeyt
                    colourPopupVariety = 1;
                    break;
                case AknLayoutUtils::EAknCbaLocationRight:
                    //Right softkeyt
                    colourPopupVariety = 2;
                    break;
                case AknLayoutUtils::EAknCbaLocationLeft:
                    //Left softkeyt
                    colourPopupVariety = 3;
                    break;
                default:
                    break;
                }
            }
            popupWindowLayout = AknLayoutScalable_Avkon::popup_large_graphic_colour_window(colourPopupVariety);
            }
        else
            {
            popupWindowLayout = AknLayoutScalable_Avkon::popup_window_general(1);
            }
    popupLayoutRect.LayoutRect(mainPaneRect, popupWindowLayout);
    popupRect = TRect(TPoint(0,0), popupLayoutRect.Rect().Size());        

    TAknWindowComponentLayout headingPaneWindowLayout;       
    if (iAttributes->iLayout == EColourSelectionGridHeadingPane)
        {
        headingPaneWindowLayout = AknLayoutScalable_Avkon::heading_pane_cp4();
        }
    else if (iAttributes->iLayout == EMessageQueryHeadingPane)
        {
        headingPaneWindowLayout = AknLayoutScalable_Avkon::heading_pane_cp5();
        }
    else
        {
        headingPaneWindowLayout = AknLayoutScalable_Avkon::heading_pane(0);
        }
    
    TAknLayoutRect headingPaneRect; 
    headingPaneRect.LayoutRect(popupRect, headingPaneWindowLayout);

    TSize minimumSize;
    if (iAttributes->iLayout == EColourSelectionGridHeadingPane ||
        iAttributes->iLayout == EMessageQueryHeadingPane)
        {
        minimumSize = TSize(popupRect.Width(), headingPaneRect.Rect().iBr.iY - popupRect.iTl.iY);
        }
    else
        {
#ifndef RD_NO_DIALOG_BORDERS        
        minimumSize = TSize(headingPaneRect.Rect().Width(), headingPaneRect.Rect().iTl.iY + headingPaneRect.Rect().Height());
#else
        minimumSize = headingPaneRect.Rect().Size();
#endif
        }
            
    return minimumSize;
    }

EXPORT_C void CAknPopupHeadingPane::Draw(const TRect &/*aRect*/) const
    { 
    TRect parentRect = Rect();
    CWindowGc &gc = SystemGc();
    gc.Reset();

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    
    TRect windowRect = parentRect;    							
    TAknLayoutRect headingLayoutRect;
    TAknWindowComponentLayout headingPaneLayout;

    if (iAttributes->iLayout == EMessageQueryHeadingPane)
        {
        headingPaneLayout = AknLayoutScalable_Avkon::heading_pane_cp5();
        }
    else if(iAttributes->iLayout == EQueryHeadingPane)
        {
        headingPaneLayout = AknLayoutScalable_Avkon::heading_pane(0);
        }
    else if(iAttributes->iLayout == EColourSelectionGridHeadingPane)
        {            
        headingPaneLayout = AknLayoutScalable_Avkon::heading_pane_cp4();
        }

    headingLayoutRect.LayoutRect(parentRect, headingPaneLayout);
    windowRect = headingLayoutRect.Rect();        
    				
    TAknWindowComponentLayout innerArea = AknLayoutScalable_Avkon::bg_popup_heading_pane_g1();
    TAknLayoutRect inner;
    inner.LayoutRect(windowRect, innerArea .LayoutLine());

    TRect outerRect = windowRect;
    TRect innerRect = inner.Rect();
    
    TBool drawn(EFalse);
    
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this ); // get parent's cc
    
    /*
    // with transparency on, we can't draw both background and frame
    if ( CAknEnv::Static()->TransparencyEnabled() )
        {
        if ( iExtension )
            {
            TRegionFix<1> dontDrawRegion;
            TRegionFix<4> drawRegion;
            dontDrawRegion.AddRect( outerRect );
            drawRegion.AddRect( parentRect );
            drawRegion.SubRegion( dontDrawRegion );
            // this causes wserver flush, but only if parentRect != outerRect
            gc.SetClippingRegion( drawRegion );
            AknsDrawUtils::Background( skin, cc, this, gc, parentRect );
            gc.CancelClippingRegion();    
    	    drawn = AknsDrawUtils::DrawFrame( skin, gc, outerRect, innerRect, 
                                    	  iExtension->iFrameId,
                                      	  iExtension->iFrameCenterId );
            if ( !drawn )
                {
                // Couldn't draw frame, draw background again without clipping
                drawn = AknsDrawUtils::Background( skin, cc, this, gc, parentRect );
                }
            }
        else
            {
            drawn = AknsDrawUtils::Background( skin, cc, this, gc, parentRect );
            }
        }*/   

    drawn = AknsDrawUtils::Background( skin, cc, this, gc, parentRect );
    if ( iExtension )
        {
        drawn |= AknsDrawUtils::DrawFrame( skin, gc, outerRect, innerRect,
                                           iExtension->iFrameId,
                                           iExtension->iFrameCenterId);
        }
    else
        {
        drawn = AknsDrawUtils::Background( skin, cc, this, gc, parentRect );
        }

    if (!drawn) // skin drawing didn't work, so just clear the rect
        {
        gc.Clear(parentRect);
        }
    }

EXPORT_C CEikLabel* CAknPopupHeadingPane::Prompt() const 
    {         
    return iPrompt->Line(0);
    }

EXPORT_C TPtr CAknPopupHeadingPane::PromptText() const
    {
    return iPrompt->Text();
    }

CCoeControl* CAknPopupHeadingPane::ComponentControl(TInt anIndex) const
    {
    CCoeControl* controls[] =
        {
        iPrompt,
        iHeaderImage,
        iAnimation,
        iAttributes->iPage,
        iAttributes->iCloseButton
        };

    for ( TUint ii=0; ii < sizeof(controls)/sizeof(CCoeControl*); ii++)
        if ( controls[ii] && anIndex-- == 0 )
            {
            return controls[ii];
            }
    return NULL;
    }


TInt CAknPopupHeadingPane::CountComponentControls() const
    {
    TInt count = 0;
    CCoeControl* controls[] =
        {
        iPrompt,
        iHeaderImage,
        iAnimation,
        iAttributes->iPage,
        iAttributes->iCloseButton
        };

    for (TUint ii=0; ii < sizeof(controls)/sizeof(CCoeControl*); ii++ )
        {
        if (controls[ii])
            {
            count++;
            }
        }
    return count;
    }

void CAknPopupHeadingPane::ActivateL()
    {
    CCoeControl::ActivateL();
    if ( iAnimation )
        {
        SetAnimationBackGroundFrameL();
        iAnimation->StartAnimationL();
        }
    }
    
EXPORT_C void CAknPopupHeadingPane::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknControl::HandlePointerEventL( aPointerEvent ); 
    if( iExtension->iTouchObserver )
        iExtension->iTouchObserver->HandleHeadingPanePointerEventL( this, aPointerEvent );
    }    

EXPORT_C void CAknPopupHeadingPane::HandleResourceChange( TInt aType ) 
    {        
    if (iAttributes->iLayout == EQueryHeadingPane)
        {
        LayoutQueryHeadingPane();
        }
    else if (iAttributes->iLayout == EColourSelectionGridHeadingPane)
        {
        LayoutColourSelectionGridHeadingPane();
        }
    else if (iAttributes->iLayout == EMessageQueryHeadingPane)
        {
        LayoutMessageQueryHeadingPane();
        }
    else
        {
        LayoutListHeadingPane();
        }
        
    TRAP_IGNORE( DoSetPromptL() );
        
    CCoeControl::HandleResourceChange( aType );
    
    if (aType == KEikDynamicLayoutVariantSwitch)
        {
        DrawDeferred();
        }
    }

EXPORT_C void* CAknPopupHeadingPane::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

EXPORT_C void CAknPopupHeadingPane::StartAnimationL()
    {
    __ASSERT_DEBUG(iAnimation,Panic(EAknPanicNullPointer));
    SetAnimationBackGroundFrameL();
    iAnimation->StartAnimationL();
    }

EXPORT_C TInt CAknPopupHeadingPane::CancelAnimation()
    {
    __ASSERT_DEBUG(iAnimation,Panic(EAknPanicNullPointer));
    return iAnimation->CancelAnimation();
    }

EXPORT_C CAknPopupHeadingPane::CAknPopupHeadingPane()
    {
    }

void CAknPopupHeadingPane::SetAnimationBackGroundFrameL()
    {
    if (iAnimation)
        {
        // Not set background frame, if there is only one frame in animation.
        CBitmapAnimClientData *animClientData = iAnimation->BitmapAnimData();
        if (animClientData != NULL && animClientData->FrameArray().Count() <= 1)
            {
            return;
            }
        
        const TDisplayMode displayMode( 
            CCoeEnv::Static()->ScreenDevice()->DisplayMode() );
        
        CFbsBitmap* bitmap = new(ELeave) CFbsBitmap;
        CleanupStack::PushL(bitmap);
        
        User::LeaveIfError( bitmap->Create(iAnimation->Rect().Size(), displayMode ) );
        
        CFbsBitmapDevice* doubleBufferDev = CFbsBitmapDevice::NewL( bitmap );
        CleanupStack::PushL(doubleBufferDev);    
        
        CFbsBitGc* doubleBufferGc = 0;
        User::LeaveIfError( doubleBufferDev->CreateContext( doubleBufferGc ) );    
        CleanupStack::PushL(doubleBufferGc);    
        
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );
        
        AknsDrawUtils::DrawBackground( skin, cc, this, *doubleBufferGc,
                                       TPoint(0,0), iAnimation->Rect(), KAknsDrawParamDefault );
        
        CleanupStack::PopAndDestroy(2); // doubleBufferGc, doubleBufferDev
        
        CBitmapFrameData* data = CBitmapFrameData::NewL();
        data->SetBitmapsOwnedExternally( EFalse );
        data->SetBitmap( bitmap );
        
        // Set frame to animation
        iAnimation->BitmapAnimData()->SetBackgroundFrame( data ); // gets ownership
        
        CleanupStack::Pop(bitmap);
        }
    }

void CAknPopupHeadingPane::SetPageL(TInt aCurrent, TInt aMax)
    {
    if (aMax > 0 || iAttributes->iCurrentPage != aCurrent)
        {
        if (aMax > 0)
            {
            iAttributes->iMaxPage = aMax;
            }

        iAttributes->iPage->MakeVisible(iAttributes->iMaxPage > 1? ETrue: EFalse);
        iAttributes->iCurrentPage = aCurrent;
        HBufC* text = PageTextL();
        CleanupStack::PushL(text);
        iAttributes->iPage->SetTextL(*text);
        DoSetPromptL();
        CleanupStack::PopAndDestroy(); //text
        DrawDeferred();
        }
    }

HBufC* CAknPopupHeadingPane::PageTextL() const
    {
    CArrayFix<TInt>* numbers = new(ELeave)CArrayFixFlat<TInt>(2);
    CleanupStack::PushL(numbers);
    numbers->AppendL(iAttributes->iCurrentPage);
    numbers->AppendL(iAttributes->iMaxPage);
    HBufC* page = StringLoader::LoadL(
        R_AVKON_SPECIAL_CHARACTERS_PAGE_INDICATOR, *numbers, iEikonEnv);
    CleanupStack::PopAndDestroy(); // numbers
    return page;
    }

EXPORT_C void CAknPopupHeadingPane::SetSkinFrameId(const TAknsItemID &aFrameId)
    {
    if (iExtension)
        {
        iExtension->iFrameId = aFrameId;
        }
    }

EXPORT_C void CAknPopupHeadingPane::SetSkinFrameCenterId(const TAknsItemID &aFrameCenterId)
    {
    if (iExtension)
        {
        iExtension->iFrameCenterId = aFrameCenterId;
        }
    }

void CAknPopupHeadingPane::SetTouchObserver( MAknHeadingPaneTouchObserver* aTouchObserver )
    {
    iExtension->iTouchObserver = aTouchObserver;
    }

// End of File
