// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------
//
// release       : 
// release_date  : 1999, September 02
//
// file          : circulator.h
// package       : Circulator (3.4)
// chapter       : $CGAL_Chapter: Circulators $
// source        : circulator.fw
// revision      : $Revision$
// revision_date : $Date$
// author(s)     : Lutz Kettner  <kettner@inf.ethz.ch>
//
// coordinator   : INRIA, Sophia Antipolis
//
// Circulator support and Adaptors between circulators and iterators.
// ======================================================================

#ifndef CGAL_CIRCULATOR_H
#define CGAL_CIRCULATOR_H 1

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif
#ifndef CGAL_PROTECT_CSTDDEF
#include <cstddef>
#define CGAL_PROTECT_CSTDDEF
#endif
#ifndef CGAL_PROTECT_FUNCTIONAL
#include <functional>
#define CGAL_PROTECT_FUNCTIONAL
#endif
#ifndef CGAL_PROTECT_ITERATOR
#include <iterator>
#define CGAL_PROTECT_ITERATOR
#endif
#ifndef CGAL_CIRCULATOR_BASES_H
#include <CGAL/circulator_bases.h>
#endif

#ifndef CGAL_NULL_TYPE
#if defined( __GNUG__ )
    // (__GNUC__ < 2 || (__GNUC__ == 2 && __GNUC_MINOR__ < 91))
#define CGAL_NULL_TYPE const void*
#define CGAL_CIRC_NULL 0
#else // __GNUG__ //
#define CGAL_NULL_TYPE int
#define CGAL_CIRC_NULL NULL
#endif // __GNUG__ //
#endif // CGAL_NULL_TYPE //

// These are name redefinitions for backwards compatibility
// with the pre iterator-traits style adaptors.

#define Forward_container_from_circulator \
            Container_from_circulator
#define Bidirectional_container_from_circulator \
            Container_from_circulator
#define Random_access_container_from_circulator \
            Container_from_circulator

#define Forward_circulator_from_iterator \
            Circulator_from_iterator
#define Forward_const_circulator_from_iterator \
            Circulator_from_iterator
#define Bidirectional_circulator_from_iterator \
            Circulator_from_iterator
#define Bidirectional_const_circulator_from_iterator \
            Circulator_from_iterator
#define Random_access_circulator_from_iterator \
            Circulator_from_iterator
#define Random_access_const_circulator_from_iterator \
            Circulator_from_iterator

#define Forward_circulator_from_container \
            Circulator_from_container
#define Bidirectional_circulator_from_container \
            Circulator_from_container
#define Random_access_circulator_from_container \
            Circulator_from_container

#define Forward_const_circulator_from_container \
            Const_circulator_from_container
#define Bidirectional_const_circulator_from_container \
            Const_circulator_from_container
#define Random_access_const_circulator_from_container \
            Const_circulator_from_container



CGAL_BEGIN_NAMESPACE

template <class C>
struct I_Circulator_traits {
    typedef  Iterator_tag  category;
};
CGAL_TEMPLATE_NULL
struct I_Circulator_traits<Forward_circulator_tag> {
    typedef  Circulator_tag  category;
};
CGAL_TEMPLATE_NULL
struct I_Circulator_traits<Bidirectional_circulator_tag> {
    typedef  Circulator_tag  category;
};
CGAL_TEMPLATE_NULL
struct I_Circulator_traits<Random_access_circulator_tag> {
    typedef  Circulator_tag  category;
};

// Circulator_size_traits are used by general adaptors for
// iterators and circulators. For example the N_step_adaptor
// works for iterators as well as for circulators. Circulators
// need a local type called size_type which is not needed for
// iterators. But a general adaptor has to declare this type
// in any case and the following Circulator_size_traits helps
// in this case. It declares size_type to be std::size_t for
// iterators and to be C::size_type for any circulator C.
template <class Tag, class IC>
struct I_Circulator_size_traits {
    typedef  std::size_t  size_type;
};
#ifndef CGAL_CFG_NO_PARTIAL_CLASS_TEMPLATE_SPECIALISATION
template <class C>
struct I_Circulator_size_traits< Forward_circulator_tag, C> {
    typedef  typename  C::size_type  size_type;
};
template <class C>
struct I_Circulator_size_traits< Bidirectional_circulator_tag, C> {
    typedef  typename  C::size_type  size_type;
};
template <class C>
struct I_Circulator_size_traits< Random_access_circulator_tag, C> {
    typedef  typename  C::size_type  size_type;
};
#endif // CGAL_CFG_NO_PARTIAL_CLASS_TEMPLATE_SPECIALISATION //

template <class CCtg>
struct I_Iterator_from_circulator_traits {
    typedef CCtg iterator_category;
};
CGAL_TEMPLATE_NULL
struct I_Iterator_from_circulator_traits< Forward_circulator_tag> {
    typedef  std::forward_iterator_tag  iterator_category;
};
CGAL_TEMPLATE_NULL
struct I_Iterator_from_circulator_traits<
    Bidirectional_circulator_tag> {
    typedef  std::bidirectional_iterator_tag  iterator_category;
};
CGAL_TEMPLATE_NULL
struct I_Iterator_from_circulator_traits<
    Random_access_circulator_tag> {
    typedef  std::random_access_iterator_tag  iterator_category;
};

template <class ICtg>
struct I_Circulator_from_iterator_traits {
    typedef ICtg iterator_category;
};
CGAL_TEMPLATE_NULL
struct I_Circulator_from_iterator_traits< std::forward_iterator_tag> {
    typedef  Forward_circulator_tag  iterator_category;
};
CGAL_TEMPLATE_NULL
struct I_Circulator_from_iterator_traits<std::bidirectional_iterator_tag> {
    typedef  Bidirectional_circulator_tag  iterator_category;
};
CGAL_TEMPLATE_NULL
struct I_Circulator_from_iterator_traits<std::random_access_iterator_tag> {
    typedef  Random_access_circulator_tag  iterator_category;
};

template <class C>
struct Circulator_traits {
    typedef std::iterator_traits<C>                 traits;
    typedef typename traits::iterator_category      ICAT;
    typedef I_Circulator_traits<ICAT>               C_traits;
    typedef typename C_traits::category             category;

    typedef I_Iterator_from_circulator_traits<ICAT> Ic_traits;
    typedef typename Ic_traits::iterator_category   iterator_category;

    typedef I_Circulator_from_iterator_traits<ICAT> Ci_traits;
    typedef typename Ci_traits::iterator_category   circulator_category;
};

template <class C>
typename Circulator_traits<C>::category
query_circulator_or_iterator( const C&) {
    typedef typename Circulator_traits<C>::category category;
    return category();
}
/* A function that asserts a specific compile time tag */
/* forcing its two arguments to have equal type.       */
/* It is encapsulated with #ifdef since it will be defined also elsewhere. */
#ifndef CGAL_ASSERT_COMPILE_TIME_TAG
#define CGAL_ASSERT_COMPILE_TIME_TAG 1
template <class Base>
struct I_Assert_tag_class {
    void match_compile_time_tag( const Base&) const {}
};
template< class Tag, class Derived>
inline void Assert_compile_time_tag( const Tag&, const Derived& b) {
    I_Assert_tag_class<Tag> x;
    x.match_compile_time_tag(b);
}
#endif

template <class C> inline
void Assert_circulator( const C &c) {
    Assert_compile_time_tag( Circulator_tag(),query_circulator_or_iterator(c));
}
template <class I> inline
void Assert_iterator( const I &i) {
    Assert_compile_time_tag( Iterator_tag(), query_circulator_or_iterator(i));
}
template <class I> inline
void Assert_input_category( const I &i) {
    Assert_compile_time_tag( std::input_iterator_tag(),
                             std::iterator_category(i));
}
template <class I> inline
void Assert_output_category( const I &i) {
    Assert_compile_time_tag( std::output_iterator_tag(),
                             std::iterator_category(i));
}
template <class IC> inline
void Assert_forward_category( const IC &ic) {
    Assert_compile_time_tag( std::forward_iterator_tag(),
                             std::iterator_category(ic));
}
template <class IC> inline
void Assert_bidirectional_category( const IC &ic) {
    Assert_compile_time_tag( std::bidirectional_iterator_tag(),
                             std::iterator_category(ic));
}
template <class IC> inline
void Assert_random_access_category( const IC &ic) {
    Assert_compile_time_tag( std::random_access_iterator_tag(),
                             std::iterator_category(ic));
}

// The assert at-least-category functions use the following
// functions to resolve properly. Note the proper order of the
// arguments: 1st is the to be type, 2nd is the actual type.
inline void I_Has_to_be_at_least( std::input_iterator_tag,
                                  std::input_iterator_tag){}
inline void I_Has_to_be_at_least( std::input_iterator_tag,
                                  std::forward_iterator_tag){}
inline void I_Has_to_be_at_least( std::input_iterator_tag,
                                  std::bidirectional_iterator_tag){}
inline void I_Has_to_be_at_least( std::input_iterator_tag,
                                  std::random_access_iterator_tag){}

inline void I_Has_to_be_at_least( std::output_iterator_tag,
                                  std::output_iterator_tag){}
inline void I_Has_to_be_at_least( std::output_iterator_tag,
                                  std::forward_iterator_tag){}
inline void I_Has_to_be_at_least( std::output_iterator_tag,
                                  std::bidirectional_iterator_tag){}
inline void I_Has_to_be_at_least( std::output_iterator_tag,
                                  std::random_access_iterator_tag){}

inline void I_Has_to_be_at_least( std::forward_iterator_tag,
                                  std::forward_iterator_tag){}
inline void I_Has_to_be_at_least( std::forward_iterator_tag,
                                  std::bidirectional_iterator_tag){}
inline void I_Has_to_be_at_least( std::forward_iterator_tag,
                                  std::random_access_iterator_tag){}

inline void I_Has_to_be_at_least( std::bidirectional_iterator_tag,
                                  std::bidirectional_iterator_tag){}
inline void I_Has_to_be_at_least( std::bidirectional_iterator_tag,
                                  std::random_access_iterator_tag){}

inline void I_Has_to_be_at_least( std::random_access_iterator_tag,
                                  std::random_access_iterator_tag){}

// The is-at-least assertions.
template <class I> inline
void Assert_is_at_least_input_category( const I& i) {
    I_Has_to_be_at_least( std::input_iterator_tag(),
                          std::iterator_category(i));
}
template <class I> inline
void Assert_is_at_least_output_category( const I& i) {
    I_Has_to_be_at_least( std::output_iterator_tag(),
                          std::iterator_category(i));
}
template <class IC> inline
void Assert_is_at_least_forward_category( const IC& ic) {
    I_Has_to_be_at_least( std::forward_iterator_tag(),
                          std::iterator_category(ic));
}
template <class IC> inline
void Assert_is_at_least_bidirectional_category( const IC& ic) {
    I_Has_to_be_at_least( std::bidirectional_iterator_tag(),
                          std::iterator_category(ic)) ;
    }
template <class IC> inline
void Assert_is_at_least_random_access_category( const IC& ic) {
    I_Has_to_be_at_least( std::random_access_iterator_tag(),
                          std::iterator_category(ic));
}

template< class C> inline
bool I_is_empty_range( const C& c1, const C&, Circulator_tag){
    return c1 == CGAL_CIRC_NULL;
}

template< class I> inline
bool I_is_empty_range( const I& i1, const I& i2, Iterator_tag){
    return i1 == i2;
}

template< class IC> inline
bool is_empty_range( const IC& ic1, const IC& ic2){
    // is `true' if the range [`ic1, ic2') is empty, `false' otherwise.
    // Precondition: `T' is either a circulator or an iterator type. The
    // range [`ic1, ic2') is valid.
    return I_is_empty_range( ic1, ic2, query_circulator_or_iterator(ic1));
}

struct Circulator_or_iterator_tag {};  // any circulator or iterator.

inline
Circulator_or_iterator_tag
check_circulator_or_iterator( Circulator_tag ){
    return Circulator_or_iterator_tag();
}
inline
Circulator_or_iterator_tag
check_circulator_or_iterator( Iterator_tag ){
    return Circulator_or_iterator_tag();
}

template< class IC> inline
void Assert_circulator_or_iterator( const IC &ic){
    Assert_compile_time_tag(
        Circulator_or_iterator_tag(),
        check_circulator_or_iterator( query_circulator_or_iterator(ic)));
}

#define CGAL_For_all( ic1, ic2) \
    for ( bool _circ_loop_flag = ! ::CGAL::is_empty_range( ic1, ic2); \
          _circ_loop_flag; \
          _circ_loop_flag = ((++ic1) != (ic2)) )

#define CGAL_For_all_backwards( ic1, ic2) \
    for ( bool _circ_loop_flag = ! ::CGAL::is_empty_range( ic1, ic2); \
          _circ_loop_flag; \
          _circ_loop_flag = ((ic1) != (--ic2)) )



template <class C> inline
typename C::size_type
I_min_circulator_size( const C& c) {
    Assert_circulator(c);
    Assert_random_access_category(c);
    typedef typename C::size_type  size_type;
    size_type n = 0;
    if ( c != CGAL_CIRC_NULL) {
        n = (c-1) - c + 1;
        CGAL_assertion(n > 0);
    }
    return n;
}

template <class C>
typename C::size_type
I_circulator_size( const C& c, Forward_circulator_tag) {
    // Simply count.
    if ( c == CGAL_CIRC_NULL)
        return 0;
    typedef typename C::size_type  size_type;
    size_type n = 0;
    C      d = c;
    do {
        ++n;
        ++d;
    } while( c != d);
    return n;
}
template <class C> inline
typename C::size_type
I_circulator_size( const C& c, Bidirectional_circulator_tag) {
    return I_circulator_size( c, Forward_circulator_tag());
}
template <class C> inline
typename C::size_type
I_circulator_size( const C& c, Random_access_circulator_tag) {
    return I_min_circulator_size( c.min_circulator());
}

template <class C> inline
typename C::size_type
circulator_size( const C& c) {
    return I_circulator_size( c, std::iterator_category(c));
}
template <class C>
typename C::difference_type
I_circulator_distance( C c, const C& d, Forward_circulator_tag) {
    // Simply count.
    if ( c == CGAL_CIRC_NULL)
        return 0;
    typedef typename C::difference_type  difference_type;
    difference_type n = 0;
    do {
        ++n;
    } while( ++c != d);
    return n;
}
template <class C> inline
typename C::difference_type
I_circulator_distance( const C& c, const C& d,
                       Bidirectional_circulator_tag) {
    return I_circulator_distance( c, d, Forward_circulator_tag());
}
template <class C> inline
typename C::difference_type
I_circulator_distance( const C& c, const C& d,
                       Random_access_circulator_tag) {
    typedef typename C::difference_type  difference_type;
    typedef typename C::size_type        size_type;
    if ( d - c > 0)
        return (d - c);
    return difference_type( size_type( I_min_circulator_size(
               c.min_circulator()))) - (c-d);
}

template <class C> inline
typename C::difference_type
circulator_distance( const C& c, const C& d) {
    return I_circulator_distance( c, d, std::iterator_category(c));
}
template <class C> inline
typename std::iterator_traits<C>::difference_type
I_iterator_distance(const C& c1, const C& c2, Circulator_tag) {
    return circulator_distance( c1, c2);
}

template <class I> inline
typename std::iterator_traits<I>::difference_type
I_iterator_distance(const I& i1, const I& i2, Iterator_tag) {
    return std::distance( i1, i2);
}

template <class IC> inline
typename std::iterator_traits<IC>::difference_type
iterator_distance(const IC& ic1, const IC& ic2) {
    return I_iterator_distance( ic1, ic2,
                                query_circulator_or_iterator(ic1));
}
template <class C> inline
C I_get_min_circulator( C c, Forward_circulator_tag) {
    return c;
}
template <class C> inline
C I_get_min_circulator( C c, Bidirectional_circulator_tag) {
    return c;
}
template <class C> inline
C I_get_min_circulator( C c, Random_access_circulator_tag) {
    return c.min_circulator();
}
template <class C> inline
C get_min_circulator( C c) {
    return I_get_min_circulator( c, std::iterator_category(c));
}
template<class I, class U> inline
I non_negative_mod(I n, U m) {
    CGAL_precondition( m > 0);
    #if (-1 % 3) > 0
        n = n % m;
    #else
    if (n < 0)
        n = - (( - n - 1) % m) + m - 1;
    else
        n = n % m;
    #endif
    CGAL_postcondition( n >= 0);
    return n;
}

template < class  C, class Ref, class Ptr>
class Iterator_from_circulator {
private:
    // The m_anchor is normalized to be a minimal circulator.
    const C*  m_anchor;
    C         current;
    int       m_winding;

    typedef  std::iterator_traits<C>                       I_traits;
    typedef  typename  I_traits::iterator_category         I_Iter_cat;
    typedef  I_Iterator_from_circulator_traits<I_Iter_cat> I__traits;

public:
//
// TYPES

    typedef C  Circulator;
    typedef Iterator_from_circulator<C,Ref,Ptr> Self;

    typedef typename I__traits::iterator_category iterator_category;

    typedef typename C::value_type       value_type;
    typedef typename C::difference_type  difference_type;
    typedef typename C::size_type        size_type;
    typedef typename C::reference        reference;
    typedef typename C::pointer          pointer;

//
// CREATION

    Iterator_from_circulator() : m_anchor(0), m_winding(0) {}

    Iterator_from_circulator( const C* circ, int n)
        : m_anchor( circ), current( *circ), m_winding(n) {}

    // Allow construction from Iterator_from_circulator with
    // assignment compatible circulator CC:
    template <class CC, class CREF, class CPTR>
    Iterator_from_circulator(
        const Iterator_from_circulator<CC,CREF,CPTR>& c)
    : m_anchor( c.anchor()), current( c.current_circulator()),
        m_winding(c.winding()) {}

//
// OPERATIONS

    bool operator==( const Self& i) const {
        CGAL_assertion( m_anchor == i.m_anchor);  // same anchor?
        return ( current == i.current) && ( m_winding == i.m_winding);
    }
    bool operator!=( const Self& i) const {
        return !(*this == i);
    }
    Ref  operator*() const {
        CGAL_assertion( m_anchor != CGAL_CIRC_NULL);
        CGAL_assertion( current  != CGAL_CIRC_NULL);
        return Ref(*current);
    }
    Ptr  operator->() const {
        CGAL_assertion( m_anchor != CGAL_CIRC_NULL);
        CGAL_assertion( current  != CGAL_CIRC_NULL);
        return Ptr(current.operator->());
    }
    Self& operator++() {
        CGAL_assertion( m_anchor != CGAL_CIRC_NULL);
        CGAL_assertion( current  != CGAL_CIRC_NULL);
        ++current;
        if ( current == *m_anchor)
            ++m_winding;
        return *this;
    }
    Self  operator++(int) {
        Self tmp = *this;
        ++*this;
        return tmp;
    }
    Self& operator--() {
        CGAL_assertion( m_anchor != CGAL_CIRC_NULL);
        CGAL_assertion( current != CGAL_CIRC_NULL);
        if ( current == *m_anchor)
            --m_winding;
        --current;
        return *this;
    }
    Self  operator--(int) {
        Self tmp = *this;
        --*this;
        return tmp;
    }
    Self& operator+=( difference_type n) {
        CGAL_assertion( m_anchor != CGAL_CIRC_NULL);
        CGAL_assertion( current != CGAL_CIRC_NULL);
        if ( n < 0 && current == *m_anchor)  // We are leaving the anchor.
            --m_winding;
        current += n;
        if ( n > 0 && current == *m_anchor)  // Back again at the anchor.
            ++m_winding;
        return *this;
    }
    Self  operator+( difference_type n) const {
        Self tmp = *this;
        return tmp += n;
    }
    Self& operator-=( difference_type n) {
        return operator+=( -n);
    }
    Self  operator-( difference_type n) const {
        Self tmp = *this;
        return tmp += -n;
    }
#ifndef _MSC_VER
    difference_type  operator-( const Self& i) const;
#else
    difference_type  operator-( const Self& i) const {
        CGAL_assertion( m_anchor  != CGAL_CIRC_NULL);
        CGAL_assertion( current   != CGAL_CIRC_NULL);
        CGAL_assertion( m_anchor  == i.m_anchor);
        if ( m_winding != i.m_winding) {
            difference_type s = I_min_circulator_size( *m_anchor);
            return   (current - *m_anchor) - (i.current - *m_anchor)
                   + s * (m_winding - i.m_winding);
        }
        return (current - *m_anchor) - (i.current - *m_anchor);
    }
#endif

    Ref  operator[](difference_type n) const {
        Self tmp = *this;
        tmp += n;
        return tmp.operator*();
    }
    bool operator<( const Self& i) const {
        CGAL_assertion( m_anchor  != CGAL_CIRC_NULL);
        CGAL_assertion( current != CGAL_CIRC_NULL);
        CGAL_assertion( m_anchor  == i.m_anchor);
        return (     (m_winding < i.m_winding)
                 || (    (m_winding == i.m_winding)
                      && (current - *m_anchor) < (i.current - *m_anchor)
                    )
               );
    }
    bool operator> ( const Self& i) const { return i < *this; }
    bool operator<=( const Self& i) const { return !(i < *this); }
    bool operator>=( const Self& i) const { return !(*this < i); }

    const C*    anchor()             const { return m_anchor;}
    int         winding()            const { return m_winding;}
    Circulator  current_circulator() const { return current;}
};

template < class Dist, class  C, class Ref, class Ptr>
Iterator_from_circulator<C,Ref,Ptr>
operator+( Dist n, const Iterator_from_circulator<C,Ref,Ptr>& circ) {
    Iterator_from_circulator<C,Ref,Ptr> tmp = circ;
    return tmp += n;
}

#ifndef _MSC_VER
template < class  C, class Ref, class Ptr>
typename C::difference_type
Iterator_from_circulator<C,Ref,Ptr>::
operator-( const Iterator_from_circulator<C,Ref,Ptr>& i) const {
    CGAL_assertion( m_anchor  != CGAL_CIRC_NULL);
    CGAL_assertion( current   != CGAL_CIRC_NULL);
    CGAL_assertion( m_anchor  == i.m_anchor);
    if ( m_winding != i.m_winding) {
        difference_type s = I_min_circulator_size( *m_anchor);
        return   (current - *m_anchor) - (i.current - *m_anchor)
               + s * (m_winding - i.m_winding);
    }
    return (current - *m_anchor) - (i.current - *m_anchor);
}
#endif // _MSC_VER //

template < class  C >
class Container_from_circulator {
private:
    C anchor;
public:
//
// CREATION

    Container_from_circulator() {}
        // the resulting iterators will have a singular value.

    Container_from_circulator(const C& c)
        // The anchor is normalized to be a minimal circulator.
        : anchor(get_min_circulator(c)) {}
        // the resulting iterators will have a singular value if the
        // circulator `c' is singular.

//
// TYPES

typedef C  Circulator;

typedef typename C::value_type       value_type;
typedef value_type&                  reference;
typedef const value_type&            const_reference;
typedef value_type*                  pointer;
typedef const value_type*            const_pointer;
typedef typename C::size_type        size_type;
typedef typename C::difference_type  difference_type;

typedef Iterator_from_circulator< C, reference, pointer>
    iterator;
typedef Iterator_from_circulator< C, const_reference, const_pointer>
    const_iterator;
//
// OPERATIONS

    iterator begin() {
        // the start iterator.
        return iterator( &anchor, 0);
    }
    const_iterator begin() const {
        // the start const iterator.
        return const_iterator( &anchor, 0);
    }
    iterator end() {
        // the past-the-end iterator.
        return anchor == CGAL_CIRC_NULL ?  iterator( &anchor, 0)
                                        :  iterator( &anchor, 1);
    }
    const_iterator end() const {
        // the past-the-end const iterator.
        return anchor == CGAL_CIRC_NULL ?  const_iterator( &anchor, 0)
                                        :  const_iterator( &anchor, 1);
    }
};
template < class  Ctnr>
class Circulator_from_container {
public:
// TYPES

    typedef Circulator_from_container<Ctnr>     Self;
    typedef Ctnr                                Container;
    typedef typename Ctnr::iterator             iterator;
    typedef typename Ctnr::value_type           value_type;
    typedef typename Ctnr::reference            reference;
    typedef value_type*                         pointer;
    typedef typename Ctnr::size_type            size_type;
    typedef typename Ctnr::difference_type      difference_type;

    typedef std::iterator_traits<iterator>      ITraits;
    typedef typename ITraits::iterator_category Icategory;
    typedef I_Circulator_from_iterator_traits<Icategory> CTraits;
    typedef typename CTraits::iterator_category iterator_category;

private:
    Ctnr*     ctnr;
    iterator  i;

public:
// CREATION

    Circulator_from_container() : ctnr(NULL) {}
    Circulator_from_container( Ctnr* c) : ctnr(c), i(c->begin()) {}
    Circulator_from_container( Ctnr* c, iterator j)  : ctnr(c), i(j) {}

// Gnu-bug workaround: define operator= explicitly.
    Self& operator=( const Self& c) {
        ctnr = c.ctnr;
        i    = c.i;
        return *this;
    }

// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == CGAL_CIRC_NULL);
        return (ctnr == NULL) || (ctnr->begin() == ctnr->end());
    }
    bool operator!=( CGAL_NULL_TYPE p) const { return !(*this == p); }
    bool operator==( const Self& c) const { return i == c.i; }
    bool operator!=( const Self& c) const { return !(*this == c); }
    reference  operator*() const {
        CGAL_assertion( ctnr != NULL);
        CGAL_assertion( i != ctnr->end());
        return *i;
    }
    pointer  operator->() const {
        CGAL_assertion( ctnr != NULL);
        CGAL_assertion( i != ctnr->end());
        return i.operator->();
    }
    Self& operator++() {
        CGAL_assertion( ctnr != NULL);
        CGAL_assertion( i != ctnr->end());
        ++i;
        if ( i == ctnr->end())
            i = ctnr->begin();
        return *this;
    }
    Self operator++(int) {
        Self tmp= *this;
        ++*this;
        return tmp;
    }
    Self& operator--() {
        CGAL_assertion( ctnr != NULL);
        CGAL_assertion( i != ctnr->end());
        if ( i == ctnr->begin())
            i = ctnr->end();
        --i;
        return *this;
    }
    Self operator--(int) {
        Self tmp = *this;
        --*this;
        return tmp;
    }
#ifndef _MSC_VER
    Self& operator+=( difference_type n);
#else
    Self& operator+=( difference_type n) {
        CGAL_assertion( ctnr != NULL);
        CGAL_assertion( i != ctnr->end());
        typename Ctnr::difference_type j    = i - ctnr->begin();
        typename Ctnr::difference_type size = ctnr->size();
        CGAL_assertion( j    >= 0);
        CGAL_assertion( size >= 0);
        j = non_negative_mod( j + n, size);
        CGAL_assertion( j >= 0);
        CGAL_assertion( j < size);
        i = ctnr->begin() + j;
        return *this;
    }
#endif
    Self operator+( difference_type n) const {
        Self tmp = *this;
        return tmp += n;
    }
    Self& operator-=( difference_type n) { return operator+=( -n); }
    Self operator-( difference_type n) const {
        Self tmp = *this;
        return tmp += -n;
    }
    difference_type operator-( const Self& c) const {
        CGAL_assertion( ctnr != NULL);
        CGAL_assertion( c.ctnr != NULL);
        return i - c.i;
    }
    reference  operator[]( difference_type n) const {
        Self tmp = *this;
        tmp += n;
        return *tmp;
    }
    iterator    current_iterator() const { return i;}
    Self        min_circulator()   const { return Self(ctnr); }
    Ctnr*       container()        const { return ctnr; }
};

template <class Ctnr>
inline
Circulator_from_container<Ctnr>
operator+( typename Circulator_from_container<Ctnr>::difference_type n,
           const Circulator_from_container<Ctnr>& c) {
    Circulator_from_container<Ctnr> tmp = c;
    return tmp += n;
}

#ifndef _MSC_VER
template <class Ctnr>
Circulator_from_container<Ctnr>&
Circulator_from_container<Ctnr>::
operator+=( typename Ctnr::difference_type n) {
    CGAL_assertion( ctnr != NULL);
    CGAL_assertion( i != ctnr->end());
    typename Ctnr::difference_type j    = i - ctnr->begin();
    typename Ctnr::difference_type size = ctnr->size();
    CGAL_assertion( j    >= 0);
    CGAL_assertion( size >= 0);
    j = non_negative_mod( j + n, size);
    CGAL_assertion( j >= 0);
    CGAL_assertion( j < size);
    i = ctnr->begin() + j;
    return *this;
}
#endif // _MSC_VER //


template < class  Ctnr>
class Const_circulator_from_container {
public:
// TYPES

    typedef Const_circulator_from_container<Ctnr> Self;
    typedef Circulator_from_container<Ctnr>       Mutable;
    typedef Ctnr                                  Container;
    typedef typename Ctnr::const_iterator         const_iterator;
    typedef typename Ctnr::value_type             value_type;
    typedef typename Ctnr::const_reference        reference;
    typedef const value_type*                     pointer;
    typedef typename Ctnr::size_type              size_type;
    typedef typename Ctnr::difference_type        difference_type;

    typedef std::iterator_traits<const_iterator>  ITraits;
    typedef typename ITraits::iterator_category   Icategory;
    typedef I_Circulator_from_iterator_traits<Icategory> CTraits;
    typedef typename CTraits::iterator_category   iterator_category;

private:
    const Ctnr*    ctnr;
    const_iterator i;

public:
// CREATION

    Const_circulator_from_container() : ctnr(NULL) {}
    Const_circulator_from_container( const Ctnr* c)
        : ctnr(c), i(c->begin()) {}
    Const_circulator_from_container( const Ctnr* c, const_iterator j)
        : ctnr(c), i(j) {}
    Const_circulator_from_container( const Mutable& c)
        : ctnr( c.container()), i( c.current_iterator()) {}

// Gnu-bug workaround: define operator= explicitly.
    Self& operator=( const Self& c) {
        ctnr = c.ctnr;
        i    = c.i;
        return *this;
    }

// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == CGAL_CIRC_NULL);
        return (ctnr == NULL) || (ctnr->begin() == ctnr->end());
    }
    bool operator!=( CGAL_NULL_TYPE p) const { return !(*this == p); }
    bool operator==( const Self& c) const { return i == c.i; }
    bool operator!=( const Self& c) const { return !(*this == c); }
    reference  operator*() const {
        CGAL_assertion( ctnr != NULL);
        CGAL_assertion( i != ctnr->end());
        return *i;
    }
    pointer  operator->() const {
        CGAL_assertion( ctnr != NULL);
        CGAL_assertion( i != ctnr->end());
        return i.operator->();
    }
    Self& operator++() {
        CGAL_assertion( ctnr != NULL);
        CGAL_assertion( i != ctnr->end());
        ++i;
        if ( i == ctnr->end())
            i = ctnr->begin();
        return *this;
    }
    Self operator++(int) {
        Self tmp= *this;
        ++*this;
        return tmp;
    }
    Self& operator--() {
        CGAL_assertion( ctnr != NULL);
        CGAL_assertion( i != ctnr->end());
        if ( i == ctnr->begin())
            i = ctnr->end();
        --i;
        return *this;
    }
    Self operator--(int) {
        Self tmp = *this;
        --*this;
        return tmp;
    }
#ifndef _MSC_VER
    Self& operator+=( difference_type n);
#else
    Self& operator+=( difference_type n) {
        CGAL_assertion( ctnr != NULL);
        CGAL_assertion( i != ctnr->end());
        typename Ctnr::difference_type j    = i - ctnr->begin();
        typename Ctnr::difference_type size = ctnr->size();
        CGAL_assertion( j    >= 0);
        CGAL_assertion( size >= 0);
        j = non_negative_mod( j + n, size);
        CGAL_assertion( j >= 0);
        CGAL_assertion( j < size);
        i = ctnr->begin() + j;
        return *this;
    }
#endif
    Self operator+( difference_type n) const {
        Self tmp = *this;
        return tmp += n;
    }
    Self& operator-=( difference_type n) { return operator+=( -n); }
    Self operator-( difference_type n) const {
        Self tmp = *this;
        return tmp += -n;
    }
    difference_type operator-( const Self& c) const {
        CGAL_assertion( ctnr != NULL);
        CGAL_assertion( c.ctnr != NULL);
        return i - c.i;
    }
    reference  operator[]( difference_type n) const {
        Self tmp = *this;
        tmp += n;
        return *tmp;
    }
    const_iterator current_iterator() const { return i;}
    Self           min_circulator()   const { return Self(ctnr); }
    const Ctnr*    container()        const { return ctnr; }
};

template <class Ctnr>
inline
Const_circulator_from_container<Ctnr>
operator+( typename Const_circulator_from_container<Ctnr>::
               difference_type n,
           const Const_circulator_from_container<Ctnr>& c) {
    Const_circulator_from_container<Ctnr> tmp = c;
    return tmp += n;
}

#ifndef _MSC_VER
template <class Ctnr>
Const_circulator_from_container<Ctnr>&
Const_circulator_from_container<Ctnr>::
operator+=( typename Ctnr::difference_type n) {
    CGAL_assertion( ctnr != NULL);
    CGAL_assertion( i != ctnr->end());
    typename Ctnr::difference_type j    = i - ctnr->begin();
    typename Ctnr::difference_type size = ctnr->size();
    CGAL_assertion( j    >= 0);
    CGAL_assertion( size >= 0);
    j = non_negative_mod( j + n, size);
    CGAL_assertion( j >= 0);
    CGAL_assertion( j < size);
    i = ctnr->begin() + j;
    return *this;
}
#endif // _MSC_VER
// Note: TT, SS, and DD are here for backwards compatibility, they are
// not used.
template < class  I, class TT = int, class SS = int, class DD = int>
class Circulator_from_iterator {
public:
// TYPES

    typedef Circulator_from_iterator<I,TT,SS,DD>     Self;
    typedef I                                        iterator;
    typedef std::iterator_traits<iterator>           Traits;

    typedef typename Traits::value_type              value_type;
    typedef std::size_t                              size_type;
    typedef typename Traits::difference_type         difference_type;
    typedef typename Traits::reference               reference;
    typedef typename Traits::pointer                 pointer;

    typedef typename Traits::iterator_category       Icategory;
    typedef I_Circulator_from_iterator_traits<Icategory> CTraits;
    typedef typename CTraits::iterator_category      iterator_category;

private:
    I m_begin;
    I m_end;
    I current;

public:
// CREATION

    Circulator_from_iterator() : m_begin(I()), m_end(I()), current(I()) {}

    Circulator_from_iterator( const I& bgn, const I& end)
        : m_begin(bgn), m_end(end), current(bgn) {}

    Circulator_from_iterator( const I& bgn, const I& end, const I& cur)
        : m_begin(bgn), m_end(end), current(cur) {}

    Circulator_from_iterator( const Self& c, const I& cur)
        : m_begin( c.m_begin), m_end( c.m_end), current(cur) {}


    template <class II, class A1, class A2, class A3>
    // Allow construction from Circulator_from_iterator with
    // assignment compatible iterator II:
    Circulator_from_iterator(
        const Circulator_from_iterator<II,A1,A2,A3>& ii)
    : m_begin( ii.begin()), m_end( ii.end()),
        current(ii.current_iterator()) {}

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == CGAL_CIRC_NULL);
        CGAL_assertion((m_end == m_begin) || (current != m_end));
        return m_end == m_begin;
    }
    bool operator!=( CGAL_NULL_TYPE p) const { return !(*this == p); }
    bool operator==( const Self& c) const { return current == c.current;}
    bool operator!=( const Self& c) const { return !(*this == c); }
    reference  operator*() const {
        CGAL_assertion( current != m_end);
        return *current;
    }
    pointer  operator->() const {
        CGAL_assertion( current != m_end);
        return &(*current);
    }
    Self& operator++() {
        CGAL_assertion( current != m_end);
        ++current;
        if ( current == m_end)
            current = m_begin;
        return *this;
    }
    Self  operator++(int) {
        Self tmp= *this;
        ++*this;
        return tmp;
    }
    Self& operator--() {
        CGAL_assertion( current != m_end);
        if ( current == m_begin)
            current = m_end;
        --current;
        return *this;
    }
    Self  operator--(int) {
        Self tmp = *this;
        --*this;
        return tmp;
    }
    Self& operator+=( difference_type n) {
        CGAL_assertion( current != m_end);
        difference_type i    = current - m_begin;
        difference_type size = m_end    - m_begin;
        CGAL_assertion( i    >= 0);
        CGAL_assertion( size >= 0);
        i = non_negative_mod( i + n, size);
        CGAL_assertion( i >= 0);
        CGAL_assertion( i < size);
        current = m_begin + i;
        return *this;
    }
    Self  operator+( difference_type n) const {
        Self tmp = *this;
        return tmp += n;
    }
    Self& operator-=( difference_type n) { return operator+=( -n); }
    Self  operator-( difference_type n) const {
        Self tmp = *this;
        return tmp += -n;
    }
    difference_type  operator-( const Self& i) const {
        CGAL_assertion((m_begin == i.m_begin) && (m_end == i.m_end));
        return current - i.current;
    }
    reference  operator[](difference_type n) const {
        Self tmp = *this;
        tmp += n;
        return tmp.operator*();
    }
    iterator  begin()            const { return m_begin;}
    iterator  end()              const { return m_end;}
    iterator  current_iterator() const { return current;}
    Self      min_circulator()   const { return Self( m_begin, m_end); }
};

template < class D, class I, class  T, class Size, class Dist> inline
Circulator_from_iterator< I, T, Size, Dist>
operator+( D n, const
    Circulator_from_iterator< I, T, Size, Dist>& circ) {
    Circulator_from_iterator< I, T, Size, Dist>
        tmp = circ;
    return tmp += Dist(n);
}

CGAL_END_NAMESPACE

#endif // CGAL_CIRCULATOR_H //
// EOF //
