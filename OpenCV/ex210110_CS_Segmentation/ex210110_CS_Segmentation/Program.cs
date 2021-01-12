using System;
using OpenCvSharp;
using OpenCvSharp.Blob;

namespace Project
{
    class Program
    {
        static void Main(string[] args)
        {

            //세그멘테이션
            //이미지에서 각각의 픽셀들을 분류하여 그룹화하는 것
            Mat src1 = new Mat("../../google.png");
            Mat gray = new Mat();
            Mat binary = new Mat();

            Cv2.CvtColor(src1, gray, ColorConversionCodes.BGR2GRAY);
            Cv2.Threshold(gray, binary, 200, 255, ThresholdTypes.Binary);
            //이진화 함수: Cv2.Threshold
            //Cv2.Threshold(원본 이미지, 결과 이미지, 임곗값, 최댓값, 임곗값 형식)
            //임곗값보다 낮은 픽셀값은 0이나 원본 픽셀값으로 변경,
            //임곗값보다 높은 픽셀값은 최댓값으로 변경

            Cv2.ImShow("src", src1);
            Cv2.ImShow("dst", binary);
            Cv2.WaitKey(0);


            Mat src = new Mat("../../1.png");
            Mat bin = new Mat();

            Cv2.CvtColor(src, bin, ColorConversionCodes.BGR2GRAY);
            //이미지 그레이스케일로 변경
            Cv2.Threshold(bin, bin, 50, 255, ThresholdTypes.Binary);
            //임계값을 초과할 경우 최댓값, 아닐 경우 0

            Cv2.ImShow("src", src);

            Mat result = new Mat(src.Size(), MatType.CV_8UC3);
            //src의 size에 맞춘 8비트 3채널짜리 Mat 클래스 인스턴스 선언
            CvBlobs blobs = new CvBlobs();
            //blob 라벨링에 필요한 요소 선언

            blobs.Label(bin);
            //bin binary 이미지, 원본 이미지 이진화하여 사용
            blobs.RenderBlobs(src, result);
            //결과를 result로
            foreach (var item in blobs)
            {
                CvBlob b = item.Value; Cv2.Circle(result, b.Contour.StartingPoint, 4, Scalar.Red, 2, LineTypes.AntiAlias);
                Cv2.PutText(result, b.Label.ToString(), new Point(b.Centroid.X, b.Centroid.Y),
                    HersheyFonts.HersheyComplex, 1, Scalar.Yellow, 2, LineTypes.AntiAlias);
            }
            Cv2.ImShow("result", result);
            Cv2.WaitKey(0);

        }
    }
}