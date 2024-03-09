#include "conversioncalculator.h"
#include "ui_conversioncalculator.h"

ConversionCalculator::ConversionCalculator(QWidget *parent)
    : QMainWindow{parent},
    ui(new Ui::ConversionCalculator) //attatch to the UI file
{
    ui->setupUi(this); // This line is crucial
}
