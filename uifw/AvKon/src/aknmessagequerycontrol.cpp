/*
* Copyright (c) 2002 - 2006 Nokia Corporation and/or its subsidiary(-ies).
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
#include <barsread.h>
#include <eikenv.h>
#include <AknPanic.h>
#include <avkon.hrh>
#include <avkon.rsg>
#include <aknmessagequerycontrol.h>
#include <aknmessagequerydialog.h>

#include <eiksbfrm.h>
#include <eikscrlb.h>

#include <eikappui.h>

#include <frmlaydt.h>
#include "aknconsts.h"

#include <AknsDrawUtils.h>

#include <applayout.cdl.h>
#include "aknappui.h"

#include <eikrted.h>
#include <txtrich.h> 
#include <txtfrmat.h>

#include <layoutmetadata.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>

#include <eikdialg.h>
#include <eikdialogext.h>

#include <eikedwob.h>

#include <AknTasHook.h> // for testability hooks
class CAknMessageQueryControlExtension: public CBase, public MEikEdwinObserver
    {
public:
    CAknMessageQueryControlExtension( CAknMessageQueryControl* aParent ): iParent( aParent ) {}
        
    /**
    * From MEikEdwinObserver. Handles edwin events.
    * On the scroll event, any selected link is dehighlighted.
    */
    void HandleEdwinEventL( CEikEdwin* /*aEdwin*/, TEdwinEvent aEventType )
        {
    	if( aEventType == MEikEdwinObserver::EEventScroll )
    	    {
    		iParent->DehighlightLink();
    		}
        }
        
    ~CAknMessageQueryControlExtension()
        {    
        if( iDestroyedPtr )
            {
            // Mark the object as destroyed.
            *iDestroyedPtr = ETrue;
            iDestroyedPtr = NULL;
            }
        }
        
    public:
    
    CAknMessageQueryControl* iParent;
    /**
    * @c iDestroyedPtr is used for the object destruction check.
    * If it has non-null value, the destruction check is turned on, and
    * the value points to a local boolean variable that keeps the destroyed state.
    */
    TBool* iDestroyedPtr;
    };

CAknMessageQueryControl::CAknMessageQueryControl() :
    iTopLine( 0 ), iLinksCount( 0 ), iVisibleLinksCount( 0 ),
    iFirstVisibleLink( -1 ), iCurPos( 0 ), iFullMessage( NULL )
    {
    iLinesPerPage = AknLayoutScalable_Avkon::popup_info_list_pane_t1_ParamLimits().LastRow() + 1;
    AKNTASHOOK_ADD( this, "CAknMessageQueryControl" );
    }

CAknMessageQueryControl::~CAknMessageQueryControl()
    {
    AKNTASHOOK_REMOVE();
    AknsUtils::DeregisterControlPosition( iEdwin );
    delete iEdwin;
    if ( !AknLayoutUtils::PenEnabled() )
        {
        delete iSBFrame;
        } 
    iLinkTextLocationArray.Close();
    iLinkTextArray.Close();
    delete iFullMessage;
    delete iExtension;
    }

EXPORT_C void CAknMessageQueryControl::ConstructFromResourceL( TResourceReader& aReader )
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
    
    TPtrC messageLabel = aReader.ReadTPtrC();
    SetMessageTextL( &messageLabel );
    }

EXPORT_C void CAknMessageQueryControl::SetMessageTextL( TDesC* aMessage )
    {
    CreateEditorL();
    iEdwin->TextLayout()->SetAmountToFormat( CTextLayout::EFFormatAllText );
    if ( aMessage->Length() > iEdwin->UpperFullFormattingLength() )
        iEdwin->SetUpperFullFormattingLength( aMessage->Length() ); 
    iEdwin->SetTextL( aMessage );
    LayoutEditorL(); 
    
    HBufC* msgBuf = aMessage->AllocLC();
    TPtr message( msgBuf->Des() );
    if( iListQLayout )
        {
        TruncateTextForListQLayout( message );
        iEdwin->SetTextL( &message );
        LayoutEditorL(); 
        }

    if ( message.Locate('\n') != KErrNotFound )
        {
        iEdwin->SetCursorPosL( 1, EFalse );
        SEdwinFindModel findModel;
        _LIT( KNChar,"\n" ); 
        _LIT( KFChar,"\f" );
        TBuf<1> text( KNChar );
        TBuf<1> replaceText( KFChar );
        findModel.iFlags = 0;
        findModel.iText = text;
        findModel.iReplaceText = replaceText;
        findModel.iReplaceOption = EReplaceAll;
        iEdwin->ReplaceAllL( &findModel );
        }
    CleanupStack::PopAndDestroy( msgBuf );  // After all usages of message        
             
    iNumberOfLines = iEdwin->TextLayout()->NumFormattedLines();
    iTopLine = 0;
    UpdateScrollIndicatorL();    
    }           
    
void CAknMessageQueryControl::CreateEditorL()
    {
    delete iEdwin;
    iEdwin = NULL;
    if ( !AknLayoutUtils::PenEnabled() )
        {
        delete iSBFrame;
        iSBFrame = NULL;
        } 
    
    iEdwin = new ( ELeave ) CEikRichTextEditor( TGulBorder::ENone );
    iEdwin->SetContainerWindowL( *this );
    AknEditUtils::ConstructEditingL( iEdwin, R_AVKON_MESSAGE_QUERY_EDITOR );
    
    if ( !iExtension )
        {
        iExtension = new (ELeave) CAknMessageQueryControlExtension( this );
        }
    iEdwin->SetEdwinObserver( iExtension );
    iEdwin->SetAvkonWrap( ETrue );                                  
    iEdwin->SetFocus( EFalse );
    iEdwin->SetNonFocusing();
    }    
    
void CAknMessageQueryControl::LayoutEditorL()
    {
    TInt lines = 1;

    RArray<TAknTextComponentLayout> textComponentLayoutArray;
    for ( TInt rowIndex = 0; rowIndex < lines; rowIndex++)
        {
        TRAPD(error, textComponentLayoutArray.AppendL(AknLayoutScalable_Avkon::popup_info_list_pane_t1(rowIndex)));
        if (error != KErrNone)
            {
            textComponentLayoutArray.Close();
            User::Leave(error);
            }
        }

    TRect parentRect = LayoutRect();
    TAknLayoutRect listScrollPopupInfoPane;
    listScrollPopupInfoPane.LayoutRect(parentRect, AknLayoutScalable_Avkon::listscroll_popup_info_pane());
    TAknLayoutRect listPopupInfoPane;
    listPopupInfoPane.LayoutRect(listScrollPopupInfoPane.Rect(), AknLayoutScalable_Avkon::list_popup_info_pane( 0 ));  // Variety with scroll bar
    
    /** The edwin rect is set totally from layout list_popup_info_pane. But
      * AknLayoutUtils::LayoutEdwin() is still used for setting its text color and font. 
     **/ 
    AknLayoutUtils::LayoutEdwin( iEdwin, listPopupInfoPane.Rect(),
        TAknTextComponentLayout::Multiline(textComponentLayoutArray), EAknsCIQsnTextColorsCG19 );
    iEdwin->SetSuppressFormatting(ETrue);
    iEdwin->SetRect( listPopupInfoPane.Rect() );
    iEdwin->SetSuppressFormatting(EFalse);
    textComponentLayoutArray.Close();
    }    

TKeyResponse CAknMessageQueryControl::OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode /*aModifiers*/ )
    {
    TInt key( aKeyEvent.iCode );
    if( !(key == EKeyDownArrow || key == EKeyUpArrow) )
        return EKeyWasConsumed;
    TBool moveDown = key == EKeyDownArrow; // Moving down?
        
    /* 4 transitions are possible:
    
    Text   -> *Link*
    *Link* -> *Link*
    *Link* -> Text
    Text   -> >>Scroll page>>
    
    */
    
    // If the editor was scrolled with pen, synchronize the query's and editor's states
    TInt editorTopLine = iEdwin->TextLayout()->FirstLineInBand();
    if( editorTopLine != iTopLine )
        {
        if( LinkHighLighted() ) // Standing on a link?
            {
            // Synchronize to the query's position
            iEdwin->TextView()->SetViewLineAtTopL( iTopLine + 1 );    // Uses 1-based line numbers
            }
        else
            {
            // Synchronize to the editor's position
            iTopLine = editorTopLine;
            UpdatePageInfo();
            }
        }
        
    SetHighlightOnL( EFalse );  // Dehighlight the old link    
        
    // Move to the following position    
    iCurPos += moveDown? 1 : -1;
    if( iCurPos < 1 || iPositionsCount -1  <= iCurPos ) // Beyond the allowed range
        {
        if( CanScrollPage( moveDown ) )
            {
            iTopLine += moveDown? iLinesPerPage - 1 : 1 - iLinesPerPage;
            if( iTopLine >= iNumberOfLines - iLinesPerPage)
                {
                iTopLine = iNumberOfLines - iLinesPerPage;
                }
            if( iTopLine < 0)
                {
                iTopLine = 0;
                }
            iEdwin->MoveDisplayL( moveDown? TCursorPosition::EFPageDown : TCursorPosition::EFPageUp );
            int lastPageLink = -1;
            if( iFirstVisibleLink > -1 )
            	lastPageLink = moveDown?
            	    (iFirstVisibleLink + iVisibleLinksCount - 1): iFirstVisibleLink;
            UpdatePageInfo();
            if( lastPageLink > -1 && iFirstVisibleLink > -1 )
                {
                if( moveDown )
                    {
                	iCurPos = 1;
                	while( lastPageLink-- >= iFirstVisibleLink )
                	    {
                		iCurPos++;
                	    }
                    }
                
                else
                    {
                    iCurPos = iPositionsCount - 2;
                    while( lastPageLink++ <= iFirstVisibleLink + iVisibleLinksCount - 1 )
                        {
                    	iCurPos--;
                        }	
                    }
            	
                }
            else
                {
            	iCurPos = moveDown? 1 : iPositionsCount - 2;   // Proceed to top or bottom of the following page
                }
            }
        else
            {
            iCurPos = moveDown? iPositionsCount - 1 : 0;    // Return to bottom or top of the current page
            }
        }
    
    SetHighlightOnL( ETrue );   // Highlight the new link
    
        
    UpdateScrollIndicatorL();
    return( EKeyWasConsumed );
    }

void CAknMessageQueryControl::SizeChanged()
    {
    TRAP_IGNORE( DoSizeChangedL() );
    }


TSize CAknMessageQueryControl::MinimumSize()
    {
    const TRect rect( LayoutRect() );
    TAknLayoutRect listScrollPopupInfoPane;
    listScrollPopupInfoPane.LayoutRect(rect, AknLayoutScalable_Avkon::listscroll_popup_info_pane());

    if ( AknLayoutUtils::PenEnabled() )
        {
        return TSize( rect.Width(), listScrollPopupInfoPane.Rect().Height() );
        }
    else
        {
        return listScrollPopupInfoPane.Rect().Size();
        }
    } 


TRect CAknMessageQueryControl::LayoutRect() const
    {
    TInt lines = iNumberOfLines > iLinesPerPage ? iLinesPerPage : iNumberOfLines;
    
    lines--;
    if ( lines < 0 ) 
        {
        lines = 0;    
        }

    TInt variety = 0;
    AknLayoutUtils::TAknCbaLocation cbaLocation = AknLayoutUtils::CbaLocation();
    if (cbaLocation == AknLayoutUtils::EAknCbaLocationRight)
        { // Variety numbers for right CBA are 6-11
        variety = lines + 6;
        }
    else if (cbaLocation == AknLayoutUtils::EAknCbaLocationLeft)
        { // Variety numbers for left CBA are 12-17
        variety = lines + 12;
        }
    else // bottom
        {
        variety = lines;
        }

    TRect appRect = iAvkonAppUi->ApplicationRect();
    TAknLayoutRect applicationWindow;
    applicationWindow.LayoutRect(appRect, AknLayoutScalable_Avkon::application_window(0));    
    TRect mainPane;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EPopupParent, mainPane );
    
    TAknLayoutRect layout;
    layout.LayoutRect( mainPane, AknLayoutScalable_Avkon::popup_query_sat_info_window( variety ) );
    TRect rect( layout.Rect() );

    return TRect( TPoint(0, 0), rect.Size() );
    }

// Get component controls into a table
const TInt KMaxMessageQueryControls = 2;
static TInt ComponentControls(CCoeControl* aEditor,
    CEikScrollBarFrame* aScrollBarFrame,
    CCoeControl* aControls[KMaxMessageQueryControls])
    {
    TInt i = 0;
    if (aEditor)
        {
        aControls[i++] = aEditor;
        }
    // Non-window owning acroll bar
    if (aScrollBarFrame && aScrollBarFrame->TypeOfVScrollBar() == CEikScrollBarFrame::EDoubleSpan)
        {
        aControls[i++] = aScrollBarFrame->GetScrollBarHandle(
            CEikScrollBar::EVertical);
        }
    return i;
    }

TInt CAknMessageQueryControl::CountComponentControls() const
    {
     CCoeControl* unused[KMaxMessageQueryControls];
     return ComponentControls(iEdwin, iSBFrame, unused);
    }


CCoeControl* CAknMessageQueryControl::ComponentControl( TInt aIndex ) const
    {
     CCoeControl* controls[KMaxMessageQueryControls];
     TInt cnt = ComponentControls(iEdwin, iSBFrame, controls);
     if (aIndex < cnt)
        {
        return controls[aIndex];
        }
    else
        {
        return NULL;
        }
    }         

// This method is needed to set correct initial value to scroll indicator.
void CAknMessageQueryControl::ActivateL()
    {
    CCoeControl::ActivateL();
    UpdateScrollIndicatorL();
    }

void CAknMessageQueryControl::UpdateScrollIndicatorL()
    {   
    if ( iNumberOfLines <= iLinesPerPage )
        {
        return;
        }
    if ( !iSBFrame )
        {
        if ( AknLayoutUtils::PenEnabled())
            {   
            // Edwin will make scrollbar and also observe it
            iSBFrame= iEdwin->CreateScrollBarFrameL();
            }
        else
            {
            iSBFrame=new( ELeave ) CEikScrollBarFrame( this, NULL, ETrue );
            }           

        // Check which type of scrollbar is to be shown
        CAknAppUiBase* appUi = iAvkonAppUi;
        if ( AknLayoutUtils::DefaultScrollBarType( appUi ) == CEikScrollBarFrame::EDoubleSpan )
            {
            iSBFrame->CreateDoubleSpanScrollBarsL(EFalse, EFalse, ETrue, EFalse ); // non-window owning scrollbar
            iSBFrame->SetTypeOfVScrollBar( CEikScrollBarFrame::EDoubleSpan );
            if( CAknEnv::Static()->TransparencyEnabled() )
                {
                iSBFrame->DrawBackground( EFalse, EFalse );
                }
            }
        else
            {
            // For EArrowHead type scrollbar
            iSBFrame->SetTypeOfVScrollBar( CEikScrollBarFrame::EArrowHead );
            }
        iSBFrame->SetScrollBarVisibilityL( CEikScrollBarFrame::EOff,CEikScrollBarFrame::EAuto );
        }
    if ( !iSBFrame )
        {
        return;
        }
        
    if ( !AknLayoutUtils::PenEnabled() )
        {
        TEikScrollBarModel hSbarModel;
        TEikScrollBarModel vSbarModel;
        vSbarModel.iThumbPosition = iTopLine;
        vSbarModel.iScrollSpan = iNumberOfLines;
        vSbarModel.iThumbSpan = iLinesPerPage;
        
        TEikScrollBarFrameLayout layout;
        TRect rect( Rect() );
        
        if ( iSBFrame->TypeOfVScrollBar() == CEikScrollBarFrame::EDoubleSpan )
            {
            // For EDoubleSpan type scrollbar
            TAknDoubleSpanScrollBarModel hDsSbarModel( hSbarModel );
            TAknDoubleSpanScrollBarModel vDsSbarModel( vSbarModel );
            layout.iTilingMode = TEikScrollBarFrameLayout::EInclusiveRectConstant;
                 
            TAknLayoutRect listScrollPopupInfoPane;
            listScrollPopupInfoPane.LayoutRect( LayoutRect(), AknLayoutScalable_Avkon::listscroll_popup_info_pane() );
            TRect listScrollPopupInfoPaneRect( listScrollPopupInfoPane.Rect() );
            CAknPopupHeadingPane* heading = NULL;
            if( iListQLayout )
            	{
            	CAknListQueryDialog* dlg;
            	MopGetObject( dlg );
            	if( dlg )
            		{
            		heading = dlg->QueryHeading();
            		}            	
            	}
            else
            	{
            	CEikDialog* dlg;
                MopGetObject( dlg );
                if( dlg )
                	{
                	heading = (CAknPopupHeadingPane*)dlg->ControlOrNull(EAknMessageQueryHeaderId); 
                	}                
            	}
            
            if( heading && heading->PromptText() == KNullDesC )
                {
                TAknLayoutRect headingPaneLayout;
                headingPaneLayout.LayoutRect( LayoutRect(), AknLayoutScalable_Avkon::heading_pane_cp5() );
                listScrollPopupInfoPaneRect.Move( 0, -1 * headingPaneLayout.Rect().Height() );
                }
            AknLayoutUtils::LayoutVerticalScrollBar( iSBFrame, listScrollPopupInfoPaneRect, AknLayoutScalable_Avkon::scroll_pane_cp7().LayoutLine() );
        
            TRect inclusiveRect( Rect() );
            TRect clientRect( Rect() );
            
            iSBFrame->TileL( &hDsSbarModel,&vDsSbarModel,clientRect,inclusiveRect,layout );        
            iSBFrame->SetVFocusPosToThumbPos( vDsSbarModel.FocusPosition() );
            }
        else
            {
            // For EArrowHead type scrollbar
            iSBFrame->TileL( &hSbarModel,&vSbarModel,rect,rect,layout );        
            iSBFrame->SetVFocusPosToThumbPos( vSbarModel.iThumbPosition );
            }
        }
    else
        {
        iEdwin->UpdateScrollBarsL();    
        }
    }

EXPORT_C void CAknMessageQueryControl::Draw( const TRect& /*aRect*/ ) const
    {
    if ( iListQLayout )
    	{
        return;
        }

    CWindowGc& gc=SystemGc(); 
    TRect messageQueryControlRect( Rect() );
    TRect popupRect = TRect(LayoutRect());

    TRect backgroundRect = TRect(messageQueryControlRect.iTl, popupRect.iBr);    
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );

    if( CAknEnv::Static()->TransparencyEnabled() )
        {
        TRegionFix<4> clipReg;
        clipReg.AddRect(backgroundRect);
        if (iEdwin)
            {
            clipReg.SubRect(iEdwin->Rect());
            }
        gc.SetClippingRegion(clipReg);
        AknsDrawUtils::Background( skin, cc, this, gc, backgroundRect, KAknsDrawParamNoClearUnderImage );
        gc.CancelClippingRegion();
        }
    else
        {
        AknsDrawUtils::Background( skin, cc, this, gc, backgroundRect );
        }
    }

TInt CAknMessageQueryControl::CurrentLink() const
    {
    if( 0 < iCurPos && iCurPos < iPositionsCount - 1 ) // The current position is on a link
        {
        return iCurPos - 1 + iFirstVisibleLink;
        }
    else    // No link is active
        {
        return -1;
        }
    }

EXPORT_C TBool CAknMessageQueryControl::LinkHighLighted() const
    {
    return CurrentLink() > -1;
    }

void CAknMessageQueryControl::SetHighlightOnL( TBool aOn )
    {
    if( !LinkHighLighted() )
        return;
    iCharFormatMask.ClearAll();
    if ( iEdwin && iEdwin->TextLength() > 0 &&
        iLinkTextArray.Count() > 0 && iLinkTextArray[CurrentLink()]->Length() > 0 )
        {
        iCharFormatMask.SetAttrib( EAttFontHighlightStyle );
        iCharFormatMask.SetAttrib( EAttFontHighlightColor );
        if ( aOn )
            {
            iCharFormat.iFontPresentation.iHighlightStyle = TFontPresentation::EFontHighlightNormal;
            
            TRgb color = AKN_LAF_COLOR( 244 );
            AknsUtils::GetCachedColor( AknsUtils::SkinInstance(), color, KAknsIIDQsnHighlightColors, EAknsCIQsnHighlightColorsCG1 ); 
            iCharFormat.iFontPresentation.iHighlightColor = color;
            
            color = AKN_LAF_COLOR( 210 );
            AknsUtils::GetCachedColor( AknsUtils::SkinInstance(), color, KAknsIIDQsnHighlightColors, EAknsCIQsnHighlightColorsCG3 );                    
	        iCharFormat.iFontPresentation.iTextColor = color;           
            }
        else
            {
            iCharFormat.iFontPresentation.iHighlightStyle = TFontPresentation::EFontHighlightNone;
            }

        if ( iLinksCount > 0 )
            {
            iEdwin->RichText()->ApplyCharFormatL( iCharFormat, iCharFormatMask, ( iLinkTextLocationArray )[CurrentLink()], ( iLinkTextArray )[CurrentLink()]->Length() );
            }

        iEdwin->DrawNow();
        }
    }
    
TBool CAknMessageQueryControl::CanScrollPage( TBool aMoveDown )
    {
    if( iNumberOfLines <= iLinesPerPage )    // Only one page
        return EFalse;
    if( aMoveDown )
        return iTopLine < iNumberOfLines - iLinesPerPage;
    else
        return iTopLine > 0;
    }    

TBool CAknMessageQueryControl::IsLinkVisible( TInt aIndex ) const
    {
    if ( aIndex >= iLinksCount )
        {
        return EFalse;
        }
    TInt linkLine( iEdwin->TextLayout()->GetLineNumber( iLinkTextLocationArray[aIndex] ) );
    if ( iTopLine <= linkLine && linkLine < iTopLine + iLinesPerPage )
        {
        return ETrue;
        }
    else
        {
        return EFalse;
        }
    }

void CAknMessageQueryControl::UpdatePageInfo()
    {
    TBool firstFound( EFalse );
    iVisibleLinksCount = 0;
    iFirstVisibleLink = -1;
    
    // Update visible links
    for( TInt count = 0; count < iLinksCount; count++ )
        {
        if( IsLinkVisible( count ) )
            {
            iVisibleLinksCount++;
            if( !firstFound )
                {
                iFirstVisibleLink = count;
                firstFound = ETrue;
                }
            }
        else if( firstFound )   // All visible links have been already found
            {
            break;
            }
        }
    
    // Update number of cursor positions
    if( iVisibleLinksCount > 0 )
        {
        iPositionsCount = iVisibleLinksCount + 2;
        }
    else
        {
        iPositionsCount = 1;
        }
    }
    
void CAknMessageQueryControl::SetListQLayout(TBool aListQLayout)
    {
    iListQLayout = aListQLayout;
    }

    
void CAknMessageQueryControl::SetMessageTextWithFormattingL( TDesC* aMessage, RArray<TDesC*>* aFormatTextArray, RArray<TInt>* aFormatTextLocationArray, RArray<TMsgQueryTag>* aFormatTypeArray )
    {
    if( iListQLayout )
        User::Leave( KErrNotSupported );  // Links in the list query layout are not supported
    CreateEditorL();
    iEdwin->TextLayout()->SetAmountToFormat( CTextLayout::EFFormatAllText );
    if ( aMessage->Length() > iEdwin->UpperFullFormattingLength() )
        iEdwin->SetUpperFullFormattingLength( aMessage->Length() ); 
    iEdwin->RichText()->DeleteL( 0, iEdwin->RichText()->DocumentLength() );
    iEdwin->RichText()->InsertL ( 0, *aMessage );
                
    // Initialize link data
    for ( TInt count = 0; count < aFormatTypeArray->Count(); count++ )
        {
        if ( (*aFormatTypeArray)[count] == EMsgQueryLink )
            {
            // Add the link location and text keeping the arrays sorted on the location
            TInt location = (*aFormatTextLocationArray)[count];
            iLinkTextLocationArray.InsertInOrder( location );
            TInt index = iLinkTextLocationArray.FindInOrder( location );
            iLinkTextArray.Insert( (*aFormatTextArray)[count], index );
            }
        }
    iLinksCount = iLinkTextLocationArray.Count();

    iCharFormatMask.ClearAll();    
    
    // Set link font
    if (aMessage->Length() > 0)
        {
        // Set font color and underlining
       	for (TInt count = 0; count < iLinksCount; count++)
	        {    
	        if ((iLinkTextLocationArray )[count] != KErrNotFound)
	            {
	            iCharFormatMask.SetAttrib( EAttFontUnderline );
	            iCharFormatMask.SetAttrib( EAttColor );
	            iCharFormat.iFontPresentation.iUnderline = EUnderlineOn;
	            
	            TRgb color = AKN_LAF_COLOR( 210 );
                AknsUtils::GetCachedColor( AknsUtils::SkinInstance(), color, KAknsIIDQsnHighlightColors, EAknsCIQsnHighlightColorsCG3 );
                    
	            iCharFormat.iFontPresentation.iTextColor = color;
	            
	            iEdwin->RichText()->ApplyCharFormatL(iCharFormat, iCharFormatMask, (iLinkTextLocationArray)[count], ((iLinkTextArray )[count])->Length());
	            }            
	        }     
        
        iCharFormatMask.ClearAll();
        
        // Set font boldness
        for ( TInt count = 0; count < aFormatTextLocationArray->Count(); count++ )
	        {    
	        if ((*aFormatTextLocationArray)[count] != KErrNotFound && (*aFormatTypeArray)[count] == EMsgQueryBold)
	            {
	            iCharFormatMask.SetAttrib( EAttFontStrokeWeight );
	            iCharFormat.iFontSpec.iFontStyle.SetStrokeWeight(EStrokeWeightBold);
	            iEdwin->RichText()->ApplyCharFormatL( iCharFormat, iCharFormatMask, (*aFormatTextLocationArray)[count], (*aFormatTextArray )[count]->Length() );
	            }
	        }
	    }
        
    LayoutEditorL();
    
    if ( aMessage->Locate( '\n' ) != KErrNotFound )
        {
        iEdwin->SetCursorPosL( 1, EFalse );
        SEdwinFindModel findModel;
        _LIT( KNChar,"\n" ); 
        _LIT( KFChar,"\f" );
        TBuf<1> text( KNChar );
        TBuf<1> replaceText( KFChar );
        findModel.iFlags = 0;
        findModel.iText = text;
        findModel.iReplaceText = replaceText;
        findModel.iReplaceOption = EReplaceAll;
        iEdwin->ReplaceAllL( &findModel );
        }
        
    iNumberOfLines = iEdwin->TextLayout()->NumFormattedLines();
    iTopLine = 0;
    iCurPos = 0;   // Page top, no link selected
    
    UpdatePageInfo();
    UpdateScrollIndicatorL();
    }


/**
 * CAknMessageQueryControl::HandlePointerEventL()
 *
 * Transfers pointerevent to editor control and updates it's scroll bar. 
 * Checks for the object destruction after the pointer event handling.
 */
void CAknMessageQueryControl::HandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    TBool highlightBefore = LinkHighLighted();
    /**
    * The local @c destroyed variable keeps track of the object destroyed state.
    */
    TBool destroyed = EFalse;
    if (AknLayoutUtils::PenEnabled() )
        {
        iExtension->iDestroyedPtr = &destroyed;
        // Call default implementation of HandlePointerEventL to transfer event to correct control.
        CAknControl::HandlePointerEventL( aPointerEvent );
        if ( !destroyed )
            {
            iExtension->iDestroyedPtr = NULL;
            iEdwin->UpdateScrollBarsL();
            }
        else
            {
            return;
            }
        }
    TBool highlightAfter = LinkHighLighted();
    if( aPointerEvent.iType == TPointerEvent::EButton1Down && 
        highlightBefore == highlightAfter && highlightAfter )
        {
        DehighlightLink();
        }
    }

//----------------------------------------------------------------------------------
// CAknMessageQueryControl::LinkTapped()
// Checks if a link is tapped and hightlights it. 
//----------------------------------------------------------------------------------
//

TBool CAknMessageQueryControl::LinkTappedL( TInt aPos )
    {
    if ( iLinksCount <= 0 )
        {
        return EFalse; 
        }
    /** There can be 3 possible results.
    1. The link is found and it's a new link.
    2. The link is found, but it's the current link.
    3. The link was not found at the tapped position. 
    */
    TInt oldLink = CurrentLink();
    TInt linkPos = 0; 
    for ( TInt count = 0; count < iLinksCount; count++ )
        {
        linkPos = iLinkTextLocationArray[count];
        if ( linkPos <= aPos && aPos < linkPos + iLinkTextArray[count]->Length() ) // The tapped link found
            {
            if ( oldLink != count ) // A new link
                {
                TInt editorTopLine = iEdwin->TextLayout()->FirstLineInBand();
                if( iTopLine != editorTopLine ) // User scrolled with the pen
                    {
                    // Synchronize query's top line with editor's one
                    iTopLine = editorTopLine;
                    UpdatePageInfo();
                    }
                SetCurPosL( count - iFirstVisibleLink + 1 ); 
                }
            return ETrue; 
            }
        }
    DehighlightLink();
    return EFalse; 
    }


TBool CAknMessageQueryControl::SetCurPosL( TInt aCurPos )
    {
    if( aCurPos < 0 || aCurPos >= iPositionsCount )
        return EFalse;
    SetHighlightOnL( EFalse );  // Dehighlight the old link
    iCurPos = aCurPos;
    SetHighlightOnL( ETrue );     // Highlight the new link
    return ETrue;
    }
    
void CAknMessageQueryControl::DehighlightLink()
    {
    if ( !LinkHighLighted() )
        {
        return; 
        }
    TRAP_IGNORE( SetHighlightOnL( EFalse ) );  // Dehighlight the old link
    iCurPos = 0;    // Move the cursor to the top of the page
    // Update the softkey labels (set them to "Ok - Cancel")
    CAknMessageQueryDialog* dlg;
    MopGetObject( dlg );
    if ( dlg )
        {
        dlg->UpdateSoftkeyLabels();
        }
    }

TBool CAknMessageQueryControl::ScrollBarGrabbing()
    {
    CCoeControl* grabbingComponent = GrabbingComponent();

    TBool grabbing = EFalse;
    if (grabbingComponent)
        {
        grabbing = iSBFrame && iSBFrame->GetScrollBarHandle(
            CEikScrollBar::EVertical) == grabbingComponent;
        }
    return grabbing;
    }

void CAknMessageQueryControl::TruncateTextForListQLayout( TDes& aMessage )
    {
    if( !iListQLayout )
        return;

    delete iFullMessage;
    iFullMessage = NULL;
    iFullMessage = aMessage.AllocL();
    TInt maxLines = 3;  // Should be AknLayoutScalable_Apps::loc_type_pane_t1_ParamLimits().LastRow();
    TInt lastLineBegin = iEdwin->TextLayout()->FirstCharOnLine( maxLines );       
    TInt lastLineEnd = iEdwin->TextLayout()->FirstCharOnLine( maxLines + 1 );       
    if( lastLineEnd < aMessage.Length() )
        {
        const CFont* font = AknLayoutUtils::FontFromId(
            AknLayoutScalable_Avkon::popup_info_list_pane_t1( 0 ).Font() );
        TInt ellipsisPosInLastLine = font->TextCount( aMessage.Mid( lastLineBegin, lastLineEnd - lastLineBegin ),
            iEdwin->LayoutWidth() - font->CharWidthInPixels( KEllipsis ) ) - 1;
        aMessage = aMessage.LeftTPtr( lastLineBegin + ellipsisPosInLastLine );
        aMessage.Append( KEllipsis );
        }
    }

void CAknMessageQueryControl::DoSizeChangedL()
    {
    if ( iListQLayout )
        {
        iLinesPerPage = 3;  // Should be AknLayoutScalable_Apps::loc_type_pane_t1_ParamLimits().LastRow();
        HBufC* msgBuf = iFullMessage->AllocLC() ;
        TPtr message( msgBuf->Des() );
        iEdwin->SetTextL( &message );
        LayoutEditorL(); 
        TruncateTextForListQLayout( message );
        iEdwin->SetTextL( &message );
        CleanupStack::PopAndDestroy( msgBuf );  // After all usages of message        
        iNumberOfLines = iEdwin->TextLayout()->NumFormattedLines();
        }
    else
        {
        iLinesPerPage = AknLayoutScalable_Avkon::popup_info_list_pane_t1_ParamLimits().LastRow() + 1;    
        }    
    
    TInt lines = iNumberOfLines > iLinesPerPage ? iLinesPerPage : iNumberOfLines;
    if (lines <= 0)
        {
        return;
        }

    RArray<TAknTextComponentLayout> textComponentLayoutArray;
    for ( TInt rowIndex = 0; rowIndex < lines; rowIndex++)
        {
        TRAPD(error, textComponentLayoutArray.AppendL(AknLayoutScalable_Avkon::popup_info_list_pane_t1(rowIndex)));
        if (error != KErrNone)
            {
            if (rowIndex == 0)
                {
                // Give up! textComponentLayoutArray does not contain any items.
                textComponentLayoutArray.Close();
                return; // Layout will fail...
                }
            }
        }

    TAknLayoutRect listScrollPopupInfoPane;
    listScrollPopupInfoPane.LayoutRect( LayoutRect(), AknLayoutScalable_Avkon::listscroll_popup_info_pane() );
    TRect listScrollPopupInfoPaneRect( listScrollPopupInfoPane.Rect() );
    CAknPopupHeadingPane* heading = NULL;
    if( iListQLayout )
    	{
    	CAknListQueryDialog* dlg;
    	MopGetObject( dlg );
    	if( dlg )
    		{
    		heading = dlg->QueryHeading();
    		}    	
    	}
    else
    	{
    	CEikDialog* dlg;
        MopGetObject( dlg );
        if( dlg )
        	{
        	heading = (CAknPopupHeadingPane*)dlg->ControlOrNull(EAknMessageQueryHeaderId); 
        	}        
    	}
    if( heading && heading->PromptText() == KNullDesC )
        {
        TAknLayoutRect headingPaneLayout;
        headingPaneLayout.LayoutRect( LayoutRect(), AknLayoutScalable_Avkon::heading_pane_cp5() );
        listScrollPopupInfoPaneRect.Move( 0, -1 * headingPaneLayout.Rect().Height() );
        }
    TAknLayoutRect listPopupInfoPane;    
    listPopupInfoPane.LayoutRect( listScrollPopupInfoPaneRect, AknLayoutScalable_Avkon::list_popup_info_pane( 0 ) );  // Variety with scroll bar    
    
    
    /** The edwin rect is set totally from layout list_popup_info_pane. But
      * AknLayoutUtils::LayoutEdwin() is still used for setting its text color and font. 
     **/ 
    TAknMultiLineTextLayout multilineLayout = TAknTextComponentLayout::Multiline(textComponentLayoutArray);
    AknLayoutUtils::LayoutEdwin( iEdwin, listPopupInfoPane.Rect(),
        multilineLayout, EAknsCIQsnTextColorsCG19 );
    //iEdwin->SetRect( listPopupInfoPane.Rect() );
    textComponentLayoutArray.Close();
    
    iEdwin->SetBorder( TGulBorder::ENone );
    iEdwin->SetFocus( EFalse );
    AknsUtils::RegisterControlPosition( iEdwin );
    
    iNumberOfLines = iEdwin->TextLayout()->NumFormattedLines();
    
    UpdateScrollIndicatorL();
    }
//  End of File 
