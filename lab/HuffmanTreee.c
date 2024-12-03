#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Huffman树结点结构体
typedef struct {
    char ch;
    int weight;
    int parent;
    int left;
    int right;
    /* data */
} HuffmanNode;

// Huffman编码结构体
typedef struct {
    char ch;
    char *code; // 动态分配编码字符串
} HuffmanCode;

typedef struct {
    int index;  // Huffman树节点的索引
    int weight; // 权值
} HeapNode;//堆节点定义

int compare(const void *a, const void *b) {
    return ((HeapNode *)a)->weight - ((HeapNode *)b)->weight;
}//堆比较函数（升序排列）

// 函数声明
void buildHuffmanTree(HuffmanNode *huffTree, int n);
void generateCodes(HuffmanNode *huffTree, HuffmanCode *codes, int n);
void encode(HuffmanCode *codes, int n, char *input);
void decode(HuffmanNode *huffTree, int root, char *encoded);
void printHuffmanTree(HuffmanNode *huffTree, int n);
void freeResources(HuffmanNode *huffTree, HuffmanCode *codes, int n);

// 全局变量（保存动态分配的内存）
HuffmanNode *huffTree = NULL;
HuffmanCode *codes = NULL;
int char_count = 0; // 记录字符数量

// 主程序
int main() {
    int choice;
    char input[256], encoded[256];
    FILE *file;

    do {
        printf("\n===== 哈夫曼编码工具 =====\n");
        printf("1. 输入字符及权值\n");
        printf("2. 查看Huffman编码\n");
        printf("3. 进行编码\n");
        printf("4. 进行译码\n");
        printf("5. 从文件读取输入\n");
        printf("6. 输出结果到文件\n");
        printf("7. 退出\n");
        printf("请选择操作: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: { // 手动输入字符及权值
            printf("请输入字符数量: ");
            scanf("%d", &char_count);

            // 动态分配内存
            huffTree = (HuffmanNode *)malloc((2 * char_count - 1) * sizeof(HuffmanNode));
            codes = (HuffmanCode *)malloc(char_count * sizeof(HuffmanCode));

            printf("请输入字符及其权值（格式: 字符 权值）:\n");
            for (int i = 0; i < char_count; i++) {
                getchar(); // 读取换行符
                scanf("%c %d", &huffTree[i].ch, &huffTree[i].weight);
                huffTree[i].parent = huffTree[i].left = huffTree[i].right = -1;
            }

            // 初始化额外节点
            for (int i = char_count; i < 2 * char_count - 1; i++) {
                huffTree[i].weight = 0;
                huffTree[i].parent = huffTree[i].left = huffTree[i].right = -1;
            }

            buildHuffmanTree(huffTree, char_count);
            generateCodes(huffTree, codes, char_count);
            printf("Huffman树和编码已生成！\n");
            break;
        }

        case 2: { // 查看Huffman树
            if (huffTree == NULL) {
                printf("请先输入字符及权值，生成Huffman树。\n");
            } else {
                printHuffmanTree(huffTree, 2 * char_count - 1);
            }
            break;
        }

        case 3: { // 进行编码
            if (codes == NULL) {
                printf("请先生成Huffman编码。\n");
            } else {
                printf("请输入要编码的字符串: ");
                scanf("%s", input);
                encode(codes, char_count, input);
            }
            break;
        }

        case 4: { // 进行译码
            if (huffTree == NULL) {
                printf("请先生成Huffman树。\n");
            } else {
                printf("请输入Huffman编码串进行译码: ");
                scanf("%s", encoded);
                decode(huffTree, 2 * char_count - 2, encoded);
            }
            break;
        }

        case 5: { // 从文件读取输入
            char filename[256];
            printf("请输入文件名: ");
            scanf("%s", filename);

            file = fopen(filename, "r");
            if (file == NULL) {
                printf("文件打开失败！\n");
            } else {
                fscanf(file, "%d", &char_count);

                // 动态分配内存
                huffTree = (HuffmanNode *)malloc((2 * char_count - 1) * sizeof(HuffmanNode));
                codes = (HuffmanCode *)malloc(char_count * sizeof(HuffmanCode));

                for (int i = 0; i < char_count; i++) {
                    fgetc(file); // 读取换行符
                    fscanf(file, "%c %d", &huffTree[i].ch, &huffTree[i].weight);
                    huffTree[i].parent = huffTree[i].left = huffTree[i].right = -1;
                }
                fclose(file);

                // 初始化额外节点
                for (int i = char_count; i < 2 * char_count - 1; i++) {
                    huffTree[i].weight = 0;
                    huffTree[i].parent = huffTree[i].left = huffTree[i].right = -1;
                }

                buildHuffmanTree(huffTree, char_count);
                generateCodes(huffTree, codes, char_count);
                printf("已从文件读取并生成Huffman树！\n");
            }
            break;
        }

        case 6: { // 输出结果到文件
            char filename[256];
            printf("请输入输出文件名: ");
            scanf("%s", filename);

            file = fopen(filename, "w");
            if (file == NULL) {
                printf("文件打开失败！\n");
            } else {
                fprintf(file, "字符及其Huffman编码:\n");
                for (int i = 0; i < char_count; i++) {
                    fprintf(file, "%c: %s\n", codes[i].ch, codes[i].code);
                }
                fclose(file);
                printf("结果已输出到文件！\n");
            }
            break;
        }

        case 7: { // 退出
            printf("程序结束，感谢使用！\n");
            freeResources(huffTree, codes, char_count);
            break;
        }

        default:
            printf("无效选项，请重新选择。\n");
        }
    } while (choice != 7);

    return 0;
}

// 构造Huffman树

void buildHuffmanTree(HuffmanNode *huffTree, int n) {
    int m = 2 * n - 1;
    HeapNode *heap = (HeapNode *)malloc(n * sizeof(HeapNode)); // 初始化堆
    int heapSize = n;

    // 初始化堆，将每个字符节点加入堆中
    for (int i = 0; i < n; i++) {
        heap[i].index = i;
        heap[i].weight = huffTree[i].weight;
    }

    // 构造初始堆
    qsort(heap, heapSize, sizeof(HeapNode), compare);

    // 构造哈夫曼树
    for (int i = n; i < m; i++) {
        // 取出堆中权值最小的两个节点
        HeapNode min1 = heap[0];
        heap[0] = heap[--heapSize]; // 删除堆顶
        qsort(heap, heapSize, sizeof(HeapNode), compare);

        HeapNode min2 = heap[0];
        heap[0] = heap[--heapSize]; // 删除堆顶
        qsort(heap, heapSize, sizeof(HeapNode), compare);

        // 合并两个最小节点，生成新节点
        huffTree[i].weight = min1.weight + min2.weight;
        huffTree[i].left = min1.index;
        huffTree[i].right = min2.index;
        huffTree[min1.index].parent = i;
        huffTree[min2.index].parent = i;

        // 将新节点插入堆
        heap[heapSize].index = i;
        heap[heapSize].weight = huffTree[i].weight;
        heapSize++;
        qsort(heap, heapSize, sizeof(HeapNode), compare);
    }

    free(heap); // 释放堆内存
}

// 生成Huffman编码
void generateCodes(HuffmanNode *huffTree, HuffmanCode *codes, int n) {
    char *temp = (char *)malloc(n * sizeof(char));
    for (int i = 0; i < n; i++) {
        int current = i, parent;
        int codeLen = 0;
        while ((parent = huffTree[current].parent) != -1) {
            temp[codeLen++] = (huffTree[parent].left == current) ? '0' : '1';
            current = parent;
        }
        temp[codeLen] = '\0';
        codes[i].ch = huffTree[i].ch;
        codes[i].code = (char *)malloc((codeLen + 1) * sizeof(char));
        for (int j = 0; j < codeLen; j++) {
            codes[i].code[j] = temp[codeLen - j - 1];
        }
        codes[i].code[codeLen] = '\0';
    }
    free(temp);
}

// 查看Huffman树
void printHuffmanTree(HuffmanNode *huffTree, int n) {
    printf("字符及其哈夫曼编码:\n");
    for (int i = 0; i < n; i++) {
        printf("%c: %s\n", codes[i].ch, codes[i].code);
    }
}

// 编码函数
void encode(HuffmanCode *codes, int n, char *input) {
    printf("编码结果: ");
    for (int i = 0; input[i] != '\0'; i++) {
        for (int j = 0; j < n; j++) {
            if (codes[j].ch == input[i]) {
                printf("%s", codes[j].code);
                break;
            }
        }
    }
    printf("\n");
}

// 译码函数
void decode(HuffmanNode *huffTree, int root, char *encoded) {
    int current = root;
    printf("译码结果: ");
    for (int i = 0; encoded[i] != '\0'; i++) {
        if (encoded[i] == '0') {
            current = huffTree[current].left;
        } else {
            current = huffTree[current].right;
        }

        if (huffTree[current].left == -1 && huffTree[current].right == -1) {
            printf("%c", huffTree[current].ch);
            current = root;
        }
    }
    printf("\n");
}

// 释放资源
void freeResources(HuffmanNode *huffTree, HuffmanCode *codes, int n) {
    if (huffTree) {
        free(huffTree);
    }
    if (codes) {
        for (int i = 0; i < n; i++) {
            free(codes[i].code);
        }
        free(codes);
    }
}
