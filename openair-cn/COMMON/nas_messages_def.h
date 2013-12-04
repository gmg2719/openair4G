//WARNING: Do not include this header directly. Use intertask_interface.h instead.

MESSAGE_DEF(NAS_PAGING_IND,                   MESSAGE_PRIORITY_MED, nas_paging_ind_t,    nas_paging_ind)
MESSAGE_DEF(NAS_CONNECTION_ESTABLISHMENT_IND, MESSAGE_PRIORITY_MED, nas_conn_est_ind_t,  nas_conn_est_ind)
MESSAGE_DEF(NAS_CONNECTION_ESTABLISHMENT_CNF, MESSAGE_PRIORITY_MED, nas_conn_est_cnf_t,  nas_conn_est_cnf)
MESSAGE_DEF(NAS_CONNECTION_RELEASE_IND,       MESSAGE_PRIORITY_MED, nas_conn_rel_ind_t,  nas_conn_rel_ind)
MESSAGE_DEF(NAS_UPLINK_DATA_IND,              MESSAGE_PRIORITY_MED, nas_ul_data_ind_t,   nas_ul_data_ind)
MESSAGE_DEF(NAS_DOWNLINK_DATA_REQ,            MESSAGE_PRIORITY_MED, nas_dl_data_req_t,   nas_dl_data_req)
MESSAGE_DEF(NAS_DOWNLINK_DATA_CNF,            MESSAGE_PRIORITY_MED, nas_dl_data_cnf_t,   nas_dl_data_cnf)
MESSAGE_DEF(NAS_NON_DELIVERY_IND,             MESSAGE_PRIORITY_MED, nas_non_del_ind_t,   nas_non_del_ind)
MESSAGE_DEF(NAS_RAB_ESTABLISHMENT_REQ,        MESSAGE_PRIORITY_MED, nas_rab_est_req_t,   nas_rab_est_req)
MESSAGE_DEF(NAS_RAB_ESTABLISHMENT_RESP,       MESSAGE_PRIORITY_MED, nas_rab_est_rsp_t,   nas_rab_est_rsp)
MESSAGE_DEF(NAS_RAB_RELEASE_REQ,              MESSAGE_PRIORITY_MED, nas_rab_rel_req_t,   nas_rab_rel_req)

/* NAS layer -> MME app messages */
MESSAGE_DEF(NAS_AUTHENTICATION_REQ,           MESSAGE_PRIORITY_MED, nas_auth_req_t,       nas_auth_req)
MESSAGE_DEF(NAS_AUTHENTICATION_PARAM_REQ,     MESSAGE_PRIORITY_MED, nas_auth_param_req_t, nas_auth_param_req)

/* MME app -> NAS layer messages */
MESSAGE_DEF(NAS_BEARER_PARAM,                 MESSAGE_PRIORITY_MED, nas_bearer_param_t,  nas_bearer_param)
MESSAGE_DEF(NAS_AUTHENTICATION_RESP,          MESSAGE_PRIORITY_MED, nas_auth_resp_t,     nas_auth_resp)

#if defined(DISABLE_USE_NAS)
MESSAGE_DEF(NAS_ATTACH_REQ,                   MESSAGE_PRIORITY_MED, nas_attach_req_t,    nas_attach_req)
MESSAGE_DEF(NAS_ATTACH_ACCEPT,                MESSAGE_PRIORITY_MED, nas_attach_accept_t, nas_attach_accept)
#endif