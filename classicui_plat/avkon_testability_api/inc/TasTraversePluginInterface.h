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
* Description:  Avkon TAS default control traverse ECOM plugin interface definition.
*
*/

#ifndef TASTRAVERSEPLUGININTERFACE_H_
#define TASTRAVERSEPLUGININTERFACE_H_

// INCLUDES
#include <e32base.h>
#include <ecom/ecom.h>
#include <e32hashtab.h>

// FORWARD DECLARATIONS
class CAknTasPluginInterface;

// CONSTANTS
const static TUid KTasTraversePluginInterfaceUid = { 0x2002A4F2 };

// MACROS

// DATA TYPES

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS
class MTasObject;

// CLASS DECLARATION

/**
*  Avkon traverse ECom plugin interface definition class.
*  It provides ECom interface instantiation and destruction as well as the 
*  interface for services it provides. The concrete implementations are 
*  defined in inherited classes.
*/
class CTasTraversePluginInterface : public CBase
    {
    public:
        
        /**
          * @brief Two-phased constructor. 
          *
          * Creates an instance of a CTasTraversePluginInterface implementation.
          * ECom framework is used in finding and creating the suitable 
          * implementation by its name. 
          *
          * @return A new instance of a CTasTraversePluginInterface implementation
          */ 
         static CTasTraversePluginInterface* NewL( const TDesC8& aTraverseObjectName, CAknTasPluginInterface * aAknTasPluginInterface );
    
        /**
         * @brief Destructor.
         */
        virtual ~CTasTraversePluginInterface();
        
        
    public:

        /**
         * @brief Traverse method for traversing the UI object. 
         *
         * Reads the UI object information using aPbjectPtr.
         * Writes the information into tasObject enabling XML format exports in the upper levels.         
         *
         * @param tasObject Father object under which the new object is created
         * @param aObjectPtr Pointer to the object to be traversed
         * @return void
         */ 
        virtual void TraverseL(MTasObject& tasObject, TAny* aObjectPtr) = 0;
        
    protected:
        CAknTasPluginInterface * iAknTasPluginInterface;
        TPtrC8  iAknTasTraverseObjectName;

    private: // Data
        
        /// Current instance identifier
        TUid iImplementation;
        
    };

#include <TasTraversePluginInterface.inl>

#endif /* TASTRAVERSEPLUGININTERFACE_H_ */
