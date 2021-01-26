using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ZXing;
using ZXing.Common;


namespace QRcodeApp2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        public string decoded;
        
        private void button1_Click(object sender, EventArgs e)
        {
            pictureBox1.Image = Bitmap.FromFile("../../qrcode.png");
            pictureBox1.SizeMode = PictureBoxSizeMode.Zoom;

            BarcodeReader reader = new BarcodeReader(); 
            Result result = reader.Decode((Bitmap)pictureBox1.Image);
            if (result != null)
            {
                decoded = "Decode : " + result.ToString() + "\r\n Type : " + result.BarcodeFormat.ToString();
                if (decoded != "")
                {
                    textBox1.Text = decoded;
                }
            }
            else 
                MessageBox.Show("바코드나 QR코드를 비추세요!");
        }
    }
}
//using System;
//using System.Collections.Generic;
//using System.ComponentModel;
//using System.Data;
//using System.Drawing;
//using System.IO;
//using System.Linq;
//using System.Text;
//using System.Threading.Tasks;
//using System.Windows.Forms;
//using ZXing;
//using ZXing.Common;


//namespace QRcodeApp2
//{
//    public partial class Form1 : Form
//    {
//        public Form1()
//        {
//            InitializeComponent();
//        }

//        private void button1_Click(object sender, EventArgs e)
//        {
//             Result decode(Uri uri)
//            {
//                Bitmap image;
//                try
//                {
//                    image = (Bitmap)Bitmap.FromFile(@"C: \Users\Administrator\source\study\OpenCV(Csharp)\QRcodeApp2\qrcode2.png");
//                }
//                catch (Exception)
//                {
//                    throw new FileNotFoundException("Resource not found: " + uri);
//                }

//                using (image)
//                {
//                    LuminanceSource source;
//                    source = new BitmapLuminanceSource(image);
//                    BinaryBitmap bitmap = new BinaryBitmap(new HybridBinarizer(source));
//                    Result result = new MultiFormatReader().decode(bitmap);
//                    if (result != null)
//                    {
//                        //... code found
//                    }
//                    else
//                    {
//                        //... no code found
//                    }
//                    return result;
//                }
//            }
//        }
//    }
//}
