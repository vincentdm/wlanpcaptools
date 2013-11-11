/*
 * ieee80211.h
 *
 *  Created on: 9-nov.-2013
 *      Author: vincent
 */

#ifndef IEEE80211_H_
#define IEEE80211_H_

struct ieee80211_management_header {
	u_int16_t frame_control;
	u_int16_t duration;
	u_char addr1[6];
	u_char addr2[6];
	u_char addr3[6];
	u_int16_t seq_ctrl;
} __attribute__((__packed__));

struct ieee80211_beacon_header {
	u_int64_t timestamp;
	u_int16_t beacon_interval;
	u_int16_t capabilities;
} __attribute__((__packed__));

#endif /* IEEE80211_H_ */
