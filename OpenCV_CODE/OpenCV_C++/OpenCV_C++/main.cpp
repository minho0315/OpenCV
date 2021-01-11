//// �󺧸� (����� �ڵ�) - 2021/1/11
//#include <opencv2/opencv.hpp>
//#include <windows.h>
//
//using namespace cv;
//using namespace std;
//
//int main(int ac, char** av)
//{
//	Mat img = imread("../Image/bacteria.tif");
//
//	Mat img_resize;
//	resize(img, img_resize, Size(img.cols * 3, img.rows * 3));
//
//	Mat img_gray;
//	cvtColor(img_resize, img_gray, COLOR_BGR2GRAY);
//
//	Mat img_threshold;
//	threshold(img_gray, img_threshold, 100, 255, THRESH_BINARY_INV);
//
//	Mat img_labels, stats, centroids;
//	int numOfLables = connectedComponentsWithStats(img_threshold, img_labels, stats, centroids, 8, CV_32S);
//
//	// ���̺� ����� �簢�� �׸���, �ѹ� ǥ���ϱ�
//	for (int j = 1; j < numOfLables; j++) {
//		int area = stats.at<int>(j, CC_STAT_AREA);
//		int left = stats.at<int>(j, CC_STAT_LEFT);
//		int top = stats.at<int>(j, CC_STAT_TOP);
//		int width = stats.at<int>(j, CC_STAT_WIDTH);
//		int height = stats.at<int>(j, CC_STAT_HEIGHT);
//
//
//		rectangle(img_resize, Point(left, top), Point(left + width, top + height),
//			Scalar(0, 0, 255), 1);
//
//		putText(img_resize, to_string(j), Point(left + 20, top + 20), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 1);
//	}
//
//
//	imshow("img_resize", img_resize);
//
//	cout << "numOfLables : " << numOfLables - 1 << endl;	// ���� �ѹ������� 1�� ����� ��
//	waitKey(0);
//
//
//
//	return 0;
//}

//// ���׸����̼� (����� �ڵ�) - 2021/1/11
//#include <opencv2/core.hpp>
//#include <opencv2/imgproc.hpp>
//#include <opencv2/highgui.hpp>
//#include <iostream>
//using namespace std;
//using namespace cv;
//int main(int argc, char* argv[])
//{
//    // Load the image
//    Mat src = imread("../Image/coin.png");
//    if (src.empty())
//    {
//        cout << "Could not open or find the image!\n" << endl;
//        cout << "Usage: " << argv[0] << " <Input image>" << endl;
//        return -1;
//    }
//
//    // Show source image
//    imshow("Source Image", src);
//
//    // ���߿� �����ϴµ� �����̵ǹǷ� ����� ����� ���� ������ ����
//    for (int i = 0; i < src.rows; i++) {
//        for (int j = 0; j < src.cols; j++) {
//            if (src.at<Vec3b>(i, j) == Vec3b(255, 255, 255))
//            {
//                src.at<Vec3b>(i, j)[0] = 0;
//                src.at<Vec3b>(i, j)[1] = 0;
//                src.at<Vec3b>(i, j)[2] = 0;
//            }
//        }
//    }
//    // Show output image
//    imshow("Black Background Image", src);
//
//    // �̹����� �����ϰ��ϴ� �� ����� Ŀ���� �����.
//    Mat kernel = (Mat_<float>(3, 3) <<
//        1, 1, 1,
//        1, -8, 1,
//        1, 1, 1); // an approximation of second derivative, a quite strong kernel
//
//// do the laplacian filtering as it is
//// well, we need to convert everything in something more deeper then CV_8U
//// because the kernel has some negative values,
//// and we can expect in general to have a Laplacian image with negative values
//// BUT a 8bits unsigned int (the one we are working with) can contain values from 0 to 255
//// so the possible negative number will be truncated
//    Mat imgLaplacian;
//    filter2D(src, imgLaplacian, CV_32F, kernel);
//    Mat sharp;
//    src.convertTo(sharp, CV_32F);
//    Mat imgResult = sharp - imgLaplacian;
//    // convert back to 8bits gray scale
//    imgResult.convertTo(imgResult, CV_8UC3);
//    imgLaplacian.convertTo(imgLaplacian, CV_8UC3);
//    // imshow( "Laplace Filtered Image", imgLaplacian );
//    imshow("New Sharped Image", imgResult);
//
//    // Create binary image from source image
//    Mat bw;
//    cvtColor(imgResult, bw, COLOR_BGR2GRAY);
//    threshold(bw, bw, 40, 255, THRESH_BINARY | THRESH_OTSU);
//    imshow("Binary Image", bw);
//
//    // Perform the distance transform algorithm
//    Mat dist;
//    distanceTransform(bw, dist, DIST_L2, 3);
//    // Normalize the distance image for range = {0.0, 1.0}
//    // so we can visualize and threshold it
//    normalize(dist, dist, 0, 1.0, NORM_MINMAX);
//    imshow("Distance Transform Image", dist);
//
//    // Threshold to obtain the peaks
//    // This will be the markers for the foreground objects
//    threshold(dist, dist, 0.4, 1.0, THRESH_BINARY);
//    // Dilate a bit the dist image
//    Mat kernel1 = Mat::ones(3, 3, CV_8U);
//    dilate(dist, dist, kernel1);
//    imshow("Peaks", dist);
//
//    // Create the CV_8U version of the distance image
//    // It is needed for findContours()
//    Mat dist_8u;
//    dist.convertTo(dist_8u, CV_8U);
//    // Find total markers
//    vector<vector<Point> > contours;
//    findContours(dist_8u, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//    // Create the marker image for the watershed algorithm
//    Mat markers = Mat::zeros(dist.size(), CV_32S);
//    // Draw the foreground markers
//    for (size_t i = 0; i < contours.size(); i++)
//    {
//        drawContours(markers, contours, static_cast<int>(i), Scalar(static_cast<int>(i) + 1), -1);
//    }
//    // Draw the background marker
//    circle(markers, Point(5, 5), 3, Scalar(255), -1);
//    imshow("Markers", markers * 10000);
//
//    // Perform the watershed algorithm
//    watershed(imgResult, markers);
//    Mat mark;
//    markers.convertTo(mark, CV_8U);
//    bitwise_not(mark, mark);
//    imshow("Markers_v2", mark); // uncomment this if you want to see how the mark
//    // image looks like at that point
//    // Generate random colors
//    vector<Vec3b> colors;
//    for (size_t i = 0; i < contours.size(); i++)
//    {
//        int b = theRNG().uniform(0, 256);
//        int g = theRNG().uniform(0, 256);
//        int r = theRNG().uniform(0, 256);
//        colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
//    }
//    // Create the result image
//    Mat dst = Mat::zeros(markers.size(), CV_8UC3);
//    // Fill labeled objects with random colors
//    for (int i = 0; i < markers.rows; i++)
//    {
//        for (int j = 0; j < markers.cols; j++)
//        {
//            int index = markers.at<int>(i, j);
//            if (index > 0 && index <= static_cast<int>(contours.size()))
//            {
//                dst.at<Vec3b>(i, j) = colors[index - 1];
//            }
//        }
//    }
//    // Visualize the final image
//    imshow("Final Result", dst);
//    waitKey();
//    return 0;
//}

//// ���׸����̼� (ȥ��) - 2021/1/9
//#include<opencv2/core.hpp>
//#include<opencv2/imgproc.hpp>
//#include<opencv2/highgui.hpp>+
//using namespace cv;
//using namespace std;
//int main()
//{
//	Mat image = imread("../Image/fruit.png");
//	Mat image_gray;
//	Mat image_bi;
//	Mat label_box;
//
//	// �� ���̾� ����
//	Mat img_label;
//	Mat stats;
//	Mat centroids;
//	int label;
//
//
//	//�̹��� ���/Ȯ��
//	resize(image, image, Size(500, 500));
//
//	// ����
//	label_box = image.clone();
//
//	//�׷��̽�����
//	cvtColor(image, image_gray, CV_RGB2GRAY);
//
//	//����ȭ
//	threshold(image_gray, image_bi, 235, 255, CV_THRESH_BINARY); // �׷��� �̹���, 
//	image_bi = ~image_bi;
//
//	label = connectedComponentsWithStats(image_bi, img_label, stats, centroids, 8, CV_32S);
//	// 1. �Է� �̹��� / 2. �󺧸� ��� �̹��� / 3. �󺧸� �� �̹����� ���� / 4. �󺧸� �� �̹����� �߽� ��ǥ /  5. 4���� or 8���� /  6. Ÿ��
//	for (int j = 1; j < label; j++)
//	{
//		int area = stats.at<int>(j, CC_STAT_AREA);
//		int left = stats.at<int>(j, CC_STAT_LEFT);
//		int top = stats.at<int>(j, CC_STAT_TOP);
//		int width = stats.at<int>(j, CC_STAT_WIDTH);
//		int height = stats.at<int>(j, CC_STAT_HEIGHT);
//
//		// �󺧸� �ڽ�
//		rectangle(label_box, Point(left, top), Point(left + width, top + height), Scalar(0, 0, 255), 3);
//		putText(label_box, to_string(j), Point(left + 20, top + 20),
//			FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2);
//
//	}
//
//	imshow("original", image);
//	imshow("Binary", image_bi);
//	imshow("Label box", label_box);
//
//	waitKey(0);
//}


//// �ȼ��� ���� - 2021/1/8
//#include<opencv2/core.hpp>
//#include<opencv2/imgproc.hpp>
//#include<opencv2/highgui.hpp>
//using namespace std;
//using namespace cv;
//void salt(Mat& image, int snum) {
//	for (int n = 0; n < snum; n++)
//	{
//		int x = rand() % image.cols;
//		int y = rand() % image.rows;
//		if (image.channels() == 1) // Gray ������ ���
//		{
//			image.at<uchar>(x, y) = 255; // 255�� ���
//		}
//		else if (image.channels()==3) // RGB ������ ���
//		{
//			image.at<Vec3b>(y, x)[0] = 255;
//			image.at<Vec3b>(y, x)[1] = 255;
//			image.at<Vec3b>(y, x)[2] = 255;
//		}
//	}
//}
//int main()
//{
//	Mat image = imread("../Image/Lenna.png"); // ("lena.png",0) �̸� Gray �������� ����
//	salt(image, 15000);
//	imshow("�ұݻѸ���", image);
//	waitKey(0);
//}
	


//// �̹��� RGB �и� - 2021/1/7
//#include <iostream>
//#include <opencv2/core.hpp>
//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/highgui.hpp>
//using namespace std;
//using namespace cv;
//
//int main(int argc, char* argv[]) {
//
//    Mat Image = imread("../Image/ThankYou.jpg", IMREAD_COLOR); // �̹��� ��������
//
//    Mat bgr[3]; // split�� ���� ���
//
//    Mat zFillMatrix = Mat::zeros(Image.size(), CV_8UC1); // ���� 0�� ����� ����
//
//    
//    split(Image, bgr); // 3cheanls�� ���� image�� split�ؼ� ������ single channel�� bgr �迭 ��ҿ� ����!
//
//    // 3���� �÷������ ����
//    Mat R[] = { zFillMatrix, zFillMatrix, bgr[2] }; // �� ������ ���ִ� ����: �̱�ä�η� ����ϸ� ���������� �����⶧��. (������� R�ǰ��� ����ϰ� ������ G, B�� ���� 0���� ���� ��Ƽä�η� �������� ����� ����� ��.)
//    Mat G[] = { zFillMatrix, bgr[1], zFillMatrix };
//    Mat B[] = { bgr[0], zFillMatrix, zFillMatrix };
//    merge(R, 3, bgr[2]);
//    merge(G, 3, bgr[1]);
//    merge(B, 3, bgr[0]);
//
//    // ������ 4�� ����
//    namedWindow("Original Image");
//    namedWindow("Red Channel");
//    namedWindow("Green Channel");
//    namedWindow("Blue Channel");
//    
//    // show 4 windows
//    imshow("Original Image", Image);
//    imshow("Red Channel", bgr[2]); // ��������: OpenCV������ ä���� RGB�� �ƴ�, BGR������!
//    imshow("Green Channel", bgr[1]);
//    imshow("Blue Channel", bgr[0]);
//
//    waitKey(0);
//    return 0;
//}



//// �÷��̹��� ������׷� ��� - 2021/1/7
//#include<iostream>
//#include<opencv2\core.hpp>
//#include<opencv\cv.h>
//#include<opencv2\highgui.hpp>
//#include<opencv2\imgproc.hpp>
//#include <stdio.h>
//
//using namespace cv;
//using namespace std;
//
//int main(int ac, char** av) {
//	Mat inputImg = imread("../Image/Lenna.png", CV_LOAD_IMAGE_COLOR);
//
//	MatND histogramB, histogramG, histogramR;
//	int channel_B[] = { 0 };  // Blue
//	int channel_G[] = { 1 };  // Green
//	int channel_R[] = { 2 };  // Red
//	float channel_range[2] = { 0.0 , 255.0 };
//	const float* channel_ranges[1] = { channel_range };
//	int histSize[1] = { 256 };
//
//	// R, G, B���� ���� ������׷��� ����Ѵ�.
//	calcHist(&inputImg, 1, channel_B, Mat(), histogramB, 1, histSize, channel_ranges);
//	calcHist(&inputImg, 1, channel_G, Mat(), histogramG, 1, histSize, channel_ranges);
//	calcHist(&inputImg, 1, channel_R, Mat(), histogramR, 1, histSize, channel_ranges);
//
//	// Plot the histogram
//	int hist_w = 512; int hist_h = 400;
//	int bin_w = cvRound((double)hist_w / histSize[0]);
//
//	Mat histImageB(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
//	normalize(histogramB, histogramB, 0, histImageB.rows, NORM_MINMAX, -1, Mat());
//
//	Mat histImageG(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
//	normalize(histogramG, histogramG, 0, histImageG.rows, NORM_MINMAX, -1, Mat());
//
//	Mat histImageR(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
//	normalize(histogramR, histogramR, 0, histImageR.rows, NORM_MINMAX, -1, Mat());
//
//	for (int i = 1; i < histSize[0]; i++)
//	{
//		line(histImageB, Point(bin_w * (i - 1), hist_h - cvRound(histogramB.at<float>(i - 1))),
//			Point(bin_w * (i), hist_h - cvRound(histogramB.at<float>(i))),
//			Scalar(255, 0, 0), 2, 8, 0);
//
//		line(histImageG, Point(bin_w * (i - 1), hist_h - cvRound(histogramG.at<float>(i - 1))),
//			Point(bin_w * (i), hist_h - cvRound(histogramG.at<float>(i))),
//			Scalar(0, 255, 0), 2, 8, 0);
//
//		line(histImageR, Point(bin_w * (i - 1), hist_h - cvRound(histogramR.at<float>(i - 1))),
//			Point(bin_w * (i), hist_h - cvRound(histogramR.at<float>(i))),
//			Scalar(0, 0, 255), 2, 8, 0);
//
//	}
//
//	namedWindow("Original", CV_WINDOW_AUTOSIZE);
//	namedWindow("HistogramB", CV_WINDOW_AUTOSIZE);
//	namedWindow("HistogramG", CV_WINDOW_AUTOSIZE);
//	namedWindow("HistogramR", CV_WINDOW_AUTOSIZE);
//
//	moveWindow("Original", 100, 100);
//	moveWindow("HistogramB", 110, 110);
//	moveWindow("HistogramG", 120, 120);
//	moveWindow("HistogramR", 130, 130);
//
//	imshow("Original", inputImg);
//	imshow("HistogramB", histImageB);
//	imshow("HistogramG", histImageG);
//	imshow("HistogramR", histImageR);
//
//	waitKey(0);
//	return 0;
//}


//// ����̹��� ������׷� - 2021/1/7
//#include <opencv2/opencv.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//int main(int ac, char** av) {
//
//	Mat img_1 = imread("../Image/Lenna.png", 0);	//�̹����� grayscale�� �ҷ���
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

//// ����̹��� ������׷� ��� - 2021/1/5
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <iostream>
//using namespace cv;
//using namespace std;
//// ��� ���� ����
//class Histogram1D {
//private:
//    int histSize[1]; // �󵵼�
//    float hranges[2]; // �ּ�/�ִ� ȭ�Ұ�
//    const float* ranges[1];
//    int channels[1]; // ���⼭ 1ä�θ� ���
//public:
//    Histogram1D() { // 1���� ������׷��� ���� ���� �غ�
//        histSize[0] = 256;
//        hranges[0] = 0.0;
//        hranges[1] = 256.0;
//        ranges[0] = hranges;
//        channels[0] = 0; // �⺻������ ä���� 0���� ����
//    }
//
//    // ������ ��� ������ �׷��̷��� ������ ������׷��� ����� ���� ���� �޼ҵ带 ����� ����
//    Mat getHistogram(const Mat& image)
//    {
//        Mat hist;
//        calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);
//        return hist;
//
//        // calcHist(1. *������׷� ����� ����, 2. �����ǰ���, 3. ����� ä�ι�ȣ (����̸� 0), 4. ����ũ�ɼ�(�����ϸ� Mat() �Ǵ� noArray()
//		//	5. ��� ������׷�, 6. ������׷��� �������� 1D ������׷��̸� 1, 7. ������׷� hist�� �� ������ ũ��(bin�� ũ�⿡ ���� ���� �迭),
//		//	8. ������׷��� �� ���� ���� ��谪�� �迭�� �迭)
//    }
//
//    // 1D ������׷��� ����� �� ������׷� �������� ��ȯ
//    Mat getHistogramImage(const Mat& image) {
//
//        Mat hist = getHistogram(image); // ���� ������׷� ���
//
//        double maxVal = 0;
//        double minVal = 0;
//        minMaxLoc(hist, &minVal, &maxVal, 0, 0);
//
//        Mat histImg(histSize[0], histSize[0], CV_8U, Scalar(255));
//
//        // �� bins�� 90%�� �ִ������� ����(�󵵼� �ִ� 256*0.9=230)
//        int hpt = static_cast<int>(0.9 * histSize[0]);
//        int maxH = 0; // �ִ� �� ��
//        int maxV = 0; // �󵵰� ���� ���� ȭ�� ��
//        for (int h = 0; h < 256; h++)  // �� �󵵿� ���� �������� �׸���
//        {
//            float binVal = hist.at<float>(h);
//            int intensity = static_cast<int>(binVal * hpt / maxVal);
//            line(histImg, Point(h, histSize[0]), Point(h, histSize[0] - intensity), Scalar::all(0)); // �׷��� �׸���
//            if (intensity > maxH) {
//                maxH = intensity;
//                maxV = h;
//            }
//        }
//        cout << maxV << endl;
//        return histImg;
//    }
//};
//int main()
//{
//    Mat image = imread("../Image/Lenna.png", 0);  // ����̹���
//
//    Histogram1D h; // ������׷� ��ü
//    Mat histo = h.getHistogram(image); // ������׷� ���
//
//    imshow("Image", image);
//    imshow("Histogram", h.getHistogramImage(image));
//
//    waitKey(0);
//    return 0;
//}




//// ������׷� ����ȭ - 2021/1/5
//#include <opencv2/opencv.hpp>
//using namespace cv;
//using namespace std;
//
//int main(int ac, char** av) {
//
//	Mat img_1 = imread("../Image/ThankYou.jpg", 0);
//
//	Mat hist_img;
//
//	equalizeHist(img_1, hist_img);
//	// equalizeHist(Input Array, Output Array) :
//	// Input Array(�Է� �̹���)�� ������׷� ������ ���ؼ� ����ȭ�� ���� �� �ش� ������ Output Array(��� �̹���)�� �����Ѵ�.
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

//// ���� ��� ���� (��������) - 2021/1/3
//#include <opencv2/opencv.hpp>
//
//using namespace cv;
//using namespace std;
//
//int main(int ac, char** av) {
//
//	Mat img_1 = imread("../Image/ThankYou.jpg", 0);
//
//	Mat img_2 = img_1 * 2;
//	Mat img_3 = img_1 / 2;
//
//	imshow("original", img_1);
//	imshow("img_mul", img_2);
//	imshow("img_div", img_3);
//
//	waitKey(0);
//
//	return 0;
//}


//// ���� ��� ���� (��������) - 2021/1/3
//#include <opencv2/opencv.hpp>
//using namespace cv;
//using namespace std;
//
//int main(int ac, char** av) {
//
//	Mat img_1 = imread("../Image/ThankYou.jpg", IMREAD_GRAYSCALE);
//
//	Mat img_2 = img_1 + 100; // ���
//	Mat img_3 = img_1 - 100; // ��Ӱ�
//
//	imshow("original", img_1);
//	imshow("img_sum", img_2);
//	imshow("img_sub", img_3);
//
//	waitKey(0);
//
//	return 0;
//}

////���� �׵θ� ��� (��, GRAYSCALE ������ ������. ����!) - 2021/1/2
//#include <opencv2/core.hpp>
//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp> // Canny �Լ��� ����ϱ� ���ؼ� �߰���.
//#include <opencv2/videoio.hpp>
//#include <iostream>
//#include <stdio.h>
//using namespace cv;
//using namespace std;
//
//
//int main(int ac, char** av) {
//
//	//Mat image = imread("../Image/ThankYou.jpg");
//	Mat image = imread("../Image/ThankYou.jpg", IMREAD_GRAYSCALE);
//
//
//
//	if (image.empty()) // �̹����� ������
//	{
//		cout << "�̹����� �����ϴ�." << endl;
//		return -1;
//	}
//
//
//	Canny(image, image, 50, 150); // ����! IMREAD_GRAYSCALE (������) �϶��� ��밡����! �ȱ׷��� ��������!
//
//
//	imshow("Original", image);
//	
//	waitKey(0); // ������ ������ wiatKey(1000) �� 1�� ��ٸ� �� ����.
//
//	return 0;
//}


//// ����ũ�� ���� - 2021/1/2
//#include <opencv2/core.hpp>
//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/videoio.hpp>
//#include <iostream>
//#include <stdio.h>
//
//using namespace cv;
//using namespace std;
//
//
//int main(int ac, char** av) {
//
//	Mat image = imread("../Image/ThankYou.jpg");
//
//
//
//	if (image.empty()) // �̹����� ������
//	{
//		cout << "�̹����� �����ϴ�." << endl;
//		return -1;
//	}
//
//
//	//namedWindow �� �̹����� ������ �����츦 ����
//	//namedWindow("Original", WINDOW_AUTOSIZE);
//	namedWindow("Original", WINDOW_NORMAL);
//	// WINDOW_AUTOSIZE �� �̹���ũ�⿡ �°� ������ ũ�Ⱑ ������.
//	// WINDOW_NORMAL �� �̹����� ū ��� �ػ� ũ�⿡ ���� ������ũ�Ⱑ �����ǰ�, ����ڰ� ������ ũ�⸦ ������ �� ����.
//
//
//	//��üȭ������ ��¡�
///*	namedWindow("Original", WND_PROP_FULLSCREEN);
//	setWindowProperty("Original", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);*/
//	// =======================================================
//
//
//	imshow("Original", image);
//
//	waitKey(0); // ������ ������ wiatKey(1000) �� 1�� ��ٸ� �� ����.
//
//	return 0;
//}



//// �̹��� ��ä�� ���� - 2021/1/2
//#include <opencv2/opencv.hpp>
//
//using namespace cv;
//using namespace std;
//
//int main(int ac, char** av) {
//
//	Mat color_img = imread("../Image/ThankYou.jpg");
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

//// ������ ��� - 2020/12/30
//#include <opencv2/core.hpp>
//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/videoio.hpp>
//#include <iostream>
//#include <stdio.h>
//
//using namespace cv;
//using namespace std;
//
//
//int main(int ac, char** av) {
//
//	//Mat image = imread("../Image/ThankYou.jpg");
//	Mat image = imread("../Image/ThankYou.jpg", IMREAD_GRAYSCALE);
//
//
//	if (image.empty()) // �̹����� ������
//	{
//		cout << "�̹����� �����ϴ�." << endl;
//		return -1;
//	}
//
//	
//
//
//	imshow("Title", image);
//
//	waitKey(0); // ������ ������ wiatKey(1000) �� 1�� ��ٸ� �� ����.
//
//	return 0;
//}


//// �̹��� ��� - 2020/12/30
//#include <opencv2/core.hpp> // opencv���� ����ϴ� �⺻���� �ڷᱸ���� �Լ����� ���Ե�����.
//#include <opencv2/imgcodecs.hpp> // �̹��� ������ �о���� �Լ��� �����ϴ� �Լ��� ����
//#include <opencv2/highgui.hpp> // �������̽��� �����س��� ���, ������� �Է��� �ޱ����� ����ϴ� �Լ��� ȭ�鿡 �̹����� �����ֱ� ���� �Լ��� ����
//#include <opencv2/videoio.hpp>
//#include <iostream>
//#include <stdio.h>
//
//using namespace cv;
//using namespace std;
//
//
//int main(int ac, char** av) {
//
//	Mat image = imread("../Image/ThankYou.jpg");
//
//
//
//	if (image.empty()) // �̹����� ������
//	{
//		cout << "�̹����� �����ϴ�." << endl;
//		return -1;
//	}
//
//	imshow("Title", image);
//
//	waitKey(0); // ������ ������ wiatKey(1000) �� 1�� ��ٸ� �� ����.
//
//	return 0;
//}