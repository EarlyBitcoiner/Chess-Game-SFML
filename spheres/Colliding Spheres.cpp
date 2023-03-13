
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Sphere {
public:
	double r, x, y, z;

	Sphere() = default;

	Sphere(int _r, int _x, int _y, int _z) :r(_r), x(_x), y(_y), z(_z) {};

};

// Formula to find distance between 2 points with x,y,z cordinates : D = sqrt( pow(x1 - x2) + pow(y1 - y2) + pow(z1 - z2) )

double distanceBetween(const Sphere& a, const Sphere& b) { // We will use the formula above to find the distance between the two centres of the spheres a and b.
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}

bool areColliding(const Sphere& a, const Sphere& b) {
	return distanceBetween(a, b) <= (a.r + b.r); // if the distance between them is smaller than their radiuses combined, they have collided. If it is equal, they are touching.
}

int contactless(vector<Sphere>& v) {
	int contactless = 0; // number of spheres not touching or colliding with others.
	bool contact;

	for (size_t i = 0;i < v.size();i++) {
		contact = 0;

		for (size_t j = 0;j < v.size();j++) {
			if (i == j)
				continue;

			if (areColliding(v[i], v[j])) {
				contact = 1;
				break;
			}

		}

		if (!contact)
			contactless++;
	}

	return contactless;
}

int main()
{

	vector<Sphere> spheres{
		Sphere(4,4,4,20),
		Sphere(4,4,4,-14),
		Sphere(4,4,4,-4),
		Sphere(4,4,4,8)
	}; 
  
	cout << contactless(spheres) << endl;

	return 0;
}
