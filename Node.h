#pragma once
#include <vector>
#include "vec.h"
#include "modelerdraw.h"
#include <FL/gl.h>

#include <random >

class Node
{
public:
	Node* parent;
	std::vector<Node*> childrens;

	Vec3f rotate;
	Vec3f scale;

	static Node* generateTree(int maxDepth);
	static void drawTree(Node* root);
	static void setTexture(std::vector<GLuint*>* textures);

private:
	int depth = 0;
	float leavesRot = 0;
	Node(Node* parent);
};

