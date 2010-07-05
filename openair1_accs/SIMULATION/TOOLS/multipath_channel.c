#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "defs.h"
#include "SIMULATION/RF/defs.h"

#define MAX_CHANNEL_LENGTH 200
struct complex a[4][4][MAX_CHANNEL_LENGTH];

void multipath_channel(struct complex **ch,
		       double **tx_sig_re, 
		       double **tx_sig_im, 
		       double **rx_sig_re,
		       double **rx_sig_im,
		       double *amps, 
		       double Td, 
		       double BW, 
		       double ricean_factor,
		       double aoa,
		       unsigned char nb_antennas_tx,
		       unsigned char nb_antennas_rx,
		       unsigned int length,
		       unsigned int channel_length,
		       double path_loss_dB,
		       double forgetting_factor,
		       unsigned char clear) {
 
  int i,ii,j,l;
  struct complex rx_tmp,tx;
  struct complex phase;
  double path_loss = pow(10,-path_loss_dB/20);
  unsigned int n;
#ifdef DEBUG_PHY
  //  printf("path_loss = %g\n",path_loss);
#endif
  
  for (i=0;i<nb_antennas_rx;i++)      // RX Antenna loop
    for (j=0;j<nb_antennas_tx;j++) {  // TX Antenna loop
      
      phase.r = cos(2.0*M_PI*(i-j)/aoa);
      phase.i = sin(2.0*M_PI*(i-j)/aoa);
      

      memset(ch[i + (j*nb_antennas_rx)], 0,channel_length * sizeof(struct complex));
      
      random_channel(amps,Td, &a[i][j][0],8,BW,ch[i + (j*nb_antennas_rx)],ricean_factor,&phase,forgetting_factor,clear);
      /*
      if ((i==0) && (j==0)) {
	printf("Forgetting factor %f, Ricean factor %f\n",forgetting_factor,ricean_factor);
	for (n=0;n<channel_length;n++)
	  printf("%f ",pow(ch[i+(j*nb_antennas_rx)][n].r,2.0) + pow(ch[i+(j*nb_antennas_rx)][n].i,2.0));
	printf("\n");
      }
      */
      //ch[i + (j*nb_antennas_rx)][0].r=1;
      //ch[i + (j*nb_antennas_rx)][0].i=0;

    }

  for (i=0;i<length;i++) {
    for (ii=0;ii<nb_antennas_rx;ii++) {
      rx_tmp.r = 0;
      rx_tmp.i = 0;
      for (j=0;j<nb_antennas_tx;j++) {


	for (l = 0;l<channel_length;l++) {
	  if ((i-l)>=0) {
	    tx.r = tx_sig_re[j][i-l];
	    tx.i = tx_sig_im[j][i-l];
	  }
	  else {
	    tx.r =0;
	    tx.i =0;
	  }
	  rx_tmp.r += (tx.r * ch[ii+(j*nb_antennas_rx)][l].r) - (tx.i * ch[ii+(j*nb_antennas_rx)][l].i);
	  rx_tmp.i += (tx.i * ch[ii+(j*nb_antennas_rx)][l].r) + (tx.r * ch[ii+(j*nb_antennas_rx)][l].i);
	  
	} //l
      }  // j
      rx_sig_re[ii][i] = rx_tmp.r*path_loss;
      rx_sig_im[ii][i] = rx_tmp.i*path_loss;
      
    } // ii
  } // i
}

