//=========================================================
//  LOS
//  Libre Octave Studio
//    $Id: tempolabel.cpp,v 1.1.1.1 2003/10/27 18:54:29 wschweer Exp $
//  (C) Copyright 1999 Werner Schweer (ws@seh.de)
//=========================================================

#include <QApplication>
#include <QStyle>

#include "tempolabel.h"

//---------------------------------------------------------
//   TempoLabel
//---------------------------------------------------------

TempoLabel::TempoLabel(QWidget* parent, const char* name)
: QLabel(parent)
{
	setObjectName(name);
	setFrameStyle(WinPanel | Sunken);
	setLineWidth(2);
	setMidLineWidth(3);
	_value = 1.0;
	setValue(0.0);
	setIndent(3);
	setMinimumSize(sizeHint());
}

//---------------------------------------------------------
//   setVal
//---------------------------------------------------------

void TempoLabel::setValue(int val)
{
	//qDebug("TempoLabel::setValue: %d", val);
	setValue(double(val / 1000.0));
}

void TempoLabel::setValue(double val)
{
	//qDebug("TempoLabel::setValue: %f", val);
	if (val == _value)
		return;
	_value = val;
	QString s = QString("%1").arg(val, 3, 'f', 2);
	setText(s);
}

//---------------------------------------------------------
//   sizeHint
//---------------------------------------------------------

QSize TempoLabel::sizeHint() const
{
	QFontMetrics fm(font());
	int fw = 4;
	int h = fm.height() + fw * 2;
	int w = 6 + fm.width(QString("000.00")) + fw * 2; // 6=indent
	return QSize(w, h).expandedTo(QApplication::globalStrut());
}

//---------------------------------------------------------
//   TempoSpinBox
//---------------------------------------------------------

TempoEdit::TempoEdit(QWidget* parent)
: QDoubleSpinBox(parent)
{
	curVal = -1.0;
	setSingleStep(1.0);
	setRange(30.0, 250.0);
	connect(this, SIGNAL(valueChanged(double)), SLOT(newValue(double)));
}

//---------------------------------------------------------
//   sizeHint
//---------------------------------------------------------

QSize TempoEdit::sizeHint() const
{
	QFontMetrics fm(font());
	int fw = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
	int h = fm.height() + fw * 2;
	int w = 2 + fm.width(QString("000.00")) + fw * 4 + 30;
	return QSize(w, h).expandedTo(QApplication::globalStrut());
}

//---------------------------------------------------------
//   tempoChanged
//---------------------------------------------------------

void TempoEdit::newValue(double val)
{
	if (val != curVal)
	{
		curVal = val;
		emit tempoChanged(curVal);
	}
}

//---------------------------------------------------------
//   setValue
//---------------------------------------------------------

void TempoEdit::setValue(double val)
{
	if (val != curVal)
	{
		curVal = val;
		blockSignals(true);
		QDoubleSpinBox::setValue(val);
		blockSignals(false);
	}
}


//---------------------------------------------------------
//   tempo
//---------------------------------------------------------

//int TempoEdit::tempo() const
//      {
//        return lrint(60000000.0/value());
//      }


