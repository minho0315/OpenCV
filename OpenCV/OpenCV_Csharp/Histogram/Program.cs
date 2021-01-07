// 히스토그램(color)
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using OpenCvSharp;

namespace Histogram
{
    class Program
    {
        static void Main(string[] args)
        {
            Mat src = Cv2.ImRead("../../opencv.png");
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

//// 히스토그램(gray)
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
//            Mat src = Cv2.ImRead("../../opencv.png");
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
