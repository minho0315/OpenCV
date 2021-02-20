#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <algorithm>
#include <cstdlib>
#include <map>
#include <string>
#include "transform.hpp"
#include <iostream>
#include <fstream>

#include <stdio.h>
#include <io.h>
#include <conio.h>

#include "tinyxml.h"

using namespace std;
using namespace cv;

const int NoOfChoice = 5;
const int NoOfQuestion = 20;
const int StudentNumber = 9;
const int recognitionValue = 100; // (100~169) 인식률 조절가능
int correctRate[NoOfQuestion]; //문제별 정답률 인식을 위한 변수
map<int, int> standardAnswer1;

map<int, double> Total;

vector<string> get_files_inDirectory(const string& _path, const string& _filter); //디렉터리에서 파일이름 가져오기
void omrScanner(string& fileName);
bool cmp(const pair<int, int>& a, const pair<int, int>& b);
void arrange(string& directoryName);

int main()
{
	string directoryName = "omr"; //default값
	string selectMode = "m"; //default값
	int count = 0;

	while (1) {
		cout << "모드 선택하세요(관리자모드 : m, 사용자모드: u) : ";
		cin >> selectMode;

		if (selectMode == "m") {
			count++;
			cout << "정답을 입력하세요!!(20문제)" << endl;
			for (int i = 0; i < NoOfQuestion; i++) {
				int answer = 0;
				cout << i + 1 << "번 " << "정답을 입력하세요(1~5) : ";
				cin >> answer;
				while (1) {
					if (answer < 1 || answer > 5) {
						cout << i + 1 << "번 " << "정답을 다시 입력하세요 : ";
						cin >> answer;
					}
					else {
						standardAnswer1.insert(make_pair(i, answer - 1));
						break;
					}
				}
			}

			while (1) {
				cout << "directory를 선택하세요(omr5, omr10, omr15, omr20) : ";
				cin >> directoryName;
				if (directoryName == "omr5" || directoryName == "omr10" || directoryName == "omr15" || directoryName == "omr20") {
					break;
				}
				else {
					cout << "omr5, omr10, omr15, omr20 중에 하나만 선택하세요!!!" << endl;
					continue;
				}

			}
		}
		else if (selectMode == "u") {
			if (count == 0) {
				//default값
				standardAnswer1.insert(make_pair(0, 0)); //Question 1: answer: A
				standardAnswer1.insert(make_pair(1, 1)); //Question 2: answer: B
				standardAnswer1.insert(make_pair(2, 3)); //Question 3: answer: D
				standardAnswer1.insert(make_pair(3, 0)); //Question 4: answer: A
				standardAnswer1.insert(make_pair(4, 2)); //Question 5: answer: C
				standardAnswer1.insert(make_pair(5, 1)); //Question 6: answer: B
				standardAnswer1.insert(make_pair(6, 0)); //Question 7: answer: A
				standardAnswer1.insert(make_pair(7, 1)); //Question 8: answer: B
				standardAnswer1.insert(make_pair(8, 2)); //Question 9: answer: C
				standardAnswer1.insert(make_pair(9, 3)); //Question 10: answer: D
				standardAnswer1.insert(make_pair(10, 1)); //Question 11: answer: B
				standardAnswer1.insert(make_pair(11, 3)); //Question 12: answer: D
				standardAnswer1.insert(make_pair(12, 2)); //Question 13: answer: C
				standardAnswer1.insert(make_pair(13, 2)); //Question 14: answer: C
				standardAnswer1.insert(make_pair(14, 1)); //Question 15: answer: B
				standardAnswer1.insert(make_pair(15, 0)); //Question 16: answer: A
				standardAnswer1.insert(make_pair(16, 1)); //Question 17: answer: B
				standardAnswer1.insert(make_pair(17, 3)); //Question 18: answer: D
				standardAnswer1.insert(make_pair(18, 0)); //Question 19: answer: A
				standardAnswer1.insert(make_pair(19, 1)); //Question 20: answer: B
			}
			break;
		}
		else {
			cout << "관리자모드 m 사용자모드 u 중에 하나만 선택하세요!!! 제발" << endl;
		}
	}

	vector<string> imgNames = get_files_inDirectory(directoryName + "\\", "*.png");

	for (auto i = imgNames.begin(); i != imgNames.end(); ++i)
	{
		string imgName = directoryName + "/" + *i;
		omrScanner(imgName);
	}
	
	arrange(directoryName);

	return 0;
}


vector<string> get_files_inDirectory(const string& _path, const string& _filter)
{
	string searching = _path + _filter;

	vector<string> return_;

	_finddata_t fd;
	intptr_t handle = _findfirst(searching.c_str(), &fd);  //현재 폴더 내 모든 파일을 찾는다.

	if (handle == -1)
	{
		cout << "Failed to read file" << endl;
		return return_;
	}

	int result = 0;
	do
	{
		return_.push_back(fd.name);
		result = _findnext(handle, &fd);
	} while (result != -1);

	_findclose(handle);

	return return_;
}

void omrScanner(string& fileName)
{

	map<int, int> testerAnswer1;

	Mat image, gray, blurred, edge;

	image = imread(fileName, IMREAD_COLOR);

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

	resize(paper, paper, Size(591, 838)); //사이즈 고정
	resize(warped, warped, Size(591, 838));


	// 관심영역 자르기
	Mat studentNumber = warped(Range(0, warped.rows), Range(0, warped.cols / 2));
	Mat studentNumbers = paper(Range(0, paper.rows), Range(0, paper.cols / 2));
	Mat questions = warped(Range(0, warped.rows), Range(warped.cols / 2, warped.cols));
	Mat questionss = paper(Range(0, paper.rows), Range(paper.cols / 2, paper.cols));


	///////////////////////////////////////// 학번 인식 //////////////////////////////////////////////////////
	Mat threshs;
	vector<vector<Point> > contourss;
	vector<Vec4i> hierarchys;

	threshold(studentNumber, threshs, 127, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU); //이진화
	findContours(threshs, contourss, hierarchys, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	//imshow("threshs", threshs);

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
			if (w >= 13 && h >= 13 && ar < 1.3 && ar > 0.7) {
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
			int a = countNonZero(mask);
			if (countNonZero(mask) > recognitionValue) // 배열 행렬 에서 0(검은색)이 아닌 픽셀의 수를 반환
			{
				answerKey += num * (int)pow(10, 8 - j);
				drawContours(studentNumbers, questionCnts, i, Scalar(255, 0, 0), 2, 8, hierarchys, 0, Point()); //인식한 원 파란색으로 표시
			}
		}
		id += answerKey;
		num++;
	}

	////////////////////////////////////////////////문제 인식//////////////////////////////////////////////////////////////

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
			if (w >= 13 && h >= 13 && ar < 1.3 && ar > 0.7) {
				questionCnt.push_back(contours_poly[i]);
			}


	}

	sort_contour(questionCnt, 0, (int)questionCnt.size(), string("top-to-bottom"));

	for (int i = 0; i < (int)questionCnt.size(); i = i + NoOfChoice)
	{
		sort_contour(questionCnt, i, i + NoOfChoice, string("left-to-right"));
	}

	list<int> emptyAnswer; //예외처리 : omr 체크를 안했을 때

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

		if (maxPixel < recognitionValue)  // 원의 크기(169pixel) : 인식률 조절가능
		{
			emptyAnswer.push_back(i / NoOfChoice);
			answerKey = NoOfChoice;
		}

		testerAnswer1.insert(make_pair(i / NoOfChoice - 1, answerKey));
		//cout << "Question: " << i / NoOfChoice  << " Tester's Answer: " << answerKey + 1 << "\n";
	}

	//Step 6: Lookup the correct answer in our answer key to determine if the user was correct in their choice.
	map<int, int>::const_iterator itStandardAnswer;
	map<int, int>::const_iterator itTesterAnswer;

	itStandardAnswer = standardAnswer1.begin();
	itTesterAnswer = testerAnswer1.begin();

	int correct = 0;
	int currentQuestion = 0;
	int i = 0;

	while (itStandardAnswer != standardAnswer1.end())
	{
		if (itStandardAnswer->second == itTesterAnswer->second)
		{
			correctRate[i]++;
			++correct;
			//Circle in GREEN
			drawContours(questionss, questionCnt, (currentQuestion * NoOfChoice) + itStandardAnswer->second, Scalar(0, 255, 0), 2, 8, hierarchy, 0, Point());
		}
		else //Circle in RED
		{
			drawContours(questionss, questionCnt, (currentQuestion * NoOfChoice) + itStandardAnswer->second, Scalar(0, 0, 255), 2, 8, hierarchy, 0, Point());
		}
		++i;
		++currentQuestion;
		++itTesterAnswer;
		++itStandardAnswer;
	}

	////////////////////////////////////////정리/////////////////////////////////////////////////////////////////

	double score = ((double)correct / NoOfQuestion * 100); // id 값 제외

	Scalar color;
	if (score >= 60.0)
		color = Scalar(0, 255, 0);
	else
		color = Scalar(0, 0, 255);

	putText(questionss, to_string((int)score) + "%", Point(20, 60), FONT_HERSHEY_SIMPLEX, 0.9, color, 2);

	cout << "학번 : " << id << endl;
	cout << "총 문제의 수 : " << currentQuestion << endl;
	cout << "맞은 정답의 수 : " << correct << endl;
	cout << "점수 : " << score << endl;
	cout << "인식률 : " << (double)(NoOfQuestion - emptyAnswer.size()) / NoOfQuestion * 100 << "%" << endl;
	if (emptyAnswer.size()) {
		cout << "문제 ";
		list<int>::iterator iter;
		for (iter = emptyAnswer.begin(); iter != emptyAnswer.end(); iter++) {
			cout << *iter << "번 ";
		}
		cout << "(총 " << emptyAnswer.size() << "문제) "<< "체크 안 했습니다." << endl;
	}
	cout << endl;
	Total.insert(make_pair(id, score));

	Mat sumImgs;
	hconcat(studentNumbers, questionss, sumImgs);

    //imshow("edge", edge);
	//imshow("Marked questionss", questionss);
	//imshow("Marked questions", questions);
	//imshow("studentNumbers", studentNumbers);
	//imshow("studentNumber", studentNumber);
	//imshow("Marked sumImgs", sumImgs);
	//waitKey();

}

bool cmp(const pair<int, int>& a, const pair<int, int>& b) { //vec 정렬을 위한 함수
	if (a.second == b.second) return a.first < b.first;
	return a.second > b.second;
}

void arrange(string& directoryName)
{
	double sum = 0;
	double average = 0;
	int stn = 0;

	ofstream resultList("resultList.txt"); //txt파일로 저장

	cout << "===========총합============" << endl;
	resultList << "===========총합============" << endl;

	map<int, double>::iterator iter;
	for (iter = Total.begin(); iter != Total.end(); iter++)
	{
		cout << "학번 : " << iter->first << " 점수 : " << iter->second << endl;
		sum += iter->second;

		resultList << "학번 : " << iter->first << " 점수 : " << iter->second << endl;
	}

	average = sum / Total.size();

	cout << "\n학생수는 " << Total.size() << "명 입니다." << endl;
	cout << "합계는 " << sum << "점 입니다." << endl;
	cout << "평균 점수는 " << average << "점 입니다." << endl;

	resultList << "학생수는 " << Total.size() << "명 입니다." << endl;
	resultList << "\n합계는 " << sum << "점 입니다." << endl;
	resultList << "평균 점수는 " << average << "점 입니다." << endl;

	vector<pair<int, double>> vec(Total.begin(), Total.end()); // 정렬을 위해 벡터로 전환
	sort(vec.begin(), vec.end(), cmp);

	cout << "\n===========성적순===========" << endl;
	resultList << "\n===========성적순===========" << endl;

	for (auto num : vec) {
		cout << num.first << "   " << num.second << endl;
		//cout  <<  "학생" << num.first << " " << num.second << "점" <<  endl;
		//printf("학생%2d %2d점 입니다.\n", num.first, num.second);
		resultList << num.first << "   " << num.second << endl;
	}
	
	cout << endl;
	resultList << endl;

	for (int i = 0; i < NoOfQuestion; i++) {
		cout << i + 1 << "번째 문제의 정답률은 " << (double)correctRate[i] / Total.size() * 100 << "%입니다." << endl;
		resultList << i + 1 << "번째 문제의 정답률은 " << (double)correctRate[i] / Total.size() * 100 << "%입니다." << endl;
	}
	cout << endl;

	resultList.close();

	//xml 선언
	TiXmlDocument doc;
	TiXmlDeclaration* pDec1 = new TiXmlDeclaration("1.0", "", "");
	doc.LinkEndChild(pDec1);

	//루트 노드 추가
	TiXmlElement* pRoot = new TiXmlElement("OMR");
	doc.LinkEndChild(pRoot);

	//주석 문장 추가
	TiXmlComment* pComment = new TiXmlComment();
	pComment->SetValue("Directory name");
	pRoot->LinkEndChild(pComment);


	const char* dNP = directoryName.c_str();
	// 하위노드 및 데이터 추가
	TiXmlElement* pElem = new TiXmlElement(dNP);
	pRoot->LinkEndChild(pElem);

	TiXmlElement* pSubElem;
	for (iter = Total.begin(); iter != Total.end(); iter++)
	{
		pSubElem = new TiXmlElement("student");
		pElem->LinkEndChild(pSubElem);
		pSubElem->SetAttribute("studentID", iter->first);
		pSubElem->SetAttribute("score", iter->second);
	}

	doc.SaveFile("resultList.xml");
}