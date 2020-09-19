#include <mainwindow.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    mainWindow *m_window = new mainWindow();
    m_window->resize(QSize(600, 700));
    m_window->show();
    return app.exec();
}
