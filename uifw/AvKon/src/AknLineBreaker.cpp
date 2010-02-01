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
* Description:  Line breaker class customized to meet Series 60 specifications.
*
*/


// INCLUDE FILES
#include "AknLineBreaker.h"
#include "aknenv.h"
#include <linebreak.h>
#include <featmgr.h>                //FeatureManager

// CONSTANTS

const TUint KOpFlag = 1 << MLineBreaker::EOpLineBreakClass;
const TUint KClFlag = 1 << MLineBreaker::EClLineBreakClass;
// const TUint KQuFlag = 1 << MLineBreaker::EQuLineBreakClass;
// const TUint KGlFlag = 1 << MLineBreaker::EGlLineBreakClass;
const TUint KNsFlag = 1 << MLineBreaker::ENsLineBreakClass;
const TUint KExFlag = 1 << MLineBreaker::EExLineBreakClass;
const TUint KSyFlag = 1 << MLineBreaker::ESyLineBreakClass;
const TUint KIsFlag = 1 << MLineBreaker::EIsLineBreakClass;
const TUint KPrFlag = 1 << MLineBreaker::EPrLineBreakClass;
const TUint KPoFlag = 1 << MLineBreaker::EPoLineBreakClass;
const TUint KNuFlag = 1 << MLineBreaker::ENuLineBreakClass;
const TUint KAlFlag = 1 << MLineBreaker::EAlLineBreakClass;
const TUint KIdFlag = 1 << MLineBreaker::EIdLineBreakClass;
const TUint KInFlag = 1 << MLineBreaker::EInLineBreakClass;
// const TUint KHyFlag = 1 << MLineBreaker::EHyLineBreakClass;
// const TUint KBaFlag = 1 << MLineBreaker::EBaLineBreakClass;
const TUint KBbFlag = 1 << MLineBreaker::EBbLineBreakClass;
const TUint KB2Flag = 1 << MLineBreaker::EB2LineBreakClass;
const TUint KZwFlag = 1 << MLineBreaker::EZwLineBreakClass;
const TUint KCmFlag = 1 << MLineBreaker::ECmLineBreakClass;
// const TUint KBkFlag = 1 << MLineBreaker::EBkLineBreakClass;
// const TUint KCrFlag = 1 << MLineBreaker::ECrLineBreakClass;
// const TUint KLfFlag = 1 << MLineBreaker::ELfLineBreakClass;
// const TUint KSgFlag = 1 << MLineBreaker::ESgLineBreakClass;
// const TUint KCbFlag = 1 << MLineBreaker::ECbLineBreakClass;
// const TUint KSpFlag = 1 << MLineBreaker::ESpLineBreakClass;
// const TUint KSaFlag = 1 << MLineBreaker::ESaLineBreakClass;
const TUint KAiFlag = 1 << MLineBreaker::EAiLineBreakClass;
// const TUint KXxFlag = 1 << MLineBreaker::EXxLineBreakClass;

const TUint KAllBreaks = 0xFFFFFFFF;

const TUint KUsualForbidden = KClFlag | KExFlag | KSyFlag | KIsFlag | KZwFlag;

const TUint KUsualAllowed =
    KOpFlag | KPrFlag | KPoFlag | KNuFlag | KAlFlag | KIdFlag | KInFlag |
    KBbFlag | KB2Flag | KAiFlag;

struct TLineBreakRule
    {
    // Classes that breaks are illegal before, even after spaces.
    TUint iForbid;
    // Classes that breaks are legal before, even without spaces.
    TUint iAllow;
    };

// A table of break rules, indexed by the class of the character before the
// possible break.
static const TLineBreakRule
    TheLineBreakRuleTable[MLineBreaker::ELineBreakClasses] =
    {
    { KAllBreaks - KCmFlag,0 },                                                     // Op
    { KUsualForbidden | KNsFlag,KUsualAllowed - KPoFlag },                          // Cl
    { KUsualForbidden | KOpFlag,0 },                                                // Qu
    { KUsualForbidden, 0 },                                                         // Gl
    { KUsualForbidden, KUsualAllowed },                                             // Ns
    { KUsualForbidden, KUsualAllowed },                                             // Ex
    { KUsualForbidden, KUsualAllowed - KNuFlag },                                   // Sy
    { KUsualForbidden, KUsualAllowed - KNuFlag },                                   // Is
    { KUsualForbidden, KPrFlag | KPoFlag | KInFlag | KBbFlag | KB2Flag },           // Pr
    { KUsualForbidden, KUsualAllowed },                                             // Po
    { KUsualForbidden, KOpFlag | KPrFlag | KIdFlag | KBbFlag | KB2Flag },           // Nu
    { KUsualForbidden, KOpFlag | KPrFlag | KPoFlag | KIdFlag | KBbFlag | KB2Flag }, // Al
    { KUsualForbidden, KUsualAllowed - KPoFlag - KInFlag },                         // Id
    { KUsualForbidden, KUsualAllowed - KInFlag },                                   // In
    { KUsualForbidden, KUsualAllowed },                                             // Hy
    { KUsualForbidden, KUsualAllowed },                                             // Ba
    { KUsualForbidden, 0 },                                                         // Bb
    { KUsualForbidden | KB2Flag, KUsualAllowed },                                   // B2
    { KZwFlag, KAllBreaks - KZwFlag - KCmFlag},                                     // Zw
    { KUsualForbidden, KOpFlag | KPrFlag | KPoFlag | KIdFlag | KBbFlag | KB2Flag }, // Cm
    { 0, 0, },                                                                      // Bk
    { 0, 0, },                                                                      // Cr
    { 0, 0, },                                                                      // Lf
    { 0, 0, },                                                                      // Sg
    { 0, 0, },                                                                      // Cb
    { KAllBreaks, 0, },                                                             // Sp
    { 0, 0, },                                                                      // Sa
    // the next line is different from GDI's table!
    { KUsualForbidden, KOpFlag | KPrFlag | KPoFlag | KIdFlag | KBbFlag | KB2Flag }, // Ai
    { 0, 0, }                                                                       // Xx
    };

// These are from editing UI spec.
// 0xFFxx values are corresponding full width forms used in Chinese translations

_LIT( KWrappingBeforeOrAfterChars,
      "#_@&/\\=\xFF03\xFF3F\xFF20\xFF06\xFF0F\xFF3C\xFF1D" );

const TText KPrivateUseAreaStart = 0xE000;
const TText KPrivateUseAreaEnd = 0xF900;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// TAknLineBreaker::LineBreakClass()
// -----------------------------------------------------------------------------
//
TUint TAknLineBreaker::LineBreakClass(
    TUint aCode, TUint& aRangeStart, TUint& aRangeEnd ) const
    {
    aRangeStart = aCode;
    aRangeEnd = aCode + 1;

    // Need to fix those areas of TheLineBreakRangeTable (see linebreak.cpp)
    // here, where our special wrapping characters reside.

    TUint lineclass;
    if (IsSpecialVariantChar(aCode, aRangeStart, aRangeEnd, lineclass))
        {
        return lineclass;
        }

    if ( aCode == 0x003C || aCode == 0x003E || aCode == 0x005E )
        {
        return EAlLineBreakClass;
        }

    if ( aCode >= 0x0041 && aCode <= 0x005A )
        {
        aRangeStart = 0x0041;
        aRangeEnd = 0x005B;
        return EAlLineBreakClass;
        }

    if ( aCode >= 0x0060 && aCode <= 0x007A )
        {
        aRangeStart = 0x0060;
        aRangeEnd = 0x007B;
        return EAlLineBreakClass;
        }

    // Regions, where our full with form special wrapping characters reside,
    // already return EIdLineBreakClass in TheLineBreakRangeTable, so no
    // need to fix them.

    if ( KWrappingBeforeOrAfterChars().Locate( aCode ) != KErrNotFound )
        {
        // this allows break before and after
        return EIdLineBreakClass;
        }
    if ( aCode >= KPrivateUseAreaStart && aCode < KPrivateUseAreaEnd )
        {
        aRangeStart = KPrivateUseAreaStart;
        aRangeEnd = KPrivateUseAreaEnd;
        // this allows break before and after
        return EIdLineBreakClass;
        }
    else
        {
        return MLineBreaker::LineBreakClass( aCode, aRangeStart, aRangeEnd );
        }
    }

// -----------------------------------------------------------------------------
// TAknLineBreaker::LineBreakPossible()
// This function is identical with the base implementation in LineBreak.dll.
// Only the used table TheLineBreakRuleTable is different.
// -----------------------------------------------------------------------------
//
TBool TAknLineBreaker::LineBreakPossible(
    TUint aPrevClass, TUint aNextClass, TBool aHaveSpaces ) const
    {
    if (aPrevClass >= ELineBreakClasses || aNextClass >= ELineBreakClasses)
        return FALSE;
    const TLineBreakRule& rule = TheLineBreakRuleTable[aPrevClass];
    TUint flag = 1 << aNextClass;
    if (rule.iForbid & flag)
        return FALSE;
    return aHaveSpaces || (rule.iAllow & flag);
    }


struct TLineBreakRangeForSpecialVariant
    {
    TUint iStart;
    TUint iEnd;
    TUint iClass;
    };

// -----------------------------------------------------------------------------
// The following definitions are for Japane variant
// -----------------------------------------------------------------------------
//
static const TLineBreakRangeForSpecialVariant TheLineBreakRangeTableForJapanese[] =
    {
    { 0x301c, 0x301d, MLineBreaker::EIdLineBreakClass },  //wave dash
    { 0x30fc, 0x30fd, MLineBreaker::ENsLineBreakClass },  //katakana-hiragana prolonged sound mark
    { 0x30fe, 0x30ff, MLineBreaker::ENsLineBreakClass },  //katakana voiced iteration mark
    { 0xff66, 0xff67, MLineBreaker::EIdLineBreakClass },  //halfwidth katakana letter wo
    { 0xff71, 0xff9e, MLineBreaker::EIdLineBreakClass },  //halfwidth katakana letter a - nn
    };

// -----------------------------------------------------------------------------
// TAknLineBreaker::IsSpecialVariantChar()
// Converts Unicode character into line breaking class for special variant.
// -----------------------------------------------------------------------------
//
EXPORT_C TBool TAknLineBreaker::IsSpecialVariantChar(TUint aCode, TUint& aRangeStart,TUint& aRangeEnd, TUint& aClass)
    {
    TBool ret = EFalse;

    // return if feature language is not Japanese
    CAknEnv* env = CAknEnv::Static();
    if (env)
        {
        if (!env->IsFeatureLanguage(KFeatureIdJapanese))
            {
            return ret;
            }
        }
    else
        {
        return ret;
        }

    // Now search the table.
    const TLineBreakRangeForSpecialVariant* base = TheLineBreakRangeTableForJapanese;
    const TLineBreakRangeForSpecialVariant* end = base +
                            (sizeof(TheLineBreakRangeTableForJapanese)
                             / sizeof(TheLineBreakRangeTableForJapanese[0]));
    while (base < end)
        {
        TInt n = end - base;
        const TLineBreakRangeForSpecialVariant* r = &base[n / 2];
        if (r->iStart > aCode)
            {
            end = r;
            }
        else if (r->iEnd <= aCode)
            {
            base = r + 1;
            }
        else
            {
            aRangeStart = r->iStart;
            aRangeEnd = r->iEnd;
            aClass = r->iClass;
            ret = ETrue;
            break;
            }
        }
    return ret;
    }

//  End of File
