#include "prog3.h"
#include <stdbool.h>


extern int TRACE;
extern int YES;
extern int NO;

#define INF 999

struct distance_table 
{
  int costs[4][4];
} dt2;

struct rtpkt packet2;



void printdt2(struct distance_table *dtptr);
void create_send_rtPack2(struct rtpkt toSendpkt);


/* students to write the following two routines, and maybe some others */

void rtinit2() 
{
  dt2.costs[0][0] = 3;
  dt2.costs[0][1] = INF;
  dt2.costs[0][2] = INF;
  dt2.costs[0][3] = INF;

  dt2.costs[1][0] = INF;
  dt2.costs[1][1] = 1;
  dt2.costs[1][2] = INF;
  dt2.costs[1][3] = INF;

  dt2.costs[2][0] = INF;
  dt2.costs[2][1] = INF;
  dt2.costs[2][2] = 0;
  dt2.costs[2][3] = INF;

  dt2.costs[3][0] = INF;
  dt2.costs[3][1] = INF;
  dt2.costs[3][2] = INF;
  dt2.costs[3][3] = 2;

  //Sets starting lowest value and sourceid for rtpacket
  packet2.mincost[0] = 3;
  packet2.mincost[1] = 1;
  packet2.mincost[2] = 0;
  packet2.mincost[3] = 2;
  packet2.sourceid = 2;
}

/* Sends and rtpacket to all recievers connected to node2*/
void create_send_rtPack2(struct rtpkt toSendpkt)
{
  //Sets dest to 0 and sends to node0
  toSendpkt.destid = 0;
  tolayer2(toSendpkt);

  //sets dest to 1 and sends to node1
  toSendpkt.destid = 1;
  tolayer2(toSendpkt);

  //Sets dest to 3 and sends to node 3
  toSendpkt.destid = 3;
  tolayer2(toSendpkt);
}


void rtupdate2(struct rtpkt *rcvdpkt)
{
  printf("rdupdate2_\n");

  int s = rcvdpkt->sourceid;
  int sourceValue = dt2.costs[s][s];
  int newSum;
  bool hasChanged = false;

  for(int i = 0; i<4; i++)
  {
    //Sums up travelValue to source + current mincost in source
    newSum = sourceValue + rcvdpkt->mincost[i];

    //Checks if newsum is smaller than existing distance
    if(newSum < dt2.costs[i][s])
    {
      dt2.costs[i][s] = newSum;
      
      //Checks if the newly added value is also lowest num in row[i]
      if(newSum < packet2.mincost[i])
      {
        packet2.mincost[i] = newSum; //Updates value in mincost
        hasChanged = true; //Used to trigger creat_send_rtpack
      }
    }
  }

  if(hasChanged)
  {
    create_send_rtPack2(packet2);
  }
  printdt2(&dt2); //Prints values
}


void printdt2(struct distance_table *dtptr)

  
{
  printf("                via     \n");
  printf("   D2 |    0     1    3 \n");
  printf("  ----|-----------------\n");
  printf("     0|  %3d   %3d   %3d\n",dtptr->costs[0][0],
	 dtptr->costs[0][1],dtptr->costs[0][3]);
  printf("dest 1|  %3d   %3d   %3d\n",dtptr->costs[1][0],
	 dtptr->costs[1][1],dtptr->costs[1][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][0],
	 dtptr->costs[3][1],dtptr->costs[3][3]);
}







