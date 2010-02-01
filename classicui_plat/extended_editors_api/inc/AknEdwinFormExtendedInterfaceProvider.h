/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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


#if !defined(__AKNEDWINFORMEXTENDEDINTERFACE_H__)
#define __AKNEDWINFORMEXTENDEDINTERFACE_H__

#include <inlinetext.h>
#include <frmtlay.h>

class CAknCompositeInlineTextSource;

NONSHARABLE_CLASS(CAknEdwinFormExtendedInterfaceProvider): public CBase, public MFormCustomInterfaceProvider
    {
public: // 2-stage constructor and the destructor
    IMPORT_C static CAknEdwinFormExtendedInterfaceProvider* NewL();
    ~CAknEdwinFormExtendedInterfaceProvider();

public: // new methods
    /**
    * Access method to the inline text source implementation
    */
    IMPORT_C CAknCompositeInlineTextSource& CompositeInlineTextSource() const;

public: // From MFormCustomInterfaceProvider
    // Documented in header
    TAny* GetExtendedInterface(const TUid& aInterfaceId);

private:
    /**
    * Private constructor
    */
    CAknEdwinFormExtendedInterfaceProvider();

    /**
    * 2nd state construction
    */
    void ConstructL();

private:
    CAknCompositeInlineTextSource* iCompositeInlineTextSource; // Owned
    };

#endif // __AKNEDWINFORMEXTENDEDINTERFACE_H__

