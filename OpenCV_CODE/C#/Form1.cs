// 이미지 상하좌우 대칭
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using OpenCvSharp;

namespace OpenCV_CSharp
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            IplImage ipl = new IplImage("../../ThankYou.jpg", LoadMode.AnyColor);
            pictureBoxIpl1.ImageIpl = ipl;

            OpenCV Convert = new OpenCV();
            pictureBoxIpl2.ImageIpl = Convert.Symmetry(ipl);
        }
        class OpenCV : IDisposable
        {
            IplImage symm;

            public IplImage Symmetry(IplImage src)
            {
                symm = new IplImage(src.Size, BitDepth.U8, 3);
                Cv.Flip(src, symm, FlipMode.Y); // 좌우 대칭
                //Cv.Flip(src, symm, FlipMode.X); // 상하 대칭
                //Cv.Flip(src, symm, FlipMode.XY); // 상하좌우 대칭

                return symm;
            }

            public void Dispose()
            {
                if (symm != null) Cv.ReleaseImage(symm);
            }
        }
    }
}



// 이미지 출력
//using System;
//using System.Collections.Generic;
//using System.ComponentModel;
//using System.Data;
//using System.Drawing;
//using System.Linq;
//using System.Text;
//using System.Threading.Tasks;
//using System.Windows.Forms;
//using OpenCvSharp;

//namespace OpenCV_CSharp
//{
//    public partial class Form1 : Form
//    {
//        public Form1()
//        {
//            InitializeComponent();
//        }

//        private void Form1_Load(object sender, EventArgs e)
//        {
//            using (IplImage ipl = new IplImage("../../ThankYou.jpg", LoadMode.AnyColor))
//            {
//                pictureBoxIpl1.ImageIpl = ipl;
//            }
//        }
//    }
//}
