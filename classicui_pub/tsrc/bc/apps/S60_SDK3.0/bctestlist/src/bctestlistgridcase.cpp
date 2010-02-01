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
* Description:         test case for grid pane list box classes
*
*/









#include <eikenv.h>
#include <aknlists.h>
#include <barsread.h>
#include <akniconarray.h>

#include "bctestlistgridcase.h"
#include "bctestlistcontainer.h"
#include "bctestlist.hrh"
#include <bctestlist.rsg>
#include <bctestlist.mbg>

_LIT( KGridCreate1, "Create CAknPinbStyleGrid" );
_LIT( KGridCreate2, "Create CAknQdialStyleGrid" );
_LIT( KGridCreate3, "Create CAknCaleMonthStyleGrid" );

_LIT( KPinbTest1, "CAknPinbStyleGrid::SizeChanged" );
_LIT( KPinbTest2, "CAknPinbStyleGrid::MinimumSize" );
_LIT( KPinbTest3, "CAknPinbStyleGrid::HandlePointerEventL" );
_LIT( KLayoutSetupGridFormGfxCell, "AknListBoxLayouts::SetupGridFormGfxCell" );

_LIT( KQdialTest1, "CAknQdialStyleGrid::SizeChanged" );
_LIT( KQdialTest2, "CAknQdialStyleGrid::MinimumSize" );
_LIT( KQdialTest3, "CAknQdialStyleGrid::HandlePointerEventL" );

_LIT( KCaleMonthTest1, "CAknCaleMonthStyleGrid::SizeChanged" );
_LIT( KCaleMonthTest2, "CAknCaleMonthStyleGrid::MinimumSize" );
_LIT( KCaleMonthTest3, "CAknCaleMonthStyleGrid::HandlePointerEventL" );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestListGridCase* CBCTestListGridCase::NewL( 
    CBCTestListContainer* aContainer, CEikonEnv* aEikEnv )
    {
    CBCTestListGridCase* self = new( ELeave ) CBCTestListGridCase( 
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
CBCTestListGridCase::CBCTestListGridCase( CBCTestListContainer* aContainer,
    CEikonEnv* aEikEnv )
    : CBCTestListBaseCase( aContainer, aEikEnv )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestListGridCase::~CBCTestListGridCase()
    {    
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestListGridCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestListGridCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestListGridCase::BuildScriptL()
    {    
    for ( TInt i=0; i <= EBCTestCmdOutline42 - EBCTestCmdOutline40; i++ )
        {
        AddTestL( LeftCBA, REP( Down, 4 ), KeyOK, TEND );
        AddTestL( REP( Down, i ), KeyOK, TEND );
        }      
    }
    
// ---------------------------------------------------------------------------
// CBCTestListGridCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestListGridCase::RunL( TInt aCmd )
    {    
    if ( aCmd < EBCTestCmdOutline40 ||
         aCmd > EBCTestCmdOutline42 )
        {
        return;
        }
    iOutlineId = aCmd;
    ReleaseCase();
    PrepareCaseL( aCmd );
    TestGridListL( aCmd );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestListGridCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestListGridCase::PrepareCaseL( TInt aCmd )
    {        
    TInt resourceId( R_BCTESTLIST_SELECTION_GRID );

    switch ( aCmd )
        {        
        case EBCTestCmdOutline40:                       
            iListBox = new( ELeave ) CAknPinbStyleGrid();
            AssertNotNullL( iListBox, KGridCreate1 );
            break;
        case EBCTestCmdOutline41:            
            iListBox = new( ELeave ) CAknQdialStyleGrid();
            AssertNotNullL( iListBox, KGridCreate2 );
            break;
        case EBCTestCmdOutline42:            
            iListBox = new( ELeave ) CAknCaleMonthStyleGrid();
            AssertNotNullL( iListBox, KGridCreate3 );
            break;        
            
        default:
            break;
        }

    if ( iListBox )
        {    
        // construct from resource    
        iListBox->SetContainerWindowL( *iContainer );        

        TResourceReader reader;
        iEikEnv->CreateResourceReaderLC( reader, resourceId );
        iListBox->ConstructFromResourceL( reader );
        CleanupStack::PopAndDestroy(); // resource stuffs.        
        
        // create icon array
        CArrayPtr<CGulIcon>* icons = new( ELeave ) CAknIconArray(
        KBCTestListGraphicGulIconIndex );
        CleanupStack::PushL( icons );
        GraphicIconL( icons ); // Appends graphic data.
        // Sets graphics as ListBox icon.
        iListBox->ItemDrawer()->ColumnData()->SetIconArray( icons );
        CleanupStack::Pop();
                
        iContainer->SetControl( iListBox );        
        }    
    }
    
// ---------------------------------------------------------------------------
// CBCTestListGridCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//
void CBCTestListGridCase::ReleaseCase()
    {
    iContainer->ResetControl();
    iListBox = NULL;
    }
    
// ---------------------------------------------------------------------------
// CBCTestListGridCase::TestGridListL
// ---------------------------------------------------------------------------
//
void CBCTestListGridCase::TestGridListL( TInt aCmd )
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
        case EBCTestCmdOutline40:
            {
            CAknPinbStyleGrid* listbox = 
                static_cast<CAknPinbStyleGrid*>( iListBox );           
            listbox->SizeChanged();
            AssertTrueL( ETrue, KPinbTest1 );
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KPinbTest2 );            
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KPinbTest3 );
                        
            TRect rect = iContainer->Rect();
            TSize size = listbox->ItemDrawer()->MinimumCellSize();
            TPoint pt1( rect.iTl );
            TPoint pt2( rect.iTl.iX + size.iWidth, 
                rect.iTl.iY + size.iHeight );
            AknListBoxLayouts::SetupGridFormGfxCell( 
                *listbox, listbox->ItemDrawer(),
                0, rect.iTl.iX, rect.iTl.iY, rect.iBr.iX, rect.iBr.iY,
                size.iWidth, size.iHeight, pt1, pt2 );
            AssertTrueL( ETrue, KLayoutSetupGridFormGfxCell );
            }
            break;
        case EBCTestCmdOutline41:
            {
            CAknQdialStyleGrid* listbox = 
                static_cast<CAknQdialStyleGrid*>( iListBox );           
            listbox->SizeChanged();
            AssertTrueL( ETrue, KQdialTest1 );            
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KQdialTest2 );            
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KQdialTest3 );            
            }
            break;
        case EBCTestCmdOutline42:
            {
            CAknCaleMonthStyleGrid* listbox = 
                static_cast<CAknCaleMonthStyleGrid*>( iListBox );           
            listbox->SizeChanged();
            AssertTrueL( ETrue, KCaleMonthTest1 );            
            size = listbox->MinimumSize();
            AssertTrueL( ETrue, KCaleMonthTest2 );            
            listbox->HandlePointerEventL( event );
            AssertTrueL( ETrue, KCaleMonthTest3 );            
            }
            break;
                            
        default:
            break;
        }        
    }
    
// ---------------------------------------------------------------------------
// CBCTestListGridCase::GraphicIconL
// ---------------------------------------------------------------------------
//
void CBCTestListGridCase::GraphicIconL( CArrayPtr<CGulIcon>* aIcons )
    {
    if ( aIcons )
        {
        // Appends icon according to iOutlineId.
        switch ( iOutlineId )
            {            
            case EBCTestCmdOutline40:
            case EBCTestCmdOutline41:
            case EBCTestCmdOutline42:
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
                                    
                break;
           
            default:
                break;
            }
        }
    }
