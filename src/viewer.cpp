#include "viewer.hpp"
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkActor.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkUnstructuredGrid.h>

Viewer::Viewer() {


}

Viewer::~Viewer() {


}

void Viewer::view(vtkSmartPointer<vtkUnstructuredGrid> grid) {
    auto renderer = vtkSmartPointer<vtkRenderer>::New();

    auto window = vtkSmartPointer<vtkRenderWindow>::New();
    window->AddRenderer(renderer);
    window->SetSize(1080, 720);

    auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(window);

    renderer->SetBackground(0.2, 0.2, 0.2);
    renderer->UseHiddenLineRemovalOn();

    auto mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    mapper->SetInputData(grid);
    mapper->ScalarVisibilityOff();

    auto backProp = vtkSmartPointer<vtkProperty>::New();
    backProp->SetDiffuseColor(0.95, 0.95, 0.95);
    backProp->SetSpecular(0.6);
    backProp->SetSpecularPower(30);

    auto actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->SetBackfaceProperty(backProp);
    actor->GetProperty()->EdgeVisibilityOn();
    actor->GetProperty()->SetDiffuseColor(1.0, 0.1, 0.1);
    actor->GetProperty()->SetSpecular(0.3);
    actor->GetProperty()->SetSpecularPower(30);

    renderer->AddActor(actor);
    renderer->GetActiveCamera()->Azimuth(45);
    renderer->GetActiveCamera()->Elevation(45);
    renderer->ResetCamera();
    
    window->Render();
    interactor->Start();
}

