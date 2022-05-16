#include "mesignal.h"

void create_alarm(struct operation *op, struct config *config)
{
   signal(SIGALRM, create_alarm);
   if(op->status == 'C') {
   printf("request:%d status:C start:%d restaurant:%d rest_time:%d driver:%d driver_time:%d client:%d client_end_time:%d",
          op->id,
          op->start_time,
          op->receiving_rest,
          op->rest_time->tv_sec,
          op->receiving_driver,
          op->driver_time->tv_sec,
          op->requesting_client,
          op->client_end_time->tv_sec);
   }
   else {
      printf("request:%d status:%c", op->id, op->status);
   }
   alarm(config->alarm_time);

}