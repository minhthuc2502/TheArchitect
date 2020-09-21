#ifndef WINDOWGENERATEDCODE_H
#define WINDOWGENERATEDCODE_H
#include <QtWidgets>
class windowGenerateCode : public QWidget {
    Q_OBJECT
private:
    QTextEdit* CodeHpp;
    QTextEdit* CodeCpp;
    QPushButton* exitButton;
    QPushButton* saveCppButton;
    QPushButton* saveHppButton;
    QString sourceHPP;
    QString sourceCPP;
public:
    windowGenerateCode();
    void fillCodeInWindow(QString, QString); // show code to this window
public slots:
    void writeToSourceFile();  // save source file
    void writeToHeaderFile();  // save header file
};

#endif // WINDOWGENERATEDCODE_H
