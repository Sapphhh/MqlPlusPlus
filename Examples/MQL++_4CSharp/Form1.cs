using MQL;
using SharpMQ_UI;
using System;
using System.Runtime.InteropServices;
using System;
using System.IO;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.TrackBar;

namespace SharpMQ_UI
{
    /*
     This form contains is used to login into your Metatrader account
     */
    public partial class Form1 : Form
    {

        private static string mSymbol = "";

        private const int MINUTE = 60;
        private const int HOUR = 60 * MINUTE;
        private const int DAY = 24 * HOUR;
        private const int WEEK = 7 * DAY;

        private Form2 frm2 = new Form2();

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Methods.InitPyEnv();
            Methods.Init();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (Methods.Login(UInt64.Parse(textBox1.Text), textBox2.Text, "ZeroMarkets-Demo-1", 15000) == true)
            {
                this.Hide();
                frm2.ShowDialog();
            }
        }
    }
}