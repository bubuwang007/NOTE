### PE文件格式

PE 文件时Windows操作系统下使用的可执行文件格式。

是微软在UNIX平台的COFF (Common Object File Format) 基础上制作的。



#### PE文件种类

|     种类     |       扩展名       |
| :----------: | :----------------: |
|  可执行程序  |      exe、scr      |
|      库      | dll、ocx、cpl、drv |
|   驱动程序   |      sys、vxd      |
| 对象文件系列 |        obj         |

根据PE正式规范，编译结果OBJ文件也视为PE文件，但是OBJ文件本身不能以任何方式执行。



#### 基本结构

![img](https://bbs.kanxue.com/upload/attach/202110/835440_RKCWW7MPS69W8A7.jpg)

DOS头到节区头是PE头部分，合称PE体。

文件中使用偏移 (offset)，内存中使用VA (Virtual Address) 来表示位置。

文件加载到内存时，情况会发生变化 (节区的大小和位置等)。

文件的内容一般可分为代码 (.text)，数据 (.data)，资源 (.rsrc) 分别保存。

PE与各节区尾部存在一个NULL填充区域。为了提高文件处理、内存和网络包的处理效率，将代码对齐到某一个地址的倍数。

SectionAlignment指定了在内存中的节区对齐大小 (通常是0x1000)。

FileAlignment指定了在磁盘中节区对齐大小 (通常是0x400或者0x1000)。



#### VA&RVA

VA指的是进程虚拟内存的绝对地址，RVA是指从某个基准位置 (ImageBase，一般是0x40000) 开始的相对地址。
$$
{\rm RVA}+{\rm ImageBase} = {\rm VA}
$$
PE头内部信息大多数以RVA形式存在。

原因是当PE文件 (主要是dll) 加载到进程虚拟内存的特定位置时，该位置可能已经加载了其他PE文件 (dll)。此时需要重定位将其加载到其他空白的位置，若PE头使用的是VA，则无法正常访问。因此使用RVA来保存信息，这样即使发生了重定位，也能正常访问。

> 32位Windows OS中，每个进程分配有4GB虚拟内存，因此VA值范围为0x00000000~0xFFFFFFFF



#### PE头

PE头由许多结构体组成。

##### DOS头

~~~C
typedef struct _IMAGE_DOS_HEADER {      // DOS .EXE header
    WORD   e_magic;                     // Magic number DOS签名
    WORD   e_cblp;                      // Bytes on last page of file
    WORD   e_cp;                        // Pages in file
    WORD   e_crlc;                      // Relocations
    WORD   e_cparhdr;                   // Size of header in paragraphs
    WORD   e_minalloc;                  // Minimum extra paragraphs needed  0x0000
    WORD   e_maxalloc;                  // Maximum extra paragraphs needed	0xFFFF
    WORD   e_ss;                        // Initial (relative) SS value
    WORD   e_sp;                        // Initial SP value
    WORD   e_csum;                      // Checksum
    WORD   e_ip;                        // Initial IP value
    WORD   e_cs;                        // Initial (relative) CS value
    WORD   e_lfarlc;                    // File address of relocation table
    WORD   e_ovno;                      // Overlay number
    WORD   e_res[4];                    // Reserved words
    WORD   e_oemid;                     // OEM identifier (for e_oeminfo)
    WORD   e_oeminfo;                   // OEM information; e_oemid specific
    WORD   e_res2[10];                  // Reserved words
    LONG   e_lfanew;                    // File address of new exe header
  } IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER;
~~~

IMAGE_DOS_HEADER 一共64字节

![](C:\Users\Administrator\Desktop\NOTE\hys\逆向\PE结构.assets\image-20230108202934735.png)

主要有两个重要成员：

e_magic: DOS签名，0x5A4D -> ascii “MZ”

e_lflange:  NT头的偏移地址 -> DOS头最后一个long 0x00000100 ->NT头开始位置



##### DOS存根

在DOS头下面，是个可选项且大小不固定，没有DOS存根也能运行。



##### NT头

~~~c
typedef struct _IMAGE_NT_HEADERS {
    DWORD Signature;	//签名：0x00004550 PE
    IMAGE_FILE_HEADER FileHeader;	//文件头
    IMAGE_OPTIONAL_HEADER32 OptionalHeader;	//可选头
} IMAGE_NT_HEADERS32, *PIMAGE_NT_HEADERS32;
~~~

大小为0xF8，248个字节

###### NT文件头

~~~c
typedef struct _IMAGE_FILE_HEADER {
    WORD    Machine;
    WORD    NumberOfSections;
    DWORD   TimeDateStamp;
    DWORD   PointerToSymbolTable;
    DWORD   NumberOfSymbols;
    WORD    SizeOfOptionalHeader;
    WORD    Characteristics;
} IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;
~~~

**Machine**

~~~
#define IMAGE_FILE_MACHINE_UNKNOWN           0
#define IMAGE_FILE_MACHINE_TARGET_HOST       0x0001  // indicating we want to interact with the host and not a WoW guest.
#define IMAGE_FILE_MACHINE_I386              0x014c  // Intel 386.
#define IMAGE_FILE_MACHINE_R3000             0x0162  // MIPS little-endian, 0x160 big-endian
#define IMAGE_FILE_MACHINE_R4000             0x0166  // MIPS little-endian
#define IMAGE_FILE_MACHINE_R10000            0x0168  // MIPS little-endian
#define IMAGE_FILE_MACHINE_WCEMIPSV2         0x0169  // MIPS little-endian WCE v2
#define IMAGE_FILE_MACHINE_ALPHA             0x0184  // Alpha_AXP
#define IMAGE_FILE_MACHINE_SH3               0x01a2  // SH3 little-endian
#define IMAGE_FILE_MACHINE_SH3DSP            0x01a3
#define IMAGE_FILE_MACHINE_SH3E              0x01a4  // SH3E little-endian
#define IMAGE_FILE_MACHINE_SH4               0x01a6  // SH4 little-endian
#define IMAGE_FILE_MACHINE_SH5               0x01a8  // SH5
#define IMAGE_FILE_MACHINE_ARM               0x01c0  // ARM Little-Endian
#define IMAGE_FILE_MACHINE_THUMB             0x01c2  // ARM Thumb/Thumb-2 Little-Endian
#define IMAGE_FILE_MACHINE_ARMNT             0x01c4  // ARM Thumb-2 Little-Endian
#define IMAGE_FILE_MACHINE_AM33              0x01d3
#define IMAGE_FILE_MACHINE_POWERPC           0x01F0  // IBM PowerPC Little-Endian
#define IMAGE_FILE_MACHINE_POWERPCFP         0x01f1
#define IMAGE_FILE_MACHINE_IA64              0x0200  // Intel 64
#define IMAGE_FILE_MACHINE_MIPS16            0x0266  // MIPS
#define IMAGE_FILE_MACHINE_ALPHA64           0x0284  // ALPHA64
#define IMAGE_FILE_MACHINE_MIPSFPU           0x0366  // MIPS
#define IMAGE_FILE_MACHINE_MIPSFPU16         0x0466  // MIPS
#define IMAGE_FILE_MACHINE_AXP64             IMAGE_FILE_MACHINE_ALPHA64
#define IMAGE_FILE_MACHINE_TRICORE           0x0520  // Infineon
#define IMAGE_FILE_MACHINE_CEF               0x0CEF
#define IMAGE_FILE_MACHINE_EBC               0x0EBC  // EFI Byte Code
#define IMAGE_FILE_MACHINE_AMD64             0x8664  // AMD64 (K8)
#define IMAGE_FILE_MACHINE_M32R              0x9041  // M32R little-endian
#define IMAGE_FILE_MACHINE_ARM64             0xAA64  // ARM64 Little-Endian
#define IMAGE_FILE_MACHINE_CEE               0xC0EE
~~~

一般32位编译出来是 0x014c -> Intel 386

64位编译出来是 0x8664 -> // AMD64 (K8)



**NumberOfSections**

文件中存在的节区数量，该值必须大于0，当定义的节区与实际节区数不符时，将发生运行错误。



**SizeOfOptionalHeader**

NT文件头的最后一个成员为IMAGE_OPTIONAL_HEADER32，SizeOfOptionalHeader用来指出IMAGE_OPTIONAL_HEADER32的长度。由于IMAGE_OPTIONAL_HEADER32大小已经确定，PE32+格式中使用IMAGE_OPTIONAL_HEADER64结构体，两者的尺寸不同，所以需要在SizeOfOptionalHeader中明确指出结构体的大小。



**Characteristics**

~~~c
#define IMAGE_FILE_RELOCS_STRIPPED           0x0001  // Relocation info stripped from file.
#define IMAGE_FILE_EXECUTABLE_IMAGE          0x0002  // File is executable  (i.e. no unresolved external references).
#define IMAGE_FILE_LINE_NUMS_STRIPPED        0x0004  // Line nunbers stripped from file.
#define IMAGE_FILE_LOCAL_SYMS_STRIPPED       0x0008  // Local symbols stripped from file.
#define IMAGE_FILE_AGGRESIVE_WS_TRIM         0x0010  // Aggressively trim working set
#define IMAGE_FILE_LARGE_ADDRESS_AWARE       0x0020  // App can handle >2gb addresses
#define IMAGE_FILE_BYTES_REVERSED_LO         0x0080  // Bytes of machine word are reversed.
#define IMAGE_FILE_32BIT_MACHINE             0x0100  // 32 bit word machine.
#define IMAGE_FILE_DEBUG_STRIPPED            0x0200  // Debugging info stripped from file in .DBG file
#define IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP   0x0400  // If Image is on removable media, copy and run from the swap file.
#define IMAGE_FILE_NET_RUN_FROM_SWAP         0x0800  // If Image is on Net, copy and run from the swap file.
#define IMAGE_FILE_SYSTEM                    0x1000  // System File.
#define IMAGE_FILE_DLL                       0x2000  // File is a DLL.
#define IMAGE_FILE_UP_SYSTEM_ONLY            0x4000  // File should only be run on a UP machine
#define IMAGE_FILE_BYTES_REVERSED_HI         0x8000  // Bytes of machine word are reversed.
~~~

重点：

0x0002 是否可执行

0x2000 是否是dll



##### NT可选头

~~~c
typedef struct _IMAGE_DATA_DIRECTORY {
    DWORD   VirtualAddress;
    DWORD   Size;
} IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;

#define IMAGE_NUMBEROF_DIRECTORY_ENTRIES    16

//
// Optional header format.
//

typedef struct _IMAGE_OPTIONAL_HEADER {
    //
    // Standard fields.
    //

    WORD    Magic;
    BYTE    MajorLinkerVersion;
    BYTE    MinorLinkerVersion;
    DWORD   SizeOfCode;
    DWORD   SizeOfInitializedData;
    DWORD   SizeOfUninitializedData;
    DWORD   AddressOfEntryPoint;
    DWORD   BaseOfCode;
    DWORD   BaseOfData;

    //
    // NT additional fields.
    //

    DWORD   ImageBase;
    DWORD   SectionAlignment;
    DWORD   FileAlignment;
    WORD    MajorOperatingSystemVersion;
    WORD    MinorOperatingSystemVersion;
    WORD    MajorImageVersion;
    WORD    MinorImageVersion;
    WORD    MajorSubsystemVersion;
    WORD    MinorSubsystemVersion;
    DWORD   Win32VersionValue;
    DWORD   SizeOfImage;
    DWORD   SizeOfHeaders;
    DWORD   CheckSum;
    WORD    Subsystem;
    WORD    DllCharacteristics;
    DWORD   SizeOfStackReserve;
    DWORD   SizeOfStackCommit;
    DWORD   SizeOfHeapReserve;
    DWORD   SizeOfHeapCommit;
    DWORD   LoaderFlags;
    DWORD   NumberOfRvaAndSizes;
    IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
} IMAGE_OPTIONAL_HEADER32, *PIMAGE_OPTIONAL_HEADER32;

typedef struct _IMAGE_OPTIONAL_HEADER64 {
    WORD        Magic;
    BYTE        MajorLinkerVersion;
    BYTE        MinorLinkerVersion;
    DWORD       SizeOfCode;
    DWORD       SizeOfInitializedData;
    DWORD       SizeOfUninitializedData;
    DWORD       AddressOfEntryPoint;
    DWORD       BaseOfCode;
    ULONGLONG   ImageBase;
    DWORD       SectionAlignment;
    DWORD       FileAlignment;
    WORD        MajorOperatingSystemVersion;
    WORD        MinorOperatingSystemVersion;
    WORD        MajorImageVersion;
    WORD        MinorImageVersion;
    WORD        MajorSubsystemVersion;
    WORD        MinorSubsystemVersion;
    DWORD       Win32VersionValue;
    DWORD       SizeOfImage;
    DWORD       SizeOfHeaders;
    DWORD       CheckSum;
    WORD        Subsystem;
    WORD        DllCharacteristics;
    ULONGLONG   SizeOfStackReserve;
    ULONGLONG   SizeOfStackCommit;
    ULONGLONG   SizeOfHeapReserve;
    ULONGLONG   SizeOfHeapCommit;
    DWORD       LoaderFlags;
    DWORD       NumberOfRvaAndSizes;
    IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
} IMAGE_OPTIONAL_HEADER64, *PIMAGE_OPTIONAL_HEADER64;
~~~

**magic**

IMAGE_OPTIONAL_HEADER32 : 0x10B

IMAGE_OPTIONAL_HEADER64 : 0x20B



### 参考

[看雪: Win PE系列之PE头解析](https://bbs.kanxue.com/thread-269719.htm) 

逆向工程核心原理

[知乎](https://zhuanlan.zhihu.com/p/517297051)