# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>

static FILE *fp = NULL;
static char *fullpath = NULL;

static void sig_handler(int signo)
{
  if (signo == SIGINT || signo == SIGKILL || signo == SIGTERM) {
      printf("received signal = %d\n", signo);
      if (fp)
          fclose(fp);
      /* use fullpath */
      if (fullpath)
          free(fullpath);
      exit(0);
  }
}

int main()
{
    int z = 0;

    signal(SIGINT, sig_handler);
    signal(SIGKILL, sig_handler);
    signal(SIGTERM, sig_handler);
    char* log_dir = getenv("CAF_APP_LOG_DIR");
    if (log_dir == NULL) {
        printf("Environement variable CAF_APP_LOG_DIR missing, exiting.\n");
        return -1;
    }
    size_t dir_len = strlen(log_dir);
    const char *logfile = "helloworld.log";
    /* + 2 because of the '/' and the terminating null character */
    fullpath = malloc(dir_len + strlen(logfile) + 2);
    if (fullpath == NULL) {
        return -1;
    }
    sprintf(fullpath, "%s/%s", log_dir, logfile);
    fp;
    fp = fopen(fullpath, "w+");
    while(1) {
        fprintf(fp, "[%i] Hello World from IOx App!!!\n", z++);
        sleep(5);
        fflush(fp);
    }
    fclose(fp);
    /* use fullpath */
    free(fullpath);

}