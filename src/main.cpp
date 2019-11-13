#include <iostream>
#include "../include/libmatrix.hpp"

using namespace libmatrix;

int main(){
    Vector<3,int> v1;
    v1.set(0,1);
    v1.set(1,2);
    v1.set(2,3);
    int a = v1.at(2);
    std::cout<<a<<std::endl;
    std::cout<<v1<<std::endl;
    Vector<3,int> *vcross = v1.cross(v1);
    std::cout<<*vcross<<std::endl;
}