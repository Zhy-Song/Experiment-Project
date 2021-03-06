/**
 * @Author: Song-zy
 * @Date: 2021/11/7 21:12
 * @Description: 
 */

#include "stdio.h"
#include "stdlib.h"

#define MaxRuleNum 8
#define MaxVnNum 5
#define MaxVtNum 5
#define MaxStackDepth 20
#define MaxPLength 20
#define MaxStLength 50
struct pRNode /* 产生式右部结构 */
{
    int rCursor;
    struct pRNode *next;
};
struct pNode {
    int lCursor;
    int rLength; /* 右部长度 */
    struct pRNode *rHead; /* 右部结点头指针 */
};
char Vn[MaxVnNum + 1]; /* 非终结符集 */
int vnNum;
char Vt[MaxVtNum + 1]; /* 终结符集 */
int vtNum;
struct pNode P[MaxRuleNum];
int PNum;
char buffer[MaxPLength + 1];
char ch;
char st[MaxStLength]; /* 要分析的符号串 */
struct collectNode {
    int nVt;
    struct collectNode *next;
};
struct collectNode *first[MaxVnNum + 1]; /*first 集*/
struct collectNode *follow[MaxVnNum + 1]; /*follow 集*/
int analyseTable[MaxVnNum + 1][MaxVtNum + 1 + 1];
int analyseStack[MaxStackDepth + 1]; /* 分析栈 */
int topAnalyse; /* 分析栈顶 */
void Init();/* 初始化 */
int IndexCh(char ch);

void InputVt(); /* 输入终结符 */
void InputVn();/* 输入非终结符 */
void ShowChArray(char *collect, int num);/* 输出 Vn 或 Vt 的内容 */
void InputP();/* 产生式输入 */
bool CheckP(char *st);/* 判断产生式正确性 */
void First(int U);

void AddFirst(int U, int nCh); /* 加入 first 集*/
bool HaveEmpty(int nVn);

void Follow(int V);/* 计算 follow 集*/
void AddFollow(int V, int nCh, int kind);

void ShowCollect(struct collectNode **collect);/* 输出 first 或 follow
集*/
void FirstFollow();/* 计算 first 和 follow*/
void CreateAT();/* 构造预测分析表 */
void ShowAT();/* 输出分析表 */
void Identify(char *st);

void InitStack();

void ShowStack();

void Pop();

void Push(int r);

int main() {
    char todo, ch;
    Init();
    InputVn();
    InputVt();
    InputP();
    getchar();
    FirstFollow();
    printf(" 所得 first 集为： ");
    ShowCollect(first);
    printf(" 所得 follow 集为： ");
    ShowCollect(follow);
    CreateAT();
    ShowAT();
    todo = 'y';
    while ('y' == todo) {
        printf("\n 是否继续进行句型分析？ (y / n):");
        todo = getchar();
        while ('y' != todo && 'n' != todo) {
            printf("\n(y / n)? ");
            todo = getchar();
        }
        if ('y' == todo) {
            int i;
            InitStack();
            printf(" 请输入符号串 ( 以#结束 ) : ");
            ch = getchar();
            i = 0;
            while ('#' != ch && i < MaxStLength) {
                if (' ' != ch && '\n' != ch) {
                    st[i++] = ch;
                }
                ch = getchar();
            }
            if ('#' == ch && i < MaxStLength) {
                st[i] = ch;
                Identify(st);
            } else
                printf(" 输入出错！ \n");
        }
    }
    getchar();
}

void Init() {
    int i, j;
    vnNum = 0;
    vtNum = 0;
    PNum = 0;
    for (i = 0; i <= MaxVnNum; i++)
        Vn[i] = '\0';
    for (i = 0; i <= MaxVtNum; i++)
        Vt[i] = '\0';
    for (i = 0; i < MaxRuleNum; i++) {
        P[i].lCursor = NULL;
        P[i].rHead = NULL;
        P[i].rLength = 0;
    }
    PNum = 0;
    for (i = 0; i <= MaxPLength; i++)
        buffer[i] = '\0';
    for (i = 0; i < MaxVnNum; i++) {
        first[i] = NULL;
        follow[i] = NULL;
    }
    for (i = 0; i <= MaxVnNum; i++) {
        for (j = 0; j <= MaxVnNum + 1; j++)
            analyseTable[i][j] = -1;
    }
}

int IndexCh(char ch) {
    int n;
    n = 0; /*is Vn?*/
    while (ch != Vn[n] && '\0' != Vn[n])
        n++;
    if ('\0' != Vn[n])
        return 100 + n;
    n = 0; /*is Vt?*/
    while (ch != Vt[n] && '\0' != Vt[n])
        n++;
    if ('\0' != Vt[n])
        return n;
    return -1;
}

/* 输出 Vn 或 Vt 的内容 */
void ShowChArray(char *collect) {
    int k = 0;
    while ('\0' != collect[k]) {
        printf(" %c ", collect[k++]);
    }
    printf("\n");
}

/* 输入非终结符 */
void InputVn() {
    int inErr = 1;
    int n, k;
    char ch;
    while (inErr) {
        printf("\n请输入所有的非终结符,\n注意:");
        printf(" 请将开始符放在第一位,并以#号结束:");
        ch = ' ';
        n = 0;
        /* 初始化数组 */
        while (n < MaxVnNum) {
            Vn[n++] = '\0';
        }
        n = 0;
        while (('#' != ch) && (n < MaxVnNum)) {
            if (' ' != ch && '\n' != ch && -1 == IndexCh(ch)) {
                Vn[n++] = ch;
                vnNum++;
            }
            ch = getchar();
        }
        Vn[n] = '#'; /* 以"#" 标志结束用于判断长度是否合法 */
        k = n;
        if ('#' != ch) {
            if ('#' != (ch = getchar())) {
                while ('#' != (ch = getchar()));
                printf("\n 符号数目超过限制！ \n");
                inErr = 1;
                continue;
            }
        }
        /* 正确性确认，正确则，执行下下面，否则重新输入 */
        Vn[k] = '\0';
        ShowChArray(Vn);
        ch = ' ';
        while ('y' != ch && 'n' != ch) {
            if ('\n' != ch) {
                printf("输入正确确认 ?(y/n):");
            }
            scanf("%c", &ch);
        }
        if ('n' == ch) {
            printf(" 录入错误重新输入！ \n");
            inErr = 1;
        } else {
            inErr = 0;
        }
    }
}

/* 输入终结符 */
void InputVt() {
    int inErr = 1;
    int n, k;
    char ch;
    while (inErr) {
        printf("\n请输入所有的终结符,\n注意:");
        printf(" 以#号结束:");
        ch = ' ';
        n = 0;
        /* 初始化数组 */
        while (n < MaxVtNum) {
            Vt[n++] = '\0';
        }
        n = 0;
        while (('#' != ch) && (n < MaxVtNum)) {
            if (' ' != ch && '\n' != ch && -1 == IndexCh(ch)) {
                Vt[n++] = ch;
                vtNum++;
            }
            ch = getchar();
        }
        Vt[n] = '#';
        k = n;
        if ('#' != ch) {
            if ('#' != (ch = getchar())) {
                while ('#' != (ch = getchar()));
                printf("\n 符号数目超过限制！ \n");
                inErr = 1;
                continue;
            }
        }
        Vt[k] = '\0';
        ShowChArray(Vt);
        ch = ' ';
        while ('y' != ch && 'n' != ch) {
            if ('\n' != ch) {
                printf(" 输入正确确认 ?(y/n):");
            }
            scanf("%c", &ch);
        }
        if ('n' == ch) {
            printf(" 录入错误重新输入！ \n");
            inErr = 1;
        } else {
            inErr = 0;
        }
    }
}

/* 产生式输入 */
void InputP() {
    char ch;
    int i = 0, n, num;
    printf(" 请输入文法产生式的个数： ");
    scanf("%d", &num);
    PNum = num;
    getchar(); /* 消除回车符 */
    printf("\n 请输入文法的 %d个产生式 , 并以回车分隔每个产生式： ", num);
    printf("\n");
    while (i < num) {
        printf(" 第%d 个： ", i);
        /* 初始化 */
        for (n = 0; n < MaxPLength; n++)
            buffer[n] = '\0';
        /* 输入产生式串 */
        ch = ' ';
        n = 0;
        while ('\n' != (ch = getchar()) && n < MaxPLength) {
            if (' ' != ch)
                buffer[n++] = ch;
        }
        buffer[n] = '\0';
        if (CheckP(buffer)) {
            pRNode *pt, *qt;
            P[i].lCursor = IndexCh(buffer[0]);
            pt = (pRNode *) malloc(sizeof(pRNode));
            pt->rCursor = IndexCh(buffer[3]);
            pt->next = NULL;
            P[i].rHead = pt;
            n = 4;
            while ('\0' != buffer[n]) {
                qt = (pRNode *) malloc(sizeof(pRNode));
                qt->rCursor = IndexCh(buffer[n]);
                qt->next = NULL;
                pt->next = qt;
                pt = qt;
                n++;
            }
            P[i].rLength = n - 3;
            i++;
        } else
            printf(" 输入符号含非法在成分，请重新输入！ \n");
    }
}

/* 判断产生式正确性 */
bool CheckP(char *st) {
    int n;
    if (100 > IndexCh(st[0]))
        return false;
    if ('-' != st[1])
        return false;
    if ('>' != st[2])
        return false;
    for (n = 3; '\0' != st[n]; n++) {
        if (-1 == IndexCh(st[n]))
            return false;
    }
    return true;
}

void First(int U) {
    int i, j;
    for (i = 0; i < PNum; i++) {
        if (P[i].lCursor == U) {
            struct pRNode *pt;
            pt = P[i].rHead;
            j = 0;
            while (j < P[i].rLength) {
                if (100 > pt->rCursor) {
                    AddFirst(U, pt->rCursor);
                    break;
                } else {
                    if (NULL == first[pt->rCursor - 100]) {
                        First(pt->rCursor);
                    }
                    AddFirst(U, pt->rCursor);
                    if (!HaveEmpty(pt->rCursor)) {
                        break;
                    } else {
                        pt = pt->next;
                    }
                }
                j++;
            }
            if (j >= P[i].rLength) /* 当产生式右部都能推出空时 */
                AddFirst(U, -1);
        }
    }
}

/* 加入 first 集*/
void AddFirst(int U, int nCh) {
    struct collectNode *pt, *qt;
    int ch; /* 用于处理 Vn*/
    pt = NULL;
    qt = NULL;
    if (nCh < 100) {
        pt = first[U - 100];
        while (NULL != pt) {
            if (pt->nVt == nCh)
                break;
            else {
                qt = pt;
                pt = pt->next;
            }
        }
        if (NULL == pt) {
            pt = (struct collectNode *) malloc(sizeof(struct collectNode));
            pt->nVt = nCh;
            pt->next = NULL;
            if (NULL == first[U - 100]) {
                first[U - 100] = pt;
            } else {
                qt->next = pt; /*qt 指向 first 集的最后一个元素 */
            }
            pt = pt->next;
        }
    } else {
        pt = first[nCh - 100];
        while (NULL != pt) {
            ch = pt->nVt;
            if (-1 != ch) {
                AddFirst(U, ch);
            }
            pt = pt->next;
        }
    }
}

bool HaveEmpty(int nVn) {
    if (nVn < 100)
        return false;
    struct collectNode *pt;
    pt = first[nVn - 100];
    while (NULL != pt) {
        if (-1 == pt->nVt)
            return true;
        pt = pt->next;
    }
    return false;
}

void Follow(int V) {
    int i;
    struct pRNode *pt;
    if (100 == V) /* 当为初始符时 */
        AddFollow(V, -1, 0);
    for (i = 0; i < PNum; i++) {
        pt = P[i].rHead;
        while (NULL != pt && pt->rCursor != V)
            pt = pt->next;
        if (NULL != pt) {
            pt = pt->next;
            if (NULL == pt) {
                if (NULL == follow[P[i].lCursor - 100] && P[i].lCursor != V) {
                    Follow(P[i].lCursor);
                }
                AddFollow(V, P[i].lCursor, 0);
            } else {
                while (NULL != pt && HaveEmpty(pt->rCursor)) {
                    AddFollow(V, pt->rCursor, 1);
                    pt = pt->next;
                }
                if (NULL == pt) {
                    if (NULL == follow[P[i].lCursor - 100] && P[i].lCursor != V) {
                        Follow(P[i].lCursor);
                    }
                    AddFollow(V, P[i].lCursor, 0);
                } else {
                    AddFollow(V, pt->rCursor, 1);
                }
            }
        }
    }
}

void AddFollow(int V, int nCh, int kind) {
    struct collectNode *pt, *qt;
    int ch;
    pt = NULL;
    qt = NULL;
    if (nCh < 100) /* 为终结符时 */
    {
        pt = follow[V - 100];
        while (NULL != pt) {
            if (pt->nVt == nCh)
                break;
            else {
                qt = pt;
                pt = pt->next;
            }
        }
        if (NULL == pt) {
            pt = (struct collectNode *) malloc(sizeof(struct collectNode));
            pt->nVt = nCh;
            pt->next = NULL;
            if (NULL == follow[V - 100]) {
                follow[V - 100] = pt;
            } else {
                qt->next = pt; /*qt 指向 follow 集的最后一个元素 */
            }
            pt = pt->next;
        }
    } else {
        if (0 == kind) {
            pt = follow[nCh - 100];
            while (NULL != pt) {
                ch = pt->nVt;
                AddFollow(V, ch, 0);
                pt = pt->next;
            }
        } else {
            pt = first[nCh - 100];
            while (NULL != pt) {
                ch = pt->nVt;
                if (-1 != ch) {
                    AddFollow(V, ch, 1);
                }
                pt = pt->next;
            }
        }
    }
}

/* 输出 first 或 follow 集*/
void ShowCollect(struct collectNode **collect) {
    int i;
    struct collectNode *pt;
    i = 0;
    while (NULL != collect[i]) {
        pt = collect[i];
        printf("\n%c:\t", Vn[i]);
        while (NULL != pt) {
            if (-1 != pt->nVt) {
                printf(" %c", Vt[pt->nVt]);
            } else
                printf(" #");
            pt = pt->next;
        }
        i++;
    }
    printf("\n");
}

/* 计算 first 和 follow*/
void FirstFollow() {
    int i;
    i = 0;
    while ('\0' != Vn[i]) {
        if (NULL == first[i])
            First(100 + i);
        i++;
    }
    i = 0;
    while ('\0' != Vn[i]) {
        if (NULL == follow[i])
            Follow(100 + i);
        i++;
    }
}

/* 构造预测分析表 */
void CreateAT() {
    int i;
    struct pRNode *pt;
    struct collectNode *ct;
    for (i = 0; i < PNum; i++) {
        pt = P[i].rHead;
        while (NULL != pt && HaveEmpty(pt->rCursor)) {
            ct = first[pt->rCursor - 100];
            while (NULL != ct) {
                if (-1 != ct->nVt)
                    analyseTable[P[i].lCursor - 100][ct->nVt] = i;
                ct = ct->next;
            }
            pt = pt->next;
        }
        if (NULL == pt) {
            ct = follow[P[i].lCursor - 100];
            while (NULL != ct) {
                if (-1 != ct->nVt)
                    analyseTable[P[i].lCursor - 100][ct->nVt] = i;
                else
                    analyseTable[P[i].lCursor - 100][vtNum] = i;
                ct = ct->next;
            }
        } else {
            if (100 <= pt->rCursor) /* 不含空的非终结符 */
            {
                ct = first[pt->rCursor - 100];
                while (NULL != ct) {
                    analyseTable[P[i].lCursor - 100][ct->nVt] = i;
                    ct = ct->next;
                }
            } else /* 终结符或者空 */
            {
                if (-1 == pt->rCursor) {
                    ct = follow[P[i].lCursor - 100];
                    while (NULL != ct) {
                        if (-1 != ct->nVt)
                            analyseTable[P[i].lCursor - 100][ct->nVt] = i;
                        else /* 当含有 # 号时 */
                            analyseTable[P[i].lCursor - 100][vtNum] = i;
                        ct = ct->next;
                    }
                } else /* 为终结符 */
                {
                    analyseTable[P[i].lCursor - 100][pt->rCursor] = i;
                }
            }
        }
    }
}

/* 输出分析表 */
void ShowAT() {
    int i, j;
    printf(" 构造预测分析表如下： \n");
    printf("\t|\t");
    for (i = 0; i < vtNum; i++) {
        printf("%c\t", Vt[i]);
    }
    printf("#\t\n");
    printf("- - -\t|- - -\t");
    for (i = 0; i <= vtNum; i++)
        printf("- - -\t");
    printf("\n");
    for (i = 0; i < vnNum; i++) {
        printf("%c\t|\t", Vn[i]);
        for (j = 0; j <= vtNum; j++) {
            if (-1 != analyseTable[i][j])
                printf("R(%d)\t", analyseTable[i][j]);
            else
                printf("error\t");
        }
        printf("\n");
    }
}

void Identify(char *st) {
    int current, step, r; /*r 表使用的产生式的序号 */
    printf("\n%s 的分析过程： \n", st);
    printf(" 步骤 \t 分析符号栈 \t 当前指示字符 \t 使用产生式序号 \n");
    step = 0;
    current = 0;
    printf("%d\t", step);
    ShowStack();
    printf("\t\t%c\t\t- -\n", st[current]);
    while ('#' != st[current]) {
        if (100 > analyseStack[topAnalyse]) {
            if (analyseStack[topAnalyse] == IndexCh(st[current])) {
                Pop();
                current++;
                step++;
                printf("%d\t", step);
                ShowStack();
                printf("\t\t%c\t\t 出栈、后移 \n", st[current]);
            } else {
                printf("%c-%c 不匹配！ ", analyseStack[topAnalyse], st[current]);
                printf(" 此串不是此文法的句子！ \n");
                return;
            }
        } else /* 当为非终结符时 */
        {
            r = analyseTable[analyseStack[topAnalyse] -
                             100][IndexCh(st[current])];
            if (-1 != r) {
                Push(r);
                step++;
                printf("%d\t", step);
                ShowStack();
                printf("\t\t%c\t\t%d\n", st[current], r);
            } else {
                printf(" 此串不是此文法的句子！ \n");
                return;
            }
        }
    }
    if ('#' == st[current]) {
        if (0 == topAnalyse && '#' == st[current]) {
            step++;
            printf("%d\t", step);
            ShowStack();
            printf("\t\t%c\t\t 分析成功！ \n", st[current]);
            printf("%s 是给定文法的句子！ \n", st);
        } else {
            while (topAnalyse > 0) {
                if (100 > analyseStack[topAnalyse]) {
                    printf(" 此串不是此文法的句子！ \n");
                    return;
                } else {
                    r = analyseTable[analyseStack[topAnalyse] - 100][vtNum];
                    if (-1 != r) {
                        Push(r); /* 产生式右部代替左部，指示器不移动 */
                        step++;
                        printf("%d\t", step);
                        ShowStack();
                        if (0 == topAnalyse && '#' == st[current]) {
                            printf("\t\t%c\t\t 分析成功！ \n", st[current]);
                            printf("%s 是给定文法的句子！ \n", st);
                        } else
                            printf("\t\t%c\t\t%d\n", st[current], r);
                    } else {
                        printf(" 此串不是此文法的句子！ \n");
                        return;
                    }
                }
            }
        }
    }
}

/* 初始化栈及符号串 */
void InitStack() {
    int i;
    /* 分析栈的初始化 */
    for (i = 0; i < MaxStLength; i++)
        st[i] = '\0';
    analyseStack[0] = -1; /*#(-1) 入栈 */
    analyseStack[1] = 100; /* 初始符入栈 */
    topAnalyse = 1;
}

/* 显示符号栈中内容 */
void ShowStack() {
    int i;
    for (i = 0; i <= topAnalyse; i++) {
        if (100 <= analyseStack[i])
            printf("%c", Vn[analyseStack[i] - 100]);
        else {
            if (-1 != analyseStack[i])
                printf("%c", Vt[analyseStack[i]]);
            else
                printf("#");
        }
    }
}

/* 栈顶出栈 */
void Pop() {
    topAnalyse--;
}

void Push(int r) {
    int i;
    struct pRNode *pt;
    Pop();
    pt = P[r].rHead;
    if (-1 == pt->rCursor)
        return;
    topAnalyse += P[r].rLength;
    for (i = 0; i < P[r].rLength; i++) {
        analyseStack[topAnalyse - i] = pt->rCursor;/* 逆序入栈 */
        pt = pt->next;
    }
}