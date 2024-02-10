#include "xargs/xargs.h"

int main(int argc, char* argv[])
{
    Args args{ argc, argv };

    Flag fExitCode;
    bool fExitCodeExist;

    fExitCode = args.get("-c");
    fExitCodeExist = args.exists(fExitCode);

    if (fExitCodeExist)
    {
        exit((int)fExitCode.value);
    }

    return 0x000;
}
