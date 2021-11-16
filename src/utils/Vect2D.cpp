#include "utils/Vect2D.hpp"

#include <cmath>

double Vect2D::get_x() const {return this->x;}
double Vect2D::get_y() const {return this->y;}
double Vect2D::get_magnitude() const {return std::sqrt(this->x*this->x + this->y*this->y);}

void Vect2D::set_x(const double &newX) {this->x = newX;}
void Vect2D::set_y(const double &newY) {this->y = newY;}

double Vect2D::dot(const Vect2D &v) const {
    return this->x*v.x + this->y*v.y;
}

void Vect2D::make_unit() {
    double mag = this->get_magnitude();
    this->x = this->x/mag;
    this->y = this->y/mag;
}