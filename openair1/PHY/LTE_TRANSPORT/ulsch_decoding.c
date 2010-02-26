#include "defs.h"
#include "PHY/defs.h"
#include "PHY/CODING/extern.h"
#include "extern.h"

#define DEBUG_ULSCH_DECODING
void free_eNb_ulsch(LTE_eNb_ULSCH_t *ulsch) {

  int i,r;

  if (ulsch) {
    for (i=0;i<ulsch->Mdlharq;i++) {
      if (ulsch->harq_processes[i]) {
	if (ulsch->harq_processes[i]->b)
	  free16(ulsch->harq_processes[i]->b,MAX_ULSCH_PAYLOAD_BYTES);
	if (ulsch->harq_processes[i]->c) {
	  for (r=0;r<MAX_NUM_ULSCH_SEGMENTS;r++)
	    free16(ulsch->harq_processes[i]->c[r],((r==0)?8:0) + 768);
	}
	for (r=0;r<MAX_NUM_ULSCH_SEGMENTS;r++)
	  if (ulsch->harq_processes[i]->d[r])
	    free16(ulsch->harq_processes[i]->d[r],((3*8*6144)+12+96)*sizeof(short));
	free16(ulsch->harq_processes[i],sizeof(LTE_UL_eNb_HARQ_t));
      }
    }
  free16(ulsch,sizeof(LTE_eNb_ULSCH_t));
  }
}

LTE_eNb_ULSCH_t *new_eNb_ulsch(unsigned char Mdlharq) {

  LTE_eNb_ULSCH_t *ulsch;
  unsigned char exit_flag = 0,i,r;

  ulsch = (LTE_eNb_ULSCH_t *)malloc16(sizeof(LTE_eNb_ULSCH_t));
  if (ulsch) {
    ulsch->Mdlharq = Mdlharq;

    for (i=0;i<Mdlharq;i++) {
      //      printf("new_ue_ulsch: Harq process %d\n",i);
      ulsch->harq_processes[i] = (LTE_UL_eNb_HARQ_t *)malloc16(sizeof(LTE_UL_eNb_HARQ_t));
      if (ulsch->harq_processes[i]) {
	ulsch->harq_processes[i]->b = (unsigned char*)malloc16(MAX_ULSCH_PAYLOAD_BYTES);
	if (!ulsch->harq_processes[i]->b)
	  exit_flag=3;
	for (r=0;r<MAX_NUM_ULSCH_SEGMENTS;r++) {
	  ulsch->harq_processes[i]->c[r] = (unsigned char*)malloc16(((r==0)?8:0) + 768);	
	  if (!ulsch->harq_processes[i]->c[r])
	    exit_flag=2;
	  ulsch->harq_processes[i]->d[r] = (short*)malloc16(((3*8*6144)+12+96)*sizeof(short));
	}
      
      }	else {
	exit_flag=1;
      }
    }

    if (exit_flag==0)
      return(ulsch);
  }
  msg("new_ue_ulsch: exit_flag = %d\n",exit_flag);
  free_eNb_ulsch(ulsch);

  return(NULL);
}

unsigned int  ulsch_decoding(short *ulsch_llr,
			     LTE_DL_FRAME_PARMS *frame_parms,
			     LTE_eNb_ULSCH_t *ulsch,
			     unsigned char subframe){

  

  unsigned short nb_rb = ulsch->nb_rb;
  unsigned char harq_pid = harq_pid = subframe2harq_pid_tdd(frame_parms->tdd_config,subframe);
  unsigned int A = ulsch->harq_processes[harq_pid]->TBS;
  unsigned char Q_m = get_Qm(ulsch->harq_processes[harq_pid]->mcs);
  unsigned int i,q,j;
  int iprime;
  unsigned int ret,offset;
  unsigned short iind;
  //  unsigned char dummy_channel_output[(3*8*block_length)+12];
  short coded_bits=0;
  short dummy_w[8][3*(6144+64)];
  unsigned char dummy_w_cc[3*(MAX_CQI_BITS+8)];
  unsigned int r,r_offset=0,Kr,Kr_bytes;
  unsigned char crc_type;
  short y[6*14*1200];
  unsigned char *columnset;
  unsigned int sumKr=0;
  unsigned int Qprime,L,G,Q_CQI,Q_RI,Q_ACK,H,Hprime,Hpp,Cmux,Rmux,Rmux_prime,O_RCC;
  unsigned int Qprime_ACK,Qprime_CQI,Qprime_RI;
  int metric,metric_new;



  G = nb_rb * (12 * Q_m) * ulsch->Nsymb_pusch;



  if (ulsch->harq_processes[harq_pid]->Ndi == 1) {
    // This is a new packet, so compute quantities regarding segmentation
    ulsch->harq_processes[harq_pid]->B = A+24;
    lte_segmentation(NULL,
		     NULL,
		     ulsch->harq_processes[harq_pid]->B,
		     &ulsch->harq_processes[harq_pid]->C,
		     &ulsch->harq_processes[harq_pid]->Cplus,
		     &ulsch->harq_processes[harq_pid]->Cminus,
		     &ulsch->harq_processes[harq_pid]->Kplus,
		     &ulsch->harq_processes[harq_pid]->Kminus,		     
		     &ulsch->harq_processes[harq_pid]->F);
    //  CLEAR LLR's HERE for first packet in process
  }


  r_offset = 0;
  for (r=0;r<ulsch->harq_processes[harq_pid]->C;r++) {

    // Get Turbo interleaver parameters
    if (r<ulsch->harq_processes[harq_pid]->Cminus)
      Kr = ulsch->harq_processes[harq_pid]->Kminus;
    else
      Kr = ulsch->harq_processes[harq_pid]->Kplus;
    Kr_bytes = Kr>>3;
    
    if (Kr_bytes<=64)
      iind = (Kr_bytes-5);
    else if (Kr_bytes <=128)
      iind = 59 + ((Kr_bytes-64)>>1);
    else if (Kr_bytes <= 256)
      iind = 91 + ((Kr_bytes-128)>>2);
    else if (Kr_bytes <= 768)
      iind = 123 + ((Kr_bytes-256)>>3);
    else {
      msg("ulsch_decoding: Illegal codeword size %d!!!\n",Kr_bytes);
      return(-1);
    }

  sumKr = 0;
  for (r=0;r<ulsch->harq_processes[harq_pid]->C;r++) {
    if (r<ulsch->harq_processes[harq_pid]->Cminus)
      Kr = ulsch->harq_processes[harq_pid]->Kminus;
    else
      Kr = ulsch->harq_processes[harq_pid]->Kplus;
    sumKr += Kr;
  }
  // Compute Q_ri
  Qprime = ulsch->O_RI*ulsch->harq_processes[harq_pid]->Msc_initial*ulsch->harq_processes[harq_pid]->Nsymb_initial * ulsch->beta_offset_cqi_times8;
  if ((Qprime % (8*sumKr)) > 0)
    Qprime = 1+(Qprime/(8*sumKr));
  else
    Qprime = Qprime/(8*sumKr);

  if (Qprime > 4*ulsch->nb_rb * 12)
    Qprime = 4*ulsch->nb_rb * 12;

  Q_RI = Q_m*Qprime;

  // Compute Q_ack

  Qprime = ulsch->O_ACK*ulsch->harq_processes[harq_pid]->Msc_initial*ulsch->harq_processes[harq_pid]->Nsymb_initial * ulsch->beta_offset_cqi_times8;
  if ((Qprime % (8*sumKr)) > 0)
    Qprime = 1+(Qprime/(8*sumKr));
  else
    Qprime = Qprime/(8*sumKr);

  if (Qprime > 4*ulsch->nb_rb * 12)
    Qprime = 4*ulsch->nb_rb * 12;

  Q_ACK = Qprime * Q_m;

  // Compute Q_cqi
  L=8;
  Qprime = (ulsch->Or1 + L) * ulsch->harq_processes[harq_pid]->Msc_initial*ulsch->harq_processes[harq_pid]->Nsymb_initial * ulsch->beta_offset_cqi_times8;
  if ((Qprime % (8*sumKr)) > 0)
    Qprime = 1+(Qprime/(8*sumKr));
  else
    Qprime = Qprime/(8*sumKr);

  G = ulsch->nb_rb * (12 * Q_m) * (ulsch->Nsymb_pusch);

  if (Qprime > (G - ulsch->O_RI))
    Qprime = G - ulsch->O_RI;

  Q_CQI = Q_m * Qprime;

  G = G - Q_RI - Q_CQI;
  H = G + Q_CQI;
  Hprime = H/Q_m;

  // Demultiplexing/Deinterleaving of PUSCH/ACK/RI/CQI
  Hpp = Hprime + Q_RI;
  
  Cmux       = ulsch->Nsymb_pusch;
  Rmux       = Hpp*Q_m/Cmux;
  Rmux_prime = Rmux/Q_m;
  
  Qprime_RI  = Q_RI / Q_m;
  Qprime_ACK = Q_ACK / Q_m;
  Qprime_CQI = Q_CQI / Q_m;

  // read in buffer
  j=0;
  for (i=0;i<Cmux;i++)
    for (r=0;r<Rmux_prime;r++)
      for (q=0;q<Q_m;q++) 
	y[q+(Q_m*((r*Cmux)+i))] = ulsch_llr[j++];
  
  if (j!=(H+Q_RI))
    msg("ulsch_coding.c: Error in input buffer length (j %d, H+Q_RI %d)\n",j,H+Q_RI); 

  // HARQ-ACK Bits (LLRs are nulled in overwritten bits after copying HARQ-ACK LLR)
  r = Rmux_prime-1;

  if (frame_parms->Ncp == 0)
    columnset = cs_ack_normal;
  else
    columnset = cs_ack_extended;

  j=0;
  for (i=0;i<Qprime_ACK;i++) {
    for (q=0;q<Q_m;q++) {
      ulsch->q_ACK[q+(Q_m*i)] = y[q+(Q_m*((r*Cmux) + columnset[j]))];
      y[q+(Q_m*((r*Cmux) + columnset[j]))]=0;  // NULL LLRs in ACK positions
    }
    j=(j+3)&3;
    r = Rmux_prime - (i>>2);
  }

  // CQI and Data bits
  j=0;
  for (i=0,iprime=-Qprime_CQI;i<Hprime;i++,iprime++) {
    if (y[Q_m*j] == 0) {
      if (i<Qprime_CQI) {
	for (q=0;q<Q_m;q++) {
	  ulsch->q[q+(Q_m*i)]=y[q+(Q_m*j)];
	}
      }
      else {
	for (q=0;q<Q_m;q++) {
	  ulsch->e[q+(Q_m*iprime)] = y[q+(Q_m*j)];
	}
      }
    }
    j++;
  }

  // RI BITS 
  r = Rmux_prime-1;

  if (frame_parms->Ncp == 0)
    columnset = cs_ri_normal;
  else
    columnset = cs_ri_extended;
  j=0;   
  for (i=0;i<Qprime_RI;i++) {
    for (q=0;q<Q_m;q++) 
      ulsch->q_RI[q+(Q_m*i)] = y[q+(Q_m*((r*Cmux) + columnset[j]))];
    j=(j+3)&3;
    r = Rmux_prime - (i>>2);
  }

  // Do CQI/RI/HARQ-ACK Decoding first and pass to MAC

  // HARQ-ACK 
  if (ulsch->O_ACK == 1) {
      ulsch->o_ACK[0] = ((ulsch->q_ACK[0] + ulsch->q_ACK[Q_m/2]) > 0) ? 1 : 0; 
  }
  if (ulsch->O_ACK == 2) {
    switch (Q_m) {
    case 2:
      ulsch->q_ACK[0] += ulsch->q_ACK[2];
      ulsch->q_ACK[1] += ulsch->q_ACK[4];
      ulsch->q_ACK[2] += ulsch->q_ACK[5];

      break;
    case 4:
      ulsch->q_ACK[0] += ulsch->q_ACK[6];
      ulsch->q_ACK[1] = ulsch->q_ACK[2] + ulsch->q_ACK[8];
      ulsch->q_ACK[2] = ulsch->q_ACK[4] + ulsch->q_ACK[10];

      break;
    case 6:
      ulsch->q_ACK[0] += ulsch->q_ACK[9];
      ulsch->q_ACK[1] = ulsch->q_ACK[3] + ulsch->q_ACK[12]; 
      ulsch->q_ACK[2] = ulsch->q_ACK[6] + ulsch->q_ACK[15]; 
      break;
    }
    ulsch->o_ACK[0] = 0;
    ulsch->o_ACK[1] = 0;
    metric     = -ulsch->q_ACK[0]-ulsch->q_ACK[1]-ulsch->q_ACK[2];
    metric_new = ulsch->q_ACK[0]-ulsch->q_ACK[1]+ulsch->q_ACK[2];
    if (metric_new > metric) {
      ulsch->o_ACK[0]=1;
      ulsch->o_ACK[1]=0;
      metric = metric_new;
    }
    metric_new = -ulsch->q_ACK[0]+ulsch->q_ACK[1]+ulsch->q_ACK[2];
    if (metric_new > metric) {
      ulsch->o_ACK[0] = 0;
      ulsch->o_ACK[1] = 1;
      metric = metric_new;
    }
    metric_new = ulsch->q_ACK[0]+ulsch->q_ACK[1]-ulsch->q_ACK[2];
    if (metric_new > metric) {
      ulsch->o_ACK[0] = 1;
      ulsch->o_ACK[0] = 1;
      metric = metric_new;
    }
  }
  else{
    msg("ulsch_decoding: FATAL, ACK cannot be more than 2 bits yet\n");
    return(-1);
  }

  // RI

  if (ulsch->O_RI == 1) {
      ulsch->o_RI[0] = ((ulsch->q_RI[0] + ulsch->q_RI[Q_m/2]) > 0) ? 1 : 0; 
  }
  else {
    msg("ulsch_decoding: FATAL, RI cannot be more than 1 bit yet\n");
    return(-1);
  }

  // CQI
  memset(dummy_w,0,3*(ulsch->Or1+8));
  O_RCC = generate_dummy_w_cc(ulsch->Or1+8,
			      dummy_w_cc);
  
  lte_rate_matching_cc_rx(O_RCC,
			  Q_CQI,
			  ulsch->o_w,
			  dummy_w_cc,
			  ulsch->q);

  sub_block_deinterleaving_cc((unsigned int)(ulsch->Or1+8), 
			      &ulsch->o_d[96], 
			      &ulsch->o_w[0]); 
 
  memset(ulsch->o,0,1+(ulsch->Or1/8));
  phy_viterbi_lte_sse2(ulsch->o_d+96,ulsch->o,8+ulsch->Or1);

  // Do PUSCH Decoding


  
#ifdef DEBUG_ULSCH_DECODING     
    printf("f1 %d, f2 %d, F %d\n",f1f2mat[2*iind],f1f2mat[1+(2*iind)],(r==0) ? ulsch->harq_processes[harq_pid]->F : 0);
#endif

    memset(dummy_w[r],0,3*(6144+64)*sizeof(short));
    ulsch->harq_processes[harq_pid]->RTC[r] = generate_dummy_w(4+(Kr_bytes*8), 
							       dummy_w[r],
							       (r==0) ? ulsch->harq_processes[harq_pid]->F : 0);

#ifdef DEBUG_ULSCH_DECODING    
    printf("Rate Matching Segment %d (coded bits (G) %d,unpunctured/repeated bits %d, Q_m %d, nb_rb %d, Nl %d)...\n",
	   r, G,
	   Kr*3,
	   Q_m,
	   nb_rb,
	   ulsch->harq_processes[harq_pid]->Nl);
#endif    

    r_offset += lte_rate_matching_turbo_rx(ulsch->harq_processes[harq_pid]->RTC[r],
					   G,
			 		   ulsch->harq_processes[harq_pid]->w[r],
					   dummy_w[r],
					   ulsch->e,
					   ulsch->harq_processes[harq_pid]->C,
					   NSOFT,
					   ulsch->Mdlharq,
					   1,
					   ulsch->harq_processes[harq_pid]->rvidx,
					   ulsch->harq_processes[harq_pid]->Ndi,
					   get_Qm(ulsch->harq_processes[harq_pid]->mcs),
					   1,
					   r);
    /*
    printf("Subblock deinterleaving, d %p w %p\n",
	   ulsch->harq_processes[harq_pid]->d[r],
	   ulsch->harq_processes[harq_pid]->w);
    */

    sub_block_deinterleaving_turbo(4+Kr, 
				   &ulsch->harq_processes[harq_pid]->d[r][96], 

				   ulsch->harq_processes[harq_pid]->w[r]); 

    /*
#ifdef DEBUG_ULSCH_DECODING    
    if (r==0) {
      write_output("decoder_llr.m","decllr",ulsch_llr,coded_bits_per_codeword,1,0);
      write_output("decoder_in.m","dec",&ulsch->harq_processes[harq_pid]->d[0][96],(3*8*Kr_bytes)+12,1,0);
    }

    printf("decoder input(segment %d) :",r);
    for (i=0;i<(3*8*Kr_bytes)+12;i++)
      printf("%d : %d\n",i,ulsch->harq_processes[harq_pid]->d[r][96+i]);
    printf("\n");
#endif
    */

    //    printf("Clearing c, %p\n",ulsch->harq_processes[harq_pid]->c[r]);
    //    memset(ulsch->harq_processes[harq_pid]->c[r],0,16);//block_length);
    //    printf("done\n");
    if (ulsch->harq_processes[harq_pid]->C == 1) 
      crc_type = CRC24_A;
    else 
      crc_type = CRC24_B;

    /*        
    printf("decoder input(segment %d)\n",r);
    for (i=0;i<(3*8*Kr_bytes)+12;i++)
      if ((ulsch->harq_processes[harq_pid]->d[r][96+i]>7) || 
	  (ulsch->harq_processes[harq_pid]->d[r][96+i] < -8))
	printf("%d : %d\n",i,ulsch->harq_processes[harq_pid]->d[r][96+i]);
    printf("\n");
    */
    
    ret = phy_threegpplte_turbo_decoder(&ulsch->harq_processes[harq_pid]->d[r][96],
					ulsch->harq_processes[harq_pid]->c[r],
					Kr,
					f1f2mat[iind*2],   
					f1f2mat[(iind*2)+1], 
					MAX_TURBO_ITERATIONS,
					crc_type,
					(r==0) ? ulsch->harq_processes[harq_pid]->F : 0,
					harq_pid+1);
    

    if (ret==(1+MAX_TURBO_ITERATIONS)) {// a Code segment is in error so break;
      //      printf("CRC failed\n");
      return(ret);
    }
  }
  // Reassembly of Transport block here
  offset = 0;
  //  printf("F %d, Fbytes %d\n",ulsch->harq_processes[harq_pid]->F,ulsch->harq_processes[harq_pid]->F>>3);
  
  for (r=0;r<ulsch->harq_processes[harq_pid]->C;r++) {
    if (r<ulsch->harq_processes[harq_pid]->Cminus)
      Kr = ulsch->harq_processes[harq_pid]->Kminus;
    else
      Kr = ulsch->harq_processes[harq_pid]->Kplus;

    Kr_bytes = Kr>>3;
    
    if (r==0) {
      memcpy(ulsch->harq_processes[harq_pid]->b,
	     &ulsch->harq_processes[harq_pid]->c[0][(ulsch->harq_processes[harq_pid]->F>>3)],
	     Kr_bytes - (ulsch->harq_processes[harq_pid]->F>>3));
      offset = Kr_bytes - (ulsch->harq_processes[harq_pid]->F>>3);
      //            printf("copied %d bytes to b sequence\n",
      //      	     Kr_bytes - (ulsch->harq_processes[harq_pid]->F>>3));
    }
    else {
      memcpy(ulsch->harq_processes[harq_pid]->b+offset,
	     ulsch->harq_processes[harq_pid]->c[0],
	     Kr_bytes);
      offset += Kr_bytes;
    }
  }
  
  return(ret);
}
