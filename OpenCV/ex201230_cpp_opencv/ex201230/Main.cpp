#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;


/* c++에 opencv 연결
1. opencv 라이브러리 다운로드하여 실행
2. vs에서 빈프로젝트 생성
3. 상단바 프로젝트 -> [프로젝트이름] 속성 클릭
	1) 구성을 모든구성으로 플랫폼을 x64로 변경
	2) c/c++  ->  일반
		(1) 추가 포함 디렉토리에 opencv\build\include 의 절대 경로 추가
	3) 링커 
		(1) [-> 일반] 추가 라이브러리 디렉터리에 opencv\build\x64\vc15\lib 의 절대 경로 추가
		(2) [-> 입력] 추가 종속성에 opencv\build\x64\vc15\lib 안에 있는 opencv_world[버전숫자]d.lib를 ;(세미콜론)을 포함하여 추가
4. 상단바 아래에 있는 Debug 옆에 x64로 잘 설정되어 있는지 확인
5. 자신의 프로젝트 폴더에 opencv\build\x64\vc15\bin 에 있는 opencv_world[버전숫자]d.dll 파일과 
	opencv_world[버전숫자].dll을 복사 붙여넣기
*/

int main(int ac, char** av) {

	Mat img = imread("Lenna.png"); //자신이 저장시킨 이미지 이름이 입력되어야 함, 확장자까지

	imshow("img", img);
	waitKey(0);

	return 0;
}