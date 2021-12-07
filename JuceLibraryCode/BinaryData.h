/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   clap_wav;
    const int            clap_wavSize = 95852;

    extern const char*   clave_wav;
    const int            clave_wavSize = 4028;

    extern const char*   crash_wav;
    const int            crash_wavSize = 206850;

    extern const char*   hat1_wav;
    const int            hat1_wavSize = 22504;

    extern const char*   hat2_wav;
    const int            hat2_wavSize = 38664;

    extern const char*   hat3_wav;
    const int            hat3_wavSize = 40064;

    extern const char*   kick1_wav;
    const int            kick1_wavSize = 72314;

    extern const char*   kick2_wav;
    const int            kick2_wavSize = 76244;

    extern const char*   sn1_wav;
    const int            sn1_wavSize = 78298;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 9;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
