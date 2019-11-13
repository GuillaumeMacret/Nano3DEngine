#include <iostream>

namespace libmatrix{

    template <int N, typename T>
    class Vector{
        private:
            T *tab;
        public:
            Vector(){
                tab = new T[N];
            }
            ~Vector(){
                delete [] tab;
            }
            /**
             * Sets the index i at the val val
             **/
            void set(int i, T val){
                if(i < 0 || i > N){
                    throw std::string("Index out of range");
                }else{
                    tab[i] = val;
                }
            }

            /**
             * addresses the i-th element (i is give as an argument) of the vector
             **/
            T at(int i){
                if(i < 0 || i > N){
                    throw std::string("Index out of range");
                }else{
                    return tab[i];
                }
            }

            /**
             * cross product with another vector (given as an argument). Uses only the first 3 coordinates. Raises an exception if the vector has less than 3 elements
            **/
            Vector<N, T>* cross(Vector<N,T> &other){
                if(N < 3){
                    throw std::string("Too few arguments to do cross product");
                }else{
                    Vector<3,T> *crossVec = new Vector<3,T>;
                    crossVec->set(0,tab[1] * other.at(2) - tab[2] * other.at(1));
                    crossVec->set(1, tab[2] * other.at(0) - tab[0] * other.at(2));
                    crossVec->set(2, tab[0] * other.at(1) - tab[1] * other.at(0));

                    return crossVec;
                }
            }

            /**
             * dot product with another vector (give as an argument)
             **/
            float dot();

            /**
             * returns true if the vector is orthogonal to another given as an argument, false otherwise
             **/
            bool is_ortho();

            /**
             * returns true if the vector contains an invalid value, false otherwise. Notably, if the vector contains nan as values.
            **/
            bool is_null();

            /**
             * returns true if the vector is unit, false otherwise
             **/
            bool is_unit();
            
            /**
             * returns the norm of the vector
             **/
            Vector<N, T> norm();

            /**
             * Returns a copy of the vector normalised
             **/
            Vector<N, T> to_unit();
            
            friend std::ostream &operator<<(std::ostream &s,const Vector &vec){
                s<<"[";
                for(int i = 0; i < N; ++i){
                    s<<(i==0?"":" ")<<vec.tab[i];
                }
                s<<"]";
                return s;
            }
    };
}