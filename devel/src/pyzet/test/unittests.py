#
# Unit tests for pyzet
#

#
# NOTE: do __NOT__ try to import zet or pyzet here; we have to set
# the relevant paths to point into the build tree first.  See
# __main__ below.
#
import unittest
import os
import sys
import distutils
import distutils.core
import shutil
import cPickle

ZET_ROOT=os.path.join(*([os.path.pardir] * 3))

MOBY_TXT=os.path.join(ZET_ROOT, "txt", "moby.txt")
ZET_EXE=os.path.join(ZET_ROOT, "zet")

LD_LIBRARY_PATH=os.path.join(ZET_ROOT, ".libs")

SETUP_PY=os.path.join(ZET_ROOT, "setup.py")

DATA_DIR="dat"
DATA_FILE="test.dat"

INDEX_DIR="indexes"
INDEX_NAME="moby"
INDEX_PATH=os.path.join(INDEX_DIR, INDEX_NAME)

IMPACT_INDEX_NAME="moby_impact"
IMPACT_INDEX_PATH=os.path.join(INDEX_DIR, IMPACT_INDEX_NAME)

TEST_QUERIES = ("white whale",)

def build_moby_index(moby_txt=MOBY_TXT, index_name=None, 
        index_dir=INDEX_DIR, zet_exe=ZET_EXE, impacts=False):
    """Build an index of Moby Dick."""
    if index_name is None:
        if impacts:
            index_name = IMPACT_INDEX_NAME
        else:
            index_name = INDEX_NAME
    if not os.access(zet_exe, os.X_OK):
        raise MobyTestError("Cannot run the zet program at '%s'" % zet_exe)
    if not os.access(moby_txt, os.R_OK):
        raise MobyTestError("Cannot access moby test collection at '%s'" \
                % (moby_txt))
    args = [ zet_exe, "-f", os.path.join(index_dir, index_name),
            "-i", moby_txt ]
    if impacts:
        args[1:1] = [ "--anh-impact" ]
    ret = os.spawnv(os.P_WAIT, zet_exe, args)
    if ret != 0:
        raise MobyTestError("Failed to build index of Moby Dick")

def rm_moby_index(index_name=INDEX_NAME, index_dir=INDEX_DIR):
    if os.path.isdir(index_dir):
        shutil.rmtree(index_dir)

def load_test_data(data_dir=DATA_DIR, data_file=DATA_FILE):
    data_path = os.path.join(data_dir, data_file)
    if not os.access(data_path, os.R_OK):
        raise MobyTestError("Cannot read test data file")
    fp = open(data_path, "r")
    dat = cPickle.load(fp)
    fp.close()
    return dat

def store_test_data(data, data_dir=DATA_DIR, data_file=DATA_FILE):
    if not os.path.isdir(data_dir):
        os.mkdir(data_dir)
    data_path = os.path.join(data_dir, data_file)
    fp = open(data_path, "w")
    dat = cPickle.dump(data, fp)
    fp.close()

def make_test_data(idx):
    td = TestData()
    for query in TEST_QUERIES:
        res = idx.search(query, 0, 100)
        tq = TestQuery(query, res)
        td.add_query(tq)
    vit = idx.vocab_iterator()
    for v in vit:
        td.add_term_info(v)
    return td

def update_test_data():
    idx = zet.Index(INDEX_PATH)
    store_test_data(make_test_data(idx))

class TestData:

    def __init__(self):
        self.queries = [] 
        self.term_infos = []

    def __eq__(self, other):
        return isinstance(other, TestData) and self.queries == other.queries \
                and self.term_infos == other.term_infos

    def __ne__(self, other):
        return not self.__eq__(other)

    def add_query(self, query):
        self.queries.append(query)

    def add_term_info(self, term_info):
        self.term_infos.append(term_info)

class TestQuery:

    def __init__(self, query, results):
        self.query = query
        self.results = results

    def __eq__(self, other):
        return isinstance(other, TestQuery) and self.query == other.query \
                and self.results == other.results

    def __ne__(self, other):
        return not self.__eq__(other)

def build_test_query(qry, zet_results):
    tq = TestQuery(qry, zet_results)

class MobyTestError(StandardError):
    pass

class MobyTestCase(unittest.TestCase):

    """Unit tests that use the Moby Dick text collection."""
    def setUp(self):
        self.idx = zet.Index(INDEX_PATH)
        self.impact_idx = zet.Index(IMPACT_INDEX_PATH)

    def testNoResults(self):
        results = self.idx.search("asdffdsa", 0, 20)
        assert len(results.results) == 0

    def testEmptyQuery(self):
        results = self.idx.search("", 0, 20)
        assert len(results.results) == 0


    def testSearchResultEquality(self):
        r1s = self.idx.search("indefatigable pickles")
        r2s = self.idx.search("indefatigable pickles")
        r1 = r1s.results[0]
        r2 = r2s.results[0]
        r1x = r1s.results[1]
        assert r1 != "fresh"
        assert "fresh" != r1
        assert r1 == r1
        assert r1 == r2
        assert r1x != r2

    def testSearchResultsEquality(self):
        r1s = self.idx.search("indefatigable pickles")
        r2s = self.idx.search("indefatigable pickles")
        r3s = self.idx.search("white whale")
        assert r1s == r2s
        assert r1s != r3s
        assert r1s != r1s.results[0]
        assert r1s.results[0] != r1s

    def testSearchResultsPickling(self):
        r1s = self.idx.search("indefatigable pickles")
        pcks = cPickle.dumps(r1s)
        r1sx = cPickle.loads(pcks)
        assert r1s == r1sx

    def testVocabEntryPickling(self):
        vit = self.idx.vocab_iterator()
        te = vit.next()
        tep = cPickle.dumps(te)
        teu = cPickle.loads(tep)
        assert teu == te

    def testTestData(self):
        td_now = make_test_data(self.idx)
        td_store = load_test_data()
        assert td_now == td_store

    def testPostings(self):
        postings = self.idx.term_postings("indifferent")
        count = 0
        assert postings is not None
        for p in postings:
            count += 1
        vocab = self.idx.term_info("indifferent")
        assert count == vocab[0]

    def testTermInfo(self):
        tinfo = self.idx.term_info("whale")
        assert tinfo[0] == 1
        assert tinfo[1] == 1
        assert tinfo[2] == 466
        assert tinfo[3] == 4

    def testTotalResults(self):
        res = self.idx.search("whale")
        assert res.total_results == 791

    def testVocabIterator(self):
        vit = self.idx.vocab_iterator()

class MLParserTestCase(unittest.TestCase):

    """Unit tests that test the MLParser."""
    def testInvalidConstructor(self):
        try:
            parser = zet.MLParser()
        except TypeError:
            pass

    def testSimple(self):
        text = "<html><head><title>Hi</title></head><body>Hello there. </body></html>"
        parser = zet.MLParser(text)
        assert parser.parse() == (zet.MLPARSE_TAG, "html", False, False)
        assert parser.parse() == (zet.MLPARSE_TAG, "head", False, False)
        assert parser.parse() == (zet.MLPARSE_TAG, "title", False, False)
        assert parser.parse() == (zet.MLPARSE_WORD, "hi", False, False)
        assert parser.parse() == (zet.MLPARSE_TAG, "/title", False, False)
        assert parser.parse() == (zet.MLPARSE_TAG, "/head", False, False)
        assert parser.parse() == (zet.MLPARSE_TAG, "body", False, False)
        assert parser.parse() == (zet.MLPARSE_WORD, "hello", False, False)
        # NOTE: mlparse currently doesn't recognise end of sentence if
        # the full stop is not followed by a space
        assert parser.parse() == (zet.MLPARSE_WORD, "there", True, False)
        assert parser.parse() == (zet.MLPARSE_TAG, "/body", False, False)
        assert parser.parse() == (zet.MLPARSE_TAG, "/html", False, False)
        assert parser.parse() is None

    def testHangingTag(self):
        text = "<html"
        parser = zet.MLParser(text)
        assert parser.parse() == (zet.MLPARSE_WORD, "html", False, False)

if __name__ == "__main__":
    # Make sure that our cwd is the directory that these
    # scripts sit in
    TEST_DIR = os.path.abspath(os.path.dirname(sys.argv[0]))
    os.chdir(TEST_DIR)

    # Make sure that we're using the libzet.so inside the
    # build tree, not an installed one.  If the incorrect
    # LD_LIBRARY_PATH is set, then we have to correct it
    # and re-exec this program.
    ld_lib_path = os.environ["LD_LIBRARY_PATH"]
    if ld_lib_path != LD_LIBRARY_PATH:
        if len(sys.argv) < 2 or sys.argv[1] != "reexeced":
            os.environ["LD_LIBRARY_PATH"] = LD_LIBRARY_PATH
            os.execlp("python", "python", os.path.basename(sys.argv[0]), "reexeced", *sys.argv[1:])
        else:
            raise MobyTestError("Failed to set LD_LIBRARY_PATH")

    # We have to preserve the args here, because they get screwed
    # up by distutils.core.run_setup
    args = sys.argv[1:]
    if len(args) > 0 and args[0] == "reexeced":
        args = args[1:]

    # Place the build-directory zet module in our path, not
    # the installed one.
    #
    # We intialise the distutils objects in the same way
    # as is done for the build, and extract the build directory
    dist = distutils.core.run_setup(SETUP_PY, [], stop_after="config")
    bld_obj = dist.get_command_obj("build")
    bld_obj.ensure_finalized()
    sys.path = [ os.path.join(ZET_ROOT, bld_obj.build_platlib) ]
    import zet

    # We build the moby index once here, rather than in the setUp()
    # method of each individual unit test
    if os.path.isdir(INDEX_DIR):
        shutil.rmtree(INDEX_DIR)
    os.mkdir(INDEX_DIR)
    build_moby_index()
    build_moby_index(impacts=True)
    if len(args) > 0 and args[0] == "update":
        update_test_data()
    else:
        unittest.main()
