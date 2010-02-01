/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef HGSCROLLBUFFERMANAGER_H_
#define HGSCROLLBUFFERMANAGER_H_

#include <e32base.h>
class MHgScrollBufferObserver;
class MHgBufferOwner;

NONSHARABLE_CLASS( CHgScrollBufferManager ) : public CActive
    {
public:

    static CHgScrollBufferManager* NewL( 
            MHgScrollBufferObserver& aObserver, 
            TInt aBufferSize,
            TInt aBufferTreshold,
            TInt aInitialPosition,
            TInt aTotalCount );
    
    virtual ~CHgScrollBufferManager();
    
protected: // From CActive

    void RunL();
    void DoCancel();
    TInt RunError( TInt aError );

public:
    void SetPosition( TInt aIndex );

    void ItemCountChanged( TInt aIndex, TBool aRemoved, TInt aNewTotalCount );
    
    void SetTotalCount( TInt aTotalCount );
    
    void SetBufferOwner( MHgBufferOwner& aOwner );
    
    void ResetBuffer( TInt aPosition, TInt aTotalCount);

protected:
    CHgScrollBufferManager(
            MHgScrollBufferObserver& aObserver, 
            TInt aBufferSize,
            TInt aBufferTreshold,
            TInt aInitialPosition,
            TInt aTotalCount );
    
    void ConstructL();

private:
    void NotifyObserver();
    
private:
    MHgScrollBufferObserver& iObserver; 
    MHgBufferOwner* iOwner;
    
    TInt iBufferSize;
    TInt iBufferTreshold;
    TInt iBufferPosition;
    TInt iDiff;
    TInt iTotalCount;
    
    TBool iResetOrdered;
    
    TInt iRequestStart;
    TInt iRequestCount;
    TInt iReleaseStart;
    TInt iReleaseCount;
    };

#endif /*HGSCROLLBUFFERMANAGER_H_*/
