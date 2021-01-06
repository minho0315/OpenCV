//히스토그램 RGB
#include<iostream>
#include<opencv2\core.hpp>
#include<opencv\cv.h>
#include<opencv2\highgui.hpp>
#include<opencv2\imgproc.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;

int main(int ac, char** av) {
	Mat inputImg = imread("Lenna.png", CV_LOAD_IMAGE_COLOR);

	MatND histogramB, histogramG, histogramR;
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


////히스토그램 (gray)
//#include <opencv2/opencv.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//int main(int ac, char** av) {
//
//	Mat img_1 = imread("Lenna.png", 0);	//이미지를 grayscale로 불러옴
//
//	Mat img_2 = img_1 * 2;
//	Mat img_3 = img_1 / 2;
//	Mat img_hist;
//
//	MatND histogram;
//
//	const int* channel_numbers = { 0 };
//	float channel_range[] = { 0.0, 255.0 };
//	const float* channel_ranges = channel_range;
//	int number_bins = 255;
//
//	calcHist(&img_1, 1, channel_numbers, Mat(), histogram, 1, &number_bins, &channel_ranges);
//
//	// plot the histogram
//	int hist_w = img_1.cols;
//	int hist_h = img_1.rows;
//	int bin_w = cvRound((double)hist_w / number_bins);
//
//	Mat hist_img(hist_h, hist_w, CV_8UC1, Scalar::all(0));
//	normalize(histogram, histogram, 0, hist_img.rows, NORM_MINMAX, -1, Mat());
//
//	for (int i = 1; i < number_bins; i++)
//	{
//		line(hist_img, Point(bin_w * (i - 1), hist_h - cvRound(histogram.at<float>(i - 1))), Point(bin_w * (i), hist_h - cvRound(histogram.at<float>(i))), Scalar(255, 0, 0), 1, 8, 0);
//	}
//
//	imshow("Origianl", img_1);
//	imshow("Histogram", hist_img);
//
//
//
//	//imshow("original", img_1);
//	//imshow("img_mul", img_2);
//	//imshow("img_div", img_3);
//
//	waitKey(0);
//
//
//	return 0;
//}

//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/videoio.hpp>
//#include <opencv2/highgui.hpp>
//
//#include <iostream>
//#include <stdio.h>
//
//using namespace cv;
//using namespace std;
//
//
//int main(int ac, char** av) {
//
//	Mat img = imread("Lenna.png"); //자신이 저장시킨 이미지 이름이 입력되어야 함, 확장자까지
//
//	imshow("img", img);
//	waitKey(0);
//
//	return 0;
//}