#pragma once

#ifdef DLL_EXPORT
#ifdef _WIN32
#define DLL_API __declspec(dllexport)
#else
#define DLL_API
#endif // _WIN32
#else
#ifdef _WIN32
#define DLL_API __declspec(dllimport)
#else
#define DLL_API
#endif // _WIN32
#endif // DLL_EXPORT

#include <array>
#include <string>
#include <vector>

struct OffFaceInfo {
  public:
    std::vector<unsigned int> vertices;
    unsigned int r;
    unsigned int g;
    unsigned int b;
    bool with_color;

  public:
    OffFaceInfo() : r(0), g(0), b(0), with_color(false) {}
};

class DLL_API OffParser {
  public:
    static int read_from(const std::string &src_file_name, std::vector<std::array<float, 3>> &vertices, std::vector<OffFaceInfo> &faces);

    static int write_to(const std::string &dst_file_name, const std::vector<std::array<float, 3>> &vertices, const std::vector<OffFaceInfo> &faces);
};