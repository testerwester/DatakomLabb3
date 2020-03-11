#include "prog3.h"
#include <string.h>
#include <stdbool.h>


extern int TRACE;
extern int YES;
extern int NO;

#define INF 999

struct distance_table 
{
    int costs[4][4];
} dt0;

struct rtpkt packet0;

void printdt0(struct distance_table *dtptr);
void create_send_rtPack0(struct rtpkt toSendpkt);

/* students to write the following two routines, and maybe some others */
void rtinit0() 
{
  //Initiates all values in distance_table
  dt0.costs[0][0] = 0;
  dt0.costs[0][1] = INF;
  dt0.costs[0][2] = INF;
  dt0.costs[0][3] = INF;

  dt0.costs[1][0] = INF;
  dt0.costs[1][1] = 1;
  dt0.costs[1][2] = INF;
  dt0.costs[1][3] = INF;

  dt0.costs[2][0] = INF;
  dt0.costs[2][1] = INF;
  dt0.costs[2][2] = 3;
  dt0.costs[2][3] = INF;

  dt0.costs[3][0] = INF;
  dt0.costs[3][1] = INF;
  dt0.costs[3][2] = INF;
  dt0.costs[3][3] = 7;

  //Sets starting lowest value and sourceid for rtpacket
  packet0.mincost[0] = 0;
  packet0.mincost[1] = 1;
  packet0.mincost[2] = 3;
  packet0.mincost[3] = 7;
  packet0.sourceid = 0;

  //Sends first update to initate program
  create_send_rtPack0(packet0);
}


/* Sends and rtpacket to all recievers connected to node0*/
void create_send_rtPack0(struct rtpkt toSendpkt)
{
  //Sends rtpackages to all nodes except node0
  for(int i = 1; i<4; i++)
  {
    toSendpkt.destid = i;
    tolayer2(toSendpkt);
  }
}
void rtupdate0(struct rtpkt *rcvdpkt)
{
  printf("rdupdate0_\n");

  int s = rcvdpkt->sourceid;
  int sourceValue = dt0.costs[s][s];
  int newSum;
  bool hasChanged = false;

  for(int i = 0; i<4; i++)
  {
    //Sums up travelValue to source + current mincost in source
    newSum = sourceValue + rcvdpkt->mincost[i];

    //Checks if newsum is smaller than existing distance
    if(newSum < dt0.costs[i][s])
    {
      dt0.costs[i][s] = newSum; //Sets new value in distance table
      
      //Checks if the newly added value is also lowest num in row[i]
      if(newSum < packet0.mincost[i])
      {
        packet0.mincost[i] = newSum; //Updates value in mincost
        hasChanged = true; //Used to trigger creat_send_rtpack
      }
    }
  }

  if(hasChanged)
  {
    create_send_rtPack0(packet0);
  }
  
  printdt0(&dt0); //Prints values

  
}

void printdt0(struct distance_table *dtptr)
{
    printf("                via     \n");
  printf("   D0 |    1     2    3 \n");
  printf("  ----|-----------------\n");
  printf("     1|  %3d   %3d   %3d\n",dtptr->costs[1][1], dtptr->costs[1][2],dtptr->costs[1][3]);
  printf("dest 2|  %3d   %3d   %3d\n",dtptr->costs[2][1], dtptr->costs[2][2],dtptr->costs[2][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][1], dtptr->costs[3][2],dtptr->costs[3][3]);
}
void linkhandler0(int linkid, int newcost)
/* called when cost from 0 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */

{

}
