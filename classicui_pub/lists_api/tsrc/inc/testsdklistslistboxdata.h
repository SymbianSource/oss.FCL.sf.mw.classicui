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
* Description:  test protected for CListBoxData
*
*/

#ifndef C_TESTSDKLISTSLISTBOXDATA_H
#define C_TESTSDKLISTSLISTBOXDATA_H

#include <eiklbd.h>

class CTestSDKListsListBoxData : public CListBoxData
{
public:
    /**
     * test SetSkinBackgroundControlContextL(MAknsControlContext* aContext)
     * Sets a background skinning context. Set @c NULL to disable background
     * skinning.
     *
     * @since Series 60 2.0
     * @param aContext Background skinning context.
     */
    void TestSetSkinBackgroundControlContextL(MAknsControlContext* aContext);

    /**
     * test SetSkinEnabledL(TBool aEnabled)
     * Sets whether skins are enabled.
     *
     * @param aEnabled @c EFalse disable skinning, @c ETrue enable
     */
    void TestSetSkinEnabledL(TBool aEnabled);

    /**
     * test ConstructFontL(const CFont* aBaseFont, 
                                 TFontStyle aFontStyle, 
                                 CFontsWithStyle& aFonts)
     * Constructs a new font based on the base font and font style given.
     * Constructed font is added to @c CFontsWithStyle.
     *
     * @param aBaseFont Base fontused in construction
     * @param aFontStyle A new font's style
     * @param aFonts New font is added to this font container.
     */
    void TestConstructFontL(const CFont* aBaseFont);

    /**
     * test UpdateFontBoundValues(const CFont& aFont)
     * Updates width and heigh information. Used when font is changed. 
     *
     * @param aFont A font from which bound values are taken.
     */
    void TestUpdateFontBoundValues(const CFont* aFont);
    
    /**
     * test RegenerateFonts(CFontsWithStyle& aFonts,
                                  TInt aFontHeightInTwips)
     * Changes fonts' height. Takes new height as argument and regenerates 
     * font set so that height is modified.
     *
     * @param aFonts Font set to modify
     * @param aFontHeightInTwips New font height
     */
    TInt TestRegenerateFonts();

    // the follow functions test class CFontsWithStyle
    /**
     * test void ReleaseFonts()
     * Releases fonts when they are no longer required.
     */
    void TestReleaseFonts();

    /**
     * test TFontStyle FontStyle()
     * Getter for used font style
     * 
     * @return TFontStyle Used font style
     */
    void TestFontStyle();

    /**
     * test void SetFontStyle(TFontStyle aFontStyle)
     * Setter for used font style
     *
     * @return aFontStyle Font style to use.
     */
    TBool TestSetFontStyle();

};

#endif /*C_TESTSDKLISTSLISTBOXDATA_H*/
