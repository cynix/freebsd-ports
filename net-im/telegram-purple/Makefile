# Created by: Kris Moore <kmoore@freebsd.org>
# $FreeBSD$

PORTNAME=	telegram-purple
PORTVERSION=	1.2.6
DISTVERSIONPREFIX=	v
CATEGORIES=	net-im

MAINTAINER=	kevlo@FreeBSD.org
COMMENT=	Libpurple plugin for Telegram messenger

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/COPYING

BUILD_DEPENDS=	pidgin:net-im/pidgin
RUN_DEPENDS=	pidgin:net-im/pidgin

OPTIONS_DEFINE=	NLS
OPTIONS_SUB=	yes

USES=		execinfo gettext gmake pkgconfig tar:xz
USE_GNOME=	glib20 libxml2
USE_GCC=	yes
GNU_CONFIGURE=	yes
LIBS+=		-lexecinfo -lm

USE_GITHUB=	yes
GH_ACCOUNT=	majn:DEFAULT,tgl vysheng:tlparser
GH_PROJECT=	tgl:tgl tl-parser:tlparser
GH_TAGNAME?=	bec66c2:tgl 1659d87:tlparser

BROKEN_sparc64=	cannot compile: assertion fails

.include <bsd.port.pre.mk>

pre-configure:
	@${REINPLACE_CMD} -e 's|/etc/telegram-purple/server.tglpub|${PREFIX}/etc/telegram-purple/server.tglpub|g' \
		 ${WRKSRC}/telegram-purple.c

post-extract:
	@${MV} ${WRKSRC_tgl}/* ${WRKSRC}/tgl
	@${MV} ${WRKSRC_tlparser}/* ${WRKSRC}/tgl/tl-parser

.include <bsd.port.post.mk>
