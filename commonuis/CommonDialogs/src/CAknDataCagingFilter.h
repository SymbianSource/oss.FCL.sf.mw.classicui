/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Filter system directories according data caging
*
*/


#ifndef C_CAKNDATACAGINGFILTER_H
#define C_CAKNDATACAGINGFILTER_H

#include <e32base.h>
#include <MAknFileFilter.h>

class TEntry;

/**
*  A filter class that checks if a file or a folder name matches
*  with the data caging items.
*
*  @lib CommonDialogs.lib
*  @since S60 3.1
*/
NONSHARABLE_CLASS(CAknDataCagingFilter) : public CBase, public MAknFileFilter
    {

public:     
    
// Constructors and destructors

    /**
     * Static constructor, leaves a pointer to itself to the cleanup stack.
     * 
     */
    static CAknDataCagingFilter* NewLC();

    ~CAknDataCagingFilter();

// from base class MAknFileFilter

    /**
     * Described in MAknFileFilter
     */
    TBool Accept( const TDesC& aDriveAndPath, const TEntry& aEntry ) const;

private:

// Constructors and destructors

    CAknDataCagingFilter();
    void ConstructL();

    /**
     * Extract the most highest level directory from a path
     * @param aPath the input path descriptor
     * @param aResult the output descriptor to hold the extracted result
     * @return the Result descriptor reference
     */
    TDesC& ExtractRoot(const TDesC& aPath, TDes& aResult);

private: // Data

    CDesCArray*     iCagingList;    //Own
    };

#endif // C_CAKNDATACAGINGFILTER_H

