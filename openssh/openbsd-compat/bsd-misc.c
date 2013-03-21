/*
 * Copyright (c) 1999-2000 Damien Miller.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "includes.h"
#include "xmalloc.h"
#include "ssh.h"

RCSID("$Id: bsd-misc.c,v 1.1.1.3 2001/05/03 16:51:26 zarzycki Exp $");

char *get_progname(char *argv0)
{
#ifdef HAVE___PROGNAME
	extern char *__progname;

	return __progname;
#else
	char *p;

	if (argv0 == NULL)
		return "unknown";	/* XXX */
	p = strrchr(argv0, '/');
	if (p == NULL)
		p = argv0;
	else
		p++;
	return p;
#endif
}

#ifndef HAVE_SETLOGIN
int setlogin(const char *name)
{
	return(0);
}
#endif /* !HAVE_SETLOGIN */

#ifndef HAVE_INNETGR
int innetgr(const char *netgroup, const char *host, 
            const char *user, const char *domain)
{
	return(0);
}
#endif /* HAVE_INNETGR */

#if !defined(HAVE_SETEUID) && defined(HAVE_SETREUID)
int seteuid(uid_t euid)
{
	return(setreuid(-1,euid));
}
#endif /* !defined(HAVE_SETEUID) && defined(HAVE_SETREUID) */

#if !defined(HAVE_SETEGID) && defined(HAVE_SETRESGID)
int setegid(uid_t egid)
{
	return(setresgid(-1,egid,-1));
}
#endif /* !defined(HAVE_SETEGID) && defined(HAVE_SETRESGID) */

#if !defined(HAVE_STRERROR) && defined(HAVE_SYS_ERRLIST) && defined(HAVE_SYS_NERR)
const char *strerror(int e)
{
	extern int sys_nerr;
	extern char *sys_errlist[];
	
	if ((e >= 0) && (e < sys_nerr))
		return(sys_errlist[e]);
	else
		return("unlisted error");
}
#endif

#ifndef HAVE_UTIMES
int utimes(char *filename, struct timeval *tvp)
{
	struct utimbuf ub;

	ub.actime = tvp->tv_sec;
	ub.modtime = tvp->tv_usec;
	
	return(utime(filename, &ub));
}
#endif 