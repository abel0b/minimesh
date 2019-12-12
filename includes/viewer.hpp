#pragma once

#include <vtkDataSet.h>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>

class Viewer
{
public:
    Viewer(void);
    ~Viewer(void);

    void view(vtkSmartPointer<vtkUnstructuredGrid> data);
};
