#include "binarydigit.h"

BinaryDigit::BinaryDigit(QString objName, QRect geoRect, QWidget *parent = 0)
	:QPushButton(parent)
{
	setObjectName(objName);
	setIcon(QIcon(UNIT_IMG_FILE_NORMAL));
	setIconSize(QSize(40, 40));
	setGeometry(geoRect);
	setMode(Normal);
	connect(this, SIGNAL(clicked()), this, SLOT(changeMode()));
	Q_UNUSED(parent);
}

void BinaryDigit::changeMode()
{
	if (isNormal()) {
		setMode(BinaryDigit::Checked);
		setIcon(QIcon(UNIT_IMG_FILE_CHKED));
		emit checked();
	} else {
		setMode(BinaryDigit::Normal);
		setIcon(QIcon(UNIT_IMG_FILE_NORMAL));
		emit normal();
	}
}

void BinaryDigit::resetMode()
{
	if (isChecked()) {
		setMode(BinaryDigit::Normal);
		setIcon(QIcon(UNIT_IMG_FILE_NORMAL));
	}
}
