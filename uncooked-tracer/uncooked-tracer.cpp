﻿#include "uncooked-tracer.h"

#include "colour.h"
#include "hittable.h"
#include "hittableList.h"
#include "sphere.h"

#include <iostream>

colour rayColour(const ray& r, const hittable& world) {
	hitRecord rec;
	if (world.hit(r, 0, infinity, rec)) {
		return 0.5 * (rec.normal + colour(1, 1, 1));
	}

	vec3 unitDirection = unitVector(r.direction());
	auto a = 0.5 * (unitDirection.y() + 1.0);
	return (1.0 - a) * colour(1.0, 1.0, 1.0) + a * colour(0.5, 0.7, 1.0);
}

int main()
{
	auto aspectRatio = 16.0 / 9.0;
	int imageWidth = 400;

	int imageHeight = static_cast<int>(imageWidth / aspectRatio);
	imageHeight = (imageHeight > 1) ? imageHeight : 1;

	// World
	hittableList world;

	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

	// Camera
	// actual ratio might be different
	auto viewportHeight = 2.0;
	auto viewportWidth = viewportHeight * (static_cast<double>(imageWidth) / imageHeight);
	auto focalLength = 1.0;
	auto cameraCenter = point3(0, 0, 0);

	auto viewportU = vec3(viewportWidth, 0, 0);
	auto viewportV = vec3(0, -viewportHeight, 0);

	auto pixelDeltaU = viewportU / imageWidth;
	auto pixelDeltaV = viewportV / imageHeight;

	auto viewportUpLeft = cameraCenter - vec3(0, 0, focalLength) - (viewportU / 2) - (viewportV / 2);

	auto pixel00Loc = viewportUpLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

	//Render
	std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	for (int j = 0; j < imageHeight; ++j) {
		std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
		for (int i = 0; i < imageWidth; ++i) {
			auto pixelCenter = pixel00Loc + (i * pixelDeltaU) + (j * pixelDeltaV);
			auto rayDirection = pixelCenter - cameraCenter;
			ray r(cameraCenter, rayDirection);

			colour pixelColour = rayColour(r, world);
			writeColour(std::cout, pixelColour);
		}
	}

	std::clog << "\rDone.						\n";
}