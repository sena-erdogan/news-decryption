#include<stdio.h>

void menu();

void read_news(char buffer[500], char file_path[11], int is_Only_Title); /* This function reads the news' title if is_Only_Title is 1 and reads the whole news if it is 0 */

void append_file(char* file_Path, char c); /* This fuction adds the previously read news' number at the and of the readed_news_id.txt file */

void read_magic_numbers(char buffer_magic[10], char buffer_news[500]); /* Decrypts the magic numbers */

double f_func(int x);

double g_func(double f(int x), int a);

int is_read(char* filepath, int i); /* If the news is read, returns 1 and if not, returns 0 */

int is_read(char* filepath, int i){

    int flag = 0; /* Flag is 0 at first */

    FILE *filep;
    filep = fopen(filepath, "r"); /* File is opened ony to read from it */

    while( !feof(filep) ){

        if(getc(filep) == i + 48 ){ /* The numbers in the file will be read according to the ASCII table so if there is a number in the file, the value we get from the file will be its value incremented by 48 */

            flag++; /* If the number we're looking for is in the file, then flag will be incremented by 1 */

        }

    }

    if( flag == 0 ){ /* If the number we're looking for was not in the file, flag will stay the same */

        return 0;

    }else{ /* If the number was in the file, flag will be incremented */

        return 1;

    }

    fclose(filep);

}

void read_news(char buffer[500], char file_path[11], int is_Only_Title){

    int i = 0;

    FILE *filep;

    filep = fopen(file_path, "r");

    if(is_Only_Title == 1){ /* Reading only the title of the news */

        fscanf(filep, "%[^\n]", buffer); /* The title of the news is only the first line of the file, so the file is scanned until the file pointer is on \n and that's assigned to buffer */

        printf("%s\n", buffer); /* buffer is printed */

    }else if(is_Only_Title == 0){ /* Reading only the news */

        while(!feof(filep)){ /* The file is read until EOF */

            buffer[i] = getc(filep); /* Read character is assigned to buffer */
            i++; /* The next element of the buffer array */

        }

        i--;

        buffer[i] = '\0'; /* The last element of the array is set to '\0' indicating that the array is finished*/

        printf("%s\n", buffer); /* buffer is printed to the terminal */

    }

    fclose(filep);

}

void append_file(char* file_path, char c){

    FILE *filep;
    filep = fopen(file_path,"a"); /* The file is opened on append mode so previous texts are protected */

    fprintf(filep, "%d", c); /* The integer value of input is printed at the end of the file */

    fclose(filep);

}

void read_magic_numbers(char buffer_magic[10], char buffer_news[500]){ 

    int i=0, j=0, new;
    double sum;

    char new_1[11] = "news/1.txt";
    char new_2[11] = "news/2.txt";
    char new_3[11] = "news/3.txt";
    char new_4[11] = "news/4.txt";

    FILE *filep;

    printf("Which news would you like to decrypt?:"); /* The news the user wants to decrypt is taken from the user */

    scanf("%d", &new);
        
    switch(new){ /* The news is printed and the file of that news is opened */

        case 1: read_news(buffer_news, new_1, 0); 
                filep = fopen("news/1.txt","r");
                                        
                break;

        case 2: read_news(buffer_news, new_2, 0);   
                filep = fopen("news/2.txt","r");                                 

                break;

        case 3: read_news(buffer_news, new_3, 0);  
                filep = fopen("news/3.txt","r");                                  

                break;

        case 4: read_news(buffer_news, new_4, 0); 
                filep = fopen("news/4.txt","r");                                   

                break;

    }    

    while(!feof(filep)){

            buffer_news[i] = getc(filep); /* All the characters the file contains are copied to the buffer array */
            i++;

        }

        buffer_news[i] = '\0'; /* At the end of the array, there is '\0' to show that the string is over */

        i = 0; /* i is assigned to 0 to be used again */

    while( buffer_news[i] != '\0' ){ 

        if(buffer_news[i] == '#'){ 

            buffer_magic[j] = buffer_news[ i + 1 ]; /* The character after # is assigned to the buffer_magic array */
            j++;

        }

    i++;

    }

    buffer_magic[j] = '\0';

    i = 0;

    while( buffer_magic[i] != '\0' ){

        sum += g_func(f_func, buffer_magic[i] - 48); /* The function is applied to all the magic numbers in the file and they are added together */

        i++;

    }

    switch(new){ /* The messgae is printed with the numbers the sum represents for used file */

        case 1: printf("Number of tests performed: %.2lf\n", sum);
            

                break;

        case 2: printf("Number of sick people: %.2lf\n", sum);
                                        

                break;

        case 3: printf("Number of deaths: %.2lf\n", sum);
                                       

                break;

        case 4: printf("Expected number of sick people: %.2lf\n", sum);
                                       

                break;

        }

        fclose(filep); 

}

double f_func(int x){

    return ((x*x*x)-(x*x)+2);

}

double g_func(double f(int x), int a){

    return ( f(a) * f(a) );

}

void menu(){

    char choice, ccommand; /* ccommand represents the commands that are character type */
    char buff[500], magic[10];
    char new_1[11] = "news/1.txt"; /* All file names are assigned to arrays to be used in the functions */
    char new_2[11] = "news/2.txt";
    char new_3[11] = "news/3.txt";
    char new_4[11] = "news/4.txt";
    int new, icommand, i=0; /* icommand represents the commands that are integer type */

    printf("**********Daily Press**********\n\nToday's news are listed for you :\n\n");

    printf("Title of 1. news:");
    read_news(buff, new_1, 1);

    printf("Title of 2. news:");
    read_news(buff, new_2, 1);

    printf("Title of 3. news:");
    read_news(buff, new_3, 1);

    printf("Title of 4. news:");
    read_news(buff, new_4, 1);

    printf("\n\nWhat do you want to do?\na.Read a new\nb.List the readed news\nc.Get decrypted information from the news\n");
    scanf(" %c", &choice);

    switch(choice){

        case 'a': printf("Which news do you want to read?:");
                  scanf("%d", &new);

                  printf("\n");

                  if( is_read("readed_news_id.txt", new) == 0 ){ /* If the file the user wants to read is not in the readed news' file, then it will be added at the end of the said file */
                      
                    append_file("readed_news_id.txt", new);

                    switch(new){ /* The news is printed */

                        case 1: read_news(buff, new_1, 0);

                                break;

                        case 2: read_news(buff, new_2, 0);

                                break;

                        case 3: read_news(buff, new_3, 0);

                                break;

                        case 4: read_news(buff, new_4, 0);

                                break;

                    }

                    printf("\nWould you like to continue? Yes(y)/No(n):\n");
                    scanf(" %c", &ccommand);

                    switch(ccommand){

                        case 'y': printf("\n\n");
                                  menu();

                                  break;

                        case 'n': printf("Good Bye!\n");

                                  break;

                    }

                    }else if( is_read("readed_news_id.txt", new ) == 1 ){

                        printf("This new is readed. Do you want to read again? Yes(1) / No(0):\n");
                        scanf("%d", &icommand);

                        if( icommand == 1){

                            switch(new){

                                case 1: read_news(buff, new_1, 0);

                                        break;

                                case 2: read_news(buff, new_2, 0);

                                        break;

                                case 3: read_news(buff, new_3, 0);

                                        break;

                                case 4: read_news(buff, new_4, 0);

                                        break;

                            }

                            printf("\nWould you like to continue? Yes(y)/No(n):\n");
                            scanf(" %c", &ccommand);

                            switch(ccommand){

                                case 'y': printf("\n\n");
                                          menu();

                                          break;

                                case 'n': printf("Good Bye!\n");

                                          break;

                            }

                        }else if( icommand == 0 ){

                            printf("\nWould you like to go back to the menu? Yes(y)/No(n):\n");
                            scanf(" %c", &ccommand);

                            switch(ccommand){

                                case 'y': printf("\n\n");
                                          menu();

                                        break;

                                case 'n': printf("Good Bye!\n");

                                        break;

                            }

                        }

                  }

                break;

        case 'b': printf("\n\nReaded news are listed below:\n");
                
                  FILE *filep;
                  filep = fopen("readed_news_id.txt","rt" );

                  new = getc(filep); /* The first character of the file is assigned to the new variable */

                  if(new == EOF){ /* If the character taken from the file is EOFi the file is empty therefore there are no readed news yet */

                      printf("There are no readed news.\n\n");

                  }else{

                      while(!feof(filep)){

                          printf("%d. new is readed\n", new - 48); /* new - 48 is printed since we took a character from the file and assigned it to an integer value so 
                                                                        the character will have the ascii value of the taken character */
                          new = getc(filep);

                      } 
                          
                  }

                  fclose(filep);

                  printf("\nDo you want to continue? Yes(y)/No(n):\n");
                  scanf(" %c", &ccommand);

                  switch(ccommand){

                      case 'y': printf("\n\n");
                                menu();

                                break;

                      case 'n': printf("Good Bye!\n");

                                break;

                    }

                break;

        case 'c': read_magic_numbers(magic, buff);

                  printf("\nDo you want to continue? Yes(y)/No(n):\n");
                  scanf(" %c", &ccommand);

                  switch(ccommand){

                      case 'y': printf("\n\n");
                                menu();

                                break;

                      case 'n': printf("Good Bye!\n");

                                break;

                            }
                    
                break;

        default: printf("Invalid command\n");
                 menu();

    }

}

void main(){ /* Since the main function contains of only the menu function, it doesn't need to return anything */

    menu();

}