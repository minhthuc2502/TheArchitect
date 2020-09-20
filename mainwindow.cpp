#include <mainwindow.h>
#include <QDebug>
mainWindow::mainWindow() : QWidget() {
    // set title for window
    setWindowTitle("The architect");
    QVBoxLayout *mainWindowLayout = new QVBoxLayout();
    /* box information class */
    QGroupBox *informationClass = new QGroupBox("Information class");

    QGridLayout *infoClassLayout = new QGridLayout();
    QLabel *classNameLabel = new QLabel("Class name:");
    classname = new QLineEdit();
    infoClassLayout->addWidget(classNameLabel, 0, 0);
    infoClassLayout->addWidget(classname, 0, 1);

    QLabel *classParentLabel = new QLabel("Class parent:");
    classParent = new QLineEdit();
    infoClassLayout->addWidget(classParentLabel, 1, 0);
    infoClassLayout->addWidget(classParent, 1, 1);

    informationClass->setLayout(infoClassLayout);

    /* Box option */
    QGroupBox *optionClass = new QGroupBox("Options");
    QGridLayout *optionClassLayout = new QGridLayout();

    // widget in box option
    avoidDuplicateHeader = new QCheckBox("Avoid duplicating the Header");
    constructorDefault = new QCheckBox("Create default constructor");
    destructorDefault = new QCheckBox("Create default destructor");

    // add widget to layout option
    optionClassLayout->addWidget(avoidDuplicateHeader, 0, 0);
    optionClassLayout->addWidget(constructorDefault, 1, 0);
    optionClassLayout->addWidget(destructorDefault, 2, 0);

    optionClass->setLayout(optionClassLayout);

    /* box description class */
    descriptionclass = new QGroupBox("Add description for source code");
    descriptionclass->setCheckable(true);
    QGridLayout *descriptionClassLayout = new QGridLayout();

    // Author
    QLabel *authorLabel = new QLabel("Author:");
    author = new QLineEdit();
    // Date
    QLabel *dateLabel = new QLabel("Date:");
    date = new QDateEdit();
    // Description
    QLabel *descLabel = new QLabel("Description:");
    description = new QTextEdit();

    descriptionClassLayout->addWidget(authorLabel, 0, 0);
    descriptionClassLayout->addWidget(author, 0, 1);
    descriptionClassLayout->addWidget(dateLabel, 1, 0);
    descriptionClassLayout->addWidget(date, 1, 1);
    descriptionClassLayout->addWidget(descLabel, 2, 0, 1, 1, Qt::AlignTop);
    descriptionClassLayout->addWidget(description, 2, 1);

    descriptionclass->setLayout(descriptionClassLayout);

    /* Set buttons of window*/
    generateButton = new QPushButton("Generate");
    exitButton = new QPushButton("Exit");
    QGridLayout *buttonLayout = new QGridLayout();
    buttonLayout->addWidget(generateButton, 0, 0, 0, 5, Qt::AlignRight);
    buttonLayout->addWidget(exitButton, 0, 6, 0, 1, Qt::AlignRight);

    // add widget box to main window's layout
    mainWindowLayout->addWidget(informationClass);
    mainWindowLayout->addWidget(optionClass);
    mainWindowLayout->addWidget(descriptionclass);
    mainWindowLayout->addLayout(buttonLayout, 0);
    setLayout(mainWindowLayout);

    // add connection
    connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(generateButton, SIGNAL(clicked()), this, SLOT(generateCodeSlot()));
}

void mainWindow::generateCodeSlot() {
    QString context = generateCode();
    qDebug() << context;
    windowGenerateCode* m_windowGenerate = new windowGenerateCode();
    m_windowGenerate->resize(600, 700);
    if (context != NULL) {
        m_windowGenerate->fillCodeInWindow(context);
    }

}

QString mainWindow::generateCode() {
    QString context = "";
    if (classname->text().isEmpty()) {
        QMessageBox::warning(this, "warning", "You have to fill the name of class");
        return NULL;
    }
    context += "class " + classname->text();
    if (!classParent->text().isEmpty()) {
        context += " : public " + classParent->text();
    }
    context +=  " {\npublic:\n";
    if (constructorDefault->isChecked()) {
        context += "\t" + classname->text() + "();\n";
    }
    if (constructorDefault->isChecked()) {
        context += "\t~" + classname->text() + "();\n";
    }
    context += "\nprotect:\n";
    context += "\nprrivate:\n};\n\n";
    if (avoidDuplicateHeader->isChecked()) {
        context = "#ifndef HEADER_" + classname->text().toUpper() + "\n"
                + "#define HEADER_" + classname->text().toUpper() + "\n\n" + context;
        context += "#endif   //HEADER_" + classname->text().toUpper();
    }
    if (descriptionclass->isChecked()) {
        context = "/*\n@author: " + author->text()
                + "\n@date: " + date->text()
                + "\n@brief: " + description->toPlainText() + "\n*/\n" + context;
    }
    return context;
}
