#include <stdio.h>
#include <string.h>
int *getCharNum(char *Yourfile, int *total);
int main(){
    char Yourfile[30];
    // total[0]: 总行数  total[1]: 总字符数  total[2]: 总单词数
    int total[3] = {0, 0, 0};
    printf("Input file name: ");
    scanf("%s", Yourfile);
    if(getCharNum(Yourfile, total)){
        printf("Total: %d lines, %d words, %d chars\n", total[0], total[2], total[1]);
    }else{
        printf("Error!\n");
    }
    return 0;
}
/**
 * 统计文件的字符数、单词数、行数
 *
 * @param  Yourfile  文件名
 * @param  total  文件统计数据
 *
 * @return  成功返回统计数据，否则返回NULL
**/
int *getCharNum(char *Yourfile, int *total){
    FILE *fp;  // 指向文件的指针
    char buf[1008];  //缓冲区，存储读取到的每行的内容
    int bufLength;  // 缓冲区中实际存储的内容的长度
    int i;  // 当前读到缓冲区的第i个字符
    char c;  // 读取到的字符c
    int isLastBlank = 0;  // 上个字符是否是空格
    int charNum = 0;  // 当前行的字符数
    int wordNum = 0; // 当前行的单词数
    if( (fp=fopen(Yourfile, "rb")) == NULL ){
        perror(Yourfile);
        return NULL;
    }
    printf("line   words  chars\n");
    // 每次读取一行数据，保存到buf，每行最多只能有1000个字符
    while(fgets(buf, 1003, fp) != NULL){
        bufLength = strlen(buf);
        // 遍历缓冲区的内容
        for(i=0; i<bufLength; i++){
            c = buf[i];
            if( c==' ' || c=='\t'){  // 遇到空格
                !isLastBlank && wordNum++;  // 如果上个字符不是空格，那么单词数加1
                isLastBlank = 1;
            }else if(c!='\n'&&c!='\r'){  // 忽略换行符
                charNum++;  // 如果既不是换行符也不是空格，字符数加1
                isLastBlank = 0;
            }
        }
        !isLastBlank && wordNum++;  // 如果最后一个字符不是空格，那么单词数加1
        isLastBlank = 1;  // 每次换行重置为1
        // 一行结束，计算总字符数、总单词数、总行数:
        total[0]++;  // 总行数
        total[1] += charNum;  // 总字符数
        total[2] += wordNum;  // 总单词数
        printf("%-7d%-7d%d\n", total[0], wordNum, charNum);
        // 置零，重新统计下一行
        charNum = 0;
        wordNum = 0;
    }
    return total;
}