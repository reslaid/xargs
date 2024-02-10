#include "xargs/xargs.h"

void showHelp(Args* args)
{
    printf(
        "Usage: %s [options]\n",
        args->from_index(
            XARGS_APP_INDEX
        )
    );

    printf(
        "Options:\n"
    );
    
    printf(
        "  --help     Display this help message\n"
    );
}

int main(int argc, char* argv[])
{
    Args args{ argc, argv };

    Flag fHelp;
    bool fHelpExist;

    fHelp = args.get("--help");
    fHelpExist = args.exists(fHelp);

    if (argc <= 0x1) {
        showHelp(&args);
        exit(0x002);
    }

    if (fHelpExist)
    {
        showHelp(&args);
        exit(0x000);
    }

    return 0x000;
}
