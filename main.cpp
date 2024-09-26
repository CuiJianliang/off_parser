#include <array>
#include <string>
#include <vector>

#include "off_parser.h"

int main() {
    std::vector<std::array<float, 3>> vertices;
    std::vector<OffFaceInfo> faces;
    OffParser::read_from("1.off", vertices, faces);
    OffParser::write_to("2.off", vertices, faces);

    return 0;
}
