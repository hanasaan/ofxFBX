//
//  ofxFBXMesh.h
//  ofxFBX-Example-Importer
//
//  Created by Nick Hardeman on 10/31/13.
//
//

#pragma once

#define FBXSDK_NEW_API
//#if defined(TARGET_LINUX) && !defined(TARGET_OPENGLES)
//    #include <fbxsdk.h>
//#endif
//
//#include "ofMain.h"
//#if defined(TARGET_OSX)
//    #include "fbxsdk.h"
//#endif

#include "ofMain.h"
#include <fbxsdk.h>

#include "ofVboMesh.h"
#include "ofxFBXNode.h"
#include "ofxFBXBone.h"
#include "ofxFBXCluster.h"
#include "ofxFBXMeshMaterial.h"

class ofxFBXSubMesh {
public:
    
    ofxFBXSubMesh() {
        triangleCount   = 0;
        indexOffset     = 0;
        totalIndices    = 0;
        materialPtr     = NULL;
    }
    
    ~ofxFBXSubMesh() {
        
    }
    
    ofxFBXMeshMaterial* materialPtr;
    bool bRender;
    int triangleCount;
    int indexOffset;
    int totalIndices;
};

class ofxFBXMesh : public ofxFBXNode {
public:
	ofxFBXMesh();
	virtual ~ofxFBXMesh();
    
    void setup( FbxNode * pNode );
	void setFBXMesh( FbxMesh* lMesh );
    void configureMesh( ofMesh& aMesh );
    
    void update( FbxTime& pTime, FbxPose* pPose );
    virtual void update( int aAnimIndex, signed long aMillis );
    
    void updateMesh( ofMesh* aMesh, FbxTime& pTime, FbxAnimLayer * pAnimLayer, FbxPose* pPose  );

	void draw( ofMesh* aMesh );
    void drawNormals( ofMesh* aMesh, float length, bool bFaceNormals);
    
    FbxMesh* getFbxMesh() { return fbxMesh; }
    int getNumSubMeshes();
    int getNumMaterials();
    
    const vector<ofxFBXSubMesh>& getSubMeshes() const { return subMeshes; }
    vector< ofxFBXMeshMaterial* > getMaterials();
    
    bool hasTexture();
    vector< ofxFBXTexture* > getTextures();
    
    bool hasClusterDeformation();
    
	ofVbo& getVbo();
    ofMesh& getOFMesh();
    
    void prepareDeformThreadTasks(int numThreads = 0);

private:
    
    void computeBlendShapes( ofMesh* aMesh, FbxTime& pTime, FbxAnimLayer * pAnimLayer );
    void computeSkinDeformation( FbxAMatrix& pGlobalPosition, FbxTime& pTime, FbxAnimLayer * pAnimLayer, FbxVector4* pVertexArray, FbxVector4* pNormalsArray, FbxPose* pPose );
    void computeLinearDeformation(FbxAMatrix& pGlobalPosition,
                                  FbxMesh* pMesh,
                                  FbxTime& pTime,
                                  FbxVector4* pVertexArray,
                                  FbxPose* pPose,
                                  bool bNormals);
    void computeLinearDeformationWithNormals(FbxAMatrix& pGlobalPosition,
                                  FbxMesh* pMesh,
                                  FbxTime& pTime,
                                  FbxVector4* pVertexArray,
                                  FbxVector4* pNormalArray,
                                  FbxPose* pPose);
    void computeDualQuaternionDeformation(FbxAMatrix& pGlobalPosition,
                                          FbxMesh* pMesh,
                                          FbxTime& pTime,
                                          FbxVector4* pVertexArray,
                                          FbxPose* pPose,
                                          bool bNormals);
    void computeClusterDeformation(FbxAMatrix& pGlobalPosition,
                                   FbxMesh* pMesh,
                                   FbxCluster* pCluster,
                                   FbxAMatrix& pVertexTransformMatrix,
                                   FbxTime pTime,
                                   FbxPose* pPose,
                                   bool bNormals);
    
    void populateNormals( FbxVector4* pNormalsArray );
    
    vector<ofxFBXSubMesh> subMeshes;
    ofVbo veebs;
	ofMesh mesh;
	ofMesh original;
	FbxMesh* fbxMesh;
    FbxVector4* mNormalsArray;
//    bool bAllMappedByControlPoint;
    
    FbxGeometryElement::EMappingMode mNormalMappingMode = FbxGeometryElement::eNone;
    
    vector<FbxAMatrix> lClusterDeformations;
    vector<FbxAMatrix> lNormalClusterDeformations;
    vector<FbxDualQuaternion> lDQClusterDeformations;
    vector<double> lClusterWeights;
    vector<FbxVector4> lVertices;
    vector<FbxVector4> lNormals;
    
    struct DeformTask
    {
        FbxSkin* skin = nullptr;
        FbxCluster* cluster = nullptr;
        int skinIndex = -1;
        int clusterIndex = -1;
        int index = -1;
        double weight = 0.0;
        
        DeformTask(){}
        DeformTask(FbxSkin* s, FbxCluster* c, int si, int ci, int i, double w)
        : skin(s), cluster(c), skinIndex(si), clusterIndex(ci), index(i), weight(w)
        {
        }
    };
    class DeformTasks : public vector<DeformTask>
    {
    public:
        int startIndex = 0;
        int endIndex = 0;
    };
    vector< DeformTasks > deformTasks;

};

