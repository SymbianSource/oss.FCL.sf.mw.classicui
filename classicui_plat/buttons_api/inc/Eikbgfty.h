/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Button group factory interface definitions.
*
*/


#ifndef __EIKBGFTY_H__
#define __EIKBGFTY_H__

#include <eikbtgpc.h>
#include <coemain.h>

/**
 * The EikButtonGroupFactory class provides an interface to the button group factory.
 *
 * @lib eikcoctl.lib
 * @since S60 0.9
 */ 
class EikButtonGroupFactory
    {
public:
    /**
     * Defines information required to create a button group.
     *
     * @lib eikcoctl.lib
     */
    class TCreationData
        {
    public:
        /**
         * Constructor taking arguments required to create a button group.
         *
         * @param aUse The type of button group container.
         * @param aCommandObserver A command observer to be notified of commands on the container.
         * @param aResourceId A resource containing descriptions of buttons in the group. 
         *                    This can be NULL if buttons are to be added dynamically. 
         * @param aParentWg Parent window group.
         * @param aFlags The button group's flags.
         * @param aOrientation The button group's containers orientation. You need specify this 
         *                     only for devices that can layout their buttons either horizontally 
         *                     or vertically. 
         */
        IMPORT_C TCreationData(
            CEikButtonGroupContainer::TUse aUse,
            MEikCommandObserver* aCommandObserver,
            TInt aResourceId, 
            RWindowGroup* aParentWg, 
            TUint aFlags,
            CEikButtonGroupContainer::TOrientation aOrientation);
    public:
        /**
         * Container use type.
         *
         * This member is used to specify to the system the general type of the button group that
         * is required. The system then creates the appropriate button group for the specified type. 
         */
        CEikButtonGroupContainer::TUse iUse;
        
        /**
         * The command observer to be notified of commands on the container. 
         * Not owned.
         */        
        MEikCommandObserver* iCommandObserver;
        
        /**
         * A resource containing descriptions of buttons in the group.
         */
        TInt iResourceId;
        
        /**
         * Parent window group.
         * Not owned.
         */        
        RWindowGroup* iParentWg;
        
        /**
         * Flags for the button group.
         */
        TUint iFlags;
        
        /**
         * Orientation of the new button group.
         */
        CEikButtonGroupContainer::TOrientation iOrientation;
        };
        
public:
    /**
     * Creates a button group of given type if it exists in any registered button group
     * factory function.
     *
     * @param aButtonGroupType The type of button group to be created.
     * @param aCreationData Required extra information.
     * @param aAddToButtonGroupStack Whether to add the button group to the button group stack.
     * @return A handle to the button group interface the constructed object implements. NULL 
     *         if aButtonGroupType doesn't exist in any registered button group factory function.
     */
    static MEikButtonGroup* CreateButtonGroupByTypeL(
        TInt aButtonGroupType,
        TCreationData& aCreationData,
        TBool& aAddToButtonGroupStack);
    };

/**
 * Pointer to a button group factory function is defined as a pointer to a MEikButtonGroup object.
 */
typedef MEikButtonGroup* (*TCreateButtonGroupByTypeFunction)(
    TInt, 
    EikButtonGroupFactory::TCreationData&, 
    TBool&);

/**
 * Array storing the button group factory functions.
 *
 * The CEikButtonGroupFactoryArray class actually stores the button group factory functions
 * which are registered. It also provides facility to add and remove these functions from
 * the storage array. Notably this class is CCoeStatic derived, allowing application wide
 * access.
 *
 * @lib eikcoctl.lib
 * @since S60 0.9 
 */
NONSHARABLE_CLASS(CEikButtonGroupFactoryArray) : public CCoeStatic
    {
public:
    /**
     * Adds a button group factory function to the array.
     *
     * @param aCreateButtonGroupByTypeFunction The factory function to be added.
     */
    IMPORT_C static void AppendFactoryFunctionL(
        TCreateButtonGroupByTypeFunction aCreateButtonGroupByTypeFunction);
        
    /**
     * Removes a button group factory function from the array.
     *
     * @param aCreateButtonGroupByTypeFunction The factory function to be removed.
     */        
    IMPORT_C static void RemoveFactoryFunction(
        TCreateButtonGroupByTypeFunction aCreateButtonGroupByTypeFunction);

    /**
     * Returns the array of pointers to the registered button group factory creation methods.
     *
     * @return The array of button group factory functions.
     */
    static CArrayFixFlat<TCreateButtonGroupByTypeFunction>* ButtonGroupFactoryFuncArray();

    /**
     * Destructor.
     */
    ~CEikButtonGroupFactoryArray();

private:
    inline CEikButtonGroupFactoryArray();
    inline static CEikButtonGroupFactoryArray* Self();
    
private: // data    
    CArrayFixFlat<TCreateButtonGroupByTypeFunction>* iButtonGroupFactoryFuncArray;
    };

#endif // __EIKBGFTY_H__
