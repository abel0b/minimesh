#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <tuple>
#include <regex>
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkUnstructuredGridReader.h>
#include <vtkUnstructuredGrid.h>
#include <vtkSmartPointer.h>
#include <vtkDataSet.h>
#include "options.hpp"
#include "viewer.hpp"

void print_usage()
{
  std::cout << "A VTK-focused unstructured mesh manipulation mini-app\n";
  std::cout << "Usage:\n";
  std::cout << "  minimesh [OPTION...]\n";
  std::cout << "\n";
  std::cout << "  -v, --view Mesh file            View a mesh\n";
  std::cout << "  -t, --transform Transform file  Transform (merge, translate) a mesh\n";
  std::cout << "  -h, --help                      Print help\n";
}

int main(int argc, char * argv []) {
    std::string command;
    std::string file_name;

    if (argc > 1) {
        command = argv[1];
    }

    if ((argc <= 1) || command == "-h" || command == "--help") {
        print_usage();
        return EXIT_SUCCESS;
    }

    if (command == "-v" || command == "--view") {
        if (argc < 3) {
            std::cerr << "Error: missing file\n";
            print_usage();
            return EXIT_FAILURE;
        }
        file_name = argv[2];
        
        std::string ext = file_name.substr(file_name.find_last_of(".") + 1);
        vtkSmartPointer<vtkUnstructuredGrid> grid;
        if (ext == "vtu") {
            auto reader = vtkSmartPointer<vtkXMLUnstructuredGridReader>::New();
            reader->SetFileName(file_name.c_str());
            reader->Update();
            grid = reader->GetOutput();
        }
        else if (ext == "vtk") {
            auto reader = vtkSmartPointer<vtkUnstructuredGridReader>::New();
            reader->SetFileName(file_name.c_str());
            reader->Update();
            grid = reader->GetOutput(); 
        }
        else {
            std::cerr << "Invalid file name" << std::endl;
            return EXIT_FAILURE;
        }
       
        Viewer viewer;
        viewer.view(grid);
    }
    else if (command == "-t" || command == "--transform") {
        if (argc < 3) {
            std::cerr << "Error: missing file\n";
            print_usage();
            return EXIT_FAILURE;
        }
        file_name = argv[2];
        
        OptionsParser op(file_name);
        auto command = op.parse();
        command->execute();
    }
    else {
        std::cerr << "Error: unknown command\n";
        print_usage();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
