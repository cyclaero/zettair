#!/usr/bin/awk -f

BEGIN {
    print "newgraph";
    print;
    print "yaxis min 0"; 
    print "  label fontsize 8 : Time (seconds)";
    print;
    print "xaxis min 0"; 
    print "  label fontsize 8 : Size (MBytes)";
    print;
    version = "";
    run = 1;

	# hardcode sizes of .GOV collection so we don't need to have it
	# hanging around
	sizes["GOV-1.html"] = 2105982626 / (1024 * 1024);
	sizes["GOV-2.html"] = 2108312619 / (1024 * 1024);
	sizes["GOV-3.html"] = 2108327778 / (1024 * 1024);
	sizes["GOV-4.html"] = 2109366413 / (1024 * 1024);
	sizes["GOV-5.html"] = 2109664810 / (1024 * 1024);
	sizes["GOV-6.html"] = 2110057684 / (1024 * 1024);
	sizes["GOV-7.html"] = 2109622336 / (1024 * 1024);
	sizes["GOV-8.html"] = 2108314272 / (1024 * 1024);
	sizes["GOV-9.html"] = 2108976486 / (1024 * 1024);
	sizes["GOV-10.html"] = 476405526 / (1024 * 1024);
}

END {
    sum = 0;
    num = 0;

    # sort by index value
    j = 1
    for (i in build) {
        ind[j] = i;   # index value becomes element value
        j++;
    }

    for (i = 1; i < j; i++) {
        split(ind[i], seperate, SUBSEP);
        # get average build time
        num = split(build[ind[i]], times, " ");
        sum = 0;
        for (k = 1; k <= num; k++) {
            sum += times[k];
        }
        buildtime = sum / num;

        # get average accumulation time
        accnum = split(acc[ind[i]], times, " ");
        sum = 0;
        for (k = 1; k <= accnum; k++) {
            sum += times[k];
        }
        # note averaging by number of runs, not by number of accumulations 
        acctime = sum / num;

        # get average dump time
        dumpnum = split(dump[ind[i]], times, " ");
        sum = 0;
        for (k = 1; k <= dumpnum; k++) {
            sum += times[k];
        }
        # note averaging by number of runs, not by number of dumps 
        dumptime = sum / num;

        # get average merge time
        mergenum = split(merge[ind[i]], times, " ");
        sum = 0;
        for (k = 1; k <= mergenum; k++) {
            sum += times[k];
        }
        # note averaging by number of runs, not by number of merges 
        mergetime = sum / num;

        bdata[seperate[1]] = bdata[seperate[1]] " " buildtime;
        adata[seperate[1]] = adata[seperate[1]] " " acctime;
        ddata[seperate[1]] = ddata[seperate[1]] " " dumptime;
        mdata[seperate[1]] = mdata[seperate[1]] " " mergetime;
        datasize[seperate[1]] = datasize[seperate[1]] " " seperate[2];
    }

    colours[1] = "1.0 0.0 0.0"; 
    colours[2] = "0.5 0.0 0.0"; 
    colours[3] = "0.0 1.0 0.0"; 
    colours[4] = "0.0 0.5 0.0"; 
    colours[5] = "0.0 0.0 1.0"; 
    colours[6] = "0.0 0.0 0.5"; 
    colours[7] = "1.0 1.0 0.0";  
    colours[8] = "0.5 0.5 0.0";  
    colours[9] = "1.0 0.0 1.0"; 
    colours[10] = "0.5 0.0 0.5"; 
    colours[11] = "0.0 1.0 1.0"; 
    colours[12] = "0.0 0.5 0.5"; 

    j = 1;
    for (x in datasize) {
        num = split(datasize[x], dsizes, " ");

        # print out overall curve
        print "newcurve color", colours[j], 
          "marktype circle linetype solid label :", x;
        print "pts"
        split(bdata[x], btimes, " ");
        for (i = 1; i <= num; i++) {
            print dsizes[i], btimes[i];
        }
        print "\n"; 

        # print out accumulation curve
        print "newcurve color", colours[j + 1],
          "marktype diamond linetype longdash label :", x, "accumulation";
        print "pts"
        split(adata[x], atimes, " ");
        for (i = 1; i <= num; i++) {
            print dsizes[i], atimes[i];
        }
        print "\n"; 

        # print out dump curve
        print "newcurve color", colours[j + 1],
          "marktype box linetype dashed label :", x, "dump";
        print "pts"
        split(ddata[x], dtimes, " ");
        for (i = 1; i <= num; i++) {
            print dsizes[i], dtimes[i];
        }
        print "\n"; 

        # print out merge curve 
        print "newcurve color", colours[j + 1],
          "marktype cross linetype dotdash label :", x, "merge";
        print "pts"
        split(mdata[x], mtimes, " ");
        for (i = 1; i <= num; i++) {
            print dsizes[i], mtimes[i];
        }
        print "\n"; 

        # print out other curve
        print "newcurve color", colours[j + 1],
          "marktype triangle linetype dotted label :", x, "other";
        print "pts"
        for (i = 1; i <= num; i++) {
            print dsizes[i], btimes[i] - mtimes[i] - atimes[i] - dtimes[i];
        }
        print "\n"; 
        j++;
        j++;
    }
}

/^sources/ {
	vocabsize = 0;

    for (i = 4; i <= NF; i++) {
        if (sizes[$i] == "") {
            # write the file size to tempfile
            tempfile = ("mydata." PROCINFO["pid"])
            system("wc -c " $2 " > " tempfile);
            close(tempfile)

            # read it back in and remove tempfile
            getline newdata < tempfile
            split(newdata, tmp, " ");
            sizes[$i] = (tmp[1] / (1024 * 1024));
            close(tempfile)
            system("rm " tempfile)
        }

		vocabsize += sizes[$i];
    }
}

/^version/ {
    version = $2;
}

/^build\ time\:/ {
    build[version, vocabsize] = build[version, vocabsize] " " substr($4, 2);
    run++;
}

/^accumulation\ time\:/ {
    acc[version, vocabsize] = acc[version, vocabsize] " " substr($4, 2);
}

/^dump\ time\:/ {
    dump[version, vocabsize] = dump[version, vocabsize] " " substr($4, 2);
}

/^merge\ time\:/ {
    merge[version, vocabsize] = merge[version, vocabsize] " " substr($4, 2);
}

