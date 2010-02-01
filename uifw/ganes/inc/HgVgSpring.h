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

#ifndef HGVGSPRING_H_
#define HGVSPRING_H_

// INCLUDES
#include <e32base.h>
#include <e32std.h>


    NONSHARABLE_CLASS(THgVgSpring)
    {
        public:
                                
            THgVgSpring(TReal aSpringK, TReal aSpringDamping, 
                TReal aSpringMaxVelocity, TReal aPositionSnap,
                TReal aVelocitySnap);

            void SetConstants(TReal aSpringK, TReal aSpringDamping, 
                TReal aSpringMaxVelocity, TReal aPositionSnap,
                TReal aVelocitySnap);

            void Reset();
            void Reset(TReal aX, TReal aY);
            void SetXY(TReal aX, TReal aY);
            void SetEnd(TReal aX, TReal aY);
            void SetVelocity(TReal aVx, TReal aVy);
            TBool IntegratePhysics(TReal aDeltaTime, TBool aEndCondition);            
            TReal GetX() const;
            TReal GetY() const;
            TReal GetInterpolatedX() const;
            TReal GetInterpolatedY() const;
            TReal VelX() const;
            TReal VelY() const;
            TReal EndX() const;
            TReal EndY() const;            
            TReal StartX() const;
            TReal StartY() const;
            
        private:
                        
            TReal iPrevX, iPrevY;
            TReal iX, iY;
            TReal iEndX, iEndY;
            TReal iVelX, iVelY;
            TReal iAccumulator;
            TReal iSpringK;
            TReal iSpringDamping;
            TReal iMaxSpringVelocity;
            TReal iPositionSnap;
            TReal iVelocitySnap;
            TReal iStartX, iStartY;
        };


#endif /* HGVGSPRING_H */
