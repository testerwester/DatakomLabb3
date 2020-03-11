#include "prog3.h"
#include <stdbool.h>


extern int TRACE;
extern int YES;
extern int NO;

#define INF 999

struct distance_table 
{
  int costs[4][4];
} dt1;

struct rtpkt packet1;

void printdt1(struct distance_table *dtptr);
void create_send_rtPack1(struct rtpkt toSendpkt);


/* students to write the following two routines, and maybe some others */


void rtinit1()
{
  dt1.costs[0][0] = 1;
  dt1.costs[0][1] = INF;
  dt1.costs[0][2] = INF;
  dt1.costs[0][3] = INF;

  dt1.costs[1][0] = INF;
  dt1.costs[1][1] = INF;
  dt1.costs[1][2] = INF;
  dt1.costs[1][3] = INF;

  dt1.costs[2][0] = INF;
  dt1.costs[2][1] = INF;
  dt1.costs[2][2] = 1;
  dt1.costs[2][3] = INF;

  dt1.costs[3][0] = INF;
  dt1.costs[3][1] = INF;
  dt1.costs[3][2] = INF;
  dt1.costs[3][3] = INF;

  //Sets starting lowest value and sourceid for rtpacket
  packet1.mincost[0] = 1;
  packet1.mincost[1] = 0;
  packet1.mincost[2] = 1;
  packet1.mincost[3] = INF;
  packet1.sourceid = 1;

  
}

/* Sends and rtpacket to all recievers connected to node1*/
void create_send_rtPack1(struct rtpkt toSendpkt)
{
  //sets dest to 0 and sends to node0
  toSendpkt.destid = 0;
  tolayer2(toSendpkt);

  //Sets dest to 2 and sends to node2
  toSendpkt.destid = 2;
  tolayer2(toSendpkt);
}


void rtupdate1(struct rtpkt *rcvdpkt)
{
  printf("rdupdate1_\n");
  int s = rcvdpkt->sourceid;
  int sourceValue = dt1.costs[s][s];
  int newSum;
  bool hasChanged = false;

  for(int i = 0; i<4; i++)
  {
    //Sums up travelValue to source + current mincost in source
    newSum = sourceValue + rcvdpkt->mincost[i];

    //Checks if newsum is msaller than existing distance
    if(newSum < dt1.costs[i][s])
    {
      dt1.costs[i][s] = newSum; //Sets new value in distance table

      //Checks if the newly added value is also lowest num in row[i]
      if(newSum < packet1.mincost[i])
      {
        packet1.mincost[i] = newSum; //Updates value in mincost
        hasChanged = true; //Used to trigger creat_send_rtpack
      }
    }
  }


  if(hasChanged)
  {
    create_send_rtPack1(packet1);
  }
  printdt1(&dt1);

  

}


void printdt1(struct distance_table *dtptr)

  
{
  printf("             via   \n");
  printf("   D1 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
  printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);

}



void linkhandler1(int linkid, int newcost)

/* called when cost from 1 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
	
{
}


