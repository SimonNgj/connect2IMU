namespace DAGapp
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea2 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend2 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series3 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series4 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.chart1 = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.BtnConnect = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.txtCom = new System.Windows.Forms.TextBox();
            this.lbCOM = new System.Windows.Forms.Label();
            this.txtBaud = new System.Windows.Forms.TextBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.txtRt = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.txtFile = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.yMax = new System.Windows.Forms.TextBox();
            this.yMin = new System.Windows.Forms.TextBox();
            this.cbTail = new System.Windows.Forms.ComboBox();
            this.btSet = new System.Windows.Forms.Button();
            this.xMax = new System.Windows.Forms.TextBox();
            this.txtTrig = new System.Windows.Forms.TextBox();
            this.btnTrig = new System.Windows.Forms.Button();
            this.txtSignal = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).BeginInit();
            this.SuspendLayout();
            // 
            // chart1
            // 
            chartArea2.AxisX.Enabled = System.Windows.Forms.DataVisualization.Charting.AxisEnabled.True;
            chartArea2.AxisX.IsMarginVisible = false;
            chartArea2.AxisX.IsStartedFromZero = false;
            chartArea2.AxisX.MajorGrid.Interval = 50D;
            chartArea2.AxisX.MajorGrid.LineColor = System.Drawing.Color.Silver;
            chartArea2.AxisX.MajorGrid.LineDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Dash;
            chartArea2.AxisX.MajorTickMark.TickMarkStyle = System.Windows.Forms.DataVisualization.Charting.TickMarkStyle.InsideArea;
            chartArea2.AxisX.MinorGrid.Enabled = true;
            chartArea2.AxisX.MinorGrid.LineColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            chartArea2.AxisX.MinorGrid.LineDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Dash;
            chartArea2.AxisX2.IsStartedFromZero = false;
            chartArea2.AxisY.LineColor = System.Drawing.Color.FromArgb(((int)(((byte)(190)))), ((int)(((byte)(190)))), ((int)(((byte)(190)))));
            chartArea2.AxisY.MajorGrid.Interval = 50D;
            chartArea2.AxisY.MajorGrid.LineColor = System.Drawing.Color.Silver;
            chartArea2.AxisY.MajorGrid.LineDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Dash;
            chartArea2.AxisY.MinorGrid.Enabled = true;
            chartArea2.AxisY.MinorGrid.LineColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            chartArea2.AxisY.MinorGrid.LineDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Dash;
            chartArea2.Name = "ChartArea1";
            this.chart1.ChartAreas.Add(chartArea2);
            legend2.LegendStyle = System.Windows.Forms.DataVisualization.Charting.LegendStyle.Row;
            legend2.Name = "Legend1";
            legend2.Position.Auto = false;
            legend2.Position.Height = 5F;
            legend2.Position.Width = 25.875F;
            legend2.Position.X = 45F;
            legend2.Position.Y = 95F;
            this.chart1.Legends.Add(legend2);
            this.chart1.Location = new System.Drawing.Point(197, 12);
            this.chart1.Name = "chart1";
            series3.ChartArea = "ChartArea1";
            series3.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series3.Color = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(0)))), ((int)(((byte)(192)))));
            series3.CustomProperties = "IsXAxisQuantitative=False";
            series3.Legend = "Legend1";
            series3.Name = "Data1";
            series4.ChartArea = "ChartArea1";
            series4.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series4.Color = System.Drawing.Color.Red;
            series4.Legend = "Legend1";
            series4.Name = "Data1 (Filtered)";
            this.chart1.Series.Add(series3);
            this.chart1.Series.Add(series4);
            this.chart1.Size = new System.Drawing.Size(982, 517);
            this.chart1.TabIndex = 3;
            this.chart1.Text = "chart1";
            // 
            // BtnConnect
            // 
            this.BtnConnect.Location = new System.Drawing.Point(58, 98);
            this.BtnConnect.Name = "BtnConnect";
            this.BtnConnect.Size = new System.Drawing.Size(75, 29);
            this.BtnConnect.TabIndex = 5;
            this.BtnConnect.Text = "Connect";
            this.BtnConnect.UseVisualStyleBackColor = true;
            this.BtnConnect.Click += new System.EventHandler(this.BtnConnect_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(5, 66);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(58, 13);
            this.label1.TabIndex = 8;
            this.label1.Text = "Baud Rate";
            // 
            // txtCom
            // 
            this.txtCom.Location = new System.Drawing.Point(65, 30);
            this.txtCom.Name = "txtCom";
            this.txtCom.Size = new System.Drawing.Size(61, 20);
            this.txtCom.TabIndex = 2;
            this.txtCom.Text = "COM10";
            this.txtCom.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // lbCOM
            // 
            this.lbCOM.AutoSize = true;
            this.lbCOM.Location = new System.Drawing.Point(5, 33);
            this.lbCOM.Name = "lbCOM";
            this.lbCOM.Size = new System.Drawing.Size(52, 13);
            this.lbCOM.TabIndex = 9;
            this.lbCOM.Text = "COM port";
            // 
            // txtBaud
            // 
            this.txtBaud.Location = new System.Drawing.Point(65, 62);
            this.txtBaud.Name = "txtBaud";
            this.txtBaud.Size = new System.Drawing.Size(61, 20);
            this.txtBaud.TabIndex = 10;
            this.txtBaud.Text = "115200";
            this.txtBaud.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // timer1
            // 
            this.timer1.Interval = 50;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // listBox1
            // 
            this.listBox1.FormattingEnabled = true;
            this.listBox1.HorizontalScrollbar = true;
            this.listBox1.Location = new System.Drawing.Point(12, 176);
            this.listBox1.Name = "listBox1";
            this.listBox1.ScrollAlwaysVisible = true;
            this.listBox1.Size = new System.Drawing.Size(158, 173);
            this.listBox1.TabIndex = 11;
            // 
            // txtRt
            // 
            this.txtRt.Location = new System.Drawing.Point(67, 145);
            this.txtRt.Name = "txtRt";
            this.txtRt.Size = new System.Drawing.Size(61, 20);
            this.txtRt.TabIndex = 12;
            this.txtRt.Text = "0.1";
            this.txtRt.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.txtRt.TextChanged += new System.EventHandler(this.txtRt_TextChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(13, 148);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(52, 13);
            this.label2.TabIndex = 13;
            this.label2.Text = "Filter ratio";
            // 
            // txtFile
            // 
            this.txtFile.Location = new System.Drawing.Point(8, 381);
            this.txtFile.Name = "txtFile";
            this.txtFile.Size = new System.Drawing.Size(100, 20);
            this.txtFile.TabIndex = 14;
            this.txtFile.Text = "Data1";
            this.txtFile.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(7, 363);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(51, 13);
            this.label3.TabIndex = 15;
            this.label3.Text = "Name file";
            // 
            // yMax
            // 
            this.yMax.Location = new System.Drawing.Point(197, 40);
            this.yMax.Name = "yMax";
            this.yMax.Size = new System.Drawing.Size(35, 20);
            this.yMax.TabIndex = 16;
            this.yMax.Text = "400";
            this.yMax.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // yMin
            // 
            this.yMin.Location = new System.Drawing.Point(197, 464);
            this.yMin.Name = "yMin";
            this.yMin.Size = new System.Drawing.Size(37, 20);
            this.yMin.TabIndex = 17;
            this.yMin.Text = "100";
            this.yMin.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // cbTail
            // 
            this.cbTail.FormattingEnabled = true;
            this.cbTail.Items.AddRange(new object[] {
            ".txt",
            ".csv"});
            this.cbTail.Location = new System.Drawing.Point(115, 381);
            this.cbTail.Name = "cbTail";
            this.cbTail.Size = new System.Drawing.Size(55, 21);
            this.cbTail.TabIndex = 20;
            this.cbTail.Text = ".txt";
            // 
            // btSet
            // 
            this.btSet.Location = new System.Drawing.Point(197, 68);
            this.btSet.Name = "btSet";
            this.btSet.Size = new System.Drawing.Size(35, 29);
            this.btSet.TabIndex = 21;
            this.btSet.Text = "Set";
            this.btSet.UseVisualStyleBackColor = true;
            this.btSet.Click += new System.EventHandler(this.btSet_Click);
            // 
            // xMax
            // 
            this.xMax.Location = new System.Drawing.Point(1107, 509);
            this.xMax.Name = "xMax";
            this.xMax.Size = new System.Drawing.Size(35, 20);
            this.xMax.TabIndex = 22;
            this.xMax.Text = "400";
            this.xMax.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // txtTrig
            // 
            this.txtTrig.Location = new System.Drawing.Point(104, 441);
            this.txtTrig.Name = "txtTrig";
            this.txtTrig.Size = new System.Drawing.Size(61, 20);
            this.txtTrig.TabIndex = 23;
            this.txtTrig.Text = "50";
            this.txtTrig.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // btnTrig
            // 
            this.btnTrig.Location = new System.Drawing.Point(8, 437);
            this.btnTrig.Name = "btnTrig";
            this.btnTrig.Size = new System.Drawing.Size(86, 27);
            this.btnTrig.TabIndex = 25;
            this.btnTrig.Text = "Trigger freq";
            this.btnTrig.UseVisualStyleBackColor = true;
            this.btnTrig.Click += new System.EventHandler(this.btnTrig_Click);
            // 
            // txtSignal
            // 
            this.txtSignal.Location = new System.Drawing.Point(104, 480);
            this.txtSignal.Name = "txtSignal";
            this.txtSignal.Size = new System.Drawing.Size(61, 20);
            this.txtSignal.TabIndex = 26;
            this.txtSignal.Text = "1";
            this.txtSignal.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(8, 476);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(86, 27);
            this.button1.TabIndex = 27;
            this.button1.Text = "Num signal";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1191, 541);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.txtSignal);
            this.Controls.Add(this.btnTrig);
            this.Controls.Add(this.txtTrig);
            this.Controls.Add(this.xMax);
            this.Controls.Add(this.btSet);
            this.Controls.Add(this.cbTail);
            this.Controls.Add(this.yMin);
            this.Controls.Add(this.yMax);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.txtFile);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.txtRt);
            this.Controls.Add(this.listBox1);
            this.Controls.Add(this.txtBaud);
            this.Controls.Add(this.lbCOM);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.BtnConnect);
            this.Controls.Add(this.chart1);
            this.Controls.Add(this.txtCom);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "Form1";
            this.Text = "Data Acquisition ";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.DataVisualization.Charting.Chart chart1;
        private System.Windows.Forms.Button BtnConnect;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtCom;
        private System.Windows.Forms.Label lbCOM;
        private System.Windows.Forms.TextBox txtBaud;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.TextBox txtRt;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtFile;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox yMax;
        private System.Windows.Forms.TextBox yMin;
        private System.Windows.Forms.ComboBox cbTail;
        private System.Windows.Forms.Button btSet;
        private System.Windows.Forms.TextBox xMax;
        private System.Windows.Forms.TextBox txtTrig;
        private System.Windows.Forms.Button btnTrig;
        private System.Windows.Forms.TextBox txtSignal;
        private System.Windows.Forms.Button button1;
    }
}