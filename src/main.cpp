#include <iostream>
#include "../include/libmatrix.hpp"

using namespace libmatrix;

int main(){
    Vector<3,int> v1,v2,v3,v4;
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

    Vector<3,int> *vcross = v1.cross(v2);
    std::cout<<"Vector 1 cross 2 : "<<*vcross<<std::endl;

    float dotProduct = v3.dot(v4);
    std::cout<<"Vector 3 dot 4 : "<<dotProduct<<std::endl;

    float norm = v2.norm();
    std::cout<<"Vector 2 norm: "<<norm<<std::endl;

    Vector<3,int> *vUnit = v2.to_unit();
    std::cout<<"Vector 2 unit: "<<*vUnit<<std::endl;

}