#ifndef LIBGEOMETRYH
#define LIBGEOMETRYH

#include "libmatrix.hpp"

using namespace libmatrix;

namespace libgeometry{
    template<int N, typename T>
    class Direction{
        private:
            Vector<N,T> dir;
        public:
            Direction(){
                for(int i = 0; i < N; ++i){
                    dir[i] = 0;
                }
            }

            T at(int i){
                return dir.at(i);
            }

            bool is_null(){
                return dir.is_null();
            }

            T& operator[](int i) { return dir[i]; }

            friend std::ostream& operator<<(std::ostream& s, const Direction &d) {
                s<<d.dir;
                return s;
            }
    };

    template <int N, typename T>
    class Plane;

    template <int N,typename T>
    class Sphere;

    template <typename T>
    class Quaternion{
        private:
            Vector<4,T> vector;
        public:
            //constructs a quaternion corresponding to the rotation defined by the angle (in degrees) and the axis (class Direction) given as arguments.
            //TODO test
            Quaternion(float angle, Direction<3,T> axis){
                Quaternion(angle * axis[0], angle * axis[1], angle * axis[2]);
            }

            Quaternion(double yaw, double pitch, double roll){// yaw (Z), pitch (Y), roll (X)
                // Abbreviations for the various angular functions
                double cy = cos(yaw * 0.5);
                double sy = sin(yaw * 0.5);
                double cp = cos(pitch * 0.5);
                double sp = sin(pitch * 0.5);
                double cr = cos(roll * 0.5);
                double sr = sin(roll * 0.5);

                vector[0] = cy * cp * cr + sy * sp * sr;
                vector[1] = cy * cp * sr - sy * sp * cr;
                vector[2] = sy * cp * sr + cy * sp * cr;
                vector[3] = sy * cp * cr - cy * sp * sr;
            }

            Quaternion(T w, T x, T y, T z){
                vector[0] = w;
                vector[1] = x;
                vector[2] = y;
                vector[3] = z;
            }

            Quaternion(T realPart, Vector3r imPart){
                Quaternion(realPart, imPart[0], imPart[1], imPart[2], imPart[3]);
            }

            //Returns the conjugate
            //TODO
            Quaternion conjugate(){
                return nullptr;
            }

            //Returns the norm
            //TODO
            T norm(){
                return nullptr;
            }

            //Returns the imaginary part
            Vector3r im(){
                return Vector3r(vector[1],vector[2],vector[3]);
            }

            //Returns the inverse
            //TODO
            Quaternion inverse(){
                return nullptr;
            }

            //Return the real part
            T re(){
                return vector[0];
            }

            //Returns a nomalised copy of the quaternion
            //TODO
            Quaternion to_norm(){

            }

            Quaternion<T> operator+(Quaternion<T> &q){
                return Quaternion(q[0] + vector[0], q[1] + vector[1],q[2] + vector[2],q[3] + vector[3]);
            }

            void operator+=(Quaternion<T> &q){
                vector[0] += q[0];
                vector[1] += q[1];
                vector[2] += q[2];
                vector[3] += q[3];
            }

            //TODO
            Quaternion<T> operator*(Quaternion<T> &q){
                /*
                T realPart = re() * q.re() - (im().dot(q.im()));
                Vector3r imPart = im();
                return Quaternion(realPart, imPart);
                */
            }

            //TODO operators -, -=, *, *=

            T& operator[](int i){
                return vector[i];
            }

            friend std::ostream& operator<<(std::ostream& s, const Quaternion &q){
                s<<q.vector;
                return s;
            }
    };

    template <int N, typename T>
    class Point{
        private:
            Vector<N,T> vec;
        public:
            Point(){
                for(int i = 0; i < N; ++i){
                    vec[i] = 0;
                }
            }

            //TODO test
            bool behind(Plane<N,T> plane){
                Vector<N,T> *unitDir = plane.vector.to_unit();
                float x = unitDir->dot(vec) + plane.point;
                return x < 0;
            }

            bool is_null(){
                return vec.is_null();
            }

            //returns a direction (class Direction below) representing the vector between the point and another point given as argument.
            Direction<N,T> length_to(Point<N,T> &point){
                Direction<N,T> dir;
                for(int i = 0; i < N; ++i){
                    dir[i] = /*abs(*/point.at(i) - at(i)/*)*/;
                }
                return dir;
            }

            //Returns true if the point is inside a sphere
            //TODO test
            bool outside(Sphere<N,T> sphere){
                Direction<N,T> dist = length_to(sphere.center);
                for(int i = 0; i < N; ++i){
                    if(dist[i] > sphere.radius)return false;
                }
                return true;
            }
            //returns a new point corresponding to the rotation of the point by the quaternion given as argument.
            //TODO
            Point rotate(Quaternion<T> quat){

            }

            friend std::ostream& operator<<(std::ostream& s, const Point &p) {
                s<<p.vec;
                return s;
            }

            T& operator[](int i){return vec[i];}
            T at(int i){
                return vec.at(i);
            }
    };

    template <int N, typename T>
    class Sphere{
        Point<N,T> center;
        T radius;
    };

    template <int N, typename T>
    class Plane{
        private:
        public:
            Point <N,T> point;
            Vector<N,T> vector;
            //Returns true if the plane contains an invalid value, false otherwise
            bool is_null(){
                //TODO
                return nullptr;
            }
    };
} //namespace libgeometry
#endif