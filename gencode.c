// 这个程序用于在Linux下生成一个简单的C语言模板文件(包括头文件和源文件)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>

#define FILE_NAME_SIZE 64

static void to_upper (char* dst, const char* src)
{
    for (; *src; src++, dst++) {
        if ((*src >= 'a') && (*src <= 'z')) {
            *dst = *src - 'a' + 'A';
        } else {
            *dst = *src;
        }
    }

    *dst = '\0';
}

static void minus2hyphen (char* dst, const char* src)
{
    for (; *src; src++, dst++) {
        if ('-' == *src) {
            *dst = '_';
        } else {
            *dst = *src;
        }
    }
}

static void version_history (void)
{
    printf("*\n");
    printf("* 版本历史\n");
    printf("* +----------------------------------------------------------------------------------------------------+\n");
    printf("* |    时间    |  版本  |                              描 述                              |    作者    |\n");
    printf("* +----------------------------------------------------------------------------------------------------+\n");
    printf("* | yyyy/mm/dd |  0.00  |                                                                 |            |\n");
    printf("* +----------------------------------------------------------------------------------------------------+\n");
    printf("*\n");
}

static void header (const char* filename, const char* author, const char* descript, const time_t* timep, const int type)
{
    printf("/*\n");
    printf("*********************************************************************************************************\n");
    printf("* 文件: %s\n", filename);
    printf("* 版本: V0.00\n");
    printf("* 创建: %s", ctime(timep));
    printf("* 作者: %s\n", author);
    printf("* 描述: %s\n", descript);
    if (0 == type) {
        version_history();
    }
    printf("*********************************************************************************************************\n");
    printf("*/\n");
}

int main (int argc, char* argv[])
{
    const char* filename = "";
    const char* author = "";
    const char* descript = "";

    char buffer[FILE_NAME_SIZE + 3]; // 3 = .x\0
    time_t time_cur;
    int fd;

    time(&time_cur);

    if ((argc < 2) || (argc > 4)) {
        printf("Useage: ./gencode filename [author [descript]]\n");
        exit(0);
    }

    int size = strlen(argv[1]);
    if (size > FILE_NAME_SIZE) {
        printf("Warning: file name is too long, limit to %d\n", FILE_NAME_SIZE);
        size = FILE_NAME_SIZE;
        argv[1][size] = '\0';
    }
    if (size >= 2) {
        if ('.' == argv[1][size - 2]) {
            char c = argv[1][size - 1];
            if (('h' == c) || ('H' == c) || ('c' == c) || ('C' == c)) {
                printf("Warning: ignore the filename's suffix\n");
                size -= 2;
                argv[1][size] = '\0';
            }
        }
    }
    if (size <= 0) {
        printf("Error: illegal filename argment\n");
        exit(0);
    }

    switch (argc) {
        case 4: descript = argv[3];
        case 3: author = argv[2];
        case 2: filename = argv[1];
        default: break;
    }

    // generate header file
    sprintf(buffer, "%s.h", filename);
    if ((fd = open(buffer, O_WRONLY | O_CREAT | O_TRUNC, 0600)) < 0) {
        perror("open");
        exit(0);
    }
    dup2(fd, 1);

    header(buffer, author, descript, &time_cur, 0);
    printf("\n");

    to_upper(buffer, filename);
    minus2hyphen(buffer, buffer);
    printf("#ifndef %s_H_\n", buffer);
    printf("#define %s_H_\n", buffer);
    printf("\n");
    printf("/* 包含头文件 -----------------------------------------------------------------------------------------*/\n");
    printf("#include \"types.h\"\n");
    printf("\n");
    printf("#ifdef __cplusplus\n");
    printf("  extern \"C\" {\n");
    printf("#endif\n");
    printf("\n");
    printf("/* 宏定义 ---------------------------------------------------------------------------------------------*/\n");
    printf("\n");
    printf("/* 数据类型声明 ---------------------------------------------------------------------------------------*/\n");
    printf("\n");
    printf("/* 函数声明 -------------------------------------------------------------------------------------------*/\n");
    printf("\n");
    printf("#ifdef __cplusplus\n");
    printf("  }\n");
    printf("#endif\n");
    printf("\n");
    printf("#endif /* %s_H_ */\n", buffer);
    printf("/********************************************* end of file *********************************************/\n");
    printf("\n");
    fflush(stdout);
    close(fd);

    // generate source file
    sprintf(buffer, "%s.c", filename);
    if ((fd = open(buffer, O_WRONLY | O_CREAT | O_TRUNC, 0600)) < 0) {
        perror("open");
        exit(0);
    }
    dup2(fd, 1);

    header(buffer, author, descript, &time_cur, 1);
    printf("\n");

    printf("/* 包含头文件 -----------------------------------------------------------------------------------------*/\n");
    printf("#include \"%s.h\"\n", filename);
    printf("\n");
    printf("/* 私有宏定义 -----------------------------------------------------------------------------------------*/\n");
    printf("\n");
    printf("/* 私有数据类型声明 -----------------------------------------------------------------------------------*/\n");
    printf("\n");
    printf("/* 私有全局变量定义 -----------------------------------------------------------------------------------*/\n");
    printf("\n");
    printf("/* 私有函数声明 ---------------------------------------------------------------------------------------*/\n");
    printf("\n");
    printf("/* 函数定义 -------------------------------------------------------------------------------------------*/\n");
    printf("\n");
    printf("/********************************************* end of file *********************************************/\n");
    printf("\n");
    fflush(stdout);
    close(fd);

    return 0;
}

