#ifndef LIBMATRIXH
#define LIBMATRIXH

#include <cmath>
#include <iostream>

namespace libmatrix {

template <int N, typename T>
class Vector {
 private:
  T* tab;

 public:
  Vector() { 
    tab = new T[N]; 
    for(int i = 0; i < N; ++i){
      tab[i] = 0;
    }
  }
  
  Vector(Vector<N, T>&& vec) : tab(vec.tab) { vec.tab = nullptr; }
  
  Vector(T inTab[N]){
    tab = new T[N];
    for(int i = 0; i < N; ++i){
      tab[i] = inTab[i];
    }
  }

  ~Vector() { delete[] tab; }
  /**
   * Sets the index i at the val val
   **/
  void set(int i, T val) {
    if (i < 0 || i > N) {
      throw std::string("Index out of range");
    } else {
      tab[i] = val;
    }
  }

  /**
   * addresses the i-th element (i is give as an argument) of the vector
   **/
  T at(int i) {
    if (i < 0 || i > N) {
      throw std::string("Index out of range");
    } else {
      return tab[i];
    }
  }

  /**
   * cross product with another vector (given as an argument). Uses only the
   *first 3 coordinates. Raises an exception if the vector has less than 3
   *elements
   **/
  Vector<N, T>* cross(Vector<N, T>& other) {
    if (N < 3) {
      throw std::string("Too few arguments to do cross product");
    } else {
      Vector<3, T>* crossVec = new Vector<3, T>();
      crossVec->set(0, tab[1] * other.at(2) - tab[2] * other.at(1));
      crossVec->set(1, tab[2] * other.at(0) - tab[0] * other.at(2));
      crossVec->set(2, tab[0] * other.at(1) - tab[1] * other.at(0));

      return crossVec;
    }
  }

  /**
   * dot product with another vector (give as an argument)
   **/
  float dot(Vector<N, T>& other) {
    float sum = 0;
    for (int i = 0; i < N; ++i) {
      sum += tab[i] * other.at(i);
    }
    return sum;
  }

  /**
   * returns true if the vector is orthogonal to another given as an argument,
   *false otherwise
   **/
  bool is_ortho(Vector<N, T>& other) { return dot(other) == 0; }

  /**
   * returns true if the vector contains an invalid value, false otherwise.
   * Notably, if the vector contains nan as values.
   * TODO
   **/
  bool is_null();

  /**
   * returns true if the vector is unit, false otherwise
   **/
  bool is_unit() { return norm() == 1; }

  /**
   * returns the norm of the vector
   **/
  float norm() {
    float squareSum = 0;
    for (int i = 0; i < N; ++i) {
      squareSum += tab[i] * tab[i];
    }
    return std::sqrt(squareSum);
  }

  /**
   * Returns a copy of the vector normalised
   **/
  Vector<N, T>* to_unit() {
    Vector<N, T>* unit = new Vector<N, T>;
    float invNorm = 1 / norm();
    for (int i = 0; i < N; ++i) {
      unit->set(i, invNorm * tab[i]);
    }
    return unit;
  }

  friend std::ostream& operator<<(std::ostream& s, const Vector& vec) {
    s << "[";
    for (int i = 0; i < N; ++i) {
      s << (i == 0 ? "" : " ") << vec.tab[i];
    }
    s << "]";
    return s;
  }

  T& operator[](int i) { return tab[i]; }

  Vector<N, T> operator+(Vector<N, T>& other) {
    Vector<N, T> sumVec;
    for (int i = 0; i < N; ++i) {
      sumVec[i] = tab[i] + other[i];
    }
    return sumVec;
  }

  void operator+=(Vector<N, T>& other) {
    for (int i = 0; i < N; ++i) {
      tab[i] += other[i];
    }
  }

  void operator-=(Vector<N, T>& other) {
    for (int i = 0; i < N; ++i) {
      tab[i] -= other[i];
    }
  }

  Vector<N, T> operator-(Vector<N, T>& other) {
    Vector<N, T> difVec;
    for (int i = 0; i < N; ++i) {
      difVec[i] = tab[i] - other[i];
    }
    return difVec;
  }

  Vector<N, T> operator-() {
    T invTab[N];
    for (int i = 0; i < N; ++i) {
      invTab[i] = tab[i] * -1;
    }
    return std::move(Vector(invTab));
  }

  Vector<N, T> operator*(float scalar) {
    Vector<N, T> vec;
    for (int i = 0; i < N; ++i) {
      vec[i] = tab[i] * scalar;
    }
    return vec;
  }

//   template <int M>
//   Vector<N, T> operator*(Matrix<N, M, T> mat) {
//     // TODO
//   }
};

class Vector2i : public Vector<2,int>{};
class Vector3i : public Vector<3,int>{};
class Vector4i : public Vector<4,int>{};
class Vector2r : public Vector<2,float>{};
class Vector3r : public Vector<3,float>{};


/************************************************************************************************/

template <int N, int M, typename T>
class Matrix {
 private:
  T mat[N][M];

 public:
  Matrix() { init(); }

  void init() {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) {
        mat[i][j] = 0;
      }
    }
  }

  void setIdentity() {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) {
        if (i != j) {
          mat[i][j] = 0;
        } else {
          mat[i][j] = 1;
        }
      }
    }
  }

  T at(int i, int j) {
    if (i < 0 || i > N || j < 0 || j > M) {
      throw std::string("Index out of range");
    } else {
      return mat[i][j];
    }
  }

  /*FIXME*/
  Matrix<N, M, T>* inverse() {
    Matrix<N, M, T>* inverseMat = new Matrix<N, M, T>;
    Matrix<N, M, T> identity;
    identity.setIdentity();
    inverseMat->init();
    if (N != M) {
      return inverseMat;
    } else {
      T matDouble[N][N * 2];
      for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N * 2; ++j) {
          if (j < N) {
            matDouble[i][j] = mat[i][j];
          } else if (j % N == i) {
            matDouble[i][j] = 1;
          } else {
            matDouble[i][j] = 0;
          }
        }
      }

      /* Pivot */
      // for each column j of M'
      for (int j = 0; j < N; ++j) {
        T maxValue = 0;
        int maxIndex = -1;
        // Find best line
        for (int i = 0; i < N; ++i) {
          if (matDouble[i][j] != 0 && abs(matDouble[i][j]) > abs(maxValue)) {
            maxValue = matDouble[i][j];
            maxIndex = i;
          }
        }
        std::cout << "Max is : " << maxValue << " in : " << maxIndex
                  << std::endl;
        if (maxIndex == -1) {
          return nullptr;
        } else if (maxIndex != 0) {
          // Put best line in first
          T tmp;
          for (int i = 0; i < N * 2; ++i) {
            tmp = matDouble[0][i];
            matDouble[0][i] = matDouble[maxIndex][i];
            matDouble[maxIndex][i] = tmp;
          }
          
        }
        // Divide row 0, add other
        for (int i = 0; i < N; ++i) {
          T lineCoef;
          bool coefInited = false;
          for (int k = 0; k < N * 2; ++k) {
            if (i == 0) {
              matDouble[i][k] /= maxValue;
            } else {
              if (!coefInited) {
                lineCoef = -matDouble[i][j];
                coefInited = true;
              }
              matDouble[i][k] += matDouble[0][k] * lineCoef;
            }
          }
        }
      }
      // Swaping rows to get the diag
      for(int j = 0; j < N; ++j){
        if(matDouble[j][j] != 1){
          for(int k = j; k < N; ++k){
            if(matDouble[k][j] == 1){
              //do swap
              T tmp;
              for (int i = 0; i < N * 2; ++i) {
                tmp = matDouble[j][i];
                matDouble[j][i] = matDouble[k][i];
                matDouble[k][i] = tmp;
              }
            }
          }
        }
      }
      // Keep right side only
      for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
          (*inverseMat)[i][j] = matDouble[i][j+N];
        }
      }
      std::cout<<*inverseMat<<std::endl;
      return inverseMat;
    }
  }

  /*
   * returns true if the matrix contains invalid values, false otherwise
   */
  bool is_null() {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) {
        if (std::isnan(mat[i][j])) return false;
      }
    }
    return true;
  }

  Matrix* transpose() {
    if (N != M) return nullptr;
    Matrix<N, M, T>* transposed = new Matrix<N, M, T>;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) {
        // std::cerr<<i<<" "<<j<<" "<<*transposed[i][j]<<"
        // "<<mat[j][i]<<std::endl;
        (*transposed)[i][j] = mat[j][i];
      }
    }
    return transposed;
  }

  bool is_ortho() {
      return *transpose() == *inverse();
  }

  friend std::ostream& operator<<(std::ostream& s, const Matrix& mat) {
    s << "{\n";
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) {
        s << (j == 0 ? "" : " ") << mat.mat[i][j];
      }
      s << "\n";
    }
    s << "}";
    return s;
  }

  T* operator[](int i) { return mat[i]; }

  bool operator==(Matrix& other) {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) {
        if (mat[i][j] != other[i][j]) return false;
      }
    }
    return true;
  }

  Matrix<N,M,T> operator+(Matrix &other){
    Matrix<N,M,T> sum;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) {
        sum[i][j] = mat[i][j] + other[i][j];
      }
    }
    return sum;
  }

  void operator+=(Matrix &other){
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) {
        mat[i][j] += other[i][j];
      }
    }
  }

  Matrix<N,M,T> operator*(T scalar){
    Matrix<N,M,T> mul;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) {
        mul[i][j] = mat[i][j] * scalar;
      }
    }
  }

  Matrix<N,M,T> operator*(Vector<N,T> &vec){
    Matrix<N,M,T> mul;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) {
        mul[i][j] = mat[i][j] * vec[i];
      }
    }
    return mul;
  }

  Matrix<N,M,T> operator*(Matrix<M,N,T> &other){
    Matrix<N,M,T> mul;
    mul.init();
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) {
        for(int k = 0; k < N; ++k){
            mul[i][j] += mat[i][j] * other[k][j];
        }
      }
    }
    return mul;
  }
};

class Mat44r : public Matrix<4,4,float>{};

#define zerovector Vector()

#define zerovec2i Vector2i()
#define zerovec3i Vector3i()
#define zerovec4i Vector4i()
#define zerovec2r Vector2r()
#define zerovec3r Vector3r()
#define zerovec4r Vector4r()

//TODO
//#define IdentityMat Matrix()

}  // namespace libmatrix
#endif