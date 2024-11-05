#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void main()
{
    while (1)
    {

        int B;
        printf("Inserez le borne B pour visualiser le tracé de courbe:");
        scanf("%d", &B);

        char content[256];
        snprintf(content, sizeof(content),
                 "set samples 500\n"
                 "set title \"Sinus cardinal\"\n"
                 "set xlabel \"x\"\n"
                 "set ylabel \"sin(x) / x\"\n"
                 "set xrange [%d:%d]\n"
                 "set border\n"
                 "set grid\n"
                 "plot sin(x)/x\n",
                 B, B);

        // printf("B = %s\n", content);

        FILE *fptr;
        fptr = fopen("commandes.gp", "rw");
        fputs(content, fptr);
        fclose(fptr);

        pid_t p = fork();
        if (p < 0)
        {
            perror("fork fail");
            exit(1);
        }
        else if (p == 0)
        {
            // sleep(10);
            printf("Hello from Child!\n");
            fptr = fopen("commandes.gp", "rw");
            execlp("gnuplot", "-persist", "commandes.gp", NULL);
            fclose(fptr);
        }
        else
        {
            sleep(10);
            kill(p, SIGKILL);
        }
    }
}
