#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

float x, y, z;
float cube = 10; //cube width
int width = 160;
int height = 44;
float zBuffer[160*44];
char buffer[160*44];
int background = ' ';
float distance = 60; //distance from cam
float speed = 0.6; //increment speed
float X, Y, Z;
float ooz;
int xp, yp;
float K1 = 40;
int idx;

float calX(int i, int j, int k){
	return j*sin(x)*sin(y)*cos(z)-k*cos(x)*sin(y)*cos(z)+j*cos(x)*sin(z)+k*sin(x)*sin(z)+i*cos(y)*cos(z);
}

float calY(int i, int j, int k){
	return j*cos(x)*cos(z)+k*sin(x)*cos(z)-j*sin(x)*sin(y)*sin(z)+k*cos(x)*sin(y)*sin(z)-i*cos(y)*sin(z);
}

float calZ(int i, int j, int k){
	return k*cos(x)*cos(y)-j*sin(x)*cos(y)+i*sin(y);
}

void calculateForSurface(float cubeX, float cubeY, float cubeZ, int ch) {
	X = calX(cubeX, cubeY, cubeZ);
	Y = calY(cubeX, cubeY, cubeZ);
	Z = calZ(cubeX, cubeY, cubeZ) + distance;

	ooz = 1/Z;
	xp = (int)(width/2 + K1 * ooz * X * 2);
	yp = (int)(height/2 + K1 * ooz * Y);

	idx = xp + yp * width;
	if(idx >= 0 && idx < width * height) {
		if(ooz > zBuffer[idx]){
			zBuffer[idx] = ooz;
			buffer[idx] = ch;
		}
	}
}

int main(){
	printf("\x1b[2J");
	while(1){
		float cubeX, cubeY;
		int k;
		memset(buffer, background, width*height);
		memset(zBuffer, 0, width * height * 4);
		for(cubeX = - cube; cubeX < cube; cubeX += speed){
			for(cubeY = - cube; cubeY < cube; cubeY += speed){
				calculateForSurface(cubeX, cubeY, -cube, '$');
			}
		}
		printf("\x1b[H");
		for(k = 0; k < width * height; k++){
			putchar(k % width ? buffer[k] : 10);
		}
		x += 0.005;
		y += 0.005;
		usleep(1000);
		
	}
	return 0;
}
