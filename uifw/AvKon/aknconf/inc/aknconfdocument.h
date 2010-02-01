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
* Description:  Declares document class for application.
 *
*/


#ifndef __AKNCONFDOCUMENT_H__
#define __AKNCONFDOCUMENT_H__

// INCLUDES
#include <AknDoc.h>

// FORWARD DECLARATIONS
class CAknConfAppUi;
class CEikApplication;

// CLASS DECLARATION

/**
 * CAknConfDocument application class.
 * An instance of class CAknConfDocument is the Document part of the
 * AVKON application framework for the aknconf example application.
 */
class CAknConfDocument : public CAknDocument
    {
public:
    // Constructors and destructor

    /**
     * NewL.
     * Two-phased constructor.
     * Construct a CAknConfDocument for the AVKON application aApp
     * using two phase construction, and return a pointer
     * to the created object.
     * @param aApp Application creating this document.
     * @return A pointer to the created instance of CAknConfDocument.
     */
    static CAknConfDocument* NewL(CEikApplication& aApp);

    /**
     * NewLC.
     * Two-phased constructor.
     * Construct a CAknConfDocument for the AVKON application aApp
     * using two phase construction, and return a pointer
     * to the created object.
     * @param aApp Application creating this document.
     * @return A pointer to the created instance of CAknConfDocument.
     */
    static CAknConfDocument* NewLC(CEikApplication& aApp);

    /**
     * ~CAknConfDocument
     * Virtual Destructor.
     */
    virtual ~CAknConfDocument();

public:
    // Functions from base classes

    /**
     * CreateAppUiL
     * From CEikDocument, CreateAppUiL.
     * Create a CAknConfAppUi object and return a pointer to it.
     * The object returned is owned by the Uikon framework.
     * @return Pointer to created instance of AppUi.
     */
    CEikAppUi* CreateAppUiL();

private:
    // Constructors

    /**
     * ConstructL
     * 2nd phase constructor.
     */
    void ConstructL();

    /**
     * CAknConfDocument.
     * C++ default constructor.
     * @param aApp Application creating this document.
     */
    CAknConfDocument(CEikApplication& aApp);

    };

#endif // __AKNCONFDOCUMENT_H__
// End of File
