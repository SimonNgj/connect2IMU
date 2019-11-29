
// ChartllDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Chartll.h"
#include "ChartllDlg.h"
#include "afxdialogex.h"
#include <math.h>
#include <sstream>
#include <vector>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <msclr\marshal_cppstd.h>
#include <iostream>
#include <cstring>
#using <System.dll>

using namespace std;
using namespace System;
using namespace System::IO::Ports;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Variables 
vector<int> vect;
std::ofstream myfile;
std::string file_result;
gcroot<SerialPort^> mySerialPort = nullptr;
std::string incomingData;
int serialBUSY = 0;
double kl = 0;
clock_t beginT;
clock_t endT;
double elapT = 0;
double elapS = 0;

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CChartllDlg dialog

CChartllDlg::CChartllDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CHARTLL_DIALOG, pParent)
	, filesave_name(_T("Data1.csv"))
	, com_name(_T("COM10"))
	, com_baud(115200)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

//
// Destructor
//
CChartllDlg::~CChartllDlg()
{
	delete m_ChartViewer.getChart();
	delete m_ViewPortControl.getChart();
	//delete dataSource;
}

void CChartllDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PointerPB, m_PointerPB);
	DDX_Control(pDX, IDC_ChartViewer, m_ChartViewer);
	DDX_Control(pDX, IDC_ViewPortControl, m_ViewPortControl);
	DDX_Text(pDX, txtMyfile, filesave_name);
	DDX_Text(pDX, txtCOM, com_name);
	DDX_Text(pDX, txtBAUD, com_baud);
}

BEGIN_MESSAGE_MAP(CChartllDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PointerPB, &CChartllDlg::OnPointerPB)
	ON_BN_CLICKED(IDC_ZoomInPB, &CChartllDlg::OnZoomInPB)
	ON_BN_CLICKED(IDC_ZoomOutPB, &CChartllDlg::OnZoomOutPB)
	ON_BN_CLICKED(IDC_SavePB, &CChartllDlg::OnSavePB)
	ON_CONTROL(CVN_ViewPortChanged, IDC_ChartViewer, OnViewPortChanged)
	ON_CONTROL(CVN_MouseMovePlotArea, IDC_ChartViewer, OnMouseMovePlotArea)
	ON_WM_TIMER()
	ON_BN_CLICKED(btnStart, &CChartllDlg::OnBnClickedbtnstart)
END_MESSAGE_MAP()

// CChartllDlg message handlers

BOOL CChartllDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//// Open a console window
	//AllocConsole();
	//SetConsoleTitle(_T("Debug Output"));
	//freopen("CONOUT$", "w", stdout);

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//
	// Initialize member variables
	
	m_currentIndex = 0;

	// Initially, auto-move the track line to make it follow the data series
	trackLineEndPos = 0;
	trackLineIsAtEnd = true;

	// Initially set the mouse to drag to scroll mode.
	m_PointerPB.SetCheck(1);
	m_ChartViewer.setMouseUsage(Chart::MouseUsageScroll);

	// Enable mouse wheel zooming by setting the zoom ratio to 1.1 per wheel event
	m_ChartViewer.setMouseWheelZoomRatio(1.1);

	// Configure the initial viewport 
	m_ChartViewer.setViewPortWidth(initialVisibleRange / (double)initialFullRange);

	// Bind the CChartViewer to the CViewPortControl
	m_ViewPortControl.setViewer(&m_ChartViewer);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CChartllDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CChartllDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CChartllDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CChartllDlg::OnPointerPB()
{
	// TODO: Add your control notification handler code here
	m_ChartViewer.setMouseUsage(Chart::MouseUsageScroll);
}

void CChartllDlg::OnZoomInPB()
{
	// TODO: Add your control notification handler code here
	m_ChartViewer.setMouseUsage(Chart::MouseUsageZoomIn);
}

void CChartllDlg::OnZoomOutPB()
{
	// TODO: Add your control notification handler code here
	m_ChartViewer.setMouseUsage(Chart::MouseUsageZoomOut);
}

void CChartllDlg::OnSavePB()
{
	// TODO: Add your control notification handler code here
	TCHAR szFilters[] = _T("PNG (*.png)|*.png|JPG (*.jpg)|*.jpg|GIF (*.gif)|*.gif|")
		_T("BMP (*.bmp)|*.bmp|SVG (*.svg)|*.svg|PDF (*.pdf)|*.pdf||");

	// The standard CFileDialog
	CFileDialog fileDlg(FALSE, _T("png"), _T("chartdirector_demo"), OFN_HIDEREADONLY |
		OFN_OVERWRITEPROMPT, szFilters);
	if (fileDlg.DoModal() != IDOK)
		return;

	// Save the chart
	CString path = fileDlg.GetPathName();
	BaseChart *c = m_ChartViewer.getChart();
	if (0 != c)
		c->makeChart(TCHARtoUTF8(path));
}

void CChartllDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == ChartUpdateTimer)
		OnChartUpdateTimer();

	CDialog::OnTimer(nIDEvent);
}

////////////////////////////////////////////////////////////////////////
// Split a string into vectors
std::vector<std::string> split(std::string strToSplit, char delimeter)
{
	std::stringstream ss(strToSplit);
	std::string item;
	std::vector<std::string> splittedStrings;
	while (std::getline(ss, item, delimeter))
	{
		splittedStrings.push_back(item);
	}
	return splittedStrings;
}

// Implement a sub-function at every timer update
void CChartllDlg::OnChartUpdateTimer()
{
	/////////////////////from COM port////////////////////////
	// Calculate the elapsed time to check the timer period
	endT = clock();
	elapT = double(endT - beginT);
	beginT = endT;
	elapS += elapT / 1000;
	// Split a string by ',' into vectors
	vector<string> a = split(incomingData, ',');
	myfile << elapT << " ";
	//myfile << kl << " " << elapT << " ";
	//kl++;

	for (int i = 0; i < a.size(); i++)
	{
		//// cout function takes too much time to proceed
		//cout << stoi(a[i]) << " ";
		myfile << stoi(a[i]) << " ";
	}
	myfile << endl;
	//cout << endl;
	////////////////////////////////////////////////////////////

	CChartViewer *viewer = &m_ChartViewer;

	// Enables auto scroll if the viewport is showing the latest data before the update
	bool autoScroll = (m_currentIndex > 0) && (0.001 + viewer->getValueAtViewPort("x",
		viewer->getViewPortLeft() + viewer->getViewPortWidth()) >= m_timeStamps[m_currentIndex - 1]);

	//
	// Get new data from the queue and append them to the data arrays
	//
	int count = 2;
	//DataPacket *packets;
	//if ((count = buffer.get(&packets)) <= 0)
	//	return;

	// if data arrays have insufficient space, we need to remove some old data.
	if (m_currentIndex + 2 >= sampleSize)
	{
		// For safety, we check if the queue contains too much data than the entire data arrays. If
		// this is the case, we only use the latest data to completely fill the data arrays.
		//if (count > sampleSize)
		//{
		//	packets += count - sampleSize;
		//	count = sampleSize;
		//}

		// Remove oldest data to leave space for new data. To avoid frequent removal, we ensure at
		// least 5% empty space available after removal. 
		int originalIndex = m_currentIndex;
		m_currentIndex = sampleSize * 95 / 100 - 1;
		if (m_currentIndex > sampleSize - count)
			m_currentIndex = sampleSize - count;

		for (int i = 0; i < m_currentIndex; ++i)
		{
			int srcIndex = i + originalIndex - m_currentIndex;
			m_timeStamps[i] = m_timeStamps[srcIndex];
			m_dataSeriesA[i] = m_dataSeriesA[srcIndex];
			m_dataSeriesB[i] = m_dataSeriesB[srcIndex];
		}
	}

	// Append the data from the queue to the data arrays
	m_timeStamps[m_currentIndex] = elapS;
	m_dataSeriesA[m_currentIndex] = stoi(a[0]); // First data from Arduino
	m_dataSeriesB[m_currentIndex] = stoi(a[1]); // Second data from Arduino
	//m_dataSeriesC[m_currentIndex] = stoi(a[2]); // Probably third data from Arduino
	++m_currentIndex;

	//
	// As we added more data, we may need to update the full range of the viewport. 
	//

	double startDate = m_timeStamps[0];
	double endDate = m_timeStamps[m_currentIndex - 1];

	// Use the initialFullRange (which is 60 seconds in this demo) if this is sufficient.
	double duration = endDate - startDate;
	if (duration < initialFullRange)
		endDate = startDate + initialFullRange;

	// Update the new full data range to include the latest data
	bool axisScaleHasChanged = viewer->updateFullRangeH("x", startDate, endDate,
		Chart::KeepVisibleRange);

	if (autoScroll)
	{
		// Scroll the viewport if necessary to display the latest data
		double viewPortEndPos = viewer->getViewPortAtValue("x", m_timeStamps[m_currentIndex - 1]);
		if (viewPortEndPos > viewer->getViewPortLeft() + viewer->getViewPortWidth())
		{
			viewer->setViewPortLeft(viewPortEndPos - viewer->getViewPortWidth());
			axisScaleHasChanged = true;
		}
	}

	// Set the zoom in limit as a ratio to the full range
	viewer->setZoomInWidthLimit(zoomInLimit / (viewer->getValueAtViewPort("x", 1) -
		viewer->getValueAtViewPort("x", 0)));

	// Trigger the viewPortChanged event. Updates the chart if the axis scale has changed
	// (scrolling or zooming) or if new data are added to the existing axis scale.
	viewer->updateViewPort(axisScaleHasChanged || (duration < initialFullRange), false);
}

// Draw chart (focused part)
void CChartllDlg::drawChart(CChartViewer *viewer)
{
	// Get the start date and end date that are visible on the chart.
	double viewPortStartDate = viewer->getValueAtViewPort("x", viewer->getViewPortLeft());
	double viewPortEndDate = viewer->getValueAtViewPort("x", viewer->getViewPortLeft() +
		viewer->getViewPortWidth());

	// Extract the part of the data arrays that are visible.
	DoubleArray viewPortTimeStamps;
	DoubleArray viewPortDataSeriesA;
	DoubleArray viewPortDataSeriesB;
	// DoubleArray viewPortDataSeriesC;

	if (m_currentIndex > 0)
	{
		// Get the array indexes that corresponds to the visible start and end dates
		int startIndex = (int)floor(Chart::bSearch(DoubleArray(m_timeStamps, m_currentIndex), viewPortStartDate));
		int endIndex = (int)ceil(Chart::bSearch(DoubleArray(m_timeStamps, m_currentIndex), viewPortEndDate));
		int noOfPoints = endIndex - startIndex + 1;

		// Extract the visible data
		if (m_timeStamps[endIndex] >= viewPortStartDate)
		{
			viewPortTimeStamps = DoubleArray(m_timeStamps + startIndex, noOfPoints);
			viewPortDataSeriesA = DoubleArray(m_dataSeriesA + startIndex, noOfPoints);
			viewPortDataSeriesB = DoubleArray(m_dataSeriesB + startIndex, noOfPoints);
			//viewPortDataSeriesC = DoubleArray(m_dataSeriesC + startIndex, noOfPoints);
		}

		// Keep track of the latest available data at chart plotting time
		trackLineEndPos = m_timeStamps[m_currentIndex - 1];
	}

	//
	// At this stage, we have extracted the visible data. We can use those data to plot the chart.
	//

	//================================================================================
	// Configure overall chart appearance.
	//================================================================================

	// Create an XYChart object of size 640 x 350 pixels
	XYChart *c = new XYChart(640, 350);

	// Set the plotarea at (20, 30) with width 41 pixels less than chart width, and height 50 pixels
	// less than chart height. Use a vertical gradient from light blue (f0f6ff) to sky blue (a0c0ff)
	// as background. Set border to transparent and grid lines to white (ffffff).
	c->setPlotArea(20, 30, c->getWidth() - 41, c->getHeight() - 50, c->linearGradientColor(0, 30, 0,
		c->getHeight() - 50, 0xf0f6ff, 0xa0c0ff), -1, Chart::Transparent, 0xffffff, 0xffffff);

	// As the data can lie outside the plotarea in a zoomed chart, we need enable clipping.
	c->setClipping();

	// Add a title to the chart using 18pt Arial font
	c->addTitle("Realtime line chart", "arial.ttf", 18);

	// Add a legend box at (55, 25) using horizontal layout. Use 10pt Arial Bold as font. Set the
	// background and border color to transparent and use line style legend key.
	LegendBox *b = c->addLegend(55, 25, false, "arialbd.ttf", 10);
	b->setBackground(Chart::Transparent);
	b->setLineStyleKey();

	// Set the x and y axis stems to transparent and the label font to 10pt Arial
	c->xAxis()->setColors(Chart::Transparent);
	c->yAxis()->setColors(Chart::Transparent);
	c->xAxis()->setLabelStyle("arial.ttf", 10);
	c->yAxis()->setLabelStyle("arial.ttf", 10, 0x336699);

	// Set the y-axis tick length to 0 to disable the tick and put the labels closer to the axis.
	c->yAxis()->setTickLength(0);

	// Add axis title using 10pt Arial Bold Italic font
	c->yAxis()->setTitle("Sensor output", "arialbd.ttf", 10);

	// Configure the y-axis label to be inside the plot area and above the horizontal grid lines
	c->yAxis()->setLabelGap(-1);
	c->yAxis()->setLabelAlignment(1);
	c->yAxis()->setMargin(20);

	// Configure the x-axis labels to be to the left of the vertical grid lines
	c->xAxis()->setLabelAlignment(1);

	//================================================================================
	// Add data to chart
	//================================================================================

	//
	// In this example, we represent the data by lines. You may modify the code below to use other
	// representations (areas, scatter plot, etc).
	//

	// Add a line layer for the lines, using a line width of 2 pixels
	LineLayer *layer = c->addLineLayer();
	layer->setLineWidth(3);
	layer->setFastLineMode();

	// Now we add the 2 data series to the line layer with red (ff0000) and green (00cc00) colors
	layer->setXData(viewPortTimeStamps);
	layer->addDataSet(viewPortDataSeriesA, 0xff0000, "Alpha");
	layer->addDataSet(viewPortDataSeriesB, 0x00cc00, "Beta");
	//layer->addDataSet(viewPortDataSeriesC, 0x00ccdd, "Gamma");

	//================================================================================
	// Configure axis scale and labelling
	//================================================================================

	// Set the x-axis as a date/time axis with the scale according to the view port x range.
	if (m_currentIndex > 0)
		c->xAxis()->setDateScale(viewPortStartDate, viewPortEndDate);

	// For the automatic axis labels, set the minimum spacing to 75/30 pixels for the x/y axis.
	c->xAxis()->setTickDensity(75);
	c->yAxis()->setTickDensity(30);

	// We use "nn:ss" as the axis label format.
	c->xAxis()->setLabelFormat("{value|nn:ss}");

	// We make sure the tick increment must be at least 1 second.
	c->xAxis()->setMinTickInc(1);

	// Set the auto-scale margin to 0.05, and the zero affinity to 0.6
	c->yAxis()->setAutoScale(0.05, 0.05, 0.6);

	//================================================================================
	// Output the chart
	//================================================================================

	// We need to update the track line too. If the mouse is moving on the chart (eg. if 
	// the user drags the mouse on the chart to scroll it), the track line will be updated
	// in the MouseMovePlotArea event. Otherwise, we need to update the track line here.
	if (!viewer->isInMouseMoveEvent())
		trackLineLabel(c, trackLineIsAtEnd ? c->getWidth() : viewer->getPlotAreaMouseX());

	// Set the chart image to the CChartViewer
	delete viewer->getChart();
	viewer->setChart(c);
}

// Draw full chart (small size on the botton)
void CChartllDlg::drawFullChart(CViewPortControl *vpc)
{
	// Create an XYChart object of size 640 x 60 pixels   
	XYChart *c = new XYChart(640, 60);

	// Set the plotarea with the same horizontal position as that in the main chart for alignment.
	c->setPlotArea(20, 0, c->getWidth() - 41, c->getHeight() - 1, 0xc0d8ff, -1, 0xcccccc,
		Chart::Transparent, 0xffffff);

	// Set the x axis stem to transparent and the label font to 10pt Arial
	c->xAxis()->setColors(Chart::Transparent);
	c->xAxis()->setLabelStyle("Arial", 10);

	// Put the x-axis labels inside the plot area by setting a negative label gap. Use
	// setLabelAlignment to put the label at the right side of the tick.
	c->xAxis()->setLabelGap(-1);
	c->xAxis()->setLabelAlignment(1);

	// Set the y axis stem and labels to transparent (that is, hide the labels)
	c->yAxis()->setColors(Chart::Transparent, Chart::Transparent);

	// Add a line layer for the lines with fast line mode enabled
	LineLayer *layer = c->addLineLayer();
	layer->setFastLineMode();

	// Now we add the 3 data series to a line layer, using the color red (0xff3333), green
	// (0x008800) and blue (0x3333cc)
	layer->setXData(DoubleArray(m_timeStamps, m_currentIndex));
	layer->addDataSet(DoubleArray(m_dataSeriesA, m_currentIndex), 0xff3333);
	layer->addDataSet(DoubleArray(m_dataSeriesB, m_currentIndex), 0x008800);

	// The x axis scales should reflect the full range of the view port
	c->xAxis()->setDateScale(vpc->getViewer()->getValueAtViewPort("x", 0),
		vpc->getViewer()->getValueAtViewPort("x", 1));
	c->xAxis()->setLabelFormat("{value|nn:ss}");

	// For the automatic x-axis labels, set the minimum spacing to 75 pixels.
	c->xAxis()->setTickDensity(75);

	// For the auto-scaled y-axis, as we hide the labels, we can disable axis rounding. This can
	// make the axis scale fit the data tighter.
	c->yAxis()->setRounding(false, false);

	// Output the chart
	delete vpc->getChart();
	vpc->setChart(c);
}

// Display the t time
double CChartllDlg::trackLineLabel(XYChart *c, int mouseX)
{
	// Clear the current dynamic layer and get the DrawArea object to draw on it.
	DrawArea *d = c->initDynamicLayer();

	// The plot area object
	PlotArea *plotArea = c->getPlotArea();

	// Get the data x-value that is nearest to the mouse, and find its pixel coordinate.
	double xValue = c->getNearestXValue(mouseX);
	int xCoor = c->getXCoor(xValue);
	if (xCoor < plotArea->getLeftX())
		return xValue;

	// Draw a vertical track line at the x-position
	d->vline(plotArea->getTopY(), plotArea->getBottomY(), xCoor, 0x888888);

	// Draw a label on the x-axis to show the track line position.
	ostringstream xlabel;
	xlabel << "<*font,bgColor=000000*> " << c->xAxis()->getFormattedLabel(xValue + 0.00499,
		"nn:ss.ff") << " <*/font*>";
	TTFText *t = d->text(xlabel.str().c_str(), "arialbd.ttf", 10);

	// Restrict the x-pixel position of the label to make sure it stays inside the chart image.
	int xLabelPos = max(0, min(xCoor - t->getWidth() / 2, c->getWidth() - t->getWidth()));
	t->draw(xLabelPos, plotArea->getBottomY() + 2, 0xffffff);
	t->destroy();

	// Iterate through all layers to draw the data labels
	for (int i = 0; i < c->getLayerCount(); ++i) {
		Layer *layer = c->getLayerByZ(i);

		// The data array index of the x-value
		int xIndex = layer->getXIndexOf(xValue);

		// Iterate through all the data sets in the layer
		for (int j = 0; j < layer->getDataSetCount(); ++j)
		{
			DataSet *dataSet = layer->getDataSetByZ(j);
			const char *dataSetName = dataSet->getDataName();

			// Get the color, name and position of the data label
			int color = dataSet->getDataColor();
			int yCoor = c->getYCoor(dataSet->getPosition(xIndex), dataSet->getUseYAxis());

			// Draw a track dot with a label next to it for visible data points in the plot area
			if ((yCoor >= plotArea->getTopY()) && (yCoor <= plotArea->getBottomY()) && (color !=
				Chart::Transparent) && dataSetName && *dataSetName)
			{
				d->circle(xCoor, yCoor, 4, 4, color, color);

				ostringstream label;
				label << "<*font,bgColor=" << hex << color << "*> "
					<< c->formatValue(dataSet->getValue(xIndex), "{value|P4}") << " <*font*>";
				t = d->text(label.str().c_str(), "arialbd.ttf", 10);

				// Draw the label on the right side of the dot if the mouse is on the left side the
				// chart, and vice versa. This ensures the label will not go outside the chart image.
				if (xCoor <= (plotArea->getLeftX() + plotArea->getRightX()) / 2)
					t->draw(xCoor + 6, yCoor, 0xffffff, Chart::Left);
				else
					t->draw(xCoor - 6, yCoor, 0xffffff, Chart::Right);

				t->destroy();
			}
		}
	}

	return xValue;
}

void CChartllDlg::OnViewPortChanged()
{
	// Update the chart if necessary
	if (m_ChartViewer.needUpdateChart())
		drawChart(&m_ChartViewer);

	// Update the full chart
	drawFullChart(&m_ViewPortControl);
}

// Mouse event when move the mouse in the chart area (the focused one)
void CChartllDlg::OnMouseMovePlotArea()
{
	double trackLinePos = trackLineLabel((XYChart *)m_ChartViewer.getChart(),
		m_ChartViewer.getPlotAreaMouseX());
	trackLineIsAtEnd = (m_currentIndex <= 0) || (trackLinePos == trackLineEndPos);
	m_ChartViewer.updateDisplay();
}

// Data receiver handler for serial port
static void DataReceivedHandler(Object^ sender, SerialDataReceivedEventArgs^ e)
{
	SerialPort^ sp = (SerialPort^)sender;
	// Read the whole line data
	String^ indata = sp->ReadLine();
	incomingData = msclr::interop::marshal_as<std::string>(indata);

	//String^ indata = sp->ReadExisting();
	//// Write data to the file
	//myfile << indata;
}

// Start to connect to serial port
void CChartllDlg::OnBnClickedbtnstart()
{
	UpdateData(true);
	CString name;
	GetDlgItem(btnStart)->GetWindowText(name);

	// The button text has 2 modes: CONNECT and DISCONNECT
	if (name == "CONNECT")
	{
		// Configure a serial port
		String^ comN = gcnew System::String(com_name);
		mySerialPort = gcnew SerialPort(comN);
		mySerialPort->BaudRate = com_baud;
		mySerialPort->Parity = Parity::None;
		mySerialPort->StopBits = StopBits::One;
		mySerialPort->DataBits = 8;
		mySerialPort->Handshake = Handshake::None;
		mySerialPort->RtsEnable = true;
		// Whenever there's a serial event, go to DataReceivedHandler function
		mySerialPort->DataReceived += gcnew SerialDataReceivedEventHandler(DataReceivedHandler);
		mySerialPort->Open();
		Sleep(1);

		// Open a file to store sensor signal
		std::wstring wstr_fileName = (std::wstring)filesave_name;
		file_result.assign(wstr_fileName.begin(), wstr_fileName.end());
		myfile.open(file_result);

		// Turn to disconnection mode
		GetDlgItem(btnStart)->SetWindowText(L"DISCONNECT");

		// Start a clock to count the elapsed time
		beginT = clock();
		// The chart update rate is set to 50ms
		SetTimer(ChartUpdateTimer, 50, 0);
	}
	else
	{
		GetDlgItem(btnStart)->SetWindowText(L"CONNECT");

		// Stop the timer
		KillTimer(1);

		// Close the serial port
		mySerialPort->Close();


		myfile.close();
	}
	UpdateData(false);
}
