/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Declares test bc for labelinfoindicators document.
*
*/









#ifndef C_CBCTESTLABELINFOINDICATORSDOCUMENT_H
#define C_CBCTESTLABELINFOINDICATORSDOCUMENT_H

#include <eikdoc.h>

class  CEikAppUi;

/**
* CBCTestLabelInfoIndicatorsDocument application class.
*/
class CBCTestLabelInfoIndicatorsDocument : public CEikDocument
    {
public: // Constructors and destructor

    /**
    * Symbian OS two-phased constructor.
    * @return Pointer to created Document class object.
    * @param aApp Reference to Application class object.
    */
    static CBCTestLabelInfoIndicatorsDocument* NewL( CEikApplication& aApp );

    /**
    * Destructor.
    */
    virtual ~CBCTestLabelInfoIndicatorsDocument();

private: // Constructors

    /**
    * Overload constructor.
    * @param aApp Reference to Application class object.
    */
    CBCTestLabelInfoIndicatorsDocument( CEikApplication& aApp );

// From CEikDocument

    /**
    * From CEikDocument, CreateAppUiL.
    * Creates CBCTestLabelInfoIndicatorsAppUi "App UI" object.
    * @return Pointer to created AppUi class object.
    */
    CEikAppUi* CreateAppUiL();

};

#endif  // C_CBCTESTLABELINFOINDICATORSDOCUMENT_H
