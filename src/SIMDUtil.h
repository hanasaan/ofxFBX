//
//  SIMDUtil.h
//  example-BoneControl
//
//  Created by Yuya Hanai on 2017/05/31.
//
//
#pragma once

#include "fbxsdk.h"
#include "ofMain.h"
#include <immintrin.h>

namespace SIMD
{
    // Scale all the elements of a matrix.
    void MatrixScale(FbxAMatrix& pMatrix, double pValue);
    
    // Add a value to all the elements in the diagonal of the matrix.
    void MatrixAddToDiagonal(FbxAMatrix& pMatrix, double pValue);
    
    // Sum two matrices element by element.
    void MatrixAdd(FbxAMatrix& pDstMatrix, FbxAMatrix& pSrcMatrix);

    // A += B*C
    static inline void MatrixScaleAdd(FbxAMatrix& A, const FbxAMatrix& B, double C)
    {
#if defined ( __AVX__ )
        __m256d S = _mm256_set1_pd(C);
        __m256d A_0 = _mm256_loadu_pd(A[0].mData);
        __m256d A_1 = _mm256_loadu_pd(A[1].mData);
        __m256d A_2 = _mm256_loadu_pd(A[2].mData);
        __m256d A_3 = _mm256_loadu_pd(A[3].mData);
        
        __m256d B_0 = _mm256_loadu_pd(B[0].mData);
        __m256d B_1 = _mm256_loadu_pd(B[1].mData);
        __m256d B_2 = _mm256_loadu_pd(B[2].mData);
        __m256d B_3 = _mm256_loadu_pd(B[3].mData);
        
        B_0 = _mm256_mul_pd(B_0, S);
        B_1 = _mm256_mul_pd(B_1, S);
        B_2 = _mm256_mul_pd(B_2, S);
        B_3 = _mm256_mul_pd(B_3, S);
        
        A_0 = _mm256_add_pd(A_0, B_0);
        A_1 = _mm256_add_pd(A_1, B_1);
        A_2 = _mm256_add_pd(A_2, B_2);
        A_3 = _mm256_add_pd(A_3, B_3);
        
        _mm256_storeu_pd(A[0].mData, A_0);
        _mm256_storeu_pd(A[1].mData, A_1);
        _mm256_storeu_pd(A[2].mData, A_2);
        _mm256_storeu_pd(A[3].mData, A_3);
        
        //_mm_set1
#else
        int i,j;
        
        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                A[i][j] += B[i][j] * C;
            }
        }
#endif

    }
    
    static inline void MatrixMultT(FbxVector4& dst, const FbxAMatrix& _mat, const FbxVector4& v)
    {
        double* dst_ptr = dst.mData;
        dst_ptr[0] = (_mat[0][0]*v[0] + _mat[1][0]*v[1] + _mat[2][0]*v[2] + _mat[3][0]);
        dst_ptr[1] = (_mat[0][1]*v[0] + _mat[1][1]*v[1] + _mat[2][1]*v[2] + _mat[3][1]);
        dst_ptr[2] = (_mat[0][2]*v[0] + _mat[1][2]*v[1] + _mat[2][2]*v[2] + _mat[3][2]);
        dst_ptr[3] = 0;

    }
}


