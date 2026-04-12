#ifndef VEC3_H
#define VEC3_H

// The VEC3_H macro only serves one purpose:
// Being defined/undefined so that the ifndef statement
// Stops the code from calling this class more then once.

#include <cmath>
#include <iostream>

class vec3 {
	/*
	 * vec3: Instances represent 3-dimensional vectors
	 * vec3 my_vec = {double x, double y, double z}
	 * 	Note: In the context of physics simulations, using doubles is essential
	 * because we focus on precision rather then efficiency. If you're looking
	 * for increased efficiency at the cost of precision, use float instead.
	 * 
	 * Attributes:
	 * 	double v[3]: Array containing components
	 * 
	 * Methods:
	 * 	mag(vec3){return double}: Calculates magnitude of the vector
	 * 	unit(vec3){return vec3}: Calculates unit vector in the same direction
	 * 	dot(vec3, vec3){return double}: Calculates dot product of two vec3
	 * 	cross(vec3, vec3){return vec3}: Calculates cross product of two vec3
	 * 
	 * Operators:
	 * 	+: Vector sum
	 * 	-: Vector subtraction
	 * 	*: Scalar*vec3 or dot product (?)
	 *  /: vec3/scalar
	 * 	<<: How to output vec3
	*/
	public:
		double arr[3];

		// Constructor:
		vec3() : arr{0,0,0} {} // Default vector instance is a null vector
    	vec3(double v0, double v1, double v2) : arr{v0, v1, v2} {} // Assigns this array to v

		// Getters for each component:
		double x() const { return arr[0]; }
    	double y() const { return arr[1]; }
    	double z() const { return arr[2]; }
		/*
		 * The const in these getters is a confusing C++ detail
		 * that can only be placed in this position for class methods.
		 * In summary, it makes sure v can't be changed inside
		 * these methods. For more details, look it up!
		 */

		vec3 operator-() const { return vec3(-arr[0], -arr[1], -arr[2]); } // Behavior for -instance treatment
		// Indexing behavior:
    	double operator[](int i) const { return arr[i]; }
    	double& operator[](int i) { return arr[i]; } 

		void operator+=(const vec3& other) {
			/*
			We could have simply used vec3 other, but that would mean
			creating a copy of other everytime we used the operator,
			using more memory, which might be relevant when it comes
			to this project.

			PS: The reference uses a different implementation, but
			I can understand this one much better, so I will use
			this one!
			*/
			arr[0]+=other.arr[0];
			arr[1]+=other.arr[1];
			arr[2]+=other.arr[2];
		}

		void operator*=(const double& lambda){
			arr[0]*=lambda;
			arr[1]*=lambda;
			arr[2]*=lambda;
		}

		void operator/=(const double& k){
			*this *= (1/k); // Makes use of the previous operation
		}

		double length_squared() const {
			return arr[0]*arr[0]+arr[1]*arr[1]+arr[2]*arr[2];
		}

		double length() const {
			return std::sqrt(this->length_squared()); // this->length_squared() is equivalent to (*this).length_squared()
			// Notice that using simply length_squared() the compiler already assumes it's this->length_squared(), I'm
			// using this verbosity purely for more readability, since I'm not very proficient with C++.
		}
};

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using point3 = vec3;

// Vector Utility Functions

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.arr[0] << ' ' << v.arr[1] << ' ' << v.arr[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.arr[0] + v.arr[0], u.arr[1] + v.arr[1], u.arr[2] + v.arr[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.arr[0] - v.arr[0], u.arr[1] - v.arr[1], u.arr[2] - v.arr[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.arr[0] * v.arr[0], u.arr[1] * v.arr[1], u.arr[2] * v.arr[2]);
}

inline vec3 operator*(double t, const vec3& v) {
    return vec3(t*v.arr[0], t*v.arr[1], t*v.arr[2]);
}

inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

inline vec3 operator/(const vec3& v, double t) {
    return (1/t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
    return u.arr[0] * v.arr[0]
         + u.arr[1] * v.arr[1]
         + u.arr[2] * v.arr[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.arr[1] * v.arr[2] - u.arr[2] * v.arr[1],
                u.arr[2] * v.arr[0] - u.arr[0] * v.arr[2],
                u.arr[0] * v.arr[1] - u.arr[1] * v.arr[0]);
}

inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

#endif
