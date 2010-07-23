/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test protected for CEikListBoxTextEditor
*
*/

#ifndef C_TESTSDKLISTSLBTEXTEDITOR_H
#define C_TESTSDKLISTSLBTEXTEDITOR_H

#include <eiklbed.h>

class CTestSDKListsLBTextEditor : public CEikListBoxTextEditor
{
public:
    /**
     * C++ default constructor.
     *
     * @param aModel Model class of the list box.
     */
    CTestSDKListsLBTextEditor(MListBoxModel* aModel);

    /**
     * From @c MEikListBoxEditor. 
     * Deletes the editor. 
     */
    void Release();

    /**
     * Gets the list box model.
     *
     * @return MListBoxModel* Pointer to the list box model instance.
     */
    MListBoxModel* ListBoxModel();

    /**
     * Function for getting the list box item index that holds the text editor.
     *
     * @return TInt Index of the list box item that holds the text editor.
     */
    TInt ItemIndex() const;

    /**
     * This function writes the internal state of the control and its components
     * to @c aStream in debug mode. Does nothing in release mode. 
     *
     * @param aWriteStream Stream where control and its components internal 
     *                     state will be written.
     */
    void WriteInternalStateL(RWriteStream& aWriteStream) const;

};

#endif /*C_TESTSDKLISTSLBTEXTEDITOR_H*/
