// 원근 변환
#include "iostream"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    //Mat src = imread("Lenna.png");
    Mat src = imread("cloud.jpg");
    
    Point2f srcTri[4];
    srcTri[0] = Point2f(0.f, 0.f);
    srcTri[1] = Point2f(src.cols - 1.f, 0.f);
    srcTri[2] = Point2f(0.f, src.rows - 1.f);
    srcTri[3] = Point2f(src.cols - 1.f, src.rows - 1.f);

    Point2f dstTri[4];
    dstTri[0] = Point2f(0.f, src.rows * 0.33f);
    dstTri[1] = Point2f(src.cols * 0.85f, src.rows * 0.25f);
    dstTri[2] = Point2f(src.cols * 0.15f, src.rows * 0.7f);
    dstTri[3] = Point2f(src.cols * 0.85f, src.rows * 0.7f);

    Mat warp_mat = getPerspectiveTransform(srcTri, dstTri);
    Mat dst = Mat::zeros(src.rows, src.cols, src.type());
    warpPerspective(src, dst, warp_mat, dst.size());

    imshow("src", src);
    imshow("dst", dst);

    waitKey(0);

    return 0;
}

//// 아핀 변환
//#include "iostream"
//#include "opencv2/imgproc.hpp"
//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/highgui.hpp"
//
//using namespace std;
//using namespace cv;
//
//int main(int argc, char** argv)
//{
//    //Mat src = imread("Lenna.png");
//    Mat src = imread("cloud.jpg");
//
//    Point2f srcTri[3];
//    srcTri[0] = Point2f(0.f, 0.f);
//    srcTri[1] = Point2f(src.cols - 1.f, 0.f);
//    srcTri[2] = Point2f(0.f, src.rows - 1.f);
//
//    Point2f dstTri[3];
//    dstTri[0] = Point2f(0.f, src.rows * 0.33f);
//    dstTri[1] = Point2f(src.cols * 0.85f, src.rows * 0.25f);
//    dstTri[2] = Point2f(src.cols * 0.15f, src.rows * 0.7f);
//
//    Mat warp_mat = getAffineTransform(srcTri, dstTri);
//    Mat dst = Mat::zeros(src.rows, src.cols, src.type());
//    warpAffine(src, dst, warp_mat, dst.size());
//
//    imshow("src", src);
//    imshow("dst", dst);
//
//    waitKey(0);
//
//    return 0;
//}

//// 이미지 회전
//#include "iostream"
//#include "opencv2/imgproc.hpp"
//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/highgui.hpp"
//
//using namespace std;
//using namespace cv;
//
//int main(int argc, char** argv)
//{
//    //Mat src = imread("Lenna.png");
//    Mat src = imread("cloud.jpg");
//    Mat dst;
//
//    Point center = Point(src.cols / 2, src.rows / 2);
//    double angle = 45.0;
//    double scale = 1.0;
//
//    Mat rot_mat = getRotationMatrix2D(center, angle, scale);
//
//    warpAffine(src, dst, rot_mat, src.size());
//
//    imshow("src", src);
//    imshow("dst", dst);
//
//    waitKey(0);
//
//    return 0;
//}

//// 이미지 대칭
//#include "iostream"
//#include "opencv2/imgproc.hpp"
//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/highgui.hpp"
//
//using namespace std;
//using namespace cv;
//
//int main(int argc, char** argv)
//{
//	//Mat src = imread("Lenna.png");
//	Mat src = imread("cloud.jpg");
//	Mat dst;
//	Mat dst2;
//	Mat dst3;
//
//	flip(src, dst, 0); // X축 대칭
//	flip(src, dst2, 1); // Y축 대칭
//	flip(src, dst3, -1); // XY축 대칭
//
//	imshow("src", src);
//	imshow("dst", dst);
//	imshow("dst2", dst2);
//	imshow("dst3", dst3);
//
//	waitKey(0);
//
//	return 0;
//}

//// 이미지 크기조절
//#include "iostream"
//#include "opencv2/imgproc.hpp"
//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/highgui.hpp"
//
//using namespace std;
//using namespace cv;
//
//int main(int argc, char** argv)
//{
//	//Mat img = imread("Lenna.png");
//	Mat img = imread("cloud.jpg");
//
//	Mat img_big, img_small;
//
//	resize(img, img_big, Size(0, 0), 1.5, 1.5); // 상대적 크기
//	resize(img, img_small, Size(200, 200)); // 절대적 크기
//
//	imshow("original", img);
//	imshow("img_big", img_big);
//	imshow("img_small", img_small);
//
//	waitKey(0);
//
//	return 0;
//}

//// 이미지 확대 & 축소
//#include "iostream"
//#include "opencv2/imgproc.hpp"
//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/highgui.hpp"
//
//using namespace std;
//using namespace cv;
//
//int main(int argc, char** argv)
//{
//    //Mat src = imread("Lenna.png");
//    Mat src = imread("cloud.jpg");
//    Mat dst;
//    Mat dst2;
//
//    pyrUp(src, dst, Size(src.cols * 2, src.rows * 2));
//    pyrDown(src, dst2, Size(src.cols / 2, src.rows / 2));
//
//    imshow("src", src);
//    imshow("dst", dst);
//    imshow("dst2", dst2);
//
//    waitKey(0);
//
//    return 0;
//}