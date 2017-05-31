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

namespace SIMD
{
    // Scale all the elements of a matrix.
    void MatrixScale(FbxAMatrix& pMatrix, double pValue);
    
    // Add a value to all the elements in the diagonal of the matrix.
    void MatrixAddToDiagonal(FbxAMatrix& pMatrix, double pValue);
    
    // Sum two matrices element by element.
    void MatrixAdd(FbxAMatrix& pDstMatrix, FbxAMatrix& pSrcMatrix);

    // A += B*C
    void MatrixScaleAdd(FbxAMatrix& A, const FbxAMatrix& B, double C);
    
    void MatrixMultT(FbxVector4& dst, const FbxAMatrix& A, const FbxVector4& pVector4);
}


