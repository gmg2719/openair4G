/*******************************************************************************

  Eurecom OpenAirInterface
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
  Forums       : http://forums.eurecom.fr/openairinterface
  Address      : EURECOM, Campus SophiaTech, 450 Route des Chappes
                 06410 Biot FRANCE

*******************************************************************************/

#ifndef ENB_CONFIG_H_
#define ENB_CONFIG_H_

#include "commonDef.h"
#include "PHY/impl_defs_lte.h"
#include "s1ap_messages_types.h"

// Hard to find a defined value for max enb...
#define MAX_ENB 16

#define IPV4_STR_ADDR_TO_INT_NWBO(AdDr_StR,NwBo,MeSsAgE ) do {\
            struct in_addr inp;\
            if ( inet_aton(AdDr_StR, &inp ) < 0 ) {\
                AssertFatal (0, MeSsAgE);\
            } else {\
                NwBo = inp.s_addr;\
            }\
        } while (0);

#define ENB_CONFIG_STRING_ACTIVE_ENBS                   "Active_eNBs"

#define ENB_CONFIG_STRING_ENB_LIST                      "eNBs"
#define ENB_CONFIG_STRING_ENB_ID                        "eNB_ID"
#define ENB_CONFIG_STRING_CELL_TYPE                     "cell_type"
#define ENB_CONFIG_STRING_ENB_NAME                      "eNB_name"

#define ENB_CONFIG_STRING_TRACKING_AREA_CODE            "tracking_area_code"
#define ENB_CONFIG_STRING_MOBILE_COUNTRY_CODE           "mobile_country_code"
#define ENB_CONFIG_STRING_MOBILE_NETWORK_CODE           "mobile_network_code"

#define ENB_CONFIG_STRING_DEFAULT_PAGING_DRX            "default_paging_drx"

#define ENB_CONFIG_STRING_FRAME_TYPE                    "frame_type"
#define ENB_CONFIG_STRING_PREFIX_TYPE                   "prefix_type"
#define ENB_CONFIG_STRING_DOWNLINK_FREQUENCY            "downlink_frequency"
#define ENB_CONFIG_STRING_UPLINK_FREQUENCY_OFFSET       "uplink_frequency_offset"

#define ENB_CONFIG_STRING_MME_IP_ADDRESS                "mme_ip_address"
#define ENB_CONFIG_STRING_MME_IPV4_ADDRESS              "ipv4"
#define ENB_CONFIG_STRING_MME_IPV6_ADDRESS              "ipv6"
#define ENB_CONFIG_STRING_MME_IP_ADDRESS_ACTIVE         "active"
#define ENB_CONFIG_STRING_MME_IP_ADDRESS_PREFERENCE     "preference"

#define ENB_CONFIG_STRING_NETWORK_INTERFACES_CONFIG     "NETWORK_INTERFACES"
#define ENB_CONFIG_STRING_ENB_INTERFACE_NAME_FOR_S1_MME "ENB_INTERFACE_NAME_FOR_S1_MME"
#define ENB_CONFIG_STRING_ENB_IPV4_ADDRESS_FOR_S1_MME   "ENB_IPV4_ADDRESS_FOR_S1_MME"
#define ENB_CONFIG_STRING_ENB_INTERFACE_NAME_FOR_S1U    "ENB_INTERFACE_NAME_FOR_S1U"
#define ENB_CONFIG_STRING_ENB_IPV4_ADDR_FOR_S1U         "ENB_IPV4_ADDRESS_FOR_S1U"

typedef struct mme_ip_address_s {
    unsigned  ipv4:1;
    unsigned  ipv6:1;
    unsigned  active:1;
    char     *ipv4_address;
    char     *ipv6_address;
} mme_ip_address_t;

typedef struct Enb_properties_s {
    /* Unique eNB_id to identify the eNB within EPC.
     * For macro eNB ids this field should be 20 bits long.
     * For home eNB ids this field should be 28 bits long.
     */
    uint32_t            eNB_id;

    /* The type of the cell */
    enum cell_type_e    cell_type;

    /* Optional name for the cell
     * NOTE: the name can be NULL (i.e no name) and will be cropped to 150
     * characters.
     */
    char               *eNB_name;

    /* Tracking area code */
    uint16_t            tac;

    /* Mobile Country Code
     * Mobile Network Code
     */
    uint16_t            mcc;
    uint16_t            mnc;

    /* Default Paging DRX of the eNB as defined in TS 36.304 */
    paging_drx_t        default_drx;

    /* Physical parameters */
    lte_frame_type_t    frame_type;
    lte_prefix_type_t   prefix_type;
    uint32_t            downlink_frequency;
    int32_t             uplink_frequency_offset;

    /* Nb of MME to connect to */
    uint8_t             nb_mme;
    /* List of MME to connect to */
    mme_ip_address_t    mme_ip_address[S1AP_MAX_NB_MME_IP_ADDRESS];

    char               *enb_interface_name_for_S1U;
    uint32_t            enb_ipv4_address_for_S1U;

    char               *enb_interface_name_for_S1_MME;
    uint32_t            enb_ipv4_address_for_S1_MME;

} Enb_properties_t;

int enb_config_init(char* lib_config_file_name_pP, Enb_properties_t **enb_properties);

#endif /* ENB_CONFIG_H_ */