/* ****************************************************************************

 Eine Zeile ins SysLog schreiben
 oder den Textinhalt einer ganzen Datei auf den Console/LogFile/Syslog schreiben
 Author: Hesti (hesti16@aol.de)
 Created: 04.07.19
 Copyright: Hesti ()
 License:   GNU GPL

*******************************************************************************

 12.06.18 HS Created
 04.07.19 HS Updated um Logfile umschreiben zu können
 05.07.19 HS ReUpdate heißt jetzt HSCopyLog
 17.02.20 HS -F C:\HS\Log\Hallo.log "Hallo ins Syslog schreiben" schreibt in ein File nicht ins SysLog
 24.01.21 HS -s syslog + stderr "Hallo ins ... schreiben"
 07.02.22 HS wenn -f ohne pfad, dann einen Pfad nach hsdir\log mappen incl. datum
 08.06.23 HS neue Auswertung

**************************************************************************** */

#include "tools.h"
#include "VERSION.h"

signed int main(int argc, char *argv[])
{
    int textat;
    textat = 1;

	if (InitTools(argc , argv, "%v%t%m", I_MAJOR, I_MINOR, I_BUILD, I_BETA, LOG_SYSLLOG)) return -1;
    if (argc<2) return -1;

    for (textat=1;textat<argc;textat++)
    {
        // -e knuffel "Moin Moin"
        // -e entrame "wo sind die Baeume"
        if (!strcmp(argv[textat],"-E"))
        {
            LogExtra = NULL;
            continue;
        }

        if (!strcmp(argv[textat],"-e"))
        {
            if ((textat+1)<argc)
            {
                LogType = LOG_SYSLLOG;
                textat++;
                LogExtra = argv[textat];
            }
            continue;
        }
        // -s "bla bla"
        if (!strcasecmp(argv[textat],"-s"))
        {
            LogType = LOG_SYSLLOG + LOG_STDERR;
            continue;
        }
        // -f/-F myname "bla more then"
        if (!strcasecmp(argv[textat],"-f"))
        {
            if ((textat+1)<argc)
            {
                textat++;
                LogFileName = argv[textat];
                LogType     = LOG_STDERR;

                if (!strcmp(Cbasename(argv[textat]), LogFileName))
                {
                    char *ext;
                    ext=CfilenameExt(argv[textat]);
                    if (ext[0]==0) ext="log";
                    sprintf_ex(m_Workfile, "%s\\%s-%s.%s", LogDir, CfilenameName(argv[textat]), datestr(unixtime()),ext);
                    LogFileName=m_Workfile;
                    //lprintf ("%s ** %s ** \"%s\" ** \"%s\"",Cbasename(argv[2]), LogFileName, CfilenameExt(argv[2]),m_Workfile);
                    //return 0;
                }
                LogType     = LOG_LOGFILE;
                if (argv[textat-1][1]=='F') LogType = LogType + LOG_STDERR;
                continue;
            }
        }
        break;
    }
    char *text;
    text = NULL;
    for (;textat<argc;textat++)
    {
        if (text) stradd(text, " ");
        stradd(text,argv[textat]);
    }
    if (text)
    {
        lprintf("%s", text);
        free(text);
    }
    return 0;
#ifdef OLDSTUFF
    LogExtra=NULL;
    //LogFileWithExtra=false;

    if ( (argc==3) && (!strcasecmp(argv[1],"-s")) )
    {
        textat = 2;
        LogType = LOG_SYSLLOG + LOG_STDERR;
    }
    if ( (argc==4) && (!strcasecmp(argv[1],"-f")) )
    {
        textat = 3;
        LogFileName = argv[2];
        LogType     = LOG_STDERR;

        if (!strcmp(Cbasename(argv[2]), LogFileName))
        {
            char *ext;
            ext=CfilenameExt(argv[2]);
            if (ext[0]==0) ext="log";
            sprintf_ex(m_Workfile, "%s\\%s-%s.%s", LogDir, CfilenameName(argv[2]), datestr(unixtime()),ext);
            LogFileName=m_Workfile;
            //lprintf ("%s ** %s ** \"%s\" ** \"%s\"",Cbasename(argv[2]), LogFileName, CfilenameExt(argv[2]),m_Workfile);
            //return 0;
        }
        LogType     = LOG_LOGFILE;
        if (argv[1][1]=='F') LogType = LogType + LOG_STDERR;
    }
    lprintf("%s", argv[textat]);
    return 0;
#endif
}
