// dHeightfield Collider
//  Paul Cheyrou-Lagreze aka Tuan Kuranes 2006 Speed enhancements http://www.pop-3d.com
//  Martijn Buijs 2006 http://home.planet.nl/~buijs512/
// Based on Terrain & Cone contrib by:
//  Benoit CHAPEROT 2003-2004 http://www.jstarlab.com
//  Some code inspired by Magic Software


#include <ode/common.h>
#include <ode/collision.h>
#include <ode/matrix.h>
#include <ode/rotation.h>
#include <ode/odemath.h>
#include "collision_kernel.h"
#include "collision_std.h"
#include "collision_util.h"
#include "heightfield.h"

#define TERRAINTOL REAL(0.0f)

#define dMIN(A,B)  ((A)>(B) ? B : A)
#define dMAX(A,B)  ((A)>(B) ? A : B)


// Three-way MIN and MAX
#define dMIN3(A,B,C)	( (A)<(B) ? dMIN((A),(C)) : dMIN((B),(C)) )
#define dMAX3(A,B,C)	( (A)>(B) ? dMAX((A),(C)) : dMAX((B),(C)) )

#define dOPESIGN(a, op1, op2,b) \
    (a)[0] op1 op2 ((b)[0]); \
    (a)[1] op1 op2 ((b)[1]); \
    (a)[2] op1 op2 ((b)[2]);

#define dGeomRaySetNoNormalize(myRay, MyPoint, MyVector) {  \
    \
    dVector3Copy (MyPoint, myRay.final_posr->pos);   \
    myRay.final_posr->R[2] = MyVector[0];       \
    myRay.final_posr->R[6] = MyVector[1];       \
    myRay.final_posr->R[10] = MyVector[2];      \
    dGeomMoved (&myRay);                        \
            }

#define dGeomPlaneSetNoNormalize(MyPlane, MyPlaneDef) { \
    \
    MyPlane->p[0] = MyPlaneDef[0];  \
    MyPlane->p[1] = MyPlaneDef[1];  \
    MyPlane->p[2] = MyPlaneDef[2];  \
    MyPlane->p[3] = MyPlaneDef[3];  \
    dGeomMoved (MyPlane);           \
                    }
//////// dxHeightfieldData /////////////////////////////////////////////////////////////

// dxHeightfieldData constructor
dxHeightfieldData::dxHeightfieldData()
{
    //
}


// build Heightfield data
void dxHeightfieldData::SetData( int nWidthSamples, int nDepthSamples,
                                dReal fWidth, dReal fDepth,
                                dReal fScale, dReal fOffset, dReal fThickness,
                                int bWrapMode )
{


    // x,z bounds
    m_fWidth = fWidth;
    m_fDepth = fDepth;

    // cache half x,z bounds
    m_fHalfWidth = dDIV(fWidth,REAL( 2.0 ));
    m_fHalfDepth = dDIV(fDepth,REAL( 2.0 ));

    // scale and offset
    m_fScale = fScale;
    m_fOffset = fOffset;

    // infinite min height bounds
    m_fThickness = fThickness;

    // number of vertices per side
    m_nWidthSamples = nWidthSamples;
    m_nDepthSamples = nDepthSamples;

    m_fSampleWidth = m_fWidth / ( m_nWidthSamples - 1 );
    m_fSampleDepth = m_fDepth / ( m_nDepthSamples - 1 );

    m_fInvSampleWidth = dDIV(REAL(1.0),m_fSampleWidth);
    m_fInvSampleDepth = dDIV(REAL(1.0),m_fSampleDepth);

    // finite or repeated terrain?
    m_bWrapMode = bWrapMode;
}


// recomputes heights bounds
void dxHeightfieldData::ComputeHeightBounds()
{
    static int i;
    static dReal h;
    static dReal *data_float;

    data_float = (dReal*)m_pHeightData;
    m_fMinHeight = dInfinity;
    m_fMaxHeight = -dInfinity;

    for (i=0; i<m_nWidthSamples*m_nDepthSamples; i++)
    {
       h = data_float[i];
       if (h < m_fMinHeight)	m_fMinHeight = h;
       if (h > m_fMaxHeight)	m_fMaxHeight = h;
    }

    // scale and offset
    m_fMinHeight = dMUL(m_fMinHeight,m_fScale);
    m_fMaxHeight = dMUL(m_fMaxHeight,m_fScale);
    m_fMinHeight += m_fOffset;
    m_fMaxHeight += m_fOffset;

    // add thickness
    m_fMinHeight -= m_fThickness;
}


// returns whether point is over terrain Cell triangle?
bool dxHeightfieldData::IsOnHeightfield  ( const dReal * const CellOrigin, const dReal * const pos,  const bool isABC) const
{
    {
        const dReal MaxX = CellOrigin[0] + m_fSampleWidth;
        const dReal TolX = dMUL(m_fSampleWidth,TERRAINTOL);
        if ((pos[0]<CellOrigin[0]-TolX) || (pos[0]>MaxX+TolX))	
            return false;
    }

    {
        const dReal MaxZ = CellOrigin[2] + m_fSampleDepth;
        const dReal TolZ = dMUL(m_fSampleDepth,TERRAINTOL);
        if ((pos[2]<CellOrigin[2]-TolZ) || (pos[2]>MaxZ+TolZ))	
            return false;
    }

    // add X percentage position on cell and Z percentage position on cell
    const dReal pctTotal = dMUL((pos[0] - CellOrigin[0]),m_fInvSampleWidth )
        + dMUL((pos[2] - CellOrigin[2]),m_fInvSampleDepth);

    if (isABC)
    {
        if (pctTotal >= REAL(1.0) + TERRAINTOL)	
            return false;
        else	
            return true;
    }
    else if (pctTotal <= REAL(1.0) - TERRAINTOL)	
    {
        return false;
    }
    return true;
}
// returns whether point is over terrain Cell triangle?
bool dxHeightfieldData::IsOnHeightfield2  ( const dReal * const CellOrigin, const dReal * const pos,  const bool isABC) const
{
    dReal MaxX, MinX;
    dReal MaxZ, MinZ;
    if (isABC)
    {
        // point A
        MinX = CellOrigin[0];
        MaxX = CellOrigin[0] + m_fSampleWidth;

        MinZ = CellOrigin[2];
        MaxZ = CellOrigin[2] + m_fSampleDepth;
    }
    else
    {
        // point D
        MinX = CellOrigin[0] - m_fSampleWidth;
        MaxX = CellOrigin[0];

        MinZ = CellOrigin[2] - m_fSampleDepth;
        MaxZ = CellOrigin[2];
    }

    // check if inside CELL
    {
        const dReal TolX = dMUL(m_fSampleWidth,TERRAINTOL);
        if ((pos[0]<MinX-TolX) || (pos[0]>MaxX+TolX))	
            return false;
    }

    {
        const dReal TolZ = dMUL(m_fSampleDepth,TERRAINTOL);
        if ((pos[2]<MinZ-TolZ) || (pos[2]>MaxZ+TolZ))	
            return false;
    }

    // Sum up X percentage position on cell and Z percentage position on cell
    const dReal pctTotal = dMUL((pos[0] - MinX),m_fInvSampleWidth) 
        + dMUL((pos[2] - MinZ),m_fInvSampleDepth);

    // check if inside respective Triangle of Cell
    if (isABC)	
    {
        if (pctTotal >= REAL(1.0) + TERRAINTOL)	
            return false;
        else	
            return true;
    }
    else if (pctTotal <= REAL(1.0) - TERRAINTOL)	
    {
        return false;
    }
    return true;
}


// returns height at given sample coordinates
dReal dxHeightfieldData::GetHeight( int x, int z )
{
    static dReal h;
    static dReal *data_float;

    if ( m_bWrapMode == 0 )
    {
        // Finite
        if ( x < 0 ) x = 0;
        if ( z < 0 ) z = 0;
        if ( x > m_nWidthSamples - 1 ) x = m_nWidthSamples - 1;
        if ( z > m_nDepthSamples - 1 ) z = m_nDepthSamples - 1;
    }
    else
    {
        // Infinite
        x %= m_nWidthSamples - 1;
        z %= m_nDepthSamples - 1;
        if ( x < 0 ) x += m_nWidthSamples - 1;
        if ( z < 0 ) z += m_nDepthSamples - 1;
    }

    data_float = (dReal*)m_pHeightData;
    h = data_float[x+(z * m_nWidthSamples)];

    return dMUL(h,m_fScale) + m_fOffset;
}


// returns height at given coordinates
dReal dxHeightfieldData::GetHeight( dReal x, dReal z )
{
    int nX	= dMUL( x,m_fInvSampleWidth )>>QFACTOR;
    int nZ	= dMUL( z,m_fInvSampleDepth )>>QFACTOR;

    dReal dx = dMUL(( x - ( nX * m_fSampleWidth ) ),m_fInvSampleWidth);
    dReal dz = dMUL(( z - ( nZ * m_fSampleDepth ) ),m_fInvSampleDepth);



    dReal y, y0;

    if ( dx + dz < REAL( 1.0 ) )
    {
        y0 = GetHeight( nX, nZ );

        y = y0 + dMUL(( GetHeight( nX + 1, nZ ) - y0 ),dx)
            + dMUL(( GetHeight( nX, nZ + 1 ) - y0 ),dz);
    }
    else
    {
        y0 = GetHeight( nX + 1, nZ + 1 );

        y = y0	+ dMUL(( GetHeight( nX + 1, nZ ) - y0 ),( REAL(1.0f) - dz )) +
            dMUL(( GetHeight( nX, nZ + 1 ) - y0 ),( REAL(1.0f) - dx ));
    }

    return y;
}


// dxHeightfieldData destructor
dxHeightfieldData::~dxHeightfieldData()
{
    static dReal *data_float;


    if ( m_bCopyHeightData )
    {
        data_float = (dReal*)m_pHeightData;
        delete [] data_float;     
    }
}


//////// dxHeightfield /////////////////////////////////////////////////////////////////


// dxHeightfield constructor
dxHeightfield::dxHeightfield( dSpaceID space,
                             dHeightfieldDataID data,
                             int bPlaceable )			:
    dxGeom( space, bPlaceable ),
    tempPlaneBuffer(0),
    tempPlaneBufferSize(0),
    tempTriangleBuffer(0),
    tempTriangleBufferSize(0),
    tempHeightBuffer(0),
    tempHeightBufferSizeX(0),
    tempHeightBufferSizeZ(0)
{
    type = dHeightfieldClass;
    this->m_p_data = data;
}


// compute axis aligned bounding box
void dxHeightfield::computeAABB()
{
    const dxHeightfieldData *d = m_p_data;

    if ( d->m_bWrapMode == 0 )
    {
        // Finite
        if ( gflags & GEOM_PLACEABLE )
        {
            dReal dx[6], dy[6], dz[6];

            // Y-axis
            dy[0] = dMUL( final_posr->R[ 1],d->m_fMinHeight );
            dy[1] = dMUL( final_posr->R[ 5],d->m_fMinHeight );
            dy[2] = dMUL( final_posr->R[ 9],d->m_fMinHeight );
            dy[3] = dMUL( final_posr->R[ 1],d->m_fMaxHeight );
            dy[4] = dMUL( final_posr->R[ 5],d->m_fMaxHeight );
            dy[5] = dMUL( final_posr->R[ 9],d->m_fMaxHeight );


            // X-axis
            dx[0] = dMUL( final_posr->R[ 0],-d->m_fHalfWidth );
            dx[1] = dMUL( final_posr->R[ 4],-d->m_fHalfWidth );
            dx[2] = dMUL( final_posr->R[ 8],-d->m_fHalfWidth );
            dx[3] = dMUL( final_posr->R[ 0],d->m_fHalfWidth );
            dx[4] = dMUL( final_posr->R[ 4],d->m_fHalfWidth );
            dx[5] = dMUL( final_posr->R[ 8],d->m_fHalfWidth );

            // Z-axis
            dz[0] = dMUL( final_posr->R[ 2],-d->m_fHalfDepth );
            dz[1] = dMUL( final_posr->R[ 6],-d->m_fHalfDepth );
            dz[2] = dMUL( final_posr->R[10],-d->m_fHalfDepth );
            dz[3] = dMUL( final_posr->R[ 2],d->m_fHalfDepth );
            dz[4] = dMUL( final_posr->R[ 6],d->m_fHalfDepth );
            dz[5] = dMUL( final_posr->R[10],d->m_fHalfDepth );


            // X extents
            aabb[0] = final_posr->pos[0] +
                dMIN3( dMIN( dx[0], dx[3] ), dMIN( dy[0], dy[3] ), dMIN( dz[0], dz[3] ) );
            aabb[1] = final_posr->pos[0] +
                dMAX3( dMAX( dx[0], dx[3] ), dMAX( dy[0], dy[3] ), dMAX( dz[0], dz[3] ) );

            // Y extents
            aabb[2] = final_posr->pos[1] +
                dMIN3( dMIN( dx[1], dx[4] ), dMIN( dy[1], dy[4] ), dMIN( dz[1], dz[4] ) );
            aabb[3] = final_posr->pos[1] +
                dMAX3( dMAX( dx[1], dx[4] ), dMAX( dy[1], dy[4] ), dMAX( dz[1], dz[4] ) );

            // Z extents
            aabb[4] = final_posr->pos[2] +
                dMIN3( dMIN( dx[2], dx[5] ), dMIN( dy[2], dy[5] ), dMIN( dz[2], dz[5] ) );
            aabb[5] = final_posr->pos[2] +
                dMAX3( dMAX( dx[2], dx[5] ), dMAX( dy[2], dy[5] ), dMAX( dz[2], dz[5] ) );
        }
        else
        {

            aabb[0] = -d->m_fHalfWidth;		aabb[1] = +d->m_fHalfWidth;
            aabb[2] = d->m_fMinHeight;		aabb[3] = d->m_fMaxHeight;
            aabb[4] = -d->m_fHalfDepth;		aabb[5] = +d->m_fHalfDepth;


        }
    }
    else
    {
        // Infinite
        if ( gflags & GEOM_PLACEABLE )
        {
            aabb[0] = -dInfinity;			aabb[1] = +dInfinity;
            aabb[2] = -dInfinity;			aabb[3] = +dInfinity;
            aabb[4] = -dInfinity;			aabb[5] = +dInfinity;
        }
        else
        {
            aabb[0] = -dInfinity;			aabb[1] = +dInfinity;
            aabb[2] = d->m_fMinHeight;		aabb[3] = d->m_fMaxHeight;
            aabb[4] = -dInfinity;			aabb[5] = +dInfinity;
        }
    }

}


// dxHeightfield destructor
dxHeightfield::~dxHeightfield()
{
    delete [] tempTriangleBuffer;

    for (unsigned int k = 0; k < tempPlaneBufferSize; k++)
    {
        delete tempPlaneBuffer[k];
    }
    delete [] tempPlaneBuffer;

    resetHeightBuffer();
}

void dxHeightfield::resetHeightBuffer()
{
    const size_t xSize = tempHeightBufferSizeX;
    for (size_t x = 0; xSize < x; x++)
    {
        delete [] tempHeightBuffer[x];
    }
    delete [] tempHeightBuffer;
}
//////// Heightfield data interface ////////////////////////////////////////////////////


EXPORT_C dHeightfieldDataID dGeomHeightfieldDataCreate()
{
    return new dxHeightfieldData();
}


EXPORT_C void dGeomHeightfieldDataBuildCallback( dHeightfieldDataID d,
                                       void* pUserData, dHeightfieldGetHeight* pCallback,
                                       dReal width, dReal depth, int widthSamples, int depthSamples,
                                       dReal scale, dReal offset, dReal thickness, int bWrap )
{


    // callback
    d->m_nGetHeightMode = 0;
    d->m_pUserData = pUserData;
    d->m_pGetHeightCallback = pCallback;

    // set info
    d->SetData( widthSamples, depthSamples, width, depth, scale, offset, thickness, bWrap );

    // default bounds
    d->m_fMinHeight = -dInfinity;
    d->m_fMaxHeight = dInfinity;
}

EXPORT_C void dGeomHeightfieldDataBuildSingle( dHeightfieldDataID d,
                                     const float *pHeightData, int bCopyHeightData,
                                     dReal width, dReal depth, int widthSamples, int depthSamples,
                                     dReal scale, dReal offset, dReal thickness, int bWrap )
{


    // set info
    d->SetData( widthSamples, depthSamples, width, depth, scale, offset, thickness, bWrap );
    d->m_nGetHeightMode = 3;
    d->m_bCopyHeightData = bCopyHeightData;

    if ( d->m_bCopyHeightData == 0 )
    {
        // Data is referenced only.
        d->m_pHeightData = pHeightData;
    }
    else
    {
        // We own the height data, allocate storage
        d->m_pHeightData = new dReal[ d->m_nWidthSamples * d->m_nDepthSamples ];


        // Copy data.
        memcpy( (void*)d->m_pHeightData, pHeightData,
            sizeof( dReal ) * d->m_nWidthSamples * d->m_nDepthSamples );
    }

    // Find height bounds
    d->ComputeHeightBounds();
}


EXPORT_C void dGeomHeightfieldDataSetBounds( dHeightfieldDataID d, dReal minHeight, dReal maxHeight )
{

    d->m_fMinHeight = dMUL( minHeight,d->m_fScale ) + d->m_fOffset - d->m_fThickness;
    d->m_fMaxHeight = dMUL( maxHeight,d->m_fScale ) + d->m_fOffset;
}


EXPORT_C void dGeomHeightfieldDataDestroy( dHeightfieldDataID d )
{
    delete d;
}


//////// Heightfield geom interface ////////////////////////////////////////////////////


EXPORT_C dGeomID dCreateHeightfield( dSpaceID space, dHeightfieldDataID data, int bPlaceable )
{
    return new dxHeightfield( space, data, bPlaceable );
}


EXPORT_C void dGeomHeightfieldSetHeightfieldData( dGeomID g, dHeightfieldDataID d )
{
    dxHeightfield* geom = (dxHeightfield*) g;
    geom->data = d;
}


EXPORT_C dHeightfieldDataID dGeomHeightfieldGetHeightfieldData( dGeomID g )
{
    dxHeightfield* geom = (dxHeightfield*) g;
    return geom->m_p_data;
}

//////// dxHeightfield /////////////////////////////////////////////////////////////////


// Typedef for generic 'get point depth' function
typedef dReal dGetDepthFn( dGeomID g, dReal x, dReal y, dReal z );



static inline bool DescendingPlaneSort(const HeightFieldPlane * const A, const HeightFieldPlane * const B)
{
    return ((A->maxAAAB - B->maxAAAB) > dEpsilon);
}

void dxHeightfield::sortPlanes(const size_t numPlanes)
{
    bool has_swapped = true;
    do
    {
        has_swapped = false;//reset flag
        for (size_t i = 0; i < numPlanes - 1; i++)
        {
            //if they are in the wrong order
            if (DescendingPlaneSort(tempPlaneBuffer[i], tempPlaneBuffer[i + 1]))
            { 
                //exchange them
                HeightFieldPlane * tempPlane = tempPlaneBuffer[i];
                tempPlaneBuffer[i] = tempPlaneBuffer[i + 1];
                tempPlaneBuffer[i + 1] = tempPlane;

                //we have swapped at least once, list may not be sorted yet
                has_swapped = true;
            }
        }
    }    //if no swaps were made during this pass, the list has been sorted
    while (has_swapped);
}

int dxHeightfield::dCollideHeightfieldZone( const int minX, const int maxX, const int minZ, const int maxZ, 
                                           dxGeom* o2, const int numMaxContactsPossible,
                                           int flags, dContactGeom* contact, 
                                           int skip )
{
	dContactGeom *pContact = 0;
    int  x, z;
    // check if not above or inside terrain first
    // while filling a heightmap partial temporary buffer
    const unsigned int numX = (maxX - minX) + 1;
    const unsigned int numZ = (maxZ - minZ) + 1;
    const dReal minO2Height = o2->aabb[2];
    const dReal maxO2Height = o2->aabb[3];
    unsigned int x_local, z_local;
    dReal maxY = - dInfinity;
    dReal minY = dInfinity;
    // localize and const for faster access
    const dReal cfSampleWidth = m_p_data->m_fSampleWidth;
    const dReal cfSampleDepth = m_p_data->m_fSampleDepth;
    {
        if (tempHeightBufferSizeX < numX || tempHeightBufferSizeZ < numZ)
        {
            resetHeightBuffer();
            tempHeightBufferSizeX = numX;
            tempHeightBufferSizeZ = numZ;
            tempHeightBuffer = new HeightFieldVertex *[numX];
            for ( x_local = 0; x_local < numX; x_local++)
            {
                tempHeightBuffer[x_local] = new HeightFieldVertex [numZ];     
            }
        }

        dReal Xpos, Ypos;
        Xpos = minX*cfSampleWidth;


        for ( x = minX, x_local = 0; x_local < numX; x++, x_local++)
        {
            const dReal c_Xpos = Xpos;
            HeightFieldVertex *HeightFieldRow = tempHeightBuffer[x_local];
            Ypos = minZ * cfSampleDepth;
            for ( z = minZ, z_local = 0; z_local < numZ; z++, z_local++)
            {
                const dReal h = m_p_data->GetHeight(x, z);
                HeightFieldRow[z_local].vertex[0] = c_Xpos;
                HeightFieldRow[z_local].vertex[1] = h;
                HeightFieldRow[z_local].vertex[2] = Ypos;
                

                maxY = dMAX(maxY, h);
                minY = dMIN(minY, h);


                Ypos += cfSampleDepth;
            }
            Xpos += cfSampleWidth;
        }
        if (minO2Height - maxY > -dEpsilon )
        {
			//totally above heightfield
            return 0;
        }
		if (minY - maxO2Height > -dEpsilon )
		{
			// totally under heightfield
			pContact = CONTACT(contact, 0);

			pContact->pos[0] = o2->final_posr->pos[0];
			pContact->pos[1] = minY;
			pContact->pos[2] = o2->final_posr->pos[2];

			pContact->normal[0] = 0;
			pContact->normal[1] = REAL(-1.0);
			pContact->normal[2] = 0;

			pContact->depth =  minY - maxO2Height;

			return 1;
		}
    }
    int numTerrainContacts = 0;
    // get All Planes that could collide against.
    dColliderFn *geomRayNCollider = 0;
    dColliderFn *geomNPlaneCollider = 0;
    dGetDepthFn *geomNDepthGetter = 0;

    int max_collisionContact = numMaxContactsPossible;
    switch (o2->type)
    {
    case dRayClass:
        geomRayNCollider		= NULL;
        geomNPlaneCollider	    = dCollideRayPlane;
        geomNDepthGetter		= NULL;
        //max_collisionContact    = 1;
        break;

    case dSphereClass:
        geomRayNCollider		= dCollideRaySphere;
        geomNPlaneCollider  	= dCollideSpherePlane;
        geomNDepthGetter		= dGeomSpherePointDepth;
        //max_collisionContact    = 3;
        break;

    case dBoxClass:
        geomRayNCollider		= dCollideRayBox;
        geomNPlaneCollider	    = dCollideBoxPlane;
        geomNDepthGetter		= dGeomBoxPointDepth;
        //max_collisionContact    = 8;
        break;

    case dCapsuleClass:
        geomRayNCollider		= dCollideRayCapsule;
        geomNPlaneCollider  	= dCollideCapsulePlane;
        geomNDepthGetter		= dGeomCapsulePointDepth;
        // max_collisionContact    = 3;
        break;

    case dCylinderClass:
        geomRayNCollider		= dCollideRayCylinder;
        geomNPlaneCollider	    = dCollideCylinderPlane;
        geomNDepthGetter		= NULL;// TODO: dGeomCCylinderPointDepth
        //max_collisionContact    = 3;
        break;

    case dConvexClass:
        geomRayNCollider		= dCollideRayConvex;
        geomNPlaneCollider  	= dCollideConvexPlane;
        geomNDepthGetter		= NULL;// TODO: dGeomConvexPointDepth;
        //max_collisionContact    = 3;
        break;

    default:
        	// Shouldn't ever get here.
        break;

    }


    const int numMaxContacts = dMIN (max_collisionContact, HEIGHTFIELDMAXCONTACTPERCELL);
    
    dxPlane myplane(0,0,0,0,0);
    dxPlane* sliding_plane = &myplane;
    dContactGeom *PlaneContact = m_p_data->m_contacts;    
    flags = (flags & 0xffff0000) | HEIGHTFIELDMAXCONTACTPERCELL;
    dReal triplane[4];
    int i;

    // check some trivial case.
    // Vector Up plane
    if (maxY - minY < dEpsilon)
    {
        // it's a single plane.
        triplane[0] = 0;
        triplane[1] = REAL(1.0);
        triplane[2] = 0;
        triplane[3] =  minY;
        dGeomPlaneSetNoNormalize (sliding_plane, triplane);
        // find collision and compute contact points
        const int numPlaneContacts = geomNPlaneCollider (o2, sliding_plane, flags, PlaneContact, sizeof(dContactGeom));
        for (i = 0; i < numPlaneContacts; i++)
        {
            pContact = CONTACT(contact, numTerrainContacts*skip);
            const dVector3 &pCPos = PlaneContact[i].pos;
            dVector3Copy (pCPos, pContact->pos);
            dOPESIGN(pContact->normal, =, -, triplane);

            pContact->depth = PlaneContact[i].depth;
            numTerrainContacts++;
            if (numTerrainContacts > numMaxContactsPossible)
                break;
        }
        return numTerrainContacts;
    }
    // unique plane
    {
        // check for very simple plane heightfield
        dReal minXHeightDelta = dInfinity, maxXHeightDelta = - dInfinity;
        dReal minZHeightDelta = dInfinity, maxZHeightDelta = - dInfinity;


        dReal lastXHeight = tempHeightBuffer[0][0].vertex[1];
        for ( x_local = 1; x_local < numX; x_local++)
        {
            HeightFieldVertex *HeightFieldRow = tempHeightBuffer[x_local];

            const dReal deltaX = HeightFieldRow[0].vertex[1] - lastXHeight;

            maxXHeightDelta = dMAX (maxXHeightDelta,  deltaX);
            minXHeightDelta = dMIN (minXHeightDelta,  deltaX);

            dReal lastZHeight = HeightFieldRow[0].vertex[1];
            for ( z_local = 1; z_local < numZ; z_local++)
            {
                const dReal deltaZ = (HeightFieldRow[z_local].vertex[1] - lastZHeight);

                maxZHeightDelta = dMAX (maxZHeightDelta,  deltaZ);
                minZHeightDelta = dMIN (minZHeightDelta,  deltaZ);

            }
        }

        if (maxZHeightDelta - minZHeightDelta < dEpsilon && 
            maxXHeightDelta - minXHeightDelta < dEpsilon )
        {
            // it's a single plane.
            const dVector3 &A = tempHeightBuffer[0][0].vertex;
            const dVector3 &B = tempHeightBuffer[1][0].vertex;
            const dVector3 &C = tempHeightBuffer[0][1].vertex;

            // define 2 edges and a point that will define collision plane
            {
                dVector3 Edge1, Edge2; 
                dVector3Subtract(C, A, Edge1);
                dVector3Subtract(B, A, Edge2);
                dVector3Cross(Edge1, Edge2, triplane);
            }

            // Define Plane
            // Normalize plane normal
            const dReal dinvlength = dDIV(REAL(1.0),dVector3Length(triplane));
            triplane[0] = dMUL(triplane[0],dinvlength);
            triplane[1] = dMUL(triplane[1],dinvlength);
            triplane[2] = dMUL(triplane[2],dinvlength);
            // get distance to origin from plane 
            triplane[3] = dVector3Dot(triplane, A);

            dGeomPlaneSetNoNormalize (sliding_plane, triplane);
            // find collision and compute contact points
            const int numPlaneContacts = geomNPlaneCollider (o2, sliding_plane, flags, PlaneContact, sizeof(dContactGeom));
            for (i = 0; i < numPlaneContacts; i++)
            {
                pContact = CONTACT(contact, numTerrainContacts*skip);
                const dVector3 &pCPos = PlaneContact[i].pos;
                dVector3Copy (pCPos, pContact->pos);
                dOPESIGN(pContact->normal, =, -, triplane);

                pContact->depth = PlaneContact[i].depth;
                numTerrainContacts++;
                if (numTerrainContacts > numMaxContactsPossible)
                    break;
            }
            return numTerrainContacts;
        }
    }


    const unsigned int numTriMax = (maxX - minX) * (maxZ - minZ) * 2;
    if (tempTriangleBufferSize < numTriMax)
    {
        delete [] tempTriangleBuffer;
        tempTriangleBufferSize = numTriMax;
        tempTriangleBuffer = new HeightFieldTriangle[numTriMax];
    }
    
    // Sorting triangle/plane  resulting from heightfield zone
    // Perhaps that would be necessary in case of too much limited
    // maximum contact point...
    // or in complex mesh case (trimesh and convex)
    // need some test or insights on this before enabling this.
    const bool isContactNumPointsLimited = 
        true;
    // (numMaxContacts < 8)
    //    || o2->type == dConvexClass
    //    || o2->type == dTriMeshClass
    //    || (numMaxContacts < (int)numTriMax)       
        


    // if small heightfield triangle related to O2 colliding
    // or no Triangle colliding at all.
    bool needFurtherPasses = (o2->type == dTriMeshClass);
    //compute Ratio between Triangle size and O2 aabb size
	// no FurtherPasses are needed in ray class
    if (o2->type != dRayClass  && needFurtherPasses == false)
    {
        const dReal xratio = dMUL((o2->aabb[1] - o2->aabb[0]),m_p_data->m_fInvSampleWidth);
        if (xratio > REAL(1.5))
            needFurtherPasses = true;
        else
        {
            const dReal zratio = dMUL((o2->aabb[5] - o2->aabb[4]),m_p_data->m_fInvSampleDepth);
            if (zratio > REAL(1.5))
                needFurtherPasses = true;
        }

    }

    unsigned int numTri = 0;
    HeightFieldVertex *A, *B, *C, *D;
    /*    (y is up)
         A--------B-...x
         |       /|
         |      / |
         |     /  |
         |    /   |
         |   /    |
         |  /     |
         | /      |
         |/       |
         C--------D   
         .
         .
         .
         z
    */  
    // keep only triangle that does intersect geom
    for ( x = minX, x_local = 0; x < maxX; x++, x_local++)
    {
        HeightFieldVertex *HeightFieldRow      = tempHeightBuffer[x_local];
        HeightFieldVertex *HeightFieldNextRow  = tempHeightBuffer[x_local + 1];

        // First A
        C = &HeightFieldRow    [0];
        // First B
        D = &HeightFieldNextRow[0];
        for ( z = minZ, z_local = 0; z < maxZ; z++, z_local++)
        {
            A = C;
            B = D;

            C = &HeightFieldRow    [z_local + 1];
            D = &HeightFieldNextRow[z_local + 1];

            const dReal AHeight = A->vertex[1];
            const dReal BHeight = B->vertex[1];
            const dReal CHeight = C->vertex[1];
            const dReal DHeight = D->vertex[1];

            const bool isACollide = 0 < AHeight - minO2Height;
            const bool isBCollide = 0 < BHeight - minO2Height;
            const bool isCCollide = 0 < CHeight - minO2Height;
            const bool isDCollide = 0 < DHeight - minO2Height;

            A->state = !(isACollide);
            B->state = !(isBCollide);
            C->state = !(isCCollide);
            D->state = !(isCCollide);

            if (isACollide || isBCollide || isCCollide)
            {
                HeightFieldTriangle * const CurrTriUp = &tempTriangleBuffer[numTri++];

                CurrTriUp->state = false;

                // changing point order here implies to change it in isOnHeightField
                CurrTriUp->vertices[0] = A;
                CurrTriUp->vertices[1] = B;
                CurrTriUp->vertices[2] = C;

                if (isContactNumPointsLimited)
                    CurrTriUp->setMinMax();
                CurrTriUp->isUp = true;
            }

            if (isBCollide || isCCollide || isDCollide)
            {
                HeightFieldTriangle * const CurrTriDown = &tempTriangleBuffer[numTri++];

                CurrTriDown->state = false;
                // changing point order here implies to change it in isOnHeightField

                CurrTriDown->vertices[0] = D;
                CurrTriDown->vertices[1] = B;
                CurrTriDown->vertices[2] = C;


                if (isContactNumPointsLimited)
                    CurrTriDown->setMinMax();
                CurrTriDown->isUp = false;
            }


            if (needFurtherPasses &&
                (isBCollide || isCCollide)
                &&
                (AHeight - CHeight > 0 &&
                 AHeight - BHeight > 0 &&
                 DHeight - CHeight > 0 &&
                 DHeight - BHeight > 0))
            {
                // That means Edge BC is concave, therefore
                // BC Edge and B and C vertices cannot collide

                B->state = true;
                C->state = true;
            }
            // should find a way to check other edges (AB, BD, CD) too for concavity
        }
    }

    // at least on triangle should intersect geom

    // pass1: VS triangle as Planes
    // Group Triangle by same plane definition
    // as Terrain often has many triangles using same plane definition
    // then collide against that list of triangles.
    {

        dVector3 Edge1, Edge2;
        //compute all triangles normals.
        for (unsigned int k = 0; k < numTri; k++)
        {
            HeightFieldTriangle * const itTriangle = &tempTriangleBuffer[k];

            // define 2 edges and a point that will define collision plane
            dVector3Subtract(itTriangle->vertices[2]->vertex, itTriangle->vertices[0]->vertex, Edge1);
            dVector3Subtract(itTriangle->vertices[1]->vertex, itTriangle->vertices[0]->vertex, Edge2);

            // find a perpendicular vector to the triangle
            if  (itTriangle->isUp)
                dVector3Cross(Edge1, Edge2, triplane);
            else
                dVector3Cross(Edge2, Edge1, triplane);

            // Define Plane
            // Normalize plane normal
            const dReal dinvlength = dDIV(1,dVector3Length(triplane));
            triplane[0] = dMUL(triplane[0],dinvlength);
            triplane[1] = dMUL(triplane[1],dinvlength);
            triplane[2] = dMUL(triplane[2],dinvlength);
            // get distance to origin from plane 
            triplane[3] = dVector3Dot(triplane, itTriangle->vertices[0]->vertex);

            // saves normal for collision check (planes, triangles, vertices and edges.)
            dVector3Copy(triplane, itTriangle->planeDef);
            // saves distance for collision check (planes, triangles, vertices and edges.)
            itTriangle->planeDef[3] = triplane[3];
        }

        // group by Triangles by Planes sharing shame plane definition
        if (tempPlaneBufferSize  < numTri)
        {
            delete [] tempPlaneBuffer;
            tempPlaneBufferSize = numTri;
            tempPlaneBuffer = new HeightFieldPlane *[numTri];

            for (unsigned int k = 0; k < tempPlaneBufferSize; k++)
            {
                tempPlaneBuffer[k] = new HeightFieldPlane();
            }
        }
        unsigned int numPlanes = 0;
        for (unsigned int k = 0; k < numTri; k++)
        {
            HeightFieldTriangle * const tri_base = &tempTriangleBuffer[k];

            if (tri_base->state == true)
                continue;// already tested or added to plane list.

            HeightFieldPlane * const currPlane = tempPlaneBuffer[numPlanes];
            currPlane->resetTriangleListSize(numTri - k);
            currPlane->addTriangle(tri_base);
            // saves normal for collision check (planes, triangles, vertices and edges.)
            dVector3Copy(tri_base->planeDef, currPlane->planeDef);
            // saves distance for collision check (planes, triangles, vertices and edges.)
            currPlane->planeDef[3]= tri_base->planeDef[3];

            const dReal normx = tri_base->planeDef[0];
            const dReal normy = tri_base->planeDef[1];
            const dReal normz = tri_base->planeDef[2];
            const dReal dist = tri_base->planeDef[3];

            for (unsigned int m = k + 1; m < numTri; m++)
            {

                HeightFieldTriangle * const tri_test = &tempTriangleBuffer[m];
                if (tri_test->state == true)
                    continue;// already tested or added to plane list.

                // normals and distance are the same.
                if (
                    dFabs(normy - tri_test->planeDef[1]) < dEpsilon &&  
                    dFabs(dist  - tri_test->planeDef[3]) < dEpsilon &&
                    dFabs(normx - tri_test->planeDef[0]) < dEpsilon && 
                    dFabs(normz - tri_test->planeDef[2]) < dEpsilon
                    )
                {
                    currPlane->addTriangle (tri_test);
                    tri_test->state = true;
                }
            }

            tri_base->state = true;
            if (isContactNumPointsLimited)
                currPlane->setMinMax();

            numPlanes++;
        }

        // sort planes
        if (isContactNumPointsLimited)
            sortPlanes(numPlanes);

        for (unsigned int k = 0; k < numPlanes; k++)
        {
            HeightFieldPlane * const itPlane = tempPlaneBuffer[k];

            //set Geom
            dGeomPlaneSetNoNormalize (sliding_plane,  itPlane->planeDef);
            //dGeomPlaneSetParams (sliding_plane, triangle_Plane[0], triangle_Plane[1], triangle_Plane[2], triangle_Plane[3]);
            // find collision and compute contact points
            bool didCollide = false;
            const int numPlaneContacts = geomNPlaneCollider (o2, sliding_plane, flags, PlaneContact, sizeof(dContactGeom));
            const size_t planeTriListSize = itPlane->trianglelistCurrentSize;
            for (i = 0; i < numPlaneContacts; i++)
            {
                // Check if contact point found in plane is inside Triangle.
                const dVector3 &pCPos = PlaneContact[i].pos;
                bool isOnOneOfTrianglePlane = false;
                for (size_t b = 0; planeTriListSize > b; b++)
                {  
                    if (m_p_data->IsOnHeightfield2 (itPlane->trianglelist[b]->vertices[0]->vertex, 
                                                    pCPos, 
                                                    itPlane->trianglelist[b]->isUp))
                    {
                        isOnOneOfTrianglePlane = true;
                        break;
                    }
                }
                if ( isOnOneOfTrianglePlane)
                {
                    pContact = CONTACT(contact, numTerrainContacts*skip);
                    dVector3Copy(pCPos, pContact->pos);
                    dOPESIGN(pContact->normal, =, -, itPlane->planeDef);
                    pContact->depth = PlaneContact[i].depth;
                    didCollide = true;
                    numTerrainContacts++;
                    if ( numTerrainContacts == numMaxContacts ) 
                        return numTerrainContacts;
                }
            }
            if (didCollide)
            {
                for (size_t b = 0; planeTriListSize > b; b++)
                {                      
                    // flag Triangles Vertices as collided 
                    // to prevent any collision test of those
                    for (i = 0; i < 3; i++)
                        itPlane->trianglelist[b]->vertices[i]->state = true;
                }
            }
            else 
            {
                // flag triangle as not collided so that Vertices or Edge
                // of that triangles will be checked.
                for (size_t b = 0; planeTriListSize > b; b++)
                { 
                    itPlane->trianglelist[b]->state = false;
                }
            }
        }
    }
    

   
    // pass2: VS triangle vertices
    if (needFurtherPasses)
    {
        dxRay tempRay(0, 1); 
        dReal depth;
        bool vertexCollided;
        //
        // Find Contact Penetration Depth of each vertices
        //
        for (unsigned int k = 0; k < numTri; k++)
        {
            const HeightFieldTriangle * const itTriangle = &tempTriangleBuffer[k];
            if (itTriangle->state == true)
                continue;// plane triangle did already collide.

            for (size_t i = 0; i < 3; i++)
            {
                HeightFieldVertex *vertex = itTriangle->vertices[i];
                if (vertex->state == true)
                    continue;// vertice did already collide.

                vertexCollided = false;
                const dVector3 &triVertex = vertex->vertex;
                if ( geomNDepthGetter )
                {
                    depth = geomNDepthGetter( o2,
                        triVertex[0], triVertex[1], triVertex[2] );
                    if (depth + dEpsilon < 0)
                        vertexCollided = true;
                }
                else
                {
                    // We don't have a GetDepth function, so do a ray cast instead.
                    // NOTE: This isn't ideal, and a GetDepth function should be
                    // written for all geom classes.
                    tempRay.length = (minO2Height - triVertex[1]) * REAL(1000.f);

                    //dGeomRaySet( &tempRay, pContact->pos[0], pContact->pos[1], pContact->pos[2],
                    //    - itTriangle->Normal[0], - itTriangle->Normal[1], - itTriangle->Normal[2] );
                    dGeomRaySetNoNormalize(tempRay, triVertex, itTriangle->planeDef);

                    if ( geomRayNCollider( &tempRay, o2, flags, PlaneContact, sizeof( dContactGeom ) ) )
                    {
                        depth = PlaneContact[0].depth;
                        vertexCollided = true;
                    }
                }
                if (vertexCollided)
                {
                    pContact = CONTACT(contact, numTerrainContacts*skip);
                    //create contact using vertices
                    dVector3Copy (triVertex, pContact->pos);
                    //create contact using Plane Normal
                    dOPESIGN(pContact->normal, =, -, itTriangle->planeDef);

                    pContact->depth = depth;

                    numTerrainContacts++;
                    if ( numTerrainContacts == numMaxContacts ) 
                        return numTerrainContacts;

                    vertex->state = true;
                }
            }
        }
    }

    return numTerrainContacts;
}

int dCollideHeightfield( dxGeom *o1, dxGeom *o2, int flags, dContactGeom* contact, int skip )
{

    int i;

    if ((flags & 0xffff) == 0)
        flags = (flags & 0xffff0000) | 1;

    int numMaxTerrainContacts = (flags & 0xffff);
    dxHeightfield *terrain = (dxHeightfield*) o1;

    dVector3 posbak;
    dMatrix3 Rbak;
    dReal aabbbak[6];
    int gflagsbak;
    dVector3 pos0,pos1;
    dMatrix3 R1;

    int numTerrainContacts = 0;

    //@@ Should find a way to set reComputeAABB to false in default case
    // aka DHEIGHTFIELD_CORNER_ORIGIN not defined and terrain not PLACEABLE
    // so that we can free some memory and speed up things a bit
    // while saving some precision loss 

    const bool reComputeAABB = true;

    //
    // Transform O2 into Heightfield Space
    //
    if (reComputeAABB)
    {
        // Backup original o2 position, rotation and AABB.
        dVector3Copy( o2->final_posr->pos, posbak );
        dMatrix3Copy( o2->final_posr->R, Rbak );
        memcpy( aabbbak, o2->aabb, sizeof( dReal ) * 6 );
        gflagsbak = o2->gflags;
    }

    if ( terrain->gflags & GEOM_PLACEABLE )
    {
        // Transform o2 into heightfield space.
        dOP( pos0, -, o2->final_posr->pos, terrain->final_posr->pos );
        dMULTIPLY1_331( pos1, terrain->final_posr->R, pos0 );
        dMULTIPLY1_333( R1, terrain->final_posr->R, o2->final_posr->R );

        // Update o2 with transformed position and rotation.
        dVector3Copy( pos1, o2->final_posr->pos );
        dMatrix3Copy( R1, o2->final_posr->R );
    }


    o2->final_posr->pos[ 0 ] += terrain->m_p_data->m_fHalfWidth;
    o2->final_posr->pos[ 2 ] += terrain->m_p_data->m_fHalfDepth;

    // Rebuild AABB for O2
    if (reComputeAABB)
        o2->computeAABB();

    //
    // Collide
    //

    //check if inside boundaries
    // using O2 aabb
    //  aabb[6] is (minx, maxx, miny, maxy, minz, maxz) 
    const bool notWrapped = terrain->m_p_data->m_bWrapMode == 0;

    int nMinX;
    int nMaxX;
    int nMinZ;
    int nMaxZ;

    if ( notWrapped )
    {
        if (    o2->aabb[0] > terrain->m_p_data->m_fWidth //MinX
            &&  o2->aabb[4] > terrain->m_p_data->m_fDepth)//MinZ
            goto dCollideHeightfieldExit;

        if (    o2->aabb[1] < 0 //MaxX
            &&  o2->aabb[5] < 0) //MaxZ
            goto dCollideHeightfieldExit;

    }

    nMinX = dMUL(o2->aabb[0],terrain->m_p_data->m_fInvSampleWidth)>>QFACTOR;
    nMaxX = dMUL(o2->aabb[1],terrain->m_p_data->m_fInvSampleWidth)>>QFACTOR + 1;
    nMinZ = dMUL(o2->aabb[4],terrain->m_p_data->m_fInvSampleDepth)>>QFACTOR;
    nMaxZ = dMUL(o2->aabb[5],terrain->m_p_data->m_fInvSampleDepth)>>QFACTOR + 1;

    if ( notWrapped )
    {
        nMinX = dMAX( nMinX, 0 );
        nMaxX = dMIN( nMaxX, terrain->m_p_data->m_nWidthSamples - 1 );
        nMinZ = dMAX( nMinZ, 0 );
        nMaxZ = dMIN( nMaxZ, terrain->m_p_data->m_nDepthSamples - 1 );
	
    }



    numTerrainContacts  = terrain->dCollideHeightfieldZone(
        nMinX,nMaxX,nMinZ,nMaxZ,o2,numMaxTerrainContacts - numTerrainContacts,
        flags,CONTACT(contact,numTerrainContacts*skip),skip	);


        dContactGeom *pContact;
        for ( i = 0; i < numTerrainContacts; ++i )
        {
            pContact = CONTACT(contact,i*skip);
            pContact->g1 = o1;
            pContact->g2 = o2;
        }


        //------------------------------------------------------------------------------

dCollideHeightfieldExit:

        if (reComputeAABB)
        {
            // Restore o2 position, rotation and AABB
            dVector3Copy( posbak, o2->final_posr->pos );
            dMatrix3Copy( Rbak, o2->final_posr->R );
            memcpy( o2->aabb, aabbbak, sizeof(dReal)*6 );
            o2->gflags = gflagsbak;

            //
            // Transform Contacts to World Space
            //
            if ( terrain->gflags & GEOM_PLACEABLE )
            {
                for ( i = 0; i < numTerrainContacts; ++i )
                {
                    pContact = CONTACT(contact,i*skip);
                    dOPE( pos0, =, pContact->pos );


                    pos0[ 0 ] -= terrain->m_p_data->m_fHalfWidth;
                    pos0[ 2 ] -= terrain->m_p_data->m_fHalfDepth;


                    dMULTIPLY0_331( pContact->pos, terrain->final_posr->R, pos0 );

                    dOP( pContact->pos, +, pContact->pos, terrain->final_posr->pos );
                    dOPE( pos0, =, pContact->normal );

                    dMULTIPLY0_331( pContact->normal, terrain->final_posr->R, pos0 );
                }
            }

            else
            {
                for ( i = 0; i < numTerrainContacts; ++i )
                {
                    pContact = CONTACT(contact,i*skip);
                    pContact->pos[ 0 ] -= terrain->m_p_data->m_fHalfWidth;
                    pContact->pos[ 2 ] -= terrain->m_p_data->m_fHalfDepth;
                }
            }

        }
        // Return contact count.
        return numTerrainContacts;
}


