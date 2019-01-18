// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef INTRTRIANGLE3TRIANGLE3_H
#define INTRTRIANGLE3TRIANGLE3_H

#include "sn3DFoundationLIB.h"
#include "Intersector.h"
#include "Triangle3.h"
#include "Line3.h"
#include "Plane3.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM IntrTriangle3Triangle3
    : public Intersector<Real,Vector3<Real> >
{
public:
    IntrTriangle3Triangle3 (const Triangle3<Real>& rkTriangle0,
        const Triangle3<Real>& rkTriangle1);

    // object access
    const Triangle3<Real>& GetTriangle0 () const;
    const Triangle3<Real>& GetTriangle1 () const;

    bool ReportCoplanarIntersections;  // default 'true'

    // static queries
    virtual bool Test ();
    virtual bool Find ();

    // dynamic queries
    virtual bool Test (Real fTMax, const Vector3<Real>& rkVelocity0,
        const Vector3<Real>& rkVelocity1);
    virtual bool Find (Real fTMax, const Vector3<Real>& rkVelocity0,
        const Vector3<Real>& rkVelocity1);

    // information about the intersection set
    int GetQuantity () const;
    const Vector3<Real>& GetPoint (int i) const;

private:
    using Intersector<Real,Vector3<Real> >::IT_POINT;
    using Intersector<Real,Vector3<Real> >::IT_SEGMENT;
    using Intersector<Real,Vector3<Real> >::m_iIntersectionType;
    using Intersector<Real,Vector3<Real> >::m_fContactTime;

    static void ProjectOntoAxis (const Triangle3<Real>& rkTri,
        const Vector3<Real>& rkAxis, Real& rfMin, Real& rfMax);

    static void TrianglePlaneRelations (const Triangle3<Real>& rkTriangle,
        const Plane3<Real>& rkPlane, Real afDistance[3], int aiSign[3],
        int& riPositive, int& riNegative, int& riZero);

    static void GetInterval (const Triangle3<Real>& rkTriangle,
        const Line3<Real>& rkLine, const Real afDistance[3],
        const int aiSign[3], Real afParam[2]);

    bool ContainsPoint (const Triangle3<Real>& rkTriangle,
        const Plane3<Real>& rkPlane, const Vector3<Real>& rkPoint);

    bool IntersectsSegment (const Plane3<Real>& rkPlane,
        const Triangle3<Real>& rkTriangle, const Vector3<Real>& rkEnd0,
        const Vector3<Real>& rkEnd1);

    bool GetCoplanarIntersection (const Plane3<Real>& rkPlane,
        const Triangle3<Real>& rkTri0, const Triangle3<Real>& rkTri1);

    static bool TestOverlap (Real fTMax, Real fSpeed, Real fUMin,
        Real fUMax, Real fVMin, Real fVMax, Real& rfTFirst, Real& rfTLast);

    bool TestOverlap (const Vector3<Real>& rkAxis, Real fTMax,
        const Vector3<Real>& rkVelocity, Real& rfTFirst, Real& rfTLast);

    enum ProjectionMap
    {
        M2, M11,                // lines
        M3, M21, M12, M111,     // triangles
        M44, M2_2, M1_1         // boxes
    };

    enum ContactSide
    {
        CS_LEFT,
        CS_RIGHT,
        CS_NONE
    };

    class SN3D_FOUNDATION_ITEM Configuration
    {
    public:
        ProjectionMap Map;  // how vertices map to the projection interval
        int Index[8];       // the sorted indices of the vertices
        Real Min, Max;      // the interval is [min,max]
    };

    static void ProjectOntoAxis (const Triangle3<Real>& rkTri,
        const Vector3<Real>& rkAxis, Configuration& rkCfg);

    bool FindOverlap (Real fTMax, Real fSpeed, const Configuration& rkUC,
        const Configuration& rkVC, ContactSide& reSide, Configuration& rkTUC,
        Configuration& rkTVC, Real& rfTFirst, Real& rfTLast);

    bool FindOverlap (const Vector3<Real>& rkAxis, Real fTMax,
        const Vector3<Real>& rkVelocity, ContactSide& reSide,
        Configuration& rkTCfg0, Configuration& rkTCfg1, Real& rfTFirst,
        Real& rfTLast);

    void FindContactSet (const Triangle3<Real>& rkTri0,
        const Triangle3<Real>& rkTri1, ContactSide& reSide,
        Configuration& rkCfg0, Configuration& rkCfg1);

    void GetEdgeEdgeIntersection (const Vector3<Real>& rkU0,
        const Vector3<Real>& rkU1, const Vector3<Real>& rkV0,
        const Vector3<Real>& rkV1);

    void GetEdgeFaceIntersection (const Vector3<Real>& rkU0,
        const Vector3<Real>& rkU1, const Triangle3<Real>& rkTri);

    // the objects to intersect
    const Triangle3<Real>* m_pkTriangle0;
    const Triangle3<Real>* m_pkTriangle1;

    // information about the intersection set
    int m_iQuantity;
    Vector3<Real> m_akPoint[6];
};

typedef IntrTriangle3Triangle3<float> IntrTriangle3Triangle3f;
typedef IntrTriangle3Triangle3<double> IntrTriangle3Triangle3d;

}

#endif