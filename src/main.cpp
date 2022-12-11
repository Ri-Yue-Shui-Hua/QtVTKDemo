#include "ct.h"
#include <QtWidgets/QApplication>
#include <vtkAutoInit.h> 
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
//VTK_MODULE_INIT(vtkRenderingOpenGL);

#pragma execution_character_set("utf-8")
#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ct w;
	w.show();
	return a.exec();
}
