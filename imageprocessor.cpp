#include "imageprocessor.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <QtCore>
using namespace std;

ImageProcessor::ImageProcessor()
{

}

double ImageProcessor::min(double a, double b, double c)
{
    double min=256;
    if(a<min)
        min=a;
    if(b<min)
        min=b;
    if(c<min)
        min=c;
    return min;
}

double ImageProcessor::max(double a, double b, double c)
{
    double max=0;
    if(a>max)
        max=a;
    if(b>max)
        max=b;
    if(c>max)
        max=c;
    return c;
}

void ImageProcessor::rgb2hsi(QRgb rgb,HSI Hsi)
{
    double R = qRed(rgb);
    double G = qGreen(rgb);
    double B = qBlue(rgb);
    double H,S,I;
    double var_R = R/255;//RGB from 0 to 255
    double var_G = G/255;
    double var_B = B/255;
    double var_Min = min(var_R,var_G,var_B);//Min.value of RGB
    double var_Max = max(var_R,var_G,var_B);//Max.value of RGB
    double del_Max = var_Max - var_Min;//delta RGB value
    I = (var_Max + var_Min)/2;//get I
    if(0 == del_Max)//gray picture
    {
        H = 0;
        S = 0;
    }
    else
    {
        if(I < 0.5)
        {
            S = del_Max / (var_Max + var_Min);
        }
        else
        {
            S = del_Max / (2 - var_Max - var_Min);
        }
        double del_R = ( ( ( var_Max - var_R ) / 6 ) + ( del_Max / 2 ) ) / del_Max;
        double del_G = ( ( ( var_Max - var_G ) / 6 ) + ( del_Max / 2 ) ) / del_Max;
        double del_B = ( ( ( var_Max - var_B ) / 6 ) + ( del_Max / 2 ) ) / del_Max;
        if ( var_R == var_Max )
            H = del_B - del_G;
        else if ( var_G == var_Max )
            H = ( 1 / 3 ) + del_R - del_B;
        else if ( var_B == var_Max )
            H = ( 2 / 3 ) + del_G - del_R;
        if ( H < 0 )
            H += 1;
        if ( H > 1 )
            H -= 1;
    }

    Hsi.h = H;
    Hsi.i = I;
    Hsi.s = S;
}

double ImageProcessor::Hue_2_RGB(double v1,double v2,double vH )
{
    if ( vH < 0 )
        vH += 1;
    if ( vH > 1 )
        vH -= 1;
    if ( ( 6 * vH ) < 1 )
        return ( v1 + ( v2 - v1 ) * 6 * vH );
    if ( ( 2 * vH ) < 1 )
        return ( v2 );
    if ( ( 3 * vH ) < 2 )
        return ( v1 + ( v2 - v1 ) * ( ( 2 / 3 ) - vH ) * 6 );
    return ( v1 );
}

void ImageProcessor::cumulateHist(int* hist,int* map,int N)
{
    double sum = 0;
    for(int i =0;i<256;i++)
    {
        sum += hist[i];
        map[i] = round(sum / N * 255);
    }
}

void ImageProcessor::hsi2rgb(QRgb rgb,HSI Hsi)
{
    double S = Hsi.s;
    double H = Hsi.h;
    double I = Hsi.i;
    double var_1,var_2;
    int R,G,B;
    if ( S == 0 ) //HSL from 0 to 1
    {
        R = I * 255; //RGB results from 0 to 255
        G = I * 255;
        B = I * 255;
    }
    else
    {
        if ( I < 0.5 )
            var_2 = I * ( 1 + S );
        else
            var_2 = ( I + S ) - ( S *I );

        var_1 = 2 *I - var_2;
        R = 255 * Hue_2_RGB( var_1, var_2, H+ ( 1 / 3 ) );
        G = 255 * Hue_2_RGB( var_1, var_2, H);
        B = 255 * Hue_2_RGB( var_1, var_2, H- ( 1 / 3 ) );
    }

    rgb = qRgb(R,G,B);
}

QImage ImageProcessor::rgb2gray(const QImage &img)
{
    QImage ret(img);
    int width = img.width();
    int height= img.height();
    int N= width*height;

     //map the pixcal
            for(int i=0;i<width;i++)
            {
                for(int j=0;j<height;j++)
                {
                    int g = qGray(img.pixel(i,j));
                    ret.setPixel(i,j,qRgb(g,g,g));
                }
            }
      return ret;
}


//反
QImage ImageProcessor::reverse(const QImage& img)
{
    QImage ret(img);//copy
    int width = img.width();
    int height= img.height();
    for(int i=0;i<width;i++)
    {
        for(int j=0;j<height;j++)
        {
            QRgb rgb = img.pixel(i,j);
            int r= 255-qRed(rgb);
            int g= 255-qGreen(rgb);
            int b= 255-qBlue(rgb);
//            int gray=(r+g+b)/3;
            ret.setPixel(i,j,qRgb(r,g,b));
        }
    }
    return ret;
}

QImage ImageProcessor::logTransmation(const QImage &img,double c)
{
    QImage ret=rgb2gray(img);
    int width = ret.width();
    int height = ret.height();
    for(int i=0;i<width;i++)
    {
        for(int j=0;j<height;j++)
        {
            QRgb rgb=ret.pixel(i,j);
            int g = qRed(rgb);
            int ng= (c*log(1+g/255.0))*255;
            if(ng>255)
                ng=255;
            ret.setPixel(i,j,qRgb(ng,ng,ng));
        }
    }
    return ret;
}


QImage ImageProcessor::histEq(const QImage &img)
{
    QImage ret(img);
    int width = img.width();
    int height= img.height();
    int N= width*height;

    //count histogram
    int hist[256];
    std::fill(hist,hist+256,0);
    for(int i=0;i<width;i++)
    {
        for(int j=0;j<height;j++)
        {
            hist[qGray(img.pixel(i,j))]++;
        }
    }

    //calculate map function
            int map[256];
            double sum = 0;
            for(int i=0;i<256;i++)
            {
                sum+=hist[i];
                map[i]= round(sum / N*255);
            }

     //map the pixcal
            for(int i=0;i<width;i++)
            {
                for(int j=0;j<height;j++)
                {
                    int g = map[qGray(img.pixel(i,j))];
                    ret.setPixel(i,j,qRgb(g,g,g));
                }
            }
      return ret;
}


QImage ImageProcessor::colorHisteq1(const QImage &img)
{
    QImage ret(img);//copy
    int width = img.width();
    int height= img.height();
    int N= width*height;

    //count histogram
    int hist[3][256];//R G B
    std::fill(hist[0],hist[0]+3*256,0);//初始值 填充为0，！256
    for(int i=0;i<width;i++)
    {
        for(int j=0;j<height;j++)
        {
            hist[0][qRed(img.pixel(i,j))]++;
            hist[1][qGreen(img.pixel(i,j))]++;
            hist[2][qBlue(img.pixel(i,j))]++;
        }
    }

    //calculate map function
            int map[3][256];
            double sumR = 0;
            double sumG = 0;
            double sumB = 0;
            for(int i=0;i<256;i++)
            {
                sumR+=hist[0][i];//R通道的总值
                map[0][i]= round(sumR / N*255);//均衡计算

                sumG+=hist[1][i];
                map[1][i]= round(sumG / N*255);

                sumB+=hist[2][i];
                map[2][i]= round(sumB / N*255);
            }

     //map the pixcal
            for(int i=0;i<width;i++)
            {
                for(int j=0;j<height;j++)
                {
                    int r = map[0][qRed(img.pixel(i,j))];
                    int g = map[1][qGreen(img.pixel(i,j))];
                    int b = map[2][qBlue(img.pixel(i,j))];
                    ret.setPixel(i,j,qRgb(r,g,b));
                }
            }
      return ret;
}

QImage ImageProcessor::hsi(const QImage&img)
{
    QImage ret(img);//copy
    int width =ret.width();
    int height=ret.height();
    long N =width*height;

    //RGB2HSI
    HSI* Hsi=new HSI[N];
    for(int i=0;i<width;i++)
    {
        for(int j=0;j<height;j++)
        {
            QRgb rgb = ret.pixel(i,j);
            Hsi[i*height+j] = HSI();
            rgb2hsi(rgb,Hsi[i*height+j]);
        }
    }

    //count histogram of I
    int hist[256];
    std::fill(hist,hist+256,0);
    for(int i=0;i<N;i++)
        hist[int(Hsi[i].i)]++;

    //calculate map function
    int map[256];
    cumulateHist(hist,map,N);

    //map the pixcel
    for(int i=0;i<N;i++)
        Hsi[i].i=map[int(Hsi[i].i)];

    //HSI to RGB
    for(int i=0;i<width;i++)
        for(int j=0;j<height;j++)
        {
            QRgb rgb;
            hsi2rgb(rgb,Hsi[i*height+j]);
            ret.setPixel(i,j,rgb);
        }

    //clear memory
    delete Hsi;

    return ret;
}

////////////////////////////////////////////////////////////////////////////////
QImage ImageProcessor::zeroPadding(const QImage& img,int nCol,int nRow)
{
    QImage ret(img.width() + nCol - 1 ,img.height() + nRow - 1,img.format());
    int width = ret.width();
    int height = ret.height();
    for(int i = 0;i<width;++i)
    {
        for(int j = 0;j<height;++j)
        {
            if(i<nCol/2 || i>=width - nCol/2 ||
                    j<nRow/2 ||j>=height - nRow/2)
                ret.setPixel(i,j,qRgb(0,0,0));
            else
                ret.setPixel(i,j,img.pixel(i-nCol/2,j-nRow/2));
        }
    }
    cout<<"zeroPadding"<<endl;
    return ret;
}

QImage ImageProcessor::zeroPadding_repeat(const QImage& img,int nCol,int nRow)
{
    QImage ret(img.width() + nCol - 1 ,img.height() + nRow - 1,img.format());
    int width  = img.width();
    int height = img.height();
    int Width  = ret.width();
    int Height = ret.height();
    for(int i = 0;i<Width;++i)
    {
        for(int j = 0;j<Height;++j)
        {
            //第一行
            if(i<nCol/2 && j<nRow/2)
                ret.setPixel(i,j,img.pixel(i+width-nCol/2,j+height-nRow/2));
            if(i>=nCol/2 && i<width+nCol/2 &&j<nRow/2)
                ret.setPixel(i,j,img.pixel(i-nCol/2,j+height-nRow/2));
            if(i>=width+nCol/2 &&j<nRow/2)
                ret.setPixel(i,j,img.pixel(i-width-nCol/2,j+height-nRow/2));
            //第二行
            if(i<nCol/2 && j>=nRow/2 && j<height+nRow/2)
                ret.setPixel(i,j,img.pixel(i+width-nCol/2,j-nRow/2));
            if(i>=nCol/2 && i<width+nCol/2 && j>=nRow/2 && j<height+nRow/2)
                ret.setPixel(i,j,img.pixel(i-nCol/2,j-nRow/2));
            if(i>=width+nCol/2 && j>=nRow/2 && j<height+nRow/2)
                ret.setPixel(i,j,img.pixel(i-width-nCol/2,j-nRow/2));
            //第三行
            if(i<nCol/2 && j>=height+nRow/2 )
                ret.setPixel(i,j,img.pixel(i+width-nCol/2,j-height-nRow/2));
            if(i>=nCol/2 && i<width+nCol/2 &&j>=height+nRow/2 )
                ret.setPixel(i,j,img.pixel(i-nCol/2,j-height-nRow/2));
            if(i>=width+nCol/2 &&j>=height+nRow/2)
                ret.setPixel(i,j,img.pixel(i-width-nCol/2,j-height-nRow/2));
        }
    }
    cout<<"zeroPadding"<<endl;
    return ret;
}

QImage ImageProcessor::zeroPadding_mirror(const QImage& img,int nCol,int nRow)
{
   QImage ret(img.width() + nCol - 1 ,img.height() + nRow - 1,img.format());
   int width  = img.width();
   int height = img.height();
   int Width  = ret.width();
   int Height = ret.height();

   QImage mirror_image1=img.mirrored(false,true);
   QImage mirror_image2=img.mirrored(true,false);
   QImage mirror_image3=img.mirrored(true,true);

   for(int i = 0;i<Width;++i)
      {
            for(int j = 0;j<Height;++j)
            {
                //第一行
                if(i<nCol/2 && j<nRow/2)
                {
                    ret.setPixel(i,j,mirror_image3.pixel(i+width-nCol/2,j+height-nRow/2));
                }
                if(i>=nCol/2 && i<width+nCol/2 &&j<nRow/2)
                {
                    ret.setPixel(i,j,mirror_image1.pixel(i-nCol/2,j+height-nRow/2));
                }
                if(i>=width+nCol/2 &&j<nRow/2)
                {
                    ret.setPixel(i,j,mirror_image3.pixel(i-width-nCol/2,j+height-nRow/2));
                }
                //第二行
                if(i<nCol/2 && j>=nRow/2 && j<height+nRow/2)
                {
                    ret.setPixel(i,j,mirror_image2.pixel(i+width-nCol/2,j-nRow/2));
                }
                if(i>=nCol/2 && i<width+nCol/2 && j>=nRow/2 && j<height+nRow/2)
                {
                    ret.setPixel(i,j,img.pixel(i-nCol/2,j-nRow/2));
                }
                if(i>=width+nCol/2 && j>=nRow/2 && j<height+nRow/2)
                {
                    ret.setPixel(i,j,mirror_image2.pixel(i-width-nCol/2,j-nRow/2));
                }
                //第三行
                if(i<nCol/2 && j>height+nRow/2 )
                {
                    ret.setPixel(i,j,mirror_image3.pixel(i+width-nCol/2,j-height-nRow/2));
                }
                if(i>=nCol/2 && i<width+nCol/2 &&j>height+nRow/2 )
                {
                    ret.setPixel(i,j,mirror_image1.pixel(i-nCol/2,j-height-nRow/2));
                }
                if(i>=width+nCol/2 &&j>height+nRow/2)
                {
                    ret.setPixel(i,j,mirror_image3.pixel(i-width-nCol/2,j-height-nRow/2));
                }
            }
        }
        cout<<"zeroPadding"<<endl;
        return ret;
    }

QImage ImageProcessor::linearRgbFilter(const QImage& img, std::vector<double> kernel, int nCol)
{
    cout<<"enter linearRgbFilter finished"<<endl;
    int nRow =kernel.size()/nCol;
    if(0 == nRow%2 || 0== nCol%2) return img;
    //padding
//   QImage padded=zeroPadding(img,nCol,nRow);
//      QImage padded=zeroPadding_repeat(img,nCol,nRow);
    QImage padded=zeroPadding_mirror(img,nCol,nRow);
    cout<<"zeroPadding finished"<<endl;
    //filterRgb
    QImage filtered=filterRgb(padded,kernel,nCol,nRow);
     cout<<"filterRgb finished"<<endl;
    //crop
    QImage croped =crop(filtered,nCol,nRow);
     cout<<"crop finished"<<endl;
    return croped;
}

QImage ImageProcessor::linearGrayFilter(const QImage& img, std::vector<double> kernel, int nCol)
{
    cout<<"enter linearGrayFilter finished"<<endl;
    int nRow =kernel.size()/nCol;
    if(0 == nRow%2 || 0== nCol%2) return img;
    //padding
    QImage padded=zeroPadding(img,nCol,nRow);
    cout<<"zeroPadding finished"<<endl;
    //filter
    QImage filtered=filterGray(padded,kernel,nCol,nRow);
     cout<<"filterGray finished"<<endl;
    //crop
    QImage croped =crop(filtered,nCol,nRow);
     cout<<"crop finished"<<endl;
    return croped;
}

//RGB线性滤波
QImage ImageProcessor::filterRgb(const QImage& img,std::vector<double>& kernel,int nCol,int nRow)
{
    QImage ret(img);
    int width = img.width();
    int height = img.height();
    for(int i = nCol/2;i<width - nCol/2;++i)
    {
        for(int j = nRow/2;j<height - nRow/2;++j)
        {
            std::vector<int> patchR = getPatch(img,i,j,nCol,nRow,'r');
            std::vector<int> patchG = getPatch(img,i,j,nCol,nRow,'g');
            std::vector<int> patchB = getPatch(img,i,j,nCol,nRow,'b');
            double sumR = 0,sumG = 0,sumB = 0;
            for(int k = 0;k<kernel.size();++k)
            {
                sumR += kernel[k]*patchR[k];
                sumG += kernel[k]*patchG[k];
                sumB += kernel[k]*patchB[k];
            }
            int r = (int)sumR;
            int g = (int)sumG;
            int b = (int)sumB;
            if(r>255) r = 255;
            if(g>255) g = 255;
            if(b>255) b = 255;
            if(r<0) r = 0;
            if(g<0) g = 0;
            if(b<0) b = 0;
            ret.setPixel(i,j,qRgb(r,g,b));
        }
    }
    cout<<"filterRgb!"<<endl;
    return ret;
}

//GRAY线性滤波
QImage ImageProcessor::filterGray(const QImage &img, std::vector<double> & kernel, int nCol, int nRow)
{
    QImage ret(img);
    int width = img.width();
    int height = img.height();
    for(int i = nCol/2;i<width - nCol/2;++i)
    {
        for(int j = nRow/2;j<height - nRow/2;++j)
        {
            std::vector<int> patchG = getPatch(img,i,j,nCol,nRow,'y');
            double sumG=0;
            for(int k = 0;k<kernel.size();++k)
            {
                sumG += kernel[k]*patchG[k];
            }
            int g = (int)sumG;
            if(g>255) g = 255;
            if(g<0) g = 0;
            ret.setPixel(i,j,qRgb(g,g,g));
        }
    }
    cout<<"filterGray!"<<endl;
    return ret;
}

std::vector<int> ImageProcessor::getPatch(const QImage& img,int w,int h,int nCol,int nRow,char c)
{
    std::vector<int> ret;
    for(int i = w - nCol/2;i<=w + nCol/2;++i)
    {
        for(int j = h - nRow/2;j<=h + nRow/2;++j)
        {
            switch (c)
            {
            case 'r':
                ret.push_back(qRed(img.pixel(i,j)));
                break;
            case 'g':
                ret.push_back(qGreen(img.pixel(i,j)));
                break;
            case 'b':
                ret.push_back(qBlue(img.pixel(i,j)));
                break;
            case 'y':
                ret.push_back(qGray(img.pixel(i,j)));
                break;
            default:
                break;
            }
        }
    }
    cout<<"getPatch!"<<endl;
    return ret;
}

QImage ImageProcessor::crop(const QImage& img,int nCol,int nRow)
{
    QImage ret(img.width() - nCol + 1,img.height() - nRow + 1,img.format());
    int width = ret.width();
    int height = ret.height();
    for(int i = 0;i<width;++i)
    {
        for(int j = 0;j<height;++j)
        {
            ret.setPixel(i,j,img.pixel(i + nCol/2,j + nRow/2));
        }
    }
    cout<<"crop!"<<endl;
    return ret;
}

//归一化
void ImageProcessor::KernelNormalization(std::vector<double>& kernel)
{
    double sum = 0;
    for(int i = 0;i<kernel.size();++i)
    {
        sum += kernel[i];
    }
    if(0!=sum)
    {
        for(int i = 0;i<kernel.size();++i)
        {
            kernel[i] /= sum;
        }
    }
}
//gaussRgbBlur
QImage ImageProcessor::gaussRgbBlur(const QImage& img, int size, double sigma)
{
    std::vector<double> kernel = creatGaussKernel(size,sigma);
    KernelNormalization(kernel);
    return linearRgbFilter(img,kernel,size);
}

//gaussGrayBlur
QImage ImageProcessor::gaussGrayBlur(const QImage& img, int size, double sigma)
{
    std::vector<double> kernel = creatGaussKernel(size,sigma);
    KernelNormalization(kernel);
    return linearGrayFilter(img,kernel,size);
}

//创建Gauss变换矩阵
std::vector<double> ImageProcessor::creatGaussKernel(int size, double sigma)
{
    std::vector<double> ret;
    for(int i=0;i<size;i++)
    {
        for (int j=0;j<size;j++)
        {
            int deltaX = abs(i-size/2);
            int deltaY = abs(i-size/2);
            ret.push_back(exp((-deltaX*deltaX-deltaY*deltaY)/(2*sigma*sigma)));
        }
    }
    return ret;
}


QImage ImageProcessor::bilateralFilter(const QImage& img, int size, double sigmaColor, double sigmaSpace)
{
    //padding
    QImage padded = zeroPadding(img,size,size);

    //pre-calculate
    std::vector<double> kernelSpace = creatGaussKernel(size,sigmaSpace);
    std::vector<double> kernelColor = creatBilateralKernel(sigmaColor);

    //filter
    QImage filtered(padded);
    int width = padded.width();
    int height=padded.height();
    for(int i=size/2;i<width-size/2;i++)
    {
        for(int j=size/2;j<height-size/2;j++)
        {
           std::vector<int> patch = getPatch(padded,i,j,size,size,'y');
           std::vector<double> kernel;
           for(int k=0;k<kernelSpace.size();k++)
           {
               int delta = abs(patch[k]-qGray(padded.pixel(i,j)));
               kernel.push_back(kernelColor[delta]*kernelSpace[k]);
           }
           KernelNormalization(kernel);
           double sum=0;
           for(int k=0;k<kernelSpace.size();k++)
           {
               sum += kernel[k]*patch[k];
           }
           int y=(int)sum;
           if(y>255) y=255;
           filtered.setPixel(i,j,qRgb(y,y,y));
        }
    }

    //crop
    QImage croped = crop(filtered,size,size);
    return croped;
}

std::vector<double> ImageProcessor::creatBilateralKernel(double sigmaColor)
{
    std::vector<double> ret;
    for(int i=0;i<256;i++)
    {
        ret.push_back(exp((-i*i)/(2*sigmaColor*sigmaColor)));
    }
    return ret;
}

//RGB中值滤波
QImage ImageProcessor::medianRgbFilter(const QImage &img, double m)
{
    //m就是size
    if(0==m) return img;
    QImage padded = zeroPadding(img,m,m);
    QImage filtered(padded);
    int width = padded.width();
    int height = padded.height();
    for(int i=m/2;i<width-m/2;i++)
    {
        for(int j=m/2;j<height-m/2;j++)
        {
            std::vector<int> patchR=getPatch(padded,i,j,m,m,'r');
            std::vector<int> patchG=getPatch(padded,i,j,m,m,'g');
            std::vector<int> patchB=getPatch(padded,i,j,m,m,'b');
            std::sort(patchR.begin(),patchR.end());
            std::sort(patchG.begin(),patchG.end());
            std::sort(patchB.begin(),patchB.end());
            int r=patchR.at(patchR.size()/2);
            int g=patchG.at(patchG.size()/2);
            int b=patchB.at(patchB.size()/2);
            filtered.setPixel(i,j,qRgb(r,g,b));
        }
    }

    //crop
    QImage croped=crop(filtered,m,m);
    return croped;
}

//Gray中值滤波
QImage ImageProcessor::medianGrayFilter(const QImage &img, double m)
{
    //m就是size
    if(0==m) return img;
    QImage padded = zeroPadding(img,m,m);
    QImage filtered(padded);
    int width = padded.width();
    int height = padded.height();
    for(int i=m/2;i<width-m/2;i++)
    {
        for(int j=m/2;j<height-m/2;j++)
        {
            std::vector<int> patch=getPatch(padded,i,j,m,m,'y');//?
            std::sort(patch.begin(),patch.end());
            int y=patch.at(patch.size()/2);
            filtered.setPixel(i,j,qRgb(y,y,y));
        }
    }

    //crop
    QImage croped=crop(filtered,m,m);
    return croped;
}

//RGB膨胀
QImage ImageProcessor::expandRgbFilter(const QImage &img, double e)
{
    cout<<"ExpandRgb start"<<endl;
    //e就是size
    if(0==e) return img;
    QImage padded = zeroPadding(img,e,e);
    QImage filtered(padded);
    int width = padded.width();
    int height = padded.height();
    for(int i=e/2;i<width-e/2;i++)
    {
        for(int j=e/2;j<height-e/2;j++)
        {
            std::vector<int> patchR=getPatch(padded,i,j,e,e,'r');
            std::vector<int> patchG=getPatch(padded,i,j,e,e,'g');
            std::vector<int> patchB=getPatch(padded,i,j,e,e,'b');
            std::sort(patchR.begin(),patchR.end());
            std::sort(patchG.begin(),patchG.end());
            std::sort(patchB.begin(),patchB.end());
            int r=patchR.at(patchR.size()-1);
            int g=patchG.at(patchG.size()-1);
            int b=patchB.at(patchB.size()-1);
            filtered.setPixel(i,j,qRgb(r,g,b));
        }
    }

    //crop
    QImage croped=crop(filtered,e,e);
    return croped;
}

//Gray膨胀
QImage ImageProcessor::expandGrayFilter(const QImage &img, double co)
{
    cout<<"ExpandGray start"<<endl;
    //e就是size
    if(0==co) return img;
    QImage padded = zeroPadding(img,co,co);
    QImage filtered(padded);
    int width = padded.width();
    int height = padded.height();
    for(int i=co/2;i<width-co/2;i++)
    {
        for(int j=co/2;j<height-co/2;j++)
        {

            std::vector<int> patch=getPatch(padded,i,j,co,co,'y');
            std::sort(patch.begin(),patch.end());
            int y=patch.at(patch.size()-1);
            filtered.setPixel(i,j,qRgb(y,y,y));
        }
    }

    //crop
    QImage croped=crop(filtered,co,co);
    return croped;
}

//Rgb腐蚀
QImage ImageProcessor::corrosionRgbFilter(const QImage &img, double co)
{
    if(0==co) return img;
    QImage padded = zeroPadding(img,co,co);
    QImage filtered(padded);
    int width = padded.width();
    int height = padded.height();
    for(int i=co/2;i<width-co/2;i++)
    {
        for(int j=co/2;j<height-co/2;j++)
        {
            std::vector<int> patchR=getPatch(padded,i,j,co,co,'r');
            std::vector<int> patchG=getPatch(padded,i,j,co,co,'g');
            std::vector<int> patchB=getPatch(padded,i,j,co,co,'b');
            std::sort(patchR.begin(),patchR.end());
            std::sort(patchG.begin(),patchG.end());
            std::sort(patchB.begin(),patchB.end());
//            int r=patchR.at(patchR[0]);
//            int g=patchG.at(patchG[0]);
//            int b=patchB.at(patchB[0]);
            int r=patchR[0];
            int g=patchG[0];
            int b=patchB[0];
            filtered.setPixel(i,j,qRgb(r,g,b));
        }
    }
    //crop
    QImage croped=crop(filtered,co,co);
    return croped;
}

//Gray腐蚀
QImage ImageProcessor::corrosionGrayFilter(const QImage &img, double co)
{
    if(0==co) return img;
    QImage padded = zeroPadding(img,co,co);
//    QImage padded = zeroPadding_repeat(img,co,co);
//        QImage padded = zeroPadding_mirror(img,co,co);
    QImage filtered(padded);
    int width = padded.width();
    int height = padded.height();
    for(int i=co/2;i<width-co/2;i++)
    {
        for(int j=co/2;j<height-co/2;j++)
        {

            std::vector<int> patch=getPatch(padded,i,j,co,co,'y');
            std::sort(patch.begin(),patch.end());
//            int y=patch.at(patch[0]);
            int y = patch[0];
            filtered.setPixel(i,j,qRgb(y,y,y));
        }
    }

    //crop
    QImage croped=crop(filtered,co,co);
    return croped;
}

/* ***************************************/
void ImageProcessor::getRange(const QMatrix &matrix, const QImage &img,double &minX,  double &maxX, double &minY,  double &maxY)
{
    // get four points in transformed image
    std::vector<qreal> vx(4),vy(4);
    matrix.map(0,0,&vx[0],&vy[0]);
    matrix.map(0,img.height()-1,&vx[1],&vy[1]);
    matrix.map(img.width()-1,0,&vx[2],&vy[2]);
    matrix.map(img.width()-1,img.height()-1,&vx[3],&vy[3]);

    // sort x and y
    for (int i =1;i <= 3;++i){
            for(int j = i;j > 0;--j){
                if(vx[j] < vx[j -1]){
                    qreal temp = vx[j];
                    vx[j] = vx[j - 1];
                    vx[j - 1] = temp;
                }
            }
        }

    for (int i =1;i <= 3;++i){
            for(int j = i;j > 0;--j){
                if(vy[j] < vy[j -1]){
                    qreal temp = vy[j];
                    vy[j] = vy[j - 1];
                    vy[j - 1] = temp;
                }
            }
        }

    // get the min and max of x and y
    minX = vx[0];
    minY = vy[0];
    maxX = vx[3];
    maxY = vy[3];
}

QRgb ImageProcessor::getNewRgb(const QMatrix &matrix, const QImage &img, const int i, const int j, const double minX, const double minY)
{
    // get the position in origal image
    double srcX,srcY;
    matrix.map(i+minX,j+minY,&srcX,&srcY);
    // if it is out of the original image
    if(srcX<0 || srcX>img.width()-1 || srcY<0 || srcY>img.height()-1)
    {
        return qRgb(0,0,0);
    }

    // get RGB by bilinear interpolation
    else
    {
        return bilinear(img,srcX,srcY);
    }
}

double ImageProcessor::linear_inter(const double v1,const double v2,const double c1,const double c2,const double c3)
{
    if(c1 == c2)
        return v1;
    // follow the formula of linear interpolation
    return (c2-c3)/(c2-c1)*v1+(c3-c1)/(c2-c1)*v2;
}

QRgb ImageProcessor::bilinear(const QImage &img,const double x,const double y)
{
    // get four pixels
    int x1 = ceil(x);
    int x2 = floor(x);
    int y1 = ceil(y);
    int y2 = floor(y);
    QRgb rgb1 = img.pixel(x1,y1);
    QRgb rgb2 = img.pixel(x1,y2);
    QRgb rgb3 = img.pixel(x2,y1);
    QRgb rgb4 = img.pixel(x2,y2);


    // bilinear on red
    double temp1,temp2;
    temp1 = linear_inter(qRed(rgb1),qRed(rgb2),y1,y2,y);
    temp2 = linear_inter(qRed(rgb3),qRed(rgb4),y1,y2,y);
    double r = linear_inter(temp1,temp2,x1,x2,x);

    //bilinear on green
    temp1 = linear_inter(qGreen(rgb1),qGreen(rgb2),y1,y2,y);
    temp2 = linear_inter(qGreen(rgb3),qGreen(rgb4),y1,y2,y);
    double g = linear_inter(temp1,temp2,x1,x2,x);

    //bilinear on blue
    temp1 = linear_inter(qBlue(rgb1),qBlue(rgb2),y1,y2,y);
    temp2 = linear_inter(qBlue(rgb3),qBlue(rgb4),y1,y2,y);
    double b= linear_inter(temp1,temp2,x1,x2,x);

    return qRgb(r,g,b);
}

QImage ImageProcessor::transform(const QImage &img, const QMatrix &matrix)
{
    // check if tform is invertible
    bool invertible = true;
    QMatrix inv_matrix = matrix.inverted(&invertible);
    if (!invertible)    return img;

    // determine the size of new image
    double minX, maxX, minY, maxY;
    getRange(matrix,img, minX, maxX, minY, maxY);

    // and create new QImage
    int newWidth = ceil(maxX-minX);
    int newHeight = ceil(maxY-minY);
    QImage newImg( newWidth, newHeight, img.format());

    // backward map per pixel
    for(int i=0;i<newWidth;++i)
    {
        for(int j=0;j<newHeight;++j)
        {
            QRgb newRgb = getNewRgb(inv_matrix,img, i, j, minX, minY);
            newImg.setPixel(i,j, newRgb);
        }
    }

    return newImg;
}

QVector<double> ImageProcessor::computeEveryDistance(const double anotherSigma){
    QVector<double> dis;

    for(int i = 0; i < 255; i++){
        dis.push_back(exp(- ((i * i) / (2 * anotherSigma * anotherSigma))));
    }
    return dis;
}

QVector<QVector<double> > ImageProcessor::computeGaussFilter(const int filterSize, const double sigma){

    QVector<QVector<double> > kernel;
    for(int i = 0; i < filterSize; i++){
        QVector<double> line;
        for(int j = 0; j < filterSize; j++){

            double x = (i - filterSize/2) * (i - filterSize/2);
            double y = (j - filterSize/2) * (j - filterSize/2);

            line.push_back(exp(-((x + y) / 2 / sigma / sigma)));
        }
        kernel.push_back(line);
    }

    double sum = 0;
    for(int i = 0; i < filterSize; i++){
        for(int j = 0; j < filterSize; j++){
            sum += kernel[i][j];
        }
    }

    for(int i = 0; i < filterSize; i++){
        for(int j = 0; j < filterSize; j++){
            kernel[i][j] /= sum;
        }
    }

    return kernel;
}

void ImageProcessor::filterNormalization(QVector<QVector<double> > & vec, const int nCOl){

    double sum = 0;
    for(int i = 0; i < vec.length(); i++){
        for(int j = 0; j < nCOl; j++){
            sum += vec[i][j];
        }
    }

    // 对于锐化滤波器，算子和为0
    if(sum == 0){
        return;
    }

    for(int i = 0; i < vec.length(); i++){
        for(int j = 0; j < nCOl; j++){
            vec[i][j] /= sum;
        }
    }
}

