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
*       application grid
* 
*
*/


#ifndef __AKNAPPGRID_H__
#define __AKNAPPGRID_H__


#include <eikfrlb.h>
#include <AknGrid.h>
#include "aknshortcuts.h"

typedef AknListBoxShortCutTemplate<CAknGrid> CAknShortCutSelectionGridTypedef;
#define AKNSHORTCUTGRID AknListBoxShortCutTemplate<CAknGrid>


/** grid_app_pane
 * Application shell uses this (note that part of layout needs to be done
 * inside application -- the listbox will not be in correct position on the
 * screen by just using this -- see listapp)
 */
class CAknAppStyleGrid : public CAknShortCutSelectionGridTypedef
    {
public:
    IMPORT_C virtual void ConstructL(const CCoeControl* aParent, TInt aFlags=0);
    IMPORT_C void SizeChanged();
    IMPORT_C TSize MinimumSize();
    IMPORT_C void SetShortcutEnabledL(TBool aValue);
    IMPORT_C void DrawBackgroundAroundGrid(CWindowGc &aGc, const TRect &aClientRect, const TRect &aGridRect);
private:
    void SizeChangedL();
    };


#endif
