#include "ct.h"
#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkDICOMImageReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkTextProperty.h>
#include <vtkTextMapper.h>
#include <vtkCommand.h>
#include <vtkImageMapper.h>
#include "ReadDICOMSeries.h"
#include <QFileDialog.h>
#include <QDockWidget>
#include <QListWidget>
#include <QDockWidget>
#include <QStatusBar>
#include <QLabel>
#include <QDebug>
#include "ui_ct.h"

#pragma execution_character_set("utf-8")//显示中文

ct::ct(QWidget*parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setWindowTitle("肺部三维重建");
	ui.statusBar->setSizeGripEnabled(false);//去掉状态栏右下角的三角

											////浮动窗口
	QDockWidget *dockList = new QDockWidget(this);
	addDockWidget(Qt::LeftDockWidgetArea, dockList);
	QListWidget *listWidget = new QListWidget(this);
	dockList->setWidget(listWidget);

	////状态栏
	//QStatusBar *sBar = statusBar();
	//QLabel *label = new QLabel(this);
	//sBar->addWidget(label);
	//label->setText("大是大非 "+QString::number(a)); //imageViewer_1->GetSlice()
}

void ct::on_actionOpen_triggered()
{
	//读取文件夹目录
	QString fileName = QFileDialog::getExistingDirectory(this, "请选择文件夹","/");
	if (fileName.isEmpty())
	{
		return;
	}

	QByteArray ba = fileName.toLocal8Bit();
	const char *fileName_str = ba.data();// 支持带中文路径的读取

	std::string folder = fileName.toStdString();//打开文件
	
	vtkSmartPointer<vtkDICOMImageReader> reader =
		vtkSmartPointer<vtkDICOMImageReader>::New();//创建读取图片的对象
	reader->SetDirectoryName(folder.c_str());//获取该文件夹下的图片
	reader->Update();
	vtkSmartPointer<vtkImageViewer2> imageViewer_1 = vtkSmartPointer<vtkImageViewer2>::New();
	vtkSmartPointer<vtkImageViewer2> imageViewer_2 = vtkSmartPointer<vtkImageViewer2>::New();
	vtkSmartPointer<vtkImageViewer2> imageViewer_3 = vtkSmartPointer<vtkImageViewer2>::New();


	imageViewer_1->SetInputConnection(reader->GetOutputPort());//将读取的图像显示出来
	imageViewer_1->SetRenderWindow(ui.qvtk_1->GetRenderWindow());
	imageViewer_1->SetSliceOrientationToXY();
	imageViewer_1->SetSlice((int)imageViewer_1->GetSliceMax()*0.5);//将图片定位到中间图片

	imageViewer_2->SetInputConnection(reader->GetOutputPort());//将读取的图像显示出来
	imageViewer_2->SetRenderWindow(ui.qvtk_2->GetRenderWindow());
	imageViewer_2->SetSliceOrientationToYZ();
	imageViewer_2->SetSlice((int)imageViewer_2->GetSliceMax()*0.5);//将图片定位到中间图片

	imageViewer_3->SetInputConnection(reader->GetOutputPort());//将读取的图像显示出来
	imageViewer_3->SetRenderWindow(ui.qvtk_3->GetRenderWindow());
	imageViewer_3->SetSliceOrientationToXZ();
	imageViewer_3->SetSlice((int)imageViewer_3->GetSliceMax()*0.5);//将图片定位到中间图片


	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor_1 = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor_2 = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor_3 = vtkSmartPointer<vtkRenderWindowInteractor>::New();

	vtkSmartPointer<myVtkInteractorStyleImage> myInteractorStyle_1 = vtkSmartPointer<myVtkInteractorStyleImage>::New();
	vtkSmartPointer<myVtkInteractorStyleImage> myInteractorStyle_2 = vtkSmartPointer<myVtkInteractorStyleImage>::New();
	vtkSmartPointer<myVtkInteractorStyleImage> myInteractorStyle_3 = vtkSmartPointer<myVtkInteractorStyleImage>::New();

	myInteractorStyle_1->SetImageViewer(imageViewer_1);
	myInteractorStyle_2->SetImageViewer(imageViewer_2);
	myInteractorStyle_3->SetImageViewer(imageViewer_3);

	imageViewer_1->SetupInteractor(renderWindowInteractor_1);
	imageViewer_2->SetupInteractor(renderWindowInteractor_2);
	imageViewer_3->SetupInteractor(renderWindowInteractor_3);

	renderWindowInteractor_1->SetInteractorStyle(myInteractorStyle_1);
	renderWindowInteractor_2->SetInteractorStyle(myInteractorStyle_2);
	renderWindowInteractor_3->SetInteractorStyle(myInteractorStyle_3);

	imageViewer_1->GetRenderer()->SetBackground(0.0, 0.0, 0.0);
	imageViewer_1->Render();
	imageViewer_1->GetRenderer()->ResetCamera();
	imageViewer_1->Render();

	imageViewer_2->GetRenderer()->SetBackground(0.0, 0.0, 0.0);
	imageViewer_2->Render();
	imageViewer_2->GetRenderer()->ResetCamera();
	imageViewer_2->Render();

	imageViewer_3->GetRenderer()->SetBackground(0.0, 0.0, 0.0);
	imageViewer_3->Render();
	imageViewer_3->GetRenderer()->ResetCamera();
	imageViewer_3->Render();

	renderWindowInteractor_1->Initialize();
	renderWindowInteractor_2->Initialize();
	renderWindowInteractor_3->Initialize();
	renderWindowInteractor_1->Start();
	renderWindowInteractor_2->Start();
	renderWindowInteractor_3->Start();
}

void ct::on_action3D_triggered()
{
	
}
void myVtkInteractorStyleImage::SetImageViewer(vtkImageViewer2* imageViewer) {//定位图片位置
	_ImageViewer = imageViewer;
	_MinSlice = imageViewer->GetSliceMin();
	_MaxSlice = imageViewer->GetSliceMax();
	_NowSlice = imageViewer->GetSlice();
	_Slice = _NowSlice;
}

void myVtkInteractorStyleImage::MoveSliceForward() {
	if (_Slice < _MaxSlice) {
		_Slice += 1;
		_ImageViewer->SetSlice(_Slice);
		_ImageViewer->Render();
	}
}

void myVtkInteractorStyleImage::MoveSliceBackward() {
	if (_Slice > _MinSlice) {
		_Slice -= 1;
		_ImageViewer->SetSlice(_Slice);
		_ImageViewer->Render();
	}
}

void myVtkInteractorStyleImage::OnKeyDown() {
	std::string key = this->GetInteractor()->GetKeySym();
	if (key.compare("Up") == 0) {
		MoveSliceForward();
	}
	else if (key.compare("Down") == 0) {
		MoveSliceBackward();
	}
	vtkInteractorStyleImage::OnKeyDown();
}

void myVtkInteractorStyleImage::OnMouseWheelForward() {
	MoveSliceForward();
}

void myVtkInteractorStyleImage::OnMouseWheelBackward() {
	if (_Slice > _MinSlice) {
		MoveSliceBackward();
	}
}

void ct::on_actionQuit_triggered()
{
	qApp->quit();
}