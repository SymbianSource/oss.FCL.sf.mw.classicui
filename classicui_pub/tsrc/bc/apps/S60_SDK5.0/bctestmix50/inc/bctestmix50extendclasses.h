/*
* Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         declaration of testting needed extend classes.
*
*/









#ifndef C_BCTESTMIX50EXTENDCLASSES_H
#define C_BCTESTMIX50EXTENDCLASSES_H

#include <eikccpu.h>
#include <eikcapc.h>
#include <akngrid.h>
#include <aknpopup.h>
#include <aknLocationed.h>
#include <aknsettingpage.h>


/*
 * following class test for CAknPopupList::FadeBehindPopup(protected)
 */
class CBCTestCAknPopupList: public CAknPopupList
    {
    friend class CBCTestMix50Case;

public:
    /**
     * Symbian static 2nd constructor
     */
    static CBCTestCAknPopupList* NewL( CEikListBox* aListBox );
    };


/*
 * following class for UpdateCommandObserverL testing
 */
class TBCTestCommandObserver: public MEikCommandObserver
    {
    /*
     * realize the interface function ProcessCommandL
     */
    void ProcessCommandL( TInt /*aCommandId*/ );
    };


/*
 * following class for SetPointerEventObserver tesing
 */
class TBCTestPointerObserver: public MPointerEventObserver
    {
    /*
     * realize the interface function PointerEvent
     */
    bool PointerEvent( CEikCaptionedControl* /*aControl*/,
                       const TPointerEvent& /*aPointerEvent*/ );
    };

/*
 * test for CAknSettingPage::TextLabel/ShadowText ( protected )
 */
class CBCTestCAknSettingPage: public CAknSettingPage
    {
    friend class CBCTestMix50Case;

public:
    CBCTestCAknSettingPage::CBCTestCAknSettingPage( TInt aResourceId );

    CBCTestCAknSettingPage::CBCTestCAknSettingPage(
                                             const TDesC* aSettingText,
                                             TInt aSettingNumber,
                                             TInt aControlType,
                                             TInt aEditorResourceId,
                                             TInt aSettingPageResourceId );
    };


/*
 * following class for AddSelectionObserverL/RemoveSelectionObserver
 */
class TBCTestSelectionObserver: public MListBoxSelectionObserver
    {
    void SelectionModeChanged( CEikListBox* /*aListBox*/,
                               TBool /*aSelectionModeEnabled*/ );
    };

/*
 * following class for SetCcpuState
 */
class TBCTestCcpuEditor: public MEikCcpuEditor
    {
    /*
     * realize the interface function CcpuIsFocused
     */
    TBool CcpuIsFocused() const;

    /*
     * realize the interface function CcpuCanCut
     */
    TBool CcpuCanCut() const;

    /*
     * realize the interface function CcpuCutL
     */
    void CcpuCutL();

    /*
     * realize the interface function CcpuCanCopy
     */
    TBool CcpuCanCopy() const;

    /*
     * realize the interface function CcpuCopyL
     */
    void CcpuCopyL();

    /*
     * realize the interface function CcpuCanPaste
     */
    TBool CcpuCanPaste() const;

    /*
     * realize the interface function CcpuPasteL
     */
    void CcpuPasteL();

    /*
     * realize the interface function CcpuCanUndo
     */
    TBool CcpuCanUndo() const;

    /*
     * realize the interface function CcpuUndoL
     */
    void CcpuUndoL();
    };


/*
 * following class for CAknGrid::MopSupplyObject
 */
class CBCTestCAknGrid: public CAknGrid
    {
    friend class CBCTestMix50Case;

public:
    CBCTestCAknGrid();

    };

/*
 * following class for CAknLocationEditor::CAknLocationEditor_ExtensionInterface
 */
class CBCTestCAknLocationEditor: public CAknLocationEditor
    {
    friend class CBCTestMix50Case;
    void* CAknLocationEditor_ExtensionInterface( TUid aInterface );
    };

#endif //C_BCTESTMIX50EXTENDCLASSES_H
