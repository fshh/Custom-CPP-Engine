// Support Code written by Michael D. Shah
// Updated by Seth Cooper
// Last Updated: Spring 2020
// Please do not redistribute without asking permission.

#ifndef TINYMATH_HPP
#define TINYMATH_HPP

#include <cmath>
#include <stdexcept>
#include <limits>
#include <algorithm>

namespace TinyMath {

	template <class T>
	inline T clamp(T n, T lower, T upper) {
		return std::max(lower, std::min(n, upper));
	}

	inline double radiansToDegrees(double radians) {
		double pi = 3.14159;
		return radians * (180 / pi);
	}

	template <class T>
	inline T lerp(T a, T b, T t) {
		return (a * (1.0 - t)) + (b * t);
	}

	// Forward references of each of the structs
	template <class T>
	struct Vector2D;
	template <class T>
	struct Vector3D;
	template <class T>
	struct Matrix3D;

	/**
	 * A struct representing a 2D vector of numeric types.
	 */
	template <class T>
	struct Vector2D{
		T x; /**< The x-component of a 2D vector. */
		T y; /**< The y-component of a 2D vector. */

		/**
		 * Construct a 2D vector with default values.
		 */
		Vector2D() = default;

		/**
		 * Construct a 2D vector with the given x and y values.
		 * @param a The x value of the vector.
		 * @param b The y value of the vector.
		 */
		Vector2D(T a, T b): x{a}, y{b} { }

		/**
		 * Access a given index in the vector.
		 * @param i The index within the vector.
		 * @return the value at the given index.
		 */
		T& operator[](int i){
			return ((&x)[i]);
		}

		/**
		 * Access a given index in the vector.
		 * @param i The index within the vector.
		 * @return the value at the given index.
		 */
		const T& operator[](int i) const{
			return ((&x)[i]);
		}

		/**
		 * Multiply this vector by a uniform scalar.
		 * @param s The uniform scalar.
		 * @return a reference to this modified vector.
		 */
		Vector2D& operator *=(T s){
			x *= s;
			y *= s;
			return (*this);
		}

		/**
		 * Divide this vector by a uniform scalar.
		 * @param s The uniform scalar.
		 * @return a reference to this modified vector.
		 */
		Vector2D& operator /=(T s){
			if (s == 0) {
				throw std::domain_error("Cannot divide by zero.");
			}
			x /= s;
			y /= s;
			return (*this);
		}

		/**
		 * Add a vector to this vector component-wise.
		 * @param v The vector to add by.
		 * @return a reference to this modified vector.
		 */
		Vector2D& operator +=(const Vector2D<T>& v){
			x += v.x;
			y += v.y;
			return (*this);
		}

		/**
		 * Subtract a vector from this vector component-wise.
		 * @param v The vector to subtract by.
		 * @return a reference to this modified vector.
		 */
		Vector2D& operator -=(const Vector2D<T>& v){
			x -= v.x;
			y -= v.y;
			return (*this);
		}

	};

	/**
	 * Compute the dot product of two vectors.
	 * @param a The first vector.
	 * @param b The second vector.
	 * @return the result of the dot product.
	 */
	template <class T>
	inline T Dot(const Vector2D<T>& a, const Vector2D<T>& b){
		return a.x * b.x + a.y * b.y;
	}

	/**
	 * Multiply a vector by a uniform scalar.
	 * @param v The vector.
	 * @param s The uniform scalar.
	 * @return a vector representing the result of the multiplication.
	 */
	template <class T>
	inline Vector2D<T> operator *(const Vector2D<T>& v, T s){
		return Vector2D<T>(v.x * s, v.y * s);
	}

	/**
	 * Multiply a vector by a uniform scalar.
	 * @param s The uniform scalar.
	 * @param v The vector.
	 * @return a vector representing the result of the multiplication.
	 */
	template <class T>
	inline Vector2D<T> operator *(T s, const Vector2D<T>& v){
		return Vector2D<T>(v.x * s, v.y * s);
	}

	/**
	 * Divide a vector by a uniform scalar.
	 * @param s The uniform scalar.
	 * @return a vector representing the result of the division.
	 */
	template <class T>
	inline Vector2D<T> operator /(const Vector2D<T>& v, T s){
		if (s == 0) {
			throw std::domain_error("Cannot divide by zero.");
		}
		return Vector2D<T>(v.x / s, v.y / s);
	}

	/**
	 * Negate a vector.
	 * @param v The vector.
	 * @return a vector representing the result of the negation.
	 */
	template <class T>
	inline Vector2D<T> operator -(const Vector2D<T>& v){
		return Vector2D<T>(-v.x, -v.y);
	}

	/**
	 * Add two vectors together.
	 * @param a The first vector.
	 * @param b The second vector.
	 * @return a vector representing the result of the addition.
	 */
	template <class T>
	inline Vector2D<T> operator +(const Vector2D<T>& a, const Vector2D<T>& b){
		return Vector2D<T>(a.x + b.x, a.y + b.y);
	}

	/**
	 * Subtract one vector from another.
	 * @param a The first vector.
	 * @param b The second vector.
	 * @return a vector representing the result of the subtraction.
	 */
	template <class T>
	inline Vector2D<T> operator -(const Vector2D<T>& a, const Vector2D<T>& b){
		return Vector2D<T>(a.x - b.x, a.y - b.y);
	}

	/**
	 * Compute the magnitude of a vector.
	 * @param v The vector.
	 * @return the magnitude of the vector.
	 */
	template <class T>
	inline T Magnitude(const Vector2D<T>& v){
		return (T)std::sqrt(std::pow(v.x, 2) + std::pow(v.y, 2));
	}

	/**
	 * Project one vector onto another.
	 * @param a The vector to project.
	 * @param b The vector to project onto.
	 * @return the result of the projection.
	 */
	template <class T>
	inline Vector2D<T> Project(const Vector2D<T>& a, const Vector2D<T>& b){
		T denom = Dot(b, b);
		if (denom == 0) {
			throw std::domain_error("Cannot project onto a zero vector.");
		}
		T coefficient = Dot(a, b) / denom;
		return Vector2D<T>(b.x * coefficient, b.y * coefficient);
	}

	/**
	 * Get a normalized version of a vector.
	 * @param v The vector.
	 * @return a normalized version of the vector.
	 */
	template <class T>
	inline Vector2D<T> Normalize(const Vector2D<T>& v){
		T mag = Magnitude(v);
		if (mag == 0) {
			return v;
		}
		return Vector2D<T>(v.x / mag, v.y / mag);
	}

	/**
	 * Reflect an incoming vector across a normal vector.
	 * @param normal The normal vector.
	 * @param incoming The incoming vector.
	 * @return the result of the reflection.
	 */
	template <class T>
	inline Vector2D<T> Reflect(Vector2D<T> normal, Vector2D<T> incoming) {
		Vector2D<T> reflected = incoming + (-2 * Dot(normal, incoming) * normal);
		return reflected;
	}

	/**
	 * Compute the point of intersection of two lines.
	 * @param p The first point of the first line.
	 * @param r The second point of the first line.
	 * @param q The first point of the second line.
	 * @param s The second point of the second line.
	 * @return the point of intersection of the two lines. If the lines do not intersect, return the maximum possible point.
	 */
	template <class T>
	Vector2D<T> Intersect(Vector2D<T> p, Vector2D<T> r, Vector2D<T> q, Vector2D<T> s){
		r.x -= p.x;
		r.y -= p.y;
		s.x -= q.x;
		s.y -= q.y;
		T rxs = r.x*s.y - r.y*s.x;
		if (rxs == 0.0) {
			// A value that is _almost_ impossible to be at
			return Vector2D<T>{std::numeric_limits<T>::max(), std::numeric_limits<T>::max()};
		}
		T t = ((q.x - p.x)*s.y - (q.y - p.y)*s.x) / rxs;
		T u = ((q.x - p.x)*r.y - (q.y - p.y)*r.x) / rxs;
		if (t <= 0.0 || u <= 0.0 || t >= 1.0 || u >= 1.0) {
			// A value that is _almost_ impossible to be at
			return Vector2D<T>{std::numeric_limits<T>::max(), std::numeric_limits<T>::max()};
		}
		else {
			return Vector2D<T>{p.x + t * r.x, p.y + t * r.y};
		}
	}

	template <class T>
	double AngleBetweenRadians(Vector2D<T> u, Vector2D<T> v) {
		T dot = Dot(u, v);
		T det = u.x * v.y - u.y * v.x;
		return atan2(det, dot);
	}

	template <class T>
	double AngleBetweenDegrees(Vector2D<T> u, Vector2D<T> v) {
		return radiansToDegrees(AngleBetweenRadians(u, v));
	}




	/**
	 * A struct representing a 3D vector of numeric types.
	 */
	template <class T>
	struct Vector3D{
		T x; /**< The x-component of a 3D vector. */
		T y; /**< The y-component of a 3D vector. */
		T z; /**< The z-component of a 3D vector. */

		/**
		 * Construct a 2D vector with default values.
		 */
		Vector3D() = default;

		/**
		 * Construct a 3D vector with the given x, y, and z values.
		 * @param a The x value of the vector.
		 * @param b The y value of the vector.
		 * @param c The z value of the vector.
		 */
		Vector3D(T a, T b, T c): x{a}, y{b}, z{c} { }

		/**
		 * Access a given index in the vector.
		 * @param i The index within the vector.
		 * @return the value at the given index.
		 */
		T& operator[](int i){
			return ((&x)[i]);
		}

		/**
		 * Access a given index in the vector.
		 * @param i The index within the vector.
		 * @return the value at the given index.
		 */
		const T& operator[](int i) const{
			return ((&x)[i]);
		}

		/**
		 * Multiply this vector by a uniform scalar.
		 * @param s The uniform scalar.
		 * @return a reference to this modified vector.
		 */
		Vector3D& operator *=(T s){
			x *= s;
			y *= s;
			z *= s;
			return (*this);
		}

		/**
		 * Divide this vector by a uniform scalar.
		 * @param s The uniform scalar.
		 * @return a reference to this modified vector.
		 */
		Vector3D& operator /=(T s){
			if (s == 0) {
				throw std::domain_error("Cannot divide by zero.");
			}
			x /= s;
			y /= s;
			z /= s;

			return (*this);
		}

		/**
		 * Add a vector to this vector component-wise.
		 * @param v The vector to add by.
		 * @return a reference to this modified vector.
		 */
		Vector3D& operator +=(const Vector3D<T>& v){
			x += v.x;
			y += v.y;
			z += v.z;

			return (*this);
		}

		/**
		 * Subtract a vector from this vector component-wise.
		 * @param v The vector to subtract by.
		 * @return a reference to this modified vector.
		 */
		Vector3D& operator -=(const Vector3D<T>& v){
			x -= v.x;
			y -= v.y;
			z -= v.z;

			return (*this);
		}
	};

	/**
	 * Compute the dot product of two vectors.
	 * @param a The first vector.
	 * @param b The second vector.
	 * @return the result of the dot product.
	 */
	template <class T>
	inline T Dot(const Vector3D<T>& a, const Vector3D<T>& b){
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	/**
	 * Multiply a vector by a uniform scalar.
	 * @param v The vector.
	 * @param s The uniform scalar.
	 * @return a vector representing the result of the multiplication.
	 */
	template <class T>
	inline Vector3D<T> operator *(const Vector3D<T>& v, T s){
		return Vector3D<T>(v.x * s, v.y * s, v.z * s);
	}

	/**
	 * Multiply a vector by a uniform scalar.
	 * @param s The uniform scalar.
	 * @param v The vector.
	 * @return a vector representing the result of the multiplication.
	 */
	template <class T>
	inline Vector3D<T> operator *(T s, const Vector3D<T>& v){
		return Vector3D<T>(v.x * s, v.y * s, v.z * s);
	}

	/**
	 * Divide a vector by a uniform scalar.
	 * @param s The uniform scalar.
	 * @return a vector representing the result of the division.
	 */
	template <class T>
	inline Vector3D<T> operator /(const Vector3D<T>& v, T s){
		if (s == 0) {
			throw std::domain_error("Cannot divide by zero.");
		}
		return Vector3D<T>(v.x / s, v.y / s, v.z / s);
	}

	/**
	 * Negate a vector.
	 * @param v The vector.
	 * @return a vector representing the result of the negation.
	 */
	template <class T>
	inline Vector3D<T> operator -(const Vector3D<T>& v){
		return Vector3D<T>(-v.x, -v.y, -v.z);
	}

	/**
	 * Add two vectors together.
	 * @param a The first vector.
	 * @param b The second vector.
	 * @return a vector representing the result of the addition.
	 */
	template <class T>
	inline Vector3D<T> operator +(const Vector3D<T>& a, const Vector3D<T>& b){
		return Vector3D<T>(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	/**
	 * Subtract one vector from another.
	 * @param a The first vector.
	 * @param b The second vector.
	 * @return a vector representing the result of the subtraction.
	 */
	template <class T>
	inline Vector3D<T> operator -(const Vector3D<T>& a, const Vector3D<T>& b){
		return Vector3D<T>(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	/**
	 * Compute the magnitude of a vector.
	 * @param v The vector.
	 * @return the magnitude of the vector.
	 */
	template <class T>
	inline T Magnitude(const Vector3D<T>& v){
		return (T)std::sqrt(std::pow(v.x, 2) + std::pow(v.y, 2) + std::pow(v.z, 2));
	}

	/**
	 * Project one vector onto another.
	 * @param a The vector to project.
	 * @param b The vector to project onto.
	 * @return the result of the projection.
	 */
	template <class T>
	inline Vector3D<T> Project(const Vector3D<T>& a, const Vector3D<T>& b){
		T denom = Dot(b, b);
		if (denom == 0) {
		throw std::domain_error("Cannot project onto a zero vector.");
		}
		T coefficient = Dot(a, b) / denom;
		return Vector3D<T>(b.x * coefficient, b.y * coefficient, b.z * coefficient);
	}

	/**
	 * Get a normalized version of a vector.
	 * @param v The vector.
	 * @return a normalized version of the vector.
	 */
	template <class T>
	inline Vector3D<T> Normalize(const Vector3D<T>& v){
		T mag = Magnitude(v);
		if (mag == 0) {
		throw std::domain_error("Cannot normalize a zero vector.");
		}
		return Vector3D<T>(v.x / mag, v.y / mag, v.z / mag);
	}

	/**
	 * Compute the cross product of two vectors.
	 * @param a The first vector.
	 * @param b The second vector.
	 * @return a vector perpendicular to both vectors.
	 */
	template <class T>
	inline Vector3D<T> CrossProduct(const Vector3D<T>& a, const Vector3D<T>& b){
		return Vector3D<T>(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
	}




	/**
	 * A struct representing a 3x3 matrix.
	 */
	template <class T>
	struct Matrix3D{
	private:
		T n[3][3];  // Store each value of the matrix

	public:
		/**
		 * Construct a 3x3 matrix with default values.
		 */
		Matrix3D() = default;

		/**
		 * Construct a 3x3 matrix with the given values in row major order.
		 */
		Matrix3D( T n00, T n01, T n02,
							T n10, T n11, T n12,
							T n20, T n21, T n22){
			n[0][0] = n00; n[0][1] = n01; n[0][2] = n02;
			n[1][0] = n10; n[1][1] = n11; n[1][2] = n12;
			n[2][0] = n20; n[2][1] = n21; n[2][2] = n22;
		}

		/**
		 * Construct a 3x3 matrix with the 3 given rows.
		 * @param a The top row of the matrix.
		 * @param b The middle row of the matrix.
		 * @param c The bottom row of the matrix.
		 */
		Matrix3D(const Vector3D<T>& a, const Vector3D<T>& b, const Vector3D<T>& c){
			n[0][0] = a.x; n[0][1] = a.y; n[0][2] = a.z;
			n[1][0] = b.x; n[1][1] = b.y; n[1][2] = b.z;
			n[2][0] = c.x; n[2][1] = c.y; n[2][2] = c.z;
		}

		/**
		 * Access the value at a given row and column within the matrix.
		 * Example: M(1,1) returns row 1 and column 1 of matrix M.
		 * @param i The row of the value.
		 * @param j The column of the value.
		 * @return the value at the given row and column.
		 */
		float& operator ()(int i, int j){
			return (n[i][j]);
		}

		/**
		 * Access the value at a given row and column within the matrix.
		 * Example: M(1,1) returns row 1 and column 1 of matrix M.
		 * @param i The row of the value.
		 * @param j The column of the value.
		 * @return the value at the given row and column.
		 */
		const float& operator ()(int i, int j) const{
			return (n[i][j]);
		}

		/**
		 * Return a row of this matrix as a reference vector.
		 * @param i The index of the row.
		 * @return the row at the given index.
		 */
		Vector3D<T>& operator [](int i){
			return (*reinterpret_cast<Vector3D<T> *>(n[i]));
		}

		/**
		 * Return a row of this matrix as a reference vector.
		 * @param i The index of the row.
		 * @return the row at the given index.
		 */
		const Vector3D<T>& operator [](int i) const{
			return (*reinterpret_cast<const Vector3D<T> *>(n[i]));
		}

		/**
		 * Return a column from the matrix as a vector.
		 * NOTE: Unlike the row access, modifying this vector WILL NOT modify the matrix.
		 * @param j The index of the column.
		 * @return a copy of the column at the given index.
		 */
		Vector3D<T> col(int j){
			return Vector3D<T>(n[0][j], n[1][j], n[2][j]);
		}

		/**
		 * Return a column from the matrix as a vector.
		 * NOTE: Unlike the row access, modifying this vector WILL NOT modify the matrix.
		 * @param j The index of the column.
		 * @return a copy of the column at the given index.
		 */
		const Vector3D<T> col(int j) const{
			return Vector3D<T>(n[0][j], n[1][j], n[2][j]);
		}
	};

	/**
	 * Multiply one matrix by another.
	 * @param A The first matrix.
	 * @param B The second matrix.
	 * @return the result of the matrix multiplication.
	 */
	template <class T>
	Matrix3D<T> operator *(const Matrix3D<T>& A, const Matrix3D<T>& B){
		const Vector3D<T> Arow1 = A[0];
		const Vector3D<T> Arow2 = A[1];
		const Vector3D<T> Arow3 = A[2];
		const Vector3D<T> Bcol1 = B.col(0);
		const Vector3D<T> Bcol2 = B.col(1);
		const Vector3D<T> Bcol3 = B.col(2);

		return Matrix3D<T>(
				Dot<T>(Arow1, Bcol1), Dot<T>(Arow1, Bcol2), Dot<T>(Arow1, Bcol3),
				Dot<T>(Arow2, Bcol1), Dot<T>(Arow2, Bcol2), Dot<T>(Arow2, Bcol3),
				Dot<T>(Arow3, Bcol1), Dot<T>(Arow3, Bcol2), Dot<T>(Arow3, Bcol3));
	}

	/**
	 * Multiply a vector by a matrix.
	 * @param v The vector.
	 * @param M The matrix.
	 * @return the result of the multiplication as a vector.
	 */
	template <class T>
	Vector3D<T> operator *(const Vector3D<T>& v, const Matrix3D<T>& M){
		const Vector3D<T> Mcol1 = M.col(0);
		const Vector3D<T> Mcol2 = M.col(1);
		const Vector3D<T> Mcol3 = M.col(2);

		return Vector3D<T>(Dot<T>(v, Mcol1), Dot<T>(v, Mcol2), Dot<T>(v, Mcol3));
	}

}


#endif
