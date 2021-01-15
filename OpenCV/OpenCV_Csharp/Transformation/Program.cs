//원근 변환
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using OpenCvSharp;

namespace Transformation
{
    class Program
    {
        static void Main(string[] args)
        {
            Mat src = Cv2.ImRead("../../opencv.png");
            Mat dst = new Mat();

            List<Point2f> src_pts = new List<Point2f>()
            {
                new Point2f(0.0f, 0.0f),
                new Point2f(0.0f, src.Height),
                new Point2f(src.Width, src.Height),
                new Point2f(src.Width, 0.0f)
            };

            List<Point2f> dst_pts = new List<Point2f>()
            {
               new Point2f(50.0f, 50.0f),
               new Point2f(0.0f, src.Height),
               new Point2f(src.Width, src.Height),
               new Point2f(src.Width - 100.0f, 0.0f)
            };

            Mat matrix = Cv2.GetPerspectiveTransform(src_pts, dst_pts);
            Cv2.WarpPerspective(src, dst, matrix, new Size(src.Width, src.Height));

            Cv2.ImShow("src", src);
            Cv2.ImShow("dst", dst);
            Cv2.WaitKey(0);
        }
    }
}

//// 아핀 변환(수평성 유지)
//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using System.Threading.Tasks;
//using OpenCvSharp;

//namespace Transformation
//{
//    class Program
//    {
//        static void Main(string[] args)
//        {
//            Mat src = Cv2.ImRead("../../opencv.png");
//            Mat dst = new Mat();

//            List<Point2f> src_pts = new List<Point2f>()
//            {
//                new Point2f(0.0f, 0.0f), 
//                new Point2f(0.0f, src.Height),
//                new Point2f(src.Width, src.Height)
//            };

//            List<Point2f> dst_pts = new List<Point2f>()
//            {
//               new Point2f(50.0f, 50.0f),
//               new Point2f(0.0f, src.Height - 100.0f),
//               new Point2f(src.Width - 50.0f, src.Height - 50.0f)
//            };

//            Mat matrix = Cv2.GetAffineTransform(src_pts, dst_pts);
//            Cv2.WarpAffine(src, dst, matrix, new Size(src.Width, src.Height));

//            Cv2.ImShow("src", src);
//            Cv2.ImShow("dst", dst);
//            Cv2.WaitKey(0);
//        }
//    }
//}

//// 이미지 회전
//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using System.Threading.Tasks;
//using OpenCvSharp;

//namespace Transformation
//{
//    class Program
//    {
//        static void Main(string[] args)
//        {
//            Mat src = Cv2.ImRead("../../opencv.png");
//            Mat dst = new Mat();
//            Mat dst2 = new Mat();
//            Mat dst3 = new Mat();

//            Mat matrix = Cv2.GetRotationMatrix2D(new Point2f(src.Width / 2, src.Height / 2), 90.0, 1.0);
//            Mat matrix2 = Cv2.GetRotationMatrix2D(new Point2f(src.Width / 2, src.Height / 2), 180.0, 1.0);
//            Mat matrix3 = Cv2.GetRotationMatrix2D(new Point2f(src.Width / 2, src.Height / 2), 100.0, 1.0);

//            Cv2.WarpAffine(src, dst, matrix, new Size(src.Width, src.Height)); // 아핀변환 함수를 적용
//            Cv2.WarpAffine(src, dst2, matrix2, new Size(src.Width, src.Height));
//            Cv2.WarpAffine(src, dst3, matrix3, new Size(src.Width, src.Height));

//            Cv2.ImShow("src", src);
//            Cv2.ImShow("dst", dst);
//            Cv2.ImShow("dst2", dst2);
//            Cv2.ImShow("dst3", dst3);

//            Cv2.WaitKey(0);
//            Cv2.DestroyAllWindows();
//        }
//    }
//}

//// 이미지 대칭
//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using System.Threading.Tasks;
//using OpenCvSharp;

//namespace Transformation
//{
//    class Program
//    {
//        static void Main(string[] args)
//        {
//            Mat src = Cv2.ImRead("../../opencv.png");
//            Mat dst = new Mat(src.Size(), MatType.CV_8UC3);
//            Mat dst2 = new Mat(src.Size(), MatType.CV_8UC3);
//            Mat dst3 = new Mat(src.Size(), MatType.CV_8UC3);

//            Cv2.Flip(src, dst, FlipMode.Y); // Y축대칭
//            Cv2.Flip(src, dst2, FlipMode.X); // X축대칭
//            Cv2.Flip(src, dst3, FlipMode.XY); // XY축대칭

//            Cv2.ImShow("src", src);
//            Cv2.ImShow("dst", dst);
//            Cv2.ImShow("dst2", dst2);
//            Cv2.ImShow("dst3", dst3);
//            Cv2.WaitKey(0);
//            Cv2.DestroyAllWindows();
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

//namespace Transformation
//{
//    class Program
//    {
//        static void Main(string[] args)
//        {
//            Mat src = Cv2.ImRead("../../opencv.png");
//            Mat dst = new Mat();
//            Mat dst2 = new Mat();

//            Cv2.Resize(src, dst, new Size(500, 250)); // 절대적 크기
//            Cv2.Resize(src, dst2, new Size(0, 0), 0.5, 0.5); // 상대적 크기

//            Cv2.ImShow("src", src);
//            Cv2.ImShow("dst", dst);
//            Cv2.ImShow("dst2", dst2);
//            Cv2.WaitKey(0);
//        }
//    }
//}

//// 이미지 확대 축소
//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using System.Threading.Tasks;
//using OpenCvSharp;

//namespace Transformation
//{
//    class Program
//    {
//        static void Main(string[] args)
//        {
//            Mat src = Cv2.ImRead("../../opencv.png");
//            Mat dst = new Mat(src.Size(), MatType.CV_8UC3);
//            Mat dst2 = new Mat(src.Size(), MatType.CV_8UC3);

//            // Cv2.PyrUp(src, dst, new Size(src.Width * 2 + 1, src.Height * 2 - 1));
//            Cv2.PyrUp(src, dst);
//            Cv2.PyrDown(src, dst2); //4배 축소
//            Cv2.PyrDown(dst2, dst2); //16배 축소

//            Cv2.ImShow("src", src);
//            Cv2.ImShow("dst", dst);
//            Cv2.ImShow("dst2", dst2);

//            Cv2.WaitKey(0);
//            Cv2.DestroyAllWindows();
//        }
//    }
//}

