# Created by: Euan Thoms <euan@potensol.com>
# $FreeBSD$

PORTNAME=		sogo3
PORTVERSION=		3.1.4
CATEGORIES=		www gnustep
MASTER_SITES=		http://www.sogo.nu/files/downloads/SOGo/Sources/
DISTNAME=		SOGo-${PORTVERSION}

MAINTAINER=		euan@potensol.com
COMMENT=		Groupware server with a focus on scalability and open standards

LICENSE=		GPLv2

LIB_DEPENDS=		libmemcached.so:databases/libmemcached \
			libcurl.so:ftp/curl \
			libDOM.so:devel/sope3
RUN_DEPENDS=		zip:archivers/zip

OPTIONS_DEFINE=		ACTIVESYNC
OPTIONS_SUB=		yes

ACTIVESYNC_DESC=	Enable support for ActiveSync protocol

ACTIVESYNC_LIB_DEPENDS=	libwbxml2.so:textproc/wbxml2

USERS=			sogod
GROUPS=			sogod

USES=			gnustep objc
USE_GNUSTEP=		base build
USE_LDCONFIG=		${GNUSTEP_LOCAL_LIBRARIES}/sogo

CONFLICTS?=		sogo[2-3]-activesync-[0-9]* sogo2-[0-9]*

USE_RC_SUBR=		sogod

SUB_LIST+=		GNUSTEP_LOCAL_TOOLS=${GNUSTEP_LOCAL_TOOLS} \
			GNUSTEP_MAKEFILES=${GNUSTEP_MAKEFILES}
ETCDIR=			${PREFIX}/etc/${PORTNAME:S/3//}
CONFIGURE_ARGS=		--disable-debug --enable-strip

post-patch:
	@${GREP} -rlF '/etc/sogo' ${WRKSRC} \
		| ${XARGS} ${REINPLACE_CMD} 's#/etc/sogo#${PREFIX}/etc/sogo#g'
	@${REINPLACE_CMD} -e 's|/usr/|/usr/local/|g' ${WRKSRC}/Apache/SOGo.conf

post-patch-ACTIVESYNC-on:
	@${REINPLACE_CMD} -e 's/Tools/Tools ActiveSync/' ${WRKSRC}/GNUmakefile

do-configure:
	cd ${WRKSRC} ; . ${GNUSTEP_MAKEFILES}/GNUstep.sh ; ./configure ${CONFIGURE_ARGS}

post-install:
	${MKDIR} ${STAGEDIR}/var/spool/sogo
	${MKDIR} ${STAGEDIR}${ETCDIR}
	${INSTALL_DATA} ${WRKSRC}/Scripts/sogo.conf ${STAGEDIR}${ETCDIR}/sogo.conf.sample
	${INSTALL_DATA} ${WRKSRC}/Apache/SOGo.conf ${STAGEDIR}${ETCDIR}/SOGo-Apache.conf.sample
	${INSTALL_DATA} ${WRKSRC}/Apache/SOGo-apple-ab.conf ${STAGEDIR}${ETCDIR}/SOGo-apple-ab.Apache.conf.sample
	${INSTALL_DATA} ${FILESDIR}/expire-autoreply.creds.sample ${STAGEDIR}${ETCDIR}/
	${INSTALL_DATA} ${FILESDIR}/ealarms-notify.creds.sample ${STAGEDIR}${ETCDIR}/
	${INSTALL_DATA} ${FILESDIR}/cron-ealarms-notify.sample ${STAGEDIR}${PREFIX}/GNUstep/Local/Tools/Admin/
	${INSTALL_DATA} ${FILESDIR}/cron-expire-autoreply.sample ${STAGEDIR}${PREFIX}/GNUstep/Local/Tools/Admin/

.include <bsd.port.mk>
