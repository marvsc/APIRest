#include "restapi.h"
#include <vector>
#include <string>

int main() {
    restapi();

    std::vector<std::string> vec;
    vec.push_back("test_package");

    restapi_print_vector(vec);
}
