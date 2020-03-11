#include "prog3.h"
#include <stdbool.h>

extern int TRACE;
extern int YES;
extern int NO;

#define INF 999

struct distance_table 
{
  int costs[4][4];
} dt3;

struct rtpkt packet3;

void printdt3(struct distance_table *dtptr);
void create_send_rtPack3(struct rtpkt toSendpkt); //BYT NAMN PÅ


/* students to write the following two routines, and maybe some others */

void rtinit3() 
{
  dt3.costs[0][0] = 7;
  dt3.costs[0][1] = INF;
  dt3.costs[0][2] = INF;
  dt3.costs[0][3] = INF;

  dt3.costs[1][0] = INF;
  dt3.costs[1][1] = INF;
  dt3.costs[1][2] = INF;
  dt3.costs[1][3] = INF;

  dt3.costs[2][0] = INF;
  dt3.costs[2][1] = INF;
  dt3.costs[2][2] = 2;
  dt3.costs[2][3] = INF;

  dt3.costs[3][0] = INF;
  dt3.costs[3][1] = INF;
  dt3.costs[3][2] = INF;
  dt3.costs[3][3] = INF;

  //Sets starting lowest value and sourceid for rtpacket
  packet3.mincost[0] = 7;
  packet3.mincost[1] = INF;
  packet3.mincost[2] = 2;
  packet3.mincost[3] = INF;
  packet3.sourceid = 3;
}


/* Sends and rtpacket to all recievers connected to node3*/
void create_send_rtPack3(struct rtpkt toSendpkt)
{
  //sets dest to node0 and sends
  toSendpkt.destid = 0;
  tolayer2(toSendpkt);

  //sets dest to node 2 and sens
  toSendpkt.destid = 2;
  tolayer2(toSendpkt);
}


void rtupdate3(struct rtpkt *rcvdpkt)
{
  printf("rdupdate3_\n");

  int s = rcvdpkt->sourceid;
  int sourceValue = dt3.costs[s][s];
  int newSum;
  bool hasChanged = false;

  for(int i = 0; i<4; i++)
  {
    //Sums up travelValue to source + current mincost in source
    newSum = sourceValue + rcvdpkt->mincost[i];

  //Checks if newsum is smaller than existing distance
    if(newSum < dt3.costs[i][s])
    {
      dt3.costs[i][s] = newSum;
      
      //Checks if the newly added value is also lowest num in row[i]
      if(newSum < packet3.mincost[i])
      {
        packet3.mincost[i] = newSum; //Updates value in mincost
        hasChanged = true; //Used to trigger creat_send_rtpack
      }
    }
  }

  if(hasChanged)
  {
    create_send_rtPack3(packet3);
  }
  printdt3(&dt3);

}


void printdt3(struct distance_table *dtptr)

  
{
  printf("             via     \n");
  printf("   D3 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 1|  %3d   %3d\n",dtptr->costs[1][0], dtptr->costs[1][2]);
  printf("     2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);

}







