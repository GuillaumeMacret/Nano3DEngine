#include <iostream>
#include "../include/libmatrix.hpp"
#include "../include/libgeometry.hpp"

using namespace libmatrix;
using namespace libgeometry;

int main(){
    // libmatrix test
    {
        Vector<3,float> v1,v2,v3,v4;
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

        Vector<3,float> *vcross = v1.cross(v2);
        std::cout<<"Vector 1 cross 2 : "<<*vcross<<std::endl;

        float dotProduct = v3.dot(v4);
        std::cout<<"Vector 3 dot 4 : "<<dotProduct<<std::endl;

        float norm = v2.norm();
        std::cout<<"Vector 2 norm: "<<norm<<std::endl;

        Vector<3,float> *vUnit = v2.to_unit();
        std::cout<<"Vector 2 unit: "<<*vUnit<<std::endl;

        Vector<3,float> vAdd = v1 + v2;
        std::cout<<"Vector 1 + 2 (+) : "<<vAdd<<std::endl;

        v1 += v2;
        std::cout<<"Vector 1 + 2 (+=) : "<<v1<<std::endl;


        Matrix<3,3,float> mat1;
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

        Vector2i zero = zerovec2i;

        // std::cout << mat1 << std::endl;
        // std::cout << *mat1.transpose() << std::endl;
        // std::cout << (mat1 == mat1) << " " << (mat1 == *mat1.transpose())<<std::endl;
        // std::cout << (mat1 + *mat1.transpose())<<std::endl;
        // mat1+= *mat1.transpose();
        // std::cout << mat1 <<std::endl;
        // std::cout << mat1 * v1<<std::endl;
        // std::cout << mat1 * mat1<<std::endl;
    }


    
    Direction<3,float> xDir;
    xDir[0] = 1;
    std::cout<<"Direction : "<<xDir<<std::endl;
    Point<3,float> p1, p2;
    p1[0] = 1;
    p1[1] = 3;
    p1[2] = 1;
    std::cout<<"Points : "<<p1<<" "<<p2<<std::endl;
    Direction<3,float> distance = p1.length_to(p2);
    std::cout<<"Distance between those two : "<<distance<<std::endl;
    Quaternion<double> q(3.0, 1.0, 3.0), q2(1,2,3,4);
    std::cout<<"Quaternion : "<<q<<" Im part : " << q.im()<<std::endl;
    q2+=q2;
    std::cout<<"Sum : "<<q2<<std::endl;

    std::cout<<"Prod : "<<q2 * q2<<std::endl;
    /*
    Quaternion<float> q1(45.0f,xDir);
    std::cout<<q1<<std::endl;
    */
}