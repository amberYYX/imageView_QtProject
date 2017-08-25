#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QImage>
#include <QRgb>
#include <algorithm>

class ImageProcessor
{
    struct HSI
    {
        double h;
        double s;
        double i;
    };

public:
    ImageProcessor();

    static QImage rgb2gray(const QImage&);
    static QImage reverse(const QImage&);

    static QImage histEq(const QImage&);
    static QImage colorHisteq1(const QImage&);
    static QImage hsi(const QImage&);

    static void rgb2hsi(QRgb rgb,HSI Hsi);
    static void hsi2rgb(QRgb rgb,HSI Hsi);
    static double Hue_2_RGB(double v1,double v2,double vH );
    static void cumulateHist(int* hist,int* map,int N);

    static double min(double a,double b,double c);
    static double max(double a,double b,double c);

    static QImage logTransmation(const QImage&,double c);

    static QImage zeroPadding(const QImage&,int,int);
    static QImage zeroPadding_repeat(const QImage&,int,int);
    static QImage zeroPadding_mirror(const QImage&,int,int);

    //filter
    static QImage linearRgbFilter(const QImage&,std::vector<double>,int);
    static QImage linearGrayFilter(const QImage&,std::vector<double>,int);

//    static QImage filter(const QImage&,std:: vector<double>&,int,int);
    static QImage filterRgb(const QImage&,std:: vector<double>&,int,int);
    static QImage filterGray(const QImage&,std:: vector<double>&,int,int);


    static std::vector<int> getPatch(const QImage&,int,int,int,int,char);//?
    static QImage crop(const QImage&,int,int);
    static void KernelNormalization(std::vector<double>&);

    //gaussBlur
    static QImage gaussRgbBlur(const QImage&,int,double);
    static QImage gaussGrayBlur(const QImage&,int,double);

    static std::vector<double> creatGaussKernel(int,double);

    //bilateral filter
    static QImage bilateralFilter(const QImage&,int,double,double);
    static std::vector<double> creatBilateralKernel(double);

    //median filter
    static QImage medianRgbFilter(const QImage&,double);
    static QImage medianGrayFilter(const QImage&,double);

    //expand filter
    static QImage expandRgbFilter(const QImage&,double);
    static QImage expandGrayFilter(const QImage&,double);

    //corrosion filter
    static QImage corrosionRgbFilter(const QImage&,double);
    static QImage corrosionGrayFilter(const QImage&,double);

    static QImage transform(const QImage &img,const QMatrix &matrix);
    static QRgb getNewRgb(const QMatrix& matrix,const QImage &img,const int i,const  int j,const  double minX,const  double minY) ;
    static void getRange(const QMatrix& matrix,const QImage &img, double &minX, double& maxX, double& minY, double& maxY);
    static void filterNormalization(QVector<QVector<double> > &vec, const int nCOl);

    void my_Sort( const  std::vector<qreal>::iterator begin, const std::vector<qreal>::iterator end);
    static QRgb bilinear(const QImage &img,const double x, double y);
    static double linear_inter(const double v1,const double v2,const double c1,const double c2,const double c3) ;

    static QVector<QVector<double> > computeGaussFilter(const int filterSize, const double sigma);
    static QVector<double> computeEveryDistance(const double anotherSigma);

};

#endif // IMAGEPROCESSOR_H
