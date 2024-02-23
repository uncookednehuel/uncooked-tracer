#ifndef CAMERA_H
#define CAMERA_H

#include "uncooked-tracer.h"

#include "colour.h"
#include "hittable.h"

#include <iostream>

class camera {
public:
	double aspectRatio = 1.0;
	int imageWidth = 100;

	void render(const hittable& world) {
		initialize();

		std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

		for (int j = 0; j < imageHeight; ++j) {
			std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
			for (int i = 0; i < imageWidth; ++i) {
				auto pixelCenter = pixel00Loc + (i * pixelDeltaU) + (j * pixelDeltaV);
				auto rayDirection = pixelCenter - center;
				ray r(center, rayDirection);

				colour pixelColour = rayColour(r, world);
				writeColour(std::cout, pixelColour);
			}
		}

		std::clog << "\rDone.						\n";
	}
	
private:
	int imageHeight;
	point3 center;
	point3 pixel00Loc;
	vec3 pixelDeltaU;
	vec3 pixelDeltaV;

	void initialize() {
		imageHeight = static_cast<int>(imageWidth / aspectRatio);
		imageHeight = (imageHeight < 1) ? 1 : imageHeight;

		center = point3(0, 0, 0);

			
		auto focalLength = 1.0;
		auto viewportHeight = 2.0;
		auto viewportWidth = viewportHeight * (static_cast<double> (imageWidth) / imageHeight);

		auto viewportU = vec3(viewportWidth, 0, 0);
		auto viewportV = vec3(0, -viewportHeight, 0);

		auto pixelDeltaU = viewportU / imageWidth;
		auto pixelDeltaV = viewportV / imageHeight;

		auto viewportUpLeft = center - vec3(0, 0, focalLength) - (viewportU / 2) - (viewportV / 2);

		auto pixel00Loc = viewportUpLeft + 0.5 * (pixelDeltaU + pixelDeltaV);
	}

	colour rayColour(const ray& r, const hittable& world) const {
		hitRecord rec;

		if (world.hit(r, interval(0, infinity), rec)) {
			return 0.5 * (rec.normal + colour(1, 1, 1));
		}

		vec3 unitDirection = unitVector(r.direction());
		auto a = 0.5 * (unitDirection.y() + 1.0);
		return (1.0 - a) * colour(1.0, 1.0, 1.0) + a * colour(0.5, 0.7, 1.0);
	}
};

#endif