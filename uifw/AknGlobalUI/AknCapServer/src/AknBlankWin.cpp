/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
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

#include "aknblankwin.h"

CAknServBlankWin::CAknServBlankWin(CEikServStatusPane* aSp)
: iSp(aSp)
    {
    if (iSp)
        {
        iSp->SetBlankWinObserver(this);
        }
    }

CAknServBlankWin::~CAknServBlankWin()
    {
    if (iSp)
        {
        iSp->SetBlankWinObserver(NULL);
        }
    }

CAknServBlankWin* CAknServBlankWin::NewL(RWindowGroup& aParent, CEikServStatusPane* aSp)
    {
    CAknServBlankWin* self = new(ELeave) CAknServBlankWin(aSp);
    CleanupStack::PushL(self);
    // We set ordinal param value to 0 (not -1) because we want to blank also serverside
    // statuspane panes.
    self->ConstructL(aParent, 0, ETrue);
    CleanupStack::Pop(); // self
    return(self);
    }

void CAknServBlankWin::HandleStatusPaneSizeChange()
    {
    TRAP_IGNORE( HandleStatusPaneSizeChangeL());
    // Statuspane should be ready at this point. We can set ordinal param to -1 now
    // to avoid wierd situations if unblank is delayed for some reason.
    if (!iLayoutBlank)
        {
        DrawableWindow()->SetOrdinalPosition(-1); 
        }
    }

void CAknServBlankWin::SetLayoutBlank(TBool aLayoutBlank)
    {
    iLayoutBlank = aLayoutBlank;
    
    if ( !iSp )
        {
        return;
        }
    
    if ( iLayoutBlank )
        {
        iSp->SetBlankWinObserver(this);
        }
    else    
        {
        iSp->SetBlankWinObserver(NULL);
        }
    }

// End of file 
