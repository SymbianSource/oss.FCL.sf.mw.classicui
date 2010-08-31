/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Avkon keypad 
*
*/


#include <aknlayoutscalable_apps.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <layoutmetadata.cdl.h>
#include <aknbutton.h>
#include <AknsDrawUtils.h>
#include <AknBidiTextUtils.h>
#include <AknsFrameBackgroundControlContext.h>
#include <aknappui.h>
#include "aknkeypad.h"

#include <AknTasHook.h> // for testability hooks
#include <e32property.h>
#include <PtiDefs.h>                //keys
#include <featmgr.h>                //FeatureManager
#include <AvkonInternalCRKeys.h>


CAknKeypad* CAknKeypad::NewL( CCoeControl& aParent, TInt aQueryType )
    {
    CAknKeypad* self = new ( ELeave ) CAknKeypad;
    CleanupStack::PushL( self );
    self->ConstructL( aParent, aQueryType );
    CleanupStack::Pop(); // self
    AKNTASHOOK_ADDL( self, "CAknKeypad" );
    return self;
    }

CAknKeypad::~CAknKeypad()
    {
    AKNTASHOOK_REMOVE();
    }

void CAknKeypad::SizeChanged()
    {
    TBool landscape = Layout_Meta_Data::IsLandscapeOrientation();
         
    TAknLayoutScalableParameterLimits limits = AknLayoutScalable_Apps::cell_vitu2_itu_pane_ParamLimits( 0 );

    for ( TInt row = 0; row <= limits.LastRow(); ++row )
        {
        for ( TInt column = 0; column <= limits.LastColumn(); ++column )
            {
            TAknLayoutRect layoutRect;
            layoutRect.LayoutRect( Rect(), AknLayoutScalable_Apps::cell_vitu2_itu_pane( landscape ? 1 : 0, column, row ).LayoutLine() );
  
      		TAknLayoutRect layoutRect2;
            layoutRect2.LayoutRect( layoutRect.Rect(), AknLayoutScalable_Apps::bg_button_pane_cp010( landscape ? 3 : 0 ).LayoutLine() );
        
            Components().At( row * ( limits.LastColumn() + 1 ) + column ).iControl->SetRect( layoutRect2.Rect() );
            }
        }
    }

CAknKeypad::CAknKeypad()
    {
    }

void CAknKeypad::ConstructL( CCoeControl& aParent, TInt aQueryType )
    {
    SetContainerWindowL( aParent );
    InitComponentArrayL();
    
    iQueryType = aQueryType;
    
    // create as many buttons as there are rows & columns
    TAknLayoutScalableParameterLimits limits = AknLayoutScalable_Apps::cell_vitu2_itu_pane_ParamLimits( 0 );
    
    TInt count = ( limits.LastRow() + 1 ) * ( limits.LastColumn() + 1 );
    
    const TChar KCharArray[] = 
    	{
    	'1', '2', '3', '4', '5', '6', '7', '8', '9', '*', '0', '#'
    	};
    
    const TInt KScanCodeArray[] =
    	{
    	49, 50, 51, 52, 53, 54, 55, 56, 57, EStdKeyNkpAsterisk, 48, EStdKeyHash
    	};
    
    for ( TInt i = 0; i < count; ++i )
        {
        TBuf<1> keyChar;
        keyChar.Append( KCharArray[i] );
      
        TInt scanCode = KScanCodeArray[ i ];
        CAknKeypadButton* button = CAknKeypadButton::NewL( keyChar, scanCode, this );
        CleanupStack::PushL( button );

        button->SetFocusing( EFalse );
        
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        
        TRgb color; 
        AknsUtils::GetCachedColor( skin, color, KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG68 );
   
  		button->OverrideColorL( EColorButtonText, color );
        button->OverrideColorL( EColorButtonTextPressed, color );
        button->OverrideColorL( EColorButtonTextDimmed, color );
        
        button->SetBackgroundIds( KAknsIIDQsnFrKeypadButtonNormal,
        	KAknsIIDQsnFrKeypadButtonPressed, KAknsIIDQsnFrKeypadButtonInactive,
        	KAknsIIDQsnFrKeypadButtonPressed, KAknsIIDQsnFrKeypadButtonInactive );
     
     	// Hack
        
        if ( i == 1)
        	{
        	button->SetUpperAndLowerTextL(_L("ABC"), _L("abc"));
       		}
        else if ( i == 2)
        	{
        	button->SetUpperAndLowerTextL(_L("DEF"), _L("def"));
        	}
        else if ( i == 3)
        	{
        	button->SetUpperAndLowerTextL(_L("GHI"), _L("ghi"));
        	}
        else if ( i == 4)
        	{
        	button->SetUpperAndLowerTextL(_L("JKL"), _L("jkl"));
        	}
        else if ( i == 5)
        	{
        	button->SetUpperAndLowerTextL(_L("MNO"), _L("mno"));
        	}	
        else if ( i == 6)
        	{
        	button->SetUpperAndLowerTextL(_L("PQRS"), _L("pqrs"));
        	}
        else if ( i == 7)
        	{
        	button->SetUpperAndLowerTextL(_L("TUV"), _L("tuv"));
        	}
        else if ( i == 8)
        	{
        	button->SetUpperAndLowerTextL(_L("WXYZ"), _L("wxyz"));
        	}
        else if ( i == 9)
        	{
        	button->SetUpperAndLowerTextL(_L("+"), _L("+"));
        	}
        else if ( i == 10)
        	{
        	TBuf<16> txt;
        	txt.Append( TChar(0xf812) );
        	button->SetUpperAndLowerTextL(txt, txt);
        	}
        else if ( i == 11)
        	{
        	TBuf<16> txt;
        	txt.Append( TChar(0x2191) );
        	button->SetUpperAndLowerTextL(txt, txt);
        	}
        	
        // End of Hack	
         
        
        if( scanCode == EStdKeyNkpAsterisk && aQueryType != ECodeLayout && aQueryType != EDataLayout)
        	{
            button->SetDimmed( ETrue );  
            }
        else if( scanCode == EStdKeyHash && aQueryType != EPinLayout && aQueryType != ECodeLayout && aQueryType != EDataLayout)
        	{
        	button->SetDimmed( ETrue );
        	}
        
        
        	
        CleanupStack::Pop(); // button
        
        Components().AppendLC( button, i );
        CleanupStack::Pop(); // button
        }
    }
    
    
void CAknKeypad::SetState(TAknEditingState aState)
	{
	iState = aState;
	Window().Invalidate( Rect() );
	}
	
TAknEditingState CAknKeypad::State()
	{
	return iState;
	}
	
TInt CAknKeypad::QueryType()
	{
	return iQueryType;	
	}
    
    
// CAknKeypadButton
        
CAknKeypadButton* CAknKeypadButton::NewL( const TDesC& aText, const TInt aScanCode, CAknKeypad* aKeypad )
	{
 	CAknKeypadButton* self = new (ELeave) CAknKeypadButton( KAknButtonKeyRepeat, aScanCode, aKeypad );
    CleanupStack::PushL( self );
    self->ConstructL( aText );
    CleanupStack::Pop( self );
    AKNTASHOOK_ADDL( self, "CAknKeypadButton" );
    return self;
	}

CAknKeypadButton::~CAknKeypadButton()
    {
    AKNTASHOOK_REMOVE();
    delete iUpperText;
    delete iLowerText;
    }
    
CAknKeypadButton::CAknKeypadButton( const TInt aFlags, const TInt aScanCode, CAknKeypad* aKeypad ):
	CAknButton( aFlags ), iScanCode(aScanCode), iKeypad(aKeypad)
    {
    }
    
void CAknKeypadButton::ConstructL( const TDesC& aText )
    {
    CAknButton::ConstructL( NULL, NULL, NULL, NULL, aText, KNullDesC, 0 );
    }
    
    
    
void CAknKeypadButton::SetUpperAndLowerTextL( const TDesC& aUpperText, const TDesC& aLowerText )
    {
    delete iUpperText;
    delete iLowerText;
    
    iUpperText = NULL;
    iLowerText = NULL;

    iUpperText = aUpperText.AllocL();
    iLowerText = aLowerText.AllocL();
    }    

void CAknKeypadButton::HandlePointerEventL( const TPointerEvent& aPointerEvent )
	{
	CAknButton::HandlePointerEventL( aPointerEvent);
	
	if ( AknLayoutUtils::PenEnabled() )
		{
		TInt activeKeypad =0;
        RProperty::Get(KCRUidAvkon, KAknKeyBoardLayout,activeKeypad);
        
        
        switch ( aPointerEvent.iType )
            {
            case TPointerEvent::EButton1Down:
                {
                TRawEvent event;
               	event.Set( TRawEvent::EKeyDown, iScanCode);
               	event.SetTip( ETrue );
               	
               	if (iEikonEnv->AppUi())
					{
					static_cast<CAknAppUi*>(iEikonEnv->EikAppUi())->DisableNextKeySound( iScanCode );
					}
               	
                if(activeKeypad != EPtiKeyboard12Key)
				    {				
              	    // Security lock code add, begin:
				    TKeyEvent keyEvent;
				    // Fep manager need check the event, the modifiers and the event type must the same
				    // And other parts must not use the same modifiers!!!
             	    keyEvent.iModifiers = EModifierNumLock | EModifierKeypad | EModifierSpecial;
							ControlEnv()->SimulateKeyEventL( keyEvent, EEventKeyDown );
				    // Security lock code add, end. 
				    }

            	CCoeEnv::Static()->WsSession().SimulateRawEvent( event );
            	
            	if ( iKeypad->QueryType() != ECodeLayout && iKeypad->QueryType() != EDataLayout)
                	{
            		TRawEvent event;
               		event.Set( TRawEvent::EKeyUp, iScanCode);
               		event.SetTip( ETrue );
            		CCoeEnv::Static()->WsSession().SimulateRawEvent( event );
                	}
                break;	
                }

            case TPointerEvent::EButton1Up:
                {
                if ( iKeypad->QueryType() == ECodeLayout || iKeypad->QueryType() == EDataLayout)
                	{
                	TRawEvent event;
               		event.Set( TRawEvent::EKeyUp, iScanCode);
               		event.SetTip( ETrue );
            		CCoeEnv::Static()->WsSession().SimulateRawEvent( event );
                	}
     
                break;
                }

            default:
                break;
            }
       }	
	}
	
	
void CAknKeypadButton::Draw( const TRect& /*aRect*/ ) const
    {
    TRect rect = Rect();

    TAknLayoutRect centerLayout;
    centerLayout.LayoutRect( rect,
        AknLayoutScalable_Avkon::toolbar_button_pane_g1().LayoutLine() );
    TRect innerRect = centerLayout.Rect();

    CWindowGc& gc = SystemGc();
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

 	TAknsItemID frameId = KAknsIIDQsnFrKeypadButtonNormal;

    if ( iButtonPressed )
    	{
        frameId = KAknsIIDQsnFrKeypadButtonPressed;
    	}
    else if ( IsDimmed())
        {
    	frameId = KAknsIIDQsnFrKeypadButtonInactive;
        }
        
    iBgContext->SetFrame( frameId );
    iBgContext->SetCenter( frameId );
    iBgContext->SetFrameRects( rect, innerRect );

    if ( !AknsDrawUtils::Background( skin, iBgContext, NULL, gc, rect, KAknsDrawParamNoClearUnderImage ) )
        {
        gc.SetBrushColor( KRgbRed );
        gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
        gc.DrawRect( rect );
        }
    gc.SetBrushStyle( CGraphicsContext::ENullBrush );


	CAknButtonState* state = State();
	TBool landscape = Layout_Meta_Data::IsLandscapeOrientation();
    
    // Draw left text
    TAknEditingState editingState = iKeypad->State();
    
    TAknTextComponentLayout leftLayout;
    leftLayout = AknLayoutScalable_Apps::cell_vitu2_itu_pane_t1( landscape ? 3 : 0  );
        
 	DrawText(gc, state->Text(), leftLayout, 1);	
 	
 	// Draw right text
 	
 	TAknTextComponentLayout rightLayout = AknLayoutScalable_Apps::cell_vitu2_itu_pane_t2( landscape ? 2 : 0 );
 	
 	if (editingState == EMultitapLower && iLowerText)
 		{
 		DrawText(gc, *iLowerText, rightLayout, 0);
 		}
 	else if ( (editingState == EMultitapUpper || 
 	           editingState == EMultitapShifted || editingState == EQwertyShift) 
 	           && iUpperText)
 		{
 		DrawText(gc, *iUpperText, rightLayout, 0);
 		}
    }




void CAknKeypadButton::DrawText( CWindowGc& aGc, const TDesC& aText, TAknTextComponentLayout& aLayout, TInt aMargin ) const
    {
    TAknLayoutText layoutText;
    layoutText.LayoutText(Rect(), aLayout.LayoutLine() );
    
    const CFont* font = layoutText.Font();
    TRect textRect = layoutText.TextRect();
    
    aGc.UseFont( font );
    
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
	TRgb color( layoutText.Color() );
	
    if ( IsDimmed() )
        {
        color = iEikonEnv->ControlColor( EColorButtonText, *this );
        color.SetAlpha( 77 );
        }
    else if ( iButtonPressed )
        {
        color = iEikonEnv->ControlColor( EColorButtonTextPressed, *this );
        }
    else
        {
        color = iEikonEnv->ControlColor( EColorButtonText, *this );
        }
    aGc.SetPenColor( color);
    
    // NOTE: Layout data not correct, add some space for text
    textRect.iBr.iX += aMargin;
    textRect.iTl.iX -= aMargin;
    	
    
    // buffer for visually ordered text
    TBuf<255 + KAknBidiExtraSpacePerLine> visualText; 
    TInt clipWidth = textRect.Width();

    // bidi processing - using AknBidiTextUtils.
    AknBidiTextUtils::ConvertToVisualAndClip(
        aText,
        visualText,
        *font,
        clipWidth,
        clipWidth );

    TInt baselineOffset = 0;
    switch ( iVerticalAlignment )
        {
        case ETop:
            baselineOffset = font->AscentInPixels();
            break;

        case EBottom:
            baselineOffset = textRect.Height();
            break;

        default:  // centered
            baselineOffset = font->AscentInPixels() +
                           ( textRect.Height() - font->AscentInPixels() ) / 2;
        }
        
    aGc.DrawText( visualText, textRect, baselineOffset, layoutText.Align() );    
    }
