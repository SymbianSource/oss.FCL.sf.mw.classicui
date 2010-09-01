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
* Description:  Compa mode Settings model.
*
*/


#ifndef AKNCOMPAGSMODEL_H
#define AKNCOMPAGSMODEL_H

#include <e32base.h>

class CRepository;

/**
*  CAknCompaGSModel is the model class for akncompamode GS plugin.
*  It provides functions to get and set setting values.
*  @since Series 60_5.0
*/
class CAknCompaGSModel : public CBase
    {
    public:  // Constructor and destructor
        /**
        * Two-phased constructor
        */
        static CAknCompaGSModel* NewL();

        /**
        * Destructor
        */
        ~CAknCompaGSModel();

    public: // new ones

        /**
        * Retrieve compa-mode feature enabled status
        */
        TBool FeatureEnabled();

        /**
        * Retrieve setting state
        */
        TBool CompaAppState();
        
        /**
        * Store setting state
        */
        void SetCompaAppState(TBool aState);

    private: // Private constructors
        /**
        * Default C++ contructor
        */
        CAknCompaGSModel();

        /**
        * Symbian OS default constructor
        * @return void
        */
        void ConstructL();

    private:
        TInt iFeatures;
        TInt iSettings;
        CRepository* iRepository;
    };

#endif //AKNCOMPAGSMODEL_H

// End of File
