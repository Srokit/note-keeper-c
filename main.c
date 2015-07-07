//holds main()
#include "main.h"

void print_notes(Notes *notes){
    int i;
    //if there is no notes say so and return
    if(notes->size == 0){
        puts("\nNo Notes!");
        return;
    }
    puts("\nNotes:\n");
    for(i = 0; i < notes->size; i++) 
        printf("\t-%s\n\n%s\n\n", notes->tags[i], notes->vals[i]);
}

//return 1 = add, 2 = del, 0 = exit
int input_choice(void){
    
    char input[SM_CH_BUF];

    while(1){
        printf("%s", "add, del, or exit\n>> ");
        fgets(input, SM_CH_BUF, stdin);
        
        //take off newline
        input[strlen(input) - 1] = '\0';
    
        if(strcmp(input, "add") == 0) return 1;
        else if(strcmp(input, "del") == 0) return 2;
        else if(strcmp(input, "exit") == 0) return 0;

        //if none of the ifs were true
        puts("Invalid input. Try again.\n");
    }
}

//0 = tag, 1 = val
char *input_tag_or_val(int choice, char *input){

    do{
        if(choice == 0)
            printf("%s", "Note Tag\n>>");   
        else
            printf("%s", "Note\n>> ");

    fgets(input, LG_CH_BUF, stdin);
    input[strlen(input) - 1] = '\0';

    //if nothing was entered ask again
    }while(strlen(input) == 0);

    return input;
}

int main(void){
    
    puts("\nNote Keeper\n-----------");

    //load notes in from file
    Notes *notes = create_notes(notes);
    read_notes(notes);
    
    while(1){
        print_notes(notes);
    
        //ask for if user wants to add, delete, or exit
        int choice = input_choice();

        char tag[LG_CH_BUF], val[LG_CH_BUF];
        switch(choice){
    
            case 0:
                //exit program
                free(notes);
                return 0;
            //add note
            case 1:

                input_tag_or_val(0, tag);
                input_tag_or_val(1, val);
                add_note(notes, tag, val);
                write_notes(notes);
                break;

            //del note
            default:

                input_tag_or_val(0, tag);
                if(del_note(notes, tag) == NULL){
                    puts("Did not find that note."); 
                }
                else write_notes(notes);
        }
    }
}
