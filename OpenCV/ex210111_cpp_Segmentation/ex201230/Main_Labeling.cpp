#include <opencv2/opencv.hpp>

#include <windows.h>

using namespace cv;
using namespace std;

int main(int ac, char** av)
{
	Mat img = imread("bacteria.tif");

	Mat img_resize;
	resize(img, img_resize, Size(img.cols * 3, img.rows * 3));

	Mat img_gray;
	cvtColor(img_resize, img_gray, COLOR_BGR2GRAY);

	Mat img_threshold;
	threshold(img_gray, img_threshold, 100, 255, THRESH_BINARY_INV);

	Mat img_labels, stats, centroids;
	int numOfLables = connectedComponentsWithStats(img_threshold, img_labels, stats, centroids, 8, CV_32S);

	// 레이블링 결과에 사각형 그리고, 넘버 표시하기
	for (int j = 1; j < numOfLables; j++) {
		int area = stats.at<int>(j, CC_STAT_AREA);
		int left = stats.at<int>(j, CC_STAT_LEFT);
		int top = stats.at<int>(j, CC_STAT_TOP);
		int width = stats.at<int>(j, CC_STAT_WIDTH);
		int height = stats.at<int>(j, CC_STAT_HEIGHT);


		rectangle(img_resize, Point(left, top), Point(left + width, top + height),
			Scalar(0, 0, 255), 1);

		putText(img_resize, to_string(j), Point(left + 20, top + 20), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 1);
	}


	imshow("img_resize", img_resize);

	cout << "numOfLables : " << numOfLables - 1 << endl;	// 최종 넘버링에서 1을 빼줘야 함
	waitKey(0);



	return 0;
}