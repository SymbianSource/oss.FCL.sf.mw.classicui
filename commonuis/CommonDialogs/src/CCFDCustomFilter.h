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
* Description:  Custom filter for file selection dialog.
*
*/


#ifndef CCFDCUSTOMFILTER_H
#define CCFDCUSTOMFILTER_H

//  INCLUDES
#include <e32base.h>
#include <MAknFileFilter.h>

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;

// CLASS DECLARATION

/**
*  A dummy custom filter class which can be used to give ownership 
*  to file selection model without deleting client filter object.
*
*  @lib CommonDialogs.lib
*  @since 2.0
*/
NONSHARABLE_CLASS(CCFDCustomFilter) : public CBase, public MAknFileFilter
    {
    public:  // Constructors and destructor
        
        CCFDCustomFilter( MAknFileFilter* aFilter );
		~CCFDCustomFilter();

    private:  // Functions from base classes

		/**
		* From MAknFileFilter.
		*/
        TBool Accept( const TDesC& aDriveAndPath, const TEntry& aEntry ) const;

    private:    // Data

		// Ref: A pointer to filter
        MAknFileFilter* iFilter;

    };

#endif      // CCFDCUSTOMFILTER_H   
            
// End of File
