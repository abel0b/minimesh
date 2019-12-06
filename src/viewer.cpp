#include "viewer.hpp"
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkActor.h>
#include <vtkDataSetMapper.h>

Viewer::Viewer() {


}

Viewer::~Viewer() {


}

void Viewer::view(vtkSmartPointer<vtkDataSet> data) {
    auto mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    mapper->SetInputData(data);

    auto renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->SetBackground(0.2, 0.2, 0.2);

    auto window = vtkSmartPointer<vtkRenderWindow>::New();
    window->AddRenderer(renderer);
    window->SetSize(1080, 720);

    auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(window);

    interactor->Initialize();

    auto actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    renderer->AddActor(actor);

    window->Render();
    interactor->Start();
}

