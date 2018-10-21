#include "opencv2/opencv.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

/*//Basic OpenCV program from OpenCV doc
//Opens the camera and then apply filtering to display edges only
int main(int, char**)
{
	VideoCapture cap(0); // open the default camera
	if (!cap.isOpened())  // check if we succeeded
		return -1;

	Mat edges;
	namedWindow("edges", 1);
	for (;;)
	{
		Mat frame;
		cap >> frame; // get a new frame from camera
		cvtColor(frame, edges, COLOR_BGR2GRAY);
		GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5); //ini ngapain?
		Canny(edges, edges, 0, 30, 3); //ini juga ngapain?
		imshow("edges", edges);
		if (waitKey(30) >= 0) break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}//*/

/*//Image blending -- blending different image into one
int main(int, char**)
{
	double alpha = 0.5;double beta; double gamma=0.0; double in;

	Mat src1, src2, dst;
	cin >> in;
	if (in >= 0.0 && in <= 1.0)
	{
		alpha = in;
	}
	beta = 1 - alpha;
	src1 = imread("C:\\Users\\Daffa Mage\\Documents\\Kuliah\\Semester 5\\PCV\\imgj.jpg");
	src2 = imread("C:\\Users\\Daffa Mage\\Documents\\Kuliah\\Semester 5\\PCV\\imgz.jpg");

	if (src1.empty()) { cout << "Error loading src1" << endl; return -1; }
	if (src2.empty()) { cout << "Error loading src2" << endl; return -1; }
	resize(src2, src2, Size(src1.cols, src1.rows), 0, 0, CV_INTER_LINEAR);
	beta = (1.0 - alpha);
	addWeighted(src1, alpha, src2, beta, gamma, dst);
	imshow("Linear Blend", dst);
	quit:
	waitKey(0);
	return 0;

}//*/

//Main Code Area
/*
Mat greenFilter(const Mat& src)
{
	assert(src.type() == CV_8UC3);

	Mat greenOnly;
	inRange(src, Scalar(10, 0, 40), Scalar(20, 255, 50), greenOnly);//GBR Model

	return greenOnly;
}

int main(int, char**)
{
	double alpha = 0.5;double beta = 0.5; double gamma = 0.0; double in;

	VideoCapture cap("C:\\Users\\Daffa Mage\\Documents\\Kuliah\\Semester 5\\PCV\\vid1.mp4"); // open the video file
	if (!cap.isOpened())  // check if we succeeded
		return -1;

	VideoCapture bg("C:\\Users\\Daffa Mage\\Documents\\Kuliah\\Semester 5\\PCV\\vid2.mp4"); // open the video file
	if (!cap.isOpened())  // check if we succeeded
		return -1;

	Mat edges;
	Mat res;
	for (;;)
	{
		Mat frame, frame2;
		cap >> frame; //get a frame from the first video
		//bg >> frame2; //get a frame from the second video
		//edges = frame;
		//inRange(frame,Scalar(0,200,0),Scalar(0,255,0),edges);
		//resize(frame2, frame2, Size(frame.cols, frame.rows), 0, 0, CV_INTER_LINEAR);
		edges = greenFilter(frame);
		resize(edges, edges, Size(frame.cols, frame.rows), 0, 0, CV_INTER_LINEAR);
		//resize(res, res, Size(frame.cols, frame.rows), 0, 0, CV_INTER_LINEAR);
		//bitwise_and(frame, edges, res);
		//addWeighted(frame, alpha, frame2, beta, gamma, edges);
		imshow("frame", frame);
		imshow("edges", edges);
		//imshow("res", res);
		//imshow("frame2", frame2);
		if (waitKey(30) >= 0) break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}
//*/

/*//Main Code Verse 2
/// Global Variables for RGB control 
const int red_low_max = 255;
const int red_high_max = 255;
int red_low, red_high;
double red_l, red_h;

const int green_low_max = 255;
const int green_high_max = 255;
int green_low, green_high;
double green_l, green_h;

const int blue_low_max = 255;
const int blue_high_max = 255;
int blue_low, blue_high;
double blue_l, blue_h;

void on_trackbar(int, void*)
{
	red_l = getTrackbarPos("RedLow","Result1");
	red_h = getTrackbarPos("RedHigh", "Result1");

	green_l = getTrackbarPos("GreenLow", "Result1");
	green_h = getTrackbarPos("GreenHigh", "Result1");

	blue_l = getTrackbarPos("BlueLow", "Result1");
	blue_h = getTrackbarPos("BlueHigh", "Result1");
}

void chromakey(const Mat under, const Mat over, Mat *dst, const Scalar& color);

int main()
{
	VideoCapture cap("C:\\Users\\Daffa Mage\\Documents\\Kuliah\\Semester 5\\PCV\\vid1.mp4"); // open the video file
	if (!cap.isOpened())  // check if we succeeded
		return -1;

	VideoCapture bg("C:\\Users\\Daffa Mage\\Documents\\Kuliah\\Semester 5\\PCV\\vid2.mp4"); // open the video file
	if (!cap.isOpened())  // check if we succeeded
		return -1;

	namedWindow("Result1", 1);

	createTrackbar("RedLow", "Result1", 0, 255,on_trackbar);
	createTrackbar("RedHigh", "Result1", 0, 255,on_trackbar);
	createTrackbar("GreenLow", "Result1", 0, 255,on_trackbar);
	createTrackbar("GreenHigh", "Result1", 0, 255,on_trackbar);
	createTrackbar("BlueLow", "Result1", 0, 255,on_trackbar);
	createTrackbar("BlueHigh", "Result1", 0, 255,on_trackbar);

	setTrackbarPos("RedLow", "Result1", 10);
	setTrackbarPos("GreenLow", "Result1", 10);
	setTrackbarPos("BlueLow", "Result1", 10);

	setTrackbarPos("RedHigh", "Result1", 40);
	setTrackbarPos("GreenHigh", "Result1", 255);
	setTrackbarPos("BlueHigh", "Result1", 40);

	for(;;)
	{
		Mat imgRGB, combined_image, background;
		cap >> imgRGB;
		bg >> background;
		resize(background, background, Size(600, 400), 0, 0, CV_INTER_LINEAR);
		resize(imgRGB, imgRGB, Size(600, 400), 0, 0, CV_INTER_LINEAR);
		chromakey(background, imgRGB, &combined_image, Scalar(0, 255, 0));
		imshow("combined_image", combined_image);
		resizeWindow("combined_image",Size(600,400));
		if (waitKey(30) >= 0) break;
	}
	return 0;
}

void chromakey(const Mat under, const Mat over, Mat *dst, const Scalar& color)
{
	*dst = Mat(under.rows, under.cols, CV_8UC3);
	for (int y = 0;y < under.rows;y++)
	{
		for (int x = 0; x < under.cols;x++)
		{
			if (over.at<Vec3b>(y, x)[0] >= red_l && over.at<Vec3b>(y, x)[0] <= red_h && over.at<Vec3b>(y, x)[0] >= green_l && over.at<Vec3b>(y, x)[0] <= green_h && over.at<Vec3b>(y, x)[0] >= blue_l && over.at<Vec3b>(y, x)[0] <= blue_h)
			{
				dst->at<Vec3b>(y, x)[0] = under.at < Vec3b> (y, x)[0];
				dst->at<Vec3b>(y, x)[1] = under.at < Vec3b> (y, x)[1];
				dst->at<Vec3b>(y, x)[2] = under.at < Vec3b> (y, x)[2];
			}
			else
			{
				dst->at<Vec3b>(y, x)[0] = over.at < Vec3b>(y, x)[0];
				dst->at<Vec3b>(y, x)[1] = over.at < Vec3b>(y, x)[1];
				dst->at<Vec3b>(y, x)[2] = over.at < Vec3b>(y, x)[2];
			}
		}
	}
}
//*/

//Main Code Verse 3
/// Global Variables for control 
const int hue_low_max = 180;
const int hue_high_max = 180;
int hue_low, hue_high;
double hue_l, hue_h;

const int sat_low_max = 255;
const int sat_high_max = 255;
int sat_low, sat_high;
double sat_l, sat_h;

const int int_low_max = 255;
const int int_high_max = 255;
int int_low, int_high;
double int_l, int_h;

void on_trackbar(int, void*)
{
	hue_l = getTrackbarPos("HueLow", "Result1");
	hue_h = getTrackbarPos("HueHigh", "Result1");

	sat_l = getTrackbarPos("SatLow", "Result1");
	sat_h = getTrackbarPos("SatHigh", "Result1");

	int_l = getTrackbarPos("IntLow", "Result1");
	int_h = getTrackbarPos("IntHigh", "Result1");
}

void chromakey(const Mat under, const Mat over, Mat *dst, const Scalar& color, const Mat layer);

int main()
{
	VideoCapture cap("C:\\Users\\Daffa Mage\\Documents\\Kuliah\\Semester 5\\PCV\\vid1.mp4"); // open the video file
	if (!cap.isOpened())  // check if we succeeded
		return -1;

	VideoCapture bg("C:\\Users\\Daffa Mage\\Documents\\Kuliah\\Semester 5\\PCV\\vid2.mp4"); // open the video file
	if (!cap.isOpened())  // check if we succeeded
		return -1;

	namedWindow("Result1", 1);

	createTrackbar("HueLow", "Result1", 0, 180, on_trackbar);
	createTrackbar("HueHigh", "Result1", 0, 180, on_trackbar);
	createTrackbar("SatLow", "Result1", 0, 255, on_trackbar);
	createTrackbar("SatHigh", "Result1", 0, 255, on_trackbar);
	createTrackbar("IntLow", "Result1", 0, 255, on_trackbar);
	createTrackbar("IntHigh", "Result1", 0, 255, on_trackbar);

	setTrackbarPos("HueLow", "Result1", 0);
	setTrackbarPos("SatLow", "Result1", 0);
	setTrackbarPos("IntLow", "Result1", 77);

	setTrackbarPos("HueHigh", "Result1", 120);
	setTrackbarPos("SatHigh", "Result1", 100);
	setTrackbarPos("IntHigh", "Result1", 100);

	for (;;)
	{
		Mat imgRGB, imgHSV, combined_image, background;
		cap >> imgRGB;
		bg >> background;
		resize(background, background, Size(600, 400), 0, 0, CV_INTER_LINEAR);
		resize(imgRGB, imgRGB, Size(600, 400), 0, 0, CV_INTER_LINEAR);
		cvtColor(imgRGB, imgHSV, CV_RGB2HSV_FULL);
		chromakey(background, imgHSV, &combined_image, Scalar(0, 255, 0), imgRGB);
		imshow("combined_image", combined_image);
		imshow("imgRGB", imgRGB);
		imshow("background", background);
		if (waitKey(30) >= 0) break;
	}
	return 0;
}

void chromakey(const Mat under, const Mat over, Mat *dst, const Scalar& color, const Mat layer)
{
	*dst = Mat(under.rows, under.cols, CV_8UC3);
	for (int y = 0;y < under.rows;y++)
	{
		for (int x = 0; x < under.cols;x++)
		{
			if (over.at<Vec3b>(y, x)[0] >= hue_l && over.at<Vec3b>(y, x)[0] <= hue_h && over.at<Vec3b>(y, x)[0] >= sat_l && over.at<Vec3b>(y, x)[0] <= sat_h && over.at<Vec3b>(y, x)[0] >= int_l && over.at<Vec3b>(y, x)[0] <= int_h)
			{
				dst->at<Vec3b>(y, x)[0] = under.at < Vec3b>(y, x)[0];
				dst->at<Vec3b>(y, x)[1] = under.at < Vec3b>(y, x)[1];
				dst->at<Vec3b>(y, x)[2] = under.at < Vec3b>(y, x)[2];
			}
			else
			{
				dst->at<Vec3b>(y, x)[0] = layer.at < Vec3b>(y, x)[0];
				dst->at<Vec3b>(y, x)[1] = layer.at < Vec3b>(y, x)[1];
				dst->at<Vec3b>(y, x)[2] = layer.at < Vec3b>(y, x)[2];
			}
		}
	}
}
//*/
