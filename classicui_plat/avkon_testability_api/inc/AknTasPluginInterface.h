/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Avkon testability ECom plugin interface definition.
*
*/


#ifndef __AKNTASPLUGININTERFACE_H__
#define __AKNTASPLUGININTERFACE_H__

// INCLUDES
#include <e32base.h>
#include <ecom/ecom.h>

// CONSTANTS
const static TUid KAknTasPluginInterfaceUid = { 0x20018449 };
const static TUid KAknTasPluginImplementationUid = { 0x2001844A };

// MACROS

// DATA TYPES

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS
class CAknTasHook;
class RWindowGroup;
class CCoeControl;
class MTasObject;
class CFont;
class TMargins;

// CLASS DECLARATION
/**
*  Avkon testability ECom plugin interface definition class.
*  It provides ECom interface instantiation and destruction as well as the 
*  interface for services it provides. The concrete implementations are 
*  defined in inherited classes.
*/
class CAknTasPluginInterface : public CBase
    {
    public:
        
        /**
         * @brief Two-phased constructor. 
         *
         * Creates an instance of a CAknTasPluginInterface implementation. ECom
         * framework is used in finding and creating the suitable 
         * implementation. 
         *
         * @return A new instance of a CAknTasPluginInterface implementation
         */ 
        static CAknTasPluginInterface* NewL();
    
        /**
         * @brief Destructor.
         */
        virtual ~CAknTasPluginInterface();
        
        // Interface methods
        
        /**
         * @brief Set the TAS Hook singleton from the owning application. 
         *
         * Interface for providing the Avkon TAS Hook singleton from the 
         * owning application. A pointer is used but the OWNERSHIP IS NOT 
         * TRANSFERRED, the plugin will only use it to get Avkon specific 
         * object data from the TAS Hook component.
         * 
         * Abstract function, must be implemented in derived classes.
         *
         * @param aHooks TAS Hook singleton from the owning application
         */
        virtual void SetHookInterfaceL( CAknTasHook* aHooks ) = 0;
        
        /**
         * @brief Examines a control's visibility on the device screen.
         *
         * Interface for examining single control visibility on the
         * device screen. The control's or its parent's owning window's 
         * position and relation to other windows of the same window
         * group are used to determine the visibility.
         * 
         * Abstract function, must be implemented in derived classes.
         *
         * @return ETrue if the control is really visible, EFalse if not
         * @param aControl The examined control
         */
        virtual TBool IsControlVisible( CCoeControl& aControl ) = 0;
        
        /**
         * @brief Function to check the sanity of the object. 
         *
         * Functionality to check whether this object is visible or not 
         * or otherwise such that it need to be discarded.           
         * 
         * Abstract function, must be implemented in derived classes.
         *         
         * @param aControl The examined control
         * 
         * @return ETrue if the object should be included in traversal, EFalse otherwise
         */
        virtual TBool CheckSanityL( CCoeControl* aControl ) = 0;
        
        /**
         * @brief Adds the object header info into TasModel. 
         *
         * Adds new child under father object and writes out the header information.           
         * 
         * Abstract function, must be implemented in derived classes.
         *         
         * @param aObjPtr Pointer to the object to be traversed
         * @param aClassName Implementation class name for the object to be traversed
         * @param aType Type of the object to be traversed
         * @param aFather Father object of the object to be traversed
         * 
         * @return ETrue if the object should be included in traversal, EFalse otherwise
         */
        virtual MTasObject& AddHeaderL( TAny* aObjPtr, const TDesC& aClassName, const TDesC& aType, MTasObject& aFather ) = 0;        
        
        /**
         * Convert boolean into string value.
         * 
         * Abstract function, must be implemented in derived classes.
         *         
         */
        virtual const TDesC& BooleanToString( TBool aBoolean ) = 0;
        
        /**
        * Add common coecontrol details to a tas data object
        */
        virtual void AddCommonCoeInfoL( CCoeControl* aObjPtr, MTasObject& aObjectInfo )= 0;
        
        /**
        * Travereses font object and adds the details to the given parent tas object.
        *
        * @param aFont CFont object to traverse
        * @param aTasParent TasModel parent object to add the traverse details to.          
        */
        virtual void AddFontL(const CFont* aFont, MTasObject& aTasParent)= 0 ;
        
        /**
         * Travereses font object and adds the details to the given parent tas object.
         *
         * @param aMargins TMargins to traverse
         * @param aTasParent TasModel parent object to add the traverse details to.          
         */
        virtual void AddMarginsL(TMargins aMargins, MTasObject& aTasParent)= 0 ;    

    private: // Data
        
        /// Current instance identifier
        TUid iImplementation;
        
    };

#include <AknTasPluginInterface.inl>

#endif // __AKNTASPLUGININTERFACE_H__

// End of File
