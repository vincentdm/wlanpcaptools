/*
* Copyright 2013 Vincent De Maertelaere
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*     http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
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
