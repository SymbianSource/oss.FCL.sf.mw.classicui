/*
* Copyright (c) 2002-2008 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef __AKNGLOBALNOTENOTIFY_H__
#define __AKNGLOBALNOTENOTIFY_H__

// INCLUDES
#include <AknNotify.h>
#include <AknNotifyStd.h>

// CLASS DECLARATION

/**
*  This class handles the global notes.
*  
*  @since S60 0.9
*/
NONSHARABLE_CLASS(CAknGlobalNote) : public CAknNotifyBase
    {
public: 
    /**
    * Two-phased constructor.
    * @return Pointer to new global note object.
    */
    IMPORT_C static CAknGlobalNote* NewL();
    
    /**
    * Two-phased constructor.
    * @return Pointer to new global note object.
    */
    IMPORT_C static CAknGlobalNote* NewLC();
    
    /**
    * Destructor.
    */
    IMPORT_C ~CAknGlobalNote();

   /**
    * Enable or disable all text processing done by the dialog.
    * This includes text wrapping, text truncation
    * and reordering of bidirectional text.
    *
    * By default, it is enabled.
    *
    * If text processing is disabled, lines are broken only at explicit line 
    * end characters and they are not truncated, but drawn as long as they
    * fit. Also, the dialog does not handle reordering of bidirectional text.
    *
    * @since S60 2.0
    * @param aEnabled Enable or disable all text processing.
    */
    IMPORT_C void SetTextProcessing(TBool aEnabled);

    /**
    * Displays the global note.
    * @param aType Note type.
    * @param aNoteText Note text.
    * @return Note ID.
    */
    IMPORT_C TInt ShowNoteL(TAknGlobalNoteType aType, const TDesC& aNoteText);
    
    /**
    * Displays the global note.
    * @param aStatus Reference to request status.
    * @param aType Note type.
    * @param aNoteText Note text.
    * @return Note ID.
    */
    IMPORT_C TInt ShowNoteL(
        TRequestStatus& aStatus, 
        TAknGlobalNoteType aType,
        const TDesC& aNoteText);
    
    /**
    * Cancels the global note.
    * @param aNoteId Note ID.
    */
    IMPORT_C void CancelNoteL(TInt aNoteId);
    
    /**
    * Sets the priority.
    * @param aPriority An integer specifying the new priority.
    */
    IMPORT_C void SetPriority(TInt aPriority);
    
    /**
    * Sets the softkey ID. (Not used)
    * @param aId softkey ID 
    */
    IMPORT_C void SetSoftkeys(TInt aId);
    
    /**
    * Sets the graphic ID and the graphic mask ID.
    * @param aId Graphic ID
    * @param aMaskId Graphic mask ID.
    */
    IMPORT_C void SetGraphic(TInt aId, TInt aMaskId=-1);
    
    /**
    * Sets the animation.
    * @param aResourceId Resource ID of the animation.
    */
    IMPORT_C void SetAnimation(TInt aResourceId);
    
    /**
    * Sets the tone.
    * @param aTone New tone.
    */
    IMPORT_C void SetTone(TInt aTone);  // must be specified in avkon.hrh
    
    /** 
    * Internal, please do not use.
    * @internal
    */
    IMPORT_C static void DoGlobaNoteBufferL(
        TInt16 aType,
        TInt16 aPriority,
        TInt aSoftkeys,
        TInt16 aGraphic,
        TInt16 aGraphicMask,
        TInt aAnimation,
        TInt16 aTone,
        TBool aAdapterUsed,
        TBool aTextProcessingEnabled,
        const TDesC& aNoteText,
        CBufFlat* aBuffer
        );
        
    /** 
    * @internal
    */
    static void DoGlobalNoteBufferL(
        TInt16 aType,
        TInt16 aPriority,
        TInt aSoftkeys,
        TInt16 aGraphic,
        TInt16 aGraphicMask,
        TInt aAnimation,
        TInt16 aTone,
        TBool aAdapterUsed,
        TBool aTextProcessingEnabled,
        const TDesC& aNoteText,
        CBufFlat* aBuffer,
        TInt32 aPreallocatedGlobalNoteId
        );        

private:
    CAknGlobalNote();
    void ConstructL();    
    
    void PrepareBufferL(
        TAknGlobalNoteType aType,
        const TDesC& aNoteText,
        TInt aPreallocatedGlobalNoteId = 0);

private:
    IMPORT_C void CAknNotifyBase_Reserved();
    
private:
    TInt iPriority;
    TInt iSoftkeys;
    TInt iGraphic;
    TInt iGraphicMask;
    TInt iAnimation;
    TInt iTone;
    TBool iTextProcessing;
    
    CBufFlat *iBuffer;
    TPtrC8 iBufferPtr;

    CBufFlat *iCancelBuffer;
    TPtrC8 iCancelBufferPtr;
    
    // Not really used, but needed to prevent buffer handling errors.
    TPckgBuf<SAknGlobalNoteReturnParams> iRetPckg;
    };

#endif // __AKNGLOBALNOTENOTIFY_H__
