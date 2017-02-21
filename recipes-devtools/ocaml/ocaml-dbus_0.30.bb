inherit findlib pkgconfig
SRC_URI[md5sum] = "0137ed32d142c37400b74c7f9c7d4666"
SRC_URI[sha256sum] = "b590666c08f9ae7d134a669e57680a11cdfb1f506ad24deef171119dee902868"
DESCRIPTION = "OCaml DBUS bindings"
DEPENDS = "ocaml-cross ocaml-findlib-cross dbus"
LICENSE = "LGPLv2.1"
LIC_FILES_CHKSUM = "file://LICENSE;md5=f89276652d4738435c98d27fee7c6c7f"

PR = "r6"

S = "${WORKDIR}/ocaml-dbus-${PV}"

SRC_URI = "https://github.com/vincenthz/ocaml-dbus/archive/v0.30.tar.gz \
           file://fix-incorrect-dispatch-statuses.patch;patch=1 \
           file://fix-double-enter-blocking-section.patch;patch=1 \
           file://fix-error-name-lookup.patch;patch=1 \
           file://fix-memleak.patch;patch=1 \
           file://fix-multithread.patch;patch=1 \
"

PARALLEL_MAKE = ""

FILES_${PN} = "${ocamllibdir}/dbus/*${SOLIBS} \
               "
FILES_${PN}-dev = "${ocamllibdir}/dbus/*${SOLIBSDEV}  \
                   ${ocamllibdir}/dbus/*.cm*          \
                   ${ocamllibdir}/dbus/META           \
                  "
FILES_${PN}-staticdev = "${ocamllibdir}/dbus/*.a"
FILES_${PN}-dbg = "${ocamllibdir}/dbus/.debug/*"

INSANE_SKIP_${PN}-dev = "rpaths ldflags"

do_compile() {
	oe_runmake \
		OCAMLC="ocamlc -cc '${CC} -fPIC'" \
		OCAMLOPT="ocamlopt -cc '${CC} -fPIC'" \
		OCAMLMKLIB="ocamlmklib -elfmode -L'${STAGING_DIR_TARGET}/lib' -L'${STAGING_DIR_TARGET}/usr/lib'"

}

do_install() {
	mkdir -p ${D}${ocamllibdir}
	ocamlfind install -destdir ${D}${ocamllibdir} dbus META dBus.cmxa dBus.cma dBus.cmi dlldbus_stubs.so dBus.a libdbus_stubs.a
}
