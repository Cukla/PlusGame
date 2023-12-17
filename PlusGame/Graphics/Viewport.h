#pragma once  
#include "../Rectangle.h" 

struct Viewport {
public:
	int x;
	int y;
	int width;
	int height;
	float minDepth;
	float maxDepth;

public:
	float getAspectRatio();
	Rectangle getBounds();
	Rectangle getTileSafeArea();
	Viewport(int x, int y, int width, int height);
	Viewport(int x, int y, int width, int height, float minDepth, float maxDepth);

};