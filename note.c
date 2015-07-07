//holds note functions
#include "note.h"

//alloc pointer for notes
Notes *create_notes(Notes* notes){
    
    notes = (Notes*) malloc(sizeof(*notes));
    return notes;
}

//return array of either tag or note strings from file
//! = tag
//@ = note
Notes *read_notes(Notes *notes){

    FILE *f = fopen("notes.txt", "r");

    int i = 0;
    int j;
    int c;
    int isEOF = 0;
    while(!isEOF){
        c = fgetc(f);
        switch(c){

            case '!':
                //tag
                for(j = 0; (c = fgetc(f)) != '\n' && c != EOF; j++) notes->tags[i][j] = c; 
                notes->tags[i][j] = '\0';
                break;

            case '@':
                //val
                for(j = 0; (c = fgetc(f)) != '\n' && c != EOF; j++) notes->vals[i][j] = c;
                notes->vals[i][j] = '\0';
                i++;
                break;

            default:
                //ignore this line
                while((c = fgetc(f)) != '\n' && c != EOF);
        }
        if(c == EOF) isEOF = 1;
    }
    fclose(f);

    //give array sizes
    notes->size = i;

    return notes;
}

//write data array back to file with sym in front
void write_notes(Notes *notes){
    
    FILE *f = fopen("notes.txt", "w");

    //disclaimer
    fputs("# Warning: If this file is edited the program may fail.\n"
    "# ! = tag\n# @ = note\n", f);

    int i;
    for(i = 0; i < notes->size - 1; i++){
        fprintf(f, "%c%s\n", '!', notes->tags[i]);
        fprintf(f, "%c%s\n", '@', notes->vals[i]);
    }
    //dont print newline on last entry 
    fprintf(f, "%c%s\n", '!', notes->tags[i]);
    fprintf(f, "%c%s", '@', notes->vals[i]);

    fclose(f);
}

//append one note one the end of notes
Notes *add_note(Notes *notes, char *tag, char *val){
    
    int i = notes->size;

    strcpy(notes->tags[i], tag);
    strcpy(notes->vals[i], val);

    notes->size++;

    return notes;
}

//search for note with val and del it, if val doesnt exist return null
Notes *del_note(Notes *notes, char *tag){
    
    int found = 0;
    int i;
    for(i = 0; i < notes->size; i++){
        if(strcmp(notes->tags[i], tag) == 0){
            found = 1;
            break;
        }
    }
    if(found){
        for(; i < notes->size - 1; i++){ 
            strcpy(notes->tags[i], notes->tags[i + 1]); 
            strcpy(notes->vals[i], notes->vals[i + 1]);
        }
        notes->tags[i][0] = '\0';
        notes->vals[i][0] = '\0';

        notes->size--;
        return notes;
    }
    else return NULL;
}
