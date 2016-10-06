LICENSE = "GPLv2 & LGPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=441c28d2cf86e15a37fa47e15a72fbac  \
                    file://COPYING.LIB;md5=79ffa0ec772fa86740948cb7327a0cc7"
DEPENDS = "xen-tools alsa-lib pciutils libpng xen-blktap libv4v openssl zlib libcap-ng libdmbus"

# Leave this in it's own definition so that it can be replaced with a local
# tarball (the QEMU download speed is terrible). If this is combined with the
# other patches, it doesn't seem to work
SRC_URI = "http://wiki.qemu-project.org/download/qemu-${PV}.tar.bz2"

# QEMU Patch Queue
SRC_URI += "file://0001-compile-time-stubdom-flag.patch \
            file://0001-generic-xenstore-extensions.patch \
            file://0001-readonly-ide.patch;striplevel=1 \
            file://0003-hvm-param-dm-domain.patch;striplevel=1 \
            file://0005-logging-syslog.patch;striplevel=1 \
            file://0006-dmbus.patch;striplevel=1 \
            file://0008-switcher.patch;striplevel=1 \
            file://0009-acpi.patch;striplevel=1 \
            file://0013-xenmou.patch;striplevel=1 \
            file://0015-atapi-pass-through.patch;striplevel=1 \
            file://0016-vbe-xt-extensions.patch;striplevel=1 \
            file://0017-vga-spinlock.patch;striplevel=1 \
            file://0018-vga-shadow-bda.patch;striplevel=1 \
            file://0019-surfman-dcl.patch;striplevel=1 \
            file://0020-audio-policy.patch;striplevel=1 \
            file://0023-msix-cap-disable.patch;striplevel=1 \
            file://0024-Xenstore-based-ISO-media-change-detection-for-both-s.patch;striplevel=1 \
            file://0026-openxtaudio.patch;striplevel=1 \
            file://0027-nic-link-state-propagation.patch;striplevel=1 \
            file://0029-stubdom-read-gsi-from-device-config-space.patch;striplevel=1 \
            file://0030-xenfv-i440fx-max-ram-below-4g.patch;striplevel=1 \
            file://0033-acpi-pm-feature.patch;striplevel=1 \
            file://0034-maintain-time-offset.patch;striplevel=1 \
            file://0035-add-acpi-wakeup.patch;striplevel=1 \
            "

SRC_URI[md5sum] = "bdf1f3d0c177ebeb35a079a4bc3fc74e"
SRC_URI[sha256sum] = "9a7ec64f147b9e1e570c410e00ebe271869b5d4c85392ba047db7617c297faa3"

S = "${WORKDIR}/qemu-${PV}"

inherit xenclient autotools-brokensep

# Include a minimal amount of blobs by default.
FILES_${PN} += "/usr/share/qemu/keymaps/en-us       \
                /usr/share/qemu/keymaps/commons     \
                /usr/share/qemu/keymaps/modifiers   \
                "
FILES_${PN}-dbg += "/usr/lib/.debug/* /usr/libexec/.debug/*"
FILES_${PN}-extra-keymaps = "/usr/share/qemu/keymaps/*"
FILES_${PN}-extra-roms = "/usr/share/qemu/*"
INSANE_SKIP_${PN}-extra-roms = "arch"
FILES_${PN}-utils = "/usr/libexec/*"

PACKAGES += "${PN}-extra-keymaps ${PN}-extra-roms ${PN}-utils"

EXTRA_OECONF += " \
    --enable-xen \
    --target-list=i386-softmmu \
    --without-system-pixman \
    --disable-sdl \
    --disable-vnc \
    --disable-docs \
    --disable-strip \
    --disable-virtfs \
    --disable-bluez \
    --disable-guest-agent \
    --disable-curses \
    --disable-slirp \
    --disable-curl \
    --disable-kvm \
    --disable-tools \
    --disable-guest-base \
    --enable-pie \
    --enable-werror \
    --enable-surfman \
    --enable-atapi-pt \
    --enable-atapi-pt-v4v \
    --enable-readonly-ide \
    --enable-debug \
"

do_configure(){
    ${S}/configure --prefix=${prefix} --sysconfdir=${sysconfdir} ${EXTRA_OECONF}
}

EXTRA_OEMAKE += "AUTOCONF_HOST='--host=`arch`' DESTDIR=${D} STRIP=''"

CFLAGS_append = " -Wno-unused-parameter -Wno-unused-local-typedefs --param ssp-buffer-size=4 -ftrapv -D_FORTIFY_SOURCE=2"

INC_PR = "r17"
