using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using OpenCvSharp;
using OpenCvSharp.Blob;

namespace KeyboardLabeling
{
    class Program
    {
        static void Main(string[] args)
        {
            Mat src = new Mat("../../keyboard.png");
            Mat bin = new Mat();
            Mat binary = new Mat();

            src = src.SubMat(new Rect(300, 300, 1000, 1000)); // 이미지 자르기

            Cv2.CvtColor(src, bin, ColorConversionCodes.BGR2GRAY); // gray
            Cv2.Threshold(bin, binary, 125, 255, ThresholdTypes.BinaryInv); //이진화

            Mat result = new Mat(src.Size(), MatType.CV_8UC3);
            CvBlobs blobs = new CvBlobs();

            blobs.Label(binary);
            blobs.RenderBlobs(src, result);

            int text = 1; // 번호
            foreach (var item in blobs)
            {
                if (item.Value.Area > 40000) // 라벨링 면적 확인
                {  
                    CvBlob b = item.Value;

                    Cv2.Circle(result, b.Contour.StartingPoint, 8, Scalar.Red, 2, LineTypes.AntiAlias);
                    Cv2.PutText(result, text.ToString(), new Point(b.Centroid.X, b.Centroid.Y),  // 라벨링 번호 설정 수정
                        HersheyFonts.HersheyComplex, 1, Scalar.Yellow, 2, LineTypes.AntiAlias);
                    text++;
                }
            }

            Cv2.ImShow("src", src);
            Cv2.ImShow("binary", binary);
            Cv2.ImShow("result", result);
            Cv2.WaitKey(0);

        }
    }
}

//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using System.Threading.Tasks;
//using OpenCvSharp;
//using OpenCvSharp.Blob;

//namespace KeyboardLabeling
//{
//    class Program
//    {
//        static void Main(string[] args)
//        {
//            Mat src = new Mat("../../keyboard.png");
//            Mat bin = new Mat();
//            Mat binary = new Mat();

//            src = src.SubMat(new Rect(300, 300, 1000, 1000)); // 이미지 자르기

//            Cv2.CvtColor(src, bin, ColorConversionCodes.BGR2GRAY); // gray
//            Cv2.Threshold(bin, binary, 125, 255, ThresholdTypes.BinaryInv); //이진화

//            Mat result = new Mat(src.Size(), MatType.CV_8UC3);
//            CvBlobs blobs = new CvBlobs();

//            blobs.Label(binary);
//            blobs.RenderBlobs(src, result);

//            foreach (var item in blobs)
//            {
//                if (item.Value.Area > 40000)
//                {
//                    CvBlob b = item.Value;

//                    Cv2.Circle(result, b.Contour.StartingPoint, 4, Scalar.Red, 2, LineTypes.AntiAlias);
//                    Cv2.PutText(result, b.Label.ToString(), new Point(b.Centroid.X, b.Centroid.Y),
//                        HersheyFonts.HersheyComplex, 1, Scalar.Yellow, 2, LineTypes.AntiAlias);
//                }
//            }

//            Cv2.ImShow("src", src);
//            Cv2.ImShow("binary", binary);
//            Cv2.ImShow("result", result);
//            Cv2.WaitKey(0);

//        }
//    }
//}

//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using System.Threading.Tasks;
//using OpenCvSharp;
//using OpenCvSharp.Blob;

//namespace KeyboardLabeling
//{
//    class Program
//    {
//        static void Main(string[] args)
//        {
//            Mat src = new Mat("../../keyboard.png");
//            Mat bin = new Mat();
//            Mat binary = new Mat();

//            src = src.SubMat(new Rect(300, 300, 1000, 1000)); // 이미지 자르기

//            Cv2.CvtColor(src, bin, ColorConversionCodes.BGR2GRAY); // gray
//            Cv2.Threshold(bin, binary, 125, 255, ThresholdTypes.BinaryInv); //이진화

//            Mat result = new Mat(src.Size(), MatType.CV_8UC3);
//            CvBlobs blobs = new CvBlobs();
//            blobs.Label(binary);
//            blobs.RenderBlobs(src, result);

//            foreach (var item in blobs)
//            {
//                    CvBlob b = item.Value;

//                    Cv2.Circle(result, b.Contour.StartingPoint, 4, Scalar.Red, 2, LineTypes.AntiAlias);
//                    Cv2.PutText(result, b.Label.ToString(), new Point(b.Centroid.X, b.Centroid.Y),
//                        HersheyFonts.HersheyComplex, 1, Scalar.Yellow, 2, LineTypes.AntiAlias);
//            }

//            Cv2.ImShow("src", src);
//            Cv2.ImShow("binary", binary);
//            Cv2.ImShow("result", result);
//            Cv2.WaitKey(0);

//        }
//    }
//}
