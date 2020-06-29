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
using System.IO;

namespace DAGapp
{
    public partial class Form1 : Form
    {
        private SerialPort sensport;
        private string data;
        //double rt = 0;
        double k = 0;
        int nPoints = 400;
        int trig_freq;
        int num_Signal;
        //Boolean ii = false;
        double ratio = 0.1;

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

            nPoints = int.Parse(xMax.Text);
            chart1.ChartAreas[0].AxisX.Minimum = 0;
            chart1.ChartAreas[0].AxisX.Maximum = nPoints;
            chart1.ChartAreas[0].AxisY.Minimum = int.Parse(yMin.Text);
            chart1.ChartAreas[0].AxisY.Maximum = int.Parse(yMax.Text);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            num_Signal = int.Parse(txtSignal.Text);
            trig_freq = int.Parse(txtTrig.Text);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            //rt = rt + 0.1;


            if ((data == "") || k < 20 || (data == null))
            { k++; }
            else
            {
                //k = 20;
                String[] datalist = data.Split(',');
                int length = datalist.Length;
                if (length < num_Signal)
                { }
                else
                {
                    if (datalist.Any(x => x == "")) // If any element is ""
                    { }
                    else
                    {
                        //this.chart1.Series["Data1"].Points.AddXY(rt, data1);

                        //double data1b = lowpass1.firstOrder_lowpassFilter(double.Parse(data1), ratio);
                        //double data1b = lowpass1.secondOrder_lowpassFilter(double.Parse(data1), ratio);
                        //double data1b = lowpass1.thirdOrder_lowpassFilter(double.Parse(data1), ratio);

                        //kal1D.Update(rt);
                        //kal1D.Predict(double.Parse(data1));
                        //label2.Text = kal1D.State.ToString();

                        //this.chart1.Series["Data1 (Filtered)"].Points.AddXY(rt, data1b);


                        double number;
                        for (int i = 0; i < num_Signal && i < 2; i++)
                        {
                            if (double.TryParse(datalist[i], out number))
                            {
                                if (chart1.Series[i].Points.Count > nPoints - 10)
                                    chart1.Series[i].Points.RemoveAt(0);

                                chart1.Series[i].Points.Add(number);
                            }
                        }
                        chart1.ResetAutoValues();

                        try
                        {
                            using (StreamWriter writer = File.AppendText(txtFile.Text + cbTail.Text))
                            {
                                writer.Write(data);
                            }
                        }
                        catch { }
                    }
                }
            }
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
                    timer1.Start();
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
                //foreach (var series in chart1.Series)
                //{
                //    series.Points.Clear();
                //    rt = 0;
                //}
                timer1.Stop();
            }
        }

        void sensport_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            //k++;

            //if (ii == false)
            //{
            //    rt = 0;
            //    ii = true;
            //}

            data = sensport.ReadLine();
            //listBox1.Items.Add(data);
        }


        private void txtRt_TextChanged(object sender, EventArgs e)
        {
            ratio = double.Parse(txtRt.Text);
        }

        private void btSet_Click(object sender, EventArgs e)
        {
            
            chart1.ChartAreas[0].AxisY.Minimum = int.Parse(yMin.Text);
            chart1.ChartAreas[0].AxisY.Maximum = int.Parse(yMax.Text);

            nPoints = int.Parse(xMax.Text);
            chart1.ChartAreas[0].AxisX.Maximum = nPoints;
        }

        private void btnTrig_Click(object sender, EventArgs e)
        {
            trig_freq = int.Parse(txtTrig.Text);
            timer1.Interval = 1000 / trig_freq;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            num_Signal = int.Parse(txtSignal.Text);
        }
    }
}