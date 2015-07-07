#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SM_CH_BUF 20
#define LG_CH_BUF 100
#define MAX_NOTES 50

typedef struct{

    char vals[MAX_NOTES][LG_CH_BUF];
    char tags[MAX_NOTES][LG_CH_BUF];
    int size;//size of arrays
} Notes;

Notes* create_notes(Notes *notes);
Notes *read_notes(Notes *notes);
void write_notes(Notes *notes);
Notes *add_note(Notes *notes, char *tag, char *val);
Notes *del_note(Notes *notes, char *tag);

#endif
