#include <vtkSmartPointer.h>
#include <vtkObjectFactory.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkImageViewer2.h>
#include <vtkDICOMImageReader.h>
#include <vtkInteractorStyleImage.h>
#include <vtkActor2D.h>
#include <vtkTextProperty.h>
#include <vtkTextMapper.h>
#include <sstream>

class myVtkInteractorStyleImage : public vtkInteractorStyleImage
{
public:
	static myVtkInteractorStyleImage* New();
	vtkTypeMacro(myVtkInteractorStyleImage, vtkInteractorStyleImage);

protected:
	vtkImageViewer2* _ImageViewer;
	vtkTextMapper* _StatusMapper;
	int _Slice;
	int _MinSlice;
	int _MaxSlice;
	int _NowSlice;

public:
	void SetImageViewer(vtkImageViewer2* imageViewer);
	//void SetStatusMapper(vtkTextMapper* statusMapper);

protected:
	void MoveSliceForward();
	void MoveSliceBackward();
	virtual void OnKeyDown();
	virtual void OnMouseWheelForward();
	virtual void OnMouseWheelBackward();
};

vtkStandardNewMacro(myVtkInteractorStyleImage);