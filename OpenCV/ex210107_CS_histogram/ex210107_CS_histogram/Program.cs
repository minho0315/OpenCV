using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using OpenCvSharp;

namespace ex210107_CS_histogram
{
    static class Program
    {
        /// <summary>
        /// 해당 애플리케이션의 주 진입점입니다.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Mat src = Cv2.ImRead("../../opencv.png");
            Mat gray = new Mat();
            Mat hist = new Mat();
            Mat result = Mat.Ones(new Size(256, src.Height), MatType.CV_8UC1);
            //넓이 256에 높이가 opencv.png 만큼인 채널 1개의 짜리의 모든 원소가 1인 행렬 반환
            Mat dst = new Mat();

            Cv2.CvtColor(src, gray, ColorConversionCodes.BGR2GRAY); //흑백처리
            //히스토그램 구현
            Cv2.CalcHist(
                new Mat[] { gray }, ///Mat image
                new int[] { 0 }, ////channels : grayscale = 0 / R,G,B = 0,1,2
                null, //mask : all area = null 마스크에 지정한 픽셀만 히스토그램 계산
                hist, //output
                1,  //dims
                new int[] { 256 }, //hist size 채널 개수에 맞게 리스트로 표현 - 1 채널: [256], 2 채널: [256, 256], 3 채널: [256, 256, 256]
                new Rangef[] { new Rangef(0, 256) } //range 각픽셀이 가질 수 있는 값의 범위
                );
           
            //정규화, 특정영역에 몰려있는 경우 화질을 개선하기도 하고 이미지간의 연산 시 서로 조건이 다른 경우 같은 조건으로 만들기도 한다.
            Cv2.Normalize(
                hist, //정규화 이전 데이터 
                hist, //정규화 이후 데이터
                0, //정규화 구간 시작
                255, //정규화 구간 끝
                NormTypes.MinMax //정규화 알고리즘 선택 플래그 상수
                );

            for (int i = 0; i < hist.Rows; i++)
            {
                Cv2.Line(result, new Point(i, src.Height), new Point(i, src.Height - hist.Get<float>(i)), Scalar.White);
            }

            Cv2.ImShow("img", gray);
            Cv2.ImShow("histogram", result);
            Cv2.WaitKey(0);
            Cv2.DestroyAllWindows();


            Mat color = new Mat();
            Mat histB = new Mat();
            Mat histG = new Mat();
            Mat histR = new Mat();
            Mat resultB = Mat.Ones(new Size(256, src.Height), MatType.CV_8UC3);
            Mat resultG = Mat.Ones(new Size(256, src.Height), MatType.CV_8UC3);
            Mat resultR = Mat.Ones(new Size(256, src.Height), MatType.CV_8UC3);

            Cv2.CvtColor(src, color, ColorConversionCodes.BGR2BGRA);

            Cv2.CalcHist(new Mat[] { color }, new int[] { 0 }, null, histB, 1, new int[] { 256 }, new Rangef[] { new Rangef(0, 256) });
            Cv2.Normalize(histB, histB, 0, 255, NormTypes.MinMax);

            Cv2.CalcHist(new Mat[] { color }, new int[] { 1 }, null, histG, 1, new int[] { 256 }, new Rangef[] { new Rangef(0, 256) });
            Cv2.Normalize(histG, histG, 0, 255, NormTypes.MinMax);

            Cv2.CalcHist(new Mat[] { color }, new int[] { 2 }, null, histR, 1, new int[] { 256 }, new Rangef[] { new Rangef(0, 256) });
            Cv2.Normalize(histR, histR, 0, 255, NormTypes.MinMax);

            for (int i = 0; i < histB.Rows; i++)
            {
                Cv2.Line(resultB, new Point(i, src.Height), new Point(i, src.Height - histB.Get<float>(i)), Scalar.Blue);
            }
            for (int i = 0; i < histG.Rows; i++)
            {
                Cv2.Line(resultG, new Point(i, src.Height), new Point(i, src.Height - histG.Get<float>(i)), Scalar.Green);
            }
            for (int i = 0; i < histR.Rows; i++)
            {
                Cv2.Line(resultR, new Point(i, src.Height), new Point(i, src.Height - histR.Get<float>(i)), Scalar.Red);
            }

            Cv2.ImShow("img", color);
            Cv2.ImShow("Blue", resultB);
            Cv2.ImShow("Green", resultG);
            Cv2.ImShow("Red", resultR);
            Cv2.WaitKey(0);
            Cv2.DestroyAllWindows();
        }
    }
}
