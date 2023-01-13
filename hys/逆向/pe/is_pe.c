#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <winnt.h>

void is_pe(WORD e_magic, DWORD signature);
void machine(WORD machine);
void time_date_stamp(DWORD time_date_stamp);
void characteristics(WORD characteristics);

int main()
{
    // 打开文件 helloworld1.exe KeyHook.dll
    char * path[] = {
        "helloworld.exe",
        "helloworld1.exe",
        "KeyHook.dll"
    };
    FILE *fp = fopen(path[2], "r");

    // 读取文件头
    IMAGE_DOS_HEADER dos_header;
    fread(&dos_header, sizeof(IMAGE_DOS_HEADER), 1, fp);

    printf("-----------------------------\n");
    printf("IMAGE_DOS_HEADER\n");
    printf("-----------------------------\n");
    // 输出e_magic, 0x5a4d, 将其转化为MZ
    printf("e_magic:0x%x:%c%c\n", dos_header.e_magic, dos_header.e_magic & 0xff, dos_header.e_magic >> 8);
    // 输出e_lfanew
    printf("e_lfanew:0x%08x\n", dos_header.e_lfanew);

    // 定位到nt头
    printf("-----------------------------\n");
    printf("IMAGE_NT_HEADERS32\n");
    printf("-----------------------------\n");
    fseek(fp, dos_header.e_lfanew, SEEK_SET);
    IMAGE_NT_HEADERS32 nt_headers;
    fread(&nt_headers, sizeof(IMAGE_NT_HEADERS32), 1, fp);

    // 输出Signature, 0x4550, 将其转化为PE
    printf("Signature:0x%x:%c%c\n", nt_headers.Signature, nt_headers.Signature & 0xff, nt_headers.Signature >> 8);
    is_pe(dos_header.e_magic, nt_headers.Signature);

    // nt文件头
    printf("-----------------------------\n");
    printf("IMAGE_FILE_HEADER\n");
    printf("-----------------------------\n");
    IMAGE_FILE_HEADER nt_file_header = nt_headers.FileHeader;
    printf("Machine:%04x\n", nt_file_header.Machine);
    machine(nt_file_header.Machine);
    printf("NumberOfSections:0x%04d\n", nt_file_header.NumberOfSections);
    time_date_stamp(nt_file_header.TimeDateStamp);
    printf("SizeOfOptionalHeader:0x%04x\n", nt_file_header.SizeOfOptionalHeader);
    characteristics(nt_file_header.Characteristics);

    // 根据nt_file_header.SizeOfOptionalHeader的大小来判断是32位还是64位
    if (nt_file_header.SizeOfOptionalHeader == 0xe0)
    {
        printf("-----------------------------\n");
        printf("IMAGE_OPTIONAL_HEADER32\n");
        printf("-----------------------------\n");
        IMAGE_OPTIONAL_HEADER32 nt_optional_header = nt_headers.OptionalHeader;
        printf("Magic:%04x\n", nt_optional_header.Magic);
        printf("IMAGE_OPTIONAL_HEADER32\n");
        printf("AddressOfEntryPoint:0x%08x\n", nt_optional_header.AddressOfEntryPoint);
        printf("ImageBase:0x%08x\n", nt_optional_header.ImageBase);
        printf("SectionAlignment:0x%08x\n", nt_optional_header.SectionAlignment);
        printf("FileAlignment:0x%08x\n", nt_optional_header.FileAlignment);
        printf("SizeOfImage:0x%08x\n", nt_optional_header.SizeOfImage);
        printf("SizeOfHeaders:0x%08x\n", nt_optional_header.SizeOfHeaders);
        printf("Subsystem:0x%04x\n", nt_optional_header.Subsystem);
        printf("NumberOfRvaAndSizes:0x%04x\n", nt_optional_header.NumberOfRvaAndSizes);
    }
    else if (nt_file_header.SizeOfOptionalHeader == 0xf0)
    {
        printf("-----------------------------\n");
        printf("IMAGE_OPTIONAL_HEADER64\n");
        printf("-----------------------------\n");
        PIMAGE_OPTIONAL_HEADER64 nt_optional_header = (PIMAGE_OPTIONAL_HEADER64)(&nt_headers.OptionalHeader);
        printf("Magic:%04x\n", nt_optional_header->Magic);
        printf("IMAGE_OPTIONAL_HEADER64\n");
        printf("AddressOfEntryPoint:0x%08x\n", nt_optional_header->AddressOfEntryPoint);
        printf("ImageBase:0x%016llx\n", nt_optional_header->ImageBase);
        printf("SectionAlignment:0x%08x\n", nt_optional_header->SectionAlignment);
        printf("FileAlignment:0x%08x\n", nt_optional_header->FileAlignment);
        printf("SizeOfImage:0x%08x\n", nt_optional_header->SizeOfImage);
        printf("SizeOfHeaders:0x%08x\n", nt_optional_header->SizeOfHeaders);
        printf("Subsystem:0x%04x\n", nt_optional_header->Subsystem);
        printf("Subsystem:0x%04x\n", nt_optional_header->Subsystem);
        printf("NumberOfRvaAndSizes:0x%04x\n", nt_optional_header->NumberOfRvaAndSizes);
    }

    // 节区头
    printf("-----------------------------\n");
    printf("IMAGE_SECTION_HEADER\n");
    printf("-----------------------------\n");

    // 定位到节区头
    if(nt_file_header.SizeOfOptionalHeader == 0xe0){
        fseek(fp, dos_header.e_lfanew + sizeof(IMAGE_NT_HEADERS32), SEEK_SET);
    }else if(nt_file_header.SizeOfOptionalHeader == 0xf0){
        fseek(fp, dos_header.e_lfanew + sizeof(IMAGE_NT_HEADERS64), SEEK_SET);
    }

    IMAGE_SECTION_HEADER section_header;
    
    for (int i = 0; i < nt_file_header.NumberOfSections; i++)
    {
        fread(&section_header, sizeof(IMAGE_SECTION_HEADER), 1, fp);
        printf("Name:%s\n", section_header.Name);
        printf("VirtualSize:0x%08x\n", section_header.Misc.VirtualSize);
        printf("VirtualAddress:0x%08x\n", section_header.VirtualAddress);
        printf("SizeOfRawData:0x%08x\n", section_header.SizeOfRawData);
        printf("PointerToRawData:0x%08x\n", section_header.PointerToRawData);
        printf("PointerToRelocations:0x%08x\n", section_header.PointerToRelocations);
        printf("PointerToLinenumbers:0x%08x\n", section_header.PointerToLinenumbers);
        printf("NumberOfRelocations:0x%04x\n", section_header.NumberOfRelocations);
        printf("NumberOfLinenumbers:0x%04x\n", section_header.NumberOfLinenumbers);
        printf("Characteristics:0x%08x\n", section_header.Characteristics);
    }


    fclose(fp);
}

void is_pe(WORD e_magic, DWORD signature)
{
    if (signature == 0x4550 & e_magic == 0x5a4d)
        printf("This is a PE file.\n");
    else
        printf("This is not a PE file.\n");
}

void machine(WORD machine)
{
    switch (machine)
    {
    case 0x014c:
        printf("This is intel 386 machine.\n");
        break;
    case 0x8664:
        printf("This is amd64 machine.\n");
        break;
    default:
        break;
    }
}

void time_date_stamp(DWORD time_date_stamp)
{
    // 1970-01-01 00:00:00
    time_t time = 0;
    time += time_date_stamp;
    printf("TimeDateStamp:%s", ctime(&time));
}

void characteristics(WORD characteristics)
{
    if (characteristics & 0x0002)
        printf("File is executable\n");
    if (characteristics & 0x2000)
        printf("File is dll\n");
}
