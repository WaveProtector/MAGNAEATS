#include "mesignal.h"

struct operation *op;

void sig_handler()
{
   while (op != NULL)
   {
      if (op->status == 'C')
      {
         printf("request:%d status:C start:%ld restaurant:%d rest_time:%ld driver:%d driver_time:%ld client:%d client_end_time:%ld",
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
         printf("request:%d status:%c", op->id, op->status);
      }
      op++;
   }
}

void create_alarm(struct main_data *data, struct config config)
{
   op = data->results;
   signal(SIGALRM, sig_handler);
   int alarm_time = config.alarm_time;

   while (1)
   {
      op = data->results;
      alarm(alarm_time);
      pause();
   }
}