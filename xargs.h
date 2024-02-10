#pragma once

/**
 * @brief Macro to disable secure CRT warnings.
 */
#if !defined(       _CRT_SECURE_NO_WARNINGS)
# define            _CRT_SECURE_NO_WARNINGS
#endif

 /**
 * @brief Includes based on the programming language.
 */
#pragma region Includes

#if defined(        __cplusplus)
# include <cstdio>     /**< Standard input/output operations */
# include <cstdlib>    /**< General utilities library */
# include <cstddef>    /**< Standard definitions */
# include <cstring>    /**< String handling */
# include <cstdint>    /**< Standard integer types */
# include <cstdbool>   /**< Boolean type and values */
#else
# include <stdio.h>    /**< Standard input/output operations */
# include <stdlib.h>   /**< General utilities library */
# include <stddef.h>   /**< Standard definitions */
# include <string.h>   /**< String handling */
# include <stdint.h>   /**< Standard integer types */
# include <stdbool.h>  /**< Boolean type and values */
#endif

#pragma endregion

 /**
  * @brief Macros for common definitions.
  */
#pragma region Macros

  /* Version number of XARGS */
#if !defined(       XARGS_VERSION)
# define            XARGS_VERSION               0x1
#else
# undef             XARGS_VERSION
# define            XARGS_VERSION               0x1
#endif

/* Pointer type definition */
#if !defined(       PTR)
# define            PTR                         void*
#endif

#if !defined(       _STR)

/* String type definition */
# define            _STR                        char*

/* Constant string type definition */
# define            _CSTR const                 _STR

/* Unsigned integer type definition */
# define            _UINT unsigned              int
#endif

/* Macro to get the size of an array */
#if !defined(       __XARGS_ARR_SIZE)
# define            __XARGS_ARR_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#endif

/* Macro to stringify a symbol */
#if !defined(       __XARGS_STRINGIFY)
# define            __XARGS_STRINGIFY(DATA)     #DATA
#endif

/**< Macro for null pointer value */
#if !defined(       __XARGS_NULLPTR)
# define            __XARGS_NULLPTR (PTR)       0x0
#endif

/* Calling convention for functions */
#if !defined(       __XARGS_CALLTYPE)
# define            __XARGS_CALLTYPE            __cdecl
#endif

/* Dynamic calling convention for functions */
#if !defined(       __XARGS_DYNAMIC_CALLTYPE)
# define            __XARGS_DYNAMIC_CALLTYPE    __declspec
#endif

/* Inline */
#if !defined(       __XARGS_INLINE)
# if defined(   __cplusplus)
#  define           __XARGS_INLINE              inline
# else
#  define            __XARGS_INLINE              
#endif
#endif

/* Import specifier */
#if !defined(       __XARGS_IMPORT)
# define            __XARGS_IMPORT              __DYNAMIC_CALLTYPE(import)
#endif

/* Export specifier */
#if !defined(       __XARGS_EXPORT)
# define            __XARGS_EXPORT              __DYNAMIC_CALLTYPE(export)
#endif

/* External linkage specifier for C++ */
#if !defined(       __XARGS_EXTERN)
# if defined(       __cplusplus)
#  define           __XARGS_EXTERN extern       "C"
# else
#  define           __XARGS_EXTERN
# endif
#endif

/* Result type for functions */
#if !defined (      XARGS_RSLT)
# define            XARGS_RSLT const            short
#endif

/* Non-existent result */
#if !defined(       XARGS_NON_EXIST)
# define            XARGS_NON_EXIST (XARGS_RSLT)0x0002
#endif

/* Existent result */
#if !defined(       XARGS_EXIST)
# define            XARGS_EXIST (XARGS_RSLT)    0x0003
#endif

/* Coincident result */
#if !defined(       XARGS_COINCIDENCE)
# define            XARGS_COINCIDENCE           0x0004
#endif

/* Non-coincident result */
#if !defined(       XARGS_NOT_COINCIDENCE)
# define            XARGS_NOT_COINCIDENCE       0x0005
#endif

/* Index with the executable file name */
#if !defined(       XARGS_APP_INDEX)
# define            XARGS_APP_INDEX             0x0
#endif

#pragma endregion

#pragma region Types & Structures

/**
 * @brief Structure representing a command-line flag with its name and value.
 */
__XARGS_EXTERN typedef struct
{
    _STR name; /**< The name of the flag. */
    _STR value; /**< The value associated with the flag. */
} __Arg_Flag;

/**
 * @brief Structure representing command-line arguments and their parsed flags.
 */
__XARGS_EXTERN struct _ArgsStruct
{
    int count_;         /**< The number of command-line arguments. */
    _STR* vals_;        /**< Array of command-line argument strings. */
    _STR strvals_;      /**< Concatenated string of all command-line arguments. */
    __Arg_Flag* flags_; /**< Array of parsed command-line flags. */

    /**
     * @brief Concatenate an array of strings into a single string with space separation.
     * @param strings Array of strings to concatenate.
     * @param count Number of strings in the array.
     * @return Pointer to the concatenated string.
     */
    __XARGS_INLINE _STR __XARGS_CALLTYPE _join(_STR* strings, int count) {
        size_t total_length = 0; // Initialize total length to 0
        for (int i = 0; i < count; i++) {
            total_length += strlen(strings[i]); // Add the length of each string
            if (i < count - 1) {
                total_length++; // Add 1 for the space between strings
            }
        }

        // Allocate memory for the result string
        _STR result = (_STR)malloc(total_length + 1); // +1 for null terminator
        if (!result) {
            return NULL; // Return NULL if memory allocation fails
        }

        result[0] = '\0'; // Initialize the result string as empty

        // Concatenate each string with a space in between
        for (int i = 0; i < count; i++) {
            strcat(result, strings[i]); // Concatenate the current string
            if (i < count - 1) {
                strcat(result, " "); // Add a space if it's not the last string
            }
        }

        return result; // Return the joined string
    }

    /**
     * @brief Initialize the command-line arguments structure with the given arguments.
     * @param count Number of command-line arguments.
     * @param values Array of command-line argument strings.
     */
    __XARGS_INLINE void __XARGS_CALLTYPE init(int count, _STR* values)
    {
        // Set the count of values
        this->count_ = count;

        // Allocate memory for vals_ array and copy values
        this->vals_ = (_STR*)malloc(sizeof(_STR) * this->count_);
        for (int i = 0; i < this->count_; i++) {
            this->vals_[i] = values[i];
        }

        // Join the string values into a single string
        this->strvals_ = this->_join(this->vals_, this->count_);

        // Parse all flags from the string values
        this->flags_ = this->parseall();
    }

    /**
     * @brief Default constructor for the command-line arguments structure.
     */
    __XARGS_INLINE __XARGS_CALLTYPE _ArgsStruct()
    {
        this->count_ = 0;
        this->vals_ = NULL;
        this->flags_ = NULL;
    }

    /**
     * @brief Constructor for the command-line arguments structure.
     * @param count Number of command-line arguments.
     * @param values Array of command-line argument strings.
     */
    __XARGS_INLINE __XARGS_CALLTYPE _ArgsStruct(int count, _STR* values)
    {
        this->init(count, values); // Call the init method to perform initialization
    }

    /**
     * @brief Check if a specific flag exists in the command-line arguments.
     * @param FLAG The flag to check for.
     * @return XARGS_RSLT value indicating whether the flag exists or not.
     */
    __XARGS_INLINE XARGS_RSLT __XARGS_CALLTYPE contains(_CSTR FLAG)
    {
        // Search for the flag within the concatenated string values
        _STR rslt = strstr(this->strvals_, FLAG);

        // If the flag is not found, return XARGS_NON_EXIST
        if (rslt == NULL)
        {
            return (XARGS_RSLT)XARGS_NON_EXIST;
        }

        // If the flag is found, return XARGS_EXIST
        return (XARGS_RSLT)XARGS_EXIST;
    }

    /**
     * @brief Check if a specific flag exists in the command-line arguments using an iterative search.
     * @param FLAG The flag to check for.
     * @return XARGS_RSLT value indicating whether the flag exists or not.
     */
    __XARGS_INLINE XARGS_RSLT __XARGS_CALLTYPE contains_iter(_CSTR FLAG)
    {
        // Iterate through each individual string value
        for (int i = 0; i < count_; ++i) {
            // Check if the flag is contained within the current value
            if (strstr(vals_[i], FLAG) != NULL) {
                return (XARGS_RSLT)XARGS_EXIST; // Flag found, return XARGS_EXIST
            }
        }
        // Flag not found in any value, return XARGS_NON_EXIST
        return (XARGS_RSLT)XARGS_NON_EXIST;
    }

    /**
     * @brief Compare two flag structures to check for coincidence.
     * @param flag1 First flag to compare.
     * @param flag2 Second flag to compare.
     * @return XARGS_RSLT value indicating whether the flags coincide or not.
     */
    __XARGS_INLINE XARGS_RSLT __XARGS_CALLTYPE compare(__Arg_Flag* flag1, __Arg_Flag* flag2) {
        // Compare the name fields of the two __Arg_Flag structures
        if (strcmp(flag1->name, flag2->name) == 0) {
            return XARGS_COINCIDENCE; // Names are identical, return XARGS_COINCIDENCE
        }
        else {
            return XARGS_NOT_COINCIDENCE; // Names are different, return XARGS_NOT_COINCIDENCE
        }
    }

    /**
     * @brief Parse a command-line flag string into a flag structure.
     * @param FLAG The flag string to parse.
     * @return Parsed flag structure.
     */
    __XARGS_INLINE __Arg_Flag __XARGS_CALLTYPE parse(_STR FLAG)
    {
        __Arg_Flag flag; // Declare a flag structure to hold the parsed flag information
        flag.name = NULL; // Initialize flag name to NULL
        flag.value = NULL; // Initialize flag value to NULL

        // Find the position of the first '=' and ' ' characters in the input string
        char* equals = strchr(FLAG, '='); // Find the position of '=' character
        char* space = strchr(FLAG, ' '); // Find the position of ' ' character

        // Check if the input string starts with '-' or '--'
        if (strncmp(FLAG, "--", 0x2) == 0x0 || strncmp(FLAG, "-", 0x1) == 0x0) {
            if (equals != NULL) { // If '=' is found, parse flag name and value
                size_t name_len = equals - FLAG - 0x2; // Calculate the length of the flag name
                flag.name = (_STR)malloc(name_len + 0x1); // Allocate memory for flag name
                strncpy(flag.name, FLAG + 0x2, name_len); // Copy flag name from input string
                flag.name[name_len] = '\0'; // Null-terminate the flag name

                size_t value_len = strlen(equals + 0x1); // Calculate the length of the flag value
                flag.value = (_STR)malloc(value_len + 0x1); // Allocate memory for flag value
                strcpy(flag.value, equals + 0x1); // Copy flag value from input string
            }
            else if (space != NULL && (space < equals || equals == NULL)) { // If ' ' is found, parse flag name and value
                size_t name_len = space - FLAG - 0x2; // Calculate the length of the flag name
                flag.name = (_STR)malloc(name_len + 0x1); // Allocate memory for flag name
                strncpy(flag.name, FLAG + 0x2, name_len); // Copy flag name from input string
                flag.name[name_len] = '\0'; // Null-terminate the flag name

                size_t value_len = strlen(space + 0x1); // Calculate the length of the flag value
                flag.value = (_STR)malloc(value_len + 0x1); // Allocate memory for flag value
                strcpy(flag.value, space + 0x1); // Copy flag value from input string
            }
            else { // If neither '=' nor ' ' is found, parse only flag name
                size_t name_len = strlen(FLAG) - 0x2; // Calculate the length of the flag name
                flag.name = (_STR)malloc(name_len + 0x1); // Allocate memory for flag name
                strncpy(flag.name, FLAG + 0x2, name_len); // Copy flag name from input string
                flag.name[name_len] = '\0'; // Null-terminate the flag name
            }
        }

        return flag; // Return the parsed flag structure
    }

    /**
     * @brief Parse all command-line flags and return an array of parsed flags.
     * @return Array of parsed flags.
     */
    __XARGS_INLINE __Arg_Flag* __XARGS_CALLTYPE parseall()
    {
        // Allocate memory for an array to store parsed flags
        __Arg_Flag* flags = (__Arg_Flag*)malloc(sizeof(__Arg_Flag) * this->count_);
        int num_flags = 0; // Counter for the number of parsed flags

        // Iterate through each command-line flag value
        for (int i = 1; i < this->count_; ++i) {
            // Parse the flag stored at index i in the vals_ array
            __Arg_Flag flag = parse(this->vals_[i]);
            // Check if the parsed flag has a valid name
            if (flag.name != NULL) {
                // If the flag has a valid name, add it to the flags array and increment the counter
                flags[num_flags++] = flag;
            }
        }

        // Return the array containing parsed flags
        return flags;
    }

    /**
     * @brief Check if a parsed flag structure exists (i.e., has a non-null name).
     * @param flag The flag structure to check.
     * @return True if the flag exists, false otherwise.
     */
    __XARGS_INLINE bool __XARGS_CALLTYPE exists(__Arg_Flag flag)
    {
        // Check if the name of the flag is not NULL
        return flag.name != NULL;
    }

    /**
     * @brief Get the number of command-line flags.
     * @return The number of command-line flags.
     */
    __XARGS_INLINE _UINT __XARGS_CALLTYPE get_flags_count()
    {
        // Subtract 1 from the total count to exclude the program name
        return this->count_ - 0x1;
    }

    /**
     * @brief Extracts the command-line argument string by index.
     *
     * Retrieves the command-line argument string at the specified index from the
     * array of arguments stored within the Args structure instance.
     *
     * @param uindex The index of the command-line argument to retrieve.
     * @return Pointer to the command-line argument string.
     */
    __XARGS_INLINE _STR __XARGS_CALLTYPE from_index(_UINT uindex)
    {
        // Pointer to the command-line argument string at the specified index.
        return this->vals_[uindex];
    }

    /**
     * @brief Get the flag name by removing leading '-' characters.
     * @param FLAG The flag string.
     * @return Pointer to the first non '-' character in the flag string.
     */
    __XARGS_INLINE _STR __XARGS_CALLTYPE get_flag(_STR FLAG)
    {
        size_t size = strlen(FLAG);

        _STR ptr = FLAG;

        // Skip leading dashes
        while (*ptr == '-') {
            ++ptr;
        }

        // Return a pointer to the flag name
        return ptr;
    }

    /**
     * @brief Get the parsed flag structure corresponding to the given flag string.
     * @param FLAG The flag string.
     * @return Parsed flag structure.
     */
    __XARGS_INLINE __Arg_Flag __XARGS_CALLTYPE get(_CSTR FLAG)
    {
        _STR FFLAG = this->get_flag((_STR)FLAG); // Extract the flag name

        __Arg_Flag flag{ NULL, NULL }; // Initialize an empty flag object

        // Check if there are flags available
        if (this->get_flags_count() <= 0x0) {
            return flag; // No flags available, return empty flag object
        }

        // Search for the flag with the specified name
        for (int i = 0; i < this->count_ - 1; ++i) {
            flag = this->flags_[i]; // Get the current flag object

            // Compare the flag name with the specified name
            if (strcmp(flag.name, FFLAG) == 0) {
                return flag; // Found matching flag, return the flag object
            }
        }

        // Flag with the specified name not found, return empty flag object
        flag.name = NULL;
        flag.value = NULL;
        return flag;
    }
};

__XARGS_EXTERN typedef _ArgsStruct Args; /**< Typedef for command-line arguments structure. */
__XARGS_EXTERN typedef __Arg_Flag Flag;  /**< Typedef for command-line flag structure. */

#pragma endregion
