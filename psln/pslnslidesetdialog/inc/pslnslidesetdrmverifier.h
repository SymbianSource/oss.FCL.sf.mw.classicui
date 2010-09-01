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
* Description:  Verifies that selected files are valid from DRM point of view.
*
*/


#ifndef C_PSLNSLIDESETDRMVERIFIER_H
#define C_PSLNSLIDESETDRMVERIFIER_H


#include <e32base.h>
#include <badesca.h>
#include <MMGFetchVerifier.h>

class CDRMHelper;

/**
 * Verifies that selected files are correct from DRM point of view.
 *
 *  @lib pslnslidesetdialog.dll
 *  @since S60 3.2
*/
NONSHARABLE_CLASS( CPslnSlideSetDRMVerifier ) : 
    public CBase, public MMGFetchVerifier
    {
public:

    /**
    * Two-phased constructor.
    * @param aType type of dialog.
    * @return new instance of CPslnSlideSetDRMVerifier.
    */
    static CPslnSlideSetDRMVerifier* NewL( TInt aType );

    /**
    * Destructor.
    */
    ~CPslnSlideSetDRMVerifier();

    /**
    * From MFLDFileObserver.
    */
    TBool VerifySelectionL( const MDesCArray* aSelectedFiles );

private:

    // Shows error note.
    void ShowErrorNoteL( TInt  aResourceId  ) const;

    /**
    * C++ constructor.
    */
    CPslnSlideSetDRMVerifier(  TInt aType  );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

private:    // Data
    
    /**
    * DRM helper.
    * Own.
    */
    CDRMHelper* iDRMHelper;

    /**
    * Type of slide set (wallpaper / screensaver).
    */
    TInt iType;
    };


#endif // C_PSLNSLIDESETDRMVERIFIER_H
