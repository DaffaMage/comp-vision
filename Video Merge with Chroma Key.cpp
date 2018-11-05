#include "opencv2/opencv.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

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
