# Created by: KalleDK <plexmaintainer@k-moeller.dk>
# $FreeBSD$

PORTNAME=	plexmediaserver
PORTVERSION?=	1.0.2.2413
PORTREVISION?=	0
CATEGORIES=	multimedia
MASTER_SITES=	https://downloads.plexapp.com/plex-media-server/${PORTVERSION}-${PLEX_BUILD}/
DISTNAME=	PlexMediaServer-${PORTVERSION}-${PLEX_BUILD}-freebsd-${ARCH}

MAINTAINER?=	feld@FreeBSD.org
COMMENT=	Plex Media Server component

USES=		cpe tar:bzip2
PLEX_BUILD?=	7caf41d
NO_BUILD=	yes
WRKSRC=	${WRKDIR}/PlexMediaServer-${PORTVERSION}-${PLEX_BUILD}

CPE_VENDOR=	plex
CPE_PRODUCT=	plex_media_server
CPE_VERSION=	${PORTVERSION:R}

USE_RC_SUBR?=	${PORTNAME}

SUB_FILES=	pkg-message
SUB_LIST?=	PORTNAME=${PORTNAME} DATADIR=${DATADIR} USERS=${USERS} GROUPS=${GROUPS}
PLIST_SUB+=	PLEX_BUILD=${PLEX_BUILD}

USERS=	plex
GROUPS=	${USERS}
BUNDLE_LIBS=	yes

ONLY_FOR_ARCHS=	amd64
ONLY_FOR_ARCHS_REASON=	binary-only program, source code not available

.include <bsd.port.pre.mk>

.if ${OPSYS} == FreeBSD && ${OSVERSION} >= 1000054
RUN_DEPENDS+=	${LOCALBASE}/lib/compat/libstdc++.so.6:misc/compat9x
.endif

post-patch:
	# binaries don't come pre-stripped
	${FIND} ${WRKSRC}/Resources -name '*.so' -exec ${STRIP_CMD} {} \+
	${STRIP_CMD} ${WRKSRC}/lib* ${WRKSRC}/Resources/Plex*
	${RM} ${WRKSRC}/start.sh
	# Older verisons of Plex we have to create a symlink
	# Newer versions of Plex ship a duplicate file; we'll just symlink
	${RM} ${WRKSRC}/libpython2.7.so

do-install:
	(cd ${WRKSRC} && ${COPYTREE_SHARE} \* ${STAGEDIR}/${DATADIR})
	# Python fix for older releases of Plex
	@${LN} -s ${DATADIR}/libpython2.7.so.1 ${STAGEDIR}/${DATADIR}/libpython2.7.so
	# Workaround for space in binary name
	@${LN} -s ${DATADIR}/Plex\ Media\ Server ${STAGEDIR}${DATADIR}/Plex_Media_Server

.include <bsd.port.post.mk>
