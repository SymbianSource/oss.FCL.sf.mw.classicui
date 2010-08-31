/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
*       Wrappers for standard note types
*
*/



#ifndef     __AknNoteWrappers_H__
#define     __AknNoteWrappers_H__


#include <aknnotedialog.h> 
#include <AknQueryDialog.h>


class TResourceReader;


class TAknNoteResData
	{
public:
    void ReadFromResource(TResourceReader& aResReader);
public:
	TInt iResId;
    CAknNoteDialog::TTimeout iTimeout;
    CAknNoteDialog::TTone iTone;
    TBuf<256> iText;
	};

/**
 * Base class for implementing commonly used notes.
 */
class CAknNoteWrapper : public CAknNoteDialog
    {
    public:
	   /**
		* Class default constructor.
		* 
		* Does not do anything
		*/
        IMPORT_C CAknNoteWrapper();
	   /**
		* Another class constructor
		*
		* Accept self pointer to CEikDialog* in order to NULL 
		* client pointer when a non modal note is dismissed.
		*
		* @param aSelfPtr Address of the dialog pointer
		*/
        IMPORT_C CAknNoteWrapper(CAknNoteWrapper** aSelfPtr);
       /**
		* Construct and display the dialog.
		*
		* Create a TAknNoteResData object by reading from resource file.
		* Set the timeout, set the tone (unless they have already been set)
		* and call RunLD. 
		*
		* @see SetTimeout, SetTone
		*
		* @param aResId Resource file ID
		*/
		IMPORT_C TInt ExecuteLD(TInt aResId);
       /**
		* Construct and display the dialog
		*
		* Construct a TAknNoteResData object by reading from resource file.
		* Set the prompt calling SetTextL. Set the timeout, set the
		* tone (unless they have already been set) and call RunLD. 
		*
		* @see SetTimeout, SetTone
		*
		* @param aResId             Resource file ID
		* @param aPrompt            Note text
		*/
		IMPORT_C TInt ExecuteLD(TInt aResId, const TDesC& aPrompt);

    	 /**
	     * From CCoeControl
		 * HandlePointerEventL Processes the pointer event directed at any note dialogs.
		 * @param aPointerEvent the pointer event to be processed.
		 */
	    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);		
    private:
        /**
        * From CAknControl
        */
        IMPORT_C void* ExtensionInterface( TUid aInterface );
	private: 
		IMPORT_C virtual void CEikDialog_Reserved_1();
		IMPORT_C virtual void CEikDialog_Reserved_2();	
	private: 
		IMPORT_C virtual void CAknNoteDialog_Reserved();
	private:
		TAknNoteResData ReadResDataAndPrepareL(TInt aResId);

	public:
		
		/**
		 * HandleDialogPageEventL is the interface method used by CEikDialogPage to
		 * signal the note that the some event happened on dialog page
		 * 
		 * @param aEventID event to be handled
		 */
		IMPORT_C virtual void HandleDialogPageEventL( TInt aEventID );
    private:
        IMPORT_C virtual void Reserved1();
    };

/**
 * Helper base class for implementing specialised note classes.
 * Using this class makes it unneccessary to overload ExecuteLD
 * in the specialised classes.
 */
class CAknResourceNoteDialog : public CAknNoteWrapper
    {
    public:
	   /**
	    * Construct and display the dialog.
	    *
	    * Using the resource ID stored in the constructor call the
		* corresponding ExecuteLD method in CAknNoteWrapper.
		*
		* @see CAknNoteWrapper::ExecuteLD
		*
	    */
		IMPORT_C TInt ExecuteLD();
	   /**
		* Construct, set the prompt and display the dialog.
		*
		* Using the resource ID stored in the constructor call the
		* corresponding ExecuteLD method in CAknNoteWrapper.
		*
		* @see CAknNoteWrapper::ExecuteLD
		*
		*/
		IMPORT_C TInt ExecuteLD(const TDesC& aPrompt);
        /**
         * From CCoeControl.     
         * Handles pointer events
         */
    	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);            

    protected:
		/**
		 * Constructor.
		 *
		 * Store resource ID.
		 *
		 * @param aResId The resource ID
		 */
        inline CAknResourceNoteDialog(TInt aResId)
            : iResId(aResId)
            {
            }
		
		/**
		 * Another class constructor.
		 *
		 * Store resource ID. Accept self pointer to CEikDialog* in order
		 * to NULL the dialog client pointer when a non modal note is
		 * dismissed.
		 *
		 * @param aResId    The resource ID
		 * @param aSelfPtr  Address to itself. The pointer must be valid when the
		 *                  dialog is dismissed and must not be on the stack.   
		 */
        inline CAknResourceNoteDialog(TInt aResId, CAknNoteWrapper** aSelfPtr)
            : CAknNoteWrapper(aSelfPtr), iResId(aResId)
            {
            }
    private:
        /**
        * From CAknControl
        */
        IMPORT_C void* ExtensionInterface( TUid aInterface );
	private: 
		IMPORT_C virtual void CEikDialog_Reserved_1();
		IMPORT_C virtual void CEikDialog_Reserved_2();	
	private: 
		IMPORT_C virtual void CAknNoteDialog_Reserved();
	private: // new virtual function
		IMPORT_C virtual void CAknResourceNoteDialog_Reserved();
    private:
        TInt iResId;
		TInt iSpare;
    };

/**
 * Wrapper for CAknNoteDialog implementing a Confirmation Note as
 * from S60 specifications.
 */
class CAknConfirmationNote : public CAknResourceNoteDialog
    {
    public:
	   /**
		* Default constructor.
		*
		* Create a CAknResourceNoteDialog using
		* R_AKN_CONFIRMATION_NOTE
		*/
        IMPORT_C CAknConfirmationNote();
	   /**
		* Another class constructor.
		*
		* Create a CAknResourceNoteDialog using 
		* R_AKN_CONFIRMATION_NOTE_WAIT or R_AKN_CONFIRMATION_NOTE
		* depending on the specified parameter
		*
		* @param aWaitingDialog If true use R_AKN_CONFIRMATION_NOTE_WAIT, 
		*                       else use R_AKN_CONFIRMATION_NOTE
		*/
        IMPORT_C CAknConfirmationNote( TBool aWaitingDialog );
	   /**
		* Another class constructor.
		*
		* Create a CAknResourceNoteDialog using
		* R_AKN_CONFIRMATION_NOTE. Accept self pointer to CEikDialog* 
		* in order to NULL client pointer when a non modal note is dismissed.
		*
		* @param aSelfPtr Address of the dialog pointer
		*/
        IMPORT_C CAknConfirmationNote(CAknConfirmationNote** aSelfPtr);
        /**
        * From CCoeControl.     
        * Handles pointer events
        */
    	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    private:
        /**
        * From CAknControl
        */
        IMPORT_C void* ExtensionInterface( TUid aInterface );
	private: 
		IMPORT_C virtual void CEikDialog_Reserved_1();
		IMPORT_C virtual void CEikDialog_Reserved_2();	
	private: 
		IMPORT_C virtual void CAknNoteDialog_Reserved();
	private: 
		IMPORT_C virtual void CAknResourceNoteDialog_Reserved();
    };

/**
 * Wrapper for CAknNoteDialog implementing an Information Note as
 * from S60 specifications.
 */
class CAknInformationNote : public CAknResourceNoteDialog
    {
    public:
	   /**
		* Default constructor.
		*
		* Create a CAknResourceNoteDialog using
		* R_AKN_INFORMATION_NOTE
		*/
        IMPORT_C CAknInformationNote();
	   /**
		* Another class constructor.
		*
		* Create a CAknResourceNoteDialog using
		* R_AKN_INFORMATION_NOTE_WAIT or R_AKN_INFORMATION_NOTE
		* depending on the specified parameter
		*
		* @param aWaitingDialog If true use R_AKN_INFORMATION_NOTE_WAIT, 
		*                       else use R_AKN_INFORMATION_NOTE
		*/
		IMPORT_C CAknInformationNote( TBool aWaitingDialog );
	   /**
		* Another class constructor.
		*
		* Create a CAknResourceNoteDialog using
		* R_AKN_INFORMATION_NOTE. Accept self pointer to CEikDialog* 
		* in order to NULL client pointer when a non modal note is dismissed.
		*
		* @param aSelfPtr Address of the dialog pointer
		*/
		IMPORT_C CAknInformationNote(CAknInformationNote** aSelfPtr);
        /**
        * From CCoeControl.     
        * Handles pointer events
        */
    	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);		
    private:
        /**
        * From CAknControl
        */
        IMPORT_C void* ExtensionInterface( TUid aInterface );        
	private: 
		IMPORT_C virtual void CEikDialog_Reserved_1();
		IMPORT_C virtual void CEikDialog_Reserved_2();	
	private: 
		IMPORT_C virtual void CAknNoteDialog_Reserved();
	private: 
		IMPORT_C virtual void CAknResourceNoteDialog_Reserved();
    };

/**
 * Wrapper for CAknNoteDialog implementing an Error Note as
 * from S60 specifications.
 */
class CAknErrorNote : public CAknResourceNoteDialog
    {
    public:
       /**
		* Default constructor.
		*
		* Create a CAknResourceNoteDialog using
		* R_AKN_ERROR_NOTE
		*/
		IMPORT_C CAknErrorNote();
	   /**
		* Another class constructor.
		*
		* Create a CAknResourceNoteDialog using
		* R_AKN_ERROR_NOTE_WAIT or R_AKN_ERROR_NOTE
		* depending on the specified parameter
		*
		* @param aWaitingDialog If true use R_AKN_ERROR_NOTE_WAIT, 
		*                       else use R_AKN_ERROR_NOTE
		*/
		IMPORT_C CAknErrorNote( TBool aWaitingDialog );
	   /**
		* Another class constructor.
		*
		* Create a CAknResourceNoteDialog using
		* R_AKN_ERROR_NOTE. Accept self pointer to CEikDialog* 
		* in order to NULL client pointer when a non modal note is dismissed.
		*
		* @param aSelfPtr Address of the dialog pointer
		*/     
		IMPORT_C CAknErrorNote(CAknErrorNote** aSelfPtr);
        /**
        * From CCoeControl. Handles pointer event
        * @param aPointerEvent Pointer event to be handled
        */
	    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);  
    private:
        /**
        * From CAknControl
        */
        IMPORT_C void* ExtensionInterface( TUid aInterface );
	private: 
		IMPORT_C virtual void CEikDialog_Reserved_1();
		IMPORT_C virtual void CEikDialog_Reserved_2();	
	private: 
		IMPORT_C virtual void CAknNoteDialog_Reserved();
	private: 
		IMPORT_C virtual void CAknResourceNoteDialog_Reserved();
    };

/**
 * Wrapper for CAknNoteDialog implementing a Warning Note as
 * from S60 specifications.
 */
class CAknWarningNote : public CAknResourceNoteDialog
    {
    public:
	   /**
		* Default constructor.
		*
		* Create a CAknResourceNoteDialog using
		* R_AKN_WARNING_NOTE
		*/
        IMPORT_C CAknWarningNote();
       /**
		* Another class constructor.
		*
		* Create a CAknResourceNoteDialog using
		* R_AKN_WARNING_NOTE_WAIT or R_AKN_WARNING_NOTE
		* depending on the specified parameter
		*
		* @param aWaitingDialog If true use R_AKN_WARNING_NOTE_WAIT, 
		*                       else use R_AKN_WARNING_NOTE
		*/
		IMPORT_C CAknWarningNote( TBool aWaitingDialog );
	   /**
		* Another class constructor.
		*
		* Create a CAknResourceNoteDialog using
		* R_AKN_WARNING_NOTE. Accept self pointer to CEikDialog* 
		* in order to NULL client pointer when a non modal note is dismissed.
		*
		* @param aSelfPtr Address of the dialog pointer
		*/     
		IMPORT_C CAknWarningNote(CAknWarningNote** aSelfPtr);
       /**
        * From CCoeControl.     
        * Handles pointer events
        */
	    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    private:
        /**
        * From CAknControl
        */
        IMPORT_C void* ExtensionInterface( TUid aInterface );
	private: 
		IMPORT_C virtual void CEikDialog_Reserved_1();
		IMPORT_C virtual void CEikDialog_Reserved_2();	
	private: 
		IMPORT_C virtual void CAknNoteDialog_Reserved();
	private: 
		IMPORT_C virtual void CAknResourceNoteDialog_Reserved();
    };

#endif  
            
