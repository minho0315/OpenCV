#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int ac, char** av) {

	Mat img_1 = imread("Lenna.png", 0);	//이미지를 grayscale로 불러옴


	MatND histogram;

	const int* channel_numbers = { 0 };
	float channel_range[] = { 0.0, 255.0 };
	const float* channel_ranges = channel_range;
	int number_bins = 255;

	calcHist(&img_1, 1, channel_numbers, Mat(), histogram, 1, &number_bins, &channel_ranges);

	// plot the histogram
	int hist_w = img_1.cols;
	int hist_h = img_1.rows;
	int bin_w = cvRound((double)hist_w / number_bins);

	Mat hist_img(hist_h, hist_w, CV_8UC1, Scalar::all(0));
	normalize(histogram, histogram, 0, hist_img.rows, NORM_MINMAX, -1, Mat());

	for (int i = 1; i < number_bins; i++)
	{
		line(hist_img, Point(bin_w * (i - 1), hist_h - cvRound(histogram.at<float>(i - 1))), Point(bin_w * (i), hist_h - cvRound(histogram.at<float>(i))), Scalar(255, 0, 0), 1, 8, 0);
	}

	imshow("Origianl", img_1);
	imshow("Histogram", hist_img);


	waitKey(0);


	return 0;
}