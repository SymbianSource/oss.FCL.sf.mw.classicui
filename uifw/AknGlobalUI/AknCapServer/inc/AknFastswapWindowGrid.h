/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Grid handling the list functionality in fast application swap.
*
*/

#ifndef AKNFASTSWAPWINDOWGRID_H
#define AKNFASTSWAPWINDOWGRID_H

//  INCLUDES
#include <AknGrid.h>
#include <eikfrlb.h>
#include <bldvariant.hrh>

/**
 *  Grid handling the list functionality in fast application swap
 *  Basically a listbox with a different item drawer.
 */
NONSHARABLE_CLASS(CAknFastSwapWindowGrid): public CAknGrid
    {
    public: // Functions from base classes
        /**
         * From CCoeControl.
         */
        void SizeChanged();

        /**
         * From CAknGrid/CEikFormattedCellListBox.
         */
        void CreateItemDrawerL();

        /**
         * From CAknGrid/CEikFormattedCellListBox.
         */
        void HandleItemRemovalL();

        void UpdateScrollBarsL();
 
    private:
        /**
         * Color and border setting.
         */
        void SetupStandardGrid();

        /**
         * From CCoeControl      Method handling the pointer events while the fsw is used.
         * @param aPointerEvent  Information about the event.
         */
        void HandlePointerEventL( const TPointerEvent &aPointerEvent );
    
    private: // listbox use only
        IMPORT_C virtual void CEikListBox_Reserved(); 
        
    };

#endif // AKNFSGRID_H   
            
// End of File
