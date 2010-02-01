/*
* Copyright (c) 2002-2006 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef FINDITEMDIALOGPANIC_H
#define FINDITEMDIALOGPANIC_H

// ========== INCLUDE FILES ================================

// ========== CONSTANTS ====================================

// ========== MACROS =======================================

// ========== DATA TYPES ===================================

enum TFindItemDialogPanic
    {
    EItemOutOfDocumentRange = 0x100,
    ENoItemSelected,
    ENoSearchCase,
    ETooLongItem,
    EAiwMenu
    };

// ========== FUNCTION PROTOTYPES ==========================

// ---------------------------------------------------------
// Panic
//
// ---------------------------------------------------------
//
GLREF_C void Panic (TFindItemDialogPanic aPanic);

// ========== FORWARD DECLARATIONS =========================

// ========== CLASS DECLARATION ============================

#endif // FINDITEMDIALOGPANIC_H

// End of File
