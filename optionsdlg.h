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

#ifndef _optionsdlg_h
#define _optionsdlg_h

#include <QDialog>

class QSpinBox;
class QComboBox;

class GOptionsDlg: public QDialog
{
public:
	GOptionsDlg(QWidget* parent);
	void setOptions(int buff_sz, int afmode);
	int bufferSize();
	int afMode();
private:
	QSpinBox* BufferBox;
	QComboBox* AFModeBox;
};

#endif // _optionsdlg_h
