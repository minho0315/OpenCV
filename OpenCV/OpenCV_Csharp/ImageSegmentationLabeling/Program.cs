using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using OpenCvSharp;
using OpenCvSharp.Blob;

namespace ImageSegmentationLabeling
{
    class Program
    {
        static void Main(string[] args)
        {
            Mat src = new Mat("../../sample.png");
            Mat gray = new Mat();
            Mat binary = new Mat();

            Cv2.CvtColor(src, gray, ColorConversionCodes.BGR2GRAY);
            Cv2.Threshold(gray, binary, 150, 255, ThresholdTypes.Binary);

            Cv2.ImShow("src", src);
            Cv2.ImShow("dst", binary);
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
