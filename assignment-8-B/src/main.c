#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    bool valid;
    struct node *next[27];
} node;

typedef struct trie {
  node *root;
} trie;

int BUFFER = 256;

static int code(wchar_t w) {
    switch (w) {
        case 'a' :
            return 0;
        case 'b' :
            return 1;
        case 'c':
            return 2;
        case 'd':
            return 3;
        case 'e':
            return 4;
        case 'f':
            return 5;
        case 'g':
            return 6;
        case 'h':
            return 7;
        case 'i':
            return 8;
        case 'j':
            return 9;
        case 'k':
            return 10;
        case 'l':
            return 11;
        case 'm':
            return 12;
        case 'n':
            return 13;
        case 'o':
            return 14;
        case 'p':
            return 15;
        case 'r':
            return 16;
        case 's':
            return 17;
        case 't':
            return 18;
        case 'u':
            return 19;
        case 'v':
            return 20;
        case 'x':
            return 21;
        case 'y':
            return 22;
        case 'z':
            return 23;
        case 229 :
            return 24;
        case 228 :
            return 25;
        case 246 :
            return 26;
    }
    printf("strange character in word: %d\n", w);
    return -1;
}

static wchar_t code_to_character(int code) {
    switch(code) {
        case 0:
            return 'a';
        case 1:
            return 'b';
        case 2:
            return 'c';
        case 3:
            return 'd';
        case 4:
            return 'e';
        case 5:
            return 'f';
        case 6:
            return 'g';
        case 7:
            return 'h';
        case 8:
            return 'i';
        case 9:
            return 'j';
        case 10:
            return 'k';
        case 11:
            return 'l';
        case 12:
            return 'm';
        case 13:
            return 'n';
        case 14:
            return 'o';
        case 15:
            return 'p';
        case 16:
            return 'r';
        case 17:
            return 's';
        case 18:
            return 't';
        case 19:
            return 'u';
        case 20:
            return 'v';
        case 21:
            return 'x';
        case 22:
            return 'y';
        case 23:
            return 'z';
        case 24:
            return 229;
        case 25:
            return 228;
        case 26:
            return 246;
    }
    printf("strange character code: %d\n", code);
    return -1;
}

static int key_to_index(char key) {
    switch(key) {
        case '1': return 0;
        case '2': return 1;
        case '3': return 2;
        case '4': return 3;
        case '5': return 4;
        case '6': return 5;
        case '7': return 6;
        case '8': return 7;
        case '9': return 8;
    }
    return -1;
}

static char character_to_key(wchar_t w) {
    switch (w) {
        case 'a' :
        case 'b' :
        case 'c':
            return '1';
        case 'd':
        case 'e':
        case 'f':
            return '2';
        case 'g':
        case 'h':
        case 'i':
            return '3';
        case 'j':
        case 'k':
        case 'l':
            return '4';
        case 'm':
        case 'n':
        case 'o':
            return '5';
        case 'p':
        case 'r':
        case 's':
            return '6';
        case 't':
        case 'u':
        case 'v':
            return '7';
        case 'x':
        case 'y':
        case 'z':
            return '8';
        case 229 :
        case 228 :
        case 246 :
            return '9';
    }
    printf("(char to key) strange character in word: %d\n", w);
    return '-';
}

static char* text_to_keys(wchar_t* w) {
    char* text = (char*)malloc(sizeof(char)*100);
    int i = 0;
    while(*w != L'\0') {
        //printf("%S", w);
        printf("%d\n", code((int)*w)/3 + 1);
        char c = (char)(code(*w) / 3 + '1');
        text[i] = c;
        i++;
        w++;
    }
    return text;
}

node *add(node *nd, wchar_t *rest) {
    if (nd == NULL) {
        nd = (node*)malloc(sizeof(node));
        for (int i = 0; i < 27; i++ ) {
            nd->next[i] = NULL;
        }
        nd->valid = false;
    }
    if (rest[0] == '\n') {
        nd->valid = true;
    } else {
        int c = code((int)*rest);
        nd->next[c] = add(nd->next[c], (rest + 1));
    } 
    return nd;
}

trie *dict() {
    setlocale(LC_ALL,"en_US.UTF-8");
    // Open the dictionary in read mode
    FILE *fptr = fopen("kelly.txt", "r");
    if (fptr == NULL)
        return NULL;
    trie *kelly = (trie*)malloc(sizeof(trie));
    kelly->root = NULL;
    wchar_t ws[BUFFER];
    while (fgetws(ws, BUFFER, fptr) != NULL) {
        printf("adding %S", ws);
        kelly->root = add(kelly->root, ws);
    }
    fclose(fptr);
    return kelly;
}

void collect(node* nd, char* fullKey, wchar_t* sequence, int length, wchar_t** possible_words, int* count) {
    char key = fullKey[length];
    if (key == '\0') {
        if (nd->valid) {
            printf("Valid: %S\n", sequence);
            sequence[length] = L'\0';
            wchar_t* final = (wchar_t*)malloc(sizeof(wchar_t)*(length + 1));
            for(int i = 0; i <= length; i++) {
                final[i] = sequence[i];
            }
            possible_words[*count] = final;
            (*count)++;
        }
        printf("Returning: %S, (%d)\n", sequence, length);
        return;
    }   

    int idx = key_to_index(key);
    for (int i = 0; i < 3; i++) {
        int code = idx*3 + i;
        node* branch = nd->next[code];
        if(branch == NULL) {
            printf("Hit dead end: %S, %d\n", sequence, code);
            continue;
        }
        wchar_t nextChar = code_to_character(code);
        wchar_t* final = (wchar_t*)malloc(sizeof(wchar_t)*(length + 1));
        for(int i = 0; i <= length; i++) {
            final[i] = sequence[i];
        }
        final[length] = nextChar;
        printf("Checked: %S, (%d)\n", sequence, length);
        collect(branch, fullKey, final, length + 1, possible_words, count);
    }
}

wchar_t** decode(trie* dict, char* key) {
    wchar_t** possible_words = (wchar_t**)malloc(sizeof(wchar_t*)*1000);
    int count = 0;
    collect(dict->root, key, (wchar_t*)malloc(sizeof(wchar_t)*1), 0, possible_words, &count);
    return possible_words;
}

int main() {
    trie* tr = dict();
    char* keys = text_to_keys(L"ö");
    printf("%s", keys);
    wchar_t** results = decode(tr, keys);
    printf("%ls\n", *(results+1));
    return 0;
}