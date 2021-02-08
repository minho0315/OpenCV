#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <algorithm>
#include <cstdlib>
#include <map>
#include "transform.hpp"
#include <string>
using namespace std;
using namespace cv;
const int NoOfChoice = 5;
const int NoOfQuestion = 6;
int i = 1; // 몇번째 학생인지를 나타내는 변수
map<int, int> answerAll;

void OMR()
{
    map<int, int> standardAnswer; // 원래 정답
    map<int, int> testerAnswer; // 학생의 답변
    standardAnswer.insert(make_pair(0, 0));
    standardAnswer.insert(make_pair(1, 1)); //Question 1: answer: B
    standardAnswer.insert(make_pair(2, 3)); //Question 2: answer: D
    standardAnswer.insert(make_pair(3, 0)); //Question 3: answer: A
    standardAnswer.insert(make_pair(4, 2)); //Question 4: answer: C
    standardAnswer.insert(make_pair(5, 1)); //Question 5: answer: B
    // make_pair(변수1, 변수2) 변수1과 변수2가 들어간 pair를 만들어줌

    Mat image, gray, blurred, edge;

    // 이미지파일을 상황에 맞게 불러오기 (string.append , to_string() 사용)
    string filename = "omr2/omr_test_";
    filename.append(to_string(i));
    filename.append(".png");

    image = imread(filename, IMREAD_COLOR);
    // image = imread("omr_test_(?).png");


    if (image.empty()) // 이미지가 없을때
    {
        cout << i << "번째 학생의 OMR 이미지가 없습니다." << endl;
        exit(1);
    }

    // 이미지 처리
    cvtColor(image, gray, COLOR_BGR2GRAY); // 흑백화
    GaussianBlur(gray, blurred, Size(5, 5), 0); // 블러처리
    Canny(blurred, edge, 75, 200); // 경계선


    Mat paper, warped, thresh;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    vector<Point> approxCurve, docCnt;

    // 외곽선 검출하는 코드
    findContours(edge, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
    // CV_RETR_EXTERNAL : 오직 초외곽 외곽선만을 검출
    // CV_CHAIN_APPROX_SIMPLE : 수평, 수직, 대각 성분의 끝 점만 저장

    // 정렬
    sort(contours.begin(), contours.end(), compareContourAreas);


    // 문서의 외곽선 인식
    for (const auto& element : contours)
    {
        double perimeter = arcLength(element, true); // 외곽선 길이 반환
        approxPolyDP(element, approxCurve, 0.05 * perimeter, true);

        if (approxCurve.size() == 4) // 사각형 검출(OMR 카드)
        {
            docCnt = approxCurve;
            break;
        }
    }


    //Step 2: OMR시험지를 인식하기 위해 변형 (OMR 카드를 점 4개를 받아서 기하학적으로 펼치거나 좁힘.)

    four_point_transform(image, paper, docCnt); // docCnt는 문서의 꼭짓점 4개
    four_point_transform(gray, warped, docCnt);


    //Step 3: Extract the sets of bubbles (questionCnt)
    threshold(warped, thresh, 127, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU); // 이진화
    //imshow("thresh", thresh);


    findContours(thresh, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, Point(0, 0)); // 외곽선 검출

    vector<vector<Point> > contours_poly(contours.size());
    vector<Rect> boundRect(contours.size());
    vector<vector<Point>> questionCnt;


    //Find document countour
    for (int i = 0; i < contours.size(); i++)
    {
        approxPolyDP(Mat(contours[i]), contours_poly[i], 0.1, true); // 원 검출. (approxPolyDP의 인자가 true 이면 원, false면 곡선)
        int w = boundingRect(Mat(contours[i])).width;
        int h = boundingRect(Mat(contours[i])).height;
        double ar = (double)w / h;

        if (hierarchy[i][3] == -1) //No parent
            if (w >= 20 && h >= 20 && ar < 1.1 && ar > 0.9)
                questionCnt.push_back(contours_poly[i]);


    }

    //cout << "\nquestionCnt " << questionCnt.size() << "\n";

    //Step 4: 질문과 답변들을 정렬함.
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
        for (int j = 0; j < NoOfChoice; ++i, ++j)
        {
            Mat mask = Mat::zeros(thresh.size(), CV_8U);
            drawContours(mask, questionCnt, i, 255, CV_FILLED, 8, hierarchy, 0, Point());
            bitwise_and(mask, thresh, mask);
            if (countNonZero(mask) > maxPixel)
            {
                maxPixel = countNonZero(mask); // 행렬 mask에서 0 이 아닌 요소의 개수를 반환함.
                answerKey = j;
            }

        }


        testerAnswer.insert(make_pair(i / NoOfChoice - 1, answerKey));


        if (i / NoOfChoice != 1) // id값 제외
        {
            cout << "Question: " << i / NoOfChoice - 1 << " Tester's Answer: " << answerKey << "\n";
        }
    }


    //Step 6: OMR 정답이 맞는지 체크하는 코드
    map<int, int>::const_iterator itStandardAnswer;
    map<int, int>::const_iterator itTesterAnswer;

    itStandardAnswer = standardAnswer.begin();
    itTesterAnswer = testerAnswer.begin();

    int correct = 0;
    int currentQuestion = 0;
    int id;

    while (itStandardAnswer != standardAnswer.end())
    {
        if (itStandardAnswer == standardAnswer.begin()) //id 값은 파란색으로 표시
        {
            drawContours(paper, questionCnt, (currentQuestion * NoOfChoice) + itTesterAnswer->second, Scalar(255, 0, 0), 2, 8, hierarchy, 0, Point());

            id = itTesterAnswer->second + 1;
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

    //Step 7: 점수 표시하는 코드
    double score = ((double)correct / (NoOfQuestion - 1) * 100); // id값 제외하고 계산

    Scalar color;
    if (score >= 60.0)
        color = Scalar(0, 255, 0);
    else
        color = Scalar(0, 0, 255);

    putText(paper, to_string((int)score) + "%", Point(20, 30), FONT_HERSHEY_SIMPLEX, 0.9, color, 2);

    cout << "학생" << i << "의 성적" << endl;
    cout << "총 문제의 수 : " << currentQuestion << endl;
    cout << "맞은 정답의 수 : " << correct << "\n";
    cout << "점수는 " << score << "점 입니다." << "" << endl;
    cout << endl;
    imshow("Marked Paper", paper);
    waitKey();
    answerAll.insert(make_pair(id, score)); //id값 추가
    i++;

}

    bool cmp(const pair<int, int>&a, const pair<int, int>&b) { //vec 정렬을 위한 함수
        if (a.second == b.second) return a.first < b.first;
        return a.second > b.second;
}



int main()
{

    int n; // 학생의 수 (OMR 카드 수)
    cout << "학생의 수를 입력해주세요 : ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        OMR();
    }


    double sum = 0;
    double average = 0;
    map<int, int>::const_iterator itAnswerAll;
    itAnswerAll = answerAll.begin();

    cout << "===========총합============" << endl;

    while (itAnswerAll != answerAll.end())
    {
        cout << "학생" << itAnswerAll->first << "의 점수는 " << itAnswerAll->second << "점 입니다." << endl;
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
        cout << "학생" << num.first << " " << num.second << "점" << endl;
    }

    return 0;
}