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
* Description:     
*
*/

#ifndef HGVGITEM_H_
#define HGVGITEM_H_

// INCLUDES
#include <ganes/HgItem.h> // base class
#include <VG/openvg.h>

// FORWARD DECLARATIONS
class CGulIcon;

// CLASS DECLARATION
class CHgVgItem : public CHgItem 
    {
public:    
    
    /**
     * Creates new CHgVgItem.
     * 
     * @param aFlags Item flags. Default is EHgItemFlagsNone
     * @param aIcon Item Icon. Ownership transferred.
     * @param aTitle Title text.
     * @param aText Additional Text.
     * 
     * @return CHgVgItem-object
     */    
    IMPORT_C static CHgVgItem* NewL(TInt aFlags = EHgItemFlagsNone,
            CGulIcon* aIcon = 0,
            const TDesC& aTitle = KNullDesC,
            const TDesC& aText = KNullDesC );
    
    /**
     * @copydoc CHgVgItem::NewL
     */
    IMPORT_C static CHgVgItem* NewLC(TInt aFlags = EHgItemFlagsNone,
            CGulIcon* aIcon = 0,
            const TDesC& aTitle = KNullDesC,
            const TDesC& aText = KNullDesC);
    
    IMPORT_C virtual ~CHgVgItem();
    
public: // CHgItem
    
    IMPORT_C void SetIcon( CGulIcon* aIcon, TInt aFlags = EHgItemFlagsNone );
        
public: // METHODS
        
    /**
     * Gets OpenVG Image.
     * 
     * @return VGImage-object
     */
    VGImage VgImage() const;
    
    /**
     * Reloads openvg image resource. 
     * This is used by media wall to allocate resources on demand and should 
     * not be used externally.
     */
    void ReloadOpenVgImage();
    
    /**
     * Frees openvg image resource.
     * This is used by media wall to free resources on demand and should 
     * not be used externally.
     */
    void FreeOpenVgImage();
        
protected:
    
    CHgVgItem(TInt aFlags, CGulIcon* aIcon);

    void ConstructL( const TDesC& aTitle, const TDesC& aText );
        
private:

    VGImage iVgImage; // VGImage of this item, owns.
    };

#endif /* HGVGHELPER */
