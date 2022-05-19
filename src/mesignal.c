#include "mesignal.h"

void create_alarm(struct operation *op, struct config *config)
{
   signal(SIGALRM, create_alarm);
   if(op->status == 'C') {
   printf("request:%d status:C start:%d restaurant:%d rest_time:%d driver:%d driver_time:%d client:%d client_end_time:%d",
          op->id,
          op->start_time,
          op->receiving_rest,
          op->rest_time,
          op->receiving_driver,
          op->driver_time,
          op->requesting_client,
          op->client_end_time);
   }
   else {
      printf("request:%d status:%c", op->id, op->status);
   }
   alarm(config->alarm_time);

}

void ctrlC (int sig, struct main_data* data, struct semaphores* sems) {
   printf("Stop Execution \n");
   stop_execution(data, sems);

   //garantir que todos os processos capturem o sinal
   pid_t my_ppid = getppid();
   kill(my_ppid, SIGINT); 
}

void signal_ctrlC(struct main_data* data, struct semaphores* sems) {

   struct sigaction sa;
   sa.sa_handler = ctrlC;
   sa.sa_flags = 0;
   sigemptyset(&sa.sa_mask);

   if (sigaction(SIGINT, &sa, NULL) == -1) {
      perror("main:");
      exit(-1); 
   }

}