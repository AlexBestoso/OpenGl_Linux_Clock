#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>
#include <string>
#include <stdio.h>
#include <ctime>
#include <sstream>
#include <iostream>
#include <unistd.h>

//global
time_t rawTime;
struct tm *timeInfo;

class GLClock{
private:
	GLfloat clockBody_X = 0.0;
	GLfloat clockBody_Y = 0.0;
	GLfloat clockBody_R = 1.0;
	GLfloat clockBody_C = 0;

	std::string clockNumbers[12] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"};
	GLfloat clockNumberAxis[2] = {0.0, 0.0};

	GLfloat clockHourHandbase[2] = {0.0, 0.0};
	GLfloat clockHourPoint[2] = {0.5, 0.5};

	GLfloat clockMinHandbase[2] = {0.0, 0.0};
	GLfloat clockMinPoint[2] = {-0.5, -0.5};

	GLfloat clockSecHandbase[2] = {0.0, 0.0};
	GLfloat clockSecPoint[2] = {-0.5, 0.5};

	GLfloat rateOfChange = .0001;
	
public:
	int second;
	int minute;
	int hour;
	int circleEdge = 0;

	void drawClockBody(void){
		glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 1.0);
			for(int i=0; i<360; i++){
				clockBody_X = sin(i*3.14/180) * clockBody_R;
				clockBody_Y = cos(i*3.14/180) * clockBody_R;
				glVertex3f(clockBody_X, clockBody_Y, 0);
			}
		glEnd();
	}

	/*****/
	void positionClockAxis(int i, GLfloat NumberAxis[2]){
		if(i==0){
			NumberAxis[0] = 0.45;
			NumberAxis[1] = 0.70;
		}
		if(i==1){
			NumberAxis[0] = 0.75;
			NumberAxis[1] = 0.37;
		}
		if(i==2){
			NumberAxis[0] = 0.90;
			NumberAxis[1] = 0.0;
		}
		if(i==3){
			NumberAxis[0] = 0.80;
			NumberAxis[1] = -0.37;
		}
		if(i==4){
			NumberAxis[0] = 0.55;
			NumberAxis[1] = -0.70;
		}
		if(i==5){
			NumberAxis[0] = 0.0;
			NumberAxis[1] = -0.99;
		}
		if(i==6){
			NumberAxis[0] = -0.55;
			NumberAxis[1] = -0.70;
		}
		if(i==7){
			NumberAxis[0] = -0.85;
			NumberAxis[1] = -0.37;
		}
		if(i==8){
			NumberAxis[0] = -0.99;
			NumberAxis[1] = 0.0;
		}
		if(i==9){
			NumberAxis[0] = -0.85;
			NumberAxis[1] = 0.37;
		}
		if(i==10){
			NumberAxis[0] = -0.55;
			NumberAxis[1] = 0.70;
		}
		if(i==11){
			NumberAxis[0] = -0.05;
			NumberAxis[1] = 0.85;
		}
	}
	void placeClockNumbers(void){
		glColor3f(0.0, 0.0, 0.0);
		for(int i=0; i<12;  i++){
			positionClockAxis(i, clockNumberAxis);
			glRasterPos3f(clockNumberAxis[0], clockNumberAxis[1], 0.0);
			glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char *)clockNumbers[i].c_str());
		}
	}
	/*^^**/

	void placeHourHand(void){
		glBegin(GL_LINE_STRIP);
		glColor3f(0.0, 0.0, 1.0);
			glVertex3f(clockHourHandbase[0], clockHourHandbase[1], 0);
			glVertex3f(clockHourPoint[0], clockHourPoint[1], 0);
		glEnd();
			time(&rawTime);
			timeInfo = localtime(&rawTime);
			hour = timeInfo->tm_hour;
			if(hour > 12){hour = 0;}
			clockHourPoint[0] = sin((hour * 30) * 3.14/180) * clockBody_R;
			clockHourPoint[1] = cos((hour * 30) * 3.14/180) * clockBody_R;
		glutPostRedisplay();
	}

	void placeMinHand(void){
		glBegin(GL_LINE_STRIP);
		glColor3f(0.0, 1.0, 0.0);
			glVertex3f(clockMinHandbase[0], clockMinHandbase[1], 0);
			glVertex3f(clockMinPoint[0], clockMinPoint[1], 0);
		glEnd();
			time(&rawTime);
			timeInfo = localtime(&rawTime);
			minute = timeInfo->tm_min;
			if(minute > 60){ minute = 0;}
			clockMinPoint[0] = sin((minute*6) * 3.14/180) * clockBody_R;
			clockMinPoint[1] = cos((minute*6) * 3.14/180) * clockBody_R;
		glutPostRedisplay();
	}

	void placeSecHand(void){
		glBegin(GL_LINE_STRIP);
		glColor3f(1.0, 0.0, 0.0);
			glVertex3f(clockSecHandbase[0], clockSecHandbase[1], 0);
			glVertex3f(clockSecPoint[0], clockSecPoint[1], 0);
		glEnd();
			time(&rawTime);
			timeInfo = localtime(&rawTime);
			second = timeInfo->tm_sec;
			if(second > 60){second = 0;}
			clockSecPoint[0] = sin((second*6) * 3.14/180) * clockBody_R;
			clockSecPoint[1] = cos((second*6) * 3.14/180) * clockBody_R;
		glutPostRedisplay();
	}
}glclock;


/*main functions*/
void render(void){
	glClear(GL_COLOR_BUFFER_BIT);
		glLineWidth(5);
		glclock.drawClockBody();
		glclock.placeClockNumbers();
		glLineWidth(7);
		glclock.placeHourHand();
		glLineWidth(5);
		glclock.placeMinHand();
		glLineWidth(3);
		glclock.placeSecHand();
	glFlush();
}

void startGL(int argv, char *argc[]){
	glutInit(&argv, argc);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Linux GL Clock");
	glutDisplayFunc(render);
	glutMainLoop();
}


int main(int argv, char *argc[]){

	time(&rawTime);
	timeInfo = localtime(&rawTime);

	glclock.second = timeInfo->tm_sec;
	startGL(argv, argc);
	return 0;
}