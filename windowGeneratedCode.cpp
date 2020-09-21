#include <windowGeneratedCode.h>

windowGenerateCode::windowGenerateCode() : QWidget() {
    // set title of window
    setWindowTitle("Generated Source Code");
    QVBoxLayout *codewindowLayout = new QVBoxLayout();

    QTabWidget *SCodeTab = new QTabWidget();
    CodeHpp = new QTextEdit();
    CodeHpp->setFont(QFont("Courrier", 10));
    CodeCpp = new QTextEdit();
    CodeCpp->setFont(QFont("Courrier", 10));
    SCodeTab->addTab(CodeHpp, "Header");
    SCodeTab->addTab(CodeCpp, "Source Code");

    exitButton = new QPushButton("Exit");
    exitButton->setCursor(Qt::PointingHandCursor);
    saveHppButton = new QPushButton("Save Header file");
    saveHppButton->setCursor(Qt::PointingHandCursor);
    saveCppButton = new QPushButton("Save Source file");
    saveCppButton->setCursor(Qt::PointingHandCursor);
    QHBoxLayout *arrayButton = new QHBoxLayout();
    arrayButton->addWidget(saveHppButton);
    arrayButton->addWidget(saveCppButton);
    arrayButton->addWidget(exitButton);
    // add widgets to layout
    codewindowLayout->addWidget(SCodeTab);
    codewindowLayout->addLayout(arrayButton);

    // set layout
    setLayout(codewindowLayout);
    // add connection
    connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(saveCppButton, SIGNAL(clicked()), this, SLOT(writeToSourceFile()));
    connect(saveHppButton, SIGNAL(clicked()), this, SLOT(writeToHeaderFile()));
}

void windowGenerateCode::fillCodeInWindow(QString sourceHPP, QString sourceCPP) {
    this->sourceCPP = sourceCPP;
    this->sourceHPP = sourceHPP;
    CodeHpp->setPlainText(this->sourceHPP);
    CodeCpp->setPlainText(this->sourceCPP);
    show();
}

void windowGenerateCode::writeToHeaderFile() {
    QString path = QFileDialog::getSaveFileName(this, "Save file", QString(), "Header (*.h *.hpp)");
    QFile file(path);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        return;

    QTextStream Fileout(&file); // using QTextStream to interact with files
    Fileout << sourceHPP;
}

void windowGenerateCode::writeToSourceFile() {
    QString path = QFileDialog::getSaveFileName(this, "Save file", QString(), "Source code (*.cpp *.c)");
    QFile file(path);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        return;

    QTextStream Fileout(&file);
    Fileout << sourceCPP;
}
