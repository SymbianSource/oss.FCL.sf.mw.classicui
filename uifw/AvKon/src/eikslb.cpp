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


#include <eikslb.h>
#include <eikfrlb.h>
#include <eikslbd.h>
#include <AknUtils.h>
#include <featmgr.h>
#include "eikslbProt.h"
#include "eikslbProtFactory.h"
#include <layoutmetadata.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>

#include <AknTasHook.h>
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
#include <aknlistloadertfx.h>
#include <aknlistboxtfxinternal.h>
#endif

#include "akntrace.h"
//
// settings itemdrawer
//

EXPORT_C CSettingsListBoxItemDrawer::CSettingsListBoxItemDrawer( MTextListBoxModel* aTextListBoxModel,
                                                                 const CFont* aFont,
                                                                 CSettingsListBoxData* aSettingsData)
    : CFormattedCellListBoxItemDrawer( aTextListBoxModel, aFont, aSettingsData )
    {
    }

EXPORT_C CSettingsListBoxItemDrawer::~CSettingsListBoxItemDrawer()
    {
    }

EXPORT_C CSettingsListBoxData* CSettingsListBoxItemDrawer::SettingsData() const
    {
    return STATIC_CAST(CSettingsListBoxData*,iData);
    }

EXPORT_C void CSettingsListBoxItemDrawer::DrawItemText( TInt aItemIndex,
                                                        const TRect& aItemTextRect,
                                                        TBool aItemIsCurrent,
                                                        TBool /*aViewIsEmphasized*/,
                                                        TBool /*aItemIsSelected*/) const
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE("DrawItemText: aItemIndex=%d, aItemTextRect=(%d,%d,%d,%d), aItemIsCurrent=%d",
            aItemIndex, aItemTextRect.iTl.iX, aItemTextRect.iTl.iY, aItemTextRect.iBr.iX,
            aItemTextRect.iBr.iY, aItemIsCurrent);
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal( iGc );
    if ( transApi )
        {
        transApi->StartDrawing( MAknListBoxTfxInternal::EListNotSpecified );
        }
#endif //RD_UI_TRANSITION_EFFECTS_LIST
    iGc->SetBrushColor( AKN_LAF_COLOR( 0 ) );
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    if ( transApi )
        {
        transApi->StopDrawing();
        }
#endif //RD_UI_TRANSITION_EFFECTS_LIST

    DrawBackgroundAndSeparatorLines( aItemTextRect );

    if ( aItemIsCurrent )
        {
        FormattedCellData()->SetCurrentItemIndex( aItemIndex );
        }
        
    FormattedCellData()->SetCurrentlyDrawnItemIndex( aItemIndex );

    FormattedCellData()->DrawSettingHighlight( *iGc, aItemTextRect, aItemIsCurrent );

    TBool drawBackground = ETrue;
    TPtrC temp = iModel->ItemText( aItemIndex );
    TPtrC columnText;

    TextUtils::ColumnText( columnText, 3, &temp );
    
    if ( columnText == KNullDesC )
        {
        drawBackground = EFalse;
        }

#ifdef RD_UI_TRANSITION_EFFECTS_LIST 
    if ( transApi )
        {
        transApi->StartDrawing( MAknListBoxTfxInternal::EListItem );
        iGc->SetClippingRect( iViewRect );
        }
#endif // RD_UI_TRANSITION_EFFECTS_LIST

    // draw setting item's background
    if ( drawBackground )
        {
        TAknLayoutRect outerRect;
        TAknWindowComponentLayout valuePane;
#ifdef RD_LIST_STRETCH                
        if ( Layout_Meta_Data::IsLandscapeOrientation() && 
             Layout_Meta_Data::IsListStretchingEnabled() &&
             FormattedCellData()->StretchingEnabled() )
            {
            valuePane = AknLayoutScalable_Avkon::set_value_pane_cp_vc( 0 );
            }
        else
#endif // RD_LIST_STRETCH
            {
            valuePane = AknLayoutScalable_Avkon::set_value_pane_cp( 0 );
            }
                
        outerRect.LayoutRect( aItemTextRect, TAknWindowComponentLayout::Compose(
                              valuePane,
                              AknLayoutScalable_Avkon::bg_set_opt_pane( 0 ) ).LayoutLine() );

        TBool frameDrawn = EFalse;
        MAknsControlContext *cc = AknsDrawUtils::ControlContext( FormattedCellData()->Control() );
        
        if ( !cc )
            {
            cc = FormattedCellData()->SkinBackgroundContext();
            }

        if ( cc )
            {
            TAknLayoutRect innerRect;
            innerRect.LayoutRect( aItemTextRect, TAknWindowComponentLayout::Compose(
                                  valuePane,
                                  AknLayoutScalable_Avkon::bg_set_opt_pane_g1() ).LayoutLine() );

            frameDrawn = AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(), 
                                                   *iGc, 
                                                   outerRect.Rect(), 
                                                   innerRect.Rect(),
                                                   KAknsIIDQsnFrSetOptFoc, 
                                                   KAknsIIDQsnFrSetOptFocCenter );
            }
                
        if ( !frameDrawn )
            {
            iGc->SetBrushColor( AKN_LAF_COLOR( 243 ) );
            iGc->Clear( outerRect.Rect() );
            }
        }

    SetupGc( aItemIndex );
        
    CFormattedCellListBoxData::TColors colors;
    
    TBufC<KMaxTotalDataLength> target;

    // Try to allocate buffer dynamically. If out of memory, use the fixed size stack buffer.
    // This size should be sufficient.
    TInt size = temp.Length() * 2;
    HBufC* buffer = NULL;
    
    if ( size > KMaxTotalDataLength )
        {
        buffer = HBufC::New( size );
        }

    TPtr des = ( buffer ? buffer->Des() : target.Des() );
    TDesC* targetptr = &temp;

    if ( columnText == KNullDesC )
        {
#ifdef RD_LIST_STRETCH
        // If list stretching is used and the device is in landscape orientation
        // there is only one text cell available. Therefore, word wrapping 
        // cannot be done. Instead the first text cell must be omitted and the 
        // possible text moved to the second cell. If both text cells contain 
        // data they are combined and the data is moved to the second cell (i.e. 
        // the first cell is never drawn in landscape if list stretching is 
        // turned on).
        if ( Layout_Meta_Data::IsLandscapeOrientation() &&
             Layout_Meta_Data::IsListStretchingEnabled() &&
             FormattedCellData()->StretchingEnabled() )
            {
            TBool swapCells = ETrue;
            TPtrC itemText;
            
            // check if cell swapping should be done at all
            for ( TInt i = 2; i <= 4; ++i )
                {
                if ( TextUtils::ColumnText( itemText, i, targetptr ) == KErrNotFound )
                    {
                    break;
                    }
                
                if ( itemText != KNullDesC )
                    {
                    swapCells = EFalse;
                    break;
                    }
                }
            
            TextUtils::ColumnText( itemText, 1, targetptr );

            if ( swapCells && itemText.Length() > 0 )
                {
                TPtrC secondaryText;
                TextUtils::ColumnText( secondaryText, 5, targetptr );
            
                // remove text from the first text cell
                AknLAFUtils::ReplaceColumn( des, targetptr, (TDesC16*)&KNullDesC, KColumnListSeparator, 1 );

                // ReplaceColumn does not update descriptor's length :(
                des.Set( buffer ? buffer->Des() : target.Des() ); 
                
                TInt secondaryPos = 0;
                TPtrC temp;
                temp.Set( des );

                // add separators if needed
                for ( TInt i = 0; i < 5; ++i )
                    {
                    TInt position = temp.Locate( KColumnListSeparator );
                    
                    if ( position != KErrNotFound )
                        {
                        if ( position < temp.Length() )
                            {
                            ++position;
                            }
                            
                        secondaryPos += position;
                        }
                    else
                        {
                        des.Append( KColumnListSeparator );
                        secondaryPos = des.Length();
                        }

                    temp.Set( des.Mid( secondaryPos ) );
                    }
                
                des.Insert( secondaryPos, itemText );

                if ( secondaryText != KNullDesC )
                    {
                    _LIT( KEmptySpace, " " );
                    des.Insert( secondaryPos + itemText.Length(), KEmptySpace );
                    }
                    
                targetptr = &des;
                }
            }
        else
            {
            WordWrapListItem( des, *targetptr, 1, 5, aItemIndex );
            // Set again because ReplaceColumn in WordWrapListItem does not update the length to 'des' !
            des.Set( buffer ? buffer->Des() : target.Des() );
            targetptr = &des;
            }
#else
        WordWrapListItem( des, temp, 1, 5, aItemIndex );
        // Set again because ReplaceColumn in WordWrapListItem does not update the length to 'des' !
        des.Set( buffer ? buffer->Des() : target.Des() );
        targetptr = &des;
#endif // RD_LIST_STRETCH
        }

#ifdef RD_UI_TRANSITION_EFFECTS_LIST 
    if ( transApi )
        {
        iGc->CancelClippingRect();
        transApi->StopDrawing();
        }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
                
    if (FormattedCellData()->IsMarqueeOn() && 
            FormattedCellData()->CurrentMarqueeItemIndex() != aItemIndex && 
            aItemIsCurrent)
        {
        FormattedCellData()->ResetMarquee();
        FormattedCellData()->SetCurrentMarqueeItemIndex(aItemIndex);
        }

    SettingsData()->Draw( Properties( aItemIndex ), 
                          *iGc,
                          targetptr,
                          aItemTextRect,
                          aItemIsCurrent,
                          colors );

    delete buffer;
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CSettingsListBoxItemDrawer::CFormattedCellListBoxItemDrawer_Reserved()
    {
    }

//
// Settings listbox
//
EXPORT_C CEikSettingsListBox::CEikSettingsListBox()
    {
    _AKNTRACE_FUNC_ENTER;
    AKNTASHOOK_ADD( this, "CEikSettingsListBox" );
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C CSettingsListBoxItemDrawer* CEikSettingsListBox::ItemDrawer() const
    {
    return(CSettingsListBoxItemDrawer*)iItemDrawer;
    }

EXPORT_C void CEikSettingsListBox::CreateItemDrawerL()
    {
    _AKNTRACE_FUNC_ENTER;
    CSettingsListBoxData* cellData=CSettingsListBoxData::NewL();
    CleanupStack::PushL( cellData );

    if ( FeatureManager::FeatureSupported( KFeatureIdSettingsProtection ) )
        {
        iItemDrawer = SettingsProtListBoxItemDrawerFactory::
            CreateSettingsProtListBoxItemDrawerL(
                Model(),
                CEikonEnv::Static()->NormalFont(),
                cellData,
                this );
        }
    else
        {
        iItemDrawer = new ( ELeave ) CSettingsListBoxItemDrawer(
            Model(), CEikonEnv::Static()->NormalFont(), cellData );
        }

    CleanupStack::Pop();
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C CListBoxView* CEikSettingsListBox::MakeViewClassInstanceL()
    {
    return new ( ELeave )CSettingsListBoxView;
    }

#define ITEM_EXISTS_ONCE(x) (((x) > -1) && ((x) < iModel->NumberOfItems()))

EXPORT_C void CEikSettingsListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    {
    _AKNTRACE_FUNC_ENTER;
    CEikFormattedCellListBox::HandlePointerEventL(aPointerEvent);
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void* CEikSettingsListBox::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

EXPORT_C void CEikSettingsListBox::CEikListBox_Reserved() 
    {
    }

EXPORT_C void CSettingsListBoxView::Draw(const TRect* clipRect) const
    {
    _AKNTRACE_FUNC_ENTER;
    CFormattedCellListBoxView::Draw( clipRect );
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CSettingsListBoxView::DrawItem( TInt aItemIndex ) const
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE("DrawItem: aItemIndex=%d",aItemIndex);
    CListBoxView::DrawItem( aItemIndex );
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C TAny* CSettingsListBoxView::Reserved_1()
    {
    return NULL;
    }

// End of File
