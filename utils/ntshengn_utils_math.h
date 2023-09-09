#pragma once
#include <string>
#include <iostream>
#include <cmath>
#include <stdexcept>

namespace NtshEngn {

	namespace Math {

		struct vec2;
		struct vec3;
		struct vec4;
		struct mat2;
		struct mat3;
		struct mat4;
		struct quat;

		const float PI = 3.1415926535897932384626433832795f;

		inline float toRad(const float degrees) {
			return degrees * (PI / 180.0f);
		}
		inline float toDeg(const float radians) {
			return radians * (180.0f / PI);
		}

		inline float lerp(const float a, const float b, const float interpolationValue) {
			return a + interpolationValue * (b - a);
		}

		// vec2
		// x | y
		struct vec2 {
			float x;
			float y;
			
			// Constructors
			vec2();
			vec2(float _value);
			vec2(float _x, float _y);
			vec2(const float* _ptr);
			vec2(vec3 _xyz);
			vec2(vec4 _xyzw);

			// Operators
			vec2& operator+=(const vec2& other);
			vec2& operator-=(const vec2& other);
			vec2& operator*=(const float other);
			vec2& operator/=(const float other);
			float& operator[](size_t index);
			const float operator[](size_t index) const;

			// Functions
			float length() const;

			float* data();
		};

		// vec3
		// x | y | z
		struct vec3 {
			float x;
			float y;
			float z;
			
			// Constructors
			vec3();
			vec3(float _value);
			vec3(float _x, float _y, float _z);
			vec3(float _x, vec2 _yz);
			vec3(vec2 _xy, float _z);
			vec3(const float* _ptr);
			vec3(vec4 _xyzw);

			// Operators
			vec3& operator+=(const vec3& other);
			vec3& operator-=(const vec3& other);
			vec3& operator*=(const float other);
			vec3& operator/=(const float other);
			float& operator[](size_t index);
			const float operator[](size_t index) const;

			// Functions
			float length() const;

			float* data();
		};

		// vec4
		// x | y | z | w
		struct vec4 {
			float x;
			float y;
			float z;
			float w;
			
			// Constructors
			vec4();
			vec4(float _value);
			vec4(float _x, float _y, float _z, float _w);
			vec4(float _x, vec3 _yzw);
			vec4(vec3 _xyz, float _w);
			vec4(float _x, float _y, vec2 _zw);
			vec4(float _x, vec2 _yz, float _w);
			vec4(vec2 _xy, float _z, float _w);
			vec4(vec2 _xy, vec2 _zw);
			vec4(const float* _ptr);

			// Operators
			vec4& operator+=(const vec4& other);
			vec4& operator-=(const vec4& other);
			vec4& operator*=(const float other);
			vec4& operator/=(const float other);
			float& operator[](size_t index);
			const float operator[](size_t index) const;

			// Functions
			float length() const;

			float* data();
		};

		// mat2
		//  xx | yx
		// ----|----
		//  xy | yy
		struct mat2 {
			vec2 x;
			vec2 y;
			
			// Constructors
			mat2();
			mat2(float _value);
			mat2(float _xx, float _xy, float _yx, float _yy);
			mat2(float _xx, float _xy, vec2 _y);
			mat2(vec2 _x, float _yx, float _yy);
			mat2(vec2 _x, vec2 _y);
			mat2(const float* _ptr);
			mat2(mat3 _mat);
			mat2(mat4 _mat);

			// Operators
			mat2& operator+=(const mat2& other);
			mat2& operator-=(const mat2& other);
			mat2& operator*=(const mat2& other);
			mat2& operator*=(const float other);
			mat2& operator/=(const float other);
			vec2& operator[](size_t index);
			const vec2& operator[](size_t index) const;

			// Functions
			float det() const;

			float* data();
		};

		// mat3
		//  xx | yx | zx
		// ----|----|----
		//  xy | yy | zy
		// ----|----|----
		//  xz | yz | zz
		struct mat3 {
			vec3 x;
			vec3 y;
			vec3 z;
			
			// Constructors
			mat3();
			mat3(float _value);
			mat3(float _xx, float _xy, float _xz, float _yx, float _yy, float _yz, float _zx, float _zy, float _zz);
			mat3(float _xx, float _xy, float _xz, float _yx, float _yy, float _yz, vec3 _z);
			mat3(float _xx, float _xy, float _xz, vec3 _y, float _zx, float _zy, float _zz);
			mat3(vec3 _x, float _yx, float _yy, float _yz, float _zx, float _zy, float _zz);
			mat3(float _xx, float _xy, float _xz, vec3 _y, vec3 _z);
			mat3(vec3 _x, vec3 _y, float _zx, float _zy, float _zz);
			mat3(vec3 _x, float _yx, float _yy, float _yz, vec3 _z);
			mat3(vec3 _x, vec3 _y, vec3 _z);
			mat3(const float* _ptr);
			mat3(mat4 _mat);

			// Operators
			mat3& operator+=(const mat3& other);
			mat3& operator-=(const mat3& other);
			mat3& operator*=(const mat3& other);
			mat3& operator*=(const float other);
			mat3& operator/=(const float other);
			vec3& operator[](size_t index);
			const vec3& operator[](size_t index) const;

			// Functions
			float det() const;

			float* data();
		};

		// mat4
		//  xx | yx | zx | wx
		// ----|----|----|----
		//  xy | yy | zy | wy
		// ----|----|----|----
		//  xz | yz | zz | wz
		// ----|----|----|----
		//  xw | yw | zw | ww
		struct mat4 {
			vec4 x;
			vec4 y;
			vec4 z;
			vec4 w;
			
			// Constructors
			mat4();
			mat4(float _value);
			mat4(float _xx, float _xy, float _xz, float _xw, float _yx, float _yy, float _yz, float _yw, float _zx, float _zy, float _zz, float _zw, float _wx, float _wy, float _wz, float _ww);
			mat4(float _xx, float _xy, float _xz, float _xw, float _yx, float _yy, float _yz, float _yw, float _zx, float _zy, float _zz, float _zw, vec4 _w);
			mat4(float _xx, float _xy, float _xz, float _xw, float _yx, float _yy, float _yz, float _yw, vec4 _z, float _wx, float _wy, float _wz, float _ww);
			mat4(float _xx, float _xy, float _xz, float _xw, vec4 _y, float _zx, float _zy, float _zz, float _zw, float _wx, float _wy, float _wz, float _ww);
			mat4(vec4 _x, float _yx, float _yy, float _yz, float _yw, float _zx, float _zy, float _zz, float _zw, float _wx, float _wy, float _wz, float _ww);
			mat4(float _xx, float _xy, float _xz, float _xw, float _yx, float _yy, float _yz, float _yw, vec4 _z, vec4 _w);
			mat4(float _xx, float _xy, float _xz, float _xw, vec4 _y, float _zx, float _zy, float _zz, float _zw, vec4 _w);
			mat4(vec4 _x, float _yx, float _yy, float _yz, float _yw, float _zx, float _zy, float _zz, float _zw, vec4 _w);
			mat4(float _xx, float _xy, float _xz, float _xw, vec4 _y, vec4 _z, float _wx, float _wy, float _wz, float _ww);
			mat4(vec4 _x, float _yx, float _yy, float _yz, float _yw, vec4 _z, float _wx, float _wy, float _wz, float _ww);
			mat4(vec4 _x, vec4 _y, float _zx, float _zy, float _zz, float _zw, float _wx, float _wy, float _wz, float _ww);
			mat4(float _xx, float _xy, float _xz, float _xw, vec4 _y, vec4 _z, vec4 _w);
			mat4(vec4 _x, float _yx, float _yy, float _yz, float _yw, vec4 _z, vec4 _w);
			mat4(vec4 _x, vec4 _y, float _zx, float _zy, float _zz, float _zw, vec4 _w);
			mat4(vec4 _x, vec4 _y, vec4 _z, float _wx, float _wy, float _wz, float _ww);
			mat4(vec4 _x, vec4 _y, vec4 _z, vec4 _w);
			mat4(const float* _ptr);

			// Operators
			mat4& operator+=(const mat4& other);
			mat4& operator-=(const mat4& other);
			mat4& operator*=(const mat4& other);
			mat4& operator*=(const float other);
			mat4& operator/=(const float other);
			vec4& operator[](size_t index);
			const vec4& operator[](size_t index) const;

			// Functions
			float det() const;

			float* data();
		};

		// quat
		// a + bi + cj + dk
		struct quat {
			float a;
			float b;
			float c;
			float d;

			// Constructors
			quat();
			quat(float _a, float _b, float _c, float _d);
			quat(const float* _ptr);

			// Operators
			quat& operator+=(const quat& other);
			quat& operator-=(const quat& other);
			quat& operator*=(const quat& other);
			quat& operator*=(const float other);
			quat& operator/=(const float other);
			float& operator[](size_t index);
			const float operator[](size_t index) const;

			// Functions
			float length() const;

			float* data();
		};
		
		// Implementation
		// Constructors
		// vec2
		inline vec2::vec2(): x(0.0f), y(0.0f) {}
		inline vec2::vec2(float _value): x(_value), y(_value) {}
		inline vec2::vec2(float _x, float _y): x(_x), y(_y) {}
		inline vec2::vec2(const float* _ptr): x(*_ptr), y(*(_ptr + 1)) {}
		inline vec2::vec2(vec3 _xyz): x(_xyz.x), y(_xyz.y) {}
		inline vec2::vec2(vec4 _xyzw): x(_xyzw.x), y(_xyzw.y) {}

		// vec3
		inline vec3::vec3(): x(0.0f), y(0.0f), z(0.0f) {}
		inline vec3::vec3(float _value): x(_value), y(_value), z(_value) {}
		inline vec3::vec3(float _x, float _y, float _z): x(_x), y(_y), z(_z) {}
		inline vec3::vec3(float _x, vec2 _yz): x(_x), y(_yz.x), z(_yz.y) {}
		inline vec3::vec3(vec2 _xy, float _z): x(_xy.x), y(_xy.y), z(_z) {}
		inline vec3::vec3(const float* _ptr): x(*_ptr), y(*(_ptr + 1)), z(*(_ptr + 2)) {}
		inline vec3::vec3(vec4 _xyzw): x(_xyzw.x), y(_xyzw.y), z(_xyzw.z) {}

		// vec4
		inline vec4::vec4(): x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
		inline vec4::vec4(float _value): x(_value), y(_value), z(_value), w(_value) {}
		inline vec4::vec4(float _x, float _y, float _z, float _w): x(_x), y(_y), z(_z), w(_w) {}
		inline vec4::vec4(float _x, vec3 _yzw): x(_x), y(_yzw.x), z(_yzw.y), w(_yzw.z) {}
		inline vec4::vec4(vec3 _xyz, float _w): x(_xyz.x), y(_xyz.y), z(_xyz.z), w(_w) {}
		inline vec4::vec4(float _x, float _y, vec2 _zw): x(_x), y(_y), z(_zw.x), w(_zw.y) {}
		inline vec4::vec4(float _x, vec2 _yz, float _w): x(_x), y(_yz.x), z(_yz.y), w(_w) {}
		inline vec4::vec4(vec2 _xy, float _z, float _w): x(_xy.x), y(_xy.y), z(_z), w(_w) {}
		inline vec4::vec4(vec2 _xy, vec2 _zw): x(_xy.x), y(_xy.y), z(_zw.x), w(_zw.y) {}
		inline vec4::vec4(const float* _ptr): x(*_ptr), y(*(_ptr + 1)), z(*(_ptr + 2)), w(*(_ptr + 3)) {}

		// mat2
		inline mat2::mat2(): x(1.0f, 0.0f), y(0.0f, 1.0f) {}
		inline mat2::mat2(float _value): x(_value), y(_value) {}
		inline mat2::mat2(float _xx, float _xy, float _yx, float _yy): x(_xx, _xy), y(_yx, _yy) {}
		inline mat2::mat2(float _xx, float _xy, vec2 _y): x(_xx, _xy), y(_y) {}
		inline mat2::mat2(vec2 _x, float _yx, float _yy): x(_x), y(_yx, _yy) {}
		inline mat2::mat2(vec2 _x, vec2 _y): x(_x), y(_y) {}
		inline mat2::mat2(const float* _ptr): x(_ptr), y(_ptr + 2) {}
		inline mat2::mat2(mat3 _mat): x(_mat.x), y(_mat.y) {}
		inline mat2::mat2(mat4 _mat): x(_mat.x), y(_mat.y) {}

		// mat3
		inline mat3::mat3(): x(1.0f, 0.0f, 0.0f), y(0.0f, 1.0f, 0.0f), z(0.0f, 0.0f, 1.0f) {}
		inline mat3::mat3(float _value): x(_value), y(_value), z(_value) {}
		inline mat3::mat3(float _xx, float _xy, float _xz, float _yx, float _yy, float _yz, float _zx, float _zy, float _zz): x(_xx, _xy, _xz), y(_yx, _yy, _yz), z(_zx, _zy, _zz) {}
		inline mat3::mat3(float _xx, float _xy, float _xz, float _yx, float _yy, float _yz, vec3 _z): x(_xx, _xy, _xz), y(_yx, _yy, _yz), z(_z) {}
		inline mat3::mat3(float _xx, float _xy, float _xz, vec3 _y, float _zx, float _zy, float _zz): x(_xx, _xy, _xz), y(_y), z(_zx, _zy, _zz) {}
		inline mat3::mat3(vec3 _x, float _yx, float _yy, float _yz, float _zx, float _zy, float _zz): x(_x), y(_yx, _yy, _yz), z(_zx, _zy, _zz) {}
		inline mat3::mat3(float _xx, float _xy, float _xz, vec3 _y, vec3 _z): x(_xx, _xy, _xz), y(_y), z(_z) {}
		inline mat3::mat3(vec3 _x, vec3 _y, float _zx, float _zy, float _zz): x(_x), y(_y), z(_zx, _zy, _zz) {}
		inline mat3::mat3(vec3 _x, float _yx, float _yy, float _yz, vec3 _z): x(_x), y(_yx, _yy, _yz), z(_z) {}
		inline mat3::mat3(vec3 _x, vec3 _y, vec3 _z): x(_x), y(_y), z(_z) {}
		inline mat3::mat3(const float* _ptr): x(_ptr), y(_ptr + 3), z(_ptr + 6) {}
		inline mat3::mat3(mat4 _mat): x(_mat.x), y(_mat.y), z(_mat.z) {}

		// mat4
		inline mat4::mat4(): x(1.0f, 0.0f, 0.0f, 0.0f), y(0.0f, 1.0f, 0.0f, 0.0f), z(0.0f, 0.0f, 1.0f, 0.0f), w(0.0f, 0.0f, 0.0f, 1.0f) {}
		inline mat4::mat4(float _value): x(_value), y(_value), z(_value), w(_value) {}
		inline mat4::mat4(float _xx, float _xy, float _xz, float _xw, float _yx, float _yy, float _yz, float _yw, float _zx, float _zy, float _zz, float _zw, float _wx, float _wy, float _wz, float _ww): x(_xx, _xy, _xz, _xw), y(_yx, _yy, _yz, _yw), z(_zx, _zy, _zz, _zw), w(_wx, _wy, _wz, _ww) {}
		inline mat4::mat4(float _xx, float _xy, float _xz, float _xw, float _yx, float _yy, float _yz, float _yw, float _zx, float _zy, float _zz, float _zw, vec4 _w): x(_xx, _xy, _xz, _xw), y(_yx, _yy, _yz, _yw), z(_zx, _zy, _zz, _zw), w(_w) {}
		inline mat4::mat4(float _xx, float _xy, float _xz, float _xw, float _yx, float _yy, float _yz, float _yw, vec4 _z, float _wx, float _wy, float _wz, float _ww): x(_xx, _xy, _xz, _xw), y(_yx, _yy, _yz, _yw), z(_z), w(_wx, _wy, _wz, _ww) {}
		inline mat4::mat4(float _xx, float _xy, float _xz, float _xw, vec4 _y, float _zx, float _zy, float _zz, float _zw, float _wx, float _wy, float _wz, float _ww): x(_xx, _xy, _xz, _xw), y(_y), z(_zx, _zy, _zz, _zw), w(_wx, _wy, _wz, _ww) {}
		inline mat4::mat4(vec4 _x, float _yx, float _yy, float _yz, float _yw, float _zx, float _zy, float _zz, float _zw, float _wx, float _wy, float _wz, float _ww): x(_x), y(_yx, _yy, _yz, _yw), z(_zx, _zy, _zz, _zw), w(_wx, _wy, _wz, _ww) {}
		inline mat4::mat4(float _xx, float _xy, float _xz, float _xw, float _yx, float _yy, float _yz, float _yw, vec4 _z, vec4 _w): x(_xx, _xy, _xz, _xw), y(_yx, _yy, _yz, _yw), z(_z), w(_w) {}
		inline mat4::mat4(float _xx, float _xy, float _xz, float _xw, vec4 _y, float _zx, float _zy, float _zz, float _zw, vec4 _w): x(_xx, _xy, _xz, _xw), y(_y), z(_zx, _zy, _zz, _zw), w(_w) {}
		inline mat4::mat4(vec4 _x, float _yx, float _yy, float _yz, float _yw, float _zx, float _zy, float _zz, float _zw, vec4 _w): x(_x), y(_yx, _yy, _yz, _yw), z(_zx, _zy, _zz, _zw), w(_w) {}
		inline mat4::mat4(float _xx, float _xy, float _xz, float _xw, vec4 _y, vec4 _z, float _wx, float _wy, float _wz, float _ww): x(_xx, _xy, _xz, _xw), y(_y), z(_z), w(_wx, _wy, _wz, _ww) {}
		inline mat4::mat4(vec4 _x, float _yx, float _yy, float _yz, float _yw, vec4 _z, float _wx, float _wy, float _wz, float _ww): x(_x), y(_yx, _yy, _yz, _yw), z(_z), w(_wx, _wy, _wz, _ww) {}
		inline mat4::mat4(vec4 _x, vec4 _y, float _zx, float _zy, float _zz, float _zw, float _wx, float _wy, float _wz, float _ww): x(_x), y(_y), z(_zx, _zy, _zz, _zw), w(_wx, _wy, _wz, _ww) {}
		inline mat4::mat4(float _xx, float _xy, float _xz, float _xw, vec4 _y, vec4 _z, vec4 _w): x(_xx, _xy, _xz, _xw), y(_y), z(_z), w(_w) {}
		inline mat4::mat4(vec4 _x, float _yx, float _yy, float _yz, float _yw, vec4 _z, vec4 _w): x(_x), y(_yx, _yy, _yz, _yw), z(_z), w(_w) {}
		inline mat4::mat4(vec4 _x, vec4 _y, float _zx, float _zy, float _zz, float _zw, vec4 _w): x(_x), y(_y), z(_zx, _zy, _zz, _zw), w(_w) {}
		inline mat4::mat4(vec4 _x, vec4 _y, vec4 _z, float _wx, float _wy, float _wz, float _ww): x(_x), y(_y), z(_z), w(_wx, _wy, _wz, _ww) {}
		inline mat4::mat4(vec4 _x, vec4 _y, vec4 _z, vec4 _w): x(_x), y(_y), z(_z), w(_w) {}
		inline mat4::mat4(const float* _ptr): x(_ptr), y(_ptr + 4), z(_ptr + 8), w(_ptr + 12) {}

		// quat
		inline quat::quat(): a(1.0f), b(0.0f), c(0.0f), d(0.0f) {}
		inline quat::quat(float _a, float _b, float _c, float _d): a(_a), b(_b), c(_c), d(_d) {}
		inline quat::quat(const float* _ptr): a(*_ptr), b(*(_ptr + 1)), c(*(_ptr + 2)), d(*(_ptr + 3)) {}

		// Operators
		// vec2
		inline vec2& vec2::operator+=(const vec2& other) { 
			x += other.x;
			y += other.y;

			return *this;
		}
		inline vec2& vec2::operator-=(const vec2& other) { 
			x -= other.x;
			y -= other.y;

			return *this;
		}
		inline vec2& vec2::operator*=(const float other) {
			x *= other;
			y *= other;

			return *this;
		}
		inline vec2& vec2::operator/=(const float other) {
			x /= other;
			y /= other;

			return *this;
		}
		inline float& vec2::operator[](size_t index) {
			if (index == 0) { return x; }
			else if (index == 1) { return y; }
			else { throw std::out_of_range("vec2::operator[]: index is out of range."); }
		}
		inline const float vec2::operator[](size_t index) const {
			if (index == 0) { return x; }
			else if (index == 1) { return y; }
			else { throw std::out_of_range("vec2::operator[]: index is out of range."); }
		}

		// vec3
		inline vec3& vec3::operator+=(const vec3& other) { 
			x += other.x;
			y += other.y;
			z += other.z;

			return *this;
		}
		inline vec3& vec3::operator-=(const vec3& other) { 
			x -= other.x;
			y -= other.y;
			z -= other.z;

			return *this;
		}
		inline vec3& vec3::operator*=(const float other) {
			x *= other;
			y *= other;
			z *= other;

			return *this;
		}
		inline vec3& vec3::operator/=(const float other) {
			x /= other;
			y /= other;
			z /= other;

			return *this;
		}
		inline float& vec3::operator[](size_t index) {
			if (index == 0) { return x; }
			else if (index == 1) { return y; }
			else if (index == 2) { return z; }
			else { throw std::out_of_range("vec3::operator[]: index is out of range."); }
		}
		inline const float vec3::operator[](size_t index) const {
			if (index == 0) { return x; }
			else if (index == 1) { return y; }
			else if (index == 2) { return z; }
			else { throw std::out_of_range("vec3::operator[]: index is out of range."); }
		}

		// vec4
		inline vec4& vec4::operator+=(const vec4& other) { 
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;

			return *this;
		}
		inline vec4& vec4::operator-=(const vec4& other) { 
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;

			return *this;
		}
		inline vec4& vec4::operator*=(const float other) {
			x *= other;
			y *= other;
			z *= other;
			w *= other;

			return *this;
		}
		inline vec4& vec4::operator/=(const float other) {
			x /= other;
			y /= other;
			z /= other;
			w /= other;

			return *this;
		}
		inline float& vec4::operator[](size_t index) {
			if (index == 0) { return x; }
			else if (index == 1) { return y; }
			else if (index == 2) { return z; }
			else if (index == 3) { return w; }
			else { throw std::out_of_range("vec4::operator[]: index is out of range."); }
		}
		inline const float vec4::operator[](size_t index) const {
			if (index == 0) { return x; }
			else if (index == 1) { return y; }
			else if (index == 2) { return z; }
			else if (index == 3) { return w; }
			else { throw std::out_of_range("vec4::operator[]: index is out of range."); }
		}

		// mat2
		inline mat2& mat2::operator+=(const mat2& other) {
			x += other.x;
			y += other.y;

			return *this;
		}
		inline mat2& mat2::operator-=(const mat2& other) {
			x -= other.x;
			y -= other.y;

			return *this;
		}
		inline mat2& mat2::operator*=(const mat2& other) {
			const mat2 tmp(vec2(x.x * other.x.x + y.x * other.x.y,
					x.y * other.x.x + y.y * other.x.y),
				vec2(x.x * other.y.x + y.x * other.y.y,
					x.y * other.y.x + y.y * other.y.y));

			x = tmp.x;
			y = tmp.y;

			return *this;
		}
		inline mat2& mat2::operator*=(const float other) {
			x *= other;
			y *= other;

			return *this;
		}
		inline mat2& mat2::operator/=(const float other) {
			x /= other;
			y /= other;

			return *this;
		}
		inline vec2& mat2::operator[](size_t index) {
			if (index == 0) { return x; }
			else if (index == 1) { return y; }
			else { throw std::out_of_range("mat2::operator[]: index is out of range."); }
		}
		inline const vec2& mat2::operator[](size_t index) const {
			if (index == 0) { return x; }
			else if (index == 1) { return y; }
			else { throw std::out_of_range("mat2::operator[]: index is out of range."); }
		}

		// mat3
		inline mat3& mat3::operator+=(const mat3& other) {
			x += other.x;
			y += other.y;
			z += other.z;

			return *this;
		}
		inline mat3& mat3::operator-=(const mat3& other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;

			return *this;
		}
		inline mat3& mat3::operator*=(const mat3& other) {
			mat3 tmp(vec3(x.x * other.x.x + y.x * other.x.y + z.x * other.x.z,
					x.y * other.x.x + y.y * other.x.y + z.y * other.x.z,
					x.z * other.x.x + y.z * other.x.y + z.z * other.x.z),
				vec3(x.x * other.y.x + y.x * other.y.y + z.x * other.y.z,
					x.y * other.y.x + y.y * other.y.y + z.y * other.y.z,
					x.z * other.y.x + y.z * other.y.y + z.z * other.y.z),
				vec3(x.x * other.z.x + y.x * other.z.y + z.x * other.z.z,
					x.y * other.z.x + y.y * other.z.y + z.y * other.z.z,
					x.z * other.z.x + y.z * other.z.y + z.z * other.z.z));

			x = tmp.x;
			y = tmp.y;
			z = tmp.z;

			return *this;
		}
		inline mat3& mat3::operator*=(const float other) {
			x *= other;
			y *= other;
			z *= other;

			return *this;
		}
		inline mat3& mat3::operator/=(const float other) {
			x /= other;
			y /= other;
			z /= other;

			return *this;
		}
		inline vec3& mat3::operator[](size_t index) {
			if (index == 0) { return x; }
			else if (index == 1) { return y; }
			else if (index == 2) { return z; }
			else { throw std::out_of_range("mat3::operator[]: index is out of range."); }
		}
		inline const vec3& mat3::operator[](size_t index) const {
			if (index == 0) { return x; }
			else if (index == 1) { return y; }
			else if (index == 2) { return z; }
			else { throw std::out_of_range("mat3::operator[]: index is out of range."); }
		}

		// mat4
		inline mat4& mat4::operator+=(const mat4& other) {
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;

			return *this;
		}
		inline mat4& mat4::operator-=(const mat4& other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;

			return *this;
		}
		inline mat4& mat4::operator*=(const mat4& other) {
			const mat4 tmp(vec4(x.x * other.x.x + y.x * other.x.y + z.x * other.x.z + w.x * other.x.w,
					x.y * other.x.x + y.y * other.x.y + z.y * other.x.z + w.y * other.x.w,
					x.z * other.x.x + y.z * other.x.y + z.z * other.x.z + w.z * other.x.w,
					x.w * other.x.x + y.w * other.x.y + z.w * other.x.z + w.w * other.x.w),
				vec4(x.x * other.y.x + y.x * other.y.y + z.x * other.y.z + w.x * other.y.w,
					x.y * other.y.x + y.y * other.y.y + z.y * other.y.z + w.y * other.y.w,
					x.z * other.y.x + y.z * other.y.y + z.z * other.y.z + w.z * other.y.w,
					x.w * other.y.x + y.w * other.y.y + z.w * other.y.z + w.w * other.y.w),
				vec4(x.x * other.z.x + y.x * other.z.y + z.x * other.z.z + w.x * other.z.w,
					x.y * other.z.x + y.y * other.z.y + z.y * other.z.z + w.y * other.z.w,
					x.z * other.z.x + y.z * other.z.y + z.z * other.z.z + w.z * other.z.w,
					x.w * other.z.x + y.w * other.z.y + z.w * other.z.z + w.w * other.z.w),
				vec4(x.x * other.w.x + y.x * other.w.y + z.x * other.w.z + w.x * other.w.w,
					x.y * other.w.x + y.y * other.w.y + z.y * other.w.z + w.y * other.w.w,
					x.z * other.w.x + y.z * other.w.y + z.z * other.w.z + w.z * other.w.w,
					x.w * other.w.x + y.w * other.w.y + z.w * other.w.z + w.w * other.w.w));

			x = tmp.x;
			y = tmp.y;
			z = tmp.z;
			w = tmp.w;

			return *this;
		}
		inline mat4& mat4::operator*=(const float other) {
			x *= other;
			y *= other;
			z *= other;
			w *= other;

			return *this;
		}
		inline mat4& mat4::operator/=(const float other) {
			x /= other;
			y /= other;
			z /= other;
			w /= other;

			return *this;
		}
		inline vec4& mat4::operator[](size_t index) {
			if (index == 0) { return x; }
			else if (index == 1) { return y; }
			else if (index == 2) { return z; }
			else if (index == 3) { return w; }
			else { throw std::out_of_range("mat4::operator[]: index is out of range."); }
		}
		inline const vec4& mat4::operator[](size_t index) const {
			if (index == 0) { return x; }
			else if (index == 1) { return y; }
			else if (index == 2) { return z; }
			else if (index == 3) { return w; }
			else { throw std::out_of_range("mat4::operator[]: index is out of range."); }
		}

		// quat
		inline quat& quat::operator+=(const quat& other) {
			a += other.a;
			b += other.b;
			c += other.c;
			d += other.d;

			return *this;
		}
		inline quat& quat::operator-=(const quat& other) {
			a -= other.a;
			b -= other.b;
			c -= other.c;
			d -= other.d;

			return *this;
		}
		inline quat& quat::operator*=(const quat& other) {
			const quat tmp((a * other.a) - (b * other.b) - (c * other.c) - (d * other.d),
			(a * other.b) + (b * other.a) + (c * other.d) - (d * other.c),
			(a * other.c) - (b * other.d) + (c * other.a) + (d * other.b),
			(a * other.d) + (b * other.c) - (c * other.b) + (d * other.a));

			a = tmp.a;
			b = tmp.b;
			c = tmp.c;
			d = tmp.d;

			return *this;
		}
		inline quat& quat::operator*=(const float other) {
			a *= other;
			b *= other;
			c *= other;
			d *= other;

			return *this;
		}
		inline quat& quat::operator/=(const float other) {
			a /= other;
			b /= other;
			c /= other;
			d /= other;

			return *this;
		}
		inline float& quat::operator[](size_t index) {
			if (index == 0) { return a; }
			else if (index == 1) { return b; }
			else if (index == 2) { return c; }
			else if (index == 3) { return d; }
			else { throw std::out_of_range("quat::operator[]: index is out of range."); }
		}
		inline const float quat::operator[](size_t index) const {
			if (index == 0) { return a; }
			else if (index == 1) { return b; }
			else if (index == 2) { return c; }
			else if (index == 3) { return d; }
			else { throw std::out_of_range("quat::operator[]: index is out of range."); }
		}

		// Functions
		// vec2
		inline float vec2::length() const {
			return std::sqrt((x * x) + (y * y));
		}

		inline float* vec2::data() {
			return &x;
		}

		// vec3
		inline float vec3::length() const {
			return std::sqrt((x * x) + (y * y) + (z * z));
		}
		
		inline float* vec3::data() {
			return &x;
		}

		// vec4
		inline float vec4::length() const {
				return std::sqrt((x * x) + (y * y) + (z * z) + (w * w));
			}

		inline float* vec4::data() {
			return &x;
		}

		// mat2
		inline float mat2::det() const {
			return (x.x * y.y -
				y.x * x.y);
		}

		inline float* mat2::data() {
			return x.data();
		}

		// mat3
		inline float mat3::det() const {
			return ((x.x * ((y.y * z.z) - (z.y * y.z))) -
				(y.x * ((x.y * z.z) - (z.y * x.z))) +
				(z.x *((x.y * y.z) - (y.y * x.z))));
		}

		inline float* mat3::data() {
			return x.data();
		}

		// mat4
		inline float mat4::det() const {
			return (x.x * ((y.y * z.z * w.w) - (y.y * w.z * z.w) - (z.y * y.z * w.w) + (z.y * w.z * y.w) + (w.y * y.z * z.w) - (w.y * z.z * y.w)) -
				y.x * ((x.y * z.z * w.w) - (x.y * w.z * z.w) - (z.y * x.z * w.w) + (z.y * w.z * x.w) + (w.y * x.z * z.w) - (w.y * z.z * x.w)) +
				z.x * ((x.y * y.z * w.w) - (x.y * w.z * y.w) - (y.y * x.z * w.w) + (y.y * w.z * x.w) + (w.y * x.z * y.w) - (w.y * y.z * x.w)) -
				w.x * ((x.y * y.z * z.w) - (x.y * z.z * y.w) - (y.y * x.z * z.w) + (y.y * z.z * x.w) + (z.y * x.z * y.w) - (z.y * y.z * x.w)));
		}

		inline float* mat4::data() {
			return x.data();
		}

		// quat
		inline float quat::length() const {
			return std::sqrt((a * a) + (b * b) + (c * c) + (d * d));
		}

		inline float* quat::data() {
			return &a;
		}

		// Namespace
		// Operators
		// vec2
		inline vec2 operator+(vec2 lhs, const vec2& rhs) { 
			lhs += rhs;

			return lhs;
		}
		inline vec2 operator-(vec2 lhs, const vec2& rhs) {
			lhs -= rhs;

			return lhs;
		}
		inline vec2 operator*(vec2 lhs, const float rhs) {
			lhs *= rhs;

			return lhs;
		}
		inline vec2 operator*(float lhs, const vec2& rhs) {
			return (rhs * lhs);
		}
		inline vec2 operator/(vec2 lhs, const float rhs) { 
			lhs /= rhs;

			return lhs;
		}
		inline bool operator==(const vec2& lhs, const vec2& rhs) {
			return ((lhs.x == rhs.x) && (lhs.y == rhs.y));
		}
		inline bool operator!=(const vec2& lhs, const vec2& rhs) {
			return !(lhs == rhs);
		}

		// vec3
		inline vec3 operator+(vec3 lhs, const vec3& rhs) { 
			lhs += rhs;

			return lhs;
		}
		inline vec3 operator-(vec3 lhs, const vec3& rhs) {
			lhs -= rhs;

			return lhs;
		}
		inline vec3 operator*(vec3 lhs, const float rhs) {
			lhs *= rhs;

			return lhs;
		}
		inline vec3 operator*(float lhs, const vec3& rhs) {
			return (rhs * lhs);
		}
		inline vec3 operator/(vec3 lhs, const float rhs) { 
			lhs /= rhs;

			return lhs;
		}
		inline bool operator==(const vec3& lhs, const vec3& rhs) {
			return ((lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z));
		}
		inline bool operator!=(const vec3& lhs, const vec3& rhs) {
			return !(lhs == rhs);
		}

		// vec4
		inline vec4 operator+(vec4 lhs, const vec4& rhs) { 
			lhs += rhs;

			return lhs;
		}
		inline vec4 operator-(vec4 lhs, const vec4& rhs) {
			lhs -= rhs;

			return lhs;
		}
		inline vec4 operator*(vec4 lhs, const float rhs) {
			lhs *= rhs;

			return lhs;
		}
		inline vec4 operator*(float lhs, const vec4& rhs) {
			return (rhs * lhs);
		}
		inline vec4 operator/(vec4 lhs, const float rhs) { 
			lhs /= rhs;

			return lhs;
		}
		inline bool operator==(const vec4& lhs, const vec4& rhs) {
			return ((lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z) && (lhs.w == rhs.w));
		}
		inline bool operator!=(const vec4& lhs, const vec4& rhs) {
			return !(lhs == rhs);
		}

		// mat2
		inline mat2 operator+(mat2 lhs, const mat2& rhs) {
			lhs += rhs;

			return lhs;
		}
		inline mat2 operator-(mat2 lhs, const mat2& rhs) {
			lhs -= rhs;

			return lhs;
		}
		inline mat2 operator*(mat2 lhs, const mat2& rhs) { 
			lhs *= rhs;

			return lhs;
		}
		inline vec2 operator*(mat2 lhs, const vec2& rhs) {
			return vec2(lhs.x.x * rhs.x + lhs.y.x * rhs.y,
				lhs.x.y * rhs.x + lhs.y.y * rhs.y);
		}
		inline mat2 operator*(mat2 lhs, const float rhs) {
			lhs *= rhs;

			return lhs;
		}
		inline mat2 operator*(float lhs, const mat2& rhs) {
			return (rhs * lhs);
		}
		inline mat2 operator/(mat2 lhs, const float rhs) {
			lhs /= rhs;

			return lhs;
		}
		inline bool operator==(const mat2& lhs, const mat2& rhs) {
			return ((lhs.x == rhs.x) && (lhs.y == rhs.y));
		}
		inline bool operator!=(const mat2& lhs, const mat2& rhs) {
			return !(lhs == rhs);
		}

		// mat3
		inline mat3 operator+(mat3 lhs, const mat3& rhs) {
			lhs += rhs;

			return lhs;
		}
		inline mat3 operator-(mat3 lhs, const mat3& rhs) {
			lhs -= rhs;

			return lhs;
		}
		inline mat3 operator*(mat3 lhs, const mat3& rhs) { 
			lhs *= rhs;

			return lhs;
		}
		inline vec3 operator*(mat3 lhs, const vec3& rhs) {
			return vec3(lhs.x.x * rhs.x + lhs.y.x * rhs.y + lhs.z.x * rhs.z,
				lhs.x.y * rhs.x + lhs.y.y * rhs.y + lhs.z.y * rhs.z,
				lhs.x.z * rhs.x + lhs.y.z * rhs.y + lhs.z.z * rhs.z);
		}
		inline mat3 operator*(mat3 lhs, const float rhs) {
			lhs *= rhs;

			return lhs;
		}
		inline mat3 operator*(float lhs, const mat3& rhs) {
			return (rhs * lhs);
		}
		inline mat3 operator/(mat3 lhs, const float rhs) {
			lhs /= rhs;

			return lhs;
		}
		inline bool operator==(const mat3& lhs, const mat3& rhs) {
			return ((lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z));
		}
		inline bool operator!=(const mat3& lhs, const mat3& rhs) {
			return !(lhs == rhs);
		}

		// mat4
		inline mat4 operator+(mat4 lhs, const mat4& rhs) {
			lhs += rhs;

			return lhs;
		}
		inline mat4 operator-(mat4 lhs, const mat4& rhs) {
			lhs -= rhs;

			return lhs;
		}
		inline mat4 operator*(mat4 lhs, const mat4& rhs) { 
			lhs *= rhs;

			return lhs;
		}
		inline vec4 operator*(mat4 lhs, const vec4& rhs) {
			return vec4(lhs.x.x * rhs.x + lhs.y.x * rhs.y + lhs.z.x * rhs.z + lhs.w.x * rhs.w,
				lhs.x.y * rhs.x + lhs.y.y * rhs.y + lhs.z.y * rhs.z + lhs.w.y * rhs.w,
				lhs.x.z * rhs.x + lhs.y.z * rhs.y + lhs.z.z * rhs.z + lhs.w.z * rhs.w,
				lhs.x.w * rhs.x + lhs.y.w * rhs.y + lhs.z.w * rhs.z + lhs.w.w * rhs.w);
		}
		inline mat4 operator*(mat4 lhs, const float rhs) {
			lhs *= rhs;

			return lhs;
		}
		inline mat4 operator*(float lhs, const mat4& rhs) {
			return (rhs * lhs);
		}
		inline mat4 operator/(mat4 lhs, const float rhs) {
			lhs /= rhs;

			return lhs;
		}
		inline bool operator==(const mat4& lhs, const mat4& rhs) {
			return ((lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z));
		}
		inline bool operator!=(const mat4& lhs, const mat4& rhs) {
			return !(lhs == rhs);
		}

		// quat
		inline quat operator+(quat lhs, const quat& rhs) {
			lhs += rhs;

			return lhs;
		}
		inline quat operator-(quat lhs, const quat& rhs) {
			lhs -= rhs;

			return lhs;
		}
		inline quat operator*(quat lhs, const quat& rhs) {
			lhs *= rhs;

			return lhs;
		}
		inline quat operator*(quat lhs, const float rhs) {
			lhs *= rhs;

			return lhs;
		}
		inline quat operator*(float lhs, const quat& rhs) {
			return (rhs * lhs);
		}
		inline quat operator/(quat lhs, const float rhs) {
			lhs /= rhs;

			return lhs;
		}
		inline bool operator==(const quat& lhs, const quat& rhs) {
			return ((lhs.a == rhs.a) && (lhs.b == rhs.b) && (lhs.c == rhs.c) && (lhs.d == rhs.d));
		}
		inline bool operator!=(const quat& lhs, const quat& rhs) {
			return !(lhs == rhs);
		}

		// Functions
		// vec2
		inline vec2 normalize(const vec2& vec) {
			const float l = vec.length();

			return (vec / l);
		}
		inline float dot(const vec2& a, const vec2& b) {
			return ((a.x * b.x) + (a.y * b.y));
		}
		inline vec2 reflect(const vec2& i, const vec2& n) {
			return (i - 2.0f * dot(n, i) * n);
		}
		inline vec2 refract(const vec2& i, const vec2& n, float ior) {
			const float ndoti = dot(n, i);
			const float k = 1.0f - ior * ior * (1.0f - ndoti * ndoti);
			if (k < 0.0f) {
				return vec2(0.0f);
			}
			else {
				return ior * i - (ior * ndoti + std::sqrt(k)) * n;
			}
		}

		inline std::string to_string(const vec2& vec) {
			return ("[" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + "]");
		}

		// vec3
		inline vec3 normalize(const vec3& vec) {
			const float l = vec.length();

			return (vec / l);
		}
		inline float dot(const vec3& a, const vec3& b) {
			return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
		}
		inline vec3 cross(const vec3& a, const vec3& b) {
			return vec3(a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x);
		}
		inline vec3 reflect(const vec3& i, const vec3& n) {
			return (i - 2.0f * dot(n, i) * n);
		}
		inline vec3 refract(const vec3& i, const vec3& n, float ior) {
			const float ndoti = dot(n, i);
			const float k = 1.0f - ior * ior * (1.0f - ndoti * ndoti);
			if (k < 0.0f) {
				return vec3(0.0f);
			}
			else {
				return ior * i - (ior * ndoti + std::sqrt(k)) * n;
			}
		}

		inline vec3 to_vec3(const quat& qua) {
			return vec3(std::atan2(2.0f * ((qua.a * qua.b) + (qua.c * qua.d)), 1.0f - (2.0f * ((qua.b * qua.b) + (qua.c * qua.c)))),
				std::asin(2.0f * ((qua.a * qua.c) - (qua.d * qua.b))),
				std::atan2(2.0f * ((qua.a * qua.d) + (qua.b * qua.c)), 1.0f - (2.0f * ((qua.c * qua.c) + (qua.d * qua.d)))));
		}
		inline std::string to_string(const vec3& vec) {
			return ("[" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + "]");
		}

		// vec4
		inline vec4 normalize(const vec4& vec) {
			const float l = vec.length();

			return (vec / l);
		}
		inline float dot(const vec4& a, const vec4& b) {
			return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w));
		}
		inline vec4 reflect(const vec4& i, const vec4& n) {
			return (i - 2.0f * dot(n, i) * n);
		}
		inline vec4 refract(const vec4& i, const vec4& n, float ior) {
			const float ndoti = dot(n, i);
			const float k = 1.0f - ior * ior * (1.0f - ndoti * ndoti);
			if (k < 0.0f) {
				return vec4(0.0f);
			}
			else {
				return ior * i - (ior * ndoti + std::sqrt(k)) * n;
			}
		}

		inline std::string to_string(const vec4& vec) {
			return ("[" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + ", " + std::to_string(vec.w) + "]");
		}

		// mat2
		inline mat2 transpose(const mat2& mat) {
			return mat2(mat.x.x, mat.y.x, mat.x.y, mat.y.y);
		}
		inline mat2 inverse(const mat2& mat) {
			const float determinant = mat.det();

			return ((1.0f / determinant) * mat2(mat.y.y, -mat.x.y, -mat.y.x, mat.x.x));
		}

		inline std::string to_string(const mat2& mat) {
			return ("[" + to_string(mat.x) + ", " + to_string(mat.y) + "]");
		}

		// mat3
		inline mat3 transpose(const mat3& mat) {
			return mat3(mat.x.x, mat.y.x, mat.z.x, mat.x.y, mat.y.y, mat.z.y, mat.x.z, mat.y.z, mat.z.z);
		}
		inline mat3 inverse(const mat3& mat) {
			const float determinant = mat.det();

			const mat3 t = transpose(mat);
			const float a = mat2(t.y.y, t.y.z, t.z.y, t.z.z).det();
			const float b = mat2(t.y.x, t.y.z, t.z.x, t.z.z).det() * -1.0f;
			const float c = mat2(t.y.x, t.y.y, t.z.x, t.z.y).det();
			const float d = mat2(t.x.y, t.x.z, t.z.y, t.z.z).det() * -1.0f;
			const float e = mat2(t.x.x, t.x.z, t.z.x, t.z.z).det();
			const float f = mat2(t.x.x, t.x.y, t.z.x, t.z.y).det() * -1.0f;
			const float g = mat2(t.x.y, t.x.z, t.y.y, t.y.z).det();
			const float h = mat2(t.x.x, t.x.z, t.y.x, t.y.z).det() * -1.0f;
			const float i = mat2(t.x.x, t.x.y, t.y.x, t.y.y).det();

			const mat3 adj = mat3(a, b, c, d, e, f, g, h, i);

			return ((1.0f / determinant) * adj);
		}
		inline mat3 translate(const vec2& translation) {
			return mat3(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, translation.x, translation.y, 1.0f);
		}
		inline mat3 rotate(const float angle) {
			const float cosTheta = std::cos(angle);
			const float sinTheta = std::sin(angle);
			
			return mat3(cosTheta, sinTheta, 0.0f, -sinTheta, cosTheta, 0.0f, 0.0f, 0.0f, 1.0f);
		}
		inline mat3 scale(const vec2& scaling) {
			return mat3(scaling.x, 0.0f, 0.0f, 0.0f, scaling.y, 0.0f, 0.0f, 0.0f, 1.0f);
		}

		inline std::string to_string(const mat3& mat) {
			return ("[" + to_string(mat.x) + ", " + to_string(mat.y) + ", " + to_string(mat.z) + "]");
		}

		// mat4
		inline mat4 transpose(const mat4& mat) {
			return mat4(mat.x.x, mat.y.x, mat.z.x, mat.w.x, mat.x.y, mat.y.y, mat.z.y, mat.w.y, mat.x.z, mat.y.z, mat.z.z, mat.w.z, mat.x.w, mat.y.w, mat.z.w, mat.w.w);
		}
		inline mat4 inverse(const mat4& mat) {
			const float determinant = mat.det();

			const mat4 t = transpose(mat);
			const float a = mat3(t.y.y, t.y.z, t.y.w, t.z.y, t.z.z, t.z.w, t.w.y, t.w.z, t.w.w).det();
			const float b = mat3(t.y.x, t.y.z, t.y.w, t.z.x, t.z.z, t.z.w, t.w.x, t.w.z, t.w.w).det() * -1.0f;
			const float c = mat3(t.y.x, t.y.y, t.y.w, t.z.x, t.z.y, t.z.w, t.w.x, t.w.y, t.w.w).det();
			const float d = mat3(t.y.x, t.y.y, t.y.z, t.z.x, t.z.y, t.z.z, t.w.x, t.w.y, t.w.z).det() * -1.0f;
			const float e = mat3(t.x.y, t.x.z, t.x.w, t.z.y, t.z.z, t.z.w, t.w.y, t.w.z, t.w.w).det() * -1.0f;
			const float f = mat3(t.x.x, t.x.z, t.x.w, t.z.x, t.z.z, t.z.w, t.w.x, t.w.z, t.w.w).det();
			const float g = mat3(t.x.x, t.x.y, t.x.w, t.z.x, t.z.y, t.z.w, t.w.x, t.w.y, t.w.w).det() * -1.0f;
			const float h = mat3(t.x.x, t.x.y, t.x.z, t.z.x, t.z.y, t.z.z, t.w.x, t.w.y, t.w.z).det();
			const float i = mat3(t.x.y, t.x.z, t.x.w, t.y.y, t.y.z, t.y.w, t.w.y, t.w.z, t.w.w).det();
			const float j = mat3(t.x.x, t.x.z, t.x.w, t.y.x, t.y.z, t.y.w, t.w.x, t.w.z, t.w.w).det() * -1.0f;
			const float k = mat3(t.x.x, t.x.y, t.x.w, t.y.x, t.y.y, t.y.w, t.w.x, t.w.y, t.w.w).det();
			const float l = mat3(t.x.x, t.x.y, t.x.z, t.y.x, t.y.y, t.y.z, t.w.x, t.w.y, t.w.z).det() * -1.0f;
			const float m = mat3(t.x.y, t.x.z, t.x.w, t.y.y, t.y.z, t.y.w, t.z.y, t.z.z, t.z.w).det() * -1.0f;
			const float n = mat3(t.x.x, t.x.z, t.x.w, t.y.x, t.y.z, t.y.w, t.z.x, t.z.z, t.z.w).det();
			const float o = mat3(t.x.x, t.x.y, t.x.w, t.y.x, t.y.y, t.y.w, t.z.x, t.z.y, t.z.w).det() * -1.0f;
			const float p = mat3(t.x.x, t.x.y, t.x.z, t.y.x, t.y.y, t.y.z, t.z.x, t.z.y, t.z.z).det();

			const mat4 adj = mat4(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p);

			return ((1.0f / determinant) * adj);
		}
		inline mat4 translate(const vec3& translation) {
			return mat4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, translation.x, translation.y, translation.z, 1.0f);
		}
		inline mat4 rotate(const float angle, const vec3& axis) {
			const float cosTheta = std::cos(angle);
			const float oMCT = 1.0f - cosTheta;
			const float sinTheta = std::sin(angle);

			return mat4(cosTheta + ((axis.x * axis.x) * oMCT),
				((axis.y * axis.x) * oMCT) + (axis.z * sinTheta),
				((axis.z * axis.x) * oMCT) - (axis.y * sinTheta),
				0.0f,
				((axis.x * axis.y) * oMCT) - (axis.z * sinTheta),
				cosTheta + ((axis.y * axis.y) * oMCT),
				((axis.z * axis.y) * oMCT) + (axis.x * sinTheta),
				0.0f,
				((axis.x * axis.z) * oMCT) + (axis.y * sinTheta),
				((axis.y * axis.z) * oMCT) - (axis.x * sinTheta),
				cosTheta + ((axis.z * axis.z) * oMCT),
				0.0f,
				0.0f, 0.0f, 0.0f, 1.0f);
		}
		inline mat4 scale(const vec3& scaling) {
			return mat4(scaling.x, 0.0f, 0.0f, 0.0f, 0.0f, scaling.y, 0.0f, 0.0f, 0.0f, 0.0f, scaling.z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		}
		inline mat4 lookAtLH(const vec3& from, const vec3& to, const vec3& up) {
			const vec3 forward = normalize(to - from);
			const vec3 right = normalize(cross(up, forward));
			const vec3 realUp = cross(forward, right);

			return mat4(right.x, realUp.x, forward.x, 0.0,
				right.y, realUp.y, forward.y, 0.0,
				right.z, realUp.z, forward.z, 0.0,
				-dot(right, from), -dot(realUp, from), -dot(forward, from), 1.0);
		}
		inline mat4 lookAtRH(const vec3& from, const vec3& to, const vec3& up) {
			const vec3 forward = normalize(to - from);
			const vec3 right = normalize(cross(forward, up));
			const vec3 realUp = cross(right, forward);

			return mat4(right.x, realUp.x, -forward.x, 0.0f,
				right.y, realUp.y, -forward.y, 0.0f,
				right.z, realUp.z, -forward.z, 0.0f,
				-dot(right, from), -dot(realUp, from), dot(forward, from), 1.0f);
		}
		inline mat4 orthoLH(const float left, const float right, const float bottom, const float top, const float near, const float far) {
			const float rightPlusLeft = right + left;
			const float rightMinusLeft = right - left;
			const float topPlusBottom = top + bottom;
			const float topMinusBottom = top - bottom;
			const float farMinusNear = far - near;

			return mat4(2.0f / rightMinusLeft, 0.0f, 0.0f, 0.0f,
				0.0f, 2.0f / topMinusBottom, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f / farMinusNear, 0.0f,
				-(rightPlusLeft / rightMinusLeft), -(topPlusBottom / topMinusBottom), -near / farMinusNear, 1.0f);
		}
		inline mat4 orthoRH(const float left, const float right, const float bottom, const float top, const float near, const float far) {
			const float rightPlusLeft = right + left;
			const float rightMinusLeft = right - left;
			const float topPlusBottom = top + bottom;
			const float topMinusBottom = top - bottom;
			const float farMinusNear = far - near;

			return mat4(2.0f / rightMinusLeft, 0.0f, 0.0f, 0.0f,
				0.0f, 2.0f / topMinusBottom, 0.0f, 0.0f,
				0.0f, 0.0f, -1.0f / farMinusNear, 0.0f,
				-(rightPlusLeft / rightMinusLeft), -(topPlusBottom / topMinusBottom), -near / farMinusNear, 1.0f);
		}
		inline mat4 perspectiveLH(const float fovY, const float aspectRatio, const float near, const float far) {
			const float tanHalfFovY = std::tan(fovY / 2.0f);
			const float farMinusNear = far - near;

			return mat4(1.0f / (aspectRatio * tanHalfFovY), 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f / tanHalfFovY, 0.0f, 0.0f,
				0.0f, 0.0f, far / farMinusNear, 1.0f,
				0.0f, 0.0f, -(far * near) / farMinusNear, 0.0f);
		}
		inline mat4 perspectiveRH(const float fovY, const float aspectRatio, const float near, const float far) {
			const float tanHalfFovY = std::tan(fovY / 2.0f);
			const float farMinusNear = far - near;
			const float nearMinusFar = near - far;

			return mat4(1.0f / (aspectRatio * tanHalfFovY), 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f / tanHalfFovY, 0.0f, 0.0f,
				0.0f, 0.0f, far / nearMinusFar, -1.0f,
				0.0f, 0.0f, -(far * near) / farMinusNear, 0.0f);
		}

		inline mat4 to_mat4(const quat& qua) {
			const float ab = qua.a * qua.b;
			const float ac = qua.a * qua.c;
			const float ad = qua.a * qua.d;
			const float bb = qua.b * qua.b;
			const float bc = qua.b * qua.c;
			const float bd = qua.b * qua.d;
			const float cc = qua.c * qua.c;
			const float cd = qua.c * qua.d;
			const float dd = qua.d * qua.d;

			return mat4(1.0f - 2.0f * (cc + dd),
				2.0f * (bc + ad),
				2.0f * (bd - ac),
				0.0f,
				2.0f * (bc - ad),
				1.0f - 2.0f * (bb + dd),
				2.0f * (cd + ab),
				0.0f,
				2.0f * (bd + ac),
				2.0f * (cd - ab),
				1.0f - 2.0f * (bb + cc),
				0.0f,
				0.0f, 0.0f, 0.0f, 1.0f);
		}
		inline std::string to_string(const mat4& mat) {
			return ("[" + to_string(mat.x) + ", " + to_string(mat.y) + ", " + to_string(mat.z) + ", " + to_string(mat.w) + "]");
		}

		// quat
		inline quat conjugate(const quat& qua) {
			return quat(qua.a, -qua.b, -qua.c, -qua.d);
		}
		inline quat normalize(const quat& qua) {
			const float l = qua.length();

			return (qua / l);
		}
		inline float dot(const quat& a, const quat& b) {
			return ((a.a * b.a) + (a.b * b.b) + (a.c * b.c) + (a.d * b.d));
		}
		inline quat slerp(const quat& a, const quat& b, const float interpolationValue) {
			quat tmpB = b;

			float aDotb = dot(a, b);

			if (aDotb < 0.0) {
				tmpB = tmpB * -1.0f;
				aDotb = -aDotb;
			}

			if (aDotb > 0.9995) {
				return normalize(a + interpolationValue * (tmpB - a));
			}

			const float theta0 = std::acos(aDotb);
			const float theta = interpolationValue * theta0;
			const float sinTheta0 = std::sin(theta0);
			const float sinTheta = std::sin(theta);

			float scaleA = std::cos(theta) - aDotb * (sinTheta / sinTheta0);
			float scaleB = sinTheta / sinTheta0;

			return (scaleA * a + scaleB * tmpB);
		}

		inline quat to_quat(const vec3& vec) {
			const float cosHalfPhi = std::cos(vec.x / 2.0f);
			const float sinHalfPhi = std::sin(vec.x / 2.0f);
			const float cosHalfTheta = std::cos(vec.y / 2.0f);
			const float sinHalfTheta = std::sin(vec.y / 2.0f);
			const float cosHalfPsi = std::cos(vec.z / 2.0f);
			const float sinHalfPsi = std::sin(vec.z / 2.0f);

			return quat(cosHalfPhi * cosHalfTheta * cosHalfPsi + sinHalfPhi * sinHalfTheta * sinHalfPsi,
				sinHalfPhi * cosHalfTheta * cosHalfPsi - cosHalfPhi * sinHalfTheta * sinHalfPsi,
				cosHalfPhi * sinHalfTheta * cosHalfPsi + sinHalfPhi * cosHalfTheta * sinHalfPsi,
				cosHalfPhi * cosHalfTheta * sinHalfPsi - sinHalfPhi * sinHalfTheta * cosHalfPsi);
		}
		inline std::string to_string(const quat& qua) {
			return std::to_string(qua.a) + " + " + std::to_string(qua.b) + "i + " + std::to_string(qua.c) + "j + " + std::to_string(qua.d) + "k";
		}

	}

}