#include "Node.h"

static vector<Node*> nodeList;
static int maxDepth = 10;


std::default_random_engine generator;

std::uniform_real<float> distribution(0.7, 1.3);
std::uniform_real<float> distribution2(0, 360);

static std::vector<GLuint*>* textures;

void Node::setTexture(std::vector<GLuint*>* tex) {
    textures = tex;
}

Node* Node::generateTree(int Depth)
{
    maxDepth = Depth;
    generator.seed(time(NULL));
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
    //
    setDiffuseColor(155 / 255.0, 115 / 255.0, 58 / 255.0);
    glBindTexture(GL_TEXTURE_2D, *(*textures)[0]);
    drawBox(root->scale[0], root->scale[1], root->scale[2]);
    for (Node* child : root->childrens) {
        drawTree(child);
    }
    if (root->childrens.size() == 0) {
        glRotated(root->leavesRot, 0, 1, 0);

        glTranslated(-root->scale[0]*1.8, root->scale[1] + 0.01,- root->scale[2]*1.5);
        drawleaves(1, 1, 1,(*textures)[2]);
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
    else {
        leavesRot = distribution2(generator);
    }
    nodeList.push_back(this);
}

