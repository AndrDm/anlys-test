#include <advanlys.h> // for Struve
#include <ansi_c.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

static int parse_double(const char *s, const char *name, double *out)
{
    char *endptr;
    errno = 0;
    *out = strtod(s, &endptr);	/* convert */

    if (endptr == s) {			/* no digits */
        fprintf(stderr, "invalid %s (no number): %s\n", name, s);
        return -1;
    }
    if (errno == ERANGE) {		/* out of range */
        fprintf(stderr, "invalid %s (out of range): %s\n", name, s);
        return -1;
    }
    if (*endptr != '\0') {		/* extra junk */
        fprintf(stderr, "invalid %s (trailing chars): %s\n", name, s);
        return -1;
    }
    return 0;
}

static void usage (char *name)
{
    fprintf(stderr, "usage: %s <x> <v>\n", name);
    fprintf(stderr, "Struve Tester\n");
    fprintf(stderr, "    x    real argument of the Struve function H_v(x)\n");
    fprintf(stderr, "    v    order (index) of the Struve function H_v(x)\n");
    exit(1);
}

int main (int argc, char *argv[])
{
    if (argc < 3 || argc > 4) usage (argv[0]);

    double x, v;
    if (parse_double(argv[1], "x", &x) != 0) return 1;
    if (parse_double(argv[2], "v", &v) != 0) return 1;

    double res = Struve(x, v);
    printf("Struve (%f, %f) = %f\n", x, v, res);
}
