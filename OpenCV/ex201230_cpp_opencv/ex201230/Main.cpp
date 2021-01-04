#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;


/* c++�� opencv ����
1. opencv ���̺귯�� �ٿ�ε��Ͽ� ����
2. vs���� ��������Ʈ ����
3. ��ܹ� ������Ʈ -> [������Ʈ�̸�] �Ӽ� Ŭ��
	1) ������ ��籸������ �÷����� x64�� ����
	2) c/c++  ->  �Ϲ�
		(1) �߰� ���� ���丮�� opencv\build\include �� ���� ��� �߰�
	3) ��Ŀ 
		(1) [-> �Ϲ�] �߰� ���̺귯�� ���͸��� opencv\build\x64\vc15\lib �� ���� ��� �߰�
		(2) [-> �Է�] �߰� ���Ӽ��� opencv\build\x64\vc15\lib �ȿ� �ִ� opencv_world[��������]d.lib�� ;(�����ݷ�)�� �����Ͽ� �߰�
4. ��ܹ� �Ʒ��� �ִ� Debug ���� x64�� �� �����Ǿ� �ִ��� Ȯ��
5. �ڽ��� ������Ʈ ������ opencv\build\x64\vc15\bin �� �ִ� opencv_world[��������]d.dll ���ϰ� 
	opencv_world[��������].dll�� ���� �ٿ��ֱ�
*/

int main(int ac, char** av) {

	Mat img = imread("Lenna.png"); //�ڽ��� �����Ų �̹��� �̸��� �ԷµǾ�� ��, Ȯ���ڱ���

	imshow("img", img);
	waitKey(0);

	return 0;
}