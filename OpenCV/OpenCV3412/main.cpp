//// ������׷� ����ȭ �̹���
//#include <opencv2/opencv.hpp>
//
//using namespace cv;
//using namespace std;
//
//int main(int ac, char** av) {
//
//	Mat img_1 = imread("Lenna.png", 0);	//�̹����� grayscale�� �ҷ���
//
//	Mat hist_img;
//
//	equalizeHist(img_1, hist_img);
//
//	imshow("Original", img_1);
//	imshow("Histogram equalization", hist_img);
//
//	waitKey(0);
//
//
//
//	return 0;
//}

//// ������׷� �м� �ڵ� �׽�Ʈ
//#include <opencv2/opencv.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//int main(int ac, char** av) {
//
//	Mat img_1 = imread("Lenna.png", 0);	//�̹����� grayscale�� �ҷ���
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
//	imshow("original", img_1);
//	imshow("img_mul", img_2);
//	imshow("img_div", img_3);
//
//	waitKey(0);
//
//
//	return 0;
//}


//// ������� ���� ����
//#include <opencv2/opencv.hpp>
//
//using namespace cv;
//using namespace std;
//
//int main(int ac, char** av) {
//
//	Mat img_1 = imread("Lenna.png", 0);	//�̹����� grayscale�� �ҷ���
//
//	Mat img_2 = img_1 + 100;
//	Mat img_3 = img_1 - 100;
//
//	imshow("original", img_1);
//	imshow("img_sum", img_2);
//	imshow("img_sub", img_3);
//
//	waitKey(0);
//
//	return 0;
//}

//// imread-graycaler�� cvtColor�� ����
//#include <opencv2/opencv.hpp>
//
//using namespace cv;
//using namespace std;
//
//int main(int ac, char** av) {
//
//	Mat color_img = imread("Lenna.png");
//	Mat grayscale_img_1 = imread("Lenna.png", 0);
//
//	Mat grayscale_img_2;
//
//	cvtColor(color_img, grayscale_img_2, COLOR_BGR2GRAY);
//
//	imshow("grayscale_img_1", grayscale_img_1);
//	imshow("grayscale_img_2", grayscale_img_2);
//
//	waitKey(0);
//
//	return 0;
//}

////���� ���ȭ �ڵ�
//#include <opencv2/opencv.hpp>
//
//using namespace cv;
//using namespace std;
//
//int main(int ac, char** av) {
//
//	Mat color_img = imread("Lenna.png");
//	Mat grayscale_img(color_img.rows,color_img.cols, CV_8UC1);
//		
//	for (int y = 0; y < color_img.rows; y++)
//	{
//		for (int x = 0; x < color_img.cols; x++)
//		{
//			int avg_val = (color_img.at<Vec3b>(y, x)[0]+ color_img.at<Vec3b>(y, x)[1]+ color_img.at<Vec3b>(y, x)[2])/3;
//			grayscale_img.at<uchar>(y, x) = avg_val;
//		}
//	}
//    
//	imshow("grayscale_img", grayscale_img);
//	waitKey(0);
//
//	return 0;
//}

//// RGB to Grayscale
//#include <opencv2/opencv.hpp>
//
//using namespace cv;
//using namespace std;
//
//int main(int ac, char** av) {
//
//	Mat color_img = imread("Lenna.png");
//	Mat grayscale_img;
//
//	cvtColor(color_img, grayscale_img, COLOR_BGR2GRAY);
//	
//	imshow("color_img", color_img);
//	imshow("grayscale_img", grayscale_img);
//	waitKey(0);
//
//	return 0;
//}

//// imread(), imshow()
//#include <opencv2/highgui.hpp>
//
//using namespace cv;
//using namespace std;
//
//int main(int ac, char** av) {
//
//	Mat color_img = imread("Lenna.png", IMREAD_COLOR);
//	Mat grayscale_img = imread("Lenna.png", IMREAD_GRAYSCALE);
//	Mat unchanged_img = imread("Lenna.png", IMREAD_UNCHANGED);
//	Mat reduced_img = imread("Lenna.png", IMREAD_REDUCED_COLOR_2);
//	Mat reduced_grayscale_img = imread("Lenna.png", IMREAD_REDUCED_GRAYSCALE_4);
//
//	imshow("color_img", color_img);
//	imshow("grayscale_img", grayscale_img);
//	imshow("unchanged_img", unchanged_img);
//	imshow("reduced_img", reduced_img);
//	imshow("reduced_grayscale_img", reduced_grayscale_img);
//	waitKey(0);
//
//	return 0;
//}

////�⺻����
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
//	Mat img = imread("Lenna.png"); //�ڽ��� �����Ų �̹��� �̸��� �ԷµǾ�� ��, Ȯ���ڱ���
//
//	imshow("img", img);
//	waitKey(0);
//
//	return 0;
//}