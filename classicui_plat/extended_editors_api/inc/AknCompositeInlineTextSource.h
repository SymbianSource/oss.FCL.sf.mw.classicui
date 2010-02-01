/*
* Copyright (c) 2003 Nokia Corporation and/or its subsidiary(-ies).
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
*     Classes used combining several MTmInlineTextSource interfaces into one.
*
*/


#ifndef AKNCOMPOSITEINLINETEXTSOURCE_H
#define AKNCOMPOSITEINLINETEXTSOURCE_H

// INCLUDES
#include "AknInlineText.h"

// CONSTANTS

// CLASS DECLARATION

// This array holds all the individual implementations of CAknInlineTextSource
typedef CArrayPtrFlat<CAknInlineTextSource> CAknInlineTextSourceArray;

/**
* This class is the implementation of MFormInlineTextSource that is actually accessed by 
* Tagma. It delegates its functionality to the installed formatters
*/
NONSHARABLE_CLASS(CAknCompositeInlineTextSource) : public CAknInlineTextSource
    {
public: // 2-stage constructor and the destructor
    static CAknCompositeInlineTextSource* NewL();
    ~CAknCompositeInlineTextSource();

public:
    /**
    * Adds the inline text source to the array.  Ownership is taken by this object
    *
    * @param    aNewSource  formatter to add
    */
    IMPORT_C void InstallInlineTextSourceL( CAknInlineTextSource* aNewSource);

public: // From MTmInlineTextSource. Documented in header

	virtual TInt GetNextInlineTextPosition(const TTmDocPos& aFrom, TInt aMaxLength, TTmDocPos& aNext);
	virtual TPtrC GetInlineText(const TTmDocPos& aAt);

public: // From CAknInlineTextSource
    /**
    * See AknInlineText.h
    */
    virtual void CheckFormattingL(const TTmDocPos& aFrom, const TTmDocPos& aTo);

public: // From MEditObserver
    /**
    * See Medobsrv.h
    */
	virtual void EditObserver(TInt aStart, TInt aExtent);

private:
    /**
    * Private constructor
    */ 
    CAknCompositeInlineTextSource();

    /**
    * 2nd stage construction
    */
    void ConstructL();

private:
    CAknInlineTextSourceArray* iInlineTextSourceArray;
    };

#endif

// End of File
