# $FreeBSD$

PORTNAME=	freefilesync
PORTVERSION=	8.2
CATEGORIES=	sysutils
MASTER_SITES=	http://www.freefilesync.org/download/ \
		http://www.freefilesync.org/archive/
DISTNAME=	FreeFileSync_${PORTVERSION}_Source

MAINTAINER=	kevlo@FreeBSD.org
COMMENT=	Backup software to synchronize files and folders

LICENSE=	GPLv3

BROKEN_FreeBSD_9=	does not build on FreeBSD < 10.x

BUILD_DEPENDS=	${LOCALBASE}/include/zenxml/xml.h:textproc/zenxml
LIB_DEPENDS=	libboost_system.so:devel/boost-libs \
		libnotify.so:devel/libnotify

WRKSRC=		${WRKDIR}/FreeFileSync/Source
DOS2UNIX_WRKSRC=${WRKDIR}
DOS2UNIX_GLOB=	*.cpp *.h

USES=		compiler:c++14-lang dos2unix gmake pkgconfig zip
USE_LDCONFIG=	yes
USE_WX=		3.0+

post-patch:
	@${REINPLACE_CMD} -e 's/wx-config/$${WX_CONFIG:T}/' \
		-e 's,g++,$${CXX},' ${WRKSRC}/Makefile
	@${REINPLACE_CMD} -e 's|<sys/vfs.h>|<sys/mount.h>|' \
		${WRKDIR}/zen/file_access.cpp
	@${REINPLACE_CMD} -e 's|WEXITSTATUS||' ${WRKDIR}/zen/shell_execute.h
	@${REINPLACE_CMD} -e 's|CLOCK_MONOTONIC_RAW|CLOCK_MONOTONIC|' \
		${WRKDIR}/zen/tick_count.h

.include <bsd.port.mk>
