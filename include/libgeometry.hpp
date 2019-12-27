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

/*********************************************************************************/
/*
    template <typename T>
    class Quaternion{
        private:
            T angle;
            Direction<T> axis;
        
        public:
            Quaternion();

            //constructs a quaternion corresponding to the rotation defined by the angle (in degrees) and the axis (class Direction) given as arguments.
            Quaternion(T angle, Direction<T> &axis):angle(angle),axis(axis){
                
            }

            //Returns the conjugate of the quaternion
            Quaternion *conjugate(){
                Quaternion q = new Quaternion(angle,-axis);
                return q;                
            }

        friend std::ostream& operator<<(std::ostream& s, const Quaternion &q) {
            s<<"<"<<q.angle<<","<<q.axis<<">";
            return s;
        }
    };
*/
} //namespace libgeometry
#endif