#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(void)
{
	QRCodeDetector detector;

	Mat frame, gray;
	frame = imread("qr7.jpg");

	if (frame.empty()) {
		cerr << "Frame load failed!" << endl;
		return -1;
	}

	cvtColor(frame, gray, COLOR_BGR2GRAY);

	vector<Point> points;

	if (detector.detect(gray, points)) {
		polylines(frame, points, true, Scalar(0, 255, 255), 2);

		String info = detector.decode(gray, points);
		if (!info.empty()) {
			polylines(frame, points, true, Scalar(0, 0, 255), 2);
			cout << "Decoded Data : " << info << endl;
		}
		
	}
	else
		cout << "QR Code not detected" << endl;

	imshow("frame", frame);
	waitKey(0);

	return 0;
}

//#include <opencv2/objdetect.hpp>
//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//void display(Mat& im, Mat& bbox)
//{
//    int n = bbox.rows;
//    for (int i = 0; i < n; i++)
//    {
//        line(im, Point2i(bbox.at<float>(i, 0), bbox.at<float>(i, 1)), Point2i(bbox.at<float>((i + 1) % n, 0),
//            bbox.at<float>((i + 1) % n, 1)), Scalar(255, 0, 0), 3);
//    }
//    imshow("Result", im);
//}
//
//int main(int argc, char* argv[])
//{
//    // Read image
//    Mat inputImage;
//    if (argc > 1)
//        inputImage = imread(argv[1]);
//    else
//        inputImage = imread("qrcode2.png");
//
//    QRCodeDetector qrDecoder = QRCodeDetector::QRCodeDetector();
//
//    Mat bbox, rectifiedImage;
//
//    std::string data = qrDecoder.detectAndDecode(inputImage, bbox, rectifiedImage);
//    if (data.length() > 0)
//    {
//        cout << "Decoded Data : " << data << endl;
//
//        display(inputImage, bbox);
//        rectifiedImage.convertTo(rectifiedImage, CV_8UC3);
//        imshow("Rectified QRCode", rectifiedImage);
//
//        waitKey(0);
//    }
//    else
//        cout << "QR Code not detected" << endl;
//}
