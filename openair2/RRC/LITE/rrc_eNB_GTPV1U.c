/*******************************************************************************
    OpenAirInterface
    Copyright(c) 1999 - 2014 Eurecom

    OpenAirInterface is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.


    OpenAirInterface is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with OpenAirInterface.The full GNU General Public License is
    included in this distribution in the file called "COPYING". If not,
    see <http://www.gnu.org/licenses/>.

  Contact Information
  OpenAirInterface Admin: openair_admin@eurecom.fr
  OpenAirInterface Tech : openair_tech@eurecom.fr
  OpenAirInterface Dev  : openair4g-devel@eurecom.fr

  Address      : Eurecom, Campus SophiaTech, 450 Route des Chappes, CS 50193 - 06904 Biot Sophia Antipolis cedex, FRANCE

*******************************************************************************/
/*! \file rrc_eNB_GTPV1U.c
 * \brief rrc GTPV1U procedures for eNB
 * \author Lionel GAUTHIER
 * \version 1.0
 * \company Eurecom
 * \email: lionel.gauthier@eurecom.fr
 */

#if defined(ENABLE_USE_MME)
# include "defs.h"
# include "extern.h"
# include "RRC/LITE/MESSAGES/asn1_msg.h"
# include "rrc_eNB_GTPV1U.h"
# include "rrc_eNB_UE_context.h"

# if defined(ENABLE_ITTI)
#   include "asn1_conversions.h"
#   include "intertask_interface.h"
# endif

int
rrc_eNB_process_GTPV1U_CREATE_TUNNEL_RESP(
  const protocol_ctxt_t* const ctxt_pP,
  MessageDef* msg_pP,
  const char* msg_name_pP
)
{
  rnti_t                         rnti;
  int                    i;
  struct rrc_eNB_ue_context_s*   ue_context_p = NULL;

  if (msg_pP) {
    LOG_D(RRC, PROTOCOL_RRC_CTXT_UE_FMT" RX %s num tunnels %u \n",
          PROTOCOL_RRC_CTXT_UE_ARGS(ctxt_pP),
          msg_name_pP,
          GTPV1U_ENB_CREATE_TUNNEL_RESP(msg_pP).num_tunnels);

    rnti = GTPV1U_ENB_CREATE_TUNNEL_RESP(msg_pP).rnti;
    ue_context_p = rrc_eNB_get_ue_context(
                     &eNB_rrc_inst[ctxt_pP->module_id],
                     ctxt_pP->rnti);

    for (i = 0; i < GTPV1U_ENB_CREATE_TUNNEL_RESP(msg_pP).num_tunnels; i++) {
      LOG_D(RRC, PROTOCOL_RRC_CTXT_UE_FMT" rrc_eNB_process_GTPV1U_CREATE_TUNNEL_RESP tunnel %u bearer index %u id %u\n",
            PROTOCOL_RRC_CTXT_UE_ARGS(ctxt_pP),
            GTPV1U_ENB_CREATE_TUNNEL_RESP(msg_pP).enb_S1u_teid[i],
            i,
            GTPV1U_ENB_CREATE_TUNNEL_RESP(msg_pP).eps_bearer_id[i]);
      ue_context_p->ue_context.enb_gtp_teid[i]  = GTPV1U_ENB_CREATE_TUNNEL_RESP(msg_pP).enb_S1u_teid[i];
      ue_context_p->ue_context.enb_gtp_addrs[i] = GTPV1U_ENB_CREATE_TUNNEL_RESP(msg_pP).enb_addr;
      ue_context_p->ue_context.enb_gtp_ebi[i]   = GTPV1U_ENB_CREATE_TUNNEL_RESP(msg_pP).eps_bearer_id[i];
    }
    return 0;
  } else {
    return -1;
  }
}
#endif
