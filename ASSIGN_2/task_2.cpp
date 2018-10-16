
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include <math.h>
#include <iostream>
#include<map>
#include<iterator>

using namespace std;

#define PI 3.14159265
float x_PAC = 0.0, y_PAC = 0.0, z = 0.0,\
 x_pac_displacment = 0.0, angle_PAC = 0.0f;
int f_mouse_pac = -1;
float red[] = {1.0f, 0.0f, 0.0f, 0.7f};
float purple[] = {1.0f, 0.0f, 1.0f, 0.7f};
float yellow[] = {1.0f, 1.0f, 0.0f, 0.7f};
float green[] = {0.0f, 1.0f, 0.0f, 0.7f};
float blue[] = {0.0f, 0.0f, 1.0f, 0.7f};
float black[] = {0.0f, 0.0f, 0.0f, 0.7f};
float white[] = {1.0f, 1.0f, 1.0f, 0.7f};
float orange[]= {1.0f, 0.5f, 0.0f,0.7f};     // Orange
float magenta[]={1.0f, 0.0f, 1.0f,0.7f};     // Magenta
map<pair<float,float>,int> food,walls;
// <pair<float,float>,int>::iterator itr;

void initRendering() {
	//Makes 3D drawing work when something is in front of something else
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
}

void drawMouth(int a, int rotate, float colors[]){
    float angle = (180.0/8);
    float main_side = a * sin (angle*PI/180);
    float bisector = a * cos (angle*PI/180);
    glPushMatrix();
        glRotatef(rotate, 0.0f, 0.0f, 1.0f);
        glColor4f(colors[0], colors[1], colors[2], colors[3]);
        glBegin(GL_TRIANGLES); //Begin quadrilateral coordinates
        glVertex3f(bisector, main_side, -197.0f);
        glVertex3f(bisector, -1*main_side, -198.0f);
        glVertex3f(0.0f, 0.0f, -198.0f);

        glEnd(); //End quadrilateral coordinates
    glPopMatrix();
}

void drawPolygon(int y){
    glTranslated(0.0f, -15.0f*y, 0.0f);
    glPushMatrix();
    for(int d= 3*y; d<3*y+3; d++){
        glTranslated(+50.0f, 0.0f, 0.0f);
        float angle = (180.0/d);
        float main_side = 5 * sin (angle*PI/180);
        float bisector = 5 * cos (angle*PI/180);
        for (int i = 0; i < d; ++i) {
            glRotatef((360.0/d), 0.0f, 0.0f, 1.0f);

            glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
            glBegin(GL_TRIANGLES); //Begin quadrilateral coordinates
            glVertex3f(bisector, main_side, -130.0f);
            glVertex3f(bisector, -1*main_side, -130.0f);
            glVertex3f(0.0f, 0.0f, -130.0f);

            glEnd(); //End quadrilateral coordinates
        }   
    }
    glPopMatrix();
}

void drawCircle(int a, float colors[], float depth){
    
    // int d = 1000;
     int d = 30;
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


// draw white grid 28*16 depth 20
void drawGrid(){
    glColor4f(white[0], white[1], white[2], white[3]);
    glPushMatrix();
        glTranslated(0.0f, 8.0f, 0.0f);
        glBegin(GL_LINES);

        glVertex3f(-14.5f, 0.1f, -20.0f);
        glVertex3f(14.5f, 0.1f, -20.0f);

        glEnd();

        // add to map of walls
        // walls.insert({{14.6,8.1},1});
        // walls.insert({{-14.6,8.1},1});

        glTranslated(-14.40f, -8.0f, 0.0f);

        glRotated(90.0f, 0.0f, 0.0f, 1.0f);

        glBegin(GL_LINES);

        glVertex3f(-8.1f, 0.1f, -20.0f);
        glVertex3f(8.1f, 0.1f, -20.0f);

        glEnd();

        
        glTranslated(-8.0f, -14.4f, 0.0f);

        glRotated(90.0f, 0.0f, 0.0f, 1.0f);

        glBegin(GL_LINES);

        glVertex3f(-14.51f, 0.1f, -20.0f);
        glVertex3f(14.5f, 0.1f, -20.0f);

        glEnd();

        glTranslated(-14.4f, -8.0f, 0.0f);

        glRotated(90.0f, 0.0f, 0.0f, 1.0f);

        glBegin(GL_LINES);

        glVertex3f(-8.1f, 0.1f, -20.0f);
        glVertex3f(8.1f, 0.1f, -20.0f);

        glEnd();

    glPopMatrix();
}


// draw pac-man 
void drawPac_man(){
    //cout<<x_PAC<<" "<<y_PAC<<endl;
    food[{x_PAC,y_PAC}]=1;
    glPushMatrix();
        glTranslated(x_PAC, y_PAC, 0.0f);
        glRotated(angle_PAC, 0.0f, 0.0f, 1.0f);
        glPushMatrix();
            // body
            drawCircle(5.0f, yellow, -198.0f);

            // eye
            glPushMatrix();
                if(angle_PAC == 180.0f) {   
                    glRotated(angle_PAC, 0.0f, 0.0f, 1.0f);
                }
                glTranslated(0.0f, 2.0f, 0.0f);
                drawCircle(1.8f, red, -197.0f);
            glPopMatrix();
            
            // mouth
            glPushMatrix();
                x_pac_displacment +=0.2*f_mouse_pac;
                if(x_pac_displacment > 0.5f || x_pac_displacment <= -4.0f) f_mouse_pac = f_mouse_pac*-1;
                glTranslated(x_pac_displacment, 0.0f, 0.0f);
                drawMouth(7.0f, 180.f, black);
            glPopMatrix();

        glPopMatrix();

    glPopMatrix();
}


// draw Food
void drawPac_food(){

    for(int i=-10;i>-150;i-=20){
        for(int j=-10;j>-80;j-=10){
            glPushMatrix();
                glTranslated((float)i, (float)j, 0.0f);
                    // body
                if(!food[{i, j}])
                    drawCircle(1.8f, magenta, -197.0f);
            glPopMatrix();
         }
    //cout<<food[{i,0.0}]<<endl;

          for(int j=0;j<80;j+=10){
            glPushMatrix();
                glTranslated((float)i, (float)j, 0.0f);
                    // body
                if(!food[{i, j}])
                    drawCircle(1.8f, magenta, -197.0f);
            glPopMatrix();
          }
     }

    // float j=5.0;
    for(int i=10;i<150;i+=20){
          for(int j=0;j<80;j+=10){
            glPushMatrix();
                glTranslated((float)i, (float)j, 0.0f);
                    // body
                if(!food[{i, j}])
                    drawCircle(1.8f, magenta, -197.0f);
            glPopMatrix();
          }
            // j+=5;;
    //cout<<food[{i,0.0}]<<endl;
        for(int j=-10;j>-80;j-=10){
            glPushMatrix();
                glTranslated((float)i, (float)j, 0.0f);
                    // body
                if(!food[{i, j}])
                    drawCircle(1.8f, magenta, -197.0f);
            glPopMatrix();
         }
     }

    
}
void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
    glLoadIdentity(); //Reset the drawing perspective  
    
    drawGrid();

    drawPac_man();

    drawPac_food();

    glutPostRedisplay();              //Tell GLUT that the display has changed
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

void handleKeypress(unsigned char key, //The key that was pressed
	int x, int y) {    //The current mouse coordinates
    // cout << (int)key;
	switch (key) {
	case 27: //Escape key
		exit(0); //Exit the program
    case 56: // move PAC-MAN up => 8
		y_PAC += 10.0f; // speed 1.0
        angle_PAC = -90.0f;
        break;
    case 53: // move PAC-MAN down => 5
		y_PAC -= 10.0f; // speed 1.0
        angle_PAC = 90.0f;
        break;
    case 54: // move PAC-MAN right => 6
		x_PAC += 10.0f; // speed 1.0
        angle_PAC = 180.0f;
        break;
    case 52: // move PAC-MAN left => 4
		x_PAC -= 10.0f; // speed 1.0
        angle_PAC = 0.0f;
        break;
	}
}

int main(int argc, char** argv) {
    ///Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400); //Set the window size
   
	//Create the window
	glutCreateWindow("PIC-MAN Game");
	initRendering(); //Initialize rendering

	//Set handler functions for drawing, keypresses, and window resizes
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);

	glutMainLoop(); //Start the main loop.  glutMainLoop doesn't return.
}
