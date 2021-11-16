#pragma once

class Vect2D {
    private:
        double x;
        double y;
    
    public:
        Vect2D()                  : x(0),                      y(0)                      {}
        Vect2D(double x, double y): x(x),                      y(y)                      {}
        Vect2D(const Vect2D &obj) : x(obj.x),                  y(obj.y)                  {}

        Vect2D(const Vect2D &pointA, const Vect2D &pointB): x(pointB.x-pointA.x), y(pointB.y-pointA.y) {}

        double get_x() const;
        double get_y() const;
        double get_magnitude() const;

        void set_x(const double &newX);
        void set_y(const double &newY);

        double dot(const Vect2D &v) const;

        void make_unit();
};