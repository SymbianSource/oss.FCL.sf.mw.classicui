/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Container for compatibility mode view.
*
*/


#ifndef AKNCOMPAGSCONTAINER_H
#define AKNCOMPAGSCONTAINER_H

#include <gsbasecontainer.h>
#include "gssettingid.h"


class CGSListBoxItemTextArray;


/**
*  CAknCompaGSContainer container class
*  @since Series 60 5.0
* 
*/
class CAknCompaGSContainer : public CGSBaseContainer
    {
    public: // Constructors and destructor
        
        /**
        * Symbian OS constructor.
        * @param aRect Listbox's rect.
        * 
        */
        void ConstructL( const TRect& aRect );

        /**
        * Destructor.
        */
        ~CAknCompaGSContainer();

    public: //new

        /**
        * Updates listbox's item's value.
        * @param aFeatureId An item which is updated.
        * 
        */
        void UpdateListBoxL( TInt aFeatureId, TInt aValue );

        /**
        * Retrieves the currently selected listbox feature id
        * @return feature id.
        */
        TInt CurrentFeatureId() const;

    protected: // from CGSBaseContainer
        void ConstructListBoxL( TInt aResLbxId );

    private: // new

        void CreateListBoxItemsL();
        void MakeCompaModeStateItemL();
        void UpdateCompaModeStateItemL(const TInt& aState);
    
    private: // data
        CDesCArrayFlat* iCompaModeStateItems;
        CGSListBoxItemTextArray* iListboxItemArray;
        
    };

#endif // AKNCOMPAGSCONTAINER_H

// End of File
