#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

float x, y, z, X, Y, Z;
float cube = 10; //cube width
int width = 160;
int height = 44;
float zBuffer[160*44];
char buffer[160*44];
int background = ' ';
float distance; //distance from cam
float speed; //increment speed
float ooz;
int xp, yp;
float K1 = 40;
int idx;

float calX(int i, int j, int k){
	return j*sin(x)*sin(y)*cos(z)-k*cos(x)*sin(y)*cos(z)+k*sin(x)*sin(z)+j*cos(x)*sin(z)+i*cos(y)*cos(z);
}

float calY(int i, int j, int k){
	return k*sin(x)*cos(z)+j*cos(x)*cos(z)-j*sin(x)*sin(y)*sin(z)+k*cos(x)*sin(y)*sin(z)-i*cos(y)*sin(z);
}

float calZ(int i, int j, int k){
	return k*cos(x)*cos(y)-j*sin(x)*cos(y)+i*sin(y);
}

void calculateForSurface(float cubeX, float cubeY, float cubeZ, int ch) {
	X = calX(cubeX. cubeY, cubeZ);
	Y = calY(cubeX. cubeY, cubeZ);
	Z = calZ(cubeX. cubeY, cubeZ) + distance;

	ooz = 1/z;
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
		memset(buffer, background, width*height);
		memset(zBuffer, 0, width * height * 4);
		for(float cubeX = - cube; cubeX < cube; cubeX += speed){
			for(float cubeY = - cube; cubeY < cube; cubeY += speed){
				calculateForSurface(cubeX, cubeY, -cube, '#');
			}
		}
	}
	return 0;
}
