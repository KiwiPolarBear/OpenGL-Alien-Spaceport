//  ========================================================================
//  Adam Hunt ID:99273354 COSC 363 Assignment 1 2016
//  ========================================================================
 
#include <iostream>
#include <climits>
#include <math.h> 
#include <GL/freeglut.h>
#include "loadBMP.h"
#include "loadTGA.h"
using namespace std;

GLuint txId[11];  //Texture ID

//Settings for the skybox
float skyLength = 2000.0;
float skyHight = 1000.0;
float skyWidth = 2000.0;

//Settings for the walls
float wallLength = 300.0;
float wallHight = 20.0;
float wallWidth = 5.0;

//Settings for the Garage
float buildingLength = 70.0;
float buildingHight = 40.0;
float buildingWidth = 70.0;

//Settings for the Abandoned Building
float abanLength = 40.0;
float abanHight = 40.0;
float abanWidth = 80.0;

//Settings for the spacecraft
float spacecraftHight = 10;
float speed = 0.0;
float rotateAngle = 0;
bool liftOff = false;
bool upDirection = false;

//settings for the patrolling alien
bool longRun = true;
bool toggle = true;
float alienForward = -125;
float alienX = -10;
float alienAngle = 0;
float alienBallAngle = 0;

//settings for the waving alien
int waveAngle = 0;
bool waveUp = true;

//Settings for the camera
float  eye_x = -140,  eye_y = 10,  eye_z = 140;    
float look_x = 200, look_y = 1, look_z = 200;    
float  theta = -0.7; 
float takeoffCamera = 100;                             
int step = 0;
bool cameraToggle = true;
int keyNum = 0;

//Settings for light
float white[4]  = {1.0, 1.0, 1.0, 1.0};
float grey[4] = {0.2, 0.2, 0.2, 1.0};
float black[4] = {0};

//Settings for the portal
float zMovement = 0;
bool flip = true;

//Settings for the vehicle
float vehicleZ = 180;
float vehicleSpeed = 0;
bool vehicleForward = true;
float waitTime = 0;



//------Function to load a texture in bmp format  ------------------------
void loadTexture() {
    
	glGenTextures(11, txId); 
    			
    //Wall texture            	
	glBindTexture(GL_TEXTURE_2D, txId[0]);	
    loadBMP("brickwall.BMP");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    //Floor texture
    glBindTexture(GL_TEXTURE_2D, txId[1]);	
    loadBMP("concrete.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    //Garage
    glBindTexture(GL_TEXTURE_2D, txId[2]);	
    loadBMP("brickgarage.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    //Garage wall
    glBindTexture(GL_TEXTURE_2D, txId[3]);	
    loadBMP("greybrickwall.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    //Building
    glBindTexture(GL_TEXTURE_2D, txId[4]);	
    loadBMP("building.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    //Front
    glBindTexture(GL_TEXTURE_2D, txId[5]);	
    loadTGA("front.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    //Back
    glBindTexture(GL_TEXTURE_2D, txId[6]);	
    loadTGA("back.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    //Top
    glBindTexture(GL_TEXTURE_2D, txId[7]);	
    loadTGA("top.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    //Left
    glBindTexture(GL_TEXTURE_2D, txId[8]);	
    loadTGA("left.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	;
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    //Right
    glBindTexture(GL_TEXTURE_2D, txId[9]);	
    loadTGA("right.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    //Bottom
    glBindTexture(GL_TEXTURE_2D, txId[10]);	
    loadTGA("bottom.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
}

//-- Alien Vehicle --------------------------------------------------------
void drawVehicle() {
    
    //Portal
    glPushMatrix();
        glColor3f(0.0, 0.0, 1.0);
        glScalef(25, 6, 40);
        glTranslatef(0, 2.5, 0);
        glRotatef(0, 0, 0, 0);
        glutSolidCube(1);
    glPopMatrix();
    
    //Wheel 1
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);
    glColor3f(0.0, 1.0, 0.0);
    glScalef(2.5, 2.5, 2.5);
    glTranslatef(3, 4, -6);
    glRotatef(alienBallAngle, 0, 1, 0);
    glutSolidDodecahedron();
    glPopMatrix();
    
    //Wheel 2
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);
    glColor3f(0.0, 1.0, 0.0);
    glScalef(2.5, 2.5, 2.5);
    glTranslatef(-3, 4, -6);
    glRotatef(alienBallAngle, 0, 1, 0);
    glutSolidDodecahedron();
    glPopMatrix();
    
    //Wheel 3
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);
    glColor3f(0.0, 1.0, 0.0);
    glScalef(2.5, 2.5, 2.5);
    glTranslatef(3, 4, 6);
    glRotatef(alienBallAngle, 0, 1, 0);
    glutSolidDodecahedron();
    glPopMatrix();
    
    //Wheel 4
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);
    glColor3f(0.0, 1.0, 0.0);
    glScalef(2.5, 2.5, 2.5);
    glTranslatef(-3, 4, 6);
    glRotatef(alienBallAngle, 0, 1, 0);
    glutSolidDodecahedron();
    glPopMatrix();

}

//-- Portal --------------------------------------------------------
void drawPortal() {
    
    //Portal
    glPushMatrix();
        glColor3f(0.0, 0.0, 1.0);
        glScalef(1, 1, 1);
        glTranslatef(0, 25, zMovement);
        glRotatef(0, 0, 0, 0);
        glutSolidTorus(2, 21, 20, 20);
    glPopMatrix();
    
    //Portal
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glScalef(1, 1, 1);
        glTranslatef(0, 25, -zMovement);
        glRotatef(0, 0, 0, 0);
        glutSolidTorus(2, 18, 20, 20);
    glPopMatrix();
    
    //Portal
    glPushMatrix();
        glColor3f(0.0, 0.0, 1.0);
        glScalef(1, 1, 1);
        glTranslatef(0, 25, zMovement);
        glRotatef(0, 0, 0, 0);
        glutSolidTorus(2, 15, 20, 20);
    glPopMatrix();
    
    //Portal
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glScalef(1, 1, 1);
        glTranslatef(0, 25, -zMovement);
        glRotatef(0, 0, 0, 0);
        glutSolidTorus(2, 12, 20, 20);
    glPopMatrix();
    
    //Portal
    glPushMatrix();
        glColor3f(0.0, 0.0, 1.0);
        glScalef(1, 1, 1);
        glTranslatef(0, 25, zMovement);
        glRotatef(0, 0, 0, 0);
        glutSolidTorus(2, 9, 20, 20);
    glPopMatrix();
    
    //Portal
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glScalef(1, 1, 1);
        glTranslatef(0, 25, -zMovement);
        glRotatef(0, 0, 0, 0);
        glutSolidTorus(2, 6, 20, 20);
    glPopMatrix();
    
    //Portal
    glPushMatrix();
        glColor3f(0.0, 0.0, 1.0);
        glScalef(1, 1, 1);
        glTranslatef(0, 25, zMovement);
        glRotatef(0, 0, 0, 0);
        glutSolidTorus(2, 3, 20, 20);
    glPopMatrix();
    
    //Portal
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glScalef(1, 1, 1);
        glTranslatef(0, 25, -zMovement);
        glRotatef(0, 0, 0, 0);
        glutSolidTorus(1, 1, 20, 20);
    glPopMatrix();
    
}

//-- Garage road --------------------------------------------------------
void garageRoad() {
    
    //Bottom Pad
    glPushMatrix();
        glTranslatef(-65, 0, -50);
        glPushMatrix();
            glMaterialfv(GL_FRONT, GL_SPECULAR, black);
            glMaterialf(GL_FRONT, GL_SHININESS, 50);
            glColor3f(0.0, 0.0, 0.0);
            glScalef(70, 1, 400);
            glRotatef(0, 0, 0, 0);
            glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, black);
    
    for (int i = -100; i < 180; i+= 70) {
        glPushMatrix();
            glTranslatef(-65, 0.3, i);
            glColor3f(1.0, 1.0, 1.0);
            glScalef(5, 1, 40);
            glRotatef(0, 0, 0, 0);
            glutSolidCube(1);
        glPopMatrix();
    }
}

//--------draws a single skybox----------------------------
void drawSkybox() {
    
    glEnable(GL_TEXTURE_2D);
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, txId[6]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    
    glBegin(GL_QUADS);
        //Facing +z (Front side)
        glNormal3f(0.0, 0.0, 1.0);        
        glTexCoord2f(1.0, 0.0); glVertex3f(0.0, 0.0, skyWidth);
        glTexCoord2f(0.0, 0.0); glVertex3f(skyLength, 0.0, skyWidth);
        glTexCoord2f(0.0, 1.0); glVertex3f(skyLength, skyHight, skyWidth);
        glTexCoord2f(1.0, 1.0); glVertex3f(0.0, skyHight, skyWidth);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, txId[5]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    glBegin(GL_QUADS);
        //Facing -z (Back side)
        glNormal3f(0.0, 0.0, -1.0);           
        glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(skyLength, 0.0, 0.0);
        glTexCoord2f(1.0, 1.0); glVertex3f(skyLength, skyHight, 0.0);
        glTexCoord2f(0.0, 1.0); glVertex3f(0.0, skyHight, 0.0);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, txId[7]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    
    glBegin(GL_QUADS);
        //Facing +y (Top side)
        glNormal3f(0.0, 1.0, 0.0);        
        glTexCoord2f(0.0, 0.0); glVertex3f(0.0, skyHight, 0.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(skyLength, skyHight, 0.0);
        glTexCoord2f(1.0, 1.0); glVertex3f(skyLength, skyHight, skyWidth);
        glTexCoord2f(0.0, 1.0); glVertex3f(0.0, skyHight, skyWidth);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, txId[9]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    
    glBegin(GL_QUADS);
        //Facing -x (Left side)
        glNormal3f(-1.0, 0.0, 0.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(0.0, 0.0, 0.0);       
        glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, skyWidth);
        glTexCoord2f(0.0, 1.0); glVertex3f(0.0, skyHight, skyWidth);
        glTexCoord2f(1.0, 1.0); glVertex3f(0.0, skyHight, 0.0);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, txId[8]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    
    glBegin(GL_QUADS);
        //Facing +x (Right side)
        glNormal3f(1.0, 0.0, 0.0);   
        glTexCoord2f(0.0, 0.0); glVertex3f(skyLength, 0.0, 0.0);       
        glTexCoord2f(1.0, 0.0); glVertex3f(skyLength, 0.0, skyWidth);
        glTexCoord2f(1.0, 1.0); glVertex3f(skyLength, skyHight, skyWidth);
        glTexCoord2f(0.0, 1.0); glVertex3f(skyLength, skyHight, 0.0);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, txId[10]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    
    glBegin(GL_QUADS);

    //Bottom
    glNormal3f(0.0, -1.0, 0.0); 
		glTexCoord2f(0.0, 0.0); glVertex3f(-skyLength, 0, -skyLength);
		glTexCoord2f(0.0, 1.0); glVertex3f(-skyLength, 0, skyLength);
		glTexCoord2f(1.0, 1.0); glVertex3f(skyLength, 0, skyLength);
		glTexCoord2f(1.0, 0.0); glVertex3f(skyLength, 0, -skyLength);
	glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

//--------draws a single building----------------------------
void drawAbandonedBuilding() {
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, txId[4]);
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    glBegin(GL_QUADS);
        //Facing +z (Front side)
        glNormal3f(0.0, 0.0, 1.0);        
        glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, abanWidth);
        glTexCoord2f(0.5, 0.0); glVertex3f(abanLength, 0.0, abanWidth);
        glTexCoord2f(0.5, 1.0); glVertex3f(abanLength, abanHight, abanWidth);
        glTexCoord2f(0.0, 1.0); glVertex3f(0.0, abanHight, abanWidth);

        //Facing -z (Back side)
        glNormal3f(0.0, 0.0, -1.0);           
        glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
        glTexCoord2f(0.5, 0.0); glVertex3f(abanLength, 0.0, 0.0);
        glTexCoord2f(0.5, 1.0); glVertex3f(abanLength, abanHight, 0.0);
        glTexCoord2f(0.0, 1.0); glVertex3f(0.0, abanHight, 0.0);
        
        //Facing +y (Top side)
        glNormal3f(0.0, 1.0, 0.0);        
        glTexCoord2f(0.0, 0.0); glVertex3f(0.0, abanHight, 0.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(abanLength, abanHight, 0.0);
        glTexCoord2f(1.0, 0.2); glVertex3f(abanLength, abanHight, abanWidth);
        glTexCoord2f(0.0, 0.2); glVertex3f(0.0, abanHight, abanWidth);
        
        //Facing -x (Left side)
        glNormal3f(-1.0, 0.0, 0.0);
        glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);       
        glTexCoord2f(1.0, 0.0); glVertex3f(0.0, 0.0, abanWidth);
        glTexCoord2f(1.0, 1.0); glVertex3f(0.0, abanHight, abanWidth);
        glTexCoord2f(0.0, 1.0); glVertex3f(0.0, abanHight, 0.0);
        
        //Facing +x (Right side)
        glNormal3f(1.0, 0.0, 0.0);   
        glTexCoord2f(0.0, 0.0); glVertex3f(abanLength, 0.0, 0.0);       
        glTexCoord2f(1.0, 0.0); glVertex3f(abanLength, 0.0, abanWidth);
        glTexCoord2f(1.0, 1.0); glVertex3f(abanLength, abanHight, abanWidth);
        glTexCoord2f(0.0, 1.0); glVertex3f(abanLength, abanHight, 0.0);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

//--------draws a single building----------------------------
void drawBuilding() {
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, txId[2]);
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    glBegin(GL_QUADS);
        //Facing +z (Front side)
        glNormal3f(0.0, 0.0, 1.0);        
        glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, buildingWidth);
        glTexCoord2f(1.0, 0.0); glVertex3f(buildingLength, 0.0, buildingWidth);
        glTexCoord2f(1.0, 1.0); glVertex3f(buildingLength, buildingHight, buildingWidth);
        glTexCoord2f(0.0, 1.0); glVertex3f(0.0, buildingHight, buildingWidth);
    glEnd();
    
        glBindTexture(GL_TEXTURE_2D, txId[3]);
        glColor4f(1.0, 1.0, 1.0, 1.0);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        
    glBegin(GL_QUADS);
        //Facing -z (Back side)
        glNormal3f(0.0, 0.0, -1.0);           
        glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(buildingLength, 0.0, 0.0);
        glTexCoord2f(1.0, 1.0); glVertex3f(buildingLength, buildingHight, 0.0);
        glTexCoord2f(0.0, 1.0); glVertex3f(0.0, buildingHight, 0.0);
        
        //Facing +y (Top side)
        glNormal3f(0.0, 1.0, 0.0);        
        glTexCoord2f(0.0, 0.0); glVertex3f(0.0, buildingHight, 0.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(buildingLength, buildingHight, 0.0);
        glTexCoord2f(1.0, 1.0); glVertex3f(buildingLength, buildingHight, buildingWidth);
        glTexCoord2f(0.0, 1.0); glVertex3f(0.0, buildingHight, buildingWidth);
        
        //Facing -x (Left side)
        glNormal3f(-1.0, 0.0, 0.0);
        glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);       
        glTexCoord2f(1.0, 0.0); glVertex3f(0.0, 0.0, buildingWidth);
        glTexCoord2f(1.0, 1.0); glVertex3f(0.0, buildingHight, buildingWidth);
        glTexCoord2f(0.0, 1.0); glVertex3f(0.0, buildingHight, 0.0);
        
        //Facing +x (Right side)
        glNormal3f(1.0, 0.0, 0.0);   
        glTexCoord2f(0.0, 0.0); glVertex3f(buildingLength, 0.0, 0.0);       
        glTexCoord2f(1.0, 0.0); glVertex3f(buildingLength, 0.0, buildingWidth);
        glTexCoord2f(1.0, 1.0); glVertex3f(buildingLength, buildingHight, buildingWidth);
        glTexCoord2f(0.0, 1.0); glVertex3f(buildingLength, buildingHight, 0.0);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

//--------draws a single wall----------------------------
void drawWall() {
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, txId[0]);
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    glBegin(GL_QUADS);
        //Facing +z (Front side)
        glNormal3f(0.0, 0.0, 1.0);        
        glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, wallWidth);
        glTexCoord2f(10.0, 0.0); glVertex3f(wallLength, 0.0, wallWidth);
        glTexCoord2f(10.0, 1.0); glVertex3f(wallLength, wallHight, wallWidth);
        glTexCoord2f(0.0, 1.0); glVertex3f(0.0, wallHight, wallWidth);
        
        //Facing -z (Back side)
        glNormal3f(0.0, 0.0, -1.0);           
        glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
        glTexCoord2f(10.0, 0.0); glVertex3f(wallLength, 0.0, 0.0);
        glTexCoord2f(10.0, 1.0); glVertex3f(wallLength, wallHight, 0.0);
        glTexCoord2f(0.0, 1.0); glVertex3f(0.0, wallHight, 0.0);
        
        //Facing +y (Top side)
        glNormal3f(0.0, 1.0, 0.0);        
        glTexCoord2f(0.0, 0.0); glVertex3f(0.0, wallHight, 0.0);
        glTexCoord2f(10.0, 0.0); glVertex3f(wallLength, wallHight, 0.0);
        glTexCoord2f(10.0, 0.2); glVertex3f(wallLength, wallHight, wallWidth);
        glTexCoord2f(0.0, 0.2); glVertex3f(0.0, wallHight, wallWidth);
        
        //Facing -x (Left side)
        glNormal3f(-1.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);       
        glVertex3f(0.0, 0.0, wallWidth);
        glVertex3f(0.0, wallHight, wallWidth);
        glVertex3f(0.0, wallHight, 0.0);
        
        //Facing +x (Right side)
        glNormal3f(1.0, 0.0, 0.0);   
        glVertex3f(wallLength, 0.0, 0.0);       
        glVertex3f(wallLength, 0.0, wallWidth);
        glVertex3f(wallLength, wallHight, wallWidth);
        glVertex3f(wallLength, wallHight, 0.0);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

//--------draws all 4 walls----------------------------
void drawAllWalls() {
    
    glPushMatrix();
        glTranslatef(-150.0, 0.0, 150);
        drawWall();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(-145.0, 0.0, -150);
        drawWall();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(-150.0, 0.0, 150);
        glRotatef(90, 0.0, 1.0 , 0.0);
        drawWall();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(150.0, 0.0, 155);
        glRotatef(90, 0.0, 1.0 , 0.0);
        drawWall();
    glPopMatrix();
}

//--------Draws a lamp post----------------------------
void drawLampPost() {
    
    //Post
    glPushMatrix();
        glColor3f(0.0, 1.0, 1.0);
        glScalef(1, 75, 1);
        glTranslatef(0, 0, 0);
        glRotatef(0, 0, 0, 0);
        glutSolidCube(1);
    glPopMatrix();
    
    //Bulb
    glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glScalef(1, 1, 1);
        glTranslatef(0, 35, 0);
        glRotatef(0, 0, 0, 0);
        glutSolidSphere(5, 20, 20);
    glPopMatrix();
    
    //Top
    glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glScalef(1, 1, 1);
        glTranslatef(0, 38, 0);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(7, 3, 20, 20);
    glPopMatrix();
}

//--------Draws a spaceship----------------------------
void drawSpaceShip() {
    
    //Outer Ring
    glPushMatrix();
        glColor3f(0.0, 1.0, 0.0);
        glScalef(1, 0.3, 1);
        glTranslatef(0, 65, 0);
        glRotatef(90, 1, 0, 0);
        glutSolidTorus(8, 20, 20, 20);
    glPopMatrix();
    
    //Inner Pod
    glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glScalef(1, 0.5, 1);
        glTranslatef(0, 40, 0);
        glRotatef(0, 0, 0, 0);
        glutSolidSphere(20, 20, 20);
    glPopMatrix();
    
    //Outer Bumps
    for (int i = 0; i < 8; i++) {
        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_SPECULAR, white);
        glMaterialf(GL_FRONT, GL_SHININESS, 50);
        glRotatef(rotateAngle, 0, 1, 0);
        glPushMatrix();
            glColor3f(0.0, 0.0, 1.0);
            glScalef(1, 1, 1);
            glTranslatef(0, 21, 23);
            glutSolidSphere(3, 20, 20);
        glPopMatrix();
        glPopMatrix();
        rotateAngle += 45;
    }
}

//--------draws an alien----------------------------
void drawPatrollingAlienShadow() {
    
    //Head
    glPushMatrix();
    glColor4f(0.2, 0.2, 0.2, 1.0);
    glScalef(1, 1.5, 1);
    glTranslatef(0, 15, 0);
    glutSolidSphere(6, 20, 20);
    glPopMatrix();
    
    //Left Eye
    glPushMatrix();
    glColor4f(0.2, 0.2, 0.2, 1.0);
    glScalef(1, 1, 1);
    glTranslatef(2, 25, 5);
    glutSolidSphere(2, 20, 20);
    glPopMatrix();
    
    //Right Eye
    glPushMatrix();
    glColor4f(0.2, 0.2, 0.2, 1.0);
    glScalef(1, 1, 1);
    glTranslatef(-2, 25, 5);
    glutSolidSphere(2, 20, 20);
    glPopMatrix();
    
    //Left Ear
    glPushMatrix();
    glColor4f(0.2, 0.2, 0.2, 1.0);
    glScalef(1, 1, 1);
    glTranslatef(5, 28, 0);
    glutSolidTorus(1, 2, 20, 20);
    glPopMatrix();
    
    //Right Ear
    glPushMatrix();
    glColor4f(0.2, 0.2, 0.2, 1.0);
    glScalef(1, 1, 1);
    glTranslatef(-5, 28, 0);
    glutSolidTorus(1, 2, 20, 20);
    glPopMatrix();
    
    //Mouth
    glPushMatrix();
    glColor4f(0.2, 0.2, 0.2, 1.0);
    glScalef(1, 1, 1);
    glTranslatef(0, 19, 6);
    glutSolidTorus(1, 2, 20, 20);
    glPopMatrix();
    
    //Left Arm
    glPushMatrix();
    glColor4f(0.2, 0.2, 0.2, 1.0);
    glScalef(1, 1, 1);
    glTranslatef(0, 16, 0);
    glRotatef(50, 0, 1, 0);
    GLUquadric *q;
    q = gluNewQuadric();
    gluCylinder(q, 2, 2, 20, 20,
    20);
    gluQuadricDrawStyle(q, GLU_FILL);
    glPopMatrix();
    
    //Right Arm
    glPushMatrix();
    glColor4f(0.2, 0.2, 0.2, 1.0);
    glScalef(1, 1, 1);
    glTranslatef(0, 16, 0);
    glRotatef(310, 0, 1, 0);
    GLUquadric *t;
    t = gluNewQuadric();
    gluCylinder(t, 2, 2, 20, 20,
    20);
    gluQuadricDrawStyle(q, GLU_FILL);
    glPopMatrix();
    
    //Left Hand
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);
    glColor4f(0.2, 0.2, 0.2, 1.0);
    glScalef(1, 1, 1);
    glTranslatef(14, 16, 12);
    glutSolidSphere(3, 20, 20);
    glPopMatrix();
    
    //Right Hand
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);
    glColor4f(0.2, 0.2, 0.2, 1.0);
    glScalef(1, 1, 1);
    glTranslatef(-14, 16, 12);
    glutSolidSphere(3, 20, 20);
    glPopMatrix();
    
    //Floating Body Ball
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);
    glColor4f(0.2, 0.2, 0.2, 1.0);
    glRotatef(alienBallAngle, 0, 1, 0);
    glScalef(2.5, 2.5, 2.5);
    glTranslatef(0, 3, 0);
    glutSolidDodecahedron();
    glPopMatrix();
}

//--------draws an alien----------------------------
void drawPatrollingAlien() {
    
    //Head
    glPushMatrix();
    glColor3f(0.0, 1.0, 0.0);
    glScalef(1, 1.5, 1);
    glTranslatef(0, 15, 0);
    glutSolidSphere(6, 20, 20);
    glPopMatrix();
    
    //Left Eye
    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glScalef(1, 1, 1);
    glTranslatef(2, 25, 5);
    glutSolidSphere(2, 20, 20);
    glPopMatrix();
    
    //Right Eye
    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glScalef(1, 1, 1);
    glTranslatef(-2, 25, 5);
    glutSolidSphere(2, 20, 20);
    glPopMatrix();
    
    //Left Ear
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glScalef(1, 1, 1);
    glTranslatef(5, 28, 0);
    glutSolidTorus(1, 2, 20, 20);
    glPopMatrix();
    
    //Right Ear
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glScalef(1, 1, 1);
    glTranslatef(-5, 28, 0);
    glutSolidTorus(1, 2, 20, 20);
    glPopMatrix();
    
    //Mouth
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glScalef(1, 1, 1);
    glTranslatef(0, 19, 6);
    glutSolidTorus(1, 2, 20, 20);
    glPopMatrix();
    
    //Left Arm
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glScalef(1, 1, 1);
    glTranslatef(0, 16, 0);
    glRotatef(50, 0, 1, 0);
    GLUquadric *q;
    q = gluNewQuadric();
    gluCylinder(q, 2, 2, 20, 20,
    20);
    gluQuadricDrawStyle(q, GLU_FILL);
    glPopMatrix();
    
    //Right Arm
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glScalef(1, 1, 1);
    glTranslatef(0, 16, 0);
    glRotatef(310, 0, 1, 0);
    GLUquadric *t;
    t = gluNewQuadric();
    gluCylinder(t, 2, 2, 20, 20,
    20);
    gluQuadricDrawStyle(q, GLU_FILL);
    glPopMatrix();
    
    //Left Hand
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);
    glColor3f(0.0, 1.0, 0.0);
    glScalef(1, 1, 1);
    glTranslatef(14, 16, 12);
    glutSolidSphere(3, 20, 20);
    glPopMatrix();
    
    //Right Hand
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);
    glColor3f(0.0, 1.0, 0.0);
    glScalef(1, 1, 1);
    glTranslatef(-14, 16, 12);
    glutSolidSphere(3, 20, 20);
    glPopMatrix();
    
    //Floating Body Ball
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);
    glColor3f(0.0, 1.0, 0.0);
    glRotatef(alienBallAngle, 0, 1, 0);
    glScalef(2.5, 2.5, 2.5);
    glTranslatef(0, 3, 0);
    glutSolidDodecahedron();
    glPopMatrix();
}

//--------draws an alien----------------------------
void drawWavingAlien() {
    
    //Head
    glPushMatrix();
    glColor3f(0.0, 1.0, 0.0);
    glScalef(1, 1.5, 1);
    glTranslatef(0, 15, 0);
    glutSolidSphere(6, 20, 20);
    glPopMatrix();
    
    //Left Eye
    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glScalef(1, 1, 1);
    glTranslatef(2, 25, 5);
    glutSolidSphere(2, 20, 20);
    glPopMatrix();
    
    //Right Eye
    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glScalef(1, 1, 1);
    glTranslatef(-2, 25, 5);
    glutSolidSphere(2, 20, 20);
    glPopMatrix();
    
    //Left Ear
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glScalef(1, 1, 1);
    glTranslatef(5, 28, 0);
    glutSolidTorus(1, 2, 20, 20);
    glPopMatrix();
    
    //Right Ear
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glScalef(1, 1, 1);
    glTranslatef(-5, 28, 0);
    glutSolidTorus(1, 2, 20, 20);
    glPopMatrix();
    
    //Mouth
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glScalef(1, 1, 1);
    glTranslatef(0, 19, 6);
    glutSolidTorus(1, 2, 20, 20);
    glPopMatrix();
    
    //Left Arm
    glPushMatrix();
    glTranslatef(0, 16, 0);
    glRotatef(waveAngle, 0, 0, 1);
    glTranslatef(0, -16, 0);
    
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glScalef(1, 1, 1);
    glTranslatef(0, 16, 0);
    glRotatef(90, 0, 1, 0);
    GLUquadric *q;
    q = gluNewQuadric();
    gluCylinder(q, 2, 2, 20, 20,
    20);
    gluQuadricDrawStyle(q, GLU_FILL);
    glPopMatrix();
    
    //Left Hand
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);
    glColor3f(0.0, 1.0, 0.0);
    glScalef(1, 1, 1);
    glTranslatef(20, 16, 0);
    glutSolidSphere(3, 20, 20);
    glPopMatrix();
    glPopMatrix();
    
    //Right Arm
    glPushMatrix();
    glTranslatef(0, 16, 0);
    glRotatef(-waveAngle, 0, 0, 1);
    glTranslatef(0, -16, 0);
    
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glScalef(1, 1, 1);
    glTranslatef(0, 16, 0);;
    glRotatef(270, 0, 1, 0);
    GLUquadric *t;
    t = gluNewQuadric();
    gluCylinder(t, 2, 2, 20, 20,
    20);
    gluQuadricDrawStyle(q, GLU_FILL);
    glPopMatrix();
    
    //Right Hand
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);
    glColor3f(0.0, 1.0, 0.0);
    glScalef(1, 1, 1);
    glTranslatef(-20, 16, 0);
    glutSolidSphere(3, 20, 20);
    glPopMatrix();
    glPopMatrix();
    
    //Floating Body Ball
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);
    glColor3f(0.0, 1.0, 0.0);
    glRotatef(alienBallAngle, 0, 1, 0);
    glScalef(2.5, 2.5, 2.5);
    glTranslatef(0, 3, 0);
    glutSolidDodecahedron();
    glPopMatrix();
}

//----------Draws a floor quad-------------------
void drawFloor() {
    
    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, txId[1]);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor4f(1.0, 1.0, 1.0, 1.0);
    
    float size = 210;
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(-size, -0.1, -size);
		glTexCoord2f(0.0, 20.0); glVertex3f(-size, -0.1, size);
		glTexCoord2f(20.0, 20.0); glVertex3f(size, -0.1, size);
		glTexCoord2f(20.0, 0.0); glVertex3f(size, -0.1, -size);
	glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

//--Display: ----------------------------------------------------------------------
//--This is the main display module containing function calls for generating
//--the scene.
void display() {
    
    //Lamp Light Source
    float lgt_pos[] = {143.0, 35.0, 143.0, 1.0}; 
    float lgt_pos1[] = {143.0, 35.0, -138.0, 1.0}; 
    
    float shadowMat[16] = { 35,0,0,0, -143,0,-143,-1,
                            0,0,35,0, 0,0,0,35 };
    
    //Display Settings
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    
    //Camera view and direction
    float dir_x = -sin(theta), dir_y = 0,  dir_z = -cos(theta);
    eye_x = eye_x + step*dir_x;
    eye_z = eye_z + step*dir_z;
    if (eye_x >=145) eye_x = 145;
    else if (eye_x <= -140) eye_x = -140;
    else if (eye_z >= 145) eye_z = 145;
    else if (eye_z <= -135) eye_z = -135; 
	look_x = eye_x + 2*dir_x;
	look_y = eye_y + 2*dir_y;
	look_z = eye_z + 2*dir_z;
    if (keyNum == 0) {
        gluLookAt(eye_x, eye_y, eye_z,  look_x, look_y, look_z,   0, 1, 0);
        //gluLookAt(0, 300, 600, 0, 100, 0, 0, 1, 0);
    } else if (keyNum == 1) {
        gluLookAt(200, takeoffCamera, -200, 120, takeoffCamera-90, -120, 0, 1, 0);
    } else if (keyNum == 2) {
        gluLookAt(0, 400, 0, 0, 0, 1, 0, 1, 0);
    }
    step = 0;
    
    
    //Portal
    glPushMatrix();
        glTranslatef(-65, -4, vehicleZ);
        drawVehicle();
    glPopMatrix();
    
    //Portal Frame
    glPushMatrix();
        glColor3f(0.0, 1.0, 0.0);
        glTranslatef(-65, -10, 151);
        glScalef(50, 100, 4);
        glutSolidCube(1);
    glPopMatrix();
    
    //Portal
    glPushMatrix();
        glTranslatef(-65, -10, 150);
        drawPortal();
    glPopMatrix();
    
    //Skybox
    glPushMatrix();
        glTranslatef(-1000, -400, -1000);
        drawSkybox();
    glPopMatrix();
    
    //Abandoned Building
    glPushMatrix();
        glTranslatef(148, 0, 0);
        drawAbandonedBuilding();
    glPopMatrix();
    
    //Garage Road
    garageRoad();

    //Garage
    glPushMatrix();
        glTranslatef(-100, 0, -210);
        drawBuilding();
    glPopMatrix();
    
    //Lamp post
    glLightfv(GL_LIGHT0, GL_POSITION, lgt_pos);
    glPushMatrix();
        glTranslatef(150, 0, 150);
        drawLampPost();
    glPopMatrix();
    
    //Lamp post
    glLightfv(GL_LIGHT1, GL_POSITION, lgt_pos1);
    glPushMatrix();
        glTranslatef(150, 0, -145);
        drawLampPost();
    glPopMatrix();
    
    //Space Ship
    glPushMatrix(); 
        glTranslatef(120, spacecraftHight, -120);
        glScalef(2.0, 2.0, 2.0);
        drawSpaceShip();
    glPopMatrix();
    
    //Patrolling Alien
    glPushMatrix();
        glRotatef(alienAngle, 0, 1, 0);
        glTranslatef(alienX, 0, alienForward);
        glScalef(0.7, 0.7, 0.7);
        drawPatrollingAlien();
    glPopMatrix();
    
    //Waving Alien
    glPushMatrix();
        glRotatef(0, 0, 0, 0);
        glTranslatef(-65, 0, -100);
        glScalef(0.7, 0.7, 0.7);
        drawWavingAlien();
    glPopMatrix();
    
    //alienShadow
    glDisable(GL_LIGHTING);
    glPushMatrix();
        glMultMatrixf(shadowMat);
        glRotatef(alienAngle, 0, 1, 0);
        glTranslatef(alienX, 0, alienForward);
        glScalef(0.7, 0.7, 0.7);
        glColor4f(0.2, 0.2, 0.2, 1.0);
        drawPatrollingAlienShadow();
    glPopMatrix();
    glEnable(GL_LIGHTING);
    
    //Compound Walls
    glPushMatrix();
        drawAllWalls();
    glPopMatrix();
    
    //Compound Floor
    drawFloor();
    
    glutSwapBuffers();	
	glFlush();
}

//------- Initialize OpenGL parameters -----------------------------------
void initialize() {
    
    loadTexture();
    
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);	//Background colour
    
    glPushMatrix();
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_AMBIENT, grey);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
        glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glPopMatrix();
    
    glPushMatrix();
    glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT1);
        glLightfv(GL_LIGHT1, GL_AMBIENT, grey);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
        glLightfv(GL_LIGHT1, GL_SPECULAR, white);
    glPopMatrix();
    
 	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 50); 
    
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45., 1.7, 1., 2000.);  //The camera view volume  
}

//------------ Timer Function ---------------------------------
void spaceTimer(int value) {
    
    if (upDirection && spacecraftHight < 10000) {
        takeoffCamera += speed;
        liftOff = true;
        spacecraftHight += speed;
        speed += 0.07;
        glutPostRedisplay();
    } else if (!upDirection && spacecraftHight > 20) {
        takeoffCamera = 100; 
        speed = 0;
        liftOff = false;
        spacecraftHight = 10;
        glutPostRedisplay();
    }
    glutTimerFunc(10, spaceTimer, value);
}

//------------ Timer Function ---------------------------------
void Timer(int value) {
    
    rotateAngle += 1.5;
    alienForward += 0.5;
    waitTime += 0.1;
    
    if (vehicleForward && waitTime > 10) {
        vehicleZ -= vehicleSpeed;
        vehicleSpeed -= 0.2;
    } else if (!vehicleForward && waitTime > 10) {
        vehicleZ += vehicleSpeed;
        vehicleSpeed += 0.2;
    }
    
    if (vehicleZ <= -70) {
        vehicleZ = -69;
        waitTime = 0.1;
        vehicleForward = false;
        vehicleSpeed = 0.1;
    } else if (vehicleZ >= 180) {
        vehicleZ = 179;
        waitTime = 0.1;
        vehicleForward = true;
        vehicleSpeed = 10;
    }
    
    if (flip) zMovement -= 0.1;
    else zMovement += 0.1;
    
    if (zMovement < -1) {
        flip = false;
    } else if (zMovement > 1) {
        flip = true;
    }
    
    if (waveUp) {
        waveAngle += 3;
    } else {
        waveAngle -= 3;
    }
    
    if (waveAngle >= 30) waveUp = false;
    else if (waveAngle <= -30) waveUp = true;
    
    if (alienForward >= 125 && longRun) {
        longRun = false;
        if (toggle) {
            toggle = false;
            alienForward = -10;
        } else {
            toggle = true;
            alienForward = -125;
        }
        alienX = -125;
        alienAngle += 90;
    } 
    
    if (alienForward >= 125 && !longRun && !toggle) {
        longRun = true;
        alienX = -125;
        alienForward = -125;
        alienAngle += 90;
    } 
    
    if (alienForward >= 10 && !longRun && toggle) {
        longRun = true;
        alienX = -10;
        alienForward = -125;
        alienAngle += 90;
    } 
    
    if (alienBallAngle == 360) {
        alienBallAngle = 0;
    }
    
    if (rotateAngle == 360) {
        rotateAngle = 0;
    }
    
    alienBallAngle += 3;
    glutPostRedisplay();
    glutTimerFunc(10, Timer, value);
}

//------------ Special key event callback ---------------------------------
// To enable the use of left and right arrow keys to rotate the scene
void special(int key, int x, int y) {
    
	step = 0;
	if(key == GLUT_KEY_LEFT) theta += 0.1;   //in radians
	else if(key == GLUT_KEY_RIGHT) theta -= 0.1;
	else if(key == GLUT_KEY_DOWN) step = -2;
	else if(key == GLUT_KEY_UP) step = 2;
    else if(key == GLUT_KEY_PAGE_UP) {
        if (eye_y < 25){
            eye_y++;
        }
    } else if(key == GLUT_KEY_PAGE_DOWN) {
        if (eye_y > 1) {
            eye_y--;
        }
    } else if(key == GLUT_KEY_HOME) {
      if (!liftOff) {
        upDirection = true;
    } else if (liftOff) {
        upDirection = false;
        }
    } else if (key == GLUT_KEY_INSERT) {
        keyNum++;
        if (keyNum > 2) keyNum = 0;
    }
	glutPostRedisplay();
}

//  ------- Main: Initialize glut window and register call backs -----------
int main(int argc, char** argv) {
    
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
   glutInitWindowSize (1280, 720); 
   glutInitWindowPosition (10, 10);
   glutCreateWindow ("Space Port");
   initialize();

   glutDisplayFunc(display);
   glutSpecialFunc(special); 
   glutTimerFunc(10, Timer, 0);
   glutTimerFunc(10, spaceTimer, 0);
   glutMainLoop();
   return 0;
}
