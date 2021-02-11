#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <algorithm>
#include <cstdlib>
#include <map>
#include <string>
#include "transform.hpp"

using namespace std;
using namespace cv;

const int NoOfChoice = 5;
const int NoOfQuestion = 20;
const int NoOfStudent = 10;
const int StudentNumber = 9;

void test() {

}

int main()
{
	map<int, int> standardAnswer1;
	map<int, int> testerAnswer1;


	standardAnswer1.insert(make_pair(0, 0)); //Question 1: answer: A
	standardAnswer1.insert(make_pair(1, 1)); //Question 2: answer: B
	standardAnswer1.insert(make_pair(2, 3)); //Question 3: answer: D
	standardAnswer1.insert(make_pair(3, 0)); //Question 4: answer: A
	standardAnswer1.insert(make_pair(4, 2)); //Question 5: answer: C
	standardAnswer1.insert(make_pair(5, 1)); //Question 6: answer: B
	standardAnswer1.insert(make_pair(6, 0)); //Question 7: answer: B
	standardAnswer1.insert(make_pair(7, 1)); //Question 7: answer: B
	standardAnswer1.insert(make_pair(8, 0)); //Question 7: answer: B
	standardAnswer1.insert(make_pair(9, 1)); //Question 7: answer: B
	standardAnswer1.insert(make_pair(10, 1)); //Question 7: answer: B
	standardAnswer1.insert(make_pair(11, 3)); //Question 7: answer: B
	standardAnswer1.insert(make_pair(12, 1)); //Question 7: answer: B
	standardAnswer1.insert(make_pair(13, 2)); //Question 7: answer: B
	standardAnswer1.insert(make_pair(14, 1)); //Question 7: answer: B
	standardAnswer1.insert(make_pair(15, 0)); //Question 7: answer: B
	standardAnswer1.insert(make_pair(16, 1)); //Question 7: answer: B
	standardAnswer1.insert(make_pair(17, 3)); //Question 7: answer: B
	standardAnswer1.insert(make_pair(18, 0)); //Question 7: answer: B
	standardAnswer1.insert(make_pair(19, 1)); //Question 7: answer: B


	Mat image, gray, blurred, edge;
	string filename = "omrTest/omr_test_10.png";

	image = imread(filename, IMREAD_COLOR);

	if (image.empty())
	{
		cout << "Failed to read file\n";
		exit(1);
	}

	cvtColor(image, gray, COLOR_BGR2GRAY); //gray
	GaussianBlur(gray, blurred, Size(5, 5), 0); //흐리게
	Canny(blurred, edge, 75, 200); //경계선

	Mat paper, warped, thresh;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	vector<Point> approxCurve, docCnt;

	/// Find contours
	findContours(edge, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0)); //외곽선추출
	sort(contours.begin(), contours.end(), compareContourAreas); //정렬

	//Find document countour
	for (const auto& element : contours)
	{
		double perimeter = arcLength(element, true); //둘레 폐곡선
		approxPolyDP(element, approxCurve, 0.05 * perimeter, true); //근사선

		if (approxCurve.size() == 4)
		{
			docCnt = approxCurve;
			break;
		}
	}

	//Step 2: Apply a perspective transform to extract the top-down, birds-eye-view of the exam

	four_point_transform(image, paper, docCnt); //원근변환
	four_point_transform(gray, warped, docCnt);

	// 관심영역 자르기
	Mat studentNumber = warped(Range(0, warped.rows), Range(0, warped.cols / 2));
	Mat studentNumbers = paper(Range(0, paper.rows), Range(0, paper.cols / 2));
	Mat questions = warped(Range(0, warped.rows), Range(warped.cols / 2, warped.cols));
	Mat questionss = paper(Range(0, paper.rows), Range(paper.cols / 2, paper.cols));


	//Step 3: Extract the sets of bubbles (questionCnt)

	threshold(questions, thresh, 127, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU); //이진화
	findContours(thresh, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));


	vector<vector<Point> > contours_poly(contours.size()); 
	vector<Rect> boundRect(contours.size());
	vector<vector<Point>> questionCnt;

	//Find document countour
	for (int i = 0; i < contours.size(); i++) //원검출
	{
		approxPolyDP(Mat(contours[i]), contours_poly[i], 0.1, true);
		int w = boundingRect(Mat(contours[i])).width;
		int h = boundingRect(Mat(contours[i])).height;
		double ar = (double)w / h;

		if (hierarchy[i][3] == -1) //No parent 
			if (w >= 13 && h >= 13 && ar < 1.2 && ar > 0.8) {
				questionCnt.push_back(contours_poly[i]);
			}


	}

	sort_contour(questionCnt, 0, (int)questionCnt.size(), string("top-to-bottom"));

	for (int i = 0; i < (int)questionCnt.size(); i = i + NoOfChoice)
	{
		sort_contour(questionCnt, i, i + NoOfChoice, string("left-to-right"));
	}

	//Step 5: Determine the marked answer
	for (int i = 0; i < questionCnt.size();)
	{
		int maxPixel = 0;
		int answerKey = 0;

		
		for (int j = 0; j < NoOfChoice; ++i, ++j) // 이미지에서 흰 픽셀 수가 많은 값을 선택한다.
		{
			Mat mask = Mat::zeros(thresh.size(), CV_8U);
			drawContours(mask, questionCnt, i, 255, CV_FILLED, 8, hierarchy, 0, Point());
			bitwise_and(mask, thresh, mask);

			if (countNonZero(mask) > maxPixel) // 배열 행렬 에서 0(검은색)이 아닌 픽셀의 수를 반환
			{
				maxPixel = countNonZero(mask);
				answerKey = j;
			}
		}

		testerAnswer1.insert(make_pair(i / NoOfChoice - 1, answerKey));
		cout << "Question: " << i / NoOfChoice  << " Tester's Answer: " << answerKey + 1 << "\n";
	}

	//Step 6: Lookup the correct answer in our answer key to determine if the user was correct in their choice.
	map<int, int>::const_iterator itStandardAnswer;
	map<int, int>::const_iterator itTesterAnswer;

	itStandardAnswer = standardAnswer1.begin();
	itTesterAnswer = testerAnswer1.begin();

	int correct = 0;
	int currentQuestion = 0;

	while (itStandardAnswer != standardAnswer1.end())
	{
		if (itStandardAnswer->second == itTesterAnswer->second)
		{
			++correct;
			//Circle in GREEN
			drawContours(questionss, questionCnt, (currentQuestion * NoOfChoice) + itStandardAnswer->second, Scalar(0, 255, 0), 2, 8, hierarchy, 0, Point());
		}
		else //Circle in RED
		{
			drawContours(questionss, questionCnt, (currentQuestion * NoOfChoice) + itStandardAnswer->second, Scalar(0, 0, 255), 2, 8, hierarchy, 0, Point());
		}

		++currentQuestion;
		++itTesterAnswer;
		++itStandardAnswer;
	}

	//Step 7: Display the score
	double score = ((double)correct / NoOfQuestion * 100); // id 값 제외

	Scalar color;
	if (score >= 60.0)
		color = Scalar(0, 255, 0);
	else
		color = Scalar(0, 0, 255);

	//putText(questionss, to_string((int)score) + "%", Point(20, 30), FONT_HERSHEY_SIMPLEX, 0.9, color, 2);

	cout << "학생" << "의 성적" << endl;
	cout << "총 문제의 수 : " << currentQuestion << endl;
	cout << "맞은 정답의 수 : " << correct << endl;
	cout << "점수는 " << score << "점 입니다." << "" << endl;
	cout << endl;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Mat threshs;
	vector<vector<Point> > contourss;
	vector<Vec4i> hierarchys;

	threshold(studentNumber, threshs, 127, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU); //이진화
	findContours(threshs, contourss, hierarchys, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	vector<vector<Point> > contours_polys(contourss.size());
	vector<Rect> boundRects(contourss.size());
	vector<vector<Point>> questionCnts;

	//Find document countour
	for (int i = 0; i < contourss.size(); i++) //원검출
	{
		approxPolyDP(Mat(contourss[i]), contours_polys[i], 0.1, true);
		int w = boundingRect(Mat(contourss[i])).width;
		int h = boundingRect(Mat(contourss[i])).height;
		double ar = (double)w / h;

		if (hierarchys[i][3] == -1) //No parent 
			if (w >= 13 && h >= 13 && ar < 1.2 && ar > 0.8) {
				questionCnts.push_back(contours_polys[i]);
			}
	}

	sort_contour(questionCnts, 0, (int)questionCnts.size(), string("top-to-bottom"));

	for (int i = 0; i < (int)questionCnts.size(); i = i + StudentNumber)
	{
		sort_contour(questionCnts, i, i + StudentNumber, string("left-to-right"));
	}

	int num = 0;
	int id = 0;

	//Step 5: Determine the marked answer
	for (int i = 0; i < questionCnts.size();)
	{
		
		int answerKey = 0;

		for (int j = 0; j < StudentNumber; ++i, ++j) // 이미지에서 흰 픽셀 수가 많은 값을 선택한다.
		{
			Mat mask = Mat::zeros(threshs.size(), CV_8U);
			drawContours(mask, questionCnts, i, 255, CV_FILLED, 8, hierarchys, 0, Point());
			bitwise_and(mask, threshs, mask);

			if (countNonZero(mask) > 160) // 배열 행렬 에서 0(검은색)이 아닌 픽셀의 수를 반환
			{
				answerKey += num * pow(10, 8-j);
				drawContours(studentNumbers, questionCnts, i, Scalar(255, 0, 0), 2, 8, hierarchys, 0, Point()); //인식한 원 파란색으로 표시
			}
		}
		id += answerKey;
		num++;
	}

	cout << "학번 : " << id << endl;


	Mat sumImgs;
	hconcat(studentNumbers, questionss, sumImgs);

	//imshow("Marked questionss", questionss);
	//imshow("studentNumbers", studentNumbers);
	imshow("Marked sumImgs", sumImgs);


	waitKey();
	return 0;
}
