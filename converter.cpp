#include "converter.h"
#include "ui_converter.h"
#include <QString>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QClipboard>

Converter::Converter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Converter)
{
    ui->setupUi(this);
    //connect the button clicked SIGNAL to the slot with the calculate function.
    connect(ui->calculateResult_pushButton, SIGNAL(clicked()), this, SLOT(on_calculateResult_pushButton_clicked()));
    //connect the input type change to the slot with the function to clear the input type
    connect(ui->inputType_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_inputType_comboBox_currentIndexChanged(int)));
    //copy the result to the clipboard signal
    connect(ui->copyResult_pushButton, &QPushButton::clicked, this, &Converter::on_copyResult_pushButton_clicked);
}

Converter::~Converter()
{
    delete ui; //exit process for UI
}

//slot that connects the calculate button
void Converter::on_calculateResult_pushButton_clicked() {
    calculateResult();
}

// Slot that gets called whenever the selected index of the input or output type combo box changes
void Converter::on_inputType_comboBox_currentIndexChanged(int index)
{
    ui->input_lineEdit->clear(); // Clear the input field
    //if binary selected, only let the user input binary (1 or zero)
    //if hex selected, only let the user input hex
    //if decimal selected as input, only allow integers
    // Create validators for different types of input
    QValidator *validator = nullptr;
    QString inputType = ui->inputType_comboBox->currentText();
    // Depending on the input type, add the other two types to the output combo box
    ui->outputType_comboBox->clear();
    if (inputType == "Binary") {
        ui->outputType_comboBox->addItem("Decimal");
        ui->outputType_comboBox->addItem("Hexadecimal");
    } else if (inputType == "Hexadecimal") {
        ui->outputType_comboBox->addItem("Decimal");
        ui->outputType_comboBox->addItem("Binary");
    } else if (inputType == "Decimal") {
        ui->outputType_comboBox->addItem("Binary");
        ui->outputType_comboBox->addItem("Hexadecimal");
    }

    if (inputType == "Binary") {
        // Allow only binary (1 or 0)
        QRegularExpression binaryRegExp("^[01]*$");
        validator = new QRegularExpressionValidator(binaryRegExp, this);
    } else if (inputType == "Hexadecimal") {
        // Allow only hexadecimal characters
        QRegularExpression hexRegExp("^[0-9A-Fa-f]*$");
        validator = new QRegularExpressionValidator(hexRegExp, this);
    } else if (inputType == "Decimal") {
        // Allow only decimal numbers
        validator = new QIntValidator(this);
    }

    // Set the appropriate validator to the input line edit
    ui->input_lineEdit->setValidator(validator);
}

//conversion function.
void Converter::calculateResult()
{
    // Retrieve input and selected types from UI
    QString input = ui->input_lineEdit->text();
    QString inputType = ui->inputType_comboBox->currentText();
    QString outputType = ui->outputType_comboBox->currentText();

    QString result;

    // Try block to handle any potential conversion errors
    try {
        // Branch based on input type
        if (inputType == "Decimal") {
            int decimal = input.toInt();
            // Convert based on output type
            if (outputType == "Binary") {
                result = convertDecimalToBinary(decimal);
            } else if (outputType == "Hexadecimal") {
                result = convertDecimalToHex(decimal);
            }
        } else if (inputType == "Binary") {
            // Convert based on output type
            if (outputType == "Decimal") {
                result = QString::number(convertBinaryToDecimal(input));
            } else if (outputType == "Hexadecimal") {
                result = convertBinaryToHex(input);
            }
        } else if (inputType == "Hexadecimal") {
            // Convert based on output type
            if (outputType == "Decimal") {
                result = QString::number(convertHexToDecimal(input));
            } else if (outputType == "Binary") {
                result = convertHexToBinary(input);
            }
        }
    } catch (...) {
        // Display a warning message if conversion fails
        QMessageBox::warning(this, "Conversion Error", "Invalid input for the selected input type.");
        return;
    }

    // Display the result in the UI
    ui->output_label->setText(result);
}

// Converts a decimal number to a binary string
QString Converter::convertDecimalToBinary(int decimal)
{
    QString binary;
    if(decimal == 0) return "0"; // Special case for 0
    while (decimal > 0) {
        binary.prepend(QString::number(decimal % 2)); // Add the remainder (0 or 1) to the front
        decimal /= 2; // Divide by 2 to get the next bit
    }
    return binary;
}

// Converts a decimal number to a hexadecimal string
QString Converter::convertDecimalToHex(int decimal)
{
    QString hex;
    if(decimal == 0) return "0"; // Special case for 0
    while (decimal > 0) {
        int remainder = decimal % 16;
        // Convert remainder to hexadecimal character
        hex.prepend((remainder < 10) ? QString::number(remainder) : QString(QChar('A' + remainder - 10)));
        decimal /= 16; // Divide by 16 to get the next digit
    }
    return hex;
}

// Converts a binary string to a decimal number
int Converter::convertBinaryToDecimal(QString binary)
{
    int decimal = 0;
    int base = 1; // The base value for the binary number system is 2
    for(int i = binary.length() - 1; i >= 0; i--) {
        if(binary.at(i) == '1') {
            decimal += base; // Add the current base value if the binary digit is 1
        }
        base *= 2; // Increase base value (2^0, 2^1, 2^2, ...)
    }
    return decimal;
}

// Converts a binary string to a hexadecimal string
QString Converter::convertBinaryToHex(QString binary)
{
    // First convert binary to decimal
    int decimal = convertBinaryToDecimal(binary);
    // Then convert decimal to hexadecimal
    return convertDecimalToHex(decimal);
}

// Converts a hexadecimal string to a decimal number
int Converter::convertHexToDecimal(QString hex)
{
    int decimal = 0;
    int base = 1; // The base value for the hexadecimal number system is 16
    for(int i = hex.length() - 1; i >= 0; i--) {
        if(hex.at(i).isDigit()) {
            decimal += (hex.at(i).toLatin1() - '0') * base; // Convert number from character to integer
        } else {
            decimal += (hex.at(i).toUpper().toLatin1() - 'A' + 10) * base; // Convert letter to its decimal value
        }
        base *= 16; // Increase base value
    }
    return decimal;
}

// Converts a hexadecimal string to a binary string
QString Converter::convertHexToBinary(QString hex)
{
    // First convert hex to decimal
    int decimal = convertHexToDecimal(hex);
    // Then convert decimal to binary
    return convertDecimalToBinary(decimal);
}

//copies the result to the clipboard function:
void Converter::on_copyResult_pushButton_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(ui->output_label->text());
}
