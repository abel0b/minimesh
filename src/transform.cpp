#include "transform.hpp"
#include <iostream>
#include <vtkSmartPointer.h>
#include <vtkTransform.h>
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkTransformFilter.h>
#include <vtkXMLUnstructuredGridWriter.h>

void Merge::execute() {
    std::cout << "merge" << std::endl;
}

void Translate::execute() {
    auto translation = vtkSmartPointer<vtkTransform>::New();
    translation->Translate(this->x, this->y, this->z);

    auto reader = vtkSmartPointer<vtkXMLUnstructuredGridReader>::New();
    reader->SetFileName(this->input.c_str());
    reader->Update();

    auto filter = vtkSmartPointer<vtkTransformFilter>::New();
    filter->SetInputConnection(reader->GetOutputPort());
    filter->SetTransform(translation);
    filter->Update();

    auto writer = vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
    writer->SetFileName(this->output.c_str());
    writer->SetInputConnection(filter->GetOutputPort());
    writer->Write();
}



