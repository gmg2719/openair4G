/*******************************************************************************
Eurecom OpenAirInterface 2
Copyright(c) 1999 - 2014 Eurecom

This program is free software; you can redistribute it and/or modify it
under the terms and conditions of the GNU General Public License,
version 2, as published by the Free Software Foundation.

This program is distributed in the hope it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.

The full GNU General Public License is included in this distribution in
the file called "COPYING".

Contact Information
Openair Admin: openair_admin@eurecom.fr
Openair Tech : openair_tech@eurecom.fr
Forums       : http://forums.eurecom.fsr/openairinterface
Address      : EURECOM,
               Campus SophiaTech,
               450 Route des Chappes,
               CS 50193
               06904 Biot Sophia Antipolis cedex,
               FRANCE
*******************************************************************************/
/***************************************************************************
                          rlc_am_util_proto_extern.h  -
                             -------------------
  AUTHOR  : Lionel GAUTHIER
  COMPANY : EURECOM
  EMAIL   : Lionel.Gauthier@eurecom.fr

 ***************************************************************************/
#    ifndef __RLC_AM_UTIL_PROTO_EXTERN_H__
#        define __RLC_AM_UTIL_PROTO_EXTERN_H__
//-----------------------------------------------------------------------------
#        include "rlc_am_entity.h"
#        include "mem_block.h"
//-----------------------------------------------------------------------------
extern void     rlc_am_stat_req     (struct rlc_am_entity *rlcP, 
							  unsigned int* tx_pdcp_sdu,
							  unsigned int* tx_pdcp_sdu_discarded,
							  unsigned int* tx_retransmit_pdu_unblock,
							  unsigned int* tx_retransmit_pdu_by_status,
							  unsigned int* tx_retransmit_pdu,
							  unsigned int* tx_data_pdu,
							  unsigned int* tx_control_pdu,
							  unsigned int* rx_sdu,
							  unsigned int* rx_error_pdu,  
							  unsigned int* rx_data_pdu,
							  unsigned int* rx_data_pdu_out_of_window,
							  unsigned int* rx_control_pdu);
extern int      rlc_am_comp_sn (struct rlc_am_entity *rlcP, uint16_t low_boundaryP, uint16_t sn1P, uint16_t sn2P);
extern void     adjust_vr_r_mr (struct rlc_am_entity *rlcP);
extern void     adjust_vt_a_ms (struct rlc_am_entity *rlcP);
extern void     display_protocol_vars_rlc_am (struct rlc_am_entity *rlcP);
extern void     display_retransmission_buffer (struct rlc_am_entity *rlcP);
extern void     display_receiver_buffer (struct rlc_am_entity *rlcP);
extern void     rlc_am_check_retransmission_buffer (struct rlc_am_entity *rlcP, uint8_t * messageP);
extern void     rlc_am_check_receiver_buffer (struct rlc_am_entity *rlcP, uint8_t * messageP);
extern void     rlc_am_display_data_pdu7 (mem_block_t * pduP);
#        ifdef DEBUG_RLC_AM_CONFIRM
void            debug_rlc_am_confirm (struct rlc_am_entity *rlcP, uint32_t muiP);
#        endif
#    endif
