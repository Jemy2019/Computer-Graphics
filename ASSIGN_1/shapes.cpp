#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include <math.h>
#include <iostream>

using namespace std;

#define PI 3.14159265

// colors map
float red[] = {1.0f, 0.0f, 0.0f, 0.7f};
float purple[] = {1.0f, 0.0f, 1.0f, 0.7f};
float yellow[] = {1.0f, 1.0f, 0.0f, 0.7f};
float green[] = {0.0f, 1.0f, 0.0f, 0.7f};
float blue[] = {0.0f, 0.0f, 1.0f, 0.7f};
float black[] = {0.0f, 0.0f, 0.0f, 0.7f};
float white[] = {1.0f, 1.0f, 1.0f, 0.7f};
float orange[]= {1.0f, 0.5f, 0.0f,0.7f};   
float magenta[]={1.0f, 0.0f, 1.0f,0.7f}; 


void drawShape(int y){
    glPushMatrix();
    for(int d= 3; d<=10; d++){
        glTranslated(16.0f, -11.0f, 0.0f);
        float angle = (180.0/d);
        float main_side = 7 * sin (angle*PI/180);
        float bisector = 7 * cos (angle*PI/180);
        for (int i = 0; i < d; ++i) {
            glRotatef((360.0/d), 0.0f, 0.0f, 1.0f);

            glColor4f(1.0f, 1.0f, 0.0f, 0.5f);
            glBegin(GL_TRIANGLES); 
            glVertex3f(bisector, main_side, -130.0f);
            glVertex3f(bisector, -1*main_side, -130.0f);
            glVertex3f(0.0f, 0.0f, -130.0f);

            glEnd(); 
        }   
    }
    glPopMatrix();
}

void drawCircle(int a, float colors[], float depth){
    
    int d = 1000;
    float angle = (180.0/d);
    float main_side = a * sin (angle*PI/180);
    float bisector = a * cos (angle*PI/180);
    for (int i = 0; i < d; ++i) {
        glRotatef((360.0/d), 0.0f, 0.0f, 1.0f);

        glBegin(GL_TRIANGLES); //Begin quadrilateral coordinates
        // glColor4f(1.0f, 0.0f, 0.0f, 0.7f);
        glColor4f(colors[0], colors[1], colors[2], colors[3]);
        glVertex3f(bisector, main_side, depth);
        glVertex3f(bisector, -1*main_side, depth);
        glVertex3f(0.0f, 0.0f, depth);

        glEnd(); //End quadrilateral coordinates
    }  

}

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();  

    // circle
    glPushMatrix();
        glTranslated(40.0f, 30.0f, 0.0f);
        drawCircle(10, green, -120);
        glTranslated(-80.0f, -60.0f, 0.0f);
        drawCircle(10, green, -120);
    glPopMatrix();
    glTranslated(-75.0f, 50.0f, 0.0f);
    drawShape(1);
    glutSwapBuffers();
}



void handleResize(int w, int h) {
	//Tell OpenGL how to convert from coordinates to pixel values
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective

	//Set the camera perspective
	glLoadIdentity(); //Reset the camera
	gluPerspective(45.0,                  //The camera angle
		(double)w / (double)h, //The width-to-height ratio
		1.0,                   //The near z clipping coordinate
		200.0);                //The far z clipping coordinate
}

void initRendering() {
	glEnable(GL_DEPTH_TEST);
}

void handleKeypress(unsigned char key, //The key that was pressed
	int x, int y) {    //The current mouse coordinates

	switch (key) {
	case 27: //Escape key
		exit(0); //Exit the program
	}
}

int main(int argc, char** argv) {
    ///Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400); //Set the window size
	glutCreateWindow("%%%%%%");
	initRendering(); //Initialize rendering


	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);

	glutMainLoop();
}
