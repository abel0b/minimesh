#pragma once

#include <vector>
#include <string>

struct Command {
    virtual ~Command(void) = default;
    virtual void execute() = 0;
};

struct Merge : public Command {
    bool merge_nodes;
    std::vector<std::string> inputs;
    std::string output;
    bool compute_quality;
    Merge(bool merge_nodes, std::vector<std::string> inputs, std::string output, bool coompute_quality) : merge_nodes(merge_nodes), inputs(inputs), output(output), compute_quality(compute_quality) {}

    void execute();
};

struct Translate : public Command
{
    double x,y,z;
    std::string input;
    std::string output;
    bool compute_quality;
    Translate(double x, double y, double z, std::string input, std::string output, bool compute_quality) : x(x), y(y), z(z), input(input), output(output), compute_quality(compute_quality) {}
    void execute();
};

class Transform
{
public:
    Transform(void) {}
    ~Transform(void) {}
};
