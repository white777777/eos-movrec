/***************************************************************************
 *   Copyright (C) 2008-2009 by ������ �.�.                                *
 *   valexlin@gmail.com                                                    *
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

#ifndef _histogramwnd_h
#define _histogramwnd_h

#include <QWidget>

class GMyLiveThread;

class GHistogramWnd: public QWidget
{
public:
	GHistogramWnd(QWidget* parent, GMyLiveThread* thread);
	~GHistogramWnd();
	void updateHistogram();
protected:
	virtual void paintEvent(QPaintEvent * event);
	virtual void closeEvent(QCloseEvent* event);
private:
	struct YRGB
	{
		int Y;
		int R;
		int G;
		int B;
	};
	struct YRGB* Histogram;
	int HistogramSize;
	int HistogramMax;
	GMyLiveThread* LiveThread;
	QWidget* Owner;
};

#endif // _histogramwnd_h