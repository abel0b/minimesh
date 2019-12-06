#pragma once

#include <vtkDataSet.hpp>
#include <vtkSmartPointer.hpp>

class Viewer
{
public:
  Viewer(void);
  ~Viewer(void);

  void view(vtkSmartPointer<vtkDataSet> data);
};
