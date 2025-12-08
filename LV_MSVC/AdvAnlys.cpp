#include <print>     // C++23: std::print, std::println
#include <cstdlib>   // std::strtod, std::exit
#include <cerrno>    // errno, ERANGE

// If the library exports C symbols (no C++ name mangling)
extern "C" {
    double LV_Struve(double x, double u, double *Struve);
}

using namespace std;

// Parse a double from C string; return 0 on success, -1 on error
static int parse_double(const char* s, const char* name, double* out)
{
    char* endptr;
    errno = 0;
    *out = strtod(s, &endptr);  // convert

    if (endptr == s) {               // no digits
        print(stderr, "invalid {} (no number): {}\n", name, s);
        return -1;
    }
    if (errno == ERANGE) {           // out of range
        print(stderr, "invalid {} (out of range): {}\n", name, s);
        return -1;
    }
    if (*endptr != '\0') {           // extra junk
        print(stderr, "invalid {} (trailing chars): {}\n", name, s);
        return -1;
    }
    return 0;
}

static void usage(const char* name)
{
    print(stderr, "usage: {} <x> <v>\n", name);
    println(stderr, "Struve Tester");
    println(stderr, "    x    real argument of the Struve function H_v(x)");
    println(stderr, "    v    order (index) of the Struve function H_v(x)");
    exit(1);
}

int main(int argc, char* argv[])
{
    if (argc < 3 || argc > 4) usage(argv[0]);

    double x, v;
    if (parse_double(argv[1], "x", &x) != 0) return 1;
    if (parse_double(argv[2], "v", &v) != 0) return 1;

    double res;
	LV_Struve(x, v, &res);
    println("Struve ({}, {}) = {}", x, v, res);
}