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
* Description:  Test AknNoteDialog.h 
*
*/

#ifndef C_TESTSDKNOTESNOTEDIALOG_H
#define C_TESTSDKNOTESNOTEDIALOG_H

//  INCLUDES

#include <aknnotedialog.h>
#include <bassnd.h>
#include <aknnotecontrol.h>

    /**
    *  CTestSDKNotesNoteDialog test class for CAknNoteDialog protected API.
    */
class CTestSDKNotesNoteDialog : public CAknNoteDialog
    {
public:// Constructors and destructor
    
    /**
    * C++ default constructor.
    */
    CTestSDKNotesNoteDialog();
    
    /**
    * Destructor.
    */
    ~CTestSDKNotesNoteDialog();
    
public:    
    /**
    *  SetSizeAndPosition test function for testing the 
    * Test SetSizeAndPosition function
    */
    void SetSizeAndPosition( const TSize& aSize );
    
    /**
    *  PreLayoutDynInitL test function for testing the 
    * Test PreLayoutDynInitL function
    */
    void PreLayoutDynInitL();
    
    /**
    *  PostLayoutDynInitL test function for testing the 
    * Test PostLayoutDynInitL function
    */
    void PostLayoutDynInitL();
    
    /**
    *  PlayTone test function for testing the 
    * Test PlayTone function
    */
    void PlayTone();
    
    /**
    *  ReportUserActivity test function for testing the 
    * Test ReportUserActivity function
    */
    void ReportUserActivity() const;
    
    /**
    *  StaticDeleteL test function for testing the 
    * Test StaticDeleteL function
    */
    static TInt StaticDeleteL( TAny* aThis );
    
    /**
    *  ControlAttributes test function for testing the 
    * Test ControlAttributes function
    */
    CAknNoteAttributes* ControlAttributes();
    
    /**
    *  TransferControlAttributes test function for testing the 
    * Test TransferControlAttributes function
    */
    void TransferControlAttributes();
    
    /**
    *  SoundSystem test function for testing the 
    * Test SoundSystem function
    */
    CAknKeySoundSystem* SoundSystem() const;
    
    /**
    *  NoteControl test function for testing the 
    * Test NoteControl function
    */
    CAknNoteControl* NoteControl();
    
    /**
    *  SetNoMemoryAllocation test function for testing the 
    * Test SetNoMemoryAllocation function
    */
    void SetNoMemoryAllocation();
    
public:// Data
    /**
     * CPeriodic Property
     */
    CPeriodic* iTimer;
    
    /**
     * Timeout Property
     */
    TInt iTimeoutInMicroseconds; 
    
    /**
     * CEikDialog Property
     */
    CEikDialog** SelfPtr; 
    
    /**
     * TTone Property
     */
    TTone iTone;
    
    /**
     * CAknNoteAttributes Property
     */
    CAknNoteAttributes* iControlAttributes; 
    };

#endif /*C_TESTSDKNOTESNOTEDIALOG_H*/
