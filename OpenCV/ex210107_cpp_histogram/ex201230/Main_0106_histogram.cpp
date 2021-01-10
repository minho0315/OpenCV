#include<iostream>
#include<opencv2\core.hpp>
#include<opencv\cv.h>
#include<opencv2\highgui.hpp>
#include<opencv2\imgproc.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;

/*
void cv::calcHist(const Mat*    images, // Histogram을 계산할 이미지들에 대한 배열이다.
				  int           nimages, // images 배열에 포함된 이미지의 개수이다.
				  const int*    channels, //Histogram을 계산할 채널 번호들의 배열이다.
				  InputArray    mask, //Histogram을 계산할 영역을 지정할 수 있다.
				  OutputArray   hist, //Histogram 계산결과를 저장한다.
				  int           dims, //Histogram 계산결과를 저장한 hist의 차원으 가리킨다.
				  const int*    histSize, //각 차원의 bin개수, 즉 빈도수를 분류할 칸의 개수를 의미한다.
				  const float** ranges, //각 차원의 분류 bin의 최소값 최대값을 의미한다.
				  bool          uniform =true,
				  bool          accumulate = flase
				 )
*/
int main(int ac, char** av) {
	Mat inputImg = imread("Lenna.png", CV_LOAD_IMAGE_COLOR);

	MatND histogramB, histogramG, histogramR, histogram;
	int channel_B[] = { 0 };  // Blue
	int channel_G[] = { 1 };  // Green
	int channel_R[] = { 2 };  // Red
	float channel_range[2] = { 0.0 , 255.0 };
	const float* channel_ranges[1] = { channel_range };
	int histSize[1] = { 256 };

	// R, G, B별로 각각 히스토그램을 계산한다.
	calcHist(&inputImg, 1, channel_B, Mat(), histogramB, 1, histSize, channel_ranges);
	calcHist(&inputImg, 1, channel_G, Mat(), histogramG, 1, histSize, channel_ranges);
	calcHist(&inputImg, 1, channel_R, Mat(), histogramR, 1, histSize, channel_ranges);
	// Plot the histogram

	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize[0]);


	Mat histImageB(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	normalize(histogramB, histogramB, 0, histImageB.rows, NORM_MINMAX, -1, Mat());

	Mat histImageG(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	normalize(histogramG, histogramG, 0, histImageG.rows, NORM_MINMAX, -1, Mat());

	Mat histImageR(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	normalize(histogramR, histogramR, 0, histImageR.rows, NORM_MINMAX, -1, Mat());

	for (int i = 1; i < histSize[0]; i++)
	{
		line(histImageB, Point(bin_w * (i - 1), hist_h - cvRound(histogramB.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(histogramB.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);

		line(histImageG, Point(bin_w * (i - 1), hist_h - cvRound(histogramG.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(histogramG.at<float>(i))),
			Scalar(0, 255, 0), 2, 8, 0);

		line(histImageR, Point(bin_w * (i - 1), hist_h - cvRound(histogramR.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(histogramR.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);

	}

	namedWindow("Original", CV_WINDOW_AUTOSIZE);
	namedWindow("HistogramB", CV_WINDOW_AUTOSIZE);
	namedWindow("HistogramG", CV_WINDOW_AUTOSIZE);
	namedWindow("HistogramR", CV_WINDOW_AUTOSIZE);

	moveWindow("Original", 100, 100);
	moveWindow("HistogramB", 110, 110);
	moveWindow("HistogramG", 120, 120);
	moveWindow("HistogramR", 130, 130);

	imshow("Original", inputImg);
	imshow("HistogramB", histImageB);
	imshow("HistogramG", histImageG);
	imshow("HistogramR", histImageR);

	waitKey(0);
	return 0;
}