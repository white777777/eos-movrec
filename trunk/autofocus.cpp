/***************************************************************************
 *   Copyright (C) 2008-2009 by ������ �.�.                                *
 *   valexlin@gmail.com                                                    *
 *   --                                                                    *
 *   Copyright (C) 2009 by Uterr                                           *
 *     Old AF method                                                       *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "autofocus.h"

#include <stdlib.h>
#include <math.h>

#if AF_DEBUG_LOG
#include <QImage>
#include <stdio.h>

static QImage array_to_image(int** array, int w, int h);
#endif

GAutoFocus::GAutoFocus()
{
	Noise = 0.0;
	stop = false;
	focus_step = 8;
	NextFocus = focus_step;
	change_count = 0;
	NoiseCounts = 10;		// must calibrate
}

GAutoFocus::~GAutoFocus()
{
	/*int infs = finfos.count();
	for (int i = 0; i < infs; i++)
	{
		delete finfos[i];
	}
	finfos.clear();*/
}

int GAutoFocus::lastDispersion()
{
	int last_index = finfos.count() - 1;
	if (last_index < 0)
		return 0.0;
	return finfos[last_index].dispersion;
}

int GAutoFocus::lastPosition()
{
	int last_index = finfos.count() - 1;
	if (last_index < 0)
		return 0.0;
	return finfos[last_index].focusPosition;
}

void GAutoFocus::NextIter(int **image_arr, int w, int h, int* cookie)
{
	if (stop)
		return;

	int i;
	int last_index = finfos.count() - 1;
	focusingInfo finf;
	int** sobel_image = sobel_trans(image_arr, w, h);
#if AF_DEBUG_LOG
	QString name1 = QString("afimg_%1.bmp").arg(*cookie, 3, 10);
	QString name2 = QString("afimg_%1_sobel.bmp").arg(*cookie, 3, 10);
	char name3[128];
	sprintf(name3, "afimg_%3d.txt", *cookie);
	array_to_image(image_arr, w, h).save(name1);
	array_to_image(sobel_image, w, h).save(name2);
	FILE* info = fopen(name3, "wt");
#endif
	finf.dispersion = dispersion(sobel_image, w, h);	// this value of dispersion is a result of previous NextFocus
	// delete sobel image
	for (i = 0; i < h; i++)
		free(sobel_image[i]);
	free(sobel_image);
	if (last_index >= NoiseCounts)
	{
		finf.focusPosition = finfos[last_index].focusPosition + NextFocus;
		finf.focusDir = NextFocus;
	}
	else
	{
		finf.focusPosition = 0;
		finf.focusDir = 0;
	}
	finfos.append(finf);
	last_index++;

	if (last_index == NoiseCounts - 1)
	{
		// ���������� ����� - ������� ���������� )))
		//Noise = (maxdispersion() - mindispersion())/2;
		int avg = 0;
		int s = 0;
		for (i = 0; i < NoiseCounts; i++)
			avg += finfos[i].dispersion;
		avg /= NoiseCounts;
		for (i = 0; i < NoiseCounts; i++)
			s += (finfos[i].dispersion - avg)*
				 (finfos[i].dispersion - avg);
		Noise = (int)sqrt((double)s/(double)NoiseCounts);
	}

	if (last_index >= NoiseCounts)
	{
		//if (abs(finf->dispersion - finfos[last_index - 1].dispersion) < Noise)
		//	finf->dispersion = finfos[last_index - 1].dispersion;
		// ���� ��������� ��������� ����� �� �������� -> ������������
		if (finfos.count() > 10 + NoiseCounts)
		{
			int avg = 0;
			int e = 0;
			const int n = 6;
			for (i = 0; i < n; i++)
				avg += finfos[last_index - i].dispersion;
			avg /= n;
			for (i = 0; i < n; i++)
				e += (finfos[last_index - i].dispersion - avg)*
					 (finfos[last_index - i].dispersion - avg);
			e = (int)sqrt((double)e/(double)n);
			if (e <= Noise)
			{
#if AF_DEBUG_LOG
				fprintf(info, "AF stoped: e <= Noise\n");
				fflush(info);
#endif
				stop = true;
			}
		}

		int max_disp = maxdispersion();
		//int min_disp = mindispersion();
		if (finf.dispersion > max_disp && finfos.count() > 50 + NoiseCounts)
		{
#if AF_DEBUG_LOG
				fprintf(info, "AF stoped: to many iterations\n");
				fflush(info);
#endif
			stop = true;
		}

		if (finf.focusDir != finfos[last_index - 1].focusDir && abs(finfos[last_index - 1].focusDir) > 0)
			change_count++;
		if (change_count > 2)
			focus_step = 1;
		if (change_count > 4)
		{
#if AF_DEBUG_LOG
				fprintf(info, "AF stoped: change_count > 4\n");
				fflush(info);
#endif
			stop = true;
		}

		if (finf.dispersion >= finfos[last_index - 1].dispersion ||
			abs(finf.dispersion - max_disp) < 3*Noise/2)
		{
			NextFocus = finf.focusDir > 0 ? focus_step : -focus_step;
		}
		else
		{
			NextFocus = finf.focusDir > 0 ? -focus_step : focus_step;
		}
	}
	if (stop)
		NextFocus = 0;
#if AF_DEBUG_LOG
		fprintf(info, "i = %d\ndisp = %d, NextFocus = %d\n", *cookie, finf.dispersion, NextFocus);
		if (info)
			fclose(info);
#endif
}

int GAutoFocus::maxdispersion()
{
	int infs = finfos.count();
	if (infs < 1)
		return 0;
	int ret = finfos[0].dispersion;
	for(int i = 0; i < infs; i++)
	{
		if (ret < finfos[i].dispersion)
			ret = finfos[i].dispersion;
	}
	return ret;
}

int GAutoFocus::mindispersion()
{
	int infs = finfos.count();
	if (infs < 1)
		return 0;
	int ret = finfos[0].dispersion;
	for(int i = 0; i < infs; i++)
	{
		if (ret > finfos[i].dispersion)
			ret = finfos[i].dispersion;
	}
	return ret;
}

int** GAutoFocus::sobel_trans(int** src_image, int w, int h)
{
	static const int Gx[3][3] =
		{
			{-1, 0, 1},
			{-2, 0, 2},
			{-1, 0, 1}
		};
	static const int Gy[3][3] =
		{
			{1, 2, 1},
			{0, 0, 0},
			{-1, -2, -1}
		};
	int x, y;
	// allocate destination array
	int** dst_vals = (int**)malloc(h*sizeof(int*));
	if (!dst_vals)
	{
		return 0;
	}
	for (y = 0; y < h; y++)
	{
		dst_vals[y] = (int*)malloc(w*sizeof(int));
	}
	int i, j;
	int sum_x, sum_y;
	int sum;
	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w; x++)
		{
			if (x == 0 || x == w - 1 || y == 0 || y == h - 1)
				sum = 0;
			else
			{
				sum_x = 0;
				sum_y = 0;
				for (i = 0; i < 3; i++)
				{
					for (j = 0; j < 3; j++)
					{
						sum_x += src_image[y + i - 1][x + j - 1]*Gx[i][j];
						sum_y += src_image[y + i - 1][x + j - 1]*Gy[i][j];
					}
				}
				sum = abs(sum_x) + abs(sum_y);
				if (sum > 255)
					sum = 255;
				else if (sum < 0)
					sum = 0;
			}
			dst_vals[y][x] = 255 - sum;
		}
	}
	return dst_vals;
}

int GAutoFocus::dispersion(int** array, int w, int h)
{
	int i, j;
	int res = 0;
	int avg = average(array, w, h);
	for (i = 1; i < h - 1; i++)
	{
		for (j = 1; j < w - 1; j++)
			res += (array[i][j] - avg)*(array[i][j] - avg);
	}
	res = res/((w - 2)*(h - 2));
	return res;
}

int GAutoFocus::average(int** array, int w, int h)
{
	int i, j;
	int res = 0;
	for (i = 1; i < h - 1; i++)
	{
		for (j = 1; j < w - 1; j++)
			res += array[i][j];
	}
	res = res/((w - 2)*(h - 2));
	return res;
}

#if AF_DEBUG_LOG
QImage array_to_image(int** array, int w, int h)
{
	QImage img(w, h, QImage::Format_RGB32);
	int i, j;
	for (i = 0; i < h; i++)
		for (j = 0; j < w; j++)
			img.setPixel(j, i, qRgb(array[i][j], array[i][j], array[i][j]));
	return img;
}
#endif
