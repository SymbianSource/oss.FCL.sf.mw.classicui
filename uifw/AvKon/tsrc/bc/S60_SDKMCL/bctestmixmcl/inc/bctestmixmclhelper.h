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
* Description:  declaration of helper classes
*
*/


#ifndef BCTESTMIXMCLHELPER_H
#define BCTESTMIXMCLHELPER_H

#include <hwrmhaptics.h>

#include "bctestcase.h"

/**
*  helper class for testing CHWRMHaptics
*/
class CBCTestHWRMHapticsHelperActiveObject : public CActive
	{
public:
    /**
     * C++ constructor
     */
	static CBCTestHWRMHapticsHelperActiveObject* NewL(
			CBCTestCase* aTestCase )
		{
		CBCTestHWRMHapticsHelperActiveObject* self = 
			new (ELeave) CBCTestHWRMHapticsHelperActiveObject();
		CleanupStack::PushL( self );
		self->ConstructL( aTestCase );
		CleanupStack::Pop( self );
		return self;
		}
	
    /**
     * C++ destructor
     */
	~CBCTestHWRMHapticsHelperActiveObject()
		{
		Cancel();
		delete iHaptics;
		}

	/*
	 * Generate a request and set the status as Active.
	 */
	void StartTestL()
		{
		iHaptics = CHWRMHaptics::NewL( NULL, NULL, iStatus );
		SetActive();
		}
	
protected:
	
	void RunL()
		{
		_LIT( KNewL2, "CHWRMHaptics::NewL() 3 parameters" );
		
		if ( iStatus.Int() == KErrNone )
			{
			iTestCase->AssertNotNullL( iHaptics, KNewL2 );
			}
		else
			{
			iTestCase->AssertNotNullL( NULL, KNewL2 );
			}
		}
	/*
	 * Cancellation of the outstanding request.
	 */
	void DoCancel()
		{
	    
		}
	
	/*
	 * Cope with errors
	 */
	TInt RunError( TInt /* aError */ )
		{
		return KErrNone;
		}
	
private:
    /**
     * default constructor
     */
	CBCTestHWRMHapticsHelperActiveObject() 
			: CActive( CActive::EPriorityStandard )
		{ 
		CActiveScheduler::Add( this );
		}
	
    /**
     * symbian second-phase constructor
     */
	void ConstructL( CBCTestCase* aTestCase ) 
		{
		iHaptics = NULL;
		iTestCase = aTestCase;
		}
	
	/*
	 * pointer to haptics instance
	 * owned.
	 */
	CHWRMHaptics* iHaptics;
	
	/*
	 * pointer to case
	 * not owned.
	 */
	CBCTestCase* iTestCase;
	};
#endif /*BCTESTMIXMCLHELPER_H*/
