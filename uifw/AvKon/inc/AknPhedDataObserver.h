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
*
*/

#ifndef AKNPHEDDATAOBSERVER_H
#define AKNPHEDDATAOBSERVER_H

#include <e32base.h>

class CAknPhedModel;

//
// MPhedDataObserver
//
class MPhedDataObserver
    {
public:
    class TAknPhedDataEvent
        {
    public:
        enum TType
            {
            EText=0x1,
            ECursor=0x2,
            ESelection=0x4
            };

    public:
        inline TAknPhedDataEvent();
        inline TAknPhedDataEvent( TInt aType );
        inline TAknPhedDataEvent( TInt aType, TInt aStart, TInt aEnd );

        inline void Reset();
        void Add( const TAknPhedDataEvent& aEvent );

        inline TBool TextChanged() const;
        inline TBool CursorChanged() const;
        inline TBool SelectionChanged() const;
        inline void TextChangeRange( TInt& aStart, TInt& aEnd ) const;

        inline TInt Type() const;

    private:
        TInt iType;
        TInt iStart;
        TInt iEnd;
        };

    virtual void HandlePhedDataEvent( const TAknPhedDataEvent& aEvent, 
                                      CAknPhedModel* aPhedData ) = 0;
    };

#endif // AKNPHEDDATAOBSERVER_H

