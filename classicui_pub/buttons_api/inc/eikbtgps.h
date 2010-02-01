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
* Description:  Button group stack class definition.
*
*/


#ifndef __EIKBTGPS_H__
#define __EIKBTGPS_H__

#include <coemain.h>
#include <eikbtgpc.h>

/**
 * A list of all button groups currently available within a thread. 
 * 
 * CEikButtonGroupStack maintains a list of all button groups currently 
 * available within a thread. Only button groups that are expected to be 
 * available to other controls will register here.
 *
 * @lib eikcoctl.lib
 * @since S60 0.9 
 */
class CEikButtonGroupStack : public CCoeStatic
    {
public:
    /**
     * Gets the minimum size required to display all the visible button 
     * groups on the button group stack.
     *
     * @return The minimum size required to display all the visible button
     *         groups currently on the stack. 
     */
    IMPORT_C static TSize MinimumSize();

    /**
     * Gets the button group currently displayed.
     *
     * @return The button group currently displayed.
     */
    static CEikButtonGroupContainer* Current();
    
    /**
     * Adds a button group to the button group stack.
     *
     * @param aGroup The button group to add to the button group stack. 
     */    
    static void AddL(CEikButtonGroupContainer& aGroup);
    
    /**
     * Removes the specified button group from the button group stack.
     *
     * @param aGroup The button group to remove.
     */    
    static void Remove(CEikButtonGroupContainer& aGroup);
    
private:
    inline CEikButtonGroupStack();
    inline static CEikButtonGroupStack* Self();
    
private: // data
    TDblQue<CEikButtonGroupContainer> iBtStack;
    };

#endif // __EIKBTGPS_H__
