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


#include "HgPopupDrawer.h"
#include "HgConstants.h"

#include <gdi.h>
#include <AknUtils.h>
#include <AknsDrawUtils.h>
#include <bitstd.h>
#include <skinlayout.cdl.h>
#include <layoutmetadata.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <aknlayoutscalable_apps.cdl.h>


THgPopupDrawer::THgPopupDrawer()
    {
    }

void THgPopupDrawer::Init(  TRect aRect, const CFont* aFont )
    {
    iRect = aRect;
    iFont = aFont;
    iLongestMonth = 0;
    }

void THgPopupDrawer::InitLongestMonth()
    {
    TTime time;
    time.HomeTime();
    TDateTime date = time.DateTime();
    date.SetMonth(EJanuary);
    time = date;
    
    TFileName month;
    month.Zero();
    
    for(TInt i = 0; i < 12; ++i)
        {
        TRAP_IGNORE
            (
            time.FormatL(month, KGanesMonthString);
            )
        time += TTimeIntervalMonths(1);
        TInt monthLen = iFont->TextWidthInPixels(month); 
        iLongestMonth = monthLen > iLongestMonth ? monthLen : iLongestMonth;
        }
    }

void THgPopupDrawer::Draw( CWindowGc& aGc, const TDesC& aDesc )
    {
    // Resolve rect for the popup "window"
    const TInt textLength = iFont->TextWidthInPixels( aDesc );
    TInt width = iRect.Width()/KPopupWidthDiv > textLength + KPopupTextExtraPadding ? 
        iRect.Width()/KPopupWidthDiv : textLength + KPopupTextExtraPadding;
    TInt height = (iFont->FontMaxHeight() * 2);
    
    // calculate the position of the popup
    TPoint pos(((iRect.Width() - width )/2), (iRect.Height() - height)/2);
    TRect area( pos, TSize( width, height) );

    // First draw background box, after that the text
    DrawBackground(aGc, area);
    
    InitFont(aGc);

    // Draw Text
    TPoint point( area.iTl );
    point.iY += iFont->FontMaxAscent() + ((area.Height() - iFont->FontMaxHeight()) / 2);

    TRAP_IGNORE(
            TBidiText* text = TBidiText::NewL( aDesc, 1 );
            text->WrapText(area.Width(), *iFont, NULL);
            if(text->Directionality() == TBidiText::ELeftToRight ) 
                {
                point.iX += (area.Width() - textLength)/2;
                }
            else
                {
                point.iX -= (area.Width() - textLength)/2;
                }
        
            text->DrawText( aGc, point );
            delete text;
        )
    }

void THgPopupDrawer::DrawNaviChar( CWindowGc& aGc, const TDesC& aDesc )
    {
    TRgb normal;
    AknsUtils::GetCachedColor(AknsUtils::SkinInstance(), 
            normal, 
            KAknsIIDQsnTextColors, 
            EAknsCIQsnTextColorsCG6 );

    TAknLayoutRect layout;
    layout.LayoutRect(iRect, AknLayoutScalable_Apps::popup_navstr_preview_pane(0));

    DrawBackground( aGc, layout.Rect() );
    
    TAknLayoutText textLayout;
    textLayout.LayoutText(layout.Rect(), AknLayoutScalable_Apps::popup_navstr_preview_pane_t1(0).LayoutLine());
    textLayout.DrawText(aGc, aDesc, ETrue, normal );
    
    }

void THgPopupDrawer::Draw( CWindowGc& aGc, 
        const TDesC& aDesc1,
        const TDesC& aDesc2
        )
    {
    // init longest month value.
    if(!iLongestMonth)
        InitLongestMonth();
    
    // Resolve rect for the popup "window"
    TInt d1Length = iFont->TextWidthInPixels( aDesc1 );
    TInt d2Length = iFont->TextWidthInPixels( aDesc2 );
    
    // Calculate the dimensions
    TInt width = iRect.Width()/KPopupWidthDiv > iLongestMonth + KPopupTextExtraPadding ? 
        iRect.Width()/KPopupWidthDiv : iLongestMonth + KPopupTextExtraPadding;
    TInt height = (iFont->FontMaxHeight() * 3);
    
    // calculate the position of the popup
    TPoint pos(((iRect.Width() - width )/2), (iRect.Height() - height)/2);
    TRect area( pos, TSize( width, height) );

    // First draw background box, after that the text
    DrawBackground(aGc, area);

    InitFont(aGc);
    
    // First text
    TPoint point( area.iTl );
    point.iY += iFont->FontMaxAscent() + (iFont->FontMaxHeight() / 2);
    TRAP_IGNORE(
            TBidiText* text = TBidiText::NewL( aDesc1, 1 );
            text->WrapText(area.Width(), *iFont, NULL);
            if(text->Directionality() == TBidiText::ELeftToRight ) 
                {
                point.iX += (area.Width() - d1Length)/2;
                }
            else
                {
                point.iX -= (area.Width() - d1Length)/2;
                }
        
            text->DrawText( aGc, point );
            delete text;
        )

    // Second text
    point.iX = area.iTl.iX;
    point.iX += (area.Width() - d2Length)/2;
    point.iY += iFont->FontMaxHeight();
    aGc.DrawText(aDesc2, point );
    }

void THgPopupDrawer::DrawBackground( CWindowGc& aGc, const TRect& aRect )
    {
    TAknLayoutRect cornerRect;
    // skinned draw uses submenu popup window skin (skinned border)
    cornerRect.LayoutRect(
        aRect,
        SkinLayout::Submenu_skin_placing_Line_2() );
    
    TRect innerRect( aRect );
    innerRect.Shrink( cornerRect.Rect().Width(), cornerRect.Rect().Height() );
    
    if ( !AknsDrawUtils::DrawFrame(
            AknsUtils::SkinInstance(),
            aGc,
            aRect,
            innerRect,
            KAknsIIDQsnFrPopupSub,
            KAknsIIDQsnFrPopupCenterSubmenu ) )
        {
        // skinned border failed -> black border
        aGc.SetPenStyle( CGraphicsContext::ESolidPen );
        aGc.SetBrushColor( KRgbBlack );
        aGc.DrawRect( aRect );
        }
    }

void THgPopupDrawer::InitFont(CWindowGc& aGc)
    {
    // Get color for the text from the skin.
    TRgb normal;
    AknsUtils::GetCachedColor(AknsUtils::SkinInstance(), 
            normal, 
            KAknsIIDQsnTextColors, 
            EAknsCIQsnTextColorsCG6 );
    
    // Draw text
    aGc.UseFont( iFont );
    aGc.SetPenColor(normal);    
    }

