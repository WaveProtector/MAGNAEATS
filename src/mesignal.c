// Projeto - 2ª fase realizado pelo grupo 21:
// João Assis, fc56325
// José Brás, fc55449
// Ricardo Mateus, fc56366

#include <mesignal.h>

struct operation* op;

struct main_data *d;

struct semaphores *s;

void get_params(struct main_data *data, struct semaphores *sems)
{
   d = data;
   s = sems;
}

void sig_handler()
{
   while (op->id != 0 && *d->terminate != -1)
   {
      if (op->status == 'C')
      {
         printf("\nrequest:%d status:C start:%ld restaurant:%d rest_time:%ld driver:%d driver_time:%ld client:%d client_end_time:%ld",
                op->id,
                op->start_time.tv_sec,
                op->receiving_rest,
                op->rest_time.tv_sec,
                op->receiving_driver,
                op->driver_time.tv_sec,
                op->requesting_client,
                op->client_end_time.tv_sec);
      }
      else
      {
         printf("\nrequest:%d status:%c", op->id, op->status);
      }
      op++;
   }
}


void create_alarm(struct main_data *data, struct config *config)
{
   op = data->results;
   signal(SIGALRM, sig_handler);
   int alarm_time = config->alarm_time;
   int pid = fork();
   if(pid == 0){
      while (*data->terminate != 1)
      {
         op = data->results;
         alarm(alarm_time);
         pause();
      }
   }
      
}

void ctrlC(int sig)
{
   printf("Stop Execution \n");
   stop_execution(d, s); 

   // garantir que todos os processos capturem o sinal
   pid_t my_ppid = getppid();
   kill(my_ppid, SIGINT);
}

void signal_ctrlC(struct main_data *data, struct semaphores *sems)
{
   struct sigaction sa;
   sa.sa_handler = &ctrlC;
   sa.sa_flags = 0;
   sigemptyset(&sa.sa_mask);

   if (sigaction(SIGINT, &sa, NULL) == -1) {
      perror("main:");
      exit(-1);
   }
}