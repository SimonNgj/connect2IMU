using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace DAGapp
{
    public partial class Form1 : Form
    {
        private SerialPort sensport;
        private string data;
        double rt = 0;  
        double k = 0;
        Boolean i = false;
        double ratio = 0.5;

        // For Kalman filter
        //double measurement_sigma = 1.0;
        //double motion_sigma = 1.0;
        //double mu = 0;
        //double sigma = 1;

        LowpassFilter lowpass1 = new LowpassFilter();
        //KalmanFilters.KalmanFilter1D kal1D;

        public Form1()
        {
            InitializeComponent();
            Control.CheckForIllegalCrossThreadCalls = false;
            //kal1D = new KalmanFilters.KalmanFilter1D(mu, sigma, measurement_sigma, motion_sigma);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            timer1.Start();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            rt = rt + 0.1;
        }

        private void BtnConnect_Click(object sender, EventArgs e)
        {
            if (BtnConnect.Text == "Connect")
            {
                BtnConnect.Text = "Close";

                sensport = new SerialPort();
                sensport.PortName = txtCom.Text;
                sensport.BaudRate = int.Parse(txtBaud.Text);
                sensport.Parity = Parity.None;
                sensport.DataBits = 8;
                sensport.StopBits = StopBits.One;
                sensport.Handshake = Handshake.None;
                sensport.DataReceived += sensport_DataReceived;

                try
                {
                    sensport.Open();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message, "Error");
                }
            }
            else
            {
                BtnConnect.Text = "Connect";
                sensport.Close();
            }
        }

        void sensport_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            k++;

            if (i == false)
            {
                rt = 0;
                i = true;
            }

            data = sensport.ReadLine();
            listBox1.Items.Add(data);

            if ((data == "") || k < 5)
            { }
            else
            {
                String[] datalist = data.Split(',');
                int length = datalist.Length;
                if (length != 2)
                { }
                else
                {
                    string data1 = datalist[0];
                    //string data2 = datalist[1];
                    this.chart1.Series["Data1"].Points.AddXY(rt, data1);
                    
                   //double data1b = lowpass1.firstOrder_lowpassFilter(double.Parse(data1), ratio);
                   double data1b = lowpass1.secondOrder_lowpassFilter(double.Parse(data1), ratio);
                   //double data1b = lowpass1.thirdOrder_lowpassFilter(double.Parse(data1), ratio);

                    //kal1D.Update(rt);
                    //kal1D.Predict(double.Parse(data1));
                    //label2.Text = kal1D.State.ToString();

                    this.chart1.Series["Data1 (Filtered)"].Points.AddXY(rt, data1b);
                }
            }
        }
    }
}
