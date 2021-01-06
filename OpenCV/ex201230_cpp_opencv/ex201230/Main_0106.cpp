#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int main(int ac, char** av) {

	/*�̹��� �ҷ�����*/
	Mat img1 = imread("Lenna.png", 1); //�ڽ��� �����Ų �̹��� �̸��� �ԷµǾ�� ��, Ȯ���ڱ���
	//���� ������Ʈ ���� �ִٸ� "" �ȿ� �����, �ƴ϶�� ���� ��� �Է�
	//1�̶�� ���� �κ��� flag, 1�� default �����̴�.
	//1 = �������� ���Կ��� �ҷ��´�.
	//0=�̹��� ������ ������� ��ȯ�Ͽ� �ҷ��´�.
	//-1=�̹��� ������ �������� ���� ä�α��� �����Ͽ� �ҷ��´�. 
	//reduced �ɼ��� ����ϸ� ũ�� ������ ����
	Mat img2 = imread("Lenna.png", 0);
	Mat img3 = imread("Lenna.png", -1);


	imshow("img flag 1", img1); //img�� ��� ������â Ÿ��Ʋ �̸��� "img"
	imshow("img flag 0", img2);
	imshow("img flag -1", img3);
	waitKey(0);//Ű�Է��� ��ٸ� �ð��� 0�̶�� �ǹ�

	/*�̹��� ��ä�� ����*/
	// cvtColor( input Array,  output Array, flag)
	// - input Array�� �Է¹޾� flag �� ���� �ɼ����� �̹��� ��ä���� �����Ͽ� output Array�� �����Ѵ�.
	// - �÷� �� ä���� �ٷ� ��� BGR ���̴�.
	Mat color_img = imread("Lenna.png");
	Mat grayscale_img;

	cvtColor(color_img, grayscale_img, COLOR_BGR2GRAY);//grayscale�� ��ä�� ����, ���ڸ� 6���� �൵ �Ȱ��� ����
	
	imshow("color_img", color_img);
	imshow("grayscale_img", grayscale_img);
	waitKey(0);


	/*�̹��� ��� ����*/
	//OpenCV������ �� �ȼ��� ���鿡 ���� �ִ밪255 �ּҰ� 0�� ������ ����� �ʵ��� ����ó���� ���ش�

	Mat img_2 = img2 + 100; //��ü������ �������.
	Mat img_3 = img2 - 100; //��ü������ ��ο�����. 100�� ������ �� �ּҰ� 0�� �Ǵ� �ȼ��� ���� ��ü������ ��Ӱ� ��������.
	Mat img_4 = img2 * 2;//��Ҵ� �κ��� �ξ� ���
	Mat img_5 = img2 / 2;//������ �������� ���������� ��ο�����.

	imshow("original", img2);
	imshow("img_sum", img_2);
	imshow("img_sub", img_3);
	imshow("img_mul", img_4);
	imshow("img_div", img_5);
	waitKey(0);

	return 0;
}