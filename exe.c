typedef short int word;
typedef long int dword;

/**
 * Data Directory
 * addr:Address
 * size:Size
 */
struct DATA_DIRECTORY
{
    dword addr;
    dword size;
};

/**
 * Coff Optional header
 * win32 needed this header
 */
struct OPTI_HEADER
{

    word Magic;
    char MajorLinkerVersion;
    char MinorLinkerVersion;
    dword SizeOfCode;
    dword SizeOfInitializedData;
    dword SizeOfUninitializedData;
    dword AddressOfEntryPoint;
    dword BaseOfCode;
    dword BaseOfData;
    dword ImageBase;
    dword SectionAlignment;
    dword FileAlignment;
    word MajorOperatingSystemVersion;
    word MinorOperatingSystemVersion;
    word MajorImageVersion;
    word MinorImageVersion;
    word MajorSubsystemVersion;
    word MinorSubsystemVersion;
    dword Win32VersionValue;
    dword SizeOfImage;
    dword SizeOfHeaders;
    dword CheckSum;
    word Subsystem;
    word DllCharacteristics;
    dword SizeOfStackReserve;
    dword SizeOfStackCommit;
    dword SizeOfHeapReserve;
    dword SizeOfHeapCommit;
    dword LoaderFlags;
    dword NumberOfRvaAndSizes;
    struct DATA_DIRECTORY DataDirectory[16];
};

/**
 * DOS header
 * File write for first
 */
struct DOS_HEADER
{
    word magic;
    word cblp;
    word cp;
    word crlc;
    word cparhdr;
    word minalloc;
    word maxalloc;
    word ss;
    word sp;
    word csum;
    word ip;
    word cs;
    word lfarlc;
    word ovno;
    word res[4];
    word oemid;
    word oeminfo;
    word res2[10];
    long lfanew;
};

/**
 * File Header
 */
struct FILE_HEADER
{
    word Matchine;
    word Sections_len;
    dword TimeStamp;
    dword SymboltableAddr;
    dword symbols_len;
    word optiheadsize;
    word Chara;
};

/**
 * NT header
 * sign: const(PE\0\0)
 */
struct NT_HEADER
{
    dword sign;
    struct FILE_HEADER filehead;
    struct OPTI_HEADER optihead;
};

/**
 * section header
 * File write for first
 */
struct SECTION_HEADER
{
    char Name[8];
    union {
        dword PhysicalAddress;
        dword VirtualSize;
    } Misc;
    dword VirtualAddress;
    dword SizeOfRawData;
    dword PointerToRawData;
    dword PointerToRelocations;
    dword PointerToLinenumbers;
    word NumberOfRelocations;
    word NumberOfLinenumbers;
    dword Characteristics;
};

struct DOS_HEADER Dosheader = {
    magic : 0x5a4d,
    cblp : 0x0090,
    cp : 0x0003,
    cparhdr : 0x0004,
    minalloc : 0x0000,
    maxalloc : 0xffff,
    sp : 0x00b8,
    lfarlc : 0x0040,
    lfanew : 0x0080
};

struct NT_HEADER Ntheader =
    {
        sign : 0x00004550,
        filehead : {
            Matchine : 0x014c,
            Sections_len : 16,
            TimeStamp : 0x00000000, //Zerotime
            SymboltableAddr : 0x00000000,
            symbols_len : 0x00000000,
            optiheadsize : 0x00f0,
            Chara : 0x0107 //32bit
        },
        optihead : {
            Magic : 0x010b,
            MajorLinkerVersion : 0,
            MinorLinkerVersion : 0,
            SizeOfCode : 0x0400,
            SizeOfInitializedData : 0x00000000,
            SizeOfUninitializedData : 0x00000000,
            AddressOfEntryPoint : 0x00000000,
            BaseOfCode : 0x1000,
            BaseOfData : 0x2000,
            ImageBase : 0x00400000,
            SectionAlignment : 0x10,
            FileAlignment : 0x10,
            MajorOperatingSystemVersion : 0x0004,
            MinorOperatingSystemVersion : 0x0000,
            MajorImageVersion : 0x0000,
            MinorImageVersion : 0x0000,
            MajorSubsystemVersion : 0x0004,
            MinorSubsystemVersion : 0x0000,
            Win32VersionValue : 0x0000,
            SizeOfImage : 0x3000,
            SizeOfHeaders : 0x200,
            CheckSum : 0xffff,
            Subsystem : 0x0003,
            DllCharacteristics : 0x0000,
            SizeOfStackReserve : 0x00100000,
            SizeOfStackCommit : 0x00001000,
            SizeOfHeapReserve : 0x00100000,
            SizeOfHeapCommit : 0x00001000,
            LoaderFlags : 0x0,
            NumberOfRvaAndSizes : 16,
            DataDirectory : {
                {0x00000000, 0x00000000},
                {0x00000000, 0x00000000},
                {0x00000000, 0x00000000},
                {0x00002000, 0x0000000c},
                {0x00000000, 0x00000000},
                {0x00000000, 0x00000000},
                {0x00000000, 0x00000000},
                {0x00000000, 0x00000000},
                {0x00000000, 0x00000000},
                {0x00000000, 0x00000000},
                {0x00000000, 0x00000000},
                {0x00000000, 0x00000000},
                {0x00000000, 0x00000000},
                {0x00000000, 0x00000000},
                {0x00000000, 0x00000000},
                {0x00000000, 0x00000000},
            }
        }
    };

#include <stdio.h>
#include <ctype.h>

#define target Ntheader
int main()
{
    char ch;
    char *base = (char *)&target;
    int j;
    for (int i = 0; i * 16 < sizeof(target); i++)
    {
        printf("%08x|",i*16);
        for (j = 0; j < 16; j++)
        {
            ch = *(base + i * 16 + j);
            if ((i * 16 + j) < sizeof(target))
                printf("%02x ", ch & 0xff);
            else
                printf("   ");
        }
        putchar('\b');
        putchar('|');
        for (j = 0; j < 16; j++)
        {
            ch = *(base + i * 16 + j);
            if ((i * 16 + j) < sizeof(target))
            {
                if (isalnum(ch) || isgraph(ch))
                    putchar(ch);
                else
                    putchar('.');
            }
        }
        putchar('\n');
    }
}