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

#include "fhss.h"

#include <stdlib.h>

struct suscan_fhss_tracker {
  struct suscan_fhss_frame_detection *detections;
  struct suscan_fhss_hop_summary *summaries;
  struct suscan_fhss_channel_aggregate *aggregates;
  size_t detections_count;
  size_t summaries_count;
  size_t aggregates_count;
};

suscan_fhss_tracker_t *
suscan_fhss_new(void)
{
  return calloc(1, sizeof(suscan_fhss_tracker_t));
}

void
suscan_fhss_destroy(suscan_fhss_tracker_t *self)
{
  if (self == NULL)
    return;

  free(self->detections);
  free(self->summaries);
  free(self->aggregates);
  free(self);
}

void
suscan_fhss_reset(suscan_fhss_tracker_t *self)
{
  if (self == NULL)
    return;

  free(self->detections);
  free(self->summaries);
  free(self->aggregates);

  self->detections = NULL;
  self->summaries = NULL;
  self->aggregates = NULL;
  self->detections_count = 0;
  self->summaries_count = 0;
  self->aggregates_count = 0;
}

SUBOOL
suscan_fhss_feed_psd(
    suscan_fhss_tracker_t *self,
    const struct timeval *timestamp,
    SUFREQ center_freq,
    SUFLOAT samp_rate,
    const SUFLOAT *psd,
    size_t psd_size)
{
  (void) self;
  (void) timestamp;
  (void) center_freq;
  (void) samp_rate;
  (void) psd;
  (void) psd_size;

  return SU_TRUE;
}

SUBOOL
suscan_fhss_finalize(suscan_fhss_tracker_t *self)
{
  (void) self;
  return SU_TRUE;
}

size_t
suscan_fhss_get_frame_detections(
    const suscan_fhss_tracker_t *self,
    const struct suscan_fhss_frame_detection **detections)
{
  if (detections != NULL) {
    *detections = self != NULL ? self->detections : NULL;
  }

  return self != NULL ? self->detections_count : 0;
}

size_t
suscan_fhss_get_hop_summaries(
    const suscan_fhss_tracker_t *self,
    const struct suscan_fhss_hop_summary **summaries)
{
  if (summaries != NULL) {
    *summaries = self != NULL ? self->summaries : NULL;
  }

  return self != NULL ? self->summaries_count : 0;
}

size_t
suscan_fhss_get_channel_aggregates(
    const suscan_fhss_tracker_t *self,
    const struct suscan_fhss_channel_aggregate **aggregates)
{
  if (aggregates != NULL) {
    *aggregates = self != NULL ? self->aggregates : NULL;
  }

  return self != NULL ? self->aggregates_count : 0;
}
