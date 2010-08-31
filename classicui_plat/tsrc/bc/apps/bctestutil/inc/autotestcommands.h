/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Defines commands used in autotesting
*
*/








#ifndef AUTOTESTCOMMANDS_H
#define AUTOTESTCOMMANDS_H

// Language enumerations would overlap with command enumerations -->
// start commands somewhere else

enum TAutotestCommands
    {
    LeftCBA = 2000,
    RightCBA,
    KeyOK,
    Up,
    Down,
    Left,
    Right,
    Key1,
    Key2,
    Key3,
    Key4,
    Key5,
    Key6,
    Key7,
    Key8,
    Key9,
    Key0,
    KeyAsterisk,
    KeyHash,
    KeyApplication,
    KeyPhoneSend,
    KeyPhoneEnd,
    KeyPower,
    KeyVoice,
    KeyBackspace,
    KeyABC,
    GripOpen,
    GripClose,
    REPEAT,            // command and count must follow repeat
    WAITCOMMAND,       // count must follow wait    
    SETTICKCOUNT,   // sets time between commands (in 0.1 second intervals)
    JUSTKEYDOWN,    // next command is key down press
    JUSTKEYUP,      // next command is key up press    

    //for touch screen support
    PointerDown,
    PointerUp,
    PointerMove
    };

#define REP(command, count) REPEAT, command, count
#define WAIT(count) WAITCOMMAND, count
#define DELAY(count) SETTICKCOUNT, count
#define KEYDOWN(keypress) JUSTKEYDOWN, keypress
#define KEYUP(keypress) JUSTKEYUP, keypress

//  for localization support
#define IFDISPLANG(aLanguage) IfDispLanguage, aLanguage,
#define ELSE Else,
#define ENDIF EndIf,
#define POINTERDOWN(x,y) PointerDown, x, y
#define POINTERUP(x,y) PointerUp, x, y
#define POINTERMOVE(x,y) PointerMove, x, y
#define TEND -1

#endif //AUTOTESTCOMMANDS_H
