/*
* Copyright (c) 1999 Nokia Corporation and/or its subsidiary(-ies).
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
#include <eikenv.h>
#include <eikappui.h>
#include <eikdpsel.h>
#include <eikdpage.h>
#include <eikdialg.h>

#include <AknTasHook.h> // for testability hooks
// Include files for status pane.
// These are from AVKON which introduces undesirable dependancies.
#include <eikspane.h>
#include <aknconsts.h>
#include <akntitle.h>
#include <akncontext.h>
#include <akntabgrp.h>
#include <aknnavi.h>
#include <aknnavide.h>
#include <akntabgrp.h>
#include <avkon.hrh>
#include <eikcba.h>
// SERIES60 form laf includes
#include <AknUtils.h>
#include <avkon.rsg>
//<SKIN>
#include <AknsDrawUtils.h>
#include <AknsUtils.h>
#include <AknsListBoxBackgroundControlContext.h>
#include "eikdialogext.h"
//
// Constants
//

#define KBorderType TGulBorder::EDeepRaisedWithOutline
#define KFirstTab 0


//
// CEikTabPreStore.
//

class CEikTabPreStore : public CBase
    {
public:	    
    // Takes ownership of aTabText and aBitmapFile
    CEikTabPreStore(TInt aPageId, HBufC* aTabText, HBufC* aBitmapFile, TInt aBitmapId, TInt aMaskId);
    ~CEikTabPreStore();

    TInt PageId() const;
    HBufC* TabText() const;
    HBufC* BitmapFile() const;
    TInt BitmapId() const;
    TInt MaskId() const;

private:
    TInt iPageId;
    HBufC* iTabText;
    HBufC* iBitmapFile;
    TInt iBitmapId;
    TInt iMaskId;
    
    };

CEikTabPreStore::CEikTabPreStore(
    TInt aPageId, HBufC* aTabText, HBufC* aBitmapFile, TInt aBitmapId, TInt aMaskId )
    : iPageId( aPageId ), 
      iTabText( aTabText ), 
      iBitmapFile( aBitmapFile ), 
      iBitmapId( aBitmapId ), 
      iMaskId( aMaskId )
    {
    }
    
CEikTabPreStore::~CEikTabPreStore()
    {
    delete iTabText;
    delete iBitmapFile;
    }

TInt CEikTabPreStore::PageId() const
    {
    return iPageId;
    }
    
HBufC* CEikTabPreStore::TabText() const
    {
    return iTabText;
    }
    
HBufC* CEikTabPreStore::BitmapFile() const
    {
    return iBitmapFile;
    }
    
TInt CEikTabPreStore::BitmapId() const
    {
    return iBitmapId;
    }
    
TInt CEikTabPreStore::MaskId() const
    {
    return iMaskId;
    }

//
// CEikDialogPageSelector.
//

CEikDialogPageSelector::~CEikDialogPageSelector()
    {
    AKNTASHOOK_REMOVE();
    AknsUtils::DeregisterControlPosition(this);
    delete iPageContainer;
    delete iTabPreStore;

    DestroyTabContainer() ;

    }

CEikDialogPageSelector* CEikDialogPageSelector::NewL(const CCoeControl& aParent,CEikDialog* aDialog)
    {
    CEikDialogPageSelector* self=CEikDialogPageSelector::NewLC(aParent,aDialog);
    CleanupStack::Pop();
    return self;
    }

CEikDialogPageSelector* CEikDialogPageSelector::NewLC(const CCoeControl& aParent,CEikDialog* aDialog)
    {
    CEikDialogPageSelector* self=new(ELeave) CEikDialogPageSelector;
    CleanupStack::PushL(self);
    self->SetDialg(aDialog);
    self->SetContainerWindowL(aParent); // Not window owning
    self->ConstructL(aDialog);
    AKNTASHOOK_ADDL( self, "CEikDialogPageSelector" );
    return self;
    }

CEikDialogPageSelector* CEikDialogPageSelector::NewL(const CCoeControl& aParent,TResourceReader& aReader,CEikDialog* aDialog)
    {
    CEikDialogPageSelector* self=CEikDialogPageSelector::NewLC(aParent,aReader,aDialog);
    CleanupStack::Pop();
    return self;
    }

CEikDialogPageSelector* CEikDialogPageSelector::NewLC(const CCoeControl& aParent,TResourceReader& aReader,CEikDialog* aDialog)
    {
    CEikDialogPageSelector* self=new(ELeave) CEikDialogPageSelector;
    CleanupStack::PushL(self);
    self->SetDialg(aDialog);
    self->SetContainerWindowL(aParent);
    self->ConstructFromResourceL(aReader,aDialog);
    AKNTASHOOK_ADDL( self, "CEikDialogPageSelector" );
    return self;
    }

CEikDialogPageSelector::CEikDialogPageSelector()
    {
    iBorder.SetType(TGulBorder::ENone);
    }

void CEikDialogPageSelector::ConstructL(MEikDialogPageObserver* aPageObserver)
    {
    iContext=this;
    iPageContainer=CEikDialogPageContainer::NewL(*this,aPageObserver);
    iPageContainer->SetObserver(this);
    RegisterPageSelectorWithPageContainer();
    }

void CEikDialogPageSelector::CreatePreStoredTabL()
    {
    __ASSERT_ALWAYS( iTabContainer, User::Invariant() );
    
    // Create the first tab (if pre-stored) 
    if( iTabPreStore )
        {
        if (iTabPreStore->TabText() && iTabContainer)
            {
            // If the first tab contains text, tab layout with 2 long tabs is used
            // by default instead of 2 short tabs.           
            iTabContainer->SetTabFixedWidthL(KTabWidthWithTwoLongTabs);
            iFirstTabContainsText = ETrue;
            }
        if( ( iTabPreStore->BitmapFile() ) && 
            ( iTabPreStore->BitmapId() != -1 ) )
            {
            // Bitmapped tab..
            TFileName fileName( *(iTabPreStore->BitmapFile() ) );
            CompleteWithAppPath(fileName);                

            CFbsBitmap* bitmap;
            if( iTabPreStore->MaskId() != -1 )
                {
                // ..with mask..
                CFbsBitmap* mask;
                AknIconUtils::CreateIconLC( 
                    bitmap, 
                    mask, 
                    fileName,
                    iTabPreStore->BitmapId(), 
                    iTabPreStore->MaskId() );
                
                if( iTabPreStore->TabText() )
                    {
                    // ..and with text
                    iTabContainer->AddTabL(
                        iTabPreStore->PageId(),
                        *( iTabPreStore->TabText() ),
                        bitmap,
                        mask);
                    }
                else                        
                    {
                    // ..and without text
                    iTabContainer->AddTabL(
                        iTabPreStore->PageId(),
                        bitmap,
                        mask);
                    }

                // Note: ownership change at end of AddTabL
                CleanupStack::Pop(); // bitmap
                CleanupStack::Pop(); // mask
                }
            else
                {
                // ..without mask..
                bitmap = AknIconUtils::CreateIconL( fileName, iTabPreStore->BitmapId() );
                CleanupStack::PushL( bitmap );
                if( iTabPreStore->TabText() )
                    {
                    // ..and with text
                    iTabContainer->AddTabL(
                        iTabPreStore->PageId(),
                        *( iTabPreStore->TabText() ),
                        bitmap);
                    }
                else
                    {
                    // ..and without text
                    iTabContainer->AddTabL(
                        iTabPreStore->PageId(),
                        bitmap);
                    }

                // Note: ownership change at end of AddTabL
                CleanupStack::Pop( bitmap );
                }
            }
        else
            {
            if ( iTabPreStore->TabText() )
                {
                // Tab with text, no bitmap
                iTabContainer->AddTabL( iTabPreStore->PageId(), *( iTabPreStore->TabText() ) );
                }
            else
                {
                // Tab with no text, no bitmap.
                iTabContainer->AddTabL( iTabPreStore->PageId(), KNullDesC );
                }
            }
        }
        delete iTabPreStore;
        iTabPreStore = NULL;
    }   

void CEikDialogPageSelector::CreateTabContainerL()
    {
    if( !iTabContainer )
        {
        // Get a Tab group from the status pane.
        CEikStatusPane* statusPane = iEikonEnv->AppUiFactory()->StatusPane() ;
        if (statusPane)
            {
            CEikStatusPaneBase::TPaneCapabilities statusPaneCapabilities = statusPane->PaneCapabilities( TUid::Uid( EEikStatusPaneUidNavi ) ) ;
            if ( statusPaneCapabilities.IsPresent() && statusPaneCapabilities.IsAppOwned() )
                {
                iNaviContainer = (CAknNavigationControlContainer*)statusPane->ControlL( TUid::Uid( EEikStatusPaneUidNavi ))  ;

                iNaviDecorator = iNaviContainer->CreateTabGroupL() ;
                iTabContainer = (CAknTabGroup*)( iNaviDecorator->DecoratedControl() ) ;
                iTabContainer->SetObserver(this);

                STATIC_CAST(CCoeControl*,iNaviDecorator)->SetObserver(this); 
                
                CreatePreStoredTabL();
                }
            }
        }
    }

void CEikDialogPageSelector::ConstructFromResourceL(TResourceReader& aReader,MEikDialogPageObserver* aPageObserver)
    {
    ConstructL(aPageObserver);

    const TInt numPages=aReader.ReadInt16();
    for (TInt ii=0;ii<numPages;ii++)
        AddPageL(aReader);

    }

void CEikDialogPageSelector::SetActivePageByIdL(TInt aPageId)
    {
    iPageContainer->SetActivePageByIdL(aPageId);
    if ( iTabContainer )
    iTabContainer->SetActiveTabById(aPageId);
    DrawNow();
    }

void CEikDialogPageSelector::SetActivePageByIndexL(TInt aPageIndex)
    {
    iPageContainer->SetActivePageByIndexL(aPageIndex);
    if ( iTabContainer )
    iTabContainer->SetActiveTabByIndex(aPageIndex);
    DrawNow();
    }

void CEikDialogPageSelector::ActivateFirstPageL()
    {
    delete iTabPreStore;
    iTabPreStore = NULL;
    
    if ( iTabContainer && iTabContainer->TabCount() < 2 )
        DestroyTabContainer() ;
    else
        {
        if ( iNaviContainer && iNaviDecorator )
            {
            iNaviContainer->Pop( iNaviDecorator );
            iNaviContainer->PushL( *iNaviDecorator ) ;
            iTabsVisible = ETrue ;
            }
        }

#if defined(_DEBUG)
    iPageContainer->ActivateFirstPageL();
    if ( iTabContainer )
        iTabContainer->SetActiveTabByIndex( KFirstTab );  //<<-- AknTab
#else
    iPageContainer->ActivateFirstPageL();
    if ( iTabContainer )
        iTabContainer->SetActiveTabByIndex( KFirstTab );  //<<-- AknTab
#endif
    }

void CEikDialogPageSelector::AddPageL(TResourceReader& aReader) 
    {
    TInt pageId;
    if( iPageContainer->NumPages() == 0 )
        {
        // This is the first page -- save tab details for delayed tab construction
        __ASSERT_ALWAYS( !iTabPreStore, User::Invariant() );
        
        pageId = aReader.ReadInt16(); // tab id
        HBufC* tabText = aReader.ReadHBufCL();
        CleanupStack::PushL( tabText );        
        HBufC* bitmapFile = aReader.ReadHBufCL();
        CleanupStack::PushL( bitmapFile );
        TInt bitmapId = aReader.ReadInt16();
        TInt maskId = aReader.ReadInt16();
        
        iTabPreStore = new (ELeave) CEikTabPreStore(
            pageId, tabText, bitmapFile, bitmapId, maskId );
            
        CleanupStack::Pop( bitmapFile );
        CleanupStack::Pop( tabText );
        }
    else
        {
        // Create tab container on second page
        CreateTabContainerL();
        
        if ( iTabContainer )
            {            
            pageId = iTabContainer->AddTabL(aReader); // Might need to read tab info from resource
            if (iFirstTabContainsText && iPageContainer->NumPages() == 2)
                {
                // Change the tab layout to 3 long tabs if there are 3 or more dialog pages.
                iTabContainer->SetTabFixedWidthL(KTabWidthWithThreeLongTabs);                
                }
            }
        else
            {
            pageId = aReader.ReadInt16(); // tab id
            aReader.ReadTPtrC(); // text
            aReader.ReadTPtrC(); // bmp filename
            aReader.ReadInt16(); // bmp id
            aReader.ReadInt16(); // bmp mask id
            }
        }
    
    TResourceReader pageReader;

    // This bit changed to check if  "lines=" exists
    // not correct yet as we still need to create a page!
    TInt32 pageReaderID = aReader.ReadInt32() ;
    if ( pageReaderID != 0 )
        {
        iCoeEnv->CreateResourceReaderLC( pageReader, pageReaderID ) ;
        iPageContainer->AddPageL(pageId,pageReader);
    CleanupStack::PopAndDestroy(); // pageReader
        }
    else
        iPageContainer->AddPageL( pageId ) ;

    AddFormToPageL(  pageId, aReader ) ;
    
    // read page flags, those are not used anywhere 
    aReader.ReadInt16();
    }

void CEikDialogPageSelector::AddPageL(TInt aPageId,const TDesC& aTabText)
    {
    if( iPageContainer->NumPages() == 0 )
        {
        // This is the first page -- save tab details for delayed tab construction
        __ASSERT_ALWAYS( !iTabPreStore, User::Invariant() );

        HBufC* tabText = aTabText.AllocL();
        CleanupStack::PushL( tabText );

        iTabPreStore = new (ELeave) CEikTabPreStore(
            aPageId, tabText, NULL, -1, -1 );
            
        CleanupStack::Pop(tabText);
        }
    else
        {
        // Create tab container on second page
        CreateTabContainerL();
        
        if ( iTabContainer )
            iTabContainer->AddTabL(aPageId,aTabText);
        }
    
    iPageContainer->AddPageL(aPageId);

    if(iPageContainer->NumPages()>1)
        iBorder.SetType(KBorderType);
    }

void CEikDialogPageSelector::AddPageL(TInt aPageId,const TDesC& aTabText,TResourceReader& aReader)
    {
    if( iPageContainer->NumPages() == 0 )
        {
        // This is the first page -- save tab details for delayed tab construction
        __ASSERT_ALWAYS( !iTabPreStore, User::Invariant() );

        HBufC* tabText = aTabText.AllocL();
        CleanupStack::PushL( tabText );

        iTabPreStore = new (ELeave) CEikTabPreStore(
            aPageId, tabText, NULL, -1, -1 );

        CleanupStack::Pop( tabText );
        }
    else
        {
        // Create tab container on second page
        CreateTabContainerL();
        
        if ( iTabContainer )
            iTabContainer->AddTabL(aPageId,aTabText);
        }

    iPageContainer->AddPageL(aPageId,aReader);

    AddFormToPageL(  aPageId, aReader ) ;

    if(iPageContainer->NumPages()>1)
        iBorder.SetType(KBorderType);
    }

CEikCaptionedControl* CEikDialogPageSelector::Line(TInt aControlId) const
    {
    return iPageContainer->Line(aControlId);
    }

CEikCaptionedControl* CEikDialogPageSelector::LineOrNull(TInt aControlId) const
    {
    return iPageContainer->LineOrNull(aControlId);
    }

CEikCaptionedControl* CEikDialogPageSelector::CurrentLine() const
    {
    return iPageContainer->CurrentLine();
    }

void CEikDialogPageSelector::SetPageDensePacked(TInt aPageId,TBool aDensePacked)
    {
    iPageContainer->SetPageDensePacked(aPageId,aDensePacked);
    }

void CEikDialogPageSelector::SetAllPagesDensePacked(TBool aDensePacked)
    {
    iPageContainer->SetAllPagesDensePacked(aDensePacked);
    }

void CEikDialogPageSelector::SetPageDimmed(TInt aPageId,TBool aDimmed,TDrawNow aDrawNow)
    {
    iPageContainer->SetPageDimmed(aPageId,aDimmed,aDrawNow);
    if ( iTabContainer )
        iTabContainer->DimTab(aPageId,aDimmed);  //<<-- AknTab
    }

TInt CEikDialogPageSelector::LineId(const CCoeControl& aControl) const
    {
    return iPageContainer->LineId(aControl);
    }

void CEikDialogPageSelector::DeleteLine(TInt aLineId,TBool aRedraw)
    {
    iPageContainer->DeleteLine(aLineId, aRedraw);
    }

void CEikDialogPageSelector::InsertLineL(TInt aPosition,TInt aPageId,TInt aResourceId)
    {
    iPageContainer->InsertLineL(aPosition,aPageId,aResourceId);
    }

void CEikDialogPageSelector::AdjustAllIds(TInt aPageId,TInt aControlIdDelta)
    {
    iPageContainer->AdjustAllIds(aPageId,aControlIdDelta);
    }

CCoeControl* CEikDialogPageSelector::CreateLineByTypeL(const TDesC& aCaption,TInt aControlId,TInt aControlType,TAny* aReturnValue)
    {
    return iPageContainer->CreateLineByTypeL(aCaption,aControlId,aControlType,aReturnValue);
    }

CCoeControl* CEikDialogPageSelector::CreateLineByTypeL(const TDesC& aCaption,TInt aPageId,TInt aControlId,TInt aControlType,TAny* aReturnValue)
    {
    return iPageContainer->CreateLineByTypeL(aCaption,aPageId,aControlId,aControlType,aReturnValue);
    }

void CEikDialogPageSelector::FocusLineL(TInt aLineId)
    {
    TInt newPageIndex=iPageContainer->FindPageIndexForLineId(aLineId);
    
    if (newPageIndex>=0)
        {
        if ( iTabContainer )
        iTabContainer->SetFocus(EFalse);
        iPageContainer->SetFocus(EFalse);
        SetActivePageByIndexL(newPageIndex);
        }

    iPageContainer->FocusLineL(aLineId);
    }

TInt CEikDialogPageSelector::FocusedLineId() const
    {
    return iPageContainer->FocusedLineId();
    }

void CEikDialogPageSelector::GetAutoValues()
    {
    iPageContainer->GetAutoValues();
    }

TInt CEikDialogPageSelector::ActivePageId() const
    {
    return iPageContainer->ActivePageId();
    }

TInt CEikDialogPageSelector::ActivePageIndex() const
    {
    return iPageContainer->ActivePageIndex();
    }

void CEikDialogPageSelector::SizeChanged()
    {
    const TInt borderThickness = iBorder.SizeDelta().iWidth;
    const TSize pageContainerSize( iSize.iWidth - borderThickness, iSize.iHeight - borderThickness / 2 );

    if ( iIsForm )
        {
        iPageContainer->SetPageFormSized();
        }
    else
        {
        iPageContainer->SetExtent( TPoint( iPosition.iX + borderThickness / 2, iPosition.iY ), pageContainerSize );
        }

    AknsUtils::RegisterControlPosition(this);
    }

TKeyResponse CEikDialogPageSelector::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    if (Dialg()->DialogFlags() & EEikDialogFlagDontEatUpDownEvents)
        {
        // Forward up/down events...
        if (aType!=EEventKey)
        return iPageContainer->OfferKeyEventL(aKeyEvent,aType);
        }
    else
        {
        // ignore up/down events...
        if (aType!=EEventKey)
        return EKeyWasNotConsumed;
        }

    TKeyResponse keyResponse=EKeyWasNotConsumed;

    switch (aKeyEvent.iCode)
        {
        case EKeyUpArrow:
        case EKeyDownArrow:
      case EKeyPrevious:
	  case EKeyNext:        
                {   // Single page dialog.
                keyResponse=iPageContainer->OfferUpDownKeyEventL(aKeyEvent,aType,CEikDialogPage::ENonCyclic);
                }
            break;
        case EKeyLeftArrow:
        case EKeyRightArrow:
            if ( iTabContainer && ( iTabContainer->TabCount() > 1 ) && !iEditable )
                keyResponse=iTabContainer->OfferKeyEventL(aKeyEvent,aType);
            else
                keyResponse=iPageContainer->OfferKeyEventL(aKeyEvent,aType);
            break;
        default:
            keyResponse=iPageContainer->OfferKeyEventL(aKeyEvent,aType);
        }

    return keyResponse;
    }

TSize CEikDialogPageSelector::MinimumSize()
    {
    const TSize pageContainerSize=iPageContainer->MinimumSize();
    const TSize minSize(pageContainerSize.iWidth,pageContainerSize.iHeight);
    return minSize;
    }

TSize CEikDialogPageSelector::PreferredSize(const TSize& aMaxSize) const
    {
    const TInt borderThickness(iBorder.SizeDelta().iWidth);

    const TSize maxSize(aMaxSize.iWidth-borderThickness,aMaxSize.iHeight-borderThickness/2);
    const TSize pageContainerPreferredSize(iPageContainer->PreferredSize(maxSize));

    TSize preferredSize(pageContainerPreferredSize.iWidth,pageContainerPreferredSize.iHeight);
    preferredSize.iWidth=Min(preferredSize.iWidth+borderThickness,aMaxSize.iWidth);
    preferredSize.iHeight=Min(preferredSize.iHeight+borderThickness/2,aMaxSize.iHeight);
    return preferredSize;
    }

TInt CEikDialogPageSelector::CountComponentControls() const
    {
    return 1 ;
    }

CCoeControl* CEikDialogPageSelector::ComponentControl(TInt /*aIndex*/) const
    {
    return iPageContainer;
    }

void CEikDialogPageSelector::PrepareContext(CWindowGc& aGc) const
    {
    if ( iIsForm && AknsUtils::AvkonSkinEnabled() )
        aGc.SetBrushStyle( CGraphicsContext::ENullBrush );
    else
        aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    }

void CEikDialogPageSelector::Draw(const TRect& aRect) const
    {
    DrawBorder(aRect);
    DrawBackground(aRect);
    }

void CEikDialogPageSelector::DrawBorder(const TRect& aRect) const
    {
    TRect innerRect(iPageContainer->Position(),iPageContainer->Size()) ;
    TRect rect=iBorder.OuterRect(innerRect);
    CWindowGc& gc=SystemGc();
    rect.Intersection(aRect); 
    iBorder.Draw(gc,rect);
    }

void CEikDialogPageSelector::DrawBackground(const TRect& aRect) const
    { // if no arguments provided, redraw whole screen.
    // If the Page contains a form then form formatting is required.  A horizontal line is required between the
    // bottom item and the CBA below the data side (not the caption side).  It must not be in the scrolling area
    // hence it's drawn outside the page container.  Note that the page container is shrunk by 1 pixel in SizeChanged() to create
    // space for the line.  (TimW 18th May 2000)
    // <SKIN> This should be the first place to deal with skin stuff.  It is the parent area for the dialog and shows at the top and 
    // bottom.  There might be issues about the vertical line and tiling background bitmaps.  There might also be something about 
    // area underneath the horzontal line (not tiled)
    MAknsSkinInstance* skin = AknsUtils::SkinInstance() ;
    TBool drawSkin = AknsUtils::AvkonSkinEnabled() ;
    CAknsListBoxBackgroundControlContext* cc = iDialg->Extension()->iBgContext ;

    CWindowGc& gc=SystemGc();
    if ( iIsForm )
        {
        if (!iPageContainer->Page(iPageContainer->ActivePageId())->AnythingToDisplay())
            {
// Added to obtain a clear screen to display "no data" text.
            if ( drawSkin )
                {
                TRect empty( TPoint( 0, 0 ), TPoint ( 0, 0 ) ) ;
                cc->SetTiledRect( empty ) ;
                AknsDrawUtils::Background( skin, cc, this, gc, aRect ) ;
                }
            else
                {
                gc.Clear(aRect);
                }
            return;
            }

        // Draw the vertical and horizontal lines on the page
        TAknLayoutRect iVertLine1, iVertLine2, iHoriLine;    
        CEikDialogPage* dialogPage = iPageContainer->Page( iPageContainer->ActivePageId() );
        if ( dialogPage )
            {
            if (dialogPage->FormLayout() == CEikDialogPage::ESingle )
                {
                // <SKIN> Get the bitmaps for tiling here.
                if ( drawSkin )
                    cc->SetTiledBitmap( KAknsIIDQsnBgColumnAB ) ;

                // List single heading pane uses BC columns (Table 65)
                iVertLine1.LayoutRect( Rect(), AKN_LAYOUT_WINDOW_List_pane_lines__BC_columns__Line_1( 0 ) );
                iVertLine2.LayoutRect( Rect(), AKN_LAYOUT_WINDOW_List_pane_lines__BC_columns__Line_1( 1 ) );
                iHoriLine.LayoutRect( Rect(), AKN_LAYOUT_WINDOW_List_pane_lines__BC_columns__Line_2 );
                }
        // For double line format 
            else
                {
                if (dialogPage->GetFormFlags()&EEikFormShowBitmaps) 
                    {
                    // <SKIN> Get the bitmaps for tiling here.
                    if ( drawSkin )
                        cc->SetTiledBitmap( KAknsIIDQsnBgColumnA ) ;

                    iVertLine1.LayoutRect( Rect(), AKN_LAYOUT_WINDOW_List_pane_lines__AB_columns__Line_1( 0 ) );
                    iVertLine2.LayoutRect( Rect(), AKN_LAYOUT_WINDOW_List_pane_lines__AB_columns__Line_1( 1 ) );
                    iHoriLine.LayoutRect( Rect(), AKN_LAYOUT_WINDOW_List_pane_lines__AB_columns__Line_2 );
                    }
                else
                    {
                    // <SKIN> Get the bitmaps for tiling here.
                    if ( drawSkin )
                        cc->SetTiledBitmap( KAknsIIDQsnBgColumnA ) ;

                    iVertLine1.LayoutRect( Rect(), AKN_LAYOUT_WINDOW_List_pane_lines__A_column__Line_1( 0 ) );
                    iVertLine2.LayoutRect( Rect(), AKN_LAYOUT_WINDOW_List_pane_lines__A_column__Line_1( 1 ) );
                    iHoriLine.LayoutRect( Rect(), AKN_LAYOUT_WINDOW_List_pane_lines__A_column__Line_2);
                    }
                }

            TBool skinDrawn = EFalse;
            if ( drawSkin )
                {
                // <SKIN> Drawing the background stuff.
                TRect columnRect = Rect() ;
                if ( AknLayoutUtils::LayoutMirrored() )
                    {
                    columnRect.iTl.iX = iVertLine1.Rect().iTl.iX ;
                    }
                else
                    {
                    columnRect.iBr.iX = iVertLine1.Rect().iTl.iX ;
                    }
                cc->SetTiledRect( columnRect ) ;

                if ( AknsDrawUtils::Background( skin, cc, this, gc, Rect() ) )
                    {
                    skinDrawn = ETrue;
                    }
                }

            if ( !skinDrawn )
                {
                iVertLine1.DrawRect(gc);
                iVertLine2.DrawRect(gc);            
                iHoriLine.DrawRect(gc);
                }

            }
        }
    }

void CEikDialogPageSelector::HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType)
    {
    switch (aEventType)
        {
        case EEventPrepareFocusTransition:
            PrepareForFocusTransitionL();
            break;
        case EEventRequestFocus:
            HandleRequestFocusL(aControl);
            break;
        case EEventStateChanged:
            if (aControl==iNaviDecorator) 
                HandleTabStateChangedL((CAknTabGroup*)STATIC_CAST(CAknNavigationDecorator*,aControl)->DecoratedControl());
            else
                PassOnEventL(aControl,aEventType);
            break;
        case EEventInteractionRefused:
            // *** ToDo
            break;
        default:
            break;
        }
    }

void CEikDialogPageSelector::PrepareForFocusTransitionL()
    {
    if (iPageContainer && iPageContainer->IsFocused())
        iPageContainer->PrepareForFocusLossL();
    else if (iTabContainer && iTabContainer->IsFocused())
        iTabContainer->PrepareForFocusLossL();
    }

void CEikDialogPageSelector::HandleRequestFocusL(CCoeControl* aControl)
    {
    if (aControl==iTabContainer)
        {
        if (iPageContainer) iPageContainer->SetFocus(EFalse,EDrawNow);
        if (iTabContainer) iTabContainer->SetFocus(ETrue,EDrawNow);
        }
    else
        {
        if (iTabContainer) iTabContainer->SetFocus(EFalse,EDrawNow);
        if (iPageContainer) iPageContainer->SetFocus(ETrue,EDrawNow);
        }
    }

void CEikDialogPageSelector::HandleTabStateChangedL(CAknTabGroup* aTabContainer) //<<--AknTab
    {
    if(iPageContainer->ActivePageIndex() != aTabContainer->ActiveTabIndex())
        {
        iPageContainer->SetFocus(EFalse,EDrawNow);
        iPageContainer->SetActivePageByIndexL(aTabContainer->ActiveTabIndex());
        DrawDeferred();
        }
    }

void CEikDialogPageSelector::PassOnEventL(CCoeControl* aControl,MCoeControlObserver::TCoeEvent aEvent)
    {
    MCoeControlObserver* observer=Observer();
    if (observer)
        observer->HandleControlEventL(aControl,aEvent);
    }

void CEikDialogPageSelector::SetInitialFocus()
    {
    if ( iTabContainer && ( iTabContainer->TabCount() > 1 ) )
        iTabContainer->SetActiveTabByIndex( KFirstTab ); //<<--AknTab

    iPageContainer->SetInitialFocus();
    }

void CEikDialogPageSelector::ResetLineMinimumSizes()
    {
    iPageContainer->ResetLineMinimumSizes();
    }

TInt CEikDialogPageSelector::FindLineIndex(const CCoeControl& aControl) const
    {
    return iPageContainer->FindLineIndex(aControl);
    }

TBool CEikDialogPageSelector::RotateFocusByL(TInt aDelta)
    {
    return iPageContainer->RotateFocusByL(aDelta);
    }

TKeyResponse CEikDialogPageSelector::OfferHotKeysKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    return iPageContainer->OfferHotKeysKeyEventL(aKeyEvent,aType);
    }

TBool CEikDialogPageSelector::TakesEnterKey()
    {
    return iPageContainer->TakesEnterKey();
    }


void CEikDialogPageSelector::AddFormToPageL( TInt aPageId,TResourceReader& aReader ) 
    {
    // This function process FORM structures in the DIALOG resource
    // Is there a FORM on the page?
    TInt32 formReaderID ;
    formReaderID = aReader.ReadInt32()  ; 
    
    if ( formReaderID != 0 )
        {
        // SB creation moved here, 
        // because at the moment only forms use dialog's SB
        iPageContainer->CreateScrollBarL(*this);
        iIsForm = ETrue ;
        TResourceReader formReader ;
        iCoeEnv->CreateResourceReaderLC( formReader, formReaderID ) ;
        // Find the dialog page 
        CEikDialogPage* targetPage = iPageContainer->Page( aPageId ) ;
        // instruct it to create form controls
        targetPage->ConstructFormFromResourceL( formReader ) ;
        CleanupStack::PopAndDestroy() ; //formReader
        }
    }

void CEikDialogPageSelector::SetEditableL( TBool aEditable) 
    {
// These should be uncommented on submission 
//  _LIT(KPanicNotDialog,"Form resource not used");
//  __ASSERT_DEBUG(iIsForm,User::Panic(KPanicNotDialog,0));

    iEditable = aEditable ;
    if ( iEditable )
        { // In editable mode hide the tab container 
        if ( iNaviContainer && iTabContainer && iTabContainer->TabCount() > 1 && iTabsVisible )
            {
            iNaviContainer->Pop( iNaviDecorator ) ;
            iTabsVisible = EFalse ;
            }
        }
    else
        { // in View mode show the tab container
        if ( iNaviContainer && iNaviDecorator && iTabContainer && iTabContainer->TabCount() > 1 && !iTabsVisible )
            {
            iNaviContainer->PushL( *iNaviDecorator ) ;
            iTabsVisible = ETrue ;
            }
        }
    iPageContainer->SetEditableL( iEditable ) ;
    }

TInt CEikDialogPageSelector::NumPages() const 
    {
    return iPageContainer->NumPages() ;
    }

void CEikDialogPageSelector::DestroyTabContainer() 
    {
    if ( iNaviDecorator )
        {
        delete iNaviDecorator ;
        iNaviDecorator = NULL ;
        iTabContainer = NULL ;
        iTabsVisible = EFalse; // deletion will pop decorator from stack.
        }
    }

CEikDialogPageContainer*  CEikDialogPageSelector::PageContainer()
    {
    return iPageContainer;
    }


/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 *
 * @internal
 * @since App-Framework_6.1
 */
#ifndef _DEBUG
void CEikDialogPageSelector::WriteInternalStateL(RWriteStream&) const
    {}
#else
void CEikDialogPageSelector::WriteInternalStateL(RWriteStream& aWriteStream) const
    {
    CCoeControl::WriteInternalStateL(aWriteStream);
    }
#endif

void  CEikDialogPageSelector::Reserved_2()
    {
    }

void CEikDialogPageSelector::SetDialg(CEikDialog* aDialg)
    {
    iDialg=aDialg;
    };

void CEikDialogPageSelector::RegisterPageSelectorWithPageContainer()
    {
    if (iPageContainer)
        iPageContainer->SetPageSelector(this);
    };

CEikDialog* CEikDialogPageSelector::Dialg() const
    {
    return iDialg;
    }

TBool CEikDialogPageSelector::IsForm() const
    {
    return iIsForm;
    }

void CEikDialogPageSelector::TabChangedL(TInt aIndex)
    {
    iPageContainer->SetActivePageByIndexL(aIndex);
    DrawNow();
    }
 


/* =====================================
 * Tool Tip Manager.
 * SERIES60 Forms have a tool tip feature allowing a piece of text
 * to be displayed in the Navi Pane when an input control has the focus.
 * This little class ensures that tool tip functionality is located in one
 * place and that no memory is leaked.
 * =====================================
 */

CEikDlgToolTipMgr::CEikDlgToolTipMgr( CEikonEnv* aEikonEnv ) :
iToolTip( NULL ) ,
iShowTips( EFalse ) ,
iIsTipShowing( EFalse )
    {
    CEikStatusPane* statusPane = aEikonEnv->AppUiFactory()->StatusPane() ;
    if (statusPane)
        {
        CEikStatusPaneBase::TPaneCapabilities statusPaneCapabilities = statusPane->PaneCapabilities( TUid::Uid( EEikStatusPaneUidNavi ) ) ;
        if ( statusPaneCapabilities.IsPresent() && statusPaneCapabilities.IsAppOwned() )
            { // continue
            TRAP_IGNORE(iNaviContainer = (MAknNavigationContainerInterface*)(CAknNavigationControlContainer*)statusPane->ControlL( TUid::Uid( EEikStatusPaneUidNavi ))) ;
            }
        }
    }

CEikDlgToolTipMgr::~CEikDlgToolTipMgr() 
    {
    if ( iIsTipShowing )
        HideTip() ;
    }

void CEikDlgToolTipMgr::DisplayTipL( const TDesC* aTipText ) 
    {
    if ( iShowTips )
        {
        User::LeaveIfNull(iNaviContainer);

        MAknNavigationDecoratorInterface* newToolTip;

        //push the new tip
        if ( aTipText  && aTipText->Length() )
            newToolTip = iNaviContainer->CreateMessageLabelL( *aTipText ) ;
        else
            newToolTip = iNaviContainer->CreateMessageLabelL( _L("") ) ;
         
        CleanupStack::PushL(newToolTip);
        iNaviContainer->PushL( (CAknNavigationDecorator&)*newToolTip ) ;
        CleanupStack::Pop();

        //pop the new tip
        HideTip();

        iToolTip = newToolTip;

        iIsTipShowing = ETrue ;
        }
    }

void CEikDlgToolTipMgr::HideTip() 
    {
    if ( iIsTipShowing )
        {
        // Destroy the tip that's just been popped
        delete iToolTip ;
        iToolTip = NULL ;

        iIsTipShowing = EFalse ;
        }
    }

void CEikDlgToolTipMgr::EnableTips( TBool aShowTips ) 
    {
    if ( iNaviContainer )
        {
        iShowTips = aShowTips ;
        if ( !iShowTips )
            // Hide the current tip if tips are being switched off
            HideTip() ;
        }
    }
