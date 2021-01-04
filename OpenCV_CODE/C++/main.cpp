// ���� ��� ����
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main(int ac, char** av) {

	Mat img_1 = imread("../Image/ThankYou.jpg", IMREAD_GRAYSCALE);

	Mat img_2 = img_1 + 100; // ���
	Mat img_3 = img_1 - 100; // ��Ӱ�

	imshow("original", img_1);
	imshow("img_sum", img_2);
	imshow("img_sub", img_3);

	waitKey(0);

	return 0;
}

////���� ���� ��� (��, GRAYSCALE ������ ������. ����!)
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


//// ����ũ�� ����
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


//// ������ ���
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


//// �̹��� ���
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