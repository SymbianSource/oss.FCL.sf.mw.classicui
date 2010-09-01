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
* Description:  Psln document class definition.
*
*/


#ifndef C_PSLNDOCUMENT_H
#define C_PSLNDOCUMENT_H

#include <AknDoc.h>

class CEikAppUi;

/**
 *  CPslnDocument class.
 *
 *  Psln document class definition.
 *
 *  @since S60 v2.0
 */
class CPslnDocument : public CAknDocument
    {

public:

    /**
    * Two-phased constructor.
    * @param aApp Application.
    * @return new instance of CPslnDocument.
    */
    static CPslnDocument* NewL( CEikApplication& aApp );

    /**
    * Destructor.
    */
    virtual ~CPslnDocument();

private:

    /**
    * C++ constructor
    */
    CPslnDocument( CEikApplication& aApp );

    /**
    * From CEikDocument. Create Psln AppUi object.
    *
    * @return Eikon application UI.
    */
    CEikAppUi* CreateAppUiL();
    };

#endif // C_PSLNDOCUMENT_H
            
// End of File
