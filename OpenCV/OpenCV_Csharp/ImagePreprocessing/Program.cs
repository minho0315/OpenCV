//// 이미지연산
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
//            Mat src1 = new Mat("../../opencv.png", ImreadModes.ReducedColor2);
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

//// 이미지연산
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
//            Mat src = new Mat("../../opencv.png", ImreadModes.ReducedColor2);
//            Mat val = new Mat(src.Size(), MatType.CV_8UC3, new Scalar(0, 0, 30));

//            Mat add = new Mat();
//            Mat sub = new Mat();
//            Mat mul = new Mat();
//            Mat div = new Mat();
//            Mat max = new Mat();
//            Mat min = new Mat();
//            Mat abs = new Mat();
//            Mat absdiff = new Mat();

//            Cv2.Add(src, val, add) ;
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

//// 이진화
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
//            Mat src = new Mat("../../opencv.png");
//            Mat gray = new Mat();
//            Mat binary = new Mat();

//            Cv2.CvtColor(src, gray, ColorConversionCodes.BGR2GRAY);
//            Cv2.Threshold(gray, binary, 150, 255, ThresholdTypes.Binary);

//            Cv2.ImShow("src", src);
//            Cv2.ImShow("dst", binary);
//            Cv2.WaitKey(0);
//        }
//    }
//}


//// 자르기
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
//            Mat src = new Mat("../../opencv.png");
//            Mat dst = src.SubMat(new Rect(100, 100, 100, 100));

//            Cv2.ImShow("src", src);
//            Cv2.ImShow("dst", dst);
//            Cv2.WaitKey(0);
//        }
//    }
//}

//// 이미지 크기 조절
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
//            Mat src = new Mat("../../opencv.png");
//            Mat dst = new Mat();

//            Cv2.Resize(src, dst, new Size(500, 250));

//            Cv2.ImShow("src", src);
//            Cv2.ImShow("dst", dst);
//            Cv2.WaitKey(0);
//        }
//    }
//}

//// 확대축소
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
//            Mat src = new Mat("../../opencv.png", ImreadModes.ReducedColor2);
//            Mat pyrUp = new Mat();
//            Mat pyrDown = new Mat();

//            Cv2.PyrUp(src, pyrUp);
//            Cv2.PyrDown(src, pyrDown);

//            Cv2.ImShow("pyrUp", pyrUp);
//            Cv2.ImShow("pyrDown", pyrDown);
//            Cv2.WaitKey(0);
//        }
//    }
//}


//// 대칭
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
//            Mat src = Cv2.ImRead("../../opencv.png");
//            Mat dst = new Mat(src.Size(), MatType.CV_8UC3);

//            Cv2.Flip(src, dst, FlipMode.Y);

//            Cv2.ImShow("dst", dst);
//            Cv2.WaitKey(0);
//            Cv2.DestroyAllWindows();
//        }
//    }
//}

//// 생삭 공간 변환
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
//            Mat src = Cv2.ImRead("../../opencv.png");
//            Mat dst = new Mat(src.Size(), MatType.CV_8UC1);

//            Cv2.CvtColor(src, dst, ColorConversionCodes.BGR2GRAY);

//            Cv2.ImShow("dst", dst);
//            Cv2.WaitKey(0);
//            Cv2.DestroyAllWindows();
//        }
//    }
//}
