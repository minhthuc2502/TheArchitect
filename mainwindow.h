#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>

class mainWindow : public QWidget
{
    Q_OBJECT
private:
    QLineEdit* classname;
    QLineEdit* classParent;
    QCheckBox* avoidDuplicateHeader;
    QCheckBox* constructorDefault;
    QCheckBox* destructorDefault;
    QCheckBox* addNote;
    QLineEdit* author;
    QDateEdit* date;
    QTextEdit* description;
    QPushButton* generateButton;
    QPushButton* exitButton;
public:
    mainWindow();
    ~mainWindow() {}
};

#endif // MAINWINDOW_H
