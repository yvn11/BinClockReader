#include "binaryclockreader.h"

BinaryClockReader::BinaryClockReader(int width, int height, QWidget *parent = 0)
	:QDialog(parent),
	field(x(), y(), width, height),
	view(&field, this)
{
	field.setBackgroundBrush(Qt::black);
	view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view.setAutoFillBackground(false);
	createBinaryMap();        
	initTime();
	QPalette pal;
	/* Show digital time */
	lblDigitalTime = new QLabel(tr("00:00:00"), this);
        lblDigitalTime->setObjectName(tr("lblDigitalTime"));
        lblDigitalTime->setGeometry(QRect(60, 40, 120, 40));
        lblDigitalTime->setTextFormat(Qt::AutoText);
        lblDigitalTime->setAlignment(Qt::AlignCenter);
	pal.setColor(QPalette::WindowText, Qt::red);
	lblDigitalTime->setPalette(pal);
	connect(this, SIGNAL(digitTimeChanged()), this, SLOT(updateDigitTime()));
	/* leave button */
	leave = new QPushButton(tr("Leave"), this);
	pal = leave->palette();
	pal.setColor(QPalette::ButtonText, Qt::red);
	leave->setPalette(pal);
	leave->setEnabled(true);
	leave->setGeometry(QRect(90, 90, 70, 20));
	leave->setFlat(true);
	connect(leave, SIGNAL(clicked()), this, SLOT(close()));

	setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
        QSize size(width, height);
	this->resize(size);
        this->move(x(), y());
	Q_UNUSED(parent);
}

void BinaryClockReader::updateDigitTime()
{
	QString newTime;
	newTime = QString("%1").arg(hour0) + QString("%1").arg(hour1) + ":"
		+ QString("%1").arg(minute0) + QString("%1").arg(minute1) + ":"
		+ QString("%1").arg(second0) + QString("%1").arg(second1);

	lblDigitalTime->setText(newTime);
}

bool BinaryClockReader::isSave()
{
#define MAX_HOUR	24
#define MAX_MINUTE	60
#define MAX_SECOND	60
#define MIN_ALL		0
#define MAX_ALL		9
	if (hour0 > MAX_HOUR/10 or hour0 < MIN_ALL or 
		(hour0 >= MAX_HOUR/10 and hour1 > MAX_HOUR%10))
		return false;
	if (hour1 > MAX_ALL or hour1 < MIN_ALL or
		(hour0 >= MAX_HOUR/10 and hour1 > MAX_HOUR%10))
		return false;
	if (minute0 >= MAX_MINUTE/10 or minute0 < MIN_ALL)
		return false;
	if (minute1 > MAX_ALL or minute1 < MIN_ALL)
		return false;
	if (second0 >= MAX_SECOND/10 or second0 < MIN_ALL)
		return false;
	if (second1 > MAX_ALL or second1 < MIN_ALL)
		return false;
	return true;
}

int BinaryClockReader::setSaveValue(int &unit, int value) {
	unit += value;
	int ret = isSave();
	unit = ret ? unit : (unit-value);
	return ret;
}

int BinaryClockReader::setDigitalTime(QString unit, int value)
{
	if (unit == "hour0") {
		return setSaveValue(hour0, value);
	} else if (unit == "hour1") {
		return setSaveValue(hour1, value);
	} else if (unit == "minute0") {
		return setSaveValue(minute0, value);
	} else if (unit == "minute1") {
		return setSaveValue(minute1, value);
	} else if (unit == "second0") {
		return setSaveValue(second0, value);
	} else if (unit == "second1") {
		return setSaveValue(second1, value);
	}
	return 0;
}

void BinaryClockReader::calcTime()
{
	  BinaryDigit *pressedLabel = qobject_cast<BinaryDigit *>(sender());
	  QString objName = pressedLabel->objectName();
	  bool ok;
	  int value = objName.right(2).left(1).toInt(&ok, 10);
	  QString pos = objName.right(1);

	  value = pressedLabel->isChecked() ? value : -value;
	  if (objName.contains("Hour")) {
		if (setDigitalTime("hour"+pos, value))
			emit digitTimeChanged();
		else pressedLabel->resetMode(); 
	  } else if (objName.contains("Minute")) {
		if (setDigitalTime("minute"+pos, value))
			emit digitTimeChanged();
		else pressedLabel->resetMode();
	  } else {
		if (setDigitalTime("second"+pos, value))
			emit digitTimeChanged();
		else pressedLabel->resetMode();
	  }
}

void BinaryClockReader::setupConnection(BinaryDigit *obj)
{
	connect(obj, SIGNAL(checked()), this, SLOT(calcTime()));
	connect(obj, SIGNAL(normal()), this, SLOT(calcTime()));
}

void BinaryClockReader::createBinaryMap()
{
     	/* the 1st column of Hour unit */
        lblHour10 = new BinaryDigit(tr("lblHour10"), QRect(0, 280, 40, 40), this);
	setupConnection(lblHour10);
        lblHour20 = new BinaryDigit(tr("lblHour20"), QRect(0, 240, 40, 40), this);
	setupConnection(lblHour20);
     	/* the 2nd column of Hour unit */
        lblHour81 = new BinaryDigit(tr("lblHour81"), QRect(40, 160, 40, 40), this);
	setupConnection(lblHour81);
        lblHour41 = new BinaryDigit(tr("lblHour41"), QRect(40, 200, 40, 40), this);
	setupConnection(lblHour41);
        lblHour21 = new BinaryDigit(tr("lblHour21"), QRect(40, 240, 40, 40), this);
	setupConnection(lblHour21);
        lblHour11 = new BinaryDigit(tr("lblHour11"), QRect(40, 280, 40, 40), this);
	setupConnection(lblHour11);
        /* the 1st column of Minute unit */
        lblMinute40 = new BinaryDigit(tr("lblMinute40"), QRect(80, 200, 40, 40), this);
	setupConnection(lblMinute40);
        lblMinute20 = new BinaryDigit(tr("lblMinute20"), QRect(80, 240, 40, 40), this);
	setupConnection(lblMinute20);
        lblMinute10 = new BinaryDigit(tr("lblMinute10"), QRect(80, 280, 40, 40), this);
	setupConnection(lblMinute10);
        /* the 2nd column of Minute unit */
        lblMinute81 = new BinaryDigit(tr("lblMinute81"), QRect(120, 160, 40, 40), this);
	setupConnection(lblMinute81);
        lblMinute41 = new BinaryDigit(tr("lblMinute41"), QRect(120, 200, 40, 40), this);
	setupConnection(lblMinute41);
        lblMinute21 = new BinaryDigit(tr("lblMinute21"), QRect(120, 240, 40, 40), this);
	setupConnection(lblMinute21);
        lblMinute11 = new BinaryDigit(tr("lblMinute11"), QRect(120, 280, 40, 40), this);
	setupConnection(lblMinute11);
        /* the 1st column of Second unit */
        lblSecond40 = new BinaryDigit(tr("lblSecond40"), QRect(160, 200, 40, 40), this);
	setupConnection(lblSecond40);
        lblSecond20 = new BinaryDigit(tr("lblSecond20"), QRect(160, 240, 40, 40), this);
	setupConnection(lblSecond20);
        lblSecond10 = new BinaryDigit(tr("lblSecond10"), QRect(160, 280, 40, 40), this);
	setupConnection(lblSecond10);
        /* the 2nd column of Second unit */
        lblSecond81 = new BinaryDigit(tr("lblSecond81"), QRect(200, 160, 40, 40), this);
	setupConnection(lblSecond81);
        lblSecond41 = new BinaryDigit(tr("lblSecond41"), QRect(200, 200, 40, 40), this);
	setupConnection(lblSecond41);
        lblSecond21 = new BinaryDigit(tr("lblSecond21"), QRect(200, 240, 40, 40), this);
	setupConnection(lblSecond21);
        lblSecond11 = new BinaryDigit(tr("lblSecond11"), QRect(200, 280, 40, 40), this);
	setupConnection(lblSecond11);
}
