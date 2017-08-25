//
//  matrixTemplate.h
//
//  Created by HelloSangShen on 2017/4/27.
//  Copyright © 2017年 HelloSangShen. All rights reserved.
//

#ifndef MATRIXTEMPLATE_H
#define MATRIXTEMPLATE_H

#include <iostream>
#include <vector>
#include <math.h>
#include <stdexcept>
#include <QImage>
#include"imageprocessor.h"

struct HSI{
    double h;
    double s;
    double i;
};


using std::range_error;
using std::vector;
using std::cout;
using std::endl;
using std::ostream;



template<typename T>
class Matrix
{
private:
    // point to the data
    T ** _data;
    // number of row and column
    size_t _nRow, _nCol;

    // flag to indicate row-first or column-first

    bool checkRange(size_t r, size_t c) const;
    void swap(Matrix& mat);

public:
    size_t _startR, _startC;
    int _t;
    // construct a r-row and c-column matrix with all init element
    Matrix(size_t r, size_t c, T init);
    // copy constructor
    Matrix(const Matrix<T>& mat);
    Matrix<T>& operator=(Matrix<T> mat);
    ~Matrix();
    // get element at r-row and c-column
    // return reference to make it modifiable
    T& operator()(size_t r, size_t c) const;
    // get a submatrix [rs:re,cs:ce]
    Matrix<T> subMatrix(size_t rs, size_t re, size_t cs, size_t ce) const;
    // output the matrix
    template<typename U>
    friend std::ostream& operator<<(std::ostream& out, const Matrix<U>& rhs);
    size_t getNRow() const;
    size_t getNCol() const;
    void setStartR(const size_t sr);
    void setStartC(const size_t sc);
    std::vector<T> getRow(size_t r) const;
    std::vector<T> getCol(size_t c) const;
    bool setRow(size_t r, const std::vector<T>& d);
    bool setCol(size_t c, const std::vector<T>& d);
    // transpose it in-place
    Matrix<T>& transpose();

    // operator +
    Matrix<T> operator+(Matrix<T>& otherMat) const;
    Matrix<T> operator+(T factor) const;

    template<typename U>
    friend Matrix<U> operator+(const U factor, Matrix<U>& mat);

    // operator -
    Matrix<T> operator-(Matrix<T>& otherMat) const;
    Matrix<T> operator-(T factor) const;

    template<typename U>
    friend Matrix<U> operator-(const U factor, Matrix<U> & mat);

    // operator *
    Matrix<T> operator*(Matrix<T>& otherMat) const;
    T mul(vector<T> vec1, vector<T> vec2) const;

    Matrix<T> operator*(T factor) const;

    template<typename U>
    friend Matrix<U> operator*(const U factor, Matrix<U> & mat);

    // operator /
    template<typename U>
    friend Matrix<U> operator/(Matrix<U>& mat, const U factor);

    // translate between QImage & Matrix
    static Matrix<int> fromQImage(const QImage&, char);
    static QImage toQImage(const Matrix<int>&);
    static QImage toQImage(const Matrix<int>&, const Matrix<int>&, const Matrix<int>&);
    static Matrix<double> abs4complex(const Matrix<std::complex<double> > &);
    static Matrix<double> logtranslate(const Matrix<double> &);
    static void fftshift(Matrix<double> &);
    static Matrix<int> normalization(Matrix<double> &);
    static Matrix<int> lowpass(const Matrix<int> & mat,double c);
    static Matrix<int> highpass(const Matrix<int> & mat,double c);


    static QImage rgb2gray(const QImage&);
    static QImage pixelReverse(const QImage&);
    static QImage logTransformation(const QImage&,int c );
    static QImage histEquilibrium(const QImage&);
    static QImage histEquilibriumForRgb(const QImage&);
    static QImage histEquilibriumByHSI(const QImage&);
    static HSI Rgb2Hsi(const Matrix<int>& r,const Matrix<int>& g,const Matrix<int>& b,int j,int i);
    static int Hsi2Rgb(const HSI hsi,const Matrix<int>& r,const Matrix<int>& g,const Matrix<int>& b,int j,int i);
    static double Hue2Rgb(double v1, double v2,double vH);
    static QImage linearSpacialFilter(const QImage & img, const QVector<QVector<double> > vec,const int nCol, QString patten);
    static Matrix<int> zeroPadding(const Matrix<int>& r,const int nCol, const int nRow);
    static QImage filterImage(const Matrix<int> & r,const Matrix<int> & g,const Matrix<int> & b,const Matrix<int> & h,const QVector<QVector<double> > vec, int nCol, int nRow, QString patten);
    static int getBlockResult(const Matrix<int>& mat, int i, int j, QVector<QVector<double> > vec,int nCol, int nRow);
    static QImage gaussBlurFilter(const QImage & img, const int filterSize, const double sigma, QString patten);
    static QImage bilateralFilter(const QImage & img, const int filterSize, const double sigma, const double anotherSigma);
    static QImage medianFilter(const QImage & img, const int size, const QString filterPatten, const QString colorPatten);

};

template<typename T>
Matrix<T>::Matrix(size_t r, size_t c, T init):
_nRow(r), _nCol(c), _t(0)
{
    // new _data
    // new _data[i] within loop

    _t = 1;
    _startR = 0;
    _startC = 0;

    _data = new T* [r];

    for(int i = 0; i < r; i++){
        _data[i] = new T[c];
    }

    for(int i = 0; i < r ; i++){
        for (int j = 0; j < c; j++) {
            _data[i][j] = init;
        }
    }
}

template<typename T>
void Matrix<T>::setStartC(const size_t sc)
{
    this->_startC = sc;
}

template<typename T>
void Matrix<T>::setStartR(const size_t sr)
{
    this->_startR = sr;
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& mat):
_nRow(mat._nRow), _nCol(mat._nCol), _t(mat._t)
{
    // new _data
    // new and assign _data[i] within loop

    _t = 1;
    _startR = 0;
    _startC = 0;

    _data = new T* [_nRow];

    for(int i = 0; i < _nRow; i++){
        _data[i] = new T[_nCol];
    }

    for(int i = 0; i < _nRow ; i++){
        for (int j = 0; j < _nCol; j++) {
            _data[i][j] = mat._data[i][j];
        }
    }
}

template<typename T>
Matrix<T>::~Matrix()
{
    // delete _data[i] first
    // then delete _data

    for (int i = 0; i < _nRow; i++) {
        delete _data[i];
    }
    delete _data;
}

template<typename T>
void Matrix<T>::swap(Matrix<T>& mat) {
    std::swap(_data, mat._data);
    std::swap(_nRow, mat._nRow);
    std::swap(_nCol, mat._nCol);
    std::swap(_t, mat._t);
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T> mat)
{
    swap(mat);
    return *this;
}


template<typename T>
size_t Matrix<T>::getNRow() const
{
    // return the number of row
    if(_t == 1)
        return _nRow;
    return _nCol;
}

template<typename T>
size_t Matrix<T>::getNCol() const
{
    // return the number of column
    if(_t == 0)
        return _nRow;
    return _nCol;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(Matrix<T>& otherMat) const
{

    if(otherMat.getNRow() == getNRow() && otherMat.getNCol() == getNCol()){
        Matrix<T> matRes = otherMat;

        for(int i = 0; i < getNRow(); i++){
            // This is not the best, I wana a better method
            vector<T> row = getRow(i);
            for(int j = 0; j < getNCol(); j++){
                matRes(i, j) = row[j] + otherMat(i, j);
            }
        }
        return matRes;
    }else{
        throw range_error("operator+ :    Range Error");
    }
}

template<typename T>
Matrix<T> Matrix<T>::operator+(T factor) const
{
    Matrix<T> matRes = *this;
    for(int i = 0; i < getNRow(); i++){
        for(int j = 0; j < getNCol(); j++){
            matRes(i, j) = this->operator()(i, j) + factor;
        }
    }
    return matRes;
}

template<typename U>
Matrix<U> operator+(const U factor, Matrix<U>& mat)
{
    return mat + factor;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(Matrix<T>& otherMat) const{

    if(otherMat.getNRow() == getNRow() && otherMat.getNCol() == getNCol()){
        Matrix<T> matRes = otherMat;

        for(int i = 0; i < getNRow(); i++){
            // This is not the best, I wana a better method
            vector<T> row = getRow(i);
            for(int j = 0; j < getNCol(); j++){
                matRes(i, j) = row[j] - otherMat(i, j);
            }
        }
        return matRes;
    }else{
        throw range_error("operator+ :    Range Error");
    }
}

template<typename T>
Matrix<T> Matrix<T>::operator-(T factor) const
{
    Matrix<T> matRes = *this;
    for(int i = 0; i < getNRow(); i++){
        for(int j = 0; j < getNCol(); j++){
            matRes(i, j) = this->operator()(i, j) - factor;
        }
    }
    return matRes;
}

template<typename U>
Matrix<U> operator-(const U factor, Matrix<U>& mat)
{
    Matrix<U> matRes = mat;
    for(int i = 0; i < mat.getNRow(); i++){
        for(int j = 0; j < mat.getNCol(); j++){
            matRes(i, j) = factor - mat(i, j);
        }
    }
    return matRes;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T>& otherMat) const{

    if(otherMat.getNRow() == getNCol()){
        // It is terrible, ugly
        Matrix<T> matRes = Matrix(getNRow(), otherMat.getNCol(), otherMat(0,0));

        for(int i = 0; i < getNRow(); i++){
            for(int j = 0; j < otherMat.getNCol(); j++){
                matRes(i, j) = mul(getRow(i), otherMat.getCol(j));
            }
        }
        return matRes;
    }else{
        throw range_error("operator+ :    Range Error");
    }
}

template<typename T>
T Matrix<T>::mul(vector<T> vec1, vector<T> vec2) const{

    if(vec1.size() != vec2.size()){
        throw range_error("operator* :    Size Error");
    }
    else{
        // ...
        T t = vec1[0] * vec2[0];
        for(int i = 1; i < vec1.size(); i++)
            t += vec1[i] * vec2[i];
        return t;
    }
}

template<typename T>
Matrix<T> Matrix<T>::operator*(T factor) const
{
    Matrix<T> matRes = *this;
    for(int i = 0; i < getNRow(); i++){
        for(int j = 0; j < getNCol(); j++){
            matRes(i, j) = this->operator()(i, j) * factor;
        }
    }
    return matRes;
}

template<typename U>
Matrix<U> operator*(const U factor, Matrix<U>& mat)
{
    return mat * factor;
}

template<typename U>
Matrix<U> operator/(Matrix<U>& mat, const U factor)
{
    Matrix<U> matRes = mat;
    for(int i = 0; i < mat.getNRow(); i++){
        for(int j = 0; j < mat.getNCol(); j++){
            matRes(i, j) = mat(i, j)/factor;
        }
    }
    return matRes;
}


template<typename T>
bool Matrix<T>::checkRange(size_t r, size_t c) const
{
    // check if r-row and c-column is out of range
    if(_t == 1){
        if(r >= _nRow || c >= _nCol)
            return false;
    }else if(_t == 0){
        if(r >= _nCol || c >= _nRow)
            return false;
    }

    return true;
}

template<typename T>
T& Matrix<T>::operator()(size_t r, size_t c) const
{
    // get element in (r,c)
    // remember check first
    // different of _t has different order
    if(!checkRange(r, c)){
        // out of range
        throw range_error("operator() :    Out Of Range");
    }

    if(_t == 1){
        return _data[(r+_startR)%_nRow][(c+_startC)%_nCol];
    }else{
        return _data[(c+_startC)%_nCol][(r+_startR)%_nRow];
    }
}

template<typename T>
Matrix<T> Matrix<T>::subMatrix(size_t rs, size_t re, size_t cs, size_t ce) const
{
    // note the validity of value:rs, re, cs, ce
    // try to use "except" to broadcast the exception

    if(_t == 1){
        if(!(rs <= re && re < _nRow && cs <= ce && ce < _nCol)){
            // out of range
            throw range_error("subMatrix :    Parameters Out Of Range");
        }else{
            Matrix<T> newMat =  Matrix<T>(re - rs + 1, ce - cs + 1, 0);
            for(int i = 0; i < newMat._nRow; i++){
                for(int j = 0; j < newMat._nCol; j++){
                    newMat._data[i][j] = _data[i + rs][j + cs];
                }
            }
            return newMat;
        }
    }else {
        if(!(rs <= re && re <= _nCol && cs <= ce && ce <= _nRow)){
            // out of range
            throw range_error("subMatrix :    Parameters Out Of Range");
        }else{
            Matrix<T> newMat =  Matrix<T>(ce - cs + 1, re - rs + 1, 0);
            for(int i = 0; i < newMat._nRow; i++){
                for(int j = 0; j < newMat._nCol; j++){
                    // ...
                    newMat._data[i][j] = _data[i + cs][j + rs];
                }
            }
            return newMat;
        }
    }

    //...
    return Matrix<int>(1,1,0);
}

template<typename T>
std::vector<T> Matrix<T>::getRow(size_t r) const
{
    // get all element in r-row and push it back in a vector
    // remember check range first
    if((_t == 1 && r > _nRow) || (_t == 0 && r > _nCol)){
        throw range_error("getRow() :    Out Of Range");
    }
    vector<T> vec;
    if(_t == 1){
        for(int i = 0; i < _nCol; i++){
            vec.push_back(_data[r][i]);
        }
    }else{
        for(int i = 0; i < _nRow; i++){
            vec.push_back(_data[i][r]);
        }
    }
    return vec;
}

template<typename T>
std::vector<T> Matrix<T>::getCol(size_t c) const
{
    // get all element in c-column and push it back in a vector
    // remember check range first
    if((_t == 1 && c > _nCol) || (_t == 0 && c > _nRow)){
        throw range_error("getCol() :    Out Of Range");
    }
    vector<T> vec;
    if(_t == 1){
        for(int i = 0; i < _nRow; i++){
            vec.push_back(_data[i][c]);
        }
    }else{
        for(int i = 0; i < _nCol; i++){
            vec.push_back(_data[c][i]);
        }
    }
    return vec;
}

template<typename T>
bool Matrix<T>::setRow(size_t r, const vector<T>& d)
{
    // set the element of the r-row
    // remember check range first

    if(_t == 1 && checkRange(r, d.size() - 1)){
        if(d.size() == _nCol){
            for(int i = 0; i < d.size(); i++){
                _data[r][i] = d[i];
            }
            return true;
        }else{
            throw range_error("setRow :    illegal size of vector");
        }
    }else if(_t == 0 && checkRange(d.size() - 1, r)){
        if(d.size() == _nRow){
            for(int i = 0; i < d.size(); i++){
                _data[i][r] = d[i];
            }
            return true;
        }else{
            throw range_error("setRow :    illegal size of vector");}
    }
    return false;
}

template<typename T>
bool Matrix<T>::setCol(size_t c, const vector<T>& d)
{
    // set the element of the c-column
    // remember check range first

    if(_t == 1 && checkRange(d.size() - 1, c)){
        if(d.size() == _nRow){
            for(int i = 0; i < d.size(); i++){
                _data[i][c] = d.at(i);
            }
            return true;
        }else{
            throw range_error("setRow :    illegal size of vector");
        }
    }else if(_t == 0 && checkRange(c, d.size() - 1)){
        if (d.size() == _nCol) {
            for(int i = 0; i < d.size(); i++){
                _data[c][i] = d.at(i);
            }
            return true;
        }else{
            throw range_error("setRow :    illegal size of vector");
        }
    }
    return false;
}

template<typename T>
Matrix<T>& Matrix<T>::transpose()
{
    // change _t
    // swap _nRow and _nCol
    // the fastest transpose in the history ?
    if(_t == 0){
        _t = 1;
    }else if( _t == 1){
        _t = 0;
    }
    return * this;
}

template<typename U>
ostream& operator<<(ostream& out, const Matrix<U>& rhs)
{
    for(size_t i = 0; i < rhs.getNRow(); ++i) {
        for(size_t j = 0; j < rhs.getNCol(); ++j) {
            out << rhs(i,j) << "\t";
        }
        out << endl;
    }
    return out;
}


// translate between QImage & Matrix
template<typename T>
Matrix<int> Matrix<T>::fromQImage(const QImage& img, char patten)
{
    Matrix<int> ret(img.height(), img.width(), 0);

    for(int i = 0; i < img.height(); i++){
        for(int j = 0; j < img.width(); j++){
            if(patten == 'r'){
                ret(i, j) = qRed(img.pixel(j, i));
            }else if(patten == 'g'){
                ret(i, j) = qGreen(img.pixel(j, i));
            }else if(patten == 'b'){
                ret(i, j) = qBlue(img.pixel(j, i));
            }else if(patten == 'h'){
                ret(i, j) = qGray(img.pixel(j, i));
            }
        }
    }

    return ret;
}
template<typename T>
QImage Matrix<T>::rgb2gray(const QImage& img)
{
     Matrix<int> g = Matrix<int>::fromQImage(img, 'h');
     QImage ret = Matrix<int>::toQImage(g);
     return ret;
}

template<typename T>
QImage Matrix<T>::pixelReverse(const QImage& img)
{
     Matrix<int> r = Matrix<int>::fromQImage(img, 'r');
     Matrix<int> g = Matrix<int>::fromQImage(img, 'g');
     Matrix<int> b = Matrix<int>::fromQImage(img, 'b');
     int r_width = r.getNCol();
     int r_height = r.getNRow();
     int g_width = g.getNCol();
     int g_height = g.getNRow();
     int b_width = b.getNCol();
     int b_height = b.getNRow();
     for(int i = 0; i< r_width; i++){
             for(int j = 0; j < r_height; j++){
                 int red = r(j,i);
                 r(j,i) =  255 - red;

             }
         }
     for(int i = 0; i< g_width; i++){
             for(int j = 0; j < g_height; j++){
                int green = g(j,i);
                 g(j,i) =255 - green;
             }
         }
     for(int i = 0; i< b_width; i++){
             for(int j = 0; j < b_height; j++){
                 int blue = b(j,i);
                 b(j,i) = 255-blue;
             }
         }


     QImage ret = Matrix<int>::toQImage(r,g,b);
     return ret;
}

template<typename T>
QImage Matrix<T>:: logTransformation(const QImage& img,int c)
{
     Matrix<int> h = Matrix<int>::fromQImage(img, 'h');
     int width = h.getNCol();
     int height = h.getNRow();
     for(int i = 0; i< width; i++){
             for(int j = 0; j < height; j++){
                 int gray = h(j,i);
                 int grayValue = c * log(gray/255.0 + 1) * 255;
                 h(j,i) = grayValue;
             }
         }
     QImage ret = Matrix<int>::toQImage(h);
     return ret;
}

template<typename T>
QImage Matrix<T>::histEquilibrium(const QImage& img)
{
     Matrix<int> h = Matrix<int>::fromQImage(img, 'h');
     int width = h.getNCol();
     int height = h.getNRow();
     int N = width * height;

         // 统计各级灰度
         int hist[256];
         std::fill(hist, hist + 256, 0);

         for(int i = 0; i < width; i++){
             for(int j = 0; j < height; j++){
                 hist[h(j,i)]++;
             }
         }

         // 累计灰度计算
         int map[256];
         double sum = 0;
         for(int i = 0; i < 256; i++){
             sum += hist[i];
             map[i] = round(sum / N * 255);
         }

         // 映射
         for(int i = 0; i < width; i++){
             for(int j = 0; j < height; j++){
                 h(j,i) = map[h(j,i)];
             }
         }
     QImage ret = Matrix<int>::toQImage(h);
     return ret;
}
template<typename T>
QImage Matrix<T>::histEquilibriumForRgb(const QImage& img)
{
     Matrix<int> r = Matrix<int>::fromQImage(img, 'r');
     Matrix<int> g = Matrix<int>::fromQImage(img, 'g');
     Matrix<int> b = Matrix<int>::fromQImage(img, 'b');
     int width = r.getNCol();
     int height = r.getNRow();
     int N = width * height;

         // count histgram
         int hist[3][256];
         std::fill(hist[0], hist[0] + 3 * 256, 0);

         for(int i = 0; i < width; i++){
             for(int j = 0; j < height; j++){
                 hist[0][r(j,i)]++;
                 hist[1][g(j,i)]++;
                 hist[2][b(j,i)]++;
             }
         }

         // calculate
         int map[3][256];
         double sum[3] = {0};
         for(int i = 0; i < 256; i++){
             sum[0] += hist[0][i];
             sum[1] += hist[1][i];
             sum[2] += hist[2][i];

             map[0][i] = round(sum[0] / N * 255);
             map[1][i] = round(sum[1] / N * 255);
             map[2][i] = round(sum[2] / N * 255);
         }

         // map the pixel
         for(int i = 0; i < width; i++){
             for(int j = 0; j < height; j++){
                 r(j,i) = map[0][r(j,i)];
                 g(j,i) = map[1][g(j,i)];
                 b(j,i) = map[2][b(j,i)];
             }
         }
     QImage ret = Matrix<int>::toQImage(r,g,b);
     return ret;
}



template<typename T>
QImage Matrix<T>::histEquilibriumByHSI(const QImage& img)
{

    Matrix<int> r = Matrix<int>::fromQImage(img, 'r');
    Matrix<int> g = Matrix<int>::fromQImage(img, 'g');
    Matrix<int> b = Matrix<int>::fromQImage(img, 'b');
    int width = r.getNCol();
    int height = r.getNRow();
    int N = width * height;

    // count histgram
    int hist[256];
    std::fill(hist, hist + 256, 0);

    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){

            // 此处I的取值范围为0-1，所以需要乘以255
            hist[(int)(Matrix<T>::Rgb2Hsi(r,g,b,j,i).i * 255)]++;
        }
    }

    // calculate
    int map[256];
    double sum = 0;
    for(int i = 0; i < 256; i++){
        sum += hist[i];
        map[i] = round(sum / N * 255);
    }

    // map the pixel
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            HSI temp = Matrix<T>::Rgb2Hsi(r,g,b,j,i);
            temp.i = map[(int)(Matrix<T>::Rgb2Hsi(r,g,b,j,i).i * 255)] / 255.0;
             Matrix<T>::Hsi2Rgb(temp,r,g,b,j,i);
        }
    }
    QImage ret = Matrix<int>::toQImage(r,g,b);
    return ret;
}

template<typename T>
HSI Matrix<T>::Rgb2Hsi(const Matrix<int>& r,const Matrix<int>& g,const Matrix<int>& b,int j,int i){

    HSI hsi;
    // 归一化
    double R = r(j,i)/ 255.0;
    double G = g(j,i) / 255.0;
    double B = b (j,i)/ 255.0;

    // 求范围
    double min = std::min(std::min(R, G), B);
    double max = std::max(std::max(R, G), B);
    double deltaMax = max - min;

    double H;
    double S;
    double I = (max + min) / 2;

    if (deltaMax == 0 ){
        H = 0;
        S = 0;
    }else{
        H = 0;
        if (I < 0.5)
            S = deltaMax / (max + min);
        else
            S = deltaMax / (2 - max - min);

        double deltaR = (((max - R) / 6.0) + (deltaMax / 2.0)) / deltaMax;
        double deltaG = (((max - G) / 6.0) + (deltaMax / 2.0)) / deltaMax;
        double deltaB = (((max - B) / 6.0) + (deltaMax / 2.0)) / deltaMax;

        if (R == max){
            H = deltaB - deltaG;
        }else if (G == max){
            H = 1 / 3.0 + deltaR - deltaB;
        }else if (B == max){
            H = 2 / 3.0 + deltaG - deltaR;
        }

        if (H < 0)
            H += 1;
        if (H > 1)
            H -= 1;
    }

    hsi.h = H;
    hsi.s = S;
    hsi.i = I;

    return hsi;
}

/**
 * HSI颜色空间转换到RGB中
 */
template<typename T>
int Matrix<T>::Hsi2Rgb(const HSI hsi,const Matrix<int>& r,const Matrix<int>& g,const Matrix<int>& b,int j,int i){

    double H = hsi.h;
    double S = hsi.s;
    double I = hsi.i;

    int R = 0;
    int G = 0;
    int B = 0;

    double v1 = 0;
    double v2 = 0;

    if (S == 0) {
        R = I * 255;
        G = I * 255;
        B = I * 255;
    }else {
        if (I < 0.5){
            v2 = I * (1 + S);
        }else{
            v2 = (I + S) - (S * I);
        }

        v1 = 2 * I - v2;

        R = 255 * Matrix<int>::Hue2Rgb(v1, v2, H + 1/3.0);
        G = 255 * Matrix<int>::Hue2Rgb(v1, v2, H);
        B = 255 * Matrix<int>::Hue2Rgb(v1, v2, H - 1/3.0);
    }
    r(j,i) = R;
    g(j,i) = G;
    b(j,i) = B;
}

/**
 * Hue2Rgb格式
 */
template<typename T>
double Matrix<T>::Hue2Rgb(double v1, double v2,double vH)
{
    if (vH < 0)
        vH += 1;
    if (vH > 1)
        vH -= 1;

    if ((6 * vH) < 1)
        return v1 + (v2 - v1) * 6 * vH;

    if ((2 * vH) < 1)
        return v2;

    if ((3 * vH) < 2)
        return v1 + (v2 - v1) * (2 / 3.0 - vH) * 6;

    return v1;
}

template<typename T>
QImage Matrix<T>::toQImage(const Matrix<int>& gray)
{
    int width = gray.getNCol();
    int height = gray.getNRow();

    QImage img = QImage(width, height, QImage::Format_RGB32);
    for(int i = 0; i < width; i++){
        for(int j =0; j < height; j++){
            int g = gray(j, i);
            img.setPixel(i, j, qRgb(g, g, g));
        }
    }
    return img;
}

template<typename T>
QImage Matrix<T>::toQImage(const Matrix<int>& red, const Matrix<int>& green, const Matrix<int>& blue)
{
    // illegal size
    if(red.getNCol() != blue.getNCol() || red.getNCol() != green.getNCol() || green.getNCol() != blue.getNCol() ||
            red.getNRow() != blue.getNRow() || red.getNRow() != green.getNRow() || green.getNRow() != blue.getNRow()){
        throw range_error("toQImage :    illegal size of matrix");
    }

    int width = red.getNCol();
    int height = red.getNRow();
    QImage img = QImage(width, height, QImage::Format_RGB32);
    for(int i = 0; i < width; i++){
        for(int j =0; j < height; j++){
            int r = red(j, i);
            int g = green(j, i);
            int b = blue(j, i);
            img.setPixel(i, j, qRgb(r, g, b));
        }
    }
    return img;
}

template<typename T>
Matrix<double> Matrix<T>::abs4complex(const Matrix<std::complex<double> > & mat)
{
    int width = mat.getNCol();
    int height = mat.getNRow();

    Matrix<double> res(height, width, 0);

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            res(i, j) = abs(mat(i, j));
        }
    }

    return res;
}

template<typename T>
Matrix<double> Matrix<T>::logtranslate(const Matrix<double> & mat)
{
    int width = mat.getNCol();
    int height = mat.getNRow();

    Matrix<double> res(height, width, 0);

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            res(i, j) = log(1 + mat(i, j));
        }
    }

    return res;
}

template<typename T>
void Matrix<T>::fftshift(Matrix<double> & mat)
{
    mat.setStartC(mat.getNCol()/2);
    mat.setStartR(mat.getNRow()/2);
}

template<typename T>
Matrix<int> Matrix<T>::lowpass(const Matrix<int> & mat,double c)
{
    int width = mat.getNCol();
    int height = mat.getNRow();
    Matrix<int> res(height, width, 0);
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            double d = sqrt(((i-height/2)*(i-height/2)+(j-width/2)*(j-width/2)));
           if(d<c)
           {
              res(i, j) = mat(i, j);
           }
           else
           {
               res(i,j) = 0;
           }
        }
    }

    return res;
}

template<typename T>
Matrix<int> Matrix<T>::highpass(const Matrix<int> & mat,double c)
{
    int width = mat.getNCol();
    int height = mat.getNRow();
    Matrix<int> res(height, width, 0);
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            double d = sqrt(((i-height/2)*(i-height/2)+(j-width/2)*(j-width/2)));
           if(d>c)
           {
              res(i, j) = mat(i, j);
           }
           else
           {
               res(i,j) = 0;
           }
        }
    }

    return res;
}

template<typename T>
Matrix<int> Matrix<T>::normalization(Matrix<double> & mat)
{
    int width = mat.getNCol();
    int height = mat.getNRow();

    Matrix<int> res(height, width, 0);

    double max = mat(0, 0), min = mat(0, 0);
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(mat(i, j) > max){
                max = mat(i, j);
            }
            if(mat(i, j) < min){
                min = mat(i, j);
            }
        }
    }

    double dis = max - min;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            res(i, j) = (int) ((mat(i, j) - min)/dis * 255);
        }
    }

    return res;
}
template<typename T>
QImage Matrix<T>::linearSpacialFilter(const QImage & img, const QVector<QVector<double> > vec,const int nCol, QString patten)
{

    Matrix<int> r = Matrix<int>::fromQImage(img, 'r');
    Matrix<int> g = Matrix<int>::fromQImage(img, 'g');
    Matrix<int> b = Matrix<int>::fromQImage(img, 'b');
    Matrix<int> h = Matrix<int>::fromQImage(img, 'h');

    int nRow = vec.length();
    if(nRow * nCol % 2 == 0)
    {
        return img;
    }

    // 补0
    Matrix<int> _r = Matrix<T>::zeroPadding(r,nCol, nRow);
    Matrix<int> _g = Matrix<T>::zeroPadding(g,nCol, nRow);
    Matrix<int> _b = Matrix<T>::zeroPadding(b,nCol, nRow);
    Matrix<int> _h = Matrix<T>::zeroPadding(h,nCol, nRow);

    // 滤波计算
    QImage filteredImage = Matrix<T>::filterImage(_r,_g,_b,_h,vec, nCol, nRow, patten);
    return filteredImage;
}

template<typename T>
Matrix<int> Matrix<T>::zeroPadding(const Matrix<int>& r,const int nCol, const int nRow)
{
    //QImage ret = QImage(img.width() + nCol - 1, img.height() + nRow - 1, img.format());
    int width_res = r.getNCol() + nCol - 1;
    int height_res = r.getNRow()+ nRow - 1;
    Matrix<int> res(height_res, width_res, 0);

    for(int i = 0; i < width_res; i++){
        for(int j = 0; j < height_res; j++){
            if(i >= nCol/2 && i < width_res- nCol/2 && j >= nRow/2 && j < height_res - nRow/2)
            {
                //ret.setPixel(i, j, img.pixel(i - nCol/2, j - nRow/2));
                res(j,i) = r(j - nRow/2,i - nCol/2);
            }else{
                res(j,i) = 0;

            }
        }
    }

    return res;
}
template<typename T>
QImage Matrix<T>::filterImage(const Matrix<int>& r,const Matrix<int>& g,const Matrix<int>& b,const Matrix<int>& h,const QVector<QVector<double> > vec, int nCol, int nRow, QString patten)
{

    //QImage ret = QImage(img.width() - nCol + 1, img.height() - nRow + 1, img.format());

    int width = r.getNCol();
    int height = r.getNRow();
    for(int i = nCol/2; i < width - nCol/2  ; i++)
    {
        for(int j = nRow/2; j < height -nRow/2; j++)
        {

            if(patten == "RGB")
            {
                // 直接计算每一块的结果
                int blockR = Matrix::getBlockResult(r, i, j, vec, nCol, nRow);
                int blockG = Matrix::getBlockResult(g, i, j, vec, nCol, nRow);
                int blockB = Matrix::getBlockResult(b, i, j, vec, nCol, nRow);

                //ret.setPixel(i - nCol/2, j - nRow/2, qRgb(blockR, blockG, blockB));
                r(j - nRow/2,i - nCol/2) = blockR;
                g(j - nRow/2,i - nCol/2) = blockG;
                b(j - nRow/2,i - nCol/2) = blockB;

            }
            else if(patten == "Gray")
            {
                int blockY = Matrix::getBlockResult(h, i, j, vec, nCol, nRow);
                //ret.setPixel(i - nCol/2, j - nRow/2, qRgb(blockY, blockY, blockY));
                h(j - nRow/2,i - nCol/2) = blockY;
            }

        }
    }
   if(patten == "RGB")
   {
       QImage ret1 = Matrix<int>::toQImage(r,g,b);
       return ret1;
   }
   else
   {
       QImage ret2 = Matrix<int>::toQImage(h);
       return ret2;
   }
}

template<typename T>
int Matrix<T>::getBlockResult(const Matrix<int>& mat, int i, int j, QVector<QVector<double> > vec,int nCol, int nRow)
{

    double sum = 0;

    int indexX = 0;
    for(int x = i - nCol/2; x <= i + nCol/2; x++){
        int indexY = 0;
        for(int y = j - nRow/2; y <= j + nRow/2; y++)
        {
            sum += mat(y,x)* vec[indexX][indexY];
            indexY++;
        }
        indexX++;
    }
    return (int)sum;
}
template<typename T>
QImage Matrix<T>::gaussBlurFilter(const QImage & img, const int filterSize, const double sigma, QString patten)
{

    QVector<QVector<double> > kernel = ImageProcessor::computeGaussFilter(filterSize, sigma);

    return Matrix<int>::linearSpacialFilter(img, kernel, filterSize, patten);
}
template<typename T>
QImage Matrix<T>::bilateralFilter(const QImage & img, const int filterSize, const double sigma, const double anotherSigma){

    QVector<QVector<double> > gaussFIilter = ImageProcessor::computeGaussFilter(filterSize, sigma);

    QVector<double> bilateralPar = ImageProcessor::computeEveryDistance(anotherSigma);

    Matrix<int> h = Matrix<int>::fromQImage(img, 'h');
    Matrix<int> proImg = Matrix<T>::zeroPadding(h, filterSize, filterSize);
    int width = h.getNCol();
    int height = h.getNRow();
    Matrix<int> res(height, width, 0);
    //QImage ret = QImage(img.width(), img.height(), img.format());

    for(int i = filterSize/2; i < proImg.getNCol()- filterSize/2; i++){
        for(int j = filterSize/2; j < proImg.getNRow() - filterSize/2; j++){

            QVector<QVector<double> > curKernel;

            for(int ii = -filterSize/2; ii <= filterSize/2; ii++){
                QVector<double> lineKernel;
                for(int jj = -filterSize/2; jj <= filterSize/2; jj++){

                    lineKernel.push_back(gaussFIilter[ii + filterSize/2][jj + filterSize/2] *
                            bilateralPar[abs(proImg(j,i) -proImg(j + jj,i + ii))]);

                }
                curKernel.push_back(lineKernel);
            }

            ImageProcessor::filterNormalization(curKernel, filterSize);
            int blockGray = Matrix::getBlockResult(proImg, i, j, curKernel, filterSize, filterSize);
            res(j - filterSize/2,i - filterSize/2) = blockGray;
            //ret.setPixel(i - filterSize/2, j - filterSize/2, qRgb(blockGray, blockGray, blockGray));
        }
    }
    QImage ret = Matrix<int>::toQImage(res);
    return ret;

}

template<typename T>
QImage Matrix<T>::medianFilter(const QImage & img, const int size, const QString filterPatten, const QString colorPatten){

    Matrix<int> r = Matrix<int>::fromQImage(img, 'r');
    Matrix<int> g = Matrix<int>::fromQImage(img, 'g');
    Matrix<int> b = Matrix<int>::fromQImage(img, 'b');
    Matrix<int> h = Matrix<int>::fromQImage(img, 'h');
    Matrix<int> padImg_r = Matrix<int>::zeroPadding(r, size, size);
    Matrix<int> padImg_g = Matrix<int>::zeroPadding(g, size, size);
    Matrix<int> padImg_b = Matrix<int>::zeroPadding(b, size, size);
    Matrix<int> padImg_h = Matrix<int>::zeroPadding(h, size, size);
    int width = h.getNCol();
    int height = h.getNRow();
    Matrix<int> ret_h(height, width, 0);
    Matrix<int> ret_r(height, width, 0);
    Matrix<int> ret_g(height, width, 0);
    Matrix<int> ret_b(height, width, 0);
    //QImage ret(img);

    for(int i = size/2; i < width; i++){
        for(int j = size/2; j < height; j++){

            if(colorPatten == "Gray"){
                QVector<int> block;
                for(int ii = -size/2; ii <= size/2; ii++){
                    for(int jj = -size/2; jj <= size/2; jj++){
                        block.push_back(padImg_h(j+jj,i+ii));
                    }
                }
                std::sort(block.begin(), block.end());

                int gray;
                if(filterPatten == "median"){
                    gray = block[block.length()/2];
                }else if(filterPatten == "expand"){
                    gray = block[block.length() - 1];
                }else if(filterPatten == "corrosion"){
                    gray = block[0];
                }
                ret_h(j - size/2,i - size/2) = gray;

            }else if(colorPatten == "RGB"){
                QVector<int> blockR;
                QVector<int> blockG;
                QVector<int> blockB;
                for(int ii = -size/2; ii <= size/2; ii++){
                    for(int jj = -size/2; jj <= size/2; jj++){
                        blockR.push_back(padImg_r(j+jj,i+ii));
                        blockG.push_back(padImg_g(j+jj,i+ii));
                        blockB.push_back(padImg_b(j+jj,i+ii));
                    }
                }
                std::sort(blockR.begin(), blockR.end());
                std::sort(blockG.begin(), blockG.end());
                std::sort(blockB.begin(), blockB.end());

                int red;
                int green;
                int blue;
                if(filterPatten == "median"){
                    red = blockR[blockR.length()/2];
                    green = blockG[blockG.length()/2];
                    blue = blockB[blockB.length()/2];
                }else if(filterPatten == "expand"){
                    red = blockR[blockR.length() - 1];
                    green = blockG[blockG.length() - 1];
                    blue = blockB[blockB.length() - 1];
                }else if(filterPatten == "corrosion"){
                    red = blockR[0];
                    green = blockG[0];
                    blue = blockB[0];
                }
                //ret.setPixel(i - size/2, j - size/2, qRgb(red, green, blue));
                ret_r(j - size/2,i - size/2) = red;
                ret_g(j - size/2,i - size/2) = green;
                ret_b(j - size/2,i - size/2) = blue;
            }
        }
    }

    if(colorPatten == "Gray")
    {
        QImage res = Matrix<int>::toQImage(ret_h);
        return res;
    }
    else if(colorPatten == "RGB")
    {
        QImage res = Matrix<int>::toQImage(ret_r,ret_g,ret_b);
        return res;
    }
}
#endif /* matrixTemplate_h */
