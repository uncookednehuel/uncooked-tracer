﻿#include "uncooked-tracer.h"

#include "camera.h"
#include "hittableList.h"
#include "sphere.h"

#include <iostream>

int main()
{
	// World
	hittableList world;

	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

	camera cam;

	cam.aspectRatio = 16.0 / 9.0;
	cam.imageWidth = 400;

	cam.render(world);
}