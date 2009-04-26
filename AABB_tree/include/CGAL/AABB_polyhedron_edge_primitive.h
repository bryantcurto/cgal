// Copyright (c) 2009 INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: $
// $Id: $
//
//
// Author(s)     : Pierre Alliez, Stephane Tayeb
//
//******************************************************************************
// File Description :
//
//******************************************************************************

#ifndef AABB_POLYHEDRON_EDGE_PRIMITIVE_H_
#define AABB_POLYHEDRON_EDGE_PRIMITIVE_H_

namespace CGAL {

    /**
    * @class AABB_polyhedron_edge_primitive
    *
    *
    */
    template<typename GeomTraits, typename Polyhedron_>
    class AABB_polyhedron_edge_primitive
    {
    public:
        /// AABBTrianglePrimitive types
        typedef typename GeomTraits::FT FT;
        typedef typename GeomTraits::Point_3 Point;
        typedef typename GeomTraits::Segment_3 Datum;
        typedef typename Polyhedron_::Edge_const_iterator Id;

        /// Self
        typedef AABB_polyhedron_edge_primitive<GeomTraits, Polyhedron_> Self;

        /// Constructors
        //AABB_polyhedron_triangle_primitive() { };

        AABB_polyhedron_edge_primitive(const Id& handle)
            : m_handle(handle)  { };

        // Default copy constructor and assignment operator are ok

        /// Destructor
        ~AABB_polyhedron_edge_primitive() {};

        /// Returns by constructing on the fly the geometric datum wrapped by the primitive
        Datum datum() const;
        /// Returns the identifier
        const Id id() const { return m_handle; }

        /// Returns a point on the primitive
        Point point_on() const;

        /// Returns the x/y/z reference coordinate for sorting
        /// here simply one vertex of the triangle
        const FT xref() const { return m_handle->vertex()->point().x(); }
        const FT yref() const { return m_handle->vertex()->point().y(); }
        const FT zref() const { return m_handle->vertex()->point().z(); }

    private:
        /// Halfedge handle
        Id m_handle;
    };  // end class AABB_polyhedron_edge_primitive


    template<typename GT, typename P_>
    typename AABB_polyhedron_edge_primitive<GT,P_>::Datum
        AABB_polyhedron_edge_primitive<GT,P_>::datum() const
    {
        typedef typename GT::Point_3 Point;
        typedef typename GT::Segment_3 Segment;
        const Point& a = m_handle->vertex()->point();
        const Point& b = m_handle->opposite()->vertex()->point();
        return Datum(a,b);
    }

    template<typename GT, typename P_>
    typename AABB_polyhedron_edge_primitive<GT,P_>::Point
        AABB_polyhedron_edge_primitive<GT,P_>::point_on() const
    {
        return m_handle->vertex()->point();
    }


}  // end namespace CGAL


#endif // AABB_POLYHEDRON_EDGE_PRIMITIVE_H_
