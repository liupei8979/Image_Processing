#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;

Point ptStart;


void on_MouseHandle(int event, int x, int y, int flag, void* param);


bool equalImg(Mat mat1, Mat mat2);


void RegionFilling(Mat& src, Point ptStart);

int main()
{

    Mat img = imread("/Users/liupei/desktop/Profile.png", 0);
    if (img.empty())
    {
        std::cout << "Could not load image!" << std::endl;
        return -1;
    }
   
    Point anchor(-1, -1);
    
    Size ksize(3, 3);
    
    
    Mat kernal = getStructuringElement(MORPH_ELLIPSE, ksize, anchor);
    
    Mat boundaryImg;
    
    
    morphologyEx(img, boundaryImg, MORPH_GRADIENT, kernal);
   
    imshow("boundaryImg", boundaryImg);
    namedWindow("boundaryImg");
    
    setMouseCallback("boundaryImg", on_MouseHandle, (void*)&boundaryImg);
    waitKey(0);
    return 0;
}

void on_MouseHandle(int event, int x, int y, int flag, void* param)
{
    Mat& img = *(Mat*)param;
    switch (event)
    {
    
    case EVENT_LBUTTONDOWN:
        ptStart.x = x; ptStart.y = y;
        break;
   case EVENT_LBUTTONUP:
        
        RegionFilling(img, ptStart);

        break;
    }
}

void RegionFilling(Mat& src, Point ptStart)
{
    
    Mat dst = Mat::zeros(src.size(), src.type());

    Point anchor(-1, -1);
    Size ksize(3, 3);
       
    Mat kernal = getStructuringElement(MORPH_ELLIPSE, ksize, anchor);
    Mat tempImg = Mat::ones(src.size(), src.type()) * 255;
    
    
    Mat revImg = tempImg - src;

    dst.at<uchar>(ptStart.y, ptStart.x) = 255;
    
    while (true)
    {
        Mat temp;
        
       
        dst.copyTo(temp);
        
       
        dilate(dst, dst, kernal);
                
       
        dst = dst & revImg;
                    
      
        if (equalImg(dst, temp))
        {
            break;
        }
        src = dst;
        imshow("Result", src);
        waitKey(10);
    }
}

bool equalImg(Mat mat1, Mat mat2)
{
   
    if (mat1.empty() && mat2.empty())
    {
        return true;
    }
    
    if (mat1.cols != mat2.cols || mat1.rows != mat2.rows || mat1.dims != mat2.dims ||
        mat1.channels() != mat2.channels())
    {
        return false;
    }
    
    if (mat1.size() != mat2.size() || mat1.channels() != mat2.channels() || mat1.type() != mat2.type())
    {
        return false;
    }
    //////*------------------------------*------------------------////
        
    int nrOfElements1 = mat1.total() * mat1.elemSize();
    
    if (nrOfElements1 != mat2.total() * mat2.elemSize())
    {
      return false;
    }
    
    bool lvRet = memcmp(mat1.data, mat2.data, nrOfElements1) == 0;
    
    return lvRet;
}
