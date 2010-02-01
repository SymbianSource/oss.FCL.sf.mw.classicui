/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Plugin utility used for automatic tags ( http, email, phone numbers )
*                syntax highlighting in text viewers
*
*
*/



#ifndef ITEMFINDER_H
#define ITEMFINDER_H

// INCLUDES
#include <mparser.h>                       // for MParser

// CONSTANTS

// FORWARD DECLARATIONS
class CEikRichTextEditor;
class CFindItemEngine;
class CItemFinderAsyncParser;
class CSchemeResolver;
class CFindItemEngine;

// CLASS DECLARATION
class MItemFinderObserver
    {
    public:
        virtual void HandleParsingComplete() = 0;
    };

/**
* Parser plugin
*/
NONSHARABLE_CLASS(CItemFinder) :
    public CBase,
    public MParser
    {
    public:  // Constructors and destructor

        /**
        * Destructor.
        */
        ~CItemFinder();

    public: // definitions
    
        enum TItemType
            {
            ENoneSelected = 0,
            EUrlAddress = 1,
            EEmailAddress = 2,
            EPhoneNumber = 4,
            EUriScheme =8
            };

        enum TFindDirection
            {
            EInit = 0,
            ENextDown = 1,
            ENextUp = 2,
            EInitDown = 3,
            EInitUp = 4
            };

        /*class CFindItemDef: public CBase // @deprecated since 3.2
            {
            public:
                ~CFindItemDef(){ if ( iItemDescriptor ) delete iItemDescriptor; }
                TItemType iItemType;
                HBufC* iItemDescriptor;
                TInt iDisplayLength;
            };*/

        class CFindItemExt: public CBase // replaces CFindItemDef.
            {
            public:
                IMPORT_C ~CFindItemExt();// { if ( iItemDescriptor ) delete iItemDescriptor; }
                TItemType iItemType;
                HBufC* iItemDescriptor;
                TInt iStart;
                TInt iEnd;
            };

    public: // New functions
        /**
        * @since Series 60 2.6
        * Creates instance of ItemFinder and adds it to editor parser list (TLS)
        * Must be called before editor creation in order to have effect
        *
        * @param    aFindFlags   Find mode ( defaults to all )
        * @return                New instance
        */
        IMPORT_C static CItemFinder* NewL( TInt aFindFlags = EUrlAddress|EEmailAddress|EPhoneNumber );

        /**
        * @since Series 60 2.6
        * Notify item finder to move focus to next item or scroll display
        *
        * @param    aDirection   Direction ( ENextDown or ENextUp )
        * @return                EFalse if command had no effect, ETrue otherwise
        */
        IMPORT_C TBool NextItemOrScrollL( TFindDirection aDirection );

        /**
        * @since Series 60 2.6
        * Sets the find mode, can be used for initialize parsers for current position after eg screen size change
        * Refreshes parser data if editor and text set.
        *
        * @param    aFindFlags      Any combination of (EUrlAddress|EEmailAddress|EPhoneNumber)
        */
        IMPORT_C void SetFindModeL( TInt aFindFlags );

        /**
        * @since Series 60 2.6
        * Set pointer to applications instance of CEikRichTextEditor.
        * If editor is not set, all methods return immediately
        * Editor should have texts installed when application sets the pointer
        * Refreshes parser data if text is set.
        *
        * @param    aEditor Pointer array pointing applications editor instance
        */
        IMPORT_C void SetEditor( CEikRichTextEditor** aEditor );

    public: // From MParser

        IMPORT_C TBool ParseThisText(
            const CRichText& aTextObj,
            TBool aAllowBack,
            TInt aStartScan,
            TInt aScanLength,
            TInt& aStartTag,
            TInt& aTagLength );

        IMPORT_C const TDesC& CreateDoItText(
            const CRichText& aTextObj,
            TInt aStartText,
            TInt aLength );

        IMPORT_C void ActivateThisTextL(
            const CRichText& aTextObj,
            TInt aStartText,
            TInt aLength );

        IMPORT_C TBool ReformatOnRecognise() const;

        IMPORT_C TBool ReformatOnRollover() const;

        IMPORT_C void GetRecogniseFormat( TCharFormat& aFormat );

        IMPORT_C void GetRolloverFormat( TCharFormat& aFormat );

        IMPORT_C TBool ConfirmCursorOverTag(
            const CRichText& aTextObj,
            TInt aTagStart,
            TInt aTagLen,
            TInt aCurPos );

        IMPORT_C void Release();

        IMPORT_C void MParser_Reserved_2();

    public: // new methods
        /**
        * @since Series 60 2.6
        * Returns document position of next item in given direction.
        * Needed if application wants to control the scrolling and
        * NextItemOrScrollL() is thus not suitable.
        *
        * @param    aDirection   Direction ( ENextDown or ENextUp )
        * @return                Start position of next tag, KErrNotFound if
        *                        no tag found from given direction
        */
        IMPORT_C TInt PositionOfNextItem( TFindDirection aDirection );

        /**
        * @since Series 60 2.6
        * Deletes current item descriptor and sets type to ENoneSelected
        */
        IMPORT_C void ResetCurrentItem();

        /**
        * @since Series 60 2.6
        *
        * Creates item descriptor starting from aStart and sets the item type
        * to CurrentItem().iItemType, if default value is not overridden
        * uses internal members to resolve type.
        * Method does NOT any formatting to editor.
        *
        * @param    aStart   Position from which tag to be recognized should start
        *                    Default value uses internal members
        */
        IMPORT_C void ResolveAndSetItemTypeL( TInt aStart = KErrNotFound );

        /**
        * @since Series 60 2.6
        *
        * Sets external observer (Must implement MItemFinderObserver) to which notify when parsing is completed.
        * There is no need to set an observer if ItemFinder implements scrolling in editor.
        * Must be called before SetEditor in order to have effect.
        *
        * @param    aObserver   Observer which will be notified about the praser state changes
        */
        IMPORT_C void AddObserver( MItemFinderObserver& aObserver );

        /**
        * @since Series 60 3.2
        *
        * Tells whether the point tapped inside the editor text body was hit some find item.
        * Also updates the current item selection and cursor position when necessary.
        *
        * @param    aTappedPoint Tapped point relative to the upper left point of the editor text body control.
        * @return   ETrue if some find item inside editor text body was tapped. Otherwise EFalse.
        */
        IMPORT_C TBool ItemWasTappedL( const TPoint aTappedPoint );

        /**
        * @since Series 60 3.2
        * Sets the given external links (hyperlinks) and refreshes the text buffer.
        * Validites the links by their type.
        *
        * @param    aLinks a pointer list of external link objects ordered by start position (lowest first).
        * @return   KErrNone if successfull operation, otherwise system-wide error code.
        */
        IMPORT_C TInt SetExternalLinks( CArrayPtrFlat<CFindItemExt>* aLinks );

        /**
        * @since Series 60 3.2
        * Returns reference to currently selected item, if none selected iItemType = ENoneSelected
        * Please note that method does not check whether the editor has focus or not, it will return
        * last selected item even the highlight is not visible as editor is not focused
        * Unlike CurrentItem() that contains the length, this method also contains position of the item.
        *
        * @return   currently selected item
        */
        IMPORT_C CFindItemExt& CurrentItemExt();

        /**
        * @since Series 60 3.2
        * Returns the current selection of the text buffer on the screen.
        *
        * @return   current selection of the text buffer on the screen.
        */
        IMPORT_C TPtrC CurrentSelection();

    private:

        /**
        * C++ default constructor.
        */
        CItemFinder( TInt aFindFlags );

        // utilities
        TInt EngineFlags();
        void InsertPrefixToUrl();
        TBool SchemeSupported( const TDesC& aScheme );

        TBool CallbackToExtObserver();

        /**
        * 2nd phase constructor.
        */
        void ConstructL();

        void DoResolveAndSetItemTypeL( const CFindItemExt* aItem );

        TInt MinLengthForItemType( TInt aItemType );

        TInt GetMinDigitsToFindL();

        TInt RefreshEditor();

    private:    // Data

        CEikRichTextEditor** iEditor; // Not owned
        TInt iFlags;

        CFindItemExt* iCurrentItemExt;
        CArrayPtrFlat<CFindItemExt>* iExternalLinks;

        TInt iCurrentStart;
        TInt iCurrentEnd;

        TFindDirection iPreviousDirection;
        TInt iFirstVisible;

        CItemFinderAsyncParser* iAsyncParser;

        CSchemeResolver* iSchemeResolver;

        TBool iMarkedArrayComplete;

        MItemFinderObserver* iExternalObserver; // not owned

        friend class CItemFinderAsyncParser;

        TInt iMinDigitsToFind;
    };

#endif      // ITEMFINDER_H

// End of File
