#include <math.h>
#include <stdio.h>
#include <string.h>

float x, y, z;
float cube = 10;
int width = 160;
int height = 44;
float zBuffer[160*44];
char buffer[160*44];
int background = ' ';

float calX(int i, int j, int k){
	return j*sin(x)*sin(y)*cos(z)-k*cos(x)*sin(y)*cos(z)+k*sin(x)*sin(z)+j*cos(x)*sin(z)+i*cos(y)*cos(z);
}

float calY(int i, int j, int k){
	return k*sin(x)*cos(z)+j*cos(x)*cos(z)-j*sin(x)*sin(y)*sin(z)+k*cos(x)*sin(y)*sin(z)-i*cos(y)*sin(z);
}

float calZ(int i, int j, int k){
	return k*cos(x)*cos(y)-j*sin(x)*cos(y)+i*sin(y);
}

int main(){
	printf("\x1b[2J");
	while(1){
		memset(buffer, background, width*height);
		memset(zBuffer, 0, width * height * 4);
	}
	return 0;
}
