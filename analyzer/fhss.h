/*

  Copyright (C) 2024 Gonzalo José Carracedo Carballal

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation, version 3.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this program.  If not, see
  <http://www.gnu.org/licenses/>

*/

#ifndef _ANALYZER_FHSS_H
#define _ANALYZER_FHSS_H

#include <sigutils/sigutils.h>
#include <stddef.h>
#include <sys/time.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct suscan_fhss_tracker;

struct suscan_fhss_frame_detection {
  struct timeval timestamp;
  SUFREQ   center_freq;
  SUFLOAT  bandwidth;
  SUFLOAT  peak_power;
  SUFLOAT  snr;
};

struct suscan_fhss_hop_summary {
  SUFREQ   center_freq;
  SUFLOAT  dwell_time;
  SUFLOAT  avg_power;
  SUFLOAT  max_power;
  uint64_t hits;
};

struct suscan_fhss_channel_aggregate {
  SUFREQ   channel_freq;
  SUFLOAT  occupancy;
  SUFLOAT  avg_power;
  uint64_t hits;
};

typedef struct suscan_fhss_tracker suscan_fhss_tracker_t;

suscan_fhss_tracker_t *suscan_fhss_new(void);
void suscan_fhss_destroy(suscan_fhss_tracker_t *self);
void suscan_fhss_reset(suscan_fhss_tracker_t *self);

SUBOOL suscan_fhss_feed_psd(
    suscan_fhss_tracker_t *self,
    const struct timeval *timestamp,
    SUFREQ center_freq,
    SUFLOAT samp_rate,
    const SUFLOAT *psd,
    size_t psd_size);

SUBOOL suscan_fhss_finalize(suscan_fhss_tracker_t *self);

size_t suscan_fhss_get_frame_detections(
    const suscan_fhss_tracker_t *self,
    const struct suscan_fhss_frame_detection **detections);

size_t suscan_fhss_get_hop_summaries(
    const suscan_fhss_tracker_t *self,
    const struct suscan_fhss_hop_summary **summaries);

size_t suscan_fhss_get_channel_aggregates(
    const suscan_fhss_tracker_t *self,
    const struct suscan_fhss_channel_aggregate **aggregates);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _ANALYZER_FHSS_H */
