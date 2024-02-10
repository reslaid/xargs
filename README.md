> # [XArgs](https://github.com/reslaid/xargs.git) [![Version](https://img.shields.io/badge/Version-0.1.1-green.svg)](https://github.com/reslaid/xargs.git)
> [![languages](https://skillicons.dev/icons?i=c,cpp)](https://github.com/reslaid/xargs.git)

# **Dependencies**
- [**Git**](https://git-scm.com/downloads)

# Installing
- **Installation from repository**
  ```bash
  git clone https://github.com/reslaid/xargs.git
  ```

# Docs
- **Including a header file**
    ```cpp
    #include "xargs/xargs.h"
    ```

- **Creating Instance**
    ```cpp
    void main(int argc, char* argv[])
    {
        Args args{ argc, argv };
    }
    ```

- **Checking the existence of an argument**
    - **(`LEGACY`) Conventional approach (strstr)**
        ```cpp
        bool flHelpExist;
        XARGS_RSLT flHelp;

        flHelp = args.contains("--help");
        flHelpExist = (flHelp == XARGS_EXIST);
        ```

    - **(`LEGACY`) Iterative Approach**
        ```cpp
        bool flIterHelpExist;
        XARGS_RSLT flIterHelp;
        
        flIterHelp = args.contains_iter("--help");
        flIterHelpExist = (flIterHelp == XARGS_EXIST);
        ```

    - **(`MODERN`) Flag Structure Approach**
        ```cpp
        Flag fHelp;
        bool fHelpExist;

        fHelp = args.get("--help");
        fHelpExist = args.exists(fHelp);
        ```

- **Flag structure**
    -  **Structure attributes**
        ```cpp
        // Contains the name of the flag
        char* name; // --name

        // If the value was not passed contains NULL
        char* value; // --name=value
        ```

    - **Usage**
        ```cpp
        // Checking if a flag is specified
        if (fHelpExist)
        {
            /* Output:
             Usage: {%path%\%file%.%ext%} [options] 
            */
            printf(
                "Usage: %s [options]\n",
                args.from_index(
                    (_UINT)XARGS_APP_INDEX
                )
            );

            printf("Options:\n");
            printf(
                "  --help     Display this help message\n"
            );
            
            exit(0x0);
        }
        ```
