/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Declares document for application.
*
*/









#ifndef C_CBCTESTLAUNCHERDOCUMENT_H
#define C_CBCTESTLAUNCHERDOCUMENT_H

#include <akndoc.h>

class  CEikAppUi;
class  CBCTestLauncherAppUi;

/**
 *  CBCTestLauncherDocument document class.
 */
class CBCTestLauncherDocument : public CAknDocument
    {
public: // Constructors and destructor
   
    /**
    * Two-phased constructor.
    */
    static CBCTestLauncherDocument* NewL( CEikApplication& aApp );

    /**
    * Destructor.
    */
    virtual ~CBCTestLauncherDocument();

private: 
   
    /**
    * C++ default constructor.
    * @param aApp Application class
    */
    CBCTestLauncherDocument( CEikApplication& aApp );

    /**
    * Symbian 2nd phase constructor.
    */
    void ConstructL();

private:  // From CEikDocument
    
    /**
    * From CEikDocument,
    * create CBCTestLauncherAppUi "App UI" object.
    * @return A pointer to the created "App UI" object.
    */
    CEikAppUi* CreateAppUiL();

    };

#endif // C_CBCTESTLAUNCHERDOCUMENT_H

