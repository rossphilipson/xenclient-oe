require recipes-devtools/ghc/ghc-xclib.inc

DESCRIPTION = "Haskell RPC library (wrapper around dbus)"
LICENSE = "LGPLv2.1"
LIC_FILES_CHKSUM = "file://../COPYING;md5=321bf41f280cf805086dd5a720b37785"
DEPENDS = "libxchv4v ghc-native ghc-network-bytestring ghc-hsyslog udbus ghc-transformers-base ghc-monad-control"
RDEPENDS_${PN} += "glibc-gconv-utf-32 ghc-runtime"

PV = "0+git${SRCPV}"

SRCREV = "${AUTOREV}"
SRC_URI = "git://${OPENXT_GIT_MIRROR}/xclibs.git;protocol=${OPENXT_GIT_PROTOCOL};branch=${OPENXT_BRANCH}"
S = "${WORKDIR}/git/xch-rpc"
