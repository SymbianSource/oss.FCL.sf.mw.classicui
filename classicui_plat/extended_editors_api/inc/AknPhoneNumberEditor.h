/*
* Copyright (c) 2002 - 2005 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef AKNPHONENUMBEREDITOR_H
#define AKNPHONENUMBEREDITOR_H

#include <babitflags.h>
#include <eikbctrl.h>
#include <fepbase.h>
#include <gulutil.h>
#include <eikdef.h>
#include <eikccpu.h>
#include <baclipb.h>
#include <aknedstsobs.h>

class CEikScrollBarFrame;
class CAknPhedModel;
class CAknPhedView;
class CAknPhoneNumberEditorExtension;

class CAknPhoneNumberEditor : public CEikBorderedControl, public MCoeFepAwareTextEditor, 
    public MCoeFepAwareTextEditor_Extension1, public MEikCcpuEditor
    {
public:
    class TFormat
        {
    public:
        IMPORT_C TFormat();
        // MUST NOT BE USED; LAYOUT INFO CANNOT BE IN RESOURCES OR FACE VARIATION TROUBLE.
        IMPORT_C TFormat( TResourceReader& aReader ); 
        IMPORT_C TFormat( const TRect& aOuterRect, TInt aBorderType, TInt aNumLines, 
            TInt aBottomBaselineOffset, TInt aBaselineSeparation, const CFont* aFont );
    public:
        TRect iOuterRect;
        TInt iBorderType;
        TInt iNumLines;
        TInt iBottomBaselineOffset;
        TInt iBaselineSeparation;
        const CFont* iFont;
        };

public:
    IMPORT_C CAknPhoneNumberEditor();
    IMPORT_C ~CAknPhoneNumberEditor();
    IMPORT_C void ConstructFromResourceL( TResourceReader& aReader );
    IMPORT_C void ConstructL( TInt aMaxChars, TInt aMaxLines, 
                              TInt aMaxFormats, const TDesC& aTruncation );

    // Format manipulation functions
    IMPORT_C void AddFormat( const TFormat& aFormat );
    IMPORT_C TInt CountFormats() const;
    IMPORT_C TFormat& Format( TInt aFormatIndex ) const;
    IMPORT_C TInt CurrentFormatIndex() const;
    IMPORT_C TBool WouldTextFitInFormat( TInt aFormatIndex ) const;
    IMPORT_C void SetFormat( TInt aFormatIndex );

    // Text access functions
    IMPORT_C TPtrC Text(TInt aFrom = 0) const;
    IMPORT_C void SetText( const TDesC& aText );

    // from CCoeControl
    IMPORT_C void SizeChanged();
    IMPORT_C TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent,
                                          TEventCode aType );
    IMPORT_C TSize MinimumSize();
    IMPORT_C void FocusChanged( TDrawNow aDrawNow );
    IMPORT_C void Draw( const TRect& aRect ) const;
    IMPORT_C TCoeInputCapabilities InputCapabilities() const;

    // Edwin like interface
    IMPORT_C TInt TextLength() const;
    IMPORT_C TInt CursorPos() const;
    IMPORT_C TInt SelectionLength() const;
    IMPORT_C TCursorSelection Selection() const;
    IMPORT_C void ClearSelectionL();
    IMPORT_C void SetSelectionL( TInt aCursorPos,TInt aAnchorPos );
    IMPORT_C void SetCursorPosL( TInt aCursorPos,TBool aSelect );
    IMPORT_C void SelectAllL();
    IMPORT_C void GetText(TDes& aDes) const;
    IMPORT_C HBufC* GetTextInHBufL() const;
    IMPORT_C void SetTextL( const TDesC* aDes );
    // this is particularly important for when the front-end processor 
    // is inline-editing a CEikEdwin
    IMPORT_C void CancelFepTransaction(); 
    IMPORT_C void UpdateScrollBarsL();
    IMPORT_C CEikScrollBarFrame* CreateScrollBarFrameL();
    inline CEikScrollBarFrame* CreatePreAllocatedScrollBarFrameL();
    inline CEikScrollBarFrame* ScrollBarFrame();
    IMPORT_C virtual TInt LineCursorWidth() const;
    IMPORT_C TMargins8 Margins() const;
    IMPORT_C TInt AknEditorFlags() ;
    // Event reporting
    void StateChanged();

private:
    TInt TargetCursorPos( TInt aCurrentPos );
    void DrawChanges();
    CEikScrollBarFrame* CreateScrollBarFrameL( TBool aPreAlloc );
    void CreateFepStateL();

private: // from MCoeFepAwareTextEditor
    void StartFepInlineEditL( const TDesC& aInitialInlineText, 
             TInt aPositionOfInsertionPointInInlineText, 
             TBool aCursorVisibility, 
             const MFormCustomDraw* aCustomDraw, 
             MFepInlineTextFormatRetriever& aInlineTextFormatRetriever, 
             MFepPointerEventHandlerDuringInlineEdit& aPointerEventHandlerDuringInlineEdit );

    void UpdateFepInlineTextL( const TDesC& aNewInlineText, 
                               TInt aPositionOfInsertionPointInInlineText );

    void SetInlineEditingCursorVisibilityL( TBool aCursorVisibility );
    void CancelFepInlineEdit();
    // with regard to the behaviour of the following functions when inline editing, 
    // note that the contents of the editor will be such that the text constituting 
    // the selection immediately prior to inline editing will be replaced by the 
    // inline text (CancelFepInlineEdit reinstates the previous selection)
    TInt DocumentLengthForFep() const;
    TInt DocumentMaximumLengthForFep() const;
    void SetCursorSelectionForFepL( const TCursorSelection& aCursorSelection );
    void GetCursorSelectionForFep(TCursorSelection& aCursorSelection) const;
    void GetEditorContentForFep( TDes& aEditorContent, TInt aDocumentPosition, 
                                 TInt aLengthToRetrieve) const;
    void GetFormatForFep( TCharFormat& aFormat, TInt aDocumentPosition ) const;
    void GetScreenCoordinatesForFepL( TPoint& aLeftSideOfBaseLine, TInt& aHeight, 
                                      TInt& aAscent, TInt aDocumentPosition ) const;
    void DoCommitFepInlineEditL();
    MCoeFepAwareTextEditor_Extension1* Extension1( TBool& aSetToTrue );

private: // from MCoeFepAwareTextEditor
    void SetStateTransferingOwnershipL( CState* aState, TUid aTypeSafetyUid );
    CState* State( TUid aTypeSafetyUid ); // this function does *not* transfer ownership

private: // from MCoeFepAwareTextEditor
    IMPORT_C void MCoeFepAwareTextEditor_Reserved_2();

private:  // from MCoeFepAwareTextEditor_Extension1
    IMPORT_C virtual void MCoeFepAwareTextEditor_Extension1_Reserved_2();
    IMPORT_C virtual void MCoeFepAwareTextEditor_Extension1_Reserved_3();
    IMPORT_C virtual void MCoeFepAwareTextEditor_Extension1_Reserved_4();

public:
    IMPORT_C TInt ChangeEditorMode( TBool aDefaultMode = EFalse );   
    IMPORT_C TInt GetEditorMode() const;    
    IMPORT_C void ResetEditorToDefaultValues();  

public: 
// from CCoeControl  
    /**
     * Handle pointer events.
     * @param aPointerEvent, the pointer event.
     * @since 5.0
     */
    IMPORT_C void HandlePointerEventL( const TPointerEvent& aPointerEvent );  

    /**
     * Retrieves an object of the same type as that encapsulated in aId.
     * @param aId, encapsulated object type
     * @return Pointer to the object as the same type as in aId, if there is 
     * no object as the type, NULL will be returned.
     * @since 5.0
     */
    TTypeUid::Ptr MopSupplyObject( TTypeUid aId );

// From MEikCcpuEditor

    /**
     * Tests whether the editor is focused.
     * 
     * @return If editor is focused, @c ETrue is returned.
     * @since 5.0
     */
    IMPORT_C TBool CcpuIsFocused() const;

    /**
     * Tests whether the selected text can be cut.
     * 
     * @return @c ETrue if it is possible to cut the selected text.
     * @since 5.0
     */
    IMPORT_C TBool CcpuCanCut() const;

    /**
     * Cuts selected text.
     * @since 5.0
     */
    IMPORT_C void CcpuCutL();
    
    /**
     * Tests whether the selected text can be copied.
     * 
     * @return @c ETrue if it is possible to copy the selected text.
     * @since 5.0
     */
    IMPORT_C TBool CcpuCanCopy() const;

    /**
     * Copies selected text.
     * @since 5.0
     */
    IMPORT_C void CcpuCopyL();
    
    /**
     * Tests whether text can be pasted from the clipboard.
     * 
     * @return @c ETrue if it is possible to paste the clipboard text.
     * @since 5.0
     */
    IMPORT_C TBool CcpuCanPaste() const;

    /**
     * Pastes text from the clipboard to the editor.
     * @since 5.0
     */
    IMPORT_C void CcpuPasteL();
    
    /**
     * Tests is it possible to undo previous operation.
     * 
     * @return @c ETrue if it is possible to undo previous operation.
     * @since 5.0
     */
    IMPORT_C TBool CcpuCanUndo() const;

    /**
     * Undoes the most recent text operation when the Edwin supports this
     * feature and when the undo store is not empty
     * @since 5.0
     */
    IMPORT_C void CcpuUndoL();
    
    /**
     * Open VKB .  
     */
    EXPORT_C void OpenVKB();


private: 
//new functions, for ccpu support 
    /**
     * Handle clipboard operation.
     * @param aIsCopy, ETrue means this is copy operation, otherwise 
     * it is cut operation 
     */
    void ClipboardL( TBool aIsCopy );
    
    /**
     * Enable or disable ccpu support.
     * @param aSupport, ETrue enable, EFalse disable     
     */
    void EnableCcpuSupportL( TBool aSupport );
    
    /**
     * Place text on clipboard.
     * @param aText, the text that will be put on clipboard
     */
    void PlaceDataOnClipboardL( const TDesC& aText );

    /**
     * Check if paste operation is valid or not. If paste is invalid, 
     * this function will leave.
     */
    void DoCanPasteL() const;
    
    /**
     * Report event to pen input method.
     * @param aStateEvent, MAknEdStateObserver::EAknEdwinStateEvent     
     */
    void ReportAknEdStateEventL( 
             MAknEdStateObserver::EAknEdwinStateEvent aStateEvent );
    /**
     * close VKB .    
     */
    void CloseVKB( );
private:
    CAknPhoneNumberEditorExtension* iExtension; 
    TInt iNumFormats;
    TInt iCurrentFormatIndex;
    CAknPhedModel* iModel;
    CAknPhedView* iView;
    TInt iTargetCursorPos;
    TBitFlags32 iFlags;
    CEikScrollBarFrame* iSBFrame;
    CState* iFepState;
    };


inline CEikScrollBarFrame* CAknPhoneNumberEditor::CreatePreAllocatedScrollBarFrameL()
    { return CreateScrollBarFrameL( ETrue );}
inline CEikScrollBarFrame* CAknPhoneNumberEditor::ScrollBarFrame()
    { return ( ( CEikScrollBarFrame* const )iSBFrame ); }


#endif
