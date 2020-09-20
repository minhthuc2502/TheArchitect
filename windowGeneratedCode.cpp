#include <windowGeneratedCode.h>

windowGenerateCode::windowGenerateCode() : QWidget() {
    // set title of window
    setWindowTitle("Generated Source Code");
    QVBoxLayout *codewindowLayout = new QVBoxLayout();
    generatedCode = new QTextEdit();
    generatedCode->setFont(QFont("Courrier", 10));
    exitButton = new QPushButton("Exit");
    exitButton->setCursor(Qt::PointingHandCursor);
    // add widgets to layout
    codewindowLayout->addWidget(generatedCode);
    codewindowLayout->addWidget(exitButton);

    // set layout
    setLayout(codewindowLayout);
    // add connection
    connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));
}

void windowGenerateCode::fillCodeInWindow(QString context) {
    generatedCode->setPlainText(context);
    show();
}
