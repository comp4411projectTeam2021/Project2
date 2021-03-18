// The sample model.  You should build a file
// very similar to this for when you make your model.
#include <gl/glew.h>
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include "FBXManager.h"

#include "modelerglobals.h"
//#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <FL/gl.h>
#include <vector>

// To make a MyModel, we inherit off of ModelerView
class MyModel : public ModelerView
{
public:
	MyModel(int x, int y, int w, int h, char* label)
		: ModelerView(x, y, w, h, label) { 
		
	}

	virtual void draw();
	//Shader* testShader = NULL;
	bool init = false;
	std::vector<GLuint*> texture;
};

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createMyModel(int x, int y, int w, int h, char* label)
{
	return new MyModel(x, y, w, h, label);
}

// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out MyModel
void MyModel::draw()
{
	if (!init) {
		init = true;
		//testShader = new Shader("shader.vs", "shader.fs");
		glEnable(GL_TEXTURE_2D);


		
		// 为当前绑定的纹理对象设置环绕、过滤方式
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		// 加载并生成纹理
		int width, height, nrChannels;
		unsigned char* data = stbi_load("鳞片.jpg", &width, &height, &nrChannels, 0);
		unsigned char* data2;
		if (data)
		{
			texture.push_back( new GLuint);
			glGenTextures(1, texture[0]);
			glBindTexture(GL_TEXTURE_2D, *texture[0]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			data2 = stbi_load("testTexture.jpg", &width, &height, &nrChannels, 0);

			texture.push_back(new GLuint);
			glGenTextures(1, texture[1]);
			glBindTexture(GL_TEXTURE_2D, *texture[1]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
			glGenerateMipmap(GL_TEXTURE_2D);


		}
		else
		{
			printf("Failed to load texture");
		}
			stbi_image_free(data);
			stbi_image_free(data2);

	}
	//testShader->use();
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// This call takes care of a lot of the nasty projection 
	// matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
	ModelerView::draw();
	
	if (FBXManager::getFbxManager()->loaded) {
		FBXManager* fbxManager = FBXManager::getFbxManager();
		fbxManager->drawSceneGL();
	}
	else {

		// draw the floor
		setAmbientColor(.1f, .1f, .1f);
		setDiffuseColor(COLOR_RED);
		/*
		glPushMatrix();
		glTranslated(-5, 0, -5);
		drawBox(10, 0.01f, 10);
		glPopMatrix();
	*/
	//Draw some test obj
		glBindTexture(GL_TEXTURE_2D, *texture[1]);

		glPushMatrix();
		setDiffuseColor(0.3, 0, 0);
		glTranslated(-5, 0, 0);
		drawTextureBox(1, 1, 1);
		glPopMatrix();


		glPushMatrix();
		setDiffuseColor(COLOR_RED);
		glTranslated(5, 0, 0);
		drawTextureBox(1, 1, 1);
		glPopMatrix();

		glPushMatrix();
		setDiffuseColor(0, 0.3, 0);
		glTranslated(0, -5, 0);
		drawTextureBox(1, 1, 1);
		glPopMatrix();


		glPushMatrix();
		setDiffuseColor(COLOR_GREEN);
		glTranslated(0, 5, 0);
		drawTextureBox(1, 1, 1);
		glPopMatrix();

		glPushMatrix();
		setDiffuseColor(0, 0, 0.3);
		glTranslated(0, 0, -5);
		drawTextureBox(1, 1, 1);
		glPopMatrix();


		glPushMatrix();
		setDiffuseColor(COLOR_BLUE);
		glTranslated(0, 0, 5);
		drawTextureBox(1, 1, 1);
		glPopMatrix();

		//glDeleteTextures(1, &texture);
		//test obj end

		//change testure
		glBindTexture(GL_TEXTURE_2D, *texture[0]);

		// draw the sample model
		setAmbientColor(.1f, .1f, .1f);
		setDiffuseColor(.4f, 0, .2f);

		glPushMatrix();
		glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));

		glPushMatrix();
		glRotated(VAL(FRONT_BODY), 0.0, 1.0, 0.0);
		glTranslated(-1, 0, .1);
		drawTextureBox(2, 1.2, 1);
		glTranslated(0.4, 0.1, 1);
		drawTextureBox(1.2, 1, 0.8);
		glPushMatrix();
		glTranslated(-.4, -.4, -.8);//2.9 -1.7
		glRotated(-80 + VAL(LEG_RIGHT1), 0.0, 1.0, 0.0);
		glRotated(30, 1.0, 0.0, 0.0);
		drawTextureBox(.3, .3, 1.5);
		glPopMatrix();

		glPushMatrix();
		glTranslated(1.6, -.4, -.8);
		glRotated(80 + VAL(LEG_LEFT1), 0.0, 1.0, 0.0);
		glRotated(30, 1.0, 0.0, 0.0);
		drawTextureBox(-.3, .3, 1.5);
		glPopMatrix();


			glPushMatrix();
			glTranslated(1.8, .4, -.4);
			glRotated(75 + VAL(ARM_LEFT2_1), 0.0, 1.0, 0.0);
			glRotated(VAL(ARM_LEFT2_2), 1.0, 0.0, 0.0);
			glRotated(10, 1.0, 0.0, 0.0);
			drawTextureBox(-.3, .3, 1.4);
				glPushMatrix();
				glTranslated(-.2, .15, 1.2);
				glRotated(-90 + VAL(ARM_LEFT1), 0.0, 1.0, 0.0);
				drawCylinder(1.5, 0.15, 0.15);
					glPushMatrix();
					glTranslated(0, 0, 1.4);
					glRotated(30, 0.0, 1.0, 0.0);
					drawCylinder(0.8, 0.15, 0.1);
						glPushMatrix();
						glRotated(-40, 0.0, 1.0, 0.0);
						glTranslated(0.5, 0, 0.6);
						drawCylinder(0.8, 0.08, 0.08);
							glPushMatrix();
							glTranslated(0, 0, 0.8);
							glRotated(-45, 0.0, 1.0, 0.0);
							drawCylinder(0.6, 0.08, 0.001);
							glPopMatrix();
						glPopMatrix();
					glPopMatrix();
					glPushMatrix();
					glTranslated(-0.1, 0, 1.6);
					glRotated(-10 + VAL(JAW_LEFT), 0.0, 1.0, 0.0);
					drawCylinder(.9, 0.1, 0.06);
						glPushMatrix();
						glTranslated(0, 0, .9);
						glRotated(30, 0.0, 1.0, 0.0);
						drawCylinder(.6, 0.06, 0.001);
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();

			glPushMatrix();
			glTranslated(-0.6, .4, -.4);
			glRotated(-75 + VAL(ARM_RIGHT2_1), 0.0, 1.0, 0.0);
			glRotated(VAL(ARM_RIGHT2_2), 1.0, 0.0, 0.0);
			glRotated(10, 1.0, 0.0, 0.0);
			drawTextureBox(.3, .3, 1.4);
				glPushMatrix();
				glTranslated(.2, .15, 1.2);
				glRotated(90 + VAL(ARM_RIGHT1), 0.0, 1.0, 0.0);
				drawCylinder(1.5, 0.15, 0.15);
					glPushMatrix();
					glTranslated(0, 0, 1.5);
					glRotated(-30, 0.0, 1.0, 0.0);
					drawCylinder(0.8, 0.15, 0.1);
						glPushMatrix();
						glRotated(40, 0.0, 1.0, 0.0);
						glTranslated(-0.5, 0, 0.6);
						drawCylinder(0.8, 0.08, 0.08);
							glPushMatrix();
							glTranslated(0, 0, 0.8);
							glRotated(45, 0.0, 1.0, 0.0);
							drawCylinder(0.6, 0.08, 0.001);
							glPopMatrix();
						glPopMatrix();
					glPopMatrix();
					glPushMatrix();
					glTranslated(0.1, 0, 1.6);
					glRotated(10 + VAL(JAW_RIGHT), 0.0, 1.0, 0.0);
					drawCylinder(.9, 0.1, 0.06);
						glPushMatrix();
						glTranslated(0, 0, .9);
						glRotated(-30, 0.0, 1.0, 0.0);
						drawCylinder(.6, 0.06, 0.001);
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		
		/*glPushMatrix();
		glPopMatrix();*/
		/*
		glPushMatrix();
		glTranslated(1.8, .4, -.4);
		glRotated(75 + VAL(ARM_LEFT2_1), 0.0, 1.0, 0.0);
		glRotated(VAL(ARM_LEFT2_2), 1.0, 0.0, 0.0);
		glRotated(10, 1.0, 0.0, 0.0);
		drawBox(-.3, .3, 1.4);
		glPushMatrix();
		glTranslated(-.2, .15, 1.2);
		glRotated(-90 + VAL(ARM_LEFT1), 0.0, 1.0, 0.0);
		drawCylinder(1.5, 0.15, 0.15);
		glPushMatrix();
		glTranslated(0, 0, 1.4);
		glRotated(30, 0.0, 1.0, 0.0);
		drawCylinder(0.8, 0.15, 0.1);
		glPopMatrix();
		glPushMatrix();
		glTranslated(-0.1, 0, 1.6);
		glRotated(-10 + VAL(JAW_LEFT), 0.0, 1.0, 0.0);
		drawCylinder(1.1, 0.1, 0.05);
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslated(-0.6, .4, -.4);
		glRotated(-75 + VAL(ARM_RIGHT2_1), 0.0, 1.0, 0.0);
		glRotated(VAL(ARM_RIGHT2_2), 1.0, 0.0, 0.0);
		glRotated(10, 1.0, 0.0, 0.0);
		drawBox(.3, .3, 1.4);
		glPushMatrix();
		glTranslated(.2, .15, 1.2);
		glRotated(90 + VAL(ARM_RIGHT1), 0.0, 1.0, 0.0);
		drawCylinder(1.5, 0.15, 0.15);
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();
*/



		glPushMatrix();
		glRotated(VAL(BACK_BODY), 0.0, 1.0, 0.0);
		glTranslated(-1, 0, -1.1);
		drawTextureBox(2, 1.2, 1);
		glTranslated(0.4, 0.1, -.8);
		drawTextureBox(1.2, 1, 0.8);
			glPushMatrix();
			glTranslated(1.5, -.4, .7);
			glRotated(-45 + VAL(LEG_LEFT3), 0.0, 1.0, 0.0);
			glRotated(-30, 1.0, 0.0, 0.0);
			drawTextureBox(.3, .3, -1.5);
			glPopMatrix();

			glPushMatrix();
			glTranslated(-.3, -.4, .7);
			glRotated(45 + VAL(LEG_RIGHT3), 0.0, 1.0, 0.0);
			glRotated(-30, 1.0, 0.0, 0.0);
			drawTextureBox(-.3, .3, -1.5);
			glPopMatrix();

			glPushMatrix();
			glTranslated(1.6, -.4, 1.4);
			glRotated(-80 + VAL(LEG_LEFT2), 0.0, 1.0, 0.0);
			glRotated(-30, 1.0, 0.0, 0.0);
			drawTextureBox(.3, .3, -1.5);
			glPopMatrix();

			glPushMatrix();
			glTranslated(-.4, -.4, 1.4);
			glRotated(80 + VAL(LEG_RIGHT2), 0.0, 1.0, 0.0);
			glRotated(-30, 1.0, 0.0, 0.0);
			drawTextureBox(-.3, .3, -1.5);
			glPopMatrix();
		
		/*
			glPushMatrix();
			glTranslated(-1.5, 0, -2);
			glScaled(3, 1, 4);
			drawBox(1, 1, 1);
			glPopMatrix();

			// draw cannon
			glPushMatrix();
			glTranslated(-.4, -.4, 1.4);
			glRotated(80 + VAL(LEG_RIGHT2), 0.0, 1.0, 0.0);
			glRotated(-30, 1.0, 0.0, 0.0);
			drawBox(-.3, .3, -1.5);
			glPopMatrix();
*/
			glPushMatrix();
			glRotated(30 + VAL(TAIL1), 1.0, 0.0, 0.0);
			glTranslated(0.3, 0.1, 0);
			drawTextureBox(.6, .6, -1.2);
				glPushMatrix();
				glTranslated(.05, 0.06, -1.2);
				glRotated(30 + VAL(TAIL2), 1.0, 0.0, 0.0);
				drawTextureBox(.5, .5, -1.2);
					glPushMatrix();
					glTranslated(.05, 0.06, -1.2);
					glRotated(30 + VAL(TAIL3), 1.0, 0.0, 0.0);
					drawTextureBox(.4, .4, -1.2);
						glPushMatrix();
						glTranslated(.05, 0.06, -1.2);
						glRotated(30 + VAL(TAIL4), 1.0, 0.0, 0.0);
						drawTextureBox(.3, .3, -1);
							glPushMatrix();
							glTranslated(.15, .15, -.9);
							glRotated(VAL(HOOK1), 0.0, 1.0, 0.0);
							glRotated(180 + VAL(HOOK2), 1.0, 0.0, 0.0);
							drawCylinder(1, 0.1, 0.001);
							glPopMatrix();
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	/*
		glPushMatrix();
		glTranslated(-1.5, 0, -2);
		glScaled(3, 1, 4);
		drawBox(1, 1, 1);
		glPopMatrix();
			glRotated(VAL(ROTATE), 0.0, 1.0, 0.0);
			glRotated(-90, 1.0, 0.0, 0.0);
			drawCylinder(VAL(HEIGHT), 0.1, 0.1);

			glTranslated(0.0, 0.0, VAL(HEIGHT));
			drawCylinder(1, 1.0, 0.9);

			glTranslated(0.0, 0.0, 0.5);
			glRotated(90, 1.0, 0.0, 0.0);
			drawCylinder(4, 0.1, 0.2);
			glPopMatrix();
			*/

		glPopMatrix();
	}
}

int main()
{
	// Initialize the controls
	// Constructor is ModelerControl(name, minimumvalue, maximumvalue, 
	// stepsize, defaultvalue)
	ModelerControl controls[NUMCONTROLS];
	controls[XPOS] = ModelerControl("X Position", -5, 5, 0.1f, 0);
	controls[YPOS] = ModelerControl("Y Position", 0, 5, 0.1f, 0);
	controls[ZPOS] = ModelerControl("Z Position", -5, 5, 0.1f, 0);
	//controls[HEIGHT] = ModelerControl("Height", 1, 2.5, 0.1f, 1);
	//controls[ROTATE] = ModelerControl("Rotate", -135, 135, 1, 0);
	controls[FRONT_BODY] = ModelerControl("Front Body Angle", -8, 8, 0.1f, 0);
	controls[BACK_BODY] = ModelerControl("Back Body Angle", -8, 8, 0.1f, 0);
	controls[LEG_LEFT1] = ModelerControl("Left Leg-1 Angle", -8, 8, 0.1f, 0);
	controls[LEG_LEFT2] = ModelerControl("Left Leg-2 Angle", -8, 8, 0.1f, 0);
	controls[LEG_LEFT3] = ModelerControl("Left Leg-3 Angle", -8, 8, 0.1f, 0);
	controls[LEG_RIGHT1] = ModelerControl("Right Leg-1 Angle", -8, 8, 0.1f, 0);
	controls[LEG_RIGHT2] = ModelerControl("Right Leg-2 Angle", -8, 8, 0.1f, 0);
	controls[LEG_RIGHT3] = ModelerControl("Right Leg-3 Angle", -8, 8, 0.1f, 0);
	controls[ARM_LEFT1] = ModelerControl("Left Arm-1 Angle", -15, 15, 0.1f, 0);
	controls[ARM_RIGHT1] = ModelerControl("Right Arm-1 Angle", -15, 15, 0.1f, 0);
	controls[ARM_LEFT2_1] = ModelerControl("Left Arm-2 Angle-1", -15, 15, 0.1f, 0);
	controls[ARM_RIGHT2_1] = ModelerControl("Right Arm-2 Angle-1", -15, 15, 0.1f, 0);
	controls[ARM_LEFT2_2] = ModelerControl("Left Arm-2 Angle-2", -8, 8, 0.1f, 0);
	controls[ARM_RIGHT2_2] = ModelerControl("Right Arm-2 Angle-2", -8, 8, 0.1f, 0);
	controls[JAW_LEFT] = ModelerControl("Left Jaw Angle", -12, 12, 0.1f, 0);
	controls[JAW_RIGHT] = ModelerControl("Right Jaw Angle", -12, 12, 0.1f, 0);
	controls[TAIL1] = ModelerControl("Tail-1 Angle", -15, 20, 0.1f, 0);
	controls[TAIL2] = ModelerControl("Tail-2 Angle", -15, 20, 0.1f, 0);
	controls[TAIL3] = ModelerControl("Tail-3 Angle", -15, 20, 0.1f, 0);
	controls[TAIL4] = ModelerControl("Tail-4 Angle", -15, 29, 0.1f, 0);
	controls[HOOK1] = ModelerControl("Hook Angle-1", -15, 15, 0.1f, 0);
	controls[HOOK2] = ModelerControl("Hook Angle-2", -15, 20, 0.1f, 0);

	controls[LIGHT_X] = ModelerControl("light X", -100, 100, 1, 0);
	controls[LIGHT_Y] = ModelerControl("light Y", -100, 100, 1, 0);
	controls[LIGHT_Z] = ModelerControl("light Z", -100, 100, 1, 0);
	ModelerApplication::Instance()->Init(&createMyModel, controls, NUMCONTROLS);
	return ModelerApplication::Instance()->Run();
}
