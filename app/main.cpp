/**
 * RogueByte Forensic Recovery Pro (RFRP)
 * Native Qt 6 GUI Entry Point
 * Developer: SidoDev-Dz | Brand: RogueByte
 */

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QStyleFactory>
#include "ui/MainWindow.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("RogueByte Forensic Recovery Pro");
    app.setOrganizationName("RogueByte");
    app.setApplicationVersion("2.4.0");

    // Default to dark fusion theme
    app.setStyle(QStyleFactory::create("Fusion"));

    // Check system locale for Arabic RTL auto-orientation
    QLocale sysLocale = QLocale::system();
    if (sysLocale.language() == QLocale::Arabic) {
        app.setLayoutDirection(Qt::RightToLeft);
    }

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
