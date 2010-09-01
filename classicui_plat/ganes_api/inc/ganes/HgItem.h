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


#ifndef HGITEM_H_
#define HGITEM_H_

#include <e32base.h>

// Forward declarations
class CGulIcon;

class CHgItem : public CBase
    {
public:
    
    /**
     * Creates new CHgItem.
     * 
     * @param aFlags Item flags. Default is EHgItemFlagsNone
     * @param aIcon Item Icon. Ownership transferred.
     * @param aTitle Title text.
     * @param aText Additional Text.
     * 
     * @return CHgItem-object
     */
    IMPORT_C static CHgItem* NewL(TInt aFlags = EHgItemFlagsNone,
            CGulIcon* aIcon = 0, 
            const TDesC& aTitle = KNullDesC,
            const TDesC& aText = KNullDesC );
    
    /**
     * @copydoc CHgItem::NewL
     */
    IMPORT_C static CHgItem* NewLC(TInt aFlags = EHgItemFlagsNone,
            CGulIcon* aIcon = 0,
            const TDesC& aTitle = KNullDesC,
            const TDesC& aText = KNullDesC);

    /**
     * Destructor.
     */
    IMPORT_C virtual ~CHgItem();

public:
    /**
     * Gets the Icon.
     * 
     * @return pointer to Icon.
     */
    IMPORT_C CGulIcon* Icon() const;

    /**
     * Gets the title text.
     * 
     * @return The title text.
     */
    IMPORT_C const TDesC& Title() const;
    
    /**
     * Gets the additional text.
     * 
     * @return The additional text.
     */
    IMPORT_C const TDesC& Text() const;
    
    /**
     * Gets time of the item.
     * 
     * @return Time.
     */
    IMPORT_C TTime Time() const;
    
    /**
     * Sets icon.
     * 
     * @param aIcon New icon. Ownership transferred.
     */
    IMPORT_C virtual void SetIcon( CGulIcon* aIcon, TInt aFlags = EHgItemFlagsNone );
    
    /**
     * Sets title text.
     * 
     * @param aTitle New title text.
     */
    IMPORT_C void SetTitleL( const TDesC& aTitle );
    
    /**
     * Sets additional text.
     * 
     * @param aTitle New additional text.
     */
    IMPORT_C void SetTextL( const TDesC& aText );

    /**
     * Sets item time.
     * 
     * @param aTime Time.
     */
    IMPORT_C void SetTime( TTime aTime );

    /**
     * Gets flags associated with item.
     * @see THgItemFlags
     */
    IMPORT_C TInt Flags();

    
public:

    /**
     * Item flags.
     */
    enum THgItemFlags
        {
        EHgItemFlagsNone = 0,
        EHgItemFlagMarked = 0x0001,
        EHgItemFlagsDrmRightsValid = 0x0002,
        EHgItemFlagsDrmRightsExpired = 0x0004,
        EHgItemFlagsVideo = 0x0008,
        EHgItemFlagsMmc = 0x0010,
        EHgItemFlagsPlaybackIndicator = 0x0020,        
        EHgItemFlagsPauseIndicator = 0x0040,        
        EHgItemFlagsBrokenPlaylistIndicator = 0x0080,        
        EHgItemFlagsBrokenTrackIndicator = 0x0100,        
        EHgItemFlagsCorruptedTrackIndicator = 0x0200,
        EHgItemFlagsNewVideoIndicator = 0x0400,
        EHgItemFlagsMassStorageIndicator = 0x0800,
        EHgItemFlagsPhoneStorageIndicator = 0x1000,
        EHgItemFlagsNewPodcastIndicator = 0x2000,
        EHgItemFlagsPlayedPodcastIndicator = 0x4000,
        EHgItemFlagsCompletelyPlayedPodcastIndicator = 0x8000,
        EHgItemFlagsMoveUpIndicator = 0x10000,
        EHgItemFlagsMoveDownIndicator = 0x20000,
        EHgItemFlagsMoveUpDownIndicator = 0x40000,
        EHgItemFlagsIconOverlayIndicator = 0x80000000
        };

    /**
     * Sets item flags.
     * 
     * @param aFlags Flags to be set.
     */
    IMPORT_C void SetFlags( TInt aFlags );
        
    /**
     * Clears item flags.
     * 
     * @param aFlags Flags to be cleared.
     */
    IMPORT_C void ClearFlags( TInt aFlags );
    
protected:
    
    CHgItem( TInt aFlags, CGulIcon* aIcon );
    virtual void ConstructL( const TDesC& aTitle, const TDesC& aText );
    
protected:
    
    CGulIcon* iIcon; // Item icon. Own
    HBufC* iTitle; // Item title. Own
    HBufC* iText; // Item text. Own
    TTime iTime; // Item time
    
    TInt iFlags; // Item flags 
    
    };

#endif /*HGITEM_H_*/
