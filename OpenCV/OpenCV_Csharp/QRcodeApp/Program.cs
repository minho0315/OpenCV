using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;
using OpenCvSharp;
using OpenCvSharp.Blob;
using ZXing;

namespace QRcodeApp
{
    class Program
    {
        static void Main(string[] args)
        {
            Mat src = Cv2.ImRead("../../qrcode2.png");

            // create a barcode reader instance
            var barcodeReader = new BarcodeReader();

            // create an in memory bitmap
            var barcodeBitmap = (Bitmap)Bitmap.FromFile("../../qrcode2.png");

            // decode the barcode from the in memory bitmap
            var barcodeResult = barcodeReader.Decode(barcodeBitmap);

            // output results to consoles
            Console.WriteLine($"Decoded barcode text: {barcodeResult?.Text}");
            Console.WriteLine($"Barcode format: {barcodeResult?.BarcodeFormat}");


            Cv2.ImShow("src", src);

            Cv2.WaitKey(0);
            Cv2.DestroyAllWindows();

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

//namespace QRcodeApp
//{
//    class Program
//    {
//        static void Main(string[] args)
//        {
//            Mat src = Cv2.ImRead("../../qr1.jpg");

//            QRCodeDetector qRCodeDetector = null;
//            String info = qRCodeDetector.DetectAndDecode(src, out Point2f[] points);

//            IEnumerable<IEnumerable<Point>> pts = (IEnumerable<IEnumerable<Point>>)points;

//            Cv2.Polylines(src, points, true, new Scalar(0, 0, 255), 2);

//            Cv2.ImShow("src", src);

//            Cv2.WaitKey(0);
//            Cv2.DestroyAllWindows();

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

//namespace QRcodeApp
//{
//    class Program
//    {
//        static void Main(string[] args)
//        {
//            Mat src = new Mat("../../qr1.jpg");
//            Mat yellow = new Mat();
//            Mat dst = src.Clone();

//            Point[][] contours;
//            HierarchyIndex[] hierarchy;

//            Cv2.InRange(src, new Scalar(150,150,150), new Scalar(200, 200, 200), yellow);
//            Cv2.FindContours(yellow, out contours, out hierarchy, RetrievalModes.Tree, ContourApproximationModes.ApproxTC89KCOS);

//            List<Point[]> new_contours = new List<Point[]>();
//            foreach (Point[] p in contours)
//            {
//                double length = Cv2.ArcLength(p, true);
//                if (length < 100) continue;

//                new_contours.Add(Cv2.ApproxPolyDP(p, length * 0.02, true));
//            }

//            Cv2.DrawContours(dst, new_contours, -1, new Scalar(255, 0, 0), 2, LineTypes.AntiAlias, null, 1);
//            Cv2.ImShow("dst", dst);
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

//namespace QRcodeApp
//{
//    class Program
//    {
//        static void Main(string[] args)
//        {
//            Mat src = Cv2.ImRead("../../qr1.jpg");
//            OpenCvSharp.Point[] squares = Square(src);
//            Mat square = DrawSquare(src, squares);

//            Cv2.ImShow("square", square);
//            Cv2.WaitKey(0);
//            Cv2.DestroyAllWindows();
//        }

//        static double Angle(OpenCvSharp.Point pt1, OpenCvSharp.Point pt0, OpenCvSharp.Point pt2)
//        {
//            double u1 = pt1.X - pt0.X;
//            double u2 = pt1.Y - pt0.Y;
//            double v1 = pt2.X - pt0.X;
//            double v2 = pt2.Y - pt0.Y;

//            return (u1 * v1 + u2 * v2) / (Math.Sqrt(u1 * u1 + u2 * u2) * Math.Sqrt(v1 * v1 + v2 * v2));
//        }

//        public static OpenCvSharp.Point[] Square(Mat src)
//        {
//            Mat[] split = Cv2.Split(src);
//            Mat blur = new Mat();
//            Mat binary = new Mat();
//            OpenCvSharp.Point[] squares = new OpenCvSharp.Point[4];

//            int N = 10;
//            double max = src.Size().Width * src.Size().Height * 0.9;
//            double min = src.Size().Width * src.Size().Height * 0.1;

//            for (int channel = 0; channel < 3; channel++)
//            {
//                Cv2.GaussianBlur(split[channel], blur, new OpenCvSharp.Size(5, 5), 1);
//                for (int i = 0; i < N; i++)
//                {
//                    Cv2.Threshold(blur, binary, i * 255 / N, 255, ThresholdTypes.Binary);

//                    OpenCvSharp.Point[][] contours;
//                    HierarchyIndex[] hierarchy;
//                    Cv2.FindContours(binary, out contours, out hierarchy, RetrievalModes.List, ContourApproximationModes.ApproxTC89KCOS);

//                    for (int j = 0; j < contours.Length; j++)
//                    {
//                        double perimeter = Cv2.ArcLength(contours[j], true);
//                        OpenCvSharp.Point[] result = Cv2.ApproxPolyDP(contours[j], perimeter * 0.02, true);

//                        double area = Cv2.ContourArea(result);
//                        bool convex = Cv2.IsContourConvex(result);

//                        if (result.Length == 4 && area > min && area < max && convex)
//                        {
//                            double cos = 0;
//                            for (int k = 1; k < 5; k++)
//                            {
//                                double t = Math.Abs(Angle(result[(k - 1) % 4], result[k % 4], result[(k + 1) % 4]));
//                                cos = cos > t ? cos : t;
//                            }
//                            if (cos < 0.15) squares = result;
//                        }
//                    }
//                }
//            }
//            return squares;
//        }

//        public static Mat DrawSquare(Mat src, OpenCvSharp.Point[] squares)
//        {
//            Mat drawsquare = src.Clone();
//            OpenCvSharp.Point[][] pts = new OpenCvSharp.Point[][] { squares };
//            Cv2.Polylines(drawsquare, pts, true, Scalar.Yellow, 3, LineTypes.AntiAlias, 0);
//            return drawsquare;
//        }

//        public static Mat PerspectiveTransform(Mat src, OpenCvSharp.Point[] squares)
//        {
//            Mat dst = new Mat();
//            Moments moments = Cv2.Moments(squares);
//            double cX = moments.M10 / moments.M00;
//            double cY = moments.M01 / moments.M00;

//            Point2f[] src_pts = new Point2f[4];
//            for (int i = 0; i < squares.Length; i++)
//            {
//                if (cX > squares[i].X && cY > squares[i].Y) src_pts[0] = squares[i];
//                if (cX > squares[i].X && cY < squares[i].Y) src_pts[1] = squares[i];
//                if (cX < squares[i].X && cY > squares[i].Y) src_pts[2] = squares[i];
//                if (cX < squares[i].X && cY < squares[i].Y) src_pts[3] = squares[i];
//            }

//            Point2f[] dst_pts = new Point2f[4]
//            {
//                new Point2f(0, 0),
//                new Point2f(0, src.Height),
//                new Point2f(src.Width, 0),
//                new Point2f(src.Width, src.Height)
//            };

//            Mat matrix = Cv2.GetPerspectiveTransform(src_pts, dst_pts);
//            Cv2.WarpPerspective(src, dst, matrix, new OpenCvSharp.Size(src.Width, src.Height));
//            return dst;
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

//namespace QRcodeApp
//{

//    class Program
//    {
//        static void Main(string[] args)
//        {
//            Mat src = Cv2.ImRead("../../qr2.jpg");
//            Mat gray = new Mat();
//            Mat binary = new Mat();
//            Mat result = new Mat(src.Size(), MatType.CV_8UC3);
//            Cv2.CvtColor(src, gray, ColorConversionCodes.BGR2GRAY);
//            Cv2.Threshold(gray, binary, 170, 255, ThresholdTypes.Binary);

//            CvBlobs blobs = new CvBlobs();

//            blobs.Label(binary);
//            blobs.RenderBlobs(binary, result);

//            //Cv2.ImShow("src", src);
//            //Cv2.ImShow("gray", gray);
//            //Cv2.ImShow("binary", binary);
//            Cv2.ImShow("result", result);

//            Cv2.WaitKey(0);
//            Cv2.DestroyAllWindows();

//            QRCodeDetector qRCodeDetector = null;

//            Point2f[] points = null;
//            string info = qRCodeDetector.DetectAndDecode(src, out points);

//            //Cv2.Polylines(src, points, true, new Scalar(0, 0, 255), 2);
//            Cv2.PutText(src, info, new Point(10, 30), HersheyFonts.HersheyComplex , 1,
//                    new Scalar(0, 0, 255));

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

//namespace QRcodeApp
//{
//    class Program
//    {
//        static void Main(string[] args)
//        {
//            Mat src = Cv2.ImRead("../../qr2.jpg");
//            Mat gray = new Mat();
//            Mat binary = new Mat();
//            Mat result = new Mat(src.Size(), MatType.CV_8UC3);
//            Cv2.CvtColor(src, gray, ColorConversionCodes.BGR2GRAY);
//            Cv2.Threshold(gray, binary, 170, 255, ThresholdTypes.Binary);

//            CvBlobs blobs = new CvBlobs();

//            blobs.Label(binary);
//            blobs.RenderBlobs(binary, result);

//            //Cv2.ImShow("src", src);
//            //Cv2.ImShow("gray", gray);
//            //Cv2.ImShow("binary", binary);
//            Cv2.ImShow("result", result);

//            Cv2.WaitKey(0);
//            Cv2.DestroyAllWindows();

//        }
//    }
//}
