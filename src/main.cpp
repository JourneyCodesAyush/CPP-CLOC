#include "middleware.hpp"

int main(int argc, char const *argv[])
{
    if (argc == 2)
    {
        middleware::process_file(argv[1]);
    }

    return 0;
}
