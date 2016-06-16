#!/usr/bin/awk -f

function bsort(arr, i,x) {
    for (i in arr) {
        for (x in arr) {
            if (arr[i] < arr[x]) {
                swap(arr,i,x)
            }
        }
    }
}


function swap(array,ind1,ind2) {
    sw = array[ind1]
    array[ind1] = array[ind2]
    array[ind2] = sw
}

function assert(bool) {
    if (!bool) {
        print "assert failed!"
    }
}

BEGIN {
	int_frag = -1;
	ext_frag = -1;
	updates = -1;
	results = 0;
}

END {
    # first, figure out what our variable is
	if (results == 0) {
	    print "no results to graph"
	} else if (results == 1) { 
	    print "only one result!"
	}

    accbuf_var = docbuf_var = dumpbuf_var = 0;
	for (x in accbuf) {
	    if (accbuf[x] != accbuf[0]) { accbuf_var = 1; }
	}
	for (x in dumpbuf) {
	    if (dumpbuf[x] != dumpbuf[0]) { dumpbuf_var = 1; }
	}
	for (x in docbuf) {
	    if (docbuf[x] != docbuf[0]) { docbuf_var = 1; }
	}
	for (x in results_updates) {
	    if (results_updates[x] != results_updates[first]) { updates_var = 1; }
	}
    if (accbuf_var + docbuf_var + dumpbuf_var > 1) {
	    print "too many variables (", accbuf_var, docbuf_var, dumpbuf_var, ")";
	} else if (accbuf_var + docbuf_var + dumpbuf_var == 0) {
	    print "no variables";
	}

    print "newgraph";
    print "";
    print "legend defaults left bottom x 5 y 1.1";
    print "";
    print "yaxis min 0 max 1"; 
    print "  label fontsize 8 : Time per document (seconds/document update)";
    print "";
    print "xaxis log min 1"; 
    if (accbuf_var) {
        # copy the array
        for (x in accbuf) {
            var[x] = accbuf[x];
        }
		var_num = 1;
        print "  label fontsize 8 : Compressed bytes of postings buffered";
    } else if (docbuf_var) {
        # copy the array
        for (x in docbuf) {
            var[x] = docbuf[x];
        }
		var_num = 3;
        print "  label fontsize 8 : Number of documents buffered";
	} else {
        # copy the array
        for (x in dumpbuf) {
            var[x] = dumpbuf[x];
        }
		var_num = 2;
        print "  label fontsize 8 : Compressed bytes of postings read during update";
	}
    print "";

	# sort the results by the variable
	bsort(var);
    for (x in results_time) {
	    num = split(x, key);
		assert(num == 3);
		tmptime[key[var_num]] = results_time[x];
        #print "assigning ", results_time[x], "to", key[var_num], " (x = ", x, ")";
	}
    for (x in results_frag) {
	    num = split(x, key);
		assert(num == 3);
		tmpfrag[key[var_num]] = results_frag[x];
	}
    for (x in results_updates) {
	    num = split(x, key);
		assert(num == 3);
		tmpupdates[key[var_num]] = results_updates[x];
	}

    print "newcurve marktype box linetype solid label : time"; 
    print "pts"; 
    # output the results in sorted order 
    for (x in var) {
        print var[x], tmptime[var[x]] 
    }
    print "";

    # draw the fragmentation graph over the top 
    print "copygraph";
    print "";
    print "legend x 50 y 110";
    print "";
    print "yaxis";
	print "  min 0 max 100";
    print "  hash_scale 1.0"
    print "  label fontsize 8 : Index Fragmentation (%)";
    print "  draw_at 10000";
    print "";
    print "xaxis nodraw"; 
    print "";

    print "newcurve marktype circle linetype dashed label : fragmentation"; 
    print "pts"; 
    # output the results in sorted order 
    for (x in var) {
        print var[x], tmpfrag[var[x]] * 100
    }
    print "";
}

/^querying\/building/ {
    accbuf[results] = substr($5, 1, length($5) -1)
	dumpbuf[results] = $8;
	docbuf[results] = $12;

	buffers = substr($5, 1, length($5) -1) " " $8 " " $12;
}

/^average\ update\ time/ {
    time = $4;
}

/updates\ performed/ {
    if (((updates != $4) && (updates != -1)) || ($4 == -1)) {
	    print "ERROR!(1)";
	}
    updates = $4;
}

/^internal\ fragmentation/ {
    if (int_frag != -1) {
        print "ERROR!(2)";
    }

    int_frag = $3;
}

/^external\ fragmentation/ {
    if ((ext_frag != -1) || (int_frag == -1)) {
        print "ERROR!(3)";
    }
	if (!buffers || (time == -1) || (updates == -1)) {
        print "ERROR!(4)", buffers, time, updates;
	}

    ext_frag = $3;
	frag = (int_frag * (1.0 - ext_frag)) + ext_frag;

    int_frag = -1;
    ext_frag = -1;

	results_time[buffers] = time;
	results_frag[buffers] = frag;
	results_updates[buffers] = updates;
	if (!results) {
	    first = buffers;
    }
    #print "recording", time, frag, updates, "for", buffer;
	results++;
}

