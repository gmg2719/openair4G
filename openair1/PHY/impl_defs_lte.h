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

/*! \file PHY/impl_defs_lte.h
* \brief LTE Physical channel configuration and variable structure definitions
* \author R. Knopp, F. Kaltenberger
* \date 2011
* \version 0.1
* \company Eurecom
* \email: knopp@eurecom.fr,florian.kaltenberger@eurecom.fr
* \note
* \warning
*/

#ifndef __PHY_IMPLEMENTATION_DEFS_LTE_H__
#define __PHY_IMPLEMENTATION_DEFS_LTE_H__


#include "types.h"
#include "spec_defs_top.h"
//#include "defs.h"

#define LTE_NUMBER_OF_SUBFRAMES_PER_FRAME 10
#define LTE_SLOTS_PER_FRAME  20
#define LTE_CE_FILTER_LENGTH 5
#define LTE_CE_OFFSET LTE_CE_FILTER_LENGTH
#define TX_RX_SWITCH_SYMBOL (NUMBER_OF_SYMBOLS_PER_FRAME>>1) 
#define PBCH_PDU_SIZE 3 //bytes

#define PRACH_SYMBOL 3 //position of the UL PSS wrt 2nd slot of special subframe

#define NUMBER_OF_FREQUENCY_GROUPS (lte_frame_parms->N_RB_DL)

#define SSS_AMP 1148

#define MAX_NUM_PHICH_GROUPS 56  //110 RBs Ng=2, p.60 36-212, Sec. 6.9

#define MAX_MBSFN_AREA 8


typedef enum {TDD=1,FDD=0} lte_frame_type_t;

typedef enum {EXTENDED=1,NORMAL=0} lte_prefix_type_t;

/// Enumeration for parameter PHICH-Duration \ref PHICH_CONFIG_COMMON::phich_duration.
typedef enum {
  normal=0,
  extended=1
} PHICH_DURATION_t;

/// Enumeration for parameter Ng \ref PHICH_CONFIG_COMMON::phich_resource.
typedef enum {
  oneSixth=1,
  half=3,
  one=6,
  two=12
} PHICH_RESOURCE_t;

/// PHICH-Config from 36.331 RRC spec
typedef struct {
  /// Parameter: PHICH-Duration, see TS 36.211 (Table 6.9.3-1).
  PHICH_DURATION_t phich_duration;
  /// Parameter: Ng, see TS 36.211 (6.9). \details Value oneSixth corresponds to 1/6, half corresponds to 1/2 and so on.
  PHICH_RESOURCE_t phich_resource;
} PHICH_CONFIG_COMMON;

/// PRACH-ConfigInfo from 36.331 RRC spec
typedef struct {
  /// Parameter: prach-ConfigurationIndex, see TS 36.211 (5.7.1). \vr{[0..63]}
  uint8_t prach_ConfigIndex;
  /// Parameter: High-speed-flag, see TS 36.211 (5.7.2). \vr{[0..1]} 1 corresponds to Restricted set and 0 to Unrestricted set.
  uint8_t highSpeedFlag;
  /// Parameter: \f$N_\text{CS}\f$, see TS 36.211 (5.7.2). \vr{[0..15]}\n Refer to table 5.7.2-2 for preamble format 0..3 and to table 5.7.2-3 for preamble format 4.
  uint8_t zeroCorrelationZoneConfig;
  /// Parameter: prach-FrequencyOffset, see TS 36.211 (5.7.1). \vr{[0..94]}\n For TDD the value range is dependent on the value of \ref prach_ConfigIndex.
  uint8_t prach_FreqOffset;
} PRACH_CONFIG_INFO;

/// PRACH-ConfigSIB or PRACH-Config from 36.331 RRC spec
typedef struct {
  /// Parameter: RACH_ROOT_SEQUENCE, see TS 36.211 (5.7.1). \vr{[0..837]}
  uint16_t rootSequenceIndex;
  /// prach_Config_enabled=1 means enabled. \vr{[0..1]}
  uint8_t prach_Config_enabled;
  /// PRACH Configuration Information
  PRACH_CONFIG_INFO prach_ConfigInfo;
} PRACH_CONFIG_COMMON;

/// Enumeration for parameter \f$N_\text{ANRep}\f$ \ref PUCCH_CONFIG_DEDICATED::repetitionFactor.
typedef enum {
  n2=0,
  n4,
  n6
} ACKNAKREP_t;

/// Enumeration for \ref PUCCH_CONFIG_DEDICATED::tdd_AckNackFeedbackMode.
typedef enum {
  bundling=0,
  multiplexing
} ANFBmode_t;

/// PUCCH-ConfigDedicated from 36.331 RRC spec
typedef struct {
  /// Flag to indicate ACK NAK repetition activation, see TS 36.213 (10.1). \vr{[0..1]}
  uint8_t ackNackRepetition;
  /// Parameter: \f$N_\text{ANRep}\f$, see TS 36.213 (10.1).
  ACKNAKREP_t repetitionFactor;
  /// Parameter: \f$n^{(1)}_\text{PUCCH,ANRep}\f$, see TS 36.213 (10.1). \vr{[0..2047]}
  uint16_t n1PUCCH_AN_Rep;
  /// Feedback mode, see TS 36.213 (7.3). \details Applied to both PUCCH and PUSCH feedback. For TDD, should always be set to bundling.
  ANFBmode_t tdd_AckNackFeedbackMode;
} PUCCH_CONFIG_DEDICATED;

/// PUCCH-ConfigCommon from 36.331 RRC spec
typedef struct {
  /// Parameter: \f$\Delta^\text{PUCCH}_\text{shift}\f$, see TS 36.211 (5.4.1). \vr{[1..3]} \note the specification sais it is an enumerated value.
  uint8_t deltaPUCCH_Shift;
  /// Parameter: \f$N^{(2)}_\text{RB}\f$, see TS 36.211 (5.4). \vr{[0..98]}
  uint8_t nRB_CQI;
  /// Parameter: \f$N^{(1)}_\text{CS}\f$, see TS 36.211 (5.4). \vr{[0..7]}
  uint8_t nCS_AN;
  /// Parameter: \f$N^{(1)}_\text{PUCCH}\f$ see TS 36.213 (10.1). \vr{[0..2047]}
  uint16_t n1PUCCH_AN;
} PUCCH_CONFIG_COMMON;

/// UL-ReferenceSignalsPUSCH from 36.331 RRC spec
typedef struct {
  /// Parameter: Group-hopping-enabled, see TS 36.211 (5.5.1.3). \vr{[0..1]}
  uint8_t groupHoppingEnabled;
  /// Parameter: \f$\Delta SS\f$, see TS 36.211 (5.5.1.3). \vr{[0..29]}
  uint8_t groupAssignmentPUSCH;
  /// Parameter: Sequence-hopping-enabled, see TS 36.211 (5.5.1.4). \vr{[0..1]}
  uint8_t sequenceHoppingEnabled;
  /// Parameter: cyclicShift, see TS 36.211 (Table 5.5.2.1.1-2). \vr{[0..7]}
  uint8_t cyclicShift;
  /// nPRS for cyclic shift of DRS \note not part of offical UL-ReferenceSignalsPUSCH ASN1 specification.
  uint8_t nPRS[20];
  /// group hopping sequence for DRS \note not part of offical UL-ReferenceSignalsPUSCH ASN1 specification.
  uint8_t grouphop[20];
  /// sequence hopping sequence for DRS \note not part of offical UL-ReferenceSignalsPUSCH ASN1 specification.
  uint8_t seqhop[20];
} UL_REFERENCE_SIGNALS_PUSCH_t;
 
/// Enumeration for parameter Hopping-mode \ref PUSCH_CONFIG_COMMON::hoppingMode.
typedef enum {
  interSubFrame=0, 
  intraAndInterSubFrame=1
} PUSCH_HOPPING_t;

/// PUSCH-ConfigCommon from 36.331 RRC spec.
typedef struct {
  /// Parameter: \f$N_{sb}\f$, see TS 36.211 (5.3.4). \vr{[1..4]}
  uint8_t n_SB;
  /// Parameter: Hopping-mode, see TS 36.211 (5.3.4).
  PUSCH_HOPPING_t hoppingMode;
  /// Parameter: \f$N^{HO}_{RB}\f$, see TS 36.211 (5.3.4). \vr{[0..98]}
  uint8_t pusch_HoppingOffset;
  /// See TS 36.213 (8.6.1). \vr{[0..1]} 1 indicates 64QAM is allowed, 0 not allowed.
  uint8_t enable64QAM;
  /// Ref signals configuration
  UL_REFERENCE_SIGNALS_PUSCH_t ul_ReferenceSignalsPUSCH;
} PUSCH_CONFIG_COMMON;

/// UE specific PUSCH configuration.
typedef struct {
  /// Parameter: \f$I^\text{HARQ-ACK}_\text{offset}\f$, see TS 36.213 (Table 8.6.3-1). \vr{[0..15]}
  uint16_t betaOffset_ACK_Index;
  /// Parameter: \f$I^{RI}_\text{offset}\f$, see TS 36.213 (Table 8.6.3-2). \vr{[0..15]}
  uint16_t betaOffset_RI_Index;
  /// Parameter: \f$I^{CQI}_\text{offset}\f$, see TS 36.213 (Table 8.6.3-3). \vr{[0..15]}
  uint16_t betaOffset_CQI_Index;
} PUSCH_CONFIG_DEDICATED;

/// lola CBA information 
typedef struct {
  /// 
  uint16_t betaOffset_CA_Index;
  ///
  uint16_t cShift;
} PUSCH_CA_CONFIG_DEDICATED;

/// PDSCH-ConfigCommon from 36.331 RRC spec
typedef struct {
  /// Parameter: Reference-signal power, see TS 36.213 (5.2). \vr{[-60..50]}\n Provides the downlink reference-signal EPRE. The actual value in dBm.
  int8_t referenceSignalPower;
  /// Parameter: \f$P_B\f$, see TS 36.213 (Table 5.2-1). \vr{[0..3]}
  uint8_t p_b;
} PDSCH_CONFIG_COMMON;

/// Enumeration for Parameter \f$P_A\f$ \ref PDSCH_CONFIG_DEDICATED::p_a.
typedef enum {
  dBm6=0, ///< (dB-6) corresponds to -6 dB
  dBm477, ///< (dB-4dot77) corresponds to -4.77 dB
  dBm3,   ///< (dB-3) corresponds to -3 dB
  dBm177, ///< (dB-1dot77) corresponds to -1.77 dB
  dB0,    ///< corresponds to 0 dB
  dB1,    ///< corresponds to 1 dB
  dB2,    ///< corresponds to 2 dB
  dB3     ///< corresponds to 3 dB
} PA_t;

/// PDSCH-ConfigDedicated from 36.331 RRC spec
typedef struct {
  /// Parameter: \f$P_A\f$, see TS 36.213 (5.2).
  PA_t p_a;
} PDSCH_CONFIG_DEDICATED;

/// SoundingRS-UL-ConfigCommon Information Element from 36.331 RRC spec
typedef struct {
  /// enabled flag=1 means SRS is enabled. \vr{[0..1]}
  uint8_t enabled_flag;
  /// Parameter: SRS Bandwidth Configuration, see TS 36.211 (table 5.5.3.2-1, 5.5.3.2-2, 5.5.3.2-3 and 5.5.3.2-4). \vr{[0..7]}\n Actual configuration depends on UL bandwidth. \note the specification sais it is an enumerated value.
  uint8_t srs_BandwidthConfig;
  /// Parameter: SRS SubframeConfiguration, see TS 36.211 (table 5.5.3.3-1 for FDD, table 5.5.3.3-2 for TDD). \vr{[0..15]} \note the specification sais it is an enumerated value.
  uint8_t srs_SubframeConfig;
  /// Parameter: Simultaneous-AN-and-SRS, see TS 36.213 (8.2). \vr{[0..1]}
  uint8_t ackNackSRS_SimultaneousTransmission;
  /// Parameter: srsMaxUpPts, see TS 36.211 (5.5.3.2). \details If this field is present, reconfiguration of \f$m^\text{max}_\text{SRS,0}\f$ applies for UpPts, otherwise reconfiguration does not apply.
  uint8_t srs_MaxUpPts;
} SOUNDINGRS_UL_CONFIG_COMMON;

/// \note UNUSED
typedef enum {
  ulpc_al0=0,
  ulpc_al04=1,
  ulpc_al05=2,
  ulpc_al06=3,
  ulpc_al07=4,
  ulpc_al08=5,
  ulpc_al09=6,
  ulpc_al11=7
} UL_POWER_CONTROL_COMMON_alpha_t;

/// Enumeration for \ref deltaFList_PUCCH_t::deltaF_PUCCH_Format1.
typedef enum {
        deltaF_PUCCH_Format1_deltaF_2  = 0,
        deltaF_PUCCH_Format1_deltaF0   = 1,
        deltaF_PUCCH_Format1_deltaF2   = 2
} deltaF_PUCCH_Format1_t;

/// Enumeration for \ref deltaFList_PUCCH_t::deltaF_PUCCH_Format1b.
typedef enum {
        deltaF_PUCCH_Format1b_deltaF1  = 0,
        deltaF_PUCCH_Format1b_deltaF3  = 1,
        deltaF_PUCCH_Format1b_deltaF5  = 2
} deltaF_PUCCH_Format1b_t;

/// Enumeration for \ref deltaFList_PUCCH_t::deltaF_PUCCH_Format2.
typedef enum {
        deltaF_PUCCH_Format2_deltaF_2  = 0,
        deltaF_PUCCH_Format2_deltaF0   = 1,
        deltaF_PUCCH_Format2_deltaF1   = 2,
        deltaF_PUCCH_Format2_deltaF2   = 3
} deltaF_PUCCH_Format2_t;

/// Enumeration for \ref deltaFList_PUCCH_t::deltaF_PUCCH_Format2a.
typedef enum {
        deltaF_PUCCH_Format2a_deltaF_2 = 0,
        deltaF_PUCCH_Format2a_deltaF0  = 1,
        deltaF_PUCCH_Format2a_deltaF2  = 2
} deltaF_PUCCH_Format2a_t;

/// Enumeration for \ref deltaFList_PUCCH_t::deltaF_PUCCH_Format2b.
typedef enum {
        deltaF_PUCCH_Format2b_deltaF_2 = 0,
        deltaF_PUCCH_Format2b_deltaF0  = 1,
        deltaF_PUCCH_Format2b_deltaF2  = 2
} deltaF_PUCCH_Format2b_t;

/// DeltaFList-PUCCH from 36.331 RRC spec
typedef struct {
        deltaF_PUCCH_Format1_t   deltaF_PUCCH_Format1;
        deltaF_PUCCH_Format1b_t  deltaF_PUCCH_Format1b;
        deltaF_PUCCH_Format2_t   deltaF_PUCCH_Format2;
        deltaF_PUCCH_Format2a_t  deltaF_PUCCH_Format2a;
        deltaF_PUCCH_Format2b_t  deltaF_PUCCH_Format2b;
} deltaFList_PUCCH_t;

/// SoundingRS-UL-ConfigDedicated Information Element from 36.331 RRC spec
typedef struct {
  /// Parameter: \f$B_\text{SRS}\f$, see TS 36.211 (table 5.5.3.2-1, 5.5.3.2-2, 5.5.3.2-3 and 5.5.3.2-4). \vr{[0..3]} \note the specification sais it is an enumerated value.
  uint8_t srs_Bandwidth;
  /// Parameter: SRS hopping bandwidth \f$b_\text{hop}\in\{0,1,2,3\}\f$, see TS 36.211 (5.5.3.2) \vr{[0..3]} \note the specification sais it is an enumerated value.
  uint8_t srs_HoppingBandwidth;
  /// Parameter: \f$n_\text{RRC}\f$, see TS 36.211 (5.5.3.2). \vr{[0..23]}
  uint8_t freqDomainPosition;
  /// Parameter: Duration, see TS 36.213 (8.2). \vr{[0..1]} 0 corresponds to "single" and 1 to "indefinite".
  uint8_t duration;
  /// Parameter: \f$k_\text{TC}\in\{0,1\}\f$, see TS 36.211 (5.5.3.2). \vr{[0..1]}
  uint8_t transmissionComb;
  /// Parameter: \f$I_\text{SRS}\f$, see TS 36.213 (table 8.2-1). \vr{[0..1023]}
  uint16_t srs_ConfigIndex;
  /// Parameter: \f$n^\text{CS}_\text{SRS}\f$. See TS 36.211 (5.5.3.1). \vr{[0..7]} \note the specification sais it is an enumerated value.
  uint8_t cyclicShift;
} SOUNDINGRS_UL_CONFIG_DEDICATED;

/// UplinkPowerControlDedicated Information Element from 36.331 RRC spec
typedef struct {
  /// Parameter: \f$P_\text{0\_UE\_PUSCH}(1)\f$, see TS 36.213 (5.1.1.1), unit dB. \vr{[-8..7]}\n This field is applicable for non-persistent scheduling, only.
  int8_t p0_UE_PUSCH;
  /// Parameter: Ks, see TS 36.213 (5.1.1.1). \vr{[0..1]}\n en0 corresponds to value 0 corresponding to state “disabled”. en1 corresponds to value 1.25 corresponding to “enabled”. \note the specification sais it is an enumerated value. \warning the enumeration values do not correspond to the given values in the specification (en1 should be 1.25).
  uint8_t deltaMCS_Enabled;
  /// Parameter: Accumulation-enabled, see TS 36.213 (5.1.1.1). \vr{[0..1]} 1 corresponds to "enabled" whereas 0 corresponds to "disabled".
  uint8_t accumulationEnabled;
  /// Parameter: \f$P_\text{0\_UE\_PUCCH}(1)\f$, see TS 36.213 (5.1.2.1), unit dB. \vr{[-8..7]}
  int8_t p0_UE_PUCCH;
  /// Parameter: \f$P_\text{SRS\_OFFSET}\f$, see TS 36.213 (5.1.3.1). \vr{[0..15]}\n For Ks=1.25 (\ref deltaMCS_Enabled), the actual parameter value is pSRS_Offset value - 3. For Ks=0, the actual parameter value is -10.5 + 1.5*pSRS_Offset value.
  int8_t pSRS_Offset;
  /// Specifies the filtering coefficient for RSRP measurements used to calculate path loss, as specified in TS 36.213 (5.1.1.1).\details The same filtering mechanism applies as for quantityConfig described in 5.5.3.2. \note the specification sais it is an enumerated value.
  uint8_t filterCoefficient;
} UL_POWER_CONTROL_DEDICATED;

/// Enumeration for parameter \f$\alpha\f$ \ref UL_POWER_CONTROL_CONFIG_COMMON::alpha.
typedef enum {
  al0=0,
  al04=1,
  al05=2,
  al06=3,
  al07=4,
  al08=5,
  al09=6,
  al1=7
} PUSCH_alpha_t;

/// \note UNUSED
typedef enum {
  deltaFm2=0,
  deltaF0,
  deltaF1,
  deltaF2,
  deltaF3,
  deltaF5  
} deltaF_PUCCH_t;

/// UplinkPowerControlCommon Information Element from 36.331 RRC spec \note this structure does not currently make use of \ref deltaFList_PUCCH_t.
typedef struct {
  /// Parameter: \f$P_\text{0\_NOMINAL\_PUSCH}(1)\f$, see TS 36.213 (5.1.1.1), unit dBm. \vr{[-126..24]}\n This field is applicable for non-persistent scheduling, only.
  int8_t p0_NominalPUSCH;
  /// Parameter: \f$\alpha\f$, see TS 36.213 (5.1.1.1) \warning the enumeration values do not correspond to the given values in the specification (al04 should be 0.4, ...)!
  PUSCH_alpha_t alpha;
  /// Parameter: \f$P_\text{0\_NOMINAL\_PUCCH}\f$ See TS 36.213 (5.1.2.1), unit dBm. \vr{[-127..-96]}
  int8_t p0_NominalPUCCH;
  /// Parameter: \f$\Delta_\text{PREAMBLE\_Msg3}\f$ see TS 36.213 (5.1.1.1). \vr{[-1..6]}\n Actual value = IE value * 2 [dB].
  int8_t deltaPreambleMsg3;
  /// Parameter: \f$\Delta_\text{F\_PUCCH}(F)\f$ for the PUCCH format 1, see TS 36.213 (5.1.2). \vr{[0..2]} \warning check value range, why is this a long? \note the specification sais it is an enumerated value.
  long deltaF_PUCCH_Format1;
  /// Parameter: \f$\Delta_\text{F\_PUCCH}(F)\f$ for the PUCCH format 1a, see TS 36.213 (5.1.2). \vr{[0..2]} \warning check value range, why is this a long? \note the specification sais it is an enumerated value.
  long deltaF_PUCCH_Format1a;
  /// Parameter: \f$\Delta_\text{F\_PUCCH}(F)\f$ for the PUCCH format 1b, see TS 36.213 (5.1.2). \vr{[0..2]} \warning check value range, why is this a long? \note the specification sais it is an enumerated value.
  long deltaF_PUCCH_Format1b;
  /// Parameter: \f$\Delta_\text{F\_PUCCH}(F)\f$ for the PUCCH format 2, see TS 36.213 (5.1.2). \vr{[0..3]} \warning check value range, why is this a long? \note the specification sais it is an enumerated value.
  long deltaF_PUCCH_Format2;
  /// Parameter: \f$\Delta_\text{F\_PUCCH}(F)\f$ for the PUCCH format 2a, see TS 36.213 (5.1.2). \vr{[0..2]} \warning check value range, why is this a long? \note the specification sais it is an enumerated value.
  long deltaF_PUCCH_Format2a;
  /// Parameter: \f$\Delta_\text{F\_PUCCH}(F)\f$ for the PUCCH format 2b, see TS 36.213 (5.1.2). \vr{[0..2]} \warning check value range, why is this a long? \note the specification sais it is an enumerated value.
  long deltaF_PUCCH_Format2b;
} UL_POWER_CONTROL_CONFIG_COMMON;

/// Union for \ref TPC_PDCCH_CONFIG::tpc_Index.
typedef union {
    /// Index of N when DCI format 3 is used. See TS 36.212 (5.3.3.1.6). \vr{[1..15]}
    uint8_t indexOfFormat3;
    /// Index of M when DCI format 3A is used. See TS 36.212 (5.3.3.1.7). \vr{[1..31]}
    uint8_t indexOfFormat3A;
} TPC_INDEX_t;

/// TPC-PDCCH-Config Information Element from 36.331 RRC spec
typedef struct
{
  /// RNTI for power control using DCI format 3/3A, see TS 36.212. \vr{[0..65535]}
  uint16_t rnti;
  /// Index of N or M, see TS 36.212 (5.3.3.1.6 and 5.3.3.1.7), where N or M is dependent on the used DCI format (i.e. format 3 or 3a).
  TPC_INDEX_t tpc_Index;
} TPC_PDCCH_CONFIG;

/// Enumeration for parameter SR transmission \ref SCHEDULING_REQUEST_CONFIG::dsr_TransMax.
typedef enum {
  sr_n4=0,
  sr_n8=1,
  sr_n16=2,
  sr_n32=3,
  sr_n64=4
} DSR_TRANSMAX_t;

/// SchedulingRequestConfig Information Element from 36.331 RRC spec
typedef struct {
  /// Parameter: \f$n^{(1)}_\text{PUCCH,SRI}\f$, see TS 36.213 (10.1). \vr{[0..2047]}
  uint16_t sr_PUCCH_ResourceIndex;
  /// Parameter: \f$I_\text{SR}\f$, see TS 36.213 (10.1). \vr{[0..155]}
  uint8_t sr_ConfigIndex;
  /// Parameter for SR transmission in TS 36.321 (5.4.4). \details The value n4 corresponds to 4 transmissions, n8 corresponds to 8 transmissions and so on.
  DSR_TRANSMAX_t dsr_TransMax;
} SCHEDULING_REQUEST_CONFIG;

/// CQI-ReportPeriodic
typedef struct {
  /// Parameter: \f$n^{(2)}_\text{PUCCH}\f$, see TS 36.213 (7.2). \vr{[0..1185]}
  uint16_t cqi_PUCCH_ResourceIndex;
  /// Parameter: CQI/PMI Periodicity and Offset Configuration Index \f$I_\text{CQI/PMI}\f$, see TS 36.213 (tables 7.2.2-1A and 7.2.2-1C). \vr{[0..1023]}
  uint16_t cqi_PMI_ConfigIndex;
  /// Parameter: K, see 36.213 (4.2.2). \vr{[1..4]}
  uint8_t K;
  /// Parameter: RI Config Index \f$I_\text{RI}\f$, see TS 36.213 (7.2.2-1B). \vr{[0..1023]}
  uint16_t ri_ConfigIndex;
  /// Parameter: Simultaneous-AN-and-CQI, see TS 36.213 (10.1). \vr{[0..1]} 1 indicates that simultaneous transmission of ACK/NACK and CQI is allowed.
  uint8_t simultaneousAckNackAndCQI;
} CQI_REPORTPERIODIC;

/// Enumeration for parameter reporting mode \ref CQI_REPORT_CONFIG::cqi_ReportModeAperiodic.
typedef enum {
  rm12=0,
  rm20=1,
  rm22=2,
  rm30=3,
  rm31=4
} CQI_REPORTMODEAPERIODIC;

/// CQI-ReportConfig Information Element from 36.331 RRC spec
typedef struct {
  /// Parameter: reporting mode. Value rm12 corresponds to Mode 1-2, rm20 corresponds to Mode 2-0, rm22 corresponds to Mode 2-2 etc. PUSCH reporting modes are described in TS 36.213 [23, 7.2.1].
  CQI_REPORTMODEAPERIODIC cqi_ReportModeAperiodic;
  /// Parameter: \f$\Delta_\text{offset}\f$, see TS 36.213 (7.2.3). \vr{[-1..6]}\n Actual value = IE value * 2 [dB].
  int8_t nomPDSCH_RS_EPRE_Offset;
  CQI_REPORTPERIODIC CQI_ReportPeriodic;
} CQI_REPORT_CONFIG;

/// MBSFN-SubframeConfig Information Element from 36.331 RRC spec \note deviates from specification.
typedef struct {
  /// MBSFN subframe occurance. \details Radio-frames that contain MBSFN subframes occur when equation SFN mod radioFrameAllocationPeriod = radioFrameAllocationOffset is satisfied. When fourFrames is used for subframeAllocation, the equation defines the first radio frame referred to in the description below. Values n1 and n2 are not applicable when fourFrames is used. \note the specification sais it is an enumerated value {n1, n2, n4, n8, n16, n32}.
  int radioframeAllocationPeriod;
  /// MBSFN subframe occurance. \vr{[0..7]}\n Radio-frames that contain MBSFN subframes occur when equation SFN mod radioFrameAllocationPeriod = radioFrameAllocationOffset is satisfied. When fourFrames is used for subframeAllocation, the equation defines the first radio frame referred to in the description below. Values n1 and n2 are not applicable when fourFrames is used.
  int radioframeAllocationOffset;
  /// oneFrame or fourFrames. \vr{[0..1]}
  int fourFrames_flag;
  /// Subframe configuration. \vr{[0..63]} (\ref fourFrames_flag == 0) or \vr{[0..16777215]} (\ref fourFrames_flag == 1)
  /// \par fourFrames_flag == 0
  /// "1" denotes that the corresponding subframe is allocated for MBSFN. The following mapping applies:\n FDD: The first/leftmost bit defines the MBSFN allocation for subframe #1, the second bit for #2, third bit for #3 , fourth bit for #6, fifth bit for #7, sixth bit for #8.\n TDD: The first/leftmost bit defines the allocation for subframe #3, the second bit for #4, third bit for #7, fourth bit for #8, fifth bit for #9. Uplink subframes are not allocated. The last bit is not used.
  /// \par fourFrames_flag == 1
  /// A bit-map indicating MBSFN subframe allocation in four consecutive radio frames, "1" denotes that the corresponding subframe is allocated for MBSFN. The bitmap is interpreted as follows:\n FDD: Starting from the first radioframe and from the first/leftmost bit in the bitmap, the allocation applies to subframes #1, #2, #3 , #6, #7, and #8 in the sequence of the four radio-frames.\n TDD: Starting from the first radioframe and from the first/leftmost bit in the bitmap, the allocation applies to subframes #3, #4, #7, #8, and #9 in the sequence of the four radio-frames. The last four bits are not used. Uplink subframes are not allocated.
  int mbsfn_SubframeConfig;
} MBSFN_config_t;

typedef struct {
  /// Number of resource blocks (RB) in DL
  uint8_t N_RB_DL;
  /// Number of resource blocks (RB) in UL
  uint8_t N_RB_UL;
  ///  total Number of Resource Block Groups: this is ceil(N_PRB/P)
  uint8_t N_RBG;
  /// Total Number of Resource Block Groups SubSets: this is P
  uint8_t N_RBGS;
  /// Cell ID                 
  uint16_t Nid_cell;
  /// MBSFN Area ID
  uint16_t Nid_cell_mbsfn;
  /// Cyclic Prefix for DL (0=Normal CP, 1=Extended CP)
  lte_prefix_type_t Ncp;
  /// Cyclic Prefix for UL (0=Normal CP, 1=Extended CP)
  lte_prefix_type_t Ncp_UL;                   
  /// shift of pilot position in one RB
  uint8_t nushift;
  /// Frame type (0 FDD, 1 TDD)
  lte_frame_type_t frame_type;
  /// TDD subframe assignment (0-7) (default = 3) (254=RX only, 255=TX only)
  uint8_t tdd_config;
  /// TDD S-subframe configuration (0-9) 
  uint8_t tdd_config_S;
  /// indicates if node is a UE (NODE=2) or eNB (PRIMARY_CH=0).
  uint8_t node_id;
  /// Frequency index of CBMIMO1 card
  uint8_t freq_idx;
  /// RX Frequency for ExpressMIMO/LIME
  uint32_t carrier_freq[4];
  /// TX Frequency for ExpressMIMO/LIME
  uint32_t carrier_freqtx[4];
  /// RX gain for ExpressMIMO/LIME
  uint32_t rxgain[4];
  /// TX gain for ExpressMIMO/LIME
  uint32_t txgain[4];
  /// RF mode for ExpressMIMO/LIME
  uint32_t rfmode[4];
  /// RF RX DC Calibration for ExpressMIMO/LIME
  uint32_t rxdc[4];
  /// RF TX DC Calibration for ExpressMIMO/LIME
  uint32_t rflocal[4];
  /// RF VCO calibration for ExpressMIMO/LIME
  uint32_t rfvcolocal[4];
  /// Turns on second TX of CBMIMO1 card
  uint8_t dual_tx;
  /// flag to indicate SISO transmission
  uint8_t mode1_flag;
  /// Size of FFT  
  uint16_t ofdm_symbol_size;
  /// log2(Size of FFT)  
  uint8_t log2_symbol_size;
  /// Number of prefix samples in all but first symbol of slot
  uint16_t nb_prefix_samples;
  /// Number of prefix samples in first symbol of slot
  uint16_t nb_prefix_samples0;
  /// Carrier offset in FFT buffer for first RE in PRB0
  uint16_t first_carrier_offset;
  /// Number of samples in a subframe
  uint32_t samples_per_tti;
  /// Number of OFDM/SC-FDMA symbols in one subframe (to be modified to account for potential different in UL/DL)
  uint16_t symbols_per_tti;
  /// Number of Transmit antennas in node
  uint8_t nb_antennas_tx;
  /// Number of Receive antennas in node
  uint8_t nb_antennas_rx;
  /// Number of Transmit antennas in eNodeB
  uint8_t nb_antennas_tx_eNB;
  /// Pointer to twiddle factors for FFT
  int16_t *twiddle_fft;
  ///pointer to twiddle factors for IFFT
  int16_t *twiddle_ifft;
  ///pointer to FFT permutation vector
  uint16_t *rev;
  /// PRACH_CONFIG
  PRACH_CONFIG_COMMON prach_config_common;
  /// PUCCH Config Common (from 36-331 RRC spec)
  PUCCH_CONFIG_COMMON pucch_config_common;
  /// PDSCH Config Common (from 36-331 RRC spec)
  PDSCH_CONFIG_COMMON pdsch_config_common;
  /// PUSCH Config Common (from 36-331 RRC spec)
  PUSCH_CONFIG_COMMON pusch_config_common;
  /// PHICH Config (from 36-331 RRC spec)
  PHICH_CONFIG_COMMON phich_config_common;
  /// SRS Config (from 36-331 RRC spec)
  SOUNDINGRS_UL_CONFIG_COMMON soundingrs_ul_config_common;
  /// UL Power Control (from 36-331 RRC spec)
  UL_POWER_CONTROL_CONFIG_COMMON ul_power_control_config_common;
  /// Number of MBSFN Configurations
  int num_MBSFN_config;
  /// Array of MBSFN Configurations (max 8 (maxMBSFN-Allocations) elements as per 36.331)
  MBSFN_config_t MBSFN_config[8];
  /// Maximum Number of Retransmissions of RRCConnectionRequest (from 36-331 RRC Spec)
  uint8_t maxHARQ_Msg3Tx;
  /// Size of SI windows used for repetition of one SI message (in frames)
  uint8_t SIwindowsize;
  /// Period of SI windows used for repetition of one SI message (in frames)
  uint16_t SIPeriod;
  /// REGs assigned to PCFICH
  uint16_t pcfich_reg[4];
  /// Index of first REG assigned to PCFICH
  uint8_t pcfich_first_reg_idx;
  /// REGs assigned to PHICH
  uint16_t phich_reg[MAX_NUM_PHICH_GROUPS][3];

  struct MBSFN_SubframeConfig *mbsfn_SubframeConfig[MAX_MBSFN_AREA];

} LTE_DL_FRAME_PARMS;

typedef enum {
  SISO=0,
  ALAMOUTI=1,
  LARGE_CDD=2,
  UNIFORM_PRECODING11=3,
  UNIFORM_PRECODING1m1=4,
  UNIFORM_PRECODING1j=5,
  UNIFORM_PRECODING1mj=6,
  PUSCH_PRECODING0=7,
  PUSCH_PRECODING1=8,
  DUALSTREAM_UNIFORM_PRECODING1=9,
  DUALSTREAM_UNIFORM_PRECODINGj=10,
  DUALSTREAM_PUSCH_PRECODING=11,
  TM8=12,
  TM9_10=13
} MIMO_mode_t;

typedef struct{
  ///holds the transmit data in time domain (for IFFT_FPGA this points to the same memory as PHY_vars->rx_vars[a].RX_DMA_BUFFER)
  int32_t **txdata[3];
  /// \brief holds the transmit data in the frequency domain.
  /// For IFFT_FPGA this points to the same memory as PHY_vars->rx_vars[a].RX_DMA_BUFFER.
  /// - first index: eNB id [0..2] (hard coded)
  /// - second index: antenna [0..PHY_vars_eNB_g[0][0]->lte_frame_parms.nb_antennas_tx[
  /// - third index: samples [0..]
  mod_sym_t **txdataF[3];    
  ///holds the received data in time domain (should point to the same memory as PHY_vars->rx_vars[a].RX_DMA_BUFFER)
  int32_t **rxdata[3];
  ///holds the last subframe of received data in time domain after removal of 7.5kHz frequency offset
  int32_t **rxdata_7_5kHz[3];
  ///holds the received data in the frequency domain
  int32_t **rxdataF[3];
  /// holds output of the sync correlator
  uint32_t *sync_corr[3];
} LTE_eNB_COMMON;

typedef struct{
  /// hold the channel estimates in frequency domain based on SRS
  int32_t **srs_ch_estimates[3];
  /// hold the channel estimates in time domain based on SRS
  int32_t **srs_ch_estimates_time[3];
  /// holds the SRS for channel estimation at the RX    
  int32_t *srs;
} LTE_eNB_SRS;

typedef struct{
  ///holds the received data in the frequency domain for the allocated RBs in repeated format
  int32_t **rxdataF_ext[3];
  ///holds the received data in the frequency domain for the allocated RBs in normal format
  int32_t **rxdataF_ext2[3];
  /// hold the channel estimates in time domain based on DRS   
  int32_t **drs_ch_estimates_time[3];
  /// hold the channel estimates in frequency domain based on DRS   
  int32_t **drs_ch_estimates[3];
  /// hold the channel estimates for UE0 in case of Distributed Alamouti Scheme
  int32_t **drs_ch_estimates_0[3];
  /// hold the channel estimates for UE1 in case of Distributed Almouti Scheme 
  int32_t **drs_ch_estimates_1[3];
  /// holds the compensated signal
  int32_t **rxdataF_comp[3];
  /// hold the compensated data (y)*(h0*) in case of Distributed Alamouti Scheme
  int32_t **rxdataF_comp_0[3];
  /// hold the compensated data (y*)*(h1) in case of Distributed Alamouti Scheme
  int32_t **rxdataF_comp_1[3];
  int32_t **ul_ch_mag[3];
  int32_t **ul_ch_magb[3];
  /// hold the channel mag for UE0 in case of Distributed Alamouti Scheme
  int32_t **ul_ch_mag_0[3];
  /// hold the channel magb for UE0 in case of Distributed Alamouti Scheme
  int32_t **ul_ch_magb_0[3];
  /// hold the channel mag for UE1 in case of Distributed Alamouti Scheme
  int32_t **ul_ch_mag_1[3];
  /// hold the channel magb for UE1 in case of Distributed Alamouti Scheme
  int32_t **ul_ch_magb_1[3];
  /// measured RX power based on DRS
  int ulsch_power[2];
  /// measured RX power based on DRS for UE0 in case of Distributed Alamouti Scheme
  int ulsch_power_0[2];
  /// measured RX power based on DRS for UE0 in case of Distributed Alamouti Scheme
  int ulsch_power_1[2];
  /// llr values
  int16_t *llr;
#ifdef LOCALIZATION
  /// number of active subcarrier for a specific UE
  int32_t active_subcarrier;
  /// subcarrier power in dBm
  int32_t *subcarrier_power;
#endif
} LTE_eNB_PUSCH;

typedef struct {
  ///holds the transmit data in time domain (for IFFT_FPGA this points to the same memory as PHY_vars->tx_vars[a].TX_DMA_BUFFER)
  int32_t **txdata;
  ///holds the transmit data in the frequency domain (for IFFT_FPGA this points to the same memory as PHY_vars->rx_vars[a].RX_DMA_BUFFER)
  mod_sym_t **txdataF;    
  ///holds the received data in time domain (should point to the same memory as PHY_vars->rx_vars[a].RX_DMA_BUFFER)
  int32_t **rxdata;
  ///holds the received data in the frequency domain
  int32_t **rxdataF;
  int32_t **rxdataF2;
  /// hold the channel estimates in frequency domain
  int32_t **dl_ch_estimates[7];
  /// hold the channel estimates in time domain (used for tracking)
  int32_t **dl_ch_estimates_time[7];
  /// holds output of the sync correlator  
  int32_t *sync_corr;
  /// estimated frequency offset (in radians) for all subcarriers
  int32_t freq_offset;
  /// eNb_id user is synched to          
  int32_t eNb_id;
} LTE_UE_COMMON;

typedef struct {
  /// Received frequency-domain signal after extraction
  int32_t **rxdataF_ext;
  /// Received frequency-domain signal after extraction and channel compensation
  int32_t **rxdataF_comp0;
  /// Received frequency-domain signal after extraction and channel compensation
  int32_t **rxdataF_comp1[8];
  /// Downlink channel estimates extracted in PRBS
  int32_t **dl_ch_estimates_ext;
  /// Downlink cross-correlation of MIMO channel estimates (unquantized PMI) extracted in PRBS
  int32_t **dl_ch_rho_ext;
  /// Downlink PMIs extracted in PRBS and grouped in subbands
  uint8_t *pmi_ext;
  /// Magnitude of Downlink Channel first layer (16QAM level/First 64QAM level)
  int32_t **dl_ch_mag0;
  /// Magnitude of Downlink Channel second layer (16QAM level/First 64QAM level)
  int32_t **dl_ch_mag1;
  /// Magnitude of Downlink Channel, first layer (2nd 64QAM level)
  int32_t **dl_ch_magb0;
  /// Magnitude of Downlink Channel second layer (2nd 64QAM level)
  int32_t **dl_ch_magb1;
  /// Cross-correlation of two eNB signals
  int32_t **rho;
  /// never used... always send dl_ch_rho_ext instead...
  int32_t **rho_i;
  /// Pointers to llr vectors (2 TBs)
  int16_t *llr[2];
  /// \f$\log_2(\max|H_i|^2)\f$
  int16_t log2_maxh;
  /// LLR shifts for subband scaling
  uint8_t *llr_shifts;
  /// Pointer to LLR shifts
  uint8_t *llr_shifts_p;
  /// Pointers to llr vectors (128-bit alignment)
  int16_t **llr128;
  //uint32_t *rb_alloc;
  //uint8_t Qm[2];
  //MIMO_mode_t mimo_mode;
} LTE_UE_PDSCH;

typedef struct {
  /// Received frequency-domain signal after extraction
  int32_t **rxdataF_ext;
  /// Received frequency-domain signal after extraction and channel compensation
  double **rxdataF_comp;
  /// Downlink channel estimates extracted in PRBS
  int32_t **dl_ch_estimates_ext;
  /// Downlink cross-correlation of MIMO channel estimates (unquantized PMI) extracted in PRBS
  double **dl_ch_rho_ext;
  /// Downlink PMIs extracted in PRBS and grouped in subbands
  uint8_t *pmi_ext;
  /// Magnitude of Downlink Channel (16QAM level/First 64QAM level)
  double **dl_ch_mag;
  /// Magnitude of Downlink Channel (2nd 64QAM level)
  double **dl_ch_magb;
  /// Cross-correlation of two eNB signals
  double **rho;
  /// never used... always send dl_ch_rho_ext instead...
  double **rho_i;  
  /// Pointers to llr vectors (2 TBs)
  int16_t *llr[2];
  /// \f$\log_2(\max|H_i|^2)\f$
  uint8_t log2_maxh;
  /// Pointers to llr vectors (128-bit alignment)
  int16_t **llr128;
  //uint32_t *rb_alloc;
  //uint8_t Qm[2];
  //MIMO_mode_t mimo_mode;
} LTE_UE_PDSCH_FLP;

typedef struct {
  /// pointers to extracted PDCCH symbols in frequency-domain
  int32_t **rxdataF_ext;
  /// pointers to extracted and compensated PDCCH symbols in frequency-domain
  int32_t **rxdataF_comp;
  /// pointers to extracted channel estimates of PDCCH symbols
  int32_t **dl_ch_estimates_ext;
  /// pointers to channel cross-correlation vectors for multi-eNB detection
  int32_t **dl_ch_rho_ext;
  /// pointers to channel cross-correlation vectors for multi-eNB detection
  int32_t **rho;
  /// pointer to llrs, 4-bit resolution
  uint16_t *llr;
  /// pointer to llrs, 16-bit resolution
  uint16_t *llr16;
  /// \f$\overline{w}\f$ from 36-211
  uint16_t *wbar;
  /// PDCCH/DCI e-sequence (input to rate matching)
  int8_t *e_rx;
  /// number of PDCCH symbols in current subframe
  uint8_t num_pdcch_symbols;
  /// Allocated CRNTI for UE
  uint16_t crnti;
  /// Total number of PDU errors (diagnostic mode)
  uint32_t dci_errors;
  /// Total number of PDU received
  uint32_t dci_received;
  /// Total number of DCI False detection (diagnostic mode)
  uint32_t dci_false;
  /// Total number of DCI missed (diagnostic mode)
  uint32_t dci_missed;
  /// nCCE for PUCCH per subframe
  uint8_t nCCE[10];
} LTE_UE_PDCCH;

#define PBCH_A 24
typedef struct {
  uint8_t pbch_d[96+(3*(16+PBCH_A))];
  uint8_t pbch_w[3*3*(16+PBCH_A)];
  uint8_t pbch_e[1920];
} LTE_eNB_PBCH;

typedef struct {
  /// Pointers to extracted PBCH symbols in frequency-domain
  int32_t **rxdataF_ext;
  /// Pointers to extracted and compensated PBCH symbols in frequency-domain
  int32_t **rxdataF_comp;
  /// Pointers to downlink channel estimates in frequency-domain extracted in PRBS
  int32_t **dl_ch_estimates_ext;
  /// Pointer to PBCH llrs
  int8_t *llr;
  /// Pointer to PBCH decoded output
  uint8_t *decoded_output;
  /// Total number of PDU errors
  uint32_t pdu_errors;
  /// Total number of PDU errors 128 frames ago
  uint32_t pdu_errors_last;
  /// Total number of consecutive PDU errors
  uint32_t pdu_errors_conseq;
  /// FER (in percent) 
  uint32_t pdu_fer;
} LTE_UE_PBCH;

typedef struct {
  int16_t amp;
  int16_t *prachF;
  int16_t *prach;
} LTE_UE_PRACH;

typedef struct {
  int16_t *prachF;
  int16_t *rxsigF[4];
} LTE_eNB_PRACH;

typedef struct {
  /// Preamble index for PRACH (0-63)
  uint8_t ra_PreambleIndex;
  /// RACH MaskIndex
  uint8_t ra_RACH_MaskIndex;
  /// Target received power at eNB (-120 ... -82 dBm)
  int8_t ra_PREAMBLE_RECEIVED_TARGET_POWER;
  /// PRACH index for TDD (0 ... 6) depending on TDD configuration and prachConfigIndex
  uint8_t ra_TDD_map_index;
  /// Corresponding RA-RNTI for UL-grant
  uint16_t ra_RNTI;
  /// Pointer to Msg3 payload for UL-grant
  uint8_t *Msg3;
} PRACH_RESOURCES_t;

typedef struct {
  /// Downlink Power offset field
  uint8_t dl_pow_off;
  ///Subband resource allocation field
  uint8_t rballoc_sub[50];
  ///Total number of PRBs indicator
  uint8_t pre_nb_available_rbs;
}MU_MIMO_mode;

typedef enum {
  NOT_SYNCHED=0,
  PRACH=1,
  RA_RESPONSE=2,
  PUSCH=3,
  RESYNCH=4
} UE_MODE_t;



typedef enum {SF_DL, SF_UL, SF_S} lte_subframe_t;

#endif


