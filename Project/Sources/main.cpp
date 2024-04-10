#include "Application/application_data.h"

int main(int, char**)
{
  std::filesystem::path currentPath = std::filesystem::current_path();
  std::filesystem::path root(currentPath.parent_path().parent_path());
  string project = currentPath.stem().string();
  root.concat("/Project/");
  std::cout << root << std::endl;

  Application application(project, root.string());
  application.start_application();
  application.main_loop();
  application.exit();
  
  return 0;
}