#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QImage>
#include <QLabel>
#include <QDebug>
#include <QStringList>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QRegExp>

#include "mypixmapitem.h"
#include "imageprocessor.h"

#include "loginformation.h"
//#include "lineardialog.h"
//#include "gaussdialog.h"
#include "bilateraldialog.h"
//#include "mediandialog.h"
#include "expanddialog.h"
#include "corrosiondialog.h"
#include "linearrgbdialog.h"
#include "lineargraydialog.h"
#include "gaussrgbdialog.h"
#include "gaussgraydialog.h"
#include "medianrgbdialog.h"
#include "mediangraydialog.h"
#include "expandrgbdialog.h"
#include "expandgraydialog.h"
#include "corrosionrgbdialog.h"
#include "corrosiongraydialog.h"

#include "fft.h"
#include "matrixTemplate.h"
#include "affine.h"

#include "hpdialog.h"
#include "lpdialog.h"

#include <iostream>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_OPEN_clicked();

    void on_RESET_clicked();

    void on_lastImg_clicked();

    void on_nextImg_clicked();

    void on_actionRgb2gray_triggered();

    void on_actionReverse_triggered();

    void on_saveBtn_clicked();

    //点击弹出Log对话框
    void on_actionLog_transformation_triggered();
    void on_ItDlg_confirmed_triggered(double c);

//    //点击Linear弹出对话框
//    void on_action_Linear_triggered();
//    void on_ItDlg2_confirmed(QString l);

    //点击弹出LinearRGB对话框
    void on_actionRGB_triggered();
    void on_linearRgbDialog_confirmed(QString l);

//    vector<double> parseMatrixl(QString,int&);
    vector<double> parseMatrixl2(QString,int&);
    bool readOneRow(QString,std::vector<double>&kernel,int);

    //点击弹出LinearGRAY对话框
    void on_actionGRAY_triggered();
    void on_linearGrayDialog_confirmed(QString l);


//    //点击Gauss弹出对话框
//    void on_actionGauss_blur_triggered();
//    void on_gaussDialog_confirmed(int size,double sigma);

    //点击弹出GaussRGB对话框
    void on_actionRGB_GAUSS_triggered();
    void on_gaussRgbDialog_confirmed(int size,double sigma);

    //点击弹出GaussGRAY对话框
    void on_actionGRAY_GAUSS_triggered();
    void on_gaussGrayDialog_confirmed(int size,double sigma);


    //点击bilateral弹出对话框
    void on_actionBilateral_triggered();
    void on_bilateralDialog_confirmed(int size,double sigmaColor,double sigmaSpace);

//    //点击Median弹出对话框
//    void on_actionMedian_triggered();
//    void on_mediandialog_confirmed(double m);

    //点击MedianRGB弹出对话框
    void on_actionRGB_Median_triggered();
    void on_medianRgbdialog_confirmed(double m);

    //点击MedianGray弹出对话框
    void on_actionGRAY_Median_triggered();
    void on_medianGraydialog_confirmed(double m);


//    //点击Expand弹出对话框
//    void on_actionExpand_triggered();
//    void on_expanddialog_confirmed(double e);

    //点击ExpandRGB弹出对话框
    void on_actionRGB_Expand_triggered();
    void on_expandRgbdialog_confirmed(double e);

    //点击ExpandGray弹出对话框
    void on_actionGRAY_Expand_triggered();
    void on_expandGraydialog_confirmed(double e);


//    //点击Corrision弹出对话框
//    void on_actionCorrosion_triggered();
//    void on_corrosiondialog_confirmed(double co);

    //点击CorrisionRGB弹出对话框
    void on_actionRGB_Corrosion_triggered();
    void on_corrosionRgbdialog_confirmed(double co);

    //点击CorrisionGray弹出对话框
    void on_actionGRAY_Corrosion_triggered();
    void on_corrosionGraydialog_confirmed(double co);


    void on_actionHistEq_triggered();

    void on_actionColor_histeq1_triggered();

    void on_actionHsi_triggered();

    //点击affine Transformation弹出对话框
    void on_actionAlline_Transformation_triggered();
    void on_affineDialog_confirmed(QMatrix matrix);

    //点击进行FFT操作
    void on_actionFFT_triggered();

    //点击进行IFFT操作
    void on_actionIFFT_triggered();

    //点击High Pass弹出对话框
    void on_actionHighPass_triggered();
    void on_hpdialog_confirmed(double c);

    //点击Low Pass弹出对话框
    void on_actionLowPass_triggered();
    void on_lpdialog_confirmed(double c);



private:
    Ui::MainWindow *ui;
//    QGraphicsPixmapItem *gpi;
    MyPixmapItem *gpi;
    QGraphicsScene *gs;
    QFileDialog *fileDlg;

    QFileInfoList images;
    int curIdx;

    void showImage(QImage img);

    void reset();

    bool getDisplayImage(QImage &img) const;

    logInformation *ItDlg;
//    LinearDialog *ItDlg2;
    LinearRgbDialog  *linearRgbDialog;
    LinearGrayDialog *linearGrayDialog;

//    GaussDialog *gaussDialog;
    GaussRgbDialog *gaussRgbDialog;
    GaussGrayDialog *gaussGrayDialog;

    bilateralDialog *bilateraldialog;

//    MedianDialog *mediandialog;
    MedianRgbDialog *medianRgbDialog;
    MedianGrayDialog *medianGrayDialog;

//    ExpandDialog *expanddialog;
    ExpandRgbDialog *expandRgbDialog;
    ExpandGrayDialog *expandGrayDialog;

//    CorrosionDialog *corrosiondialog;
    CorrosionRgbDialog *corrosionRgbDialog;
    CorrosionGrayDialog *corrosionGrayDialog;

//    affine
    affine *affineDialog;

    hpDialog *hpdialog;
    lpDialog *lpdialog;

    QVector<QVector<double> > getFilterData(QString &str, int &colNum);
    QVector<double> getFilterDataOfEveryLine(QString &str, int &colNum);

};

#endif // MAINWINDOW_H
