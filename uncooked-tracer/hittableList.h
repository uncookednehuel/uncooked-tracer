#ifndef HITTABLE_LIST
#define HITTABLE_LIST

#include "hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hittableList : public hittable {
public:
	std::vector<shared_ptr<hittable>> objects;
	
	hittableList() {}
	hittableList(shared_ptr<hittable> object) { add(object); }

	void clear() { objects.clear(); }

	void add(shared_ptr<hittable> object) {
		objects.push_back(object);
	}

	bool hit(const ray& r, interval rayT, hitRecord& rec) const override {
		hitRecord tempRec;
		bool hitAnything = false;
		auto closestYet = rayT.max;

		for (const auto& object : objects) {
			if (object->hit(r, interval(rayT.min, closestYet), tempRec)) {
				hitAnything = true;
				closestYet = tempRec.t;
				rec = tempRec;
			}
		}

		return hitAnything;
	}
};

#endif