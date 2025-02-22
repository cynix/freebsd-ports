# Created by: Daniel O'Connor
# $FreeBSD$

PORTNAME=	teamspeak3-server
PORTVERSION=	3.0.12.4
PORTEPOCH=	1
CATEGORIES=	audio net
MASTER_SITES=	http://dl.4players.de/ts/releases/${PORTVERSION}/ \
		http://teamspeak.gameserver.gamed.de/ts3/releases/${PORTVERSION}/
DISTNAME=	${PORTNAME}_freebsd_${TEAMSPEAK_ARCH}-${PORTVERSION}

MAINTAINER=	ultima1252@gmail.com
COMMENT=	Server side of the TeamSpeak group voice chat system

LICENSE=	teamspeak
LICENSE_NAME=	TeamSpeak 3.x End User License Agreement
LICENSE_FILE=	${WRKSRC}/LICENSE
LICENSE_PERMS=	no-dist-mirror no-dist-sell no-pkg-mirror no-pkg-sell

USES=		tar:bz2
NO_BUILD=	yes
USE_LDCONFIG=	${LIBDIR}
USE_RC_SUBR=	teamspeak
SUB_FILES=	pkg-message

# see release note
# http://forum.teamspeak.com/threads/123250-TeamSpeak-3-Server-3-0-12-3-released
BROKEN_FreeBSD_9=	No longer starts on 9.x

RESTRICTED=	No redistribution
ONLY_FOR_ARCHS=	amd64 i386

USERS=	teamspeak
GROUPS=	teamspeak

CONFLICTS=	teamspeak_server-[0-9]*

PLIST_SUB+=	DBDIR=${DBDIR} \
		ETCDIR=${ETCDIR} \
		LOGDIR=${LOGDIR} \
		BINGRP=${BINGRP}

SUB_LIST+=	DBDIR=${DBDIR} \
		ETCDIR=${ETCDIR} \
		LOGDIR=${LOGDIR}

OPTIONS_DEFINE=	DOCS

.include <bsd.port.options.mk>

.if ${ARCH} ==	"i386"
TEAMSPEAK_ARCH=	x86
WRKSRC=	${WRKDIR}/${PORTNAME}_freebsd_${TEAMSPEAK_ARCH}
.endif
.if ${ARCH} ==	"amd64"
TEAMSPEAK_ARCH=	amd64
WRKSRC=	${WRKDIR}/${PORTNAME}_freebsd_${TEAMSPEAK_ARCH}
.endif

DBDIR=	/var/db/teamspeak
ETCDIR=	${PREFIX}/etc/teamspeak
LIBDIR=	${PREFIX}/lib/teamspeak/server
LIBEXECDIR=	${PREFIX}/libexec
LOGDIR=	/var/log/teamspeak
SHAREDIR=	${PREFIX}/share/teamspeak/server
PORTDOCS=	permissiondoc.txt \
		privilegekey_guide.txt \
		server_quickstart.txt \
		server_upgrade.txt \
		update_mysql_to_mariadb.txt

do-install:
	@${MKDIR} ${STAGEDIR}${SHAREDIR}
	${INSTALL_DATA} ${WRKSRC}/CHANGELOG ${STAGEDIR}${SHAREDIR}
	${INSTALL_DATA} ${WRKSRC}/LICENSE ${STAGEDIR}${SHAREDIR}
	(cd ${WRKSRC} && ${COPYTREE_SHARE} "sql serverquerydocs" ${STAGEDIR}${SHAREDIR})

	@${MKDIR} ${STAGEDIR}${LIBDIR}
	${INSTALL_LIB} ${WRKSRC}/*.so ${STAGEDIR}${LIBDIR}
	${INSTALL_LIB} ${WRKSRC}/redist/*.so* ${STAGEDIR}${LIBDIR}

	${INSTALL_PROGRAM} ${WRKSRC}/ts3server \
		${STAGEDIR}${LIBEXECDIR}/

	@${MKDIR} ${STAGEDIR}${DOCSDIR}
.	for DOCFILE in ${PORTDOCS}
		${INSTALL_DATA} ${WRKSRC}/doc/${DOCFILE} ${STAGEDIR}${DOCSDIR}
.	endfor

	${INSTALL} -d ${STAGEDIR}${DBDIR}
	${INSTALL} -d ${STAGEDIR}${LOGDIR}
	${INSTALL} -d ${STAGEDIR}${ETCDIR}

.include <bsd.port.mk>
