# trec_mix.py interpolates two set of trec outputs (suitable for
# trec_eval) into a single, combined result.  Usage:
#
#   trec_mix.py alpha file1 file2 num_results runid
#
# Results will be output with each result calculated as 
# alpha * score1 + (1 - alpha) * score2.  Alpha should be in range [0, 1]
#
# written nml 2005-08-08

import sys

if (len(sys.argv) != 6):
    print 'usage: trec_mix.py alpha file1 file2 num_results runid'
    sys.exit(0)

alpha = float(sys.argv[1])
one = open(sys.argv[2])
two = open(sys.argv[3])
runid = sys.argv[5]
numres = int(sys.argv[4])

l1 = one.readline()
w1 = l1.split()
l2 = two.readline()
w2 = l2.split()
results = {}
topic = ''

def rescmp(x, y):
    if (x[1] < y[1]):
        return 1
    elif (x[1] > y[1]):
        return -1
    else:
        return 0

prefix = ''
for i in range(len(w2)):
    if (w2[0][0:i].isalpha()):
        prefix = w2[0][0:i]

while (len(l1) > 0 or len(l2) > 0 or len(topic) > 0):
    if (len(l1) > 0 and w1[0] == topic):
        if (results.has_key(w1[2])):
            results[w1[2]] += alpha * float(w1[4])
        else:
            results[w1[2]] = alpha * float(w1[4])
        l1 = one.readline()
        w1 = l1.split()
    elif (len(l2) > 0 and w2[0] == topic):
        if (results.has_key(w2[2])):
            results[w2[2]] += (1 - alpha) * float(w2[4])
        else:
            results[w2[2]] = (1 - alpha) * float(w2[4])
        l2 = two.readline()
        w2 = l2.split()
    else:
        if (len(topic) > 0):
            # finished current topic, output it 

            # sort by score and print
            scores = map(lambda x: [x, results[x]], results.keys())
            scores.sort(rescmp)
            i = 1
            for s in scores:
                if (i <= numres):
                    print '%s\tQ0\t%s\t%u\t%f\t%s' \
                      % (topic, s[0], i, s[1], runid)
                i += 1

        # empty results and choose next topic
        results = {}
        if (len(l2) > 0):
            if (len(l1) > 0):
                # order by topic number, removing possible string prefix
                if (int(w1[0][len(prefix):]) < int(w2[0][len(prefix):])):
                    topic = w1[0]
                else:
                    topic = w2[0]
            else:
                topic = w2[0]
        elif (len(l1) > 0):
            topic = w1[0]
        else:
            topic = ''

