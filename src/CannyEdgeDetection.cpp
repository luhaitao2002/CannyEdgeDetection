#include "..\include\CImg.h"
#include <iostream>

using namespace cimg_library;
using namespace std;

const float pi = 3.1415926f;

int main()
{
	//// ����һ��ÿ����ɫ 8 λ(bit)�� 640x400 �Ĳ�ɫͼ��
	//CImg<unsigned char> img(640, 400, 1, 3);
	////������ֵ��Ϊ 0����ɫ��
	//img.fill(0);
	//// ����һ����ɫ
	//unsigned char purple[] = { 255,0,255 };

	//// ������(100, 100)����һ����ɫ�ġ�Hello world��
	//img.draw_text(100, 100, "Hello World", purple);
	//// ��һ������Ϊ��My first CImg code���Ĵ�������ʾ���ͼ��
	//img.display("My first CImg code");


	//����ԭͼ lena
	CImg<float> *image = new CImg<float>("lena.bmp");
	//image->display("My first CImg code");

	//ԭͼת��Ϊ�Ҷ�ͼ
	int col = 500;
	int row = 500;
	CImg<float>* Gray_image = new CImg<float>(col, row, 1, 1, 0);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			float r = (*image)(j, i, 0);
			float g = (*image)(j, i, 1);
			float b = (*image)(j, i, 2);
			(*Gray_image)(j, i, 0) = 0.299f*r + 0.587f*g + 0.114f*b;
		}
	}


	//�����˹ģ���ľ����
	int kSize = 5;
	float filter[5][5] = {};
	float sigma = 1.5f;
	float coordSum = 0;
	float constant = 2.0f * sigma * sigma;
	float sum = 0.0f;
	for (int x=-kSize/2; x<=kSize/2; x++)
	{
		for (int y=-kSize/2; y<=kSize/2; y++)
		{
			coordSum = (float)(x*x + y * y);
			filter[x + kSize/2][y + kSize/2] = (exp(-(coordSum) / constant)) / sqrt(pi*constant);
			sum += filter[x + kSize / 2][y + kSize / 2];
		}
	}

	std::cout << "Filter:" << std::endl;
	for (int i = 0; i < kSize; i++)
	{
		for (int j = 0; j < kSize; j++)
		{
			filter[i][j] /= sum;
			std::cout << filter[i][j] << " ";
		}
	}
	cout << endl;


	//���и�˹ģ������
	CImg<float>* Gaussian_image = new CImg<float>(col, row, 1, 1, 0);
	for (int i = kSize; i < col - kSize; i++)
	{
		for (int j = kSize; j < row - kSize; j++)
		{
			sum = 0.0f;
			for (int x = 0; x < kSize; x++)
			{
				for (int y = 0; y < kSize; y++)
				{
					int image_x = x - kSize + i;
					int image_y = y - kSize + j;
					sum += filter[x][y] * ((*Gray_image)(image_x, image_y, 0));
				}
			}

			if (sum > 255)
				sum = 255;
			(*Gaussian_image)(i, j, 0) = sum;
		}
	}

	//Gray_image->display("My Gray CImg code");
	//Gaussian_image->display("My Gaussian CImg code");


	//����ͼ���ݶȵķ�ֵ�ͷ���
	int gSize = 3;
	int  SlobelX  [3][3] = 
	{
		{-1,0,1},
		{-2,0,2},
		{-1,0,1}
	};

	int  SlobelY[3][3] =
	{
		{1,2,1},
		{0,0,0},
		{-1,-2,-1}
	};





	return 0;
}