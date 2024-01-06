#include <stdio.h>
#include <string.h>

int main() {
    char seq[100000];                                                              // Don't know how to make it work without giving it a value
    printf("Welcome to the most basic ORF finder!\nFeed me sequences: ");

    while (scanf("%s", seq) == 1) {
        float directionality;
        printf("What is the directionality? \nFor 5' --> 3', type: 0\nFor 3' --> 5', type: 1\n");
        scanf("%f", &directionality);
        if(directionality != 0 && directionality != 1){
            printf("You have entered an invalid directionality, please rerun the program and enter a valid value.");
            break;
        }

        int i;
        int length = strlen(seq);
        int start = 0;
        int c_c = 0;

        if (directionality == 1){
            char rev_seq[length];
            for (i = 0; i < length; i++) {
                rev_seq[i] = seq[i];
            }
            for (i = 0; i < length; i++) {
                seq[length - 1 - i] = rev_seq[i];
            }
        }

        for (i = 0; i < length; i += 1) {
            char codon[4];
            if (i == 0) {

                codon[0] = seq[i];
                codon[1] = seq[i + 1];
                codon[2] = seq[i + 2];
                codon[3] = '\0';

                if ((strcmp(codon, "ATG") == 0 &&
                     start == 0))
                {
                    printf("Starting codon found\n");
                    start += 1;
                    i += 2;
                }

                if (start != 0) {
                    c_c += 1;
                    printf("Codon %d: %s\n", c_c, codon);
                }
            } else if (start == 0) {

                codon[0] = codon[1];
                codon[1] = codon[2];
                codon[2] = seq[i + 2];
                codon[3] = '\0';

                if ((strcmp(codon, "ATG") == 0)) {
                    printf("Starting codon found\n");
                    start += 1;
                    i += 2;
                }

                if (start != 0) {
                    c_c += 1;
                    printf("Codon %d: %s\n", c_c, codon);
                }

            }
            else {

                codon[0] = seq[i];
                codon[1] = seq[i + 1];
                codon[2] = seq[i + 2];
                codon[3] = '\0';


                if ((strcmp(codon, "TAA") == 0 || strcmp(codon, "TAG") == 0 ||
                     strcmp(codon, "TGA") == 0)) {
                    printf("Stop codon %s found\n", codon);
                    printf("Feed me more sequences: ");
                    break;
                }

                c_c += 1;
                printf("Codon %d: %s\n", c_c, codon);

                i += 2;
            }

            int remaining = (length - 1) - i;
            if (remaining > 0 && remaining < 3) {
                printf("No stop codon was found and the remaining nucleotides aren't in multiple of three\n");
                printf("Feed me more sequences: ");                                 // Feed me Seymour #2
                break;
            }

        }
    }

    return 0;
}
