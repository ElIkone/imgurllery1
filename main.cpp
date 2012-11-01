/*******************************************************************************
**                                                                            **
**                                                                            **
**                                 By Ikone                                   **
**                            %YEAR%                                          **
**                                                                            **
**                                                                            **
**                                                                            **
**                                                                            **
*******************************************************************************/
#include <QtGui/QApplication>
#include "wmain.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WMain w;
    w.show();

    return a.exec();
}
