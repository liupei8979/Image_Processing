//
//  main.cpp
//  m2ntae
//
//  Created by 김민태 on 2022/04/11.
//

#include <iostream>
#include <array>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;


void MyMedianFilter(InputArray input, OutputArray &output, int windowSize) {
    
    Mat input_ = input.getMat();
   Mat output_ = output.getMat();
    
     int ww = (windowSize - 1) / 2;
     int wh = (windowSize - 1) / 2;
     Mat Newsrc;
     copyMakeBorder(input, Newsrc, ww, ww, wh, wh, BORDER_REFLECT_101);
    
     output_ = Mat::zeros(input_.rows, input_.cols, input_.type());
     

     for (int i = 0; i < input_.rows; i++)
     {
    
         for (int j = 0; j < input_.cols; j++)
         {
    
             double valueSum = 0.0;
             #define SIZE 256
             int iVec[SIZE];
             for (int k = 0; k < ww*2+1; k++)
             {
    
                 for (int z = 0; z < wh*2+1; z++)
                 {
    
                     int srcValue = (int)Newsrc.at<uchar>(i + k, j + z);
                     valueSum += srcValue;
                     iVec[z+k] = srcValue;
                 }
             }
        
             int iSize = ww*2+1 + wh*2+1;
             for(int h = 0; h < iSize;h++)
             {
                 for(int w = 1; w < iSize - h; w++)
                 {
    
                     int temp =  iVec[w-1];
                     if(iVec[w-1]>iVec[w])
                     {
                         iVec[w-1] = iVec[w];
                         iVec[w] = temp;
                     }
                 }
             }

             int iValue = iSize % 2 == 0 ? (iVec[iSize/2]+iVec[iSize/2-1])/2 : iVec[iSize/2];
          output_.at<uchar>(i, j) = (uchar)iValue;
         }
     }

 }




int main()
{
    Mat img = imread ("/Users/liupei/desktop/ty04.jpeg", 0);
    
    Mat out1 = img.clone();
    
    MyMedianFilter(img, out1,5);
    imshow("Image", img);
    imshow("MedianFilter",out1);

    waitKey();
    return 0;
}
