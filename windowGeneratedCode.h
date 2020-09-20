#ifndef WINDOWGENERATEDCODE_H
#define WINDOWGENERATEDCODE_H
#include <QtWidgets>
class windowGenerateCode : public QWidget {
    Q_OBJECT
private:
    QTextEdit* generatedCode;
    QPushButton* exitButton;
public:
    windowGenerateCode();
    void fillCodeInWindow(QString context);
};

#endif // WINDOWGENERATEDCODE_H
