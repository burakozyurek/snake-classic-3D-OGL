//#define STB_IMAGE_IMPLEMENTATION
//#define GLEW_STATIC
//#include <stb_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <glew.h>
#include <glfw3.h>
#include <irrKlang.h>
#include <ctime>
#include <cmath>
char direction = 'R';
char score[5];
const int gridsize = 30;
int snakelength = 0;
int prevtime = 0;
int currenttime = 0;
int cam_currenttime = 0;
int cam_prevtime = 0;
int timescale = 60;
int fasttimescale = 90;
int slowtimescale = 30;
float slowdown = 0.1;
float cx = 0, cy = 0, cz = 0;
float ratio;
float gridscale = 1.0 / gridsize;
bool pause = false;
bool isescpress = false;
bool iskeypress = true;
bool isaddpress = false;
bool _0[5][3] = { { 1,1,1 },
				 { 1,0,1 },
				 { 1,0,1 },
				 { 1,0,1 },
				 { 1,1,1 } };
bool _1[5][3] = { { 0,1,0 },
				 { 0,1,0 },
				 { 0,1,0 },
				 { 0,1,0 },
				 { 0,1,0 } };
bool _2[5][3] = { { 1,1,1 },
				 { 0,0,1 },
				 { 1,1,1 },
				 { 1,0,0 },
				 { 1,1,1 } };
bool _3[5][3] = { { 1,1,1 },
				 { 0,0,1 },
				 { 0,1,1 },
				 { 0,0,1 },
				 { 1,1,1 } };
bool _4[5][3] = { { 1,0,1 },
				 { 1,0,1 },
				 { 1,1,1 },
				 { 0,0,1 },
				 { 0,0,1 } };
bool _5[5][3] = { { 1,1,1 },
				 { 1,0,0 },
				 { 1,1,1 },
				 { 0,0,1 },
				 { 1,1,1 } };
bool _6[5][3] = { { 1,1,1 },
				 { 1,0,0 },
				 { 1,1,1 },
				 { 1,0,1 },
				 { 1,1,1 } };
bool _7[5][3] = { { 1,1,1 },
				 { 0,0,1 },
				 { 0,0,1 },
				 { 0,0,1 },
				 { 0,0,1 } };
bool _8[5][3] = { { 1,1,1 },
				 { 1,0,1 },
				 { 1,1,1 },
				 { 1,0,1 },
				 { 1,1,1 } };
bool _9[5][3] = { { 1,1,1 },
				 { 1,0,1 },
				 { 1,1,1 },
				 { 0,0,1 },
				 { 1,1,1 } };
using namespace irrklang;
ISoundEngine* SoundEngine = createIrrKlangDevice();
class unitobject {
public:
	bool isAlive = false;
	float LocX = 0.0, LocY = 0.0, LocZ = 0.0;
	float unitW = (1.0 / gridsize) - (gridscale / 10.0), unitH = (1.0 / gridsize) - (gridscale / 10.0), unitZ = (1.0 / gridsize) - (gridscale / 10.0);
	float R = 1.0, G = 0.5, B = 0.7, A = 0.5;
	void spawn() {
		LocX = ((rand() % (gridsize * 2) - gridsize) / (float)gridsize);
		LocY = ((rand() % (gridsize * 2) - gridsize) / (float)gridsize);
		LocY += 1.0 / gridsize;
		R = 0.8;
		G = 0.1;
		B = 0.1;
	}
	void draw() {
		glColor4f(R, G, B, A);
		glNormal3f(0.0, 0.0, -1.0);
		glBegin(GL_QUADS);//BACK
		glVertex3f(LocX, LocY, LocZ);
		glVertex3f(LocX + unitW, LocY, LocZ);
		glVertex3f(LocX + unitW, LocY - unitH, LocZ);
		glVertex3f(LocX, LocY - unitH, LocZ);
		glEnd();
		glNormal3f(0.0, 0.0, 1.0);
		glBegin(GL_QUADS);//FRONT
		glVertex3f(LocX, LocY, LocZ + unitZ);
		glVertex3f(LocX + unitW, LocY, LocZ + unitZ);
		glVertex3f(LocX + unitW, LocY - unitH, LocZ + unitZ);
		glVertex3f(LocX, LocY - unitH, +LocZ + unitZ);
		glEnd();
		glNormal3f(0.0, 1.0, 0.0);
		glBegin(GL_QUADS);//TOP
		glVertex3f(LocX, LocY, LocZ);
		glVertex3f(LocX + unitW, LocY, LocZ);
		glVertex3f(LocX + unitW, LocY, LocZ + unitZ);
		glVertex3f(LocX, LocY, LocZ + unitZ);
		glEnd();
		glNormal3f(0.0, -1.0, 0.0);
		glBegin(GL_QUADS);//BOTTOM
		glVertex3f(LocX, LocY - unitH, LocZ);
		glVertex3f(LocX + unitW, LocY - unitH, LocZ);
		glVertex3f(LocX + unitW, LocY - unitH, LocZ + unitZ);
		glVertex3f(LocX, LocY - unitH, LocZ + unitZ);
		glEnd();
		glNormal3f(-1.0, 0.0, 0.0);
		glBegin(GL_QUADS);//LEFT
		glVertex3f(LocX + unitW, LocY, LocZ);
		glVertex3f(LocX + unitW, LocY, LocZ + unitZ);
		glVertex3f(LocX + unitW, LocY - unitH, LocZ + unitZ);
		glVertex3f(LocX + unitW, LocY - unitH, LocZ);
		glEnd();
		glNormal3f(1.0, 0.0, 0.0);
		glBegin(GL_QUADS);//RIGTH
		glVertex3f(LocX, LocY, LocZ + unitZ);
		glVertex3f(LocX, LocY, LocZ);
		glVertex3f(LocX, LocY - unitH, LocZ);
		glVertex3f(LocX, LocY - unitH, LocZ + unitZ);
		glEnd();
	}
}unit;
unitobject snake[gridsize * 2 * gridsize * 2];
unitobject bait;
unitobject powerup;
unitobject stones[gridsize * gridsize];
unitobject digit[5][3];
void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}
void setbuffersizecallbackfunc(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	ratio = (float)width / (float)height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50, ratio, 0.001, 20000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
float collisiondet(float aX, float aY, float bX, float bY) {
	float dx = aX - bX;
	float dy = aY - bY;
	float distance = sqrt(dx * dx + dy * dy);
	return distance;
}
void shiftarray() {
	for (int i = snakelength; i >= 0; i--) {
		snake[i + 1].LocX = snake[i].LocX;
		snake[i + 1].LocY = snake[i].LocY;
	}
}
void reset() {
	for (int i = 0; i < gridsize * gridsize; i++) {
		stones[i].LocX = 0;
		stones[i].LocY = 0;
		if (rand() % 10 == 0)	stones[i].spawn();
	}
	snakelength = 3;
	slowdown = 0.3;
	snake[0].LocX = 3 * gridscale;
	snake[0].LocY = 0;
	snake[1].LocX = 2 * gridscale;
	snake[1].LocY = 0;
	snake[2].LocX = 1 * gridscale;
	snake[2].LocY = 0;
	snake[3].LocX = 0;
	snake[3].LocY = 0;
	cx = gridscale * 2;
	cy = 0;
	cz = 0;
	direction = 'R';
}
void selfcollision() {
	for (int i = 1; i <= snakelength; i++)
		if (collisiondet(snake[0].LocX, snake[0].LocY, snake[i].LocX, snake[i].LocY) * 1.1 <= 1.0 / gridsize) {
			printf("self collusion");
			direction = 'R';
			reset();
			SoundEngine->play2D("gameover.mp3", GL_FALSE);
		}
}
void info() {
	printf("\n%f %f", snake[0].LocX, snake[0].LocY);
}
int main() {
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())printf("GLFW Initialization failed!");
	GLFWwindow* window = glfwCreateWindow(900, 900, "", NULL, NULL);
	glfwSetWindowSizeCallback(window, setbuffersizecallbackfunc);
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSwapInterval(1);
	glfwSetWindowSize(window, 1600, 900);
	glfwMaximizeWindow(window);
	if (!window)printf("An error occured during GLFW Window creating!");

	glfwWindowHint(GLFW_SAMPLES, 2);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	srand(time(NULL));
	prevtime = glfwGetTime();
	cam_prevtime = glfwGetTime();
	bait.spawn();
	//powerup.spawn();
	reset();
	SoundEngine->play2D("theme.mp3", GL_TRUE);

	while (!glfwWindowShouldClose(window)) {

		if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS) {
			isaddpress = true;
		}
		if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_RELEASE && isaddpress == true)
		{
			snakelength += 1;
			isaddpress = false;
		}
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) isescpress = true;
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
			if (pause == false && isescpress == true) {
				pause = true;
				isescpress = false;
			}
			else if (pause == true && isescpress == true) {
				pause = false;
				isescpress = false;
			}
		}
		if (pause == false) {
			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_DOWN) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_RIGHT) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT) != GLFW_PRESS && direction != 'D' && iskeypress == false) {
				direction = 'U';
				iskeypress = true;
			}
			if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_UP) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_RIGHT) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT) != GLFW_PRESS && direction != 'U' && iskeypress == false) {
				direction = 'D';
				iskeypress = true;
			}
			if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_DOWN) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_UP) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT) != GLFW_PRESS && direction != 'L' && iskeypress == false) {
				direction = 'R';
				iskeypress = true;
			}
			if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_DOWN) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_UP) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_RIGHT) != GLFW_PRESS && direction != 'R' && iskeypress == false) {
				direction = 'L';
				iskeypress = true;
			}

			if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && slowdown > 0) {
				currenttime = glfwGetTime() * 5;
				cam_currenttime = glfwGetTime() * 30;
				slowdown -= 0.002;
			}
			else {
				currenttime = glfwGetTime() * 10;
				cam_currenttime = glfwGetTime() * 60;
			}
			if (prevtime != currenttime) {
				if (direction == 'U') {
					selfcollision();
					shiftarray();
					snake[0].LocY += gridscale;
					iskeypress = false;
				}
				if (direction == 'D') {
					selfcollision();
					shiftarray();
					snake[0].LocY -= gridscale;
					iskeypress = false;
				}
				if (direction == 'R') {
					selfcollision();
					shiftarray();
					snake[0].LocX += gridscale;
					iskeypress = false;
				}
				if (direction == 'L') {
					selfcollision();
					shiftarray();
					snake[0].LocX -= gridscale;
					iskeypress = false;
				}
				if (collisiondet(snake[0].LocX, snake[0].LocY, 1, snake[0].LocY) * 1.1 <= gridscale && direction == 'R') {//Hitwall
					//snake[0].LocX = -1.0;
					//cx = -1.0;
					reset();
					SoundEngine->play2D("gameover.mp3", GL_FALSE);
				}
				if (collisiondet(snake[0].LocX, snake[0].LocY, -1 - gridscale, snake[0].LocY) * 1.1 <= gridscale && direction == 'L') {
					//snake[0].LocX = 1.0 - gridscale;
					//cx = 1.0 - gridscale;
					reset();
					SoundEngine->play2D("gameover.mp3", GL_FALSE);
				}
				if (collisiondet(snake[0].LocX, snake[0].LocY, snake[0].LocX, 1 + gridscale) * 1.1 <= gridscale && direction == 'U') {
					//snake[0].LocY = -1.0 + gridscale;
					//cy = -1.0 + gridscale;
					reset();
					SoundEngine->play2D("gameover.mp3", GL_FALSE);
				}
				if (collisiondet(snake[0].LocX, snake[0].LocY, snake[0].LocX, -1) * 1.1 <= gridscale && direction == 'D') {
					//snake[0].LocY = 1.0;
					//cy = 1.0;
					reset();
					SoundEngine->play2D("gameover.mp3", GL_FALSE);
				}
				prevtime = currenttime;
				if (collisiondet(snake[0].LocX, snake[0].LocY, bait.LocX, bait.LocY) * 1.1 <= gridscale) {//Snake and bait collision detection
					bait.spawn();
					SoundEngine->play2D("eat.mp3", GL_FALSE);
					for (int i = 1; i <= snakelength; i++) {//Bait respawn collision check on snake
						if (collisiondet(snake[i].LocX, snake[i].LocY, bait.LocX, bait.LocY) * 1.1 <= gridscale)bait.spawn();
					}
					snakelength += 1;
					slowdown += 0.05;
				}
				//if (collisiondet(snake[0].LocX, snake[0].LocY, powerup.LocX, powerup.LocY)*1.1 <= gridscale) {//Snake and powerup collision detection
				//	powerup.spawn();
				//	SoundEngine->play2D("powerup.mp3", GL_FALSE);
				//	for (int i = 1; i <= snakelength; i++) {//powerup respawn collision check on snake
				//		if (collisiondet(snake[i].LocX, snake[i].LocY, powerup.LocX, powerup.LocY)*1.1 <= gridscale)powerup.spawn();
				//	}
				//	slowdown += 0.05;
				//}
				for (int i = 0; i < gridsize * gridsize; i++)//Bait respawn collision check with stones
					if (collisiondet(bait.LocX, bait.LocY, stones[i].LocX, stones[i].LocY) * 1.1 <= gridscale)bait.spawn();
				//for (int i = 0; i < gridsize*gridsize; i++)//Powerup respawn collision check with stones
				//	if (collisiondet(powerup.LocX, powerup.LocY, stones[i].LocX, stones[i].LocY)*1.1 <= gridscale)bait.spawn();
				for (int i = 0; i < gridsize * gridsize; i++)//Snake and stones collision check
					if (collisiondet(snake[0].LocX, snake[0].LocY, stones[i].LocX, stones[i].LocY) * 1.1 <= gridscale) {
						SoundEngine->play2D("gameover.mp3", GL_FALSE);
						reset();
					}
			}
			if (cam_prevtime != cam_currenttime) {
				if (direction == 'U') cy += gridscale / 6;
				if (direction == 'D') cy -= gridscale / 6;
				if (direction == 'R') cx += gridscale / 6;
				if (direction == 'L') cx -= gridscale / 6;
				cam_prevtime = cam_currenttime;
			}
		}
		glLoadIdentity();
		glClearColor(0.05, 0.05, 0.05, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		gluLookAt(cx, cy - 0.5, 1.0, cx, cy - 0.0, 0.0, 0.0, 1.0, 0.0);
		//gluLookAt(0, -0.5, 2.2, 0, -0.1, 0.0, 0.0, 1.0, 0.0);
		for (int i = 0; i <= snakelength; i++) {
			snake[i].R = 0.9;
			snake[i].G = 0.9;
			snake[i].B = 0.9;
			snake[i].draw();
		}
		for (int i = 0; i < gridsize * gridsize; i++) {
			stones[i].R = 0.1;
			stones[i].G = 0.15;
			stones[i].B = 0.1;
			stones[i].draw();
		}
		for (int i = 0 - gridsize; i < gridsize; i++) {
			for (int j = 0 - gridsize; j < gridsize; j++) {
				if (i % 2 == 0) {
					if (j % 2 == 0)glColor3f(0.15, 0.25, 0.15);
					else glColor3f(0.2, 0.3, 0.2);
				}
				else {
					if (j % 2 == 0) glColor3f(0.2, 0.3, 0.2);
					else glColor3f(0.15, 0.25, 0.15);
				}
				glNormal3f(0.1, 0.1, 1.0);
				glBegin(GL_QUADS);//Background
				glVertex3f(gridscale * i, gridscale * j, 0.0);
				glVertex3f(gridscale * i + gridscale, gridscale * j, 0.0);
				glVertex3f(gridscale * i + gridscale, gridscale * j + gridscale, 0.0);
				glVertex3f(gridscale * i, gridscale * j + gridscale, 0.0);
				glEnd();
			}
		}
		glLineWidth(1);
		//glColor3f(0.1, 0.1, 0.5);
		//for (int i = 0; i < slowdown; i++){
		//	glBegin(GL_LINES);
		//	glVertex3f(cx - 0.6 + (i*0.001)-0.01, cy + 0.5-0.01, 0.1);
		//	glVertex3f(cx - 0.6 + (i*0.001)-0.01, cy + 0.45-0.01, 0.1);
		//	glEnd();
		//}

		score[0] = snakelength % 10;
		score[1] = ((snakelength % 100) - score[0]) / 10;
		score[2] = ((snakelength % 1000) - score[1]) / 100;
		score[3] = ((snakelength % 10000) - score[2]) / 1000;
		score[4] = ((snakelength % 100000) - score[3]) / 10000;
		for (int s = 0; s < 5; s++) {
			if (score[s] == 0) {
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 3; j++) {
						if (_0[i][j] == 1) {
							digit[i][j].R = 0.2;
							digit[i][j].G = 0.2;
							digit[i][j].B = slowdown;
							digit[i][j].LocX = (cx + (j / 50.0) - (s * 4 * gridscale)) + 6 * gridscale;
							digit[i][j].LocY = (cy - (i / 50.0) + 0.65);
							digit[i][j].LocZ = gridscale;

							digit[i][j].draw();
						}
					}
				}
			}
			if (score[s] == 1) {
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 3; j++) {
						if (_1[i][j] == 1) {
							digit[i][j].R = 0.2;
							digit[i][j].G = 0.2;
							digit[i][j].B = slowdown;
							digit[i][j].LocX = (cx + (j / 50.0) - (s * 4 * gridscale)) + 6 * gridscale;
							digit[i][j].LocY = (cy - (i / 50.0) + 0.65);
							digit[i][j].LocZ = gridscale;
							digit[i][j].draw();
						}
					}
				}
			}
			if (score[s] == 2) {
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 3; j++) {
						if (_2[i][j] == 1) {
							digit[i][j].R = 0.2;
							digit[i][j].G = 0.2;
							digit[i][j].B = slowdown;
							digit[i][j].LocX = (cx + (j / 50.0) - (s * 4 * gridscale)) + 6 * gridscale;
							digit[i][j].LocY = (cy - (i / 50.0) + 0.65);
							digit[i][j].LocZ = gridscale;
							digit[i][j].draw();
						}
					}
				}
			}
			if (score[s] == 3) {
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 3; j++) {
						if (_3[i][j] == 1) {
							digit[i][j].R = 0.2;
							digit[i][j].G = 0.2;
							digit[i][j].B = slowdown;
							digit[i][j].LocX = (cx + (j / 50.0) - (s * 4 * gridscale)) + 6 * gridscale;
							digit[i][j].LocY = (cy - (i / 50.0) + 0.65);
							digit[i][j].LocZ = gridscale;
							digit[i][j].draw();
						}
					}
				}
			}
			if (score[s] == 4) {
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 3; j++) {
						if (_4[i][j] == 1) {
							digit[i][j].R = 0.2;
							digit[i][j].G = 0.2;
							digit[i][j].B = slowdown;
							digit[i][j].LocX = (cx + (j / 50.0) - (s * 4 * gridscale)) + 6 * gridscale;
							digit[i][j].LocY = (cy - (i / 50.0) + 0.65);
							digit[i][j].LocZ = gridscale;
							digit[i][j].draw();

						}
					}
				}
			}
			if (score[s] == 5) {
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 3; j++) {
						if (_5[i][j] == 1) {
							digit[i][j].R = 0.2;
							digit[i][j].G = 0.2;
							digit[i][j].B = slowdown;
							digit[i][j].LocX = (cx + (j / 50.0) - (s * 4 * gridscale)) + 6 * gridscale;
							digit[i][j].LocY = (cy - (i / 50.0) + 0.65);
							digit[i][j].LocZ = gridscale;
							digit[i][j].draw();
						}
					}
				}
			}
			if (score[s] == 6) {
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 3; j++) {
						if (_6[i][j] == 1) {
							digit[i][j].R = 0.2;
							digit[i][j].G = 0.2;
							digit[i][j].B = slowdown;
							digit[i][j].LocX = (cx + (j / 50.0) - (s * 4 * gridscale)) + 6 * gridscale;
							digit[i][j].LocY = (cy - (i / 50.0) + 0.65);
							digit[i][j].LocZ = gridscale;
							digit[i][j].draw();
						}
					}
				}
			}
			if (score[s] == 7) {
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 3; j++) {
						if (_7[i][j] == 1) {
							digit[i][j].R = 0.2;
							digit[i][j].G = 0.2;
							digit[i][j].B = slowdown;
							digit[i][j].LocX = (cx + (j / 50.0) - (s * 4 * gridscale)) + 6 * gridscale;
							digit[i][j].LocY = (cy - (i / 50.0) + 0.65);
							digit[i][j].LocZ = gridscale;
							digit[i][j].draw();
						}
					}
				}
			}
			if (score[s] == 8) {
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 3; j++) {
						if (_8[i][j] == 1) {
							digit[i][j].R = 0.2;
							digit[i][j].G = 0.2;
							digit[i][j].B = slowdown;
							digit[i][j].LocX = (cx + (j / 50.0) - (s * 4 * gridscale)) + 6 * gridscale;
							digit[i][j].LocY = (cy - (i / 50.0) + 0.65);
							digit[i][j].LocZ = gridscale;
							digit[i][j].draw();
						}
					}
				}
			}
			if (score[s] == 9) {
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 3; j++) {
						if (_9[i][j] == 1) {
							digit[i][j].R = 0.2;
							digit[i][j].G = 0.2;
							digit[i][j].B = slowdown;
							digit[i][j].LocX = (cx + (j / 50.0) - (s * 4 * gridscale)) + 6 * gridscale;
							digit[i][j].LocY = (cy - (i / 50.0) + 0.65);
							digit[i][j].LocZ = gridscale;
							digit[i][j].draw();
						}
					}
				}
			}
		}
		bait.draw();
		//powerup.R = 0.1;
		//powerup.G = 0.1;
		//powerup.B = 0.8;
		//powerup.draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}