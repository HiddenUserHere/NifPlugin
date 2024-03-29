
/*<html><pre>  -<a                             href="../libqhull/index.htm#TOC"
  >-------------------------------</a><a name="TOP">-</a>

   rbox.c
     rbox program for generating input points for qhull.

   notes:
     50 points generated for 'rbox D4'

*/

#include "libqhull_r/libqhull_r.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _MSC_VER  /* Microsoft Visual C++ -- warning level 4 */
#pragma warning( disable : 4706)  /* assignment within conditional function */
#endif

char prompt[]= "\n\
-rbox- generate various point distributions.  Default is random in cube.\n\
\n\
args (any order, space separated):                    Version: 2015/08/30 r\n\
  3000    number of random points in cube, lens, spiral, sphere or grid\n\
  D3      dimension 3-d\n\
  c       add a unit cube to the output ('c G2.0' sets size)\n\
  d       add a unit diamond to the output ('d G2.0' sets size)\n\
  l       generate a regular 3-d spiral\n\
  r       generate a regular polygon, ('r s Z1 G0.1' makes a cone)\n\
  s       generate cospherical points\n\
  x       generate random points in simplex, may use 'r' or 'Wn'\n\
  y       same as 'x', plus simplex\n\
  Pn,m,r  add point [n,m,r] first, pads with 0\n\
\n\
  Ln      lens distribution of radius n.  Also 's', 'r', 'G', 'W'.\n\
  Mn,m,r  lattice(Mesh) rotated by [n,-m,0], [m,n,0], [0,0,r], ...\n\
          '27 M1,0,1' is {0,1,2} x {0,1,2} x {0,1,2}.  Try 'M3,4 z'.\n\
  W0.1    random distribution within 0.1 of the cube's or sphere's surface\n\
  Z0.5 s  random points in a 0.5 disk projected to a sphere\n\
  Z0.5 s G0.6 same as Z0.5 within a 0.6 gap\n\
\n\
  Bn      bounding box coordinates, default %2.2g\n\
  h       output as homogeneous coordinates for cdd\n\
  n       remove command line from the first line of output\n\
  On      offset coordinates by n\n\
  t       use time as the random number seed(default is command line)\n\
  tn      use n as the random number seed\n\
  z       print integer coordinates, default 'Bn' is %2.2g\n\
";

/*--------------------------------------------
-rbox-  main procedure of rbox application
*/
int main(int argc, char **argv) {
  int return_status;
  qhT qh_qh;
  qhT *qh= &qh_qh;

  QHULL_LIB_CHECK_RBOX

  if (argc == 1) {
    printf(prompt, qh_DEFAULTbox, qh_DEFAULTzbox);
    return 1;
  }
  if (argc == 2 && strcmp(argv[1], "D4")==0)
    fprintf(stderr, "\nStarting the rbox smoketest for qhull.  An immediate failure indicates\nthat reentrant rbox was linked to non-reentrant routines.  An immediate\nfailure of qhull may indicate that qhull was linked to the wrong\nqhull library.  Also try 'rbox D4 | qhull T1'\n");

  qh_init_A(qh, stdin, stdout, stderr, argc, argv);  /*no qh_errexit, sets qh->qhull_command */
  return_status= qh_rboxpoints(qh, qh->qhull_command); /* Traps its own errors, qh_errexit_rbox() */
  return return_status;
}/*main*/

