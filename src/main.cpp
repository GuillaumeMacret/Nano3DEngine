#include <iostream>
#include "../include/libmatrix.hpp"
#include "../include/libgeometry.hpp"
//#include "scene.hpp"

using namespace libmatrix;
using namespace libgeometry;

int main(){
    // libmatrix test
    {
        Vector<3,double> v1,v2,v3,v4;
        v1.set(0,2);
        v1.set(1,1);
        v1.set(2,1);
        v2.set(0,2);
        v2.set(1,0);
        v2.set(2,0);

        v3.set(0,0);
        v3.set(1,0);
        v3.set(2,1);
        v4.set(0,1);
        v4.set(1,0);
        v4.set(2,0);

        std::cout<<"Vector 1 : " <<v1<<std::endl;
        std::cout<<"Vector 2 : " <<v2<<std::endl;
        std::cout<<"-Vector 2 : " <<-v2<<std::endl;

        Vector<3,double> *vcross = v1.cross(v2);
        std::cout<<"Vector 1 cross 2 : "<<*vcross<<std::endl;

        double dotProduct = v3.dot(v4);
        std::cout<<"Vector 3 dot 4 : "<<dotProduct<<std::endl;

        double norm = v2.norm();
        std::cout<<"Vector 2 norm: "<<norm<<std::endl;

        Vector<3,double> *vUnit = v2.to_unit();
        std::cout<<"Vector 2 unit: "<<*vUnit<<std::endl;

        Vector<3,double> vAdd = v1 + v2;
        std::cout<<"Vector 1 + 2 (+) : "<<vAdd<<std::endl;

        v1 += v2;
        std::cout<<"Vector 1 + 2 (+=) : "<<v1<<std::endl;


        Matrix<3,3,double> mat1;
        mat1.init();
        std::cout<<mat1<<std::endl;
        mat1.setIdentity();
        std::cout<<mat1<<std::endl;

        mat1[0][0] = 2;
        mat1[0][1] = 3;
        mat1[0][2] = 8;

        mat1[1][0] = 6;
        mat1[1][1] = 0;
        mat1[1][2] = -3;

        mat1[2][0] = -1;
        mat1[2][1] = 3;
        mat1[2][2] = 2;

        mat1.inverse();

        Vec2i zero = zerovec2i;

        // std::cout << mat1 << std::endl;
        // std::cout << *mat1.transpose() << std::endl;
        // std::cout << (mat1 == mat1) << " " << (mat1 == *mat1.transpose())<<std::endl;
        // std::cout << (mat1 + *mat1.transpose())<<std::endl;
        // mat1+= *mat1.transpose();
        // std::cout << mat1 <<std::endl;
        // std::cout << mat1 * v1<<std::endl;
        // std::cout << mat1 * mat1<<std::endl;
    }

    //libGeo test
    {
        Direction<3,double> xDir;
        xDir[0] = 1;
        std::cout<<"Direction : "<<xDir<<std::endl;
        Point<3,double> p1, p2;
        p1[0] = 1;
        p1[1] = 0;
        p1[2] = 0;
        std::cout<<"Points : "<<p1<<" "<<p2<<std::endl;
        Direction<3,double> distance = p1.length_to(p2);
        std::cout<<"Distance between those two : "<<distance<<std::endl;
        
        Quaternion<double> q(3.0, 1.0, 3.0), q2(1,2,3,4);
        std::cout<<"Quaternion : "<<q<<" Im part : " << q.im()<<std::endl;
        std::cout<<"Quaternion conjuge : "<<q.conjugate()<<std::endl;
        std::cout<<"Quaternion norm : "<<q.norm()<<std::endl;
        q2+=q2;
        std::cout<<"Sum+= : "<<q2<<std::endl;

        std::cout<<"Prod : "<<q2 * q2<<std::endl;
        
        LineSegment<4,double> seg1(Vector3r(0,0,0), Vector3r(1,1,1));
        std::cout<<"Segment : "<< seg1<<std::endl;

        Plane<4,double> plane1(0,1,0,0);
        std::cout<<"Plane"<<plane1<<std::endl;

        std::cout<<"Plane & seg intersect : " <<*seg1.inter(plane1)<<std::endl;

        Sphere<3,double> s1(p2,1);
        std::cout<<"Sphere : "<<s1<<std::endl;

        Point<3,double> p3;
        p3[0] = 0;
        p3[1] = 1;
        p3[2] = 0;
        Triangle t1(p1,p2,p3);
        std::cout<<"Triangle : "<<t1<<std::endl;

        Point<3,double> p4;
        p4[0] = 1;
        p4[1] = 1;
        p4[2] = 0;
        Rectangle r1(p1,p2,p3,p4);
        std::cout<<"Rectangle : "<<r1<<std::endl;

        Transform trans1(Vector3r(1,1,1)), trans2(Vector4r(1,1,1,1));
        std::cout<<"Transform1 : "<<trans1<<std::endl;
        std::cout<<"Transform2 : "<<trans2<<std::endl;

        Transform trans3 = trans1.concat(trans2);
        std::cout<<"Transform1+2 : "<<trans3<<std::endl;

        std::cout<<xDir<<std::endl;
        Quaternion<double> q3(30,xDir);
        std::cout<<"Quaternion : "<<q3<<std::endl;
        Transform trans4(q3);


    }

    //////////////////////////////////////////////////////////////

}