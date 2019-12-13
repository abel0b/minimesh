#include <memory>
#include <stdexcept>

#include "options.hpp"
#include "transform.hpp"

OptionsParser::OptionsParser(const std::string& file_name)
  : m_file_name(file_name)
{
  m_data = cpptoml::parse_file(m_file_name);
}

std::shared_ptr<Command> OptionsParser::parse(void)
{
  auto transform = m_data->get_table("transform");
  auto name = *transform->get_as<std::string>("name");

  if (name.compare("merge") == 0) {
    bool merge_nodes = *transform->get_as<bool>("merge_nodes");
    
    auto io = m_data->get_table("io");
    std::vector<std::string> meshes = *io->get_array_of<std::string>("inputs");
    std::string result_file_name = *io->get_as<std::string>("output");

    auto quality = m_data->get_table("quality");
    bool compute_quality = *quality->get_as<bool>("compute_quality");


    std::shared_ptr<Command> command(new Merge(
        merge_nodes,
        meshes,
        result_file_name,
        compute_quality       
    ));

    return command;
  } else if (name.compare("translate") == 0) {
    std::vector<double> coords = *transform->get_array_of<double>("translation");

    auto io = m_data->get_table("io");
    std::string mesh = *io->get_as<std::string>("input");
    std::string result_file_name = *io->get_as<std::string>("output");

    auto quality = m_data->get_table("quality");
    bool compute_quality = *quality->get_as<bool>("compute_quality");
  
    std::shared_ptr<Command> command(new Translate(
        coords[0],
        coords[1],
        coords[2],
        mesh,
        result_file_name,
        compute_quality
     ));

    return command;
  } else {
      throw std::invalid_argument("incorrect file format");
  }
}

OptionsParser::~OptionsParser() {
    //delete m_data;
}

