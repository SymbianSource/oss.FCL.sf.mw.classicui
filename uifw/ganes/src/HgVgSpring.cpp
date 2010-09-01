/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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

// INCLUDE FILES

#include "HgVgSpring.h"
#include "HgVgConstants.h"

#include <e32math.h>

using namespace HgVgConstants;


THgVgSpring::THgVgSpring(TReal aSpringK, TReal aSpringDamping, 
                TReal aSpringMaxVelocity, TReal aPositionSnap,
                TReal aVelocitySnap) : 
iPrevX(0), 
iPrevY(0),
iX(0), 
iY(0),
iEndX(0), 
iEndY(0),
iVelX(0), 
iVelY(0),
iAccumulator(0),
iSpringK(aSpringK),
iSpringDamping(aSpringDamping),
iMaxSpringVelocity(aSpringMaxVelocity),
iPositionSnap(aPositionSnap),
iVelocitySnap(aVelocitySnap),
iStartX(0),
iStartY(0)
    {
    
    }

void THgVgSpring::SetConstants(TReal aSpringK, TReal aSpringDamping, 
    TReal aSpringMaxVelocity, TReal aPositionSnap,
    TReal aVelocitySnap)
    {
    iSpringK = aSpringK;
    iSpringDamping = aSpringDamping;
    iMaxSpringVelocity = aSpringMaxVelocity;
    iPositionSnap = aPositionSnap;
    iVelocitySnap = aVelocitySnap;
    }


void THgVgSpring::Reset(TReal aX, TReal aY)
    {
    iEndX = aX;
    iEndY = aY;
    Reset();
    }

void THgVgSpring::Reset()
    {
    iPrevX = iX = iStartX = iEndX;
    iPrevY = iY = iStartY = iEndY;
    iAccumulator = 0;
    iVelX = 0;
    iVelY = 0;
    }

void THgVgSpring::SetXY(TReal aX, TReal aY)
    {
    iStartX = iPrevX = iX = aX;
    iStartY = iPrevY = iY = aY;
    }

void THgVgSpring::SetEnd(TReal aX, TReal aY)
    {
    iStartX = iEndX;
    iStartY = iEndY;
    iEndX = aX;
    iEndY = aY;
    }

void THgVgSpring::SetVelocity(TReal aVx, TReal aVy)
    {
    iVelX = aVx;
    iVelY = aVy;
    }

TBool THgVgSpring::IntegratePhysics(TReal aDeltaTime, TBool aEndCondition)
    {
    iAccumulator += aDeltaTime;    
    while (iAccumulator >= KTimeStep)
        {
        iPrevX = iX;
        iPrevY = iY;

        // calculate spring force F = -kx - bv
        TReal Fx = -(iX - iEndX) * iSpringK - iVelX * iSpringDamping;
        TReal Fy = -(iY - iEndY) * iSpringK - iVelY * iSpringDamping;
        
        // do euler integration
        iVelX += Fx * KTimeStep;
        iVelY += Fy * KTimeStep;
                
        // limit velocity to certain max
        if (Abs(iVelX) > iMaxSpringVelocity)
            iVelX = (iVelX < 0) ? -iMaxSpringVelocity : iMaxSpringVelocity;
        
        if (Abs(iVelY) > iMaxSpringVelocity)
            iVelY = (iVelY < 0) ? -iMaxSpringVelocity : iMaxSpringVelocity;

        // do euler integration
        iX += iVelX * KTimeStep;
        iY += iVelY * KTimeStep;
        
        // decrease accumulator
        iAccumulator -= KTimeStep;

        // snap to item if close enough and speed is small enough
        if (Abs(iX - iEndX) < iPositionSnap && Abs(iVelX) < iVelocitySnap &&
                Abs(iY - iEndY) < iPositionSnap && Abs(iVelY) < iVelocitySnap && aEndCondition)
            {
            Reset();
            return ETrue;
            }
                
        }
    
    return EFalse;
    }

TReal THgVgSpring::GetX() const
    {
    return iX;
    }

TReal THgVgSpring::GetY() const
    {
    return iY;
    }

TReal THgVgSpring::EndX() const
    {
    return iEndX;
    }

TReal THgVgSpring::EndY() const
    {
    return iEndY;
    }

TReal THgVgSpring::VelX() const
    {
    return iVelX;
    }

TReal THgVgSpring::VelY() const
    {
    return iVelY;
    }

TReal THgVgSpring::GetInterpolatedX() const
    {
    TReal a = iAccumulator / KTimeStep;
    return iX * (1.0 - a) + iPrevX * a;    
    }

TReal THgVgSpring::GetInterpolatedY() const
    {
    TReal a = iAccumulator / KTimeStep;
    return iY * (1.0 - a) + iPrevY * a;
    }

TReal THgVgSpring::StartX() const
    {
    return iStartX;
    }

TReal THgVgSpring::StartY() const
    {
    return iStartY;
    }


// End of File
