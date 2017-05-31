//
//  SIMDUtil.cpp
//  example-BoneControl
//
//  Created by Yuya Hanai on 2017/05/31.
//
//

#include "SIMDUtil.h"

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
        pMatrix[0][0] += pValue;
        pMatrix[1][1] += pValue;
        pMatrix[2][2] += pValue;
        pMatrix[3][3] += pValue;
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
}

