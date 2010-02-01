/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         test case for formatted list classes
*
*/









#include <aknlists.h>

#include "bctestlistformattedcase.h"
#include "bctestlistcontainer.h"
#include "bctestlist.hrh"
#include <bctestlist.rsg>
#include <bctestlist.mbg>

_LIT( KFormattedCreate1, "Create CAknDoubleStyleListBox" );
_LIT( KFormattedCreate2, "Create CAknDoubleStyle2ListBox" );
_LIT( KFormattedCreate3, "Create CAknDoubleNumberStyleListBox" );
_LIT( KFormattedCreate4, "Create CAknDoubleTimeStyleListBox" );
_LIT( KFormattedCreate5, "Create CAknDoubleLargeStyleListBox" );
_LIT( KFormattedCreate6, "Create CAknDoubleGraphicStyleListBox" );
_LIT( KFormattedCreate7, "Create CAknDouble2GraphicStyleListBox" );
_LIT( KFormattedCreate8, "Create CAknDouble2LargeStyleListBox" );
_LIT( KFormattedCreate9, "Create CAknDouble2GraphicLargeGraphicStyleListBox" );
_LIT( KFormattedCreate10, "Create CAknFormDoubleGraphicStyleListBox" );
_LIT( KFormattedCreate11, "Create CAknFormDoubleStyleListBox" );

_LIT( KDoubleStyleTest1, "CAknDoubleStyleListBox::SizeChanged" );
_LIT( KDoubleStyleTest2, "CAknDoubleStyleListBox::MinimumSize" );
_LIT( KDoubleStyleTest3, "CAknDoubleStyleListBox::HandlePointerEventL" );
_LIT( KListBoxLayoutSetupFormTextCell, "AknListBoxLayouts::SetupFormTextCell" );

_LIT( KDoubleStyle2Test1, "CAknDoubleStyle2ListBox::SizeChanged" );
_LIT( KDoubleStyle2Test2, "CAknDoubleStyle2ListBox::MinimumSize" );
_LIT( KDoubleStyle2Test3, "CAknDoubleStyle2ListBox::HandlePointerEventL" );

_LIT( KDoubleNumberTest1, "CAknDoubleNumberStyleListBox::SizeChanged" );
_LIT( KDoubleNumberTest2, "CAknDoubleNumberStyleListBox::MinimumSize" );
_LIT( KDoubleNumberTest3, "CAknDoubleNumberStyleListBox::HandlePointerEventL" );

_LIT( KDoubleTimeTest1, "CAknDoubleTimeStyleListBox::SizeChanged" );
_LIT( KDoubleTimeTest2, "CAknDoubleTimeStyleListBox::MinimumSize" );
_LIT( KDoubleTimeTest3, "CAknDoubleTimeStyleListBox::HandlePointerEventL" );

_LIT( KDoubleLargeTest1, "CAknDoubleLargeStyleListBox::SizeChanged" );
_LIT( KDoubleLargeTest2, "CAknDoubleLargeStyleListBox::MinimumSize" );
_LIT( KDoubleLargeTest3, "CAknDoubleLargeStyleListBox::HandlePointerEventL" );

_LIT( KDoubleGraphicTest1, "CAknDoubleGraphicStyleListBox::SizeChanged" );
_LIT( KDoubleGraphicTest2, "CAknDoubleGraphicStyleListBox::MinimumSize" );
_LIT( KDoubleGraphicTest3, "CAknDoubleGraphicStyleListBox::HandlePointerEventL" );

_LIT( KDouble2GraphicTest1, "CAknDouble2GraphicStyleListBox::SizeChanged" );
_LIT( KDouble2GraphicTest2, "CAknDouble2GraphicStyleListBox::MinimumSize" );
_LIT( KDouble2GraphicTest3, "CAknDouble2GraphicStyleListBox::HandlePointerEventL" );

_LIT( KDouble2LargeTest1, "CAknDouble2LargeStyleListBox::SizeChanged" );
_LIT( KDouble2LargeTest2, "CAknDouble2LargeStyleListBox::MinimumSize" );
_LIT( KDouble2LargeTest3, "CAknDouble2LargeStyleListBox::HandlePointerEventL" );

_LIT( KDouble2GraphicLargeGraphicTest1, "CAknDouble2GraphicLargeGraphicStyleListBox::SizeChanged" );
_LIT( KDouble2GraphicLargeGraphicTest2, "CAknDouble2GraphicLargeGraphicStyleListBox::MinimumSize" );
_LIT( KDouble2GraphicLargeGraphicTest3, "CAknDouble2GraphicLargeGraphicStyleListBox::HandlePointerEventL" );

_LIT( KFormDoubleGraphicTest1, "CAknFormDoubleGraphicStyleListBox::SizeChanged" );
_LIT( KFormDoubleGraphicTest2, "CAknFormDoubleGraphicStyleListBox::MinimumSize" );
_LIT( KFormDoubleGraphicTest3, "CAknFormDoubleGraphicStyleListBox::HandlePointerEventL" );

_LIT( KFormDoubleTest1, "CAknFormDoubleStyleListBox::SizeChanged" );
_LIT( KFormDoubleTest2, "CAknFormDoubleStyleListBox::MinimumSize" );
_LIT( KFormDoubleTest3, "CAknFormDoubleStyleListBox::HandlePointerEventL" );


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestListFormattedCase* CBCTestListFormattedCase::NewL( 
    CBCTestListContainer* aContainer, CEikonEnv* aEikEnv )
    {
    CBCTestListFormattedCase* self = new( ELeave ) CBCTestListFormattedCase( 
        aContainer, aEikEnv );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestListFormattedCase::CBCTestListFormattedCase( 
    CBCTestListContainer* aContainer, CEikonEnv* aEikEnv )
    : CBCTestListBaseCase( aContainer, aEikEnv )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestListFormattedCase::~CBCTestListFormattedCase()
    {    
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestListFormattedCase::ConstructL()
    {    
    BuildScriptL();
    }
    
// ---------------------------------------------------------------------------
// CBCTestListFormattedCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestListFormattedCase::BuildScriptL()
    {    
    for ( TInt i=0; i <= EBCTestCmdOutline20 - EBCTestCmdOutline10; i++ )
        {
        AddTestL( LeftCBA, Down, KeyOK, TEND );
        AddTestL( REP( Down, i ), KeyOK, TEND );
        }      
    }
    
// ---------------------------------------------------------------------------
// CBCTestListFormattedCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestListFormattedCase::RunL( TInt aCmd )
    {    
    if ( aCmd < EBCTestCmdOutline10 ||
         aCmd > EBCTestCmdOutline20 )
        {
        return;
        }
    iOutlineId = aCmd;
    ReleaseCase();
    PrepareCaseL( aCmd );
    TestFormattedCellListL( aCmd );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestListFormattedCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestListFormattedCase::PrepareCaseL( TInt aCmd )
    {    
    TInt resourceId( KBCTestListInitListResourceId );    
    TBool useGraphics( EFalse );
    CDesCArray* textArray = NULL;

    switch ( aCmd )
        {        
        case EBCTestCmdOutline10:                       
            iListBox = new( ELeave ) CAknDoubleStyleListBox();
            AssertNotNullL( iListBox, KFormattedCreate1 );
            break;
        case EBCTestCmdOutline11:                       
            iListBox = new( ELeave ) CAknDoubleStyle2ListBox();
            useGraphics = ETrue;
            textArray = iEikEnv->ReadDesCArrayResourceL( 
                R_BCTESTLIST_DOUBLE2_ITEM );
            AssertNotNullL( iListBox, KFormattedCreate2 );
            break;
        case EBCTestCmdOutline12:
            resourceId = R_BCTESTLIST_LOOP_BIG_SINGLE_NUMBER;            
            iListBox = new( ELeave ) CAknDoubleNumberStyleListBox();
            AssertNotNullL( iListBox, KFormattedCreate3 );
            break;
        case EBCTestCmdOutline13:
            resourceId = R_BCTESTLIST_DOUBLE_TIME;
            iListBox = new( ELeave ) CAknDoubleTimeStyleListBox();
            AssertNotNullL( iListBox, KFormattedCreate4 );
            break;
        case EBCTestCmdOutline14:
            resourceId = R_BCTESTLIST_DOUBLE_LARGE_GRAPHIC;
            useGraphics = ETrue;
            iListBox = new( ELeave ) CAknDoubleLargeStyleListBox();
            AssertNotNullL( iListBox, KFormattedCreate5 );
            break;
        case EBCTestCmdOutline15:
            resourceId = R_BCTESTLIST_DOUBLE_GRAPHIC;
            useGraphics = ETrue;
            iListBox = new( ELeave ) CAknDoubleGraphicStyleListBox();
            AssertNotNullL( iListBox, KFormattedCreate6 );
            break;
        case EBCTestCmdOutline16:
            resourceId = R_BCTESTLIST_DOUBLE2_GRAPHIC;
            useGraphics = ETrue;
            iListBox = new( ELeave ) CAknDouble2GraphicStyleListBox();
            AssertNotNullL( iListBox, KFormattedCreate7 );
            break;
        case EBCTestCmdOutline17:
            resourceId = R_BCTESTLIST_DOUBLE_LARGE_GRAPHIC;
            useGraphics = ETrue;
            iListBox = new( ELeave ) CAknDouble2LargeStyleListBox();
            AssertNotNullL( iListBox, KFormattedCreate8 );
            break;
        case EBCTestCmdOutline18:
            resourceId = R_BCTESTLIST_DOUBLE2_GRAPHIC_LARGE_GRAPHIC;
            useGraphics = ETrue;
            iListBox = 
                new( ELeave ) CAknDouble2GraphicLargeGraphicStyleListBox();
            AssertNotNullL( iListBox, KFormattedCreate9 );
            break;
        case EBCTestCmdOutline19:
            resourceId = R_BCTESTLIST_DOUBLE_GRAPHIC;
            iListBox = new( ELeave ) CAknFormDoubleGraphicStyleListBox();
            useGraphics = ETrue;
            AssertNotNullL( iListBox, KFormattedCreate10 );
            break;
        case EBCTestCmdOutline20:
            resourceId = R_BCTESTLIST_DOUBLE_GRAPHIC;
            useGraphics = ETrue;
            iListBox = new( ELeave ) CAknFormDoubleStyleListBox();
            AssertNotNullL( iListBox, KFormattedCreate11 );
            break; 
        case EBCTestCmdOutline21:
            resourceId = R_BCTESTLIST_DOUBLE_LARGE_GRAPHIC;
            useGraphics = ETrue;
            iListBox = new( ELeave ) CAknDoubleLargeStyleListBox();
            break;        
        default:
            break;
        }

    if ( iListBox )
        {        
        if ( resourceId != 0 )
            {
            SetListBoxFromResourceL( iListBox, resourceId );            
            }
        else
            {            
            if ( textArray )
                {
                SetListBoxFromInnerDescriptionL( iListBox, 
                    EAknListBoxSelectionList, textArray );
                }
            else
                {
                SetListBoxFromInnerDescriptionL( iListBox );
                }
            }
               
        if ( useGraphics )
            {
            SetGraphicIconL( iListBox );
            }
        
        iContainer->SetControl( iListBox );        
        }    
    }
    
// ---------------------------------------------------------------------------
// CBCTestListFormattedCase::ReleaseCase
// ---------------------------------------------------------------------------
//
void CBCTestListFormattedCase::ReleaseCase()
    {
    iContainer->ResetControl();    
    iListBox = NULL;
    }
    
// ---------------------------------------------------------------------------
// CBCTestListFormattedCase::TestFormattedCellListL
// ---------------------------------------------------------------------------
//
void CBCTestListFormattedCase::TestFormattedCellListL( TInt aCmd )
    {
    if ( !iListBox )
        {
        return;
        }
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos(0, 30);
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
        
    TSize size;
    switch ( aCmd )
        {
        case EBCTestCmdOutline10:
            {
            CAknDoubleStyleListBox* listbox = 
                static_cast<CAknDoubleStyleListBox*>( iListBox );            
            listbox->SizeChanged();
            AssertTrueL( ETrue, KDoubleStyleTest1 );
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KDoubleStyleTest2 );            
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KDoubleStyleTest3 );            
            
            TRect rect = iContainer->Rect();
            TSize size = listbox->ItemDrawer()->MinimumCellSize();
            TPoint pt1( rect.iTl );
            TPoint pt2( rect.iTl.iX + size.iWidth, 
                rect.iTl.iY + size.iHeight );
            AknListBoxLayouts::SetupFormTextCell( 
                *listbox, listbox->ItemDrawer(), 0, iEikEnv->NormalFont(),
                0, rect.iTl.iX, rect.iTl.iY, rect.iBr.iY, size.iWidth,
                CGraphicsContext::ELeft, pt1, pt2
                );
            AssertTrueL( ETrue, KListBoxLayoutSetupFormTextCell );            
            }
            break;
        case EBCTestCmdOutline11:
            {
            CAknDoubleStyle2ListBox* listbox = 
                static_cast<CAknDoubleStyle2ListBox*>( iListBox );           
            listbox->SizeChanged();
            AssertTrueL( ETrue, KDoubleStyle2Test1 );            
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KDoubleStyle2Test2 );            
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KDoubleStyle2Test3 );            
            }
            break;
        case EBCTestCmdOutline12:
            {
            CAknDoubleNumberStyleListBox* listbox = 
                static_cast<CAknDoubleNumberStyleListBox*>( iListBox );           
            listbox->SizeChanged();
            AssertTrueL( ETrue, KDoubleNumberTest1 );            
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KDoubleNumberTest2 );            
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KDoubleNumberTest3 );            
            }            
            break;
        case EBCTestCmdOutline13:
            {
            CAknDoubleTimeStyleListBox* listbox = 
                static_cast<CAknDoubleTimeStyleListBox*>( iListBox );           
            listbox->SizeChanged();
            AssertTrueL( ETrue, KDoubleTimeTest1 );            
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KDoubleTimeTest2 );            
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KDoubleTimeTest3 );            
            }            
            break;
        case EBCTestCmdOutline14:
            {
            CAknDoubleLargeStyleListBox* listbox = 
                static_cast<CAknDoubleLargeStyleListBox*>( iListBox );           
            listbox->SizeChanged();
            AssertTrueL( ETrue, KDoubleLargeTest1 );            
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KDoubleLargeTest2 );            
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KDoubleLargeTest3 );            
            }            
            break;
        case EBCTestCmdOutline15:
            {
            CAknDoubleGraphicStyleListBox* listbox = 
                static_cast<CAknDoubleGraphicStyleListBox*>( iListBox );           
            listbox->SizeChanged();
            AssertTrueL( ETrue, KDoubleGraphicTest1 );            
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KDoubleGraphicTest2 );            
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KDoubleGraphicTest3 );            
            }            
            break;
        case EBCTestCmdOutline16:
            {
            CAknDouble2GraphicStyleListBox* listbox = 
                static_cast<CAknDouble2GraphicStyleListBox*>( iListBox );           
            listbox->SizeChanged();
            AssertTrueL( ETrue, KDouble2GraphicTest1 );            
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KDouble2GraphicTest2 );            
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KDouble2GraphicTest3 );            
            }            
            break;
        case EBCTestCmdOutline17:
            {
            CAknDouble2LargeStyleListBox* listbox = 
                static_cast<CAknDouble2LargeStyleListBox*>( iListBox );           
            listbox->SizeChanged();
            AssertTrueL( ETrue, KDouble2LargeTest1 );            
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KDouble2LargeTest2 );            
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KDouble2LargeTest3 );            
            }            
            break;
        case EBCTestCmdOutline18:
            {
            CAknDouble2GraphicLargeGraphicStyleListBox* listbox = 
                static_cast<CAknDouble2GraphicLargeGraphicStyleListBox*>( iListBox );           
            listbox->SizeChanged();
            AssertTrueL( ETrue, KDouble2GraphicLargeGraphicTest1 );            
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KDouble2GraphicLargeGraphicTest2 );            
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KDouble2GraphicLargeGraphicTest3 );            
            }
            break;
        case EBCTestCmdOutline19:
            {
            CAknFormDoubleGraphicStyleListBox* listbox = 
                static_cast<CAknFormDoubleGraphicStyleListBox*>( iListBox );           
            listbox->SizeChanged();
            AssertTrueL( ETrue, KFormDoubleGraphicTest1 );            
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KFormDoubleGraphicTest2 );            
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KFormDoubleGraphicTest3 );            
            }            
            break;
        case EBCTestCmdOutline20:
            {
            CAknFormDoubleStyleListBox* listbox = 
                static_cast<CAknFormDoubleStyleListBox*>( iListBox );           
            listbox->SizeChanged();
            AssertTrueL( ETrue, KFormDoubleTest1 );            
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KFormDoubleTest2 );            
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KFormDoubleTest3 );            
            }            
            break;
                                
        default:
            break;
        }        
    }
    
// ---------------------------------------------------------------------------
// CBCTestListFormattedCase::GraphicIconL
// ---------------------------------------------------------------------------
//
void CBCTestListFormattedCase::GraphicIconL( CArrayPtr<CGulIcon>* aIcons )
    {
    if ( aIcons )
        {
        // Appends icon according to iOutlineId.
        switch ( iOutlineId )
            {            
            case EBCTestCmdOutline14:            
            case EBCTestCmdOutline17:
            case EBCTestCmdOutline18:
                CreateIconAndAddToArrayL(
                    aIcons, KBCTestListMifFileName,
                    EMbmBctestlistQgn_indi_marked_add,
                    EMbmBctestlistQgn_indi_marked_add_mask );
                CreateIconAndAddToArrayL(
                    aIcons, KBCTestListMbmFileName,
                    EMbmBctestlistGolgo2,
                    EMbmBctestlistGolgo2_mask );                    
                CreateIconAndAddToArrayL(
                    aIcons, KBCTestListMbmFileName,
                    EMbmBctestlistGolgo3,
                    EMbmBctestlistGolgo3_mask );
                CreateIconAndAddToArrayL(
                    aIcons, KBCTestListMbmFileName,
                    EMbmBctestlistGolgo4,
                    EMbmBctestlistGolgo4_mask );
                CreateIconAndAddToArrayL(
                    aIcons, KBCTestListMbmFileName,
                    EMbmBctestlistGolgo5,
                    EMbmBctestlistGolgo5_mask );
                break;
            case EBCTestCmdOutline11:
            case EBCTestCmdOutline15:
            case EBCTestCmdOutline16:
            case EBCTestCmdOutline19:
            case EBCTestCmdOutline20:
                CreateIconAndAddToArrayL(
                    aIcons, KBCTestListMifFileName,
                    EMbmBctestlistQgn_indi_marked_add,
                    EMbmBctestlistQgn_indi_marked_add_mask );
                CreateIconAndAddToArrayL(
                    aIcons, KBCTestListMbmFileName,
                    EMbmBctestlistGolgo3,
                    EMbmBctestlistGolgo3_mask );
                break;

            default:
                break;
            }
        }
    }
