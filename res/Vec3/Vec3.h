#pragma once
#include <cmath>
#include <iostream>
#include <cassert>

namespace msl
{
	class Vec3
	{

	private:

		double x_, y_, z_;

	public:

		constexpr Vec3() noexcept : x_(0.0), y_(0.0), z_(0.0) {}
		constexpr Vec3(const double x_i, const double y_i, const double z_i) noexcept : x_(x_i), y_(y_i), z_(z_i) {}
		constexpr Vec3(const Vec3&) noexcept = default;
		constexpr ~Vec3()           noexcept = default;

		constexpr Vec3  operator+  (const Vec3& rhs)     const noexcept { return Vec3(x_ + rhs.x_, y_ + rhs.y_, z_ + rhs.z_); }
		constexpr Vec3  operator-  (const Vec3& rhs)     const noexcept { return Vec3(x_ - rhs.x_, y_ - rhs.y_, z_ - rhs.z_); }
		Vec3  operator/  (const double scalar) const { if (scalar != 0.0) return Vec3(x_ / scalar, y_ / scalar, z_ / scalar); else throw std::domain_error("Division by zero!"); }
		constexpr Vec3  operator*  (const double scalar) const noexcept { return Vec3(x_ * scalar, y_ * scalar, z_ * scalar); }

		constexpr Vec3& operator+= (const Vec3& rhs)     noexcept { x_ += rhs.x_; y_ += rhs.y_; z_ += rhs.z_; return *this; }
		constexpr Vec3& operator-= (const Vec3& rhs)     noexcept { x_ -= rhs.x_; y_ -= rhs.y_; z_ -= rhs.z_; return *this; }
		constexpr Vec3& operator*= (const double scalar) noexcept { x_ *= scalar; y_ *= scalar; z_ *= scalar; return *this; }
		Vec3& operator/= (const double scalar) { if (scalar != 0.0) { x_ /= scalar; y_ /= scalar; z_ /= scalar; return *this; } else throw std::domain_error("Division by zero!"); }

		constexpr Vec3& operator=  (const Vec3& rhs)       noexcept { x_ = rhs.x_; y_ = rhs.y_; z_ = rhs.z_; return *this; }
		bool  operator== (const Vec3& rhs) const noexcept { return std::abs(x_ - rhs.x_) < 1e-9 && std::abs(y_ - rhs.y_) < 1e-9 && std::abs(z_ - rhs.z_) < 1e-9; }

		constexpr double dot(const Vec3& rhs)   const noexcept { return x_ * rhs.x_ + y_ * rhs.y_ + z_ * rhs.z_; }
		double length()               const noexcept { return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_); }
		constexpr double lengthSqrd()           const noexcept { return x_ * x_ + y_ * y_ + z_ * z_; }
		constexpr Vec3   cross(const Vec3& rhs) const noexcept { return Vec3(y_ * rhs.z_ - z_ * rhs.y_, z_ * rhs.x_ - x_ * rhs.z_, x_ * rhs.y_ - y_ * rhs.x_); }
		Vec3   normalized()           const { double l = length(); if (l != 0.0) return Vec3(x_ / l, y_ / l, z_ / l); else return Vec3(0.0, 0.0, 0.0); }
		Vec3& normalize() { double l = length(); if (l != 0.0) { x_ /= l; y_ /= l; z_ /= l; return *this; } else return *this; }

		constexpr void    setValues(const double x_i, const double y_i, const double z_i) noexcept { x_ = x_i; y_ = y_i; z_ = z_i; }
		constexpr double  x() const noexcept { return x_; }
		constexpr double  y() const noexcept { return y_; }
		constexpr double  z() const noexcept { return z_; }
		constexpr double& x()       noexcept { return x_; }
		constexpr double& y()       noexcept { return y_; }
		constexpr double& z()       noexcept { return z_; }

		friend std::ostream& operator<<(std::ostream& out, const Vec3& v)   noexcept { out << "(" << v.x_ << ", " << v.y_ << ", " << v.z_ << ")"; return out; }
		friend Vec3          operator* (const double scalar, const Vec3& v) noexcept { return Vec3(v.x_ * scalar, v.y_ * scalar, v.z_ * scalar); }

		double& operator[](int i) { if (i < 0 || i > 2) throw std::out_of_range("Index violation!"); if (i == 0) return x_; else if (i == 1) return y_; else return z_; }
		const double& operator[](int i) const { if (i < 0 || i > 2) throw std::out_of_range("Index violation!"); if (i == 0) return x_; else if (i == 1) return y_; else return z_; }
	};
}


