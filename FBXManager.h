#pragma once
#include "fbxsdk.h"
#include "modelerdraw.h"


class FBXManager
{
public:

	static FBXManager* getFbxManager();

	char* getFileName();

	bool loadFbx(char* path);

	bool loaded;

	void drawSceneGL();

private:
	FBXManager();

	FbxManager* lSdkManager;

	FbxIOSettings* ios;

	FbxScene* lScene;

	bool drawNodes(FbxNode* Node);
	
	char* fileName;
};

