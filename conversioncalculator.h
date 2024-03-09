#ifndef CONVERSIONCALCULATOR_H
#define CONVERSIONCALCULATOR_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class ConversionCalculator; }
QT_END_NAMESPACE

class ConversionCalculator : public QMainWindow
{
    Q_OBJECT
public:
    ConversionCalculator(QWidget *parent = nullptr);
    ~ConversionCalculator();

signals:

private:
    Ui::ConversionCalculator *ui;

};



#endif // CONVERSIONCALCULATOR_H
