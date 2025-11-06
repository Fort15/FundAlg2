#include "foo.h"
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void solve_and_write_string(char words[][82], int words_count, int words_len, FILE *out) {
    if (words_count == 0) return;
    
    if (words_count == 1) {
        fputs(words[0], out);
        fputc('\n', out);
        return;
    }
    
    int total_spaces_needed = 80 - words_len;
    int spaces_between_words = words_count - 1; 
    
    int base_spaces = total_spaces_needed / spaces_between_words;  
    int extra_spaces = total_spaces_needed % spaces_between_words; 
    

    for (int i = 0; i < words_count; i++) {
        fputs(words[i], out);
        
        if (i < words_count - 1) {
            for (int j = 0; j < base_spaces; j++) {
                fputc(' ', out);
            }
            
            if (i < extra_spaces) {
                fputc(' ', out);
            }
        }
    }
    fputc('\n', out);
}


Status same_files(const char *file1, const char *file2) {
    struct stat st1, st2;
    if (stat(file1, &st1) != 0) return STATUS_OK;    
    if (stat(file2, &st2) != 0) return STATUS_OK;    
    
    if ((st1.st_dev == st2.st_dev) && (st1.st_ino == st2.st_ino)) {
        return STATUS_SAME_FILES;
    }
    return STATUS_OK;
}

Status copy_file1_to_file2(FILE *in, FILE *out) {
    char *line = (char *)malloc(BUF_SIZE * sizeof(char));
    if (!line) return STATUS_ERROR_MEMORY;
    size_t current_size = BUF_SIZE;
    size_t len = 0;
    int c;

    while (1) {
        c = fgetc(in);

        if (c == EOF && len == 0) break;

        if (c != EOF) {
            if (len >= current_size - 2) {
                current_size *= 2;
                char *temp = (char *)realloc(line, current_size * sizeof(char));
                if (!temp) {
                    free(line);
                    return STATUS_ERROR_MEMORY;
                }
                line = temp;
            }

            line[len++] = (char)c;
        }
        if (c == '\n' || c == EOF) {
            if (len == 0 || (len == 1 && line[0] == '\n')) {
                len = 0;
                continue; 
            }

            int has_newline = (line[len - 1] == '\n');
            if (has_newline) {
                line[len - 1] = '\0';
                len--;
            } else {
                line[len] = '\0';   // EOF
            }   

            if (len < 80) { 
                size_t start_index = 0;
                while (start_index < len && isspace(line[start_index])) {
                    start_index++;
                }
                if (start_index == len) {
                    len = 0;
                    continue;
                }
                fputs(line + start_index, out); 
                
                if (has_newline || c == EOF) fputc('\n', out);
            } else {
                char words[82][82];
                int words_count = 0, words_len = 0;
                char current_word[82];
                int word_len = 0;

                int wrong_word = 0;

                for (size_t i = 0; i <= len; i++) {
                    char current_char = (i < len) ? line[i] : ' '; 
                    if (wrong_word && !isspace(current_char)) continue;
                    else wrong_word = 0;

                    if (!isspace(current_char)) {
                        if (word_len < 80) { 
                            current_word[word_len++] = current_char;
                        } else {
                            word_len = 0;
                            wrong_word = 1;
                            continue;
                        }
                    } else {
                        if (word_len > 0) {
                            current_word[word_len] = '\0';

                            int spaces_needed = words_count; 
                            int current_word_len = word_len;
                            int new_total_len = words_len + current_word_len + spaces_needed;
                            
                            if (words_count > 0 && new_total_len >= 80) {
                                solve_and_write_string(words, words_count, words_len, out);
                                words_count = 0;
                                words_len = 0;
                            }

                            strcpy(words[words_count++], current_word);
                            words_len += current_word_len;
                            word_len = 0;
                        }
                    }
                }

                if (words_count > 0) {
                    solve_and_write_string(words, words_count, words_len, out);
                }
            }

            len = 0;
        }
        if (c == EOF) break;
    }

    free(line);
    return STATUS_OK;
}

// Status copy_file1_to_file2(FILE *in, FILE *out) {
//     int c;
//     char words[82][82];
//     int words_count = 0, words_len = 0;

//     char current_word[82];
//     int word_len = 0;

//     while ((c = fgetc(in)) != EOF) {
//         if (!isspace(c)) {
//             if (word_len < 80) {
//                 current_word[word_len++] = (char)c;
//             } else {
//                 current_word[word_len++] = '\n';
//                 current_word[word_len] = '\0';
//                 fputs(current_word, out);
//                 current_word[0] = (char)c;
//                 word_len = 1;
//             }
//         } else {
//             if (word_len > 0) {
//                 current_word[word_len] = '\0';

//                 int new_words_len = words_len + word_len;
//                 int number_of_spaces = (words_count > 0) ? words_count : 0;
//                 if (words_count > 0 && new_words_len + number_of_spaces > 80) {
//                     solve_and_write_string(words, words_count, words_len, out);
//                     words_count = 0;
//                     words_len = 0;
//                 }

//                 strcpy(words[words_count++], current_word);
//                 words_len += word_len;
//                 word_len = 0;
//             }

//             if (c == '\n' && words_count > 0) {
//                 for (int i = 0; i < words_count; i++) {
//                     fputs(words[i], out);
//                     if (i < words_count - 1) {
//                         fputc(' ', out);
//                     }
//                 }
//                 fputc('\n', out);
//                 words_count = 0;
//                 words_len = 0;
//             }
//         }
//     }

//     if (word_len > 0) {
//         current_word[word_len] = '\0';
//         strcpy(words[words_count], current_word);
//         words_len += word_len;
//         words_count++;
//     }
        
//     if (words_count > 0) {
//         if (words_len + (words_count - 1) < 80) {
//             for (int i = 0; i < words_count; i++) {
//                 fputs(words[i], out);
//                 if (i < words_count - 1) {
//                     fputc(' ', out);
//                 }
//             }
//             fputc('\n', out);
//         } else {
//             solve_and_write_string(words, words_count, words_len, out);
//         }
//     }
    
//     return STATUS_OK;
// }