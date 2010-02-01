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
* Description:    
*
*/


#ifndef CDOCSAVER_H
#define CDOCSAVER_H

//  INCLUDES
#include <StringLoader.h>           // For loading resource strings
#include <documenthandlerui.rsg>    // Resource ids
#include <AknWaitDialog.h>          // CAknWaitDialog

// CONSTANTS
const TInt KDocNotDialogShowed = 1;
const TInt KDocConfNoteMaxLen = 256;
const TInt KDocWaitNoteMaxLen = 256;

// MACROS

// DATA TYPES

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS

// CLASS DECLARATION

NONSHARABLE_CLASS(CDocSaver) :public CBase
    {
    public:  // Constructors and destructor
        
        /**
        * C++ default constructor.
        */
        CDocSaver();

        /**
        * Two-phased constructor.
        */
        static CDocSaver* NewL();
        
        /**
        * Destructor.
        */
        virtual ~CDocSaver();

    public: // New functions
        
        static void ConfNoteL( const TDesC& aText, TBool aWait );

    private:

        /**
        * By default EPOC constructor is private.
        */
        void ConstructL();

        // By default, prohibit copy constructor
        CDocSaver( const CDocSaver& );
        // Prohibit assigment operator
        CDocSaver& operator= ( const CDocSaver& );
    };



/**
*  DocHandler's WaitDialog
*  Shows wait dialog if executed over 1 second, if not shows confirmation note
*/
class CDocWaitDialog :public CAknWaitDialog
    {
    public:  // Constructors and destructor
                
        /**
        * C++ default constructor.
        * @param aNoteControlId     Control id of the resource
        * @param aSelfPtr           Pointer to itself.
        * @param aCaption           Caption of the application
        */
        CDocWaitDialog( 
            CEikDialog** aSelfPtr,
            const TDesC& aText);            
        
        

    public: // New functions
        
        /**
        * Delete the wait dialog and show confirmation note if
        * wait dialog hasn't been visible.
        */
        TBool Finish();
        
        /**
        * Execute the dialog. Sets the label 
        * and calls CAknWaitDialog's RunDlgLD().
        * @return ?description
        */
        TInt ExecuteDlgLD();    
               
    private:

        // By default, prohibit copy constructor
        CDocWaitDialog( const CDocWaitDialog& );
        // Prohibit assigment operator
        CDocWaitDialog& operator= ( const CDocWaitDialog& );

    private:    // Data
        TPtrC iText;
        TBool iFinished;
    };


/**
*  DocHandler's CDocAsyncSaver
*  Hides asynchronous saving and provides synchronous saving function
*/
NONSHARABLE_CLASS(CDocAsyncSaver) :public CActive
    {
    public:  // Constructors and destructor
        
        /**
        * C++ default constructor.
        */
        CDocAsyncSaver();

        /**
        * Two-phased constructor.
        */
        static CDocAsyncSaver* NewL();
        static CDocAsyncSaver* NewLC();
        
        /**
        * Destructor.
        */
        virtual ~CDocAsyncSaver();

    public: // New functions
        
        /**
        * Write aContent to the file.
        * @param aContent       Content
        * @param aDestFile      Destination file
        * @param aWaitNoteText  Wait Note text                
        */
        void WriteToFileL(const TDesC8& aContent, 
                         RFile& aDestFile,                         
                         const TDesC& aWaitNoteText );

        /**
        * Copy aSourceFile to aDestFile
        * @param aSourceFile    Source file
        * @param aDestFile      Destination file
        * @param aSwitch        Switch        
        * @param aWaitNoteText  Wait Note text                
        */
        void CopyFileL(CFileMan* aFileManager, 
                      const TFileName& aSourceFile,
                      const TFileName& aDestFile,
                      TUint aSwitch,
                      const TDesC& aWaitNoteText );
                      
        /**
        * Copy aSourceFile to aDestFile
        * @param aSourceFile    Filehandle of source file
        * @param aDestFile      Destination file
        * @param aSwitch        Switch        
        * @param aWaitNoteText  Wait Note text                
        */
        void CopyFileL(CFileMan* aFileManager, 
                      const RFile& aSourceFile,
                      const TFileName& aDestFile,
                      TUint aSwitch,                      
                      const TDesC& aWaitNoteText );


        /**
        * Move aSourceFile to aDestFile
        * @param aSourceFile    Source file
        * @param aDestFile      Destination file
        * @param aSwitch        Switch        
        * @param aWaitNoteText  Wait Note text
        * @param aSilent        True=silent operation (do not show waitdialog)        
        */
        void MoveFileL(CFileMan* aFileManager, 
                      const TFileName& aSourceFile,
                      const TFileName& aDestFile,
                      TUint aSwitch,                      
                      const TDesC& aWaitNoteText,
                      const TBool aSilent);

        /**
        * Returns status of the asynchronous operation
        * @return Status of the asynchronous operation
        */
        TRequestStatus Status();    
        
        /**
        * Delete waitdialog and return status of the dialog.
        * @return ETrue if waitdialog is visible
        *         EFalse if waitdialog isn't visible 
        */
        TBool ShowDialog();
            
    protected:  // Functions from base classes
        
        /**
        * From CActive Not implemented
        */
        void DoCancel() ;
        /**
        * From CActive Delete wait dialog and stop CActiveSchedulerWait
        */
        void RunL() ;

    private:

        /**
        * By default EPOC constructor is private.
        */
        void ConstructL();

        // By default, prohibit copy constructor
        CDocAsyncSaver( const CDocAsyncSaver& );
        // Prohibit assigment operator
        CDocAsyncSaver& operator= ( const CDocAsyncSaver& );
    
    private:    // Data
        CDocWaitDialog* iDocWaitDialog;
        CActiveSchedulerWait iWait; // To make asychronous synchronous
        TBool iShowDialog;
        TBool iSilent;
    };

#endif      // CDOCSAVER_H   
            
// End of File
