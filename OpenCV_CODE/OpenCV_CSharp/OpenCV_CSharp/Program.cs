//// 세그멘테이션, 라벨링 코드 - 2021/1/11
//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using System.Threading.Tasks;
//using OpenCvSharp;
//using OpenCvSharp.Blob;

//namespace ImageSegmentationLabeling
//{
//    class Program
//    {
//        static void Main(string[] args)
//        {
//            Mat src = new Mat("../../sample.png");
//            Mat bin = new Mat();

//            Cv2.CvtColor(src, bin, ColorConversionCodes.BGR2GRAY);
//            Cv2.Threshold(bin, bin, 0, 255, ThresholdTypes.Binary);

//            Cv2.ImShow("src", src);

//            Mat result = new Mat(src.Size(), MatType.CV_8UC3);
//            CvBlobs blobs = new CvBlobs();
//            blobs.Label(bin);
//            blobs.RenderBlobs(src, result);
//            foreach (var item in blobs)
//            {
//                CvBlob b = item.Value; Cv2.Circle(result, b.Contour.StartingPoint, 4, Scalar.Red, 2, LineTypes.AntiAlias);
//                Cv2.PutText(result, b.Label.ToString(), new Point(b.Centroid.X, b.Centroid.Y),
//                    HersheyFonts.HersheyComplex, 1, Scalar.Yellow, 2, LineTypes.AntiAlias);
//            }
//            Cv2.ImShow("result", result); Cv2.WaitKey(0);

//        }
//    }
//}


//// 컬러이미지 히스토그램 출력 - 2021/1/7
//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using System.Threading.Tasks;
//using OpenCvSharp;

//namespace Histogram
//{
//    class Program
//    {
//        static void Main(string[] args)
//        {
//            Mat src = Cv2.ImRead("../../Lenna.png");
//            Mat color = new Mat();
//            Mat histB = new Mat();
//            Mat histG = new Mat();
//            Mat histR = new Mat();
//            Mat resultB = Mat.Ones(new Size(256, src.Height), MatType.CV_8UC3);
//            Mat resultG = Mat.Ones(new Size(256, src.Height), MatType.CV_8UC3);
//            Mat resultR = Mat.Ones(new Size(256, src.Height), MatType.CV_8UC3);

//            Cv2.CvtColor(src, color, ColorConversionCodes.BGR2BGRA);

//            Cv2.CalcHist(new Mat[] { color }, new int[] { 0 }, null, histB, 1, new int[] { 256 }, new Rangef[] { new Rangef(0, 256) });
//            Cv2.Normalize(histB, histB, 0, 255, NormTypes.MinMax);

//            Cv2.CalcHist(new Mat[] { color }, new int[] { 1 }, null, histG, 1, new int[] { 256 }, new Rangef[] { new Rangef(0, 256) });
//            Cv2.Normalize(histG, histG, 0, 255, NormTypes.MinMax);

//            Cv2.CalcHist(new Mat[] { color }, new int[] { 2 }, null, histR, 1, new int[] { 256 }, new Rangef[] { new Rangef(0, 256) });
//            Cv2.Normalize(histR, histR, 0, 255, NormTypes.MinMax);

//            for (int i = 0; i < histB.Rows; i++)
//            {
//                Cv2.Line(resultB, new Point(i, src.Height), new Point(i, src.Height - histB.Get<float>(i)), Scalar.Blue);
//            }
//            for (int i = 0; i < histG.Rows; i++)
//            {
//                Cv2.Line(resultG, new Point(i, src.Height), new Point(i, src.Height - histG.Get<float>(i)), Scalar.Green);
//            }
//            for (int i = 0; i < histR.Rows; i++)
//            {
//                Cv2.Line(resultR, new Point(i, src.Height), new Point(i, src.Height - histR.Get<float>(i)), Scalar.Red);
//            }

//            Cv2.ImShow("img", color);
//            Cv2.ImShow("Blue", resultB);
//            Cv2.ImShow("Green", resultG);
//            Cv2.ImShow("Red", resultR);
//            Cv2.WaitKey(0);
//            Cv2.DestroyAllWindows();
//        }
//    }
//}

//// 흑백이미지 히스토그램 출력 - 2021/1/7
//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using System.Threading.Tasks;
//using OpenCvSharp;

//namespace Histogram
//{
//    class Program
//    {
//        static void Main(string[] args)
//        {
//            Mat src = Cv2.ImRead("../../Lenna.png");
//            Mat gray = new Mat();
//            Mat hist = new Mat();
//            Mat result = Mat.Ones(new Size(256, src.Height), MatType.CV_8UC1);
//            Mat dst = new Mat();

//            Cv2.CvtColor(src, gray, ColorConversionCodes.BGR2GRAY);
//            Cv2.CalcHist(new Mat[] { gray }, new int[] { 0 }, null, hist, 1, new int[] { 256 }, new Rangef[] { new Rangef(0, 256) });
//            Cv2.Normalize(hist, hist, 0, 255, NormTypes.MinMax);

//            for (int i = 0; i < hist.Rows; i++)
//            {
//                Cv2.Line(result, new Point(i, src.Height), new Point(i, src.Height - hist.Get<float>(i)), Scalar.White);
//            }

//            Cv2.ImShow("img", gray);
//            Cv2.ImShow("histogram", result);
//            Cv2.WaitKey(0);
//            Cv2.DestroyAllWindows();
//        }
//    }
//}

//// 이미지 연산2 - 2021/1/4
//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using System.Threading.Tasks;
//using OpenCvSharp;

//namespace ImagePreprocessing
//{
//    class Program
//    {
//        static void Main(string[] args)
//        {
//            Mat src1 = new Mat("../../ThankYou.jpg", ImreadModes.ReducedColor2);
//            Mat src2 = src1.Flip(FlipMode.Y);

//            Mat and = new Mat();
//            Mat or = new Mat();
//            Mat xor = new Mat();
//            Mat not = new Mat();
//            Mat compare = new Mat();

//            Cv2.BitwiseAnd(src1, src2, and);
//            Cv2.BitwiseOr(src1, src2, or);
//            Cv2.BitwiseXor(src1, src2, xor);
//            Cv2.BitwiseNot(src1, not);
//            Cv2.Compare(src1, src2, compare, CmpTypes.EQ);

//            Cv2.ImShow("and", and);
//            Cv2.ImShow("or", or);
//            Cv2.ImShow("xor", xor);
//            Cv2.ImShow("not", not);
//            Cv2.ImShow("compare", compare);
//            Cv2.WaitKey(0);
//        }
//    }
//}

//// 이미지 연산 - 2021/1/4
//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using System.Threading.Tasks;
//using OpenCvSharp;

//namespace ImagePreprocessing
//{
//    class Program
//    {
//        static void Main(string[] args)
//        {
//            Mat src = new Mat("../../ThankYou.jpg", ImreadModes.ReducedColor2);
//            Mat val = new Mat(src.Size(), MatType.CV_8UC3, new Scalar(0, 0, 30));

//            Mat add = new Mat();
//            Mat sub = new Mat();
//            Mat mul = new Mat();
//            Mat div = new Mat();
//            Mat max = new Mat();
//            Mat min = new Mat();
//            Mat abs = new Mat();
//            Mat absdiff = new Mat();

//            Cv2.Add(src, val, add);
//            Cv2.Subtract(src, val, sub);
//            Cv2.Multiply(src, val, mul);
//            Cv2.Divide(src, val, div);
//            Cv2.Max(src, mul, max);
//            Cv2.Min(src, mul, min);
//            abs = Cv2.Abs(mul);
//            Cv2.Absdiff(src, mul, absdiff);

//            Cv2.ImShow("add", add);
//            Cv2.ImShow("sub", sub);
//            Cv2.ImShow("mul", mul);
//            Cv2.ImShow("div", div);
//            Cv2.ImShow("max", max);
//            Cv2.ImShow("min", min);
//            Cv2.ImShow("abs", abs);
//            Cv2.ImShow("absdiff", absdiff);
//            Cv2.WaitKey(0);
//        }
//    }
//}

//// 이진화 - 2021/1/3
//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using System.Threading.Tasks;
//using OpenCvSharp;

//namespace ImagePreprocessing
//{
//    class Program
//    {
//        static void Main(string[] args)
//        {
//            Mat src = new Mat("../../ThankYou.jpg");
//            Mat gray = new Mat();
//            Mat binary = new Mat();

//            Cv2.CvtColor(src, gray, ColorConversionCodes.BGR2GRAY);
//            Cv2.Threshold(gray, binary, 150, 255, ThresholdTypes.Binary);
//            // Cv2.Threshold(원본 이미지, 결과 이미지, 임곗값, 최댓값, 임곗값 형식)로 이진화
//            // 임곗값 보다 낮은 픽셀값은 0이나 원본 픽셀값으로 변경하며, 임곗값보다 높은 픽셀값은 최댓값으로 변경

//            Cv2.ImShow("src", src);
//            Cv2.ImShow("dst", binary);
//            Cv2.WaitKey(0);
//        }
//    }
//}

//// 이미지 자르기 - 2021/1/3
//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using System.Threading.Tasks;
//using OpenCvSharp;

//namespace ImagePreprocessing
//{
//    class Program
//    {
//        static void Main(string[] args)
//        {
//            Mat src = new Mat("../../ThankYou.jpg");
//            Mat dst = src.SubMat(new Rect(100, 100, 100, 100));
//            // *.SubMat()는 Range구조체, Rect구조체, int할당 등을 통해 생성
//            // 이 예제에선 int 형식활용
//            Cv2.ImShow("src", src);
//            Cv2.ImShow("dst", dst);
//            Cv2.WaitKey(0);
//        }
//    }
//}

//// 이미지 크기 조절 - 2021/1/1
//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using System.Threading.Tasks;
//using OpenCvSharp;

//namespace ImagePreprocessing
//{
//    class Program
//    {
//        static void Main(string[] args)
//        {
//            Mat src = new Mat("../../ThankYou.jpg");
//            Mat dst = new Mat();

//            Cv2.Resize(src, dst, new Size(500, 250));
//            // Cv2.Resize(원본 이미지, 결과 이미지, 절대 크기, 상대 크기(X), 상대 크기(Y), 보간법)

//            Cv2.ImShow("src", src);
//            Cv2.ImShow("dst", dst);
//            Cv2.WaitKey(0);
//        }
//    }
//}

//// 이미지 크기 설정(확대, 축소) - 2021/1/1
//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using System.Threading.Tasks;
//using OpenCvSharp;

//namespace ImagePreprocessing
//{
//    class Program
//    {
//        static void Main(string[] args)
//        {
//            Mat src = new Mat("../../ThankYou.jpg", ImreadModes.ReducedColor2);
//            Mat pyrUp = new Mat();
//            Mat pyrDown = new Mat();

//            Cv2.PyrUp(src, pyrUp);
//            Cv2.PyrDown(src, pyrDown);
//            // Cv2.Pyr*(원본 이미지, 결과 이미지, 결과 이미지 크기, 테두리 외삽법)

//            Cv2.ImShow("src", src);
//            Cv2.ImShow("pyrUp", pyrUp);
//            Cv2.ImShow("pyrDown", pyrDown);
//            Cv2.WaitKey(0);
//        }
//    }
//}

//// 이미지 대칭 - 2021/1/1
//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using System.Threading.Tasks;
//using OpenCvSharp;

//namespace ImagePreprocessing
//{
//    class Program
//    {
//        static void Main(string[] args)
//        {
//            Mat src = Cv2.ImRead("../../ThankYou.jpg");
//            Mat dst_X = new Mat(src.Size(), MatType.CV_8UC3);
//            Mat dst_Y = new Mat(src.Size(), MatType.CV_8UC3);
//            Mat dst_XY = new Mat(src.Size(), MatType.CV_8UC3);

//            Cv2.Flip(src, dst_X, FlipMode.X);
//            Cv2.Flip(src, dst_Y, FlipMode.Y);
//            Cv2.Flip(src, dst_XY, FlipMode.XY);

//            // Cv2.Flip(원본 이미지, 결과 이미지, 대칭 축)
//            Cv2.ImShow("src", src);
//            Cv2.ImShow("dst_X", dst_X);
//            Cv2.ImShow("dst_Y", dst_Y);
//            Cv2.ImShow("dst_XY", dst_XY);
//            Cv2.WaitKey(0);
//            Cv2.DestroyAllWindows();
//        }
//    }
//}


//// 색상공간 변환 - 2020/12/30
//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using System.Threading.Tasks;
//using OpenCvSharp;
//namespace OpenCV_CSharp
//{
//    class Program
//    {
//        static void Main(string[] args)
//        {
//            Mat src = Cv2.ImRead("../../ThankYou.jpg");
//            Mat dst = new Mat(src.Size(), MatType.CV_8UC1);

//            Cv2.CvtColor(src, dst, ColorConversionCodes.BGR2GRAY);
//            // CV2. CVtColor (원본이미지, 결과 이미지, 색상 변환 코드)

//            Cv2.ImShow("dst", dst);
//            Cv2.WaitKey(0);
//            Cv2.DestroyAllWindows();
//        }
//    }
//}


//// 이미지 출력, 흑백 이미지 출력 - 2020/12/30
//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using System.Threading.Tasks;
//using OpenCvSharp;
//namespace OpenCV_CSharp
//{
//    class Program
//    {
//        static void Main(string[] args)
//        {
//            Mat image = Cv2.ImRead("../../ThankYou.jpg");
//            Mat image2 = Cv2.ImRead("../../ThankYou.jpg", ImreadModes.Grayscale);
//            Cv2.ImShow("image", image);
//            Cv2.ImShow("image_GRAY", image2);
//            Cv2.WaitKey(0);
//            Cv2.DestroyAllWindows();
//        }
//    }
//}