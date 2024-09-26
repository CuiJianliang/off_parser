#include <array>
#include <string>
#include <vector>

#include "off_parser.h"

int main() {
    std::vector<std::array<float, 3>> vertices;
    std::vector<OffFaceInfo> faces;
#ifdef _WIN32
    const std::string input_file_name = "../../resource/input.off";
    const std::string output_file_name = "../../resource/output.off";
#else
    const std::string input_file_name = "../resource/test.off";
    const std::string output_file_name = "../resource/output.off";
#endif
    OffParser::read_from(input_file_name, vertices, faces);
    OffParser::write_to(output_file_name, vertices, faces);

    return 0;
}
