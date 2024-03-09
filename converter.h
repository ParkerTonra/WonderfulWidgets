#ifndef CONVERTER_H
#define CONVERTER_H

#include <QMainWindow>

namespace Ui {
class Converter;
}

//class for Converter
class Converter : public QMainWindow
{
    Q_OBJECT

public:
    explicit Converter(QWidget *parent = nullptr); // Constructor
    ~Converter(); // Destructor

private slots:
    void on_calculateResult_pushButton_clicked(); // slot for the calculate button click
    void on_inputType_comboBox_currentIndexChanged(int index); //slot to update UI when a new input is selected
    void on_copyResult_pushButton_clicked();

private:
    Ui::Converter *ui; //pointer to the user interface

    // conversion functions
    QString convertDecimalToBinary(int decimal);
    QString convertDecimalToHex(int decimal);
    int convertBinaryToDecimal(QString binary);
    QString convertBinaryToHex(QString binary);
    int convertHexToDecimal(QString hex);
    QString convertHexToBinary(QString hex);

    void calculateResult();  //function to trigger the calculation based on current UI inputs
};

#endif // CONVERTER_H
