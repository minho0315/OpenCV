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
const int NoOfQuestion = 6;
const int NoOfStudent = 10;

map<int, int> answerAll;

void OMR(int n)
{
	map<int, int> standardAnswer;
	map<int, int> testerAnswer;

	standardAnswer.insert(make_pair(0, 0)); //id default
	standardAnswer.insert(make_pair(1, 1)); //Question 1: answer: B
	standardAnswer.insert(make_pair(2, 3)); //Question 2: answer: D
	standardAnswer.insert(make_pair(3, 0)); //Question 3: answer: A
	standardAnswer.insert(make_pair(4, 2)); //Question 4: answer: C
	standardAnswer.insert(make_pair(5, 1)); //Question 5: answer: B

	//Step 1: Detect the exam in an image
	Mat image, gray, blurred, edge;
	string filename = "omr2/omr_test_";
	filename.append(to_string(n));
	filename.append(".png");

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

	//Step 3: Extract the sets of bubbles (questionCnt)

	threshold(warped, thresh, 127, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU); //이진화
	findContours(thresh, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, Point(0, 0)); 

	//imshow("thresh", thresh);

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
			if (w >= 20 && h >= 20 && ar < 1.1 && ar > 0.9)
				questionCnt.push_back(contours_poly[i]);


	}

	//Step 4: Sort the questions/bubbles into rows. //문제정렬

	sort_contour(questionCnt, 0, (int)questionCnt.size(), string("top-to-bottom"));

	for (int i = 0; i < questionCnt.size(); i = i + NoOfChoice)
	{
		sort_contour(questionCnt, i, i + 5, string("left-to-right"));
	}

	//Step 5: Determine the marked answer
	for (int i = 0; i < questionCnt.size();)
	{
		int maxPixel = 0;
		int answerKey = 0;

		if (i == 0) //id값 인식
		{
			for (int j = 0; j < NoOfChoice; ++i, ++j) // 이미지에서 흰 픽셀 수가 많은 값을 선택한다.
			{
				Mat mask = Mat::zeros(thresh.size(), CV_8U);
				drawContours(mask, questionCnt, i, 255, CV_FILLED, 8, hierarchy, 0, Point());
				bitwise_and(mask, thresh, mask);

				if (countNonZero(mask) > 500) // 배열 행렬 에서 0(검은색)이 아닌 픽셀의 수를 반환
				{
					drawContours(paper, questionCnt, j, Scalar(255, 0, 0), 2, 8, hierarchy, 0, Point()); //인식한 원 파란색으로 표시
					answerKey += pow(2,4-j); // 2진수 값 합계
				}
			}
		}
		else { //문제 계산
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
		}

		testerAnswer.insert(make_pair(i / NoOfChoice - 1, answerKey));

		if (i / NoOfChoice != 1) // id값 제외
		{
			cout << "Question: " << i / NoOfChoice - 1 << " Tester's Answer: " << answerKey + 1 << "\n";
		}
	}

	//Step 6: Lookup the correct answer in our answer key to determine if the user was correct in their choice.
	map<int, int>::const_iterator itStandardAnswer;
	map<int, int>::const_iterator itTesterAnswer;

	itStandardAnswer = standardAnswer.begin();
	itTesterAnswer = testerAnswer.begin();

	int correct = 0;
	int currentQuestion = 0;
	int id = 0; // id값

	while (itStandardAnswer != standardAnswer.end())
	{
		if (itStandardAnswer == standardAnswer.begin())
		{
			//drawContours(paper, questionCnt, (currentQuestion * NoOfChoice) + itTesterAnswer->second, Scalar(255, 0, 0), 2, 8, hierarchy, 0, Point());
			id = itTesterAnswer->second;
			++currentQuestion;
			++itTesterAnswer;
			++itStandardAnswer;

			continue;
		}
		if (itStandardAnswer->second == itTesterAnswer->second)
		{
			++correct;
			//Circle in GREEN
			drawContours(paper, questionCnt, (currentQuestion * NoOfChoice) + itStandardAnswer->second, Scalar(0, 255, 0), 2, 8, hierarchy, 0, Point());
		}
		else //Circle in RED
		{
			drawContours(paper, questionCnt, (currentQuestion * NoOfChoice) + itStandardAnswer->second, Scalar(0, 0, 255), 2, 8, hierarchy, 0, Point());
		}

		++currentQuestion;
		++itTesterAnswer;
		++itStandardAnswer;
	}

	//Step 7: Display the score
	double score = ((double)correct / (NoOfQuestion - 1) * 100); // id 값 제외

	Scalar color;
	if (score >= 60.0)
		color = Scalar(0, 255, 0);
	else
		color = Scalar(0, 0, 255);

	putText(paper, to_string((int)score) + "%", Point(20, 30), FONT_HERSHEY_SIMPLEX, 0.9, color, 2);

	//cout << "학생" << id << "의 성적" << endl;
	printf("학생%2d의 성적\n", id);
	cout << "총 문제의 수 : " << currentQuestion - 1 << endl;
	cout << "맞은 정답의 수 : " << correct << endl;
	cout << "점수는 " << score << "점 입니다." << "" << endl;
	cout << endl;

	imshow("Marked Paper", paper);
	waitKey();

	answerAll.insert(make_pair(id, score)); //id값 추가
}

bool cmp(const pair<int, int>& a, const pair<int, int>& b) { //vec 정렬을 위한 함수
	if (a.second == b.second) return a.first < b.first;
	return a.second > b.second;
}

int main()
{
	for (int i = 0; i < NoOfStudent; i++)
		OMR(i + 1);

	double sum = 0;
	double average = 0;
	map<int, int>::const_iterator itAnswerAll;
	itAnswerAll = answerAll.begin();

	cout << "===========총합============" << endl;

	while (itAnswerAll != answerAll.end())
	{
		//cout << "학생" << itAnswerAll->first << "의 점수는 " << itAnswerAll->second << "점 입니다." << endl;
		printf("학생%2d의 점수는 %2d점 입니다.\n", itAnswerAll->first, itAnswerAll->second);
		sum += itAnswerAll->second;
		++itAnswerAll;
	}

	average = sum / answerAll.size();

	cout << "\n합계는 " << sum << "점 입니다." << endl;
	cout << "평균 점수는 " << average << "점 입니다." << endl;

	vector<pair<int, int>> vec(answerAll.begin(), answerAll.end()); // 정렬을 위해 벡터로 전환
	sort(vec.begin(), vec.end(), cmp);

	cout << "\n===========등수===========" << endl;

	for (auto num : vec) {
		//cout  <<  "학생" << num.first << " " << num.second << "점" <<  endl;
		printf("학생%2d %2d점 입니다.\n", num.first, num.second);

	}

	return 0;
}
