/*
* Copyright (c) 2003-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Background task for generic tasks.
*
*/


#include "pslntaskgenericupdate.h"
#include "PslnUi.h"
#include "PslnGeneralThemeView.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ constructor can NOT contain any code, that might leave.
// ---------------------------------------------------------------------------
//
CPslnTaskGenericUpdate::CPslnTaskGenericUpdate( 
    CPslnUi& aUi,
    TPslnModelFunctionPtr aModelFunc, 
    TBool aUpdateList ) : iUi( aUi ), 
                          iModelFunc( aModelFunc ),
                          iUpdateList( aUpdateList ), 
                          iDone( EFalse ), 
                          iCallErr( KErrNone )
    {
    }

// ---------------------------------------------------------------------------
// Return ETrue when the process is done.
// ---------------------------------------------------------------------------
//
TBool CPslnTaskGenericUpdate::IsProcessDone() const
    {
    return iDone;
    }

// ---------------------------------------------------------------------------
// Completes one cycle of the process.
// ---------------------------------------------------------------------------
//
void CPslnTaskGenericUpdate::StepL()
    {
    if( IsProcessDone() ) 
        {
        return;
        }

    TRAP( iCallErr, ( iUi.Model()->*iModelFunc)() );

    if( iUpdateList )
        {
        static_cast<CPslnGeneralThemeView*>
            ( iUi.View( KPslnGeneralView ) )->
                UpdateSkinListItemsL();
        }

    iDone = ETrue;
    }

// End of file

