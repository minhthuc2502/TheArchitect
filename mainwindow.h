#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <windowGeneratedCode.h>

class mainWindow : public QWidget
{
    Q_OBJECT
private:
    QLineEdit* classname;
    QLineEdit* classParent;
    QCheckBox* avoidDuplicateHeader;
    QCheckBox* constructorDefault;
    QCheckBox* destructorDefault;
    QGroupBox* descriptionclass;
    QLineEdit* author;
    QDateEdit* date;
    QTextEdit* description;
    QPushButton* generateButton;
    QPushButton* exitButton;
public:
    mainWindow();
    ~mainWindow() {}
    QString generateCodeHPP();
    QString generateCodeCPP();
public slots:
    void generateCodeSlot();
    void updateCheckBoxText(QString);
};

#endif // MAINWINDOW_H
