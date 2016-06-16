/* metric.h contains signatures for all of the metrics currently known
 * in the system.  It contains functions of different prefixes, but it
 * beats having a different header file for each metric, since they
 * consist of a single function
 *
 * written nml 2005-05-31
 *
 */

#ifndef METRIC_H
#define METRIC_H

struct search_metric;

/* okapi metric */
const struct search_metric *okapi(struct search_metric *sm, int offsets);

/* dirichlet metric */
const struct search_metric *dirichlet(struct search_metric *sm, int offsets);

/* pivoted cosine metric */
const struct search_metric *pcosine(struct search_metric *sm, int offsets);

/* (incredibly simple) cosine metric */
const struct search_metric *cosine(struct search_metric *sm, int offsets);

/* Dave Hawking's AF1 metric */
const struct search_metric *hawkapi(struct search_metric *sm, int offsets);

#endif

