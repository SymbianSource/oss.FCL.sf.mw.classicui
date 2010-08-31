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



#ifndef C_TESTSDKNOTIFIERS_H
#define C_TESTSDKNOTIFIERS_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>

class CAknGlobalListMsgQuery;

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtestsdknotifiersLogPath, "\\logs\\testframework\\testsdknotifiers\\" ); 
// Log file
_LIT( KtestsdknotifiersLogFile, "testsdknotifiers.txt" ); 
_LIT( KtestsdknotifiersLogFileWithTitle, "testsdknotifiers_[%S].txt" );

/**
*  Ctestsdknotifiers test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS(CTestSDKNotifiers) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestSDKNotifiers* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKNotifiers();

public: // Functions from base classes

    /**
    * From CScriptBase Runs a script line.
    * @since S60 5.0
    * @param aItem Script line containing method name and parameters
    * @return Symbian OS error code
    */
    virtual TInt RunMethodL( CStifItemParser& aItem );

private:

    /**
    * C++ default constructor.
    */
    CTestSDKNotifiers( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    /**
    * Frees all resources allocated from test methods.
    * @since S60 5.0
    */
    void Delete();
    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

    //[TestMethods]
    
/*
 * aknglobalconfirmationquery.h
 */
private:
    /**
     * TestNotifiersCFMQueryNewLL test function for testing the NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersCFMQueryNewLL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersCFMQueryNewLCL test function for testing the NewLC function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersCFMQueryNewLCL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersCFMQueryDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersCFMQueryDestructorL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersCFMQueryShowConfirmationQueryLL test function for testing 
     * the ShowConfirmationQueryL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersCFMQueryShowConfirmationQueryLL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersCFMQueryUpdateConfirmationQueryL test function for testing the 
     * UpdateConfirmationQuery function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersCFMQueryUpdateConfirmationQueryL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersCFMQueryCancelConfirmationQueryL test function for testing the 
     * CancelConfirmationQuery function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersCFMQueryCancelConfirmationQueryL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersCFMQuerySetImageSkinIdL test function for testing the SetImageSkinId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersCFMQuerySetImageSkinIdL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersCFMQuerySetSecondaryDisplayDataL test function for testing 
     * the SetSecondaryDisplayData function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersCFMQuerySetSecondaryDisplayDataL( CStifItemParser& /*aItem*/ );
/*
 * AknGlobalListQuery.h
 */
private:
    /**
     * TestNotifiersListQueryNewLL test function for testing the NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersListQueryNewLL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersListQueryNewLCL test function for testing the NewLC function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersListQueryNewLCL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersListQueryDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersListQueryDestructorL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersListQueryShowListQueryLL test function for testing the 
     * ShowListQueryL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersListQueryShowListQueryLL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersListQueryMoveSelectionUpL test function for testing the 
     * MoveSelectionUp function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersListQueryMoveSelectionUpL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersListQueryMoveSelectionDownL test function for testing the 
     * MoveSelectionDown function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersListQueryMoveSelectionDownL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersListQuerySelectItemL test function for testing the SelectItem function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersListQuerySelectItemL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersListQueryCancelListQueryL test function for testing the 
     * CancelListQuery function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersListQueryCancelListQueryL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersListQuerySetHeadingLL test function for testing the SetHeadingL 
     * function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersListQuerySetHeadingLL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersListQuerySetSecondaryDisplayDataL test function for testing the 
     * SetSecondaryDisplayData function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersListQuerySetSecondaryDisplayDataL( CStifItemParser& /*aItem*/ );
/*
 * aknglobalmsgquery.h
 */
private:
    /**
     * TestNotifiersMsgQueryNewLL test function for testing the NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersMsgQueryNewLL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersMsgQueryNewLCL test function for testing the NewLC function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersMsgQueryNewLCL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersMsgQueryDestructorL test function for testing the Destructor 
     * function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersMsgQueryDestructorL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersMsgQueryShowMsgQueryLL test function for testing the ShowMsgQueryL 
     * function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersMsgQueryShowMsgQueryLL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersMsgQueryUpdateMsgQueryL test function for testing the UpdateMsgQuery 
     * function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersMsgQueryUpdateMsgQueryL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersMsgQueryCancelMsgQueryL test function for testing the CancelMsgQuery 
     * function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersMsgQueryCancelMsgQueryL( CStifItemParser& aItem );
    /**
     * TestNotifiersMsgQuerySetExitDelayL test function for testing the SetExitDelay function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersMsgQuerySetExitDelayL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersMsgQuerySetImageSkinIdL test function for testing the SetImageSkinId function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersMsgQuerySetImageSkinIdL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersMsgQuerySetSecondaryDisplayDataL test function for testing the 
     * SetSecondaryDisplayData function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersMsgQuerySetSecondaryDisplayDataL( CStifItemParser& /*aItem*/ );
    /**
     * TestGridsGMSSGVConstuctionL test function for testing the construction function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
/*
 * AknGlobalNote.h
 */
private:
    /**
     * TestNotifiersNoteNewLL test function for testing the NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersNoteNewLL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersNoteNewLCL test function for testing the NewLC function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersNoteNewLCL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersNoteDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersNoteDestructorL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersNoteSetTextProcessingL test function for testing the 
     * SetTextProcessing function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersNoteSetTextProcessingL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersNoteShowNoteLL test function for testing the ShowNoteL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersNoteShowNoteLL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersNoteShowNoteLStatusL test function for testing the ShowNoteL 
     * function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersNoteShowNoteLStatusL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersNoteCancelNoteLL test function for testing the CancelNoteL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersNoteCancelNoteLL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersNoteSetPriorityL test function for testing the SetPriority function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersNoteSetPriorityL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersNoteSetSoftkeysL test function for testing the NoteSetSoftkeys function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersNoteSetSoftkeysL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersNoteSetGraphicL test function for testing the SetGraphic function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersNoteSetGraphicL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersNoteSetAnimationL test function for testing the SetAnimation function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersNoteSetAnimationL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersNoteSetToneL test function for testing the SetTone function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersNoteSetToneL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersNoteDoGlobaNoteBufferLL test function for testing the 
     * DoGlobaNoteBufferL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersNoteDoGlobaNoteBufferLL( CStifItemParser& /*aItem*/ );
/*
 * aknglobalprogressdialog.h
 */
private:
    /**
     * TestNotifiersPGDialogNewLL test function for testing the NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersPGDialogNewLL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersPGDialogNewLCL test function for testing the NewLC function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersPGDialogNewLCL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersPGDialogDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersPGDialogDestructorL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersPGDialogSetIconLL test function for testing the SetIconL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersPGDialogSetIconLL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersPGDialogSetImageLL test function for testing the SetImageL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersPGDialogSetImageLL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersPGDialogShowProgressDialogLL test function for testing the 
     * ShowProgressDialogL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersPGDialogShowProgressDialogLL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersPGDialogUpdateProgressDialogL test function for testing the 
     * UpdateProgressDialog function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersPGDialogUpdateProgressDialogL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersPGDialogProcessFinishedL test function for testing the ProcessFinished function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersPGDialogProcessFinishedL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersPGDialogCancelProgressDialogL test function for testing the 
     * CancelProgressDialog function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersPGDialogCancelProgressDialogL( CStifItemParser& aItem );
    /**
     * TestNotifiersPGDialogSetImageSkinIdsL test function for testing the SetImageSkinIds function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersPGDialogSetImageSkinIdsL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersPGDialogSetSecondaryDisplayDataL test function for testing the 
     * SetSecondaryDisplayData function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersPGDialogSetSecondaryDisplayDataL( CStifItemParser& /*aItem*/ );
/*
 * AknNotify.h
 */
private:
    /**
     * TestNotifiersNotifyDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersNotifyDestructorL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersNotifySetSecondaryDisplayDataL test function for testing the 
     * SetSecondaryDisplayData function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersNotifySetSecondaryDisplayDataL( CStifItemParser& /*aItem*/ );

/*
 * AknPopupNotify.h
 */
private:
    /**
     * TestNotifiersPopNotifyNewLL test function for testing the NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersPopNotifyNewLL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersPopNotifyNewLCL test function for testing the NewLC function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersPopNotifyNewLCL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersPopNotifyDestructorL test function for testing the Destructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersPopNotifyDestructorL( CStifItemParser& /*aItem*/ );
    /**
     * TestNotifiersPopNotifyPopupMessageLL test function for testing the 
     * PopupMessageL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestNotifiersPopNotifyPopupMessageLL( CStifItemParser& /*aItem*/ );

/*
 * AknGlobalListMsgQuery.h
 */
private:
    
    /**
    * TestCAknGMsgQueryL test method of CAknGlobalListMsgQuery.
    * @since S60 5.0
    * @param is never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknGMsgQueryNewL( CStifItemParser& /*aItem*/ );
    
    /**
    * TestCAknGMsgQueryLC test method of CAknGlobalListMsgQuery.
    * @since S60 5.0
    * @param is never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknGMsgQueryNewLC( CStifItemParser& /*aItem*/ );
    
    /**
    * TestCAknGMsgQueryShowListMsgQueryL test method of CAknGlobalListMsgQuery.
    * @since S60 5.0
    * @param is never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknGMsgQueryShowListMsgQueryL( CStifItemParser& /*aItem*/);
    
    /**
    * TestCAknGMsgQueryMoveSelectionUpL test method of CAknGlobalListMsgQuery.
    * @since S60 5.0
    * @param is never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknGMsgQueryMoveSelectionUpL( CStifItemParser& /*aItem*/);
    
    /**
    * TestCAknGMsgQueryMoveSelectionDownL test method of CAknGlobalListMsgQuery.
    * @since S60 5.0
    * @param is never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknGMsgQueryMoveSelectionDownL( CStifItemParser& /*aItem*/);
    
    /**
    * TestCAknGMsgQuerySelectItemL test method of CAknGlobalListMsgQuery.
    * @since S60 5.0
    * @param is never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknGMsgQuerySelectItemL( CStifItemParser& /*aItem*/);
    
    /**
    * TestCAknGMsgQueryCancelListMsgQueryL test method of CAknGlobalListMsgQuery.
    * @since S60 5.0
    * @param is never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknGMsgQueryCancelListMsgQueryL( CStifItemParser& /*aItem*/);
    
    /**
    * TestCAknGMsgQuerySetSecondaryDisplayDataL test method of CAknGlobalListMsgQuery.
    * @since S60 5.0
    * @param is never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknGMsgQuerySetSecondaryDisplayDataL( CStifItemParser& /*aItem*/);
    
    /**
    * TestCAknGMsgQuerySetImageSkinIdL test method of CAknGlobalListMsgQuery.
    * @since S60 5.0
    * @param is never used.
    * @return Symbian OS error code.
    */
    virtual TInt TestCAknGMsgQuerySetImageSkinIdL( CStifItemParser& /*aItem*/);
    
private:    // Data

    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;
    

    };

#endif      // C_TESTSDKNOTIFIERS_H

// End of File
