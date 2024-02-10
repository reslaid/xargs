#include "xargs/xargs.h"

int main(int argc, char* argv[])
{
    Args args{ argc, argv };

    Flag fExitCode;
    bool fExitCodeExist;

    fExitCode = args.get("--c");
    fExitCodeExist = args.exists(fExitCode);

    if (fExitCodeExist)
    {
        int exitCode = atoi(fExitCode.value);
        exit(exitCode);
    }

    return 0x000;
}
