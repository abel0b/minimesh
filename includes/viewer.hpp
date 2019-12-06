#pragma once

#include <vtkDataSet.h>
#include <vtkSmartPointer.h>

class Viewer
{
public:
    Viewer(void);
    ~Viewer(void);

    void view(vtkSmartPointer<vtkDataSet> data);
};
