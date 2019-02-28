#pragma once
#include <cmath>

#define M_PI 3.14159265358979356

class Point {
public:
	Point(double x = 0., double y = 0.) :x(x), y(y) {};
	double theta() const {
		double angle = atan2(y, x);
		angle = (angle < 0.0) ? angle + 2 * M_PI : angle;
		return angle;
	}
	double norm2() const {
		return x*x + y*y;
	}
	double x, y;
};
Point operator+(const Point& a, const Point& b) {
	return Point(a.x + b.x, a.y + b.y);
}
Point operator-(const Point& a, const Point& b) {
	return Point(a.x - b.x, a.y - b.y);
}
class StarShaped {
public:
	StarShaped(Point center = Point(0., 0.)) : center(center) {};

	virtual Point x(double t) const = 0;
	virtual Point xp(double t) const = 0;
	virtual Point xpp(double t) const = 0;
	double param(Point p) const {
		return (p - center).theta();
	}
	double curvature(double t) const {
		Point vxp = xp(t);
		Point vxpp = xpp(t);
		return fabs(vxp.x*vxpp.y - vxp.y*vxpp.x) / std::pow(vxp.norm2(), 1.5);
	}

	bool inside(const Point & p) const {
		double xnorm2 = (x(param(p)) - center).norm2();
		double pnorm2 = (p - center).norm2();
		return (xnorm2 > pnorm2);
	}

	Point center;
};

class AccFlower2D : public StarShaped {
public:
	AccFlower2D(Point center, double radius, double smallRadius, unsigned int k, double phi)
		: StarShaped(center), radius(radius), smallRadius(smallRadius), k(k), phi(phi) {
		kp = 2 * k / (M_PI * M_PI);
	}
	Point x(double t) const {
		while (t >= M_PI) t -= 2 * M_PI;
		while (t < -M_PI) t += 2 * M_PI;
		double ktn = kp * t * t * t;
		double r = radius + smallRadius * cos(ktn);
		return Point(r * cos(t) + center.x, r * sin(t) + center.y);
	}
	Point xp(double t) const {
		while (t >= M_PI) t -= 2 * M_PI;
		while (t < -M_PI) t += 2 * M_PI;

		double ktn = kp * t * t * t;
		double ktnp = 3 * kp * t * t;

		double r = radius + smallRadius * cos(ktn);
		double rp = -smallRadius * sin(ktn) * ktnp;

		return Point(rp * cos(t) - r * sin(t), rp * sin(t) + r * cos(t));
	}
	Point xpp(double t) const {
		while (t >= M_PI) t -= 2 * M_PI;
		while (t < -M_PI) t += 2 * M_PI;

		double ktn = kp * t * t * t;
		double ktnp = 3 * kp * t * t;
		double ktnpp = 6 * kp * t;

		double r = radius + smallRadius * cos(ktn);
		double rp = -smallRadius * sin(ktn) * ktnp;
		double rpp = -smallRadius * cos(ktn) * ktnp * ktnp - smallRadius * sin(ktn) * ktnpp;

		return Point(rpp * cos(t) - 2 * rp * sin(t) - r * cos(t), rpp * sin(t) + 2 * rp * cos(t) - r * sin(t));
	}
	double radius, smallRadius, phi, kp;
	unsigned int k;
};

class Flower : public StarShaped {
public:
	Flower(Point center, double radius, double varRadius, unsigned int k, double phi)
		: StarShaped(center), radius(radius), varRadius(varRadius), k(k), phi(phi) {}

	Point x(double t) const {
		double r = radius + varRadius*cos(k*t + phi);
		return Point(r*cos(t) + center.x, r*sin(t) + center.y);
	}
	Point xp(double t) const {
		double r = radius + varRadius*cos(k*t + phi);
		double rp = -varRadius * sin(k * t + phi) * k;
		return Point(rp*cos(t) - r*sin(t), rp*sin(t) + r*cos(t));
	}
	Point xpp(double t) const {
		double r = radius + varRadius*cos(k*t + phi);
		double rp = -varRadius * sin(k * t + phi) * k;
		double rpp = -varRadius * cos(k * t + phi) * k * k;

		return Point(rpp * cos(t) - 2 * rp * sin(t) - r * cos(t), rpp * sin(t) + 2 * rp * cos(t) - r * sin(t));
	}
	double radius, varRadius, phi;
	int k;
};