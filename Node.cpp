#include "Node.h"

static vector<Node*> nodeList;
static int maxDepth = 10;

std::default_random_engine generator;
std::uniform_real<float> distribution(0.7, 1.3);

static std::vector<GLuint*>* textures;

void Node::setTexture(std::vector<GLuint*>* tex) {
    textures = tex;
}

Node* Node::generateTree(int Depth)
{
    maxDepth = Depth;

    Node* root = new Node(nullptr);
    return root;
}

void Node::drawTree(Node* root)
{
    glPushMatrix();
    glTranslated(root->scale[0] / 2 + root->scale[0]*0.2, root->parent == nullptr?0: (root->parent->scale[1] - root->scale[0] / 2), root->scale[2] / 2 + root->scale[2]*0.2);
    glRotated(root->rotate[0], 1, 0, 0);
    glRotated(root->rotate[1], 0, 1, 0);
    glRotated(root->rotate[2], 0, 0, 1);
    //if(root->parent == nullptr)
    //make it rotate w.r.t center of box
    glTranslated(-root->scale[0]/2,0,-root->scale[2]/2);

    //glScaled(root->scale[0], root->scale[1], root->scale[2]);
    //drawleaves(root->scale[0], root->scale[1], root->scale[2],(*textures)[2]);
    setDiffuseColor(1, 1, 1);
    drawBox(root->scale[0], root->scale[1], root->scale[2]);
    for (Node* child : root->childrens) {
        drawTree(child);
    }
    glPopMatrix();
}

Vec3f dir[4] = {
    Vec3f(-50,0,0),
    Vec3f(0,0,-50),
    Vec3f(50,0,0),
    Vec3f(0,0,50)
};
Node::Node(Node* parent = nullptr) {
    this->parent = parent;
    if (parent == nullptr) {
        depth = 0;
        scale = Vec3f(1,8,1);
    }
    else
    {
        depth = parent->depth+1;

        this->scale = Vec3f(0.8 * parent->scale);
        this->scale[1] = 0.6 * parent->scale[1]* distribution(generator);
        int num = parent->childrens.size();
        this->rotate = dir[num]* distribution(generator);
    }

    if (depth <= maxDepth) {
        for (int i = 0; i < 4; i++) {
            Node* tempChild = new Node(this);
            nodeList.push_back(tempChild);
            this->childrens.push_back(tempChild);
        }
    }
    nodeList.push_back(this);
}

