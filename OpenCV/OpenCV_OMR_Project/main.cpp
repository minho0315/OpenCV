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
const int recognitionValue = 100; // (100~169) �νķ� ��������
int correctRate[NoOfQuestion]; //������ ����� �ν��� ���� ����
map<int, int> standardAnswer1;

map<int, double> Total;

vector<string> get_files_inDirectory(const string& _path, const string& _filter); //���͸����� �����̸� ��������
void omrScanner(string& fileName);
bool cmp(const pair<int, int>& a, const pair<int, int>& b);
void arrange(string& directoryName);

int main()
{
	string directoryName = "omr"; //default��
	string selectMode = "m"; //default��
	int count = 0;

	while (1) {
		cout << "��� �����ϼ���(�����ڸ�� : m, ����ڸ��: u) : ";
		cin >> selectMode;

		if (selectMode == "m") {
			count++;
			cout << "������ �Է��ϼ���!!(20����)" << endl;
			for (int i = 0; i < NoOfQuestion; i++) {
				int answer = 0;
				cout << i + 1 << "�� " << "������ �Է��ϼ���(1~5) : ";
				cin >> answer;
				while (1) {
					if (answer < 1 || answer > 5) {
						cout << i + 1 << "�� " << "������ �ٽ� �Է��ϼ��� : ";
						cin >> answer;
					}
					else {
						standardAnswer1.insert(make_pair(i, answer - 1));
						break;
					}
				}
			}

			while (1) {
				cout << "directory�� �����ϼ���(omr5, omr10, omr15, omr20) : ";
				cin >> directoryName;
				if (directoryName == "omr5" || directoryName == "omr10" || directoryName == "omr15" || directoryName == "omr20") {
					break;
				}
				else {
					cout << "omr5, omr10, omr15, omr20 �߿� �ϳ��� �����ϼ���!!!" << endl;
					continue;
				}

			}
		}
		else if (selectMode == "u") {
			if (count == 0) {
				//default��
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
			cout << "�����ڸ�� m ����ڸ�� u �߿� �ϳ��� �����ϼ���!!! ����" << endl;
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
	intptr_t handle = _findfirst(searching.c_str(), &fd);  //���� ���� �� ��� ������ ã�´�.

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
	GaussianBlur(gray, blurred, Size(5, 5), 0); //�帮��
	Canny(blurred, edge, 75, 200); //��輱

	Mat paper, warped, thresh;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	vector<Point> approxCurve, docCnt;

	/// Find contours
	findContours(edge, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0)); //�ܰ�������
	sort(contours.begin(), contours.end(), compareContourAreas); //����

	//Find document countour
	for (const auto& element : contours)
	{
		double perimeter = arcLength(element, true); //�ѷ� ��
		approxPolyDP(element, approxCurve, 0.05 * perimeter, true); //�ٻ缱

		if (approxCurve.size() == 4)
		{
			docCnt = approxCurve;
			break;
		}
	}

	//Step 2: Apply a perspective transform to extract the top-down, birds-eye-view of the exam

	four_point_transform(image, paper, docCnt); //���ٺ�ȯ
	four_point_transform(gray, warped, docCnt);

	resize(paper, paper, Size(591, 838)); //������ ����
	resize(warped, warped, Size(591, 838));


	// ���ɿ��� �ڸ���
	Mat studentNumber = warped(Range(0, warped.rows), Range(0, warped.cols / 2));
	Mat studentNumbers = paper(Range(0, paper.rows), Range(0, paper.cols / 2));
	Mat questions = warped(Range(0, warped.rows), Range(warped.cols / 2, warped.cols));
	Mat questionss = paper(Range(0, paper.rows), Range(paper.cols / 2, paper.cols));


	///////////////////////////////////////// �й� �ν� //////////////////////////////////////////////////////
	Mat threshs;
	vector<vector<Point> > contourss;
	vector<Vec4i> hierarchys;

	threshold(studentNumber, threshs, 127, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU); //����ȭ
	findContours(threshs, contourss, hierarchys, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	//imshow("threshs", threshs);

	vector<vector<Point> > contours_polys(contourss.size());
	vector<Rect> boundRects(contourss.size());
	vector<vector<Point>> questionCnts;

	//Find document countour
	for (int i = 0; i < contourss.size(); i++) //������
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


		for (int j = 0; j < StudentNumber; ++i, ++j) // �̹������� �� �ȼ� ���� ���� ���� �����Ѵ�.
		{
			Mat mask = Mat::zeros(threshs.size(), CV_8U);
			drawContours(mask, questionCnts, i, 255, CV_FILLED, 8, hierarchys, 0, Point());
			bitwise_and(mask, threshs, mask);
			int a = countNonZero(mask);
			if (countNonZero(mask) > recognitionValue) // �迭 ��� ���� 0(������)�� �ƴ� �ȼ��� ���� ��ȯ
			{
				answerKey += num * (int)pow(10, 8 - j);
				drawContours(studentNumbers, questionCnts, i, Scalar(255, 0, 0), 2, 8, hierarchys, 0, Point()); //�ν��� �� �Ķ������� ǥ��
			}
		}
		id += answerKey;
		num++;
	}

	////////////////////////////////////////////////���� �ν�//////////////////////////////////////////////////////////////

	threshold(questions, thresh, 127, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU); //����ȭ
	findContours(thresh, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));


	vector<vector<Point> > contours_poly(contours.size());
	vector<Rect> boundRect(contours.size());
	vector<vector<Point>> questionCnt;

	//Find document countour
	for (int i = 0; i < contours.size(); i++) //������
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

	list<int> emptyAnswer; //����ó�� : omr üũ�� ������ ��

	//Step 5: Determine the marked answer
	for (int i = 0; i < questionCnt.size();)
	{
		int maxPixel = 0;
		int answerKey = 0;


		for (int j = 0; j < NoOfChoice; ++i, ++j) // �̹������� �� �ȼ� ���� ���� ���� �����Ѵ�.
		{
			Mat mask = Mat::zeros(thresh.size(), CV_8U);
			drawContours(mask, questionCnt, i, 255, CV_FILLED, 8, hierarchy, 0, Point());
			bitwise_and(mask, thresh, mask);
			if (countNonZero(mask) > maxPixel) // �迭 ��� ���� 0(������)�� �ƴ� �ȼ��� ���� ��ȯ
			{
				maxPixel = countNonZero(mask);
				answerKey = j;
			}
		}

		if (maxPixel < recognitionValue)  // ���� ũ��(169pixel) : �νķ� ��������
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

	////////////////////////////////////////����/////////////////////////////////////////////////////////////////

	double score = ((double)correct / NoOfQuestion * 100); // id �� ����

	Scalar color;
	if (score >= 60.0)
		color = Scalar(0, 255, 0);
	else
		color = Scalar(0, 0, 255);

	putText(questionss, to_string((int)score) + "%", Point(20, 60), FONT_HERSHEY_SIMPLEX, 0.9, color, 2);

	cout << "�й� : " << id << endl;
	cout << "�� ������ �� : " << currentQuestion << endl;
	cout << "���� ������ �� : " << correct << endl;
	cout << "���� : " << score << endl;
	cout << "�νķ� : " << (double)(NoOfQuestion - emptyAnswer.size()) / NoOfQuestion * 100 << "%" << endl;
	if (emptyAnswer.size()) {
		cout << "���� ";
		list<int>::iterator iter;
		for (iter = emptyAnswer.begin(); iter != emptyAnswer.end(); iter++) {
			cout << *iter << "�� ";
		}
		cout << "(�� " << emptyAnswer.size() << "����) "<< "üũ �� �߽��ϴ�." << endl;
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

bool cmp(const pair<int, int>& a, const pair<int, int>& b) { //vec ������ ���� �Լ�
	if (a.second == b.second) return a.first < b.first;
	return a.second > b.second;
}

void arrange(string& directoryName)
{
	double sum = 0;
	double average = 0;
	int stn = 0;

	ofstream resultList("resultList.txt"); //txt���Ϸ� ����

	cout << "===========����============" << endl;
	resultList << "===========����============" << endl;

	map<int, double>::iterator iter;
	for (iter = Total.begin(); iter != Total.end(); iter++)
	{
		cout << "�й� : " << iter->first << " ���� : " << iter->second << endl;
		sum += iter->second;

		resultList << "�й� : " << iter->first << " ���� : " << iter->second << endl;
	}

	average = sum / Total.size();

	cout << "\n�л����� " << Total.size() << "�� �Դϴ�." << endl;
	cout << "�հ�� " << sum << "�� �Դϴ�." << endl;
	cout << "��� ������ " << average << "�� �Դϴ�." << endl;

	resultList << "�л����� " << Total.size() << "�� �Դϴ�." << endl;
	resultList << "\n�հ�� " << sum << "�� �Դϴ�." << endl;
	resultList << "��� ������ " << average << "�� �Դϴ�." << endl;

	vector<pair<int, double>> vec(Total.begin(), Total.end()); // ������ ���� ���ͷ� ��ȯ
	sort(vec.begin(), vec.end(), cmp);

	cout << "\n===========������===========" << endl;
	resultList << "\n===========������===========" << endl;

	for (auto num : vec) {
		cout << num.first << "   " << num.second << endl;
		//cout  <<  "�л�" << num.first << " " << num.second << "��" <<  endl;
		//printf("�л�%2d %2d�� �Դϴ�.\n", num.first, num.second);
		resultList << num.first << "   " << num.second << endl;
	}
	
	cout << endl;
	resultList << endl;

	for (int i = 0; i < NoOfQuestion; i++) {
		cout << i + 1 << "��° ������ ������� " << (double)correctRate[i] / Total.size() * 100 << "%�Դϴ�." << endl;
		resultList << i + 1 << "��° ������ ������� " << (double)correctRate[i] / Total.size() * 100 << "%�Դϴ�." << endl;
	}
	cout << endl;

	resultList.close();

	//xml ����
	TiXmlDocument doc;
	TiXmlDeclaration* pDec1 = new TiXmlDeclaration("1.0", "", "");
	doc.LinkEndChild(pDec1);

	//��Ʈ ��� �߰�
	TiXmlElement* pRoot = new TiXmlElement("OMR");
	doc.LinkEndChild(pRoot);

	//�ּ� ���� �߰�
	TiXmlComment* pComment = new TiXmlComment();
	pComment->SetValue("Directory name");
	pRoot->LinkEndChild(pComment);


	const char* dNP = directoryName.c_str();
	// ������� �� ������ �߰�
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