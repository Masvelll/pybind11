#include <pybind11/pybind11.h>

namespace py = pybind11;

int add(int i = 1, int j = 2){
    return i + j;
}

struct Pet {
    Pet(const std::string &name) : name(name) { }
    void setName(const std::string &name_) { name = name_; }
    const std::string &getName() const { return name; }

    std::string name;

};

PYBIND11_MODULE(example, m) {
    m.doc() = "pybind example plugin";

    m.def("add", &add, "A function that adds to numbers", 
          py::arg("i") = 1, py::arg("j") = 2);

    m.attr("the_answer") = 42; // automatic conversion as atributes
    py::object world = py::cast("World"); // explicit conversion
    m.attr("what") = world;

    py::class_<Pet>(m, "Pet")
        .def(py::init<const std::string &>())
        .def("setName", &Pet::setName)
        .def("getName", &Pet::getName)
        .def("__repr__",
            [](const Pet &a){
                return "<example.Pet named '" + a.name + "'>";
            }
        );

}
// to make a file 
// c++ -O3 -Wall -shared -std=c++11 -fPIC $(python3 -m pybind11 --includes) example.cpp -o example$(python3-config --extension-suffix)