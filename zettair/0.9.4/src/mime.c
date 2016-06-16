/* mime.c implements the interface declared by mime.h
 *
 * DO NOT modify this file, as it is automatically generated 
 * and changes will be lost upon subsequent regeneration.
 *
 * It is automatically generated from media-type files describing 
 * valid MIME types by scripts/mime.py.  The definitive list can be found at 
 * http://www.isi.edu/in-notes/iana/assignments/media-types/media-types, 
 * although scripts/mime.py will accept multiple files (in the same format), 
 * allowing you to define your own MIME types as convenient.
 *
 * This file was generated on Mon, 02 Mar 2009 06:33:29 +0000 
 * by scripts/mime.py
 *
 */
               
#include "firstinclude.h"

#include "mime.h"

#include "str.h"

#include <ctype.h>
          
struct mime_lookup {
    const char *name;
    enum mime_top_types toptype;
};
          
static const struct mime_lookup lookup[] = {
    {"text/html", MIME_TOP_TYPE_TEXT},
    {"text/plain", MIME_TOP_TYPE_TEXT},
    {"application/x-inex", MIME_TOP_TYPE_APPLICATION},
    {"application/x-trec", MIME_TOP_TYPE_APPLICATION},
    {"text/css", MIME_TOP_TYPE_TEXT},
    {"text/rtf", MIME_TOP_TYPE_TEXT},
    {"image/gif", MIME_TOP_TYPE_IMAGE},
    {"image/png", MIME_TOP_TYPE_IMAGE},
    {"audio/mpeg", MIME_TOP_TYPE_AUDIO},
    {"image/jpeg", MIME_TOP_TYPE_IMAGE},
    {"image/tiff", MIME_TOP_TYPE_IMAGE},
    {"video/mpeg", MIME_TOP_TYPE_VIDEO},
    {"audio/basic", MIME_TOP_TYPE_AUDIO},
    {"message/http", MIME_TOP_TYPE_MESSAGE},
    {"message/rfc822", MIME_TOP_TYPE_MESSAGE},
    {"message/s-http", MIME_TOP_TYPE_MESSAGE},
    {"application/pdf", MIME_TOP_TYPE_APPLICATION},
    {"application/zip", MIME_TOP_TYPE_APPLICATION},
    {"message/partial", MIME_TOP_TYPE_MESSAGE},
    {"multipart/mixed", MIME_TOP_TYPE_MULTIPART},
    {"video/quicktime", MIME_TOP_TYPE_VIDEO},
    {"multipart/digest", MIME_TOP_TYPE_MULTIPART},
    {"multipart/signed", MIME_TOP_TYPE_MULTIPART},
    {"application/msword", MIME_TOP_TYPE_APPLICATION},
    {"multipart/parallel", MIME_TOP_TYPE_MULTIPART},
    {"multipart/encrypted", MIME_TOP_TYPE_MULTIPART},
    {"multipart/byteranges", MIME_TOP_TYPE_MULTIPART},
    {"message/external-body", MIME_TOP_TYPE_MESSAGE},
    {"multipart/alternative", MIME_TOP_TYPE_MULTIPART},
    {"application/postscript", MIME_TOP_TYPE_APPLICATION},
    {"application/mathematica", MIME_TOP_TYPE_APPLICATION},
    {"application/octet-stream", MIME_TOP_TYPE_APPLICATION},
    {"text/xml", MIME_TOP_TYPE_TEXT},
    {"application/x-tar", MIME_TOP_TYPE_APPLICATION},
    {"image/cgm", MIME_TOP_TYPE_IMAGE},
    {"image/ief", MIME_TOP_TYPE_IMAGE},
    {"text/t140", MIME_TOP_TYPE_TEXT},
    {"audio/tone", MIME_TOP_TYPE_AUDIO},
    {"model/iges", MIME_TOP_TYPE_MODEL},
    {"model/mesh", MIME_TOP_TYPE_MODEL},
    {"model/vrml", MIME_TOP_TYPE_MODEL},
    {"image/g3fax", MIME_TOP_TYPE_IMAGE},
    {"image/naplps", MIME_TOP_TYPE_IMAGE},
    {"message/news", MIME_TOP_TYPE_MESSAGE},
    {"text/vnd.abc", MIME_TOP_TYPE_TEXT},
    {"text/vnd.fly", MIME_TOP_TYPE_TEXT},
    {"audio/prs.sid", MIME_TOP_TYPE_AUDIO},
    {"image/prs.pti", MIME_TOP_TYPE_IMAGE},
    {"image/vnd.dwg", MIME_TOP_TYPE_IMAGE},
    {"image/vnd.dxf", MIME_TOP_TYPE_IMAGE},
    {"image/vnd.fpx", MIME_TOP_TYPE_IMAGE},
    {"image/vnd.fst", MIME_TOP_TYPE_IMAGE},
    {"image/vnd.mix", MIME_TOP_TYPE_IMAGE},
    {"image/vnd.svf", MIME_TOP_TYPE_IMAGE},
    {"model/vnd.dwf", MIME_TOP_TYPE_MODEL},
    {"model/vnd.gdl", MIME_TOP_TYPE_MODEL},
    {"model/vnd.gtw", MIME_TOP_TYPE_MODEL},
    {"model/vnd.mts", MIME_TOP_TYPE_MODEL},
    {"model/vnd.vtu", MIME_TOP_TYPE_MODEL},
    {"text/calendar", MIME_TOP_TYPE_TEXT},
    {"text/enriched", MIME_TOP_TYPE_TEXT},
    {"text/richtext", MIME_TOP_TYPE_TEXT},
    {"text/uri-list", MIME_TOP_TYPE_TEXT},
    {"text/vnd.curl", MIME_TOP_TYPE_TEXT},
    {"video/pointer", MIME_TOP_TYPE_VIDEO},
    {"video/vnd.fvt", MIME_TOP_TYPE_VIDEO},
    {"audio/32kadpcm", MIME_TOP_TYPE_AUDIO},
    {"image/prs.btif", MIME_TOP_TYPE_IMAGE},
    {"image/vnd.xiff", MIME_TOP_TYPE_IMAGE},
    {"text/directory", MIME_TOP_TYPE_TEXT},
    {"text/parityfec", MIME_TOP_TYPE_TEXT},
    {"video/vnd.vivo", MIME_TOP_TYPE_VIDEO},
    {"application/ipp", MIME_TOP_TYPE_APPLICATION},
    {"application/oda", MIME_TOP_TYPE_APPLICATION},
    {"application/rtf", MIME_TOP_TYPE_APPLICATION},
    {"application/sdp", MIME_TOP_TYPE_APPLICATION},
    {"application/xml", MIME_TOP_TYPE_APPLICATION},
    {"audio/parityfec", MIME_TOP_TYPE_AUDIO},
    {"audio/vnd.qcelp", MIME_TOP_TYPE_AUDIO},
    {"text/vnd.wap.si", MIME_TOP_TYPE_TEXT},
    {"text/vnd.wap.sl", MIME_TOP_TYPE_TEXT},
    {"video/parityfec", MIME_TOP_TYPE_VIDEO},
    {"application/dvcs", MIME_TOP_TYPE_APPLICATION},
    {"application/http", MIME_TOP_TYPE_APPLICATION},
    {"application/iges", MIME_TOP_TYPE_APPLICATION},
    {"application/iotp", MIME_TOP_TYPE_APPLICATION},
    {"application/isup", MIME_TOP_TYPE_APPLICATION},
    {"application/marc", MIME_TOP_TYPE_APPLICATION},
    {"application/qsig", MIME_TOP_TYPE_APPLICATION},
    {"application/sgml", MIME_TOP_TYPE_APPLICATION},
    {"application/wita", MIME_TOP_TYPE_APPLICATION},
    {"audio/mpa-robust", MIME_TOP_TYPE_AUDIO},
    {"model/vnd.gs-gdl", MIME_TOP_TYPE_MODEL},
    {"multipart/report", MIME_TOP_TYPE_MULTIPART},
    {"text/vnd.latex-z", MIME_TOP_TYPE_TEXT},
    {"text/vnd.wap.wml", MIME_TOP_TYPE_TEXT},
    {"application/eshop", MIME_TOP_TYPE_APPLICATION},
    {"application/index", MIME_TOP_TYPE_APPLICATION},
    {"application/sieve", MIME_TOP_TYPE_APPLICATION},
    {"application/slate", MIME_TOP_TYPE_APPLICATION},
    {"application/vemmi", MIME_TOP_TYPE_APPLICATION},
    {"image/vnd.net-fpx", MIME_TOP_TYPE_IMAGE},
    {"multipart/related", MIME_TOP_TYPE_MULTIPART},
    {"video/vnd.mpegurl", MIME_TOP_TYPE_VIDEO},
    {"application/dec-dx", MIME_TOP_TYPE_APPLICATION},
    {"application/pkcs10", MIME_TOP_TYPE_APPLICATION},
    {"application/riscos", MIME_TOP_TYPE_APPLICATION},
    {"application/x-gzip", MIME_TOP_TYPE_APPLICATION},
    {"audio/vnd.cns.anp1", MIME_TOP_TYPE_AUDIO},
    {"audio/vnd.cns.inf1", MIME_TOP_TYPE_AUDIO},
    {"audio/vnd.vmx.cvsd", MIME_TOP_TYPE_AUDIO},
    {"image/vnd.cns.inf2", MIME_TOP_TYPE_IMAGE},
    {"image/vnd.wap.wbmp", MIME_TOP_TYPE_IMAGE},
    {"text/prs.lines.tag", MIME_TOP_TYPE_TEXT},
    {"text/vnd.IPTC.NITF", MIME_TOP_TYPE_TEXT},
    {"text/vnd.in3d.3dml", MIME_TOP_TYPE_TEXT},
    {"text/vnd.in3d.spot", MIME_TOP_TYPE_TEXT},
    {"application/dca-rft", MIME_TOP_TYPE_APPLICATION},
    {"application/pkixcmp", MIME_TOP_TYPE_APPLICATION},
    {"application/prs.cww", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.bmi", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.dna", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.dxr", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.fdf", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.mcd", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.mif", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.svd", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.vcx", MIME_TOP_TYPE_APPLICATION},
    {"application/x-bzip2", MIME_TOP_TYPE_APPLICATION},
    {"application/x400-bp", MIME_TOP_TYPE_APPLICATION},
    {"application/xml-dtd", MIME_TOP_TYPE_APPLICATION},
    {"audio/vnd.cisco.nse", MIME_TOP_TYPE_AUDIO},
    {"audio/vnd.octel.sbc", MIME_TOP_TYPE_AUDIO},
    {"multipart/form-data", MIME_TOP_TYPE_MULTIPART},
    {"text/rfc822-headers", MIME_TOP_TYPE_TEXT},
    {"application/beep+xml", MIME_TOP_TYPE_APPLICATION},
    {"application/pgp-keys", MIME_TOP_TYPE_APPLICATION},
    {"application/pkix-crl", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.koan", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.mseq", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.palm", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.ufdl", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.xara", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.xfdl", MIME_TOP_TYPE_APPLICATION},
    {"audio/vnd.everad.plj", MIME_TOP_TYPE_AUDIO},
    {"audio/vnd.nortel.vbk", MIME_TOP_TYPE_AUDIO},
    {"multipart/header-set", MIME_TOP_TYPE_MULTIPART},
    {"text/vnd.IPTC.NewsML", MIME_TOP_TYPE_TEXT},
    {"application/applefile", MIME_TOP_TYPE_APPLICATION},
    {"application/cals-1840", MIME_TOP_TYPE_APPLICATION},
    {"application/cybercash", MIME_TOP_TYPE_APPLICATION},
    {"application/index.cmd", MIME_TOP_TYPE_APPLICATION},
    {"application/index.obj", MIME_TOP_TYPE_APPLICATION},
    {"application/index.vnd", MIME_TOP_TYPE_APPLICATION},
    {"application/parityfec", MIME_TOP_TYPE_APPLICATION},
    {"application/pkix-cert", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.ffsns", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.msign", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.rapid", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.s3sms", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.visio", MIME_TOP_TYPE_APPLICATION},
    {"audio/telephone-event", MIME_TOP_TYPE_AUDIO},
    {"multipart/appledouble", MIME_TOP_TYPE_MULTIPART},
    {"text/vnd.fmi.flexstor", MIME_TOP_TYPE_TEXT},
    {"application/atomicmail", MIME_TOP_TYPE_APPLICATION},
    {"application/batch-SMTP", MIME_TOP_TYPE_APPLICATION},
    {"application/font-tdpfr", MIME_TOP_TYPE_APPLICATION},
    {"application/macwriteii", MIME_TOP_TYPE_APPLICATION},
    {"application/pkcs7-mime", MIME_TOP_TYPE_APPLICATION},
    {"application/prs.nprend", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.cybank", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.grafeq", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.hp-PCL", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.hp-hps", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.is-xpr", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.ms-asf", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.ms-lrm", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.netfpx", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.wt.stf", MIME_TOP_TYPE_APPLICATION},
    {"audio/vnd.lucent.voice", MIME_TOP_TYPE_AUDIO},
    {"image/vnd.fastbidsheet", MIME_TOP_TYPE_IMAGE},
    {"text/vnd.wap.wmlscript", MIME_TOP_TYPE_TEXT},
    {"application/hyperstudio", MIME_TOP_TYPE_APPLICATION},
    {"application/set-payment", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.dpgraph", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.enliven", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.hp-HPGL", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.hp-hpid", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.ms-tnef", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.seemail", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.sss-cod", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.sss-dtf", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.sss-ntf", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.trueapp", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.truedoc", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.wap.sic", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.wap.slc", MIME_TOP_TYPE_APPLICATION},
    {"audio/vnd.digital-winds", MIME_TOP_TYPE_AUDIO},
    {"message/delivery-status", MIME_TOP_TYPE_MESSAGE},
    {"model/vnd.flatland.3dml", MIME_TOP_TYPE_MODEL},
    {"multipart/voice-message", MIME_TOP_TYPE_MULTIPART},
    {"text/vnd.DMClientScript", MIME_TOP_TYPE_TEXT},
    {"application/andrew-inset", MIME_TOP_TYPE_APPLICATION},
    {"application/commonground", MIME_TOP_TYPE_APPLICATION},
    {"application/mac-binhex40", MIME_TOP_TYPE_APPLICATION},
    {"application/ocsp-request", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.acucobol", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.claymore", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.cups-raw", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.hp-PCLXL", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.httphone", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.intu.qbo", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.intu.qfx", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.ms-excel", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.ms-works", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.musician", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.wap.wmlc", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.webturbo", MIME_TOP_TYPE_APPLICATION},
    {"text/vnd.motorola.reflex", MIME_TOP_TYPE_TEXT},
    {"text/vnd.ms-mediapackage", MIME_TOP_TYPE_TEXT},
    {"video/vnd.motorola.video", MIME_TOP_TYPE_VIDEO},
    {"application/activemessage", MIME_TOP_TYPE_APPLICATION},
    {"application/ocsp-response", MIME_TOP_TYPE_APPLICATION},
    {"application/pgp-encrypted", MIME_TOP_TYPE_APPLICATION},
    {"application/pgp-signature", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.ctc-posml", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.epson.esf", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.epson.msf", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.epson.ssf", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.pg.format", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.pg.osasli", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.pvi.ptid1", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.wap.wbxml", MIME_TOP_TYPE_APPLICATION},
    {"application/whoispp-query", MIME_TOP_TYPE_APPLICATION},
    {"audio/vnd.nuera.ecelp4800", MIME_TOP_TYPE_AUDIO},
    {"audio/vnd.nuera.ecelp7470", MIME_TOP_TYPE_AUDIO},
    {"audio/vnd.nuera.ecelp9600", MIME_TOP_TYPE_AUDIO},
    {"text/tab-separated-values", MIME_TOP_TYPE_TEXT},
    {"video/vnd.motorola.videop", MIME_TOP_TYPE_VIDEO},
    {"application/index.response", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.aether.imp", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.audiograph", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.canon-cpdl", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.canon-lips", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.epson.salt", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.framemaker", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.fut-misnet", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.ibm.modcap", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.ms-project", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.music-niff", MIME_TOP_TYPE_APPLICATION},
    {"application/wordperfect5.1", MIME_TOP_TYPE_APPLICATION},
    {"application/news-message-id", MIME_TOP_TYPE_APPLICATION},
    {"application/pkcs7-signature", MIME_TOP_TYPE_APPLICATION},
    {"application/remote-printing", MIME_TOP_TYPE_APPLICATION},
    {"application/timestamp-query", MIME_TOP_TYPE_APPLICATION},
    {"application/timestamp-reply", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.commonspace", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.comsocaller", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.cups-raster", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.eudora.data", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.ibm.MiniPay", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.lotus-1-2-3", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.lotus-notes", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.ms-artgalry", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.tve-trigger", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.vectorworks", MIME_TOP_TYPE_APPLICATION},
    {"audio/vnd.rhetorex.32kadpcm", MIME_TOP_TYPE_AUDIO},
    {"application/set-registration", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.contact.cmsg", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.ecdis-update", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.ecowin.chart", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.groove-vcard", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.noblenet-web", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.novadigm.EDM", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.novadigm.EDX", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.novadigm.EXT", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.triscape.mxs", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.uplanet.list", MIME_TOP_TYPE_APPLICATION},
    {"application/whoispp-response", MIME_TOP_TYPE_APPLICATION},
    {"application/news-transmission",
      MIME_TOP_TYPE_APPLICATION},
    {"application/sgml-open-catalog",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.ecowin.series",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.fsc.weblaunch",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.fujitsu.oasys",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.fujixerox.ddd",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.lotus-wordpro",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.ms-powerpoint",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.osa.netdeploy",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.powerbuilder6",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.powerbuilder7",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.street-stream",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.swiftview-ics",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.uplanet.alert",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.fujitsu.oasys2",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.fujitsu.oasys3",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.groove-account",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.lotus-approach",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.powerbuilder75",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.uplanet.signal",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.wap.wmlscriptc",
      MIME_TOP_TYPE_APPLICATION},
    {"image/vnd.fujixerox.edmics-mmr",
      MIME_TOP_TYPE_IMAGE},
    {"image/vnd.fujixerox.edmics-rlc",
      MIME_TOP_TYPE_IMAGE},
    {"application/vnd.businessobjects",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.cups-postscript",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.fujitsu.oasysgp",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.groove-injector",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.ibm.afplinedata",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.intertrust.nncp",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.lotus-freelance",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.lotus-organizer",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.lotus-screencam",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.mozilla.xul+xml",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.noblenet-sealer",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.powerbuilder6-s",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.powerbuilder7-s",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.uplanet.cacheop",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.uplanet.channel",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.uplanet.listcmd",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.3M.Post-it-Notes",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.epson.quickanime",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.fujitsu.oasysprs",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.hzn-3d-crossword",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.intercon.formnet",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.powerbuilder75-s",
      MIME_TOP_TYPE_APPLICATION},
    {"message/disposition-notification",
      MIME_TOP_TYPE_MESSAGE},
    {"application/vnd.accpac.simply.aso",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.accpac.simply.imp",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.ecowin.fileupdate",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.hhe.lesson-player",
      MIME_TOP_TYPE_APPLICATION},
    {"application/set-payment-initiation",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.ecowin.filerequest",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.ericsson.quickcall",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.informix-visionary",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.intertrust.digibox",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.mediastation.cdkey",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.meridian-slingshot",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.motorola.flexsuite",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.noblenet-directory",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.previewsystems.box",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.uplanet.list-wbxml",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.ecowin.seriesupdate",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.fujixerox.docuworks",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.groove-tool-message",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.pwg-xhtml-print+xml",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.uplanet.alert-wbxml",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.wrq-hp3000-labelled",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.ecowin.seriesrequest",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.groove-tool-template",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.minisoft-hp3000-save",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.vividence.scriptfile",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.japannet-registration",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.japannet-verification",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.publishare-delta-tree",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.uplanet.bearer-choice",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.uplanet.cacheop-wbxml",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.uplanet.channel-wbxml",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.uplanet.listcmd-wbxml",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.vidsoft.vidconference",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.motorola.flexsuite.fis",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.motorola.flexsuite.kmr",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.motorola.flexsuite.ttc",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.motorola.flexsuite.wem",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.shana.informed.package",
      MIME_TOP_TYPE_APPLICATION},
    {"application/xml-external-parsed-entity",
      MIME_TOP_TYPE_APPLICATION},
    {"video/vnd.nokia.interleaved-multimedia",
      MIME_TOP_TYPE_VIDEO},
    {"application/prs.alvestrand.titrax-sheet",
      MIME_TOP_TYPE_APPLICATION},
    {"application/set-registration-initiation",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.groove-identity-message",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.irepository.package+xml",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.japannet-payment-wakeup",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.motorola.flexsuite.adsi",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.shana.informed.formdata",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.yellowriver-custom-menu",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.japannet-jpnstore-wakeup",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.japannet-setstore-wakeup",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.motorola.flexsuite.gotap",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.fujixerox.docuworks.binder",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.japannet-directory-service",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.shana.informed.interchange",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.shana.informed.formtemplate",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.uplanet.bearer-choice-wbxml",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.japannet-registration-wakeup",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.japannet-verification-wakeup",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.mitsubishi.misty-guard.trustweb",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.anser-web-funds-transfer-initiation",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.anser-web-certificate-issue-initiation",
      MIME_TOP_TYPE_APPLICATION},
    {"text/csv", MIME_TOP_TYPE_TEXT},
    {"video/dl", MIME_TOP_TYPE_VIDEO},
    {"video/dv", MIME_TOP_TYPE_VIDEO},
    {"video/gl", MIME_TOP_TYPE_VIDEO},
    {"audio/L16", MIME_TOP_TYPE_AUDIO},
    {"audio/L20", MIME_TOP_TYPE_AUDIO},
    {"audio/L24", MIME_TOP_TYPE_AUDIO},
    {"audio/ogg", MIME_TOP_TYPE_AUDIO},
    {"image/pcx", MIME_TOP_TYPE_IMAGE},
    {"text/h323", MIME_TOP_TYPE_TEXT},
    {"text/iuls", MIME_TOP_TYPE_TEXT},
    {"text/sgml", MIME_TOP_TYPE_TEXT},
    {"text/x-sh", MIME_TOP_TYPE_TEXT},
    {"video/fli", MIME_TOP_TYPE_VIDEO},
    {"video/mp4", MIME_TOP_TYPE_VIDEO},
    {"video/ogg", MIME_TOP_TYPE_VIDEO},
    {"audio/3gpp", MIME_TOP_TYPE_AUDIO},
    {"audio/midi", MIME_TOP_TYPE_AUDIO},
    {"image/x-jg", MIME_TOP_TYPE_IMAGE},
    {"inode/fifo", MIME_TOP_TYPE_INODE},
    {"text/x-boo", MIME_TOP_TYPE_TEXT},
    {"text/x-csh", MIME_TOP_TYPE_TEXT},
    {"text/x-moc", MIME_TOP_TYPE_TEXT},
    {"text/x-tcl", MIME_TOP_TYPE_TEXT},
    {"text/x-tex", MIME_TOP_TYPE_TEXT},
    {"video/3gpp", MIME_TOP_TYPE_VIDEO},
    {"audio/DAT12", MIME_TOP_TYPE_AUDIO},
    {"audio/x-gsm", MIME_TOP_TYPE_AUDIO},
    {"audio/x-sd2", MIME_TOP_TYPE_AUDIO},
    {"audio/x-wav", MIME_TOP_TYPE_AUDIO},
    {"image/x-jng", MIME_TOP_TYPE_IMAGE},
    {"image/x-rgb", MIME_TOP_TYPE_IMAGE},
    {"text/mathml", MIME_TOP_TYPE_TEXT},
    {"text/x-chdr", MIME_TOP_TYPE_TEXT},
    {"text/x-csrc", MIME_TOP_TYPE_TEXT},
    {"text/x-diff", MIME_TOP_TYPE_TEXT},
    {"text/x-dsrc", MIME_TOP_TYPE_TEXT},
    {"text/x-java", MIME_TOP_TYPE_TEXT},
    {"text/x-perl", MIME_TOP_TYPE_TEXT},
    {"video/x-mng", MIME_TOP_TYPE_VIDEO},
    {"audio/x-aiff", MIME_TOP_TYPE_AUDIO},
    {"image/x-icon", MIME_TOP_TYPE_IMAGE},
    {"inode/socket", MIME_TOP_TYPE_INODE},
    {"text/english", MIME_TOP_TYPE_TEXT},
    {"text/texmacs", MIME_TOP_TYPE_TEXT},
    {"text/x-vcard", MIME_TOP_TYPE_TEXT},
    {"audio/G.722.1", MIME_TOP_TYPE_AUDIO},
    {"audio/mpegurl", MIME_TOP_TYPE_AUDIO},
    {"audio/x-scpls", MIME_TOP_TYPE_AUDIO},
    {"image/svg+xml", MIME_TOP_TYPE_IMAGE},
    {"text/x-bibtex", MIME_TOP_TYPE_TEXT},
    {"text/x-c++hdr", MIME_TOP_TYPE_TEXT},
    {"text/x-c++src", MIME_TOP_TYPE_TEXT},
    {"text/x-pascal", MIME_TOP_TYPE_TEXT},
    {"text/x-python", MIME_TOP_TYPE_TEXT},
    {"text/x-setext", MIME_TOP_TYPE_TEXT},
    {"video/MP4V-ES", MIME_TOP_TYPE_VIDEO},
    {"video/vnd.mts", MIME_TOP_TYPE_VIDEO},
    {"video/x-ms-wm", MIME_TOP_TYPE_VIDEO},
    {"audio/x-ms-wax", MIME_TOP_TYPE_AUDIO},
    {"audio/x-ms-wma", MIME_TOP_TYPE_AUDIO},
    {"chemical/x-cdx", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-cif", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-cml", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-ctx", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-cxf", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-hin", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-pdb", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-vmd", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-xyz", MIME_TOP_TYPE_CHEMICAL},
    {"image/vnd.djvu", MIME_TOP_TYPE_IMAGE},
    {"image/x-ms-bmp", MIME_TOP_TYPE_IMAGE},
    {"text/scriptlet", MIME_TOP_TYPE_TEXT},
    {"text/x-crontab", MIME_TOP_TYPE_TEXT},
    {"text/x-haskell", MIME_TOP_TYPE_TEXT},
    {"text/x-pcs-gcd", MIME_TOP_TYPE_TEXT},
    {"video/x-la-asf", MIME_TOP_TYPE_VIDEO},
    {"video/x-ms-asf", MIME_TOP_TYPE_VIDEO},
    {"video/x-ms-wmv", MIME_TOP_TYPE_VIDEO},
    {"video/x-ms-wmx", MIME_TOP_TYPE_VIDEO},
    {"video/x-ms-wvx", MIME_TOP_TYPE_VIDEO},
    {"x-world/x-vrml", MIME_TOP_TYPE_X_WORLD},
    {"application/cap", MIME_TOP_TYPE_APPLICATION},
    {"application/hta", MIME_TOP_TYPE_APPLICATION},
    {"application/ogg", MIME_TOP_TYPE_APPLICATION},
    {"application/rar", MIME_TOP_TYPE_APPLICATION},
    {"audio/MP4A-LATM", MIME_TOP_TYPE_AUDIO},
    {"audio/x-mpegurl", MIME_TOP_TYPE_AUDIO},
    {"chemical/x-cmdf", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-csml", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-mol2", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-xtel", MIME_TOP_TYPE_CHEMICAL},
    {"image/x-xbitmap", MIME_TOP_TYPE_IMAGE},
    {"image/x-xpixmap", MIME_TOP_TYPE_IMAGE},
    {"inode/directory", MIME_TOP_TYPE_INODE},
    {"text/x-makefile", MIME_TOP_TYPE_TEXT},
    {"video/x-msvideo", MIME_TOP_TYPE_VIDEO},
    {"application/atom", MIME_TOP_TYPE_APPLICATION},
    {"application/smil", MIME_TOP_TYPE_APPLICATION},
    {"application/x-rx", MIME_TOP_TYPE_APPLICATION},
    {"application/x-sh", MIME_TOP_TYPE_APPLICATION},
    {"chemical/x-cache", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-mmcif", MIME_TOP_TYPE_CHEMICAL},
    {"inode/chardevice", MIME_TOP_TYPE_INODE},
    {"text/x-component", MIME_TOP_TYPE_TEXT},
    {"text/x-vcalendar", MIME_TOP_TYPE_TEXT},
    {"application/x-123", MIME_TOP_TYPE_APPLICATION},
    {"application/x-cab", MIME_TOP_TYPE_APPLICATION},
    {"application/x-cbr", MIME_TOP_TYPE_APPLICATION},
    {"application/x-cbz", MIME_TOP_TYPE_APPLICATION},
    {"application/x-cdf", MIME_TOP_TYPE_APPLICATION},
    {"application/x-csh", MIME_TOP_TYPE_APPLICATION},
    {"application/x-dms", MIME_TOP_TYPE_APPLICATION},
    {"application/x-dvi", MIME_TOP_TYPE_APPLICATION},
    {"application/x-hdf", MIME_TOP_TYPE_APPLICATION},
    {"application/x-ica", MIME_TOP_TYPE_APPLICATION},
    {"application/x-lha", MIME_TOP_TYPE_APPLICATION},
    {"application/x-lyx", MIME_TOP_TYPE_APPLICATION},
    {"application/x-lzh", MIME_TOP_TYPE_APPLICATION},
    {"application/x-lzx", MIME_TOP_TYPE_APPLICATION},
    {"application/x-mif", MIME_TOP_TYPE_APPLICATION},
    {"application/x-msi", MIME_TOP_TYPE_APPLICATION},
    {"application/x-nwc", MIME_TOP_TYPE_APPLICATION},
    {"application/x-tcl", MIME_TOP_TYPE_APPLICATION},
    {"application/x-xcf", MIME_TOP_TYPE_APPLICATION},
    {"audio/x-realaudio", MIME_TOP_TYPE_AUDIO},
    {"chemical/x-cerius", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-chem3d", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-rosdal", MIME_TOP_TYPE_CHEMICAL},
    {"image/x-coreldraw", MIME_TOP_TYPE_IMAGE},
    {"image/x-photoshop", MIME_TOP_TYPE_IMAGE},
    {"inode/blockdevice", MIME_TOP_TYPE_INODE},
    {"video/x-sgi-movie", MIME_TOP_TYPE_VIDEO},
    {"x-epoc/x-sisx-app", MIME_TOP_TYPE_X_EPOC},
    {"application/x-core", MIME_TOP_TYPE_APPLICATION},
    {"application/x-cpio", MIME_TOP_TYPE_APPLICATION},
    {"application/x-doom", MIME_TOP_TYPE_APPLICATION},
    {"application/x-flac", MIME_TOP_TYPE_APPLICATION},
    {"application/x-font", MIME_TOP_TYPE_APPLICATION},
    {"application/x-gtar", MIME_TOP_TYPE_APPLICATION},
    {"application/x-jmol", MIME_TOP_TYPE_APPLICATION},
    {"application/x-koan", MIME_TOP_TYPE_APPLICATION},
    {"application/x-shar", MIME_TOP_TYPE_APPLICATION},
    {"application/x-xfig", MIME_TOP_TYPE_APPLICATION},
    {"chemical/x-alchemy", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-compass", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-genbank", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-isostar", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-mdl-tgf", MIME_TOP_TYPE_CHEMICAL},
    {"image/x-cmu-raster", MIME_TOP_TYPE_IMAGE},
    {"application/EDI-X12", MIME_TOP_TYPE_APPLICATION},
    {"application/EDIFACT", MIME_TOP_TYPE_APPLICATION},
    {"application/dsptype", MIME_TOP_TYPE_APPLICATION},
    {"application/java-vm", MIME_TOP_TYPE_APPLICATION},
    {"application/ms-tnef", MIME_TOP_TYPE_APPLICATION},
    {"application/rdf+xml", MIME_TOP_TYPE_APPLICATION},
    {"application/rss+xml", MIME_TOP_TYPE_APPLICATION},
    {"application/x-bcpio", MIME_TOP_TYPE_APPLICATION},
    {"application/x-kword", MIME_TOP_TYPE_APPLICATION},
    {"application/x-latex", MIME_TOP_TYPE_APPLICATION},
    {"application/x-maker", MIME_TOP_TYPE_APPLICATION},
    {"application/x-trash", MIME_TOP_TYPE_APPLICATION},
    {"application/x-troff", MIME_TOP_TYPE_APPLICATION},
    {"application/x-ustar", MIME_TOP_TYPE_APPLICATION},
    {"application/x-wingz", MIME_TOP_TYPE_APPLICATION},
    {"chemical/x-chemdraw", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-jcamp-dx", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-kinemage", MIME_TOP_TYPE_CHEMICAL},
    {"image/x-xwindowdump", MIME_TOP_TYPE_IMAGE},
    {"application/cu-seeme", MIME_TOP_TYPE_APPLICATION},
    {"application/msaccess", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.smaf", MIME_TOP_TYPE_APPLICATION},
    {"application/x-cdlink", MIME_TOP_TYPE_APPLICATION},
    {"application/x-go-sgf", MIME_TOP_TYPE_APPLICATION},
    {"application/x-iphone", MIME_TOP_TYPE_APPLICATION},
    {"application/x-kchart", MIME_TOP_TYPE_APPLICATION},
    {"application/x-kdelnk", MIME_TOP_TYPE_APPLICATION},
    {"application/x-ms-wmd", MIME_TOP_TYPE_APPLICATION},
    {"application/x-ms-wmz", MIME_TOP_TYPE_APPLICATION},
    {"application/x-netcdf", MIME_TOP_TYPE_APPLICATION},
    {"application/x-object", MIME_TOP_TYPE_APPLICATION},
    {"application/x-sv4crc", MIME_TOP_TYPE_APPLICATION},
    {"application/x-tex-gf", MIME_TOP_TYPE_APPLICATION},
    {"application/x-tex-pk", MIME_TOP_TYPE_APPLICATION},
    {"audio/x-pn-realaudio", MIME_TOP_TYPE_AUDIO},
    {"chemical/x-cache-csf", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-crossfire", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-molconn-Z", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-mopac-out", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-mopac-vib", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-ncbi-asn1", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-swissprot", MIME_TOP_TYPE_CHEMICAL},
    {"application/ghostview", MIME_TOP_TYPE_APPLICATION},
    {"application/x-abiword", MIME_TOP_TYPE_APPLICATION},
    {"application/x-kspread", MIME_TOP_TYPE_APPLICATION},
    {"application/x-stuffit", MIME_TOP_TYPE_APPLICATION},
    {"application/x-sv4cpio", MIME_TOP_TYPE_APPLICATION},
    {"application/x-texinfo", MIME_TOP_TYPE_APPLICATION},
    {"application/xhtml+xml", MIME_TOP_TYPE_APPLICATION},
    {"chemical/x-mdl-rdfile", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-mdl-sdfile", MIME_TOP_TYPE_CHEMICAL},
    {"application/pics-rules", MIME_TOP_TYPE_APPLICATION},
    {"application/x-director", MIME_TOP_TYPE_APPLICATION},
    {"application/x-freemind", MIME_TOP_TYPE_APPLICATION},
    {"application/x-gnumeric", MIME_TOP_TYPE_APPLICATION},
    {"application/x-troff-me", MIME_TOP_TYPE_APPLICATION},
    {"application/x-troff-ms", MIME_TOP_TYPE_APPLICATION},
    {"application/x-videolan", MIME_TOP_TYPE_APPLICATION},
    {"chemical/x-macmolecule", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-mdl-molfile", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-mdl-rxnfile", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-mopac-graph", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-mopac-input", MIME_TOP_TYPE_CHEMICAL},
    {"inode/directory-locked", MIME_TOP_TYPE_INODE},
    {"text/vnd.flatland.3dml", MIME_TOP_TYPE_TEXT},
    {"application/EDI-Consent", MIME_TOP_TYPE_APPLICATION},
    {"application/atomcat+xml", MIME_TOP_TYPE_APPLICATION},
    {"application/docbook+xml", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.rim.cod", MIME_TOP_TYPE_APPLICATION},
    {"application/wordperfect", MIME_TOP_TYPE_APPLICATION},
    {"application/x-chess-pgn", MIME_TOP_TYPE_APPLICATION},
    {"application/x-httpd-php", MIME_TOP_TYPE_APPLICATION},
    {"application/x-java-bean", MIME_TOP_TYPE_APPLICATION},
    {"application/x-pkcs7-crl", MIME_TOP_TYPE_APPLICATION},
    {"application/x-troff-man", MIME_TOP_TYPE_APPLICATION},
    {"application/x-xpinstall", MIME_TOP_TYPE_APPLICATION},
    {"chemical/x-galactic-spc", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-gamess-input", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-gaussian-log", MIME_TOP_TYPE_CHEMICAL},
    {"image/x-corelphotopaint", MIME_TOP_TYPE_IMAGE},
    {"image/x-portable-anymap", MIME_TOP_TYPE_IMAGE},
    {"image/x-portable-bitmap", MIME_TOP_TYPE_IMAGE},
    {"image/x-portable-pixmap", MIME_TOP_TYPE_IMAGE},
    {"text/x-literate-haskell", MIME_TOP_TYPE_TEXT},
    {"x-conference/x-cooltalk", MIME_TOP_TYPE_X_CONFERENCE},
    {"application/atomserv+xml", MIME_TOP_TYPE_APPLICATION},
    {"application/futuresplash", MIME_TOP_TYPE_APPLICATION},
    {"application/java-archive", MIME_TOP_TYPE_APPLICATION},
    {"application/x-bittorrent", MIME_TOP_TYPE_APPLICATION},
    {"application/x-executable", MIME_TOP_TYPE_APPLICATION},
    {"application/x-httpd-php3", MIME_TOP_TYPE_APPLICATION},
    {"application/x-httpd-php4", MIME_TOP_TYPE_APPLICATION},
    {"application/x-javascript", MIME_TOP_TYPE_APPLICATION},
    {"application/x-kpresenter", MIME_TOP_TYPE_APPLICATION},
    {"chemical/x-cactvs-binary", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-gaussian-cube", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-gcg8-sequence", MIME_TOP_TYPE_CHEMICAL},
    {"image/x-coreldrawpattern", MIME_TOP_TYPE_IMAGE},
    {"image/x-portable-graymap", MIME_TOP_TYPE_IMAGE},
    {"application/x-httpd-eruby", MIME_TOP_TYPE_APPLICATION},
    {"application/x-java-applet", MIME_TOP_TYPE_APPLICATION},
    {"application/x-python-code", MIME_TOP_TYPE_APPLICATION},
    {"application/x-shellscript", MIME_TOP_TYPE_APPLICATION},
    {"application/x-wais-source", MIME_TOP_TYPE_APPLICATION},
    {"chemical/x-gaussian-input", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-ncbi-asn1-spec", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-vamas-iso14976", MIME_TOP_TYPE_CHEMICAL},
    {"image/x-coreldrawtemplate", MIME_TOP_TYPE_IMAGE},
    {"text/x-server-parsed-html", MIME_TOP_TYPE_TEXT},
    {"application/mac-compactpro", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.FloGraphIt", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.Mobius.DAF", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.Mobius.DIS", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.Mobius.MBK", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.Mobius.MQY", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.Mobius.MSL", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.Mobius.PLC", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.Mobius.TXF", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.cinderella", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.ms-pki.stl", MIME_TOP_TYPE_APPLICATION},
    {"application/x-futuresplash", MIME_TOP_TYPE_APPLICATION},
    {"application/x-killustrator", MIME_TOP_TYPE_APPLICATION},
    {"application/x-x509-ca-cert", MIME_TOP_TYPE_APPLICATION},
    {"chemical/x-ncbi-asn1-ascii", MIME_TOP_TYPE_CHEMICAL},
    {"application/mathematica-old", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.cosmocaller", MIME_TOP_TYPE_APPLICATION},
    {"application/x-7z-compressed", MIME_TOP_TYPE_APPLICATION},
    {"application/x-iso9660-image", MIME_TOP_TYPE_APPLICATION},
    {"application/x-msdos-program", MIME_TOP_TYPE_APPLICATION},
    {"audio/x-pn-realaudio-plugin", MIME_TOP_TYPE_AUDIO},
    {"chemical/x-macromodel-input", MIME_TOP_TYPE_CHEMICAL},
    {"chemical/x-ncbi-asn1-binary", MIME_TOP_TYPE_CHEMICAL},
    {"application/vnd.sun.xml.calc", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.sun.xml.draw", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.sun.xml.math", MIME_TOP_TYPE_APPLICATION},
    {"application/x-debian-package", MIME_TOP_TYPE_APPLICATION},
    {"application/x-java-jnlp-file", MIME_TOP_TYPE_APPLICATION},
    {"application/x-oz-application", MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.ms-pki.seccat",
      MIME_TOP_TYPE_APPLICATION},
    {"application/x-apple-diskimage",
      MIME_TOP_TYPE_APPLICATION},
    {"application/x-internet-signup",
      MIME_TOP_TYPE_APPLICATION},
    {"application/x-quicktimeplayer",
      MIME_TOP_TYPE_APPLICATION},
    {"application/x-shockwave-flash",
      MIME_TOP_TYPE_APPLICATION},
    {"chemical/x-embl-dl-nucleotide",
      MIME_TOP_TYPE_CHEMICAL},
    {"application/vnd.sun.xml.writer",
      MIME_TOP_TYPE_APPLICATION},
    {"application/x-httpd-php-source",
      MIME_TOP_TYPE_APPLICATION},
    {"chemical/x-gaussian-checkpoint",
      MIME_TOP_TYPE_CHEMICAL},
    {"application/vnd.sun.xml.impress",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.symbian.install",
      MIME_TOP_TYPE_APPLICATION},
    {"application/x-pkcs7-certreqresp",
      MIME_TOP_TYPE_APPLICATION},
    {"text/xml-external-parsed-entity",
      MIME_TOP_TYPE_TEXT},
    {"application/vnd.google-earth.kmz",
      MIME_TOP_TYPE_APPLICATION},
    {"text/vnd.sun.j2me.app-descriptor",
      MIME_TOP_TYPE_TEXT},
    {"application/vnd.stardivision.calc",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.stardivision.draw",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.stardivision.math",
      MIME_TOP_TYPE_APPLICATION},
    {"application/x-graphing-calculator",
      MIME_TOP_TYPE_APPLICATION},
    {"application/x-ns-proxy-autoconfig",
      MIME_TOP_TYPE_APPLICATION},
    {"model/vnd.parasolid.transmit.text",
      MIME_TOP_TYPE_MODEL},
    {"application/java-serialized-object",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.$commerce_battelle",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.stardivision.chart",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.stardivision.writer",
      MIME_TOP_TYPE_APPLICATION},
    {"model/vnd.parasolid.transmit.binary",
      MIME_TOP_TYPE_MODEL},
    {"application/vnd.google-earth.kml+xml",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.stardivision.impress",
      MIME_TOP_TYPE_APPLICATION},
    {"application/x-redhat-package-manager",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.sun.xml.calc.template",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.sun.xml.draw.template",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.sun.xml.writer.global",
      MIME_TOP_TYPE_APPLICATION},
    {"application/x-httpd-php3-preprocessed",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.oasis.opendocument.text",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.sun.xml.writer.template",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.oasis.opendocument.chart",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.oasis.opendocument.image",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.sun.xml.impress.template",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.oasis.opendocument.formula",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.stardivision.writer-global",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.oasis.opendocument.database",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.oasis.opendocument.graphics",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.oasis.opendocument.text-web",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.oasis.opendocument.spreadsheet",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.oasis.opendocument.text-master",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.oasis.opendocument.presentation",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.oasis.opendocument.text-template",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.oasis.opendocument.graphics-template",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.oasis.opendocument.spreadsheet-template",
      MIME_TOP_TYPE_APPLICATION},
    {"application/vnd.oasis.opendocument.presentation-template",
      MIME_TOP_TYPE_APPLICATION},

    {NULL, MIME_TOP_TYPE_ERR}
};

const char *mime_string(enum mime_types mtype) {
    if (mtype <= 724) {
        return lookup[mtype].name;
    } else {
        return NULL;
    }
}

enum mime_top_types mime_top_type(enum mime_types mtype) {
    if (mtype <= 724) {
        return lookup[mtype].toptype;
    } else {
        return MIME_TOP_TYPE_ERR;
    }
}

       
/* FIXME: do this properly, using parsing-type stuff */
enum mime_types mime_content_guess(const void *buf, unsigned int len) {
    const char *cbuf = buf;

    if (len >= 4) {
        /* test for JPEG */
        if ((cbuf[0] == (char) 0xff) && (cbuf[1] == (char) 0xd8) 
          && (cbuf[2] == (char) 0xff) && (cbuf[3] == (char) 0xe0)) {
            return MIME_TYPE_IMAGE_JPEG;
        }
    }

    if (len >= 6) {
        /* test for GIF */
        if (!str_ncmp(cbuf, "GIF8", 4) && ((cbuf[4] == '9') || (cbuf[4] == '7'))
          && (cbuf[5] == 'a')) {
            return MIME_TYPE_IMAGE_GIF;
        }
    }

    if (len >= 4) {
        /* test for MS cbuf (badly) */
        if ((cbuf[0] == (char) 0xd0) && (cbuf[1] == (char) 0xcf) 
          && (cbuf[2] == (char) 0x11) && (cbuf[3] == (char) 0xe0)) {
            /* XXX: not strictly true, its just an OLE document, but most of 
             * them are MS cbuf docs anyway.  Testing for MS cbuf requires 
             * looking further into the document, so we won't be doing that 
             * here. */
            return MIME_TYPE_APPLICATION_MSWORD;
        }

        if (len == 2) {
            if ((cbuf[0] == (char) 0x31) && (cbuf[1] == (char) 0xbe) 
              && (cbuf[0] == '\0')) {
                /* more MS cbuf stuff :o( */
                return MIME_TYPE_APPLICATION_MSWORD;
            } else if ((cbuf[0] == (char) 0xfe) && (cbuf[1] == '7') 
              && (cbuf[0] == '\0')) {
                /* office document */
                return MIME_TYPE_APPLICATION_MSWORD;
            }
        }
    }

    /* test for wordperfect files */
    if (len >= 4) {
        if ((cbuf[0] == (char) 0xff) && (cbuf[1] == 'W') && (cbuf[2] == 'P') 
          && (cbuf[3] == 'C')) {
            return MIME_TYPE_APPLICATION_WORDPERFECT5_1;
        }
    }

    /* test for postscript files */
    if (len >= 2) {
        if ((cbuf[0] == '%') && (cbuf[1] == '!')) {
            return MIME_TYPE_APPLICATION_POSTSCRIPT;
        }
    }

    /* test for PDF files */
    if (len >= 5) {
        if ((cbuf[0] == '%') && (cbuf[1] == 'P') && (cbuf[2] == 'D') 
          && (cbuf[3] == 'F') && (cbuf[4] == '-')) {
            return MIME_TYPE_APPLICATION_PDF;
        }
    }

    /* test for markup languages, first locating the first
     * non-whitespace character */
    while (isspace(*cbuf) && len) {
        cbuf++;
        len--;
    }

    /* TREC documents */
    if (((len >= str_len("<doc>")) 
        && !str_ncasecmp("<doc>", cbuf, str_len("<doc>")))) {
        return MIME_TYPE_APPLICATION_X_TREC;
    }

    /* INEX documents */
    if (((len >= str_len("<article>")) 
        && !str_ncasecmp("<article>", cbuf, str_len("<article>")))) {
        return MIME_TYPE_APPLICATION_X_INEX;
    }

    /* HTML */
    if (((len >= str_len("<!doctype html")) 
        && !str_ncasecmp("<!doctype html", cbuf, str_len("<!doctype html")))
      || ((len >= str_len("<head")) 
        && !str_ncasecmp("<head", cbuf, str_len("<head")))
      || ((len >= str_len("<title")) 
        && !str_ncasecmp("<title", cbuf, str_len("<title")))
      || ((len >= str_len("<html")) 
        && !str_ncasecmp("<html", cbuf, str_len("<html")))) {
        return MIME_TYPE_TEXT_HTML;
    }

    /* SGML */
    if (((len >= str_len("<!doctype ")) 
        && !str_ncasecmp("<!doctype ", cbuf, str_len("<!doctype ")))
      || ((len >= str_len("<subdoc")) 
        && !str_ncasecmp("<subdoc", cbuf, str_len("<subdoc")))) {
        return MIME_TYPE_TEXT_SGML;
    }

    /* XML */
    if (((len >= str_len("<?xml")) 
        && !str_ncasecmp("<?xml", cbuf, str_len("<?xml")))) {
        return MIME_TYPE_TEXT_XML;
    }

    /* XXX: test for tar files */

    return MIME_TYPE_APPLICATION_OCTET_STREAM;
}

enum mime_types mime_type(const char *str) {

    switch (*str++) {
    case 'a':
    case 'A':
        goto a_label;

    case 'c':
    case 'C':
        /* skip to prefix 'chemical/x-' */
        if (!str_ncasecmp(str, "hemical/x-", 10)) {
            str += 10;
            goto chemical_x__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'i':
    case 'I':
        goto i_label;

    case 'm':
    case 'M':
        goto m_label;

    case 't':
    case 'T':
        /* skip to prefix 'text/' */
        if (!str_ncasecmp(str, "ext/", 4)) {
            str += 4;
            goto text__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'v':
    case 'V':
        /* skip to prefix 'video/' */
        if (!str_ncasecmp(str, "ideo/", 5)) {
            str += 5;
            goto video__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'x':
    case 'X':
        /* skip to prefix 'x-' */
        if (!str_ncasecmp(str, "-", 1)) {
            str += 1;
            goto x__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

a_label:
    switch (*str++) {
    case 'p':
    case 'P':
        /* skip to prefix 'application/' */
        if (!str_ncasecmp(str, "plication/", 10)) {
            str += 10;
            goto application__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'u':
    case 'U':
        /* skip to prefix 'audio/' */
        if (!str_ncasecmp(str, "dio/", 4)) {
            str += 4;
            goto audio__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application__label:
    switch (*str++) {
    case 'a':
    case 'A':
        goto application_a_label;

    case 'c':
    case 'C':
        goto application_c_label;

    case 'b':
    case 'B':
        goto application_b_label;

    case 'e':
    case 'E':
        goto application_e_label;

    case 'd':
    case 'D':
        goto application_d_label;

    case 'g':
    case 'G':
        /* must be 'application/ghostview' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_GHOSTVIEW].name[13])) {
            return MIME_TYPE_APPLICATION_GHOSTVIEW;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'f':
    case 'F':
        goto application_f_label;

    case 'i':
    case 'I':
        goto application_i_label;

    case 'h':
    case 'H':
        goto application_h_label;

    case 'j':
    case 'J':
        /* skip to prefix 'application/java-' */
        if (!str_ncasecmp(str, "ava-", 4)) {
            str += 4;
            goto application_java__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'm':
    case 'M':
        goto application_m_label;

    case 'o':
    case 'O':
        goto application_o_label;

    case 'n':
    case 'N':
        /* skip to prefix 'application/news-' */
        if (!str_ncasecmp(str, "ews-", 4)) {
            str += 4;
            goto application_news__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'q':
    case 'Q':
        /* must be 'application/qsig' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_QSIG].name[13])) {
            return MIME_TYPE_APPLICATION_QSIG;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'p':
    case 'P':
        goto application_p_label;

    case 's':
    case 'S':
        goto application_s_label;

    case 'r':
    case 'R':
        goto application_r_label;

    case 't':
    case 'T':
        /* skip to prefix 'application/timestamp-' */
        if (!str_ncasecmp(str, "imestamp-", 9)) {
            str += 9;
            goto application_timestamp__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'w':
    case 'W':
        goto application_w_label;

    case 'v':
    case 'V':
        goto application_v_label;

    case 'x':
    case 'X':
        goto application_x_label;

    case 'z':
    case 'Z':
        /* must be 'application/zip' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_ZIP].name[13])) {
            return MIME_TYPE_APPLICATION_ZIP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_a_label:
    switch (*str++) {
    case 'p':
    case 'P':
        /* must be 'application/applefile' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_APPLEFILE].name[14])) {
            return MIME_TYPE_APPLICATION_APPLEFILE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'c':
    case 'C':
        /* must be 'application/activemessage' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_ACTIVEMESSAGE].name[14])) {
            return MIME_TYPE_APPLICATION_ACTIVEMESSAGE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 't':
    case 'T':
        /* skip to prefix 'application/atom' */
        if (!str_ncasecmp(str, "om", 2)) {
            str += 2;
            goto application_atom_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'n':
    case 'N':
        /* must be 'application/andrew-inset' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_ANDREW_INSET].name[14])) {
            return MIME_TYPE_APPLICATION_ANDREW_INSET;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_atom_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_ATOM;

    case 'i':
    case 'I':
        /* must be 'application/atomicmail' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_ATOMICMAIL].name[17])) {
            return MIME_TYPE_APPLICATION_ATOMICMAIL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'c':
    case 'C':
        /* must be 'application/atomcat+xml' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_ATOMCAT_XML].name[17])) {
            return MIME_TYPE_APPLICATION_ATOMCAT_XML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* must be 'application/atomserv+xml' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_ATOMSERV_XML].name[17])) {
            return MIME_TYPE_APPLICATION_ATOMSERV_XML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_c_label:
    switch (*str++) {
    case 'a':
    case 'A':
        goto application_ca_label;

    case 'y':
    case 'Y':
        /* must be 'application/cybercash' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_CYBERCASH].name[14])) {
            return MIME_TYPE_APPLICATION_CYBERCASH;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'u':
    case 'U':
        /* must be 'application/cu-seeme' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_CU_SEEME].name[14])) {
            return MIME_TYPE_APPLICATION_CU_SEEME;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'o':
    case 'O':
        /* must be 'application/commonground' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_COMMONGROUND].name[14])) {
            return MIME_TYPE_APPLICATION_COMMONGROUND;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_ca_label:
    switch (*str++) {
    case 'p':
    case 'P':
        /* must be 'application/cap' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_CAP].name[15])) {
            return MIME_TYPE_APPLICATION_CAP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'l':
    case 'L':
        /* must be 'application/cals-1840' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_CALS_1840].name[15])) {
            return MIME_TYPE_APPLICATION_CALS_1840;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_b_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'application/batch-smtp' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_BATCH_SMTP].name[14])) {
            return MIME_TYPE_APPLICATION_BATCH_SMTP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'e':
    case 'E':
        /* must be 'application/beep+xml' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_BEEP_XML].name[14])) {
            return MIME_TYPE_APPLICATION_BEEP_XML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_e_label:
    switch (*str++) {
    case 's':
    case 'S':
        /* must be 'application/eshop' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_ESHOP].name[14])) {
            return MIME_TYPE_APPLICATION_ESHOP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'd':
    case 'D':
        /* skip to prefix 'application/edi' */
        if (!str_ncasecmp(str, "i", 1)) {
            str += 1;
            goto application_edi_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_edi_label:
    switch (*str++) {
    case '-':
        goto application_edi__label;

    case 'f':
    case 'F':
        /* must be 'application/edifact' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_EDIFACT].name[16])) {
            return MIME_TYPE_APPLICATION_EDIFACT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_edi__label:
    switch (*str++) {
    case 'x':
    case 'X':
        /* must be 'application/edi-x12' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_EDI_X12].name[17])) {
            return MIME_TYPE_APPLICATION_EDI_X12;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'c':
    case 'C':
        /* must be 'application/edi-consent' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_EDI_CONSENT].name[17])) {
            return MIME_TYPE_APPLICATION_EDI_CONSENT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_d_label:
    switch (*str++) {
    case 'c':
    case 'C':
        /* must be 'application/dca-rft' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_DCA_RFT].name[14])) {
            return MIME_TYPE_APPLICATION_DCA_RFT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'e':
    case 'E':
        /* must be 'application/dec-dx' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_DEC_DX].name[14])) {
            return MIME_TYPE_APPLICATION_DEC_DX;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* must be 'application/dsptype' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_DSPTYPE].name[14])) {
            return MIME_TYPE_APPLICATION_DSPTYPE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'o':
    case 'O':
        /* must be 'application/docbook+xml' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_DOCBOOK_XML].name[14])) {
            return MIME_TYPE_APPLICATION_DOCBOOK_XML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'v':
    case 'V':
        /* must be 'application/dvcs' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_DVCS].name[14])) {
            return MIME_TYPE_APPLICATION_DVCS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_f_label:
    switch (*str++) {
    case 'u':
    case 'U':
        /* must be 'application/futuresplash' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_FUTURESPLASH].name[14])) {
            return MIME_TYPE_APPLICATION_FUTURESPLASH;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'o':
    case 'O':
        /* must be 'application/font-tdpfr' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_FONT_TDPFR].name[14])) {
            return MIME_TYPE_APPLICATION_FONT_TDPFR;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_i_label:
    switch (*str++) {
    case 'p':
    case 'P':
        /* must be 'application/ipp' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_IPP].name[14])) {
            return MIME_TYPE_APPLICATION_IPP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* must be 'application/isup' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_ISUP].name[14])) {
            return MIME_TYPE_APPLICATION_ISUP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'o':
    case 'O':
        /* must be 'application/iotp' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_IOTP].name[14])) {
            return MIME_TYPE_APPLICATION_IOTP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'g':
    case 'G':
        /* must be 'application/iges' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_IGES].name[14])) {
            return MIME_TYPE_APPLICATION_IGES;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'n':
    case 'N':
        /* skip to prefix 'application/index' */
        if (!str_ncasecmp(str, "dex", 3)) {
            str += 3;
            goto application_index_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_index_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_INDEX;

    case '.':
        goto application_index__label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_index__label:
    switch (*str++) {
    case 'c':
    case 'C':
        /* must be 'application/index.cmd' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_INDEX_CMD].name[19])) {
            return MIME_TYPE_APPLICATION_INDEX_CMD;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'r':
    case 'R':
        /* must be 'application/index.response' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_INDEX_RESPONSE].name[19])) {
            return MIME_TYPE_APPLICATION_INDEX_RESPONSE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'o':
    case 'O':
        /* must be 'application/index.obj' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_INDEX_OBJ].name[19])) {
            return MIME_TYPE_APPLICATION_INDEX_OBJ;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'v':
    case 'V':
        /* must be 'application/index.vnd' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_INDEX_VND].name[19])) {
            return MIME_TYPE_APPLICATION_INDEX_VND;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_h_label:
    switch (*str++) {
    case 'y':
    case 'Y':
        /* must be 'application/hyperstudio' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_HYPERSTUDIO].name[14])) {
            return MIME_TYPE_APPLICATION_HYPERSTUDIO;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 't':
    case 'T':
        goto application_ht_label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_ht_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'application/hta' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_HTA].name[15])) {
            return MIME_TYPE_APPLICATION_HTA;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 't':
    case 'T':
        /* must be 'application/http' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_HTTP].name[15])) {
            return MIME_TYPE_APPLICATION_HTTP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_java__label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'application/java-archive' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_JAVA_ARCHIVE].name[18])) {
            return MIME_TYPE_APPLICATION_JAVA_ARCHIVE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* must be 'application/java-serialized-object' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_JAVA_SERIALIZED_OBJECT].name[18])) {
            return MIME_TYPE_APPLICATION_JAVA_SERIALIZED_OBJECT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'v':
    case 'V':
        /* must be 'application/java-vm' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_JAVA_VM].name[18])) {
            return MIME_TYPE_APPLICATION_JAVA_VM;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_m_label:
    switch (*str++) {
    case 'a':
    case 'A':
        goto application_ma_label;

    case 's':
    case 'S':
        goto application_ms_label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_ma_label:
    switch (*str++) {
    case 'c':
    case 'C':
        goto application_mac_label;

    case 'r':
    case 'R':
        /* must be 'application/marc' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_MARC].name[15])) {
            return MIME_TYPE_APPLICATION_MARC;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 't':
    case 'T':
        /* skip to prefix 'application/mathematica' */
        if (!str_ncasecmp(str, "hematica", 8)) {
            str += 8;
            goto application_mathematica_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_mac_label:
    switch (*str++) {
    case '-':
        goto application_mac__label;

    case 'w':
    case 'W':
        /* must be 'application/macwriteii' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_MACWRITEII].name[16])) {
            return MIME_TYPE_APPLICATION_MACWRITEII;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_mac__label:
    switch (*str++) {
    case 'c':
    case 'C':
        /* must be 'application/mac-compactpro' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_MAC_COMPACTPRO].name[17])) {
            return MIME_TYPE_APPLICATION_MAC_COMPACTPRO;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'b':
    case 'B':
        /* must be 'application/mac-binhex40' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_MAC_BINHEX40].name[17])) {
            return MIME_TYPE_APPLICATION_MAC_BINHEX40;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_mathematica_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_MATHEMATICA;

    case '-':
        /* must be 'application/mathematica-old' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_MATHEMATICA_OLD].name[24])) {
            return MIME_TYPE_APPLICATION_MATHEMATICA_OLD;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_ms_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'application/msaccess' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_MSACCESS].name[15])) {
            return MIME_TYPE_APPLICATION_MSACCESS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case '-':
        /* must be 'application/ms-tnef' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_MS_TNEF].name[15])) {
            return MIME_TYPE_APPLICATION_MS_TNEF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'w':
    case 'W':
        /* must be 'application/msword' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_MSWORD].name[15])) {
            return MIME_TYPE_APPLICATION_MSWORD;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_o_label:
    switch (*str++) {
    case 'c':
    case 'C':
        goto application_oc_label;

    case 'd':
    case 'D':
        /* must be 'application/oda' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_ODA].name[14])) {
            return MIME_TYPE_APPLICATION_ODA;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'g':
    case 'G':
        /* must be 'application/ogg' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_OGG].name[14])) {
            return MIME_TYPE_APPLICATION_OGG;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_oc_label:
    switch (*str++) {
    case 's':
    case 'S':
        /* skip to prefix 'application/ocsp-re' */
        if (!str_ncasecmp(str, "p-re", 4)) {
            str += 4;
            goto application_ocsp_re_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 't':
    case 'T':
        /* must be 'application/octet-stream' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_OCTET_STREAM].name[15])) {
            return MIME_TYPE_APPLICATION_OCTET_STREAM;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_ocsp_re_label:
    switch (*str++) {
    case 'q':
    case 'Q':
        /* must be 'application/ocsp-request' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_OCSP_REQUEST].name[20])) {
            return MIME_TYPE_APPLICATION_OCSP_REQUEST;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* must be 'application/ocsp-response' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_OCSP_RESPONSE].name[20])) {
            return MIME_TYPE_APPLICATION_OCSP_RESPONSE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_news__label:
    switch (*str++) {
    case 'm':
    case 'M':
        /* must be 'application/news-message-id' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_NEWS_MESSAGE_ID].name[18])) {
            return MIME_TYPE_APPLICATION_NEWS_MESSAGE_ID;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 't':
    case 'T':
        /* must be 'application/news-transmission' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_NEWS_TRANSMISSION].name[18])) {
            return MIME_TYPE_APPLICATION_NEWS_TRANSMISSION;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_p_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'application/parityfec' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_PARITYFEC].name[14])) {
            return MIME_TYPE_APPLICATION_PARITYFEC;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'd':
    case 'D':
        /* must be 'application/pdf' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_PDF].name[14])) {
            return MIME_TYPE_APPLICATION_PDF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'g':
    case 'G':
        /* skip to prefix 'application/pgp-' */
        if (!str_ncasecmp(str, "p-", 2)) {
            str += 2;
            goto application_pgp__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'i':
    case 'I':
        /* must be 'application/pics-rules' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_PICS_RULES].name[14])) {
            return MIME_TYPE_APPLICATION_PICS_RULES;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'k':
    case 'K':
        goto application_pk_label;

    case 'o':
    case 'O':
        /* must be 'application/postscript' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_POSTSCRIPT].name[14])) {
            return MIME_TYPE_APPLICATION_POSTSCRIPT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'r':
    case 'R':
        /* skip to prefix 'application/prs.' */
        if (!str_ncasecmp(str, "s.", 2)) {
            str += 2;
            goto application_prs__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_pgp__label:
    switch (*str++) {
    case 'k':
    case 'K':
        /* must be 'application/pgp-keys' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_PGP_KEYS].name[17])) {
            return MIME_TYPE_APPLICATION_PGP_KEYS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'e':
    case 'E':
        /* must be 'application/pgp-encrypted' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_PGP_ENCRYPTED].name[17])) {
            return MIME_TYPE_APPLICATION_PGP_ENCRYPTED;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* must be 'application/pgp-signature' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_PGP_SIGNATURE].name[17])) {
            return MIME_TYPE_APPLICATION_PGP_SIGNATURE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_pk_label:
    switch (*str++) {
    case 'i':
    case 'I':
        /* skip to prefix 'application/pkix' */
        if (!str_ncasecmp(str, "x", 1)) {
            str += 1;
            goto application_pkix_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'c':
    case 'C':
        /* skip to prefix 'application/pkcs' */
        if (!str_ncasecmp(str, "s", 1)) {
            str += 1;
            goto application_pkcs_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_pkix_label:
    switch (*str++) {
    case 'c':
    case 'C':
        /* must be 'application/pkixcmp' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_PKIXCMP].name[17])) {
            return MIME_TYPE_APPLICATION_PKIXCMP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case '-':
        /* skip to prefix 'application/pkix-c' */
        if (!str_ncasecmp(str, "c", 1)) {
            str += 1;
            goto application_pkix_c_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_pkix_c_label:
    switch (*str++) {
    case 'r':
    case 'R':
        /* must be 'application/pkix-crl' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_PKIX_CRL].name[19])) {
            return MIME_TYPE_APPLICATION_PKIX_CRL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'e':
    case 'E':
        /* must be 'application/pkix-cert' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_PKIX_CERT].name[19])) {
            return MIME_TYPE_APPLICATION_PKIX_CERT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_pkcs_label:
    switch (*str++) {
    case '1':
        /* must be 'application/pkcs10' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_PKCS10].name[17])) {
            return MIME_TYPE_APPLICATION_PKCS10;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case '7':
        /* skip to prefix 'application/pkcs7-' */
        if (!str_ncasecmp(str, "-", 1)) {
            str += 1;
            goto application_pkcs7__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_pkcs7__label:
    switch (*str++) {
    case 's':
    case 'S':
        /* must be 'application/pkcs7-signature' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_PKCS7_SIGNATURE].name[19])) {
            return MIME_TYPE_APPLICATION_PKCS7_SIGNATURE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'm':
    case 'M':
        /* must be 'application/pkcs7-mime' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_PKCS7_MIME].name[19])) {
            return MIME_TYPE_APPLICATION_PKCS7_MIME;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_prs__label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'application/prs.alvestrand.titrax-sheet' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_PRS_ALVESTRAND_TITRAX_SHEET].name[17])) {
            return MIME_TYPE_APPLICATION_PRS_ALVESTRAND_TITRAX_SHEET;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'c':
    case 'C':
        /* must be 'application/prs.cww' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_PRS_CWW].name[17])) {
            return MIME_TYPE_APPLICATION_PRS_CWW;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'n':
    case 'N':
        /* must be 'application/prs.nprend' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_PRS_NPREND].name[17])) {
            return MIME_TYPE_APPLICATION_PRS_NPREND;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_s_label:
    switch (*str++) {
    case 'e':
    case 'E':
        /* skip to prefix 'application/set-' */
        if (!str_ncasecmp(str, "t-", 2)) {
            str += 2;
            goto application_set__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'd':
    case 'D':
        /* must be 'application/sdp' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_SDP].name[14])) {
            return MIME_TYPE_APPLICATION_SDP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'g':
    case 'G':
        /* skip to prefix 'application/sgml' */
        if (!str_ncasecmp(str, "ml", 2)) {
            str += 2;
            goto application_sgml_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'i':
    case 'I':
        /* must be 'application/sieve' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_SIEVE].name[14])) {
            return MIME_TYPE_APPLICATION_SIEVE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'm':
    case 'M':
        /* must be 'application/smil' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_SMIL].name[14])) {
            return MIME_TYPE_APPLICATION_SMIL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'l':
    case 'L':
        /* must be 'application/slate' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_SLATE].name[14])) {
            return MIME_TYPE_APPLICATION_SLATE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_set__label:
    switch (*str++) {
    case 'p':
    case 'P':
        /* skip to prefix 'application/set-payment' */
        if (!str_ncasecmp(str, "ayment", 6)) {
            str += 6;
            goto application_set_payment_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'r':
    case 'R':
        /* skip to prefix 'application/set-registration' */
        if (!str_ncasecmp(str, "egistration", 11)) {
            str += 11;
            goto application_set_registration_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_set_payment_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_SET_PAYMENT;

    case '-':
        /* must be 'application/set-payment-initiation' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_SET_PAYMENT_INITIATION].name[24])) {
            return MIME_TYPE_APPLICATION_SET_PAYMENT_INITIATION;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_set_registration_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_SET_REGISTRATION;

    case '-':
        /* must be 'application/set-registration-initiation' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_SET_REGISTRATION_INITIATION].name[29])) {
            return MIME_TYPE_APPLICATION_SET_REGISTRATION_INITIATION;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_sgml_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_SGML;

    case '-':
        /* must be 'application/sgml-open-catalog' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_SGML_OPEN_CATALOG].name[17])) {
            return MIME_TYPE_APPLICATION_SGML_OPEN_CATALOG;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_r_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'application/rar' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_RAR].name[14])) {
            return MIME_TYPE_APPLICATION_RAR;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'e':
    case 'E':
        /* must be 'application/remote-printing' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_REMOTE_PRINTING].name[14])) {
            return MIME_TYPE_APPLICATION_REMOTE_PRINTING;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'd':
    case 'D':
        /* must be 'application/rdf+xml' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_RDF_XML].name[14])) {
            return MIME_TYPE_APPLICATION_RDF_XML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'i':
    case 'I':
        /* must be 'application/riscos' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_RISCOS].name[14])) {
            return MIME_TYPE_APPLICATION_RISCOS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* must be 'application/rss+xml' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_RSS_XML].name[14])) {
            return MIME_TYPE_APPLICATION_RSS_XML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 't':
    case 'T':
        /* must be 'application/rtf' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_RTF].name[14])) {
            return MIME_TYPE_APPLICATION_RTF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_timestamp__label:
    switch (*str++) {
    case 'q':
    case 'Q':
        /* must be 'application/timestamp-query' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_TIMESTAMP_QUERY].name[23])) {
            return MIME_TYPE_APPLICATION_TIMESTAMP_QUERY;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'r':
    case 'R':
        /* must be 'application/timestamp-reply' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_TIMESTAMP_REPLY].name[23])) {
            return MIME_TYPE_APPLICATION_TIMESTAMP_REPLY;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_w_label:
    switch (*str++) {
    case 'i':
    case 'I':
        /* must be 'application/wita' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_WITA].name[14])) {
            return MIME_TYPE_APPLICATION_WITA;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'h':
    case 'H':
        /* skip to prefix 'application/whoispp-' */
        if (!str_ncasecmp(str, "oispp-", 6)) {
            str += 6;
            goto application_whoispp__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'o':
    case 'O':
        /* skip to prefix 'application/wordperfect' */
        if (!str_ncasecmp(str, "rdperfect", 9)) {
            str += 9;
            goto application_wordperfect_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_whoispp__label:
    switch (*str++) {
    case 'q':
    case 'Q':
        /* must be 'application/whoispp-query' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_WHOISPP_QUERY].name[21])) {
            return MIME_TYPE_APPLICATION_WHOISPP_QUERY;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'r':
    case 'R':
        /* must be 'application/whoispp-response' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_WHOISPP_RESPONSE].name[21])) {
            return MIME_TYPE_APPLICATION_WHOISPP_RESPONSE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_wordperfect_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_WORDPERFECT;

    case '5':
        /* must be 'application/wordperfect5.1' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_WORDPERFECT5_1].name[24])) {
            return MIME_TYPE_APPLICATION_WORDPERFECT5_1;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_v_label:
    switch (*str++) {
    case 'e':
    case 'E':
        /* must be 'application/vemmi' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VEMMI].name[14])) {
            return MIME_TYPE_APPLICATION_VEMMI;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'n':
    case 'N':
        /* skip to prefix 'application/vnd.' */
        if (!str_ncasecmp(str, "d.", 2)) {
            str += 2;
            goto application_vnd__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd__label:
    switch (*str++) {
    case '$':
        /* must be 'application/vnd.$commerce_battelle' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_COMMERCE_BATTELLE].name[17])) {
            return MIME_TYPE_APPLICATION_VND_COMMERCE_BATTELLE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case '3':
        /* must be 'application/vnd.3m.post-it-notes' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_3M_POST_IT_NOTES].name[17])) {
            return MIME_TYPE_APPLICATION_VND_3M_POST_IT_NOTES;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'a':
    case 'A':
        goto application_vnd_a_label;

    case 'c':
    case 'C':
        goto application_vnd_c_label;

    case 'b':
    case 'B':
        goto application_vnd_b_label;

    case 'e':
    case 'E':
        goto application_vnd_e_label;

    case 'd':
    case 'D':
        goto application_vnd_d_label;

    case 'g':
    case 'G':
        goto application_vnd_g_label;

    case 'f':
    case 'F':
        goto application_vnd_f_label;

    case 'i':
    case 'I':
        goto application_vnd_i_label;

    case 'h':
    case 'H':
        goto application_vnd_h_label;

    case 'k':
    case 'K':
        /* must be 'application/vnd.koan' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_KOAN].name[17])) {
            return MIME_TYPE_APPLICATION_VND_KOAN;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'j':
    case 'J':
        /* skip to prefix 'application/vnd.japannet-' */
        if (!str_ncasecmp(str, "apannet-", 8)) {
            str += 8;
            goto application_vnd_japannet__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'm':
    case 'M':
        goto application_vnd_m_label;

    case 'l':
    case 'L':
        /* skip to prefix 'application/vnd.lotus-' */
        if (!str_ncasecmp(str, "otus-", 5)) {
            str += 5;
            goto application_vnd_lotus__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'o':
    case 'O':
        goto application_vnd_o_label;

    case 'n':
    case 'N':
        goto application_vnd_n_label;

    case 'p':
    case 'P':
        goto application_vnd_p_label;

    case 's':
    case 'S':
        goto application_vnd_s_label;

    case 'r':
    case 'R':
        goto application_vnd_r_label;

    case 'u':
    case 'U':
        goto application_vnd_u_label;

    case 't':
    case 'T':
        goto application_vnd_t_label;

    case 'w':
    case 'W':
        goto application_vnd_w_label;

    case 'v':
    case 'V':
        goto application_vnd_v_label;

    case 'y':
    case 'Y':
        /* must be 'application/vnd.yellowriver-custom-menu' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_YELLOWRIVER_CUSTOM_MENU].name[17])) {
            return MIME_TYPE_APPLICATION_VND_YELLOWRIVER_CUSTOM_MENU;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'x':
    case 'X':
        goto application_vnd_x_label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_a_label:
    switch (*str++) {
    case 'u':
    case 'U':
        /* must be 'application/vnd.audiograph' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_AUDIOGRAPH].name[18])) {
            return MIME_TYPE_APPLICATION_VND_AUDIOGRAPH;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'c':
    case 'C':
        goto application_vnd_ac_label;

    case 'e':
    case 'E':
        /* must be 'application/vnd.aether.imp' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_AETHER_IMP].name[18])) {
            return MIME_TYPE_APPLICATION_VND_AETHER_IMP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'n':
    case 'N':
        /* skip to prefix 'application/vnd.anser-web-' */
        if (!str_ncasecmp(str, "ser-web-", 8)) {
            str += 8;
            goto application_vnd_anser_web__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_ac_label:
    switch (*str++) {
    case 'c':
    case 'C':
        /* skip to prefix 'application/vnd.accpac.simply.' */
        if (!str_ncasecmp(str, "pac.simply.", 11)) {
            str += 11;
            goto application_vnd_accpac_simply__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'u':
    case 'U':
        /* must be 'application/vnd.acucobol' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_ACUCOBOL].name[19])) {
            return MIME_TYPE_APPLICATION_VND_ACUCOBOL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_accpac_simply__label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'application/vnd.accpac.simply.aso' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_ACCPAC_SIMPLY_ASO].name[31])) {
            return MIME_TYPE_APPLICATION_VND_ACCPAC_SIMPLY_ASO;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'i':
    case 'I':
        /* must be 'application/vnd.accpac.simply.imp' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_ACCPAC_SIMPLY_IMP].name[31])) {
            return MIME_TYPE_APPLICATION_VND_ACCPAC_SIMPLY_IMP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_anser_web__label:
    switch (*str++) {
    case 'c':
    case 'C':
        /* must be 'application/vnd.anser-web-certificate-issue-initiation' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_ANSER_WEB_CERTIFICATE_ISSUE_INITIATION].name[27])) {
            return MIME_TYPE_APPLICATION_VND_ANSER_WEB_CERTIFICATE_ISSUE_INITIATION;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'f':
    case 'F':
        /* must be 'application/vnd.anser-web-funds-transfer-initiation' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_ANSER_WEB_FUNDS_TRANSFER_INITIATION].name[27])) {
            return MIME_TYPE_APPLICATION_VND_ANSER_WEB_FUNDS_TRANSFER_INITIATION;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_c_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* skip to prefix 'application/vnd.canon-' */
        if (!str_ncasecmp(str, "non-", 4)) {
            str += 4;
            goto application_vnd_canon__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'i':
    case 'I':
        /* must be 'application/vnd.cinderella' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_CINDERELLA].name[18])) {
            return MIME_TYPE_APPLICATION_VND_CINDERELLA;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'l':
    case 'L':
        /* must be 'application/vnd.claymore' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_CLAYMORE].name[18])) {
            return MIME_TYPE_APPLICATION_VND_CLAYMORE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'o':
    case 'O':
        goto application_vnd_co_label;

    case 'u':
    case 'U':
        /* skip to prefix 'application/vnd.cups-' */
        if (!str_ncasecmp(str, "ps-", 3)) {
            str += 3;
            goto application_vnd_cups__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 't':
    case 'T':
        /* must be 'application/vnd.ctc-posml' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_CTC_POSML].name[18])) {
            return MIME_TYPE_APPLICATION_VND_CTC_POSML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'y':
    case 'Y':
        /* must be 'application/vnd.cybank' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_CYBANK].name[18])) {
            return MIME_TYPE_APPLICATION_VND_CYBANK;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_canon__label:
    switch (*str++) {
    case 'c':
    case 'C':
        /* must be 'application/vnd.canon-cpdl' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_CANON_CPDL].name[23])) {
            return MIME_TYPE_APPLICATION_VND_CANON_CPDL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'l':
    case 'L':
        /* must be 'application/vnd.canon-lips' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_CANON_LIPS].name[23])) {
            return MIME_TYPE_APPLICATION_VND_CANON_LIPS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_co_label:
    switch (*str++) {
    case 's':
    case 'S':
        /* must be 'application/vnd.cosmocaller' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_COSMOCALLER].name[19])) {
            return MIME_TYPE_APPLICATION_VND_COSMOCALLER;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'm':
    case 'M':
        goto application_vnd_com_label;

    case 'n':
    case 'N':
        /* must be 'application/vnd.contact.cmsg' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_CONTACT_CMSG].name[19])) {
            return MIME_TYPE_APPLICATION_VND_CONTACT_CMSG;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_com_label:
    switch (*str++) {
    case 's':
    case 'S':
        /* must be 'application/vnd.comsocaller' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_COMSOCALLER].name[20])) {
            return MIME_TYPE_APPLICATION_VND_COMSOCALLER;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'm':
    case 'M':
        /* must be 'application/vnd.commonspace' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_COMMONSPACE].name[20])) {
            return MIME_TYPE_APPLICATION_VND_COMMONSPACE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_cups__label:
    switch (*str++) {
    case 'p':
    case 'P':
        /* must be 'application/vnd.cups-postscript' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_CUPS_POSTSCRIPT].name[22])) {
            return MIME_TYPE_APPLICATION_VND_CUPS_POSTSCRIPT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'r':
    case 'R':
        /* skip to prefix 'application/vnd.cups-ra' */
        if (!str_ncasecmp(str, "a", 1)) {
            str += 1;
            goto application_vnd_cups_ra_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_cups_ra_label:
    switch (*str++) {
    case 's':
    case 'S':
        /* must be 'application/vnd.cups-raster' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_CUPS_RASTER].name[24])) {
            return MIME_TYPE_APPLICATION_VND_CUPS_RASTER;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'w':
    case 'W':
        /* must be 'application/vnd.cups-raw' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_CUPS_RAW].name[24])) {
            return MIME_TYPE_APPLICATION_VND_CUPS_RAW;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_b_label:
    switch (*str++) {
    case 'u':
    case 'U':
        /* must be 'application/vnd.businessobjects' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_BUSINESSOBJECTS].name[18])) {
            return MIME_TYPE_APPLICATION_VND_BUSINESSOBJECTS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'm':
    case 'M':
        /* must be 'application/vnd.bmi' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_BMI].name[18])) {
            return MIME_TYPE_APPLICATION_VND_BMI;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_e_label:
    switch (*str++) {
    case 'p':
    case 'P':
        /* skip to prefix 'application/vnd.epson.' */
        if (!str_ncasecmp(str, "son.", 4)) {
            str += 4;
            goto application_vnd_epson__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'c':
    case 'C':
        goto application_vnd_ec_label;

    case 'r':
    case 'R':
        /* must be 'application/vnd.ericsson.quickcall' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_ERICSSON_QUICKCALL].name[18])) {
            return MIME_TYPE_APPLICATION_VND_ERICSSON_QUICKCALL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'u':
    case 'U':
        /* must be 'application/vnd.eudora.data' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_EUDORA_DATA].name[18])) {
            return MIME_TYPE_APPLICATION_VND_EUDORA_DATA;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'n':
    case 'N':
        /* must be 'application/vnd.enliven' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_ENLIVEN].name[18])) {
            return MIME_TYPE_APPLICATION_VND_ENLIVEN;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_epson__label:
    switch (*str++) {
    case 'q':
    case 'Q':
        /* must be 'application/vnd.epson.quickanime' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_EPSON_QUICKANIME].name[23])) {
            return MIME_TYPE_APPLICATION_VND_EPSON_QUICKANIME;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'm':
    case 'M':
        /* must be 'application/vnd.epson.msf' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_EPSON_MSF].name[23])) {
            return MIME_TYPE_APPLICATION_VND_EPSON_MSF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        goto application_vnd_epson_s_label;

    case 'e':
    case 'E':
        /* must be 'application/vnd.epson.esf' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_EPSON_ESF].name[23])) {
            return MIME_TYPE_APPLICATION_VND_EPSON_ESF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_epson_s_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'application/vnd.epson.salt' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_EPSON_SALT].name[24])) {
            return MIME_TYPE_APPLICATION_VND_EPSON_SALT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* must be 'application/vnd.epson.ssf' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_EPSON_SSF].name[24])) {
            return MIME_TYPE_APPLICATION_VND_EPSON_SSF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_ec_label:
    switch (*str++) {
    case 'd':
    case 'D':
        /* must be 'application/vnd.ecdis-update' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_ECDIS_UPDATE].name[19])) {
            return MIME_TYPE_APPLICATION_VND_ECDIS_UPDATE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'o':
    case 'O':
        /* skip to prefix 'application/vnd.ecowin.' */
        if (!str_ncasecmp(str, "win.", 4)) {
            str += 4;
            goto application_vnd_ecowin__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_ecowin__label:
    switch (*str++) {
    case 'c':
    case 'C':
        /* must be 'application/vnd.ecowin.chart' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_ECOWIN_CHART].name[24])) {
            return MIME_TYPE_APPLICATION_VND_ECOWIN_CHART;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* skip to prefix 'application/vnd.ecowin.series' */
        if (!str_ncasecmp(str, "eries", 5)) {
            str += 5;
            goto application_vnd_ecowin_series_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'f':
    case 'F':
        /* skip to prefix 'application/vnd.ecowin.file' */
        if (!str_ncasecmp(str, "ile", 3)) {
            str += 3;
            goto application_vnd_ecowin_file_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_ecowin_series_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_VND_ECOWIN_SERIES;

    case 'r':
    case 'R':
        /* must be 'application/vnd.ecowin.seriesrequest' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_ECOWIN_SERIESREQUEST].name[30])) {
            return MIME_TYPE_APPLICATION_VND_ECOWIN_SERIESREQUEST;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'u':
    case 'U':
        /* must be 'application/vnd.ecowin.seriesupdate' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_ECOWIN_SERIESUPDATE].name[30])) {
            return MIME_TYPE_APPLICATION_VND_ECOWIN_SERIESUPDATE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_ecowin_file_label:
    switch (*str++) {
    case 'r':
    case 'R':
        /* must be 'application/vnd.ecowin.filerequest' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_ECOWIN_FILEREQUEST].name[28])) {
            return MIME_TYPE_APPLICATION_VND_ECOWIN_FILEREQUEST;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'u':
    case 'U':
        /* must be 'application/vnd.ecowin.fileupdate' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_ECOWIN_FILEUPDATE].name[28])) {
            return MIME_TYPE_APPLICATION_VND_ECOWIN_FILEUPDATE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_d_label:
    switch (*str++) {
    case 'p':
    case 'P':
        /* must be 'application/vnd.dpgraph' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_DPGRAPH].name[18])) {
            return MIME_TYPE_APPLICATION_VND_DPGRAPH;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'x':
    case 'X':
        /* must be 'application/vnd.dxr' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_DXR].name[18])) {
            return MIME_TYPE_APPLICATION_VND_DXR;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'n':
    case 'N':
        /* must be 'application/vnd.dna' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_DNA].name[18])) {
            return MIME_TYPE_APPLICATION_VND_DNA;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_g_label:
    switch (*str++) {
    case 'r':
    case 'R':
        goto application_vnd_gr_label;

    case 'o':
    case 'O':
        /* skip to prefix 'application/vnd.google-earth.km' */
        if (!str_ncasecmp(str, "ogle-earth.km", 13)) {
            str += 13;
            goto application_vnd_google_earth_km_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_gr_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'application/vnd.grafeq' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_GRAFEQ].name[19])) {
            return MIME_TYPE_APPLICATION_VND_GRAFEQ;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'o':
    case 'O':
        /* skip to prefix 'application/vnd.groove-' */
        if (!str_ncasecmp(str, "ove-", 4)) {
            str += 4;
            goto application_vnd_groove__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_groove__label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'application/vnd.groove-account' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_GROOVE_ACCOUNT].name[24])) {
            return MIME_TYPE_APPLICATION_VND_GROOVE_ACCOUNT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'i':
    case 'I':
        goto application_vnd_groove_i_label;

    case 't':
    case 'T':
        /* skip to prefix 'application/vnd.groove-tool-' */
        if (!str_ncasecmp(str, "ool-", 4)) {
            str += 4;
            goto application_vnd_groove_tool__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'v':
    case 'V':
        /* must be 'application/vnd.groove-vcard' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_GROOVE_VCARD].name[24])) {
            return MIME_TYPE_APPLICATION_VND_GROOVE_VCARD;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_groove_i_label:
    switch (*str++) {
    case 'd':
    case 'D':
        /* must be 'application/vnd.groove-identity-message' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_GROOVE_IDENTITY_MESSAGE].name[25])) {
            return MIME_TYPE_APPLICATION_VND_GROOVE_IDENTITY_MESSAGE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'n':
    case 'N':
        /* must be 'application/vnd.groove-injector' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_GROOVE_INJECTOR].name[25])) {
            return MIME_TYPE_APPLICATION_VND_GROOVE_INJECTOR;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_groove_tool__label:
    switch (*str++) {
    case 'm':
    case 'M':
        /* must be 'application/vnd.groove-tool-message' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_GROOVE_TOOL_MESSAGE].name[29])) {
            return MIME_TYPE_APPLICATION_VND_GROOVE_TOOL_MESSAGE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 't':
    case 'T':
        /* must be 'application/vnd.groove-tool-template' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_GROOVE_TOOL_TEMPLATE].name[29])) {
            return MIME_TYPE_APPLICATION_VND_GROOVE_TOOL_TEMPLATE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_google_earth_km_label:
    switch (*str++) {
    case 'z':
    case 'Z':
        /* must be 'application/vnd.google-earth.kmz' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_GOOGLE_EARTH_KMZ].name[32])) {
            return MIME_TYPE_APPLICATION_VND_GOOGLE_EARTH_KMZ;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'l':
    case 'L':
        /* must be 'application/vnd.google-earth.kml+xml' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_GOOGLE_EARTH_KML_XML].name[32])) {
            return MIME_TYPE_APPLICATION_VND_GOOGLE_EARTH_KML_XML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_f_label:
    switch (*str++) {
    case 'd':
    case 'D':
        /* must be 'application/vnd.fdf' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_FDF].name[18])) {
            return MIME_TYPE_APPLICATION_VND_FDF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'f':
    case 'F':
        /* must be 'application/vnd.ffsns' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_FFSNS].name[18])) {
            return MIME_TYPE_APPLICATION_VND_FFSNS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'l':
    case 'L':
        /* must be 'application/vnd.flographit' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_FLOGRAPHIT].name[18])) {
            return MIME_TYPE_APPLICATION_VND_FLOGRAPHIT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* must be 'application/vnd.fsc.weblaunch' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_FSC_WEBLAUNCH].name[18])) {
            return MIME_TYPE_APPLICATION_VND_FSC_WEBLAUNCH;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'r':
    case 'R':
        /* must be 'application/vnd.framemaker' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_FRAMEMAKER].name[18])) {
            return MIME_TYPE_APPLICATION_VND_FRAMEMAKER;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'u':
    case 'U':
        goto application_vnd_fu_label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_fu_label:
    switch (*str++) {
    case 'j':
    case 'J':
        /* skip to prefix 'application/vnd.fuji' */
        if (!str_ncasecmp(str, "i", 1)) {
            str += 1;
            goto application_vnd_fuji_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 't':
    case 'T':
        /* must be 'application/vnd.fut-misnet' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_FUT_MISNET].name[19])) {
            return MIME_TYPE_APPLICATION_VND_FUT_MISNET;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_fuji_label:
    switch (*str++) {
    case 'x':
    case 'X':
        /* skip to prefix 'application/vnd.fujixerox.d' */
        if (!str_ncasecmp(str, "erox.d", 6)) {
            str += 6;
            goto application_vnd_fujixerox_d_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 't':
    case 'T':
        /* skip to prefix 'application/vnd.fujitsu.oasys' */
        if (!str_ncasecmp(str, "su.oasys", 8)) {
            str += 8;
            goto application_vnd_fujitsu_oasys_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_fujixerox_d_label:
    switch (*str++) {
    case 'd':
    case 'D':
        /* must be 'application/vnd.fujixerox.ddd' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_FUJIXEROX_DDD].name[28])) {
            return MIME_TYPE_APPLICATION_VND_FUJIXEROX_DDD;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'o':
    case 'O':
        /* skip to prefix 'application/vnd.fujixerox.docuworks' */
        if (!str_ncasecmp(str, "cuworks", 7)) {
            str += 7;
            goto application_vnd_fujixerox_docuworks_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_fujixerox_docuworks_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_VND_FUJIXEROX_DOCUWORKS;

    case '.':
        /* must be 'application/vnd.fujixerox.docuworks.binder' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_FUJIXEROX_DOCUWORKS_BINDER].name[36])) {
            return MIME_TYPE_APPLICATION_VND_FUJIXEROX_DOCUWORKS_BINDER;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_fujitsu_oasys_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_VND_FUJITSU_OASYS;

    case 'p':
    case 'P':
        /* must be 'application/vnd.fujitsu.oasysprs' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_FUJITSU_OASYSPRS].name[30])) {
            return MIME_TYPE_APPLICATION_VND_FUJITSU_OASYSPRS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case '3':
        /* must be 'application/vnd.fujitsu.oasys3' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_FUJITSU_OASYS3].name[30])) {
            return MIME_TYPE_APPLICATION_VND_FUJITSU_OASYS3;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case '2':
        /* must be 'application/vnd.fujitsu.oasys2' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_FUJITSU_OASYS2].name[30])) {
            return MIME_TYPE_APPLICATION_VND_FUJITSU_OASYS2;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'g':
    case 'G':
        /* must be 'application/vnd.fujitsu.oasysgp' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_FUJITSU_OASYSGP].name[30])) {
            return MIME_TYPE_APPLICATION_VND_FUJITSU_OASYSGP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_i_label:
    switch (*str++) {
    case 'r':
    case 'R':
        /* must be 'application/vnd.irepository.package+xml' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_IREPOSITORY_PACKAGE_XML].name[18])) {
            return MIME_TYPE_APPLICATION_VND_IREPOSITORY_PACKAGE_XML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'b':
    case 'B':
        /* skip to prefix 'application/vnd.ibm.' */
        if (!str_ncasecmp(str, "m.", 2)) {
            str += 2;
            goto application_vnd_ibm__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 's':
    case 'S':
        /* must be 'application/vnd.is-xpr' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_IS_XPR].name[18])) {
            return MIME_TYPE_APPLICATION_VND_IS_XPR;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'n':
    case 'N':
        goto application_vnd_in_label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_ibm__label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'application/vnd.ibm.afplinedata' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_IBM_AFPLINEDATA].name[21])) {
            return MIME_TYPE_APPLICATION_VND_IBM_AFPLINEDATA;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'm':
    case 'M':
        goto application_vnd_ibm_m_label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_ibm_m_label:
    switch (*str++) {
    case 'i':
    case 'I':
        /* must be 'application/vnd.ibm.minipay' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_IBM_MINIPAY].name[22])) {
            return MIME_TYPE_APPLICATION_VND_IBM_MINIPAY;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'o':
    case 'O':
        /* must be 'application/vnd.ibm.modcap' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_IBM_MODCAP].name[22])) {
            return MIME_TYPE_APPLICATION_VND_IBM_MODCAP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_in_label:
    switch (*str++) {
    case 't':
    case 'T':
        goto application_vnd_int_label;

    case 'f':
    case 'F':
        /* must be 'application/vnd.informix-visionary' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_INFORMIX_VISIONARY].name[19])) {
            return MIME_TYPE_APPLICATION_VND_INFORMIX_VISIONARY;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_int_label:
    switch (*str++) {
    case 'u':
    case 'U':
        /* skip to prefix 'application/vnd.intu.q' */
        if (!str_ncasecmp(str, ".q", 2)) {
            str += 2;
            goto application_vnd_intu_q_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'e':
    case 'E':
        /* skip to prefix 'application/vnd.inter' */
        if (!str_ncasecmp(str, "r", 1)) {
            str += 1;
            goto application_vnd_inter_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_intu_q_label:
    switch (*str++) {
    case 'b':
    case 'B':
        /* must be 'application/vnd.intu.qbo' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_INTU_QBO].name[23])) {
            return MIME_TYPE_APPLICATION_VND_INTU_QBO;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'f':
    case 'F':
        /* must be 'application/vnd.intu.qfx' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_INTU_QFX].name[23])) {
            return MIME_TYPE_APPLICATION_VND_INTU_QFX;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_inter_label:
    switch (*str++) {
    case 'c':
    case 'C':
        /* must be 'application/vnd.intercon.formnet' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_INTERCON_FORMNET].name[22])) {
            return MIME_TYPE_APPLICATION_VND_INTERCON_FORMNET;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 't':
    case 'T':
        /* skip to prefix 'application/vnd.intertrust.' */
        if (!str_ncasecmp(str, "rust.", 5)) {
            str += 5;
            goto application_vnd_intertrust__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_intertrust__label:
    switch (*str++) {
    case 'd':
    case 'D':
        /* must be 'application/vnd.intertrust.digibox' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_INTERTRUST_DIGIBOX].name[28])) {
            return MIME_TYPE_APPLICATION_VND_INTERTRUST_DIGIBOX;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'n':
    case 'N':
        /* must be 'application/vnd.intertrust.nncp' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_INTERTRUST_NNCP].name[28])) {
            return MIME_TYPE_APPLICATION_VND_INTERTRUST_NNCP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_h_label:
    switch (*str++) {
    case 'h':
    case 'H':
        /* must be 'application/vnd.hhe.lesson-player' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_HHE_LESSON_PLAYER].name[18])) {
            return MIME_TYPE_APPLICATION_VND_HHE_LESSON_PLAYER;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'z':
    case 'Z':
        /* must be 'application/vnd.hzn-3d-crossword' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_HZN_3D_CROSSWORD].name[18])) {
            return MIME_TYPE_APPLICATION_VND_HZN_3D_CROSSWORD;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 't':
    case 'T':
        /* must be 'application/vnd.httphone' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_HTTPHONE].name[18])) {
            return MIME_TYPE_APPLICATION_VND_HTTPHONE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'p':
    case 'P':
        /* skip to prefix 'application/vnd.hp-' */
        if (!str_ncasecmp(str, "-", 1)) {
            str += 1;
            goto application_vnd_hp__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_hp__label:
    switch (*str++) {
    case 'h':
    case 'H':
        /* skip to prefix 'application/vnd.hp-hp' */
        if (!str_ncasecmp(str, "p", 1)) {
            str += 1;
            goto application_vnd_hp_hp_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'p':
    case 'P':
        /* skip to prefix 'application/vnd.hp-pcl' */
        if (!str_ncasecmp(str, "cl", 2)) {
            str += 2;
            goto application_vnd_hp_pcl_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_hp_hp_label:
    switch (*str++) {
    case 'i':
    case 'I':
        /* must be 'application/vnd.hp-hpid' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_HP_HPID].name[22])) {
            return MIME_TYPE_APPLICATION_VND_HP_HPID;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* must be 'application/vnd.hp-hps' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_HP_HPS].name[22])) {
            return MIME_TYPE_APPLICATION_VND_HP_HPS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'g':
    case 'G':
        /* must be 'application/vnd.hp-hpgl' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_HP_HPGL].name[22])) {
            return MIME_TYPE_APPLICATION_VND_HP_HPGL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_hp_pcl_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_VND_HP_PCL;

    case 'x':
    case 'X':
        /* must be 'application/vnd.hp-pclxl' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_HP_PCLXL].name[23])) {
            return MIME_TYPE_APPLICATION_VND_HP_PCLXL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_japannet__label:
    switch (*str++) {
    case 'd':
    case 'D':
        /* must be 'application/vnd.japannet-directory-service' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_JAPANNET_DIRECTORY_SERVICE].name[26])) {
            return MIME_TYPE_APPLICATION_VND_JAPANNET_DIRECTORY_SERVICE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'j':
    case 'J':
        /* must be 'application/vnd.japannet-jpnstore-wakeup' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_JAPANNET_JPNSTORE_WAKEUP].name[26])) {
            return MIME_TYPE_APPLICATION_VND_JAPANNET_JPNSTORE_WAKEUP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'p':
    case 'P':
        /* must be 'application/vnd.japannet-payment-wakeup' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_JAPANNET_PAYMENT_WAKEUP].name[26])) {
            return MIME_TYPE_APPLICATION_VND_JAPANNET_PAYMENT_WAKEUP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* must be 'application/vnd.japannet-setstore-wakeup' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_JAPANNET_SETSTORE_WAKEUP].name[26])) {
            return MIME_TYPE_APPLICATION_VND_JAPANNET_SETSTORE_WAKEUP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'r':
    case 'R':
        /* skip to prefix 'application/vnd.japannet-registration' */
        if (!str_ncasecmp(str, "egistration", 11)) {
            str += 11;
            goto application_vnd_japannet_registration_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'v':
    case 'V':
        /* skip to prefix 'application/vnd.japannet-verification' */
        if (!str_ncasecmp(str, "erification", 11)) {
            str += 11;
            goto application_vnd_japannet_verification_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_japannet_registration_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_VND_JAPANNET_REGISTRATION;

    case '-':
        /* must be 'application/vnd.japannet-registration-wakeup' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_JAPANNET_REGISTRATION_WAKEUP].name[38])) {
            return MIME_TYPE_APPLICATION_VND_JAPANNET_REGISTRATION_WAKEUP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_japannet_verification_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_VND_JAPANNET_VERIFICATION;

    case '-':
        /* must be 'application/vnd.japannet-verification-wakeup' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_JAPANNET_VERIFICATION_WAKEUP].name[38])) {
            return MIME_TYPE_APPLICATION_VND_JAPANNET_VERIFICATION_WAKEUP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_m_label:
    switch (*str++) {
    case 'c':
    case 'C':
        /* must be 'application/vnd.mcd' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MCD].name[18])) {
            return MIME_TYPE_APPLICATION_VND_MCD;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'e':
    case 'E':
        goto application_vnd_me_label;

    case 'i':
    case 'I':
        goto application_vnd_mi_label;

    case 'o':
    case 'O':
        goto application_vnd_mo_label;

    case 's':
    case 'S':
        goto application_vnd_ms_label;

    case 'u':
    case 'U':
        /* skip to prefix 'application/vnd.music' */
        if (!str_ncasecmp(str, "sic", 3)) {
            str += 3;
            goto application_vnd_music_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_me_label:
    switch (*str++) {
    case 'r':
    case 'R':
        /* must be 'application/vnd.meridian-slingshot' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MERIDIAN_SLINGSHOT].name[19])) {
            return MIME_TYPE_APPLICATION_VND_MERIDIAN_SLINGSHOT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'd':
    case 'D':
        /* must be 'application/vnd.mediastation.cdkey' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MEDIASTATION_CDKEY].name[19])) {
            return MIME_TYPE_APPLICATION_VND_MEDIASTATION_CDKEY;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_mi_label:
    switch (*str++) {
    case 'n':
    case 'N':
        /* must be 'application/vnd.minisoft-hp3000-save' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MINISOFT_HP3000_SAVE].name[19])) {
            return MIME_TYPE_APPLICATION_VND_MINISOFT_HP3000_SAVE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 't':
    case 'T':
        /* must be 'application/vnd.mitsubishi.misty-guard.trustweb' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MITSUBISHI_MISTY_GUARD_TRUSTWEB].name[19])) {
            return MIME_TYPE_APPLICATION_VND_MITSUBISHI_MISTY_GUARD_TRUSTWEB;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'f':
    case 'F':
        /* must be 'application/vnd.mif' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MIF].name[19])) {
            return MIME_TYPE_APPLICATION_VND_MIF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_mo_label:
    switch (*str++) {
    case 'b':
    case 'B':
        /* skip to prefix 'application/vnd.mobius.' */
        if (!str_ncasecmp(str, "ius.", 4)) {
            str += 4;
            goto application_vnd_mobius__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 't':
    case 'T':
        /* skip to prefix 'application/vnd.motorola.flexsuite' */
        if (!str_ncasecmp(str, "orola.flexsuite", 15)) {
            str += 15;
            goto application_vnd_motorola_flexsuite_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'z':
    case 'Z':
        /* must be 'application/vnd.mozilla.xul+xml' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MOZILLA_XUL_XML].name[19])) {
            return MIME_TYPE_APPLICATION_VND_MOZILLA_XUL_XML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_mobius__label:
    switch (*str++) {
    case 'p':
    case 'P':
        /* must be 'application/vnd.mobius.plc' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MOBIUS_PLC].name[24])) {
            return MIME_TYPE_APPLICATION_VND_MOBIUS_PLC;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'm':
    case 'M':
        goto application_vnd_mobius_m_label;

    case 'd':
    case 'D':
        goto application_vnd_mobius_d_label;

    case 't':
    case 'T':
        /* must be 'application/vnd.mobius.txf' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MOBIUS_TXF].name[24])) {
            return MIME_TYPE_APPLICATION_VND_MOBIUS_TXF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_mobius_m_label:
    switch (*str++) {
    case 'q':
    case 'Q':
        /* must be 'application/vnd.mobius.mqy' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MOBIUS_MQY].name[25])) {
            return MIME_TYPE_APPLICATION_VND_MOBIUS_MQY;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* must be 'application/vnd.mobius.msl' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MOBIUS_MSL].name[25])) {
            return MIME_TYPE_APPLICATION_VND_MOBIUS_MSL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'b':
    case 'B':
        /* must be 'application/vnd.mobius.mbk' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MOBIUS_MBK].name[25])) {
            return MIME_TYPE_APPLICATION_VND_MOBIUS_MBK;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_mobius_d_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'application/vnd.mobius.daf' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MOBIUS_DAF].name[25])) {
            return MIME_TYPE_APPLICATION_VND_MOBIUS_DAF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'i':
    case 'I':
        /* must be 'application/vnd.mobius.dis' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MOBIUS_DIS].name[25])) {
            return MIME_TYPE_APPLICATION_VND_MOBIUS_DIS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_motorola_flexsuite_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_VND_MOTOROLA_FLEXSUITE;

    case '.':
        goto application_vnd_motorola_flexsuite__label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_motorola_flexsuite__label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'application/vnd.motorola.flexsuite.adsi' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MOTOROLA_FLEXSUITE_ADSI].name[36])) {
            return MIME_TYPE_APPLICATION_VND_MOTOROLA_FLEXSUITE_ADSI;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'g':
    case 'G':
        /* must be 'application/vnd.motorola.flexsuite.gotap' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MOTOROLA_FLEXSUITE_GOTAP].name[36])) {
            return MIME_TYPE_APPLICATION_VND_MOTOROLA_FLEXSUITE_GOTAP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'f':
    case 'F':
        /* must be 'application/vnd.motorola.flexsuite.fis' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MOTOROLA_FLEXSUITE_FIS].name[36])) {
            return MIME_TYPE_APPLICATION_VND_MOTOROLA_FLEXSUITE_FIS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'k':
    case 'K':
        /* must be 'application/vnd.motorola.flexsuite.kmr' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MOTOROLA_FLEXSUITE_KMR].name[36])) {
            return MIME_TYPE_APPLICATION_VND_MOTOROLA_FLEXSUITE_KMR;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 't':
    case 'T':
        /* must be 'application/vnd.motorola.flexsuite.ttc' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MOTOROLA_FLEXSUITE_TTC].name[36])) {
            return MIME_TYPE_APPLICATION_VND_MOTOROLA_FLEXSUITE_TTC;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'w':
    case 'W':
        /* must be 'application/vnd.motorola.flexsuite.wem' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MOTOROLA_FLEXSUITE_WEM].name[36])) {
            return MIME_TYPE_APPLICATION_VND_MOTOROLA_FLEXSUITE_WEM;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_ms_label:
    switch (*str++) {
    case 'i':
    case 'I':
        /* must be 'application/vnd.msign' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MSIGN].name[19])) {
            return MIME_TYPE_APPLICATION_VND_MSIGN;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'e':
    case 'E':
        /* must be 'application/vnd.mseq' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MSEQ].name[19])) {
            return MIME_TYPE_APPLICATION_VND_MSEQ;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case '-':
        goto application_vnd_ms__label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_ms__label:
    switch (*str++) {
    case 'a':
    case 'A':
        goto application_vnd_ms_a_label;

    case 'e':
    case 'E':
        /* must be 'application/vnd.ms-excel' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MS_EXCEL].name[20])) {
            return MIME_TYPE_APPLICATION_VND_MS_EXCEL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'l':
    case 'L':
        /* must be 'application/vnd.ms-lrm' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MS_LRM].name[20])) {
            return MIME_TYPE_APPLICATION_VND_MS_LRM;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'p':
    case 'P':
        goto application_vnd_ms_p_label;

    case 't':
    case 'T':
        /* must be 'application/vnd.ms-tnef' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MS_TNEF].name[20])) {
            return MIME_TYPE_APPLICATION_VND_MS_TNEF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'w':
    case 'W':
        /* must be 'application/vnd.ms-works' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MS_WORKS].name[20])) {
            return MIME_TYPE_APPLICATION_VND_MS_WORKS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_ms_a_label:
    switch (*str++) {
    case 's':
    case 'S':
        /* must be 'application/vnd.ms-asf' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MS_ASF].name[21])) {
            return MIME_TYPE_APPLICATION_VND_MS_ASF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'r':
    case 'R':
        /* must be 'application/vnd.ms-artgalry' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MS_ARTGALRY].name[21])) {
            return MIME_TYPE_APPLICATION_VND_MS_ARTGALRY;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_ms_p_label:
    switch (*str++) {
    case 'k':
    case 'K':
        /* skip to prefix 'application/vnd.ms-pki.s' */
        if (!str_ncasecmp(str, "i.s", 3)) {
            str += 3;
            goto application_vnd_ms_pki_s_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'r':
    case 'R':
        /* must be 'application/vnd.ms-project' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MS_PROJECT].name[21])) {
            return MIME_TYPE_APPLICATION_VND_MS_PROJECT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'o':
    case 'O':
        /* must be 'application/vnd.ms-powerpoint' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MS_POWERPOINT].name[21])) {
            return MIME_TYPE_APPLICATION_VND_MS_POWERPOINT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_ms_pki_s_label:
    switch (*str++) {
    case 'e':
    case 'E':
        /* must be 'application/vnd.ms-pki.seccat' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MS_PKI_SECCAT].name[25])) {
            return MIME_TYPE_APPLICATION_VND_MS_PKI_SECCAT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 't':
    case 'T':
        /* must be 'application/vnd.ms-pki.stl' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MS_PKI_STL].name[25])) {
            return MIME_TYPE_APPLICATION_VND_MS_PKI_STL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_music_label:
    switch (*str++) {
    case 'i':
    case 'I':
        /* must be 'application/vnd.musician' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MUSICIAN].name[22])) {
            return MIME_TYPE_APPLICATION_VND_MUSICIAN;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case '-':
        /* must be 'application/vnd.music-niff' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_MUSIC_NIFF].name[22])) {
            return MIME_TYPE_APPLICATION_VND_MUSIC_NIFF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_lotus__label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'application/vnd.lotus-approach' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_LOTUS_APPROACH].name[23])) {
            return MIME_TYPE_APPLICATION_VND_LOTUS_APPROACH;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'f':
    case 'F':
        /* must be 'application/vnd.lotus-freelance' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_LOTUS_FREELANCE].name[23])) {
            return MIME_TYPE_APPLICATION_VND_LOTUS_FREELANCE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'o':
    case 'O':
        /* must be 'application/vnd.lotus-organizer' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_LOTUS_ORGANIZER].name[23])) {
            return MIME_TYPE_APPLICATION_VND_LOTUS_ORGANIZER;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'n':
    case 'N':
        /* must be 'application/vnd.lotus-notes' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_LOTUS_NOTES].name[23])) {
            return MIME_TYPE_APPLICATION_VND_LOTUS_NOTES;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case '1':
        /* must be 'application/vnd.lotus-1-2-3' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_LOTUS_1_2_3].name[23])) {
            return MIME_TYPE_APPLICATION_VND_LOTUS_1_2_3;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* must be 'application/vnd.lotus-screencam' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_LOTUS_SCREENCAM].name[23])) {
            return MIME_TYPE_APPLICATION_VND_LOTUS_SCREENCAM;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'w':
    case 'W':
        /* must be 'application/vnd.lotus-wordpro' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_LOTUS_WORDPRO].name[23])) {
            return MIME_TYPE_APPLICATION_VND_LOTUS_WORDPRO;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_o_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* skip to prefix 'application/vnd.oasis.opendocument.' */
        if (!str_ncasecmp(str, "sis.opendocument.", 17)) {
            str += 17;
            goto application_vnd_oasis_opendocument__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 's':
    case 'S':
        /* must be 'application/vnd.osa.netdeploy' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_OSA_NETDEPLOY].name[18])) {
            return MIME_TYPE_APPLICATION_VND_OSA_NETDEPLOY;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_oasis_opendocument__label:
    switch (*str++) {
    case 'c':
    case 'C':
        /* must be 'application/vnd.oasis.opendocument.chart' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_CHART].name[36])) {
            return MIME_TYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_CHART;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'd':
    case 'D':
        /* must be 'application/vnd.oasis.opendocument.database' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_DATABASE].name[36])) {
            return MIME_TYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_DATABASE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'g':
    case 'G':
        /* skip to prefix 'application/vnd.oasis.opendocument.graphics' */
        if (!str_ncasecmp(str, "raphics", 7)) {
            str += 7;
            goto application_vnd_oasis_opendocument_graphics_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'f':
    case 'F':
        /* must be 'application/vnd.oasis.opendocument.formula' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_FORMULA].name[36])) {
            return MIME_TYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_FORMULA;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'i':
    case 'I':
        /* must be 'application/vnd.oasis.opendocument.image' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_IMAGE].name[36])) {
            return MIME_TYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_IMAGE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'p':
    case 'P':
        /* skip to prefix 'application/vnd.oasis.opendocument.presentation' */
        if (!str_ncasecmp(str, "resentation", 11)) {
            str += 11;
            goto application_vnd_oasis_opendocument_presentation_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 's':
    case 'S':
        /* skip to prefix 'application/vnd.oasis.opendocument.spreadsheet' */
        if (!str_ncasecmp(str, "preadsheet", 10)) {
            str += 10;
            goto application_vnd_oasis_opendocument_spreadsheet_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 't':
    case 'T':
        /* skip to prefix 'application/vnd.oasis.opendocument.text' */
        if (!str_ncasecmp(str, "ext", 3)) {
            str += 3;
            goto application_vnd_oasis_opendocument_text_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_oasis_opendocument_graphics_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_GRAPHICS;

    case '-':
        /* must be 'application/vnd.oasis.opendocument.graphics-template' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_GRAPHICS_TEMPLATE].name[44])) {
            return MIME_TYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_GRAPHICS_TEMPLATE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_oasis_opendocument_presentation_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_PRESENTATION;

    case '-':
        /* must be 'application/vnd.oasis.opendocument.presentation-template' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_PRESENTATION_TEMPLATE].name[48])) {
            return MIME_TYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_PRESENTATION_TEMPLATE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_oasis_opendocument_spreadsheet_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_SPREADSHEET;

    case '-':
        /* must be 'application/vnd.oasis.opendocument.spreadsheet-template' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_SPREADSHEET_TEMPLATE].name[47])) {
            return MIME_TYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_SPREADSHEET_TEMPLATE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_oasis_opendocument_text_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_TEXT;

    case '-':
        goto application_vnd_oasis_opendocument_text__label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_oasis_opendocument_text__label:
    switch (*str++) {
    case 'm':
    case 'M':
        /* must be 'application/vnd.oasis.opendocument.text-master' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_TEXT_MASTER].name[41])) {
            return MIME_TYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_TEXT_MASTER;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 't':
    case 'T':
        /* must be 'application/vnd.oasis.opendocument.text-template' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_TEXT_TEMPLATE].name[41])) {
            return MIME_TYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_TEXT_TEMPLATE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'w':
    case 'W':
        /* must be 'application/vnd.oasis.opendocument.text-web' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_TEXT_WEB].name[41])) {
            return MIME_TYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_TEXT_WEB;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_n_label:
    switch (*str++) {
    case 'e':
    case 'E':
        /* must be 'application/vnd.netfpx' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_NETFPX].name[18])) {
            return MIME_TYPE_APPLICATION_VND_NETFPX;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'o':
    case 'O':
        goto application_vnd_no_label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_no_label:
    switch (*str++) {
    case 'b':
    case 'B':
        /* skip to prefix 'application/vnd.noblenet-' */
        if (!str_ncasecmp(str, "lenet-", 6)) {
            str += 6;
            goto application_vnd_noblenet__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'v':
    case 'V':
        /* skip to prefix 'application/vnd.novadigm.e' */
        if (!str_ncasecmp(str, "adigm.e", 7)) {
            str += 7;
            goto application_vnd_novadigm_e_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_noblenet__label:
    switch (*str++) {
    case 's':
    case 'S':
        /* must be 'application/vnd.noblenet-sealer' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_NOBLENET_SEALER].name[26])) {
            return MIME_TYPE_APPLICATION_VND_NOBLENET_SEALER;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'd':
    case 'D':
        /* must be 'application/vnd.noblenet-directory' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_NOBLENET_DIRECTORY].name[26])) {
            return MIME_TYPE_APPLICATION_VND_NOBLENET_DIRECTORY;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'w':
    case 'W':
        /* must be 'application/vnd.noblenet-web' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_NOBLENET_WEB].name[26])) {
            return MIME_TYPE_APPLICATION_VND_NOBLENET_WEB;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_novadigm_e_label:
    switch (*str++) {
    case 'x':
    case 'X':
        /* must be 'application/vnd.novadigm.ext' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_NOVADIGM_EXT].name[27])) {
            return MIME_TYPE_APPLICATION_VND_NOVADIGM_EXT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'd':
    case 'D':
        goto application_vnd_novadigm_ed_label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_novadigm_ed_label:
    switch (*str++) {
    case 'x':
    case 'X':
        /* must be 'application/vnd.novadigm.edx' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_NOVADIGM_EDX].name[28])) {
            return MIME_TYPE_APPLICATION_VND_NOVADIGM_EDX;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'm':
    case 'M':
        /* must be 'application/vnd.novadigm.edm' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_NOVADIGM_EDM].name[28])) {
            return MIME_TYPE_APPLICATION_VND_NOVADIGM_EDM;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_p_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'application/vnd.palm' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_PALM].name[18])) {
            return MIME_TYPE_APPLICATION_VND_PALM;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'g':
    case 'G':
        /* skip to prefix 'application/vnd.pg.' */
        if (!str_ncasecmp(str, ".", 1)) {
            str += 1;
            goto application_vnd_pg__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'o':
    case 'O':
        /* skip to prefix 'application/vnd.powerbuilder' */
        if (!str_ncasecmp(str, "werbuilder", 10)) {
            str += 10;
            goto application_vnd_powerbuilder_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'r':
    case 'R':
        /* must be 'application/vnd.previewsystems.box' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_PREVIEWSYSTEMS_BOX].name[18])) {
            return MIME_TYPE_APPLICATION_VND_PREVIEWSYSTEMS_BOX;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'u':
    case 'U':
        /* must be 'application/vnd.publishare-delta-tree' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_PUBLISHARE_DELTA_TREE].name[18])) {
            return MIME_TYPE_APPLICATION_VND_PUBLISHARE_DELTA_TREE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'w':
    case 'W':
        /* must be 'application/vnd.pwg-xhtml-print+xml' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_PWG_XHTML_PRINT_XML].name[18])) {
            return MIME_TYPE_APPLICATION_VND_PWG_XHTML_PRINT_XML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'v':
    case 'V':
        /* must be 'application/vnd.pvi.ptid1' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_PVI_PTID1].name[18])) {
            return MIME_TYPE_APPLICATION_VND_PVI_PTID1;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_pg__label:
    switch (*str++) {
    case 'o':
    case 'O':
        /* must be 'application/vnd.pg.osasli' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_PG_OSASLI].name[20])) {
            return MIME_TYPE_APPLICATION_VND_PG_OSASLI;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'f':
    case 'F':
        /* must be 'application/vnd.pg.format' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_PG_FORMAT].name[20])) {
            return MIME_TYPE_APPLICATION_VND_PG_FORMAT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_powerbuilder_label:
    switch (*str++) {
    case '7':
        goto application_vnd_powerbuilder7_label;

    case '6':
        goto application_vnd_powerbuilder6_label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_powerbuilder7_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_VND_POWERBUILDER7;

    case '5':
        goto application_vnd_powerbuilder75_label;

    case '-':
        /* must be 'application/vnd.powerbuilder7-s' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_POWERBUILDER7_S].name[30])) {
            return MIME_TYPE_APPLICATION_VND_POWERBUILDER7_S;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_powerbuilder75_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_VND_POWERBUILDER75;

    case '-':
        /* must be 'application/vnd.powerbuilder75-s' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_POWERBUILDER75_S].name[31])) {
            return MIME_TYPE_APPLICATION_VND_POWERBUILDER75_S;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_powerbuilder6_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_VND_POWERBUILDER6;

    case '-':
        /* must be 'application/vnd.powerbuilder6-s' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_POWERBUILDER6_S].name[30])) {
            return MIME_TYPE_APPLICATION_VND_POWERBUILDER6_S;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_s_label:
    switch (*str++) {
    case 'e':
    case 'E':
        /* must be 'application/vnd.seemail' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_SEEMAIL].name[18])) {
            return MIME_TYPE_APPLICATION_VND_SEEMAIL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'h':
    case 'H':
        /* skip to prefix 'application/vnd.shana.informed.' */
        if (!str_ncasecmp(str, "ana.informed.", 13)) {
            str += 13;
            goto application_vnd_shana_informed__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'm':
    case 'M':
        /* must be 'application/vnd.smaf' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_SMAF].name[18])) {
            return MIME_TYPE_APPLICATION_VND_SMAF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* skip to prefix 'application/vnd.sss-' */
        if (!str_ncasecmp(str, "s-", 2)) {
            str += 2;
            goto application_vnd_sss__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case '3':
        /* must be 'application/vnd.s3sms' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_S3SMS].name[18])) {
            return MIME_TYPE_APPLICATION_VND_S3SMS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'u':
    case 'U':
        /* skip to prefix 'application/vnd.sun.xml.' */
        if (!str_ncasecmp(str, "n.xml.", 6)) {
            str += 6;
            goto application_vnd_sun_xml__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 't':
    case 'T':
        goto application_vnd_st_label;

    case 'w':
    case 'W':
        /* must be 'application/vnd.swiftview-ics' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_SWIFTVIEW_ICS].name[18])) {
            return MIME_TYPE_APPLICATION_VND_SWIFTVIEW_ICS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'v':
    case 'V':
        /* must be 'application/vnd.svd' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_SVD].name[18])) {
            return MIME_TYPE_APPLICATION_VND_SVD;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'y':
    case 'Y':
        /* must be 'application/vnd.symbian.install' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_SYMBIAN_INSTALL].name[18])) {
            return MIME_TYPE_APPLICATION_VND_SYMBIAN_INSTALL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_shana_informed__label:
    switch (*str++) {
    case 'i':
    case 'I':
        /* must be 'application/vnd.shana.informed.interchange' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_SHANA_INFORMED_INTERCHANGE].name[32])) {
            return MIME_TYPE_APPLICATION_VND_SHANA_INFORMED_INTERCHANGE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'p':
    case 'P':
        /* must be 'application/vnd.shana.informed.package' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_SHANA_INFORMED_PACKAGE].name[32])) {
            return MIME_TYPE_APPLICATION_VND_SHANA_INFORMED_PACKAGE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'f':
    case 'F':
        /* skip to prefix 'application/vnd.shana.informed.form' */
        if (!str_ncasecmp(str, "orm", 3)) {
            str += 3;
            goto application_vnd_shana_informed_form_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_shana_informed_form_label:
    switch (*str++) {
    case 'd':
    case 'D':
        /* must be 'application/vnd.shana.informed.formdata' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_SHANA_INFORMED_FORMDATA].name[36])) {
            return MIME_TYPE_APPLICATION_VND_SHANA_INFORMED_FORMDATA;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 't':
    case 'T':
        /* must be 'application/vnd.shana.informed.formtemplate' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_SHANA_INFORMED_FORMTEMPLATE].name[36])) {
            return MIME_TYPE_APPLICATION_VND_SHANA_INFORMED_FORMTEMPLATE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_sss__label:
    switch (*str++) {
    case 'c':
    case 'C':
        /* must be 'application/vnd.sss-cod' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_SSS_COD].name[21])) {
            return MIME_TYPE_APPLICATION_VND_SSS_COD;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'd':
    case 'D':
        /* must be 'application/vnd.sss-dtf' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_SSS_DTF].name[21])) {
            return MIME_TYPE_APPLICATION_VND_SSS_DTF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'n':
    case 'N':
        /* must be 'application/vnd.sss-ntf' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_SSS_NTF].name[21])) {
            return MIME_TYPE_APPLICATION_VND_SSS_NTF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_sun_xml__label:
    switch (*str++) {
    case 'i':
    case 'I':
        /* skip to prefix 'application/vnd.sun.xml.impress' */
        if (!str_ncasecmp(str, "mpress", 6)) {
            str += 6;
            goto application_vnd_sun_xml_impress_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'c':
    case 'C':
        /* skip to prefix 'application/vnd.sun.xml.calc' */
        if (!str_ncasecmp(str, "alc", 3)) {
            str += 3;
            goto application_vnd_sun_xml_calc_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'm':
    case 'M':
        /* must be 'application/vnd.sun.xml.math' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_SUN_XML_MATH].name[25])) {
            return MIME_TYPE_APPLICATION_VND_SUN_XML_MATH;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'd':
    case 'D':
        /* skip to prefix 'application/vnd.sun.xml.draw' */
        if (!str_ncasecmp(str, "raw", 3)) {
            str += 3;
            goto application_vnd_sun_xml_draw_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'w':
    case 'W':
        /* skip to prefix 'application/vnd.sun.xml.writer' */
        if (!str_ncasecmp(str, "riter", 5)) {
            str += 5;
            goto application_vnd_sun_xml_writer_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_sun_xml_impress_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_VND_SUN_XML_IMPRESS;

    case '.':
        /* must be 'application/vnd.sun.xml.impress.template' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_SUN_XML_IMPRESS_TEMPLATE].name[32])) {
            return MIME_TYPE_APPLICATION_VND_SUN_XML_IMPRESS_TEMPLATE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_sun_xml_calc_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_VND_SUN_XML_CALC;

    case '.':
        /* must be 'application/vnd.sun.xml.calc.template' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_SUN_XML_CALC_TEMPLATE].name[29])) {
            return MIME_TYPE_APPLICATION_VND_SUN_XML_CALC_TEMPLATE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_sun_xml_draw_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_VND_SUN_XML_DRAW;

    case '.':
        /* must be 'application/vnd.sun.xml.draw.template' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_SUN_XML_DRAW_TEMPLATE].name[29])) {
            return MIME_TYPE_APPLICATION_VND_SUN_XML_DRAW_TEMPLATE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_sun_xml_writer_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_VND_SUN_XML_WRITER;

    case '.':
        goto application_vnd_sun_xml_writer__label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_sun_xml_writer__label:
    switch (*str++) {
    case 't':
    case 'T':
        /* must be 'application/vnd.sun.xml.writer.template' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_SUN_XML_WRITER_TEMPLATE].name[32])) {
            return MIME_TYPE_APPLICATION_VND_SUN_XML_WRITER_TEMPLATE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'g':
    case 'G':
        /* must be 'application/vnd.sun.xml.writer.global' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_SUN_XML_WRITER_GLOBAL].name[32])) {
            return MIME_TYPE_APPLICATION_VND_SUN_XML_WRITER_GLOBAL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_st_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* skip to prefix 'application/vnd.stardivision.' */
        if (!str_ncasecmp(str, "rdivision.", 10)) {
            str += 10;
            goto application_vnd_stardivision__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'r':
    case 'R':
        /* must be 'application/vnd.street-stream' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_STREET_STREAM].name[19])) {
            return MIME_TYPE_APPLICATION_VND_STREET_STREAM;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_stardivision__label:
    switch (*str++) {
    case 'i':
    case 'I':
        /* must be 'application/vnd.stardivision.impress' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_STARDIVISION_IMPRESS].name[30])) {
            return MIME_TYPE_APPLICATION_VND_STARDIVISION_IMPRESS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'c':
    case 'C':
        goto application_vnd_stardivision_c_label;

    case 'm':
    case 'M':
        /* must be 'application/vnd.stardivision.math' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_STARDIVISION_MATH].name[30])) {
            return MIME_TYPE_APPLICATION_VND_STARDIVISION_MATH;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'd':
    case 'D':
        /* must be 'application/vnd.stardivision.draw' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_STARDIVISION_DRAW].name[30])) {
            return MIME_TYPE_APPLICATION_VND_STARDIVISION_DRAW;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'w':
    case 'W':
        /* skip to prefix 'application/vnd.stardivision.writer' */
        if (!str_ncasecmp(str, "riter", 5)) {
            str += 5;
            goto application_vnd_stardivision_writer_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_stardivision_c_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'application/vnd.stardivision.calc' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_STARDIVISION_CALC].name[31])) {
            return MIME_TYPE_APPLICATION_VND_STARDIVISION_CALC;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'h':
    case 'H':
        /* must be 'application/vnd.stardivision.chart' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_STARDIVISION_CHART].name[31])) {
            return MIME_TYPE_APPLICATION_VND_STARDIVISION_CHART;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_stardivision_writer_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_VND_STARDIVISION_WRITER;

    case '-':
        /* must be 'application/vnd.stardivision.writer-global' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_STARDIVISION_WRITER_GLOBAL].name[36])) {
            return MIME_TYPE_APPLICATION_VND_STARDIVISION_WRITER_GLOBAL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_r_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'application/vnd.rapid' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_RAPID].name[18])) {
            return MIME_TYPE_APPLICATION_VND_RAPID;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'i':
    case 'I':
        /* must be 'application/vnd.rim.cod' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_RIM_COD].name[18])) {
            return MIME_TYPE_APPLICATION_VND_RIM_COD;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_u_label:
    switch (*str++) {
    case 'p':
    case 'P':
        /* skip to prefix 'application/vnd.uplanet.' */
        if (!str_ncasecmp(str, "lanet.", 6)) {
            str += 6;
            goto application_vnd_uplanet__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'f':
    case 'F':
        /* must be 'application/vnd.ufdl' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_UFDL].name[18])) {
            return MIME_TYPE_APPLICATION_VND_UFDL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_uplanet__label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* skip to prefix 'application/vnd.uplanet.alert' */
        if (!str_ncasecmp(str, "lert", 4)) {
            str += 4;
            goto application_vnd_uplanet_alert_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 's':
    case 'S':
        /* must be 'application/vnd.uplanet.signal' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_UPLANET_SIGNAL].name[25])) {
            return MIME_TYPE_APPLICATION_VND_UPLANET_SIGNAL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'c':
    case 'C':
        goto application_vnd_uplanet_c_label;

    case 'b':
    case 'B':
        /* skip to prefix 'application/vnd.uplanet.bearer-choice' */
        if (!str_ncasecmp(str, "earer-choice", 12)) {
            str += 12;
            goto application_vnd_uplanet_bearer_choice_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'l':
    case 'L':
        /* skip to prefix 'application/vnd.uplanet.list' */
        if (!str_ncasecmp(str, "ist", 3)) {
            str += 3;
            goto application_vnd_uplanet_list_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_uplanet_alert_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_VND_UPLANET_ALERT;

    case '-':
        /* must be 'application/vnd.uplanet.alert-wbxml' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_UPLANET_ALERT_WBXML].name[30])) {
            return MIME_TYPE_APPLICATION_VND_UPLANET_ALERT_WBXML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_uplanet_c_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* skip to prefix 'application/vnd.uplanet.cacheop' */
        if (!str_ncasecmp(str, "cheop", 5)) {
            str += 5;
            goto application_vnd_uplanet_cacheop_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'h':
    case 'H':
        /* skip to prefix 'application/vnd.uplanet.channel' */
        if (!str_ncasecmp(str, "annel", 5)) {
            str += 5;
            goto application_vnd_uplanet_channel_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_uplanet_cacheop_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_VND_UPLANET_CACHEOP;

    case '-':
        /* must be 'application/vnd.uplanet.cacheop-wbxml' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_UPLANET_CACHEOP_WBXML].name[32])) {
            return MIME_TYPE_APPLICATION_VND_UPLANET_CACHEOP_WBXML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_uplanet_channel_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_VND_UPLANET_CHANNEL;

    case '-':
        /* must be 'application/vnd.uplanet.channel-wbxml' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_UPLANET_CHANNEL_WBXML].name[32])) {
            return MIME_TYPE_APPLICATION_VND_UPLANET_CHANNEL_WBXML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_uplanet_bearer_choice_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_VND_UPLANET_BEARER_CHOICE;

    case '-':
        /* must be 'application/vnd.uplanet.bearer-choice-wbxml' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_UPLANET_BEARER_CHOICE_WBXML].name[38])) {
            return MIME_TYPE_APPLICATION_VND_UPLANET_BEARER_CHOICE_WBXML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_uplanet_list_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_VND_UPLANET_LIST;

    case 'c':
    case 'C':
        /* skip to prefix 'application/vnd.uplanet.listcmd' */
        if (!str_ncasecmp(str, "md", 2)) {
            str += 2;
            goto application_vnd_uplanet_listcmd_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case '-':
        /* must be 'application/vnd.uplanet.list-wbxml' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_UPLANET_LIST_WBXML].name[29])) {
            return MIME_TYPE_APPLICATION_VND_UPLANET_LIST_WBXML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_uplanet_listcmd_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_VND_UPLANET_LISTCMD;

    case '-':
        /* must be 'application/vnd.uplanet.listcmd-wbxml' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_UPLANET_LISTCMD_WBXML].name[32])) {
            return MIME_TYPE_APPLICATION_VND_UPLANET_LISTCMD_WBXML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_t_label:
    switch (*str++) {
    case 'r':
    case 'R':
        goto application_vnd_tr_label;

    case 'v':
    case 'V':
        /* must be 'application/vnd.tve-trigger' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_TVE_TRIGGER].name[18])) {
            return MIME_TYPE_APPLICATION_VND_TVE_TRIGGER;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_tr_label:
    switch (*str++) {
    case 'i':
    case 'I':
        /* must be 'application/vnd.triscape.mxs' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_TRISCAPE_MXS].name[19])) {
            return MIME_TYPE_APPLICATION_VND_TRISCAPE_MXS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'u':
    case 'U':
        /* skip to prefix 'application/vnd.true' */
        if (!str_ncasecmp(str, "e", 1)) {
            str += 1;
            goto application_vnd_true_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_true_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'application/vnd.trueapp' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_TRUEAPP].name[21])) {
            return MIME_TYPE_APPLICATION_VND_TRUEAPP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'd':
    case 'D':
        /* must be 'application/vnd.truedoc' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_TRUEDOC].name[21])) {
            return MIME_TYPE_APPLICATION_VND_TRUEDOC;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_w_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* skip to prefix 'application/vnd.wap.' */
        if (!str_ncasecmp(str, "p.", 2)) {
            str += 2;
            goto application_vnd_wap__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'r':
    case 'R':
        /* must be 'application/vnd.wrq-hp3000-labelled' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_WRQ_HP3000_LABELLED].name[18])) {
            return MIME_TYPE_APPLICATION_VND_WRQ_HP3000_LABELLED;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'e':
    case 'E':
        /* must be 'application/vnd.webturbo' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_WEBTURBO].name[18])) {
            return MIME_TYPE_APPLICATION_VND_WEBTURBO;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 't':
    case 'T':
        /* must be 'application/vnd.wt.stf' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_WT_STF].name[18])) {
            return MIME_TYPE_APPLICATION_VND_WT_STF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_wap__label:
    switch (*str++) {
    case 's':
    case 'S':
        goto application_vnd_wap_s_label;

    case 'w':
    case 'W':
        goto application_vnd_wap_w_label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_wap_s_label:
    switch (*str++) {
    case 'i':
    case 'I':
        /* must be 'application/vnd.wap.sic' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_WAP_SIC].name[22])) {
            return MIME_TYPE_APPLICATION_VND_WAP_SIC;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'l':
    case 'L':
        /* must be 'application/vnd.wap.slc' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_WAP_SLC].name[22])) {
            return MIME_TYPE_APPLICATION_VND_WAP_SLC;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_wap_w_label:
    switch (*str++) {
    case 'b':
    case 'B':
        /* must be 'application/vnd.wap.wbxml' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_WAP_WBXML].name[22])) {
            return MIME_TYPE_APPLICATION_VND_WAP_WBXML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'm':
    case 'M':
        /* skip to prefix 'application/vnd.wap.wml' */
        if (!str_ncasecmp(str, "l", 1)) {
            str += 1;
            goto application_vnd_wap_wml_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_wap_wml_label:
    switch (*str++) {
    case 'c':
    case 'C':
        /* must be 'application/vnd.wap.wmlc' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_WAP_WMLC].name[24])) {
            return MIME_TYPE_APPLICATION_VND_WAP_WMLC;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* must be 'application/vnd.wap.wmlscriptc' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_WAP_WMLSCRIPTC].name[24])) {
            return MIME_TYPE_APPLICATION_VND_WAP_WMLSCRIPTC;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_v_label:
    switch (*str++) {
    case 'i':
    case 'I':
        goto application_vnd_vi_label;

    case 'c':
    case 'C':
        /* must be 'application/vnd.vcx' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_VCX].name[18])) {
            return MIME_TYPE_APPLICATION_VND_VCX;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'e':
    case 'E':
        /* must be 'application/vnd.vectorworks' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_VECTORWORKS].name[18])) {
            return MIME_TYPE_APPLICATION_VND_VECTORWORKS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_vi_label:
    switch (*str++) {
    case 's':
    case 'S':
        /* must be 'application/vnd.visio' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_VISIO].name[19])) {
            return MIME_TYPE_APPLICATION_VND_VISIO;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'd':
    case 'D':
        /* must be 'application/vnd.vidsoft.vidconference' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_VIDSOFT_VIDCONFERENCE].name[19])) {
            return MIME_TYPE_APPLICATION_VND_VIDSOFT_VIDCONFERENCE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'v':
    case 'V':
        /* must be 'application/vnd.vividence.scriptfile' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_VIVIDENCE_SCRIPTFILE].name[19])) {
            return MIME_TYPE_APPLICATION_VND_VIVIDENCE_SCRIPTFILE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_vnd_x_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'application/vnd.xara' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_XARA].name[18])) {
            return MIME_TYPE_APPLICATION_VND_XARA;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'f':
    case 'F':
        /* must be 'application/vnd.xfdl' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_VND_XFDL].name[18])) {
            return MIME_TYPE_APPLICATION_VND_XFDL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_label:
    switch (*str++) {
    case 'h':
    case 'H':
        /* must be 'application/xhtml+xml' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_XHTML_XML].name[14])) {
            return MIME_TYPE_APPLICATION_XHTML_XML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'm':
    case 'M':
        /* skip to prefix 'application/xml' */
        if (!str_ncasecmp(str, "l", 1)) {
            str += 1;
            goto application_xml_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case '-':
        goto application_x__label;

    case '4':
        /* must be 'application/x400-bp' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X400_BP].name[14])) {
            return MIME_TYPE_APPLICATION_X400_BP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_xml_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_XML;

    case '-':
        goto application_xml__label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_xml__label:
    switch (*str++) {
    case 'e':
    case 'E':
        /* must be 'application/xml-external-parsed-entity' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_XML_EXTERNAL_PARSED_ENTITY].name[17])) {
            return MIME_TYPE_APPLICATION_XML_EXTERNAL_PARSED_ENTITY;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'd':
    case 'D':
        /* must be 'application/xml-dtd' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_XML_DTD].name[17])) {
            return MIME_TYPE_APPLICATION_XML_DTD;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x__label:
    switch (*str++) {
    case '1':
        /* must be 'application/x-123' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_123].name[15])) {
            return MIME_TYPE_APPLICATION_X_123;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case '7':
        /* must be 'application/x-7z-compressed' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_7Z_COMPRESSED].name[15])) {
            return MIME_TYPE_APPLICATION_X_7Z_COMPRESSED;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'a':
    case 'A':
        goto application_x_a_label;

    case 'c':
    case 'C':
        goto application_x_c_label;

    case 'b':
    case 'B':
        goto application_x_b_label;

    case 'e':
    case 'E':
        /* must be 'application/x-executable' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_EXECUTABLE].name[15])) {
            return MIME_TYPE_APPLICATION_X_EXECUTABLE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'd':
    case 'D':
        goto application_x_d_label;

    case 'g':
    case 'G':
        goto application_x_g_label;

    case 'f':
    case 'F':
        goto application_x_f_label;

    case 'i':
    case 'I':
        goto application_x_i_label;

    case 'h':
    case 'H':
        goto application_x_h_label;

    case 'k':
    case 'K':
        goto application_x_k_label;

    case 'j':
    case 'J':
        goto application_x_j_label;

    case 'm':
    case 'M':
        goto application_x_m_label;

    case 'l':
    case 'L':
        goto application_x_l_label;

    case 'o':
    case 'O':
        goto application_x_o_label;

    case 'n':
    case 'N':
        goto application_x_n_label;

    case 'q':
    case 'Q':
        /* must be 'application/x-quicktimeplayer' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_QUICKTIMEPLAYER].name[15])) {
            return MIME_TYPE_APPLICATION_X_QUICKTIMEPLAYER;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'p':
    case 'P':
        goto application_x_p_label;

    case 's':
    case 'S':
        goto application_x_s_label;

    case 'r':
    case 'R':
        goto application_x_r_label;

    case 'u':
    case 'U':
        /* must be 'application/x-ustar' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_USTAR].name[15])) {
            return MIME_TYPE_APPLICATION_X_USTAR;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 't':
    case 'T':
        goto application_x_t_label;

    case 'w':
    case 'W':
        goto application_x_w_label;

    case 'v':
    case 'V':
        /* must be 'application/x-videolan' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_VIDEOLAN].name[15])) {
            return MIME_TYPE_APPLICATION_X_VIDEOLAN;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'x':
    case 'X':
        goto application_x_x_label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_a_label:
    switch (*str++) {
    case 'p':
    case 'P':
        /* must be 'application/x-apple-diskimage' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_APPLE_DISKIMAGE].name[16])) {
            return MIME_TYPE_APPLICATION_X_APPLE_DISKIMAGE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'b':
    case 'B':
        /* must be 'application/x-abiword' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_ABIWORD].name[16])) {
            return MIME_TYPE_APPLICATION_X_ABIWORD;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_c_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'application/x-cab' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_CAB].name[16])) {
            return MIME_TYPE_APPLICATION_X_CAB;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'b':
    case 'B':
        goto application_x_cb_label;

    case 'd':
    case 'D':
        goto application_x_cd_label;

    case 'h':
    case 'H':
        /* must be 'application/x-chess-pgn' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_CHESS_PGN].name[16])) {
            return MIME_TYPE_APPLICATION_X_CHESS_PGN;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'o':
    case 'O':
        /* must be 'application/x-core' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_CORE].name[16])) {
            return MIME_TYPE_APPLICATION_X_CORE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'p':
    case 'P':
        /* must be 'application/x-cpio' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_CPIO].name[16])) {
            return MIME_TYPE_APPLICATION_X_CPIO;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* must be 'application/x-csh' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_CSH].name[16])) {
            return MIME_TYPE_APPLICATION_X_CSH;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_cb_label:
    switch (*str++) {
    case 'r':
    case 'R':
        /* must be 'application/x-cbr' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_CBR].name[17])) {
            return MIME_TYPE_APPLICATION_X_CBR;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'z':
    case 'Z':
        /* must be 'application/x-cbz' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_CBZ].name[17])) {
            return MIME_TYPE_APPLICATION_X_CBZ;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_cd_label:
    switch (*str++) {
    case 'l':
    case 'L':
        /* must be 'application/x-cdlink' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_CDLINK].name[17])) {
            return MIME_TYPE_APPLICATION_X_CDLINK;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'f':
    case 'F':
        /* must be 'application/x-cdf' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_CDF].name[17])) {
            return MIME_TYPE_APPLICATION_X_CDF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_b_label:
    switch (*str++) {
    case 'i':
    case 'I':
        /* must be 'application/x-bittorrent' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_BITTORRENT].name[16])) {
            return MIME_TYPE_APPLICATION_X_BITTORRENT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'c':
    case 'C':
        /* must be 'application/x-bcpio' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_BCPIO].name[16])) {
            return MIME_TYPE_APPLICATION_X_BCPIO;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'z':
    case 'Z':
        /* must be 'application/x-bzip2' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_BZIP2].name[16])) {
            return MIME_TYPE_APPLICATION_X_BZIP2;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_d_label:
    switch (*str++) {
    case 'i':
    case 'I':
        /* must be 'application/x-director' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_DIRECTOR].name[16])) {
            return MIME_TYPE_APPLICATION_X_DIRECTOR;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'm':
    case 'M':
        /* must be 'application/x-dms' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_DMS].name[16])) {
            return MIME_TYPE_APPLICATION_X_DMS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'e':
    case 'E':
        /* must be 'application/x-debian-package' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_DEBIAN_PACKAGE].name[16])) {
            return MIME_TYPE_APPLICATION_X_DEBIAN_PACKAGE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'o':
    case 'O':
        /* must be 'application/x-doom' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_DOOM].name[16])) {
            return MIME_TYPE_APPLICATION_X_DOOM;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'v':
    case 'V':
        /* must be 'application/x-dvi' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_DVI].name[16])) {
            return MIME_TYPE_APPLICATION_X_DVI;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_g_label:
    switch (*str++) {
    case 'z':
    case 'Z':
        /* must be 'application/x-gzip' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_GZIP].name[16])) {
            return MIME_TYPE_APPLICATION_X_GZIP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'r':
    case 'R':
        /* must be 'application/x-graphing-calculator' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_GRAPHING_CALCULATOR].name[16])) {
            return MIME_TYPE_APPLICATION_X_GRAPHING_CALCULATOR;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 't':
    case 'T':
        /* must be 'application/x-gtar' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_GTAR].name[16])) {
            return MIME_TYPE_APPLICATION_X_GTAR;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'o':
    case 'O':
        /* must be 'application/x-go-sgf' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_GO_SGF].name[16])) {
            return MIME_TYPE_APPLICATION_X_GO_SGF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'n':
    case 'N':
        /* must be 'application/x-gnumeric' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_GNUMERIC].name[16])) {
            return MIME_TYPE_APPLICATION_X_GNUMERIC;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_f_label:
    switch (*str++) {
    case 'r':
    case 'R':
        /* must be 'application/x-freemind' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_FREEMIND].name[16])) {
            return MIME_TYPE_APPLICATION_X_FREEMIND;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'u':
    case 'U':
        /* must be 'application/x-futuresplash' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_FUTURESPLASH].name[16])) {
            return MIME_TYPE_APPLICATION_X_FUTURESPLASH;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'l':
    case 'L':
        /* must be 'application/x-flac' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_FLAC].name[16])) {
            return MIME_TYPE_APPLICATION_X_FLAC;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'o':
    case 'O':
        /* must be 'application/x-font' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_FONT].name[16])) {
            return MIME_TYPE_APPLICATION_X_FONT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_i_label:
    switch (*str++) {
    case 'p':
    case 'P':
        /* must be 'application/x-iphone' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_IPHONE].name[16])) {
            return MIME_TYPE_APPLICATION_X_IPHONE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'c':
    case 'C':
        /* must be 'application/x-ica' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_ICA].name[16])) {
            return MIME_TYPE_APPLICATION_X_ICA;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* must be 'application/x-iso9660-image' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_ISO9660_IMAGE].name[16])) {
            return MIME_TYPE_APPLICATION_X_ISO9660_IMAGE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'n':
    case 'N':
        goto application_x_in_label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_in_label:
    switch (*str++) {
    case 'e':
    case 'E':
        /* must be 'application/x-inex' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_INEX].name[17])) {
            return MIME_TYPE_APPLICATION_X_INEX;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 't':
    case 'T':
        /* must be 'application/x-internet-signup' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_INTERNET_SIGNUP].name[17])) {
            return MIME_TYPE_APPLICATION_X_INTERNET_SIGNUP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_h_label:
    switch (*str++) {
    case 'd':
    case 'D':
        /* must be 'application/x-hdf' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_HDF].name[16])) {
            return MIME_TYPE_APPLICATION_X_HDF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 't':
    case 'T':
        /* skip to prefix 'application/x-httpd-' */
        if (!str_ncasecmp(str, "tpd-", 4)) {
            str += 4;
            goto application_x_httpd__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_httpd__label:
    switch (*str++) {
    case 'p':
    case 'P':
        /* skip to prefix 'application/x-httpd-php' */
        if (!str_ncasecmp(str, "hp", 2)) {
            str += 2;
            goto application_x_httpd_php_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'e':
    case 'E':
        /* must be 'application/x-httpd-eruby' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_HTTPD_ERUBY].name[21])) {
            return MIME_TYPE_APPLICATION_X_HTTPD_ERUBY;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_httpd_php_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_X_HTTPD_PHP;

    case '3':
        goto application_x_httpd_php3_label;

    case '-':
        /* must be 'application/x-httpd-php-source' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_HTTPD_PHP_SOURCE].name[24])) {
            return MIME_TYPE_APPLICATION_X_HTTPD_PHP_SOURCE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case '4':
        /* must be 'application/x-httpd-php4' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_HTTPD_PHP4].name[24])) {
            return MIME_TYPE_APPLICATION_X_HTTPD_PHP4;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_httpd_php3_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_X_HTTPD_PHP3;

    case '-':
        /* must be 'application/x-httpd-php3-preprocessed' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_HTTPD_PHP3_PREPROCESSED].name[25])) {
            return MIME_TYPE_APPLICATION_X_HTTPD_PHP3_PREPROCESSED;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_k_label:
    switch (*str++) {
    case 'c':
    case 'C':
        /* must be 'application/x-kchart' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_KCHART].name[16])) {
            return MIME_TYPE_APPLICATION_X_KCHART;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'd':
    case 'D':
        /* must be 'application/x-kdelnk' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_KDELNK].name[16])) {
            return MIME_TYPE_APPLICATION_X_KDELNK;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'i':
    case 'I':
        /* must be 'application/x-killustrator' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_KILLUSTRATOR].name[16])) {
            return MIME_TYPE_APPLICATION_X_KILLUSTRATOR;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'o':
    case 'O':
        /* must be 'application/x-koan' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_KOAN].name[16])) {
            return MIME_TYPE_APPLICATION_X_KOAN;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'p':
    case 'P':
        /* must be 'application/x-kpresenter' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_KPRESENTER].name[16])) {
            return MIME_TYPE_APPLICATION_X_KPRESENTER;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* must be 'application/x-kspread' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_KSPREAD].name[16])) {
            return MIME_TYPE_APPLICATION_X_KSPREAD;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'w':
    case 'W':
        /* must be 'application/x-kword' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_KWORD].name[16])) {
            return MIME_TYPE_APPLICATION_X_KWORD;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_j_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* skip to prefix 'application/x-java' */
        if (!str_ncasecmp(str, "va", 2)) {
            str += 2;
            goto application_x_java_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'm':
    case 'M':
        /* must be 'application/x-jmol' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_JMOL].name[16])) {
            return MIME_TYPE_APPLICATION_X_JMOL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_java_label:
    switch (*str++) {
    case 's':
    case 'S':
        /* must be 'application/x-javascript' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_JAVASCRIPT].name[19])) {
            return MIME_TYPE_APPLICATION_X_JAVASCRIPT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case '-':
        goto application_x_java__label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_java__label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'application/x-java-applet' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_JAVA_APPLET].name[20])) {
            return MIME_TYPE_APPLICATION_X_JAVA_APPLET;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'b':
    case 'B':
        /* must be 'application/x-java-bean' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_JAVA_BEAN].name[20])) {
            return MIME_TYPE_APPLICATION_X_JAVA_BEAN;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'j':
    case 'J':
        /* must be 'application/x-java-jnlp-file' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_JAVA_JNLP_FILE].name[20])) {
            return MIME_TYPE_APPLICATION_X_JAVA_JNLP_FILE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_m_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'application/x-maker' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_MAKER].name[16])) {
            return MIME_TYPE_APPLICATION_X_MAKER;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'i':
    case 'I':
        /* must be 'application/x-mif' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_MIF].name[16])) {
            return MIME_TYPE_APPLICATION_X_MIF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        goto application_x_ms_label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_ms_label:
    switch (*str++) {
    case 'i':
    case 'I':
        /* must be 'application/x-msi' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_MSI].name[17])) {
            return MIME_TYPE_APPLICATION_X_MSI;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case '-':
        /* skip to prefix 'application/x-ms-wm' */
        if (!str_ncasecmp(str, "wm", 2)) {
            str += 2;
            goto application_x_ms_wm_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'd':
    case 'D':
        /* must be 'application/x-msdos-program' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_MSDOS_PROGRAM].name[17])) {
            return MIME_TYPE_APPLICATION_X_MSDOS_PROGRAM;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_ms_wm_label:
    switch (*str++) {
    case 'z':
    case 'Z':
        /* must be 'application/x-ms-wmz' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_MS_WMZ].name[20])) {
            return MIME_TYPE_APPLICATION_X_MS_WMZ;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'd':
    case 'D':
        /* must be 'application/x-ms-wmd' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_MS_WMD].name[20])) {
            return MIME_TYPE_APPLICATION_X_MS_WMD;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_l_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'application/x-latex' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_LATEX].name[16])) {
            return MIME_TYPE_APPLICATION_X_LATEX;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'h':
    case 'H':
        /* must be 'application/x-lha' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_LHA].name[16])) {
            return MIME_TYPE_APPLICATION_X_LHA;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'z':
    case 'Z':
        goto application_x_lz_label;

    case 'y':
    case 'Y':
        /* must be 'application/x-lyx' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_LYX].name[16])) {
            return MIME_TYPE_APPLICATION_X_LYX;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_lz_label:
    switch (*str++) {
    case 'h':
    case 'H':
        /* must be 'application/x-lzh' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_LZH].name[17])) {
            return MIME_TYPE_APPLICATION_X_LZH;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'x':
    case 'X':
        /* must be 'application/x-lzx' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_LZX].name[17])) {
            return MIME_TYPE_APPLICATION_X_LZX;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_o_label:
    switch (*str++) {
    case 'b':
    case 'B':
        /* must be 'application/x-object' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_OBJECT].name[16])) {
            return MIME_TYPE_APPLICATION_X_OBJECT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'z':
    case 'Z':
        /* must be 'application/x-oz-application' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_OZ_APPLICATION].name[16])) {
            return MIME_TYPE_APPLICATION_X_OZ_APPLICATION;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_n_label:
    switch (*str++) {
    case 's':
    case 'S':
        /* must be 'application/x-ns-proxy-autoconfig' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_NS_PROXY_AUTOCONFIG].name[16])) {
            return MIME_TYPE_APPLICATION_X_NS_PROXY_AUTOCONFIG;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'e':
    case 'E':
        /* must be 'application/x-netcdf' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_NETCDF].name[16])) {
            return MIME_TYPE_APPLICATION_X_NETCDF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'w':
    case 'W':
        /* must be 'application/x-nwc' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_NWC].name[16])) {
            return MIME_TYPE_APPLICATION_X_NWC;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_p_label:
    switch (*str++) {
    case 'y':
    case 'Y':
        /* must be 'application/x-python-code' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_PYTHON_CODE].name[16])) {
            return MIME_TYPE_APPLICATION_X_PYTHON_CODE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'k':
    case 'K':
        /* skip to prefix 'application/x-pkcs7-c' */
        if (!str_ncasecmp(str, "cs7-c", 5)) {
            str += 5;
            goto application_x_pkcs7_c_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_pkcs7_c_label:
    switch (*str++) {
    case 'r':
    case 'R':
        /* must be 'application/x-pkcs7-crl' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_PKCS7_CRL].name[22])) {
            return MIME_TYPE_APPLICATION_X_PKCS7_CRL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'e':
    case 'E':
        /* must be 'application/x-pkcs7-certreqresp' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_PKCS7_CERTREQRESP].name[22])) {
            return MIME_TYPE_APPLICATION_X_PKCS7_CERTREQRESP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_s_label:
    switch (*str++) {
    case 'h':
    case 'H':
        goto application_x_sh_label;

    case 't':
    case 'T':
        /* must be 'application/x-stuffit' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_STUFFIT].name[16])) {
            return MIME_TYPE_APPLICATION_X_STUFFIT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'v':
    case 'V':
        /* skip to prefix 'application/x-sv4c' */
        if (!str_ncasecmp(str, "4c", 2)) {
            str += 2;
            goto application_x_sv4c_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_sh_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_X_SH;

    case 'a':
    case 'A':
        /* must be 'application/x-shar' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_SHAR].name[17])) {
            return MIME_TYPE_APPLICATION_X_SHAR;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'e':
    case 'E':
        /* must be 'application/x-shellscript' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_SHELLSCRIPT].name[17])) {
            return MIME_TYPE_APPLICATION_X_SHELLSCRIPT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'o':
    case 'O':
        /* must be 'application/x-shockwave-flash' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_SHOCKWAVE_FLASH].name[17])) {
            return MIME_TYPE_APPLICATION_X_SHOCKWAVE_FLASH;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_sv4c_label:
    switch (*str++) {
    case 'p':
    case 'P':
        /* must be 'application/x-sv4cpio' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_SV4CPIO].name[19])) {
            return MIME_TYPE_APPLICATION_X_SV4CPIO;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'r':
    case 'R':
        /* must be 'application/x-sv4crc' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_SV4CRC].name[19])) {
            return MIME_TYPE_APPLICATION_X_SV4CRC;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_r_label:
    switch (*str++) {
    case 'x':
    case 'X':
        /* must be 'application/x-rx' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_RX].name[16])) {
            return MIME_TYPE_APPLICATION_X_RX;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'e':
    case 'E':
        /* must be 'application/x-redhat-package-manager' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_REDHAT_PACKAGE_MANAGER].name[16])) {
            return MIME_TYPE_APPLICATION_X_REDHAT_PACKAGE_MANAGER;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_t_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'application/x-tar' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_TAR].name[16])) {
            return MIME_TYPE_APPLICATION_X_TAR;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'c':
    case 'C':
        /* must be 'application/x-tcl' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_TCL].name[16])) {
            return MIME_TYPE_APPLICATION_X_TCL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'r':
    case 'R':
        goto application_x_tr_label;

    case 'e':
    case 'E':
        /* skip to prefix 'application/x-tex' */
        if (!str_ncasecmp(str, "x", 1)) {
            str += 1;
            goto application_x_tex_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_tr_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'application/x-trash' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_TRASH].name[17])) {
            return MIME_TYPE_APPLICATION_X_TRASH;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'e':
    case 'E':
        /* must be 'application/x-trec' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_TREC].name[17])) {
            return MIME_TYPE_APPLICATION_X_TREC;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'o':
    case 'O':
        /* skip to prefix 'application/x-troff' */
        if (!str_ncasecmp(str, "ff", 2)) {
            str += 2;
            goto application_x_troff_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_troff_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_APPLICATION_X_TROFF;

    case '-':
        /* skip to prefix 'application/x-troff-m' */
        if (!str_ncasecmp(str, "m", 1)) {
            str += 1;
            goto application_x_troff_m_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_troff_m_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'application/x-troff-man' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_TROFF_MAN].name[22])) {
            return MIME_TYPE_APPLICATION_X_TROFF_MAN;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* must be 'application/x-troff-ms' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_TROFF_MS].name[22])) {
            return MIME_TYPE_APPLICATION_X_TROFF_MS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'e':
    case 'E':
        /* must be 'application/x-troff-me' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_TROFF_ME].name[22])) {
            return MIME_TYPE_APPLICATION_X_TROFF_ME;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_tex_label:
    switch (*str++) {
    case 'i':
    case 'I':
        /* must be 'application/x-texinfo' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_TEXINFO].name[18])) {
            return MIME_TYPE_APPLICATION_X_TEXINFO;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case '-':
        goto application_x_tex__label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_tex__label:
    switch (*str++) {
    case 'p':
    case 'P':
        /* must be 'application/x-tex-pk' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_TEX_PK].name[19])) {
            return MIME_TYPE_APPLICATION_X_TEX_PK;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'g':
    case 'G':
        /* must be 'application/x-tex-gf' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_TEX_GF].name[19])) {
            return MIME_TYPE_APPLICATION_X_TEX_GF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_w_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'application/x-wais-source' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_WAIS_SOURCE].name[16])) {
            return MIME_TYPE_APPLICATION_X_WAIS_SOURCE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'i':
    case 'I':
        /* must be 'application/x-wingz' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_WINGZ].name[16])) {
            return MIME_TYPE_APPLICATION_X_WINGZ;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

application_x_x_label:
    switch (*str++) {
    case 'p':
    case 'P':
        /* must be 'application/x-xpinstall' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_XPINSTALL].name[16])) {
            return MIME_TYPE_APPLICATION_X_XPINSTALL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'c':
    case 'C':
        /* must be 'application/x-xcf' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_XCF].name[16])) {
            return MIME_TYPE_APPLICATION_X_XCF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case '5':
        /* must be 'application/x-x509-ca-cert' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_X509_CA_CERT].name[16])) {
            return MIME_TYPE_APPLICATION_X_X509_CA_CERT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'f':
    case 'F':
        /* must be 'application/x-xfig' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_APPLICATION_X_XFIG].name[16])) {
            return MIME_TYPE_APPLICATION_X_XFIG;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

audio__label:
    switch (*str++) {
    case 'b':
    case 'B':
        /* must be 'audio/basic' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_BASIC].name[7])) {
            return MIME_TYPE_AUDIO_BASIC;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'd':
    case 'D':
        /* must be 'audio/dat12' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_DAT12].name[7])) {
            return MIME_TYPE_AUDIO_DAT12;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'g':
    case 'G':
        /* must be 'audio/g.722.1' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_G_722_1].name[7])) {
            return MIME_TYPE_AUDIO_G_722_1;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'm':
    case 'M':
        goto audio_m_label;

    case 'l':
    case 'L':
        goto audio_l_label;

    case 'o':
    case 'O':
        /* must be 'audio/ogg' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_OGG].name[7])) {
            return MIME_TYPE_AUDIO_OGG;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'p':
    case 'P':
        goto audio_p_label;

    case '3':
        goto audio_3_label;

    case 't':
    case 'T':
        goto audio_t_label;

    case 'v':
    case 'V':
        /* skip to prefix 'audio/vnd.' */
        if (!str_ncasecmp(str, "nd.", 3)) {
            str += 3;
            goto audio_vnd__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'x':
    case 'X':
        /* skip to prefix 'audio/x-' */
        if (!str_ncasecmp(str, "-", 1)) {
            str += 1;
            goto audio_x__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

audio_m_label:
    switch (*str++) {
    case 'i':
    case 'I':
        /* must be 'audio/midi' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_MIDI].name[8])) {
            return MIME_TYPE_AUDIO_MIDI;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'p':
    case 'P':
        goto audio_mp_label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

audio_mp_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'audio/mpa-robust' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_MPA_ROBUST].name[9])) {
            return MIME_TYPE_AUDIO_MPA_ROBUST;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'e':
    case 'E':
        /* skip to prefix 'audio/mpeg' */
        if (!str_ncasecmp(str, "g", 1)) {
            str += 1;
            goto audio_mpeg_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case '4':
        /* must be 'audio/mp4a-latm' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_MP4A_LATM].name[9])) {
            return MIME_TYPE_AUDIO_MP4A_LATM;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

audio_mpeg_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_AUDIO_MPEG;

    case 'u':
    case 'U':
        /* must be 'audio/mpegurl' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_MPEGURL].name[11])) {
            return MIME_TYPE_AUDIO_MPEGURL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

audio_l_label:
    switch (*str++) {
    case '1':
        /* must be 'audio/l16' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_L16].name[8])) {
            return MIME_TYPE_AUDIO_L16;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case '2':
        goto audio_l2_label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

audio_l2_label:
    switch (*str++) {
    case '0':
        /* must be 'audio/l20' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_L20].name[9])) {
            return MIME_TYPE_AUDIO_L20;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case '4':
        /* must be 'audio/l24' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_L24].name[9])) {
            return MIME_TYPE_AUDIO_L24;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

audio_p_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'audio/parityfec' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_PARITYFEC].name[8])) {
            return MIME_TYPE_AUDIO_PARITYFEC;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'r':
    case 'R':
        /* must be 'audio/prs.sid' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_PRS_SID].name[8])) {
            return MIME_TYPE_AUDIO_PRS_SID;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

audio_3_label:
    switch (*str++) {
    case '2':
        /* must be 'audio/32kadpcm' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_32KADPCM].name[8])) {
            return MIME_TYPE_AUDIO_32KADPCM;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'g':
    case 'G':
        /* must be 'audio/3gpp' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_3GPP].name[8])) {
            return MIME_TYPE_AUDIO_3GPP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

audio_t_label:
    switch (*str++) {
    case 'e':
    case 'E':
        /* must be 'audio/telephone-event' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_TELEPHONE_EVENT].name[8])) {
            return MIME_TYPE_AUDIO_TELEPHONE_EVENT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'o':
    case 'O':
        /* must be 'audio/tone' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_TONE].name[8])) {
            return MIME_TYPE_AUDIO_TONE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

audio_vnd__label:
    switch (*str++) {
    case 'c':
    case 'C':
        goto audio_vnd_c_label;

    case 'e':
    case 'E':
        /* must be 'audio/vnd.everad.plj' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_VND_EVERAD_PLJ].name[11])) {
            return MIME_TYPE_AUDIO_VND_EVERAD_PLJ;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'd':
    case 'D':
        /* must be 'audio/vnd.digital-winds' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_VND_DIGITAL_WINDS].name[11])) {
            return MIME_TYPE_AUDIO_VND_DIGITAL_WINDS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'l':
    case 'L':
        /* must be 'audio/vnd.lucent.voice' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_VND_LUCENT_VOICE].name[11])) {
            return MIME_TYPE_AUDIO_VND_LUCENT_VOICE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'o':
    case 'O':
        /* must be 'audio/vnd.octel.sbc' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_VND_OCTEL_SBC].name[11])) {
            return MIME_TYPE_AUDIO_VND_OCTEL_SBC;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'n':
    case 'N':
        goto audio_vnd_n_label;

    case 'q':
    case 'Q':
        /* must be 'audio/vnd.qcelp' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_VND_QCELP].name[11])) {
            return MIME_TYPE_AUDIO_VND_QCELP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'r':
    case 'R':
        /* must be 'audio/vnd.rhetorex.32kadpcm' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_VND_RHETOREX_32KADPCM].name[11])) {
            return MIME_TYPE_AUDIO_VND_RHETOREX_32KADPCM;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'v':
    case 'V':
        /* must be 'audio/vnd.vmx.cvsd' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_VND_VMX_CVSD].name[11])) {
            return MIME_TYPE_AUDIO_VND_VMX_CVSD;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

audio_vnd_c_label:
    switch (*str++) {
    case 'i':
    case 'I':
        /* must be 'audio/vnd.cisco.nse' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_VND_CISCO_NSE].name[12])) {
            return MIME_TYPE_AUDIO_VND_CISCO_NSE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'n':
    case 'N':
        /* skip to prefix 'audio/vnd.cns.' */
        if (!str_ncasecmp(str, "s.", 2)) {
            str += 2;
            goto audio_vnd_cns__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

audio_vnd_cns__label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'audio/vnd.cns.anp1' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_VND_CNS_ANP1].name[15])) {
            return MIME_TYPE_AUDIO_VND_CNS_ANP1;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'i':
    case 'I':
        /* must be 'audio/vnd.cns.inf1' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_VND_CNS_INF1].name[15])) {
            return MIME_TYPE_AUDIO_VND_CNS_INF1;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

audio_vnd_n_label:
    switch (*str++) {
    case 'u':
    case 'U':
        /* skip to prefix 'audio/vnd.nuera.ecelp' */
        if (!str_ncasecmp(str, "era.ecelp", 9)) {
            str += 9;
            goto audio_vnd_nuera_ecelp_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'o':
    case 'O':
        /* must be 'audio/vnd.nortel.vbk' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_VND_NORTEL_VBK].name[12])) {
            return MIME_TYPE_AUDIO_VND_NORTEL_VBK;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

audio_vnd_nuera_ecelp_label:
    switch (*str++) {
    case '9':
        /* must be 'audio/vnd.nuera.ecelp9600' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_VND_NUERA_ECELP9600].name[22])) {
            return MIME_TYPE_AUDIO_VND_NUERA_ECELP9600;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case '4':
        /* must be 'audio/vnd.nuera.ecelp4800' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_VND_NUERA_ECELP4800].name[22])) {
            return MIME_TYPE_AUDIO_VND_NUERA_ECELP4800;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case '7':
        /* must be 'audio/vnd.nuera.ecelp7470' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_VND_NUERA_ECELP7470].name[22])) {
            return MIME_TYPE_AUDIO_VND_NUERA_ECELP7470;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

audio_x__label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'audio/x-aiff' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_X_AIFF].name[9])) {
            return MIME_TYPE_AUDIO_X_AIFF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'g':
    case 'G':
        /* must be 'audio/x-gsm' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_X_GSM].name[9])) {
            return MIME_TYPE_AUDIO_X_GSM;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'm':
    case 'M':
        goto audio_x_m_label;

    case 'p':
    case 'P':
        /* skip to prefix 'audio/x-pn-realaudio' */
        if (!str_ncasecmp(str, "n-realaudio", 11)) {
            str += 11;
            goto audio_x_pn_realaudio_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 's':
    case 'S':
        goto audio_x_s_label;

    case 'r':
    case 'R':
        /* must be 'audio/x-realaudio' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_X_REALAUDIO].name[9])) {
            return MIME_TYPE_AUDIO_X_REALAUDIO;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'w':
    case 'W':
        /* must be 'audio/x-wav' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_X_WAV].name[9])) {
            return MIME_TYPE_AUDIO_X_WAV;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

audio_x_m_label:
    switch (*str++) {
    case 'p':
    case 'P':
        /* must be 'audio/x-mpegurl' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_X_MPEGURL].name[10])) {
            return MIME_TYPE_AUDIO_X_MPEGURL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* skip to prefix 'audio/x-ms-w' */
        if (!str_ncasecmp(str, "-w", 2)) {
            str += 2;
            goto audio_x_ms_w_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

audio_x_ms_w_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'audio/x-ms-wax' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_X_MS_WAX].name[13])) {
            return MIME_TYPE_AUDIO_X_MS_WAX;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'm':
    case 'M':
        /* must be 'audio/x-ms-wma' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_X_MS_WMA].name[13])) {
            return MIME_TYPE_AUDIO_X_MS_WMA;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

audio_x_pn_realaudio_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_AUDIO_X_PN_REALAUDIO;

    case '-':
        /* must be 'audio/x-pn-realaudio-plugin' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_X_PN_REALAUDIO_PLUGIN].name[21])) {
            return MIME_TYPE_AUDIO_X_PN_REALAUDIO_PLUGIN;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

audio_x_s_label:
    switch (*str++) {
    case 'c':
    case 'C':
        /* must be 'audio/x-scpls' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_X_SCPLS].name[10])) {
            return MIME_TYPE_AUDIO_X_SCPLS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'd':
    case 'D':
        /* must be 'audio/x-sd2' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_AUDIO_X_SD2].name[10])) {
            return MIME_TYPE_AUDIO_X_SD2;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

chemical_x__label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'chemical/x-alchemy' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_ALCHEMY].name[12])) {
            return MIME_TYPE_CHEMICAL_X_ALCHEMY;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'c':
    case 'C':
        goto chemical_x_c_label;

    case 'e':
    case 'E':
        /* must be 'chemical/x-embl-dl-nucleotide' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_EMBL_DL_NUCLEOTIDE].name[12])) {
            return MIME_TYPE_CHEMICAL_X_EMBL_DL_NUCLEOTIDE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'g':
    case 'G':
        goto chemical_x_g_label;

    case 'i':
    case 'I':
        /* must be 'chemical/x-isostar' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_ISOSTAR].name[12])) {
            return MIME_TYPE_CHEMICAL_X_ISOSTAR;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'h':
    case 'H':
        /* must be 'chemical/x-hin' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_HIN].name[12])) {
            return MIME_TYPE_CHEMICAL_X_HIN;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'k':
    case 'K':
        /* must be 'chemical/x-kinemage' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_KINEMAGE].name[12])) {
            return MIME_TYPE_CHEMICAL_X_KINEMAGE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'j':
    case 'J':
        /* must be 'chemical/x-jcamp-dx' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_JCAMP_DX].name[12])) {
            return MIME_TYPE_CHEMICAL_X_JCAMP_DX;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'm':
    case 'M':
        goto chemical_x_m_label;

    case 'n':
    case 'N':
        /* skip to prefix 'chemical/x-ncbi-asn1' */
        if (!str_ncasecmp(str, "cbi-asn1", 8)) {
            str += 8;
            goto chemical_x_ncbi_asn1_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'p':
    case 'P':
        /* must be 'chemical/x-pdb' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_PDB].name[12])) {
            return MIME_TYPE_CHEMICAL_X_PDB;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* must be 'chemical/x-swissprot' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_SWISSPROT].name[12])) {
            return MIME_TYPE_CHEMICAL_X_SWISSPROT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'r':
    case 'R':
        /* must be 'chemical/x-rosdal' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_ROSDAL].name[12])) {
            return MIME_TYPE_CHEMICAL_X_ROSDAL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'v':
    case 'V':
        goto chemical_x_v_label;

    case 'x':
    case 'X':
        goto chemical_x_x_label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

chemical_x_c_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* skip to prefix 'chemical/x-cac' */
        if (!str_ncasecmp(str, "c", 1)) {
            str += 1;
            goto chemical_x_cac_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'e':
    case 'E':
        /* must be 'chemical/x-cerius' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_CERIUS].name[13])) {
            return MIME_TYPE_CHEMICAL_X_CERIUS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'd':
    case 'D':
        /* must be 'chemical/x-cdx' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_CDX].name[13])) {
            return MIME_TYPE_CHEMICAL_X_CDX;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'i':
    case 'I':
        /* must be 'chemical/x-cif' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_CIF].name[13])) {
            return MIME_TYPE_CHEMICAL_X_CIF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'h':
    case 'H':
        /* skip to prefix 'chemical/x-chem' */
        if (!str_ncasecmp(str, "em", 2)) {
            str += 2;
            goto chemical_x_chem_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'm':
    case 'M':
        goto chemical_x_cm_label;

    case 'o':
    case 'O':
        /* must be 'chemical/x-compass' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_COMPASS].name[13])) {
            return MIME_TYPE_CHEMICAL_X_COMPASS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* must be 'chemical/x-csml' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_CSML].name[13])) {
            return MIME_TYPE_CHEMICAL_X_CSML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'r':
    case 'R':
        /* must be 'chemical/x-crossfire' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_CROSSFIRE].name[13])) {
            return MIME_TYPE_CHEMICAL_X_CROSSFIRE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 't':
    case 'T':
        /* must be 'chemical/x-ctx' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_CTX].name[13])) {
            return MIME_TYPE_CHEMICAL_X_CTX;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'x':
    case 'X':
        /* must be 'chemical/x-cxf' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_CXF].name[13])) {
            return MIME_TYPE_CHEMICAL_X_CXF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

chemical_x_cac_label:
    switch (*str++) {
    case 'h':
    case 'H':
        /* skip to prefix 'chemical/x-cache' */
        if (!str_ncasecmp(str, "e", 1)) {
            str += 1;
            goto chemical_x_cache_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 't':
    case 'T':
        /* must be 'chemical/x-cactvs-binary' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_CACTVS_BINARY].name[15])) {
            return MIME_TYPE_CHEMICAL_X_CACTVS_BINARY;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

chemical_x_cache_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_CHEMICAL_X_CACHE;

    case '-':
        /* must be 'chemical/x-cache-csf' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_CACHE_CSF].name[17])) {
            return MIME_TYPE_CHEMICAL_X_CACHE_CSF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

chemical_x_chem_label:
    switch (*str++) {
    case '3':
        /* must be 'chemical/x-chem3d' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_CHEM3D].name[16])) {
            return MIME_TYPE_CHEMICAL_X_CHEM3D;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'd':
    case 'D':
        /* must be 'chemical/x-chemdraw' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_CHEMDRAW].name[16])) {
            return MIME_TYPE_CHEMICAL_X_CHEMDRAW;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

chemical_x_cm_label:
    switch (*str++) {
    case 'd':
    case 'D':
        /* must be 'chemical/x-cmdf' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_CMDF].name[14])) {
            return MIME_TYPE_CHEMICAL_X_CMDF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'l':
    case 'L':
        /* must be 'chemical/x-cml' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_CML].name[14])) {
            return MIME_TYPE_CHEMICAL_X_CML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

chemical_x_g_label:
    switch (*str++) {
    case 'a':
    case 'A':
        goto chemical_x_ga_label;

    case 'c':
    case 'C':
        /* must be 'chemical/x-gcg8-sequence' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_GCG8_SEQUENCE].name[13])) {
            return MIME_TYPE_CHEMICAL_X_GCG8_SEQUENCE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'e':
    case 'E':
        /* must be 'chemical/x-genbank' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_GENBANK].name[13])) {
            return MIME_TYPE_CHEMICAL_X_GENBANK;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

chemical_x_ga_label:
    switch (*str++) {
    case 'u':
    case 'U':
        /* skip to prefix 'chemical/x-gaussian-' */
        if (!str_ncasecmp(str, "ssian-", 6)) {
            str += 6;
            goto chemical_x_gaussian__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'm':
    case 'M':
        /* must be 'chemical/x-gamess-input' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_GAMESS_INPUT].name[14])) {
            return MIME_TYPE_CHEMICAL_X_GAMESS_INPUT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'l':
    case 'L':
        /* must be 'chemical/x-galactic-spc' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_GALACTIC_SPC].name[14])) {
            return MIME_TYPE_CHEMICAL_X_GALACTIC_SPC;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

chemical_x_gaussian__label:
    switch (*str++) {
    case 'i':
    case 'I':
        /* must be 'chemical/x-gaussian-input' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_GAUSSIAN_INPUT].name[21])) {
            return MIME_TYPE_CHEMICAL_X_GAUSSIAN_INPUT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'c':
    case 'C':
        goto chemical_x_gaussian_c_label;

    case 'l':
    case 'L':
        /* must be 'chemical/x-gaussian-log' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_GAUSSIAN_LOG].name[21])) {
            return MIME_TYPE_CHEMICAL_X_GAUSSIAN_LOG;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

chemical_x_gaussian_c_label:
    switch (*str++) {
    case 'h':
    case 'H':
        /* must be 'chemical/x-gaussian-checkpoint' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_GAUSSIAN_CHECKPOINT].name[22])) {
            return MIME_TYPE_CHEMICAL_X_GAUSSIAN_CHECKPOINT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'u':
    case 'U':
        /* must be 'chemical/x-gaussian-cube' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_GAUSSIAN_CUBE].name[22])) {
            return MIME_TYPE_CHEMICAL_X_GAUSSIAN_CUBE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

chemical_x_m_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* skip to prefix 'chemical/x-mac' */
        if (!str_ncasecmp(str, "c", 1)) {
            str += 1;
            goto chemical_x_mac_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'm':
    case 'M':
        /* must be 'chemical/x-mmcif' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_MMCIF].name[13])) {
            return MIME_TYPE_CHEMICAL_X_MMCIF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'd':
    case 'D':
        /* skip to prefix 'chemical/x-mdl-' */
        if (!str_ncasecmp(str, "l-", 2)) {
            str += 2;
            goto chemical_x_mdl__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'o':
    case 'O':
        goto chemical_x_mo_label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

chemical_x_mac_label:
    switch (*str++) {
    case 'r':
    case 'R':
        /* must be 'chemical/x-macromodel-input' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_MACROMODEL_INPUT].name[15])) {
            return MIME_TYPE_CHEMICAL_X_MACROMODEL_INPUT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'm':
    case 'M':
        /* must be 'chemical/x-macmolecule' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_MACMOLECULE].name[15])) {
            return MIME_TYPE_CHEMICAL_X_MACMOLECULE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

chemical_x_mdl__label:
    switch (*str++) {
    case 's':
    case 'S':
        /* must be 'chemical/x-mdl-sdfile' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_MDL_SDFILE].name[16])) {
            return MIME_TYPE_CHEMICAL_X_MDL_SDFILE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'r':
    case 'R':
        goto chemical_x_mdl_r_label;

    case 'm':
    case 'M':
        /* must be 'chemical/x-mdl-molfile' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_MDL_MOLFILE].name[16])) {
            return MIME_TYPE_CHEMICAL_X_MDL_MOLFILE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 't':
    case 'T':
        /* must be 'chemical/x-mdl-tgf' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_MDL_TGF].name[16])) {
            return MIME_TYPE_CHEMICAL_X_MDL_TGF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

chemical_x_mdl_r_label:
    switch (*str++) {
    case 'x':
    case 'X':
        /* must be 'chemical/x-mdl-rxnfile' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_MDL_RXNFILE].name[17])) {
            return MIME_TYPE_CHEMICAL_X_MDL_RXNFILE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'd':
    case 'D':
        /* must be 'chemical/x-mdl-rdfile' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_MDL_RDFILE].name[17])) {
            return MIME_TYPE_CHEMICAL_X_MDL_RDFILE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

chemical_x_mo_label:
    switch (*str++) {
    case 'p':
    case 'P':
        /* skip to prefix 'chemical/x-mopac-' */
        if (!str_ncasecmp(str, "ac-", 3)) {
            str += 3;
            goto chemical_x_mopac__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'l':
    case 'L':
        goto chemical_x_mol_label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

chemical_x_mopac__label:
    switch (*str++) {
    case 'i':
    case 'I':
        /* must be 'chemical/x-mopac-input' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_MOPAC_INPUT].name[18])) {
            return MIME_TYPE_CHEMICAL_X_MOPAC_INPUT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'o':
    case 'O':
        /* must be 'chemical/x-mopac-out' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_MOPAC_OUT].name[18])) {
            return MIME_TYPE_CHEMICAL_X_MOPAC_OUT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'g':
    case 'G':
        /* must be 'chemical/x-mopac-graph' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_MOPAC_GRAPH].name[18])) {
            return MIME_TYPE_CHEMICAL_X_MOPAC_GRAPH;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'v':
    case 'V':
        /* must be 'chemical/x-mopac-vib' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_MOPAC_VIB].name[18])) {
            return MIME_TYPE_CHEMICAL_X_MOPAC_VIB;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

chemical_x_mol_label:
    switch (*str++) {
    case 'c':
    case 'C':
        /* must be 'chemical/x-molconn-z' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_MOLCONN_Z].name[15])) {
            return MIME_TYPE_CHEMICAL_X_MOLCONN_Z;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case '2':
        /* must be 'chemical/x-mol2' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_MOL2].name[15])) {
            return MIME_TYPE_CHEMICAL_X_MOL2;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

chemical_x_ncbi_asn1_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_CHEMICAL_X_NCBI_ASN1;

    case '-':
        goto chemical_x_ncbi_asn1__label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

chemical_x_ncbi_asn1__label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'chemical/x-ncbi-asn1-ascii' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_NCBI_ASN1_ASCII].name[22])) {
            return MIME_TYPE_CHEMICAL_X_NCBI_ASN1_ASCII;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* must be 'chemical/x-ncbi-asn1-spec' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_NCBI_ASN1_SPEC].name[22])) {
            return MIME_TYPE_CHEMICAL_X_NCBI_ASN1_SPEC;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'b':
    case 'B':
        /* must be 'chemical/x-ncbi-asn1-binary' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_NCBI_ASN1_BINARY].name[22])) {
            return MIME_TYPE_CHEMICAL_X_NCBI_ASN1_BINARY;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

chemical_x_v_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'chemical/x-vamas-iso14976' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_VAMAS_ISO14976].name[13])) {
            return MIME_TYPE_CHEMICAL_X_VAMAS_ISO14976;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'm':
    case 'M':
        /* must be 'chemical/x-vmd' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_VMD].name[13])) {
            return MIME_TYPE_CHEMICAL_X_VMD;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

chemical_x_x_label:
    switch (*str++) {
    case 'y':
    case 'Y':
        /* must be 'chemical/x-xyz' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_XYZ].name[13])) {
            return MIME_TYPE_CHEMICAL_X_XYZ;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 't':
    case 'T':
        /* must be 'chemical/x-xtel' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_CHEMICAL_X_XTEL].name[13])) {
            return MIME_TYPE_CHEMICAL_X_XTEL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

i_label:
    switch (*str++) {
    case 'm':
    case 'M':
        /* skip to prefix 'image/' */
        if (!str_ncasecmp(str, "age/", 4)) {
            str += 4;
            goto image__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'n':
    case 'N':
        /* skip to prefix 'inode/' */
        if (!str_ncasecmp(str, "ode/", 4)) {
            str += 4;
            goto inode__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

image__label:
    switch (*str++) {
    case 'c':
    case 'C':
        /* must be 'image/cgm' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_CGM].name[7])) {
            return MIME_TYPE_IMAGE_CGM;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'g':
    case 'G':
        goto image_g_label;

    case 'i':
    case 'I':
        /* must be 'image/ief' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_IEF].name[7])) {
            return MIME_TYPE_IMAGE_IEF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'j':
    case 'J':
        /* must be 'image/jpeg' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_JPEG].name[7])) {
            return MIME_TYPE_IMAGE_JPEG;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'n':
    case 'N':
        /* must be 'image/naplps' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_NAPLPS].name[7])) {
            return MIME_TYPE_IMAGE_NAPLPS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'p':
    case 'P':
        goto image_p_label;

    case 's':
    case 'S':
        /* must be 'image/svg+xml' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_SVG_XML].name[7])) {
            return MIME_TYPE_IMAGE_SVG_XML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 't':
    case 'T':
        /* must be 'image/tiff' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_TIFF].name[7])) {
            return MIME_TYPE_IMAGE_TIFF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'v':
    case 'V':
        /* skip to prefix 'image/vnd.' */
        if (!str_ncasecmp(str, "nd.", 3)) {
            str += 3;
            goto image_vnd__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'x':
    case 'X':
        /* skip to prefix 'image/x-' */
        if (!str_ncasecmp(str, "-", 1)) {
            str += 1;
            goto image_x__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

image_g_label:
    switch (*str++) {
    case 'i':
    case 'I':
        /* must be 'image/gif' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_GIF].name[8])) {
            return MIME_TYPE_IMAGE_GIF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case '3':
        /* must be 'image/g3fax' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_G3FAX].name[8])) {
            return MIME_TYPE_IMAGE_G3FAX;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

image_p_label:
    switch (*str++) {
    case 'c':
    case 'C':
        /* must be 'image/pcx' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_PCX].name[8])) {
            return MIME_TYPE_IMAGE_PCX;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'r':
    case 'R':
        /* skip to prefix 'image/prs.' */
        if (!str_ncasecmp(str, "s.", 2)) {
            str += 2;
            goto image_prs__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'n':
    case 'N':
        /* must be 'image/png' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_PNG].name[8])) {
            return MIME_TYPE_IMAGE_PNG;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

image_prs__label:
    switch (*str++) {
    case 'p':
    case 'P':
        /* must be 'image/prs.pti' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_PRS_PTI].name[11])) {
            return MIME_TYPE_IMAGE_PRS_PTI;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'b':
    case 'B':
        /* must be 'image/prs.btif' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_PRS_BTIF].name[11])) {
            return MIME_TYPE_IMAGE_PRS_BTIF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

image_vnd__label:
    switch (*str++) {
    case 'c':
    case 'C':
        /* must be 'image/vnd.cns.inf2' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_VND_CNS_INF2].name[11])) {
            return MIME_TYPE_IMAGE_VND_CNS_INF2;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'd':
    case 'D':
        goto image_vnd_d_label;

    case 'f':
    case 'F':
        goto image_vnd_f_label;

    case 'm':
    case 'M':
        /* must be 'image/vnd.mix' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_VND_MIX].name[11])) {
            return MIME_TYPE_IMAGE_VND_MIX;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'n':
    case 'N':
        /* must be 'image/vnd.net-fpx' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_VND_NET_FPX].name[11])) {
            return MIME_TYPE_IMAGE_VND_NET_FPX;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* must be 'image/vnd.svf' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_VND_SVF].name[11])) {
            return MIME_TYPE_IMAGE_VND_SVF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'w':
    case 'W':
        /* must be 'image/vnd.wap.wbmp' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_VND_WAP_WBMP].name[11])) {
            return MIME_TYPE_IMAGE_VND_WAP_WBMP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'x':
    case 'X':
        /* must be 'image/vnd.xiff' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_VND_XIFF].name[11])) {
            return MIME_TYPE_IMAGE_VND_XIFF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

image_vnd_d_label:
    switch (*str++) {
    case 'x':
    case 'X':
        /* must be 'image/vnd.dxf' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_VND_DXF].name[12])) {
            return MIME_TYPE_IMAGE_VND_DXF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'j':
    case 'J':
        /* must be 'image/vnd.djvu' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_VND_DJVU].name[12])) {
            return MIME_TYPE_IMAGE_VND_DJVU;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'w':
    case 'W':
        /* must be 'image/vnd.dwg' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_VND_DWG].name[12])) {
            return MIME_TYPE_IMAGE_VND_DWG;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

image_vnd_f_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'image/vnd.fastbidsheet' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_VND_FASTBIDSHEET].name[12])) {
            return MIME_TYPE_IMAGE_VND_FASTBIDSHEET;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'p':
    case 'P':
        /* must be 'image/vnd.fpx' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_VND_FPX].name[12])) {
            return MIME_TYPE_IMAGE_VND_FPX;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* must be 'image/vnd.fst' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_VND_FST].name[12])) {
            return MIME_TYPE_IMAGE_VND_FST;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'u':
    case 'U':
        /* skip to prefix 'image/vnd.fujixerox.edmics-' */
        if (!str_ncasecmp(str, "jixerox.edmics-", 15)) {
            str += 15;
            goto image_vnd_fujixerox_edmics__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

image_vnd_fujixerox_edmics__label:
    switch (*str++) {
    case 'r':
    case 'R':
        /* must be 'image/vnd.fujixerox.edmics-rlc' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_VND_FUJIXEROX_EDMICS_RLC].name[28])) {
            return MIME_TYPE_IMAGE_VND_FUJIXEROX_EDMICS_RLC;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'm':
    case 'M':
        /* must be 'image/vnd.fujixerox.edmics-mmr' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_VND_FUJIXEROX_EDMICS_MMR].name[28])) {
            return MIME_TYPE_IMAGE_VND_FUJIXEROX_EDMICS_MMR;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

image_x__label:
    switch (*str++) {
    case 'c':
    case 'C':
        goto image_x_c_label;

    case 'i':
    case 'I':
        /* must be 'image/x-icon' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_X_ICON].name[9])) {
            return MIME_TYPE_IMAGE_X_ICON;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'j':
    case 'J':
        goto image_x_j_label;

    case 'm':
    case 'M':
        /* must be 'image/x-ms-bmp' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_X_MS_BMP].name[9])) {
            return MIME_TYPE_IMAGE_X_MS_BMP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'p':
    case 'P':
        goto image_x_p_label;

    case 'r':
    case 'R':
        /* must be 'image/x-rgb' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_X_RGB].name[9])) {
            return MIME_TYPE_IMAGE_X_RGB;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'x':
    case 'X':
        goto image_x_x_label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

image_x_c_label:
    switch (*str++) {
    case 'm':
    case 'M':
        /* must be 'image/x-cmu-raster' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_X_CMU_RASTER].name[10])) {
            return MIME_TYPE_IMAGE_X_CMU_RASTER;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'o':
    case 'O':
        /* skip to prefix 'image/x-corel' */
        if (!str_ncasecmp(str, "rel", 3)) {
            str += 3;
            goto image_x_corel_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

image_x_corel_label:
    switch (*str++) {
    case 'p':
    case 'P':
        /* must be 'image/x-corelphotopaint' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_X_CORELPHOTOPAINT].name[14])) {
            return MIME_TYPE_IMAGE_X_CORELPHOTOPAINT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'd':
    case 'D':
        /* skip to prefix 'image/x-coreldraw' */
        if (!str_ncasecmp(str, "raw", 3)) {
            str += 3;
            goto image_x_coreldraw_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

image_x_coreldraw_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_IMAGE_X_CORELDRAW;

    case 'p':
    case 'P':
        /* must be 'image/x-coreldrawpattern' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_X_CORELDRAWPATTERN].name[18])) {
            return MIME_TYPE_IMAGE_X_CORELDRAWPATTERN;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 't':
    case 'T':
        /* must be 'image/x-coreldrawtemplate' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_X_CORELDRAWTEMPLATE].name[18])) {
            return MIME_TYPE_IMAGE_X_CORELDRAWTEMPLATE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

image_x_j_label:
    switch (*str++) {
    case 'g':
    case 'G':
        /* must be 'image/x-jg' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_X_JG].name[10])) {
            return MIME_TYPE_IMAGE_X_JG;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'n':
    case 'N':
        /* must be 'image/x-jng' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_X_JNG].name[10])) {
            return MIME_TYPE_IMAGE_X_JNG;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

image_x_p_label:
    switch (*str++) {
    case 'h':
    case 'H':
        /* must be 'image/x-photoshop' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_X_PHOTOSHOP].name[10])) {
            return MIME_TYPE_IMAGE_X_PHOTOSHOP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'o':
    case 'O':
        /* skip to prefix 'image/x-portable-' */
        if (!str_ncasecmp(str, "rtable-", 7)) {
            str += 7;
            goto image_x_portable__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

image_x_portable__label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'image/x-portable-anymap' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_X_PORTABLE_ANYMAP].name[18])) {
            return MIME_TYPE_IMAGE_X_PORTABLE_ANYMAP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'p':
    case 'P':
        /* must be 'image/x-portable-pixmap' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_X_PORTABLE_PIXMAP].name[18])) {
            return MIME_TYPE_IMAGE_X_PORTABLE_PIXMAP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'b':
    case 'B':
        /* must be 'image/x-portable-bitmap' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_X_PORTABLE_BITMAP].name[18])) {
            return MIME_TYPE_IMAGE_X_PORTABLE_BITMAP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'g':
    case 'G':
        /* must be 'image/x-portable-graymap' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_X_PORTABLE_GRAYMAP].name[18])) {
            return MIME_TYPE_IMAGE_X_PORTABLE_GRAYMAP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

image_x_x_label:
    switch (*str++) {
    case 'p':
    case 'P':
        /* must be 'image/x-xpixmap' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_X_XPIXMAP].name[10])) {
            return MIME_TYPE_IMAGE_X_XPIXMAP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'b':
    case 'B':
        /* must be 'image/x-xbitmap' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_X_XBITMAP].name[10])) {
            return MIME_TYPE_IMAGE_X_XBITMAP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'w':
    case 'W':
        /* must be 'image/x-xwindowdump' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_IMAGE_X_XWINDOWDUMP].name[10])) {
            return MIME_TYPE_IMAGE_X_XWINDOWDUMP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

inode__label:
    switch (*str++) {
    case 's':
    case 'S':
        /* must be 'inode/socket' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_INODE_SOCKET].name[7])) {
            return MIME_TYPE_INODE_SOCKET;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'c':
    case 'C':
        /* must be 'inode/chardevice' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_INODE_CHARDEVICE].name[7])) {
            return MIME_TYPE_INODE_CHARDEVICE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'b':
    case 'B':
        /* must be 'inode/blockdevice' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_INODE_BLOCKDEVICE].name[7])) {
            return MIME_TYPE_INODE_BLOCKDEVICE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'd':
    case 'D':
        /* skip to prefix 'inode/directory' */
        if (!str_ncasecmp(str, "irectory", 8)) {
            str += 8;
            goto inode_directory_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'f':
    case 'F':
        /* must be 'inode/fifo' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_INODE_FIFO].name[7])) {
            return MIME_TYPE_INODE_FIFO;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

inode_directory_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_INODE_DIRECTORY;

    case '-':
        /* must be 'inode/directory-locked' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_INODE_DIRECTORY_LOCKED].name[16])) {
            return MIME_TYPE_INODE_DIRECTORY_LOCKED;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

m_label:
    switch (*str++) {
    case 'u':
    case 'U':
        /* skip to prefix 'multipart/' */
        if (!str_ncasecmp(str, "ltipart/", 8)) {
            str += 8;
            goto multipart__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'e':
    case 'E':
        /* skip to prefix 'message/' */
        if (!str_ncasecmp(str, "ssage/", 6)) {
            str += 6;
            goto message__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'o':
    case 'O':
        /* skip to prefix 'model/' */
        if (!str_ncasecmp(str, "del/", 4)) {
            str += 4;
            goto model__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

multipart__label:
    switch (*str++) {
    case 'a':
    case 'A':
        goto multipart_a_label;

    case 'b':
    case 'B':
        /* must be 'multipart/byteranges' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MULTIPART_BYTERANGES].name[11])) {
            return MIME_TYPE_MULTIPART_BYTERANGES;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'e':
    case 'E':
        /* must be 'multipart/encrypted' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MULTIPART_ENCRYPTED].name[11])) {
            return MIME_TYPE_MULTIPART_ENCRYPTED;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'd':
    case 'D':
        /* must be 'multipart/digest' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MULTIPART_DIGEST].name[11])) {
            return MIME_TYPE_MULTIPART_DIGEST;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'f':
    case 'F':
        /* must be 'multipart/form-data' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MULTIPART_FORM_DATA].name[11])) {
            return MIME_TYPE_MULTIPART_FORM_DATA;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'h':
    case 'H':
        /* must be 'multipart/header-set' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MULTIPART_HEADER_SET].name[11])) {
            return MIME_TYPE_MULTIPART_HEADER_SET;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'm':
    case 'M':
        /* must be 'multipart/mixed' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MULTIPART_MIXED].name[11])) {
            return MIME_TYPE_MULTIPART_MIXED;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'p':
    case 'P':
        /* must be 'multipart/parallel' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MULTIPART_PARALLEL].name[11])) {
            return MIME_TYPE_MULTIPART_PARALLEL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* must be 'multipart/signed' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MULTIPART_SIGNED].name[11])) {
            return MIME_TYPE_MULTIPART_SIGNED;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'r':
    case 'R':
        /* skip to prefix 'multipart/re' */
        if (!str_ncasecmp(str, "e", 1)) {
            str += 1;
            goto multipart_re_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'v':
    case 'V':
        /* must be 'multipart/voice-message' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MULTIPART_VOICE_MESSAGE].name[11])) {
            return MIME_TYPE_MULTIPART_VOICE_MESSAGE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

multipart_a_label:
    switch (*str++) {
    case 'p':
    case 'P':
        /* must be 'multipart/appledouble' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MULTIPART_APPLEDOUBLE].name[12])) {
            return MIME_TYPE_MULTIPART_APPLEDOUBLE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'l':
    case 'L':
        /* must be 'multipart/alternative' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MULTIPART_ALTERNATIVE].name[12])) {
            return MIME_TYPE_MULTIPART_ALTERNATIVE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

multipart_re_label:
    switch (*str++) {
    case 'p':
    case 'P':
        /* must be 'multipart/report' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MULTIPART_REPORT].name[13])) {
            return MIME_TYPE_MULTIPART_REPORT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'l':
    case 'L':
        /* must be 'multipart/related' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MULTIPART_RELATED].name[13])) {
            return MIME_TYPE_MULTIPART_RELATED;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

message__label:
    switch (*str++) {
    case 'e':
    case 'E':
        /* must be 'message/external-body' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MESSAGE_EXTERNAL_BODY].name[9])) {
            return MIME_TYPE_MESSAGE_EXTERNAL_BODY;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'd':
    case 'D':
        goto message_d_label;

    case 'h':
    case 'H':
        /* must be 'message/http' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MESSAGE_HTTP].name[9])) {
            return MIME_TYPE_MESSAGE_HTTP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'n':
    case 'N':
        /* must be 'message/news' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MESSAGE_NEWS].name[9])) {
            return MIME_TYPE_MESSAGE_NEWS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'p':
    case 'P':
        /* must be 'message/partial' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MESSAGE_PARTIAL].name[9])) {
            return MIME_TYPE_MESSAGE_PARTIAL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* must be 'message/s-http' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MESSAGE_S_HTTP].name[9])) {
            return MIME_TYPE_MESSAGE_S_HTTP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'r':
    case 'R':
        /* must be 'message/rfc822' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MESSAGE_RFC822].name[9])) {
            return MIME_TYPE_MESSAGE_RFC822;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

message_d_label:
    switch (*str++) {
    case 'i':
    case 'I':
        /* must be 'message/disposition-notification' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MESSAGE_DISPOSITION_NOTIFICATION].name[10])) {
            return MIME_TYPE_MESSAGE_DISPOSITION_NOTIFICATION;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'e':
    case 'E':
        /* must be 'message/delivery-status' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MESSAGE_DELIVERY_STATUS].name[10])) {
            return MIME_TYPE_MESSAGE_DELIVERY_STATUS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

model__label:
    switch (*str++) {
    case 'i':
    case 'I':
        /* must be 'model/iges' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MODEL_IGES].name[7])) {
            return MIME_TYPE_MODEL_IGES;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'm':
    case 'M':
        /* must be 'model/mesh' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MODEL_MESH].name[7])) {
            return MIME_TYPE_MODEL_MESH;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'v':
    case 'V':
        goto model_v_label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

model_v_label:
    switch (*str++) {
    case 'r':
    case 'R':
        /* must be 'model/vrml' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MODEL_VRML].name[8])) {
            return MIME_TYPE_MODEL_VRML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'n':
    case 'N':
        /* skip to prefix 'model/vnd.' */
        if (!str_ncasecmp(str, "d.", 2)) {
            str += 2;
            goto model_vnd__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

model_vnd__label:
    switch (*str++) {
    case 'd':
    case 'D':
        /* must be 'model/vnd.dwf' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MODEL_VND_DWF].name[11])) {
            return MIME_TYPE_MODEL_VND_DWF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'g':
    case 'G':
        goto model_vnd_g_label;

    case 'f':
    case 'F':
        /* must be 'model/vnd.flatland.3dml' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MODEL_VND_FLATLAND_3DML].name[11])) {
            return MIME_TYPE_MODEL_VND_FLATLAND_3DML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'm':
    case 'M':
        /* must be 'model/vnd.mts' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MODEL_VND_MTS].name[11])) {
            return MIME_TYPE_MODEL_VND_MTS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'p':
    case 'P':
        /* skip to prefix 'model/vnd.parasolid.transmit.' */
        if (!str_ncasecmp(str, "arasolid.transmit.", 18)) {
            str += 18;
            goto model_vnd_parasolid_transmit__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'v':
    case 'V':
        /* must be 'model/vnd.vtu' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MODEL_VND_VTU].name[11])) {
            return MIME_TYPE_MODEL_VND_VTU;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

model_vnd_g_label:
    switch (*str++) {
    case 's':
    case 'S':
        /* must be 'model/vnd.gs-gdl' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MODEL_VND_GS_GDL].name[12])) {
            return MIME_TYPE_MODEL_VND_GS_GDL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'd':
    case 'D':
        /* must be 'model/vnd.gdl' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MODEL_VND_GDL].name[12])) {
            return MIME_TYPE_MODEL_VND_GDL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 't':
    case 'T':
        /* must be 'model/vnd.gtw' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MODEL_VND_GTW].name[12])) {
            return MIME_TYPE_MODEL_VND_GTW;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

model_vnd_parasolid_transmit__label:
    switch (*str++) {
    case 'b':
    case 'B':
        /* must be 'model/vnd.parasolid.transmit.binary' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MODEL_VND_PARASOLID_TRANSMIT_BINARY].name[30])) {
            return MIME_TYPE_MODEL_VND_PARASOLID_TRANSMIT_BINARY;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 't':
    case 'T':
        /* must be 'model/vnd.parasolid.transmit.text' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_MODEL_VND_PARASOLID_TRANSMIT_TEXT].name[30])) {
            return MIME_TYPE_MODEL_VND_PARASOLID_TRANSMIT_TEXT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text__label:
    switch (*str++) {
    case 'c':
    case 'C':
        goto text_c_label;

    case 'e':
    case 'E':
        /* skip to prefix 'text/en' */
        if (!str_ncasecmp(str, "n", 1)) {
            str += 1;
            goto text_en_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'd':
    case 'D':
        /* must be 'text/directory' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_DIRECTORY].name[6])) {
            return MIME_TYPE_TEXT_DIRECTORY;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'i':
    case 'I':
        /* must be 'text/iuls' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_IULS].name[6])) {
            return MIME_TYPE_TEXT_IULS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'h':
    case 'H':
        goto text_h_label;

    case 'm':
    case 'M':
        /* must be 'text/mathml' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_MATHML].name[6])) {
            return MIME_TYPE_TEXT_MATHML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'p':
    case 'P':
        goto text_p_label;

    case 's':
    case 'S':
        goto text_s_label;

    case 'r':
    case 'R':
        goto text_r_label;

    case 'u':
    case 'U':
        /* must be 'text/uri-list' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_URI_LIST].name[6])) {
            return MIME_TYPE_TEXT_URI_LIST;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 't':
    case 'T':
        goto text_t_label;

    case 'v':
    case 'V':
        /* skip to prefix 'text/vnd.' */
        if (!str_ncasecmp(str, "nd.", 3)) {
            str += 3;
            goto text_vnd__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'x':
    case 'X':
        goto text_x_label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_c_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'text/calendar' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_CALENDAR].name[7])) {
            return MIME_TYPE_TEXT_CALENDAR;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        goto text_cs_label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_cs_label:
    switch (*str++) {
    case 's':
    case 'S':
        /* must be 'text/css' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_CSS].name[8])) {
            return MIME_TYPE_TEXT_CSS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'v':
    case 'V':
        /* must be 'text/csv' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_CSV].name[8])) {
            return MIME_TYPE_TEXT_CSV;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_en_label:
    switch (*str++) {
    case 'r':
    case 'R':
        /* must be 'text/enriched' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_ENRICHED].name[8])) {
            return MIME_TYPE_TEXT_ENRICHED;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'g':
    case 'G':
        /* must be 'text/english' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_ENGLISH].name[8])) {
            return MIME_TYPE_TEXT_ENGLISH;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_h_label:
    switch (*str++) {
    case '3':
        /* must be 'text/h323' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_H323].name[7])) {
            return MIME_TYPE_TEXT_H323;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 't':
    case 'T':
        /* must be 'text/html' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_HTML].name[7])) {
            return MIME_TYPE_TEXT_HTML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_p_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'text/parityfec' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_PARITYFEC].name[7])) {
            return MIME_TYPE_TEXT_PARITYFEC;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'r':
    case 'R':
        /* must be 'text/prs.lines.tag' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_PRS_LINES_TAG].name[7])) {
            return MIME_TYPE_TEXT_PRS_LINES_TAG;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'l':
    case 'L':
        /* must be 'text/plain' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_PLAIN].name[7])) {
            return MIME_TYPE_TEXT_PLAIN;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_s_label:
    switch (*str++) {
    case 'c':
    case 'C':
        /* must be 'text/scriptlet' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_SCRIPTLET].name[7])) {
            return MIME_TYPE_TEXT_SCRIPTLET;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'g':
    case 'G':
        /* must be 'text/sgml' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_SGML].name[7])) {
            return MIME_TYPE_TEXT_SGML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_r_label:
    switch (*str++) {
    case 'i':
    case 'I':
        /* must be 'text/richtext' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_RICHTEXT].name[7])) {
            return MIME_TYPE_TEXT_RICHTEXT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 't':
    case 'T':
        /* must be 'text/rtf' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_RTF].name[7])) {
            return MIME_TYPE_TEXT_RTF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'f':
    case 'F':
        /* must be 'text/rfc822-headers' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_RFC822_HEADERS].name[7])) {
            return MIME_TYPE_TEXT_RFC822_HEADERS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_t_label:
    switch (*str++) {
    case '1':
        /* must be 'text/t140' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_T140].name[7])) {
            return MIME_TYPE_TEXT_T140;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'a':
    case 'A':
        /* must be 'text/tab-separated-values' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_TAB_SEPARATED_VALUES].name[7])) {
            return MIME_TYPE_TEXT_TAB_SEPARATED_VALUES;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'e':
    case 'E':
        /* must be 'text/texmacs' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_TEXMACS].name[7])) {
            return MIME_TYPE_TEXT_TEXMACS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_vnd__label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'text/vnd.abc' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_VND_ABC].name[10])) {
            return MIME_TYPE_TEXT_VND_ABC;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'c':
    case 'C':
        /* must be 'text/vnd.curl' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_VND_CURL].name[10])) {
            return MIME_TYPE_TEXT_VND_CURL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'd':
    case 'D':
        /* must be 'text/vnd.dmclientscript' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_VND_DMCLIENTSCRIPT].name[10])) {
            return MIME_TYPE_TEXT_VND_DMCLIENTSCRIPT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'f':
    case 'F':
        goto text_vnd_f_label;

    case 'i':
    case 'I':
        goto text_vnd_i_label;

    case 'm':
    case 'M':
        goto text_vnd_m_label;

    case 'l':
    case 'L':
        /* must be 'text/vnd.latex-z' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_VND_LATEX_Z].name[10])) {
            return MIME_TYPE_TEXT_VND_LATEX_Z;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* must be 'text/vnd.sun.j2me.app-descriptor' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_VND_SUN_J2ME_APP_DESCRIPTOR].name[10])) {
            return MIME_TYPE_TEXT_VND_SUN_J2ME_APP_DESCRIPTOR;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'w':
    case 'W':
        /* skip to prefix 'text/vnd.wap.' */
        if (!str_ncasecmp(str, "ap.", 3)) {
            str += 3;
            goto text_vnd_wap__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_vnd_f_label:
    switch (*str++) {
    case 'm':
    case 'M':
        /* must be 'text/vnd.fmi.flexstor' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_VND_FMI_FLEXSTOR].name[11])) {
            return MIME_TYPE_TEXT_VND_FMI_FLEXSTOR;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'l':
    case 'L':
        goto text_vnd_fl_label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_vnd_fl_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'text/vnd.flatland.3dml' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_VND_FLATLAND_3DML].name[12])) {
            return MIME_TYPE_TEXT_VND_FLATLAND_3DML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'y':
    case 'Y':
        /* must be 'text/vnd.fly' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_VND_FLY].name[12])) {
            return MIME_TYPE_TEXT_VND_FLY;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_vnd_i_label:
    switch (*str++) {
    case 'p':
    case 'P':
        /* skip to prefix 'text/vnd.iptc.n' */
        if (!str_ncasecmp(str, "tc.n", 4)) {
            str += 4;
            goto text_vnd_iptc_n_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'n':
    case 'N':
        /* skip to prefix 'text/vnd.in3d.' */
        if (!str_ncasecmp(str, "3d.", 3)) {
            str += 3;
            goto text_vnd_in3d__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_vnd_iptc_n_label:
    switch (*str++) {
    case 'i':
    case 'I':
        /* must be 'text/vnd.iptc.nitf' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_VND_IPTC_NITF].name[16])) {
            return MIME_TYPE_TEXT_VND_IPTC_NITF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'e':
    case 'E':
        /* must be 'text/vnd.iptc.newsml' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_VND_IPTC_NEWSML].name[16])) {
            return MIME_TYPE_TEXT_VND_IPTC_NEWSML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_vnd_in3d__label:
    switch (*str++) {
    case '3':
        /* must be 'text/vnd.in3d.3dml' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_VND_IN3D_3DML].name[15])) {
            return MIME_TYPE_TEXT_VND_IN3D_3DML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* must be 'text/vnd.in3d.spot' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_VND_IN3D_SPOT].name[15])) {
            return MIME_TYPE_TEXT_VND_IN3D_SPOT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_vnd_m_label:
    switch (*str++) {
    case 's':
    case 'S':
        /* must be 'text/vnd.ms-mediapackage' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_VND_MS_MEDIAPACKAGE].name[11])) {
            return MIME_TYPE_TEXT_VND_MS_MEDIAPACKAGE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'o':
    case 'O':
        /* must be 'text/vnd.motorola.reflex' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_VND_MOTOROLA_REFLEX].name[11])) {
            return MIME_TYPE_TEXT_VND_MOTOROLA_REFLEX;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_vnd_wap__label:
    switch (*str++) {
    case 's':
    case 'S':
        goto text_vnd_wap_s_label;

    case 'w':
    case 'W':
        /* skip to prefix 'text/vnd.wap.wml' */
        if (!str_ncasecmp(str, "ml", 2)) {
            str += 2;
            goto text_vnd_wap_wml_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_vnd_wap_s_label:
    switch (*str++) {
    case 'i':
    case 'I':
        /* must be 'text/vnd.wap.si' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_VND_WAP_SI].name[15])) {
            return MIME_TYPE_TEXT_VND_WAP_SI;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'l':
    case 'L':
        /* must be 'text/vnd.wap.sl' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_VND_WAP_SL].name[15])) {
            return MIME_TYPE_TEXT_VND_WAP_SL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_vnd_wap_wml_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_TEXT_VND_WAP_WML;

    case 's':
    case 'S':
        /* must be 'text/vnd.wap.wmlscript' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_VND_WAP_WMLSCRIPT].name[17])) {
            return MIME_TYPE_TEXT_VND_WAP_WMLSCRIPT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_x_label:
    switch (*str++) {
    case 'm':
    case 'M':
        /* skip to prefix 'text/xml' */
        if (!str_ncasecmp(str, "l", 1)) {
            str += 1;
            goto text_xml_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case '-':
        goto text_x__label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_xml_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_TEXT_XML;

    case '-':
        /* must be 'text/xml-external-parsed-entity' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_XML_EXTERNAL_PARSED_ENTITY].name[9])) {
            return MIME_TYPE_TEXT_XML_EXTERNAL_PARSED_ENTITY;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_x__label:
    switch (*str++) {
    case 'c':
    case 'C':
        goto text_x_c_label;

    case 'b':
    case 'B':
        goto text_x_b_label;

    case 'd':
    case 'D':
        goto text_x_d_label;

    case 'h':
    case 'H':
        /* must be 'text/x-haskell' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_X_HASKELL].name[8])) {
            return MIME_TYPE_TEXT_X_HASKELL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'j':
    case 'J':
        /* must be 'text/x-java' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_X_JAVA].name[8])) {
            return MIME_TYPE_TEXT_X_JAVA;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'm':
    case 'M':
        goto text_x_m_label;

    case 'l':
    case 'L':
        /* must be 'text/x-literate-haskell' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_X_LITERATE_HASKELL].name[8])) {
            return MIME_TYPE_TEXT_X_LITERATE_HASKELL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'p':
    case 'P':
        goto text_x_p_label;

    case 's':
    case 'S':
        goto text_x_s_label;

    case 't':
    case 'T':
        goto text_x_t_label;

    case 'v':
    case 'V':
        /* skip to prefix 'text/x-vca' */
        if (!str_ncasecmp(str, "ca", 2)) {
            str += 2;
            goto text_x_vca_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_x_c_label:
    switch (*str++) {
    case 'h':
    case 'H':
        /* must be 'text/x-chdr' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_X_CHDR].name[9])) {
            return MIME_TYPE_TEXT_X_CHDR;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case '+':
        /* skip to prefix 'text/x-c++' */
        if (!str_ncasecmp(str, "+", 1)) {
            str += 1;
            goto text_x_c___label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'r':
    case 'R':
        /* must be 'text/x-crontab' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_X_CRONTAB].name[9])) {
            return MIME_TYPE_TEXT_X_CRONTAB;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        goto text_x_cs_label;

    case 'o':
    case 'O':
        /* must be 'text/x-component' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_X_COMPONENT].name[9])) {
            return MIME_TYPE_TEXT_X_COMPONENT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_x_c___label:
    switch (*str++) {
    case 'h':
    case 'H':
        /* must be 'text/x-c++hdr' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_X_C__HDR].name[11])) {
            return MIME_TYPE_TEXT_X_C__HDR;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* must be 'text/x-c++src' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_X_C__SRC].name[11])) {
            return MIME_TYPE_TEXT_X_C__SRC;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_x_cs_label:
    switch (*str++) {
    case 'h':
    case 'H':
        /* must be 'text/x-csh' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_X_CSH].name[10])) {
            return MIME_TYPE_TEXT_X_CSH;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'r':
    case 'R':
        /* must be 'text/x-csrc' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_X_CSRC].name[10])) {
            return MIME_TYPE_TEXT_X_CSRC;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_x_b_label:
    switch (*str++) {
    case 'i':
    case 'I':
        /* must be 'text/x-bibtex' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_X_BIBTEX].name[9])) {
            return MIME_TYPE_TEXT_X_BIBTEX;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'o':
    case 'O':
        /* must be 'text/x-boo' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_X_BOO].name[9])) {
            return MIME_TYPE_TEXT_X_BOO;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_x_d_label:
    switch (*str++) {
    case 'i':
    case 'I':
        /* must be 'text/x-diff' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_X_DIFF].name[9])) {
            return MIME_TYPE_TEXT_X_DIFF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 's':
    case 'S':
        /* must be 'text/x-dsrc' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_X_DSRC].name[9])) {
            return MIME_TYPE_TEXT_X_DSRC;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_x_m_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'text/x-makefile' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_X_MAKEFILE].name[9])) {
            return MIME_TYPE_TEXT_X_MAKEFILE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'o':
    case 'O':
        /* must be 'text/x-moc' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_X_MOC].name[9])) {
            return MIME_TYPE_TEXT_X_MOC;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_x_p_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'text/x-pascal' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_X_PASCAL].name[9])) {
            return MIME_TYPE_TEXT_X_PASCAL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'y':
    case 'Y':
        /* must be 'text/x-python' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_X_PYTHON].name[9])) {
            return MIME_TYPE_TEXT_X_PYTHON;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'c':
    case 'C':
        /* must be 'text/x-pcs-gcd' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_X_PCS_GCD].name[9])) {
            return MIME_TYPE_TEXT_X_PCS_GCD;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'e':
    case 'E':
        /* must be 'text/x-perl' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_X_PERL].name[9])) {
            return MIME_TYPE_TEXT_X_PERL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_x_s_label:
    switch (*str++) {
    case 'h':
    case 'H':
        /* must be 'text/x-sh' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_X_SH].name[9])) {
            return MIME_TYPE_TEXT_X_SH;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'e':
    case 'E':
        goto text_x_se_label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_x_se_label:
    switch (*str++) {
    case 'r':
    case 'R':
        /* must be 'text/x-server-parsed-html' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_X_SERVER_PARSED_HTML].name[10])) {
            return MIME_TYPE_TEXT_X_SERVER_PARSED_HTML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 't':
    case 'T':
        /* must be 'text/x-setext' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_X_SETEXT].name[10])) {
            return MIME_TYPE_TEXT_X_SETEXT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_x_t_label:
    switch (*str++) {
    case 'c':
    case 'C':
        /* must be 'text/x-tcl' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_X_TCL].name[9])) {
            return MIME_TYPE_TEXT_X_TCL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'e':
    case 'E':
        /* must be 'text/x-tex' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_X_TEX].name[9])) {
            return MIME_TYPE_TEXT_X_TEX;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

text_x_vca_label:
    switch (*str++) {
    case 'r':
    case 'R':
        /* must be 'text/x-vcard' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_X_VCARD].name[11])) {
            return MIME_TYPE_TEXT_X_VCARD;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'l':
    case 'L':
        /* must be 'text/x-vcalendar' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_TEXT_X_VCALENDAR].name[11])) {
            return MIME_TYPE_TEXT_X_VCALENDAR;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

video__label:
    switch (*str++) {
    case 'd':
    case 'D':
        goto video_d_label;

    case 'g':
    case 'G':
        /* must be 'video/gl' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_VIDEO_GL].name[7])) {
            return MIME_TYPE_VIDEO_GL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'f':
    case 'F':
        /* must be 'video/fli' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_VIDEO_FLI].name[7])) {
            return MIME_TYPE_VIDEO_FLI;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'm':
    case 'M':
        /* skip to prefix 'video/mp' */
        if (!str_ncasecmp(str, "p", 1)) {
            str += 1;
            goto video_mp_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'o':
    case 'O':
        /* must be 'video/ogg' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_VIDEO_OGG].name[7])) {
            return MIME_TYPE_VIDEO_OGG;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'q':
    case 'Q':
        /* must be 'video/quicktime' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_VIDEO_QUICKTIME].name[7])) {
            return MIME_TYPE_VIDEO_QUICKTIME;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'p':
    case 'P':
        goto video_p_label;

    case '3':
        /* must be 'video/3gpp' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_VIDEO_3GPP].name[7])) {
            return MIME_TYPE_VIDEO_3GPP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'v':
    case 'V':
        /* skip to prefix 'video/vnd.' */
        if (!str_ncasecmp(str, "nd.", 3)) {
            str += 3;
            goto video_vnd__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    case 'x':
    case 'X':
        /* skip to prefix 'video/x-' */
        if (!str_ncasecmp(str, "-", 1)) {
            str += 1;
            goto video_x__label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

video_d_label:
    switch (*str++) {
    case 'l':
    case 'L':
        /* must be 'video/dl' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_VIDEO_DL].name[8])) {
            return MIME_TYPE_VIDEO_DL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'v':
    case 'V':
        /* must be 'video/dv' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_VIDEO_DV].name[8])) {
            return MIME_TYPE_VIDEO_DV;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

video_mp_label:
    switch (*str++) {
    case 'e':
    case 'E':
        /* must be 'video/mpeg' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_VIDEO_MPEG].name[9])) {
            return MIME_TYPE_VIDEO_MPEG;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case '4':
        goto video_mp4_label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

video_mp4_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_VIDEO_MP4;

    case 'v':
    case 'V':
        /* must be 'video/mp4v-es' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_VIDEO_MP4V_ES].name[10])) {
            return MIME_TYPE_VIDEO_MP4V_ES;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

video_p_label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'video/parityfec' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_VIDEO_PARITYFEC].name[8])) {
            return MIME_TYPE_VIDEO_PARITYFEC;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'o':
    case 'O':
        /* must be 'video/pointer' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_VIDEO_POINTER].name[8])) {
            return MIME_TYPE_VIDEO_POINTER;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

video_vnd__label:
    switch (*str++) {
    case 'v':
    case 'V':
        /* must be 'video/vnd.vivo' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_VIDEO_VND_VIVO].name[11])) {
            return MIME_TYPE_VIDEO_VND_VIVO;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'n':
    case 'N':
        /* must be 'video/vnd.nokia.interleaved-multimedia' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_VIDEO_VND_NOKIA_INTERLEAVED_MULTIMEDIA].name[11])) {
            return MIME_TYPE_VIDEO_VND_NOKIA_INTERLEAVED_MULTIMEDIA;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'm':
    case 'M':
        goto video_vnd_m_label;

    case 'f':
    case 'F':
        /* must be 'video/vnd.fvt' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_VIDEO_VND_FVT].name[11])) {
            return MIME_TYPE_VIDEO_VND_FVT;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

video_vnd_m_label:
    switch (*str++) {
    case 'p':
    case 'P':
        /* must be 'video/vnd.mpegurl' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_VIDEO_VND_MPEGURL].name[12])) {
            return MIME_TYPE_VIDEO_VND_MPEGURL;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 't':
    case 'T':
        /* must be 'video/vnd.mts' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_VIDEO_VND_MTS].name[12])) {
            return MIME_TYPE_VIDEO_VND_MTS;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'o':
    case 'O':
        /* skip to prefix 'video/vnd.motorola.video' */
        if (!str_ncasecmp(str, "torola.video", 12)) {
            str += 12;
            goto video_vnd_motorola_video_label;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

video_vnd_motorola_video_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_VIDEO_VND_MOTOROLA_VIDEO;

    case 'p':
    case 'P':
        /* must be 'video/vnd.motorola.videop' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_VIDEO_VND_MOTOROLA_VIDEOP].name[25])) {
            return MIME_TYPE_VIDEO_VND_MOTOROLA_VIDEOP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

video_x__label:
    switch (*str++) {
    case 's':
    case 'S':
        /* must be 'video/x-sgi-movie' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_VIDEO_X_SGI_MOVIE].name[9])) {
            return MIME_TYPE_VIDEO_X_SGI_MOVIE;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'm':
    case 'M':
        goto video_x_m_label;

    case 'l':
    case 'L':
        /* must be 'video/x-la-asf' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_VIDEO_X_LA_ASF].name[9])) {
            return MIME_TYPE_VIDEO_X_LA_ASF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

video_x_m_label:
    switch (*str++) {
    case 's':
    case 'S':
        goto video_x_ms_label;

    case 'n':
    case 'N':
        /* must be 'video/x-mng' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_VIDEO_X_MNG].name[10])) {
            return MIME_TYPE_VIDEO_X_MNG;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

video_x_ms_label:
    switch (*str++) {
    case '-':
        goto video_x_ms__label;

    case 'v':
    case 'V':
        /* must be 'video/x-msvideo' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_VIDEO_X_MSVIDEO].name[11])) {
            return MIME_TYPE_VIDEO_X_MSVIDEO;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

video_x_ms__label:
    switch (*str++) {
    case 'a':
    case 'A':
        /* must be 'video/x-ms-asf' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_VIDEO_X_MS_ASF].name[12])) {
            return MIME_TYPE_VIDEO_X_MS_ASF;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'w':
    case 'W':
        goto video_x_ms_w_label;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

video_x_ms_w_label:
    switch (*str++) {
    case 'm':
    case 'M':
        goto video_x_ms_wm_label;

    case 'v':
    case 'V':
        /* must be 'video/x-ms-wvx' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_VIDEO_X_MS_WVX].name[13])) {
            return MIME_TYPE_VIDEO_X_MS_WVX;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

video_x_ms_wm_label:
    switch (*str++) {
    case '\0':
        return MIME_TYPE_VIDEO_X_MS_WM;

    case 'x':
    case 'X':
        /* must be 'video/x-ms-wmx' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_VIDEO_X_MS_WMX].name[14])) {
            return MIME_TYPE_VIDEO_X_MS_WMX;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'v':
    case 'V':
        /* must be 'video/x-ms-wmv' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_VIDEO_X_MS_WMV].name[14])) {
            return MIME_TYPE_VIDEO_X_MS_WMV;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }

x__label:
    switch (*str++) {
    case 'c':
    case 'C':
        /* must be 'x-conference/x-cooltalk' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_X_CONFERENCE_X_COOLTALK].name[3])) {
            return MIME_TYPE_X_CONFERENCE_X_COOLTALK;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'e':
    case 'E':
        /* must be 'x-epoc/x-sisx-app' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_X_EPOC_X_SISX_APP].name[3])) {
            return MIME_TYPE_X_EPOC_X_SISX_APP;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    case 'w':
    case 'W':
        /* must be 'x-world/x-vrml' or unrecognised */
        if (!str_casecmp(str, 
          &lookup[MIME_TYPE_X_WORLD_X_VRML].name[3])) {
            return MIME_TYPE_X_WORLD_X_VRML;
        } else {
            return MIME_TYPE_UNKNOWN_UNKNOWN;
        }
        break;

    default: 
        return MIME_TYPE_UNKNOWN_UNKNOWN;
    }
}

#ifdef MIME_TEST

#include <stdlib.h>
#include <stdio.h>
#include "str.h"

int main() {
    char buf[BUFSIZ + 1];
    enum mime_types mtype;

    while (fgets(buf, BUFSIZ, stdin)) {
        str_rtrim(buf);
        mtype = mime_type(str_ltrim(buf));
        printf("%s\n", mime_string(mtype));
    }

    return EXIT_SUCCESS;
}

#endif

