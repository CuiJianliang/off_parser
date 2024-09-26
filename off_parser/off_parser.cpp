#include "off_parser.h"

#include <fstream>
#include <iostream>
#include <sstream>

int OffParser::read_from(const std::string &src_file_name, std::vector<std::array<float, 3>> &vertices, std::vector<OffFaceInfo> &faces) {
    std::ifstream in(src_file_name);
    if (!in.is_open()) {
        std::cerr << "call read_from function failed: open off file failed!" << std::endl;
        return -1;
    }

    std::string line;
    std::getline(in, line);
    if (line != "OFF") {
        in.close();
        std::cerr << "call read_from function failed: input file is not off format!" << std::endl;
        return -1;
    }

    int num_vertices = 0, num_faces = 0, num_edges = 0;
    while (std::getline(in, line)) {
        if (line[0] == '#' || line[0] == '\r') {
            continue;
        } else if (!std::isdigit(line[0])) {
            in.close();
            std::cerr << "call read_from function failed: invalid type!";
            return -1;
        }
        auto pos = line.find('#');
        if (pos == std::string::npos) {
            pos = line.size();
        }
        std::stringstream ss(line.substr(0, pos));
        ss >> num_vertices >> num_faces >> num_edges;
        break;
    }

    if (num_vertices <= 0) {
        in.close();
        std::cerr << "call read_from function failed: vertex num is less equal than 0!" << std::endl;
        return -1;
    }

    if (num_faces <= 0) {
        in.close();
        std::cerr << "call read_from function failed: faces num is less equal than 0!" << std::endl;
        return -1;
    }

    unsigned int count = 0;

    std::vector<std::array<float, 3>> tmp_vertices;
    while (count < num_vertices && std::getline(in, line)) {
        if (line[0] == '#' || line[0] == '\r') {
            continue;
        } else if (!std::isdigit(line[0]) && !std::isblank(line[0]) && line[0] != '-') {
            in.close();
            std::cerr << "call read_from function failed: invalid type!";
            return -1;
        }

        std::array<float, 3> current_vertex;

        auto pos = line.find('#');
        if (pos == std::string::npos) {
            pos = line.size();
        }
        std::stringstream ss(line.substr(0, pos));
        ss >> current_vertex[0] >> current_vertex[1] >> current_vertex[2];

        tmp_vertices.emplace_back(current_vertex);
        count++;
    }

    if (count != num_vertices) {
        in.close();
        std::cerr << "call read_from function failed: invalid type!";
        return -1;
    }

    count = 0;
    std::vector<OffFaceInfo> tmp_faces;
    while (count < num_faces && std::getline(in, line)) {
        if (line[0] == '#' || line[0] == '\r') {
            continue;
        } else if (!std::isdigit(line[0]) && !std::isblank(line[0])) {
            in.close();
            std::cerr << "call read_from function failed: invalid type!";
            return -1;
        }
        unsigned int face_vertex = 0;

        auto pos = line.find('#');
        if (pos == std::string::npos) {
            pos = line.size();
        }
        std::stringstream ss(line.substr(0, pos));
        ss >> face_vertex;
        if (face_vertex <= 0) {
            in.close();
            std::cerr << "call read_from function failed: invalid type!";
            return -1;
        }

        OffFaceInfo current_info;
        current_info.vertices.resize(face_vertex);
        for (int i = 0; i < face_vertex; i++) {
            ss >> current_info.vertices[i];
        }
        ss >> current_info.r >> current_info.g >> current_info.b;

        tmp_faces.emplace_back(current_info);
        count++;
    }

    in.close();

    if (count != num_faces) {
        std::cerr << "call read_from function failed: invalid type!";
        return -1;
    }

    vertices.swap(tmp_vertices);
    faces.swap(tmp_faces);
    return 0;
}

int OffParser::write_to(const std::string &dst_file_name, const std::vector<std::array<float, 3>> &vertices, const std::vector<OffFaceInfo> &faces) {
    std::ofstream out(dst_file_name);
    if (!out.is_open()) {
        std::cerr << "call write_to function failed: open file failed" << std::endl;
        return -1;
    }
    out << "OFF" << std::endl;
    out << vertices.size() << " " << faces.size() << " 0" << std::endl;
    for (auto i = 0; i < vertices.size(); i++) {
        out << vertices[i][0] << " " << vertices[i][1] << " " << vertices[i][2] << std::endl;
    }

    for (auto i = 0; i < faces.size(); i++) {
        const auto vertex_size = faces[i].vertices.size();
        out << vertex_size << " ";
        for (auto j = 0; j < vertex_size; j++) {
            out << faces[i].vertices[j] << " ";
        }
        out << faces[i].r << " " << faces[i].g << " " << faces[i].b << std::endl;
    }
    out.close();
    return 0;
}