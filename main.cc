#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>


GLfloat gfPosX = -1.0;
GLfloat gfPosY = 1.0;

float startingX = -1.0;
float startingY = 1.0;

bool flopFlag = false;

GLfloat rateOfChange = .0001; //gfDeltaX

void shape(void){
        glBegin(GL_LINES);
		glColor3f(1.0, 0.0, 0.0);
			
                glVertex3f(0.0, 0.0, 0.0);
		
                glVertex3f(gfPosX, gfPosY, 0.0);
        glEnd();
		
	if(flopFlag == false){
		if((gfPosX == startingX || gfPosX < 1.0) && (gfPosY == startingY)){//Then start incrementing x
			gfPosX += rateOfChange;
		}/*Enter*/else{/*Once gfPosX > 1*/
			if(gfPosY <= -1.0){
				flopFlag = true;
			}
			gfPosY -= rateOfChange;
		}
	}else{
		if(gfPosX != startingX){
			gfPosX -= rateOfChange;
		}else if(gfPosY != startingY){
			gfPosY += rateOfChange;
		}

		if(gfPosX == startingX && gfPosY == startingY){
			flopFlag = false;
		}
	}
	std::cout<<"X: "<<gfPosX<<"  Y: "<<gfPosY<<std::endl;
	glutPostRedisplay();
}
 
void render(void){//This made me happy c:
	glClear(GL_COLOR_BUFFER_BIT);
	shape();
	glFlush();
	
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("A Square");
	glutDisplayFunc(render);
	glutMainLoop();

	return 0;
}
