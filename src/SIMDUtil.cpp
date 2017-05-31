//
//  SIMDUtil.cpp
//  example-BoneControl
//
//  Created by Yuya Hanai on 2017/05/31.
//
//

#include "SIMDUtil.h"
#include <immintrin.h>

namespace SIMD
{
    // Scale all the elements of a matrix.
    void MatrixScale(FbxAMatrix& pMatrix, double pValue)
    {
        int i,j;
        
        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                pMatrix[i][j] *= pValue;
            }
        }
    }
    
    // Add a value to all the elements in the diagonal of the matrix.
    void MatrixAddToDiagonal(FbxAMatrix& pMatrix, double pValue)
    {
        
    }
    
    // Sum two matrices element by element.
    void MatrixAdd(FbxAMatrix& pDstMatrix, FbxAMatrix& pSrcMatrix)
    {
        int i,j;
        
        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                pDstMatrix[i][j] += pSrcMatrix[i][j];
            }
        }
    }
    
    // A += B*C
    void MatrixScaleAdd(FbxAMatrix& A, const FbxAMatrix& B, double C)
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
    
    void MatrixMultT(FbxVector4& dst, const FbxAMatrix& A, const FbxVector4& v)
    {
    }
}

