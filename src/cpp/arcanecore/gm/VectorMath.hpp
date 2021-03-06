/*!
 * \file
 * \author David Saxon
 * \brief Math operations for vectors.
 */
#ifndef ARCANECORE_GM_VECTORMATH_HPP_
#define ARCANECORE_GM_VECTORMATH_HPP_

#include <algorithm>
#include <cmath>

#include <arcanecore/base/math/MathOperations.hpp>

#include "arcanecore/gm/Vector.hpp"


namespace arc
{
namespace gm
{

/*!
 * \brief Casts the components of the given vector to a new vector with
 *        T_out_scalar as the type.
 */
template<
    typename T_out_scalar,
    typename T_in_scalar,
    std::size_t T_dimensions,
    bool T_use_simd
>
inline Vector<T_out_scalar, T_dimensions, T_use_simd> cast(
        const Vector<T_in_scalar, T_dimensions, T_use_simd>& v)
{
    Vector<T_out_scalar, T_dimensions, T_use_simd> r;
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        r[i] = static_cast<T_out_scalar>(v[i]);
    }
    return r;
}

/*!
 * \brief Returns a copy of the given vector with all components made absolute.
 */
template<typename T_scalar, std::size_t T_dimensions, bool T_use_simd>
inline Vector<T_scalar, T_dimensions, T_use_simd> abs(
        const Vector<T_scalar, T_dimensions, T_use_simd>& v)
{
    Vector<T_scalar, T_dimensions, T_use_simd> r;
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        r[i] = arc::math::abs<T_scalar>(v[i]);
    }
    return r;
}

/*!
 * \brief Returns a new vector which has the smallest of each of of the
 *        components of the vectors a and b.
 */
template<
    typename T_scalar,
    std::size_t T_dimensions,
    bool T_use_simd,
    bool T_other_use_simd
>
inline Vector<T_scalar, T_dimensions, T_use_simd> min(
        const Vector<T_scalar, T_dimensions, T_use_simd>& a,
        const Vector<T_scalar, T_dimensions, T_other_use_simd>& b)
{
    Vector<T_scalar, T_dimensions, T_use_simd> r;
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        r[i] = std::min<T_scalar>(a[i], b[i]);
    }
    return r;
}

/*!
 * \brief Returns a new vector which has the largest of each of of the
 *        components of the vectors a and b.
 */
template<
    typename T_scalar,
    std::size_t T_dimensions,
    bool T_use_simd,
    bool T_other_use_simd
>
inline Vector<T_scalar, T_dimensions, T_use_simd> max(
        const Vector<T_scalar, T_dimensions, T_use_simd>& a,
        const Vector<T_scalar, T_dimensions, T_other_use_simd>& b)
{
    Vector<T_scalar, T_dimensions, T_use_simd> r;
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        r[i] = std::max<T_scalar>(a[i], b[i]);
    }
    return r;
}

/*!
 * \brief Clamps the each component in the given vector so that it is greater
 *        than or equal to the lower threshold scalar and less than or equal to
 *        the upper threshold scalar.
 *
 * \warning If upper_threshold is less than lower_threshold the result of this
 *          function is undefined.
 *
 * \return The result as a new vector.
 */
template<typename T_scalar, std::size_t T_dimensions, bool T_use_simd>
inline Vector<T_scalar, T_dimensions, T_use_simd> clamp(
        const Vector<T_scalar, T_dimensions, T_use_simd>& v,
        T_scalar lower_threshold,
        T_scalar upper_threshold)
{
    Vector<T_scalar, T_dimensions, T_use_simd> r;
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        r[i] = arc::math::clamp<T_scalar>(
            v[i],
            lower_threshold,
            upper_threshold
        );
    }
    return r;
}

/*!
 * \brief Clamps the each component in the given vector so that it is greater
 *        than or equal to the respective component in the lower threshold
 *        vector and is less than or equal to each respective in the upper
 *        threshold vector.
 *
 * \warning If a component in upper_threshold vector is less than a respective
 *          component n the lower_threshold vector the result of this function
 *          is undefined.
 *
 * \return The result as a new vector.
 */
template<
    typename T_scalar,
    std::size_t T_dimensions,
    bool T_use_simd,
    bool T_lower_use_simd,
    bool T_upper_use_simd
>
inline Vector<T_scalar, T_dimensions, T_use_simd> clamp(
        const Vector<T_scalar, T_dimensions, T_use_simd>& v,
        const Vector<T_scalar, T_dimensions, T_lower_use_simd>& lower_threshold,
        const Vector<T_scalar, T_dimensions, T_upper_use_simd>& upper_threshold)
{
    Vector<T_scalar, T_dimensions, T_use_simd> r;
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        r[i] = arc::math::clamp<T_scalar>(
            v[i],
            lower_threshold[i],
            upper_threshold[i]
        );
    }
    return r;
}

/*!
 * \brief Computes the floor of each component of this vector and returns the
 *        result in a new vector.
 */
template<typename T_scalar, std::size_t T_dimensions, bool T_use_simd>
inline Vector<T_scalar, T_dimensions, T_use_simd> floor(
        const Vector<T_scalar, T_dimensions, T_use_simd>& v)
{
    Vector<T_scalar, T_dimensions, T_use_simd> r;
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        r[i] = std::floor(v[i]);
    }
    return r;
}

/*!
 * \brief Computes the ceil of each component of this vector and returns the
 *        result in a new vector.
 */
template<typename T_scalar, std::size_t T_dimensions, bool T_use_simd>
inline Vector<T_scalar, T_dimensions, T_use_simd> ceil(
        const Vector<T_scalar, T_dimensions, T_use_simd>& v)
{
    Vector<T_scalar, T_dimensions, T_use_simd> r;
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        r[i] = std::ceil(v[i]);
    }
    return r;
}

/*!
 * \brief Computes the rounded value of each component of this vector and
 *        returns the result in a new vector.
 */
template<typename T_scalar, std::size_t T_dimensions, bool T_use_simd>
inline Vector<T_scalar, T_dimensions, T_use_simd> round(
        const Vector<T_scalar, T_dimensions, T_use_simd>& v)
{
    Vector<T_scalar, T_dimensions, T_use_simd> r;
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        r[i] = std::round(v[i]);
    }
    return r;
}

/*!
 * \brief Returns a normalised copy of the given vector.
 */
template<typename T_scalar, std::size_t T_dimensions, bool T_use_simd>
inline Vector<T_scalar, T_dimensions, T_use_simd> normalise(
        const Vector<T_scalar, T_dimensions, T_use_simd>& v)
{
    return v * arc::math::rsqrt(dot(v, v));
}

/*!
 * \brief Computes the dot product of vectors a and b.
 */
template<
    typename T_scalar,
    std::size_t T_dimensions,
    bool T_use_simd,
    bool T_other_use_simd
>
inline T_scalar dot(
    const Vector<T_scalar, T_dimensions, T_use_simd>& a,
    const Vector<T_scalar, T_dimensions, T_other_use_simd>& b)
{
    T_scalar r = 0;
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        r += a[i] * b[i];
    }
    return r;
}

/*!
 * \brief Computes the dot product of vectors a and b and returns the result
 *        copied across the components of a vector.
 */
template<
    typename T_scalar,
    std::size_t T_dimensions,
    bool T_use_simd,
    bool T_other_use_simd
>
inline Vector<T_scalar, T_dimensions, T_use_simd> dot_vector(
    const Vector<T_scalar, T_dimensions, T_use_simd>& a,
    const Vector<T_scalar, T_dimensions, T_other_use_simd>& b)
{
    T_scalar r = 0;
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        r += a[i] * b[i];
    }
    return Vector<T_scalar, T_dimensions, T_use_simd>(r);
}

/*!
 * \brief Computes the cross product of vectors a and b.
 */
template<
    typename T_scalar,
    std::size_t T_dimensions,
    bool T_use_simd,
    bool T_other_use_simd
>
inline Vector<T_scalar, T_dimensions, T_use_simd> cross(
    const Vector<T_scalar, T_dimensions, T_use_simd>& a,
    const Vector<T_scalar, T_dimensions, T_other_use_simd>& b)
{
    // check dimensionality
    static_assert(
        T_dimensions == 3,
        "Cross product is only valid for vectors with a dimensionality of 3"
    );

    return Vector<T_scalar, T_dimensions, T_use_simd>(
        (a[1] * b[2]) - (b[1] * a[2]),
        (a[2] * b[0]) - (b[2] * a[0]),
        (a[0] * b[1]) - (b[0] * a[1])
    );
}

/*!
 * \brief Calculates and returns the squared magnitude of the given vector.
 *
 * \note When this can be used (e.g. finding the difference between magnitudes)
 *       this is more efficient than magnitude() since it avoid have to
 *       calculate the squared root.
 */
template<typename T_scalar, std::size_t T_dimensions, bool T_use_simd>
inline T_scalar magnitude2(const Vector<T_scalar, T_dimensions, T_use_simd>& v)
{
    return dot(v, v);
}

/*!
 * \brief Calculates and returns the magnitude of the given vector.
 */
template<typename T_scalar, std::size_t T_dimensions, bool T_use_simd>
inline T_scalar magnitude(const Vector<T_scalar, T_dimensions, T_use_simd>& v)
{
    return static_cast<T_scalar>(std::sqrt(magnitude2(v)));
}

/*!
 * \brief Calculates the distance between the vectors a and b.
 */
template<typename T_scalar, std::size_t T_dimensions, bool T_use_simd>
inline T_scalar distance(
        const Vector<T_scalar, T_dimensions, T_use_simd>& a,
        const Vector<T_scalar, T_dimensions, T_use_simd>& b)
{
    return magnitude(b - a);
}

/*!
 * \brief Returns the direction vector between the two points a and b.
 */
template<
    typename T_scalar,
    std::size_t T_dimensions,
    bool T_use_simd,
    bool T_other_use_simd
>
inline Vector<T_scalar, T_dimensions, T_use_simd> direction(
        const Vector<T_scalar, T_dimensions, T_use_simd>& a,
        const Vector<T_scalar, T_dimensions, T_other_use_simd>& b)
{
    Vector<T_scalar, T_dimensions, T_use_simd> diff(b - a);
    return Vector<T_scalar, T_dimensions, T_use_simd>(diff / magnitude(diff));
}

/*!
 * \brief Returns the single value directional angle of the difference between
 *        the x and y components of the vectors a and b.
 *
 * \note The directional vector between a and b is (1.0, 0.0), then the angle
 * would be 0.0, likewise if it were (-1.0, 0.0) the angle would be pi,
 * (0.0, 1.0) would have angle of pi/2, and (0.0, -1.0) would have angle of
 * -pi/2.
 */
template<
    typename T_scalar,
    std::size_t T_dimensions,
    bool T_use_simd,
    bool T_other_use_simd
>
inline T_scalar angle2(
        const Vector<T_scalar, T_dimensions, T_use_simd>& a,
        const Vector<T_scalar, T_dimensions, T_other_use_simd>& b)
{
    // check dimensionality
    static_assert(
        T_dimensions >= 2,
        "angle2 is only valid for vectors with a dimensionality of 2 or more"
    );

    Vector<T_scalar, T_dimensions, T_use_simd> d(direction(a, b));
    return std::atan2(d[1], d[0]);
}

/*!
 * \brief Calculates the natural base e logarithm of each component of this
 *        vector and returns the result in a new vector.
 */
template<typename T_scalar, std::size_t T_dimensions, bool T_use_simd>
inline Vector<T_scalar, T_dimensions, T_use_simd> log(
        const Vector<T_scalar, T_dimensions, T_use_simd>& v)
{
    Vector<T_scalar, T_dimensions, T_use_simd> r;
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        r[i] = std::log(v[i]);
    }
    return r;
}

/*!
 * \brief Calculates the binary (base 2) logarithm of each component of this
 *        vector and returns the result in a new vector.
 */
template<typename T_scalar, std::size_t T_dimensions, bool T_use_simd>
inline Vector<T_scalar, T_dimensions, T_use_simd> log2(
        const Vector<T_scalar, T_dimensions, T_use_simd>& v)
{
    Vector<T_scalar, T_dimensions, T_use_simd> r;
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        r[i] = std::log2(v[i]);
    }
    return r;
}

/*!
 * \brief Calculates the base-e exponential function of each component of this
 *        vector and returns the result in a new vector.
 */
template<typename T_scalar, std::size_t T_dimensions, bool T_use_simd>
inline Vector<T_scalar, T_dimensions, T_use_simd> exp(
        const Vector<T_scalar, T_dimensions, T_use_simd>& v)
{
    Vector<T_scalar, T_dimensions, T_use_simd> r;
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        r[i] = std::exp(v[i]);
    }
    return r;
}

/*!
 * \brief Calculates each component of the vector a raised to the power of the
 *        respective component in vector b.
 */
template<
    typename T_scalar,
    std::size_t T_dimensions,
    bool T_use_simd,
    bool T_other_use_simd
>
inline Vector<T_scalar, T_dimensions, T_use_simd> pow(
        const Vector<T_scalar, T_dimensions, T_use_simd>& a,
        const Vector<T_scalar, T_dimensions, T_other_use_simd>& b)
{

    Vector<T_scalar, T_dimensions, T_use_simd> r;
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        r[i] = static_cast<T_scalar>(std::pow(a[i], b[i]));
    }
    return r;
}

/*!
 * \brief Calculates each component of the vector a raised to the power of the
 *        scalar b.
 */
template<typename T_scalar, std::size_t T_dimensions, bool T_use_simd>
inline Vector<T_scalar, T_dimensions, T_use_simd> pow(
        const Vector<T_scalar, T_dimensions, T_use_simd>& a,
        T_scalar b)
{
    return pow(a, Vector<T_scalar, T_dimensions, T_use_simd>(b));
}

/*!
 * \brief Calculates each component of the vector a raised to the power of the
 *        respective component in vector b.
 *
 * This is a performance orientated version of power that does not support
 * negative exponents.
 */
template<
    typename T_scalar,
    std::size_t T_dimensions,
    bool T_use_simd,
    bool T_other_use_simd
>
inline Vector<T_scalar, T_dimensions, T_use_simd> pow_fast(
        const Vector<T_scalar, T_dimensions, T_use_simd>& a,
        const Vector<T_scalar, T_dimensions, T_other_use_simd>& b)
{
    return exp(b * log(a));
}

/*!
 * \brief Calculates each component of the vector a raised to the power of the
 *        scalar b.
 *
 * This is a performance orientated version of power that does not support
 * negative exponents.
 */
template<typename T_scalar, std::size_t T_dimensions, bool T_use_simd>
inline Vector<T_scalar, T_dimensions, T_use_simd> pow_fast(
        const Vector<T_scalar, T_dimensions, T_use_simd>& a,
        T_scalar b)
{
    return pow_fast(a, Vector<T_scalar, T_dimensions, T_use_simd>(b));
}

/*!
 * \brief Calculates the square root of each component in the given vector.
 */
template<typename T_scalar,std::size_t T_dimensions,bool T_use_simd>
inline Vector<T_scalar, T_dimensions, T_use_simd> sqrt(
        const Vector<T_scalar, T_dimensions, T_use_simd>& v)
{
    Vector<T_scalar, T_dimensions, T_use_simd> r;
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        r[i] = static_cast<T_scalar>(std::sqrt(v[i]));
    }
    return r;
}

/*!
 * \brief Calculates the reciprocal (or multiplicative inverse) of the square
 *        root for each component in the vector.
 */
template<typename T_scalar,std::size_t T_dimensions,bool T_use_simd>
inline Vector<T_scalar, T_dimensions, T_use_simd> rsqrt(
        const Vector<T_scalar, T_dimensions, T_use_simd>& v)
{
    Vector<T_scalar, T_dimensions, T_use_simd> r;
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        r[i] = static_cast<T_scalar>(arc::math::rsqrt(v[i]));
    }
    return r;
}

/*!
 * \brief Calculates the sine of each component in the given vector.
 */
template<typename T_scalar,std::size_t T_dimensions,bool T_use_simd>
inline Vector<T_scalar, T_dimensions, T_use_simd> sin(
        const Vector<T_scalar, T_dimensions, T_use_simd>& v)
{
    Vector<T_scalar, T_dimensions, T_use_simd> r;
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        r[i] = static_cast<T_scalar>(std::sin(v[i]));
    }
    return r;
}

/*!
 * \brief Calculates the cosine of each component in the given vector.
 */
template<typename T_scalar,std::size_t T_dimensions,bool T_use_simd>
inline Vector<T_scalar, T_dimensions, T_use_simd> cos(
        const Vector<T_scalar, T_dimensions, T_use_simd>& v)
{
    Vector<T_scalar, T_dimensions, T_use_simd> r;
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        r[i] = static_cast<T_scalar>(std::cos(v[i]));
    }
    return r;
}

/*!
 * \brief Calculates the both the sin and the cos of each component in the
 *        given vector.
 *
 * \note This is implemented for efficiency when using SIMD types since sin and
 *       cos can be computed simultaneously with almost no extra overhead.
 */
template<typename T_scalar,std::size_t T_dimensions,bool T_use_simd>
inline void sincos(
        const Vector<T_scalar, T_dimensions, T_use_simd>& v,
        Vector<T_scalar, T_dimensions, T_use_simd>& r_sin,
        Vector<T_scalar, T_dimensions, T_use_simd>& r_cos)
{
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        r_sin[i] = static_cast<T_scalar>(std::sin(v[i]));
        r_cos[i] = static_cast<T_scalar>(std::cos(v[i]));
    }
}

// TODO: tan:
//      https://github.com/to-miz/sse_mathfun_extension

// TODO: asin

// TODO: acos

// TODO: atan

} // namespace gm
} // namespace arc

//----------------------I N L I N E -- E X T E N S I O N S----------------------
#ifndef ARC_GM_DISABLE_SSE
    #include "arcanecore/gm/VectorMathSimd3f.inl"
    #include "arcanecore/gm/VectorMathSimd4f.inl"
#endif

#endif
