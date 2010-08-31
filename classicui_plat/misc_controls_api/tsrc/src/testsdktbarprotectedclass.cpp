/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  misc_controls_api
*
*/


//  INCLUDES

#include "testsdktbarprotectedclass.h"

// -----------------------------------------------------------------------------
// CTestToolBar::AsControl
// -----------------------------------------------------------------------------

const CCoeControl* CTestToolBar::AsControl() const
    {
    return NULL;
    }
// -----------------------------------------------------------------------------
// CTestToolBar::AsControl
// -----------------------------------------------------------------------------

CCoeControl* CTestToolBar::AsControl()
    {
    return NULL;
    }
// -----------------------------------------------------------------------------
// CTestToolBar::GroupControlById
// -----------------------------------------------------------------------------
CCoeControl* CTestToolBar::GroupControlById(TInt /*aCommandId*/) const
    {
    return NULL;
    }
// -----------------------------------------------------------------------------
// CTestToolBar::GroupControlAsButton
// -----------------------------------------------------------------------------
CEikCommandButton* CTestToolBar::GroupControlAsButton(TInt /*aCommandId*/) const
    {
    return NULL;
    }
// -----------------------------------------------------------------------------
// CTestToolBar::CalcMinimumSizeL
// -----------------------------------------------------------------------------
TSize CTestToolBar::CalcMinimumSizeL(TInt /*aResourceId*/)
    {
    TSize size; 
    return size;
    }
// -----------------------------------------------------------------------------
// CTestToolBar::CommandId
// -----------------------------------------------------------------------------
TInt CTestToolBar::CommandId(TInt /*aCommandPos*/) const
    {
    return 0;
    }
// -----------------------------------------------------------------------------
// CTestToolBar::ButtonCount
// -----------------------------------------------------------------------------
TInt CTestToolBar::ButtonCount() const
    {
    return 0;
    }
// -----------------------------------------------------------------------------
// CTestToolBar::CommandPos
// -----------------------------------------------------------------------------
TInt CTestToolBar::CommandPos(TInt /*aCommandId*/) const
    {
    return 0;
    }
// -----------------------------------------------------------------------------
// CTestToolBar::IsCommandDimmed
// -----------------------------------------------------------------------------
TBool CTestToolBar::IsCommandDimmed(TInt /*aCommandId*/) const
    {
    return ETrue;
    }
// -----------------------------------------------------------------------------
// CTestToolBar::IsCommandDimmedByPosition
// -----------------------------------------------------------------------------
TBool CTestToolBar::IsCommandDimmedByPosition(TInt /*aPosition*/) const
    {
    return ETrue;
    }
// -----------------------------------------------------------------------------
// CTestToolBar::IsCommandVisible
// -----------------------------------------------------------------------------
TBool CTestToolBar::IsCommandVisible(TInt /*aCommandId*/) const
    {
    return ETrue;
    }
// -----------------------------------------------------------------------------
// CTestToolBar::IsCommandVisibleByPosition
// -----------------------------------------------------------------------------
TBool CTestToolBar::IsCommandVisibleByPosition(TInt /*aPosition*/) const
    {
    return ETrue;
    }
// -----------------------------------------------------------------------------
// CTestToolBar::ButtonGroupFlags
// -----------------------------------------------------------------------------
TUint CTestToolBar::ButtonGroupFlags() const
    {
    return 0;
    }
// -----------------------------------------------------------------------------
// CTestToolBar::AddCommandL
// -----------------------------------------------------------------------------
void CTestToolBar::AddCommandL( TInt /*aPosition*/, TInt /*aCommandId*/, const TDesC* /*aText*/,
                      const CFbsBitmap* /*aBitmap*/, const CFbsBitmap* /*aMask*/ )
    {
    
    }
// -----------------------------------------------------------------------------
// CTestToolBar::AddCommandSetToStackL
// -----------------------------------------------------------------------------
void CTestToolBar::AddCommandSetToStackL(TInt /*aResourceId*/)
    {
    
    }
// -----------------------------------------------------------------------------
// CTestToolBar::AddCommandToStackL
// -----------------------------------------------------------------------------
void CTestToolBar::AddCommandToStackL( TInt /*aPosition*/, TInt /*aCommandId*/, const TDesC* /*aText*/,
                             const CFbsBitmap* /*aBitmap*/, const CFbsBitmap* /*aMask*/ )
    {
     
    }
// -----------------------------------------------------------------------------
// CTestToolBar::AddCommandToStackL
// -----------------------------------------------------------------------------
void CTestToolBar::AddCommandToStackL(TInt /*aPosition*/,TInt /*aResourceId*/)
    {
    
    }
// -----------------------------------------------------------------------------
// CTestToolBar::AnimateCommandByPosition
// -----------------------------------------------------------------------------
void CTestToolBar::AnimateCommandByPosition(TInt /*aPosition*/)
    {
    
    }
// -----------------------------------------------------------------------------
// CTestToolBar::DimCommand
// -----------------------------------------------------------------------------
void CTestToolBar::DimCommand(TInt /*aCommandId*/,TBool /*aDimmed*/)
    {
    
    }
// -----------------------------------------------------------------------------
// CTestToolBar::DimCommandByPosition
// -----------------------------------------------------------------------------
void CTestToolBar::DimCommandByPosition(TInt /*aPosition*/,TBool /*aDimmed*/)
    {
    
    }
// -----------------------------------------------------------------------------
// CTestToolBar::MakeCommandVisible
// -----------------------------------------------------------------------------
void CTestToolBar::MakeCommandVisible(TInt /*aCommandId*/,TBool /*aVisible*/)
    {
    
    }
// -----------------------------------------------------------------------------
// CTestToolBar::MakeCommandVisibleByPosition
// -----------------------------------------------------------------------------
void CTestToolBar::MakeCommandVisibleByPosition(TInt /*aPosition*/,TBool /*aVisible*/)
    {
    
    }
// -----------------------------------------------------------------------------
// CTestToolBar::RemoveCommandFromStack
// -----------------------------------------------------------------------------
void CTestToolBar::RemoveCommandFromStack(TInt /*aPosition*/,TInt /*aCommandId*/)
    {
    
    }
// -----------------------------------------------------------------------------
// CTestToolBar::SetCommandL
// -----------------------------------------------------------------------------
void CTestToolBar::SetCommandL(TInt /*aPosition*/,TInt /*aResourceId*/)
    {
    
    }
// -----------------------------------------------------------------------------
// CTestToolBar::SetCommandL
// -----------------------------------------------------------------------------
void CTestToolBar::SetCommandL( TInt /*aPosition*/, TInt /*aCommandId*/, const TDesC* /*aText*/,
                                const CFbsBitmap* /*aBitmap*/, const CFbsBitmap* /*aMask*/ )
    {
    
    }
// -----------------------------------------------------------------------------
// CTestToolBar::SetCommandSetL
// -----------------------------------------------------------------------------
void CTestToolBar::SetCommandSetL(TInt /*aResourceId*/)
    {
    
    }
// -----------------------------------------------------------------------------
// CTestToolBar::SetDefaultCommand
// -----------------------------------------------------------------------------
void CTestToolBar::SetDefaultCommand(TInt /*aCommandId*/)
    {
    
    }
// -----------------------------------------------------------------------------
// CTestToolBar::SetMSKCommandObserver
// -----------------------------------------------------------------------------
void CTestToolBar::SetMSKCommandObserver(MEikCommandObserver* /*aCommandObserver*/)
    {
    
    }
