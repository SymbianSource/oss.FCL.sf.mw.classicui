/*
* Copyright (c) 2001 Nokia Corporation and/or its subsidiary(-ies).
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


#include <eiklay.h>
#include <eikpanic.h>
#include <eikcoctlpanic.h>
#include <AknLineBreaker.h>

const TUint KOpFlag = 1 << MTmCustom::EOpLineBreakClass;
const TUint KClFlag = 1 << MTmCustom::EClLineBreakClass;
// const TUint KQuFlag = 1 << MTmCustom::EQuLineBreakClass;
// const TUint KGlFlag = 1 << MTmCustom::EGlLineBreakClass;
const TUint KNsFlag = 1 << MTmCustom::ENsLineBreakClass;
const TUint KExFlag = 1 << MTmCustom::EExLineBreakClass;
const TUint KSyFlag = 1 << MTmCustom::ESyLineBreakClass;
const TUint KIsFlag = 1 << MTmCustom::EIsLineBreakClass;
const TUint KPrFlag = 1 << MTmCustom::EPrLineBreakClass;
const TUint KPoFlag = 1 << MTmCustom::EPoLineBreakClass;
const TUint KNuFlag = 1 << MTmCustom::ENuLineBreakClass;
const TUint KAlFlag = 1 << MTmCustom::EAlLineBreakClass;
const TUint KIdFlag = 1 << MTmCustom::EIdLineBreakClass;
const TUint KInFlag = 1 << MTmCustom::EInLineBreakClass;
// const TUint KHyFlag = 1 << MTmCustom::EHyLineBreakClass;
const TUint KBaFlag = 1 << MTmCustom::EBaLineBreakClass;
const TUint KBbFlag = 1 << MTmCustom::EBbLineBreakClass;
const TUint KB2Flag = 1 << MTmCustom::EB2LineBreakClass;
const TUint KZwFlag = 1 << MTmCustom::EZwLineBreakClass;
const TUint KCmFlag = 1 << MTmCustom::ECmLineBreakClass;
// const TUint KBkFlag = 1 << MTmCustom::EBkLineBreakClass;
// const TUint KCrFlag = 1 << MTmCustom::ECrLineBreakClass;
// const TUint KLfFlag = 1 << MTmCustom::ELfLineBreakClass;
// const TUint KSgFlag = 1 << MTmCustom::ESgLineBreakClass;
// const TUint KCbFlag = 1 << MTmCustom::ECbLineBreakClass;
// const TUint KSpFlag = 1 << MTmCustom::ESpLineBreakClass;
// const TUint KSaFlag = 1 << MTmCustom::ESaLineBreakClass;
const TUint KAiFlag = 1 << MTmCustom::EAiLineBreakClass;
// const TUint KXxFlag = 1 << MTmCustom::EXxLineBreakClass;
const TUint KCalSpaceFlag = 1 << TAvkonEditorCustomWrap::EAvkSpaceLineBreakClass;

// const TInt KUsualBreaks = KOpFlag | KPrFlag | KPoFlag | KNuFlag | KAlFlag | KIdFlag | KInFlag | KBbFlag | KB2Flag | KAiFlag;

struct TLineBreakRule
    {
    TUint iForbid;  // set bits represent forbidden breaks
    TUint iAllow;   // set bits represent allowed breaks
                    // bits not in iForbid or iAllow represent breaks allowed only when spaces are present
    };

const TUint KAllBreaks = 0xFFFFFFFF;
const TUint KUsualForbidden = KClFlag | KExFlag | KSyFlag | KIsFlag | KZwFlag;
const TUint KUsualAllowed = KOpFlag | KPrFlag | KPoFlag | KNuFlag | KAlFlag | KIdFlag | KInFlag | KBbFlag | KB2Flag | KAiFlag | KBaFlag;

// A table of break rules, indexed by the class of the character before the possible break.
static const TLineBreakRule TheLineBreakRuleTable[TAvkonEditorCustomWrap::EAvkLineBreakClasses] =
    {
    { KAllBreaks - KCmFlag,0 },                                                     // Op 0
    { KUsualForbidden | KNsFlag,KUsualAllowed - KPoFlag },                          // Cl 1
    { KUsualForbidden | KOpFlag,0 },                                                // Qu 2
    { KUsualForbidden, 0 },                                                         // Gl 3
    { KUsualForbidden, KUsualAllowed },                                             // Ns 4
    { KUsualForbidden, KUsualAllowed },                                             // Ex 5
    { KUsualForbidden, KUsualAllowed - KNuFlag },                                   // Sy 6
    { KUsualForbidden, KUsualAllowed - KNuFlag },                                   // Is 7
    { KUsualForbidden, KPrFlag | KPoFlag | KInFlag | KBbFlag | KB2Flag },           // Pr 8
    { KUsualForbidden, KUsualAllowed },                                             // Po 9
    { KUsualForbidden, KOpFlag | KPrFlag | KIdFlag | KBbFlag | KB2Flag },           // Nu 10
    { KUsualForbidden, KOpFlag | KPrFlag | KPoFlag | KIdFlag | KBbFlag | KB2Flag }, // Al 11
    { KUsualForbidden, KUsualAllowed - KPoFlag - KInFlag },                         // Id 12
    { KUsualForbidden, KUsualAllowed - KInFlag },                                   // In 13
    { KUsualForbidden, KUsualAllowed },                                             // Hy 14
    { KUsualForbidden, KUsualAllowed },                                             // Ba 15
    { KUsualForbidden, 0 },                                                         // Bb 16
    { KUsualForbidden | KB2Flag, KUsualAllowed },                                   // B2 17
    { KZwFlag, KAllBreaks },                                                        // Zw 18
    { KUsualForbidden, KOpFlag | KPrFlag | KPoFlag | KIdFlag | KBbFlag | KB2Flag }, // Cm 19
    { 0, 0, },                                                                      // Bk 20
    { 0, 0, },                                                                      // Cr 21
    { 0, 0, },                                                                      // Lf 22
    { 0, 0, },                                                                      // Sg 23
    { 0, 0, },                                                                      // Cb 24
    { 0, 0, },                                                                      // Sp 25
    { 0, 0, },                                                                      // Sa 26
    { KUsualForbidden, KOpFlag | KPrFlag | KPoFlag | KIdFlag | KBbFlag | KB2Flag }, // Ai 27
    { 0, 0, },                                                                      // Xx 28
    { KUsualForbidden, KUsualAllowed | KCalSpaceFlag },                             // CalSpace 29
    };

const TText KPrivateUseAreaStart = 0xE000;
const TText KPrivateUseAreaEnd = 0xF900;

/*

Avkon break rules for editors:

Break-before only: "+"
Break-after only:  ". , ? ! ; : - _" 
Before/After:      "# * @ & / \ ="

*/
TUint TAvkonEditorCustomWrap::LineBreakClass(TUint aCode,TUint& aRangeStart,TUint& aRangeEnd) const
    {
    aRangeStart = aCode;
    aRangeEnd = aCode + 1;

    TUint lineclass;
    if (TAknLineBreaker::IsSpecialVariantChar(aCode, aRangeStart, aRangeEnd, lineclass))
        {
        // if special line break classes are defined for each variant
        return lineclass;
        }

    switch (aCode)
        {
        case 0x0020: // unicode for space
            return EAvkSpaceLineBreakClass;
        case 0x0021: // unicode for exclamation mark    (!)
        case 0xff01: // unicode for fullwidth exclamation mark
            return MTmCustom::EBaLineBreakClass;
        case 0x002c: // unicode for comma               (,) deliberate fall through
        case 0x002d: // unicode for hyphen              (-) deliberate fall through
        case 0x002e: // unicode for fullstop            (.)
        case 0xff0c: // unicode for fullwidth comma
            aRangeStart=0x002c;
            aRangeEnd=0x002f;
            return MTmCustom::EBaLineBreakClass;
        case 0x3001: // unicode for ideographic comma
        case 0x3002: // unicode for idegraphic full stop
        case 0xff1f: // unicode for fullwidth question mark
            aRangeStart=0x002c;
            aRangeEnd=0x002f;
            return MTmCustom::EClLineBreakClass;
        case 0x003a: // unicode for colon               (:) deliberate fall through
        case 0x003b: // unicode for semi-colon          (;)
        case 0xff1a: // unicode for fullwidth colon
            aRangeStart=0x003a;
            aRangeEnd=0x003c;
            return MTmCustom::EBaLineBreakClass;
        case 0x003f: // unicode for question mark       (?) deliberate fall through
        case 0x005f: // unicode for underscore          (_)
            return MTmCustom::EBaLineBreakClass;
        case 0x002b: // unicode for plus        (+)
            return MTmCustom::EBbLineBreakClass;
        case 0x0023: // unicode for hash        (#) deliberate fall through
        case 0x0026: // unicode for ampersand   (&) deliberate fall through
        case 0x002a: // unicode for asterisk    (*) deliberate fall through
        case 0x002f: // unicode for fwd-slash   (/) deliberate fall through
        case 0x003d: // unicode for equals      (=) deliberate fall through
        case 0x0040: // unicode for 'at'        (@) deliberate fall through
        case 0x005c: // unicode for bk-slash    (\)
            return MTmCustom::EB2LineBreakClass;
        default:
            break; // carry on
        }

    // Allow break before and after PUA characters (required for pictographs).
    if ( aCode >= KPrivateUseAreaStart && aCode < KPrivateUseAreaEnd )
        {
        aRangeStart = KPrivateUseAreaStart;
        aRangeEnd = KPrivateUseAreaEnd;
        // this allows break before and after
        return MTmCustom::EIdLineBreakClass;
        }

    return MFormCustomWrap::LineBreakClass(aCode,aRangeStart,aRangeEnd);
    }

TBool TAvkonEditorCustomWrap::LineBreakPossible(TUint aPrevClass,TUint aNextClass,TBool aHaveSpaces) const
    {
    __ASSERT_DEBUG(!aHaveSpaces,Panic(EEikPanicUnexpectedSpaces)); // should be no codes->ESpLineBreakClass using this source
    if (aPrevClass >= EAvkLineBreakClasses || aNextClass >= EAvkLineBreakClasses)
        return FALSE;

    const TLineBreakRule& rule = TheLineBreakRuleTable[aPrevClass];
    TUint flag = 1 << aNextClass;
    if (rule.iForbid & flag)
        return FALSE;
    return aHaveSpaces || (rule.iAllow & flag);
    }
