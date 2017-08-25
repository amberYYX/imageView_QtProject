#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets/QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    gpi(NULL),//初始界面时，不需要对gpi、gs进行构建
    gs(NULL),//在使用时再实例，申请内存，由此可避免浪费内存
    fileDlg(new QFileDialog),
    ItDlg(new logInformation(this)),
//    ItDlg2(new LinearDialog(this)),
    linearRgbDialog(new LinearRgbDialog(this)),
    linearGrayDialog(new LinearGrayDialog(this)),
//    gaussDialog(new GaussDialog(this)),
    gaussRgbDialog(new GaussRgbDialog(this)),
    gaussGrayDialog(new GaussGrayDialog(this)),
    bilateraldialog(new bilateralDialog(this)),
//    mediandialog(new MedianDialog(this)),
    medianRgbDialog(new MedianRgbDialog(this)),
    medianGrayDialog(new MedianGrayDialog(this)),
//    expanddialog(new ExpandDialog(this)),
    expandRgbDialog(new ExpandRgbDialog(this)),
    expandGrayDialog(new ExpandGrayDialog(this)),
//    corrosiondialog(new CorrosionDialog(this)),
    corrosionRgbDialog(new CorrosionRgbDialog(this)),
    corrosionGrayDialog(new CorrosionGrayDialog(this)),
    affineDialog(new affine(this)),
    lpdialog(new lpDialog(this)),
    hpdialog(new hpDialog(this)),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ItDlg,SIGNAL(confirmed(double)),
            this,SLOT(on_ItDlg_confirmed_triggered(double)));

    connect(linearRgbDialog,SIGNAL(confirmed(QString)),
            this,SLOT(on_linearRgbDialog_confirmed(QString)));

    connect(linearGrayDialog,SIGNAL(confirmed(QString)),
            this,SLOT(on_linearGrayDialog_confirmed(QString)));

    connect(gaussRgbDialog,SIGNAL(confirmed(int,double)),
            this,SLOT(on_gaussRgbDialog_confirmed(int,double)));

    connect(gaussGrayDialog,SIGNAL(confirmed(int,double)),
            this,SLOT(on_gaussGrayDialog_confirmed(int,double)));

    connect(bilateraldialog,SIGNAL(confirmed(int,double,double)),
            this,SLOT(on_bilateralDialog_confirmed(int,double,double)));

    connect(medianRgbDialog,SIGNAL(confirmed(double)),
            this,SLOT(on_medianRgbdialog_confirmed(double)));

    connect(medianGrayDialog,SIGNAL(confirmed(double)),
            this,SLOT(on_medianGraydialog_confirmed(double)));

    connect(expandRgbDialog,SIGNAL(confirmed(double)),
            this,SLOT(on_expandRgbdialog_confirmed(double)));

    connect(expandGrayDialog,SIGNAL(confirmed(double)),
            this,SLOT(on_expandGraydialog_confirmed(double)));

    connect(corrosionRgbDialog,SIGNAL(confirmed(double)),
            this,SLOT(on_corrosionRgbdialog_confirmed(double)));

    connect(corrosionGrayDialog,SIGNAL(confirmed(double)),
            this,SLOT(on_corrosionGraydialog_confirmed(double)));

    connect(affineDialog,SIGNAL(confirmed(QMatrix)),
            this,SLOT(on_affineDialog_confirmed(QMatrix)));

    connect(hpdialog,SIGNAL(confirmed(double)),
            this,SLOT(on_hpdialog_confirmed(double)));

    connect(lpdialog,SIGNAL(confirmed(double)),
            this,SLOT(on_lpdialog_confirmed(double)));
}

MainWindow::~MainWindow()
{
    delete gpi;
    delete gs;//按照层级顺序进行delete
    delete fileDlg;
    delete ItDlg;
    delete ui;

}

void MainWindow::on_OPEN_clicked()
{
    if (fileDlg->exec())
        {
        QStringList files=fileDlg->selectedFiles();
        files<<"*.jpg"<<"*.bmp"<<"*.png";

        QDir dir=fileDlg->directory();
        images=dir.entryInfoList(files);
            for(int i = 0;i < images.length();i ++)
            {
            if(images[i].absoluteFilePath()==files[0])
                curIdx=i;
            }

            QImage img=QImage(files[0]);
            showImage(img);
        }
}

void MainWindow::showImage(QImage img)
{
    if(NULL!=gpi) //等价于gpi~=NULL的判断，但可避免人为失误导致的错误
    {
        delete gpi;
        gpi=NULL;
        //每次打开新文件，如果原来已有图片，自动删除,
        //以此来节省内存空间
    }

    if(NULL!=gs)
    {
        delete gs;
        gs=NULL;
    }
//    gpi=new QGraphicsPixmapItem();
    gpi=new MyPixmapItem();
    gpi->setPixmap(QPixmap::fromImage(img));

    gs=new QGraphicsScene();
    gs->addItem(gpi);

    ui->graphicsView->setScene(gs);

    reset();
}

void MainWindow::on_RESET_clicked()
{
    reset();
}

void MainWindow::reset()
{

    // 若当前没有图片显示
        if(NULL == gpi){
            return;
        }

        // 调用gpi的初始化函数
        gpi->itemReset();

        // QGraphics大小自适应
        gs->setSceneRect(gpi->boundingRect());
        // graphicsView的自适应
        ui->graphicsView->fitInView(gpi->boundingRect(), Qt::KeepAspectRatio);



//    if(NULL==gpi)
//        return;
//    gpi->itemReset();//gpi（即img）复原到初始大小

//    gs->setSceneRect(gpi->boundingRect());//将scene设置为和gpi一样的大小

//    ui->graphicsView->fitInView(gpi->boundingRect(),Qt::KeepAspectRatio);//将gpi放置到graphicsView中，保持宽高比


}

void MainWindow::on_lastImg_clicked()
{
    if(0 == images.length())
        return;
    if(curIdx <= 0 )
        curIdx = images.length();
    showImage(QImage(images[--curIdx].absoluteFilePath()));
}

void MainWindow::on_nextImg_clicked()
{
    if(0 == images.length())
        return;
    if(curIdx >= images.length()-1)
        curIdx=-1;
    showImage(QImage(images[++curIdx].absoluteFilePath()));
}


//
bool MainWindow::getDisplayImage(QImage &img) const
{
    if(gpi)
    {
    QList<QGraphicsItem*>items=ui->graphicsView->scene()->items();
    QGraphicsPixmapItem* item=
            (QGraphicsPixmapItem*)items.at(0);
    img=item->pixmap().toImage();
    return true;
    }
    return false;
}

//Rgb2gray
void MainWindow::on_actionRgb2gray_triggered()
{
    QImage img;
      if(getDisplayImage(img)){
          img = Matrix<int>::rgb2gray(img);
          showImage(img);
      }
}


//反转
void MainWindow::on_actionReverse_triggered()
{
    QImage img;
    if(getDisplayImage(img)){
       img = Matrix<int>::pixelReverse(img);
       img = img;
       showImage(img);
    }
}

//点击弹出对话框
void MainWindow::on_actionLog_transformation_triggered()
{
    ItDlg->exec();
}

//log均衡
void MainWindow::on_ItDlg_confirmed_triggered(double c)
{
    QImage img;
    if(getDisplayImage(img))
    {
        QImage processimg = Matrix<int>::logTransformation(img, c);
        showImage(processimg);
    }
    cout<<"get_c:"<<c<<endl;
}


//直方图均衡
void MainWindow::on_actionHistEq_triggered()
{
    bool ok;
    QImage img;
    ok = getDisplayImage(img);
    if(ok)
    {
        showImage(ImageProcessor::histEq(img));
    cout<<"histEQ"<<endl;
    }
}

void MainWindow::on_actionColor_histeq1_triggered()
{
    bool ok;
    QImage img;
    ok = getDisplayImage(img);
    if(ok)
    {
        showImage(ImageProcessor::colorHisteq1(img));
    cout<<"color_histeq1"<<endl;
    }
}

void MainWindow::on_actionHsi_triggered()
{
    bool ok;
    QImage img;
    ok = getDisplayImage(img);
    if(ok)
    {
        showImage(ImageProcessor::hsi(img));
    cout<<"actionHsi"<<endl;
    }
}

///////////////////////////////////////////////////////////////////////

//点击弹出LinearRGB对话框
void MainWindow::on_actionRGB_triggered()
{
    linearRgbDialog->exec();
}
//LinearRGB对话框 确认
void MainWindow::on_linearRgbDialog_confirmed(QString txt)
{
    int nCol;
    cout<<"get_l:"<<txt.toStdString()<<endl;
    vector<double> kernel = parseMatrixl2(txt,nCol);
    ImageProcessor::KernelNormalization(kernel);
    if(-1 == nCol)
        return;
    QImage img;
    bool ok = getDisplayImage(img);
    if(ok)
    {
        cout<<"enter linearFilter"<<endl;
        showImage(ImageProcessor::linearRgbFilter(img,kernel,nCol));
    }
}


//点击弹出LinearGRAY对话框
void MainWindow::on_actionGRAY_triggered()
{
    linearGrayDialog->exec();
}
//LinearGRAY对话框 确认
void MainWindow::on_linearGrayDialog_confirmed(QString txt)
{
    int nCol;
    cout<<"get_l:"<<txt.toStdString()<<endl;
    vector<double> kernel = parseMatrixl2(txt,nCol);
    ImageProcessor::KernelNormalization(kernel);
    if(-1 == nCol)
        return;
    QImage img;
    bool ok = getDisplayImage(img);
    if(ok)
    {
        cout<<"enter linearFilter"<<endl;
        showImage(ImageProcessor::linearGrayFilter(img,kernel,nCol));
    }
}

vector<double> MainWindow::parseMatrixl2(QString txt, int& nCol)
{
    vector<double>ret;
    QRegularExpression reRow("[-\\d\\.\\s,]+;?");
    QRegularExpression reCol("-?\\d*\\.?\\d+[,|\\s]?");
    QRegularExpressionMatchIterator remiRow = reRow.globalMatch(txt);
    while(remiRow.hasNext()) { QString row = remiRow.next().
                captured().replace(";","").trimmed();
         if (row.isEmpty()) continue;
        QRegularExpressionMatchIterator remiCol = reCol.globalMatch(row);
        nCol = -1;
        int tmp = 0;
        while(remiCol.hasNext()) { QString col = remiCol.
                    next().captured().replace(",","").trimmed();
          if (col.isEmpty()) continue;
          bool ok;
          double d = col.toDouble(&ok);
          if(ok)
          {
              ret.push_back(d); tmp++;
          }
          else
              return vector<double>();
        }
        if(-1==nCol)
            nCol = tmp;
        else if (nCol != tmp)
            return vector<double>();
    }
    return ret;
}

bool MainWindow::readOneRow(QString row, std::vector<double> &kernel,int nCol)
{
    nCol = 0;
    //split into nuber by , and \s
    QStringList cols = row.trimmed().
            split(QRegularExpression("\\s*,|\\s+"));
    for(int j=0;j<cols.size();j++)
    {
        //parse each col
        bool ok;
        QString col = cols[j];
        if(col.trimmed().isEmpty())  continue;
        double d=col.trimmed().toDouble(&ok);
        if(ok)
        {
            nCol++;
            kernel.push_back(d);
        }
        else
        {
            return false;
        }
    }
    return true;
}

//点击弹出GaussRGB对话框
void MainWindow::on_actionRGB_GAUSS_triggered()
{
    gaussRgbDialog->exec();
}
//GaussRGB对话框确认
void MainWindow::on_gaussRgbDialog_confirmed(int filterSize, double sigma)
{
    QImage img;
    if(getDisplayImage(img)){
        QString patten = "RGB";
        QImage processimg = Matrix<int>::gaussBlurFilter(img, filterSize, sigma, patten);
        showImage(processimg);
    }
}

//点击弹出GaussGray对话框
void MainWindow::on_actionGRAY_GAUSS_triggered()
{
    gaussGrayDialog->exec();
}
//GaussGray对话框确认
void MainWindow::on_gaussGrayDialog_confirmed(int filterSize, double sigma)
{
    QImage img;
    if(getDisplayImage(img)){
        QString patten = "Gray";
        QImage processimg = Matrix<int>::gaussBlurFilter(img, filterSize, sigma, patten);
        showImage(processimg);
    }
}


//bilateral对话框确认
void MainWindow::on_actionBilateral_triggered()
{
    bilateraldialog->exec();
}

void MainWindow::on_bilateralDialog_confirmed(int size,double sigmaColor,double sigmaSpace)
{
    QImage img;
    bool ok= getDisplayImage(img);
    if(ok)
    {
        showImage(ImageProcessor::bilateralFilter(img,size,sigmaColor,sigmaSpace));
    }
}

//弹出MedianRGB对话框
void MainWindow::on_actionRGB_Median_triggered()
{
    medianRgbDialog->exec();
}
//MedianRGB对话框确认
void MainWindow::on_medianRgbdialog_confirmed(double m)
{
    QImage img;
    bool ok = getDisplayImage(img);
    if(ok)
    {
        showImage(ImageProcessor::medianRgbFilter(img,m));
    }
}

//弹出MedianGray对话框
void MainWindow::on_actionGRAY_Median_triggered()
{
    medianGrayDialog->exec();
}
//MedianGray对话框确认
void MainWindow::on_medianGraydialog_confirmed(double m)
{
    QImage img;
    bool ok = getDisplayImage(img);
    if(ok)
    {
        showImage(ImageProcessor::medianGrayFilter(img,m));
    }
}

//点击弹出ExpandRGB对话框
void MainWindow::on_actionRGB_Expand_triggered()
{
   expandRgbDialog->exec();
}

void MainWindow::on_expandRgbdialog_confirmed(double e)
{
    QImage img;
    bool ok = getDisplayImage(img);
    if(ok)
    {
        showImage(ImageProcessor::expandRgbFilter(img,e));
    }
}

//点击弹出ExpandGray对话框
void MainWindow::on_actionGRAY_Expand_triggered()
{
   expandGrayDialog->exec();
}

void MainWindow::on_expandGraydialog_confirmed(double e)
{
    QImage img;
    bool ok = getDisplayImage(img);
    if(ok)
    {
        showImage(ImageProcessor::expandGrayFilter(img,e));
    }
}

//弹出CorrisionRGB对话框
void MainWindow::on_actionRGB_Corrosion_triggered()
{
    corrosionRgbDialog->exec();
}

void MainWindow::on_corrosionRgbdialog_confirmed(double co)
{
    QImage img;
    bool ok = getDisplayImage(img);
    if(ok)
    {
        showImage(ImageProcessor::corrosionRgbFilter(img,co));
    }
}

//弹出CorrisionGRAY对话框
void MainWindow::on_actionGRAY_Corrosion_triggered()
{
    corrosionGrayDialog->exec();
}

void MainWindow::on_corrosionGraydialog_confirmed(double co)
{
    QImage img;
    bool ok = getDisplayImage(img);
    if(ok)
    {
        showImage(ImageProcessor::corrosionGrayFilter(img,co));
    }
}

/////////////////////////////////////////////////////
QVector<QVector<double> > MainWindow::getFilterData(QString & str, int & colNum){

    QVector<QVector<double> > vec;

    // 切割成每一行
    QStringList qsl = str.replace("\n", "").trimmed().split(QRegExp("\\s*;"));

    // 第一行
    QVector<double> vecLine = getFilterDataOfEveryLine(qsl[0], colNum);
    vec.push_back(vecLine);

    // 从第二行开始
    for(int i = 1; i < qsl.length() && qsl[i] != ""; i++){

        int curColNum = 0;
        QVector<double> vecLine = getFilterDataOfEveryLine(qsl[i], curColNum);
        if(curColNum == colNum){
            vec.push_back(vecLine);
        }
    }
    return vec;
}

QVector<double> MainWindow::getFilterDataOfEveryLine(QString &str, int & colNum){

    QVector<double> vec;

    // 切割成每一个元素
    QStringList qsl = str.replace("\n","").trimmed().split(QRegExp("\\s*,"));

    // 本行元素个数
    colNum = qsl.length();
    for(int i = 0; i < qsl.length() && qsl[i] != ""; i++){

        double d = (double)qsl.at(i).toDouble();

        vec.push_back(d);
    }
    return vec;
}

void MainWindow::on_actionAlline_Transformation_triggered()
{
    affineDialog->exec();
}

void MainWindow::on_affineDialog_confirmed(QMatrix matrix)
{
    QImage img;
    if(getDisplayImage(img)){
        showImage(ImageProcessor::transform(img,matrix));
    }
    cout<<"on_affineDialog_confirmed(QMatrix matrix)"<<endl;
}

void MainWindow::on_actionFFT_triggered()
{
    QImage img;
    if(getDisplayImage(img)){
        Matrix<int> g = Matrix<int>::fromQImage(img, 'h');
        Matrix<std::complex<double> > ff = fft2d(g, g.getNRow(), g.getNCol());
        Matrix<double> ffta = Matrix<double>::abs4complex(ff);
        Matrix<double> fftl = Matrix<double>::logtranslate(ffta);
        Matrix<double>::fftshift(fftl);
        Matrix<int> fftres = Matrix<int>::normalization(fftl);
        QImage res = Matrix<int>::toQImage(fftres);
        QImage processor  = res;
        showImage(processor);
    }
    cout<<"FFT"<<endl;
}

void MainWindow::on_actionIFFT_triggered()
{
    cout<<"ifft"<<endl;
}

void MainWindow::on_actionHighPass_triggered()
{
    hpdialog->exec();
}

void MainWindow::on_hpdialog_confirmed(double c)
{
    QImage img;
      if(getDisplayImage(img)){
          Matrix<int> g = Matrix<int>::fromQImage(img, 'h');
          Matrix<std::complex<double> > ff = fft2d(g, g.getNRow(), g.getNCol());
          Matrix<double> ffta = Matrix<double>::abs4complex(ff);
          Matrix<double> fftl = Matrix<double>::logtranslate(ffta);
          Matrix<double>::fftshift(fftl);
          Matrix<int> fftres = Matrix<int>::normalization(fftl);
          Matrix<int> fftlp = Matrix<int>::highpass(fftres,c);
          QImage res = Matrix<int>::toQImage(fftlp);
          QImage processimg  = res;
          showImage(processimg);
    }
}

void MainWindow::on_actionLowPass_triggered()
{
    lpdialog->exec();
}

void MainWindow::on_lpdialog_confirmed(double c)
{
    QImage img;
      if(getDisplayImage(img))
      {
          Matrix<int> g = Matrix<int>::fromQImage(img, 'h');
          Matrix<std::complex<double> > ff = fft2d(g, g.getNRow(), g.getNCol());
          Matrix<double> ffta = Matrix<double>::abs4complex(ff);
          Matrix<double> fftl = Matrix<double>::logtranslate(ffta);
          Matrix<double>::fftshift(fftl);
          Matrix<int> fftres = Matrix<int>::normalization(fftl);
          Matrix<int> fftlp = Matrix<int>::lowpass(fftres,c);
          QImage res = Matrix<int>::toQImage(fftlp);
          QImage processimg  = res;
          showImage(processimg);
      }
}

void MainWindow::on_saveBtn_clicked()
{
    QImage img;
     bool ok;
     ok = getDisplayImage(img);
     if(ok)
     {
         //设置图片的保存路径
         QString fileName = QFileDialog::getSaveFileName(this,tr(" Save Image "),
                                                     "/",tr(" Image files(*.bmp;;*.jpg;;*.png;;*.tif;;*.GIF;;All Files(*.*)"));
         if(fileName.isNull())
         {
             return;
         }
         else
         {
             //弹出保存反馈窗口
             if(!img.save(fileName))
             {
                 QMessageBox::information(this,tr(" Save Failed  "),tr(" Save Failed ! "));
             }
             else
                 QMessageBox::information(this,tr(" Save Succeed  "),tr(" Save Succeed ! "));
         }
     }

}
