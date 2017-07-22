/*!
 * \file
 * \author David Saxon
 * \brief Math operations for matrices.
 */
#ifndef ARCANECORE_GM_MATRIXMATH_HPP_
#define ARCANECORE_GM_MATRIXMATH_HPP_

#include "arcanecore/gm/Matrix.hpp"


namespace arc
{
namespace gm
{

//------------------------------------------------------------------------------
//                                   TRANSPOSE
//------------------------------------------------------------------------------

/*!
 * \brief Flips a matrix over its diagonal, i.e. switches the row and column
 *        indices of the matrix.
 *
 * \note If T_cols does not equals T_rows the resulting matrices will have
 *       differently dimensionality to the given matrix.
 */
template<
    typename T_scalar,
    std::size_t T_cols,
    std::size_t T_rows,
    bool T_use_simd
>
Matrix<T_scalar, T_rows, T_cols, T_use_simd> transpose(
        const Matrix<T_scalar, T_cols, T_rows, T_use_simd>& m)
{
    Matrix<T_scalar, T_rows, T_cols, T_use_simd> r;
    for(std::size_t i = 0; i < T_rows; ++i)
    {
        Vector<T_scalar, T_cols, T_use_simd> v;
        for(std::size_t j = 0; j < T_cols; ++j)
        {
            v[j] = m[j][i];
        }
        r[i] = v;
    }
    return r;
}

//------------------------S P E C I A L I S A T I O N S-------------------------

template<typename T_scalar, bool T_use_simd>
Matrix<T_scalar, 3, 3, T_use_simd> transpose(
        const Matrix<T_scalar, 3, 3, T_use_simd>& m)
{
    return Matrix<T_scalar, 3, 3, T_use_simd>(
        Vector<T_scalar, 3, T_use_simd>(m[0][0], m[1][0], m[2][0]),
        Vector<T_scalar, 3, T_use_simd>(m[0][1], m[1][1], m[2][1]),
        Vector<T_scalar, 3, T_use_simd>(m[0][2], m[1][2], m[2][2])
    );
}

template<typename T_scalar, bool T_use_simd>
Matrix<T_scalar, 3, 4, T_use_simd> transpose(
        const Matrix<T_scalar, 3, 4, T_use_simd>& m)
{
    return Matrix<T_scalar, 4, 3, T_use_simd>(
        Vector<T_scalar, 3, T_use_simd>(m[0][0], m[1][0], m[2][0]),
        Vector<T_scalar, 3, T_use_simd>(m[0][1], m[1][1], m[2][1]),
        Vector<T_scalar, 3, T_use_simd>(m[0][2], m[1][2], m[2][2]),
        Vector<T_scalar, 3, T_use_simd>(m[0][3], m[1][3], m[2][3])
    );
}

template<typename T_scalar, bool T_use_simd>
Matrix<T_scalar, 4, 4, T_use_simd> transpose(
        const Matrix<T_scalar, 4, 4, T_use_simd>& m)
{
    return Matrix<T_scalar, 4, 4, T_use_simd>(
        Vector<T_scalar, 4, T_use_simd>(m[0][0], m[1][0], m[2][0], m[3][0]),
        Vector<T_scalar, 4, T_use_simd>(m[0][1], m[1][1], m[2][1], m[3][1]),
        Vector<T_scalar, 4, T_use_simd>(m[0][2], m[1][2], m[2][2], m[3][2]),
        Vector<T_scalar, 4, T_use_simd>(m[0][3], m[1][3], m[2][3], m[3][3])
    );
}

} // namespace gm
} // namespace arc

#endif
