#include <mainwindow.h>
mainWindow::mainWindow() : QWidget() {
    // set title for window
    setWindowTitle("The architect");
    QVBoxLayout *mainWindowLayout = new QVBoxLayout();
    /* box information class */
    QGroupBox *informationClass = new QGroupBox("Information class");

    QGridLayout *infoClassLayout = new QGridLayout();
    QLabel *classNameLabel = new QLabel("Class name:");
    classname = new QLineEdit();
    /*
     * Determize regrex for validator (can using inputMask() instead of validator)
     * ^ start must be alphabet [A-Za-z]
     * $ end must be alphabet [A-Za-z]
     * + one or more occurrence [A-Za-z]
    */
    QRegExp rx("^[A-Za-z]+$");
    QValidator *validator = new QRegExpValidator(rx);
    classname->setValidator(validator);
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
    avoidDuplicateHeader->setCursor(Qt::PointingHandCursor);
    constructorDefault = new QCheckBox("Create default constructor");
    constructorDefault->setCursor(Qt::PointingHandCursor);
    destructorDefault = new QCheckBox("Create default destructor");
    destructorDefault->setCursor(Qt::PointingHandCursor);

    // add widget to layout option
    optionClassLayout->addWidget(avoidDuplicateHeader, 0, 0);
    optionClassLayout->addWidget(constructorDefault, 1, 0);
    optionClassLayout->addWidget(destructorDefault, 2, 0);

    optionClass->setLayout(optionClassLayout);

    /* box description class */
    descriptionclass = new QGroupBox("Add description for source code");
    descriptionclass->setCheckable(true);
    descriptionclass->setCursor(Qt::PointingHandCursor);
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
    description->setPlaceholderText("write some description for this class");

    descriptionClassLayout->addWidget(authorLabel, 0, 0);
    descriptionClassLayout->addWidget(author, 0, 1);
    descriptionClassLayout->addWidget(dateLabel, 1, 0);
    descriptionClassLayout->addWidget(date, 1, 1);
    descriptionClassLayout->addWidget(descLabel, 2, 0, 1, 1, Qt::AlignTop);
    descriptionClassLayout->addWidget(description, 2, 1);

    descriptionclass->setLayout(descriptionClassLayout);

    /* Set buttons of window*/
    generateButton = new QPushButton("Generate");
    generateButton->setCursor(Qt::PointingHandCursor);
    exitButton = new QPushButton("Exit");
    exitButton->setCursor(Qt::PointingHandCursor);
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
    connect(classname, SIGNAL(textChanged(QString)), this, SLOT(updateCheckBoxText(QString)));
}

void mainWindow::generateCodeSlot() {
    if (classname->text().isEmpty()) {
        QMessageBox::warning(this, "warning", "You have to fill the name of class");
        return;
    }
    QString sourceHPP = generateCodeHPP();
    QString sourceCPP = generateCodeCPP();
    windowGenerateCode* m_windowGenerate = new windowGenerateCode();
    m_windowGenerate->resize(600, 700);
    if (sourceCPP != NULL && sourceHPP != NULL) {
        m_windowGenerate->fillCodeInWindow(sourceHPP, sourceCPP);
    }
}

QString mainWindow::generateCodeHPP() {
    QString context = "";
    context += "class " + classname->text();
    if (!classParent->text().isEmpty()) {
        context += " : public " + classParent->text();
    }
    context +=  " {\npublic:\n";
    if (constructorDefault->isChecked()) {
        context += "\t" + classname->text() + "();\n";
    }
    if (destructorDefault->isChecked()) {
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
                + "\n@brief: " + description->toPlainText() + "\n*/\n\n" + context;
    }
    return context;
}

QString mainWindow::generateCodeCPP() {
    QString context = "#include <" + classname->text() + ".h>\n";
    if (constructorDefault->isChecked()) {
        context += "\n" + classname->text() + "::" + classname->text() + "()";
        context += (!classParent->text().isEmpty()) ? (" : " + classParent->text() + "()") : ("");
        context += " {\n}\n";
    }
    if (destructorDefault->isChecked()) {
        context += "\n" + classname->text() + "::~" + classname->text() + "()";
        context += (!classParent->text().isEmpty()) ? (" : ~" + classParent->text() + "()") : ("");
        context += " {\n}\n";
    }
    if (descriptionclass->isChecked()) {
        context = "/*\n@author: " + author->text()
                + "\n@date: " + date->text()
                + "\n@brief: " + description->toPlainText() + "\n*/\n\n" + context;
    }
    return context;
}
void mainWindow::updateCheckBoxText(QString text) {
    avoidDuplicateHeader->setText("Avoid duplicating the Header \"HEADER_" + text.toUpper() + "\"");
    return;
}
