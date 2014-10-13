#ifndef BINARYDIGIT_H
#define BINARYDIGIT_H

#include <QPushButton>

#define UNIT_IMG_FILE_NORMAL	":/img/40x40/normalBinary.png"
#define UNIT_IMG_FILE_CHKED	":/img/40x40/checkedBinary.png"

class BinaryDigit : public QPushButton
{
	Q_OBJECT
public:
	BinaryDigit(QString objName, QRect geoRect, QWidget *parent);
	int getMode() { return mode; }
	void setMode(int newMode) { mode = newMode; }
	bool isNormal() { return mode == BinaryDigit::Normal; }
	bool isChecked() { return mode == BinaryDigit::Checked; }
	//void emitResetDigit() { emit resetDigit(); }
	void resetMode();
	enum {
		Normal,
		Checked
	};
signals:
	void checked();
	void normal();
private slots:
	void changeMode();
private:
	int mode; 
};

#endif /* BINARYDIGIT_H */
