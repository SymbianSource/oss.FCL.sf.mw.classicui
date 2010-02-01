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
* Description:  Interface for model classes to be used by
*                CAknMemorySelectionEventHandler.
*
*/



#ifndef M_AKNMEMORYSELECTIONMODEL_H
#define M_AKNMEMORYSELECTIONMODEL_H

#include <bamdesca.h> // MDesCArray

/**
*  interface class for memory selection models
*
*  @lib CommonDialogs.lib
*  @since S60 5.0
*/
class MAknMemorySelectionModel: public MDesCArray
    {

public:

// Enumerations

    /**
    * Layout for listbox. For decorating items.
    */
    enum TListBoxLayout
        {
        ELayoutPopupMenu = 0,
        ELayoutSettingPage = 10,
        ELayoutDoublePopup = 20
        };

// Constructors and destructor

    /**
     * A virtual destructor to ensure that correct destructor gets called.
     * Must have an empty implementation.
     */
    virtual ~MAknMemorySelectionModel() { };

// New functions

    /**
     * Update Data arrays
     */
    virtual void UpdateDataArraysL() { }

    /**
     * Update model's items
     */
    virtual void UpdateItemsL() = 0;

    /**
     * Get path of a drive referenced by given listbox item index.
     * @param aLbxItemIndex Index of the listbox item.
     * @param aDrivePath A reference to a descriptor where the drive path is
     *        stored.
     */
    virtual void GetDrive( TInt aLbxItemIndex, TDes& aDrivePath ) = 0;

    };


#endif // M_AKNMEMORYSELECTIONMODEL_H
