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
* Description:  Test notifiers_api
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testsdknotifiers.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestsdknotifiers::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKNotifiers::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctestsdknotifiers::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKNotifiers::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        //aknglobalconfirmationquery.h
        ENTRY( "TestNotifiersCFMQueryNewLL", 
            CTestSDKNotifiers::TestNotifiersCFMQueryNewLL ),
        ENTRY( "TestNotifiersCFMQueryNewLCL", 
            CTestSDKNotifiers::TestNotifiersCFMQueryNewLCL ),
        ENTRY( "TestNotifiersCFMQueryDestructorL", 
            CTestSDKNotifiers::TestNotifiersCFMQueryDestructorL ),
        ENTRY( "TestNotifiersCFMQueryShowConfirmationQueryLL", 
            CTestSDKNotifiers::TestNotifiersCFMQueryShowConfirmationQueryLL ),
        ENTRY( "TestNotifiersCFMQueryUpdateConfirmationQueryL", 
            CTestSDKNotifiers::TestNotifiersCFMQueryUpdateConfirmationQueryL ),
        ENTRY( "TestNotifiersCFMQueryCancelConfirmationQueryL", 
            CTestSDKNotifiers::TestNotifiersCFMQueryCancelConfirmationQueryL ),
        ENTRY( "TestNotifiersCFMQuerySetImageSkinIdL", 
            CTestSDKNotifiers::TestNotifiersCFMQuerySetImageSkinIdL ),
        ENTRY( "TestNotifiersCFMQuerySetSecondaryDisplayDataL", 
            CTestSDKNotifiers::TestNotifiersCFMQuerySetSecondaryDisplayDataL ),
        
        //AknGlobalListQuery.h
        ENTRY( "TestNotifiersListQueryNewLL", 
            CTestSDKNotifiers::TestNotifiersListQueryNewLL ),
        ENTRY( "TestNotifiersListQueryNewLCL", 
            CTestSDKNotifiers::TestNotifiersListQueryNewLCL ),
        ENTRY( "TestNotifiersListQueryDestructorL", 
            CTestSDKNotifiers::TestNotifiersListQueryDestructorL ),
        ENTRY( "TestNotifiersListQueryShowListQueryLL", 
            CTestSDKNotifiers::TestNotifiersListQueryShowListQueryLL ),
        ENTRY( "TestNotifiersListQueryMoveSelectionUpL", 
            CTestSDKNotifiers::TestNotifiersListQueryMoveSelectionUpL ),
        ENTRY( "TestNotifiersListQueryMoveSelectionDownL", 
            CTestSDKNotifiers::TestNotifiersListQueryMoveSelectionDownL ),
        ENTRY( "TestNotifiersListQuerySelectItemL", 
            CTestSDKNotifiers::TestNotifiersListQuerySelectItemL ),
        ENTRY( "TestNotifiersListQueryCancelListQueryL", 
            CTestSDKNotifiers::TestNotifiersListQueryCancelListQueryL ),
        ENTRY( "TestNotifiersListQuerySetHeadingLL", 
            CTestSDKNotifiers::TestNotifiersListQuerySetHeadingLL ),
        ENTRY( "TestNotifiersListQuerySetSecondaryDisplayDataL", 
            CTestSDKNotifiers::TestNotifiersListQuerySetSecondaryDisplayDataL ),
        
        //aknglobalmsgquery.h
        ENTRY( "TestNotifiersMsgQueryNewLL", 
            CTestSDKNotifiers::TestNotifiersMsgQueryNewLL ),
        ENTRY( "TestNotifiersMsgQueryNewLCL", 
            CTestSDKNotifiers::TestNotifiersMsgQueryNewLCL ),
        ENTRY( "TestNotifiersMsgQueryDestructorL", 
            CTestSDKNotifiers::TestNotifiersMsgQueryDestructorL ),
        ENTRY( "TestNotifiersMsgQueryShowMsgQueryLL", 
            CTestSDKNotifiers::TestNotifiersMsgQueryShowMsgQueryLL ),
        ENTRY( "TestNotifiersMsgQueryUpdateMsgQueryL", 
            CTestSDKNotifiers::TestNotifiersMsgQueryUpdateMsgQueryL ),
        ENTRY( "TestNotifiersMsgQueryCancelMsgQueryL", 
            CTestSDKNotifiers::TestNotifiersMsgQueryCancelMsgQueryL ),
        ENTRY( "TestNotifiersMsgQuerySetExitDelayL", 
            CTestSDKNotifiers::TestNotifiersMsgQuerySetExitDelayL ),
        ENTRY( "TestNotifiersMsgQuerySetImageSkinIdL", 
            CTestSDKNotifiers::TestNotifiersMsgQuerySetImageSkinIdL ),
        ENTRY( "TestNotifiersMsgQuerySetSecondaryDisplayDataL", 
            CTestSDKNotifiers::TestNotifiersMsgQuerySetSecondaryDisplayDataL ),
        
        //AknGlobalNote.h
        ENTRY( "TestNotifiersNoteNewLL", 
            CTestSDKNotifiers::TestNotifiersNoteNewLL ),
        ENTRY( "TestNotifiersNoteNewLCL", 
            CTestSDKNotifiers::TestNotifiersNoteNewLCL ),
        ENTRY( "TestNotifiersNoteDestructorL", 
            CTestSDKNotifiers::TestNotifiersNoteDestructorL ),
        ENTRY( "TestNotifiersNoteSetTextProcessingL", 
            CTestSDKNotifiers::TestNotifiersNoteSetTextProcessingL ),
        ENTRY( "TestNotifiersNoteShowNoteLL", 
            CTestSDKNotifiers::TestNotifiersNoteShowNoteLL ),
        ENTRY( "TestNotifiersNoteShowNoteLStatusL", 
            CTestSDKNotifiers::TestNotifiersNoteShowNoteLStatusL ),
        ENTRY( "TestNotifiersNoteCancelNoteLL", 
            CTestSDKNotifiers::TestNotifiersNoteCancelNoteLL ),
        ENTRY( "TestNotifiersNoteSetPriorityL", 
            CTestSDKNotifiers::TestNotifiersNoteSetPriorityL ),
        ENTRY( "TestNotifiersNoteSetSoftkeysL", 
            CTestSDKNotifiers::TestNotifiersNoteSetSoftkeysL ),
        ENTRY( "TestNotifiersNoteSetGraphicL", 
            CTestSDKNotifiers::TestNotifiersNoteSetGraphicL ),
        ENTRY( "TestNotifiersNoteSetAnimationL", 
            CTestSDKNotifiers::TestNotifiersNoteSetAnimationL ),
        ENTRY( "TestNotifiersNoteSetToneL", 
            CTestSDKNotifiers::TestNotifiersNoteSetToneL ),
        ENTRY( "TestNotifiersNoteDoGlobaNoteBufferLL", 
            CTestSDKNotifiers::TestNotifiersNoteDoGlobaNoteBufferLL ),
        
        //aknglobalprogressdialog.h
        ENTRY( "TestNotifiersPGDialogNewLL", 
            CTestSDKNotifiers::TestNotifiersPGDialogNewLL ),
        ENTRY( "TestNotifiersPGDialogNewLCL", 
            CTestSDKNotifiers::TestNotifiersPGDialogNewLCL ),
        ENTRY( "TestNotifiersPGDialogDestructorL", 
            CTestSDKNotifiers::TestNotifiersPGDialogDestructorL ),
        ENTRY( "TestNotifiersPGDialogSetIconLL", 
            CTestSDKNotifiers::TestNotifiersPGDialogSetIconLL ),
        ENTRY( "TestNotifiersPGDialogSetImageLL",
            CTestSDKNotifiers::TestNotifiersPGDialogSetImageLL ),
        ENTRY( "TestNotifiersPGDialogShowProgressDialogLL", 
            CTestSDKNotifiers::TestNotifiersPGDialogShowProgressDialogLL ),
        ENTRY( "TestNotifiersPGDialogUpdateProgressDialogL", 
            CTestSDKNotifiers::TestNotifiersPGDialogUpdateProgressDialogL ),
        ENTRY( "TestNotifiersPGDialogProcessFinishedL", 
            CTestSDKNotifiers::TestNotifiersPGDialogProcessFinishedL ),
        ENTRY( "TestNotifiersPGDialogCancelProgressDialogL", 
            CTestSDKNotifiers::TestNotifiersPGDialogCancelProgressDialogL ),
        ENTRY( "TestNotifiersPGDialogSetImageSkinIdsL", 
            CTestSDKNotifiers::TestNotifiersPGDialogSetImageSkinIdsL ),
        ENTRY( "TestNotifiersPGDialogSetSecondaryDisplayDataL", 
            CTestSDKNotifiers::TestNotifiersPGDialogSetSecondaryDisplayDataL ),
        
        //AknNotify.h
        ENTRY( "TestNotifiersNotifyDestructorL", 
            CTestSDKNotifiers::TestNotifiersNotifyDestructorL ),
        ENTRY( "TestNotifiersNotifySetSecondaryDisplayDataL", 
            CTestSDKNotifiers::TestNotifiersNotifySetSecondaryDisplayDataL ),
        
        //AknPopupNotify.h
        ENTRY( "TestNotifiersPopNotifyNewLL", 
            CTestSDKNotifiers::TestNotifiersPopNotifyNewLL ),
        ENTRY( "TestNotifiersPopNotifyNewLCL", 
            CTestSDKNotifiers::TestNotifiersPopNotifyNewLCL ),
        ENTRY( "TestNotifiersPopNotifyDestructorL", 
            CTestSDKNotifiers::TestNotifiersPopNotifyDestructorL ),
        ENTRY( "TestNotifiersPopNotifyPopupMessageLL", 
            CTestSDKNotifiers::TestNotifiersPopNotifyPopupMessageLL ),
            
        //AknGloballistMsgQuery.h
        ENTRY( "TestCAknGMsgQueryNewL", 
            CTestSDKNotifiers::TestCAknGMsgQueryNewL ),
        ENTRY( "TestCAknGMsgQueryNewLC", 
            CTestSDKNotifiers::TestCAknGMsgQueryNewLC ),
        ENTRY( "TestCAknGMsgQueryShowListMsgQueryL", 
            CTestSDKNotifiers::TestCAknGMsgQueryShowListMsgQueryL ),
        ENTRY( "TestCAknGMsgQueryMoveSelectionUpL", 
            CTestSDKNotifiers::TestCAknGMsgQueryMoveSelectionUpL ),
        ENTRY( "TestCAknGMsgQueryMoveSelectionDownL", 
            CTestSDKNotifiers::TestCAknGMsgQueryMoveSelectionDownL ),
        ENTRY( "TestCAknGMsgQuerySelectItemL", 
            CTestSDKNotifiers::TestCAknGMsgQuerySelectItemL ),
        ENTRY( "TestCAknGMsgQueryCancelListMsgQueryL", 
            CTestSDKNotifiers::TestCAknGMsgQueryCancelListMsgQueryL ),
        ENTRY( "TestCAknGMsgQuerySetSecondaryDisplayDataL", 
            CTestSDKNotifiers::TestCAknGMsgQuerySetSecondaryDisplayDataL ),
        ENTRY( "TestCAknGMsgQuerySetImageSkinIdL", 
            CTestSDKNotifiers::TestCAknGMsgQuerySetImageSkinIdL ),
        
        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

//  [End of File]
