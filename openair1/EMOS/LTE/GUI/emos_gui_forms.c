/* Form definition file generated by fdesign */

#include <stdlib.h>
#include "emos_gui_forms.h"


/***************************************
 ***************************************/

FD_main_frm *
create_form_main_frm( void )
{
    FL_OBJECT *obj;
    FD_main_frm *fdui = fl_malloc( sizeof *fdui );

    fdui->vdata = fdui->cdata = NULL;
    fdui->ldata = 0;

    fdui->main_frm = fl_bgn_form( FL_NO_BOX, 1010, 710 );

    obj = fl_add_box( FL_FLAT_BOX, 0, 0, 1010, 710, "Main form" );
    fl_set_object_color( obj, FL_LIGHTER_COL1, FL_MCOL );
    fl_set_object_lalign( obj, FL_ALIGN_TOP );

    obj = fl_add_box( FL_ROUNDED_BOX, 10, 610, 230, 90, "" );
    fl_set_object_color( obj, FL_DARKER_COL1, FL_COL1 );
    fl_set_object_lalign( obj, FL_ALIGN_LEFT | FL_ALIGN_INSIDE );

    obj = fl_add_box( FL_ROUNDED3D_DOWNBOX, 5, 5, 850, 600, "" );
    fl_set_object_color( obj, FL_BLACK, FL_BLACK );

    fdui->sync_lbl = obj = fl_add_text( FL_NORMAL_TEXT, 635, 15, 40, 20, "sync" );
    fl_set_object_boxtype( obj, FL_ROUNDED_BOX );
    fl_set_object_color( obj, FL_BLACK, FL_TOP_BCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER | FL_ALIGN_INSIDE );
    fl_set_object_lstyle( obj, FL_BOLD_STYLE );

    fdui->rec_lbl = obj = fl_add_text( FL_NORMAL_TEXT, 720, 15, 40, 20, "rec" );
    fl_set_object_boxtype( obj, FL_ROUNDED_BOX );
    fl_set_object_color( obj, FL_BLACK, FL_TOP_BCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER | FL_ALIGN_INSIDE );
    fl_set_object_lstyle( obj, FL_BOLD_STYLE );

    fdui->pwr1_xyp = obj = fl_add_xyplot( FL_NORMAL_XYPLOT, 20, 45, 300, 110, "Power" );
    fl_set_object_color( obj, FL_BLACK, FL_RIGHT_BCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lalign( obj, FL_ALIGN_TOP );

    fdui->pwr2_xyp = obj = fl_add_xyplot( FL_NORMAL_XYPLOT, 330, 45, 300, 110, "Power" );
    fl_set_object_color( obj, FL_BLACK, FL_RIGHT_BCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lalign( obj, FL_ALIGN_TOP );

    fdui->rx2_lbl = obj = fl_add_text( FL_NORMAL_TEXT, 345, 10, 80, 40, "RX 2" );
    fl_set_object_color( obj, FL_BLACK, FL_MCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lsize( obj, FL_HUGE_SIZE );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER | FL_ALIGN_INSIDE );
    fl_set_object_lstyle( obj, FL_BOLD_STYLE );

    fdui->noise1_xyp = obj = fl_add_xyplot( FL_NORMAL_XYPLOT, 20, 170, 300, 110, "N0/SNR" );
    fl_set_object_color( obj, FL_BLACK, FL_RIGHT_BCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lalign( obj, FL_ALIGN_TOP );

    fdui->noise2_xyp = obj = fl_add_xyplot( FL_NORMAL_XYPLOT, 330, 170, 300, 110, "N0/SNR" );
    fl_set_object_color( obj, FL_BLACK, FL_RIGHT_BCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lalign( obj, FL_ALIGN_TOP );

    fdui->ch11_sec0_xyp = obj = fl_add_xyplot( FL_NORMAL_XYPLOT, 10, 325, 140, 110, "CH 11" );
    fl_set_object_color( obj, FL_BLACK, FL_RIGHT_BCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lalign( obj, FL_ALIGN_TOP );

    fdui->ch12_sec0_xyp = obj = fl_add_xyplot( FL_NORMAL_XYPLOT, 145, 325, 140, 110, "CH 12" );
    fl_set_object_color( obj, FL_BLACK, FL_RIGHT_BCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lalign( obj, FL_ALIGN_TOP );

    fdui->ch21_sec0_xyp = obj = fl_add_xyplot( FL_NORMAL_XYPLOT, 10, 455, 140, 110, "CH 21" );
    fl_set_object_color( obj, FL_BLACK, FL_RIGHT_BCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lalign( obj, FL_ALIGN_TOP );

    fdui->ch22_sec0_xyp = obj = fl_add_xyplot( FL_NORMAL_XYPLOT, 145, 455, 140, 110, "CH 22" );
    fl_set_object_color( obj, FL_BLACK, FL_RIGHT_BCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lalign( obj, FL_ALIGN_TOP );

    fdui->ch11_sec1_xyp = obj = fl_add_xyplot( FL_NORMAL_XYPLOT, 290, 325, 140, 110, "CH 11" );
    fl_set_object_color( obj, FL_BLACK, FL_RIGHT_BCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lalign( obj, FL_ALIGN_TOP );

    fdui->ch12_sec1_xyp = obj = fl_add_xyplot( FL_NORMAL_XYPLOT, 430, 325, 140, 110, "CH 12" );
    fl_set_object_color( obj, FL_BLACK, FL_RIGHT_BCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lalign( obj, FL_ALIGN_TOP );

    fdui->ch21_sec1_xyp = obj = fl_add_xyplot( FL_NORMAL_XYPLOT, 290, 455, 140, 110, "CH 21" );
    fl_set_object_color( obj, FL_BLACK, FL_RIGHT_BCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lalign( obj, FL_ALIGN_TOP );

    fdui->ch22_sec1_xyp = obj = fl_add_xyplot( FL_NORMAL_XYPLOT, 430, 455, 140, 110, "CH 22" );
    fl_set_object_color( obj, FL_BLACK, FL_RIGHT_BCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lalign( obj, FL_ALIGN_TOP );

    fdui->error_lbl = obj = fl_add_text( FL_NORMAL_TEXT, 680, 15, 40, 20, "error" );
    fl_set_object_boxtype( obj, FL_ROUNDED_BOX );
    fl_set_object_color( obj, FL_BLACK, FL_TOP_BCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER | FL_ALIGN_INSIDE );
    fl_set_object_lstyle( obj, FL_BOLD_STYLE );

    fdui->gps_lbl = obj = fl_add_text( FL_NORMAL_TEXT, 640, 65, 60, 30, "gps" );
    fl_set_object_boxtype( obj, FL_ROUNDED_BOX );
    fl_set_object_color( obj, FL_BLACK, FL_TOP_BCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER | FL_ALIGN_INSIDE );
    fl_set_object_lstyle( obj, FL_BOLD_STYLE );

    fdui->date_lbl = obj = fl_add_text( FL_NORMAL_TEXT, 655, 120, 170, 30, "date: " );
    fl_set_object_color( obj, FL_BLACK, FL_TOP_BCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER | FL_ALIGN_INSIDE );
    fl_set_object_lstyle( obj, FL_BOLD_STYLE );

    fdui->gps_lat_lbl = obj = fl_add_text( FL_NORMAL_TEXT, 700, 65, 150, 30, "lat: 0" );
    fl_set_object_color( obj, FL_BLACK, FL_TOP_BCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lstyle( obj, FL_BOLD_STYLE );

    fdui->gps_lon_lbl = obj = fl_add_text( FL_NORMAL_TEXT, 700, 95, 150, 30, "lon: 0" );
    fl_set_object_color( obj, FL_BLACK, FL_TOP_BCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lstyle( obj, FL_BOLD_STYLE );

    fdui->idx_lbl = obj = fl_add_text( FL_NORMAL_TEXT, 685, 150, 110, 20, "Idx: " );
    fl_set_object_color( obj, FL_BLACK, FL_TOP_BCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER | FL_ALIGN_INSIDE );
    fl_set_object_lstyle( obj, FL_BOLD_STYLE );

    obj = fl_add_box( FL_ROUNDED_BOX, 485, 610, 140, 90, "" );
    fl_set_object_color( obj, FL_DARKCYAN, FL_COL1 );
    fl_set_object_lalign( obj, FL_ALIGN_LEFT | FL_ALIGN_INSIDE );

    fdui->power_btn = obj = fl_add_button( FL_NORMAL_BUTTON, 130, 620, 100, 70, "PWR" );
    fl_set_object_boxtype( obj, FL_ROUNDED3D_UPBOX );
    fl_set_object_color( obj, FL_LIGHTER_COL1, FL_COL1 );
    fl_set_object_lsize( obj, FL_MEDIUM_SIZE );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER );
    fl_set_object_callback( obj, power_callback, 0 );

    fdui->buffer_lbl = obj = fl_add_text( FL_NORMAL_TEXT, 760, 15, 90, 20, "Buffer: 100%" );
    fl_set_object_boxtype( obj, FL_ROUNDED_BOX );
    fl_set_object_color( obj, FL_BLACK, FL_TOP_BCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lsize( obj, FL_TINY_SIZE );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER | FL_ALIGN_INSIDE );
    fl_set_object_lstyle( obj, FL_BOLD_STYLE );

    fdui->refresh_lbl = obj = fl_add_text( FL_NORMAL_TEXT, 655, 175, 170, 20, "Refresh interval: 1s" );
    fl_set_object_color( obj, FL_BLACK, FL_TOP_BCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER | FL_ALIGN_INSIDE );
    fl_set_object_lstyle( obj, FL_BOLD_STYLE );

    obj = fl_add_box( FL_ROUNDED_BOX, 860, 90, 140, 220, "" );
    fl_set_object_color( obj, FL_DARKER_COL1, FL_COL1 );
    fl_set_object_lalign( obj, FL_ALIGN_LEFT | FL_ALIGN_INSIDE );

    fdui->refresh_dial = obj = fl_add_dial( FL_NORMAL_DIAL, 890, 110, 80, 70, "screen refresh rate" );
    fl_set_object_boxtype( obj, FL_ROUNDED3D_UPBOX );
    fl_set_object_color( obj, FL_LIGHTER_COL1, FL_RIGHT_BCOL );
    fl_set_object_lsize( obj, FL_TINY_SIZE );
    fl_set_object_lalign( obj, FL_ALIGN_TOP );
    fl_set_object_callback( obj, refresh_callback, 0 );
    fl_set_object_return( obj, FL_RETURN_CHANGED );
    fl_set_dial_bounds( obj, 0, 5 );
    fl_set_dial_angles( obj, 45, 315 );
    fl_set_dial_value( obj, 1 );
    fl_set_dial_step( obj, 1 );

    obj = fl_add_box( FL_ROUNDED_BOX, 860, 528, 137, 72, "" );
    fl_set_object_color( obj, FL_INDIANRED, FL_COL1 );
    fl_set_object_lalign( obj, FL_ALIGN_LEFT | FL_ALIGN_INSIDE );

    fdui->bler_lbl = obj = fl_add_text( FL_NORMAL_TEXT, 650, 200, 180, 20, "BLER:" );
    fl_set_object_color( obj, FL_BLACK, FL_TOP_BCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER | FL_ALIGN_INSIDE );
    fl_set_object_lstyle( obj, FL_BOLD_STYLE );

    fdui->n_recd_frames_lbl = obj = fl_add_text( FL_NORMAL_TEXT, 650, 225, 180, 20, "Rec'd frms:" );
    fl_set_object_color( obj, FL_BLACK, FL_TOP_BCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER | FL_ALIGN_INSIDE );
    fl_set_object_lstyle( obj, FL_BOLD_STYLE );

    fdui->msg_text = obj = fl_add_text( FL_NORMAL_TEXT, 25, 570, 810, 30, "" );
    fl_set_object_color( obj, FL_BLACK, FL_MCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );

    obj = fl_add_pixmapbutton( FL_NORMAL_BUTTON, 860, 5, 140, 70, "" );
    fl_set_object_boxtype( obj, FL_ROUNDED_BOX );
    fl_set_object_color( obj, FL_WHITE, FL_YELLOW );
    fl_set_pixmapbutton_file( obj, "Eurecom_Logo.xpm" );

    fdui->rx1_lbl = obj = fl_add_text( FL_NORMAL_TEXT, 35, 10, 80, 40, "RX 1" );
    fl_set_object_color( obj, FL_BLACK, FL_MCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lsize( obj, FL_HUGE_SIZE );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER | FL_ALIGN_INSIDE );
    fl_set_object_lstyle( obj, FL_BOLD_STYLE );

    fdui->alamouti_btn = obj = fl_add_button( FL_PUSH_BUTTON, 505, 655, 100, 20, "2: ALAMOUTI" );
    fl_set_object_boxtype( obj, FL_ROUNDED3D_UPBOX );
    fl_set_object_color( obj, FL_LIGHTER_COL1, FL_COL1 );
    fl_set_object_lsize( obj, FL_TINY_SIZE );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER );
    fl_set_object_callback( obj, rx_mode_button_callback, 2 );

    fdui->precoding_btn = obj = fl_add_button( FL_PUSH_BUTTON, 505, 675, 100, 20, "6: PRECODING" );
    fl_set_object_boxtype( obj, FL_ROUNDED3D_UPBOX );
    fl_set_object_color( obj, FL_LIGHTER_COL1, FL_COL1 );
    fl_set_object_lsize( obj, FL_TINY_SIZE );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER );
    fl_set_object_callback( obj, rx_mode_button_callback, 6 );

    fdui->cbmimo_lbl = obj = fl_add_text( FL_NORMAL_TEXT, 665, 40, 70, 20, "cbmimo" );
    fl_set_object_boxtype( obj, FL_ROUNDED_BOX );
    fl_set_object_color( obj, FL_BLACK, FL_TOP_BCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER | FL_ALIGN_INSIDE );
    fl_set_object_lstyle( obj, FL_BOLD_STYLE );

    fdui->fix_lbl = obj = fl_add_text( FL_NORMAL_TEXT, 640, 95, 60, 30, "NO" );
    fl_set_object_boxtype( obj, FL_ROUNDED_BOX );
    fl_set_object_color( obj, FL_BLACK, FL_TOP_BCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER | FL_ALIGN_INSIDE );
    fl_set_object_lstyle( obj, FL_BOLD_STYLE );

    obj = fl_add_box( FL_ROUNDED_BOX, 800, 610, 200, 90, "" );
    fl_set_object_color( obj, FL_INDIANRED, FL_COL1 );
    fl_set_object_lalign( obj, FL_ALIGN_LEFT | FL_ALIGN_INSIDE );

    fdui->rec_btn = obj = fl_add_button( FL_NORMAL_BUTTON, 820, 620, 160, 70, "Record" );
    fl_set_object_boxtype( obj, FL_ROUNDED3D_UPBOX );
    fl_set_object_color( obj, FL_LIGHTER_COL1, FL_COL1 );
    fl_set_object_lsize( obj, FL_TINY_SIZE );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER );
    fl_set_object_callback( obj, record_callback, 0 );

    fdui->exit_btn = obj = fl_add_button( FL_NORMAL_BUTTON, 20, 660, 90, 30, "exit" );
    fl_set_object_boxtype( obj, FL_ROUNDED3D_UPBOX );
    fl_set_object_color( obj, FL_TOMATO, FL_COL1 );
    fl_set_object_lsize( obj, FL_TINY_SIZE );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER );
    fl_set_object_callback( obj, exit_callback, 0 );

    fdui->config_btn = obj = fl_add_button( FL_NORMAL_BUTTON, 20, 620, 90, 30, "config" );
    fl_set_object_boxtype( obj, FL_ROUNDED3D_UPBOX );
    fl_set_object_color( obj, FL_LIGHTER_COL1, FL_COL1 );
    fl_set_object_lsize( obj, FL_TINY_SIZE );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER );
    fl_set_object_callback( obj, config_btn_callback, 0 );

    obj = fl_add_button( FL_NORMAL_BUTTON, 870, 180, 40, 30, "+" );
    fl_set_object_boxtype( obj, FL_ROUNDED3D_UPBOX );
    fl_set_object_color( obj, FL_LIGHTER_COL1, FL_COL1 );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER );
    fl_set_object_lstyle( obj, FL_BOLD_STYLE );
    fl_set_object_callback( obj, refresh_callback, 1 );

    obj = fl_add_button( FL_NORMAL_BUTTON, 950, 180, 40, 30, "-" );
    fl_set_object_boxtype( obj, FL_ROUNDED3D_UPBOX );
    fl_set_object_color( obj, FL_LIGHTER_COL1, FL_COL1 );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER );
    fl_set_object_lstyle( obj, FL_BOLD_STYLE );
    fl_set_object_callback( obj, refresh_callback, -1 );

    fdui->time_domain_btn = obj = fl_add_button( FL_PUSH_BUTTON, 870, 235, 60, 20, "time" );
    fl_set_object_boxtype( obj, FL_ROUNDED3D_UPBOX );
    fl_set_object_color( obj, FL_LIGHTER_COL1, FL_COL1 );
    fl_set_object_lsize( obj, FL_TINY_SIZE );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER );
    fl_set_object_callback( obj, time_freq_callback, 0 );

    fdui->freq_domain_btn = obj = fl_add_button( FL_PUSH_BUTTON, 930, 235, 60, 20, "freq" );
    fl_set_object_boxtype( obj, FL_ROUNDED3D_UPBOX );
    fl_set_object_color( obj, FL_LIGHTER_COL1, FL_COL1 );
    fl_set_object_lsize( obj, FL_TINY_SIZE );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER );
    fl_set_object_callback( obj, time_freq_callback, 1 );

    obj = fl_add_text( FL_NORMAL_TEXT, 875, 215, 110, 20, "channel display" );
    fl_set_object_color( obj, FL_DARKER_COL1, FL_MCOL );
    fl_set_object_lsize( obj, FL_TINY_SIZE );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER | FL_ALIGN_INSIDE );

    fdui->refresh_timer = obj = fl_add_timer( FL_HIDDEN_TIMER, 810, 720, 10, 10, "timer" );
    fl_set_object_callback( obj, refresh_timer_callback, 0 );

    obj = fl_add_text( FL_NORMAL_TEXT, 875, 260, 110, 20, "N0/SNR" );
    fl_set_object_color( obj, FL_DARKER_COL1, FL_MCOL );
    fl_set_object_lsize( obj, FL_TINY_SIZE );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER | FL_ALIGN_INSIDE );

    fdui->n0_btn = obj = fl_add_button( FL_PUSH_BUTTON, 870, 280, 60, 20, "N0" );
    fl_set_object_boxtype( obj, FL_ROUNDED3D_UPBOX );
    fl_set_object_color( obj, FL_LIGHTER_COL1, FL_COL1 );
    fl_set_object_lsize( obj, FL_TINY_SIZE );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER );
    fl_set_object_callback( obj, noise_snr_callback, 0 );

    fdui->snr_btn = obj = fl_add_button( FL_PUSH_BUTTON, 930, 280, 60, 20, "SNR" );
    fl_set_object_boxtype( obj, FL_ROUNDED3D_UPBOX );
    fl_set_object_color( obj, FL_LIGHTER_COL1, FL_COL1 );
    fl_set_object_lsize( obj, FL_TINY_SIZE );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER );
    fl_set_object_callback( obj, noise_snr_callback, 1 );

    fdui->rx_mode_lbl = obj = fl_add_text( FL_NORMAL_TEXT, 650, 250, 180, 20, "RX mode:" );
    fl_set_object_color( obj, FL_BLACK, FL_TOP_BCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER | FL_ALIGN_INSIDE );
    fl_set_object_lstyle( obj, FL_BOLD_STYLE );

    fdui->siso_btn = obj = fl_add_button( FL_PUSH_BUTTON, 505, 635, 100, 20, "1: SISO" );
    fl_set_object_boxtype( obj, FL_ROUNDED3D_UPBOX );
    fl_set_object_color( obj, FL_LIGHTER_COL1, FL_COL1 );
    fl_set_object_lsize( obj, FL_TINY_SIZE );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER );
    fl_set_object_callback( obj, rx_mode_button_callback, 1 );

    obj = fl_add_text( FL_NORMAL_TEXT, 505, 615, 100, 20, "TX mode" );
    fl_set_object_boxtype( obj, FL_NO_BOX );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER | FL_ALIGN_INSIDE );

    fdui->ch11_sec2_xyp = obj = fl_add_xyplot( FL_NORMAL_XYPLOT, 570, 325, 140, 110, "CH 11" );
    fl_set_object_color( obj, FL_BLACK, FL_RIGHT_BCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lalign( obj, FL_ALIGN_TOP );

    fdui->ch12_sec2_xyp = obj = fl_add_xyplot( FL_NORMAL_XYPLOT, 710, 325, 140, 110, "CH 12" );
    fl_set_object_color( obj, FL_BLACK, FL_RIGHT_BCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lalign( obj, FL_ALIGN_TOP );

    fdui->ch21_sec2_xyp = obj = fl_add_xyplot( FL_NORMAL_XYPLOT, 570, 455, 140, 110, "CH 21" );
    fl_set_object_color( obj, FL_BLACK, FL_RIGHT_BCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lalign( obj, FL_ALIGN_TOP );

    fdui->ch22_sec2_xyp = obj = fl_add_xyplot( FL_NORMAL_XYPLOT, 710, 455, 140, 110, "CH 22" );
    fl_set_object_color( obj, FL_BLACK, FL_RIGHT_BCOL );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lalign( obj, FL_ALIGN_TOP );

    fdui->sec0_lbl = obj = fl_add_text( FL_NORMAL_TEXT, 85, 285, 140, 20, "Sector 0" );
    fl_set_object_color( obj, FL_BLACK, FL_BLACK );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lsize( obj, FL_MEDIUM_SIZE );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER | FL_ALIGN_INSIDE );

    fdui->sec1_lbl = obj = fl_add_text( FL_NORMAL_TEXT, 380, 285, 140, 20, "Sector 1" );
    fl_set_object_color( obj, FL_BLACK, FL_BLACK );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lsize( obj, FL_MEDIUM_SIZE );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER | FL_ALIGN_INSIDE );

    fdui->sec2_lbl = obj = fl_add_text( FL_NORMAL_TEXT, 650, 285, 140, 20, "Sector 2" );
    fl_set_object_color( obj, FL_BLACK, FL_BLACK );
    fl_set_object_lcolor( obj, FL_RIGHT_BCOL );
    fl_set_object_lsize( obj, FL_MEDIUM_SIZE );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER | FL_ALIGN_INSIDE );

    obj = fl_add_box( FL_ROUNDED_BOX, 250, 610, 130, 90, "" );
    fl_set_object_color( obj, FL_PALEGREEN, FL_COL1 );
    fl_set_object_lalign( obj, FL_ALIGN_LEFT | FL_ALIGN_INSIDE );

    fdui->terminal_btn1 = obj = fl_add_button( FL_PUSH_BUTTON, 265, 632, 40, 28, "eNb" );
    fl_set_object_boxtype( obj, FL_ROUNDED3D_UPBOX );
    fl_set_object_color( obj, FL_LIGHTER_COL1, FL_COL1 );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER );
    fl_set_object_lstyle( obj, FL_BOLD_STYLE );
    fl_set_object_callback( obj, terminal_button_callback, 1 );

    fdui->terminal_btn3 = obj = fl_add_button( FL_PUSH_BUTTON, 320, 633, 41, 28, "UE" );
    fl_set_object_boxtype( obj, FL_ROUNDED3D_UPBOX );
    fl_set_object_color( obj, FL_LIGHTER_COL1, FL_COL1 );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER );
    fl_set_object_lstyle( obj, FL_BOLD_STYLE );
    fl_set_object_callback( obj, terminal_button_callback, 3 );

    obj = fl_add_text( FL_NORMAL_TEXT, 260, 611, 110, 20, "terminal type" );
    fl_set_object_color( obj, FL_PALEGREEN, FL_MCOL );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER | FL_ALIGN_INSIDE );

    obj = fl_add_box( FL_ROUNDED_BOX, 630, 610, 160, 90, "" );
    fl_set_object_color( obj, FL_WHEAT, FL_COL1 );
    fl_set_object_lalign( obj, FL_ALIGN_LEFT | FL_ALIGN_INSIDE );

    obj = fl_add_button( FL_NORMAL_BUTTON, 645, 660, 90, 30, "Checkpoint" );
    fl_set_object_boxtype( obj, FL_ROUNDED3D_UPBOX );
    fl_set_object_color( obj, FL_LIGHTER_COL1, FL_COL1 );
    fl_set_object_lsize( obj, FL_TINY_SIZE );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER );
    fl_set_object_callback( obj, checkpoint_callback, 0 );

    obj = fl_add_button( FL_NORMAL_BUTTON, 740, 620, 40, 30, "+" );
    fl_set_object_boxtype( obj, FL_ROUNDED3D_UPBOX );
    fl_set_object_color( obj, FL_LIGHTER_COL1, FL_COL1 );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER );
    fl_set_object_lstyle( obj, FL_BOLD_STYLE );
    fl_set_object_callback( obj, checkpoint_callback, 1 );

    obj = fl_add_button( FL_NORMAL_BUTTON, 740, 660, 40, 30, "-" );
    fl_set_object_boxtype( obj, FL_ROUNDED3D_UPBOX );
    fl_set_object_color( obj, FL_LIGHTER_COL1, FL_COL1 );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER );
    fl_set_object_lstyle( obj, FL_BOLD_STYLE );
    fl_set_object_callback( obj, checkpoint_callback, -1 );

    fdui->next_cp = obj = fl_add_text( FL_NORMAL_TEXT, 650, 625, 90, 20, "Next CP: 1" );
    fl_set_object_color( obj, FL_WHEAT, FL_MCOL );

    obj = fl_add_box( FL_ROUNDED_BOX, 860, 320, 142, 199, "" );
    fl_set_object_color( obj, FL_PALEGREEN, FL_COL1 );

    fdui->rf_gain_txt = obj = fl_add_input( FL_NORMAL_INPUT, 925, 340, 60, 20, "RF gain" );
    fl_set_object_lsize( obj, FL_TINY_SIZE );
    fl_set_object_callback( obj, input_callback, 0 );
    fl_set_object_return( obj, FL_RETURN_END_CHANGED );

    fdui->digital_gain_txt = obj = fl_add_input( FL_NORMAL_INPUT, 925, 374, 60, 20, "digital gain" );
    fl_set_object_lsize( obj, FL_TINY_SIZE );
    fl_set_object_callback( obj, input_callback, 0 );
    fl_set_object_return( obj, FL_RETURN_END_CHANGED );

    fdui->rf_mode_txt = obj = fl_add_input( FL_NORMAL_INPUT, 925, 409, 60, 20, "RF mode" );
    fl_set_object_lsize( obj, FL_TINY_SIZE );
    fl_set_object_callback( obj, input_callback, 0 );
    fl_set_object_return( obj, FL_RETURN_END_CHANGED );

    obj = fl_add_box( FL_ROUNDED_BOX, 390, 610, 90, 90, "" );
    fl_set_object_color( obj, FL_DARKCYAN, FL_COL1 );
    fl_set_object_lalign( obj, FL_ALIGN_LEFT | FL_ALIGN_INSIDE );

    fdui->la_btn = obj = fl_add_lightbutton( FL_PUSH_BUTTON, 405, 645, 60, 40, "LA" );
    fl_set_object_callback( obj, link_adpt_callback, 0 );
    fl_set_button( obj, 1 );

    obj = fl_add_text( FL_NORMAL_TEXT, 400, 620, 70, 20, "link adpt." );
    fl_set_object_color( obj, FL_DARKCYAN, FL_MCOL );

    fdui->label_input = obj = fl_add_input( FL_NORMAL_INPUT, 880, 569, 100, 20, "" );
    fl_set_object_lsize( obj, FL_TINY_SIZE );
    fl_set_object_lalign( obj, FL_ALIGN_TOP );
    fl_set_object_callback( obj, label_callback, 0 );
    fl_set_object_return( obj, FL_RETURN_END_CHANGED );

    fdui->label_button = obj = fl_add_checkbutton( FL_PUSH_BUTTON, 877, 539, 60, 30, "manual label" );
    fl_set_object_callback( obj, label_btn_callback, 0 );

    fdui->freq_txt = obj = fl_add_input( FL_NORMAL_INPUT, 925, 444, 60, 20, "frequency" );
    fl_set_object_lsize( obj, FL_TINY_SIZE );
    fl_set_object_callback( obj, input_callback, 0 );
    fl_set_object_return( obj, FL_RETURN_END_CHANGED );

    fdui->tcxo_txt = obj = fl_add_input( FL_NORMAL_INPUT, 925, 479, 60, 20, "TCXO" );
    fl_set_object_lsize( obj, FL_TINY_SIZE );
    fl_set_object_callback( obj, input_callback, 0 );
    fl_set_object_return( obj, FL_RETURN_END_CHANGED );

    fdui->tdd_button = obj = fl_add_button( FL_PUSH_BUTTON, 265, 664, 40, 28, "TDD" );
    fl_set_object_boxtype( obj, FL_ROUNDED3D_UPBOX );
    fl_set_object_color( obj, FL_LIGHTER_COL1, FL_COL1 );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER );
    fl_set_object_lstyle( obj, FL_BOLD_STYLE );
    fl_set_object_callback( obj, duplex_button_callback, 0 );

    fdui->fdd_button = obj = fl_add_button( FL_PUSH_BUTTON, 319, 664, 41, 28, "FDD" );
    fl_set_object_boxtype( obj, FL_ROUNDED3D_UPBOX );
    fl_set_object_color( obj, FL_LIGHTER_COL1, FL_COL1 );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER );
    fl_set_object_lstyle( obj, FL_BOLD_STYLE );
    fl_set_object_callback( obj, duplex_button_callback, 1 );

    fl_end_form( );

    fdui->main_frm->fdui = fdui;

    return fdui;
}


/***************************************
 ***************************************/

FD_splash_frm *
create_form_splash_frm( void )
{
    FL_OBJECT *obj;
    FD_splash_frm *fdui = fl_malloc( sizeof *fdui );

    fdui->vdata = fdui->cdata = NULL;
    fdui->ldata = 0;

    fdui->splash_frm = fl_bgn_form( FL_NO_BOX, 390, 280 );

    obj = fl_add_box( FL_FLAT_BOX, 0, 0, 390, 280, "" );

    obj = fl_add_pixmap( FL_NORMAL_PIXMAP, 40, 20, 310, 100, "" );

    obj = fl_add_text( FL_NORMAL_TEXT, 70, 150, 80, 30, "text" );

    fl_end_form( );

    fdui->splash_frm->fdui = fdui;

    return fdui;
}


/***************************************
 ***************************************/

FD_config_dialog *
create_form_config_dialog( void )
{
    FL_OBJECT *obj;
    FD_config_dialog *fdui = fl_malloc( sizeof *fdui );

    fdui->vdata = fdui->cdata = NULL;
    fdui->ldata = 0;

    fdui->config_dialog = fl_bgn_form( FL_NO_BOX, 410, 120 );

    obj = fl_add_box( FL_UP_BOX, 0, 0, 410, 120, "" );

    fdui->cancel_btn = obj = fl_add_button( FL_NORMAL_BUTTON, 80, 75, 100, 30, "Cancel" );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER );
    fl_set_object_callback( obj, get_dir_callback, -1 );

    fdui->ok_btn = obj = fl_add_button( FL_RETURN_BUTTON, 225, 75, 100, 30, "OK" );
    fl_set_object_lalign( obj, FL_ALIGN_CENTER );
    fl_set_object_callback( obj, get_dir_callback, 0 );

    fdui->dir_input = obj = fl_add_input( FL_NORMAL_INPUT, 80, 30, 300, 30, "Directory" );
    fl_set_object_return( obj, FL_RETURN_END_CHANGED );

    fl_end_form( );

    fdui->config_dialog->fdui = fdui;

    return fdui;
}


/***************************************
 ***************************************/

FD_throughput_form *
create_form_throughput_form( void )
{
    FL_OBJECT *obj;
    FD_throughput_form *fdui = fl_malloc( sizeof *fdui );

    fdui->vdata = fdui->cdata = NULL;
    fdui->ldata = 0;

    fdui->throughput_form = fl_bgn_form( FL_NO_BOX, 429, 290 );

    obj = fl_add_box( FL_UP_BOX, 0, 0, 429, 290, "" );

    fdui->throughput_text = obj = fl_add_text( FL_NORMAL_TEXT, 0, 0, 428, 290, "text" );
    fl_set_object_lsize( obj, FL_HUGE_SIZE );

    fl_end_form( );

    fdui->throughput_form->fdui = fdui;

    return fdui;
}
