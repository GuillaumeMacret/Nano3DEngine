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
            Quaternion(){}

            //constructs a quaternion corresponding to the rotation defined by the angle (in degrees) and the axis (class Direction) given as arguments.
            //TODO test
            Quaternion(double angle, Direction<3,T> &axis){
                double yaw = angle * axis[0], pitch = angle * axis[1], roll = angle * axis[2];
                //Quaternion(angle * axis[0], angle * axis[1], angle * axis[2]);

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
            Quaternion conjugate(){
                return Quaternion(vector[0],-vector[1],-vector[2], -vector[3]);
            }

            //Returns the norm
            T norm(){
                T norm = 0;
                for(int i = 0; i < 4; ++i){
                    norm += vector[i] * vector[i];
                }
                return std::sqrt(norm);
            }

            //TODO
            Quaternion inverse(){
                T bottom = norm() * norm();
                return std::move(conjugate() * (1/bottom));
            }

            //Returns the imaginary part
            Vector3r im(){
                return Vector3r(vector[1],vector[2],vector[3]);
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

            Quaternion<T> operator*(double scalar){
                return std::move(Quaternion(vector[0] * scalar, vector[1] * scalar, vector[2] * scalar, vector[3] * scalar));
            }

            //TODO test
            Quaternion<T> operator*(Quaternion<T> &q){
                T s1 = re(), s2 = q.re();
                Vector3r v1 = im(), v2 = q.im();
                T realPart = s1*s2 - (v1.dot(v2));

                Vector3r prod = v1*v2;
                Vector3r p1 = v2 * s1, p2 = v1 * s2;
                Vector<3,double> imPart = p1 + p2 + prod;
                return std::move(Quaternion(realPart, imPart[0],imPart[1],imPart[2]));
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
        public:
            Vector<N,T> vec;

            Point(){
                for(int i = 0; i < N; ++i){
                    vec[i] = 0;
                }
            }

            Point(T tab[N]){
                for(int i = 0; i < N; ++i){
                    vec[i] = tab[i];
                }
            }

            Point(Vector<N,T> &v){
                for(int i = 0; i < N; ++i){
                    vec[i] = v[i];
                }
            }

            Point(Point<N,T> &p){
                for(int i = 0; i < N; ++i){
                    vec[i] = p[i];
                }
            }

            //TODO test
            bool behind(Plane<N,T> plane){
                Vector<N,T> *unitDir = plane.vector.to_unit();
                double x = unitDir->dot(vec) + plane.point;
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
            bool outside(Sphere<N,T> &sphere){
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

            Point<N,T> operator*(T &scalar){
                return Point<N,T>(vec * scalar);
            }

            Point<N,T> operator+(Point<N,T> &p){
                return Point<N,T>(vec + p.vec);
            }

            void operator=(Point<N,T> &p){
                vec = p.vec;
            }
    };

    template <int N, typename T>
    class Sphere{
        public:
            Point<N,T> center;
            T radius;

            Sphere(Point<N,T> &center, T radius):center(center), radius(radius){}

            //Returns trus if the sphere is behing a plane given as argument
            //TODO
            bool behind(Plane<N,T> plane){
                return center.behind(plane);
            }

            bool is_null(){
                return center.is_null() || std::isnan(radius);
            }

            friend std::ostream &operator<<(std::ostream &s, Sphere &sphere){
                s<<"Center : "<<sphere.center<<"; Radius : "<<sphere.radius;
                return s;
            }
    };

    template <int N, typename T>
    class Plane{
        private:
        public:
            Vector4r vector;

            Plane(){}
            
            Plane(T a, T b, T c, T d){
                vector[0] = a;
                vector[1] = b;
                vector[2] = c;
                vector[3] = d;
            }
            
            //Returns true if the plane contains an invalid value, false otherwise
            bool is_null(){
                return vector.is_null();
            }

            friend std::ostream& operator<<(std::ostream& s, const Plane& p){
                s<<p.vector;
                return s;
            }
    };

    template <int N, typename T>
    class LineSegment{
        private:
            Point <4,T> begin, end;
        public:
            LineSegment(Vector3r b, Vector3r e){
                begin[0] = b[0];
                end[0] = e[0];
                begin[1] = b[1];
                end[1] = e[1];
                begin[2] = b[2];
                end[2] = e[2];
                begin[3] = 0;
                end[3] = 1;
            }

            Point<N,T> get_begin(){return begin;}
            Point<N,T> get_end(){return end;}

            //returns the coefficient of intersection between the segment and a plane
            //The coefficient of intersection determines if the line whose the segment belongs is in front, behind or lies on the plane
            //TODO
            T inter_coef(Plane<N,T> &plane){
                
            }

            // returns the intersection point between the segment and the plane
            //TODO test deeper & change pointer to ref
            Point<N,T> *inter(Plane<N,T> &p){
                double upper = p.vector.dot(begin.vec);
                double lower = p.vector.dot(end.vec);
                if(lower == 0){
                    std::cerr<<"Error divided by 0"<<std::endl;
                    throw std::string("Divided by 0 in intersection calculations");
                }else{
                    double coef = -upper/lower;
                    auto r = end.vec * coef;
                    r += begin.vec;

                    Point<N,T> *lePoint = new Point<N,T>(r);
                    return lePoint;
                }
            }

            bool is_null(){
                return begin.is_null() || end.is_null();
            }

            friend std::ostream& operator<<(std::ostream& s, const LineSegment& seg) {
                s<<"Begin : "<<seg.begin<<"; End : "<<seg.end;
                return s;
            }
    };

    class Triangle{
        public:
            Point<3,double> p0,p1,p2;
            Point<3,double> get_p0(){return p0;}
            Point<3,double> get_p1(){return p1;}
            Point<3,double> get_p2(){return p2;}

            Triangle(Point<3,double>p0, Point<3,double>p1, Point<3,double>p2):p0(p0),p1(p1),p2(p2){}

            void operator=(Triangle &&tr){
                p0 = tr.p0;
                p1 = tr.p1;
                p2 = tr.p2;
            }

            //Returns the area of the triangle
            //TODO
            void area(){

            }

            bool is_null(){
                return p0.is_null() || p1.is_null() || p2.is_null();
            }

            friend std::ostream& operator<<(std::ostream& s, const Triangle &t){
                s<<"P0 : " << t.p0 <<"; P1 : "<<t.p1<<"; P2 : "<<t.p2;
                return s;
            }
    };

    class Rectangle{
        public:
            Point<3,double> p0,p1,p2,p3;
            
            Rectangle(Point<3,double>p0, Point<3,double>p1, Point<3,double>p2, Point<3,double>p3):p0(p0),p1(p1),p2(p2),p3(p3){}

            bool is_null(){
                return p0.is_null() || p1.is_null() || p2.is_null() || p3.is_null();
            }

            friend std::ostream& operator<<(std::ostream& s, const Rectangle t){
                s<<"P0 : " << t.p0 <<"; P1 : "<<t.p1<<"; P2 : "<<t.p2<<"; P3 : "<<t.p3;
                return s;
            }
    };

    class Transform{
        public:
            Vector4r translation;
            Mat33r matrix;

            Transform(Matrix<3,3,double> m, Vector<4,double> t){
                for(int i = 0; i < 3; ++i){
                    translation[i] = t[i];
                    for(int j = 0; j < 3; ++j){
                        matrix[i][j] = m[i][j];
                    }
                }
                translation[3] = t[3];
            }

            Transform(Vector4r t){
                for(int i = 0; i < 4; ++i){
                    translation[i]  = t[i];
                }
            }

            Transform(Vector3r scale){
                for(int i = 0; i < 3; ++i){
                    matrix[i][i] = scale[i];
                }
            }

            Transform(Quaternion<double>& quat){
                //TODOtest
                double w = quat[0], x = quat[1], y = quat[2], z = quat[3];

                matrix[0][0] = 1 - 2 * (y*y) - 2 * (z*z);
                matrix[0][1] = 2 * x * y - 2 * w * z;
                matrix[0][2] = 2 *x * z + 2 * w * y;
                matrix[1][0] = 2 * x * y + 2 * w * z;
                matrix[1][1] = 1 - 2 * x * x - 2 * z * z;
                matrix[1][2] = 2 * y * z - 2 * w * x;
                matrix[2][0] = 2 * x * z - 2 * w * y;
                matrix[2][1] = 2 * y * z + 2 * w * x;
                matrix[2][2] = 1 - 2 * x * x - 2 * y * y;
            }

            //TODO test
            Transform(double angle, Direction<3, double> &axis){
                Quaternion<double> quat(angle, axis);

                double w = quat[0], x = quat[1], y = quat[2], z = quat[3];

                matrix[0][0] = 1 - 2 * (y*y) - 2 * (z*z);
                matrix[0][1] = 2 * x * y - 2 * w * z;
                matrix[0][2] = 2 *x * z + 2 * w * y;
                matrix[1][0] = 2 * x * y + 2 * w * z;
                matrix[1][1] = 1 - 2 * x * x - 2 * z * z;
                matrix[1][2] = 2 * y * z - 2 * w * x;
                matrix[2][0] = 2 * x * z - 2 * w * y;
                matrix[2][1] = 2 * y * z + 2 * w * x;
                matrix[2][2] = 1 - 2 * x * x - 2 * y * y;
            }

            //TODO test
            Transform concat(Transform &tr){
                return Transform(matrix + tr.matrix,translation + tr.translation);
            }

            //TODO
            // returns the quaternion corresponding to a rotation stored in the transform
            Quaternion<double> to_quat(){

            }

            //todo
            Point<3,double> apply(Point<3,double> point){

            }

            friend std::ostream& operator<<(std::ostream& s, const Transform &t){
                s<<"Translation : "<<t.translation<< "; Rotation & scale : "<<t.matrix;
                return s;
            }
    };

} //namespace libgeometry
#endif