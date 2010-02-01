/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Constants for hierarchical list internal use.
*
*/


#ifndef AKNTREELISTINTERNALCONSTANTS_H
#define AKNTREELISTINTERNALCONSTANTS_H


/** Namespace for concrete hiearchical list item types. */
namespace AknTreeList
    {
    /** Root of tree structure. */
    const TInt KTree = 1;

    /** Single style tree leaf. */
    const TInt KSingleStyleTreeLeaf = 2;

    /** Single style tree node. */
    const TInt KSingleStyleTreeNode = 3;

    /** Single column style simple data row. */
    const TInt KSingleColumnStyleSimpleDataRow = 4;

    /** Single column style core data row. */
    const TInt KSingleColumnStyleCoreDataRow = 5;

    /** Single column style subtitle row. */
    const TInt KSingleColumnStyleSubtitleRow = 6;
    }


#endif // AKNTREELISTINTERNALCONSTANTS_H
