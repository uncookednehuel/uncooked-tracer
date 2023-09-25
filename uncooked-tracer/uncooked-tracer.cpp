#include <iostream>

int main()
{
	// For image
	int imageWidth = 256;
	int imageHeight = 256;

	//Render
	std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	for (int j = 0; j < imageHeight; j++) {
		std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
		for (int i = 0; i < imageHeight; i++) {
			auto r = double(i) / (imageHeight - 1);
			auto g = double(j) / (imageWidth - 1);
			auto b = 0;

			int ir = static_cast<int>(r * 255.99);
			int ig = static_cast<int>(g * 255.99);
			int ib = static_cast<int>(b * 255.99);

			std::cout << ir << ' ' << ig << ' ' << ib << "\n";
		}
	}

	std::clog << "\rDone.						\n";
}