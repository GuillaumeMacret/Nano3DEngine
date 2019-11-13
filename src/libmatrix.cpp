#include "../include/libmatrix.hpp"

// using namespace libmatrix;

// template <int N, typename T>
// Vector<N, T>::Vector(){
//     tab = new T[N];
// }

// template <int N, typename T>
// Vector<N, T>::~Vector(){
//     delete [] tab;
// }

// template <int N, typename T>
// void Vector<N, T>::set(int i, T val){
//     if(i < 0 || i > N){
//         throw std::string("Index out of range");
//     }else{
//         tab[i] = val;
//     }
// }

// template <int N, typename T>
// T Vector<N, T>::at(int i){
//     if(i < 0 || i > N){
//         throw std::string("Index out of range");
//     }else{
//         return tab[i];
//     }
// }

// template <int N, typename T>
// Vector<N,T>* Vector<N,T>::cross(Vector<N,T> &other){
//     if(N < 3){
//         throw std::string("Too few arguments to do cross product");
//     }else{
//         Vector<3,T> *crossVec = new Vector<3,T>;
//         crossVec->set(0,tab[1] * other.at(2) - tab[2] * other.at(1));
//         crossVec->set(1, tab[2] * other.at(0) - tab[0] * other.at(2));
//         crossVec->set(2, tab[0] * other.at(1) - tab[1] * other.at(0));

//         return crossVec;
//     }
// }