using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using OpenCvSharp;

namespace ex210106_CS_OpenCV
{
    static class Program
    {
        /// <summary>
        /// 해당 애플리케이션의 주 진입점입니다.
        /// </summary>
        [STAThread]
        static void Main()
        {
            //Console.WriteLine(Cv2.GetVersionString());
            ////Application.EnableVisualStyles();
            ////Application.SetCompatibleTextRenderingDefault(false);
            ////Application.Run(new Form1());

            ///
            /*이미지 불러오기*/
            Mat src = Cv2.ImRead("../../opencv.png");
            Cv2.ImShow("image", src);
            Cv2.WaitKey(0);
            Cv2.DestroyAllWindows();


            
            Mat dst = new Mat(src.Size(), MatType.CV_8UC1);


            /*색상공간 변화*/
            //데이터 타입을 같게 유지하고 채널을 변환
            Cv2.CvtColor(src, dst, ColorConversionCodes.BGR2GRAY);
            //Cv2.CvtColor(원본 이미지, 결과 이미지, 색상 변환 코드)로 색상 공간을 변환
            //색상 변환 코드(code)를 사용해 BGR 색상 공간을 RGBA 색상 공간으로 변환하거나 
            //그레이스케일, HSV, CIE Luv 등으로 변환이 가능
            //그레이스케일 변환은 다중 채널에서 단일 채널로 변화하기 때문에 dst의 채널수가 1이어야함

            Cv2.ImShow("색상공간변화- 그레이스케일", dst);
            Cv2.WaitKey(0);
            Cv2.DestroyAllWindows();


            /*대칭*/
            //변환할 행렬(이미지)에 대해 2*2 행렬을 왼쪽 곱셈함
            Cv2.Flip(src, dst, FlipMode.Y);
            //Cv2.Flip(원본 이미지, 결과 이미지, 대칭 축)로 색상 공간을 변환
            //대칭 축(FlipMode)를 사용해 X 축, Y 축, XY 축 대칭을 진행
            //FlipMode.X X축 대칭(상하 대칭)
            //FlipMode.Y Y축 대칭(좌우 대칭)
            //FlipMode.XY XY축 대칭(상하좌우 대칭)
            Cv2.ImShow("좌우 대칭", dst);
            Cv2.WaitKey(0);
            Cv2.DestroyAllWindows();

        }
    }
}
